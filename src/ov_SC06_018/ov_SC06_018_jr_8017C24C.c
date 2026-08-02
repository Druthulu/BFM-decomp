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
extern u8 D_80195B0C;
extern u8 D_80195A7C;
extern u8 D_80195A58;
extern u8 D_80195A34;
extern u8 D_80195AE8;
extern u8 D_80195AC4;
extern u8 D_80195AA0;
extern u8 D_80195A10;
extern void func_80145934(void);
extern u8 D_80195B9C;
extern u8 D_80195B78;
extern u8 D_80195B54;
extern u8 D_80195B30;
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
extern unsigned char D_80194F94[];
extern unsigned char D_80194FC4[];
extern unsigned char D_80195014[];
extern unsigned char D_80195044[];
extern unsigned char D_80195074[];
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
extern void (*D_801950C4[])(void *);
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
extern s32 D_8019518C[];
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
extern u8 D_80195214[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8019521C;
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
extern int D_801D3D70;
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
extern s32 D_801D3D74;
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
extern s32 D_8019524C;
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
extern void (*D_801952F4[])(void);
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
extern void (*D_80195318[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80195308;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019532C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80195338[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80195348[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80195360[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80195350;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80195374[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80195390[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80195380;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801953A4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801953B8[])(void);
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
extern s32 D_801953CC;
extern void (*D_801953F4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801953D4;
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
extern int (*D_80195440[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80195444[])(void);
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
extern unsigned short D_801958A8[];
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
extern void (*D_801958B8[])(void);
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
extern int D_801D3DA8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801958E0[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801958C0;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801958D0;
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
extern void (*D_80195920[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80195928[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801958F4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80195934[])(void);
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
extern u8 D_80195904;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D3DB0;
extern s32 D_801D3DBC;
extern s32 D_801D3DC0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80195970[])(s32 *);
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
extern s32 D_80195944[];
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
extern s32 D_801D3DB8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80195BC0[])(void);
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
extern char D_801959E0[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80195C64[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80195DB8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80195BD4;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80195DC0[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80195BE4;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80195C04;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80195DC8[])(void);
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
extern void (*D_80195DF0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80195DFC[])(void);
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
extern void (*D_80195C70[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80195EA0;
extern void func_8015D380(s32 a0);
extern unsigned char D_80194F84[];
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
extern unsigned char D_80195EB4[];
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
extern s8 D_80195EF0[];
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
extern u16 D_80195F38;
extern u16 D_80195F3A;
extern u16 D_80195F3C;
extern s32 D_80195F40;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80195F48;
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
extern int D_80195C54;
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
extern unsigned int D_80195FCC[];
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
extern void (*D_8019607C[])(void);
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
extern u16 D_801960AC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80196110;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D3DC8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80196134[])(void);
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
extern int D_801D3E20[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8019617C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8019616C;
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
extern char D_801D34A0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80196184[])(void);
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
extern void (*D_801961D8[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801961A0;
extern s16 D_801961D4;
extern s16 D_801961D2;
extern s16 D_801961D0;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801961E4[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D3E80;
extern u8 D_801D3E81;
extern u8 D_801D3E82;
extern u8 D_801D3E83;
extern u8 D_801D3E84;
extern u8 D_801D3E85;
extern u8 D_801D3E86;
extern u8 D_801D3E87;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801961F4[])(void);
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
extern s32 D_801D3EC0;
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
extern void (*D_80196238[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801962B4[];
extern s32 D_801962D4[];
extern u8 D_80196350[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80196370[];
extern u8 D_80196390[];
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
extern void (*D_8019642C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801964A8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D34B0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801964B4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801964BC[])(void);
extern void func_801663FC(void *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_80196584[])(void);
extern void func_80166618(void *a0);
extern void (*D_80196594[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801965A4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801965B0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80196510[];
extern u8   D_80196524[];
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
extern void (*D_801965C8[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801965D0[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801965D8[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801965E0[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801965E8[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801965F0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801965F8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801966AC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801966B4[])(void);
extern void func_80169F00(void *a0);
extern char D_80196664[];
extern char D_80196624[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801966EC[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801966F8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80196740[])(void);
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
extern void (*D_801967BC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D41E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801967B0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801967F4[];
extern unsigned short D_801967FC[];
extern unsigned short D_80196804[];
extern unsigned char D_801D41E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D41E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019680C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D431C;
extern M2C_UNK D_801D4320;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D42A8;
extern void (*D_8019683C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D4324[];
extern u8 D_801D432C[];
extern u8 D_801D42DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80196844[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80196860[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80196868[])(void);
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
extern void (*D_801968D0[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80196874;
extern u8 D_80196880;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80196904[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019690C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80196960[])(void);
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
extern u16 D_80196994[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80196984[];
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
extern s32 D_801969B0;
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
extern void (*D_80196A28[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80196A30[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80196A38[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80196A40[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80196A48[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80196A50[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80196A5C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80196A68[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80196A74[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80196A84[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80196A94[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80196A9C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80196AA4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80196AAC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80196AB4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80196ABC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80196AC4[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80196ACC[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80196AD4[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80196ADC[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80196AE4[])(void);
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
extern void (*D_80196AEC[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80196AF4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80196AFC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80196B04[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80196B0C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80196B14[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80196B1C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80196B24[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80196B2C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80196B34[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80196B3C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80196B44[])(void);
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
extern void (*D_80196B88[])(void);
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
extern M2C_UNK D_80196B4C;
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
extern void (*D_80196BB8[])(void);
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
extern void (*D_80196BF4[])(void);
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
extern s32 func_801749C8(s32);
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80196C4C[])();
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
extern void (*D_80196C5C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80196C64[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80196DCC[])();
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
extern void (*D_80196DD8[])();
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
extern M2C_UNK D_801D36F8;
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
extern s16 D_801D5B28;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D4A60;
extern short D_801D5B9C;
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
extern s32 D_801D4E8C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D4EB4;
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
extern s16 D_801D4E70;
extern s32 func_8017A3B0(void);
extern short D_801D4EAC;
extern short D_801D4EA8;
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
extern s16 D_801D4E74;
extern u16 D_801D4EF4;
extern u16 D_801D4EF6;
extern u16 D_801D4EF8;
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
extern s16 D_801D4EEC;
extern s16 D_801D4EEE;
extern s16 D_801D4EF0;
extern s16 D_801D4EE4;
extern s16 D_801D4EE6;
extern s16 D_801D4EE8;
extern void func_8017B7A8(void);
extern s16 D_801D4F04;
extern s16 D_801D4F06;
extern s16 D_801D4F08;
extern s16 D_801D4F0C;
extern s16 D_801D4F0E;
extern s16 D_801D4F10;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D4EFC;
extern short D_801D4EFE;
extern short D_801D4F00;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D4E94;
extern SV4 D_801D4E9C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D4EBC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D4EB8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80196FB4[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80196FCC[])(void);
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



extern void (*D_80197048[])(void);

void func_8017D14C(void *a0) {
    D_80197048[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D3B8(void);
extern void func_800167B8(s32 a0);

s32 func_8017D188(s32 a0) {
    func_8017D3B8();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D1CC(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_80197050[])(void);

void func_8017D1F0(void *a0) {
    D_80197050[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D3E0(void);

s32 func_8017D22C(s32 a0) {
    func_8017D3E0();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D26C(u8 *a0) {
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
    void func_8017D2E8(void) {
        func_800D1EBC();
    }



extern void (*D_8019705C[])(void);

void func_8017D308(void *a0) {
    D_8019705C[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D344);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D3B8(void) {

    extern s32 D_80197068(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80197068, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8019706C;

void func_8017D3E0(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8019706C, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D408);


extern void (*D_80197080[])(void);

void func_8017D4A0(void *a0) {
    D_80197080[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D4DC);

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

void func_8017D648(s32 param_1, s16 *param_2) {
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D7E0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D874);


extern void (*D_80197088[])(void);

void func_8017D8F8(void *a0) {
    D_80197088[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D934);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017D9A4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DB20);

extern s32 func_8017DC58(void);

s32 func_8017DC58(void) {
    return 0x7E;
}



extern void func_8012DFD4(void *a0);

void func_8017DC60(void *a0) {

    extern void (*D_80197108[])(void);
    D_80197108[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_8012DFD4(a0);
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DCC0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DD88);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DE08);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DE64);

DEFINE_func_8017DEA4()  /* dedup: shared engine-core @0x8017DEA4 (src/shared) */


extern void func_80019064(void *a0);

void func_8017DEAC(void *a0) {

    extern u8 D_80197118;
    extern void (*D_80197140[])(void *);
    func_80019064(&D_80197118);
    D_80197140[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DF04);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DF54);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017DFD8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E134);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E188);



s32 func_8017E1AC(void)
{

    extern u8 D_801D4F18[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801D4F18;
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



extern void (*D_8019714C[])(void);

void func_8017E1F0(void *a0) {
    D_8019714C[*(u16 *)((s32)a0 + 0x2)]();
}


// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801D4F2C + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017E420(void*);
extern void func_8017E3F0(int);
extern int rand(void);
extern unsigned char D_801D4F2C[];

void func_8017E22C(int param_1)
{
    register int iVar3 __asm__("$16");
    register int iVar3b __asm__("$19");
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801D4F2C + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    *(int *)(param_1 + 0x20) = iVar3;
    iVar3b = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8017E420)(iVar5);
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
        func_8017E3F0(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E378);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E3F0);


void func_8017E420(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E434);


extern void (*D_80197184[])(void);

void func_8017E49C(void *a0) {
    D_80197184[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E4D8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017E524);

void func_8017E56C(void) {
}

// @class: regalloc-order
// @stuck: none — MATCH (89 ins). Blk8(align1) struct copies + array indexing (IV-base regalloc)
#include "common.h"



extern u32 *D_8019717C[];
extern Blk8 D_80197198[];
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8017E6D8();

void func_8017E574(s32 param_1) {
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_8019717C[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_80197198[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8017E6D8(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
        }
    }
}


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

extern SVECTOR_8017E6D8 D_801D542C[4];
extern struct PW8017E6D8 D_801D544C;
extern struct PW8017E6D8 D_801D5450;
extern u8 D_801D5454, D_801D5455, D_801D5456, D_801D5458, D_801D5459, D_801D545A;
extern int D_801D545C;

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

void func_8017E6D8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801D542C[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801D545C = 0x50000000;
        D_801D5454 = 0;
        D_801D5455 = 0;
        D_801D5456 = 0;
        D_801D5458 = 0;
        D_801D5459 = 0;
        D_801D545A = 0;
    }
    D_801D544C = h[0];
    D_801D5450 = h[1];

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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017EA54);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017EB8C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017ED60);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017EF0C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017F0F4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017F430);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017F6D8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017F808);


extern void (*D_801AAF88[])(void);

void func_8017F8E0(void *a0) {
    D_801AAF88[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017F91C);


extern void (*D_801AAFA8[])(void);

void func_8017FA90(void *a0) {
    D_801AAFA8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FACC);


extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8017EB8C(s32);

void func_8017FB54(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8017EB8C)(a0);
}




extern void func_8017ED60(void);
    void func_8017FB8C(s32 *param) {
        *(s16 *)(*(s32 *)((char *)param + 0x20) + 0x10) = 0xE00;
        func_8017ED60();
    }




extern void func_8017ED60(void);
    void func_8017FBB4(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x10) += 0x20;
        ((void (*)(void))func_8017ED60)();
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FBE8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FC34);

extern void func_8017EB8C(s32 arg0);
    void func_8017FD20(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x10) >> 1;
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0x18) >> 1;
        ((void (*)(s32 *))func_8017EB8C)(a0);
    }


extern void func_8017EB8C(s32 arg0);
    void func_8017FD54(u8 *param_1) {
        param_1[0xC1] = 0xC;
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        ((void (*)(void))func_8017EB8C)();
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FD80);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FE0C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8017FF34);


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80180068);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801800C8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80180188);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018025C);

extern s32 D_801D55A0;
extern s32 func_8012C588(s32 a0, s32 a1);

void func_80180354(s32 a0, s32 a1) {
    D_801D55A0 = a1;
    ((void (*)(s32, s32))func_8012C588)(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801D55A0;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_80180384(s32 param_1) {

    extern M2C_UNK D_80193900;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801ACD24;
    extern char * D_801ACD58;
    extern char D_801D5580[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801ACD24) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80193900));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801D55A0, &s60);
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
        tmp = D_801ACD58;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801ACD58 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801D5580 < puVar4) {
        D_801ACD58 = D_801D5580 - 0x120;
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
            tmp = D_801ACD58;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801ACD58 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801D5580 < puVar4) {
            D_801ACD58 = D_801D5580 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
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

s32 func_801805C8(s32 param_1) {

    extern signed char D_801ACD10[];
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
        p = D_801ACD10;
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
            p = D_801ACD10;
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
        func_8012C218((void *)self);
    }
}



extern void (*D_801ACD5C[])(void);

void func_80180868(void *a0) {
    D_801ACD5C[*(u16 *)((s32)a0 + 0x2)]();
}


// @class: schedule
// @stuck: none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_801808A4(int param_1, short param_2)
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80180AB4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80180EB8);

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

extern u8 D_801AD470[];
extern u8 D_801AD3B4[];
extern u8 D_801AD374[];
extern u8 D_801AD3BC[];
extern u8 D_801AD394[];
extern u8 D_801B16DC[];
extern u8 D_801B498C[];
extern u8 D_801AD4B0[];
extern u8 D_801B47F4[];
extern u8 D_801B487C[];
extern u8 D_801B4904[];

void func_8018102C(int param_1) {
    int iVar1;

    iVar1 = func_8012C354(param_1, D_801AD470);
    if (iVar1 != 0) {
        if (*(short *)(param_1 + 0x70) != 0) {
            func_800599B8(D_801AD3B4, D_801AD374);
            func_800599B8(D_801AD3BC, D_801AD394);
            func_8001C214(*(int *)(param_1 + 0x20), D_801B16DC);
        }
        *(u8 *)(param_1 + 0xc0) = 1;
        *(int *)(param_1 + 0xb4) = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        *(short *)(param_1 + 0xae) = 0x2100;
        func_8012A828(param_1, D_801B498C);
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
    *(u32 *)(param_1 + 0xbc) = (u32)D_801AD4B0;
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
        *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x18) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = 0x2400;
    *(u16 *)(param_1 + 2) = 8;
    func_8012A828(param_1, D_801B47F4);
    func_8012A828(*(int *)(param_1 + 0xcc), D_801B487C);
    func_8012A828(*(int *)(param_1 + 0xd0), D_801B4904);
    return;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801811DC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80181468);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018192C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80181AFC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80181CEC);

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
extern unsigned char D_801AD450[];

void func_80182004(int param_1)
{
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
                func_80019064(D_801AD450);
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801821FC);

// @class: struct
// @stuck: none — MATCH

extern int rand(void);
extern int func_80143C74(short *, int);
extern int func_80047948(int);
extern int func_8004787C(int);
extern void (*D_801AD568[])(short *);

void func_80182644(short *param_1)
{
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
    D_801AD568[*(unsigned short *)(param_1 + 1)](param_1);
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80182854);

// @class: other
// @stuck: none — MATCH (132 ins). Blocker was gcc reassociating `mem - 0x20 + masked`
//   into `mem + (masked - 0x20)` and CSE-hoisting the shared -0x20 (as 0xffe0/ori) into the
//   freed s0, which then filled the jal func_8004787C delay slot. Fix: split `mem - 0x20`
//   into its own temp so addiu -0x20 stays on the memory operand at each of the two sites.

#include "common.h"

extern s32 rand(void);
extern void (*D_801AD5E0[])(s32);
extern s32 func_80143C74();
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80182C98(s32 a0) {
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

    D_801AD5E0[*(u16 *)(a0 + 2)](a0);

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

extern u8  D_801AD3C4;
extern u8  D_801AD3D0;
extern u16 D_80126B96;
extern u16 D_801270C0;

void func_80182EA8(s32 arg0) {
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (*(u16 *)(arg0 + 2) == 0) {
        *(u8 **)(*(s32 *)(arg0 + 0x20) + 0x20) = &D_801AD3C4;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x50000000;
        *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x59;
        func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)&D_801AD3D0);
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018312C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018314C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018324C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801832EC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801833AC);



















void func_80183444(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183464);

void func_80183554(void) {
}

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018355C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183630);

extern void func_8012B370(int);
void func_801836F0(void) {
    ((void (*)(void))func_8012B370)();
}




















void func_80183710(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183730);

void func_80183824(void) {
}

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018382C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183920);

extern void func_8012B370(int a0);
    void func_801839E0(void) {
        ((s32 (*)(void))func_8012B370)();
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183A00);

// @class: struct
// @stuck: none — MATCH (135/135 ins, match_one confirmed)

extern Elem52_801B5094 D_801B5094[];
extern u8 D_801B522C[];
extern u8 D_801B51B4[];
extern u8 D_801CC180[];
extern u16 D_801CC674;
extern u16 D_801CC4CC;

extern s32 func_8012C354(s32 a0, void *a1);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012CAE4(s32 a0);
extern void func_8012B030(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_80183A70(s32 param_1) {
    s32 iVar1;
    u16 uVar2;

    iVar1 = func_8012C354(param_1, &D_801B5094[*(u16 *)(param_1 + 0x70) & 0xf]);
    if (iVar1 != 0) {
        *(u8 *)(param_1 + 0xc0) = 1;
        *(u8 **)(param_1 + 0xbc) = D_801B522C;
        *(s32 *)(param_1 + 0xb4) = -0x8ad;
        *(u32 *)(param_1 + 0xc4) |= 2;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x80;
        *(u8 **)(*(s32 *)(param_1 + 0x20) + 0x80) = D_801B51B4;
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
                func_8012A828(param_1, &D_801CC180);
            }
            break;
        }
        case 1:
            *(s16 *)(param_1 + 2) = 0x13;
            D_801CC674 = 0x28;
            if (((s32)*(s16 *)(param_1 + 0x70) & 0x8000) != 0) {
                *(u32 *)(param_1 + 0xe0) |= 0x400;
            }
            break;
        case 2:
            *(s16 *)(param_1 + 2) = 0x18;
            D_801CC4CC = 0x28;
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183C8C);

#include "common.h"

/* func_80183CDC — a randomised state entry: seed the timer at 0x1C with
 * rand()%64 + 0x80, park 18000 at 0x48, then nudge the value at 0xE8 by a
 * random 0..1023 in a random direction, push the command list D_801CCCA0,
 * set the state word at 0x02 to 3 and clear bit 6 of the flags at 0xE0.
 *
 * §71 sibling-first: func_8018598C (same TU, MATCHed) is the same
 * `if ((rand() & 1) == 0) v = base - off; else v = base + off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801CCCA0[];

void func_80183CDC(s32 param_1) {
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

    func_8012A828(param_1, D_801CCCA0);
    *(s16 *)(param_1 + 2) = 3;
    *(u32 *)(param_1 + 0xE0) &= 0xFFFFFFBF;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183DA4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183F10);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80183F50);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801840D8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018410C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184194);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801841E0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018431C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184370);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801844C0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184500);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018457C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801847FC);

#include "common.h"

extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern void func_80142414(s32 a0, s16 a1);

void func_80184844(s32 p) {
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184904);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184944);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184AA8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184AFC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184C0C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80184C74);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801850F4);

#include "common.h"

/* func_80185268 — randomised state entry (state word 0x19):
 * set the state at 0x02, push command list D_801CC7A0, seed the timer at
 * 0x1C with rand()%64 + 0x80, nudge the value at 0xE8 by a random 0..1023
 * in a random direction, then park 18000 at 0x48.
 *
 * §71 sibling-first: func_80183CDC / func_8018598C (same TU, MATCHed) are the
 * same `if ((rand() & 1) != 0) v = base + off; else v = base - off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801CC7A0[];

void func_80185268(s32 param_1) {
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    *(s16 *)(param_1 + 2) = 0x19;
    func_8012A828(param_1, D_801CC7A0);

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


#include "common.h"

extern u8 D_801B5164[];

extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_80189284(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */

void func_80185320(s32 p) {
    s32 buf10[2];
    s32 r_b608;

    r_b608 = func_8012B608((s32)*(s16 *)(*(s32 *)(p + 0x20) + 0x12),
                           *(s32 *)(p + 0xE8), 0x10);
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r_b608;
    func_8012B178(p, 0xFFFBD000);

    *(u32 *)(p + 0xE0) &= 0xFFFFFFBF;
    if (func_8018765C(p) == 0) {
        func_801877E4(p);
    }

    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf10);
    if (func_80189284(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0 &&
        func_8012BCCC(p) < 0x64000) {
        *(u16 *)(p + 2) = 0x1C;
    } else if (func_8012BEE8(p) != 0) {
        *(u16 *)(p + 2) = 0x1A;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185400);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185440);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801854C0);

// @class: schedule
// @stuck: none — MATCH (181 ins, relocation-masked)








extern s32 func_8012BEE8();
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_80189380(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_80189E60(s32 a0, s32 a1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80189284(void *a0, s32 a1, s32 a2);
extern s32 rand(void);

extern u8 D_801CC3D0[];
extern u8 D_801CC358[];
extern u8 D_801B517C[];
extern u8 D_801B518C[];
extern u8 D_801B5164[];

void func_801854F8(s32 p) {
    s32 buf58[8];   /* auStack_58  sp+0x18 (0x20) */
    s32 g38[4];     /* uStack_38/34, iStack_30 sp+0x38 (0x10) */
    u16 g28[4];     /* uStack_28/26/24 sp+0x48 (0x08) */
    u16 out[4];     /* func_80189380 output sp+0x50 (0x08) */
    s32 buf18[2];   /* auStack_18  sp+0x58 (0x08) */
    s32 i;
    s32 e;

    if (*(u16 *)(p + 0x34) == 0) {
        if (func_8012BEE8() == 0) return;
        func_8012A828(p, D_801CC3D0);
        *(u16 *)(p + 0x34) += 1;
    }
    if (*(s32 *)(p + 0x94) < 0xe) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B8E4(p, 8);
    }
    if (*(s32 *)(p + 0x94) == 0xe) {
        func_80189380(p, D_801B517C, out, 0xb);
        func_8018931C(p, out, 0x282, 0, 0, 0);
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
                func_80189380(p, D_801B518C + i * 8, out, 0xb);
                *(u16 *)(e + 6) = out[0];
                *(u16 *)(e + 0xa) = out[1];
                *(u16 *)(e + 0xe) = out[2];
            }
            i++;
        } while (i < 5);
        func_80189E60(p, 0x8be);
    }
    if (*(u16 *)(p + 0x72) & 0x4000) {
        ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf18);
        if (0x63fff < func_8012BCCC(p) ||
            func_80189284(buf18, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) == 0) {
            *(u16 *)(p + 2) = 0x1b;
            func_8012A828(p, D_801CC358);
            *(s32 *)(p + 0x1c) = 0x20;
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801857CC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185944);

// @class: regalloc-order
// @stuck: none — MATCH (168/168). $s4/$s5 pins for base+&local28; s32 sVar1 for single lh;
//          inverted if for bnez; sp20[3] array so 3 stores survive DSE; fresh-pseudo c=coord in
//          the else so gcc keeps s2v as the commutative addu's first operand (§10 A1 via pseudo order).

#include "common.h"

typedef struct {
    u8  pad0[6];
    u16 f6;         /* 0x06 -> D_80126B5E */
    u8  pad8[2];
    u16 fa;         /* 0x0A -> D_80126B62 */
    u8  padc[2];
    u16 fe;         /* 0x0E -> D_80126B66 */
} StructB58;

extern s32 D_80126B58;
/* holds a pointer value */
extern u16       D_800B99DA;
extern u8        D_801B5184;

extern int  rand(void);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern void func_8012F14C(s32 a0);
extern void func_80189380(s32, void*, void*, s32);
extern void func_8018931C(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);

void func_8018598C(s32 param_1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    u8  auStack_38[8];
    s16 sp20[3];
    u8  auStack_28[8];
    register StructB58 *b58 __asm__("$20") = &(*(StructB58 *)&D_80126B58);   /* $s4 */
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
    if (func_8018765C(param_1) == 0) {
        func_801877E4(param_1);
        sp20[1] = 0;
        sp20[0] = 0;
        sp20[2] = -0x100;
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34,
                                                 (s32)sp20, (s32)psVar7);
    }

    if (((u32)D_800B99DA % 0x28 == 0) && ((*(u32 *)(param_1 + 0xe0) & 0x80) == 0)) {
        ((void (*)(s32, s32, s32, s32))func_80189380)(param_1, (s32)&D_801B5184, (s32)auStack_38, 0xb);
        ((void (*)(s32, s32, s32, s32, s32, s32))func_8018931C)(param_1, (s32)auStack_38, 0x282, 1, 0, 0);
        *(u32 *)(param_1 + 0xe0) |= 0x80;
    }

    if (func_80013478(param_1 + 4, (s32)psVar7) < 0x400) {
        *(s32 *)(param_1 + 0x1c) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185C2C);

extern void func_80187038(void);
    void func_80185DA8(s32 arg0) {
        if (*(s16 *)((s32)arg0 + 0x98) == 0) {
            ((void (*)(void))func_80187038)();
        }
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185DD8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80185F58);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186270);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801866D4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186738);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186784);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186800);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186850);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186894);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801868DC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186928);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186994);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186D80);

extern void func_80189E60(s32 arg0, s32 arg1);
    void func_80186ED4(s32 arg0) {
        func_80189E60(arg0, 0x9B7);
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80186EF4);

#include "common.h"

extern void func_80187038(void);
extern void func_801874E4(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801CD170;

void func_80186F78(s32 param_1) {
    u16 uVar1;
    s32 iVar2;

    *(s16 *)(param_1 + 0x34) = 0;
    if ((*(u32 *)(param_1 + 0xe0) & 8) == 0) {
        func_80187038();
    } else {
        if ((*(u32 *)(param_1 + 0xe0) & 0x20) != 0) {
            func_801874E4(param_1, -0x8000);
        }
        *(s16 *)(param_1 + 2) = 0x22;
        func_8012A828(param_1, &D_801CD170);
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187038);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187130);

#include "common.h"

extern s32 D_80126B9C;
extern u8 D_801B5164[];

extern s32 func_8012BCCC(s32 a0);
extern s32 func_801893CC(s32 a0, s32 a1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_80189284(void *a0, s32 a1, s32 a2);

/* Two load-bearing constructs (do NOT "clean up"):
 *  1. `goto ret0` / `goto store` with `ret0:` placed BEFORE the store block — cookbook L1344
 *     shared-ret0 goto. A trailing `return 0` makes gcc sink the merged ret0 tail past the
 *     store block (7 mismatches: BRANCH-POLARITY + swapped tail).
 *  2. `register s32 r __asm__("$2")` on the func_801893CC result + `return r`. Plain
 *     `return 0;` there emits `set v0,0; j epi`, which cross_jump (§5a) merges into the
 *     ret0 block, so the branch lands on ret0 instead of the epilogue. Pinning r to $v0
 *     makes `return r` a self-copy that dies before jump2, leaving a bare `j epi` that
 *     jump.c collapses into `beqz $v0, .L8018730C`. (A plain `s32 r` does NOT work — cse2
 *     const-folds `r` to 0 on the fall-through edge and the merge comes back.) */
s32 func_80187250(s32 p) {
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
    r = func_801893CC(p, 0x380);
    if (r == 0) {
        return r;
    }
    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf10);
    if (func_80189284(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0) {
        goto store;
    }
ret0:
    return 0;
store:
    *(u16 *)(p + 2) = 0xC;
    return 1;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187320);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801874E4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018765C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801876BC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801877E4);

#include "common.h"

/* func_80187844 — line-of-sight / collision probe.
 *
 * Rotate the direction SVECTOR D_801B53B4[dir] through the entity's matrix
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
extern s16 D_801B53B4[][4];
extern s32 D_801D55A8;

s32 func_80187844(s32 a0, s32 a1) {
    s32 s0 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR — ApplyMatrixSV out */
    s16 v18[4];   /* sp+0x18 SVECTOR — segment start */
    s16 v20[4];   /* sp+0x20 SVECTOR — segment end */
    s32 r;

    ApplyMatrixSV((void *)(*(s32 *)(s0 + 0x20) + 0x34), D_801B53B4[a1], v10);
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
    D_801D55A8 = func_800132BC(v18, v20);
    return r != 0x2000;
}



extern void (*D_801B53F4[])(void);

void func_80187924(void *a0) {
    D_801B53F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187960);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187AEC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80187DD0);


extern void (*D_801B554C[])(void);

void func_80188088(void *a0) {
    D_801B554C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801880C4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188234);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018829C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801884F4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188554);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018868C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801886B0);

#include "common.h"

extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8012B260(u8 *a0);

void func_80188B00(s32 p) {
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188B9C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188D54);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188D90);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80188E10);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189000);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189284);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018931C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189380);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801893CC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018944C);


extern void (*D_801B5580[])(void);

void func_801894B4(void *a0) {
    D_801B5580[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_801894F0);

#include "common.h"

extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);   /* TU-canonical (ov_SC06_018_jr_8017C24C L5455) */
extern void func_80017274(s32 a0, s32 a1);

void func_80189954(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0x100);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x102);

    if (func_8012CBF4(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}



extern void (*D_801B55A0[])(void);

void func_801899F8(void *a0) {
    D_801B55A0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189A34);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189C28);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189D64);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_80189E60);


extern void (*D_801B55AC[])(void);

void func_80189FCC(void *a0) {
    D_801B55AC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018A008(s32 param_1) {
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


#include "common.h"

extern void func_8012931C(s32 a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_801292C8(s32 a0);

void func_8018A0B8(s32 param_1) {
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
        func_801292C8(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A170);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A28C);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018A474(void *arg0) {
        *(s16 *)((char *)arg0 + 0x108) = 0;
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 2);
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A498);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A5D8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A61C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A688);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A7C8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A86C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018A974);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AB00);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AB74);


void func_8018ABD4(s32 target, u16 *cur, s32 step)
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


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AC58);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018ACD4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AD74);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AE64);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018AF88);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B060);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B1D8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B330);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B4D8);


extern void (*D_801CD4B0[])(void);

void func_8018B65C(void *a0) {
    D_801CD4B0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B698);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B714);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B774);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B8B0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B8F8);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018B998(void *a0) {
        func_8002D4C8(0xAE5, 0);
        ((void (*)(void *, int))func_8012AD44)(a0, 0x3);
    }


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018B9D4);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018BB18);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018BBB8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018BC40);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018BCC4);


extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */

/* The 4-byte destination is a PACKED PAIR of angles held entirely in ONE saved register
 * ($s4) across all three calls — that is what produces the target's
 *   andi $s4,$s4,0xFFFF   (read of the still-uninitialized local, hoisted into the prologue)
 *   ... or  $s4,$s4,ang<<16      -> t.hi = yaw
 *   ... and $s4,$s4,0xFFFF0000 / or $s4,$s4,ang&0xFFFF  -> t.lo = pitch
 * A `struct { s16 lo, hi; }` has align 2 -> BLKmode-ish handling: gcc spills it to the stack
 * and stores it with lwl/lwr + swl/swr (54 ins, 53 mismatched). Two 16-bit BITFIELDS in a
 * u32 container give the SImode, align-4 struct gcc keeps in a register. */
typedef struct {
    u32 lo : 16;
    u32 hi : 16;
} Ang2_8012B77C_8018BFA8;

/* a0 = destination packed-angle word, a1 = "from" entity, a2 = "to" entity.
 * Both entities carry 16.16 fixed-point x/y/z at +0/+4/+8; the s16 reads at +2/+6/+0x4 are
 * the integer halves. Returns the destination pointer — the return value is REAL: without it
 * gcc stores with `sw $s4,0($s3)` (57 ins) instead of the target's
 *   addu $v0,$s3,$zero ; sw $s4,0($v0)   (the return-value copy that the store's base coalesces onto).
 * The flattened `dz` reuse at the end is also load-bearing: making the (dz*sin + dx*cos)>>12
 * temp its OWN variable gives it $a1 for the whole chain; reusing `dz` extends that allocno so
 * it lands in $s5 exactly as the target does (`sra $s5,$v0,12` / `negu $a1,$s5`), and it also
 * demotes dz's priority so the saved-reg order comes out $s3=out, $s4=t, $s5=dz. */
s32 func_8018BFA8(s32 out, s32 from, s32 to) {
    Ang2_8012B77C_8018BFA8 t;
    s32 dx, dy, dz;
    s32 ang;
    s32 r1, r2;

    dz = *(s16 *)(to + 0x4) - *(s16 *)(from + 0x4);
    dx = *(s16 *)(to + 0x0) - *(s16 *)(from + 0x0);
    dy = *(s16 *)(to + 0x2) - *(s16 *)(from + 0x2);

    ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;
    t.hi = ang;

    r1 = func_80047948(ang);
    r2 = func_8004787C(ang);
    dz = (dz * r1 + dx * r2) >> 12;
    t.lo = ratan2(dy, -dz);

    *(Ang2_8012B77C_8018BFA8 *)out = t;
    return out;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C090);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C190);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C310);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C334);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C3F8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C7A8);

void func_8018C884(void) {
}

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C88C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018C9B0);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CA44);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CABC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CB14);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CB88);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CC88);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018CD04);

// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_8018D364(short *pos, int a1, int a2);

void func_8018D1A4(unsigned short *param_1, short *param_2, short *param_3,
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
        p = func_8018D364(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D330);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D364);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D40C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D514);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D654);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018D870);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018DE60);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018DFF4);

// @class: regalloc-order
// @stuck: none — MATCH (277 ins). p pinned $s1; e/spawn-ptr coalesce $s0; counter $s2; const2 hoisted $s3.
//   Key lever: dec-block written as AND form `if (q!=0 && p60!=0){compute}else{dec=p60}` (compute as
//   fall-through) — the OR/De-Morgan form inverted the 2nd branch (bnez v1) and drifted +1 ins.

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012B23C(void *);
extern void func_8012B1B4(void *, void *);
extern void func_8012A828(s32, void*);
extern void func_8012C218(void *);
extern u8 D_801D1210;
extern u8 D_801D1200;
extern u8 D_801D11DC;

void func_8018E188(void *arg) {
    register u8 *p __asm__("$17");   /* $s1 */
    s32 e;
    s32 i;
    s32 iv;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        if (-1000 < *(s16 *)(p + 0x76)) {
            func_8002D4C8(0xAE0, 0);
        }
        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        iv = *(s32 *)(p + 0xCC);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD0);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD4);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        *(s32 *)(*(s32 *)(p + 0x64) + 0xCC) = 0;
        func_8012C218(p);
    } else {
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018E5DC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018E9BC);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018EDB8);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018F060);

