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
typedef struct { short m[3][3]; long t[3]; } Mtx_8017DECC;   /* 0x20; .t @ +0x14 */
typedef struct { short vx, vy, vz, pad; } Sv_8017DECC;       /* 0x08 */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80188D84;
extern u8 D_80188CF4;
extern u8 D_80188CD0;
extern u8 D_80188CAC;
extern u8 D_80188D60;
extern u8 D_80188D3C;
extern u8 D_80188D18;
extern u8 D_80188C88;
extern void func_80145934(void);
extern u8 D_80188E14;
extern u8 D_80188DF0;
extern u8 D_80188DCC;
extern u8 D_80188DA8;
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
extern unsigned char D_8018820C[];
extern unsigned char D_8018823C[];
extern unsigned char D_8018828C[];
extern unsigned char D_801882BC[];
extern unsigned char D_801882EC[];
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
extern void (*D_8018833C[])(void *);
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
extern s32 D_80188404[];
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
extern u8 D_8018848C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188494;
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
extern int D_801C6330;
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
extern s32 D_801C6334;
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
extern s32 D_801884C4;
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
extern void (*D_8018856C[])(void);
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
extern void (*D_80188590[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188580;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801885A4[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801885B0[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801885C0[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801885D8[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801885C8;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801885EC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80188608[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801885F8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018861C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188630[])(void);
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
extern s32 D_80188644;
extern void (*D_8018866C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018864C;
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
extern int (*D_801886B8[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801886BC[])(void);
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
extern unsigned short D_80188B20[];
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
extern void (*D_80188B30[])(void);
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
extern int D_801C6368;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188B58[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188B38;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188B48;
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
extern void (*D_80188B98[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188BA0[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188B6C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188BAC[])(void);
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
extern u8 D_80188B7C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C6370;
extern s32 D_801C637C;
extern s32 D_801C6380;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188BE8[])(s32 *);
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
extern s32 D_80188BBC[];
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
extern s32 D_801C6378;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188E38[])(void);
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
extern char D_80188C58[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80188EDC[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189030[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188E4C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189038[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80188E5C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80188E7C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189040[])(void);
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
extern void (*D_80189068[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189074[])(void);
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
extern void (*D_80188EE8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80189118;
extern void func_8015D380(s32 a0);
extern unsigned char D_801881FC[];
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
extern unsigned char D_8018912C[];
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
extern s8 D_80189168[];
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
extern void (*D_801891A0[])(void);
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
extern u16 D_801891B0;
extern u16 D_801891B2;
extern u16 D_801891B4;
extern s32 D_801891B8;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801891C0;
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
extern int D_80188ECC;
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
extern unsigned int D_80189244[];
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
extern void (*D_801892F4[])(void);
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
extern u16 D_80189324[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189388;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C6388[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801893AC[])(void);
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
extern int D_801C63E0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801893F4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801893E4;
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
extern char D_801C5B60[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801893FC[])(void);
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
extern void (*D_80189450[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189418;
extern s16 D_8018944C;
extern s16 D_8018944A;
extern s16 D_80189448;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018945C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C6440;
extern u8 D_801C6441;
extern u8 D_801C6442;
extern u8 D_801C6443;
extern u8 D_801C6444;
extern u8 D_801C6445;
extern u8 D_801C6446;
extern u8 D_801C6447;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018946C[])(void);
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
extern s32 D_801C6480;
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
extern void (*D_801894B0[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018952C[];
extern s32 D_8018954C[];
extern u8 D_801895C8[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801895E8[];
extern u8 D_80189608[];
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
extern void (*D_801896A4[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80189720[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C5B70;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018972C[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80189734[])(void);
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
extern void (*D_801897FC[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018980C[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018981C[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80189828[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189788[];
extern u8   D_8018979C[];
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
extern void (*D_80189840[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80189848[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80189850[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80189858[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80189860[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189868[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189870[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189924[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018992C[])(void);
extern void func_80169F00(void *a0);
extern char D_801898DC[];
extern char D_8018989C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189964[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80189970[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801899B8[])(void);
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
extern void (*D_80189A34[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C67A0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80189A28[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189A6C[];
extern unsigned short D_80189A74[];
extern unsigned short D_80189A7C[];
extern unsigned char D_801C67A8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C67A0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189A84[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C68DC;
extern M2C_UNK D_801C68E0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C6868;
extern void (*D_80189AB4[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C68E4[];
extern u8 D_801C68EC[];
extern u8 D_801C689C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189ABC[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189AD8[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189AE0[])(void);
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
extern void (*D_80189B48[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189AEC;
extern u8 D_80189AF8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80189B7C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189B84[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189BD8[])(void);
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
extern u16 D_80189C0C[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189BFC[];
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
extern s32 D_80189C28;
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
extern void (*D_80189CA0[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189CA8[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189CB0[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189CB8[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189CC0[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189CC8[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189CD4[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189CE0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189CEC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189CFC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189D0C[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189D14[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189D1C[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189D24[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189D2C[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80189D34[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80189D3C[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80189D44[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80189D4C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80189D54[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80189D5C[])(void);
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
extern void (*D_80189D64[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80189D6C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80189D74[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80189D7C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80189D84[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80189D8C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80189D94[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80189D9C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80189DA4[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80189DAC[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80189DB4[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80189DBC[])(void);
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
extern void (*D_80189E00[])(void);
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
extern M2C_UNK D_80189DC4;
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
extern void (*D_80189E30[])(void);
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
extern void (*D_80189E6C[])(void);
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
extern void (*D_80189EC4[])();
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
extern void (*D_80189ED4[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80189EDC[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018A044[])();
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
extern void (*D_8018A050[])();
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
extern M2C_UNK D_801C5DB8;
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
extern s16 D_801C7AB8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C7020;
extern short D_801C7BF4;
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
extern s32 D_801C744C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C7474;
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
extern s16 D_801C7430;
extern s32 func_8017A3B0(void);
extern short D_801C746C;
extern short D_801C7468;
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
extern s16 D_801C7434;
extern u16 D_801C74B4;
extern u16 D_801C74B6;
extern u16 D_801C74B8;
extern void func_8017B1D8(void);
extern s32 func_8017B238(s32 param_1, s32 param_2);
extern s32 func_8017B368(s32 param);
extern s32 func_8017B614(s32 param_1, s32 param_2);
extern void func_8017B7A8(void);
extern s16 D_801C74C4;
extern s16 D_801C74C6;
extern s16 D_801C74C8;
extern s16 D_801C74CC;
extern s16 D_801C74CE;
extern s16 D_801C74D0;
extern void func_8017B824(void);
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C7454;
extern SV4 D_801C745C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C747C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C7478)(void);
extern short D_801C74BC;
extern short D_801C74BE;
extern short D_801C74C0;
extern void func_8017BD50(int param_1);
extern void (*D_8018A22C[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018A264[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_8018A278[])(void);
extern void func_8017C524(void *a0);
extern void (*D_8018A28C[])(void);
extern void func_8017C7C4(void *a0);
extern void func_8017CA80(s32 arg0);
extern void func_8017D960(void);
extern void func_8017DA00(void);
extern void func_8012A094(s32 a0);
extern void func_8017DD2C(void *a0);
extern void func_8017DB44(void);
extern s8 D_8012694C;
extern void func_8017DBA0(void);
extern void func_8017DBDC(void);
extern void func_8017DC04(void);
extern void func_8017DCAC(void);
extern void (*D_8018A294[])(void);
extern s32 func_8017DECC(s32 param_1, s32 param_2);
extern void func_8017DD68(s32 param_1);
extern void func_8017DE24(s32 *a0);
extern void func_8017DE50(s32 *a0);
extern s32 func_80012ABC(s32, s32, s32);
extern void (*D_8018A2F8[])(void);
extern void func_8017E0C0(void *a0);
extern void func_8017E290(void *arg0);
extern s32 func_8017E0FC(s32 param_1);
extern s32 func_8017E14C(void);
extern void (*D_8018A300[])(void);
extern void func_8017E170(void *a0);
extern s32 func_8017E21C(void);
extern void func_800D1EBC(void);
extern void func_8017E270(void);
extern void (*D_8018A47C[])(void);
extern void func_8017E290(void *a0);
extern u8 D_8018A310[];
extern u8 D_8018A390[];
extern u8 D_8018A410[];
extern void func_8017E384(int param_1);
extern void func_8017E4E4(s32 arg0);
extern void (*D_8018A48C[])(void);
extern void func_8017E524(void *a0);
extern void func_8017E560(u8 *a0);
extern Blk8 D_801C60B8;
extern void func_8017E598(void *arg0);
extern void func_8017E608(u8 *a0);
extern void func_8017E6A8(s32 a0);
extern void func_8017E704(void);
extern void func_8017E70C(void);
extern void func_8017E734(void *a0);
extern void func_8017E7C0(void *a0);
extern s16 D_801A3288;
extern void func_8017E8E8(void *arg0);
extern void func_8017E9F8(u8 *a0);
extern void func_8017EA4C(s32 param_1);
extern void func_8018072C();
extern s32 func_8004787C(s32 a0);   /* already declared elsewhere in this TU, same signature */
extern s32 func_80180720(s32 a0);
extern void func_8017EEF4(u8 *a0);
extern s16 D_801C7748;
extern s16 D_8018A6E0;
extern s16 D_8018A6E2;
extern s16 D_801C774A;
extern s16 D_8018A6EA;
extern s16 D_8018A6E8;
extern u16 D_8018A6E4;
extern s16 D_8018A6E6;
extern void func_8017EDBC(u8 *a0);
extern void func_8017F218(void *arg0);
extern void func_8017F26C(s32 *a0);
extern void (*D_8018A798[])(void);
extern void func_8017F294(void *a0);
extern void func_8012A828(s32, void*);
extern void func_8017F2D0(void *arg0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32, s32, s32);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BB3C0[];
extern u8 D_8018A714[];
extern u8 D_8018A6B8[];
extern u8 D_8018A724[];
extern s32 D_8018A568;
extern void func_8017F378(s32 param_1);
extern void func_8017F474(void *a0);
extern s32 func_8012BEE8(s32 arg);
extern void func_8017F520(s32 *a0);
extern void func_8017F558(void);
extern void func_8017F560(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_801270D8;
extern s32 D_8018A7A8[];
extern s32 D_8018A838[];
extern void func_8017F5E4(s32 param_1);
/* ==== end §8b carried decl layer ==== */


extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
extern s32 D_801270D8;

void func_8017F690(s32 param_1)
{
    u8 *s0;

    if (*(s32 *)(param_1 + 0xDC) != ((struct { s32 w; } *)&D_801270D8)->w) {
        *(s32 *)(param_1 + 0xDC) = ((struct { s32 w; } *)&D_801270D8)->w;
        switch (((struct { s32 w; } *)&D_801270D8)->w) {
        case 2:
        case 4:
        case 6:
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
            s0 = func_8012913C(3);
            if (s0 == NULL) {
                return;
            }
            func_80129350((s32)s0, param_1);
            *(u16 *)((s32)s0 + 0xA) -= 0x30;
            break;

        case 3:
        case 5:
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
            break;
        }
    }
}



extern void (*D_8018A8A0[])(void);

void func_8017F768(void *a0) {
    D_8018A8A0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_8018A8A8;
extern s32 D_8018A8B4;

void func_8017F7A4(s32 arg0) {
    s32 s0;

    s0 = *(s32 *)(arg0 + 0x20);
    func_8001CB6C((u8 *)s0, (s32)&D_8018A8A8, 0x2E0, 0);
    *(u8 *)(s0 + 0x27) = 0x9E;
    *(u16 *)(s0 + 0x1A) = 0x4000;
    *(u16 *)(s0 + 0x18) = 0x4000;
    *(u16 *)(s0 + 0x10) = 0x400;
    *(u32 *)(s0 + 4) = *(u32 *)(s0 + 4) | 0x50000000;
    func_80128EA8(s0, arg0 + 0x24, (s32)&D_8018A8B4);
    *(u16 *)(arg0 + 0x2) += 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(void);
void func_8017F83C(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}



extern void (*D_8018A8E4[])(void);

void func_8017F87C(void *a0) {
    D_8018A8E4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_800233CC(void *, unsigned short);

extern s16 D_801C7AC0;   /* fleet-modal spelling (9x in src/); viewed as bytes at the use site */
extern u8 D_801C7AC1;
extern u8 D_801C7AC2;
extern u8 D_801C7AC4;
extern u8 D_801C7AC5;
extern u8 D_801C7AC6;

extern u8 D_801C7B00;
extern u8 D_801C7B01;
extern u8 D_801C7B02;
extern u8 D_801C7B04;
extern u8 D_801C7B05;
extern u8 D_801C7B06;

extern u8 D_801C7B40;
extern u8 D_801C7B41;
extern u8 D_801C7B42;
extern u8 D_801C7B44;
extern u8 D_801C7B45;
extern u8 D_801C7B46;

extern u8 D_801C7830;
extern s32 D_801C7B80;   /* raw word holding a pointer (law 4): cast at the use site */

void func_8017F8B8(void *a0) {
    u8 *pAC0;
    u8 *p40;
    u8 *p00;

    u8 *v1 = func_8012913C(7);

    if (v1 != NULL) {
        *(s16 *)(v1 + 0x6) = 0x20;
        *(s16 *)(v1 + 0xA) = 0x80;
        *(s16 *)(v1 + 0xE) = 0;
    }

    func_8012913C(8);

    pAC0 = (u8 *)&D_801C7AC0;
    D_801C7AC2 = 0xE0;
    D_801C7AC1 = 0xE0;
    *pAC0 = 0xE0;
    D_801C7AC6 = 0;
    D_801C7AC5 = 0;
    D_801C7AC4 = 0;
    func_800233CC(pAC0, 0xE0);

    p00 = &D_801C7B00;
    p40 = &D_801C7B40;
    *p40 = 0xFF;
    *p00 = 0xFF;
    D_801C7B41 = 0xC0;
    D_801C7B01 = 0xC0;
    D_801C7B42 = 0x40;
    D_801C7B02 = 0x40;
    D_801C7B46 = 0;
    D_801C7B45 = 0;
    D_801C7B44 = 0;
    D_801C7B06 = 0;
    D_801C7B05 = 0;
    D_801C7B04 = 0;
    func_800233CC(p00, 0x80);
    func_800233CC(p40, 0x1C0);

    {
        u16 t = *(u16 *)((s32)a0 + 0x2);
        D_801C7B80 = (s32)&D_801C7830;
        *(u16 *)((s32)a0 + 0x2) = t + 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_8017F9F4);

extern void (*D_8018A8EC[])(void);

void func_8017FBD4(void *a0) {
    D_8018A8EC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Local aliases of the PsyQ MATRIX / SVECTOR layouts, following this TU's own
 * house style at func_8017DECC (§183.1 law 8): match_one's standalone compile
 * cannot reach src/shared/, so keep uniquely-named local structs of the same
 * layout instead of colliding with the TU's real typedef names. */
typedef struct { short m[3][3]; long t[3]; } Mtx_8017FC10;   /* 0x20; .t @ +0x14 */
typedef struct { short vx, vy, vz, pad; } Sv_8017FC10;       /* 0x08 */

/* TU-verified declarations (src/ov_SC01_084/ov_SC01_084_jr_8017CA80.c) */
extern s32 ratan2(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void RotMatrixYXZ(void *a0, void *a1);

/* not declared elsewhere in this TU; fleet-wide spelling (§decl_prior) */
extern s16 D_801C7AC0;
extern s32 D_801C7B80;

void func_8017FC10(void *a0)
{
    Mtx_8017FC10 mtx;   /* sp+0x10 */
    Sv_8017FC10 svec;   /* sp+0x30 */
    s32 obj;

    obj = *(s32 *)((s8 *)a0 + 0x20);
    func_8001CD50(obj, (s32)&D_801C7AC0);

    *(s32 *)(obj + 0x34) = D_801C7B80;
    *(s32 *)(obj + 4) |= 0x50000100;

    svec.vx = 0x40;
    svec.vy = (s16)ratan2(*(s16 *)((s8 *)a0 + 6), *(s16 *)((s8 *)a0 + 0xE));
    svec.vz = 0;

    RotMatrixYXZ(&svec, &mtx);

    mtx.t[0] = *(s16 *)((s8 *)a0 + 6);
    mtx.t[1] = *(s16 *)((s8 *)a0 + 0xA);
    mtx.t[2] = *(s16 *)((s8 *)a0 + 0xE);

    *(Mtx_8017FC10 *)D_801C7B80 = mtx;

    {
        u16 t;
        t = *(u16 *)((s8 *)a0 + 2) + 1;
        D_801C7B80 = D_801C7B80 + 0x20;
        *(u16 *)((s8 *)a0 + 2) = t;
    }
}


void func_8017FD24(void) {
}


extern void (*D_8018A8F4[])(void);

void func_8017FD2C(void *a0) {
    D_8018A8F4[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_801C7B00;
extern void func_8001CD9C(int, void *);

void func_8017FD68(param_1)
void *param_1;
{
    s32 obj;

    obj = *(s32 *)((u8 *)param_1 + 0x20);
    func_8001CD9C(obj, &D_801C7B00);
    *(u16 *)((u8 *)param_1 + 2) = *(u16 *)((u8 *)param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_8017FDB0);

extern void (*D_8018A8FC[])(void);

void func_8017FDE0(void *a0) {
    D_8018A8FC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8001CD9C(int, void *);
extern u8 D_801C7B40;

void func_8017FE1C(void *param_1) {
    s32 obj;

    obj = *(s32 *)((u8 *)param_1 + 0x20);
    func_8001CD9C(obj, &D_801C7B40);
    *(u16 *)((u8 *)param_1 + 2) = *(u16 *)((u8 *)param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_8017FE64);


extern void (*D_8018A904[])(void);

void func_8017FF2C(void *a0) {
    D_8018A904[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern u8 D_80191B50[];
extern u8 D_801A1820[];
extern s32 D_801270D8;

void func_8017FF68(s32 param_1)
{
    s32 v0;
    s32 v1;

    *(s32 *)(param_1 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(v0, (s32)D_80191B50);
    func_8012A828(param_1, D_801A1820);
    *(s16 *)(param_1 + 0x2) = 1;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4) |= 0x80000000;
    v1 = D_801270D8;
    *(s32 *)(param_1 + 0xE0) = 0;
    *(s32 *)(param_1 + 0xE4) = 1;
    *(s32 *)(param_1 + 0xDC) = v1;
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80180000);

extern void (*D_8018A90C[])(void);

void func_801801BC(void *a0) {
    D_8018A90C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s16 D_801C7748;

s32 func_801801F8(s32 a0) {
    s32 temp;
    s32 val;

    temp = D_801C7748 + 0xC00;
    val = *(s16 *) (a0 + 0x2);
    if (val >= -0x60) {
        val = 0;
    } else if (val < -0x601) {
        val = 0x3000;
    } else {
        val = (val + 0x20) * 0x3000 / -0x600;
    }
    if ((temp - val >= 0) ? ((temp - val) < 0x21) : ((val - temp) < 0x21)) {
        return 1;
    }
    return 0;
}


extern s16 D_801C7748;

s32 func_8018028C(s32 a0) {
    s32 val;
    s32 temp;

    temp = D_801C7748;
    val = *(s16 *) (a0 + 0xA);
    if (val >= -0x60) {
        val = 0;
    } else if (val < -0x601) {
        val = 0x3000;
    } else {
        val = (val + 0x20) * 0x3000 / -0x600;
    }
    temp -= val;
    if (temp < 0x100) {
        return temp < -0xBFF;
    }
    return 1;
}


#include "common.h"

/* func_80180300 -- draws the three debug world axes.  For each axis
 * (X = 0x0000FF, Y = 0x00FF00, Z = 0xFF0000) it walks 8 segments of 0x100
 * units.  Per segment it emits four lines through func_8012D4B4(ctx, &from,
 * &to, colour):  the segment a->b, a +/-0x10 tick across b, and then the same
 * pair mirrored onto the NEGATIVE half-axis.  `a` and `b` are 8-byte SVECTORs
 * living at sp+0x10 and sp+0x18.
 *
 * TWO SHAPE NOTES (both byte-load-bearing):
 *
 * 1. The tick block reloads b from memory (lhu 0x18/0x1a/0x1c) and stores the
 *    +0x10 value TWICE (to b's tick field and to a's).  flow.c's last_mem_set
 *    only kills *adjacent* identical-address stores, so the source order must
 *    be `b.vK += 0x10;` then the fieldwise copy `a = b` then `a.vK -= 0x20;`.
 *
 * 2. The negative half-axis writes the negation INLINE at the store site
 *    (`a.vx = -p;`), it does NOT reassign p/q (`p = -p; q = -q;`).  This is a
 *    sched1 birthing-boost lever, not cosmetics -- see below.
 */

/* Provided by the destination TU at line 3253 with an identical body; the gate
 * strips this copy (structurally-equal duplicate typedef).  Kept so the draft
 * compiles standalone. */


extern void func_8012D4B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);


void func_80180300(s32 arg0) {
    Sv_8017DECC a;
    Sv_8017DECC b;
    s32 i;
    short p;
    short q;

    for (i = 0; i < 8; i++) {
        p = i << 8;
        q = (i + 1) << 8;
        a.vx = p;
        a.vy = 0;
        a.vz = 0;
        b.vx = q;
        b.vy = 0;
        b.vz = 0;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF);
        b.vy += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vy -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF);
        a.vx = -p;
        a.vy = 0;
        a.vz = 0;
        b.vx = -q;
        b.vy = 0;
        b.vz = 0;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF);
        b.vy += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vy -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF);
    }

    for (i = 0; i < 8; i++) {
        p = i << 8;
        q = (i + 1) << 8;
        a.vx = 0;
        a.vy = p;
        a.vz = 0;
        b.vx = 0;
        b.vy = q;
        b.vz = 0;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF00);
        b.vz += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vz -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF00);
        a.vx = 0;
        a.vy = -p;
        a.vz = 0;
        b.vx = 0;
        b.vy = -q;
        b.vz = 0;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF00);
        b.vz += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vz -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF00);
    }

    for (i = 0; i < 8; i++) {
        p = i << 8;
        q = (i + 1) << 8;
        a.vx = 0;
        a.vy = 0;
        a.vz = p;
        b.vx = 0;
        b.vy = 0;
        b.vz = q;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF0000);
        b.vy += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vy -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF0000);
        a.vx = 0;
        a.vy = 0;
        a.vz = -p;
        b.vx = 0;
        b.vy = 0;
        b.vz = -q;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF0000);
        b.vy += 0x10;
        a.vx = b.vx; a.vy = b.vy; a.vz = b.vz;
        a.vy -= 0x20;
        func_8012D4B4(arg0, (s32) &a, (s32) &b, 0xFF0000);
    }

}

/* WHY `a.vx = -p;` AND NOT `p = -p; a.vx = p;`  (the 18-diff residual, cracked)
 * ---------------------------------------------------------------------------
 * sched1 schedules each basic block BACKWARD (sched.c schedule_block: `last =
 * next_tail`, then `PREV_INSN(last) = insn`), picking ready[0], so the insn
 * ranked HIGHEST is placed LAST.  The whole loop body is ONE basic block (calls
 * are not block boundaries), so in the window between call 2 and call 3 the
 * ready set after the six `sh` stores are placed is {negu, negu, a0..a3}.
 *
 * With `p = -p; q = -q;` the two negu insns write pseudos that are set TWICE in
 * the function (once by `p = i << 8`, once by the negation).  birthing_insn_p
 * (sched.c:2469) requires `reg_n_sets[i] == 1`, so they get no adjust_priority
 * boost; the arg set-ups -- which carry an anti-dependence on the previous
 * CALL_INSN and therefore inherit its priority -- outrank them, get picked
 * first, and land LAST.  Result: `negu, negu, a0, a1, a2, a3` (18 diffs).
 *
 * Writing the negation at the store site creates a FRESH single-set pseudo per
 * negation.  reg_n_sets == 1 and the dest is live at that point, so
 * adjust_priority raises it to max_priority: the negus now outrank the arg
 * set-ups, are picked first, and are placed LAST -- i.e. AFTER the four arg
 * insns.  Exactly the target's `a0, a1, a2, a3, negu, negu`.
 *
 * Ablations that do NOT work (all still 18 diffs):
 *   - `{ short np = -p; short nq = -q; ... }` -- a declared narrow local
 *     re-truncates and does not present as the birthing insn.
 *   - `__asm__ __volatile__("")` before OR after the negation (194-A): a fence
 *     splits the region but does not change the rank INSIDE it.
 * The lever is the SET COUNT of the negation's destination, nothing else.
 */


extern void (*D_8018A990[])(void);

void func_80180614(void *a0) {
    D_8018A990[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180650(s32 a0, s32 out) {
    s32 t;
    s32 x;
    s32 y;
    s32 angle;
    s32 q1;
    s32 q2;
    s32 sinVal;
    s32 cosVal;

    t = a0;
    x = -(t * 1536);
    y = -(t * 160);
    angle = t & 0xFFF;
    q1 = x / 12288 - 0x22;
    q2 = y / 12288 + 0x260;

    sinVal = func_80047948(angle) * q2 >> 12;
    cosVal = func_8004787C(angle) * q2 >> 12;

    *(s16 *)(out + 0) = sinVal;
    *(s16 *)(out + 2) = q1;
    *(s16 *)(out + 4) = cosVal;
}


s32 func_80180720(s32 a0) {
    return -a0 & 0xFFF;
}


extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018072C(s32 a0, s32 a1, s32 out) {
    s32 t;
    s32 x;
    s32 angle;
    s32 q1;
    s32 sinVal;
    s32 cosVal;

    t = a0;
    x = -(t * 1536);
    angle = t & 0xFFF;
    q1 = x / 12288 - 0x22;

    sinVal = func_80047948(angle) * a1 >> 12;
    cosVal = func_8004787C(angle) * a1 >> 12;

    *(s16 *)(out + 0) = sinVal;
    *(s16 *)(out + 2) = q1;
    *(s16 *)(out + 4) = cosVal;
}


#include "common.h"

extern s32 ratan2(s32 a0, s32 a1);

/* camera / target position pair: two s16 at 0x800D3918 (x) and 0x800D391C (z).
   D_800D3918 is spelled `u8 []` by this TU (law 2); D_800D391C is absent from
   the whole tree, so it follows the same rawest-form spelling (law 4). */
extern u8 D_800D3918[];
extern u8 D_800D391C[];

s32 func_801807D8(s16 *arg0) {
    s32 ang[6];
    s32 d[6];
    s32 a;
    s32 r;

    a = (ratan2(*(s16 *)D_800D391C - arg0[2], arg0[0] - *(s16 *)D_800D3918) - 0x400) & 0xFFF;
    a = (-a - 0x400) & 0xFFF;

    if (a >= 0xC00 && arg0[1] >= -0x80) {
        return 0;
    }

    ang[0] = -(a * 1536) / 12288 - 0x22;
    ang[1] = -((a + 0x1000) * 1536) / 12288 - 0x22;
    ang[2] = -((a + 0x2000) * 1536) / 12288 - 0x22;

    if (arg0[1] >= -0x60) {
        return 0;
    }
    if (arg0[1] < -0x601) {
        return 0x3000;
    }

    d[0] = arg0[1] - ang[0];
    if (d[0] < 0) {
        d[0] = -d[0];
    }
    d[1] = arg0[1] - ang[1];
    if (d[1] < 0) {
        d[1] = -d[1];
    }
    d[2] = arg0[1] - ang[2];
    if (d[2] < 0) {
        d[2] = -d[2];
    }

    if (d[0] == 0) {
        r = 0;
    } else if (d[1] == 0) {
        r = 0x1000;
    } else if (d[2] == 0) {
        r = 0x2000;
    } else if (d[0] < d[1] && d[0] < d[2]) {
        r = 0;
    } else if (d[1] < d[2]) {
        r = 0x1000;
    } else {
        r = 0x2000;
    }

    return a | r;
}


#include "common.h"

/* func_801809C4 — ov_SC01_084 / ov_SC01_084_jr_8017CA80  — MATCH (190 ins)
 *
 * Builds a 6-vertex "fan" around obj (3 iterations x 2 vertices, each vertex
 * from the polar helper func_8012B0B4), projects all six through RotTransPers,
 * averages the six OTZs (/6 -> the 0x2AAAAAAB magic), then emits TWO
 * semi-transparent POLY_G4 primitives (len 8 => tag 0x08000000, code 0x3A,
 * 0x24 bytes each, one 0x48 alloc) that share one gouraud colour ramp, links
 * both into D_800A651C[D_800B9A02].a at otz*4 and closes with
 * func_8012E28C(otz, 1).
 *
 * Byte-forced shape notes (the four levers that got this from 183 -> 0):
 *
 *  1. §190-A — the second vertex of each pair is reached as
 *     `k = (i + 3) * 8; e = (SVec *)((u8 *)base + k);` with the offset as its
 *     OWN NAMED STATEMENT.  Writing `base[i + 3].x` instead lets combine_givs
 *     merge both groups into ONE address giv (all six MEMs off $s0), which
 *     drops `$fp` entirely and shrinks the frame by 8 (obj then stays in a
 *     callee-saved reg instead of spilling to 0x70(sp)).  The named form is
 *     what produces the target's `addiu $fp,$sp,0x10` + `addu $s0,$fp,$zero`
 *     + `addu $v1,$fp,$s4` triple.
 *
 *  2. sched.c true_dependence (NEW, see index_gap) — `D_8018A9A4/6` must be
 *     declared as ARRAYS and read as `[0]`.  As plain scalar globals their
 *     MEM is (not-in-struct, non-varying address), so true_dependence()'s
 *     second drop-clause kills the dependence against the in-struct varying
 *     stores to base[i] and sched1 hoists `lh $a2,%lo(D_8018A9A6)` eight slots,
 *     above the three `sh`.  An ARRAY_REF sets MEM_IN_STRUCT_P on the load,
 *     the drop-clause no longer applies, and the load lands where the target
 *     has it — immediately before the jal.  Same symbol, same reloc, 0 bytes.
 *
 *  3. Chained assignment `p[0]->f = p[1]->f = val;` for the four paired
 *     zero/colour writes.  Written as two separate statements gcc reloads one
 *     pointer per store (load, store, load, store + hazard nops); the chained
 *     form evaluates both lvalue addresses first, giving the target's
 *     `lw 0x58 / lw 0x5C / <store p[1]> / <store p[0]>` pairing.  `p` is a
 *     2-element local ARRAY on purpose: that is what forces the pointers to
 *     memory and makes every store re-kill the cse of the next read (§193-E).
 *
 *  4. Two register pins.  `c` -> $v0 collapses c and c>>16 (and the colour
 *     ramp's or/and/srl chain) onto one register exactly as the target does;
 *     `pb` -> $s1 with a "memory"-clobbering zero-byte re-tie (§189-C) both
 *     stops reload from rematerialising `la $17,D_800B9A02` after the first
 *     AddPrim AND pins the `la` into the last load-delay slot instead of an
 *     earlier one.  Without the clobber the la floats 4 slots early
 *     (position in the source is irrelevant — verified at 4 sites).
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_801809C4;      /* 0x14 stride */
typedef struct { s16 x, y, z, pad; } SVec_801809C4;      /* 0x08 stride */

typedef struct {
    s16 unk0;      /* 0x00 — the shared vy of every generated vertex */
    s16 unk2;      /* 0x02 — base angle                              */
    u32 unk4;      /* 0x04 — packed colour (b in bits 16..23)        */
} Obj_801809C4;

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012E32C(void);
extern void *func_80010A08(s32);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern s32 AddPrim(s32 a0, void *a1);
extern void func_8012E28C(s32 arg0, s32 arg1);

void func_801809C4(Obj_801809C4 *obj) {
    /* All four data externs are BLOCK scope: engine_core.h's DEFINE_ macros
     * declare D_800A651C scalar inside their own bodies, and the overlay
     * table trio is spelled as arrays only here (see note 2 above), so keeping
     * them local avoids a file-scope clash with any sibling function. */
    extern short D_800B9A02;                  /* TU spelling, line 2470 */
    extern OtBlk_801809C4 D_800A651C[];
    extern s16 D_8018A998[];                  /* [0..2] + [3..5] angle offsets */
    extern s16 D_8018A9A4[];                  /* radius for the [0..2] vertices */
    extern s16 D_8018A9A6[];                  /* radius for the [3..5] vertices */

    SVec_801809C4 v[6];       /* 0x10 */
    s32 sxy[6];               /* 0x40 */
    u8 *p[2];                 /* 0x58 */
    u32 buf[2];               /* 0x60 */
    s32 pp;                   /* 0x68 */
    s32 flag;                 /* 0x6C */
    s32 i;
    s32 otz;
    s32 cy;
    s32 ang;
    register u32 c __asm__("$2");
    u32 col;
    register u16 *pb __asm__("$17");
    SVec_801809C4 *base;
    SVec_801809C4 *e;
    s32 k;

    cy = obj->unk0;
    ang = obj->unk2;
    base = v;
    for (i = 0; i < 3; i++) {
        func_8012B0B4(buf, ang - D_8018A998[i], D_8018A9A4[0]);
        c = buf[0];
        base[i].x = c;
        base[i].y = cy;
        c = (s32)c >> 16;
        base[i].z = c;
        func_8012B0B4(buf, ang - D_8018A998[i + 3], D_8018A9A6[0]);
        c = buf[0];
        k = (i + 3) * 8;
        e = (SVec_801809C4 *)((u8 *)base + k);
        e->x = c;
        e->y = cy;
        c = (s32)c >> 16;
        e->z = c;
    }

    func_8012E32C();
    otz = 0;
    for (i = 0; i < 6; i++) {
        otz += RotTransPers((s32)&v[i], (s32)&sxy[i], &pp, &flag);
    }
    otz = otz / 6;

    p[0] = (u8 *)func_80010A08(0x48);   /* two POLY_G4 back to back */
    p[1] = p[0] + 0x24;

    col = obj->unk4;
    *(s32 *)(p[0] + 0x04) = *(s32 *)(p[1] + 0x04) = 0;   /* rgb0 */
    *(s32 *)(p[0] + 0x0C) = *(s32 *)(p[1] + 0x0C) = 0;   /* rgb1 */

    /* rgb2 = colour with the top byte scaled 7/8; rgb3 = rgb2 >> 2 (masked) */
    c = ((((col >> 16) * 7) / 8) << 16) | (col & 0xFFFF);
    *(s32 *)(p[0] + 0x14) = *(s32 *)(p[1] + 0x14) = c;
    c = (c & 0xFCFCFC) >> 2;
    *(s32 *)(p[0] + 0x1C) = *(s32 *)(p[1] + 0x1C) = c;

    p[0][7] = 0x3A;                          /* POLY_G4 | semi-trans */
    *(s32 *)(p[0] + 0x00) = 0x8000000;       /* tag: len 8           */
    p[1][7] = 0x3A;
    *(s32 *)(p[1] + 0x00) = 0x8000000;

    *(s32 *)(p[0] + 0x08) = sxy[0];          /* xy0..xy3 of prim 0 */
    *(s32 *)(p[0] + 0x10) = sxy[3];
    *(s32 *)(p[0] + 0x18) = sxy[1];
    *(s32 *)(p[0] + 0x20) = sxy[4];
    *(s32 *)(p[1] + 0x08) = sxy[2];          /* xy0..xy3 of prim 1 */
    *(s32 *)(p[1] + 0x10) = sxy[5];
    *(s32 *)(p[1] + 0x18) = sxy[1];
    *(s32 *)(p[1] + 0x20) = sxy[4];

    pb = (u16 *)&D_800B9A02;
    __asm__("" : "=r"(pb) : "0"(pb) : "memory");   /* 0 bytes — see note 4 */
    AddPrim(D_800A651C[*pb].a + otz * 4, p[0]);
    AddPrim(D_800A651C[*pb].a + otz * 4, p[1]);
    func_8012E28C(otz, 1);
}


void func_80180CBC(s32 param_1) {
    extern void func_8012A828(s32, void *);
    extern s32 D_80186B78;
    extern s16 D_8018A9D0;
    extern s16 D_8018A9D2;
    extern s16 D_801C774C;

    s32 ptr;
    s32 tmp;

    func_8012A828(param_1, &D_80186B78);
    *(s16 *)(param_1 + 2) = 2;
    *(s32 *)(param_1 + 0xDC) = D_8018A9D0;
    ptr = *(s32 *)(param_1 + 0x20);
    *(s32 *)(param_1 + 0xE0) = D_8018A9D2;
    *(s32 *)(param_1 + 0xE4) = 0;
    tmp = *(volatile s32 *)(param_1 + 0xE4);
    *(s16 *)(param_1 + 0xFC) = 0x18;
    *(s16 *)(ptr + 0x10) = (s16)tmp;
    *(s32 *)(param_1 + 0x1C) = 0x12C;
    D_801C774C = 1;
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);

void func_80180D38(s32 param_1) {

    extern M2C_UNK D_80186B78;
    extern s16 D_8018A9D0;
    extern s16 D_8018A9D2;
    extern s16 D_801C774C;

    s32 v0, v1;
    register s32 a0v __asm__("$4");
    register s32 dir __asm__("$5");

    if (*(s32 *)(param_1 + 0xE4) > 0) {
        dir = 0;
        v0 = *(s32 *)(param_1 + 0xDC);
        v1 = *(s32 *)(param_1 + 0xE0);
        v0 = v0 - v1;
    } else {
        dir = 1;
        v0 = *(s32 *)(param_1 + 0xDC);
        v1 = *(s32 *)(param_1 + 0xE0);
        v0 = v0 + v1;
    }
    *(s32 *)(param_1 + 0xDC) = v0;
    v0 = *(s32 *)(param_1 + 0xE4);
    v1 = *(s32 *)(param_1 + 0xDC);
    a0v = *(s32 *)(param_1 + 0x20);
    v0 = v0 + v1;
    *(s32 *)(param_1 + 0xE4) = v0;
    *(s16 *)(a0v + 0x10) = (s16)v0;

    if (*(s32 *)(param_1 + 0xE4) <= 0) {
        if (dir == 1) goto tail;
    } else {
        if (dir == 0) goto tail;
    }

    v0 = *(s32 *)(param_1 + 0xDC);
    if (v0 > 0) {
        if (v0 - 3 >= 0) goto tail;
    } else {
        if (v0 + 3 <= 0) goto tail;
    }

    func_8012A828(param_1, &D_80186B78);
    *(s16 *)(param_1 + 0x2) = 2;
    *(s32 *)(param_1 + 0xDC) = D_8018A9D0;
    *(s32 *)(param_1 + 0xE0) = D_8018A9D2;
    *(s32 *)(param_1 + 0xE4) = 0;
    *(s16 *)(param_1 + 0xFC) = 0x18;
    a0v = *(s32 *)(param_1 + 0x20);
    *(s16 *)(a0v + 0x10) = (s16)*(s32 *)(param_1 + 0xE4);
    *(s32 *)(param_1 + 0x1C) = 0x12C;
    D_801C774C = 1;

tail:
    *(s32 *)(param_1 + 0x24) = *(s16 *)(param_1 + 0x6);
    *(s32 *)(param_1 + 0x28) = *(s16 *)(param_1 + 0xA);
    *(s32 *)(param_1 + 0x2C) = *(s16 *)(param_1 + 0xE);
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80180E74);

extern s16 D_8018A91A;

void func_801812F4(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 4;
    *(s16 *)&D_8018A91A = -1;
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80181310);

extern void (*D_8018AA2C[])(void);
extern s16 D_801C774C;
extern s16 D_801C7748;
extern s16 D_801C774A;
extern s16 D_801C774E;
extern s16 D_801C7750;
extern s16 D_801C7752;
extern s16 D_8018A914;
extern s16 D_8018A916;
extern s16 D_8018A91A;
extern s16 D_8018A918;
extern s32 D_80126B9C;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 D_801270DC;
extern s32 D_801270E0;
extern s32 D_80126D50;
extern s32 D_801270D8;
extern s32 D_801270E4;
extern s32 D_801270E8;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern int func_8001AAA0(void);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_80181310(void);
extern void func_8017E70C(void);
extern void func_8012B21C(void *a0);
extern void func_80174824(void);
extern void func_80175454(void);

void func_801814E8(void *a0)
{
    s16 buf[3];
    s32 t;
    s32 w;

    D_8018AA2C[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x2) != 0) {
        if (D_801C774C > 0) {
            *(s16 *)&D_8018A914 = *(s32 *)((s32)a0 + 0x24);
            *(s16 *)&D_8018A916 = *(s32 *)((s32)a0 + 0x28);
            w = *(s32 *)((s32)a0 + 0x2C);
            *(s16 *)&D_8018A91A = 0;
            *(s16 *)&D_8018A918 = w;
        }
        if (D_80126B9C & 0x8000000) {
            buf[0] = D_80126B5E;
            buf[1] = D_80126B62;
            buf[2] = D_80126B66;
            D_801C7748 = func_801807D8(buf);
            D_801C774A = func_80047D3C((s32)(s16)buf[0] * (s32)(s16)buf[0] +
                                       (s32)(s16)buf[2] * (s32)(s16)buf[2]);
            if (D_801C774E < D_801C7748) {
                D_801C774E = D_801C7748;
            }
        }
        if (D_801C774C == 1) {
            if (D_801C7748 >= 0x1E80) {
                t = 0x7F;
            } else {
                t = 0x7F - ((0x1E80 - D_801C7748) * 0x7F) / 0x1E80;
            }
            func_8002D4C8(0x4BD, ((t | 0x1000) & 0xFFFF));
        }
        if (D_801C7752 == 1) {
            if (D_801C7750 == 0) {
                func_8002D4C8(1, 0);
            }
            D_801C7750 = D_801C7750 + 1;
            if ((s16)D_801C7750 >= 0x52 && ((int (*)(int))func_8001AAA0)(0x12) != 0) {
                D_801C7752 = 2;
            }
        }
        if (D_801270DC != 1) {
            if (D_801270DC < 2 && D_801270DC == 0 && D_801C7748 >= 0x1AE6) {
                D_801270DC = 1;
                func_8017E70C();
            }
        } else {
            D_801270E0 = D_801270E0 + 1;
            if (D_80126D50 == 0) {
                D_801270DC = 2;
                D_801270E0 = 0;
            }
        }
        func_80181310();
        if (D_801C774C == 1 && D_801270D8 == 0 && D_801C7748 >= 0x23F0 &&
            D_801270E4 <= 0) {
            D_801270E8 = D_801270E8 - 1;
            if (D_801270E8 <= 0) {
                D_801270E8 = 0x1E;
                func_8012C658(0x1D, 2, 0);
                D_801270E4 = D_801270E4 + 1;
            }
        }
    }
    if (*(u16 *)((s32)a0 + 0x2) == 2 && (*(u16 *)((s32)a0 + 0x5C) & 1)) {
        if (*(u16 *)((s32)a0 + 0x5E) == 0x10) {
            *(s16 *)((s32)a0 + 0x5C) = 0;
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
            *(s16 *)((s32)a0 + 0x2) = 3;
            func_8012B21C(a0);
            *(s32 *)((s32)a0 + 0x1C) = 0x27;
            *(s16 *)((s32)a0 + 0x34) = 0;
            *(s16 *)((s32)a0 + 0xFE) = *(u16 *)((s32)a0 + 0xA);
            D_801C774C = 2;
            func_8002D4C8(0x4BD, 0x1000);
            func_80174824();
            D_801270D8 = 1;
            func_80175454();
        } else {
            *(u16 *)((s32)a0 + 0x5C) &= ~1;
        }
    }
}


void func_801818E0(void *arg0) {
    extern void func_8012A828(s32, void*);
    extern s32 D_801A18C8;

    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A18C8);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x28;
}


void func_80181920(void* a0)
{
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_801A1A10;

    *(s16 *)(a0 + 2) = 3;
    *(s16 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x1C) = 0x3C;
    func_8012A828(a0, &D_801A1A10);
    *(s16 *)(a0 + 0xDC) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
}


void func_80181978(void *arg0) {
    extern void func_80142414(void *a0, s32 a1);
    extern s32 D_801A1B40;

    func_8012A828((s32)arg0, &D_801A1B40);
    *(s16 *)((u8 *)arg0 + 0x2) = 4;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x19;
    func_80142414(arg0, -0x96);
    func_8002D4C8(0x6A9, 0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B21C(void *a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 D_8018AA4C;
extern void (*D_8018AA48)(void);
extern void D_801A1AB8;

void func_801819D0(s32 a0) {
    struct {
        s32 w0;
        s32 w1;
        void (*w2)(void);
    } sp10;

    sp10.w0 = 0;
    sp10.w1 = 0;
    sp10.w2 = D_8018AA48;
    func_8012A828(a0, &D_801A1AB8);
    *(s16 *)(a0 + 2) = 5;
    *(s32 *)(a0 + 0x1C) = D_8018AA4C;
    func_8012B21C((void *)a0);
    func_8012B14C(a0, (s32)((u8 *)&sp10));
    *(s16 *)(a0 + 0xFC) = 0;
}



extern void (*D_8018AA50[])(void);

void func_80181A40(void *a0) {
    D_8018AA50[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80181A7C);

void func_80181DEC(s32 param_1) {
    extern s32 rand(void);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_801A18C8;
    extern s32 D_801A1A10;
    extern s32 func_80047D3C(s32 a0);
    extern s32 func_801807D8(s16 *a0);
    s16 sp10[3];
    s32 t;
    u16 m;
    u16 y;
    u16 f;
    u16 g;

    if ((rand() & 1) != 0) {
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);
        m = *(u16 *)(param_1 + 0x5C);
        y = *(u16 *)(param_1 + 6);
        f = *(u16 *)(param_1 + 0xFC);
        *(s32 *)(param_1 + 0x1C) = 0xA;
        t = (s32)(s16)y * (s32)(s16)y;
        *(u16 *)(param_1 + 0x5E) = 0;
        g = m | 0x8000;
        *(u16 *)(param_1 + 0x5C) = g;
        *(u16 *)(param_1 + 0xFC) = f ^ 1;
        sp10[0] = y;
        sp10[1] = *(u16 *)(param_1 + 0xA);
        sp10[2] = *(u16 *)(param_1 + 0xE);
        t += (s32)(s16)sp10[2] * (s32)(s16)sp10[2];
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(t);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(sp10);
    } else {
        *(s16 *)(param_1 + 2) = 5;
        func_8012A828(param_1, &D_801A18C8);
        *(s32 *)(param_1 + 0x1C) = 0x28;
    }
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80181ED4);

extern void func_8012A828(s32 a0, void *a1);
extern void D_801A1AB8;

void func_80181F3C(s32 a0) {
    *(u16 *)(a0 + 0x5C) = 0xAA00;
    func_8012A828(a0, &D_801A1AB8);
    *(s16 *)(a0 + 2) = 3;
    *(s16 *)(a0 + 0xFE) = 0;
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80181F80);

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_801822A4);

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80182328);

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_801826C4);

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80182A00);


// @class: plumbing
// @stuck: none — MATCH (30 ins)

extern unsigned char D_801A2400[];

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_80143CD4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern int func_800CB0E8(int param);

void func_80182D3C(int param_1)
{
    *(short *)(param_1 + 2) = 12;
    ((int (*)(int, void *))func_8012A828)(param_1, &D_801A2400);
    ((int (*)(int))func_8012B23C)(param_1);
    *(int *)(param_1 + 0x1c) = 0x78;
    ((int (*)(int))func_80143CD4)(param_1);
    ((int (*)(int, int))func_8002D4C8)(0x47b, 0);
    ((int (*)(int, int))func_8002D4C8)(0x478, 0);
    func_800CB0E8(param_1);
    *(char *)(param_1 + 0xc1) = 6;
}


extern unsigned char D_801A24C8;
extern void func_8012A828(s32, void*);

void func_80182DB4(param_1)
int param_1;
{
    *(short *)(param_1 + 2) = 7;
    *(short *)(param_1 + 0x5c) = 0;
    func_8012A828(param_1, &D_801A24C8);
    *(int *)(param_1 + 0x1c) = 0x1e;
}


void func_80182DF8(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0xB;
        *(short *)((char *)a0 + 0x5C) = 0;
        *(int *)((char *)a0 + 0x1C) = 0x1E;
        *(short *)((char *)a0 + 0x98) = 0;
    }


#include "common.h"

/* Declarations follow the destination TU (ov_SC01_084_jr_8017CA80.c) house style,
 * verified against the fleet-wide idiom at ov_SC02_027_jr_8017AE2C.c:3651 etc.
 *   func_8012CBCC  fleet-canonical `void (s32)`; callers that need the s32 return
 *                  value cast the pointer at the use site (e.g.
 *                  ov_SC02_027_jr_8017D898.c:5522, engine_core.h idiom 9).
 *   func_8012BEE8  matches this TU's own decl at line 3546 (`s32 (s32)`).
 *   func_8012B23C  matches this TU's own decl at line 3892 (`void (s32)`).
 *   func_8002D4C8  matches this TU's own decl at line 3894/59 (`void (s32,s32)`).
 *   func_80013328  matches this TU's own decl at line 521 (`s32 (s32,s32)`),
 *                   fleet-canonical call shape `func_80013328(a0+4,(s32)&D_80126B5C)`
 *                   verified at ov_SC02_027_jr_8017AE2C.c:3651 and dozens of sibling
 *                   overlay TUs (the seq-volume-lookup idiom).
 *   D_80126B5C     fleet-canonical `extern u8 D_80126B5C;` passed as `(s32)&D_80126B5C`.
 *   func_80182F90  same-TU sibling defined later in this file (INCLUDE_ASM at
 *                  line 3923); forward-declared here.
 */
extern void func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80013328(s32 a0, s32 a1);
extern u8 D_80126B5C;
extern void func_80182F90(s32 a0);

void func_80182E14(s32 a0) {
    s32 s0 = a0;
    u16 state = *(u16 *)(s0 + 0x34);

    switch (state) {
    case 0: {
        s32 p;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) + 0xE0;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
        if (((s32 (*)(s32))func_8012CBCC)(s0) == 0) {
            return;
        }
        {
            s32 vol = func_80013328(s0 + 4, (s32)&D_80126B5C);

            if (vol < 0) {
                vol = 0;
            }
            if (vol > 0x300) {
                vol = 0x300;
            }
            vol = (0x300 - vol) * 127 / 0x300;
            if (vol < 0) {
                vol = 0;
            }
            if (vol > 0x7F) {
                vol = 0x7F;
            }
            func_8002D4C8(0x43B, (vol | 0x1000) & 0xFFFF);
        }
        func_8012B23C(s0);
        p = *(s32 *)(s0 + 0x20);
        *(s32 *)(s0 + 0x14) = 0xFFF00000;
        *(u16 *)(p + 0x10) = 0;
        *(u16 *)(s0 + 0x34) = 1;
        return;
    }
    case 1: {
        s32 p;

        if (((s32 (*)(s32))func_8012CBCC)(s0) == 0) {
            return;
        }
        func_8012B23C(s0);
        p = *(s32 *)(s0 + 0x20);
        *(u16 *)(s0 + 0x34) = 2;
        *(u16 *)(p + 0x10) = 0;
        *(s32 *)(s0 + 0x1C) = 0xA;
        return;
    }
    case 2:
        if (func_8012BEE8(s0) == 0) {
            return;
        }
        func_80182F90(s0);
        return;
    }
}


extern u8 D_801A21E0[];

void func_80182F90(s32 a0)
{
    s32 v1;

    *(s16 *)(a0 + 0x2) = 0xE;
    *(u16 *)(a0 + 0x34) = 0;
    func_8012A828(a0, D_801A21E0);
    v1 = *(s32 *)(a0 + 0x20);
    *(u16 *)(a0 + 0x5C) = 0xAA00;
    *(u16 *)(a0 + 0x5E) = 0;
    *(u16 *)(v1 + 0x14) = 0;
    *(u16 *)(v1 + 0x10) = 0;
    func_8012B23C(a0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801A21E0[];
extern u8 D_801A2848[];

void func_80182FEC(s32 param_1)
{
    s32 v1;

    *(s16 *)(param_1 + 2) = 0xE;
    *(u16 *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, D_801A21E0);
    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 0x5C) = 0xAA00;
    *(u16 *)(param_1 + 0x5E) = 0;
    *(u16 *)(v1 + 0x14) = 0;
    *(u16 *)(v1 + 0x10) = 0;
    func_8012B23C(param_1);
    func_8012A828(param_1, D_801A2848);
    *(s32 *)(param_1 + 0x1C) = 0x1E;
    *(u16 *)(param_1 + 0x34) = 1;
}


#include "common.h"

extern s32 D_801270D8;
extern s32 D_801270D4;
extern s32 D_801270E4;
extern u8 D_8018AA6C[];
extern u8 D_801A2940[];
extern u8 D_801A21E0[];
extern u8 D_801A2848[];

extern void func_8012C098(void *a0);
extern s32 func_801845EC(s32 a0, s32 a1);
extern s32 func_80185E68(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80183068(void *a0)
{
    s32 v1 = *(u16 *)((s32)a0 + 0x34);

    switch (v1) {
    case 0:
        if ((*(u16 *)((s32)a0 + 0x72) & 0x4000) != 0) {
            func_8012A828((s32)a0, D_801A2848);
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            *(u16 *)((s32)a0 + 0x34) = 1;
        }
        break;
    case 1:
    case 2:
    case 3:
        if (D_801270D8 != 0) {
            if (*(s16 *)((s32)a0 + 0x70) == 2) {
                D_801270E4 -= 1;
            } else {
                D_801270D4 -= 1;
            }
            func_8012C098(a0);
        } else {
            s32 state = *(s32 *)((s32)a0 + 0x1C);
            if (state == 0xC) {
                func_801845EC((s32)a0, 0);
            } else if (state == 0xF) {
                func_80185E68((s32)a0, (s32)D_8018AA6C);
            }
            if (func_8012BEE8((s32)a0) != 0) {
                *(s32 *)((s32)a0 + 0x1C) = 0x1E;
                *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
                __asm__("" ::: "memory");
                if (*(u16 *)((s32)a0 + 0x34) == 4) {
                    func_8012A828((s32)a0, D_801A2940);
                }
            }
        }
        break;
    case 4:
        if ((*(u16 *)((s32)a0 + 0x72) & 0x4000) != 0) {
            s32 p20;
            *(s16 *)((s32)a0 + 2) = 0xE;
            *(u16 *)((s32)a0 + 0x34) = 0;
            func_8012A828((s32)a0, D_801A21E0);
            p20 = *(s32 *)((s32)a0 + 0x20);
            *(u16 *)((s32)a0 + 0x5C) = 0xAA00;
            *(u16 *)((s32)a0 + 0x5E) = 0;
            *(u16 *)(p20 + 0x14) = 0;
            *(u16 *)(p20 + 0x10) = 0;
            func_8012B23C((s32)a0);
            func_8012A828((s32)a0, D_801A2848);
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            *(u16 *)((s32)a0 + 0x34) = 1;
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80183244);

void func_801834B8(u16 *param_1) {
    extern void func_80182A00();
    extern void (*D_8018AB4C[])(void *);

    if (param_1[1] != 0 && (param_1[0x2E] & 1)) {
        func_80182A00();
    }
    if (param_1[0] != 0) {
        D_8018AB4C[param_1[1]](param_1);
    }
}


#include "common.h"

/* Card func_8018353C — fresh mass-lane crack (no banked twin). Shape and house
 * style adopted from same-TU neighbour func_80183A7C (shares func_8012AD80,
 * func_8012B14C, func_8012B608, func_8012B77C) — same "load 3 u16 globals into
 * two stack scratch structs, dispatch table entry + init call, then feed a
 * position/rotation triad through func_8012B77C, poke the result into a linked
 * struct at param_1+0x20" skeleton. See docs/matching-cookbook.md for the
 * general pattern. */

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8  D_8018AB8C[];

extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_801838F0(void *arg0);

void func_8018353C(s32 param_1) {
    register s32 a2val __asm__("$6");
    register s32 v1val __asm__("$3");
    register s32 a3val __asm__("$7");
    s32 v0;
    register s32 s0 __asm__("$16");
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 outVal;
    s32 v1;

    a2val = D_80126B5E;
    v1val = D_80126B62;
    a3val = D_80126B66;

    buf1[0] = (s16)a2val;
    buf1[1] = (s16)v1val;
    buf1[2] = (s16)a3val;

    v0 = *(s16 *)(param_1 + 0x70);
    v1val = v1val - 0x40;
    v0 = v0 << 5;
    v1val = v1val - v0;
    buf1[1] = (s16)v1val;

    s0 = *(s16 *)(param_1 + 0x70);

    *((s16 *)&in3[0] + 1) = (s16)a2val;
    *((s16 *)&in3[1] + 1) = (s16)v1val;
    *((s16 *)&in3[2] + 1) = (s16)a3val;

    s0 = (s0 << 2) + 6;

    func_8012B14C(param_1, (s32)D_8018AB8C);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, s0);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;

    if (*(s16 *)(param_1 + 0x70) == 0) {
        func_801838F0((void *)param_1);
    }
}


#include "common.h"

extern s16 D_801C7748;
extern s16 D_801C774A;
extern s16 D_8018AB98;
extern s16 D_8018AB9A;
extern u16 D_8018AB9C;
extern s16 D_8018AB9E;
extern s16 D_8018ABA0;

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80183630(s32 a0) {
    register s32 sum1 __asm__("$17");
    register s32 sum2 __asm__("$18");
    register s32 frac __asm__("$19");
    register s32 threshold __asm__("$16");
    s32 ret;
    s32 val0;
    u16 tmp[3];
    s32 cnt1;
    s32 cnt2;
    s32 ptr;
    s32 k5;

    sum1 = D_801C7748 + D_8018AB98;
    frac = sum1 & 0xFFF;
    sum2 = D_801C774A;
    sum2 += D_8018AB9A;

    threshold = -(sum1 * 1536) / 12288 - 0x22;

    ret = func_80047948(frac);
    val0 = (ret * sum2) >> 12;

    ret = func_8004787C(frac);
    k5 = D_8018ABA0;
    tmp[0] = val0;
    tmp[1] = threshold;
    tmp[2] = (ret * sum2) >> 12;

    cnt1 = *(s32 *)(a0 + 0x1C);
    tmp[1] -= D_8018AB9C + k5 * cnt1;

    *(s16 *)(a0 + 0x6) = tmp[0];
    *(s16 *)(a0 + 0xA) = tmp[1];
    *(s16 *)(a0 + 0xE) = tmp[2];

    ptr = *(s32 *)(a0 + 0x20);
    *(s16 *)(ptr + 0x12) = ((-sum1) & 0xFFF) + 0x400;

    cnt2 = *(s32 *)(a0 + 0x1C) + 1;
    *(s32 *)(a0 + 0x1C) = cnt2;

    if (cnt2 >= D_8018AB9E) {
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    }
}


#include "common.h"

/* Row-specific tuning constants for this instance (family group with func_80183630/func_80183AF0 etc.
   each hardcodes its OWN row of a 5 x s16 table spaced 0xC apart -- not an indexed array access in
   this TU, see wave card notes). Types by access width (law 2 -- absent from this TU). */
extern s16 D_801C7748;
extern s16 D_801C774A;
extern s16 D_8018ABA4;
extern s16 D_8018ABA6;
extern u16 D_8018ABA8;
extern s16 D_8018ABAA;
extern s16 D_8018ABAC;

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80183790(s32 a0) {
    register s32 sum1 __asm__("$18");
    register s32 sum2 __asm__("$17");
    register s32 frac __asm__("$19");
    register s32 threshold __asm__("$16");
    s32 ret;
    s32 val0;
    u16 tmp[3];
    s32 cnt1;
    s32 cnt2;
    s32 ptr;
    s32 k5;

    sum1 = D_801C7748 + D_8018ABA4;
    frac = sum1 & 0xFFF;
    sum2 = D_801C774A;
    sum2 += D_8018ABA6;

    threshold = -(sum1 * 1536) / 12288 - 0x22;

    ret = func_80047948(frac);
    val0 = (ret * sum2) >> 12;

    ret = func_8004787C(frac);
    k5 = D_8018ABAC;
    tmp[0] = val0;
    tmp[1] = threshold;
    tmp[2] = (ret * sum2) >> 12;

    cnt1 = *(s32 *)(a0 + 0x1C);
    tmp[1] -= D_8018ABA8 + k5 * cnt1;

    *(s16 *)(a0 + 0x6) = tmp[0];
    *(s16 *)(a0 + 0xA) = tmp[1];
    *(s16 *)(a0 + 0xE) = tmp[2];

    ptr = *(s32 *)(a0 + 0x20);
    *(s16 *)(ptr + 0x12) = (-sum1) & 0xFFF;

    cnt2 = *(s32 *)(a0 + 0x1C) + 1;
    *(s32 *)(a0 + 0x1C) = cnt2;

    if (cnt2 >= D_8018ABAA) {
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    }
}


extern void func_8012A828(s32, void*);
extern M2C_UNK D_8018A568;

void func_801838F0(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_8018A568);
    *(s16 *)((s32)arg0 + 0x2) = 0x3;
    *(s16 *)((s32)arg0 + 0x34) = 0;
}


#include "common.h"

/* Structural twin of func_80183A7C (0.9704 similarity) in this TU: same
 * angle/sin/cos setup, same buf1/in3 layout, same call sequence, differing
 * only in the literal constants (offset, multiplier, data symbol, and the
 * two magic args at the tail). */

extern s16 D_801C7748;
extern u8  D_8018ABB0[];

extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_80013478(s32 a0, s32 a1);

void func_8018392C(s32 param_1) {
    s32 t;
    s32 x;
    s32 s2;
    s32 angle;
    s32 s1;
    s32 v0dead;
    s32 angle2;
    s32 r1;
    s32 sinVal;
    s32 r2;
    s32 cosVal;
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 v0;
    s32 v1;
    s32 outVal;

    t = D_801C7748 + 0x400;
    x = -(t * 1536);
    angle = t & 0xFFF;
    s2 = 0x180;
    s1 = x / 12288;

    r1 = func_80047948(angle);
    sinVal = (r1 * s2) >> 12;

    r2 = func_8004787C(angle);
    cosVal = (r2 * s2) >> 12;

    v0dead = s1 - 0x22;
    angle2 = s1 - 0x32;

    buf1[0] = (s16)sinVal;
    *(volatile s16 *)&buf1[1] = (s16)v0dead;
    buf1[1] = (s16)angle2;
    *((s16 *)&in3[0] + 1) = (s16)sinVal;
    *((s16 *)&in3[1] + 1) = (s16)angle2;
    buf1[2] = (s16)cosVal;
    *((s16 *)&in3[2] + 1) = (s16)cosVal;

    func_8012B14C(param_1, (s32)D_8018ABB0);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, 6);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;
    v0 = func_80013478(posPtr, (s32)buf1);

    v1 = 0x28;
    if (v0 < 0x1000) {
        v0 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1C) = v1;
        v0 = v0 + 1;
        *(u16 *)(param_1 + 0x34) = (s16)v0;
    }
}


#include "common.h"

/* Card func_80183A7C — fresh mass-lane crack (no banked twin, no cookbook hit
 * found for this shape). Layout derived purely from the target .s; struct/
 * field types are unknown so raw byte-offset casts are used throughout,
 * matching this TU's own established idiom (see func_80186688 etc.). */

extern s16 D_801C7748;
extern s16 D_801C774A;
extern u8  D_8018ABBC[];

extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_80013478(s32 a0, s32 a1);

void func_80183A7C(s32 param_1) {
    s32 t;
    s32 x;
    s32 s2;
    s32 angle;
    s32 s1;
    s32 v0dead;
    s32 angle2;
    s32 r1;
    s32 sinVal;
    s32 r2;
    s32 cosVal;
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 v0;
    s32 v1;
    s32 outVal;

    t = D_801C7748 + 0x200;
    x = -(t * 1536);
    angle = t & 0xFFF;
    s2 = D_801C774A;
    s1 = x / 12288;

    r1 = func_80047948(angle);
    sinVal = (r1 * s2) >> 12;

    r2 = func_8004787C(angle);
    cosVal = (r2 * s2) >> 12;

    v0dead = s1 - 0x22;
    angle2 = s1 - 0x32;

    buf1[0] = (s16)sinVal;
    *(volatile s16 *)&buf1[1] = (s16)v0dead;
    buf1[1] = (s16)angle2;
    *((s16 *)&in3[0] + 1) = (s16)sinVal;
    *((s16 *)&in3[1] + 1) = (s16)angle2;
    buf1[2] = (s16)cosVal;
    *((s16 *)&in3[2] + 1) = (s16)cosVal;

    func_8012B14C(param_1, (s32)D_8018ABBC);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, 4);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;
    v0 = func_80013478(posPtr, (s32)buf1);

    v1 = 0x78;
    if (v0 < 0x1000) {
        v0 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1C) = v1;
        v0 = v0 + 1;
        *(u16 *)(param_1 + 0x34) = (s16)v0;
    }
}


#include "common.h"

/* Declarations copied verbatim from src/ov_SC01_084/ov_SC01_084_jr_8017CA80.c:
 *   func_80047D3C  @270,  func_80047948 @2207, func_8004787C @2208,
 *   func_8012B8E4  @4181, func_8012BEE8 @4182, func_8012A828 @3891,
 *   D_8018A568     @4003 (file-scope M2C_UNK spelling).
 * func_801807D8 has no C prototype in the TU (still INCLUDE_ASM @3668). */
extern s32 func_801807D8(s16 *a0);
extern s32 func_80047D3C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_8018A568;

void func_80183BD0(s32 param_1) {
    s16 tmp[3];
    s32 t;
    s32 ss;
    s32 sq0;
    s32 sq1;
    s32 s2;
    s32 frac;
    s32 threshold;
    s32 sinRaw;
    s32 cosRaw;
    s32 sinVal;
    s32 cosVal;
    s32 ptr;
    s32 v0;
    unsigned short *p;

    tmp[0] = *(u16 *)(param_1 + 0x6);   /* +0x06 vel.x  */
    tmp[1] = *(u16 *)(param_1 + 0xA);   /* +0x0A vel.y  */
    tmp[2] = *(u16 *)(param_1 + 0xE);   /* +0x0E vel.z  */

    t = func_801807D8(tmp);
    sq0 = (s32)tmp[0] * (s32)tmp[0];
    sq1 = (s32)tmp[2] * (s32)tmp[2];
    ss = sq0 + sq1;
    s2 = func_80047D3C(ss);

    /* §193-B LEVER (this is the whole match): `t -= 4` is written BELOW the
     * func_80047D3C call.  combine.c:929 refuses to combine across a CALL_INSN,
     * so the `addu $s0,$v0,$zero` return-value copy survives as its own insn and
     * the subtract stays a separate `addiu $s0,$s0,-0x4` (90 ins, not 89).
     * sched2 then sinks BOTH of them into the second mult->mflo interlock slot,
     * reproducing the target's `mult ; addu s0 ; addiu s0 ; mflo` filler order.
     * Writing `t -= 4` above the call (or fencing it with a zero-byte __asm__)
     * either folds to one `addiu $s0,$v0,-4` or leaves only ONE filler before
     * the mflo -- both were tried and both miss. */
    t -= 4;

    frac = t & 0xFFF;
    threshold = -(t * 1536) / 12288;

    sinRaw = func_80047948(frac);
    sinVal = (sinRaw * s2) >> 12;

    cosRaw = func_8004787C(frac);
    cosVal = (cosRaw * s2) >> 12;

    tmp[0] = (s16)sinVal;
    /* §194-J: the target really does store 0x12($sp) twice back-to-back
     * (sh $v0 then sh $s1); the first store must be volatile or flow.c's
     * last_mem_set deletes it. */
    *(volatile s16 *)&tmp[1] = (s16)(threshold - 0x22);
    tmp[1] = (s16)(threshold - 0x32);
    tmp[2] = (s16)cosVal;

    *(s16 *)(param_1 + 0x6) = tmp[0];
    *(s16 *)(param_1 + 0xA) = tmp[1];
    *(s16 *)(param_1 + 0xE) = tmp[2];

    v0 = func_8012B8E4(param_1, 8);
    ptr = *(s32 *)(param_1 + 0x20);
    p = (unsigned short *)(ptr + 0x12);
    *p = (unsigned short)(*p + v0);

    if (func_8012BEE8(param_1) != 0) {
        func_8012A828(param_1, &D_8018A568);
        *(s16 *)(param_1 + 0x2) = 3;
        *(s16 *)(param_1 + 0x34) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80183D38);

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80183DA4);

extern void func_8012B21C(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_80126B62;

void func_80184090(void *a0) {
    u16 t;

    t = *(u16 *)((s32)a0 + 0x5C);
    *(u16 *)((s32)a0 + 0x2) = 2;
    *(u16 *)((s32)a0 + 0x34) = 0;
    *(u16 *)((s32)a0 + 0x5C) = t & 0x7FFE;
    func_8012B21C(a0);
    *(s32 *)((s32)a0 + 0x1C) = 0;
    *(u16 *)((s32)a0 + 0x24) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)((s32)a0 + 0x28) = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)((s32)a0 + 0x26) = D_80126B62;
    func_8002D4C8(0x4B4, 0);
}



extern void (*D_8018AC10[])(void);

void func_801840FC(void *a0) {
    D_8018AC10[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80184138);


extern void (*D_8018AC2C[])(void);

void func_80184424(void *a0) {
    D_8018AC2C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Card func_80184460 — fresh mass-lane crack (no banked twin, no cookbook hit).
 * Layout derived purely from the target .s; struct/field types unknown so raw
 * byte-offset casts are used throughout, matching this TU's own established
 * idiom (see func_80183A7C / func_8017DECC etc).
 *
 * TU-adopted signatures (law 2 — verified by grep against this TU):
 *   func_8012B0B4(unsigned int *, int, int)   void   (TU:3728)
 *   func_8012AD80(s32)                        void   (TU:4028)
 *   func_8012C218(void *)                     void   (TU:4547)
 *   func_8012E32C(void)                       void   (TU:3729)
 *   RotTransPers(s32, s32, s32 *, s32 *)      s32    (TU:3731)
 *   D_80126B62                                u16    (TU:1795/3263), read via
 *                                             the TU's own (s32)(s16) idiom
 * func_801845A0 is the next INCLUDE_ASM stub in this same TU (TU:4129) — no
 * declaration exists anywhere in the TU, so it is typed from this call site.
 * D_801C774C / D_80126CBA / D_801270CC are likewise undeclared in this TU and
 * are typed by this function's own access widths (lh/lh/sw -> s16/s16/s32).
 * Other overlays' TUs give D_801C774C/D_801270CC different types — that is
 * different overlay-local data at the same relocatable offset, not evidence.
 *
 * ---- THE LEVER (second-pass repair; new cookbook candidate) --------------
 * The first pass parked at closeness=40 on a BRANCH-POLARITY/LENGTH-DRIFT
 * residual: the D_80126CBA test wants
 *     beqz -> .L80184510 / fallthrough = {li 1; sh 0xFC; j .L80184520}
 *              .L80184510: {call func_801845A0; j epilogue}
 * but EVERY spelling of the inner if/else (both polarities, explicit gotos,
 * shared-epilogue goto) compiled to the inverted, block-SWAPPED shape
 * (bnez -> store-block / fallthrough = call).
 *
 * Root cause found in the compiler source: jump.c:1799 "Look for
 * if (foo) bar; else break;" — a RANGE-SWAP that inverts the condjump and
 * physically splices the two arms when
 *     JUMP_LABEL(insn) == next_label(insn) == label1, LABEL_NUSES(label1)==1,
 *     range1 ends in a simplejump to label2 == next_label(label1),
 *     range2 ends in a jump followed by a BARRIER.
 * Our if/else satisfies all of those, so the swap is unavoidable ONCE IT IS
 * REACHED. But the guard is `! first` (jump.c:1818): jump_optimize's
 * `while (changed)` loop only clears `first` at the END of a round
 * (jump.c:2037), so the swap can only fire in round 2+ — i.e. only if
 * SOMETHING ELSE IN THE FUNCTION changed in round 1.
 *
 * `if (X) goto L;` and mid-function `return;` both expand to a conditional
 * jump around an unconditional jump, which jump.c:1737 collapses in round 1 —
 * that single change is what enabled round 2 and swapped our arms. Writing
 * the whole guard chain as nested/&&-joined ifs (no goto, no early return
 * except the one the target itself needs) leaves jump pass 1 with NOTHING to
 * do in round 1, the loop exits, and the arms stay in source order.
 * ⇒ Class name for §31: "jump.c:1799 range-swap, armed by a round-1 change".
 *    The C dial is NOT the if's polarity — it is REMOVING the unrelated
 *    goto/early-return elsewhere in the function.
 *
 * The $v0/$v1 pins are still load-bearing (a separate, real regalloc-order
 * residual in the func_8012AD80 setup block: without them the 0x64 reloads
 * and the a0 copy reorder, 11 mismatches).
 */
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012E32C(void);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_801845A0(void *a0);
extern u16 D_80126B62;
extern s16 D_801C774C;
extern s16 D_80126CBA;
extern s32 D_801270CC;

void func_80184460(void *a0) {
    void *s0;
    void *v0p;
    s32 buf[2];      /* sp+0x10..0x17 — reused below as the u16 triple for
                       * func_8012E32C / RotTransPers' input vector */
    s32 sxy;         /* sp+0x18 */
    s32 pp;          /* sp+0x1c */
    s32 flag;        /* sp+0x20 */
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    s0 = a0;

    v0p = *(void **)((u8 *)s0 + 0x20);
    func_8012B0B4((unsigned int *)buf, *(s16 *)((u8 *)v0p + 0x12), 0x18);

    /* offset 0x64 is re-dereferenced (not cached) — matches this TU's
     * per-access raw-cast idiom and the target's two separate loads. */
    v1 = buf[0];
    v0 = *(u16 *)((u8 *)*(void **)((u8 *)s0 + 0x64) + 0x6);
    v0 = v0 + v1;
    *(s16 *)((u8 *)s0 + 0x6) = v0;
    v0 = *(u16 *)((u8 *)*(void **)((u8 *)s0 + 0x64) + 0xE) + (v1 >> 16);
    *(s16 *)((u8 *)s0 + 0xE) = v0;
    func_8012AD80((s32)s0);

    if (*(s16 *)((u8 *)s0 + 0xFC) == 0 &&
        *(s16 *)((u8 *)s0 + 0xA) <= (s32)(s16)D_80126B62 &&
        D_801C774C == 1) {
        if (D_80126CBA != 0) {
            *(s16 *)((u8 *)s0 + 0xFC) = 1;
        } else {
            func_801845A0(s0);
            return;
        }
    }

    if (*(s16 *)((u8 *)s0 + 0xFC) == 1) {
        *(u16 *)((u8 *)buf + 0x0) = *(u16 *)((u8 *)s0 + 0x6);
        *(u16 *)((u8 *)buf + 0x2) = *(u16 *)((u8 *)s0 + 0xA);
        *(u16 *)((u8 *)buf + 0x4) = *(u16 *)((u8 *)s0 + 0xE);
        func_8012E32C();

        RotTransPers((s32)buf, (s32)&sxy, &pp, &flag);

        if (*((s16 *)&sxy + 1) < -0x6F) {
            D_801270CC = 0;
            func_8012C218(s0);
        }
    }
}


void func_801845A0(void *arg0) {
    extern void func_8012A828(s32, void*);
    extern s32 D_801A2750;

    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A2750);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x1E;
    *(s16 *)((u8 *)arg0 + 0x34) = 0;
    *(s16 *)((u8 *)arg0 + 0xFC) = 1;
}


struct S845EC_in { s16 f00, f02, f04, f06, f08, f0A, f0C, f0E; s32 f10; };
struct S845EC_out { s16 a, b, c; };

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern u8 D_8018AA6C[];

s32 func_801845EC(s32 a0, s32 a1)
{
    s32 s1;
    struct S845EC_in in;
    struct S845EC_out out;

    func_8012F214(a0, (s32)&D_8018AA6C[a1 * 8], (s32)&out);
    in.f00 = out.a;
    in.f02 = out.b;
    in.f04 = out.c;
    in.f06 = 0x20;
    in.f08 = a1;
    in.f0A = 0;
    in.f10 = 0;
    in.f0E = 0;
    s1 = func_8012C51C((void *)&in, a0);

    if (a1 == 0 && s1 != 0) {
        s32 t = *(s32 *)(a0 + 0x20);
        if (t != 0) {
            *(unsigned short *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(unsigned short *)(t + 0x12);
        }
        func_8012B2CC(s1);
    }
    return s1;
}


#include "common.h"

/* wave_p31z func_801846B4 — mass lane, fresh crack.
 * Seed twin: md_SC07_003:func_801A27A4 (sim 0.5714) — same S80190C84_846B4 "spawn
 * record" struct + func_8012C51C tail, minus the tmp.fC assignment (target
 * asm never writes sp+0x24, so that field is left uninitialized on purpose).
 * TU-neighbour func_80184C90 supplies the "*p = *p + v" accumulate idiom and
 * the int param_1 / raw-pointer-cast house style adopted throughout.
 * S80190C84/SV3 are real shared/engine_types.h types (src/shared/engine_types.h:612,1337);
 * re-declared locally here per the md_SC07_003.c precedent since this standalone
 * draft can't reach the src/shared/ include path. */

struct S80190C84_846B4 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};

typedef struct { short a, b, c; } SV3_846B4;

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_80185E68(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32, void*);
extern void func_8012B200(u8 *a0);

extern s32 D_8018AA74;
extern s32 D_801A2378;
extern s32 D_8018AC34;

void func_801846B4(int param_1)
{
    s32 t;
    s32 cond;
    s32 v;
    unsigned short *p;

    {
        unsigned int buf;
        func_8012B0B4(&buf, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), 0x18);
        t = (s32)buf;
    }

    *(s16 *)(param_1 + 0x6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x6) + t;
    *(s16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE) + (t >> 16);
    v = func_8012B8E4(param_1, 4);

    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);

    cond = *(s32 *)(param_1 + 0x1C);
    if (cond == 0x11) {
        func_80185E68(param_1, (s32)&D_8018AA74);
    } else if (cond == 0xF) {
        struct S80190C84_846B4 tmp;
        SV3_846B4 out;

        func_8012F214(param_1, (s32)&D_8018AA74, (s32)&out);
        tmp.f0 = out.a;
        tmp.f2 = out.b;
        tmp.f4 = out.c;
        tmp.f6 = 0x20;
        tmp.f8 = 1;
        tmp.fA = 0;
        tmp.f10 = 0;
        tmp.fE = 0;
        func_8012C51C(&tmp, param_1);
    }

    if (func_8012BEE8(param_1) != 0) {
        func_8012A828(param_1, (void *)&D_801A2378);
        *(s16 *)(param_1 + 0x2) = 1;
        func_8012B200((u8 *)param_1);
        *(s32 *)(param_1 + 0x14) = D_8018AC34;
    }
}


extern void (*D_8018AC38[])(void);

void func_801847F8(void *a0) {
    D_8018AC38[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80184834);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern void (*D_8018A984[])(void);
extern void (*D_8018A978[])(void);

void func_80184908(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(v0, (s32)D_8018A984[*(s16 *)(param_1 + 0x70)]);
    func_8012A828(param_1, ((void **)D_8018A978[*(s16 *)(param_1 + 0x70)])[*(s16 *)(param_1 + 0xFC)]);
    *(u16 *)(param_1 + 2) = 1;
}


extern s32 func_8012BEE8(s32);
    extern void func_80180CBC(s32);
    void func_801849A0(s32 arg0) {
        if (func_8012BEE8(arg0)) {
            func_80180CBC(arg0);
        }
    }


void func_801849D8(void *a0) {
        M2C_FIELD(a0, s16 *, 0xA) = -0x4BD;
    }


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8005C2C8(s32 a0, s32 a1);
extern u8 D_801BE010[];
extern s32 D_80186B78;
extern u8 D_8018A9C0[];
extern s16 D_8018A91A;
extern s16 D_801C7748;

void func_801849E4(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    *(u32 *)(v0 + 4) |= 0x70000000;
    func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801BE010);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xBE, 0xD0);
    *(s32 *)(param_1 + 0x58) = (s32)D_8018A9C0;
    *(u16 *)(param_1 + 0x5C) |= 0x8000;
    D_8018A91A = -1;
    func_8012A828(param_1, &D_80186B78);
    *(u16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 0x14;
    *(s32 *)(param_1 + 0xE0) = 0;
    *(s32 *)(param_1 + 0xDC) = 0;
    func_8012B2CC(param_1);
    *(s32 *)(param_1 + 0xCC) = func_8012C588(0x17, 0);
    func_8005C2C8((s32)&D_801C7748, 0xC);
}


extern void func_8012CBA4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_801818E0();
void func_80184AD0(s32 a0) {
    func_8012CBA4(a0);
    if (func_8012BEE8(a0)) {
        func_801818E0(a0);
    }
}


extern void (*D_8018AA40)(void *);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80181978(void *a0);
extern void func_80181920(void *a0);

void func_80184B10(s32 *a0)
{
    s32 s1 = (s32)D_8018AA40;
    if (func_8012BEE8((s32)a0) != 0) {
        if (func_8012BD3C((s32)a0, 0x400, s1 * s1) != 0) {
            func_80181978(a0);
        } else {
            func_80181920(a0);
        }
    }
}


#include "common.h"

extern void func_8012CBA4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B21C(void *a0);

extern s32 D_8018AA44;
extern u8 D_801A1820[];

void func_80184B80(s32 a0) {
    s32 sp10[3];
    s32 ret;
    s32 v0;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = D_8018AA44;

    if (*(u16 *)(a0 + 0x34) == 0) {
        v0 = *(s32 *)(a0 + 0x20);
        ret = func_8012B608(*(s16 *)(v0 + 0x12), *(s16 *)(a0 + 0xDC) + 0x800, 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += ret;
        if (*(s32 *)(a0 + 0x1C) == 0x28) {
            *(u16 *)(a0 + 0x34) = 1;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (*(u16 *)(a0 + 0xDC) + 0x800) & 0xFFF;
            func_8012B2CC(a0);
            func_8012B21C((void *)a0);
            func_8012B14C(a0, (s32)sp10);
        }
    } else {
        /* TU declares func_8012CBA4 void (line 4162); this call site uses the
         * return value, so adopt the TU prototype and cast at the call (idiom9). */
        if (((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) {
            *(s32 *)(a0 + 0x14) = 0;
        }
    }

    if (func_8012BEE8(a0)) {
        func_8012A828(a0, D_801A1820);
        *(s16 *)(a0 + 0x2) = 1;
        func_8012B21C((void *)a0);
        *(s32 *)(a0 + 0x1C) = 0x14;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801819D0(s32 a0);

void func_80184C90(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        func_801819D0(param_1);
    }
}


extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B21C(void *a0);
extern u8 D_801A1820[];

void func_80184CE8(s32 a0) {
    u16 timer;

    timer = *(u16 *)(a0 + 0xFC) - 1;
    *(u16 *)(a0 + 0xFC) = timer;
    if ((s16)timer <= 0) {
        func_80143B6C(a0, 0);
        *(u16 *)(a0 + 0xFC) = 8;
    }
    if (((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) {
        *(s32 *)(a0 + 0x14) = 0;
    }
    if (func_8012BEE8(a0)) {
        func_8012A828(a0, D_801A1820);
        *(u16 *)(a0 + 2) = 1;
        func_8012B21C((void *)a0);
        *(s32 *)(a0 + 0x1C) = 0x14;
    }
}


void func_80184D88(void) {
}

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B21C(void *a0);
extern s32 func_80143970(s32 a0);

void func_80184D90(void *a0) {
    extern u8 D_80191B50[];
    extern u8 D_801A1820[];
    s32 v0;
    s32 v1;
    s32 v2;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&(*(s32 *)D_80191B50));
        v1 = *(s32 *)((s32)a0 + 0x20);
        v2 = *(u16 *)((s32)a0 + 0xA);
        v1 = *(u16 *)(v1 + 0x12);
        v2 = v2 - 0x80;
        *(u16 *)((s32)a0 + 0xA) = v2;
        *(u16 *)((s32)a0 + 0xDC) = v1;
        func_80143970((s32)a0);
        func_8012A828((s32)a0, (s32)&D_801A1820);
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012B21C(a0);
        *(s32 *)((s32)a0 + 0x1C) = 0x14;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern s32 D_801A1A10;

void func_80184E28(s32 param_1)
{
    s16 tmp[3];
    s32 sq;

    if (func_8012BEE8(param_1) != 0) {
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);
        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(u16 *)(param_1 + 0x5C) |= 0x8000;
        *(u16 *)(param_1 + 0x5E) = 0;
        *(u16 *)(param_1 + 0xFC) ^= 1;
        tmp[0] = *(s16 *)(param_1 + 0x6);
        tmp[1] = *(s16 *)(param_1 + 0xA);
        tmp[2] = *(s16 *)(param_1 + 0xE);
        sq = (tmp[0] * tmp[0]) + (tmp[2] * tmp[2]);
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(sq);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(tmp);
    }
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80142414(void *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80181F3C(s32 a0);

void func_80184EEC(s32 param_1)
{
    s32 v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (*(s32 *)(param_1 + 0x1C) == 0xF) {
        func_8002D4C8(0x6A9, 0);
        func_80142414((void *)param_1, -0x78);
    }
    if (func_8012BEE8(param_1) != 0) {
        func_80181F3C(param_1);
    }
}


extern void func_8012E364(void);
    void func_80184F6C(void) {
        func_8012E364();
    }


extern s32 func_8012E470(s32 a0);
extern s32 func_8012E4C8(void *a0);
void func_80184F8C(int param_1)
{
    if (((int (*)(void))func_8012E470)() != 0) {
        ((void (*)(int))func_8012E4C8)(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (clean structural stub)

extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern unsigned char D_801A24C8;

void func_80184FC4(int param_1)
{
    ((void (*)(void))func_8012BEE8)();
    if (*(int *)(param_1 + 0x1c) == 1) {
        func_8012A828(param_1, &D_801A24C8);
    }
    return;
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182FEC(int param_1);
extern void D_801A1AB8;

void func_8018500C(int param_1)
{
    int iVar1;

    iVar1 = func_8012BEE8((s32)param_1);
    if (iVar1 != 0) {
        if (*(s16 *)(param_1 + 0x70) == 2) {
            func_80182FEC(param_1);
        } else {
            *(u16 *)(param_1 + 0x5e) = 0;
            *(u16 *)(param_1 + 0x5c) = 0xAA00;
            func_8012A828((s32)param_1, &D_801A1AB8);
            *(u16 *)(param_1 + 2) = 3;
            *(u16 *)(param_1 + 0xfe) = 0;
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern s32 D_801A1A10;
extern void func_8012CBA4(s32 a0);

void func_80185080(s32 param_1)
{
    s16 tmp[3];
    s32 sq;

    func_8012CBA4(param_1);
    if (func_8012BEE8(param_1) != 0) {
        *(u16 *)(param_1 + 0xFC) = 0;
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);
        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(u16 *)(param_1 + 0x5C) |= 0x8000;
        *(u16 *)(param_1 + 0x5E) = 0;
        *(u16 *)(param_1 + 0xFC) ^= 1;
        tmp[0] = *(s16 *)(param_1 + 0x6);
        tmp[1] = *(s16 *)(param_1 + 0xA);
        tmp[2] = *(s16 *)(param_1 + 0xE);
        sq = (tmp[0] * tmp[0]) + (tmp[2] * tmp[2]);
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(sq);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(tmp);
    }
}


extern s32 D_801270D4;
extern s32 D_801270E4;

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void *a0);

void func_80185150(s32 param_1) {
    s32 v1;

    func_8012AD80(param_1);
    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x100;
    if (func_8012BEE8(param_1) != 0) {
        if (*(s16 *)(param_1 + 0x70) == 2) {
            D_801270E4 -= 1;
        } else {
            D_801270D4 -= 1;
        }
        func_8012C098((void *)param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_8012C098(void *a0);
extern s32 D_801270D4;
extern s32 D_801270E4;

void func_801851EC(s32 param_1) {
    register s32 *p __asm__("$2");
    register s32 mask __asm__("$5");

    mask = 0x80000000;
    p = *(s32 **)(param_1 + 0x20);
    p[1] ^= mask;
    if (((s32 (*)(void))func_8012BEE8)() == 0) {
        return;
    }
    func_80130D48(param_1);
    if (*(s16 *)(param_1 + 0x70) == 2) {
        D_801270E4 -= 1;
    } else {
        D_801270D4 -= 1;
    }
    func_8012C098(param_1);
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183630(s32 a0);
extern void func_80183790(s32 a0);

void func_8018528C(void *a0) {
    void *s0;
    register unsigned short state __asm__("$4");

    s0 = a0;
    state = *(u16 *)((u8 *)s0 + 0x34);

    switch (state) {
    case 0:
        ((struct { unsigned short h; } *)((u8 *)s0 + 0x34))->h = state + 1;
        ((struct { s32 f; } *)((u8 *)s0 + 0x1C))->f = 0;
        func_8002D4C8(0x4AA, 0);
        break;
    case 1:
        func_80183630((s32)s0);
        break;
    case 2:
        func_80183790((s32)s0);
        break;
    case 3:
        if (func_8012BEE8((s32)s0) != 0) {
            *(u16 *)((u8 *)s0 + 0x34) = 0;
        }
        break;
    }
}


#include "common.h"

void func_80185348(s32 param_1) {
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        func_8018392C(param_1);
        break;
    case 1:
        func_80183A7C(param_1);
        break;
    case 2:
        func_80183BD0(param_1);
        break;
    }
}


void func_801853C4(void) {
}

INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_801853CC);

void func_8018544C(s32 arg0)
{
    s16 sp10[3];
    s16 temp_v0;
    s32 temp_a0;

    temp_v0 = *(s16 *)(arg0 + 0xDC) + 0x10;
    *(s16 *)(arg0 + 0xDC) = temp_v0;
    temp_a0 = func_8004787C(temp_v0);
    *(s16 *)(arg0 + 0xA) = *(s16 *)(arg0 + 0xDE) + (temp_a0 << 5 >> 12);
    sp10[0] = *(u16 *)(arg0 + 6);
    sp10[1] = *(u16 *)(arg0 + 0xA);
    sp10[2] = *(u16 *)(arg0 + 0xE);
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 8) = sp10[0];
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 0xC) = sp10[2];
    func_80183DA4(sp10);
    if (*(u16 *)(arg0 + 0x5C) & 1) {
        if (*(u16 *)(arg0 + 0x5E) == 0x10) {
            func_80184090(arg0);
        } else {
            *(u16 *)(arg0 + 0x5C) = *(u16 *)(arg0 + 0x5C) & ~1;
        }
    }
}


extern void func_8012AD80(s32 a0);
extern void func_80183DA4();
extern void func_8005C2C8(s32 a0, s32 a1);
extern void func_8012C098(void *a0);
extern s32 D_8018ABF4;

void func_80185528(void *arg0)
{
    u16 sp10[3];

    func_8012AD80((s32)arg0);
    sp10[0] = *(u16 *)((s32)arg0 + 0x6);
    sp10[1] = *(u16 *)((s32)arg0 + 0xA);
    sp10[2] = *(u16 *)((s32)arg0 + 0xE);
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0x8) = sp10[0];
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xC) = sp10[2];
    *(u16 *)((s32)arg0 + 0x26) = *(u16 *)((s32)arg0 + 0x26) - D_8018ABF4;
    func_80183DA4((s32)arg0 + 0x24);
    *(s32 *)((s32)arg0 + 0x1C) += 1;
    if (*(s32 *)((s32)arg0 + 0x1C) >= 0x28) {
        func_8005C2C8(*(s32 *)((s32)arg0 + 0xCC), 0x84);
        func_8012C098(arg0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8005C2C8(s32 a0, s32 a1);
extern s32 rand(void);
extern u8 D_8018ABF8[];
extern void (*D_8018ABE4[])(void *);

void func_801855EC(s32 param_1)
{
    register s32 s0v __asm__("$16") = param_1;
    register s32 s1v __asm__("$17");
    u16 uVar2;

    s1v = ((s32 (*)(void))func_8012C1B8)();
    if (s1v == 0) {
        ((void (*)(s32))func_8012CAE4)(s0v);
        return;
    }
    ((void (*)(s32, void *))func_8001CA1C)(s1v,
        &D_8018ABF8[(*(u16 *)(s0v + 0x70) & 1) * 12]);
    *(u16 *)(s1v + 0x1C) = 0x3000;
    *(u16 *)(s1v + 0x1A) = 0x3000;
    *(u16 *)(s1v + 0x18) = 0x3000;
    *(s32 *)(s0v + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(s0v + 0x20) == 0) {
        ((void (*)(s32, s32))func_8005C2C8)(s1v, 0x84);
        ((void (*)(s32))func_8012CAE4)(s0v);
        return;
    }
    uVar2 = *(u16 *)(s0v + 0xA);
    *(s32 *)(s0v + 0xCC) = s1v;
    *(u16 *)(s0v + 0xDE) = uVar2;
    ((void (*)(s32, s32))func_8001C214)(*(s32 *)(s0v + 0x20), 0);
    *(s32 *)(s0v + 0x58) = (s32)D_8018ABE4;
    *(u16 *)(s0v + 0x2) = 1;
    *(u16 *)(s0v + 0x5C) |= 0x8000;
    *(u16 *)(s0v + 0x72) |= 0x1000;
    *(u16 *)(s0v + 0xDC) = rand() & 0xFFF;
}


extern void func_80184138(u16 *a0);
extern void func_80183DA4();
extern s16 D_8018A914;
extern s16 D_8018A91A;
extern s32 D_801270C8;
extern s32 D_801270CC;
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801856D8(int param_1)
{
    u16 sp10[3];   /* sp+0x10 */
    u16 sp18[10];  /* sp+0x18 .. 0x2B */
    s16 *p;

    if (func_8012BEE8((s32)param_1) != 0) {
        sp10[0] = *(u16 *)(param_1 + 6);
        sp10[1] = *(u16 *)(param_1 + 0xA);
        sp10[2] = *(u16 *)(param_1 + 0xE);
        func_80184138(sp10);
        p = &D_8018A91A;
        if (*p == 0) {
            func_80183DA4((s32)p - 6);
        }
    }
    if (D_801270C8 != 0) {
        register void *a0pin __asm__("$4") = sp18;
        __asm__ __volatile__("" : : "r"(a0pin));
        if (D_801270CC == 0) {
            D_801270CC = 1;
            sp18[0] = *(u16 *)(param_1 + 6);
            sp18[1] = *(u16 *)(param_1 + 0xA);
            sp18[2] = *(u16 *)(param_1 + 0xE);
            sp18[3] = 0x1E;
            sp18[5] = 0;
            sp18[4] = 0;
            *(s32 *)&sp18[8] = 0;
            sp18[7] = 0;
            func_8012C51C(a0pin, (s32)param_1);
        }
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s16 D_8018AC1C;

void func_801857BC(s32 param_1)
{
    s32 iVar1;
    u16 uVar2;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, s32))func_8001C214)(iVar1, 0);
    uVar2 = *(u16 *)(param_1 + 0x72);
    *(s32 *)(param_1 + 0x58) = (s32)&D_8018AC1C;
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 0x10;
    *(u16 *)(param_1 + 0xFC) = 0;
    *(u16 *)(param_1 + 0x72) = uVar2 | 0x1000;
}


void func_80185834(s32 param_1) {
    s32 v0;
    s32 a;
    s32 pad[2];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern u8 D_8018CE0C[];
    extern void func_8001C214(s32, s32);
    extern void func_8001D0E8(s32, s32, s32);
    extern void func_8012B2CC(s32);
    extern s32 ratan2(s32, s32);
    extern void func_8012A828(s32, void *);
    extern void func_8012B200(u8 *);
    extern u8 D_800D3918[];
    extern u8 D_800D391C[];
    extern s32 D_801A2378;
    extern s32 D_8018AC34;

    (void)&pad;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    ((void (*)(void *, void *))func_8001C214)((void *)v0, D_8018CE0C);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xBE, 0x8C);
    func_8012B2CC(param_1);
    a = ratan2(*(s16 *)D_800D391C - *(s16 *)(*(s32 *)(param_1 + 0x20) + 0xC),
               *(s16 *)(*(s32 *)(param_1 + 0x20) + 8) - *(s16 *)D_800D3918);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (a - 0x400) & 0xFFF;
    func_8012A828(param_1, &D_801A2378);
    *(s16 *)(param_1 + 2) = 1;
    func_8012B200((u8 *)param_1);
    *(s32 *)(param_1 + 0x14) = D_8018AC34;
}


extern void func_800183E0(s32 a0);
    extern s32 D_801C4854;
    void func_80185904(void) {
        ((void (*)(void *))func_800183E0)(&D_801C4854);
    }



extern void (*D_8018AC44[])(void);

void func_8018592C(void *a0) {
    D_8018AC44[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s32 a1);
    extern s32 func_8012AD50(void *a0);
    void func_80185968(s32 arg0) {
        ((void (*)(s32, s32))func_8012BF4C)(arg0, 0);
        ((void (*)(void *))func_8012AD50)((void *)arg0);
    }


#include "common.h"

/* func_8018599C — spawn 4 particles/effects (id 0x67) at jittered offsets around
 * the actor's world position, then re-arm the actor timer.
 *
 * S55 second-pass crack. Residual class the first pass parked on was
 * "REGALLOC-COALESCE (mag/delta persistence-across-call)": the target keeps the
 * magnitude in $s1 live across the sign-deciding rand() call while the signed
 * delta lives in $s0, and a plain `s32 delta = mag;` lets cse copy-propagate
 * delta into the `negu` so mag dies at the copy ($v0, 83 ins / wrong regs).
 *
 * Three levers, in order of yield:
 *   1. §194-B WIDTH IS A DIAL — `delta` is declared **16-bit**. The truncating
 *      copy is not a plain reg-reg copy, so copy-propagation cannot rewrite the
 *      `negu`'s operand; mag stays a separate pseudo live across the call and
 *      earns its own callee-saved register (the 5th, which is why the target
 *      saves $s0..$s4 and not $s0..$s3).  58 mismatches -> 12.
 *      No sign-extension appears because combine drops it: the sum is only ever
 *      consumed by an `sh` (same reason `in[]` reads as lhu, not lh).
 *   2. The two shift/mask steps of r0 are written as SELF-ASSIGNMENTS
 *      (`r0 &= 0xF; r0 <<= 6;`) rather than one `r0 = (r0 & 0xF) << 6;`.
 *      The single-expression form spawns a fresh pseudo for the `&` result and
 *      local_alloc parks it in $v1 (`andi $v1,$s0,0xF ; sll $s0,$v1,6`);
 *      the split form reuses r0's own register in place, as the target does.
 *   3. §178/pin — with 1+2 the only residual was a straight $s0<->$s1 swap of
 *      mag/delta that no declaration-order permutation moved (3 tried, all 8).
 *      `register s16 delta __asm__("$16")` pins delta to $s0 and mag falls into
 *      $s1 on its own.  MATCH.
 *
 * in/out are two 3-halfword stack vectors at sp+0x10 / sp+0x18 (the
 * func_80186688 house idiom, §193-I: a 6-byte aggregate strides 8 in the frame).
 * They are plain s16[3] rather than the TU's `SV3` typedef ONLY so this file
 * compiles standalone in the match harness — SV3 is already visible in the
 * destination TU via engine_core.h and re-typedef'ing it would be a
 * redefinition error at bank time (§183.1). Layout/bytes are identical.
 *
 * Declarations: D_80126B58 / func_80015978 / func_8012BEE8 / func_8012BF4C /
 * rand are copied verbatim from this TU's existing rows; func_801290DC has no
 * TU row, so the fleet-consensus u8 *(s32, u8 *) (n=1494) is used.
 */

extern s32 func_8012BEE8(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 D_80126B58;
extern s32 rand(void);

void func_8018599C(s32 param_1)
{
    s16 in[3];                              /* sp+0x10 (x,y,z) */
    s16 out[3];                             /* sp+0x18 (x,y,z) */
    u8 *base = (u8 *)&D_80126B58;
    s32 i;
    u8 *p;
    s32 r0, r1, r2;
    s32 mag;                                /* -> $s1, live across the sign rand() */
    register s16 delta __asm__("$16");      /* -> $s0, 16-bit on purpose (§194-B) */
    s32 t;

    if (func_8012BEE8(param_1) == 0) {
        return;
    }

    func_80015978(param_1 + 4, (s32 *)in);

    for (i = 0; i < 4; i++) {
        if (*(s32 *)(param_1 + 0xDC) != 0) {
            /* jitter X: +/- ((rand&0xF)<<6 + (rand&0xF)<<2) */
            r0 = rand();
            r1 = rand();
            r0 &= 0xF;
            r0 <<= 6;
            r1 = (r1 & 0xF) << 2;
            mag = r0 + r1;
            delta = mag;
            r2 = rand();
            if ((r2 & 1) != 0) {
                delta = -mag;
            }
            out[0] = in[0] + delta;

            /* jitter Z, same shape */
            r0 = rand();
            r1 = rand();
            r0 &= 0xF;
            r0 <<= 6;
            r1 = (r1 & 0xF) << 2;
            mag = r0 + r1;
            delta = mag;
            r2 = rand();
            if ((r2 & 1) != 0) {
                delta = -mag;
            }
            out[2] = in[2] + delta;
            out[1] = *(u16 *)(base + 0xA) - 0x200;   /* D_80126B58+0xA: camera/ground Y */
        }

        p = func_801290DC(0x67, (u8 *)out);
        if (p != NULL) {
            *(u16 *)(p + 0x2E) = *(u16 *)(param_1 + 0xFC);
        }
    }

    t = rand() & 0x1F;
    func_8012BF4C((s32 *)param_1, t + 8);
}



extern void (*D_8018AC50[])(void);

void func_80185AF8(void *a0) {
    D_8018AC50[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8017F690", func_80185B34);

#include "common.h"

extern void func_80185C0C(s32 arg0);
extern void func_8012931C(void *a0, s32 a1);
extern void func_801292C8(void);

void func_80185B78(void *a0) {
    register s8 *s0 __asm__("$16");
    s32 pad[2];
    s32 cnt;
    s32 t;

    s0 = (s8 *)a0;
    cnt = *(s32 *)(s0 + 0x1C);

    if (cnt == 0) {
        func_80185C0C((s32)s0);
        *(volatile s32 *)(s0 + 0x10) = *(s32 *)(s0 + 0x10);
        t = *(s32 *)(s0 + 0x18);
        *(s32 *)(s0 + 0x18) = t;
        *(s32 *)(s0 + 0x14) = *(s32 *)(s0 + 0x14) + 0xC000;
        func_8012931C(s0, t);
        if (*(s16 *)(s0 + 0x2E) < *(s16 *)(s0 + 0xA)) {
            *(s16 *)(s0 + 0xA) = *(s16 *)(s0 + 0x2E);
            ((void (*)(u8 *))func_801292C8)((u8 *)s0);
        }
    } else {
        *(s32 *)(s0 + 0x1C) = cnt - 1;
    }
}


#include "common.h"

/* ---------------------------------------------------------------------------
 * BANKING PRE-FLIGHT (dest TU: src/ov_SC01_084/ov_SC01_084_jr_8017CA80.c)
 *
 *  ALREADY IN THE TU -- DELETE MY COPIES WHEN BANKING (verified token-identical):
 *    line  119 : extern void func_80015978(s32 a0, s32 *a1);   <- adopted verbatim
 *    line 2704 : gte_ldv3      line 2725 : gte_rtpt      line 2734 : gte_stsxy3
 *    line 2791 : gte_stszotz   line 2800 : gte_stflg
 *
 *  MUST BE ADDED TO THE TU (not present anywhere in it):
 *    gte_SetRotMatrix / gte_SetTransMatrix   (bodies below; identical to the
 *      already-banked pair in ov_SC03_099_jr_8017BEBC.c lines 3784/3798)
 *    extern s32 func_8012EF34(s32 a0, s32 a1);   <-- SEE WARNING
 *    extern void func_80017D98(void *a0);        (matches the def in src/800.c)
 *    extern void func_8001739C(void *a0);        (the spelling every other TU uses)
 *    extern s16 D_8018AC58/5C/60/64/68/6C;       (raw-word form, law 4)
 *
 *  WARNING (§181 law 2/4): every other TU spells func_8012EF34 `extern void
 *  func_8012EF34(s32 a0, s32 a1);` because no other caller consumes its return.
 *  THIS caller does (`and $v0,$v0,-0x1001; bnez`), so the draft needs the s32
 *  return type.  ov_SC01_084_jr_8017CA80.c declares func_8012EF34 NOWHERE today,
 *  so there is no in-TU conflict -- but if another draft in this wave lands the
 *  `void` spelling in this same TU, the two collide.  Reconcile to the s32 form
 *  (a `void` callee called for value is what the shared DEFINE actually leaks).
 *
 *  No other symbol in this draft appears in the TU.  D_8018AC50 (line 3886) is a
 *  different symbol.  All type names are suffixed _80185C0C, so no §183.1 clash.
 * ------------------------------------------------------------------------- */


/* func_80185C0C @ 0x80185C0C  (ov_SC01_084, TU ov_SC01_084_jr_8017CA80.c)
 *
 * Splat calls this "handwritten" only because the body is full of cop2 traffic.
 * It is ordinary gcc-2.7.2 -O2 C using the project's PsyQ inline GTE macros
 * (the $12/$13/$14 scratch triple and the "nop;nop;rtpt" spelling are the tell) --
 * exactly the macro set the destination TU already carries at lines 2698-2812.
 *
 * Shape:  project the owner's world position, then draw a 4-way mirrored
 * triangle fan through func_8001739C using an identity rot-matrix.
 */

extern void func_80015978(s32 a0, s32 *a1);
/* NOTE: the shared DEFINE_func_8012EF34() spells this `void func_8012EF34(s32,s32)`.
 * This call site consumes the $v0 that leaks out of its tail call, so the draft must
 * declare an s32 return.  The destination TU declares func_8012EF34 nowhere, so there
 * is no in-TU conflict to reconcile (see notes). */
extern s32 func_8012EF34(s32 a0, s32 a1);
extern void func_80017D98(void *a0);
extern void func_8001739C(void *a0);

/* three separate 8-byte SVECTOR-ish globals; each store below emits its own lui/%lo */
extern s16 D_8018AC58;   /* vert0 .vx/.vy word */
extern s16 D_8018AC5C;   /* vert0 .vz        */
extern s16 D_8018AC60;   /* vert1 .vx/.vy    */
extern s16 D_8018AC64;   /* vert1 .vz        */
extern s16 D_8018AC68;   /* vert2 .vx/.vy    */
extern s16 D_8018AC6C;   /* vert2 .vz        */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
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

typedef struct {
    s16 x;      /* +0x0 */
    s16 y;      /* +0x2 */
    s16 c;      /* +0x4 */
    s16 pad;    /* +0x6 */
} Vtx_80185C0C;                     /* 0x08 */

typedef struct {
    Vtx_80185C0C v[3];              /* +0x00 +0x08 +0x10 */
    u8 r0, g0, b0, code;            /* +0x18 .. +0x1B */
    u8 r1, g1, b1, pad1;            /* +0x1C .. +0x1F */
    u8 r2, g2, b2, pad2;            /* +0x20 .. +0x23 */
    u32 color;                      /* +0x24 */
} Prim_80185C0C;                    /* 0x28 */

typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 z;      /* +0x4 */
} Pos_80185C0C;                     /* 0x06 -> 8-byte frame stride, §193-I */

typedef struct {
    u16 vx;     /* +0x0 */
    u16 vy;     /* +0x2 */
    u16 vz;     /* +0x4 */
    u16 pad;    /* +0x6 */
} Sxy_80185C0C;                     /* 0x08 */

typedef struct {
    s16 m[3][3];                    /* +0x00, padded to 0x14 */
    s32 t[3];                       /* +0x14 +0x18 +0x1C */
} Mtx_80185C0C;                     /* 0x20 */

void func_80185C0C(s32 arg0)
{
    Prim_80185C0C prim;             /* sp+0x10 */
    Pos_80185C0C wpos;              /* sp+0x38 */
    Pos_80185C0C spos;              /* sp+0x40 */
    Sxy_80185C0C sxy[4];            /* sp+0x48 (only 0..2 used; 4th slot fills 0x60) */
    Mtx_80185C0C mtx;               /* sp+0x68 */
    s32 otz;                        /* sp+0x88 */
    s32 flag;                       /* sp+0x8C */
    s32 t;
    Prim_80185C0C *p = &prim;

    func_80015978(arg0 + 4, (s32 *)&wpos);
    if ((func_8012EF34((s32)&wpos, (s32)&spos) & ~0x1000) == 0) {
        gte_stszotz(&otz);
        D_8018AC5C = spos.z;
        D_8018AC64 = spos.z;
        D_8018AC6C = spos.z;
        func_80017D98(&mtx);
        /* emitted 0x84/0x80/0x7C -> source runs t[2] first */
        mtx.t[2] = 0;
        mtx.t[1] = 0;
        mtx.t[0] = 0;
        gte_SetRotMatrix(&mtx);
        gte_SetTransMatrix(&mtx);
        gte_ldv3(&D_8018AC58, &D_8018AC60, &D_8018AC68);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_stflg(&flag);
        if (flag >= 0) {
            /* per-vertex colour written b,g,r: the shared-constant groups keep
             * source order inside each group (0xC0 -> 0x2A,0x29,0x28 etc.) */
            p->b0 = 0xC0;
            p->g0 = 0xC0;
            p->r0 = 0xC0;
            p->b1 = 0x40;
            p->g1 = 0x20;
            p->r1 = 0x20;
            p->b2 = 0x40;
            p->g2 = 0x20;
            p->r2 = 0x20;
            p->color = 0x50000000;
            p->v[0].x = sxy[0].vx + spos.x;
            p->v[0].y = sxy[0].vy + spos.y;
            p->v[1].x = sxy[1].vx + spos.x;
            p->v[1].y = sxy[1].vy + spos.y;
            p->v[2].x = sxy[2].vx + spos.x;
            p->v[2].y = sxy[2].vy + spos.y;
            p->v[0].c = otz;
            func_8001739C(p);
            t = sxy[1].vy;
            p->v[1].y = spos.y - t;
            func_8001739C(p);
            t = sxy[2].vx;
            p->v[2].x = spos.x - t;
            func_8001739C(p);
            p->v[1].y = sxy[1].vy + spos.y;
            func_8001739C(p);
        }
    }
}


extern s32 func_800CF854(s32);

s32 func_80185E38(void)
{
    register s32 r __asm__("$2");
    s32 v;

    v = ((s32 (*)(void))func_800CF854)();
    r = 3;
    if (v != 0)
        r = 4;
    return r;
}



extern s32 D_801C7728;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80185E68(s32 a0, s32 a1) {
    D_801C7728 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801C7728;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_80185E98(s32 param_1) {

    extern M2C_UNK D_80186B78;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_8018AC84;
    extern char * D_8018ACB8;
    extern char D_801C7708[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8018AC84) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80186B78));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801C7728, &s60);
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
        tmp = D_8018ACB8;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_8018ACB8 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801C7708 < puVar4) {
        D_8018ACB8 = D_801C7708 - 0x120;
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
            tmp = D_8018ACB8;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_8018ACB8 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801C7708 < puVar4) {
            D_8018ACB8 = D_801C7708 - 0x120;
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

s32 func_801860DC(s32 param_1) {

    extern signed char D_8018AC70[];
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
        p = D_8018AC70;
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
            p = D_8018AC70;
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


extern void (*D_8018ACBC[])(void);

void func_8018637C(void *a0) {
    D_8018ACBC[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH (94 ins). Keys: (1) cache out[0] in a local `o` before the switch so gcc
//   holds it in $a0 across the case stores (else it reloads/`lh` per case, +3 ins); (2) declare the
//   `in` struct BEFORE `out[2]` so in@sp+0x10 / out@sp+0x20; (3) the 0x14 word is written via
//   `*(s32*)&in.lo = D_80126B60` then the high short RMW'd `in.hi -= 0x20` (memory lhu/sh, not reg);
//   (4) order the three global assigns B60,B5C,B64 (B60 first → v0/v1/a2 alloc); (5) explicit
//   `case 2: break;` after case 3 so gcc emits the `beq $v1,2` test with case1 falling into case3.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8002D4C8(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B77C(void *, s32, void *);
extern void func_8012B2CC(s32);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_801863B8(s32 param_1) {

    extern M2C_UNK D_801A2F28;
    extern u8   D_801A2D00;
    extern u8 D_80126B5C;
    extern s32  D_80126B60;
    extern s32  D_80126B64;
    s32 iVar1;
    struct In in;
    s32 out[2];
    s32 t;
    s32 o;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801A2F28));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801A2D00);
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 100;

    *(s32 *)&in.lo = D_80126B60;
    in.hi -= 0x20;
    in.w0 = (*(s32 *)&D_80126B5C);
    in.w2 = D_80126B64;
    func_8012B77C(out, param_1 + 4, &in);

    o = out[0];
    t = *(u16 *)(param_1 + 0x70) & 0xF;
    switch (t) {
    case 0:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
        break;
    case 1:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
    case 3:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(o >> 16);
        break;
    case 2:
        break;
    }

    if (*(u16 *)(param_1 + 0x70) & 0x1000) {
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) << 1;
    }
    func_8012B2CC(param_1);
    ((void (*)(s32, s32))func_8012C588)(0xBC, param_1);
}



extern void (*D_801A2D9C[])(void);

void func_80186530(void *a0) {
    D_801A2D9C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A2DB0[])(void);

void func_8018656C(void *a0) {
    D_801A2DB0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801A2D88;
extern s32 D_801A2D94;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_801865A8(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801A2D88);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801A2D94, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}



// @class: schedule
// @stuck: none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801A2DA4;

void func_80186688(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801A2DA4);
        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        ((void (*)(int, void *, void *))func_8012F214)(param_1, &in, &out);
        *(short *)(param_1 + 6) = out.a;
        *(short *)(param_1 + 0xa) = out.b;
        c = out.c;
        *(int *)(param_1 + 0x1c) = 0x5a;
        *(short *)(param_1 + 0x34) = 1;
        *(short *)(param_1 + 0xe) = c;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - 0x80;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 4;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 5;
    func_8012AD80(param_1);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801A3058;

void func_801867A4(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801A3058);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}






