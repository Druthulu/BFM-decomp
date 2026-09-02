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
extern u8 D_80188D20;
extern u8 D_80188C90;
extern u8 D_80188C6C;
extern u8 D_80188C48;
extern u8 D_80188CFC;
extern u8 D_80188CD8;
extern u8 D_80188CB4;
extern u8 D_80188C24;
extern void func_80145934(void);
extern u8 D_80188DB0;
extern u8 D_80188D8C;
extern u8 D_80188D68;
extern u8 D_80188D44;
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
extern unsigned char D_801881A8[];
extern unsigned char D_801881D8[];
extern unsigned char D_80188228[];
extern unsigned char D_80188258[];
extern unsigned char D_80188288[];
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
extern void (*D_801882D8[])(void *);
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
extern s32 D_801883A0[];
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
extern u8 D_80188428[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188430;
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
extern int D_8019A548;
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
extern s32 D_8019A54C;
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
extern s32 D_80188460;
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
extern void (*D_80188508[])(void);
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
extern void (*D_8018852C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018851C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188540[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018854C[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018855C[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80188574[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80188564;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80188588[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801885A4[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80188594;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801885B8[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801885CC[])(void);
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
extern s32 D_801885E0;
extern void (*D_80188608[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801885E8;
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
extern int (*D_80188654[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80188658[])(void);
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
extern unsigned short D_80188ABC[];
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
extern void (*D_80188ACC[])(void);
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
extern int D_8019A580;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188AF4[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188AD4;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188AE4;
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
extern void (*D_80188B34[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188B3C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188B08;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188B48[])(void);
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
extern u8 D_80188B18;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_8019A588;
extern s32 D_8019A594;
extern s32 D_8019A598;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188B84[])(s32 *);
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
extern s32 D_80188B58[];
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
extern s32 D_8019A590;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188DD4[])(void);
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
extern char D_80188BF4[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80188E78[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80188FCC[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188DE8;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80188FD4[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80188DF8;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80188E18;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80188FDC[])(void);
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
extern void (*D_80189004[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189010[])(void);
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
extern void (*D_80188E84[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801890B4;
extern void func_8015D380(s32 a0);
extern unsigned char D_80188198[];
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
extern unsigned char D_801890C8[];
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
extern s8 D_80189104[];
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
extern u16 D_8018914C;
extern u16 D_8018914E;
extern u16 D_80189150;
extern s32 D_80189154;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018915C;
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
extern int D_80188E68;
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
extern unsigned int D_801891E0[];
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
extern void (*D_80189290[])(void);
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
extern u16 D_801892C0[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189324;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_8019A5A0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189348[])(void);
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
extern int D_8019A5F8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189390[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189380;
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
extern char D_80199D08[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80189398[])(void);
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
extern void (*D_801893EC[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801893B4;
extern s16 D_801893E8;
extern s16 D_801893E6;
extern s16 D_801893E4;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801893F8[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_8019A658;
extern u8 D_8019A659;
extern u8 D_8019A65A;
extern u8 D_8019A65B;
extern u8 D_8019A65C;
extern u8 D_8019A65D;
extern u8 D_8019A65E;
extern u8 D_8019A65F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189408[])(void);
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
extern s32 D_8019A698;
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
extern void (*D_8018944C[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801894C8[];
extern s32 D_801894E8[];
extern u8 D_80189564[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80189584[];
extern u8 D_801895A4[];
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
extern void (*D_80189640[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801896BC[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_80199D18;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801896C8[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801896D0[])(void);
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
extern void (*D_80189798[])(void);
extern void func_80166618(void *a0);
extern void (*D_801897A8[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801897B8[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801897C4[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189724[];
extern u8   D_80189738[];
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
extern void (*D_801897DC[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801897E4[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801897EC[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801897F4[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801897FC[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189804[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018980C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801898C0[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801898C8[])(void);
extern void func_80169F00(void *a0);
extern char D_80189878[];
extern char D_80189838[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189900[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018990C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80189954[])(void);
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
extern void (*D_801899D0[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_8019A9B8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801899C4[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189A08[];
extern unsigned short D_80189A10[];
extern unsigned short D_80189A18[];
extern unsigned char D_8019A9C0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_8019A9B8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189A20[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_8019AAF4;
extern M2C_UNK D_8019AAF8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_8019AA80;
extern void (*D_80189A50[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8019AAFC[];
extern u8 D_8019AB04[];
extern u8 D_8019AAB4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189A58[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189A74[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189A7C[])(void);
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
extern void (*D_80189AE4[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189A88;
extern u8 D_80189A94;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80189B18[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189B20[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189B74[])(void);
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
extern u16 D_80189BA8[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189B98[];
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
extern s32 D_80189BC4;
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
extern void (*D_80189C3C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189C44[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189C4C[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189C54[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189C5C[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189C64[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189C70[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189C7C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189C88[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189C98[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189CA8[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189CB0[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189CB8[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189CC0[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189CC8[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80189CD0[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80189CD8[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80189CE0[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80189CE8[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80189CF0[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80189CF8[])(void);
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
extern void (*D_80189D00[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80189D08[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80189D10[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80189D18[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80189D20[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80189D28[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80189D30[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80189D38[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80189D40[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80189D48[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80189D50[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80189D58[])(void);
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
extern void (*D_80189D9C[])(void);
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
extern M2C_UNK D_80189D60;
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
extern void (*D_80189DCC[])(void);
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
extern void (*D_80189E08[])(void);
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
extern void (*D_80189E60[])();
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
extern void (*D_80189E70[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80189E78[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80189FE0[])();
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
extern void (*D_80189FEC[])();
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
extern M2C_UNK D_80199F60;
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
extern s16 D_801A0060;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_8019B238;
extern short D_801A00D4;
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
extern s32 D_8019B664;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_8019B68C;
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
extern s16 D_8019B648;
extern s32 func_8017A3B0(void);
extern short D_8019B684;
extern short D_8019B680;
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
extern s16 D_8019B64C;
extern u16 D_8019B6CC;
extern u16 D_8019B6CE;
extern u16 D_8019B6D0;
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
extern s16 D_8019B6C4;
extern s16 D_8019B6C6;
extern s16 D_8019B6C8;
extern s16 D_8019B6BC;
extern s16 D_8019B6BE;
extern s16 D_8019B6C0;
extern void func_8017B7A8(void);
extern s16 D_8019B6DC;
extern s16 D_8019B6DE;
extern s16 D_8019B6E0;
extern s16 D_8019B6E4;
extern s16 D_8019B6E6;
extern s16 D_8019B6E8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_8019B6D4;
extern short D_8019B6D6;
extern short D_8019B6D8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_8019B66C;
extern SV4 D_8019B674;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_8019B694[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_8019B690)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018A1C8[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018A228[])(void);
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

void func_8017C8D0(s32 arg0)
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


extern s32 D_8019B7B8;

void func_8017D7B0(void) {
    s32 i = 0x29C8;
    do {
        *(s16 *)((s32)&D_8019B7B8 + i) = 0;
        i -= 0x38;
    } while (i >= 0);
}


extern s32 func_8017D8D8(void);
extern void func_8017D920();

s32 func_8017D7D4(s32 a0, s32 a1, s32 a2, s8 a3) {
    s32 handle;
    *(s16 *)(a0 + 6) = 0;
    handle = func_8017D8D8();
    if (handle != 0) {
        func_8017D920(handle, a0, a1, a2, a3);
    }
    return handle;
}


s32 func_8017D858(s32 a0, s32 a1, s32 a2, s8 a3) {
    s32 handle;
    handle = func_8017D8D8();
    if (handle != 0) {
        func_8017D920(handle, a0, a1, a2, a3);
    }
    return handle;
}


extern s32 D_8019B7B8;
s32 func_8017D8D8(void) {
    s32 i;
    u8 *p;
    s32 j;
    for (i = 0, p = ((u8 *)&D_8019B7B8), j = 0; i < 0xC0; p += 0x38, i++, j += 0x38) {
        if (((u8 *)&D_8019B7B8)[j] == 0) return (s32)p;
    }
    return 0;
}


/* §324/§99 — the TU already declares `extern void func_8017D920();` (no prototype).
 * A prototyped definition whose 5th param is `u8` is NOT compatible with it (u8 is
 * changed by the default argument promotions) => `conflicting types`. The K&R
 * definition carries no prototype, is compatible, and is byte-neutral: the narrow
 * param still emits `lbu 0x10($sp)`. */
void func_8017D920(param_1, param_2, param_3, param_4, param_5)
u16 *param_1;
u16 *param_2;
u16 *param_3;
u8 *param_4;
u8 param_5;
{
    u16 w;
    s8 d = param_5;

    *param_1 = param_4[3] * 0x100 + 1;
    param_1[2] = param_2[0];
    param_1[3] = param_2[1];
    param_1[4] = param_2[2];
    w = param_2[3];
    param_1[5] = w;
    if (param_3 != NULL) {
        param_1[5] = w & 0xEFFF;
        param_1[6] = param_3[0];
        param_1[7] = param_3[1];
        param_1[8] = param_3[2];
    } else {
        param_1[5] = w | 0x1000;
    }
    param_1[0x12] = param_4[0] * 0x100;
    param_1[0x13] = param_4[1] * 0x100;
    param_1[0x14] = param_4[2] * 0x100;
    if (d < 0) {
        d = -d;
        param_1[0x17] = 0;
        param_1[0x16] = 0;
        param_1[0x15] = 0;
    } else {
        param_1[0x15] = param_1[0x12] / d;
        param_1[0x16] = param_1[0x13] / d;
        param_1[0x17] = param_1[0x14] / d;
        if (param_1[0x15] == 0) {
            param_1[0x15] = 1;
        }
        if (param_1[0x16] == 0) {
            param_1[0x16] = 1;
        }
        if (param_1[0x17] == 0) {
            param_1[0x17] = 1;
        }
    }
    param_1[1] = d;
    *(u32 *)&param_1[0x1A] = 0;
    *(u32 *)&param_1[0x18] = 0;
}


extern void func_8017E5D4(s32);
extern void func_8017DC80(void);

typedef union {
    u8 b;
    u16 h[0x1C];
    s16 s[0x1C];
} R38;

extern R38 A_B8[0xC0] __asm__("D_8019B7B8");
extern R38 A_BA[0xC0] __asm__("D_8019B7BA");
extern R38 A_DC[0xC0] __asm__("D_8019B7DC");
extern R38 A_E0[0xC0] __asm__("D_8019B7E0");
extern R38 A_E2[0xC0] __asm__("D_8019B7E2");
extern R38 A_E4[0xC0] __asm__("D_8019B7E4");
extern R38 A_E6[0xC0] __asm__("D_8019B7E6");

void func_8017DAEC(void)
{
    s32 i;
    R38 *e;
    s16 t;
    s16 d;
    s32 st;

    for (i = 0; i < 0xC0; i++) {
        st = A_B8[i].b;
        if (st < 2) {
            continue;
        }
        t = A_BA[i].s[0];
        if (t == 0) {
            continue;
        }
        d = t - 1;
        e = &A_B8[i];
        e->h[1] = d;
        if (A_BA[i].s[0] == 0) {
            ((void (*)(void *))func_8017E5D4)(e);
            continue;
        }
        if (A_DC[i].h[0] < A_E2[i].h[0]) {
            A_DC[i].h[0] = 0;
        } else {
            A_DC[i].h[0] = A_DC[i].h[0] - A_E2[i].h[0];
        }
        if (A_DC[i].h[1] < A_E4[i].h[0]) {
            A_DC[i].h[1] = 0;
        } else {
            A_DC[i].h[1] = A_DC[i].h[1] - A_E4[i].h[0];
        }
        if (A_E0[i].h[0] < A_E6[i].h[0]) {
            A_E0[i].h[0] = 0;
        } else {
            A_E0[i].h[0] = A_E0[i].h[0] - A_E6[i].h[0];
        }
    }
    func_8017DC80();
}


/* func_8017DC80 — VERBATIM-ASM BANK (cookbook §265).
 * Target .s carries the splat tag "Handwritten function" (line 1): interleaved
 * callee-save/base materialisation prologue, hand-placed GTE hazard nops, fall-through
 * loop head — no -O2 C schedule reaches it (~20 C drafts plateaued at LENGTH-DRIFT/-33).
 * Recovered semantics (for the eventual real decomp): walks the 0xC0-record table at
 * D_8019B7B8 (stride 0x38); records with low byte < 2 project v3(vb, r+0xC, va)+v0(r+0x1C),
 * clamp OTZ by the mode word at c-0x1F (0xC000 subtract-clamp / 0x4000 add), skip if
 * flag&~0x1000 or otz>=0x1000, fill a POLY_G4 (0x24) or POLY_F3-ish (0x14) from c[-4..0]
 * and tex-page p+0x25/27/29, setcode by n<4, addPrim into OT bucket
 * D_800A6610[D_800B9A02<<14] + n*4, and chain a DR_TPAGE ((n<<5)&0x9FF)|0xE1000000 when
 * n<4.  Immediates are DECIMAL throughout (maspsx rejects hex in __asm__ strings, §265). */

__asm__(".text\n.align 2\n.globl func_8017DC80\n.ent\tfunc_8017DC80\n"
"func_8017DC80:\n.frame $sp,112,$31\n.mask 3238002688,-16\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -112\n"
"lui $a0, %hi(D_800AF648)\n"
"addiu $a0, $a0, %lo(D_800AF648)\n"
"sw $s4, 88($sp)\n"
"lui $s4, %hi(D_8019B7B8)\n"
"addiu $s4, $s4, %lo(D_8019B7B8)\n"
"sw $s3, 84($sp)\n"
"lui $s3, 255\n"
"ori $s3, $s3, 65535\n"
"sw $s7, 100($sp)\n"
"lui $s7, 65280\n"
"sw $s2, 80($sp)\n"
"addiu $s2, $s4, 41\n"
"sw $s5, 92($sp)\n"
"addiu $s5, $s4, 20\n"
"sw $s6, 96($sp)\n"
"addiu $s6, $s4, 4\n"
"lui $v0, %hi(D_800B9A02)\n"
"lhu $v0, %lo(D_800B9A02)($v0)\n"
"lui $v1, %hi(D_800A6610)\n"
"addiu $v1, $v1, %lo(D_800A6610)\n"
"sw $ra, 108($sp)\n"
"sw $fp, 104($sp)\n"
"sw $s1, 76($sp)\n"
"sw $s0, 72($sp)\n"
"sw $zero, 48($sp)\n"
"sll $v0, $v0, 14\n"
"jal func_80052E38\n"
"addu $fp, $v0, $v1\n"
".L8017DCF4:\n"
"lhu $v1, 0($s4)\n"
"nop\n"
"andi $v0, $v1, 255\n"
"slti $v0, $v0, 2\n"
"bnez $v0, .L8017E190\n"
"nop\n"
"lhu $v0, -31($s2)\n"
"nop\n"
"andi $v0, $v0, 4096\n"
"bnez $v0, .L8017DF50\n"
"srl $s0, $v1, 8\n"
"jal func_80010A08\n"
"addiu $a0, $zero, 36\n"
"addu $a1, $v0, $zero\n"
"addiu $v0, $zero, 8\n"
"sb $v0, 3($a1)\n"
"addiu $v0, $zero, 56\n"
"sb $v0, 7($a1)\n"
"addiu $v0, $s4, 12\n"
"lwc2 $0, 0($s6)\n"
"lwc2 $1, 4($s6)\n"
"lwc2 $2, 0($v0)\n"
"lwc2 $3, 4($v0)\n"
"lwc2 $4, 0($s5)\n"
"lwc2 $5, 4($s5)\n"
"nop\n"
"nop\n"
"rtpt\n"
"addiu $v0, $sp, 16\n"
"cfc2 $12, $31\n"
"nop\n"
"sw $12, 0($v0)\n"
"addiu $4, $sp, 20\n"
"addiu $3, $sp, 24\n"
"addiu $2, $sp, 28\n"
"swc2 $12, 0($4)\n"
"swc2 $13, 0($3)\n"
"swc2 $14, 0($2)\n"
"addiu $2, $s4, 28\n"
"lwc2 $0, 0($2)\n"
"lwc2 $1, 4($2)\n"
"nop\n"
"nop\n"
"rtps\n"
"addiu $2, $sp, 32\n"
"cfc2 $12, $31\n"
"nop\n"
"sw $12, 0($2)\n"
"lw $2, 16($sp)\n"
"lw $3, 32($sp)\n"
"nop\n"
"or $2, $2, $3\n"
"sw $2, 16($sp)\n"
"addiu $2, $sp, 36\n"
"swc2 $14, 0($2)\n"
"nop\n"
"nop\n"
"avsz4\n"
"addiu $2, $sp, 40\n"
"swc2 $7, 0($2)\n"
"lw $2, 16($sp)\n"
"addiu $3, $zero, -4097\n"
"and $2, $2, $3\n"
"bnez $2, .L8017E190\n"
"nop\n"
"lh $2, -31($s2)\n"
"lw $17, 40($sp)\n"
"andi $4, $2, 49152\n"
"beqz $4, .L8017DE30\n"
"addu $3, $2, $zero\n"
"ori $2, $zero, 49152\n"
"bne $4, $2, .L8017DE2C\n"
"andi $2, $3, 4095\n"
"subu $17, $17, $2\n"
"bgez $17, .L8017DE34\n"
"sltiu $2, $17, 4096\n"
"j .L8017DE30\n"
"addu $17, $zero, $zero\n"
".L8017DE2C:\n"
"addu $17, $17, $2\n"
".L8017DE30:\n"
"sltiu $2, $17, 4096\n"
".L8017DE34:\n"
"beqz $2, .L8017E190\n"
"nop\n"
"lw $2, 20($sp)\n"
"nop\n"
"sh $2, 8($5)\n"
"lw $3, 24($sp)\n"
"sra $2, $2, 16\n"
"sh $2, 10($5)\n"
"sh $3, 16($5)\n"
"lw $4, 28($sp)\n"
"sra $3, $3, 16\n"
"sh $3, 18($5)\n"
"sh $4, 24($5)\n"
"lw $2, 36($sp)\n"
"sra $4, $4, 16\n"
"sh $4, 26($5)\n"
"sh $2, 32($5)\n"
"sra $2, $2, 16\n"
"sh $2, 34($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"beqz $2, .L8017DF0C\n"
"nop\n"
"lbu $2, -4($s2)\n"
"nop\n"
"sb $2, 12($5)\n"
"sb $2, 4($5)\n"
"lbu $2, -2($s2)\n"
"nop\n"
"sb $2, 13($5)\n"
"sb $2, 5($5)\n"
"lbu $2, 0($s2)\n"
"nop\n"
"sb $2, 14($5)\n"
"sb $2, 6($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 37($2)\n"
"nop\n"
"sb $2, 28($5)\n"
"sb $2, 20($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 39($2)\n"
"nop\n"
"sb $2, 29($5)\n"
"sb $2, 21($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 41($2)\n"
"nop\n"
"sb $2, 30($5)\n"
"j .L8017E0E0\n"
"sb $2, 22($5)\n"
".L8017DF0C:\n"
"lbu $2, -4($s2)\n"
"nop\n"
"sb $2, 28($5)\n"
"sb $2, 20($5)\n"
"sb $2, 12($5)\n"
"sb $2, 4($5)\n"
"lbu $2, -2($s2)\n"
"nop\n"
"sb $2, 29($5)\n"
"sb $2, 21($5)\n"
"sb $2, 13($5)\n"
"sb $2, 5($5)\n"
"lbu $2, 0($s2)\n"
"nop\n"
"sb $2, 30($5)\n"
"j .L8017E0D4\n"
"sb $2, 22($5)\n"
".L8017DF50:\n"
"jal func_80010A08\n"
"addiu $4, $zero, 20\n"
"addu $5, $2, $zero\n"
"addiu $2, $zero, 4\n"
"sb $2, 3($5)\n"
"addiu $2, $zero, 80\n"
"sb $2, 7($5)\n"
"lwc2 $0, 0($s6)\n"
"lwc2 $1, 4($s6)\n"
"lwc2 $2, 0($s5)\n"
"lwc2 $3, 4($s5)\n"
"lwc2 $4, 0($s5)\n"
"lwc2 $5, 4($s5)\n"
"nop\n"
"nop\n"
"rtpt\n"
"addiu $2, $sp, 20\n"
"swc2 $12, 0($2)\n"
"addiu $2, $sp, 24\n"
"swc2 $13, 0($2)\n"
"addiu $2, $sp, 16\n"
"cfc2 $12, $31\n"
"nop\n"
"sw $12, 0($2)\n"
"addiu $2, $sp, 40\n"
"mfc2 $12, $19\n"
"nop\n"
"sra $12, $12, 2\n"
"sw $12, 0($2)\n"
"lw $2, 16($sp)\n"
"addiu $3, $zero, -4097\n"
"and $2, $2, $3\n"
"bnez $2, .L8017E190\n"
"nop\n"
"lh $2, -31($s2)\n"
"lw $17, 40($sp)\n"
"andi $4, $2, 49152\n"
"beqz $4, .L8017E010\n"
"addu $3, $2, $zero\n"
"ori $2, $zero, 49152\n"
"bne $4, $2, .L8017E00C\n"
"andi $2, $3, 4095\n"
"subu $17, $17, $2\n"
"bgez $17, .L8017E014\n"
"sltiu $2, $17, 4096\n"
"j .L8017E010\n"
"addu $17, $zero, $zero\n"
".L8017E00C:\n"
"addu $17, $17, $2\n"
".L8017E010:\n"
"sltiu $2, $17, 4096\n"
".L8017E014:\n"
"beqz $2, .L8017E190\n"
"nop\n"
"lw $2, 20($sp)\n"
"nop\n"
"sh $2, 8($5)\n"
"lw $3, 24($sp)\n"
"sra $2, $2, 16\n"
"sh $2, 10($5)\n"
"sh $3, 16($5)\n"
"sra $3, $3, 16\n"
"sh $3, 18($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"beqz $2, .L8017E0B0\n"
"nop\n"
"lbu $2, -4($s2)\n"
"nop\n"
"sb $2, 4($5)\n"
"lbu $2, -2($s2)\n"
"nop\n"
"sb $2, 5($5)\n"
"lbu $2, 0($s2)\n"
"nop\n"
"sb $2, 6($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 37($2)\n"
"nop\n"
"sb $2, 12($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 39($2)\n"
"nop\n"
"sb $2, 13($5)\n"
"lw $2, 11($s2)\n"
"nop\n"
"lbu $2, 41($2)\n"
"j .L8017E0E0\n"
"sb $2, 14($5)\n"
".L8017E0B0:\n"
"lbu $2, -4($s2)\n"
"nop\n"
"sb $2, 12($5)\n"
"sb $2, 4($5)\n"
"lbu $2, -2($s2)\n"
"nop\n"
"sb $2, 13($5)\n"
"sb $2, 5($5)\n"
"lbu $2, 0($s2)\n"
".L8017E0D4:\n"
"nop\n"
"sb $2, 14($5)\n"
"sb $2, 6($5)\n"
".L8017E0E0:\n"
"slti $2, $16, 4\n"
"beqz $2, .L8017E0FC\n"
"sll $4, $17, 2\n"
"lbu $2, 7($5)\n"
"nop\n"
"ori $2, $2, 2\n"
"sb $2, 7($5)\n"
".L8017E0FC:\n"
"addu $4, $4, $30\n"
"lw $3, 0($5)\n"
"lw $2, 0($4)\n"
"and $3, $3, $23\n"
"and $2, $2, $19\n"
"or $3, $3, $2\n"
"sw $3, 0($5)\n"
"lw $2, 0($4)\n"
"and $3, $5, $19\n"
"and $2, $2, $23\n"
"or $2, $2, $3\n"
"sw $2, 0($4)\n"
"slti $2, $16, 4\n"
"beqz $2, .L8017E190\n"
"nop\n"
"jal func_80010A08\n"
"addiu $4, $zero, 8\n"
"addiu $3, $zero, 1\n"
"sb $3, 3($2)\n"
"sll $3, $16, 5\n"
"andi $3, $3, 2559\n"
"lui $4, 57600\n"
"or $3, $3, $4\n"
"sll $4, $17, 2\n"
"lw $5, 0($2)\n"
"addu $4, $4, $30\n"
"sw $3, 4($2)\n"
"lw $3, 0($4)\n"
"and $5, $5, $23\n"
"and $3, $3, $19\n"
"or $5, $5, $3\n"
"sw $5, 0($2)\n"
"lw $3, 0($4)\n"
"and $2, $2, $19\n"
"and $3, $3, $23\n"
"or $3, $3, $2\n"
"sw $3, 0($4)\n"
".L8017E190:\n"
"addiu $18, $18, 56\n"
"addiu $21, $21, 56\n"
"addiu $22, $22, 56\n"
"lw $6, 48($sp)\n"
"addiu $20, $20, 56\n"
"addiu $6, $6, 1\n"
"slti $2, $6, 192\n"
"bnez $2, .L8017DCF4\n"
"sw $6, 48($sp)\n"
"lw $ra, 108($sp)\n"
"lw $fp, 104($sp)\n"
"lw $23, 100($sp)\n"
"lw $22, 96($sp)\n"
"lw $21, 92($sp)\n"
"lw $20, 88($sp)\n"
"lw $19, 84($sp)\n"
"lw $18, 80($sp)\n"
"lw $17, 76($sp)\n"
"lw $16, 72($sp)\n"
"addiu $sp, $sp, 112\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_8017DC80\n");


extern s32 D_8019B7B8;
extern void func_8017E37C(u8*, u8*, u8*, u8*);

void func_8017E1E8(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 zr __asm__("$0");
    register s32 off __asm__("$4");
    register s32 cnt __asm__("$5");
    s32 ent = arg0;
    s32 p1 = arg1;
    s32 p2 = arg2;
    s32 slot;
    s32 cur;

    if (*(u8 *)ent == 1) {
        cnt = 0;
        off = 0;
        do {
            cur = off + zr;
            if (*(u8 *)((s32)&D_8019B7B8 + cur) == 0) {
                slot = (s32)&D_8019B7B8 + off;
                goto found;
            }
            cnt = cnt + 1;
            off = cur + 0x38;
        } while (cnt < 0xC0);
        slot = 0;
    found:
        if (slot != 0) {
            ((void (*)(s32, s32, s32, s32))func_8017E37C)(slot, ent, p1, p2);
            *(u16 *)(ent + 4) = *(u16 *)p1;
            *(u16 *)(ent + 6) = *(u16 *)(p1 + 2);
            *(u16 *)(ent + 8) = *(u16 *)(p1 + 4);
            if ((*(u16 *)(ent + 0xA) & 0x1000) == 0 && p2 != 0) {
                *(u16 *)(ent + 0xC) = *(u16 *)p2;
                *(u16 *)(ent + 0xE) = *(u16 *)(p2 + 2);
                *(u16 *)(ent + 0x10) = *(u16 *)(p2 + 4);
            }
            *(s32 *)(ent + 0x34) = slot;
        } else {
            if (*(s32 *)(ent + 0x34) != 0) {
                *(u16 *)(*(s32 *)(ent + 0x34) + 4) = *(u16 *)p1;
                *(u16 *)(*(s32 *)(ent + 0x34) + 6) = *(u16 *)(p1 + 2);
                *(u16 *)(*(s32 *)(ent + 0x34) + 8) = *(u16 *)(p1 + 4);
                if ((*(u16 *)(ent + 0xA) & 0x1000) == 0 && p2 != 0) {
                    *(u16 *)(*(s32 *)(ent + 0x34) + 0xC) = *(u16 *)p2;
                    *(u16 *)(*(s32 *)(ent + 0x34) + 0xE) = *(u16 *)(p2 + 2);
                    *(u16 *)(*(s32 *)(ent + 0x34) + 0x10) = *(u16 *)(p2 + 4);
                }
            }
        }
    }
}


void func_8017E37C(u8 *dst, u8 *src1, u8 *src2, u8 *src3)
{
    u16 w;

    w = *(u16 *)(src1 + 0);
    *(u16 *)(dst + 0) = (w & 0xFF00) + 2;
    w = *(u16 *)(src1 + 2);
    *(u16 *)(dst + 2) = w;
    w = *(u16 *)(src2 + 0);
    *(u16 *)(dst + 4) = w;
    w = *(u16 *)(src2 + 2);
    *(u16 *)(dst + 6) = w;
    w = *(u16 *)(src2 + 4);
    *(u16 *)(dst + 8) = w;
    w = *(u16 *)(src1 + 0xA);
    *(u16 *)(dst + 0xA) = w;
    if (!(*(u16 *)(src1 + 0xA) & 0x1000) && src3 != NULL) {
        w = *(u16 *)(src3 + 0);
        *(u16 *)(dst + 0xC) = w;
        w = *(u16 *)(src3 + 2);
        *(u16 *)(dst + 0xE) = w;
        w = *(u16 *)(src3 + 4);
        *(u16 *)(dst + 0x10) = w;
    }
    w = *(u16 *)(src1 + 4);
    *(u16 *)(dst + 0x14) = w;
    w = *(u16 *)(src1 + 6);
    *(u16 *)(dst + 0x16) = w;
    w = *(u16 *)(src1 + 8);
    *(u16 *)(dst + 0x18) = w;
    w = *(u16 *)(src1 + 0xA);
    *(u16 *)(dst + 0x1A) = w;
    if (!(*(u16 *)(src1 + 0xA) & 0x1000)) {
        w = *(u16 *)(src1 + 0xC);
        *(u16 *)(dst + 0x1C) = w;
        w = *(u16 *)(src1 + 0xE);
        *(u16 *)(dst + 0x1E) = w;
        w = *(u16 *)(src1 + 0x10);
        *(u16 *)(dst + 0x20) = w;
    }
    w = *(u16 *)(src1 + 0x24);
    *(u16 *)(dst + 0x24) = w;
    w = *(u16 *)(src1 + 0x26);
    *(u16 *)(dst + 0x26) = w;
    w = *(u16 *)(src1 + 0x28);
    *(u16 *)(dst + 0x28) = w;
    w = *(u16 *)(src1 + 0x2A);
    *(u16 *)(dst + 0x2A) = w;
    w = *(u16 *)(src1 + 0x2C);
    *(u16 *)(dst + 0x2C) = w;
    w = *(u16 *)(src1 + 0x2E);
    *(u16 *)(dst + 0x2E) = w;
    *(u32 *)(dst + 0x34) = *(u32 *)(src1 + 0x34);
    *(u32 *)(dst + 0x30) = (u32)src1;
    *(u32 *)(*(u32 *)(dst + 0x34) + 0x30) = (u32)dst;
}


typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017E4D8;

extern void func_8004978C(s16 *a0, void *a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

void func_8017E4D8(void *arg, void *b, void *c, void *d, void *e) {
    s16 sv[4][4];
    MTX_8017E4D8 mat;
    s16 out[4];

    func_8004978C((s16 *)((s32)arg + 0x10), &mat);
    sv[0][0] = *(u16 *)((s32)arg + 0x18);
    sv[0][1] = 0;
    sv[0][2] = 0;
    sv[0][3] = 0;
    sv[1][0] = *(u16 *)((s32)arg + 0x1A);
    sv[1][1] = 0;
    sv[1][2] = 0;
    sv[1][3] = 0;
    sv[2][0] = *(u16 *)((s32)arg + 0x1C);
    func_80048D9C(&mat, sv);
    mat.t[0] = *(s16 *)((s32)arg + 0x08);
    mat.t[1] = *(s16 *)((s32)arg + 0x0A);
    mat.t[2] = *(s16 *)((s32)arg + 0x0C);
    func_8004914C(&mat);
    func_800491AC(&mat);
    RotTransSV(b, d, out);
    RotTransSV(c, e, out);
}


void func_8017E5D4(s32 param_1)
{
    *(u16 *)param_1 = 0;
    if (*(s32 *)(param_1 + 0x34) != 0) {
        *(s32 *)(*(s32 *)(param_1 + 0x34) + 0x30) = 0;
    }
    if (*(s32 *)(param_1 + 0x30) != 0) {
        *(s32 *)(*(s32 *)(param_1 + 0x30) + 0x34) = 0;
    }
}



extern void (*D_8018A230[])(void);

void func_8017E604(void *a0) {
    D_8018A230[*(u16 *)((s32)a0 + 0x2)]();
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
} SubRec_801EB5C8_8017E640; /* 0x1C */

typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017E640 subs[16];
} GroupRec_801EB5C8_8017E640; /* 0x1D0 */


void func_8017E640(s32 param_1)
{

    extern GroupRec_801EB5C8_8017E640 D_8019E1B8[8];
    s32 i, j;
    GroupRec_801EB5C8_8017E640 *grp;
    SubRec_801EB5C8_8017E640 *sub;

    for (i = 0; i < 8; i++) {
        grp = &D_8019E1B8[i];
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


#include "common.h"

/* func_8017E7E8 (ov_SC07_002, 101 ins) -- MATCH, relocation-masked (tools/match_one.py).
 *
 * Per-frame tick of the 8 x 16 particle-group table at D_8019E1B8 (8 groups of 0x1D0,
 * each = a 0x10 header + 16 subs of 0x1C).  For every group: if header.g0 == 0 bump
 * header.gC by 0x10000; then run each sub's 3-state machine (0 = integrate, 1 = fade,
 * 2 = dead, counted); then call func_8017E97C(arg0, group).  When all 8*16 = 0x80 subs
 * have reached state 2 the whole effect is torn down via func_80146C3C(arg0).
 *
 * TWIN (§193-A): this is a line-for-line relative of the already-banked
 *   src/ov_SC03_028/ov_SC03_028_jr_8017DF98.c:func_8017F278 (also 101 ins).  Same guards,
 *   same switch, same tail.  Per law 2 only the SHAPE was carried across -- every symbol
 *   here was re-read off THIS .s's own relocation lines: D_8019E1B8 (not D_801EB5C8),
 *   func_8017E97C (not func_8017F40C), func_80146C3C (shared).
 *
 * The two register pins are the twin's and they are load-bearing (§17-family):
 *   - `base` pinned to $5/$a1 because $a1 is ALSO the second argument of the inner call:
 *     the group pointer is already sitting in $a1 when `jal func_8017E97C` fires, so the
 *     delay slot only has to reload $a0 (`addu $a0,$s3,$zero`).  Without the pin gcc
 *     schedules a `move $a1,...` into that slot and the tail drifts.
 *   - `sym` pinned to $2/$v0 so the %hi/%lo pair materialises into $v0 and the induction
 *     variable add lands as `addu $a1,$s1,$v0` (gcc strength-reduces i*0x1D0 into $s1).
 *
 * BANKING NOTES (§376/§378) -- the declarations, not the body, are what a gate rejects:
 *   - The two typedefs above are the standard strip-on-bank copy: the destination TU
 *     src/ov_SC07_002/ov_SC07_002_jr_8017C8D0.c ALREADY defines both at file scope
 *     (:3838 SubRec..., :3847 GroupRec...), just above func_8017E640, which declares
 *     D_8019E1B8 block-scope with exactly the spelling used here (:3861).  Drop the
 *     typedefs when inserting; keep the block-scope `extern GroupRec_...[8]` verbatim.
 *   - func_8017E97C is DEFINED later in the same TU (:3907) as `void (s32, s32)`, so the
 *     block-scope extern here is that prototype verbatim -- it cannot conflict and
 *     sig_unify has nothing to widen.  The call passes ONE argument through a cast,
 *     which is this TU's house style for exactly this situation (see func_80186494 at
 *     :8997 doing `((void (*)(void *))func_80146C3C)(s0)`), and is why $a1 is left alone.
 *   - func_80146C3C is already declared at file scope twice (:1683 `()`, :1701 `(void)`);
 *     the `(void)` form repeated here is the card's authoritative `tu=('void', ())` row
 *     and is a compatible redeclaration, so it may be kept or dropped on bank.
 */

 /* 0x1C */

 /* 0x1D0 */

extern void func_80146C3C(void);

void func_8017E7E8(void *arg0) {
    extern GroupRec_801EB5C8_8017E640 D_8019E1B8[8];
    extern void func_8017E97C(s32 a0, s32 a1);
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
            register s32 sym __asm__("$2") = (s32)((u8 *)D_8019E1B8);
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
        ((void (*)(void *))func_8017E97C)(arg0);
    }
    if (cnt2 == 0x80) {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}



extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_8012EFB8(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80017DC4(void *a0, void *a1);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016ED4(void *a0);




void func_8017E97C(s32 a0, s32 a1) {

    extern SVECTOR_8017F40C_8017E97C D_8018A238[4];
    Prim_8017F40C_8017E97C prim;
    u8 matBuf[0x20];
    SVECTOR_8017F40C_8017E97C vecB;
    SVECTOR_8017F40C_8017E97C angBuf;
    SVECTOR_8017F40C_8017E97C sinOut;
    SVECTOR_8017F40C_8017E97C sv1, sv2, sv3, sv4;
    u32 mask;
    s32 rowPtr;
    SVECTOR_8017F40C_8017E97C *ap;
    void *mp;
    SVECTOR_8017F40C_8017E97C *dv;

    func_80015978(a0 + 4, (s32 *)&vecB);
    angBuf.vx = 0;
    angBuf.vy = 0;
    angBuf.vz = *(u16 *)(a1 + 0xe);
    func_800139C8((s32) *(s16 *)(a1 + 2), &angBuf, &angBuf);
    mask = ((u32(*)(void *, void *))func_8012EFB8)(&vecB, &vecB);
    if ((mask & 0xffffefff) == 0) {
        Prim_8017F40C_8017E97C *pp = &prim;
        s32 off;
        s32 cnt;
        cnt = 0;
        ap = &angBuf;
        mp = matBuf;
        dv = D_8018A238;
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


extern s32 func_80029504(void);
extern void func_8002931C(void);
extern u8 *D_801274C8;
extern void *D_801274CC;
extern s32 D_8011DB10;
extern u8 D_8018A728[];
extern u8 D_8018A7C8[];
extern u8 D_8018A7DC[];
extern u8 D_8018A87C[];
extern u8 D_801A64DC[];

void func_8017EC34(void) {
    s32 t;

    t = func_80029504();
    ((void (*)(s32))func_8002931C)(0x4740000);
    if (t < 0x640) {
        D_801274C8 = D_8018A728;
        D_801274CC = D_8018A7C8;
    } else {
        D_801274C8 = D_8018A7DC;
        D_801274CC = D_8018A87C;
    }
    D_8011DB10 = (s32)D_801A64DC;
}



extern void (*D_8018A2A8[])(void);

void func_8017ECC0(void *a0) {
    D_8018A2A8[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017EFB4(void);
extern void func_800167B8(s32 a0);

s32 func_8017ECFC(s32 a0) {
    func_8017EFB4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017ED40(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018A2B0[])(void);

void func_8017ED64(void *a0) {
    D_8018A2B0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017EFDC(void);

s32 func_8017EDA0(s32 a0) {
    func_8017EFDC();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017EDE0(u8 *a0) {
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
    void func_8017EE5C(void) {
        func_800D1EBC();
    }



extern void (*D_8018A2BC[])(void);

void func_8017EE7C(void *a0) {
    D_8018A2BC[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017EFAC(void);

s32 func_8017EEB8(s32 a0) {
    func_8017EFAC();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}






extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_80016940(s32 a0);

s32 func_8017EEF8(void *a0) {
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
        func_80016940(4);
        *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1;
    }
    return 0;
}


extern s32 func_80016978(s32 arg);
extern void func_80029240(void);

s32 func_8017EF74(void) {
    if ((func_80016978(4) & 0xFFFF) == 0) {
        return 0;
    }
    func_80029240();
    return 1;
}


void func_8017EFAC(void) {
}

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018A2C8;

void func_8017EFB4(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018A2C8, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
    extern s32 D_8018A2CC;
    void func_8017EFDC(void) {
        ((void (*)(void *, s32))func_8016EE40)(&D_8018A2CC, 0x1000000);
    }


extern s32 func_80029504(void);
extern void func_8017F048(void);
extern void func_8017F0E8(void);

void func_8017F004(void)
{
    s32 v0;

    v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017F048();
    } else {
        func_8017F0E8();
    }
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];

void func_8017F048(void) {
    func_801817E0(0);
    D_80126954 = 0x190;
    D_8012695C = 0x320;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
    func_8012A094((s32)D_80126948);
    func_8017FB48(D_80126948);
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];

void func_8017F0E8(void) {
    func_801817E0(0);
    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -1;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
    func_8012A094((s32)D_80126948);
    func_8017FB48(D_80126948);
}


extern s32 func_80029504(void);
extern void func_8017F1C8(void);
extern void func_8017F250(void);

void func_8017F184(void)
{
    s32 v0;

    v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017F1C8();
    } else {
        func_8017F250();
    }
}


extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_80126954;
extern s32 D_8012695C;
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F1C8() {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 1);
    func_8012A62C(0x1E);
}


extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_80126954;
extern s32 D_8012695C;
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F250() {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 1);
    func_8012A62C(0x1E);
}


extern s32 func_80029504(void);
extern void func_8017F31C(void);
extern void func_8017F39C(void);

void func_8017F2D8(void)
{
    s32 v0;

    v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017F31C();
    } else {
        func_8017F39C();
    }
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F31C(void) {
    func_801817E0(1);
    D_80126954 = 0x190;
    D_8012695C = 0x320;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F39C(void)
{
    func_801817E0(1);
    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -1;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
}


extern s32 func_80029504(void);
extern void func_8017F45C(void);
extern void func_8017F4DC(void);

void func_8017F418(void)
{
    s32 v0;

    v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017F45C();
    } else {
        func_8017F4DC();
    }
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F45C(void) {
    func_801817E0(1);
    D_80126954 = 0x190;
    D_8012695C = 0x320;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
}


extern void func_801817E0(s32 a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8017FB48(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F4DC(void) {
    func_801817E0(1);
    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_80126968 = 0x38;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -1;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 0);
}


extern s32 D_8019F038;
    void func_8017F558(void) {
        D_8019F038 += 1;
    }


extern s32 D_8019F038;

void func_8017F578(void) {
    extern s32 func_80029504(void);
    extern void func_8017F5C4(void);
    extern void func_8017F680(void);
    s32 v0;

    v0 = func_80029504();
    D_8019F038 = 0;
    if (v0 < 0x640) {
        func_8017F5C4();
    } else {
        func_8017F680();
    }
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F5C4(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s16 D_801269E8;
    func_801817E0(0);
    D_80126954 = 0x12C;
    D_8012695C = 0x2BC;
    D_80126968 = 0x38;
    D_8012696A = 0x638;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    ((void (*)(void *, s32))func_8012A018)((void *)func_8017FB48, 2);
    D_801269E8 = 0;
    func_8012A094((s32)D_80126948);
    func_8017FB48((void *)D_80126948);
    func_8012A094((s32)D_80126948);
    func_8017FB48((void *)D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F680(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    func_801817E0(0);
    D_80126954 = 0xC8;
    D_8012695C = 0x300;
    D_80126968 = 0x100;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    ((void (*)(void *, s32))func_8012A018)((void *)func_8017FB48, 2);
    func_8012A094((s32)D_80126948);
    func_8017FB48((void *)D_80126948);
    func_8012A094((s32)D_80126948);
    func_8017FB48((void *)D_80126948);
}


extern void func_8017F750(void);
    void func_8017F730(void) {
        func_8017F750();
    }


extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_80126954;
extern s32 D_8012695C;
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F750() {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 3);
    func_8012A62C(0x1E);
}


extern void func_8017F7F8(void);
void func_8017F7D8(void) {
    func_8017F7F8();
}


extern void func_801817E0(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F7F8(void) {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 4);
    func_8012A62C(0x1E);
}


extern void func_8017F8A0(void);
void func_8017F880(void) {
    func_8017F8A0();
}


extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_80126954;
extern s32 D_8012695C;
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_801817E0(s32 a0);

void func_8017F8A0() {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 5);
    func_8012A62C(0x1E);
}


extern void func_8017F948(void);
void func_8017F928(void) {
    func_8017F948();
}


extern void func_801817E0(s32 a0);
extern void func_8017FB48(void *a0);
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A62C(s32 a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017F948(void) {
    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 6);
    func_8012A62C(0x1E);
}


extern void func_8017F9EC(void);
void func_8017F9CC(void) {
    func_8017F9EC();
}


void func_8017F9EC(void) {
    extern void func_801817E0(s32);
    extern void func_8017FB48(void *);
    extern void func_8012A018(s32, s32);
    extern void func_8012A62C(s32);
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    func_801817E0(2);
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    D_80126968 = 0x200;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x180;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FB48, 7);
    func_8012A62C(0x1E);
}


extern s32 func_8017FA94();
    s32 func_8017FA74(void) {
        return func_8017FA94();
    }


extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s32 D_80126B58;

extern void func_801817E0(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_8014C59C(void *a0, void *a1);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A62C(s32 a0);
extern void func_8017FB48(void *a0);

s32 func_8017FA94(void)
{
    u8 *s0;
    s32 ret;

    func_801817E0(2);
    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_80126968 = 0x11C;
    ret = func_8012E544(0x306);
    s0 = D_80126948;
    if (ret != 0) {
        D_8012696A = func_8014C59C(&D_80126B58, ret);
    } else {
        D_8012696A = 0;
    }
    *(s16 *)(s0 + 0x24) = 0;
    *(s16 *)(s0 + 0x2E) = 0;
    *(s16 *)(s0 + 0x30) = -1;
    *(s16 *)(s0 + 0x32) = 0;
    func_8012A018((s32)func_8017FB48, 8);
    func_8012A62C(0x1E);
}



extern void (*D_8018A2F8[])(void);

void func_8017FB48(void *a0) {
    D_8018A2F8[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

extern s32 func_80029504(void);
extern void func_8017FBD0(s32 a0);
extern void func_8017FCA8(s32 a0);

void func_8017FB84(s32 a0) {
    s32 v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017FBD0(a0);
    } else {
        func_8017FCA8(a0);
    }
}


void func_8017FBD0(s32 s0) {
    typedef struct { s16 vx, vy, vz, pad; } SVfbd0;
    extern SVfbd0 D_80126940;
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVfbd0 base;
    SVfbd0 target;
    s32 ret;
    s32 ang;

    base = D_80126940;
    ret = func_8012E544(0x322);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = D_80126940;
    }
    ang = ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff;
    if (base.vy > -0x200) {
        base.vy = -0x200;
    }
    func_80181394(s0, &base, ang);
}


INCLUDE_ASM("asm/ov_SC07_002/nonmatchings/ov_SC07_002_jr_8017C8D0", func_8017FCA8);

extern s32 func_80029504(void);
extern void func_8017FEC4(s32 a0);
extern void func_8017FF84(s32 a0);

void func_8017FE78(s32 a0) {
    s32 v0 = func_80029504();
    if (v0 < 0x640) {
        func_8017FEC4(a0);
    } else {
        func_8017FF84(a0);
    }
}


void func_8017FEC4(s32 s0) {
    typedef struct { s16 vx, vy, vz, pad; } SVfec4;
    extern SVfec4 D_80126940;
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVfec4 base;
    SVfec4 target;
    s32 ret;

    base = D_80126940;
    ret = func_8012E544(0x322);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = D_80126940;
    }
    func_80181394(s0, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


void func_8017FF84(s32 s1) {
    typedef struct { s16 vx, vy, vz, pad; } SVff84;
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVff84 base;
    SVff84 target;
    s32 ret;

    base = (*(SVff84 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVff84 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}



extern s32 func_80029504(void);
extern void func_80180090(s32 a0);
extern void func_80180248(s32 a0);

void func_80180044(s32 a0) {
    s32 v0 = func_80029504();
    if (v0 < 0x640) {
        func_80180090(a0);
    } else {
        func_80180248(a0);
    }
}


void func_80180090(s32 a0)
{
    typedef struct { s16 vx, vy, vz, pad; } SV180090;
    extern SV180090 D_80126940;
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern s32 func_8004787C(s32 a0);
    extern void func_80181394();

    SV180090 base;
    SV180090 target;
    s32 ret;
    s16 clamped;

    base = D_80126940;
    ret = func_8012E544(0x322);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = D_80126940;
    }
    ratan2(base.vx - target.vx, base.vz - target.vz);

    clamped = func_8004787C(((*(s16 *)(a0 + 0x1a) - 0x638) * 2048) / 910) * 341 / 4096 - 0x71;
    if (clamped < 0) {
        clamped = 0;
    }
    *(s16 *)(a0 + 0x20) = 0x38 - clamped;

    clamped = func_8004787C(((*(s16 *)(a0 + 0x1a) - 0x638) * 2048) / 910) * 288 / 4096 - 0x40;
    if (clamped < 0) {
        clamped = 0;
    }
    target.vy -= clamped;
    *(s16 *)(a0 + 0x22) = (*(u16 *)(a0 + 0x1a) += 4);

    func_80181394(a0, &target, 0);
}


INCLUDE_ASM("asm/ov_SC07_002/nonmatchings/ov_SC07_002_jr_8017C8D0", func_80180248);

typedef struct { u16 w[4]; } __attribute__((aligned(2))) DBlock_8019F04C;

extern s16 D_8019F048;
extern s16 D_8019F04A;
extern s16 D_8019F04C;
extern s16 D_8019F054;
extern s16 D_8019F056;
extern s16 D_8019F058;
extern s32 D_8019F03C;
extern s32 D_8019F05C;
extern s32 *D_8019F040;
extern s32 D_8018A31C[];
extern s32 func_8018059C(s32 arg0);

void func_801804D4(void *a0, s32 a1) {
    D_8019F048 = *(s32 *)((s32)a0 + 8);
    D_8019F04A = *(s32 *)((s32)a0 + 0x10);
    *(DBlock_8019F04C *)(void *)&D_8019F04C = *(DBlock_8019F04C *)(void *)((s32)a0 + 0x18);
    D_8019F054 = *(u16 *)((s32)a0 + 0x28);
    D_8019F056 = *(u16 *)((s32)a0 + 0x2A);
    D_8019F03C = 0;
    D_8019F05C = 0;
    D_8019F058 = *(u16 *)((s32)a0 + 0x2C);
    D_8019F040 = (s32 *)((u8 *)D_8018A31C + a1 * 0x18);
    if (*D_8019F040 == 1) {
        func_8018059C((s32)a0);
    }
}


extern s32 *D_8019F040;
extern s32 D_8019F03C;
extern s16 D_8019F048;
extern s16 D_8019F04A;
extern s16 D_8019F04C;
extern s16 D_8019F04E;
extern s16 D_8019F050;
extern s16 D_8019F054;
extern s16 D_8019F056;
extern s16 D_8019F058;

s32 func_8018059C(s32 arg0) {
    s16 *ptr;
    s32 step;
    s32 div;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    s32 v5;
    s32 v6;
    s32 v7;
    s32 v8;
    s32 q3;
    s32 q4;
    s32 q5;
    s32 q6;
    s32 q7;
    s32 q8;
    s32 frame_pad[12];

    ptr = (s16 *)D_8019F040;
    step = D_8019F03C + 1;
    div = *(s32 *)ptr;
    v1 = D_8019F048 + ((ptr[2] - D_8019F048) * step / div);
    *(s32 *)(arg0 + 0xc) = v1;
    *(s32 *)(arg0 + 8) = v1;
    v2 = D_8019F04A + ((ptr[3] - D_8019F04A) * step / div);
    *(s32 *)(arg0 + 0x14) = v2;
    *(s32 *)(arg0 + 0x10) = v2;
    q3 = (ptr[4] - D_8019F04C) * step / div;
    v3 = D_8019F04C + q3;
    *(s16 *)(arg0 + 0x20) = v3;
    *(s16 *)(arg0 + 0x18) = v3;
    q4 = (ptr[5] - D_8019F04E) * step / div;
    v4 = D_8019F04E + q4;
    *(s16 *)(arg0 + 0x22) = v4;
    *(s16 *)(arg0 + 0x1a) = v4;
    q5 = (ptr[6] - D_8019F050) * step / div;
    v5 = D_8019F050 + q5;
    *(s16 *)(arg0 + 0x24) = v5;
    *(s16 *)(arg0 + 0x1c) = v5;
    q6 = (ptr[8] - D_8019F054) * step / div;
    v6 = D_8019F054 + q6;
    *(s16 *)(arg0 + 0x2e) = v6;
    *(s16 *)(arg0 + 0x28) = v6;
    q7 = (ptr[9] - D_8019F056) * step / div;
    v7 = D_8019F056 + q7;
    *(s16 *)(arg0 + 0x30) = v7;
    *(s16 *)(arg0 + 0x2a) = v7;
    q8 = (ptr[10] - D_8019F058) * step / div;
    v8 = D_8019F058 + q8;
    D_8019F03C = step;
    *(s16 *)(arg0 + 0x32) = v8;
    *(s16 *)(arg0 + 0x2c) = v8;
    if (step == *(s32 *)ptr) {
        D_8019F03C = div;
        return 1;
    }
    return 0;
}


extern s32 D_8019F05C;
extern void func_80016224(s32 a0, s32 a1);

void func_801808E0(s32 param_1, s32 param_2)
{
    if (D_8019F05C < param_2) {
        func_80016224(0xFF, 0);
        D_8019F05C = D_8019F05C + 1;
    }
}


extern s32 func_8018094C();
    void func_8018092C(void) {
        func_8018094C();
    }


typedef struct { s16 vx, vy, vz, pad; } SVfbd0;

s32 func_8018094C(s32 s1)
{
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVfbd0 base;
    SVfbd0 target;
    s32 ret;

    base = (*(SVfbd0 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVfbd0 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


extern s32 func_80180A2C();
    void func_80180A0C(void) {
        func_80180A2C();
    }


s32 func_80180A2C(s32 s1) {
    typedef struct { s16 vx, vy, vz, pad; } SVfbd0;
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern s32 func_80181394();

    SVfbd0 base;
    SVfbd0 target;
    s32 ret;

    base = (*(SVfbd0 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVfbd0 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


extern void func_80180B0C();
void func_80180AEC(void) {
    func_80180B0C();
}


void func_80180B0C(s32 s1) {
    typedef struct { s16 vx, vy, vz, pad; } SVfbd0;
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVfbd0 base;
    SVfbd0 target;
    s32 ret;

    base = (*(SVfbd0 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVfbd0 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


extern void func_80180BEC(void);
void func_80180BCC(void) {
    func_80180BEC();
}


/* func_80180BEC (ov_SC07_002, TU src/ov_SC07_002/ov_SC07_002_jr_8017C8D0.c)
 *
 * INTEGRATION LEVER — cookbook index line 15 ("conflicting types on YOUR OWN
 * function's definition, where the fleet canon is (void)") -> §73 PARAMS axis
 * + §42 lever 6 (register-arg capture, byte-proven on func_80168828).
 *
 * The previous attempt drafted this as `void func_80180BEC(s32 s1)`. That is
 * iso-MATCH but the whole-binary gate REFUSED it: the destination TU already
 * carries `extern void func_80180BEC(void);` (its caller stub func_80180BCC,
 * line ~5109) BEFORE the splice point, and in gcc-2.7.2 a (void) prototype vs
 * a one-param definition is a HARD ERROR, not a warning:
 *     tu.c:5115: conflicting types for `func_80180BEC'
 *     tu.c:5109: previous declaration of `func_80180BEC'
 *   -> cc1 exit 33 (measured here on a scratch copy of the real TU).
 * sweep_parallel's phase A runs with GATE_NO_ARITY=1, so the arity pre-pass
 * that would relax that decl does not run for it -- the draft must not need it.
 *
 * FIX (draft-side, T0, no fleet edit): keep the canonical (void) signature and
 * read the incoming $a0 through a pinned register variable, copied at once into
 * a normal pseudo so it gets a callee-saved home (target: `addu $s1,$a0,$zero`).
 *
 * VERIFIED: match_one MATCH (48/48), AND a real-TU compile of the spliced
 * ov_SC07_002_jr_8017C8D0.c is cc1 rc=0 with 0 masked diffs for this function.
 */
void func_80180BEC(void) {
    typedef struct { s16 vx, vy, vz, pad; } SVfbd0;
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();
    register s32 a0v __asm__("$4");

    s32 s1 = a0v;
    SVfbd0 base;
    SVfbd0 target;
    s32 ret;

    base = (*(SVfbd0 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVfbd0 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


extern void func_80180CCC();
void func_80180CAC(void) {
    func_80180CCC();
}


#include "common.h"

void func_80180CCC(s32 s1) {
    typedef struct { s16 vx, vy, vz, pad; } SVfbd0;
    extern s16 D_80126940[4];
    extern s32 func_8012E544(s32 a0);
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181394();

    SVfbd0 base;
    SVfbd0 target;
    s32 ret;

    base = (*(SVfbd0 *)D_80126940);
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *)&target);
    } else {
        target = (*(SVfbd0 *)D_80126940);
    }
    func_80181394(s1, &base, ratan2(base.vx - target.vx, base.vz - target.vz) & 0xfff);
}


extern s32 func_80180DAC();
    void func_80180D8C(void) {
        func_80180DAC();
    }


typedef struct { s16 m0, m1, m2, m3; } Pos;

extern s16 D_80126940[4];
extern void func_80180F7C(s32 a0, void *a1);

s32 func_80180DAC(s32 a0)
{
    Pos cur;
    Pos target;
    s32 ret;
    s32 dist;
    s16 clamped;
    register s16 ang __asm__("$5");
    register s32 sc __asm__("$2");

    cur = *(Pos *) D_80126940;
    ret = func_8012E544(0x306);
    if (ret != 0) {
        func_80015978(ret + 4, (s32 *) &target);
        if (cur.m1 > -0x200) {
            cur.m1 = -0x200;
        }
        func_80015978(ret + 4, (s32 *) &target);
        target.m1 = cur.m1;
        dist = func_80013294(&cur, &target) - 0x80;
        clamped = dist;
        if (clamped < 0) {
            clamped = 0;
        }
        if (clamped > 0x380) {
            clamped = 0x380;
        }
        ang = ((clamped * 111) / 896) - 0x70;
        *(s16 *) (a0 + 0x30) = ang;
        sc = ((clamped * 1000) / 896) + 0x190;
        *(s32 *) (a0 + 0x14) = (s16) sc;
    } else {
        target = *(Pos *) D_80126940;
    }

    cur.m0 = (cur.m0 + target.m0) / 2;
    cur.m2 = (cur.m2 + target.m2) / 2;
    func_80180F7C(a0, &cur);
}


/* func_80180F7C (ov_SC07_002, 262 ins) — the §250/§195-H address-materialisation
 * card.  Family template: func_8017F048 (ov_SC04_005) / func_801EDEE8 (md_SC05_027)
 * are byte-identical tails (MATRIX + SVECTOR in/out, m1.t[2] written BEFORE
 * svec_in.vx/vy so the two `sh zero` land in t[2]'s load-delay gap).
 *
 * The two non-obvious levers on this card:
 *  1. D_8019F064 and D_8019F060 are reached through the TU's `extern u8 D[];`
 *     array spelling + a `(s16 *)` cast, which force_regs the address into ONE
 *     held base (`lui`/`addiu` pair, then `lh 0($reg)`) — §250 row 1 / §195-H
 *     BOUND 3.  D_8019F062 is a plain `extern s16` scalar, so it re-emits its own
 *     `lui`/`lh %lo` per use (9 of them).  Getting either one backwards costs
 *     instructions in both directions.
 *  2. `p60` must be ASSIGNED AFTER the guarded-decrement `if`, not at its
 *     declaration: the `la $s1` pair is what fills the load-delay gap of the
 *     switch's own `lhu %lo(D_8019F066)`.  Initialising p60 at the top hoists the
 *     pair above the `beqz` and leaves a `nop` there — LENGTH-DRIFT/+1.
 *
 * §252 guarded pre-decrement: `beqz` first with a `move` in its delay slot and a
 * `sll 16` (not `andi 0xffff`) test => separate s16 temp, `t = D - 1; D = t; if (t == 0)`.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_80180F7C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_80180F7C;   /* 0x20: m@0, pad@0x12, t@0x14 */

void func_80180F7C(s32 a0, void *a1)
{
    extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
    extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
    extern s32  func_800130D0(s32 a0, s32 a1, s32 a2);
    extern s32  func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32  func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_801817E0(s32 a0);
    extern u8   D_8019F060[];
    extern s16  D_8019F062;
    extern u8   D_8019F064[];
    extern u16  D_8019F066;

    MTX_80180F7C m1;
    SV_80180F7C svec_in;
    SV_80180F7C svec_out;
    s16 *param_2 = (s16 *)a1;
    s16 *p60;
    s16 t;

    if (*(s16 *)D_8019F064 != 0) {
        t = *(s16 *)D_8019F064 - 1;
        *(s16 *)D_8019F064 = t;
        if (t == 0) {
            func_801817E0((D_8019F066 >> 4) & 0xF);
        }
    }

    p60 = (s16 *)D_8019F060;

    switch (D_8019F066 & 0xF) {
    case 0:
        *(s32 *)(a0 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60);
        *(s32 *)(a0 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60);
        *(s16 *)(a0 + 0x18) = func_80012ABC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)*p60);
        *(s16 *)(a0 + 0x1A) = func_80012ABC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)*p60);
        *(s16 *)(a0 + 0x1C) = func_80012ABC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)*p60);
        *(s16 *)(a0 + 0x28) = func_80012C6C((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)D_8019F062);
        *(s16 *)(a0 + 0x2A) = func_80012C6C((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)D_8019F062);
        *(s16 *)(a0 + 0x2C) = func_80012C6C((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)D_8019F062);
        break;
    case 1:
        *(s32 *)(a0 + 0x8)  = (s16)func_80012F74((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60, 1);
        *(s32 *)(a0 + 0x10) = (s16)func_80012F74((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60, 1);
        *(s16 *)(a0 + 0x18) = func_80012DBC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1A) = func_80012DBC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1C) = func_80012DBC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x28) = func_80012F74((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)*p60, 1);
        *(s16 *)(a0 + 0x2A) = func_80012F74((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)*p60, 1);
        *(s16 *)(a0 + 0x2C) = func_80012F74((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)*p60, 1);
        break;
    case 2:
        *(s32 *)(a0 + 0x8)  = (s16)func_800130D0((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60);
        *(s32 *)(a0 + 0x10) = (s16)func_800130D0((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60);
        *(s16 *)(a0 + 0x18) = func_80012DBC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1A) = func_80012DBC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1C) = func_80012DBC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x28) = func_800130D0((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)*p60);
        *(s16 *)(a0 + 0x2A) = func_800130D0((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)*p60);
        *(s16 *)(a0 + 0x2C) = func_800130D0((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)*p60);
        break;
    }

    *(s32 *)(a0 + 0x48) = (s32)*(s16 *)(a0 + 0x28) + (s32)param_2[0];
    *(s32 *)(a0 + 0x4C) = (s32)*(s16 *)(a0 + 0x2A) + (s32)param_2[1];
    *(s32 *)(a0 + 0x50) = (s32)*(s16 *)(a0 + 0x2C) + (s32)param_2[2];
    func_80049CAC(a0 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(a0 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(a0 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(a0 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(a0 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(a0 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(a0 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(a0 + 0x44) = (s32)svec_out.vz;
}


/* func_80181394 (ov_SC07_002, 275 ins) — the §250/§195-H address-materialisation
 * card again.  Head + switch are structurally IDENTICAL to the banked neighbour
 * func_80180F7C in this same TU (same `extern u8 D[];` + `(s16 *)` cast for
 * D_8019F060/D_8019F064, same plain `extern s16 D_8019F062` scalar, same §252
 * guarded pre-decrement, same "assign p60 AFTER the if" lever).  Only the tail
 * differs: func_80185848 + ApplyMatrixSV, and the results are `<< 16 >> 19`.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_80181394;
typedef struct { u16 vx, vy, vz, pad; } UV_80181394;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_80181394;   /* 0x20 */

void func_80181394(s32 a0, s16 *param_2, s32 a2)
{
    extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
    extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
    extern s32  func_800130D0(s32 a0, s32 a1, s32 a2);
    extern s32  func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32  func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_801817E0(s32 a0);
    extern void func_80185848(u16 *a0, s16 *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern u8   D_8019F060[];
    extern s16  D_8019F062;
    extern u8   D_8019F064[];
    extern u16  D_8019F066;

    MTX_80181394 m1;            /* sp+0x10 */
    SV_80181394  svec_in;       /* sp+0x30 */
    UV_80181394  svec_out;      /* sp+0x38 */
    UV_80181394  rot;           /* sp+0x40 */
    s16 *p60;
    s16 t;

    if (*(s16 *)D_8019F064 != 0) {
        t = *(s16 *)D_8019F064 - 1;
        *(s16 *)D_8019F064 = t;
        if (t == 0) {
            func_801817E0((D_8019F066 >> 4) & 0xF);
        }
    }

    p60 = (s16 *)D_8019F060;

    switch (D_8019F066 & 0xF) {
    case 0:
        *(s32 *)(a0 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60);
        *(s32 *)(a0 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60);
        *(s16 *)(a0 + 0x18) = func_80012ABC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)*p60);
        *(s16 *)(a0 + 0x1A) = func_80012ABC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)*p60);
        *(s16 *)(a0 + 0x1C) = func_80012ABC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)*p60);
        *(s16 *)(a0 + 0x28) = func_80012C6C((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)D_8019F062);
        *(s16 *)(a0 + 0x2A) = func_80012C6C((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)D_8019F062);
        *(s16 *)(a0 + 0x2C) = func_80012C6C((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)D_8019F062);
        break;
    case 1:
        *(s32 *)(a0 + 0x8)  = (s16)func_80012F74((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60, 1);
        *(s32 *)(a0 + 0x10) = (s16)func_80012F74((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60, 1);
        *(s16 *)(a0 + 0x18) = func_80012DBC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1A) = func_80012DBC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1C) = func_80012DBC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x28) = func_80012F74((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)*p60, 1);
        *(s16 *)(a0 + 0x2A) = func_80012F74((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)*p60, 1);
        *(s16 *)(a0 + 0x2C) = func_80012F74((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)*p60, 1);
        break;
    case 2:
        *(s32 *)(a0 + 0x8)  = (s16)func_800130D0((s32)*(s16 *)(a0 + 0x8),  (s32)*(s16 *)(a0 + 0xC),  (s32)*p60);
        *(s32 *)(a0 + 0x10) = (s16)func_800130D0((s32)*(s16 *)(a0 + 0x10), (s32)*(s16 *)(a0 + 0x14), (s32)*p60);
        *(s16 *)(a0 + 0x18) = func_80012DBC((s32)*(s16 *)(a0 + 0x18), (s32)*(s16 *)(a0 + 0x20), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1A) = func_80012DBC((s32)*(s16 *)(a0 + 0x1A), (s32)*(s16 *)(a0 + 0x22), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x1C) = func_80012DBC((s32)*(s16 *)(a0 + 0x1C), (s32)*(s16 *)(a0 + 0x24), (s32)D_8019F062, 1);
        *(s16 *)(a0 + 0x28) = func_800130D0((s32)*(s16 *)(a0 + 0x28), (s32)*(s16 *)(a0 + 0x2E), (s32)*p60);
        *(s16 *)(a0 + 0x2A) = func_800130D0((s32)*(s16 *)(a0 + 0x2A), (s32)*(s16 *)(a0 + 0x30), (s32)*p60);
        *(s16 *)(a0 + 0x2C) = func_800130D0((s32)*(s16 *)(a0 + 0x2C), (s32)*(s16 *)(a0 + 0x32), (s32)*p60);
        break;
    }

    *(s32 *)(a0 + 0x48) = (s32)*(s16 *)(a0 + 0x28) + (s32)param_2[0];
    *(s32 *)(a0 + 0x4C) = (s32)*(s16 *)(a0 + 0x2A) + (s32)param_2[1];
    *(s32 *)(a0 + 0x50) = (s32)*(s16 *)(a0 + 0x2C) + (s32)param_2[2];

    rot.vx = *(u16 *)(a0 + 0x18);
    rot.vy = *(u16 *)(a0 + 0x1A) + a2;
    rot.vz = *(u16 *)(a0 + 0x1C);
    func_80185848((u16 *)&rot, (s16 *)&m1);

    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(a0 + 0x10);
    ApplyMatrixSV(&m1, &svec_in, &svec_out);

    *(s32 *)(a0 + 0x3C) = ((svec_out.vx << 16) >> 19) + *(s16 *)(a0 + 0x28) + param_2[0];
    *(s32 *)(a0 + 0x40) = ((svec_out.vy << 16) >> 19) + *(s16 *)(a0 + 0x2A) + param_2[1];
    *(s32 *)(a0 + 0x44) = ((svec_out.vz << 16) >> 19) + *(s16 *)(a0 + 0x2C) + param_2[2];
}


typedef struct { u16 a, b, c, d; } V8;

extern V8 D_8018A2E0[];
extern u8 D_8019F060[];

void func_801817E0(s32 arg0)
{
    *(V8 *)D_8019F060 = D_8018A2E0[arg0];
}


s32 func_80181834(s32 arg0) {
    return -(arg0 < 0x640) & 0x98;
}


void func_80181844(void) {
}

extern u8 D_8019FF68;
extern u8 D_8019FF89;
extern u8 D_8019FF8C;
extern u8 D_801A0044;
extern s32 D_801A0048;
extern u8 D_801A0062;
extern u8 D_801A00D6;

s32 func_8018184C(s32 arg0) {
    s32 var_a1;
    u8 temp;

    var_a1 = 0;
    switch (arg0) {
    case 1:
        D_801A00D6 = 0x10;
        D_801A0044 = 0x10;
        D_8019FF89 = 0x10;
        break;
    case 7:
        D_801A00D6 = 0x10;
        D_801A0044 = 4;
        D_8019FF89 = 2;
        break;
    case 8:
        D_801A00D6 = 2;
        D_801A0044 = 0xA;
        D_8019FF89 = 0x10;
        break;
    case 9:
        D_801A00D6 = 8;
        D_801A0044 = 7;
        D_8019FF89 = 7;
        break;
    }

    temp = D_801A0062;
    if (temp != D_801A00D6) {
        temp = (temp < D_801A00D6) ? temp + 1 : temp - 1;
        D_801A0062 = temp;
        var_a1 = 1;
    }

    temp = D_8019FF8C;
    if (temp != D_801A0044) {
        temp = (temp < D_801A0044) ? temp + 1 : temp - 1;
        D_8019FF8C = temp;
        var_a1 = 1;
    }

    temp = D_8019FF68;
    if (temp != D_8019FF89) {
        temp = (temp < D_8019FF89) ? temp + 1 : temp - 1;
        D_8019FF68 = temp;
        var_a1 = 1;
    }

    if (var_a1 != 0) {
        D_801A0048 = 1;
    } else {
        D_801A0048 = 0;
    }
    return var_a1;
}


void func_801819C4(void) {
}



extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801819CC(void) {

    extern u8 D_800AF568[];
    func_8001ABBC(0, 0, D_800AF568, 0, 0);
}


extern s16 D_8019F070;
    void func_80181A00(void) {
        D_8019F070 = 0x1;
    }


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181F98(s32*, s32*);
extern void func_80181BD8();
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80181C80(a0);

extern u16 D_8019FF8A;
extern s16 D_8019F070;

extern s32 D_8018A3AC[];
extern void (*D_8018A3D4[])(void);
extern u8 D_80196C04[];
extern s32 D_80196BEC[];

typedef struct { u16 v; u16 pad; } Rec4;
extern Rec4 D_8018A3C0[];
extern Rec4 D_8018A3C2[];

typedef struct { s32 v; s32 pad; } Rec8;
extern Rec8 D_8019F074[];
extern Rec8 D_8019F078[];

void func_80181A14(int param_1)
{
    s32 v0;
    u16 v1;

    v0 = func_8012C1B8();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }

    if (*(s16 *)(param_1 + 0x70) == 0) {
        D_8019FF8A = 0;
        D_8019F070 = 0;
    }

    v1 = *(u16 *)(param_1 + 0x70);
    if ((v1 & 0x100) == 0) {
        func_8001C214(*(s32 *)(param_1 + 0x20), D_8018A3AC[(s16)v1]);
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x28) = 0xB000D0;
        *(s32 *)(param_1 + 0x58) = (s32)D_8018A3D4 | 0x40000000;
        *(u16 *)(param_1 + 0x5c) = 0xC800;
        *(u8 *)(param_1 + 0x75) = 0;
        ((void (*)(s32, s32))func_80181F98)(param_1, (s32)D_80196C04 + (*(s16 *)(param_1 + 0x70)) * 12);

        *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 6) + D_8018A3C0[*(s16 *)(param_1 + 0x70)].v;
        *(u16 *)(param_1 + 0xE) = *(u16 *)(param_1 + 0xE) + D_8018A3C2[*(s16 *)(param_1 + 0x70)].v;

        if (*(s16 *)(param_1 + 0x70) == 0) {
            s32 bi, bj;
            for (bi = 0, bj = 0; bi < 0x14; bi += 4, bj += 8) {
                *(s32 *)((u8 *)D_8019F078 + bj) = 0;
                *(s32 *)((u8 *)D_8019F074 + bj) = *(s32 *)((u8 *)D_80196BEC + bi);
            }
        }

        func_80181BD8(param_1);
        func_8012C658(0x4A, *(s16 *)(param_1 + 0x70), param_1);
    } else {
        v1 = v1 & 0xFF;
        *(u16 *)(param_1 + 0x70) = v1;
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)&D_8019F074[v1]);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) | 0x10;
        ((void (*)(s32))func_80181C80)(param_1);
    }
}


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80181BD8(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 1);
  new_var = 0x10000;
}

extern void func_80128940(void);
void func_80181BF8(void) {
    func_80128940();
}


extern s32 func_8012C2D0(void);
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

void func_80181C18(s32 arg0) {
    struct {
        s16 a[8];
        s32 b;
        s32 c;
    } work;

    work.a[3] = 0x306;
    work.a[2] = 0;
    work.a[1] = 0;
    work.a[0] = 0;
    work.a[5] = 0;
    work.a[4] = 0;
    work.b = 0;
    work.a[7] = 0;
    work.a[6] = 0x7FFF;
    {
        s32 ret;
        ret = func_8012C2D0();
        if (ret != 0) {
            func_8012C890((s32)&work, ret, arg0);
        }
    }
}


extern u16 D_8018A3E4[];
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80181C80(a0)
s32 a0;
{
    *(s32 *)(a0 + 0x1C) = D_8018A3E4[*(s16 *)(a0 + 0x70)];
    ((void (*)(void *, s32))func_8012AD44)((void *)a0, 2);
}


extern void func_80182940(s32 a0);
extern void func_8012AD44(s32*, s16);
void func_80181CBC(s32 a0) {
    func_80182940(a0);
    ((void (*)(s32, s32))func_8012AD44)(a0, 0x3);
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801829F0(s32 *a0);

void func_80181CF0(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v;
    s32 p;
    s32 q;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x40;
        if (0x80 < *(s32 *)(s0 + 0xE0)) {
            *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 0x10;
        }
        if (0x300 < *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18)) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) =
                *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) - 0x40;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        }
        if (0x1800 < *(s16 *)(s0 + 0x100)) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 1:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x80;
        *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 4;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) - 0x10;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        if (*(s32 *)(s0 + 0xE0) > 0) {
            break;
        }
        func_8012C218((void *)s0);
        return;
    }
    v = *(u16 *)(s0 + 0x104) + 0x30;
    *(u16 *)(s0 + 0x104) = v;
    v = func_8004787C((s16)v);
    *(u16 *)(s0 + 0x102) = v >> 4;
    func_801829F0((s32 *)s0);
    p = *(s32 *)(s0 + 0x20);
    *(u16 *)(p + 0x10) = *(u16 *)(p + 0x10) + *(u16 *)(s0 + 0x106);
    q = *(s32 *)(s0 + 0x20);
    *(u16 *)(q + 0x14) = *(u16 *)(q + 0x14) + *(u16 *)(s0 + 0x108);
}



extern void (*D_8018A428[])(void);

void func_80181E9C(void *a0) {
    D_8018A428[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 D_81196E5C;

void func_80181ED8(s32 a0) {
    s32 s0;
    s32 s1;

    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)&D_81196E5C;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = 0;
    for (s1 = 0; s1 < 5; s1++) {
        s0 = func_8012C658(0x4B, s1 + 0x100, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 6) = 0;
            *(s16 *)(s0 + 0xA) = 0;
            *(s16 *)(s0 + 0xE) = 0;
            func_80132784(s0, a0, (u16)s1);
            *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48);
            *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4C);
            *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x50);
            *(s32 *)(s0 + 0x64) = 0;
        }
    }
}


void func_80181F98(s32 *a0, s32 *a1) {
    *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a1 + 0x0);
    *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a1 + 0x2);
    *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a1 + 0x4);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = *(u16 *)((s32)a1 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = *(u16 *)((s32)a1 + 0x8);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = *(u16 *)((s32)a1 + 0xA);
}


extern u16 D_8018A438[];
extern void func_80182464(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80181FE8(void *arg0) {
    *(s32 *)((s32)arg0 + 0x1C) = D_8018A438[*(s16 *)((s32)arg0 + 0x70)];
    func_80182464(arg0);
    ((void (*)(void *, s32))func_8012AD44)((void *)arg0, 2);
}


extern void func_80182940(s32 arg0);
    extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80182038(s32 param_1) {
        func_80182940(param_1);
        ((void (*)(s32, s32))func_8012AD44)(param_1, 3);
    }


void func_8018206C(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v;
    s32 p;
    s32 q;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x40;
        if (0x80 < *(s32 *)(s0 + 0xE0)) {
            *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 0x10;
        }
        if (0x400 < *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18)) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) -= 0x80;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        }
        if (0x1800 < *(s16 *)(s0 + 0x100)) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 1:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x80;
        *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 4;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) - 0x40;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        if (*(s32 *)(s0 + 0xE0) > 0) {
            break;
        }
        func_80016714(*(void **)(s0 + 0xD0), 0x84);
        func_8012C218((void *)s0);
        return;
    }
    v = *(u16 *)(s0 + 0x104) + 0x30;
    *(u16 *)(s0 + 0x104) = v;
    v = func_8004787C((s16)v);
    *(u16 *)(s0 + 0x102) = v >> 4;
    func_801829F0((void *)s0);
    p = *(s32 *)(s0 + 0x20);
    *(u16 *)(p + 0x10) = *(u16 *)(p + 0x10) + *(u16 *)(s0 + 0x106);
    q = *(s32 *)(s0 + 0x20);
    *(u16 *)(q + 0x14) = *(u16 *)(q + 0x14) + *(u16 *)(s0 + 0x108);
    func_8018247C((void *)s0);
}


extern void (*D_8018A444[])(void);

void func_80182228(void *a0) {
    D_8018A444[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182264(void *a0)
{
    *(u16 *)((s32)a0 + 0xE4) = 0;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


void func_80182270(void *a0) {
    s16 rect[4];
    u16 t1;
    u16 t2;

    t1 = *(u16 *)((s32)a0 + 0xE4);
    *(u16 *)((s32)a0 + 0xE4) = t1 + 1;
    if ((s16)(t1 + 1) >= 0x30) {
        *(u16 *)((s32)a0 + 0xE4) = 0;
    }
    if (*(s16 *)((s32)a0 + 0xE4) != 0) {
        rect[0] = *(s16 *)((s32)a0 + 0xE4) + 0x340;
        rect[1] = 0;
        rect[2] = 0x30 - *(u16 *)((s32)a0 + 0xE4);
        rect[3] = 0x80;
        MoveImage(rect, 0x340, 0x80);
        rect[0] = 0x340;
        rect[2] = *(u16 *)((s32)a0 + 0xE4);
        MoveImage(rect, 0x370 - *(s16 *)((s32)a0 + 0xE4), 0x80);
    } else {
        rect[0] = 0x340;
        rect[2] = 0x30;
        rect[1] = 0;
        rect[3] = 0x80;
        MoveImage(rect, 0x340, 0x80);
    }

    t2 = *(u16 *)((s32)a0 + 0xE6);
    *(u16 *)((s32)a0 + 0xE6) = t2 - 1;
    if ((s16)(t2 - 1) < 0) {
        *(u16 *)((s32)a0 + 0xE6) = t2 + 0xF;
    }
    if (*(s16 *)((s32)a0 + 0xE6) != 0) {
        rect[0] = *(s16 *)((s32)a0 + 0xE6) + 0x2F0;
        rect[1] = 0x100;
        rect[2] = 0x10 - *(u16 *)((s32)a0 + 0xE6);
        rect[3] = 0x40;
        MoveImage(rect, 0x2F0, 0x140);
        rect[0] = 0x2F0;
        rect[2] = *(u16 *)((s32)a0 + 0xE6);
        MoveImage(rect, 0x300 - *(s16 *)((s32)a0 + 0xE6), 0x140);
    } else {
        rect[0] = 0x2F0;
        rect[1] = 0x100;
        rect[2] = 0x10;
        rect[3] = 0x40;
        MoveImage(rect, 0x2F0, 0x140);
    }
}


void func_8018241C(void *a0) {
    s16 v = (s16)(*(u16 *)((s32)a0 + 0xE8) + 0x30);
    *(u16 *)((s32)a0 + 0xE8) = v;
    *(u16 *)((s32)a0 + 0x52) = func_8004787C(v) >> 8;
}


void func_80182464(void *a0) {
        s32 v0 = *(u16 *)((s32)a0 + 0xA);
        s32 v1 = *(u16 *)((s32)a0 + 0x52);
        *(u16 *)((s32)a0 + 0x52) = 0;
        *(u16 *)((s32)a0 + 0xA) = v0 + v1;
    }


void func_8018247C(void)
{
    register s32 a0 __asm__("$4");
    s32 a1;
    u16 v0;
    u16 v1;

    a1 = *(s32 *)(a0 + 0xD0);
    if (a1 != 0) {
        *(u16 *)(a1 + 0x8) = *(u16 *)(a0 + 0x6);
        v0 = *(u16 *)(a0 + 0xA);
        v1 = *(u16 *)(a0 + 0x52);
        *(u16 *)(a1 + 0xA) = v0 + v1;
        *(u16 *)(a1 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(a1 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(a1 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        *(u16 *)(a1 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(a1 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

void func_80182538(s32 param_1)
{
    s32 p;
    s32 r;
    s32 t;
    s32 f;

    p = func_80132EF4(param_1, 0x72);
    if (p != 0) {
        r = 0x30;
        t = *(u16 *)(p + 6) - r + rand() % 96;
        f = *(u16 *)(p + 0xA);
        *(u16 *)(p + 6) = t;
        *(u16 *)(p + 0xA) = *(u16 *)(param_1 + 0x52) + (f + 0x80);
        r = 0x30;
        t = *(u16 *)(p + 0xE) - r + rand() % 96;
        *(u16 *)(p + 0xE) = t;
    }
}


extern void func_8012AD44(s32 *a0, s16 a1);
extern u16 D_8018A464[];

void func_8018260C(s32 a0) {
    *(s32 *)(a0 + 0x1C) = D_8018A464[*(s16 *)(a0 + 0x70)];
    ((void (*)(void *, s32))func_8012AD44)((void *)a0, 2);
}


extern void func_80182940(s32 arg0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80182648(void *arg0) {
    func_80182940((s32)arg0);
    ((s32 (*)(s32, s32))func_8012AD44)((s32)arg0, 0x3);
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801829F0(s32 *a0);

void func_8018267C(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v;
    s32 p;
    s32 q;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x40;
        if (0x80 < *(s32 *)(s0 + 0xE0)) {
            *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 0x10;
        }
        if (0x1800 < *(s16 *)(s0 + 0x100)) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 1:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x80;
        *(s32 *)(s0 + 0xE0) = *(s32 *)(s0 + 0xE0) - 4;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) - 0x40;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        if (*(s32 *)(s0 + 0xE0) > 0) {
            break;
        }
        func_8012C218((void *)s0);
        return;
    }
    v = *(u16 *)(s0 + 0x104) + 0x30;
    *(u16 *)(s0 + 0x104) = v;
    v = func_8004787C((s16)v);
    *(u16 *)(s0 + 0x102) = v >> 4;
    func_801829F0((s32 *)s0);
    p = *(s32 *)(s0 + 0x20);
    *(u16 *)(p + 0x10) = *(u16 *)(p + 0x10) + *(u16 *)(s0 + 0x106);
    q = *(s32 *)(s0 + 0x20);
    *(u16 *)(q + 0x14) = *(u16 *)(q + 0x14) + *(u16 *)(s0 + 0x108);
}



extern void (*D_8018A484[])(void);

void func_801827DC(void *a0) {
    D_8018A484[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct { s16 a, b, c, d; } SV4_80182818;

void func_80182818(void *a0)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);

    SV4_80182818 sv;
    u8 buf[36];

    sv.a = 0;
    sv.b = *(u16 *)((s32)a0 + 0xE4);
    sv.c = *(u16 *)((s32)a0 + 0xE6);

    func_80049CAC((s32)&sv, (s32)buf);

    *(s32 *)((s32)buf + 0x14) = *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 6);
    *(s32 *)((s32)buf + 0x18) = *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 10) + *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x52);
    *(s32 *)((s32)buf + 0x1C) = *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 14);

    func_8004914C(buf);
    func_800491AC(buf);

    sv.b = 0;
    sv.a = 0;
    sv.c = 0xA0;

    RotTransSV(&sv, &sv, buf + 0x20);

    *(u16 *)((s32)a0 + 6) = sv.a;
    *(u16 *)((s32)a0 + 10) = sv.b;
    *(u16 *)((s32)a0 + 14) = sv.c;
}


void func_801828FC(void) {
}


extern void (*D_8018A4A0[])(void);

void func_80182904(void *a0) {
    D_8018A4A0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80182AD4(s32 a0);
extern s32 func_8012B6D4(s32 a0, s32 a1);
extern s32 func_8012BC60(s32 a0, s32 a1);
extern s32 rand(void);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047D3C(s32 a0);

void func_80182940(s32 param_1)
{
    s32 v0;
    s32 s1;
    s32 s0;
    s32 t;

    v0 = func_80182AD4(param_1);
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        return;
    }
    s1 = v0 + 4;
    s0 = param_1 + 4;
    *(u16 *)(param_1 + 0x100) = func_8012B6D4(s1, s0);
    t = rand() & 0xFFF;
    *(u16 *)(param_1 + 0x104) = t;
    *(s16 *)(param_1 + 0x102) = func_8004787C(t) >> 4;
    *(s32 *)(param_1 + 0xE0) = func_80047D3C(func_8012BC60(s1, s0));
    *(s16 *)(param_1 + 0xFE) = -(rand() & 0x1F);
    *(u16 *)(param_1 + 0x106) = rand() & 0xF0;
    *(u16 *)(param_1 + 0x108) = rand() & 0xF0;
}


void func_801829F0(s32* a0)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);

    typedef struct { u16 a, b, c; } SV3;

    u8 buf[32];
    SV3 sv;
    s32 out[2];
    s32 p;

    p = *(s32 *)((s32)a0 + 0xCC);
    if (p != 0) {
        sv.a = 0;
        sv.b = *(u16 *)((s32)a0 + 0x100);
        sv.c = *(u16 *)((s32)a0 + 0x102);

        func_80049CAC((s32)&sv, (s32)buf);

        *(s32 *)(buf + 0x14) = *(s16 *)(p + 6);
        *(s32 *)(buf + 0x18) = *(s16 *)(p + 0xA);
        *(s32 *)(buf + 0x1C) = *(s16 *)(p + 0xE);

        sv.a = 0;
        sv.b = *(u16 *)((s32)a0 + 0xFE);
        sv.c = -*(s32 *)((s32)a0 + 0xE0);

        func_8004914C(buf);
        func_800491AC(buf);

        RotTransSV(&sv, &sv, out);

        *(u16 *)((s32)a0 + 6) = sv.a;
        *(u16 *)((s32)a0 + 10) = sv.b;
        *(u16 *)((s32)a0 + 14) = sv.c;
    }
}


extern u8 D_801202A0[];

s32 func_80182AD4(s32 a0) {
    s32 i;
    u8 *v1;

    v1 = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)v1 == 0x306) {
            return (s32) v1;
        }
        v1 += 0x10C;
    }
    return 0;
}


#include "common.h"

/* func_80182B10 — ov_SC07_002 state tick on the 0x34 halfword state field.
 *
 * §199-G LEVER (the whole function): the 2-arm dispatch looks like a `switch`
 * but is NOT one.  A 2-case switch never splits (`balance_case_nodes`' gate is
 * `if (i > 2)`), so its list stays flat with case 0 at the ROOT and it emits
 * `beqz→arm0 ; li 1 ; beq→arm1 ; j default`.  The target instead leads with a
 * POSITIVE `beq $v1,1 →arm1`, then a `slti $v1,2 / beqz →default` RANGE test,
 * then `bnez →default` and FALLS INTO arm 0 — three tests for two values, and
 * no `j default` fall-out.  That is §199-G's nested-inverted spelling
 * `if (x != A) { ...inner... } else { bodyA }`, whose header is all-positive up
 * front with the LAST test inverted; the extra `slti` is the redundant `x < 2`
 * the source spends before re-testing `x == 0`.  Writing it as a bare switch
 * costs 4 mismatches at idx 5-8 (verified).
 *
 * §263 / the delay-slot tell: `jal func_80178B18` has a bare `nop` in its slot
 * — no `move $a0,$s0`.  Passing `s0` there emits that move (idx 24 residual);
 * passing the PARAMETER `arg0` keeps a second pseudo live in its incoming $a0
 * from entry to the call (no intervening call), so reload deletes the no-op
 * copy.  A `register __asm__("$16")` pin on s0 is the WRONG fix here: it forces
 * gcc to park the parameter in $a1 first (`move $a1,$a0 ; move $s0,$a1`), +1 ins.
 *
 * func_80178970 / func_80178D18 carry `(void)` prototypes at TU L2538/L2546 but
 * are called with the entity pointer, so they go through this TU's established
 * function-pointer-cast idiom (cf. func_80182C68 L6135, func_80182DF0 L6192)
 * rather than a conflicting redeclaration.
 *
 * Whole-TU compile verified: spliced over the INCLUDE_ASM the emitted asm is
 * instruction-identical to the standalone MATCH (local label numbers only).
 */

extern s32 func_80178B18(s32 param_1, s32 param_2);
extern int func_80178970(void);
extern void func_80178D18(void);
extern u8 D_8018A418;
extern void func_80016450(s32 a0, s32 a1);
extern void func_80184C70(void);
extern void func_80181C18(s32 arg0);
extern void func_80181ED8(s32 a0);
extern void func_8012C218(void *a0);
extern u16 D_8019FF8A;
extern s16 D_8019F070;

void func_80182B10(s32 arg0) {
    s32 s0 = arg0;
    s32 x = *(u16 *)(s0 + 0x34);

    if (x != 1) {
        if (x < 2) {
            if (x == 0) {
                if (*(s16 *)(s0 + 0x70) == 0 && D_8019F070 != 0) {
                    func_80178B18(arg0, (s32)&D_8018A418);
                    *(s16 *)(s0 + 0xF6) = 0xFF;
                    func_80016450(0xFF, 1);
                    func_80184C70();
                    *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
                }
            }
        }
    } else {
        if (((s32 (*)(s32))func_80178970)(s0) != 0) {
            ((void (*)(s32))func_80178D18)(s0);
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_80181C18(s0);
        }
        func_80016450(*(u8 *)(s0 + 0xF6), 1);
    }
    if (D_8019FF8A & 0x4000) {
        func_80181ED8(s0);
        func_8012C218((void *)s0);
    }
}


void func_80182C18(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;
    extern s32 rand(void);
    extern s32 func_8012BEE8(s32 a0);

    *(s16 *)(s0 + 0x52) = (rand() & 3) * 2 - 3;
    if (func_8012BEE8(s0) != 0) {
        func_80181CBC(s0);
    }
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80182264(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_80197494;
extern s32 D_80197B04;

void func_80182C68(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s1 = a0;
    s0 = func_8012C1B8();
    *(s32 *)(s1 + 0x20) = s0;
    if (s0 == 0) {
        ((void (*)(void *))func_8012CAE4)(s1);
    } else {
        func_8001C214(s0, (s32)&D_80197494);
        *(u16 *)(s0 + 0x1c) = 0x3000;
        *(u16 *)(s0 + 0x1a) = 0x3000;
        *(u16 *)(s0 + 0x18) = 0x3000;
        *(u16 *)(s0 + 0x2c) = *(u16 *)(s0 + 0x2c) | 0x10;
        *(s16 *)(s1 + 0xa) = -0x340;
        if (*(s16 *)(s1 + 0x70) == 0) {
            func_80182264(s1);
        }
        s0 = func_8012C1B8();
        *(s32 *)(s1 + 0xd0) = s0;
        if (s0 != 0) {
            func_8001C214(s0, (s32)&D_80197B04);
            *(u16 *)(s0 + 0x2c) = *(u16 *)(s0 + 0x2c) | 0x10;
            v0 = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x18);
            *(u16 *)(s0 + 0x1c) = v0;
            *(u16 *)(s0 + 0x1a) = v0;
            *(u16 *)(s0 + 0x18) = v0;
        }
        func_8012AD50(s1);
    }
}


extern void func_8018247C(void);
extern void func_80182270(void *a0);
extern void func_8018241C(void *a0);
extern void func_80182538();
extern void func_80181FE8(void *a0);
extern u16 D_800B99DA;
extern u16 D_8019FF8A;

void func_80182D50(void *a0) {
    u8 *p = *(u8 **)((s32)a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) - 0x20;
    func_8018247C();
    if (*(s16 *)((s32)a0 + 0x70) == 0) {
        func_80182270(a0);
    }
    func_8018241C(a0);
    if ((D_800B99DA & 3) == 0) {
        func_80182538(a0);
    }
    if (D_8019FF8A & 0x4000) {
        func_80181FE8(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80182038(s32 param_1);
extern void func_8018247C(void);

void func_80182DF0(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;

    *(s16 *)(s0 + 0x52) = (rand() & 3) * 2 - 3;
    if (func_8012BEE8(s0) != 0) {
        func_80182038(s0);
    }
    ((void (*)(s32))func_8018247C)(s0);
}


extern s32 D_80197C64;
extern u8 D_8018A454[];
extern u8 D_8018A45C[];

void func_80182E48(int param_1)
{
  int v0;
  short sVar1;
  int idx;

  v0 = func_8012C1B8();
  *(int *)(param_1 + 0x20) = v0;
  if (v0 == 0) {
    func_8012CAE4(param_1);
  } else {
    func_8001C214(v0, &D_80197C64);
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
         *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    idx = ((short)*(u16 *)(param_1 + 0x70) % 3) * 0x10000 >> 0xf;
    sVar1 = *(u16 *)(D_8018A454 + idx);
    *(short *)(param_1 + 0xe6) = sVar1;
    *(short *)(param_1 + 0xe4) = sVar1 + *(short *)(*(int *)(param_1 + 0x64) + 0x70) * 0x300;
    *(u16 *)(param_1 + 0xe8) = *(u16 *)(D_8018A45C + idx);
    func_8012AD50(param_1);
  }
}


void func_80182F2C(void *a0)
{
    extern u16 D_8019FF8A;
    s32 q;
    u16 g;

    func_80182818(a0);
    q = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(q + 0x12) = *(u16 *)(q + 0x12) + 0x80;
    g = D_8019FF8A;
    *(u16 *)((s32)a0 + 0xE4) = *(u16 *)((s32)a0 + 0xE4) + *(u16 *)((s32)a0 + 0xE8);
    if (g & 0x4000) {
        func_8018260C((s32)a0);
    }
}


void func_80182F94(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;
    extern s32 rand(void);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_80182648(void *a0);

    *(s16 *)(s0 + 0x52) = (rand() & 3) * 2 - 3;
    if (func_8012BEE8(s0) != 0) {
        func_80182648((void *)s0);
    }
}


void func_80182FE4(s32 param_1) {
    extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 rand(void);
    extern void (*D_8018A494[])(void);
    s32 q;
    s32 t;

    func_8001CC3C(*(s32 *)(param_1 + 0x20), (s32)D_8018A494, 0x240, 0xE0);

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) = *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) | 0x58000000;

    t = (rand() & 0x3F0) + 0x600;
    q = *(s32 *)(param_1 + 0x20);
    *(u16 *)(q + 0x1a) = t;
    *(u16 *)(q + 0x18) = t;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x79;

    *(s32 *)(param_1 + 0x14) = 0x80000;
    *(s32 *)(param_1 + 0x1C) = 0xC;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_801292C8(u8 *a0);
extern void func_8012931C(struct vec *a0);

void func_80183078(int param_1)
{
    if (*(int *)(param_1 + 0x1c) != 0) {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) - 1;
        func_8012931C((struct vec *)param_1);
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) = *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x40;
    } else {
        func_801292C8((u8 *)param_1);
    }
}


typedef struct { s32 a[14]; } Blk38;
extern Blk38 D_8018A4F0;

void func_801830D8(s32 *a0)
{
    extern u8 D_8019F0F0[];
    extern s16 D_8019FD68;
    extern s32 func_80029504(void);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32 func_8012C51C(void *a0, s32 a1);

    struct {
        u16 f0;  /* 0x10 */
        s16 f2;  /* 0x12 */
        u16 f4;  /* 0x14 */
        u16 f6;  /* 0x16 */
        u16 f8;  /* 0x18 */
        u16 fA;  /* 0x1A */
        u16 fC;  /* 0x1C */
        u16 fE;  /* 0x1E */
        s32 f10; /* 0x20 */
    } sub;

    s16 i;

    for (i = 0; i < 0x39; i++) {
        *(Blk38 *)(D_8019F0F0 + i * 0x38) = D_8018A4F0;
    }

    sub.f6 = 0x352;
    D_8019FD68 = 0;
    sub.f8 = 0xFFFF;
    sub.fA = 0;
    sub.fC = 0;
    if ((u32)func_80029504() < 0x640) {
        sub.fE = 0;
        func_8002D4C8(0xBA7, 0);
    } else {
        sub.fE = 1;
    }
    sub.f10 = 0;
    sub.f0 = *(u16 *)((s32)a0 + 6);
    sub.f2 = -0x208;
    sub.f4 = *(u16 *)((s32)a0 + 0xE);
    func_8012C51C(&sub, (s32)a0);
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void GsMapModelingData(u32 *p);
extern s16 D_8019FD68;
extern u8 D_8019F0F0[];
extern s32 D_8019F0E0[];
extern u32 *D_80197DCC;
extern s32 D_80186B14;
extern void (*D_8018A4B4)(void *);

void func_801831FC(s32 param_1)
{
    /* the 0x10..0x20 sub-block handed to func_8012C51C — same spelling as func_801830D8 */
    struct {
        u16 f0;  /* 0x10 */
        s16 f2;  /* 0x12 */
        u16 f4;  /* 0x14 */
        u16 f6;  /* 0x16 */
        u16 f8;  /* 0x18 */
        u16 fA;  /* 0x1A */
        u16 fC;  /* 0x1C */
        u16 fE;  /* 0x1E */
        s32 f10; /* 0x20 */
    } sub;
    s16 i;      /* ONE pseudo: the loop counter AND the 0x200/0x600 value -> $s0 in both arms */
    s16 *pp;
    u32 **pd;   /* &D_80197DCC held in a call-saved reg across GsMapModelingData */
    s32 o;
    s32 t;

    if (*(s16 *)(param_1 + 0x70) < 0) {
        sub.f6 = 0x352;
        sub.fA = 0;
        sub.fC = 0;
        sub.f10 = *(s16 *)(param_1 + 0xFC);
        sub.f0 = *(u16 *)(param_1 + 6);
        sub.f2 = -0x208;
        sub.f4 = *(u16 *)(param_1 + 0xE);
        for (i = 0; i < 0x13; i++) {
            sub.f8 = i;
            sub.fE = D_8019FD68++;
            func_8012C51C(&sub, param_1);
        }
        if (*(s16 *)(param_1 + 0x10A) == 0) {
            pd = &D_80197DCC;
            GsMapModelingData(*pd);
            func_80132288(D_8019F0E0, (s32 *)&D_8018A4B4, (s32)*pd);
        }
        pp = (s16 *)(param_1 + 0xF0);
        /* both stores duplicated in each arm: cross-jump merges only the last 3 ins */
        if (*(s16 *)(param_1 + 0xFC) == 0) {
            pp[*(s16 *)(param_1 + 0x10A) * 2 + 1] = 0x38;
            pp[*(s16 *)(param_1 + 0x10A) * 2] = 0x600;
        } else {
            pp[*(s16 *)(param_1 + 0x10A) * 2 + 1] = 0x38;
            pp[*(s16 *)(param_1 + 0x10A) * 2] = 0x200;
        }
        *(s16 *)(param_1 + 2) = 1;
    } else {
        o = func_8012C1B8();
        *(s32 *)(param_1 + 0x20) = o;
        if (o == 0) {
            func_8012CAE4(param_1);
            return;
        }
        func_8001C214(o, (s32)&D_80197DCC);
        func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x7FFF, 0x7FFF);
        func_8012A828(param_1, &D_80186B14);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0xA0;
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) =
            (s32)&D_8019F0F0[*(s16 *)(param_1 + 0xFC) * 0x38];
        i = 0x200;
        if (*(s32 *)(param_1 + 0xDC) == 0) {
            i = 0x600;
        }
        t = *(s32 *)(param_1 + 0x20);
        *(s16 *)(t + 0x1C) = i;
        *(s16 *)(t + 0x18) = i;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = 0;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(s16 *)(param_1 + 0x70) * 0xE3;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)(param_1 + 0x1C) = 8;
        *(s16 *)(param_1 + 2) = 2;
    }
}


INCLUDE_ASM("asm/ov_SC07_002/nonmatchings/ov_SC07_002_jr_8017C8D0", func_80183458);

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012C218(void *a0);
extern s32 func_80047D3C(s32 a0);
extern u8 D_8019F0F0[];

void func_801838FC(void *a0) {
    u16 m[3];
    void *v1p;
    s32 v1;
    s32 t0;
    s32 sum;
    s32 dist;
    s32 col;
    u8 *row;

    (*(s32 *)((s32)a0 + 0x1C))--;
    v1p = *(void **)((s32)a0 + 0x20);
    *(u16 *)((s32)v1p + 0x18) = *(u16 *)((s32)v1p + 0x1C) =
        *(u16 *)((s32)v1p + 0x1C) + 0x80;
    if (*(s16 *)((s32)a0 + 0x108) == 0) {
        m[0] = 0x9C;
        m[1] = 0;
        m[2] = 0x372;
        ApplyMatrixSV((void *)(*(void **)((s32)a0 + 0x20) + 0x34), m, m);
        m[0] = m[0] + *(u16 *)((s32)a0 + 6);
        t0 = (s16)m[0] * (s16)m[0];
        m[2] = m[2] + *(u16 *)((s32)a0 + 0xE);
        sum = t0 + (s16)m[2] * (s16)m[2];
        if (0xD23FF < sum) {
            dist = func_80047D3C(sum) - 0x3A0;
            if (dist >= 0x80) {
                goto kill;
            }
            col = 0xFF - dist * 2;
            v1 = *(s16 *)((s32)a0 + 0xFC);
            row = &D_8019F0F0[v1 * 0x38];
            *(u16 *)(row + 0x34) = col;
            *(u16 *)(row + 0x32) = col;
            *(u16 *)(row + 0x30) = col;
        }
    }
    if (*(s32 *)((s32)a0 + 0x1C) == 0) {
kill:
        func_8012C218(a0);
    }
}


extern void (*D_8018A528[])(void);

void func_80183A34(void *a0) {
    D_8018A528[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018A53C[])(void);

void func_80183A70(void *a0) {
    D_8018A53C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 param_1);
extern void func_8001C214(s32 param_1, s32 param_2);
extern void func_8012B2CC(s32 param_1);
extern void func_8012B178(s32 param_1, s32 param_2);

void func_80183AAC(s32 param_1) {
    s32 unused[2]; /* dead -- frame padding */
    s16 raw;
    s32 r;
    s32 obj;
    s32 sgn;
    s32 v;
    s16 *p;
    s32 q;
    s32 w;

    obj = func_8012C1B8();
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
    *(s16 *)(obj + 0x12) = rand() % 4096;
    *(s32 *)(param_1 + 0x48) = 0xC000;
    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B178(param_1, -0x80000 - ((r % 8) << 16));
    *(s32 *)(param_1 + 0x1C) = 0x3C;
    *(s16 *)(param_1 + 0xFE) = rand() & 0xF0;
    *(s16 *)(param_1 + 0x100) = rand() & 0x1F0;
    *(s16 *)(param_1 + 0x102) = rand() & 0x30;

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

    p += 4;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
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

    p += 4;

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
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[2] = w;

    p += 4;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[0] = w;
    p[1] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[2] = w;

    *(s16 *)(param_1 + 0x104) = (rand() % 4) * 0x20;
    *(s16 *)(param_1 + 0x106) = (rand() % 8) * 0x20;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}









extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012CBF4(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_80183FE0(s32 p);
extern void func_8012C218(void *arg0);

void func_80183F28(s32 param_1)
{
    s32 iVar1;

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0x100);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x102);

    iVar1 = func_8012BEE8(param_1);
    if (iVar1 != 0) {
        goto LAB_80183FAC;
    }
    if (*(s16 *)(param_1 + 0x70) != 0) {
        goto LAB_80183FBC;
    }
    iVar1 = func_8012CBF4(param_1);
    if (iVar1 == 0) {
        goto LAB_80183FC4;
    }
LAB_80183FAC:
    func_8012C218((void *)param_1);
    return;
LAB_80183FBC:
    func_8012AD80(param_1);
LAB_80183FC4:
    func_80183FE0(param_1);
}


#define gte_SetRotMatrix_1(r0) __asm__ __volatile__ ( \
    "lw $12, 0( %0 );"   \
    "lw $13, 4( %0 );"   \
    "ctc2 $12, $0;"      \
    "ctc2 $13, $1;"      \
    "lw $12, 8( %0 );"   \
    "lw $13, 12( %0 );"  \
    "lw $14, 16( %0 );"  \
    "ctc2 $12, $2;"      \
    "ctc2 $13, $3;"      \
    "ctc2 $14, $4"       \
    : : "r"( r0 ) : "$12", "$13", "$14" )
#define gte_SetTransMatrix_1(r0) __asm__ __volatile__ ( \
    "lw $12, 20( %0 );"  \
    "lw $13, 24( %0 );"  \
    "ctc2 $12, $5;"      \
    "lw $14, 28( %0 );"  \
    "ctc2 $13, $6;"      \
    "ctc2 $14, $7"       \
    : : "r"( r0 ) : "$12", "$13", "$14" )
#define gte_ldclmv_1(r0) __asm__ __volatile__ ( \
    "lhu $12, 0( %0 );"  \
    "lhu $13, 6( %0 );"  \
    "lhu $14, 12( %0 );" \
    "mtc2 $12, $9;"      \
    "mtc2 $13, $10;"     \
    "mtc2 $14, $11"      \
    : : "r"( r0 ) : "$12", "$13", "$14" )
#define gte_rtir_1() __asm__ __volatile__ ( "nop;nop;mvmva 1, 0, 3, 3, 0" )
#define gte_stclmv_1(r0) __asm__ __volatile__ ( \
    "mfc2 $12, $9;"      \
    "mfc2 $13, $10;"     \
    "mfc2 $14, $11;"     \
    "sh $12, 0( %0 );"   \
    "sh $13, 6( %0 );"   \
    "sh $14, 12( %0 )"   \
    : : "r"( r0 ) : "$12", "$13", "$14", "memory" )
#define gte_ldlv0_1(r0) __asm__ __volatile__ ( \
    "lhu $13, 4( %0 );"  \
    "lhu $12, 0( %0 );"  \
    "sll $13, $13, 16;"  \
    "or $12, $12, $13;"  \
    "mtc2 $12, $0;"      \
    "lwc2 $1, 8( %0 )"   \
    : : "r"( r0 ) : "$12", "$13" )
#define gte_rt_1() __asm__ __volatile__ ( "nop;nop;mvmva 1, 0, 0, 0, 0" )
#define gte_stlvnl_1(r0) __asm__ __volatile__ ( \
    "swc2 $25, 0( %0 );" \
    "swc2 $26, 4( %0 );" \
    "swc2 $27, 8( %0 )"  \
    : : "r"( r0 ) : "memory" )
#define gte_ldv3_1(r0, r1, r2) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 );"  \
    "lwc2 $2, 0( %1 );"  \
    "lwc2 $3, 4( %1 );"  \
    "lwc2 $4, 0( %2 );"  \
    "lwc2 $5, 4( %2 )"   \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_ldv0_1(r0) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 )"   \
    : : "r"( r0 ) )
#define gte_rtpt_1() __asm__ __volatile__ ( "nop;nop;rtpt" )
#define gte_rtps_1() __asm__ __volatile__ ( "nop;nop;rtps" )
#define gte_avsz4_1() __asm__ __volatile__ ( "nop;nop;avsz4" )
#define gte_stflg_1(r0) __asm__ __volatile__ ( \
    "cfc2 $12, $31;"     \
    "nop;"               \
    "sw $12, 0( %0 )"    \
    : : "r"( r0 ) : "$12", "memory" )
#define gte_stsxy3_1(r0, r1, r2) __asm__ __volatile__ ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 );" \
    "swc2 $14, 0( %2 )"  \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) : "memory" )
#define gte_stsxy_1(r0) __asm__ __volatile__ ( \
    "swc2 $14, 0( %0 )"  \
    : : "r"( r0 ) : "memory" )
#define gte_stotz_1(r0) __asm__ __volatile__ ( \
    "swc2 $7, 0( %0 )"   \
    : : "r"( r0 ) : "memory" )

/* Billboard POLY_FT4 emitter: rotates the entity matrix (obj->0x20 + 0x34) through the
 * camera matrix D_800AF648 into a stack MATRIX, projects the four corners, and links the
 * 0x28-byte primitive into OT bucket D_800A6610[D_800B9A02 << 14]. */
void func_80183FE0(s32 p)
{
    /* [T51] all decls block-scoped: they constrain nothing later in the host TU.
     * D_800A5E60 / D_800A6610 use this TU's existing block-scope spellings
     * (ov_SC07_001_jr_8017BEBC.c:2821-2822); D_800B9A02 AGREES with the file-scope
     * `extern short D_800B9A02;` at line 2469 (unsigned access forced at use,
     * §8d sub-class (b)); D_800AF648 is the project-wide `extern u8` spelling. */
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF648;

    typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017FE38_80183FE0;   /* 0x20 */

    MTX_8017FE38_80183FE0 mat;                       /* sp+0x00 */
    struct { s32 flag, flag2, otz; } g;     /* sp+0x20 */
    u8 *pkt;
    u32 ot;
    u32 d;
    MTX_8017FE38_80183FE0 *r0;
    u8 *va;
    u32 x, y, tp, a, b, w;
    /* forced copy of the tpage word (§ ov_SC04_005 func_80181470 idiom): the target keeps
     * `addu $v0,$v1,$zero` because the stored/masked value and the `& 0x10` test read two
     * distinct pseudos; every plain spelling gets them coalesced. */
    register s32 zr __asm__("$0");
    s32 z;
    u32 *otp;

    pkt = D_800A5E60;
    d = *(u16 *)&D_800B9A02;
    D_800A5E60 = pkt + 0x28;
    *(u8 *)(pkt + 3) = 9;
    *(u32 *)(pkt + 4) = 0x808080;
    va = (u8 *)(p + 0xDC);
    *(u8 *)(pkt + 7) = 0x2C;
    ot = (u32)&D_800A6610[d << 14];

    r0 = (MTX_8017FE38_80183FE0 *)&D_800AF648;
    gte_SetRotMatrix_1(r0);
    gte_ldclmv_1(*(s32 *)(p + 0x20) + 0x34);
    gte_rtir_1();
    gte_stclmv_1((s16 *)&mat);
    gte_ldclmv_1(*(s32 *)(p + 0x20) + 0x36);
    gte_rtir_1();
    gte_stclmv_1((s16 *)&mat + 1);
    gte_ldclmv_1(*(s32 *)(p + 0x20) + 0x38);
    gte_rtir_1();
    gte_stclmv_1((s16 *)&mat + 2);
    gte_SetTransMatrix_1(r0);
    gte_ldlv0_1(*(s32 *)(p + 0x20) + 0x48);
    gte_rt_1();
    gte_stlvnl_1(&mat.t[0]);
    gte_SetRotMatrix_1(&mat);
    gte_SetTransMatrix_1(&mat);
    gte_ldv3_1(va, p + 0xE4, p + 0xEC);
    gte_rtpt_1();
    gte_stflg_1(&g.flag);
    gte_stsxy3_1(pkt + 8, pkt + 0x10, pkt + 0x18);
    gte_ldv0_1(p + 0xF4);
    gte_rtps_1();
    gte_stflg_1(&g.flag2);
    g.flag = g.flag | g.flag2;
    gte_stsxy_1(pkt + 0x20);
    gte_avsz4_1();
    gte_stotz_1(&g.otz);

    if ((g.flag & ~0x1000) == 0) {
        x = *(u16 *)(p + 0x104);
        y = *(u16 *)(p + 0x106);
        *(u16 *)(pkt + 0xE) = 0x7800;
        x = x + 0x140;
        a = (y & 0x100) >> 4;
        b = ((x & 0x3C0) >> 6) | 0x80;
        w = a | b | ((y & 0x200) << 2);
        tp = w + zr;
        *(u16 *)(pkt + 0x16) = tp;
        tp = tp & 0xF;
        x -= tp << 6;
        x <<= 1;
        tp = y & 0xFFFF;
        *(u8 *)(pkt + 0xC) = x;
        if (w & 0x10) {
            tp = tp - 0x100;
        }
        *(u8 *)(pkt + 0xD) = tp;
        *(u8 *)(pkt + 0x14) = *(u8 *)(pkt + 0xC) + 0x1F;
        *(u8 *)(pkt + 0x1D) = *(u8 *)(pkt + 0xD) + 0x1F;
        *(u8 *)(pkt + 0x15) = *(u8 *)(pkt + 0xD);
        *(u8 *)(pkt + 0x1C) = *(u8 *)(pkt + 0xC);
        *(u8 *)(pkt + 0x24) = *(u8 *)(pkt + 0x14);
        *(u8 *)(pkt + 0x25) = *(u8 *)(pkt + 0x1D);
        z = g.otz + 1;
        if (z >= 0x1000) {
            z = 0x1000;
        }
        otp = (u32 *)(z * 4 + ot);
        *(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (*otp & 0xFFFFFF);
        *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
    }
}


extern u16 D_8018A4CC[];

void func_8018439C(s32 param_1)
{
    s32 t;
    s32 p;
    s16 h;

    t = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = t;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = D_8018A4CC[7 - t];
    p = *(s32 *)(param_1 + 0x20);
    h = *(u16 *)(p + 0x1C) + 0x20;
    *(u16 *)(p + 0x1C) = h;
    *(u16 *)(p + 0x18) = h;
    if (*(s32 *)(param_1 + 0x1C) == 0) {
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        *(s32 *)(param_1 + 0x1C) = 0x30;
    }
}


extern s32 D_8019F0EC;
extern void func_8012C218(void *arg0);

void func_80184410(s32 arg0)
{
    (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) += 0x94;
    if ((D_8019F0EC & 0x4000) && (*(s32 *)(arg0 + 0x64) != 0))
        func_8012C218(arg0);
}


extern void (*D_8018A544[])(void);

void func_80184470(void *a0) {
    D_8018A544[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012AD50(void *a0);
    void func_801844AC(u8 *a0) {
        *(s16 *)(a0 + 0xFC) = 0;
        *(u16 *)(a0 + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];
extern s32 func_80029504(void);
extern s16 func_8012A758(void);
extern s16 func_8012A68C(void);

void func_801844D8(void)
{
    s32 iVar1;
    s16 sVar2;
    s16 sVar3;
    s16 tmp;

    iVar1 = func_80029504();
    sVar2 = func_8012A758();
    sVar3 = func_8012A68C();
    if (iVar1 < 0x640) {
        D_800B9AB8[0] = (sVar2 * 0x140) / 0x1000;
        tmp = ((sVar3 * -15) << 4) / 682;
        if (tmp < 0) {
            tmp = 0;
        }
        D_800B9ABA[0] = tmp;
    }
}


void func_80184594(void) {

    extern s16 D_8019FE84;
    s16 *p = &D_8019FE84;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_801845B8 — cookbook §71 (sibling-first).
 * func_80184658 is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_80184658(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_80184774 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
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


extern void func_80184658(s32 arg0, s32 arg1, s32 arg2);
extern void func_80184774(s32 arg0, Rec_8018A6A4_801845B8 *arg1, s32 arg2, s32 arg3);

void func_801845B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_801845B8 sp10;
    s32 i;
    s32 ang;

    func_80184658(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_80184774(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



    extern s16 D_8019FE7E;
    extern s16 D_8019FE80;
    extern s16 D_8019FE82;
    void func_80184658(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_8019FE7C;
        D_8019FE7C = *(u16 *)((s32)arg0 + 0x0);
        D_8019FE7E = *(u16 *)((s32)arg0 + 0x2);
        D_8019FE80 = arg1;
        D_8019FE82 = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80184688(s32 a0) {

    extern s16 D_8019FE7C;
    extern s16 D_8019FE7E;
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

    D_8019FE7C = sxy[0];
    D_8019FE7E = sxy[1];
}


extern s16 D_8019FE82;
    void func_80184700(s32 arg0) {
        *(s16 *)((s32)&D_8019FE82 + 0x0) += arg0;
    }




extern s32 func_80184848(void);
extern void func_80184774();

void func_8018471C(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_80184848();
    if (v0 >= 0) {
        func_80184774(v0, (void *)a0, a1, a2);
    }
}



/* func_80184774 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
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
 * (2) func_80184774 itself — the TU prototypes it at L3570 as
 *     `extern void func_80184774(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_80184774") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_8019FE84 / rand — declared VERBATIM as the TU already has them
 *     (D_8019FE84: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_80184774");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_8019FE84;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_8019FE84);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_80184774 *)((u8 *)s1 + 6) = *(B4_80184774 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_80184774 *)((u8 *)s1 + 10) = *(B4_80184774 *)a3;
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




s32 func_80184848(void) {

    extern s16 D_8019FE84;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_8019FE84 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_80184884(s32 a0, s32 a1) {

    extern s16 D_8019FE84;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_8019FE84);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_801848D0 — 16-entry table walk, stride 0xE, over D_8019FE84.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_8019FE84; s16 *p = &D_8019FE84; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_801849AC(s32 arg0);

void func_801848D0(void) {

    extern s16 D_8019FE84;
    s16 *p = &D_8019FE84;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_801849AC(i);
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



/* func_801849AC — draws one entry of the 16-slot D_8019FE84 particle table:
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
 * LEVERS (each byte-checked against asm/.../func_801849AC.s)
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
 *      instead of EA,E4,E6.  `lh $a0,D_8019FE82` is a single-set SET(REG,…) —
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
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_8019FE7C/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_8019FE80, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_801849AC is byte-identical.
 */

void func_801849AC(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_801849AC D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_8019FE7C;
    extern s16 D_8019FE7E;
    extern s16 D_8019FE80;
    extern s16 D_8019FE84;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_801849AC m;                    /* sp+0x10 */
    s16 sv[4];                           /* sp+0x30 */
    s16 out[4];                          /* sp+0x38 */
    s32 v[2];                            /* sp+0x40 — 3rd word lives in the temp area */
    void *mp;
    u8 *p;
    u8 *ent;
    s32 ot;
    u16 bx;
    u16 by;
    register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */
    volatile u16 *bidx;
    s32 t;
    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */

    m = D_800AE620;
    mp = &m;

    ent = (u8 *)((arg0 * 14) + (s32)&D_8019FE84);
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

    ang = D_8019FE82;
    bx = (u16)D_8019FE7C;
    by = (u16)D_8019FE7E;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_8019FE80;
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
    bidx = (volatile u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (*(u32 *)(*(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)) + 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
}


void func_80184C70(void) {

    extern s16 D_8019FD7C;
    s16 *p = &D_8019FD7C;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_80184CBC(s32 a0);

void func_80184C94(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_80184CBC((s32)pv);
}



/* func_80184CBC — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_8019A3A8 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_80184D44 arg0
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
 * func_800491AC / RotTransPers at file scope L3484-3486; func_80184D44 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_8019A3A8 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80184D44(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_80184CBC(s32 a0) {
    extern u8 D_800AF648;
    extern V4_80184CBC D_8019A3A8;
    u16 sxy[4];
    s32 pv[4];

    *(V4_80184CBC *)pv = D_8019A3A8;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_80184D44(sxy, pv, 0x10, 0x18);
}



extern void func_80184DB0(void *a0, void *a1, s16 a2);
extern void func_80184EE4(s32 a0, s16 a1, u16 a2);

void func_80184D44(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_80184DB0(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_80184EE4(i, j, arg3);
    }
}





void func_80184DB0(void *a0, void *a1, s16 a2) {

    extern s16 D_8019FD70;
    extern s16 D_8019FD72;
    extern u8 D_8019FD78;
    extern u8 D_8019FD79;
    extern u8 D_8019FD7A;
    extern u32 D_8019FD74;
    if (a0 != NULL) {
        D_8019FD70 = *(u16 *)a0;
        D_8019FD72 = *(u16 *)((s32)a0 + 2);
    } else {
        D_8019FD70 = 0;
        D_8019FD72 = 0;
    }

    D_8019FD78 = *(u8 *)a1;
    D_8019FD79 = *(u8 *)((s32)a1 + 1);
    D_8019FD7A = *(u8 *)((s32)a1 + 2);
    D_8019FD74 = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80184E20(s32 a0) {

    extern s16 D_8019FD70;
    extern s16 D_8019FD72;
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

    D_8019FD70 = sxy[0];
    D_8019FD72 = sxy[1];
}




extern s32 func_80185000(void);
extern void func_80184EE4(s32 a0, s16 a1, u16 a2);

void func_80184E98(s32 a0, s32 a1) {
    s32 result = func_80185000();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_80184EE4(result, ext_a0, (u16)a1);
    }
}



/* func_80184EE4 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_8019FD7C.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_8019FD7C : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_8019FD76 : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_80184EE4(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_80184EE4");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_8019FD7C;
    extern s16 D_8019FD76[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_80184EE4 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_80184EE4 *)((s32)&D_8019FD7C + (a0 << 4));

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
    p->f4 = (s32)D_8019FD76[0] * 64;
}




s32 func_80185000(void) {

    extern s16 D_8019FD7C;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_8019FD7C + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_8018503C — the 16-slot particle/effect stepper over D_8019FD7C[16]
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
 * D_8019FD7C uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018503C(void) {

    extern s16 D_8019FD76;
    extern s16 D_8019FD7C;
    extern void func_80185150(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_8019FD76;
    p = &D_8019FD7C;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_80185150(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_80185150 — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_8019FD7C[a0] record, projects the
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


/* 0x10-byte-stride record table at D_8019FD7C (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_80185150(s32 a0) {

    extern s16 D_8019FD70;
    extern s16 D_8019FD72;
    extern u8 D_8019FD78;
    extern u8 D_8019FD79;
    extern u8 D_8019FD7A;

    extern s16 D_8019FD7C;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_80185150 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_80185150 *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_80185150 *)m = *(Mat32_8018B23C_80185150 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_8019FD78;
    *(u8 *)(q + 5) = D_8019FD79;
    *(u8 *)(q + 6) = D_8019FD7A;

    p = (Rec_8018B23C_80185150 *)((s32)&D_8019FD7C + (a0 << 4));
    x = p->fA + (u16)D_8019FD70;
    y = p->fE + (u16)D_8019FD72;
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
        __asm__ __volatile__("" : "=r"(svp));
        __asm__ __volatile__("" : "=r"(outp));
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
        register u8 *spr __asm__("$29");
        ApplyMatrixSV(spr + 0x10, sv, out);
    }

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_80185150 *bp = (Bidx_8018B23C_80185150 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_80185150 *)q)->addr =
            ((PTag_8018B23C_80185150 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_80185150 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80185434;

/* func_80185434 (ov_SC03_117, ov_SC03_117_jr_8017BEBC) — MATCH (148 ins)
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
 * LEVERS (each byte-checked against asm/.../func_80185434.s)
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

typedef struct { s16 vx, vy, vz, pad; } SV_1A30_80185434;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_1A30_80185434;   /* 0x20 bytes */

void func_80185434(s16 *arg0)
{
    extern u8 D_800A6610[];
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void *func_80010A08(s32);
    extern void func_80017E8C(void *);
    extern s32 RotTransPers4(void *, void *, void *, void *,
                             s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);

    SV_1A30_80185434 v[4];        /* sp+0x28 */
    MTX_1A30_80185434 mtx;        /* sp+0x48 */
    s32 opz;             /* sp+0x68 */
    s32 flag;            /* sp+0x6C */

    u32 *ot;
    u32 *otp;
    u8 *poly;
    u8 *q;
    void *mp;
    u16 len;
    u32 otz;
    register u32 qt __asm__("$4");   /* §17 pin — kills the birthing boost AND
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



/* func_80185684 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_801856E8((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_801856E8();

void func_80185684(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_801856E8)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}



void func_801856E8(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_80185AE8(s0);
    sin_val = func_80185A2C(s0);

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



void func_80185848(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_80185AE8(r[0] & 0xFFF);
    sx = func_80185A2C(r[0] & 0xFFF);
    cy = func_80185AE8(r[1] & 0xFFF);
    sy = func_80185A2C(r[1] & 0xFFF);
    cz = func_80185AE8(r[2] & 0xFFF);
    sz = func_80185A2C(r[2] & 0xFFF);

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



/* func_80185A2C — quadrant-folded sine lookup over a 0x400-entry u16 table.
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
 * Q2's base is D_80196F84 == D_80197F84 - 0x1000: gcc folded the `- 0x800`
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


s16 func_80185A2C(u32 a0)
{

    extern u16 D_80197F84[];
    if (a0 < 0x400) {
        return D_80197F84[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_80197F84[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_80197F84[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_80197F84[0xFFF - a0];
    }
}



/* func_80185AE8 — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_80197F84); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_80197F84)[a - 0x400]  ->  base ((s16 *)D_80197F84)-0x800 = D_80197784, index a*2
 *   ((s16 *)D_80197F84)[a - 0xC00]  ->  base ((s16 *)D_80197F84)-0x1800 = D_80196784, index a*2
 * so no extra externs are needed for D_80197784 / D_80196784.
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


s32 func_80185AE8(u32 a0v)
{

    extern u16 D_80197F84[];
    if (a0v < 0x400) {
        return ((s16 *)D_80197F84)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_80197F84)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_80197F84)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_80197F84)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}



extern void (*D_801987F8[])(void);

void func_80185B94(void *a0) {
    D_801987F8[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80185C00();
extern void func_80146CA0(void *a0);

void func_80185BD0(s32 arg0) {
    func_80185C00(arg0);
    ((void (*)(s32))func_80146CA0)(arg0);
}


s32 func_80185C00(s32 a0)
{
    extern s32 D_80062C14;
    extern s32 D_80198784;
    extern s32 D_80198808;
    s32 *s0 = (s32 *)a0;
    s32 buf[4];

    func_80019064(&D_80062C14);
    func_801511E0((int)s0);
    func_80154274(s0, (s32)&D_80198784);
    func_80146E90(s0, 0x20);
    func_8001382C(*(s16 *)((s32)s0 + 0x42), (void *)&D_80198808, (void *)buf);
    func_80146DB8(s0, buf);
    func_801477E8(s0, 0xFFF00000);
    func_80149020(s0);
    func_80147324(0x451);
    func_80146CA0(s0);
}


extern void func_80146CA0(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80147460(s32 a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80147F50(s32 arg0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014C010(s32 a0, s32 a1);
extern u16 D_800B99DA;
extern s32 func_801535F4(void *arg0);

void func_80185C9C(s32 param_1) {
    s32 pad[8];

    func_80149020((s32 *)param_1);
    func_80147F50(param_1);
    func_801473EC((s32 *)param_1);
    func_80148038(param_1, 0x18000);
    func_80147460(param_1);

    if (!(D_800B99DA & 1)) {
        func_8014C010(param_1, 2);
    }

    if (func_801535F4((void *)param_1) == 4 || func_80146E98(param_1) != 0) {
        func_801477E8((s32 *)param_1, 0x40000);
        func_80146CA0((void *)param_1);
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_801535F4(void *arg0);
extern void func_80147460(s32 a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80159B3C(void *a0);
extern void func_8015BF48(s32 *a0);
extern void func_80165718(s32 a0);
extern void func_80185E48(s32 a0);

void func_80185D40(s32 param_1)
{
    s32 v1;
    s32 one;
    s32 pad[8]; 

    func_80149020((s32 *)param_1);
    func_80148038(param_1, 0x18000);
    func_80147460(param_1);

    if (*(s32 *)(param_1 + 0x234) == 0) {
        if (*(s32 *)(param_1 + 0x34) >= 0) {
            if (*(u16 *)(param_1 + 0xB8) & 0x8000) {
                *(u16 *)(param_1 + 0xB8) = *(u16 *)(param_1 + 0xBA);
            }
        }
    }

    v1 = func_801535F4((void *)param_1);
    one = 1;
    if (v1 == one) goto case1;
    if (v1 < 2) return;
    if (v1 == 2) goto case2;
    return;
case1:
    func_80185E48(param_1);
    func_80159B3C((void *)param_1);
    goto join;
case2:
    func_80185E48(param_1);
    func_8015BF48((s32 *)param_1);
join:
    func_80146A6C(2, (void *)param_1, 0, 0, 0, one, 0);
    func_80165718(param_1);
}


extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_80185E48(s32 a0)
{
    s32 s0 = a0;
    s32 v0;
    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    v0 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v0 + 0x10) = 0;
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}


extern void func_80019064(void *a0);
extern u8 D_80198818[];
extern void (*D_80198988[])(void *);
extern s16 D_8011DB0C;

void func_80185E90(s32 param_1)
{
    if (*(u16 *)((s32)param_1 + 2) < 3) {
        func_80019064(D_80198818);
    }

    D_80198988[*(u16 *)((s32)param_1 + 2)](param_1);
    D_8011DB0C = 0;
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_80185F4C(s32 a0);
extern void func_80146CA0(void *a0);
void func_80185F04(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_80185F4C(a0);
    func_80146CA0((void *)a0);
}


extern void func_80147324(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern void (*D_80198864)(void);

void func_80185F4C(s32 a0)
{
    s32 *s0 = (s32 *)a0;

    func_80147324(0x451);
    func_80154274(s0, (s32)&D_80198864);
    func_80149020(s0);
    *(u16 *)((s32)s0 + 0x244) = *(u16 *)((s32)s0 + 0x6);
    *(u16 *)((s32)s0 + 0x246) = *(u16 *)((s32)s0 + 0xA);
    *(u16 *)((s32)s0 + 0x248) = *(u16 *)((s32)s0 + 0xE);
    func_80146CA0(s0);
}


extern s16 D_8011DB1A;
extern s16 D_8011DB18;
extern s16 D_8011DB0C;
extern u16 D_8011DB0C_r __asm__("D_8011DB0C");
extern s32 func_80029D3C(void);
extern int func_80151204(int arg, int a1);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_801542A4(s32 *a0, s32 a1);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80149020(s32 *a0);
extern u8 D_801988FC[];
extern u8 D_801989A0[];

void func_80185FB0(s32 param_1) {
    s32 s0;
    s32 sp10[4];

    func_80149020((s32 *)param_1);
    if (D_8011DB0C_r == 0) {
        return;
    }
    {
        register s32 arg4 __asm__("$4");
        arg4 = D_8011DB1A;
        __asm__ __volatile__("" : "=r"(arg4) : "0"(arg4));
        s0 = func_80029D3C();
    }
    func_8014BC44(param_1, s0);
    func_80151204(param_1, s0);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0xC00;
    func_801542A4((s32 *)param_1, (s32)&D_801988FC);
    func_8001382C(D_8011DB18, (void *)&D_801989A0, (void *)sp10);
    func_80146DB8((s32 *)param_1, sp10);
    func_801477E8((s32 *)param_1, 0x100000);
    D_8011DB0C = 0;
    *(u8 *)(param_1 + 0xDE) = 3;
    func_80146E90((s32 *)param_1, 0x20);
    func_80146CA0((void *)param_1);
}


void func_80186090(s32 param_1)
{
    extern u16 D_800B99DA;
    extern void *D_80198854[];
    extern s32 D_80198934;
    s32 var_v1;

    func_80149020((s32 *)param_1);
    func_80147F50(param_1);
    func_801473EC((s32 *)param_1);
    func_80148038(param_1, 0x40000);
    func_80147460(param_1);
    if (!(D_800B99DA & 1)) {
        func_8014C010(param_1, 2);
    }
    var_v1 = func_801535F4((void *)param_1);
    switch (var_v1) {
    case 1:
        if (*(u8 *)(param_1 + 0xDE) != 0) {
            func_801863B0(param_1);
            func_80147324(0xC72);
            func_8013C9C4(D_80198854[*(u8 *)(param_1 + 0xDE)]);
            func_801542A4((s32 *)param_1, (s32)&D_80198934);
            *(s32 *)(param_1 + 0x34) = -(*(s32 *)(param_1 + 0x34) * 3 / 4);
            *(u8 *)(param_1 + 0xDE) = *(u8 *)(param_1 + 0xDE) - 1;
        } else {
            func_80146E90((s32 *)param_1, 0x10);
            func_80146CA0((void *)param_1);
            return;
        }
        break;
    case 4:
        func_801477E8((s32 *)param_1, 0xC0000);
        func_80146C98((s32 *)param_1, 5);
        return;
    default:
        break;
    }
    if (func_80146E98(param_1) != 0) {
        func_801477E8((s32 *)param_1, 0xC0000);
        func_80146C98((s32 *)param_1, 5);
    }
}


extern void func_80149020(s32 *a0);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern u16 D_800B99DA;
extern void func_8014C010(s32 a0, s32 a1);
extern s32 func_801535F4(void *arg0);
extern s32 func_80146E98(s32 a0);
extern void func_8018637C();
extern void func_80159B3C(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80165718(s32 a0);

void func_801861EC(s32 param_1) {
    func_80149020((s32 *)param_1);
    func_80147F50(param_1);
    func_801473EC((s32 *)param_1);
    if (!(D_800B99DA & 1)) {
        func_8014C010(param_1, 2);
    }
    func_801535F4((void *)param_1);
    if (func_80146E98(param_1) == 0) {
        return;
    }
    func_8018637C(param_1);
    func_80159B3C((void *)param_1);
    func_80146A6C(2, (void *)param_1, 0, 0, 0, 1, 0);
    func_80165718(param_1);
}


extern u16 D_800B99DA;

void func_80186298(s32 param_1)
{
    s32 v1;
    s32 one;

    func_80149020((s32 *)param_1);
    func_80148038(param_1, 0x40000);
    func_80147460(param_1);

    if ((D_800B99DA & 1) == 0) {
        func_8014C010(param_1, 2);
    }

    v1 = func_801535F4((void *)param_1);
    one = 1;
    if (v1 == one) goto case1;
    if (v1 < 2) return;
    if (v1 == 2) goto case2;
    return;
case1:
    func_8018637C(param_1);
    func_80159B3C((void *)param_1);
    goto join;
case2:
    func_8018637C(param_1);
    func_8015BF48((s32 *)param_1);
join:
    func_80146A6C(2, (void *)param_1, 0, 0, 0, one, 0);
    func_80165718(param_1);
}


extern s32 D_80127518;
extern void func_80151664(void);

void func_8018637C(s32 param_1) {
    D_80127518 = 0;
    *(u16 *)(((struct { s32 a, b, c, d, e, f, g, h, f20; } *)param_1)->f20 + 0x10) = 0;
    *(u8 *)(param_1 + 0xA8) = 0x20;
    func_80151664();
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_801863B0(s32 param_1) {

    extern u8 *func_8012913C(s32 a0);
    extern void func_800159E4(s32 a0, s32 a1);

    u8 *s0;
    s32 i;
    s32 v1;

    for (i = 0; i < 0x1000; i += 0x100) {
        s0 = func_8012913C(0x22);
        if (s0 != 0) {
            func_800159E4(param_1 + 4, (s32)s0 + 4);
            *(s32 *)(s0 + 0x10) = func_80047948(i) * 0x140;
            *(s32 *)(s0 + 0x18) = func_8004787C(i) * 0x140;
            *(s16 *)(s0 + 0x34) = 0x3000;
            v1 = *(s32 *)(s0 + 0x20);
            *(u16 *)(v1 + 0x2c) = 0xc002;
        }
    }
}



extern void (*D_80198BA0[])(void);

void func_80186458(void *a0) {
    D_80198BA0[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);



void func_80186494(void *a0) {

    extern s16 D_80198A2C[][2];
    extern u8 D_80198A58[];
    extern EffectSlot4_80186494 D_80198A64[];
    extern u8 D_80198A90[];
    extern EffectSlot4_80186494 D_80198AC8;
    extern EffectSlot4_80186494 D_80198AF0;
    extern EffectSlot4_80186494 D_80198AF4;
    extern EffectSlot4_80186494 D_80198B24;
    extern EffectSlot4_80186494 D_80198B28;
    extern EffectSlot4_80186494 D_80198B58;
    extern EffectSlot4_80186494 D_80198B5C;
    extern EffectSlot4_80186494 D_80198B8C;
    extern EffectSlot4_80186494 D_80198B90;
    register void *s0 __asm__("$16");
    register void *s1 __asm__("$17");

    s0 = a0;
    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)s0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)s0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_80198A90, D_80198A2C[idx][0], D_80198A2C[idx][1]);
        uVar1 = D_80198A58[*(s32 *)((s32)s0 + 0x2C)];
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
           neighbouring symbol (idiom 7): `&D_80198B8C + 4 == &D_80198B90`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)s0 + 0x2C) > 0)
        *(EffectSlot4_80186494 *)((s32)&D_80198B8C + 4) = D_80198A64[*(s32 *)((s32)s0 + 0x2C)];
        if (COND) { D_80198B8C = D_80198B90; } else { D_80198B8C = D_80198B90; }
        if (COND) { D_80198B5C = D_80198B8C; } else { D_80198B5C = D_80198B8C; }
        if (COND) { D_80198B58 = D_80198B5C; } else { D_80198B58 = D_80198B5C; }
        if (COND) { D_80198B28 = D_80198B58; } else { D_80198B28 = D_80198B58; }
        if (COND) { D_80198B24 = D_80198B28; } else { D_80198B24 = D_80198B28; }
        if (COND) { D_80198AF4 = D_80198B24; } else { D_80198AF4 = D_80198B24; }
#undef COND
        D_80198AF0 = D_80198AF4;
        D_80198AC8 = D_80198AF0;

        *(s16 *)((s32)s0 + 0x2) = *(s16 *)((s32)s0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(s0);
    }
}


extern s32 func_801866D4(void);
    void func_80186694(void) {
        func_801866D4();
    }


extern void func_80146C3C(void);
    void func_801866B4(void) {
        func_80146C3C();
    }



extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);

void aF801866D4(void) __asm__("func_801866D4");
void aF801866D4(void)
{

    extern u8 D_80198AA8[];
    extern u8 D_80198AD0[];
    u8 *p;
    s32 i;

    func_80017254(D_80198AA8);
    i = 0;
    p = D_80198AD0;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}




extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    void func_8018672C(void *arg0) {
        ((void (*)(s32, s32, s32, s32))func_80146994)(0x28, 0, arg0, 0);
    }



extern s32 func_8014C050(s32 a0, s32 a1);

void func_80186758(void) {

    extern s32 D_80126B58;
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}





