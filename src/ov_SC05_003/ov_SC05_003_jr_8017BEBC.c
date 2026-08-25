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
extern u8 D_80184A98;
extern u8 D_80184A08;
extern u8 D_801849E4;
extern u8 D_801849C0;
extern u8 D_80184A74;
extern u8 D_80184A50;
extern u8 D_80184A2C;
extern u8 D_8018499C;
extern void func_80145934(void);
extern u8 D_80184B28;
extern u8 D_80184B04;
extern u8 D_80184AE0;
extern u8 D_80184ABC;
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
extern unsigned char D_80183F20[];
extern unsigned char D_80183F50[];
extern unsigned char D_80183FA0[];
extern unsigned char D_80183FD0[];
extern unsigned char D_80184000[];
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
extern void (*D_80184050[])(void *);
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
extern s32 D_80184118[];
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
extern u8 D_801841A0[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801841A8;
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
extern int D_801AB7B0;
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
extern s32 D_801AB7B4;
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
extern s32 D_801841D8;
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
extern void (*D_80184280[])(void);
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
extern void (*D_801842A4[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80184294;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801842B8[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801842C4[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801842D4[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801842EC[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801842DC;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80184300[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018431C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018430C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80184330[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80184344[])(void);
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
extern s32 D_80184358;
extern void (*D_80184380[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80184360;
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
extern int (*D_801843CC[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801843D0[])(void);
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
extern unsigned short D_80184834[];
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
extern void (*D_80184844[])(void);
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
extern int D_801AB7E8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018486C[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018484C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018485C;
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
extern void (*D_801848AC[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801848B4[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80184880;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801848C0[])(void);
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
extern u8 D_80184890;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801AB7F0;
extern s32 D_801AB7FC;
extern s32 D_801AB800;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801848FC[])(s32 *);
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
extern s32 D_801848D0[];
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
extern s32 D_801AB7F8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80184B4C[])(void);
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
extern char D_8018496C[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80184BF0[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80184D44[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80184B60;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80184D4C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80184B70;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80184B90;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80184D54[])(void);
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
extern void (*D_80184D7C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80184D88[])(void);
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
extern void (*D_80184BFC[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80184E2C;
extern void func_8015D380(s32 a0);
extern unsigned char D_80183F10[];
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
extern unsigned char D_80184E40[];
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
extern s8 D_80184E7C[];
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
extern u16 D_80184EC4;
extern u16 D_80184EC6;
extern u16 D_80184EC8;
extern s32 D_80184ECC;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80184ED4;
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
extern int D_80184BE0;
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
extern unsigned int D_80184F58[];
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
extern void (*D_80185008[])(void);
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
extern u16 D_80185038[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018509C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801AB808[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801850C0[])(void);
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
extern int D_801AB860[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80185108[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801850F8;
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
extern char D_801AB0C4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80185110[])(void);
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
extern void (*D_80185164[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018512C;
extern s16 D_80185160;
extern s16 D_8018515E;
extern s16 D_8018515C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80185170[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801AB8C0;
extern u8 D_801AB8C1;
extern u8 D_801AB8C2;
extern u8 D_801AB8C3;
extern u8 D_801AB8C4;
extern u8 D_801AB8C5;
extern u8 D_801AB8C6;
extern u8 D_801AB8C7;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80185180[])(void);
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
extern s32 D_801AB900;
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
extern void (*D_801851C4[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80185240[];
extern s32 D_80185260[];
extern u8 D_801852DC[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801852FC[];
extern u8 D_8018531C[];
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
extern void (*D_801853B8[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80185434[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801AB0D4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80185440[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80185448[])(void);
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
extern void (*D_80185510[])(void);
extern void func_80166618(void *a0);
extern void (*D_80185520[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80185530[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018553C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018549C[];
extern u8   D_801854B0[];
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
extern void (*D_80185554[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018555C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80185564[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018556C[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80185574[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018557C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80185584[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80185638[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80185640[])(void);
extern void func_80169F00(void *a0);
extern char D_801855F0[];
extern char D_801855B0[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80185678[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80185684[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801856CC[])(void);
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
extern void (*D_80185748[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801ABC20;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018573C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80185780[];
extern unsigned short D_80185788[];
extern unsigned short D_80185790[];
extern unsigned char D_801ABC28[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801ABC20;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80185798[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801ABD5C;
extern M2C_UNK D_801ABD60;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801ABCE8;
extern void (*D_801857C8[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801ABD64[];
extern u8 D_801ABD6C[];
extern u8 D_801ABD1C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801857D0[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801857EC[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801857F4[])(void);
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
extern void (*D_8018585C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80185800;
extern u8 D_8018580C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80185890[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80185898[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801858EC[])(void);
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
extern u16 D_80185920[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80185910[];
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
extern s32 D_8018593C;
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
extern void (*D_801859B4[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801859BC[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801859C4[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801859CC[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801859D4[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801859DC[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801859E8[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801859F4[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80185A00[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80185A10[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80185A20[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80185A28[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80185A30[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80185A38[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80185A40[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80185A48[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80185A50[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80185A58[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80185A60[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80185A68[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80185A70[])(void);
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
extern void (*D_80185A78[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80185A80[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80185A88[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80185A90[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80185A98[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80185AA0[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80185AA8[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80185AB0[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80185AB8[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80185AC0[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80185AC8[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80185AD0[])(void);
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
extern void (*D_80185B14[])(void);
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
extern M2C_UNK D_80185AD8;
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
extern void (*D_80185B44[])(void);
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
extern void (*D_80185B80[])(void);
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
extern void (*D_80185BD8[])();
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
extern void (*D_80185BE8[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80185BF0[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80185D58[])();
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
extern void (*D_80185D64[])();
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
extern M2C_UNK D_801AB31C;
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
extern s16 D_801ACA58;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801AC4A0;
extern short D_801ACACC;
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
extern s32 D_801AC8CC;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801AC8F4;
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
extern s16 D_801AC8B0;
extern s32 func_8017A3B0(void);
extern short D_801AC8EC;
extern short D_801AC8E8;
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
extern s16 D_801AC8B4;
extern u16 D_801AC934;
extern u16 D_801AC936;
extern u16 D_801AC938;
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
extern s16 D_801AC92C;
extern s16 D_801AC92E;
extern s16 D_801AC930;
extern s16 D_801AC924;
extern s16 D_801AC926;
extern s16 D_801AC928;
extern void func_8017B7A8(void);
extern s16 D_801AC944;
extern s16 D_801AC946;
extern s16 D_801AC948;
extern s16 D_801AC94C;
extern s16 D_801AC94E;
extern s16 D_801AC950;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801AC93C;
extern short D_801AC93E;
extern short D_801AC940;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801AC8D4;
extern SV4 D_801AC8DC;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801AC8FC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801AC8F8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80185F40[])(void);
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


#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
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
#define gte_stsxy3_ft3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
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
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
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
#define gte_stsxy3_ft3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
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
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) )
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

void func_8017CD9C(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u16 D_80185F4C[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    SVECTOR2 vv[4];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 dy;
    u32 ot;
    s32 nparts;
    Part *part;
    s32 j;
    u32 nprim;
    u32 i;
    Prim_8017CD9C *prim;
    u8 *pkt;
    u8 *vtx;
    u8 *vd;
    u32 w;
    s32 code;
    s32 ang, half;
    u32 wx, wy, wz, wv;
    u8 *va, *vb, *vc;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    if (*(s32 *)arg0 != 0) return;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = (Part *)(arg1 + 0x14);
    nparts = *(s32 *)(arg1 + 8);
    vtx = *(u8 **)(arg1 + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    ang = arg2;
    half = ang / 2;
    dy = arg3;

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wz = part->zz;
        wv = wz >> 16;
        wy = part->yy;
        mny = wy + dy;
        __asm__ ("" : "=r"(wz) : "0"(wz));   /* zero-byte re-tie #2 — see (2) in the header */
        my = (wy >> 16) + dy;
        box[0].vz = wz;
        box[1].vz = wz;
        box[2].vz = wv;
        box[3].vz = wv;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        __asm__ ("" : "=r"(wz) : "0"(wz));   /* zero-byte re-tie #1 — see (2) in the header */
        box[4].vx = mn; box[4].vy = my; box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my; box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my; box[6].vz = wv;
        box[7].vx = mx; box[7].vy = my; box[7].vz = wv;
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
            __asm__ volatile ("");   /* live-length sliders — see (1) in the header. */
            __asm__ volatile ("");   /* Deliberately in THIS block, not the loop head. */
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
                if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                    prim = (Prim_8017CD9C *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        vv[0] = *(SVECTOR2 *)va;
                        vv[1] = *(SVECTOR2 *)vb;
                        vv[2] = *(SVECTOR2 *)vc;
                        w = w >> 16;
                        vv[0].vy += D_80185F4C[(vv[0].vz + ang) & 0x1FF] + D_80185F4C[(vv[0].vx + half) & 0x1FF];
                        vv[1].vy += D_80185F4C[(vv[1].vz + ang) & 0x1FF] + D_80185F4C[(vv[1].vx + half) & 0x1FF];
                        vv[2].vy += D_80185F4C[(vv[2].vz + ang) & 0x1FF] + D_80185F4C[(vv[2].vx + half) & 0x1FF];
                        gte_ldv3c(&vv[0]);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
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
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za;
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
                                            ((PolyFT3 *)pkt)->rgbc = tp[0] | 0x2000000;
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vv[3] = *(SVECTOR2 *)vd;
                                    vv[3].vy += D_80185F4C[(vv[3].vz + ang) & 0x1FF] + D_80185F4C[(vv[3].vx + half) & 0x1FF];
                                    gte_ldv0(&vv[3]);
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
                                            if (my >= -0x6E && mny < 0x6F) {
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
                                                ((PolyFT4 *)pkt)->rgbc = tp[0] | 0x2000000;
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



extern void (*D_80186364[])(void);

void func_8017DA00(void *a0) {
    D_80186364[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017DA3C(s32 param_1) {

    extern u8 D_8018634C;
    s32 obj = *(s32 *)(param_1 + 0x34);
    Work8017 w;
    short i;
    s32 e;
    s32 node;

    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 0x10),
                  *(s16 *)(param_1 + 0xE), 0, 0);

    w.x = *(u16 *)(param_1 + 6);
    w.y = *(u16 *)(param_1 + 0xA);
    w.z = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&w.x, &w.vx, 10);
    *(s16 *)(param_1 + 6) = w.x;
    *(s16 *)(param_1 + 0xE) = w.z;
    w.vy = 0;
    func_800D23D0(&w.vx);

    i = 0;
    do {
        e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                          *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE), i, 0);
        if (e != 0) {
            *(s16 *)(e + 0x12) = w.vx;
            *(s16 *)(e + 0x16) = w.vy;
            *(s16 *)(e + 0x1A) = 0;
        }
        i = i + 1;
    } while (i < 3);

    node = func_800D222C(param_1, &D_8018634C, 0xFD);
    if (node != 0) {
        *(s32 *)(param_1 + 0x20) = node;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x5D000100;
        ((void (*)(void *))func_8001CF30)((void *)node);
        *(s16 *)(node + 0x18) = 0x4000;
        *(s16 *)(node + 0x1A) = 0x200;
        *(s16 *)(param_1 + 0x16) = 0x200;
        *(s16 *)(param_1 + 0x14) = 0x1000;
        *(s16 *)(node + 0x28) = 0x240;
        *(s16 *)(node + 0x2A) = 0x180;
        *(s16 *)(node + 0x10) = w.vx;
        *(s16 *)(node + 0x12) = w.vy;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_80146C3C(void);
void func_8017DC00(u8 *p) {
    u8 *q;
    s32 t;
    s32 b;
    q = *(u8 **)(p + 0x20);
    *(u16 *)(p + 0x16) = *(u16 *)(p + 0x16) + *(u16 *)(p + 0x14);
    if (*(s32 *)(p + 0x1C) < 8) {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x200;
    } else {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x51;
    }
    b = *(u8 *)(q + 0x26) - 2;
    *(s16 *)(q + 0x1A) = *(u16 *)(p + 0x16);
    *(s8 *)(q + 0x26) = b;
    *(s8 *)(q + 0x25) = b;
    *(s8 *)(q + 0x24) = b;
    t = *(s32 *)(p + 0x1C);
    *(s32 *)(p + 0x1C) = t + 1;
    if (t >= 0x1E) {
        ((void (*)(u8 *))func_80146C3C)(p);
    }
}



extern void (*D_8018636C[])(void);

void func_8017DC94(void *a0) {
    D_8018636C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_80186358;

void func_8017DCD0(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_80186358, 0x18);
    if (r != 0) {
        *(s32 *)(a0 + 0x20) = r;
        *(u32 *)(r + 4) = *(u32 *)(r + 4) | 0x5C000140;
        func_8001CF30((void *)r);
        *(s16 *)(r + 0x10) = 0x400;
        *(s16 *)(r + 0x18) = 0x3000;
        *(s16 *)(r + 0x1A) = 0x3000;
        *(s16 *)(r + 0x28) = 0x248;
        *(s16 *)(r + 0x2A) = 0x180;
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}


extern void func_80146C3C(void);
void func_8017DD74(int a0) {
    int v0 = *(int *)(a0 + 0x1C);
    register unsigned char *p __asm__("$5") = *(unsigned char **)(a0 + 0x20);
    *(int *)(a0 + 0x1C) = v0 + 1;
    if (v0 >= 0x1F) {
        func_80146C3C();
    } else {
        unsigned short hv = *(unsigned short *)(p + 0x1A) + 0x1E0;
        signed char bv = *(unsigned char *)(p + 0x26) - 3;
        *(unsigned short *)(p + 0x1A) = hv;
        *(unsigned short *)(p + 0x18) = hv;
        *(signed char *)(p + 0x26) = bv;
        *(signed char *)(p + 0x25) = bv;
        *(signed char *)(p + 0x24) = bv;
    }
}



extern void (*D_801863C4[])(void);

void func_8017DDD8(void *a0) {
    D_801863C4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E008(void);
extern void func_800167B8(s32 a0);

s32 func_8017DE14(s32 a0) {
    func_8017E008();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017DE58(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017E030(void);

s32 func_8017DE7C(s32 a0) {
    func_8017E030();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017DEBC(u8 *a0) {
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
    void func_8017DF38(void) {
        func_800D1EBC();
    }



extern void (*D_801863D8[])(void);

void func_8017DF58(void *a0) {
    D_801863D8[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017DF94(s32 a0) {
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
void func_8017E008(void) {

    extern s32 D_801863E4(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801863E4, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E030(void) {

    extern s32 D_801863F0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801863F0, 0x1000000);
}


#include "common.h"

/* A-prop sibling of the byte-matched seed func_8017D840 (ov_SC01_077,
 * src/ov_SC01_077/ov_SC01_077_jr_8017AE2C.c). Same skeleton; the words that
 * differ are the per-overlay callback symbol, the eight init constants, and the
 * call order of func_8012A094 vs the callback. Symbol surface taken from
 * asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC/func_8017E058.s. */
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017E0F4(void*);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017E058(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x20;
    D_8012697A = 0;
    func_8012A018(func_8017E0F4, 0);
    func_8012A094(&D_80126948);
    ((s32 (*)(void *))func_8017E0F4)(&D_80126948);
}



extern void (*D_80186404[])(void);

void func_8017E0F4(void *a0) {
    D_80186404[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017E130);


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

void func_8017E1E8(s32 param_1, s16 *param_2) {
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


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017E380);


s32 func_8017E67C(void) {
    return 95;
}


extern s32 D_801ACA44;
extern s32 D_801AC958;
extern s32 D_801ACA60[];
extern unsigned char D_8019B394[];
extern void func_8013C0F8(s32 a0);

void func_8017E684(void)
{
    switch (D_801ACA44) {
    case 0:
        func_8013C0F8((s32)&D_8019B394);
        D_801AC958 = 0;
        D_801ACA44 = D_801ACA44 + 1;
        break;
    case 1:
        func_8017CD9C((s32)D_801ACA60, (s32)&D_8019B394, D_801AC958, 0);
        D_801AC958 = D_801AC958 + 0x14;
        break;
    }
}


extern void (*D_8019EAD4[])(void *);
extern s32 func_8012C044(s32 a0);
extern void func_8017F4FC(void *a0);

void func_8017E728(void *a0) {
    s32 s0 = (s32)a0;

    D_8019EAD4[*(u16 *)(s0 + 0x2)](a0);
    if (*(u16 *)(s0 + 0x0) != 0) {
        void *ptr = *(void **)(s0 + 0x20);
        *(u16 *)((s32)ptr + 0x2C) |= 0x10;
        if (!(*(u16 *)(s0 + 0x70) & 0x800)) {
            s32 ret = func_8012C044(s0);
            if (ret == 1) {
                *(s32 *)(s0 + 0xE4) = ret;
                func_8017F4FC((void *)s0);
            }
        }
    }
}


extern s32  func_80143970(s32 a0);
extern u16 D_8019EA10;
extern s32 D_8019EA44;
extern s32 func_8012C354(s32 a0, s32 a1);
extern short D_801A410C;
extern void func_8012A828(s32, s32);

void func_8017E7D0(s32 param_1) {
    if (func_8012C354(param_1, (s32)&(*(s32 *)&D_8019EA10)) != 0) {
        *(u8 *)(param_1 + 0xC0) = 1;
        *(s32 *)(param_1 + 0xBC) = (s32)&D_8019EA44;
        *(s32 *)(param_1 + 0xB4) = 0xFFFBDFDD;
        *(s16 *)(param_1 + 0xDE) = 0;
        *(s32 *)(param_1 + 0xC4) |= 1;
        ((void (*)(s32, void *))func_8012A828)(param_1, (void *)&D_801A410C);

        *(s16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        if ((*(u16 *)(param_1 + 0x70) & 1) != 0) {
            *(s16 *)(param_1 + 0x2) = 1;
            *(s16 *)(param_1 + 0x5C) = 0;
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4) |= 0x80000000;
        } else {
            *(s16 *)(param_1 + 0x2) = 3;
            *(s32 *)(param_1 + 0xCC) = func_80143970(param_1);
        }
    }
}


extern void func_8012BD14(s32 a0);
extern s32 func_80143970(s32 a0);
extern u16 D_8019EA10;

void func_8017E89C(void *a0) {
    register s32 mask __asm__("$4");
    register s32 v1 __asm__("$3");

    if (((s32 (*)(s32))func_8012BD14)((s32)a0) > 0x18FFF) {
        mask = 0x7FFFFFFF;
        v1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)((s32)a0 + 2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
        *(s32 *)(v1 + 4) = *(s32 *)(v1 + 4) & mask;
        v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x2C) |= 0x10;
        v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x1C) = 1;
        *(u16 *)(v1 + 0x1A) = 1;
        *(u16 *)(v1 + 0x18) = 1;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(u16 *)((s32)a0 + 0x76) = D_8019EA10;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80047948(s32 a0);
extern u16 D_8019EA12;

void func_8017E940(s32 param_1) {
    register s32 *s0 __asm__("$16");
    s32 v1;
    u16 v0;

    s0 = (s32 *)param_1;
    if (func_8012BEE8(param_1) != 0) {
        v1 = *(s32 *)((s32)s0 + 0x20);
        *(u16 *)((s32)v1 + 0x2C) &= ~0x10;
        *(u16 *)((s32)s0 + 2) = 3;
        *(u16 *)((s32)s0 + 0x5C) = D_8019EA12;
    } else {
        v0 = func_80047948(*(s32 *)((s32)s0 + 0x1C) << 10 >> 4);
        v1 = *(s32 *)((s32)s0 + 0x20);
        *(s16 *)((s32)v1 + 0x1C) = v0;
        *(s16 *)((s32)v1 + 0x1A) = v0;
        *(s16 *)((s32)v1 + 0x18) = v0;
    }
}



extern void func_8012A828(s32 a0, s32 a1);
    extern short D_801A410C;
    void func_8017E9C8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_8012A828((int)arg0, (int)&D_801A410C);
    }


extern s32 func_8012BCCC(s32 a0);

void func_8017E9F4(s32 a0) {
    s32 v0 = func_8012BCCC(a0);
    if (v0 <= 0x18000) {
        *(s16 *)(a0 + 0x2) = 5;
    }
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017EA34);

extern s32 func_8012BEE8(s32 a0);
extern u8 D_80078EAE;

void func_8017EA78(s32 param_1) {
    if (D_80078EAE != 0) {
        if (*(u16 *)(param_1 + 0x34) == 0 && *(s32 *)(param_1 + 0x94) == 10) {
            *(u16 *)(param_1 + 0x98) = 0;
            *(u16 *)(param_1 + 0x34) += 1;
        }
    } else {
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 2) = 7;
        }
    }
}


extern s32 D_801A41E4;
extern s32 func_8017F12C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_8012B23C(s32 a0);

void func_8017EAF0(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x8;
    func_8012B23C(s0);
    func_8017F12C(s0);
    ((void (*)(s32, void *))func_8012A828)(s0, (void *)&D_801A41E4);
    *(s32 *)((s32)a0 + 0x1C) = 0x2D;
    *(s32 *)((s32)a0 + 0xE0) = 0;
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017EB44);

INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017EC00);


// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @stuck: none - MATCH (41 ins), match_one + rtu_match.
// Three levers, in the order they mattered:
//  1) The `mult` sitting in BOTH branch arms is a dbr DELAY-SLOT STEAL from the
//     join block, not two multiplies in the source. The C selects the
//     MULTIPLICAND in the arms (`m`), and multiplies ONCE after the join.
//     That also makes the product a LOCAL allocno, so local-alloc coalesces
//     expand_divmod's `copy_to_mode_reg` temp away -> no `move v0,a0`, and the
//     bgez/addiu/shift all run in-place on $v0 (this was the whole 8-22 residual).
//  2) `srl` (not `sra`) for the /0x1000: the quotient's ONLY use must be a
//     narrowing store, i.e. hold it in an `s16 t`. combine's force_to_mode then
//     rewrites ASHIFTRT->LSHIFTRT because the high bits are discarded. Storing
//     `v / 0x1000` inline (2 SImode uses) keeps `sra`.
//  3) `m` must be `s32`, not `s16` - a narrow local costs lhu+sll+sra (loose
//     typing); the s32 local keeps the plain `lh`.
//  4) `p` and `q` are two SEPARATE variables so the reloaded 0x20 pointer lands
//     in $a0 rather than re-using $v1.

extern s32 func_8004787C(s32 a0);

void func_8017EC68(s32 param_1) {

    extern s16 D_80126CE0;
    s32 v;
    s32 p;
    s32 q;
    s32 m;
    s16 t;

    v = func_8004787C(0x400 - (D_80126CE0 * 8));
    if (*(s16 *)(param_1 + 0xAA) == 0) {
        m = *(s16 *)(param_1 + 0x100);
    } else {
        m = *(s16 *)(param_1 + 0x104);
    }
    p = *(s32 *)(param_1 + 0x20);
    t = (v * m) / 0x1000;
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;
    q = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(q + 0x18) <= 0) {
        *(s16 *)(q + 0x1C) = 1;
        *(s16 *)(q + 0x18) = 1;
    }
}



void func_8017ED0C(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_8017ED1C(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        if (*(s16 *)(param_1 + 0x106) != 0) {
            p = *(s32 *)(param_1 + 0x20);
            *(s16 *)(p + 0x1C) = 0x1000;
            *(s16 *)(p + 0x18) = 0x1000;
            *(s16 *)(param_1 + 0x106) = 0;
        } else {
            p = *(s32 *)(param_1 + 0x20);
            h = *(u16 *)(param_1 + 0x100);
            *(s16 *)(p + 0x1C) = h;
            *(s16 *)(p + 0x18) = h;
        }
        a = param_1;
        *(s16 *)(a + 0x5C) |= 1;
        *(s16 *)(a + 0x60) = 0;
        q = *(s32 *)(a + 0x20);
        *(s16 *)(a + 0x62) = *(u16 *)(q + 0x12) + 0x800;
        *(s16 *)(a + 0x5E) = 1;
        ((void (*)(s32, s32))func_80131E00)(a, 1);
    } else {
        a = *(s32 *)(param_1 + 0x20);
        x = *(s16 *)(a + 0x18);
        t = x + (*(s16 *)(param_1 + 0x100) - x) / 4;
        *(s16 *)(a + 0x1C) = t;
        *(s16 *)(a + 0x18) = t;
    }
}


extern s32 func_8012BCCC(s32 a0);
extern u8 D_801A43A4[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);

void func_8017EDF4(s32 param_1) {
    s32 ptr;
    s32 ret;
    s32 k;

    ptr = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 0x5C) = 0;
    *(s32 *)(param_1 + 0x1C) = 0x37;
    *(u16 *)(ptr + 0x10) = 0;
    ((void (*)(s32, void *))func_8012A828)(param_1, D_801A43A4);
    *(u16 *)(param_1 + 0x34) = 0;
    ret = func_8012BCCC(param_1);
    k = 0x52B;
    if (!(0x8FFF < ret)) {
        k = 0x52A;
    }
    func_8002D4C8(k, 0);
}


void func_8017EE60(s32 param_1) {
    extern s32 func_8012BEE8(s32 a0);
    extern void func_80130D48(s32 a0);
    extern void func_8017F4FC();
    s32 p;
    s32 q;

    if (*(s32 *)(param_1 + 0x1C) < 0xC) {
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) ^= 0x80000000;
    }
    if (func_8012BEE8(param_1) != 0) {
        func_80130D48(param_1);
        p = param_1;
        q = *(s32 *)(p + 0x20);
        *(s32 *)(p + 0x1C) = 0x3C;
        *(s32 *)(q + 4) = 0x80000000;
        func_8017F4FC(p);
    }
}


void func_8017EEE4(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        *(short *)((char *)a0 + 0xfe) = 0;
        *(unsigned short *)((char *)a0 + 0x5c) = 0xaa10;
        *(short *)((char *)a0 + 0x102) = 1;
    }


void func_8017EF04(void) {
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801824B4(s32 a0, u16 *a1, s16 a2);

void func_8017EF0C(s32 a0) {
    register int zr __asm__("$0");
    s16 sp10[3];
    u16 temp_v1;
    u16 var_v1;
    s32 phi_a1;

    phi_a1 = a0 + zr;
    temp_v1 = *(u16 *)(phi_a1 + 0x5E);
    if (temp_v1 == 0x23) {
        *(u16 *)(phi_a1 + 0xFE) = 1;
        var_v1 = *(u16 *)(*(s32 *)(phi_a1 + 0x20) + 0x2C) | 0x10;
        *(u16 *)(*(s32 *)(phi_a1 + 0x20) + 0x2C) = var_v1;
        func_8002D4C8(0xAA1, 0);
    } else {
        if (temp_v1 == 0x24) {
            sp10[2] = 0;
            sp10[0] = 0;
            sp10[1] = -8;
            func_801824B4(phi_a1, (u16 *)sp10, 0xB);
        }
    }
}



/* func_8017EF88 — light/colour ramp-up on the entity's attached prim block.
 *
 * If the s16 flag at 0xFE is set, bump the three u16 colour words at
 * 0x18/0x1A/0x1C of the block pointed to by the word at 0x20 by 0x40 each,
 * then clamp all three to 0x1800 once the first one reaches it.
 *
 * Widths pinned off the target: `lh` at 0xFE and at 0x18 (the signed compare),
 * `lhu` for the three read-modify-writes, `sh` for every store.  The pointer at
 * 0x20 is re-loaded before each RMW (the `sh` stores may alias it), which is
 * exactly what writing the deref inline gives.
 */
void func_8017EF88(int param_1) {
    int v1;

    if (*(short *)(param_1 + 0xfe) != 0) {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x18) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1a) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1c) += 0x40;
        v1 = *(int *)(param_1 + 0x20);
        if (*(short *)(v1 + 0x18) >= 0x1800) {
            *(short *)(v1 + 0x1c) = 0x1800;
            *(short *)(v1 + 0x1a) = 0x1800;
            *(short *)(v1 + 0x18) = 0x1800;
        }
    }
}


#include "common.h"

extern void func_8012CBA4(s32 a0);            /* canonical void; $v0 used -> cast at use site */
extern void func_8012ADE4(u8 *a0);
extern void func_80131E00();
extern void func_8017F338(s32 a0, s32 a1);
extern s32 func_8012AF0C(s32 a0, s32 a1);

/* func_8017F010 -- same "aggro/hostility" broadcast shape as the banked twin
 * func_801841E4 (ov_SC03_006, sim 0.9007): query the entity's own status
 * flags via func_8012CBA4(); depending on which bits are set, tell the
 * entity to react (func_8012ADE4) and/or notify (func_8017F338(obj, 2) here,
 * vs func_8018450C in the twin).  A special status byte (== 2) short-circuits
 * into func_80131E00(obj, 0x12) and returns -1 immediately.  Otherwise walk
 * the 0x60-entry, 0x10C-stride entity table at D_801202A0 looking for another
 * live entry of the SAME kind (u16 at offset 0) that isn't this entity itself
 * and that func_8012AF0C() accepts; on the first hit, either bail out
 * returning 0 (if the flags block already zeroed the state var) or notify
 * once more and return the un-zeroed state var (1).
 */
s32 func_8017F010(s32 a0) {
    extern u8 D_801202A0[];
    s32 obj;
    s32 state;
    s32 flags;
    u8 *p;
    s32 i;

    obj = a0;
    state = 1;

    flags = ((s32 (*)(s32))func_8012CBA4)(a0);

    if (flags == 0) {
        goto call_ade4;
    }
    if ((flags & 0xFF) == 2) {
        ((void (*)(s32, s32))func_80131E00)(obj, 0x12);
        return -1;
    }
    if ((flags & 0x8000) != 0) {
        if ((flags & 0x2000) != 0) {
            goto call_notify;
        }
    } else {
        if ((flags & 0x4000) == 0) {
            goto walk;
        }
    }

call_ade4:
    func_8012ADE4((u8 *)obj);

call_notify:
    func_8017F338(obj, 2);
    state = 0;

walk:
    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(u16 *)obj == *(u16 *)p && obj != (s32)p) {
            if (func_8012AF0C(obj, (s32)p) != 0) {
                if (state != 0) {
                    func_8017F338(obj, 2);
                }
                break;
            }
        }
    }
    return state;
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017F12C);









extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_8017F1AC(void *arg0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 pointA[3];
    s16 pointB[3];
    s16 diff[3];
    s32 addr;

    pointA[0] = D_80126B5E;
    pointA[1] = D_80126B62;
    pointA[2] = D_80126B66;

    pointB[0] = *(u16 *)((s32)arg0 + 0x6);
    pointB[1] = *(u16 *)((s32)arg0 + 0xA);
    pointB[2] = *(u16 *)((s32)arg0 + 0xE);
    pointA[1] = D_80126B62 - 0x2A;

    addr = (*(s32 *)((s32)arg0 + 0x58) & 0xFFFFFFF) | 0x80000000;

    if (*(s16 *)(addr + 0x4) + pointB[0] > pointA[0]) {
        return 0;
    }
    if (*(s16 *)(addr + 0x6) + pointB[0] < pointA[0]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xC) + pointB[2] > pointA[2]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xE) + pointB[2] < pointA[2]) {
        return 0;
    }
    if (*(s16 *)(addr + 0x8) + pointB[1] > pointA[1]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xA) + pointB[1] < pointA[1]) {
        goto ret0;
    }

    diff[0] = pointA[0] - pointB[0];
    diff[1] = pointA[1] - pointB[1];
    diff[2] = pointA[2] - pointB[2];

    VectorNormalSS(diff, diff);
    func_8012F568(1, 1, *(s16 *)((s32)arg0 + 0xDC), 0xD, (s32)pointA, (s32)diff);
    return 1;

ret0:
    return 0;
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017F338);

#include "common.h"

/* Banked twin: src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c func_801846D0 (seed_sim 1.0).
 * Same guard-and-reset shape; TU-local symbol names adopted per law 2/1b. */

extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8002A04C(s32 a0);
extern s32 func_801439C0(s32 a0);
extern void func_8012C218(void *a0);
extern short D_801A410C;

void func_8017F4FC(void *a0) {
    s32 s0 = (s32)a0;
    s32 p20a;

    *(s16 *)(s0 + 0x76) = 0;

    if (*(s32 *)(s0 + 0xE4) == 0) {
        p20a = *(s32 *)(s0 + 0x20);
        *(u8 *)(s0 + 0xC1) = 0;
        *(s16 *)(s0 + 0x2) = 1;
        *(s32 *)(p20a + 0x4) |= 0x80000000;

        {
            s32 p20b = *(s32 *)(s0 + 0x20);
            *(s16 *)(s0 + 0x5E) = 0;
            *(s16 *)(s0 + 0x5C) = 0;
            *(s16 *)(p20b + 0x14) = 0;
            *(s16 *)(p20b + 0x12) = 0;
            *(s16 *)(p20b + 0x10) = 0;
        }

        {
            s32 p20c = *(s32 *)(s0 + 0x20);
            *(u16 *)(p20c + 0x1C) = 0x1000;
            *(u16 *)(p20c + 0x1A) = 0x1000;
            *(u16 *)(p20c + 0x18) = 0x1000;
        }

        {
            register u16 t88 __asm__("$2") = *(u16 *)(s0 + 0x88);
            register u16 t8A __asm__("$3") = *(u16 *)(s0 + 0x8A);
            *(s16 *)(s0 + 0xDE) = 0;
            *(s16 *)(s0 + 0xAA) = 0;
            *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0x8C);
            *(u16 *)(s0 + 0x6) = t88;
            *(u16 *)(s0 + 0xA) = t8A;
            func_8012A828(s0, (s32)&D_801A410C);
        }
        func_8012B2CC(s0);
        func_8002A04C(s0);

        if (*(s32 *)(s0 + 0xCC) != 0) {
            func_801439C0(*(s32 *)(s0 + 0xCC));
        }
    } else {
        s32 p68;

        if ((*(s16 *)(s0 + 0x70) & 0x8000) == 0) {
            p68 = *(s32 *)(s0 + 0x68);
            if (p68 != 0) {
                if (*(s16 *)(s0 + 0x72) & 0x8000) {
                    *(u16 *)(p68 + 0xA) = *(u16 *)(p68 + 0xA) & 0x7FFF;
                }
            }
        }
        func_8012C218((void *)s0);
    }
}




s32 func_8017F62C(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


extern void (*D_801A466C[])(void);
extern s32 D_801A9620;
extern void func_80180834(void *a0);
extern s32 func_8012C0EC(s32 a0);

void func_8017F68C(void *a0) {
    D_801A466C[*(u16 *)((s32)a0 + 2)]();
    if (*(u16 *)a0 != 0) {
        if (*(s32 *)((s32)a0 + 0x90) == (s32)&D_801A9620) {
            if (*(s32 *)((s32)a0 + 0x94) == 0xA) {
                func_80181CDC((s32)a0, 0x7F9);
            } else if (*(s32 *)((s32)a0 + 0x94) == 0xF) {
                func_80181CDC((s32)a0, 0x7F8);
            }
        }
        func_80180834(a0);
        func_8012C0EC((s32)a0);
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C97C(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8017F738(void *a0) {

    extern u8 D_801A4544[];
    extern u8 D_801A461C[];
    extern s32 D_801A45B4[];

    s16 flag;

    if (func_8012C354((s32)a0, (s32)(D_801A4544 + (*(u16 *)((s32)a0 + 0x70) & 0xF) * 0x34)) == 0) {
        return;
    }

    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xBC) = (s32)D_801A461C;
    *(s32 *)((s32)a0 + 0xB4) = 0xFFFF5FFF;
    *(s32 *)((s32)a0 + 0xC4) |= 3;

    func_8001C97C(D_801A45B4[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    if ((*(u16 *)((s32)a0 + 0x70) & 1) != 0) {
        *(s16 *)((s32)a0 + 0xAE) = -0x81;
        *(u8 *)((s32)a0 + 0x75) = 2;
        flag = *(s16 *)((s32)a0 + 0x70);

        if ((flag & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 6;
            *(s16 *)((s32)a0 + 0x76) = 1;
            return;
        }
        if ((flag & 0x4000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 8;
            *(s16 *)((s32)a0 + 0x76) = 1;
            return;
        }
        if ((flag & 0x2000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 0xA;
            *(s16 *)((s32)a0 + 0x76) = 1;
        } else {
            *(s16 *)((s32)a0 + 0x2) = 3;
            func_8012B030((u8 *)a0);
        }
    } else {
        *(s16 *)((s32)a0 + 0xAE) = 0xC;
        *(s16 *)((s32)a0 + 0x2) = 1;
    }

    func_80143994((s32)a0, 0x4000);
}



extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801A96A8;

void func_8017F880(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A96A8);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017F8B8);

INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017F914);

#include "common.h"

/* callee spellings adopted from the ov_SC05_003 sibling TUs / src/shared canon (law 2) */
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);            /* canonical void; $v0 used -> cast at use site */
extern void func_8012ADE4(u8 *a0);
extern void func_80180E58(s32 a0);            /* same-TU INCLUDE_ASM neighbour */
extern s32  func_8012B8E4(s32 arg0, s32 arg1);
extern s32  func_8012BEE8(s32 a0);
extern s32  rand(void);

void func_8017F9B4(s32 param_1) {
    extern u16 D_800B99DA;
    extern s32 D_801A45B4[];
    s32 p = param_1;
    s32 t;
    s32 n;
    s32 off;
    s32 base;
    s32 nv;

    /* 0x20 -> sub-object, +0x12 = u16 angle/timer */
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) +=
        func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE0), 0xA);
    func_8012B178(p, 0xFFF80000);

    if ((((s32 (*)(s32))func_8012CBA4)(p) & 0xFF00) != 0x2000) {
        func_8012ADE4((u8 *)p);
        n = *(s32 *)(p + 0xE8) + 1;
        *(s32 *)(p + 0xE8) = n;
        if (n >= 0x80) {
            func_80180E58(p);
        } else {
            *(s32 *)(p + 0xE4) |= 1;
        }
    } else {
        *(s32 *)(p + 0xE8) = 0;
        *(s32 *)(p + 0xE4) &= ~1;
    }

    t = *(s32 *)(p + 0xE4);
    if (t & 2) {
        *(s16 *)(p + 2) = 5;
        *(s32 *)(*(s32 *)(p + 0x20) + 0x24) = D_801A45B4[*(u16 *)(p + 0x70) & 0xF];
        *(s32 *)(p + 0xE4) &= ~2;
    } else if ((t & 1) == 0) {
        if ((D_800B99DA & 0x3F) == 0) {
            *(s32 *)(p + 0xE0) += func_8012B8E4(p, 8);
        }
        if (func_8012BEE8(p) == 1) {
            off = rand() % 1024;
            base = *(s32 *)(p + 0xE0);
            if ((rand() & 1) != 0) {
                nv = base + off;
            } else {
                nv = base - off;
            }
            *(s32 *)(p + 0xE0) = nv;
            *(s32 *)(p + 0x1C) = rand() % 32 + 0x40;
        }
    } else {
        *(s32 *)(p + 0xE0) += 0x21;
    }
}


/* callee spellings adopted verbatim from this TU (law 2) */
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);            /* canonical void; $v0 used -> cast at use site */
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012B8E4(s32 arg0, s32 arg1);

extern s32 D_801A45AC[];

void func_8017FB9C(s32 param_1) {
    unsigned short *p16;
    s32 v;

    if (func_8012BDBC(param_1, 0x400) == 0) {
        v = 4;
        *(u16 *)(param_1 + 2) = v;
        v = *(s32 *)(param_1 + 0x20);
        *(s32 *)(v + 0x24) = D_801A45AC[*(u16 *)(param_1 + 0x70) & 0xF];
    }
    v = func_8012B8E4(param_1, 8);
    p16 = (unsigned short *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *p16 = (unsigned short)(*p16 + v);
    func_8012B178(param_1, 0xFFF80000);
    if (((s32 (*)(s32))func_8012CBA4)(param_1) != 0x2000) {
        func_8012ADE4((u8 *)param_1);
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80134510(s32 arg);
extern void func_80180D70(s32 a0, s32 a1);
extern u8 D_801152A8[];
extern s16 D_801152AA;
extern s16 D_801152AC;
extern s32 D_801A9620;

void func_8017FC3C(s32 param_1) {
    u16 local[3];

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xFC);
    func_8012A828(param_1, (s32)&D_801A9620);
    local[0] = *(u16 *)(param_1 + 0x6);
    local[1] = *(u16 *)(param_1 + 0xA);
    local[2] = *(u16 *)(param_1 + 0xE);
    if (func_80134510((s32)local) != 0) {
        *(u16 *)(param_1 + 0x6) = local[0];
        *(u16 *)(param_1 + 0xA) = local[1];
        *(u16 *)(param_1 + 0xE) = local[2];
        *(u16 *)(param_1 + 0xE8) = *(u16 *)D_801152A8;
        *(u16 *)(param_1 + 0xEA) = *(u16 *)&D_801152AA;
        *(u16 *)(param_1 + 0xEC) = *(u16 *)&D_801152AC;
        func_80180D70(param_1, param_1 + 0xE8);
        *(u16 *)(param_1 + 0x2) = 7;
    }
}


#include "common.h"

extern s32 func_80180B04(s32 a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);
extern void func_80180E34(s32 arg0);
extern s32 func_801808E8(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_80180CE8(s32, void *, s32);
extern void func_8012B178(s32 a0, s32 a1);

extern u8 D_800D3918[];
extern u8 D_801A45C4[];
extern u8 D_801152A8[];
extern s16 D_801152B0;

void func_8017FD08(s32 a0) {
    s32 s0 = a0;
    s32 sp10[2];
    s32 v1;
    void *ptr;

    v1 = func_80180B04(s0, (s32)D_800D3918, 1);
    if ((v1 & 0xE000) == 0) {
        ((void (*)(s32, void *, void *))func_80180E34)(s0, D_801A45C4, sp10);
        v1 = func_801808E8(s0, sp10, 1, 1);
        if ((v1 & 0xE000) == 0) {
            func_8012C218((void *)s0);
            return;
        }
    }
    ptr = D_801152A8;
    if ((v1 & 0xC000) != 0) {
        ptr = &D_801152B0;
    }
    func_80180CE8(s0, ptr, 4);
    func_8012B178(s0, 0xFFF80000);
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017FDC0);

INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017FE44);

INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8017FEC0);

#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

/* func_8017FF60 — 4-state handler on the u16 state word at +0x34.
 * Symbols spelled from asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC/func_8017FF60.s
 *
 * TU-adopted declarations (law 2):
 *   func_8012AD80 / func_8012C218 / func_80012C6C / func_80180E34 come from
 *   src/ov_SC05_003/ov_SC05_003_jr_8017BEBC.c verbatim; func_80180E34 is
 *   DEFINED there with one parameter, so its 3-arg use is a call-site cast
 *   (same idiom the TU already uses for ApplyMatrixSV / func_8012CBCC).
 */

extern void func_8012AD80(struct vec *a0);
extern void func_8012C218(void *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80180E34(s32 arg0);

extern s32  func_801808E8(s32 a0, void *a1, s32 a2, s32 a3);
extern s32  func_80180C44(s32 a0, void *a1, s32 a2);

extern void func_8012B21C(void *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern s32  func_80013478(s32 a0, s32 a1);   /* 2nd arg is the +0xCC record: the
                                              * copy-suggestion that puts it in $a1
                                              * (see the note at the use site) */

extern u8   D_801A45C4[];   /* two 0x10-byte records: +0x00 and +0x10 */

void func_8017FF60(s32 a0) {
    SV3_8012CC88 sp10;   /* sp+0x10, 8 bytes -> 0x28 frame */
    s32 r;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        func_8012AD80((struct vec *)a0);
        ((void (*)(s32, void *, void *))func_80180E34)(a0, &D_801A45C4[0], &sp10);
        func_801808E8(a0, &sp10, 1, 1);
        ((void (*)(s32, void *, void *))func_80180E34)(a0, &D_801A45C4[0x10], &sp10);
        if (func_80180C44(a0, &sp10, 1) & 0x2000) {
            func_8012B21C((void *)a0);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    /* case 1: the second read of *(s32 *)(a0 + 0xCC) is ALSO func_80013478's
     * arg1.  local-alloc's copy-suggestion then homes that pseudo in $a1 and
     * deletes the redundant `move $a1,$a1`, which is why the target loads
     * `lw $a1, 0xCC($s1)` and the `lh` lands in $v1 instead of reusing the base.
     * Writing the call with one argument compiles to 152/152 with those exact
     * two instructions in $v1 (only a `register __asm__("$5")` pin recovers it,
     * and a pin would forfeit the h_seq family). */
    case 1:
        if (*(s16 *)(*(s32 *)(a0 + 0xCC) + 6) != -1) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                func_80012C6C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10), 0, 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) +
                func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4),
                                            (void *)*(s32 *)(a0 + 0xCC)),
                              8);
        }
        func_8012B178(a0, 0xFFF80000);
        r = ((s32 (*)(s32))func_8012CBA4)(a0) & 0x8000;
        if (*(s16 *)(*(s32 *)(a0 + 0xCC) + 6) != -1) {
            if (func_80013478(a0 + 4, *(s32 *)(a0 + 0xCC)) < 0x100) {
                *(s32 *)(a0 + 0xCC) = *(s32 *)(a0 + 0xCC) + 8;
            }
        } else if (r != 0) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    case 2:
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            func_80012C6C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10), -0x400, 8);
        func_8012B178(a0, 0xFFF80000);
        func_8012CBCC(a0);
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x21) {
            *(s32 *)(a0 + 0x48) = 0;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    case 3:
        func_8012AD80((struct vec *)a0);
        ((void (*)(s32, void *, void *))func_80180E34)(a0, &D_801A45C4[0], &sp10);
        if ((func_801808E8(a0, &sp10, 1, 1) & 0xE000) == 0) {
            func_8012C218((void *)a0);
        }
        break;
    }
}



#include "common.h"

extern void func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801A45B4[];
extern s32 D_801A96F0;

void func_801801C0(s32 *a0) {
    s32 *s0 = a0;
    s32 v0, v1;

    *(s16 *)((char *)s0 + 2) = 0xD;
    *(s16 *)((char *)s0 + 0x34) = 0;
    *(s32 *)((char *)s0 + 0x1C) = 0;
    func_8012C588(0x24F, (s32)s0);
    v1 = *(s32 *)((char *)a0 + 0x20);
    v0 = D_801A45B4[*(u16 *)((char *)s0 + 0x70) & 0xF];
    *(s32 *)((char *)v1 + 0x24) = v0;
    func_8012A828((s32)a0, (s32)&D_801A96F0);
}


#include "common.h"

extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);

extern s32 D_801A9740;
extern s32 D_801A97C8;
extern s32 D_801A96A8;
extern s32 D_801A45AC[];

void func_80180230(s32 arg0) {
    s32 v0;
    s32 p;
    u16 mode;
    s32 idx;
    s32 q;

    v0 = func_8012B864(arg0);
    v0 = func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), v0 + 0x800, 10);
    p = *(s32 *)(arg0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;

    mode = *(u16 *)(arg0 + 0x34);
    switch (mode) {
        case 0:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                func_8012A828(arg0, (s32) &D_801A9740);
                v0 = *(u16 *)(arg0 + 0x34) + 1;
                *(u16 *)(arg0 + 0x34) = v0;
            }
            break;
        case 1:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                v0 = *(s32 *)(arg0 + 0x1C) + 1;
                *(s32 *)(arg0 + 0x1C) = v0;
                if (v0 >= 4) {
                    func_8012A828(arg0, (s32) &D_801A97C8);
                    *(u16 *)(arg0 + 0x34) += 1;
                }
            }
            break;
        case 2:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                func_8012A828(arg0, (s32) &D_801A96A8);
                *(s32 *)(arg0 + 0x1C) = 0x1E;
                *(u16 *)(arg0 + 0x34) += 1;
            }
            break;
        case 3:
            if (func_8012BEE8(arg0) != 0) {
                idx = *(u16 *)(arg0 + 0x70) & 0xF;
                *(u16 *)(arg0 + 0x2) = 1;
                q = *(s32 *)(arg0 + 0x20);
                *(s32 *)(q + 0x24) = D_801A45AC[idx];
            }
            break;
    }
}


#include "common.h"

extern void func_8012E9C0(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_80131E00();

void func_801803B8(s32 param_1) {
    s32 s0;
    s32 v0;
    s32 v1;
    s32 a2;
    s32 p;
    s32 ret;

    func_8012E9C0(param_1);
    s0 = param_1;

    v0 = *(s32 *)(s0 + 0x78);
    v1 = *(s16 *)(s0 + 0x60);
    v0 = *(s16 *)(v0 + 0x30);
    a2 = v1 * v0;
    v0 = a2 >> 12;
    v1 = v0;
    __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
    if ((s16)v0 <= 0) {
        v1 = 1;
    }

    v0 = *(u16 *)(s0 + 0x76) - v1;
    *(s16 *)(s0 + 0x76) = v0;

    v0 = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(s16 *)(s0 + 0x5C) = v0;
    if (*(s16 *)(s0 + 0x76) <= 0) {
        *(s16 *)(s0 + 0x5C) = 0;
    }

    v1 = *(u16 *)(s0 + 0x70);
    if (v1 & 1) {
        if ((v1 & 0xE000) != 0) {
            goto label_468;
        }
        v0 = *(u16 *)(s0 + 0x62);
        p = *(s32 *)(s0 + 0x20);
        v0 = (v0 + 0x800) & 0xFFF;
        *(u16 *)(p + 0x12) = v0;
    }
    v0 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v0 + 0x14) = 0;
    *(s16 *)(v0 + 0x10) = 0;
    func_8012B2CC(s0);

label_468:
    func_8012B23C(s0);

    if (*(s16 *)(s0 + 0x76) <= 0) {
        func_80131E00(s0, 0xC);
    } else {
        ret = func_80131A34(s0, 4);
        if (ret != 0) {
            *(s8 *)(s0 + 0xC2) = 0;
        } else {
            *(s8 *)(s0 + 0xC2) = 1;
            *(s16 *)(s0 + 0x98) = 0;
            *(s32 *)(s0 + 0x1C) = 0x10;
        }
    }
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_801804CC);

void func_80180584(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
    }


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_80180598);

#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80180C44(s32 a0, void *a1, s32 a2);
extern void func_80180E34(s32 arg0);
extern void func_8012E8C4(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_801807F8(s32 a0);
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 dx, s32 dy);
extern s16 D_801152B0;
extern u8 D_801152A8[];
extern u8 D_801A45C4[];

/* a0 = actor base (state u16 at +0x34, mode s32 at +0x1C).
 * case 0/1/2 dispatch on the actor's state field; case 0 additionally spawns
 * a sub-object via func_80132EF4(a0, 0x50) and, depending on flag bits
 * returned by func_80180C44, aims it using a table entry (D_801152B0 /
 * D_801152A8) via ratan2 + func_80047D3C (hypot-like). */
void func_801805E4(s32 a0) {
    s32 state;
    s32 s2;
    void *s1;
    s16 buf[4];
    s32 flags;
    s32 v0;
    s32 t0;
    s32 t1;
    s16 tmp;

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x80;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        s2 = func_80132EF4(a0, 0x50);
        if (s2 == 0) {
            return;
        }
        s1 = 0;
        ((void (*)())func_80180E34)(a0, D_801A45C4, buf);
        flags = func_80180C44(a0, buf, 1);
        if (flags & 0xC000) {
            s1 = &D_801152B0;
        } else if (flags & 0x2000) {
            s1 = D_801152A8;
        }
        if (s1 != 0) {
            v0 = ratan2(*(s16 *)((u8 *)s1 + 4), *(s16 *)((u8 *)s1 + 2));
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x10) = v0 + 0x400;
            tmp = *(s16 *)((u8 *)s1 + 4);
            t0 = tmp * tmp;
            tmp = *(s16 *)((u8 *)s1 + 2);
            t1 = tmp * tmp;
            v0 = func_80047D3C(t0 + t1);
            v0 = ratan2(*(s16 *)((u8 *)s1 + 0), -v0);
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x12) = v0;
        } else {
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x10) = 0x400;
        }
        return;
    case 1:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x20;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;
    case 2:
        func_8012E8C4(a0);
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        func_80130D48(a0);
        func_801807F8(a0);
        return;
    default:
        return;
    }
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_8018079C);

extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void *param_1);

void func_801807F8(s32 a0) {
    func_8002AC00(0x19);
    func_8002A04C(a0);
    func_8012C098((void *)a0);
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_80180834);

INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_801808E8);

#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"
extern void func_8012AD80(struct vec *a0);
extern s32 func_80133784(s32, void*, s32);

s32 func_80180B04(s32 a0, s32 a1, s32 a2) {
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16*)(a0 + 0x3A);
    sp10.vy = *(u16*)(a0 + 0x3E);
    sp10.vz = *(u16*)(a0 + 0x42);
    sp10.vx += *(u16*)(a1 + 0);
    sp10.vy += *(u16*)(a1 + 2);
    sp10.vz += *(u16*)(a1 + 4);

    func_8012AD80((struct vec *)a0);

    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a1 + 0);
    sp18.vy += *(u16*)(a1 + 2);
    sp18.vz += *(u16*)(a1 + 4);

    v0 = ((s32 (*)(s32, s32, s32))func_80133784)((s32)(s16)a2, (s32)&sp10, (s32)&sp18);

    sp18.vx -= *(u16*)(a1 + 0);
    sp18.vy -= *(u16*)(a1 + 2);
    v0 |= *(u8*)&sp18.pad;
    sp18.vz -= *(u16*)(a1 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;
    return v0;
}


extern s32 func_80133784(s32, void *, s32);
struct SV3_8012CC88 { u16 vx, vy, vz; u8 pad; };

s32 func_80180C44(s32 a0, void *a1, s32 a2) {
    struct SV3_8012CC88 sp10;
    struct SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16 *)(a0 + 0x06);
    sp10.vy = *(u16 *)(a0 + 0x0A);
    sp10.vz = *(u16 *)(a0 + 0x0E);

    sp18.vx = *(u16 *)(a0 + 0x06);
    sp18.vy = *(u16 *)(a0 + 0x0A);
    sp18.vz = *(u16 *)(a0 + 0x0E);
    sp18.vx += *(u16 *)(a1 + 0);
    sp18.vy += *(u16 *)(a1 + 2);
    sp18.vz += *(u16 *)(a1 + 4);

    v0 = ((s32 (*)(s32, s32, s32))func_80133784)((s32)(s16)a2, (s32)&sp10, (s32)&sp18);

    v0 |= *(u8 *)&sp18.pad;
    return v0;
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_80180CE8);

extern void func_80013F3C(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_8012B260(u8 *a0);
extern void RotMatrixY(s32, void *);
extern void RotMatrixZ(s32, void *);
extern s32 RotMatrixX(s32, void *);

void func_80180D70(s32 a0, s32 a1) {
    s16 ang[4];
    void *m;

    m = (void *)(*(s32 *)(a0 + 0x20) + 0x34);
    ang[0] = ratan2(*(s16 *)(a1 + 4), *(s16 *)(a1 + 2));
    ang[2] = ratan2(*(s16 *)a1,
                    -func_80047D3C((*(s16 *)(a1 + 4)) * (*(s16 *)(a1 + 4)) +
                                   (*(s16 *)(a1 + 2)) * (*(s16 *)(a1 + 2))));
    func_80013F3C((s32)m);
    RotMatrixY(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), m);
    RotMatrixZ(ang[2], m);
    RotMatrixX(ang[0], m);
    func_8012B260((u8 *)a0);
}


    extern void ApplyMatrixSV(void*, void*, void*);
    void func_80180E34(s32 arg0) {
        ((void (*)())ApplyMatrixSV)(*(s32 *)(arg0 + 0x20) + 0x34);
    }


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_80180E58);

extern u16 D_800B99DA;
extern s32 D_801A46B4[];
extern s32 D_801A46EC[];
extern s32 D_801A4724[];

void func_80180F44(void)
{
    func_800183E0(D_801A46B4[D_800B99DA % 14]);
    func_800183E0(D_801A46EC[D_800B99DA % 14]);
    func_800183E0(D_801A4724[D_800B99DA & 0xF]);
}



extern void (*D_801A4770[])(void);

void func_80181020(void *a0) {
    D_801A4770[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, void *a1);
extern void func_801814D8(s32 a0, s32 a1);
extern u8 D_801A4764[];

void func_8018105C(void *param_1)
{
    s32 v0;

    v0 = func_8012C1B8();
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }

    *(s32 *)(param_1 + 0x20) = v0;
    func_8001CA1C(v0, &D_801A4764);

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;

    v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = ((s32)v0 << 16) >> 17;

    v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = ((s32)v0 << 16) >> 17;

    *(s16 *)(param_1 + 0xFE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);

    func_801814D8((s32)param_1, 2);
    *(u16 *)(param_1 + 0x2) = 1;
}


extern s32 D_801A9850;
extern s32 D_801A97C8;
extern void func_801814D8(s32 a0, s32 a1);

void func_8018111C(s32 param_1)
{
    s32 vec;
    s32 w;

    vec = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(param_1 + 0xFE) != *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x36) ||
        *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x90) == (s32)&D_801A9850) {
        *(s32 *)(param_1 + 0x48) = 0xC000;
        *(u16 *)(param_1 + 2) = 3;
        return;
    }
    w = *(u16 *)(vec + 0x1A) + 0x40;
    *(u16 *)(vec + 0x18) += 0x40;
    *(u16 *)(vec + 0x1A) = w;
    if ((s16)*(u16 *)(vec + 0x18) >= 0x1801 || (s16)w >= 0x1801) {
        *(u16 *)(vec + 0x1A) = 0x1800;
        *(u16 *)(vec + 0x18) = 0x1800;
    }
    if (*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x90) == (s32)&D_801A97C8 &&
        *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x94) == 9) {
        *(u16 *)(param_1 + 2) = 2;
    }
    func_801814D8(param_1, 2);
}


#include "common.h"

extern void func_8012B2CC(s32 a0);
extern s32  func_80013328(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32  func_80181CDC(s32 a0, s32 a1);

extern u8 D_80126B5C;

void func_801811EC(s32 a0)
{
    s32 vec[3];

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) + 0x800;
    func_8012B2CC(a0);

    vec[0] = 0;
    vec[1] = -0x100000;
    vec[2] = -((func_80013328((s32)&D_80126B5C, a0 + 4) << 16) / 34);

    func_8012B14C(a0, vec);

    *(s32 *)(a0 + 0x48) = 0x18000;
    func_8012CBF4(a0);
    func_80181CDC(a0, 0x7FA);
    *(u16 *)(a0 + 2) = 3;
}


#include "common.h"

/* Callees / globals — spelled exactly as this TU's own declarations
 * (law 2/2b). See src/ov_SC05_003/ov_SC05_003_jr_8017BEBC.c for the
 * canonical spellings this draft adopted:
 *   - D_801270C0  : extern u16 D_801270C0;   (line 1129)  read via *(s16*)& cast
 *                   (idiom seen at src/ov_SC03_006/ov_SC03_006_jr_80140608.c:1778)
 *   - D_801152B0  : extern s16 D_801152B0;   (line 405)
 *   - D_801152A8  : extern u8 D_801152A8[];  (line 600/635)
 *   - func_8012C218 : extern void func_8012C218(void *a0);  (line 4730, used by
 *                     the in-TU neighbour func_80182470 at line 4739)
 *   - func_8012CBF4 : canonical decl is `void func_8012CBF4(s32 a0)` (see
 *                     src/shared/engine_core.h DEFINE_func_8012CBF4); callers
 *                     that need its $v0 side value cast the call, e.g.
 *                     src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:4793.
 *   - func_80132EF4 : extern s32 func_80132EF4(s32 a0, s32 a1); (used earlier
 *                     in this same TU, e.g. line 4553/4586).
 *   - ratan2, func_80047D3C : per this TU's own externs (lines 247/270 area).
 *   - func_80181CDC : DEFINED earlier in this same TU (line 4454) as
 *                     `s32 func_80181CDC(s32 a0, s32 a1)`.
 *   - func_8012D5E4 : extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
 *                     (repo-wide idiom `(s32)D_x, (s32)D_x + 8` — e.g.
 *                     src/ov_SC04_007/ov_SC04_007_jr_8017BEBC.c:6765).
 *   - D_80126B96  : not declared in this TU yet; repo-wide canonical is
 *                     `extern u16 D_80126B96;`.
 *   - D_801A4784  : brand-new symbol (no other TU references it). Declared
 *                     raw array per the func_8012D5E4-table idiom
 *                     `extern u8 D_x[];`.
 */

extern u16 D_801270C0;
extern s16 D_801152B0;
extern u8 D_801152A8[];
extern void func_8012C218(void *a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_80181CDC(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_80126B96;
extern u8 D_801A4784[];

void func_801812AC(s32 a0) {
    s32 obj = a0;
    s16 v1;
    s16 *s1;
    s32 s0;
    s32 i;
    s32 pad[2]; /* dead-local frame pad (cookbook §162i1); target frame is 8
                 * bytes larger than this body's live locals account for. */

    if (*(s16 *)(obj + 0xA) >= 0x10) {
        func_8012C218((void *)a0);
        __asm__ __volatile__("" ::: "memory");   /* zero-byte cross-jump barrier (cookbook §5a) */
        return;
    }

    s1 = 0;
    __asm__ __volatile__("");
    if (*(s16 *)&D_801270C0 == 2) {
        return;
    }

    v1 = ((s32 (*)(s32))func_8012CBF4)(obj);
    if (v1 & 0xC000) {
        s1 = &D_801152B0;
    } else if (v1 & 0x2000) {
        s1 = (s16 *)D_801152A8;
    }

    if (s1 != 0) {
        for (i = 0; i < 6; i++) {
            func_80132EF4(obj, 0x51);
        }
        s0 = func_80132EF4(obj, 0x50);
        if (s0 != 0) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
                ratan2(s1[2], s1[1]) + 0x400;
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                ratan2(s1[0], -func_80047D3C(s1[2] * s1[2] + s1[1] * s1[1]));
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x14) = 0;
        }
        func_80181CDC(obj, 0x7FB);
        func_8012C218((void *)obj);
    } else {
        if (func_8012D5E4(obj, (s32)D_801A4784, (s32)D_801A4784 + 8, 0x18) == 1) {
            D_80126B96 = 0x4014;
        }
    }
}


extern void func_8012C218(void *a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80181CDC(s32 a0, s32 a1);

void func_80181438(s32 a0) {
    s32 s1 = a0;
    s32 q;
    s32 i;

    if (*(s16 *)(s1 + 0xA) >= 0x10) {
        func_8012C218((void *)s1);
        return;
    }
    if (((s32 (*)(s32))func_8012CBF4)(s1) & 0x6000) {
        q = func_80132EF4(s1, 0x50);
        i = 0;
        if (q != 0) {
            *(s16 *)(*(s32 *)(q + 0x20) + 0x10) = 0x400;
        }
        while (i < 3) {
            func_80132EF4(s1, 0x51);
            i++;
        }
        func_80181CDC(s1, 0x7FB);
        func_8012C218((void *)s1);
    }
}


extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern u8 D_801A4794[];

void func_801814D8(s32 arg0, s32 arg1) {
    s32 buf[8];
    u16 out[4];

    func_8012EC04(*(s32 *)(arg0 + 0x64), arg1, buf);
    ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, (s32)D_801A4794, out);
    *(u16 *)(arg0 + 0x6) = out[0];
    *(u16 *)(arg0 + 0xA) = out[1];
    *(u16 *)(arg0 + 0xE) = out[2];
}



extern void func_80181720(void *a0);

void func_80181540(void *a0) {

    extern void (*D_801A47A8[])(void);
    D_801A47A8[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_80181720(a0);
    }
}


extern u8 D_801A479C[];

void func_801815A0(void *arg0) {
    u8 *work;
    s16 val;

    work = *(u8 **)((s32)arg0 + 0x20);
    *(u8 *)(work + 0x26) = 0x80;
    *(u8 *)(work + 0x25) = 0x80;
    *(u8 *)(work + 0x24) = 0x80;
    *(s16 *)(work + 0x00) = 2;
    *(s16 *)(work + 0x02) = 2;
    *(s16 *)(work + 0x28) = 0x2F0;
    *(s16 *)(work + 0x2A) = 0x100;
    *(s32 *)(work + 0x20) = (s32)D_801A479C;
    *(volatile s16 *)(work + 0x2C) = 0;
    *(u16 *)(work + 0x2C) = 0xC006;
    *(u8 *)(work + 0x27) = 0x51;
    val = 0xC00;
    *(s16 *)(work + 0x08) = 0;
    *(s16 *)(work + 0x0A) = 0;
    *(s16 *)(work + 0x0C) = 0;
    *(s16 *)(work + 0x2E) = 0;
    *(s16 *)(work + 0x30) = 0;
    *(s16 *)(work + 0x32) = 0;
    *(s32 *)(work + 0x34) = 0;
    *(s32 *)(work + 0x04) = 0xC000040;
    *(s16 *)(work + 0x1A) = val;
    *(s16 *)(work + 0x18) = val;
    (*(s16 *)((s32)arg0 + 2))++;
}


void func_80181638(void *arg0) {
    register int zr __asm__("$0");
    s32 a1;
    u16 *p;
    s32 v0;

    a1 = (s32)arg0 + zr;
    p = (u16 *)(*(s32 *)(a1 + 0x20));
    *(u16 *)((s32)p + 0x18) += 0x20;
    *(u16 *)((s32)p + 0x1A) += 0x20;
    v0 = *(s32 *)(a1 + 0x1C) + 1;
    *(s32 *)(a1 + 0x1C) = v0;
    if (v0 >= 0x80) {
        *(u16 *)(a1 + 2) += 1;
        *(s32 *)(a1 + 0x1C) = 0;
    }
}



void func_80181690(void *a0) {
        s32 v0;
        v0 = *(s32 *)((s32)a0 + 0x1C);
        v0 += 1;
        *(s32 *)((s32)a0 + 0x1C) = v0;
        if (v0 >= 0x40) {
            *(u16 *)((s32)a0 + 0x2) += 1;
        }
    }


extern void func_801292C8(u8 *a0);

void func_801816C4(u8 *a0) {
    u8 *a1 = *(u8 **)(a0 + 0x20);

    *(u16 *)(a1 + 0x18) = *(u16 *)(a1 + 0x18) - 0x100;
    *(u16 *)(a1 + 0x1A) = *(u16 *)(a1 + 0x1A) - 0x100;
    if (*(s16 *)(a1 + 0x18) <= 0 || *(s16 *)(a1 + 0x1A) <= 0) {
        func_801292C8(a0);
    }
}


INCLUDE_ASM("asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC", func_80181720);


extern void (*D_801A47C4[])(void);

void func_8018187C(void *a0) {
    D_801A47C4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* TU-matching types (src/shared/engine_types.h): SVECTOR, MATRIX, VECTOR.
   Adopted from the canonical header rather than re-typedef'd locally: the
   destination TU already pulls engine_core.h -> engine_types.h in at line 2,
   so local copies would be a DUPLICATE-TYPEDEF at bank time (C89 rejects a
   repeated typedef even with an identical body). Absolute path so match_one's
   standalone compile resolves it; the header guard makes it a no-op in the TU.
   Same idiom as the neighbouring draft func_8017FF60. */
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s32 rand(void);
extern s32 D_801A47B8;
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801818B8(s32 arg0) {
    s32 p;
    s32 tmp;
    s32 t2, t3, t4, t5;
    s32 rem128;
    s32 signed_rem;
    SVECTOR sv;
    MATRIX m;
    VECTOR v;

    p = *(s32 *)(arg0 + 0x20);
    *(s32 *)(p + 0x20) = (s32)&D_801A47B8;
    *(u8 *)(p + 0x27) = 0x52;
    *(u16 *)(p + 0x28) = 0x2D0;
    *(u16 *)(p + 0x2A) = 0x100;

    tmp = rand() % 0x1000 + 0x800;
    *(u16 *)(p + 0x1A) = tmp;
    *(u16 *)(p + 0x18) = tmp;

    t2 = rand();
    rem128 = t2 % 128;

    t3 = rand();
    if (!(t3 & 1)) {
        signed_rem = -rem128 - 0x300;
    } else {
        signed_rem = rem128 - 0x300;
    }
    sv.vx = signed_rem;

    t4 = rand();
    sv.vy = t4 % 0x1000;

    sv.vz = 0;
    v.vy = 0;
    v.vx = 0;

    t5 = rand();
    v.vz = -0x60000 - ((t5 % 4) << 16);

    func_80049CAC((s32)&sv, (s32)&m);
    func_800484EC((s32)&m, (s32)&v, arg0 + 0x10);

    *(s32 *)(arg0 + 0x1C) = 0x2D;
    *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
}


extern void func_801292C8(u8 *a0);
extern s32 func_80181AAC(s32 a0, s32 a1, s32 a2);
extern u8 D_800D3918[];

void func_80181A08(s32 arg0) {
    s32 var;

    if (*(s16 *)(arg0 + 0xA) >= 0x10) {
        func_801292C8((u8 *)arg0);
        return;
    }
    if (func_80181AAC(arg0, (s32)D_800D3918, 0x11) & 0x6000) {
        func_801292C8((u8 *)arg0);
        return;
    }
    var = *(s32 *)(arg0 + 0x1C) - 1;
    *(s32 *)(arg0 + 0x1C) = var;
    if (var < 0x23) {
        *(s32 *)(arg0 + 0x14) += 0x10000;
    }
}



extern void func_8012931C(struct vec *a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

/* a0 = actor/entity base (struct vec-compatible; s16 fields at +6/+A/+E, s32 flag/vel at +0x14),
 * a1 = s16[3] offset vector, a2 = mode passed through to func_8012CEB0.
 * Same family as func_8012CC88 (src/ov_SC02_027/ov_SC02_027_jr_8012ACE0.c etc) but the
 * position-integration step is a real call to func_8012931C instead of being inlined. */
s32 func_80181AAC(s32 a0, s32 a1, s32 a2) {
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16*)(a0 + 0x06);
    sp10.vy = *(u16*)(a0 + 0x0A);
    sp10.vz = *(u16*)(a0 + 0x0E);
    sp10.vx += *(u16*)(a1 + 0);
    sp10.vy += *(u16*)(a1 + 2);
    sp10.vz += *(u16*)(a1 + 4);

    func_8012931C((struct vec *)a0);

    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a1 + 0);
    sp18.vy += *(u16*)(a1 + 2);
    sp18.vz += *(u16*)(a1 + 4);

    v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, a2);

    sp18.vx -= *(u16*)(a1 + 0);
    sp18.vy -= *(u16*)(a1 + 2);
    sp18.vz -= *(u16*)(a1 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;

    if (v0 & 0x6000) {
        *(s32*)(a0 + 0x14) = 0;
    }
    return v0;
}


typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
} S80190C84L;

extern s32 func_8012BE54(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_80181C00(s32 arg0) {
    S80190C84L sp;
    s32 counter;
    s32 divisor;

    counter = *(s32 *)(arg0 + 0x1C);
    divisor = *(s16 *)(arg0 + 0xFC);
    *(s32 *)(arg0 + 0x1C) = counter + 1;
    if (counter % divisor == 0) {
        if (func_8012BE54(arg0) < 0x240001) {
            sp.f0 = *(u16 *)(arg0 + 0x06);
            sp.f2 = *(u16 *)(arg0 + 0x0A);
            sp.f4 = *(u16 *)(arg0 + 0x0E);
            sp.f6 = 0x1FB;
            sp.f8 = *(u16 *)(arg0 + 0x70);
            sp.fA = 0;
            sp.fE = *(u16 *)(*(s32 *)(arg0 + 0x68) + 0x0C);
            sp.f10 = *(s32 *)(arg0 + 0xDC);
            sp.fC = 0x7FFF;
            func_8012C51C(&sp, arg0);
        }
    }
}


#include "common.h"


extern void func_8012EFB8(s32 a0);
extern void func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80181CDC(s32 a0, s32 a1) {
    register s32 zr __asm__("$0");
    SVec_80181CDC pos;
    SVec_80181CDC out;
    s32 val;
    s32 lvl;
    s32 t;
    s32 x;
    s32 n;
    s32 y;
    s32 arg;

    val = 0x7F;
    arg = a1;
    pos.vx = *(s16 *)(a0 + 0x6);
    pos.vy = *(s16 *)(a0 + 0xA);
    pos.vz = *(s16 *)(a0 + 0xE);
    ((void (*)(void *, void *))func_8012EFB8)(&pos, &out);
    lvl = 7;

    t = out.vx;
    if (t < 0) { t = -t; }
    if (t >= 0xC9) { return 0; }

    if (out.vy >= 0) {
        if (out.vy >= 0xA1) { return 0; }
        __asm__ __volatile__("");
    } else {
        if (-out.vy >= 0xA1) { return 0; }
    }

    val -= ((((s32 (*)(s32))func_8012BD14)(a0) - 0x1000) * 0x7F) / 0xFF000;
    x = out.vx;
    n = lvl + x / 0x19;
    lvl = n + zr;
    if ((s16)n < 0) { lvl = 0; }
    else if ((s16)n > 0xF) { lvl = 0xF; }
    y = (lvl << 8) | 0x3000;
    func_8002D4C8(arg & 0xFFFF, (val | y) & 0xFFFF);
    return 1;
}


extern void (*D_801A9F5C[])(void);

void func_80181E40(void *a0) {
    D_801A9F5C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8018239C(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801823F4(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181E7C(s32 a0) {
    extern u8 D_801A9F10[];
    extern u8 D_801A9F1C[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_8018239C(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801A9F10, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801A9F1C);
        func_801823F4(a0);
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
extern void func_801823F4(s32 arg0);
extern void func_80182470(void *arg0);

void func_80181F78(s32 arg0) {
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
            func_801823F4(arg0);
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
    func_80182470((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_801823F4(s32 arg0);
extern void func_80182470(void *arg0);

void func_80182208(s32 arg0) {

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
        func_801823F4(arg0);
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
    func_80182470((void *)arg0);
}



/* func_8018239C — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_8018239C(s32 arg0) {
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

void func_801823F4(s32 arg0) {
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



/* func_80182470 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_80182470(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_801824B4(s32 a0, u16 *a1, s16 a2) {
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





