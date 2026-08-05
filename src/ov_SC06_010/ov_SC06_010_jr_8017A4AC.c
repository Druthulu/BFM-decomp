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
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80188F28;
extern u8 D_80188E98;
extern u8 D_80188E74;
extern u8 D_80188E50;
extern u8 D_80188F04;
extern u8 D_80188EE0;
extern u8 D_80188EBC;
extern u8 D_80188E2C;
extern void func_80145934(void);
extern u8 D_80188FB8;
extern u8 D_80188F94;
extern u8 D_80188F70;
extern u8 D_80188F4C;
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
extern unsigned char D_801883B0[];
extern unsigned char D_801883E0[];
extern unsigned char D_80188430[];
extern unsigned char D_80188460[];
extern unsigned char D_80188490[];
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
extern void (*D_801884E0[])(void *);
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
extern s32 D_801885A8[];
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
extern u8 D_80188630[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188638;
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
extern int D_801B0E80;
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
extern s32 D_801B0E84;
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
extern s32 D_80188668;
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
extern void (*D_80188710[])(void);
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
extern void (*D_80188734[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188724;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188748[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188754[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80188764[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018877C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018876C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80188790[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801887AC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018879C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801887C0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801887D4[])(void);
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
extern s32 D_801887E8;
extern void (*D_80188810[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801887F0;
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
extern int (*D_8018885C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80188860[])(void);
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
extern unsigned short D_80188CC4[];
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
extern void (*D_80188CD4[])(void);
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
extern int D_801B0EB8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188CFC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188CDC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188CEC;
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
extern void (*D_80188D3C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188D44[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188D10;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188D50[])(void);
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
extern u8 D_80188D20;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B0EC0;
extern s32 D_801B0ECC;
extern s32 D_801B0ED0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188D8C[])(s32 *);
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
extern s32 D_80188D60[];
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
extern s32 D_801B0EC8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188FDC[])(void);
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
extern char D_80188DFC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80189080[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801891D4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188FF0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801891DC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80189000;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80189020;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_801891E4[])(void);
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
extern void (*D_8018920C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189218[])(void);
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
extern void (*D_8018908C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801892BC;
extern void func_8015D380(s32 a0);
extern unsigned char D_801883A0[];
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
extern unsigned char D_801892D0[];
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
extern s8 D_8018930C[];
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
extern u16 D_80189354;
extern u16 D_80189356;
extern u16 D_80189358;
extern s32 D_8018935C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189364;
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
extern int D_80189070;
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
extern unsigned int D_801893E8[];
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
extern void (*D_80189498[])(void);
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
extern u16 D_801894C8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018952C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B0ED8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189550[])(void);
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
extern int D_801B0F30[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189598[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189588;
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
extern char D_801B07C4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801895A0[])(void);
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
extern void (*D_801895F4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801895BC;
extern s16 D_801895F0;
extern s16 D_801895EE;
extern s16 D_801895EC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189600[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B0F90;
extern u8 D_801B0F91;
extern u8 D_801B0F92;
extern u8 D_801B0F93;
extern u8 D_801B0F94;
extern u8 D_801B0F95;
extern u8 D_801B0F96;
extern u8 D_801B0F97;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189610[])(void);
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
extern s32 D_801B0FD0;
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
extern void (*D_80189654[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801896D0[];
extern s32 D_801896F0[];
extern u8 D_8018976C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018978C[];
extern u8 D_801897AC[];
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
extern void (*D_80189848[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801898C4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B07D4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801898D0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801898D8[])(void);
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
extern void (*D_801899A0[])(void);
extern void func_80166618(void *a0);
extern void (*D_801899B0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801899C0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801899CC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018992C[];
extern u8   D_80189940[];
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
extern void (*D_801899E4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801899EC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801899F4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801899FC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80189A04[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189A0C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189A14[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189AC8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189AD0[])(void);
extern void func_80169F00(void *a0);
extern char D_80189A80[];
extern char D_80189A40[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189B08[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80189B14[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80189B5C[])(void);
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
extern void (*D_80189BD8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B12F0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80189BCC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189C10[];
extern unsigned short D_80189C18[];
extern unsigned short D_80189C20[];
extern unsigned char D_801B12F8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B12F0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189C28[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B142C;
extern M2C_UNK D_801B1430;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B13B8;
extern void (*D_80189C58[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B1434[];
extern u8 D_801B143C[];
extern u8 D_801B13EC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189C60[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189C7C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189C84[])(void);
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
extern void (*D_80189CEC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189C90;
extern u8 D_80189C9C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80189D20[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189D28[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189D7C[])(void);
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
extern u16 D_80189DB0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189DA0[];
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
extern s32 D_80189DCC;
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
extern void (*D_80189E44[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189E4C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189E54[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189E5C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189E64[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189E6C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189E78[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189E84[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189E90[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189EA0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189EB0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189EB8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189EC0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189EC8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189ED0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80189ED8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80189EE0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80189EE8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80189EF0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80189EF8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80189F00[])(void);
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
extern void (*D_80189F08[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80189F10[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80189F18[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80189F20[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80189F28[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80189F30[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80189F38[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80189F40[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80189F48[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80189F50[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80189F58[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80189F60[])(void);
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
extern void (*D_80189FA4[])(void);
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
extern M2C_UNK D_80189F68;
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
extern void (*D_80189FD4[])(void);
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
extern void (*D_8018A010[])(void);
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
extern void (*D_8018A068[])();
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
extern void (*D_8018A078[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018A080[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018A1E8[])();
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
extern void (*D_8018A1F4[])();
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
extern M2C_UNK D_801B0A1C;
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
extern s16 D_801B2C08;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B1B70;
extern short D_801B2C7C;
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
extern s32 D_801B1F9C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B1FC4;
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
extern s16 D_801B1F80;
extern s32 func_8017A3B0(void);
extern short D_801B1FBC;
extern short D_801B1FB8;
extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
/* ==== end §8b carried decl layer ==== */


// func_8017A4AC (ov_SC01_077) — 536-ins command/bytecode interpreter, 35-case jtbl switch.


    extern u16 D_801B1B78[0x200];
    extern s16 D_801B1F78;
    extern s16 D_801B1F7C;
    extern s32 D_801B1FC0;

extern s32 D_80126B58;
extern s16 D_801B1F80;
extern s32 D_801B1F9C;
extern s32 D_801B1FC4;

extern void func_80172310(u8*);
extern void func_80172738(void);
extern void func_80172780(void*);
extern void func_80172894(void*);
extern void func_801729B0(s32);
extern void func_80172B14(s16);
extern void func_80172C50(u16 *);
extern void func_80172D68(s32);
extern void func_80172E94(void);
extern void func_80172ED4(void);
extern void func_80172EFC(void);
extern void func_80172F24(void);
extern void func_80172F4C(void);
extern void func_80172F9C(void);
extern void func_80172FEC(void);
extern void func_80173174(void);
extern void func_8017329C(void);
extern void func_8017334C(void);
extern void func_801733A4(void);
extern void func_801733FC(s16, u16 *);
extern void func_80173460(s32, s32);
extern void func_801734BC(s32, s32);
extern void func_801736B0(s32, s32);
extern void func_801737B8(s16);
extern void func_801738DC(s16);
extern void func_80173A28(s32, s32, s32, s32, s32, s32);
extern void func_8017427C(void);
extern void func_80174438(s32);
extern void func_8017452C(void);
extern void func_80174584(void);
extern void func_801745DC(void);
extern s32 func_80174754(void);

void func_8017A4AC(void) {
    u16 sp18[4];
    u16 sp20[4];
    u16 sp28[4];
    u16 sp30[4];
    struct S126B58 *w = &(*(struct S126B58 *)&D_80126B58);
    s16 cmd;

    if (D_801B1F78 == D_801B1F7C) {
        if (func_80174754() != 0) {
            D_801B1F80 = 0;
        } else {
            D_801B1F80 = 1;
        }
        return;
    }
    D_801B1F80 = 1;
    if (func_80174754() == 0) {
        return;
    }
    cmd = D_801B1B78[D_801B1F78];
    D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
    switch (cmd) {
    case 0:
        func_80172738();
        return;
    case 1:
        sp18[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172780)(sp18);
        return;
    case 28:
        sp18[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[3] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172894)(sp18);
        return;
    case 2:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(s16))func_801729B0)(arg);
        return; }
    case 3:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        func_80172B14(arg);
        return; }
    case 4:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        { s32 t = w->unk20->unk12 + arg;
        func_80172B14(t & 0xFFF); }
        return; }
    case 5:
        sp18[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp18[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        func_80172C50(sp18);
        return;
    case 6:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(s16))func_80172D68)(arg);
        return; }
    case 7: func_80172E94(); return;
    case 8: func_80172ED4(); return;
    case 27: ((void (*)())D_801B1FC4)(); return;
    case 9: func_80172EFC(); return;
    case 10: func_80172F24(); return;
    case 11: func_80173174(); return;
    case 12: func_80172F4C(); return;
    case 33: func_80172F9C(); return;
    case 34: func_80172FEC(); return;
    case 13: func_801745DC(); return;
    case 14:
    case 15: func_8017329C(); return;
    case 16: func_8017334C(); return;
    case 17: func_801733A4(); return;
    case 18:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        func_801738DC(arg);
        return; }
    case 19: {
        s16 a, b;
        s32 ea, eb;
        a = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF; ea = a;
        b = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF; eb = b;
        func_801736B0(ea, eb);
        return;
    }
    case 20:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(s16))func_801734BC)(arg);
        return; }
    case 23:
        sp20[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp20[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp20[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(s16, u16 *))func_80173460)(arg, sp20);
        return; }
    case 29:
        sp28[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp28[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp28[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        func_801733FC(arg, sp28);
        return; }
    case 32:
        sp30[0] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp30[1] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp30[2] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        sp30[3] = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172310)(sp30);
        return;
    case 25: func_8017452C(); return;
    case 30: func_80174584(); return;
    case 26: func_8017427C(); return;
    case 24: func_80174438(D_801B1FC0); return;
    case 21:
        ((void (*)(s32, s32, s32, s32, void *, s32))func_80173A28)((*(struct S734 * *)&D_801B1F9C)->unk0, (*(struct S734 * *)&D_801B1F9C)->unk4, (*(struct S734 * *)&D_801B1F9C)->unk8,
                      (*(struct S734 * *)&D_801B1F9C)->unkC, (*(struct S734 * *)&D_801B1F9C)->unk10, (*(struct S734 * *)&D_801B1F9C)->unk18);
        return;
    case 22:
        (*(struct S734 * *)&D_801B1F9C)->unk1C((*(struct S734 * *)&D_801B1F9C)->unk4, (*(struct S734 * *)&D_801B1F9C)->unk10, (*(struct S734 * *)&D_801B1F9C)->unk18);
        return;
    case 31:
        { s16 arg = D_801B1B78[D_801B1F78]; D_801B1F78 = (D_801B1F78 + 1) & 0x1FF;
        func_801737B8(arg);
        return; }
    }
}


DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017AD0C (src/shared) */

DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ADE8 (src/shared) */

DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017AE08 (src/shared) */


extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B030();
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s32 func_80012A60(s32 a0, s32 a1);


void func_8017AE2C(s32 param_1) {

    extern s16 D_801B2BD8;
    extern s16 D_801B2BDA;
    extern s16 D_801B2BE4;
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801B2BD8;

    switch (g[0]) {
    case 0:
    default:
        return;
    case 1:
        g[1] = (u16)g[1] - 1;
        if (g[1] <= 0) {
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) = (u16)g[2];
            goto reset_both;
        }
        {
            s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), g[2], 6);
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
        }
        return;
    case 2:
        func_8012B178(pv, (s32)g[4] << 8);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        ((s32 (*)(u8 *))func_8012B030)((u8 *)pv);
        break;
    case 3:
        if (g[1] != 0) {
            if (g[5] != 0) {
                void *p = (void *)(pv + 4);
                if ((s16)func_80012A60(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12),
                                       (s16)func_8012B744(p, &g[6])) < 0x100) {
                    g[1] = 0;
                }
                *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    func_8012B744(p, &D_801B2BE4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                ((s32 (*)(u8 *))func_8012B030)((u8 *)pv);
                /* &D_801B2BD8+0xC == &D_801B2BE4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801B2BD8 + 0xC)) < 0x101) {
                    D_801B2BD8 = 0;
                    D_801B2BDA = 0;
                }
            }
            {
                s32 t = func_8012B744((void *)(pv + 4), &g[6]);
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), t, g[3]);
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
            }
            g[1] = (u16)g[1] - 1;
            if (g[1] > 0) {
                return;
            }
            g[1] = 0;
            return;
        }
        *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            func_8012B744((void *)(pv + 4), &D_801B2BE4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        ((s32 (*)(u8 *))func_8012B030)((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801B2BD8 + 0xC)) < 0x101) {
            D_801B2BD8 = 0;
            D_801B2BDA = 0;
        }
        return;
    case 4:
        func_8012AD80(pv);
    }
    g[1] = (u16)g[1] - 1;
    if (g[1] > 0) {
        return;
    }
reset_both:
    g[0] = 0;
    g[1] = 0;
    return;
}

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801B1FFC;
    extern s16 D_801B1FFE;
    extern s16 D_801B2000;
    extern s16 D_801B1FF4;
    extern s16 D_801B1FF6;
    extern s16 D_801B1FF8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801B1FFC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801B1FFE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801B2000, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801B1FF4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801B1FF6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801B1FF8, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801B1F84;
extern u16 D_801B2004;
extern u16 D_801B2006;
extern u16 D_801B2008;
extern s16 D_801B2C08;

void func_8017B1D8(void) {
    func_8012A418();
    D_801B2C08 = 0;
    D_801B1F84 = 0;
    D_801B2004 = D_80126B5E;
    D_801B2006 = D_80126B62;
    D_801B2008 = D_80126B66;
}


// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018A330[];
    extern s16 D_801B1FFC;
    extern s16 D_801B1FF4;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018A330[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A330[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801B1FFC;
        s16 *p78C = &D_801B1FF4;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801B2C08 = 1;
        D_801B1F84 = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801B1FA4;
    extern SV4_8017B368 D_801B1FAC;
    extern s16 D_801B1FFC;
    extern s16 D_801B1FF4;
    extern u16 D_8018A330;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801B1FA4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801B1FAC;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018A330)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018A330)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801B1FFC) = loc0;
    (*(SV4_8017B368 *)&D_801B1FF4) = loc1;
    D_801B2C08 = 1;
    D_801B1F84 = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801B1FA4;
    extern SV4_8017B368 D_801B1FAC;
    extern s16 D_801B1FFC;
    extern s16 D_801B1FF4;
    extern u16 D_8018A330;
    extern s16 D_801B1F84;
    extern s16 D_801B2C08;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801B1FA4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801B1FAC;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018A330)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018A330)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801B1FFC) = loc0;
    (*(SV4_8017B368 *)&D_801B1FF4) = loc1;
    D_801B2C08 = 1;
    D_801B1F84 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801B1FFC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801B1FFC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801B1FFC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801B1FF4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801B1FF4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801B1FF4).c;
}


// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.




s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018A330[];
    extern s16 D_801B1FFC;
    extern s16 D_801B1FFE;
    extern s16 D_801B2000;
    extern s16 D_801B1FF4;
    extern s16 D_801B1FF6;
    extern s16 D_801B1FF8;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018A330[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A330[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801B1FFC;
        s16 *p78C = &D_801B1FF4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801B1FFE;
            v798 = D_801B2000;
            v78C = *p78C;
            v78E = D_801B1FF6;
            v790 = D_801B1FF8;
            __asm__ __volatile__("");
            D_801B2C08 = 1;
            D_801B1F84 = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}




// @class: plumbing
// @stuck: none — MATCH

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8 D_8012694C;
extern s16 D_801B1F84;
extern s16 D_801B1FFC;
extern s16 D_801B1FFE;
extern s16 D_801B2000;
extern s16 D_801B1FF4;
extern s16 D_801B1FF6;
extern s16 D_801B1FF8;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801B1F84 = 0;
    D_801B1FFC = (s16) D_80114F30;
    D_801B1FFE = (s16) D_80114F34;
    D_801B2000 = (s16) D_80114F38;
    D_801B1FF4 = (s16) D_80114F24;
    D_801B1FF6 = (s16) D_80114F28;
    D_801B1FF8 = (s16) D_80114F2C;
}




extern s16 D_801B2014;
extern s16 D_801B2016;
extern s16 D_801B2018;
extern s16 D_801B201C;
extern s16 D_801B201E;
extern s16 D_801B2020;

void func_8017B824(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801151D4;
    D_801B2014 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801B2016 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801B2018 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801B201C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801B201E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801B2020 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801B2014;
extern s16 D_801B2016;
extern s16 D_801B2018;
extern s16 D_801B201C;
extern s16 D_801B201E;
extern s16 D_801B2020;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801B2014;
    D_80114F34 = D_801B2016;
    D_80114F38 = D_801B2018;
    D_80114F24 = D_801B201C;
    D_80114F28 = D_801B201E;
    D_80114F2C = D_801B2020;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801B1FFC), src[8..15] -> (*(S8_8017B8E8 *)&D_801B1FF4) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801B1FFC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801B1FF4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801B2004;
extern u16 D_801B2006;
extern u16 D_801B2008;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801B1F84;
extern short D_801B200C;
extern short D_801B200E;
extern short D_801B2010;
extern s16 D_801B1FFC;
extern s16 D_801B1FFE;
extern s16 D_801B2000;
extern s16 D_801B1FF4;
extern s16 D_801B1FF6;
extern s16 D_801B1FF8;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801B2004);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801B2006);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801B2008);
    (*(s16 *)&D_801B200C) = buf[0];
    (*(s16 *)&D_801B200E) = buf[1];
    (*(s16 *)&D_801B2010) = buf[2];
    D_801B1FFC = D_80114F30 + buf[0];
    D_801B1F84 = 0;
    D_801B1FFE = D_80114F34 + buf[1];
    D_801B2000 = D_80114F38 + buf[2];
    D_801B1FF4 = D_80114F24 + buf[0];
    D_801B1FF6 = D_80114F28 + buf[1];
    D_801B1FF8 = D_80114F2C + buf[2];
}



// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801B1FA4;
extern SV4 D_801B1FAC;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801B1FAC) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801B1FA4 = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    D_801B1FAC = buf1;
}


// @class: struct
// @stuck: none — MATCH (65 ins)
#include "common.h"




s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801B1FAC)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801B1FA4) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_801B1FAC) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801B1FCC[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801B1FCC;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}




// @class: plumbing
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);
extern s16 D_801B1F84;
extern s16 D_801B2C08;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801B1F84 = D_801B1F84 + 1;
    if (D_801B1F84 >= 0x1F) {
        D_801B2C08 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801B1F84;
extern s16 D_801B2C08;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801B1F84 = D_801B1F84 + 1;
    if (0x18 < D_801B1F84) {
        func_8012A4BC();
        D_801B2C08 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801B1F84;
extern void (*D_801B1FC8)(void);
extern short D_801B200C;
extern short D_801B200E;
extern short D_801B2010;
extern s16 D_801B2C08;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801B1F84 = D_801B1F84 + 1;
    if (D_801B1F84 >= 0x19) {
        if (D_801B1FC8 != 0) {
            (*D_801B1FC8)();
        } else {
            D_80114F30 = D_80114F30 + D_801B200C;
            D_80114F34 = D_80114F34 + D_801B200E;
            D_80114F38 = D_80114F38 + D_801B2010;
            D_80114F24 = D_80114F24 + D_801B200C;
            D_80114F28 = D_80114F28 + D_801B200E;
            D_80114F2C = D_80114F2C + D_801B2010;
            func_8012A4BC();
        }
        D_801B2C08 = 0;
    }
}



extern void (*D_8018A3D0[])(void);

void func_8017BE60(void *a0) {
    D_8018A3D0[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017BEBC);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017CA80);

#include "common.h"

/* ============================================================================
 * func_8017CAD4 — ov_SC06_010 / split TU ov_SC06_010_jr_8017A4AC  (755 ins)
 *
 * WHAT IT DOES — TMD-style textured model renderer, near-twin of the MATCHED
 * func_8017C294 (ov_SC06_008_jr_8017C294.c, 952 ins).  Differences from twin:
 *   - 3 params (ctx, model, mtxsrc) instead of 1; early-out on ctx->f0 != 0
 *   - part[] is EMBEDDED at model+0x14 (stride 0x14), nparts=model->8,
 *     vtx=model->0x10   (twin loaded them indirectly through model->8/->0xC)
 *   - Y screen-cull limits are -0x6E/0x6F (twin: -0x78/0x79)
 *   - switch(code&7) handles ONLY {2,3}=POLY_FT4 and {6,7}=POLY_FT3
 *     (twin also had 4,5=F3 and 0,1=F4)  -> gcc emits a 4-way decision TREE,
 *     no jump table.
 *   - vertices are copied through an align-1 local scratch (lwl/lwr+swl/swr
 *     block moves) before gte_ldv3c, instead of gte_ldv3(va,vb,vc)
 *   - OT z is fogged: rgb = clamp0(0x80 - (opz-0x190)/24) splatted to 3 bytes,
 *     opz bias is +0x40 (twin: +0x200), and FT3 adds a CLUT-row (<<22) to uvc0
 *
 * CONTROL FLOW MAP (asm labels)
 *   8017CAD4  prologue, if (ctx->f0) goto .L8017D66C (bare return)
 *             lim = func_800491EC() + ctx->f64;  func_800547D8(mtxsrc,&mtx);
 *             func_80052E38(&mtx); pkt=D_800A5E60; ot=&D_800A6610[hu<<14]
 *             nparts=model->8; vtx=model->0x10; if (nparts<=0) -> .L8017D664
 *   .L8017CB90  OUTER per-part loop (j: $t9, part: $fp=+0x14 / $s2=+0x20)
 *             build box[0..3] -> rtpt/rtps -> sxy[0..3]
 *             build box[4..7] (in the rtps shadow) -> rtpt/rtps -> sxy[4..7]
 *             gte_stszotz(&g.otz); if (lim < g.otz) -> .L8017D648 (next part)
 *   .L8017CCFC  X bbox min/max over sxy[0..3] and sxy[4..7], merge, cull ±0xA0
 *   .L8017CE34  Y bbox min/max, merge, cull ±0x6E/0x6F
 *   .L8017CF6C  nprim=part->nprim; prim=part->prim; if(!nprim)->.L8017D648
 *   .L8017CF90  INNER per-prim loop (i:$s1, prim:$t7 +=0xC, pkt:$t6, $t3=pkt+0x24)
 *             copy 3 vertices -> vt[3]; gte_ldv3c(vtp); rtpt
 *             gte_stflg; if (flag & 0x7F85E000) -> .L8017D630
 *             nclip; code=w&7; vd=vtx+(w&0xFFF8); gte_stopz
 *             if (opz<=0) -> .L8017D630 ; switch tree:
 *                code<2 -> .L8017D630 ; code<4 -> .L8017D2F4 (FT4)
 *                code>=8-> .L8017D630 ; code<6 -> .L8017D630 ; else FT3
 *   .L8017D0C0  FT3 (cases 6,7): stsxy3 @8/0x10/0x18, stsz3, x/y cull,
 *             za=max(sz0,sz1,sz2); opz=za(+0x40 if code==7); fog rgbc;
 *             uvc0=tp[1]+(cl<<22); uvp1; uv2; OT insert 0x7000000; pkt+=0x20
 *   .L8017D2F4  FT4 (cases 2,3): stsxy3c(tmpxy), ldv0(vd copy), rtps,
 *             x/y cull on tmpxy then on pkt->x3/y3 after stflg/stsz4/stsxy,
 *             za=max(sz0..sz3); opz=za(+0x40 if code==3); fog rgbc;
 *             uv2/uv3; OT insert 0x9000000; pkt+=0x28
 *   .L8017D624  shared OT-store tail (cross-jumped from both cases)
 *   .L8017D630  inner loop latch    .L8017D648 outer loop latch
 *   .L8017D664  D_800A5E60 = pkt    .L8017D66C epilogue
 *
 * STACK MAP (frame 0x1D0)
 *   0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 vt[3] | 0xB8 vd8
 *   0xC0 mtx | 0xE0 g{otz,flag,opz,sz0,sz1,sz2,sz3}
 *   reload slots (declaration order): 0x100 lim, 0x108 cl, 0x110 nparts,
 *           0x118 vtp(&vt[0]), 0x1A0 nprim
 *   NOTE 0x108 is READ (`lw $s3,0x108($sp)`; `sll $v1,$s3,22`) and NEVER
 *   WRITTEN anywhere in the function -> an uninitialised local that failed to
 *   get a hard reg.  Modelled here as `cl` (an uninitialised s32; gcc gives a
 *   never-defined pseudo its stack slot and emits only the reload).
 *
 * STATUS: MATCH 755/755 (match_one + rtu_match, 2026-07-30).
 *
 * THE FOUR LEVERS THAT CRACKED IT (all byte-verified, each named + isolated):
 *  (1) SIBLING PORT.  func_8017C294 (ov_SC06_008_jr_8017C294.c) is a MATCHED
 *      near-twin; porting its body and swapping constants/cases got 641 -> 253
 *      in two edits.  Cookbook §37 meta-law 1 (sibling isomorphism) again.
 *  (2) GIV ANCHOR = LAST-RECORDED mem-giv.  The 5 part[] field addresses
 *      combine into ONE base register; gcc anchors on the giv recorded LAST.
 *      Reading `prim` (+0x10) BEFORE `nprim` (+0xC) makes nprim the last giv
 *      -> base = part+0xC (`addiu $s2,$s1,0x20`), the target's.  Reading them
 *      the other way anchors on +0x10 (`addiu $s1,$s1,0x24`).  2-line swap.
 *  (3) THE OUTER-LOOP RE-HOIST REFUSAL (the big one, ~200 diffs).
 *      The 0x00FFFFFF OT mask must live in the INNER preheader.  Written as a
 *      literal, gcc's inner scan_loop hoists it there correctly -- and then the
 *      OUTER scan_loop RE-HOISTS it to the outer preheader (loop.c dump:
 *      "regno N (life 436), savings 1 halved since already moved  moved to M";
 *      threshold*savings*lifetime = 58*1*436 >> insn_count 602, so the
 *      desirability test can never refuse it).  The only reachable block is the
 *      ELIGIBILITY test `n_times_set[regno] == 1`:
 *        - name the mask (`u32 m24`), assign it in the INNER PREHEADER, and
 *        - add ONE zero-byte `__asm__("":"=r"(m24):"0"(m24))` after the inner
 *          loop -> 2 sets in the OUTER loop -> not a movable -> it stays put.
 *          (cookbook §37 "S2-kill re-tie", used here as a HOIST blocker.)
 *      The assignment must land AFTER the loop-entry guard, which a `for` can
 *      never do (the guard is generated by the `for`) -> hand-write the guard:
 *          i = 0; if (i >= nprim) goto noprim; m24 = 0xFFFFFF;
 *          do { ... i++; prim++; } while (i < nprim);  noprim: ;
 *      Latch order matters: `i++` BEFORE `prim++` reproduces the target's
 *      [addiu $s1,1][lw nprim][nop][sltu] (the other order lets `i++` fill the
 *      load-delay slot and costs the nop).  253 -> 30.
 *  (4) THE MISSING 8-BYTE RELOAD SLOT (frame 0x1C8 vs 0x1D0, 24 diffs, every
 *      emitted instruction already identical).  gcc gives EVERY pseudo that
 *      fails global allocation an 8-byte slot even when its references all
 *      vanish; the target has 21 such slots, the hand-written guard had 20.
 *      Spelling the guard `if (i >= nprim)` instead of `if (nprim == 0)` makes
 *      the (immediately folded) comparison temp exist -> the 21st slot, frame
 *      0x1D0.  It is created BEFORE the loop, so it stole 0x118 from the
 *      `&vt[0]` temp; hoisting that address into a DECLARED variable (`vtp`,
 *      declared right after `nparts`) puts it back at 0x118 (declared locals
 *      get lower regnos than any statement temp) and pushes the guard temp
 *      into the unreferenced 0x120..0x19F run.  30 -> 8 -> 6 -> MATCH.
 *      DO NOT add a `__asm__ volatile("")` live-length slider here: with the
 *      final shape the &g.sz0/&g.sz1 allocno tie already falls the target's
 *      way ($s6/$s5); a slider (or 2) flips it back (§47 cuts both ways).
 * ========================================================================== */


extern s32 func_800491EC(void);
extern void func_800547D8(s32, XMTX2 *);
extern void func_80052E38(XMTX2 *);
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern short D_800B9A02;

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

void func_8017CAD4(s32 *ctx, s32 *model, s32 mtxsrc)
{
    XDV2 tmpxy[4];
    XSV2 box[8];
    XSV2 sxy[8];
    XV8  vt[3];
    XV8  vd8;
    XMTX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 cl;
    s32 nparts;
    XV8 *vtp;
    s32 j;
    u32 nprim;
    u32 i;
    XPart *part;
    XPrim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *vd;
    u8 *va, *vb, *vc;
    u32 w;
    u32 m24;
    s32 code;
    u32 wx, wy, wz, wzh;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    if (*ctx != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)((u8 *)ctx + 0x64);
    func_800547D8(mtxsrc, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = (XPart *)((u8 *)model + 0x14);
    nparts = *(s32 *)((u8 *)model + 8);
    vtx = *(u8 **)((u8 *)model + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        vtp = &vt[0];
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wzh = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wzh;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wzh;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        box[4].vx = mn; box[4].vy = my; box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my; box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my; box[6].vz = wzh;
        box[7].vx = mx; box[7].vy = my; box[7].vz = wzh;
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
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
                if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                    prim = (XPrim *)part->prim;
                    nprim = part->nprim;
                    i = 0;
                    if (i >= nprim) goto noprim;
                    m24 = 0xFFFFFF;
                    do {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vt[0] = *(XV8 *)va;
                        vt[1] = *(XV8 *)vb;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        vt[2] = *(XV8 *)vc;
                        gte_ldv3c(vtp);
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
                                    if (((XFT3 *)pkt)->x0 > ((XFT3 *)pkt)->x1) {
                                        mx = ((XFT3 *)pkt)->x0;
                                        mn = ((XFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((XFT3 *)pkt)->x0;
                                        mx = ((XFT3 *)pkt)->x1;
                                    }
                                    if (((XFT3 *)pkt)->x2 > mx) mx = ((XFT3 *)pkt)->x2;
                                    else if (((XFT3 *)pkt)->x2 < mn) mn = ((XFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((XFT3 *)pkt)->y0 > ((XFT3 *)pkt)->y1) {
                                            my = ((XFT3 *)pkt)->y0;
                                            mny = ((XFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((XFT3 *)pkt)->y0;
                                            my = ((XFT3 *)pkt)->y1;
                                        }
                                        if (((XFT3 *)pkt)->y2 > my) my = ((XFT3 *)pkt)->y2;
                                        else if (((XFT3 *)pkt)->y2 < mny) mny = ((XFT3 *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, tz, q, rgb;
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
                                            if (code == 7) g.opz = za + 0x40;
                                            tz = g.opz;
                                            tp = (u32 *)prim->w0;
                                            q = 0x80 - (tz - 0x190) / 24;
                                            if (q < 0) q = 0;
                                            rgb = q | (q << 8) | (q << 16);
                                            ((XFT3 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                            ((XFT3 *)pkt)->uvc0 = tp[1] + (cl << 22);
                                            ((XFT3 *)pkt)->uvp1 = tp[2];
                                            ((XFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((tz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & m24) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & m24);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vd8 = *(XV8 *)vd;
                                    gte_ldv0(&vd8);
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
                                        gte_stsxy((long *)&((XFT4 *)pkt)->x3);
                                        if (((XFT4 *)pkt)->x3 < mn) mn = ((XFT4 *)pkt)->x3;
                                        else if (mx < ((XFT4 *)pkt)->x3) mx = ((XFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((XFT4 *)pkt)->y3 < mny) mny = ((XFT4 *)pkt)->y3;
                                            else if (my < ((XFT4 *)pkt)->y3) my = ((XFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb, tz, q, rgb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x40;
                                                *(u32 *)&((XFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((XFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((XFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tz = g.opz;
                                                tp = (u32 *)prim->w0;
                                                q = 0x80 - (tz - 0x190) / 24;
                                                if (q < 0) q = 0;
                                                rgb = q | (q << 8) | (q << 16);
                                                ((XFT4 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                                ((XFT4 *)pkt)->uvc0 = tp[1];
                                                ((XFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((XFT4 *)pkt)->uv2 = uvw;
                                                ((XFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((tz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & m24) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & m24);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                        i++;
                        prim++;
                    } while (i < nprim);
                    __asm__ __volatile__("" : "=r"(m24) : "0"(m24));
                  noprim: ;
                }
            }
        }
    }
    D_800A5E60 = pkt;
}



extern void func_80019064(void *a0);

void func_8017D6A0(void *a0) {

    extern u8 D_8018A3DC;
    extern void (*D_8018A404[])(void *);
    func_80019064(&D_8018A3DC);
    D_8018A404[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_8017D6F8(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8017D748(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017D748);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017D7CC);

extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_8017D928 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
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
 *   func_8017D928  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_8017D928(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_8017D97C(void)
{
    extern u8 D_801B203B;
    s32 i = 19;
    u8 *p = &D_801B203B;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_8017D9A0(void)
{

    extern u8 D_801B2028[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801B2028;
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



extern void (*D_8018A410[])(void);

void func_8017D9E4(void *a0) {
    D_8018A410[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801B203C + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017DC14(void*);
extern void func_8017DBE4(s32*);
extern int rand(void);

void func_8017DA20(int param_1)
{

    extern unsigned char D_801B203C[];
    register int iVar3 __asm__("$16");
    register int iVar3b __asm__("$19");
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801B203C + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    *(int *)(param_1 + 0x20) = iVar3;
    iVar3b = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8017DC14)(iVar5);
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
        ((void (*)(int))func_8017DBE4)(param_1);
    }
}




extern s32 func_8017DC28(s32 *a0, s32 a1);
extern void func_8017DBE4(s32 *a0);

void func_8017DB6C(s32 *a0)
{

    extern unsigned char D_801B203C[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801B203C + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_8017DC28(a0, table_base) == 0) {
            return;
        }
    }

    func_8017DBE4(a0);
}



















extern void func_80146C3C(void);
void func_8017DBE4(s32 *param_1)
{

    extern s8 D_801B2028;
  int new_var;
register s32 p __asm__("$4");
register s32 r __asm__("$3");
  p = (s32) (&D_801B2028);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}


void func_8017DC14(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_8017DC28 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_8017DC28(s32 *a0, s32 a1);
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
s32 func_8017DC28(s32 *a0, s32 a1) {
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



extern void (*D_8018A448[])(void);

void func_8017DC90(void *a0) {
    D_8018A448[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8017DCCC(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_8017DD68(s32 param_1);

void func_8017DD18(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_8017DD68(param);
    }
}


void func_8017DD60(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8017DECC();

void func_8017DD68(s32 param_1) {

    extern u32 *D_8018A440[];
    extern Blk8 D_8018A45C[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_8018A440[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_8018A45C[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8017DECC(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
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

extern SVECTOR_8017E6D8 D_801B253C[4];
extern struct PW8017E6D8 D_801B255C;
extern struct PW8017E6D8 D_801B2560;
extern u8 D_801B2564, D_801B2565, D_801B2566, D_801B2568, D_801B2569, D_801B256A;
extern int D_801B256C;

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

void func_8017DECC(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801B253C[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801B256C = 0x50000000;
        D_801B2564 = 0;
        D_801B2565 = 0;
        D_801B2566 = 0;
        D_801B2568 = 0;
        D_801B2569 = 0;
        D_801B256A = 0;
    }
    D_801B255C = h[0];
    D_801B2560 = h[1];

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



extern void func_8002931C(void);
    void func_8017E248(void) {
        ((void (*)(int))func_8002931C)(0x1A40000);
    }



extern void (*D_8018A54C[])(void);

void func_8017E268(void *a0) {
    D_8018A54C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E424(void);
extern void func_800167B8(s32 a0);

s32 func_8017E2A4(s32 a0) {
    func_8017E424();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017E2E8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018A554[])(void);

void func_8017E30C(void *a0) {
    D_8018A554[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E44C(void);

s32 func_8017E348(s32 a0) {
    func_8017E44C();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E388(u8 *a0) {
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
void func_8017E404(void) {
    func_800D1EBC();
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern char D_8018A560;

void func_8017E424(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018A560, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E44C(void) {

    extern s32 D_8018A564(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018A564, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017E474);


extern void (*D_8018A570[])(void);

void func_8017E510(void *a0) {
    D_8018A570[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017E54C);


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

void func_8017E5CC(s32 param_1, s16 *param_2) {
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


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017E764);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017EE3C);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F024);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F098);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F10C);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F278);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F438);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F600);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017F978);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017FC80);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8017FE3C);


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80180170);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801802E0);


extern void func_8017F278(void *a0);

void func_80180450(void *a0) {

    extern void (*D_8018B10C[])(void);
    D_8018B10C[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_8017F278(a0);
    }
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801804B0);

void func_80180598(void) {
}

extern void func_8002A04C(s32 a0);
    void func_801805A0(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x4;
        *(s16 *)((s32)a0 + 0x5C) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
        *(s8 *)((s32)a0 + 0xC1) = 0;
        ((void (*)(void))func_8002A04C)();
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801805D0);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8018072C);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801807AC);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80180834);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80180864);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_8018098C);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801809E4);

extern s32 func_80180A88(void);
    s32 func_80180A68(void) {
        return func_80180A88();
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80180A88);

s32 func_801810F4(void) {
        return 0x6F;
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801810FC);


/* TU declares func_80181234 as void(void) (S35 self-axis) but the asm takes
 * $a0 as a pointer parameter — bind through a private C name. */
extern void aF8017ED80(void *param_1) __asm__("func_80181234");

void aF8017ED80(void *param_1) {
    u8 *a0 = (u8 *)param_1;
    s32 pad_[4];
    s32 iVar2;
    u32 uVar1;

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
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;

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
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;
    }
}



/* func_80181408 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (open-only h_norm
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
 * Tail always calls ((void (*)(void *))func_80181234)(a0) (the TU's canonical decl for this
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
 * `extern void func_80181408(void);` (L4082, L4091) for callers that invoke it with NO args,
 * while the byte-true definition takes an s32 in $a0 -> `conflicting types`. Neither side can
 * move (a no-prototype escape is illegal once a param promotes), so the DEFINITION gets a
 * private C identifier and binds the emitted symbol with a GNU asm label. Zero blast radius:
 * the TU's declaration never meets the definition, and the emitted symbol is unchanged. */
void aF8017EF54(s32 a0) __asm__("func_80181408");

void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern void func_80181234(void);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2[2]; /* sp+0x24 -- dead, sizes the frame */
    } L;

    register s32 v1 __asm__("$3");
    register s32 cool __asm__("$2");
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
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
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
    __asm__ __volatile__("" ::: "memory");

    {
        s32 p = a0;
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x280;
        *(u16 *)(p + 0xFE) = *(u16 *)(p + 0xFE) - 0x280;
        ((void (*)(void *))func_80181234)((void *)p);
    }
}



extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_80181234(void);

void func_801815B4(s32 a0)
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
        ((void (*)(s32))func_80181234)(a0);
    }
}



extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_8012BE98(s32, u16*);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_801810FC(s32 a0, s32 a1);

void func_8018179C(s32 a0)
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
    func_8012B1B4(a0, (s32)sp10);
    func_8012CBCC(a0);

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0: {
        register s32 s0v __asm__("$16");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        register s32 p20 __asm__("$4");

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_801810FC(a0, 0x51) == 0) {
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
        func_8012B1B4(a0, (s32)sp10);
        break;
    }
    case 1: {
        s32 ret;

        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_801810FC(a0, 0x51) == 0) {
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
        func_801810FC(a0, 0x51);
        if (*(s16 *)(a0 + 0x102) == 0) {
            *(u16 *)(a0 + 0x34) = 3;
        } else {
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) - 1;
        }
        break;
    }
    case 3: {
        register s32 s2v __asm__("$18");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        if (func_801810FC(a0, 0x51) != 0) {
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




extern s32 func_801829FC(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);


void func_80181AD8(s32 param_1)
{

    extern u8 D_801A4BF8;
    extern u8 D_801A4C00;
    extern u8 D_801A4C08;
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

            func_801829FC(param_1, (s32)&D_801A4BF8);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801A4C00, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801A4C08, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
            L.rv[1] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
            L.rv[2] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
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
                __asm__("" : "=r"(ax) : "0"(ax));
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


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80181D80);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80181EB0);


extern void (*D_801A4C5C[])(void);

void func_80181F88(void *a0) {
    D_801A4C5C[*(u16 *)((s32)a0 + 0x2)]();
}



/* SV4 is the TU-canonical name (src/shared/engine_types.h) for func_8012F214's
 * in/out struct (see ov_SC06_008_jr_8017AE2C.c:3135, "SV4 svec" comment: func_8012F214 out).
 * Isolated match_one has no include path to that header, so it is typedef'd
 * locally here for the standalone compile only. */


/* func_80181FC4 - ov_SC06_008 / ov_SC06_008_jr_8017C294 (93 ins)
 *
 * One-time init (guarded by state flag at +0x34): mirror the +0x64 sub-object's
 * +0x20/+0x12 field into our own +0x20 sub-object, kick off two "core" calls,
 * pick an entry from the 2-element 12-byte table D_801A4C64 (indexed by the
 * s16 at +0x70), then call func_8012F214 with a zeroed input SV4 and read the
 * first 3 fields of the output SV4 back into +6/+0xA/+0xE.  Sets the countdown
 * at +0x1c to 0x5a and marks the state flag +0x34 = 1.
 *
 * Always-executed tail: bump the +0x20 sub-object's +0x10/+0x12/+0x14 fields
 * (reloading the +0x20 pointer fresh for each field -- no CSE across the
 * intervening stores, straight literal translation), mirror +0x14 into +0xDC,
 * call func_8012CBCC(a0) and test its return (canonical fleet decl is
 * void func_8012CBCC(s32 a0); the return value is read via a function-
 * pointer cast at the use site, per the established TU idiom -- see
 * ov_SC03_099_jr_8017BEBC.c:5630 comment block). If (ret & 0x6000), decrement
 * the +0xac counter (signed s16 compare-to-zero on the POST-decrement value --
 * gcc-2.7.2's sll-by-16/bnez idiom for a s16 local) and negate +0xDC into
 * +0x14; on the counter hitting zero, call func_8012C218. Finally decrement
 * the +0x1c countdown and call func_8012C218 again when IT hits zero.
 */

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);


void func_80181FC4(s32 a0)
{

    extern s32 D_801A4C64;
    SV4 in;
    SV4 out;
    s16 v1;
    u16 uStack_c;

    if (*(u16 *)(a0 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, *(s16 *)(a0 + 0x70) * 12 + (s32)&D_801A4C64);

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
        register s32 negdc __asm__("$2");
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



extern void (*D_801A4C7C[])(void);

void func_80182138(void *a0) {
    D_801A4C7C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182174);


extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_80181234(void);

void func_801821FC(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_80181234)(a0);
}




extern void func_80181408(void);
    void func_80182234(s32 *param) {
        *(s16 *)(*(s32 *)((char *)param + 0x20) + 0x10) = 0xE00;
        func_80181408();
    }


extern void func_80181408(void);
    void func_8018225C(u8 *a0) {
        s32 v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x10) += 0x20;
        func_80181408();
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182290);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801822DC);

extern void func_80181234(void);
    void func_801823C8(s32 *param) {
        param[0x10 / sizeof(s32)] >>= 1;
        param[0x18 / sizeof(s32)] >>= 1;
        func_80181234();
    }


extern void func_80181234(void);
    void func_801823FC(u8 *param_1) {
        param_1[0xC1] = 0xC;
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        ((void (*)(void))func_80181234)();
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182428);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801824B4);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801825DC);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182710);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182770);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182830);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80182904);


extern s32 D_801B2B08;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_801829FC(s32 a0, s32 a1) {
    D_801B2B08 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801B2B08;
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




s32 func_80182A2C(s32 param_1) {

    extern M2C_UNK D_80186D1C;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801A69F8;
    extern char * D_801A6A2C;
    extern char D_801B2AE8[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801A69F8) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80186D1C));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801B2B08, &s60);
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
        tmp = D_801A6A2C;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801A6A2C = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801B2AE8 < puVar4) {
        D_801A6A2C = D_801B2AE8 - 0x120;
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
            tmp = D_801A6A2C;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801A6A2C = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801B2AE8 < puVar4) {
            D_801A6A2C = D_801B2AE8 - 0x120;
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

s32 func_80182C70(s32 param_1) {

    extern signed char D_801A69E4[];
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
        p = D_801A69E4;
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
            p = D_801A69E4;
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



extern void (*D_801A6A30[])(void);

void func_80182F10(void *a0) {
    D_801A6A30[*(u16 *)((s32)a0 + 0x2)]();
}




// @class: schedule
// @stuck: none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_80182F4C(int param_1, short param_2)
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




/* func_8018315C — ov_SC06_008 / ov_SC06_008_jr_8017C294
 *
 * Two-arm actor tick keyed on the s16 countdown at actor+0xFC:
 *   arm A (counter == 0, the FALL-THROUGH / longer block): three func_8012C658
 *     spawns with offset pokes, a sound cue, two child-actor state pokes, an
 *     8-iteration 0x281 particle burst, then the RTP positional-sound block
 *     (the byte-proven RTP_SND shape from ov_SC03_099_jr_8017BEBC.c:5406).
 *   arm B (counter != 0): a func_8012913C(0x23) spawn scattered around the
 *     actor, VectorNormalSS toward D_801151D4->{0x5C,0x60,0x64}, sound 0xAF8.
 *
 * Declarations copied VERBATIM from the TU (one-pass grep, D2):
 *   D_801151D4      src/ov_SC06_008/ov_SC06_008_jr_8017C294.c:323
 *   rand            :956
 *   VectorNormalSS  :1849
 *   func_8012C658   :2523
 *   func_8012C588   :3767
 *   func_8012C218   :3782
 *   func_8002D4C8   :59
 *   func_8004914C   :2645
 *   func_800491AC   :2646
 *   func_8012913C   :4356  (non-prototype form, BELOW the splice point)
 *   func_8002AC00   :5447  (block-scope extern only)
 * RotTransPers / D_800AF648 / func_8002A04C are not in this TU -> fleet-dominant forms.
 */

extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();

void func_8018315C(s32 a0)
{

    extern s32  D_801151D4;
    extern u8 D_800AF648;

    /* L5: slot offsets are exact only through ONE struct — plain array locals
       get 8-byte-rounded slots and pushed z/flag to 0x28/0x2C (measured). */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s32 g;
    s32 s0;
    s32 i;

    g = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) == 0) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);

        s0 = *(s32 *)(a0 + 0xCC);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;
        s0 = *(s32 *)(a0 + 0xD0);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x30;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.rv[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.rv[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.rv[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
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
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }
        func_8002A04C(a0);
        func_8012C218((void *)a0);
    } else {
        s0 = (s32)func_8012913C(0x23);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
            *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0xE0;
            {
                s32 r = rand();
                s32 t = *(u16 *)(a0 + 0xE);
                *(s16 *)(s0 + 0x34) = 0x1800;
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = t + (r & 0x7F) - 0x40;
            }
            L.nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
            L.nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
            L.nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
            VectorNormalSS(L.nv, L.nv);
            *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
            *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
            *(s16 *)(s0 + 0x34) = 0x3000;
            func_8002D4C8(0xAF8, 0);
        }
        *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) - 1;
    }
}




// TARGET: func_80183560  (ov_SC06_008, TU ov_SC06_008_jr_8017C294.c, 93 ins)
//
// Template: func_801821F8 in this SAME TU (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c,
// around line 5283) is an already-MATCHED sibling (126 ins) with a documented byte-exact
// idiom set (its comment, verbatim):
//   @class: plumbing
//   @stuck: none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//     lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//     `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//     (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//     hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//     the `< 1` test.
//
// func_80183560 is the SAME body with the leading "if (*(short*)(param_1+0xfc)==0) {...}" block
// (the 0x64-indirected 3x int-copy + 3x u16-copy prologue) removed, and the "already fired" gate
// field is 0xe2 instead of 0x102. Confirmed against the target .s: no reference anywhere to 0xfc,
// 0x64, or 0x102/0x20 offsets; the gate compare is `lh $v1, 0xE2($s0)` / `sh $v1(=0xA), 0xE2($s0)`.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_80183560(int param_1)
{
    extern unsigned char D_801A7124[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    *(char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xe2) == 0) {
        *(short *)(param_1 + 0xe2) = 10;
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
                func_80019064(D_801A7124);
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


void func_801836D4(int param_1) {

    extern u8 D_801A7144[];
    extern u8 D_801A7088[];
    extern u8 D_801A7048[];
    extern u8 D_801A7090[];
    extern u8 D_801A7068[];
    extern u8 D_801AB3B0[];
    extern u8 D_801AE660[];
    extern u8 D_801A7184[];
    extern u8 D_801AE4C8[];
    extern u8 D_801AE550[];
    extern u8 D_801AE5D8[];
    int iVar1;

    iVar1 = func_8012C354(param_1, D_801A7144);
    if (iVar1 != 0) {
        if (*(short *)(param_1 + 0x70) != 0) {
            func_800599B8(D_801A7088, D_801A7048);
            func_800599B8(D_801A7090, D_801A7068);
            func_8001C214(*(int *)(param_1 + 0x20), D_801AB3B0);
        }
        *(u8 *)(param_1 + 0xc0) = 1;
        *(int *)(param_1 + 0xb4) = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        *(short *)(param_1 + 0xae) = 0x2100;
        func_8012A828(param_1, D_801AE660);
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
    *(u32 *)(param_1 + 0xbc) = (u32)D_801A7184;
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
        *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x18) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = 0x2400;
    *(u16 *)(param_1 + 2) = 8;
    func_8012A828(param_1, D_801AE4C8);
    func_8012A828(*(int *)(param_1 + 0xcc), D_801AE550);
    func_8012A828(*(int *)(param_1 + 0xd0), D_801AE5D8);
    return;
}



/* func_80183884 — ov_SC06_008 / ov_SC06_008_jr_8017C294.  MATCH 163/163.
 * Family of 7 (ov_SC06_008/010/018/022/024/032/033, all 163 ins, all still in
 * nonmatchings) — §136e applies: no twin existed, so this is derived from the .s.
 * The byte-proven accumulate head (b744 nested inside b608, then two RE-LOADS of
 * *(s32*)(a0+0x20)) is copied verbatim from src/ov_SC03_099/..._jr_8017BEBC.c:5424.
 *
 * Four levers, each measured against match_one:
 *
 * 1. NO frame padding.  args_size already fills sp+0x00..0x1F, so the four saved
 *    regs land at 0x20..0x2F and the frame is 0x30 with ZERO locals.  A 16-byte
 *    dead aggregate (idiom 6, added on the first draft from a mis-derived
 *    args_size=0x10) made it 0x40 — idiom 6 only applies when the reg-save area
 *    does NOT start at args_size.
 *
 * 2. BRANCH POLARITY / BLOCK LAYOUT (§3-T4, T7).  `if (C) goto X;` followed by a
 *    `break` is REWRITTEN by jump.c's jump-around-jump inversion into
 *    `if (!C) goto break_target;` — which is the wrong polarity here.  The target
 *    wants the true arm to FALL THROUGH.  Two rewrites, both worth +0 instructions
 *    but different bytes:
 *      case 1: `if (A||B) goto st2; break;`  ->  `if (!A && !B) break; goto st2;`
 *              (TRUTH_ANDIF gives reversed branches to `next`, and the trailing
 *               `j st2` is the fall-through — exactly `beqz L600 / j L5E0`.)
 *      case 3: same shape, plus the range test written as the POSITIVE
 *              `if (r >= -0xFF && r <= 0xFF) break;` so fold_range_test's
 *              `sltiu (r+0xFF),0x1FF` branches on TRUE to the switch end and case 3
 *              falls through into st2 (saves the `j`+`nop`, 165 -> 163 ins).
 *    Case 0 keeps the plain `if (A||B) {..} else {..}` — there jump.c's inversion
 *    IS what the target has.
 *
 * 3. THE SHARED STORE BLOCK.  L801815F8/L801815FC (`li v0,1` / `sh v0,0x34`) sit
 *    AFTER st2 in the target, so they are NOT inline `else` arms (cross-jumping
 *    keeps the LAST copy, which would put them BEFORE st2).  They are explicit
 *    trailing labels inside the switch with an `ns` join variable; case 2 enters at
 *    `setstate` with ns=3, cases 0 and 3 enter at `set1`.
 *
 * 4. REGALLOC-PERM -> the $16 pin (see below).
 */

extern s32 rand(void);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_8012BE98(s32, u16*);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern int func_80182F4C(int param_1, short param_2);

void func_80183884(s32 a0) {

    extern u8 D_801A71A4[];

    /* §137/K3+K5: unpinned, the a0-copy allocno (R=37/L=137, pri 13503) is
     * ranked first and first-fits $s0, pushing `tbl` to $s1 — a clean 2-reg
     * perm no source reordering can flip (pri(tbl) = 394). Pinning `tbl` to
     * $16 makes $s0 "already dirty" in find_reg pass 0: the a0 copy conflicts
     * with it and opens $s1, and case 3's `d` (which does NOT conflict with
     * `tbl`) grabs $s0 in pass 0 — exactly the target's assignment. */
    register s32 tbl __asm__("$16");
    s32 ns;

    tbl = (s32)D_801A71A4;
    func_8012B1B4(a0, tbl);
    func_8012CBCC(a0);

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_80182F4C(a0, 0x48) != 0 ||
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) >
                0x3FFFF) {
            s32 r = func_8012B608(
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
            func_8012B1B4(a0, tbl);
        } else {
            goto set1;
        }
        break;

    case 1:
        if (func_80182F4C(a0, 0x48) == 0 &&
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) <=
                0x3FFFF) {
            break;
        }
        goto st2;

    case 2: {
        s32 r = func_8012B608(
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
            func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }
        func_80182F4C(a0, 0x48);
        {
            s16 c = *(s16 *)(a0 + 0x102);
            if (c == 0) {
                ns = 3;
                goto setstate;
            }
            *(s16 *)(a0 + 0x102) = c - 1;
        }
        break;

    case 3: {
        void *p88 = (void *)(a0 + 0x88);
        s32 d = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
        if (func_80182F4C(a0, 0x48) == 0) {
            if (d > 0x40000) {
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                                      func_8012B744((void *)(a0 + 4), p88), 1);
                if (r >= -0xFF && r <= 0xFF) {
                    break;
                }
            } else {
                goto set1;
            }
        }
    }
        /* fall through into st2 */
    st2:
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0x102) = (rand() & 7) + 8;
        break;

    set1:
        ns = 1;
    setstate:
        *(u16 *)(a0 + 0x34) = ns;
        break;
    }

    {
        s16 t = *(s16 *)(a0 + 0x100);
        if (t != 0) {
            *(s16 *)(a0 + 0x100) = t - 1;
        } else if (((s32(*)(s32))func_8012BE54)(a0) <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 5;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
#define RTP_SND(sndid)                                                        \
    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);                            \
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);                            \
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);                            \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); } \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); } \
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);                        \
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF              \
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {           \
        s32 x = (s16)L.sxy[0];                                                \
        s32 ax;                                                               \
        ax = x;                                                               \
        if (x < 0) {                                                          \
            ax = -x;                                                          \
        }                                                                     \
        ax = ((0xF0 - ax) * 0x7F) / 0xF0;                                     \
        __asm__("" : "=r"(ax) : "0"(ax));                                     \
        x = (x + 0xF0) / 0x1E;                                                \
        if (x == 0x10) {                                                      \
            x = 0xF;                                                          \
        }                                                                     \
        x = x << 8;                                                           \
        {                                                                     \
            s32 flg = 0x3000;                                                 \
            func_8002D4C8(sndid, ((ax | flg) | x) & 0xFFFF);                  \
        }                                                                     \
    }

void func_80183B10(s32 a0) {

    extern u8  D_800AF648;
    extern s32 D_801A7008[];
    extern u8  D_801AE4C8[];
    extern u8  D_801AE550[];
    extern u8  D_801AE5D8[];
    struct {
        s16 pad0[4];  /* sp+0x10 — dead, but sizes the frame (idiom 6) */
        s16 v[3];     /* sp+0x18 */
        s16 pad1;     /* sp+0x1E */
        u16 sxy[2];   /* sp+0x20 */
        s32 z;        /* sp+0x24 */
        s32 flag;     /* sp+0x28 */
    } L;
    s32 t;
    s32 ang;
    s32 idx;
    s32 m;
    s32 c;
    s32 p;

    if (*(s16 *)(a0 + 0x98) == 0) {
        s32 spr = (s32)func_8012913C(0x7F);
        if (spr != 0) {
            m = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)
              + (func_8004787C(*(s16 *)(a0 + 0x104)) >> 3);
            *(s16 *)(spr + 0x6) = *(u16 *)(a0 + 0x6) - (func_8004787C(m) * 0x6C) / 0x1000;
            *(s16 *)(spr + 0xA) = *(u16 *)(a0 + 0xA) - 0x34;
            *(s16 *)(spr + 0xE) = *(u16 *)(a0 + 0xE) - (func_80047948(m) * 0x6C) / 0x1000;
            *(s32 *)(spr + 0x14) = 0x40000;
            *(s32 *)(spr + 0x10) = -(func_8004787C(m) * 0xC0);
            *(s32 *)(spr + 0x18) = -(func_80047948(m) * 0xC0);
        }
        t = *(u16 *)(a0 + 0x104) + 0x100;
        *(s16 *)(a0 + 0x104) = t;
        ang = (s16)t;
        idx = ang / 0x100;
        m = (s16)(idx % 0x10);
        if (ang == 0x100) {
            RTP_SND(0x95F)
        } else if (m == 0) {
            RTP_SND(0x960)
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = D_801A7008[m];
        c = *(u16 *)(a0 + 0x100) - 1;
        *(s16 *)(a0 + 0x100) = c;
        if ((s16)c == 0) {
            p = *(s32 *)(a0 + 0xCC);
            *(s16 *)(a0 + 0x98) = 1;
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
            p = *(s32 *)(a0 + 0xD0);
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
        }
    } else if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 7;
        *(s16 *)(a0 + 0x100) = 0x3C;
        func_8012A828(a0, D_801AE4C8);
        p = *(s32 *)(a0 + 0xCC);
        if (p != 0) {
            func_8012A828(p, D_801AE550);
        }
        p = *(s32 *)(a0 + 0xD0);
        if (p != 0) {
            func_8012A828(p, D_801AE5D8);
        }
    }
}



extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80183FD4(s32 a0) {

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    s16 hp;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp < 0x301) {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + total;
    } else {
        p = *(s32 *)(a0 + 0xD0);
        *(s16 *)(a0 + 2) = 3;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x98) = 0;
        *(s16 *)(p + 2) = 3;
        *(s32 *)(p + 0x1C) = 0x1E;
        *(s16 *)(p + 0x98) = 0;

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
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
            func_8002D4C8(0x961, (ax | (0x3000 | x)) & 0xFFFF);
        }
    }
    func_8012B370(a0);
}


extern s32 func_801823F0(void);

/* func_801841A4 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (family of 7)
 *
 * Low-HP flinch/knockback reaction. hp = *(s16*)(a0->0x20 ptr + 0x14). If
 * 0 < hp < 0xD00, put self AND the partner at a0->0xCC into stagger state 3
 * (a 0x1E-frame timer, status flag cleared), compute a screen-space
 * position via RotTransPers and play a positional sound. Otherwise
 * (hp==0 or hp>=0xD00) apply the accumulated hit-combo counter (0xFC/0xFE)
 * to the target's HP and re-mask its low 12 bits.
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND form from func_8018165C in this same TU (line 4746) -- v[]/pad,
 * u16 sxy[2], s32 z, s32 flag, and the ax/x div-by-0xF0 / div-by-0x1E
 * magic-constant idiom (0x88888889); also confirmed against func_801823F0
 * (same TU) which reuses the identical sndid 0x961 and the identical
 * `sx = (sx + 0xF0) / 0x1E; if (sx == 0x10) sx = 0xF; sx <<= 8;` tail.
 *
 * Control flow: gcc-2.7.2 lays out basic blocks in literal SOURCE order, not
 * by fallthrough-preference. A nested-if spelling (`if (hp<0xD00) { state=3;
 * if (hp!=0) { B; goto end; } } A; end:`) places B (textually the inner
 * then-body) inline right after the tests and relocates A after it -- the
 * REVERSE of the target, which has the short block A inline and the long
 * RTP+sound block B out-of-line. Explicit goto/label with A written BEFORE B
 * in source (`if (hp>=0xD00) goto L_A; state=3; if (hp!=0) goto L_B; L_A: A;
 * goto L_end; L_B: B; L_end: ...`) reproduces the target's physical layout
 * directly -- no branch-polarity inversion needed, just source ORDER.
 *
 * Frame: RotTransPers args are sp+0x10 (v), sp+0x18 (&sxy), sp+0x1C (&z),
 * sp+0x20 (&flag); v[3]+pad1 fills 0x10-0x17, sxy 0x18-0x1B, z 0x1C-0x1F,
 * flag 0x20-0x23 -- leaves a dead 4 bytes (0x24-0x27) before the s0 save at
 * 0x28. A trailing `pad2` dead struct member (same aggregate, so it can't
 * be eliminated) reserves those 4 bytes, mirroring func_8018165C's own
 * "dead aggregate sizes the frame" idiom (comment there: idiom 6).
 */

extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_801841A4(s32 a0) {

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2;    /* sp+0x24 -- dead, sizes the frame */
    } L;

    s16 hp;
    s32 state;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp >= 0xD00) {
        goto L_A;
    }
    state = 3;
    if (hp != 0) {
        goto L_B;
    }

L_A:
    {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;
    }
    goto L_end;

L_B:
    p = *(s32 *)(a0 + 0xCC);
    *(s16 *)(a0 + 2) = state;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(s16 *)(a0 + 0x98) = 0;
    *(s16 *)(p + 2) = state;
    *(s32 *)(p + 0x1C) = 0x1E;
    *(s16 *)(p + 0x98) = 0;

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
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
        func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_end:
    func_8012B370(a0);
}


extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern void func_8012C218(void *a0);
extern int func_80143C74(short *, int);
extern s32 rand(void);

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80184394(s32 a0)
{

    extern void (*D_801A71B4[])(void);
    extern u8 D_800AF648;
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    D_801A71B4[*(u16 *)(a0 + 0x2)]();

    if (*(u16 *)(a0 + 0x0) != 0) {
        if (*(s16 *)(a0 + 0x70) == 0 && func_8012C044(a0) != 0) {
            if (*(s32 *)(a0 + 0xCC) != 0) {
                func_8012C218(*(void **)(a0 + 0xCC));
            }
            if (*(s32 *)(a0 + 0xD0) != 0) {
                func_8012C218(*(void **)(a0 + 0xD0));
            }
            func_8012C098((void *)a0);
        } else {
            s16 v;

            v = *(s16 *)(a0 + 0xE2);
            if (v != 0) {
                v = v - 1;
                *(s16 *)(a0 + 0xE2) = v;
                if (v == 0) {
                    *(u16 *)(a0 + 0x5C) &= 0xBFFF;
                }
            }

            if ((*(s16 *)(a0 + 0x76) < 5) && ((rand() & 3) == 0)) {
                s32 iVar2 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
                s32 r;

                if (iVar2 != 0) {
                    r = rand();
                    *(s32 *)(iVar2 + 0x10) = ((r & 0x7FF) - 0x400) << 8;
                    *(s32 *)(iVar2 + 0x14) = 0xFFF00000;
                    r = rand();
                    *(s32 *)(iVar2 + 0x18) = ((r & 0x7FF) - 0x400) << 8;
                    r = rand();
                    *(u16 *)(iVar2 + 0x6) -= 0x20;
                    *(u16 *)(iVar2 + 0x6) += (r & 0x3F);
                    *(s16 *)(iVar2 + 0xA) -= 0xC0;
                    r = rand();
                    *(u16 *)(iVar2 + 0xE) -= 0x20;
                    *(u16 *)(iVar2 + 0xE) += (r & 0x3F);
                }
            }

            if (*(u16 *)(a0 + 0x2) != 1 && *(u16 *)(a0 + 0x2) != 5) {
                *(s16 *)(a0 + 0x84) = 0xE;
            } else {
                if (*(s16 *)(a0 + 0x84) != 0) {
                    *(s16 *)(a0 + 0x84) = *(s16 *)(a0 + 0x84) - 1;
                } else {
                    *(s16 *)(a0 + 0x84) = 0xE;

                    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
                    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
                    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
                    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
                    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
                    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
                    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                        s32 x = (s16)L.sxy[0];
                        s32 ax;
                        ax = x;
                        if (x < 0) {
                            ax = -x;
                        }
                        ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                        __asm__("" : "=r"(ax) : "0"(ax));
                        x = (x + 0xF0) / 0x1E;
                        if (x == 0x10) {
                            x = 0xF;
                        }
                        x = x << 8;
                        {
                            s32 flg = 0x3000;
                            func_8002D4C8(0x8BF, ((ax | flg) | x) & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
}



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

void func_801846AC(int param_1)
{

    extern unsigned char D_801A7124[];
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
                func_80019064(D_801A7124);
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





extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 *func_8012913C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

void func_801848A4(s32 a0) {

    extern s32 D_801151D4;

    extern void func_8002AC00(s32 arg0);
    extern void func_8002A04C(s32 arg0);
    extern u8 D_800AF648;

    u16 v10[4];   /* sp+0x10 */
    s16 v18[4];   /* sp+0x18 */
    s32 sxy;      /* sp+0x20 */
    s32 z;        /* sp+0x24 */
    s32 flag;     /* sp+0x28 */
    s32 base;
    s32 iv;
    s32 i;
    s32 t;
    s32 r;

    base = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) - 5;
        }
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) + 5;
        }
        iv = func_8012C658(0x32, 2, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) + 8;
        }

        func_8002AC00(0x22);

        iv = *(s32 *)(a0 + 0x64);
        *(s16 *)(iv + 2) = 2;
        iv = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0);
        *(s16 *)(iv + 2) = 4;
        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC) = 0;

        i = 0;
        do {
            iv = func_8012C588(0x281, a0);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(s16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(s16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);

        v18[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        v18[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        v18[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)v18, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((*((u16 *)&sxy + 1) + 0xB3) & 0xFFFF) < 0x167) {
            s32 sx;
            s32 av;

            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            /* one local for |x| AND the volume: gcc-2.7.2 keeps the single pseudo
               in $v1 in place (subu $v1,$v0,$v1); a separate `vol` local steals $a1
               and the whole OR chain drifts (cookbook §136 L1). */
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
        }

        func_8002A04C(a0);
        func_8012C218((void *)a0);
        return;
    }

    iv = (s32)func_8012913C(0x23);
    if (iv != 0) {
        r = rand();
        *(u16 *)(iv + 0x06) = *(u16 *)(a0 + 0x06) + (r & 0x7F) - 0x40;
        r = rand();
        *(u16 *)(iv + 0x0A) = *(u16 *)(a0 + 0x0A) + (r & 0x7F) - 0x80;
        r = rand();
        *(u16 *)(iv + 0x0E) = *(u16 *)(a0 + 0x0E) + (r & 0x7F) - 0x40;

        t = func_80047948((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s32 *)(iv + 0x04) = *(s32 *)(iv + 0x04) + (t << 10);

        t = func_8004787C((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(u16 *)(iv + 0x34) = 0x1800;
        *(s32 *)(iv + 0x18) = 0;
        *(s32 *)(iv + 0x14) = 0;
        *(s32 *)(iv + 0x10) = 0;
        *(s32 *)(iv + 0x0C) = *(s32 *)(iv + 0x0C) - (t << 10);

        v10[0] = *(s32 *)(base + 0x5C) - *(u16 *)(iv + 0x06);
        v10[1] = *(s32 *)(base + 0x60) - *(u16 *)(iv + 0x0A);
        v10[2] = *(s32 *)(base + 0x64) - *(u16 *)(iv + 0x0E);
        VectorNormalSS(v10, v10);

        *(u16 *)(iv + 0x06) = *(u16 *)(iv + 0x06) + ((s16)v10[0] >> 6);
        *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) + ((s16)v10[1] >> 6);
        *(u16 *)(iv + 0x0E) = *(u16 *)(iv + 0x0E) + ((s16)v10[2] >> 6);
        *(u16 *)(iv + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



// @class: struct
// @stuck: none — MATCH

extern int rand(void);
extern int func_80143C74(short *, int);
extern int func_80047948(int);
extern int func_8004787C(int);

void func_80184CEC(short *param_1)
{

    extern void (*D_801A723C[])(short *);
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
    D_801A723C[*(unsigned short *)(param_1 + 1)](param_1);
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




extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8  *func_8012913C();
extern s32  rand(void);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  VectorNormalSS(void *a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002A04C(s32 a0);


void func_80184EFC(s32 a0) {

    extern s32 D_801151D4;

    extern u8 D_800AF648;
    extern void func_8002AC00(s32 arg0);

    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 v[4];    /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;
    s32 p;
    s32 s0;
    s32 i;

    p = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);
        s0 = *(s32 *)(a0 + 0x64);
        *(s16 *)(s0 + 0x2) = 4;
        s0 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC);
        *(s16 *)(s0 + 0x2) = 4;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }

        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0) = 0;
        func_8002A04C(a0);
        func_8012C218((void *)a0);
        return;
    }

    s0 = (s32)func_8012913C(0x23);
    if (s0 != 0) {
        *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
        *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0x80;
        *(s16 *)(s0 + 0xE) = *(u16 *)(a0 + 0xE) + (rand() & 0x7F) - 0x40;

        *(s32 *)(s0 + 0x4) =
            *(s32 *)(s0 + 0x4) -
            func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
        {
            s32 t = func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
            *(s16 *)(s0 + 0x34) = 0x1800;
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)(s0 + 0x10) = 0;
            *(s32 *)(s0 + 0xC) = *(s32 *)(s0 + 0xC) + t;
        }

        L.nv[0] = *(s32 *)(p + 0x5C) - *(u16 *)(s0 + 0x6);
        L.nv[1] = *(s32 *)(p + 0x60) - *(u16 *)(s0 + 0xA);
        L.nv[2] = *(s32 *)(p + 0x64) - *(u16 *)(s0 + 0xE);
        VectorNormalSS(L.nv, L.nv);

        *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
        *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
        *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
        *(s16 *)(s0 + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(s16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



extern s32 rand(void);
extern s32 func_80143C74();
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80185340(s32 a0) {

    extern void (*D_801A72B4[])(s32);
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

    D_801A72B4[*(u16 *)(a0 + 2)](a0);

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

extern u16 D_801270C0;

void func_80185550(s32 arg0) {

    extern u8  D_801A7098;
    extern u8  D_801A70A4;
    extern u16 D_80126B96;
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (*(u16 *)(arg0 + 2) == 0) {
        *(u8 **)(*(s32 *)(arg0 + 0x20) + 0x20) = &D_801A7098;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x50000000;
        *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x59;
        func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)&D_801A70A4);
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


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801857D4);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801857F4);

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801858F4);


extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80185994(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80185A54);



















void func_80185AEC(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80185B0C);

void func_80185BFC(void) {
}

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80185C04);


extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80185CD8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int a0);
    void func_80185D98(void) {
        ((void (*)(void))func_8012B370)();
    }




















void func_80185DB8(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80185DD8);

void func_80185ECC(void) {
}

INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_80185ED4);


extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80185FC8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int a0);
    void func_80186088(void) {
        ((void (*)(void))func_8012B370)();
    }


INCLUDE_ASM("asm/ov_SC06_010/nonmatchings/ov_SC06_010_jr_8017A4AC", func_801860A8);

extern void (*D_801AEF60[])(void);

void func_801861C4(void *a0) {
    D_801AEF60[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_801868AC(void);

void func_80186200(void *a0) {

    extern s32 D_801AECB8[];
    extern u8 D_801AEC50[];
    extern u8 D_80186D1C[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801AEC50);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801AECB8[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_801868AC);
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
        func_8012A828((s32)a0, D_80186D1C);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_801862D4(void *a0) {
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


void func_801862FC(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80186304(void *a0) {

    extern s32 D_801AEE9C;
    extern s32 D_801AEE88;
    extern s32 D_801AEE84;
    extern s32 D_801AEF1C;
    extern s32 D_801AEEB0;
    extern s32 D_801AED7C[];
    extern s32 D_801AEE00[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801AEE9C = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801AEE84 = 0;
                D_801AEE88 = D_801AEE00[v0];
            } else {
                D_801AEE88 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801AEE00[v0], 1);
                D_801AEE84 = 2;
            }
        } else {
            D_801AEE9C = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801AEE84 = 0;
            D_801AEE88 = D_801AED7C[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801AEEB0);
    } else {
        p = &D_801AEF1C;
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
extern s32 func_80186654(void);

void func_80186450(void *arg0) {

    extern s32 D_801AECB8[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801AECB8[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801AECB8[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80186654() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



extern void func_8012C218(void *a0);
    s32 func_80186570(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_8018659C(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_801865AC(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_801865BC(void *a0) {

    extern s32 D_801AECB8[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801AECB8[idx], 1);
}


extern void func_8014ADA8(s32 a0, s32 a1);
    extern s32 D_80126B58;
    void func_801865FC(void *arg0) {
        s32 temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
        func_8014ADA8((s32)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
    }


extern s16 func_80174764(void);
s32 func_80186630(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_80186654(void) {

    extern s32 D_801AECB8[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801AECB8[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


extern void (*D_801AEF88[])(void);

void func_801866B8(void *a0) {
    D_801AEF88[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_801866F4(void *a0) {

    extern u8 D_801AEC84[];
    extern u8 D_801AF648[];
    extern u8 D_801AF428[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801AEC84) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801AF648);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801AF428);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018677C(void *a0) {

    extern u8 D_801AF438[];
    extern u8 D_801AF540[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801AF438);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801AF540);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_8018683C — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801AF648, else
 * D_801AF428), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801AF648 / D_801AF428)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_8018683C(void *a0) {

    extern u8 D_801AF648[];
    extern u8 D_801AF428[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801AF648);
        } else {
            func_8012A828((s32)a0, D_801AF428);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801AEF78[];
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

s32 aF8018A224() __asm__("func_801868AC");

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

    RotTransSV(D_801AEF78, sv0, &flag);
    RotTransSV(D_801AEF78 + 8, sv1, &flag);

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




