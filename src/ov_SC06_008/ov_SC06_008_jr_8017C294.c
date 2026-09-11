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
extern u8 D_80187D4C;
extern u8 D_80187CBC;
extern u8 D_80187C98;
extern u8 D_80187C74;
extern u8 D_80187D28;
extern u8 D_80187D04;
extern u8 D_80187CE0;
extern u8 D_80187C50;
extern void func_80145934(void);
extern u8 D_80187DDC;
extern u8 D_80187DB8;
extern u8 D_80187D94;
extern u8 D_80187D70;
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
extern unsigned char D_801871D4[];
extern unsigned char D_80187204[];
extern unsigned char D_80187254[];
extern unsigned char D_80187284[];
extern unsigned char D_801872B4[];
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
extern void (*D_80187304[])(void *);
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
extern s32 D_801873CC[];
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
extern u8 D_80187454[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018745C;
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
extern int D_801A8E48;
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
extern s32 D_801A8E4C;
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
extern s32 D_8018748C;
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
extern s32 func_80151944(void *a0);
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
extern void (*D_80187534[])(void);
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
extern void (*D_80187558[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80187548;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018756C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80187578[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80187588[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801875A0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80187590;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801875B4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801875D0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801875C0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801875E4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801875F8[])(void);
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
extern s32 D_8018760C;
extern void (*D_80187634[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80187614;
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
extern int (*D_80187680[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80187684[])(void);
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
extern unsigned short D_80187AE8[];
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
extern void (*D_80187AF8[])(void);
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
extern int D_801A8E80;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80187B20[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80187B00;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80187B10;
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
extern void (*D_80187B60[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80187B68[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80187B34;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80187B74[])(void);
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
extern u8 D_80187B44;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801A8E88;
extern s32 D_801A8E94;
extern s32 D_801A8E98;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187BB0[])(s32 *);
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
extern s32 D_80187B84[];
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
extern s32 D_801A8E90;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80187E00[])(void);
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
extern char D_80187C20[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80187EA4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80187FF8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80187E14;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80188000[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80187E24;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80187E44;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80188008[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(int param_1);
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
extern void (*D_80188030[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018803C[])(void);
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
extern void (*D_80187EB0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801880E0;
extern void func_8015D380(s32 a0);
extern unsigned char D_801871C4[];
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
extern unsigned char D_801880F4[];
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
extern s8 D_80188130[];
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
extern u16 D_80188178;
extern u16 D_8018817A;
extern u16 D_8018817C;
extern s32 D_80188180;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80188188;
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
extern int D_80187E94;
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
extern unsigned int D_8018820C[];
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
extern void (*D_801882BC[])(void);
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
extern void func_801483E8(unsigned char *self);
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
extern int func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_801882EC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80188350;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801A8EA0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80188374[])(void);
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
extern int D_801A8EF8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801883BC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801883AC;
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
extern char D_801A8770[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801883C4[])(void);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418(s32 s0);
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void (*D_80188418[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801883E0;
extern s16 D_80188414;
extern s16 D_80188412;
extern s16 D_80188410;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80188424[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801A8F58;
extern u8 D_801A8F59;
extern u8 D_801A8F5A;
extern u8 D_801A8F5B;
extern u8 D_801A8F5C;
extern u8 D_801A8F5D;
extern u8 D_801A8F5E;
extern u8 D_801A8F5F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80188434[])(void);
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
extern s32 D_801A8F98;
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
extern void (*D_80188478[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801884F4[];
extern s32 D_80188514[];
extern u8 D_80188590[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801885B0[];
extern u8 D_801885D0[];
extern void func_800CAF6C(s32 *a0);
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
extern void (*D_8018866C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801886E8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801A8780;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801886F4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801886FC[])(void);
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
extern void (*D_801887C4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801887D4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801887E4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801887F0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80188750[];
extern u8   D_80188764[];
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
extern void (*D_80188808[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80188810[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80188818[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80188820[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80188828[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80188830[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80188838[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801888EC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801888F4[])(void);
extern void func_80169F00(void *a0);
extern char D_801888A4[];
extern char D_80188864[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018892C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80188938[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80188980[])(void);
extern void func_8016AB30(void *a0);
extern void func_8016B234(s32 param_1);
extern void func_8016AFB0(s32 a0);
extern void func_8016B114(void *arg0);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void (*D_801889FC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801A92B8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801889F0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80188A34[];
extern unsigned short D_80188A3C[];
extern unsigned short D_80188A44[];
extern unsigned char D_801A92C0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801A92B8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188A4C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801A93F4;
extern M2C_UNK D_801A93F8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801A9380;
extern void (*D_80188A7C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801A93FC[];
extern u8 D_801A9404[];
extern u8 D_801A93B4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80188A84[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80188AA0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80188AA8[])(void);
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
extern void (*D_80188B10[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80188AB4;
extern u8 D_80188AC0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80188B44[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188B4C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188BA0[])(void);
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
extern u16 D_80188BD4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80188BC4[];
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
extern s32 D_80188BF0;
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
extern void (*D_80188C68[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80188C70[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80188C78[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188C80[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80188C88[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80188C90[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80188C9C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80188CA8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80188CB4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80188CC4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80188CD4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80188CDC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80188CE4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80188CEC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80188CF4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80188CFC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80188D04[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80188D0C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80188D14[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80188D1C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80188D24[])(void);
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
extern void (*D_80188D2C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80188D34[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80188D3C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80188D44[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80188D4C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80188D54[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80188D5C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80188D64[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80188D6C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80188D74[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80188D7C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80188D84[])(void);
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
extern void (*D_80188DC8[])(void);
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
extern M2C_UNK D_80188D8C;
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
extern void (*D_80188DF8[])(void);
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
extern void (*D_80188E34[])(void);
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
extern void (*D_80188E8C[])();
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
extern void (*D_80188E9C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80188EA4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018900C[])();
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
extern void (*D_80189018[])();
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
extern M2C_UNK D_801A89C8;
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
extern s16 D_801AA7C0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801A9B38;
extern short D_801AA834;
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
extern s32 D_801A9F64;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801A9F8C;
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
extern s16 D_801A9F48;
extern s32 func_8017A3B0(void);
extern short D_801A9F84;
extern short D_801A9F80;
extern int func_800D0CA0(int);
extern int func_8001AAA0(s32 arg0);
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
extern s16 D_801A9F4C;
extern u16 D_801A9FCC;
extern u16 D_801A9FCE;
extern u16 D_801A9FD0;
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
extern s16 D_801A9FC4;
extern s16 D_801A9FC6;
extern s16 D_801A9FC8;
extern s16 D_801A9FBC;
extern s16 D_801A9FBE;
extern s16 D_801A9FC0;
extern void func_8017B7A8(void);
extern s16 D_801A9FDC;
extern s16 D_801A9FDE;
extern s16 D_801A9FE0;
extern s16 D_801A9FE4;
extern s16 D_801A9FE6;
extern s16 D_801A9FE8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801A9FD4;
extern short D_801A9FD6;
extern short D_801A9FD8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801A9F6C;
extern SV4 D_801A9F74;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801A9F94[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801A9F90)(void);
extern void func_8017BD50(int param_1);
extern void (*D_801891F4[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80189218[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C0BC(u8 *p);
extern void (*D_80189220[])(void);
extern void func_8017C150(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern u8 D_8018920C;
extern void func_8017C18C(s32 a0);
extern void func_8017C230(int a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017C294 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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






#include "../shared/ov/func_8017C294__t67f11bf2.h"


extern void func_8002931C(s32 a0);

void func_8017D174(void) {
    func_8002931C(0x1A40000);
}



extern void (*D_8018929C[])(void);

void func_8017D194(void *a0) {
    D_8018929C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D400(void);
extern void func_800167B8(s32 a0);

s32 func_8017D1D0(s32 a0) {
    func_8017D400();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D214(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_801892A4[])(void);

void func_8017D238(void *a0) {
    D_801892A4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D428(void);

s32 func_8017D274(s32 a0) {
    func_8017D428();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D2B4(u8 *a0) {
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


extern s32 func_800D1EBC(void);
    void func_8017D330(void) {
        func_800D1EBC();
    }



extern void (*D_801892B0[])(void);

void func_8017D350(void *a0) {
    D_801892B0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017D38C(s32 a0) {
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


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D400(void) {

    extern s32 D_801892BC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801892BC, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D428(void) {

    extern s32 D_801892C0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801892C0, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D4E8(void *a0);

void func_8017D450(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    D_80126968 = 0x3c7;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D4E8, 0);
    func_8012A094((s32)D_80126948);
    func_8017D4E8(D_80126948);
}



extern void (*D_801892CC[])(void);

void func_8017D4E8(void *a0) {
    D_801892CC[*(u8 *)((s32)a0 + 0x4)]();
}


typedef struct {
    s16 v[4];
} Blk8_80126940_8017D524;

void func_8017D524(s32 a0) {
    extern Blk8_80126940_8017D524 D_80126940;
    extern void func_8017D5A4(s32 a0, s16 *a1);
    Blk8_80126940_8017D524 sp10;

    sp10 = D_80126940;
    if (sp10.v[2] < 0x80) {
        sp10.v[2] = 0x80;
    }
    if (sp10.v[2] > 0x2140) {
        sp10.v[2] = 0x2140;
    }
    func_8017D5A4(a0, sp10.v);
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

void func_8017D5A4(s32 param_1, s16 *param_2) {
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


#include "common.h"

/* func_8017D73C -- ov_SC06_008 / ov_SC06_008_jr_8017C294
 * Adapted from the byte-matched sibling func_8017FAC0 (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c).
 * Symbol surface renamed per this TU's own .s (asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294/func_8017D73C.s).
 * Semantic edits vs the seed (measured against the target .s):
 *   1. The 3x20-entry scan loops use a variable trip count `n` instead of the seed's fixed 20:
 *      n = 0x14; if (*(s16 *)(a0 + 0x70) >= 2) { n = 0x10; }
 *   2. The tail func_8002D59C calls read entity field +0x36 (u16) where the seed reads +0x70
 *      (a different field on this entity type -- confirmed directly off the target .s
 *      `lhu $a2, 0x36($s3)` at both call sites, not caught by the site-diff card).
 */

typedef struct {
    u16 x; /* 0x00 */
    u16 y; /* 0x02 */
    u16 z; /* 0x04 */
    u16 w; /* 0x06 */
} V4_8017D73C;

extern u16 D_80126B62;
extern u16 D_80126B96;
extern u16 D_80189324[];
extern u16 D_8018934C[];
extern u16 D_80189374[];
extern void (*D_8018939C[])(s32);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BD14(s32 a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_8017D73C(s32 a0) {

    V4_8017D73C p1;
    V4_8017D73C p2;
    V4_8017D73C unused0;
    V4_8017D73C unused1;
    V4_8017D73C unused2;
    s32 i;
    s32 t;
    s32 y;
    s32 ret;
    s32 n;

    t = *(s16 *)(a0 + 0xA) + 0x20;
    y = *(s16 *)&D_80126B62 - t;
    if (y < -0x110) {
        y = -0x110;
    } else if (y > 0) {
        y = 0;
    }

    n = 0x14;
    if (*(s16 *)(a0 + 0x70) >= 2) {
        n = 0x10;
    }

    p1.y = y;
    p2.y = y;
    i = 0;
    if (n != 0) {
        do {
            p1.x = D_80189324[i];
            p1.z = D_80189324[i + 1];
            p2.x = D_80189324[i + 2];
            p2.z = D_80189324[i + 3];
            if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
                D_80126B96 = 0x4004;
            }
            i += 4;
        } while (i < n);
    }

    __asm__ ("" : "=r"(n) : "0"(n));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    i = 0;
    if (n != 0) {
        do {
            p1.x = D_8018934C[i];
            p1.z = D_8018934C[i + 1];
            p2.x = D_8018934C[i + 2];
            p2.z = D_8018934C[i + 3];
            if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
                D_80126B96 = 0x4004;
            }
            i += 4;
        } while (i < n);
    }

    __asm__ ("" : "=r"(n) : "0"(n));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    i = 0;
    if (n != 0) {
        do {
            p1.x = D_80189374[i];
            p1.z = D_80189374[i + 1];
            p2.x = D_80189374[i + 2];
            p2.z = D_80189374[i + 3];
            if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
                D_80126B96 = 0x4004;
            }
            i += 4;
        } while (i < n);
    }

    D_8018939C[*(u16 *)(a0 + 0x2)](a0);

    ret = func_8012BD14(a0);
    if (ret > 0x3FFFF) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8002D59C(4, 0x609, *(u16 *)(a0 + 0x36));
    } else {
        *(s16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - 1;
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(a0 + 0xFE) = 4;
            func_8002D59C(0x609, ((0x40000 - ret) * 127) / 0x40000 | 0x1000,
                          *(u16 *)(a0 + 0x36));
        }
    }
}


extern void (*D_801893E8[])(void);

void func_8017DA00(void *a0) {
    s32 pad[4]; /* load-bearing dead local: reserves 16B var_size (§162i1) matching target's 0x28 frame */
    D_801893E8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017DA3C(s32 param_1)
{
    extern u8 D_801893F0[];
    extern u8 D_80189450[];
    extern u8 D_801894B0[];
    extern u8 D_801894F8[];
    extern u16 D_80189540[];
    extern u16 D_80189550[];
    extern void func_8001CA1C(void *a0, void *a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012C1B8(void);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern void func_8012CAE4(void *a0);

    s32 pad[4];

    if ((*(s32 *)(param_1 + 0x20) = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        switch (*(s16 *)(param_1 + 0x70)) {
        case 0: {
            u16 *p50;
            u16 *p40;
            s32 i;
            *(u16 *)(param_1 + 2) = 1;
            *(s32 *)(param_1 + 0xDC) = 0x21100;
            for (i = 0, p50 = D_80189550, p40 = D_80189540; i < 7; p50++, p40++, i++) {
                s32 r = func_8012C658(0x305, 3, param_1);
                if (r != 0) {
                    *(u16 *)(r + 6) = *p40;
                    *(u16 *)(r + 0xE) = *p50;
                }
            }
            break;
        }
        case 1:
            *(u16 *)(param_1 + 2) = 3;
            func_8001CA1C((void *)*(s32 *)(param_1 + 0x20), D_801893F0);
            func_8012A828(param_1, D_801894B0);
            break;
        case 2:
            *(u16 *)(param_1 + 2) = 3;
            func_8001CA1C((void *)*(s32 *)(param_1 + 0x20), D_80189450);
            func_8012A828(param_1, D_801894F8);
            break;
        case 3:
            *(u16 *)(param_1 + 2) = 2;
            break;
        }
    }
}



extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32, void*, s32);
extern u8 D_80126B5C;
extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_8017DBB0(s32 param_1)
{
    s32 x;
    SVECTOR sv1;
    SVECTOR sv2;

    x = func_8012B6D4((s16 *)(param_1 + 4), (s16 *)&D_80126B5C);
    sv1.vx = *(u16 *)(param_1 + 6) - ((func_8004787C(x) << 4) >> 12);
    sv1.vy = -0x200;
    sv1.vz = *(u16 *)(param_1 + 0xE) - ((func_80047948(x) << 4) >> 12);
    sv2.vx = sv1.vx;
    sv2.vy = 0;
    sv2.vz = sv1.vz;
    ((s32 (*)(s32, void *, void *))func_80133784)(1, &sv1, &sv2);
    if ((u8)sv2.pad == 0x1B) {
        *(u16 *)(param_1 + 6) = sv1.vx;
        *(u16 *)(param_1 + 0xE) = sv1.vz;
    }
    {
        s32 dx = *(s16 *)(param_1 + 6) - *(s16 *)&D_80126B5E;
        s32 dz = *(s16 *)(param_1 + 0xE) - *(s16 *)&D_80126B66;
        s32 *p = *(s32 **)(param_1 + 0x64);
        x = dx * dx + dz * dz;
        if (x < *(p + 0x37)) {
            *(p + 0x37) = x;
        }
    }
}



extern void (*D_80189560[])(void);

void func_8017DCD0(void *a0) {
    D_80189560[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017DD0C(void *a0) {
        *(s8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
        *(s16 *)((s32)a0 + 0x5C) &= 0xC800;
    }


void func_8017DD24(s32 a0) {
    extern u8 D_801892F0[];
    extern u8 D_80185B40[];
    extern u8 D_801892D0[];
    s32 t;

    if (func_8012C354(a0, (s32)D_801892F0) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;
        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801892D0;
        *(s32 *)(a0 + 0xC4) = t | 0x2;
        func_8012A828(a0, (s32)D_80185B40);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;
        if (*(s16 *)(a0 + 0x70) >= 2) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0xD55;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0xD55;
        }
        func_8012C658(0x25C, 0x555, a0);
        func_8012C658(0x25C, 0xAAA, a0);
        func_8012C658(0x25C, 0x1000, a0);
    }
}



void func_8017DE04(void *a0) {
        void *a1 = *(void **)((char *)a0 + 0x20);
        *(u16 *)((char *)a1 + 0x12) += *(u16 *)((char *)a0 + 0xfc);
    }


void func_8017DE20(s32 a0) {
    extern u8 D_801893B4[];
    extern u8 D_80185B40[];
    extern u8 D_801892D0[];
    void *a2;
    s32 t;

    if (func_8012C354(a0, (s32)D_801893B4) != 0) {
        a2 = *(void **)((s32)a0 + 0x20);
        *(u32 *)((char *)a2 + 4) |= 0x80000000;
        *(u8 *)((s32)a0 + 0xC0) = 1;
        t = *(s32 *)((s32)a0 + 0xC4);
        *(s32 *)((s32)a0 + 0xBC) = (s32)D_801892D0;
        *(s32 *)((s32)a0 + 0xC4) = t | 0x2;
        func_8012A828(a0, (s32)D_80185B40);
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(u8 *)((s32)a0 + 0x75) = 0;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) >= 2) {
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = 0xD55;
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 0xD55;
        }
    }
}


extern void func_8012B2CC(s32 a0);


void func_8017DEEC(s32 *a0) {
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


extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017DF28(s32 param_1)
{
    s32 a1;

    a1 = *(s32 *)(param_1 + 0xDC);
    if (a1 > 0x1E3FF) {
        func_8002D4C8(4, 0x8B4);
    } else {
        func_8002D4C8(0x8B4, ((0x1E400 - a1) * 127 / 0x1E400 | 0x1000) & 0xFFFF);
    }
    *(s32 *)(param_1 + 0xDC) = 0x21100;
}


void func_8017DFBC(void) {
}


s32 func_8017DFC4(void) {
    return 111;
}


extern void func_8017DFEC(void);
void func_8017DFCC(void) {
    func_8017DFEC();
}


extern s32 D_801AA7AC;
extern s32 D_801A9FF0;
extern s32 D_801A9FF4;
extern s32 D_801A9FF8;
extern s32 D_801A9FFC;
extern s16 D_8019A568[];
extern s16 D_8019A61C[];
extern void func_8017E140(void *a0, s32 a1);

void func_8017DFEC(void) {
    switch (D_801AA7AC) {
    case 0:
        D_801A9FF0 = 1;
        D_801A9FF4 = 0;
        D_801A9FF8 = 1;
        D_801A9FFC = 0;
        D_801AA7AC = 1;
        break;
    case 1:
        if (--D_801A9FF0 == 0) {
            D_801A9FF0 = 1;
            func_8017E140(D_8019A568, D_801A9FF4 * 6);
            if (++D_801A9FF4 >= 15) {
                D_801A9FF4 = 0;
            }
        }
        if (--D_801A9FF8 == 0) {
            D_801A9FF8 = 2;
            func_8017E140(D_8019A61C, D_801A9FFC * 6);
            if (++D_801A9FFC >= 16) {
                D_801A9FFC = 0;
            }
        }
        break;
    }
}



void func_8017E140(void *a0, s32 a1)
{
    s32 offset;
    s16 buf[4];
    u16 t0, t1, t2, t3;
    u16 *ptr;

    offset = a1 << 1;
    ptr = (u16 *)((s32)offset + (s32)a0);

    t0 = ptr[0];
    buf[0] = t0;

    t1 = ptr[1];
    buf[1] = t1;

    t2 = ptr[2];
    buf[2] = t2;

    t3 = ptr[3];
    buf[3] = t3;

    MoveImage(buf, ptr[4], ptr[5]);
}



extern void (*D_801895AC[])(void);

void func_8017E1A0(void *a0) {
    D_801895AC[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012AD50(void *a0);
    void func_8017E1DC(s32 *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s16 *)((s32)a0 + 0xFE) = 0;
        *(s16 *)((s32)a0 + 0x100) = 0;
        ((void (*)(void))func_8012AD50)();
    }


extern s32 func_8017E37C(void *a0, s32 a1, s32 a2);

void func_8017E204(u8 *s1)
{
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v0, v1, s0;
    s32 pad[8];
    v0 = *(s16 *)(s1 + 0xDC);
    v1 = v0 + zr;
    if (v0 != 0) goto dec1;
    v0 = func_8017E37C(s1, *(s16 *)(s1 + 0xFC), 0);
    if (v0 != 0) {
        *(s16 *)(s1 + 0xFC) = 0;
        s0 = rand();
        v0 = rand();
        s0 &= 0xF;
        v0 &= 0xF;
        s0 += v0;
        s0 <<= 1;
        s0 += 0x20;
        *(s16 *)(s1 + 0xDC) = s0;
    } else {
        v0 = *(u16 *)(s1 + 0xFC) + 1;
        *(s16 *)(s1 + 0xFC) = v0;
    }
    goto next1;
dec1:
    *(s16 *)(s1 + 0xDC) = v1 - 1;
next1:
    v0 = *(s16 *)(s1 + 0xDE);
    v1 = v0 + zr;
    if (v0 != 0) goto dec2;
    v0 = func_8017E37C(s1, *(s16 *)(s1 + 0xFE), 0x80);
    if (v0 != 0) {
        *(s16 *)(s1 + 0xFE) = 0;
        s0 = rand();
        v0 = rand();
        s0 &= 0xF;
        v0 &= 0xF;
        s0 += v0;
        s0 <<= 1;
        s0 += 0x20;
        *(s16 *)(s1 + 0xDE) = s0;
    } else {
        v0 = *(u16 *)(s1 + 0xFE) + 1;
        *(s16 *)(s1 + 0xFE) = v0;
    }
    goto next2;
dec2:
    *(s16 *)(s1 + 0xDE) = v1 - 1;
next2:
    v0 = *(s16 *)(s1 + 0xE0);
    v1 = v0 + zr;
    if (v0 != 0) goto dec3;
    v0 = func_8017E37C(s1, *(s16 *)(s1 + 0x100), 0x100);
    if (v0 != 0) {
        *(s16 *)(s1 + 0x100) = 0;
        s0 = rand();
        v0 = rand();
        s0 &= 0xF;
        v0 &= 0xF;
        s0 += v0;
        s0 <<= 1;
        s0 += 0x20;
        *(s16 *)(s1 + 0xE0) = s0;
    } else {
        v0 = *(u16 *)(s1 + 0x100) + 1;
        *(s16 *)(s1 + 0x100) = v0;
    }
    goto next3;
dec3:
    *(s16 *)(s1 + 0xE0) = v1 - 1;
next3:
    ;
}


#include "common.h"

/* ---- decls (TU house style: ratan2/func_80021174/rand copied verbatim from
 *      the existing decls in src/ov_SC06_008/ov_SC06_008_jr_8017C294.c;
 *      func_801290DC is left unprototyped exactly as the neighbour
 *      func_8017EBAC uses it; func_8017EBAC matches its definition below in
 *      the same TU. D_80189570 / D_801895B4 are new to this TU.) ---- */
extern u16 *D_80189570[];
extern s32 D_801895B4;
extern s32 func_80021174(s32 a0, s32 a1);
extern s32 ratan2(s32 dx, s32 dy);
extern s32 rand(void);
extern void func_8017EBAC(int param_1);
extern s32 func_801290DC();

/* 0x10-byte spawn record built on the stack at sp+0x10 */
typedef struct {
    s16 x;    /* 0x00 */
    s16 y;    /* 0x02 */
    s16 z;    /* 0x04 */
    u16 ang;  /* 0x06 */
    s16 f8;   /* 0x08 */
    s16 fA;   /* 0x0A */
    s16 fC;   /* 0x0C */
    s16 fE;   /* 0x0E */
} Cfg_8017E37C;

/* 0x10-byte VECTOR at sp+0x20 (pad needed: it fixes s0/ra at 0x30/0x34) */
typedef struct {
    s32 vx, vy, vz, pad;
} Vec_8017E37C;

s32 func_8017E37C(void *a0, s32 a1, s32 a2)
{
    Cfg_8017E37C sp10;
    Vec_8017E37C sp20;
    u16 *p;
    s32 q;

    /* §219: the base load and the stride add MUST be two statements —
     * folding them into one expression schedules the a1*6 chain first and
     * lands the base in $v1 instead of accumulating into $s0. */
    p = D_80189570[*(s16 *)((s32)a0 + 0x70)];
    p += (s16)a1 * 3;

    sp10.x = p[0];
    sp20.vx = sp10.x;
    sp10.y = p[1] + a2;
    sp20.vy = sp10.y;
    sp10.z = p[2];
    sp20.vz = sp10.z;
    sp10.f8 = p[3];
    if (sp10.f8 == 0x7FFF) {
        return 1;
    }
    if (func_80021174(D_801895B4, (s32)&sp20) != 1) {
        return 0;
    }
    sp10.fC = p[5];
    sp10.ang = ratan2(sp10.f8 - sp10.x, sp10.fC - sp10.z);
    q = func_801290DC(0x68, &sp10);
    if (q != 0) {
        *(s16 *)(q + 0x2C) = sp10.ang;
    }
    if ((rand() & 7) == 0) {
        func_8017EBAC((int)&sp10);
    }
    return 0;
}



extern void (*D_80189604[])(void);

void func_8017E4BC(void *a0) {
    D_80189604[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801895B8[];

void func_8017E4F8(void *a0)
{
    s32 s0;
    s32 s1;
    s16 v0;

    s1 = (s32)a0;
    s0 = *(s32 *)(s1 + 0x20);
    func_8001CC3C(s0, (s32)D_801895B8, 0x2C0, 0x100);
    *(u8 *)(s0 + 0x27) = 0x46;
    v0 = 0x1333;
    *(s16 *)(s0 + 0x1A) = v0;
    *(s16 *)(s0 + 0x18) = v0;
    *(s32 *)(s0 + 0x4) |= 0x08000000;
    *(s16 *)(s0 + 0x14) = *(u16 *)(s1 + 0x2C);
    *(s32 *)(s1 + 0x30) = 0;
    *(s16 *)(s1 + 0x2) = *(u16 *)(s1 + 0x2) + 1;
}


void func_8017E580(s32 a0) {
    extern void (*D_801895C4[])(void);
    extern void (*D_801895C6[])(void);
    extern void func_801292C8();
    s16 h;
    s32 w;
    s32 i;

    h = *(s16 *)((s32)&D_801895C4 + (*(s32 *)(a0 + 0x30) << 3));
    w = *(s32 *)(a0 + 0x20);
    if (h != 0) {
        *(s16 *)(w + 0x28) = h;
        i = *(s32 *)(a0 + 0x30);
        *(s32 *)(a0 + 0x30) = i + 1;
        *(s16 *)(w + 0x2A) = *(u16 *)((s32)&D_801895C6 + (i << 3));
    } else {
        func_801292C8(a0);
    }
}



extern void (*D_80189620[])(void);

void func_8017E5F0(void *a0) {
    D_80189620[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012EF70(s32 a0, s32 a1);
extern void func_80015954(s32 a0, s32 a1);

void func_8017E62C(s32 param_1) {
    s16 buf[4];

    func_80015978(param_1 + 4, (s32 *)buf);
    func_8012EF70((s32)buf, (s32)buf);
    func_80015954((s32)buf, param_1 + 4);
    *(s32 *)(param_1 + 0x1c) = 3;
    *(s16 *)(param_1 + 2) += 1;
}


void func_8017E694(s32 a0) {
    extern void func_801292C8();
    if (*(s32 *)(a0 + 0x1c) == 0) {
        func_801292C8(a0);
    } else {
        func_8017E6F0(a0);
        *(s32 *)(a0 + 0x1c) -= 1;
    }
}




void func_8017E6F0(s32 param_1) {
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8017E830(s32 a0, s16 *a1, void *a2, void *a3, void *a4, void *a5, s16 *a6, void *a7);
    extern Blk8 D_80189628[];
    extern void *D_8018960C[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    s32 i;
    s32 j;

    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_80189628[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8017E830(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, &D_8018960C[i]);
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

extern SVECTOR_8017E6D8 D_801AA000[4];
extern struct PW8017E6D8 D_801AA020;
extern struct PW8017E6D8 D_801AA024;
extern u8 D_801AA028, D_801AA029, D_801AA02A, D_801AA02C, D_801AA02D, D_801AA02E;
extern int D_801AA030;


/* GTE VARIANT `gte_rtv0tr_m`: memory beyond Sony's `gte_rtv0tr` — a scheduling steer, its uses are marked (P36 T5) */
#define gte_rtv0tr_m()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")


void func_8017E830(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801AA000[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801AA030 = 0x50000000;
        D_801AA028 = 0;
        D_801AA029 = 0;
        D_801AA02A = 0;
        D_801AA02C = 0;
        D_801AA02D = 0;
        D_801AA02E = 0;
    }
    D_801AA020 = h[0];
    D_801AA024 = h[1];

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
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rtv0tr_m();  // !FAKE: gte via gte_rtv0tr_m — memory beyond Sony's `gte_rtv0tr` (P36 T5 gte1)
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}



void func_8017EBAC(int param_1)
{
    int p;
    s32 r1;
    s32 r2;
    s16 r3;
    s16 v;

    p = func_801290DC(0x69, param_1);
    if (p != 0) {
        r1 = rand();
        r2 = rand();
        r3 = rand();
        v = (r1 & 3) * 1024;
        v += (r2 & 3) * 250;
        v += (r3 & 3) * 68;
        *(s16 *)(p + 0x10) = v;
    }
}










extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

s32 func_8017EC48(s32 param_1, s32 param_2)
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    SVECTOR sv1;
    SVECTOR sv2;

    sv1.vx = *(short *)(param_1 + 6);
    sv1.vy = *(short *)(param_1 + 0xa) + -0x20;
    sv1.vz = *(short *)(param_1 + 0xe);
    iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    iVar3 = (short)param_2;
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
    return 0;
}


#include "common.h"

/* TU declares func_8017ED80 as void(void) (S35 self-axis) but the asm takes
 * $a0 as a pointer parameter — bind through a private C name. */
extern void aF8017ED80(void *param_1) __asm__("func_8017ED80");

void aF8017ED80(void *param_1) {
    u8 *a0 = (u8 *)param_1;
    s32 iVar2;

    if (*(u16 *)(a0 + 0x0) != 0) {
        iVar2 = *(s32 *)(a0 + 0xCC);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFC);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(u32 *)(*(s32 *)(a0 + 0x20) + 0x4) & 0x80000000) {
            *(u32 *)(iVar2 + 0x4) |= 0x80000000;
        } else {
            *(u32 *)(iVar2 + 0x4) &= 0x7FFFFFFF;
        }

        iVar2 = *(s32 *)(a0 + 0xD0);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFE);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(u32 *)(*(s32 *)(a0 + 0x20) + 0x4) & 0x80000000) {
            *(u32 *)(iVar2 + 0x4) |= 0x80000000;
        } else {
            *(u32 *)(iVar2 + 0x4) &= 0x7FFFFFFF;
        }
    }
}


#include "common.h"

/* func_8017EF54 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (open-only h_norm
 * cluster exemplar, 7 members).
 *
 * a0+0x0  : u16 active flag; 0 => early return.
 * a0+0x84 : s16 sound cooldown timer.
 *   cooldown != 0  -> just decrement it.
 *   cooldown == 0  -> try to play a positional sound (RotTransPers screen
 *                     projection of the parent's position, range-gated on
 *                     screen X/Y, volume from the classic div-by-0xF0 /
 *                     div-by-0x1E magic-constant idiom -- byte-proven sibling
 *                     form is func_80181CF0 in this same TU, sndid 0x849 here
 *                     vs 0x961 there), then unconditionally reset the timer
 *                     to 0xA regardless of whether the sound actually played.
 * a0+0xFC / 0xFE : running hit-combo accumulators, bumped by +/-0x280 every
 *                     call (unconditional tail).
 * Tail always calls func_8017ED80(a0) (the TU's canonical decl for this
 * symbol is void(void) -- S35 self-axis -- so this draft binds its own
 * private extern with the asm's real void(void*) shape).
 *
 * Control flow is EXPLICIT goto/label, mirroring source-order block
 * placement (gcc-2.7.2 lays out basic blocks in literal source order, not by
 * fallthrough preference -- see the func_80181CF0 comment, same TU): the
 * cooldown!=0 decrement is the SHORT block and sits out-of-line (jumped to),
 * the cooldown==0 RTP+sound block is the LONG block and sits inline
 * (fallthrough), matching the target's physical layout exactly.
 *
 * MATCH levers (byte-proven, 2026-08-05):
 *  1. Naive `if(old!=0){cool=old-1;}else{...}` folds trivially: reorg.c's
 *     delay-slot filler steals the single-insn decrement into the `bnez`'s
 *     own delay slot and retargets the branch straight to the join label
 *     (2 ins short of target). The target instead keeps a genuine copy
 *     (`addu $v1,$v0,zero`) in the delay slot and a SEPARATE `addiu $v0,$v1,-1`
 *     at the decrement site. Reproduced by pinning a second variable
 *     `register s32 v1 __asm__("$3")`, assigned UNCONDITIONALLY right after
 *     the load (`v1 = old;`) -- the scheduler places that copy in the
 *     branch's delay slot on its own, and the decrement (`cool = v1 - 1`)
 *     can no longer be folded away. `cool` is separately pinned to
 *     `__asm__("$2")` so its other def sites (the three `cool = 0xA` early
 *     exits) don't drift onto $3 by coalescing with v1.
 *  2. The tail's `sh $v0,0x84($s0)` / `addu $a0,$s0,zero` order (store off
 *     the callee-saved pointer BEFORE reloading it into the call-argument
 *     register) needed a `__asm__ __volatile__("":::"memory")` fence right
 *     after the store -- without it, sched1 hoists the independent a0-reload
 *     ahead of the store even when the reload is written later in source.
 *  3. Frame is -0x38, 8 bytes (2 words) larger than the natural -0x30 the
 *     locals alone produce; `pad2[2]` (dead, address never read) inside `L`
 *     reserves them, mirroring func_80181CF0's own "dead aggregate sizes the
 *     frame" idiom.
 */


/* §37/§124 def-side asm-label alias (P30 S1d class lever): the TU declares
 * `extern void func_8017EF54(void);` (L4082, L4091) for callers that invoke it with NO args,
 * while the byte-true definition takes an s32 in $a0 -> `conflicting types`. Neither side can
 * move (a no-prototype escape is illegal once a param promotes), so the DEFINITION gets a
 * private C identifier and binds the emitted symbol with a GNU asm label. Zero blast radius:
 * the TU's declaration never meets the definition, and the emitted symbol is unchanged. */
void aF8017EF54(s32 a0) __asm__("func_8017EF54");

void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern void func_8017ED80(void *a0);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2[2]; /* sp+0x24 -- dead, sizes the frame */
    } L;

    s32 v1;
    s32 cool;
    s32 old;

    if (*(u16 *)(a0 + 0x0) == 0) {
        return;
    }

    old = *(s16 *)(a0 + 0x84);
    v1 = old;
    if (old != 0) {
        goto L_dec;
    }

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

    if (L.flag < 0) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[0] + 0xEF) & 0xFFFF) >= 0x1DF) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[1] + 0xB3) & 0xFFFF) >= 0x167) {
        goto L_snd_skip;
    }

    {
        s32 sx = (s16)L.sxy[0];
        s32 av;

        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x849, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_snd_skip:
    cool = 0xA;
    goto L_join;

L_dec:
    cool = v1 - 1;

L_join:
    *(s16 *)(a0 + 0x84) = cool;
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)

    {
        s32 p = a0;
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x280;
        *(u16 *)(p + 0xFE) = *(u16 *)(p + 0xFE) - 0x280;
        func_8017ED80((void *)p);
    }
}


#include "common.h"

extern s32  D_801151D4;
extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_8017ED80(void);

void func_8017F100(s32 a0)
{
    u16 nv[4];
    s32 g;
    s32 s0;
    s32 idx;

    g = D_801151D4;

    if (*(u16 *)a0 != 0) {
        idx = *(s32 *)(a0 + 0x1C) & 3;
        switch (idx) {
        case 0:
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            break;
        case 1:
            break;
        case 2:
        case 3:
            s0 = (s32)func_8012913C(0x23);
            if (s0 != 0) {
                *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x3F) - 0x20;
                *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x3F) - 0x30;
                {
                    s32 r = rand();
                    s32 t = *(u16 *)(a0 + 0xE);
                    *(s32 *)(s0 + 0x18) = 0;
                    *(s32 *)(s0 + 0x14) = 0;
                    *(s32 *)(s0 + 0x10) = 0;
                    *(s16 *)(s0 + 0xE) = t + (r & 0x3F) - 0x20;
                }
                *(s16 *)(s0 + 0x34) = (rand() & 0x17FF) + 0x800;
                nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
                nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
                nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
                VectorNormalSS(nv, nv);
                *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)nv[0] >> 6);
                *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)nv[1] >> 6);
                *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)nv[2] >> 6);
            }
            break;
        }
        ((void (*)(s32))func_8017ED80)(a0);
    }
}


extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017EC48(s32 a0, s32 a1);

void func_8017F2E8(s32 a0)
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
        register s32 s0v __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        register s32 p20 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_8017EC48(a0, 0x51) == 0) {
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
        if (func_8017EC48(a0, 0x51) == 0) {
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
        func_8017EC48(a0, 0x51);
        if (*(s16 *)(a0 + 0x102) == 0) {
            *(u16 *)(a0 + 0x34) = 3;
        } else {
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) - 1;
        }
        break;
    }
    case 3: {
        s32 s2v;
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        if (func_8017EC48(a0, 0x51) != 0) {
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


extern s32 func_80180548(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

extern u8 D_8019C904;
extern u8 D_8019C90C;
extern u8 D_8019C914;
extern u8 D_800AF648;

void func_8017F624(s32 param_1)
{
    extern u8 D_800AF648_b __asm__("D_800AF648");
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

            func_80180548(param_1, (s32)&D_8019C904);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_8019C90C, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_8019C914, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
            L.rv[1] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
            L.rv[2] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
            { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
            { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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








extern s16 D_8019C91C[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

void func_8017F8CC(s32 a0)
{
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
    {
        s16 idx = *(s16 *)(a0 + 0x70);
        s16 *p = &D_8019C91C[(idx - 1) * 4];
        s16 gx = *(s16 *)&D_80126B5E;
        s16 gz;
        s32 p20;

        if (!(*p < gx)) {
            break;
        }
        p++;
        if (!(gx < *p)) {
            break;
        }
        p++;
        gz = *(s16 *)&D_80126B66;
        if (!(*p < gz)) {
            break;
        }
        if (!(gz < p[1])) {
            break;
        }

        p20 = *(s32 *)(a0 + 0x20);
        *(u32 *)(p20 + 4) = *(u32 *)(p20 + 4) & 0x7FFFFFFF;

        {
            s32 t;

            *(s16 *)(a0 + 0x88) = D_80126B5E;
            *(s16 *)(a0 + 0x6)  = D_80126B5E;
            t = D_80126B62 - 0x80;
            *(s16 *)(a0 + 0x8A) = t;

            t = *(u16 *)(a0 + 0x34);
            {
                s16 z;
                z = D_80126B66;
                *(u16 *)(a0 + 0x34) = (t + 1);
                *(s16 *)(a0 + 0x8C) = z;
                *(s16 *)(a0 + 0xE)  = z;
            }
        }
        break;
    }
    case 1:
    {
        s16 v;

        v = *(u16 *)(a0 + 0xA) + 8;
        *(u16 *)(a0 + 0xA) = v;
        if (v < *(s16 *)(a0 + 0x8A)) {
            break;
        }
        *(s16 *)(a0 + 0x2) = 1;
        *(u16 *)(a0 + 0x34) = 0;
        break;
    }
    }
}


extern s32 D_8019C93C[];
extern void func_8017EF54(void);

void func_8017F9FC(s32 a0)
{
    void (*handler)(s32);

    handler = (void (*)(s32))D_8019C93C[*(u16 *)(a0 + 0x2)];
    handler(a0);

    if (*(u16 *)(a0 + 0x0) == 0)
        return;

    ((void (*)(s32))func_8017EF54)(a0);

    if (func_8012C044(a0) == 0)
        return;

    if (*(s16 *)(a0 + 0x70) == 0) {
        if (*(s32 *)(a0 + 0xCC) != 0)
            func_80016714(*(void **)(a0 + 0xCC), 0x84);
        if (*(s32 *)(a0 + 0xD0) != 0)
            func_80016714(*(void **)(a0 + 0xD0), 0x84);
        func_8012C098((void *)a0);
    } else {
        if (*(u16 *)(a0 + 0x2) < 4)
            *(u16 *)(a0 + 0x2) = 4;
    }
}



extern void (*D_8019C968[])(void);

void func_8017FAD4(void *a0) {
    D_8019C968[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* SV4 is the TU-canonical name (src/shared/engine_types.h) for func_8012F214's
 * in/out struct (see ov_SC06_008_jr_8017AE2C.c:3135, "SV4 svec" comment: func_8012F214 out).
 * Isolated match_one has no include path to that header, so it is typedef'd
 * locally here for the standalone compile only. */


/* func_8017FB10 - ov_SC06_008 / ov_SC06_008_jr_8017C294 (93 ins)
 *
 * One-time init (guarded by state flag at +0x34): mirror the +0x64 sub-object's
 * +0x20/+0x12 field into our own +0x20 sub-object, kick off two "core" calls,
 * pick an entry from the 2-element 12-byte table D_8019C970 (indexed by the
 * s16 at +0x70), then call func_8012F214 with a zeroed input SV4 and read the
 * first 3 fields of the output SV4 back into +6/+0xA/+0xE.  Sets the countdown
 * at +0x1c to 0x5a and marks the state flag +0x34 = 1.
 *
 * Always-executed tail: bump the +0x20 sub-object's +0x10/+0x12/+0x14 fields
 * (reloading the +0x20 pointer fresh for each field -- no CSE across the
 * intervening stores, straight literal translation), mirror +0x14 into +0xDC,
 * call func_8012CBCC(a0) and test its return (canonical fleet decl is
 * void func_8012CBCC(s32 a0); the return value is read via a function-
 * pointer cast at the use site, per the established TU idiom -- see
 * ov_SC03_099_jr_8017BEBC.c:5630 comment block). If (ret & 0x6000), decrement
 * the +0xac counter (signed s16 compare-to-zero on the POST-decrement value --
 * gcc-2.7.2's sll-by-16/bnez idiom for a s16 local) and negate +0xDC into
 * +0x14; on the counter hitting zero, call func_8012C218. Finally decrement
 * the +0x1c countdown and call func_8012C218 again when IT hits zero.
 */

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_8019C970;

void func_8017FB10(s32 a0)
{
    SV4 in;
    SV4 out;
    s16 v1;
    u16 uStack_c;

    if (*(u16 *)(a0 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, *(s16 *)(a0 + 0x70) * 12 + (s32)&D_8019C970);

        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        func_8012F214(a0, (s32)&in, (s32)&out);
        *(u16 *)(a0 + 6) = out.a;
        *(u16 *)(a0 + 0xa) = out.b;
        uStack_c = out.c;
        *(s32 *)(a0 + 0x1c) = 0x5a;
        *(u16 *)(a0 + 0x34) = 1;
        *(u16 *)(a0 + 0xe) = uStack_c;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += -0x80;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 4;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0xfc);

    *(s32 *)(a0 + 0xdc) = *(s32 *)(a0 + 0x14);
    if ((((s32 (*)(s32))func_8012CBCC)(a0)) & 0x6000) {
        register s32 negdc __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
        negdc = -*(s32 *)(a0 + 0xdc);
        v1 = *(u16 *)(a0 + 0xac);
        v1 -= 1;
        *(s16 *)(a0 + 0xac) = v1;
        *(s32 *)(a0 + 0x14) = negdc;
        if (v1 == 0) {
            func_8012C218((void *)a0);
        }
    }

    {
        s32 iVar3 = *(s32 *)(a0 + 0x1c) - 1;
        *(s32 *)(a0 + 0x1c) = iVar3;
        if (iVar3 == 0) {
            func_8012C218((void *)a0);
        }
    }
}



extern void (*D_8019C988[])(void);

void func_8017FC84(void *a0) {
    D_8019C988[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_8017FCC0(a0)
s32 a0;
{
    if (*(s16 *)(a0 + 0x70) != 0) {
        *(u16 *)(a0 + 0x2) = 4;
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x5E) = 0;
        *(u8 *)(a0 + 0xC1) = 0;
        return;
    }

    if (*(s32 *)(a0 + 0xCC) != 0)
        func_80016714(*(void **)(a0 + 0xCC), 0x84);

    if (*(s32 *)(a0 + 0xD0) != 0)
        func_80016714(*(void **)(a0 + 0xD0), 0x84);

    func_8002A04C(a0);
    func_8012C218((void *)a0);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8017ED80(void);

void func_8017FD48(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8017ED80)(a0);
}


extern void func_8017EF54(void);
    void func_8017FD80(s32 *param) {
        *(s16 *)(*(s32 *)((char *)param + 0x20) + 0x10) = 0xE00;
        func_8017EF54();
    }




extern void func_8017EF54(void);
    void func_8017FDA8(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x10) += 0x20;
        ((void (*)(void))func_8017EF54)();
    }


extern void func_80131E00(int, int);
extern void func_8017EF54(void);

void func_8017FDDC(a0)
s32 a0;
{
    if (*(s16 *)(a0 + 0x76) < 0) {
        func_80131E00(a0, 6);
    } else {
        *(s16 *)(a0 + 2) = 1;
        *(s16 *)(a0 + 0x100) = 0x3C;
        *(u16 *)(a0 + 0x34) = 0;
        func_8017EF54();
    }
}


extern int func_80143C74(short*, int);
extern s32 rand(void);
extern void func_8017EF54(void);

void func_8017FE28(s32 a0)
{
    s32 s0;

    if (*(u16 *)(a0 + 0x0) != 0) {
        s0 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x3F) - 0x20;
            *(u16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x3F) - 0x30;
            *(u16 *)(s0 + 0xE) = *(u16 *)(a0 + 0xE) + (rand() & 0x3F) - 0x20;
            *(s32 *)(s0 + 0x10) = -*(s32 *)(a0 + 0x10);
            *(s32 *)(s0 + 0x14) = -*(s32 *)(a0 + 0x14);
            *(s32 *)(s0 + 0x18) = -*(s32 *)(a0 + 0x18);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18) = 0x800;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) = 0x800;
        }
        ((void (*)(s32))func_8017EF54)(a0);
    }
}


extern void func_8017ED80(void);
    void func_8017FF14(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x10) >> 1;
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0x18) >> 1;
        ((void (*)(void))func_8017ED80)();
    }


extern void func_8017ED80(void);
    void func_8017FF48(s32 a0) {
        s32 v0;
        v0 = 0xc;
        *(s8 *)(a0 + 0xc1) = v0;
        *(s32 *)(a0 + 0x1c) = 0x3c;
        ((void (*)(void))func_8017ED80)();
    }


void func_8017FF74(s32 a0)
{
    extern void func_801319E0(s32 a0);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_8012CBF4(s32 a0);
    extern void func_80131C78(s32 a0);
    extern void func_80131E00(int a0, int a1);
    extern void func_8017ED80(void);
    s16 field_a;
    s32 result;

    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x10) {
        func_801319E0(a0);
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_80131E00(a0, 6);
        } else {
            result = ((s32 (*)(s32))func_8012CBF4)(a0);
            if (result & 0x2000) {
                func_80131C78(a0);
            }
            ((void (*)(s32))func_8017ED80)(a0);
        }
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_80143970();
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(void *a0);

void func_80180000(s32 a0) {

    extern u8 D_8019C808[];
    extern u8 D_8019E548[];
    extern u8 D_8019C83C[];
    extern u8 D_8019E258[];
    extern u8 D_8019E530[];
    extern u8 D_80185B40[];

    s32 s0;
    u16 t;

    if (func_8012C354(a0, D_8019C808) == 0) {
        return;
    }
    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -0x1001;
    ((s32 (*)(s32))func_80143970)(a0);
    func_8012A828(a0, D_8019E548);
    *(u16 *)(a0 + 0x2) += 1;
    func_8012B200((u8 *)a0);
    *(s32 *)(a0 + 0xBC) = (s32)D_8019C83C;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        goto fail;
    }
    *(s32 *)(a0 + 0xCC) = s0;
    func_8001C214(s0, (s32)D_8019E258);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_80185B40;
    *(u16 *)(s0 + 0x2C) = t;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        func_80016714((void *)*(s32 *)(a0 + 0xCC), 0x84);
fail:
        func_8012CAE4((void *)a0);
        return;
    }
    *(s32 *)(a0 + 0xD0) = s0;
    func_8001C214(s0, (s32)D_8019E530);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_80185B40;
    *(u16 *)(s0 + 0x2C) = t;
    *(u16 *)(a0 + 0x100) = 0x3C;
    *(s32 *)(a0 + 0xDC) = 0xFFFC0000;
}


extern s32 D_80126B60;
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_8017EC48(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);

void func_80180128(s32 a0)
{
    s32 sp10[3];

    if (*(s32 *)(a0 + 8) >= D_80126B60 - 0x200000) {
        if (*(s32 *)(a0 + 0x48) >= 0) {
            *(s32 *)(a0 + 0x48) = -0x8000;
            *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        }
    } else {
        if (D_80126B60 - 0x180000 >= *(s32 *)(a0 + 8)) {
            if (*(s32 *)(a0 + 0x48) <= 0) {
                *(s32 *)(a0 + 0x48) = 0x8000;
                *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
            }
        }
    }

    *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) >> 1;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = *(s32 *)(a0 + 0xDC);
    func_8012B1B4(a0, (s32)sp10);
    func_8012CBCC(a0);
    func_8017EC48(a0, 0x51);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    *(u16 *)(a0 + 0x100) -= 1;
    if (*(s16 *)(a0 + 0x100) == 0) {
        *(s16 *)(a0 + 2) = 3;
        *(u16 *)(a0 + 0x100) = 5;
        *(s32 *)(a0 + 0x1C) = 0;
    }
}




void func_8018025C(s32 a0) {
    s32 p;
    s32 q;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(a0 + 0x6) = 0x7FFF;
    *(s16 *)(a0 + 0xA) = -0x1000;
    *(u16 *)(a0 + 0x2) = 5;
    *(u16 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x1C) = 0x12C;
    *(s32 *)(p + 0x4) |= 0x80000000;
    q = *(s32 *)(a0 + 0x20);
    *(u16 *)(q + 0x1C) = 0x1000;
    *(u16 *)(q + 0x1A) = 0x1000;
    *(u16 *)(q + 0x18) = 0x1000;
    *(u16 *)(a0 + 0x76) = 0x1E0;
    *(u16 *)(a0 + 0x5C) = 0x8810;
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_801802BC(s32 param_1)
{
    extern u8 D_8019E628[];
    extern u8 D_80185B40[];

    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(v0, (s32)D_8019E628);
        func_8012A828(param_1, (void *)D_80185B40);
        *(u16 *)(param_1 + 0x2) = 1;
        *(s32 *)(param_1 + 0x1C) = 0x40;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x10);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x14);
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B370(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

extern s32 D_8019C954;
extern s32 D_8019C960;
extern u8 D_800D3918[];

void func_8018037C(s32 a0)
{
    s32 v0;

    if (*(s16 *)(a0 + 6) == *(s16 *)(a0 + 0xDE) &&
        *(s16 *)(a0 + 0xE) == *(s16 *)(a0 + 0xE2)) {
        func_8012C218((void *)a0);
    } else {
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 4);
        *(s32 *)(a0 + 0xE0) = *(s32 *)(a0 + 0xC);
        func_8012B14C(a0, (s32)&D_8019C954);
        func_8012AD80(a0);

        if (func_8012D5E4(a0, (s32)&D_8019C960, (s32)&D_800D3918, 0x30) != 0) {
            func_8012C218((void *)a0);
        } else {
            v0 = *(s32 *)(a0 + 0x1c) - 1;
            *(s32 *)(a0 + 0x1c) = v0;
            if (v0 == 0) {
                func_8012C218((void *)a0);
            } else {
                func_8012B370(a0);
            }
        }
    }
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 rand(void);
extern u8 D_8019E6E8[];

void func_80180450(s32 param_1)
{
    *(s32 *)(param_1 + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(param_1 + 0x20) == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_8019E6E8);

        *(u16 *)(param_1 + 0x2) = 1;
        *(u16 *)(param_1 + 0x34) = 0;
        {
            s32 v1 = *(s32 *)(param_1 + 0x64);
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_80047948(*(s16 *)(t + 0x12));
            *(s32 *)(param_1 + 0xC) = *(s32 *)(param_1 + 0xC) + (r << 8);
        }
        {
            s32 v1 = *(s32 *)(param_1 + 0x64);
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_8004787C(*(s16 *)(t + 0x12));
            *(s32 *)(param_1 + 0x4) = *(s32 *)(param_1 + 0x4) + (r << 8);
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(u16 *)(t + 0x2C) = *(u16 *)(t + 0x2C) | 0x10;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x18) = 0x1800;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x1A) = 0x1800;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x1C) = 0x1800;
        }

        *(u16 *)(param_1 + 0xAC) = 2;
        {
            s32 r = rand();
            *(u16 *)(param_1 + 0xFC) = r & 0xFF;
        }
    }
}



extern s32 D_801AA178;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80180548(s32 a0, s32 a1) {
    D_801AA178 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801AA178;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_80180578(s32 param_1) {

    extern M2C_UNK D_80185B40;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_8019E704;
    extern MATRIX *D_8019E738;     /* matrix pool cursor */
    extern MATRIX D_801AA158[];    /* matrix pool end */

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    MATRIX *m;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8019E704) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80185B40));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801AA178, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* take the next matrix from the pool (wraps near the end); the post-increment
       is what keeps the load in $v0 and the copy into $s1. */
    m = D_8019E738++;
    *(MATRIX **)(param_1 + 0xcc) = m;
    if (D_8019E738 > D_801AA158) {
        D_8019E738 = D_801AA158 - 9;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, m);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)m);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        m = D_8019E738++;
        *(MATRIX **)(param_1 + 0xd0) = m;
        if (D_8019E738 > D_801AA158) {
            D_8019E738 = D_801AA158 - 9;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), m);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)m);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(void *a0);


// @class: regalloc-order
// @stuck: none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_801807BC(s32 param_1) {

    extern signed char D_8019E6F0[];
    int self = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    do { iVar1 = *(int *)(self + 0x1c); } while (0);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_8019E6F0;
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
            p = D_8019E6F0;
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
        do { *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1; } while (0);
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        func_8012C218((void *)self);
    }
}



extern void (*D_8019E73C[])(void);

void func_80180A5C(void *a0) {
    D_8019E73C[*(u16 *)((s32)a0 + 0x2)]();
}




// @class: schedule
// @stuck: none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_80180A98(int param_1, short param_2)
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


/* func_80180CA8 — ov_SC06_008 / ov_SC06_008_jr_8017C294
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

extern s32  D_801151D4;
extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();

void func_80180CA8(s32 a0)
{
    extern u8 D_800AF648_b __asm__("D_800AF648");
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
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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
        func_8012C218((void *)a0);
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


// TARGET: func_801810AC  (ov_SC06_008, TU ov_SC06_008_jr_8017C294.c, 93 ins)
//
// Template: func_801821F8 in this SAME TU (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c,
// around line 5283) is an already-MATCHED sibling (126 ins) with a documented byte-exact
// idiom set (its comment, verbatim):
//   @class: plumbing
//   @stuck: none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//     lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//     `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//     (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//     hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//     the `< 1` test.
//
// func_801810AC is the SAME body with the leading "if (*(short*)(param_1+0xfc)==0) {...}" block
// (the 0x64-indirected 3x int-copy + 3x u16-copy prologue) removed, and the "already fired" gate
// field is 0xe2 instead of 0x102. Confirmed against the target .s: no reference anywhere to 0xfc,
// 0x64, or 0x102/0x20 offsets; the gate compare is `lh $v1, 0xE2($s0)` / `sh $v1(=0xA), 0xE2($s0)`.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_801810AC(int param_1)
{
    extern unsigned char D_8019EE30[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    *(char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xe2) == 0) {
        *(short *)(param_1 + 0xe2) = 10;
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
                func_80019064(D_8019EE30);
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


void func_80181220(int param_1) {

    extern u8 D_8019EE50[];
    extern u8 D_8019ED94[];
    extern u8 D_8019ED54[];
    extern u8 D_8019ED9C[];
    extern u8 D_8019ED74[];
    extern u8 D_801A30BC[];
    extern u8 D_801A636C[];
    extern u8 D_8019EE90[];
    extern u8 D_801A61D4[];
    extern u8 D_801A625C[];
    extern u8 D_801A62E4[];
    int iVar1;

    iVar1 = func_8012C354(param_1, D_8019EE50);
    if (iVar1 != 0) {
        if (*(short *)(param_1 + 0x70) != 0) {
            func_800599B8(D_8019ED94, D_8019ED54);
            func_800599B8(D_8019ED9C, D_8019ED74);
            func_8001C214(*(int *)(param_1 + 0x20), D_801A30BC);
        }
        *(u8 *)(param_1 + 0xc0) = 1;
        *(int *)(param_1 + 0xb4) = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        *(short *)(param_1 + 0xae) = 0x2100;
        func_8012A828(param_1, D_801A636C);
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
    *(u32 *)(param_1 + 0xbc) = (u32)D_8019EE90;
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
        *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x18) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = 0x2400;
    *(u16 *)(param_1 + 2) = 8;
    func_8012A828(param_1, D_801A61D4);
    func_8012A828(*(int *)(param_1 + 0xcc), D_801A625C);
    func_8012A828(*(int *)(param_1 + 0xd0), D_801A62E4);
    return;
}


#include "common.h"

/* func_801813D0 — ov_SC06_008 / ov_SC06_008_jr_8017C294.  MATCH 163/163.
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
extern int func_80180A98(int param_1, short param_2);

void func_801813D0(s32 a0) {

    extern u8 D_8019EEB0[];

    /* §137/K3+K5: unpinned, the a0-copy allocno (R=37/L=137, pri 13503) is
     * ranked first and first-fits $s0, pushing `tbl` to $s1 — a clean 2-reg
     * perm no source reordering can flip (pri(tbl) = 394). Pinning `tbl` to
     * $16 makes $s0 "already dirty" in find_reg pass 0: the a0 copy conflicts
     * with it and opens $s1, and case 3's `d` (which does NOT conflict with
     * `tbl`) grabs $s0 in pass 0 — exactly the target's assignment. */
    register s32 tbl __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    s32 ns;

    tbl = (s32)D_8019EEB0;
    func_8012B1B4(a0, tbl);
    func_8012CBCC(a0);

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_80180A98(a0, 0x48) != 0 ||
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
        if (func_80180A98(a0, 0x48) == 0 &&
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
        func_80180A98(a0, 0x48);
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
        if (func_80180A98(a0, 0x48) == 0) {
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


#include "common.h"

/* func_8018165C — ov_SC06_008 jr_8017C294 (family of 7).  MATCH 305/305.
 *
 * §136c sibling-first paid for the whole body: the RTP + positional-sound tail
 * is the byte-proven RTP_SND block from
 * src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.c:3480 (func_8017E120) plus the
 * panner from src/ov_SC03_103/ov_SC03_103_jr_8017C294.c:5378 (func_801819DC):
 *   - $a0-pinned scopes REMATERIALISE &D_800AF648 per call (else CSE hoists it
 *     into a callee-saved reg and shoves the actor out of $s0),
 *   - `u16 sxy[2]` + `(u32)((sxy[i] + K) & 0xFFFF) < N` range tests (u32 cast
 *     is what keeps the compare `sltiu` rather than `slt`),
 *   - `ax = x; if (x < 0) ax = -x;` — the branch must test x, NOT ax, so reorg
 *     can sink the copy into the bgez delay slot,
 *   - the zero-byte re-tie `__asm__("" : "=r"(v) : "0"(v))` after the vol
 *     divide: both divides share one HI/LO and priority is height-to-block-end,
 *     so without it the pan quotient (which feeds the `bne`) issues first,
 *   - the pan quotient REUSES `x`'s pseudo (target `subu $a2,$v0,$a0`),
 *   - 0x3000 in a local `flg` so fold cannot reassociate the `ori` onto the pan,
 *     and the OR stays inside the call ARGUMENT.
 * §88a: both copies are written LONGHAND via the macro; gcc cross-jumps the
 * common 4-insn suffix itself (target `.L80181A20`).
 *
 * Four deltas from the SC03_103 twin, each measured here:
 *  1. NO hard-register pin on the abs result — instead `ax` and `vol` are ONE
 *     variable.  The twin pins ax to $a1 and keeps vol separate; this target
 *     wants BOTH in $v1 (`addu $v1,$a2,$zero` … `subu $v1,$v0,$v1`), which one
 *     variable gives for free.  Pinning it to $3 instead makes `ax` a hard reg,
 *     and then local-alloc's combine_regs ties the tail's `ori` dest to the
 *     dying $v1 (`ori $v1,$v1,0x3000`) — the target has `ori $a1,$v1,0x3000`.
 *     A plain pseudo is a GLOBAL allocno, which combine_regs will not tie.  (21
 *     -> 11 -> 8 mismatches across the two spellings.)
 *  2. ONE local for the sprite angle AND the mod-16 index.  Two locals put the
 *     index in $s1 (reusing the dead sprite pointer); one gives the target's
 *     $s2 (§136 L1 inverted — MERGING, not splitting).
 *  3. ONE local `p` for the 0xCC/0xD0 child pointers, used in BOTH branches.
 *     In the else-branch it is a call argument, so regclass's arg-copy
 *     preference pulls the whole allocno to $a0 and frees $v0 for the constant
 *     1 (`addiu $v0,$zero,1` / `lw $a0,0xCC($s0)`).  Confined to the then-branch
 *     it wins $v0 on priority and the constant falls to $v1 (8 off).
 *  4. STORE ORDER: `*(spr+0x14) = 0x40000` must be written AFTER the 0xE
 *     statement.  Written before it, it lands ahead of the `jal func_80047948`
 *     and frees the next call's `addu $a0,$s2,$zero` early enough for reorg to
 *     eat the bgez delay slot (-1 ins).  After it, the scheduler hoists the
 *     lui/sw pair inside .L80181724 by itself (idiom 4 / S1: same-base
 *     `reg+const` stores are disambiguated, so the hoist is free).
 * Idiom 6: 8 bytes of dead aggregate precede L.v so the RTP block sits at
 * sp+0x18 (vars 0x20 => frame 0x40).
 *
 * Decls: func_8002D4C8 / func_8004787C / func_80047948 / func_8004914C /
 * func_800491AC / func_8012A828 / func_8012913C are copied VERBATIM from the TU
 * (lines 59, 2205, 2204, 2645, 2646, 3781, 4356).  RotTransPers, D_800AF648 and
 * D_8019ED14 appear nowhere in the TU (fleet-dominant forms used); the three
 * D_801A6xxx tables are declared BLOCK-scope exactly as func_80181220 does.
 */

extern u8  *func_8012913C();
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

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

void func_8018165C(s32 a0) {

    extern u8  D_800AF648;
    extern s32 D_8019ED14[];
    extern u8  D_801A61D4[];
    extern u8  D_801A625C[];
    extern u8  D_801A62E4[];
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
            RTP_SND(0x95F)  // !FAKE: instruction via RTP_SND — REFUSED macro-carried instruction: the lever is inside `#define RTP_SND` with real code around it (T5) (P36 rung B tus9)
        } else if (m == 0) {
            RTP_SND(0x960)  // !FAKE: instruction via RTP_SND — REFUSED macro-carried instruction: the lever is inside `#define RTP_SND` with real code around it (T5) (P36 rung B tus9)
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = D_8019ED14[m];
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
        func_8012A828(a0, D_801A61D4);
        p = *(s32 *)(a0 + 0xCC);
        if (p != 0) {
            func_8012A828(p, D_801A625C);
        }
        p = *(s32 *)(a0 + 0xD0);
        if (p != 0) {
            func_8012A828(p, D_801A62E4);
        }
    }
}


#include "common.h"

extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8   D_800AF648;

void func_80181B20(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    s16 hp;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp < 0x301) {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + total;
    } else {
        p = *(s32 *)(a0 + 0xD0);
        *(s16 *)(a0 + 2) = 3;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x98) = 0;
        *(s16 *)(p + 2) = 3;
        *(s32 *)(p + 0x1C) = 0x1E;
        *(s16 *)(p + 0x98) = 0;

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            func_8002D4C8(0x961, (ax | (0x3000 | x)) & 0xFFFF);
        }
    }
    func_8012B370(a0);
}


#include "common.h"

/* func_80181CF0 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (family of 7)
 *
 * Low-HP flinch/knockback reaction. hp = *(s16*)(a0->0x20 ptr + 0x14). If
 * 0 < hp < 0xD00, put self AND the partner at a0->0xCC into stagger state 3
 * (a 0x1E-frame timer, status flag cleared), compute a screen-space
 * position via RotTransPers and play a positional sound. Otherwise
 * (hp==0 or hp>=0xD00) apply the accumulated hit-combo counter (0xFC/0xFE)
 * to the target's HP and re-mask its low 12 bits.
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND form from func_8018165C in this same TU (line 4746) -- v[]/pad,
 * u16 sxy[2], s32 z, s32 flag, and the ax/x div-by-0xF0 / div-by-0x1E
 * magic-constant idiom (0x88888889); also confirmed against func_801823F0
 * (same TU) which reuses the identical sndid 0x961 and the identical
 * `sx = (sx + 0xF0) / 0x1E; if (sx == 0x10) sx = 0xF; sx <<= 8;` tail.
 *
 * Control flow: gcc-2.7.2 lays out basic blocks in literal SOURCE order, not
 * by fallthrough-preference. A nested-if spelling (`if (hp<0xD00) { state=3;
 * if (hp!=0) { B; goto end; } } A; end:`) places B (textually the inner
 * then-body) inline right after the tests and relocates A after it -- the
 * REVERSE of the target, which has the short block A inline and the long
 * RTP+sound block B out-of-line. Explicit goto/label with A written BEFORE B
 * in source (`if (hp>=0xD00) goto L_A; state=3; if (hp!=0) goto L_B; L_A: A;
 * goto L_end; L_B: B; L_end: ...`) reproduces the target's physical layout
 * directly -- no branch-polarity inversion needed, just source ORDER.
 *
 * Frame: RotTransPers args are sp+0x10 (v), sp+0x18 (&sxy), sp+0x1C (&z),
 * sp+0x20 (&flag); v[3]+pad1 fills 0x10-0x17, sxy 0x18-0x1B, z 0x1C-0x1F,
 * flag 0x20-0x23 -- leaves a dead 4 bytes (0x24-0x27) before the s0 save at
 * 0x28. A trailing `pad2` dead struct member (same aggregate, so it can't
 * be eliminated) reserves those 4 bytes, mirroring func_8018165C's own
 * "dead aggregate sizes the frame" idiom (comment there: idiom 6).
 */

extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8   D_800AF648;

void func_80181CF0(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2;    /* sp+0x24 -- dead, sizes the frame */
    } L;

    s16 hp;
    s32 state;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp >= 0xD00) {
        goto L_A;
    }
    state = 3;
    if (hp != 0) {
        goto L_B;
    }

L_A:
    {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;
    }
    goto L_end;

L_B:
    p = *(s32 *)(a0 + 0xCC);
    *(s16 *)(a0 + 2) = state;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(s16 *)(a0 + 0x98) = 0;
    *(s16 *)(p + 2) = state;
    *(s32 *)(p + 0x1C) = 0x1E;
    *(s16 *)(p + 0x98) = 0;

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
        s32 sx = (s16)L.sxy[0];
        s32 av;
        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_end:
    func_8012B370(a0);
}


extern void (*D_8019EEC0[])(void);

extern s32 func_8012C044(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012C098(void *a0);
/* func_80143C74: the TU's decl `extern int func_80143C74(short *, int);` is at L5082 — BELOW this
   splice point (§17a-1 D2), so dropping our own left it undeclared. Declare it in the TU's EXACT
   shape (compatible with the later decl) and cast at the use — codegen-neutral. */
extern int func_80143C74(short *, int);
extern s32 rand(void);

extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181EE0(s32 a0)
{
    extern u8 D_800AF648_b __asm__("D_800AF648");
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    D_8019EEC0[*(u16 *)(a0 + 0x2)]();

    if (*(u16 *)(a0 + 0x0) != 0) {
        if (*(s16 *)(a0 + 0x70) == 0 && func_8012C044(a0) != 0) {
            if (*(s32 *)(a0 + 0xCC) != 0) {
                func_8012C218(*(void **)(a0 + 0xCC));
            }
            if (*(s32 *)(a0 + 0xD0) != 0) {
                func_8012C218(*(void **)(a0 + 0xD0));
            }
            func_8012C098((void *)a0);
        } else {
            s16 v;

            v = *(s16 *)(a0 + 0xE2);
            if (v != 0) {
                v = v - 1;
                *(s16 *)(a0 + 0xE2) = v;
                if (v == 0) {
                    *(u16 *)(a0 + 0x5C) &= 0xBFFF;
                }
            }

            if ((*(s16 *)(a0 + 0x76) < 5) && ((rand() & 3) == 0)) {
                s32 iVar2 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
                s32 r;

                if (iVar2 != 0) {
                    r = rand();
                    *(s32 *)(iVar2 + 0x10) = ((r & 0x7FF) - 0x400) << 8;
                    *(s32 *)(iVar2 + 0x14) = 0xFFF00000;
                    r = rand();
                    *(s32 *)(iVar2 + 0x18) = ((r & 0x7FF) - 0x400) << 8;
                    r = rand();
                    *(u16 *)(iVar2 + 0x6) -= 0x20;
                    *(u16 *)(iVar2 + 0x6) += (r & 0x3F);
                    *(s16 *)(iVar2 + 0xA) -= 0xC0;
                    r = rand();
                    *(u16 *)(iVar2 + 0xE) -= 0x20;
                    *(u16 *)(iVar2 + 0xE) += (r & 0x3F);
                }
            }

            if (*(u16 *)(a0 + 0x2) != 1 && *(u16 *)(a0 + 0x2) != 5) {
                *(s16 *)(a0 + 0x84) = 0xE;
            } else {
                if (*(s16 *)(a0 + 0x84) != 0) {
                    *(s16 *)(a0 + 0x84) = *(s16 *)(a0 + 0x84) - 1;
                } else {
                    *(s16 *)(a0 + 0x84) = 0xE;

                    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
                    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
                    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
                    { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
                    { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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
                        x = (x + 0xF0) / 0x1E;
                        if (x == 0x10) {
                            x = 0xF;
                        }
                        x = x << 8;
                        {
                            s32 flg = 0x3000;
                            func_8002D4C8(0x8BF, ((ax | flg) | x) & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
}



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

void func_801821F8(int param_1)
{

    extern unsigned char D_8019EE30[];
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
                func_80019064(D_8019EE30);
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


extern s32 D_801151D4;

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 *func_8012913C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

void func_801823F0(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

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
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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
        func_8012C218((void *)a0);
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

void func_80182838(short *param_1)
{

    extern void (*D_8019EF48[])(short *);
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
    D_8019EF48[*(unsigned short *)(param_1 + 1)](param_1);
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


#include "common.h"

extern s32 D_801151D4;

extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
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


void func_80182A48(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

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
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
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
        func_8012C218((void *)a0);
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

void func_80182E8C(s32 a0) {

    extern void (*D_8019EFC0[])(s32);
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

    D_8019EFC0[*(u16 *)(a0 + 2)](a0);

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
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern u8  *func_8012913C();
extern void func_801292C8();
extern int  func_8012D664();

extern u16 D_801270C0;

void func_8018309C(s32 arg0) {

    extern u8  D_8019EDA4;
    extern u8  D_8019EDB0;
    extern u16 D_80126B96;
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (*(u16 *)(arg0 + 2) == 0) {
        *(u8 **)(*(s32 *)(arg0 + 0x20) + 0x20) = &D_8019EDA4;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x50000000;
        *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x59;
        func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)&D_8019EDB0);
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


void func_80183320(s32 param_1)
{
  int p;
  *(s16 *)(param_1 + 0x5c) = 0;
  *(s16 *)(param_1 + 0xfc) = 0x1e;
  p = *(int *)(param_1 + 0xcc);
  *(s16 *)(p + 0x5c) = 0;
  p = *(int *)(param_1 + 0xd0);
  *(s16 *)(p + 0x5c) = 0;
}


#include "common.h"

extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern int func_80180A98(int param_1, short param_2);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012A828(s32 a0, void *a1);

void func_80183340(s32 a0) {
    extern u8 D_8019EEB0[];
    extern u8 D_801A666C[];
    extern u8 D_801A675C[];
    extern u8 D_801A684C[];
    s32 pad[4];

    func_8012B1B4(a0, (s32)D_8019EEB0);
    func_8012CBCC(a0);
    func_80180A98(a0, 0x48);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    *(u16 *)(a0 + 0x100) -= 1;
    if (*(s16 *)(a0 + 0x100) == 0) {
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(a0 + 0x100) = 0x2D;
        *(s32 *)(a0 + 0x1C) = 0;
        *(s16 *)(a0 + 0x104) = 0;
        func_8012A828(a0, D_801A666C);

        if (*(s32 *)(a0 + 0xCC) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xCC), D_801A675C);
        }
        if (*(s32 *)(a0 + 0xD0) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xD0), D_801A684C);
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);

void func_80183440(s32 a0) {
    extern u8 D_801A636C[];
    extern u8 D_801A646C[];
    extern u8 D_801A656C[];

    if (*(s16 *)(a0 + 0x100) == 0) {
        *(u16 *)(a0 + 2) = 1;
        *(s16 *)(a0 + 0x100) = 0x3C;
        func_8012A828(a0, D_801A636C);
        if (*(s32 *)(a0 + 0xCC) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xCC), D_801A646C);
        }
        if (*(s32 *)(a0 + 0xD0) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xD0), D_801A656C);
        }
    } else {
        *(s16 *)(a0 + 0x100) = *(s16 *)(a0 + 0x100) - 1;
    }
}


extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_801834E0(s32 a0)
{
    s32 t;
    u32 *p;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        p = *(u32 **)(a0 + 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((*(s32 *)(a0 + 0x1C) & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                *(s32 *)(obj + 0x1C) = 2;
                *(s16 *)(obj + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(obj + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


void func_801835A0(s32 a0) {
    extern u8 D_801A636C[];
    extern u8 D_801A646C[];
    extern u8 D_801A656C[];

    if (*(s16 *)(a0 + 0xFC) == 0) {
        *(u16 *)(a0 + 2) = 1;
        func_8012A828(a0, D_801A636C);
        if (*(s32 *)(a0 + 0xCC) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xCC), D_801A646C);
        }
        if (*(s32 *)(a0 + 0xD0) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xD0), D_801A656C);
        }
    } else {
        *(s16 *)(a0 + 0xFC) = *(s16 *)(a0 + 0xFC) - 1;
    }
}




















void func_80183638(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B030(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80183658(s32 a0) {

    extern u8 D_8019EEF4[];
    extern u8 D_801A3E2C[];
    extern u8 D_801A646C[];
    extern u8 D_8019EF28[];

    s32 v0;

    v0 = func_8012C354(a0, (s32)D_8019EEF4);
    if (v0 != 0) {
        if (*(s16 *)(a0 + 0x70) != 0) {
            func_8001C214(*(s32 *)(a0 + 0x20), (s32)D_801A3E2C);
        }
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = 0xFFFFDFDF;
        func_8012B030(a0);
        *(s16 *)(a0 + 0xAE) = 0x2100;
        func_8012A828(a0, D_801A646C);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        func_8012B23C(a0);
        *(void **)(a0 + 0xBC) = D_8019EF28;
        *(u32 *)(a0 + 0xC4) = *(u32 *)(a0 + 0xC4) | 2;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x2400;
    }
}


void func_80183748(void) {
}

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012B370(s32 a0);

void func_80183750(s32 a0) {
    u16 cnt;
    u16 acc;

    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) < 0x401) {
        cnt = *(u16 *)(a0 + 0xFC);
        acc = *(u16 *)(a0 + 0xFE);
        cnt = cnt + 1;
        acc = acc + cnt;
        *(u16 *)(a0 + 0xFC) = cnt;
        *(u16 *)(a0 + 0xFE) = acc;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + acc;
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 4;
        *(s32 *)(a0 + 4) = *(s32 *)(a0 + 4) +
            func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x40;
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) -
            func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x40;
    } else {
        *(u16 *)(a0 + 2) = 3;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(u16 *)(a0 + 0x98) = 0;
    }
    func_8012B370(a0);
}



extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80183824(s32 a0)
{
    s32 t;
    u32 *p;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        p = *(u32 **)(a0 + 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((*(s32 *)(a0 + 0x1C) & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                *(s32 *)(obj + 0x1C) = 2;
                *(s16 *)(obj + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(obj + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int a0);
    void func_801838E4(void) {
        ((void (*)(void))func_8012B370)();
    }


















void func_80183904(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B030();
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80183924(s32 a0) {

    extern u8 D_8019EF6C[];
    extern u8 D_801A4B98[];
    extern u8 D_8019EFA0[];
    extern u8 D_801A656C[];

    s32 v0;

    v0 = func_8012C354(a0, (s32)D_8019EF6C);
    if (v0 != 0) {
        if (*(s16 *)(a0 + 0x70) != 0) {
            func_8001C214(*(s32 *)(a0 + 0x20), (s32)D_801A4B98);
        }
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = 0xFFFFDFDF;
        func_8012B030(a0);
        *(void **)(a0 + 0xBC) = D_8019EFA0;
        *(s16 *)(a0 + 0xAE) = 0x2100;
        *(u32 *)(a0 + 0xC4) = *(u32 *)(a0 + 0xC4) | 2;
        func_8012A828(a0, D_801A656C);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        func_8012B23C(a0);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x2400;
    }
}


void func_80183A18(void) {
}

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012B370(s32 a0);

void func_80183A20(s32 a0) {
    s16 ang;
    u16 cnt;
    u16 acc;

    ang = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (ang < 0xC00) {
        if (ang != 0) {
            goto state3;
        }
    }

    cnt = *(u16 *)(a0 + 0xFC);
    acc = *(u16 *)(a0 + 0xFE);
    cnt = cnt + 1;
    acc = acc + cnt;
    *(u16 *)(a0 + 0xFC) = cnt;
    *(u16 *)(a0 + 0xFE) = acc;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - acc;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;

    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 8;

    *(s32 *)(a0 + 4) = *(s32 *)(a0 + 4) -
        func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x80;

    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) +
        func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x80;
    goto tail;

state3:
    *(u16 *)(a0 + 2) = 3;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(u16 *)(a0 + 0x98) = 0;

tail:
    func_8012B370(a0);
}



extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80183B14(s32 a0)
{
    s32 t;
    u32 *p;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        p = *(u32 **)(a0 + 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((*(s32 *)(a0 + 0x1C) & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                *(s32 *)(obj + 0x1C) = 2;
                *(s16 *)(obj + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(obj + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int a0);
    void func_80183BD4(void) {
        ((void (*)(void))func_8012B370)();
    }


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012CBCC(s32 a0);
extern u8 *func_8012913C(s32 a0);
extern void func_8012C218(void *a0);

void func_80183BF4(s32 a0)
{
    s32 s0 = a0;
    s32 ret;
    u16 val;

    if (*(u16 *)(s0 + 2) == 0) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        func_8012B23C(s0);
        *(s32 *)(s0 + 0x1C) = 1;
        return;
    }

    *(s32 *)(s0 + 0xDC) = *(s32 *)(s0 + 0x14);
    ret = ((s32 (*)(s32))func_8012CBCC)(s0);
    if (ret != 0 && (ret & 0x6000) != 0) {
        s32 cnt = *(s32 *)(s0 + 0x1C) - 1;
        *(s32 *)(s0 + 0x1C) = cnt;
        if (cnt == 0) {
            goto L80183CF4;
        }
        *(s32 *)(s0 + 0x14) = -*(s32 *)(s0 + 0xDC) >> 2;
    }

    val = *(u16 *)(s0 + 0xFC) + 1;
    *(u16 *)(s0 + 0xFC) = val;
    if ((val & 1) != 0) {
        s32 np = (s32)func_8012913C(0x23);
        if (np != 0) {
            *(u16 *)(np + 6) = *(u16 *)(s0 + 6);
            *(u16 *)(np + 0xA) = *(u16 *)(s0 + 0xA);
            {
                u16 t = *(u16 *)(s0 + 0xE);
                *(u32 *)(np + 0x18) = 0;
                *(u32 *)(np + 0x14) = 0;
                *(u32 *)(np + 0x10) = 0;
                *(u16 *)(np + 0x34) = 0x3000;
                *(u16 *)(np + 0xE) = t;
            }
        }
    }

    if (*(s16 *)(s0 + 0xA) < 0x20) {
        return;
    }

L80183CF4:
    func_8012C218((void *)s0);
}



extern void func_80019064(void *a0);

void func_80183D10(void *a0) {

    extern u8 D_801A693C;
    extern void (*D_801A6964[])(void *);
    func_80019064(&D_801A693C);
    D_801A6964[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_80183D68(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_80183DB8(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


extern void func_80183FCC(void);
extern u8 D_801A6944[];

void func_80183DB8(s32 p)
{
    func_80147324(0x451);
    func_801511E0(p);
    func_80154274((s32 *)p, (s32)D_801A6944);
    func_80149020((s32 *)p);
    *(u8 *)(p + 0xDE) = 0x1E;
    *(u8 *)(p + 0xDF) = 0;
    func_80183FCC();
    func_80172630((u8 *)p);
    func_80146CA0((void *)p);
}



/* func_80183E24 @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_80183E24 --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_80183E24.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_80183F78 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_80183FF0` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
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
 *   if (func_80183FF0() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
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
extern s32 func_80183FF0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_80183F78(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_80183E24(s32 param_1)
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
        iVar1 = func_80183FF0();
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
        func_80183F78(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_80183F78 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
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
 *   func_80183F78  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_80183F78(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_80183FCC(void)
{
    extern u8 D_801AA193;
    s32 i = 19;
    u8 *p = &D_801AA193;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_80183FF0(void)
{

    extern u8 D_801AA180[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801AA180;
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



extern void (*D_801A6970[])(void);

void func_80184034(void *a0) {
    D_801A6970[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801AA194 + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_80184264(void*);
extern void func_80184234(s32*);
extern int rand(void);

void func_80184070(int param_1)
{

    extern unsigned char D_801AA194[];
    int iVar3;
    int iVar3b;
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801AA194 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    iVar3b = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_80184264)(iVar5);
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
        ((void (*)(int))func_80184234)(param_1);
    }
}




extern s32 func_80184278(s32 *a0, s32 a1);
extern void func_80184234(s32 *a0);

void func_801841BC(s32 *a0)
{

    extern unsigned char D_801AA194[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801AA194 + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_80184278(a0, table_base) == 0) {
            return;
        }
    }

    func_80184234(a0);
}



















extern void func_80146C3C(void);
void func_80184234(s32 *param_1)
{
    extern u8 D_801AA180[];

    D_801AA180[param_1[0x2c / 4]] = 0;
    ((void (*)(s32 *))func_80146C3C)(param_1);
}


void func_80184264(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_80184278 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_80184278(s32 *a0, s32 a1);
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
s32 func_80184278(s32 *a0, s32 a1) {
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



extern void (*D_801A69A8[])(void);

void func_801842E0(void *a0) {
    D_801A69A8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8018431C(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_801843B8(s32 param_1);

void func_80184368(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_801843B8(param);
    }
}


void func_801843B0(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018451C();

void func_801843B8(s32 param_1) {

    extern u32 *D_801A69A0[];
    extern Blk8 D_801A69BC[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_801A69A0[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_801A69BC[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8018451C(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
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

extern SVECTOR_8017E6D8 D_801AA694[4];
extern struct PW8017E6D8 D_801AA6B4;
extern struct PW8017E6D8 D_801AA6B8;
extern u8 D_801AA6BC, D_801AA6BD, D_801AA6BE, D_801AA6C0, D_801AA6C1, D_801AA6C2;
extern int D_801AA6C4;




void func_8018451C(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801AA694[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801AA6C4 = 0x50000000;
        D_801AA6BC = 0;
        D_801AA6BD = 0;
        D_801AA6BE = 0;
        D_801AA6C0 = 0;
        D_801AA6C1 = 0;
        D_801AA6C2 = 0;
    }
    D_801AA6B4 = h[0];
    D_801AA6B8 = h[1];

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




extern void func_80019064(void *a0);

void func_80184898(void *a0) {

    extern u8 D_801A69DC;
    extern void (*D_801A6A04[])(void *);
    func_80019064(&D_801A69DC);
    D_801A6A04[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8018494C(s32 a0);

void func_801848F0(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8018494C(s0);
    func_80147324(0x92F);
    *(u16 *)(s0 + 0xA) += 0x10;
    func_80146CA0((void *)s0);
}


extern s8 D_801A69E4[];

void func_8018494C(s32 p)
{
    func_80147324(0x451);
    func_80154274((s32 *)p, (s32)D_801A69E4);
    func_80149020((s32 *)p);
    *(u8 *)(p + 0xDE) = 0x1E;
    *(u8 *)(p + 0xDF) = 0;
    func_80183FCC();
    func_80146CA0((void *)p);
}


extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80183FF0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_80184AEC(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);

void func_801849A8(s32 param_1)
{
    s16 buf[4];
    s32 i;
    s32 slot;
    s32 r1;
    s32 r2;
    s32 r3;
    s16 rnd;
    u8 cnt;

    func_80015978(param_1 + 4, (s32 *)buf);
    buf[1] -= 0x40;

    i = 0;
    do {
        slot = func_80183FF0();
        if (slot >= 0) {
            func_80146A6C(0x51, (void *)param_1, buf[0], buf[1], buf[2], slot, 0);

            r1 = rand();
            r2 = rand();
            r3 = rand();
            rnd = (r1 & 3) * 0x400 + (r2 & 3) * 0xfa + (r3 & 3) * 0x44;
            func_80146A6C(0x52, (void *)param_1, 0, -0x20, 0x10, rnd, 0);
        }
        i++;
    } while (i < 3);

    cnt = *(u8 *)(param_1 + 0xde);
    *(u8 *)(param_1 + 0xde) = cnt + 0xff;
    if (cnt == 0) {
        func_80184AEC(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    }
}


extern void func_80147364(u16 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80151664(void);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_80184AEC(s32 param_1)
{
    s16 buf[4];

    func_80147364(4, 0x92F);
    func_80147324(0x930);
    ((void (*)(s32))func_80151664)(param_1);
    func_80015978(param_1 + 4, (s32 *)buf);
    func_8012F568(1, 0xC003, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), 0x10, (s32)buf, (s32)buf);
}



extern void (*D_801A6BB0[])(void);

void func_80184B5C(void *a0) {
    D_801A6BB0[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_8012A828(s32, void *);
extern void func_80184E94(void);


void func_80184B98(s32 param_1) {

    extern u8 D_801A6AB0[];
    extern u8 D_801A7070[];
    s32 v;

    if (((s32 (*)(s32, void *))func_8012C354)(
            param_1, &D_801A6AB0[(*(u16 *)(param_1 + 0x70) & 0xF) * 0x34]) != 0) {
        if ((*(u16 *)(param_1 + 0x70) & 1) == 0) {
            v = func_8012C658(0x1E3, 1, param_1);
            *(s32 *)(param_1 + 0x6C) = v;
            if (v == 0) {
                ((void (*)(s32))func_8012CAE4)(param_1);
            } else {
                *(s16 *)(param_1 + 0x2) = 1;
                *(s32 *)(param_1 + 0xCC) =
                    ((s32 (*)(s32, void *))func_801788B8)(param_1, func_80184E94);
            }
        } else {
            *(s16 *)(param_1 + 0x2) = 5;
            *(u16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);
            func_8012A828(param_1, D_801A7070);
        }
    }
}




s32 func_80184C70(void *a0) {
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


void func_80184C98(void) {
}


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801A6B60;
    void func_80184CA0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801A6B60);
    }



extern s32 func_801789AC(s32);
extern void func_80178D18(void);

void func_80184CCC(s32 a0) {
    if (((int (*)(void))func_801789AC)() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 2;
    }
}


extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80184D0C(void *a0) {

    extern u8 D_801A7080[];
    extern u8 D_801A7188[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0x100) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801A7080);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801A7188);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80184DCC(void *a0) {
    extern u8 D_801A7070[];

    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        if (*(s16 *)((s32)a0 + 0xFE) == 2) {
            func_8002D4C8(0x888, 0);
            func_8012A828((s32)a0, D_801A7070);
        }
        *(s16 *)((s32)a0 + 0x2) = 5;
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


void func_80184E38(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80184E48(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }





s32 func_80184E58(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801AA6DC;
    return !(D_801AA6DC ^ 1);
}


extern void func_800296F8(s32 arg0);
    s32 func_80184E70(s32 arg0) {
        ((void (*)(s32))func_800296F8)(*(s32 *)(arg0 + 0xdc));
    }


extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

/* §71 sibling: identical shape to func_8018F390 (same TU, this file, D_80126B78/RotTransSV/
 * func_80135888/func_8012BDBC/func_80178BF8/func_80172710 idiom) already MATCHED -- only the
 * per-overlay data symbol (D_801A6BCC vs D_801E33F0) differs. §37 asm-label alias avoids the
 * `conflicting types` clash with the fleet's `extern void func_80184E94(void);` used elsewhere
 * in this TU as a state-handler function pointer. */

s32 aF801904E0() __asm__("func_80184E94");

s32 aF801904E0(param_1)
    void *param_1;
{

    extern s32 *D_80126B78;
    extern u8 D_801A6BCC[];
    MATRIX m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    obj = *(s32 *)((s32)param_1 + 0x64);
    m = *(MATRIX *)((u8 *)D_80126B78 + 0x34);

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);

    RotTransSV(D_801A6BCC, sv0, &flag);
    RotTransSV(D_801A6BCC + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x20),
                       *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58),
                       (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_801A75D0[])(void);

void func_80184FE8(void *a0) {
    D_801A75D0[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_801856D0(void);

void func_80185024(void *a0) {

    extern s32 D_801A7328[];
    extern u8 D_801A72C0[];
    extern u8 D_80185B40[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801A72C0);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801A7328[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_801856D0);
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
        func_8012A828((s32)a0, D_80185B40);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_801850F8(void *a0) {
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


void func_80185120(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80185128(void *a0) {

    extern s32 D_801A750C;
    extern s32 D_801A74F8;
    extern s32 D_801A74F4;
    extern s32 D_801A758C;
    extern s32 D_801A7520;
    extern s32 D_801A73EC[];
    extern s32 D_801A7470[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801A750C = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801A74F4 = 0;
                D_801A74F8 = D_801A7470[v0];
            } else {
                D_801A74F8 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801A7470[v0], 1);
                D_801A74F4 = 2;
            }
        } else {
            D_801A750C = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801A74F4 = 0;
            D_801A74F8 = D_801A73EC[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801A7520);
    } else {
        p = &D_801A758C;
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
extern s32 func_80185478(void);

void func_80185274(void *arg0) {

    extern s32 D_801A7328[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801A7328[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801A7328[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80185478() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



extern void func_8012C218(void *a0);
    s32 func_80185394(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_801853C0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_801853D0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_801853E0(void *a0) {

    extern s32 D_801A7328[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801A7328[idx], 1);
}


extern void func_8014ADA8(s32 a0, s32 a1);
    extern s32 D_80126B58;
    void func_80185420(s32 arg0) {
        s32 temp_v0 = *(s32 *)(arg0 + 0xdc);
        ((void (*)(void *, s32))func_8014ADA8)((void *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
    }


extern s16 func_80174764(void);
    s32 func_80185454(void) {
        return ((u32)((s32 (*)(void))func_80174764)() == 1);
    }




extern s32 func_80029178(s32 arg);

s32 func_80185478(void) {

    extern s32 D_801A7328[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801A7328[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801A75F8[])(void);

void func_801854DC(void *a0) {
    D_801A75F8[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80185518(void *a0) {

    extern u8 D_801A72F4[];
    extern u8 D_801A7290[];
    extern u8 D_801A7070[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801A72F4) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801A7290);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801A7070);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801855A0(void *a0) {

    extern u8 D_801A7080[];
    extern u8 D_801A7188[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801A7080);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801A7188);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_80185660 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801A7290, else
 * D_801A7070), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801A7290 / D_801A7070)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_80185660(void *a0) {

    extern u8 D_801A7290[];
    extern u8 D_801A7070[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801A7290);
        } else {
            func_8012A828((s32)a0, D_801A7070);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801A75E8[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

s32 aF8018A224() __asm__("func_801856D0");

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

    RotTransSV(D_801A75E8, sv0, &flag);
    RotTransSV(D_801A75E8 + 8, sv1, &flag);

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





