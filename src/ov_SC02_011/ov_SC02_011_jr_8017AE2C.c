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
extern u8 D_80193268;
extern u8 D_801931D8;
extern u8 D_801931B4;
extern u8 D_80193190;
extern u8 D_80193244;
extern u8 D_80193220;
extern u8 D_801931FC;
extern u8 D_8019316C;
extern void func_80145934(void);
extern u8 D_801932F8;
extern u8 D_801932D4;
extern u8 D_801932B0;
extern u8 D_8019328C;
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
extern unsigned char D_801926F0[];
extern unsigned char D_80192720[];
extern unsigned char D_80192770[];
extern unsigned char D_801927A0[];
extern unsigned char D_801927D0[];
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
extern void (*D_80192820[])(void *);
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
extern s32 D_801928E8[];
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
extern u8 D_80192970[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80192978;
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
extern int D_801EA008;
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
extern s32 D_801EA00C;
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
extern s32 D_801929A8;
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
extern void (*D_80192A50[])(void);
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
extern void (*D_80192A74[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80192A64;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80192A88[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80192A94[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80192AA4[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80192ABC[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80192AAC;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80192AD0[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80192AEC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80192ADC;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80192B00[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80192B14[])(void);
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
extern s32 D_80192B28;
extern void (*D_80192B50[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80192B30;
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
extern int (*D_80192B9C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80192BA0[])(void);
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
extern s32 func_8014C568(void *a0);
extern void func_801567BC(s32 a0);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80193004[];
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
extern void (*D_80193014[])(void);
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
extern int D_801EA040;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8019303C[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8019301C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8019302C;
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
extern void (*D_8019307C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80193084[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80193050;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80193090[])(void);
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
extern u8 D_80193060;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801EA048;
extern s32 D_801EA054;
extern s32 D_801EA058;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801930CC[])(s32 *);
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
extern s32 D_801930A0[];
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
extern s32 D_801EA050;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8019331C[])(void);
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
extern char D_8019313C[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801933C0[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80193514[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80193330;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8019351C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80193340;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80193360;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80193524[])(void);
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
extern void (*D_8019354C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80193558[])(void);
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
extern void (*D_801933CC[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801935FC;
extern void func_8015D380(s32 a0);
extern unsigned char D_801926E0[];
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
extern unsigned char D_80193610[];
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
extern s8 D_8019364C[];
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
extern u16 D_80193694;
extern u16 D_80193696;
extern u16 D_80193698;
extern s32 D_8019369C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801936A4;
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
extern int D_801933B0;
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
extern unsigned int D_80193728[];
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
extern void (*D_801937D8[])(void);
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
extern u16 D_80193808[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8019386C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801EA060[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80193890[])(void);
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
extern int D_801EA0B8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801938D8[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801938C8;
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
extern char D_801E9854[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801938E0[])(void);
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
extern void (*D_80193934[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801938FC;
extern s16 D_80193930;
extern s16 D_8019392E;
extern s16 D_8019392C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80193940[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801EA118;
extern u8 D_801EA119;
extern u8 D_801EA11A;
extern u8 D_801EA11B;
extern u8 D_801EA11C;
extern u8 D_801EA11D;
extern u8 D_801EA11E;
extern u8 D_801EA11F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80193950[])(void);
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
extern s32 D_801EA158;
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
extern void (*D_80193994[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80193A10[];
extern s32 D_80193A30[];
extern u8 D_80193AAC[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80193ACC[];
extern u8 D_80193AEC[];
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
extern void (*D_80193B88[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80193C04[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E9864;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80193C10[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80193C18[])(void);
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
extern void (*D_80193CE0[])(void);
extern void func_80166618(void *a0);
extern void (*D_80193CF0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80193D00[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80193D0C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80193C6C[];
extern u8   D_80193C80[];
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
extern void (*D_80193D24[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80193D2C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80193D34[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80193D3C[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80193D44[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80193D4C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80193D54[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80193E08[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80193E10[])(void);
extern void func_80169F00(void *a0);
extern char D_80193DC0[];
extern char D_80193D80[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80193E48[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80193E54[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80193E9C[])(void);
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
extern void (*D_80193F18[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801EA478;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80193F0C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80193F50[];
extern unsigned short D_80193F58[];
extern unsigned short D_80193F60[];
extern unsigned char D_801EA480[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801EA478;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80193F68[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EA5B4;
extern M2C_UNK D_801EA5B8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EA540;
extern void (*D_80193F98[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EA5BC[];
extern u8 D_801EA5C4[];
extern u8 D_801EA574[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80193FA0[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80193FBC[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80193FC4[])(void);
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
extern void (*D_8019402C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80193FD0;
extern u8 D_80193FDC;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80194060[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80194068[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801940BC[])(void);
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
extern u16 D_801940F0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801940E0[];
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
extern s32 D_8019410C;
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
extern void (*D_80194184[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8019418C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80194194[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8019419C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801941A4[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801941AC[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801941B8[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801941C4[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801941D0[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801941E0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801941F0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801941F8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80194200[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80194208[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80194210[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80194218[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80194220[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80194228[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80194230[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80194238[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80194240[])(void);
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
extern void (*D_80194248[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80194250[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80194258[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80194260[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80194268[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80194270[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80194278[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80194280[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80194288[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80194290[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80194298[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801942A0[])(void);
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
extern void (*D_801942E4[])(void);
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
extern M2C_UNK D_801942A8;
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
extern void (*D_80194314[])(void);
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
extern void (*D_80194350[])(void);
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
extern void (*D_801943A8[])();
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
extern void (*D_801943B8[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801943C0[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80194528[])();
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
extern void (*D_80194534[])();
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
extern M2C_UNK D_801E9AAC;
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
extern s16 D_801EBA08;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801EACF8;
extern short D_801EBA7C;
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
extern s32 D_801EB124;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801EB14C;
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
extern s16 D_801EB108;
extern s32 func_8017A3B0(void);
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

extern s16 D_801EB9D8;
extern s16 D_801EB9DA;
extern s16 D_801EB9E4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801EB9D8;

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
                    func_8012B744(p, &D_801EB9E4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801EB9D8+0xC == &D_801EB9E4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801EB9D8 + 0xC)) < 0x101) {
                    D_801EB9D8 = 0;
                    D_801EB9DA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801EB9E4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801EB9D8 + 0xC)) < 0x101) {
            D_801EB9D8 = 0;
            D_801EB9DA = 0;
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
    extern s16 D_801EB184;
    extern s16 D_801EB186;
    extern s16 D_801EB188;
    extern s16 D_801EB17C;
    extern s16 D_801EB17E;
    extern s16 D_801EB180;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801EB184, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801EB186, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801EB188, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801EB17C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801EB17E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801EB180, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801EB10C;
extern u16 D_801EB18C;
extern u16 D_801EB18E;
extern u16 D_801EB190;
extern s16 D_801EBA08;

void func_8017B1D8(void) {
    func_8012A418();
    D_801EBA08 = 0;
    D_801EB10C = 0;
    D_801EB18C = D_80126B5E;
    D_801EB18E = D_80126B62;
    D_801EB190 = D_80126B66;
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
    extern u8 D_80194670[];
    extern s16 D_801EB184;
    extern s16 D_801EB17C;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80194670[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80194670[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EB184;
        s16 *p78C = &D_801EB17C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801EBA08 = 1;
        D_801EB10C = 0;
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
    extern SV4_8017B368 D_801EB12C;
    extern SV4_8017B368 D_801EB134;
    extern s16 D_801EB184;
    extern s16 D_801EB17C;
    extern u16 D_80194670;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801EB12C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801EB134;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80194670)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80194670)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801EB184) = loc0;
    (*(SV4_8017B368 *)&D_801EB17C) = loc1;
    D_801EBA08 = 1;
    D_801EB10C = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801EB12C;
    extern SV4_8017B368 D_801EB134;
    extern s16 D_801EB184;
    extern s16 D_801EB17C;
    extern u16 D_80194670;
    extern s16 D_801EB10C;
    extern s16 D_801EBA08;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801EB12C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801EB134;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80194670)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80194670)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801EB184) = loc0;
    (*(SV4_8017B368 *)&D_801EB17C) = loc1;
    D_801EBA08 = 1;
    D_801EB10C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801EB184).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801EB184).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801EB184).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801EB17C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801EB17C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801EB17C).c;
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
    extern u8 D_80194670[];
    extern s16 D_801EB184;
    extern s16 D_801EB186;
    extern s16 D_801EB188;
    extern s16 D_801EB17C;
    extern s16 D_801EB17E;
    extern s16 D_801EB180;
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
        s32 a1addr = (s32)&D_80194670[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80194670[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EB184;
        s16 *p78C = &D_801EB17C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801EB186;
            v798 = D_801EB188;
            v78C = *p78C;
            v78E = D_801EB17E;
            v790 = D_801EB180;
            __asm__ __volatile__("");
            D_801EBA08 = 1;
            D_801EB10C = 0x1E;
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
extern s16 D_801EB10C;
extern s16 D_801EB184;
extern s16 D_801EB186;
extern s16 D_801EB188;
extern s16 D_801EB17C;
extern s16 D_801EB17E;
extern s16 D_801EB180;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801EB10C = 0;
    D_801EB184 = (s16) D_80114F30;
    D_801EB186 = (s16) D_80114F34;
    D_801EB188 = (s16) D_80114F38;
    D_801EB17C = (s16) D_80114F24;
    D_801EB17E = (s16) D_80114F28;
    D_801EB180 = (s16) D_80114F2C;
}




extern s16 D_801EB19C;
extern s16 D_801EB19E;
extern s16 D_801EB1A0;
extern s16 D_801EB1A4;
extern s16 D_801EB1A6;
extern s16 D_801EB1A8;

void func_8017B824(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801151D4;
    D_801EB19C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801EB19E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801EB1A0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801EB1A4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801EB1A6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801EB1A8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801EB19C;
extern s16 D_801EB19E;
extern s16 D_801EB1A0;
extern s16 D_801EB1A4;
extern s16 D_801EB1A6;
extern s16 D_801EB1A8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801EB19C;
    D_80114F34 = D_801EB19E;
    D_80114F38 = D_801EB1A0;
    D_80114F24 = D_801EB1A4;
    D_80114F28 = D_801EB1A6;
    D_80114F2C = D_801EB1A8;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801EB184), src[8..15] -> (*(S8_8017B8E8 *)&D_801EB17C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801EB184) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801EB17C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801EB18C;
extern u16 D_801EB18E;
extern u16 D_801EB190;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801EB10C;
extern short D_801EB194;
extern short D_801EB196;
extern short D_801EB198;
extern s16 D_801EB184;
extern s16 D_801EB186;
extern s16 D_801EB188;
extern s16 D_801EB17C;
extern s16 D_801EB17E;
extern s16 D_801EB180;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801EB18C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801EB18E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801EB190);
    (*(s16 *)&D_801EB194) = buf[0];
    (*(s16 *)&D_801EB196) = buf[1];
    (*(s16 *)&D_801EB198) = buf[2];
    D_801EB184 = D_80114F30 + buf[0];
    D_801EB10C = 0;
    D_801EB186 = D_80114F34 + buf[1];
    D_801EB188 = D_80114F38 + buf[2];
    D_801EB17C = D_80114F24 + buf[0];
    D_801EB17E = D_80114F28 + buf[1];
    D_801EB180 = D_80114F2C + buf[2];
}



// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_L48: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801EB12C;
extern SV4 D_801EB134;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801EB134) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801EB12C = svec;

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
    D_801EB134 = buf1;
}


// @class: struct
// @stuck: none — MATCH (65 ins)
#include "common.h"




s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801EB134)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801EB12C) = svec;

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
    (*(SV4_8017BB34*)&D_801EB134) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801EB154[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801EB154;
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
extern s16 D_801EB10C;
extern s16 D_801EBA08;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801EB10C = D_801EB10C + 1;
    if (D_801EB10C >= 0x1F) {
        D_801EBA08 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801EB10C;
extern s16 D_801EBA08;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EB10C = D_801EB10C + 1;
    if (0x18 < D_801EB10C) {
        func_8012A4BC();
        D_801EBA08 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801EB10C;
extern void (*D_801EB150)(void);
extern short D_801EB194;
extern short D_801EB196;
extern short D_801EB198;
extern s16 D_801EBA08;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EB10C = D_801EB10C + 1;
    if (D_801EB10C >= 0x19) {
        if (D_801EB150 != 0) {
            (*D_801EB150)();
        } else {
            D_80114F30 = D_80114F30 + D_801EB194;
            D_80114F34 = D_80114F34 + D_801EB196;
            D_80114F38 = D_80114F38 + D_801EB198;
            D_80114F24 = D_80114F24 + D_801EB194;
            D_80114F28 = D_80114F28 + D_801EB196;
            D_80114F2C = D_80114F2C + D_801EB198;
            func_8012A4BC();
        }
        D_801EBA08 = 0;
    }
}



extern void (*D_80194710[])(void);

void func_8017BE60(void *a0) {
    D_80194710[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */


extern void (*D_80194734[])(void);

void func_8017BEBC(void *a0) {
    D_80194734[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017BEF8(s32 param_1) {

    extern u8 D_8019471C;
    s32 obj = *(s32 *)(param_1 + 0x34);
    Work8017 w;
    short i;
    s32 e;
    s32 node;

    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 0x10),
                  *(s16 *)(param_1 + 0xE), 0, 0);

    w.x = *(u16 *)(param_1 + 6);
    w.y = *(u16 *)(param_1 + 0xA);
    w.z = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&w.x, &w.vx, 10);
    *(s16 *)(param_1 + 6) = w.x;
    *(s16 *)(param_1 + 0xE) = w.z;
    w.vy = 0;
    func_800D23D0(&w.vx);

    i = 0;
    do {
        e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                          *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE), i, 0);
        if (e != 0) {
            *(s16 *)(e + 0x12) = w.vx;
            *(s16 *)(e + 0x16) = w.vy;
            *(s16 *)(e + 0x1A) = 0;
        }
        i = i + 1;
    } while (i < 3);

    node = func_800D222C(param_1, &D_8019471C, 0xFD);
    if (node != 0) {
        *(s32 *)(param_1 + 0x20) = node;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x5D000100;
        ((void (*)(void *))func_8001CF30)((void *)node);
        *(s16 *)(node + 0x18) = 0x4000;
        *(s16 *)(node + 0x1A) = 0x200;
        *(s16 *)(param_1 + 0x16) = 0x200;
        *(s16 *)(param_1 + 0x14) = 0x1000;
        *(s16 *)(node + 0x28) = 0x240;
        *(s16 *)(node + 0x2A) = 0x180;
        *(s16 *)(node + 0x10) = w.vx;
        *(s16 *)(node + 0x12) = w.vy;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


DEFINE_func_8017C0BC()  /* dedup: shared engine-core @0x8017C0BC (src/shared) */


extern void (*D_8019473C[])(void);

void func_8017C150(void *a0) {
    D_8019473C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_80194728;

void func_8017C18C(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_80194728, 0x18);
    if (r != 0) {
        *(s32 *)(a0 + 0x20) = r;
        *(u32 *)(r + 4) = *(u32 *)(r + 4) | 0x5C000140;
        func_8001CF30((void *)r);
        *(s16 *)(r + 0x10) = 0x400;
        *(s16 *)(r + 0x18) = 0x3000;
        *(s16 *)(r + 0x1A) = 0x3000;
        *(s16 *)(r + 0x28) = 0x248;
        *(s16 *)(r + 0x2A) = 0x180;
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}


DEFINE_func_8017C230()  /* dedup: shared engine-core @0x8017C230 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017C294);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017C360);


extern void (*D_80194750[])(void);

void func_8017C4BC(void *a0) {
    D_80194750[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017C4F8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017C558);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017C688);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017CA14);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017CC8C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017CDD4);


extern void (*D_80194868[])(void);

void func_8017CF54(void *a0) {
    D_80194868[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017CF90);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017CFDC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D0D0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D150);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D204);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D270);

extern void func_8012C218(void *a0);
    void func_8017D2FC(void) {
        ((void (*)(void))func_8012C218)();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D31C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D370);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D50C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017D710);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017DB04);


extern void (*D_80194B68[])(void);

void func_8017DC84(void *a0) {
    D_80194B68[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017DCC0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017DD34);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017DE10);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E024);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E0F8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E1C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E220);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E318);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E358);


extern void (*D_80194B8C[])(void);

void func_8017E380(void *a0) {
    D_80194B8C[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8 *a0);
    extern void func_80171A1C(u8 *a0);
    extern void func_8017E3F4(s32 a0);
    void func_8017E3BC(s32 a0) {
        s32 s0 = a0;
        ((void (*)(s32 *))func_80147060)((s32 *)s0);
        ((void (*)(s32))func_80171A1C)(s0);
        ((void (*)(s32))func_8017E3F4)(s0);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E3F4);

void func_8017E434(void) {
}

extern void func_80174684(void *);
    extern s32 func_8017E464;
    void func_8017E43C(void) {
        func_80174684(&func_8017E464);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E464);

extern void func_80147060(u8 *a0);
    extern void func_80171A1C(u8 *a0);
    extern void func_8017E4D8(s32 a0);
    void func_8017E4A0(s32 a0) {
        s32 s0 = a0;
        ((void (*)(s32 *))func_80147060)((s32 *)s0);
        ((void (*)(s32))func_80171A1C)(s0);
        ((void (*)(s32))func_8017E4D8)(s0);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E4D8);

void func_8017E518(void) {
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E520);


extern void (*D_80194C58[])(void);

void func_8017E564(void *a0) {
    D_80194C58[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E5A0);

extern void func_8017E5F0(void);
void func_8017E5C8(void) {
    func_8017E5F0();
}


void func_8017E5E8(void) {
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E5F0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017E72C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017EAC0);


extern void (*D_80194C98[])(void);

void func_8017EB00(void *a0) {
    D_80194C98[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017EB3C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017ECB0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017ED98);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F0E0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F160);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F1AC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F2AC);


extern void (*D_80194CB8[])(void);

void func_8017F2F0(void *a0) {
    D_80194CB8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F32C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F458);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F534);


extern void (*D_80194CC8[])(void);

void func_8017F578(void *a0) {
    D_80194CC8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F5B4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F630);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F67C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017F7B4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FA94);


extern void (*D_80194CD4[])(void);

void func_8017FAD8(void *a0) {
    D_80194CD4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FB14);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FBF8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FCA0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FD2C);


/* func_8017FD9C — fade the 4-byte colour quad at D_801EB488 one step toward 0
 * (func_80012F74 = "step a value toward a target"), splat the byte over the
 * three sibling bytes, mirror the whole quad into the three following quads,
 * then tear the entity down once the byte reaches 0.
 *
 * §71 sibling-first: DEFINE_func_801685EC() (engine_core.h L8520) is the same
 * `if (<call result> == 0) ((void (*)(s32))func_80146C3C)(arg0);` teardown tail.
 * In-TU sibling func_8017D678 shows D_801EB489/D_801EB48A are SEPARATE u8
 * globals (each gets its own lui/%lo sb) while D_801EB488's address lives in a
 * callee-saved register.
 *
 * @class: schedule (LENGTH-DRIFT/-1)
 * @stuck: none — MATCH 50/50 (match_one AND rtu_match), iteration 2.
 * THE CRACK (one edit): the TRAILING reload `if (*p == 0)` was being hoisted by
 * sched2 up past the third block move, where the swl/swr pair covered its load
 * delay — costing exactly the one `nop` the target keeps (49 vs 50 ins,
 * LENGTH-DRIFT/-1). A second zero-byte `__asm__("")` fence between the last
 * struct assignment and the `if` pins the lbu after the copies and the load-delay
 * nop reappears. Lesson: an inline block move (swl/swr) is a fat delay-slot
 * SPONGE — any following narrow load will be sucked up into it unless fenced.
 * The first fence (after the chained byte stores) is what keeps the block moves
 * from being interleaved with them.
 * Other levers already in this draft, all load-bearing:
 *  - `u8 *p = &D_801EB488;` (§20) — one address register ($s0, callee-saved
 *    across the jal) serves the lbu, the sb and all three block-move sources.
 *  - chained assignment `D_801EB489 = D_801EB48A = *p = f(...)` gives the
 *    target's store order 880, 882, 881 (right-to-left after the *p store).
 *  - the 4×u8 struct (align 1) is what makes the assignment expand to inline
 *    lwl/lwr + swl/swr instead of a `jal memcpy` (cf. §38).
 */

typedef struct {
    u8 b0, b1, b2, b3;
} Quad_801EA880_8017FD9C; /* align 1 => movstrsi expands to lwl/lwr + swl/swr */


extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

void func_8017FD9C(s32 arg0) {

    extern u8 D_801EB488;
    extern u8 D_801EB489;
    extern u8 D_801EB48A;
    extern u8 D_801EB48C;
    extern u8 D_801EB490;
    extern u8 D_801EB494;
    u8 *p = &D_801EB488;

    D_801EB489 = D_801EB48A = *p = func_80012F74(*p, 0, 10, 1);
    __asm__("");
    *(Quad_801EA880_8017FD9C *)&D_801EB48C = *(Quad_801EA880_8017FD9C *)p;
    *(Quad_801EA880_8017FD9C *)&D_801EB490 = *(Quad_801EA880_8017FD9C *)p;
    *(Quad_801EA880_8017FD9C *)&D_801EB494 = *(Quad_801EA880_8017FD9C *)p;
    __asm__("");
    if (*p == 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FE64);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8017FF34);


extern void (*D_80194E58[])(void);

void func_8017FF9C(void *a0) {
    D_80194E58[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_80180010(u8*);
void func_8017FFD8(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    ((void (*)(void *))func_80180010)(a0);
}



extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B36;
void func_80180010(u8 *a0) {
    s16 *p = &D_80126B36;
    if (*p != 0) {
        if (func_80171CC4(a0, p - 3) == 0) {
            return;
        }
    }
    func_80171A1C(a0);
}


extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171A1C(u8*);
void func_80180060(u8 * a0)
{

    extern s32 D_801151D4;
    s16 buf[3];
    s32 *p;
    p = (s32 *)D_801151D4;
    buf[0] = (s16)p[0xF];   /* 0x3C */
    buf[1] = (s16)p[0x10];  /* 0x40 */
    buf[2] = (s16)p[0x11];  /* 0x44 */
    if (func_80171AB0(a0, buf) == 0) {
        ((void (*)(void *))func_80171A1C)((void *)a0);
    }
}


extern void func_80171A1C(u8 *a0);
    void func_801800C4(s32 *param) {
        param[0x200 / sizeof(s32)] = 1;
        ((void (*)(void))func_80171A1C)();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801800E8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018015C);

DEFINE_func_80180210()  /* dedup: shared engine-core @0x80180210 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180218);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180258);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801802C0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180328);

void func_80180418(void) {
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180420);


extern void (*D_80194EB0[])(void);

void func_8018045C(void *a0) {
    D_80194EB0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_80180498(void *a0)
{
    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        func_80147324(*(u16 *)((s32)a0 + 0x2E));
    }
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



// @class: plumbing
// @stuck: none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

extern void func_8018077C(int);

void func_801804E8(int param_1)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x1c);
    *(int *)(param_1 + 0x1c) = iVar1 + 1;
    if (iVar1 < 0xc) {
        *(unsigned short *)(param_1 + 0x12) = *(unsigned short *)(param_1 + 0x12) + 0xe0;
    } else {
        *(int *)(param_1 + 0x1c) = 0;
        *(unsigned short *)(param_1 + 2) = *(unsigned short *)(param_1 + 2) + 1;
    }
    func_8018077C(param_1);
    return;
}



/* Entity record touched by func_80180544 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */
typedef struct Ent_8017BFE0_80180544 {
    u8  pad00[2];   /* 0x00 */
    u16 f02;        /* 0x02 */
    u8  pad04[0x18];/* 0x04 */
    s32 f1c;        /* 0x1C */
    u8  pad20[0xA]; /* 0x20 */
    u16 f2a;        /* 0x2A */
    u16 f2c;        /* 0x2C */
    u8  pad2e[2];   /* 0x2E */
    s32 f30;        /* 0x30 */
} Ent_8017BFE0_80180544;

extern void func_80147324(s32 arg0);
extern void func_8018077C(int);

void func_80180544(Ent_8017BFE0_80180544 *param_1)
{
    s32 t;

    t = param_1->f1c;
    param_1->f1c = t + 1;
    if (t < 0x20) {
        param_1->f2a = param_1->f2a - 0x10;
    } else {
        if (param_1->f30 == 0) {
            func_80147324(param_1->f2c);
        }
        param_1->f1c = 0;
        param_1->f02 = param_1->f02 + 1;
    }
    ((void (*)(Ent_8017BFE0_80180544 *))func_8018077C)(param_1);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801805C8);

extern void func_8018077C(int);
extern void func_80146C3C(void);
void func_80180730(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8018077C(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018077C);


extern void (*D_80194EC4[])(void);

void func_80180A88(void *a0) {
    D_80194EC4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_80180AC4(void *a0)
{
    func_80147324(*(u16 *)((s32)a0 + 0x2E));
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



/* func_80180B04 — a state-tick: bump the frame counter at 0x1C; while it is
 * below 0xC spin the angle at 0x12 by 0xE0, otherwise reset the counter, zero
 * the vector at *(0x34)+0x60/0x64, set +0x62 to 0x3000 and advance the state
 * word at 0x02.  Falls through to ((void (*)(void *))func_8018077C)(a0) on both arms (the target
 * leaves $a0 untouched, so the call needs no move).
 *
 * §71 sibling-first: func_8017C560 (same TU, 4 bytes earlier) is the same
 * `*(u16 *)(a0 + 2) += 1` idiom, and func_8018077C's own prologue reads
 * `lw $s1, 0x34($s2)` / `lhu $v0, 0x12($s2)` — same record, same widths.
 */

extern void func_8018077C(int);

void func_80180B04(void *a0) {
    s32 t;
    s32 p;

    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    p = *(s32 *)((s32)a0 + 0x34);
    if (t < 0xC) {
        *(u16 *)((s32)a0 + 0x12) += 0xE0;
    } else {
        *(s16 *)(p + 0x64) = 0;
        *(s16 *)(p + 0x60) = 0;
        *(s16 *)(p + 0x62) = 0x3000;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
    ((void (*)(void *))func_8018077C)(a0);
}



/* func_80180B74 — small entity tick:
 *   read counter @0x1C and the sub-object pointer @0x34 up-front, bump the
 *   counter unconditionally (gcc puts that store in the beqz delay slot),
 *   then either slide @0x2A down by 0x10 or run the 3-call teardown. */

extern void func_80147324(s32 arg0);
extern void func_80147084(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_8018077C(int);

void func_80180B74(void *a0)
{
    s32 t;
    s32 *sub;

    t = *(s32 *)((s32)a0 + 0x1C);
    sub = *(s32 **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        *(u16 *)((s32)a0 + 0x2A) = *(u16 *)((s32)a0 + 0x2A) - 0x10;
    } else {
        func_80147324(*(u16 *)((s32)a0 + 0x2C));
        func_80147084(sub);
        func_801472B4(sub);
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
    ((void (*)(void *))func_8018077C)(a0);
}



extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8018077C(int);

void func_80180C00(void *a0)
{
    void *obj;
    s32 t;
    s16 i;
    u16 v;
    u16 w;

    t = *(s32 *)((s32)a0 + 0x1C);
    obj = *(void **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        v = *(u16 *)((s32)obj + 0x64) + 0x80;
        w = *(u16 *)((s32)obj + 0x62) - 0x100;
        *(s16 *)((s32)obj + 0x64) = v;
        *(s16 *)((s32)obj + 0x60) = v;
        *(s16 *)((s32)obj + 0x62) = w;
        i = 0;
        do {
            func_80146A6C(0x1B, obj, 0, 0, 0, 1, 0);
            i++;
        } while (i < 3);
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
    ((void (*)(void *))func_8018077C)(a0);
}


extern void func_8018077C(int);
extern void func_80146C3C(void);
void func_80180CD4(void *a0)
{
    void *obj;
    s16 v;
    v = *(u16 *)((s32)a0 + 0x12) - 0x100;
    obj = *(void **)((s32)a0 + 0x34);
    *(s16 *)((s32)a0 + 0x12) = v;
    if (v > 0) {
        ((void (*)(void *))func_8018077C)(a0);
    } else {
        *(s16 *)((s32)obj + 0x64) = 0x1000;
        *(s16 *)((s32)obj + 0x62) = 0x1000;
        *(s16 *)((s32)obj + 0x60) = 0x1000;
        func_80146C3C();
    }
}



extern void (*D_80194ED8[])(void);

void func_80180D28(void *a0) {
    D_80194ED8[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_80180D64 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
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

void func_80180D64(void *a0)
{
    s32 p;
    s32 obj;
    short r;
    u16 t;
    u16 t2;
    u16 e;
    u16 c;
    u16 d;

    p = (s32)a0;
    obj = *(s32 *)(p + 0x34);
    r = rand();
    *(u16 *)(p + 0x06) = *(u16 *)(obj + 0x06) + ((r & 0x3F) - 0x20);
    if (*(s32 *)(p + 0x2C) != 0) {
        t = *(u16 *)(obj + 0x0A);
        *(s16 *)(p + 0x16) = 0x20;
        *(u16 *)(p + 0x0A) = t - 0x140;
    } else {
        t2 = *(u16 *)(obj + 0x0A);
        *(s16 *)(p + 0x16) = -0x20;
        *(u16 *)(p + 0x0A) = t2;
    }
    e = *(u16 *)(obj + 0x0E);
    c = *(u16 *)(p + 0x02);
    *(s32 *)(p + 0x30) = (r >> 12) & 3;
    d = ((r >> 6) & 0x3F) - 0x20;
    *(u16 *)(p + 0x0E) = e + d;
    d = c + 1;
    *(u16 *)(p + 0x02) = d;
}


extern void func_800D22E4(s32 a0);
extern void func_80146C3C(void);
extern void func_80180E74(void *a0);
void func_80180E18(void *a0)
{
    s32 t;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0xA) {
        ((void (*)(void))func_800D22E4)();
        func_80180E74(a0);
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180E74);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80180FE4);


extern void (*D_80194FA4[])(void);

void func_80181A64(void *a0) {
    D_80194FA4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80181D74(void);
extern void func_800167B8(s32 a0);

s32 func_80181AA0(s32 a0) {
    func_80181D74();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80181AE4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_80194FAC[])(void);

void func_80181B08(void *a0) {
    D_80194FAC[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80181D9C(void);

s32 func_80181B44(s32 a0) {
    func_80181D9C();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_80181B84(s32 a0) {
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


extern void func_800D1EBC(void);
    void func_80181BF8(void) {
        func_800D1EBC();
    }



extern void (*D_80194FB8[])(void);

void func_80181C18(void *a0) {
    D_80194FB8[*(u8 *)((s32)a0 + 0x15)]();
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_80181C54(u8 *a0) {
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



extern void (*D_80194FC4[])(void);

void func_80181CD0(void *a0) {
    D_80194FC4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80182090(void);
extern void func_800167B8(s32 a0);

s32 func_80181D0C(s32 a0) {
    func_80182090();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80181D50(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_80194FD4;

void func_80181D74(void) {
    ((void (*)(s32 *, s32))func_8016EE40)(&D_80194FD4, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_80194FE0;

void func_80181D9C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_80194FE0, 0x1000000);
}



extern void (*D_8019501C[])(void);

void func_80181DC4(void *a0) {
    D_8019501C[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80181E00);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80181E40);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80181EF4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80181F6C);

#include "common.h"

// func_80181FA0 — MATCH (60 ins), match_one + rtu_match. Two levers:
//  1) §20 pointer-var-to-the-global: `u16 *p = &D_800B99DA;` and read `*p`
//     twice. The bare global would fold %lo into each access independently
//     (two lui/lhu pairs, no $s1); the pointer var force_regs the address so
//     CSE hoists it into the callee-saved $s1 across both calls.
//  2) SEPARATE temps `t` and `u` for the two call results (NOT one reused
//     `t`). gcc-2.7.2 expand_divmod emits `move temp,op0; bgez temp; temp+=d-1`
//     for a signed /2^k; cse.c make_regs_eqv only makes `temp` the canonical
//     reg of the quantity when temp's REGNO_LAST_UID outlives op0's. Reusing
//     one `t` across both calls stretches op0's last-use past temp's, so op0
//     stays canonical and cse rewrites the pair to `bgez $v0` + `addiu
//     $v1,$v0,3` — the copy then fills the delay slot and the function comes
//     out 1 instruction short. Split temps ⇒ op0 dies immediately ⇒ target's
//     `addu $v1,$v0,$zero; bgez $v1; nop; addiu $v1,$v1,3`.
// (The 2nd division still coalesces temp/u into $v0, matching `bgez $v0`.)

extern u16 D_800B99DA;
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80181FA0(s32 param_1) {
    u16 *p = &D_800B99DA;
    s32 t;
    s32 u;

    *(s16 *)(param_1 + 0x20E) = func_80012F74(*(s16 *)(param_1 + 0x20E), 0, 10, 1);
    *(s16 *)(param_1 + 0x12E) = 1;
    t = func_8004787C((*p & 0x3F) << 6);
    *(s16 *)(param_1 + 0x128) = *(s16 *)(param_1 + 0x20E) + t / 4;
    u = func_80047948((*p & 0x3F) << 6);
    *(s16 *)(param_1 + 0x12C) = u / 8;
    if (*(s16 *)(param_1 + 0x13A) != 0) {
        *(s16 *)(param_1 + 0x13A) += *(s8 *)(param_1 + 0x20D);
        *(s16 *)(param_1 + 0x20C) -= 0xE0;
        if (*(s16 *)(param_1 + 0x13A) < 0) {
            *(s16 *)(param_1 + 0x13A) = 0;
            *(s16 *)(param_1 + 0x20C) = 0;
        }
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_80194FF4;

void func_80182090(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_80194FF4, 0x1000000);
}



extern void (*D_80195030[])(void);

void func_801820B8(void *a0) {
    D_80195030[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801820F4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182148);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801821AC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801821FC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182268);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801822F4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182344);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182380);

















extern s32 D_80126CF0;
extern void func_80139914(s32 a0);
void func_801823B8(void)
{
  s32 p = D_80126CF0;
  if (p != 0)
  {
    func_80139914(p);
    D_80126CF0 = 0;
  }
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801823EC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182488);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182564);

extern void func_8012A568(void (*a0)(void));
    extern s32 func_801823EC(s32 a0);
    void func_80182614(void) {
        ((void (*)(void *))func_8012A568)((void *)func_801823EC);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018263C);


extern void (*D_80195048[])(void);

void func_801826D8(void *a0) {
    D_80195048[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182714);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182A08);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182A9C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182AF8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182B88);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182D60);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182DB8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182E68);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182EC8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182FA8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182FF0);


extern void func_8012A828(s32, void*);
    extern short D_801F3EA4;
    void func_80183054(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801F3EA4);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183080);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018312C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183178);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801834EC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183558);

extern void func_8018452C(void);
    void func_8018360C(short *param) {
        param[1] = 0xB;
        func_8018452C();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183630);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183954);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183994);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183B30);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183C2C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801840C0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184134);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018418C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184414);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018446C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018452C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184590);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801845C0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801845F4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184738);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018479C);

extern void func_8012A568(void (*a0)(void));
    extern s32 func_8018263C(s32);
    void func_801847C8(void) {
        ((void (*)(void *))func_8012A568)((void *)func_8018263C);
    }


extern void func_8012A568(void (*a0)(void));
    extern s32 func_801823EC(s32 a0);
    void func_801847F0(void) {
        ((void (*)(void *))func_8012A568)((void *)func_801823EC);
    }


extern void func_80184918(s32 arg0, s32 arg1);
    void func_80184818(s32 arg0) {
        func_80184918(arg0, 0x1D);
    }


extern void func_80184918(s32 arg0, s32 arg1);
    void func_80184838(s32 arg0) {
        func_80184918(arg0, 0x1E);
    }


extern void func_80029124(s32 arg0, s32 arg1);
    void func_80184858(void) {
        func_80029124(0x9E, 1);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018487C);

void func_8018490C(s32 *a0, s32 a1, s16 a2) {
        *(s32 *)((s32)a0 + 0xCC) = a1;
        *(s16 *)((s32)a0 + 0x102) = a2;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184918);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184964);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801849D4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184A28);

extern s32 func_800D0CE0(void);
    s32 func_80184A34(void) {
        return func_800D0CE0() != 0;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184A54);


extern void (*D_801957F8[])(void);

void func_80184ACC(void *a0) {
    D_801957F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184B08);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184C0C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184C98);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184D50);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184E00);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80184F48);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185048);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185098);


extern void (*D_801958B8[])(void);

void func_80185120(void *a0) {
    D_801958B8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018515C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185268);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801852B0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185388);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801853CC);

void func_80185464(void *a0) {
        s16 v0;
        v0 = *(s16 *)((char *)a0 + 0xfc);
        if (!v0) {
            *(s16 *)((char *)a0 + 0x2) = 2;
        }
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185480);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801854DC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185548);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018567C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018576C);


extern void (*D_801958E8[])(void);

void func_801859E0(void *a0) {
    D_801958E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185A1C);

void func_80185A84(void) {
}

















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80185A8C(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 1);
  new_var = 0x100000;
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185AAC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185BA4);

u16 func_80185BF4(s32 *a0) {
    return *(u16*)((s32)a0 + 0x34);
}


extern void func_8001AAA0(s32 arg);
    void func_80185C00(void) {
        func_8001AAA0(0x2F);
    }


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80185C20(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 3);
  new_var = 0x51AB;
}


extern void (*D_80195948[])(void);

void func_80185C40(void *a0) {
    D_80195948[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185C7C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185E20);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185FA0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186070);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186184);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801861FC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186250);

s32 func_80186290(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x6;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801862A4);

extern s32 func_80188168(void);
    void func_80186354(void) {
        func_80188168();
    }


extern s32 func_8013CAE8(void);
    void func_80186374(void) {
        func_8013CAE8();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186394);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801863D4);


extern void (*D_80195CC4[])(void);

void func_801863F4(void *a0) {
    D_80195CC4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186430);

void func_80186548(s32 *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186558);

void func_801865B0(s32 arg0) {
        s32 *p = *(s32 **)((s32)arg0 + 0xcc);
        *(u16 *)((s32)p + 0x8) = *(u16 *)((s32)arg0 + 0x6);
        *(s16 *)((s32)p + 0xa) = *(u16 *)((s32)arg0 + 0xa) - 0xe0;
        *(s16 *)((s32)p + 0xc) = *(u16 *)((s32)arg0 + 0xe) - 0x10;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801865E4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186680);

extern s32 func_8017E358(void);
    void func_801866E8(void) {
        func_8017E358();
    }


extern void func_8017E43C(void);
    void func_80186708(void) {
        func_8017E43C();
    }


void func_80186728(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }


void func_80186734(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x3;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186740);


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80186790(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x4;
        func_8002D4C8(0x634, 0);
    }


void func_801867BC(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0;
    }



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_80186818(u8 *a0);
extern void (*D_80195D18[])(int);

void func_801867CC(int param_1)
{
    ((void (*)(void))func_80186818)();
    D_80195D18[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186818);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186868);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186AA0);


extern void (*D_80195D40[])(void);

void func_80186AE0(void *a0) {
    D_80195D40[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186B1C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186BB0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186C30);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186CB4);

void func_80186D3C(void) {
}

void func_80186D44(void) {
}

extern s32 func_80128ED8(void *a0, void *a1);
    extern s32 D_801EB518;
    void func_80186D4C(void *arg0) {
        ((void (*)(s32, s32))func_80128ED8)(M2C_FIELD(arg0, s32 *, 0xCC), &D_801EB518);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186D78);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186E24);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186E94);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186F24);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186F74);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187018);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018707C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801870D0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187110);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801871CC);

extern s32 func_80186740(void);
    void func_80187234(void) {
        func_80186740();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187254);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801872B4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018734C);


extern void (*D_80195D50[])(void);

void func_801873FC(void *a0) {
    D_80195D50[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187438);

void func_801874A0(void) {
}


extern void (*D_80195D58[])(void);

void func_801874A8(void *a0) {
    D_80195D58[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801874E4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018754C);

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void);
void func_80187614(s32 a0) {
    func_8012AD80(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C098)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187654);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187724);


extern void (*D_80195DC4[])(void);

void func_80187784(void *a0) {
    D_80195DC4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801877C0(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);
void func_801877C8(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8012AD50)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187800);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187838);


extern void (*D_80195F14[])(void);

void func_8018788C(void *a0) {
    D_80195F14[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801878C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018797C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187CE8);


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_80195FD8[])();

void func_80187D90(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_80195FD8[*(u16 *)(param_1 + 2)]();
    }
}


extern s32 func_8012AD50(void *a0);
    void func_80187DDC(u8 *a0) {
        *(u16 *)(a0 + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187E08);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80187FA0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188034);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188114);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188168);


// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x18 store AND arg5; writing D_800C7C60=0x18 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEFA0;
extern int D_801E8C34;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801881BC(int arg0)
{
    int *p = &D_800C7C60;
    *p = 0x18;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEFA0, D_801E8C34, p);
}


extern s32 D_8012704C;
    void func_80188214(void) {
        D_8012704C = 0x1;
    }



extern s32 D_801EBA74;

void func_80188228(void) {
    D_801EBA74 = 640;
}



extern s32 D_801EBA74;

void func_8018823C(void) {
    D_801EBA74 = 272;
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188250);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_801883C8(void) {
        func_8002D4C8(0x6AA, 0);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801883EC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188430);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188508);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188554);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188654);



extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801887C8(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D3B74);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801887F8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018898C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188A10);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188D54);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188D80);


extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80188DC8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188DF4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188E3C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189050);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801890C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801891E8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189324);


extern void (*D_801960D4[])(void);

void func_801894E0(void *a0) {
    D_801960D4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018951C);


extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801895A0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D3B74);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801895CC);


extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80189620(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 12;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018964C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189674);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801896B4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018974C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801897A4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018983C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189880);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801898C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801899B4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189A50);


extern void (*D_801961D4[])(void);

void func_80189B28(void *a0) {
    D_801961D4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189B64);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189C20);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189C90);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189E00);

extern s32 func_800D0CE0(void);
    extern void func_8012C218(void *a0);
    void func_80189EF4(void *a0) {
        if (((s32 (*)(s32))func_800D0CE0)((s32)a0) == 1) {
            ((void (*)(s32))func_8012C218)((s32)a0);
        }
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80189F30);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A084);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A184);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A1A4);

extern void func_8012A4BC(void);
    void func_8018A264(void) {
        ((s32 (*)(void))func_8012A4BC)();
    }



extern void (*D_801D6268[])(void);

void func_8018A284(void *a0) {
    D_801D6268[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A2C0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A438);


extern void (*D_801D626C[])(void);

void func_8018A5E4(void *a0) {
    D_801D626C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_8018A620(void) {
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A640);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A698);

void func_8018A708(void) {

    extern s16 D_801EB6E4;
    s16 *p = &D_801EB6E4;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_8018A72C — cookbook §71 (sibling-first).
 * func_8018A7CC is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_8018A7CC(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_8018A8E8 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
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

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Rec_8018A6A4_8018A72C;

extern void func_8018A7CC(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018A8E8(s32 arg0, Rec_8018A6A4_8018A72C *arg1, s32 arg2, s32 arg3);

void func_8018A72C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_8018A72C sp10;
    s32 i;
    s32 ang;

    func_8018A7CC(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_8018A8E8(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



extern s16 D_801EB6DC;
    extern s16 D_801EB6DE;
    extern s16 D_801EB6E0;
    extern s16 D_801EB6E2;
    void func_8018A7CC(s32 arg0, s32 arg1, s32 arg2) {
        D_801EB6DC = *(u16 *)((s32)arg0 + 0x0);
        D_801EB6DE = *(u16 *)((s32)arg0 + 0x2);
        D_801EB6E0 = arg1;
        D_801EB6E2 = arg2;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A7FC);


extern s16 D_801EB6E2;
    void func_8018A874(s32 arg0) {
        *(s16 *)((s32)&D_801EB6E2 + 0x0) += arg0;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A890);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A8E8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A9BC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018A9F8);


/* func_8018AA44 — 16-entry table walk, stride 0xE, over D_801EB6E4.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801EB6E4; s16 *p = &D_801EB6E4; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_8018AB20(s32 arg0);

void func_8018AA44(void) {

    extern s16 D_801EB6E4;
    s16 *p = &D_801EB6E4;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_8018AB20(i);
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


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018AB20);

void func_8018ADE4(void) {

    extern s16 D_801EB5DC;
    s16 *p = &D_801EB5DC;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018AE08);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018AE30);


extern void func_8018AF24(void *a0, void *a1, s16 a2);
extern void func_8018B058(s32 a0, s16 a1, u16 a2);

void func_8018AEB8(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_8018AF24(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_8018B058(i, j, arg3);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018AF24);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018AF94);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B00C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B058);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B174);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B1B0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B2C4);

#include "common.h"

/* func_8018B5A8 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_8018B60C((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8018B60C();

void func_8018B5A8(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_8018B60C)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B60C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018B76C);

#include "common.h"

/* func_8018B950 — quadrant-folded sine lookup over a 0x400-entry u16 table.
 *
 * asm evidence:
 *   Q0 (a<0x400)          : lh   tbl[a]
 *   Q1 (a-0x400 < 0x400)  : lh   tbl[0x7FF - a]
 *   Q2 (a-0x800 < 0x400)  : lhu  tbl[a - 0x800], negu, sll/sra 16
 *   Q3 (a-0xC00 < 0x400)  : lhu  tbl[0xFFF - a],  negu, sll/sra 16
 *   else                  : NO value is produced at all (see below)
 *
 * The `lhu` + `negu` + 16-bit sign-extend in Q2/Q3 pins BOTH types:
 *   - the table element is UNSIGNED (zero-extending load feeding the negate), and
 *   - the result is truncated back to 16 bits => the function returns s16.
 * (An s16 table would give `lh`; an s32 return would drop the sll/sra pair.)
 *
 * Q2's base is D_801D56C8 == D_801D66C8 - 0x1000: gcc folded the `- 0x800`
 * element offset into the symbol addend and indexes with the raw parameter
 * (`sll $v0, $a0, 1`). Writing `tbl[a0 - 0x800]` reproduces that exactly.
 *
 * LOAD-BEARING: there is deliberately NO trailing `return 0;`.  The original
 * falls off the end of a non-void function, so the out-of-range path returns
 * whatever `$v0` happens to hold — which is the failing `sltiu` result, i.e. 0.
 * That is why the target's last test is `beqz $v0, .L8018BA04` + a bare `nop`
 * delay slot (gcc may not clobber $v0 on the taken edge) with no `move $v0,
 * $zero` anywhere.  Adding `return 0;` costs 2 instructions AND lets
 * find_cross_jump tail-merge the Q2/Q3 `negu; sll; sra` tails (cookbook §5a):
 * 45 ins / 19 mismatched instead of MATCH.
 */

extern u16 D_801D66C8[];

s16 func_8018B950(u32 a0)
{
    if (a0 < 0x400) {
        return D_801D66C8[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801D66C8[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801D66C8[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801D66C8[0xFFF - a0];
    }
}


#include "common.h"

/* func_8018BA0C — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801D66C8); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801D66C8)[a - 0x400]  ->  base ((s16 *)D_801D66C8)-0x800 = D_801D5EC8, index a*2
 *   ((s16 *)D_801D66C8)[a - 0xC00]  ->  base ((s16 *)D_801D66C8)-0x1800 = D_801D4EC8, index a*2
 * so no extra externs are needed for D_801D5EC8 / D_801D4EC8.
 *
 * Types: the positive quadrants return the `lh` value straight through (already
 * sign-extended, no sll/sra); the negative quadrants take an explicit (s16) cast on
 * the negation, which forces the truncate -> the return's sign-extend becomes the
 * `sll 16 / sra 16` pair, and combine downgrades those loads to `lhu`.  Writing the
 * arms as four flat `return`s (not one shared s16 local) keeps the extension OFF the
 * positive quadrants; cross-jump then merges the two `sll/sra` tails.
 *
 * The tail has NO `return 0`.  A trailing `return 0` costs an extra `move $v0,$zero`
 * block AND lets dbr steal `sll $v0,$a0,1` into the final beqz delay slot (target has
 * a `nop` there).  Falling off the end keeps `expand_function_end`'s `(use $v0)` live
 * over the epilogue, so the delay slot stays empty and the branch lands straight on
 * the shared `jr $ra` with the `sltiu` zero already in $v0 — which IS the 0 the
 * caller observes.  Same shape as the sibling func_8018B950.
 */

extern u16 D_801D66C8[];

s32 func_8018BA0C(u32 a0v)
{
    if (a0v < 0x400) {
        return ((s16 *)D_801D66C8)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801D66C8)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801D66C8)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801D66C8)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}


extern void func_8012C098(void);
    void func_8018BAB8(void) {
        func_8012C098();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BAD8);

#include "common.h"

/* func_8018BB44 — light/colour ramp-up on the entity's attached prim block.
 *
 * If the s16 flag at 0xFE is set, bump the three u16 colour words at
 * 0x18/0x1A/0x1C of the block pointed to by the word at 0x20 by 0x40 each,
 * then clamp all three to 0x1800 once the first one reaches it.
 *
 * Widths pinned off the target: `lh` at 0xFE and at 0x18 (the signed compare),
 * `lhu` for the three read-modify-writes, `sh` for every store.  The pointer at
 * 0x20 is re-loaded before each RMW (the `sh` stores may alias it), which is
 * exactly what writing the deref inline gives.
 */
void func_8018BB44(int param_1) {
    int v1;

    if (*(short *)(param_1 + 0xfe) != 0) {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x18) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1a) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1c) += 0x40;
        v1 = *(int *)(param_1 + 0x20);
        if (*(short *)(v1 + 0x18) >= 0x1800) {
            *(short *)(v1 + 0x1c) = 0x1800;
            *(short *)(v1 + 0x1a) = 0x1800;
            *(short *)(v1 + 0x18) = 0x1800;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BBCC);

#include "common.h"

// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @stuck: none - MATCH (41 ins), match_one + rtu_match.
// Three levers, in the order they mattered:
//  1) The `mult` sitting in BOTH branch arms is a dbr DELAY-SLOT STEAL from the
//     join block, not two multiplies in the source. The C selects the
//     MULTIPLICAND in the arms (`m`), and multiplies ONCE after the join.
//     That also makes the product a LOCAL allocno, so local-alloc coalesces
//     expand_divmod's `copy_to_mode_reg` temp away -> no `move v0,a0`, and the
//     bgez/addiu/shift all run in-place on $v0 (this was the whole 8-22 residual).
//  2) `srl` (not `sra`) for the /0x1000: the quotient's ONLY use must be a
//     narrowing store, i.e. hold it in an `s16 t`. combine's force_to_mode then
//     rewrites ASHIFTRT->LSHIFTRT because the high bits are discarded. Storing
//     `v / 0x1000` inline (2 SImode uses) keeps `sra`.
//  3) `m` must be `s32`, not `s16` - a narrow local costs lhu+sll+sra (loose
//     typing); the s32 local keeps the plain `lh`.
//  4) `p` and `q` are two SEPARATE variables so the reloaded 0x20 pointer lands
//     in $a0 rather than re-using $v1.

extern s32 func_8004787C(s32 a0);
extern s16 D_80126CE0;

void func_8018BC10(s32 param_1) {
    s32 v;
    s32 p;
    s32 q;
    s32 m;
    s16 t;

    v = func_8004787C(0x400 - (D_80126CE0 * 8));
    if (*(s16 *)(param_1 + 0xAA) == 0) {
        m = *(s16 *)(param_1 + 0x100);
    } else {
        m = *(s16 *)(param_1 + 0x102);
    }
    p = *(s32 *)(param_1 + 0x20);
    t = (v * m) / 0x1000;
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;
    q = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(q + 0x18) <= 0) {
        *(s16 *)(q + 0x1C) = 1;
        *(s16 *)(q + 0x18) = 1;
    }
}



void func_8018BCB4(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BCC4);


// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);
extern void D_801DEB58;

void func_8018BD70(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801DEB58)) {
        func_8012A828(arg0, &D_801DEB58);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BDB8);


extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DEFE0;

void func_8018BE00(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801DEFE0);
    *(s32 *)(a0 + 0x1C) = 0x14;
}



// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_8018BEF0 else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_8018BEF0(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DEF38;

s32 func_8018BE40(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_8018BEF0(param_1);
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
    func_8012A828(param_1, &D_801DEF38);
    return 1;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801DECF8;

void func_8018BEF0(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801DECF8);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_8018BF4C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 5;
        *(int *)((char *)a0 + 0x1c) = 0x14;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BF60);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018BFBC);


extern void (*D_801D6FDC[])(void);

void func_8018C040(void *a0) {
    D_801D6FDC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801D7024[])(void);

void func_8018C07C(void *a0) {
    D_801D7024[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (clean if/else, sh into delay slot of func_8001CA88 call)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern void func_80143994(s32 a0, s32 a1);
extern int D_801D6FE4;

void func_8018C0B8(int param_1)
{
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        *(short *)(param_1 + 2) = 1;
        func_8001CA88(*(int *)(param_1 + 0x20), &D_801D6FE4);
        func_80143994(param_1, 0x1000);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C11C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C174);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C1E0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C31C);

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018BF60(void *a0);
void func_8018C388(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8018BF60)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C3C0);


// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018BF4C(void*);

void func_8018C424(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_8018BF4C)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C47C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C534);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C5A4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C734);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C7B8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C874);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C968);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CA04);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CA64);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CAC4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CB20);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CB70);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CBBC);

















void func_8018CC6C(void *a0)
{
  s32 v1 = *((s32 *) (((s32) a0) + 0x20));
  int new_var;
  *((s16 *) (((s32) a0) + 0x2)) = 0xA;
  *((s16 *) (((s32) a0) + 0x5C)) = 0;
  *((s16 *) (((s32) a0) + (new_var = 0x34))) = 0;
  *((s32 *) (((s32) a0) + 0x1C)) = 0x8;
  *((s16 *) (((s32) v1) + 0x2C)) |= 0x10;
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CC9C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CEB0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CF04);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CFAC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018CFF4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D0C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D128);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D19C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D1D8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D218);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D288);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D370);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D52C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D574);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D720);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D820);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018D8B8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DAA8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DBF4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DD60);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DDD0);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DE30);


