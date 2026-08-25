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
extern u8 D_80187594;
extern u8 D_80187504;
extern u8 D_801874E0;
extern u8 D_801874BC;
extern u8 D_80187570;
extern u8 D_8018754C;
extern u8 D_80187528;
extern u8 D_80187498;
extern void func_80145934(void);
extern u8 D_80187624;
extern u8 D_80187600;
extern u8 D_801875DC;
extern u8 D_801875B8;
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
extern unsigned char D_80186A1C[];
extern unsigned char D_80186A4C[];
extern unsigned char D_80186A9C[];
extern unsigned char D_80186ACC[];
extern unsigned char D_80186AFC[];
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
extern void (*D_80186B4C[])(void *);
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
extern s32 D_80186C14[];
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
extern u8 D_80186C9C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80186CA4;
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
extern int D_801B9588;
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
extern s32 D_801B958C;
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
extern s32 D_80186CD4;
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
extern void (*D_80186D7C[])(void);
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
extern void (*D_80186DA0[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80186D90;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80186DB4[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80186DC0[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80186DD0[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80186DE8[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80186DD8;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80186DFC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80186E18[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80186E08;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80186E2C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80186E40[])(void);
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
extern s32 D_80186E54;
extern void (*D_80186E7C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80186E5C;
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
extern int (*D_80186EC8[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80186ECC[])(void);
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
extern unsigned short D_80187330[];
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
extern void (*D_80187340[])(void);
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
extern int D_801B95C0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80187368[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80187348;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80187358;
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
extern void (*D_801873A8[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801873B0[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018737C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801873BC[])(void);
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
extern u8 D_8018738C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B95C8;
extern s32 D_801B95D4;
extern s32 D_801B95D8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801873F8[])(s32 *);
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
extern s32 D_801873CC[];
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
extern s32 D_801B95D0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80187648[])(void);
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
extern char D_80187468[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801876EC[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80187840[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018765C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80187848[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018766C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018768C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80187850[])(void);
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
extern void (*D_80187878[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80187884[])(void);
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
extern void (*D_801876F8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80187928;
extern void func_8015D380(s32 a0);
extern unsigned char D_80186A0C[];
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
extern unsigned char D_8018793C[];
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
extern s8 D_80187978[];
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
extern u16 D_801879C0;
extern u16 D_801879C2;
extern u16 D_801879C4;
extern s32 D_801879C8;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801879D0;
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
extern int D_801876DC;
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
extern unsigned int D_80187A54[];
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
extern void (*D_80187B04[])(void);
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
extern u16 D_80187B34[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80187B98;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B95E0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80187BBC[])(void);
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
extern int D_801B9638[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80187C04[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80187BF4;
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
extern char D_801B8D88[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80187C0C[])(void);
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
extern void (*D_80187C60[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80187C28;
extern s16 D_80187C5C;
extern s16 D_80187C5A;
extern s16 D_80187C58;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80187C6C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B9698;
extern u8 D_801B9699;
extern u8 D_801B969A;
extern u8 D_801B969B;
extern u8 D_801B969C;
extern u8 D_801B969D;
extern u8 D_801B969E;
extern u8 D_801B969F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80187C7C[])(void);
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
extern s32 D_801B96D8;
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
extern void (*D_80187CC0[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80187D3C[];
extern s32 D_80187D5C[];
extern u8 D_80187DD8[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80187DF8[];
extern u8 D_80187E18[];
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
extern void (*D_80187EB4[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80187F30[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B8D98;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80187F3C[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80187F44[])(void);
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
extern void (*D_8018800C[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018801C[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018802C[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80188038[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80187F98[];
extern u8   D_80187FAC[];
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
extern void (*D_80188050[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80188058[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80188060[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80188068[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80188070[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80188078[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80188080[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80188134[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018813C[])(void);
extern void func_80169F00(void *a0);
extern char D_801880EC[];
extern char D_801880AC[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80188174[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80188180[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801881C8[])(void);
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
extern void (*D_80188244[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B99F8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80188238[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018827C[];
extern unsigned short D_80188284[];
extern unsigned short D_8018828C[];
extern unsigned char D_801B9A00[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B99F8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188294[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B9B34;
extern M2C_UNK D_801B9B38;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B9AC0;
extern void (*D_801882C4[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B9B3C[];
extern u8 D_801B9B44[];
extern u8 D_801B9AF4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801882CC[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801882E8[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801882F0[])(void);
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
extern void (*D_80188358[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801882FC;
extern u8 D_80188308;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018838C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188394[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801883E8[])(void);
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
extern u16 D_8018841C[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018840C[];
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
extern s32 D_80188438;
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
extern void (*D_801884B0[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801884B8[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801884C0[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801884C8[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801884D0[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801884D8[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801884E4[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801884F0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801884FC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018850C[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018851C[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80188524[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018852C[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80188534[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018853C[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80188544[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018854C[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80188554[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018855C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80188564[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018856C[])(void);
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
extern void (*D_80188574[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018857C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80188584[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018858C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80188594[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018859C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801885A4[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801885AC[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_801885B4[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801885BC[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801885C4[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801885CC[])(void);
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
extern void (*D_80188610[])(void);
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
extern M2C_UNK D_801885D4;
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
extern void (*D_80188640[])(void);
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
extern void (*D_8018867C[])(void);
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
extern void (*D_801886D4[])();
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
extern void (*D_801886E4[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801886EC[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80188854[])();
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
extern void (*D_80188860[])();
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
extern M2C_UNK D_801B8FE0;
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
extern s16 D_801BA978;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801BA278;
extern short D_801BA9EC;
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
extern s32 D_801BA6A4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801BA6CC;
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
extern s16 D_801BA688;
extern s32 func_8017A3B0(void);
extern short D_801BA6C4;
extern short D_801BA6C0;
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
extern s16 D_801BA68C;
extern u16 D_801BA70C;
extern u16 D_801BA70E;
extern u16 D_801BA710;
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
extern s16 D_801BA704;
extern s16 D_801BA706;
extern s16 D_801BA708;
extern s16 D_801BA6FC;
extern s16 D_801BA6FE;
extern s16 D_801BA700;
extern void func_8017B7A8(void);
extern s16 D_801BA71C;
extern s16 D_801BA71E;
extern s16 D_801BA720;
extern s16 D_801BA724;
extern s16 D_801BA726;
extern s16 D_801BA728;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801BA714;
extern short D_801BA716;
extern short D_801BA718;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801BA6AC;
extern SV4 D_801BA6B4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801BA6D4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801BA6D0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80188A3C[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80188A54[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017C24C — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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

void func_8017C24C(s32 arg0)
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


DEFINE_func_8017D12C()  /* dedup: shared engine-core @0x8017D12C (src/shared) */


extern void (*D_80188AD0[])(void);

void func_8017D14C(void *a0) {
    D_80188AD0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D37C(void);
extern void func_800167B8(s32 a0);

s32 func_8017D188(s32 a0) {
    func_8017D37C();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D1CC(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017D3A4(void);

s32 func_8017D1F0(s32 a0) {
    func_8017D3A4();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D230(u8 *a0) {
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
    void func_8017D2AC(void) {
        func_800D1EBC();
    }



extern void (*D_80188AE4[])(void);

void func_8017D2CC(void *a0) {
    D_80188AE4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017D308(s32 a0) {
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
extern char D_80188AF0[];

void func_8017D37C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_80188AF0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D3A4(void) {

    extern s32 D_80188AFC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80188AFC, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D464(void *a0);

void func_8017D3CC(void) {

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
    D_8012695C = 0x44c;
    D_80126968 = 0x31c;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D464, 0);
    func_8012A094((s32)D_80126948);
    func_8017D464(D_80126948);
}



extern void (*D_80188B10[])(void);

void func_8017D464(void *a0) {
    D_80188B10[*(u8 *)((s32)a0 + 0x4)]();
}


typedef struct {
    s16 v[4];
} Blk8_80126940_8017D4A0;

void func_8017D4A0(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80188B14[];
    extern Blk8_80126940_8017D4A0 D_80126940;
    Blk8_80126940_8017D4A0 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80188B14[t];
    }
    sp10 = D_80126940;

    /* Clamp sp10.v[1] */
    if (sp10.v[1] < -0x102) {
        sp10.v[1] = -0x102;
    }

    func_8017D558(a0, sp10.v);
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

void func_8017D558(s32 param_1, s16 *param_2) {
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



extern void (*D_80188B18[])(void);

void func_8017D6F0(void *a0) {
    D_80188B18[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern s32 func_8012AD50(void *a0);

void func_8017D72C(s32 a0) {
    u16 h0;
    u16 h1;

    h0 = *(u16 *)(a0 + 0xFC);
    h1 = *(u16 *)(a0 + 0x70);
    *(s32 *)(a0 + 0xDC) = 0;
    *(s32 *)(a0 + 0xE0) = 0;
    *(s32 *)(a0 + 0xE4) = 0;
    *(u16 *)(a0 + 0x100) = h0;
    *(u16 *)(a0 + 0x102) = h1;
    *(u16 *)(a0 + 0xFE) = (rand() & 0x1F) + (rand() & 0x1F) + 0x3C;
    func_8012AD50((void *)a0);
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017D79C);

INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017D918);

INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017DA50);

INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017DAE4);

extern s32 func_8017DB68(void);

s32 func_8017DB68(void) {
    return 0x7E;
}


extern void (*D_8019EAEC[])(void);
extern void func_8012C0EC(void *a0);
extern void func_801813C0(void *a0);
extern void func_80181490(void *a0);

void func_8017DB70(void *a0) {
    D_8019EAEC[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_801813C0(a0);
        func_80181490(a0);
        func_8012C0EC(a0);
    }
}



// @class: struct
// @stuck: none — MATCH (135/135 ins, match_one confirmed)


extern s32 func_8012C354(s32, s32);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012CAE4(void*);
extern void func_8012B030(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_8017DBE0(s32 param_1) {

    extern Elem52_801B5094 D_8019E8C4[];
    extern u8 D_8019EA5C[];
    extern u8 D_8019E9E4[];
    extern u8 D_801B59B0[];
    extern u16 D_801B5EA4;
    extern u16 D_801B5CFC;
    s32 iVar1;
    u16 uVar2;

    iVar1 = ((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8019E8C4[*(u16 *)(param_1 + 0x70) & 0xf]);
    if (iVar1 != 0) {
        *(u8 *)(param_1 + 0xc0) = 1;
        *(u8 **)(param_1 + 0xbc) = D_8019EA5C;
        *(s32 *)(param_1 + 0xb4) = -0x8ad;
        *(u32 *)(param_1 + 0xc4) |= 2;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x80;
        *(u8 **)(*(s32 *)(param_1 + 0x20) + 0x80) = D_8019E9E4;
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
                func_8012A828(param_1, &D_801B59B0);
            }
            break;
        }
        case 1:
            *(s16 *)(param_1 + 2) = 0x13;
            D_801B5EA4 = 0x28;
            if (((s32)*(s16 *)(param_1 + 0x70) & 0x8000) != 0) {
                *(u32 *)(param_1 + 0xe0) |= 0x400;
            }
            break;
        case 2:
            *(s16 *)(param_1 + 2) = 0x18;
            D_801B5CFC = 0x28;
            break;
        case 3:
            *(s16 *)(param_1 + 2) = 0x1f;
            if (func_8012C658(0x27f, 5, param_1) == 0) {
                ((void (*)(s32))func_8012CAE4)(param_1);
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


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017DDFC);


/* func_8017DE4C — a randomised state entry: seed the timer at 0x1C with
 * rand()%64 + 0x80, park 18000 at 0x48, then nudge the value at 0xE8 by a
 * random 0..1023 in a random direction, push the command list D_801B64D0,
 * set the state word at 0x02 to 3 and clear bit 6 of the flags at 0xE0.
 *
 * §71 sibling-first: func_8018598C (same TU, MATCHed) is the same
 * `if ((rand() & 1) == 0) v = base - off; else v = base + off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);

void func_8017DE4C(s32 param_1) {

    extern u8 D_801B64D0[];
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

    func_8012A828(param_1, D_801B64D0);
    *(s16 *)(param_1 + 2) = 3;
    *(u32 *)(param_1 + 0xE0) &= 0xFFFFFFBF;
}




extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_801817CC(s32 a0);
extern void func_80181954(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8();
extern s32 rand(void);

void func_8017DF14(s32 param_1)
{
    register s32 p __asm__("$17") = param_1;
    s32 r;
    s32 s0;
    register s32 s2 __asm__("$18");

    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 8);
    func_8012B178(p, 0xFFFB0000);

    *(u32 *)(p + 0xE0) &= 0xFFFFFFBF;
    if (func_801817CC(p) == 0) {
        func_80181954(p);
    }

    r = func_8012BDBC(p, 0x300);
    if (r != 0) {
        r = func_8012BCCC(p);
        if (r < 0x100000) {
            *(s16 *)(p + 2) = 4;
            return;
        }
    } else {
        r = func_8012BCCC(p);
        if (r < 0x4000) {
            *(s16 *)(p + 2) = 0xF;
            return;
        }
    }

    if ((*(u32 *)(p + 0xE0) & 0x40) != 0) {
        return;
    }
    if (func_8012BEE8(p) == 0) {
        return;
    }

    s0 = rand() % 1024;
    s2 = *(s32 *)(p + 0xE8);
    if ((rand() & 1) == 0) {
        r = s2 - s0;
    } else {
        r = s2 + s0;
    }
    *(s32 *)(p + 0xE8) = r;
    *(s32 *)(p + 0x1C) = (rand() % 64) + 0x80;
}




extern void func_8012A828(s32 a0, void *a1);

void func_8017E080(s32 param_1)
{

    extern u8 D_801B5A18[];
    func_8012A828(param_1, D_801B5A18);
    *(s32 *)(param_1 + 0x48) = 0x4650;
    *(s16 *)(param_1 + 0x2) = 0x5;
}



extern s32  func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_801819B4(s32 a0, s32 a1);

void func_8017E0C0(s32 p)
{

    extern u16  D_800B99DA;
    extern s32  D_801BA730;
    s32 s1;
    s32 e;

    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B8E4(p, 8);
    func_8012B178(p, 0xFFF90000);

    if ((u32)D_800B99DA % 10 == 0) {
        e = func_80143B6C(p, 0);
        if (e != 0) {
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x18) = 0x5000;
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x1A) = 0x5000;
        }
    }

    func_801817CC(p);

    if (func_8012BDBC(p, 0x300) == 0) {
        *(s16 *)(p + 2) = 6;
        return;
    }
    s1 = func_8012BCCC(p);
    if (s1 >= 0x100000) {
        *(s16 *)(p + 2) = 6;
        return;
    }
    if (s1 < 0x6400) {
        e = func_801819B4(p, 0);
        if (e == 0) {
            *(s16 *)(p + 2) = 8;
            return;
        }
        if (s1 < D_801BA730) {
            register s32 rv __asm__("$2") = 8;
            *(s16 *)(p + 2) = rv;
        }
        return;
    }
    if (0x13FFE < s1 - 0x10001U) {
        return;
    }
    e = func_8012BDBC(p, 0x100);
    if (e == 0) {
        return;
    }
    e = func_801819B4(p, 0);
    if (e == 0) {
        *(s16 *)(p + 2) = 0xA;
        return;
    }
    if (D_801BA730 <= s1) {
        return;
    }
    *(s16 *)(p + 2) = 8;
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017E248);

INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017E27C);

extern void func_8012A828(s32 a0, void *a1);

void func_8017E304(s32 param_1)
{
    extern u8 D_801B5AC0[];
    s32 *s0 = (s32 *)param_1;
    s32 temp;

    func_8012A828(param_1, D_801B5AC0);
    temp = *(s32 *)(param_1 + 0xE0);
    *(s16 *)(param_1 + 2) = 9;
    *(s32 *)(param_1 + 0xE0) = (temp | 2) & ~0x10;
}



extern s32  func_801812A0(s32 a0, s32 a1);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern void func_80183FD0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8017E350(s32 p)
{

    extern u8   D_801B5AC0[];
    extern u8   D_801B63D8[];
    s32 v0;
    s32 s1;

    if (func_801812A0(p, 0x64) == 1) {
        *(u32 *)(p + 0xE0) |= 0x10;
    }

    if (*(s32 *)(p + 0x90) == (s32) D_801B5AC0) {
        if (*(s32 *)(p + 0x94) == 0xB) {
            func_80183FD0(p, 0x8C0);
        }
    } else {
        if (*(s32 *)(p + 0x94) == 8) {
            func_80183FD0(p, 0x8C0);
        }
    }

    if (*(u16 *)(p + 0x72) & 0x4000) {
        if (func_8012BDBC(p, 0x300) == 0) {
            v0 = 6;
            goto set_and_return;
        }
        s1 = func_8012BCCC(p);
        if (s1 >= 0x100000) {
            v0 = 2;
            goto set_and_return;
        }
        if (s1 < 0x4000) {
            func_8012A828(p, D_801B63D8);
            *(u32 *)(p + 0xE0) &= ~0x10;
            return;
        } else if (s1 < 0x6400) {
            if ((*(s32 *)(p + 0xE0) & 0x10) == 0) {
                func_8012A828(p, D_801B63D8);
                return;
            }
            func_8012A828(p, D_801B5AC0);
            *(u32 *)(p + 0xE0) &= ~0x10;
            return;
        } else {
            v0 = 4;
            goto set_and_return;
        }
    }
    return;

set_and_return:
    *(s16 *)(p + 2) = v0;
}


extern void func_8012A828(s32 a0, void *a1);
extern u8   D_801B63D8[];

void func_8017E48C(s32 p) {
    func_8012A828(p, D_801B63D8);
    *(u16 *)(p + 2) = 0xB;
    *(u16 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x10) *= 2;
    *(s32 *)(p + 0x18) *= 2;
}



extern s32  func_801812A0(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_80183FD0(s32 a0, s32 a1);
extern s32  func_8012BEE8();

void func_8017E4E0(s32 p)
{

    extern u16  D_80126B96;
    extern u16  D_800B99DA;
    s32 e;

    if (func_801812A0(p, 0x64) == 1) {
        D_80126B96 = 4;
    }

    *(s32 *)(p + 0x10) = *(s32 *)(p + 0x10) * 31 / 32;
    *(s32 *)(p + 0x18) = *(s32 *)(p + 0x18) * 31 / 32;
    func_801817CC(p);

    if ((u32)D_800B99DA % 6 == 0) {
        e = func_80143B6C(p, 0);
        if (e != 0) {
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x18) = 0x5000;
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x1A) = 0x5000;
        }
    }

    if (*(s32 *)(p + 0x94) == 8) {
        func_80183FD0(p, 0x8C0);
    }

    if (*(u16 *)(p + 0x34) == 0) {
        if (*(s32 *)(p + 0x94) == 0xE) {
            *(u16 *)(p + 0x98) = 0;
            *(s32 *)(p + 0x1C) = 0x1E;
            *(u16 *)(p + 0x34) += 1;
        }
    } else {
        if (func_8012BEE8(p) != 0) {
            *(s16 *)(p + 2) = 6;
        }
    }
}


extern s32 D_801B5D08;
extern void func_8012A828(s32 a0, void *a1);

void func_8017E630(arg0)
void *arg0;
{
    extern void func_8012A828(s32, void*);
    extern s32 D_801B5D08;

    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801B5D08);
    *(s16 *)((u8 *)arg0 + 0x2) = 0xd;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x28;
}


void func_8017E670(s32 p) {
    extern void func_8012F214(s32, s32, s32);
    extern s32  func_801833F4(void *a0, s32 a1, s32 a2);
    extern s32  func_8012BEE8();
    extern u8   D_8019E994[];
    extern s32  D_80126B9C;
    s32 buf10[2];

    ((void (*)(s32, void *, void *))func_8012F214)(p, D_8019E994, buf10);
    if (func_8012BEE8(p) != 0 && (D_80126B9C & 2) == 0) {
        *(u16 *)(p + 2) = 4;
    } else if (func_801833F4(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x400) == 0) {
        *(u16 *)(p + 2) = 4;
    }
}



extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_80013350(s32 a0, void *a1);


void func_8017E6EC(s32 p)
{

    extern u8 D_801A4EAC;
    extern u8 D_801A16E8;
    extern u8 D_801B5A18[];
    extern u8 D_801B6918[];
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
        func_8012C218((void *)*(s32 *)(p + 0xCC));
        *(s32 *)(p + 0xCC) = 0;
        func_8001C924(*(s32 *)(p + 0x20), &D_801A4EAC);
        func_8012A828(p, D_801B5A18);
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
        func_8012C218((void *)*(s32 *)(p + 0xD0));
        *(s32 *)(p + 0xD0) = 0;
        func_8001C924(*(s32 *)(p + 0x20), &D_801A16E8);
        func_8012A828(p, D_801B5A18);
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

    func_801817CC(p);

    r = ((s32(*)(s32, s32))func_80013350)(p + 4, s1 + 4);
    if (r < 0x900) {
        if (*(u16 *)(p + 0x34) == 0) {
            func_8012A828(p, D_801B6918);
        }
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
    }
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017E96C);


extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern void func_80142414(s32 a0, s16 a1);

void func_8017E9B4(s32 p) {
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

void func_8017EA74(s32 param_1)
{

    extern u8 D_801B6098[];
    func_8012A828(param_1, D_801B6098);
    *(s32 *)(param_1 + 0x48) = 0x4650;
    *(s16 *)(param_1 + 0x2) = 0x12;
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017EAB4;

extern s32  func_8012BCCC(s32 a0);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern s32  func_8012B8A4(s16 *a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_80181954(s32 a0);
extern s32  rand(void);

void func_8017EAB4(s32 p)
{
    s32 v;
    s32 r;
    s32 t;

    v = func_8012BCCC(p);
    if (v > 0x144000) {
        *(s16 *)(p + 2) = 0x13;
        return;
    }

    if (v > 0xC4000) {
        if ((*(u32 *)(p + 0xE0) & 0x40) == 0) {
            r = func_8012B8E4(p, 8);
            *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += r;
        }
    } else {
        if ((u32)(v - 0x24000) <= 0xA0000) {
            *(s16 *)(p + 2) = 0x15;
            return;
        }

        if ((*(u32 *)(p + 0xE0) & 0x40) == 0) {
            if (func_8012BEE8(p) != 0) {
                t = func_8012B8A4((s16 *)p);
                *(u32 *)(p + 0xE8) = (t + 0x800) & 0xFFF;
                r = rand();
                *(s32 *)(p + 0x1C) = r % 0x40 + 0x40;
            }
        }

        r = func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 8);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += r;
    }

    func_8012B178(p, 0xFFF9C000);
    *(u32 *)(p + 0xE0) &= 0xFFFFFFBF;
    if (func_801817CC(p) == 0) {
        func_80181954(p);
    }
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017EC18);

typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017EC6C;

extern s32  func_8012BCCC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);


void func_8017EC6C(s32 p)
{

    extern u8 D_801B5D60[];
    extern u8 D_801B6098[];
    extern u8 D_801B6150[];
    s32 v;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801B5D60);
            *(u16 *)(p + 0x34) += 1;
        }
        break;
    case 1:
        v = func_8012BCCC(p);
        if (v > 0x24000) {
            break;
        }

        if ((*(u32 *)(p + 0xE0) & 0x400) == 0) {
            *(s16 *)(p + 2) = 0x15;
        } else {
            func_8012A828(p, D_801B6150);
            *(u16 *)(p + 0x34) += 1;
        }
        break;
    case 2:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801B6098);
            *(s32 *)(p + 0x48) = 0x4650;
            *(s16 *)(p + 0x2) = 0x12;
        }
        break;
    }
}


extern void func_8012A828(s32 a0, void *a1);

void func_8017ED7C(s32 a0)
{
    extern u8 D_801B5D60[];

    *(s16 *)(a0 + 2) = 0x16;
    if ((*(u32 *)(a0 + 0xE0) & 0x400) == 0) {
        func_8012A828(a0, D_801B5D60);
        *(s16 *)(a0 + 0x34) = 4;
        *(s32 *)(a0 + 0x1C) = 0xF;
    } else {
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x34) = 0;
    }
}


#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_801842E0(s32, s32);
extern void func_8018348C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_80183FD0(s32 a0, s32 a1);


void func_8017EDE4(s32 p)
{

    extern u8 D_8019E78C[];
    extern u8 D_8019E9A4[];
    extern u8 D_801B5D60[];
    extern u8 D_801B5DC8[];
    extern u8 D_801B6098[];
    extern u8 D_801B6150[];
    s16 v18[4];   /* sp+0x18 */
    s32 mat[8];   /* sp+0x20 - MATRIX: 3x3 s16 + pad, 3 s32 at +0x14 */
    s32 s0;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        s0 = func_8012B8E4(p, 8);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += s0;
        if (func_8012BEE8(p) == 0 && s0 != 0) {
            return;
        }
        func_8012A828(p, D_8019E78C);
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;

    case 1:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801B5DC8);
            *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        }
        break;

    case 2:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            if (func_8012E778(p, 0xA000C8) == 0) {
                *(s16 *)(p + 2) = 0x14;
                if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                    *(u16 *)(p + 0x34) = 1;
                    func_8012A828(p, D_801B5D60);
                } else {
                    *(u16 *)(p + 0x34) = 0;
                    func_8012A828(p, D_8019E78C);
                }
                return;
            }
            s0 = func_8012BCCC(p);
            if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                if (0x63FFF < s0) {
                    *(s16 *)(p + 2) = 0x14;
                    if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                        *(u16 *)(p + 0x34) = 1;
                        func_8012A828(p, D_801B5D60);
                    } else {
                        *(u16 *)(p + 0x34) = 0;
                        func_8012A828(p, D_8019E78C);
                    }
                    return;
                }
            } else if (0xA0000 < (u32)(s0 - 0x24000)) {
                func_8012A828(p, D_801B6150);
                *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
                break;
            }
        }

        if (*(s32 *)(p + 0x94) < 8) {
            *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B8E4(p, 8);
        }
        if (*(s32 *)(p + 0x94) != 7) {
            return;
        }

        func_8012EA90(p, 0xB, mat);
        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_8019E9A4, v18);
        ((void (*)(s32, void *))func_801842E0)(p, v18);

        /* gte_SetRotMatrix */
        __asm__ __volatile__(
            "lw $12, 0( %0 );"
            "lw $13, 4( %0 );"
            "ctc2 $12, $0;"
            "ctc2 $13, $1;"
            "lw $12, 8( %0 );"
            "lw $13, 12( %0 );"
            "lw $14, 16( %0 );"
            "ctc2 $12, $2;"
            "ctc2 $13, $3;"
            "ctc2 $14, $4"
            : : "r"(*(s32 *)(p + 0x20) + 0x34) : "$12", "$13", "$14");

        /* column 0: gte_ldclmv / gte_rtir / gte_stclmv */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat) : "$12", "$13", "$14", "memory");

        /* column 1 */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat + 1) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat + 1) : "$12", "$13", "$14", "memory");

        /* column 2 */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat + 2) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat + 2) : "$12", "$13", "$14", "memory");

        /* gte_SetTransMatrix */
        __asm__ __volatile__(
            "lw $12, 20( %0 );"
            "lw $13, 24( %0 );"
            "ctc2 $12, $5;"
            "lw $14, 28( %0 );"
            "ctc2 $13, $6;"
            "ctc2 $14, $7"
            : : "r"(*(s32 *)(p + 0x20) + 0x34) : "$12", "$13", "$14");

        /* gte_ldlvl / gte_rt / gte_stlvnl on the translation vector */
        __asm__ __volatile__(
            "lhu $13, 4( %0 );"
            "lhu $12, 0( %0 );"
            "sll $13, $13, 16;"
            "or $12, $12, $13;"
            "mtc2 $12, $0;"
            "lwc2 $1, 8( %0 )"
            : : "r"(&mat[5]) : "$12", "$13");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 0, 0, 0");
        __asm__ __volatile__(
            "swc2 $25, 0( %0 );"
            "swc2 $26, 4( %0 );"
            "swc2 $27, 8( %0 )"
            : : "r"(&mat[5]) : "memory");

        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_8019E9A4, v18);
        func_8018348C(p, v18, 0x282, 2, -0x120, 0);
        func_8018348C(p, v18, 0x282, 2, 0, 0);
        func_8018348C(p, v18, 0x282, 2, 0x120, 0);
        func_80183FD0(p, 0x8BD);
        return;

    case 3:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801B6098);
            *(s32 *)(p + 0x48) = 0x4650;
            *(s16 *)(p + 2) = 0x12;
        }
        return;

    case 4:
        if (func_8012BEE8(p) != 0) {
            func_8012A828(p, D_801B5DC8);
            *(u16 *)(p + 0x34) = 2;
        }
        break;
    }
}



/* Host TU: src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c
 * Insertion point replaces the INCLUDE_ASM at line 6996, in scope after the
 * decl block that begins at line 6786 (#include "common.h"). That block
 * ALREADY declares (in scope, do not redeclare):
 *   extern s32  func_8012BEE8();                       (line 6789)
 *   extern void func_8012A828(s32 a0, void *a1);        (line 6790)
 *   extern u8   D_801B6098[];                           (line 6803)
 * and elsewhere earlier in the SAME TU (still in scope, file-scope extern):
 *   extern void func_80013350(s32 a0, void *a1);        (line 6647)
 *     -- loose prototype (real callee takes/returns s32,s32->s32); per
 *        cookbook §161c do NOT add a conflicting extern here, cast at the
 *        call site instead (matches the TU's own sibling func_8018457C).
 * New decls needed for this function (not yet declared in this TU's scope
 * at the insertion point):
 *   func_8012B6D4, func_8012B608, func_8012B178, func_801817CC,
 *   func_8012C218, func_8001C924, D_801B6918[], D_801A58C0[]
 * (func_8012B6D4/B608/B178/8765C signatures copied verbatim from this TU's
 * other declarations of the same symbols, e.g. lines 6643-6646/7043-7045;
 * func_8012C218/func_8001C924 copied from lines 6639-6640.)
 */

extern s32  func_8012BEE8();
extern void func_8012A828(s32 a0, void *a1);
extern void func_80013350(s32 a0, void *a1); /* loose proto, real TU decl (line 6647); cast at call site per §161c */
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);


void func_8017F264(s32 p)
{

    extern u8 D_801B6918[];
    extern u8 D_801B6098[];
    extern u8 D_801A58C0[];
    s32 s1;
    s32 r;

    if (*(u16 *)(p + 0x34) == 0) {
        s1 = *(s32 *)(p + 0xCC);
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != *(s16 *)(p + 0xEC) ||
            func_8012BEE8(p) != 0) {
            *(u16 *)(p + 2) = 0x23;
            *(u32 *)(p + 0xE0) |= 0x800;
            return;
        }

        r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s1 + 4));
        *(s32 *)(p + 0xE8) = r;

        r = func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 8);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r;

        func_8012B178(p, 0xFFF8D000);
        func_801817CC(p);

        r = ((s32 (*)(s32, s32))func_80013350)(p + 4, s1 + 4);
        if (r < 0x900) {
            *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
            func_8012A828(p, D_801B6918);
        }
    } else {
        if (*(s16 *)(p + 0x98) != 0) {
            return;
        }
        func_8012C218((void *)*(s32 *)(p + 0xCC));
        *(s32 *)(p + 0xCC) = 0;
        func_8001C924(*(s32 *)(p + 0x20), D_801A58C0);
        func_8012A828(p, D_801B6098);
        *(s32 *)(p + 0x48) = 0x4650;
        *(s16 *)(p + 2) = 0x12;
        *(u32 *)(p + 0xE0) &= ~4;
    }
}



/* func_8017F3D8 — randomised state entry (state word 0x19):
 * set the state at 0x02, push command list D_801B5FD0, seed the timer at
 * 0x1C with rand()%64 + 0x80, nudge the value at 0xE8 by a random 0..1023
 * in a random direction, then park 18000 at 0x48.
 *
 * §71 sibling-first: func_80183CDC / func_8018598C (same TU, MATCHed) are the
 * same `if ((rand() & 1) != 0) v = base + off; else v = base - off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);

void func_8017F3D8(s32 param_1) {

    extern u8 D_801B5FD0[];
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    *(s16 *)(param_1 + 2) = 0x19;
    func_8012A828(param_1, D_801B5FD0);

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
extern s32  func_801817CC(s32 a0);
extern void func_80181954(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_801833F4(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */

void func_8017F490(s32 p) {

    extern u8 D_8019E994[];
    s32 buf10[2];
    s32 r_b608;

    r_b608 = func_8012B608((s32)*(s16 *)(*(s32 *)(p + 0x20) + 0x12),
                           *(s32 *)(p + 0xE8), 0x10);
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r_b608;
    func_8012B178(p, 0xFFFBD000);

    *(u32 *)(p + 0xE0) &= 0xFFFFFFBF;
    if (func_801817CC(p) == 0) {
        func_80181954(p);
    }

    ((void (*)(s32, void *, void *))func_8012F214)(p, D_8019E994, buf10);
    if (func_801833F4(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0 &&
        func_8012BCCC(p) < 0x64000) {
        *(u16 *)(p + 2) = 0x1C;
    } else if (func_8012BEE8(p) != 0) {
        *(u16 *)(p + 2) = 0x1A;
    }
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017F570);

INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017F5B0);


extern void func_8012A828(s32, void*);
    extern short aD801B5B88_8017F630 __asm__("D_801B5B88");
    void func_8017F630(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x1D;
        *(short *)((char *)a0 + 0x34) = 0;
        *(int *)((char *)a0 + 0x1c) = 0xf;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (int)&aD801B5B88_8017F630);
    }



// @class: schedule
// @stuck: none — MATCH (181 ins, relocation-masked)








extern s32 func_8012BEE8();
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_801834F0(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8018348C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_80183FD0(s32 a0, s32 a1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_801833F4(void *a0, s32 a1, s32 a2);
extern s32 rand(void);


void func_8017F668(s32 p) {

    extern u8 D_801B5C00[];
    extern u8 D_801B5B88[];
    extern u8 D_8019E9AC[];
    extern u8 D_8019E9BC[];
    extern u8 D_8019E994[];
    s32 buf58[8];   /* auStack_58  sp+0x18 (0x20) */
    s32 g38[4];     /* uStack_38/34, iStack_30 sp+0x38 (0x10) */
    u16 g28[4];     /* uStack_28/26/24 sp+0x48 (0x08) */
    u16 out[4];     /* func_801834F0 output sp+0x50 (0x08) */
    s32 buf18[2];   /* auStack_18  sp+0x58 (0x08) */
    s32 i;
    s32 e;

    if (*(u16 *)(p + 0x34) == 0) {
        if (func_8012BEE8() == 0) return;
        func_8012A828(p, D_801B5C00);
        *(u16 *)(p + 0x34) += 1;
    }
    if (*(s32 *)(p + 0x94) < 0xe) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B8E4(p, 8);
    }
    if (*(s32 *)(p + 0x94) == 0xe) {
        func_801834F0(p, D_8019E9AC, out, 0xb);
        func_8018348C(p, out, 0x282, 0, 0, 0);
        e = func_80132EF4(p, 0x22);
        if (e != 0) {
            *(u16 *)(e + 0x34) = 0x7002;
            *(u16 *)(e + 6) = out[0];
            *(u16 *)(e + 0xa) = out[1];
            *(u16 *)(e + 0xe) = out[2];
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc006;
        }
        g28[0] = 0x40;
        g28[1] = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
        g28[2] = 0;
        ((void (*)(void *, void *))func_80049CAC)(g28, buf58);
        i = 0;
        do {
            e = func_80132EF4(p, 0x22);
            if (e != 0) {
                g38[1] = 0;
                g38[0] = 0;
                g38[2] = (rand() % 5 + 4) << 16;
                ((void (*)(void *, void *, s32))func_800484EC)(buf58, g38, e + 0x10);
                *(u16 *)(e + 0x34) = ((rand() % 2 + 2) << 12) | 1;
                *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc006;
                func_801834F0(p, D_8019E9BC + i * 8, out, 0xb);
                *(u16 *)(e + 6) = out[0];
                *(u16 *)(e + 0xa) = out[1];
                *(u16 *)(e + 0xe) = out[2];
            }
            i++;
        } while (i < 5);
        func_80183FD0(p, 0x8be);
    }
    if (*(u16 *)(p + 0x72) & 0x4000) {
        ((void (*)(s32, void *, void *))func_8012F214)(p, D_8019E994, buf18);
        if (0x63fff < func_8012BCCC(p) ||
            func_801833F4(buf18, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) == 0) {
            *(u16 *)(p + 2) = 0x1b;
            func_8012A828(p, D_801B5B88);
            *(s32 *)(p + 0x1c) = 0x20;
        }
    }
}



/* §160g sibling search: callee set {func_8012BEE8, func_8012B6D4, func_8012B608,
 * func_8012B178, func_801817CC, func_80013350, func_8012A828, func_8012C218,
 * func_8001C924} matches the ALREADY-MATCHED func_8018457C in this exact TU
 * (src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c, lines 6654-6733) almost verbatim --
 * that function's case 0 (the s1=*(p+0xCC) null/field-0x36-vs-0xEC/func_8012BEE8
 * mismatch guard, then func_8012B6D4 + the func_8012B608/func_8012B178/
 * func_801817CC/func_80013350 tail with the same D_801B6918 transition) is a
 * structural template for our "state==0" branch. The "state!=0" branch's tail
 * (set +2=0x1D, +0x34=0, +0x1C=0xF, call func_8012A828) is verbatim the body of
 * the tiny already-MATCHED func_801854C0 a few lines above ours in the same TU
 * (it uses a function-pointer cast only because ITS param is `short *`; ours is
 * already `s32 param_1` so a plain call suffices, mirroring func_801854F8's own
 * plain `func_8012A828(p, D_801B5B88);` two lines before our INCLUDE_ASM slot).
 * The `*(u32*)(p+0xE0) &= 0xFFFFFFFB;` mask is byte-identical to func_8018457C's
 * case 1 mask. All extern decls below are copied verbatim from these matched
 * siblings' own decl blocks (same TU, same file-scope conventions).
 */

extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);


void func_8017F93C(s32 param_1)
{

    extern u8 D_801B6918[];
    extern u8 D_801A54A8;
    extern u8 D_801B5B88[];
    s32 s1;
    s32 uVar4;
    s32 sVar1;
    s32 r;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        s1 = *(s32 *)(param_1 + 0xCC);
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != *(s16 *)(param_1 + 0xEC) ||
            func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 2) = 0x23;
            *(u32 *)(param_1 + 0xE0) |= 0x800;
            return;
        }

        uVar4 = func_8012B6D4((s16 *)(param_1 + 4), (s16 *)(s1 + 4));
        *(s32 *)(param_1 + 0xE8) = uVar4;

        sVar1 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), uVar4, 8);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + sVar1;

        func_8012B178(param_1, 0xFFF8D000);
        func_801817CC(param_1);

        r = ((s32 (*)(s32, s32))func_80013350)(param_1 + 4, s1 + 4);
        if (r < 0x900) {
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            func_8012A828(param_1, D_801B6918);
        }
        return;
    }

    if (*(s16 *)(param_1 + 0x98) != 0) {
        return;
    }
    func_8012C218((void *)*(s32 *)(param_1 + 0xCC));
    *(s32 *)(param_1 + 0xCC) = 0;
    func_8001C924(*(s32 *)(param_1 + 0x20), &D_801A54A8);
    *(s16 *)(param_1 + 2) = 0x1D;
    *(u16 *)(param_1 + 0x34) = 0;
    *(s32 *)(param_1 + 0x1C) = 0xF;
    func_8012A828(param_1, D_801B5B88);
    *(u32 *)(param_1 + 0xE0) &= 0xFFFFFFFB;
}


INCLUDE_ASM("asm/ov_SC06_020/nonmatchings/ov_SC06_020_jr_8017C24C", func_8017FAB4);



/* holds a pointer value */

extern int  rand(void);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_80181954(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_801834F0(s32, void*, void*, s32);
extern void func_8018348C(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);

void func_8017FAFC(s32 param_1) {

    extern u16       D_800B99DA;
    extern u8        D_8019E9B4;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    u8  auStack_38[8];
    s16 sp20[3];
    u8  auStack_28[8];
    register StructB58_8017FAFC *b58 __asm__("$20") = &(*(StructB58_8017FAFC *)&D_80126B58);   /* $s4 */
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
    if (func_801817CC(param_1) == 0) {
        func_80181954(param_1);
        sp20[1] = 0;
        sp20[0] = 0;
        sp20[2] = -0x100;
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34,
                                                 (s32)sp20, (s32)psVar7);
    }

    if (((u32)D_800B99DA % 0x28 == 0) && ((*(u32 *)(param_1 + 0xe0) & 0x80) == 0)) {
        ((void (*)(s32, s32, s32, s32))func_801834F0)(param_1, (s32)&D_8019E9B4, (s32)auStack_38, 0xb);
        ((void (*)(s32, s32, s32, s32, s32, s32))func_8018348C)(param_1, (s32)auStack_38, 0x282, 1, 0, 0);
        *(u32 *)(param_1 + 0xe0) |= 0x80;
    }

    if (func_80013478(param_1 + 4, (s32)psVar7) < 0x400) {
        *(s32 *)(param_1 + 0x1c) = 0;
    }
}



/* Sibling-search hit (cookbook §160g): src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c:6654
 * func_8018457C (already banked) is the SAME structural family — its case 0 (the
 * s0==0||mismatch||func_8012BEE8() guard + call_b6d4/LAB_80184738 tail) and case 3
 * (func_8012C218/func_8001C924/func_8012A828 teardown chain) are literally this
 * function's two branches with different field offsets/globals. Types/signatures below
 * mirror that TU's existing extern decls exactly (host TU already declares all of
 * these at file scope before this insertion point, e.g. lines 6639-6652, 7203-7213).
 */

extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801817CC(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);


void func_8017FD9C(s32 p)
{

    extern u8 D_801B6918[];
    extern u8 D_801A5CC4;
    extern u8 D_801B5F18[];
    s32 s0;
    s32 r;

    if (*(u16 *)(p + 0x34) == 0) {
        s0 = *(s32 *)(p + 0xCC);
        if (s0 == 0 || *(s16 *)(s0 + 0x36) != *(s16 *)(p + 0xEC) ||
            func_8012BEE8(p) != 0) {
            *(u16 *)(p + 2) = 0x23;
            *(u32 *)(p + 0xE0) |= 0x800;
        } else {
            r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s0 + 4));
            *(s32 *)(p + 0xE8) = r;

            r = func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 8);
            *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r;

            func_8012B178(p, 0xFFF8D000);

            func_801817CC(p);

            r = ((s32 (*)(s32, s32))func_80013350)(p + 4, s0 + 4);
            if (r < 0x900) {
                *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
                func_8012A828(p, D_801B6918);
            }
        }
    } else {
        if (*(s16 *)(p + 0x98) == 0) {
            func_8012C218((void *)*(s32 *)(p + 0xCC));
            *(s32 *)(p + 0xCC) = 0;
            func_8001C924(*(s32 *)(p + 0x20), &D_801A5CC4);
            *(u16 *)(p + 2) = 0x20;
            func_8012A828(p, D_801B5F18);
            *(s32 *)(p + 0x48) = 0x4650;
            *(s32 *)(p + 0x1C) = 0;
            *(s32 *)(p + 0xE4) = 0;
            *(u32 *)(p + 0xE0) &= 0xFFFFFFFB;
        }
    }
}


extern void func_801811A8(void);
    void func_8017FF18(s32 arg0) {
        if (*(s16 *)(arg0 + 0x98) == 0) {
            ((void (*)(void))func_801811A8)();
        }
    }



/* Sibling-search (§160g) findings, kept for the integration note:
 * - func_8018598C (same TU, ov_SC06_018_jr_8017C24C.c:7215, MATCHED/banked already) shares
 *   func_8012BEE8/func_8012B608/func_8012B178/func_801817CC/func_80181954 with identical
 *   argument shapes -- confirms every extern signature below except func_8012B8A4/func_8012EFB8.
 * - func_8018457C (same TU, :6654) uses the SAME func_8012B608(*(s16*)(*(s32*)(p+0x20)+0x12),
 *   *(s32*)(p+0xE8), 8) / field += pattern and the SAME func_8012B178(p, 0xFFF8D000) magic
 *   literal -- confirms the b608/b178 idiom byte-for-byte.
 * - func_8012B8A4 canonical decl (many matched TUs): extern s32 func_8012B8A4(s16 *a0);
 * - func_8012EFB8's byte-true body (src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c:1106) is
 *   `s32 func_8012EFB8(void *param_1, void *param_2)` -- TWO pointers, s32 return -- but the
 *   fleet-canon extern in THIS TU (line 335: `extern void func_8012EFB8(s32 a0);`, file scope,
 *   already in effect before this function) conflicts on both arity and return axis. Per §161c,
 *   do NOT add a second extern; cast the existing symbol at the call site instead.
 * - Ghidra seed at .run/ghidra_c/func_8017FF48.c confirms the callee set and control flow
 *   (verified address-matched: FUN_80185dd8, calls FUN_8012be54/bee8/b8a4/b608/b178/8765c/877e4/
 *   efb8/c098) -- used only to cross-check, not copied verbatim (Ghidra's decompile is
 *   -O0-shaped and not reg-alloc-accurate).
 *
 * INTEGRATION SURFACE (for the banking step): every extern below is checked against this TU's
 * (ov_SC06_018_jr_8017C24C.c) own file-scope decls already in effect before line 7301:
 *   func_8012BE54 -> void(s32) EXACT match (host decl at :4212/:5193; cast to (s32(*)(s32)) at
 *     the one call site, mirroring the host's own existing call-site casts at :4363/:5291).
 *   func_8012BEE8 -> s32(s32) EXACT match (:7203).
 *   func_8012B608 -> s32(s32,s32,s32) EXACT match (:6644).
 *   func_8012B178 -> void(s32,s32) EXACT match (:6645/:7044/:7207).
 *   func_801817CC -> s32(s32) EXACT match (:6646/:7045/:7208).
 *   func_80181954 -> void(s32) EXACT match (:7046/:7209).
 *   func_8012EFB8 -> declared void(s32) to match the host's loose file-scope decl (:335); the
 *     real (void*,void*)->s32 body is invoked through a cast at the call site (§161c), so no
 *     second/conflicting extern is introduced.
 *   func_8012C098 -> void(void*) EXACT match (:5603).
 *   func_8012B8A4 -> NOT declared anywhere in this TU before this point; the draft's
 *     `extern s32 func_8012B8A4(s16 *a0);` is the canonical signature used fleet-wide and
 *     introduces no conflict.
 * Net: zero declaration conflicts predicted against the host TU.
 */

extern void func_8012BE54(s32 a0); /* host TU decl is void (§161c-style loose proto); cast at call site */
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_801817CC(s32 a0);
extern void func_80181954(s32 a0);
extern void func_8012EFB8(s32 a0); /* loose decl, real body is (void*,void*)->s32; call via cast */
extern void func_8012C098(void *param_1);

void func_8017FF48(s32 a0) {
    s32 r;
    s16 vecA[4];
    s16 vecB[4];
    s32 x, z;

    if ((*(u32 *)(a0 + 0xE0) & 0x40) == 0) {
        s32 ret = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret <= 0x63FFF) {
            if (func_8012BEE8(a0) != 0) {
                s32 t;
                s32 rr;

                t = func_8012B8A4((s16 *)a0);
                *(u32 *)(a0 + 0xE8) = (t + 0x800) & 0xFFF;
                rr = rand();
                *(s32 *)(a0 + 0x1C) = rr % 0x40 + 0x40;
            }
        }
    }

    r = func_8012B608((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12), *(s32 *)(a0 + 0xE8), 8);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;

    *(u32 *)(a0 + 0xE0) &= 0xFFFFFFBF;
    func_8012B178(a0, 0xFFF8D000);

    if (func_801817CC(a0) == 0) {
        func_80181954(a0);
    }

    vecA[0] = *(s16 *)(a0 + 0x6);
    vecA[1] = *(s16 *)(a0 + 0xA);
    vecA[2] = *(s16 *)(a0 + 0xE);
    ((s32 (*)(void *, void *))func_8012EFB8)(vecA, vecB);

    x = vecB[0];
    if (x < 0) {
        x = -x;
    }
    if (x < 0x105) {
        z = vecB[1];
        if (z >= 0) {
            if (z < 0xC9) {
                /* NEW LEVER (not yet in cookbook): a bare if/else-with-return here compiles
                 * to a value-converge merge (ONE shared `slti`+`bne` fed by both signs of z,
                 * ~91 ins) instead of the target's genuine PER-BRANCH duplicate compare
                 * (96 ins: `bltz`+`slti`+`beqz`+`j` in this arm, `negu`+`slti`+`bnez` in the
                 * else arm). A zero-emission `__asm__ __volatile__("":::"memory")` right
                 * before this `return` is a scheduling/combine barrier that blocks whatever
                 * RTL-level pass performs that merge, without adding a single byte itself --
                 * the compiled result is byte-exact target. Byte-proven via 9 probe variants
                 * (assignment-abs, ternary-condition, if/else, 2-independent-ifs, goto-labeled
                 * return) that ALL either fully merged or left a redundant extra sign-retest;
                 * only this barrier reproduces the target exactly. See match_one MATCH 96/96.
                 */
                __asm__ __volatile__("" ::: "memory");
                return;
            }
        } else {
            if (-z < 0xC9) {
                return;
            }
        }
    }
    func_8012C098((void *)a0);
}




/* func_801800C8 (ov_SC06_018_jr_8017C24C) — MATCH 198/198, relocation-masked.
 * @class: regalloc-copy + schedule
 * @stuck: none. Three load-bearing idioms:
 *  1. ONE shared scratch `t` for all three `sll 16` compares. Three separate temps let
 *     local-alloc TIE the short temp to `iVar1` (no `addu $s1,$v0,$zero` at all, 197 ins);
 *     the shared `t` conflicts with `iVar1` so the copy survives.
 *  2. `t = t << 16; if (t <= 0)` instead of `if ((s16)t <= 0)` at the FIRST site only.
 *     With the natural cast the shift lands in a fresh pseudo, so local-alloc's
 *     `optimize_reg_copy_1` (local-alloc.c:700, called at :1007 — MIPS never defines
 *     SMALL_REGISTER_CLASSES so pins cannot block it) finds `t` dying there and rewrites the
 *     use to the copy's destination -> `sll $v0,$s1,16`. Shifting IN PLACE makes the insn
 *     SET `t`, which trips the `reg_set_p (src, p)` break in the forward scan (and flow emits
 *     no REG_DEAD when a reg is set in the insn that last uses it, cookbook §45 Lever B)
 *     -> the scan aborts, the use stays on `$v0`: `sll $v0,$v0,16`. Cookbook §25 triage tell.
 *     Sites 2 and 3 (0xFE / 0x76) have no copy insn, so `(s16)t <= 0` is correct there.
 *  3. case 8 assigns `ptr` AFTER the func_8012A828 call. Assigning it first gives the
 *     `la $s1,D_8019E9FC` a low enough LUID to win the `lhu 0x70` load-delay slot, which
 *     eats the target's `nop` (-1 ins). $s1 is callee-saved, so sched1 still hoists the
 *     `la` back above the call — just not into the delay slot.
 * Also: `D_8019E994 + 8` (not a separate D_801B516C symbol) is what produces the CSE'd
 * `addiu $a1,$s2,0x8` off the $s2 base; two symbols would emit a second lui/addiu pair.
 * The `| 0x40000000 | 0x20000000` must stay as TWO ors — gcc-2.7.2 fold has no associate
 * step for BIT_IOR_EXPR, and a folded `| 0x60000000` emits only one lui/or.
 */

extern u8  D_8019E994[];
extern u8  D_8019E8B4[];
extern u8  D_801A4EAC;
extern u8  D_8019EA1C[];
extern u8  D_8019E9FC[];
extern u8  D_8019EA0C[];
extern u8  D_8019E9EC[];
extern u8  D_801B6598[];
extern void *D_8019EB7C[];

extern void func_8012E9C0(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_801833F4(void *a0, s32 a1, s32 a2);
extern s32  func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_801834F0(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8018348C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);  /* TU-canonical: matches the decl at ov_SC06_018_jr_8017C24C.c:7883 */
extern void func_8002A520(s32 a0);
extern void func_8002A790(s32 a0);
extern void func_80131E00(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_80183FD0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80181654(s32 a0, s32 a1);

void func_801800C8(s32 p) {
    s32 buf20[2];
    s32 iVar1;
    s32 iVar2;
    s32 t;
    void *ptr;

    func_8012E9C0(p);
    *(s32 *)(p + 0x1C) = 0;
    *(u16 *)(p + 0x5C) = *(u16 *)(p + 0x5C) & 0xFFFE;
    func_8012B23C(p);

    t = (*(s16 *)(p + 0x60) * *(s16 *)(*(s32 *)(p + 0x78) + 0x30)) >> 12;
    iVar1 = t;
    t = t << 16;
    if (t <= 0) {
        iVar1 = 1;
    }

    if (*(u32 *)(p + 0xE0) & 1) {
        ((void (*)(s32, void *, void *))func_8012F214)(p, D_8019E994, buf20);
        if (func_801833F4(buf20, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x400) != 0) {
            func_80146A6C(6, (void *)p, *(s16 *)(p + 0x7C), *(s16 *)(p + 0x7E),
                          *(s16 *)(p + 0x80), 0, 0);
            t = *(u16 *)(p + 0xFE) - iVar1;
            *(s16 *)(p + 0xFE) = t;
            if ((s16)t <= 0) {
                func_801834F0(p, D_8019E994 + 8, buf20, 0xC);
                func_8018348C(p, buf20, 0x27F, 0, 0, 0);
                *(s32 *)(p + 0x58) = (s32)D_8019E8B4 | 0x40000000 | 0x20000000;
                *(u32 *)(p + 0xE0) = *(u32 *)(p + 0xE0) & 0xFFFFFFFE;
                func_8001C924(*(s32 *)(p + 0x20), &D_801A4EAC);
            }
            func_8012B14C(p, (s32)D_8019EA1C);
            *(s16 *)(p + 0x34) = 3;
            return;
        }
    }

    if (*(u16 *)(p + 0x5E) != 0x1D) {
        if (*(u8 *)(p + 0xC8) != 0) {
            func_8002A520(p);
        }
        if (*(u8 *)(p + 0xC9) != 0) {
            func_8002A790(p);
        }
    }

    t = *(u16 *)(p + 0x76) - iVar1;
    *(s16 *)(p + 0x76) = t;
    if ((s16)t <= 0) {
        func_80131E00(p, 0xC);
        return;
    }

    *(s16 *)(p + 0x98) = 0;
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) = (*(u16 *)(p + 0x62) + 0x800) & 0xFFF;
    iVar2 = *(s32 *)(p + 0x20);
    *(s16 *)(iVar2 + 0x14) = 0;
    *(s16 *)(iVar2 + 0x10) = 0;
    func_8012B2CC(p);
    func_80183FD0(p, 0x9B7);

    switch (*(u16 *)(p + 0x5E)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 0xB:
    case 0xC:
    case 0x10:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x28:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x31:
    case 0x32:
        *(s16 *)(p + 0x34) = 4;
        func_8012A828(p, D_8019EB7C[*(u16 *)(p + 0x70) & 0xF]);
        return;
    case 8:
        func_8012A828(p, D_8019EB7C[*(u16 *)(p + 0x70) & 0xF]);
        ptr = D_8019E9FC;
        break;
    case 5:
    case 0x1D:
    case 0x20:
    case 0x26:
    case 0x2A:
        ptr = D_8019EA0C;
        func_8012A828(p, D_801B6598);
        *(u32 *)(p + 0xE0) = *(u32 *)(p + 0xE0) | 8;
        *(u16 *)(p + 0xAE) = *(u16 *)(p + 0xAE) | 1;
        func_80181654(p, -0x8000);
        break;
    default:
        ptr = D_8019E9EC;
        break;
    }
    func_8012B14C(p, (s32)ptr);
    *(s16 *)(p + 0x34) = 0;
}
