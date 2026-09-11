#include "common.h"
#include "../shared/engine_prelude.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
typedef void (*Handler)(struct Entry_8016E95C *);
typedef struct { u16 x, y, z, w; } V4_80188E10_80187898;
typedef struct {
    u16 f0;                     /* 0x00  entity kind; 0x282 is the one we want */
    s16 f2;                     /* 0x02  state -> 9 on a hit                   */
    u8  p04[0x20 - 0x04];
    s32 f20;                    /* 0x20  collision volume A                    */
    u8  p24[0x58 - 0x24];
    s32 f58;                    /* 0x58  collision volume B                    */
    u8  p5C[0x70 - 0x5C];
    s16 f70;                    /* 0x70  sub-kind / owner tag                  */
    u8  p72[0x10C - 0x72];      /* stride 0x10C, 0x60 entries (0x6480)         */
} Ent_80188E10_80187898;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80193D6C;
extern u8 D_80193CDC;
extern u8 D_80193CB8;
extern u8 D_80193C94;
extern u8 D_80193D48;
extern u8 D_80193D24;
extern u8 D_80193D00;
extern u8 D_80193C70;
extern void func_80145934(void);
extern u8 D_80193DFC;
extern u8 D_80193DD8;
extern u8 D_80193DB4;
extern u8 D_80193D90;
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
extern unsigned char D_801931F4[];
extern unsigned char D_80193224[];
extern unsigned char D_80193274[];
extern unsigned char D_801932A4[];
extern unsigned char D_801932D4[];
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
extern void (*D_80193324[])(void *);
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
extern s32 D_801933EC[];
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
extern u8 D_80193474[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8019347C;
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
extern int D_801CF400;
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
extern s32 D_801CF404;
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
extern s32 D_801934AC;
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
extern void (*D_80193554[])(void);
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
extern void (*D_80193578[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80193568;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019358C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80193598[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801935A8[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801935C0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801935B0;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801935D4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801935F0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801935E0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80193604[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80193618[])(void);
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
extern s32 D_8019362C;
extern void (*D_80193654[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80193634;
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
extern int (*D_801936A0[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801936A4[])(void);
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
extern unsigned short D_80193B08[];
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void (*D_80193B18[])(void);
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
extern int D_801CF438;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80193B40[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80193B20;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80193B30;
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
extern void (*D_80193B80[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80193B88[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80193B54;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80193B94[])(void);
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
extern u8 D_80193B64;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801CF440;
extern s32 D_801CF44C;
extern s32 D_801CF450;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80193BD0[])(s32 *);
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
extern s32 D_80193BA4[];
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
extern s32 D_801CF448;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80193E20[])(void);
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
extern char D_80193C40[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80193EC4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80194018[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80193E34;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80194020[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80193E44;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80193E64;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80194028[])(void);
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
extern void (*D_80194050[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8019405C[])(void);
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
extern void (*D_80193ED0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80194100;
extern void func_8015D380(s32 a0);
extern unsigned char D_801931E4[];
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
extern unsigned char D_80194114[];
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
extern s8 D_80194150[];
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
extern u16 D_80194198;
extern u16 D_8019419A;
extern u16 D_8019419C;
extern s32 D_801941A0;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801941A8;
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
extern int D_80193EB4;
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
extern unsigned int D_8019422C[];
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
extern void (*D_801942DC[])(void);
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
extern u16 D_8019430C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80194370;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801CF458[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80194394[])(void);
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
extern int D_801CF4B0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801943DC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801943CC;
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
extern char D_801CEB28[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801943E4[])(void);
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
extern void (*D_80194438[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80194400;
extern s16 D_80194434;
extern s16 D_80194432;
extern s16 D_80194430;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80194444[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801CF510;
extern u8 D_801CF511;
extern u8 D_801CF512;
extern u8 D_801CF513;
extern u8 D_801CF514;
extern u8 D_801CF515;
extern u8 D_801CF516;
extern u8 D_801CF517;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80194454[])(void);
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
extern s32 D_801CF550;
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
extern void (*D_80194498[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80194514[];
extern s32 D_80194534[];
extern u8 D_801945B0[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801945D0[];
extern u8 D_801945F0[];
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
extern void (*D_8019468C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80194708[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801CEB38;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80194714[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8019471C[])(void);
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
extern void (*D_801947E4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801947F4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80194804[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80194810[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80194770[];
extern u8   D_80194784[];
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
extern void (*D_80194828[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80194830[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80194838[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80194840[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80194848[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80194850[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80194858[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8019490C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80194914[])(void);
extern void func_80169F00(void *a0);
extern char D_801948C4[];
extern char D_80194884[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8019494C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80194958[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801949A0[])(void);
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
extern void (*D_80194A1C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801CF870;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80194A10[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80194A54[];
extern unsigned short D_80194A5C[];
extern unsigned short D_80194A64[];
extern unsigned char D_801CF878[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801CF870;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80194A6C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801CF9AC;
extern M2C_UNK D_801CF9B0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801CF938;
extern void (*D_80194A9C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801CF9B4[];
extern u8 D_801CF9BC[];
extern u8 D_801CF96C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80194AA4[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80194AC0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80194AC8[])(void);
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
extern void (*D_80194B30[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80194AD4;
extern u8 D_80194AE0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80194B64[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80194B6C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80194BC0[])(void);
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
extern u16 D_80194BF4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80194BE4[];
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
extern s32 D_80194C10;
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
extern void (*D_80194C88[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80194C90[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80194C98[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80194CA0[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80194CA8[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80194CB0[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80194CBC[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80194CC8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80194CD4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80194CE4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80194CF4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80194CFC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80194D04[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80194D0C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80194D14[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80194D1C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80194D24[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80194D2C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80194D34[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80194D3C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80194D44[])(void);
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
extern void (*D_80194D4C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80194D54[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80194D5C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80194D64[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80194D6C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80194D74[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80194D7C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80194D84[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80194D8C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80194D94[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80194D9C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80194DA4[])(void);
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
extern void (*D_80194DE8[])(void);
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
extern M2C_UNK D_80194DAC;
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
extern void (*D_80194E18[])(void);
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
extern void (*D_80194E54[])(void);
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
extern void (*D_80194EAC[])();
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
extern void (*D_80194EBC[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80194EC4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8019502C[])();
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
extern void (*D_80195038[])();
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
extern M2C_UNK D_801CED80;
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
extern s16 D_801D0F78;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D00F0;
extern short D_801D0FEC;
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
extern s32 func_80178D40(s32 arg0, s32 arg1);
extern void func_80179B28(s32 a0);
extern void func_80179B74(u16 *p);
extern void func_80179D30(u16 *a0);
extern void func_80179D78(u16 *a0);
extern void func_80179DCC(short a0);
extern void func_80179DF8(void);
extern void func_80179E1C(short a0);
extern void func_80179E48(s16 a0);
extern void func_80179E74(s16 a0);
extern void func_80179EA0(u16 *a0);
extern void func_80179EE8(short a0);
extern void func_80179F14(s16 a0, s16 a1);
extern void func_80179F44(void);
extern void func_80179F6C(short a0);
extern void func_80179F98(u16 *a0);
extern void func_80179FEC(u16 *a0);
extern void func_8017A040(u16 *a0);
extern s32 D_801D051C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D0544;
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
extern s16 D_801D0500;
extern s32 func_8017A3B0(void);
extern short D_801D053C;
extern short D_801D0538;
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
extern s16 D_801D0504;
extern u16 D_801D0584;
extern u16 D_801D0586;
extern u16 D_801D0588;
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
extern s16 D_801D057C;
extern s16 D_801D057E;
extern s16 D_801D0580;
extern s16 D_801D0574;
extern s16 D_801D0576;
extern s16 D_801D0578;
extern void func_8017B7A8(void);
extern s16 D_801D0594;
extern s16 D_801D0596;
extern s16 D_801D0598;
extern s16 D_801D059C;
extern s16 D_801D059E;
extern s16 D_801D05A0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D058C;
extern short D_801D058E;
extern short D_801D0590;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D0524;
extern SV4 D_801D052C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D054C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D0548)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80195214[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8019522C[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);
extern void func_8017C24C(s32 arg0);
extern void func_8017D12C(s32 a0, s16 *a1, s16 a2);
extern void func_8017D1F8(s32 a0);
extern void (*D_80195264[])(void);
extern void func_8017D354(void *a0);
extern void func_8017D390(void *a0);
extern void func_8002931C(s32 a0);
extern void func_8017D3F0(void);
extern void (*D_801952BC[])(void);
extern void func_8017D410(void *a0);
extern void func_8017D67C(s32 *a0);
extern s32 func_8017D44C(s32 a0);
extern s32 func_8017D490(void);
extern void (*D_801952C4[])(void);
extern void func_8017D4B4(void *a0);
extern void func_8017D6A4(void *a0);
extern s32 func_8017D4F0(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D530(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D5AC(void);
extern void (*D_801952D0[])(void);
extern void func_8017D5CC(void *a0);
extern s32 func_8017D608(s32 a0);
extern void (*D_801952F4[])(void);
extern void func_8017D7A4(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017DA78(s32 param_1, s16 *param_2);
extern void func_8017DC10(void *a0);
extern void (*D_801952FC[])(void);
extern void func_8017DDC4(void *a0);
extern s32 func_8017E21C(void);
extern void func_8012DFD4(void *a0);
extern void func_8017E594(void *a0);
extern s32 func_8017E5F4(s32 *a0);
extern void func_8017E694(s32 a0);
extern void func_8017E784(void *a0);
extern void func_8017E7DC(s32 a0);
extern void func_8017EA0C(s32 a0);
extern void func_8017EA60(s32 param_1);
extern s32 func_8017EA84(s32 a0);
extern void (*D_801953D0[])(void);
extern void func_8017EAC8(void *a0);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017ECF8(void*);
extern void func_8017ECC8(s32*);
extern void func_8017EB04(int param_1);
extern s32 func_8017ED0C(s32 *a0, s32 a1);
extern void func_8017ECC8(s32 *a0);
extern void func_8017EC50(s32 *a0);
extern void func_8017ECC8(s32 *param_1);
extern void func_8017ECF8(void *a0);
extern void (*D_80195408[])(void);
extern void func_8017ED74(void *a0);
extern void func_8017EDB0(s32 param_1);
extern void func_8017EE4C(s32 param_1);
extern void func_8017EDFC(s32 param);
extern void func_8017EE44(int param_1);
extern void func_8017EFB0();
extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_80017714(void *);
extern SVECTOR_8017E6D8 D_801D0ABC[4];
extern struct PW8017E6D8 D_801D0ADC;
extern struct PW8017E6D8 D_801D0AE0;
extern u8 D_801D0AE4, D_801D0AE5, D_801D0AE6, D_801D0AE8, D_801D0AE9, D_801D0AEA;
extern int D_801D0AEC;
extern void func_8017EFB0(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h);
extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);
extern int func_8017F32C(int param_1, short param_2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();
extern void func_8017F53C(s32 a0);
extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);
extern void func_8017F940(int param_1);
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
extern void func_8017FAB4(int param_1);
extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern void func_8017FC64(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8017FEF0(s32 a0);
extern void func_8012B370(int a0);
extern void func_801803B4(s32 a0);
extern s32 func_801823F0(s32 a0);
extern void func_80180584(s32 a0);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern int func_80143C74(short *, int);
extern void func_80180774(s32 a0);
extern void func_80180A8C(int param_1);
extern void func_80180C84(s32 a0);
extern void func_801810CC(short *param_1);
extern void func_801812DC(s32 a0);
extern s32 func_80143C74();
extern void func_80181720(s32 a0);
extern void func_80128EA8();
extern void func_8012931C();
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8();
extern int  func_8012D664();
extern void func_80181930(s32 arg0);
extern void func_80181D74(s32 a0);
extern void func_80181ECC(void *a0);
extern void func_80181FDC(s32 a0);
extern void func_801820B8(s32 a0);
extern void func_80182178(void);
extern void func_80182198(void *a0);
extern void func_801822AC(s32 a0);
extern void func_801823A8(s32 a0);
extern void func_80182468(s32 arg0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182764(s32 param_1);
extern void func_80182998(s32 param_1);
extern void func_8001C924(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801860E4(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_80183004(s32 p);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_801832CC(s32 p);
extern void func_8018338C(s32 param_1);
extern void func_80183CF0(s32 param_1);
extern void func_8018626C(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_80187D0C(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */
extern void func_80183DA8(s32 p);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_80187E08(s32 a0, void *a1, void *a2, s32 a3);
extern void func_80187DA4(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern s32 func_801888E8(s32 arg0, u16 arg1);
extern void func_80183F80(s32 p);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80187E08(s32, void*, void*, s32);
extern void func_80187DA4(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_80184414(s32 param_1);
extern void func_80185AC0(void);
extern void func_80184830(s32 *param);
extern void func_80185F6C(s32 a0, s32 a1);
extern void func_80185A00(s32 param_1);
extern s32 func_80187E54(s32 a0, s32 a1);
extern s32 func_80185CD8(s32 p);
extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012CEB0(void *a0, void *a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
extern void func_80185DA8(s32 a0);
extern s32 func_800132BC(void *a0, void *a1);
extern s32 func_801862CC(s32 a0, s32 a1);
extern void (*D_801AFC18[])(void);
extern void func_801863AC(void *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_80186858(s32 param_1);
extern void (*D_801AFD70[])(void);
extern void func_80186B10(void *a0);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80187A88(s32 a0, s32 a1);
extern s32  func_8012CBF4(s32 a0);
extern void func_80186D24(s32 param_1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern void func_80016714(void*, s32);
extern void func_80187138(s32 param_1);
extern void func_8012B260(u8 *a0);
extern void func_80187588(s32 p);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80187898(Ent_80188E10_80187898 *self, s32 arg1, s32 arg2, s32 arg3, u16 kind);
extern s32 aF80187E54();
extern void (*D_801AFDA4[])(void);
extern void func_80187F3C(void *a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80187F78(s32 param_1);
extern void func_8012C218(void *a0);   /* TU-canonical (ov_SC06_018_jr_8017C24C L5455) */
extern void func_80017274(s32 a0, s32 a1);
extern void func_801883DC(s32 param_1);
extern void (*D_801AFDC4[])(void);
extern void func_80188480(void *a0);
extern void func_8012C1B8(void);   /* TU-canonical (ov_SC06_018_jr_8017C24C) */
extern void func_8012B0B4(unsigned int *p, int a1, int a2);  /* TU-canonical */
extern void func_801884BC(s32 param_1);
extern void (*D_801AFDD0[])(void);
extern void func_80188A54(void *a0);
extern void func_80188A90(s32 param_1);
extern void func_8012931C(s32 a0);
extern void func_801292C8(s32 a0);
extern void func_80188B40(s32 param_1);
extern s32 D_801D0C38;
extern s32 func_80188BF8(s32 a0, s32 a1);
extern s32 func_80188C28(s32 param_1);
extern s32 func_80188E6C(s32 param_1);
extern void (*D_801C7C10[])(void);
extern void func_8018910C(void *a0);
extern void func_8016AA50(s32, s32);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012B23C(void *);
extern void func_8012B1B4(void *, void *);
extern void func_8012A828(s32, void *);
extern void func_8012C218(void *);
extern void func_801895AC(void *arg);
extern void func_8012A828(s32, void*);
extern void func_80189EC4(void *arg);
extern void func_8018A318(void *arg);
extern void func_8018B3D0(void);
/* ==== end §8b carried decl layer ==== */


/* func_8018D98C — ov_SC06_033_jr_8017C24C — 710 ins.
 * NOT a renderer: a 12-state entity state machine (switch on *(u16*)(a0+0x34))
 * driving three spawned child objects at +0xCC / +0xD0 / +0xD4.
 *
 * Repeated inline blocks (three source copies, verbatim in the target):
 *   CHAIN(src,dst) — func_8012B2CC(child) + ((void (*)(s32, s32, s32))func_8012F14C)(child->0x20+0x34,
 *                    &D_801C8344, v10) then push the rotation into `dst` and
 *                    add dst->0xFC/0xFE onto (child->0x20)->0x10/0x12.
 *   LAST()         — same, but the third child writes the PARENT's 6/A/E.
 *   SCAN()         — walk the 0x60-entry / 0x10C-stride table D_801202A0 and
 *                    bump +0x1C by 0x10 on every other 0x318 in state 6.
 */

extern int  rand(void);
extern s32  func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_8012B77C(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32);
extern void func_80189148(s32 a0);
extern void func_80189250(s32 a0);
extern void func_8018BB48(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void*);
extern void func_800491AC(void*);
extern void RotTransSV(void *a0, void *a1, void *a2);

extern u8  D_801202A0[];
extern u8  D_801C8344;
extern u8  D_801C836C;
extern u8  D_80126B5C;
extern u16 D_800B99D8;

/* Zero-emission launder (see NOTES.md). Each expansion gets a FRESH pseudo that
 * cse/cse2 cannot unify with the other sites' identical (symbol_ref "D_801C8344"),
 * so the address is rematerialised as `la $a1, D_801C8344` at every call instead of
 * being hoisted once into a callee-saved register. Emits no instruction. */
#define F14C(MTXOWNER, OUT)                                                   \
    { s32 _m = (s32)&D_801C8344;                                              \
      __asm__ __volatile__("" : "=r"(_m) : "0"(_m));                          \
      ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((MTXOWNER) + 0x20) + 0x34, _m, (s32)(OUT)); }

#define CHAIN(SRC, DST)                                                       \
    { s32 p;                                                                  \
    s0 = *(s32 *)(a0 + (SRC));                                                \
    func_8012B2CC(s0);                                                        \
    F14C(s0, v10)                                                             \
    p = *(s32 *)(a0 + (DST));                                                 \
    *(u16 *)(p + 0x6) = v10[0];                                               \
    *(u16 *)(p + 0xA) = v10[1];                                               \
    *(u16 *)(p + 0xE) = v10[2];                                               \
    *(u16 *)(*(s32 *)(p + 0x20) + 0x10) =                                     \
        *(u16 *)(p + 0xFC) + *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10);            \
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =                                     \
        *(u16 *)(p + 0xFE) + *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12); }

#define LAST()                                                                \
    s0 = *(s32 *)(a0 + 0xD4);                                                 \
    func_8012B2CC(s0);                                                        \
    F14C(s0, v10)                                                             \
    *(u16 *)(a0 + 0x6) = v10[0];                                              \
    *(u16 *)(a0 + 0xA) = v10[1];                                              \
    *(u16 *)(a0 + 0xE) = v10[2];

#define SCAN()                                                                \
    e = D_801202A0;                                                           \
    i = 0;                                                                    \
    do {                                                                      \
        if (*(u16 *)e == 0x318 && e != (u8 *)a0 &&                            \
            (*(s16 *)(e + 0x70) == 0 || *(s16 *)(e + 0x70) == 6) &&           \
            *(u16 *)(e + 0x34) == 6 && *(s32 *)(e + 0x1C) < 0x11) {           \
            *(s32 *)(e + 0x1C) = *(s32 *)(e + 0x1C) + 0x10;                   \
        }                                                                     \
        e += 0x10C;                                                           \
        i++;                                                                  \
    } while (i < 0x60);

void func_8018D98C(s32 a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    u16 v10[4];  /* sp+0x10 */
    s16 v18[4];  /* sp+0x18 */
    s16 v20[4];  /* sp+0x20 */
    s32 flag;    /* sp+0x28 */
    s32 s0;
    s32 p;
    s32 i;
    s32 col;
    u8 *e;

    switch (*(u16 *)(a0 + 0x34)) {
    case 1: {
        p = func_8012C658(0x318, 2, a0);
        if (p == 0) {
            return;
        }
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0x120;
        *(s32 *)(a0 + 0xCC) = p;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        *(u32 *)(*(s32 *)(p + 0x20) + 0x4) |= 0x80000000;
        /* fallthrough */
        }
    case 2: {
        p = func_8012C658(0x318, 2, a0);
        if (p == 0) {
            return;
        }
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0xC0;
        *(s32 *)(a0 + 0xD0) = p;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        *(u32 *)(*(s32 *)(p + 0x20) + 0x4) |= 0x80000000;
        /* fallthrough */
        }
    case 3: {
        p = func_8012C658(0x318, 2, a0);
        if (p == 0) {
            return;
        }
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0x60;
        *(u16 *)(a0 + 0x34) = 0xA;
        *(s32 *)(a0 + 0xD4) = p;
        *(s32 *)(a0 + 0x1C) = 2;
        return;

        }
    case 4: {
        s32 t;
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) - 0x30;
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t <= 0) {
            *(s32 *)(a0 + 0x1C) = 2;
            *(u16 *)(a0 + 0xAE) = 0;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

        }
    case 5: {
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(p + 0x20) + 0x10) + 0x40;
        if (*(s16 *)(*(s32 *)(p + 0x20) + 0x10) >= 0x200) {
            *(u16 *)(a0 + 0x34) = 9;
        }
        p = *(s32 *)(a0 + 0xD0);
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) - 0x40;
        p = *(s32 *)(a0 + 0xD4);
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) - 0x40;
        break;

        }
    case 6: {
        s32 t;
        func_80189148(*(s32 *)(a0 + 0xCC));
        CHAIN(0xCC, 0xD0)
        func_80189250(*(s32 *)(a0 + 0xD0));
        CHAIN(0xD0, 0xD4)
        func_80189250(*(s32 *)(a0 + 0xD4));
        LAST()
        func_8012B77C((s32)v10, a0 + 4, (s32)&D_80126B5C);
        { s32 xy = *(s32 *)v10;
          *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = xy;
          *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = xy >> 16; }
        if ((*(s32 *)(a0 + 0x1C) & 0xF) == 0) {
            *(u16 *)(a0 + 0xFC) = rand() % 0x180 + 0x180;
        }
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t == 0) {
            *(s32 *)(a0 + 0x1C) = 0x10;
            if (((s32 (*)(s32))func_8012BE54)(a0) <= 0x8FFFF) {
                SCAN()
                *(s32 *)(a0 + 0x1C) = 0x3C;
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
                func_8002D4C8(0x9BB, 0);
            }
        }
        return;

        }
    case 7: {
        s32 t;
        if (((s32 (*)(s32))func_8012BE54)(a0) > 0x8FFFF) {
            *(u16 *)(a0 + 0x34) = 6;
            *(s32 *)(a0 + 0x1C) = 0x96;
            return;
        }
        SCAN()
        CHAIN(0xCC, 0xD0)
        CHAIN(0xD0, 0xD4)
        LAST()
        func_8012B77C((s32)v10, a0 + 4, (s32)&D_80126B5C);
        { s32 xy = *(s32 *)v10;
          *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = xy;
          *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = xy >> 16; }
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t == 0) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            *(u16 *)(a0 + 0xDC) = D_80126B5E;
            *(u16 *)(a0 + 0xDE) = D_80126B62 - 0x38;
            *(u16 *)(a0 + 0xE0) = D_80126B66;
            *(s32 *)(a0 + 0x1C) = 0xF;
            func_8002D4C8(0x9BC, 0);
            func_8012C658(0x318, 3, a0);
            return;
        }
        v20[0] = D_80126B5E;
        v20[1] = D_80126B62 - 0x38;
        v20[2] = D_80126B66;
        ((void (*)(s32))func_8004914C)(*(s32 *)(a0 + 0x20) + 0x34);
        ((void (*)(s32))func_800491AC)(*(s32 *)(a0 + 0x20) + 0x34);
        { void *m = &D_801C836C;
          s32 _v;
          __asm__ __volatile__("" : "=r"(m) : "0"(m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
          _v = (s32)v18;
          __asm__ __volatile__("" : "=r"(_v) : "0"(_v));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
          RotTransSV(m, (void *)_v, &flag); }
        col = 0x202080;
        if (D_800B99D8 & 1) {
            col = 0xE0;
        }
        func_8018BB48((s32)v18, (s32)v20, col);
        return;

        }
    case 8: {
        s32 t;
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t != 0) {
            SCAN()
            break;
        }
        *(u16 *)(a0 + 0x34) = 6;
        *(s32 *)(a0 + 0x1C) = 0x96;
        return;

        }
    case 9: {
        s32 t;
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(p + 0x20) + 0x10) - 0x40;
        *(u16 *)(*(s32 *)(p + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(p + 0x20) + 0x10) & 0xFFF;
        if (*(s16 *)(*(s32 *)(p + 0x20) + 0x10) == 0) {
            t = *(s32 *)(a0 + 0x1C) - 1;
            *(s32 *)(a0 + 0x1C) = t;
            if (t != 0) {
                *(u16 *)(a0 + 0x34) = 5;
            } else {
                *(u16 *)(a0 + 0x34) = 6;
                *(s32 *)(a0 + 0x1C) = 0x1E;
            }
        }
        p = *(s32 *)(a0 + 0xD0);
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x40;
        p = *(s32 *)(a0 + 0xD4);
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x40;
        break;

        }
    case 10: {
        s32 t;
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) - 0x30;
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t <= 0) {
            *(s32 *)(a0 + 0x1C) = 2;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        p = *(s32 *)(a0 + 0xD0);
        *(u32 *)(*(s32 *)(p + 0x20) + 0x4) &= 0x7FFFFFFF;
        break;

        }
    case 11: {
        s32 t;
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) - 0x30;
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t <= 0) {
            *(u16 *)(a0 + 0x34) = 4;
            *(s32 *)(a0 + 0x1C) = 2;
        }
        *(u32 *)(*(s32 *)(p + 0x20) + 0x4) &= 0x7FFFFFFF;
        break;

        }

    case 0:
    default:
        return;
    }

    CHAIN(0xCC, 0xD0)
    CHAIN(0xD0, 0xD4)
    LAST()
}


extern s32  func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u8  *func_8012913C();
extern u8 D_801C9488[];
extern void func_8001C214();
extern void func_8002A04C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_80189390(void *a0);

void func_8018E4A4(arg0)
s32 arg0;
{
    s32 e;
    s32 p;
    s32 i;
    s32 t;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        *(s32 *)(arg0 + 0x1C) = 0x1E;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        goto end;
    case 1:
        *(u8 *)(arg0 + 0xC2) = 0xA;
        e = ((s32 (*)(s32))func_8012913C)(0x23);
        if (e != 0) {
            *(u16 *)(e + 6) = *(u16 *)(arg0 + 6) - rand() % 224 + 0x10;
            *(u16 *)(e + 0xA) = *(u16 *)(arg0 + 0xA) - rand() % 320;
            *(u16 *)(e + 0xE) = *(u16 *)(arg0 + 0xE) - 0x28;
            *(s32 *)(e + 0x18) = 0;
            *(s32 *)(e + 0x14) = 0;
            *(s32 *)(e + 0x10) = 0;
            *(u16 *)(e + 0x34) = (rand() & 0x17FF) + 0x1800;
            func_8002D4C8(0xAD7, 0);
        }
        t = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = t;
        if (t == 0) {
            e = *(s32 *)(arg0 + 0xCC);
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            if (e != 0) {
                *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
                if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xF4) == 0) {
                    *(s16 *)(e + 0x76) = -0x1F4;
                } else {
                    *(s16 *)(e + 0x76) = -0x3E8;
                }
                *(u16 *)(e + 0x5E) = 2;
                *(s32 *)(arg0 + 0xCC) = 0;
            }
        }
        goto end;
    case 2:
        if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xF4) != 0) {
            func_8002D4C8(0xAD6, 0);
            p = func_8012C658(0x33, 3, arg0);
            if (p != 0) {
                *(s16 *)(p + 0x12) = -3;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            p = func_8012C658(0x33, 2, arg0);
            if (p != 0) {
                *(u16 *)(p + 0x12) = 3;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            p = func_8012C658(0x32, 2, arg0);
            if (p != 0) {
                *(u16 *)(p + 0x12) = 0;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            i = 0;
            do {
                e = func_8012C588(0x281, arg0);
                if (e != 0) {
                    *(s32 *)(e + 0x1C) = 2;
                    *(u16 *)(e + 6) = (u16)(*(u16 *)(e + 6) - 0x30) - rand() % 320;
                    *(u16 *)(e + 0xA) = (u16)(*(u16 *)(e + 0xA) - 0x20) - rand() % 256;
                    *(u16 *)(e + 0x12) = (rand() & 0x1F) - 0x10;
                    *(u16 *)(e + 0x16) = -((rand() & 0xF) + 0x10);
                    *(u16 *)(e + 0x1A) = (rand() & 0x1F) - 0x10;
                }
                i += 1;
            } while (i < 8);
            func_8002A04C(arg0);
            if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xCC) != 0) {
                e = *(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xCC);
                *(s16 *)(e + 0x76) = -0x3E8;
                *(u16 *)(e + 0x5E) = 2;
                *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
            }
            func_8012C218(*(void **)(arg0 + 0x6C));
            func_8012C218((void *)arg0);
            goto end;
        }
        i = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
        func_8001C214(*(s32 *)(arg0 + 0x20), D_801C9488);
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = i;
        *(s16 *)(arg0 + 0xAE) = -1;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        goto end;
    default:
        goto end;
    }
end:
    ((void (*)(s32))func_80189390)(arg0);
}


void func_8018E89C(void *arg) {
    extern s32 rand(void);
    extern u8 *func_8012913C(s32);
    extern void func_8002D4C8(s32, s32);
    extern s32 func_8012C658(s32, s32, s32);
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern void func_8002A04C(s32 a0);
    extern void func_8012C218(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8012A828(s32, void *);
    extern void func_80189390(void *);

    extern u8 D_801C833C[];
    extern u8 D_801C9488[];

    u8 *p;
    s32 e;
    s32 iv;
    s32 i;

    p = (u8 *)arg;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        *(s32 *)(p + 0x1C) = 0x1E;
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;

    case 1:
        *(u8 *)(p + 0xC2) = 0xA;
        iv = (s32)func_8012913C(0x23);
        if (iv != 0) {
            *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + rand() % 0xE0 + 0x10;
            *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - rand() % 0x140;
            {
                s32 sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv - 0x28;
            }
            *(u16 *)(iv + 0x34) = (rand() & 0x17FF) + 0x1800;
            func_8002D4C8(0xAD7, 0);
        }
        *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x1C) - 1;
        if (*(s32 *)(p + 0x1C) == 0) {
            iv = *(s32 *)(p + 0xCC);
            *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
            if (iv != 0) {
                if (*(s32 *)(*(s32 *)(p + 0x64) + 0xF4) != 0) {
                    *(s16 *)(iv + 0x76) = -1000;
                } else {
                    *(s16 *)(iv + 0x76) = -500;
                }
                *(u16 *)(iv + 0x5E) = 2;
                *(u16 *)(iv + 0x5C) = *(u16 *)(iv + 0x5C) | 1;
                *(s32 *)(p + 0xCC) = 0;
            }
        }
        break;

    case 2:
        if (*(s32 *)(*(s32 *)(p + 0x64) + 0xF4) != 0) {
            func_8002D4C8(0xAD6, 0);

            e = func_8012C658(0x33, 3, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = -3;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }
            e = func_8012C658(0x33, 2, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = 3;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }
            e = func_8012C658(0x32, 2, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = 0;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }

            i = 0;
            do {
                iv = func_8012C588(0x281, (s32)p);
                if (iv != 0) {
                    *(s32 *)(iv + 0x1C) = 2;
                    {
                        s32 rr = rand();
                        s32 xx = *(u16 *)(iv + 0x06) + 0x30;
                        *(u16 *)(iv + 0x06) = xx + rr % 0x140;
                    }
                    {
                        s32 rr = rand();
                        s32 yy = *(u16 *)(iv + 0x0A) - 0x20;
                        *(u16 *)(iv + 0x0A) = yy - rr % 0x100;
                    }
                    *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                    *(u16 *)(iv + 0x16) = -((rand() & 0xF) + 0x10);
                    *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
                }
                i++;
            } while (i < 8);

            func_8002A04C((s32)p);
            if (*(s32 *)(*(s32 *)(p + 0x64) + 0xCC) != 0) {
                iv = *(s32 *)(*(s32 *)(p + 0x64) + 0xCC);
                *(s16 *)(iv + 0x76) = -1000;
                *(u16 *)(iv + 0x5E) = 2;
                *(u16 *)(iv + 0x5C) = *(u16 *)(iv + 0x5C) | 1;
            }
            func_8012C218(*(void **)(p + 0x64));
            func_8012C218(p);
            break;
        }
        i = *(s16 *)(*(s32 *)(p + 0x20) + 0x12);
        func_8001C214(*(s32 *)(p + 0x20), (s32)D_801C9488);
        func_8012A828((s32)p, D_801C833C);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) = i;
        *(s16 *)(p + 0xAE) = -1;
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;
    }

    func_80189390(p);
}



/* func_8018ECA0 — ov_SC06_018 / ov_SC06_018_jr_80191C50   (226 ins)
 *
 * A "sweeping beam" tick for the 0x318 boss-effect entity family — the same
 * entity class its already-MATCHED TU neighbour func_80191C50 drives
 * (src/ov_SC06_018/ov_SC06_018_jr_80191C50.c:2860).
 *
 *   - 3-way state machine on +0x34:
 *       0 = spawn the child (func_8012C658(0x318, 8, arg0)) -> +0xCC,
 *       1 = sweep -Z until 0x8C-z >= 0xFC, then state 2,
 *       2 = sweep +Z until z-0x8C >= 0xFC, then state 1.
 *   - then, if the child (+0xCC) exists: two func_8018AD9C draws (colours
 *     0x81818 / 0x204040), and TWO substep-interpolated hit sweeps that walk
 *     the beam origin backwards by `d` once per substep:
 *       (a) over the 0x60-entry entity table D_801202A0 (stride 0x10C),
 *           hit-testing each live entity with func_80135260 and, on a hit,
 *           stamping state 0x1D / timer 0xA / flag 1 / +0x62 = yaw-0x800;
 *       (b) against the player with func_8012DF34, stamping D_80126B98.
 *
 * @class: none — MATCH (226 ins), iteration 3.
 *
 * @lever (NEW, generalizable — loop.c `combine_givs` ANCHOR RULE):
 *   Iterations 1-2 were LENGTH-DRIFT +5 / +2 with an EXTRA induction register.
 *   All of the entity-record accesses (+0x20 +0x58 +0x5C +0x5E +0x60 +0x62
 *   +0xAE) are DEST_ADDR givs on the table pointer, and gcc-2.7.2 allocates
 *   ONE new pseudo for the combined group.  Which offset the group is
 *   ANCHORED at is not free: `record_giv` PREPENDS to `bl->giv`, and
 *   `combine_givs` walks that list from the head taking the first absorber —
 *   so the anchor is the **LAST address giv discovered in source order**.
 *   The target anchors at +0x5E (base $s3, giv $s0, offsets -0x3E..+0x50);
 *   my draft anchored at +0x62 because `*(u16*)(e+0x62) = ...` was the last
 *   store in the hit block, which forced a THIRD induction register (+$s7,
 *   +2 prologue/epilogue insns, +1 giv-init, +1 latch increment, +1 nop).
 *   FIX: reorder the hit block so the **+0x5E store is last** — pure source
 *   ordering, zero semantic change, and the scheduler still emits +0x62 last
 *   in the asm because it depends on a lw->lhu chain.
 *
 * @lever (§76 allocno CLASS): the spawn result, the +0xCC child pointer and
 *   the D_801202A0 table walker are ONE variable `e`.  Split into separate
 *   variables the first two are local, call-crossing-free allocnos and land
 *   in $a0 (first free in REG_ALLOC_ORDER); merged, the live range spans the
 *   func_80135260 loop, so calls_crossed > 0 forces a callee-saved reg and
 *   the whole chain coalesces onto $s3 — which is also what frees the
 *   `bnez $s3` delay slot for `addu $a0, $s2, $zero`.
 *
 * @lever (store order): `sp10.vy = sp18.vy = v` (not `sp18.vy = sp10.vy = v`)
 *   — `a = b = v` stores b first, and the target emits sh 0x1A before 0x12.
 */

extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8018AD9C(s32 param_1, u32 param_2, u16 *param_3, u32 param_4);
extern s32 func_8004787C(s32 a0);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80192F64_8018ECA0;

void func_8018ECA0(s32 arg0) {

    extern u8 D_801202A0[];
    extern u16 D_80126B98[];
    s32 e;
    s16 t;
    s32 i;
    s32 n;
    s32 d;
    SV_80192F64_8018ECA0 sp10;
    SV_80192F64_8018ECA0 sp18;
    SV_80192F64_8018ECA0 sp20;
    u16 sp28[2];

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        e = func_8012C658(0x318, 8, arg0);
        if (e != 0) {
            *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0xFC) & 1) + 1;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(e + 4) = *(s32 *)(e + 4) - *(s32 *)(arg0 + 0xDC);
            *(s32 *)(arg0 + 0xCC) = e;
            *(u16 *)(e + 0xFC) = *(u16 *)(arg0 + 0x36);
        }
        break;
    case 1:
        t = *(u16 *)(arg0 + 0xE) - 4;
        *(u16 *)(arg0 + 0xE) = t;
        if (*(s16 *)(arg0 + 0x8C) - t >= *(s16 *)(arg0 + 0xFC)) {
            *(u16 *)(arg0 + 0x34) = 2;
        }
        break;
    case 2:
        t = *(u16 *)(arg0 + 0xE) + 4;
        *(u16 *)(arg0 + 0xE) = t;
        if (t - *(s16 *)(arg0 + 0x8C) >= *(s16 *)(arg0 + 0xFC)) {
            *(u16 *)(arg0 + 0x34) = 1;
        }
        break;
    }

    e = *(s32 *)(arg0 + 0xCC);
    if (e == 0) {
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
        return;
    }
    *(s32 *)(e + 0xC) = *(s32 *)(arg0 + 0xC);
    sp28[0] = 0;
    sp28[1] = *(u16 *)(arg0 + 0xDE);
    func_8012B2CC(arg0);
    func_8018AD9C(arg0, 0, sp28, 0x81818);
    func_8018AD9C(arg0, 1, sp28, 0x204040);

    sp10.vx = *(u16 *)(arg0 + 6);
    sp10.vy = sp18.vy = *(u16 *)(arg0 + 0xA);
    sp10.vz = sp18.vz = *(u16 *)(arg0 + 0xE);
    e = (s32)D_801202A0;
    i = 0;
    d = func_8004787C(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) >> 4;
    do {
        if (*(u16 *)e != 0 && *(u16 *)e != 0x25D && *(u16 *)e != 0x318 &&
            (*(u16 *)(e + 0x5C) & 0x8000) != 0 && *(u16 *)(e + 0x5E) != 0x1D &&
            (*(u16 *)(e + 0xAE) & 1) == 0) {
            n = ((s16) * (u16 *)(arg0 + 0xDE) >> 8) + 1;
            sp18.vx = sp10.vx;
            sp20.vy = sp18.vy;
            sp20.vz = sp18.vz;
            do {
                sp20.vx = sp18.vx - d;
                if (func_80135260(*(s32 *)(e + 0x20), *(s32 *)(e + 0x58), &sp18.vx, &sp20.vx) == 1) {
                    *(u16 *)(e + 0x60) = 0xA;
                    *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
                    *(u16 *)(e + 0x62) = *(u16 *)(*(s32 *)(e + 0x20) + 0x12) - 0x800;
                    *(u16 *)(e + 0x5E) = 0x1D;
                    n = 1;
                }
                n--;
                sp18.vx = sp18.vx - d;
            } while (n != 0);
        }
        e += 0x10C;
        i++;
    } while (i < 0x60);

    n = ((s16) * (u16 *)(arg0 + 0xDE) >> 8) + 1;
    sp18.vx = sp10.vx;
    sp20.vy = sp18.vy;
    sp20.vz = sp18.vz;
    do {
        sp20.vx = sp18.vx - d;
        if (func_8012DF34(arg0, (s32)&sp18.vx, (s32)&sp20.vx) == 1) {
            D_80126B98[0] = 0x96;
            D_80126B98[-1] = 0x4018;
            n = 1;
        }
        n--;
        sp18.vx = sp18.vx - d;
    } while (n != 0);
}


extern s16 D_801C8414;

void func_8018F028(int arg0)
{
    if (*(u8 *)(arg0 + 0xC2) != 0) {
        *(u8 *)(arg0 + 0xC2) -= 1;
        if ((*(u8 *)(arg0 + 0xC2) & 0xFF) == 0) {
            *(u16 *)(arg0 + 0x5E) = 0;
        }
    }
    ((void (*)(void)) *((void **) &D_801C8414 + *(unsigned short *)(arg0 + 2)))();
}


void func_8018F088(void) {
}

void func_8018F090(void) {
}

extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

void func_8018F098(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;

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

    v1 = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v1;
    if (v1 < 0x10) {
        if (v1 == 0) {
            func_8012C218((void *)s0);
        }
    }
}


extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80189390(void *a0);

void func_8018F194(s32 arg0) {
    s32 e;

    *(u16 *)(arg0 + 0xE8) = (*(u8 *)(arg0 + 0xC2) << 4) + 0x100;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        e = func_8012C658(0x318, 6, arg0);
        if (e != 0) {
            *(u16 *)(e + 6) = *(u16 *)(e + 6) - 0x30;
            *(u16 *)(e + 0xA) = *(u16 *)(e + 0xA) - 0xF0;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x10) = 0xC00;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x12) = 0x400;
            *(s32 *)(arg0 + 0xCC) = e;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        break;
    case 1:
        break;
    case 2:
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x40;
        if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) == 0x1000) {
            e = *(s32 *)(arg0 + 0xCC);
            *(u16 *)(arg0 + 0xAE) = 0;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            *(u16 *)(e + 0x34) = *(u16 *)(e + 0x34) + 1;
        }
        break;
    }

    func_80189390((void *)arg0);
}


void func_8018F2BC(void) {
}

extern void func_8012B23C();
extern void func_8012C218(void *a0);
extern void func_8012CBCC(s32 a0);
extern u8 *func_8012913C(s32 a0);

void func_8018F2C4(s32 param_1)
{
    s32 iv;
    u32 ret;

    if (*(u16 *)(param_1 + 2) == 0) {
        *(u8 *)(param_1 + 0xC0) = 1;
        *(u16 *)(param_1 + 2) += 1;
        func_8012B23C(param_1);
        *(s32 *)(param_1 + 0x1C) = 1;
        return;
    }
    *(s32 *)(param_1 + 0xDC) = *(s32 *)(param_1 + 0x14);
    ret = ((s32 (*)(s32))func_8012CBCC)(param_1);
    if (ret != 0 && (ret & 0x6000) != 0) {
        if (--*(s32 *)(param_1 + 0x1C) == 0) {
            goto kill;
        }
        *(s32 *)(param_1 + 0x14) = -*(s32 *)(param_1 + 0xDC) >> 2;
    }
    if ((++*(u16 *)(param_1 + 0xFC)) & 1) {
        iv = (s32)func_8012913C(0x23);
        if (iv != 0) {
            *(u16 *)((u8 *)iv + 6) = *(u16 *)(param_1 + 6);
            *(u16 *)((u8 *)iv + 0xA) = *(u16 *)(param_1 + 0xA);
            *(u16 *)((u8 *)iv + 0xE) = *(u16 *)(param_1 + 0xE);
            *(u32 *)((u8 *)iv + 0x18) = 0;
            *(u32 *)((u8 *)iv + 0x14) = 0;
            *(u32 *)((u8 *)iv + 0x10) = 0;
            *(u16 *)((u8 *)iv + 0x34) = 0x3000;
        }
    }
    if (*(s16 *)(param_1 + 0xA) < 0x20) {
        return;
    }
kill:
    func_8012C218((void *)param_1);
}



extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8018F3E0(param_1, param_2)
s32 param_1;
s32 param_2;
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



/* TU declares func_8018F518 as void(void) (S35 self-axis) but the asm takes
 * $a0 as a pointer parameter — bind through a private C name. */
extern void aF8017ED80(void *param_1) __asm__("func_8018F518");

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



/* func_8018F6EC -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (open-only h_norm
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
 * Tail always calls ((void (*)(void *))func_8018F518)(a0) (the TU's canonical decl for this
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
 * `extern void func_8018F6EC(void);` (L4082, L4091) for callers that invoke it with NO args,
 * while the byte-true definition takes an s32 in $a0 -> `conflicting types`. Neither side can
 * move (a no-prototype escape is illegal once a param promotes), so the DEFINITION gets a
 * private C identifier and binds the emitted symbol with a GNU asm label. Zero blast radius:
 * the TU's declaration never meets the definition, and the emitted symbol is unchanged. */
void aF8017EF54(s32 a0) __asm__("func_8018F6EC");

void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern void func_8018F518(void);
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
        ((void (*)(void *))func_8018F518)((void *)p);
    }
}



extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_8018F518(void);

void func_8018F898(s32 a0)
{

    extern s32  D_801151D4;
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
        ((void (*)(s32))func_8018F518)(a0);
    }
}



extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8018F3E0();

void func_8018FA80(s32 a0)
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
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
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
            if (func_8018F3E0(a0, 0x51) == 0) {
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
        ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
        break;
    }
    case 1: {
        s32 ret;

        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_8018F3E0(a0, 0x51) == 0) {
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
        func_8018F3E0(a0, 0x51);
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
        if (func_8018F3E0(a0, 0x51) != 0) {
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




extern s32 func_80188BF8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);


void func_8018FDBC(s32 param_1)
{
    extern u8 D_800AF648_b __asm__("D_800AF648");

    extern u8 D_801C959C;
    extern u8 D_801C95A4;
    extern u8 D_801C95AC;
    extern u8 D_800AF648;
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

            func_80188BF8(param_1, (s32)&D_801C959C);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801C95A4, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801C95AC, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
            L.rv[1] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
            L.rv[2] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
            { void *r4; r4 = &D_800AF648; func_8004914C(r4); }
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


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80190064;









void func_80190064(s32 a0)
{

    extern s16 D_801C95B4[];
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
    {
        s16 idx = *(s16 *)(a0 + 0x70);
        s16 *p = &D_801C95B4[(idx - 1) * 4];
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


extern s32 D_801C95D4[];
extern s32 func_8012C044(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C098(void *a0);
extern void func_8018F6EC(void);

void func_80190194(s32 a0)
{
    void (*handler)(s32);

    handler = (void (*)(s32))D_801C95D4[*(u16 *)(a0 + 0x2)];
    handler(a0);

    if (*(u16 *)(a0 + 0x0) == 0)
        return;

    ((void (*)(s32))func_8018F6EC)(a0);

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



extern void (*D_801C9600[])(void);

void func_8019026C(void *a0) {
    D_801C9600[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 D_801C9608;
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C();
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

void func_801902A8(s32 a0)
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
        func_8012B14C(a0, *(s16 *)(a0 + 0x70) * 12 + (s32)&D_801C9608);

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



extern void (*D_801C9620[])(void);

void func_8019041C(void *a0) {
    D_801C9620[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_80190458(s32 a0)
{
    if (*(s16 *)(a0 + 0x70) != 0) {
        *(u16 *)(a0 + 0x2) = 4;
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x5E) = 0;
        *(u8 *)(a0 + 0xC1) = 0;
    } else {
        if (*(s32 *)(a0 + 0xCC) != 0)
            func_80016714(*(void **)(a0 + 0xCC), 0x84);
        if (*(s32 *)(a0 + 0xD0) != 0)
            func_80016714(*(void **)(a0 + 0xD0), 0x84);
        func_8002A04C(a0);
        func_8012C218((void *)a0);
    }
}



extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018F518(void);

void func_801904E0(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8018F518)(a0);
}




extern void func_8018F6EC(void);
    void func_80190518(s32 *param) {
        *(s16 *)(*(s32 *)((char *)param + 0x20) + 0x10) = 0xE00;
        func_8018F6EC();
    }


extern void func_8018F6EC(void);
    void func_80190540(s32 *a0) {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(v1 + 0x10) += 0x20;
        func_8018F6EC();
    }


extern void func_8018F6EC(void);

void func_80190574(s32 a0) {
    if (*(s16 *)(a0 + 0x76) < 0) {
        func_80131E00(a0, 6);
    } else {
        *(u16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x100) = 0x3C;
        *(u16 *)(a0 + 0x34) = 0;
        func_8018F6EC();
    }
}



extern int func_80143C74(short*, int);
extern s32 rand(void);
extern void func_8018F6EC(void);

void func_801905C0(s32 a0)
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
        ((void (*)(s32))func_8018F6EC)(a0);
    }
}


extern void func_8018F518(void);
    void func_801906AC(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x10) >> 1;
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0x18) >> 1;
        ((void (*)(void))func_8018F518)();
    }


extern void func_8018F518(void);
    void func_801906E0(s32 a0) {
        s32 v0;
        v0 = 0xC;
        *(s8 *)(a0 + 0xC1) = v0;
        *(s32 *)(a0 + 0x1C) = 0x3C;
        ((void (*)(void))func_8018F518)();
    }


extern void func_801319E0(s32 a0);
extern void func_80131C78(s32 a0);
extern void func_8018F518(void);

void func_8019070C(s32 a0) {
    s16 var;

    var = *(s16 *)(a0 + 0xA);
    if (var >= 0x10) {
        func_801319E0(a0);
    } else if (func_8012BEE8(a0) != 0) {
        func_80131E00(a0, 6);
    } else {
        if ((func_8012CBF4(a0) & 0x2000) != 0) {
            func_80131C78(a0);
        }
        ((void (*)(s32))func_8018F518)(a0);
    }
}


void func_80190798(s32 a0)
{
    extern u8 D_801C94A0[];
    extern u8 D_801CB1E0[];
    extern u8 D_801C94D4[];
    extern u8 D_801CAEF0[];
    extern u8 D_801CB1C8[];
    extern s32 D_80191B60[];
    extern void func_8012B200(u8 *a0);
    extern void func_80143970();
    extern void func_8012C1B8(void);

    s32 s0;
    u16 t;

    if (func_8012C354(a0, D_801C94A0) == 0) {
        return;
    }
    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -0x1001;
    ((s32 (*)(s32))func_80143970)(a0);
    func_8012A828(a0, D_801CB1E0);
    *(u16 *)(a0 + 0x2) += 1;
    func_8012B200((u8 *)a0);
    *(s32 *)(a0 + 0xBC) = (s32)D_801C94D4;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        goto fail;
    }
    *(s32 *)(a0 + 0xCC) = s0;
    func_8001C214(s0, (s32)D_801CAEF0);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_80191B60;
    *(u16 *)(s0 + 0x2C) = t;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        func_80016714((void *)*(s32 *)(a0 + 0xCC), 0x84);
fail:
        func_8012CAE4(a0);
        return;
    }
    *(s32 *)(a0 + 0xD0) = s0;
    func_8001C214(s0, (s32)D_801CB1C8);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_80191B60;
    *(u16 *)(s0 + 0x2C) = t;
    *(u16 *)(a0 + 0x100) = 0x3C;
    *(s32 *)(a0 + 0xDC) = 0xFFFC0000;
}




extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern s32 func_8018F3E0();
extern s32 func_8012B8E4(s32 arg0, s32 arg1);

void func_801908C0(s32 a0)
{

    extern s32 D_80126B60;
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
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
    func_8012CBCC(a0);
    func_8018F3E0(a0, 0x51);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    *(u16 *)(a0 + 0x100) -= 1;
    if (*(s16 *)(a0 + 0x100) == 0) {
        *(s16 *)(a0 + 2) = 3;
        *(u16 *)(a0 + 0x100) = 5;
        *(s32 *)(a0 + 0x1C) = 0;
    }
}


void func_801909F4(s32 a0) {
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


extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801CB2C0[];
extern s32 D_80191B60[];

void func_80190A54(s32 param_1)
{
    s32 v0;
    s32 v1;
    s32 r;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(v0, (s32)D_801CB2C0);
        func_8012A828(param_1, D_80191B60);
        v1 = *(s32 *)(param_1 + 0x64);
        *(u16 *)(param_1 + 2) = 1;
        *(s32 *)(param_1 + 0x1C) = 0x40;
        r = *(s32 *)(param_1 + 0x20);
        *(u16 *)(r + 0x10) = *(u16 *)(*(s32 *)(v1 + 0x20) + 0x10);
        r = *(s32 *)(param_1 + 0x20);
        *(u16 *)(r + 0x12) = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
        r = *(s32 *)(param_1 + 0x20);
        *(u16 *)(r + 0x14) = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x14);
    }
}


extern void func_8012C218(void *a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012B370(int a0);
extern u8 D_800D3918[];
extern u8 D_801C95EC;
extern u8 D_801C95F8;

void func_80190B14(s32 param_1) {
    s32 v0;

    if ((*(s16 *)(param_1 + 6) == *(s16 *)(param_1 + 0xDE)) &&
        (*(s16 *)(param_1 + 0xE) == *(s16 *)(param_1 + 0xE2))) {
        ((void (*)(s32))func_8012C218)(param_1);
        return;
    }

    *(s32 *)(param_1 + 0xDC) = *(s32 *)(param_1 + 4);
    *(s32 *)(param_1 + 0xE0) = *(s32 *)(param_1 + 0xC);
    func_8012B14C(param_1, (s32)&D_801C95EC);

    func_8012AD80(param_1);

    v0 = func_8012D5E4(param_1, (s32)&D_801C95F8, (s32)D_800D3918, 0x30);
    if (v0 != 0) {
        ((void (*)(s32))func_8012C218)(param_1);
        return;
    }

    v0 = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    } else {
        func_8012B370(param_1);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 rand(void);
extern u8 D_801CB380[];

void func_80190BE8(s32 param_1)
{
    *(s32 *)(param_1 + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(param_1 + 0x20) == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801CB380);

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


void func_80190CE0(s32 a0) {
    extern u8 D_801CB498[];
    extern u8 D_801CC8B4[];
    extern u8 D_801CB4D8[];
    extern u8 D_801CC8BC[];
    extern u8 D_801CB4E4[];
    extern u8 D_801CB51C[];
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012C1B8(void);
    extern int func_8012C354();
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8012A828(s32, void *);
    extern void func_8012B23C(void *);
    extern void func_8012CAE4(s32 a0);
    s32 s0;
    s32 s2;
    s16 s1;

    if (func_8012C354(a0, D_801CB498) == 0) {
        return;
    }
    s1 = *(s16 *)(a0 + 0x70);
    if (s1 != 1) {
        if (s1 < 2) {
            if (s1 != 0) {
                return;
            }
        } else if (s1 != 2) {
            return;
        }
        s0 = ((s32 (*)(void))func_8012C1B8)();
        if (s0 == 0) {
            goto fail;
        }
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001C214(s0, (s32)D_801CC8B4);
        s2 = (s32)D_801CB4D8;
        *(s32 *)(s0 + 0x20) = s2;
        func_8001D0E8(s0, 0x280, 0x1E0);
        s0 = ((s32 (*)(void))func_8012C1B8)();
        if (s0 == 0) {
        fail:
            func_8012CAE4(a0);
            return;
        }
        *(s32 *)(a0 + 0xD0) = s0;
        func_8001C214(s0, (s32)D_801CC8BC);
        *(s32 *)(s0 + 0x20) = s2 - 0xC;
        func_8001D0E8(s0, 0x280, 0x1E0);
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = 0;
        *(s32 *)(a0 + 0xC4) = 3;
        func_8012A828(a0, D_801CB4E4);
        *(u16 *)(a0 + 2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s32 *)(a0 + 0xBC) = (s32)D_801CB51C;
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x280, 0x1E0);
        return;
    } else {
        *(u8 *)(a0 + 0xC0) = 1;
        *(u16 *)(a0 + 0x5C) = 0;
        func_8012B23C(a0);
        *(u16 *)(a0 + 2) = 3;
        *(u8 *)(a0 + 0x75) = 0;
        *(s32 *)(a0 + 0x1C) = 10;
    }
}


/* func_80190E64 — ov_SC06_033 — 3-state (0/1/2 on +0x34) boss-intro/spawn driver.
   match_one MATCH 302/302, all 53 relocations audited against the .s (law 1c).

   Levers, in the order they mattered (each byte-proven on this function):

   1. `first = D_801CB512;` — the 16-entry u16 rotate (house style of the already-banked
      func_801916BC in this TU) must load `first` through the SYMBOL, not `*q1`: the target
      has `lui/lhu %lo(D_801CB512)`, and the load must be written BEFORE `k = 0` (§3-T2).
   2. `*(u16 *)(e + 6) = *(s16 *)(e + 6) - 0x40 + (rand() & 0x7F);` — the s16 LOAD is the
      dial.  Read as u16 the fold+narrowing produces a u16 `0xFFC0` constant that local-alloc
      parks in $s0 (a 1-block pseudo crossing one call), which then bars `e` from $s0 in BOTH
      cases and cascades through the whole callee-saved file (75 residual rows).  Read as s16
      the narrowed HImode arithmetic is signed, the negated constant sign-extends to -64 and
      becomes `addiu $v1,$v1,-0x40` on the FIELD side, then `addu` with the rand term.
      (Ablated 19 spellings; `(u16)(f - K)` cast and `+= (r) - K` both keep the 0xFFC0 reg.)
   3. ONE `p` variable for `*(s32 *)(a0 + 0xCC)` in case 0 AND case 1 — a global pseudo that
      does not cross calls gets the lowest used-so-far reg not conflicting with the local
      RMW temps: $a0 in both blocks (a per-block temp gets $v1).
   4. `i = rand() % 100` reuses the case-0 counter — that pseudo must cross calls to land in
      $s1 (an 8-ref/12-insn temp takes $a1); it also lifts `i` above the D_801CB52C giv in
      allocno order so the giv falls through to $s3 (pass 1: s0..s2 taken), and `tbl` then
      shares $s3 with it in pass 0.
   Free from the shape: `while (*tp <= i) tp += 3;` (duplicate_loop_exit_test + reorg's
   delay-slot steal with the `addiu -6` undo), `-(cond) & 0x1E` (store_flag normalised to -1,
   L9163), u16 dividend -> `multu 0xAAAAAAAB` (§201-D), state in $s0 reused for the `== 2`
   compare via record_jump_equiv. */
extern u8 D_80078E78[];
extern u16 D_801CB512;
extern u16 D_801CB514;
extern u16 D_801CB4F4;
extern s32 D_801CB52C[];
extern u8 D_801CB540[];
extern u8 D_801CB4CC[];
extern s16 D_801CB398[];
extern u8 D_801CD99C[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800599B8();
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern int func_80143C74(short *, int);
extern void func_80128EA8();
extern void func_80016714(void *a0, s32 a1);
extern void func_8002A04C(s32 a0);

void func_80190E64(s32 a0)
{
    u16 *tbl = (u16 *)D_80078E78;
    s32 e;
    s32 i;
    s32 child;
    s32 off;
    s16 *tp;
    s32 t;
    s32 p;
    s16 cnt;
    u16 *q1, *q2;
    u16 first, v;
    s32 k;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        func_8002D4C8(0xB33, 0);
        q1 = &D_801CB512;
        q2 = &D_801CB512 - 1;
        first = D_801CB512;
        k = 0;
        do {
            v = *q2;
            q2--;
            k++;
            *q1 = v;
            q1--;
        } while (k < 0xF);
        *q1 = first;
        func_800599B8(&D_801CB514, &D_801CB4F4);
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(p + 0x2C) |= 0x10;
        for (i = 0; i < 5; i++) {
            e = func_8012C658(0x33C, 1, a0);
            if (e != 0) {
                func_8001C214(*(s32 *)(e + 0x20), D_801CB52C[i]);
                *(u16 *)(e + 0x12) = (rand() & 0xF) - 8;
                *(u16 *)(e + 0x1A) = (rand() & 0xF) - 8;
                *(u16 *)(e + 0x16) = -((rand() & 7) + 7);
                *(u16 *)(e + 0xFC) = (rand() & 0x3F) + 4;
                *(u16 *)(e + 0xFE) = (rand() & 0x3F) + 4;
                *(u16 *)(e + 0x100) = (rand() & 0x3F) + 4;
                *(u16 *)(e + 0xA) -= 0x30;
            }
        }
        func_8001C214(*(s32 *)(a0 + 0x20), (s32)D_801CD99C);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)D_801CB4CC;
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x280, 0x1E0);
        *(u16 *)(a0 + 0x34) += 1;
        break;
    case 1:
        q1 = &D_801CB512;
        q2 = &D_801CB512 - 1;
        first = D_801CB512;
        k = 0;
        do {
            v = *q2;
            q2--;
            k++;
            *q1 = v;
            q1--;
        } while (k < 0xF);
        *q1 = first;
        func_800599B8(&D_801CB514, &D_801CB4F4);
        e = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
        if (e != 0) {
            child = *(s32 *)(e + 0xCC);
            *(u16 *)(child + 0x18) = rand() % 0x2000 + 0x3000;
            *(u16 *)(child + 0x1A) = rand() % 0x2000 + 0x3000;
            func_80128EA8(child, e + 0xD0, (s32)D_801CB540);
            *(u16 *)(e + 0x6) = *(s16 *)(e + 0x6) - 0x40 + (rand() & 0x7F);
            *(u16 *)(e + 0xE) = *(s16 *)(e + 0xE) - 0x40 + (rand() & 0x7F);
            *(u16 *)(e + 0xA) = *(u16 *)(e + 0xA) - (rand() & 0x7F);
        }
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(p + 0x18) -= 0x88;
        *(u16 *)(p + 0x1A) -= 0x88;
        *(u16 *)(p + 0x1C) -= 0x88;
        if (*(s16 *)(p + 0x18) < 0x89) {
            *(u16 *)(a0 + 0x34) += 1;
            func_80016714(*(void **)(a0 + 0xCC), 0x84);
            *(s32 *)(a0 + 0xCC) = 0;
            if (*(s16 *)(a0 + 0x70) == 1) {
                off = -((u16)(tbl[0x1D] / 3) >= tbl[0x1E]) & 0x1E;
                if ((u16)(tbl[0x1F] / 3) >= tbl[0x20]) {
                    off += 0x3C;
                }
                tp = &D_801CB398[off];
                i = rand() % 100;
                while (*tp <= i) {
                    tp += 3;
                }
                t = func_8012C658(tp[1], tp[2], a0);
                if (t != 0) {
                    *(u16 *)(t + 0xA) -= 0x40;
                }
            }
        }
        break;
    case 2:
        *(u16 *)(a0 + 0xFC) = cnt = *(u16 *)(a0 + 0xFC) + 1;
        if (cnt >= 0x20) {
            func_80016714(*(void **)(a0 + 0xD0), 0x84);
            *(s32 *)(a0 + 0xD0) = 0;
            *(u16 *)(a0 + 0x34) += 1;
            if (*(s16 *)(a0 + 0x70) == 2) {
                *(u16 *)(a0 + 0x34) = 0;
                *(u16 *)(a0 + 2) = 4;
            }
            func_8002A04C(a0);
        }
        break;
    }
}


extern void func_8012BE54(s32);
extern s32 func_8012B8A4(s32);
extern s32 func_8004787C(s32);
extern s32 func_80047948(s32);
extern void func_8012C218(void *);
extern u8 D_801202A0[];
extern u8 D_80126B5C;
extern u8 D_80126B64;

void func_8019131C(s32 arg0) {
    s32 s0;
    s16 t;
    s32 i;
    u16 *p;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (((s32 (*)(s32))func_8012BE54)(arg0) > 0x9000) {
            *(u16 *)(arg0 + 0x34) = 1;
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_8012BE54)(arg0) <= 0x9000) {
            s0 = ((s32 (*)(s32))func_8012B8A4)(arg0);
            *(s32 *)&D_80126B5C = *(s32 *)(arg0 + 4) - ((s32 (*)(s32))func_8004787C)(s0) * 0xC00;
            *(s32 *)&D_80126B64 = *(s32 *)(arg0 + 0xC) - ((s32 (*)(s32))func_80047948)(s0) * 0xC00;
        }
        *(u16 *)(arg0 + 0xA) = t = *(u16 *)(arg0 + 0xA) + 4;
        if ((s16)t - *(s16 *)(arg0 + 0x8A) < 0xC0) {
            break;
        }
        p = (u16 *)D_801202A0;
        i = 0;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x80000000;
        do {
            if (*p == 0x350) {
                *(s32 *)(p + 4) = *(s32 *)(arg0 + 8);
                *(u32 *)(*(s32 *)(p + 0x10) + 4) &= 0x7FFFFFFF;
                *(p + 1) += 1;
            }
            p += 0x86;
            i++;
        } while (i < 0x60);
        func_8012C218((void *)arg0);
        break;
    }
}


extern void (*D_801CB590[])(void);

void func_801914A0(short *param_1) {
    int iVar2;
    short var_v1;

    (*D_801CB590[(unsigned short)param_1[1]])();
    if (*(unsigned short *)param_1 != 0) {
        if (*(short *)(param_1 + 0x38) == 0 || *(short *)(param_1 + 0x38) == 2) {
            iVar2 = *(int *)(param_1 + 0x66);
            if (iVar2 != 0) {
                *(short *)(iVar2 + 8) = *(unsigned short *)(param_1 + 3);
                *(short *)(iVar2 + 10) = *(unsigned short *)(param_1 + 5);
                *(short *)(iVar2 + 12) = *(unsigned short *)(param_1 + 7);
            }
            iVar2 = *(int *)(param_1 + 0x68);
            if (iVar2 != 0) {
                *(short *)(iVar2 + 8) = *(unsigned short *)(param_1 + 3);
                *(short *)(iVar2 + 10) = *(unsigned short *)(param_1 + 5) + *(unsigned short *)(param_1 + 0x7e);
                *(short *)(iVar2 + 12) = *(unsigned short *)(param_1 + 7);
            }
            if (param_1[0x7f] != 0) {
                var_v1 = param_1[0x7f] - 1;
                param_1[0x7f] = var_v1;
                if (var_v1 == 0) {
                    param_1[0x2f] = 0;
                }
            }
        }
    }
}


extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern int D_801CB388;

void func_801915A8(s32 param_1)
{
    s32 iVar1;
    s32 state;

    *(u8 *)(param_1 + 0xc1) = 0;
    state = *(u8 *)(param_1 + 0x5e);
    if (*(s16 *)(param_1 + 0x60) != 0) {
        if (state == 0x1d) {
            *(u16 *)(param_1 + 0x82) = 0;
            *(u16 *)(param_1 + 0x7c) = *(u16 *)(param_1 + 6);
            *(u16 *)(param_1 + 0x7e) = *(u16 *)(param_1 + 0xa);
            *(u16 *)(param_1 + 0x80) = *(u16 *)(param_1 + 0xe);
        }
        if ((*(s32 *)(param_1 + 0x78) != 0) && (*(s16 *)(param_1 + 0x60) != 0)) {
            iVar1 = *(s16 *)(param_1 + 0x60) * *(s16 *)(*(s32 *)(param_1 + 0x78) + 0x30) >> 12;
            if (iVar1 < 1) {
                iVar1 = 1;
            }
        } else {
            iVar1 = *(s16 *)(param_1 + 0x60);
        }
        *(u16 *)(param_1 + 0x76) = *(u16 *)(param_1 + 0x76) - iVar1;
        func_8016AA50(param_1, iVar1);
        if (*(u16 *)(param_1 + 0x82) & 1) {
            func_8016B428(param_1);
            func_80019064(&D_801CB388);
        }
    }
    if (*(s16 *)(param_1 + 0x76) <= 0) {
        *(u16 *)(param_1 + 0x5c) = 0;
        *(u16 *)(param_1 + 2) = 2;
    } else {
        *(u16 *)(param_1 + 0xfe) = 0x10;
        *(u16 *)(param_1 + 0x5c) &= 0xfffe;
    }
}


void func_801916BC(void) {
    extern u16 D_801CB512;
    extern u16 D_801CB514;
    extern u16 D_801CB4F4;
    u16 *p;
    u16 *q;
    u16 first;
    u16 v;
    s32 i;

    p = &D_801CB512;
    q = &D_801CB512 - 1;
    i = 0;
    first = *p;
    do {
        v = *q;
        q--;
        i++;
        *p = v;
        p--;
    } while (i < 0xF);
    *p = first;
    func_800599B8(&D_801CB514, &D_801CB4F4);
}


extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

void func_8019171C(s32 param_1)
{
    u32 uVar1;
    s32 iVar2;

    *(s32 *)(param_1 + 0xDC) = *(s32 *)(param_1 + 0x14);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) += *(u16 *)(param_1 + 0xFC);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) += *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) += *(u16 *)(param_1 + 0x100);

    uVar1 = ((s32 (*)(s32))func_8012CBCC)(param_1);
    if (uVar1 != 0 && (uVar1 & 0x6000) != 0) {
        iVar2 = *(s32 *)(param_1 + 0x1C) - 1;
        *(s32 *)(param_1 + 0x1C) = iVar2;
        if (iVar2 == 0) goto LAB_801917CC;
        *(s32 *)(param_1 + 0x14) = -*(s32 *)(param_1 + 0xDC) >> 2;
    }
    if (*(s16 *)(param_1 + 0xA) < 0x20) {
        return;
    }
LAB_801917CC:
    func_8012C218((void *)param_1);
    return;
}






