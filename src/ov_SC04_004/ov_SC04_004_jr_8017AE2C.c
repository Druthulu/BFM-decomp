#include "common.h"
#include "../shared/engine_prelude.h"


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
extern u8 D_80186BF8;
extern u8 D_80186B68;
extern u8 D_80186B44;
extern u8 D_80186B20;
extern u8 D_80186BD4;
extern u8 D_80186BB0;
extern u8 D_80186B8C;
extern u8 D_80186AFC;
extern void func_80145934(void);
extern u8 D_80186C88;
extern u8 D_80186C64;
extern u8 D_80186C40;
extern u8 D_80186C1C;
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
extern unsigned char D_80186080[];
extern unsigned char D_801860B0[];
extern unsigned char D_80186100[];
extern unsigned char D_80186130[];
extern unsigned char D_80186160[];
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
extern void (*D_801861B0[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_80186278[];
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
extern u8 D_80186300[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80186308;
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
extern int D_801B2638;
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
extern s32 D_801B263C;
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
extern s32 D_80186338;
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
extern void (*D_801863E0[])(void);
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
extern void (*D_80186404[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_801863F4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80186418[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80186424[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80186434[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018644C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018643C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80186460[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018647C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018646C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80186490[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801864A4[])(void);
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
extern s32 D_801864B8;
extern void (*D_801864E0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801864C0;
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
extern int (*D_8018652C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80186530[])(void);
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
extern unsigned short D_80186994[];
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
extern void (*D_801869A4[])(void);
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
extern int D_801B2670;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801869CC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801869AC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801869BC;
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
extern void (*D_80186A0C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80186A14[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801869E0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80186A20[])(void);
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
extern u8 D_801869F0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B2678;
extern s32 D_801B2684;
extern s32 D_801B2688;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80186A5C[])(s32 *);
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
extern s32 D_80186A30[];
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
extern s32 D_801B2680;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80186CAC[])(void);
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
extern char D_80186ACC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80186D50[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80186EA4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80186CC0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80186EAC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80186CD0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80186CF0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80186EB4[])(void);
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
extern void (*D_80186EDC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80186EE8[])(void);
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
extern void (*D_80186D5C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80186F8C;
extern void func_8015D380(s32 a0);
extern unsigned char D_80186070[];
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
extern unsigned char D_80186FA0[];
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
extern s8 D_80186FDC[];
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
extern u16 D_80187024;
extern u16 D_80187026;
extern u16 D_80187028;
extern s32 D_8018702C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80187034;
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
extern int D_80186D40;
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
extern unsigned int D_801870B8[];
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
extern void (*D_80187168[])(void);
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
extern u16 D_80187198[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_801871FC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B2690[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80187220[])(void);
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
extern int D_801B26E8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80187268[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80187258;
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
extern char D_801B1F5C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80187270[])(void);
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
extern void (*D_801872C4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018728C;
extern s16 D_801872C0;
extern s16 D_801872BE;
extern s16 D_801872BC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801872D0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B2748;
extern u8 D_801B2749;
extern u8 D_801B274A;
extern u8 D_801B274B;
extern u8 D_801B274C;
extern u8 D_801B274D;
extern u8 D_801B274E;
extern u8 D_801B274F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801872E0[])(void);
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
extern s32 D_801B2788;
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
extern void (*D_80187324[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801873A0[];
extern s32 D_801873C0[];
extern u8 D_8018743C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018745C[];
extern u8 D_8018747C[];
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
extern void (*D_80187518[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80187594[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B1F6C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801875A0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801875A8[])(void);
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
extern void (*D_80187670[])(void);
extern void func_80166618(void *a0);
extern void (*D_80187680[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80187690[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018769C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_801875FC[];
extern u8   D_80187610[];
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
extern void (*D_801876B4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801876BC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801876C4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801876CC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801876D4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801876DC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801876E4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80187798[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801877A0[])(void);
extern void func_80169F00(void *a0);
extern char D_80187750[];
extern char D_80187710[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801877D8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801877E4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018782C[])(void);
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
extern void (*D_801878A8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B2AA8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018789C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801878E0[];
extern unsigned short D_801878E8[];
extern unsigned short D_801878F0[];
extern unsigned char D_801B2AB0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B2AA8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_801878F8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B2BE4;
extern M2C_UNK D_801B2BE8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B2B70;
extern void (*D_80187928[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B2BEC[];
extern u8 D_801B2BF4[];
extern u8 D_801B2BA4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80187930[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018794C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80187954[])(void);
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
extern void (*D_801879BC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80187960;
extern u8 D_8018796C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_801879F0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_801879F8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80187A4C[])(void);
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
extern u16 D_80187A80[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80187A70[];
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
extern s32 D_80187A9C;
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
extern void (*D_80187B14[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80187B1C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80187B24[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80187B2C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80187B34[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80187B3C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80187B48[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80187B54[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80187B60[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80187B70[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80187B80[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80187B88[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80187B90[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80187B98[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80187BA0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80187BA8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80187BB0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80187BB8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80187BC0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80187BC8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80187BD0[])(void);
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
extern void (*D_80187BD8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80187BE0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80187BE8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80187BF0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80187BF8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80187C00[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80187C08[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80187C10[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80187C18[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80187C20[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80187C28[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80187C30[])(void);
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
extern void (*D_80187C74[])(void);
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
extern M2C_UNK D_80187C38;
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
extern void (*D_80187CA4[])(void);
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
extern void (*D_80187CE0[])(void);
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
extern void (*D_80187D38[])();
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
extern void (*D_80187D48[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80187D50[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80187EB8[])();
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
extern void (*D_80187EC4[])();
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
extern M2C_UNK D_801B21B4;
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
extern s16 D_801B3BD8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B3328;
extern short D_801B3C54;
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
extern s32 D_801B3754;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B377C;
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
extern s16 D_801B3738;
extern s32 func_8017A3B0(void);
extern short D_801B3774;
extern short D_801B3770;
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
/* ==== end §8b carried decl layer ==== */


extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s32 func_80012A60(s32 a0, s32 a1);

extern s16 D_801B3BA8;
extern s16 D_801B3BAA;
extern s16 D_801B3BB4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801B3BA8;

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
        func_8012B030((u8 *)pv);
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
                    func_8012B744(p, &D_801B3BB4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801B3BA8+0xC == &D_801B3BB4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801B3BA8 + 0xC)) < 0x101) {
                    D_801B3BA8 = 0;
                    D_801B3BAA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801B3BB4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801B3BA8 + 0xC)) < 0x101) {
            D_801B3BA8 = 0;
            D_801B3BAA = 0;
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
    extern s16 D_801B37B4;
    extern s16 D_801B37B6;
    extern s16 D_801B37B8;
    extern s16 D_801B37AC;
    extern s16 D_801B37AE;
    extern s16 D_801B37B0;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801B37B4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801B37B6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801B37B8, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801B37AC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801B37AE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801B37B0, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s16 D_801B373C;
extern u16 D_801B37BC;
extern u16 D_801B37BE;
extern u16 D_801B37C0;
extern s16 D_801B3BD8;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    func_8012A418();
    D_801B3BD8 = 0;
    D_801B373C = 0;
    D_801B37BC = D_80126B5E;
    D_801B37BE = D_80126B62;
    D_801B37C0 = D_80126B66;
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
    extern u8 D_80188000[];
    extern s16 D_801B37B4;
    extern s16 D_801B37AC;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80188000[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80188000[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801B37B4;
        s16 *p78C = &D_801B37AC;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801B3BD8 = 1;
        D_801B373C = 0;
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
    extern SV4_8017B368 D_801B375C;
    extern SV4_8017B368 D_801B3764;
    extern s16 D_801B37B4;
    extern s16 D_801B37AC;
    extern u16 D_80188000;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801B375C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801B3764;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80188000)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80188000)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801B37B4) = loc0;
    (*(SV4_8017B368 *)&D_801B37AC) = loc1;
    D_801B3BD8 = 1;
    D_801B373C = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801B375C;
    extern SV4_8017B368 D_801B3764;
    extern s16 D_801B37B4;
    extern s16 D_801B37AC;
    extern u16 D_80188000;
    extern s16 D_801B373C;
    extern s16 D_801B3BD8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801B375C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801B3764;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80188000)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80188000)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801B37B4) = loc0;
    (*(SV4_8017B368 *)&D_801B37AC) = loc1;
    D_801B3BD8 = 1;
    D_801B373C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801B37B4).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801B37B4).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801B37B4).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801B37AC).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801B37AC).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801B37AC).c;
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
    extern u8 D_80188000[];
    extern s16 D_801B37B4;
    extern s16 D_801B37B6;
    extern s16 D_801B37B8;
    extern s16 D_801B37AC;
    extern s16 D_801B37AE;
    extern s16 D_801B37B0;
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
        s32 a1addr = (s32)&D_80188000[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80188000[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801B37B4;
        s16 *p78C = &D_801B37AC;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801B37B6;
            v798 = D_801B37B8;
            v78C = *p78C;
            v78E = D_801B37AE;
            v790 = D_801B37B0;
            __asm__ __volatile__("");
            D_801B3BD8 = 1;
            D_801B373C = 0x1E;
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
extern s16 D_801B373C;
extern s16 D_801B37B4;
extern s16 D_801B37B6;
extern s16 D_801B37B8;
extern s16 D_801B37AC;
extern s16 D_801B37AE;
extern s16 D_801B37B0;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801B373C = 0;
    D_801B37B4 = (s16) D_80114F30;
    D_801B37B6 = (s16) D_80114F34;
    D_801B37B8 = (s16) D_80114F38;
    D_801B37AC = (s16) D_80114F24;
    D_801B37AE = (s16) D_80114F28;
    D_801B37B0 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801B37CC;
extern s16 D_801B37CE;
extern s16 D_801B37D0;
extern s16 D_801B37D4;
extern s16 D_801B37D6;
extern s16 D_801B37D8;

void func_8017B824(void) {
    D_801B37CC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801B37CE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801B37D0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801B37D4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801B37D6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801B37D8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801B37CC;
extern s16 D_801B37CE;
extern s16 D_801B37D0;
extern s16 D_801B37D4;
extern s16 D_801B37D6;
extern s16 D_801B37D8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801B37CC;
    D_80114F34 = D_801B37CE;
    D_80114F38 = D_801B37D0;
    D_80114F24 = D_801B37D4;
    D_80114F28 = D_801B37D6;
    D_80114F2C = D_801B37D8;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801B37B4), src[8..15] -> (*(S8_8017B8E8 *)&D_801B37AC) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801B37B4) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801B37AC) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u16 D_801B37BC;
extern u16 D_801B37BE;
extern u16 D_801B37C0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801B373C;
extern short D_801B37C4;
extern short D_801B37C6;
extern short D_801B37C8;
extern s16 D_801B37B4;
extern s16 D_801B37B6;
extern s16 D_801B37B8;
extern s16 D_801B37AC;
extern s16 D_801B37AE;
extern s16 D_801B37B0;

void func_8017B940(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801B37BC);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801B37BE);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801B37C0);
    (*(s16 *)&D_801B37C4) = buf[0];
    (*(s16 *)&D_801B37C6) = buf[1];
    (*(s16 *)&D_801B37C8) = buf[2];
    D_801B37B4 = D_80114F30 + buf[0];
    D_801B373C = 0;
    D_801B37B6 = D_80114F34 + buf[1];
    D_801B37B8 = D_80114F38 + buf[2];
    D_801B37AC = D_80114F24 + buf[0];
    D_801B37AE = D_80114F28 + buf[1];
    D_801B37B0 = D_80114F2C + buf[2];
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

extern SV4 D_801B375C;
extern SV4 D_801B3764;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801B3764) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801B375C = svec;

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
    D_801B3764 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801B3764)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801B375C) = svec;

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
    (*(SV4_8017BB34*)&D_801B3764) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801B3784[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801B3784;
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
extern s16 D_801B373C;
extern s16 D_801B3BD8;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801B373C = D_801B373C + 1;
    if (D_801B373C >= 0x1F) {
        D_801B3BD8 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801B373C;
extern s16 D_801B3BD8;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801B373C = D_801B373C + 1;
    if (0x18 < D_801B373C) {
        func_8012A4BC();
        D_801B3BD8 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801B373C;
extern void (*D_801B3780)(void);
extern short D_801B37C4;
extern short D_801B37C6;
extern short D_801B37C8;
extern s16 D_801B3BD8;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801B373C = D_801B373C + 1;
    if (D_801B373C >= 0x19) {
        if (D_801B3780 != 0) {
            (*D_801B3780)();
        } else {
            D_80114F30 = D_80114F30 + D_801B37C4;
            D_80114F34 = D_80114F34 + D_801B37C6;
            D_80114F38 = D_80114F38 + D_801B37C8;
            D_80114F24 = D_80114F24 + D_801B37C4;
            D_80114F28 = D_80114F28 + D_801B37C6;
            D_80114F2C = D_80114F2C + D_801B37C8;
            func_8012A4BC();
        }
        D_801B3BD8 = 0;
    }
}



extern void (*D_801880A0[])(void);

void func_8017BE60(void *a0) {
    D_801880A0[*(u8 *)((s32)a0 + 0x4)]();
}


#include "../shared/ov/func_8017BE9C__76785405.h"

#include "../shared/ov/func_8017BEA4.h"

#include "../shared/ov/func_8017BEAC.h"

#include "../shared/ov/func_8017BEB4.h"

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


/* func_8017CD9C — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801B37E0..D_801B3808 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017CD9C(s32 param_1, s32 param_2)
{

    extern s32 D_801B37E0;
    extern s32 D_801B37E4;
    extern s32 D_801B37E8;
    extern s32 D_801B37F0;
    extern s32 D_801B37F4;
    extern s32 D_801B37F8;
    extern s32 D_801B3800;
    extern s32 D_801B3804;
    extern s32 D_801B3808;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_8017CD9C vec;                              /* sp+0x10 */
    MTX_L_8017CD9C mtx;                              /* sp+0x18 */
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

    D_801B3800 = vec.a;
    D_801B37F0 = vec.a;
    D_801B37E0 = vec.a;
    D_801B3804 = vec.b;
    D_801B37F4 = vec.b;
    D_801B37E4 = vec.b;
    D_801B3808 = vec.c;
    D_801B37F8 = vec.c;
    D_801B37E8 = vec.c;
}



/* func_8017CECC — ov_SC02_027_jr_8017AE2C (227 ins).  MATCH (match_one, 227/227).
 *
 * RETRY-WAVE RE-VERIFICATION (§136b — the ledgered DIFF describes an OBSOLETE draft).
 * The s8 gate ran 14:53; THIS file was written 15:22, 28 min AFTER it.  The gate never saw it.
 * Four independent checks on the file as it stands:
 *   1. match_one              -> MATCH (227 ins)
 *   2. rtu_match (whole TU)   -> MATCH (227 ins); CC1 clean, the only warning is the TU's
 *                                pre-existing `memcpy' builtin one at TU:1530 (baseline too)
 *   3. FULL RELOCATION RESOLVE (the byte-gate's view, which match_one's mask cannot see):
 *      every R_MIPS_26 / HI16 / LO16 resolved from the D_<addr>/func_<addr> symbol values and
 *      compared word-for-word against the target .s -> 0/227 diffs.  Every jal target, every
 *      %hi/%lo symbol AND addend is right.
 *   4. COLLATERAL: TU compiled with and without the splice; all 53 other functions emit
 *      IDENTICAL words.  The only deltas are .text-relative `j' addends, every one shifted by
 *      exactly 0x38C == this function's size, which the linker resolves identically.
 * No codegen work was needed; the previous agent's tbl/tbl2 split + load-before-store lever
 * (documented below) had already closed it.
 *
 * Declarations reconciled against the WHOLE TU (grepped in one pass, D2):
 *   func_800291B4  TU:59/3422   extern s32 func_800291B4(s32 arg);     -> `& 0xFF` at the call
 *   func_8001C810  TU:1548      extern void func_8001C810(s32 a0, s32 a1);
 *   func_8001CD50  TU:1564/3518 extern void func_8001CD50(s32, s32);
 *   func_800233CC  TU:1565/3519 extern void func_800233CC(void *, unsigned short);
 *   func_8001D074  TU:124/129/3517 declared VOID -> s32 return taken through a cast (idiom 9)
 *   func_8012A828  TU:3730      extern void func_8012A828(s32 a0, void *a1);
 *   D_801152BA     TU:3657      extern u16 D_801152BA;   (the SIGNED uses need an (s16) cast:
 *                               combine folds (s16)(u16 mem) back to a plain `lh`)
 *   D_80115214     TU:3432/3658 extern s16 D_80115214;
 *   D_801B37E0     TU:3333      extern s32 D_801B37E0;
 * func_8012CAE4 / func_8012C354 are absent from the TU; the canonical engine_core.h forms
 * are reused verbatim (DEFINE_func_8012CAE4 @15355 `void func_8012CAE4(void *a0)`,
 * DEFINE_func_8012C354 @15748 `s32 func_8012C354(s32 a0, s32 a1)`).
 * D_801880D4 / D_80188110 / D_8019A9B4 / every D_801D9E9x-ECx / D_801B3890 appear nowhere
 * in the TU or engine_core.h (only D_801B37E0..EB8 and D_801D9F00..F06 are declared there).
 * D_8019A9DC is declared BLOCK-SCOPE here on purpose: the TU's only other declaration
 * (TU:3587, `extern Rec_8017C738 D_8019A9DC[];`) is itself block-scope inside func_8017C738,
 * so neither is a file-scope decl the other can collide with.
 *
 * THE 0x6C-BYTE TABLE COPY.  9 x 12-byte records = 108 bytes at alignment 2, so
 * gcc-2.7.2's mips.c:expand_block_move takes the align < UNITS_PER_WORD path and emits the
 * runtime `or / andi 3 / beq` alignment probe, an unaligned lwl/lwr loop, an aligned lw/sw
 * loop, and an unaligned 12-byte tail.  The join label after the two loops resets cse, which
 * is why the target RE-COMPUTES 108*D_801152BA for the *(a0+0xD8) store.
 *
 * WHAT CLOSED THE LAST 7 (sched.md §1.7 / §S2 — THE BIRTHING BOOST).  Two independent levers,
 * both required; neither is statement-order:
 *
 *  1. `idx = (s16)D_801152BA;` must be read BEFORE the `*(s16*)(s1+0x10) = 0x400` store.
 *     Store-then-load is a true dependence (both MEMs non-struct: the store's address varies,
 *     the load's is constant, so true_dependence's MEM_IN_STRUCT_P escape does not apply) and
 *     it pins `sh 0x10(s1)` ABOVE the `lh`.  Load-first makes it an ANTI dep, whose cost is
 *     still +1 in 2.7.2 (insn_cost is dep-kind-blind, sched.md [A23]), lifting pri(sh) to 2 so
 *     the store is picked first by the backward scheduler and lands LAST, at index 93.
 *
 *  2. `tbl` and `tbl2` MUST BE TWO SEPARATE LOCALS.  One shared `tbl` gives the D_801B3890
 *     address pseudo REG_N_SETS==2, which KILLS the birthing boost (birthing_insn_p,
 *     sched.c:2469/2490): the unboosted `la $a0` then floats to the front of the pri-1 group
 *     and lands at index 86, shoving `la $a2,D_8019A9DC` to 88 (this was the entire 7-insn
 *     residual: 86..92 rotated).  Splitting the two uses makes each pseudo single-set, the
 *     boost raises `la $a0` to its consumer's priority so it sinks to 91, and `la $a2` — whose
 *     pseudo IS genuinely multi-set (expand_block_move increments it in both copy loops, so it
 *     can never be boosted) — falls to the front at 86, exactly as the target has it.
 *     Verified invariant: with a shared `tbl`, ALL 8 legal orderings of the 4 head statements
 *     x 2 store forms (INDIRECT_REF and ARRAY_REF) give the SAME wrong order — proof the
 *     residual was priority/boost-driven, not LUID/statement-order-driven.
 */
extern s32 func_800291B4(s32 arg);
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);



void func_8017CECC(s32 a0) {

    extern u8 D_801880D4[];
    extern u8 D_80188110[];
    extern s32 D_8019A9B4;
    extern u16 D_801152BA;
    extern s16 D_80115214;
    extern s32 D_801B37E0;
    extern u8 D_801B37EC;
    extern u8 D_801B37ED;
    extern u8 D_801B37EE;
    extern u8 D_801B37FC;
    extern u8 D_801B37FD;
    extern u8 D_801B37FE;
    extern u8 D_801B380D;
    extern u8 D_801B380E;
    extern u8 D_801B3810;
    extern u8 D_801B3811;
    extern u8 D_801B3812;
    extern u8 D_801B3814;
    extern u8 D_801B3815;
    extern u8 D_801B3816;
    extern u8 D_801B381C;
    /* 9 x 12-byte records = 0x6C bytes, alignment 2 */
    extern Blk027_8017CECC D_8019A9DC;
    extern Blk027_8017CECC D_801B3890[];

    u8 *v1;
    s32 s1;
    u8 *p;
    s32 t;
    s16 i;
    Blk027_8017CECC *dst;
    Blk027_8017CECC *tbl2;
    s32 idx;
    Blk027_8017CECC *tbl;
    s32 u;
    s32 w;

    v1 = *(u8 **)(a0 + 0xDC);
    if ((func_800291B4(v1[0] + 0x3A) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    if (*(s32 *)(a0 + 0x20) == 0) {
        if (func_8012C354(a0, (s32)D_801880D4) == 0) {
            return;
        }
        func_8001C810(*(s32 *)(a0 + 0x20), (s32)&D_8019A9B4);
        func_8012A828(a0, (void *)&D_80188110[(s16)D_801152BA * 16]);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x20;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)&D_801B37E0;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)(a0 + 0xAE) = -3;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 == 0) {
        return;
    }

    p = &D_801B3810;
    *(s32 *)(a0 + 0xCC) = s1;
    func_8001CD50(s1, (s32)p);

    D_801B3812 = 0x80;
    *p = 0x80;
    D_801B3811 = 0xE0;
    D_801B3815 = 0;
    D_801B3814 = 0;
    D_801B3816 = 0;
    func_800233CC(p, 0x38);

    tbl = D_801B3890;
    idx = (s16)D_801152BA;
    dst = &tbl[idx];
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x8) = *(u16 *)(a0 + 0x6);
    t = *(u16 *)(a0 + 0xA) - 4;
    *(u16 *)(a0 + 0xA) = t;
    *(s16 *)(s1 + 0xA) = t;
    *(s16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(s1 + 0x4) |= 0x50000000;

    D_801B380E = 0xFF;
    D_801B381C = 0xFF;
    D_801B37FE = 0xFF;
    D_801B37FC = 0xFF;
    D_801B37EE = 0xFF;
    D_801B37EC = 0xFF;
    D_801B380D = 0x80;
    D_801B37FD = 0x80;
    D_801B37ED = 0x80;

    *dst = D_8019A9DC;

    i = 5;
    tbl2 = D_801B3890;
    *(s32 *)(a0 + 0xD8) = (s32)&tbl2[(s16)D_801152BA];

    while (i < 0x28) {
        if ((func_800291B4(i + 0x3B) & 0xFF) != 0) {
            break;
        }
        i++;
    }
    if (i != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    }

    w = D_801152BA + 1;
    u = *(u16 *)(a0 + 0x2) + 1;
    D_80115214 = 0;
    D_801152BA = w;
    *(u16 *)(a0 + 0x2) = u;
}



/* Declarations copied VERBATIM from the TU (ov_SC02_027_jr_8017AE2C.c):
 *   func_800291B4  TU:59
 *   currentLocationId TU:349
 *   D_80126B5C     TU:361  (scalar u8 -> pass (s32)&D_80126B5C)
 *   D_801202A0     TU:385
 *   func_80013328  TU:520
 *   D_800B99DA     TU:615
 *   rand           TU:957/1092/3543
 *   D_80126B62     TU:1793/2740/3068
 *   func_801746A4  TU:2397
 *   func_80178B18  TU:2539/3653
 *   func_8017CD9C  TU:3465/3542 (void return)
 *   D_80115214     TU:3547
 * func_8012BD14 / D_80188108 / D_8018816C appear nowhere in the TU; the
 * canonical engine_core.h form of func_8012BD14 is `void func_8012BD14(s32)`
 * (DEFINE_func_8012BD14), so it is declared void and the s32 return is taken
 * through a cast at the call site (idiom 9). */
extern s32 func_800291B4(s32 arg);
extern s16 currentLocationId;
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_801746A4(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017CD9C(s32 a0, s32 a1);
extern void func_8012BD14(s32 a0);

void func_8017D258(s32 a0) {

    extern u8 D_80126B5C;
    extern u8 D_801202A0[];
    extern u16 D_80126B62;
    extern s16 D_80115214;
    extern u8 D_80188108[];
    extern u8 D_8018816C[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_800B99DA;
    s32 s0 = *(s32 *)(a0 + 0x20);
    s16 found;
    s32 lvl;
    s16 i;
    s16 j;
    s32 rand_val;

    if ((D_800B99DA & 0xF) == 0) {
        u8 *p;
        u8 *end;
        for (p = D_801202A0, end = p + 0x6480; p < end; p += 0x10C) {
            if (*(u16 *)p == 0x128) {
                found = ((s32)p == a0);
                break;
            }
        }
        lvl = func_80013328(a0 + 4, (s32)&D_80126B5C);
        if (lvl < 0x800) {
            lvl = 0x44 - ((lvl >> 5) & 0x38);
        } else {
            lvl = 4;
        }
        if (found != 0 || D_80115214 < lvl) {
            D_80115214 = lvl;
        }
    }

    *(u16 *)(s0 + 0x12) += 0x20;
    rand_val = rand();
    func_8017CD9C(a0, rand_val & 0xF);

    if (*(u16 *)(a0 + 0x5E) != 0) {
        for (i = 0; (u16)i < 8; i++) {
            if (*(u16 *)(a0 + 0x5E) == D_80188108[i]) {
                func_801746A4();
                *(s32 *)(a0 + 0x1C) = 0x20;
                *(u16 *)(a0 + 0x2) += 1;
            }
        }
        *(s16 *)(a0 + 0x5E) = 0;
        return;
    }

    if (*(s16 *)(a0 + 0x10A) != 0) {
        return;
    }

    j = 5;
    do {
        if ((func_800291B4(j + 0x3B) & 0xFF) != 0) {
            break;
        }
        j++;
    } while (j < 0x28);

    if (j != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    } else if (((s32 (*)(s32))func_8012BD14)(a0) < 0x2A40) {
        if (currentLocationId == 0x3028) {
            if ((u16)(*(u16 *)(a0 + 0xA) - D_80126B62 + 4) < 4) {
                *(u16 *)(a0 + 0x106) += 1;
            }
            if (*(s16 *)(a0 + 0x106) < 2) {
                return;
            }
        }
        func_80178B18(a0, (s32)D_8018816C);
        *(s16 *)(a0 + 0x10A) = 1;
        *(s16 *)(a0 + 0x2) = 0xA;
    } else {
        *(s16 *)(a0 + 0x106) = 0;
    }
}



extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);

/* 0x801DA0F0 has no symbol (it is interior to D_801DA084); the real relocs
 * in the .s are D_801B3A54/108/10C, with $s0 = D_801B3A54 - 0x14. */

void func_8017D4D0(s32 a0) {

    extern u8 D_801B3850;
    extern u8 D_801B3851;
    extern u8 D_801B3852;
    extern u8 D_801B3854;
    extern u8 D_801B3855;
    extern u8 D_801B3856;
    extern s32 D_801B3A54[];
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801B3850;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801B3851 = 0xFF;
    D_801B3852 = 0xFF;
    *p = 0xFF;
    D_801B3856 = 8;
    D_801B3854 = 8;
    D_801B3855 = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801B3A54[0] = sp[0];
    D_801B3A54[1] = sp[1];
    D_801B3A54[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801B3A54[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801B3A54[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017CD9C(s32 a0, s32 a1);

void func_8017D618(s32 a0) {
    extern Rec_8017C738_8017D618 D_8019A9DC[];

    Rec_8017C738_8017D618 *q = D_8019A9DC;
    Rec_8017C738_8017D618 *p = *(Rec_8017C738_8017D618 **)(a0 + 0xD8);
    u8 *v1 = *(u8 **)(a0 + 0xDC);
    s32 s1 = *(s32 *)(a0 + 0xD0);
    s32 s4 = *(s32 *)(a0 + 0x20);
    s16 val;
    s32 t;
    s16 i;

    if (v1[1] != 0) {
        if (*(s16 *)(a0 + 0x108) == 0) {
            *(s16 *)(a0 + 0x108) = func_80128CFC(*(u16 *)(v1 + 2));
        }
    }

    val = *(u16 *)(s1 + 0x1A) + 0x80;
    *(s16 *)(s1 + 0x1A) = val;
    *(s16 *)(s1 + 0x18) = val;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t != -1) {
        func_8017CD9C(a0, 0);
        for (i = 0; i < 9; ) {
            p->f0 += (s16)q->f0 >> 1;
            if (i != 0) {
                p->f2 += (q->f2 + 0x30) >> 1;
                p->f4 += (s16)q->f4 >> 1;
                p->f6 += 0x40;
                p->f8 += 0x80;
                p->fA += 0x100;
            }
            i++;
            q++;
            p++;
        }
    } else {
        *(s16 *)s4 = 0;
        *(u16 *)(a0 + 0x2) += 1;
    }
}



extern void (*D_801881BC[])(void);

void func_8017D798(void *a0) {
    D_801881BC[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017D7D4(void) {

    extern s32 D_80126B58;
    func_8014BCEC((s32)&D_80126B58, 0x5);
    func_8014BD24((s32)&D_80126B58, 0x270F);
    func_8002D4C8(0xBFE, 0);
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017CD9C(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);


#include "../shared/ov/func_8017D820__695b63f3.h"



extern s16 func_80128CFC(u16 a0);

void func_8017D914(void *a0) {
    void *v1 = *(void **)(a0 + 0xDC);
    s16 v0;

    if (*(u8 *)(v1 + 1) == 0) {
        v0 = 1;
    } else {
        v0 = *(s16 *)(a0 + 0x108);
        if (v0 == 0) {
            u16 arg = *(u16 *)(v1 + 2);
            v0 = func_80128CFC(arg);
            *(s16 *)(a0 + 0x108) = v0;
        }
        v0 = *(s16 *)(a0 + 0x108);
    }

    if (v0 != 0) {
        *(u16 *)(a0 + 0x2) += 1;
    }
}




extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);

void func_8017D994(s32 a0) {
    s32 v0;
    s32 *s0_ptr;
    u16 sp[8];

    s0_ptr = *(s32 **)(a0 + 0xDC);
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        return;
    }

    func_8001C214(v0, s0_ptr[1]);
    func_8012A828(a0, (void *)s0_ptr[2]);

    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0x58) = 0;

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);

    func_800D20C0(&sp[0], &sp[4], 0);
    func_800D23D0(&sp[4]);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = sp[5] + 0x800;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s32 func_80178B18(s32 param_1, s32 param_2);

void func_8017DA48(s32 a0) {
    s32 ptr1 = *(s32 *)(a0 + 0xD0);
    s32 ptr2 = *(s32 *)(a0 + 0xDC);
    s16 val = *(u16 *)(ptr1 + 0x1A) - 0xC0;

    *(s16 *)(ptr1 + 0x1A) = val;
    *(s16 *)(ptr1 + 0x18) = val;

    if (val < 0) {
        *(s16 *)(ptr1 + 0x0) = 0;
        func_80178B18(a0, *(s32 *)(ptr2 + 0xC));
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}




extern void func_800291A0(s32, s32);
extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017DAB4(s32 a0) {
    extern void func_8002955C(void);
    extern s32 func_8002953C(void);
    extern void func_8002AC00(s32 arg0);
    u8 *p = *(u8 **)(a0 + 0xDC);

    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        func_800291A0(*p + 0x3A, 1);
        func_8002955C();
        if ((u32)func_8002953C() >= 0x23U) {
            func_8002AC00(0x25);
        }
        *(u16 *)(a0 + 2) += 1;
    }
}


extern void func_8012C218(void *a0);
    void func_8017DB40(void) {
        ((s32 (*)(void))func_8012C218)();
    }




#include "../shared/ov/func_8017DB60__dcca8f8f.h"


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017DBB4(void *a0) {
    func_80146A6C(0x19, a0, 0, 0, 0, 0, 1);
}



extern void (*D_80188214[])(void);

void func_8017DBF0(void *a0) {
    D_80188214[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017DC2C(void *a0)
{
    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        func_80147324(*(u16 *)((s32)a0 + 0x2E));
    }
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



// @class: plumbing
// @stuck: none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

extern void func_8017DF10(int);

#include "../shared/ov/func_8017DC7C__674c410a.h"



/* Entity record touched by func_8017DCD8 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */

#include "../shared/ov/func_8017DCD8__b2ff7ffd.h"




/* func_8017DD5C — entity tick with a two-mode "hit/shake" arm.
 *   +0x1C s32  frame counter (lw / sw), signed compare against 0x20
 *   +0x34 ptr  sub-object read up-front (lives in $s0 across the jals)
 *   +0x30 s32  mode flag (0 = direct sub-object, else the +0x20 sub-sub-object)
 *   +0x02 u16  state word bumped in the timeout arm
 *
 * §71 sibling-first: func_8017C69C in this same TU is the identical shape —
 * counter @0x1C, sub-object @0x34, the 0x60/0x62/0x64 halfword triple and the
 * `do { func_80146A6C(0x1B, obj, ...); } while (++i < 3);` s16 loop.
 */

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8014708C(void *arg0);
extern s32 func_801472C8(struct S *a0);
extern void func_8017DF10(int);

#include "../shared/ov/func_8017DD5C__3551370f.h"


extern void func_8017DF10(int);
extern void func_80146C3C(void);
#include "../shared/ov/func_8017DEC4__b128b825.h"




/* func_8017DF10 — 4-point primitive sweep driven by the 44-byte curve table
 * D_801881E8.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_8017DF10(int param_1)
{

    extern u16 D_800B99DA;
    extern u8  D_801881E8[];
    SVec8_8017C218_8017DF10 rot;
    s32   pad0[2];
    Prim_8017C218_8017DF10  prim;
    s32   pad1[1];
    Mtx_8017C218_8017DF10   mtx;
    s32   pad2[8];
    s32   obj;
    u8   *p;
    s16   i;
    s32   c;

    obj = *(s32 *)(param_1 + 0x34);
    rot.vx = rot.vy = rot.vz = *(u16 *)(param_1 + 0x12);
    func_80017DC4(&rot, &mtx);

    prim.v[1].vx = prim.v[1].vy = prim.v[1].vz = 0;
    prim.v[0].vy = prim.v[2].vy = prim.v[3].vy = 0;
    prim.c[1].r = prim.c[1].g = prim.c[1].b = 0;

    c = ((s32)(s16)*(u16 *)(param_1 + 0x12) >> 5) + 0x20;
    prim.c[0].r = prim.c[0].g = prim.c[0].b =
    prim.c[2].r = prim.c[2].g = prim.c[2].b =
    prim.c[3].r = prim.c[3].g = prim.c[3].b = c;
    if (D_800B99DA & 1) {
        prim.c[0].r = prim.c[2].r = prim.c[3].r = prim.c[3].r >> 1;
    }

    prim.code = 0x50000000;
    rot.vx = *(u16 *)(obj + 0x6);
    rot.vy = *(u16 *)(obj + 0xA) - 8;
    rot.vz = *(u16 *)(obj + 0xE);
    func_80017E68(&rot, &mtx);

    p = D_801881E8;
    i = 0;
    do {
        prim.v[0].vx = (s8)*p++;
        prim.v[0].vz = (s8)*p++;
        prim.v[2].vx = (s8)*p++;
        prim.v[2].vz = (s8)*p++;
        prim.v[3].vx = (s8)*p++;
        prim.v[3].vz = (s8)*p--;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 10);

    prim.c[0].r = prim.c[0].g = prim.c[0].b = 0;
    p = D_801881E8;
    i = 0;
    do {
        prim.v[2].vx = (s8)*p++;
        prim.v[0].vx = prim.v[2].vx << 1;
        prim.v[2].vz = (s8)*p++;
        prim.v[0].vz = prim.v[2].vz << 1;
        prim.v[3].vx = (s8)*p++;
        prim.v[1].vx = prim.v[3].vx << 1;
        prim.v[3].vz = (s8)*p--;
        prim.v[1].vz = prim.v[3].vz << 1;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 0x14);

    if (*(s16 *)(param_1 + 0x2A) != 0) {
        p = D_801881E8;
        i = 0;
        do {
            prim.v[0].vx = prim.v[2].vx = (s8)*p++;
            prim.v[0].vz = prim.v[2].vz = (s8)*p++;
            prim.v[1].vx = prim.v[3].vx = (s8)*p++;
            prim.v[1].vz = prim.v[3].vz = (s8)*p--;
            prim.v[0].vy = prim.v[1].vy = *(u16 *)(param_1 + 0x2A);
            func_80017758(&prim, &mtx);
            i++;
        } while (i < 0x14);
    }
}



extern void (*D_80188228[])(void);

void func_8017E21C(void *a0) {
    D_80188228[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017E258(void *a0)
{
    func_80147324(*(u16 *)((s32)a0 + 0x2E));
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



/* func_8017E298 — a state-tick: bump the frame counter at 0x1C; while it is
 * below 0xC spin the angle at 0x12 by 0xE0, otherwise reset the counter, zero
 * the vector at *(0x34)+0x60/0x64, set +0x62 to 0x3000 and advance the state
 * word at 0x02.  Falls through to ((void (*)(void *))func_8017DF10)(a0) on both arms (the target
 * leaves $a0 untouched, so the call needs no move).
 *
 * §71 sibling-first: func_8017C560 (same TU, 4 bytes earlier) is the same
 * `*(u16 *)(a0 + 2) += 1` idiom, and func_8017DF10's own prologue reads
 * `lw $s1, 0x34($s2)` / `lhu $v0, 0x12($s2)` — same record, same widths.
 */

extern void func_8017DF10(int);

#include "../shared/ov/func_8017E298__8909e8bd.h"



/* func_8017E308 — small entity tick:
 *   read counter @0x1C and the sub-object pointer @0x34 up-front, bump the
 *   counter unconditionally (gcc puts that store in the beqz delay slot),
 *   then either slide @0x2A down by 0x10 or run the 3-call teardown. */

extern void func_80147324(s32 arg0);
extern void func_80147084(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_8017DF10(int);

#include "../shared/ov/func_8017E308.h"



extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017DF10(int);

#include "../shared/ov/func_8017E394__d086119e.h"


extern void func_8017DF10(int);
extern void func_80146C3C(void);
#include "../shared/ov/func_8017E468.h"



extern void (*D_8018823C[])(void);

void func_8017E4BC(void *a0) {
    D_8018823C[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017E4F8 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
 * MATCH (45 ins), match_one + rtu_match. Four levers, in the order they were found:
 *
 * 1. §71 sibling-first — same entity shape as func_8017C610 / func_8017C69C in this
 *    TU: sub-object pointer @0x34 read BEFORE the call (it lives in $s1 across the
 *    jal), state word @0x2 bumped last. §3-T4: `beqz $v1,else` => `if (p->f2C) {..}`.
 *    ONE rand() feeds three fields; the raw low 6 bits use a bare `andi` (no extend)
 *    while the >>12 / >>6 uses share one `sll $x,16` — that shared sign-extend is
 *    what forces `r` to be a `short` local rather than an int.
 *
 * 2. §5a CROSS-JUMP — both arms end in `sh ?,0xA($s0)`; gcc tail-merged them (23 off).
 *    They only stay separate because the loaded halfword lands in a DIFFERENT hard
 *    reg per arm, which needs (a) the load to be its own statement at the TOP of each
 *    arm and (b) a SEPARATE temp per arm (t / t2) — one shared temp is one pseudo,
 *    gets one register in both arms, and re-merges. 23 -> 10 -> 6.
 *
 * 3. +0x16 is SIGNED: the target materialises -0x20 as `addiu $v0,$zero,-0x20`, not
 *    `ori 0xffe0`, so that store must go through an s16.
 *
 * 4. §49 BIRTHING BOOST (the last 6 -> 2 -> 0). Residual was two ALU insns swapped
 *    with identical registers; source statement order does NOT flip it, because
 *    sched1's `adjust_priority`/`birthing_insn_p` hands every SET(REG,..) whose dest
 *    has REG_N_SETS==1 a 0x7f000001 priority, so it sinks to just before its consumer
 *    and fixes the .greg LUID order that sched2's tie-break then reads.
 *    THE DIAL: give the offending insn's dest a SECOND set so it loses the boost —
 *    here one `u16 d` reused by both tail statements. It must be a THIRD temp, not
 *    `c` itself: writing `c = c + 1;` also un-boosts c's LOAD, which then starves to
 *    the front of the block and swaps the two `lhu`s instead. Boost the loads, starve
 *    the arithmetic. */

extern int rand(void);

#include "../shared/ov/func_8017E4F8__d8145911.h"


extern void func_800D22E4(s32 a0);
extern void func_80146C3C(void);
extern void func_8017E608(void *a0);
#include "../shared/ov/func_8017E5AC__b35f08b0.h"




#include "../shared/ov/func_8017E608__66356b87.h"




extern void func_80029124(s32, s32);
extern void func_800291F0(s32, s32);
extern void func_8002D4C8(s32, s32);
/* NOTE: func_8017EF1C is DEFINED later in this TU as `int func_8017EF1C(int)`.
 * Conform to that signature (byte-neutral: return value unused, $a0 = 0). */
extern int func_8017EF1C(int);

void func_8017E778(void)
{

    extern s32 D_8011F9C4;
    extern s32 D_801888A8;
    extern s32 D_80188970;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_8011F9C4 = 1;
    func_80029124(0xCC, 1);
    func_800291F0(4, 0xCC);
    func_8002D4C8(6, 0);
    D_801274C8 = (u8 *)&D_801888A8;
    D_801274CC = (void *)&D_80188970;
    func_8017EF1C(0);
}


extern int func_8017EF1C(int);
extern s32 D_8011F9C4;
extern s32 D_80188984;
extern s32 D_80188A38;
extern u8 *D_801274C8;
extern void *D_801274CC;
extern void func_80029124(s32, s32);
extern void func_800291F0(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017E7E8(void)
{
    D_8011F9C4 = 1;
    func_80029124(0xCD, 1);
    func_800291F0(4, 0xCD);
    func_8002D4C8(6, 0);
    D_801274C8 = (u8 *)&D_80188984;
    D_801274CC = (void *)&D_80188A38;
    ((void (*)(s32))func_8017EF1C)(1);
}



extern void (*D_8018830C[])(void);

void func_8017E858(void *a0) {
    D_8018830C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017EA88(void);
extern void func_800167B8(s32 a0);

s32 func_8017E894(s32 a0) {
    func_8017EA88();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017E8D8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017EAB0(void);

s32 func_8017E8FC(s32 a0) {
    func_8017EAB0();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E93C(u8 *a0) {
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
    void func_8017E9B8(void) {
        func_800D1EBC();
    }



extern void (*D_80188320[])(void);

void func_8017E9D8(void *a0) {
    D_80188320[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017EA14(s32 a0) {
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
void func_8017EA88(void) {

    extern s32 D_8018832C(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018832C, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017EAB0(void) {

    extern s32 D_80188330(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80188330, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017EC08(void *a0);

void func_8017EAD8(void) {

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
    D_80126968 = 0x2aa;
    D_8012696A = 0xa00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EC08, 0);
    func_8012A094((s32)D_80126948);
    func_8017EC08(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017EC08(void *a0);

void func_8017EB70(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x2AA;
    D_8012696A = 0xA00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EC08, 1);
    func_8012A094((s32)D_80126948);
    func_8017EC08(D_80126948);
}



extern void (*D_8018833C[])(void);

void func_8017EC08(void *a0) {
    D_8018833C[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017ED84(s32 param_1, s16 *param_2);

void func_8017EC44(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80188344[];
    extern Blk8_80126940_8017EC44 D_80126940;
    Blk8_80126940_8017EC44 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80188344[t];
    }
    sp10 = D_80126940;
    func_8017ED84(a0, sp10.v);
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017ED84(s32 param_1, s16 *param_2);

void func_8017ECE4(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80188348[];
    extern Blk8_80126940_8017ECE4 D_80126940;
    Blk8_80126940_8017ECE4 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80188348[t];
    }
    sp10 = D_80126940;
    func_8017ED84(a0, sp10.v);
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

void func_8017ED84(s32 param_1, s16 *param_2) {
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

int func_8017EF1C(int param_1)
{

    extern unsigned char D_8018834C[];
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_8018834C + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}



s32 func_8017EF4C(void) {
    return 85;
}



extern void func_80019064(void *a0);

void func_8017EF54(void *a0) {

    extern u8 D_80188354;
    extern void (*D_80188378[])(void *);
    func_80019064(&D_80188354);
    D_80188378[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8017EFF4(s32 a0);
extern void func_80146CA0(void *a0);
void func_8017EFAC(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_8017EFF4(a0);
    func_80146CA0((void *)a0);
}


extern int func_801511E0(int arg);
extern s32 D_8018835C;
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80172630(u8 *a0);
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 arg0);
extern void func_80149020(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);

void func_8017EFF4(s32 a0)
{
    register s32 s0 asm("$16") = a0;
    s32 a2, a3;

    func_80149020((s32 *)s0);
    func_80147324(0x451);
    func_801511E0(s0);
    func_80154274((s32 *)s0, (s32)&D_8018835C);
    *(u8 *)(s0 + 0xDE) = 0x5A;
    func_80147324(0x7EB);

    a2 = 0;
    a3 = 0;
    ((void (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x3F, (void *)s0, a2, a3, 0, 0, 0);
    func_80172630((u8 *)s0);
    func_80146CA0((void *)s0);
}


void func_8017F07C(s32 a0)
{
    register s32 s0 asm("$16") = a0;
    u8 v1;

    func_80149020((s32 *)s0);
    v1 = *(u8 *)(s0 + 0xDE);
    *(u8 *)(s0 + 0xDE) = v1 + 0xFF;
    if (v1 == 0) {
        func_8017F0E0(s0);
        func_80159B3C((void *)s0);
        func_80165718(s0);
    } else {
        func_80172630((u8 *)s0);
    }
}


extern u8 D_80062C04[];
extern void func_80019064(void *a0);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_8017F0E0(s32 a0)
{
    s32 s0 = a0;
    ((void (*)(s32))func_80019064)((s32)&(*(s32 *)D_80062C04));
    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}



extern void (*D_801883B0[])(void);

void func_8017F130(void *a0) {
    D_801883B0[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_80188384[];
extern void func_8017F5C4(s32 *a0);
extern void func_8017F5E0(s32 *a0);
extern void func_80146C3C();

void func_8017F16C(s32 a0) {
    s32 a1;
    volatile s32 pad[12];

    a1 = func_800D21C4(a0, (s32)&D_80188384, 0x2B);
    *(s32 *)(a0 + 0x20) = a1;

    if (a1 != 0) {
        *(s16 *)(a1 + 0x28) = 0x224;
        *(s16 *)(a1 + 0x2A) = 0x1A8;
        *(s16 *)(a1 + 0x1A) = 0x3000;
        *(s16 *)(a1 + 0x18) = 0x3000;
        *(s16 *)(a1 + 0x14) = -0x400;

        *(s32 *)(a1 + 0x04) |= 0x48000000;
        *(u16 *)(a1 + 0x2C) = 0xC080;

        func_8017F5C4((s32 *)a0);
        func_8017F5E0((s32 *)a0);

        *(s32 *)(a0 + 0x2C) = 0;
        *(s32 *)(a0 + 0x30) = 0;

        func_80146E90((s32 *)a0, 0x5A);

        *(u16 *)(a0 + 0x02) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}



extern void func_8017F5E0(s32 *a0);
extern void func_800183E0(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017FBEC(s32 *a0);
extern void func_80147324(s32 arg0);
extern s32 func_80146E98(s32 a0);
extern s32 func_8017FBFC(void *a0);
extern void func_8014ABF0(void);
extern void func_80146C3C();


void func_8017F228(s32 param_1) {

    extern void *D_801883C0[];
    extern s32 D_801883A8[2];
    s32 iVar1;
    s32 iVar3;
    void *puVar2;

    iVar3 = *(s32 *)(param_1 + 0x20);
    func_8017F5E0((s32 *)param_1);
    if (*(s32 *)(param_1 + 0x30) == 0) {
        puVar2 = D_801883C0[*(s32 *)(param_1 + 0x2c)];
        if (D_801883C0[*(s32 *)(param_1 + 0x2c)] == 0) {
            *(s32 *)(param_1 + 0x30) = 0x20;
            *(s32 *)(param_1 + 0x2c) = 0;
            puVar2 = D_801883C0[0];
        }
        func_800183E0((s32)puVar2);
        *(s32 *)(param_1 + 0x2c) = *(s32 *)(param_1 + 0x2c) + 1;
    } else {
        s32 iVar0 = *(s32 *)(param_1 + 0x30) - 1;
        *(s32 *)(param_1 + 0x30) = iVar0;
        if ((iVar0 == 0) && (*(s32 *)(param_1 + 0x1c) != 0)) {
            func_80147324(0x7EC);
        }
    }
    if (*(s32 *)(param_1 + 0x1c) == 1) {
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 1);
        func_8017FBEC(D_801883A8);
        func_80147324(0x7F4);
        *(u32 *)(iVar3 + 4) = *(u32 *)(iVar3 + 4) | 0x80000000;
    }
    iVar1 = func_80146E98(param_1);
    if ((iVar1 != 0) && (iVar1 = func_8017FBFC((void *)D_801883A8), iVar1 != 0)) {
        ((void (*)(s32))func_8014ABF0)(0x40);
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


void func_8017F5C4(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x4);
        *(s32 *)((s32)a0 + 0x14) = *(s32 *)((s32)a0 + 0x8);
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0xC);
    }


void func_8017F5E0(s32 *a0)
{
    register s32 t1 asm("$6");
    register s32 t2 asm("$2");
    register s32 t3 asm("$3");
    s32 x;

    t1 = a0[4];
    x = a0[13];
    t2 = a0[5];
    t3 = a0[6];
    a0[1] = t1;
    a0[2] = t2;
    a0[3] = t3;
    func_80149374(x, (s32)(a0 + 1));
}



extern void (*D_801883E8[])(void);

void func_8017F620(void *a0) {
    D_801883E8[*(u16 *)((s32)a0 + 0x2)]();
}



/* Host TU (src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c) already has these three via
 * ../shared/engine_core.h -> engine_types.h as SVECTOR (:997), MATRIX (:1168) and
 * Vec32 (:1098) -- byte-identical layouts. Renamed here only because match_one
 * compiles standalone with -Iinclude (engine_core.h is not on that path); on bank,
 * drop these three typedefs and use the TU's own names. */
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F65C;   /*  8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0_8017F65C; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_8017D7C0_8017F65C;  /* 16 bytes, align 4 */

/* ov_SC02_041 func_8017F65C -- 181 ins, zero-crack family exemplar (reach x4:
 * ov_SC04_002:8017f19c, ov_SC04_004:8017f65c, ov_SC04_011:8017f340).
 *
 * Spawn-a-particle-burst routine:
 *   obj = actor->0x34; p = alloc(); actor->0x20 = p;
 *   if (p) { init p, force its "hidden" bit, copy the actor position into it,
 *            scale it from a table, jitter a rotation SVECTOR + a velocity
 *            Vec32 with rand(), RotMatrix + ApplyMatrix into the actor's
 *            velocity, then 9 more rand() shorts at actor+0x38 }
 *   else   { func_80146C3C(actor) }
 *
 * Frame (0x60): sp+0x10 s16 buf[4]   (func_80015978/func_80015954 position temp)
 *               sp+0x18 SVECTOR rot  (8 bytes, align 2)
 *               sp+0x20 MATRIX  m    (0x20 bytes)
 *               sp+0x40 Vec32   vel  (16 bytes, align 4)
 *               sp+0x50..0x5F saved s0/s1/s2/ra
 * -> declaration order IS frame order (gcc-2.7.2 MIPS frame grows upward).
 */

extern void func_8001CF00(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_801465C0(void);
extern void func_80146C3C();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern int rand(void);


void func_8017F65C(s32 param_1) {

    extern SV_8017D7C0_8017F65C D_801883F4[]; /* stride 8, align 2 -> lwl/lwr + swl/swr copy */
    extern V32_8017D7C0_8017F65C D_80188424;   /* 16 bytes, align 4 -> plain lw/sw copy      */
    extern u16     D_80188434[]; /* stride 2 scale table                       */
    s16 buf[4];
    SV_8017D7C0_8017F65C rot;
    MTX_8017D7C0_8017F65C m;
    V32_8017D7C0_8017F65C vel;
    s32 obj;
    s32 p;
    s16 *q;
    s32 i;
    u16 sc;

    obj = *(s32 *)(param_1 + 0x34);
    p = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        func_8001CF00(p);
        *(s32 *)(p + 0x4) |= 0x80000000;
        func_80015978(obj + 4, (s32 *)buf);
        func_80015954((s32)buf, param_1 + 4);

        sc = D_80188434[*(s32 *)(param_1 + 0x30)];
        *(u16 *)(p + 0x18) = *(u16 *)(p + 0x1a) = *(u16 *)(p + 0x1c) = sc;

        vel = D_80188424;
        rot = D_801883F4[*(s32 *)(param_1 + 0x2c)];

        if (*(s32 *)(param_1 + 0x30) != 0) {
            /* LEVER: the compound `+=` is load-bearing. Spelled out as
             * `rot.vx = rot.vx - 0x200 + ((rand() & 0x3f) << 4);` gcc-2.7.2 folds
             * the -0x200 onto the JITTER term (addiu $v0 after the sll) instead of
             * onto the loaded field (addiu $v1 after the lhu) -- 9 mismatched ins.
             * `a += jitter - 0x200` keeps `a` the accumulator and emits the target's
             * lhu / sll / addiu $v1,-0x200 / addu $v1,$v0. See notes at the bottom. */
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) << 16;
            vel.vy = ((rand() & 0x1f) - 0x10) << 16;
            vel.vz = ((rand() & 0x1f) - 0x10) << 16;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        *(s32 *)(param_1 + 0x10) = vel.vx;
        *(s32 *)(param_1 + 0x14) = vel.vy;
        *(s32 *)(param_1 + 0x18) = vel.vz;

        q = (s16 *)(param_1 + 0x38);
        i = 0;
        *(s32 *)(param_1 + 0x4c) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x50) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x54) = ((rand() & 0x1f) - 0x10) * 11;

        do {
            i++;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
        } while (i < 3);

        func_80146E90((s32 *)param_1, 2);
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_8017F9F4();
extern void func_8017FB78(s32*);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);

void func_8017F930(s32 *a0) {
    func_8017F9F4();
    ((void (*)(void *))func_8017FB78)(a0);
    if (func_80146E98((s32)a0) != 0) {
        *(s32 *)(a0 + 4) >>= 2;
        *(s32 *)(a0 + 5) >>= 2;
        *(s32 *)(a0 + 6) >>= 2;
        func_80146E90(a0, 0x40);
        *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_8017F9F4();
extern void func_8017FB78();

void func_8017F9AC(param_1)
s32 param_1;
{
    func_8017F9F4(param_1);
    func_8017FB78(param_1);
    if (func_80146E98(param_1) != 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_8017FA1C(s32 param_1, s32 param_2);
extern u8 D_80188390[];

void func_8017F9F4(s32 param_1)
{
    func_8017FA1C(param_1, (s32)D_80188390);
}


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017FA1C;   /* 0x20 bytes: m@0, t@0x14 */

extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80017DF8(s16 *a0, void *a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_80017168(void *a0, void *a1);

void func_8017FA1C(s32 param_1, s32 param_2)
{
    MTX_8017FA1C mtx;
    s32 buf2[2];
    s32 obj;

    obj = *(s32 *)(param_1 + 0x20);
    *(s32 *)(param_2 + 0x1C) = 0x50000000;

    func_80017DC4((void *)(obj + 0x18), &mtx);
    func_80017DF8((s16 *)(obj + 0x10), &mtx);

    func_80015978(param_1 + 4, buf2);
    func_80017E68((void *)buf2, &mtx);
    func_80017168((void *)param_2, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x38);
    mtx.t[1] += *(s16 *)(param_1 + 0x3A);
    mtx.t[2] += *(s16 *)(param_1 + 0x3C);
    func_80017168((void *)param_2, &mtx);
    func_80017E68((void *)buf2, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x3E);
    mtx.t[1] += *(s16 *)(param_1 + 0x40);
    mtx.t[2] += *(s16 *)(param_1 + 0x42);
    func_80017168((void *)param_2, &mtx);
    func_80017E68((void *)buf2, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x44);
    mtx.t[1] += *(s16 *)(param_1 + 0x46);
    mtx.t[2] += *(s16 *)(param_1 + 0x48);
    func_80017168((void *)param_2, &mtx);
}


void func_8017FB78(s32 *a0) {
    s16 *p;

    a0[1] += a0[4];
    a0[2] += a0[5];
    a0[3] += a0[6];
    p = (s16 *)a0[8];
    p[8] += a0[19];
    p[9] += a0[20];
    p[10] += a0[21];
}


void func_8017FBEC(s32 *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0x80404080;
    }


extern u16 D_800B99DA;

s32 func_8017FBFC(void *a0) {
    u8 val;
    u16 global;
    s32 result;
    s32 cmp;
    register s32 zr __asm__("$0");

    val = *(u8 *)((s32)a0 + 3) - 2;
    *(u8 *)((s32)a0 + 3) = val;

    if ((val & 0xFF) == 0) {
        goto ret1;
    }

    __asm__ __volatile__("" : "=r"(val) : "0"(val));

    global = D_800B99DA;

    if ((global & 1) == 0) {
        goto add40;
    }
    result = val & 0xFF;
    goto joinpt;
add40:
    result = (val & 0xFF) + 0x40;
joinpt:

    if (result >= 0x101) {
        result = 0xFF;
    }

    cmp = result + zr;

    *(u8 *)((s32)a0 + 2) = result;
    if (cmp < (s32)*(u8 *)a0) {
        *(u8 *)a0 = result;
    }

    if (cmp < (s32)*(u8 *)((s32)a0 + 1)) {
        *(u8 *)((s32)a0 + 1) = result;
    }

    return 0;

ret1:
    return 1;
}



extern void (*D_801886F8[])(void);

void func_8017FC88(void *a0) {
    D_801886F8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s16 a1);
    extern s32 func_8012AD50(void *a0);
    void func_8017FCC4(s32 *a0) {
        func_8012BF4C(a0, 0);
        ((void (*)(void *))func_8012AD50)((void *)a0);
    }


extern s32 func_8012BEE8(s32 arg);
extern s32 func_8017267C(s32 *a0);
extern void func_8012BF4C(s32 *a0, s16 a1);
extern s32 rand(void);

void func_8017FCF8(void *a0)
{

    extern s32 *D_80126B78;
    extern s32 D_80126B58;
    s16 v1;
    s32 v0;
    s32 s0;

    v0 = ((s32 (*)(void))func_8012BEE8)();
    if (v0 == 0)
        return;

    v1 = *(s16 *)((s32)a0 + 0x70);

    if (v1 != 0) {
        if (v1 != 1) {
            goto default_case;
        }
    } else {
        v0 = D_80126B78[1];
        if (v0 < 0)
            goto end_func;
        if (func_8017267C(&D_80126B58) != 0)
            goto end_func;
    }

    func_8017FE48(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017FE48(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017FE48(a0);
        }

        s0 = s0 + 1;
    } while (s0 < 3);
    goto end_func;

default_case:
    func_8017FE48(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8017FE48(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8017FE48(a0);
        }

        s0 = s0 + 1;
    } while (s0 <= 0);

end_func:
    v0 = rand();
    ((void (*)(s32, s32))func_8012BF4C)((s32)a0, (v0 & 0x1F) | 0x20);
}



extern void func_80149350(s32 arg0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012E544(s32 a0);
extern u8 *func_801290DC(s32 a0, u8 *a1);

void func_8017FE48(void *a0) {

    extern s32 D_80126B58;
    extern u8 D_801202A0[];
    extern u8 D_80188700[];
    s32 t;
    u8 *r;
    u8 *p;
    s32 i;
    s32 o;
    s16 out[4];

    t = *(s16 *)((s32)a0 + 0x70);
    r = &D_80188700[t * 8];
    switch (t) {
    case 0:
        ((void (*)(void *, void *, void *))func_80149350)(&D_80126B58, r, out);
        func_801290DC(0x56, (u8 *)out);
        break;
    case 1:
        o = func_8012E544(0x245);
        if (o == 0) {
            return;
        }
        ((void (*)(void *, void *, void *))func_8012F214)((void *)o, r, out);
        func_801290DC(0x56, (u8 *)out);
        break;
    default:
        p = D_801202A0;
        for (i = 0; i < 0x60; i++) {
            if (*(u16 *)p == *(s16 *)(r + 6)) {
                ((void (*)(void *, void *, void *))func_8012F214)(p, r, out);
                func_801290DC(0x56, (u8 *)out);
            }
            p += 0x10C;
        }
        break;
    }
}



extern void (*D_80188734[])(void);

void func_8017FF34(void *a0) {
    D_80188734[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017FF70 — state entry: init the sub-object at +4/+0x10, bind the
 * primitive at +0x20 to the command list D_80188728 (0x270 / 0x100), paint
 * its RGB (0x40,0x40,0x40) + code 0x9C, OR 0xD0000000 into its tag word,
 * clear the counter at +0x2C, then seed three random fields and bump the
 * state word at +2.
 */

extern void func_800159E4(s32 a0, s32 a1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern int rand(void);

void func_8017FF70(int param_1)
{
    extern unsigned char D_80188728[];
    int p;
    int r1;
    int r2;

    p = *(int *)(param_1 + 0x20);
    ((void (*)(int, int))func_800159E4)(param_1 + 4, param_1 + 0x10);
    ((void (*)(int, int, int, int))func_8001CC3C)(p, (int)D_80188728, 0x270, 0x100);
    *(unsigned char *)(p + 0x27) = 0x9c;
    *(unsigned char *)(p + 0x26) = 0x40;
    *(unsigned char *)(p + 0x25) = 0x40;
    *(unsigned char *)(p + 0x24) = 0x40;
    *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) | 0xd0000000;
    *(int *)(param_1 + 0x2c) = 0;
    *(unsigned short *)(param_1 + 0x30) = (rand() & 3) + 1;
    r1 = rand();
    r2 = rand();
    *(unsigned short *)(p + 0x12) = (r1 & 3) * 0x400 + (r2 & 0xf) * 0x44;
    ((void (*)(int, int))func_80146E90)(param_1, rand() & 0xf);
    *(unsigned short *)(param_1 + 2) = *(unsigned short *)(param_1 + 2) + 1;
}



extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);


void func_80180054(s32 *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    if (func_80146E98((s32)a0) != 0) {
        v1 = 0x7FFFFFFF;
        v0 = *(s32 *)((s32)s1 + 0x4);
        v0 = v0 & v1;
        *(s32 *)((s32)s1 + 0x4) = v0;
        func_80146E90(a0, 0x10);

        v0 = *(u16 *)((s32)a0 + 0x2);
        v0 = v0 + 1;
        *(u16 *)((s32)a0 + 0x2) = v0;
    }
}



/* func_801800C0 — per-frame update for the effect entity that func_8017E8CC
 * initialises (its GPU primitive lives at +0x20).  Advance the spin angle at
 * +0x2C by 0x40, take rsin(angle)/256 as the Z component of a stack vector,
 * rotate that vector by the primitive's own angle at p+0x12, then re-derive
 * the draw position words at +6/+0xA/+0xE, grow the size counter at +0x2E
 * (mirrored into the primitive's w/h at p+0x18/p+0x1A), fade the RGB triple
 * at p+0x24..0x26 by 4 per frame, and retire the entity via func_801292C8
 * once the shared lifetime check func_80146E98 reports done.
 *
 * Matching notes (cookbook §S1/§S4 in gcc-2.7.2-map/sched.md): the three
 * position statements and the +0x2E statement all tie at sched priority 1,
 * so their SOURCE ORDER is the schedule.  The target's order is
 * 0x6, 0xE, 0xA, 0x2E — writing them in field order (0x6, 0xA, 0xE, 0x2E)
 * costs 12 mismatches because the 0x30 load, not the 0x2E load, wins the
 * load-delay filler slot after the first group.  `siz` must be an explicit
 * temporary (a re-read of +0x2E in the p+0x1A statement re-groups the whole
 * block, 26+ mismatches).
 */


extern s32 func_8004787C(s32 a0);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80146E98(s32 a0);
extern void func_801292C8(void);

void func_801800C0(int param_1)
{
    UVec_8017EA1C_801800C0 v;
    int p;
    short ang;
    int siz;
    int wid;
    int col;

    p = *(int *)(param_1 + 0x20);
    ang = *(unsigned short *)(param_1 + 0x2c) + 0x40;
    *(unsigned short *)(param_1 + 0x2c) = ang;
    v.vz = func_8004787C(ang) / 256;
    v.vy = 0;
    v.vx = 0;
    func_800139C8(*(short *)(p + 0x12), &v, &v);

    *(unsigned short *)(param_1 + 6) = *(unsigned short *)(param_1 + 0x12) + v.vx;
    *(unsigned short *)(param_1 + 0xe) = *(unsigned short *)(param_1 + 0x1a) + v.vz;
    *(unsigned short *)(param_1 + 0xa) = *(unsigned short *)(param_1 + 0xa) - *(unsigned short *)(param_1 + 0x30);
    siz = *(unsigned short *)(param_1 + 0x2e) + 0x10;
    *(unsigned short *)(param_1 + 0x2e) = siz;

    wid = *(unsigned short *)(p + 0x1a) + siz;
    *(unsigned short *)(p + 0x1a) = wid;
    *(unsigned short *)(p + 0x18) = wid;

    col = *(unsigned char *)(p + 0x26) - 4;
    *(unsigned char *)(p + 0x26) = col;
    *(unsigned char *)(p + 0x25) = col;
    *(unsigned char *)(p + 0x24) = col;

    if (func_80146E98(param_1) != 0) {
        ((void (*)(int))func_801292C8)(param_1);
    }
}


void func_801801AC(s32 a0) {
    extern M2C_UNK D_8019972C;
    extern s32 D_801997A4;
    s32 *v1;

    func_8012A8B0((u8 *)a0, (s32)&D_8019972C);
    v1 = *(s32 **)(a0 + 0x20);
    *(s32 *)(a0 + 0x94) = 0xF;
    *(s32 *)((s32)v1 + 0x20) = D_801997A4;
    func_8012B23C(a0);
    func_8012AD44((s32 *)a0, 2);
}


extern M2C_UNK D_80199824;
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801804CC(void *a0);

void func_80180208(void *a0) {
    if ((*(u16 *)((u8 *)a0 + 0x86) & 1) != 0) {
        func_801804CC(a0);
    } else {
        func_8012A8B0((u8 *)a0, (s32)&D_80199824);
        *(s32 *)((u8 *)a0 + 0x1C) = 0x60;
        func_8012AD44((s32 *)a0, 3);
    }
}


extern s32 D_8019979C;
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80180274(s32 param_1, u16 param_2)
{
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = D_8019979C;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = param_2;
    func_8012B23C(param_1);
    *(s32 *)(param_1 + 0x1C) = 8;
    *(s16 *)(param_1 + 0x98) = 0;
    func_8012AD44((s32 *)param_1, 4);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012B23C(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);
extern void func_80180530(void *arg0);
extern s32 func_80180C74(s32 a0);
extern void func_80181130(s32 a0, s32 a1);
extern s32 func_80180AF0(s32 a0, s32 a1, s32 *a2);

typedef struct { short a, b, c; } SV3_801802D0;

extern M2C_UNK D_8019A00C;
extern M2C_UNK D_80199AF4;

void func_801802D0(s32 param_1) {
    SV3_801802D0 pos;
    s32 out;
    s32 flag = 0;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 0x34) += 1;
            func_8012A8B0((u8 *)param_1, (s32)&D_8019A00C);
            func_8012B2CC(param_1);
            func_8012B178(param_1, 0xFFF80000);
            *(s32 *)(param_1 + 0x14) = 0xFFF40000;
        }
        func_80181130(param_1, 0);
        break;

    case 1:
        flag = ((s32 (*)(s32))func_8012CBF4)(param_1);
        if (*(s16 *)(param_1 + 0xA) > 0) {
            func_8012C218((void *)param_1);
            return;
        }
        if (func_80180C74(param_1) != 0) {
            *(s32 *)(param_1 + 0x10) = 0;
            *(s32 *)(param_1 + 0x18) = 0;
            *(s32 *)(param_1 + 0x4) = *(s32 *)(param_1 + 0x38);
            *(s32 *)(param_1 + 0xC) = *(s32 *)(param_1 + 0x40);
        }
        if (flag & 0x2000) {
            func_8012B23C(param_1);
            func_8012B2CC(param_1);
            func_8012B178(param_1, 0xFFF20000);
            func_8012A8B0((u8 *)param_1, (s32)&D_80199AF4);
            *(s32 *)(param_1 + 0x1C) = 0x30;
            *(u16 *)(param_1 + 0x34) += 1;
            pos.a = *(s16 *)(param_1 + 0x6);
            pos.b = *(s16 *)(param_1 + 0xA);
            pos.c = *(s16 *)(param_1 + 0xE);
            func_8002D59C(0x7E5, 0, *(u16 *)(param_1 + 0x36));
        }
        func_80181130(param_1, 0);
        break;

    case 2:
        if (func_80180AF0(param_1, 0xFFF20000, &out) == 1) {
            func_8012ADE4((u8 *)param_1);
            flag = 1;
        } else if (func_8012BEE8(param_1) != 0) {
            flag = 1;
        }
        func_80181130(param_1, 2);
        if (flag != 0) {
            func_80180530((void *)param_1);
            func_8002D59C(4, 0x7E5, *(u16 *)(param_1 + 0x36));
        }
        break;
    }
}


void func_801804CC(void *arg0) {
    s32 *s0 = (s32 *)arg0;

    extern M2C_UNK D_80199904;
    func_8012A8B0((u8 *)arg0, (s32)&D_80199904);
    *(u16 *)((u8 *)s0 + 0x102) = 8;
    *(u16 *)((u8 *)s0 + 0x104) = 3;
    *(u16 *)((u8 *)s0 + 0x106) = (rand() & 0x20) - 0x10;
    s0[7] = 0x60;
    func_8012AD44(s0, 5);
}




extern void func_8012A8B0(u8*, s32);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80180530(void *arg0) {

    extern M2C_UNK D_80199E1C;
    ((void (*)(s32, s32))func_8012A8B0)((s32)arg0, (s32)&D_80199E1C);
    ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x7);
}


typedef struct {
    u8  pad0[0x2];
    u16 unk2;
    u8  pad2[0x1C];
    s32 *unk20;
    u8  pad3[0xDA];
    u16 unkFE;
    u16 unk100;
} S_8018056C;

extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_80199644;

void func_8018056C(S_8018056C *s0) {
    s0->unk100 = 0;
    s0->unkFE = ((u16 *)s0->unk20)[9] + 0x200;
    if (s0->unk2 != 1) {
        func_8012A8B0((u8 *)s0, (s32)&D_80199644);
    }
    func_8012AD44((s32 *)s0, 0x8);
}


extern M2C_UNK D_80199824;
extern M2C_UNK D_8019972C;
extern s32 D_801997A4;

void func_801805D0(void *arg0) {
    void *s0 = arg0;
    void *a1 = *(void **)((u8 *)s0 + 0x20);

    if (*(s16 *)((u8 *)s0 + 0xFE) == *(s16 *)((u8 *)a1 + 0x12)) {
        s32 buf[2];

        if (func_80180BA4(s0, buf) == 1) {
            if ((*(u16 *)((u8 *)s0 + 0x86) & 1) != 0) {
                goto L_C0;
            }
            if ((rand() & 1) == 0) {
                goto L_FC;
            }
            if ((*(u16 *)((u8 *)s0 + 0x86) & 1) == 0) {
                goto L_D0;
            }
L_C0:
            func_801804CC(s0);
            goto tail;
L_D0:
            func_8012A8B0((u8 *)s0, (s32)&D_80199824);
            *(s32 *)((u8 *)s0 + 0x1C) = 0x60;
            func_8012AD44((s32 *)s0, 3);
            goto tail;
L_FC:
            func_8012A8B0((u8 *)s0, (s32)&D_8019972C);
            *(s32 *)((u8 *)s0 + 0x94) = 0xF;
            *(s32 *)(*(u8 **)((u8 *)s0 + 0x20) + 0x20) = D_801997A4;
            func_8012B23C((s32)s0);
            func_8012AD44((s32 *)s0, 2);
        } else {
            *(u16 *)((u8 *)s0 + 0xFE) += 0x200;
        }

tail:
        *(u16 *)((u8 *)s0 + 0x100) += 1;
    } else {
        func_80180F74(*(s16 *)((u8 *)s0 + 0xFE), (u16 *)((u8 *)a1 + 0x12), 0x20);
    }
}


extern M2C_UNK D_80199644;
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018070C(void *arg0) {
    s32 *s0 = (s32 *)arg0;

    func_8012A8B0((u8 *)arg0, (s32)&D_80199644);
    s0[7] = 0x40;
    func_8012AD44(s0, 0x9);
}


typedef struct { s32 w[8]; } MTX8L_80180750;

s32 func_80180750(s32 a0)
{
    extern MTX8L_80180750 aD800AE620 __asm__("D_800AE620");
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_80020F34(s32 a0, s32 a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 func_8012C588(s32 a0, s32 a1);

    s16 *s1;
    s16 rv[4];
    s16 vec[4];
    MTX8L_80180750 m;
    s16 out[4];

    s1 = (s16 *)func_8012C588(0x239, a0);
    if (s1 != 0) {
        m = aD800AE620;

        vec[2] = 0x1800;
        vec[1] = 0x1800;
        vec[0] = 0x1800;

        RotMatrixY(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), &m);

        func_80020F34((s32)&m, (s32)vec);

        func_8004914C(&m);

        func_800491AC((void *)(*(s32 *)(a0 + 0x20) + 0x34));

        rv[1] = -0x200;
        rv[0] = 0;
        rv[2] = -0x48;
        RotTransSV(rv, rv, out);

        *(u16 *)((u8 *)s1 + 0x6) = *(u16 *)&rv[0];
        *(u16 *)((u8 *)s1 + 0xA) = *(u16 *)&rv[1];
        *(u16 *)((u8 *)s1 + 0xE) = *(u16 *)&rv[2];

        *(s32 *)(a0 + 0xCC) = (s32)s1;
    }
    return (s32)s1;
}


extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801999AC;

void func_80180878(s32 arg0) {
    ((void (*)(s32, s32))func_8012A8B0)(arg0, &D_801999AC);
    ((void (*)(s32, s32))func_8012AD44)(arg0, 0xA);
}


extern void (*D_80192E38[])(void);

void func_801808B4(s32 arg0) {
    s32 *s0 = (s32 *)arg0;
    s32 v1;

    D_80192E38[*(u16 *)((u8 *)s0 + 2)]();

    if ((*(u16 *)s0 == 0x1FC) && (*(s16 *)((u8 *)s0 + 0xAA) == 0)) {
        v1 = *(s32 *)((u8 *)s0 + 0x20);
        *(u16 *)(v1 + 0x2C) |= 0x10;
        v1 = *(s32 *)((u8 *)s0 + 0x20);
        *(u16 *)(v1 + 0x18) = *(u16 *)(v1 + 0x1A) = *(u16 *)(v1 + 0x1C) = 0x1800;
    }
}


void func_80180948(s32 arg0) {
    extern void func_80181248(s32 a0, s32 a1);
    s32 pe;

    if (*(u8 *)(arg0 + 0xC2) == 0x2) {
        *(s16 *)(arg0 + 0x52) = -0x18;
    }
    pe = func_80180C74(arg0);
    if (pe != 0) {
        *(s32 *)(arg0 + 0x10) = 0;
        *(s32 *)(arg0 + 0x18) = 0;
        *(s32 *)(arg0 + 0x04) = *(s32 *)(arg0 + 0x38);
        *(s32 *)(arg0 + 0x0C) = *(s32 *)(arg0 + 0x40);
        func_80181248(arg0, pe);
    }
}


extern M2C_UNK D_80199BA4;
extern void func_8002AC00(s32 arg0);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_80130088(void *a0);
extern void func_80131B14();

void func_801809B0(void *a0) {
    s32 s0 = (s32)a0;
    func_80131B14();
    *(u8 *)((s32)a0 + 0xC2) = 0;
    *(u8 *)((s32)a0 + 0xC3) = 0;
    *(u16 *)((s32)a0 + 0x98) = 0;
    func_8012B23C(s0);
    func_8012B2CC(s0);
    func_8012B178(s0, 0x00080000);
    func_8012A8B0((u8 *)s0, (s32)&D_80199BA4);
    if (*(s16 *)((s32)a0 + 0x76) <= 0) {
        func_80130088((void *)a0);
        func_8002AC00(0x13);
    }
}


void func_80180A30(s32 a0) {
    extern void func_8012CBF4(s32 a0);
    extern s32 func_80180C74(s32 arg0);
    extern void func_80181248(s32 a0, s32 a1);
    extern void func_8012ADE4(u8 *a0);
    extern void func_801319E0(s32 a0);
    extern void func_80131E00();
    extern void func_80131C78(s32 a0);
    register s32 s0 __asm__("$16") = a0;
    s32 s1;
    s32 v0;

    s1 = ((s32 (*)(s32))func_8012CBF4)(s0);
    if ((s1 & 0xFF) == 0x1A) {
        func_801319E0(s0);
        return;
    }

    v0 = func_80180C74(s0);
    if (v0 != 0) {
        func_80181248(s0, v0);
        func_8012ADE4((u8 *)s0);
    } else if (s1 != 0x2000) {
        func_8012ADE4((u8 *)s0);
    }

    if (*(s16 *)(s0 + 0x98) == 0) {
        if (*(s16 *)(s0 + 0x76) <= 0) {
            func_80131E00(s0, 6);
        } else {
            func_80131C78(s0);
        }
    }
}


extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32);
extern s32 func_80180C74(s32 arg0);
extern void func_8012ADE4(u8 *a0);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_80199644;

s32 func_80180AF0(s32 a0, s32 a1, s32 *a2) {
    s32 cba4;

    func_8012B2CC(a0);
    func_8012B178(a0, a1);
    cba4 = ((s32 (*)(s32))func_8012CBA4)(a0);
    if ((*a2 = func_80180C74(a0)) != 0) goto fail;
    if (cba4 == 0x2000) goto zeroret;
fail:
    func_8012ADE4((u8 *)a0);
    *(s32 *)(a0 + 0x1C) = 8;
    func_8012A8B0((u8 *)a0, (s32)&D_80199644);
    func_8012B23C(a0);
    func_8012AD44((s32 *)a0, 1);
    return 1;
zeroret:
    return 0;
}


extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32);
extern s32 func_80180C74(s32 arg0);
extern void func_8012ADE4(u8 *a0);

s32 func_80180BA4(void *a0, void *a1) {
    s32 arr[3];
    s32 cba4;

    arr[0] = *(s32 *)((u8 *)a0 + 0x10);
    arr[1] = *(s32 *)((u8 *)a0 + 0x14);
    arr[2] = *(s32 *)((u8 *)a0 + 0x18);
    func_8012B2CC((s32)a0);
    func_8012B178((s32)a0, 0xFFF10000);
    cba4 = ((s32 (*)(s32))func_8012CBA4)((s32)a0);
    *(s32 *)((u8 *)a0 + 0x10) = arr[0];
    *(s32 *)((u8 *)a0 + 0x14) = arr[1];
    *(s32 *)((u8 *)a0 + 0x18) = arr[2];
    *(s32 *)a1 = func_80180C74((s32)a0);
    func_8012ADE4((u8 *)a0);
    *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x2C) &= 0xFFFE;
    if (*(s32 *)a1 != 0) {
        goto ret0;
    }
    return cba4 == 0x2000;
ret0:
    return 0;
}


extern u8 D_801202A0[];
extern s32 func_8012BE98(s32, u16*);

s32 func_80180C74(s32 arg0) {
    extern u8 D_801202A0[];
    register s32 zr __asm__("$0");
    u8 *pe; 
    s32 i;
    u16 buf[3];
    s32 thresh;
    s32 t;
    s32 d;
    s32 f20;
    u16 state;

    pe = D_801202A0;
    i = 0;
    do {
        if ((s32) pe == arg0) {
            goto next;
        }
        state = *(u16 *) pe;
        if (state == 0x1FC) {
            goto do_1fc;
        }
        if (state == 0x239) {
            goto do_239;
        }
        goto next;

    do_1fc:
        buf[0] = *(u16 *) (pe + 6);
        buf[1] = 0;
        buf[2] = *(u16 *) (pe + 0xE);
        if (((s32 (*)(s32, u16 *)) func_8012BE98)(arg0, buf) < 0x900) {
            return (s32) pe;
        }
        goto next;

    do_239:
        f20 = *(s32 *) (pe + 0x20);
        d = *(s16 *) (pe + 6) - *(s16 *) (arg0 + 6);
        t = (*(s16 *) (f20 + 0x18) * 9) >> 9;
        if (d < 0) {
            d = -d;
        }
        thresh = t + zr;
        if (thresh < d) {
            goto next;
        }
        d = *(s16 *) (pe + 0xE) - *(s16 *) (arg0 + 0xE);
        if (d < 0) {
            d = -d;
        }
        if (thresh < d) {
            goto next;
        }
        return (s32) pe;

    next:
        i = i + 1;
        pe = pe + 0x10C;
    } while (i <= 0x5F);
    return 0;
}


extern s32 func_80132E6C(s16 *a0);
extern s32 func_8012B864(s32 a0);

s32 func_80180D94(s32 a0) {
    s16 ret;
    s16 result;
    s16 val;
    s16 t;

    if (func_80132E6C((s16 *)a0) > 0x23FFF) {
        return 0;
    }
    ret = func_8012B864(a0);
    val = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    result = ret;
    t = ret - (val & 0xFFF);
    if (t < 0) {
        t = -t;
    }
    if (t < 0x180) {
        if (ret == 0) {
            result = ret + 1;
        }
        return result;
    }
    return 0;
}


extern u8 D_80195254[0x20];
extern s32 D_801B3A80[8];
extern s32 D_801B3A90;
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s32 func_8012C588(s32 a0, s32 a1);

void func_80180E30(s32 param_1) {
    s32 i;

    if ((*(u16 *)(param_1 + 0x86) & 1) == 0) {
        if (*(s16 *)(param_1 + 0x76) < 0xB5) {
            if (((s32 (*)(s32, s32))func_8012C588)(0x22D, param_1) != 0) {
                *(u16 *)(param_1 + 0x86) |= 1;
                for (i = 0; i < 0x20; i += 4) {
                    *(s32 *)((s32)D_801B3A80 + i) = *(s32 *)((s32)D_80195254 + i);
                }
                *(s32 *)D_801B3A80 = 0x1000000;
                D_801B3A90 = 0x1000000;
                *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x24) = (s32)D_801B3A80;
                ((void (*)(s32, s32))func_8002D4C8)(0x83B, 0);
            }
        }
    }
}


extern M2C_UNK D_80199644;
extern M2C_UNK D_80199F24;
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B23C(s32 a0);

void func_80180EEC(void *arg0) {
    *(u16 *)((u8 *)arg0 + 0x5C) = 0x8A10;
    *(u16 *)((u8 *)arg0 + 0x52) = 0;
    if ((*(s32 *)((u8 *)arg0 + 0xC4) & 4) != 0) {
        func_8012A8B0((u8 *)arg0, (s32)&D_80199F24);
        func_8012AD44((s32 *)arg0, 6);
    } else {
        *(s32 *)((u8 *)arg0 + 0x1C) = 8;
        func_8012A8B0((u8 *)arg0, (s32)&D_80199644);
        func_8012B23C((s32)arg0);
        func_8012AD44((s32 *)arg0, 1);
    }
}



void func_80180F74(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

extern s16 D_80192E64;
extern s16 D_80192E66;
extern s16 D_80192E68;

void func_80180FF8(void *param_1) {
    s16 pkt[10];
    s32 vec[3];
    s32 out[3];
    s32 x;
    s32 y;
    s32 z;
    s32 ret;
    s32 p;
    s32 q;
    s32 p0;

    vec[0] = D_80192E64 << 8;
    vec[1] = D_80192E66 << 8;
    vec[2] = D_80192E68 << 8;
    p0 = *(s32 *)(param_1 + 0x20);
    func_800484EC(p0 + 0x34, (s32)vec, (s32)out);

    out[0] += *(s16 *)(param_1 + 0x6) << 8;
    out[1] += *(s16 *)(param_1 + 0xA) << 8;
    out[2] += *(s16 *)(param_1 + 0xE) << 8;

    x = out[0];
    if (x < 0) {
        x += 0xFF;
    }
    pkt[0] = x >> 8;

    y = out[1];
    if (y < 0) {
        y += 0xFF;
    }
    pkt[1] = y >> 8;

    z = out[2];
    if (z < 0) {
        z += 0xFF;
    }
    pkt[2] = z >> 8;

    pkt[3] = 0x20;
    pkt[4] = 2;
    pkt[5] = 0;
    *(s32 *)&pkt[8] = 0;
    pkt[7] = 0;

    ret = func_8012C51C(pkt, param_1);
    if (ret != 0) {
        p = *(s32 *)(param_1 + 0x20);
        q = *(s32 *)(ret + 0x20);
        *(u16 *)(q + 0x12) = *(u16 *)(p + 0x12);
        func_8012B2CC(ret);
        func_8002D4C8(0x83A, 0);
    }
}


extern u8 D_80192E6C[];
extern u8 D_80192E6E[];
extern u8 D_80192E70[];
extern s16 D_80126B98;
s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

void func_80181130(s32 a0, s32 a1) {
    u16 buf[4];

    if ((*(u16 *)(a0 + 0x86) & 1) == 0) {
        s32 off = a1 << 3;
        buf[0] = *(u16 *)(D_80192E6C + off);
        buf[1] = *(u16 *)(D_80192E6E + off);
        buf[2] = *(u16 *)(D_80192E70 + off) - 0x14;
        if (func_8012DEB8(a0, (s32)(D_80192E6C + off), (s32)buf) != 0) {
            D_80126B98 = 0x14;
        }
    }
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8002AC00(int arg0);

void func_801811BC(void) {
    func_8002D4C8(0x853, 0);
    func_8002AC00(0x13);
}


extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80192E84;

void func_801811E8(u8 *a0)
{
    u16 buf[4];

    if (*(u16 *)a0 != 0x1FC) {
        return;
    }
    buf[0] = *(u16 *)(a0 + 6);
    buf[1] = *(u16 *)(a0 + 0xA) - 0x20;
    buf[2] = *(u16 *)(a0 + 0xE);
    buf[3] = 0x1800;
    func_801437D8((s32)(a0 + 0x102), (s32)buf, (s32)&D_80192E84, 0);
}


extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_80181248(s32 a0, s32 a1) {
    if ((*(u16 *)(a1 + 0x5C) & 0x8000) != 0) {
        if (*(u16 *)(a1 + 0x5E) != 0x1D) {
            *(u16 *)(a1 + 0x5C) = *(u16 *)(a1 + 0x5C) | 1;
            *(u16 *)(a1 + 0x60) = 0xa;
            *(u16 *)(a1 + 0x62) = func_8012B6D4((s16 *)(a1 + 4), (s16 *)(a0 + 4));
            *(u16 *)(a1 + 0x5E) = 0x1D;
        }
    }
}


extern s32 D_80195264;
extern s32 D_8019979C;
extern s32 D_801B3AA0[4];
extern s32 D_801B3AB0[3];
extern s32 D_801B3ABC;
extern s32 func_80132EF4(s32 a0, s32 a1);
extern u8 D_80195254[0x20];
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_801812B8(s32 param_1) {
    s32 iVar1;
    s32 i;
    s32 q;
    s32 fill;
    u16 v1;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }

    ((void (*)(s32, void *))func_8001C214)(iVar1, D_80195254);

    fill = 0x01000000;
    for (i = 0x18; i >= 0; i -= 4) {
        *(s32 *)((u8 *)D_801B3AA0 + i) = fill;
    }

    D_801B3ABC = 0;
    D_801B3AA0[0] = *(s32 *)D_80195254;
    D_801B3AB0[0] = D_80195264;

    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x24) = (s32)D_801B3AA0;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = D_8019979C;

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
    func_8012B23C(param_1);
    func_8012B2CC(param_1);
    func_8012B178(param_1, 0x00080000);

    v1 = *(u16 *)(param_1 + 0x2) + 1;
    *(s32 *)(param_1 + 0x14) = 0xFFE40000;
    *(u16 *)(param_1 + 0xFE) = *(u16 *)(param_1 + 0xA) + 0x30;
    *(u16 *)(param_1 + 0x2) = v1;
    q = func_80132EF4(param_1, 0x23);
    if (q != 0) {
        *(u16 *)(q + 0x34) = 0x2001;
        *(u16 *)(q + 0xA) = *(u16 *)(q + 0xA) - 0x38;
    }
}



extern void (*D_80192E8C[])(void);

void func_801813F0(void *a0) {
    D_80192E8C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012B030(u8 *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern u8 D_80192D8C[];
extern u8 D_80192DC0[];
extern u8 D_80195254[0x20];
extern u8 D_801B3A60[0x20];
extern void func_801801AC(s32);
extern void func_80180208(void *a0);
extern void func_8018070C(void *arg0);

void func_8018142C(void *arg0) {
    extern u8 D_80192D8C[];
    extern u8 D_80195254[0x20];
    extern u8 D_801B3A60[0x20];
    extern u8 D_80192DC0[];

    s32 i;
    s32 p20;

    if (func_8012C354((s32)arg0, (s32)D_80192D8C) != 0) {
        for (i = 0; i < 0x20; i += 4) {
            *(s32 *)((u8 *)D_801B3A60 + i) = *(s32 *)((u8 *)D_80195254 + i);
        }

        *(s32 *)((u8 *)D_801B3A60 + 0x14) = 0x1000000;
        p20 = *(s32 *)((u8 *)arg0 + 0x20);
        *(s32 *)(p20 + 0x24) = (s32)D_801B3A60;

        *(u8 *)((u8 *)arg0 + 0xC0) = 1;
        *(s32 *)((u8 *)arg0 + 0xB4) = -0x801;
        *(s32 *)((u8 *)arg0 + 0xBC) = (s32)D_80192DC0;

        func_80143970((s32)arg0);
        func_8012B030((u8 *)arg0);

        p20 = *(s32 *)((u8 *)arg0 + 0x20);
        *(s16 *)(p20 + 0x1c) = 0x1800;
        *(s16 *)(p20 + 0x1a) = 0x1800;
        *(s16 *)(p20 + 0x18) = 0x1800;

        p20 = *(s32 *)((u8 *)arg0 + 0x20);
        *(u16 *)(p20 + 0x2c) |= 0x10;

        if (*(s16 *)((u8 *)arg0 + 0x70) != 0) {
            func_8018070C(arg0);
        } else if (rand() & 1) {
            ((void (*)(void *))func_801801AC)(arg0);
        } else {
            func_80180208(arg0);
        }
    }
}




extern s32 func_8012BEE8(s32 a0);
extern s32 func_80180BA4(void *a0, void *a1);
extern void func_8018056C(S_8018056C *s0);
extern void func_80181130(s32 a0, s32 a1);

void func_80181548(s32 a0) {
    s32 buf[2];

    if (func_8012BEE8(a0) != 0) {
        func_80180BA4((void *)a0, buf);
        func_8018056C((S_8018056C *)a0);
    }
    func_80181130(a0, 0);
}


extern s32 func_8012BEE8(s32 arg);
extern void func_80180274(s32 param_1, u16 param_2);
extern s32 func_80180BA4(void *a0, void *a1);
extern void func_80181130(s32, s32);

void func_80181594(s32 arg0) {
    extern s32 func_80180D94();
    extern void func_80180208();
    s32 buf[2];
    s16 t;
    u16 state;

    state = *(u16 *)(arg0 + 0x34);
    switch (state) {
    case 0:
        if (*(s32 *)(arg0 + 0x94) == 0xE && (*(u16 *)(arg0 + 0x72) & 0x400) == 0) {
            *(u16 *)(arg0 + 0x98) = 0;
            *(s32 *)(arg0 + 0x1C) = 8;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        } else {
            t = func_80180D94(arg0);
            if (t != 0 && func_80180BA4(arg0, buf) != 0) {
                ((void (*)(s32, s32))func_80180274)(arg0, t);
            }
        }
        break;
    case 1:
        if (func_8012BEE8(arg0) != 0) {
            func_80180208(arg0);
        }
        break;
    }
    ((s32 (*)(s32, s32))func_80181130)(arg0, 0);
}


extern s32 D_80199644;
extern s32 func_80180AF0(s32 a0, s32 a1, s32 *a2);
extern void func_8012ADE4(u8 *a0);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80180D94(s32 a0);
extern void func_80180274(s32, u16);
extern void func_80181130(s32 a0, s32 a1);

void func_80181678(s32 a0) {
    s32 local;
    s32 v0;

    v0 = func_80180AF0(a0, 0xFFFB0000, &local);
    if (v0 == 1) {
        func_8012ADE4((u8 *)a0);
        *(s32 *)(a0 + 0x1C) = 8;
        func_8012A8B0((u8 *)a0, (s32)&D_80199644);
        func_8012B23C(a0);
        func_8012AD44((s32 *)a0, 1);
    } else if (func_8012BEE8(a0) != 0) {
        *(s32 *)(a0 + 0x1C) = 8;
        func_8012A8B0((u8 *)a0, (s32)&D_80199644);
        func_8012B23C(a0);
        func_8012AD44((s32 *)a0, 1);
    } else if ((*(u16 *)(a0 + 0x86) & 1) == 0) {
        s16 r = (s16)func_80180D94(a0);
        if (r != 0) {
            ((void (*)(s32, s16))func_80180274)(a0, r);
        }
    }
    func_80181130(a0, 1);
}


extern M2C_UNK D_80199644;
extern s32 func_8012BEE8(s32 arg);
extern s32 func_80180AF0();
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012ADE4(u8 *a0);
extern void func_8012B23C(s32 a0);
extern void func_80180FF8(void *a0);

void func_80181744(s32 a0) {
    s32 local[4]; 
    register s32 v0 __asm__("$2");
    s32 sum;

    v0 = func_80180AF0(a0, 0xFFFB0000, local);
    if (v0 == 1) {
        func_8012ADE4((u8 *)a0);
        *(s32 *)(a0 + 0x1C) = 8;
        func_8012A8B0((u8 *)a0, (s32)&D_80199644);
        func_8012B23C(a0);
        func_8012AD44((s32 *)a0, 1);
    } else {
        v0 = *(s16 *)(a0 + 0x102);
        if (v0 != 0) {
            
            register s32 tmp __asm__("$3");
            tmp = v0;
            __asm__ __volatile__("" : "=r"(tmp) : "0"(tmp) : "memory");
            v0 = tmp - 1;
        } else {
            s16 cnt;

            if (*(s16 *)(a0 + 0xAA) == 0) {
                func_80180FF8((void *)a0);
            }
            cnt = *(u16 *)(a0 + 0x104) - 1;
            *(s16 *)(a0 + 0x104) = cnt;
            if (cnt != 0) {
                v0 = 4;
            } else {
                *(s16 *)(a0 + 0x104) = 3;
                v0 = 0x20;
            }
        }
        *(s16 *)(a0 + 0x102) = v0;

        v0 = *(s32 *)(a0 + 0x20);
        sum = *(u16 *)(v0 + 0x12) + *(u16 *)(a0 + 0x106);
        *(u16 *)(v0 + 0x12) = sum;
        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x80;
            v0 = rand();
            *(s16 *)(a0 + 0x106) = (v0 & 0x20) - 0x10;
        }
    }
}


extern M2C_UNK D_80199644;
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B23C(s32 a0);

void func_80181850(s32 arg0) {
    if (*(s16 *)(arg0 + 0x98) == 0) {
        *(s32 *)(arg0 + 0x1C) = 8;
        func_8012A8B0((u8 *)arg0, (s32)&D_80199644);
        func_8012B23C(arg0);
        func_8012AD44((s32 *)arg0, 1);
    }
}


extern M2C_UNK D_80199644;
extern M2C_UNK D_8019972C;
extern s32 D_801997A4;
extern s32 func_80180BA4(void *a0, void *a1);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B23C(s32 a0);

void func_801818A8(void *arg0) {
    void *s0 = arg0;
    s32 buf[2];

    if (*(s16 *)((u8 *)s0 + 0x98) != 0) {
        return;
    }
    if ((*(u16 *)((u8 *)s0 + 0x86) & 1) == 0 && func_80180BA4(s0, buf) != 0) {
        func_8012A8B0((u8 *)s0, (s32)&D_8019972C);
        *(s32 *)((u8 *)s0 + 0x94) = 0xF;
        *(s32 *)(*(u8 **)((u8 *)s0 + 0x20) + 0x20) = D_801997A4;
        func_8012B23C((s32)s0);
        func_8012AD44((s32 *)s0, 2);
    } else {
        *(s32 *)((u8 *)s0 + 0x1C) = 8;
        func_8012A8B0((u8 *)s0, (s32)&D_80199644);
        func_8012B23C((s32)s0);
        func_8012AD44((s32 *)s0, 1);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80180750(s32 a0);
extern void func_80180878(s32 a0);
extern void func_80181130(s32, s32);

void func_80181968(s32 arg0) {
    s32 state;

    if (*(s16 *)(arg0 + 0xAA) == 0) {
        switch (*(u16 *)(arg0 + 0x34)) {
        case 0:
            if (func_8012BEE8(arg0) != 0) {
                if (func_80180750(arg0) != 0) {
                    *(s32 *)(arg0 + 0x1C) = 0x30;
                    *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
                } else {
                    *(s32 *)(arg0 + 0x1C) = 0x10;
                }
            }
            break;
        case 1:
            if (func_8012BEE8(arg0) != 0) {
                func_80180878(arg0);
            }
            break;
        }
        ((s32 (*)(s32, s32))func_80181130)(arg0, 0);
    }
}


extern M2C_UNK D_80199644;
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80181130(s32 a0, s32 a1);
extern void func_80181BD4(s32 a0);

void func_80181A20(void *arg0) {
    u16 v1;

    v1 = *(u16 *)((s32)arg0 + 0x34);

    if (v1 == 0) {
        goto case0;
    }

    if (v1 == 1) {
        goto case1;
    }

    goto tail;

case0:
    if (*(s32 *)((s32)arg0 + 0x94) == 0x18) {
        func_80181BD4(*(s32 *)((s32)arg0 + 0xCC));
        *(u16 *)((s32)arg0 + 0x34) += 1;
    }
    goto tail;

case1:
    if (*(s16 *)((s32)arg0 + 0x98) == 0) {
        func_8012A8B0((u8 *)arg0, (s32)&D_80199644);
        *(s32 *)((s32)arg0 + 0x1C) = 0x40;
        func_8012AD44((s32 *)arg0, 9);
    }

tail:
    func_80181130((s32)arg0, 0);
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80181AD4(s32 param_1) {
    s32 s0;
    s32 ta;

    s0 = param_1;
    func_8012AD80(s0);
    ta = *(s16 *)(s0 + 0xA);
    __asm__ __volatile__("" : "=r"(ta) : "0"(ta));
    if (*(s16 *)(s0 + 0xFE) < ta || ta > 0) {
        func_8012C218((void *)s0);
    } else {
        (*(s32 *)(s0 + 0x1C))++;
        if ((*(s32 *)(s0 + 0x1C) & 3) == 0) {
            s32 p = func_80132EF4(s0, 0x22);
            if (p != 0) {
                *(u16 *)(p + 0x34) = 0x1000;
                *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) - 0x28;
            }
        }
    }
}


extern void func_8012B23C(s32 arg);
    extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80181B6C(void *a0) {
        func_8012B23C((s32)a0);
        ((s32 (*)(s32, s32))func_8012AD44)((s32)a0, 1);
    }


extern void func_8012B21C(void *a0);
    extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80181BA0(s32 param_1) {
        ((void (*)(s32))func_8012B21C)(param_1);
        ((void (*)(s32, s32))func_8012AD44)(param_1, 2);
    }


typedef struct { s32 w[8]; } MTX8L_80181BD4;

void func_80181BD4(s32 a0)
{
    extern MTX8L_80181BD4 aD800AE620 __asm__("D_800AE620");
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    MTX8L_80181BD4 m;
    s32 vel[3];

    m = aD800AE620;
    vel[1] = 0;
    vel[0] = 0;
    vel[2] = 0xFFF20000;
    RotMatrixY(*(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12), &m);
    func_800484EC((s32)&m, (s32)&vel[0], a0 + 0x10);
    func_8002D4C8(0xB3F, 0);
    func_8012AD44((s32 *)a0, 3);
}


extern s32 D_80192E94;
extern void (*D_80192EA4[])(void);
extern void func_8012E014(void *a0);
extern void func_80182014(s32 a0, s32 a1);

void func_80181C9C(void *a0) {
    D_80192EA4[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        if (*(u8 *)((s32)a0 + 0x74) != 0) {
            func_8012E014(a0);
            func_80182014((s32)a0, (s32)&D_80192E94);
        }
    }
}


typedef struct { s32 m[5]; s32 t[3]; } MtxW;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0_8017F19C_8018259C; /* 0x20 bytes, align 4 */


s32 func_80181D1C(s32 arg0) {
    extern s32 D_80126B58;
    extern u16 D_80126B62;
    s32 *base = &D_80126B58;
    s32 t;
    s32 r;
    register s32 rr asm("$3");
    register s32 z asm("$2");

    if (*(u8 *)(arg0 + 0x74) != 0) {
        asm volatile("");
        return 0;
    }
    t = D_80126B62 - 0x20;
    r = func_80181E90((s16 *)arg0, (s16 *)(base + 1), 0x48);
    rr = r;
    asm("" :: "r"(rr));
    if (rr == 0) {
        return 0;
    }
    z = 0;
    asm("" :: "r"(z));
    if (*(s16 *)(arg0 + 0xA) < (s16)t) {
        return z;
    }
    return *(s16 *)(arg0 + 0xA) - 0x48 <= (s16)t;
}


extern s32 func_80181E90();

s32 func_80181DAC(s32 arg0) {
    extern u8 D_801202A0[];
    register s32 zr __asm__("$0");
    u8 *pe;
    u8 *ps;
    s16 *ca;
    s16 *cb;
    u16 state;
    u16 t;
    s32 count;

    pe = D_801202A0;
    count = 0;
    ps = pe + 4;
    do {
        if ((s32)pe == arg0) {
            goto next;
        }
        state = *(u16 *)pe;
        ca = (s16 *)((s32)arg0 + zr);
        if (state == 0x1FC) {
            goto b1fc;
        }
        cb = (s16 *)((s32)ps + zr);
        if (state == 0x239) {
            goto b239;
        }
        goto next;

    b1fc:
        cb = (s16 *)((s32)ps + zr);
        t = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) * 9u) >> 9;
        goto call;

    b239:
        t = (u32)(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + *(s16 *)(*(s32 *)(ps + 0x1C) + 0x18)) >> 6;
        /* fall through */
    call:
        if (func_80181E90(ca, cb, t) == 0) {
            goto next;
        }
        __asm__ __volatile__("" :: "r"(pe));
        return (s32)pe;

    next:
        count++;
        ps += 0x10C;
        pe += 0x10C;
    } while (count < 0x60);
    return 0;
}




s32 func_80181E90(a0, a1, a2)
s16 *a0;
s16 *a1;
s32 a2;
{
    s32 d;

    d = a1[1] - a0[3];
    if (d < 0) d = -d;
    if (d > (a2 & 0xFFFF)) return 0;
    d = a1[5] - a0[7];
    if (d < 0) d = -d;
    return d <= (a2 & 0xFFFF);
}


typedef struct { s32 w[8]; } Blk20_80181EE8;
typedef struct { s16 vx, vy, vz, pad; } Svec_80181EE8;

extern Blk20_80181EE8 D_800AE620;
extern s32 func_8012B8A4(s16 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u8 D_801152A8[];

void func_80181EE8(s32 param_1)
{
    Svec_80181EE8 out;
    Svec_80181EE8 sv;
    Blk20_80181EE8 m;
    s16 r;
    s32 t;

    m = D_800AE620;
    t = (*(s16 *)(*(u32 *)(param_1 + 0x20) + 0x18) * 9) >> 9;
    sv.vx = sv.vy = 0;
    sv.vz = -t;
    r = func_8012B8A4((s16 *)param_1);
    RotMatrixY(r, &m);
    ApplyMatrixSV(&m, &sv, &out);
    out.vx += *(u16 *)(param_1 + 6);
    out.vy += *(u16 *)(param_1 + 0xA) - t;
    out.vz += *(u16 *)(param_1 + 0xE);
    func_8012F568(1, 0x4002, 0, 0x14, (s32)&out, (s32)D_801152A8);
}


extern s32 D_80126B58;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

void func_80182014(s32 arg0, s32 arg1) {
    u16 w5e;
    u16 p6;
    u16 w66;
    u16 pE;
    s16 x;
    s16 y;
    s16 z;
    s16 lim;
    s32 wide;
    s16 t1n;
    s16 a3n;
    register s32 d __asm__("6");
    register s32 t1 __asm__("9");
    register s32 a3 __asm__("7");

    if (*(u16 *)&D_80126B58 == 0x1A) {
        return;
    }
    w5e = D_80126B5E;
    p6 = *(u16 *)(arg0 + 6);
    d = w5e - p6;
    t1 = d;
    if ((s16)d < 0) {
        t1 = -d;
    }
    w66 = D_80126B66;
    pE = *(u16 *)(arg0 + 0xE);
    d = w66 - pE;
    a3 = d;
    if ((s16)d < 0) {
        a3 = -d;
    }
    x = *(s16 *)(arg0 + 0xA);
    y = *(s16 *)(arg1 + 8);
    lim = *(s16 *)&D_80126B62;
    if (lim < x + y) {
        return;
    }
    z = *(s16 *)(arg1 + 0xA);
    if (x + z < lim) {
        return;
    }
    wide = t1 << 16;
    t1 = wide >> 16;
    if (t1 >= 0x49) {
        return;
    }
    wide = a3 << 16;
    a3 = wide >> 16;
    if (a3 >= 0x49) {
        return;
    }
    if (lim < x + ((y + z) >> 1)) {
        D_80126B62 = x + y - 1;
        return;
    }
    t1n = t1;
    a3n = a3;
    if (t1n < a3n) {
        if ((s16)w66 > (s16)pE) {
            D_80126B66 = pE + 0x49;
        } else {
            D_80126B66 = pE - 0x49;
        }
    } else {
        if ((s16)w5e > (s16)p6) {
            D_80126B5E = p6 + 0x49;
        } else {
            D_80126B5E = p6 - 0x49;
        }
    }
}


void func_80182170(s32 a0, s32 a1)
{
    s16 *s0 = (s16 *)a1;
    u16 flags;

    flags = *(u16 *)(s0 + 0x2E);
    if ((flags & 0x8000) != 0 && *(u16 *)(s0 + 0x2F) != 0x1D) {
        *(u16 *)(s0 + 0x2E) = flags | 1;
        *(u16 *)(s0 + 0x30) = 0x14;
        *(u16 *)(s0 + 0x31) = func_8012B6D4(s0 + 2, (s16 *)a0 + 2);
        *(u16 *)(s0 + 0x2F) = 0x1D;
    }
}


typedef struct { s32 w[5]; s32 p5; s32 p6; s32 p7; } MTX8L_801821E0;
typedef struct { s16 a, b, c, pad; } SV_801821E0;

void func_801821E0(s32 param_1)
{
    extern MTX8L_801821E0 aD800AE620 __asm__("D_800AE620");
    extern u8 D_80192EB4[];
    extern u8 D_80192EBC[];
    extern void ApplyRotMatrixLV(void *a0, void *a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void RotMatrixY(s32 a0, void *a1);

    MTX8L_801821E0 m;   /* sp+0x10 */
    SV_801821E0 v;      /* sp+0x30 */
    SV_801821E0 out;    /* sp+0x38 */
    s32 s0;
    s16 s2;

    m.p5 = *(s16 *)(param_1 + 0x6);
    m.p6 = *(s16 *)(param_1 + 0xA);
    m.p7 = *(s16 *)(param_1 + 0xE);

    func_800491AC(&m);

    s2 = 0;
    do {
        s0 = func_80132EF4(param_1, 0x22);
        if (s0 != 0) {
            m = aD800AE620;
            RotMatrixY(s2, &m);
            func_8004914C(&m);
            RotTransSV(D_80192EB4, &v, &out);
            *(u16 *)((u8 *)s0 + 0x6) = *(u16 *)&v.a;
            *(u16 *)((u8 *)s0 + 0xA) = *(u16 *)&v.b;
            *(u16 *)((u8 *)s0 + 0xE) = *(u16 *)&v.c;
            ApplyRotMatrixLV(D_80192EBC, (void *)(param_1 + 0x10));
            *(s32 *)((u8 *)s0 + 0x34) = 0x4000;
        }
        s2 = s2 + 0x200;
    } while (s2 < 0x1000);
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80181B6C(void *a0);
extern void func_80181BA0(s32 a0);
extern s32 func_80143994(s32 a0, s32 a1);
extern s32 D_801B3BDC;
extern s32 D_80192E94;

void func_80182320(void *a0)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C810(v0, (s32)&D_801B3BDC);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(u32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x8040;
    *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
    *(u8 *)((s32)a0 + 0x75) = 2;
    *(s32 *)((s32)a0 + 0x58) = (s32)&D_80192E94 | 0x20000000;
    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        func_80181BA0(a0);
        return;
    }
    func_80181B6C(a0);
    *(s32 *)((s32)a0 + 0xD0) = func_80143994((s32)a0, 0x3000);
}


typedef struct { s32 f0, f1, f2; } S_80182618;
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F19C;   /*  8 bytes, align 2 */
typedef struct {
    s32 f0;
    u8 pad[12];
} Tbl16_8018BDE4;



extern void func_8012CBF4(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801439C0(void*);
extern void func_801821E0();
extern s32 func_80181D1C(s32 a0);
extern void func_80181EE8();

void func_801823F4(s32 param_1) {
    s32 flag;
    s16 h;
    s32 d0;
    s32 q;
    s32 v;

    flag = ((s32 (*)(s32))func_8012CBF4)(param_1);
    h = *(s16 *)(param_1 + 0xA);
    d0 = *(s32 *)(param_1 + 0xD0);
    if (h >= 0x81) {
        if (d0 != 0) {
            ((void (*)(u8 *))func_801439C0)((u8 *)d0);
        }
        func_8012C218((void *)param_1);
        return;
    }
    q = *(s32 *)(d0 + 0xCC);
    v = (h << 4) + 0x5800;
    *(u16 *)(q + 0x18) = v;
    *(u16 *)(q + 0x1A) = v;
    if (flag & 0x2000) {
        func_801821E0((void *)param_1);
        func_80181BA0(param_1);
        func_8002D4C8(0xBCB, 0);
    }
    if (func_80181D1C(param_1) != 0) {
        ((void (*)(s32))func_80181EE8)(param_1);
    }
}


void func_801824A8(void) {
}

extern void func_8012CBF4(s32);
extern s32 func_80181D1C(s32);
extern s32 func_80181DAC(s32);
extern void func_80181EE8();
extern void func_80182170(s32, s32);
extern void func_801439C0(void *);
extern void func_8012C218(void *);

void func_801824B0(s32 a0) {
    s32 result;
    s16 field_a;
    void *d0;
    void *t;

    result = ((s32 (*)(s32))func_8012CBF4)(a0);
    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x81) {
        d0 = *(void **)(a0 + 0xD0);
        if (d0 != NULL) {
            ((void (*)(void *))func_801439C0)(d0);
        }
        ((void (*)(void *))func_8012C218)((void *)a0);
        return;
    }
    if ((result & 0x2000) != 0) {
        if ((result & 0xC000) == 0) {
            if (((s32 (*)(s32))func_80181D1C)(a0) != 0) {
                ((void (*)(void *))func_80181EE8)(a0);
            } else {
                t = (void *)((s32 (*)(s32))func_80181DAC)(a0);
                if (t != NULL) {
                    if (*(u16 *)t == 0x1FC) {
                        ((void (*)(void *, void *))func_80182170)((void *)a0, t);
                    }
                }
            }
        }
    }
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


void func_80182574(s32 param_1) {

    extern M2C_UNK D_8019A2FC;
    extern u8   D_8019A0D4;
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
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_8019A2FC));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_8019A0D4);
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



extern void (*D_8019A170[])(void);

void func_801826EC(void *a0) {
    D_8019A170[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8019A184[])(void);

void func_80182728(void *a0) {
    D_8019A184[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_8019A15C;
extern s32 D_8019A168;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_80182764(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_8019A15C);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_8019A168, (s32)&D_800D3918, 0x19) == 0 &&
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

extern int D_8019A178;

void func_80182844(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_8019A178);
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

extern int D_8019A42C;

void func_80182960(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_8019A42C);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

typedef struct { u16 x, y, z, w; } V8_801829BC;

s32 func_801829BC(s32 a0, s32 a1) {
    V8_801829BC sp10;
    V8_801829BC sp18;
    s32 t;
    s32 r;

    sp10.x = *(u16 *)(a0 + 0x6);
    sp10.y = *(u16 *)(a0 + 0xA) - 0x20;
    sp10.z = *(u16 *)(a0 + 0xE);
    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = (s16)a1;
    sp18.y = sp10.y;
    sp18.x = sp10.x - ((t * r) >> 12);
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp18.z = sp10.z - ((t * r) >> 12);
    if ((func_80133784(1, &sp10, (s32)&sp18) & 0x8000) == 0) {
        t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.x = *(u16 *)(a0 + 0x6) - ((t * r) >> 12);
        sp10.y = *(u16 *)(a0 + 0xA) - 0x10;
        t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
        sp10.z = *(u16 *)(a0 + 0xE) - ((t * r) >> 12);
        sp18.x = sp10.x;
        sp18.y = sp10.y + 0x20;
        sp18.z = sp10.z;
        if (func_80133784(1, &sp10, (s32)&sp18) & 0x6000) {
            return 0;
        }
    }
    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    *(s16 *)(a0 + 0x6) = sp18.x + ((t * r) >> 12);
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    *(s16 *)(a0 + 0xE) = sp18.z + ((t * r) >> 12);
    return 1;
}


extern s32 func_8004787C(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_801829BC(s32 a0, s32 a1);
extern u8 D_801A8380[];
extern u8 D_801A8428[];
extern u8 D_801A84D0[];
extern void func_8012A828(s32, void*);
extern void func_8012B1B4(s32 a0, void *a1);
extern void func_8012CBA4(s32 a0);

void func_80182B9C(s32 a0) {
    s32 sp10[3];
    s32 v0;
    s32 v1;
    s32 ret;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = -(func_8004787C(*(s16 *)(a0 + 0xFC)) << 6);

    v0 = (*(u16 *)(a0 + 0xFC) + 0xCC) & 0x7FF;
    *(u16 *)(a0 + 0xFC) = v0;
    if (*(s16 *)(a0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A8380);
        *(s16 *)(a0 + 0xFC) = 0;
    }

    ret = func_8012B864(a0);
    v1 = *(s32 *)(a0 + 0x20);
    *(u16 *)(v1 + 0x12) = (u16)ret;

    func_8012B1B4(a0, sp10);

    func_8012CBA4(a0);

    ret = func_8004787C(*(s16 *)(a0 + 0xFC));
    {
        register s32 arg0 __asm__("$4") = a0;
        register s32 arg1 __asm__("$5") = 0x30;
        __asm__ __volatile__("" :: "r"(arg0), "r"(arg1) : "memory");
        v0 = -(ret >> 7);
        *(s16 *)(a0 + 0x52) = v0;
        func_801829BC(arg0, arg1);
    }

    ret = func_8012BCCC(a0);
    if (ret <= 0x9000) {
        *(s16 *)(a0 + 0x2) = 3;
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A84D0);
        *(s16 *)(a0 + 0x52) = 0;
    }

    if (*(s16 *)(a0 + 0xFE) != 0) {
        *(s16 *)(a0 + 0x2) = 5;
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A8428);
        *(u16 *)(a0 + 0xFC) = 0;
    }
}


extern s32 func_8004787C(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_801829BC(s32 a0, s32 a1);
extern u8 D_801A82F8[];
extern u8 D_801A8428[];
extern void func_8012A828(s32, void*);
extern void func_8012B1B4(s32 a0, void *a1);
extern void func_8012CBA4(s32 a0);

void func_80182CAC(s32 a0) {
    s32 sp10[3];
    s32 ret;
    u16 v0;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = func_8004787C(*(s16 *)(a0 + 0xFC)) * 96;

    v0 = (*(u16 *)(a0 + 0xFC) + 0xCC) & 0x7FF;
    *(u16 *)(a0 + 0xFC) = v0;
    if (*(s16 *)(a0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A8428);
        *(s16 *)(a0 + 0xFC) = 0;
    }

    ret = func_8012B864(a0);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (u16)ret;

    func_8012B1B4(a0, (void *)sp10);

    func_8012CBA4(a0);

    *(s16 *)(a0 + 0x52) = -(func_8004787C(*(s16 *)(a0 + 0xFC)) >> 7);

    if (func_8012BCCC(a0) > 0x8FFF) {
        *(s16 *)(a0 + 0x2) = 1;
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A82F8);
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0x52) = 0;
    }

    if (func_801829BC(a0, -0x30) != 0) {
        *(s16 *)(a0 + 0x2) = 1;
        ((void (*)(s32, void *))func_8012A828)(a0, D_801A82F8);
        *(s16 *)(a0 + 0xFC) = 0xF;
        *(s16 *)(a0 + 0x52) = 0;
    }
}


extern void (*D_8019DC44[])();

void func_80182DC4(int a0)
{
    if (*(s16 *)(a0 + 0x10A) != 0) {
        *(s16 *)(a0 + 0x10A) = *(s16 *)(a0 + 0x10A) - 1;
        if (*(s16 *)(a0 + 0x10A) == 0) {
            *(s32 *)(a0 + 0xC4) &= ~1;
        }
    }
    D_8019DC44[*(u16 *)(a0 + 2)]();
}


extern void func_8012A828(s32 a0, void *a1);

void func_80182E34(void *a0) {
    extern u8 D_801A8898;
    extern u8 D_801A8A58;

    if (*(s32 *)((char *)a0 + 0x90) == (s32)&D_801A8898) {
        func_8012A828((s32)a0, &D_801A8A58);
        *(u16 *)((char *)a0 + 0x5C) = 0xAA10;
    } else {
        *(u16 *)((char *)a0 + 0x98) = 0;
        *(u16 *)((char *)a0 + 0x5C) = 0xAA10;
    }
    *(u16 *)((char *)a0 + 0x2) = 1;
    *(u16 *)((char *)a0 + 0xFC) = 0xF;
}


void func_80182E9C(s32 a0) {
    *(s16 *)(a0 + 0x52) = 0;
    if (*(u8 *)(a0 + 0x5E) == 0x1D) {
        if (*(s16 *)(a0 + 0x10A) == 0) {
            *(s32 *)(a0 + 0xC4) |= 1;
            *(s16 *)(a0 + 0x10A) = 0x3C;
        }
    }
}


void func_80182ED4(s32 arg0) {
    register s32 t __asm__("$2");
    register s32 u __asm__("$3");
    register u32 zr __asm__("$0");
    u16 sp10[10];
    u16 x;
    u16 y;
    u16 z;

    if ((u32) *(u8 *) (arg0 + 0xC2) < 3U) {
        t = *(s16 *) (arg0 + 0x84);
        if (t == 0) {
            x = *(u16 *) (arg0 + 6);
            sp10[0] = x;
            y = *(u16 *) (arg0 + 0xA);
            sp10[1] = y - 0x10;
            z = *(u16 *) (arg0 + 0xE);
            sp10[4] = x;
            sp10[5] = y + 0x10;
            sp10[2] = z;
            sp10[6] = z;
            t = func_80133784(1, sp10, (s32) &sp10[4]);
            if ((t & 0x6000) == 0) {
                return;
            }
            func_8002D4C8(0x83C, 0);
            t = 0x1E;
        } else {
            u = t + zr;
            t = u - 1;
        }
        *(s16 *) (arg0 + 0x84) = t;
    }
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    extern void func_8002AC00(s32 arg0);
    void func_80182F7C(void) {
        func_8002D4C8(0xA9E, 0);
        func_8002AC00(0x14);
    }


#include "common.h"

extern void func_80165988(void);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_80182FA8(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;
    ((void (*)(s32))func_80165988)(arg0);
    if (*(s32 *)(s0 + 0x78) != 0) {
        func_8002A04C(s0);
    }
    func_8012C218((void *)s0);
}


void func_80182FF0(s32 a0) {
    extern u8 D_8019DB0C[];
    extern s32 D_8019DBA8;
    extern s32 D_8019DB40;
    extern u8 D_801A82F8[];
    extern s32 func_80143970(s32 a0);
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012B23C(s32 a0);

    if (func_8012C354(a0, (s32)D_8019DB0C) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -1;
    func_80143970(a0);
    func_8012A828(a0, (void *)&D_801A82F8);
    *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    func_8012B23C(a0);

    if (*(s16 *)(a0 + 0x70) == 3) {
        *(s32 *)(a0 + 0xBC) = (s32)&D_8019DBA8;
    } else {
        *(s32 *)(a0 + 0xBC) = (s32)&D_8019DB40;
    }
}


extern s32 func_8012BCCC(s32 a0);
extern void func_8012A828(s32, void*);
extern u8 D_801A82F8[];
extern u8 D_801A8380[];

void func_8018308C(s32 a0) {
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_8012A828(a0, D_801A82F8);
    }
    if (*(s16 *)(a0 + 0xFE) != 0) {
        *(s16 *)(a0 + 0xFE) = 0;
    } else if (*(s16 *)(a0 + 0xFC) != 0) {
        *(s16 *)(a0 + 0xFC) -= 1;
    } else if (func_8012BCCC(a0) <= 0x40000) {
        *(s16 *)(a0 + 0x2) = 2;
        func_8012A828(a0, D_801A8380);
    }
}


extern s16 D_8019DAFC;
extern s32 D_8019DC18;
extern s32 D_8019DC34;
extern s32 D_8019DC3C;
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_80126B96;
extern u8 D_801A8380[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern void func_8012B1B4(s32 a0, void *a1);

void func_80183130(arg0)
s32 arg0;
{
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    register s32 a2 __asm__("$6");
    register s32 a3 __asm__("$7");

    s0 = arg0;

    if (*(s16 *)(s0 + 0x98) == 0) {
        ((void (*)(s32, s32))func_8012A828)(s0, (s32)D_801A8380);
        *(s16 *)(s0 + 0xFC) = 0;
    }

    if (*(s32 *)(s0 + 0x94) == 15) {
        func_8012B1B4(s0, (void *)&D_8019DC18);
        a0 = s0;
        a1 = (s32)&D_8019DC34;
        __asm__ __volatile__("" :: "r"(a1));
        v0 = 0xFFF60000;
        s0 = 4;
        *(s32 *)(a0 + 0x14) = v0;
        v0 = (s32)&D_8019DAFC;
        v1 = 0x40000000;
        v0 = v0 | v1;
        v1 = 0x20000000;
        v0 = v0 | v1;
        a2 = (s32)&D_8019DC3C;
        a3 = 0x20;
        *(s16 *)(a0 + 2) = s0;
        *(s32 *)(a0 + 0x58) = v0;
        if (func_8012D5E4(a0, a1, a2, a3) == 1) {
            D_80126B96 = s0;
        }
        func_8002D4C8(0xA9D, 0);
    }
}


void func_801831FC(s32 a0) {
    extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8012CBCC(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern u16 D_80126B96;
    extern u8 D_8019DC24[];
    extern u8 D_8019DC2C[];
    extern u8 D_801A8428[];
    extern u8 D_8019DAEC[];

    if (*(s32 *)(a0 + 0x94) < 0x3D) {
        if (func_8012D5E4(a0, (s32)D_8019DC24, (s32)D_8019DC2C, 0x20) == 1) {
            D_80126B96 = 4;
        }
    }
    if (func_8012CBCC(a0) & 0x6000) {
        *(s16 *)(a0 + 0x2) = 5;
        func_8012A828(a0, D_801A8428);
        *(s16 *)(a0 + 0xFC) = 0;
        *(s32 *)(a0 + 0x58) = ((s32)D_8019DAEC | 0x40000000) | 0x20000000;
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);
extern void func_8012E8A8(u8 *a0);

void func_801832A8(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;
    *(s16 *)(s0 + 0x76) = 0;
    if (*(s16 *)(s0 + 0x100) == 0) {
        func_8002A04C(s0);
    }
    if (*(s16 *)(s0 + 0xFE) == 0) {
        ((void (*)(void *))func_8012C098)(s0);
    } else {
        *(s16 *)(s0 + 0x2) = 6;
        func_8012E8A8((u8 *)s0);
        *(s16 *)(s0 + 0x5C) = 0;
        *(u8 *)(s0 + 0xC1) = 0;
    }
}



// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);

void func_80183318(s32 arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern void D_801B0750;
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801B0750)) {
        func_8012A828(arg0, &D_801B0750);
    }
}


extern void func_8012EFB8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80183360(void *a0) {
    u16 in[3];
    s16 out[2];

    in[0] = *(u16 *)((char *)a0 + 0x6);
    in[1] = *(u16 *)((char *)a0 + 0xA);
    in[2] = *(u16 *)((char *)a0 + 0xE);

    ((void (*)(u16 *, s16 *))func_8012EFB8)(in, out);

    {
        s32 v = out[0];
        if (v < 0) {
            v = -v;
        }
        if (v < 0xB5) {
            v = out[1];
            if (v < 0) {
                v = -v;
            }
            if (v < 0xA1) {
                func_8002D4C8(0x98A, 0);
            }
        }
    }
}



extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801B0BD8;

void func_801833EC(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801B0BD8);
    *(s32 *)(a0 + 0x1C) = 0x14;
}


extern void D_801B0750;
extern void func_8012A828(s32 a0, void *a1);

void func_8018342C(s32 a0) {
    
    extern void D_801B0750;
    *(s16 *)(a0 + 0x2) = 3;
    func_8012A828(a0, &D_801B0750);
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    *(s16 *)(a0 + 0x5E) = 0;
    *(s16 *)(a0 + 0xDC) = 0;
    *(s32 *)(a0 + 0x1C) = 0x2D;
}



// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_8018352C else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_8018352C(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801B0B30;

s32 func_8018347C(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_8018352C(param_1);
        return 1;
    }
    sVar1 = *(s16 *)(param_1 + 0xdc) + 1;
    *(s16 *)(param_1 + 0xdc) = sVar1;
    if (sVar1 < 0x79) {
        return 0;
    }
    if (param_3 >= iVar2) {
        return 0;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_8012A828(param_1, &D_801B0B30);
    return 1;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801B08F0;

void func_8018352C(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801B08F0);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_80183588(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0x14;
    }


typedef struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } St_80182784_80185DA8_8018359C;
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F19C_8018359C;   /*  8 bytes, align 2 */
typedef struct {
    s32 f0;
    u8 pad[12];
} Tbl16_8018BDE4_8018359C;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8018359C;

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012EFB8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

void func_8018359C(void *a0) {

    extern void D_801B0750;
    if (*(s32 *)((char *)a0 + 0x1C) == 9) {
        extern u8 D_801A8C54[];
        extern u8 D_801A8C64[];

        func_8012D5E4((s32)a0, (s32)D_801A8C54, (s32)(D_801A8C54 + 8), 0x10);

        if (*(s16 *)((char *)a0 + 0x70) & 0x8000) {
            u16 out[4];
            struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } s;
            s32 buf[8];

            func_8012EC04((s32)a0, 0, buf);
            ((void (*)(s32 *, u8 *, u16 *))func_8012F14C)(buf, D_801A8C64, out);

            s.f6 = 0x23E;
            s.f0 = out[0];
            s.f2 = out[1];
            s.f4 = out[2];
            s.fA = 0;
            s.fC = 0x7FFF;

            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12);
            func_8012C51C(&s, (s32)a0);
            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12) + 0x100;
            func_8012C51C(&s, (s32)a0);
            s.fE = *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x12) - 0x100;
            func_8012C51C(&s, (s32)a0);
        }

        {
            u16 in3[3];
            s16 out2[2];
            s32 v;

            in3[0] = *(u16 *)((char *)a0 + 0x6);
            in3[1] = *(u16 *)((char *)a0 + 0xA);
            in3[2] = *(u16 *)((char *)a0 + 0xE);

            ((u32 (*)(u16 *, s16 *))func_8012EFB8)(in3, out2);

            v = out2[0];
            if (v < 0) {
                v = -v;
            }
            if (v < 0xB5) {
                v = out2[1];
                if (v < 0) {
                    v = -v;
                }
                if (v < 0xA1) {
                    func_8002D4C8(0x98B, 0);
                }
            }
        }
    }

    if (func_8012BEE8((s32)a0) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 3;
        func_8012A828((s32)a0, &D_801B0750);
        *(u16 *)((char *)a0 + 0x5C) = 0xAA10;
        *(s16 *)((char *)a0 + 0x5E) = 0;
        *(s16 *)((char *)a0 + 0xDC) = 0;
        *(s32 *)((char *)a0 + 0x1C) = 0x2D;
    }
}


extern void func_80184614(s32 a0, u16 *a1, s16 a2);

void func_80183750(u8 *a0) {
    s16 sp10[3];

    if (*(u16 *)(a0 + 0x5E) == 0x24) {
        sp10[0] = 2;
        sp10[1] = 0xF;
        sp10[2] = -2;
        func_80184614((s32)a0, (u16 *)sp10, 0xD);
    }
}



/* Fresh mass-lane crack (Phase-31 wave T). No banked twin was found for this
 * skeleton (grepped D_801B3AC0 / D_801A8C14 / D_801A8C34 / D_801A8C6C / the
 * jal callees across src/ -- only extern decls / INCLUDE_ASM stubs turned up,
 * all for unrelated overlay-local reuses of the same address). The dispatch
 * head (D_801A8C6C[*(u16*)(a0+2)]();) mirrors the ALREADY-BANKED
 * func_8017EC70 in THIS SAME TU (D_8018C074[*(u16*)((s32)a0+2)]();) -- same
 * idiom, used as a hint per law 1 (never copied its symbols). */

extern s32 func_8012C044(s32 a0);
extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);
extern void func_8012E8A8(u8 *a0);
extern void func_800183E0(s32 a0);

void func_80183798(void *a0) {

    extern void (*D_801A8C6C[])(void);
    extern u16 D_800B99DA;
    extern u16 D_801A8C14[];
    extern u16 D_801B3AC0[];
    extern u8 D_801A8C34[];
    void *s0 = a0;

    D_801A8C6C[*(u16 *)((u8 *)s0 + 0x2)]();

    if (func_8012C044((s32)s0)) {
        *(s16 *)((u8 *)s0 + 0x100) = 1;
        __asm__ __volatile__("" ::: "memory");
        *(s16 *)((u8 *)s0 + 0x76) = 0;
        if (*(s16 *)((u8 *)s0 + 0x100) == 0) {
            func_8002A04C((s32)s0);
        }
        if (*(s16 *)((u8 *)s0 + 0xFE) == 0) {
            ((void (*)(void *))func_8012C098)(s0);
        } else {
            *(s16 *)((u8 *)s0 + 0x2) = 6;
            func_8012E8A8((u8 *)s0);
            *(s16 *)((u8 *)s0 + 0x5C) = 0;
            *(u8 *)((u8 *)s0 + 0xC1) = 0;
        }
    }

    if (*(s16 *)((u8 *)s0 + 0xFE) != 0) {
        u16 *src = D_801A8C14;
        s32 shift = D_800B99DA & 0xF;
        u16 *dst = &D_801B3AC0[shift];
        s32 i;

        for (i = 0; i < 0xF - shift; i++) {
            *dst++ = *src++;
        }
        dst = D_801B3AC0;
        for (i = 0; i < shift; i++) {
            *dst++ = *src++;
        }
        func_800183E0((s32)D_801A8C34);
    }
}



extern void (*D_801A8C90[])(void);

void func_801838E4(void *a0) {
    D_801A8C90[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_801A8CA4[])(void);

void func_80183920(void *a0) {
    D_801A8CA4[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        void *ptr = *(void **)((s32)a0 + 0xCC);
        *(u16 *)((s32)ptr + 0x8) = *(u16 *)((s32)a0 + 0x6);
        ptr = *(void **)((s32)a0 + 0xCC);
        *(u16 *)((s32)ptr + 0xA) = *(u16 *)((s32)a0 + 0xA);
        ptr = *(void **)((s32)a0 + 0xCC);
        *(u16 *)((s32)ptr + 0xC) = *(u16 *)((s32)a0 + 0xE);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143994(s32 a0, s32 a1);
extern u8 D_801A8C98;

void func_801839A8(void *a0)
{
    s32 v0;
    s32 s0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, 0);
    v0 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v0 + 0x1A) = 0x1800;
    *(s16 *)(v0 + 0x18) = 0x1800;
    s0 = ((s32 (*)(void))func_8012C194)();
    if (s0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    *(s32 *)((s32)a0 + 0xCC) = s0;
    func_8001CB6C((u8 *)s0, (s32)&D_801A8C98, 0x2E0, 0x100);
    *(u8 *)(s0 + 0x27) = 0x37;
    *(s16 *)(s0 + 0x10) = 0x400;
    *(s32 *)(s0 + 0x4) |= 0x50000000;
    v0 = *(u16 *)((s32)a0 + 0xFC);
    *(s16 *)(s0 + 0x1A) = 0x1800;
    *(s16 *)(s0 + 0x18) = 0x1800;
    *(s16 *)(s0 + 0x14) = v0;
    *(s16 *)((s32)a0 + 0x2) = 1;
    func_80143994((s32)a0, 0x1000);
}



extern void func_8012B2CC(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80183A80(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF00000);
}


extern void func_8012CBF4(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80183B64(s32 param_1);

extern u16 D_80126B96;
extern s32 D_801A8CB0;

void func_80183AD8(s32 param_1)
{
    s32 p;

    p = *(s32 *)(param_1 + 0xCC);
    *(u16 *)(p + 0x14) = *(u16 *)(p + 0x14) + 0x80;
    if (((s32 (*)(s32))func_8012CBF4)(param_1) == 0) {
        if (func_8012D5E4(param_1, (s32)&D_801A8CB0, (s32)((u8 *)&D_801A8CB0 + 8), 0x10) == 0 &&
            --*(s32 *)(param_1 + 0x1C) != 0) {
            return;
        }
        D_80126B96 = 0x13;
    }
    func_80183B64(param_1);
}



extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);
    void func_80183B64(s32 param_1) {
        s32 iVar1;
        iVar1 = *(s32 *)(param_1 + 0xcc);
        ((void (*)(s32 *, s32))func_80016714)((s32 *)iVar1, 0x38);
        ((void (*)(s32))func_8012C218)(param_1);
    }


extern s32 func_8012BCCC(s32 a0);
extern void func_801833EC(s32 a0);

void func_80183B9C(s32 a0) {
    s32 iVar1;

    if (*(s16 *)(a0 + 0x70) & 0x8000) {
        iVar1 = func_8012BCCC(a0);
        if (iVar1 <= 0x90000) {
            func_801833EC(a0);
        }
    } else {
        iVar1 = func_8012BCCC(a0);
        if (iVar1 <= 0x24000) {
            func_801833EC(a0);
        }
    }
}


extern s32 func_8012BEE8(s32 arg);
    extern void func_8018342C(s32 a0);
    void func_80183C08(s32 a0) {
        if (func_8012BEE8(a0)) {
            ((void (*)(s32))func_8018342C)(a0);
        }
    }


extern s32 func_8012BEE8(s32 a0);

void func_80183C40(s32 param_1)
{
    if (((s32 (*)(void))func_8012BEE8)() == 1) {
        if (*(s16 *)(param_1 + 0x70) & 0x8000) {
            func_8018347C(param_1, 0x40000, 0xC4000);
        } else {
            func_8018347C(param_1, 0x9000, 0x24000);
        }
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183588(void*);

void func_80183CA4(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_80183588)(param_1);
    }
}


void func_80183CFC(void) {
}

extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80183D04(s32 s0) {
    s32 v0;
    s32 a1v;

    extern s32 D_801A8B80;
    extern s32 D_801A8BB4;
    extern u8 D_801B0B30;

    v0 = func_8012C354(s0, (s32)&D_801A8B80);
    if (v0 == 0) {
        return;
    }

    *(u8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xB4) = -1;
    *(s32 *)(s0 + 0xBC) = (s32)&D_801A8BB4;
    *(s32 *)(s0 + 0xC4) = 1;

    a1v = *(s16 *)(s0 + 0x70);
    *(u16 *)(s0 + 0xAE) = 8;

    v0 = func_8012C658(0x23F, a1v, s0);
    *(s32 *)(s0 + 0x6C) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s0);
    } else {
        if (func_8012E504(s0, 0x23D) == 0) {
            *(u16 *)(s0 + 0xFE) = 1;
        }
        *(u16 *)(s0 + 0x2) = 1;
        func_8012A828(s0, (void *)&D_801B0B30);
    }
}


extern s32 D_801AA6D0;
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_80183DBC(int param_1)
{
    int v0;
    int v1;
    int temp;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801AA6D0);
        temp = *(int *)(param_1 + 0x64);
        v1 = *(unsigned short *)(temp + 0x36);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0xFE) = 0x7FFF;
        *(short *)(param_1 + 0xFC) = v1;
    }
}



typedef struct { s16 a, b, c; } SV3x_80183E2C;          /* 6-byte, align-2 triple of s16 */
typedef struct { s16 a, b, c, d; } SV4x_80183E2C;       /* 8-byte, align-2 quad of s16 */

extern void func_8012C218(void *a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);


void func_80183E2C(void *a0) {

    extern s32 D_801B0D28;
    extern s32 D_801A8C88;
    s32 s0 = (s32)a0;
    s32 s1;
    SV3x_80183E2C out;

    s1 = *(s32 *)(s0 + 0x64);

    if (*(s16 *)(s0 + 0xFE) == 0x7FFF) {
        *(s16 *)(s0 + 0xFE) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12);
    }

    if (*(s16 *)(s0 + 0xFC) != *(s16 *)(s1 + 0x36)) {
        func_8012C218((void *)s0);
        return;
    }

    *(SV4x_80183E2C *)(*(s32 *)(s0 + 0x20) + 0x10) = *(SV4x_80183E2C *)(*(s32 *)(s1 + 0x20) + 0x10);

    if (*(s32 *)(s1 + 0x90) != (s32)&D_801B0D28) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = *(s16 *)(s0 + 0xFE);
        *(s32 *)(s0 + 0x4) = *(s32 *)(s1 + 0x4);
        *(s32 *)(s0 + 0x8) = *(s32 *)(s1 + 0x8);
        *(s32 *)(s0 + 0xC) = *(s32 *)(s1 + 0xC);
    } else {
        func_8012F214(s1, (s32)&D_801A8C88, (s32)&out);
        *(s16 *)(s0 + 0x6) = out.a;
        *(s16 *)(s0 + 0xA) = out.b;
        *(s16 *)(s0 + 0xE) = out.c;
    }

    *(SV4x_80183E2C *)(*(s32 *)(s0 + 0x20) + 0x18) = *(SV4x_80183E2C *)(*(s32 *)(s1 + 0x20) + 0x18);

    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = *(s16 *)(*(s32 *)(s1 + 0x20) + 0x2C);
    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x4);
}



extern void (*D_801B0DF4[])(void);

void func_80183FA0(void *a0) {
    D_801B0DF4[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_801844FC(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80184554(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80183FDC(s32 a0) {
    extern u8 D_801B0DA8[];
    extern u8 D_801B0DB4[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_801844FC(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801B0DA8, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801B0DB4);
        func_80184554(a0);
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
extern void func_80184554(s32 arg0);
extern void func_801845D0(void *arg0);

void func_801840D8(s32 arg0) {
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
            func_80184554(arg0);
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
    func_801845D0((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80184554(s32 arg0);
extern void func_801845D0(void *arg0);

void func_80184368(s32 arg0) {

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
        func_80184554(arg0);
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
    func_801845D0((void *)arg0);
}



/* func_801844FC — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_801844FC(s32 arg0) {
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

void func_80184554(s32 arg0) {
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



/* func_801845D0 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801845D0(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_80184614(s32 a0, u16 *a1, s16 a2) {
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





