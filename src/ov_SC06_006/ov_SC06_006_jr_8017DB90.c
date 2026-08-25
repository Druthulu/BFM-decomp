#include "common.h"
#include "../shared/engine_core.h"


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
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_8017D278;   /* 0x20; .t @ +0x14 */
typedef struct { s16 vx, vy, vz, pad; } Sv_8017D278;      /* 0x08 */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_801842E4;
extern u8 D_80184254;
extern u8 D_80184230;
extern u8 D_8018420C;
extern u8 D_801842C0;
extern u8 D_8018429C;
extern u8 D_80184278;
extern u8 D_801841E8;
extern void func_80145934(void);
extern u8 D_80184374;
extern u8 D_80184350;
extern u8 D_8018432C;
extern u8 D_80184308;
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
extern unsigned char D_8018376C[];
extern unsigned char D_8018379C[];
extern unsigned char D_801837EC[];
extern unsigned char D_8018381C[];
extern unsigned char D_8018384C[];
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
extern void (*D_8018389C[])(void *);
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
extern s32 D_80183964[];
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
extern u8 D_801839EC[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801839F4;
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
extern int D_801F6EC8;
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
extern s32 D_801F6ECC;
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
extern s32 D_80183A24;
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
extern void (*D_80183ACC[])(void);
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
extern void (*D_80183AF0[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80183AE0;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80183B04[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80183B10[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80183B20[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80183B38[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80183B28;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80183B4C[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80183B68[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80183B58;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80183B7C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80183B90[])(void);
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
extern s32 D_80183BA4;
extern void (*D_80183BCC[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80183BAC;
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
extern int (*D_80183C18[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80183C1C[])(void);
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
extern unsigned short D_80184080[];
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
extern void (*D_80184090[])(void);
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
extern int D_801F6F00;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801840B8[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80184098;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801840A8;
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
extern void (*D_801840F8[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80184100[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801840CC;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018410C[])(void);
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
extern u8 D_801840DC;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801F6F08;
extern s32 D_801F6F14;
extern s32 D_801F6F18;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80184148[])(s32 *);
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
extern s32 D_8018411C[];
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
extern s32 D_801F6F10;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80184398[])(void);
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
extern char D_801841B8[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018443C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80184590[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_801843AC;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80184598[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_801843BC;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_801843DC;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_801845A0[])(void);
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
extern void (*D_801845C8[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_801845D4[])(void);
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
extern void (*D_80184448[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80184678;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018375C[];
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
extern unsigned char D_8018468C[];
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
extern s8 D_801846C8[];
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
extern u16 D_80184710;
extern u16 D_80184712;
extern u16 D_80184714;
extern s32 D_80184718;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80184720;
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
extern int D_8018442C;
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
extern unsigned int D_801847A4[];
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
extern void (*D_80184854[])(void);
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
extern u16 D_80184884[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_801848E8;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801F6F20[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018490C[])(void);
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
extern int D_801F6F78[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80184954[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80184944;
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
extern char D_801F6698[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018495C[])(void);
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
extern void (*D_801849B0[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80184978;
extern s16 D_801849AC;
extern s16 D_801849AA;
extern s16 D_801849A8;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801849BC[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801F6FD8;
extern u8 D_801F6FD9;
extern u8 D_801F6FDA;
extern u8 D_801F6FDB;
extern u8 D_801F6FDC;
extern u8 D_801F6FDD;
extern u8 D_801F6FDE;
extern u8 D_801F6FDF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801849CC[])(void);
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
extern s32 D_801F7018;
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
extern void (*D_80184A10[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80184A8C[];
extern s32 D_80184AAC[];
extern u8 D_80184B28[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80184B48[];
extern u8 D_80184B68[];
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
extern void (*D_80184C04[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80184C80[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801F66A8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80184C8C[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80184C94[])(void);
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
extern void (*D_80184D5C[])(void);
extern void func_80166618(void *a0);
extern void (*D_80184D6C[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80184D7C[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80184D88[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80184CE8[];
extern u8   D_80184CFC[];
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
extern void (*D_80184DA0[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80184DA8[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80184DB0[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80184DB8[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80184DC0[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80184DC8[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80184DD0[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80184E84[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80184E8C[])(void);
extern void func_80169F00(void *a0);
extern char D_80184E3C[];
extern char D_80184DFC[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80184EC4[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80184ED0[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80184F18[])(void);
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
extern void (*D_80184F94[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801F7338;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80184F88[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80184FCC[];
extern unsigned short D_80184FD4[];
extern unsigned short D_80184FDC[];
extern unsigned char D_801F7340[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801F7338;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80184FE4[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801F7474;
extern M2C_UNK D_801F7478;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801F7400;
extern void (*D_80185014[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801F747C[];
extern u8 D_801F7484[];
extern u8 D_801F7434[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018501C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80185038[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80185040[])(void);
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
extern void (*D_801850A8[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018504C;
extern u8 D_80185058;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_801850DC[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_801850E4[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80185138[])(void);
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
extern u16 D_8018516C[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018515C[];
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
extern s32 D_80185188;
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
extern void (*D_80185200[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80185208[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80185210[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80185218[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80185220[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80185228[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80185234[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80185240[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018524C[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018525C[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018526C[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80185274[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018527C[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80185284[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018528C[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80185294[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018529C[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_801852A4[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_801852AC[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_801852B4[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_801852BC[])(void);
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
extern void (*D_801852C4[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801852CC[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_801852D4[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_801852DC[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_801852E4[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_801852EC[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801852F4[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801852FC[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80185304[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018530C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80185314[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018531C[])(void);
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
extern void (*D_80185360[])(void);
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
extern M2C_UNK D_80185324;
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
extern void (*D_80185390[])(void);
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
extern void (*D_801853CC[])(void);
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
extern void (*D_80185424[])();
extern void func_80174BF4(void * arg0);
extern s32 func_80174CB0(s32, s32);
extern s32 func_80174C60(s32 a0);
extern void func_80174C80(s32 a0);
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
extern void (*D_80185434[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018543C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_801855A4[])();
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
extern void (*D_801855B0[])();
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
extern M2C_UNK D_801F68F0;
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
extern s16 D_801F8AF4;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801F7BB8;
extern short D_801F8B64;
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
extern s32 D_801F7FE4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801F800C;
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
extern s16 D_801F7FC8;
extern s32 func_8017A3B0(void);
extern short D_801F8004;
extern short D_801F8000;
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
extern s16 D_801F7FCC;
extern u16 D_801F804C;
extern u16 D_801F804E;
extern u16 D_801F8050;
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
extern s16 D_801F8044;
extern s16 D_801F8046;
extern s16 D_801F8048;
extern s16 D_801F803C;
extern s16 D_801F803E;
extern s16 D_801F8040;
extern void func_8017B7A8(void);
extern s16 D_801F805C;
extern s16 D_801F805E;
extern s16 D_801F8060;
extern s16 D_801F8064;
extern s16 D_801F8066;
extern s16 D_801F8068;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801F8054;
extern short D_801F8056;
extern short D_801F8058;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801F7FEC;
extern SV4 D_801F7FF4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801F8014[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801F8010)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018578C[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void (*D_801857E8[])(void);
extern void func_8017CD9C(void *a0);
extern void func_8017D0AC(void);
extern s32 func_8017CDD8(s32 a0);
extern s32 func_8017CE1C(void);
extern void (*D_801857F0[])(void);
extern void func_8017CE40(void *a0);
extern s32 D_80126B58;
extern s32 func_801472C8();
extern s32 func_8017CE7C(void *a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017CEE0(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017CF5C(void);
extern void (*D_80185804[])(void);
extern void func_8017CF7C(void *a0);
extern s32 D_801F8070;
extern void func_8017CFB8(void *arg0);
extern s32 D_800D5F14;
extern void func_8017D000(u8 *arg0);
extern s32 D_800D5FD4;
extern void func_8017D04C(s32 arg0);
extern void func_8017D0D4(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D19C(void *a0);
extern void func_8017D0FC(void);
extern void (*D_80185810[])(void);
extern void func_8017D278(s32 param_1, s16 *param_2);
extern void func_8017D1D8(s32 a0);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);         /* src TU:204 */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);        /* src TU:329 */
extern void func_80049CAC(s32 a0, s32 a1);                /* src TU:2651 */
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 D_801F8AEC;
extern void func_8017D400(void);
extern s32 func_8017D420(void);
extern void func_801800B8(void *a0);
extern void func_8017D4C0(s16 *a0);
extern s32 D_80185AD8;
extern void func_8017D4F0(u8 *a0);
extern s32 D_80185B2C;
extern void func_8017D528(s16 *a0);
extern void (*D_80185B60)(void *);
extern s16 D_801F8094;
extern void func_8017D558(u8 *a0);
extern void func_8017D5A0(s16 *param);
extern void func_8017D5D0(s16 *a0);
extern void func_8017D04C(s32 a0);
extern s16 D_80185BEC;
extern void func_8017D600(u8 *a0);
extern u8 D_80185C18;
extern void func_8017D650(u8 *a0);
extern void (*D_80185C64)(void *);
extern void func_8017D688(u8 *a0);
extern s16 D_80185C98;
extern void func_8017D6D0(s16 *a0);
extern void func_8017D700(s16 *a0);
extern s32 func_8018034C(void);
extern void func_8017F7C4(s32 arg0);
extern void func_8017FECC(s32 a0);
extern s32 D_80185AFC;
extern s32 D_801F8084;
extern s32 D_80185CF8;
extern s32 D_80185CFC;
extern s32 D_80185D00;
extern s32 D_80185D04;
extern void func_8017D730(void);
extern s32 D_80185D28;
extern void func_8017D90C(u8 *a0);
extern void func_8017D944(s16 *param);
extern u8 D_80185DE8[];
extern void func_8017F2A0(void);
extern void func_8017D974(u8 *a0);
extern s32 D_80185E14;
extern void func_801800B8(void*);
extern void func_8017D9AC(u8 *a0);
extern void (*D_80185E90[])(void *);
extern void func_8017F5D0(void);
extern void func_8017F3E8(void);
extern void func_8017F8CC(void);
extern s32 D_801F8080;
extern s32 D_801F8088;
extern s16 D_801F80A8;
extern s32 func_80014C54(s32 a0, s32 a1, s32 a2);
extern s32 D_801857BC;
extern void func_801379D8(void);
extern void func_8017DA8C(void *param_1);
/* ==== end §8b carried decl layer ==== */


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 D_80185EDC[];

void func_8017DB90(s32 d)
{
    s32 obj;

    *(s32 *)(d + 0x20) = obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
        return;
    }

    switch ((s16)(*(u16 *)(d + 0x70) - 1)) {
    case 6:
    case 14:
        func_8001C810(*(s32 *)(d + 0x20), D_80185EDC[*(s16 *)(d + 0x70)]);
        *(s32 *)(*(s32 *)(d + 0x20) + 4) |= 0x40000000;
        break;

    case 2:
        func_8001C810(*(s32 *)(d + 0x20), D_80185EDC[*(s16 *)(d + 0x70)]);
        *(s32 *)(*(s32 *)(d + 0x20) + 4) |= 0x8000;
        break;

    case 0:
    case 4:
        func_8001C214(*(s32 *)(d + 0x20), D_80185EDC[*(s16 *)(d + 0x70)]);
        *(s32 *)(*(s32 *)(d + 0x20) + 4) |= 0x40;
        break;

    default:
        func_8001C214(*(s32 *)(d + 0x20), D_80185EDC[*(s16 *)(d + 0x70)]);
        break;
    }

    func_8001D0E8(*(s32 *)(d + 0x20), 0x7FFF, 0x7FFF);
    *(u16 *)(*(s32 *)(d + 0x20) + 0x2C) |= 0x10;
    *(s32 *)(d + 0xDC) = 0x1000;
    *(s16 *)(d + 0x34) = 0;
    *(s32 *)(d + 4) = 0;
    *(s32 *)(d + 8) = 0;
    *(s32 *)(d + 0xC) = 0;
    *(u16 *)(d + 2) += 1;
}



extern void (*D_80185F58[])(void);

void func_8017DD28(void *a0) {
    D_80185F58[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_8017DD64 — per-bone animation sampler.
 *
 *   obj + 0x20  s32   pointer to a sibling record whose +0x20 word is retargeted
 *   obj + 0x90  ptr   -> array of 8-byte track records (Rec8)
 *   obj + 0x94  s32   "animation finished" counter (bumped only on the interp path)
 *   obj + 0x98  s16   flag cleared on both paths
 *   obj + 0x9A  s16   bone count (n)
 *   obj + 0x9C  ptr   -> output array of 12-byte keys (Key12)
 *   obj + 0xFC  s16   number of key frames
 *
 *   D_801F8088 is the global animation clock; dividing it by the track's
 *   own +0x4 halfword yields the frame index (quot) and the sub-frame
 *   remainder (rem) used as the lerp numerator.
 */

/* 12 bytes, align 2 -> struct copies come out as lwl/lwr + swl/swr triples */
typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
} Key12_8017DD64;

/* 8-byte stride track record */
typedef struct {
    void *f0;
    s16   f4;
    s16   f6;
} Rec8_8017DD64;

extern s32 D_801F8088;
extern void func_8017E078();  /* (Key12_8017DD64 *dst, void *src, s32 idx) — unspecified list keeps this compatible with any slate-mate prototype */
extern s32 func_8017DFA4();
extern s32 func_8017DFEC();

void func_8017DD64(void *obj) {
    Key12_8017DD64 sp10;
    Key12_8017DD64 sp20;
    Rec8_8017DD64 *base;
    Rec8_8017DD64 *rec;
    Rec8_8017DD64 *rec2;
    Key12_8017DD64 *out;
    s32 quot;
    s32 rem;
    s32 den;
    s32 n;
    s32 i;

    base = *(Rec8_8017DD64 **)((u8 *)obj + 0x90);
    den = base->f4;
    quot = D_801F8088 / den;
    rem = D_801F8088 % den;
    out = *(Key12_8017DD64 **)((u8 *)obj + 0x9C);
    n = *(s16 *)((u8 *)obj + 0x9A);

    if (quot >= *(s16 *)((u8 *)obj + 0xFC) - 1) {
        *(s16 *)((u8 *)obj + 0x98) = 0;
        rec = &(*(Rec8_8017DD64 **)((u8 *)obj + 0x90))[*(s16 *)((u8 *)obj + 0xFC) - 1];
        for (i = 0; i < n; i++) {
            func_8017E078(&sp10, rec->f0, i);
            *out = sp10;
            out++;
        }
        *(s16 *)((u8 *)obj + 0x98) = 0;
        *(s32 *)(*(s32 *)((u8 *)obj + 0x20) + 0x20) =
            *(s32 *)((u8 *)obj + 0x9C);
    } else {
        rec = &base[quot];
        rec2 = rec + 1;
        for (i = 0; i < n; i++) {
            func_8017E078(&sp10, rec->f0, i);
            func_8017E078(&sp20, rec2->f0, i);
            out->f0 = func_8017DFA4(sp10.f0, sp20.f0, den, rem);
            out->f2 = func_8017DFA4(sp10.f2, sp20.f2, den, rem);
            out->f4 = func_8017DFA4(sp10.f4, sp20.f4, den, rem);
            out->f6 = func_8017DFEC(sp10.f6, sp20.f6, den, rem);
            out->f8 = func_8017DFEC(sp10.f8, sp20.f8, den, rem);
            out->fA = func_8017DFEC(sp10.fA, sp20.fA, den, rem);
            out++;
        }
        *(s16 *)((u8 *)obj + 0x98) = 0;
        *(s32 *)(*(s32 *)((u8 *)obj + 0x20) + 0x20) =
            *(s32 *)((u8 *)obj + 0x9C);
        (*(s32 *)((u8 *)obj + 0x94))++;
    }
}


s32 func_8017DFA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return (arg1 - arg0) * arg3 / arg2 + arg0;
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017DFEC);

INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017E078);

extern s32 D_801F80C8;
extern s32 D_801F8084;
extern u16 D_801F83A4[][6];
extern s16 D_801B9830[];
extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);

void func_8017E168(s32 a0) {
    void *p;
    u8 *ap;
    s32 j;
    s16 *r;

    ap = (u8 *)a0;
    p = (*(void * *)&D_801F80C8);
    if (p == NULL) {
        return;
    }

    j = D_801F8084;

    if ((*(u16 *)((u8 *)p + 2) == 1) && (*(u16 *)((u8 *)p + 0x34) == 1)) {
        func_8012E88C(ap);
        *(u16 *)(ap + 0x98) = 0;

        *(u16 *)(ap + 6) = D_801F83A4[*(s16 *)(ap + 0x70)][0];
        *(u16 *)(ap + 0xA) = D_801F83A4[*(s16 *)(ap + 0x70)][1];
        *(u16 *)(ap + 0xE) = D_801F83A4[*(s16 *)(ap + 0x70)][2];

        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x10) = D_801F83A4[*(s16 *)(ap + 0x70)][3];
        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x12) = D_801F83A4[*(s16 *)(ap + 0x70)][4];
        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x14) = D_801F83A4[*(s16 *)(ap + 0x70)][5];

        if (*(s16 *)(ap + 0xDC) <= j) {
            j = *(s16 *)(ap + 0xDC) - 1;
        }

        r = &D_801B9830[j * 15 + *(s16 *)(ap + 0x70) * 3];
        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x18) = *(u16 *)r;
        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x1A) = *(u16 *)(r + 1);
        *(u16 *)((u8 *)*(void **)(ap + 0x20) + 0x1C) = *(u16 *)(r + 2);
    } else {
        func_8012E8A8(ap);
        *(u16 *)(ap + 0x98) = 0;
    }
}


#include "common.h"

/* func_8017E330 (ov_SC06_006 @ 0x8017E330) — drives an actor from the global
 * "driver" entry D_801F80E4: pushes a scaled pose vector out of the 12-byte
 * pose table D_801F8428[] and mirrors the driver's rotation onto the actor's
 * coordinate record.
 *
 * All local types are uniquely suffixed; the destination TU
 * (src/ov_SC06_006/ov_SC06_006_jr_8017BEBC.c) declares none of these symbols. */

/* 8 bytes, align 2 -> the +0x18 rotation copy emits lwl/lwr + swl/swr */
typedef struct {
    s16 x, y, z, pad;
} Rot_8017E330;

/* the coordinate/model record hung off +0x20 of both the actor and the driver */
typedef struct {
    u8            pad00[0x10];
    u16           f10;          /* 0x10 */
    u16           f12;          /* 0x12 */
    u16           f14;          /* 0x14 */
    u8            pad16[0x02];
    Rot_8017E330  rot;          /* 0x18 */
    s32           align;        /* keeps align 4 so the +0x20 pointer loads with lw */
} Coord_8017E330;

typedef struct {
    u8              pad00[0x06];
    s16             f06;        /* 0x06 */
    u8              pad08[0x02];
    s16             f0A;        /* 0x0A */
    u8              pad0C[0x02];
    s16             f0E;        /* 0x0E */
    u8              pad10[0x10];
    Coord_8017E330 *f20;        /* 0x20 */
    u8              pad24[0x4C];
    u8              f70;        /* 0x70 — pose index */
    u8              pad71[0x27];
    s16             f98;        /* 0x98 */
    u8              pad9A[0x42];
    s32             fDC;        /* 0xDC */
} Actor_8017E330;

typedef struct {
    u8              pad00[0x02];
    u16             f02;        /* 0x02 */
    u8              pad04[0x1C];
    Coord_8017E330 *f20;        /* 0x20 */
    u8              pad24[0x10];
    u16             f34;        /* 0x34 */
} Drv_8017E330;

/* 12-byte stride pose table based at D_801F8428.
 * +0/+2/+4 are read signed (lh, they feed a mult); +6/+8/+A are plain HI moves
 * (D_801F842E / D_801F8430 / D_801F8432). */
typedef struct {
    s16 x, y, z;                /* D_801F8428 / D_801F842A / D_801F842C */
    u16 a, b, c;                /* D_801F842E / D_801F8430 / D_801F8432 */
} Pose_8017E330;

/* 16 bytes: the frame's var region is 0x10..0x1F (only x/y/z are ever touched) */
typedef struct { s16 x, y, z; s16 pad[5]; } Work_8017E330;

extern void *D_801F80E4;
extern s32   D_801F8090;
extern void *D_801F8118;
extern Pose_8017E330 D_801F8428[];

extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8017F824();

void func_8017E330(Actor_8017E330 *a0) {
    Work_8017E330 v;            /* sp+0x10 */
    Drv_8017E330 *p;
    s32 i;
    s32 t;

    p = (Drv_8017E330 *)D_801F80E4;
    if (p == NULL) {
        return;
    }

    a0->fDC = 0x200;
    i = a0->f70;

    if ((p->f02 == 1) && (p->f34 == 1)) {
        func_8012E88C((u8 *)a0);
        a0->f98 = 0;

        v.x = (D_801F8428[i].x * D_801F8090) >> 12;
        v.y = (D_801F8428[i].y * D_801F8090) >> 12;
        v.z = (D_801F8428[i].z * D_801F8090) >> 12;

        if (*(u16 *)((u8 *)D_801F8118 + 2) == 2) {
            func_8017F824(&v, 0x200);
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            /* The target keeps `lh` + `sra 3` (the UNCOMBINED extendhisi2_internal
             * form).  At -O2 mips.md's extendhisi2 expander does
             *   `if (optimize && MEM) force_not_mem`, so expand always emits
             * lhu + sll 16 + sra 16, and combine folds that back to a
             * `(sign_extend (mem))` == `lh` only to immediately re-fold it with
             * the `>> 3` into `sll 16 ; sra 19` (3 insns).  Blocking that LAST
             * merge is what the target did: can_combine_p bails when i2 and i3
             * are non-adjacent AND memory was written between them
             * (combine.c use_crosses_set_p -> `mem_last_set > from_cuid`).
             * The split load/shift statements give the non-adjacency (the
             * `lw 0x20($s0)` sits between them); the zero-byte re-tie with a
             * "memory" clobber supplies the write.  Byte-exact, emits nothing. */
            t = p->f20->rot.x;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.x = t >> 3;
            t = p->f20->rot.y;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.y = t >> 3;
            t = p->f20->rot.z;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.z = t >> 3;
        } else {
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            a0->f20->rot = p->f20->rot;   /* 8-byte align-2 copy: lwl/lwr + swl/swr */
        }

        a0->f20->f10 = D_801F8428[i].a;
        a0->f20->f12 = D_801F8428[i].b;
        a0->f20->f14 = D_801F8428[i].c;
    } else {
        func_8012E8A8((u8 *)a0);
        a0->f98 = 0;
    }
}


typedef struct {
    s16 x, y, z, pad;
} Rot_8017E550;

typedef struct {
    u8            pad00[0x10];
    u16           f10;
    u16           f12;
    u16           f14;
    u8            pad16[0x02];
    Rot_8017E550  rot;
    s32           align;
} Coord_8017E550;

typedef struct {
    u8              pad00[0x06];
    s16             f06;
    u8              pad08[0x02];
    s16             f0A;
    u8              pad0C[0x02];
    s16             f0E;
    u8              pad10[0x10];
    Coord_8017E550 *f20;
    u8              pad24[0x40];
    s32             f64;
    u8              pad68[0x08];
    u8              f70;
    u8              pad71[0x27];
    s16             f98;
} Actor_8017E550;

typedef struct {
    u8              pad00[0x02];
    u16             f02;
    u8              pad04[0x1C];
    Coord_8017E550 *f20;
    u8              pad24[0x10];
    u16             f34;
} Drv_8017E550;

typedef struct {
    s16 x, y, z;
    u16 a, b, c;
} Pose_8017E550;

typedef struct { s16 x, y, z; s16 pad[5]; } Work_8017E550;

extern void *D_80185F6C[];
extern s32   D_801F8090;
extern void *D_801F8118;

extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8017F824();

void func_8017E550(Actor_8017E550 *a0) {
    Work_8017E550 v;
    Drv_8017E550 *p;
    Pose_8017E550 *pp;
    s32 t;

    p = (Drv_8017E550 *)a0->f64;
    if (p == NULL) {
        return;
    }

    pp = (Pose_8017E550 *)D_80185F6C[a0->f70];

    if ((p->f02 == 1) && (p->f34 == 1)) {
        func_8012E88C((u8 *)a0);
        a0->f98 = 0;

        v.x = (pp->x * D_801F8090) >> 12;
        v.y = (pp->y * D_801F8090) >> 12;
        v.z = (pp->z * D_801F8090) >> 12;

        if (*(u16 *)((u8 *)D_801F8118 + 2) == 2) {
            func_8017F824(&v, 0x200);
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            t = p->f20->rot.x;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.x = t >> 3;
            t = p->f20->rot.y;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.y = t >> 3;
            t = p->f20->rot.z;
            __asm__("" : "=r"(t) : "0"(t) : "memory");
            a0->f20->rot.z = t >> 3;
        } else {
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            a0->f20->rot = p->f20->rot;
        }

        a0->f20->f10 = pp->a;
        a0->f20->f12 = pp->b;
        a0->f20->f14 = pp->c;
    } else {
        func_8012E8A8((u8 *)a0);
        a0->f98 = 0;
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017E734);

typedef struct {
    s16 x, y, z, pad;
} Rot_8017E878;

/* the coordinate/model record hung off +0x20 of both the actor and the driver */
typedef struct {
    u8            pad00[0x10];
    u16           f10;          /* 0x10 */
    u16           f12;          /* 0x12 */
    u16           f14;          /* 0x14 */
    u8            pad16[0x02];
    Rot_8017E878  rot;          /* 0x18 */
    s32           align;        /* keeps align 4 so the +0x20 pointer loads with lw */
} Coord_8017E878;

typedef struct {
    u8              pad00[0x06];
    s16             f06;        /* 0x06 */
    u8              pad08[0x02];
    s16             f0A;        /* 0x0A */
    u8              pad0C[0x02];
    s16             f0E;        /* 0x0E */
    u8              pad10[0x10];
    Coord_8017E878 *f20;        /* 0x20 */
    u8              pad24[0x40];
    s32             f64;        /* 0x64 — driver record pointer */
    u8              pad68[0x08];
    u8              f70;        /* 0x70 — pose index */
    u8              pad71[0x27];
    s16             f98;        /* 0x98 */
} Actor_8017E878;

typedef struct {
    u8              pad00[0x02];
    u16             f02;        /* 0x02 */
    u8              pad04[0x1C];
    Coord_8017E878 *f20;        /* 0x20 */
    u8              pad24[0x10];
    u16             f34;        /* 0x34 */
} Drv_8017E878;

/* 12-byte stride pose table based at D_801F82A8 */
typedef struct {
    s16 x, y, z;
    u16 a, b, c;
} Pose_8017E878;

/* 16 bytes: the frame's var region is 0x10..0x1F (only x/y/z are ever touched) */
typedef struct { s16 x, y, z; s16 pad[5]; } Work_8017E878;

extern s32   D_801F8090;
extern void *D_801F8118;
extern Pose_8017E878 D_801F82A8[];

extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8017E734(void *a0);

void func_8017E878(Actor_8017E878 *a0) {
    Work_8017E878 v;            /* sp+0x10 */
    Drv_8017E878 *p;
    Pose_8017E878 *pp;

    p = (Drv_8017E878 *)a0->f64;
    if (p == NULL) {
        return;
    }

    pp = &D_801F82A8[a0->f70];

    if ((p->f02 == 1) && (p->f34 == 1)) {
        func_8012E88C((u8 *)a0);
        a0->f98 = 0;

        v.x = (pp->x * D_801F8090) >> 12;
        v.y = (pp->y * D_801F8090) >> 12;
        v.z = (pp->z * D_801F8090) >> 12;

        if (*(u16 *)((u8 *)D_801F8118 + 2) == 0xF) {
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            func_8017E734(a0);
        } else {
            a0->f06 = v.x;
            a0->f0A = v.y;
            a0->f0E = v.z;
            a0->f20->rot = p->f20->rot;   /* 8-byte align-2 copy: lwl/lwr + swl/swr */
        }

        a0->f20->f10 = pp->a;
        a0->f20->f12 = pp->b;
        a0->f20->f14 = pp->c;
    } else {
        func_8012E8A8((u8 *)a0);
        a0->f98 = 0;
    }
}


#include "common.h"

/*
 * func_8017EA18 (ov_SC06_006, 180 ins) - "spawn the actor's model/animation slot".
 *
 * Shape: allocate an object (func_8012C1B8) into d->0x20; on failure hand the entity
 * to func_8012CAE4 and leave.  Otherwise dispatch on the HIGH byte of the s16 at
 * d->0x70 (a decision tree over 0x000/0x100/0x200/0x300/0x400) and, for four of the
 * five arms, publish a { source_ptr, 0 } 8-byte "slot" into a per-arm global table,
 * bind it to the object (func_8001C214), set the object's 0x7FFF/0x7FFF scale
 * (func_8001D0E8), OR 0x10 into the object's 0x2C flags, and reset the entity's
 * 0x34/0x06/0x0A/0x0E fields while bumping the 0x02 sequence counter.
 *
 * DECLARATIONS: the destination TU (src/ov_SC06_006/ov_SC06_006_jr_8017BEBC.c) declares
 * NONE of these symbols and does not pre-declare func_8017EA18, so every spelling below
 * is new.  The four callee externs use the fleet-modal raw form and recover the real
 * signature with a cast at the call site (func_8012C1B8 is `void f(void)` in 3,309
 * places yet returns the object pointer - the ov_SC03_006/ov_SC03_099 idiom, wave law 4).
 *
 * BYTE NOTES (things that are NOT free to re-spell):
 *
 *  1. `s16 h` (not s32).  The HImode local is what splits the loaded value into two
 *     pseudos - `lh $a1` plus `addu $v1,$a1,$zero` in the branch delay slot - which is
 *     the target's shape (cookbook s172a).  With `s32 h` the copy is gone and the body
 *     is 179 instructions.
 *
 *  2. THE THIRD-SYMBOL RULE (this is the frame fix; see the long note below).  In every
 *     arm the func_8001C214 slot-address argument is spelled off a symbol that the arm
 *     does NOT otherwise touch, with a constant element offset that lands on the exact
 *     same address as the arm's word-0 store:
 *         arm 0x000  &D_801F854C[h*2 - 10]  == &D_801F8524[h*2]   (0x801F854C - 0x28)
 *         arm 0x100  &D_801F8524[n*2 + 10]  == &D_801F854C[n*2]   (0x801F8524 + 0x28)
 *         arm 0x300  &D_801F859C[n*2 -  6]  == &D_801F8584[n*2]   (0x801F859C - 0x18)
 *         arm 0x400  &D_801F8584[n*2 +  6]  == &D_801F859C[n*2]   (0x801F8584 + 0x18)
 *     Every one of these resolves to the byte-identical address, so the LINKED bytes are
 *     identical to the target's; only the relocation's chosen symbol+addend differs.
 *     (The original source almost certainly declared a THIRD, struct-typed symbol at the
 *     same address as word 0 - `slotPtr[n*2]`, `slotPad[n*2]`, `&slots[n]` - which the
 *     .s cannot show, because splat names every relocation by resolved address.)
 *
 *  3. In case 0x000 the index is RE-READ from d->0x70 three times: each of the two
 *     stores kills the cse'd load (s193-E), which is exactly the target's three `lh`s.
 *
 *  4. `p = D_801B9830;` must precede `i = 0;` - that ordering is what puts the loop's
 *     `la` in $a1 and schedules it into the `lw $a0,0x20($s0)` load-delay slot.
 *
 * WHY THE THIRD SYMBOL (the frame residual the first pass could not close, measured):
 *     Each arm needs THREE distinct symbol expressions - word-0 store, word-1 store and
 *     the call argument - because the target keeps both stores in the folded
 *     `sw $x, SYM($idx)` assembler-macro form AND materialises the argument base with a
 *     separate `la`+`addu`.  If the argument names a symbol that one of the stores also
 *     names, cse hands both uses the SAME symbol pseudo; combine then folds that pseudo
 *     into the store's MEM, the `plus` insn is deleted, and its REG_DEAD note has nowhere
 *     to land (combine.c:10835 - the backward death-note walk crosses only INSNs, so it
 *     runs off the top of the arm's basic block and combine emits a bare
 *     `(use (reg N))` right after the CODE_LABEL).  That orphaned pseudo has a USE and no
 *     DEF, so regclass gives it NO_REGS, global_alloc cannot colour it, and alter_reg
 *     buys it an 8-byte stack slot that nothing ever references (cookbook s172, producer
 *     1+2).  One such orphan per arm plus one from the `s16` promotion = 40 bytes of
 *     vars, i.e. frame 0x40 instead of the target's 0x20.  Giving the argument its own
 *     un-shared symbol removes all four arm orphans at zero instruction cost; only the
 *     s16-promotion orphan survives, which is exactly the target's single 8-byte slot at
 *     sp+0x10.  Byte-verified: 5 orphans -> 1, frame 0x40 -> 0x20, 180/180 instructions.
 */

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);

extern s32 D_801E95F8[];        /* case 0x000 source table            */
extern s32 D_801F8524[];        /* case 0x000 slot word 0             */
extern s32 D_801F8528[];        /* case 0x000 slot word 1 (= +4)      */
extern s16 D_801B9830[];        /* 0x1E-byte records, -1 terminated   */
extern s32 D_801F1C50[];        /* case 0x100 source table            */
extern s32 D_801F854C[];        /* case 0x100 slot word 0             */
extern s32 D_801F8550[];        /* case 0x100 slot word 1 (= +4)      */
extern s32 D_80185F60[];        /* case 0x300 source table (pointers) */
extern s32 D_801F8584[];        /* case 0x300 slot word 0             */
extern s32 D_801F8588[];        /* case 0x300 slot word 1 (= +4)      */
extern s32 D_801CF938[];        /* case 0x400 source table            */
extern s32 D_801F859C[];        /* case 0x400 slot word 0             */
extern s32 D_801F85A0[];        /* case 0x400 slot word 1 (= +4)      */

void func_8017EA18(s32 d)
{
    s32 obj;
    s16 h;

    *(s32 *)(d + 0x20) = obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
        return;
    }

    h = *(s16 *)(d + 0x70);
    switch (h & 0xFF00) {
    case 0x000:
        {
            s16 *p;
            s32 i;

            D_801F8524[*(s16 *)(d + 0x70) * 2] = D_801E95F8[*(s16 *)(d + 0x70)];
            D_801F8528[*(s16 *)(d + 0x70) * 2] = 0;
            func_8001C214(*(s32 *)(d + 0x20),
                          (s32)&D_801F854C[*(s16 *)(d + 0x70) * 2 - 10]);
            func_8001D0E8(*(s32 *)(d + 0x20), 0x7FFF, 0x7FFF);
            *(u16 *)(*(s32 *)(d + 0x20) + 0x2C) |= 0x10;
            *(s32 *)(*(s32 *)(d + 0x20) + 0x4) |= 0x40000000;
            p = D_801B9830;
            i = 0;
            *(s16 *)(d + 0x34) = 0;
            *(s16 *)(d + 0x6) = 0;
            *(s16 *)(d + 0xA) = 0;
            *(s16 *)(d + 0xE) = 0;
            *(u16 *)(d + 0x2) += 1;
            while (*p != -1) {
                p += 15;                    /* 0x1E-byte stride */
                i++;
            }
            *(s16 *)(d + 0xDC) = i;
        }
        break;

    case 0x100:
        {
            s32 n = h & 0xFF;

            D_801F854C[n * 2] = D_801F1C50[n];
            D_801F8550[n * 2] = 0;
            func_8001C214(*(s32 *)(d + 0x20), (s32)&D_801F8524[n * 2 + 10]);
            func_8001D0E8(*(s32 *)(d + 0x20), 0x7FFF, 0x7FFF);
            *(u16 *)(*(s32 *)(d + 0x20) + 0x2C) |= 0x10;
            *(s32 *)(d + 0xDC) = 0x1000;
            *(s16 *)(d + 0x34) = 0;
            *(s16 *)(d + 0x6) = 0;
            *(s16 *)(d + 0xA) = 0;
            *(s16 *)(d + 0xE) = 0;
            *(u16 *)(d + 0x2) += 1;
        }
        break;

    case 0x200:
        break;

    case 0x300:
        {
            s32 n = h & 0xFF;

            D_801F8584[n * 2] = *(s32 *)D_80185F60[n];
            D_801F8588[n * 2] = 0;
            func_8001C214(*(s32 *)(d + 0x20), (s32)&D_801F859C[n * 2 - 6]);
            func_8001D0E8(*(s32 *)(d + 0x20), 0x7FFF, 0x7FFF);
            *(u16 *)(*(s32 *)(d + 0x20) + 0x2C) |= 0x10;
            *(s16 *)(d + 0x34) = 0;
            *(s16 *)(d + 0x6) = 0;
            *(s16 *)(d + 0xA) = 0;
            *(s16 *)(d + 0xE) = 0;
            *(u16 *)(d + 0x2) += 1;
        }
        break;

    case 0x400:
        {
            s32 n = h & 0xFF;

            D_801F859C[n * 2] = D_801CF938[n];
            D_801F85A0[n * 2] = 0;
            func_8001C214(*(s32 *)(d + 0x20), (s32)&D_801F8584[n * 2 + 6]);
            func_8001D0E8(*(s32 *)(d + 0x20), 0x7FFF, 0x7FFF);
            *(u16 *)(*(s32 *)(d + 0x20) + 0x2C) |= 0x10;
            *(s16 *)(d + 0x34) = 0;
            *(s16 *)(d + 0x6) = 0;
            *(s16 *)(d + 0xA) = 0;
            *(s16 *)(d + 0xE) = 0;
            *(u16 *)(d + 0x2) += 1;
        }
        break;
    }
}



extern void (*D_80185F8C[])(void);

void func_8017ECE8(void *a0) {
    D_80185F8C[*(u16 *)((s32)a0 + 0x2)]();
}


extern int rand(void);

typedef struct { u8 b[4]; } Col4;

u32 func_8017ED24(u32 param_1, u32 param_2)
{
    Col4 buf;
    s32 r;
    s32 g;
    s32 b;

    buf = *(Col4 *)&param_2;
    r = buf.b[0];
    g = buf.b[1];
    b = buf.b[2];

    if (rand() & 1) {
        r -= rand() & 0x1F;
        if (r < 0) {
            r = 0;
        }
    } else {
        r += rand() & 0x1F;
        if (r > 255) {
            r = 255;
        }
    }

    if (rand() & 1) {
        g -= rand() & 0x1F;
        if (g < 0) {
            g = 0;
        }
    } else {
        g += rand() & 0x1F;
        if (g > 255) {
            g = 255;
        }
    }

    if (rand() & 1) {
        b -= rand() & 0x1F;
        if (b < 0) {
            b = 0;
        }
    } else {
        b += rand() & 0x1F;
        if (b > 255) {
            b = 255;
        }
    }

    buf.b[0] = r;
    buf.b[1] = g;
    buf.b[2] = b;
    *(Col4 *)param_1 = buf;
    return param_1;
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017EEA4);

#include "common.h"

/* func_8017F074 — ov_SC06_006 "screen-flash step".
 *
 * Bumps the actor's u16 frame counter at +0x6; looks up its 20-byte flash-script
 * record D_801860AC[actor->f4C]; and while the counter is inside the record's
 * [f4+1, f8] window, ramps the actor's stored RGB (+0x50) toward the record's
 * per-frame delta (record+0x10) with a 0..255 clamp, then allocates a 24-byte
 * POLY_F4 (code 0x2A, tag len 5), lays a full-screen -160/-120..160/120 quad in
 * it, colours it with the ramped RGB and links it into the current double
 * buffer's OT at the record's depth (record+0x2), finally calling
 * func_8012E28C(depth, record->f0).
 *
 * @class: was LENGTH-DRIFT (-2) -> REGALLOC-PERM -> sched1 store-order
 * @stuck: none — MATCH (121 ins), byte-exact (relocation-masked) under match_one.
 *
 * LEVERS (each re-scored by removing it):
 *  1. `tr = a.r; tr += b.r;` — NOT `tr = a.r + b.r;`.  This is the whole crack.
 *     Written as one expression the sum is a fresh pseudo that global_alloc
 *     cannot tie to the `lbu` temp, so the three accumulators come out
 *     $a0/$a0/$v1 instead of the target's $v1/$a0/$v1; tr and tg then SHARE
 *     $a0, which creates an anti-dependence that forces each `sb <prev>` to be
 *     scheduled BEFORE the next block's `addu` — where it fills the load-delay
 *     slot that the target leaves as a `nop`.  Result: 119/120 ins, i.e. the
 *     -1/-2 LENGTH-DRIFT.  Loading into the accumulator first makes the load
 *     temp and the accumulator ONE pseudo (`addu $v1,$v1,$v0`), the stores stay
 *     free to sink into the following branch's delay slot, and the two `nop`s
 *     come back.  (`tr = a.r; tr = tr + b.r;` is byte-identical — §189-B.)
 *     Register PINS are the wrong tool here: `register s32 tr __asm__("$3")`
 *     also fixes the length (121 ins) but permanently swaps that block's two
 *     `lbu` destinations, because a pinned pseudo can never be tied to the
 *     first operand's load.  3 mismatches, unfixable.  (§178 / law 7.)
 *  2. `*(u32 *)(prim + 4) = *(u32 *)&a;` must sit BETWEEN the x2 and y2 stores
 *     (16 -> 3 mismatches).  That single statement placement is what lets the
 *     8 coordinate `sh`s come out in source order 0x8,0xA,0xC,0xE,0x10 with
 *     -160 in $a0 / 160 in $a1; with the colour word written after all eight,
 *     sched1 instead hoists the two -120 stores (0xA,0xE) to the head of the
 *     block and swaps the two $a-registers.  (§190-B: natural order first, then
 *     order is the dial.)
 *  3. y3 (0x16) is written BEFORE x3 (0x14) — the target reuses $v1 for both
 *     120-stores and only then reloads it with 0x2A (17 -> 16 mismatches).
 *  4. `if (e->f6 > *(s16 *)(p + 6))` — operand order decides which `lh` issues
 *     first ($s0's before $a2's).  The reload of p+6 is real: the `sh` above it
 *     plus the two block moves kill the CSE (§193-E).
 *  5. `Cv_8017F074` = `struct { u8 r,g,b,c; }` (ALIGNMENT 1), so the two struct
 *     assignments lower to gcc's `emit_block_move` lwl/lwr + swl/swr pairs
 *     (§160a).  A u32 copy would give aligned lw/sw and is wrong.  Their 8-byte
 *     frame stride each (0x10 and 0x18, 4 bytes apart used) is §193-I.
 *  6. `s16 n;` with `n = *(u16 *)(p + 6) + 1;` gives the lhu/addiu/sh trio plus
 *     the single sll/sra sign-extension that both `slt`s share.
 *
 * SYMBOL AUDIT (law 1c, done after MATCH) — every symbol re-checked against
 * asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017BEBC/func_8017F074.s's own
 * relocation lines.  The .s has exactly six: %hi/%lo(D_801860AC) (0x8017F09C/A0,
 * addiu => address-of the table), %hi/%lo(D_800B9A02) (0x8017F204/208, lhu),
 * %hi/%lo(D_800A651C) (0x8017F21C/224, lw), and jal func_80010A08 (0x8017F1B0),
 * jal AddPrim (0x8017F22C), jal func_8012E28C (0x8017F23C).  No others.
 * Access sides: $a2 == the argument (0x6 lhu/sh/lh, 0x4C lh, 0x50 lwl/lwr+sw);
 * $s0 == &D_801860AC[f4C] (0x0/0x2/0x4/0x6/0x8 lh, 0x10 lwl/lwr); $v0 == the
 * 0x18-byte allocation (sw 0x0, sh 0x8..0x16, sw 0x4, sb 0x7); $sp+0x10 and
 * $sp+0x18 are the two 4-byte colour locals.
 *
 * BANK NOTES (law 2 / §181) — src/ov_SC06_006/ov_SC06_006_jr_8017BEBC.c declares
 * NONE of func_80010A08 / AddPrim / func_8012E28C / D_800A651C / D_801860AC, so
 * the externs below are new; each uses the fleet-modal spelling from the card's
 * decl_prior (1676 / 1508 / 1343 sites respectively) and the block-scope
 * `extern OtBlk D_800A651C[];` form that ov_SC03_006 / ov_SC03_099 / ov_SC06_008
 * already bank next to engine_core.h's macro-internal `extern s32 D_800A651C;`.
 *  ==> DROP the `OtBlk` typedef below when banking: engine_types.h (pulled in by
 *      the TU's `#include "../shared/engine_core.h"`) already defines exactly
 *      `typedef struct { s32 a; s32 b[4]; } OtBlk;`.
 *  ==> DROP `extern short D_800B9A02;` when banking: the TU already carries that
 *      exact spelling at file scope (line 2466).
 *  ==> `Cv_8017F074` / `Fade_8017F074` / `D_801860AC` are unused names anywhere
 *      in the overlay; D_801860AC is referenced by no other .s in ov_SC06_006.
 *  The TU has no prototype for func_8017F074 itself, so the definition's
 *  `void func_8017F074(void *arg0)` is unconstrained (law 3 clear).
 */

/* DROP WHEN BANKING — engine_types.h already defines this typedef in the TU. */


/* align-1 4-byte colour word => struct assignment lowers to lwl/lwr+swl/swr (§160a) */
typedef struct { u8 r, g, b, c; } Cv_8017F074;

/* D_801860AC — overlay-private 20-byte flash-script record (stride 0x14) */
typedef struct {
    /* 0x00 */ s16 f0;
    /* 0x02 */ s16 f2;          /* OT depth */
    /* 0x04 */ s16 f4;          /* first active frame - 1 */
    /* 0x06 */ s16 f6;          /* ramp-in end frame */
    /* 0x08 */ s16 f8;          /* last active frame */
    /* 0x0A */ s16 fA, fC, fE;
    /* 0x10 */ Cv_8017F074 col; /* per-frame colour delta */
} Fade_8017F074;

extern Fade_8017F074 D_801860AC[];
extern short D_800B9A02;                    /* DROP WHEN BANKING (already in the TU) */
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32 arg0, s32 arg1);

void func_8017F074(void *arg0)
{
    extern OtBlk D_800A651C[];
    u8 *p = (u8 *)arg0;
    Fade_8017F074 *e;
    u8 *prim;
    Cv_8017F074 a;              /* $sp+0x10 — the actor's live colour */
    Cv_8017F074 b;              /* $sp+0x18 — the script's per-frame delta */
    s16 n;
    s32 tr;
    s32 tg;
    s32 tb;

    n = *(u16 *)(p + 6) + 1;                    /* frame counter */
    e = &D_801860AC[*(s16 *)(p + 0x4C)];        /* script id at +0x4C */
    *(s16 *)(p + 6) = n;
    if (e->f4 < n && e->f8 >= n) {
        a = *(Cv_8017F074 *)(p + 0x50);
        b = e->col;
        if (e->f6 > *(s16 *)(p + 6)) {          /* still ramping in */
            tr = a.r;
            tr += b.r;
            if (tr < 0) {
                tr = 0;
            } else if (tr > 0xFF) {
                tr = 0xFF;
            }
            a.r = tr;
            tg = a.g;
            tg += b.g;
            if (tg < 0) {
                tg = 0;
            } else if (tg > 0xFF) {
                tg = 0xFF;
            }
            a.g = tg;
            tb = a.b;
            tb += b.b;
            if (tb < 0) {
                tb = 0;
            } else if (tb > 0xFF) {
                tb = 0xFF;
            }
            a.b = tb;
        }
        *(u32 *)(p + 0x50) = *(u32 *)&a;
        prim = (u8 *)func_80010A08(0x18);
        *(u32 *)prim = 0x05000000;              /* tag: 5 words follow */
        *(s16 *)(prim + 0x08) = -160;           /* x0 */
        *(s16 *)(prim + 0x0A) = -120;           /* y0 */
        *(s16 *)(prim + 0x0C) = 160;            /* x1 */
        *(s16 *)(prim + 0x0E) = -120;           /* y1 */
        *(s16 *)(prim + 0x10) = -160;           /* x2 */
        *(u32 *)(prim + 4) = *(u32 *)&a;        /* r0,g0,b0 (code byte fixed up below) */
        *(s16 *)(prim + 0x12) = 120;            /* y2 */
        *(s16 *)(prim + 0x16) = 120;            /* y3 */
        *(s16 *)(prim + 0x14) = 160;            /* x3 */
        *(u8 *)(prim + 7) = 0x2A;               /* POLY_F4, semi-transparent */
        AddPrim(D_800A651C[(u16)D_800B9A02].a + (e->f2 * 4), prim);
        func_8012E28C(e->f2, e->f0);
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017F258);

void func_8017F2A0(void) {
    extern u8 D_801F85EC[];
    s32 i;
    u8 *p;

    i = 0;
    p = D_801F85EC;
    do {
        if (*(void **)(p + 8) != NULL) {
            func_80016714(*(void **)(p + 8), 0x38);
        }
        func_80016714(p, 0x54);
        i++;
        p += 0x54;
    } while (i < 12);
}


void func_8017F308(void) {
    extern s16 D_801F85EC[][42];
    extern s16 D_801F8638[][42];
    extern s16 D_801F80A4;
    s32 i;
    s32 j;
    u8 *p;

    i = 0;
    p = (u8 *)D_801F85EC;
    do {
        if (*(void **)(p + 8) != NULL) {
            func_80016714(*(void **)(p + 8), 0x38);
        }
        func_80016714(p, 0x54);
        i++;
        p += 0x54;
    } while (i < 12);

    D_801F80A4 = 1;

    for (j = 0; j < 10; j++) {
        D_801F85EC[j][0] = 1;
        D_801F8638[j][0] = j;
    }

    for (j = 10; j < 12; j++) {
        D_801F85EC[j][0] = 2;
        D_801F8638[j][0] = j - 10;
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017F3E8);

void func_8017F4B8(void) {
}

INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017F4C0);


extern void (*D_801861E4[])(void);

void func_8017F594(void *a0) {
    D_801861E4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* ov_SC06_006 camera-shake / wobble tick.
 * D_801F8118 -> control block; +0x2 is the u16 index into the 0x14-byte
 * entry table at D_801861EC.  Entry layout used here:
 *   +0x00 s32  mode (0 = clear, 1 = sin/cos wobble)
 *   +0x08 s16  X period      +0x0A s16  Y period
 *   +0x0C s16  X amplitude   +0x0E s16  Y amplitude
 *   +0x10 u16  X bias        +0x12 u16  Y bias
 * D_801F809C is the free-running frame counter, bumped on every tick.
 */
extern void *D_801F8118;
extern u8 D_801861EC[];
extern s16 D_801F8A10;              /* shake X out */
extern s16 D_801F8A12;              /* shake Y out */
extern s16 D_801F8A14;              /* shake Z out */
extern s16 D_801F809C;              /* frame counter */
extern s32 func_8004787C(s32 a0);   /* rsin */
extern s32 func_80047948(s32 a0);   /* rcos */

void func_8017F5D0(void)
{
    u8 *e;
    s16 *p = &D_801F8A10;           /* §20/§165-10: pointer form -> shared base in $s1 */
    register s32 t __asm__("$2");   /* pin: local_alloc otherwise spills t to $a0 */
    s32 u;
    s32 c;

    e = &D_801861EC[*(u16 *)((u8 *)D_801F8118 + 2) * 0x14];
    switch (*(s32 *)e) {
    case 0:
        *p = 0;
        D_801F8A12 = 0;
        D_801F8A14 = 0;
        break;
    case 1:
        t = (func_8004787C(((D_801F809C % *(s16 *)(e + 0x8)) << 12) / *(s16 *)(e + 0x8)) * *(s16 *)(e + 0xC)) >> 12;
        *p = t;
        t -= *(u16 *)(e + 0x10);
        /* §194-A pair: the fences pin the D_801F809C reload between the subu
         * and the second store; without them sched2 emits the store first. */
        __asm__ __volatile__("");
        c = D_801F809C;
        __asm__ __volatile__("");
        *p = t;
        u = (func_80047948(((c % *(s16 *)(e + 0xA)) << 12) / *(s16 *)(e + 0xA)) * *(s16 *)(e + 0xE)) >> 12;
        D_801F8A12 = u;
        u -= *(u16 *)(e + 0x12);
        D_801F8A12 = u;
        D_801F8A14 = 0;
        break;
    }
    D_801F809C++;
}


extern void func_80015D4C();

void func_8017F7C4(s32 arg0) {
    func_80015D4C(
        *(s16 *)(arg0 + 0),
        *(s16 *)(arg0 + 2),
        *(s16 *)(arg0 + 4),
        *(s16 *)(arg0 + 6),
        *(u8 *)(arg0 + 8),
        *(u8 *)(arg0 + 9),
        *(u8 *)(arg0 + 0xA),
        *(u16 *)(arg0 + 0xC),
        4);
}


extern u8 D_800AF648;
void func_8017F824(s32 a0, s32 a1) {
    s16 arr[3];
    func_8012F14C((s32)&D_800AF648, a0, (s32)arr);
    arr[0] = (s16)((arr[0] * a1) >> 12);
    arr[1] = (s16)((arr[1] * a1) >> 12);
    arr[2] = (s16)((arr[2] * a1) >> 12);
    func_8012F038((s32)&D_800AF648, arr, a0);
}


extern void *D_801F8118;
extern s16 D_800B9AAC[];
extern s16 D_800B9B00;
extern s16 D_800B9AB8[];
extern void (*D_80186368)(void);

void func_8017F8CC(void) {
    s16 t;

    if (*(u16 *)((u8 *)D_801F8118 + 2) == 0x11) {
        D_800B9AAC[0] = 0x7FFF;
        t = 0xFFE;
    } else {
        D_800B9AAC[0] = 0xFFE;
        t = 0x7FFF;
    }
    D_800B9B00 = t;
    __asm__ __volatile__("");
    *(u16 *)D_800B9AB8 += (s32)D_80186368;
}


extern s32 D_801F80B8;
extern u16 D_801F824E;
extern u16 D_801F8250;
extern u16 D_801F8252;
extern s16 D_801F8248;
extern s16 D_801F824A;
extern s16 D_801F824C;
extern s32 D_801F8090;
extern s32 D_80186394;
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_8017FA2C();

void func_8017F934(void) {
    struct {
        u8 pad[0x14];
        s32 x;
        s32 y;
        s32 z;
        u8 pad2[0x1C];
    } sp10;
    u16 sp50[3];
    u16 sp58[3];

    if (D_801F80B8 != 0 && *(u16 *)(D_801F80B8 + 2) == 1 && *(u16 *)(D_801F80B8 + 0x34) == 1) {
        sp50[0] = D_801F824E;
        sp50[1] = D_801F8250;
        sp50[2] = D_801F8252;
        func_80049CAC((s32)sp50, (s32)&sp10);
        sp10.x = (D_801F8248 * D_801F8090) >> 12;
        sp10.y = (D_801F824A * D_801F8090) >> 12;
        sp10.z = (D_801F824C * D_801F8090) >> 12;
        sp58[0] = (u16)D_801F8090;
        sp58[1] = (u16)D_801F8090;
        sp58[2] = (u16)D_801F8090;
        func_80020F34((s32)&sp10, (s32)sp58);
        func_8017FA2C(&sp10, &D_80186394, &D_80186394 + 2);
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017FA2C);

extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017FD4C(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_8012F14C)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ApplyMatrixSV((void *)param_1, dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}


extern s32 D_801F8084;
extern s32 D_801863A8;
extern u16 D_801863A4;
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FECC(s32 a0)
{
    if (D_801F8084 == *(s32 *)(&D_801863A8 + a0 * 5)) {
        func_8002D4C8(*(u16 *)(&D_801863A4 + a0 * 10), 0);
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8017FF24);

extern u8 *D_801F80AC[];
extern s32 D_801F80BC;
extern s32 D_801F80C8;
extern s32 D_801F80DC;
extern s32 D_801F80E0;
extern void *D_801F80E4;
extern s32 D_801F80E8;
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8017FFA8(void) {
    s32 i;

    for (i = 0; i < 0x1B; i++) {
        D_801F80AC[i] = (u8 *)func_8012C658(0x34A, i, 0);
    }
    for (i = 0; i < 5; i++) {
        func_8012C658(0x389, i, D_801F80C8);
    }
    for (i = 0; i < 7; i++) {
        func_8012C658(0x389, i | 0x100, (s32)D_801F80E4);
    }
    func_8012C658(0x389, 0x300, D_801F80DC);
    func_8012C658(0x389, 0x301, D_801F80E0);
    func_8012C658(0x389, 0x302, D_801F80E8);
    for (i = 0; i < 10; i++) {
        func_8012C658(0x389, i | 0x400, D_801F80BC);
    }
    func_8012C588(0x38F, 0);
}



#include "common.h"

/* 8-byte script command record */
typedef struct {
/* 0x0 */ s16 kind;   /* slot index; -1 terminates */
/* 0x2 */ s16 cmd;    /* opcode 0..3 */
/* 0x4 */ s32 arg;
} Cmd801800B8;

/* argument block (&D_80185A80 &c.) */
typedef struct {
/* 0x00 */ Cmd801800B8 *cmds;
/* 0x04 */ s32 unk04;
/* 0x08 */ s32 unk08;
/* 0x0C */ s32 unk0C;
/* 0x10 */ s32 unk10;
} Ctl801800B8;

extern void func_801802E0(s32 *);
extern void func_8017F5D0(void);
extern void func_80180E68(s32, s32);
extern void func_80129CF8(void);
extern void func_8012E8A8(u8 *);
extern void func_8012E88C(u8 *);
extern void func_8012A828(s32, void *);
extern void func_801802A0(s32, s32, s32, s32);

extern void *D_801F8118;
extern s32 D_801861F0[];
extern s16 D_801F80A4;
extern s32 D_801F8084;
extern s32 D_801F8088;
extern s32 D_801F808C;
extern s32 D_801F8090;
extern s16 D_801F809C;
extern s32 D_801F8AEC;
extern u8 *D_801F80AC[];
extern s16 D_80185870[];
extern s32 D_801858A8[];

void func_801800B8(void *a0) {
    Ctl801800B8 *ctl = (Ctl801800B8 *)a0;
    Cmd801800B8 *p;
    u8 *obj;
    s32 t;
    s32 u;

    func_801802E0((s32 *)a0);

    u = ctl->unk0C;
    t = D_801861F0[(*(u16 *)((u8 *)D_801F8118 + 2)) * 5];
    __asm__ __volatile__("");
    D_801F80A4 = 0;
    D_801F8084 = 0;
    D_801F8088 = -1;
    D_801F808C = u;
    if (t != -1) {
        D_801F809C = t;
    }

    func_8017F5D0();

    D_801F8090 = ctl->unk10;
    func_80180E68(ctl->unk04, ctl->unk10);

    D_801F8AEC = ctl->unk08;

    func_80129CF8();

    p = ctl->cmds;
    while (p->kind != -1) {
        obj = D_801F80AC[p->kind];
        switch (p->cmd) {
        case 0:
            func_8012E8A8(obj);
            *(s16 *)(obj + 0x98) = 0;
            *(s16 *)(obj + 0x34) = 0;
            break;
        case 1:
            func_8012E88C(obj);
            func_801802A0((s32)obj, p->arg,
                          D_80185870[*(s16 *)(obj + 0x70)],
                          D_801858A8[*(s16 *)(obj + 0x70)]);
            *(s16 *)(obj + 0x34) = 1;
            break;
        case 2:
            func_8012E88C(obj);
            func_8012A828((s32)obj, (void *)p->arg);
            *(s16 *)(obj + 0x34) = 2;
            break;
        case 3:
            *(s32 *)(obj + 0xDC) = p->arg;
            break;
        }
        p++;
    }
}


void func_801802A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 count = 0;

    ((s32 *)arg0)[0x24] = (s32)arg1;
    ((s32 *)arg0)[0x25] = 0;
    ((s16 *)arg0)[0x4D] = arg2;
    ((s32 *)arg0)[0x27] = arg3;
    ((s16 *)arg0)[0x4C] = 0;

    while (*(s16 *)(arg1 + 4) > 0) {
        arg1 += 8;
        count++;
    }
    ((s16 *)arg0)[0x7E] = count;
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_801802E0);

extern void func_80180390(void);
extern s32 D_801F8084;
extern s32 D_801F808C;

s32 func_8018034C(void) {
    if (D_801F8084 >= D_801F808C) {
        func_80180390();
        return 1;
    }
    return 0;
}


extern s16 D_801F807C;
extern void (*D_80185914[])(void);

void func_80180390(void) {
    s32 v1;
    register void (**base)(void) __asm__("$5");
    v1 = (s16)D_801F807C + 1;
    base = D_80185914;
    if (D_80185914[v1] == 0)
        v1 = 0;
    D_801F807C = (s16)v1;
    base[v1]();
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_801803F4);

extern s32 func_8018034C(void);
    void func_80180424(void) {
        ((void (*)(void))func_8018034C)();
    }


extern s32 func_8018034C(void);
    void func_80180444(void) {
        func_8018034C();
    }


extern s32 func_8018034C(void);
void func_80180464(void) {
    ((void (*)(void))func_8018034C)();
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_80180484);

INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_801804DC);

extern s32 func_8018034C(void);
extern void func_8017F7C4(s32 arg0);

extern s32 D_80185AFC;

void func_80180534(void) {
    if (!func_8018034C()) {
        ((void (*)(s32))func_8017F7C4)((s32)&D_80185AFC);
    }
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8018056C);

extern s32 D_80185AFC;
extern s32 func_8018034C(void);
extern void func_8017F7C4(s32 arg0);

void func_801805EC(void) {
    if (!func_8018034C()) {
        ((void (*)(s32))func_8017F7C4)((s32)&D_80185AFC);
    }
}


extern s32 func_8018034C(void);
    void func_80180624(void) {
        ((void (*)(void))func_8018034C)();
    }


extern s16 D_801F8094;
extern void func_80180390(void);
extern s16 D_801F8098;
extern s32 D_801F8084;
extern s32 D_801F808C;
extern void func_801800B8(void *a0);
extern s16 D_80185BEC;

void func_80180644(void *a0) {
    if (D_801F8094 == D_801F8098) {
        func_80180390();
    } else if (D_801F8084 >= D_801F808C) {
        *(s16 *)((char *)a0 + 0x2) = 0xA;
        func_801800B8(&D_80185BEC);
    }
}


extern s32 func_8018034C(void);
void func_801806B4(void) {
    ((void (*)(void))func_8018034C)();
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_801806D4);

extern s32 func_8018034C(void);
    void func_80180714(void) {
        func_8018034C();
    }


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_80180734);

extern s32 func_8018034C(void);
    void func_801807CC(void) {
        func_8018034C();
    }


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_801807EC);

extern s32 func_8018034C(void);
extern s32 D_801F8084;
extern s16 D_801F8094;
extern s16 D_801F80A8;
extern s32 D_801857BC;
extern void func_800D1724(s32 a0);
extern void func_801379D8(void);
extern void func_8017D9E4(void);

void func_80180840(void) {
    func_8018034C();
    if (D_801F8084 == 0x78) {
        D_801F8094 = 7;
    }
    if (D_801F80A8 == 0 && D_801F8084 == 0x168) {
        D_801F80A8 = 1;
        func_800D1724((s32)&D_801857BC);
        func_801379D8();
    }
    func_8017D9E4();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8017FF24(void);
extern void func_8017FFA8(void);
extern void func_8017F2A0(void);
extern void func_801803F4(s32 a0);
extern void *D_801F8118;

void func_801808C0(s32 arg0)
{
    register s32 param_1 __asm__("$16");   /* $s0 */
    s32 obj;

    param_1 = arg0;
    obj = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = obj;
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    func_8001C214(obj, 0);
    func_80029124(0x143, 1);
    func_80029124(0x6F, 0);
    func_80029124(0x70, 0);
    func_80029124(0x71, 0);
    func_80029124(0x72, 0);
    func_80029124(0x73, 0);
    D_801F8118 = (void *)param_1;
    func_8017FF24();
    func_8017FFA8();
    func_8017F2A0();
    func_801803F4(param_1);
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8018097C);

void func_80180A44(void *a0) {
    switch (*(s16 *)((s32)a0 + 0x70) & 0xFF00) {
    case 0x0000:
        func_8017E168(a0);
        break;
    case 0x0100:
        func_8017E330(a0);
        break;
    case 0x0200:
        break;
    case 0x0300:
        func_8017E550(a0);
        break;
    case 0x0400:
        func_8017E878(a0);
        break;
    }
}


typedef struct {
    u8 mode;                 /* 0x00 */
    u8 pad01;
    u16 f02;                 /* 0x02 */
    u16 f04, f06, f08;
    u16 f0A;                 /* 0x0A */
    u8 pad0C[0x14 - 0x0C];
} Rec_80180AE8;

extern Rec_80180AE8 D_80185FA0[];
extern s32 D_80185F9C;
extern void func_8017F258(void);
extern s32 func_8012C194(void);
extern void func_8017F4C0(void *a0, u16 a1, s32 a2);
extern void func_8001CD9C(s32 a0, void *a1);

void func_80180AE8(void *arg0)
{
    extern s32 func_8017EEA4();
    Rec_80180AE8 *rec;
    s32 ent;
    register u32 bits __asm__("$2");
    s32 col;

    rec = &D_80185FA0[*(s16 *)((s32)arg0 + 0x4C)];
    if (*(u8 *)rec == 0) {
        func_8017F258();
        return;
    }
    ent = func_8012C194();
    *(s32 *)((s32)arg0 + 8) = ent;
    if (ent != 0) {
        func_8017F4C0((void *)((s32)arg0 + 0xC), rec->f02, 0);
        func_8001CD9C(ent, (void *)((s32)arg0 + 0xC));
        bits = *(u32 *)(ent + 4);
        col = D_80185F9C;
        *(u16 *)(ent + 0x18) = 0;
        *(u16 *)(ent + 0x1A) = 0;
        bits |= 0xD0000000;
        *(u32 *)(ent + 4) = bits;
        *(s16 *)(ent + 0x2C) = col;
        if (rec->mode == 1) {
            *(u16 *)(ent + 0x1E) = rec->f0A;
        } else {
            *(u16 *)(ent + 0x1E) = 0;
        }
        *(u16 *)((s32)arg0 + 4) = 0;
        *(u16 *)((s32)arg0 + 6) = 0;
        *(u16 *)((s32)arg0 + 2) += 1;
        func_8017EEA4((s32)arg0);
    }
}


extern void (*D_801860A4[])(void);

void func_80180BF8(void *a0) {
    D_801860A4[*(s16 *)((s32)a0 + 2)]();
}


extern s32 D_801860B8[];

void func_80180C34(s32 arg0) {
    *(u16 *)(arg0 + 4) = 0;
    *(u16 *)(arg0 + 6) = 0;
    *(u16 *)(arg0 + 2) += 1;
    *(s32 *)(arg0 + 0x50) = D_801860B8[*(s16 *)(arg0 + 0x4C) * 5];
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_80180C6C);


extern s16 D_801F8094;
    u32 func_80180CA8(void) {
        return (u32)(D_801F8094 == 1);
    }


void func_80180CC0(void) {

    extern s16 D_801F8098;
    D_801F8098 = 1;
}



extern s16 D_801F8094;
    u32 func_80180CD4(void) {
        return (u32)(D_801F8094 == 2);
    }


void func_80180CEC(void) {

    extern s16 D_801F8098;
    D_801F8098 = 2;
}


extern s16 D_801F8094;
    u32 func_80180D00(void) {
        return (u32)(D_801F8094 == 3);
    }


void func_80180D18(void) {

    extern s16 D_801F8098;
    D_801F8098 = 3;
}



extern s16 D_801F8094;
    u32 func_80180D2C(void) {
        return (u32)(D_801F8094 == 4);
    }


void func_80180D44(void) {

    extern s16 D_801F8098;
    D_801F8098 = 4;
}



extern s16 D_801F8094;
    u32 func_80180D58(void) {
        return (u32)(D_801F8094 == 5);
    }


void func_80180D70(void) {

    extern s16 D_801F8098;
    D_801F8098 = 5;
}


extern s16 D_801F8094;
    u32 func_80180D84(void) {
        return (u32)(D_801F8094 == 7);
    }


void func_80180D9C(void) {

    extern s16 D_801F8098;
    D_801F8098 = 7;
}


void func_80180DB0(s32 arg0)
{
    extern s16 D_801F8098;
    extern s16 D_801F8094;
    extern void (*D_80186114)(void *);
    extern s32 func_8012BEE8(s32);
    extern void func_80178BB8(s32, s32);
    extern s32 func_801789AC(s32);

    u16 v1 = *(u16 *)(arg0 + 0x34);

    switch (v1) {
    case 0:
        if (func_8012BEE8(arg0) == 0)
            break;
        func_80178BB8(arg0, (s32)&D_80186114);
        {
            u16 v0 = *(u16 *)(arg0 + 0x34);
            D_801F8098 = 0;
            D_801F8094 = 0;
            *(u16 *)(arg0 + 0x34) = v0 + 1;
        }
        break;
    case 1:
        if (func_801789AC(arg0) == 0)
            break;
        *(s32 *)(arg0 + 0x1C) = 0x10;
        *(u16 *)(arg0 + 0x34) = 0;
        break;
    }
}


void func_80180E4C(void *a0) {
        *(s16 *)((char *)a0 + 0x34) = 0;
        *(s32 *)((char *)a0 + 0x1c) = 0x10;
        *(u16 *)((char *)a0 + 0x2) += 1;
    }


extern void func_80180EFC(void*);
void func_80180E68(s32 a0, s32 a1) {
    extern s32 D_8012697C;
    extern u16 D_80126980;
    extern s32 D_801F89E0;
    D_8012697C = a0;
    D_801F89E0 = a1;
    D_80126980 = 0;
    func_8012A018((s32)func_80180EFC, 0);
}


s32 func_80180EA8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126980;
    return (s16)(D_80126980 & 0x8000);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_80180EFC(void*);
void func_80180EC4(s32 a0, s16 a1) {

    extern s32 D_8012697C;
    extern u16 D_80126980;
    D_8012697C = a0;
    D_80126980 = a1;
    func_8012A018((s32)func_80180EFC, 1);
}



extern void (*D_8018646C[])(void);

void func_80180EFC(void *a0) {
    D_8018646C[*(u8 *)((s32)a0 + 0x4)]();
}


extern s32 func_80180FE8(u8 *a0, u8 *a1, s32 a2);
void func_80180F38(u8 *a0) {
    s32 r;
    u16 *p = (u16 *)(a0 + 0x38);
    r = func_80180FE8(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF);
    if (r != 0) {
        *p = *p | 0x8000;
    } else {
        *p = *p + 1;
    }
}


extern s32 func_80180FE8(u8 *a0, u8 *a1, s32 a2);
void func_80180F90(u8 *a0) {
    u16 *p = (u16 *)(a0 + 0x38);
    if ((*p & 0x7FFF) != 0) {
        func_80180FE8(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF);
        *p = *p - 1;
    } else {
        *p = *p | 0x8000;
    }
}


s32 func_80180FE8(u8 *a0, u8 *a1, s32 a2) {
    extern s32 D_801F89E0;
    extern s16 D_801F8A10;
    extern s16 D_801F8A12;
    extern s16 D_801F8A14;
    extern s32 D_801F8AEC;
    register u8 *p __asm__("$5");
    register s16 *pa __asm__("$6");
    register u8 *self __asm__("$7");
    s32 aec;

    p = a1 + (s16)a2 * 14;
    pa = &D_801F8A10;
    __asm__ __volatile__("" : "=r"(pa) : "0"(pa));
    self = a0;
    if (*(s16 *)(p + 0xC) == 0x7FFF) {
        (*(u16 *)(self + 0x38))--;
        p -= 14;
    }
    *(s32 *)(self + 0x3C) = (*(s16 *)(p + 0) * D_801F89E0 >> 12) + pa[0];
    *(s32 *)(self + 0x40) = (*(s16 *)(p + 2) * D_801F89E0 >> 12) + (&D_801F8A10)[1];
    *(s32 *)(self + 0x44) = (*(s16 *)(p + 4) * D_801F89E0 >> 12) + (&D_801F8A10)[2];
    *(s32 *)(self + 0x48) = (*(s16 *)(p + 6) * D_801F89E0 >> 12) + pa[0];
    *(s32 *)(self + 0x4C) = (*(s16 *)(p + 8) * D_801F89E0 >> 12) + D_801F8A12;
    *(s32 *)(self + 0x50) = (*(s16 *)(p + 0xA) * D_801F89E0 >> 12) + D_801F8A14;
    aec = D_801F8AEC;
    *(s32 *)(self + 0x54) = *(s16 *)(p + 0xC) << 5;
    *(s32 *)(self + 0x08) = aec;
    return 0;
}


s32 func_80181120(u8 *a0, s32 a1, u8 *a2, u8 *a3) {
    a1 = (s16)a1;
    a0 = a0 + a1 * 14;
    if (*(s16 *)(a0 + 0xC) == 0x7FFF) {
        return 1;
    }
    *(u16 *)(a2 + 0) = *(u16 *)(a0 + 0);
    *(u16 *)(a2 + 2) = *(u16 *)(a0 + 2);
    *(u16 *)(a2 + 4) = *(u16 *)(a0 + 4);
    *(u16 *)(a3 + 0) = *(u16 *)(a0 + 6);
    *(u16 *)(a3 + 2) = *(u16 *)(a0 + 8);
    *(u16 *)(a3 + 4) = *(u16 *)(a0 + 0xA);
    return 0;
}



extern void (*D_801F5530[])(void);

void func_80181198(void *a0) {
    D_801F5530[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);



void func_801811D4(void *a0) {

    extern s16 D_801F53BC[][2];
    extern u8 D_801F53E8[];
    extern EffectSlot4_801811D4 D_801F53F4[];
    extern u8 D_801F5420[];
    extern EffectSlot4_801811D4 D_801F5458;
    extern EffectSlot4_801811D4 D_801F5480;
    extern EffectSlot4_801811D4 D_801F5484;
    extern EffectSlot4_801811D4 D_801F54B4;
    extern EffectSlot4_801811D4 D_801F54B8;
    extern EffectSlot4_801811D4 D_801F54E8;
    extern EffectSlot4_801811D4 D_801F54EC;
    extern EffectSlot4_801811D4 D_801F551C;
    extern EffectSlot4_801811D4 D_801F5520;
    register void *s0 __asm__("$16");
    register void *s1 __asm__("$17");

    s0 = a0;
    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)s0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)s0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_801F5420, D_801F53BC[idx][0], D_801F53BC[idx][1]);
        uVar1 = D_801F53E8[*(s32 *)((s32)s0 + 0x2C)];
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
           neighbouring symbol (idiom 7): `&D_801F551C + 4 == &D_801F5520`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)s0 + 0x2C) > 0)
        *(EffectSlot4_801811D4 *)((s32)&D_801F551C + 4) = D_801F53F4[*(s32 *)((s32)s0 + 0x2C)];
        if (COND) { D_801F551C = D_801F5520; } else { D_801F551C = D_801F5520; }
        if (COND) { D_801F54EC = D_801F551C; } else { D_801F54EC = D_801F551C; }
        if (COND) { D_801F54E8 = D_801F54EC; } else { D_801F54E8 = D_801F54EC; }
        if (COND) { D_801F54B8 = D_801F54E8; } else { D_801F54B8 = D_801F54E8; }
        if (COND) { D_801F54B4 = D_801F54B8; } else { D_801F54B4 = D_801F54B8; }
        if (COND) { D_801F5484 = D_801F54B4; } else { D_801F5484 = D_801F54B4; }
#undef COND
        D_801F5480 = D_801F5484;
        D_801F5458 = D_801F5480;

        *(s16 *)((s32)s0 + 0x2) = *(s16 *)((s32)s0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(s0);
    }
}


extern void func_80181414(void);
void func_801813D4(void) {
    func_80181414();
}


extern void func_80146C3C(void);
    void func_801813F4(void) {
        func_80146C3C();
    }



extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);

void func_80181414(void) {

    extern u8 D_801F5438[];
    extern u8 D_801F5460[];
    u8 *p;
    s32 i;

    func_80017254(D_801F5438);
    i = 0;
    p = D_801F5460;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


INCLUDE_ASM("asm/ov_SC06_006/nonmatchings/ov_SC06_006_jr_8017DB90", func_8018146C);


extern s32 func_8014C050(s32 a0, s32 a1);

void func_80181498(void) {

    extern s32 D_80126B58;
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void func_801815DC(void *a0);
extern void func_80181658(void *a0);
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_801814DC(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_801815DC(a0);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_8012931C((struct vec *)a0);

        if (*(s16 *)((s32)a0 + 0x32) == 0) {
            u16 t = *(u16 *)((s32)a0 + 0xA) + 0x1000;
            if (t >= 0x1001) {
                func_801292C8((u8 *)a0);
                return;
            }
        }
    } else {
        func_801292C8((u8 *)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x14) += *(s32 *)((s32)a0 + 0x34);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += *(u16 *)((s32)a0 + 0x30);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x8) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xA) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    func_80181658((void *)*(s32 *)((s32)a0 + 0x20));
}




void func_801815DC(void *a0) {
    s32 *s1;
    s32 *s0;
    u16 v0_const;
    s32 rand_val;
    u16 *val_ptr;

    s1 = (s32 *)a0;
    v0_const = 0x0B;
    __asm__("");
    s0 = *(s32 **)((u8 *)s1 + 0x20);

    
    *(u16 *)((u8 *)s0 + 0x2) = v0_const;

    
    *(s32 *)((u8 *)s0 + 0x4) |= 0x50000000;

    
    if (*(s16 *)((u8 *)s0 + 0x18) == 0) {
        *(s16 *)((u8 *)s0 + 0x18) = 0x600;
    }

    
    rand_val = rand();
    *(u16 *)((u8 *)s0 + 0x14) = (u16)(rand_val & 0xFF0);

    
    val_ptr = (u16 *)((u8 *)s1 + 0x2);
    *val_ptr = *val_ptr + 1;

    
    *(s16 *)((u8 *)s1 + 0x30) = 0x100;
}


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
#define gte_SetRotMatrix(r0) __asm__ volatile (  \
    "lw $12, 0( %0 );"                           \
    "lw $13, 4( %0 );"                           \
    "ctc2 $12, $0;"                              \
    "ctc2 $13, $1;"                              \
    "lw $12, 8( %0 );"                           \
    "lw $13, 12( %0 );"                          \
    "lw $14, 16( %0 );"                          \
    "ctc2 $12, $2;"                              \
    "ctc2 $13, $3;"                              \
    "ctc2 $14, $4"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                          \
    "lw $13, 24( %0 );"                          \
    "ctc2 $12, $5;"                              \
    "lw $14, 28( %0 );"                          \
    "ctc2 $13, $6;"                              \
    "ctc2 $14, $7"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )
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
#define gte_stsz(r0) __asm__ volatile (          \
    "swc2 $19, 0( %0 )"                          \
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
#define RD16(p) (((struct { u16 v; } *)(p))->v)
#define RW32(p) (((struct { u32 v; } *)(p))->v)

void func_80181658(void *a0)
{
    extern u8 D_800AF648;
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern void RotMatrixZ(s32 a0, void *a1);

    u8 stk[0x60];                        /* sp+0x10 .. sp+0x6F */
    u32 flags;
    u32 idx;
    u32 ot;
    u32 t2;
    u8 *pkt;
    u8 *p1;
    u8 *p2;
    u8 *pkb;
    s32 d;
    u32 *otp;
    register u32 tv __asm__("$3");       /* §137 pin — see header */
    register u32 tv2 __asm__("$4");      /* §137 pin — see header */

    u8 *rotm;

    flags = *(u32 *)((s32)a0 + 4);
    rotm = &D_800AF648;

    gte_SetRotMatrix(rotm);
    gte_SetTransMatrix(rotm);
    gte_ldv0((s32)a0 + 8);
    gte_rtps();
    gte_stsxy(stk);
    gte_stflg(stk + 0x48);
    gte_stsz(stk + 0x4c);
    gte_stszotz(stk + 0x50);

    if ((*(u32 *)(stk + 0x48) & 0xFFFFEFFF) == 0) {
        idx = *(s32 *)(stk + 0x50) + 1;
        ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
        {
            u16 flags2 = *(u16 *)((s32)a0 + 0x2c);
            if ((flags2 & 0xC000) != 0) {
                if ((flags2 & 0xC000) == 0xC000) {
                    idx = idx - (flags2 & 0xFFF);
                    if ((s32)idx < 0) idx = 0;
                } else {
                    idx = idx + (flags2 & 0xFFF);
                }
            }
        }

        if (idx < 0x1000) {
            d = (s32)&stk[0x08];

            *(u16 *)(stk + 0x08) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x0a) = 0;
            *(u16 *)(stk + 0x0c) = 0;
            *(u16 *)(stk + 0x0e) = 0;
            *(u16 *)(stk + 0x10) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x12) = 0;
            *(u16 *)(stk + 0x14) = 0;
            *(u16 *)(stk + 0x16) = 0;
            *(u16 *)(stk + 0x18) = 0x1000;
            *(u32 *)(stk + 0x24) = 0;
            *(u32 *)(stk + 0x20) = 0;
            *(u32 *)(stk + 0x1c) = 0;

            RotMatrixZ(*(s16 *)((s32)a0 + 0x14), (void *)d);
            gte_SetRotMatrix((void *)d);
            gte_SetTransMatrix((void *)d);

            *(u16 *)(stk + 0x28) = 0x20;
            *(u16 *)(stk + 0x2a) = 0;
            *(s16 *)(stk + 0x2c) = (s16)*(u32 *)(stk + 0x4c);
            gte_ldv0(stk + 0x28);
            gte_rtps();
            gte_stsxy(stk + 0x54);

            d = (u16)((s16)(RD16(stk + 0x54)) >> 3);
            d |= (s32)((s16)(RD16(stk + 0x56)) >> 3) << 16;

            pkt = D_800A5E60;
            p1 = pkt + 0x18;
            *(u8 *)(pkt + 0x3) = 5;
            *(u8 *)(pkt + 0x7) = 0x28;
            *(u8 *)(p1 + 0x3) = 5;
            t2 = flags & 0x40000000;
            *(u8 *)(p1 + 0x7) = 0x28;
            if (t2 != 0) {
                *(u8 *)(pkt + 0x7) = *(u8 *)(pkt + 0x7) | 2;
                *(u8 *)(p1 + 0x7) = *(u8 *)(p1 + 0x7) | 2;
            }
            *(u8 *)(pkt + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(pkt + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(pkt + 0x6) = *(u8 *)((s32)a0 + 0x26);
            *(u8 *)(p1 + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(p1 + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(p1 + 0x6) = *(u8 *)((s32)a0 + 0x26);

            *(s16 *)(pkt + 0x8) = RD16(stk) + RD16(stk + 0x54);
            *(s16 *)(pkt + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x56);
            *(s16 *)(pkt + 0xc) = RD16(stk) - (d >> 16);
            *(s16 *)(pkt + 0xe) = RD16(stk + 0x02) + d;
            *(s16 *)(pkt + 0x10) = RD16(stk) + (d >> 16);
            *(s16 *)(pkt + 0x12) = RD16(stk + 0x02) - d;
            *(s16 *)(pkt + 0x14) = RD16(stk) - RD16(stk + 0x54);
            *(s16 *)(pkt + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0x8) = RD16(stk) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x54);
            *(s16 *)(p1 + 0xc) = RD16(stk) - d;
            *(s16 *)(p1 + 0xe) = RD16(stk + 0x02) - (d >> 16);
            *(s16 *)(p1 + 0x10) = RD16(stk) + d;
            *(s16 *)(p1 + 0x12) = RD16(stk + 0x02) + (d >> 16);
            *(s16 *)(p1 + 0x14) = RD16(stk) + RD16(stk + 0x56);
            *(s16 *)(p1 + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x54);

            /* addPrim(otp, pkt); addPrim(otp, p1); */
            otp = (u32 *)((idx << 2) + ot);
            tv = RW32(pkt);
            RW32(pkt) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
            tv = RW32(p1);
            RW32(p1) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);

            pkb = D_800A5E60;
            p2 = pkb + 0x30;
            D_800A5E60 = p2;
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p1 & 0xFFFFFF);

            if (t2 != 0) {
                D_800A5E60 = pkb + 0x38;
                *(u8 *)(p2 + 3) = 1;
                RW32(p2 + 4) = ((flags >> 23) & 0x60) | 0xE1000000;
                tv2 = RW32(p2);
                RW32(p2) = (tv2 & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
                RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p2 & 0xFFFFFF);
            }
        }
    }
}



// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_80181CB8(short *pos, int a1, int a2);

void func_80181AF8(unsigned short *param_1, short *param_2, short *param_3,
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
        p = func_80181CB8(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


#include "common.h"

extern int func_80181CB8(short *pos, int a1, int a2);

int func_80181C84(short *pos, int a1, int a2)
{
    int v1 = func_80181CB8(pos, a1, a2);

    if (v1 != 0) {
        *(short *)(v1 + 0x32) = 1;
    }

    return v1;
}


extern u8 *func_801290DC(s32 a0, u8 *a1);

int func_80181CB8(short *pos, int a1, int a2)
{
    u8 *v1;

    v1 = func_801290DC(0x55, (u8 *)pos);

    if (v1 != 0) {
        *(s32 *)(v1 + 0x1C) = pos[3];

        if (a1 != 0) {
            *(s32 *)(v1 + 0x10) = *(s32 *)(a1 + 0x0);
            *(s32 *)(v1 + 0x14) = *(s32 *)(a1 + 0x4);
            *(s32 *)(v1 + 0x18) = *(s32 *)(a1 + 0x8);
            *(s32 *)(v1 + 0x34) = *(s32 *)(a1 + 0xC);
        }

        if (a2 != 0) {
            u8 *ptr = *(u8 **)(v1 + 0x20);
            *(s32 *)(ptr + 0x24) = a2;
        }
    }

    return (int)v1;
}






