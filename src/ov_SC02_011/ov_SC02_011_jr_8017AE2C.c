#include "common.h"
#include "../shared/engine_core.h"
#include "ov_SC02_011_shared.h"


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
extern s32 D_801928E8[];
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
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
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
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
extern u16 D_80126B66;
extern s16 D_801EB10C;
extern u16 D_801EB18C;
extern u16 D_801EB18E;
extern u16 D_801EB190;
extern s16 D_801EBA08;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
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
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
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


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017C294(s32 a0, s16 *a1, s16 a2) {
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


void func_8017C360(s32 a0) {

    extern u8 D_80194744[];
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
    s0 = func_800D21C4(a0, D_80194744, 0x2A);
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



extern void (*D_80194750[])(void);

void func_8017C4BC(void *a0) {
    D_80194750[*(u16 *)((s32)a0 + 0x2)]();
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

void func_8017C4F8(void *a0)
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



/* func_8017C558 — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801EB1B0..D_801EB1D8 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017C558(s32 param_1, s32 param_2)
{

    extern s32 D_801EB1B0;
    extern s32 D_801EB1B4;
    extern s32 D_801EB1B8;
    extern s32 D_801EB1C0;
    extern s32 D_801EB1C4;
    extern s32 D_801EB1C8;
    extern s32 D_801EB1D0;
    extern s32 D_801EB1D4;
    extern s32 D_801EB1D8;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_8017C558 vec;                              /* sp+0x10 */
    MTX_L_8017C558 mtx;                              /* sp+0x18 */
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

    D_801EB1D0 = vec.a;
    D_801EB1C0 = vec.a;
    D_801EB1B0 = vec.a;
    D_801EB1D4 = vec.b;
    D_801EB1C4 = vec.b;
    D_801EB1B4 = vec.b;
    D_801EB1D8 = vec.c;
    D_801EB1C8 = vec.c;
    D_801EB1B8 = vec.c;
}



/* func_8017C688 — ov_SC02_027_jr_8017AE2C (227 ins).  MATCH (match_one, 227/227).
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
 *   D_801EB1B0     TU:3333      extern s32 D_801EB1B0;
 * func_8012CAE4 / func_8012C354 are absent from the TU; the canonical engine_core.h forms
 * are reused verbatim (DEFINE_func_8012CAE4 @15355 `void func_8012CAE4(void *a0)`,
 * DEFINE_func_8012C354 @15748 `s32 func_8012C354(s32 a0, s32 a1)`).
 * D_80194780 / D_801947BC / D_801E5E08 / every D_801D9E9x-ECx / D_801EB260 appear nowhere
 * in the TU or engine_core.h (only D_801EB1B0..EB8 and D_801D9F00..F06 are declared there).
 * D_801E5E30 is declared BLOCK-SCOPE here on purpose: the TU's only other declaration
 * (TU:3587, `extern Rec_8017C738 D_801E5E30[];`) is itself block-scope inside func_8017C738,
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
 *  2. `tbl` and `tbl2` MUST BE TWO SEPARATE LOCALS.  One shared `tbl` gives the D_801EB260
 *     address pseudo REG_N_SETS==2, which KILLS the birthing boost (birthing_insn_p,
 *     sched.c:2469/2490): the unboosted `la $a0` then floats to the front of the pri-1 group
 *     and lands at index 86, shoving `la $a2,D_801E5E30` to 88 (this was the entire 7-insn
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



void func_8017C688(s32 a0) {

    extern u8 D_80194780[];
    extern u8 D_801947BC[];
    extern s32 D_801E5E08;
    extern u16 D_801152BA;
    extern s16 D_80115214;
    extern s32 D_801EB1B0;
    extern u8 D_801EB1BC;
    extern u8 D_801EB1BD;
    extern u8 D_801EB1BE;
    extern u8 D_801EB1CC;
    extern u8 D_801EB1CD;
    extern u8 D_801EB1CE;
    extern u8 D_801EB1DD;
    extern u8 D_801EB1DE;
    extern u8 D_801EB1E0;
    extern u8 D_801EB1E1;
    extern u8 D_801EB1E2;
    extern u8 D_801EB1E4;
    extern u8 D_801EB1E5;
    extern u8 D_801EB1E6;
    extern u8 D_801EB1EC;
    /* 9 x 12-byte records = 0x6C bytes, alignment 2 */
    extern Blk027_8017C688 D_801E5E30;
    extern Blk027_8017C688 D_801EB260[];

    u8 *v1;
    s32 s1;
    u8 *p;
    s32 t;
    s16 i;
    Blk027_8017C688 *dst;
    Blk027_8017C688 *tbl2;
    s32 idx;
    Blk027_8017C688 *tbl;
    s32 u;
    s32 w;

    v1 = *(u8 **)(a0 + 0xDC);
    if ((func_800291B4(v1[0] + 0x3A) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    if (*(s32 *)(a0 + 0x20) == 0) {
        if (func_8012C354(a0, (s32)D_80194780) == 0) {
            return;
        }
        func_8001C810(*(s32 *)(a0 + 0x20), (s32)&D_801E5E08);
        func_8012A828(a0, (void *)&D_801947BC[(s16)D_801152BA * 16]);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x20;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)&D_801EB1B0;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)(a0 + 0xAE) = -3;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 == 0) {
        return;
    }

    p = &D_801EB1E0;
    *(s32 *)(a0 + 0xCC) = s1;
    func_8001CD50(s1, (s32)p);

    D_801EB1E2 = 0x80;
    *p = 0x80;
    D_801EB1E1 = 0xE0;
    D_801EB1E5 = 0;
    D_801EB1E4 = 0;
    D_801EB1E6 = 0;
    func_800233CC(p, 0x38);

    tbl = D_801EB260;
    idx = (s16)D_801152BA;
    dst = &tbl[idx];
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x8) = *(u16 *)(a0 + 0x6);
    t = *(u16 *)(a0 + 0xA) - 4;
    *(u16 *)(a0 + 0xA) = t;
    *(s16 *)(s1 + 0xA) = t;
    *(s16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(s1 + 0x4) |= 0x50000000;

    D_801EB1DE = 0xFF;
    D_801EB1EC = 0xFF;
    D_801EB1CE = 0xFF;
    D_801EB1CC = 0xFF;
    D_801EB1BE = 0xFF;
    D_801EB1BC = 0xFF;
    D_801EB1DD = 0x80;
    D_801EB1CD = 0x80;
    D_801EB1BD = 0x80;

    *dst = D_801E5E30;

    i = 5;
    tbl2 = D_801EB260;
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
 *   func_8017C558  TU:3465/3542 (void return)
 *   D_80115214     TU:3547
 * func_8012BD14 / D_801947B4 / D_80194818 appear nowhere in the TU; the
 * canonical engine_core.h form of func_8012BD14 is `void func_8012BD14(s32)`
 * (DEFINE_func_8012BD14), so it is declared void and the s32 return is taken
 * through a cast at the call site (idiom 9). */
extern s32 func_800291B4(s32 arg);
extern s16 currentLocationId;
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_801746A4(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017C558(s32 a0, s32 a1);
extern void func_8012BD14(s32 a0);

void func_8017CA14(s32 a0) {

    extern u8 D_80126B5C;
    extern u8 D_801202A0[];
    extern u16 D_80126B62;
    extern s16 D_80115214;
    extern u8 D_801947B4[];
    extern u8 D_80194818[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
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
    func_8017C558(a0, rand_val & 0xF);

    if (*(u16 *)(a0 + 0x5E) != 0) {
        for (i = 0; (u16)i < 8; i++) {
            if (*(u16 *)(a0 + 0x5E) == D_801947B4[i]) {
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
        func_80178B18(a0, (s32)D_80194818);
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
 * in the .s are D_801EB424/108/10C, with $s0 = D_801EB424 - 0x14. */

void func_8017CC8C(s32 a0) {

    extern u8 D_801EB220;
    extern u8 D_801EB221;
    extern u8 D_801EB222;
    extern u8 D_801EB224;
    extern u8 D_801EB225;
    extern u8 D_801EB226;
    extern s32 D_801EB424[];
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801EB220;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801EB221 = 0xFF;
    D_801EB222 = 0xFF;
    *p = 0xFF;
    D_801EB226 = 8;
    D_801EB224 = 8;
    D_801EB225 = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801EB424[0] = sp[0];
    D_801EB424[1] = sp[1];
    D_801EB424[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801EB424[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801EB424[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017C558(s32 a0, s32 a1);

void func_8017CDD4(s32 a0) {
    extern Rec_8017C738_8017CDD4 D_801E5E30[];

    Rec_8017C738_8017CDD4 *q = D_801E5E30;
    Rec_8017C738_8017CDD4 *p = *(Rec_8017C738_8017CDD4 **)(a0 + 0xD8);
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
        func_8017C558(a0, 0);
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



extern void (*D_80194868[])(void);

void func_8017CF54(void *a0) {
    D_80194868[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017CF90(void) {
    func_8014BCEC((s32)&D_80126B58, 0x5);
    func_8014BD24((s32)&D_80126B58, 0x270F);
    func_8002D4C8(0xBFE, 0);
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017C558(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_8017CFDC(void *a0) {

    extern u16 D_801152BA;
    extern s16 D_80115214;
    void *v1;
    void *s2;
    void *s1;
    u16 arg;
    s16 v0_s16;
    u16 tmp;
    s32 v0;
    s32 rand_val;
    s32 pads[4];  /* Force stack frame to 0x30 bytes */

    v1 = *(void **)(a0 + 0xDC);
    s2 = *(void **)(a0 + 0xCC);
    s1 = *(void **)(a0 + 0xD0);

    if (*(u8 *)(v1 + 1) != 0) {
        if (*(s16 *)(a0 + 0x108) == 0) {
            arg = *(u16 *)(v1 + 2);
            v0_s16 = func_80128CFC(arg);
            *(s16 *)(a0 + 0x108) = v0_s16;
        }
    }

    tmp = *(u16 *)((s32)s1 + 0x1A) + 0x20;
    *(u16 *)((s32)s1 + 0x1A) = tmp;
    *(u16 *)((s32)s1 + 0x18) = tmp;

    v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;

    if (v0 != -1) {
        rand_val = rand();
        func_8017C558((s32)a0, rand_val & 1);
    } else {
        D_80115214 = 4;
        D_801152BA -= 1;
        func_8002D4C8(0x62E, 0);
        *(u16 *)s2 = 0;
        *(u16 *)(a0 + 2) += 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
    }
}



extern s16 func_80128CFC(u16 a0);

void func_8017D0D0(void *a0) {
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

void func_8017D150(s32 a0) {
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

void func_8017D204(s32 a0) {
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

void func_8017D270(s32 a0) {
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
    void func_8017D2FC(void) {
        ((void (*)(void))func_8012C218)();
    }




void func_8017D31C(s32 a0) {
    extern int func_80178970(void);
    extern void func_80178D18(void);
    s32 rand_val = rand();

    func_8017C558(a0, rand_val & 0xF);
    if (((s32 (*)(s32))func_80178970)(a0) == 0) {
        return;
    }
    ((void (*)(s32))func_80178D18)(a0);
    *(s16 *)(a0 + 0x2) = 1;
}


extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012CAE4(void *a0);
extern s32  func_8012C354(s32 a0, s32 a1);
extern s32  func_80143970(s32 a0);

/* --- overlay-local data; none of these are declared anywhere in the TU. --- */

void func_8017D370(void *a0) {

    extern u8 D_80078E78[];
    extern s16 D_801EB430;
    extern u8  D_80194B58[];
    extern u8  D_80194A2C[];
    extern u8  D_80194894[];
    extern u8  D_80194A60[];
    extern s32 D_801EB434;
    extern s32 D_801EB438;
    /* §17 base-pointer cache: the D_80078E78 base is read ONCE at +0x1A but the original
       still pinned it in callee-saved $s1 across the first call -- that only happens when
       the base is a pointer LOCAL, not a direct D_80078E78[0x1A] (which folds %lo per use). */
    u8 *p = D_80078E78;
    s32 t;

    if ((u8)func_80029178(D_80194B58[*(s16 *)((s32)a0 + 0x70)]) != 0 ||
        (*(s16 *)((s32)a0 + 0x70) == 4 && (u32)func_80029504() < 0xC8)) {
        func_8012CAE4(a0);
        return;
    }

    t = *(u16 *)(p + 0x1A);
    if (t < 0x12C || t > 0x527) {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_80194A2C) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x5C) |= 0x10;
        func_8012A828((s32)a0, D_80194894);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)&D_801EB430 = *(s16 *)((s32)a0 + 0x88) << 16;
        D_801EB434 = *(s16 *)((s32)a0 + 0x8A) << 16;
        D_801EB438 = *(s16 *)((s32)a0 + 0x8C) << 16;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    } else {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_80194A60) == 0) {
            return;
        }
        *(s16 *)((s32)a0 + 0xAE) = -4;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(u16 *)((s32)a0 + 0x2) = 7;
    }
}


extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017DCC0(s32 a0, s16 a1, s16 a2);
extern void func_8017DD34(s16 *a0);
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
void func_8017D50C(s32 a0) {

    extern void (*D_8019491C[])(void);
    extern s16 D_801EB430;
    extern s32 D_801EB43C;
    extern s32 D_801EB444;
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

        func_8012A828(a0, (void *)&D_8019491C);

        t = *(u16 *)(a0 + 0x10A) + 1;
        *(u16 *)(a0 + 0x10A) = t;

        if ((t & 3) != 0) {
            if (*(s16 *)(a0 + 0x104) == 0) {
                s32 r = rand();
                s32 x;
                s32 y;

                x = *(s16 *)(a0 + 0x88) - 0x200;
                x += (r & 0x7F) << 3;
                D_801EB43C = x << 16;

                y = *(s16 *)(a0 + 0x8C) - 0x200;
                y += (u32)(r & 0x7F00) >> 5;
                D_801EB444 = y << 16;
            } else {
                func_8017DD34((s16 *)a0);
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0xC00;
            }
        } else {
            for (i = 0; i < 2; i++) {
                ((s32 *)&D_801EB43C)[i] = ((s32 *)&D_801EB430)[i];
            }
        }

        i = 8;
        if (*(s16 *)(a0 + 0x108) >= 0xD) {
            i = 2;
        }

        ret = func_8012BB3C(a0 + 4, (s32)&D_801EB43C,
                            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), i);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + ret;

        ang = -3 - *(u16 *)(a0 + 0x104);
        func_8017DCC0(a0, ang, 0x50);

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
extern void func_8017DE10(s32 a0);
extern void func_8017DCC0(s32 a0, s16 a1, s16 a2);
extern void func_8017DD34(s16 *a0);

void func_8017D710(s32 a0) {

    extern u8 D_80194894[];
    extern s32 D_801EB43C;
    extern s32  D_80194AFC;
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
        func_8017DE10(s0);
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
            if (func_8012BC60((void *)(s0 + 4), (void *)&D_801EB43C) < 0x900) {
                *(s32 *)(s0 + 0x1C) = 1;
            }
        }
        /* The func_8017DCC0 call is written in BOTH arms on purpose: gcc-2.7.2's sched1
           interleaves the $a0/$a2 arg setup into each arm's load-delay slots, and only
           then does cross-jumping merge the common tail (it stops at the differing `sh`).
           A single call after the if/else leaves those slots as nops (+2 ins, -1 length)
           and forces the arm pointer into $a0, wrecking the whole block's allocation.
           `ang0`/`ang1` are per-arm locals (§136 L1): one shared local becomes a GLOBAL
           allocno (2 deaths) and loses $a1.  Both must be s32 -- writing the expression
           inline lets convert_to_integer narrow it to UNSIGNED HImode (the u16 operand),
           which emits `ori $a1,$zero,0xfffd` instead of `addiu $a1,$zero,-0x3` + sll/sra. */
        if (*(s16 *)(s0 + 0x106) == 0) {
            s32 r = func_8012BB3C(s0 + 4, (s32)&D_801EB43C,
                                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), 8);
            s32 p = *(s32 *)(s0 + 0x20);
            s32 ang0;
            *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang0 = -3 - *(u16 *)(s0 + 0x104);
            func_8017DCC0(s0, ang0, 0);
        } else {
            s32 q = *(s32 *)(s0 + 0x20);
            s32 ang1;
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + *(s16 *)(s0 + 0x106);
            ang1 = -3 - *(u16 *)(s0 + 0x104);
            func_8017DCC0(s0, ang1, 0);
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
        func_8012A828(s0, D_80194894);
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
               D_80194AFC base already in $a2 (`addiu $a1,$a2,-0x1C`).  Caching the base in
               a POINTER LOCAL reproduces that; `(s32)&D_80194AFC - 0x1C` folds into a
               second lui/addiu pair and splits the store into lui+sw($at). */
            s32 *tbl = &D_80194AFC;

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
        func_8017DCC0(s0, -0xF, 0);
        func_8017DD34((s16 *)s0);
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
                func_8017DD34((s16 *)s0);
                if (*(s16 *)(s0 + 0x104) == 0) {
                    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = func_8012B864(s0) - 0x800;
                    ret = 1;
                }
                *(s16 *)(s0 + 0x104) = spd;
                func_8017DCC0(s0, -7 - spd, 0);
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


void func_8017DB04(s32 a0) {

    extern u8 D_80194894[];
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
    func_8012A828(a0, D_80194894);

    *(s16 *)(a0 + 0x104) = 0;
    *(s16 *)(a0 + 0x102) = 0xA;
    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 4) |= 0x80000000;

    func_801439C0(*(s32 *)(a0 + 0xCC));

    *(s32 *)(a0 + 0x1C) = 0x14;
    *(s16 *)(a0 + 0x2) = 6;
}



extern void (*D_80194B68[])(void);

void func_8017DC84(void *a0) {
    D_80194B68[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_8017DCC0 -- ov_SC03_002 / ov_SC03_002_jr_8017AE2C
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

void func_8017DCC0(s32 a0, s16 a1, s16 a2) {
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

void func_8017DD34(s16 *a0) {

    extern u8 D_80126B5C;
    extern s16 D_801EB430;
    extern s32 D_801EB43C;
    extern s32 D_801EB444;
    extern u8 D_80194A94[];
    extern s16 D_80194AB4[];
    extern s16 D_80194AB6[];
    /* The target frame is 0x28 with only $s0/$s1/$ra saved at 0x18/0x1C/0x20, i.e. 8 bytes
       of locals sit below the register save area and are never touched. The original source
       declared a local it no longer uses; the same fossil is visible in the neighbours
       (func_8017C594 carries 16 such bytes). gcc-2.7.2 still reserves the slot. */
    s32 sp10[2];
    s32 a, b, t, r, off, x, y;

    a = (func_8012B6D4((s16 *)&D_80126B5C, &D_801EB430) >> 7) & 0x18;
    b = func_8012B6D4(a0 + 2, &D_801EB430);
    t = a | ((b >> 9) & 7);
    off = D_80194A94[t] << 2;
    r = rand();

    /* The struct reads are plain INDIRECT_REFs, not ARRAY_REFs: an `a0[0x46]` here sets
       MEM_IN_STRUCT_P, which lets gcc-2.7.2's true_dependence() drop the dependence against
       the constant-address store and hoist the second `lh` above `sw D_801EB43C`. */
    x = *(s16 *)((s32)a0 + 0x88) + *(s16 *)((u8 *)D_80194AB4 + off) - 0x100;
    x += (r & 0x7F) << 2;
    D_801EB43C = x << 16;

    y = *(s16 *)((s32)a0 + 0x8C) + *(s16 *)((u8 *)D_80194AB6 + off) - 0x100;
    y += (unsigned)(r & 0x7F00) >> 6;
    D_801EB444 = y << 16;
}


/* func_8017DE10 -- ov_SC02_011 / ov_SC02_011_jr_8017AE2C   [target: 133 ins]
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


void func_8017DE10(s32 a0) {
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern s32  ratan2(s32 a0, s32 a1);
    extern s16  D_801152B0;
    extern s16  D_801152B4;
    extern s32  func_80133784(s32 a0, void *a1, s32 a2);
    extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void RotMatrixY(s32 a0, void *a1);
    extern Mtx8_8017DE10 D_800AE620;

    u8 in[8];
    u8 out[8];
    Mtx8_8017DE10 m;
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

void func_8017E024(s32 a0) {

    extern u8 D_80194984[];
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
        func_8012A828(a0, D_80194984);

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

void func_8017E0F8(s32 a0) {

    extern void (*D_8019491C[])(void);
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
    func_8012A828(a0, (void*)&D_8019491C);

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

void func_8017E1C8(s32 a0)
{

    extern u8 D_80194B58[];
    if (func_80178970() == 0) return;

    ((void (*)(s32))func_80178D18)(a0);

    func_80029124((s32)D_80194B58[*(s16 *)((s32)a0 + 0x70)], 1);
    ((void (*)(s32))func_8012C218)(a0);
}



extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_8012E778(s32 param_1, s32 param_2);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_801439C0(s32 a0);
extern void func_8012C218(void*);

void func_8017E220(s32 a0)
{

    extern u8 D_80078E78[];
    extern s32 D_80194B38;
    s32 s0 = a0;
    u8 *v1 = D_80078E78;
    s32 v0;

    if (*(s16 *)((u8 *)s0 + 0x100) != 0) {
        goto L_8017D524;
    }

    if (*(u16 *)((u8 *)s0 + 0x5E) == 0) {
        goto L_8017D524;
    }

    func_80178B18(s0, (s32)&D_80194B38);
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

void func_8017E318(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 7;
    }
}


extern void func_80174684(void *);
extern void func_8017E380(void *);

s32 func_8017E358(void)
{
    func_80174684((void *)func_8017E380);
}



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


extern s32 func_801881BC(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32 a0);

void func_8017E3F4(s32 a0) {
    s32 s0 = a0;
    if (func_801881BC(a0) != 0) {
        func_80171A1C((u8 *)s0);
        func_80174650(s0);
    }
}


void func_8017E434(void) {
}

extern void func_80174684(void *);
    extern s32 func_8017E464;
    void func_8017E43C(void) {
        func_80174684(&func_8017E464);
    }




void aF8017E464(void *a0) __asm__("func_8017E464");
void aF8017E464(void *a0)
{

    extern void (*D_80194B98[])(void);
    D_80194B98[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8 *a0);
    extern void func_80171A1C(u8 *a0);
    extern void func_8017E4D8(s32 a0);
    void func_8017E4A0(s32 a0) {
        s32 s0 = a0;
        ((void (*)(s32 *))func_80147060)((s32 *)s0);
        ((void (*)(s32))func_80171A1C)(s0);
        ((void (*)(s32))func_8017E4D8)(s0);
    }


extern s32 func_80188168(void);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32 a0);

void func_8017E4D8(s32 a0) {
    s32 s0 = a0;
    if (func_80188168() != 0) {
        func_80171A1C((u8 *)s0);
        func_80174650(s0);
    }
}


DEFINE_func_8017E518()  /* dedup: shared engine-core @0x8017E518 (src/shared) */

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017E520(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2B, a0, t0, t1, t2, a1, a2);
}



extern void (*D_80194C58[])(void);

void func_8017E564(void *a0) {
    D_80194C58[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E5A0(u8 *a0) {
    s32 frame_pad[10];
    u16 v1;
    u16 v0;
    (void)&frame_pad;
    v1 = *(u16 *)(a0 + 0x2);
    v0 = *(u16 *)(a0 + 0xE);
    v1 += 0x1;
    v0 += 0x10;
    *(u16 *)(a0 + 0xE) = v0;
    *(u16 *)(a0 + 0x2) = v1;
}


extern void func_8017E5F0();
void func_8017E5C8(void) {
    func_8017E5F0();
}


void func_8017E5E8(void) {
}

    extern SVECTOR_8017C290 D_80194C6C[4];
    void func_8017E5F0(void *a0)
    {
        s16 buf20[4];
        SVECTOR_8017C290 c;
        SVECTOR_8017C290 d;
        SVECTOR_8017C290 e;
        SVECTOR_8017C290 f;
        s32 i, j;
        *(s16 *)((u8 *)a0 + 0x10) = *(s32 *)((u8 *)a0 + 0x30);
        func_80015978((s32)a0 + 4, (s32 *)buf20);
        for (j = 0; j < 4; j++) {
            c.vx = 0;
            c.vy = 0;
            c.vz = 0;
            d = c;
            e = c;
            for (i = 0; i < 4; i++) {
                f = D_80194C6C[i];
                *(s16 *)((u8 *)a0 + 0x12) = i + j;
                func_8017E72C((int)a0, buf20, &c, &d, &e, &f, (s16 *)((u8 *)a0 + 0x10));
            }
        }
    }


/* func_8017E72C -- ov_SC02_011, TU ov_SC02_011_jr_8017AE2C.c
 *
 * §136c sibling-first: near-twin is the already-banked func_8017C290 in
 * src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c (same "jr_8017AE2C" family).
 * Reused verbatim from it: the MATRIX/SVECTOR/PW (packed align-1, 4 byte)
 * type trio, the gte_ldv0/gte_rt/gte_stsv inline-asm macros, the whole
 * statement shape and order, and the extern decls for func_80013F3C /
 * RotMatrixZ / func_8004914C / func_800491AC / func_80017714 / rand.
 * Only the data symbols differ (D_801EB4C8 in place of D_801EA8C0, etc.) --
 * none of them appear anywhere else in this TU, so fresh local types are
 * declared here under a _8017E72C suffix.
 */


extern void func_80013F3C(s32 a0);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern int rand(void);
extern void func_80017714(void *);

extern struct PW8017E72C D_80194BA4[];

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

void func_8017E72C(int a, s16 *b, SVECTOR_8017E72C *c, SVECTOR_8017E72C *d,
                   SVECTOR_8017E72C *e, SVECTOR_8017E72C *f, s16 *g)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern SVECTOR_8017E72C D_801EB4C8[4];
    extern struct PW8017E72C D_801EB4E8;
    extern struct PW8017E72C D_801EB4EC;
    extern u8 D_801EB4F0, D_801EB4F1, D_801EB4F2, D_801EB4F4, D_801EB4F5, D_801EB4F6;
    extern int D_801EB4F8;
    MATRIX_8017E72C m;
    SVECTOR_8017E72C *r0_00;
    SVECTOR_8017E72C *pSVar6;
    SVECTOR_8017E72C *r0;
    int r;
    int mask;

    func_80013F3C((s32)&m);
    RotMatrixZ(g[0], &m);
    m.t[0] = b[0];
    m.t[1] = b[1];
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801EB4C8[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801EB4F8 = 0x50000000;
        D_801EB4E8 = D_80194BA4[*(s32 *)(a + 0x2C)];
        D_801EB4EC = D_80194BA4[*(s32 *)(a + 0x2C)];
        D_801EB4F0 = 0;
        D_801EB4F1 = 0;
        D_801EB4F2 = 0;
        D_801EB4F4 = 0;
        D_801EB4F5 = 0;
        D_801EB4F6 = 0;
    }

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


void func_8017EAC0(void *a0, s32 a1, s32 a2) {
    func_80146A6C(0x2C, a0, 0, (s16)a1, 0, a2, 0);
}



extern void (*D_80194C98[])(void);

void func_8017EB00(void *a0) {
    D_80194C98[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146F58(s32 a0, s32 a1);

/* MATCH (match_one, 93/93). ov_SC03_014_jr_8017AE2C, family reach x7 (zero-crack exemplar; see
 * asm/ov_SC03_0{14,15,24,118,119}/... and ov_SC06_000, all still INCLUDE_ASM as of this crack).
 *
 * sibling-search (cookbook §160g) hits, all from src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c
 * (the destination TU itself) plus one cross-overlay MATCHed twin:
 *   - func_8017F2AC(void *a0, s32 a1, s32 a2)   -- defined verbatim in THIS TU (line 3679)
 *   - func_80147324(D_80194BF4[idx][0])          -- exact idiom of func_8017C8FC's
 *                                                   func_80147324(D_8018EFD4[idx][0]) (same TU)
 *   - func_8001CB00(s32,void*,s32,s32)           -- signature + literal 0x280/0x100 pair pinned
 *     by src/ov_SC03_007/ov_SC03_007_jr_8017AE2C.c:5317 func_80186BE8 (labeled MATCH), whose tail
 *     `*(short*)(param_1+2) += 1;` is the exact idiom of this function's own final statement.
 *   - func_8012A68C()/func_8012A758()/func_8004978C()/ApplyMatrixSV() call trio -- exact shape of
 *     shared-engine func_80146F58 (src/ov_SC07_007/ov_SC07_007_jr_801457A4.c:1459): two s16 calls
 *     stored, func_8004978C(anglesPtr, matOut), ApplyMatrixSV(mat, in, out).
 *   - func_801465C0 loose void(void) file-scope decl (TU:130) fought via a cast-at-callsite,
 *     per §161c -- mirrors src/ov_SC06_008/ov_SC06_008_jr_8016AB6C.c's
 *     `((s32 (*)(void))func_801465C0)()` pattern. No explicit a0 setup precedes the target's jal
 *     (a0 still holds the entry parameter unclobbered) so a ZERO-ARG cast is the byte-safe choice
 *     -- it can never force a spurious argument-setup instruction.
 *
 * PROCESS NOTE (worth banking in the cookbook): a 2-instruction "REGALLOC-LOCAL" residual on
 * func_80015954's args looked exactly like local-alloc's optimize_reg_copy_1 collapsing two
 * identical-valued arg copies (byte-verified via `cc1 -da`: `.sched` had insn112/114 both reading
 * pseudo 80 cleanly, `.lreg` had insn114 rewritten to read insn112's DEST instead of pseudo80's
 * hard reg -- textbook §162j1). The `register s32 zr __asm__("$0"); x + zr` opaque-copy lever
 * (§136d-1/RC-12) did NOT defeat it when applied to the SECOND of the pair (validate_replace_rtx
 * substitutes inside a PLUS operand just as readily as inside a plain SET) -- applying it to the
 * FIRST copy instead (so insn117 is no longer a `single_set(REG)` and never qualifies as "a copy"
 * for the pass to scan forward from) did defeat it, dropping to a genuine 1-instruction
 * REGALLOC-PERM ($s3-vs-$s0). That flushed out the REAL bug: `func_80015954`'s first argument is
 * `vecOut` (the ApplyMatrixSV output), not `s3` -- I had the wrong VALUE, not a regalloc quirk.
 * Fixing the argument made the "residual" vanish with NO register-pin needed at all. Lesson: a
 * clean REGALLOC-LOCAL/-PERM diff on an ARGUMENT SETUP is worth re-deriving the argument's
 * identity from the target's OWN register (here $s0, not the more "obvious" $s3) before reaching
 * for §162j1/RC-12 levers -- they can mask a semantic error long enough to look load-bearing.
 */

extern void func_801465C0(void);
extern void func_80149374(s32 a0, s32 a1);
extern s16 func_8012A68C(void);
extern s16 func_8012A758(void);
extern void func_8004978C(s16 *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012EF70(s32 a0, s32 a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3);
extern void func_8017F2AC(void *a0, s32 a1, s32 a2);
extern void func_80147324(s32 a0);
extern void func_80146C3C(void);

/* new-to-this-TU data symbols (own address only in this function; payload owned by
 * asm/ov_SC03_014/data/tail.data.s, a data-only splat unit -- extern is correct, not a definition,
 * per §160c's "same .s as the function" test). D_80194CB0 bytes: 0000 0000 ECFF 0000 = {0,0,-20,0}.
 * D_80194C8C: 12 opaque bytes (a GPU-primitive template), address-only use -> §160f array style. */

void func_8017EB3C(void *a0) {

    extern s16 D_80194CB0[4];
    extern u8 D_80194C8C[12];
    extern u16 D_80194BF4[][2];
    void *s3;
    s32 s0;
    s32 s1;
    u8 mat[0x20];
    u16 vecOut[4];

    s0 = *(s32 *)(a0 + 0x34);
    s3 = ((void *(*)(void))func_801465C0)();
    *(void **)(a0 + 0x20) = s3;

    if (s3 != NULL) {
        s1 = (s32)a0 + 4;
        func_80149374(s0, s1);

        *(s16 *)(s3 + 0x10) = func_8012A68C();
        *(s16 *)(s3 + 0x12) = func_8012A758();
        func_8004978C((s16 *)(s3 + 0x10), mat);

        ApplyMatrixSV(mat, D_80194CB0, vecOut);

        *(u16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + vecOut[0];
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) + vecOut[1];
        *(u16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) + vecOut[2];

        func_80015978(s1, (s32 *)vecOut);
        func_8012EF70((s32)vecOut, (s32)vecOut);
        func_80015954((s32)vecOut, s1);

        func_8001CB00((s32)s3, D_80194C8C, 0x280, 0x100);

        *(u8 *)(s3 + 0x27) = 0x80;

        *(s16 *)(s3 + 0x2C) = *(u16 *)(a0 + 0xE);
        *(s16 *)(s3 + 0x1A) = 0;
        *(s16 *)(s3 + 0x18) = 0;

        *(s32 *)(a0 + 0x10) = 0;
        func_8017F2AC(a0, *(s32 *)(a0 + 0x2C), 0x8F);

        func_80147324(D_80194BF4[*(s32 *)(a0 + 0x2C)][0]);

        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}




extern void func_80146E90(s32 *a0, s32 a1);
extern void func_8017FA94(void *a0, s32 a1, s32 a2);

void func_8017ECB0(void *a0) {
    s32 *a2 = *(s32 **)((s32)a0 + 0x20);
    s16 sum;
    s32 pad[2];

    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        a2[1] |= 0x80000000;
    } else {
        a2[1] &= 0x7FFFFFFF;
    }

    *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x10) + 0x6C000;

    sum = *(u16 *)((s32)a2 + 0x1A) + *(u16 *)((s32)a0 + 0x12);
    *(u16 *)((s32)a2 + 0x1A) = sum;
    *(u16 *)((s32)a2 + 0x18) = sum;

    if (sum >= 0x1001) {
        *(u16 *)((s32)a2 + 0x1A) = 0x1000;
        *(u16 *)((s32)a2 + 0x18) = 0x1000;
        func_80146E90((s32 *)a0, 0);
        func_8017FA94(a0, *(s32 *)((s32)a0 + 0x2C), 0);
        func_80146E90((s32 *)a0, 0);
        *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
}



extern void func_8017F2AC(void *a0, s32 a1, s32 a2);
extern void func_8017F534(void *a0, s32 a1, s32 a2);
extern void func_80146C3C(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);

void func_8017ED98(void *a0) {

    extern s32 D_8011D030;
    extern u16 D_80194C08[][2];
    s32 *s2;

    s2 = *(s32 **)((s32)a0 + 0x20);

    if (*(s32 *)((s32)a0 + 0x1C) < 0x100) {
        if ((*(s32 *)((s32)a0 + 0x1C) & 0xF) == 0) {
            func_8017F2AC(a0, *(s32 *)((s32)a0 + 0x2C), 0xF);
            if ((*(s32 *)((s32)a0 + 0x1C) & 0xF) == 0) {
                s32 flags = *(s32 *)((s32)a0 + 0x1C) << 15;
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 1);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 2);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 3);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 4);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 5);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 6);
                func_8017F534(a0, *(s32 *)((s32)a0 + 0x2C), flags | 7);
            }
        }
        if (*(s32 *)((s32)a0 + 0x1C) & 1) {
            s2[1] |= 0x80000000;
        } else {
            s2[1] &= 0x7FFFFFFF;
        }
        *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
    } else {
        u8 *p = (u8 *)&D_8011D030;
        s32 idx;

        if ((u32)p < (u32)((u8 *)&D_8011D030 + 0xA50)) {
            do {
                if (*(u16 *)p == 0x2E) {
                    ((void (*)(s32))func_80146C3C)((s32)p);
                }
                p += 0x58;
            } while ((u32)p < (u32)((u8 *)&D_8011D030 + 0xA50));
        }

        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0x1C7);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0x38E);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0x555);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0x71C);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0x8E3);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0xAAA);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0xC71);
        }
        {
            s32 t3 = *(s32 *)((s32)a0 + 0x2C);
            s16 t0 = *(s16 *)((s32)a0 + 0x6);
            s16 t1 = *(s16 *)((s32)a0 + 0xA);
            s16 t2 = *(s16 *)((s32)a0 + 0xE);
            func_80146A6C(0x2B, a0, t0, t1, t2, t3, 0xE38);
        }

        func_80146E90((s32 *)a0, 0x20);

        idx = *(s32 *)((s32)a0 + 0x2C);
        func_80147324(D_80194C08[idx][0]);

        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80180218();

void func_8017F0E0(void *a0)
{
    s32 flags = *(s32 *)((s32)a0 + 0x1C);
    s32 ptr = *(s32 *)((s32)a0 + 0x20);

    if (flags & 1) {
        *(s32 *)(ptr + 4) |= 0x80000000;
    } else {
        *(s32 *)(ptr + 4) &= 0x7FFFFFFF;
    }

    if (func_80146E98((s32)a0)) {
        func_80180218();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8017F160(s32 *a0)
{
    s32 *ptr = (s32 *)a0[8];

    if (a0[7] & 1) {
        ptr[1] |= 0x80000000;
    } else {
        ptr[1] &= 0x7FFFFFFF;
    }

    *(s16 *)&a0[9] = 3;

    a0[7] += 1;
}



extern void func_8017F2AC(void *a0, s32 a1, s32 a2);
extern void func_80147324(s32 a0);
extern void func_80146C3C(void);

void func_8017F1AC(void *a0) {

    extern u16 D_80194C1C[][2];
    s32 *s2;
    s16 v0;

    s2 = *(s32 **)((s32)a0 + 0x20);

    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        s2[1] |= 0x80000000;
    } else {
        s2[1] &= 0x7FFFFFFF;
    }

    v0 = (*(u16 *)((s32)s2 + 0x12) + 0x80) & 0xFFF;
    *(u16 *)((s32)s2 + 0x12) = v0;

    if (v0 == 0 || v0 == 0x800) {
        if (*(s16 *)((s32)a0 + 0x24) != 0) {
            *(s16 *)((s32)a0 + 0x24) = *(s16 *)((s32)a0 + 0x24) - 1;
        }
    }

    v0 = *(u16 *)((s32)s2 + 0x1A) - 0x40;
    *(u16 *)((s32)s2 + 0x1A) = v0;
    *(u16 *)((s32)s2 + 0x18) = v0;

    if (v0 < 0) {
        func_8017F2AC(a0, *(s32 *)((s32)a0 + 0x2C), 0x8F);
        func_80147324(D_80194C1C[*(s32 *)((s32)a0 + 0x2C)][0]);
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }

    *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017F2AC(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2D, a0, t0, t1, t2, a1, a2);
}



extern void (*D_80194CB8[])(void);

void func_8017F2F0(void *a0) {
    D_80194CB8[*(u16 *)((s32)a0 + 0x2)]();
}



/* callee-set / sibling search (cookbook §160g): all callees resolved from the DESTINATION TU
 * itself, src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c, whose immediately-preceding matched sibling
 * func_8017C6A0 (same TU, same family) uses the identical:
 *   - func_801465C0 loose void(void) file-scope decl, fought via a zero-arg cast-at-callsite
 *     (§161c) -- `((void *(*)(void))func_801465C0)()`.
 *   - func_80146C3C(void) called on the failure path with the object pointer cast in.
 *   - the returned object (named s3 there, s1 here) has s16 fields at +0x18/+0x1A/+0x2C, matching
 *     this function's `*(s16*)(s1+0x18)`, `+0x1A`, `+0x2C` stores exactly.
 * func_8001CD04(void*,void*) is defined in src/800.c (INCLUDE_ASM, shared engine) --
 * asm/nonmatchings/800/func_8001CD04.s shows it stores its 2nd arg into (a0+0x20), confirming a0
 * here is the newly-allocated object and a1 is an address it retains -- i.e. func_8001CD04(s1, s2)
 * installs s2 (&D_801EB448) onto the object.
 * The `lwl/lwr`+`swl/swr` pair at D_80194BB8[idx] / D_801EB448 is the §160a align-1 struct-copy
 * idiom; D_80194BB8 is already `extern M2C_UNK D_80194BB8;` (address-only) in many ov_SC05_017
 * TUs, and the shared align-1 4-byte struct type `B4` (src/shared/engine_types.h:713) is already
 * used repo-wide for this exact shape. The SAME address (&D_801EB448) also takes a plain ALIGNED
 * `sw` of 0xFFFFFF on the other branch -- an explicit `(u32*)` cast forces that, while the direct
 * `B4` struct assignment on the table-lookup branch keeps the align-1 `swl/swr` -- §160a's "read
 * the move width off the target, not off the data's apparent type", both branches hitting the same
 * lvalue.
 * D_801EB448/844/845/846 are owned by asm/ov_SC03_014/data/tail19.data.s (a data-only splat unit,
 * §160c) -- not bundled with this function's .s, so plain `extern` declarations are correct, not a
 * definition. D_801EB448 is one `.word` (4 bytes); D_801EB44C and D_801EB44D are each one `.byte`;
 * D_801EB44E opens a much larger multi-byte block in that data file, but this function only stores
 * a zero to its FIRST byte, so a scalar `extern u8 D_801EB44E;` is sufficient here.
 *
 * TYPE: match_one's standalone `common.h` does NOT reach src/shared/engine_types.h (only the real
 * TU's `#include "../shared/engine_core.h"` does), so `B4` isn't visible here. Per the
 * ov_SC06_032_jr_8018FCE8.c precedent ("cc1 errors on the redefinition" of an identical-name
 * typedef), a fresh, function-scoped name is used instead -- collides with nothing; the integrator
 * may DROP this local typedef and reuse the TU's own `B4` when banking into the host TU.
 */

typedef struct { u8 d[4]; } Blk4_8017CE90_8017F32C;

extern void func_801465C0(void);
extern void func_8001CD04(void *a0, void *a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146C3C(void);


void func_8017F32C(void *a0)
{

    extern Blk4_8017CE90_8017F32C D_80194BB8[];
    extern Blk4_8017CE90_8017F32C D_801EB448;
    extern u8 D_801EB44C;
    extern u8 D_801EB44D;
    extern u8 D_801EB44E;
    void *s1;
    Blk4_8017CE90_8017F32C *s2;
    s32 pad[10];

    s1 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s1;

    if (s1 != NULL) {
        s2 = &D_801EB448;
        func_8001CD04(s1, s2);

        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;
        func_800233CC(s2, 0x50);

        *(s32 *)((u8 *)a0 + 0x10) = 0;
        if (*(s32 *)((u8 *)a0 + 0x30) & 0x80) {
            *(u32 *)s2 = 0xFFFFFF;
            *(s16 *)((u8 *)s1 + 0x1A) = 0x80;
            *(s16 *)((u8 *)s1 + 0x18) = 0x80;
            *(s32 *)((u8 *)a0 + 0x14) = 0x80;
        } else {
            *s2 = D_80194BB8[*(s32 *)((u8 *)a0 + 0x2C)];
            *(s32 *)((u8 *)a0 + 0x14) = 0x20;
        }

        D_801EB44C = 0;
        D_801EB44D = 0;
        D_801EB44E = 0;

        *(s32 *)((u8 *)a0 + 0x30) = *(s32 *)((u8 *)a0 + 0x30) & 0x7F;
        *(s16 *)((u8 *)s1 + 0x2C) = *(u16 *)((u8 *)a0 + 0xE) + 0x10;
        *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


#include "common.h"

extern u8 D_801EB448[4];
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

void func_8017F458(void *a0)
{
    void *s2;
    void *s1;
    s32 v0;
    s32 v1;

    s2 = a0;
    s1 = *(void **)((u8 *)s2 + 0x20);
    D_801EB448[0] = func_80012F74(D_801EB448[0], 0, 10, 1);
    D_801EB448[1] = func_80012F74(D_801EB448[1], 0, 10, 1);
    D_801EB448[2] = func_80012F74(D_801EB448[2], 0, 10, 1);

    v1 = *(s32 *)((u8 *)s2 + 0x10) + *(s32 *)((u8 *)s2 + 0x14);
    *(s32 *)((u8 *)s2 + 0x10) = v1;

    v0 = *(u16 *)((u8 *)s1 + 0x1A) + v1;
    *(u16 *)((u8 *)s1 + 0x1A) = v0;
    *(s16 *)((u8 *)s1 + 0x18) = v0;

    v1 = *(s32 *)((u8 *)s2 + 0x30);
    *(s32 *)((u8 *)s2 + 0x30) = v1 - 1;
    if (v1 == 0) {
        ((void (*)(void *))func_80146C3C)(s2);
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017F534(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2E, a0, t0, t1, t2, a1, a2);
}



extern void (*D_80194CC8[])(void);

void func_8017F578(void *a0) {
    D_80194CC8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8017F5B4(s32 param_1)
{
    s32 pad[2];
    s32 r;

    r = rand();
    *(u16 *)(param_1 + 0x10) = 0x200;
    *(u16 *)(param_1 + 0x12) = 0x200;
    *(u16 *)(param_1 + 0x24) = (r & 0x1FF) + (*(u8 *)(param_1 + 0x30) << 9);
    *(u32 *)(param_1 + 0x18) = 0;
    *(u32 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x30) = *(u32 *)(param_1 + 0x30) >> 8;
    func_80146E90((s32 *)param_1, rand() & 7);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}


extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);

void func_8017F630(void *a0) {
    if (func_80146E98((s32)a0) != 0) {
        func_80146E90((s32 *)a0, 8);
        *(s16 *)((u8 *)a0 + 0x28) = 0x20;
        *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    }
}


    typedef struct { s16 vx; u16 vy; s16 vz, pad; } SVec_8017F67C;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017F67C;



extern s32 func_80146E98(s32 a0);
extern void func_80147324(s32 arg0);
extern void func_80146C3C(void);
extern void func_8017F7B4(int a0, SVECTOR_8017C290 *a1, SVECTOR_8017C290 *a2, s32 a3);

void func_8017F67C(void *a0)
{

    extern u16 D_80194C30[][2];
    s16 n;
    register s32 tmp __asm__("$4");
    register s32 t __asm__("$17");
    s16 v;
    SVECTOR_8017C290 vec1;
    SVECTOR_8017C290 vec2;

    n = *(s16 *)((s32)a0 + 0x28);
    if (n != 0) {
        n = n - 1;
        *(s16 *)((s32)a0 + 0x28) = n;
        if (n == 0) {
            func_80147324(D_80194C30[*(s32 *)((s32)a0 + 0x2C)][0]);
        }
    }

    tmp = *(s32 *)((s32)a0 + 0x30) + 0x6000;
    *(s32 *)((s32)a0 + 0x14) += tmp;
    t = tmp;

    v = *(u16 *)((s32)a0 + 0x10) - *(u16 *)((s32)a0 + 0x16);
    *(s16 *)((s32)a0 + 0x10) = v;
    if (v < 0) {
        *(s16 *)((s32)a0 + 0x10) = 0;
    }

    if (func_80146E98((s32)a0)) {
        *(s32 *)((s32)a0 + 0x18) += t;

        v = *(u16 *)((s32)a0 + 0x12) - *(u16 *)((s32)a0 + 0x1A);
        *(s16 *)((s32)a0 + 0x12) = v;
        if (v < 0) {
            *(s16 *)((s32)a0 + 0x12) = 0;
        }
    }

    vec1.vx = 0;
    vec1.vy = *(u16 *)((s32)a0 + 0x10);
    vec1.vz = 1;
    vec2.vx = 0;
    vec2.vy = *(u16 *)((s32)a0 + 0x12);
    vec2.vz = 1;
    func_8017F7B4((int)a0, &vec1, &vec2, *(s16 *)((s32)a0 + 0x24));

    if (*(s32 *)((s32)a0 + 0x10) == 0) {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}


extern void func_80013F3C(s32 a0);
extern void func_80017714(void *);
extern void func_8004914C();
extern void func_800491AC();
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
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

void func_8017F7B4(int a0, SVECTOR_8017C290 *a1, SVECTOR_8017C290 *a2, s32 a3)
{

    extern struct PW8017C290 D_80194BCC[];
    extern struct PW8017C290 D_80194BE0[];
    extern SVECTOR_8017C290 D_801EB4C8[4];
    extern struct PW8017C290 D_801EB4E8;
    extern struct PW8017C290 D_801EB4EC;
    extern u8 D_801EB4F0, D_801EA8E9, D_801EA8EA, D_801EB4F4, D_801EA8ED, D_801EA8EE;
    extern u8 D_801EB4F0, D_801EA8E9, D_801EA8EA, D_801EB4F4, D_801EA8ED, D_801EA8EE;
    extern int D_801EB4F8;
    MATRIX_8017C290 m;
    SVECTOR_8017C290 *r0_00;
    SVECTOR_8017C290 *r0;
    SVECTOR_8017C290 *pSVar6;

    D_801EB4F8 = 0x50000000;
    D_801EB4E8 = D_80194BCC[*(s32 *)(a0 + 0x2C)];
    D_801EB4EC = D_80194BE0[*(s32 *)(a0 + 0x2C)];
    *(struct PW8017C290 *)&D_801EB4F0 = D_80194BCC[*(s32 *)(a0 + 0x2C)];
    *(struct PW8017C290 *)&D_801EB4F4 = D_80194BE0[*(s32 *)(a0 + 0x2C)];

    func_80013F3C((s32)&m);
    RotMatrixZ((s16)a3, &m);
    m.t[0] = *(s16 *)(a0 + 0x6);
    m.t[1] = *(s16 *)(a0 + 0xA);
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801EB4C8[0];

    gte_ldv0(a1);
    gte_rt();
    gte_stsv(r0_00);

    gte_ldv0(a2);
    gte_rt();
    gte_stsv(r0_00 + 1);

    a1->vx = a1->vx - 2;
    gte_ldv0(a1);
    gte_rt();
    r0 = r0_00 + 2;
    gte_stsv(r0);

    a2->vx = a2->vx - 2;
    gte_ldv0(a2);
    gte_rt();
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = *(u16 *)(a0 + 0xE);
    func_80017714(r0_00);

    a1->vx = a1->vx + 4;
    gte_ldv0(a1);
    gte_rt();
    gte_stsv(r0);

    a2->vx = a2->vx + 4;
    gte_ldv0(a2);
    gte_rt();
    gte_stsv(pSVar6);

    r0_00->vz = *(u16 *)(a0 + 0xE);
    func_80017714(r0_00);
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017FA94(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2F, a0, t0, t1, t2, a1, a2);
}



extern void (*D_80194CD4[])(void);

void func_8017FAD8(void *a0) {
    D_80194CD4[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017FB14 -- ov_SC03_014, TU ov_SC03_014_jr_8017AE2C.c
 *
 * §160g sibling-first: destination TU itself has the exact template two functions earlier,
 * func_8017CE90 (same TU, same family, allocate-then-attach-a-fixed-color-quad shape):
 *   - func_801465C0 loose `void(void)` file-scope decl (TU line 130/3614/3910), fought via a
 *     zero-arg cast-at-callsite `((void *(*)(void))func_801465C0)()` (§161c).
 *   - func_8001CD04(void*,void*) shared-engine helper (src/800.c, INCLUDE_ASM) that stores its
 *     2nd arg into (a0+0x20) -- confirms s1=result-object, s0=&D_801EB488 retained address.
 *   - `*(s1+4) |= 0x50000000` computed and stored in the delay slot of the FOLLOWING
 *     func_800233CC jal (same instruction-order idiom as func_8017CE90's identical line).
 *   - func_80146C3C(void) called on the alloc-failure path with the object pointer cast in
 *     (`((void (*)(void *))func_80146C3C)(a0)`), same as func_8017CE90's else-branch.
 * func_80146E90(s32*,s32) is already declared+called directly (no cast) at TU line 3801
 * (`func_80146E90((s32 *)a0, 0x20);`) -- reused verbatim here with a different 2nd arg.
 * The color-quad global block D_801EB488.. is fixed by this TU's OWN later sibling
 * func_8017D900 (a few lines below in the same file), whose header comment explicitly notes:
 * "In-TU sibling func_8017FB14 shows D_801EB489/D_801EB48A are SEPARATE u8 globals (each gets
 * its own lui/%lo sb)" -- i.e. func_8017D900 was written FROM this function's own asm. That
 * comment also fixes D_801EB48C as a plain u8 (its Quad_801EA880 4-byte-struct framing only
 * matters for func_8017D900's block-copy; here each of D_801EB48C/885/886 gets an independent
 * byte store, so plain scalar externs are correct and sufficient).
 *
 * Source statement order mirrors instruction order 1:1 (straight-line alloc/init, no branches
 * inside the success path); the `a0 = s2` register move for the func_80146E90 call argument is
 * expected to be scheduler-hoisted early by gcc/sched2 exactly as seen in every other sibling in
 * this TU -- no special C construct needed for that.
 */

extern void func_801465C0(void);
extern void func_8001CD04(void *a0, void *a1);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C3C(void);


void func_8017FB14(void *a0)
{

    extern u8 D_801EB488;
    extern u8 D_801EB489;
    extern u8 D_801EB48A;
    extern u8 D_801EB48C;
    extern u8 D_801EB48D;
    extern u8 D_801EB48E;
    void *s1;
    void *s0;
    s32 pad[10];

    s1 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s1;

    if (s1 != NULL) {
        s0 = &D_801EB488;
        func_8001CD04(s1, s0);

        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;
        func_800233CC(s0, 0x100);

        *(s16 *)((u8 *)s1 + 0x1A) = 0;
        *(s16 *)((u8 *)s1 + 0x18) = 0;
        *(s32 *)((u8 *)a0 + 0x10) = 0x80;
        *(s16 *)((u8 *)s1 + 0x2C) = 0x10;

        *(u8 *)s0 = 0xFF;
        D_801EB489 = 0xFF;
        D_801EB48A = 0xFF;
        D_801EB48C = 0;
        D_801EB48D = 0;
        D_801EB48E = 0;

        func_80146E90((s32 *)a0, 0xC0);
        *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32*, s32);
extern void func_80147324(s32 a0);
extern u16 D_80194C44[];

void func_8017FBF8(s32 param) {
    s32 a0;
    s32 v0;
    s32 v1;
    s32 *s1;

    a0 = *(s32 *)(param + 0x1C) & 0x3F;
    s1 = (s32 *)(*(s32 *)(param + 0x20));
    v0 = func_8004787C(a0 << 6);

    v1 = *(s32 *)(param + 0x10);
    if (v0 < 0) {
        v0 += 0x7F;
    }
    v0 = v0 >> 7;
    v1 = v1 + v0;
    v0 = v1;

    *(s16 *)((u8 *)s1 + 0x1A) = v0;
    *(s16 *)((u8 *)s1 + 0x18) = v0;

    v0 = func_80146E98(param);
    if (v0 != 0) {
        ((void (*)(s32, s32))func_80146E90)(param, 0x40);

        v0 = *(s32 *)(param + 0x2C);
        v0 = D_80194C44[v0 << 1];
        func_80147324(v0);

        v0 = *(u16 *)(param + 0x2);
        *(s16 *)(param + 0x2) = v0 + 1;
    }
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);

void func_8017FCA0(s32 param) {
    s32 a0;
    s32 v0;
    s32 v1;
    s32 *s1;

    a0 = *(s32 *)(param + 0x1C) & 0x3F;
    s1 = (s32 *)(*(s32 *)(param + 0x20));
    v0 = func_8004787C(a0 << 6);

    v1 = *(s32 *)(param + 0x10);
    if (v0 < 0) {
        v0 += 0x7F;
    }
    v0 = v0 >> 7;
    v1 = v1 + v0;
    v0 = v1;

    *(s16 *)((u8 *)s1 + 0x1A) = v0;
    *(s16 *)((u8 *)s1 + 0x18) = v0;

    v0 = *(s32 *)(param + 0x10);
    *(s32 *)(param + 0x10) = v0 + 0x20;

    if (func_80146E98(param) != 0) {
        v0 = *(u16 *)(param + 0x2);
        *(s16 *)(param + 0x2) = v0 + 1;
    }
}


extern u8 D_801EB48C;
extern u8 D_801EB48D;
extern u8 D_801EB48E;

void func_8017FD2C(arg0, a1)
void *arg0;
void *a1;
{
    s16 var;

    a1 = *(void **)((s32)arg0 + 0x20);
    var = *(u16 *)((s32)a1 + 0x1A) + 0x200;
    *(u16 *)((s32)a1 + 0x1A) = var;
    *(u16 *)((s32)a1 + 0x18) = var;
    if (var >= 0x1001) {
        D_801EB48C = 0xFF;
        D_801EB48D = 0xFF;
        D_801EB48E = 0xFF;
        *(u16 *)((s32)a1 + 0x1A) = 0x1000;
        *(u16 *)((s32)a1 + 0x18) = 0x1000;
        *(u16 *)((s32)arg0 + 2) = *(u16 *)((s32)arg0 + 2) + 1;
    }
}



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

 /* align 1 => movstrsi expands to lwl/lwr + swl/swr */


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


#include "common.h"

extern void func_80146C3C(void);
extern void func_80147364(u16 a0, s32 a1);

void func_8017FE64(s32 a0) {

    extern s32 D_8011D030;
    extern u16 D_80194C08[][2];
    u8 *p = (u8 *)&D_8011D030;

    if ((u32)p < (u32)((u8 *)&D_8011D030 + 0xA50)) {
        do {
            if (*(u16 *)p == 0x2B) {
                ((void (*)(s32))func_80146C3C)((s32)p);
            }
            if (*(u16 *)p == 0x2C) {
                *(u16 *)(p + 2) = *(u16 *)(p + 2) + 1;
            }
            p += 0x58;
        } while ((u32)p < (u32)((u8 *)&D_8011D030 + 0xA50));
    }

    func_80147364(4, D_80194C08[a0][0]);
}


typedef struct { s16 m[4]; } S8_FF34;

void func_8017FF34(s16 a0, void *a1, void *a2) {
    extern s16 D_80126B30;
    extern s32 D_8012750C;
    extern s16 D_8011F9C8;
    extern s16 D_80126B3A;
    extern void func_80174684(void *);
    extern void func_8017FF9C(void *);

    *(S8_FF34 *)&D_80126B30 = *(S8_FF34 *)a1;
    D_80126B3A = a0;
    D_8012750C = (s32)a2;
    func_80174684((void *)func_8017FF9C);
    *(s32 *)&D_8011F9C8 = 0;
}



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


extern s32 D_80194CF0;
extern u8 D_800B9A11;
extern void func_8012943C(void);
extern void func_8013C938(void);
extern void func_8014706C(void *arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);

    void func_801800E8(s32 *a0) {
        s32 v0 = a0[0x80];
        s32 v1;
        v1 = v0 - 1;
        a0[0x80] = v1;
        if (v1 != -1) {
            return;
        }
        func_8014706C(a0);
        func_80154274(a0, (s32)&D_80194CF0);
        func_8013C938();
        D_800B9A11 = 0xC0;
        func_8012943C();
        func_80171A1C((u8 *)a0);
    }


extern s16 D_80126B3A;
extern s16 D_80126B3C;
extern void func_8017EAC0(void *a0, s32 a1, s32 a2);
extern void func_80171A1C(u8 *a0);

void func_8018015C(u8 *a0) {
    s32 v;
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        switch ((s16)(*(u16 *)&D_80126B3A - 2)) {
        case 0: v = 0; break;
        case 1: v = 1; break;
        case 2: v = 2; break;
        case 3: v = 3; break;
        case 4: v = 4; break;
        }
        D_80126B3C = v;
        func_8017EAC0(a0, -0x60, v);
        func_80171A1C(a0);
    }
}


DEFINE_func_80180210()  /* dedup: shared engine-core @0x80180210 (src/shared) */

extern s32 func_8013767C(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 D_8012750C;
extern s32 D_80126B58;
extern s32 D_80126CF0;

void func_80180218(void) {
    s32 v0;
    v0 = func_8013767C(D_8012750C);
    D_80126CF0 = v0;
    func_80171A1C((u8 *)&D_80126B58);
}


    extern s32 func_801399F0(s32 a0);
    extern void func_80139914(s32 a0);
    extern void func_8017FE64(s32 a0);
    extern void func_80171A1C(u8*);
    extern s16 D_80126B3C;
    void func_80180258(s32 param_1)
    {
        if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
            func_80139914(*(s32 *)(param_1 + 0x198));
            *(s32 *)(param_1 + 0x198) = 0;
            *(s32 *)(param_1 + 0x200) = 0x60;
            func_8017FE64((s32)D_80126B3C);
            ((void (*)(s32))func_80171A1C)(param_1);
        }
    }


extern void func_80154274(s32 *a0, s32 a1);
extern void func_8013C964(void);
extern void func_80129428(void);
extern void func_80171A1C(u8 *a0);
extern u8 D_800B9A11;
extern s32 D_80194D94;

void func_801802C0(s32 *a0) {
    s32 v0 = a0[0x80];
    s32 v1;
    v1 = v0 - 1;
    a0[0x80] = v1;
    if (v1 != -1) {
        return;
    }
    func_80154274(a0, (s32)&D_80194D94);
    func_8013C964();
    D_800B9A11 = 0;
    func_80129428();
    func_80171A1C((u8 *)a0);
}


extern s16 D_8011F9C8;
extern s16 D_80126B3A;
extern s32 func_80174650(s32);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern void func_80147060(u8 * a0);
extern void func_80147324(s32 arg0);
extern void func_80171A1C(u8 *a0);

void func_80180328(a0)
u8 *a0;
{
    u16 flags = *(u16 *)(a0 + 0xB8);

    if (flags & 0x4000) {
        func_80147324(0x445);
        return;
    }
    if (!(flags & 0x8000)) {
        return;
    }
    func_80147060(a0);
    switch ((s16)(*(u16 *)&D_80126B3A - 2)) {
    case 0:
        func_80029124(0x16, 1);
        func_80029514(0x85);
        break;
    case 1:
        func_80029124(0x17, 1);
        break;
    case 2:
        func_80029124(0x18, 1);
        break;
    case 3:
        func_80029124(0x19, 1);
        break;
    case 4:
        func_80029124(0x1A, 1);
        break;
    }
    (*(s32 *)&D_8011F9C8) = 1;
    func_80174650((s32)a0);
    func_80171A1C(a0);
}


void func_80180418(void) {
}

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_80180420(void *a0) {
    func_80146A6C(0x19, a0, 0, 0, 0, 0, 1);
}



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




/* func_801805C8 — entity tick with a two-mode "hit/shake" arm.
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
extern void func_8018077C(int);

void func_801805C8(void *a0)
{
    void *obj;
    s32 t;
    s32 r;
    s16 i;
    u16 v;
    u16 w;
    u16 d;

    t = *(s32 *)((s32)a0 + 0x1C);
    obj = *(void **)((s32)a0 + 0x34);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0x20) {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            v = *(u16 *)((s32)obj + 0x64) - 0x80;
            w = *(u16 *)((s32)obj + 0x62) + 0x100;
            *(s16 *)((s32)obj + 0x64) = v;
            *(s16 *)((s32)obj + 0x60) = v;
            *(s16 *)((s32)obj + 0x62) = w;
        } else {
            r = *(s32 *)((s32)obj + 0x20);
            *(u16 *)(r + 0x2C) |= 0x10;
            r = *(s32 *)((s32)obj + 0x20);
            d = *(u16 *)(r + 0x1C) - 0x80;
            *(s16 *)(r + 0x1C) = d;
            *(s16 *)(r + 0x18) = d;
            r = *(s32 *)((s32)obj + 0x20);
            *(u16 *)(r + 0x1A) += 0x100;
        }
        i = 0;
        do {
            func_80146A6C(0x1B, obj, 0, 0, 0, 0, 0);
            i++;
        } while (i < 3);
    } else {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            func_8014708C(obj);
            func_801472C8((struct S *)obj);
        } else {
            *(s32 *)(*(s32 *)((s32)obj + 0x20) + 0x4) |= 0x80000000;
        }
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
    ((void (*)(void *))func_8018077C)(a0);
}


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




/* func_8018077C — 4-point primitive sweep driven by the 44-byte curve table
 * D_80194E84.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_8018077C(int param_1)
{

    extern u8  D_80194E84[];
    SVec8_8017C218_8018077C rot;
    s32   pad0[2];
    Prim_8017C218_8018077C  prim;
    s32   pad1[1];
    Mtx_8017C218_8018077C   mtx;
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

    p = D_80194E84;
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
    p = D_80194E84;
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
        p = D_80194E84;
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




void func_80180E74(void *a0)
{
    extern Mtx8_8017C910_80180E74 aD800AE620 __asm__("D_800AE620");
    extern void aFunc80016A5C(void *arg0, void *arg1) __asm__("func_80016A5C");
    Prim_8017C910_80180E74 prim;
    Mtx8_8017C910_80180E74 mtx;
    s32 p;

    p = (s32)a0;
    if (*(s32 *)(p + 0x2C) != 0) {
        prim.v[0].y = *(u16 *)(p + 0xA) - 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) + 0x20;
    } else {
        prim.v[0].y = *(u16 *)(p + 0xA) + 0x20;
        prim.v[1].y = *(u16 *)(p + 0xA) - 0x20;
    }
    prim.v[0].x = *(u16 *)(p + 0x6);
    prim.v[0].z = *(u16 *)(p + 0xE);
    prim.v[1].x = *(u16 *)(p + 0x6);
    prim.v[1].z = *(u16 *)(p + 0xE);
    prim.col[0].b = 0;
    prim.col[0].g = 0;
    prim.col[0].r = 0;
    switch (*(u32 *)(p + 0x30)) {
    case 0:
        prim.col[1].r = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].g = 0;
        break;
    case 1:
        prim.col[1].g = 0xFF;
        prim.col[1].b = 0;
        prim.col[1].r = 0;
        break;
    case 2:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0;
        prim.col[1].r = 0;
        break;
    case 3:
        prim.col[1].b = 0xFF;
        prim.col[1].g = 0xFF;
        prim.col[1].r = 0xFF;
        break;
    }
    mtx = aD800AE620;
    prim.tag = 0x50000000;
    aFunc80016A5C(&prim, &mtx);
}


#include "common.h"

/* func_80180FE4 — ov_SC02_011 — TMD-style model renderer (672 ins, jr-function).
 * MATCH 672/672, verified by tools/match_one.py + reloc_identity AGREE (7 relocs).
 *
 * Structural TWIN of the already-banked func_8017BEBC (ov_SC03_099_jr_8017BEBC.c,
 * MATCH 952/952): identical bbox -> RTPT/RTPS projection outer loop and per-prim
 * RTPT/nclip cull.  Deltas vs the twin, all read off this .s:
 *   - only TWO prim classes survive here: 6,7 = POLY_FT3 and 2,3 = POLY_FT4
 *     (the twin also carries 4,5 = POLY_F3 and 0,1 = POLY_F4), and the FT3 case
 *     must come FIRST in the switch — expand_case lays case bodies out in SOURCE
 *     order and this .s puts the FT3 body at the dispatch fall-through;
 *   - the Y clip is -0x6E / 0x6F here (twin: -0x78 / 0x79); X is -0xA0 / 0xA1 in both;
 *   - `code` is a SIGNED s32 (the twin's u32 gives sltiu; this .s wants slti);
 *   - no `spare` filler in `g`: locals are exactly 0x10..0xDC and gcc adds a fixed
 *     128 bytes of its own, giving the 0x188 frame.
 *
 * TWO REGISTER-ALLOCATION TIES had to be split (both §47-class, global.c
 * allocno_compare priority = floor_log2(refs)*refs/live_length):
 *   1. `mny`/`my` (the two halves of part->yy) landed in $a3/$a2, transposed vs the
 *      target's $a2/$a3, and every later use cascaded (42 mismatched ins).  Writing
 *      `my = wy >> 16;` BEFORE `mny = wy;` fixed the allocation but then transposed
 *      the two defs at emission.  The fix that gets BOTH: keep the natural source
 *      order (`mny` first, correct emission) and add ONE zero-byte
 *      `__asm__ volatile ("" :: "r"(mny));` between the two defs.  It emits nothing
 *      (#APP/#NO_APP only) but adds a REF to `mny`, raising its priority above `my`
 *      so `mny` is granted $a2 first — a *ref-count* slider, complementary to §47's
 *      documented *live-length* slider (`__asm__ volatile ("")`).
 *   2. Do NOT also add the twin's §47 live-length slider between gte_ldv3c(&box[4])
 *      and gte_rtpt(): with the ref slider in place, the &g.sz0/&g.sz1 ($s4/$s5)
 *      tie already splits the target's way.  Adding both re-transposes it (6 ins).
 *
 * GTE ops are verbatim PsyQ inline_c.h macro bodies; rtps/rtpt/nclip are spelled via
 * the project gas macros in include/gte_macros.inc.  gte_stszotz/gte_stflg MUST list
 * "$12" in the clobber list (§179-D) — both hardwire $12 outside their operands.
 *
 * Types are suffixed _80180FE4 so the draft compiles standalone; when banked into
 * ov_SC02_011_jr_8017AE2C.c the shared engine_types.h spellings (DVECTOR2, SVECTOR2,
 * MATRIX2, Part, PolyFT3, PolyFT4) are already in scope via engine_core.h and these
 * local typedefs can be dropped.
 */

typedef struct { s16 vx, vy; } DVEC80180FE4;
typedef struct { s16 vx, vy, vz, pad; } SVEC80180FE4;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX80180FE4;
typedef struct { u32 xx, yy, zz; u32 nprim; u32 *prim; } Part80180FE4;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1;
                 s16 x2, y2; u16 uv2, p2; } PolyFT3_80180FE4;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1;
                 s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PolyFT4_80180FE4;

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

void func_80180FE4(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MTX80180FE4 *);
    extern void func_80052E38(MTX80180FE4 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    DVEC80180FE4 tmpxy[4];
    SVEC80180FE4 box[8];
    SVEC80180FE4 sxy[8];
    MTX80180FE4 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part80180FE4 *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w;
    s32 code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = *(Part80180FE4 **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        __asm__ volatile ("" :: "r"(mny));
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
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3_80180FE4 *)pkt)->x0 > ((PolyFT3_80180FE4 *)pkt)->x1) {
                                        mx = ((PolyFT3_80180FE4 *)pkt)->x0;
                                        mn = ((PolyFT3_80180FE4 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3_80180FE4 *)pkt)->x0;
                                        mx = ((PolyFT3_80180FE4 *)pkt)->x1;
                                    }
                                    if (((PolyFT3_80180FE4 *)pkt)->x2 > mx) mx = ((PolyFT3_80180FE4 *)pkt)->x2;
                                    else if (((PolyFT3_80180FE4 *)pkt)->x2 < mn) mn = ((PolyFT3_80180FE4 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3_80180FE4 *)pkt)->y0 > ((PolyFT3_80180FE4 *)pkt)->y1) {
                                            my = ((PolyFT3_80180FE4 *)pkt)->y0;
                                            mny = ((PolyFT3_80180FE4 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3_80180FE4 *)pkt)->y0;
                                            my = ((PolyFT3_80180FE4 *)pkt)->y1;
                                        }
                                        if (((PolyFT3_80180FE4 *)pkt)->y2 > my) my = ((PolyFT3_80180FE4 *)pkt)->y2;
                                        else if (((PolyFT3_80180FE4 *)pkt)->y2 < mny) mny = ((PolyFT3_80180FE4 *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za;
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
                                            ((PolyFT3_80180FE4 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3_80180FE4 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3_80180FE4 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3_80180FE4 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
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
                                        gte_stsxy((long *)&((PolyFT4_80180FE4 *)pkt)->x3);
                                        if (((PolyFT4_80180FE4 *)pkt)->x3 < mn) mn = ((PolyFT4_80180FE4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4_80180FE4 *)pkt)->x3) mx = ((PolyFT4_80180FE4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4_80180FE4 *)pkt)->y3 < mny) mny = ((PolyFT4_80180FE4 *)pkt)->y3;
                                            else if (my < ((PolyFT4_80180FE4 *)pkt)->y3) my = ((PolyFT4_80180FE4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
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
                                                *(u32 *)&((PolyFT4_80180FE4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4_80180FE4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4_80180FE4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4_80180FE4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4_80180FE4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4_80180FE4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4_80180FE4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4_80180FE4 *)pkt)->uv3 = uvw >> 16;
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


extern s32 func_80171990(u8 *a0);
extern u8 D_801D659C[];
extern u8 D_801D663C[];

void func_80181E00(u8 *a0) {
    *(u32 *)(a0 + 0xB0) = (u32)D_801D659C;
    *(u32 *)(a0 + 0xCC) = (u32)D_801D663C;
    *(u16 *)(a0 + 0x20C) = 0;
    *(u16 *)(a0 + 0x20E) = 0;
    *(u16 *)(a0 + 0x210) = 0;
    func_80171990(a0);
}


#include "common.h"

extern void func_80019064(void *a0);
extern void func_80181FA0(s32 a0);
extern s32 func_80181F6C(s32 a0);
extern void func_8014BF48(void);
extern void func_801722CC(s32 *a0);
extern s32 func_80171990(u8 *a0);

extern u16 D_80194FCC;
extern s16 D_8019500A[];
extern u32 D_800D6078;
extern u32 D_800D6118;

void func_80181E40(s32 param_1) {
    s16 v0;

    func_80019064(&D_80194FCC);
    func_80181FA0(param_1);
    if (func_80181F6C(param_1) != 0) {
        v0 = *(s16 *)(param_1 + 0x210);
        if (D_8019500A[v0 << 2] != 0) {
            *(u32 *)(param_1 + 0xB0) = (u32)&D_800D6078;
            *(u32 *)(param_1 + 0xCC) = (u32)&D_800D6118;
            *(s16 *)(param_1 + 0x12E) = 0;
            func_8014BF48();
            func_801722CC((s32 *)param_1);
            func_80171990((u8 *)param_1);
        } else {
            v0++;
            *(s16 *)(param_1 + 0x210) = v0;
            func_80181F6C(param_1);
        }
    }
}


void func_80181EF4(s32 param_1) {
    typedef struct { u8 b[8]; } Blk8L;
    extern Blk8L D_801E9DA0;
    Blk8L buffer;

    buffer = D_801E9DA0;
    if (func_80171CC4((void *)param_1, &buffer)) {
        func_80187838();
        func_80171928((void *)param_1);
    }
    func_80172304((s32 *)param_1);
}


extern s8 D_80195004;

s32 func_80181F6C(s32 param_1) {
    return func_80171E08(param_1, (s32)&D_80195004 + (*(s16 *)(param_1 + 0x210) << 3), 0xA);
}


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


extern s32 func_80171990(u8 *a0);
extern s32 func_80171D78(s32 a0, s32 a1);

void func_801820F4(s32 a0) {
    s16 buf[3];

    buf[0] = -0xE0;
    buf[2] = 0x400;
    buf[1] = *(u16 *)(a0 + 0xA);
    if (func_80171D78(a0, (s32)buf) != 0) {
        func_80171990((u8 *)a0);
    }
}


void func_80182148(s32 a0) {
    s16 buf[3];

    buf[0] = -0xE0;
    buf[2] = 0x3D2;
    buf[1] = *(s16 *)(a0 + 0xA);
    if (func_80171D78(a0, (s32)buf) != 0) {
        func_801722CC((s32 *)a0);
        func_80171990((u8 *)a0);
    }
    func_80182344(a0);
}


void func_801821AC(s32 param_1) {
    func_80172304((s32 *)param_1);
    func_80171EC8(param_1);
    if (func_80172664((s32 *)param_1) == 0) {
        func_80171990((u8 *)param_1);
    }
    func_80182344((u8 *)param_1);
}


void func_801821FC(s32 a0) {
    if (func_80172670((s32 *)a0) != 0) {
        func_8016F264();
        *(u16 *)(a0 + 0xAA) &= 0x4090;
        *(u16 *)(a0 + 0xAC) &= 0x4090;
    } else {
        func_8016F288();
        func_80148634((void *)a0);
        func_80171990((u8 *)a0);
    }
}


extern s16 D_80196530;
extern s32 func_8013767C(s32 a0);
extern s32 func_80171990(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern s32 func_80172670(s32 *a0);

void func_80182344(s32 param_1);

void func_80182268(s32 a0) {
    if (func_80172658((s32 *)a0) != 0) {
        if (*(s16 *)(a0 + 0xA) >= -0x1FF) {
            *(s32 *)(a0 + 0x198) = func_8013767C(&D_80196530);
            func_80171990((u8 *)a0);
        } else {
            *(u8 *)(a0 + 0x216) = 0;
        }
    } else if (func_80172670((s32 *)a0) != 0) {
        *(u8 *)(a0 + 0x216) = 3;
    }
    func_80182344(a0);
}


extern s32 func_80172658(s32 *a0);
extern s32 func_801399F0(s32 a0);
extern void func_801823B8(void);

void func_801822F4(s32 param_1) {
    s32 s0;

    if (func_80172658((s32 *)param_1) != 0) {
        s0 = param_1;
        if (func_801399F0(*(s32 *)(s0 + 0x198)) != 0) {
            func_801823B8();
            *(u8 *)(s0 + 0x216) = 0;
        }
    }
}


extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80182344(s32 param_1) {
    *(s16 *)(param_1 + 6) = func_80012F74(*(s16 *)(param_1 + 6), -0xE0, 10, 1);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_80195028;
extern s32 D_80126B58;
extern void func_8016F094(s32 *a0);

void func_80182380(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_80195028, 0x1000000);
    func_8016F094(&D_80126B58);
}


















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

#include "common.h"

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_801826D8(void *a0);

extern s32 D_80126950;
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];

s32 func_801823EC(s32 a0) {
    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x1C7;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;

    func_8012A018((s32)func_801826D8, 0);
    func_8012A094((s32)D_80126948);
    func_801826D8(D_80126948);
}


#include "common.h"

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_801826D8(void *a0);

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern u8 D_80126948[];

extern s16 D_80126940;
extern s16 D_801274E8;
extern s16 D_801269E8;

typedef struct {
    s16 x0, x1, x2, x3;
} UnalignedShortBlock;

void func_80182488(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x3E8;
    D_80126968 = -0xE3;
    D_8012696A = 0x58E;
    D_80126978 = -0x30;
    D_8012696C = 0;
    D_80126976 = 0;
    D_8012697A = -0x80;
    func_8012A018((s32)func_801826D8, 1);
    func_8012A094((s32)D_80126948);
    *(UnalignedShortBlock *)&D_801274E8 = *(UnalignedShortBlock *)&D_80126940;
    D_801269E8 = 0xA0;
    func_801826D8((void *)D_80126948);
}


#include "common.h"

extern void func_8012A018(s32 a, s32 b);
extern void func_801826D8(void *a0);
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern s32 D_80126958;
extern s32 D_8012695C;
extern s16 D_80126960;
extern s16 D_80126962;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_80126972;
extern u16 D_80126974;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s16 D_801274E8;
extern s16 D_801274EA;
extern s16 D_801274EC;

void func_80182564(s32 a0) {
    D_80126958 = 0x4B0;
    D_8012695C = 0x4B0;
    D_80126960 = 0x38E;
    D_80126968 = 0x38E;
    D_80126962 = 0;
    D_8012696A = 0;
    D_80126972 = 0;
    D_80126978 = 0;
    D_80126974 = 0;
    D_8012697A = 0;
    D_801274E8 = D_80126940;
    D_801274EA = D_80126942;
    D_801274EC = D_80126944;
    func_8012A018((s32)func_801826D8, 2);
}


extern void func_8012A568(void (*a0)(void));
    extern s32 func_801823EC(s32 a0);
    void func_80182614(void) {
        ((void (*)(void *))func_8012A568)((void *)func_801823EC);
    }


#include "common.h"

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

extern void func_801826D8(void *a0);

s32 func_8018263C(void)
{
    D_80126954 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x71;
    D_8012696A = -0x155;
    D_8012696C = 0;
    D_80126976 = 0xE0;
    D_80126978 = 0;
    D_8012697A = 0;

    func_8012A018((s32)func_801826D8, 0x3);
    func_8012A094((s32)D_80126948);
    func_801826D8((void *)D_80126948);
}



extern void (*D_80195048[])(void);

void func_801826D8(void *a0) {
    D_80195048[*(u8 *)((s32)a0 + 0x4)]();
}


/* func_80182714 (ov_SC02_011) — MATCH, 189 ins (match_one closeness 0).
 *
 * Levers (S71a, fable):
 *   §209  `mode` and `ang` are 16-BIT locals. The target's `addu $v1,$s3` before the
 *         mode `beq`s and `addu $v1,$s4` before the 0x800/0xB01/0x210 tests are the
 *         deferred sign-extension copies of s16 locals; `angle` has ONE set
 *         (`ratan2() & 0xFFF`), so combine proves the sign bit clear and each
 *         `sign_extend` collapses to a move. `ang = angle` itself is the HImode
 *         truncation copy ($s4 = $s0) that plain s32 copies coalesce away — no asm
 *         tie needed (the earlier draft's "=r"/"0" trick and fence are gone).
 *   §48-A global-alloc priority: with the copies in place ang and mode both have 5
 *         refs, and their post-sched1 live lengths tie within one insn (107 vs 108,
 *         ang first -> ang=$s3, mode=$s4, close=13). Writing `ang = angle;` BEFORE
 *         the `dist = func_80013294()` call lengthens ang to 109 (zero bytes: sched1
 *         still parks the copy in the bnez delay slot) so mode allocates first and
 *         takes $s3, ang/q share $s4, dist $s5 — byte-exact.
 *   §199-G/§222/§256 (carried from the s67o2 draft): mode dispatch is a `switch`;
 *         the redundant `ang >= 0x800` re-test reproduces `beqz $a0,.L80182930`.
 */
#include "common.h"

void func_80182714(s32 param_1) {
    typedef struct { s16 x0, x1, x2, x3; } Blk8S16;
    extern s32 D_801E9DA8;
    extern s32 D_80126B58;
    extern s16 D_80195058[];
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;
    extern u16 func_80148800(s32 *a0);
    extern s32 ratan2(s32 dx, s32 dy);
    extern s32 func_80013294(void *a0, void *a1);
    extern void func_8018B5A8(s32 a0, void *a1, void *a2);
    extern void func_80182B88(s32 a0, s32 a1, s32 a2, s32 a3);

    u16 buf[8];
    s16 *base;
    u16 *p;
    u16 *q;
    s32 angle;
    s16 ang;
    s16 dist;
    s16 mode;

    *(Blk8S16 *)&buf[4] = *(Blk8S16 *)&D_801E9DA8;
    q = &buf[4];
    mode = 0;
    if ((func_80148800(&D_80126B58) & 3) != 0) {
        *(u8 *)(param_1 + 5) = (*(u8 *)(param_1 + 5) + 1) & 1;
    }
    *(s32 *)(param_1 + 0x14) = D_80195058[*(u8 *)(param_1 + 5)];
    base = &D_80126940;
    angle = ratan2(*base << 16, D_80126944 << 16) & 0xFFF;
    *(Blk8S16 *)&buf[0] = *(Blk8S16 *)base;
    p = &buf[0];
    buf[5] = D_80126942;
    ang = angle;
    dist = func_80013294(p, q);
    if (dist >= 0xA01) {
        buf[0] = 0;
        buf[1] = D_80126942;
        buf[2] = 0xA00;
        func_8018B5A8(angle, p, p);
        buf[0] = (s32)(s16)buf[0] >> 3;
        buf[1] = (s32)(s16)buf[1] >> 3;
        buf[2] = (s32)(s16)buf[2] >> 3;
    } else {
        *(s16 *)(param_1 + 0x20) = 0x1C7;
        *(s16 *)(param_1 + 0x22) = 0;
        *(s16 *)(param_1 + 0x24) = 0;
        *(s16 *)(param_1 + 0x2E) = 0;
        *(s16 *)(param_1 + 0x30) = 0;
        *(s16 *)(param_1 + 0x32) = 0;
    }
    if (ang >= 0x800) {
        if (ang >= 0xB01) goto checks;
        if (ang >= 0x800) goto set1c7;
    }
    if (ang >= 0x210) goto set1c7;
checks:
    if (dist < 0x3C1) goto set1c7;
    if (*(s16 *)&buf[1] < -0x2FF) goto set1c7;
    if (ang < 0xD01) goto arm1;
    if (dist < 0x500) {
        *(s16 *)(param_1 + 0x20) = 0x31C;
        mode = 2;
        goto after;
    }
    mode = 2;
    *(s16 *)(param_1 + 0x20) = 0x38E;
    *(s32 *)(param_1 + 0x14) = 0x4B0;
    goto after;
arm1:
    mode = 1;
    goto after;
set1c7:
    *(s16 *)(param_1 + 0x20) = 0x1C7;
after:
    if (dist < 0x200) {
        *(s16 *)(param_1 + 0x20) = 0xE3;
        *(s16 *)(param_1 + 0x22) = 0;
        *(s16 *)(param_1 + 0x24) = 0;
        *(s16 *)(param_1 + 0x2E) = 0;
        *(s16 *)(param_1 + 0x30) = -0xC0;
        *(s16 *)(param_1 + 0x32) = 0;
    }
    if (dist >= 0x981) {
        *(s32 *)(param_1 + 0x14) = 0x384;
    }
    switch (mode) {
    case 1:
        *(s16 *)(param_1 + 0x20) = 0x2AA;
        *(s32 *)(param_1 + 0x14) = 0x4B0;
        break;
    case 2:
        *(s32 *)(param_1 + 0x14) = 0x4B0;
        break;
    }
    if ((u32)(ang - 0xD01) < 0xFF && (u16)(dist - 0x481) < 0x29F) {
        *(s16 *)(param_1 + 0x20) = 0x1C7;
    }
    func_80182B88(param_1, ang, (s32)&buf[0], (s32)&buf[0]);
}


void func_80182A08(void *a0) {
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_8012A5F8(s32 a0, s32 a1);
    extern void func_80182B88(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80182564(s32 a0);
    extern s16 D_80126944;
    extern s16 D_80126940;
    extern s16 D_801274E8;

    s16 *base;
    s32 angle;
    s16 temp;
    s32 pad[2];

    base = &D_80126940;
    angle = ratan2(*base, D_80126944) & 0xFFF;

    temp = *(u16 *)((s32)a0 + 0xA0) - 1;
    *(u16 *)((s32)a0 + 0xA0) = temp;

    if (temp == -1) {
        func_8012A5F8((s32)func_80182564, 0x40);
    } else {
        func_80182B88((s32)a0, angle, (s32)&D_801274E8, (s32)base);
    }
}


void func_80182A9C(void *a0) {
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80182B88(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s16 D_80126944;
    extern s16 D_80126940;

    s16 *base;
    s32 angle;
    s32 pad[2];

    base = &D_80126940;
    angle = ratan2(*base, D_80126944) & 0xFFF;
    func_80182B88((s32)a0, angle, (s32)base, (s32)base);
}


extern s32 ratan2(s32 dx, s32 dy);

void func_80182AF8(void *a0) {
    extern void func_80182B88(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s16 D_80126944;
    extern s16 D_80126940;
    extern s16 D_80126942;

    s16 *base;
    s32 angle;
    s16 temp;

    base = &D_80126940;
    angle = ratan2(*base << 16, D_80126944 << 16) & 0xFFF;
    temp = D_80126942;
    if (temp >= -0x27F) {
        *(s16 *)((s32)a0 + 0x20) = temp + 0x2F1;
        *(s16 *)((s32)a0 + 0x18) = temp + 0x2F1;
    } else {
        if (temp < -0x37F) {
            if (temp < -0x47F) {
                goto skip;
            }
        } else {
            goto skip;
        }
        *(s16 *)((s32)a0 + 0x20) = temp + 0x3F1;
        *(s16 *)((s32)a0 + 0x18) = temp + 0x3F1;
    }
skip:
    func_80182B88((s32)a0, angle, (s32)&D_80126940, (s32)&D_80126940);
}


extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8018B76C(u16 *r, s16 *m);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_80182B88(s32 param_1, s32 param_2, s16 *param_3, s16 *param_4) {
    s32 m1[8];
    u16 svec_in[4];
    u16 svec_out[4];
    u16 rot[12];

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_4[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_4[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_4[2];

    rot[0] = *(u16 *)(param_1 + 0x18);
    rot[1] = *(u16 *)(param_1 + 0x1A) + param_2;
    rot[2] = *(u16 *)(param_1 + 0x1C);
    func_8018B76C(rot, (s16 *)m1);

    svec_in[0] = 0;
    svec_in[1] = 0;
    svec_in[2] = *(s32 *)(param_1 + 0x10);
    ApplyMatrixSV(m1, svec_in, svec_out);

    *(s32 *)(param_1 + 0x3C) = ((s32)(s16)svec_out[0] >> 3) + *(s16 *)(param_1 + 0x28) + param_3[0];
    *(s32 *)(param_1 + 0x40) = ((s32)(s16)svec_out[1] >> 3) + *(s16 *)(param_1 + 0x2A) + param_3[1];
    *(s32 *)(param_1 + 0x44) = ((s32)(s16)svec_out[2] >> 3) + *(s16 *)(param_1 + 0x2C) + param_3[2];
}


void func_80182D60(void *a0) {
    extern void (*D_801955B0[])(void *);
    if (func_80182DB8(a0) == 1) {
        D_801955B0[*(u16 *)((s32)a0 + 0x2)](a0);
    }
}


extern void func_8001AAA0(s32 arg);

s32 func_80182DB8(s32 arg0) {
    if (*(s16 *)(arg0 + 0x104) != 0) {
        if (*(s32 *)(arg0 + 0xE4) == 0) {
            *(s16 *)(arg0 + 0x104) = 0;
            *(s16 *)(arg0 + 0xFE) = 1;
        } else {
            *(s32 *)(arg0 + 0xE4) -= 1;
        }
        goto ret1;
    }
    if (*(s16 *)(arg0 + 0xFE) == 0) {
        goto ret1;
    }
    if (((s32 (*)(s32))func_8001AAA0)(*(s32 *)(arg0 + 0xE0)) == 0) {
        if ((*(s32 *)(arg0 + 0xDC) & 0x100) == 0) {
            goto ret1;
        }
        return 0;
    }
    *(s16 *)(arg0 + 0xFE) = 0;
    *(s32 *)(arg0 + 0xDC) &= ~0x100;
ret1:
    return 1;
}


void func_80182E68(void *a0) {
    if ((func_800291B4(0xCD) & 0xFF) == 0 || (func_80029178(0x9E) & 0xFF) != 0) {
        func_8012CAE4(a0);
    } else {
        *(u16 *)((s32)a0 + 2) = 1;
    }
}


extern u8 D_801202A0[];
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_80126B5E;
extern void func_801746DC(void);

void func_80182EC8(s32 arg0) {
    u16 x;
    u16 y;
    u16 z;
    u8 *p;
    u8 *q;
    s32 i;

    x = D_80126B5E;
    y = D_80126B62;
    z = D_80126B66;
    if ((u16)(x + 0x25D) < 0xDD && (s16)y >= -0x142 && (u32)(z - 0x3C3) < 0x31D) {
        *(u16 *)(arg0 + 2) = 2;
        p = D_801202A0;
        i = 0;
        do {
            if (*(u16 *)p == 0xB0) {
                q = p + 0x70;
                if (*(s16 *)q == 0x881) {
                    *(u16 *)(q + 0x8C) = 1;
                }
                if (*(s16 *)q == -0x7780) {
                    *(s16 *)q &= ~0x800;
                }
            }
            i++;
            q += 0x10C;
            p += 0x10C;
        } while (i < 0x60);
        func_801746DC();
    }
}


extern s16 func_80128CFC(u16 a0);
extern void func_80184918(s32 arg0, s32 arg1);

void func_80182FA8(s32 arg0) {
    s32 v0;

    v0 = ((s32 (*)(u16))func_80128CFC)(6);
    if (v0 == 1) {
        *(u16 *)(arg0 + 2) = 3;
        func_80184918(arg0, 0x26);
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80178BF8();
extern short D_801950A4;
extern short D_801F3EA4;

void func_80182FF0(s32 arg0) {
    s32 s0;
    s32 v0;

    s0 = arg0;
    if (func_8012C354(s0, (s32)&D_801950A4) != 0) {
        v0 = func_80143970(s0);
        *(s32 *)(s0 + 0xD0) = v0;
        func_8012A828(s0, (void *)&D_801F3EA4);
        func_80178BF8();
        *(s16 *)(s0 + 0x2) = 6;
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801F3EA4;
    void func_80183054(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801F3EA4);
    }


void func_80183080(s32 arg0) {
    extern s32 func_80178BF8();
    extern void func_801746DC(void);
    extern void func_8012E88C(u8 *a0);
    extern s32 func_8012E57C(s32 a0, s32 a1);
    extern void func_80184918(s32 arg0, s32 arg1);
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    u16 x;
    u16 y;
    u16 z;

    x = D_80126B5E;
    y = D_80126B62;
    z = D_80126B66;
    if ((u16)(x + 0x25D) < 0xDD && (s16)y >= -0x142 && (u32)(z - 0x3C3) < 0x31D) {
        func_80178BF8();
        func_801746DC();
        *(u16 *)(arg0 + 2) = 6;
        func_8012E88C((u8 *)arg0);
        *(u16 *)(func_8012E57C(0xB0, 0x881) + 0xFC) = 1;
        func_80184918(arg0, 0x26);
    }
}


void func_8018312C(s32 a0) {
    extern s16 D_80195198;
    *(s16 *)(a0 + 2) = 7;
    func_80178CBC(a0, (s32)&D_80195198);
    func_8012B23C(a0);
    *(s16 *)(a0 + 0x34) = 9;
    func_80184A54();
}


