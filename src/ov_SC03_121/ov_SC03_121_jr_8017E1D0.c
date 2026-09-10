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
    s16 a;
    s16 b;
    s16 c;
} Pt6_8017D65C;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_801846BC;
extern u8 D_8018462C;
extern u8 D_80184608;
extern u8 D_801845E4;
extern u8 D_80184698;
extern u8 D_80184674;
extern u8 D_80184650;
extern u8 D_801845C0;
extern void func_80145934(void);
extern u8 D_8018474C;
extern u8 D_80184728;
extern u8 D_80184704;
extern u8 D_801846E0;
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
extern unsigned char D_80183B44[];
extern unsigned char D_80183B74[];
extern unsigned char D_80183BC4[];
extern unsigned char D_80183BF4[];
extern unsigned char D_80183C24[];
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
extern void (*D_80183C74[])(void *);
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
extern s32 D_80183D3C[];
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
extern u8 D_80183DC4[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80183DCC;
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
extern int D_801ADB28;
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
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801ADB2C;
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
extern s32 D_80183DFC;
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
extern void (*D_80183EA4[])(void);
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
extern void (*D_80183EC8[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80183EB8;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80183EDC[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80183EE8[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80183EF8[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80183F10[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80183F00;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80183F24[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80183F40[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80183F30;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80183F54[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80183F68[])(void);
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
extern s32 D_80183F7C;
extern void (*D_80183FA4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80183F84;
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
extern int (*D_80183FF0[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80183FF4[])(void);
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
extern unsigned short D_80184458[];
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
extern void (*D_80184468[])(void);
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
extern int D_801ADB60;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80184490[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80184470;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80184480;
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
extern void (*D_801844D0[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801844D8[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801844A4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801844E4[])(void);
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
extern u8 D_801844B4;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801ADB68;
extern s32 D_801ADB74;
extern s32 D_801ADB78;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80184520[])(s32 *);
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
extern s32 D_801844F4[];
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
extern s32 D_801ADB70;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80184770[])(void);
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
extern char D_80184590[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80184814[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80184968[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80184784;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80184970[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80184794;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_801847B4;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80184978[])(void);
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
extern void (*D_801849A0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_801849AC[])(void);
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
extern void (*D_80184820[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80184A50;
extern void func_8015D380(s32 a0);
extern unsigned char D_80183B34[];
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
extern unsigned char D_80184A64[];
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
extern s8 D_80184AA0[];
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
extern u16 D_80184AE8;
extern u16 D_80184AEA;
extern u16 D_80184AEC;
extern s32 D_80184AF0;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80184AF8;
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
extern int D_80184804;
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
extern unsigned int D_80184B7C[];
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
extern void (*D_80184C2C[])(void);
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
extern u16 D_80184C5C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80184CC0;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801ADB80[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80184CE4[])(void);
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
extern int D_801ADBD8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80184D2C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80184D1C;
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
extern char D_801AD3EC[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80184D34[])(void);
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
extern void (*D_80184D88[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80184D50;
extern s16 D_80184D84;
extern s16 D_80184D82;
extern s16 D_80184D80;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80184D94[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801ADC38;
extern u8 D_801ADC39;
extern u8 D_801ADC3A;
extern u8 D_801ADC3B;
extern u8 D_801ADC3C;
extern u8 D_801ADC3D;
extern u8 D_801ADC3E;
extern u8 D_801ADC3F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80184DA4[])(void);
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
extern s32 D_801ADC78;
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
extern void (*D_80184DE8[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80184E64[];
extern s32 D_80184E84[];
extern u8 D_80184F00[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80184F20[];
extern u8 D_80184F40[];
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
extern void (*D_80184FDC[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80185058[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801AD3FC;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80185064[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018506C[])(void);
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
extern void (*D_80185134[])(void);
extern void func_80166618(void *a0);
extern void (*D_80185144[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80185154[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80185160[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_801850C0[];
extern u8   D_801850D4[];
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
extern void (*D_80185178[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80185180[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80185188[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80185190[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80185198[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801851A0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801851A8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018525C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80185264[])(void);
extern void func_80169F00(void *a0);
extern char D_80185214[];
extern char D_801851D4[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018529C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801852A8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801852F0[])(void);
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
extern void (*D_8018536C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801ADF98;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80185360[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801853A4[];
extern unsigned short D_801853AC[];
extern unsigned short D_801853B4[];
extern unsigned char D_801ADFA0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801ADF98;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_801853BC[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801AE0D4;
extern M2C_UNK D_801AE0D8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801AE060;
extern void (*D_801853EC[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801AE0DC[];
extern u8 D_801AE0E4[];
extern u8 D_801AE094[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801853F4[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80185410[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80185418[])(void);
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
extern void (*D_80185480[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80185424;
extern u8 D_80185430;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_801854B4[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_801854BC[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80185510[])(void);
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
extern u16 D_80185544[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80185534[];
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
extern s32 D_80185560;
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
extern void (*D_801855D8[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801855E0[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801855E8[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801855F0[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801855F8[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80185600[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018560C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80185618[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80185624[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80185634[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80185644[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018564C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80185654[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018565C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80185664[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018566C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80185674[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018567C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80185684[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018568C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80185694[])(void);
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
extern void (*D_8018569C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801856A4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_801856AC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_801856B4[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_801856BC[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_801856C4[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801856CC[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801856D4[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_801856DC[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801856E4[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801856EC[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801856F4[])(void);
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
extern void (*D_80185738[])(void);
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
extern M2C_UNK D_801856FC;
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
extern void (*D_80185768[])(void);
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
extern void (*D_801857A4[])(void);
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
extern void (*D_801857FC[])();
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
extern void (*D_8018580C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80185814[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018597C[])();
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
extern void (*D_80185988[])();
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
extern M2C_UNK D_801AD644;
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
extern s16 D_801AEF38;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801AE818;
extern short D_801AEFAC;
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
extern s32 D_801AEC44;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801AEC6C;
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
extern s16 D_801AEC28;
extern s32 func_8017A3B0(void);
extern short D_801AEC64;
extern short D_801AEC60;
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
extern s16 D_801AEC2C;
extern u16 D_801AECAC;
extern u16 D_801AECAE;
extern u16 D_801AECB0;
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
extern s16 D_801AECA4;
extern s16 D_801AECA6;
extern s16 D_801AECA8;
extern s16 D_801AEC9C;
extern s16 D_801AEC9E;
extern s16 D_801AECA0;
extern void func_8017B7A8(void);
extern s16 D_801AECBC;
extern s16 D_801AECBE;
extern s16 D_801AECC0;
extern s16 D_801AECC4;
extern s16 D_801AECC6;
extern s16 D_801AECC8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801AECB4;
extern short D_801AECB6;
extern short D_801AECB8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801AEC4C;
extern SV4 D_801AEC54;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801AEC74[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801AEC70)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80185B64[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void func_8017CD9C(void *a0);
extern void func_8017CE3C(s32 a0);
extern void func_8017CDF4(s32 a0);
extern s32 func_80148E54(void *a0);
extern void func_8017D024();
extern void func_8017CEA4(u8 *a0);
extern void func_8017D024(s32 a0);
extern void func_8017D064(void *a0);
extern void func_8017D104(s32 a0);
extern void func_8017D0BC(s32 a0);
extern void func_8017D1B4(void);
extern void func_8017D1BC(void);
extern void (*D_80185C2C[])(void);
extern void func_8017D1DC(void *a0);
extern void func_8017D374(void);
extern s32 func_8017D218(s32 a0);
extern s32 func_8017D25C(void);
extern void (*D_80185C34[])(void);
extern void func_8017D280(void *a0);
extern s32 func_8017D2BC(u8 *a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D2D8(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D354(void);
extern void func_8017D39C(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D460(void*);
extern void func_8017D3C4(void);
extern void (*D_80185C58[])(void);
extern void func_8017D460(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D4C4(s32 param_1, s16 *param_2);
extern s16 D_80185CAC[];
extern s32 func_801343C4(s32 angle, s32 p1, s32 p2);
extern s32 func_8017D65C(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_8012B14C(s32 a0, s32 a1);
extern u8 D_8018E3F4[];
extern u8 D_80185D98[];
extern u8 D_8018D9F4[];
extern void func_8017DDB4(s32 a0);
/* ==== end §8b carried decl layer ==== */

extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017D65C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern u8 D_8018E3F4[];
extern u8 D_8018D9F4[];
extern s32 D_8018D8AC;
extern u8 D_80185DA4[];
extern s16 D_80185CAC[];

void func_8017E1D0(s32 param_1) {
    s32 s0;
    s32 mv[4];
    s16 sp20[4];
    s16 sp28[4];
    s32 v0;
    s32 s1;

    s0 = param_1;
    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
            func_8012A828(s0, (s32)((u8 *)&D_8018D8AC));
        }
        v0 = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12),
                           func_8012B744((void *)(s0 + 4), (void *)(s0 + 0x88)), 8);
        if (v0 != 0) {
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF;
        } else {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012B1B4(s0, (s32)D_80185DA4);
            func_8012A828(s0, (s32)D_8018D9F4);
            *(u16 *)(s0 + 0x10A) = 0;
            *(s32 *)(s0 + 0x1C) = 0x3C;
        }
        break;
    case 1:
        if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
            func_8012A828(s0, (s32)D_8018D9F4);
            func_8012B1B4(s0, (s32)D_80185DA4);
        }
        if (*(s32 *)(s0 + 0x94) == 0 || *(s32 *)(s0 + 0x94) == 0x17) {
            func_8002D4C8(0x70A, 0);
        }
        if ((((s32 (*)(s32))func_8012CBF4)(s0) & 0x8000) != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012A828(s0, (s32)D_8018E3F4);
            func_8012B14C(s0, (s32)D_80185DA4);
            break;
        }
        sp20[0] = *(u16 *)(s0 + 6);
        sp20[1] = *(u16 *)(s0 + 0xA) - 0x20;
        sp20[2] = *(u16 *)(s0 + 0xE);
        v0 = func_8004787C(*(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF);
        sp28[0] = sp20[0] - (v0 << 5 >> 12);
        sp28[1] = sp20[1];
        v0 = func_80047948(*(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF);
        sp28[2] = sp20[2] - (v0 << 5 >> 12);
        s1 = ((s32 (*)(s32, void *, s32))func_80133784)(1, sp20, (s32)sp28);
        if ((s1 & 0x8000) != 0) {
            v0 = func_8004787C(*(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF);
            *(u16 *)(s0 + 6) = sp28[0] + (v0 << 5 >> 12);
            v0 = func_80047948(*(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF);
            *(u16 *)(s0 + 0xE) = sp28[2] + (v0 << 5 >> 12);
        }
        if (s1 != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012A828(s0, (s32)D_8018E3F4);
            func_8012B14C(s0, (s32)D_80185DA4);
        } else if (*(s32 *)(s0 + 0x1C) != 0) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 1;
            return;
        } else {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012A828(s0, (s32)D_8018E3F4);
            func_8012B14C(s0, (s32)D_80185DA4);
        }
        break;
    case 2:
        if (((((s32 (*)(s32))func_8012CBF4)(s0)) & 0x6000) == 0) {
            break;
        }
        if (func_8017D65C(s0) == 0) {
            func_8012A828(s0, (s32)D_8018E3F4);
            func_8012B14C(s0, (s32)D_80185DA4);
            break;
        }
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        func_8012A828(s0, (s32)D_8018D9F4);
        *(s32 *)(s0 + 0x1C) = 0;
        break;
    case 3:
        if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
            func_8012A828(s0, (s32)D_8018D9F4);
        }
        if (*(s32 *)(s0 + 0x94) == 0 || *(s32 *)(s0 + 0x94) == 0x17) {
            func_8002D4C8(0x70A, 0);
        }
        v0 = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12),
                           func_8012B744((void *)(s0 + 4), (void *)(s0 + 0x88)), 8);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF;
        if (((((s32 (*)(s32))func_8012CBF4)(s0)) & 0x8000) != 0 &&
            (++*(s32 *)(s0 + 0x1C) >= 0x1E)) {
            func_8012A828(s0, (s32)D_8018E3F4);
            func_8012B14C(s0, (s32)D_80185DA4);
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) - 1;
            break;
        }
        s1 = ((s32 (*)(s32, u16 *))func_8012BE98)(s0, (u16 *)(s0 + 0x88));
        mv[0] = 0;
        mv[2] = -(s1 << 5);
        if (mv[2] < (s32)0xFFFE0000) {
            mv[2] = (s32)0xFFFE0000;
        }
        func_8012B1B4(s0, (s32)mv);
        if (s1 < 0x401) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012A828(s0, (s32)((u8 *)&D_8018D8AC));
            func_8012B23C(s0);
        }
        break;
    case 4:
        v0 = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12),
                           func_8012B744((void *)(s0 + 4), (void *)D_80185CAC), 8);
        if (v0 != 0) {
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF;
        } else {
            *(u16 *)(s0 + 2) = 1;
            *(u16 *)(s0 + 0x34) = 0;
        }
        if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
            func_8012A828(s0, (s32)((u8 *)&D_8018D8AC));
        }
        break;
    }
}


#include "common.h"

/* decl_prior: TU-authoritative (law 2) */
extern void func_8012A828(s32 a0, s32 a1);

/* not yet declared in this TU; fleet-modal spellings from decl_prior */
/* binary-unanimous void spelling (9 sibling TUs + the banked
   DEFINE_func_8012CBCC); result read through a cast at the call. */
extern void func_8012CBCC(s32 a0);
extern s32  func_8017D65C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32  func_8012BA10(s32 a0, s32 a1);
extern s32  func_8012BD14(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32  func_8012BDBC(s32 a0, s32 a1);

extern u8 D_8018E3F4[];
extern u8 D_80185D98[];
extern u8 D_8018D9F4[];
extern u8 D_8018E684[];

void func_8017E710(s32 a0) {
    /* register pin: target puts the dispatch value in $s2 and the case-1
       counter in $s1; without pins global_alloc swaps them (§ regalloc-order). */
    s32 s2;
    s2 = *(u16 *)(a0 + 0x34);

    switch (s2) {
    case 0:
        if ((((s32 (*)(s32))func_8012CBCC)(a0) & 0x6000) != 0) {
            if (func_8017D65C(a0) != 0) {
                func_8012A828(a0, (s32)D_8018E3F4);
                func_8012B14C(a0, (s32)D_80185D98);
            } else {
                func_8012A828(a0, (s32)D_8018D9F4);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            }
        }
        break;
    case 1: {
        s32 v0;
        s32 s1;
        s32 mv[4];

        v0 = func_8012BA10(a0, 0x10);
        /* raw pointer-derived loads, not a named local: target reloads
           *(a0+0x20) into a DIFFERENT register per CSE-live interval
           (a0, then v1) because a call intervenes — §193-E/H. */
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + v0;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        func_8012CBCC(a0);

        s1 = func_8012BD14(a0);
        mv[2] = -(s1 << 5);
        mv[0] = 0;
        if (mv[2] < (s32)0xFFFE0000) {
            mv[2] = (s32)0xFFFE0000;
        }
        func_8012B1B4(a0, (s32)mv);

        if (0x10000 < s1) {
            return;
        }
        if (func_8012BDBC(a0, 0x200) != s2) {
            return;
        }
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        func_8012A828(a0, (s32)D_8018E684);
        break;
    }
    }
}


#include "common.h"

/* decl_prior: TU-authoritative (law 2) -- copied verbatim from the block that
   precedes func_8017E1D0 / func_8017E710 in this same TU. */
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017D65C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

extern u8 D_8018D9F4[];
extern s32 D_8018D8AC;
extern u8 D_80185DA4[];
extern s16 D_80185CAC[];

void func_8017E880(s32 param_1) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 v0;
    s32 v1;
    s16 sp10[4];
    s16 sp18[4];
    s16 sp20[4];
    s16 sp28[4];

    s1 = param_1;
    if (*(s32 *)(s1 + 8) > 0) {
        *(s16 *)(s1 + 6) = -0x103;
        *(s16 *)(s1 + 0xA) = -0x182;
        *(s16 *)(s1 + 0xE) = 0xE8;
        *(s16 *)(s1 + 2) = 6;
        *(u16 *)(s1 + 0x34) = 0;
        *(u16 *)(s1 + 0x10A) = 0;
        func_8012B23C(s1);
    }

    switch (*(u16 *)(s1 + 0x34)) {
    case 0:
        if ((*(u16 *)(s1 + 0x72) & 0x4000) != 0) {
            func_8012A828(s1, (s32)D_8018D9F4);
        }
        if (*(s32 *)(s1 + 0x94) == 0 || *(s32 *)(s1 + 0x94) == 0x17) {
            func_8002D4C8(0x70A, 0);
        }
        if (((s32 (*)(s32))func_8012CBF4)(s1) != 0) {
            if (++*(s32 *)(s1 + 0x1C) >= 0x1E) {
                *(s32 *)(s1 + 0x1C) = 0;
                if (func_8017D65C(s1) == 0) {
                    *(s32 *)(s1 + 0x14) = 0xFFE80000;
                }
            }
        }
        func_8012B1B4(s1, (s32)D_80185DA4);
        if (*(s16 *)(s1 + 0xE) < -0xDF) {
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = 0x800;
            v0 = func_8012B744((void *)(s1 + 4), (void *)D_80185CAC);
            v1 = (0x800 - v0) & 0xFFF;
            if (v1 < 0x800) {
                *(s16 *)(s1 + 0xFE) = 0x400;
            } else {
                *(s16 *)(s1 + 0xFE) = -0x400;
            }
        } else {
            v0 = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12),
                               func_8012B744((void *)(s1 + 4), (void *)(s1 + 0x88)), 4);
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
            s2 = func_8012B744((void *)(s1 + 4), (void *)D_80185CAC);
            v1 = ((s32 (*)(s32, u16 *))func_8012BE98)(s1, (u16 *)D_80185CAC);
            if (v1 <= 0x1E400) {
                s2 = s2 + 0x800;
                s2 = s2 & 0xFFF;
                v1 = 0x1E400 - v1;
            } else {
                v1 = v1 - 0x1E400;
            }
            if (v1 < 0x101) {
                *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
                v0 = func_8012B744((void *)(s1 + 4), (void *)D_80185CAC);
                v1 = (*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) - v0) & 0xFFF;
                if (v1 < 0x800) {
                    *(s16 *)(s1 + 0xFE) = 0x400;
                } else {
                    *(s16 *)(s1 + 0xFE) = -0x400;
                }
            }
            v0 = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12), s2, 4);
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        }
        if (((s32 (*)(s32, u16 *))func_8012BE98)(s1, (u16 *)(s1 + 0x88)) < 0x2401) {
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 2;
            *(s32 *)(s1 + 0x10) = 0;
            *(s32 *)(s1 + 0x18) = 0;
        }
        break;
    case 1:
        if ((*(u16 *)(s1 + 0x72) & 0x4000) != 0) {
            func_8012A828(s1, (s32)D_8018D9F4);
        }
        if (*(s32 *)(s1 + 0x94) == 0 || *(s32 *)(s1 + 0x94) == 0x17) {
            func_8002D4C8(0x70A, 0);
        }
        if (((s32 (*)(s32))func_8012CBF4)(s1) != 0) {
            if (++*(s32 *)(s1 + 0x1C) >= 0x1E) {
                *(s32 *)(s1 + 0x1C) = 0;
                if (func_8017D65C(s1) == 0) {
                    *(s32 *)(s1 + 0x14) = 0xFFE80000;
                }
            }
        }
        func_8012B1B4(s1, (s32)D_80185DA4);
        if (*(s16 *)(s1 + 0xE) < -0xDF) {
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = 0x800;
            v0 = func_8012B744((void *)(s1 + 4), (void *)D_80185CAC);
            v1 = (0x800 - v0) & 0xFFF;
            if (v1 < 0x800) {
                *(s16 *)(s1 + 0xFE) = 0x400;
            } else {
                *(s16 *)(s1 + 0xFE) = -0x400;
            }
        } else {
            v0 = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12),
                               func_8012B744((void *)(s1 + 4), (void *)(s1 + 0x88)), 4);
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
            s2 = func_8012B744((void *)(s1 + 4), (void *)D_80185CAC) +
                 *(s16 *)(s1 + 0xFE);
            v0 = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12), s2 & 0xFFF, 4);
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + v0;
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        }
        if (((s32 (*)(s32, u16 *))func_8012BE98)(s1, (u16 *)(s1 + 0x88)) < 0x2401) {
            *(u16 *)(s1 + 0x34) = 2;
            *(s32 *)(s1 + 0x10) = 0;
            *(s32 *)(s1 + 0x18) = 0;
        }
        break;
    case 2:
        func_8012CBF4(s1);
        if ((*(u16 *)(s1 + 0x72) & 0x4000) != 0) {
            func_8012A828(s1, (s32)((u8 *)&D_8018D8AC));
        }
        s2 = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12),
                           func_8012B744((void *)(s1 + 4), (void *)D_80185CAC), 8);
        if (s2 != 0) {
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + s2;
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        } else {
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
            func_8012B1B4(s1, (s32)D_80185DA4);
            func_8012A828(s1, (s32)D_8018D9F4);
        }
        break;
    case 3:
        if ((*(u16 *)(s1 + 0x72) & 0x4000) != 0) {
            func_8012B1B4(s1, (s32)D_80185DA4);
            func_8012A828(s1, (s32)D_8018D9F4);
        }
        if (*(s32 *)(s1 + 0x94) == 0 || *(s32 *)(s1 + 0x94) == 0x17) {
            func_8002D4C8(0x70A, 0);
        }
        func_8012CBF4(s1);
        sp10[0] = *(u16 *)(s1 + 6);
        sp10[1] = *(u16 *)(s1 + 0xA);
        sp10[2] = *(u16 *)(s1 + 0xE);
        v0 = func_8004787C(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
        sp18[0] = *(u16 *)(s1 + 6) - (v0 >> 6);
        sp18[1] = *(u16 *)(s1 + 0xA);
        v0 = func_80047948(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
        sp18[2] = *(u16 *)(s1 + 0xE) - (v0 >> 6);
        if ((((s32 (*)(s32, void *, s32))func_80133784)(1, sp10, (s32)sp18) & 0x8000) != 0) {
            goto hit;
        }
        {
            sp20[0] = *(u16 *)(s1 + 6);
            sp20[1] = *(u16 *)(s1 + 0xA) - 0x20;
            sp20[2] = *(u16 *)(s1 + 0xE);
            v0 = func_8004787C(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
            sp28[0] = sp20[0] - (v0 << 5 >> 12);
            sp28[1] = sp20[1];
            v0 = func_80047948(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
            sp28[2] = sp20[2] - (v0 << 5 >> 12);
            s0 = ((s32 (*)(s32, void *, s32))func_80133784)(1, sp20, (s32)sp28) & 0x8000;
            if (s0 != 0) {
                v0 = func_8004787C(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
                *(u16 *)(s1 + 6) = sp28[0] + (v0 << 5 >> 12);
                v0 = func_80047948(*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF);
                *(u16 *)(s1 + 0xE) = sp28[2] + (v0 << 5 >> 12);
                /* cookbook §353: launder the VALUE so cse cannot fold the
                   surviving dead re-test that thread_jumps leaves behind. */
                __asm__("" : "=r"(s0) : "0"(s0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
            }
        }
        if (s0 != 0) {
        hit:
            *(u16 *)(s1 + 2) = 1;
            *(u16 *)(s1 + 0x34) = 0;
            *(u16 *)(s1 + 0x10A) = 0;
            func_8012B23C(s1);
        }
        break;
    }
}


#include "common.h"

extern void func_8012CBCC(s32 a0);
extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 D_80185CC0[];
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

void func_8017EFFC(s32 param_1) {
    s32 ptr;
    s32 i;
    s32 v0;
    s32 v1;

    s32 counter = *(s32 *)(param_1 + 0x1c) + 1;
    *(s32 *)(param_1 + 0x1c) = counter;
    if (counter < 0x5B) {
        func_8012CBCC(param_1);
        ptr = func_80143C74(param_1, 0);
        if (ptr != 0) {
            *(s16 *)(ptr + 0x16) = -0xC;
            *(s16 *)(ptr + 0x12) = (rand() & 7) - 4;
            *(s16 *)(ptr + 0x1A) = (rand() & 7) - 4;
            v0 = rand() & 0x1F;
            v1 = *(u16 *)(ptr + 0x6);
            v1 = v1 + -0x10;
            v1 = v1 + v0;
            *(s16 *)(ptr + 0x6) = v1;
            v0 = rand() & 0x1F;
            v1 = *(u16 *)(ptr + 0xE);
            v1 = v1 + -0x10;
            v1 = v1 + v0;
            *(s16 *)(ptr + 0xE) = v1;
            v0 = rand() & 0x1F;
            v1 = *(u16 *)(ptr + 0xA);
            v1 = v1 + -0x50;
            v1 = v1 - v0;
            *(s16 *)(ptr + 0xA) = v1;
        }
    } else {
        *(s16 *)(param_1 + 0x98) = 0;
    }

    if (*(s32 *)(param_1 + 0x1c) >= 0x78) {
        func_8002D4C8(0x7C0, 0);
        for (i = 0; i < 0xF; i++) {
            v0 = func_8012C588(0x207, param_1);
            if (v0 != 0) {
                func_8001C214(*(s32 *)(param_1 + 0x20), D_80185CC0[i % 3]);
            }
        }
        func_8012C218((void *)param_1);
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);

void func_8017F174(s32 param_1) {
    extern void (*D_80185DCC[])(s32);
    extern u8 D_8018E84C[];

    if (*(s16 *)(param_1 + 0x10A) == 5) {
        *(s16 *)(param_1 + 2) = 8;
        *(s16 *)(param_1 + 0x10A) = 0;
        func_8012A828(param_1, (s32)D_8018E84C);
        func_8012B23C(param_1);
    }
    D_80185DCC[*(u16 *)(param_1 + 2)](param_1);
    if (*(u16 *)(param_1 + 0) != 0 && *(s16 *)(param_1 + 0xA) > 0) {
        *(s16 *)(param_1 + 6) = -0x103;
        *(s16 *)(param_1 + 0xA) = -0x182;
        *(s16 *)(param_1 + 0xE) = 0xE8;
        *(s16 *)(param_1 + 2) = 6;
        *(s16 *)(param_1 + 0x34) = 0;
        *(s16 *)(param_1 + 0x10A) = 0;
        func_8012B23C(param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);

extern u8 D_80185E00[];
extern u8 D_80185E18[];
extern u8 D_80185E30[];

extern s16 D_80126CB4;
extern s16 D_80126CB8;

void func_8017F234(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001CA1C(v0, (s32)D_80185E00);
        func_8012A828(param_1, (s32)D_80185E18);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
        func_8012B23C(param_1);
        func_8012B2CC(param_1);
        func_8012B14C(param_1, (s32)D_80185E30);
        *(s16 *)(param_1 + 2) = 1;
        *(s16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0xA0;
        *(s16 *)(param_1 + 6) =
            *(u16 *)(param_1 + 6) -
            (func_8004787C(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 7);
        *(s16 *)(param_1 + 0xE) =
            *(u16 *)(param_1 + 0xE) -
            (func_80047948(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 7);
        *(s16 *)(param_1 + 0x88) = *(u16 *)(param_1 + 6);
        *(s16 *)(param_1 + 0x8A) = *(u16 *)(param_1 + 0xA);
        *(s16 *)(param_1 + 0x8C) = *(u16 *)(param_1 + 0xE);
        {
            s16 k = -0x82;
            *(s16 *)(param_1 + 0xFC) = D_80126CB4 - *(u16 *)(param_1 + 0x88);
            *(s16 *)(param_1 + 0xFE) = k - *(u16 *)(param_1 + 0x8A);
        }
        *(s16 *)(param_1 + 0x100) = D_80126CB8 - *(u16 *)(param_1 + 0x8C);
    }
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80143B6C(s32 a0, s32 a1);

void func_8017F374(s32 arg0) {
    s32 v0;
    s16 buf[8];

    *(volatile u16 *)(arg0 + 0x102) = *(u16 *)(arg0 + 0x102) + 1;

    *(u16 *)(arg0 + 0x6) = *(u16 *)(arg0 + 0x88) +
        ((*(s16 *)(arg0 + 0xFC) * *(s16 *)(arg0 + 0x102)) >> 5);

    *(u16 *)(arg0 + 0x104) = *(u16 *)(arg0 + 0x104) + 0x40;

    *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x8A) +
        ((*(s16 *)(arg0 + 0xFE) * *(s16 *)(arg0 + 0x102)) >> 5);

    v0 = func_8004787C(*(s16 *)(arg0 + 0x104));

    *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0xA) - (v0 >> 5);

    *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x8C) +
        ((*(s16 *)(arg0 + 0x100) * *(s16 *)(arg0 + 0x102)) >> 5);

    buf[0] = *(u16 *)(arg0 + 0x3A);
    buf[1] = *(u16 *)(arg0 + 0x3E);
    buf[2] = *(u16 *)(arg0 + 0x42);
    buf[4] = *(u16 *)(arg0 + 0x6);
    buf[5] = *(u16 *)(arg0 + 0xA);
    buf[6] = *(u16 *)(arg0 + 0xE);

    if (*(s16 *)(arg0 + 0x102) >= 0x20 ||
        func_80133784(1, &buf[0], (s32)&buf[4]) != 0) {
        *(s16 *)(arg0 + 0x2) = 2;
        *(s32 *)(arg0 + 0x1C) = 0x3C;
        *(s32 *)(arg0 + 0x94) = *(s32 *)(arg0 + 0x94) + 1;
    }

    func_80143B6C(arg0, 0);
}


extern void (*D_80185E3C[])(void);
extern u16 D_80126B96;
extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);

void func_8017F4C8(s32 *a0) {
    D_80185E3C[*(u16 *)((s32)a0 + 0x2)]();

    if (*(u16 *)a0 == 0) {
        return;
    }

    *(u16 *)((s32)a0 + 0xA) -= 0x40;

    if (func_8012D624(a0, ((s16)(*(u16 *)((*(s32 *)((s32)a0 + 0x20)) + 0x18))) >> 8, 0xA) == 1) {
        D_80126B96 = 0xE;
        func_8012C218(a0);
    } else {
        *(u16 *)((s32)a0 + 0xA) += 0x40;
    }
}


#include "common.h"

/* decl_prior (card): tu spellings adopted verbatim where present, fleet-modal
   spelling adopted where the TU is silent (func_8012B23C: 1674 hits for
   ('void', ('s32',)) vs 165/42 rivals). D_801824B0 reuses the exact spelling
   and &(*(s32*)&D_801824B0) idiom already used for this symbol by the TU's
   neighbour func_80181C18 (same overlay struct field). */
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 rand(void);
extern s32 D_80185E48;
extern M2C_UNK D_801824B0;

void func_8017F578(s32 param_1) {
    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_80185E48) == 0) {
        return;
    }
    *(u8 *)(param_1 + 0xC0) = 1;
    ((void (*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_801824B0));
    *(u16 *)(param_1 + 0x2) = 1;

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = (rand() & 0x3FF) + 0x400;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = (rand() & 0x3FF) + 0x400;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1C) = (rand() & 0x3FF) + 0x400;
    func_8012B23C(param_1);

    *(s16 *)(param_1 + 0xFC) = (rand() & 0xFF) - 0x80;
    *(s16 *)(param_1 + 0xFE) = (rand() & 0xFF) - 0x80;
    *(s16 *)(param_1 + 0x100) = (rand() & 0xFF) - 0x80;
    *(s16 *)(param_1 + 0x12) = (rand() & 0xF) - 0x8;
    *(s16 *)(param_1 + 0x16) = -(rand() & 0x1F);
    *(s16 *)(param_1 + 0x1A) = (rand() & 0xF) - 0x8;

    *(s16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x50;
    *(s32 *)(param_1 + 0x1C) = 0x3C;
}



extern void (*D_80185E7C[])(void);

void func_8017F69C(void *a0) {
    D_80185E7C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801AAF54;
extern s32 func_8004787C(s32 a0);

void func_8017F6D8(void *a0) {
    void *s0 = a0;
    u16 state;

    state = *(u16 *)((s32)s0 + 0x34);
    switch (state) {
    case 0:
        ((void (*)(void *, void *))func_8012A828)(s0, &D_801AAF54);
        state = *(u16 *)((s32)s0 + 0x34);
        *(u16 *)((s32)s0 + 0x98) = 0;
        state = state + 1;
        *(u16 *)((s32)s0 + 0x34) = state;
        break;

    case 1:
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) - 0x40;

        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) & 0xFFF;

        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x12) + 0x40;

        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x12) & 0xFFF;

        *(s32 *)((s32)s0 + 0x14) = *(s32 *)((s32)s0 + 0x14) + (s32)0xFFFD8000;

        if (*(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) == 0xC00) {
            state = *(u16 *)((s32)s0 + 0x34);
            state = state + 1;
            *(u16 *)((s32)s0 + 0x34) = state;
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x2C) | 0x10;
        }
        break;

    case 2: {
        register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

        v0 = func_8004787C(*(s16 *)((s32)s0 + 0xFE));
        *(u16 *)((s32)s0 + 0xFE) =
            (*(u16 *)((s32)s0 + 0xFE) + 0x40) & 0xFFF;

        if (v0 > 0) {
            v0 = (v0 >> 3) + 0x1000;
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1C) = v0;
        } else {
            v0 = 0x1000;
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1C) = v0;
        }
        break;
    }
    }
}



extern void (*D_80185ED0[])(void);

void func_8017F840(void *a0) {
    D_80185ED0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8017D65C(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern u8 D_8018D9F4[];
extern s16 D_80185CAC[];

void func_8017F87C(s32 a0) {
    s32 sm;

    *(u16 *)(a0 + 0x5C) = 0xAA00;
    *(u16 *)(a0 + 0x34) = 0;
    func_8012A828(a0, (s32)D_8018D9F4);
    func_8012B23C(a0);
    if (func_8017D65C(a0) != 0) {
        if (*(s16 *)(a0 + 0x10A) != 5) {
            *(s16 *)(a0 + 2) = 6;
            *(u16 *)(a0 + 0x10A) = 0;
            if (*(s16 *)(a0 + 0xA) < -0x90) {
                sm = func_8012B744((void *)(a0 + 4), (void *)D_80185CAC);
                sm += 0x800;
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = sm & 0xFFF;
                *(s16 *)(a0 + 0x16) = -8;
            }
        }
    }
}


void func_8017F91C(s32 param_1) {
    *(u8 *)(param_1 + 0xC1) = 0;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
    *(u16 *)(param_1 + 0x5C) = 0xAA00;
    *(s16 *)(param_1 + 0x6) = -0x103;
    *(s16 *)(param_1 + 0xA) = -0x182;
    *(s16 *)(param_1 + 0xE) = 0xE8;
    *(s16 *)(param_1 + 0x5E) = 0;
    *(s16 *)(param_1 + 0x2) = 6;
    *(s16 *)(param_1 + 0x34) = 0;
    *(s16 *)(param_1 + 0x10A) = 0;
    func_8012B23C(param_1);
}


extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    void func_8017F978(void *arg0) {
        ((void (*)(void *, int))func_80131E00)(arg0, 0x11);
    }


struct S80131E00;

extern s32 D_801151FC;
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80131B14();
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern unsigned short D_8018DE2C[];

void func_8017F998(s32 param_1) {
    s32 s0;
    s32 v0;
    s32 val;

    s0 = param_1;
    if (D_801151FC == s0) {
        D_801151FC = 0;
    }
    val = *(u8 *)(s0 + 0x5E);
    if (val != 8) {
        if (val < 9) {
            v0 = 5;
        } else if (val == 0x20) {
            goto TARGET1;
        } else {
            v0 = 0x26;
        }
        if (val != v0 && *(u16 *)(s0 + 2) != 2 &&
            (*(s16 *)(s0 + 0x76) >= 0x371 || val == 0x1D)) {
            goto TARGET2;
        }
    }
TARGET1:
    func_80131E00((struct S80131E00 *)s0, 3);
    *(s16 *)(s0 + 0x76) = 0x3E8;
    return;
TARGET2:
    func_80131B14(s0);
    func_8012A828(s0, (s32)D_8018DE2C);
    func_8002D4C8(0xA99, 0);
}


















extern void func_80131E00(struct S80131E00 *a0, s32 a1);
void func_8017FA64(void)
{
  int new_var2;
  void (*new_var)(int, int);
  new_var = (void (*)(int, int)) func_80131E00;
  new_var(new_var2, 0x1);
  new_var2 = 0x80C70000;
}



extern void func_8012CBCC(s32);
extern void func_80131C78(s32 a0);

void func_8017FA84(s32 a0) {
    s32 s0;

    s0 = a0;
    ((void (*)(s32))func_8012CBCC)(a0);
    if (*(u16 *)(s0 + 0x72) & 0x4000) {
        func_80131C78(s0);
    }
}


extern void func_80131B14();
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void (*D_8018DF04[])(void);
extern u16 D_80185CB4;

void func_8017FAC8(s32 param_1) {
    s32 s0;

    s0 = param_1;
    func_80131B14();
    *(u16 *)(s0 + 0x5C) = 0;
    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    func_8012A828(s0, (s32)D_8018DF04);
    func_8012B14C(s0, (s32)&D_80185CB4);
    func_8002D4C8(0x714, 0);
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_80143970(s32 a0);
extern s32 rand(void);
extern u8 D_80185CDC;
extern s32 D_8018D8AC;
extern s32 D_80185D10;
extern s32 D_801AECD4;

void func_8017FB28(s32 param_1) {
    D_801AECD4 = 0;
    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_80185CDC) == 0) {
        return;
    }
    *(s16 *)(param_1 + 0x76) = 1000;
    *(u8 *)(param_1 + 0xC0) = 1;
    *(s32 *)(param_1 + 0xB4) = 0x40003;
    *(u32 *)(param_1 + 0xC4) |= 2;
    func_80143970(param_1);
    ((void (*)(s32, void *))func_8012A828)(param_1, &D_8018D8AC);
    *(s16 *)(param_1 + 0x2) = 10;
    *(u32 *)(param_1 + 0x1C) = rand() & 7;
    func_8012B23C(param_1);
    *(s32 *)(param_1 + 0xBC) = (s32)&D_80185D10;
    *(u16 *)(param_1 + 0xFC) = rand() & 0x3FFF;
}


extern s32 func_8012C588(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_8018D8AC;

void func_8017FBD8(s32 a0) {
    if (*(s32 *)(a0 + 0x94) == 0x12) {
        ((void (*)(s32, s32))func_8012C588)(0x203, a0);
        func_8002D4C8(0x7BF, 0);
    }

    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        func_8012A828(a0, (s32)&D_8018D8AC);
        *(s16 *)(a0 + 0x2) = 1;
        *(s16 *)(a0 + 0x10A) = 0;
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_8018E8EC[];

void func_8017FC50(s32 param_1) {
    if ((*(u16 *)(param_1 + 0x72) & 0x4000) != 0) {
        func_8012A828(param_1, (s32)D_8018E8EC);
        *(s16 *)(param_1 + 2) = 9;
        *(s32 *)(param_1 + 0x1C) = 0;
        func_8002D4C8(0x776, 0);
    }
    func_8012CBCC(param_1);
}


extern void func_8012A828(s32 a0, s32 a1);
extern u8 D_8018E3F4[];

void func_8017FCB8(s32 a0)
{
    if (*(s32 *)(a0 + 0x1c) != 0) {
        (*(s32 *)(a0 + 0x1c))--;
    } else {
        *(s16 *)(a0 + 2) = 0xB;
        func_8012A828(a0, (s32)D_8018E3F4);
        *(s32 *)(a0 + 0x94) = 0x2C;
    }
}


/* func_8017FD14 -- ov_SC03_121, TU ov_SC03_121_jr_8017E1D0.c.  MATCH (29 ins).
 * CBCC-guarded trigger: sound(0x709); ++u16 counter at a0+2; ++global
 * D_801AECD4; when it reaches 3, one-shot func_8013C9C4(&D_801828E0).
 * Decls verbatim from this TU (lines 57 / 1303 / 2706); D_801AECD4 typed by
 * access width (lw+sw -> s32); D_801828E0 address-only -> u8[]. */

extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);

extern s32 D_801AECD4;
extern u8 D_801828E0[];

void func_8017FD14(s32 a0)
{
    s32 v0;
    s32 v1;

    if (((s32 (*)(s32))func_8012CBCC)(a0) != 0) {
        func_8002D4C8(0x709, 0);
        v0 = *(u16 *)(a0 + 2);
        v1 = D_801AECD4 + 1;
        *(u16 *)(a0 + 2) = v0 + 1;
        D_801AECD4 = v1;
        if (v1 == 3) {
            func_8013C9C4(D_801828E0);
        }
    }
}


extern void func_8012A828(s32, s32);
    extern s32 D_8018D8AC;
    void func_8017FD88(u8 *a0) {
        if (*(u16 *)((s32)a0 + 0x72) & 0x4000) {
            ((void (*)(void *, s32))func_8012A828)(a0, (s32)&D_8018D8AC);
        }
    }


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 rand(void);

void func_8017FDC4(s32 param_1)
{
    s32 ptr;
    s32 counter;

    counter = *(s32 *)(param_1 + 0x1c) - 1;
    *(s32 *)(param_1 + 0x1c) = counter;
    if (counter < 0x10) {
        if (counter == 0) {
            func_8012C218((void *)param_1);
        } else {
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) ^= 0x80000000;
        }
    }
    ptr = func_80143C74(param_1, 0);
    if (ptr != 0) {
        *(s16 *)(ptr + 0x16) = -8;
        *(s16 *)(ptr + 0x12) = (rand() & 7) - 4;
        *(s16 *)(ptr + 0x1A) = (rand() & 7) - 4;
    }
}


#include "common.h"

extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

void func_8017FE6C(s32 a0)
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


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 D_80185E94;
extern s32 D_801AB1EC;

void func_8017FF8C(s32 param_1)
{
    if (func_8012C354(param_1, (s32)&D_80185E94) == 0) {
        return;
    }
    func_8012A828(param_1, (s32)&D_801AB1EC);
    *(u8 *)(param_1 + 0xC0) = 1;
    *(s32 *)(param_1 + 0xB4) = -1;
    func_80143970(param_1);
    *(u16 *)(param_1 + 0xFC) = 0x20;
    *(u16 *)(param_1 + 2) += 1;
    if (*(s16 *)(param_1 + 0x70) == 1) {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = 0x400;
        *(s16 *)(param_1 + 0x12) = -4;
    } else {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = 0xC00;
        *(s16 *)(param_1 + 0x12) = 4;
    }
}



extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801AAF54;

void func_80180038(void *a0) {
    *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x6) + *(u16 *)((s32)a0 + 0x12);
    if (--*(s16 *)((s32)a0 + 0xFC) == 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0;
        func_8012A828((s32)a0, (s32)&D_801AAF54);
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
}


void func_801800A8(void) {
}

#include "common.h"

extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 func_80181BE8(s32 a0, s32 a1);
extern void func_8002D4C8(s32 arg0, s32 arg1);

extern s32 D_801AB144;
extern s32 D_80185C64;
extern s32 D_80185EC8;
extern s32 D_801AAF54;

void func_801800B0(void *a0) {
    u16 state;

    state = *(u16 *)((s32)a0 + 0x34);
    switch (state) {
    case 0:
        func_8012A828((s32)a0, (s32)&D_801AB144);
        *(s16 *)((s32)a0 + 0xFC) = 8;
        *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
        break;
    case 1:
        if (*(s16 *)((s32)a0 + 0xFC) != 0) {
            *(s16 *)((s32)a0 + 0xFC) -= 1;
            *(u16 *)((s32)a0 + 0xE) -= 3;
        } else {
            *(u16 *)((s32)a0 + 0x34) = state + 1;
            func_8012A828((s32)a0, (s32)&D_80185C64);
        }
        /* fallthrough */
    case 2:
        if (*(u16 *)((s32)a0 + 0x72) & 0x4000) {
            func_80181BE8((s32)a0, (s32)&D_80185EC8);
            func_8002D4C8(0x717, 0);
        }
        break;
    case 3:
        func_8012A828((s32)a0, (s32)&D_801AAF54);
        *(u16 *)((s32)a0 + 0x34) = 0;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
        break;
    }
}



extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801AB6F4;

void func_801801DC(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801AB6F4);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
}



extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 D_801AAFFC;

void func_80180214(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801AAFFC);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
}


s32 func_8018024C(void) {
        return 0x40;
    }


extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern int func_8001AAA0(void);
extern void func_8012B2CC(s32 a0);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_800291A0(s32, s32);

extern u16 D_8019B928;
extern u16 D_8019B92C;
extern u16 D_8019B92E;
extern s32 D_801AECD8[];
extern s32 D_801AECEC;
extern s32 D_801AECF0;

void func_80180254(s32 param_1) {
    s32 *p;
    s32 off;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 i;
    s32 q;
    u16 t;
    s32 e;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        break;

    case 1:
        e = D_801AECEC;
        *(u16 *)(e + 2) += 1;
        *(u16 *)(D_801AECF0 + 2) += 1;
        *(u16 *)(param_1 + 0x34) = 0;
        break;

    case 2:
        ((void (*)(s32))func_8001AAA0)(0x41);
        i = 0;
        p = D_801AECD8;
        off = 0;
        while (i < 5) {
            v0 = func_8012C588(0x1C5, param_1);
            *p = v0;
            t = *(u16 *)((s32)&D_8019B928 + off);
            *(u16 *)(v0 + 0x88) = t;
            *(u16 *)(v0 + 6) = t;
            *(s16 *)(*p + 0xA) = -0x400;
            e = *p;
            v0 = *(u16 *)((s32)&D_8019B92C + off);
            *(u16 *)(e + 0x8C) = v0;
            *(u16 *)(e + 0xE) = v0;
            v0 = *p;
            i++;
            *(u16 *)(*(s32 *)(v0 + 0x20) + 0x12) =
                *(u16 *)((s32)&D_8019B92E + off);
            off += 8;
            *(s16 *)(*p + 0x8A) = -0x92;
            p++;
        }
        *(u16 *)(param_1 + 0x34) = 0;
        break;

    case 3:
        *(u16 *)(param_1 + 0x34) = 5;
        *(s16 *)(param_1 + 0x16) = -0x14;
        func_8002D4C8(0x716, 0);
        break;

    case 4:
        *(u16 *)(D_801AECEC + 0x34) += 1;
        *(u16 *)(D_801AECF0 + 0x34) += 1;
        *(u16 *)(param_1 + 0x34) = 0;
        break;

    case 5:
        func_8012CBCC(param_1);
        i = 1;
        if (*(s32 *)(param_1 + 0x14) > 0) {
            do {
                func_8012C658(0x21D, 1, param_1);
                i++;
            } while (i < 0x20);
            q = *(s32 *)(param_1 + 0x20);
            *(u16 *)(param_1 + 0x34) = 0;
            *(u32 *)(q + 4) |= 0x80000000;
            *(s16 *)(param_1 + 0xA) = -0x10B;
            *(u16 *)(param_1 + 0x6) = 0;
            *(u16 *)(param_1 + 0xE) = 0x12F;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = 0;
            func_8012B2CC(param_1);
        } else {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x155;
            func_8012C658(0x21D, 0, param_1);
        }
        break;

    case 6:
        func_8012C658(0x220, *(s16 *)(param_1 + 0xFE), param_1);
        *(u16 *)(param_1 + 0xFE) = *(u16 *)(param_1 + 0xFE) + 1;
        if ((s16)*(u16 *)(param_1 + 0xFE) < 5) {
            break;
        }
        *(u16 *)(param_1 + 0x34) = 0;
        break;

    case 7:
        func_8012C658(0x220, *(s16 *)(param_1 + 0xFE), param_1);
        *(u16 *)(param_1 + 0xFE) = *(u16 *)(param_1 + 0xFE) + 1;
        if ((s16)*(u16 *)(param_1 + 0xFE) < 0xA) {
            break;
        }
        *(u16 *)(param_1 + 0x34) = 0;
        break;
    }

    if (((s32 (*)(s32))func_80178970)(param_1) != 0) {
        ((void (*)(s32))func_80178D18)(param_1);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        *(u16 *)(param_1 + 0x34) = 0;
        func_800291A0(0xDD, 1);
        for (i = 0; i < 5; i++) {
            *(u16 *)(D_801AECD8[i] + 2) = 1;
        }
    }
}


#include "common.h"

/* ---- decls copied verbatim from the destination TU (wave law 2) ---------- */
extern u8 D_80078E78[];                                   /* TU line 392  */
extern s32 D_801151FC;                                    /* TU line 738  */
extern s32 D_80126B58;                                    /* TU line 55   */
extern s32 rand(void);                                    /* TU line 957  */
extern s32 func_801726AC(s32 *a0);                        /* TU line 2225 */
extern int func_80178970(void);                           /* TU line 2538 */
extern s32 func_80178B18(s32 param_1, s32 param_2);       /* TU line 2539 */
extern void func_80178D18(void);                          /* TU line 2546 */
extern void func_800291A0(s32, s32);                      /* TU line 62   */

void func_80180568(s32 a0) {
    /* [T51] scoped in: these three are NEW to this TU, so they are declared in
       function scope (the TU's own convention, cf. func_80181BE8/func_80181C18)
       to avoid constraining every LATER function in the file. */
    extern s32 D_801AECD8[];   /* 5 entity pointers, stride 4 (D_801AECEC == [5]) */
    extern s32 D_801AECEC;     /* single entity pointer */
    extern s16 D_8019BB90;     /* param block passed to func_80178B18 */

    u8 *p = D_80078E78;   /* $s1 base, hoisted (house style, TU/ov_SC03_099) */
    s16 count0;
    s16 count1;
    s16 n;
    s32 i0, i1, i2, i3;
    s32 d;
    s32 e;
    s32 r;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        n = *(s16 *)(a0 + 0xFC);
        if (n != 0) {
            *(s16 *)(a0 + 0xFC) = n - 1;
        } else {
            count0 = 0;
            for (i0 = 0; i0 < 5; i0++) {
                e = D_801AECD8[i0];
                if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                    count0++;
                }
            }
            if (count0 == 0) {
                if (*(s32 *)(a0 + 0x1C) != 0) {
                    *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
                } else {
                    r = rand() % 5;
                    e = D_801AECD8[r];
                    if (*(u16 *)(e + 2) == 1) {
                        *(s16 *)(e + 0x10A) = 1;
                        d = 0xB4 - *(s16 *)(p + 0x1A);
                        *(s32 *)(a0 + 0x1C) = d;
                        if (d <= 0) {
                            *(s32 *)(a0 + 0x1C) = 1;
                        }
                    }
                }
            }
        }
        if (p[0x39] >= 3 && func_801726AC(&D_80126B58) == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            for (i1 = 0; i1 < 5; i1++) {
                *(s16 *)(D_801AECD8[i1] + 0x10A) = 2;
            }
        }
        break;

    case 1:
        count1 = 0;
        for (i2 = 0; i2 < 5; i2++) {
            e = D_801AECD8[i2];
            if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                count1++;
            }
        }
        if (count1 == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            func_80178B18(a0, (s32)&D_8019BB90);
        } else if (*(s16 *)(p + 0x1A) >= 0xD2) {
            *(u16 *)(a0 + 2) += 1;
            func_800291A0(0xDD, 2);
            *(s16 *)(a0 + 0x34) = 0;
            *(s16 *)(D_801AECEC + 2) = 5;
        }
        break;

    case 2:
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            *(u16 *)(a0 + 2) += 1;
            func_800291A0(0xDD, 2);
            *(s16 *)(a0 + 0x34) = 0;
            *(s16 *)(D_801AECEC + 2) = 5;
        }
        break;
    }

    if (D_801151FC != 0) {
        for (i3 = 0; i3 < 5; i3++) {
            *(s16 *)(D_801AECD8[i3] + 0x10A) = 3;
        }
    }
}


void func_80180850(s32 a0) {
    extern u8 D_80078E78[];
    extern s32 D_801151FC;
    extern s32 D_80126B58;
    extern s32 rand(void);
    extern s32 func_801726AC(s32 *a0);
    extern int func_80178970(void);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_80178D18(void);
    extern void func_800291A0(s32, s32);
    extern s32 D_801AECD8[];
    extern s32 D_801AECEC;
    extern s16 D_8019BBB0;

    u8 *p = D_80078E78;
    s16 count0;
    s16 count1;
    s32 i0, i1, i2, i3;
    s32 d;
    s32 e;
    s32 r;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s32 *)(a0 + 0x1C) != 0) {
            *(s32 *)(a0 + 0x1C) -= 1;
        } else {
            count0 = 0;
            for (i0 = 0; i0 < 5; i0++) {
                e = D_801AECD8[i0];
                if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                    count0++;
                }
            }
            if (count0 < 1) {
                r = rand() % 5;
                e = D_801AECD8[r];
                if (*(u16 *)(e + 2) == 1) {
                    *(s16 *)(e + 0x10A) = 1;
                    d = 0x10E - *(s16 *)(p + 0x1A);
                    *(s32 *)(a0 + 0x1C) = d;
                    if (d <= 0) {
                        *(s32 *)(a0 + 0x1C) = 1;
                    }
                }
            }
        }
        if (*(s16 *)(p + 0x1A) >= 0x10E && func_801726AC(&D_80126B58) == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            for (i1 = 0; i1 < 5; i1++) {
                *(s16 *)(D_801AECD8[i1] + 0x10A) = 2;
            }
        }
        break;

    case 1:
        count1 = 0;
        for (i2 = 0; i2 < 5; i2++) {
            e = D_801AECD8[i2];
            if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                count1++;
            }
        }
        if (count1 == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            func_80178B18(a0, (s32)&D_8019BBB0);
        } else if (*(s16 *)(p + 0x1A) >= 0x12C) {
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 2) += 1;
            func_800291A0(0xDD, 3);
            *(s16 *)(D_801AECEC + 2) = 7;
        }
        break;

    case 2:
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 2) += 1;
            func_800291A0(0xDD, 3);
            *(s16 *)(D_801AECEC + 2) = 7;
        }
        break;
    }

    if (D_801151FC != 0) {
        for (i3 = 0; i3 < 5; i3++) {
            *(s16 *)(D_801AECD8[i3] + 0x10A) = 3;
        }
    }
}


extern u8 D_80078E78[];
extern s32 D_801151FC;
extern s32 D_80126B58;
extern s32 rand(void);
extern s32 func_801726AC(s32 *a0);
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_80178D18(void);
extern void func_800291A0(s32, s32);

void func_80180B1C(s32 a0) {
    extern s32 D_801AECD8[];
    extern s32 D_801AECF0;
    extern s16 D_8019BBD0;

    u8 *p = D_80078E78;
    s16 count0;
    s16 count1;
    s32 i0, i1, i2, i3;
    s32 d;
    s32 e;
    s32 r;
    s32 v;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if ((rand() & 0x7F) == 0) {
            r = rand() % 5;
            e = D_801AECD8[r];
            if (*(u16 *)(e + 2) == 1) {
                *(s16 *)(e + 0x10A) = 4;
            }
        }
        if (*(s32 *)(a0 + 0x1C) != 0) {
            *(s32 *)(a0 + 0x1C) -= 1;
        } else {
            count0 = 0;
            for (i0 = 0; i0 < 5; i0++) {
                e = D_801AECD8[i0];
                if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                    count0++;
                }
            }
            if (count0 < 2) {
                r = rand() % 5;
                e = D_801AECD8[r];
                if (*(u16 *)(e + 2) == 1) {
                    *(s16 *)(e + 0x10A) = 1;
                    d = 0x168 - *(s16 *)(p + 0x1A);
                    *(s32 *)(a0 + 0x1C) = d;
                    if (d <= 0) {
                        *(s32 *)(a0 + 0x1C) = 1;
                    }
                }
            }
        }
        if (*(s16 *)(p + 0x1A) >= 0x168 && func_801726AC(&D_80126B58) == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            for (i1 = 0; i1 < 5; i1++) {
                *(s16 *)(D_801AECD8[i1] + 0x10A) = 2;
            }
        }
        break;

    case 1:
        count1 = 0;
        for (i2 = 0; i2 < 5; i2++) {
            e = D_801AECD8[i2];
            if (*(s16 *)(e + 0x10A) != 0 && *(u8 *)(e + 0xC1) != 3) {
                count1++;
            }
        }
        if (count1 == 0) {
            *(u16 *)(a0 + 0x34) += 1;
            func_80178B18(a0, (s32)&D_8019BBD0);
        } else if (*(s16 *)(p + 0x1A) >= 0x186) {
            v = *(u16 *)(a0 + 2);
            v += 1;
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 2) = v;
            func_800291A0(0xDD, 4);
            *(s16 *)(D_801AECF0 + 2) = 5;
        }
        break;

    case 2:
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            v = *(u16 *)(a0 + 2);
            v += 1;
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 2) = v;
            func_800291A0(0xDD, 4);
            *(s16 *)(D_801AECF0 + 2) = 5;
        }
        break;
    }

    if (D_801151FC != 0) {
        for (i3 = 0; i3 < 5; i3++) {
            *(s16 *)(D_801AECD8[i3] + 0x10A) = 3;
        }
    }
}


/* ---- decls copied verbatim from the destination TU (wave law 2) ---------- */
extern u8 D_80078E78[];                                   /* TU line 390  */
extern s32 D_801151FC;                                    /* TU line 735  */
extern s32 D_80126B58;                                    /* TU line 53   */
extern s32 rand(void);                                    /* TU line 954  */
extern void func_800D0C48(s32 a0);                        /* TU line 1466 */
extern s32 func_801726AC(s32 *a0);                        /* TU line 2221 */
extern int func_80178970(void);                           /* TU line 2533 */
extern s32 func_80178B18(s32 param_1, s32 param_2);       /* TU line 2534 */
extern void func_80178D18(void);                          /* TU line 2541 */
extern int func_8001AAA0(void);                           /* TU line 2586 */

void func_80180E64(s32 a0) {
    extern s32 D_801AECD8[];   /* 5 entity pointers, stride 4 */
    extern s32 D_801AECF0;     /* single entity pointer */
    extern s16 D_8019BBF8;     /* param block passed to func_80178B18 */

    u8 *p = D_80078E78;
    s16 c0;
    register s32 f __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    s32 i0;
    s32 i1;
    s32 i2;
    s32 i3;
    s32 r;
    s32 d;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if ((rand() & 0x3F) == 0) {
            r = rand() % 5;
            if (*(u16 *)(D_801AECD8[r] + 2) == 1) {
                *(s16 *)(D_801AECD8[r] + 0x10A) = 4;
            }
        }
        if (*(s32 *)(a0 + 0x1C) != 0) {
            *(s32 *)(a0 + 0x1C) -= 1;
        } else {
            c0 = 0;
            for (i0 = 0; i0 < 5; i0++) {
                if (*(s16 *)(D_801AECD8[i0] + 0x10A) != 0 && *(u8 *)(D_801AECD8[i0] + 0xC1) != 3) {
                    c0++;
                }
            }
            if (c0 < 3) {
                r = rand() % 5;
                if (*(u16 *)(D_801AECD8[r] + 2) == 1) {
                    *(s16 *)(D_801AECD8[r] + 0x10A) = 1;
                    d = 0x1A4 - *(s16 *)(p + 0x1A);
                    *(s32 *)(a0 + 0x1C) = d;
                    if (d < 1) {
                        *(s32 *)(a0 + 0x1C) = 1;
                    }
                }
            }
        }
        if (*(s16 *)(p + 0x1A) > 0x1A2) {
            func_800D0C48(1);
        }
        if (*(s16 *)(p + 0x1A) > 0x1A3 && func_801726AC(&D_80126B58) == 0) {
            *(u16 *)(a0 + 0x34) += 1;
        }
        break;

    case 1:
        f = 0;
        /* §NNN: the zero-byte `"r"(i1)` keepalive adds the 5th reference to the
           loop counter, which lifts its global_alloc priority above the
           strength-reduced pointer giv's -- that is what puts the counter in
           $a0 and the giv in $a1 (without it they swap).  Emits no bytes. */
        for (i1 = 0; i1 < 5; i1++) {
            __asm__ __volatile__("" :: "r"(i1));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
            if (*(u16 *)(D_801AECD8[i1] + 2) == 5) {
                f = 1;
            }
        }
        if (D_801151FC == 0 && f != 1) {
            func_80178B18(a0, (s32)&D_8019BBF8);
            for (i2 = 0; i2 < 5; i2++) {
                *(s16 *)(D_801AECD8[i2] + 0x10A) = 5;
                *(s16 *)(D_801AECD8[i2] + 0x5C) = 0;
                *(u8 *)(D_801AECD8[i2] + 0xC1) = 0;
            }
            *(u16 *)(a0 + 0x34) += 1;
            *(s16 *)(D_801AECF0 + 2) = 6;
            *(s16 *)(a0 + 0x100) = 1;
            ((void (*)(s32))func_8001AAA0)(0x42);
        }
        break;

    case 2:
        D_801151FC = 0;
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 2) += 1;
        }
        break;
    }

    if (D_801151FC != 0) {
        for (i3 = 0; i3 < 5; i3++) {
            *(s16 *)(D_801AECD8[i3] + 0x10A) = 3;
        }
    }
}



extern void (*D_8019BC80[])(void);

void func_801811DC(void *a0) {
    D_8019BC80[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);


void func_80181218(s32 arg0) {

    extern s32 D_8019BCA0;
    extern s32 D_8019BCAC;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)arg0);
        return;
    }

    func_8001CA1C(v0, (s32)&D_8019BCA0);
    ((void (*)(s32, void *))func_8012A828)(arg0, (void *)&D_8019BCAC);

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
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
    *(s32 *)(arg0 + 0x1C) = 0x10;

    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) = 0x1800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) |= 0x10;

    *(u16 *)(arg0 + 0xA) -= 0x30;
}



extern void (*D_8019BCB4[])(void);

void func_801813AC(void *a0) {
    D_8019BCB4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* ------------------------------------------------------------------ *
 * func_801813E8 @ 0x801813E8  (ov_SC03_121, 182 ins)
 *
 * Draws a 2-primitive packet (DR_MODE @+0x00 .. POLY_G4 @+0x0C) for the
 * entity at param_1, projected through the GTE.
 *
 * entity layout used here:
 *   +0x06 u16  vx    +0x0A u16 vy    +0x0E u16 vz
 *   +0x1C s32  colour/intensity
 * ------------------------------------------------------------------ */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void *func_80010A08(s32 size);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern s32 func_8005A600(s32 p, s32 dfe, s32 dtd, s32 tpage, s32 tw);
extern s32 AddPrim(s32 ot, void *p);

extern short D_800B9A02;
extern u8 D_800AF648;
/* OT-block table @ D_800A651C, 0x14 stride; word 0 of each row is the OT base.
   Declared through an __asm__ alias in the RAWEST form (s32 [] + a *5 index) so it can
   never collide with the TU's eventual spelling — the fleet is split 1198 x scalar
   `extern s32 D_800A651C;` vs 142 x `extern OtBlk D_800A651C[];`, and this TU declares
   neither.  Fleet precedent for the alias form: ov_SC03_006 `aD800A651C_80144090`.
   If the reconciler prefers the struct form, `OtBlk D_800A651C[]` + `[idx].a` is
   byte-identical (OtBlk = { s32 a; s32 b[4]; }, src/shared/engine_types.h:525). */
extern s32 otTbl_801813E8[] __asm__("D_800A651C");

void func_801813E8(s32 param_1) {
    void *prim;
    register u8 *poly __asm__("$18");   /* $s2 — global_alloc keeps it callee-saved; without the pin local_alloc coalesces it into $a1 */  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
    s32 otz;
    s32 ot;
    struct {
        s16 v10[4];   /* +0x18 */
        u16 sxy0[2];  /* +0x20 : saved projection of the un-offset point */
        u16 sxy[2];   /* +0x24 */
        s32 p;        /* +0x28 */
        s32 flag;     /* +0x2C */
    } L;

    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);

    L.v10[0] = *(u16 *)(param_1 + 0x6);
    L.v10[1] = *(u16 *)(param_1 + 0xA);
    L.v10[2] = *(u16 *)(param_1 + 0xE);
    otz = RotTransPers((s32)L.v10, (s32)L.sxy, &L.p, &L.flag);
    if (otz > 0) {
        if (L.flag >= 0) {
            ot = otTbl_801813E8[(*(u16 *)&D_800B9A02) * 5] + otz * 4;
            prim = func_80010A08(0x30);
            if (prim != 0) {
                func_8005A600((s32)prim, 1, 0, (u16)GetTPage(0, 1, 0, 0), 0);

                L.v10[0] = 0;
                L.v10[1] = *(u16 *)(param_1 + 0xA) + 0x80;
                L.v10[2] = *(u16 *)(param_1 + 0xE);
                L.sxy0[0] = L.sxy[0];
                L.sxy0[1] = L.sxy[1];
                RotTransPers((s32)L.v10, (s32)L.sxy, &L.p, &L.flag);
                poly = (u8 *)prim + 0xC;   /* the POLY_G4 riding behind the DR_MODE */

                /* r0 r1 r2 r3 */
                *(u8 *)((u8 *)prim + 0x10) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x18) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x20) = *(s32 *)(param_1 + 0x1C) / 8;
                *(u8 *)((u8 *)prim + 0x28) = *(s32 *)(param_1 + 0x1C) / 8;
                /* g0 g1 g2 g3 */
                *(u8 *)((u8 *)prim + 0x11) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x19) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x21) = *(s32 *)(param_1 + 0x1C) / 8;
                *(u8 *)((u8 *)prim + 0x29) = *(s32 *)(param_1 + 0x1C) / 8;
                /* b0 b1 b2 b3 */
                *(u8 *)((u8 *)prim + 0x12) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x1A) = *(s32 *)(param_1 + 0x1C);
                *(u8 *)((u8 *)prim + 0x22) = *(s32 *)(param_1 + 0x1C) / 8;
                *(u8 *)((u8 *)prim + 0x2A) = *(s32 *)(param_1 + 0x1C) / 8;
                /* tag len + POLY_G4 code (0x38 | ABE) */
                *(u8 *)((u8 *)prim + 0x0F) = 8;
                *(u8 *)((u8 *)prim + 0x13) = 0x3A;
                /* x0 x1 x2 x3 */
                *(s16 *)((u8 *)prim + 0x14) = L.sxy0[0];
                *(s16 *)((u8 *)prim + 0x1C) = L.sxy0[0];
                *(s16 *)((u8 *)prim + 0x24) = L.sxy[0] - 4;
                *(s16 *)((u8 *)prim + 0x2C) = L.sxy[0] + 4;
                /* y0 y1 y2 y3 */
                *(s16 *)((u8 *)prim + 0x16) = L.sxy0[1];
                *(s16 *)((u8 *)prim + 0x1E) = L.sxy0[1];
                *(s16 *)((u8 *)prim + 0x26) = L.sxy[1] - 8;
                *(s16 *)((u8 *)prim + 0x2E) = L.sxy[1] + 8;

                AddPrim(ot, poly);
                AddPrim(ot, prim);
            }
        }
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801816C0(s32 arg0)
{
    /* three parallel u16 tables, 16-byte stride, cols at +0 and +8 */
    extern s32 D_8019BCBC;
    extern s32 D_8019BCD4;
    extern u16 D_8019BCE4[];
    extern u16 D_8019BCE6[];
    extern u16 D_8019BCE8[];

    s32 v0;
    u16 buf1[3];   /* sp+0x10 */
    u16 buf2[3];   /* sp+0x18 */

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)arg0);
        return;
    }

    func_8001CA1C(v0, (s32)&D_8019BCBC);
    func_8012A828(arg0, (s32)&D_8019BCD4);

    *(u16 *)(arg0 + 0x2) += 1;   /* +0x2 : frame/anim counter */

    /* +0x70 : s16 row index */
    buf1[0] = D_8019BCE4[*(s16 *)(arg0 + 0x70) * 8];
    buf1[1] = D_8019BCE6[*(s16 *)(arg0 + 0x70) * 8];
    buf1[2] = D_8019BCE8[*(s16 *)(arg0 + 0x70) * 8];
    buf2[0] = *(u16 *)((u8 *)D_8019BCE4 + ((*(s16 *)(arg0 + 0x70) << 4) | 8));
    buf2[1] = *(u16 *)((u8 *)D_8019BCE6 + ((*(s16 *)(arg0 + 0x70) << 4) | 8));
    buf2[2] = *(u16 *)((u8 *)D_8019BCE8 + ((*(s16 *)(arg0 + 0x70) << 4) | 8));

    func_80133784(1, buf1, (s32)buf2);

    /* NOTE (§190-B): the call MUST follow all three stores in source order.
       Putting func_8002D4C8 between the 0xA and 0xE stores hand-"pre-schedules"
       the arg setup one load-delay slot too early (-2 ins, 26 mismatched). */
    *(u16 *)(arg0 + 0x6) = buf2[0];
    *(u16 *)(arg0 + 0xA) = buf2[1];
    *(u16 *)(arg0 + 0xE) = buf2[2];
    func_8002D4C8(0x718, 0);

    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) |= 0x10;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x800;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x800;
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4) |= 0x8040;
}



extern void (*D_8019BD84[])(void);

void func_80181868(void *a0) {
    D_8019BD84[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80029514(s32);
extern void func_800D1724(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void (*D_80185BDC[])(void);

void func_801818A4(void) {
    func_80029514(0x1A4);
    func_800D1724((s32)D_80185BDC);
    func_8002AC00(0xE);
    func_8002AC00(0x11);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_801818E4(void) {
        func_8002D4C8(0x79E, 0);
    }


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_801151FC;
extern s32 func_80143970(s32 a0);
extern s32 D_8019B8F4;
extern u8 D_801A007C;
extern s32 D_801AECEC;
extern s32 D_801AECF0;
extern s32 D_80127078;

void func_80181908(s32 param_1) {
    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8019B8F4) == 0) {
        return;
    }
    *(u8 *)(param_1 + 0xC0) = 1;
    *(s32 *)(param_1 + 0xB4) = -1;
    func_80143970(param_1);
    ((void (*)(s32, void *))func_8012A828)(param_1, &D_801A007C);
    *(u16 *)(param_1 + 2) += 1;
    func_8012B23C(param_1);
    D_801AECEC = func_8012C658(0x1F7, 0, param_1);
    D_801AECF0 = func_8012C658(0x1F7, 1, param_1);
    D_80127078 = 0;
    D_801151FC = 0;
}


void func_801819B8(s32 arg0) {
    extern s16 D_8019B9B0;
    s16 w;

    w = *(u16 *)(arg0 + 0xFC) + 1;
    *(u16 *)(arg0 + 0xFC) = w;

    *(s16 *)(arg0 + 0xE) = ((w - w * 72) >> 5) + 0x176;

    *(s16 *)(arg0 + 0xA) = (-(*(s16 *)(arg0 + 0xFC) * 109) >> 5) - 0x9E;
    *(s16 *)(arg0 + 0xA) -= func_8004787C(*(s16 *)(arg0 + 0xFC) << 6) >> 5;

    if (*(s16 *)(arg0 + 0xFC) == 0x20) {
        *(s16 *)(arg0 + 0x34) = 0;
        *(u16 *)(arg0 + 2) += 1;
    }
    if (*(s16 *)(arg0 + 0xFC) == 0xF) {
        func_80178B18(arg0, (s32)&D_8019B9B0);
    }
}


#include "../shared/ov/func_80181A98__76785405.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80181AA0(s32 arg0) {
    if ((*(s32 *)(arg0 + 0x1C) -= 1) != 0) {
        func_8012AD80(arg0);
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) -= 0x100;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) -= 0x100;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) -= 0x100;
    } else {
        func_8012C218((void *)arg0);
    }
}


#include "common.h"

extern void func_801813E8(s32 a0);

void func_80181B34(s32 a0) {
    u16 v1 = *(u16 *)(a0 + 0x34);

    switch (v1) {
    case 0:
        if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x100) != 0) {
            *(u16 *)(a0 + 0x34) = v1 + 1;
            *(u16 *)(a0 + 0x98) = 1;
        }
        return;
    case 1:
        if ((*(s32 *)(a0 + 0x1C) += 2) >= 0x7F) {
            *(s32 *)(a0 + 0x1C) = 0x7F;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 2:
        break;
    default:
        return;
    }
    func_801813E8(a0);
}



extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80181BE8(s32 a0, s32 a1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801AEE38;
    D_801AEE38 = a1;
    return func_8012C588(0x85, a0);
}


extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32, s32);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_80181C18(s32 param_1) {

    extern u8 D_801152A8[];
    extern M2C_UNK D_801824B0;
    extern s32 D_801AEE38;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801ABC80;
    extern char * D_801ABCB4;
    extern char D_801AEE18[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801ABC80) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_801824B0));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801AEE38, &s60);
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
        register char *tmp __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
        tmp = D_801ABCB4;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801ABCB4 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801AEE18 < puVar4) {
        D_801ABCB4 = D_801AEE18 - 0x120;
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
            register char *tmp __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
            tmp = D_801ABCB4;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801ABCB4 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801AEE18 < puVar4) {
            D_801ABCB4 = D_801AEE18 - 0x120;
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

s32 func_80181E5C(s32 param_1) {

    extern signed char D_801ABC6C[];
    int self = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    do { iVar1 = *(int *)(self + 0x1c); } while (0);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801ABC6C;
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
            p = D_801ABC6C;
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
        do { *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1; } while (0);
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        func_8012C218((void *)self);
    }
}


extern void (*D_801ABCB8[])(void);

void func_801820FC(void *a0) {
    D_801ABCB8[*(u16 *)((s32)a0 + 0x2)]();
}





