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
} SubRec_801EB5C8_8017D7EC; /* 0x1C */
typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017D7EC subs[16];
} GroupRec_801EB5C8_8017D7EC; /* 0x1D0 */
typedef struct {
    u16 f0;
    u16 f1;
    u16 f2;
    u16 f3;
    u16 f4;
    u16 f5;
    u16 f6;
    u16 f7;
    s32 f8;
} Local_8017EE34;
typedef struct { u16 vx, vy, vz, pad; } UVEC_8017F234;
typedef struct { u16 vx, vy, vz, pad; } UVEC_8017F55C;
typedef struct { s16 vx, vy, vz, pad; } SVec_8017FAE8;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018C880;
extern u8 D_8018C7F0;
extern u8 D_8018C7CC;
extern u8 D_8018C7A8;
extern u8 D_8018C85C;
extern u8 D_8018C838;
extern u8 D_8018C814;
extern u8 D_8018C784;
extern void func_80145934(void);
extern u8 D_8018C910;
extern u8 D_8018C8EC;
extern u8 D_8018C8C8;
extern u8 D_8018C8A4;
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
extern unsigned char D_8018BD08[];
extern unsigned char D_8018BD38[];
extern unsigned char D_8018BD88[];
extern unsigned char D_8018BDB8[];
extern unsigned char D_8018BDE8[];
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
extern void (*D_8018BE38[])(void *);
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
extern s32 D_8018BF00[];
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
extern u8 D_8018BF88[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018BF90;
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
extern int D_801B8498;
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
extern s32 D_801B849C;
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
extern s32 D_8018BFC0;
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
extern void (*D_8018C068[])(void);
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
extern void (*D_8018C08C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C07C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C0A0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C0AC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C0BC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C0D4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C0C4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C0E8[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C104[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C0F4;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C118[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C12C[])(void);
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
extern s32 D_8018C140;
extern void (*D_8018C168[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C148;
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
extern int (*D_8018C1B4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018C1B8[])(void);
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
extern unsigned short D_8018C61C[];
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
extern void (*D_8018C62C[])(void);
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
extern int D_801B84D0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018C654[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018C634;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018C644;
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
extern void (*D_8018C694[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018C69C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018C668;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018C6A8[])(void);
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
extern u8 D_8018C678;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B84D8;
extern s32 D_801B84E4;
extern s32 D_801B84E8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018C6E4[])(s32 *);
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
extern s32 D_8018C6B8[];
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
extern s32 D_801B84E0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018C934[])(void);
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
extern char D_8018C754[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018C9D8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018CB2C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018C948;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018CB34[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018C958;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018C978;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018CB3C[])(void);
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
extern void (*D_8018CB64[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018CB70[])(void);
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
extern void (*D_8018C9E4[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018CC14;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018BCF8[];
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
extern unsigned char D_8018CC28[];
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
extern s8 D_8018CC64[];
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
extern u16 D_8018CCAC;
extern u16 D_8018CCAE;
extern u16 D_8018CCB0;
extern s32 D_8018CCB4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018CCBC;
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
extern int D_8018C9C8;
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
extern unsigned int D_8018CD40[];
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
extern void (*D_8018CDF0[])(void);
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
extern u16 D_8018CE20[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018CE84;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B84F0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018CEA8[])(void);
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
extern int D_801B8548[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018CEF0[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018CEE0;
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
extern char D_801B7AA8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018CEF8[])(void);
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
extern void (*D_8018CF4C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018CF14;
extern s16 D_8018CF48;
extern s16 D_8018CF46;
extern s16 D_8018CF44;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018CF58[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B85A8;
extern u8 D_801B85A9;
extern u8 D_801B85AA;
extern u8 D_801B85AB;
extern u8 D_801B85AC;
extern u8 D_801B85AD;
extern u8 D_801B85AE;
extern u8 D_801B85AF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018CF68[])(void);
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
extern s32 D_801B85E8;
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
extern void (*D_8018CFAC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D028[];
extern s32 D_8018D048[];
extern u8 D_8018D0C4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D0E4[];
extern u8 D_8018D104[];
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
extern void (*D_8018D1A0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018D21C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B7AB8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018D228[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018D230[])(void);
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
extern void (*D_8018D2F8[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018D308[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018D318[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018D324[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018D284[];
extern u8   D_8018D298[];
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
extern void (*D_8018D33C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018D344[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018D34C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018D354[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018D35C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018D364[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018D36C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018D420[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018D428[])(void);
extern void func_80169F00(void *a0);
extern char D_8018D3D8[];
extern char D_8018D398[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018D460[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018D46C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018D4B4[])(void);
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
extern void (*D_8018D530[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B8908;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018D524[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018D568[];
extern unsigned short D_8018D570[];
extern unsigned short D_8018D578[];
extern unsigned char D_801B8910[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B8908;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018D580[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B8A44;
extern M2C_UNK D_801B8A48;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B89D0;
extern void (*D_8018D5B0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B8A4C[];
extern u8 D_801B8A54[];
extern u8 D_801B8A04[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018D5B8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018D5D4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018D5DC[])(void);
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
extern void (*D_8018D644[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018D5E8;
extern u8 D_8018D5F4;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018D678[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018D680[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018D6D4[])(void);
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
extern u16 D_8018D708[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018D6F8[];
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
extern s32 D_8018D724;
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
extern void (*D_8018D79C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018D7A4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018D7AC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018D7B4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018D7BC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018D7C4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018D7D0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018D7DC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018D7E8[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018D7F8[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018D808[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018D810[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018D818[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018D820[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018D828[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018D830[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018D838[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018D840[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018D848[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018D850[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018D858[])(void);
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
extern void (*D_8018D860[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018D868[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018D870[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018D878[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018D880[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018D888[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018D890[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018D898[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018D8A0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018D8A8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018D8B0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018D8B8[])(void);
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
extern void (*D_8018D8FC[])(void);
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
extern M2C_UNK D_8018D8C0;
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
extern void (*D_8018D92C[])(void);
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
extern void (*D_8018D968[])(void);
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
extern void (*D_8018D9C0[])();
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
extern void (*D_8018D9D0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018D9D8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018DB40[])();
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
extern void (*D_8018DB4C[])();
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
extern M2C_UNK D_801B7D00;
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
extern s16 D_801BCCA8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B9188;
extern short D_801BCD1C;
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
extern s32 D_801B95B4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B95DC;
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
extern s16 D_801B9598;
extern s32 func_8017A3B0(void);
extern short D_801B95D4;
extern short D_801B95D0;
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
extern s16 D_801B959C;
extern u16 D_801B961C;
extern u16 D_801B961E;
extern u16 D_801B9620;
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
extern s16 D_801B9614;
extern s16 D_801B9616;
extern s16 D_801B9618;
extern s16 D_801B960C;
extern s16 D_801B960E;
extern s16 D_801B9610;
extern void func_8017B7A8(void);
extern s16 D_801B962C;
extern s16 D_801B962E;
extern s16 D_801B9630;
extern s16 D_801B9634;
extern s16 D_801B9636;
extern s16 D_801B9638;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B9624;
extern short D_801B9626;
extern short D_801B9628;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B95BC;
extern SV4 D_801B95C4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B95E4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B95E0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018DD28[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018DD88[])(void);
extern void func_8017C114(void *a0);
extern void func_8017C8D0(s32 arg0);
extern void (*D_8018DD90[])(void);
extern void func_8017D7B0(void *a0);
extern void func_8017D7EC(s32 param_1);
extern void func_8017D994(void *arg0);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016ED4(void *a0);
extern void func_8017DB28(s32 a0, s32 a1);
extern void func_801890C8(s32);
extern void func_8017DDE0(void);
extern void (*D_8018DE2C[])(void);
extern void func_8017DE20(void *a0);
extern void func_8017E00C(void);
extern s32 func_8017DE5C(s32 a0);
extern s32 func_8017DEA0(s32 a0);
extern void (*D_8018DE34[])(void);
extern void func_8017DEC4(void *a0);
extern void func_8017E034(void);
extern s32 func_8017DF00(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017DF40(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017DFEC(s32 a0);
extern s32 func_80147054(void*);
extern void func_80171928(void*);
extern void func_8017E05C(s32 a0);
extern void func_8017E08C(s32 param_1);
extern void (*D_8018DE58[])(void);
extern void func_8017E134(void *a0);
extern void func_8017E170(s32 a0);
extern s32 func_8012E544(s32);
extern void func_80015978(s32, s32*);
extern void func_8017E33C(s32, s16*);
extern Blk8_80126940 D_80126940;
extern s32 D_801BA588;
extern void func_8017E180(s32 param_1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017E33C(s32 param_1, s16 *param_2);
extern u8 *func_8012913C(s32 a0);
extern void D_8018DE68(void);
extern s32 func_8017E4D4(s32 arg0, s16 *arg1, s32 arg2);
extern u8 D_8018DE5C;
extern u8 D_8018DE80;
extern s32 func_8017E5C8(s32 param_1);
extern void func_801292C8(u8 *a0);
extern void func_8012931C(void *);
extern void func_8017E67C(s32 a0);
extern void func_8017E6C0(s32 a0);
extern void (*D_8018DED0[])(void);
extern void func_8017E758(void *a0);
extern void func_8017E794(void *a0);
extern void func_8012C1B8(void);              /* TU:4202 (return taken via a cast, TU house style) */
extern void func_8012CAE4(void *a0);          /* TU:4203 */
extern void func_8012B2CC(s32 a0);            /* TU:2535 */
extern s32  rand(void);                       /* TU:958 / TU:3187 */
extern void func_8001CA1C(s32 a0, s32 a1);            /* fleet modal x1069 */
extern void func_8012A828(s32 a0, void *a1);          /* fleet modal x2791 */
extern void func_8012B178(s32 a0, s32 a1);            /* fleet modal x1749 */
extern s32  func_8012B77C(s32 out, s32 from, s32 to); /* fleet modal x83+ */
extern u8  D_80126B5C;      /* TU:362 -- scalar u8, s32 view at the use site (camera X) */
extern s32 D_80126B64;      /* project-canonical decl (camera Z)                        */
extern u8  D_8018DED8[];
extern u8  D_8018DF38[];
extern u8  D_8018DF98[];
extern u8  D_8018DFE0[];
extern s32 D_8018E028;      /* address-only: OR'd with 0x60000000 into owner+0x58 */
extern s32 D_8018E054[];    /* 16-entry X-offset table indexed by (0x70 & 0xF)    */
extern void func_8017E7E8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8012CBF4(s32 a0);
extern void func_8017F140(s32 a0);
extern s32 func_8017EBF8(void *param_1, s32 param_2);
extern void func_8017EA24(s32 a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_80126B96;
extern void (*D_8018E038[])(void);
extern void func_8017EB08(s32 param_1);
extern void func_8017F140(s32);
extern s32 func_8017EBA8(void *a0);
extern void (*D_8018E12C[])(void);
extern void func_8017EC5C(void *a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8017F0C8(s32 a0, s32 a1);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern s32  D_80126B64;
extern u8   D_8018E064[];
extern u8   D_8018E0C4[];
extern u8   D_8018E10C[];
extern u8   D_8018E11C[];
extern void func_8017EC98(void *a0);
extern s32 func_8012CBA4(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8017F018(s32 a0);
extern void func_8017EE34(s32 a0);
extern void func_8017EF94(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void (*D_8018E258[])(void);
extern void func_8017F1F8(void *a0);
extern void func_8012C1B8(void);              /* TU:3679 house style -- return via a cast */
extern void func_8012CAE4(void *a0);          /* TU:3680 */
extern void func_8001C214(s32 a0, s32 a1);    /* TU:4375 (TU-authoritative) */
extern void func_8012B178(s32 a0, s32 a1);    /* TU:3685 (fleet modal x1749) */
extern void func_8012E8A8(u8 *a0);            /* fleet modal x329 */
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);  /* fleet modal x300 */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);                  /* TU:329 */
extern s32  func_8017FA90(s32 a0, s16 a1, s32 a2);                  /* defined in this TU */
extern s32 D_8018E148[];   /* 16-entry pointer table indexed by (0x70 & 0xF) */
extern u8  D_8018E158[];   /* 12-byte-stride table indexed by ((0x70 & 0xFF0) >> 4) */
extern void func_8017F234(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_8012B260(u8 *a0);
extern void func_8012E88C(u8 *a0);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern s32  func_8017FA90(s32 a0, s16 a1, s32 a2);
extern void func_8017FAE8();
extern void func_8017F55C(s32 a0);
extern void func_8017F864(s32 a0);
extern void func_8017F86C(void);
extern void func_8017F874(s32 a0);
extern void func_8017F8D8(s32 a0);
extern void func_8017FAE8(s32 a0);
extern void (*D_8018E270[])(void);
extern void func_8017FBAC(void *a0);
extern void func_80128EA8(s32, s32, s32);
extern void func_8017FBE8(void *arg0);
extern void func_8017FC74(s32 a0);
extern void (*D_8018E278[])(void);
extern void func_8017FCF0(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8017FD2C(s32 a0);
extern s32 func_8017FEA8();
extern void func_8017FDB8(s32 a0);
extern void func_80016EF8(void *a0, void *a1);
extern s32 func_8017FEA8(void *a0);
extern void (*D_8018E280[])(void);
extern void func_8017FF54(void *a0);
extern void func_8017FF90(s32 arg0);
extern void func_8017FFEC(s32 a0);
extern void func_80180030(s32 arg0);
extern void func_801800C0(s32 a0);
extern void (*D_8018E7E8[])(void);
extern void func_80183F84(void *a0, void *a1);
extern s16 D_8018EE04;
extern s16 D_8018EE06;
extern s16 D_8018EE08;
extern s32 D_801BA6A8;
extern s32 D_801BA6AC;
extern void func_80180100(void *a0);
extern void func_8012C1B8(void);              /* TU:4202 house style -- return taken via a cast */
extern s32 func_8012C354(s32 a0, s32 a1);     /* fleet modal x1657 */
extern void func_8001C214(s32 a0, s32 a1);    /* TU-authoritative */
extern void func_80184458(void);              /* defined later in this TU (:4915) */
extern s32 D_8018E2C8;                        /* address-only at this site; fleet modal s32 scalar */
extern s32 D_8018E610;                        /* lw-width read -> s32 */
extern u8 D_801BA6B0;                         /* TU:5613 */
extern void func_801801F8(s32 a0);
extern void func_801824CC(s32, s32, s32, s32, s32);
extern void func_801802B0(s32 a0);
extern void func_801824CC(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8018373C(void *a0, s32 a1);
extern void func_80184604(s32 arg0);
extern s32 D_801BA5A0;
extern s32 D_801BA5A2;
extern s32 D_801BA5A4;
extern s32 D_801BCBBC;
extern s32 D_8018E610;
extern void func_801802E0(s32 a0);
extern s32 D_80126B58;                        /* TU:7037 house spelling; base taken as (u8 *)& like TU:7059 */
extern s32 D_801BCBBC;                        /* TU:5024 */
extern u16 D_801BA59A;                        /* sh/lhu width; no prior TU decl */
extern u16 D_801BA59C;                        /* sh/lhu width; no prior TU decl */
extern s32 D_8018E610;                        /* TU:4975 */
extern s32 func_80047948(s32 a0);             /* TU:2206 */
extern s32 func_8004787C(s32 a0);             /* TU:2207 */
extern s32 rand(void);                        /* TU:958 */
extern s32 func_8012BEE8(s32 a0);             /* TU:3924 */
extern s32 func_8012CBF4(s32 a0);             /* TU:3927 */
extern void func_8012AD80(s32 a0);            /* TU:4390 */
extern s32 func_8018233C(s32 arg0);           /* defined later in this TU (:5121) */
extern void func_80183768(void *a0, s32 a1, s32 a2);   /* defined later in this TU (:5669) */
extern void func_80183D38(void *a0, s16 a1, s32 a2);   /* defined later in this TU (:5930) */
extern s32 func_80183A64(s32 *a0, s32 a1, s32 a2);     /* defined later in this TU (:5775) */
extern s32 func_8018388C(void *a0, s32 a1);            /* defined later in this TU (:5714) */
extern void func_80183DA0(s32 a0);            /* defined later in this TU (:5953) */
extern void func_801824CC(s32, s32, s32, s32, s32);    /* TU:5009 spelling; K&R s16 def at :5191 */
extern void func_801803A0(s32 a0);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

extern s32 D_80126B58;                        /* TU:7037 house spelling; base taken as (u8 *)& like TU:7059 */
extern s32 D_801BCBBC;                        /* TU:5024 */
extern u8 D_8018AAA4[];                       /* TU house spelling */
extern u8 D_8018E2B8[];
extern s16 D_8018E88C[];                      /* lh + sll 1 index by D_801BCBBC */
extern void (*D_8018E288[])(void);            /* TU house spelling */

extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern s32 func_8018233C(s32 arg0);
extern void func_801834A4(s32 a0);
extern void func_8018364C(void *arg0);
extern s32 func_801839A4(s32 a0, s32 a1);
extern void func_80183D38(void *a0, s16 a1, s32 a2);   /* TU:5064 spelling; value taken via cast below */
extern void func_80183DA0(s32 a0);
extern void func_80183F0C(void *a0);
extern void func_801843DC();
extern void func_80184604(s32 arg0);

typedef struct {
    u16 f0;
    u16 f1;
    u16 f2;
    u16 f3;
    u16 f4;
    u16 f5;
    u16 f6;
    u16 f7;
    s32 f8;
} Local_80181C84;

void func_80181C84(s32 a0)
{
    /* LOAD-BEARING (P36 S104 e32, replacing the $s2/$v1 pins): case 7 and case 8 each carry their
     * OWN copy of the 0x34/0x1C/0x102/0xE0 tail (no shared label) -- the extra references raise the
     * entity's allocno_compare priority above `i` (global.c:594-607), so the entity takes $s1 and `i`
     * $s2; post-reload cross-jump (jump.c:2371) re-merges the two tails, so the bytes keep one copy.
     * `q` is declared inside each `if (p != 0)` block: a q shared by the two div loops is a global
     * allocno that conflicts with the unused-remainder pseudo of `0x1C0 / n` in $v1; a per-block q is
     * local and takes $v1 itself. */
    s32 s1;
    Local_80181C84 local;
    u8 *b58;
    u16 tE;
    u16 t34;
    u16 t34b;
    s32 i;
    s32 n;
    s32 r;
    s32 p;
    s32 tA;
    s32 t6;

    s1 = a0;
    /* LOAD-BEARING: `u8 *` base + *(s16 *)(b58 + 6), the TU:5099/7196 idiom -- this is what
     * parks &D_80126B58 in $s0 across the whole switch (prologue la, two `lh 0x6($s0)`). */
    b58 = (u8 *)&D_80126B58;

    switch (*(u16 *)(s1 + 0x34)) {
    case 0:
        *(s32 *)(s1 + 0x1C) = 0x40;
        /* LOAD-BEARING: read 0x34 into a temp BEFORE the 0xE0 read-modify-write, store it after.
         * Written inline, the lhu sinks below the lw and the +1 lands in the wrong register. */
        t34 = *(u16 *)(s1 + 0x34) + 1;
        *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) & ~0x10;
        *(u16 *)(s1 + 0x34) = t34;
    case 1:
        if (func_8012BEE8(s1) == 0) {
            return;
        }
        *(s16 *)(s1 + 0xA) = -0x102;
        *(s16 *)(s1 + 0xE) = -0x1C8;
        *(s32 *)(s1 + 0x1C) = 0x20;
        *(u16 *)(s1 + 0x6) = 0;
        *(s32 *)(s1 + 0x58) = ((s32)D_8018E2B8 | 0x40000000) | 0x20000000;
        *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        func_80184604(*(s16 *)(b58 + 6) > 0 ? 4 : 6);
        local.f0 = *(u16 *)(s1 + 0x6);
        local.f1 = *(u16 *)(s1 + 0xA);
        tE = *(u16 *)(s1 + 0xE);
        local.f3 = 0x170;
        local.f4 = 0x8000;
        local.f5 = 0;
        local.f6 = 0x7FFF;
        local.f7 = 0x80;
        local.f2 = tE;
        i = 0;
        do {
            local.f8 = i << 10;
            func_8012C51C(&local, s1);
            i++;
        } while (i < 4);
        break;
    case 2:
        if (func_8012BEE8(s1) != 0) {
            func_8018364C((void *)s1);
            /* LOAD-BEARING: the duplicated store (§224), not a ternary. As `<= 0 ? 4 : 3` the
             * shape is right but the result takes $v1; only the if/else lets it reuse the
             * dead compare's $v0. Polarity matters too: the DEFAULT (delay-slot) value is 3. */
            if (*(s16 *)(b58 + 6) <= 0) {
                *(u16 *)(s1 + 0x34) = 4;
            } else {
                *(u16 *)(s1 + 0x34) = 3;
            }
            func_8002D4C8(0xC2D, 0);
        }
        break;
    case 3:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) + 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) > 0x200) {
            *(u16 *)(s1 + 0x102) = 0x200;
            func_8013C9C4(D_8018AAA4);
            *(u16 *)(s1 + 0x34) = 5;
            *(s32 *)(s1 + 0x1C) = 0x40;
            func_8002D4C8(0xC06, 0);
            n = D_8018E88C[D_801BCBBC];
            for (i = 0; i < n; i++) {
                p = ((s32 (*)(void *, s16, s32))func_80183D38)((void *)s1, 0, 0);
                if (p != 0) {
                    s32 q;
                    r = rand();
                    q = 0x1C0 / n;
                    /* LOAD-BEARING: load 0x6 BEFORE storing 0xA (they may alias, so gcc will
                     * not hoist it afterwards), fold the +-0x40 into t6, and write the sum
                     * back THROUGH t6 so it keeps t6's register instead of taking a new one. */
                    tA = *(u16 *)(p + 0xA) - 0xE0;
                    t6 = *(u16 *)(p + 0x6) + 0x40;
                    *(u16 *)(p + 0xA) = tA;
                    t6 = t6 + (i * q + r % q);
                    *(u16 *)(p + 0x6) = t6;
                }
            }
        }
        break;
    case 4:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) - 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) < -0x200) {
            *(s16 *)(s1 + 0x102) = -0x200;
            func_8013C9C4(D_8018AAA4);
            *(u16 *)(s1 + 0x34) = 6;
            *(s32 *)(s1 + 0x1C) = 0x40;
            func_8002D4C8(0xC06, 0);
            n = D_8018E88C[D_801BCBBC];
            for (i = 0; i < n; i++) {
                p = ((s32 (*)(void *, s16, s32))func_80183D38)((void *)s1, 0, 0);
                if (p != 0) {
                    s32 q;
                    r = rand();
                    q = 0x1C0 / n;
                    /* LOAD-BEARING: load 0x6 BEFORE storing 0xA (they may alias, so gcc will
                     * not hoist it afterwards), fold the +-0x40 into t6, and write the sum
                     * back THROUGH t6 so it keeps t6's register instead of taking a new one. */
                    tA = *(u16 *)(p + 0xA) - 0xE0;
                    t6 = *(u16 *)(p + 0x6) - 0x40;
                    *(u16 *)(p + 0xA) = tA;
                    t6 = t6 - (i * q + r % q);
                    *(u16 *)(p + 0x6) = t6;
                }
            }
        }
        break;
    case 5:
    case 6:
        if (func_8012BEE8(s1) != 0) {
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 2;
        }
        break;
    case 7:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) - 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) < 0) {
            t34b = *(u16 *)(s1 + 0x34) + 1;
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x102) = 0;
            *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
            *(u16 *)(s1 + 0x34) = t34b;
        }
        break;
    case 8:
        *(u16 *)(s1 + 0x102) = *(u16 *)(s1 + 0x102) + 0x20;
        if ((s16)*(u16 *)(s1 + 0x102) > 0) {
            t34b = *(u16 *)(s1 + 0x34) + 1;
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x102) = 0;
            *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
            *(u16 *)(s1 + 0x34) = t34b;
        }
        break;
    case 9:
    case 10:
        if (func_8012BEE8(s1) != 0) {
            func_801843DC(s1);
            *(s32 *)(s1 + 0x1C) = 0x10;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 11:
        if (func_8012BEE8(s1) == 0) {
            return;
        }
        func_80183F0C((void *)s1);
        *(s32 *)(s1 + 0x4) = 0xFFF80000;
        *(s32 *)(s1 + 0x8) = 0xFE5E0000;
        *(s32 *)(s1 + 0xC) = 0xFE380000;
        *(s32 *)(s1 + 0x58) = ((s32)D_8018E288 | 0x40000000) | 0x20000000;
        return;
    }
    func_80183DA0(s1);
    func_801834A4(s1);
    func_801839A4(s1, 0x30);
    if (func_8018233C(s1) == 1) {
        func_801843DC(s1);
        *(s32 *)(s1 + 0xE0) = *(s32 *)(s1 + 0xE0) | 0x10;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80183EE8(void);
extern void func_80184604();

void func_80182220(s32 a0) {
    *(s16 *)((s32)a0 + 0x2) = 0xB;
    *(s32 *)((s32)a0 + 0x1C) = 0x3C;
    *(s16 *)((s32)a0 + 0x34) = 0;
    func_8002D4C8(0x72C, 0);
    func_80183EE8();
    func_80184604(-1);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void (*D_8018E288[])(void);
extern u8 D_801BA6B0;

void func_8018226C(s32 arg0)
{
    s32 p1;
    s32 p2;

    if (*(u16 *)(arg0 + 0x34) == 0 && func_8012BEE8(arg0) != 0) {
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4) |= 0x80000000;
        *(s32 *)(arg0 + 0x4) = 0xFFF80000;
        *(s32 *)(arg0 + 0x8) = 0xFE5E0000;
        *(s32 *)(arg0 + 0xC) = 0xFF360000;

        p1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(p1 + 0x1A) = 0x1000;
        *(s16 *)(p1 + 0x18) = 0x1000;

        p2 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(p2 + 0x14) = 0;
        *(s16 *)(p2 + 0x12) = 0;
        *(s16 *)(p2 + 0x10) = 0;

        *(s32 *)(arg0 + 0x58) = ((s32)D_8018E288 | 0x40000000) | 0x20000000;
        *(u16 *)(arg0 + 0x34) += 1;
        func_8012B2CC(arg0);
        D_801BA6B0 = 0;
    }
}


void func_80182334(void) {
}

#include "common.h"

extern void func_8012E9C0(s32 a0);
extern s16 D_8018EDFC;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

s32 func_8018233C(s32 arg0) {
    s16 flags;
    s32 spawn;
    s32 target;
    s16 *p;

    flags = *(u16 *)(arg0 + 0x5C);
    if (!(flags & 1)) {
        return 0;
    }
    if (*(u16 *)(arg0 + 0x5E) == 0x22) {
        *(u16 *)(arg0 + 0x5C) = flags & 0xFFFE;
        *(u16 *)(arg0 + 0x5E) = 0;
        return 0;
    }

    p = &D_8018EDFC;
    *(u16 *)(arg0 + 0x60) = 8;
    func_8012E9C0(arg0);
    *p -= *(u16 *)(arg0 + 0x60);

    if (*(s16 *)(arg0 + 0xAC) == 0) {
        *(s16 *)(arg0 + 0xAC) = 8;
    }
    func_8002D4C8(0xC08, 0);

    spawn = func_80132EF4(arg0, 0x22);
    if (spawn != 0) {
        *(u16 *)(spawn + 0x34) = ((rand() % 3 << 12) + 0x4000) | 2;
        *(s32 *)(spawn + 0x14) = 0xFFF80000 - ((rand() % 3) << 16);
        *(u16 *)(spawn + 0x6) = *(u16 *)(arg0 + 0x7C);
        *(u16 *)(spawn + 0xA) = *(u16 *)(arg0 + 0x7E);
        *(u16 *)(spawn + 0xE) = *(u16 *)(arg0 + 0x80);
    }

    if (*p <= 0) {
        *p = 0;
        target = *(s32 *)(arg0 + 0x64);
        *(s16 *)(target + 0x2) = 4;
        *(u16 *)(arg0 + 0x5C) = 0;
        *(s16 *)(arg0 + 0x2) = 0xA;
        return 1;
    }
    return 0;
}


typedef struct { u8 b[20]; } Stk;

/* f1 is SIGNED: `vec.f1 = -4` / `-0x10` must materialise as `addiu $v0,$zero,-K`.
 * A u16 field converts the constant to 0xFFFC/0xFFF0 and emits `ori` instead. */
typedef struct {
    u16 f0;
    s16 f1;
    u16 f2;
} Vec3x16;

extern s32 rand(void);
extern u16 D_800B99DA;
extern s32 func_8004787C(s32 a0);
extern s32 D_8018E59C[];
extern u8 D_801B822C[];
extern s32 func_801850D8();

/* LOAD-BEARING: K&R definition with s16 a1/a2/a3. The `s16` parameter type is what
 * produces the per-use `sll/sra 16` pairs; s32 params + explicit (s16) casts give a
 * different allocation (measured 189/322). The K&R form (not an ANSI prototype) is
 * also what keeps this compatible with the TU's earlier
 * `extern void func_801824CC(s32, s32, s32, s32, s32);` — an ANSI s16 prototype is a
 * hard "conflicting types" error there. */
void func_801824CC(a0, a1, a2, a3, mask)
    s32 a0;
    s16 a1;
    s16 a2;
    s16 a3;
    s32 mask;
{
    Stk stk;
    Vec3x16 vec;
    s32 base;
    s32 i;
    s32 r;
    u16 *p;

    stk = *(Stk *)D_801B822C;
    base = (func_8004787C((D_800B99DA << 6) & 0x7C0) << 4) >> 12;
    if (D_800B99DA % 6 == 0) {
        vec.f2 = 0;
        for (i = 0; i < 5; i++) {
            /* LOAD-BEARING: the explicit pointer temp. Writing the two loads as
             * `*(u16 *)&stk.b[i * 4]` / `[i * 4 + 2]` inline permutes $v0/$v1 on the
             * `sll`/`addiu $sp` pair that feeds the addu. */
            p = (u16 *)&stk.b[i * 4];
            vec.f0 = base + p[0];
            vec.f1 = p[1];
            r = func_801850D8(1, (s16)(a1 + rand() % ((a1 << 16) >> 17)), a2, a3, &vec, a0,
                              D_8018E59C[rand() & 1], 0);
            if (r != 0) {
                *(s32 *)(r + 0x20) |= mask;
            }
        }
    }
    if ((D_800B99DA & 3) == 0) {
        vec.f0 = base;
        vec.f1 = 0;
        vec.f2 = 0;
        r = func_801850D8(1, (s16)(a1 + rand() % ((a1 << 16) >> 17)), a2, a3, &vec, a0,
                          D_8018E59C[rand() & 1], -0x80000);
        if (r != 0) {
            *(s32 *)(r + 0x20) |= mask;
        }
    }
    if (D_800B99DA % 5 == 0) {
        vec.f1 = -4;
        vec.f2 = 0;
        for (i = 0; i < 2; i++) {
            /* LOAD-BEARING association: `(i << 5) + (base - 0x10)`, NOT
             * `base + (i << 5) - 0x10`. The latter makes `base + i*32` a giv of
             * benefit 4 (> 2*biv_count), so strength_reduce reduces it to an extra
             * induction pseudo — which also steals the last callee-saved register and
             * pushes `mask` out of $fp into memory. Splitting the invariant off leaves
             * a bare `i<<5` giv (benefit 2 - 2 = 0 => "not worth while"), and
             * `base - 0x10` stays unhoisted inside the loop. */
            vec.f0 = (i << 5) + (base - 0x10);
            r = func_801850D8(1, (s16)(a1 + rand() % ((a1 << 16) >> 17)), a2, a3, &vec, a0,
                              D_8018E59C[rand() & 1], -0x60000);
            if (r != 0) {
                *(s32 *)(r + 0x20) |= mask;
            }
        }
    }
    if (D_800B99DA % 6 == 0) {
        vec.f1 = -0x10;
        vec.f2 = 0;
        for (i = 0; i < 2; i++) {
            vec.f0 = (i << 6) + (base - 0x20);
            r = func_801850D8(1, (s16)(a1 + rand() % ((a1 << 16) >> 17)), a2, a3, &vec, a0,
                              D_8018E59C[rand() & 1], -0x60000);
            if (r != 0) {
                *(s32 *)(r + 0x20) |= mask;
            }
        }
    }
}


#include "common.h"

extern s32  rand(void);
extern s32  func_801850D8();
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern u8   D_800D3918[];
extern u8   D_8018E4DC[];
extern u8   D_8018E47C[];

void func_801829CC(s32 arg0) {
    /* SVEC_801BA5A8 / D_801BA5A8 are declared at BLOCK scope on purpose: this
     * block sits at TU offset ~5267, ABOVE the file-scope
     * `typedef struct { s16 vx, vy, vz, pad; } SVEC_801BA5A8;` that func_801848A4
     * already introduces further down the same TU. A second file-scope copy is
     * "conflicting types for `SVEC_801BA5A8'" (anonymous struct bodies are never
     * compatible), which is what killed the previous whole-binary gate on this
     * function. Block scope keeps the same codegen and no file-scope clash. */
    typedef struct { s16 vx, vy, vz, pad; } SVEC_801BA5A8;
    extern SVEC_801BA5A8 D_801BA5A8[];

    s16 sp20[3];
    s32 sp28[3];
    s32 sp38[8];
    s32 i, j, k;
    s32 obj, sub;
    s32 r;

    sp20[2] = 0;
    sp20[0] = 0;
    sp28[1] = 0;
    sp28[0] = 0;
    sp28[2] = 0xFFEF0000;
    for (i = 0; i < 6; i++) {
        obj = func_801850D8(2, 0x4000, 0, 0, D_800D3918, arg0, D_8018E4DC, 0);
        if (obj != 0) {
            k = 0x1800;
            sp20[1] = i * 0x2AA;
            func_80049CAC((s32)sp20, (s32)sp38);
            func_800484EC((s32)sp38, (s32)sp28, obj + 0x10);
            *(s16 *)(obj + 0x3A) = -1;
            *(s16 *)(obj + 0x50) = i;
            *(s32 *)(obj + 0x20) |= 0x300000;
            r = rand();
            *(s16 *)(obj + 0x4C) = r % 8;
            *(s16 *)(obj + 0xA) = -0x40;
            for (j = 0; j < 8; j++) {
                sub = func_801850D8(3, (s16)k, 0, 0, D_800D3918, arg0, D_8018E47C, 0);
                if (sub != 0) {
                    *(s32 *)(sub + 0x50) = obj + 0x34;
                    *(s16 *)(sub + 0x54) = j;
                    *(s16 *)(sub + 0x56) = i;
                    *(u16 *)(sub + 0x2C) += 0x2000;
                    *(s32 *)(sub + 0x20) |= 0x300000;
                    r = rand();
                    *(s16 *)(sub + 0x4C) = r % 8;
                }
                k += 0x400;
            }
        }
        D_801BA5A8[i].vx = 0;
        D_801BA5A8[i].vy = 0;
        D_801BA5A8[i].vz = 0;
    }
}


#include "common.h"

extern void func_80184FBC(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_80047D3C(s32 a0);
extern s32  func_801850D8();
extern s32  rand(void);
extern u8   D_800D3918[];
extern u8   D_8018E47C[];

/* the func_8012F14C in/out vectors are read back with `lhu`, so u16 fields
 * (TU:4309 house note on func_8017F234) */
typedef struct { u16 vx, vy, vz, pad; } UVEC_80182BD8;

void func_80182BD8(s32 a0, u16 *a1, s32 a2, s32 a3)
{
    s32 buf1[8];
    s32 buf2[8];
    UVEC_80182BD8 out1;
    UVEC_80182BD8 out2;
    UVEC_80182BD8 diff;
    s32 base;
    s32 ent;
    s32 i;
    s32 e;
    u16 cur;

    cur = a1[0];
    base = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20);
    if (*(s16 *)a1 != -1) {
        do {
            func_80184FBC(base, (s16)cur, buf1);
            func_80184FBC(base, *(s16 *)(a1 + 1), buf2);
            func_8012F14C((s32)buf1, (s32)D_800D3918, (s32)&out1);
            func_8012F14C((s32)buf2, (s32)D_800D3918, (s32)&out2);
            diff.vx = out2.vx - out1.vx;
            diff.vy = out2.vy - out1.vy;
            diff.vz = out2.vz - out1.vz;
            a1[2] = out1.vx;
            a1[3] = out1.vy;
            a1[4] = out1.vz;
            e = VectorNormalSS(&diff, a1 + 6);
            if (a3 == 0) {
                a1[9] = func_80047D3C(e);
                for (i = 0; i < a2; i++) {
                    ent = func_801850D8(4, 0x3000, 0, 0, &diff, a0, (s32)D_8018E47C, 0);
                    if (ent != 0) {
                        *(s32 *)(ent + 0x50) = (s32)a1;
                        *(s16 *)(ent + 0x54) = i;
                        *(s16 *)(ent + 0x56) = a2;
                        *(s16 *)(ent + 0x4C) = rand() % 8;
                        *(s32 *)(ent + 0x20) |= 0x800000;
                    }
                }
            }
            a1 += 10;
            cur = a1[0];
        } while (*(s16 *)a1 != -1);
    }
}


#include "common.h"

/* func_80182DCC — MATCH (234 ins). Ambient-particle spawner: on two independent
 * frame-counter beats it fires bursts of func_801850D8 emitters at randomised Y.
 *
 * KEY TECHNIQUES (all four are the whole crack; see the notes in the wave report):
 *  1. `D_800B99DA % 7` / `*(u16*)(p+0xA3AA) % 9` — a plain `u16 % const` shortens
 *     (c-typeck `shorten` for TRUNC_MOD_EXPR with an unsigned NOP_EXPR operand), so
 *     you get the UNSIGNED magic (0x24924925 / 0x38E38E39) + a trailing
 *     `andi 0xFFFF`. Do NOT write `(u32)D_800B99DA % 7` — that loses the andi.
 *  2. The SAME halfword is read twice with two different spellings: once as the bare
 *     symbol `D_800B99DA` (lui %hi / lhu %lo) and once off a held base pointer
 *     `u8 *p = D_800AF630;` at +0xA3AA (as expands `lui at,1; addu at,s3,at;
 *     lhu -0x5C56(at)`) — the resident.c "single-base-register" idiom. `p` declared
 *     at the TOP is what keeps &D_800AF630 in a callee-saved reg across block 1.
 *  3. &D_8018E59C must RELOAD at each call (folded lui %hi / addu / lw %lo), not
 *     hoist into a 9th callee reg: write it as a BYTE pointer + SHIFTED index
 *     `*(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C)`, never `D_8018E59C[rand() & 1]`
 *     (the array form costs `la` + one more saved register = +4 ins).
 *  4. `sp20[1] -= 0x20; sp20[1] -= i*4;` must be written as SEPARATE statements on an
 *     s32 temp. Any single expression (`x - 0x20 - i*4`, parenthesised, or via a temp
 *     for the product) lets gcc associate the constant into the induction variable and
 *     loop.c strength-reduces `0x20 + 4*i` to one register (`li s4,32` + `addiu 4`).
 *     The target keeps `sll i,2` unreduced — a bare 4*i giv is below the worth-while
 *     threshold. Writing `x - i*4 - 0x20` also avoids the giv but emits subu BEFORE
 *     addiu; only the split statements give the target's addiu-then-subu order.
 *
 * BANKING NOTE (S71a, law 2): the destination TU declares `extern s32 D_8018E59C[];` at FILE
 *  scope (TU:5181, before this function) and reads it as
 *  `*(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C)` (TU:5347, func_801831E0). The earlier
 *  draft's file-scope `extern u8 D_8018E59C[];` was a 'conflicting types' compile error in the
 *  TU -- the body was already right. Spelled per the TU here; re-verified MATCH standalone AND
 *  spliced into a scratch copy of the TU (cc1 clean, 234/234, 19/19 relocs by offset+symbol).
 *
 * Regalloc/schedule levers that closed the last 46 instructions:
 *  - THREE separate `range` locals (0xA00 / 0x1000 / base>>1). gcc-2.7.2 has no
 *    live-range splitting, so one C variable = one hard reg; the target uses s1/s7/s4,
 *    which is only reachable with three variables. This alone fixed all 39 register
 *    mismatches (arg0 s7->s6, p s1->s3, base s6->s5, off s4->s3, copy s5->s4).
 *  - loop 2's per-outer-iteration offset is written INLINE as `i * 0x600` so loop.c
 *    reduces it and emits the non-replaceable giv's `move s4,s3` at the top of the
 *    body (loop.md L5); loop 3's is a plain `off += 0x800` biv, used directly.
 *  - `i = 0;` hoisted out of each `for (;;)` header: sched1 wants the counter init
 *    between `base` and `range` in all three preheaders (last 7 mismatches).
 */

extern u8 D_800AF630[];
extern u16 D_800B99DA;
extern s32 rand(void);
extern s32 func_801850D8();
extern s32 D_8018E59C[];

void func_80182DCC(void *arg0) {
    u16 sp20[3];
    u8 *p = D_800AF630;
    s32 i, j;
    u32 base;
    s32 range1;
    s32 range2;
    s32 range3;
    s32 off;
    s32 ret;
    s32 h;

    if (D_800B99DA % 7 == 0) {
        base = 0x1400;
        i = 0;
        range1 = 0xA00;
        sp20[0] = 0x30;
        sp20[1] = 0;
        sp20[2] = 0;
        for (; i < 7; i++) {
            ret = func_801850D8(1, base + rand() % range1, 0, 0, sp20, (s32)arg0,
                                *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
            if (ret != 0) {
                *(s32 *)(ret + 0x20) |= 0xA00000;
            }
            sp20[0] -= 0x10;
        }
    }
    if (*(u16 *)(p + 0xA3AA) % 9 == 0) {
        base = 0x2000;
        i = 0;
        range2 = 0x1000;
        sp20[1] = 8;
        sp20[2] = 0;
        for (; i < 5; i++) {
            sp20[0] = 8;
            h = sp20[1];
            h -= 0x20;
            h -= i * 4;
            sp20[1] = h;
            for (j = 0; j < 3; j++) {
                ret = func_801850D8(1, (s16)(base + rand() % range2 + i * 0x600), 0, 0, sp20,
                                    (s32)arg0, *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
                if (ret != 0) {
                    *(s32 *)(ret + 0x20) |= 0xA00000;
                }
                sp20[0] -= 8;
            }
        }
        sp20[1] = 0;
        i = 0;
        range3 = base >> 1;
        off = 0x800;
        for (; i < 2; i++) {
            sp20[0] = 8;
            sp20[1] += 0x14;
            for (j = 0; j < 3; j++) {
                ret = func_801850D8(1, (s16)(base + rand() % range3 - off), 0, 0, sp20,
                                    (s32)arg0, *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
                if (ret != 0) {
                    *(s32 *)(ret + 0x20) |= 0xA00000;
                }
                sp20[0] -= 8;
            }
            off += 0x800;
        }
    }
}


extern u16 D_801BA628;
extern u16 D_801BA62A;
extern u16 D_801BA62C;
extern void func_801831E0();

void func_80183174(s32 a0) {
    u16 *p = &D_801BA628;
    u16 local_10[3];
    u16 local_18[3];
    register u16 c1 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus10)

    local_10[0] = *p;
    local_10[1] = D_801BA62A;
    c1 = D_801BA62C;
    local_10[2] = c1;
    func_801831E0(a0);
    local_18[0] = *p;
    local_18[1] = D_801BA62A;
    local_18[2] = D_801BA62C;
}


#include "common.h"

extern s32 rand(void);
extern s32 func_801850D8();

void func_801831E0(s32 arg0, s32 arg1) {

    extern u16 D_801BA6A0[];
    extern u16 D_801BA5E8;
    extern u16 D_801BA5EA;
    extern u16 D_801BA5EC;
    extern s32 D_8018E59C[];
    u16 *w;
    u16 *e;
    u16 *m;
    s32 ctr;
    s32 q;
    s32 ret;
    s32 t;

    w = D_801BA6A0;
    switch (arg1) {
    case 0:
        ctr = 0x17;
        do {
            w[0] = *(u16 *)(arg0 + 6);
            w[1] = *(u16 *)(arg0 + 0xA);
            w[2] = *(u16 *)(arg0 + 0xE);
            ctr--;
            w -= 4;
        } while (ctr >= 0);
        break;
    case 1:
    case 3:
        D_801BA5E8 = *(u16 *)(arg0 + 6);
        D_801BA5EA = *(u16 *)(arg0 + 0xA);
        D_801BA5EC = *(u16 *)(arg0 + 0xE);
        ctr = 0x17;
        do {
            m = w + 1;
            e = w + 2;
            *w = *(w - 4);
            *m = *(w - 3);
            *e = *(w - 2);
            if ((D_800B99DA & 7) == 0 && (ctr & 1) != 0) {
                q = rand() % 4096;
                if ((rand() & 1) == 0) {
                    t = -q;
                    q = t + 0x4000;
                } else {
                    q = q + 0x4000;
                }
                ret = func_801850D8(5, (s16)q, 0, 0, w, 0, *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
                if (ret != 0) {
                    *(s32 *)(ret + 0x54) = arg1 - 1;
                    *(s32 *)(ret + 0x50) = (s32)w;
                    *(s32 *)(ret + 0x20) |= 0x200000;
                }
            }
            ctr--;
            w -= 4;
        } while (ctr > 0);
        break;
    case 2:
        ctr = 0x17;
        do {
            if ((D_800B99DA & 7) == 0 && (ctr & 1) != 0) {
                q = rand() % 4096;
                if ((rand() & 1) == 0) {
                    t = -q;
                    q = t + 0x4000;
                } else {
                    q = q + 0x4000;
                }
                ret = func_801850D8(5, (s16)q, 0, 0, w, 0, D_8018E59C[rand() & 1], 0);
                if (ret != 0) {
                    *(s32 *)(ret + 0x50) = (s32)w;
                    *(s32 *)(ret + 0x54) = arg1;
                    *(s32 *)(ret + 0x20) |= 0x200000;
                }
            }
            ctr--;
            w -= 4;
        } while (ctr > 0);
        break;
    }
}


extern s32 rand(void);
extern s32 func_801850D8();

/* MATCH candidate (106/106 in match_one; see rtu_match below).  T5x Fable, 2026-09-05.
 *
 * Carried over from the S71 body (byte-proven, do not touch):
 *  - `tmp` pinned to $2 forces the `addu $s6,$v0,$zero` base copy and makes the
 *    modulus read the pre-copy pseudo (`sll $v0,$v0,16`, not `$v0,$s6,16`).
 *  - `*(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C)` (sibling func_801831E0's
 *    spelling) keeps the D_8018E59C address from being hoisted.
 *
 * THE RESIDUAL THAT WAS CALLED A WALL (idx 82-89) and how it closes:
 *  The target hoists ONLY the /3 sign-correction `sra $s5,$s4,31` and keeps the
 *  const+mult+mfhi+subu inline.  One `x / 3` can never do that: expand_divmod
 *  (expmed.c:3034-3057) emits K(const) B(smulsi3_highpart) C(sra 31) D(minus)
 *  ADJACENTLY from the SAME op0 rtx, so loop.c's invariant_p gives B and C the
 *  same verdict; if B is a movable, force_movables (loop.c:1193-1228) links K to it
 *  (K.lifetime += B.lifetime, K.savings DOUBLES) and K (29*6=174 >= 37) hoists.
 *  A hard-reg dividend kills all four (scan_loop:596 forces n_times_set[hard]=1).
 *
 *  Lever = CSE, not loop.c.  cse.c's canon_reg NEVER rewrites a hard register, but
 *  its hash/exp_equiv_p compare QUANTITIES.  So:
 *    sign = half >> 31;      at the TOP of the body: a movable by criterion (1)
 *                            (maybe_never==0 there, scan_loop:696-706); life 71 -> hoisted.
 *    hh = half;              hard $2 <- pseudo: cse puts $2 in half's quantity.
 *    pos[0] -= hh / 3;       B reads $2 (call-used hard reg -> invariant_p==0 -> not a
 *                            movable, so K stays unlinked: life 1 * sav 1 * 29 < 37 =
 *                            "not desirable" -> lui/ori inline); C `(ashiftrt $2 31)`
 *                            hashes into sign's `(ashiftrt half 31)` -> replaced by
 *                            (reg sign); D becomes `B - sign`.  The `hh = half` copy is
 *                            then folded into the mult by combine (can_combine_p allows a
 *                            hard i2dest with REG_DEAD in i3) -> no extra insn.
 *  Why $2 and not a callee-saved pin: the pinned reg enters regs_ever_live (flow runs
 *  before combine deletes the copy) -> global.c pass 0 hands it to the first callee-saved
 *  allocno (j took $s4, closeness 7).  $2 is ever-live anyway and dead in that window.
 *  Why `= 0` at the declaration: an unread `sign` store is deleted by jump.c before cse
 *  (first_uid==last_uid).  An asm feed keeps it alive but adds +2 weighted refs
 *  (sign 7/39 beats half 7/44 in allocno_compare -> half/sign swapped, closeness 4).
 *  The dead initializer survives jump/cse (two references), is deleted by flow as a
 *  dead store before regalloc and never counted, so sign = 5 refs/38 insns
 *  (10/38=.263) lands exactly between half (14/44=.318) and base (10/50=.2): the
 *  target's j,mod,i,half,sign,base,arg0 = $s1..$s7 order.  match_one MATCH 106/106,
 *  rtu_match MATCH in the real TU (2026-09-05).
 */
void func_801834A4(s32 arg0) {

    extern s32 D_8018E894[];
    u16 pos[3];
    s32 i;
    s32 j;
    s32 u;
    s32 base;
    register s32 tmp __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 mod;
    s32 step;
    s32 obj;
    s32 half;
    register s32 hh __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 sign = 0;

    if ((D_800B99DA & 7) == 0) {
        pos[1] = 0;
        pos[2] = 0;
        for (i = 0; i < 6; i++) {
            u = D_8018E894[i];
            tmp = u * 0x600 + 0x2000;
            base = tmp;
            __asm__ ("" : "=r"(tmp) : "0"(tmp));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
            mod = (tmp << 16) >> 18;
            step = u * 6 + 0x12;
            half = step * 2;
            pos[0] = step;
            pos[1] -= 0x24;
            for (j = 0; j < 4; j++) {
                sign = half >> 31;
                obj = func_801850D8(1, (s16)(base + rand() % mod), 0, 0, pos, arg0,
                                    *(s32 *)(((rand() & 1) << 2) + (s32)D_8018E59C), 0);
                if (obj != 0) {
                    *(s32 *)(obj + 0x20) |= 0x800000;
                }
                hh = half;
                pos[0] -= hh / 3;
            }
        }
    }
}


extern s32 rand(void);
extern s32 func_801850D8();
extern u8 D_8018E47C[];

void func_8018364C(void *arg0) {
    s16 sp20[3];
    s32 i;
    s32 r;
    s32 ret;

    sp20[2] = 0;
    sp20[0] = 0;
    sp20[1] = -0x120;
    for (i = 0; i < 10; i++) {
        r = rand();
        ret = func_801850D8(6, (s16)(i * 0x200 + 0x3000 + r % 1024), 0, 0, sp20,
                            (s32)arg0, (s32)D_8018E47C, 0);
        if (ret != 0) {
            *(s16 *)(ret + 0x52) = i;
            r = rand();
            *(s16 *)(ret + 0x4C) = r % 8;
        }
    }
}


void func_8018373C(void *a0, s32 a1)
{
    s32 arg[3];

    arg[2] = a1;
    arg[1] = 0;
    arg[0] = 0;
    func_8018383C(a0, arg);
}


void func_80183768(void *a0, s32 a1, s32 a2)
{
    s32 s0a, s0b;
    s32 arg[3];

    s0a = func_80047948((*(s32 *)((u8 *)a0 + 0x1C) << 5) & 0xFE0)
        - func_80047948(((*(s32 *)((u8 *)a0 + 0x1C) - 1) << 5) & 0xFE0);
    arg[0] = (a1 * s0a) << 4;
    arg[2] = 0;
    s0b = func_8004787C((*(s32 *)((u8 *)a0 + 0x1C) << 5) & 0x7E0)
        - func_8004787C(((*(s32 *)((u8 *)a0 + 0x1C) - 1) << 5) & 0x7E0);
    arg[1] = -((a2 * s0b) << 4);
    func_8018383C(a0, arg);
}


extern s32 D_801BA5A0;

void func_8018383C(s32 a0, s32 a1)
{
    s32 buf[8];

    func_80049CAC((s32)&D_801BA5A0, (s32)&buf);
    func_800484EC((s32)&buf, a1, a0 + 0x10);
}


#include "common.h"

/* skeleton-twin: ov_SC01_077:func_8012D664 (banked) — same D_80126B5E/62/66
 * globals-into-locals shape, different callee (AABB test func_8013361C
 * instead of func_800132BC). */

typedef struct {
    s16 a, b, c;
} Vec3s16_8018388C;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 *D_80126B90;
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_8018388C(void *a0, s32 a1) {
    Vec3s16_8018388C s;
    Vec3s16_8018388C s1;
    Vec3s16_8018388C diff;
    s16 *box0;
    s16 *box1;

    box0 = (s16 *)(((s32)D_80126B90 & 0xFFFFFFF) | 0x80000000);
    box1 = (s16 *)((*(s32 *)((u8 *)a0 + 0x58) & 0xFFFFFFF) | 0x80000000);

    s.a = D_80126B5E;
    s.b = D_80126B62;
    s.c = D_80126B66;

    s1.a = *(u16 *)((u8 *)a0 + 0x6);
    s1.b = *(u16 *)((u8 *)a0 + 0xA);
    s1.c = *(u16 *)((u8 *)a0 + 0xE);

    if (func_8013361C(box0, box1, &s, &s1) != 0) {
        diff.a = s.a - s1.a;
        diff.b = s.b - s1.b;
        diff.c = s.c - s1.c;

        VectorNormalSS(&diff, &diff);

        func_8012F568(1, 0x4201, 0, a1, &s1, &diff);

        return 1;
    }
    return 0;
}


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 *D_80126B78;
extern s32  D_8018E8AC;
extern u8   D_801152A8[];

s32 func_801839A4(s32 param_1, s32 param_2)
{
    SVECTOR out1;
    SVECTOR out2;
    s32 iVar1;

    func_8012F14C((s32)D_80126B78 + 0x34, (s32)&D_8018E8AC, (s32)&out1);
    func_8012F14C((s32)D_80126B78 + 0x34, (s32)&D_8018E8AC + 8, (s32)&out2);

    iVar1 = func_80135888(*(s32 *)(param_1 + 0x20), *(s32 *)(param_1 + 0x58),
                           (s32)&out1, (s32)&out2);

    if (iVar1 != 0) {
        func_8012F568(1, 0x4201, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12),
                      param_2, (s32)&out2, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


s32 func_80183A64(s32 *a0, s32 a1, s32 a2) {
        s32 v1 = a0[0x4 / 4];
        if (a1 < v1) {
            a0[0x4 / 4] = a1;
            return 1;
        }
        if (v1 < a2) {
            a0[0x4 / 4] = a2;
            return 1;
        }
        return 0;
    }


#include "common.h"

extern s32 rand(void);
extern s32 func_80183CA4();
extern s32 func_80183C6C(void *arg0, void *arg1);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s16 D_801152B0;

/* Random-behaviour dispatcher.  func_80183CA4() returns a flag word; bit 0x2000
 * and bit 0x8000 select two mirrored behaviours that differ ONLY in the table
 * passed as arg1 of the first func_80183C6C call (D_801152A8 vs &D_801152B0).
 * Each behaviour: 15/16 of the time run the table lookup, 1/16 of the time
 * nudge field 0xF0 by +-(rand() % 512) around a +0x800 bias.
 *
 * The four zero-byte __asm__ fences are REORG steering, not semantics.  gcc's
 * dbr_schedule (reorg.c fill_eager_delay_slots -> fill_slots_from_thread) will
 * otherwise "steal" the first insn of a branch's target/fall-through thread
 * into the branch's delay slot; the target keeps those two delay slots empty.
 * An ASM_OPERANDS insn is not eligible_for_delay, so a fence at a thread's HEAD
 * blocks the steal.  A fence at a thread's TAIL additionally blocks jump.c
 * cross_jump: find_cross_jump compares ASM_OPERANDS including their source
 * line, so two fences on different lines never match and the merge stops there
 * -- which is why only the SECOND region carries the trailing fence: it keeps
 * the first region's own `addu` alive so fill_simple's backward scan can drop
 * it into that region's `j` delay slot (target 80183B44).
 */
s32 func_80183A98(void *a0) {
    s32 flags;
    s32 s0;
    s32 s1;
    struct {
        s16 x0; /* 0x10(sp) */
        s16 x2; /* 0x12(sp) */
    } local;

    flags = func_80183CA4();
    if (flags & 0x2000) {
        if ((rand() & 0xF) != 0) {
            local.x0 = (s16)(*(s32 *)((u8 *)a0 + 0x10) >> 8);
            local.x2 = (s16)(*(s32 *)((u8 *)a0 + 0x14) >> 8);
            *(s32 *)((u8 *)a0 + 0xF0) =
                func_80183C6C(D_800D3918, D_801152A8) * 2 - func_80183C6C(&local, D_800D3918);
        } else {
            s0 = rand() % 512;
            s1 = *(s32 *)((u8 *)a0 + 0xF0) + 0x800;
            {
                s32 t;
                if ((rand() & 1) == 0) {
                    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
                    t = s1 - s0;
                } else {
                    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
                    t = s1 + s0;
                }
                *(s32 *)((u8 *)a0 + 0xF0) = t;
            }
        }
    } else if (flags & 0x8000) {
        if ((rand() & 0xF) != 0) {
            local.x0 = (s16)(*(s32 *)((u8 *)a0 + 0x10) >> 8);
            local.x2 = (s16)(*(s32 *)((u8 *)a0 + 0x14) >> 8);
            *(s32 *)((u8 *)a0 + 0xF0) =
                func_80183C6C(D_800D3918, &D_801152B0) * 2 - func_80183C6C(&local, D_800D3918);
        } else {
            s0 = rand() % 512;
            s1 = *(s32 *)((u8 *)a0 + 0xF0) + 0x800;
            {
                s32 t;
                if ((rand() & 1) == 0) {
                    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
                    t = s1 - s0;
                } else {
                    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
                    t = s1 + s0;
                    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
                }
                *(s32 *)((u8 *)a0 + 0xF0) = t;
            }
        }
    } else {
        return 0;
    }
    return 1;
}


void func_80183C20(void *a0) {
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    u16 in[2];
    u16 g[2];

    in[0] = *(u16 *)((u8 *)a0 + 6);
    in[1] = *(u16 *)((u8 *)a0 + 0xA);
    g[0] = D_80126B5E;
    g[1] = D_80126B62;
    func_80183C6C(in, g);
}


extern s32 ratan2(s32 dx, s32 dy);
    s32 func_80183C6C(void * arg0, void * arg1) {
        return ((s32 (*)(s32, s32))ratan2)(
            *(s16 *)((u8 *)arg1 + 0x2) - *(s16 *)((u8 *)arg0 + 0x2),
            *(s16 *)((u8 *)arg1 + 0x0) - *(s16 *)((u8 *)arg0 + 0x0)
        ) - 0x400 & 0xFFF;
    }






extern void func_8012AD80(s32 a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

s32 func_80183CA4(s32 a0) {
    s32 s0 = a0;
    s32 ret;
    s16 sp[7];

    sp[0] = *(u16 *)(s0 + 0x3A);
    sp[1] = *(u16 *)(s0 + 0x3E);
    sp[2] = *(u16 *)(s0 + 0x42);
    func_8012AD80(s0);
    sp[4] = *(u16 *)(s0 + 6);
    sp[5] = *(u16 *)(s0 + 0xA);
    sp[6] = *(u16 *)(s0 + 0xE);
    ret = func_8012CEB0((s32)&sp[0], (s32)&sp[4], 0x11);
    *(u16 *)(s0 + 6) = sp[4];
    *(u16 *)(s0 + 0xA) = sp[5];
    *(u16 *)(s0 + 0xE) = sp[6];
    return ret;
}




extern s32 func_8012C51C(void *a0, s32 a1);

void func_80183D38(void *a0, s16 a1, s32 a2) {
    Local_8017EE34 local;

    local.f0 = *(u16 *)((s32)a0 + 0x06);
    local.f1 = *(u16 *)((s32)a0 + 0x0A);
    local.f2 = *(u16 *)((s32)a0 + 0x0E);
    local.f3 = 0x170;
    local.f4 = a1;
    local.f5 = 0;
    local.f6 = 0x7FFF;
    local.f7 = 0;
    local.f8 = a2;
    func_8012C51C(&local, (s32)a0);
}


#include "common.h"

extern void func_8012EFB8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

typedef struct { s16 vx, vy, vz, pad; } SVec_80183DA0;

void func_80183DA0(s32 a0) {
    SVec_80183DA0 pos;
    SVec_80183DA0 out;
    s32 val;
    s32 sv;
    s16 lvl;

    val = 0x7F;
    lvl = 7;
    pos.vx = *(s16 *)(a0 + 0x6);
    pos.vy = *(s16 *)(a0 + 0xA);
    pos.vz = *(s16 *)(a0 + 0xE);
    ((void (*)(void *, void *))func_8012EFB8)(&pos, &out);

    if (out.vx >= 0 ? out.vx < 0x140 : -out.vx < 0x140) {
        sv = (s16)val;
        if (out.vx >= 0) {
            val = sv - out.vx * 0x7F / 0x140;
        } else {
            val = sv - -out.vx * 0x7F / 0x140;
        }
    } else {
        val = 0;
    }

    lvl += out.vx / 0x14;
    if (lvl < 0) {
        lvl = 0;
    } else if (lvl >= 0x10) {
        lvl = 0xF;
    }
    func_8002D4C8(0x730, (u16)(val | ((lvl << 8) | 0x3000)));
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80183EE8(void) {
        func_8002D4C8(0x4, 0x730);
    }


extern s32 D_801BA5A0;
extern s32 D_801BA5A2;
extern s32 D_801BA5A4;
extern void func_80184604();

void func_80183F0C(void *a0) {
    void *t;
    void *vp;

    *(s16 *)&D_801BA5A0 = 0;
    *(s16 *)&D_801BA5A2 = 0;
    *(s16 *)&D_801BA5A4 = 0;
    t = *(void **)((char *)a0 + 0x78);
    *(s16 *)((char *)a0 + 2) = 3;
    *(s16 *)((char *)a0 + 0x34) = 0;
    *(s32 *)((char *)a0 + 0x1C) = 30;
    *(u16 *)((char *)a0 + 0x5C) = *(u16 *)((char *)t + 2);
    t = *(void **)((char *)a0 + 0x20);
    *(u16 *)((char *)t + 0x1A) = 0x1800;
    *(u16 *)((char *)t + 0x18) = 0x1800;
    vp = *(void **)((char *)a0 + 0x20);
    *(u16 *)((char *)vp + 0x14) = 0;
    *(u16 *)((char *)vp + 0x12) = 0;
    *(u16 *)((char *)vp + 0x10) = 0;
    func_80184604(0);
}


#include "common.h"

/* ---- local layout typedefs (standalone match_one compilation) --------------
 * SVec: {s16 vx,vy,vz,pad;} 8 bytes.
 * Mtx : {s16 m[3][3]; s32 t[3];} 0x20 bytes  (frame 0x50..0x6F).
 * Prim: v[4] @0x00, 8 UV shorts @0x20, bcast @0x30, tag @0x34, code @0x38,
 *       padded to 0x40                       (frame 0x10..0x4F).
 * flag (s32) @0x70.  var_size = 0x40+0x20+8 = 0x68  ->  frame 0x98 w/ 7 saves.
 */
typedef struct { s16 vx, vy, vz, pad; } SVec_80183F84;
typedef struct {
    SVec_80183F84 v[4];                       /* 0x00 */
    s16 u0, t0, u1, t1, u2, t2, u3, t3;       /* 0x20 */
    u32 bcast;                                /* 0x30 */
    s32 tag;                                  /* 0x34 */
    u8  code;                                 /* 0x38 */
    u8  pad39[7];                             /* 0x39 -> 0x40 */
} Prim_80183F84;

extern MATRIX_80188114 D_800AE620;

extern void func_80020DA4(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_80016EF8(void *a0, void *a1);


void func_80183F84(void *a0, void *a1) {
    Prim_80183F84 prim;
    MATRIX_80188114 mtx;
    s32 flag;
    s32 i;
    s16 uL, uR, vT;
    u16 dx, dy;

    if (a1 == 0) {
        return;
    }

    prim.tag = 0x50000000;
    prim.code = 0x74;

    prim.v[0].vx = -0x20; prim.v[0].vy = -0x10;
    prim.v[1].vx =  0x20; prim.v[1].vy = -0x10;
    prim.v[2].vx = -0x20; prim.v[2].vy =  0x10;
    prim.v[3].vx =  0x20; prim.v[3].vy =  0x10;
    prim.v[3].vz = 0;
    prim.v[2].vz = 0;
    prim.v[1].vz = 0;
    prim.v[0].vz = 0;

    dx = *(u16 *)((u8 *)a1 + 4);
    dy = *(u16 *)((u8 *)a1 + 6);

    prim.bcast = 0x808080;

    mtx.t[2] = 0;
    mtx.t[1] = 0;
    mtx.t[0] = 0;

    func_80020DA4((s32)((u8 *)a1 + 8), (s32)&mtx);
    func_80020F34((s32)&mtx, (s32)((u8 *)a1 + 0x10));

    gte_SetRotMatrix(&mtx);
    gte_SetTransMatrix(&mtx);

    for (i = 0; i < 4; i++) {
        RotTransSV(&prim.v[i], &prim.v[i], &flag);
    }

    prim.v[0].vx = prim.v[0].vx + dx;
    prim.v[0].vy = prim.v[0].vy + dy;
    prim.v[1].vx = prim.v[1].vx + dx;
    prim.v[1].vy = prim.v[1].vy + dy;
    prim.v[2].vx = prim.v[2].vx + dx;
    prim.v[2].vy = prim.v[2].vy + dy;
    prim.v[3].vx = prim.v[3].vx + dx;
    prim.v[3].vy = prim.v[3].vy + dy;

    if ((*(s32 *)a1 & 1) == 0) {
        uL = 0xF14; vT = 0x1E0; uR = 0xF53;
    } else {
        uL = 0xF53; vT = 0x1E0; uR = 0xF14;
    }

    prim.u0 = uL; prim.t0 = vT;
    prim.u1 = uR; prim.t1 = vT;
    prim.u2 = uL; prim.t2 = 0x1FF;
    prim.u3 = uR; prim.t3 = 0x1FF;

    if ((*(s32 *)a1 & 2) == 0) {
        func_80016EF8(&prim, (void *)(*(s32 *)((u8 *)a0 + 0x20) + 0x34));
    } else {
        mtx = D_800AE620;
        func_80020F34((s32)&mtx, (s32)(*(s32 *)((u8 *)a0 + 0x20) + 0x18));
        mtx.t[0] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x48);
        mtx.t[1] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x4C);
        mtx.t[2] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x50);
        func_80016EF8(&prim, &mtx);
    }
}


#include "common.h"

/* 8 bytes, align 2 -> the `pos = vec` / `out = vec` assignments become the
 * lwl/lwr/swl/swr movstrsi_internal pair (align != UNITS_PER_WORD). */
typedef struct {
    u16 f0;
    s16 f1;
    u16 f2;
    u16 f3;
} Vec4s16_8018423C;

extern s32 rand(void);
extern u16 D_800B99DA;
extern s32 D_8018E59C[];
extern s32 func_801850D8();
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);

/* Four LOAD-BEARING details, each worth 1-2 instructions (Opus, S70y):
 *
 * 1. `tmp` is DECLARED AND UNUSED ON PURPOSE. The locals region is 0x20..0x3F
 *    (frame 0x58 = 0x20 outgoing args + 0x20 locals + 5 saved regs), i.e. FOUR
 *    8-byte slots, and `out` sits at 0x38 -- so a fourth aggregate must be
 *    declared third to consume 0x30..0x37. expand_decl assigns slots upward
 *    from STARTING_FRAME_OFFSET in declaration order regardless of use.
 *    Deleting `tmp` moves `out` to 0x30 and shrinks the frame to 0x50.
 *
 * 2. `vec.f2 = 0;` BEFORE `vec.f0 = 0;`, and both AFTER `pos.f2`. The two
 *    `sh $zero` are the sched1 filler for the 0xE load-use gap; source order
 *    is what puts 0x2C ahead of 0x28 (§3-T2). The reversed order was the
 *    final 2-instruction residual.
 *
 * 3. `s32 r` with an EXPLICIT (s16) cast on the value, not `s16 r`. A `s16 r`
 *    defers the sll/sra 16 pair to the USE, which lands it after the second
 *    rand() where it coalesces straight into $a1 (-1 instruction). Casting at
 *    the definition puts sll/sra before/in the jal delay slot, keeps the value
 *    in the call-saved $s0 and re-materialises `addu $a1, $s0, $zero`.
 *
 * 4. `k++, step += 0x10` as the for-increment (k FIRST), and `j = i;` as the
 *    last statement of a do/while, not `if (i >= 3) break; j = i;`. The latter
 *    orders the test ahead of the copy, so reorg fills the back-branch delay
 *    slot with `addu $v1,$s0,$zero` instead of duplicating `addiu $s0,$v1,1`
 *    from the loop head (-1 instruction).
 */
void func_8018423C(s32 arg0)
{
    Vec4s16_8018423C pos;
    Vec4s16_8018423C vec;
    Vec4s16_8018423C tmp;
    Vec4s16_8018423C out;
    s32 i;
    s32 j;
    s32 k;
    s32 step;
    s32 r;

    pos.f0 = *(u16 *)(arg0 + 6);
    pos.f1 = *(u16 *)(arg0 + 0xA);
    pos.f2 = *(u16 *)(arg0 + 0xE);
    vec.f2 = 0;
    vec.f0 = 0;

    j = 0;
    do {
        i = j + 1;
        vec.f1 = -(i << 7);
        func_8012F214(arg0, (s32)&vec, (s32)&vec);
        if (func_80135004(1, &pos, (s32)&vec) != 0) {
            if ((D_800B99DA & 7) == 0) {
                step = -0x40;
                out = vec;
                for (k = 0; k < 8; k++, step += 0x10) {
                    out.f0 = vec.f0 + step;
                    r = (s16)(rand() % 0x1000 + 0x2000);
                    func_801850D8(7, r, 0, 0, &out, 0, D_8018E59C[rand() & 1], 0);
                }
            }
            return;
        }
        pos = vec;
        j = i;
    } while (i < 3);
}


extern u8 D_801202A0[];

void func_801843DC(void)
{
    s32 i;
    u8 *p;
    s32 limit;

    i = 0;
    p = D_801202A0;
    limit = 0x170;
    do {
        if (*(u16 *)p == limit) {
            if (*(s16 *)(p + 0x70) & 0x8000) {
                func_8012C218(p);
            }
        }
        i = i + 1;
        p = p + 0x10C;
    } while (i < 0x60);
    return;
}


extern u16 D_8018E7A0[];
extern u16 D_8018E7C0[];
extern s16 D_801BA6B4[];
extern s16 D_801BA6B6[];
extern s16 D_801BA6B8[];

void func_80184458(void) {
    u16 *q = D_8018E7A0;
    u16 *p = D_8018E7C0;
    s32 i;
    s32 off;
    for (i = 0, off = 0; i < 16; i++, off += 6) {
        *(s16 *)((s32)D_801BA6B4 + off) = (p[0] & 0x1F) - (q[0] & 0x1F);
        *(s16 *)((s32)D_801BA6B6 + off) = ((p[0] >> 5) & 0x1F) - ((q[0] >> 5) & 0x1F);
        *(s16 *)((s32)D_801BA6B8 + off) = ((*p++ >> 10) & 0x1F) - ((*q++ >> 10) & 0x1F);
    }
}


extern void func_800599B8(u16 *a0, u16 *a1);
extern u16 D_8018E7A0[];
extern s32 D_8018E7E0;
extern u16 D_801BA714[16];
extern s16 D_801BA6B4[];
extern s16 D_801BA6B6[];
extern s16 D_801BA6B8[];

void func_80184500(s32 arg0) {
    u16 *src;
    u16 *dst;
    u16 pixel;
    s32 i;
    s32 off;
    s32 scale;
    s32 c;
    s32 m0, m1, m2;
    s32 b, g, h;

    dst = D_801BA714;
    src = D_8018E7A0;
    scale = *(s32 *)(arg0 + 0xF4);
    i = 0;
    c = -0x8000;
    off = 0;
    do {
        m0 = *(s16 *)((s32)D_801BA6B4 + off) * scale;
        m1 = *(s16 *)((s32)D_801BA6B6 + off) * scale;
        i = i + 1;
        m2 = *(s16 *)((s32)D_801BA6B8 + off) * scale;
        off = off + 6;
        pixel = *src++;
        b = ((pixel & 0x1F) + (m0 >> 16)) & 0x1F;
        g = (((((pixel << 16) >> 21) & 0x1F) + (m1 >> 16)) & 0x1F);
        h = (((((pixel << 16) >> 26) & 0x1F) + (m2 >> 16)) & 0x1F);
        *dst++ = b | ((h << 10) | (g << 5)) | c;
    } while (i < 0x10);
    func_800599B8(&D_8018E7E0, D_801BA714);
}


extern u8 D_8018E680[];
extern s32 D_801BA6A8;
extern s32 D_801BA6AC;

void func_80184604(s32 arg0) {
    s32 idx;

    if (arg0 != -1) {
        idx = arg0 * 24;
        D_801BA6A8 = (s32)&D_8018E680[idx];
        D_801BA6AC = (s32)&D_8018E680[idx + 24];
    } else {
        D_801BA6A8 = 0;
        D_801BA6AC = 0;
    }
}



extern void (*D_8018E8DC[])(void);

void func_8018465C(void *a0) {
    D_8018E8DC[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80016714(void *a0, s32 a1);
extern u8 D_801BA734[];
extern MATRIX_80188114 D_800AE620;
extern MATRIX_80188114 D_801BC9B4;
extern u16 D_801BC9C4;

void func_80184698(s32 *a0) {
    func_80016714(&D_801BA734, 0x2280);
    D_801BC9B4 = D_800AE620;
    D_801BC9C4 = 0x1000;
    *(u16 *)((u8 *)a0 + 2) += 1;
}


extern u8 D_801BA734[];
extern void (*D_8018E8BC[])(void *);

void func_80184738(void)
{
    u8 *p;
    s32 i;
    u16 idx;

    p = D_801BA734;
    for (i = 0; i < 0x60; i++, p += 0x5C) {
        idx = *(u16 *)p;
        if (idx != 0) {
            D_8018E8BC[idx](p);
        }
    }
}


void func_801847B0(void) {
}

struct vec;
extern void func_80185238(struct vec *a0);
extern void func_80185218(void *arg0);
extern s32  func_80185680(void *a0, void *a1);
extern void func_8018574C(void *a0);
extern void func_80185810(s32 a0);
extern s32 rand(void);

void func_801847B8(void *a0) {
    s32 pad[4];
    u16 state = *(u16 *)((u8 *)a0 + 0x2);

    if (state != 0) {
        s32 cnt = *(s32 *)((u8 *)a0 + 0x1C);
        if (cnt != 0) {
            *(s32 *)((u8 *)a0 + 0x1C) = cnt - 1;
        } else {
            void *s1 = (u8 *)a0 + 0x20;

            if (func_80185680(s1, (u8 *)a0 + 0x48) == 1) {
                if (rand() & 1) {
                    func_8018574C(s1);
                }
                func_80185218(a0);
            } else {
                u16 v0, v1, a1;

                func_80185238((struct vec *)a0);
                v0 = *(u16 *)((u8 *)a0 + 0x6);
                v1 = *(u16 *)((u8 *)a0 + 0xA);
                a1 = *(u16 *)((u8 *)a0 + 0xE);
                *(u16 *)((u8 *)a0 + 0x34) = v0;
                *(u16 *)((u8 *)a0 + 0x36) = v1;
                *(u16 *)((u8 *)a0 + 0x38) = a1;
                func_80185810((s32)s1);
            }
        }
    } else {
        s32 r;
        *(u16 *)((u8 *)a0 + 0x2) = state + 1;
        r = rand();
        *(s32 *)((u8 *)a0 + 0x1C) = r % 4;
    }
}


#include "common.h"

/* Neighbour func_80185238 in this very TU already declares/defines the struct-vec
 * calling convention this function shares (card tu_ref): void func_80185238(struct
 * vec *a0). match_one compiles standalone (no src/shared headers reachable), so we
 * pass the pointer through as void* here -- identical codegen, no dereference
 * happens on our side of the call. The real TU declaration is adopted verbatim at
 * bank time (law 2/8). */
struct vec;
extern void func_80185238(struct vec *a0);
extern void func_80185218(void *arg0);

/* No definition/decl anywhere in the fleet for these three -- derived from the
 * target .s call-site register setup (decl_prior had no "tu" row to adopt). */
extern s32  func_80185680(void *a0, void *a1);
extern void func_80185810(s32 a0);
extern s32 func_80185480();

extern s32 func_80047D3C(s32 a0);
typedef struct { s16 vx, vy, vz, pad; } SVEC_801BA5A8;
extern s32 VectorNormalSS(void *a0, void *a1);
extern SVEC_801BA5A8 D_801BA5A8[];

void func_801848A4(void *a0) {
    void *s1;
    u16 state;

    s1 = (u8 *)a0 + 0x20;
    func_80185680(s1, (u8 *)a0 + 0x48);

    state = *(u16 *)((u8 *)a0 + 0x2);
    switch (state) {
        case 0:
        {
            register s32 v1  __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
            register s32 a0f __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
            s32 a1f;
            s32 cnt;

            func_80185238((struct vec *)a0);
            v1  = *(u16 *)((u8 *)a0 + 0x6);
            a0f = *(u16 *)((u8 *)a0 + 0xA);
            cnt = *(s32 *)((u8 *)a0 + 0x1C) + 1;
            a1f = *(u16 *)((u8 *)a0 + 0xE);
            *(s32 *)((u8 *)a0 + 0x1C) = cnt;
            *(u16 *)((u8 *)a0 + 0x34) = v1;
            *(u16 *)((u8 *)a0 + 0x36) = a0f;
            *(u16 *)((u8 *)a0 + 0x38) = a1f;
            if (cnt >= 0x1E) {
                *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
            }
            break;
        }
        case 1:
        {
            s32 *p = *(s32 **)((u8 *)a0 + 0x40);
            if ((*(s32 *)((u8 *)p + 0xE0) & 1) != 0) {
                u16 t0 = *(u16 *)((u8 *)a0 + 0x34);
                u16 t1 = *(u16 *)((u8 *)a0 + 0x36);
                u16 t2 = *(u16 *)((u8 *)a0 + 0x38);

                *(u16 *)((u8 *)a0 + 0x2) = state + 1;
                *(u16 *)((u8 *)a0 + 0x6) = t0;
                *(u16 *)((u8 *)a0 + 0xA) = t1;
                *(u16 *)((u8 *)a0 + 0xE) = t2;
                *(s32 *)((u8 *)a0 + 0x1C) = 0;
                *(s32 *)((u8 *)a0 + 0x10) = -(*(s32 *)((u8 *)a0 + 0x10));
                *(s32 *)((u8 *)a0 + 0x14) = -(*(s32 *)((u8 *)a0 + 0x14));
                *(s32 *)((u8 *)a0 + 0x18) = -(*(s32 *)((u8 *)a0 + 0x18));
            }
            break;
        }
        case 2:
        {
            register s32 v1  __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
            register s32 a0f __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
            s32 a1f;
            s32 cnt;

            func_80185238((struct vec *)a0);
            v1  = *(u16 *)((u8 *)a0 + 0x6);
            a0f = *(u16 *)((u8 *)a0 + 0xA);
            cnt = *(s32 *)((u8 *)a0 + 0x1C) + 1;
            a1f = *(u16 *)((u8 *)a0 + 0xE);
            *(s32 *)((u8 *)a0 + 0x1C) = cnt;
            *(u16 *)((u8 *)a0 + 0x34) = v1;
            *(u16 *)((u8 *)a0 + 0x36) = a0f;
            *(u16 *)((u8 *)a0 + 0x38) = a1f;
            if (cnt >= 0x1E) {
                func_80185218(a0);
                return;
            }
            break;
        }
    }

    {
        SVEC_801BA5A8 sv;
        s32 idx;
        s32 ret;

        sv.vx = *(u16 *)((u8 *)s1 + 0x14);
        sv.vy = 0;
        sv.vz = *(u16 *)((u8 *)s1 + 0x18);

        idx = *(s16 *)((u8 *)a0 + 0x50);
        ret = VectorNormalSS(&sv, &D_801BA5A8[idx]);
        ret = func_80047D3C(ret);
        *(u16 *)((u8 *)s1 + 0x1A) = ret;
        func_80185480(a0, 0x28);
        func_80185810((s32)s1);
    }
}


#include "common.h"

/* ---------------------------------------------------------------------------
 * func_80184A60  --  MATCH (60/60 ins, relocation-masked).
 *
 * Per-frame update of the "aim" sub-object hanging off *(s0+0x50):
 *   if (owner->flag16 @ +6 == 0)  ->  func_80185218(self) and bail
 *   else                          ->  func_80185680(&self[0x20], &self[0x48]),
 *                                     rebuild the three s16 fields at
 *                                     +0x34/+0x36/+0x38 from
 *                                     mag(+0x54) * (ang(+6)/8) * D_801BA5A8[idx(+0x56)],
 *                                     (>>12, middle component biased -0x40),
 *                                     then func_80185810(&self[0x20]).
 *
 * Declarations (law 2/3):
 *   func_80185218 is DEFINED IN THIS TU at line 3799 -- this extern is its
 *   definition's signature verbatim.  ** BANKING NOTE: func_80184A60 sits at TU
 *   line 3769, BEFORE that definition, so the extern below (or a hoist of the
 *   definition) must survive into the TU. **
 *   func_80185680 / func_80185810 are still INCLUDE_ASM stubs with no TU decl;
 *   the spellings below are the ones that collide least with the sibling drafts
 *   in this wave: `s32 func_80185680(void*, void*)` is func_80184B50.c's decl
 *   verbatim (that draft consumes the return value; this one discards it), and
 *   `void func_80185810(s32)` is the fleet/decl_prior majority (n=5) and
 *   func_80184CA8.c's decl verbatim -- hence the (s32) cast at the call.
 *   The call site here genuinely sets BOTH $a0 and $a1 before the jal, so the
 *   decl_prior single-s32-param row for func_80185680 is a false lead.
 *
 * SVEC_801BA5A8: same NAME and same BODY as the sibling draft func_801848A4.c
 * (§183.1 -- adopting the name without the body is worse than not adopting).
 * ------------------------------------------------------------------------- */
extern void func_80185218(void *arg0);
extern s32  func_80185680(void *a0, void *a1);
extern void func_80185810(s32 a0);


extern SVEC_801BA5A8 D_801BA5A8[];

void func_80184A60(void *arg0) {
    /* PIN 1 (carried from the first-pass draft, §48-A2-shaped): without the $16
     * pin a value crossing the /8 idiom's conditional branch drags in a spurious
     * "move $s2,$s0" plus a phantom 4th callee-saved register. */
    u8 *s0 = (u8 *)arg0;
    u8 *s1;
    void *s2;
    s16 flag;
    s32 ang;
    s32 mag;
    s32 idx;
    s32 scale;
    /* PIN 2 (this pass -- the lever that closed the last 6 diffs).  The three
     * mflo destinations are the product pseudos; gcc gives each of them $v0
     * because $v0 is free in the gap between the `mult` and its `sra`.  The
     * target instead rotates them a3/a3/v1, which only happens once $v0 is
     * LIVE ACROSS the mults -- i.e. once the shifted result is one long-lived
     * value nailed to $v0 rather than three short temps.  greg dump evidence:
     * the product allocnos' conflict sets gain hard reg 2, so global_alloc's
     * plain 0..N scan skips $v0/$v1/$a0/$a1/$a2 and lands on $a3, and takes $v1
     * for the third once `vp` has died.  A `register s32 r;` (no asm) or a
     * plain `s32 r;` reused across all three does NOT do it (still 6 diffs) --
     * the hard-register pin is what forces the conflict. */
    s32 r;
    SVEC_801BA5A8 *vp;

    s1 = *(u8 **)(s0 + 0x50);
    s2 = s0 + 0x20;
    flag = *(s16 *)(s1 + 0x6);          /* +0x6 of the owner record */
    if (flag == 0) {
        func_80185218(s0);
        return;
    }

    func_80185680(s2, s0 + 0x48);

    mag = *(s16 *)(s0 + 0x54);
    /* The /8 written out longhand (bgez + addiu 7 + sra 3) AND scoped to its own
     * temp `t`.  The inner scope is load-bearing: with `ang` itself carrying the
     * rounding, `mag * ang` swapped which of mag/ang got $v0 vs $a0 and the mult
     * still printed backwards (row 25).  Giving the rounding its own pseudo lets
     * the natural source order `mag * ang` emit the target's `mult $v0,$a0`. */
    {
        s32 t = *(s16 *)(s1 + 0x6);
        if (t < 0) t += 7;
        ang = t >> 3;
    }
    idx = *(s16 *)(s0 + 0x56);
    vp = &D_801BA5A8[idx];
    scale = mag * ang;

    do { r = (scale * vp->vx) >> 12; } while (0);
    *(s16 *)(s0 + 0x34) = r;
    r = ((scale * vp->vy) >> 12) - 0x40;
    *(s16 *)(s0 + 0x36) = r;
    r = (scale * vp->vz) >> 12;
    *(s16 *)(s0 + 0x38) = r;
    func_80185810((s32)s2);
}


#include "common.h"

extern void func_80185218(void *arg0);
extern s32  func_80185680(void *a0, void *a1);
extern void func_8018574C(void *a0);
extern s32  func_8018526C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80185810(s32 a0);

void func_80184B50(u8 *param_1)
{
    u8 *s0 = param_1;
    u8 *s1;
    u8 *s2;
    s32 factor;

    s1 = *(u8 **)(s0 + 0x50);
    s2 = s0 + 0x20;

    if (*(s32 *)(*(s32 *)(s0 + 0x40) + 0xE0) & 2) {
        func_80185218(s0);
        return;
    }

    if (func_80185680(s2, s0 + 0x48) == 1) {
        if (rand() & 1) {
            func_8018574C(s2);
        }
    }

    factor = *(s16 *)(s0 + 0x54) * (*(s16 *)(s1 + 0x12) / *(s16 *)(s0 + 0x56));

    *(s16 *)(s2 + 0x14) = *(u16 *)(s1 + 0x4) + ((factor * *(s16 *)(s1 + 0xC)) >> 12);
    *(s16 *)(s2 + 0x16) = *(u16 *)(s1 + 0x6) + ((factor * *(s16 *)(s1 + 0xE)) >> 12);
    *(s16 *)(s2 + 0x18) = *(u16 *)(s1 + 0x8) + ((factor * *(s16 *)(s1 + 0x10)) >> 12);

    func_8018526C((s32)s0, -0x18, 0x18, 0x30);
    func_80185810((s32)s2);
}


#include "common.h"

extern s32 rand(void);
extern s32 func_80185628();
extern void func_80185810(s32 a0);
extern s32  func_80185680(void *a0, void *a1);
extern s32 func_8017E5C8(s32 a0);
extern s32 func_80185380();
extern void func_80185218(void *arg0);

void func_80184CA8(s32 a0) {
    s32 v0;
    s16 *s1;
    s32 s3;
    u16 flag;
    s32 counter;
    /* K&R house style: all locals at the top. gcc-2.7.2 assigns stack slots in
       DECLARATION order (cookbook item 6), so buf[8] must be declared BEFORE
       tmp[4] to land at sp+0x10 with tmp at sp+0x20 -- even though tmp's arm
       runs first at runtime. */
    s16 buf[8];
    s16 tmp[4];
    s32 t;
    s16 u;
    s32 rnd;
    s32 base;
    s32 rem;
    s32 result;

    s3 = a0 + 0x20;                       /* $s3 = a0 + 0x20 */
    v0 = *(s32 *)(a0 + 0x54);
    s1 = *(s16 **)(a0 + 0x50);
    if (v0 == 0) {                        /* target: bnez v0 SKIPS the call */
        v0 = func_80185628(a0 + 0x34, (s32)s1);
        *(s16 *)(a0 + 0x28) = v0;
    }

    flag = *(u16 *)(a0 + 2);
    *(s16 *)(a0 + 0x34) = s1[0];
    *(s16 *)(a0 + 0x36) = s1[1];
    *(s16 *)(a0 + 0x38) = s1[2];

    /* flag != 0 first: writing the arms the other way round flips which side
       falls through and corrupts every branch downstream. */
    if (flag != 0) {
        counter = *(s32 *)(a0 + 0x1C);
        if (counter != 0) {
            *(s32 *)(a0 + 0x1C) = counter - 1;
        } else {
            v0 = func_80185680((void *)s3, (void *)(a0 + 0x48));
            if (v0 == 1) {
                rnd = rand();
                t = *(s16 *)(a0 + 0x2C);
                base = *(s16 *)(a0 + 0x34);
                /* Two levers in ONE zero-byte asm.
                   (1) combine expands sign_extend(lh) into ashift/ashiftrt and
                       merges it with the outer >>7, so the natural spelling
                       always emits lhu+sll,16+sra,23 (3 ins). The re-tie breaks
                       the i2->i3 chain, leaving the target's lh + sra,7 (2 ins).
                   (2) naming `base` as an extra INPUT makes the 0x34 load a
                       predecessor of the fence, so sched1 must place it before
                       the fence -- i.e. into the lh 0x2C load-delay slot, which
                       is exactly where the target has `lh $s1,0x34($s0)`.
                       Without it that slot is a nop and the function is 116 ins. */
                __asm__("" : "=r"(t) : "0"(t), "r"(base));  // !FAKE: launder — REFUSED launder with 2 inputs (P36 rung B tus10)
                rem = rnd % (t >> 7);
                if (rand() & 1) {
                    result = base + rem;
                } else {
                    result = base - rem;
                }
                tmp[0] = result;                                        /* sp+0x20 */
                tmp[1] = *(u16 *)(s3 + 0x16) + *(u16 *)(s3 + 0x1E);     /* sp+0x22 */
                tmp[2] = *(u16 *)(s3 + 0x18);                           /* sp+0x24 */
                func_8017E5C8((s32)tmp);
                func_80185218((void *)a0);
            } else {
                /* `u` MUST be declared s16, not s32 (width dial, cookbook
                   §194-B): the 16-bit local keeps the shift result in $v0 and
                   sends the negation to $v1; an s32 local swaps the pair. */
                u = (s16)(*(u16 *)(a0 + 0x2C)) >> 9;
                buf[2] = -u;                                            /* sp+0x14 */
                buf[3] = u;                                             /* sp+0x16 */
                u = (s16)(*(u16 *)(a0 + 0x2E)) >> 9;
                buf[4] = -u;                                            /* sp+0x18 */
                buf[5] = u;                                             /* sp+0x1A */
                u = (s16)(*(u16 *)(a0 + 0x30)) >> 9;
                buf[6] = -u;                                            /* sp+0x1C */
                buf[7] = u;                                             /* sp+0x1E */
                func_80185380(a0, (s32)&buf[0], 0x30);                  /* a1 = sp+0x10 */
                func_80185810(s3);
            }
        }
    } else {
        *(s16 *)(a0 + 2) = flag + 1;
        *(s32 *)(a0 + 0x1C) = rand() % 4;
    }
}


void func_80184E74(u8 *param_1)
{
    u8 *s0 = param_1;
    u8 *s1;
    u8 *s2;
    s32 b;

    s2 = *(u8 **)(s0 + 0x40);
    if (*(s32 *)(s2 + 0xE0) & 0x10) {
        func_80185218(s0);
        return;
    }
    s1 = s0 + 0x20;

    if (func_80185680(s1, s0 + 0x48) == 1) {
        if (rand() & 1) {
            func_8018574C(s1);
        }
    }

    b = *(s16 *)(s2 + 0x102);
    *(s16 *)(s1 + 0x14) = *(u16 *)(s0 + 0x52) * (b / 10);

    func_8018526C((s32)s0, -0x18, 0x48, 0x30);
    func_80185810((s32)s1);
}


void func_80184F5C(s32 arg0) {
    s32 var_s0 = arg0;
    s32 var_s1 = arg0 + 0x20;

    if (func_80185680((void *) var_s1, (void *) (arg0 + 0x48)) == 1) {
        func_80185218((void *) var_s0);
    } else {
        func_80185810(var_s1);
    }
}


#include "common.h"

/* NOTE: destination TU already `#include "../shared/engine_core.h"`, which pulls in
 * engine_types.h's `typedef struct { s16 h[8]; } Buf;`. Drop this local typedef when
 * merging into the TU (kept here only so this draft compiles standalone). */


extern void func_80049CAC(s32 a0, s32 a1);

void func_80184FBC(s32 param_1, s32 param_2, s32 *param_3)
{
    Buf buf;

    if ((param_1 & 0x1000000) != 0) {
        s32 p;
        s32 w;

        p = param_1 & 0xfeffffff;
        p = p + param_2 * 8;
        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        param_1 = param_1 + param_2 * 0xc;
        buf.h[0] = *(s16 *)(param_1 + 6);
        buf.h[1] = *(s16 *)(param_1 + 8);
        buf.h[2] = *(s16 *)(param_1 + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(param_1 + 0);
        param_3[6] = *(s16 *)(param_1 + 2);
        param_3[7] = *(s16 *)(param_1 + 4);
    }
}


#include "common.h"

typedef struct {
    u16 f0, f1, f2, f3;
} Vec4x16;

extern s32 func_801851E0(void);
extern void func_80185660(s32 *a0, s32 *a1, s32 a2);

s32 func_801850D8(s32 a0, s32 a1, s32 a2, s32 a3, Vec4x16 *a5, s32 a6, s32 a7, s32 a8) {
    s32 obj;

    obj = func_801851E0();
    if (obj == 0) {
        return 0;
    }
    *(s32 *)(obj + 0x20) = 0x50000000;
    *(s16 *)(obj + 0x2E) = a1;
    *(s16 *)(obj + 0x2C) = a1;
    *(s16 *)(obj + 0x30) = 0x1000;
    *(Vec4x16 *)(obj + 0x34) = *a5;
    *(s32 *)(obj + 0x40) = a6;
    *(s16 *)(obj + 0x3C) = a2;
    *(s16 *)(obj + 0x3E) = a3;
    func_80185660((s32 *)(obj + 0x20), (s32 *)(obj + 0x48), a7);
    *(s16 *)(obj + 0x0) = a0;
    *(s32 *)(obj + 0x14) = a8;
    *(s16 *)(obj + 0x6) = a5->f0;
    *(s16 *)(obj + 0xA) = a5->f1;
    *(s16 *)(obj + 0xE) = a5->f2;
    return obj;
}


s32 func_801851E0(void) {

    extern u8 D_801BA734[];
    s32 a0;
    s32 v1;
    v1 = (s32)D_801BA734;
    for (a0 = 0; a0 < 0x60; a0++, v1 += 0x5C) {
        if (*(u16 *)v1 == 0) {
            return v1;
        }
    }
    return 0;
}


extern void func_80016714(void *a0, s32 a1);
    void func_80185218(void *arg0) {
        ((void (*)(s32, s32))func_80016714)((s32)arg0, 0x5C);
    }


void func_80185238(struct vec *a0) {
    a0->unk4 += a0->unk10;
    a0->unk8 += a0->unk14;
    a0->unkC += a0->unk18;
}


#include "common.h"

/* match_one isolation has no -I to src/shared/engine_types.h; on bank, drop these local
   typedefs -- the destination TU already defines SVECTOR/MATRIX via its own
   `#include "../shared/engine_core.h"`. */



extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];

s32 func_8018526C(s32 a0, s32 a1, s32 a2, s32 a3) {
    SVECTOR p1;
    SVECTOR p2;
    SVECTOR b;
    SVECTOR c;
    MATRIX  mtx;
    s32 v2;

    p1.vx = *(u16 *)(a0 + 0x34);
    p1.vy = *(u16 *)(a0 + 0x36) + a1 + *(u16 *)(a0 + 0x3E);
    p1.vz = *(u16 *)(a0 + 0x38);

    p2.vx = *(u16 *)(a0 + 0x34);
    p2.vy = *(u16 *)(a0 + 0x36) + a2 + *(u16 *)(a0 + 0x3E);
    p2.vz = *(u16 *)(a0 + 0x38);

    v2 = a3;

    func_80185FB4(*(s32 *)(*(s32 *)(a0 + 0x40) + 0x20), *(s32 *)(a0 + 0x20), (s32)&mtx);

    func_8012F14C((s32)&mtx, (s32)&p1, (s32)&b);
    func_8012F14C((s32)&mtx, (s32)&p2, (s32)&c);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&b, (s32)&c) != 0) {
        func_8012F568(1, 0x4201, 0, v2, (s32)&c, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


#include "common.h"

typedef struct {
    s16 a, b, c;
} Vec3s16_80185380;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 *D_80126B90;
extern s32  func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern s32  VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_80185380(s32 a0, s16 *a1, s32 a2) {
    Vec3s16_80185380 s;
    Vec3s16_80185380 diff;
    s16 *box0;

    box0 = (s16 *)(((s32)D_80126B90 & 0xFFFFFFF) | 0x80000000);

    s.a = D_80126B5E;
    s.b = D_80126B62;
    s.c = D_80126B66;

    if (func_8013361C(box0, a1, (s16 *)&s, (s16 *)(a0 + 0x34)) != 0) {
        diff.a = s.a - *(u16 *)(a0 + 0x34);
        diff.b = s.b - *(u16 *)(a0 + 0x36);
        diff.c = s.c - *(u16 *)(a0 + 0x38);

        VectorNormalSS(&diff, &diff);

        func_8012F568(1, 0x4201, 0, a2, a0 + 0x34, (s32)&diff);

        return 1;
    }
    return 0;
}


typedef struct { s16 x, y, z, w; } V4_80185480;
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_80185480;

extern void func_80185FB4(s32, s32, s32);
extern void func_8012F14C(s32, s32, s32);
extern s32 func_80135888(s32, s32, s32, s32);
extern void func_8012F568(s32, s32, s32, s32, s32, s32);
extern s32 D_80126B58;
extern u8 D_801152A8[];

s32 func_80185480(void *a0, void *a1)
{
    V4_80185480 va;
    V4_80185480 vb;
    V4_80185480 c;
    V4_80185480 d;
    Mtx32_80185480 mtx;
    u8 *s4p;
    u8 *b58;
    s32 w0;
    s32 w1;
    s32 sum;
    s32 i;

    s4p = (u8 *)a0 + 0x20;

    ((void (*)(s32, void *, void *))func_80185FB4)(*(s32 *)(*(s32 *)((s32)a0 + 0x40) + 0x20),
                  *(s32 *)((s32)a0 + 0x20), &mtx);

    b58 = (u8 *)&D_80126B58;
    w0 = *(s32 *)((s32)a0 + 0x10) << 1;
    w1 = *(s32 *)((s32)a0 + 0x18) << 1;

    va.x = 0;
    vb.x = (*(s16 *)(s4p + 0x14) + *((s16 *)&w0 + 1)) >> 1;
    va.z = 0;
    vb.z = (*(s16 *)(s4p + 0x18) + *((s16 *)&w1 + 1)) >> 1;
    sum = *(u16 *)(s4p + 0x16) + *(u16 *)(s4p + 0x1E) + 0x30;
    vb.y = sum;
    va.y = sum;

    i = 0;
    do {
        func_8012F14C((s32)&mtx, (s32)&va, (s32)&c);
        func_8012F14C((s32)&mtx, (s32)&vb, (s32)&d);
        if (func_80135888(*(s32 *)(b58 + 0x20), *(s32 *)(b58 + 0x38),
                          (s32)&c, (s32)&d) == 0) {
            va = vb;
            vb.x = *(u16 *)(s4p + 0x14) + *((u16 *)&w0 + 1);
            vb.z = *(u16 *)(s4p + 0x18) + *((u16 *)&w1 + 1);
            i++;
        } else {
            func_8012F568(1, 0x4201, 0, (s32)a1, (s32)&d, (s32)D_801152A8);
            return 1;
        }
    } while (i < 2);
    return 0;
}


extern s32 ratan2(s32 a0, s32 a1);

s32 func_80185628(s16 *a0, s16 *a1) {
    s16 ax = a0[1];
    s16 bx = a1[1];
    s16 by = a1[0];
    s16 ay = a0[0];
    return (ratan2(bx - ax, by - ay) + 0x400) & 0xFFF;
}


void func_80185660(s32 *a0, s32 *a1, s32 a2) {
        *(s32 *)((s32)a1 + 0x0) = a2;
        *(s32 *)((s32)a0 + 0x24) = a2;
        *(s16 *)((s32)a1 + 0x4) = 0;
        *(s16 *)((s32)a1 + 0x6) = *(u8 *)a2 & 0x3F;
    }


s32 func_80185680(void *a0, void *a1) {
    s32 frame_pad[1];
    s32 base;
    s16 cnt;
    s32 ret;
    register s32 idx __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    register s32 idc __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus10)
    u8 val;
    (void)&frame_pad;

    cnt = *(s16 *)((u8 *)a1 + 6);
    base = *(s32 *)a1;
    if (cnt == 0) {
        return 1;
    }
    cnt = cnt - 1;
    *(s16 *)((u8 *)a1 + 6) = cnt;
    ret = 0;
    if (cnt <= 0) {
        idx = *(s16 *)((u8 *)a1 + 4);
        val = *(u8 *)(base + idx * 12);
        idc = idx;
        if ((val & 0x40) != 0) {
            *(s16 *)((u8 *)a1 + 6) = 0;
            return 1;
        }
        if ((val & 0x80) != 0) {
            *(s16 *)((u8 *)a1 + 4) = 0;
            ret = 1;
        } else {
            idx = idc + 1;
            *(s16 *)((u8 *)a1 + 4) = idx;
        }
        *(s16 *)((u8 *)a1 + 6) =
            *(u8 *)(base + (*(s16 *)((u8 *)a1 + 4)) * 12) & 0x3F;
        *(s32 *)((u8 *)a0 + 0x24) =
            base + (*(s16 *)((u8 *)a1 + 4)) * 12;
    }
    return ret;
}


extern s32 rand(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8017E5C8(s32 a0);

void func_8018574C(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    s32 rnd;
    s32 t;
    s32 base;
    s32 rem;
    s32 result;
    s16 tmp[3];
    u8 aux[8];

    rnd = rand();
    t = *(s16 *)(s0 + 0xC);
    base = *(s16 *)(s0 + 0x14);
    __asm__("" : "=r"(t) : "0"(t), "r"(base));  // !FAKE: launder — REFUSED launder with 2 inputs (P36 rung B tus10)
    rem = rnd % (t >> 7);
    if (rand() & 1) {
        result = base + rem;
    } else {
        result = base - rem;
    }
    tmp[0] = result;
    tmp[1] = *(u16 *)(s0 + 0x16) + *(u16 *)(s0 + 0x1E);
    tmp[2] = *(u16 *)(s0 + 0x18);
    func_8012F214(*(s32 *)(s0 + 0x20), (s32)tmp, (s32)aux);
    func_8017E5C8((s32)aux);
}




extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);

/* func_80185810 (ov_SC03_105, sub ov_SC03_105_jr_80181C84) -- 489 ins.
 *
 * COMPILER-EMITTED gcc-2.7.2 -O2 C using PsyQ GTE inline-asm macros (splat's
 * "Handwritten function" banner is wrong).  Billboard-sprite drawer: builds the
 * rot/trans matrix (3 paths), RTPS the actor position, rejects it outside
 * +-200/+-160, RTPT the two extent vectors through D_801BC9B4, fills a 0x28-byte
 * POLY_FT4 packet off the D_800A5E60 bump allocator and addPrim()s it into the OT
 * at &D_800A6610[D_800B9A02 << 14] (read base-relative: D_800AF630 + 0xA3D2).
 *
 * BANKED byte-identical, P32 T4b hand pass (S85, 2026-09-06), cookbook §501-P:
 * the S83 Fable draft (DIFF 13 at exact length, five register pins + a zero-byte
 * fence) was replaced by the SPELLING of the banked same-shape cousin
 * ov_SC02_027:func_80180B3C (src/ov_SC02_027/ov_SC02_027_jr_8017D898.c), whose
 * compiled packet window is instruction-for-instruction this target's rows
 * 362-386.  Zero pins, zero fences, zero asm dials.  Load-bearing elements of the
 * ported window, each measured in the real TU (.run/P32/t4d/):
 *  - the v coordinate is masked into a FRESH single-set copy (`vm = cl & 0xFFFF`)
 *    whose consumers live in the two arms of the v0 conditional: the andi survives
 *    combine (a lone insn is never simplified; the lhu has intermediate uses) and,
 *    being single-set, is birthing-boosted -- no anti-dependence starvation, so no
 *    fence is needed and sched2 interleaves it into the tpage/code window itself;
 *  - the branch is spelled `if (!(tpage & 0x10)) vv = vm; else vv = vm - 0x100;`
 *    (the copy arm coalesces away): the opposite polarity re-rolls 42 rows;
 *  - u is a FRESH single-set value from the shifted difference (a 2-set `uu -= ..;
 *    uu <<= ..` re-rolls 63 rows, moving allocations 100 rows away);
 *  - `shift = 2 - mode` is born early and unpinned (the birthing boost sinks it
 *    to its consumer, rows 370/372);
 *  - the OT base is computed right after the packet code byte, before the u/v loads.
 * The P_TAG bitfield OT link and the HI-temp coordinate copy (t20/t22 around the
 * D_801BA6B0 load) are kept from the Fable draft (§500-C, §501-L mechanisms).
 */

#ifndef BFM_ENGINE_TYPES_H
typedef struct { short m[3][3]; long t[3]; } MATRIX_80188114;
#endif

extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);



















void func_80185810(s32 a0)
{
    typedef struct { u16 vx, vy, vz, pad; } UV_85810;
    typedef struct { short m[3][3]; long t[3]; } MTX_85810;
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_85810;

    UV_85810  v[5];        /* sp+0x10 .. sp+0x37 */
    MTX_85810 m;           /* sp+0x38 */
    long sz;               /* sp+0x58 */
    long flag;             /* sp+0x5C */
    long otz;              /* sp+0x60 */
    u8 *base;
    u8 *p;
    u8 *ob;
    u32 ot16;
    PTag_85810 *q;
    u32 flags;
    s32 spr;
    s32 t0;
    s32 sx;
    s32 sy;
    u32 mode;
    u32 w;
    u32 uu;
    u32 cl;
    u32 c40;
    u32 vm;
    u32 vv;
    u32 u;
    s32 shift;
    u32 tp;
    u16 t20;
    u16 t22;

    base  = D_800AF630;
    flags = *(u32 *)a0;
    spr   = *(s32 *)(a0 + 0x24);

    if (*(s32 *)(a0 + 0x20) != 0) {
        if (flags & 0x800000) {
            gte_SetRotMatrix(base + 0x18);
            gte_ldclmv((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x34));
            gte_rtir();
            gte_stclmv(&m.m[0][0]);
            gte_ldclmv((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x36));
            gte_rtir();
            gte_stclmv(&m.m[0][1]);
            gte_ldclmv((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x38));
            gte_rtir();
            gte_stclmv(&m.m[0][2]);
            gte_SetTransMatrix(base + 0x18);
            gte_ldlv0((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x48));
            gte_rtv0tr();
            gte_stlvnl(&m.t[0]);
        } else {
            func_80185FB4(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20), flags, (s32)&m);
            gte_SetRotMatrix(base + 0x18);
            gte_ldclmv(&m.m[0][0]);
            gte_rtir();
            gte_stclmv(&m.m[0][0]);
            gte_ldclmv(&m.m[0][1]);
            gte_rtir();
            gte_stclmv(&m.m[0][1]);
            gte_ldclmv(&m.m[0][2]);
            gte_rtir();
            gte_stclmv(&m.m[0][2]);
            gte_SetTransMatrix(base + 0x18);
            gte_ldlv0(&m.t[0]);
            gte_rtv0tr();
            gte_stlvnl(&m.t[0]);
        }
        gte_SetRotMatrix(&m);
        gte_SetTransMatrix(&m);
        t0 = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x10;
    } else {
        gte_SetRotMatrix(base + 0x18);
        gte_SetTransMatrix(base + 0x18);
        t0 = a0 + 4;
    }

    gte_ldv0((u8 *)(a0 + 0x14));
    gte_rtps();
    gte_stsxy(&v[0]);
    gte_stsz(&sz);

    sx = *(s16 *)&v[0].vx;
    if (sx < 0) sx = -sx;
    if (sx >= 0xC9) return;
    sy = *(s16 *)&v[0].vy;
    if (sy < 0) sy = -sy;
    if (sy >= 0xA1) return;

    *(u16 *)&D_801BC9B4 = *(u16 *)(a0 + 0xC);
    *(u16 *)((u8 *)&D_801BC9B4 + 8) = *(u16 *)(a0 + 0xE);
    gte_SetRotMatrix(&D_801BC9B4);
    gte_SetTransMatrix(&D_801BC9B4);

    v[3].vx = *(u16 *)(spr + 8) + *(u16 *)(a0 + 0x1C);
    v[3].vy = *(u16 *)(spr + 0xA) + *(u16 *)(a0 + 0x1E);
    v[3].vz = sz;
    v[4].vx = *(u8 *)(spr + 2);
    v[4].vy = *(u8 *)(spr + 3);
    v[4].vz = sz;

    gte_ldv3(&v[3], &v[4], &v[4]);
    gte_rtpt();
    gte_stsxy0(&v[1]);
    gte_stsxy1(&v[2]);
    gte_stflg(&flag);
    gte_stszotz(&otz);
    if (flag & ~0x1000) return;

    /* ---- the packet-fill window: the cousin's spelling (func_80180B3C) ---- */
    mode = (flags >> 24) & 3;
    shift = 2 - mode;
    p = D_800A5E60;
    D_800A5E60 = p + 0x28;
    w = mode << 7;
    p[3] = 9;
    p[7] = 0x2C;
    ot16 = *(u16 *)(base + 0xA3D2);
    ob = &D_800A6610[ot16 << 14];
    uu = *(u16 *)(spr + 4);
    cl = *(u16 *)(spr + 6);
    p[7] |= 2;
    *(u16 *)(p + 0x16) = w | ((flags >> 23) & 0x60) | ((cl & 0x100) >> 4)
                           | ((uu & 0x3C0) >> 6) | ((cl & 0x200) << 2);
    c40 = (flags & 0x40) >> 6;
    p[7] |= c40;
    vm = cl & 0xFFFF;
    u = (uu - ((*(u16 *)(p + 0x16) & 0xF) << 6)) << shift;
    p[0xC] = u;
    if (!(*(u16 *)(p + 0x16) & 0x10)) {
        vv = vm;
    } else {
        vv = vm - 0x100;
    }
    p[0xD] = vv;
    /* ---- end of the ported window ---- */

    p[0x14] = p[0xC] + *(u8 *)(spr + 2) - 1;
    p[0x15] = p[0xD];
    p[0x1C] = p[0xC];
    p[0x1D] = p[0xD] + *(u8 *)(spr + 3) - 1;
    p[6] = 0x80;
    p[5] = 0x80;
    p[4] = 0x80;
    p[0x24] = p[0x14];
    p[0x25] = p[0x1D];

    *(u16 *)(p + 8)    = v[0].vx + v[1].vx;
    *(u16 *)(p + 0xA)  = v[0].vy + v[1].vy;
    *(u16 *)(p + 0x10) = *(u16 *)(p + 8) + v[2].vx;
    *(u16 *)(p + 0x1A) = *(u16 *)(p + 0xA) + v[2].vy;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0xA);
    *(u16 *)(p + 0x18) = *(u16 *)(p + 8);
    t20 = *(u16 *)(p + 0x10);
    t22 = *(u16 *)(p + 0x1A);
    tp = D_801BA6B0;
    *(u16 *)(p + 0x20) = t20;
    *(u16 *)(p + 0x22) = t22;

    if (tp == 0) {
        u32 t2 = *(u8 *)(spr + 1);
        u32 tb = (t2 + 0x100) << 6;
        if (t2 < 0xE0) *(u16 *)(p + 0xE) = tb | 0x16;
        else           *(u16 *)(p + 0xE) = tb | 0x10;
    } else {
        u32 tb = (tp + 0x100) << 6;
        { u32 vx; if (tp < 0xE0) vx = tb | 0x16; else vx = tb | 0x10; *(u16 *)(p + 0xE) = vx; }
    }

    if ((flags & 0x300000) == 0x200000) {
        func_8001F730(t0, &v[0], p);
    }

    q = (PTag_85810 *)((otz << 2) + (u32)ob);
    ((PTag_85810 *)p)->addr = q[1].addr;
    q[1].addr = (u32)p;
}





void func_80185FB4(s32 a0, s32 a1, s32 a2)
{
    extern MATRIX_80188114 D_800AE620;
    extern void func_80020DA4(s32 a0, s32 a1);
    extern void func_80020F34(s32 a0, s32 a1);

    if (a1 & 0x200000) {
        func_80020DA4(a0 + 0x10, a2);
    } else {
        *(MATRIX_80188114 *)a2 = D_800AE620;
    }

    if (a1 & 0x400000) {
        func_80020F34(a2, a0 + 0x18);
    }

    *(s32 *)(a2 + 0x14) = *(s16 *)(a0 + 0x8);
    *(s32 *)(a2 + 0x18) = *(s16 *)(a0 + 0xA);
    *(s32 *)(a2 + 0x1C) = *(s16 *)(a0 + 0xC);
}



extern void (*D_8018F114[])(void);

void func_80186094(void *a0) {
    D_8018F114[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8013373C(s16 arg0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern void func_80188BA8(s32 a0);

extern s32 D_8019CD2C;
extern s32 D_8018E9AC;
extern s32 D_8018EAB4;
extern s32 D_801BCBBC;
extern s16 D_8018EE04;
extern s16 D_8018EE02;
extern s16 D_8018EE00;

void func_801860D0(int param_1)
{
    s32 v1;
    s32 v0;
    u16 flags;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
        return;
    }
    func_8001C214(v0, (s32)&D_8019CD2C);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x7FFF, 0x7FFF);
    *(u16 *)(param_1 + 0x2) = 1;
    if ((u32)func_80029504() < 0x258u) {
        func_8013373C(0);
        func_8012A828(param_1, &D_8018E9AC);
        *(s32 *)(param_1 + 0x6C) = func_8012C588(0x1DE, param_1);
        func_8012C588(0x14D, param_1);
        v1 = *(s32 *)(param_1 + 0x20);
        flags = *(u16 *)(v1 + 0x2C);
        D_801BCBBC = 0;
        *(u16 *)(v1 + 0x2C) = flags | 0x80;
        v1 = *(s32 *)(param_1 + 0x20);
        *(s32 *)(v1 + 0x80) = (s32)&D_8018EE04;
        D_8018EE02 = 0xF0;
        D_8018EE00 = 0xF0;
    } else {
        func_8012A828(param_1, &D_8018EAB4);
        func_80188BA8(param_1);
    }
}


extern s32 func_80029504(void);
extern s32 func_8016F1AC(void);
extern void func_8014704C(s32 *a0);
extern s32 func_80178B18(s32, s32);
extern s32 D_80126B58;
extern void (*D_8018EEB4[])(void);

void func_801861DC(void *a0)
{
    if ((u32)func_80029504() < 0x258u) {
        *(u16 *)((s32)a0 + 2) = 2;
        func_80178B18((s32)a0, (s32)D_8018EEB4);
    } else if (func_8016F1AC() == 0) {
        *(u16 *)((s32)a0 + 2) = 10;
        func_8014704C(&D_80126B58);
    }
}