extern void (*D_801DF7B0[])(void);

void func_8018DF08(void *a0) {
    D_801DF7B0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018DF44);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E014);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E0AC);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E208);


extern void (*D_801DF818[])(void);

void func_8018E358(void *a0) {
    D_801DF818[*(u16 *)((s32)a0 + 0x2)]();
}



void func_8018E394(void *a0) {
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s32 *)((char *)a0 + 0x1c) = 2;
        *(s8 *)((char *)a0 + 0xfc) = 1;
        *(s8 *)((char *)a0 + 0xfe) = 2;
        *(s8 *)((char *)a0 + 0xfd) = 0;
        *(s8 *)((char *)a0 + 0xff) = 4;
        *(s16 *)((char *)a0 + 0xdc) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E3C8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E420);


extern void (*D_801DF84C[])(void);

void func_8018E4BC(void *a0) {
    D_801DF84C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E4F8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E5E4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E678);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E780);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018E8A0);


extern void (*D_801DF89C[])(void);

void func_8018EBEC(void *a0) {
    D_801DF89C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018EC28);


extern void (*D_801E33D8[])(void);

void func_8018ECA8(void *a0) {
    D_801E33D8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018ECE4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018EDB8);

void func_8018EDE0(void) {
}

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018EDE8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018EF34);


