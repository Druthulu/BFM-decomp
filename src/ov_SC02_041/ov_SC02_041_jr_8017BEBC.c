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
extern u8 D_80187304;
extern u8 D_80187274;
extern u8 D_80187250;
extern u8 D_8018722C;
extern u8 D_801872E0;
extern u8 D_801872BC;
extern u8 D_80187298;
extern u8 D_80187208;
extern void func_80145934(void);
extern u8 D_80187394;
extern u8 D_80187370;
extern u8 D_8018734C;
extern u8 D_80187328;
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
extern unsigned char D_8018678C[];
extern unsigned char D_801867BC[];
extern unsigned char D_8018680C[];
extern unsigned char D_8018683C[];
extern unsigned char D_8018686C[];
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
extern void (*D_801868BC[])(void *);
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
extern s32 D_80186984[];
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
extern u8 D_80186A0C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80186A14;
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
extern int D_801B7E58;
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
extern s32 D_801B7E5C;
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
extern s32 D_80186A44;
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
extern void (*D_80186AEC[])(void);
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
extern void (*D_80186B10[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80186B00;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80186B24[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80186B30[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80186B40[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80186B58[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80186B48;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80186B6C[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80186B88[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80186B78;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80186B9C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80186BB0[])(void);
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
extern s32 D_80186BC4;
extern void (*D_80186BEC[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80186BCC;
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
extern int (*D_80186C38[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80186C3C[])(void);
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
extern unsigned short D_801870A0[];
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
extern void (*D_801870B0[])(void);
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
extern int D_801B7E90;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801870D8[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801870B8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801870C8;
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
extern void (*D_80187118[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80187120[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801870EC;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018712C[])(void);
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
extern u8 D_801870FC;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B7E98;
extern s32 D_801B7EA4;
extern s32 D_801B7EA8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187168[])(s32 *);
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
extern s32 D_8018713C[];
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
extern s32 D_801B7EA0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_801873B8[])(void);
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
extern char D_801871D8[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018745C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801875B0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_801873CC;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801875B8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_801873DC;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_801873FC;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_801875C0[])(void);
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
extern void (*D_801875E8[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_801875F4[])(void);
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
extern void (*D_80187468[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80187698;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018677C[];
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
extern unsigned char D_801876AC[];
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
extern s8 D_801876E8[];
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
extern u16 D_80187730;
extern u16 D_80187732;
extern u16 D_80187734;
extern s32 D_80187738;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80187740;
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
extern int D_8018744C;
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
extern unsigned int D_801877C4[];
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
extern void (*D_80187874[])(void);
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
extern u16 D_801878A4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80187908;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B7EB0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018792C[])(void);
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
extern int D_801B7F08[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80187974[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80187964;
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
extern char D_801B7768[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018797C[])(void);
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
extern void (*D_801879D0[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80187998;
extern s16 D_801879CC;
extern s16 D_801879CA;
extern s16 D_801879C8;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801879DC[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B7F68;
extern u8 D_801B7F69;
extern u8 D_801B7F6A;
extern u8 D_801B7F6B;
extern u8 D_801B7F6C;
extern u8 D_801B7F6D;
extern u8 D_801B7F6E;
extern u8 D_801B7F6F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801879EC[])(void);
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
extern s32 D_801B7FA8;
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
extern void (*D_80187A30[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80187AAC[];
extern s32 D_80187ACC[];
extern u8 D_80187B48[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80187B68[];
extern u8 D_80187B88[];
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
extern void (*D_80187C24[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80187CA0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B7778;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80187CAC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80187CB4[])(void);
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
extern void (*D_80187D7C[])(void);
extern void func_80166618(void *a0);
extern void (*D_80187D8C[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80187D9C[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80187DA8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80187D08[];
extern u8   D_80187D1C[];
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
extern void (*D_80187DC0[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80187DC8[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80187DD0[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80187DD8[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80187DE0[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80187DE8[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80187DF0[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80187EA4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80187EAC[])(void);
extern void func_80169F00(void *a0);
extern char D_80187E5C[];
extern char D_80187E1C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80187EE4[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80187EF0[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80187F38[])(void);
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
extern void (*D_80187FB4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B82C8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80187FA8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80187FEC[];
extern unsigned short D_80187FF4[];
extern unsigned short D_80187FFC[];
extern unsigned char D_801B82D0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B82C8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188004[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B8404;
extern M2C_UNK D_801B8408;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B8390;
extern void (*D_80188034[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B840C[];
extern u8 D_801B8414[];
extern u8 D_801B83C4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018803C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80188058[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80188060[])(void);
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
extern void (*D_801880C8[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018806C;
extern u8 D_80188078;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_801880FC[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188104[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188158[])(void);
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
extern u16 D_8018818C[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018817C[];
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
extern s32 D_801881A8;
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
extern void (*D_80188220[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80188228[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80188230[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188238[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80188240[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80188248[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80188254[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80188260[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018826C[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018827C[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018828C[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80188294[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018829C[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801882A4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801882AC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801882B4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_801882BC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_801882C4[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_801882CC[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_801882D4[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_801882DC[])(void);
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
extern void (*D_801882E4[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801882EC[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_801882F4[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_801882FC[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80188304[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018830C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80188314[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018831C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80188324[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018832C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80188334[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018833C[])(void);
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
extern void (*D_80188380[])(void);
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
extern M2C_UNK D_80188344;
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
extern void (*D_801883B0[])(void);
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
extern void (*D_801883EC[])(void);
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
extern void (*D_80188444[])();
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
extern void (*D_80188454[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018845C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_801885C4[])();
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
extern void (*D_801885D0[])();
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
extern M2C_UNK D_801B79C0;
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
extern s16 D_801B9660;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B8B48;
extern short D_801B96D4;
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
extern s32 D_801B8F74;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B8F9C;
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
extern s16 D_801B8F58;
extern s32 func_8017A3B0(void);
extern short D_801B8F94;
extern short D_801B8F90;
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
extern s16 D_801B8F5C;
extern u16 D_801B8FDC;
extern u16 D_801B8FDE;
extern u16 D_801B8FE0;
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
extern s16 D_801B8FD4;
extern s16 D_801B8FD6;
extern s16 D_801B8FD8;
extern s16 D_801B8FCC;
extern s16 D_801B8FCE;
extern s16 D_801B8FD0;
extern void func_8017B7A8(void);
extern s16 D_801B8FEC;
extern s16 D_801B8FEE;
extern s16 D_801B8FF0;
extern s16 D_801B8FF4;
extern s16 D_801B8FF6;
extern s16 D_801B8FF8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B8FE4;
extern short D_801B8FE6;
extern short D_801B8FE8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B8F7C;
extern SV4 D_801B8F84;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B8FA4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B8FA0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_801887AC[])(void);
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


#include "common.h"

extern void func_80019064(void *a0);
extern u8 D_801887F8;
extern void (*D_80188850[])(void *);

void func_8017CD9C(void *a0) {
    func_80019064(&D_801887F8);
    D_80188850[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8017CE3C(s32 a0);
extern void func_80146CA0(void *a0);
void func_8017CDF4(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_8017CE3C(a0);
    func_80146CA0((void *)a0);
}


extern s32 D_801887B8;
extern s32 D_80188800;
extern void *D_801887BC[];
extern void func_80146CA0(void *a0);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);

void func_8017CE3C(s32 a0) {
    register s32 s0 asm("$16") = a0;
    s32 v0;
    s32 v1;
    s32 a3;

    v1 = *(s32 *)(s0 + 0x20);
    v0 = (*(u16 *)(s0 + 0xF4) + 0x800) & 0xFFF;
    *(s16 *)(v1 + 0x12) = v0;
    *(s16 *)(s0 + 0x244) = v0;
    func_80154274((s32 *)s0, (s32)&D_80188800);
    *(s32 *)(s0 + 0x234) = 0;
    func_80154A74(s0, 0x1C);

    v0 = *(s16 *)(s0 + 0xF2) << 4;
    a3 = *(s32 *)((s32)&D_801887B8 + v0);
    func_80146DE8((s32 *)s0, 0, 0, a3);

    v0 = *(s16 *)(s0 + 0xF2) << 4;
    func_801477E8((s32 *)s0, (s32)*(void **)((s32)&D_801887BC + v0));

    func_80149020((s32 *)s0);
    func_80146E90((s32 *)s0, 0x96);
    func_80146CA0((void *)s0);
}


typedef struct { short a, b, c; } SV3_80181D44_8017CEF4;   /* == the TU's own `SV3` (engine_types.h:612); renamed only because
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F19C_8017CEF4;   /*  8 bytes, align 2 */

/* Callee externs — spellings copied from src/ov_SC04_002/ov_SC04_002_jr_8017BEBC.c
 * (law 2). func_8017D098 is DEFINED later in that same TU as `void func_8017D098(void)`
 * (a trivial wrapper around func_80151664()); our call site sets $a0 before the jal but
 * the real body ignores it, so we declare it unprototyped (K&R style) to accept the
 * dead argument without a conflicting-prototype error against the later definition. */
extern void func_80149020(s32 *a0);
extern void func_80147A84(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern s32 func_801535F4(void *arg0);
extern void func_8017D098();
extern void func_80159B3C(void *a0);
extern void func_8015BF48(s32 *a0);
extern s32 func_80146E98(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80165718(s32 a0);

/* 16-byte-stride table at D_801887C0, indexed by the actor's 0xF2 animation/state id
 * (signed s16); only the table row's first word (offset 0) is read. */
typedef struct {
    s32 f0;
    u8 pad[12];
} Tbl16_8018BDE4_8017CEF4;

void func_8017CEF4(s32 a0) {

    extern Tbl16_8018BDE4_8017CEF4 D_801887C0[];
    s32 s0;
    s16 s1;
    s32 ret;

    s0 = *(s32 *)(a0 + 0x20);
    func_80149020((s32 *)a0);

    s1 = *(s16 *)(s0 + 0x12);
    *(s16 *)(s0 + 0x12) = *(u16 *)(a0 + 0x244);
    func_80147A84(a0);

    func_801473EC((s32 *)a0);
    func_80148038(a0, D_801887C0[*(s16 *)(a0 + 0xF2)].f0);
    func_80147460(a0);

    *(s16 *)(s0 + 0x12) = s1;

    if (*(s32 *)(a0 + 0x234) == 0) {
        if (*(s32 *)(a0 + 0x34) >= 0) {
            if ((*(u16 *)(a0 + 0xB8) & 0x8000) != 0) {
                __asm__ __volatile__("" ::: "memory");
                *(u16 *)(a0 + 0xB8) = *(u16 *)(a0 + 0xBA);
                *(s32 *)(a0 + 0x234) = *(s32 *)(a0 + 0x234) + 1;
            }
        }
    }

    ret = func_801535F4((void *)a0);

    if (ret == 1) {
        goto L_case1;
    }
    if (ret < 2) {
        goto L_default;
    }
    if (ret == 2) {
        goto L_case2;
    }
    goto L_default;

L_case1:
    func_8017D098(a0);
    func_80159B3C((void *)a0);
    func_80146A6C(2, (void *)a0, 0, 0, 0, 1, 0);
    func_80165718(a0);
    return;

L_case2:
    func_8017D098(a0);
    func_8015BF48((s32 *)a0);
    func_80146A6C(2, (void *)a0, 0, 0, 0, 1, 0);
    func_80165718(a0);
    return;

L_default:
    if (func_80146E98(a0) == 0) {
        return;
    }
    func_8017D098(a0);
    func_80159B3C((void *)a0);
    func_80146A6C(2, (void *)a0, 0, 0, 0, 1, 0);
    func_80165718(a0);
}


extern void func_80151664(void);
    void func_8017D098(void) {
        ((s32 (*)(void))func_80151664)();
    }



extern void func_80019064(void *a0);

void func_8017D0B8(void *a0) {

    extern u8 D_8018885C;
    extern void (*D_80188880[])(void *);
    func_80019064(&D_8018885C);
    D_80188880[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8017D158(s32 a0);
extern void func_80146CA0(void *a0);
void func_8017D110(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_8017D158(a0);
    func_80146CA0((void *)a0);
}


extern int func_801511E0(int arg);
extern s32 D_80188864;
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80172630(u8 *a0);
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 arg0);
extern void func_80149020(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);

void func_8017D158(s32 a0)
{
    register s32 s0 asm("$16") = a0;
    s32 a2, a3;

    func_80149020((s32 *)s0);
    func_80147324(0x451);
    func_801511E0(s0);
    func_80154274((s32 *)s0, (s32)&D_80188864);
    *(u8 *)(s0 + 0xDE) = 0x5A;
    func_80147324(0x7EB);

    a2 = 0;
    a3 = 0;
    ((void (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x3F, (void *)s0, a2, a3, 0, 0, 0);
    func_80172630((u8 *)s0);
    func_80146CA0((void *)s0);
}


extern void func_80149020(s32 *a0);
extern void func_8017D244(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_8017D1E0(s32 param_1)
{
    u8 cnt;

    func_80149020((s32 *)param_1);
    cnt = *(u8 *)(param_1 + 0xde);
    *(u8 *)(param_1 + 0xde) = cnt + 0xff;
    if (cnt == 0) {
        func_8017D244(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80019064(void*);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);
extern u8 D_80062C04[];

void func_8017D244(s32 a0)
{
    s32 s0 = a0;
    ((void (*)(s32))func_80019064)((s32)&(*(s32 *)D_80062C04));
    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}



extern void (*D_801888B8[])(void);

void func_8017D294(void *a0) {
    D_801888B8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8017D2D0);

#include "common.h"

extern void func_8017D744(s32 *a0);
extern void func_800183E0(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017DD50(s32 *a0);
extern void func_80147324(s32 arg0);
extern s32 func_80146E98(s32 a0);
extern s32 func_8017DD60(void *a0);
extern void func_8014ABF0(void);
extern void func_80146C3C();

extern void *D_801888C8[];
extern s32 D_801888B0[2];

void func_8017D38C(s32 param_1) {
    s32 iVar1;
    s32 iVar3;
    void *puVar2;

    iVar3 = *(s32 *)(param_1 + 0x20);
    func_8017D744((s32 *)param_1);
    if (*(s32 *)(param_1 + 0x30) == 0) {
        puVar2 = D_801888C8[*(s32 *)(param_1 + 0x2c)];
        if (D_801888C8[*(s32 *)(param_1 + 0x2c)] == 0) {
            *(s32 *)(param_1 + 0x30) = 0x20;
            *(s32 *)(param_1 + 0x2c) = 0;
            puVar2 = D_801888C8[0];
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
        func_8017DD50(D_801888B0);
        func_80147324(0x7F4);
        *(u32 *)(iVar3 + 4) = *(u32 *)(iVar3 + 4) | 0x80000000;
    }
    iVar1 = func_80146E98(param_1);
    if ((iVar1 != 0) && (iVar1 = func_8017DD60((void *)D_801888B0), iVar1 != 0)) {
        ((void (*)(s32))func_8014ABF0)(0x40);
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


void func_8017D728(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x4);
        *(s32 *)((s32)a0 + 0x14) = *(s32 *)((s32)a0 + 0x8);
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0xC);
    }


extern void func_80149374(s32 a0, s32 a1);

void func_8017D744(s32 *a0)
{
    register s32 t1 asm("$6");
    register s32 t2 asm("$2");
    register s32 t3 asm("$3");
    s32 x;

    t1 = a0[4];
    x = a0[13];
    t2 = a0[5];
    t3 = a0[6];
    a0[1] = t1;
    a0[2] = t2;
    a0[3] = t3;
    func_80149374(x, (s32)(a0 + 1));
}



extern void (*D_801888F0[])(void);

void func_8017D784(void *a0) {
    D_801888F0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Host TU (src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c) already has these three via
 * ../shared/engine_core.h -> engine_types.h as SVECTOR (:997), MATRIX (:1168) and
 * Vec32 (:1098) -- byte-identical layouts. Renamed here only because match_one
 * compiles standalone with -Iinclude (engine_core.h is not on that path); on bank,
 * drop these three typedefs and use the TU's own names. */
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0;   /*  8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_8017D7C0;  /* 16 bytes, align 4 */

/* ov_SC02_041 func_8017D7C0 -- 181 ins, zero-crack family exemplar (reach x4:
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

extern SV_8017D7C0 D_801888FC[]; /* stride 8, align 2 -> lwl/lwr + swl/swr copy */
extern V32_8017D7C0 D_8018892C;   /* 16 bytes, align 4 -> plain lw/sw copy      */
extern u16     D_8018893C[]; /* stride 2 scale table                       */

void func_8017D7C0(s32 param_1) {
    s16 buf[4];
    SV_8017D7C0 rot;
    MTX_8017D7C0 m;
    V32_8017D7C0 vel;
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

        sc = D_8018893C[*(s32 *)(param_1 + 0x30)];
        *(u16 *)(p + 0x18) = *(u16 *)(p + 0x1a) = *(u16 *)(p + 0x1c) = sc;

        vel = D_8018892C;
        rot = D_801888FC[*(s32 *)(param_1 + 0x2c)];

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

/* ---------------------------------------------------------------------------
 * INTEGRATION SURFACE (§161c) -- host TU src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c
 * Every decl above is either CHARACTER-IDENTICAL to a file-scope decl already in
 * the host TU (agrees => free, per §161c) or entirely new (no conflict):
 *
 *   AGREES with host file-scope (all < :2803, the first function definition):
 *     :119  extern void func_80015978(s32 a0, s32 *a1);
 *     :132  extern void func_801465C0(void);        <- void return; the TU's own
 *           established workaround for the real s32 return is the cast-call at
 *           :4192  `iVar3 = ((int (*)(void))func_801465C0)();` -- reused here.
 *     :161  extern void func_80146E90(s32 *a0, s32 a1);
 *     :163  extern void func_80015954(s32 a0, s32 a1);
 *     :242  extern void func_800484EC(s32 a0, s32 a1, s32 a2);
 *     :1091 extern int rand(void);                 (:956 `s32 rand(void)` also at
 *           file scope; s32==int so the two already coexist)
 *     :1681 extern void func_80146C3C();           (:1699 adds the `(void)` form;
 *           both already coexist. Cast-call form copied from :3304.)
 *     :2643 extern void func_80049CAC(s32 a0, s32 a1);
 *
 *   NEW, not declared anywhere in the host TU (no conflict possible):
 *     func_8001CF00  -- fleet-canon `extern void func_8001CF00(s32);`
 *                       (ov_SC02_027_jr_8016AB6C.c:2418 and 4 more overlays)
 *     D_801888FC / D_8018892C / D_8018893C -- per-overlay data, contiguous:
 *       D_801888FC[] stride 8 (6 entries) -> D_8018892C (16B) -> D_8018893C[] u16.
 *       NOTE for the banker: none of the three is in config/symbols.ov_SC02_041.txt
 *       (15 lines, no 0x801888xx entries), so they arrive as splat auto-names --
 *       confirm before/after the whole-binary gate.
 *
 *   TYPES: SV_/MTX_/V32_8017D7C0 are byte-identical restatements of engine_types.h
 *   SVECTOR(:997) / MATRIX(:1168) / Vec32(:1098). Prefer the engine_types names on
 *   bank (the host TU already pulls them in); the local typedefs exist only so
 *   match_one's standalone `-Iinclude` compile resolves them.
 *
 * WHY THE UNALIGNED COPY: `rot = D_801888FC[idx]` emits lwl/lwr + swl/swr, not
 * lw/sw, because the array is `extern` so gcc uses TYPE_ALIGN = 2 (all-s16 struct)
 * and its block-move takes MIN(src,dst) align < 4 => unaligned path. The sibling
 * 16-byte `vel = D_8018892C` copy is plain lw/sw because Vec32 is all-s32 (align 4).
 * The host TU's own carried decl layer already records this idiom verbatim:
 * "8 bytes, align 2 -> lwl/lwr/swl/swr copy".
 *
 * OTHER LEVERS worth carrying to the 3 siblings (ov_SC04_002:8017f19c,
 * ov_SC04_004:8017f65c, ov_SC04_011:8017f340), all of which are PURE h_seq copies:
 *   - `*(u16*)(p+0x18) = *(u16*)(p+0x1a) = *(u16*)(p+0x1c) = sc;` -- chained
 *     assignment stores RIGHT to LEFT (0x1c, 0x1a, 0x18), matching the target.
 *   - the 9-short tail is `*q++ =` three times inside a do-while, NOT q[0]/q[1]/q[2]
 *     with a `q += 3`: the target advances the pointer by 2 between stores (the
 *     addiu lands in each following jal's delay slot), which q[i] indexing cannot
 *     produce (it would emit sh 0/2/4($s0) + a single addiu 6).
 *   - the loop counter increments at the TOP of the body (`i = 0; do { i++; ... }
 *     while (i < 3);`), not the bottom -- a for-loop rotation puts the addiu after
 *     the last store instead of in the first jal's delay slot.
 *   - `((rand() & 0x1f) - 0x10) * 11` is left as a literal *11; gcc-2.7.2 expands
 *     it to sll1/addu/sll2/subu exactly as the target has it.
 * --------------------------------------------------------------------------- */


extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_8017DB58();
extern void func_8017DCDC();

void func_8017DA94(s32 param_1) {
    func_8017DB58(param_1);
    func_8017DCDC(param_1);
    if (func_80146E98(param_1) != 0) {
        *(s32 *)(param_1 + 0x10) >>= 2;
        *(s32 *)(param_1 + 0x14) >>= 2;
        *(s32 *)(param_1 + 0x18) >>= 2;
        func_80146E90((s32 *)param_1, 0x40);
        *(s16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8017DB10);

INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8017DB58);

/* func_8017DB80 -- ov_SC02_041, subseg ov_SC02_041_jr_8017BEBC (87 ins).
 * Zero-crack sibling family exemplar (reach x5).
 *
 * STEP 0 (S160g callee-set sibling search): func_80017E68 and func_80017DC4 are
 * ALREADY declared in the destination TU (src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c
 * :1710 `extern void func_80017E68(void *a0, void *a1);` and :1762
 * `extern s32  func_80017DC4(void *a0, void *a1);`) -- reused verbatim below, so
 * those two are FREE per S161c (character-identical). func_80017DF8 and
 * func_80017168 are declared NOWHERE else in src/ (only as INCLUDE_ASM stubs in
 * src/800.c) -- brand new symbols, no conflict is possible, so their signature is
 * chosen freely to match the observed calling convention (void*, void*, no return
 * used, like their address-neighbour func_80017E68).
 *
 * STRUCTURE (byte-read off the .s): the stack frame is 0x10 arg-build + 0x20 MATRIX
 * (`mtx`, translation mtx.t[] read/written directly at sp+0x24/0x28/0x2c -- exactly
 * offset 0x14 into a `{s16 m[3][3]; s32 t[3];}` struct, the SAME MATRIX shape this
 * TU's func_8017D7C0 (:3337-3492, matched) already restates locally as
 * MTX_8017D7C0/SV_8017D7C0) + 0x8 s16 buf[4] (`func_80015978` position temp, the
 * TU's established `s16 buf[4]; func_80015978(a0+4,(s32*)buf);` idiom, see
 * func_8017EC1C's comment at :4138-4144) + 0x10 saved s0/s1/s2/ra.
 *
 * s1(a0)+0x38 is 9 consecutive s16 (3 groups of 3, stride 6) -- the EXACT SAME
 * offset/shape func_8017D7C0 (:3419-3430, this same TU) fills with 3x jittered
 * rand() triples via `*q++ =` in a do-while(i<3). This function consumes that
 * jitter array: 3 unrolled accumulate-into-mtx.t[]-then-draw blocks, each block
 * ending in `func_80017168(a1,&mtx)` and (except the last) re-oriented via
 * `func_80017E68(buf,&mtx)` before the next block -- a 3-point trail/line-strip
 * built from the particle's 3 jittered offset triples.
 *
 * Register note: $s0 is reused for TWO disjoint live ranges (actor's 0x20 pointer
 * field for the first two setup calls, then &mtx's position temp) -- normal
 * gcc-2.7.2 economy when the ranges don't overlap; no manual lever needed, it falls
 * out of plain sequential C.
 */

typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017DB80; /* 0x20 bytes, align 4 --
    byte-identical restatement of this TU's own MTX_8017D7C0 (:3334); renamed only
    because match_one compiles standalone (-Iinclude, no engine_core.h on that
    path). On bank, drop this typedef and reuse the TU's own MTX_8017D7C0 name. */

extern s32  func_80017DC4(void *a0, void *a1);   /* :1762, host TU AGREES verbatim */
extern void func_80017DF8(void *a0, void *a1);   /* NEW -- no conflict anywhere    */
extern void func_80015978(s32 a0, s32 *a1);      /* :119,  host TU AGREES verbatim */
extern void func_80017E68(void *a0, void *a1);   /* :1710, host TU AGREES verbatim */
extern void func_80017168(void *a0, void *a1);   /* NEW -- no conflict anywhere    */

void func_8017DB80(s32 a0, s32 a1)
{
    s32 p;
    MTX_8017DB80 mtx;
    s16 buf[4];

    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(a1 + 0x1c) = 0x50000000;

    func_80017DC4((void *)(p + 0x18), &mtx);
    func_80017DF8((void *)(p + 0x10), &mtx);
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




void func_8017DCDC(s32 a0) {
    s32 p;
    *(s32 *)(a0 + 0x4) += *(s32 *)(a0 + 0x10);
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x14);
    *(s32 *)(a0 + 0xC) += *(s32 *)(a0 + 0x18);
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x10) += *(s32 *)(a0 + 0x4C);
    *(u16 *)(p + 0x12) += *(s32 *)(a0 + 0x50);
    *(u16 *)(p + 0x14) += *(s32 *)(a0 + 0x54);
}


void func_8017DD50(s32 *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0x80404080;
    }


extern u16 D_800B99DA;

s32 func_8017DD60(void *a0) {
    u8 val;
    u16 global;
    s32 result;
    s32 cmp;
    register s32 zr __asm__("$0");

    val = *(u8 *)((s32)a0 + 3) - 2;
    *(u8 *)((s32)a0 + 3) = val;

    if ((val & 0xFF) == 0) {
        goto ret1;
    }

    __asm__ __volatile__("" : "=r"(val) : "0"(val));

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

    cmp = result + zr;

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




extern void func_80029124(s32, s32);
extern void func_800291F0(s32, s32);
extern void func_8002D4C8(s32, s32);
/* NOTE: func_8017E5AC is DEFINED later in this TU as `int func_8017E5AC(int)`.
 * Conform to that signature (byte-neutral: return value unused, $a0 = 0). */
extern int func_8017E5AC(int);

void func_8017DDEC(void)
{

    extern s32 D_8011F9C4;
    extern s32 D_80188E98;
    extern s32 D_801890DC;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_8011F9C4 = 1;
    func_80029124(0xD4, 1);
    func_800291F0(4, 0xD4);
    func_8002D4C8(6, 0);
    D_801274C8 = (u8 *)&D_80188E98;
    D_801274CC = (void *)&D_801890DC;
    func_8017E5AC(0);
}


extern int func_8017E5AC(int);
extern s32 D_8011F9C4;
extern s32 D_801890F0;
extern s32 D_801893AC;
extern u8 *D_801274C8;
extern void *D_801274CC;
extern void func_80029124(s32, s32);
extern void func_800291F0(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017DE5C(void)
{
    D_8011F9C4 = 1;
    func_80029124(0xD5, 1);
    func_800291F0(4, 0xD5);
    func_8002D4C8(6, 0);
    D_801274C8 = (u8 *)&D_801890F0;
    D_801274CC = (void *)&D_801893AC;
    ((void (*)(s32))func_8017E5AC)(1);
}



extern void (*D_80188C48[])(void);

void func_8017DECC(void *a0) {
    D_80188C48[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E0FC(void);
extern void func_800167B8(s32 a0);

s32 func_8017DF08(s32 a0) {
    func_8017E0FC();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017DF4C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017E124(void);

s32 func_8017DF70(s32 a0) {
    func_8017E124();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017DFB0(u8 *a0) {
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
void func_8017E02C(void) {
    func_800D1EBC();
}



extern void (*D_80188C5C[])(void);

void func_8017E04C(void *a0) {
    D_80188C5C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017E088(s32 a0) {
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
void func_8017E0FC(void) {

    extern s32 D_80188C68(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80188C68, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E124(void) {

    extern s32 D_80188C6C(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80188C6C, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017E27C(void *a0);

void func_8017E14C(void) {

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
    D_8012695C = 0x4b0;
    D_80126968 = 0x2aa;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E27C, 0);
    func_8012A094((s32)D_80126948);
    func_8017E27C(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017E27C(void *a0);

void func_8017E1E4(void) {

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
    D_8012696A = 0xA00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E27C, 1);
    func_8012A094((s32)D_80126948);
    func_8017E27C(D_80126948);
}



extern void (*D_80188C78[])(void);

void func_8017E27C(void *a0) {
    D_80188C78[*(u8 *)((s32)a0 + 0x4)]();
}


typedef struct {
    s16 v[4];
} Blk8_80126940_8017E2B8;

void func_8017E2B8(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80188C80[];
    extern Blk8_80126940_8017E2B8 D_80126940;
    extern u16 func_80148800(s32 *a0);
    extern void func_8017E414(s32 param_1, s16 *param_2);
    Blk8_80126940_8017E2B8 sp10;
    u8 t;
    s32 sel;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80188C80[t];
    }
    sp10 = D_80126940;

    sel = (sp10.v[0] < -0xC38);
    if (sel)
        sel = 0xA00;
    else
        sel = 0x600;
    *(s16 *)(a0 + 0x22) = sel;

    func_8017E414(a0, sp10.v);
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017E414(s32 param_1, s16 *param_2);

void func_8017E374(s32 a0) {

    extern s16 D_80188C84[];
    extern Blk8_80126940_8017E374 D_80126940;
    Blk8_80126940_8017E374 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80188C84[t];
    }
    sp10 = D_80126940;
    func_8017E414(a0, sp10.v);
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

void func_8017E414(s32 param_1, s16 *param_2) {
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

int func_8017E5AC(int param_1)
{

    extern unsigned char D_80188C88[];
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_80188C88 + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}



s32 func_8017E5DC(void) {
    return 85;
}



extern void (*D_80188C90[])(void);

void func_8017E5E4(void *a0) {
    D_80188C90[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s16 a1);
    extern s32 func_8012AD50(void *a0);
    void func_8017E620(s32 *a0) {
        func_8012BF4C(a0, 0);
        ((s32 (*)(s32))func_8012AD50)((s32)a0);
    }


void func_8017E7A4(void *);
/* Declarations conformed VERBATIM to src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c
   (func_8012BF4C @3566 above the splice; func_8012BEE8 @4244/@4260 below it).
   All type disagreement is pushed to a cast at the use site -> zero bytes change. */
extern s32 func_8012BEE8(s32 arg);
extern s32 func_8017267C(s32 *a0);
extern void func_8012BF4C(s32 *a0, s16 a1);
extern s32 *D_80126B78;
extern s32 D_80126B58;
extern s32 rand(void);

void func_8017E654(void *a0)
{
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

    func_8017E7A4(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017E7A4(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017E7A4(a0);
        }

        s0 = s0 + 1;
    } while (s0 < 3);
    goto end_func;

default_case:
    func_8017E7A4(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017E7A4(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017E7A4(a0);
        }

        s0 = s0 + 1;
    } while (s0 <= 0);

end_func:
    v0 = rand();
    ((void (*)(s32, s32))func_8012BF4C)((s32)a0, (v0 & 0x1F) | 0x20);
}


#include "common.h"

extern void func_80149350(s32 arg0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012E544(s32 a0);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern s32 D_80126B58;
extern u8 D_80188C98[];

void func_8017E7A4(void *a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];
    s32 t;
    u8 *r;
    u8 *p;
    s32 i;
    s32 o;
    s16 out[4];

    t = *(s16 *)((s32)a0 + 0x70);
    r = &D_80188C98[t * 8];
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



extern void (*D_80188CCC[])(void);

void func_8017E890(void *a0) {
    D_80188CCC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_8017E8CC — state entry: init the sub-object at +4/+0x10, bind the
 * primitive at +0x20 to the command list D_80188CC0 (0x270 / 0x100), paint
 * its RGB (0x40,0x40,0x40) + code 0x9C, OR 0xD0000000 into its tag word,
 * clear the counter at +0x2C, then seed three random fields and bump the
 * state word at +2.
 */

extern void func_800159E4(s32 a0, s32 a1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern int rand(void);

void func_8017E8CC(int param_1)
{
    extern unsigned char D_80188CC0[];
    int p;
    int r1;
    int r2;

    p = *(int *)(param_1 + 0x20);
    ((void (*)(int, int))func_800159E4)(param_1 + 4, param_1 + 0x10);
    ((void (*)(int, int, int, int))func_8001CC3C)(p, (int)D_80188CC0, 0x270, 0x100);
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


void func_8017E9B0(s32 *a0) {
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


#include "common.h"

/* func_8017EA1C — per-frame update for the effect entity that func_8017E8CC
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

void func_8017EA1C(int param_1)
{
    UVec_8017EA1C v;
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



extern void func_80019064(void *a0);

void func_8017EB08(void *a0) {

    extern u8 D_8019AB88;
    extern void (*D_8019ABB0[])(void *);
    func_80019064(&D_8019AB88);
    D_8019ABB0[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_8017EB60(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8017EBB0(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


extern void func_80147324(s32 a0);
extern int func_801511E0(int arg);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8017EDC4(void);
extern s32 func_80172630(u8 *a0);
extern void func_80146CA0(void *a0);
extern s16 D_8019AB90;

void func_8017EBB0(s32 p)
{
    func_80147324(0x451);
    func_801511E0(p);
    func_80154274((s32 *)p, (s32)&D_8019AB90);
    func_80149020((s32 *)p);
    *(u8 *)(p + 0xDE) = 0x1E;
    *(u8 *)(p + 0xDF) = 0;
    func_8017EDC4();
    func_80172630((u8 *)p);
    func_80146CA0((void *)p);
}



/* func_8017EC1C @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_8017EC1C --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_8017EC1C.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_8017ED70 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_8017EDE8` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
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
 *   if (func_8017EDE8() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
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
extern s32 func_8017EDE8(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_8017ED70(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_8017EC1C(s32 param_1)
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
        iVar1 = func_8017EDE8();
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
        func_8017ED70(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_8017ED70 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
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
 *   func_8017ED70  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_8017ED70(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_8017EDC4(void)
{
    extern u8 D_801B9013;
    s32 i = 19;
    u8 *p = &D_801B9013;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_8017EDE8(void)
{

    extern u8 D_801B9000[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801B9000;
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



extern void (*D_8019ABBC[])(void);

void func_8017EE2C(void *a0) {
    D_8019ABBC[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801B9014 + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017F05C(void*);
extern void func_8017F02C(s32*);
extern int rand(void);

void func_8017EE68(int param_1)
{

    extern unsigned char D_801B9014[];
    register int iVar3 __asm__("$16");
    register int iVar3b __asm__("$19");
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801B9014 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    *(int *)(param_1 + 0x20) = iVar3;
    iVar3b = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8017F05C)(iVar5);
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
        ((void (*)(int))func_8017F02C)(param_1);
    }
}




extern s32 func_8017F070(s32 *a0, s32 a1);
extern void func_8017F02C(s32 *a0);

void func_8017EFB4(s32 *a0)
{

    extern unsigned char D_801B9014[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801B9014 + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_8017F070(a0, table_base) == 0) {
            return;
        }
    }

    func_8017F02C(a0);
}



















extern void func_80146C3C(void);
void func_8017F02C(s32 *param_1)
{

    extern s8 D_801B9000;
  int new_var;
register s32 p __asm__("$4");
register s32 r __asm__("$3");
  p = (s32) (&D_801B9000);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}



void func_8017F05C(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_8017F070 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_8017F070(s32 *a0, s32 a1);
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
s32 func_8017F070(s32 *a0, s32 a1) {
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



extern void (*D_8019ABF4[])(void);

void func_8017F0D8(void *a0) {
    D_8019ABF4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8017F114(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_8017F1B0(s32 param_1);

void func_8017F160(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_8017F1B0(param);
    }
}


void func_8017F1A8(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8017F314();

void func_8017F1B0(s32 param_1) {

    extern u32 *D_8019ABEC[];
    extern Blk8 D_8019AC08[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_8019ABEC[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_8019AC08[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8017F314(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
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

extern SVECTOR_8017E6D8 D_801B9514[4];
extern struct PW8017E6D8 D_801B9534;
extern struct PW8017E6D8 D_801B9538;
extern u8 D_801B953C, D_801B953D, D_801B953E, D_801B9540, D_801B9541, D_801B9542;
extern int D_801B9544;

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

void func_8017F314(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801B9514[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801B9544 = 0x50000000;
        D_801B953C = 0;
        D_801B953D = 0;
        D_801B953E = 0;
        D_801B9540 = 0;
        D_801B9541 = 0;
        D_801B9542 = 0;
    }
    D_801B9534 = h[0];
    D_801B9538 = h[1];

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



typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0_8017F19C_8017F690; /* 0x20 bytes, align 4 */

typedef struct { u16 x, y, z, w; } V8_80181368_8017F690;

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8017F690(s32 a0, s32 a1) {
    V8_80181368_8017F690 sp10;
    V8_80181368_8017F690 sp18;
    s32 t;
    s32 r;

    sp10.x = *(u16 *)(a0 + 0x6);
    sp10.y = *(u16 *)(a0 + 0xA) - 0x20;
    sp10.z = *(u16 *)(a0 + 0xE);
    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = (s16)a1;
    sp18.y = sp10.y;
    sp18.x = sp10.x - ((t * r) >> 12);
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp18.z = sp10.z - ((t * r) >> 12);
    if ((func_80133784(1, &sp10, (s32)&sp18) & 0x8000) == 0) {
        t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.x = *(u16 *)(a0 + 0x6) - ((t * 8) >> 12);
        sp10.y = *(u16 *)(a0 + 0xA) - 0x10;
        t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.z = *(u16 *)(a0 + 0xE) - ((t * 8) >> 12);
        sp18.x = sp10.x;
        sp18.y = sp10.y + 0x20;
        sp18.z = sp10.z;
        if (func_80133784(1, &sp10, (s32)&sp18) & 0x6000) {
            return 0;
        }
    }
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    return 1;
}


typedef struct { short a, b, c; } SV3_80181D44_8017CEF4_8017F81C;   /* == the TU's own `SV3` (engine_types.h:612); renamed only because

/* Declarations conform VERBATIM to the ones already present in this TU
 * (src/ov_SC04_005/ov_SC04_005_jr_8017BEBC.c, lines 6342-6344 / 845 / 2190-2191)
 * for the already-matched sibling func_8018259C, which is the same skeleton
 * template as this function (same offsets, callees, mask constants) except
 * for the tail control flow after the second func_80133784 call. */

typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0_8017F19C_80182728_8017F81C; /* 0x20 bytes, align 4 */

typedef struct { u16 x, y, z, w; } V8_80181368_80182728_8017F81C;

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8017F81C(s32 a0, s32 a1) {
    V8_80181368_80182728_8017F81C sp10;
    V8_80181368_80182728_8017F81C sp18;
    s32 t;
    s32 r;

    sp10.x = *(u16 *)(a0 + 0x6);
    sp10.y = *(u16 *)(a0 + 0xA) - 0x20;
    sp10.z = *(u16 *)(a0 + 0xE);
    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = (s16)a1;
    sp18.y = sp10.y;
    sp18.x = sp10.x - ((t * r) >> 12);
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp18.z = sp10.z - ((t * r) >> 12);
    if (!(func_80133784(1, &sp10, (s32)&sp18) & 0x8000)) {
        t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.x = *(u16 *)(a0 + 0x6) - ((t * 8) >> 12);
        sp10.y = *(u16 *)(a0 + 0xA) - 0x10;
        t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.z = *(u16 *)(a0 + 0xE) - ((t * 8) >> 12);
        sp18.x = sp10.x;
        sp18.y = sp10.y + 0x20;
        sp18.z = sp10.z;
        return (func_80133784(1, &sp10, (s32)&sp18) & 0x6000) == 0;
    }
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    return 1;
}


extern s32 func_8004787C(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8017F81C(s32 a0, s32 a1);
extern u8 D_801A3560[];
extern u8 D_801A3608[];
extern u8 D_801A3710[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B1B4(s32, void*);
extern void func_8012B200(u8 *a0);
extern void func_8012CBA4(s32 a0);

void func_8017F9A4(s32 a0) {
    s32 sp10[3];
    u16 v0;
    s32 ret;
    u16 *p;
    u16 *p2;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = -(func_8004787C(*(s16 *)(a0 + 0xFC)) << 7);

    v0 = (*(u16 *)(a0 + 0xFC) + 0x80) & 0x7FF;
    *(u16 *)(a0 + 0xFC) = v0;
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_8012A828(a0, D_801A3608);
        *(s16 *)(a0 + 0xFC) = 0;
    }

    ret = func_8012B8E4(a0, 8);
    p = (u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    *p = (u16)(*p + ret);

    p2 = (u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    v0 = *p2 & 0xFFF;
    *p2 = v0;
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);

    func_8012CBA4(a0);

    if (func_8017F81C(a0, 0x48) != 0) {
        func_8012A828(a0, D_801A3560);
        *(s16 *)(a0 + 0xFC) = 1;
        *(s16 *)(a0 + 0x2) = 1;
        func_8012B200((u8 *)a0);
    }

    if (func_8012BCCC(a0) < 0x2401) {
        *(s16 *)(a0 + 0x2) = 3;
        func_8012A828(a0, D_801A3710);
    }
}


extern void (*D_8019AD84[])();
extern s32 func_801659CC(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FABC(s32 a0) {
    D_8019AD84[*(u16 *)(a0 + 2)]();
    if (((a0 != 0) && (*(s16 *)(a0 + 0x70) == 3)) && (func_801659CC() != 0)) {
        *(s16 *)(a0 + 0x70) = 0;
        func_8002D4C8(0xB6B, 0);
    }
}


extern u8 D_801A3AA0[];
extern u8 D_801A3BC0[];
extern void func_8012A828(s32 a0, void *a1);

void func_8017FB38(s32 a0) {
    if (*(s32 *)(a0 + 0x90) == (s32)&D_801A3AA0) {
        func_8012A828(a0, D_801A3BC0);
    } else {
        *(s16 *)(a0 + 0x98) = 0;
    }
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    *(s16 *)(a0 + 0x2) = 1;
    *(s16 *)(a0 + 0xFC) = 0x1E;
}


extern void func_8002AC00(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FBA0(u8 *a0) {
    func_8002D4C8(0xA9C, 0);
    func_8002AC00(0x15);
    if ((a0[0x5E] != 0x33) && (*(s16 *)(a0 + 0x70) == 3)) {
        *(s16 *)(a0 + 0x70) = 0;
        func_8002D4C8(0xB6B, 0);
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80165988(void);

void func_8017FC04(void *arg0) {
    void *s0 = arg0;

    if ((*(u8 *)((u8 *)s0 + 0x5E) == 0x33) && (*(s16 *)((u8 *)s0 + 0x70) == 3)) {
        func_80165988();
    }
    if (*(s32 *)((u8 *)s0 + 0x78) != 0) {
        func_8002A04C((s32)s0);
    }
    func_8012C218(s0);
}


void func_8017FC70(s32 a0) {
    extern u8 D_8019ACB8[];
    extern u8 D_801A3560[];
    extern u8 D_8019AD2C[];
    extern u8 D_8019ACEC[];
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern s32 func_80143970(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012B23C(s32 a0);

    if (func_8012C354(a0, (s32)D_8019ACB8) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = -1;
        func_80143970(a0);
        func_8012A828(a0, D_801A3560);
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
        func_8012B23C(a0);
        if (*(s16 *)(a0 + 0x70) == 3) {
            *(s32 *)(a0 + 0xBC) = (s32)D_8019AD2C;
            *(u16 *)(a0 + 0x76) = 0x280;
        } else {
            *(s32 *)(a0 + 0xBC) = (s32)D_8019ACEC;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8017FD14);

extern s16 D_80126B98;
extern s16 D_80126B9A;
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s16 D_80126B96;
extern u8 D_8019AD74[];
extern u8 D_8019AD7C[];
extern u8 D_801A3560[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);

void func_8017FE34(s32 a0) {
    s32 v1;
    s32 p;
    s16 v1b;

    v1 = *(s32 *)(a0 + 0x94);
    if ((u32)(v1 - 0xF) < 6) {
        if (v1 == 0xF) {
            func_8002D4C8(0x7E4, 0);
        }
        if (func_8012DEB8(a0, (s32)&D_8019AD74, (s32)&D_8019AD7C) == 1) {
            (*(u16 *)&D_80126B96) = 0x4012;
            p = *(s32 *)(a0 + 0x20);
            D_80126B9A = *(u16 *)(p + 0x12);
            v1b = *(s16 *)(a0 + 0x70);
            if (v1b == 2) {
                goto case_eq2;
            }
            if (v1b >= 3) {
                goto case_ge3;
            }
            if (v1b < 0) {
                goto after_switch;
            }
            goto store_zero;
        case_ge3:
            if (v1b != 3) {
                goto after_switch;
            }
        store_zero:
            D_80126B98 = 0;
            goto after_switch;
        case_eq2:
            D_80126B98 = 1;
        }
    }
after_switch:
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_8012A828(a0, (void *)&D_801A3560);
        *(s16 *)(a0 + 0xFC) = 0x1E;
        *(s16 *)(a0 + 0x2) = 1;
        func_8012B200((u8 *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8017FF48);


// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);

void func_8017FFB8(s32 arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern void D_801AB8A8;
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801AB8A8)) {
        func_8012A828(arg0, &D_801AB8A8);
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012EFB8(s32 a0);

void func_80180000(void *a0) {
    u16 in3[3];
    s16 out2[2];
    s32 v;

    in3[0] = *(u16 *)((char *)a0 + 0x6);
    in3[1] = *(u16 *)((char *)a0 + 0xA);
    in3[2] = *(u16 *)((char *)a0 + 0xE);

    ((u32 (*)(u16 *, s16 *))func_8012EFB8)(in3, out2);

    v = out2[0];
    if (v < 0) {
        v = -v;
    }
    if (v < 0xB5) {
        v = out2[1];
        if (v < 0) {
            v = -v;
        }
        if (v < 0xA1) {
            func_8002D4C8(0x98A, 0);
        }
    }
}



extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801ABD30;

void func_8018008C(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801ABD30);
    *(s32 *)(a0 + 0x1C) = 0x14;
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);

void func_801800CC(s32 a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern void D_801AB8A8;
    *(s16 *)(a0 + 0x2) = 3;
    func_8012A828(a0, &D_801AB8A8);
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    *(s16 *)(a0 + 0x5E) = 0;
    *(s16 *)(a0 + 0xDC) = 0;
    *(s32 *)(a0 + 0x1C) = 0x2D;
}



// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_801801CC else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_801801CC(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801ABC88;

s32 func_8018011C(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_801801CC(param_1);
        return 1;
    }
    sVar1 = *(s16 *)(param_1 + 0xdc) + 1;
    *(s16 *)(param_1 + 0xdc) = sVar1;
    if (sVar1 < 0x79) {
        return 0;
    }
    if (param_3 >= iVar2) {
        return 0;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_8012A828(param_1, &D_801ABC88);
    return 1;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801ABA48;

void func_801801CC(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801ABA48);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_80180228(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x5;
        *(s32 *)((s32)a0 + 0x1c) = 0x14;
    }


typedef struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } St_80182784_80185DA8_8018023C;
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F19C_8018023C;   /*  8 bytes, align 2 */
typedef struct {
    s32 f0;
    u8 pad[12];
} Tbl16_8018BDE4_8018023C;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8018023C;

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012EFB8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

void func_8018023C(void *a0) {

    extern void D_801AB8A8;
    if (*(s32 *)((char *)a0 + 0x1C) == 9) {
        extern u8 D_801A3DAC[];
        extern u8 D_801A3DBC[];

        func_8012D5E4((s32)a0, (s32)D_801A3DAC, (s32)(D_801A3DAC + 8), 0x10);

        if (*(s16 *)((char *)a0 + 0x70) & 0x8000) {
            u16 out[4];
            struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } s;
            s32 buf[8];

            func_8012EC04((s32)a0, 0, buf);
            ((void (*)(s32 *, u8 *, u16 *))func_8012F14C)(buf, D_801A3DBC, out);

            s.f6 = 0x23E;
            s.f0 = out[0];
            s.f2 = out[1];
            s.f4 = out[2];
            s.fA = 0;
            s.fC = 0x7FFF;

            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12);
            func_8012C51C(&s, (s32)a0);
            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12) + 0x100;
            func_8012C51C(&s, (s32)a0);
            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12) - 0x100;
            func_8012C51C(&s, (s32)a0);
        }

        {
            u16 in3[3];
            s16 out2[2];
            s32 v;

            in3[0] = *(u16 *)((char *)a0 + 0x6);
            in3[1] = *(u16 *)((char *)a0 + 0xA);
            in3[2] = *(u16 *)((char *)a0 + 0xE);

            ((u32 (*)(u16 *, s16 *))func_8012EFB8)(in3, out2);

            v = out2[0];
            if (v < 0) {
                v = -v;
            }
            if (v < 0xB5) {
                v = out2[1];
                if (v < 0) {
                    v = -v;
                }
                if (v < 0xA1) {
                    func_8002D4C8(0x98B, 0);
                }
            }
        }
    }

    if (func_8012BEE8((s32)a0) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 3;
        func_8012A828((s32)a0, &D_801AB8A8);
        *(u16 *)((char *)a0 + 0x5C) = 0xAA10;
        *(s16 *)((char *)a0 + 0x5E) = 0;
        *(s16 *)((char *)a0 + 0xDC) = 0;
        *(s32 *)((char *)a0 + 0x1C) = 0x2D;
    }
}


extern void func_80184D20(s32 a0, u16 *a1, s16 a2);

void func_801803F0(void *a0) {
    s16 rec[3];

    if (*(u16 *)((char *)a0 + 0x5E) == 0x24) {
        rec[0] = 2;
        rec[1] = 0xF;
        rec[2] = -2;
        func_80184D20((s32)a0, (u16 *)rec, 0xD);
    }
}



/* Fresh mass-lane crack (Phase-31 wave T). No banked twin was found for this
 * skeleton (grepped D_801B9548 / D_801A3D6C / D_801A3D8C / D_801A3DC4 / the
 * jal callees across src/ -- only extern decls / INCLUDE_ASM stubs turned up,
 * all for unrelated overlay-local reuses of the same address). The dispatch
 * head (D_801A3DC4[*(u16*)(a0+2)]();) mirrors the ALREADY-BANKED
 * func_8017EC70 in THIS SAME TU (D_8018C074[*(u16*)((s32)a0+2)]();) -- same
 * idiom, used as a hint per law 1 (never copied its symbols). */

extern s32 func_8012C044(s32 a0);
extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);
extern void func_8012E8A8(u8 *a0);
extern void func_800183E0(s32 a0);

void func_80180438(void *a0) {

    extern void (*D_801A3DC4[])(void);
    extern u16 D_800B99DA;
    extern u16 D_801A3D6C[];
    extern u16 D_801B9548[];
    extern u8 D_801A3D8C[];
    void *s0 = a0;

    D_801A3DC4[*(u16 *)((u8 *)s0 + 0x2)]();

    if (func_8012C044((s32)s0)) {
        *(s16 *)((u8 *)s0 + 0x100) = 1;
        __asm__ __volatile__("" ::: "memory");
        *(s16 *)((u8 *)s0 + 0x76) = 0;
        if (*(s16 *)((u8 *)s0 + 0x100) == 0) {
            func_8002A04C((s32)s0);
        }
        if (*(s16 *)((u8 *)s0 + 0xFE) == 0) {
            ((void (*)(void *))func_8012C098)(s0);
        } else {
            *(s16 *)((u8 *)s0 + 0x2) = 6;
            func_8012E8A8((u8 *)s0);
            *(s16 *)((u8 *)s0 + 0x5C) = 0;
            *(u8 *)((u8 *)s0 + 0xC1) = 0;
        }
    }

    if (*(s16 *)((u8 *)s0 + 0xFE) != 0) {
        u16 *src = D_801A3D6C;
        s32 shift = D_800B99DA & 0xF;
        u16 *dst = &D_801B9548[shift];
        s32 i;

        for (i = 0; i < 0xF - shift; i++) {
            *dst++ = *src++;
        }
        dst = D_801B9548;
        for (i = 0; i < shift; i++) {
            *dst++ = *src++;
        }
        func_800183E0((s32)D_801A3D8C);
    }
}



extern void (*D_801A3DE8[])(void);

void func_80180584(void *a0) {
    D_801A3DE8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_801A3DFC[])(void);

void func_801805C0(void *a0) {
    D_801A3DFC[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0xCC) + 0x8) = *(u16 *)((s32)a0 + 0x6);
        *(u16 *)(*(s32 *)((s32)a0 + 0xCC) + 0xA) = *(u16 *)((s32)a0 + 0xA);
        *(u16 *)(*(s32 *)((s32)a0 + 0xCC) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    }
}


extern u8 D_801A3DF0[];

void func_80180648(s32 param_1)
{
    s32 v0;
    s32 s0;
    u16 uVar1;

    v0 = func_8012C1B8();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(v0, 0);
        v0 = *(s32 *)(param_1 + 0x20);
        *(u16 *)(v0 + 0x1a) = 0x1800;
        *(u16 *)(v0 + 0x18) = 0x1800;
        s0 = func_8012C194();
        if (s0 == 0) {
            func_8012CAE4(param_1);
        } else {
            *(s32 *)(param_1 + 0xCC) = s0;
            func_8001CB6C(s0, (s32)&D_801A3DF0, 0x2E0, 0x100);
            *(u8 *)(s0 + 0x27) = 0x37;
            *(u16 *)(s0 + 0x10) = 0x400;
            *(u32 *)(s0 + 4) |= 0x50000000;
            uVar1 = *(u16 *)(param_1 + 0xFC);
            *(u16 *)(s0 + 0x1A) = 0x1800;
            *(u16 *)(s0 + 0x18) = 0x1800;
            *(u16 *)(s0 + 0x14) = uVar1;
            *(u16 *)(param_1 + 2) = 1;
            func_80143994(param_1, 0x1000);
        }
    }
}



extern void func_8012B2CC(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80180720(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF00000);
}


extern void func_8012CBF4(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80180804(s32 a0);
extern u8 D_801A3E08[];
extern s16 D_80126B96;

void func_80180778(s32 a0)
{
    s32 v1;
    s32 v0;

    v1 = *(s32 *)(a0 + 0xCC);
    *(u16 *)(v1 + 0x14) = *(u16 *)(v1 + 0x14) + 0x80;
    if (((s32 (*)(s32))func_8012CBF4)(a0) == 0) {
        if (func_8012D5E4(a0, (s32)D_801A3E08, (s32)(D_801A3E08 + 8), 0x10) == 0) {
            v0 = *(s32 *)(a0 + 0x1C) - 1;
            *(s32 *)(a0 + 0x1C) = v0;
            if (v0 != 0) {
                return;
            }
        }
        D_80126B96 = 0x13;
    }
    func_80180804(a0);
}



extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);
    void func_80180804(s32 param_1) {
        s32 iVar1;
        iVar1 = *(s32 *)(param_1 + 0xcc);
        ((void (*)(s32 *, s32))func_80016714)((s32 *)iVar1, 0x38);
        ((void (*)(s32))func_8012C218)(param_1);
    }


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_8018083C);

extern s32 func_8012BEE8(s32 arg);
    extern void func_801800CC(s32 arg);
    void func_801808A8(s32 arg0) {
        if (func_8012BEE8(arg0)) {
            func_801800CC(arg0);
        }
    }


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018011C(s32 a0, s32 a1, s32 a2);

void func_801808E0(s32 param_1)
{
    register s32 d __asm__("$4");
    s32 a1, a2;

    if (((s32 (*)(void))func_8012BEE8)() == 1) {
        d = param_1;
        if (*(s16 *)(param_1 + 0x70) & 0x8000) { a1 = 0x40000; a2 = 0xC0000; }
        else                                   { a1 = 0x9000;  a2 = 0x20000; }
        func_8018011C(d, a1, a2 | 0x4000);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80180228(s32*);

void func_80180944(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_80180228)(param_1);
    }
}


void func_8018099C(void) {
}

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012E504(s32 a0, s32 a1);
extern u8 D_801A3CD8;
extern u8 D_801A3D0C;
extern u8 D_801ABC88;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012CAE4(void *a0);

void func_801809A4(s32 s0) {
    extern u8 D_801A3CD8;
    extern u8 D_801A3D0C;
    extern u8 D_801ABC88;
    s32 v0;

    if (func_8012C354(s0, (s32)&D_801A3CD8) == 0) {
        return;
    }

    *(u8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xB4) = -1;
    *(s32 *)(s0 + 0xBC) = (s32)&D_801A3D0C;
    *(s32 *)(s0 + 0xC4) = 1;
    *(s16 *)(s0 + 0xAE) = 8;

    v0 = func_8012C658(0x23F, *(s16 *)(s0 + 0x70), s0);
    *(s32 *)(s0 + 0x6C) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }

    if (func_8012E504(s0, 0x23D) == 0) {
        *(s16 *)(s0 + 0xFE) = 1;
    }
    *(s16 *)(s0 + 2) = 1;
    func_8012A828(s0, &D_801ABC88);
}


extern s32 D_801A5828;
extern void func_8001C214(s32, void*);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_80180A5C(int param_1)
{
    int v0;
    int v1;
    int temp;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801A5828);
        temp = *(int *)(param_1 + 0x64);
        v1 = *(unsigned short *)(temp + 0x36);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0xFE) = 0x7FFF;
        *(short *)(param_1 + 0xFC) = v1;
    }
}



typedef struct { s16 a, b, c; } SV3x_80180ACC;          /* 6-byte, align-2 triple of s16 */
typedef struct { s16 a, b, c, d; } SV4x_80180ACC;       /* 8-byte, align-2 quad of s16 */

extern void func_8012C218(void *a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);


void func_80180ACC(void *a0) {

    extern s32 D_801ABE80;
    extern s32 D_801A3DE0;
    s32 s0 = (s32)a0;
    s32 s1;
    SV3x_80180ACC out;

    s1 = *(s32 *)(s0 + 0x64);

    if (*(s16 *)(s0 + 0xFE) == 0x7FFF) {
        *(s16 *)(s0 + 0xFE) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12);
    }

    if (*(s16 *)(s0 + 0xFC) != *(s16 *)(s1 + 0x36)) {
        func_8012C218((void *)s0);
        return;
    }

    *(SV4x_80180ACC *)(*(s32 *)(s0 + 0x20) + 0x10) = *(SV4x_80180ACC *)(*(s32 *)(s1 + 0x20) + 0x10);

    if (*(s32 *)(s1 + 0x90) != (s32)&D_801ABE80) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = *(s16 *)(s0 + 0xFE);
        *(s32 *)(s0 + 0x4) = *(s32 *)(s1 + 0x4);
        *(s32 *)(s0 + 0x8) = *(s32 *)(s1 + 0x8);
        *(s32 *)(s0 + 0xC) = *(s32 *)(s1 + 0xC);
    } else {
        func_8012F214(s1, (s32)&D_801A3DE0, (s32)&out);
        *(s16 *)(s0 + 0x6) = out.a;
        *(s16 *)(s0 + 0xA) = out.b;
        *(s16 *)(s0 + 0xE) = out.c;
    }

    *(SV4x_80180ACC *)(*(s32 *)(s0 + 0x20) + 0x18) = *(SV4x_80180ACC *)(*(s32 *)(s1 + 0x20) + 0x18);

    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = *(s16 *)(*(s32 *)(s1 + 0x20) + 0x2C);
    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x4);
}


#include "common.h"

extern s32 func_8014CB7C(void);
extern s32 func_8012BE54(s32 a0);
extern s32 func_8012B8A4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B1B4(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001C214(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012D624(s32 a0, s32 a1, s32 a2);
extern int rand(void);

extern u16 D_80126B62;
extern s16 D_80126B96;
extern u8 D_801ABF64;
extern u8 D_801ABF7C;
extern u8 D_801AC734;

void func_80180C40(s32 a0) {
    s32 i;
    s32 e;
    s32 lim;
    s16 d;

    if (func_8014CB7C() != 0) {
        if (func_8012BE54(a0) < 0x1000) {
            lim = 0x40;
            if (*(s16 *)(a0 + 0x70) != 0) {
                lim = 0x80;
            }
            d = *(u16 *)(a0 + 0xA) - D_80126B62;
            if ((d >= 0) && (d <= lim)) {
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B8A4(a0);
                *(u16 *)(a0 + 0xFC) = (rand() & 0xFF) - 0x80;
                *(u16 *)(a0 + 0xFE) = (rand() & 0xFF) - 0x80;
                *(u16 *)(a0 + 0x100) = (rand() & 0xFF) - 0x80;
                func_8012B2CC(a0);
                func_8012B1B4(a0, &D_801ABF64);
                *(s16 *)(a0 + 0x16) = -0x18;
                *(s32 *)(a0 + 0x1C) = 0x3C;
                *(s16 *)(a0 + 0x5C) = 0;
                *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
                if (*(s16 *)(a0 + 0x70) != 0) {
                    func_8012A828(a0, &D_801ABF7C);
                    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40;
                    func_8002D4C8(0xB41, 0);
                } else {
                    func_8001C214(*(s32 *)(a0 + 0x20), &D_801AC734);
                    i = 0;
                    do {
                        e = func_8012C658(0x244, 3, a0);
                        if (e != 0) {
                            s32 r = rand();
                            s32 b = *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x12) - 0x200;
                            *(u16 *)(*(s32 *)(e + 0x20) + 0x12) = b + (r & 0x3FF);
                            *(u16 *)(e + 0xFC) = (rand() & 0xFF) - 0x80;
                            *(u16 *)(e + 0xFE) = (rand() & 0xFF) - 0x80;
                            *(u16 *)(e + 0x100) = (rand() & 0xFF) - 0x80;
                            func_8012B2CC(e);
                            func_8012B1B4(e, &D_801ABF64);
                            *(s16 *)(e + 0x16) = -0x18;
                            *(s32 *)(e + 0x1C) = 0x3C;
                            func_8002D4C8(0xB42, 0);
                        }
                        i++;
                    } while (i < 3);
                }
            }
        }
    } else {
        if (*(s16 *)(a0 + 0x70) != 0) {
            if (*(u8 *)(a0 + 0x74) != 0) {
                if (func_8012D624(a0, 0x100, 0xA) != 0) {
                    D_80126B96 = 0x4007;
                }
            }
        } else {
            *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40;
            if (func_8012D624(a0, 0x18, 0xA) != 0) {
                D_80126B96 = 0x4007;
            }
            *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) + 0x40;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80180ED4);

void func_80181000(s32 arg0) {
        s32 var_v1;
        *(s8 *)(arg0 + 0xc1) = 0;
        *(s16 *)(arg0 + 0x5e) = 0;
        *(s16 *)(arg0 + 0x5c) = 0;
        *(s16 *)(arg0 + 0x102) = 3;
        var_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(var_v1 + 0x2c) |= 0x10;
    }


extern s32 func_8012C354(s32 a0, s32 a1);
extern u8 D_801ABF10[];
extern u8 D_801ABF44[];
extern u8 D_801AC6B4[];
extern u8 D_801AC734;
extern void func_8001C214(s32, void*);
extern void func_8012B23C(s32 a0);

void func_8018102C(s32 a0) {

    extern u8 D_801ABF10[];
    extern u8 D_801ABF44[];
    extern u8 D_801AC6B4[];
    extern u8 D_801AC734;
    s16 v1;

    if (func_8012C354(a0, (s32)D_801ABF10) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = 0;
    *(s32 *)(a0 + 0xC4) = 3;
    *(s32 *)(a0 + 0xBC) = (s32)D_801ABF44;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    func_8012B23C(a0);

    v1 = *(s16 *)(a0 + 0x70);
    switch (v1) {
    case 0:
        *(s16 *)(a0 + 0xAE) = -5;
        *(u8 *)(a0 + 0x75) = 0xC;
        break;
    case 1:
        *(s16 *)(a0 + 0xAE) = -1;
        *(u8 *)(a0 + 0x75) = 8;
        ((void (*)(s32, s32))func_8001C214)(*(s32 *)(a0 + 0x20), (s32)D_801AC6B4);
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 0xC00;
        break;
    case 2:
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x2) = 3;
        break;
    case 3:
        *(u16 *)(a0 + 0x5C) = 0;
        ((void (*)(s32, s32))func_8001C214)(*(s32 *)(a0 + 0x20), (s32)&D_801AC734);
        *(u16 *)(a0 + 0x2) = 2;
        break;
    }
}


extern void func_8012C218(void *a0);
extern void func_8012CBCC(s32 a0);

void func_80181164(s32 a0)
{
    s32 s0;
    s32 v0;

    s0 = a0;
    v0 = ((s32 (*)(s32))func_8012CBCC)(a0);
    if (v0 != 0) {
        *(u16 *)(s0 + 0xFC) = -*(u16 *)(s0 + 0xFC);
        *(u16 *)(s0 + 0xFE) = -*(u16 *)(s0 + 0xFE);
        *(u16 *)(s0 + 0x100) = -*(u16 *)(s0 + 0x100);
        if (v0 & 0x8000) {
            *(s32 *)(s0 + 0x10) = -*(s32 *)(s0 + 0x10);
            *(s32 *)(s0 + 0x18) = -*(s32 *)(s0 + 0x18);
        }
        if (v0 & 0x6000) {
            *(s32 *)(s0 + 0x14) = -8;
        }
    }

    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) += *(u16 *)(s0 + 0xFC);
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) += *(u16 *)(s0 + 0xFE);
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14) += *(u16 *)(s0 + 0x100);

    if (--*(s32 *)(s0 + 0x1C) < 0x10) {
        *(u32 *)(*(s32 *)(s0 + 0x20) + 4) ^= 0x80000000;
        if (*(s32 *)(s0 + 0x1C) == 0) {
            func_8012C218((void *)s0);
        }
    }
}


extern s32 D_801ABF84;
extern s8 D_801AC084[];
extern void func_800599B8(u16 *);
extern s32 rand(void);

void func_80181284(s32 arg0)
{
    s32 timer = *(s32 *)(arg0 + 0x1C);
    if (timer != 0) {
        *(s32 *)(arg0 + 0x1C) = timer - 1;
    } else {
        s32 frame = (*(u16 *)(arg0 + 0xFC) + 1) & 7;
        *(u16 *)(arg0 + 0xFC) = frame;
        if (frame == 0) {
            *(s32 *)(arg0 + 0x1C) = (rand() & 0x1F) + 0xA;
            ((void (*)(u16 *, s32))func_800599B8)((u16 *)D_801AC084, &D_801ABF84);
        } else {
            MoveImage(&D_801AC084[frame * 8], 0x2F0, 0x120);
        }
    }
}



extern void (*D_801ACA6C[])(void);

void func_80181324(void *a0) {
    D_801ACA6C[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_80181A0C(void);

void func_80181360(void *a0) {

    extern s32 D_801AC7C4[];
    extern u8 D_801AC75C[];
    extern u8 D_801850F8[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801AC75C);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801AC7C4[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80181A0C);
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
        func_8012A828((s32)a0, D_801850F8);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_80181434(void *a0) {
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


void func_8018145C(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80181464(void *a0) {

    extern s32 D_801AC9A8;
    extern s32 D_801AC994;
    extern s32 D_801AC990;
    extern s32 D_801ACA28;
    extern s32 D_801AC9BC;
    extern s32 D_801AC888[];
    extern s32 D_801AC90C[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801AC9A8 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801AC990 = 0;
                D_801AC994 = D_801AC90C[v0];
            } else {
                D_801AC994 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801AC90C[v0], 1);
                D_801AC990 = 2;
            }
        } else {
            D_801AC9A8 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801AC990 = 0;
            D_801AC994 = D_801AC888[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801AC9BC);
    } else {
        p = &D_801ACA28;
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
extern s32 func_801817B4(void);

void func_801815B0(void *arg0) {

    extern s32 D_801AC7C4[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801AC7C4[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801AC7C4[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_801817B4() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    s32 func_801816D0(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32))func_8012C218)(*(s32 *)((char *)arg0 + 0xcc));
    }


void func_801816FC(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_8018170C(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_8018171C(void *a0) {

    extern s32 D_801AC7C4[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801AC7C4[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_8018175C(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_80181790(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_801817B4(void) {

    extern s32 D_801AC7C4[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801AC7C4[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801ACA94[])(void);

void func_80181818(void *a0) {
    D_801ACA94[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80181854(void *a0) {

    extern u8 D_801AC790[];
    extern u8 D_801AD154[];
    extern u8 D_801ACF34[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801AC790) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801AD154);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801ACF34);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801818DC(void *a0) {

    extern u8 D_801ACF44[];
    extern u8 D_801AD04C[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801ACF44);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801AD04C);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_8018199C — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801AD154, else
 * D_801ACF34), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801AD154 / D_801ACF34)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_8018199C(void *a0) {

    extern u8 D_801AD154[];
    extern u8 D_801ACF34[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801AD154);
        } else {
            func_8012A828((s32)a0, D_801ACF34);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801ACA84[];
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

s32 aF8018A224() __asm__("func_80181A0C");

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

    RotTransSV(D_801ACA84, sv0, &flag);
    RotTransSV(D_801ACA84 + 8, sv1, &flag);

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


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80181B04);

void func_80181C40(s32 a0) {
    extern u8 D_801AD174[];
    extern u8 D_801AD290[];
    extern u8 D_801B5BC4[];
    s32 r;
    if (func_8012C354(a0, (s32)D_801AD174) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xBC) = (s32)D_801AD290;
        *(s32 *)(a0 + 0xB4) = -1;
        func_8012A828(a0, D_801B5BC4);
        func_80143994(a0, 0x2000);
        *(s16 *)(a0 + 0x2) = 3;
        *(s32 *)(a0 + 0xEC) = rand();
        r = rand();
        *(s32 *)(a0 + 0xF0) = (r % 32) + 0x10;
        *(s32 *)(a0 + 0xF4) = 2;
        func_8012B2CC(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80181CF0);

INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80181D38);

extern M2C_UNK D_801B5C6C;
extern void func_8012A828(s32 a0, void *a1);

void func_80181DD4(void *arg0) {
    func_8012A828((s32)arg0, &D_801B5C6C);
    *(s16 *)((char *)arg0 + 0x2) = 4;
    *(s32 *)((char *)arg0 + 0x1C) = 0x5A;
    *(s32 *)((char *)arg0 + 0xE8) = 0;
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern void func_8012ADE4(u8 *a0);
extern int rand(void);
extern u8 D_800D3918[];
extern s16 D_801152B0;

void func_80181E18(s32 a0) {
    s16 sp10[4];
    s32 c;

    if (func_8012BCCC(a0) <= 0x24000) {
        *(s16 *)(a0 + 2) = 1;
        return;
    }
    if (*(s32 *)(a0 + 0x14) == 0) {
        *(s32 *)(a0 + 0x14) = 0x100000;
    }
    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BEE8(a0)) {
            s32 r;
            s32 base;
            s32 v;
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            r = rand() % 0x400;
            base = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            if (rand() & 1) {
                v = base + r;
            } else {
                v = base - r;
            }
            *(s32 *)(a0 + 0xE4) = v;
        }
    } else {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              *(s32 *)(a0 + 0xE4), 8);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        if (func_8012BEE8(a0)) {
            *(s16 *)(a0 + 0x34) = 0;
            *(s32 *)(a0 + 0x1C) = 0x5A;
        }
    }

    func_8012B178(a0, 0xFFFC0000);
    c = ((s32 (*)(s32))func_8012CBA4)(a0);
    if ((c & 0x8000) && *(s32 *)(a0 + 0xE8) == 0) {
        s32 t1;
        sp10[0] = *(s32 *)(a0 + 0x10) >> 8;
        sp10[2] = *(s32 *)(a0 + 0x18) >> 8;
        t1 = func_8012B70C((s16 *)D_800D3918, &D_801152B0);
        *(s32 *)(a0 + 0xE4) =
            (t1 * 2 - func_8012B70C(sp10, (s16 *)D_800D3918)) & 0xFFF;
        *(s16 *)(a0 + 0x34) = 1;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s32 *)(a0 + 0xE8) = 0x10;
    } else if ((c & 0x2000) == 0) {
        func_8012ADE4((u8 *)a0);
    }
    if (*(s32 *)(a0 + 0xE8) != 0) {
        *(s32 *)(a0 + 0xE8) = *(s32 *)(a0 + 0xE8) - 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80181FFC);

#include "common.h"

/* func_80182044 — ov_SC02_041 / ov_SC02_041_jr_8017BEBC.c   MATCH (142 ins)
 *
 * §160g SIBLING-FIRST provenance (nothing derived from the .s that could be copied):
 *   - the `sp10 / sp18 / sp18 = sp10; sp18.y += K; func_80133784(1, &sp10, (s32)&sp18)`
 *     8-byte-vector block is copied VERBATIM from the banked sibling func_80189100
 *     (src/ov_SC02_027/ov_SC02_027_jr_8017D898.c:6330-6360), including the
 *     `{u16 x,y,z,w}` V8 layout (== engine_types.h:4534 V8_80189100).  align-2 + size-8
 *     is what makes gcc emit the ULW/USW block move (lwl/lwr,lwl/lwr,swl/swr,swl/swr)
 *     instead of four lhu/sh pairs, and it is what keeps the two slots at sp+0x10/sp+0x18.
 *   - the `s32 *base = &D_80126B58;` INITIALISED LOCAL is copied from the banked
 *     func_8016F1C4 (src/ov_SC06_008/ov_SC06_008_jr_8016AB6C.c:3944).  This is the whole
 *     reason $s1 gets lui/addiu %hi/%lo(D_80126B58) in the ENTRY block, ahead of every
 *     branch, and then serves 0x10/0x18/0x34 as base+offset: gcc-2.7.2 has no GCSE, so an
 *     address that is materialised before its first (conditional) use can only come from
 *     a declaration-with-initialiser.  Spelling the three reads as bare D_80126B68/70/8C
 *     globals would give three separate lui/lw pairs instead.
 *   - the `extern void func_8012A828(s32 a0, void *a1);` + bare-array-arg call form is the
 *     TU's own spelling (TU:4571/4585/4602/4631/4783/5041/5075/5116).
 *
 * SHAPE NOTES
 *   - `if (func_8012CBA4(a0) & 0x6000) {...} else {...}` — the 0x6000 arm FALLS THROUGH,
 *     and sched2 fills the beqz delay slot with the `li $v0,2` that the else-arm needs for
 *     its first D_8011F730 compare.  Inverting the test loses that.
 *   - the two `D_8011F730 == 2 / == 1` tests are spelled as two plain global reads; cse
 *     collapses them to ONE `lw $v1` because they sit on the same extended basic block.
 *   - `temp = *(s32*)(a0+0xD0); if (temp) { func_8012A828(a0,(void*)temp); ... }` — the
 *     value is loaded straight into $a1 and survives the beqz into the jal's argument.
 *
 * DECLARATION SURFACE (audited against the WHOLE destination TU, above AND below the
 * splice at TU:5211, plus ../shared/engine_core.h — that TU expands ZERO DEFINE_ macros,
 * so the header contributes no file-scope declaration here):
 *   D_80126B58   TU:55  `extern s32 D_80126B58;`                  <- AGREES verbatim
 *   D_8011F730   TU:83  `extern s32 D_8011F730;`                  <- AGREES verbatim
 *   func_8012A828 TU:4571 `extern void func_8012A828(s32 a0, void *a1);` <- AGREES verbatim
 *   func_80133784 TU:599/854 `extern s32 func_80133784(s32 a0, void *a1, s32 a2);`
 *                <- CONFORMED (the natural `void *a2` here CONFLICTS with the TU's `s32`);
 *                   the disagreement is pushed to a zero-byte cast at the use site.
 *   func_8012CBA4 / func_8012A8E8 — NOT declared in the TU; the fleet-dominant spellings
 *                (1651x `extern void func_8012CBA4(s32 a0);`, 1457x
 *                `extern void func_8012A8E8(void);`) are used with use-site casts so the
 *                body stays compatible if a DEFINE_ macro or another region is ever spliced.
 *   func_80182D80 / func_80182F20 / D_801B5D9C / D_801B61D4 / D_80126B84 — declared NOWHERE
 *                in the TU or in any src/ TU, so these spellings are free.
 *   V8_80182044 — fresh typedef name; no clash in the TU, engine_types.h or engine_core.h.
 *                (It is layout-identical to engine_types.h:4534 V8_80189100, which IS visible
 *                in this TU via engine_core.h; on banking it may be replaced by that name.)
 */

typedef struct { u16 x, y, z, w; } V8_80182044;

extern s32 D_80126B58;
extern s32 D_80126B84;

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012A8E8(void);
extern void func_8012CBA4(s32 a0);
extern void func_80182D80(s32 a0);
extern s32 func_80182F20(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

void func_80182044(s32 a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_8011F730;

    extern u8 D_801B5D9C[];
    extern u8 D_801B61D4[];
    V8_80182044 sp10;
    V8_80182044 sp18;
    s32 *base = &D_80126B58;
    s32 temp;

    if (*(u16 *)(a0 + 0x34) == 0 && D_80126B84 < -0x94000 &&
        *(s16 *)(a0 + 0x98) != 0 && *(u8 **)(a0 + 0x90) != D_801B61D4) {
        func_8012A828(a0, D_801B5D9C);
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    }
    func_80182D80(a0);
    if (((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) {
        if (base[4] == 0 && base[6] == 0) {
            if (func_80182F20(a0) == 0) {
                *(u16 *)(a0 + 0x2) = 1;
            }
        } else if (*(u8 **)(a0 + 0x90) == D_801B61D4) {
            temp = *(s32 *)(a0 + 0xD0);
            if (temp != 0) {
                func_8012A828(a0, (void *)temp);
                *(s32 *)(a0 + 0xD0) = 0;
            }
        } else if (*(s16 *)(a0 + 0x98) == 0) {
            ((void (*)(s32))func_8012A8E8)(a0);
        }
    } else if (D_8011F730 == 2) {
        *(s32 *)(a0 + 0xD0) = *(s32 *)(a0 + 0x90);
        func_8012A828(a0, D_801B61D4);
    } else if (D_8011F730 == 1) {
        if (*(s32 *)(a0 + 0xD0) == 0) {
            *(s16 *)(a0 + 0x98) = 0;
        }
    } else if (*(s16 *)(a0 + 0x98) != 0 && base[13] == 0) {
        sp10.x = *(u16 *)(a0 + 0x6);
        sp10.y = *(u16 *)(a0 + 0xA);
        sp10.z = *(u16 *)(a0 + 0xE);
        sp18 = sp10;
        sp18.y += 0x10;
        func_80133784(1, &sp10, (s32)&sp18);
        *(u16 *)(a0 + 0x6) = sp18.x;
        *(u16 *)(a0 + 0xA) = sp18.y;
        *(u16 *)(a0 + 0xE) = sp18.z;
    }
}


#include "common.h"

extern void func_8012B200(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801B5FAC[];

void func_8018227C(s32 a0) {
    func_8012B200((u8 *)a0);
    func_8012A828(a0, &D_801B5FAC);
    *(s16 *)((char *)a0 + 0x2) = 0x8;
    *(s16 *)((char *)a0 + 0x34) = 0;
}



extern void func_80182D80(s32 a0);
extern s32 func_80029DB4(void);
extern s32 func_80029E30(void);
extern s32 func_80182BAC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CBCC(s32 a0);

void func_801822C0(s32 a0) {

    extern s32 D_8011F730;
    extern u8 D_801B61D4[];
    extern s32 D_801B5E24;
    extern s32 D_801B5E8C;
    extern s32 D_801B6074;
    extern u8 D_801AD1B8[];
    extern u8 D_801AD1D8[];

    s32 state;
    s32 g;
    s32 v0;
    s32 arg0, arg1;

    func_80182D80(a0);
    state = *(u16 *)(a0 + 0x34);

    switch (state) {
    case 0:
        g = D_8011F730;
        if (g == 2) {
            *(u16 *)(a0 + 0x34) = 3;
            func_8012A828(a0, D_801B61D4);
            return;
        } else if (g == 3) {
            *(u16 *)(a0 + 0x34) = 1;
            func_8012A828(a0, &D_801B5E24);
            return;
        } else if (g == 4) {
            *(u16 *)(a0 + 0x34) = 2;
            func_8012A828(a0, &D_801B5E8C);
            return;
        }
        goto tail_short;
    case 1:
        v0 = func_80029DB4();
        func_80182BAC(a0, (s32)D_801AD1B8, 7, v0);
        arg0 = 0x1EB;
        arg1 = 0;
        break;
    case 2:
        v0 = func_80029E30();
        func_80182BAC(a0, (s32)D_801AD1D8, 6, v0);
        arg0 = 0x1EB;
        arg1 = 1;
        break;
    case 3:
        goto tail_short;
    default:
        return;
    }

    func_8012C658(arg0, arg1, a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_8012A828(a0, &D_801B6074);
    }

tail_short:
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        *(u16 *)(a0 + 0x2) = 1;
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 D_801B6394;

void func_80182444(s32 a0) {
    func_8012B23C(a0);
    func_8012A828(a0, &D_801B6394);
    *(s16 *)((char *)a0 + 0x2) = 0xA;
}


extern void func_8012CBCC(s32 a0);
    void func_80182484(s32 arg0) {
        if ((((s32 (*)(void))func_8012CBCC)() & 0x2000) != 0) {
            *(s16*)(arg0 + 0x2) = 1;
        }
    }


extern u8 D_801AD1A8[];
extern u8 D_801B628C[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);

void func_801824BC(s32 a0) {
    extern void func_8012B200(u8 *a0);
    extern void func_8012B14C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern u8 D_801AD1A8[];
    extern u8 D_801B628C[];

    s32 s0 = a0;
    s32 v0;

    func_8012B200((u8 *)a0);
    v0 = 0xD000;
    *(s32 *)(s0 + 0x48) = v0;
    func_8012B14C(s0, (s32)&D_801AD1A8);
    func_8012A828(s0, &D_801B628C);
    *(s16 *)(s0 + 0x2) = 0xC;
}


extern void func_8012CBCC(s32 a0);

void func_80182514(void *a0)
{
    s32 v1;
    s32 v0;

    v1 = *(s32 *)((s32)a0 + 0x94);
    v0 = 0xA;
    if (v1 == v0) {
        *(s32 *)((s32)a0 + 0x48) = 0;
        *(s32 *)((s32)a0 + 0x14) = 0;
    } else {
        v0 = 0x12;
        if (v1 == v0) {
            *(s32 *)((s32)a0 + 0x48) = 0x18000;
        }
    }

    if (((((s32 (*)(s32))func_8012CBCC)((s32)a0)) & 0x2000) != 0) {
        *(s16 *)((u8 *)a0 + 0x2) = 1;
    }
}



extern void func_8012A828(s32, void*);

void func_8018257C(void *arg0) {

    extern s32 D_801B5E24;
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801B5E24);
    *(s16 *)((u8 *)arg0 + 0x2) = 0xe;
}


extern s32 func_80029DB4(void);
extern s32 func_80182BAC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B23C(s32 a0);
extern s32 func_80182F20(s32 a0);

void func_801825B4(s32 p)
{
    extern s32 D_8011F730;
    extern u8 D_801AD1B8[];
    extern u8 D_801B5BC4[];

    func_80182BAC(p, (s32)D_801AD1B8, 7, func_80029DB4());
    if (*(s32 *)(p + 0x94) < 9) {
        func_8012C658(0x1EB, 0, p);
    }
    if (D_8011F730 == 3) {
        *(s16 *)(p + 2) = 0xD;
        return;
    }
    if (*(u16 *)(p + 0x72) & 0x4000) {
        func_8012A828(p, D_801B5BC4);
        *(s16 *)(p + 2) = 2;
        func_8012B23C(p);
        func_80182F20(p);
    }
}



extern void func_8012A828(s32, void*);

void func_8018266C(void *arg0) {

    extern s32 D_801B5E8C;
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801B5E8C);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x10;
}


#include "common.h"

extern s32 func_80029E30(void);
extern s32 func_80182BAC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B23C(s32 a0);
extern s32 func_80182F20(s32 a0);

void func_801826A4(void *a0) {

    extern s32 D_8011F730;
    extern u8 D_801AD1D8[];
    extern u8 D_801B5BC4[];

    s32 val;

    func_80182BAC((s32)a0, (s32)D_801AD1D8, 6, func_80029E30());
    val = *(s32 *)((s32)a0 + 0x94);
    if ((u32)(val - 4) < 10) {
        func_8012C658(0x1EB, 1, (s32)a0);
    }
    if (*(u16 *)((s32)a0 + 0x72) & 0x4000) {
        if (D_8011F730 != 4) {
            func_8012A828((s32)a0, D_801B5BC4);
            *(s16 *)((s32)a0 + 0x2) = 2;
            func_8012B23C((s32)a0);
            func_80182F20((s32)a0);
        }
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801B5F44;
    void func_80182758(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 18;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801B5F44);
    }


/*
 * func_80182784 -- ov_SC02_041 / ov_SC02_041_jr_8017BEBC.c   MATCH (124 ins)
 * Family reach x4 (zero-crack sibling family exemplar).
 *
 * WHAT IT DOES
 *   Entity per-frame step for state 6 (spawn/attach of a sub-object):
 *   (1) state == 6 -> rotate the local offset (0,0,0x20) by the entity's object matrix
 *       (obj+0x34), fetch bone/joint 7's matrix via func_8012EC04, project it through
 *       func_8012F14C with the shared D_800D3918 offset vector, then build a 0x14-byte
 *       spawn record {pos.xyz, id=0x1FA, 0, 0, 0x7FFF, gfxid=obj->0x12, 0} and hand it to
 *       func_8012C51C; on success cache the child at +0xCC, swap the object's anim
 *       (func_8001C924 D_801AF8D0), push the entity to script D_801AD280 and set flag 1.
 *   (2) once flags 1|2 are both set and func_80013350(entity+4, child+4) < 0x1801
 *       (distance gate), free the child, restore anim D_801AF898, push script D_801B5F44,
 *       state = 7, clear the child ptr and flags 0|1.
 *   (3) if the current script IS D_801B5F44 and entity flag 0x4000 at +0x72 is set,
 *       push script D_801B5BC4, sub-state = 2, func_8012B23C + func_80182F20.
 *
 * SIBLING-FIRST provenance (STEP 0 / cookbook 160g -- all of it from the DESTINATION TU):
 *   - the 0x14-byte spawn record IS `struct S80190C84` (engine_types.h:1337), lifted from
 *     the TU's own banked func_80184D20 (TU:5537-5566), which builds the same record
 *     (f6 = id, f8 = fA = 0, fC = 0x7FFF, fE = gfx, f10 = 0) and calls func_8012C51C(&sp, a0).
 *   - `s32 buf[8]` + `func_8012EC04(p, n, buf)` + `func_8012F14C(buf, <vec>, out)` is the
 *     TU's banked func_80184C60 (TU:6372-6383) verbatim, including the cast-call spelling
 *     that keeps the TU's `(s32,s32,s32)` prototype for func_8012F14C.
 *   - `ApplyMatrixSV((void *)(*(s32 *)(a0 + 0x20) + 0x34), v, v)` is engine_core.h
 *     DEFINE_func_80168070() (engine_core.h:21265) verbatim.
 *   - the `&D_801B5F44` script-pointer compare uses the TU's own `extern short D_801B5F44;`
 *     (TU:5537) -- taking its address, NOT re-spelling it as an array.
 *
 * IDIOMS THAT ARE LOAD-BEARING (byte-measured this session)
 *   1. The 0xE0 flag gate MUST be three NESTED ifs, not `(f&1) && (f&2) && ...`.
 *      The C front end's fold_truthop rewrites the `&&` of two bit tests on the same
 *      operand into `(f & 3) == 3` -- one `andi 3` + `bne v0,v1` instead of the target's
 *      `andi 1 / beqz / andi 2 / beqz`.  Nesting is not an && expression, so fold never
 *      sees it; cse still collapses the two `lw 0xE0` into one, which is what the target
 *      does.  (-2 ins / 52 diffs in v1.)  NEW LAW candidate -- see notes.
 *   2. `sv[1] = 0; sv[0] = 0; sv[2] = 0x20;` -- the 1-before-0 order is real source order,
 *      not scheduling; 0,1,2 emits `sh 0x50` before `sh 0x52`.
 *   3. `u16 out[4]` / `u16 sv[4]` (NOT s16): the target loads every component with `lhu`.
 *      s16 arrays give `lh` on all five reads.  Same for `*(u16 *)(obj + 0x12)`.
 *   4. Local declaration order struct -> buf -> out -> sv reproduces the frame exactly
 *      (0x10 / 0x28 / 0x48 / 0x50).  The 4-byte hole at sp+0x24 is not a missing local:
 *      assign_stack_local gives every BLKmode local BIGGEST_ALIGNMENT (8) on MIPS, so the
 *      0x14-byte struct rounds 0x24 -> 0x28 for buf.
 *   5. `temp = func_8012C51C(...); *(s32*)(a0+0xCC) = temp; if (temp != 0)` -- the store
 *      lands in the beqz delay slot (cookbook 162: non-void return visible in delay slots).
 *
 * DECLARATION SURFACE (audited against the WHOLE destination TU; it expands ZERO DEFINE_
 * macros, so engine_core.h contributes no file-scope declaration):
 *   ApplyMatrixSV  TU:170   `extern void ApplyMatrixSV(void*,void*,void*);`   <- AGREES verbatim
 *   func_8012F14C  TU:330   `extern void func_8012F14C(s32,s32,s32);`         <- AGREES verbatim
 *   func_8012EC04  TU:6369  `extern void func_8012EC04(s32,s32,s32*);`        <- AGREES verbatim
 *   func_8012C51C  TU:6410  `extern s32 func_8012C51C(void*,s32);`            <- AGREES verbatim
 *   func_8012C218  TU:5092  `extern void func_8012C218(void *a0);`            <- AGREES verbatim
 *   func_8012A828  TU:4738  `extern void func_8012A828(s32 a0, void *a1);`    <- AGREES verbatim
 *   func_80182F20  TU:5438  `extern s32 func_80182F20(s32 a0);`               <- AGREES verbatim
 *   D_800D3918     TU:634   `extern u8 D_800D3918[];`                         <- AGREES verbatim
 *   D_801B5F44     TU:5537  `extern short D_801B5F44;`                        <- AGREES verbatim
 *   func_8012B23C  not in the TU; fleet-dominant spelling (1576x) used verbatim.
 *   func_8001C924  not in the TU; fleet-dominant spelling (70x) used verbatim.
 *   func_80013350  not in the TU.  The fleet-dominant spelling is `extern void
 *                  func_80013350(s32, void*);` (1379x) but this call site NEEDS the s32
 *                  return (`slti $v0,$v0,0x1801`), so `extern s32 func_80013350(s32 a0,
 *                  void *a1);` is used.  No conflict in THIS TU -- but if a later splice
 *                  ever drops a `void` spelling into it, keep this one and cast at the
 *                  use site.
 *   D_801AF8D0 / D_801AD280 / D_801AF898 / D_801B5BC4 -- declared NOWHERE in the TU
 *                  (D_801B5BC4 exists only in ov_SC05_001, a different overlay), so the
 *                  block-scope spellings here are free.
 *   St_80182784 -- fresh typedef name, zero hits across src/ and include/.  It is
 *                  layout-identical to `struct S80190C84` (engine_types.h:1337), which IS
 *                  visible in the TU via ../shared/engine_core.h; on banking it SHOULD be
 *                  replaced by `struct S80190C84 s;` and the typedef dropped (byte-neutral
 *                  -- the local tag exists only so the standalone match_one compile works,
 *                  since engine_core.h is not on its -I path).
 */

#include "common.h"

/* Layout-identical to `struct S80190C84` (src/shared/engine_types.h:1337), which IS
 * visible in the destination TU via ../shared/engine_core.h; a fresh tag is used here
 * only so the standalone match_one compile (no engine_core.h on its -I path) works. */
typedef struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } St_80182784;

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 func_80013350(s32 a0, void *a1);
extern void func_8001C924(s32 a0, void *a1);
extern s32 func_80182F20(s32 a0);
extern u8 D_800D3918[];
extern short D_801B5F44;

void func_80182784(s32 a0) {

    extern u8 D_801AF8D0[];
    extern u8 D_801AD280[];
    extern u8 D_801AF898[];
    extern u8 D_801B5BC4[];
    St_80182784 s;
    s32 buf[8];
    u16 out[4];
    u16 sv[4];
    s32 temp;

    if (*(s32 *)(a0 + 0x94) == 6) {
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0x20;
        ApplyMatrixSV((void *)(*(s32 *)(a0 + 0x20) + 0x34), sv, sv);
        func_8012EC04(a0, 7, buf);
        ((void (*)(s32 *, u8 *, u16 *))func_8012F14C)(buf, D_800D3918, out);
        s.f0 = out[0] + sv[0];
        s.f2 = out[1];
        s.f4 = out[2] + sv[2];
        s.f6 = 0x1FA;
        s.f8 = 0;
        s.fA = 0;
        s.fC = 0x7FFF;
        s.fE = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        s.f10 = 0;
        temp = func_8012C51C(&s, a0);
        *(s32 *)(a0 + 0xCC) = temp;
        if (temp != 0) {
            func_8001C924(*(s32 *)(a0 + 0x20), D_801AF8D0);
            func_8012A828(a0, D_801AD280);
            *(s32 *)(a0 + 0xE0) |= 1;
        }
    }
    if (*(s32 *)(a0 + 0xE0) & 1) {
        if (*(s32 *)(a0 + 0xE0) & 2) {
            if (func_80013350(a0 + 4, (void *)(*(s32 *)(a0 + 0xCC) + 4)) < 0x1801) {
                func_8012C218(*(void **)(a0 + 0xCC));
                func_8001C924(*(s32 *)(a0 + 0x20), D_801AF898);
                func_8012A828(a0, &D_801B5F44);
                *(s32 *)(a0 + 0x94) = 7;
                *(s32 *)(a0 + 0xCC) = 0;
                *(s32 *)(a0 + 0xE0) &= ~3;
            }
        }
    }
    if (*(s32 *)(a0 + 0x90) == (s32)&D_801B5F44 && (*(u16 *)(a0 + 0x72) & 0x4000)) {
        func_8012A828(a0, D_801B5BC4);
        *(s16 *)(a0 + 0x2) = 2;
        func_8012B23C(a0);
        func_80182F20(a0);
    }
}


void func_80182974(s32 a0) {
    extern short D_801B64FC;
    *(s16 *)(a0 + 2) = 0x14;
    func_8012A828(a0, &D_801B64FC);
    func_8012B23C(a0);
}


extern s32 D_801B5BC4;
extern s32 func_80182F20(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBCC(s32 a0);

void func_801829B4(s32 a0) {
    func_8012CBCC(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_8012A828(a0, ((u8 *)&D_801B5BC4));
        *(s16 *)(a0 + 2) = 2;
        func_8012B23C(a0);
        func_80182F20(a0);
    }
}


extern void func_80182A54(s32 arg0);
extern void func_8012A828(s32, void*);
extern M2C_UNK D_801B5BC4;

void func_80182A18(void *arg0) {
    func_80182A54((s32)arg0);
    ((void (*)(s32 *, s32 *))func_8012A828)((s32)arg0, &D_801B5BC4);
    *(s16 *)((char *)arg0 + 0x98) = 0;
}


extern void func_8001C924(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_80182B38(s32 a0);
extern u8 D_801AF898[];

void func_80182A54(s32 a0) {
    if (*(s32 *)(a0 + 0xE0) & 1) {
        func_8001C924(*(s32 *)(a0 + 0x20), D_801AF898);
        if (*(s32 *)(a0 + 0xCC) != 0) {
            func_8012C218((void *)*(s32 *)(a0 + 0xCC));
            *(s32 *)(a0 + 0xCC) = 0;
        }
        *(s32 *)(a0 + 0xE0) &= ~3;
    }
    func_80182B38(a0);
}


void func_80182AD4(s32 arg0) {
    u16 temp;

    if (*(s32 *)(arg0 + 0xC4) & 4) {
        *(s16 *)(arg0 + 2) = 0x13;
    } else {
        *(s16 *)(arg0 + 2) = 1;
    }
    temp = *(u16 *)(*(s32 *)(arg0 + 0x78) + 2);
    *(s32 *)(arg0 + 0xE0) = 0;
    *(s16 *)(arg0 + 0x5C) = temp;
}


extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);

void func_80182B08(s32 arg0) {
    ((void (*)(void))func_8002A04C)();
    ((s32 (*)(s32))func_8012C098)(arg0);
}


extern void func_80183D78(s32 a0, void *a1, s32 a2);
extern void func_80183FE0(s32 a0, s32 a1, s32 a2);
extern u8 D_801AD1B8[];
extern u8 D_801AD1D8[];

void func_80182B38(s32 a0) {
    s32 t = *(s32 *)(a0 + 0xF4);
    if (t != 0) {
        *(s32 *)(a0 + 0xF4) = t - 1;
        return;
    }
    if ((*(u32 *)(a0 + 0xE0) & 1) == 0) {
        func_80183D78(a0, (void *)D_801AD1B8, 7);
    }
    func_80183FE0(a0, (s32)D_801AD1D8, 6);
}



/* Local twin used as the shape reference: func_801862F0 (this very TU, already MATCHED,
 * lines 6969-6988): same D_80126B78/D_80126B90/D_801152A8 globals, same
 * func_8012F14C / func_80135888 / func_8012F568 call chain. */

typedef struct { short vx, vy, vz, pad; } SVec_801861D0_80182BAC;

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_80182BAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern s32 *D_80126B90;
    s32 buf1[8];
    SVec_801861D0_80182BAC vecA;
    SVec_801861D0_80182BAC vecB;
    SVec_801861D0_80182BAC vecC;

    func_8012EC04(arg0, arg2, buf1);
    func_8012F14C((s32)buf1, arg1, (s32)&vecA);
    func_8012F14C((s32)buf1, arg1 + 8, (s32)&vecB);
    func_8012F14C((s32)buf1, arg1 + 0x10, (s32)&vecC);
    *(SVec_801861D0_80182BAC *)(arg0 + 0xFC) = vecC;
    *(SVec_801861D0_80182BAC *)(arg0 + 0x104) = vecB;
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&vecA, (s32)&vecB) != 0) {
        func_8012F568(1, 1, 0, arg3, (s32)&vecB, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


#include "common.h"

extern s32 *D_80126B78;
extern u8 D_801AD36C[];
extern u8 D_801152A8[];

extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_80182CCC(s32 arg0) {
    s32 buf1[2];
    s32 buf2[2];

    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)D_801AD36C, (s32)buf1);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)(D_801AD36C + 8), (s32)buf2);
    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58), (s32)buf1, (s32)buf2) != 0) {
        func_8012F568(1, 0x18, *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), 0x18, (s32)buf2, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


/* func_80182D80 -- ov_SC02_041, TU ov_SC02_041_jr_8017BEBC.c
 * Family reach x4 (zero-crack exemplar): func_80182D80 (ov_SC02_041) plus siblings in
 * ov_SC04_002 / ov_SC04_005 / ov_SC04_007 (all `*_jr_8017BEBC`, all still INCLUDE_ASM).
 *
 * STEP 0 / cookbook 160g -- all of this is derived from the DESTINATION TU itself:
 *   - `s32 *base = &D_80126B58;` computed unconditionally in the entry block, ahead of
 *     every branch -- the SAME idiom documented at TU:5624-5630 (func_80182044) and
 *     TU:5665-5690, where D_80126B58's own fields are read at 0x10/0x18/0x20/0x34 via
 *     `base[N]` index arithmetic (N*4 == the byte offset) rather than bare globals.
 *     Confirmed here: base[4] (== +0x10) is the SAME memory as the bare global
 *     `D_80126B68` used at the top of this very function -- the `addiu $a1,$s3,0x10`
 *     relocation (base-relative) is what forces the `base[4]`-style spelling instead of
 *     `&D_80126B68` (a bare symbol reference would emit its own lui/addiu pair, not an
 *     offset off $s3).
 *   - the `t1 = func_8012B70C(D_800D3918, &v); result = (t1*2 - func_8012B70C(&v2,
 *     D_800D3918)) & 0xFFF;` shape is the TU's own idiom at TU:5593-5598
 *     (func_80181E18), reused verbatim (both callee orderings match: first call is
 *     (D_800D3918, X), second is (Y, D_800D3918), and D_800D3918's address is CSE'd into
 *     one saved register across both calls, exactly like the exemplar).
 *   - `func_80049CAC((s32)&rot, (s32)&m); func_800484EC((s32)&m, (s32)&v, a2);` is the
 *     TU's own idiom at TU:3412-3413 (func_8017D7C0): func_80049CAC(SVECTOR*, MATRIX*)
 *     builds a rotation matrix from an angle triple; func_800484EC(MATRIX*, Vec32*,
 *     Vec32*) applies it.  Local SV_/MTX_/V32_ typedefs copied from that function
 *     (TU:3333-3335) since engine_core.h's real SVECTOR/MATRIX/Vec32 are not visible to
 *     match_one's standalone -Iinclude-only compile.
 *   - `func_801726B8(s32 *a0)` is TU:2224's own agreed extern; DEFINE_func_801726B8()
 *     (engine_core.h) shows it as `return *(s32*)(a0+0x1F4) & 0x100;` -- a flag test.
 *
 * DECLARATION SURFACE (audited against the whole destination TU):
 *   D_80126B58    TU:55   `extern s32 D_80126B58;`                    <- AGREES verbatim
 *   D_800D3918    TU:634  `extern u8 D_800D3918[];`                   <- AGREES verbatim
 *   D_80126B5E    TU:1790 `extern u16 D_80126B5E;`                    <- AGREES verbatim
 *   D_80126B66    TU:1792 `extern u16 D_80126B66;`                    <- AGREES verbatim
 *   VectorNormalSS TU:1848 `extern s32 VectorNormalSS(void *a0, void *a1);` <- AGREES verbatim
 *   func_8012B70C  TU:5546 `extern s32 func_8012B70C(s16 *a0, s16 *a1);` <- AGREES verbatim
 *   func_80149CD4  TU:381  `extern s32 func_80149CD4(s32 a0);`         <- AGREES verbatim
 *   func_80049CAC  TU:2643/3362 `extern void func_80049CAC(s32 a0, s32 a1);` <- AGREES verbatim
 *   func_800484EC  TU:242/3363 `extern void func_800484EC(s32 a0, s32 a1, s32 a2);` <- AGREES verbatim
 *   func_801726B8  TU:2224 `extern s32 func_801726B8(s32 *a0);`        <- AGREES verbatim
 *   D_80126B68 / D_80126B70 -- not declared anywhere else in the TU; used here as bare
 *     s32 globals (the entry-block gate reads) AND, via `base[4]`/`base[6]`, as offsets
 *     off the same D_80126B58 struct (see above) -- both spellings needed, no conflict.
 *
 * This host TU is inside the destination TU itself (jr_8017BEBC), where
 * `extern void func_80182D80(s32 a0);` is already forward-declared (TU:5672) and called
 * (TU:5690) by the already-matched func_80182044 -- confirming the agreed signature.
 */

typedef struct { short vx, vy, vz, pad; } SV_80182D80;   /*  8 bytes, align 2 */
typedef struct { short m[3][3]; long t[3]; } MTX_80182D80; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_80182D80;  /* 16 bytes, align 4 */

extern s32 D_80126B58;
extern s32 D_80126B68;
extern s32 D_80126B70;
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u8 D_800D3918[];

extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_80149CD4(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_801726B8(s32 *a0);

void func_80182D80(s32 a0) {
    s32 *base = &D_80126B58;
    s32 s1;
    SV_80182D80 v1;   /* also reused below as the angle-delta ("delta") vector */
    SV_80182D80 v2;
    V32_80182D80 ref;
    MTX_80182D80 m;

    if (D_80126B68 != 0 || D_80126B70 != 0) {
        s32 t1;

        v1.vx = *(u16 *)(a0 + 0x6) - D_80126B5E;
        v1.vy = 0;
        v1.vz = *(u16 *)(a0 + 0xE) - D_80126B66;
        VectorNormalSS(&v1, &v1);

        v2.vy = 0;
        v2.vx = D_80126B68 >> 8;
        v2.vz = D_80126B70 >> 8;

        t1 = func_8012B70C((s16 *)D_800D3918, (s16 *)&v1);
        s1 = (t1 * 2 - func_8012B70C((s16 *)&v2, (s16 *)D_800D3918)) & 0xFFF;
    } else {
        s1 = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    }

    if (func_80149CD4((s32)base) != 0) {
        v1.vz = 0;
        v1.vx = 0;
        v1.vy = s1;

        ref.vy = 0;
        ref.vx = 0;
        ref.vz = (s32)0xFFFC0000;

        func_80049CAC((s32)&v1, (s32)&m);
        func_800484EC((s32)&m, (s32)&ref, a0 + 0x10);
    } else {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = s1;

        v1.vz = 0;
        v1.vx = 0;
        v1.vy = s1 - *(u16 *)(base[8] + 0x12);

        func_80049CAC((s32)&v1, (s32)&m);
        func_800484EC((s32)&m, (s32)(base + 4), a0 + 0x10);
    }

    if (func_801726B8(base)) {
        *(s32 *)(a0 + 0x14) = 0x100000;
    } else {
        *(s32 *)(a0 + 0x14) = base[13];
    }
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80182F20);

INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_80183014);

extern s32 func_80132EF4(s32 a0, s32 a1);
typedef struct { short a, b, c; } SV3_80181D44_8018317C;   /* == the TU's own `SV3` (engine_types.h:612); renamed only because

extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);
/* func_801832F8 is the NEXT stub in this same TU (INCLUDE_ASM at the line below
 * func_8018317C's).  Its own .s takes TWO args ($a0 = entity-owner, $a1 = id):
 * do NOT adopt the 1-arg `void f(void*)` spelling that the *unrelated* overlay
 * ov_SC03_001 uses for its own different function at the same address. */
extern void func_801832F8(s32 a0, s32 a1);

/* Spawn a 0x4F entity for `a0`, then jitter its three s16 fields at +0x6/+0xA/+0xE
 * by a random amount (mod 28 / 32 / 28, sign picked by a second rand()), flip the
 * substruct at *(s32*)(entity+0x20) fields 0x18/0x1A/0x1C to +/-0x2000, and notify. */
s32 func_8018317C(s32 a0) {
    s32 s2;

    s2 = func_80132EF4(a0, 0x4F);
    if (s2 == 0) {
        return 0;
    }

    *(s16 *)(s2 + 0xA) = *(u16 *)(s2 + 0xA) - 0x28;

    /* NOTE (this is the whole match, do not "tidy" it): each block MUST own its
     * own r/val/base locals.  With one shared `r` across all three blocks, the
     * /32 block's remainder pseudo conflicts with the rand()-result pseudo, so
     * global.c's expand_preferences() cannot merge their preferences (it needs
     * a non-conflicting REG_DEAD copy).  The result pseudo then has NO hard-reg
     * preference of its own, prune_preferences() puts $v1 into its
     * regs_someone_prefers set, and find_reg's pass 0 skips $v1 and lands the
     * value in $a0 instead of the target's $v1 (4 wrong instructions). */
    {
        s32 r, val, base;
        r = rand() % 28;
        base = *(s16 *)(s2 + 0x6);
        val = (rand() & 1) ? (base + r) : (base - r);
        *(s16 *)(s2 + 0x6) = val;
    }
    {
        s32 r, val, base;
        r = rand() % 32;
        base = *(s16 *)(s2 + 0xA);
        val = (rand() & 1) ? (base + r) : (base - r);
        *(s16 *)(s2 + 0xA) = val;
    }
    {
        s32 r, val, base;
        r = rand() % 28;
        base = *(s16 *)(s2 + 0xE);
        val = (rand() & 1) ? (base + r) : (base - r);
        *(s16 *)(s2 + 0xE) = val;
    }

    {
        s32 v0, v1;

        if (rand() & 1) {
            v1 = *(s32 *)(s2 + 0x20);
            v0 = -0x2000;
            *(s16 *)(v1 + 0x1C) = v0;
        } else {
            v1 = *(s32 *)(s2 + 0x20);
            v0 = 0x2000;
            *(s16 *)(v1 + 0x1C) = v0;
        }
        *(s16 *)(v1 + 0x1A) = v0;
        *(s16 *)(v1 + 0x18) = v0;
    }

    /* Zero-byte scheduling fence (§190-C).  Without it BOTH sched1 and sched2
     * independently hoist the call's `move $a0,$s3` + `li $a1,0x7F3` above the
     * two trailing `sh` stores (they feed the jal, so they carry the higher
     * INSN_PRIORITY), and reorg then fills the delay slot with `sh 0x18`
     * instead of the target's `addiu $a1`.  -fno-schedule-insns{,2} alone does
     * not reproduce the target order -- only both together do, hence a real
     * barrier rather than a statement reorder. */
    __asm__ __volatile__("" ::: "memory");
    func_801832F8(a0, 0x7F3);
    return s2;
}


INCLUDE_ASM("asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC", func_801832F8);


extern void (*D_801AD37C[])(void);

void func_801834B4(void *a0) {
    D_801AD37C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801834F0(s32 a0) {
    *(s16 *)(a0 + 0xDC)  = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFC);
    *(s16 *)(a0 + 0xDE)  = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE);
    *(s16 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x100);
    *(s16 *)(a0 + 0xE4) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x104);
    *(s16 *)(a0 + 0xE6) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x106);
    *(s16 *)(a0 + 0xE8) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x108);

    (*(s16 *)(a0 + 0x2))++;
}


void func_8018354C(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


#include "common.h"

/* func_80183560 — ov_SC02_041, TU ov_SC02_041_jr_8017BEBC.c (132 ins).
 *
 * Family of 4 (zero-crack exemplar): func_80183560 (ov_SC02_041) / func_80186B84 (ov_SC04_002) /
 * func_80185F54 (ov_SC04_005) / func_801825C0 (ov_SC04_007) — all four `asm/.../jr_8017BEBC`,
 * all 141-line .s, all still INCLUDE_ASM.
 *
 * Per-frame step of an entity's ground marker.  a0+0x64 is the owner entity; the two SVECTORs at
 * +0xFC and +0x104 are copied from it (vx,vy,vz only — the +0x102/+0x10A pad words are NOT copied,
 * which is why this is six scalar assignments and not two struct copies).  The marker's own two
 * SVECTORs at +0xEC and +0xF4 are then set to the midpoints of (+0xFC,+0xDC) and (+0x104,+0xE4);
 * +0xEC -= +0xF4 turns the first into the edge vector, VectorNormalSS normalises it in place, and
 * the result is divided by the speed taken from the 2-entry s16 table D_801AD38C (0x0074/0x003C,
 * asm/ov_SC02_041/data/tail.data.s:46622) indexed by the low nibble of the u16 at +0x70, then added
 * back onto +0xF4 to give the advanced position.  +0x1C = 0x10 is the colour/intensity that
 * func_801837B0 (same TU, already matched) reads, and the u16 at +0x2 is the state counter.
 *
 * DECLARATION SURFACE (whole-TU grep of ov_SC02_041_jr_8017BEBC.c, §161c):
 *   * VectorNormalSS — TU line 1848 `extern s32 VectorNormalSS(void *a0, void *a1);`.  The decl
 *     below is CHARACTER-IDENTICAL, so it is a legal repeat, not a conflict.
 *   * D_801AD38C — not declared anywhere in ov_SC02_041; the TU's nearest neighbour is
 *     `extern void (*D_801AD37C[])(void);` at line 5604, a DIFFERENT symbol (the func_801834B4
 *     dispatch table).  `extern s16 D_801AD38C[]` is new and conflict-free.  It must stay `s16`:
 *     the target reads it with `lh`, and an `s16` LOCAL would instead give lhu+sll+sra (see below).
 *   * func_80183560 itself has no prototype anywhere in the overlay — only the INCLUDE_ASM at
 *     line 5618 that this definition replaces.
 *
 * CODEGEN NOTES (what the .s pins — every one of these was byte-measured):
 *   * `d` MUST be s32, not s16.  An `s16 d` is HImode: gcc loads the table entry with the movhi
 *     pattern (`lhu`) and then sign-extends at the division with `sll 16; sra 16` — two extra
 *     instructions and 134 ins total.  An s32 local makes the load a plain
 *     `(sign_extend:SI (mem:HI ...))` = the target's single `lh`.
 *   * The owner pointer is re-read from a0+0x64 for EVERY one of the six copies (six `lw`s in the
 *     target).  Caching it in a local collapses them to one load.
 *   * The reads are all `s16`: the `sra $v0,$v0,1` in the averaging block needs the signed sum, and
 *     the `lhu`s elsewhere are combine's own force_to_mode rewrite of a dead-high-half sign_extend
 *     — do NOT chase them with `u16` casts in the source.
 *   * >>> THE WHOLE FUNCTION TURNS ON `(*(s16 *)(a0 + 0x2))++;` <<<  Spelled `+= 1` instead, the
 *     draft is 132/132 instructions with the SAME multiset but 25 mismatched: the three div
 *     quotients come out $a0/$a1/$a2 instead of $a1/$a2/$a3 and the tail block schedules
 *     add/store/add/store instead of add,add,add,store,store,store.  `x += 1` on a memory lvalue
 *     expands to one read-modify-write chain; postincrement expands via an explicit temp
 *     (`t = *p; *p = t + 1;`), which is one more RTL insn on that chain.  That extra insn changes
 *     the dependence depth the pre-RA scheduler ranks by, so the 0x2 load is hoisted above the
 *     `0x1C = 0x10` store, its value and the 0x10 constant become simultaneously live, and the
 *     resulting pressure pushes the whole tail onto the target's registers.  `(*p)++` and
 *     `t = *p + 1; *p = t;` both match; `+= 1`, `*p = *p + 1` and `t = *p; *p = t + 1;` do not.
 */

extern s32 VectorNormalSS(void *a0, void *a1);
extern s16 D_801AD38C[];

void func_80183560(s32 a0) {
    s16 *v;
    s32 d;

    *(s16 *)(a0 + 0xFC)  = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFC);
    *(s16 *)(a0 + 0xFE)  = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE);
    *(s16 *)(a0 + 0x100) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x100);
    *(s16 *)(a0 + 0x104) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x104);
    *(s16 *)(a0 + 0x106) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x106);
    *(s16 *)(a0 + 0x108) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x108);

    *(s16 *)(a0 + 0xEC) = (*(s16 *)(a0 + 0xFC)  + *(s16 *)(a0 + 0xDC)) >> 1;
    *(s16 *)(a0 + 0xEE) = (*(s16 *)(a0 + 0xFE)  + *(s16 *)(a0 + 0xDE)) >> 1;
    *(s16 *)(a0 + 0xF0) = (*(s16 *)(a0 + 0x100) + *(s16 *)(a0 + 0xE0)) >> 1;
    *(s16 *)(a0 + 0xF4) = (*(s16 *)(a0 + 0x104) + *(s16 *)(a0 + 0xE4)) >> 1;
    *(s16 *)(a0 + 0xF6) = (*(s16 *)(a0 + 0x106) + *(s16 *)(a0 + 0xE6)) >> 1;
    *(s16 *)(a0 + 0xF8) = (*(s16 *)(a0 + 0x108) + *(s16 *)(a0 + 0xE8)) >> 1;

    *(s16 *)(a0 + 0xEC) = *(s16 *)(a0 + 0xEC) - *(s16 *)(a0 + 0xF4);
    *(s16 *)(a0 + 0xEE) = *(s16 *)(a0 + 0xEE) - *(s16 *)(a0 + 0xF6);
    *(s16 *)(a0 + 0xF0) = *(s16 *)(a0 + 0xF0) - *(s16 *)(a0 + 0xF8);

    v = (s16 *)(a0 + 0xEC);
    VectorNormalSS(v, v);

    d = D_801AD38C[*(u16 *)(a0 + 0x70) & 0xF];

    *(s32 *)(a0 + 0x1C) = 0x10;
    (*(s16 *)(a0 + 0x2))++;

    *(s16 *)(a0 + 0xEC) = *(s16 *)(a0 + 0xF4) + *(s16 *)(a0 + 0xEC) / d;
    *(s16 *)(a0 + 0xEE) = *(s16 *)(a0 + 0xF6) + *(s16 *)(a0 + 0xEE) / d;
    *(s16 *)(a0 + 0xF0) = *(s16 *)(a0 + 0xF8) + *(s16 *)(a0 + 0xF0) / d;
}


extern void func_801837B0(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void*);
void func_80183770(s32 a0) {
    func_801837B0(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C218)(a0);
    }
}


/* func_801837B0 — ov_SC02_041, TU ov_SC02_041_jr_8017BEBC.c.
 *
 * Family of 4 (824 templatable ins): func_801837B0 / func_80186DD4 (ov_SC04_002) /
 * func_801861A4 (ov_SC04_005) / func_80182810 (ov_SC04_007).
 *
 * Draws the two triangles of an entity's ground marker: builds a 4-vertex gouraud packet on
 * the stack (verts 0x10, colours 0x30, code 0x40), whose colour ramp is derived from the s32
 * at a0+0x1C (*15, then >>1 for the second component, then -0x10 clamped-at-0 for the far
 * pair).  Bit 0 of the u16 at a0+0x70 picks which channel carries the bright value.  Then the
 * camera matrix cached at D_800AF630+0x18 is loaded and two rtpt+rtps+avsz4 groups run over a
 * sliding window of the SVECTORs at a0+0xDC..0x104 (stride 8), queueing the packet through
 * func_80017714 whenever the GTE flag masked with ~0x1000 is clear.
 *
 * DECLARATION SURFACE (whole-TU one-pass grep, D2):
 *   * D_800AF630   — TU line 53   `extern u8 D_800AF630[];`      (identical extern repeated, legal)
 *   * func_80017714— TU line 4324 `extern void func_80017714(void *);` (identical extern repeated)
 *   * func_801837B0— TU line 5235 `extern void func_801837B0(s32 a0);` — the definition below
 *     uses that exact prototype, so no SELF-axis rename is needed.
 *   * every type tag and every gte_ macro carries the _801837B0 suffix: this TU already defines
 *     gte_ldv0 twice (lines 2687 and 4332, different bodies) and gte_SetRotMatrix at 5033, all
 *     ABOVE the splice point at 5246, so unsuffixed names would collide/redefine.
 *
 * CODEGEN NOTES (what the .s pins):
 *   * ONE aggregate `pkt` holds verts + colours + code.  The code word MUST live inside the
 *     object handed to func_80017714 or gcc dead-stores it (a separate `s32 tag` local is
 *     eliminated and the frame comes out 8 short: 0x80 instead of 0x88).
 *   * `c` is s16 but `d` is s32 — that asymmetry IS in the target: after the -0x10 the `c < 0`
 *     test needs `sll $v1,$v1,16; bgez` (HImode) while the `d < 0` test is a bare `bgez $a3`
 *     (an `sra` by 17 already leaves 18 sign bits, so no re-extension is emitted).
 *   * `p`/`q` are a SECOND pair of s16 locals holding the value actually stored.  They produce
 *     the `addu $a1,$v1,$zero` / `addu $a2,$a3,$zero` copies in the head and after each -0x10,
 *     and they occupy $a1/$a2 — which is what pushes the D_800AF630 base out to $t0 and the
 *     reload register out to $t1, exactly as the target has them.  `q` must be s16, not s32: an
 *     s32 `q` is copy-propagated into `d` and the three `addu $a2,...` copies vanish.
 *   * The colour writes are CHAINED assignments; gcc expands `A = B = C = D = q` innermost-first,
 *     so the store order is D,C,B,A and exactly one QImode conversion temp is materialised per
 *     chain ($a0 for the first, $v0 reused for the rest).
 *   * The -0x10 on the second channel goes through a BLOCK-SCOPED `s32 e`, not `d -= 0x10`.
 *     Two separate effects, both required:
 *       - splitting `d` into `d` + `e` cuts REG_N_REFS(d) from 10 to 4, which drops d below p
 *         and q in global.c's allocno priority.  With `d -= 0x10` the ranking is d,c,p,q and the
 *         three registers come out permuted ($a1/$a2/$a3 = d/p/q instead of p/q/d) — §137.
 *       - scoping `e` INSIDE each arm (one pseudo per arm instead of one shared) is what fixes
 *         the last residual: a function-scope `e` leaves `addiu $a3,$a3,-0x10` scheduled one slot
 *         too early, ahead of the `addu $v0,$a2,$zero` chain temp.  That reorder was INVARIANT
 *         under every legal statement permutation (8 tried), i.e. it was never a source-order
 *         problem — it is the allocno/live-range split.
 */

extern u8 D_800AF630[];
extern void func_80017714(void *);

   /* 8 bytes */
        /* 4 bytes */

          /* 0x38 */

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

void func_801837B0(s32 a0)
{
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


extern void (*D_801AD390[])(void);
extern u8 D_801AD1B8[];
extern void func_80183D78(s32 a0, void *a1, s32 a2);

void func_80183AE8(void *a0) {
    D_801AD390[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_80183D78((s32)a0, (void *)&D_801AD1B8, 0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void D_801AF904;

void func_80183B50(s32 *s0)
{
    s32 iVar2;
    s32 *v1;
    u16 uVar1;
    u16 uVar2;

    iVar2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = iVar2;

    if (iVar2 == 0) {
        func_8012CAE4(s0);
    }
    else {
        func_8001C214(iVar2, &D_801AF904);
        v1 = *(s32 **)((u8 *)s0 + 0x20);
        uVar1 = *(u16 *)((u8 *)s0 + 0xFC);
        *(u16 *)((u8 *)v1 + 0x12) = uVar1;
        func_8012B2CC(s0);

        uVar2 = *(u16 *)((u8 *)s0 + 0x2);
        *(s32 *)((u8 *)s0 + 0xE8) = 0xFFE00000;
        uVar2 = uVar2 + 1;
        *(u16 *)((u8 *)s0 + 0x2) = uVar2;
    }
}









extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBCC(s32);
extern void func_8012AD80(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

extern u8 D_80126B5C;
extern u8 D_801AD1B8[];

void func_80183BC8(s32 a0)
{
    s16 sp10[4];
    s32 v0;

    if ((*(s32 *)(*(s32 *)(a0 + 0x64) + 0xE0) & 2) == 0) {
        if (func_8012BDBC(*(s32 *)(a0 + 0x64), 0x200) == 0) {
            goto skip_update;
        }
        v0 = func_8012B6D4((s16 *)(*(s32 *)(a0 + 0x64) + 4), (s16 *)&D_80126B5C);
        {
            s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), v0, 1);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        }
    } else {
        sp10[0] = *(u16 *)(a0 + 0x6);
        sp10[1] = *(u16 *)(a0 + 0xA);
        sp10[2] = *(u16 *)(a0 + 0xE);
        v0 = func_8012B70C((s16 *)(a0 + 0x88), sp10);
        {
            s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), v0, 4);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        }
    }

skip_update:
    func_8012B178(a0, *(s32 *)(a0 + 0xE8));

    *(s32 *)(a0 + 0xE8) = *(s32 *)(a0 + 0xE8) + 0x18000;
    if (*(u16 *)(a0 + 0x34) == 0) {
        v0 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (v0 != 0) {
            if ((*(s32 *)(*(s32 *)(a0 + 0x64) + 0xE0) & 2) == 0) {
                *(s32 *)(a0 + 0xE8) = 0;
                *(s32 *)(*(s32 *)(a0 + 0x64) + 0xE0) |= 2;
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            }
        } else {
            s32 obj2 = *(s32 *)(a0 + 0x64);
            s32 flags2 = *(s32 *)(obj2 + 0xE0);
            if ((flags2 & 2) == 0 && *(s32 *)(a0 + 0x1C) == 0x15) {
                *(s32 *)(obj2 + 0xE0) = flags2 | 2;
            }
        }
    } else {
        func_8012AD80(a0);
    }

    func_8012D5E4(a0, (s32)D_801AD1B8, (s32)D_801AD1B8 + 8, 0xA);
    *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
}


/* func_80183D78 @ ov_SC02_041 (subseg ov_SC02_041_jr_8017BEBC) — MATCH (154 ins).
 *
 * GATE: .venv/bin/python tools/match_one.py func_80183D78 \
 *         --c .run/wave-s41/ov_SC02_041/func_80183D78.c \
 *         --asm-subdir asm/ov_SC02_041/nonmatchings/ov_SC02_041_jr_8017BEBC
 *
 * TU-INTEGRATION VERIFIED (not just an iso-MATCH): the body below, minus the four
 * typedefs, was spliced over the INCLUDE_ASM at
 * src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c:5587 and the whole TU compiled with the
 * real triple. Result: the SAME 4 cc1 diagnostics as the unmodified TU (zero new),
 * and cc1's emitted instruction stream for this function is IDENTICAL to the
 * standalone compile (only $L local-label numbers renumber). Splice recipe:
 * drop the `#include "common.h"` and the four typedefs, keep everything from
 * `extern u16 D_800B99DA;` down.
 *
 * NOTE: .run/ghidra_c/func_80183D78.c is a decompile of a DIFFERENT function
 * (overlay VA collision — this VA is live in 4 overlays). Discarded; worked from
 * the .s, seeded off the matched in-TU neighbour func_801837B0 (line 5484).
 *
 * WHAT THE .s SAYS — the two non-obvious levers:
 *
 * (1) THE COLOUR SELECT IS AN if/else, NOT A TERNARY. The target reads
 *       bnez $v0,.L / li $v0,0x58 [ds] / li $v0,0x48 / sb $v0,0x56($sp)
 *     — one tail-merged `sb` AFTER the join — and then RELOADS the byte with
 *       lbu $v1,0x56($sp) / srl $v1,2 / sb 0x55 / sb 0x54.
 *     Written as `pkt.rgb[1].b = (D_800B99DA & 1) ? 0x58 : 0x48;` the draft was
 *     LENGTH-DRIFT -1 with inverted branch polarity: cse kept the constant live in
 *     a register across the join, so `>>2` folded to `srl $v1,$a0,2` with NO reload,
 *     and the arms laid out mirrored (beqz + 0x48 in the delay slot).
 *     Storing INSIDE both arms fixes BOTH residuals at once: cross-jump tail-merges
 *     the two identical `sb`s into the single post-join store (cookbook §5a), which
 *     both flips the polarity to `bnez`+0x58 and kills the register equivalence, so
 *     the later `pkt.rgb[1].b >> 2` becomes a genuine `lbu` round-trip. One edit,
 *     124 mismatches -> 0. This is the §3-T4 branch-polarity lever and the §5a
 *     cross-jump lever being the SAME lever.
 *
 * (2) lbu + sll 24 + sra 24 (NOT `lb`) == `(s8)*p++` off a `u8 *`. The data really
 *     is signed (D_801AD1F8 = F4 00 F8 F8 ... = -12,0,-8,-8,... an octagon ring),
 *     but declaring the array `s8` would emit a single `lb`. The u8 array + cast at
 *     the use is what survives combine as the three-instruction form.
 *
 * (3) The pointer walk is 5x `*p++` then `*p--` for the sixth field, net +4 per
 *     iteration over a 6-byte window: consecutive iterations overlap, so v[3] of
 *     iteration k is v[0] of iteration k+1 (a quad strip round the ring). The `p--`
 *     is a real source-level post-decrement — a `p += 4` would collapse the five
 *     `addiu $s0,$s0,1`s into one.
 *
 * (4) Chained assignment order is load-bearing throughout: `a.r = a.g = a.b = 0`
 *     stores b,g,r (rightmost first), which is exactly the descending offset order
 *     the target shows for rgb[0]/rgb[2]/rgb[3] and for v[1].vx/vy/vz. Same idiom
 *     the matched neighbour func_801837B0 uses.
 *
 * (5) Frame: `MATRIX m;` declared BEFORE `PKT_801837B0 pkt;` puts m at sp+0x10 and
 *     pkt at sp+0x30 (gcc-2.7.2 assigns locals ascending in declaration order —
 *     same as func_801837B0's pkt@0x10 / flag1@0x48 / flag2@0x4C / otz@0x50).
 *
 * Signature: 3 params, forwarded untouched to func_8018428C(a0,a1,a2,&m) — both
 * callers in this TU (func_80182B38 @0x80182B7C, func_80183AE8 @0x80183B34) set
 * $a0=actor, $a1=&D_801AD1B8, $a2=const, and func_8018428C's own .s consumes
 * $a1/$a2/$a3.
 */
#include "common.h"

/* --- types: ALREADY PRESENT in src/shared/engine_types.h (pulled into the real TU
 * via engine_core.h). Delete these four typedefs when banking into
 * src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c — they exist verbatim at
 * engine_types.h:1168 (MATRIX), :1726 (CV_801837B0), :3787..:3793 (SV/PKT).
 * The immediate neighbour func_801837B0 (line 5484, MATCHed) uses PKT_801837B0
 * with the identical v[4]/rgb[4]/code layout and the same `pkt.code = 0x50000000`. */






void func_80183D78(s32 a0, void *a1, s32 a2)
{
    extern u16 D_800B99DA;
    extern u8 D_801AD1F8[];
    extern u8 D_801AD20C[];
    extern s32 func_80017758(void *a0, void *a1);   /* canon, TU line 1761 */
    extern void func_8018428C(s32 a0, void *a1, s32 a2, MATRIX *a3);
    MATRIX m;               /* sp+0x10 */
    PKT_801837B0 pkt;       /* sp+0x30 */
    u8 *p;
    s32 i;

    func_8018428C(a0, a1, a2, &m);

    if (D_800B99DA & 1) {
        pkt.rgb[1].b = 0x58;
    } else {
        pkt.rgb[1].b = 0x48;
    }

    p = D_801AD1F8;
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

    p = D_801AD20C;
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


#include "common.h"

/* func_80183FE0 (ov_SC02_041_jr_8017BEBC, 171 ins) — byte-matched.
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

void func_80183FE0(s32 a0, s32 a1, s32 a2)
{
    typedef struct {
        s16 vx, vy, vz, pad;
    } SV_80183FE0;

    typedef struct {
        SV_80183FE0 v[4];    /* 0x00 */
        u8          c[4][4]; /* 0x20 */
        u32         code;    /* 0x30 */
    } Prim_80183FE0;         /* 0x34 */

    extern void func_8018428C(s32 a0, s32 a1, s32 a2, void *a3);
    extern s32 func_80017758(void *a0, void *a1);
    extern u16 D_800B99DA;
    extern u8 D_80187EB4[];
    extern u8 D_80187EC8[];

    u8 mtx[0x20];
    Prim_80183FE0 p;
    u8 *q;
    s32 i;

    func_8018428C(a0, a1, a2, mtx);

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

    q = D_80187EB4;
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
    q = D_80187EC8;
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


typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F19C_8018428C;   /*  8 bytes, align 2 */

/* func_8018428C (ov_SC04_002, ov_SC04_002_jr_8017BEBC, 83 ins)
 *
 * Sibling family (skeleton group, remapped mechanically once this banks):
 *   ov_SC02_041:func_8018428C, ov_SC04_005:func_80186C80, ov_SC04_007:func_801832EC
 *
 * Two conflicting local extern decls exist for this function in the TU
 * (func_8018739C uses `void *a1, MATRIX *a3`; func_80187604 uses `s32 a1,
 * void *a3`) -- neither is dereferenced structurally inside this function's
 * own body (a3 is only ever forwarded as an opaque pointer argument), so the
 * definition-side signature below (s32 a1, void *a3) is chosen freely and is
 * compatible with both call sites' own local prototypes.
 */
void func_8018428C(s32 a0, s32 a1, s32 a2, void *a3)
{
    extern s32 D_801151D4;
    extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern void func_80017E68(void *a0, void *a1);
    extern void func_800D23D0(void *a0);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void RotMatrixYXZ(void *a0, void *a1);
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
    extern s32 ratan2(s32 a0, s32 a1);

    s32 mtx1[8];   /* sp+0x10, 0x20 bytes: scratch MATRIX */
    s16 buf2[4];   /* sp+0x30, 8 bytes: vx,vy,vz,pad */
    s16 vec[4];    /* sp+0x38, 8 bytes: vx,vy,vz,pad */
    s32 diff[3];   /* sp+0x40 */
    s32 base;
    s32 v0;
    s32 v1;

    base = D_801151D4;

    func_8012EC04(a0, a2, (s32 *)mtx1);

    func_8012F14C((s32)mtx1, a1 + 0x18, (s32)buf2);

    func_800D20C0((void *)buf2, (void *)vec, 8);

    func_80017E68((void *)buf2, a3);

    v0 = *(u16 *)(a1 + 0x8);
    v1 = *(u16 *)(a1 + 0x10);
    v0 = v0 - v1;
    vec[0] = v0;
    v0 = *(u16 *)(a1 + 0xA);
    v1 = *(u16 *)(a1 + 0x12);
    v0 = v0 - v1;
    vec[1] = v0;
    v0 = *(u16 *)(a1 + 0xC);
    v1 = *(u16 *)(a1 + 0x14);
    v0 = v0 - v1;
    vec[2] = v0;

    ApplyMatrixSV((void *)mtx1, (void *)vec, (void *)vec);

    func_800D23D0((void *)vec);

    RotMatrixYXZ((void *)vec, a3);

    diff[0] = *(s32 *)(base + 0x5C) - buf2[0];
    diff[1] = *(s32 *)(base + 0x60) - buf2[1];
    diff[2] = *(s32 *)(base + 0x64) - buf2[2];

    ApplyTransposeMatrixLV(a3, (void *)diff, (void *)diff);

    v0 = ratan2(diff[0], diff[1]);

    vec[2] = -v0;

    RotMatrixYXZ((void *)vec, a3);
}


#include "common.h"

typedef struct { u32 addr : 24; u32 len : 8; } PTag_801843D8;

extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern short D_800B9A02;

#define gte_ldv3_801843D8(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 );" \
    "lwc2 $2, 0( %1 );" \
    "lwc2 $3, 4( %1 );" \
    "lwc2 $4, 0( %2 );" \
    "lwc2 $5, 4( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0_801843D8(r0) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 )" \
    : \
    : "r"( r0 ) )

#define gte_rtpt_801843D8() __asm__ volatile ("nop;nop;rtpt")
#define gte_rtps_801843D8() __asm__ volatile ("nop;nop;rtps")
#define gte_avsz4_801843D8() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy3_801843D8(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 );" \
    "swc2 $14, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

#define gte_stsxy_801843D8(r0) __asm__ volatile ( \
    "swc2 $14, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

#define gte_stotz_801843D8(r0) __asm__ volatile ( \
    "swc2 $7, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

#define gte_stflg_801843D8(r0) __asm__ volatile ( \
    "cfc2 $12, $31;" \
    "nop;" \
    "sw $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )

void func_801843D8(void *a0)
{
    u8 *pkt;
    s32 flag1, flag2, otz;

    pkt = D_800A5E60;
    D_800A5E60 = pkt + 0x24;

    *(u32 *)(pkt + 4) = *(u32 *)((u8 *)a0 + 0x20);
    *(u32 *)(pkt + 0xC) = *(u32 *)((u8 *)a0 + 0x24);
    *(u32 *)(pkt + 0x14) = *(u32 *)((u8 *)a0 + 0x28);
    __asm__ volatile ("");
    *(u32 *)(pkt + 0x1C) = *(u32 *)((u8 *)a0 + 0x2C);
    pkt[3] = 8;
    pkt[7] = 0x3A;

    gte_ldv3_801843D8(a0, (u8 *)a0 + 0x8, (u8 *)a0 + 0x10);
    gte_rtpt_801843D8();
    gte_stflg_801843D8(&flag1);
    gte_stsxy3_801843D8(pkt + 8, pkt + 0x10, pkt + 0x18);

    gte_ldv0_801843D8((u8 *)a0 + 0x18);
    gte_rtps_801843D8();
    gte_stflg_801843D8(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy_801843D8(pkt + 0x20);
    gte_avsz4_801843D8();
    gte_stotz_801843D8(&otz);

    if ((flag1 & 0xFFFFEFFF) == 0) {
        u8 *pkt2;
        u32 *otp;
        s32 idx;
        u8 *ot;

        ot = &D_800A6610[(*(u16 *)&D_800B9A02) << 14];
        idx = otz + 1;
        if (idx >= 0x1000) idx = 0xFFF;
        otp = (u32 *)((idx << 2) + (u32)ot);

        ((PTag_801843D8 *)pkt)->addr = ((PTag_801843D8 *)otp)->addr;
        ((PTag_801843D8 *)otp)->addr = (u32)pkt;

        pkt2 = D_800A5E60;
        D_800A5E60 = pkt2 + 8;
        pkt2[3] = 1;
        *(u32 *)(pkt2 + 4) = 0xE100002A;

        ((PTag_801843D8 *)pkt2)->addr = ((PTag_801843D8 *)otp)->addr;
        ((PTag_801843D8 *)otp)->addr = (u32)pkt2;
    }
}



extern void (*D_801AD3D4[])(void);

void func_801845B4(void *a0) {
    D_801AD3D4[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_801845F0(s32 param_1)
{

    extern u8 D_801AD398[];
    extern u8 D_801AD3A4[];
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_801AD398;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x5b;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_801AD3A4);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(void);
void func_8018466C(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}



extern void (*D_801B65F0[])(void);

void func_801846AC(void *a0) {
    D_801B65F0[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80184C08(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80184C60(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801846E8(s32 a0) {
    extern u8 D_801B65A4[];
    extern u8 D_801B65B0[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_80184C08(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801B65A4, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801B65B0);
        func_80184C60(a0);
        *(u16 *)(s0 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA);
        t = *(u16 *)(a0 + 0xE);
        *(u16 *)(s0 + 0x1A) = 0x2000;
        *(u16 *)(s0 + 0x18) = 0x2000;
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(u16 *)(s0 + 0xC) = t;
        v = *(u16 *)(a0 + 0x2) + 1;
        u = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(s32 *)(a0 + 0x1C) = 0x180;
        *(u16 *)(a0 + 0x2) = v;
        *(u16 *)(a0 + 0x10A) = u;
        func_8002D4C8(0xAA0, 0);
    }
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80184C60(s32 arg0);
extern void func_80184CDC(void *arg0);

void func_801847E4(s32 arg0) {
    s32 p;
    s32 q;
    s32 r;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;
    s32 t3;
    s32 t4;
    u16 v;
    u16 w;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(arg0 + 0x10A) == *(s16 *)(p + 0x36) && *(s16 *)(p + 0x76) > 0) {
        if (*(s32 *)(arg0 + 0x1C) == (*(s32 *)(arg0 + 0x1C) / 0x30) * 0x30 &&
            *(u8 *)(p + 0xC1) == 0) {
            *(s16 *)(p + 0x60) = 0xA;
            *(u16 *)(p + 0x5C) |= 1;
            v = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
            *(s16 *)(p + 0x5E) = 1;
            *(u16 *)(p + 0x62) = v + 0x800;
            *(u16 *)(p + 0x7C) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(p + 0x7E) = *(u16 *)(arg0 + 0xA);
            *(u16 *)(p + 0x80) = *(u16 *)(arg0 + 0xE);
        }
        if ((*(s32 *)(arg0 + 0x1C) & 7) == 0) {
            q = func_80132EF4(arg0, 0x22);
            if (q != 0) {
                t0 = rand();
                u0 = *(u16 *)(q + 0x6) - 0x10;
                *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                t1 = rand();
                u1 = *(u16 *)(q + 0xE) - 0x10;
                *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                *(u16 *)(q + 0xA) -= 0x20;
                t2 = rand();
                *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 3) << 16);
                t3 = rand();
                t4 = rand();
                *(s16 *)(q + 0x34) = ((t3 % 0x1800 + 0x1000) & ~0xF) | (t4 & 1);
                *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                *(s32 *)(*(s32 *)(q + 0x20) + 0x4) |= 0x40000000;
            }
        }
        r = *(s32 *)(arg0 + 0xCC);
        if (r != 0) {
            func_80128ED8((void *)r, (void *)(arg0 + 0xDC));
            func_80184C60(arg0);
            *(u16 *)(r + 0x8) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(r + 0xA) = *(u16 *)(arg0 + 0xA);
            w = *(u16 *)(arg0 + 0xE);
            *(u16 *)(r + 0x18) += 0x15;
            *(u16 *)(r + 0x1A) += 0x15;
            *(u16 *)(r + 0xC) = w;
        }
        if (*(u16 *)(p + 0x5E) == 0x23) {
            *(u16 *)(arg0 + 0x2) += 1;
        }
        if (func_8012BEE8(arg0) == 0) {
            return;
        }
    }
    func_80184CDC((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80184C60(s32 arg0);
extern void func_80184CDC(void *arg0);

void func_80184A74(s32 arg0) {

    extern u16 D_800B99DA;
    s32 p;
    s32 q;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;

    p = *(s32 *)(arg0 + 0xCC);
    if (p != 0) {
        func_80128ED8((void *)p, (void *)(arg0 + 0xDC));
        func_80184C60(arg0);
        *(u16 *)(p + 0x8) = *(u16 *)(arg0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(arg0 + 0xE);
        *(u16 *)(p + 0x18) -= 0x200;
        *(u16 *)(p + 0x1A) -= 0x200;
        if (*(s16 *)(p + 0x18) >= 0) {
            if (D_800B99DA % 5 == 0) {
                q = func_80132EF4(arg0, 0x22);
                if (q != 0) {
                    t0 = rand();
                    u0 = *(u16 *)(q + 0x6) - 0x10;
                    *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                    t1 = rand();
                    u1 = *(u16 *)(q + 0xE) - 0x10;
                    *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                    *(u16 *)(q + 0xA) -= 0x20;
                    t2 = rand();
                    *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 4) << 16);
                    *(s16 *)(q + 0x34) = rand() % 0x1800 + 0x2000;
                    *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                }
            }
            return;
        }
    }
    func_80184CDC((void *)arg0);
}



/* func_80184C08 — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_80184C08(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x35C && *(s32 *)(arg0 + 0x64) == *(s32 *)(p + 0x64) &&
            arg0 != (s32)p) {
            return 1;
        }
        p += 0x10C;
    }
    return 0;
}



extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80184C60(s32 arg0) {
    s32 buf[8];
    u16 out[4];
    s32 p;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(p + 0x36) == *(s16 *)(arg0 + 0x10A)) {
        func_8012EC04(p, *(s16 *)(arg0 + 0xFC), buf);
        ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, arg0 + 0x88, out);
        *(u16 *)(arg0 + 0x6) = out[0];
        *(u16 *)(arg0 + 0xA) = out[1];
        *(u16 *)(arg0 + 0xE) = out[2];
    }
}



/* func_80184CDC — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_80184CDC(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_80184D20(s32 a0, u16 *a1, s16 a2) {
    struct S80190C84 sp;
    u16 t;
    sp.f0 = a1[0];
    sp.f2 = a1[1];
    t = a1[2];
    sp.f6 = 0x35C;
    sp.fA = 0;
    sp.f8 = 0;
    sp.fE = a2;
    sp.f10 = 0;
    sp.fC = 0x7FFF;
    sp.f4 = t;
    func_8012C51C(&sp, a0);
}





