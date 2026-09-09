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
typedef struct { u16 x, y, z, w; } V4_80188E10_80183BB4;
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
} Ent_80188E10_80183BB4;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8019585C;
extern u8 D_801957CC;
extern u8 D_801957A8;
extern u8 D_80195784;
extern u8 D_80195838;
extern u8 D_80195814;
extern u8 D_801957F0;
extern u8 D_80195760;
extern void func_80145934(void);
extern u8 D_801958EC;
extern u8 D_801958C8;
extern u8 D_801958A4;
extern u8 D_80195880;
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
extern unsigned char D_80194CE4[];
extern unsigned char D_80194D14[];
extern unsigned char D_80194D64[];
extern unsigned char D_80194D94[];
extern unsigned char D_80194DC4[];
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
extern void (*D_80194E14[])(void *);
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
extern s32 D_80194EDC[];
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
extern u8 D_80194F64[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80194F6C;
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
extern int D_801CF340;
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
extern s32 D_801CF344;
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
extern s32 D_80194F9C;
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
extern void (*D_80195044[])(void);
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
extern void (*D_80195068[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80195058;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019507C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80195088[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80195098[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801950B0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801950A0;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801950C4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801950E0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801950D0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801950F4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80195108[])(void);
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
extern s32 D_8019511C;
extern void (*D_80195144[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80195124;
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
extern int (*D_80195190[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80195194[])(void);
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
extern unsigned short D_801955F8[];
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
extern void (*D_80195608[])(void);
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
extern int D_801CF378;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80195630[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80195610;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80195620;
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
extern void (*D_80195670[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80195678[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80195644;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80195684[])(void);
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
extern u8 D_80195654;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801CF380;
extern s32 D_801CF38C;
extern s32 D_801CF390;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801956C0[])(s32 *);
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
extern s32 D_80195694[];
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
extern s32 D_801CF388;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80195910[])(void);
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
extern char D_80195730[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801959B4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80195B08[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80195924;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80195B10[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80195934;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80195954;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80195B18[])(void);
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
extern void (*D_80195B40[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80195B4C[])(void);
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
extern void (*D_801959C0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80195BF0;
extern void func_8015D380(s32 a0);
extern unsigned char D_80194CD4[];
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
extern unsigned char D_80195C04[];
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
extern s8 D_80195C40[];
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
extern u16 D_80195C88;
extern u16 D_80195C8A;
extern u16 D_80195C8C;
extern s32 D_80195C90;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80195C98;
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
extern int D_801959A4;
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
extern unsigned int D_80195D1C[];
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
extern void (*D_80195DCC[])(void);
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
extern u16 D_80195DFC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80195E60;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801CF398[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80195E84[])(void);
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
extern int D_801CF3F0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80195ECC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80195EBC;
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
extern char D_801CEA74[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80195ED4[])(void);
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
extern void (*D_80195F28[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80195EF0;
extern s16 D_80195F24;
extern s16 D_80195F22;
extern s16 D_80195F20;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80195F34[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801CF450;
extern u8 D_801CF451;
extern u8 D_801CF452;
extern u8 D_801CF453;
extern u8 D_801CF454;
extern u8 D_801CF455;
extern u8 D_801CF456;
extern u8 D_801CF457;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80195F44[])(void);
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
extern s32 D_801CF490;
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
extern void (*D_80195F88[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80196004[];
extern s32 D_80196024[];
extern u8 D_801960A0[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801960C0[];
extern u8 D_801960E0[];
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
extern void (*D_8019617C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801961F8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801CEA84;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80196204[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8019620C[])(void);
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
extern void (*D_801962D4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801962E4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801962F4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80196300[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80196260[];
extern u8   D_80196274[];
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
extern void (*D_80196318[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80196320[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80196328[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80196330[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80196338[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80196340[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80196348[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801963FC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80196404[])(void);
extern void func_80169F00(void *a0);
extern char D_801963B4[];
extern char D_80196374[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8019643C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80196448[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80196490[])(void);
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
extern void (*D_8019650C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801CF7B0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80196500[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80196544[];
extern unsigned short D_8019654C[];
extern unsigned short D_80196554[];
extern unsigned char D_801CF7B8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801CF7B0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019655C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801CF8EC;
extern M2C_UNK D_801CF8F0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801CF878;
extern void (*D_8019658C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801CF8F4[];
extern u8 D_801CF8FC[];
extern u8 D_801CF8AC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80196594[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801965B0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801965B8[])(void);
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
extern void (*D_80196620[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801965C4;
extern u8 D_801965D0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80196654[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019665C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801966B0[])(void);
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
extern u16 D_801966E4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801966D4[];
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
extern s32 D_80196700;
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
extern void (*D_80196778[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80196780[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80196788[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80196790[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80196798[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801967A0[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801967AC[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801967B8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801967C4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801967D4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801967E4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801967EC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801967F4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801967FC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80196804[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8019680C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80196814[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8019681C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80196824[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8019682C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80196834[])(void);
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
extern void (*D_8019683C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80196844[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8019684C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80196854[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8019685C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80196864[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8019686C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80196874[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8019687C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80196884[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8019688C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80196894[])(void);
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
extern void (*D_801968D8[])(void);
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
extern M2C_UNK D_8019689C;
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
extern void (*D_80196908[])(void);
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
extern void (*D_80196944[])(void);
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
extern void (*D_8019699C[])();
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
extern void (*D_801969AC[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801969B4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80196B1C[])();
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
extern void (*D_80196B28[])();
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
extern M2C_UNK D_801CECCC;
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
extern s16 D_801D10F8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D0030;
extern short D_801D116C;
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
extern s32 D_801D045C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D0484;
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
extern s16 D_801D0440;
extern s32 func_8017A3B0(void);
extern short D_801D047C;
extern short D_801D0478;
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
extern s16 D_801D0444;
extern u16 D_801D04C4;
extern u16 D_801D04C6;
extern u16 D_801D04C8;
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
extern s16 D_801D04BC;
extern s16 D_801D04BE;
extern s16 D_801D04C0;
extern s16 D_801D04B4;
extern s16 D_801D04B6;
extern s16 D_801D04B8;
extern void func_8017B7A8(void);
extern s16 D_801D04D4;
extern s16 D_801D04D6;
extern s16 D_801D04D8;
extern s16 D_801D04DC;
extern s16 D_801D04DE;
extern s16 D_801D04E0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D04CC;
extern short D_801D04CE;
extern short D_801D04D0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D0464;
extern SV4 D_801D046C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D048C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D0488)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80196D04[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80196D1C[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);
extern void func_8017C24C(s32 arg0);
extern void (*D_80196D98[])(void);
extern void func_8017D14C(void *a0);
extern void func_8017D37C(void);
extern s32 func_8017D188(s32 a0);
extern s32 func_8017D1CC(void);
extern void func_8017D3A4(void);
extern s32 func_8017D1F0(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D230(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D2AC(void);
extern void (*D_80196DAC[])(void);
extern void func_8017D2CC(void *a0);
extern s32 func_8017D308(s32 a0);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D464(void *a0);
extern void func_8017D3CC(void);
extern void (*D_80196DD8[])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D5E4(s32 param_1, s16 *param_2);
extern void (*D_80196DE0[])(void);
extern void func_8017D894(void *a0);
extern s32 func_8017DBF4(void);
extern void func_8017DBFC(void *a0);
extern void func_8017DC54(s32 a0);
extern void func_8017DE84(s32 a0);
extern void func_8017DED8(void);
extern s32 func_8017DEFC(void);
extern void (*D_80196E1C[])(void);
extern void func_8017DF40(void *a0);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017E170(void*);
extern void func_8017E140(s32*);
extern void func_8017DF7C(int param_1);
extern s32 func_8017E184(s32 *a0, s32 a1);
extern void func_8017E140(s32 *a0);
extern void func_8017E0C8(s32 *a0);
extern void func_8017E140(s32 *param_1);
extern void func_8017E170(void *a0);
extern void (*D_80196E54[])(void);
extern void func_8017E1EC(void *a0);
extern void func_8017E228(s32 param_1);
extern void func_8017E2C4(s32 param_1);
extern void func_8017E274(s32 param);
extern void func_8017E2BC(void);
extern void func_8017E428();
extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_80017714(void *);
extern SVECTOR_8017E6D8 D_801D09FC[4];
extern struct PW8017E6D8 D_801D0A1C;
extern struct PW8017E6D8 D_801D0A20;
extern u8 D_801D0A24, D_801D0A25, D_801D0A26, D_801D0A28, D_801D0A29, D_801D0A2A;
extern int D_801D0A2C;
extern void func_8017E428(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8017EA80(s32 param_1);
extern void func_8017ECB4(s32 param_1);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80182400(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_8017F320(s32 p);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_8017F5E8(s32 p);
extern void func_8017F6A8(s32 param_1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_80184F14(s32, s32);
extern void func_801840C0(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80184C04(s32 arg0, u16 arg1);
extern u8 D_801A63EC[];
extern u8 D_801A6604[];
extern u8 D_801BD9C0[];
extern u8 D_801BDA28[];
extern u8 D_801BDCF8[];
extern u8 D_801BDDB0[];
extern void func_8017FA18(s32 p);
extern void func_8018000C(s32 param_1);
extern void func_80182588(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_80184028(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */
extern void func_801800C4(s32 p);
extern void func_80184124(s32 a0, void *a1, void *a2, s32 a3);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8018029C(s32 p);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80184124(s32, void*, void*, s32);
extern void func_801840C0(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_80180730(s32 param_1);
extern void func_80181DDC();
extern void func_80180B4C(s32 arg0);
extern void func_80182288(s32 a0, s32 a1);
extern void func_80181D1C(s32 param_1);
extern s32 func_80184170(s32 a0, s32 a1);
extern s32 func_80181FF4(s32 p);
extern s32 func_8012CEB0(void *a0, void *a1, s32 a2);
extern s32 func_800132BC(void *a0, void *a1);
extern s32 func_801825E8(s32 a0, s32 a1);
extern void (*D_801A6884[])(void);
extern void func_801826C8(void *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_80182B74(s32 param_1);
extern void (*D_801A69DC[])(void);
extern void func_80182E2C(void *a0);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80183DA4(s32 a0, s32 a1);
extern s32  func_8012CBF4(s32 a0);
extern u8  *func_8012913C(s32 a0);
extern void func_80183040(s32 param_1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern void func_80016714(void*, s32);
extern void func_80183454(s32 param_1);
extern void func_8012B260(u8 *a0);
extern void func_801838A4(s32 p);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80183BB4(Ent_80188E10_80183BB4 *self, s32 arg1, s32 arg2, s32 arg3, u16 kind);
extern s32 aF80184170();
extern void (*D_801A6A10[])(void);
extern void func_80184258(void *a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80184294(s32 param_1);
extern void func_8012C218(void *a0);   /* TU-canonical (ov_SC06_018_jr_8017C24C L5455) */
extern void func_80017274(s32 a0, s32 a1);
extern void func_801846F8(s32 param_1);
extern void (*D_801A6A30[])(void);
extern void func_8018479C(void *a0);
extern void func_8012C1B8(void);   /* TU-canonical (ov_SC06_018_jr_8017C24C) */
extern void func_8012B0B4(unsigned int *p, int a1, int a2);  /* TU-canonical */
extern void func_801847D8(s32 param_1);
extern void (*D_801A6A3C[])(void);
extern void func_80184D70(void *a0);
extern void func_80184DAC(s32 param_1);
extern void func_8012931C(s32 a0);
extern void func_801292C8(s32 a0);
extern void func_80184E5C(s32 param_1);
extern s32 D_801D0B78;
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_80184F14(s32 a0, s32 a1);
extern s32 func_80184F44(s32 param_1);
extern s32 func_80185188(s32 param_1);
extern void (*D_801BE87C[])(void);
extern void func_80185428(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018564C(void *arg0);
extern void func_80185DAC(s32 target, u16 *cur, s32 step);
extern s32 func_8012B8A4(s16 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_80186160(s32 param_1);
extern void (*D_801BEF64[])(void);
extern void func_80186834(void *a0);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_80186B70(void *a0);
extern void func_80186E18(s32 param_1);
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_80187180(s32 out, s32 from, s32 to);
extern void func_80187A5C(void);
extern void func_80187E60(void *a0);
extern void func_80187EDC(void *a0);
extern void func_8012931C(s32);
extern void func_801292C8(s32);
extern void func_80187D60(void *a0);
extern int func_8018853C(short *pos, int a1, int a2);
extern void func_8018837C(unsigned short *param_1, short *param_2, short *param_3, unsigned int param_4, int param_5);
extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);
extern int func_801885E4(int param_1, short param_2);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();
extern void func_801887F4(s32 a0);
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
extern void func_80188D6C(int param_1);
extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern void func_80188F1C(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern void func_8012A828(s32 a0, void * a1);
extern void func_801891A8(s32 a0);
extern void func_8012B370(int a0);
extern void func_8018966C(s32 a0);
extern s32 func_801823F0(void);
extern void func_8018983C(s32 a0);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern int func_80143C74(short *, int);
extern void func_80189A2C(s32 a0);
extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);
extern void func_80189D44(int param_1);
extern void func_80189F3C(s32 a0);
extern void func_8018A384(short *param_1);
extern void func_8018A594(s32 a0);
extern s32 func_80143C74();
extern void func_8018A9D8(s32 a0);
extern void func_80128EA8();
extern void func_8012931C();
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8();
extern int  func_8012D664();
extern void func_8018ABE8(s32 arg0);
extern void func_8018B02C(s32 a0);
extern void func_8018B184(void *a0);
extern void func_8018B294(void);
extern void func_8018B370(s32 a0);
extern void func_8018B430(void);
extern void func_8018B450(void *a0);
extern void func_8018B564(void);
extern void func_8018B660(s32 a0);
extern void func_8018B720(void);
extern void aF8017ED80(void *param_1) __asm__("func_8018B878");
extern void aF8017ED80(void *param_1);
extern void func_8018B878(void);
extern void func_8018BBF8(s32 a0);
extern s32 func_8018B740(s32 a0, s32 a1);
extern void func_8018BDE0(s32 a0);
extern void func_8018C11C(s32 param_1);
extern void (*D_801CA8E8[])(void);
extern void func_8018C5CC(void *a0);
extern void (*D_801CA908[])(void);
extern void func_8018C77C(void *a0);
extern void func_8018C840(void *a0);
extern void func_8018BA4C(void);
extern void func_8018C878(s32 *param);
extern void func_8018C8A0(s32 arg0);
extern void func_8018CA0C(s32 *a0);
extern void func_8018CA40(s32 a0);
extern void func_8016AA50(s32, s32);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012B23C(void *);
extern void func_8012B1B4(void *, void *);
extern void func_8012A828(s32, void *);
extern void func_8012C218(void *);
extern void func_8018D5C0(void *arg);
extern void func_8012A828(s32, void*);
extern void func_8018DED8(void *arg);
extern void func_80017254(void *a0);
extern SVEC_8018EDB0 D_801CC7FC[];
extern u8 D_800A651C[];
extern u8 D_800AE610[];
extern u8 D_800AF630[];
extern void func_8018EDB0(s32 param_1, u32 param_2, u16 *param_3, u32 param_4);
extern void func_8018F3E4(void);
/* ==== end §8b carried decl layer ==== */

/* func_801902EC — Tier 2 (codegen shaping). MATCH (673 ins, match_one, reloc-masked).
 * ov_SC06_032, jr/switch carve region ov_SC06_032_jr_8017C24C (cookbook §53).
 * State-machine dispatcher on param_1->0x34 (u16, cases 0-9 via a compiler jump table).
 *
 * param_1 kept as `s32` (byte-address arithmetic via casts), matching the established
 * convention for this fleet of "entity think" functions (see src/shared/engine_core.h,
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c's DEFINE_func_80151C54 etc.) rather than
 * Ghidra's `short *` guess: two fields Ghidra split into a pair of `param_1[x]/[x+1]`
 * short assignments (offsets 0x58 and 0x1C) are each really a SINGLE 32-bit `sw`.
 *
 * ---- Tier-2 residual chain (each step byte-scored with tools/match_one.py) ----
 * Start: tier-1 draft 676 ins vs 673, diagnosed "RC-6 pressure-lock". It was NOT RC-6.
 * The 4th $s-reg was a plain aliasing mistake plus two §2 address caches. Levers, in the
 * order they were found and what each bought (mismatch count):
 *
 *  1. 4-saved-regs -> 3 (676->674).  The 3rd "from"-pointer group in cases 6/7/trailer was
 *     written through the SAME local as the short-lived "to" pointer, so that local crossed
 *     a call function-wide and got a callee-saved reg. Target keeps all three from-pointers
 *     in one reg ($s0) and every to-pointer in $v1. Fix: use the from-var at all 3 sites.
 *  2. Case order (674->672, 351->... ). gcc-2.7.2 emits switch arms in SOURCE order: the
 *     target's block layout proves the original order is 0, 9, 1, 2, 3, 4, 5, 6, 7, 8.
 *  3. cse_expr.md §2 hoist-vs-remat, x3 regions (672->674 ins, -53 mism). gcc cse'd the
 *     `D_801CC7CC` SYMBOL_REF across the 3 func_8012F14C call sites in each region into one
 *     pseudo (`la $16,..` + `move $5,$16` per site); the target rematerializes `la $5,..` at
 *     every site. Lever = nested-block pointer local + post-call OUTPUT-ONLY volatile asm
 *     kill after sites 1..n-1; last site takes the bare address.
 *     *** BOUNDARY CONDITION 3 IS LOAD-BEARING: `q`'s init must NOT cross a call. ***
 *     Initialising `q` before func_8012B2CC made it a call-crossing local qty, local-alloc
 *     parked it in $s0 (invisibly - it is a REG_EQUIV constant, so no insn is emitted) and
 *     the from-pointer allocno then CONFLICTED with hard reg 16 and could never reach $s0.
 *     Found only by reading cc1's `-dg` dump (`;; 73 conflicts: ... 16`). Moving `q = ...`
 *     to after the call freed $s0 (55 -> the $s0/$s2 swap became reachable).
 *  4. Same §2 lever on `buf18` (sp+0x18, passed to both RotTransSV and func_8018FB5C):
 *     674->673 ins, 222->91. `buf10` needs no lever - it is at offset 0x10, the first local,
 *     so `&buf10` IS virtual-stack-vars and remats for free (§2 exception).
 *  5. Local splitting = the register map. Ghidra's merged iVar2/iVar6 had to be re-split by
 *     LIVE REGION, then selectively re-merged to match the target's allocation:
 *       - one shared `eNew` for the case-9/1/2/3 call results AND case-0's loop result AND
 *         case-5's pointer temps (all $a0 in the target - a multi-block allocno, which is
 *         also why it never coalesces into the $v0 return reg: that copy `addu $a0,$v0,$zero`
 *         is in the target and cannot be reproduced by a block-local temp);
 *       - `to1..to6` per group ($v1, never call-crossing);
 *       - `cnt` (case-0 loop counter) split from `fromX` (the from-pointers);
 *       - `tmp32`/`tmp7` split per region ($v0, not the global-allocno $a0).
 *  6. §31 DENSITY lever, exactly ONE dead-read (55->16). With $s0 free, param_1 still won it
 *     on allocno_compare priority. One `__asm__ __volatile__("" :: "r"(fromX))` per region
 *     lifts fromX above param_1 -> fromX=$s0, param_1=$s1, cnt=$s0 (disjoint), 0x18=$s2.
 *     N=1/2/3 all score the same; keep the minimum.
 *     (A `register __asm__("$16")` pin instead scored 147 - the cookbook's "density > pins
 *      on giants" warning reproduced exactly.)
 *  7. Statement order (16->8->0):
 *       - case 7 "done" arm: the 0xE0 store must precede the 0x1C store in SOURCE; the
 *         scheduler then hoists the D_80126B66 load into the D_80126B62 load-delay gap and
 *         re-sinks the 0xF materialisation (8 insns).
 *       - cases 1/2 tail: the target emits loads [0x34, 0x1C] but stores [0x1C, 0x34] - a
 *         nesting no permutation of the three statements reaches (all 6 tried: 8/12/8/8/12/12).
 *         The fix is a fresh single-set local carrying the INCREMENTED 0x34 value
 *         (`h34 = *(u16*)(p+0x34) + 1; ... *(u16*)(p+0x34) = h34;`): sched.md §S2 birthing
 *         boost sinks the store while the load keeps its early LUID. -> MATCH.
 *
 * Other transcription facts worth keeping: `(s16)(tmp >> 16)` must be a SIGNED shift (`sra`,
 * not `srl`); `rand() % 160` must be inlined at its use (a named temp adds a `move`); the
 * entity-walk `for` increments are `ent += 0x10C, i++` (giv before counter).
 *
 * Cases 4, 5 and 8's "not done yet" arm all fall into the SAME shared trailer block after
 * the switch (asm .L80190C04) - real code sharing, written once as the post-switch tail.
 * Entity-table walk (D_801202A0, 0x60 entries / 0x10C stride) appears 3x verbatim (cases
 * 6, 7, 8) - kept literal/inline at each site; a helper would change the call graph.
 */

extern void func_8012BE54(s32);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B2CC(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8018D15C(s32 a0);
extern void func_8018D264(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_8018FB5C(void *a0, void *a1, s32 a2);
extern s32  rand(void);

extern s32 D_801CC670;
extern u8  D_801CC788[];
extern u8  D_801CCC94[];
extern u8  D_801CC7CC[];
extern u8  D_801CC7F4[];
extern u8  D_801202A0[];
extern u8  D_80126B5C;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_800B99D8;

void func_801902EC(s32 param_1)
{
    s32 fromX;
    s32 cnt;
    s32 c4, c6, c7, c8, d6, d7, eNew, r0, to1, to2, to3, to4, to5, to6;
    s16 sVar1;
    s16 buf10[4];    /* sp+0x10 -- the SVECTOR-ish scratch reused everywhere */
    s16 buf18[4];    /* sp+0x18 -- case 7's RotTransSV out / func_8018FB5C in */
    s16 buf20[4];    /* sp+0x20 -- case 7's constant vector -> func_8018FB5C */
    s16 buf28[4];    /* sp+0x28 -- case 7's RotTransSV 2nd out, unread after */
    s32 tmp32;
    u16 h34;
    s32 tmp7;
    u8 *ent;
    s32 i;
    s32 flag;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        r0 = ((s32 (*)(s32))func_8012BE54)(param_1);
        if (0x3ffff < r0) {
            return;
        }
        *(u16 *)(param_1 + 0x34) = 9;
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801CCC94);
        *(s32 *)(param_1 + 0x58) = (s32)((u32)&D_801CC670 | 0x40000000 | 0x20000000);
        func_8012A828(param_1, D_801CC788);
        *(u8 *)(param_1 + 0x75) = 8;
        *(u16 *)(param_1 + 0xAE) = 0;
        for (cnt = 0x200; cnt < 0x1000; cnt += 0x400) {
            eNew = func_8012C658(0x318, 1, param_1);
            if (eNew != 0) {
                *(u16 *)(*(s32 *)(eNew + 0x20) + 0x12) = (u16)cnt;
                *(s32 *)(eNew + 0x1C) = 0x18;
                *(u16 *)(eNew + 0xFC) = *(u16 *)(param_1 + 0x36);
            }
        }
        *(s32 *)(param_1 + 0x1C) = 0x32;
        return;

    case 9:
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        eNew = func_8012C658(0x318, 9, param_1);
        if (eNew == 0) {
            return;
        }
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) + 1;
        *(s32 *)(param_1 + 0xD8) = eNew;
        *(u16 *)(param_1 + 0x34) = 1;
        /* fallthrough */
    case 1:
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        eNew = func_8012C658(0x318, 2, param_1);
        if (eNew == 0) {
            return;
        }
        *(s16 *)(eNew + 0xA) = *(s16 *)(eNew + 0xA) - 0x60;
        *(u16 *)(*(s32 *)(eNew + 0x20) + 0x10) = 0xC00;
        h34 = *(u16 *)(param_1 + 0x34) + 1;
        *(s32 *)(param_1 + 0xCC) = eNew;
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) + 1;
        *(u16 *)(param_1 + 0x34) = h34;
        /* fallthrough */
    case 2:
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        eNew = func_8012C658(0x318, 2, param_1);
        if (eNew == 0) {
            return;
        }
        *(u16 *)(eNew + 0xFC) = 0x600;
        h34 = *(u16 *)(param_1 + 0x34) + 1;
        *(s32 *)(param_1 + 0xD0) = eNew;
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) + 1;
        *(u16 *)(param_1 + 0x34) = h34;
        /* fallthrough */
    case 3:
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        eNew = func_8012C658(0x318, 2, param_1);
        if (eNew == 0) {
            return;
        }
        *(u16 *)(eNew + 0xFC) = 0x600;
        *(s32 *)(param_1 + 0xD4) = eNew;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        return;

    case 4:
        c4 = *(s32 *)(param_1 + 0x1C) - 1;
        *(s32 *)(param_1 + 0x1C) = c4;
        if (c4 < 1) {
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;

    case 5:
        eNew = *(s32 *)(param_1 + 0xCC);
        *(u16 *)(*(s32 *)(eNew + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(eNew + 0x20) + 0x10) + 0x40;
        eNew = *(s32 *)(param_1 + 0xD0);
        *(s16 *)(eNew + 0xFC) = *(s16 *)(eNew + 0xFC) - 0x60;
        eNew = *(s32 *)(param_1 + 0xD4);
        sVar1 = *(s16 *)(eNew + 0xFC) - 0x60;
        *(s16 *)(eNew + 0xFC) = sVar1;
        if (sVar1 == 0) {
            *(s32 *)(param_1 + 0x1C) = 0x96;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            eNew = *(s32 *)(param_1 + 0xCC);
            *(u16 *)(*(s32 *)(eNew + 0x20) + 0x10) = 0;
        }
        break;

    case 6:
        func_8018D15C(*(s32 *)(param_1 + 0xCC));

        {
            u8 *q;
            fromX = *(s32 *)(param_1 + 0xCC);
            func_8012B2CC(fromX);
            q = D_801CC7CC;
            ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
            __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
        }
        to1 = *(s32 *)(param_1 + 0xD0);
        *(s16 *)(to1 + 6) = buf10[0];
        *(s16 *)(to1 + 0xA) = buf10[1];
        *(s16 *)(to1 + 0xE) = buf10[2];
        *(s16 *)(*(s32 *)(to1 + 0x20) + 0x10) =
            *(s16 *)(to1 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
        *(s16 *)(*(s32 *)(to1 + 0x20) + 0x12) =
            *(s16 *)(to1 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);
        func_8018D264(*(s32 *)(param_1 + 0xD0));

        {
            u8 *q;
            fromX = *(s32 *)(param_1 + 0xD0);
            func_8012B2CC(fromX);
            q = D_801CC7CC;
            ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
            __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
        }
        to2 = *(s32 *)(param_1 + 0xD4);
        *(s16 *)(to2 + 6) = buf10[0];
        *(s16 *)(to2 + 0xA) = buf10[1];
        *(s16 *)(to2 + 0xE) = buf10[2];
        *(s16 *)(*(s32 *)(to2 + 0x20) + 0x10) =
            *(s16 *)(to2 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
        *(s16 *)(*(s32 *)(to2 + 0x20) + 0x12) =
            *(s16 *)(to2 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);
        func_8018D264(*(s32 *)(param_1 + 0xD4));

        fromX = *(s32 *)(param_1 + 0xD4);
        func_8012B2CC(fromX);
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)D_801CC7CC, (s32)buf10);
        *(s16 *)(param_1 + 6) = buf10[0];
        *(s16 *)(param_1 + 0xA) = buf10[1];
        *(s16 *)(param_1 + 0xE) = buf10[2];

        func_8012B77C((s32)buf10, param_1 + 4, (s32)&D_80126B5C);
        tmp32 = *(s32 *)buf10;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)tmp32;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(tmp32 >> 16);

        if ((*(s32 *)(param_1 + 0x1C) & 0xF) == 0) {
            *(s16 *)(param_1 + 0xFC) = rand() % 160 + 0x100;
        }

        c6 = *(s32 *)(param_1 + 0x1C) - 1;
        *(s32 *)(param_1 + 0x1C) = c6;
        if (c6 != 0) {
            return;
        }

        *(s32 *)(param_1 + 0x1C) = 0x10;
        d6 = ((s32 (*)(s32))func_8012BE54)(param_1);
        if (0x8ffff < d6) {
            return;
        }
        ent = D_801202A0;
        for (i = 0; i < 0x60; ent += 0x10C, i++) {
            if (*(u16 *)(ent + 0) == 0x318 && ent != (u8 *)param_1 &&
                (*(s16 *)(ent + 0x70) == 0 || *(s16 *)(ent + 0x70) == 6) &&
                *(u16 *)(ent + 0x34) == 6 && *(s32 *)(ent + 0x1C) < 0x11) {
                *(s32 *)(ent + 0x1C) = *(s32 *)(ent + 0x1C) + 0x10;
            }
        }
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        func_8002D4C8(0x9BB, 0);
        return;

    case 7:
        d7 = ((s32 (*)(s32))func_8012BE54)(param_1);
        if (d7 < 0x90000) {
            ent = D_801202A0;
            for (i = 0; i < 0x60; ent += 0x10C, i++) {
                if (*(u16 *)(ent + 0) == 0x318 && ent != (u8 *)param_1 &&
                    (*(s16 *)(ent + 0x70) == 0 || *(s16 *)(ent + 0x70) == 6) &&
                    *(u16 *)(ent + 0x34) == 6 && *(s32 *)(ent + 0x1C) < 0x11) {
                    *(s32 *)(ent + 0x1C) = *(s32 *)(ent + 0x1C) + 0x10;
                }
            }

            {
                u8 *q;
                fromX = *(s32 *)(param_1 + 0xCC);
                func_8012B2CC(fromX);
                q = D_801CC7CC;
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
                __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
            }
            to3 = *(s32 *)(param_1 + 0xD0);
            *(s16 *)(to3 + 6) = buf10[0];
            *(s16 *)(to3 + 0xA) = buf10[1];
            *(s16 *)(to3 + 0xE) = buf10[2];
            *(s16 *)(*(s32 *)(to3 + 0x20) + 0x10) =
                *(s16 *)(to3 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
            *(s16 *)(*(s32 *)(to3 + 0x20) + 0x12) =
                *(s16 *)(to3 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);

            {
                u8 *q;
                fromX = *(s32 *)(param_1 + 0xD0);
                func_8012B2CC(fromX);
                q = D_801CC7CC;
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
                __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
            }
            to4 = *(s32 *)(param_1 + 0xD4);
            *(s16 *)(to4 + 6) = buf10[0];
            *(s16 *)(to4 + 0xA) = buf10[1];
            *(s16 *)(to4 + 0xE) = buf10[2];
            *(s16 *)(*(s32 *)(to4 + 0x20) + 0x10) =
                *(s16 *)(to4 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
            *(s16 *)(*(s32 *)(to4 + 0x20) + 0x12) =
                *(s16 *)(to4 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);

            fromX = *(s32 *)(param_1 + 0xD4);
            func_8012B2CC(fromX);
            ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)D_801CC7CC, (s32)buf10);
            *(s16 *)(param_1 + 6) = buf10[0];
            *(s16 *)(param_1 + 0xA) = buf10[1];
            *(s16 *)(param_1 + 0xE) = buf10[2];

            func_8012B77C((s32)buf10, param_1 + 4, (s32)&D_80126B5C);
            tmp7 = *(s32 *)buf10;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)tmp7;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(tmp7 >> 16);

            c7 = *(s32 *)(param_1 + 0x1C) - 1;
            *(s32 *)(param_1 + 0x1C) = c7;
            if (c7 == 0) {
                *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
                *(u16 *)(param_1 + 0xDC) = D_80126B5E;
                *(s16 *)(param_1 + 0xDE) = D_80126B62 - 0x38;
                *(u16 *)(param_1 + 0xE0) = D_80126B66;
                *(s32 *)(param_1 + 0x1C) = 0xF;
                func_8012C658(0x318, 3, param_1);
                func_8002D4C8(0x9BC, 0);
                return;
            }

            buf20[0] = D_80126B5E;
            buf20[1] = D_80126B62 - 0x38;
            buf20[2] = D_80126B66;
            func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
            func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
            {
                s16 *bp = buf18;
                RotTransSV(D_801CC7F4, bp, buf28);
                __asm__ __volatile__("" : "=r"(bp));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
            }
            flag = 0x202080;
            if (D_800B99D8 & 1) {
                flag = 0xE0;
            }
            func_8018FB5C(buf18, buf20, flag);
            return;
        }
        goto set_state6_timeout;

    case 8:
        c8 = *(s32 *)(param_1 + 0x1C) - 1;
        *(s32 *)(param_1 + 0x1C) = c8;
        if (c8 == 0) {
            goto set_state6_timeout;
        }
        ent = D_801202A0;
        for (i = 0; i < 0x60; ent += 0x10C, i++) {
            if (*(u16 *)(ent + 0) == 0x318 && ent != (u8 *)param_1 &&
                (*(s16 *)(ent + 0x70) == 0 || *(s16 *)(ent + 0x70) == 6) &&
                *(u16 *)(ent + 0x34) == 6 && *(s32 *)(ent + 0x1C) < 0x11) {
                *(s32 *)(ent + 0x1C) = *(s32 *)(ent + 0x1C) + 0x10;
            }
        }
        break;

    default:
        return;
    }

    /* shared trailer (asm .L80190C04) -- reached by `break` fromX cases 4, 5, 8 */
    {
        u8 *q;
        fromX = *(s32 *)(param_1 + 0xCC);
        func_8012B2CC(fromX);
        q = D_801CC7CC;
        __asm__ __volatile__("" :: "r"(fromX));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
        __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
    }
    to5 = *(s32 *)(param_1 + 0xD0);
    *(s16 *)(to5 + 6) = buf10[0];
    *(s16 *)(to5 + 0xA) = buf10[1];
    *(s16 *)(to5 + 0xE) = buf10[2];
    *(s16 *)(*(s32 *)(to5 + 0x20) + 0x10) =
        *(s16 *)(to5 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
    *(s16 *)(*(s32 *)(to5 + 0x20) + 0x12) =
        *(s16 *)(to5 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);

    {
        u8 *q;
        fromX = *(s32 *)(param_1 + 0xD0);
        func_8012B2CC(fromX);
        q = D_801CC7CC;
        __asm__ __volatile__("" :: "r"(fromX));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)q, (s32)buf10);
        __asm__ __volatile__("" : "=r"(q));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B tus10)
    }
    to6 = *(s32 *)(param_1 + 0xD4);
    *(s16 *)(to6 + 6) = buf10[0];
    *(s16 *)(to6 + 0xA) = buf10[1];
    *(s16 *)(to6 + 0xE) = buf10[2];
    *(s16 *)(*(s32 *)(to6 + 0x20) + 0x10) =
        *(s16 *)(to6 + 0xFC) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x10);
    *(s16 *)(*(s32 *)(to6 + 0x20) + 0x12) =
        *(s16 *)(to6 + 0xFE) + *(s16 *)(*(s32 *)(fromX + 0x20) + 0x12);

    fromX = *(s32 *)(param_1 + 0xD4);
    func_8012B2CC(fromX);
    ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(fromX + 0x20) + 0x34, (s32)D_801CC7CC, (s32)buf10);
    *(s16 *)(param_1 + 6) = buf10[0];
    *(s16 *)(param_1 + 0xA) = buf10[1];
    *(s16 *)(param_1 + 0xE) = buf10[2];
    return;

set_state6_timeout:
    *(u16 *)(param_1 + 0x34) = 6;
    *(s32 *)(param_1 + 0x1C) = 0x96;
    return;
}


#include "common.h"

/* func_80190D70 - ov_SC06_032 / ov_SC06_032_jr_801902EC (192 ins). MATCH, closeness 0.
 *
 * Body verified byte-exact standalone AND against the REAL 3407-line TU prefix
 * (every file-scope decl + engine_core.h) -- see the decl notes below.
 *
 * Structure straight from the .s: a "did my owner change?" reinit guard, then a
 * 3-case state machine on *(u16 *)(a0 + 0x34) (an if/else chain, not a jump table
 * -- the .s dispatches with beq 1 / slti 2 / beqz / beq 2).
 *   guard : owner-stamp mismatch -> reset state, re-arm, randomise 0xFC/0xFE/0x100
 *   case 0: countdown, then snapshot the owner's world XYZ, RotTransPers it, and if
 *           the projected point is on-screen fire a positional SFX whose low byte is
 *           the distance-attenuated volume ((0xA0 - |sx|) * 0x7F / 0xA0) and whose
 *           pan nibble is (sx + 0xA0) / 0x14 clamped 0x10 -> 0xF, << 8, | 0x3000.
 *   case 1: countdown, walking the entity back along its heading (rcos/rsin * 32).
 *   case 2: spin the owner's 0x10 angle by 0x20 until it hits 0x380.
 * Cases 1 and 2 share the ".L80191058: sh $v0, 0x34($s0)" tail via a cross-jump; both
 * are written as the same `*(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;` statement,
 * and gcc's cross-jumper re-merges them (case 1's arm reuses the $a0 copy of the
 * switch value that the dispatch already loaded).
 */

/* ---- DECLARATION LAYER: block scope, but NOT free-form (this is what sank the
 * previous attempt on this function -- it was byte-perfect in isolation and a hard
 * cc1 error inside the TU, which reads as an unexplained gate rejection).
 *
 * §55a says a block-scope extern conflicts with nothing at file scope. That is FALSE
 * in this direction for gcc-2.7.2: an inner redeclaration is merged with the outer one
 * into the C89 COMPOSITE type, so
 *   - `extern void func_8012B1B4(s32, s32);` against this TU's file-scope
 *     `extern void func_8012B1B4(void *, void *);` (L2939)  ->  ERROR "conflicting types"
 *   - `extern void func_8012B23C();` does NOT hide the file-scope prototype
 *     `extern void func_8012B23C(void *);` (L2938); the composite keeps the parameter
 *     list, so the zero-arg call  ->  ERROR "too few arguments to function"
 * Both were reproduced by compiling the real TU prefix + this body.
 *
 * So: spell every redeclaration EXACTLY as the TU already spells it (law 2), and where
 * the TU's arity is wrong for this call site, do not fight the prototype -- go through
 * a cast function pointer, this TU's own house idiom (L3060,
 * `((s32 (*)(s32))func_8012BE54)(param_1)`), which still emits a direct `jal`.
 *
 * The .s proves func_8012B23C takes ZERO arguments here: $a0 is never set up before the
 * jal, and its delay slot holds `sh $zero, 0x34($s0)` -- an invented argument would cost
 * an `addu $a0, $s0, $zero` and move the store out of the slot (SYS law 4).
 *
 * D_800AF648 is the scalar `extern u8` spelling engine_core.h uses everywhere; the two
 * $a0-pinned scopes below are its §2 remat lever (hoisting the lui/addiu out would emit
 * one `la` + two `move $4,$sN` instead of the target's two `la $4,...`).
 */

void func_80190D70(s32 a0) {
    extern void func_8012B23C(void *);
    extern void func_8012B1B4(void *a0, void *a1);
    extern s32 rand(void);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern s32 func_8004787C(s32 a0);
    extern s32 func_80047948(s32 a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern u8 D_800AF648;
    extern u8 D_801CC7D4[];

    struct {
        s16 v[3];   /* sp+0x10 */
        s16 pad;    /* sp+0x16 */
        u16 sxy[2]; /* sp+0x18 */
        s32 z;      /* sp+0x1C */
        s32 flag;   /* sp+0x20 */
    } L;

    if (*(s16 *)(a0 + 0xFC) != *(s16 *)(*(s32 *)(a0 + 0x64) + 0x36)) {
        *(s16 *)(a0 + 2) = 5;
        *(s16 *)(a0 + 0x34) = 0;
        ((void (*)(void))func_8012B23C)();
        func_8012B1B4((void *)a0, D_801CC7D4);
        *(s16 *)(a0 + 0x16) = (rand() & 3) - 0x1B;
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x38;
        *(s16 *)(a0 + 0xFC) = (rand() & 0xFF) - 0x80;
        *(s16 *)(a0 + 0xFE) = (rand() & 0xFF) - 0x80;
        *(s16 *)(a0 + 0x100) = (rand() & 0xFF) - 0x80;
        *(s32 *)(a0 + 0x1C) = 0x3C;
        return;
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s32 *)(a0 + 0x1C) != 0) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
            *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 4;
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x14;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes: rematerialise &D_800AF648 (lui/addiu) before EACH call */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 sx;                        /* screen X, then REUSED as the pan field */
            register s32 av __asm__("$5"); /* |X| */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus10)
            s32 vol;
            sx = (s16)L.sxy[0];
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8; /* in place, so reorg can steal it into the bne delay slot */
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
        }
        return;

    case 1:
        if (*(s32 *)(a0 + 0x1C) != 0) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
            *(s32 *)(a0 + 4) =
                *(s32 *)(a0 + 4) - (func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 5);
            *(s32 *)(a0 + 0xC) =
                *(s32 *)(a0 + 0xC) - (func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 5);
            return;
        }
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;

    case 2:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + 0x20;
        if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) != 0x380) {
            return;
        }
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80191070;

/* func_80191070 - ov_SC06_018 / ov_SC06_018_jr_8019059C   (470 ins, MATCH)
 *
 * 5-state jr-dispatch tick for the 0x318 boss-effect entity that func_8019059C
 * drives (jtbl_801D3B74, `lhu 0x34 ; sltiu ...,5` => minval 0 / maxval 4, and
 * BOTH jtbl edges are real bodies, so neither empty-case construction of
 * cookbook 161a/162a1 applies here).
 *
 *   pre-switch: if (+0x100 != owner(+0x64)->+0x36) tear the child down and
 *               fall into the shared func_8012C218 exit.
 *   case 0: seed a free slot of the 32-entry x 0x10 particle table D_801D0DC0,
 *           tick the +0xE2 countdown, then spawn the child (+0xCC).
 *   case 1: raise the child, poll func_8012BEE8, advance state + SFX 0x9B9.
 *   case 2: two func_8018EDB0 draws, a func_80133784 hit test, spawn 0x23.
 *   case 3/4: same draws + optional func_80143C74 spray with two rand() kicks.
 *   post: func_8018F3E4, then a 4-byte align-1 copy into D_801D0FC0.
 *
 * LEVERS (all byte-measured on the way to MATCH):
 *
 * (1) 160a x3 - every lwl/lwr+swl/swr pair is an ALIGN-1 STRUCT ASSIGNMENT
 *     (Blk4_80191320_80191070 / Blk8_80191320_80191070). emit_block_move takes the TYPE's
 *     alignment, so a u8[4]/u8[8] struct forces the unaligned form on BOTH
 *     sides even when one side is a 4-aligned stack slot.
 *
 * (2) THE LOOP IS ONE POINTER, NOT TWO. The target walks D_801D0DC0 with two
 *     registers 6 apart ($a3 = p, $a2 = p+6) and it is tempting to write two
 *     pointers `p` and `q = p + 6`, both `+= 0x10`. That gives TWO bivs and
 *     4 induction registers (+4 ins). The truth is ONE biv + ONE combine_givs
 *     group: the MIPS unaligned-move patterns print `swl base+3 / swr base+0`
 *     off a SINGLE MEM, so the two block moves contribute the addresses p+0
 *     and p+8 only -- p+0 is the bare biv (never a giv, loop.c:4200 needs
 *     add_val != 0) and stays on $a3 together with `p[0]`, while p+1/p+2/p+4/
 *     p+5/p+6/p+8/p+0xC/p+0xE all combine at the LAST address giv in source
 *     order, `p[6]`, giving $a2 = p+6 with offsets -5..+8. Write every access
 *     as p[k] off one pointer and the register file falls out.
 *
 * (3) 162b1 per-arm decision for the merged `+0x34 += 1` tail. cases 0/2/3 end
 *     with `t = *(u16*)(a+0x34); ...; *(u16*)(a+0x34) = t + 1;` written
 *     LONGHAND; cross_jump merges them into the LAST-emitted copy (case 3's),
 *     which is exactly where the target's .L801918A8 sits (162g). It only
 *     merges if all three copies use the SAME hard register, and that needs
 *     THREE SEPARATE locals (t34a/t34b/t34c): one shared function-scope temp
 *     is a multi-block pseudo, so global_alloc gets it AFTER local_alloc has
 *     handed $v0 to the `8`/`0x1E` constant, and the tail comes out on $v1.
 *
 * (4) case 1's `addu $v1,$v0,$zero` is the MEMORY RE-READ form. Writing
 *     `s32 t = *(s16*)(e+0x18); if (t < 0x500) ... t + 0xC0` is one insn
 *     SHORT: cse keeps the value in one pseudo and no copy is needed. Reading
 *     *(s16*)(e+0x18) twice makes cse fold the second load onto a value that
 *     must survive the `slti` clobbering $v0, so the copy appears. It also
 *     costs 8 bytes of frame (see the pad note).
 *
 * (5) 162f-adjacent SCHEDULING: three loads in the target are hoisted above a
 *     store and gcc will not do it from the natural spelling -- name them.
 *     `tmp = *(u16*)(a+0xE)` before the `| 0x50000000`, `tmp2 = *(u16*)(a+0xE0)`
 *     before the 0x3001 store, and `t34d = *(u16*)(a+0x34) + 1` before the
 *     0xE6 store. Each is worth 1 gas nop / a register swap.
 *
 * (6) THE ALIAS PAIR (new, and the last 3 bytes). sched.c:869 output_dependence
 *     drops a store-store dependence only when one MEM is (MEM_IN_STRUCT_P &&
 *     varying address && mode != QImode) and the other is (!MEM_IN_STRUCT_P &&
 *     fixed address). The preheader has exactly that pair -- the owner counter
 *     `+0x64 -> +0x1C` and the colour word at 0x34($sp) -- and it decides
 *     whether `sw $a0,0x34($sp)` is priority 1 (scheduled before
 *     `addiu $v0,$v0,1`, the target) or priority 3 (scheduled last, wrong).
 *     BOTH halves are load-bearing: the counter must be an ARRAY_REF
 *     (`((s32*)owner)[7]`, MEM_IN_STRUCT_P=1) and the colour store must be an
 *     INDIRECT_REF (`*(u32*)((u8*)col + 4)`, MEM_IN_STRUCT_P=0). Spelling the
 *     counter `*(s32*)(owner + 0x1C)` or the colour `col[1]` each leaves 3
 *     mismatched; only the pair reaches 0. No permutation of the 5 preheader
 *     statements (all 120 measured) can substitute for it.
 *
 * (7) FRAME (162i): vars = 0x38. sp10/sp18/sp20/sp28 are 8-byte SVECTORs at
 *     0x10/0x18/0x20/0x28; `col[2]` is BLKmode so it is 8-ALIGNED at 0x30 and
 *     the colour word lands at 0x34 (a plain scalar would be pushed past every
 *     BLKmode decl instead). `pad1[2]` + the 8-byte temp that lever (4)'s
 *     re-read form allocates make up the rest. Neither pad is referenced.
 *
 * INTEGRATION (52b / 161c): every callee decl below is byte-identical to the
 * host TU src/ov_SC06_018/ov_SC06_018_jr_8019059C.c where that TU declares one
 * (func_80016714 L431, func_8001CD9C L1820, func_8002D4C8 L59, func_8012F214
 * L2653, func_80133784 L600, func_8012F038 L333, func_8012C218 L2721,
 * func_8018F3E4 L2751, rand L958) -- the arguments are cast at the call sites
 * instead. func_8012C194 / func_8012BEE8 / func_8018EDB0 / func_8012D5E4 /
 * func_80132EF4 / func_80143C74 and every D_ symbol are undeclared in that TU.
 *
 * FAMILY (reach x3, all 470 ins / 0x758, identical shape) - mechanical remap:
 *   ov_SC06_018 func_80191070 | ov_SC06_032 func_80191070 | ov_SC06_033 func_8018D05C
 *   D_801D0DC0 (32x0x10 tbl)  | D_801D0DC0                | D_801D0C40
 *   D_801D0FC0 (4-byte)       | D_801D0FC0                | D_801D0E40
 *   D_801CF0F0                | D_801CF0F0                | D_801CF1AC
 *   D_801CF0E8                | D_801CF0E8                | D_801CF1A4
 *   jtbl_801D3B74             | jtbl_801CF148             | jtbl_801CF204
 *   func_8018EDB0 (draw)      | func_8018EDB0             | func_8018AD9C
 *   func_8018F3E4 (post)      | func_8018F3E4             | func_8018B3D0
 * Everything else (D_80126B96 + the 8012xxxx/8001xxxx engine callees, rand) is
 * shared verbatim across all three.
 *
 * CARVE NOTE for banking: jtbl_801D3B74 currently lives in the tail20 DATA
 * segment (config/splat.ov_SC06_018.yaml, [0xaba1c, data, tail20]). Banking
 * this body makes cc1 emit its own 5-word .rodata table, so the
 * ov_SC06_018_jr_8019059C .rodata carve must grow 0xab9f4->0xaba1c into
 * 0xab9f4->0xaba30 (5 words, from the `sltiu ...,5` bound per 162a - NOT the
 * 6-word dlabel span; the trailing 0x00000000 at 0x801D3B88 is separate data).
 */


typedef struct { u8 b[4]; } Blk4_80191320_80191070;
typedef struct { u8 b[8]; } Blk8_80191320_80191070;
typedef struct { s16 vx, vy, vz, pad; } SV_80191320_80191070;



s32 func_80191070(s32 arg0) {
    extern s32 func_8012C194(void);
    extern u8 D_801D0DC0[];
    extern u8 D_801D0FC0;
    extern u8 D_801CF0E8[];
    extern u8 D_801CF0F0[];
    extern u16 D_80126B96;


    s32 h;
    s32 e;
    s32 e2;
    u16 tmp;
    u16 tmp2;
    u16 t34d;
    u16 t34a;
    u16 t34b;
    u16 t34c;
    s16 hn0;
    s16 hn4;
    s32 cnt;
    u8 *p;
    u8 *src;
    s32 i;
    s32 c;
    u16 *v;
    SV_80191320_80191070 sp10;
    SV_80191320_80191070 sp18;
    SV_80191320_80191070 sp20;
    SV_80191320_80191070 sp28;
    u32 col[2];
    s32 pad1[2];

    if (*(s16 *)(arg0 + 0x100) != *(s16 *)(*(s32 *)(arg0 + 0x64) + 0x36)) {
        h = *(s32 *)(arg0 + 0xCC);
        if (h != 0) {
            ((void(*)(void *, s32))func_80016714)((void *)h, 0x38);
        }
        goto kill;
    }

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        ((s32 *)*(s32 *)(arg0 + 0x64))[7] = ((s32 *)*(s32 *)(arg0 + 0x64))[7] + 1;
        src = (u8 *)(arg0 + 0xDC);
        *(u32 *)((u8 *)col + 4) = 0x4040FF;
        p = D_801D0DC0;
        i = 0;
        do {
            i++;
            if (*(s16 *)(p + 0xE) == 0) {
                *(Blk8_80191320_80191070 *)(p + 8) = *(Blk8_80191320_80191070 *)src;
                *(Blk4_80191320_80191070 *)p = *(Blk4_80191320_80191070 *)((u8 *)col + 4);
                c = p[0] >> 3;
                p[4] = c;
                if (c == 0) {
                    p[4] = 1;
                }
                c = p[1] >> 3;
                p[5] = c;
                if (c == 0) {
                    p[5] = 1;
                }
                c = p[2] >> 3;
                p[6] = c;
                if (c == 0) {
                    p[6] = 1;
                }
                break;
            }
            p += 0x10;
        } while (i < 0x20);
        hn0 = *(u16 *)(src + 6) - 0x100;
        *(s16 *)(src + 6) = hn0;
        if (hn0 == 0) {
            e = func_8012C194();
            if (e != 0) {
                *(s32 *)(arg0 + 0xCC) = e;
                ((void(*)(int, void *))func_8001CD9C)(e, &D_801D0FC0);
                *(u16 *)(e + 8) = *(u16 *)(arg0 + 6);
                *(u16 *)(e + 0xA) = *(u16 *)(arg0 + 0xA);
                tmp = *(u16 *)(arg0 + 0xE);
                *(s32 *)(e + 4) = *(s32 *)(e + 4) | 0x50000000;
                *(u16 *)(e + 0x18) = *(u16 *)(e + 0x1A) = 0x80;
                *(u16 *)(e + 0x2C) = 0xC006;
                *(u16 *)(e + 0xC) = tmp;
            }
            t34a = *(u16 *)(arg0 + 0x34);
            *(s32 *)(arg0 + 0x1C) = 8;
            *(u16 *)(arg0 + 0x34) = t34a + 1;
        }
        break;

    case 1:
        ((s32 *)*(s32 *)(arg0 + 0x64))[7] = ((s32 *)*(s32 *)(arg0 + 0x64))[7] + 1;
        e = *(s32 *)(arg0 + 0xCC);
        if (*(s16 *)(e + 0x18) < 0x500) {
            *(s16 *)(e + 0x18) = *(s16 *)(e + 0x18) + 0xC0;
            *(u16 *)(e + 0x1A) = *(u16 *)(e + 0x1A) + 0xC0;
        }
        if (func_8012BEE8(arg0) != 0) {
            *(u16 *)(arg0 + 0x102) = 0;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            func_8002D4C8(0x9B9, 0);
        }
        break;

    case 2:
        v = (u16 *)(arg0 + 0xE4);
        ((s32 *)*(s32 *)(arg0 + 0x64))[7] = ((s32 *)*(s32 *)(arg0 + 0x64))[7] + 1;
        func_8018EDB0(arg0, 0, v, 0x81818);
        func_8018EDB0(arg0, 1, v, 0x204040);
        sp10.vx = sp10.vy = 0;
        sp10.vz = -*(u16 *)(arg0 + 0xE4);
        sp18.vx = sp18.vy = 0;
        sp18.vz = -*(u16 *)(arg0 + 0xE6);
        if (func_8012D5E4(arg0, (s32)&sp10, (s32)&sp18, 0x96) != 0) {
            D_80126B96 = 0x4018;
        }
        sp10.vx = sp10.vy = 0;
        sp10.vz = -*(u16 *)(arg0 + 0xE6);
        *(u16 *)(arg0 + 0xE6) = *(u16 *)(arg0 + 0xE6) + 0x40;
        sp18.vx = sp18.vy = 0;
        sp18.vz = -*(u16 *)(arg0 + 0xE6);
        ((void(*)(s32, s32, s32))func_8012F214)(arg0, (s32)&sp10, (s32)&sp20);
        ((void(*)(s32, s32, s32))func_8012F214)(arg0, (s32)&sp18, (s32)&sp28);
        if (((s32(*)(s32, void *, s32))func_80133784)(0x11, &sp20, (s32)&sp28) != 0) {
            func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, (short *)&sp28, (short *)&sp20);
            t34d = *(u16 *)(arg0 + 0x34) + 1;
            *(u16 *)(arg0 + 0xE6) = -sp20.vz;
            *(u16 *)(arg0 + 0x34) = t34d;
            *(u16 *)(arg0 + 0xDC) = sp28.vx;
            *(u16 *)(arg0 + 0xDE) = sp28.vy;
            *(u16 *)(arg0 + 0xE0) = sp28.vz;
            e2 = func_80132EF4(arg0, 0x23);
            if (e2 != 0) {
                *(u16 *)(e2 + 6) = *(u16 *)(arg0 + 0xDC);
                *(u16 *)(e2 + 0xA) = *(u16 *)(arg0 + 0xDE);
                tmp2 = *(u16 *)(arg0 + 0xE0);
                *(u16 *)(e2 + 0x34) = 0x3001;
                *(u16 *)(e2 + 0xE) = tmp2;
                *(u16 *)(*(s32 *)(e2 + 0x20) + 0x2C) = 0xC008;
                *(s32 *)(*(s32 *)(e2 + 0x20) + 4) = *(s32 *)(*(s32 *)(e2 + 0x20) + 4) | 0x50000000;
            }
            *(s32 *)(arg0 + 0x1C) = 0x1E;
            *(u16 *)(arg0 + 0x102) = 1;
            break;
        }
        if (*(s16 *)(arg0 + 0xE6) < 0x800) {
            break;
        }
        t34b = *(u16 *)(arg0 + 0x34);
        *(s32 *)(arg0 + 0x1C) = 0x1E;
        *(u16 *)(arg0 + 0x34) = t34b + 1;
        break;

    case 3:
        v = (u16 *)(arg0 + 0xE4);
        ((s32 *)*(s32 *)(arg0 + 0x64))[7] = ((s32 *)*(s32 *)(arg0 + 0x64))[7] + 1;
        func_8018EDB0(arg0, 0, v, 0x81818);
        func_8018EDB0(arg0, 1, v, 0x204040);
        sp10.vx = sp10.vy = 0;
        sp10.vz = -*(u16 *)(arg0 + 0xE4);
        sp18.vx = sp18.vy = 0;
        sp18.vz = -*(u16 *)(arg0 + 0xE6);
        if (*(s16 *)(arg0 + 0x102) != 0) {
            ((void(*)(s32, s32, s32))func_8012F214)(arg0, (s32)&sp18, (s32)&sp28);
            e = ((s32(*)(s32, s32))func_80143C74)(arg0, 0);
            if (e != 0) {
                *(u16 *)(e + 6) = sp28.vx;
                *(u16 *)(e + 0xA) = sp28.vy;
                *(u16 *)(e + 0xE) = sp28.vz;
                *(s32 *)(e + 0x10) = ((rand() & 0x7F) - 0x40) << 12;
                *(s16 *)(e + 0x16) = -0x10;
                *(s32 *)(e + 0x18) = ((rand() & 0x7F) - 0x40) << 12;
            }
        }
        if (func_8012D5E4(arg0, (s32)&sp10, (s32)&sp18, 0x96) != 0) {
            D_80126B96 = 0x4018;
        }
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt == 0) {
            e = *(s32 *)(arg0 + 0xCC);
            if (e != 0) {
                ((void(*)(void *, s32))func_80016714)((void *)e, 0x38);
                t34c = *(u16 *)(arg0 + 0x34);
                *(s32 *)(arg0 + 0xCC) = 0;
                *(u16 *)(arg0 + 0x34) = t34c + 1;
            }
        }
        break;

    case 4:
        v = (u16 *)(arg0 + 0xE4);
        func_8018EDB0(arg0, 0, v, 0x81818);
        func_8018EDB0(arg0, 1, v, 0x204040);
        sp10.vx = sp10.vy = 0;
        sp10.vz = -*(u16 *)(arg0 + 0xE4);
        sp18.vx = sp18.vy = 0;
        sp18.vz = -*(u16 *)(arg0 + 0xE6);
        if (*(s16 *)(arg0 + 0x102) != 0) {
            ((void(*)(s32, s32, s32))func_8012F214)(arg0, (s32)&sp18, (s32)&sp28);
            e = ((s32(*)(s32, s32))func_80143C74)(arg0, 0);
            if (e != 0) {
                *(u16 *)(e + 6) = sp28.vx;
                *(u16 *)(e + 0xA) = sp28.vy;
                *(u16 *)(e + 0xE) = sp28.vz;
                *(s32 *)(e + 0x10) = ((rand() & 0x7F) - 0x40) << 12;
                *(s16 *)(e + 0x16) = -0x10;
                *(s32 *)(e + 0x18) = ((rand() & 0x7F) - 0x40) << 12;
            }
        }
        if (func_8012D5E4(arg0, (s32)&sp10, (s32)&sp18, 0x96) != 0) {
            D_80126B96 = 0x4018;
        }
        hn4 = v[0] + 0x40;
        v[0] = hn4;
        if (hn4 < *(s16 *)(v + 1)) {
            break;
        }
    kill:
        ((void(*)(void *))func_8012C218)((void *)arg0);
        return;
    }

    func_8018F3E4();
    if (D_801D0FC0 == 0xFF) {
        *(Blk4_80191320_80191070 *)&D_801D0FC0 = *(Blk4_80191320_80191070 *)D_801CF0F0;
    } else {
        *(Blk4_80191320_80191070 *)&D_801D0FC0 = *(Blk4_80191320_80191070 *)D_801CF0E8;
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018D3A4(void *a0);
extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_801917C8(s32 param_1)
{
    s32 eNew;
    s32 dx;
    s32 dy;

    *(u16 *)(param_1 + 0xE8) = (*(u8 *)(param_1 + 0xC2) << 4) + 0x100;
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        eNew = func_8012C658(0x318, 5, param_1);
        if (eNew == 0) {
            break;
        }
        *(u16 *)(*(s32 *)(eNew + 0x20) + 0x12) = 0xD00;
        *(u16 *)(eNew + 6) = *(u16 *)(eNew + 6) - 0x180;
        {
            u16 t = *(u16 *)(param_1 + 0x34);
            *(s32 *)(param_1 + 0x6C) = eNew;
            *(u16 *)(param_1 + 0x34) = t + 1;
        }
        break;

    case 1:
        eNew = func_8012C658(0x318, 6, param_1);
        if (eNew == 0) {
            break;
        }
        *(u16 *)(eNew + 6) = *(u16 *)(eNew + 6) + 0x30;
        *(u16 *)(eNew + 0xA) = *(u16 *)(eNew + 0xA) - 0xF0;
        *(u16 *)(*(s32 *)(eNew + 0x20) + 0x10) = 0xC00;
        *(u16 *)(*(s32 *)(eNew + 0x20) + 0x12) = 0xC00;
        {
            u16 t = *(u16 *)(param_1 + 0x34);
            *(s32 *)(param_1 + 0xCC) = eNew;
            *(u16 *)(param_1 + 0x34) = t + 1;
        }
        break;

    case 2:
        dx = *(s16 *)&D_80126B5E - *(s16 *)(param_1 + 6) - 0xC0;
        dy = *(s16 *)&D_80126B66 - *(s16 *)(param_1 + 0xE);
        if (0x3FFFF < dx * dx + dy * dy) {
            break;
        }
        {
            u16 t = *(u16 *)(param_1 + 0x34);
            eNew = *(s32 *)(param_1 + 0x6C);
            *(u16 *)(param_1 + 0x34) = t + 1;
            *(u16 *)(eNew + 0x34) = *(u16 *)(eNew + 0x34) + 1;
        }
        break;

    case 3:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) - 0x40;
        if (*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) != 0) {
            break;
        }
        eNew = *(s32 *)(param_1 + 0xCC);
        {
            u16 t = *(u16 *)(param_1 + 0x34);
            *(u16 *)(param_1 + 0xAE) = 0;
            *(u16 *)(param_1 + 0x34) = t + 1;
            *(u16 *)(eNew + 0x34) = *(u16 *)(eNew + 0x34) + 1;
        }
        func_8002D4C8(0xAD5, 0);
        break;

    case 4:
        break;
    }

    func_8018D3A4((void *)param_1);
}


