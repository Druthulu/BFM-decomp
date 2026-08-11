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
extern u8 D_801880C4;
extern u8 D_80188034;
extern u8 D_80188010;
extern u8 D_80187FEC;
extern u8 D_801880A0;
extern u8 D_8018807C;
extern u8 D_80188058;
extern u8 D_80187FC8;
extern void func_80145934(void);
extern u8 D_80188154;
extern u8 D_80188130;
extern u8 D_8018810C;
extern u8 D_801880E8;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
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
extern unsigned char D_8018754C[];
extern unsigned char D_8018757C[];
extern unsigned char D_801875CC[];
extern unsigned char D_801875FC[];
extern unsigned char D_8018762C[];
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
extern void (*D_8018767C[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_80187744[];
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
extern u8 D_801877CC[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801877D4;
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
extern int D_801B4070;
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
extern s32 D_801B4074;
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
extern s32 D_80187804;
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
extern void (*D_801878AC[])(void);
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
extern void (*D_801878D0[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_801878C0;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801878E4[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801878F0[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80187900[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80187918[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80187908;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018792C[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80187948[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80187938;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018795C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80187970[])(void);
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
extern s32 D_80187984;
extern void (*D_801879AC[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018798C;
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
extern int (*D_801879F8[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801879FC[])(void);
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
extern unsigned short D_80187E60[];
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
extern void (*D_80187E70[])(void);
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
extern int D_801B40A8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80187E98[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80187E78;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80187E88;
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
extern void (*D_80187ED8[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80187EE0[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80187EAC;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80187EEC[])(void);
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
extern u8 D_80187EBC;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B40B0;
extern s32 D_801B40BC;
extern s32 D_801B40C0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187F28[])(s32 *);
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
extern s32 D_80187EFC[];
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
extern s32 D_801B40B8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188178[])(void);
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
extern char D_80187F98[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018821C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80188370[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018818C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80188378[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018819C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_801881BC;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80188380[])(void);
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
extern void (*D_801883A8[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_801883B4[])(void);
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
extern void (*D_80188228[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80188458;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018753C[];
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
extern unsigned char D_8018846C[];
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
extern s8 D_801884A8[];
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
extern u16 D_801884F0;
extern u16 D_801884F2;
extern u16 D_801884F4;
extern s32 D_801884F8;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80188500;
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
extern int D_8018820C;
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
extern unsigned int D_80188584[];
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
extern void (*D_80188634[])(void);
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
extern u16 D_80188664[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_801886C8;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B40C8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801886EC[])(void);
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
extern int D_801B4120[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80188734[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80188724;
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
extern char D_801B3984[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018873C[])(void);
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
extern void (*D_80188790[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80188758;
extern s16 D_8018878C;
extern s16 D_8018878A;
extern s16 D_80188788;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018879C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B4180;
extern u8 D_801B4181;
extern u8 D_801B4182;
extern u8 D_801B4183;
extern u8 D_801B4184;
extern u8 D_801B4185;
extern u8 D_801B4186;
extern u8 D_801B4187;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801887AC[])(void);
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
extern s32 D_801B41C0;
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
extern void (*D_801887F0[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018886C[];
extern s32 D_8018888C[];
extern u8 D_80188908[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80188928[];
extern u8 D_80188948[];
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
extern void (*D_801889E4[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80188A60[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B3994;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80188A6C[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80188A74[])(void);
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
extern void (*D_80188B3C[])(void);
extern void func_80166618(void *a0);
extern void (*D_80188B4C[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80188B5C[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80188B68[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80188AC8[];
extern u8   D_80188ADC[];
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
extern void (*D_80188B80[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80188B88[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80188B90[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80188B98[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80188BA0[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80188BA8[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80188BB0[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80188C64[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80188C6C[])(void);
extern void func_80169F00(void *a0);
extern char D_80188C1C[];
extern char D_80188BDC[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80188CA4[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80188CB0[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80188CF8[])(void);
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
extern void (*D_80188D74[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B44E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80188D68[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80188DAC[];
extern unsigned short D_80188DB4[];
extern unsigned short D_80188DBC[];
extern unsigned char D_801B44E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B44E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188DC4[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B461C;
extern M2C_UNK D_801B4620;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B45A8;
extern void (*D_80188DF4[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B4624[];
extern u8 D_801B462C[];
extern u8 D_801B45DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80188DFC[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80188E18[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80188E20[])(void);
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
extern void (*D_80188E88[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80188E2C;
extern u8 D_80188E38;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80188EBC[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188EC4[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188F18[])(void);
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
extern u16 D_80188F4C[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80188F3C[];
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
extern s32 D_80188F68;
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
extern void (*D_80188FE0[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80188FE8[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80188FF0[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188FF8[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189000[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189008[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189014[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189020[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018902C[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018903C[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018904C[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189054[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018905C[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189064[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018906C[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80189074[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018907C[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80189084[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018908C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80189094[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018909C[])(void);
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
extern void (*D_801890A4[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801890AC[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_801890B4[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_801890BC[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_801890C4[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_801890CC[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801890D4[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801890DC[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_801890E4[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801890EC[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801890F4[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801890FC[])(void);
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
extern void (*D_80189140[])(void);
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
extern M2C_UNK D_80189104;
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
extern void (*D_80189170[])(void);
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
extern void (*D_801891AC[])(void);
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
extern void (*D_80189204[])();
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
extern void (*D_80189214[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018921C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80189384[])();
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
extern void (*D_80189390[])();
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
extern M2C_UNK D_801B3BDC;
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
extern s16 D_801B5B18;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B4D60;
extern short D_801B5B8C;
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
extern s32 D_801B518C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B51B4;
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
extern s16 D_801B5170;
extern s32 func_8017A3B0(void);
extern short D_801B51AC;
extern short D_801B51A8;
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
extern s16 D_801B5174;
extern u16 D_801B51F4;
extern u16 D_801B51F6;
extern u16 D_801B51F8;
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
extern s16 D_801B51EC;
extern s16 D_801B51EE;
extern s16 D_801B51F0;
extern s16 D_801B51E4;
extern s16 D_801B51E6;
extern s16 D_801B51E8;
extern void func_8017B7A8(void);
extern s16 D_801B5204;
extern s16 D_801B5206;
extern s16 D_801B5208;
extern s16 D_801B520C;
extern s16 D_801B520E;
extern s16 D_801B5210;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B51FC;
extern short D_801B51FE;
extern short D_801B5200;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B5194;
extern SV4 D_801B519C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B51BC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B51B8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018956C[])(void);
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



/* func_8017CD9C — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801B5218..D_801B5240 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017CD9C(s32 param_1, s32 param_2)
{

    extern s32 D_801B5218;
    extern s32 D_801B521C;
    extern s32 D_801B5220;
    extern s32 D_801B5228;
    extern s32 D_801B522C;
    extern s32 D_801B5230;
    extern s32 D_801B5238;
    extern s32 D_801B523C;
    extern s32 D_801B5240;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_8017CD9C vec;                              /* sp+0x10 */
    MTX_L_8017CD9C mtx;                              /* sp+0x18 */
    s32 obj = *(s32 *)(param_1 + 0xCC);
    s32 prim = *(s32 *)(param_1 + 0x20);
    s32 mode;
    s32 val;
    s32 hi;
    s32 code;
    s32 t;

    if ((s16)param_2 != 0) {
        mode = 0x40000000;
        val = 0x1000;
    } else {
        mode = 0x50000000;
        val = 0x1333;
    }
    code = *(s32 *)(prim + 4) & 0xCFFFFFFF;
    hi = 0x40000000;
    *(s32 *)(prim + 4) = code | (mode | hi);

    if (*(u16 *)(*(s32 *)(param_1 + 0xCC)) != 0) {
        *(s16 *)(obj + 0x1A) = val;
        *(s16 *)(obj + 0x18) = val;
    }

    t = *(u16 *)(param_1 + 0xFC) + 0x80;
    *(u16 *)(param_1 + 0xFC) = t;
    vec.a = t;
    t = *(u16 *)(param_1 + 0xFE) + 0x100;
    *(u16 *)(param_1 + 0xFE) = t;
    vec.b = t;
    vec.c = 0;
    RotMatrixYXZ(&vec, &mtx);

    vec.b = 0;
    vec.a = 0;
    vec.c = 0x100;
    ApplyMatrixSV(&mtx, &vec, &vec);

    D_801B5238 = vec.a;
    D_801B5228 = vec.a;
    D_801B5218 = vec.a;
    D_801B523C = vec.b;
    D_801B522C = vec.b;
    D_801B521C = vec.b;
    D_801B5240 = vec.c;
    D_801B5230 = vec.c;
    D_801B5220 = vec.c;
}



/* func_8017CECC — ov_SC02_027_jr_8017AE2C (227 ins).  MATCH (match_one, 227/227).
 *
 * RETRY-WAVE RE-VERIFICATION (§136b — the ledgered DIFF describes an OBSOLETE draft).
 * The s8 gate ran 14:53; THIS file was written 15:22, 28 min AFTER it.  The gate never saw it.
 * Four independent checks on the file as it stands:
 *   1. match_one              -> MATCH (227 ins)
 *   2. rtu_match (whole TU)   -> MATCH (227 ins); CC1 clean, the only warning is the TU's
 *                                pre-existing `memcpy' builtin one at TU:1530 (baseline too)
 *   3. FULL RELOCATION RESOLVE (the byte-gate's view, which match_one's mask cannot see):
 *      every R_MIPS_26 / HI16 / LO16 resolved from the D_<addr>/func_<addr> symbol values and
 *      compared word-for-word against the target .s -> 0/227 diffs.  Every jal target, every
 *      %hi/%lo symbol AND addend is right.
 *   4. COLLATERAL: TU compiled with and without the splice; all 53 other functions emit
 *      IDENTICAL words.  The only deltas are .text-relative `j' addends, every one shifted by
 *      exactly 0x38C == this function's size, which the linker resolves identically.
 * No codegen work was needed; the previous agent's tbl/tbl2 split + load-before-store lever
 * (documented below) had already closed it.
 *
 * Declarations reconciled against the WHOLE TU (grepped in one pass, D2):
 *   func_800291B4  TU:59/3422   extern s32 func_800291B4(s32 arg);     -> `& 0xFF` at the call
 *   func_8001C810  TU:1548      extern void func_8001C810(s32 a0, s32 a1);
 *   func_8001CD50  TU:1564/3518 extern void func_8001CD50(s32, s32);
 *   func_800233CC  TU:1565/3519 extern void func_800233CC(void *, unsigned short);
 *   func_8001D074  TU:124/129/3517 declared VOID -> s32 return taken through a cast (idiom 9)
 *   func_8012A828  TU:3730      extern void ((void (*)(s32, void *))func_8012A828)(s32 a0, void *a1);
 *   D_801152BA     TU:3657      extern u16 D_801152BA;   (the SIGNED uses need an (s16) cast:
 *                               combine folds (s16)(u16 mem) back to a plain `lh`)
 *   D_80115214     TU:3432/3658 extern s16 D_80115214;
 *   D_801B5218     TU:3333      extern s32 D_801B5218;
 * func_8012CAE4 / func_8012C354 are absent from the TU; the canonical engine_core.h forms
 * are reused verbatim (DEFINE_func_8012CAE4 @15355 `void func_8012CAE4(void *a0)`,
 * DEFINE_func_8012C354 @15748 `s32 func_8012C354(s32 a0, s32 a1)`).
 * D_801895A0 / D_801895DC / D_801B0044 / every D_801D9E9x-ECx / D_801B52C8 appear nowhere
 * in the TU or engine_core.h (only D_801B5218..EB8 and D_801D9F00..F06 are declared there).
 * D_801B006C is declared BLOCK-SCOPE here on purpose: the TU's only other declaration
 * (TU:3587, `extern Rec_8017C738 D_801B006C[];`) is itself block-scope inside func_8017C738,
 * so neither is a file-scope decl the other can collide with.
 *
 * THE 0x6C-BYTE TABLE COPY.  9 x 12-byte records = 108 bytes at alignment 2, so
 * gcc-2.7.2's mips.c:expand_block_move takes the align < UNITS_PER_WORD path and emits the
 * runtime `or / andi 3 / beq` alignment probe, an unaligned lwl/lwr loop, an aligned lw/sw
 * loop, and an unaligned 12-byte tail.  The join label after the two loops resets cse, which
 * is why the target RE-COMPUTES 108*D_801152BA for the *(a0+0xD8) store.
 *
 * WHAT CLOSED THE LAST 7 (sched.md §1.7 / §S2 — THE BIRTHING BOOST).  Two independent levers,
 * both required; neither is statement-order:
 *
 *  1. `idx = (s16)D_801152BA;` must be read BEFORE the `*(s16*)(s1+0x10) = 0x400` store.
 *     Store-then-load is a true dependence (both MEMs non-struct: the store's address varies,
 *     the load's is constant, so true_dependence's MEM_IN_STRUCT_P escape does not apply) and
 *     it pins `sh 0x10(s1)` ABOVE the `lh`.  Load-first makes it an ANTI dep, whose cost is
 *     still +1 in 2.7.2 (insn_cost is dep-kind-blind, sched.md [A23]), lifting pri(sh) to 2 so
 *     the store is picked first by the backward scheduler and lands LAST, at index 93.
 *
 *  2. `tbl` and `tbl2` MUST BE TWO SEPARATE LOCALS.  One shared `tbl` gives the D_801B52C8
 *     address pseudo REG_N_SETS==2, which KILLS the birthing boost (birthing_insn_p,
 *     sched.c:2469/2490): the unboosted `la $a0` then floats to the front of the pri-1 group
 *     and lands at index 86, shoving `la $a2,D_801B006C` to 88 (this was the entire 7-insn
 *     residual: 86..92 rotated).  Splitting the two uses makes each pseudo single-set, the
 *     boost raises `la $a0` to its consumer's priority so it sinks to 91, and `la $a2` — whose
 *     pseudo IS genuinely multi-set (expand_block_move increments it in both copy loops, so it
 *     can never be boosted) — falls to the front at 86, exactly as the target has it.
 *     Verified invariant: with a shared `tbl`, ALL 8 legal orderings of the 4 head statements
 *     x 2 store forms (INDIRECT_REF and ARRAY_REF) give the SAME wrong order — proof the
 *     residual was priority/boost-driven, not LUID/statement-order-driven.
 */
extern s32 func_800291B4(s32 arg);
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);



void func_8017CECC(s32 a0) {

    extern u8 D_801895A0[];
    extern u8 D_801895DC[];
    extern s32 D_801B0044;
    extern u16 D_801152BA;
    extern s16 D_80115214;
    extern s32 D_801B5218;
    extern u8 D_801B5224;
    extern u8 D_801B5225;
    extern u8 D_801B5226;
    extern u8 D_801B5234;
    extern u8 D_801B5235;
    extern u8 D_801B5236;
    extern u8 D_801B5245;
    extern u8 D_801B5246;
    extern u8 D_801B5248;
    extern u8 D_801B5249;
    extern u8 D_801B524A;
    extern u8 D_801B524C;
    extern u8 D_801B524D;
    extern u8 D_801B524E;
    extern u8 D_801B5254;
    /* 9 x 12-byte records = 0x6C bytes, alignment 2 */
    extern Blk027_8017CECC D_801B006C;
    extern Blk027_8017CECC D_801B52C8[];

    u8 *v1;
    s32 s1;
    u8 *p;
    s32 t;
    s16 i;
    Blk027_8017CECC *dst;
    Blk027_8017CECC *tbl2;
    s32 idx;
    Blk027_8017CECC *tbl;
    s32 u;
    s32 w;

    v1 = *(u8 **)(a0 + 0xDC);
    if ((func_800291B4(v1[0] + 0x3A) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    if (*(s32 *)(a0 + 0x20) == 0) {
        if (func_8012C354(a0, (s32)D_801895A0) == 0) {
            return;
        }
        func_8001C810(*(s32 *)(a0 + 0x20), (s32)&D_801B0044);
        ((void (*)(s32, void *))func_8012A828)(a0, (void *)&D_801895DC[(s16)D_801152BA * 16]);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x20;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)&D_801B5218;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)(a0 + 0xAE) = -3;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 == 0) {
        return;
    }

    p = &D_801B5248;
    *(s32 *)(a0 + 0xCC) = s1;
    func_8001CD50(s1, (s32)p);

    D_801B524A = 0x80;
    *p = 0x80;
    D_801B5249 = 0xE0;
    D_801B524D = 0;
    D_801B524C = 0;
    D_801B524E = 0;
    func_800233CC(p, 0x38);

    tbl = D_801B52C8;
    idx = (s16)D_801152BA;
    dst = &tbl[idx];
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x8) = *(u16 *)(a0 + 0x6);
    t = *(u16 *)(a0 + 0xA) - 4;
    *(u16 *)(a0 + 0xA) = t;
    *(s16 *)(s1 + 0xA) = t;
    *(s16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(s1 + 0x4) |= 0x50000000;

    D_801B5246 = 0xFF;
    D_801B5254 = 0xFF;
    D_801B5236 = 0xFF;
    D_801B5234 = 0xFF;
    D_801B5226 = 0xFF;
    D_801B5224 = 0xFF;
    D_801B5245 = 0x80;
    D_801B5235 = 0x80;
    D_801B5225 = 0x80;

    *dst = D_801B006C;

    i = 5;
    tbl2 = D_801B52C8;
    *(s32 *)(a0 + 0xD8) = (s32)&tbl2[(s16)D_801152BA];

    while (i < 0x28) {
        if ((func_800291B4(i + 0x3B) & 0xFF) != 0) {
            break;
        }
        i++;
    }
    if (i != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    }

    w = D_801152BA + 1;
    u = *(u16 *)(a0 + 0x2) + 1;
    D_80115214 = 0;
    D_801152BA = w;
    *(u16 *)(a0 + 0x2) = u;
}



/* Declarations copied VERBATIM from the TU (ov_SC02_027_jr_8017AE2C.c):
 *   func_800291B4  TU:59
 *   currentLocationId TU:349
 *   D_80126B5C     TU:361  (scalar u8 -> pass (s32)&D_80126B5C)
 *   D_801202A0     TU:385
 *   func_80013328  TU:520
 *   D_800B99DA     TU:615
 *   rand           TU:957/1092/3543
 *   D_80126B62     TU:1793/2740/3068
 *   func_801746A4  TU:2397
 *   func_80178B18  TU:2539/3653
 *   func_8017CD9C  TU:3465/3542 (void return)
 *   D_80115214     TU:3547
 * func_8012BD14 / D_801895D4 / D_80189638 appear nowhere in the TU; the
 * canonical engine_core.h form of func_8012BD14 is `void func_8012BD14(s32)`
 * (DEFINE_func_8012BD14), so it is declared void and the s32 return is taken
 * through a cast at the call site (idiom 9). */
extern s32 func_800291B4(s32 arg);
extern s16 currentLocationId;
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_801746A4(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017CD9C(s32 a0, s32 a1);
extern void func_8012BD14(s32 a0);

void func_8017D258(s32 a0) {

    extern u8 D_80126B5C;
    extern u8 D_801202A0[];
    extern u16 D_80126B62;
    extern s16 D_80115214;
    extern u8 D_801895D4[];
    extern u8 D_80189638[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_800B99DA;
    s32 s0 = *(s32 *)(a0 + 0x20);
    s16 found;
    s32 lvl;
    s16 i;
    s16 j;
    s32 rand_val;

    if ((D_800B99DA & 0xF) == 0) {
        u8 *p;
        u8 *end;
        for (p = D_801202A0, end = p + 0x6480; p < end; p += 0x10C) {
            if (*(u16 *)p == 0x128) {
                found = ((s32)p == a0);
                break;
            }
        }
        lvl = func_80013328(a0 + 4, (s32)&D_80126B5C);
        if (lvl < 0x800) {
            lvl = 0x44 - ((lvl >> 5) & 0x38);
        } else {
            lvl = 4;
        }
        if (found != 0 || D_80115214 < lvl) {
            D_80115214 = lvl;
        }
    }

    *(u16 *)(s0 + 0x12) += 0x20;
    rand_val = rand();
    func_8017CD9C(a0, rand_val & 0xF);

    if (*(u16 *)(a0 + 0x5E) != 0) {
        for (i = 0; (u16)i < 8; i++) {
            if (*(u16 *)(a0 + 0x5E) == D_801895D4[i]) {
                func_801746A4();
                *(s32 *)(a0 + 0x1C) = 0x20;
                *(u16 *)(a0 + 0x2) += 1;
            }
        }
        *(s16 *)(a0 + 0x5E) = 0;
        return;
    }

    if (*(s16 *)(a0 + 0x10A) != 0) {
        return;
    }

    j = 5;
    do {
        if ((func_800291B4(j + 0x3B) & 0xFF) != 0) {
            break;
        }
        j++;
    } while (j < 0x28);

    if (j != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    } else if (((s32 (*)(s32))func_8012BD14)(a0) < 0x2A40) {
        if (currentLocationId == 0x3028) {
            if ((u16)(*(u16 *)(a0 + 0xA) - D_80126B62 + 4) < 4) {
                *(u16 *)(a0 + 0x106) += 1;
            }
            if (*(s16 *)(a0 + 0x106) < 2) {
                return;
            }
        }
        func_80178B18(a0, (s32)D_80189638);
        *(s16 *)(a0 + 0x10A) = 1;
        *(s16 *)(a0 + 0x2) = 0xA;
    } else {
        *(s16 *)(a0 + 0x106) = 0;
    }
}



extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);

/* 0x801DA0F0 has no symbol (it is interior to D_801DA084); the real relocs
 * in the .s are D_801B548C/108/10C, with $s0 = D_801B548C - 0x14. */

void func_8017D4D0(s32 a0) {

    extern u8 D_801B5288;
    extern u8 D_801B5289;
    extern u8 D_801B528A;
    extern u8 D_801B528C;
    extern u8 D_801B528D;
    extern u8 D_801B528E;
    extern s32 D_801B548C[];
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801B5288;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801B5289 = 0xFF;
    D_801B528A = 0xFF;
    *p = 0xFF;
    D_801B528E = 8;
    D_801B528C = 8;
    D_801B528D = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801B548C[0] = sp[0];
    D_801B548C[1] = sp[1];
    D_801B548C[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801B548C[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801B548C[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017CD9C(s32 a0, s32 a1);

void func_8017D618(s32 a0) {
    extern Rec_8017C738_8017D618 D_801B006C[];

    Rec_8017C738_8017D618 *q = D_801B006C;
    Rec_8017C738_8017D618 *p = *(Rec_8017C738_8017D618 **)(a0 + 0xD8);
    u8 *v1 = *(u8 **)(a0 + 0xDC);
    s32 s1 = *(s32 *)(a0 + 0xD0);
    s32 s4 = *(s32 *)(a0 + 0x20);
    s16 val;
    s32 t;
    s16 i;

    if (v1[1] != 0) {
        if (*(s16 *)(a0 + 0x108) == 0) {
            *(s16 *)(a0 + 0x108) = func_80128CFC(*(u16 *)(v1 + 2));
        }
    }

    val = *(u16 *)(s1 + 0x1A) + 0x80;
    *(s16 *)(s1 + 0x1A) = val;
    *(s16 *)(s1 + 0x18) = val;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t != -1) {
        func_8017CD9C(a0, 0);
        for (i = 0; i < 9; ) {
            p->f0 += (s16)q->f0 >> 1;
            if (i != 0) {
                p->f2 += (q->f2 + 0x30) >> 1;
                p->f4 += (s16)q->f4 >> 1;
                p->f6 += 0x40;
                p->f8 += 0x80;
                p->fA += 0x100;
            }
            i++;
            q++;
            p++;
        }
    } else {
        *(s16 *)s4 = 0;
        *(u16 *)(a0 + 0x2) += 1;
    }
}



extern void (*D_80189688[])(void);

void func_8017D798(void *a0) {
    D_80189688[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017D7D4(void) {
    func_8014BCEC((s32)&D_80126B58, 0x5);
    func_8014BD24((s32)&D_80126B58, 0x270F);
    func_8002D4C8(0xBFE, 0);
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017CD9C(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_8017D820(void *a0) {

    extern u16 D_801152BA;
    extern s16 D_80115214;
    void *v1;
    void *s2;
    void *s1;
    u16 arg;
    s16 v0_s16;
    u16 tmp;
    s32 v0;
    s32 rand_val;
    s32 pads[4];  /* Force stack frame to 0x30 bytes */

    v1 = *(void **)(a0 + 0xDC);
    s2 = *(void **)(a0 + 0xCC);
    s1 = *(void **)(a0 + 0xD0);

    if (*(u8 *)(v1 + 1) != 0) {
        if (*(s16 *)(a0 + 0x108) == 0) {
            arg = *(u16 *)(v1 + 2);
            v0_s16 = func_80128CFC(arg);
            *(s16 *)(a0 + 0x108) = v0_s16;
        }
    }

    tmp = *(u16 *)((s32)s1 + 0x1A) + 0x20;
    *(u16 *)((s32)s1 + 0x1A) = tmp;
    *(u16 *)((s32)s1 + 0x18) = tmp;

    v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;

    if (v0 != -1) {
        rand_val = rand();
        func_8017CD9C((s32)a0, rand_val & 1);
    } else {
        D_80115214 = 4;
        D_801152BA -= 1;
        func_8002D4C8(0x62E, 0);
        *(u16 *)s2 = 0;
        *(u16 *)(a0 + 2) += 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
    }
}



extern s16 func_80128CFC(u16 a0);

void func_8017D914(void *a0) {
    void *v1 = *(void **)(a0 + 0xDC);
    s16 v0;

    if (*(u8 *)(v1 + 1) == 0) {
        v0 = 1;
    } else {
        v0 = *(s16 *)(a0 + 0x108);
        if (v0 == 0) {
            u16 arg = *(u16 *)(v1 + 2);
            v0 = func_80128CFC(arg);
            *(s16 *)(a0 + 0x108) = v0;
        }
        v0 = *(s16 *)(a0 + 0x108);
    }

    if (v0 != 0) {
        *(u16 *)(a0 + 0x2) += 1;
    }
}




extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);

void func_8017D994(s32 a0) {
    s32 v0;
    s32 *s0_ptr;
    u16 sp[8];

    s0_ptr = *(s32 **)(a0 + 0xDC);
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        return;
    }

    func_8001C214(v0, s0_ptr[1]);
    ((void (*)(s32, void *))func_8012A828)(a0, (void *)s0_ptr[2]);

    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0x58) = 0;

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);

    func_800D20C0(&sp[0], &sp[4], 0);
    func_800D23D0(&sp[4]);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = sp[5] + 0x800;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s32 func_80178B18(s32 param_1, s32 param_2);

void func_8017DA48(s32 a0) {
    s32 ptr1 = *(s32 *)(a0 + 0xD0);
    s32 ptr2 = *(s32 *)(a0 + 0xDC);
    s16 val = *(u16 *)(ptr1 + 0x1A) - 0xC0;

    *(s16 *)(ptr1 + 0x1A) = val;
    *(s16 *)(ptr1 + 0x18) = val;

    if (val < 0) {
        *(s16 *)(ptr1 + 0x0) = 0;
        func_80178B18(a0, *(s32 *)(ptr2 + 0xC));
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}




extern void func_800291A0(s32, s32);
extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017DAB4(s32 a0) {
    extern void func_8002955C(void);
    extern s32 func_8002953C(void);
    extern void func_8002AC00(s32 arg0);
    u8 *p = *(u8 **)(a0 + 0xDC);

    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        func_800291A0(*p + 0x3A, 1);
        func_8002955C();
        if ((u32)func_8002953C() >= 0x23U) {
            func_8002AC00(0x25);
        }
        *(u16 *)(a0 + 2) += 1;
    }
}


extern void func_8012C218(void*);
void func_8017DB40(void) {
    ((void (*)(void))func_8012C218)();
}




void func_8017DB60(s32 a0) {
    extern int func_80178970(void);
    extern void func_80178D18(void);
    s32 rand_val = rand();

    func_8017CD9C(a0, rand_val & 0xF);
    if (((s32 (*)(s32))func_80178970)(a0) == 0) {
        return;
    }
    ((void (*)(s32))func_80178D18)(a0);
    *(s16 *)(a0 + 0x2) = 1;
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017DBB4(void *a0) {
    func_80146A6C(0x19, a0, 0, 0, 0, 0, 1);
}



extern void (*D_801896E0[])(void);

void func_8017DBF0(void *a0) {
    D_801896E0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017DC2C(void *a0)
{
    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        func_80147324(*(u16 *)((s32)a0 + 0x2E));
    }
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



// @class: plumbing
// @stuck: none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

extern void func_8017DF10(int);

void func_8017DC7C(int param_1)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x1c);
    *(int *)(param_1 + 0x1c) = iVar1 + 1;
    if (iVar1 < 0xc) {
        *(unsigned short *)(param_1 + 0x12) = *(unsigned short *)(param_1 + 0x12) + 0xe0;
    } else {
        *(int *)(param_1 + 0x1c) = 0;
        *(unsigned short *)(param_1 + 2) = *(unsigned short *)(param_1 + 2) + 1;
    }
    func_8017DF10(param_1);
    return;
}



/* Entity record touched by func_8017DCD8 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */

extern void func_80147324(s32 arg0);
extern void func_8017DF10(int);

void func_8017DCD8(Ent_8017BFE0_8017DCD8 *param_1)
{
    s32 t;

    t = param_1->f1c;
    param_1->f1c = t + 1;
    if (t < 0x20) {
        param_1->f2a = param_1->f2a - 0x10;
    } else {
        if (param_1->f30 == 0) {
            func_80147324(param_1->f2c);
        }
        param_1->f1c = 0;
        param_1->f02 = param_1->f02 + 1;
    }
    ((void (*)(Ent_8017BFE0_8017DCD8 *))func_8017DF10)(param_1);
}




/* func_8017DD5C — entity tick with a two-mode "hit/shake" arm.
 *   +0x1C s32  frame counter (lw / sw), signed compare against 0x20
 *   +0x34 ptr  sub-object read up-front (lives in $s0 across the jals)
 *   +0x30 s32  mode flag (0 = direct sub-object, else the +0x20 sub-sub-object)
 *   +0x02 u16  state word bumped in the timeout arm
 *
 * §71 sibling-first: func_8017C69C in this same TU is the identical shape —
 * counter @0x1C, sub-object @0x34, the 0x60/0x62/0x64 halfword triple and the
 * `do { func_80146A6C(0x1B, obj, ...); } while (++i < 3);` s16 loop.
 */

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8014708C(void *arg0);
extern s32 func_801472C8(struct S *a0);
extern void func_8017DF10(int);

void func_8017DD5C(void *a0)
{
    void *obj;
    s32 t;
    s32 r;
    s16 i;
    u16 v;
    u16 w;
    u16 d;

    t = *(s32 *)((s32)a0 + 0x1C);
    obj = *(void **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            v = *(u16 *)((s32)obj + 0x64) - 0x80;
            w = *(u16 *)((s32)obj + 0x62) + 0x100;
            *(s16 *)((s32)obj + 0x64) = v;
            *(s16 *)((s32)obj + 0x60) = v;
            *(s16 *)((s32)obj + 0x62) = w;
        } else {
            r = *(s32 *)((s32)obj + 0x20);
            *(u16 *)(r + 0x2C) |= 0x10;
            r = *(s32 *)((s32)obj + 0x20);
            d = *(u16 *)(r + 0x1C) - 0x80;
            *(s16 *)(r + 0x1C) = d;
            *(s16 *)(r + 0x18) = d;
            r = *(s32 *)((s32)obj + 0x20);
            *(u16 *)(r + 0x1A) += 0x100;
        }
        i = 0;
        do {
            func_80146A6C(0x1B, obj, 0, 0, 0, 0, 0);
            i++;
        } while (i < 3);
    } else {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            func_8014708C(obj);
            func_801472C8((struct S *)obj);
        } else {
            *(s32 *)(*(s32 *)((s32)obj + 0x20) + 0x4) |= 0x80000000;
        }
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
    ((void (*)(void *))func_8017DF10)(a0);
}


extern void func_8017DF10(int);
extern void func_80146C3C(void);
void func_8017DEC4(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8017DF10(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}




/* func_8017DF10 — 4-point primitive sweep driven by the 44-byte curve table
 * D_801896B4.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_8017DF10(int param_1)
{

    extern u16 D_800B99DA;
    extern u8  D_801896B4[];
    SVec8_8017C218_8017DF10 rot;
    s32   pad0[2];
    Prim_8017C218_8017DF10  prim;
    s32   pad1[1];
    Mtx_8017C218_8017DF10   mtx;
    s32   pad2[8];
    s32   obj;
    u8   *p;
    s16   i;
    s32   c;

    obj = *(s32 *)(param_1 + 0x34);
    rot.vx = rot.vy = rot.vz = *(u16 *)(param_1 + 0x12);
    func_80017DC4(&rot, &mtx);

    prim.v[1].vx = prim.v[1].vy = prim.v[1].vz = 0;
    prim.v[0].vy = prim.v[2].vy = prim.v[3].vy = 0;
    prim.c[1].r = prim.c[1].g = prim.c[1].b = 0;

    c = ((s32)(s16)*(u16 *)(param_1 + 0x12) >> 5) + 0x20;
    prim.c[0].r = prim.c[0].g = prim.c[0].b =
    prim.c[2].r = prim.c[2].g = prim.c[2].b =
    prim.c[3].r = prim.c[3].g = prim.c[3].b = c;
    if (D_800B99DA & 1) {
        prim.c[0].r = prim.c[2].r = prim.c[3].r = prim.c[3].r >> 1;
    }

    prim.code = 0x50000000;
    rot.vx = *(u16 *)(obj + 0x6);
    rot.vy = *(u16 *)(obj + 0xA) - 8;
    rot.vz = *(u16 *)(obj + 0xE);
    func_80017E68(&rot, &mtx);

    p = D_801896B4;
    i = 0;
    do {
        prim.v[0].vx = (s8)*p++;
        prim.v[0].vz = (s8)*p++;
        prim.v[2].vx = (s8)*p++;
        prim.v[2].vz = (s8)*p++;
        prim.v[3].vx = (s8)*p++;
        prim.v[3].vz = (s8)*p--;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 10);

    prim.c[0].r = prim.c[0].g = prim.c[0].b = 0;
    p = D_801896B4;
    i = 0;
    do {
        prim.v[2].vx = (s8)*p++;
        prim.v[0].vx = prim.v[2].vx << 1;
        prim.v[2].vz = (s8)*p++;
        prim.v[0].vz = prim.v[2].vz << 1;
        prim.v[3].vx = (s8)*p++;
        prim.v[1].vx = prim.v[3].vx << 1;
        prim.v[3].vz = (s8)*p--;
        prim.v[1].vz = prim.v[3].vz << 1;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 0x14);

    if (*(s16 *)(param_1 + 0x2A) != 0) {
        p = D_801896B4;
        i = 0;
        do {
            prim.v[0].vx = prim.v[2].vx = (s8)*p++;
            prim.v[0].vz = prim.v[2].vz = (s8)*p++;
            prim.v[1].vx = prim.v[3].vx = (s8)*p++;
            prim.v[1].vz = prim.v[3].vz = (s8)*p--;
            prim.v[0].vy = prim.v[1].vy = *(u16 *)(param_1 + 0x2A);
            func_80017758(&prim, &mtx);
            i++;
        } while (i < 0x14);
    }
}



extern void (*D_801896F4[])(void);

void func_8017E21C(void *a0) {
    D_801896F4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017E258(void *a0)
{
    func_80147324(*(u16 *)((s32)a0 + 0x2E));
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



/* func_8017E298 — a state-tick: bump the frame counter at 0x1C; while it is
 * below 0xC spin the angle at 0x12 by 0xE0, otherwise reset the counter, zero
 * the vector at *(0x34)+0x60/0x64, set +0x62 to 0x3000 and advance the state
 * word at 0x02.  Falls through to ((void (*)(void *))func_8017DF10)(a0) on both arms (the target
 * leaves $a0 untouched, so the call needs no move).
 *
 * §71 sibling-first: func_8017C560 (same TU, 4 bytes earlier) is the same
 * `*(u16 *)(a0 + 2) += 1` idiom, and func_8017DF10's own prologue reads
 * `lw $s1, 0x34($s2)` / `lhu $v0, 0x12($s2)` — same record, same widths.
 */

extern void func_8017DF10(int);

void func_8017E298(void *a0) {
    s32 t;
    s32 p;

    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    p = *(s32 *)((s32)a0 + 0x34);
    if (t < 0xC) {
        *(u16 *)((s32)a0 + 0x12) += 0xE0;
    } else {
        *(s16 *)(p + 0x64) = 0;
        *(s16 *)(p + 0x60) = 0;
        *(s16 *)(p + 0x62) = 0x3000;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
    ((void (*)(void *))func_8017DF10)(a0);
}



/* func_8017E308 — small entity tick:
 *   read counter @0x1C and the sub-object pointer @0x34 up-front, bump the
 *   counter unconditionally (gcc puts that store in the beqz delay slot),
 *   then either slide @0x2A down by 0x10 or run the 3-call teardown. */

extern void func_80147324(s32 arg0);
extern void func_80147084(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_8017DF10(int);

void func_8017E308(void *a0)
{
    s32 t;
    s32 *sub;

    t = *(s32 *)((s32)a0 + 0x1C);
    sub = *(s32 **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        *(u16 *)((s32)a0 + 0x2A) = *(u16 *)((s32)a0 + 0x2A) - 0x10;
    } else {
        func_80147324(*(u16 *)((s32)a0 + 0x2C));
        func_80147084(sub);
        func_801472B4(sub);
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
    ((void (*)(void *))func_8017DF10)(a0);
}



extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017DF10(int);

void func_8017E394(void *a0)
{
    void *obj;
    s32 t;
    s16 i;
    u16 v;
    u16 w;

    t = *(s32 *)((s32)a0 + 0x1C);
    obj = *(void **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        v = *(u16 *)((s32)obj + 0x64) + 0x80;
        w = *(u16 *)((s32)obj + 0x62) - 0x100;
        *(s16 *)((s32)obj + 0x64) = v;
        *(s16 *)((s32)obj + 0x60) = v;
        *(s16 *)((s32)obj + 0x62) = w;
        i = 0;
        do {
            func_80146A6C(0x1B, obj, 0, 0, 0, 1, 0);
            i++;
        } while (i < 3);
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
    ((void (*)(void *))func_8017DF10)(a0);
}


extern void func_8017DF10(int);
extern void func_80146C3C(void);
void func_8017E468(void *a0)
{
    void *obj;
    s16 v;
    v = *(u16 *)((s32)a0 + 0x12) - 0x100;
    obj = *(void **)((s32)a0 + 0x34);
    *(s16 *)((s32)a0 + 0x12) = v;
    if (v > 0) {
        ((void (*)(void *))func_8017DF10)(a0);
    } else {
        *(s16 *)((s32)obj + 0x64) = 0x1000;
        *(s16 *)((s32)obj + 0x62) = 0x1000;
        *(s16 *)((s32)obj + 0x60) = 0x1000;
        func_80146C3C();
    }
}



extern void (*D_80189708[])(void);

void func_8017E4BC(void *a0) {
    D_80189708[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017E4F8 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
 * MATCH (45 ins), match_one + rtu_match. Four levers, in the order they were found:
 *
 * 1. §71 sibling-first — same entity shape as func_8017C610 / func_8017C69C in this
 *    TU: sub-object pointer @0x34 read BEFORE the call (it lives in $s1 across the
 *    jal), state word @0x2 bumped last. §3-T4: `beqz $v1,else` => `if (p->f2C) {..}`.
 *    ONE rand() feeds three fields; the raw low 6 bits use a bare `andi` (no extend)
 *    while the >>12 / >>6 uses share one `sll $x,16` — that shared sign-extend is
 *    what forces `r` to be a `short` local rather than an int.
 *
 * 2. §5a CROSS-JUMP — both arms end in `sh ?,0xA($s0)`; gcc tail-merged them (23 off).
 *    They only stay separate because the loaded halfword lands in a DIFFERENT hard
 *    reg per arm, which needs (a) the load to be its own statement at the TOP of each
 *    arm and (b) a SEPARATE temp per arm (t / t2) — one shared temp is one pseudo,
 *    gets one register in both arms, and re-merges. 23 -> 10 -> 6.
 *
 * 3. +0x16 is SIGNED: the target materialises -0x20 as `addiu $v0,$zero,-0x20`, not
 *    `ori 0xffe0`, so that store must go through an s16.
 *
 * 4. §49 BIRTHING BOOST (the last 6 -> 2 -> 0). Residual was two ALU insns swapped
 *    with identical registers; source statement order does NOT flip it, because
 *    sched1's `adjust_priority`/`birthing_insn_p` hands every SET(REG,..) whose dest
 *    has REG_N_SETS==1 a 0x7f000001 priority, so it sinks to just before its consumer
 *    and fixes the .greg LUID order that sched2's tie-break then reads.
 *    THE DIAL: give the offending insn's dest a SECOND set so it loses the boost —
 *    here one `u16 d` reused by both tail statements. It must be a THIRD temp, not
 *    `c` itself: writing `c = c + 1;` also un-boosts c's LOAD, which then starves to
 *    the front of the block and swaps the two `lhu`s instead. Boost the loads, starve
 *    the arithmetic. */

extern int rand(void);

void func_8017E4F8(void *a0)
{
    s32 p;
    s32 obj;
    short r;
    u16 t;
    u16 t2;
    u16 e;
    u16 c;
    u16 d;

    p = (s32)a0;
    obj = *(s32 *)(p + 0x34);
    r = rand();
    *(u16 *)(p + 0x06) = *(u16 *)(obj + 0x06) + ((r & 0x3F) - 0x20);
    if (*(s32 *)(p + 0x2C) != 0) {
        t = *(u16 *)(obj + 0x0A);
        *(s16 *)(p + 0x16) = 0x20;
        *(u16 *)(p + 0x0A) = t - 0x140;
    } else {
        t2 = *(u16 *)(obj + 0x0A);
        *(s16 *)(p + 0x16) = -0x20;
        *(u16 *)(p + 0x0A) = t2;
    }
    e = *(u16 *)(obj + 0x0E);
    c = *(u16 *)(p + 0x02);
    *(s32 *)(p + 0x30) = (r >> 12) & 3;
    d = ((r >> 6) & 0x3F) - 0x20;
    *(u16 *)(p + 0x0E) = e + d;
    d = c + 1;
    *(u16 *)(p + 0x02) = d;
}


extern void func_800D22E4(s32 a0);
extern void func_80146C3C(void);
extern void func_8017E608(void *a0);
void func_8017E5AC(void *a0)
{
    s32 t;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0xA) {
        ((void (*)(void))func_800D22E4)();
        func_8017E608(a0);
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}




void func_8017E608(void *a0)
{
    extern Mtx8_8017C910_8017E608 aD800AE620 __asm__("D_800AE620");
    extern void aFunc80016A5C(void *arg0, void *arg1) __asm__("func_80016A5C");
    Prim_8017C910_8017E608 prim;
    Mtx8_8017C910_8017E608 mtx;
    s32 p;

    p = (s32)a0;
    if (*(s32 *)(p + 0x2C) != 0) {
        prim.v[0].y = *(u16 *)(p + 0xA) - 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) + 0x20;
    } else {
        prim.v[0].y = *(u16 *)(p + 0xA) + 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) - 0x20;
    }
    prim.v[0].x = *(u16 *)(p + 0x6);
    prim.v[0].z = *(u16 *)(p + 0xE);
    prim.v[1].x = *(u16 *)(p + 0x6);
    prim.v[1].z = *(u16 *)(p + 0xE);
    prim.col[0].b = 0;
    prim.col[0].g = 0;
    prim.col[0].r = 0;
    switch (*(u32 *)(p + 0x30)) {
    case 0:
        prim.col[1].r = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].g = 0;
        break;
    case 1:
        prim.col[1].g = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].r = 0;
        break;
    case 2:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0;
        prim.col[1].r = 0;
        break;
    case 3:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0xFF;
        prim.col[1].r = 0xFF;
        break;
    }
    mtx = aD800AE620;
    prim.tag = 0x50000000;
    aFunc80016A5C(&prim, &mtx);
}




extern void func_80029124(s32, s32);
extern void func_800291F0(s32, s32);
extern void func_8002D4C8(s32, s32);
/* NOTE: func_8017EEC4 is DEFINED later in this TU as `int func_8017EEC4(int)`.
 * Conform to that signature (byte-neutral: return value unused, $a0 = 0). */
extern int func_8017EEC4(int);

void func_8017E778(void)
{

    extern s32 D_8011F9C4;
    extern s32 D_80189A9C;
    extern s32 D_80189BB4;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_8011F9C4 = 1;
    func_80029124(0xD2, 1);
    func_800291F0(4, 0xD2);
    func_8002D4C8(6, 0);
    D_801274C8 = (u8 *)&D_80189A9C;
    D_801274CC = (void *)&D_80189BB4;
    func_8017EEC4(0);
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017E7E8);


extern void (*D_801897B0[])(void);

void func_8017E858(void *a0) {
    D_801897B0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017EA88(void);
extern void func_800167B8(s32 a0);

s32 func_8017E894(s32 a0) {
    func_8017EA88();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017E8D8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017EAB0(void);

s32 func_8017E8FC(s32 a0) {
    func_8017EAB0();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E93C(u8 *a0) {
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
void func_8017E9B8(void) {
    func_800D1EBC();
}



extern void (*D_801897C4[])(void);

void func_8017E9D8(void *a0) {
    D_801897C4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017EA14(s32 a0) {
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
void func_8017EA88(void) {

    extern s32 D_801897D0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801897D0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017EAB0(void) {

    extern s32 D_801897D4(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801897D4, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017EC08(void *a0);

void func_8017EAD8(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x1F4;
    D_8012695C = 0x384;
    D_80126968 = 0x238;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EC08, 0);
    func_8012A094((s32)D_80126948);
    func_8017EC08(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017EC08(void *a0);

void func_8017EB70(void) {

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
    D_8012695C = 0x4B0;
    D_80126968 = 0x2AA;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EC08, 1);
    func_8012A094((s32)D_80126948);
    func_8017EC08(D_80126948);
}



extern void (*D_801897E0[])(void);

void func_8017EC08(void *a0) {
    D_801897E0[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern void func_8017ED2C(s32, s16*);

void func_8017EC44(s32 a0) {

    extern Blob8_8018A47C_8017EC44 D_80126940;
    Blob8_8018A47C_8017EC44 tmp;

    tmp = D_80126940;
    ((void (*)(s32, Blob8_8018A47C_8017EC44 *))func_8017ED2C)(a0, &tmp);
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017ED2C(s32 param_1, s16 *param_2);

void func_8017EC8C(s32 a0) {

    extern s16 D_801897E8[];
    extern Blk8_80126940_8017EC8C D_80126940;
    Blk8_80126940_8017EC8C sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_801897E8[t];
    }
    sp10 = D_80126940;
    func_8017ED2C(a0, sp10.v);
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

void func_8017ED2C(s32 param_1, s16 *param_2) {
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

int func_8017EEC4(int param_1)
{

    extern unsigned char D_801897EC[];
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_801897EC + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}



s32 func_8017EEF4(void) {
    return 85;
}



extern void (*D_80189850[])(void);

void func_8017EEFC(void *a0) {
    D_80189850[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void ((void (*)(s32*, s32))func_8012A828)(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_80185EB8    : TU declares `extern u8 D_80185EB8[];` (block scope, L3467).
 *                   Conformed; `(s32)D_80185EB8` == `(s32)&D_80185EB8`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_80189804, func_8017F01C, func_8017EF38 : no other
 *                   declaration anywhere in the TU (func_8017F01C / func_8017EF38
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern void func_8017F01C(void);

void func_8017EF38(s32 a0) {

    extern M2C_UNK D_80189804;
    extern u8 D_80185EB8[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_80189804)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        ((void (*)(s32*, s32))func_8012A828)((s32 *)s0, (s32)D_80185EB8);
        func_801788B8(s0, (s32)func_8017F01C);
    }
}


void func_8017EF9C(void) {
}

extern void func_80178CBC(s32 arg0, s32 arg1);
extern s32 D_80189838;

void func_8017EFA4(void *arg0) {
    ((void (*)(void *, s32))func_80178CBC)(arg0, &D_80189838);
    *(s16 *)((s32)arg0 + 0x2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017EFDC(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017F01C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017F080);


extern void (*D_80189860[])(void);

void func_8017F110(void *a0) {
    D_80189860[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s16 a1);
extern void func_8012AD50(s32);
void func_8017F14C(s32 *a0) {
    func_8012BF4C(a0, 0);
    func_8012AD50(a0);
}


extern s32 func_8012BEE8(s32 arg);
extern s32 func_8017267C(s32 *a0);
extern void func_8012BF4C(s32 *a0, s16 a1);
extern s32 rand(void);

void func_8017F180(void *a0)
{

    extern s32 *D_80126B78;
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

    func_8017F2D0(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017F2D0(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017F2D0(a0);
        }

        s0 = s0 + 1;
    } while (s0 < 3);
    goto end_func;

default_case:
    func_8017F2D0(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017F2D0(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017F2D0(a0);
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

void func_8017F2D0(void *a0) {

    extern u8 D_801202A0[];
    extern u8 D_80189868[];
    s32 t;
    u8 *r;
    u8 *p;
    s32 i;
    s32 o;
    s16 out[4];

    t = *(s16 *)((s32)a0 + 0x70);
    r = &D_80189868[t * 8];
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



extern void (*D_8018989C[])(void);

void func_8017F3BC(void *a0) {
    D_8018989C[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017F3F8 — state entry: init the sub-object at +4/+0x10, bind the
 * primitive at +0x20 to the command list D_80189890 (0x270 / 0x100), paint
 * its RGB (0x40,0x40,0x40) + code 0x9C, OR 0xD0000000 into its tag word,
 * clear the counter at +0x2C, then seed three random fields and bump the
 * state word at +2.
 */

extern void func_800159E4(s32 a0, s32 a1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern int rand(void);

void func_8017F3F8(int param_1)
{
    extern unsigned char D_80189890[];
    int p;
    int r1;
    int r2;

    p = *(int *)(param_1 + 0x20);
    ((void (*)(int, int))func_800159E4)(param_1 + 4, param_1 + 0x10);
    ((void (*)(int, int, int, int))func_8001CC3C)(p, (int)D_80189890, 0x270, 0x100);
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


void func_8017F4DC(s32 *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    if (func_80146E98((s32)a0) != 0) {
        v1 = 0x7FFFFFFF;
        v0 = *(s32 *)((s32)s1 + 0x4);
        v0 = v0 & v1;
        *(s32 *)((s32)s1 + 0x4) = v0;
        func_80146E90(a0, 0x10);

        v0 = *(u16 *)((s32)a0 + 0x2);
        v0 = v0 + 1;
        *(u16 *)((s32)a0 + 0x2) = v0;
    }
}



/* func_8017F548 — per-frame update for the effect entity that func_8017E8CC
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
extern void func_801292C8(void);

void func_8017F548(int param_1)
{
    UVec_8017EA1C_8017F548 v;
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


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017F634);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017F7F0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017F86C);

















extern void func_8012AD44(s32 *a0, s16 a1);
void func_8017FA20(void)
{
  double new_var2;
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, (double) 3);
 do { new_var = 0x51AB; } while (0 & 0xFFFFFFFFFFFFFFFF); new_var = 0x51AB;
  new_var2 = (double) 3;
}


s32 func_8017FA40(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x3;
    }



extern void (*D_80197FF8[])(void);

void func_8017FA54(void *a0) {
    D_80197FF8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FA90);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FB1C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FC8C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FCFC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FDB0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8017FEAC);



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
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
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
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
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

void func_8017FF08(void *a0, void *a1)
{

    extern void func_8001E094(void);
    extern void func_8001E378(void *a0);
    extern void func_80180324(void *a0, void *a1, u32 *a2, u32 *a3);
    extern u8 D_800A6610[];
    extern short D_800B9A02;   /* TU-visible spelling (engine_core.h + ov_SC01_000.c col-0);
                                * unsigned access forced at the use — §8d sub-class (b) */

    Vec8_80182FD4 base;
    Vec8_80182FD4 v[3];
    u32  buf[19];
    long flag;
    long otz;
    long flag2;

    Src_80182FD4 *s;
    u32 *ot;
    s32 z;
    s32 i;
    u16 w;

    ot = (u32 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    s = *(Src_80182FD4 **)((s32)a0 + 0x20);
    if (s == 0) {
        return;
    }

    if (*(s32 *)((s32)a0 + 0x34) != 0) {
        func_8001E094();
    } else {
        func_8001E378(a0);
    }

    base.vx = *(u16 *)((s32)a0 + 0x2E);
    base.vy = *(u16 *)((s32)a0 + 0x30);
    base.vz = *(u16 *)((s32)a0 + 0x32);

    gte_ldv0(&base);
    gte_rtps();
    gte_stsxy(&buf[0]);
    gte_stflg(&flag);
    gte_stszotz(&otz);

    if (flag & ~0x1000) {
        return;
    }

    w = *(u16 *)((s32)a0 + 0x2C);
    z = otz + 1;
    if ((w & 0xC000) != 0) {
        if ((w & 0xC000) == 0xC000) {
            z -= (w & 0xFFF);
            if (z < 0) {
                z = 0;
            }
        } else {
            z += (w & 0xFFF);
        }
    }
    if (z >= 0x1000) {
        return;
    }

    if (*(s16 *)((s32)a0 + 0x1E) & 0x8000) {
        for (i = 0; i < 12; i += 6) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            v[1].vx = base.vx + s->pt[i + 2].vx;
            v[1].vy = base.vy + s->pt[i + 2].vy;
            v[1].vz = base.vz;
            v[2].vx = base.vx + s->pt[i + 4].vx;
            v[2].vy = base.vy + s->pt[i + 4].vy;
            v[2].vz = base.vz;
            gte_ldv3(&v[0], &v[1], &v[2]);
            gte_rtpt();
            gte_stsxy3(&buf[i + 1], &buf[i + 3], &buf[i + 5]);
        }
        for (i = 1; i < 12; i += 2) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            gte_ldv0(&v[0]);
            gte_rtps();
            gte_stsxy(&buf[i + 1]);
            gte_stflg(&flag2);
            gte_stszotz(&otz);
            buf[13 + (i >> 1)] = otz + 1;
        }
        func_80180324(a0, a1, &buf[0], ot);
    } else {
        for (i = 0; i < 12; i += 3) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            v[1].vx = base.vx + s->pt[i + 1].vx;
            v[1].vy = base.vy + s->pt[i + 1].vy;
            v[1].vz = base.vz;
            v[2].vx = base.vx + s->pt[i + 2].vx;
            v[2].vy = base.vy + s->pt[i + 2].vy;
            v[2].vz = base.vz;
            gte_ldv3(&v[0], &v[1], &v[2]);
            gte_rtpt();
            gte_stsxy3(&buf[i + 1], &buf[i + 2], &buf[i + 3]);
        }
        func_80180324(a0, a1, &buf[0], ot + z);
    }
}



#define ADDPRIM_801833F0(o, p)                                                 \
    (((PTag_801833F0 *)(p))->addr = ((PTag_801833F0 *)(o))->addr,              \
     ((PTag_801833F0 *)(o))->addr = (u32)(p))
#define SR3_801833F0(a) (((s32)(*(u16 *)(a) << 16)) >> 19)

void func_80180324(void *ent, void *spr, u32 *q, u32 *ot)
{
    extern u8 *D_800A5E60;
    register s32 zr __asm__("$0");

    Ft4_801833F0 *poly;
    Drm_801833F0 *dm;
    s32 vtx;
    u32 flags;
    s32 tp, abr, code, shift;
    u16 x;
    u32 y;
    s32 tpage, clut, cy;
    s32 su, sv, uu, vv;
    u16 fl;
    s32 i, m;
    u32 b;

    poly = (Ft4_801833F0 *)D_800A5E60;
    fl = *(u16 *)((s32)ent + 0x1E) & 0x8000;
    flags = *(u32 *)((s32)ent + 4);
    tp = (flags >> 24) & 3;
    shift = 2 - tp;
    x = *(u16 *)((s32)ent + 0x28) + (*(s16 *)((s32)spr + 4) >> shift);
    y = *(u16 *)((s32)ent + 0x2A) + *(u16 *)((s32)spr + 6);
    vtx = *(s32 *)((s32)ent + 0x20);
    D_800A5E60 += 0xF0;
    if (flags & 0x40000000) {
        code = 0x2E;
        abr = (flags >> 28) & 3;
    } else {
        code = 0x2C;
        abr = 1;
    }
    tpage = (tp << 7) | (abr << 5) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6) |
            ((y & 0x200) << 2);
    b = *(u8 *)((s32)ent + 0x27);
    cy = (b + 0x100) << 6;
    if (b < 0xE0) {
        clut = cy | 0x16;
    } else {
        clut = cy | 0x10;
    }
    {
        s32 t = ((x - ((tpage & 0xF) << 6)) << shift) +
                (*(u16 *)((s32)spr + 4) & ((1 << shift) - 1));
        su = t + zr;
        __asm__ __volatile__("" ::"r"(t + *(u8 *)((s32)spr + 2) - 1));
        __asm__ __volatile__("" ::"r"(t));
    }
    y = y & 0xFFFF;
    if (tpage & 0x10) {
        sv = y - 0x100;
    } else {
        sv = y + zr;
    }
    __asm__ __volatile__("" ::"r"(sv + *(u8 *)((s32)spr + 3) - 1));

    i = 1;
    uu = su;
    vv = sv;
    for (; i < 13; i += 2, poly++) {
        s32 k = (i - 1) * 4;
        __asm__ __volatile__("" ::"r"(i));
        poly->tag.len = 9;
        poly->code = code;
        poly->tpage = tpage;
        poly->u2 = su;
        poly->v2 = sv;
        poly->u0 = SR3_801833F0(vtx + k + 0x10) + uu;
        poly->v0 = SR3_801833F0(vtx + k + 0x12) + vv;
        poly->u1 = SR3_801833F0(vtx + i * 4 + 0x10) + uu;
        poly->v1 = SR3_801833F0(vtx + i * 4 + 0x12) + vv;
        /* k2 is recorded as a giv HERE, AFTER the u1/v1 mem giv - see (1). */
        {
            s32 k2 = (i + 1) * 4;
            poly->u3 = SR3_801833F0(vtx + k2 + 0x10) + uu;
            poly->v3 = SR3_801833F0(vtx + k2 + 0x12) + vv;
        }
        poly->clut = clut;
        __asm__ __volatile__("" ::"r"(i), "r"(i));
        poly->r0 = *(u8 *)((s32)ent + 0x24);
        poly->g0 = *(u8 *)((s32)ent + 0x25);
        poly->b0 = *(u8 *)((s32)ent + 0x26);
        poly->x0 = ((u16 *)q)[i * 2];
        poly->y0 = ((u16 *)q)[i * 2 + 1];
        poly->x1 = ((u16 *)q)[i * 2 + 2];
        poly->y1 = ((u16 *)q)[i * 2 + 3];
        poly->x2 = ((u16 *)q)[0];
        poly->y2 = ((u16 *)q)[1];
        poly->x3 = ((u16 *)q)[i * 2 + 4];
        poly->y3 = ((u16 *)q)[i * 2 + 5];
        if (fl != 0) {
            ADDPRIM_801833F0(&ot[*(s32 *)((s32)q + 0x34 + (i >> 1) * 4)], poly);
        } else {
            ADDPRIM_801833F0(ot, poly);
        }
    }
    poly[-1].x3 = ((u16 *)q)[2];
    poly[-1].y3 = ((u16 *)q)[3];
    poly[-1].u3 = su + SR3_801833F0(vtx + 0x10);
    poly[-1].v3 = sv + SR3_801833F0(vtx + 0x12);

    if (flags & 0x40000000) {
        dm = (Drm_801833F0 *)poly;
        if (fl != 0) {
            m = 0;
            D_800A5E60 += 0x30;
            do {
                m++;
                dm->tag.len = 1;
                dm->code0 = (abr << 5) | 0xE100000A;
                ADDPRIM_801833F0(&ot[*(volatile s32 *)((s32)q + 0x34)], dm);
                q = (u32 *)((s32)q + 4);
                dm++;
            } while (m < 6);
        } else {
            dm->code0 = (abr << 5) | 0xE100000A;
            D_800A5E60 += 8;
            dm->tag.len = 1;
            ADDPRIM_801833F0(ot, dm);
            /* Zero-byte live-range stretch: puts vtx's allocno priority at
             * 1232, inside the (1228, 1296) window - see (2).  Placement is
             * load-bearing; do not move this statement. */
            __asm__ __volatile__("" ::"r"(vtx));
        }
    }
}


void func_80180844(void) {
}

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8018084C);



extern s32 func_8004787C(s32 a0);

void func_80180894(s32 param_1, s32 param_2)
{
    extern void func_8012E32C(void);
    extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
    extern void *func_80010A08(s32);
    extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern s32 AddPrim(s32 a0, void *a1);
    extern void func_8012E28C(s32 arg0, s32 arg1);
    extern s32 D_80198008[];
    extern Ot_80182A78_80180894 D_800A651C[];

    s16 quad[4][4];
    u32 buf[2];
    s32 p, flag;
    s32 iVar1;
    s32 iVar2;
    u32 *bufPtr;
    s32 fp;
    s32 ang;
    s32 ang2;
    s32 packed0;
    s32 packed1;
    s32 y0;
    s32 y1;
    s32 otz;
    s32 c0;
    s32 c1;
    u8 *prim;

    if ((u32)(param_2 - 1) < 29) {
        func_8012E32C();
        fp = 0;
        iVar1 = func_8004787C((param_2 << 11) / 30);
        iVar2 = (iVar1 << 8) >> 12;
        ang = param_2 << 4;
        bufPtr = buf;

        for (; fp < 6; ) {
            func_8012B0B4(bufPtr, ang, 0x20);
            packed0 = buf[0];

            quad[0][0] = *(u16 *)(param_1 + 0) + packed0;
            y0 = packed0 >> 16;
            quad[0][1] = *(u16 *)(param_1 + 2);
            quad[0][2] = *(u16 *)(param_1 + 4) + y0;

            quad[2][0] = *(u16 *)(param_1 + 0) + (((s16)packed0 * (iVar1 * 3 + 0x1000)) >> 12);
            quad[2][1] = *(u16 *)(param_1 + 2) - iVar2;
            quad[2][2] = *(u16 *)(param_1 + 4) + ((y0 * (iVar1 * 3 + 0x1000)) >> 12);

            ang2 = ang + 0x2AA;
            func_8012B0B4(bufPtr, ang2, 0x20);

            packed1 = buf[0];

            quad[1][0] = *(u16 *)(param_1 + 0) + packed1;
            y1 = packed1 >> 16;
            quad[1][1] = *(u16 *)(param_1 + 2);
            quad[1][2] = *(u16 *)(param_1 + 4) + y1;

            quad[3][0] = *(u16 *)(param_1 + 0) + (((s16)packed1 * (iVar1 * 3 + 0x1000)) >> 12);
            quad[3][1] = *(u16 *)(param_1 + 2) - iVar2;
            quad[3][2] = *(u16 *)(param_1 + 4) + ((y1 * (iVar1 * 3 + 0x1000)) >> 12);

            prim = (u8 *)func_80010A08(0x24);
            c0 = D_80198008[fp];
            *(s32 *)(prim + 4) = c0;
            c1 = D_80198008[fp + 1];
            *(u8 *)(prim + 7) = 0x3A;
            *(s32 *)(prim + 0x1C) = 0;
            *(s32 *)(prim + 0x14) = 0;
            *(s32 *)prim = 0x8000000;
            *(s32 *)(prim + 0xC) = c1;
            otz = RotTransPers((s32)&quad[0], (s32)(prim + 8), &p, &flag);

            RotTransPers((s32)&quad[1], (s32)(prim + 0x10), &p, &flag);
            RotTransPers((s32)&quad[2], (s32)(prim + 0x18), &p, &flag);
            RotTransPers((s32)&quad[3], (s32)(prim + 0x20), &p, &flag);

            AddPrim(D_800A651C[(u16)D_800B9A02].a + (otz * 4), prim);
            func_8012E28C(otz, 1);
            fp++;
            ang = ang2;
        }
    }
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180B64);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180CA0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180D50);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180D98);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180E34);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80180E78);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8018105C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801810A4);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801812DC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181320);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801814A4);

extern void func_8012CBCC(s32 a0);
    void func_801814E4(s32 arg0) {
        if ((((s32 (*)(void))func_8012CBCC)() & 0x2000) != 0) {
            *(s16*)(arg0 + 0x2) = 1;
        }
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8018151C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181574);


extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801A0CE4;

void func_801815DC(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A0CE4);
    *(s16 *)((u8 *)arg0 + 0x2) = 0xe;
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181614);


extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801A0D4C;

void func_801816CC(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A0D4C);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x10;
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181704);


extern void func_8012A828(s32 a0, s32 a1);
    extern short D_801A0E04;
    void func_801817B8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 18;
        func_8012A828((int)arg0, (int)&D_801A0E04);
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801817E4);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801819D4);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181A14);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181A78);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181AB4);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181B34);

extern void func_8002A04C(s32 arg0);
    extern void func_8012C098(void);
    void func_80181B68(s32 param_1) {
        func_8002A04C(param_1);
        ((void (*)(s32))func_8012C098)(param_1);
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181B98);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181C0C);



extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_80181D2C(s32 arg0) {

    extern s32 *D_80126B78;
    extern u8 D_8019822C[];
    extern u8 D_801152A8[];
    s32 buf1[2];
    s32 buf2[2];

    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)D_8019822C, (s32)buf1);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)(D_8019822C + 8), (s32)buf2);
    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58), (s32)buf1, (s32)buf2) != 0) {
        func_8012F568(1, 0x18, *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), 0x18, (s32)buf2, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181DE0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80181F80);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182074);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801821DC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182358);


extern void (*D_8019823C[])(void);

void func_80182514(void *a0) {
    D_8019823C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182550);

void func_801825AC(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801825C0);

extern void func_80182810(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void*);
void func_801827D0(s32 a0) {
    func_80182810(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C218)(a0);
    }
}


extern void func_80017714(void *);
#define gte_ldv0_801837B0(r0) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_ldv3_801837B0(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps_801837B0() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt_801837B0() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4_801837B0() __asm__ volatile ("nop;nop;avsz4")
#define gte_stsxy_801837B0(r0) __asm__ volatile ( \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3_801837B0(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )
#define gte_stotz_801837B0(r0) __asm__ volatile ( \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stflg_801837B0(r0) __asm__ volatile ( \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define gte_SetRotMatrix_801837B0(r0) __asm__ volatile ( \
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
#define gte_SetTransMatrix_801837B0(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_80182810(s32 a0)
{

    extern u8 D_800AF630[];
    PKT_801837B0 pkt;   /* 0x10 */
    s32 flag1;          /* 0x48 */
    s32 flag2;          /* 0x4C */
    s32 otz;            /* 0x50 */
    u8 *base;
    s32 *m;
    s16 c, p, q;
    s32 d;

    c = *(s32 *)(a0 + 0x1C) * 15;
    base = D_800AF630;
    p = c;
    d = c >> 1;
    q = d;

    if ((*(u16 *)(a0 + 0x70) & 1) == 0) {
        pkt.rgb[0].b = pkt.rgb[1].b = p;
        pkt.rgb[0].r = pkt.rgb[1].r = pkt.rgb[0].g = pkt.rgb[1].g = q;
        c -= 0x10;
        p = c;
        {
            s32 e;          /* block-scoped: one pseudo per arm (§136/L1) */
            e = d - 0x10;
            q = e;
            if (c < 0) {
                p = 0;
            }
            if (e < 0) {
                q = 0;
            }
        }
        pkt.rgb[2].b = pkt.rgb[3].b = p;
        pkt.rgb[2].r = pkt.rgb[3].r = pkt.rgb[2].g = pkt.rgb[3].g = q;
    } else {
        pkt.rgb[0].r = pkt.rgb[1].r = p;
        pkt.rgb[0].g = pkt.rgb[1].g = pkt.rgb[0].b = pkt.rgb[1].b = q;
        c -= 0x10;
        p = c;
        {
            s32 e;          /* block-scoped: one pseudo per arm (§136/L1) */
            e = d - 0x10;
            q = e;
            if (c < 0) {
                p = 0;
            }
            if (e < 0) {
                q = 0;
            }
        }
        pkt.rgb[2].r = pkt.rgb[3].r = p;
        pkt.rgb[2].g = pkt.rgb[3].g = pkt.rgb[2].b = pkt.rgb[3].b = q;
    }

    pkt.code = 0x50000000;

    m = (s32 *)(base + 0x18);
    gte_SetRotMatrix_801837B0(m);
    gte_SetTransMatrix_801837B0(m);

    gte_ldv3_801837B0((SV_801837B0 *)(a0 + 0xFC), (SV_801837B0 *)(a0 + 0x104),
                      (SV_801837B0 *)(a0 + 0xEC));
    gte_rtpt_801837B0();
    gte_stflg_801837B0(&flag1);
    gte_stsxy3_801837B0(&pkt.v[0], &pkt.v[1], &pkt.v[2]);
    gte_ldv0_801837B0((SV_801837B0 *)(a0 + 0xF4));
    gte_rtps_801837B0();
    gte_stflg_801837B0(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy_801837B0(&pkt.v[3]);
    gte_avsz4_801837B0();
    gte_stotz_801837B0(&otz);
    if ((flag1 & 0xFFFFEFFF) == 0) {
        pkt.v[0].vz = (s16)otz;
        func_80017714(&pkt.v[0]);
    }

    gte_ldv3_801837B0((SV_801837B0 *)(a0 + 0xEC), (SV_801837B0 *)(a0 + 0xF4),
                      (SV_801837B0 *)(a0 + 0xDC));
    gte_rtpt_801837B0();
    gte_stflg_801837B0(&flag1);
    gte_stsxy3_801837B0(&pkt.v[0], &pkt.v[1], &pkt.v[2]);
    gte_ldv0_801837B0((SV_801837B0 *)(a0 + 0xE4));
    gte_rtps_801837B0();
    gte_stflg_801837B0(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy_801837B0(&pkt.v[3]);
    gte_avsz4_801837B0();
    gte_stotz_801837B0(&otz);
    if ((flag1 & 0xFFFFEFFF) == 0) {
        pkt.v[0].vz = (s16)otz;
        func_80017714(&pkt.v[0]);
    }
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182B48);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182BB0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80182C28);


/* --- types: ALREADY PRESENT in src/shared/engine_types.h (pulled into the real TU
 * via engine_core.h). Delete these four typedefs when banking into
 * src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c — they exist verbatim at
 * engine_types.h:1168 (MATRIX), :1726 (CV_801837B0), :3787..:3793 (SV/PKT).
 * The immediate neighbour func_801837B0 (line 5484, MATCHed) uses PKT_801837B0
 * with the identical v[4]/rgb[4]/code layout and the same `pkt.code = 0x50000000`. */






void func_80182DD8(s32 a0, void *a1, s32 a2)
{
    extern u16 D_800B99DA;
    extern u8 D_801980B8[];
    extern u8 D_801980CC[];
    extern s32 func_80017758(void *a0, void *a1);   /* canon, TU line 1761 */
    extern void func_801832EC(s32 a0, void *a1, s32 a2, MATRIX *a3);
    MATRIX m;               /* sp+0x10 */
    PKT_801837B0 pkt;       /* sp+0x30 */
    u8 *p;
    s32 i;

    func_801832EC(a0, a1, a2, &m);

    if (D_800B99DA & 1) {
        pkt.rgb[1].b = 0x58;
    } else {
        pkt.rgb[1].b = 0x48;
    }

    p = D_801980B8;
    pkt.rgb[0].r = pkt.rgb[0].g = pkt.rgb[0].b = 0;
    pkt.rgb[2].r = pkt.rgb[2].g = pkt.rgb[2].b = 0;
    pkt.rgb[3].r = pkt.rgb[3].g = pkt.rgb[3].b = 0;
    pkt.code = 0x50000000;
    pkt.v[0].vz = pkt.v[2].vz = pkt.v[3].vz = 0;
    pkt.v[1].vx = pkt.v[1].vy = pkt.v[1].vz = 0;
    pkt.rgb[1].r = pkt.rgb[1].g = pkt.rgb[1].b >> 2;

    for (i = 0; i < 4; i++) {
        pkt.v[0].vx = (s8)*p++;
        pkt.v[0].vy = (s8)*p++;
        pkt.v[2].vx = (s8)*p++;
        pkt.v[2].vy = (s8)*p++;
        pkt.v[3].vx = (s8)*p++;
        pkt.v[3].vy = (s8)*p--;
        func_80017758(&pkt.v[0], &m);
    }

    p = D_801980CC;
    pkt.v[1].vz = -0x12;
    pkt.v[0].vy = pkt.v[2].vy = pkt.v[3].vy = 0;
    pkt.v[1].vx = pkt.v[1].vy = 0;
    pkt.rgb[1].b <<= 1;
    pkt.rgb[1].r = pkt.rgb[1].g <<= 1;

    for (i = 0; i < 4; i++) {
        pkt.v[0].vx = (s8)*p++;
        pkt.v[0].vz = (s8)*p++;
        pkt.v[2].vx = (s8)*p++;
        pkt.v[2].vz = (s8)*p++;
        pkt.v[3].vx = (s8)*p++;
        pkt.v[3].vz = (s8)*p--;
        if (i == 2) {
            pkt.rgb[3].b = pkt.rgb[1].b;
            pkt.rgb[3].r = pkt.rgb[3].g = pkt.rgb[1].r;
        } else if (i == 3) {
            pkt.rgb[3].r = pkt.rgb[3].g = pkt.rgb[3].b = 0;
            pkt.rgb[0].b = pkt.rgb[1].b;
            pkt.rgb[0].r = pkt.rgb[0].g = pkt.rgb[1].r;
        }
        func_80017758(&pkt.v[0], &m);
    }
}



/* func_80183040 (ov_SC02_041_jr_8017BEBC, 171 ins) — byte-matched.
 *
 * Builds a GTE 4-vertex/4-colour packet on the stack and pushes it three times
 * through func_80017758 (the shared "transform + link prim" helper, see the
 * sibling func_80182BDC in ov_SC03_099_jr_8017BEBC.c, which uses the identical
 * 0x00 verts / 0x20 colours / 0x30 code layout).
 *
 * Layout notes that had to be right for the frame to come out as 0x78:
 *   - mtx[0x20] is declared FIRST so it takes the low local slot (sp+0x10) and
 *     the packet takes sp+0x30 (MIPS frame grows UP; slots go in decl order).
 *   - locals total 0x54 -> MIPS_STACK_ALIGN 0x58, +0x10 outgoing args +12 saved
 *     regs = 0x74 -> 0x78.
 *
 * Two idioms this needed (both byte-verified here):
 *   1. The colour/vertex zero-fills are CHAINED assignments; `a = b = c = 0`
 *      emits the stores RIGHT-TO-LEFT, which is what produces the descending
 *      0x52/0x51/0x50 and 0x4C/0x44/0x34 store orders.
 *   2. The brightness must be stored into the packet IN EACH ARM (cross-jump
 *      then merges the three `sb`s into one at the join). Hoisting it into an
 *      `s32 br` local instead lets cse/combine forward the stored value into
 *      the `>> 2`, which DELETES the `lbu 0x54(sp)` reload (-1 instruction).
 *   3. The inner test is written `!(flags & 2) -> 0x80` so gcc's
 *      jump-if-false lands `bnez` (with 0xC0 stolen into the delay slot from
 *      the branch target), not `beqz` with 0x80.
 */

void func_80183040(s32 a0, s32 a1, s32 a2)
{
    typedef struct {
        s16 vx, vy, vz, pad;
    } SV_80183FE0_80183040;

    typedef struct {
        SV_80183FE0_80183040 v[4];    /* 0x00 */
        u8          c[4][4]; /* 0x20 */
        u32         code;    /* 0x30 */
    } Prim_80183FE0_80183040;         /* 0x34 */

    extern void func_801832EC(s32 a0, s32 a1, s32 a2, void *a3);
    extern s32 func_80017758(void *a0, void *a1);
    extern u16 D_800B99DA;
    extern u8 D_80188C74[];
    extern u8 D_80188C88[];

    u8 mtx[0x20];
    Prim_80183FE0_80183040 p;
    u8 *q;
    s32 i;

    func_801832EC(a0, a1, a2, mtx);

    p.v[0].vz = p.v[2].vz = p.v[3].vz = 0;
    p.v[1].vx = p.v[1].vy = p.v[1].vz = 0;
    if (D_800B99DA & 1) {
        p.c[1][0] = 0xA0;
    } else if (!(D_800B99DA & 2)) {
        p.c[1][0] = 0x80;
    } else {
        p.c[1][0] = 0xC0;
    }
    p.c[0][0] = p.c[0][1] = p.c[0][2] = 0;
    p.c[2][0] = p.c[2][1] = p.c[2][2] = 0;
    p.c[3][0] = p.c[3][1] = p.c[3][2] = 0;
    p.code = 0x50000000;
    p.c[1][1] = p.c[1][2] = p.c[1][0] >> 2;

    q = D_80188C74;
    for (i = 0; i < 4; i++) {
        p.v[0].vx = (s8)*q++;
        p.v[0].vy = (s8)*q++;
        p.v[2].vx = (s8)*q++;
        p.v[2].vy = (s8)*q++;
        p.v[3].vx = (s8)*q++;
        p.v[3].vy = (s8)*q--;
        func_80017758(&p, mtx);
    }

    p.v[0].vy = p.v[2].vy = p.v[3].vy = 0;
    p.v[1].vx = p.v[1].vy = 0;
    p.v[1].vz = -0x20;
    q = D_80188C88;
    for (i = 0; i < 4; i++) {
        p.v[0].vx = (s8)*q++;
        p.v[0].vz = (s8)*q++;
        p.v[2].vx = (s8)*q++;
        p.v[2].vz = (s8)*q++;
        p.v[3].vx = (s8)*q++;
        p.v[3].vz = (s8)*q--;
        func_80017758(&p, mtx);
        if (i == 1) {
            p.v[1].vz = 0x20;
            q += 2;
        }
    }
    q += 2;

    p.v[0].vx = 0;
    p.v[0].vz = -0x20;
    p.c[0][0] = p.c[1][0];
    p.c[0][1] = p.c[0][2] = p.c[1][1];
    for (i = 0; i < 2; i++) {
        p.v[2].vx = (s8)*q++;
        p.v[2].vz = (s8)*q++;
        p.v[3].vx = (s8)*q++;
        p.v[3].vz = (s8)*q++;
        func_80017758(&p, mtx);
    }
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801832EC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183438);


extern void (*D_80198294[])(void);

void func_80183614(void *a0) {
    D_80198294[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80183650(s32 param_1)
{

    extern u8 D_80198258[];
    extern u8 D_80198264[];
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_80198258;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x5b;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80198264);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(void);
void func_801836CC(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_8018370C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801838EC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801839FC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183B14);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183B84);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183BEC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183C24);

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8002AC00(s32 arg0);

void func_80183CCC(void) {
    func_8002D4C8(0xA9E, 0);
    func_8002AC00(0x14);
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183CF8);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183D40);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183DDC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183E80);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183F4C);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80183FF8);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80184238);


extern void (*D_801AC550[])(void);

void func_80184358(void *a0) {
    D_801AC550[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8002AC00(s32 arg0);
    extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    void func_80184394(int param_1) {
        ((int (*)(int))func_8002AC00)(0x16);
        ((int (*)(int, int))func_80131E00)(param_1, 0x11);
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801843CC);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801843E0);

void func_8018447C(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x2;
    }


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80184488);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_801844F0);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80184560);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80184688);

INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80184708);

extern void (*D_801AF3DC[])(void);

void func_801847D8(void *a0) {
    D_801AF3DC[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32, s32);
/* not declared anywhere in the TU */
extern void func_80184EC0(void);

void func_80184814(void *a0) {

    extern s32 D_801AF134[];
    extern u8 D_801AF0CC[];
    extern u8 D_80185EB8[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801AF0CC);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801AF134[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80184EC0);
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
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80185EB8);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_801848E8(void *a0) {
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


void func_80184910(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80184918(void *a0) {

    extern s32 D_801AF318;
    extern s32 D_801AF304;
    extern s32 D_801AF300;
    extern s32 D_801AF398;
    extern s32 D_801AF32C;
    extern s32 D_801AF1F8[];
    extern s32 D_801AF27C[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801AF318 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801AF300 = 0;
                D_801AF304 = D_801AF27C[v0];
            } else {
                D_801AF304 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801AF27C[v0], 1);
                D_801AF300 = 2;
            }
        } else {
            D_801AF318 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801AF300 = 0;
            D_801AF304 = D_801AF1F8[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801AF32C);
    } else {
        p = &D_801AF398;
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
extern s32 func_80184C68(void);

void func_80184A64(void *arg0) {

    extern s32 D_801AF134[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801AF134[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801AF134[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80184C68() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    void func_80184B84(s32 arg0) {
        *(s16 *)(arg0 + 0x2) = 2;
        func_8012C218(*(void **)(arg0 + 0xcc));
    }


void func_80184BB0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80184BC0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_80184BD0(void *a0) {

    extern s32 D_801AF134[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801AF134[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_80184C10(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
    s32 func_80184C44(void) {
        return ((u32)((s32 (*)(void))func_80174764)() ^ 1) < 1;
    }




extern s32 func_80029178(s32 arg);

s32 func_80184C68(void) {

    extern s32 D_801AF134[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801AF134[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


extern void (*D_801AF404[])(void);

void func_80184CCC(void *a0) {
    D_801AF404[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);

void func_80184D08(void *a0) {

    extern u8 D_801AF100[];
    extern u8 D_801AFAC4[];
    extern u8 D_801AF8A4[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801AF100) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AFAC4);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AF8A4);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80184D90(void *a0) {

    extern u8 D_801AF8B4[];
    extern u8 D_801AF9BC[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AF8B4);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AF9BC);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_80184E50 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801AFAC4, else
 * D_801AF8A4), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `((void (*)(s32, void *))func_8012A828)(entity, D_801AFAC4 / D_801AF8A4)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32, s32);

void func_80184E50(void *a0) {

    extern u8 D_801AFAC4[];
    extern u8 D_801AF8A4[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AFAC4);
        } else {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801AF8A4);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801AF3F4[];
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

s32 aF8018A224() __asm__("func_80184EC0");

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

    RotTransSV(D_801AF3F4, sv0, &flag);
    RotTransSV(D_801AF3F4 + 8, sv1, &flag);

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



extern void func_80019064(void *a0);

void func_80184FB8(void *a0) {

    extern u8 D_801B2660;
    extern void (*D_801B2688[])(void *);
    func_80019064(&D_801B2660);
    D_801B2688[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_80185010(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_80185060(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


INCLUDE_ASM("asm/ov_SC04_007/nonmatchings/ov_SC04_007_jr_8017BEBC", func_80185060);


/* func_801850CC @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_801850CC --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_801850CC.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_80185220 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_80185298` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
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
 *   if (func_80185298() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
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
extern s32 func_80185298(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_80185220(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_801850CC(s32 param_1)
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
        iVar1 = func_80185298();
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
        func_80185220(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_80185220 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
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
 *   func_80185220  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_80185220(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_80185274(void)
{
    extern u8 D_801B54EB;
    s32 i = 19;
    u8 *p = &D_801B54EB;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_80185298(void)
{

    extern u8 D_801B54D8[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801B54D8;
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


extern void (*D_801B2694[])(void);

void func_801852DC(void *a0) {
    D_801B2694[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801B54EC + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8018550C(void*);
extern void func_801854DC(s32*);
extern int rand(void);

void func_80185318(int param_1)
{

    extern unsigned char D_801B54EC[];
    register int iVar3 __asm__("$16");
    register int iVar3b __asm__("$19");
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801B54EC + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    *(int *)(param_1 + 0x20) = iVar3;
    iVar3b = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8018550C)(iVar5);
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
        ((void (*)(int))func_801854DC)(param_1);
    }
}




extern s32 func_80185520(s32 *a0, s32 a1);
extern void func_801854DC(s32 *a0);

void func_80185464(s32 *a0)
{

    extern unsigned char D_801B54EC[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801B54EC + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_80185520(a0, table_base) == 0) {
            return;
        }
    }

    func_801854DC(a0);
}



















extern void func_80146C3C(void);
void func_801854DC(s32 *param_1)
{

    extern s8 D_801B54D8;
  int new_var;
register s32 p __asm__("$4");
register s32 r __asm__("$3");
  p = (s32) (&D_801B54D8);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}



void func_8018550C(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_80185520 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_80185520(s32 *a0, s32 a1);
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
s32 func_80185520(s32 *a0, s32 a1) {
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


extern void (*D_801B26CC[])(void);

void func_80185588(void *a0) {
    D_801B26CC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_801855C4(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_80185660(s32 param_1);

void func_80185610(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_80185660(param);
    }
}


void func_80185658(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_801857C4();

void func_80185660(s32 param_1) {

    extern u32 *D_801B26C4[];
    extern Blk8 D_801B26E0[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_801B26C4[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_801B26E0[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_801857C4(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
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

extern SVECTOR_8017E6D8 D_801B59EC[4];
extern struct PW8017E6D8 D_801B5A0C;
extern struct PW8017E6D8 D_801B5A10;
extern u8 D_801B5A14, D_801B5A15, D_801B5A16, D_801B5A18, D_801B5A19, D_801B5A1A;
extern int D_801B5A1C;

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

void func_801857C4(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801B59EC[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801B5A1C = 0x50000000;
        D_801B5A14 = 0;
        D_801B5A15 = 0;
        D_801B5A16 = 0;
        D_801B5A18 = 0;
        D_801B5A19 = 0;
        D_801B5A1A = 0;
    }
    D_801B5A0C = h[0];
    D_801B5A10 = h[1];

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