// @class: other
// @stuck: none — MATCH (478 ins, relocation-masked byte-identical)

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
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


void func_8018F694(void)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void *func_80010A08(s32);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blip_8018F694 D_801D57F0[];

    UVEC_8018F694 sxy;
    UVEC_8018F694 p0;
    UVEC_8018F694 p1;
    long flag;
    long otz;
    s32 i;
    PTag_8018F694 *ot;
    PTag_8018F694 *otp;
    Blip_8018F694 *bp;
    s32 t, c, d, z, x, n;

    ot = (PTag_8018F694 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    bp = D_801D57F0;

#define EMIT_8018F694() { \
    LineF2_8018F694 *pk = (LineF2_8018F694 *)func_80010A08(0x10); \
    pk->len = 3; \
    pk->code = 0x42; \
    pk->r0 = bp->r; \
    pk->g0 = bp->g; \
    pk->b0 = bp->b; \
    pk->x0 = p0.vx; \
    pk->y0 = p0.vy; \
    pk->x1 = p1.vx; \
    pk->y1 = p1.vy; \
    pk->addr = otp->addr; \
    otp->addr = (u32) pk; }

    for (i = 0; i < 32; i++, bp++) {
        t = bp->tm;
        __asm__ __volatile__ ("" : "=r" (t) : "0" (t));
        if (t != 0) {
            gte_ldv0(&bp->vx);
            gte_rtps();
            gte_stsxy((long *) &sxy);
            gte_stflg(&flag);
            gte_stszotz(&otz);
            if ((u16) (sxy.vx + 0x200) < 0x401 &&
                (u16) (sxy.vy + 0x180) < 0x301 &&
                (u32) (otz - 0x10) < 0x1000) {
                z = otz - 0x10;
                c = t >> 6;
                d = (t * 3) >> 8;
                otp = (PTag_8018F694 *) ((z << 2) + (s32) ot);

                p0.vx = sxy.vx - c;
                p0.vy = sxy.vy - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vx = sxy.vx + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vy = sxy.vy + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                p0.vx = sxy.vx - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                {
                    TPage_8018F694 *tp = (TPage_8018F694 *) func_80010A08(8);
                    tp->len = 1;
                    tp->code0 = 0xE100002A;
                    tp->addr = otp->addr;
                    otp->addr = (u32) tp;
                }

                n = bp->r;
                x = n - bp->dr;
                n = x;
                if (x < 0) { n = 0; }
                bp->r = n;
                n = bp->g;
                x = n - bp->dg;
                n = x;
                if (x < 0) { n = 0; }
                bp->g = n;
                n = bp->b;
                x = n - bp->db;
                n = x;
                if (x < 0) { n = 0; }
                bp->b = n;
                x = n | (bp->r | bp->g);
                if ((u8) x == 0) {
                    bp->tm = 0;
                }
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018FE0C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C", func_8018FF98);
