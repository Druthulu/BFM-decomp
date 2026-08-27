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
extern u8 D_80187A34;
extern u8 D_801879A4;
extern u8 D_80187980;
extern u8 D_8018795C;
extern u8 D_80187A10;
extern u8 D_801879EC;
extern u8 D_801879C8;
extern u8 D_80187938;
extern void func_80145934(void);
extern u8 D_80187AC4;
extern u8 D_80187AA0;
extern u8 D_80187A7C;
extern u8 D_80187A58;
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
extern unsigned char D_80186EBC[];
extern unsigned char D_80186EEC[];
extern unsigned char D_80186F3C[];
extern unsigned char D_80186F6C[];
extern unsigned char D_80186F9C[];
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
extern void (*D_80186FEC[])(void *);
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
extern s32 D_801870B4[];
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
extern u8 D_8018713C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80187144;
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
extern int D_801CA558;
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
extern s32 D_801CA55C;
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
extern s32 D_80187174;
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
extern void (*D_8018721C[])(void);
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
extern void (*D_80187240[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80187230;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80187254[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80187260[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80187270[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80187288[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80187278;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018729C[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801872B8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801872A8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801872CC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801872E0[])(void);
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
extern s32 D_801872F4;
extern void (*D_8018731C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801872FC;
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
extern int (*D_80187368[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018736C[])(void);
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
extern unsigned short D_801877D0[];
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
extern void (*D_801877E0[])(void);
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
extern int D_801CA590;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80187808[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801877E8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801877F8;
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
extern void (*D_80187848[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80187850[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018781C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018785C[])(void);
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
extern u8 D_8018782C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801CA598;
extern s32 D_801CA5A4;
extern s32 D_801CA5A8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187898[])(s32 *);
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
extern s32 D_8018786C[];
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
extern s32 D_801CA5A0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80187AE8[])(void);
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
extern char D_80187908[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80187B8C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80187CE0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80187AFC;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80187CE8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80187B0C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80187B2C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80187CF0[])(void);
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
extern void (*D_80187D18[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80187D24[])(void);
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
extern void (*D_80187B98[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80187DC8;
extern void func_8015D380(s32 a0);
extern unsigned char D_80186EAC[];
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
extern unsigned char D_80187DDC[];
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
extern s8 D_80187E18[];
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
extern u16 D_80187E60;
extern u16 D_80187E62;
extern u16 D_80187E64;
extern s32 D_80187E68;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80187E70;
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
extern int D_80187B7C;
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
extern unsigned int D_80187EF4[];
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
extern void (*D_80187FA4[])(void);
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
extern u16 D_80187FD4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80188038;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801CA5B0[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018805C[])(void);
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
extern int D_801CA608[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801880A4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80188094;
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
extern char D_801C9DE4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801880AC[])(void);
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
extern void (*D_80188100[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801880C8;
extern s16 D_801880FC;
extern s16 D_801880FA;
extern s16 D_801880F8;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018810C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801CA668;
extern u8 D_801CA669;
extern u8 D_801CA66A;
extern u8 D_801CA66B;
extern u8 D_801CA66C;
extern u8 D_801CA66D;
extern u8 D_801CA66E;
extern u8 D_801CA66F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018811C[])(void);
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
extern s32 D_801CA6A8;
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
extern void (*D_80188160[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801881DC[];
extern s32 D_801881FC[];
extern u8 D_80188278[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80188298[];
extern u8 D_801882B8[];
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
extern void (*D_80188354[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801883D0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C9DF4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801883DC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801883E4[])(void);
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
extern void (*D_801884AC[])(void);
extern void func_80166618(void *a0);
extern void (*D_801884BC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801884CC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801884D8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80188438[];
extern u8   D_8018844C[];
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
extern void (*D_801884F0[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801884F8[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80188500[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80188508[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80188510[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80188518[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80188520[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801885D4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801885DC[])(void);
extern void func_80169F00(void *a0);
extern char D_8018858C[];
extern char D_8018854C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80188614[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80188620[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80188668[])(void);
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
extern void (*D_801886E4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801CA9C8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801886D8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018871C[];
extern unsigned short D_80188724[];
extern unsigned short D_8018872C[];
extern unsigned char D_801CA9D0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801CA9C8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188734[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801CAB04;
extern M2C_UNK D_801CAB08;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801CAA90;
extern void (*D_80188764[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801CAB0C[];
extern u8 D_801CAB14[];
extern u8 D_801CAAC4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018876C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80188788[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80188790[])(void);
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
extern void (*D_801887F8[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018879C;
extern u8 D_801887A8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018882C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188834[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188888[])(void);
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
extern u16 D_801888BC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801888AC[];
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
extern s32 D_801888D8;
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
extern void (*D_80188950[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80188958[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80188960[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188968[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80188970[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80188978[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80188984[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80188990[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018899C[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801889AC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801889BC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801889C4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801889CC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801889D4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801889DC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801889E4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_801889EC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_801889F4[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_801889FC[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80188A04[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80188A0C[])(void);
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
extern void (*D_80188A14[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80188A1C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80188A24[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80188A2C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80188A34[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80188A3C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80188A44[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80188A4C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80188A54[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80188A5C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80188A64[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80188A6C[])(void);
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
extern void (*D_80188AB0[])(void);
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
extern M2C_UNK D_80188A74;
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
extern void (*D_80188AE0[])(void);
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
extern void (*D_80188B1C[])(void);
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
extern void (*D_80188B74[])();
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
extern void (*D_80188B84[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80188B8C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80188CF4[])();
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
extern void (*D_80188D00[])();
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
extern M2C_UNK D_801CA03C;
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
extern s16 D_801CBAD8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801CB248;
extern short D_801CBB4C;
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
extern s32 D_801CB674;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801CB69C;
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
extern s16 D_801CB658;
extern s32 func_8017A3B0(void);
extern short D_801CB694;
extern short D_801CB690;
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
extern s16 D_801CB65C;
extern u16 D_801CB6DC;
extern u16 D_801CB6DE;
extern u16 D_801CB6E0;
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
extern s16 D_801CB6D4;
extern s16 D_801CB6D6;
extern s16 D_801CB6D8;
extern s16 D_801CB6CC;
extern s16 D_801CB6CE;
extern s16 D_801CB6D0;
extern void func_8017B7A8(void);
extern s16 D_801CB6EC;
extern s16 D_801CB6EE;
extern s16 D_801CB6F0;
extern s16 D_801CB6F4;
extern s16 D_801CB6F6;
extern s16 D_801CB6F8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801CB6E4;
extern short D_801CB6E6;
extern short D_801CB6E8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801CB67C;
extern SV4 D_801CB684;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801CB6A4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801CB6A0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80188EDC[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80188EF4[])(void);
extern void func_8017C0E4(void *a0);
extern void (*D_80188F90[])(void);
extern void func_8017C180(void *a0);
extern void (*D_80188F98[])(void);
extern void func_8017C1BC(void *a0);
extern void (*D_80188FA0[])(void);
extern void func_8017C1F8(void *a0);
extern void (*D_8018927C[])(void);
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


extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s32 D_801892A0;

extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80129374(s32 a0, s32 a1);
extern s32 func_8017E708(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017E68C(s32 a0);

void func_8017E4E4(s32 arg0)
{
    s32 v1;
    s16 dx, dy;
    s32 v0;
    s32 dist2, rem, vol;
    u16 *p;
    u16 t;

    v1 = D_80126B5E - *(u16 *)(arg0 + 0x6);
    dx = v1;
    if ((s16)v1 < 0) dx = -v1;

    v1 = D_80126B66 - *(u16 *)(arg0 + 0xE);
    dy = v1;
    if ((s16)v1 < 0) dy = -v1;

    if (dx < 0x201 && dy < 0x201) {
        v0 = *(s32 *)(arg0 + 0x1C);
        *(s32 *)(arg0 + 0x1C) = v0 + 1;
        if (v0 & 1) {
            s32 s0 = func_80132EF4(arg0, 0x22);
            if (s0 != 0) {
                func_80129374(s0, arg0);
                *(s16 *)(s0 + 0x34) = 0x4000;
            }
        }
        if (func_8017E708(arg0, (s32) &D_801892A0) != 0) {
            p = &D_80126B96;
            t = *p;
            D_80126B98 = 0xC;
            *p = t | 0x4000;
        }
        if ((*(s32 *)(arg0 + 0x1C) & 3) == 0) {
            dist2 = dx * dx + dy * dy;
            if (dist2 <= 0x30000) {
                rem = 0x30000 - dist2;
                vol = rem * 127 / 0x30000;
                func_8002D4C8(0x644, (vol | 0x1000) & 0xFFFF);
                *(s16 *)(arg0 + 0xFC) = 1;
            } else {
                func_8017E68C(arg0);
            }
        }
    } else {
        func_8017E68C(arg0);
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017E68C(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        func_8002D4C8(4, 0x644);
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



extern void (*D_801892B0[])(void);

void func_8017E6CC(void *a0) {
    D_801892B0[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
    /* 0x6 */ u16 w;
} Vec4h_8017E708;

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

s32 func_8017E708(s32 a0, s32 a1) {
    Vec4h_8017E708 p1;
    Vec4h_8017E708 p2;
    s32 result;

    p1.z = 0;
    p2.z = *(u16 *)(a1 + 0xE);
    p1.x = p2.x = *(u16 *)(a1 + 0x4);
    p1.y = p2.y = (s16)*(u16 *)(a1 + 0x8) >> 1;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = (s16)*(u16 *)(a1 + 0xA) >> 1;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.x = p2.x = *(u16 *)(a1 + 0x6);
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = (s16)*(u16 *)(a1 + 0x8) >> 1;
    result = func_8012DEB8(a0, (s32)&p1, (s32)&p2) != 0;

save:
    return result;
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_801892A0;

void func_8017E7FC(void *a0)
{
    register void *s0 __asm__("$16") = a0;
    s32 v0;
    s32 arr[3];

    if (((func_800291B4(0xCD) & 0xFF) != 0) ||
        (v0 = ((s32 (*)(void))func_8012C1B8)(),
         (*(s32 *)((s32)s0 + 0x20) = v0),
         v0 == 0)) {
        func_8012CAE4(s0);
        return;
    }
    func_8001C2C4(v0);
    *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) = 0x400;
    func_8012B2CC((s32)s0);
    arr[1] = 0;
    arr[0] = 0;
    arr[2] = 0xC0000;
    func_8012B14C((s32)s0, (s32)arr);
    *(s32 *)((s32)s0 + 0x58) = (s32)&D_801892A0 | 0x40000000;
    *(s16 *)((s32)s0 + 0x5C) = 0x800;
    ((void (*)(void *))func_8012AD50)(s0);
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 D_801892C8;
extern s32 D_801A7F4C;
extern s32 D_80126B60;
extern s32 D_80126B64;
extern s32 D_801892FC;
extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 a0);
extern s32 func_800291DC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_800291C8(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern u8 D_80126B5C;

void func_8017E8B0(void *a0) {
    s32 v1;

    if (func_8012C354((s32)a0, (s32)&D_801892C8) == 0) {
        return;
    }
    if ((u32)func_80029504() >= 0x14 || (func_80029178(0xDF) & 0xFF) == 0 || (func_800291DC(0xA) & 0x40) == 0) {
        func_8012C218(a0);
        return;
    }
    *(u16 *)((s32)a0 + 2) = 1;
    func_8012B23C((s32)a0);
    func_8012A828((s32)a0, (s32)&D_801A7F4C);
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)((s32)a0 + 4) = *(s32 *)&D_80126B5C;
    *(s32 *)((s32)a0 + 8) = D_80126B60;
    *(s32 *)((s32)a0 + 0xC) = D_80126B64;
    *(u16 *)((s32)v1 + 0x12) = 0xF00;
    func_8012B2CC((s32)a0);
    func_8012B1B4((s32)a0, (s32)&D_801892FC);
    *(s32 *)((s32)a0 + 0x1C) = 6;
    *(s32 *)((s32)a0 + 4) += *(s32 *)((s32)a0 + 0x10);
    *(s32 *)((s32)a0 + 0xC) += *(s32 *)((s32)a0 + 0x18);
    func_80143970((s32)a0);
    func_800291C8(0xA, 0x1011);
    func_80029514(0x14);
    func_80029124(0xE1, 1);
}



extern void (*D_80189308[])(void);

void func_8017E9EC(void *a0) {
    D_80189308[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017EA28(void *a0) {
    if (--*(s32 *)((s32)a0 + 0x1C) == 0) {
        *(s32 *)((s32)a0 + 0x1C) = 0x50;
        *(s16 *)((s32)a0 + 2) = 2;
    }
}


extern s32 func_8012CBCC(s32 arg0);
extern void func_8012C218(void *arg0);

void func_8017EA54(s32 arg0)
{
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");

    s0 = arg0;
    v1 = func_8012CBCC(s0);
    v0 = v1 & 0x6000;
    if (v0 != 0) {
        *(s16 *)(s0 + 0x16) = -4;
    }
    v0 = v1 & 0x8000;
    if (v0 != 0) {
        v0 = *(s32 *)(s0 + 0x4);
        v1 = *(s32 *)(s0 + 0x10);
        a0 = *(s32 *)(s0 + 0x14);
        a1 = *(s32 *)(s0 + 0x18);
        v0 = v0 + v1;
        *(s32 *)(s0 + 0x4) = v0;
        v0 = *(s32 *)(s0 + 0x8);
        v1 = *(s32 *)(s0 + 0xC);
        v0 = v0 + a0;
        v1 = v1 + a1;
        *(s32 *)(s0 + 0x8) = v0;
        *(s32 *)(s0 + 0xC) = v1;
    }
    v0 = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v0;
    if (v0 == 0) {
        func_8012C218((void *)s0);
    }
}


extern s32 func_80029504(void);
extern s32 D_801CBAC4;
extern void func_800D06CC(void);
extern void func_8013CB84(void);
extern void func_800D06E8(void);

void func_8017EAE8(void) {
    s32 temp = func_80029504();

    switch (D_801CBAC4) {
    case 0:
        if ((u32)(temp - 0x85) < 2U) {
            func_800D06CC();
        }
        D_801CBAC4++;
        break;
    case 1:
        func_8013CB84();
        func_800D06E8();
        break;
    }
}



extern void (*D_80189314[])(void);

void func_8017EB74(void *a0) {
    D_80189314[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_8017EBB0(s32 *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_8017EBD0);

// @class: struct + regalloc(local-alloc density)
// @stuck: none — MATCH (186 ins, relocation-masked)
//
//   WHAT IT IS: a screen-space line walker. It steps `cur.vx` by 0x40 per iteration
//   from p0 towards p1, linearly interpolating vy/vz, and for each step transforms the
//   two edge points (y-4 and y+4 of the previous and current sample) through
//   func_8012EF70 (a GTE perspective transform whose return is the GTE FLAG register).
//   The `& ~0x1000` drops FLAG bit 12 (IR0 saturated) and keeps every other error bit;
//   all four corners must come back clean before the quad is drawn via func_8017EF80.
//
//   TYPE: SVEC_8017EC98 is layout-identical to the fleet's `SVECTOR_8016E7C8`
//   (`{ short vx, vy, vz, pad; }`, 8 bytes / align 2). A fresh tag is used so the draft
//   splices into ov_SC03_002_jr_8017D604.c without redefining the shared typedef; the
//   banker may substitute SVECTOR_8016E7C8 verbatim. Align 2 + size 8 is what makes
//   every whole-struct assignment come out as the inline lwl/lwr + swl/swr pair
//   (move_by_pieces_ninsns(8,2)=4 >= MOVE_RATIO 2 -> mips movstrsi, cookbook §38 family).
//
//   THE ONE NON-OBVIOUS LEVER (cost 7 mismatches -> 0):
//   Do NOT hoist the stepped abscissa into a local. Writing
//       s32 x = cur.vx;  ... (x - p0->vx) ... (x >= p1->vx)
//   is value-identical and gives the same 186 instructions, but it leaves the first
//   interpolation's `p0->vy` and `p0->vx` pseudos with the register pair SWAPPED
//   ($a1/$a2) relative to the target — a clean REGALLOC-PERM.
//   Mechanism (local-alloc.c:1579 qty_compare, pri = floor_log2(R)*R*size/(death-birth)):
//     * qty{p0->vy, addu-result} is tied by combine_regs and carries R=8, span=19  -> 12631
//     * qty{p0->vx}                                        carries R=6, span=11 -> 10909
//     so the vy qty allocates first and takes the lower free reg ($a1). In the vz block
//     two zero-byte `(use accum)` insns land inside the window, span=23 -> 10434, so
//     there the vx qty wins and the pair comes out right — which is why only the FIRST
//     block diffed. Reading `cur.vx` in place instead of through a user variable removes
//     the reg/v pseudo, re-shapes the qty birth order, and both blocks land on the
//     target's assignment with no pin and no zero-byte asm.
//   (register pins on $a1/$a2 also reach MATCH but cost §72/§80 side effects; the
//   pin-free form above is the one banked.)
#include "common.h"

/* identical layout to SVECTOR_8016E7C8 (src/shared/engine_types.h) */
typedef struct { short vx, vy, vz, pad; } SVEC_8017EC98;

void func_8017EC98(SVEC_8017EC98 *p0, SVEC_8017EC98 *p1) {
    /* conform to the TU's file-scope canon (`extern void func_8012EF70(s32, s32);`)
       and read the GTE flag through a cast at the call — the §138 "use is cast" lane. */
    extern void func_8012EF70(s32 a0, s32 a1);
    extern void func_8017EF80(void *a0, void *a1, void *a2, void *a3);

    SVEC_8017EC98 prev;
    SVEC_8017EC98 cur;
    SVEC_8017EC98 lo0;
    SVEC_8017EC98 lo1;
    SVEC_8017EC98 sv0;
    SVEC_8017EC98 sv1;
    SVEC_8017EC98 sv2;
    SVEC_8017EC98 sv3;
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
                func_8017EF80(&sv0, &sv1, &sv2, &sv3);
            }
        }
    } while (more);
}







void func_8017EF80(void *a0, void *a1, void *a2, void *a3)
{
    extern void func_80016ED4(void *a0);
    extern s32 D_8018931C;
    extern s32 D_80189320;
    extern s32 D_80189324;
    extern s32 D_80189328;

    Prim_8016E7C8 prim;

    prim.v[0] = *(SVECTOR_8016E7C8 *)a0;
    prim.v[1] = *(SVECTOR_8016E7C8 *)a1;
    prim.v[2] = *(SVECTOR_8016E7C8 *)a2;
    prim.v[3] = *(SVECTOR_8016E7C8 *)a3;
    prim.f0 = D_8018931C;
    prim.f1 = D_80189320;
    prim.f2 = D_80189324;
    prim.f3 = D_80189328;
    prim.f4 = 0x808080;
    prim.f5 = 0;
    prim.f6 = 0x50;
    func_80016ED4(&prim);
}


extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 rand(void);

void func_8017F068(void *a0, void *a1, s16 a2, s16 a3)
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
                rot[1] = a2 + (s16)((rand() & 0x7F00) >> 5);
                rot[2] = 0;
                RotMatrixYXZ(rot, mtx);
                ApplyMatrixSV(mtx, a1, rot);
                *(s16 *)(ent + 6) = *(s16 *)a0 + rot[0];
                *(s16 *)(ent + 10) = *(s16 *)((s8 *)a0 + 2) + rot[1];
                *(s16 *)(ent + 14) = *(s16 *)((s8 *)a0 + 4) + rot[2];
                *(s32 *)(ent + 0x10) = (s32)rot[0] << 12;
                *(s32 *)(ent + 0x14) = (s32)rot[1] << 12;
                *(s32 *)(ent + 0x18) = (s32)rot[2] << 12;
            }
            i = i + 1;
        } while (i < a3);
    }
}



extern void (*D_8018932C[])(void);

void func_8017F1C4(void *a0) {
    D_8018932C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017F200(s32 arg0) {

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


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_8017F290);

void func_8017F304(s32 arg0)
{
    extern u8 * func_8012913C(s32 a0);
    typedef struct {
        u32 unk00; u32 unk04; u32 unk08; u32 unk0C; u32 unk10; u32 unk14;
        u16 unk18;
    } Rec_80189334;
    extern Rec_80189334 D_80189334[];
    Rec_80189334 *src;
    u8 *temp;

    src = &D_80189334[arg0];
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



extern void (*D_801893E8[])(void);

void func_8017F3A4(void *a0) {
    D_801893E8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8001CC3C(s32, s32, s32, s32);
extern s32 D_801893DC;

void func_8017F3E0(void *a0)
{
    s32 *s1 = (s32 *)a0;
    s32 *s0;
    s32 v0;
    s32 v1;

    s0 = M2C_FIELD(s1, s32 *, 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)((s32)s0, (s32)&D_801893DC, 0x240, 0x1D0);

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


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_8017F464);


extern void (*D_80189400[])(void);

void func_8017F4C4(void *a0) {
    D_80189400[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8001C810(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_801893F0;
extern s32 D_801A74D4;

void func_8017F500(s32 a0) {
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

    func_8001C810(s0, (s32)&D_801A74D4);
    *(s32 *)(s0 + 0x28) = 0xFA00FA;
    *(s32 *)(s0 + 4) |= 0x8000;
    *(u8 *)((s8 *)a0 + 0x75) = 2;
    *(s32 *)(a0 + 0x58) = (u32)&D_801893F0 | 0x40000000;
    *(u16 *)(a0 + 0x5C) = 0xC800;
    func_8012AD50((void *)a0);
}


void func_8017F5B4(void) {
}


extern void (*D_80189438[])(void);

void func_8017F5BC(void *a0) {
    D_80189438[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8017F914(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801CB920 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_8017F5F8(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_8017F5F8 D_801CB920[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_8017F5F8 *p = &D_801CB920[i];

            p->unk16 = i;
            func_8017F914(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}


/* func_8017F688 — byte-verified twin of func_8017D77C (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c:4271),
 * found via §136e/S34 magic-word grep on the `AAA32294` instruction bytes (the
 * D_800AF630+0xA3AA far-offset lhu). This is one of the 10 members of the family
 * (all 0x23C bytes / 143 ins; grep the AAA32294 bytes across asm/ to enumerate them) --
 * func_8017D77C is the only one already banked; all others (incl. this one) were
 * still nonmatching, so this body was derived by remapping func_8017D77C's symbols:
 *   func_8017D77C -> func_8017F688      D_801E6F58   -> D_801CB920
 *   func_8017D9B8 -> func_8017F8C4      func_8017DAC4 -> func_8017F9D0
 *   Ent_8017D6EC  -> Ent_8017F688 (own function-suffixed typedef -- same 0x24-stride
 *                     shape as the TU's Ent_8017D6EC_8017F5F8 at TU:3319-3325, but
 *                     given a fresh name/no shared tag so splicing this in below that
 *                     file-scope typedef can't hit the C89 duplicate-typedef error, S33).
 * func_8017F9D0 is already banked in THIS TU (TU:3426) as `void (void *arg0)`,
 * matching the direct call below with no cast needed. func_8017F8C4 has no
 * declaration anywhere but INCLUDE_ASM stubs, so it is declared directly as
 * `void (void *)` (no idiom-9 cast needed, unlike the twin's func_8017D9B8
 * which was `void (void)`).
 */

extern u8 D_80078EB1;
extern u8 D_80078E78[];
extern u8 D_800AF630[];
extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8017F8C4(void *arg0);
extern void func_8017F9D0(void *arg0);

/* same shape as the TU's own Ent_8017D6EC_8017F5F8 (TU:3319-3325), own name to avoid
 * the C89 duplicate-typedef clash (S33); match_one compiles this file standalone (no
 * TU context), so the typedef must be repeated here regardless. */


void func_8017F688(s32 *arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_8017F688 D_801CB920[];
    u8 *m = D_800AF630;
    u8 *q = D_80078E78;
    Ent_8017F688 *p;
    Ent_8017F688 *r;
    s32 i;
    s32 j;
    s32 n;
    s32 h;
    s32 c;
    s32 e;

    if (D_80078EB1 >= 9) {
        n = 0;
        for (j = 0; j < 4; j++) {
            r = &D_801CB920[j];
            if (r->unk1C == 0) {
                n++;
            }
        }
        if (n == 0) {
            func_8012AD44(arg0, 0);
            return;
        }
    }

    i = 0;
    do {
        p = (Ent_8017F688 *)((s32)D_801CB920 + i * 0x24);
        if (p->unk1C == 0) {
            if (*(s16 *)((s32)p + 0xC) > 0x400) {
                if (*(s32 *)((s32)p + 0x18) != 0) {
                    *(s32 *)((s32)p + 0x18) = *(s32 *)((s32)p + 0x18) - 1;
                } else {
                    *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
                }
            } else {
                *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
            }
            if (*(s16 *)((s32)p + 0xC) > 0x800) {
                *(s16 *)((s32)p + 0xC) = 0;
            }
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 64) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x4) = c;
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 256) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x8) = c;
            if ((*(u16 *)(m + 0xA3AA) & 1) == 0) {
                e = *(u16 *)((s32)p + 0xE) + 1;
                *(u16 *)((s32)p + 0xE) = e;
                if ((s16)e >= 0x40) {
                    *(s16 *)((s32)p + 0xE) = 0;
                }
            }
            h = *(s16 *)((s32)p + 0xC);
            if (h == 0) {
                p->unk1C = 1;
            } else if (h > 0x555) {
                if (*(s32 *)((s32)p + 0x20) == 0) {
                    *(s32 *)((s32)p + 0x20) = 1;
                    if (q[0x39] < 9) {
                        func_8017F8C4(p);
                    }
                }
            }
            func_8017F9D0(p);
        }
        i++;
    } while (i < 4);
}




/* func_8017F8C4 - iterate through 4-entry array, call func_8017F914 if any unk1C is non-zero */

extern void func_8017F914(void *arg0);




void aF8017F8C4(void) __asm__("func_8017F8C4");
void aF8017F8C4(void)
{

    extern Ent_8017D6EC D_801CB920[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801CB920[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_8017F914(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_8017F914(void *arg0) {

    extern void (*D_80189408[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_80189408;
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




/* func_8017F9D0 — build a 4-vertex SVECTOR quad from an 8-u16 source record,
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

void func_8017F9D0(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_8017F9D0 prim;
    Prim_8017DAC4_8017F9D0 *q;
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



extern void (*D_8018962C[])(void);

void func_8017FAE8(void *a0) {
    D_8018962C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017FB24(s32 param_1)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32, s32);
    extern void func_8012A828(s32, s32);
    extern s32 func_801788B8(s32, s32);
    extern u8 D_801BFCB4[];
    extern void (*D_80189440[])(void);
    extern u16 D_80189540[];
    extern void func_8017FCD0(void);
    s32 v0;

    if ((func_80029178(0xF0) & 0xFF) == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        return;
    }
    func_8001C214(v0, (s32)D_801BFCB4);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = 0xE00;
    func_8012A828(param_1, (s32)&D_80189440);
    *(s16 *)(*(s32 *)(param_1 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)(param_1 + 0x58) = (s32)D_80189540 | 0x40000000;
    *(s16 *)(param_1 + 0x5C) = 0x800;
    *(s32 *)(param_1 + 0xD4) = func_801788B8(param_1, (s32)func_8017FCD0);
    *(s16 *)(param_1 + 0x2) = *(s16 *)(param_1 + 0x2) + 1;
}


void func_8017FBF0(void) {
}

extern s32 D_80189550[];
extern s32 func_800291B4(s32 arg);
extern u8 D_8018959C[];
extern void (*D_80189614)(void);
extern void func_800291A0(s32, s32);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_8017FBF8(arg0)
void *arg0;
{
    s32 a1;
    if ((func_800291B4(0x40) & 0xFF) == 1) {
        func_800291A0(0x40, 0x2);
    }
    if (*(s16 *)((char *)arg0 + 0x10A) == 0) {
        *(s16 *)((char *)arg0 + 0x10A) = 1;
        *(s32 *)((char *)arg0 + 0x58) = (s32)&D_80189550 | 0x40000000;
        a1 = (s32)&D_8018959C;
    } else {
        a1 = (s32)&D_80189614;
    }
    func_80178CBC((s32)arg0, a1);
    *(u16 *)((char *)arg0 + 2) += 1;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017FC90(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_8017FCD0(void *a0)
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



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_80180144(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017FD44(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_80180144, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017FD94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_80180748(void);
extern void func_800167B8(s32 a0);

s32 func_8017FDB8(s32 a0) {
    func_80180748();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern void func_801801CC(void *a0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern s32 D_80126B9C;
extern u16 D_801270C0;

s32 func_8017FDFC(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_801801CC, 0x1000000);
    D_801270C0 = 2;
    D_80126B9C = D_80126B9C | 0x4000000;
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 0xA;
    return 0;
}



extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);

s32 func_8017FE6C(s32 a0) {

    extern s16 D_800B9A0A;
    s16 s0;

    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_800D1E28();
        s0 = D_800B9A0A;
        if (s0 != 0x1000 || (s16)func_800D1D94() != s0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017FF1C(void) {
        func_800D1EBC();
    }



extern void func_800D1E28(void);

s32 func_8017FF3C(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;

    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }

    return 0;
}


extern s32 func_800291B4(s32 arg);
extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017FF90(s32 param_1) {
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



extern void func_800D06CC(void);
extern s32 D_8012704C;

void func_80180014(void) {
    func_800D06CC();
    D_8012704C = 1;
}



extern void (*D_8018963C[])(void);

void func_80180040(void *a0) {
    D_8018963C[*(u8 *)((s32)a0 + 0x15)]();
}


extern void (*D_80189644[])(void);

void func_8018007C(void *a0) {
    D_80189644[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018964C[])(void);

void func_801800B8(void *a0) {
    D_8018964C[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80189658[])(void);

void func_801800F4(void *a0) {
    D_80189658[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_80127050;
    void func_80180130(void) {
        D_80127050 = 1;
    }



extern void (*D_8018978C[])(void);

void func_80180144(void *a0) {
    D_8018978C[*(u8 *)((s32)a0 + 0x214)]();
}


void func_80180180(s32 *a0) {
        *(u8 *)((s32)a0 + 0x214) = *(u8 *)((s32)a0 + 0x214) + 1;
    }


extern void func_80175414(s32 _arg0);
    extern void func_8016F0E4(void);
    extern void func_80165770(void);
    void func_80180194(s32 arg0) {
        func_80175414(arg0);
        ((s32 (*)(s32))func_8016F0E4)(arg0);
        ((void (*)(s32))func_80165770)(arg0);
    }



extern void (*D_80189794[])(void);

void func_801801CC(void *a0) {
    D_80189794[*(u8 *)((s32)a0 + 0x214)]();
}


void func_80180208(void *a0) {
        *(u8 *)((s32)a0 + 0x214) += 1;
    }


extern void func_8016F0E4(void);
    void func_8018021C(void) {
        ((s32 (*)(void))func_8016F0E4)();
    }


extern void (*D_801897EC[])(void);
extern void func_801805B0();

void func_8018023C(int param_1)
{
    D_801897EC[*(unsigned char *)(param_1 + 0x216)]();
    func_801805B0(param_1, *(s16 *)(param_1 + 0x20C));
    return;
}


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_80180290);

INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_801802F4);

#include "common.h"

/* func_80180378 — per-frame tick for the SC03 cutscene actor at +0x200.
 *
 * Counts the actor's 0x200 timer down; while it has not underflowed past 0 the
 * frame just re-runs the two idle helpers and returns. On the frame the counter
 * reaches -1 the burst fires: reload the handler table, re-bind the actor to its
 * script, read the actor's world position into a local SVECTOR, then emit six
 * particle bursts from func_8017F068, walking the local vector between them
 * (y -0x60, y -0x60, z -0x60, y +0x60, y +0x60) and re-rolling the per-burst
 * amplitude in D_80189828 each time. Finally kick the six 0x8017F304 effects,
 * the 0x842 sound, and hand the actor to func_80171990.
 *
 * Two levers, both required (this file's house style, §194-E neighbour
 * func_80180570 + func_801806F0):
 *  (1) func_80147A84 IS CALLED WITH NO ARGUMENT — the jal's delay slot is `nop`,
 *      not `move $a0,$sN` (§263: an arg-register copy in a stolen delay slot is
 *      an ARITY fact). The TU prototypes it with one s32, so the call goes
 *      through the TU's cast-the-function-pointer idiom to drop the parameter.
 *  (2) D_80189828 IS ADDRESSED THROUGH A POINTER LOCAL, not by name. Written as
 *      `D_80189828 = ...` gcc materialises a fresh `lui $at` for every one of the
 *      six stores (+6 instructions) even though it already keeps &D_80189828 in
 *      $s0 for the $a1 argument. A `s16 *pv = &D_80189828;` gives the store and
 *      the argument one allocno, which is what the target's `sh $v0, 0x0($s0)`
 *      (and the final `sh $v0, 0x0($a1)`) actually is.
 */

extern void func_80147A84(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_8013C9C4(void *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void func_80015978(s32 a0, s32 *a1);
extern s32  rand(void);
extern void func_8017F068(void*, void*, s16, s16);
extern void func_8017F304(s32 arg0);
extern void func_80147324(s32 a0);
extern s32  func_80171990(u8 *a0);

extern u8  D_80189804[];
extern u8  D_801897FC[];
extern s16 D_80189828;

void func_80180378(s32 arg0) {
    u16 pos[4];
    s16 *pv;

    if (--*(s32 *)(arg0 + 0x200) != -1) {
        ((void (*)(void))func_80147A84)();
        func_801473EC((s32 *)arg0);
        return;
    }

    func_8013C9C4(D_80189804);
    func_80172358((u8 *)arg0, D_801897FC);
    func_80015978(arg0 + 4, (s32 *)pos);
    pv = &D_80189828;

    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xD50, 8);
    pos[1] -= 0x60;
    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xD50, 8);
    pos[1] -= 0x60;
    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xF00, 8);
    pos[2] -= 0x60;
    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xF00, 8);
    pos[1] += 0x60;
    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xF00, 8);
    pos[1] += 0x60;
    *pv = (rand() & 0x3F) + 0x40;
    ((void (*)(void *, void *, s32, s32))func_8017F068)(pos, pv, 0xF00, 8);

    func_8017F304(0);
    func_8017F304(1);
    func_8017F304(2);
    func_8017F304(3);
    func_8017F304(4);
    func_8017F304(5);
    func_80147324(0x842);
    func_80171990((u8 *)arg0);
}


extern void func_80147060(u8*);
extern void func_80172358(u8*, u8*);
extern void func_80171928(void*);
void func_80180570(s32 a0) {

    extern u8 D_80189830;
    ((void (*)(void *))func_80147060)((void *)a0);
    ((void (*)(s32 *, s32))func_80172358)((s32 *)a0, (s32)&D_80189830);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern s32 func_8012E544(s32 a0);

void func_801805B0(s32 *a0, s32 a1) {
    s32 v0 = func_8012E544(0x19C);
    if (v0 != 0) {
        s32 t;
        *(s32 *)(v0 + 4) = a0[1];
        *(s32 *)(v0 + 8) = a0[2] + 0xFFC00000;
        t = a0[3];
        *(s16 *)(v0 + 0xFC) = a1;
        *(s32 *)(v0 + 0xC) = t;
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern u16 D_800B99DA;
extern u8 D_80189838[];
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_80013E94(void *a0, void *a1);

void func_8018061C(param_1)
int param_1;
{
    u64 vec;
    u32 out;

    func_800139C8(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), D_80189838, &vec);
    func_80013E94(&vec, &out);
    out |= 0x80000000;
    if ((D_800B99DA & 3) == 0) {
        func_80146A6C(6, (void *)param_1, *(s16 *)(param_1 + 6),
                      (s16)(*(u16 *)(param_1 + 0xA) - 0x40),
                      *(s16 *)(param_1 + 0xE), out, 0);
    }
}



extern void (*D_80189840[])(void);

void func_801806B4(void *a0) {
    D_80189840[*(u8 *)((s32)a0 + 0x216)]();
}


extern s32 func_80171990(u8 *a0);
    void func_801806F0(void) {
        ((s32 (*)(void))func_80171990)();
    }


extern int func_800D0CE0(void);
extern void func_80171928(void*);
void func_80180710(int param_1)
{
    if (((int (*)(void))func_800D0CE0)() != 0) {
        ((void (*)(int))func_80171928)(param_1);
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018979C;

void func_80180748(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018979C, 0x1000000);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_801809C8(void *a0);


void func_80180770(void) {

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
    func_8012A018((s32)func_801809C8, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_801809C8(void *a0);

void func_80180834(void) {
    extern u8  D_80126948[];
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

    D_80126954 = 0x12C;
    D_8012695C = 0x708;
    D_80126968 = 0x38;
    D_8012696A = 0x868;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0xC0;
    D_8012697A = 0;
    func_8012A018((s32)func_801809C8, 1);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_801809C8(void *a0);


void func_801808F8(void) {

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
    func_8012A018((s32)func_801809C8, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
    func_8012A094((s32)D_80126948);
    func_801809C8(D_80126948);
    D_801269E8 = 3;
}



extern void (*D_80189848[])(void);

void func_801809C8(void *a0) {
    D_80189848[*(u8 *)((s32)a0 + 0x4)]();
}


extern void func_80180AC0(s32 a0, s32 a1);
    extern void func_80180C00(s32 arg0);
    void func_80180A04(s32 param_1) {
        func_80180AC0(param_1, param_1 + 0xa0);
        ((void (*)(s32))func_80180C00)(param_1);
    }


extern void func_80180C00(s32 arg0);

extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;

void func_80180A38(void *arg0) {
    s16 *p = &D_80126940;

    if (*p < -0x130) {
        *p = -0x130;
    }
    D_80126942 = -0x282;
    D_80126944 = 0x563;
    *(s32 *)((s32)arg0 + 0x14) -= 0x10;
    *(s32 *)((s32)arg0 + 0x10) = *(s32 *)((s32)arg0 + 0x14);
    if (*(s32 *)((s32)arg0 + 0x14) < 0x12C) {
        *(s32 *)((s32)arg0 + 0x14) = 0x12C;
        *(s32 *)((s32)arg0 + 0x10) = 0x12C;
    }
    func_80180C00((s32)arg0);
}






extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_80012A60(s32 a0, s32 a1);

void aF80180AC0(void *a0, u8 *a1) __asm__("func_80180AC0");
void aF80180AC0(void *a0, u8 *a1)
{

    extern s32 D_80126B58;
    extern s16 D_80185818[];
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
        if ((s16)func_80012A60(*(s16 *)((s32)a0 + 0x1A), D_80185818[dir]) < lim) {
            *a1 = dir;
        }
    }

    *(s16 *)((s32)a0 + 0x22) = D_80185818[*a1];
}




   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80180C00(s32 param_1)
{
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;

    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    register s32 lim __asm__("$16");

    lim = *(u16 *)(param_1 + 0x9C);

    {
        s32 delta = func_80012B04(*(s16 *)(param_1 + 0x1A), *(s16 *)(param_1 + 0x22), 0x14);
        if ((s16)delta > (s16)lim) {
            delta = lim;
        } else if ((s16)delta < -(s16)lim) {
            delta = -lim;
        }
        *(s16 *)(param_1 + 0x1A) = (*(u16 *)(param_1 + 0x1A) + delta) & 0xFFF;
        *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    }

    *(s16 *)(param_1 + 0x1C) = func_80012ABC(*(s16 *)(param_1 + 0x1C), *(s16 *)(param_1 + 0x24), 4);
    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C(*(s16 *)(param_1 + 0x8),  *(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C(*(s16 *)(param_1 + 0x2A), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C(*(s16 *)(param_1 + 0x2C), *(s16 *)(param_1 + 0x32), 0x10);

    {
        s16 *p940 = &D_80126940;
        *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + *p940;
        *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + D_80126942;
        *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + D_80126944;
        func_80049CAC(param_1 + 0x18, (s32)&m1);

        m1.t[0] = *(s16 *)(param_1 + 0x28) + *p940;
        m1.t[1] = *(s16 *)(param_1 + 0x2A) + D_80126942;
        m1.t[2] = *(s16 *)(param_1 + 0x2C) + D_80126944;
    }
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


#include "common.h"

extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80183480(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012B030(u8*);
extern void func_8012B2CC(s32 a0);
extern s32 D_80189904;
extern s32 D_801BD8B0;
extern s32 D_801BDC00;
extern s32 D_80189884;

void func_80180DF4(void *arg0) {
    s32 v0;

    *(short *)((char *)arg0 + 0x2) = 5;
    func_8012E8E0((s32)arg0, (s32)&D_80189904);
    func_8012E88C((s32)arg0);
    func_8012A828((s32)arg0, (s32)&D_801BD8B0);

    v0 = (s32)&D_80189884 | 0x40000000;
    *(s32 *)((char *)arg0 + 0x58) = v0;
    *(short *)((char *)arg0 + 0x34) = 0;
    *(short *)((char *)arg0 + 0x5C) = 0x800;
    *(s32 *)((char *)arg0 + 0x1C) = 0;

    func_80183480((s32)arg0, (s32)&D_801BDC00, 0x1, 0x60);
    ((void (*)(s32))func_8012B030)((s32)arg0);
    func_8012B2CC((s32)arg0);
}


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_80180E90);

extern s32  func_80029178(s32 a0);
extern s32  func_80029504(void);
extern void func_8012CAE4(void *a0);
extern s32  func_80182D68(void *a0, void *a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32, s32);
extern void func_8012E8A8(u8 *a0);
extern s32  func_80183158(s32 arg0, s32 arg1);
extern s32  func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8018118C();

void func_80180F1C(void *a0) {

    extern s32 D_80189860;
    extern s32 D_80189874;
    extern s32 D_801BD368;
    extern s32 D_80189850;

    s32 s1;

    if ((func_80029178(0xF0) & 0xFF) != 0 ||
        (u32)(func_80029504() - 0x85) < 2) {
        func_8012CAE4(a0);
        return;
    }

    if (func_80182D68(a0, &D_80189860) == 0) {
        return;
    }

    *(s16 *)(*(s32 *)((char *)a0 + 0x68) + 0xC) = 0x7FFF;
    s1 = (s32)&D_80189874 | 0x40000000;
    *(s32 *)((char *)a0 + 0x58) = s1;
    *(s16 *)((char *)a0 + 0x5C) = 0x800;

    if (func_80183158(9, 0x12) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 2;
        func_8012A828((s32)a0, (s32)&D_801BD368);
        func_8012E88C((s32)a0);
        func_8012E8E0((s32)a0, (s32)&D_80189850);
        *(s32 *)((char *)a0 + 0x58) = s1;
        *(s16 *)((char *)a0 + 0x5C) = 0x800;
    } else {
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s16 *)((char *)a0 + 0x98) = 0;
        func_8012E8A8((u8 *)a0);
        func_8012E8E0((s32)a0, (s32)&D_80189850);
        *(s32 *)((char *)a0 + 0x58) = s1;
        *(s16 *)((char *)a0 + 0x5C) = 0;
    }

    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)func_8018118C);
}



extern void (*D_8018990C[])(void);

void func_80181054(void *a0) {
    D_8018990C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_800291B4(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800291A0(s32, s32);
extern s16 D_801A9EE0;
extern s16 D_801A9F5C;
extern s16 D_801A9FFC;

void func_80181090(s32 param_1) {
    s32 v;

    v = func_800291B4(0xDC);
    v &= 0xFF;
    func_80029124(0xDE, 1);
    if (v == 0) {
        *(s32 *)(param_1 + 0xE4) = (s32)&D_801A9EE0;
    } else if (v & 1) {
        *(s32 *)(param_1 + 0xE4) = (s32)&D_801A9F5C;
    } else {
        *(s32 *)(param_1 + 0xE4) = (s32)&D_801A9FFC;
    }
    v = v + 1;
    if ((v & 0xFF) == 0) {
        v = 2;
    }
    func_800291A0(0xDC, v & 0xFF);
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80178CBC(s32, s32);

void func_8018112C(void *arg0) {

    extern s32 D_80189850;
    extern s32 D_801BDBB8;
    extern s32 D_801898A4;
    *(short *)((char *)arg0 + 0x2) = 4;
    func_8012E8E0((s32)arg0, (s32)&D_80189850);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801BDBB8);
    ((void (*)(s32 *, s32))func_80178CBC)((s32 *)arg0, (s32)&D_801898A4);
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_8018118C(a0)
void *a0;
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 2) {
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



/* func_80181200 — guarded dispatch: ask func_80183158(9, 0x12); if it answers
 * NON-zero, run func_80180DF4 on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern s32 func_80183158(s32 arg0, s32 arg1);
extern void func_80180DF4();

void func_80181200(void *arg0) {
    if (func_80183158(9, 0x12) != 0) {
        func_80180DF4(arg0);
    }
}



/* func_80181240 — guarded dispatch: ask func_80183158(9, 0x12); if it answers
 * zero, run func_80180E90 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_80183158(s32 arg0, s32 arg1);
extern void func_80180E90(void *arg0);

void func_80181240(void *arg0) {
    if (func_80183158(9, 0x12) == 0) {
        func_80180E90(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_80181280);

void func_80181304(void *a0) {

    extern short D_801BD368;
    extern short D_80189850;
    extern u8 D_80189874;
    s32 v0 = func_80183550(a0);
    if (v0 != 0) {
        *(short *)((char *)a0 + 0x2) = 2;
        func_8012A828((s32)a0, (s32)&D_801BD368);
        func_8012E88C((s32)a0);
        func_8012E8E0((s32)a0, (s32)&D_80189850);
        *(s32 *)((char *)a0 + 0x58) = (s32)&D_80189874 | 0x40000000;
        *(short *)((char *)a0 + 0x5C) = 0x800;
    }
}


void func_8018137C(void *a0) {
    extern short D_80189850;
    extern u8 D_80189874;
    extern s32 func_80183550(s32 a0);
    extern void func_8012E8A8(u8 *a0);
    extern void func_8012E8E0(s32 a0, s32 a1);
    s32 v0 = func_80183550(a0);
    if (v0 != 0) {
        *(short *)((char *)a0 + 0x2) = 1;
        *(short *)((char *)a0 + 0x98) = 0;
        func_8012E8A8((u8 *)a0);
        func_8012E8E0((s32)a0, (s32)&D_80189850);
        *(s32 *)((char *)a0 + 0x58) = (s32)&D_80189874 | 0x40000000;
        *(short *)((char *)a0 + 0x5C) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_801813E4);

extern void func_80183264(void *a0, s32 a1);
    extern short D_80189928;
    void func_801814F0(s32 a0) {
        *(short *)(a0 + 0x2) = 2;
        func_80183264((void *)a0, &D_80189928);
    }



extern void func_8012A828(s32 a0, s32 a1);
    extern short D_801AB098;
    void func_8018151C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 11;
        func_8012A828((int)arg0, (int)&D_801AB098);
    }


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_80181548);

INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_801815AC);

void func_801816F0(void *a0) {
    extern s16 D_80189928;
    extern s16 D_80189930;
    extern s16 D_80189938;
    extern s16 D_801AB098;
    extern s32 D_801A4304;
    extern s32 func_80182D68(void *a0, void *a1);
    extern s32 func_80029504(void);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32 a0, s32 a1);
    extern void func_8018323C(s32 a0);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_80183480(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80183264(void *a0, s32 a1);
    extern s32 func_801788B8(s32 arg0, s32 arg1);
    extern void func_80181990(void *a0);
    extern void func_801813E4(void *a0);
    void *s0 = a0;
    s32 v0;
    s32 v1;

    if (func_80182D68(s0, &D_80189938) != 0) {
        v1 = func_80029504();
        if (v1 < 0x64) {
            *(short *)((char *)s0 + 0x2) = 2;
            func_80183264(s0, &D_80189928);
        } else if (v1 < 0x78) {
            *(short *)((char *)s0 + 0x2) = 7;
            func_8012E88C((s32)s0);
            func_8012A828((s32)s0, (s32)&D_801AB098);
            func_8018323C((s32)s0);
            func_8012E8E0((s32)s0, (s32)&D_80189930);
            func_80183480((s32)s0, (s32)&D_801A4304, 0x1, 0x70);
        } else if (v1 < 0x82) {
            *(short *)((char *)s0 + 0x2) = 0xB;
            func_8012E88C((s32)s0);
            func_8012A828((s32)s0, (s32)&D_801AB098);
            func_8018323C((s32)s0);
            func_8012E8E0((s32)s0, (s32)&D_80189930);
            func_80183480((s32)s0, (s32)&D_801A4304, 0x1, 0x70);
        } else {
            *(short *)((char *)s0 + 0x2) = 2;
            func_80183264(s0, &D_80189928);
        }

        {
            register s32 t __asm__("$2");
            t = *(s32 *)((char *)s0 + 0x68);
            *(short *)(t + 0xC) = 0x7FFF;
        }
        v0 = func_801788B8((s32)s0, (s32)&func_80181990);
        *(s32 *)((char *)s0 + 0xD4) = v0;
        func_8012E8E0(v0, (s32)&D_80189928);
        v0 = func_801788B8((s32)s0, (s32)&func_801813E4);
        *(s32 *)((char *)s0 + 0xD8) = v0;
    }
}



extern void (*D_801899F4[])(void);

void func_80181808(void *a0) {
    D_801899F4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 (*D_8018994C)();

void func_80181844(void *param) {
    *(u16 *)((s32)param + 2) = 4;
    *(u16 *)((s32)param + 0x34) = 0;
    if ((u32)func_80029504() < 0x82) {
        func_80178CBC((s32)param, (s32)&D_8018994C);
    }
}



extern s32 func_80128C98(s32 arg);
    extern void func_801CBB54(void *a0);
    void func_80181894(void *a0) {
        if (func_80128C98(3)) {
            ((void (*)(void *))func_801CBB54)(a0);
        }
    }


extern s32 func_80128C98(s32 arg);
    extern void func_801CBBDC(void *a0);
    void func_801818D0(u8 *a0) {
        if (func_80128C98(0x3)) {
            ((void (*)(u8 *))func_801CBBDC)(a0);
        }
    }


extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_801899A4;
    void func_8018190C(short *param) {
        param[1] = 0x12;
        func_80178CBC((int)param, (int)&D_801899A4);
    }


extern int func_80178970(void);
extern short D_801AA660;
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80178D18(void);

void func_80181938(arg0)
void *arg0;
{
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8012A828(s32, s32);
    extern short D_801AA660;

    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 16;
        *(short *)((char *)arg0 + 0x34) = 2;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801AA660);
    }
}


extern s32 func_80182E88(void);
extern s32 func_80183158(s32 arg0, s32 arg1);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 aF80181990(void *a0) __asm__("func_80181990");

s32 aF80181990(void *a0) {
    register s32 obj __asm__("$16") = (s32)a0;
    s32 ptr;
    s32 ptr2;
    ptr = *(s32 *)((char *)obj + 0x64);
    if (*(u16 *)((char *)ptr + 0x2) == 2 && func_80182E88() != 0 && func_80183158(7, 0x15) != 0) {
        ptr2 = *(s32 *)((char *)obj + 0x64);
        *(u16 *)((char *)ptr2 + 0x2) = 3;
    } else {
        return 0;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


void func_80181A10(void *a0)
{
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    v0 = func_8018317C(5, 0, 5, 0x1E);
    if (v0 != 0) {
        func_80181548(a0);
    }
}


extern s32 func_80029504(void);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern s32 func_80128C98(s32 arg);
extern void func_80183264(void *a0, s32 a1);
extern short D_80189928;
extern void (*D_80189974)(void);

void func_80181A64(void *a0) {
    s32 s0 = (s32)a0;

    if ((u32)func_80029504() >= 0x82) {
        switch (*(u16 *)(s0 + 0x34)) {
        case 0:
            if (func_80128C98(3) != 0) {
                ((void (*)(s32 *, s32))func_80178CBC)((s32 *)s0, (s32)&D_80189974);
                *(s16 *)(s0 + 0x34) = 1;
            }
            return;
        case 1:
            break;
        default:
            return;
        }
    }
    if (((s32 (*)(s32))func_80178970)((s32)s0) != 0) {
        ((void (*)(s32))func_80178D18)((s32)s0);
        *(s16 *)(s0 + 2) = 2;
        func_80183264((void *)s0, &D_80189928);
    }
}


void func_80181B14(void) {
}

void func_80181B1C(void) {
}

void func_80181B24(s32 a0)
{
    extern s32 D_801A4304;
    extern s32 func_80183550(s32 a0);
    extern void func_80183480(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8012BD14(s32 a0);
    extern void func_8014CB68(void);

    if (func_80183550(a0) != 0) {
        func_80183480(a0, (s32)&D_801A4304, 1, 0x70);
    }
    if (func_8012BD14(*(s32 *)(a0 + 0x64)) < 0x4001) {
        func_8014CB68();
    }
}


INCLUDE_ASM("asm/ov_SC03_002/nonmatchings/ov_SC03_002_jr_8017D604", func_80181B88);
