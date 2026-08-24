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
extern u8 D_80189444;
extern u8 D_801893B4;
extern u8 D_80189390;
extern u8 D_8018936C;
extern u8 D_80189420;
extern u8 D_801893FC;
extern u8 D_801893D8;
extern u8 D_80189348;
extern void func_80145934(void);
extern u8 D_801894D4;
extern u8 D_801894B0;
extern u8 D_8018948C;
extern u8 D_80189468;
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
extern unsigned char D_801888CC[];
extern unsigned char D_801888FC[];
extern unsigned char D_8018894C[];
extern unsigned char D_8018897C[];
extern unsigned char D_801889AC[];
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
extern void (*D_801889FC[])(void *);
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
extern s32 D_80188AC4[];
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
extern u8 D_80188B4C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188B54;
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
extern int D_801C0008;
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
extern s32 D_801C000C;
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
extern s32 D_80188B84;
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
extern void (*D_80188C2C[])(void);
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
extern void (*D_80188C50[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188C40;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188C64[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188C70[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80188C80[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80188C98[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80188C88;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80188CAC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80188CC8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80188CB8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80188CDC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188CF0[])(void);
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
extern s32 D_80188D04;
extern void (*D_80188D2C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80188D0C;
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
extern int (*D_80188D78[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80188D7C[])(void);
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
extern unsigned short D_801891E0[];
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
extern void (*D_801891F0[])(void);
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
extern int D_801C0040;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80189218[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801891F8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80189208;
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
extern void (*D_80189258[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80189260[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018922C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018926C[])(void);
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
extern u8 D_8018923C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C0048;
extern s32 D_801C0054;
extern s32 D_801C0058;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801892A8[])(s32 *);
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
extern s32 D_8018927C[];
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
extern s32 D_801C0050;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_801894F8[])(void);
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
extern char D_80189318[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018959C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801896F0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018950C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801896F8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018951C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018953C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189700[])(void);
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
extern void (*D_80189728[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189734[])(void);
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
extern void (*D_801895A8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801897D8;
extern void func_8015D380(s32 a0);
extern unsigned char D_801888BC[];
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
extern unsigned char D_801897EC[];
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
extern s8 D_80189828[];
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
extern u16 D_80189870;
extern u16 D_80189872;
extern u16 D_80189874;
extern s32 D_80189878;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189880;
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
extern int D_8018958C;
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
extern unsigned int D_80189904[];
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
extern void (*D_801899B4[])(void);
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
extern u16 D_801899E4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189A48;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C0060[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189A6C[])(void);
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
extern int D_801C00B8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189AB4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189AA4;
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
extern char D_801BF81C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80189ABC[])(void);
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
extern void (*D_80189B10[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189AD8;
extern s16 D_80189B0C;
extern s16 D_80189B0A;
extern s16 D_80189B08;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189B1C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C0118;
extern u8 D_801C0119;
extern u8 D_801C011A;
extern u8 D_801C011B;
extern u8 D_801C011C;
extern u8 D_801C011D;
extern u8 D_801C011E;
extern u8 D_801C011F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189B2C[])(void);
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
extern s32 D_801C0158;
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
extern void (*D_80189B70[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80189BEC[];
extern s32 D_80189C0C[];
extern u8 D_80189C88[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80189CA8[];
extern u8 D_80189CC8[];
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
extern void (*D_80189D64[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80189DE0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801BF82C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80189DEC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80189DF4[])(void);
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
extern void (*D_80189EBC[])(void);
extern void func_80166618(void *a0);
extern void (*D_80189ECC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80189EDC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80189EE8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189E48[];
extern u8   D_80189E5C[];
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
extern void (*D_80189F00[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80189F08[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80189F10[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80189F18[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80189F20[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189F28[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189F30[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189FE4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189FEC[])(void);
extern void func_80169F00(void *a0);
extern char D_80189F9C[];
extern char D_80189F5C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018A024[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018A030[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018A078[])(void);
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
extern void (*D_8018A0F4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C0478;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018A0E8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018A12C[];
extern unsigned short D_8018A134[];
extern unsigned short D_8018A13C[];
extern unsigned char D_801C0480[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C0478;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018A144[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C05B4;
extern M2C_UNK D_801C05B8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C0540;
extern void (*D_8018A174[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C05BC[];
extern u8 D_801C05C4[];
extern u8 D_801C0574[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018A17C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018A198[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018A1A0[])(void);
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
extern void (*D_8018A208[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018A1AC;
extern u8 D_8018A1B8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018A23C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018A244[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018A298[])(void);
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
extern u16 D_8018A2CC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018A2BC[];
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
extern s32 D_8018A2E8;
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
extern void (*D_8018A360[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018A368[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018A370[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018A378[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018A380[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018A388[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018A394[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018A3A0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018A3AC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018A3BC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018A3CC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018A3D4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018A3DC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018A3E4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018A3EC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018A3F4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018A3FC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018A404[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018A40C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018A414[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018A41C[])(void);
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
extern void (*D_8018A424[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018A42C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018A434[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018A43C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018A444[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018A44C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018A454[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018A45C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018A464[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018A46C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018A474[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018A47C[])(void);
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
extern void (*D_8018A4C0[])(void);
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
extern M2C_UNK D_8018A484;
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
extern void (*D_8018A4F0[])(void);
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
extern void (*D_8018A52C[])(void);
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
extern void (*D_8018A584[])();
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
extern void (*D_8018A594[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018A59C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018A704[])();
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
extern void (*D_8018A710[])();
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
extern M2C_UNK D_801BFA74;
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
extern s16 D_801C17D8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C0CF8;
extern short D_801C184C;
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
extern s32 D_801C1124;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C114C;
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
extern s16 D_801C1108;
extern s32 func_8017A3B0(void);
extern short D_801C1144;
extern short D_801C1140;
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
extern s16 D_801C110C;
extern u16 D_801C118C;
extern u16 D_801C118E;
extern u16 D_801C1190;
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
extern s16 D_801C1184;
extern s16 D_801C1186;
extern s16 D_801C1188;
extern s16 D_801C117C;
extern s16 D_801C117E;
extern s16 D_801C1180;
extern void func_8017B7A8(void);
extern s16 D_801C119C;
extern s16 D_801C119E;
extern s16 D_801C11A0;
extern s16 D_801C11A4;
extern s16 D_801C11A6;
extern s16 D_801C11A8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C1194;
extern short D_801C1196;
extern short D_801C1198;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C112C;
extern SV4 D_801C1134;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C1154[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C1150)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018A8EC[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018A8F8[])(void);
extern void func_8017BEE4(void *a0);
extern void func_8017BF98(void);
extern void (*D_8018A904[])(void);
extern void func_8017BFC8(void *a0);
extern void func_8017C07C(void);
extern void (*D_8018A9C4[])(void);
extern void func_8017C0C8(void *a0);
extern void func_8017C154();
extern void func_8017C12C(void);
extern void func_8017C14C(void);
extern void (*D_8018AA04[])(void);
extern void func_8017C664(void *a0);
extern void (*D_8018AA24[])(void);
extern void func_8017CE54(void *a0);
extern void (*D_8018AA34[])(void);
extern void func_8017D0DC(void *a0);
extern void (*D_8018AA40[])(void);
extern void func_8017D63C(void *a0);
extern void (*D_8018ABC4[])(void);
extern void func_8017DB00(void *a0);
extern void func_8017DB74(u8 *a0);
extern void func_8017DD74(void);
extern void func_8017DF7C(void);
/* ==== end §8b carried decl layer ==== */

/* func_8017DF84 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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

void func_8017DF84(s32 arg0)
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



extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017EE64(s32 a0, s16 *a1, s16 a2) {
    s16 v[3];
    short i;

    v[0] = a1[0];
    v[1] = a1[1] - 0x14;
    v[2] = a1[2];
    ((void (*)(s32, void *, void *))func_8012F14C)(*(s32 *)(a0 + 0x20) + 0x34, v, v);
    i = 0;
    do {
        short t;

        if (a2 == 0) {
            t = i;
        } else {
            t = 1;
        }
        func_80146A6C(0x25, (void *)a0, v[0], v[1], v[2], t, 0);
        i = i + 1;
    } while (i < 2);
}



extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80146C3C(void);
extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);


void func_8017EF30(s32 a0) {

    extern u8 D_8018ABF0[];
    s16 sp10[4];
    s16 sp18[16];
    s32 s0;
    s32 s2;
    s32 s3;
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    s32 rnd;
    s32 scale;

    s2 = *(s32 *)(a0 + 0x34);
    s0 = func_800D21C4(a0, D_8018ABF0, 0x2A);
    if (s0 == 0) {
        ((void (*)(s32))func_80146C3C)(a0);
        return;
    }
    *(s32 *)(a0 + 0x20) = s0;
    *(s16 *)(s0 + 0x2A) = 0x1F0;
    s3 = *(s32 *)(s2 + 0x20) + 0x34;
    v1 = rand();
    rnd = v1;
    if (*(s32 *)(a0 + 0x2C) == 0) {
        scale = 0x1000;
        v0 = (v1 & 0xFF) + 0x240;
        sp10[0] = v0;
        *(s16 *)(s0 + 0x28) = 0x240;
        *(s16 *)(s0 + 0x18) = scale;
    } else {
        scale = 0x200;
        v0 = ((v1 & 0xFF) << 2) + 0xD00;
        sp10[0] = v0;
        *(s16 *)(s0 + 0x28) = 0x244;
        *(s16 *)(s0 + 0x18) = 0x1800;
    }
    sp10[1] = (((u32)(rnd & 0x7F00)) >> 5) + 0xE00;
    sp10[2] = 0;
    RotMatrixYXZ(sp10, sp18);
    func_80048EAC((void *)s3, sp18);
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = scale;
    ApplyMatrixSV(sp18, sp10, sp10);
    {
        register s32 c __asm__("$4");
        s32 z;
        c = *(u16 *)(a0 + 0x2);
        *(s32 *)(a0 + 0x10) = sp10[0] << 8;
        *(s32 *)(a0 + 0x14) = sp10[1] << 8;
        z = sp10[2];
        *(s32 *)(a0 + 0x1C) = 0x20;
        *(u16 *)(a0 + 0x2) = c + 1;
        *(s32 *)(a0 + 0x18) = z << 8;
    }
}



extern void (*D_8018ABFC[])(void);

void func_8017F08C(void *a0) {
    D_8018ABFC[*(u16 *)((s32)a0 + 0x2)]();
}




/* Decl reconciliation (lever A, cookbook §37/§124):
 * The TU declares both callees with signatures that disagree with this draft's
 * natural call shape:
 *     src/ov_SC02_026/ov_SC02_026_jr_8017AE2C.c:1683/1701/3352
 *         extern void func_80146C3C(void);      <- 0-arity  => "too many arguments"
 *     src/ov_SC02_026/ov_SC02_026_jr_8017AE2C.c:1686
 *         extern void func_800D22E4(s32 a0);    <- s32, not void *
 * We do NOT invent a competing prototype and we touch no shared header. The two
 * decls below are copied VERBATIM from the TU, so at the splice point they are
 * identical redeclarations (legal, zero conflict, zero blast radius); they are
 * carried in the draft only so the ISOLATED match_one context can resolve
 * func_80146C3C as a *value* -- implicit declaration covers a plain call but not
 * a func-ptr cast, so without it match_one alone fails "undeclared".
 * Every type disagreement is then pushed to a cast at the use site; the TU
 * already uses exactly this func-ptr-cast form for func_80146C3C at line 3374.
 * Casts emit no code -- both calls remain direct `jal`. Byte-neutral. */
extern void func_80146C3C(void);
extern void func_800D22E4(s32 a0);

void func_8017F0C8(void *a0)
{
    s32 val;

    val = *(s32 *)((s32)a0 + 0x1C);
    val--;
    *(s32 *)((s32)a0 + 0x1C) = val;

    if (val != -1) {
        func_800D22E4((s32)a0);
        *(s32 *)((s32)a0 + 0x14) += 0x1A000;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}


extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012CAE4(void *a0);
extern s32  func_8012C354(s32 a0, s32 a1);
extern s32  func_80143970(s32 a0);

/* --- overlay-local data; none of these are declared anywhere in the TU. --- */

void func_8017F128(void *a0) {

    extern u8 D_80078E78[];
    extern s16 D_801C1268;
    extern u8  D_8018AEC8[];
    extern u8  D_8018AD9C[];
    extern u8  D_8018AC04[];
    extern u8  D_8018ADD0[];
    extern s32 D_801C126C;
    extern s32 D_801C1270;
    /* §17 base-pointer cache: the D_80078E78 base is read ONCE at +0x1A but the original
       still pinned it in callee-saved $s1 across the first call -- that only happens when
       the base is a pointer LOCAL, not a direct D_80078E78[0x1A] (which folds %lo per use). */
    u8 *p = D_80078E78;
    s32 t;

    if ((u8)func_80029178(D_8018AEC8[*(s16 *)((s32)a0 + 0x70)]) != 0 ||
        (*(s16 *)((s32)a0 + 0x70) == 4 && (u32)func_80029504() < 0xC8)) {
        func_8012CAE4(a0);
        return;
    }

    t = *(u16 *)(p + 0x1A);
    if (t < 0x12C || t > 0x527) {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_8018AD9C) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x5C) |= 0x10;
        func_8012A828((s32)a0, D_8018AC04);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)&D_801C1268 = *(s16 *)((s32)a0 + 0x88) << 16;
        D_801C126C = *(s16 *)((s32)a0 + 0x8A) << 16;
        D_801C1270 = *(s16 *)((s32)a0 + 0x8C) << 16;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    } else {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_8018ADD0) == 0) {
            return;
        }
        *(s16 *)((s32)a0 + 0xAE) = -4;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(u16 *)((s32)a0 + 0x2) = 7;
    }
}


extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017FA78(s32 a0, s16 a1, s16 a2);
extern void func_8017FAEC(s16 *a0);
extern s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);

/*
 * §136 note (the lever that closed this one): the copy-loop counter and the 8/2
 * selector passed as func_8012BB3C's 4th argument are ONE `short` local, not two.
 *   - As two locals, combine's set_nonzero_bits_and_sign_copies sees the selector
 *     pseudo set only to 8 and 2, proves num_sign_bit_copies >= 17, and DELETES the
 *     `sll/sra 16` argument sign-extension  =>  LENGTH-DRIFT -2.
 *   - Sharing the pseudo with the loop's `i = i + 1` makes the union of sets
 *     unprovable, so the extension survives -- and the merged (longer) live range is
 *     what takes $a3 while the two loop-invariant base addresses take $a1/$a2.
 */
void func_8017F2C4(s32 a0) {

    extern void (*D_8018AC8C[])(void);
    extern s16 D_801C1268;
    extern s32 D_801C1274;
    extern s32 D_801C127C;
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(a0 + 0x1C);
    v1 = -1;
    v0 = v0 - 1;
    *(s32 *)(a0 + 0x1C) = v0;

    if (v0 == v1) {
        s32 t;
        s16 i;
        s32 ret;
        s32 ang;

        func_8012A828(a0, (void *)&D_8018AC8C);

        t = *(u16 *)(a0 + 0x10A) + 1;
        *(u16 *)(a0 + 0x10A) = t;

        if ((t & 3) != 0) {
            if (*(s16 *)(a0 + 0x104) == 0) {
                s32 r = rand();
                s32 x;
                s32 y;

                x = *(s16 *)(a0 + 0x88) - 0x200;
                x += (r & 0x7F) << 3;
                D_801C1274 = x << 16;

                y = *(s16 *)(a0 + 0x8C) - 0x200;
                y += (u32)(r & 0x7F00) >> 5;
                D_801C127C = y << 16;
            } else {
                func_8017FAEC((s16 *)a0);
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0xC00;
            }
        } else {
            for (i = 0; i < 2; i++) {
                ((s32 *)&D_801C1274)[i] = ((s32 *)&D_801C1268)[i];
            }
        }

        i = 8;
        if (*(s16 *)(a0 + 0x108) >= 0xD) {
            i = 2;
        }

        ret = func_8012BB3C(a0 + 4, (s32)&D_801C1274,
                            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), i);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + ret;

        ang = -3 - *(u16 *)(a0 + 0x104);
        func_8017FA78(a0, ang, 0x50);

        if (*(s16 *)(a0 + 0x104) != 0) {
            func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0);
        }

        *(s16 *)(a0 + 0x108) = 0;
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    } else {
        s16 d = *(s16 *)(a0 + 0x102);

        if (d != 0) {
            s32 r2 = func_8012B8E4(a0, d);

            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r2;
        }
    }
}


extern void func_8012A828(s32 a0, void * a1);
extern void func_8012ADE4(u8 *a0);
extern void func_8012B200(u8 *a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern void func_8012BD14(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_8016F1AC(void);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_8017FBC8(s32 a0);
extern void func_8017FA78(s32 a0, s16 a1, s16 a2);
extern void func_8017FAEC(s16 *a0);

void func_8017F4C8(s32 a0) {

    extern u8 D_8018AC04[];
    extern s32 D_801C1274;
    extern s32  D_8018AE6C;
    /* §135-6 dead locals: the target frame is 0x50 = args(0x20, func_80146A6C takes 7)
       + var(0x20) + gp(0x10).  Only 0x10 of that 0x20 is claimed by real spills, so the
       original carried 16 bytes of locals it no longer uses.  Without this the frame
       lands at 0x40 and every sp-relative immediate drifts by the same constant. */
    s32 dead[4];
    s32 flags;
    s32 v;
    s32 s0;
    s32 ret;
    s16 spd;
    s32 m;
    s32 raw;

    s0 = a0;
    ret = 0;
    /* §21 zero-byte re-tie.  The target reads the RAW return register for the first test
       (`andi $v0,$v0,0x6000`) while the saved copy lives in $s1 -- i.e. gcc-2.7.2 kept TWO
       pseudos: a local one that dies at the `andi` and a global one that survives the calls.
       Every source form of `flags = call(); if (flags & ...)` collapses them (cse canon_reg
       substitutes one for the other, so the surviving allocno is the GLOBAL and the `andi`
       reads $s1).  Re-tying the *global* after the copy makes the pair opaque to cse; `raw`
       stays local and takes $v0, which also flips the $v0/$v1 pair on the following
       compare constant.  8 no-barrier variants tested (temp var, `register` pin on either
       side, inverted test, subtract-form compare): all land on the identical 3-insn
       permutation. */
    raw = ((s32 (*)(s32))func_8012CBA4)(a0);
    flags = raw;
    __asm__ __volatile__("" : "=r"(flags) : "0"(flags));

    /* `m` blocks fold_truthop from merging the two bitfield tests below into a single
       `andi $v1,$s1,0xe000` -- the target keeps `& 0x8000` and `& 0x6000` separate. */
    if ((raw & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)s0);
        func_8017FBC8(s0);
        if (*(s32 *)(s0 + 0x1C) >= 9) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 8;
        }
    }

    m = flags & 0x8000;
    if (m != 0 || (flags & 0x6000) != 0x2000) {
        if (*(s16 *)(s0 + 0x106) == 0) {
            *(s16 *)(s0 + 0x106) = 0x111;
        }
        if (*(s32 *)(s0 + 0x1C) >= 5) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 4;
        }
        *(u16 *)(s0 + 0x108) = *(u16 *)(s0 + 0x108) + 1;
    } else {
        *(s16 *)(s0 + 0x106) = 0;
    }

    v = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v;
    if (v != 0) {
        if ((v & 3) == 0) {
            if (func_8012BC60((void *)(s0 + 4), (void *)&D_801C1274) < 0x900) {
                *(s32 *)(s0 + 0x1C) = 1;
            }
        }
        /* The func_8017FA78 call is written in BOTH arms on purpose: gcc-2.7.2's sched1
           interleaves the $a0/$a2 arg setup into each arm's load-delay slots, and only
           then does cross-jumping merge the common tail (it stops at the differing `sh`).
           A single call after the if/else leaves those slots as nops (+2 ins, -1 length)
           and forces the arm pointer into $a0, wrecking the whole block's allocation.
           `ang0`/`ang1` are per-arm locals (§136 L1): one shared local becomes a GLOBAL
           allocno (2 deaths) and loses $a1.  Both must be s32 -- writing the expression
           inline lets convert_to_integer narrow it to UNSIGNED HImode (the u16 operand),
           which emits `ori $a1,$zero,0xfffd` instead of `addiu $a1,$zero,-0x3` + sll/sra. */
        if (*(s16 *)(s0 + 0x106) == 0) {
            s32 r = func_8012BB3C(s0 + 4, (s32)&D_801C1274,
                                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), 8);
            s32 p = *(s32 *)(s0 + 0x20);
            s32 ang0;
            *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang0 = -3 - *(u16 *)(s0 + 0x104);
            func_8017FA78(s0, ang0, 0);
        } else {
            s32 q = *(s32 *)(s0 + 0x20);
            s32 ang1;
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + *(s16 *)(s0 + 0x106);
            ang1 = -3 - *(u16 *)(s0 + 0x104);
            func_8017FA78(s0, ang1, 0);
        }
        if (*(s16 *)(s0 + 0x104) != 0) {
            if ((u32)*(s32 *)(s0 + 0x94) < 0xB) {
                *(s32 *)(s0 + 0x94) = *(s32 *)(s0 + 0x94) + 1;
            }
            if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
                ret = 1;
            }
        }
    } else {
        s16 t;

        func_8012B200((u8 *)s0);
        func_8012A828(s0, D_8018AC04);
        *(s32 *)(s0 + 0x1C) = 0x14 - (*(s16 *)(s0 + 0x104) << 1);
        if (((s32 (*)(s32))func_8012BD14)(s0) <= 0x23FFF) {
            *(s16 *)(s0 + 0x102) = 0xA - *(u16 *)(s0 + 0x104);
        } else {
            *(s16 *)(s0 + 0x102) = 0;
        }
        t = *(s16 *)(s0 + 0x104);
        if (t != 0) {
            t = t - 4;
            *(s16 *)(s0 + 0x104) = t;
            if (t < 0) {
                *(s16 *)(s0 + 0x104) = 0;
            }
        }
        *(s16 *)(s0 + 0x2) = 1;
    }

    if (*(s16 *)(s0 + 0xFC) != 0) {
        if (func_8016F1AC() != 0) {
            /* §17/idiom-7: 0x801891F4 is INTERIOR to D_801891D8 and has no symbol, but the
               target does NOT build it with its own %hi/%lo -- it derives it from the
               D_8018AE6C base already in $a2 (`addiu $a1,$a2,-0x1C`).  Caching the base in
               a POINTER LOCAL reproduces that; `(s32)&D_8018AE6C - 0x1C` folds into a
               second lui/addiu pair and splits the store into lui+sw($at). */
            s32 *tbl = &D_8018AE6C;

            *(s16 *)(s0 + 0x10A) = 0;
            *tbl = *(u16 *)(s0 + 0x88) | (*(s16 *)(s0 + 0x8C) << 16);
            func_80178B70(s0, (s32)tbl - 0x1C);
            *(s16 *)(s0 + 0x98) = 0;
            *(s32 *)(s0 + 0x1C) = 0x14;
            func_8012B200((u8 *)s0);
            *(s16 *)(s0 + 0x2) = 3;
        }
        return;
    }

    if (*(u16 *)(s0 + 0x5E) != 0) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = *(u16 *)(s0 + 0x62);
        func_8017FA78(s0, -0xF, 0);
        func_8017FAEC((s16 *)s0);
        *(s16 *)(s0 + 0x5E) = 0;
        *(s16 *)(s0 + 0x104) = 0xA;
        ret = 1;
    } else {
        s32 d = ((s32 (*)(s32))func_8012BD14)(s0);

        if (d <= 0xFFFF) {
            spd = 0;
            if (d >= 0x4000) {
                spd = (func_8012BDBC(s0, 0x500) != 0) << 2;
            } else if (d >= 0x1000) {
                if (func_8012BDBC(s0, 0x680) != 0) {
                    spd = 7;
                }
            } else {
                spd = 9;
            }
            if (spd != 0) {
                func_8017FAEC((s16 *)s0);
                if (*(s16 *)(s0 + 0x104) == 0) {
                    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = func_8012B864(s0) - 0x800;
                    ret = 1;
                }
                *(s16 *)(s0 + 0x104) = spd;
                func_8017FA78(s0, -7 - spd, 0);
            }
        }
    }

    /* Same §21 re-tie as the prologue, mirrored: the target evaluates the flag through a
       LOCAL copy (`addu $v0,$s2,$zero`, which reorg then duplicates into the two branch
       delay slots) rather than testing $s2 directly.  A plain `fire = ret` is copy-
       propagated away; re-tying the global keeps the pair distinct.  Without it the three
       copies vanish and everything from .L8017CD18 on drifts by 2 instructions. */
    {
        s32 fire = ret;
        __asm__ __volatile__("" : "=r"(ret) : "0"(ret));
        if (fire != 0) {
            func_80146A6C(2, (void *)s0, 0, 0, 0, 2, 0);
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012E778(int param_1, int param_2);
extern s32 func_801439C0(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int func_80178970(void);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012B200(u8 *a0);


void func_8017F8BC(s32 a0) {

    extern u8 D_8018AC04[];
    s32 v1;
    s32 v0;
    s32 p;

    func_80178970();

    if (*(s16 *)(a0 + 0x108) < 0x10) {
        if (*(s16 *)(a0 + 0xFE) != 0) {
            v1 = ((s32 (*)(s32))func_8012CBA4)(a0);
        } else {
            v1 = ((s32 (*)(s32))func_8012CBF4)(a0);
        }
        if ((v1 & 0x8000) != 0) {
            *(u16 *)(a0 + 0x108) = *(u16 *)(a0 + 0x108) + 1;
        }
        if ((v1 & 0x2000) != 0) {
            *(s16 *)(a0 + 0xFE) = 1;
        } else {
            *(s16 *)(a0 + 0xFE) = 0;
        }
    } else {
        func_8012AD80(a0);
    }

    if ((*(s32 *)(a0 + 0x1C) & 7) == 0) {
        func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0);
    }
    if ((*(s32 *)(a0 + 0x1C) & 0xF) == 0) {
        func_8002D4C8(0x828, 0);
    }

    v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;
    if (v0 != -1) {
        if (func_8012E778(a0, 0x8000A8) != 0) {
            return;
        }
    }

    *(s16 *)(a0 + 0x10A) = 1;
    func_8012B200((u8 *)a0);
    func_8012A828(a0, D_8018AC04);

    *(s16 *)(a0 + 0x104) = 0;
    *(s16 *)(a0 + 0x102) = 0xA;
    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 4) |= 0x80000000;

    func_801439C0(*(s32 *)(a0 + 0xCC));

    *(s32 *)(a0 + 0x1C) = 0x14;
    *(s16 *)(a0 + 0x2) = 6;
}


extern void (*D_8018AED8[])(void);

void func_8017FA3C(void *a0) {
    D_8018AED8[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_8017FA78 -- ov_SC03_002 / ov_SC03_002_jr_8017AE2C
 *
 * func_8012B0B4 (the polar->cartesian helper) is NOT declared anywhere in this TU
 * (grep of the WHOLE file: 0 hits for "8012B0B4", including below the splice point),
 * so the project-canonical engine-core prototype is used VERBATIM and no conflict
 * is possible.  It writes ONE packed u32 (lo half = x, hi half = z) through param_1.
 *
 * Three non-obvious shape choices, all byte-forced:
 *
 *  1. `u32 buf[4]` (16 bytes of locals) -- NOT the 8-byte scratch the sibling
 *     func_8012B0B4 callers use.  frame = args(0x10) + var(0x10) + gp(0xC) = 0x2C
 *     -> rounded 0x30, putting $s0/$s1/$ra at 0x20/0x24/0x28 exactly as the target.
 *     An 8-byte buffer gives 0x28 (§135-6, the dead-locals/frame-padding lever).
 *
 *  2. The two reads of buf must be TWO DISTINCT memory refs (`*(s16*)buf` and
 *     `*(s32*)buf`) AND the store to a0+0x10 must sit BETWEEN the SImode load and
 *     its `>> 16` in SOURCE order.  gcc-2.7.2's combine narrows `(mem:SI >> 16)`
 *     into a sign-extending `lh` at +2 (that is §135-11 / T5 seen from the other
 *     side); can_combine_p refuses to sink the load across the intervening store,
 *     which is what keeps the target's `lw 0x10($sp)` + `sra 16`.  Every ordering
 *     that puts the two shifts adjacent to their loads collapses to 28 ins.
 *
 *  3. The `$2` pin on `hi`.  Post-sched1 the block is
 *        lh(lo) lw(hi) sll(lo) sw(0x10) sra(hi) sll(hi) sw(0x18)
 *     so local-alloc's qty densities (local-alloc.c:1579 qty_compare,
 *     floor_log2(refs)*refs/(death-birth)) are lo = 2*4/5 = 16000 vs
 *     hi = 2*6/9 = 13333 -> lo allocates FIRST and takes $v0, the mirror image of
 *     the target.  sched1 normalises every statement permutation to the same
 *     stream, so the §136 local-variable lever is inert here (8 no-pin variants
 *     tested -- decl order, scope, split temps, s16/u16 lo, `* 0x1000`, an early
 *     `t = a2`: all land on the identical 7-insn $v0<->$v1 permutation).  Pinning
 *     the SImode load to $v0 short-circuits the density contest (RC-3): its init
 *     is `pinned = expr`, so it computes directly into the hard reg with NO extra
 *     move, $v0 is live across lo's whole range so lo is pushed to $v1, and the
 *     shift results are born after $v0 dies and reclaim it.
 */

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

void func_8017FA78(s32 a0, s16 a1, s16 a2) {
    u32 buf[4];
    register s32 hi __asm__("$2");
    s32 lo;

    func_8012B0B4(buf, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), a1 << 4);

    lo = *(s16 *)buf;
    hi = *(s32 *)buf;
    *(s32 *)(a0 + 0x10) = lo << 12;
    *(s32 *)(a0 + 0x18) = (hi >> 16) << 12;
    if (a2 != 0) {
        *(s32 *)(a0 + 0x1C) = a2;
    }
}


extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_8017FAEC(s16 *a0) {

    extern u8 D_80126B5C;
    extern s16 D_801C1268;
    extern s32 D_801C1274;
    extern s32 D_801C127C;
    extern u8 D_8018AE04[];
    extern s16 D_8018AE24[];
    extern s16 D_8018AE26[];
    /* The target frame is 0x28 with only $s0/$s1/$ra saved at 0x18/0x1C/0x20, i.e. 8 bytes
       of locals sit below the register save area and are never touched. The original source
       declared a local it no longer uses; the same fossil is visible in the neighbours
       (func_8017C594 carries 16 such bytes). gcc-2.7.2 still reserves the slot. */
    s32 sp10[2];
    s32 a, b, t, r, off, x, y;

    a = (func_8012B6D4((s16 *)&D_80126B5C, &D_801C1268) >> 7) & 0x18;
    b = func_8012B6D4(a0 + 2, &D_801C1268);
    t = a | ((b >> 9) & 7);
    off = D_8018AE04[t] << 2;
    r = rand();

    /* The struct reads are plain INDIRECT_REFs, not ARRAY_REFs: an `a0[0x46]` here sets
       MEM_IN_STRUCT_P, which lets gcc-2.7.2's true_dependence() drop the dependence against
       the constant-address store and hoist the second `lh` above `sw D_801C1274`. */
    x = *(s16 *)((s32)a0 + 0x88) + *(s16 *)((u8 *)D_8018AE24 + off) - 0x100;
    x += (r & 0x7F) << 2;
    D_801C1274 = x << 16;

    y = *(s16 *)((s32)a0 + 0x8C) + *(s16 *)((u8 *)D_8018AE26 + off) - 0x100;
    y += (unsigned)(r & 0x7F00) >> 6;
    D_801C127C = y << 16;
}




/* func_8017FBC8 -- ov_SC02_011 / ov_SC02_011_jr_8017AE2C   [target: 133 ins]
 *
 * Structural twin of func_8017D0BC (ov_SC03_002/ov_SC03_002_jr_8017AE2C.c),
 * banked [MATCH, 133 ins] this session -- same jr_8017AE2C shared layout,
 * identical struct-offset chain (a0+0x6/0xA/0xE/0x10/0x12/0x16/0x18/0x1A) and
 * identical call sequence (func_80133784 -> ratan2 x2 -> angle-wrap ->
 * RotMatrixY -> ApplyMatrixSV -> func_8012CEB0). Reused verbatim per §136c
 * sibling-first (declaration + expression forms are already byte-proven for
 * this exact body).
 *
 * §136 L1/RC-5 note carried from the twin: `ang` (second ratan2 result) is a
 * GLOBAL allocno spanning the +/-0x480 arms, while the `ang - base` compare
 * temp is a LOCAL allocno in the same block; unpinned gcc hands the local
 * temp $v0 and pushes `ang` to $v1 (REGALLOC-PERM). Pinning `ang` to $v0
 * fixes the swap, and reusing the now-dead `ang` as the a0[0x6] scratch
 * (instead of a fresh local) avoids stealing back the $v0 slot.
 */


void func_8017FBC8(s32 a0) {
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern s32  ratan2(s32 a0, s32 a1);
    extern s16  D_801152B0;
    extern s16  D_801152B4;
    extern s32  func_80133784(s32 a0, void *a1, s32 a2);
    extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void RotMatrixY(s32 a0, void *a1);
    extern Mtx8_8017DE10_8017FBC8 D_800AE620;

    u8 in[8];
    u8 out[8];
    Mtx8_8017DE10_8017FBC8 m;
    s32 base;
    register s32 ang __asm__("$2");
    s16 arg;

    *(s16 *)(in + 0) = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x12);
    *(s16 *)(in + 2) = *(u16 *)(a0 + 0xA) + 8;
    *(s16 *)(in + 4) = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x1A);
    *(s16 *)(out + 0) = *(u16 *)(a0 + 0x6);
    *(s16 *)(out + 2) = *(u16 *)(a0 + 0xA) + 8;
    *(s16 *)(out + 4) = *(u16 *)(a0 + 0xE);
    if ((func_80133784(1, &in[0], (s32)&out[0]) & 0xC000) != 0) {
        base = ratan2(D_801152B0, D_801152B4) & 0xFFF;
        ang = ratan2(*(s32 *)(a0 + 0x10), *(s32 *)(a0 + 0x18)) & 0xFFF;
        if ((s16)(ang - base) < 0) {
            ang += 0x480;
        } else {
            ang -= 0x480;
        }
        arg = base - ang;
        ang = *(u16 *)(a0 + 0x6);
        *(s16 *)(in + 0) = ang;
        *(s16 *)(in + 2) = *(u16 *)(a0 + 0xA);
        *(s16 *)(in + 4) = *(u16 *)(a0 + 0xE);
        m = D_800AE620;
        RotMatrixY(arg, &m);
        *(s16 *)(out + 0) = *(u16 *)(a0 + 0x12);
        *(s16 *)(out + 2) = *(u16 *)(a0 + 0x16);
        *(s16 *)(out + 4) = *(u16 *)(a0 + 0x1A);
        ApplyMatrixSV(&m, &out[0], &out[0]);
        *(s16 *)(out + 0) = *(u16 *)(a0 + 0x6) + ((s16)*(u16 *)(out + 0) >> 1);
        *(s16 *)(out + 2) = *(u16 *)(a0 + 0xA) + ((s16)*(u16 *)(out + 2) >> 1);
        *(s16 *)(out + 4) = *(u16 *)(a0 + 0xE) + ((s16)*(u16 *)(out + 4) >> 1);
        if ((func_8012CEB0((s32)&in[0], (s32)&out[0], 0) & 0x2000) != 0) {
            *(s16 *)(a0 + 0x6) = *(u16 *)(out + 0);
            *(s16 *)(a0 + 0xA) = *(u16 *)(out + 2);
            *(s16 *)(a0 + 0xE) = *(u16 *)(out + 4);
        }
    }
}



extern int func_80178970(void);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012B14C(s32 a0, s32 a1);

void func_8017FDDC(s32 a0) {

    extern u8 D_8018ACF4[];
    s32 p;
    u16 v;
    s32 sp10[3];

    func_80178970();

    v = *(u16 *)(a0 + 0x5E);
    if ((v == 0x9) | (v == 0x11)) {
        p = func_8012C658(0x30, 2, a0);
        if (p == 0) {
            return;
        }
        *(u16 *)(p + 0xA) -= 0x20;
        *(u16 *)(p + 0x16) -= 0x10;
        func_8002D4C8(0x829, 0);

        *(s16 *)(a0 + 0x5E) = 0;
        func_8012A828(a0, D_8018ACF4);

        sp10[0] = 0;
        sp10[1] = 0xFFF20000;
        sp10[2] = 0x70000;
        func_8012B14C(a0, (s32)sp10);

        *(s32 *)(a0 + 0x48) = 0x10000;
        *(s32 *)(a0 + 0x1C) = 0x40;
        *(s16 *)(a0 + 0x108) = 0;
        *(s16 *)(a0 + 0x2) = 4;
    }
}




extern int func_80178970(void);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);

void func_8017FEB0(s32 a0) {

    extern void (*D_8018AC8C[])(void);
    s32 v0, v1;
    s32 stack[3];

    func_80178970();

    v0 = *(s32*)((s32)a0 + 0x1C);
    v1 = -1;
    v0 = v0 - 1;
    *(s32*)((s32)a0 + 0x1C) = v0;

    if (v0 != v1) {
        v0 = func_8012CBCC(a0);
        if ((v0 & 0x2000) == 0) {
            return;
        }
    }

    func_80146A6C(2, (void*)a0, 0, 0, 0, 0, 0);
    func_8012A828(a0, (void*)&D_8018AC8C);

    v1 = *(s32*)((s32)a0 + 0x20);
    v0 = *(u16*)((s32)v1 + 0x12);
    v0 = v0 + 0xB00;
    *(u16*)((s32)v1 + 0x12) = v0;

    stack[0] = 0;
    stack[1] = 0;
    stack[2] = 0xFFF40000;

    func_8012B2CC(a0);
    func_8012B14C(a0, (s32)stack);

    *(u16*)((s32)a0 + 0xFE) = 1;
    *(s32*)((s32)a0 + 0x1C) = 0x40;
    *(u16*)((s32)a0 + 0x2) = 5;
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8012C218(void*);

void func_8017FF80(s32 a0)
{

    extern u8 D_8018AEC8[];
    if (func_80178970() == 0) return;

    ((void (*)(s32))func_80178D18)(a0);

    func_80029124((s32)D_8018AEC8[*(s16 *)((s32)a0 + 0x70)], 1);
    ((void (*)(s32))func_8012C218)(a0);
}



extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_8012E778(s32 param_1, s32 param_2);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_801439C0(s32 a0);
extern void func_8012C218(void*);

void func_8017FFD8(s32 a0)
{

    extern u8 D_80078E78[];
    extern s32 D_8018AEA8;
    s32 s0 = a0;
    u8 *v1 = D_80078E78;
    s32 v0;

    if (*(s16 *)((u8 *)s0 + 0x100) != 0) {
        goto L_8017D524;
    }

    if (*(u16 *)((u8 *)s0 + 0x5E) == 0) {
        goto L_8017D524;
    }

    func_80178B18(s0, (s32)&D_8018AEA8);
    *(s16 *)((u8 *)s0 + 0x100) = 1;
    *(s16 *)((u8 *)s0 + 0x2) = 8;
    return;

L_8017D524:
    v0 = (s32)*(u16 *)((u8 *)v1 + 0x1A);
    v0 = v0 - 0x12C;

    if (((u16)v0) < 0x3FC) {
        goto L_8017D57C;
    }

    if (func_8012E778(s0, 0x9000B8) != 0) {
        goto L_8017D57C;
    }

    if (func_8012C658(0x1F8, *(s16 *)((u8 *)s0 + 0x70), s0) == 0) {
        return;
    }

    func_801439C0(*(s32 *)((u8 *)s0 + 0xCC));
    ((void (*)(s32))func_8012C218)(s0);

L_8017D57C:
    if (*(u16 *)((u8 *)s0 + 0x5E) == 0) {
        return;
    }

    v0 = *(s32 *)((u8 *)s0 + 0x1C);
    v0 = v0 + 1;
    *(s32 *)((u8 *)s0 + 0x1C) = v0;

    if (v0 < 0x10) {
        return;
    }

    *(u16 *)((u8 *)s0 + 0x5E) = 0;
    *(s32 *)((u8 *)s0 + 0x1C) = 0;
}




extern int func_80178970(void);
extern void func_80178D18(void);

void func_801800D0(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 7;
    }
}



extern void (*D_8018AF4C[])(void);

void func_80180110(void *a0) {
    D_8018AF4C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80180368(void);
extern void func_800167B8(s32 a0);

s32 func_8018014C(s32 a0) {
    func_80180368();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80180190(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018AF54[])(void);

void func_801801B4(void *a0) {
    D_8018AF54[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80180390(void);

s32 func_801801F0(s32 a0) {
    func_80180390();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180230);

extern void func_800D1EBC(void);
void func_801802CC(void) {
    func_800D1EBC();
}



extern void (*D_8018AF60[])(void);

void func_801802EC(void *a0) {
    D_8018AF60[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801803B8(void);

s32 func_80180328(s32 a0) {
    func_801803B8();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018AFE0;

void func_80180368(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018AFE0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018AFF0;

void func_80180390(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018AFF0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_801803B8(void) {

    extern s32 D_8018B004(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B004, 0x1000000);
}



extern void (*D_8018B014[])(void);

void func_801803E0(void *a0) {
    D_8018B014[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018041C);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018046C);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180580);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180660);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801806D4);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_80180720(void) {

    extern s32 D_8018B00C(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B00C, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180748);


extern void (*D_8018B044[])(void);

void func_80180770(void *a0) {
    D_8018B044[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801807AC);

extern void func_80171A1C(u8 *a0);
    extern s32 func_80174650(s32 arg0);
    void func_80180800(s32 arg0) {
        ((void (*)(s32))func_80171A1C)(arg0);
        func_80174650(arg0);
    }


void func_80180830(void) {
}

extern void func_80174684(void *);
    extern void func_80180860(void *a0);
    s32 func_80180838(void)
{
        func_80174684((void *)func_80180860);
    }




void func_80180860(void *a0) {

    extern void (*D_8018B050[])(void);
    D_8018B050[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern void func_801808E4(s32);
void func_8018089C(s32 *a0) {

    extern u8 D_8018AF6C[];
    func_8014706C(a0);
    func_80154274(a0, (s32)D_8018AF6C);
    func_80171A1C((u8 *)a0);
    ((void (*)(void *))func_801808E4)(a0);
}


extern void func_80171A1C(u8 *a0);
    extern s32 func_80174650(s32 arg0);
    void func_801808E4(s32 param_1) {
        ((void (*)(s32))func_80171A1C)(param_1);
        ((void (*)(s32))func_80174650)(param_1);
    }


void func_80180914(void) {
}

extern void func_80174684(void *);
    extern s32 func_80180944;
    void func_8018091C(void) {
        func_80174684(&func_80180944);
    }




void aF80180944(void *a0) __asm__("func_80180944");
void aF80180944(void *a0)
{

    extern void (*D_8018B05C[])(void);
    D_8018B05C[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_801809B8(u8*);
void func_80180980(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    ((void (*)(void *))func_801809B8)(a0);
}


extern void func_80171A1C(u8 *a0);
    extern s32 func_80174650(s32 a0);
    void func_801809B8(u8 * arg0) {
        *(s16 *)(*(s32 *)((s32)arg0 + 0x20) + 0x10) = 0;
        ((void (*)(void))func_80171A1C)();
        ((void (*)(s32))func_80174650)((s32)arg0);
    }


void func_801809F0(void) {
}

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801809F8);


extern void (*D_8018B068[])(void);

void func_80180A20(void *a0) {
    D_8018B068[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern void func_80180AA4(void *a0);
void func_80180A5C(s32 *a0) {

    extern u8 D_800D5880[];
    func_8014706C(a0);
    func_80154274(a0, (s32)D_800D5880);
    func_80171A1C((u8 *)a0);
    func_80180AA4(a0);
}


extern s32 func_80174650(s32);
extern void func_80147060(u8 *a0);
extern void func_80171A1C(u8 *a0);

    void func_80180AA4(void *a0) {
        if (*(u16 *)(a0 + 0xB8) & 0x8000) {
            func_80147060((u8 *)a0);
            func_80171A1C((u8 *)a0);
            func_80174650((s32)a0);
        }
    }


void func_80180AF4(void) {
}



extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_80180CCC(void *a0);

void func_80180AFC(void) {

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
    D_80126968 = 0x238;
    D_8012696A = 0x200;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80180CCC, 0);
    func_8012A094((s32)D_80126948);
    func_80180CCC(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_80180CCC(void *a0);

void func_80180B94(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x1f4;
    D_8012695C = 0x5DC;
    D_80126968 = 0x238;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80180CCC, 1);
    func_8012A094((s32)D_80126948);
    func_80180CCC(D_80126948);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180C2C);


extern void (*D_8018B074[])(void);

void func_80180CCC(void *a0) {
    D_8018B074[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_80180EA8(s32 param_1, s16 *param_2);

void func_80180D08(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_8018B080[];
    extern Blk8_80126940_80180D08 D_80126940;
    Blk8_80126940_80180D08 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018B080[t];
    }
    sp10 = D_80126940;
    func_80180EA8(a0, sp10.v);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80180DA8);


/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern void func_80180EA8(s32, s16*);

void func_80180E60(s32 a0) {

    extern Blob8_8018A47C_80180E60 D_801BFD88;
    Blob8_8018A47C_80180E60 tmp;

    tmp = D_801BFD88;
    ((void (*)(s32, Blob8_8018A47C_80180E60 *))func_80180EA8)(a0, &tmp);
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

void func_80180EA8(s32 param_1, s16 *param_2) {
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

int func_80181040(int param_1)
{

    extern unsigned char D_8018B088[];
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_8018B088 + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}


extern void func_8001ABBC(u32, u32, void *, u32, u32);
extern u8 D_800AEE88[];

void func_80181070(void) {
    func_8001ABBC(0, 0, D_800AEE88, 0, 0);
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801810A4(void) {

    extern u8 D_800AEE90[];
    func_8001ABBC(0, 0, D_800AEE90, 0, 0);
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801810D8(void) {

    extern u8 D_800AEE98[];
    func_8001ABBC(0, 0, D_800AEE98, 0, 0);
}


extern void func_8013CB84(void);
extern void func_800D06E8(void);
void func_8018110C(void) {
    func_8013CB84();
    func_800D06E8();
}



extern void (*D_8018B090[])(void);

void func_80181134(void *a0) {
    D_8018B090[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_80181170(void) {
        ((s32 (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80181190);

void func_801811EC(void) {
}


extern void (*D_8018B09C[])(void);

void func_801811F4(void *a0) {
    D_8018B09C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80181230);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801812C4);


extern void (*D_8018B0A4[])(void);

void func_80181394(void *a0) {
    D_8018B0A4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

void func_801813D0(int param_1)
{
    int p;
    register s32 r1 __asm__("$16");
    register s32 r2 __asm__("$17");
    s16 r3, r4, r5;
    s16 v;
    s16 v2;
    /* Frame-only: target reserves 0x10 bytes of local stack here that no
     * instruction ever touches (confirmed via match_one: without this the
     * function is byte-identical except every $sp-relative offset is short
     * by 0x10). Almost certainly a real (now-dead) local in the source that
     * m2c can't recover; kept as an explicit unused array rather than a
     * silent frame fudge so a later pass can retype it if the true local
     * is ever identified. */
    s32 unk_frame_pad[4];

    p = *(int *)(param_1 + 0x20);
    *(u8 **)(p + 0x20) = D_800D387C;
    *(u8 *)(p + 0x27) = 0x9c;
    *(u8 *)(p + 0x26) = 0x40;
    *(u8 *)(p + 0x25) = 0x40;
    *(u8 *)(p + 0x24) = 0x40;
    *(u32 *)(p + 4) = *(u32 *)(p + 4) | 0x60000000;

    func_80128EA8(*(s32 *)(param_1 + 0x20), param_1 + 0x24, (s32)D_800D3888);

    *(s32 *)(param_1 + 0x14) = 0xFFFC0000;
    *(s32 *)(param_1 + 0x1C) = 0x3C;
    *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 4);
    *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0xC);

    r1 = rand();
    r2 = rand();
    r3 = rand();
    v = (r1 & 3) * 1024;
    v += (r2 & 3) * 250;
    v += (r3 & 3) * 68;
    *(s16 *)(p + 0x10) = v;
    r4 = rand();
    v2 = (r4 & 3) * 2048 + 0x1000;
    *(s16 *)(p + 0x1A) = v2;
    *(s16 *)(p + 0x18) = v2;
    r5 = rand();
    *(s16 *)(param_1 + 0x2E) = (r5 & 3) + 1;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);

void func_80181500(s32 a0) {
    s32 pad[4];
    s32 s1;
    s16 temp;
    s32 v0;

    *(u16 *)(a0 + 0x2C) += *(u16 *)(a0 + 0x2E);

    s1 = *(s32 *)(a0 + 0x20);

    temp = *(u16 *)(s1 + 0x10) + 0x71;
    *(u16 *)(s1 + 0x10) = temp;
    v0 = func_8004787C(temp);
    *(u16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x12) + (*(s16 *)(a0 + 0x2C) * v0) / 4096;

    v0 = func_80047948(*(s16 *)(s1 + 0x10));
    *(u16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x1A) + (*(s16 *)(a0 + 0x2C) * v0) / 4096;

    *(s32 *)(a0 + 0x14) += 0xFFFF4000;
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x14);

    *(u16 *)(s1 + 0x1A) += 0xCC;
    *(u16 *)(s1 + 0x18) = *(u16 *)(s1 + 0x1A);

    if ((*(s32 *)(a0 + 0x1C) & 3) == 0) {
        func_80128ED8(*(s32 *)(a0 + 0x20), (s32 *)(a0 + 0x24));
    }

    *(s32 *)(a0 + 0x1C) -= 1;
    if (*(s32 *)(a0 + 0x1C) == -1) {
        func_801292C8((u8 *)a0);
    }
}



extern void (*D_8018B0AC[])(void);

void func_8018162C(void *a0) {
    D_8018B0AC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80181668);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801817A8);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018181C);



extern void func_80181BA0(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801C12C0 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_80181884(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_80181884 D_801C12C0[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_80181884 *p = &D_801C12C0[i];

            p->unk16 = i;
            func_80181BA0(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}


/* func_80181914 — byte-verified twin of func_8017D77C (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c:4271),
 * found via §136e/S34 magic-word grep on the `AAA32294` instruction bytes (the
 * D_800AF630+0xA3AA far-offset lhu). func_8017D77C is the banked member of this
 * family; this body was derived by remapping its symbols:
 *   func_8017D77C -> func_80181914       D_801E6F58    -> D_801C12C0
 *   func_8017D9B8 -> func_80181B50       func_8017DAC4 -> func_80181C5C
 *   Ent_8017D6EC  -> Ent_80181914 (own function-suffixed typedef -- same 0x24-stride
 *                     shape as this TU's own Ent_8017D6EC_80181884 at TU:4633-4639,
 *                     given a fresh name/no shared tag so splicing this in below that
 *                     file-scope typedef can't hit the C89 duplicate-typedef error, S33).
 * func_80181C5C is already banked in THIS TU (defined further down as
 * `void func_80181C5C(void *arg0)`), matching the direct call below with no cast
 * needed. func_80181B50 has no declaration anywhere in this TU but its own
 * INCLUDE_ASM stub, so it is declared directly as `void (void *)` (no idiom-9 cast
 * needed, unlike the twin's func_8017D9B8 which was `void (void)`).
 */

extern u8 D_80078EB1;
extern u8 D_80078E78[];
extern u8 D_800AF630[];
extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80181B50(void *arg0);
extern void func_80181C5C(void *arg0);



void func_80181914(s32 *arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_80181914 D_801C12C0[];
    u8 *m = D_800AF630;
    u8 *q = D_80078E78;
    Ent_80181914 *p;
    Ent_80181914 *r;
    s32 i;
    s32 j;
    s32 n;
    s32 h;
    s32 c;
    s32 e;

    if (D_80078EB1 >= 9) {
        n = 0;
        for (j = 0; j < 4; j++) {
            r = &D_801C12C0[j];
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
        p = (Ent_80181914 *)((s32)D_801C12C0 + i * 0x24);
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
                        func_80181B50(p);
                    }
                }
            }
            func_80181C5C(p);
        }
        i++;
    } while (i < 4);
}




/* func_80181B50 - iterate through 4-entry array, call func_80181BA0 if any unk1C is non-zero */

extern void func_80181BA0(void *arg0);




void aF80181B50(void) __asm__("func_80181B50");
void aF80181B50(void)
{

    extern Ent_8017D6EC D_801C12C0[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801C12C0[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_80181BA0(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_80181BA0(void *arg0) {

    extern void (*D_8018B0C4[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_8018B0C4;
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




/* func_80181C5C — build a 4-vertex SVECTOR quad from an 8-u16 source record,
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

void func_80181C5C(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_80181C5C prim;
    Prim_8017DAC4_80181C5C *q;
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



extern void (*D_8018B10C[])(void);

void func_80181D74(void *a0) {
    D_8018B10C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Structural twin of ov_SC03_014:func_80188670 (engine_core.h
 * DEFINE_func_80188670, sim 0.9767). Two real diffs vs the banked twin:
 *   1) an extra `*(u16*)(self+0xE) += 4;` right before the func_8012C194()
 *      call (target's lhu/nop/addiu/sh block that banked doesn't have).
 *   2) the "prep" callee is func_801826B4 here (already DEFINE'd in this
 *      TU at line ~5026, void func_801826B4(void *a0)), not func_80188F80.
 * Everything else (control flow, goto labels, per-field literal order in
 * the two-lw-reload block from law 23) is copied verbatim from the macro.
 */

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801826B4(void *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801B9EAC;
extern u8 D_8018B118;
extern s32 D_801C1350;
extern u8 D_8018B124;
extern u8 D_8018B174;
extern u8 D_8018B154;
extern u8 D_8018B250;

void func_80181DB0(void *a0)
{
    register void *self __asm__("$16") = a0;
    register void *obj  __asm__("$17");
    s32 h;
    s32 pad[8];

    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)self + 0x20) = h;
    if (h == 0) {
        goto L_fail;
    }
    if (*(s16 *)((s32)self + 0x70) != 0) {
        goto L_da8;
    }
    func_8001C214(h, (s32)&D_801B9EAC);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12) = 0x800;
    *(u16 *)((s32)self + 0xE) += 4;
    obj = (void *)func_8012C194();
    *(s32 *)((s32)self + 0xCC) = (s32)obj;
    if (obj != 0) {
        goto L_ce4;
    }
L_fail:
    func_8012CAE4(self);
    return;
L_ce4:
    func_8001CB6C((u8 *)obj, (s32)&D_8018B118, 0x2F0, 0x138);
    func_801826B4(self);
    *(u16 *)((s32)obj + 0x18) = 0x2400;
    *(u16 *)((s32)obj + 0x1A) = 0x1C00;
    *(u16 *)((s32)obj + 0x12) = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
    *(u32 *)((s32)obj + 4) |= 0x51000000;
    *(u8 *)((s32)obj + 0x27) = 0xED;
    func_80128EA8((s32)obj, (s32)&D_801C1350, (s32)&D_8018B124);
    *(u8 *)((s32)self + 0xC0) = 1;
    *(s32 *)((s32)self + 0xBC) = (s32)&D_8018B174;
    *(s32 *)((s32)self + 0x58) = (s32)&D_8018B154 | 0x40000000;
    *(u16 *)((s32)self + 0x5C) = 0x8000;
    *(s16 *)((s32)self + 0xAE) = -3;
    {
        s32 v0 = *(s32 *)((s32)self + 0xC4);
        u16 v1 = *(u16 *)((s32)self + 0xA);
        *(s32 *)((s32)self + 0xB4) = 0;
        *(u8 *)((s32)self + 0xC1) = 0;
        *(s32 *)((s32)self + 0xC4) = v0 | 2;
        *(u16 *)((s32)self + 0xFE) = v1;
    }
    func_8012AD50(self);
    return;
L_da8:
    func_8001CA1C(h, 0);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)((s32)self + 0x20) + 4) |= 0x71000000;
    *(s32 *)((s32)self + 0x14) = 0xFFFF0000;
    *(s32 *)((s32)self + 0x18) = 0x30000;
    *(u16 *)((s32)self + 0xFC) = 0;
    func_8012A828((s32)self, &D_8018B250);
    func_8012AD44((s32 *)self, 9);
}


extern void func_8013CABC(void);
extern void func_8018282C(s32*);
extern s32 func_8012BEE8(s32 a0);
extern void func_801821D4(s32 a0);
extern void func_80182108(s32 a0);
extern void func_80181070(void);
extern int func_80178970(void);
void func_80181F7C(s32 a0) {

    extern s32 D_801C1358;
    s32 self;
    self = a0;
    if (*(s32 *)(self + 0x1C) == 0x30) {
        func_8013CABC();
    } else if (*(s32 *)(self + 0x1C) == 0x10) {
        ((void (*)(void *))func_8018282C)((void *)*(s32 *)(self + 0xD0));
    }
    if (*(u16 *)(self + 0x84) & 1) {
        *(u16 *)(*(s32 *)(self + 0x64) + 6) = *(u16 *)(*(s32 *)(self + 0x64) + 6) - 3;
        *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) =
            *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) - 3;
        *(u16 *)(self + 6) = *(u16 *)(self + 6) - 3;
    } else {
        *(u16 *)(*(s32 *)(self + 0x64) + 6) = *(u16 *)(*(s32 *)(self + 0x64) + 6) + 3;
        *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) =
            *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) + 3;
        *(u16 *)(self + 6) = *(u16 *)(self + 6) + 3;
    }
    {
        s32 t;
        t = D_801C1358;
        *(u16 *)(self + 0x84) = *(u16 *)(self + 0x84) + 1;
        if (t == 0) {
            D_801C1358 = ((s32 (*)(void))func_80181070)();
        }
    }
    if (func_8012BEE8(self) && D_801C1358) {
        func_801821D4(self);
    } else {
        if (*(s32 *)(self + 0x1C) < 0x48) {
            if ((*(u16 *)(self + 0x84) & 3) == 0) {
                func_80182108(self);
            }
        }
    }
    ((void (*)(s32))func_80178970)(self);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182108);

#include "common.h"

extern u8 D_8018B184[];

extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801856BC(s32 a0, s32 a1);
extern void func_80182838(s32 *a0);
extern void func_801860FC(void);
extern void func_80186120(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801821D4(s32 a0) {

    register s32 obj  __asm__("$16");            /* $s0 */
    register s32 self __asm__("$17") = a0;        /* $s1 */
    s32 t0;
    s32 t1;
    s32 t2;

    obj = *(s32 *)(self + 0x20);
    func_8001CA1C(obj, (s32)D_8018B184);

    *(u16 *)(self + 0xA) = *(u16 *)(self + 0xA) - 0xA0;
    *(u16 *)(self + 0xE) = *(u16 *)(self + 0xE) + 0x10;
    *(u16 *)(obj + 0x18) = 0x2C00;
    *(u16 *)(obj + 0x1A) = 0x1C00;
    *(u32 *)(obj + 4) = *(u32 *)(obj + 4) | 0x1000000;

    t0 = *(s32 *)(self + 0xCC);
    *(u16 *)(t0) = 0;
    *(s32 *)(self + 0xCC) = func_80143970(self);

    *(s32 *)(self + 0x14) = 0xFFF80000;
    *(u16 *)(self + 0x5C) = 0;
    *(s32 *)(self + 0x1C) = 8;
    func_8012AD44((s32 *)self, 3);

    obj = *(s32 *)(self + 0x64);
    t1 = *(s32 *)(obj + 0x20);
    *(u32 *)(t1 + 4) = *(u32 *)(t1 + 4) | 0x80000000;
    func_801856BC(obj, t1);

    *(u16 *)(obj + 0x5C) = 0;
    func_8012AD44((s32 *)obj, 2);

    t2 = *(s32 *)(self + 0xD0);
    if (t2 != 0) {
        *(u16 *)(t2 + 0x2C) = 0;
        func_80182838((s32 *)t2);
    }

    func_801860FC();
    func_80186120(self + 4);

    func_8002D4C8(0x86D, 0);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801822E8);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182360);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801823B4);

s32 func_801823F4(s32 *a0) {
        return *(u16 *)((s32)a0 + 0x2) == 0x6;
    }


extern s32 func_801439C0(s32 a0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801292C8(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);

void func_80182408(int a0)
{
    register s32 s0 __asm__("$16") = a0;
    u8 *ptr;
    s32 val1;
    s32 val2;
    s32 t2;

    func_801439C0(*(s32 *)(s0 + 0xCC));
    func_8012B200((u8 *)s0);

    *(s32 *)(s0 + 0x14) = 0x80000;
    *(u16 *)(s0 + 0x6) = D_80126B5E;
    *(u16 *)(s0 + 0xE) = D_80126B66;

    ptr = *(u8 **)(s0 + 0x20);
    val1 = *(u16 *)(ptr + 0x18);
    *(s16 *)(s0 + 0xDC) = (val1 << 16) >> 19;

    ptr = *(u8 **)(s0 + 0x20);
    val2 = *(u16 *)(ptr + 0x1A);
    *(s16 *)(s0 + 0xDE) = (val2 << 16) >> 19;

    func_8012AD44((s32 *)s0, 7);

    t2 = *(s32 *)(s0 + 0xD0);
    if (t2 != 0) {
        func_801292C8((u8 *)t2);
    }

    func_8002D4C8(0x86f, 0);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_801824B8(void *arg0) {
        ((void (*)(void *, s32))func_8012AD44)(arg0, 0x8);
    }


extern s32 func_8013CAE8(void);
    void func_801824D8(void) {
        func_8013CAE8();
    }



extern void (*D_8018B3E0[])(void);

void func_801824F8(void *a0) {
    D_8018B3E0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Banked twin: ov_SC03_014:func_80188E00 (skeleton sim 1.0). Same shape,
 * different literals/globals for this overlay, plus TWO structural deltas
 * vs the twin (confirmed against this target's own .s):
 *   - matched branch does NOT return early; it goto's the shared tail label
 *     that also runs func_8002D4C8(0x426, 0) for the no-match path.
 *   - matched branch writes *(u16*)(a0+0x5E)=0 TWICE: once before the
 *     func_8002D4C8(0x86C,0) call (delay-slot sink, same as twin) and once
 *     more after func_8001AAA0(0x60), right before the goto.
 */

extern u8 D_8018B408[];
extern s32 D_801C1358;          /* TU already declares this exact symbol */
extern s32 D_8018B318;

extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);
/* §183 SIGNATURE-cast-at-call. The TU already carries `extern int func_8001AAA0(void);`
 * at file scope (ov_SC03_024_jr_8017DF84.c:2578) for a different, no-arg call site.
 * A block-scope re-declaration with a different prototype is a hard conflict, not a
 * shadow (C has no shadowing for external linkage), so adopt the TU's prototype
 * VERBATIM and cast through a function pointer at the one call that passes an
 * argument -- byte-identical (gate_main.resolve_conflicts' documented recovery). */
extern int func_8001AAA0(void);

void func_80182534(s32 a0) {
    u32 i;
    register s32 ptr __asm__("$3");
    register s32 obj __asm__("$4");
    s16 val;
    register s32 val2 __asm__("$3");

    for (i = 0; i < 8; i++) {
        if (*(u16 *)(a0 + 0x5E) == D_8018B408[i]) {
            ptr = *(s32 *)(a0 + 0x64);
            val = *(u16 *)(ptr + 6);
            D_801C1358 = 0;
            val = val + 1;
            *(u16 *)(ptr + 6) = val;
            *(s32 *)(a0 + 0x1C) = 0x50;
            *(u16 *)(a0 + 0x84) = 0;
            *(u16 *)(a0 + 6) = *(u16 *)(a0 + 6) + 1;
            func_8012AD44((s32 *)a0, 2);

            obj = func_80132EF4(a0, 0x58);
            *(s32 *)(a0 + 0xD0) = obj;
            if (obj != 0) {
                *(u16 *)(obj + 6) = *(u16 *)(a0 + 6);
                *(u16 *)(obj + 0xA) = *(u16 *)(a0 + 0xA);
                val2 = *(u16 *)(a0 + 0xE);
                *(s16 *)(obj + 0x2C) = -0xA0;
                *(s32 *)(obj + 0x34) = a0;
                *(u16 *)(obj + 0xE) = val2;
            }

            func_80178B18(a0, (s32)&D_8018B318);

            *(u8 *)(a0 + 0xC1) = 0;
            *(u16 *)(a0 + 0x5C) = 0;
            *(u16 *)(a0 + 0x5E) = 0;
            func_8002D4C8(0x86C, 0);
            ((void (*)(s32))func_8001AAA0)(0x60);
            *(u16 *)(a0 + 0x5E) = 0;
            goto end;
        }
    }

    *(u16 *)(a0 + 0x5E) = 0;
end:
    func_8002D4C8(0x426, 0);
}


void func_8018264C(void *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


extern void func_8012AD80(s32 a0);

void func_8018265C(s32 a0) {
    s32 v;

    func_8012AD80(a0);
    v = *(s32 *)(a0 + 0x14);
    if (v > 0x14000) {
        *(s32 *)(a0 + 0x48) = -0x1400;
    } else if (v < -0x14000) {
        *(s32 *)(a0 + 0x48) = 0x1400;
    }
}


void func_801826B4(void *a0) {
        s32 v1 = *(s32 *)((s32)a0 + 0xcc);
        *(s16 *)(v1 + 0x8) = *(u16 *)((s32)a0 + 0x6);
        *(s16 *)(v1 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0xe4;
        *(s16 *)(v1 + 0xc) = *(u16 *)((s32)a0 + 0xe) + 0x8;
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801826E8);

extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

s32 func_80182784(s32 arg0, s32 arg1, s32 arg2)
{
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    struct { u16 x, y, z, w; } a;
    struct { u16 x, y, z, w; } b;

    func_8012F214(arg0, arg1, &a);
    func_8012F214(arg0, arg2, &b);
    func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b);
}


extern s32 func_8017BEBC(void);
    void func_801827EC(void) {
        func_8017BEBC();
    }


extern s32 func_8017BFA0(void);
    void func_8018280C(void) {
        func_8017BFA0();
    }


void func_8018282C(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x2;
    }


void func_80182838(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x3;
    }


extern u8 D_801C135D;

s32 func_80182844(void)
{
    register u8 *a0 __asm__("a0");
    a0 = &D_801C135D;
    __asm__("" : "=r"(a0) : "0"(a0));
    if (a0[0] < 0xF8U) {
        a0[0] += 4;
        a0[-1] += 6;
        a0[1] += 6;
    }
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80182884(void *a0) {
        *(s16 *)((char *)a0 + 0x2) = 0x4;
        func_8002D4C8(0x86E, 0);
    }



void func_801828B0(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0;
    }



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8018290C();
extern void (*D_8018B430[])(int);

void func_801828C0(int param_1)
{
    ((void (*)(void))func_8018290C)();
    D_8018B430[*(unsigned short *)(param_1 + 2)](param_1);
}


extern void func_80129350(s32 *a0, s32 a1);
extern void func_80133060(s32 *a0, s32 a1, s32 a2);

void func_8018290C(s32 *a0) {
    s32 *s0;
    s32 a1;

    s0 = a0;
    a1 = *(s32 *)((u8 *)s0 + 0x34);
    func_80129350(s0, a1);

    a1 = (s32)((u8 *)s0 + 0x4);
    *(s16 *)((u8 *)s0 + 0xA) = *(u16 *)((u8 *)s0 + 0xA) + *(u16 *)((u8 *)s0 + 0x2C);
    func_80133060((s32 *)((u8 *)s0 + 0x4), a1, -0x180);
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018295C);

void func_801829F8(void) {
}

void func_80182A00(void) {
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
    extern s32 D_801C1350;
    void func_80182A08(void *arg0) {
        ((void (*)(s32, s32))func_80128ED8)(M2C_FIELD(arg0, s32 *, 0xCC), &D_801C1350);
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182A34);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182AE0);

extern int func_80178970(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_801823B4(s32 a0);

    void func_80182B50(s32 arg0) {
        u16 val_34;
        s16 val_fe, val_a;
        val_34 = *(u16 *)(arg0 + 0x34);
        if (val_34 == 0) {
            if (func_8012BEE8(arg0) != 0) {
                *(s32 *)(arg0 + 0x14) = 0x10000;
                *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            }
        } else {
            val_fe = *(s16 *)(arg0 + 0xFE);
            val_a = *(s16 *)(arg0 + 0xA);
            if (val_a < (val_fe - 0xA0)) {
                func_8012AD80(arg0);
            } else {
                func_801823B4(arg0);
            }
        }
        ((void (*)(s32))func_80178970)(arg0);
    }


    extern int func_80178970(void);
    extern void func_8018265C(int a0);
    extern int func_801826E8(int a0, void *a1);
    extern void func_80182408(int a0);
    extern char D_8018B164[];
    void func_80182BE0(int param_1)
    {
        ((void (*)(void))func_80178970)();
        func_8018265C(param_1);
        if (func_801826E8(param_1, (void *)&D_8018B164) != 0) {
            func_80182408(param_1);
        }
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182C30);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182CE0);

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80182D54(void *param_1) {
    (*(u16 *)((char *)param_1 + 0xFC))++;
    func_8012AD80(param_1);
    if (*(s16 *)((char *)param_1 + 0x98) == 0) {
        func_8012C218(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182DA4);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182E60);

extern s32 func_80182844();
    void func_80182EC8(void) {
        func_80182844();
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182EE8);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182F48);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80182FE0);


extern s32 D_801C13A0;

void func_80183094(void) {
    D_801C13A0 = 1;
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801830A8);

extern void (*D_8018B740[])(void);

void func_80183890(void *a0) {
    D_8018B740[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801838CC);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80183ACC);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80183BF8);


extern void (*D_8018B760[])(void);

void func_80184004(void *a0) {
    D_8018B760[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);

extern s32 D_8018B768;
extern s32 D_8018B774;

void func_80184040(s32 arg0) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)arg0);
        return;
    }

    func_8001CA1C(v0, (s32)&D_8018B768);
    func_8012A828(arg0, (void *)&D_8018B774);

    *(u16 *)(arg0 + 0x2) += 1;

    if (*(s16 *)(arg0 + 0x70) != 0) {
        s16 spin;

        spin = (rand() & 0x1F) - 0x10;
        *(s16 *)(arg0 + 0x12) = spin;

        *(s32 *)(arg0 + 0x44) = -(*(s32 *)(arg0 + 0x10) >> 4);

        spin = (rand() & 0x1F) - 0x10;
        *(s16 *)(arg0 + 0x16) = spin;

        *(s32 *)(arg0 + 0x48) = -(*(s32 *)(arg0 + 0x14) >> 4);

        spin = (rand() & 0x1F) - 0x10;
        *(s16 *)(arg0 + 0x1A) = spin;
    } else {
        s32 obj;
        s32 t;

        obj = *(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20);
        t = -func_8004787C(*(u16 *)(obj + 0x12) & 0xFFF);
        t = t >> 8;
        *(s16 *)(arg0 + 0x12) = t;

        *(s32 *)(arg0 + 0x44) = -(*(s32 *)(arg0 + 0x10) >> 4);

        obj = *(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20);
        t = -func_80047948(*(u16 *)(obj + 0x12) & 0xFFF);
        t = t >> 8;
        *(s16 *)(arg0 + 0x1A) = t;
    }

    *(s32 *)(arg0 + 0x4C) = -(*(s32 *)(arg0 + 0x18) >> 4);
    __asm__ __volatile__("" ::: "memory");
    *(s32 *)(arg0 + 0x1C) = 0x10;

    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) |= 0x10;

    *(u16 *)(arg0 + 0xA) -= 0x30;
}



extern void (*D_8018B77C[])(void);

void func_801841D4(void *a0) {
    D_8018B77C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_80184210 — per-object "spawn/init" dispatcher.  Allocates a display
 * record via func_8012C1B8(), homes it at +0x20, and if the allocation failed
 * frees the object (func_8012CAE4) and returns.  Otherwise a 3-arm switch on
 * the object's s16 subtype at +0x70 binds one of three animation scripts
 * (D_801B0DC8 / D_801B1458 / D_801B1E48) and seeds a per-arm preset.
 * MATCH (176/176 ins), match_one standalone.
 *
 * DECLARATIONS (§181 pre-flight against src/ov_SC03_024/ov_SC03_024_jr_8017DF84.c):
 *   Everything is declared at BLOCK scope, exactly like the neighbouring
 *   banked func_80185730 (L5483-5490) which shares this prologue idiom — the
 *   TU has no file-scope decl for func_8012C1B8 / func_8012CAE4 /
 *   func_8001C214, only block-scope ones (L3325, L5483-5485) plus the
 *   DEFINE_* macro copies in src/shared/engine_core.h.  Spellings copied
 *   verbatim:
 *     extern void func_8012C1B8(void);            (L5483, cast at the call)
 *     extern void func_8012CAE4(void *a0);        (L3325 / L5484)
 *     extern void func_8001C214(s32 a0, s32 a1);  (L5485)
 *     extern s32  func_80047948(s32 a0);          (file-scope L2198)
 *     extern s32  func_8004787C(s32 a0);          (file-scope L2199)
 *     extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);  (L2517)
 *   D_801B0DC8 / D_801B1458 / D_801B1E48 are declared NOWHERE in the TU
 *   (whole-file grep), so they are fresh raw-word externs whose ADDRESS is
 *   taken (law 4: rawest form, cast at the use site).
 *
 * SHAPE NOTES:
 *   - The allocation result is kept as a plain local written to +0x20 in a
 *     SEPARATE statement from the test (NOT func_80185730's folded
 *     `if ((*p = v0 = f()) == 0)` form): the split form is what homes the
 *     pseudo in $a0 — it stays live across the switch as func_8001C214's
 *     first argument in all three arms, which is why $a0 is never reloaded.
 *   - §193-E: `*(s32 *)(a0 + 0x20)` is re-written raw at every use because
 *     each intervening store/call kills the CSE interval.  The ONE place the
 *     target keeps a single load across two stores (sh +0x1A / sh +0x18 in
 *     case 1) is the ONE place a named local `p` is used.
 *   - The only iteration needed was §190-B statement order: +0x6 / +0xA / +0xE
 *     in source order emits the target's 6 / E / A load interleave.
 */

void func_80184210(void *a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 func_80047948(s32 a0);
    extern s32 func_8004787C(s32 a0);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

    extern s32 D_801B0DC8;
    extern s32 D_801B1458;
    extern s32 D_801B1E48;

    s32 v0;
    s32 p;
    s32 t;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    switch (*(s16 *)((s32)a0 + 0x70)) {
    case 0:
        func_8001C214(v0, (s32)&D_801B0DC8);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x50000000;
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s32 *)((s32)a0 + 0x1C) = 0x26;
        *(s32 *)((s32)a0 + 0x44) = 0x3000;
        *(s32 *)((s32)a0 + 0x4C) = 0x900;
        *(u16 *)((s32)a0 + 0x6) += 0x60;
        *(u16 *)((s32)a0 + 0xA) -= 0x40;
        *(u16 *)((s32)a0 + 0xE) -= 0x10;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0xB80;
        func_8012C658(0x383, 1, (s32)a0);
        break;

    case 1:
        func_8001C214(v0, (s32)&D_801B1458);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x50000000;
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(u16 *)((s32)a0 + 0xFE) = *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);

        t = func_8004787C(*(s16 *)((s32)a0 + 0xFC)) / 2 + 0x800;
        p = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(p + 0x1A) = t;
        *(s16 *)(p + 0x18) = t;

        *(s32 *)((s32)a0 + 0x4) =
            *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4) -
            ((func_8004787C(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)) *
              func_80047948(*(s16 *)((s32)a0 + 0xFC))) >> 3);
        *(s32 *)((s32)a0 + 0xC) =
            *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC) -
            ((func_80047948(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)) *
              func_80047948(*(s16 *)((s32)a0 + 0xFC))) >> 3);
        break;

    case 2:
        func_8001C214(v0, (s32)&D_801B1E48);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)((s32)a0 + 0x2) = 3;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
        *(s32 *)((s32)a0 + 0x10) =
            func_8004787C(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)) * 64;
        *(s32 *)((s32)a0 + 0x18) =
            func_80047948(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)) * 64;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
        break;
    }
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801844D0);


extern void (*D_8018B784[])(void);

void func_801845EC(void *a0) {
    D_8018B784[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80180748(void);
    void func_80184628(void) {
        func_80180748();
    }


extern s32 func_80180838(void);
    void func_80184648(void) {
        func_80180838();
    }


extern void func_8018091C(void);
    void func_80184668(void) {
        func_8018091C();
    }


















extern s32 func_80014C54(s32 arg0, s32 arg1, s32 arg2);
s32 func_80184688(void)
{
  short new_var;
  new_var = func_80014C54(0, 0, 0x10);
  ;
  return ((u32) (new_var == 1)) & 1;
}

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801846BC);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184700);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801847E4);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184814);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184884);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801848F4);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184940);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801849E4);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184A78);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184B00);


/* func_80184B80 — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801C13A8..D_801C13D0 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_80184B80(s32 param_1, s32 param_2)
{

    extern s32 D_801C13A8;
    extern s32 D_801C13AC;
    extern s32 D_801C13B0;
    extern s32 D_801C13B8;
    extern s32 D_801C13BC;
    extern s32 D_801C13C0;
    extern s32 D_801C13C8;
    extern s32 D_801C13CC;
    extern s32 D_801C13D0;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_80184B80 vec;                              /* sp+0x10 */
    MTX_L_80184B80 mtx;                              /* sp+0x18 */
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

    D_801C13C8 = vec.a;
    D_801C13B8 = vec.a;
    D_801C13A8 = vec.a;
    D_801C13CC = vec.b;
    D_801C13BC = vec.b;
    D_801C13AC = vec.b;
    D_801C13D0 = vec.c;
    D_801C13C0 = vec.c;
    D_801C13B0 = vec.c;
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80184CB0);

#include "common.h"

/* callees: matched against the TU's existing declarations (law 2) */
extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);

/* D_801C1418..D_801C141E: a small struct-like blob (no existing TU declaration
 * of any width other than byte accesses seen here), following the twin's
 * D_801EB220-family individual-byte-extern treatment (law 8). */
extern u8 D_801C1418;
extern u8 D_801C1419;
extern u8 D_801C141A;
extern u8 D_801C141C;
extern u8 D_801C141D;
extern u8 D_801C141E;

/* D_801C14D8[]: s32 array, indices 0..2 used, and &D_801C14D8[-5] taken as an
 * address (matrix pointer for RotMatrixYXZ), mirroring the twin's
 * D_801EB424[] treatment. */
extern s32 D_801C14D8[];

void func_80184FA0(s32 a0) {
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801C1418;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801C1419 = 0xFF;
    D_801C141A = 0xFF;
    *p = 0xFF;
    D_801C141E = 0;
    D_801C141D = 0;
    D_801C141C = 0;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801C14D8[0] = sp[0];
    D_801C14D8[1] = sp[1];
    D_801C14D8[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801C14D8[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801C14D8[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801850E0);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018520C);


extern void (*D_8018B7E8[])(void);

void func_80185334(void *a0) {
    D_8018B7E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80185370);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801853BC);

void func_80185458(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


#include "common.h"

extern void func_80147084(s32 *a0);
extern s32 D_80126B58;

void func_8018546C(void *a0) {
    func_80147084(&D_80126B58);
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801854B0);

void func_801854F4(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


extern void func_8012C218(void *a0);
    void func_80185508(void) {
        ((s32 (*)(void))func_8012C218)();
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80185528);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_8018555C);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801855AC);

INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80185638);

















extern s32 func_800D06CC(void);
char func_8018567C(void)
{
  func_800D06CC();
  return 0x67;
}

extern void func_800D0694(void);
    void func_8018569C(void) {
        func_800D0694();
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_801856BC);


/* func_80185730 — allocates a GTE-projection slot, seeds a random spread
 * vector from a per-index table, rotates it by the model's Y angle, applies
 * it to the object's matrix, adds it to the object's position, and seeds
 * three random spin fields.  MATCH (136/136 ins), match_one standalone.
 *
 * Declarations: func_8012B23C / func_8012AD50 / D_801B9330 / D_801B93B8 are
 * NOT declared anywhere else in this TU (whole-TU grep, D2) so they're fresh
 * here; func_8012C1B8 / func_8012CAE4 / func_8001C214 / ApplyMatrixSV ARE
 * already file-scope in the TU (L163, L3160-3162) with these EXACT
 * signatures, so re-declaring them identically merges silently (D3).
 *
 * §48 STRUCT ASSIGN: `m = D_800AE620;` on the 32-byte, 4-aligned matrix
 * routes move_by_pieces to the plain lw/lw/lw+sw/sw/sw grouping (no lwl/lwr).
 *
 * §48-C2: `sv = D_801B9330[idx];` on the 8-byte, 2-aligned (u16 x,y,z; s16 w)
 * record struct falls through move_by_pieces' align>=4 test and emits the
 * lwl/lwr+swl/swr unaligned block-move pair instead — matches the target's
 * four unaligned loads/stores exactly.
 *
 * REGALLOC LEVER (new, byte-verified this session — candidate for the
 * cookbook): a redundant `void *s1 = a0;` local (never reassigned, used only
 * as an alias for the parameter) made gcc-2.7.2 split the parameter pseudo
 * into TWO allocnos — one for its pre-call uses (landing in $s0) and a
 * SEPARATE one (bridged by an extra `move`) for its post-call/cross-branch
 * uses (landing in $s1) — even though the target uses ONE register ($s1)
 * uniformly from the second prologue instruction on. Referencing the
 * parameter `a0` directly everywhere (no alias local) collapses this back to
 * a single allocno and fixed 6 of the 11 mismatches outright.
 *
 * The remaining 5 (an `addu $a0,$v0,zero` copy scheduled too EARLY, and the
 * alloc-check branch/store testing `$a0` instead of `$v0` directly) were a
 * v0-pseudo/call-arg-copy coalescing difference: gcc folded the store, the
 * branch test, AND the func_8012C1B8 return value into one $a0-homed pseudo.
 * Folding the store and the compare into ONE C expression —
 * `if ((*(s32*)(a0+0x20) = v0 = func_8012C1B8()) == 0)` — instead of two
 * separate statements (assign-then-test) made cc1 keep the store/test on the
 * call's native $v0 and defer the $a0 copy to just before its actual
 * consumer (func_8001C214), matching the target's schedule exactly. No
 * register pins, no permuter, no zero-byte asm barriers needed for either
 * residual — both C-lever-closeable (§136-class local-variable/expression-
 * shape levers).
 */
void func_80185730(void *a0)
{
          /* 32B, align 4 */
 /* 8B, align 2 */

    extern Mat32_8018A390_80185730 D_800AE620;
    extern Rec8_8018A390_80185730 D_801B9330[];
    extern s32 D_801B93B8[];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8012B23C(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern s32 rand(void);

    Mat32_8018A390_80185730 m;               /* sp+0x10 */
    Rec8_8018A390_80185730 sv;               /* sp+0x30 */
    void *mp;
    void *svp;
    s32 v0;
    s16 w;

    m = D_800AE620;
    sv = D_801B9330[*(s16 *)((s32)a0 + 0x70)];

    mp = &m;
    svp = &sv;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    w = sv.w;
    func_8001C214(v0, D_801B93B8[w]);

    RotMatrixY(*(s16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12), mp);

    ApplyMatrixSV(mp, svp, svp);

    *(u16 *)((s32)a0 + 0x6) += sv.x;
    *(u16 *)((s32)a0 + 0xA) += sv.y;
    *(u16 *)((s32)a0 + 0xE) += sv.z;
    func_8012B23C((s32)a0);

    *(s16 *)((s32)a0 + 0x12) = (s16)sv.x >> 3;
    *(s16 *)((s32)a0 + 0x16) = (s16)sv.y >> 3;
    *(s16 *)((s32)a0 + 0x1A) = (s16)sv.z >> 3;

    *(s16 *)((s32)a0 + 0xFC) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0xFE) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0x100) = (s16)((rand() & 0x7FF) - 0x400) >> w;

    func_8012AD50(a0);
}


extern void (*D_801B93C4[])(void);

void func_80185950(void *a0) {
    D_801B93C4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_8018598C(s32 a0) {
    u8 *s0;
    s16 val1;
    s16 val2;

    func_8012AD80(a0);
    s0 = (u8 *)a0;

    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x10) += *(u16 *)(s0 + 0xFC);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x12) += *(u16 *)(s0 + 0xFE);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x14) += *(u16 *)(s0 + 0x100);

    val1 = *(s16 *)(*(s32 *)(s0 + 0x64) + 0x0A);
    val2 = *(s16 *)(s0 + 0x0A);

    if (val2 > val1) {
        func_8012C218((void *)a0);
    }
}


void func_80185A20(void) {

    extern s16 D_801C15FC;
    s16 *p = &D_801C15FC;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_80185A44 — cookbook §71 (sibling-first).
 * func_80185AE4 is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_80185AE4(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_80185C00 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
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


extern void func_80185AE4(s32 arg0, s32 arg1, s32 arg2);
extern void func_80185C00(s32 arg0, Rec_8018A6A4_80185A44 *arg1, s32 arg2, s32 arg3);

void func_80185A44(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_80185A44 sp10;
    s32 i;
    s32 ang;

    func_80185AE4(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_80185C00(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



    extern s16 D_801C15F6;
    extern s16 D_801C15F8;
    extern s16 D_801C15FA;
    void func_80185AE4(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801C15F4;
        D_801C15F4 = *(u16 *)((s32)arg0 + 0x0);
        D_801C15F6 = *(u16 *)((s32)arg0 + 0x2);
        D_801C15F8 = arg1;
        D_801C15FA = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80185B14(s32 a0) {

    extern s16 D_801C15F4;
    extern s16 D_801C15F6;
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

    D_801C15F4 = sxy[0];
    D_801C15F6 = sxy[1];
}


extern s16 D_801C15FA;
    void func_80185B8C(s32 arg0) {
        *(s16 *)((s32)&D_801C15FA + 0x0) += arg0;
    }


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80185BA8);


/* func_80185C00 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
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
 * (2) func_80185C00 itself — the TU prototypes it at L3570 as
 *     `extern void func_80185C00(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_80185C00") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801C15FC / rand — declared VERBATIM as the TU already has them
 *     (D_801C15FC: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_80185C00");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801C15FC;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801C15FC);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_80185C00 *)((u8 *)s1 + 6) = *(B4_80185C00 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_80185C00 *)((u8 *)s1 + 10) = *(B4_80185C00 *)a3;
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




s32 func_80185CD4(void) {

    extern s16 D_801C15FC;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801C15FC + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_80185D10(s32 a0, s32 a1) {

    extern s16 D_801C15FC;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801C15FC);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_80185D5C — 16-entry table walk, stride 0xE, over D_801C15FC.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801C15FC; s16 *p = &D_801C15FC; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_80185E38(s32 arg0);

void func_80185D5C(void) {

    extern s16 D_801C15FC;
    s16 *p = &D_801C15FC;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_80185E38(i);
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



/* func_80185E38 — draws one entry of the 16-slot D_801C15FC particle table:
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
 * LEVERS (each byte-checked against asm/.../func_80185E38.s)
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
 *      instead of EA,E4,E6.  `lh $a0,D_801C15FA` is a single-set SET(REG,…) —
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
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801C15F4/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801C15F8, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_80185E38 is byte-identical.
 */

void func_80185E38(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_80185E38 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801C15F4;
    extern s16 D_801C15F6;
    extern s16 D_801C15F8;
    extern s16 D_801C15FC;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_80185E38 m;                    /* sp+0x10 */
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

    ent = (u8 *)((arg0 * 14) + (s32)&D_801C15FC);
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

    ang = D_801C15FA;
    bx = (u16)D_801C15F4;
    by = (u16)D_801C15F6;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801C15F8;
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


void func_801860FC(void) {

    extern s16 D_801C14F4;
    s16 *p = &D_801C14F4;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_80186148(s32 a0);

void func_80186120(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_80186148((s32)pv);
}



/* func_80186148 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801BFE6C instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_801861D0 arg0
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
 * func_800491AC / RotTransPers at file scope L3484-3486; func_801861D0 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801BFE6C appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_801861D0(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_80186148(s32 a0) {
    extern u8 D_800AF648;
    extern V4_80186148 D_801BFE6C;
    u16 sxy[4];
    s32 pv[4];

    *(V4_80186148 *)pv = D_801BFE6C;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_801861D0(sxy, pv, 0x10, 0x18);
}



extern void func_8018623C(void *a0, void *a1, s16 a2);
extern void func_80186370(s32 a0, s16 a1, u16 a2);

void func_801861D0(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_8018623C(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_80186370(i, j, arg3);
    }
}





void func_8018623C(void *a0, void *a1, s16 a2) {

    extern s16 D_801C14E8;
    extern s16 D_801C14EA;
    extern u8 D_801C14F0;
    extern u8 D_801C14F1;
    extern u8 D_801C14F2;
    extern u32 D_801C14EC;
    if (a0 != NULL) {
        D_801C14E8 = *(u16 *)a0;
        D_801C14EA = *(u16 *)((s32)a0 + 2);
    } else {
        D_801C14E8 = 0;
        D_801C14EA = 0;
    }

    D_801C14F0 = *(u8 *)a1;
    D_801C14F1 = *(u8 *)((s32)a1 + 1);
    D_801C14F2 = *(u8 *)((s32)a1 + 2);
    D_801C14EC = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_801862AC(s32 a0) {

    extern s16 D_801C14E8;
    extern s16 D_801C14EA;
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

    D_801C14E8 = sxy[0];
    D_801C14EA = sxy[1];
}




extern s32 func_8018648C(void);
extern void func_80186370(s32 a0, s16 a1, u16 a2);

void func_80186324(s32 a0, s32 a1) {
    s32 result = func_8018648C();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_80186370(result, ext_a0, (u16)a1);
    }
}



/* func_80186370 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801C14F4.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801C14F4 : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801C14EE : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_80186370(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_80186370");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801C14F4;
    extern s16 D_801C14EE[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_80186370 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_80186370 *)((s32)&D_801C14F4 + (a0 << 4));

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
    p->f4 = (s32)D_801C14EE[0] * 64;
}




s32 func_8018648C(void) {

    extern s16 D_801C14F4;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801C14F4 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_801864C8 — the 16-slot particle/effect stepper over D_801C14F4[16]
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
 * D_801C14F4 uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_801864C8(void) {

    extern s16 D_801C14EE;
    extern s16 D_801C14F4;
    extern void func_801865DC(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801C14EE;
    p = &D_801C14F4;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_801865DC(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_801865DC — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801C14F4[a0] record, projects the
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


/* 0x10-byte-stride record table at D_801C14F4 (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_801865DC(s32 a0) {

    extern s16 D_801C14E8;
    extern s16 D_801C14EA;
    extern u8 D_801C14F0;
    extern u8 D_801C14F1;
    extern u8 D_801C14F2;

    extern s16 D_801C14F4;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_801865DC D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_801865DC *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_801865DC *)m = *(Mat32_8018B23C_801865DC *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801C14F0;
    *(u8 *)(q + 5) = D_801C14F1;
    *(u8 *)(q + 6) = D_801C14F2;

    p = (Rec_8018B23C_801865DC *)((s32)&D_801C14F4 + (a0 << 4));
    x = p->fA + (u16)D_801C14E8;
    y = p->fE + (u16)D_801C14EA;
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
        Bidx_8018B23C_801865DC *bp = (Bidx_8018B23C_801865DC *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_801865DC *)q)->addr =
            ((PTag_8018B23C_801865DC *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_801865DC *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}


#include "common.h"

/* -- declarations (law 2: adopt the destination TU's existing spellings) -- */
extern void func_8012BE54(s32 a0);         /* canonical (309x) -> cast at use */
extern s32  func_8014CB8C(void);           /* TU L560 */
extern void func_80019064(void *a0);       /* TU L460 */
extern s32  func_8012C588(s32 a0, s32 a1); /* not in TU; canonical (1497x) */
extern void func_8002D4C8(s32 a0, s32 a1); /* TU L57 */
extern void func_8012C218(void *a0);       /* TU L4029/4049 */
extern u8   D_80062BD0;                    /* TU L1386 */
extern s32  D_80126B58;                    /* TU L4463/5371 (raw scalar, law 4) */

/* 16-byte-stride table; only the leading u16 field is read here.
   No prior declaration exists anywhere in src/, so the shape is free. */
typedef struct {
    u16 f0;
    u8  pad[14];
} Stride16_801BA59C;

void func_801868C0(s32 a0)
{
    extern Stride16_801BA59C D_801BA59C[];

    /* Frame-pad induction (cookbook §5/§163e lever 3): the target reserves
       0x28 = 16 (arg area) + 16 (s0/s1/s2/ra) + 8 unused var_size bytes that
       no instruction ever addresses.  An address-taken-but-never-stored local
       array survives -O2 DCE and reserves exactly those 8 bytes; `(void)&pad`
       emits zero code.  Without it the frame is 0x20 and all ten save/restore
       displacements are 8 low. */
    s32 pad[2];
    s32 s0 = a0;
    s32 *anchor = &D_80126B58;   /* &SYM in the entry block -> one $s2 base */
    s32 s1 = 0;
    (void)&pad;

    if (*(u8 *)((u8 *)s0 + 0x74) != 0) {
        if (((s32 (*)(s32))func_8012BE54)(a0) < 0x4000) {
            if (func_8014CB8C()) {
                /* increment before the call, store in the call's delay slot */
                *(u16 *)((u8 *)s0 + 0xFE) = *(u16 *)((u8 *)s0 + 0xFE) + 1;
                func_80019064(&D_80062BD0);
                func_8012C588(0x27D, s0);
                /* s1 = 1 is UNCONDITIONAL once this block is entered: it rides
                   the `bnez` delay slot below, which executes either way. */
                s1 = 1;
                if (*(s16 *)((u8 *)s0 + 0xFE) >= 9) {
                    s32 t1;
                    t1 = *(u16 *)((u8 *)s0 + 0xA) + 1;
                    *(u16 *)((u8 *)s0 + 0xA) = t1;
                    {
                        /* re-read 0x20 per store-separated run (§193-H) */
                        s32 vp = *(s32 *)((u8 *)s0 + 0x20);
                        s32 t2 = *(u16 *)((u8 *)vp + 0x18) - 0x10;
                        *(u16 *)((u8 *)vp + 0x18) = t2;
                    }
                    {
                        s32 vp = *(s32 *)((u8 *)s0 + 0x20);
                        s32 t3 = *(u16 *)((u8 *)vp + 0x18);
                        *(u16 *)((u8 *)vp + 0x1C) = t3;
                    }
                }
            }
        }
        {
            s32 t4 = D_801BA59C[*(s16 *)((u8 *)s0 + 0x100)].f0 - 1;
            s32 t5 = *(u16 *)((u8 *)s0 + 0xA) + t4;
            *(u16 *)((u8 *)anchor + 0xA) = t5;   /* D_80126B58 + 0xA */
        }
    }

    {
        s32 v0;
        __asm__ __volatile__("" : "=r"(v0) : "0"(s1));
        if (v0 == 0) {
            *(u16 *)((u8 *)s0 + 0xFE) = 0;
        }
    }

    {
        /* The SImode `t6` and the HImode `u6` are two pseudos in two different
           basic blocks, so combine.c cannot fuse the truncating copy with the
           argument's zero-extension (LOG_LINKS never cross a block boundary).
           That is what mints the target's redundant `addu $a0,$v0,$zero`
           (reorg pulls it into the beqz delay slot) followed by
           `andi $a0,$a0,0xFFFF` in the bne delay slot.  Writing this as one
           s16 local, or as `t6 & 0xFFFF`, folds both into a single
           `andi $a0,$v0,0xFFFF` and loses 4 instructions' worth of bytes. */
        s32 t6 = *(s16 *)((u8 *)s0 + 0xFC);
        u16 u6 = t6;
        if (t6 != 0) {
            if ((*(u16 *)((u8 *)s0 + 0xFE) & 0xF) == 1) {
                func_8002D4C8(u6, 0);
            }
        }
    }

    {
        s32 t7 = *(s16 *)((u8 *)s0 + 0x102) + 0xA0;
        if (t7 < *(s16 *)((u8 *)s0 + 0xA)) {
            ((void (*)(s32))func_8012C218)(s0);
        }
    }
}



extern void (*D_801BA5B4[])(void);

void func_80186A1C(void *a0) {
    D_801BA5B4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_80186A58 — companion of func_80185730 (same TU, same idiom family):
 * allocates a "particle/effect" slot via func_8012C1B8, picks one of two
 * table entries by a random 1/2 flip, and if the slot+table entry are both
 * valid, seeds a batch of random spawn fields and (sometimes) attaches a
 * secondary effect via func_80132EF4.
 *
 * Declarations: func_8012C1B8 / func_8012CAE4 / func_8001C214 are already
 * file-scope in this TU with these EXACT signatures (grepped), so re-declared
 * identically here (law 2). func_80132EF4 is declared identically across many
 * sibling TUs (extern s32 func_80132EF4(s32 a0, s32 a1);) though not yet in
 * THIS TU — adopting that convention. func_80186C20 is defined later in this
 * same TU (INCLUDE_ASM) with no separate prototype anywhere else, so this is
 * a fresh forward declaration by access shape (one pointer arg, no return
 * used). D_80126B5E/62/66 already extern u16 in this TU (law 2).
 *
 * §193-E/H: *(s32*)(a0+0x20) is a pointer-derived base load that dies across
 * every jal — the target reloads it via a fresh `lw` after each call and
 * shares one load across a call-free run of uses. Written as a raw pointer
 * expression (not cached in a persisting local across calls), so CSE
 * reproduces the target's exact reload count on its own.
 */
void func_80186A58(void *a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern s32 func_8012AD50(void *a0);
    extern void func_80186C20(void *a0);
    extern s32 rand(void);
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;

    register s32 *tbl __asm__("$18");
    s32 v0;
    s32 v1;
    s32 a1;
    s32 s1;

    tbl = *(s32 **)(*(s32 *)((s32)a0 + 0x64) + 0xDC);

    s1 = (rand() & 1) + 1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0
        || tbl == 0
        || (a1 = tbl[s1]) == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, a1);

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;

    {
        s32 spread = (rand() & 0x3F0) + 0xA00;
        v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x1C) = spread;
        *(u16 *)(v1 + 0x1A) = spread;
        *(u16 *)(v1 + 0x18) = spread;
    }

    {
        s32 spread2 = rand() & 0xFF0;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = spread2;
    }

    *(u16 *)((s32)a0 + 0xFE) = D_80126B5E;
    *(u16 *)((s32)a0 + 0x6) = D_80126B5E;
    *(u16 *)((s32)a0 + 0xA) = D_80126B62;
    *(u16 *)((s32)a0 + 0x100) = D_80126B66;
    *(u16 *)((s32)a0 + 0xE) = D_80126B66;

    *(u16 *)((s32)a0 + 0xE2) = (rand() & 0x1C) + 0x18;

    *(s32 *)((s32)a0 + 0x14) = 0xFFE80000;
    *(s32 *)((s32)a0 + 0x48) = 0x8000;
    *(s32 *)((s32)a0 + 0x18) = 0x50000;

    *(u16 *)((s32)a0 + 0x106) = rand() & 0xF0;
    *(u16 *)((s32)a0 + 0x108) = rand() & 0xF0;

    func_80186C20(a0);

    if (s1 != 1) {
        v1 = func_80132EF4((s32)a0, 0x22);
        if (v1 != 0) {
            *(u16 *)(v1 + 0x34) = 0x3001;
            *(s32 *)(v1 + 0x14) = 0xFFFC0000;
        }
    }

    func_8012AD50(a0);
}



extern void (*D_801BA5BC[])(void);

void func_80186BE4(void *a0) {
    D_801BA5BC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* §193-A banked twin: ov_SC06_018:func_8018AF88 (sim 0.708) establishes the
 * `local = D_800AE620;` whole-struct-copy idiom for this exact symbol, with
 * the address cached in a pointer local (forced into $s1, callee-saved,
 * live across the RotMatrixY + follow-up calls). Same-TU sibling
 * func_80185730 (src/ov_SC03_024/ov_SC03_024_jr_8017DF84.c ~L5479) is an
 * even closer structural relative: `m = D_800AE620;` on an 8-word Mat32_*
 * typedef (§48 struct-assign -> 3+3+2 lw/sw grouping), RotMatrixY's angle
 * arg read as `*(s16*)(*(s32*)((s32)a0 + 0x20) + 0x12)` mirrors this
 * target's own `lw v0,0x20($s0); lh a0,0x12($v0)` chain almost verbatim
 * (that sibling has one extra outer +0x64 hop this target does not).
 * RotTransSV / func_8004914C / func_800491AC already carry file-scope
 * `void *` decls in the destination TU (~L2639-2641) -- reused verbatim.
 * SV4 {s16 a,b,c,d;} (src/shared/engine_types.h:598) is already used
 * alongside RotTransSV/D_801C112C in the same TU and is the exact 8-byte
 * shape both local vectors need (frame math: 16B implicit arg-spill +
 * 32B Mat32 m + 8B sv + 8B out = 64B locals, + 12B saves + 4B pad = 0x50,
 * matching the target's `addiu $sp,$sp,-0x50` exactly -- no 12-byte VECTOR
 * fits, ruling that guess out).
 */

typedef struct { s32 w[8]; } Mat32_80186C20;
typedef struct { s16 a, b, c, d; } SV4_80186C20;

void func_80186C20(void *a0)
{
    /* §183 STRUCT-view-cast. The destination TU declares this symbol four
     * different ways at block scope; the reconciler flattens scope and reads
     * the LAST one (`extern s32 D_800AE620;`, L6403) as the TU's spelling, so
     * adopt that verbatim and take the struct view at the USE site -- exactly
     * the idiom the TU itself already uses at L6420. */
    extern s32 D_800AE620;
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);

    Mat32_80186C20 m;
    SV4_80186C20 sv;
    SV4_80186C20 out;
    void *mp;

    m = *(Mat32_80186C20 *)&D_800AE620;
    mp = &m;

    RotMatrixY(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12), mp);

    m.w[5] = *(s16 *)((s32)a0 + 0xFE);
    m.w[6] = *(s16 *)((s32)a0 + 0xA);
    m.w[7] = *(s16 *)((s32)a0 + 0x100);

    func_8004914C(mp);
    func_800491AC(mp);

    sv.a = 0;
    sv.b = 0;
    sv.c = *(u16 *)((s32)a0 + 0xE2);

    RotTransSV(&sv, &sv, &out);

    *(s16 *)((s32)a0 + 0x6) = sv.a;
    *(s16 *)((s32)a0 + 0xE) = sv.c;
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern u8 D_801BA594[];

void func_80186D10(void *a0)
{
    void *s1 = *(void **)((s32)a0 + 0xDC);

    if ((*(s32 *)((s32)a0 + 0x20) = ((s32 (*)(void))func_8012C1B8)()) == 0
        || s1 == 0 || *(s32 *)s1 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(*(s32 *)((s32)a0 + 0x20), *(s32 *)s1);

    {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x2C) |= 0x10;
    }
    {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x18) = *(u16 *)((s32)a0 + 0x70);
    }
    {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x1C) = *(u16 *)((s32)a0 + 0x70);
    }

    *(s16 *)((s32)a0 + 0x100) = 0;
    *(u16 *)((s32)a0 + 0x102) = *(u16 *)((s32)a0 + 0xA);
    if (*(s16 *)((s32)a0 + 0x70) >= 0x1001) {
        *(s16 *)((s32)a0 + 0x100) = 1;
    }

    *(u16 *)((s32)a0 + 0x5C) = 0x8400;
    *(u8 *)((s32)a0 + 0x75) = 2;

    {
        s32 idx = *(s16 *)((s32)a0 + 0x100);
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_801BA594[idx << 4];
        func_8012AD50(a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_024/nonmatchings/ov_SC03_024_jr_8017DF84", func_80186E08);