extern void func_8012C218(void *a0);
    s32 func_8018F054(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_8018F080(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_8018F090(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018F0A0);


extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_8018F0E0(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_8018F114(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018F138);


extern void (*D_801E3400[])(void);

void func_8018F19C(void *a0) {
    D_801E3400[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018F1D8);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018F260);


/* func_8018F320 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801E3AC0, else
 * D_801E38A0), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801E3AC0 / D_801E38A0)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_8018F320(void *a0) {

    extern u8 D_801E3AC0[];
    extern u8 D_801E38A0[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801E3AC0);
        } else {
            func_8012A828((s32)a0, D_801E38A0);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018F390);


extern s32 D_801EB908;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018F488(s32 a0, s32 a1) {
    D_801EB908 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801EB908;
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




s32 func_8018F4B8(s32 param_1) {

    extern M2C_UNK D_8019105C;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801E3AE4;
    extern char * D_801E3B18;
    extern char D_801EB8E8[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801E3AE4) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8019105C));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801EB908, &s60);
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
        tmp = D_801E3B18;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801E3B18 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801EB8E8 < puVar4) {
        D_801E3B18 = D_801EB8E8 - 0x120;
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
            tmp = D_801E3B18;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801E3B18 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801EB8E8 < puVar4) {
            D_801E3B18 = D_801EB8E8 - 0x120;
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

s32 func_8018F6FC(s32 param_1) {

    extern signed char D_801E3AD0[];
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
        p = D_801E3AD0;
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
            p = D_801E3AD0;
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



extern void (*D_801E3B1C[])(void);

void func_8018F99C(void *a0) {
    D_801E3B1C[*(u16 *)((s32)a0 + 0x2)]();
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


void func_8018F9D8(s32 param_1) {

    extern M2C_UNK D_801E439C;
    extern u8   D_801E4174;
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
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801E439C));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801E4174);
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



extern void (*D_801E4210[])(void);

void func_8018FB50(void *a0) {
    D_801E4210[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E4224[])(void);

void func_8018FB8C(void *a0) {
    D_801E4224[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801E41FC;
extern s32 D_801E4208;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_8018FBC8(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801E41FC);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801E4208, (s32)&D_800D3918, 0x19) == 0 &&
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

extern int D_801E4218;

void func_8018FCA8(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801E4218);
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

extern int D_801E44CC;

void func_8018FDC4(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801E44CC);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018FE20);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018FE94);


extern void (*D_801E4858[])(void);

void func_801900B4(void *a0) {
    D_801E4858[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801900F0);


extern void (*D_801E8654[])(void);

void func_80190184(void *a0) {
    D_801E8654[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_8012A828(s32, void *);
extern void func_801904BC(void);

extern u8 D_801E8554[];
extern u8 D_801E38A0[];

void func_801901C0(s32 param_1) {
    s32 v;

    if (((s32 (*)(s32, void *))func_8012C354)(
            param_1, &D_801E8554[(*(u16 *)(param_1 + 0x70) & 0xF) * 0x34]) != 0) {
        if ((*(u16 *)(param_1 + 0x70) & 1) == 0) {
            v = func_8012C658(0x1E3, 1, param_1);
            *(s32 *)(param_1 + 0x6C) = v;
            if (v == 0) {
                ((void (*)(s32))func_8012CAE4)(param_1);
            } else {
                *(s16 *)(param_1 + 0x2) = 1;
                *(s32 *)(param_1 + 0xCC) =
                    ((s32 (*)(s32, void *))func_801788B8)(param_1, func_801904BC);
            }
        } else {
            *(s16 *)(param_1 + 0x2) = 5;
            *(u16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);
            func_8012A828(param_1, D_801E38A0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80190298);

void func_801902C0(void) {
}

extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801E8604;
    void func_801902C8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801E8604);
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801902F4);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80190334);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801903F4);

void func_80190460(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80190470(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80190480);

extern void func_800296F8(void);
    s32 func_80190498(s32 arg0) {
        ((void (*)(s32))func_800296F8)(*(s32 *)(arg0 + 0xdc));
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801904BC);


extern void (*D_801E86CC[])(void);

void func_80190610(void *a0) {
    D_801E86CC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8019064C);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80190748);

INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801909D8);

#include "common.h"

/* func_80190B6C — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_80190B6C(s32 arg0) {
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


#include "common.h"

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32);

void func_80190BC4(s32 arg0) {
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


#include "common.h"

/* func_80190C40 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_80190C40(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}


#include "common.h"

/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);

struct S80190C84 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};

void func_80190C84(s32 a0, u16 *a1, s16 a2) {
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





