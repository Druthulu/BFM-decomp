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


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182564);

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


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182714);

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


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80182FF0);


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


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183178);

extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182380(void);
extern u8 D_80195114[];
extern u8 D_801F404C[];

void func_801834EC(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 9;
    func_8012B23C(s0);
    func_8012B14C(s0, (s32)D_80195114);
    func_8012A828(s0, (void *)D_801F404C);
    *(s32 *)(s0 + 0x1C) = 0xA;
    *(s32 *)(s0 + 0xDC) &= ~1;
    func_80182380();
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_8012A828(s32 a0, void *a1);

extern void *D_80195144;
extern short D_801F40A4;

void func_80183558(s32 a0) {
    s32 v1;

    if (func_8012BEE8(a0) != 0) {
        v1 = ((s32 (*)(s32, s32))func_8012CC40)((int)a0, (int)&D_80195144);
        if (v1 & 0x8000) {
            *(s16 *)(a0 + 0x98) = 0;
            *(s16 *)(a0 + 0x2) = 0xA;
        } else if (v1 & 0x6000) {
            *(s16 *)(a0 + 0x2) = 8;
        } else if ((*(u32 *)(a0 + 0xDC) & 1) == 0 && *(s32 *)(a0 + 0x14) >= 0) {
            ((void (*)(s32, s32))func_8012A828)((int)a0, (int)&D_801F40A4);
            *(u32 *)(a0 + 0xDC) |= 1;
        }
    }
}


extern void func_8018452C(void);
    void func_8018360C(short *param) {
        param[1] = 0xB;
        func_8018452C();
    }


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80183630);

extern void func_8012AD80(s32 a0);

s32 func_80183954(s32 a0) {
    u8 *s0;
    s16 val;

    func_8012AD80(a0);
    s0 = (u8 *)a0;
    val = *(s16 *)(s0 + 0xA);
    return ((val - 0xB0) < -0xA01) ? 0 : 2;
}


extern s32 rand(void);
extern u8 D_801202A0[];
extern u8 D_801F3EFC[];
extern u8 D_801955F4[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012ADE4(u8 *a0);
extern void func_8012B260(u8 *a0);
extern void func_8017C294(s32 a0, s16 *a1, s16 a2);
extern s32 func_80183C2C();

s32 func_80183994(s32 a0, s32 a1) {
    s32 hit;
    u8 *p;
    s32 i;
    s32 t;

    hit = 0;
    p = D_801202A0;
    i = 0;
    do {
        if (*(u16 *)p == 0xB0) {
            if (hit == 0) {
                func_8012B260((u8 *)a0);
                hit = 1;
            }
            if (func_80183C2C(a0, p, a1) != 0) {
                func_8012ADE4((u8 *)a0);
                func_8012B260((u8 *)a0);
                *(s16 *)(a0 + 0x98) = 0;
                t = 0;
                if (func_80183C2C(a0, p, 4) != 1) {
                    return t;
                }
                *(s32 *)(a0 + 0xDC) |= 0x10;
                return 1;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);

    if (*(s16 *)(a0 + 0x98) == 0) {
        func_8012A828(a0, D_801F3EFC);
    }
    t = *(s32 *)(a0 + 0xE8) - 1;
    *(s32 *)(a0 + 0xE8) = t;
    if (t <= 0) {
        *(s32 *)(a0 + 0xE8) = 0x2D;
        if (rand() % 3 != 0) {
            goto ret0;
        }
        func_8017C294(a0, (s16 *)((rand() & 1) * 8 + (s32)D_801955F4), 1);
        func_8017C294(a0, (s16 *)((rand() & 1) * 8 + ((s32)D_801955F4 + 0x10)), 1);
    }
ret0:
    return 0;
}


extern void func_8012B14C(s32 a0, s32 a1);
extern s32 D_801950D8;
extern s32 D_801950E4;

s32 func_80183B30(s32 param_1, s32 param_2)
{
    unsigned short uVar2;

    switch (param_2) {
    case 0:
        *(unsigned int *)(param_1 + 0xdc) |= 0x20;
        return 1;
    case 1:
        if ((*(unsigned int *)(param_1 + 0xdc) & 4) != 0) {
            return 0;
        }
        uVar2 = *(unsigned short *)(param_1 + 0xfc) ^ 1;
        *(unsigned short *)(param_1 + 0xfc) = uVar2;
        func_8012B14C(param_1, (s32)&D_801950E4 + (s16)uVar2 * 12);
        *(unsigned int *)(param_1 + 0xdc) |= 4;
        break;
    case 2:
        if ((*(unsigned int *)(param_1 + 0xdc) & 4) == 0) {
            return 0;
        }
        func_8012B14C(param_1, (s32)&D_801950D8);
        *(unsigned int *)(param_1 + 0xdc) &= 0xfffffffb;
        break;
    }
    return 0;
}


extern s32 func_801840C0();

s32 func_80183C2C(s32 param_1, s32 param_2, u32 param_3)
{
    unsigned short sp10[3];
    unsigned short sp18[3];
    unsigned int addr;
    s32 ret;

    addr = (*(unsigned int *)(param_1 + 0x58) & 0xFFFFFFF) | 0x80000000;
    if (param_3 & 1) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    if (param_3 & 2) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    if (param_3 & 4) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    return 0;
}


extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_801840C0(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 sp10[2];
    s32 sp18[2];

    func_8012F214(a0, a2, (s32)sp10);
    func_8012F214(a0, a3, (s32)sp18);
    return func_80135888(*(s32 *)(a1 + 0x20), *(s32 *)(a1 + 0x58),
                         (s32)sp10, (s32)sp18) != 0;
}


extern void func_80184738(s32 a0);
extern void func_80188228(void);

void func_80184134(s32 param_1) {
    func_801823B8();
    *(s16 *)(param_1 + 2) = 0xD;
    *(s16 *)(param_1 + 0x34) = 0;
    func_80184738(1);
    func_80178BF8();
    func_80178CBC(param_1, *(s32 *)(param_1 + 0xCC));
    func_80188228();
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018418C);

#include "common.h"

extern void func_8018823C(void);
extern s32 func_800D0CE0(void);
extern void func_8012C218(void *a0);
extern u8 D_801952D8[];

void func_80184414(void *arg0) {
    if (*(void **)((char *)arg0 + 0xCC) != (void *)D_801952D8 || func_800D0CE0() != 0) {
        func_8018823C();
        func_8012C218(arg0);
    }
}


void func_8018446C(s32 param_1) {
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_80172670(s32 *a0);
    extern s32 func_80172658(s32 *a0);
    extern void func_801472DC(void);
    extern s32 D_80126B58;
    extern u16 D_80126B62;
    extern u8 D_801954B8[];
    extern u8 D_801952D8[];

    s32 *s0 = (s32 *)param_1;

    if (func_8012BEE8((s32)s0) == 0) {
        return;
    }

    {
        s32 *s1 = &D_80126B58;

        if (func_80172670(s1) != 0) {
            *(s16 *)((s32)s0 + 2) = 0xC;
        } else if (func_80172658(s1) != 0) {
            *(s16 *)((s32)s0 + 2) = 0xC;
        } else {
            return;
        }

        if (func_80172658(s1) != 0 && (s16)D_80126B62 < -0xA01) {
            func_8018490C(s0, (s32)D_801954B8, 3);
        } else {
            func_8018490C(s0, (s32)D_801952D8, 1);
            func_801472DC();
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018452C);

void func_80184590(s32 param_1) {
    extern u8 D_80126B5C;
    extern s32 func_8012C588(s32 a0, s32 a1);

    *(s32 *)(param_1 + 4) = *(s32 *)&D_80126B5C;
    func_8012C588(0xBA, param_1);
}


void func_801845C0(s32 param_1) {
    extern u8 D_80126B5C;
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

    *(s32 *)&D_80126B5C = *(s32 *)(param_1 + 4);
    func_8012C658(0xBA, 1, param_1);
}


s32 func_801845F4(s32 param_1) {
    extern s32 func_80172670(s32 *a0);
    extern s32 func_80172658(s32 *a0);
    extern void func_801746DC(void);
    extern void func_8018490C(s32 *a0, s32 a1, s16 a2);
    extern s32 D_80126B58;
    extern u8 D_801954B8[];
    extern u8 D_801953D8[];

    s32 *s0 = (s32 *)param_1;
    s32 *s1 = &D_80126B58;
    s32 var;

    if (func_80172670(s1) == 0 && func_80172658(s1) == 0) {
        return 0;
    }
    if (func_80172658(s1) != 0 && *(s16 *)((s32)s1 + 0xA) < -0xA01) {
        if ((*(u32 *)((s32)s0 + 0xDC) & 0x80) == 0) {
            func_801746DC();
            *(u32 *)((s32)s0 + 0xDC) |= 0x80;
        }
        var = *(u32 *)((s32)s0 + 0xDC);
        if ((var & 0x30) != 0) {
            return 0;
        }
        *(u32 *)((s32)s0 + 0xDC) = var & ~0x80;
        *(s16 *)((s32)s0 + 2) = 0xC;
        if ((*(u32 *)((s32)s0 + 0xDC) & 8) != 0) {
            func_8018490C(s0, (s32)D_801954B8, 3);
        } else {
            func_8018490C(s0, (s32)D_801953D8, 2);
            *(s16 *)((s32)s0 + 0x98) = 0;
        }
        return 1;
    } else {
        if ((*(u32 *)((s32)s0 + 0xDC) & 8) != 0) {
            func_801746DC();
            *(s32 *)((s32)s0 + 0x1C) = 0x10;
            *(s16 *)((s32)s0 + 2) = 0xF;
            return 1;
        }
        return 0;
    }
}


void func_80184738(s32 a0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p == 0xB0) {
            if ((*(u16 *)(p + 0x70) & 0xF) == 0) {
                *(s16 *)(p + 0xFC) = a0;
                *(u16 *)(p + 0x70) |= 0x800;
            }
        }
    }
}


void func_8018479C(void) {
    extern u16 D_80126B66;
    extern u16 D_80126B5E;
    extern s32 D_80195414;

    D_80195414 = ((u32)D_80126B5E | (((s32)(s16)D_80126B66 - 0x180) << 16));
}


extern void func_8012A568(void (*a0)(void));
    extern s32 func_8018263C();
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


#include "common.h"

extern s32 D_80126B60;
extern s32 D_80195640;
extern void func_8012B14C(s32 a0, s32 a1);

void func_8018487C(s32 param_1)
{
    s32 tmp;
    s32 iVar1;
    register s32 quot __asm__("$2");
    s32 scaled;
    s32 *p;

    tmp = *(s32 *)(param_1 + 8) + -0x900000;
    iVar1 = D_80126B60 - tmp;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0xfffff;
    }
    quot = iVar1 >> 0x14;
    scaled = quot << 0xf;
    if (scaled > 0) {
        scaled = 0;
    } else {
        if (scaled < -0x40000) {
            scaled = -0x40000;
        }
    }
    p = &D_80195640;
    __asm__("");
    *p = scaled + -0x20000;
    func_8012B14C(param_1, (s32)p - 4);
}


void func_8018490C(s32 *a0, s32 a1, s16 a2) {
        *(s32 *)((s32)a0 + 0xCC) = a1;
        *(s16 *)((s32)a0 + 0x102) = a2;
    }


extern void func_800D0C48(s32 a0);

void func_80184918(s32 arg0, s32 arg1) {
    func_800D0C48(1);
    *(s16 *)((s32)arg0 + 0x104) = 1;
    *(s32 *)((s32)arg0 + 0xE4) = 0x1E;
    *(s32 *)((s32)arg0 + 0xE0) = arg1;
}


extern s32 func_80143BDC(u16 *a0);

void func_80184964(s32 a0) {
    u16 pos[3];
    s32 hit;
    u32 ptr;

    pos[0] = *(u16 *)(a0 + 0x6);
    pos[1] = *(u16 *)(a0 + 0xA);
    pos[2] = *(u16 *)(a0 + 0xE);
    pos[1] += 0x28;
    pos[2] += 0x52;
    func_80143BDC(pos);
    hit = func_80143BDC(pos);
    if (hit != 0) {
        ptr = *(u32 *)(hit + 0xCC);
        *(u16 *)(ptr + 0x1A) = 0x6000;
        *(u16 *)(ptr + 0x18) = 0x6000;
    }
}


extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801F45D4;

void func_801849D4(s32 param_1) {
    if ((func_80029178(0x125) & 0xFF) != 0) {
        func_8012A828(param_1, &D_801F45D4);
        func_80029124(0x125, 0);
    }
}


s32 func_80184A28(s32 *a0) {
    return *(s16 *)((char *)a0 + 0xFE) == 0;
}


extern s32 func_800D0CE0(void);
    s32 func_80184A34(void) {
        return func_800D0CE0() != 0;
    }


extern u8 D_801202A0[];
extern void func_8012C098(void);

void func_80184A54(void)
{
    register int i __asm__("$17");
    register u8 *p __asm__("$16");
    register int s2 __asm__("$18");

    i = 0;
    p = D_801202A0;
    s2 = 0x6C;
    do {
        u16 v = *(u16 *)p;
        if ((u32)(v - 0x123) < 2 || v == s2) {
            ((void (*)(u8 *))func_8012C098)(p);
        }
        i = i + 1;
        p = p + 0x10C;
    } while (i < 0x60);
    return;
}



extern void (*D_801957F8[])(void);

void func_80184ACC(void *a0) {
    D_801957F8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);

void func_80184B08(s32 param_1) {
    extern u8 D_801CA540;
    extern u8 D_80195648;
    extern u8 D_80195734;
    extern s32 D_8019105C;
    extern u8 D_80126B5C;
    extern s32 D_80126B60;
    extern s32 D_80126B64;
    s32 v0;

    *(s16 *)(param_1 + 0x76) = 10;
    *(u16 *)(param_1 + 0x5C) = 0x8C00;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(v0, (s32)&D_801CA540);
        *(u32 *)(param_1 + 0x58) =
            (((*(u16 *)(param_1 + 0x70) & 1) << 4) + (s32)&D_80195648) | 0x60000000;
        if ((*(u16 *)(param_1 + 0x70) & 1) != 0) {
            *(s16 *)(param_1 + 2) = 2;
            *(u16 *)(param_1 + 0x5C) |= 0x200;
            func_8012A828(param_1, (void *)&D_8019105C);
            *(s32 *)(param_1 + 4) = *(s32 *)&D_80126B5C;
            *(s32 *)(param_1 + 8) = D_80126B60;
            *(s32 *)(param_1 + 0xC) = D_80126B64;
        } else {
            *(s16 *)(param_1 + 2) = 1;
            func_8012A828(param_1, (void *)&D_80195734);
        }
        func_8012B2CC(param_1);
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801F432C;
extern s32 D_80195744;

void func_80184C0C(s32 param_1) {
    *(u16 *)(param_1 + 6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
    *(u16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
    if (*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x90) == (s32)&D_801F432C) {
        *(s16 *)(param_1 + 2) = 3;
        func_8012A828(param_1, &D_80195744);
        *(s32 *)(param_1 + 0x1c) = 0xe;
    }
}


typedef struct { s16 a, b, c; } SV3_80184C98;
extern void func_8012B23C(s32 a0);
extern void func_80185098(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern u8 D_801957EC[];

void func_80184C98(s32 param_1) {
    SV3_80184C98 pt;
    u16 v1;
    s32 v0;

    v1 = *(u16 *)(param_1 + 0x5C);
    if (v1 & 1) {
        *(u16 *)(param_1 + 0x5C) = v1 & 0xFFFE;
        if (*(u16 *)(param_1 + 0x5E) == 9) {
            func_8012B23C(param_1);
            pt.a = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
            pt.b = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA);
            pt.c = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
            if (((s32 (*)(s32, s32))func_80185098)(param_1, (s32)&pt) == 1) {
                func_8012B14C(param_1, (s32)D_801957EC);
            }
            *(u16 *)(param_1 + 2) = 5;
        }
    }
}


typedef struct { s16 a, b, c; } SV3_80184D50;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801957EC[];
extern void func_8012B23C(s32 a0);
extern void func_80185098(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);

void func_80184D50(s32 param_1) {
    SV3_80184D50 pt;
    s32 t;
    u16 h;

    t = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = t;
    if (t == 0) {
        h = *(u16 *)(param_1 + 0xE);
        *(u16 *)(param_1 + 2) = 4;
        *(u16 *)(param_1 + 0x98) = 0;
        *(u16 *)(param_1 + 0xE) = h + 0x68;
        func_8012B23C(param_1);

        pt.a = D_80126B5E;
        pt.b = D_80126B62;
        pt.c = D_80126B66;
        if (((s32 (*)(s32, s32))func_80185098)(param_1, (s32)&pt) == 1) {
            func_8012B14C(param_1, (s32)D_801957EC);
        }
        func_8012AD80(param_1);
        *(s32 *)(param_1 + 0x1C) = 0x1E;
    }
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h, where the
 * real TU's SV3 {short a,b,c} lives (via ../shared/engine_core.h). Function-scoped local
 * name so it collides with nothing; integrator may drop this and reuse the TU's own SV3. */
typedef struct { s16 a, b, c; } SV3_80184E00;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801957CC;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8 D_801152A8[];

extern void func_80185098(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8014C978(void);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8001AAD0(s32 a0, s32 a1);

void func_80184E00(s32 param_1)
{
    SV3_80184E00 pt;
    SV3_80184E00 sv1;
    SV3_80184E00 sv2;

    pt.a = D_80126B5E;
    pt.b = D_80126B62;
    pt.c = D_80126B66;
    func_80185098(param_1, (s32)&pt);

    if (func_8012CBCC(param_1) & 0x6000) {
        *(s16 *)(param_1 + 2) = 6;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        return;
    }

    if (*(s16 *)(param_1 + 0xFC) != 0) {
        return;
    }

    func_8012F214(param_1, (s32)&D_801957CC, (s32)&sv1);
    func_8012F214(param_1, (s32)&D_801957CC + 8, (s32)&sv2);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&sv1, (s32)&sv2) == 0) {
        return;
    }

    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, (s32)&sv2, (s32)D_801152A8);

    *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x34) = 4;
    *(s16 *)(param_1 + 0xFC) = 1;
    func_8001AAD0(1, 0x4292);

    D_80126B66 = D_80126B66 + 0x20;
}


typedef struct { s16 a, b, c; } SV3_80184F48;
extern u8 D_801957DC;
extern void func_80185098(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8001AAD0(s32 a0, s32 a1);

void func_80184F48(s32 param_1)
{
    SV3_80184F48 sv1;
    SV3_80184F48 sv2;
    SV3_80184F48 pt;

    pt.a = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
    pt.b = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA);
    pt.c = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
    func_80185098(param_1, (s32)&pt);

    if (func_8012CBCC(param_1) & 0x6000) {
        *(s16 *)(param_1 + 2) = 6;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        return;
    }

    if (*(s16 *)(param_1 + 0xFC) != 0) {
        return;
    }

    func_8012F214(param_1, (s32)&D_801957DC, (s32)&sv1);
    func_8012F214(param_1, (s32)&D_801957DC + 8, (s32)&sv2);

    if (func_80135888(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20), *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x58), (s32)&sv1, (s32)&sv2) == 0) {
        return;
    }

    *(s16 *)(param_1 + 0xFC) = 1;
    *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x34) = 1;
    func_8001AAD0(1, 0x4331);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80185048(s32 param_1)
{
    s32 *temp_v0;

    temp_v0 = *(s32 **)(param_1 + 0x20);
    temp_v0[1] ^= 0x80000000;
    if (func_8012BEE8(param_1) != 0) {
        func_8012C218(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185098);


extern void (*D_801958B8[])(void);

void func_80185120(void *a0) {
    D_801958B8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018515C(void *param_1)
{
    extern u8 D_80195834[];
    extern u16 D_801958A8[];
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8012CAE4(void *a0);
    extern void func_8012C1B8(void);
    extern void func_8001C810(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);

    u16 f;
    u8 *s1;
    s32 v0;

    f = *(u16 *)((s32)param_1 + 0x70);
    s1 = &D_80195834[(f & 1) * 0x34];

    if ((f & 0x80) != 0) {
        *(s32 *)((s32)param_1 + 0x78) = (s32)s1;
        *(u16 *)((s32)param_1 + 0x5C) = *(u16 *)(s1 + 2);
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)((s32)param_1 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(param_1);
            return;
        }
        func_8001C810(v0, *(s32 *)(s1 + 4));
        *(s32 *)((s32)param_1 + 0x58) = *(s32 *)(s1 + 8) | 0x60000000;
        *(s32 *)(*(s32 *)((s32)param_1 + 0x20) + 4) |= 0x8000;
    } else {
        if (func_8012C354((s32)param_1, (s32)s1) == 0) {
            return;
        }
    }

    *(s32 *)((s32)param_1 + 0xDC) = 1;
    func_8012A828((s32)param_1, D_801958A8);
    *(u8 *)((s32)param_1 + 0x75) = 0;

    if ((*(s16 *)((s32)param_1 + 0x70) & 0x8000) != 0) {
        *(s16 *)((s32)param_1 + 2) = 1;
    } else {
        *(s16 *)((s32)param_1 + 2) = 3;
    }
}


void func_80185268(short *a0)
{
    *(u16 *)((char *)a0 + 0x2) = 2;

    if ((*(u16 *)((char *)a0 + 0x70) & 0x800) != 0) {
        if (*(s32 *)((char *)a0 + 0xDC) != 0) {
            *(s32 *)((char *)a0 + 0x1C) = 0x96;
        } else {
            *(s32 *)((char *)a0 + 0x1C) = 0x4B;
        }
    } else {
        if (*(s32 *)((char *)a0 + 0xDC) != 0) {
            *(s32 *)((char *)a0 + 0x1C) = 0x4B;
        } else {
            *(s32 *)((char *)a0 + 0x1C) = 0xB4;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_801852B0);

extern s32 func_80029178(s32 arg);

void func_80185388(void *a0) {
    *(s16 *)((char *)a0 + 2) = 4;
    if ((func_80029178(0x9E) & 0xFF) != 0) {
        *(s16 *)((char *)a0 + 0xFC) = 1;
    }
}


extern s32 func_80185548(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801853CC(s32 a0) {
    u16 v1 = *(u16 *)(a0 + 0x34);

    switch (v1) {
    case 0:
        if (*(s16 *)(a0 + 0xFC) != 0) {
            *(u16 *)(a0 + 0x34) = v1 + 1;
            func_8012B178(a0, 0xFFF80000);
            *(s32 *)(a0 + 0x1C) = 0x20;
        }
        break;
    case 1:
        if (func_80185548(a0) == v1) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 2:
        break;
    }
}


void func_80185464(void *a0) {
        s16 v0;
        v0 = *(s16 *)((char *)a0 + 0xfc);
        if (!v0) {
            *(s16 *)((char *)a0 + 0x2) = 2;
        }
    }


extern void func_80185480_dummy(void);
void func_80185480(void *a0) {
    extern s32 func_80185548(s32);
    extern void func_8018567C(s32, s32);

    if (func_80185548((s32)a0) == 1) {
        if ((*(s16 *)((s32)a0 + 0x70) & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 2) = 1;
        } else {
            *(s16 *)((s32)a0 + 2) = 3;
        }
        func_8018567C((s32)a0, 0x61B);
    }
}


void func_801854DC(void *a0) {
    extern s32 func_80185548(s32);
    extern void func_8018567C(s32, s32);

    if (func_80185548((s32)a0) == 1) {
        if ((*(s16 *)((s32)a0 + 0x70) & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 2) = 1;
        } else {
            *(s16 *)((s32)a0 + 2) = 3;
        }
        func_8018567C((s32)a0, 0x61B);
        *(u16 *)((s32)a0 + 0x5C) &= ~0x400;
    }
}


#include "common.h"

/* func_80185548 -- ov_SC02_011 / ov_SC02_011_jr_8017AE2C   [target: 77 ins]
 *
 * The engine "save camera vector, run the collision probe, restore on hit" body.
 * Structure lifted from src/shared/engine_core.h's DEFINE_func_8012E014 (the byte-proven
 * idiom for this exact func_8012F0BC / func_8012B2CC / func_8012F1A4 triad over the
 * D_80126B5C/60/64 vector).
 *
 * KEY FINDING (this is what closed the last 2 instructions):
 *   D_80126B5E / D_80126B62 / D_80126B66 are NOT independent globals -- they are the HIGH
 *   HALFWORDS of the 16.16 fixed-point words D_80126B5C / D_80126B60 / D_80126B64 (little
 *   endian: sym+2 is the integer part). Writing them as three separate `extern u16` symbols
 *   is byte-wrong in two ways at once:
 *     (a) gcc's memory disambiguator sees three distinct SYMBOL_REFs, finds NO dependency
 *         between `sw D_80126B64` and `lhu D_80126B66`, and sched1 hoists the free load to
 *         the top of the region -> 21 mismatches; and
 *     (b) papering over (a) by reusing ONE local for both the out[2] readback and the
 *         halfword refill merges them into a SINGLE pseudo whose live range now runs past
 *         the `addiu $a2, $sp, 0x40` argument setup, so it conflicts with $a2 and first-fit
 *         hands it $a3 -- the REGALLOC-PERM/$a3>$a2 residual (2 mismatches).
 *   Expressing the halfword as `*((u16 *)&gVecZ + 1)` fixes BOTH at once: the shared base
 *   gives sched1 the true memory dependency that keeps `sw` before `lhu`, AND the two values
 *   stay separate pseudos, so out[2] dies at the `sw` (free to take $a2) while the halfword
 *   lives into the jal delay slot (conflicts with $a2, takes $a3). Exactly the target.
 *   The %hi/%lo relocations come out against D_80126B5C/60/64 with in-place addend 2, which
 *   the HI16/LO16 pair resolves to D_80126B5E/62/66 -- identical linked bytes (same form the
 *   TU's constant-index global array accesses already emit).
 *
 * `base` (the unconditional `&D_80126B58` pointer local, computed before the `if`) is
 * load-bearing: it is what forces the 4-callee-saved-register frame (sw s1/ra/s2/s0) and
 * keeps the buffer base live in $s2 across the three intervening calls. Without it only 3
 * regs are saved and every later stack offset drifts by a word.
 */

s32 func_80185548(s32 param_1) {
    /* asm-label alias per engine_core.h DEFINE_func_8012E014: the TU already carries
     * `extern u8 D_80126B5C;`, so a plain `extern s32 D_80126B5C;` is a conflicting-types
     * hard error, and the cast-at-use `*(s32 *)&D_80126B5C` form makes gcc force_reg the
     * constant address (+ CSE'd `la` pseudos). The alias gives a real s32 object at the same
     * assembler symbol, so every access stays a direct lw/sw. */
    extern s32 gVecX __asm__("D_80126B5C");
    extern s32 gVecY __asm__("D_80126B60");
    extern s32 gVecZ __asm__("D_80126B64");
    extern s32 D_80126B58;
    extern void func_8012AD80(s32 a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
    extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern s32 func_8012BEE8(s32 a0);
    s32 in[4];
    s32 out[4];
    s32 tmp[4];
    u8 buf[8];
    u8 *base = (u8 *)&D_80126B58;

    func_8012AD80(param_1);
    if (*(u8 *)(param_1 + 0x74) != 0) {
        in[0] = gVecX;
        in[1] = gVecY;
        in[2] = gVecZ;
        func_8012F0BC((s32 *)(*(s32 *)(param_1 + 0x20) + 0x34), in, tmp);
        func_8012B2CC(param_1);
        func_8012F1A4((s32 *)(*(s32 *)(param_1 + 0x20) + 0x34), (s32)tmp, out);
        gVecX = out[0];
        gVecY = out[1];
        gVecZ = out[2];
        *(s16 *)(buf + 0) = *((u16 *)&gVecX + 1);
        *(s16 *)(buf + 2) = *((u16 *)&gVecY + 1);
        *(s16 *)(buf + 4) = *((u16 *)&gVecZ + 1);
        if ((func_80133784(1, base + 0x88, (s32)buf) & 0x8000) != 0) {
            gVecX = in[0];
            gVecY = in[1];
            gVecZ = in[2];
        }
    }
    return func_8012BEE8(param_1) != 0;
}


#include "common.h"

extern s32 D_80126B58;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80013478(s32 a0, s32 a1);

s32 func_8018567C(s32 a0, s32 a1) {
    s32 v1 = a0;
    s32 s1 = a1;
    s32 s0 = 0;
    extern u16 D_80126B62;
    s16 val = (s16) D_80126B62;
    s32 base = (s32) &D_80126B58;
    s32 dist;
    s32 v0;

    if (val < -0x981) {
        return 0;
    }

    dist = func_80013478(base + 4, v1 + 0x88);
    if (dist <= 0x190000) {
        dist -= 0x4000;
        s0 = 0x60;
        if (dist > 0xC7FFF) {
            register s32 tmp __asm__("$3") = dist - 0xC8000;
            v0 = tmp / 8533;
        } else {
            v0 = dist / 26425 - 31;
        }
        s0 -= v0;
    }

    func_8002D4C8(s1 & 0xFFFF, (s0 & 0x7F) | 0x1000);
    return 1;
}




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

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

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

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

void func_8018576C(u8 *vb)
{
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    register u8 *p __asm__("$4");
    register s32 t1 __asm__("$9");
    register s32 i __asm__("$11");
    register s32 t0 __asm__("$8");
    register s32 k __asm__("$2");
    u8 *pkt;
    u32 *ot;
    u32 *otp;
    u8 *v4;
    s32 flag, flag2, otz;
    s32 d;
    s32 z;
    u32 mAnd;
    u32 mOr;
    short vv[16];
    s16 vz0;

#define RS(o) (*(s16 *)((s32)vb + (o)))

    p = (u8 *)(((*(u32 *)((s32)vb + 0x58)) & 0xFFFFFFF) | 0x80000000);
    vv[1] = RS(0x8A) + *(u16 *)(p + 8) - 0x40;
    vv[5] = RS(0x8A) + *(u16 *)(p + 8) - 0x40;
    vv[9] = RS(0x8A) + *(u16 *)(p + 0xA) + 0x40;
    vv[13] = RS(0x8A) + *(u16 *)(p + 0xA) + 0x40;
    vz0 = RS(0x8C) - 0x50;
    ot = (u32 *)&D_800A6610[((u16)D_800B9A02) << 14];
    vv[14] = vz0;
    vv[10] = vz0;
    vv[6] = vz0;
    vv[2] = vz0;
    d = *(s16 *)(p + 4);
    if ((d - 0x20) >= 0) {
        z = (d - 0x20) / 2;
    } else {
        z = (0x20 - d) / 2;
    }
    i = -2;
    v4 = (u8 *)&vv[4];
    mOr = 0xFFFFFF;
    mAnd = 0xFF000000;
    k = -2 * z;
    t1 = k + z;
    t0 = k;
    for (; i < 2; i++) {
        pkt = D_800A5E60;
        D_800A5E60 = pkt + 0x18;
        *(u8 *)(pkt + 3) = 5;
        *(u32 *)(pkt + 4) = 0;
        *(u8 *)(pkt + 7) = 0x28;
        vv[0] = vv[8] = RS(0x88) + t0;
        vv[4] = vv[12] = RS(0x88) + t1;
        gte_ldv3(&vv[0], v4, &vv[8]);
        gte_rtpt();
        gte_stflg(&flag);
        gte_stsxy3(pkt + 8, pkt + 0xC, pkt + 0x10);
        gte_ldv0(&vv[12]);
        gte_rtps();
        gte_stflg(&flag2);
        flag |= flag2;
        gte_stsxy(pkt + 0x14);
        gte_avsz4();
        gte_stotz(&otz);
        if ((flag & ~0x1000) == 0) {
            s32 tt = otz + 0x29;
            if (tt > 0xFFF) {
                tt = 0x1000;
            }
            otp = (u32 *)(tt * 4 + (u32)ot);
            *(u32 *)pkt = (*(u32 *)pkt & mAnd) | (*(u32 *)otp & mOr);
            *(u32 *)otp = (*(u32 *)otp & mAnd) | ((u32)pkt & mOr);
        }
        t1 += z;
        t0 += z;
    }
#undef RS
}



extern void (*D_801958E8[])(void);

void func_801859E0(void *a0) {
    D_801958E8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern u8 D_801958D8[];
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);

void func_80185A1C(void *a0) {
    s32 ret;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(ret, 0);
    *(u16 *)((u8 *)a0 + 0x2) = 1;
    *(u16 *)((u8 *)a0 + 0x5C) = 0x40;
    *(s32 *)((u8 *)a0 + 0x58) = (u32)D_801958D8;
}


void func_80185A84(void) {
}

















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80185A8C(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 1);
  new_var = 0x100000;
}

void func_80185AAC(s32 arg0)
{
    extern u8 D_801958F0[];
    extern s32 D_801958F4;
    extern s32 D_801958F6;
    extern s32 D_801958F8;
    extern s32 D_801958FA;
    extern s32 D_801958FC;
    extern s32 D_801958FE;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_80185BA4(void *a0);
    u8 *a2 = D_801958F0;
    s16 self6;
    s16 selfA;
    s16 selfE;

    self6 = *(s16 *)(arg0 + 0x6);
    if (self6 + *(s16 *)&D_801958F4 < *(s16 *)&D_80126B5E &&
        *(s16 *)&D_80126B5E < self6 + *(s16 *)&D_801958F6) {
        selfA = *(s16 *)(arg0 + 0xA);
        if (selfA + *(s16 *)&D_801958F8 < *(s16 *)&D_80126B62 &&
            *(s16 *)&D_80126B62 < selfA + *(s16 *)&D_801958FA) {
            selfE = *(s16 *)(arg0 + 0xE);
            if (selfE + *(s16 *)&D_801958FC < *(s16 *)&D_80126B66 &&
                *(s16 *)&D_80126B66 < selfE + *(s16 *)&D_801958FE) {
                *(u32 *)(arg0 + 0x58) = (u32)(a2 + 0x10) | 0x40000000;
                *(s16 *)(arg0 + 0x5C) = 0x800;
                func_80185BA4(arg0);
            }
        }
    }
}


extern void func_800D0C48(s32 a0);
extern void (*D_80195910[])(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80185BA4(s32 a0) {
    func_800D0C48(1);
    *(s32 *)(a0 + 0x1C) = 0x20;
    func_80178B18(a0, (s32) D_80195910);
    func_8012AD44((s32 *)a0, 2);
}


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


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801865B0(s32 arg0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801E5340;
extern u8 D_8019595C;
extern s32 D_801EB518;
extern u8 D_80195968;
extern u8 D_801959B8;
extern u8 D_80195998;
extern u8 D_80195A94;

void func_80185C7C(s32 a0) {
    register s32 self __asm__("$17") = a0;
    register s32 obj  __asm__("$16");
    s32 h;
    s32 v0;
    u16 v1;
    s32 pad[8];

    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(self + 0x20) = h;
    if (h == 0) {
        goto L_fail;
    }

    if (*(s16 *)(self + 0x70) != 0) {
        goto L_da8;
    }

    func_8001C214(h, (s32)&D_801E5340);
    obj = ((s32 (*)(void))func_8012C194)();
    *(s32 *)(self + 0xCC) = obj;
    if (obj != 0) {
        goto L_ce4;
    }

L_fail:
    func_8012CAE4((void *)self);
    return;

L_ce4:
    func_8001CB6C((u8 *)obj, (s32)&D_8019595C, 0x2F0, 0x138);
    func_801865B0(self);

    *(u16 *)(obj + 0x18) = 0x2200;
    *(u16 *)(obj + 0x1A) = 0x1600;
    *(u8 *)(obj + 0x27) = 0xED;
    *(u32 *)(obj + 4) |= 0x51000000;
    func_80128EA8(obj, (s32)&(*(u8 *)&D_801EB518), (s32)&D_80195968);

    *(u8 *)(self + 0xC0) = 1;
    *(s32 *)(self + 0xBC) = (s32)&D_801959B8;
    *(s32 *)(self + 0x58) = (s32)&D_80195998 | 0x40000000;
    *(u16 *)(self + 0x5C) = 0x8000;
    *(s16 *)(self + 0xAE) = -3;

    v0 = *(s32 *)(self + 0xC4);
    v1 = *(u16 *)(self + 0xA);
    *(s32 *)(self + 0xB4) = 0;
    *(u8 *)(self + 0xC1) = 0;
    *(s32 *)(self + 0xC4) = v0 | 2;
    *(u16 *)(self + 0xFE) = v1;
    func_8012AD50((void *)self);
    return;

L_da8:
    func_8001CA1C(h, 0);

    *(u16 *)(*(s32 *)(self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)(self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)(self + 0x20) + 4) |= 0x71000000;

    *(s32 *)(self + 0x14) = 0xFFFE0000;
    *(s32 *)(self + 0x18) = 0xFFFD0000;

    func_8012A828(self, &D_80195A94);
    func_8012AD44((s32 *)self, 0xA);
}


#include "common.h"

extern void func_8013CABC(void);
extern void func_80186728(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186070(s32 a0);
extern s32 func_80185FA0(s32 a0);
extern int func_80178970(void);
extern s32 func_80188114(void);
extern s32 D_801EB520;

void func_80185E20(s32 a0) {
    s32 t;
    u16 delta;
    u16 cnt;

    t = *(s32 *)(a0 + 0x1C);
    if (t == 0x30) {
        func_8013CABC();
    } else if (t == 0x10) {
        func_80186728(*(void **)(a0 + 0xD0));
    }

    if (*(u16 *)(a0 + 0x102) & 1) {
        *(u16 *)(*(s32 *)(a0 + 0x64) + 6) -= 3;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 8) -= 3;
        delta = *(u16 *)(a0 + 6) - 3;
    } else {
        *(u16 *)(*(s32 *)(a0 + 0x64) + 6) += 3;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 8) += 3;
        delta = *(u16 *)(a0 + 6) + 3;
    }
    *(u16 *)(a0 + 6) = delta;

    {
        u16 raw = *(u16 *)(a0 + 0x102);
        s32 old = D_801EB520;
        cnt = raw + 1;
        *(u16 *)(a0 + 0x102) = cnt;
        if (old == 0) {
            D_801EB520 = func_80188114();
        }
    }

    if (func_8012BEE8(a0) != 0 && D_801EB520 != 0) {
        func_80186070(a0);
    } else {
        t = *(s32 *)(a0 + 0x1C);
        if (t < 0x48 && (t & 3) == 0) {
            func_80185FA0(a0);
        }
    }
    ((s32 (*)(s32))func_80178970)(a0);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80185FA0);


extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018FE20(s32 a0);
extern void func_80186734(void *a0);
extern void func_8018ADE4(void);
extern void func_8018AE08(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186070(s32 a0) {

    extern u8 D_801959C8[];
    register s32 obj  __asm__("$16");            /* $s0 */
    register s32 self __asm__("$17") = a0;       /* $s1 */
    s32 t0;
    s32 t1;
    s32 t2;

    obj = *(s32 *)(self + 0x20);
    func_8001CA1C(obj, (s32)D_801959C8);

    *(u16 *)(self + 0xA) = *(u16 *)(self + 0xA) - 0xA0;
    *(u16 *)(self + 0xE) = *(u16 *)(self + 0xE) - 0x10;
    *(u16 *)(obj + 0x18) = 0x2C00;
    *(u16 *)(obj + 0x1A) = 0x1C00;
    *(u32 *)(obj + 4) = *(u32 *)(obj + 4) | 0x1000000;

    t0 = *(s32 *)(self + 0xCC);
    *(u16 *)(t0) = 0;
    *(s32 *)(self + 0xCC) = func_80143970(self);

    *(s32 *)(self + 0x14) = 0xFFF80000;
    *(u16 *)(self + 0x5C) = 0;
    *(s32 *)(self + 0x1C) = 8;
    func_8012AD44((s32 *)self, 3);

    obj = *(s32 *)(self + 0x64);
    t1 = *(s32 *)(obj + 0x20);
    *(u32 *)(t1 + 4) = *(u32 *)(t1 + 4) | 0x80000000;
    func_8018FE20(obj);

    *(u16 *)(obj + 0x5C) = 0;
    func_8012AD44((s32 *)obj, 4);

    t2 = *(s32 *)(self + 0xD0);
    if (t2 != 0) {
        *(u16 *)(t2 + 0x2C) = 0;
        func_80186734((void *)t2);
    }

    func_8018ADE4();
    func_8018AE08(self + 4);

    func_8002D4C8(0x5ED, 0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186790(void *a0);
extern u8 D_80195A94;

void func_80186184(s32 a0) {
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3800;
    func_8012A828(a0, &D_80195A94);
    *(u16 *)(a0 + 0xFC) = 0;
    *(s32 *)(a0 + 0x1C) = 0x10;
    func_8012AD44((s32 *)a0, 4);
    if (*(s32 *)(a0 + 0xD0) != 0) {
        func_80186790(*(void **)(a0 + 0xD0));
    }
}


#include "common.h"

extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801867BC(void *a0);

void func_801861FC(void *arg0) {
    register s32 s0 __asm__("$16") = (s32)arg0;
    s32 val;

    *(s32 *)(s0 + 0x1C) = 4;
    func_8012B200((u8 *)s0);
    func_8012AD44((s32 *)s0, 5);

    val = *(s32 *)(s0 + 0xD0);
    if (val != 0) {
        func_801867BC((void *)val);
    }
}


void func_80186250(s32 arg0) {
    extern void func_80186548(s32 *a0);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern s8 D_801959A8[];

    *(s32 *)((s32)arg0 + 0x58) = (s32)&D_801959A8;
    func_80186548((s32 *)arg0);
    func_8012AD44((s32 *)arg0, 6);
}


s32 func_80186290(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x6;
    }


#include "common.h"

extern s32 func_801439C0(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801292C8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_801862A4(int a0)
{
    register s32 s0 __asm__("$16") = a0;
    u8 *ptr;
    s32 val1;
    s32 val2;
    s32 t2;

    func_801439C0(*(s32 *)(s0 + 0xCC));
    func_8012B200((u8 *)s0);

    *(s32 *)(s0 + 0x14) = 0x80000;
    *(u16 *)(s0 + 0x6) = D_80126B5E;
    *(u16 *)(s0 + 0xE) = D_80126B66;

    ptr = *(u8 **)(s0 + 0x20);
    val1 = *(u16 *)(ptr + 0x18);
    *(s16 *)(s0 + 0xDC) = (val1 << 16) >> 19;

    ptr = *(u8 **)(s0 + 0x20);
    val2 = *(u16 *)(ptr + 0x1A);
    *(s16 *)(s0 + 0xDE) = (val2 << 16) >> 19;

    func_8012AD44((s32 *)s0, 7);

    t2 = *(s32 *)(s0 + 0xD0);
    if (t2 != 0) {
        func_801292C8((u8 *)t2);
    }

    func_8002D4C8(0x635, 0);
}


extern s32 func_80188168(void);
    void func_80186354(void) {
        func_80188168();
    }


extern s32 func_8013CAE8(void);
    void func_80186374(void) {
        func_8013CAE8();
    }


extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186394(s32 a0) {
    func_8012AD44((s32 *)a0, 8);
    *(s32 *)(a0 + 0x1C) = 0x40;
    func_8002D4C8(0x5EC, 0);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801863D4(void *a0) {
    func_8012AD44((s32 *)a0, 9);
}



extern void (*D_80195CC4[])(void);

void func_801863F4(void *a0) {
    D_80195CC4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_80195CF0[];
extern s32 D_801EB520;
extern void (*D_80195B5C[])(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001AAA0(s32 arg);

void func_80186430(s32 a0) {
    register s32 self __asm__("$16") = a0;
    u32 idx;
    s32 t0;
    s32 t1;

    for (idx = 0; idx < 8; idx++) {
        if (*(u16 *)(self + 0x5E) == D_80195CF0[idx]) {
            {
                u16 tmp;
                t0 = *(s32 *)(self + 0x64);
                tmp = *(u16 *)(t0 + 6);
                D_801EB520 = 0;
                *(u16 *)(t0 + 6) = tmp + 1;
            }
            *(s32 *)(self + 0x1C) = 0x50;
            *(u16 *)(self + 0x102) = 0;
            *(u16 *)(self + 6) = *(u16 *)(self + 6) + 1;
            func_8012AD44((s32 *)self, 2);

            t1 = func_80132EF4(self, 0x32);
            *(s32 *)(self + 0xD0) = t1;
            if (t1 != 0) {
                u16 vE;
                *(u16 *)(t1 + 6) = *(u16 *)(self + 6);
                *(u16 *)(t1 + 0xA) = *(u16 *)(self + 0xA);
                vE = *(u16 *)(self + 0xE);
                *(s16 *)(t1 + 0x2C) = -0xA0;
                *(s32 *)(t1 + 0x34) = self;
                *(u16 *)(t1 + 0xE) = vE;
            }

            func_80178B18(self, (s32) D_80195B5C);

            *(u8 *)(self + 0xC1) = 0;
            *(u16 *)(self + 0x5C) = 0;
            *(u16 *)(self + 0x5E) = 0;
            func_8002D4C8(0x5EB, 0);
            func_8001AAA0(0x30);
            *(u16 *)(self + 0x5E) = 0;
            goto end;
        }
    }
    *(u16 *)(self + 0x5E) = 0;
end:
    func_8002D4C8(0x426, 0);
}


void func_80186548(s32 *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


void func_80186558(s32 a0) {
    s32 v;

    func_8012AD80(a0);
    v = *(s32 *)(a0 + 0x14);
    if (v > 0x14000) {
        *(s32 *)(a0 + 0x48) = -0x1400;
    } else if (v < -0x14000) {
        *(s32 *)(a0 + 0x48) = 0x1400;
    }
}


void func_801865B0(s32 arg0) {
        s32 *p = *(s32 **)((s32)arg0 + 0xcc);
        *(u16 *)((s32)p + 0x8) = *(u16 *)((s32)arg0 + 0x6);
        *(s16 *)((s32)p + 0xa) = *(u16 *)((s32)arg0 + 0xa) - 0xe0;
        *(s16 *)((s32)p + 0xc) = *(u16 *)((s32)arg0 + 0xe) - 0x10;
    }


int func_801865E4(int a0, void* a1)
{
    s16 stack_buf[8];
    register s16 *s0 __asm__("$16") = (s16 *)a1;
    s16 v0;
    s32 result;
    s32 ret;

    v0 = s0[2];
    stack_buf[0] = v0;
    v0 = s0[3];
    stack_buf[4] = v0;
    v0 = s0[5];
    stack_buf[5] = v0;
    stack_buf[1] = v0;
    v0 = s0[6];
    stack_buf[6] = v0;
    stack_buf[2] = v0;

    result = func_80186680((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = s0[7];
        stack_buf[6] = v0;
        stack_buf[2] = v0;
        result = func_80186680((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}


extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

s32 func_80186680(s32 arg0, s32 arg1, s32 arg2)
{
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    struct { u16 x, y, z, w; } a;
    struct { u16 x, y, z, w; } b;

    func_8012F214(arg0, arg1, &a);
    func_8012F214(arg0, arg2, &b);
    func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b);
}


extern s32 func_8017E358();
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


s32 func_80186740(void)
{
    typedef struct { unsigned char b[4]; } __attribute__((packed, aligned(1))) Block4;

    extern Block4 D_801EB524;
    extern unsigned char D_801EB525;
    extern unsigned char D_801EB526;

    unsigned char *p = (unsigned char *)&D_801EB524;

    if (*p < 0xF8U) {
        *p += 4;
        D_801EB525 += 4;
        D_801EB526 += 8;
    }
}



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
extern void func_80186818();
extern void (*D_80195D18[])(int);

void func_801867CC(int param_1)
{
    ((void (*)(void))func_80186818)();
    D_80195D18[*(unsigned short *)(param_1 + 2)](param_1);
}


extern void func_80129350(s32 *a0, s32 a1);
extern void func_80133060(s32 *a0, s32 a1, s32 a2);

void func_80186818(s32 *a0) {
    s32 *s0;
    s32 a1;

    s0 = a0;
    a1 = *(s32 *)((u8 *)s0 + 0x34);
    func_80129350(s0, a1);

    a1 = (s32)((u8 *)s0 + 0x4);
    *(s16 *)((u8 *)s0 + 0xA) = *(u16 *)((u8 *)s0 + 0xA) + *(u16 *)((u8 *)s0 + 0x2C);
    func_80133060((s32 *)((u8 *)s0 + 0x4), a1, -0x180);
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80186868);

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186AA0(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        func_8002D4C8(4, 0x646);
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



extern void (*D_80195D40[])(void);

void func_80186AE0(void *a0) {
    D_80195D40[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

s32 func_80186B1C(void *a0, void *a1) {
    s16 stack_buf[8];
    register s16 *s0 __asm__("$16") = (s16 *)a1;
    s16 v0;
    s32 result;
    s32 ret;

    v0 = s0[6];
    stack_buf[2] = v0;
    v0 = s0[7];
    stack_buf[5] = 0;
    stack_buf[1] = 0;
    stack_buf[6] = v0;
    v0 = s0[2];
    stack_buf[4] = v0;
    stack_buf[0] = v0;

    result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = s0[3];
        stack_buf[4] = v0;
        stack_buf[0] = v0;
        result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80186BB0(void *a0) {
    register s32 v0 __asm__("$2");
    s32 sp10[3];

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (!v0) {
        func_8012CAE4(a0);
    } else {
        func_8001C2C4(v0);

        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x600;
        func_8012B2CC((s32)a0);

        sp10[1] = 0;
        sp10[0] = 0;
        sp10[2] = 0x240000;
        func_8012B14C((s32)a0, (s32)sp10);

        func_8012AD50(a0);
    }
}


void func_80186C30(s32 a0) {
    register s32 self __asm__("$16") = a0;
    s32 v0;
    extern s32 func_80029178(s32);
    extern void func_8012C1B8(void);
    extern void func_8001C214(s32, s32);
    extern s32 func_8012C588(s32, s32);
    extern void func_8012CAE4(void *);
    extern void func_80185A8C(void);
    extern s32 D_801E4D54;

    if ((func_80029178(0x16) & 0xFF) != 0) {
        goto L88;
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(self + 0x20) = v0;
    if (v0 == 0) {
        goto L88;
    }
    func_8001C214(v0, (s32)&D_801E4D54);
    v0 = func_8012C588(0x110, self);
    if (v0 != 0) {
        goto L98;
    }
L88:
    func_8012CAE4((void *)self);
    goto LCA0;
L98:
    ((void (*)(s32))func_80185A8C)(self);
LCA0:
    return;
}


void func_80186CB4(s32 a0)
{
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_80185C20(void);

    s32 s0 = a0;
    s32 ret = func_80178970();

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) += 1;
        }
        break;
    case 1:
        if (ret == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)(s0);
        ((void (*)(s32))func_80185C20)(s0);
        break;
    }
}


void func_80186D3C(void) {
}

void func_80186D44(void) {
}

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
    extern s32 D_801EB518;
    void func_80186D4C(void *arg0) {
        ((void (*)(s32, s32))func_80128ED8)(M2C_FIELD(arg0, s32 *, 0xCC), &D_801EB518);
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186184(s32 a0);
extern void func_80186548(s32 *a0);
extern void func_80186558(s32 a0);
extern int func_80178970(void);
extern void func_8018B1B0(void);

void func_80186D78(s32 *a0) {
    if (*(u16 *)((s32)a0 + 0x34) == 0) {
        func_8012AD80((s32)a0);
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((s32)a0 + 0x100) = 0x80;
            *(s32 *)((s32)a0 + 0x1C) = 0x30;
            (*(u16 *)((s32)a0 + 0x34))++;
            func_80186548(a0);
        }
    } else {
        if (func_8012BEE8((s32)a0) != 0) {
            func_80186184((s32)a0);
        } else {
            func_80186558((s32)a0);
        }
    }
    ((int (*)(s32))func_80178970)((s32)a0);
    func_8018B1B0();
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern int func_80178970(void);

void func_80186E24(s32 a0) {
    if (func_8012BEE8(a0) == 0) {
        if ((*(s32 *)(a0 + 0x1C) & 3) == 0) {
            func_8012C658(0x110, 1, a0);
        }
    }
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_801861FC(a0);
    }
    ((s32 (*)(s32))func_80178970)(a0);
}


extern int func_80178970(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_80186250(s32 a0);

    void func_80186E94(s32 arg0) {
        u16 val_34;
        s16 val_fe, val_a;
        val_34 = *(u16 *)(arg0 + 0x34);
        if (val_34 == 0) {
            if (func_8012BEE8(arg0) != 0) {
                *(s32 *)(arg0 + 0x14) = 0x10000;
                *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            }
        } else {
            val_fe = *(s16 *)(arg0 + 0xFE);
            val_a = *(s16 *)(arg0 + 0xA);
            if (val_a < (val_fe - 0xA0)) {
                func_8012AD80(arg0);
            } else {
                func_80186250(arg0);
            }
        }
        ((void (*)(s32))func_80178970)(arg0);
    }


    extern int func_80178970(void);
    extern void func_80186558(int a0);
    extern int func_801865E4(int a0, void *a1);
    extern void func_801862A4(int a0);
    extern char D_801959A8[];
    void func_80186F24(int param_1)
    {
        ((void (*)(void))func_80178970)();
        func_80186558(param_1);
        if (func_801865E4(param_1, (void *)&D_801959A8) != 0) {
            func_801862A4(param_1);
        }
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern int func_80178970(void);

void func_80186F74(s32 a0) {
    s32 t0;
    s16 val0;

    t0 = *(s32 *)(a0 + 0x20);
    val0 = *(s16 *)(t0 + 0x18);

    if (val0 > 0) {
        s32 temp;
        s16 val;
        u16 a, b;
        u32 flags;

        func_8012AD80(a0);

        temp = *(s32 *)(a0 + 0x20);
        a = *(u16 *)(a0 + 0xDC);
        b = *(u16 *)(temp + 0x18);
        *(s16 *)(temp + 0x18) = (s16)(b - a);

        temp = *(s32 *)(a0 + 0x20);
        a = *(u16 *)(a0 + 0xDE);
        b = *(u16 *)(temp + 0x1A);
        *(s16 *)(temp + 0x1A) = (s16)(b - a);

        temp = *(s32 *)(a0 + 0x20);
        val = *(s16 *)(temp + 0x18);

        if (val == 0) {
            flags = *(u32 *)(temp + 0x04);
            flags |= 0x80000000;
            *(u32 *)(temp + 0x04) = flags;
        }
    }

    ((void (*)(s32))func_80178970)(a0);
}


#include "common.h"

extern int func_80178970(void);
extern void func_8013C9C4(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void (*D_80195CAC[])(void);
extern void func_801863D4(void *a0);

void func_80187018(s32 a0)
{
    s32 s0 = a0;

    func_80178970();
    if ((*(u32 *)(s0 + 0x1C) & 0xF) == 0) {
        func_8013C9C4(&D_80195CAC);
    }
    if (func_8012BEE8(s0) != 0) {
        func_801863D4((void *)s0);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012C218(void *a0);

void func_8018707C(s32 a0)
{
    extern s16 D_801EBA08;

    if (func_80178970() == 0) return;
    if (D_801EBA08 != 0) return;
    ((void (*)(s32))func_80178D18)(a0);
    ((void (*)(s32))func_8012C218)(a0);
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_801870D0(s32 param_1) {
    s32 s0;

    s0 = param_1;
    func_8012AD80(s0);
    if (*(s16 *)(s0 + 0x98) == 0) {
        func_8012C218((void *)s0);
    }
}


#include "common.h"

extern void func_8001CD9C(s32, void *);
extern void func_800233CC(void *, u16);


extern Block4 D_801E9E30;
extern Block4 D_801EB524;
extern Block4 D_801EB528;

void func_80187110(s32 a0) {
    register u8 *s0 __asm__("$16");
    register s32 *s1 __asm__("$17");
    s32 *v1;
    s32 *a0_ptr;
    s8 pad[32];  /* Force larger stack frame */

    s1 = (s32 *)a0;
    s0 = (u8 *)&D_801EB524;

    // Call func_8001CD9C with field at offset 0x20 in s1, and s0
    func_8001CD9C(s1[8], (s32 *)s0);  // 0x20 / 4 = 8

    // Call func_800233CC with s0 and 0x80
    func_800233CC(s0, 0x80);

    // Copy 4 bytes from D_801E9E30 to D_801EB524
    *(Block4 *)s0 = D_801E9E30;

    // Copy 4 bytes from D_801E9E30 to D_801EB528
    D_801EB528 = D_801E9E30;

    // Set field at offset 0x18 to 0x800
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x18) = 0x800;

    // Set field at offset 0x1A to 0x1000
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x1A) = 0x1000;

    // OR field at offset 0x4 with 0x50000000
    a0_ptr = s1[8];
    *(s32 *)((s8 *)a0_ptr + 0x4) |= 0x50000000;

    // Set field at offset 0x2 in s1 to 1
    *(s16 *)((s8 *)s1 + 0x2) = 1;

    (void)pad;  /* Avoid warning */
}



extern Block4 D_801EB524;
extern u8 D_801EB525;
extern u8 D_801EB526;

void func_801871CC(void) {
    if (D_801EB524.b[0] < 0xc0) {
        D_801EB524.b[0] += 4;
    }
    if (D_801EB525 < 0xc0) {
        D_801EB525 += 4;
    }
    if (D_801EB526 < 0x20) {
        D_801EB526 += 4;
    }
}


extern s32 func_80186740(void);
    void func_80187234(void) {
        func_80186740();
    }


extern s32 func_80186740(void);

void func_80187254(s32 arg0) {
    s32 a0 = *(s32 *)(arg0 + 0x20);
    if (*(s16 *)(a0 + 0x18) < 0x6000) {
        *(s16 *)(a0 + 0x18) = *(s16 *)(a0 + 0x18) + 0x800;
    }
    if (*(s16 *)(a0 + 0x1A) < 0x6000) {
        *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x1A) + 0x800;
    }
    func_80186740();
}



extern Block4 D_801EB524;
extern unsigned char D_801EB525;
extern unsigned char D_801EB526;

void func_801872B4(s32 arg0) {
    s32 a0;
    u32 v1;

    __asm__("":: : "memory");
    a0 = *(s32 *)(arg0 + 0x20);
    if (*(s16 *)(a0 + 0x18) > 0x800) {
        *(s16 *)(a0 + 0x18) = *(s16 *)(a0 + 0x18) - 0x200;
    }
    if (*(s16 *)(a0 + 0x1A) > 0x800) {
        *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x1A) - 0x200;
    }
    v1 = D_801EB524.b[0];
    if (v1 >= 0xC1) {
        D_801EB524.b[0] = v1 - 4;
        D_801EB525 -= 4;
        D_801EB526 -= 8;
    }
}



extern Block4 D_801EB524;
extern u8 D_801EB525;
extern u8 D_801EB526;

void func_8018734C(void *a0) {
    s16 *p;
    s32 t;
    u8 v;
    p = *(s16 **)((s32)a0 + 0x20);
    if (*(s16 *)((s32)p + 0x18) > 0x800) {
        *(s16 *)((s32)p + 0x18) = *(s16 *)((s32)p + 0x18) - 0x200;
    }
    if (*(s16 *)((s32)p + 0x1A) > 0x800) {
        *(s16 *)((s32)p + 0x1A) = *(s16 *)((s32)p + 0x1A) - 0x200;
    }
    t = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t & 0x10) {
        v = ((t & 0xF) >> 1) + 9;
    } else {
        v = 0x10 - ((t & 0xF) >> 1);
    }
    D_801EB524.b[0] = v * 12;
    D_801EB525 = v * 12;
    D_801EB526 = v * 2;
}



extern void (*D_80195D50[])(void);

void func_801873FC(void *a0) {
    D_80195D50[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 func_8014BF6C(void);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);

void func_80187438(s32 a0) {
    s32 s1;
    u8 n;

    s1 = a0;
    n = func_8014BF6C();
    while (n != 0) {
        func_8012C658(0x112, n - 1, s1);
        n--;
    }
    func_8012AD50((void *)s1);
}


void func_801874A0(void) {
}


extern void (*D_80195D58[])(void);

void func_801874A8(void *a0) {
    D_80195D58[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80187654(u8 *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_801DF580;
extern s32 D_81195D48;

void func_801874E4(s32 a0)
{
    s32 s1 = a0;
    s32 s0;

    if ((*(s32 *)(s1 + 0x20) = s0 = ((s32 (*)(void))func_8012C1B8)()) == 0) goto L_end;
    func_8001C214(s0, (s32)&D_801DF580);
    *(s32 *)(s0 + 0x20) = (s32)&D_81195D48;
    func_80187654((u8 *)s1);
    func_8012AD50((void *)s1);
L_end:
    return;
}


#include "common.h"

/* Packed struct to trigger lwl/lwr unaligned block copy */
typedef struct {
    u32 field0;
    u32 field1;
} __attribute__((packed, aligned(1))) BlockData;

extern u8 func_8014BF6C(void);
extern void func_8012B23C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern void func_80187654(u8*);
extern void func_80187724();
extern u16 D_800B99DA;
extern BlockData D_801E9E34;

void func_8018754C(s32 *a0)
{
    u8 result;
    BlockData buffer;

    /* Struct assignment emits lwl/lwr + swl/swr for unaligned copy */
    buffer = D_801E9E34;

    result = func_8014BF6C();

    if (!(*(s16*)((u8*)a0 + 0x70) < (result & 0xFF))) {
        func_8012B23C((s32)a0);
        func_8002D4C8(0x580, 0);
        func_8012BF4C(a0, 0x10);
        func_8012AD50((void*)a0);
    } else {
        ((void (*)(s32))func_80187654)((s32)a0);
        if ((D_800B99DA & 0x3) == 0) {
            func_80187724((s32)a0, &buffer);
        }
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void);
void func_80187614(s32 a0) {
    func_8012AD80(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C098)(a0);
    }
}


#include "common.h"

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_80187654;
typedef struct { s16 a, b, c; } SV3_80187654;

extern s32 *D_80126B78;
extern s32 D_80195DB0[];

extern u8 func_8014BF6C(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012B260(u8 *a0);

void func_80187654(u8 *param_1)
{
    u8 *obj;
    u8 idx;
    s16 off;
    SV3_80187654 out;

    obj = *(u8 **)(param_1 + 0x20);

    *(Mtx32_80187654 *)(obj + 0x34) = *(Mtx32_80187654 *)((u8 *)D_80126B78 + 0x34);

    idx = func_8014BF6C();
    off = *(s16 *)(param_1 + 0x70);

    func_8012F214((s32)param_1, D_80195DB0[idx] + off * 8, (s32)&out);

    *(s16 *)(param_1 + 0x6) = out.a;
    *(s16 *)(param_1 + 0xa) = out.b;
    *(s16 *)(param_1 + 0xe) = out.c;

    func_8012B260(param_1);
}




void func_80187724(u8 *a0, u8 *a1) {
    u16 temp[3];

    temp[0] = *(u16 *)(a0 + 0x6);
    temp[1] = *(u16 *)(a0 + 0xA);
    temp[2] = *(u16 *)(a0 + 0xE);

    temp[0] += *(u16 *)(a1 + 0x0);
    temp[1] += *(u16 *)(a1 + 0x2);
    temp[2] += *(u16 *)(a1 + 0x4);
}



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


extern s32 func_800D0CE0(void);
extern void func_8012C098(void);
void func_80187800(int param_1)
{
    if (((int (*)(void))func_800D0CE0)() != 0) {
        ((void (*)(int))func_8012C098)(param_1);
    }
}


extern s32 func_8012E544(s32);
extern void func_800D0C48(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);

void func_80187838(void) {
    s32 *s0;
    s0 = (s32 *)func_8012E544(0x11f);
    if (s0 != 0) {
        func_800D0C48(1);
        func_8012AD44(s0, 1);
        func_8012BF4C(s0, 0x30);
    }
}



extern void (*D_80195F14[])(void);

void func_8018788C(void *a0) {
    D_80195F14[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 D_80195EFC[];
extern s32 rand(void);

void func_801878C8(s32 a0) {
    s32 idx;
    s32 *entry;

    idx = *(s32 *)(a0 + 0x2C);
    entry = &D_80195EFC[idx * 3];

    if (*(u16 *)((s32)entry + 0x6) != 0) {
        *(s32 *)(a0 + 0x1C) = rand() % *(u16 *)((s32)entry + 0x6);
    } else {
        *(s32 *)(a0 + 0x1C) = 0;
    }

    *(u16 *)(a0 + 0x2) += 1;
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

extern u8 D_80195DD0[];
extern s32 D_80195EFC[];


void func_8018797C(s32 a0) {
    s32 effect;
    s32 count;
    s32 idx;
    s32 *entry;
    Quad_8018797C tmp;
    s32 off[3];
    u16 reload;

    effect = *(s32 *)(a0 + 0x20);
    count = *(s32 *)(a0 + 0x1c) - 1;
    *(s32 *)(a0 + 0x1c) = count;
    if (count == -1) {
        func_8001CC3C(effect, (s32)D_80195DD0, 0, 0);
        *(u8 *)(effect + 0x27) = 0x9c;
        *(u16 *)(effect + 0x1a) = 0x4000;
        *(u16 *)(effect + 0x18) = 0x4000;
        *(u32 *)(effect + 4) = *(u32 *)(effect + 4) | 0x50000040;

        idx = *(s32 *)(a0 + 0x2c);
        entry = &D_80195EFC[idx * 3];
        func_80128EA8(effect, a0 + 0x24, entry[0]);

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C *)(entry[2] + 0x10);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x10) = *(s32 *)(entry[2] + 0) + off[0];
        *(s32 *)(a0 + 0x14) = *(s32 *)(entry[2] + 4) + off[1];
        *(s32 *)(a0 + 0x18) = *(s32 *)(entry[2] + 8) + off[2];

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C *)(entry[2] + 0x30);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x2c) = *(s32 *)(entry[2] + 0x20) + off[0];
        *(s32 *)(a0 + 0x30) = *(s32 *)(entry[2] + 0x24) + off[1];
        *(s32 *)(a0 + 0x34) = *(s32 *)(entry[2] + 0x28) + off[2];

        reload = *(u16 *)((s32)entry + 4);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        *(u32 *)(a0 + 0x1c) = reload;
    }
}


#include "common.h"

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012931C(struct vec*);
extern void func_801292C8(u8 *a0);

void func_80187CE8(s32 arg0)
{
    register s32 s1 __asm__("$17") = arg0;
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    register s32 a2 __asm__("$6");
    register s32 zr __asm__("$0");

    /* Load velocity components */
    v0 = *(s32 *)(s1 + 0x10);
    v1 = *(s32 *)(s1 + 0x2C);
    a1 = *(s32 *)(s1 + 0x30);
    a2 = *(s32 *)(s1 + 0x34);

    /* Load s0 pointer from offset 0x20 */
    s0 = *(s32 *)(s1 + 0x20);

    /* Add velocity to position at 0x10 */
    v0 = v0 + v1;
    *(s32 *)(s1 + 0x10) = v0;

    /* Load and add velocity to positions at 0x14 and 0x18 */
    v0 = *(s32 *)(s1 + 0x14);
    v1 = *(s32 *)(s1 + 0x18);
    v0 = v0 + a1;
    v1 = v1 + a2;
    *(s32 *)(s1 + 0x14) = v0;
    *(s32 *)(s1 + 0x18) = v1;

    /* Call update function */
    ((void (*)(void))func_8012931C)();

    /* Opaque copy s0 -> a0: RC-12 $0-add so cse cannot fold the later
       lhu (which the target keeps reading from $s0) onto this copy. */
    a0 = s0 + zr;

    /* Update value at offset 0x1A (target reads this via $s0, not $a0) */
    v0 = *(u16 *)(s0 + 0x1A);
    v0 = v0 - 0x100;
    *(u16 *)(a0 + 0x1A) = (u16)v0;
    *(u16 *)(a0 + 0x18) = (u16)v0;

    /* Call func_80128ED8 and branch on result */
    if (func_80128ED8(a0, (s32 *)(s1 + 0x24)) != 0) {
        func_801292C8((u8 *)s1);
    } else {
        v0 = *(s32 *)(s1 + 0x1C);
        if (v0 != 0) {
            v0--;
            *(s32 *)(s1 + 0x1C) = v0;
            if (v0 == 0) {
                func_801292C8((u8 *)s1);
            }
        }
    }
}



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

#include "common.h"

extern u8 *func_801290DC(s32 a0, u8 *a1);

void func_80187FA0(u8 *a0, u8 *a1) {
    u16 temp[3];
    u16 v1_load;
    u8 *result;

    v1_load = *(u16 *)(a0 + 0x6);
    temp[0] = v1_load;

    temp[1] = *(u16 *)(a0 + 0xA);
    temp[2] = *(u16 *)(a0 + 0xE);

    temp[0] += *(u16 *)(a1 + 0x0);
    temp[1] += *(u16 *)(a1 + 0x2);
    temp[2] += *(u16 *)(a1 + 0x4);

    result = func_801290DC(0x3E, (u8 *)temp);

    if (result) {
        *(s32 *)(result + 0x2C) = *(s16 *)(a1 + 0x6);
    }
}


#include "common.h"

extern u8 D_80195FC8[];
extern s32 D_80126B58;
extern u16 D_80126B62;
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013294(void *a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80188034(s32 a0) {
    s32 idx;
    u8 *s0;
    s32 base;
    s16 buf[2];
    s16 sVar1;
    register s32 iVar3 __asm__("$2");
    s32 a1v;

    idx = *(s16 *)(a0 + 0xFC);
    s0 = D_80195FC8 + idx * 8;
    base = (s32)&D_80126B58;

    if (*(s16 *)(s0 + 6) != 0 && (s16)D_80126B62 >= -0x8FF) {
        func_80015978(base + 4, (s32 *)buf);
        buf[1] = *(u16 *)(s0 + 2);
        sVar1 = (s16)func_80013294((void *)buf, (void *)s0);
        if (sVar1 < 0x800) {
            iVar3 = (0x800 - sVar1) * 0x7F;
            if (iVar3 < 0) {
                iVar3 += 0x7FF;
            }
            iVar3 = iVar3 >> 11;
            a1v = iVar3;
            if (iVar3 < 0) {
                a1v = 0;
            }
            if ((s16)a1v >= 0x80) {
                a1v = 0x7F;
            }
            func_8002D4C8(*(u16 *)(s0 + 6), (a1v | 0x1000) & 0xffff);
        }
    }
}


#include "common.h"

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEF98;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80188114(void)
{
    int *p = &D_800C7C60;
    *p = 0x20;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEF98, 0, p);
}


extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEFA8;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80188168(void)
{
    int *p = &D_800C7C60;
    *p = 0x18;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEFA8, 0, p);
}



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


#include "common.h"

/* func_80188250 -- same-class neighbour push-away over the 0x60-entry /
 * 0x10C-stride entity table D_801202A0. Banked twin: ov_SC06_018:func_80187320
 * (§193-A), minus its second switch case (no 0x2F4 clamp here) and with a
 * self-id equality guard instead of constant class ids.
 *
 * §37/§124 DEF-SIDE ESCAPE (_body spelling, cf. func_801810CC_body,
 * ov_SC07_007_jr_8017BEBC.c:6600): this TU already declares
 * `extern void func_80188250(s32 a0);` at file scope (the func_80188654 block),
 * while the target tail (`addiu $v0,$zero,1` / `addu $v0,$zero,$zero`) proves
 * an s32 return. A same-name s32 definition is a hard `conflicting types`;
 * a void definition cannot emit the $v0 constants. Define under a private C
 * identifier carrying an __asm__ label: emitted symbol unchanged, no collision,
 * the existing extern keeps compiling the caller at func_80188654.
 *
 * §8d: func_8012CEB0 is declared ONLY at block scope in this TU (the
 * func_80187844 block) -- its extern rides INSIDE the body, not at file scope.
 *
 * Load-bearing constructs (do NOT "clean up"):
 *  1. NO SECOND WALKED POINTER. All of +0x6/+0xA/+0xE written off the single
 *     biv `p` (twin note 1): an explicit q = p + 0xE excludes the bare *q from
 *     givs and yields THREE IVs / wrong anchor.
 *  2. `self4` and `sc` are REAL pre-loop locals, in that order (twin note 4):
 *     written inline at the calls they fold into the argument moves and the
 *     $s5/$s6 hoists never happen. Declaration ORDER (p, i, self4, sc) gives
 *     $s2/$s4/$s5/$s6 in the target's prologue emission order.
 *  3. do-while with `i++` BEFORE `p += 0x10C` (twin note 3): strength_reduce
 *     emits the giv addiu immediately before ITS biv increment =>
 *     addiu $s4,1 / addiu $s3,0x10C / (delay) addiu $s0,0x10C.
 *  4. NO `s16 y` scalar: the twin's short-local/dead-slot pair belongs to its
 *     second switch case, absent here. Frame is exactly 0x48 with no dead slot.
 *  5. §5a cross-jump barrier before the second `return 1`: the target keeps TWO
 *     [j .epi][addiu $v0,$zero,1] tails; without the barrier gcc merges them
 *     into one shared li (93 ins).
 */

extern u8   D_801202A0[];

extern s32  func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012ADE4(u8 *a0);

s32 func_80188250_body(s32 a0) __asm__("func_80188250");

s32 func_80188250_body(s32 a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    u8 *p;
    s16 *self4;
    unsigned int *sc;
    s32 i;
    s32 ang;
    s16 v10[4];  /* sp+0x10 */
    s16 v18[4];  /* sp+0x18 */
    s32 sp20[2]; /* sp+0x20 - func_8012B0B4 output */

    p = D_801202A0;
    i = 0;
    self4 = (s16 *)(a0 + 4);
    sc = (unsigned int *)sp20;
    do {
        if (*(u16 *)a0 == *(u16 *)p && (u8 *)a0 != p) {
            if (func_8012BC60(self4, (struct Vec *)(p + 4)) < 0x1000) {
                ang = func_8012B6D4(self4, (s16 *)(p + 4));
                func_8012B0B4(sc, ang, 0x41);
                v18[0] = *(u16 *)(p + 6);
                v18[1] = *(u16 *)(p + 0xA);
                v18[2] = *(u16 *)(p + 0xE);
                v18[0] += sp20[0];
                v18[2] += sp20[0] >> 16;
                v10[0] = *(u16 *)(a0 + 0x3A);
                v10[1] = *(u16 *)(a0 + 0x3E);
                v10[2] = *(u16 *)(a0 + 0x42);
                if ((func_8012CEB0((s32)&v10[0], (s32)&v18[0], 0) & 0x2000) == 0) {
                    func_8012ADE4((u8 *)a0);
                    return 1;
                }
                *(u16 *)(a0 + 6) = v18[0];
                *(u16 *)(a0 + 0xA) = v18[1];
                *(u16 *)(a0 + 0xE) = v18[2];
                __asm__ __volatile__("" ::: "memory");   /* zero-byte cross-jump barrier (§5a) */
                return 1;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);
    return 0;
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_801883C8(void) {
        func_8002D4C8(0x6AA, 0);
    }


#include "common.h"

extern void func_8002A04C(void);
extern void func_8012C098(void);

void func_801883EC(s32 a0) {
    if (*(s16 *)(a0 + 0x102) == 0) {
        func_8002A04C();
    }

    ((void (*)(s32))func_8012C098)(a0);
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

void func_80188430(s32 a0) {
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern void func_8012B23C(s32 a0);
    extern void func_80188508(s32 a0);
    extern void func_80188554(s32 a0);

    SVECTOR in;
    SVECTOR out;
    s32 v0;

    in.vx = *(s16 *)(a0 + 0x6);
    in.vy = *(s16 *)(a0 + 0xA);
    in.vz = *(s16 *)(a0 + 0xE);
    out = in;
    out.vy += 8;

    if ((func_80133784(1, &in, (s32)&out) & 0x6000) != 0) {
        v0 = 1;
    } else {
        func_8012B23C(a0);
        v0 = 0;
    }

    if (v0 == 0) {
        *(s16 *)(a0 + 0x2) = 0x11;
        *(s16 *)(a0 + 0x98) = 0;
        return;
    }

    if (*(s32 *)(a0 + 0xC4) & 4) {
        func_80188508(a0);
    } else {
        func_80188554(a0);
    }
}


extern short D_801D40D4;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80188508(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s16 *)(a0 + 0x34) = 0;
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    func_8012A828(a0, &D_801D40D4);
    func_8012B23C(a0);
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s32 rand(void);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern u8 D_801D3CBC[];

void func_80188554(s32 param_1) {
    LVec1CDC d;

    *(s16 *)(param_1 + 0x2) = 1;
    *(s16 *)(param_1 + 0x34) = 0;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    *(s32 *)(param_1 + 0x1C) = (rand() & 0x1F) + 0x28;

    {
        void *target = (void *)(param_1 + 0x88);

        d.vx = *(s16 *)(param_1 + 0x6) - *(s16 *)target;
        d.vy = 0;
        d.vz = *(s16 *)(param_1 + 0xE) - *(s16 *)(param_1 + 0x8C);
        Square0(&d.vx, &d.vx);

        if (d.vx + d.vz > 0x8FFFF) {
            *(s16 *)(param_1 + 0xFC) =
                func_8012B744((void *)(param_1 + 0x4), target);
        } else {
            register s32 t __asm__("$2") = rand() & 0x3FF;
            s32 v1 = t - 0x200;

            if (v1 < 0) {
                v1 = t - 0x500;
            } else {
                v1 = t + 0x100;
            }
            *(s16 *)(param_1 + 0xFC) =
                (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v1) & 0xFFF;
        }
    }

    func_8012A828(param_1, D_801D3CBC);
}


#include "common.h"

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);            /* canonical void */
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void);
extern s32 func_8012C044(s32 a0);

extern void func_80188250(s32 a0);
extern void func_8018898C(s32 a0);
extern void func_801887C8(short *a0);

extern s32 D_80196098;

void func_80188654(s32 a0)
{
    s32 s0 = a0;
    s32 v0;
    s32 v1;

    if (*(s32 *)(s0 + 0x1C) >= 8) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), *(s16 *)(s0 + 0xFC), 8);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + r;
    }

    {
        s32 d[3];
        d[0] = *(s16 *)(s0 + 0x6) - *(s16 *)(s0 + 0x88);
        d[1] = 0;
        d[2] = *(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0x8C);
        Square0(d, d);
        if (d[0] + d[2] <= 0x8FFFF) {
            if (func_8012BD3C(s0, 0x300, 0x10000)) {
                func_8018898C(s0);
                return;
            }
        }
    }

    func_8012B178(s0, D_80196098);
    v1 = ((s32 (*)(s32))func_8012CBA4)(s0);
    if (v1 & 0x1000) {
        func_80131E00((struct S80131E00 *)s0, 0x12);
        v0 = 0;
    } else if (v1 == 0x2000) {
        v0 = 1;
    } else {
        func_8012ADE4((u8 *)s0);
        v0 = 1;
    }

    if (v0 == 0) {
        return;
    }

    func_80188250(s0);
    if (func_8012BEE8(s0) != 0) {
        func_801887C8((short *)s0);
        return;
    }

    if (func_8012C044(s0) != 0) {
        *(s16 *)(s0 + 0x102) = 1;
        ((void (*)(void *))func_8012C098)((void *)s0);
    }
}




extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801887C8(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D3B74);
    }


#include "common.h"

extern s32 rand(void);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern u8 D_801D3CBC[];

typedef struct {
    s32 vx, vy, vz;
} Vec3_1887F8;

void func_801887F8(s32 a0) {
    Vec3_1887F8 d;
    Vec3_1887F8 *p;
    s32 v0;
    s32 v1;
    s32 r;
    s32 dx;
    s32 dz;
    register void *s1_ptr __asm__("$17");

    if ((*(u16 *)(a0 + 0x34) == 0) && ((*(u16 *)(a0 + 0x72) & 0x4000) != 0)) {
        d.vx = *(s16 *)(a0 + 0x6) - *(s16 *)(a0 + 0x88);
        d.vy = 0;
        d.vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
        Square0(&d.vx, &d.vx);

        if (d.vx + d.vz > 0x8FFFF) {
            v0 = 1;
        } else if (func_8012BCCC(a0) > 0x10000) {
            v0 = 1;
        } else {
            func_8018898C(a0);
            return;
        }

        *(s16 *)(a0 + 0x2) = v0;
        *(s16 *)(a0 + 0x34) = 0;
        *(u16 *)(a0 + 0x5C) = 0xAA10;
        r = rand();
        p = &d;
        r = r & 0x1F;
        dx = *(s16 *)(a0 + 0x6);
        dz = *(s16 *)(a0 + 0x88);
        *(s32 *)(a0 + 0x1C) = r + 0x28;

        p->vy = 0;
        p->vx = dx - dz;
        p->vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
        Square0(&p->vx, &p->vx);

        s1_ptr = (void *)(a0 + 0x88);
        if (d.vx + d.vz > 0x8FFFF) {
            *(s16 *)(a0 + 0xFC) = func_8012B744((void *)(a0 + 4), s1_ptr);
        } else {
            v0 = rand() & 0x3FF;
            v1 = v0 - 0x200;
            if (v1 >= 0) {
                v1 = v0 + 0x100;
            } else {
                v1 = v0 - 0x500;
            }
            v0 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            *(s16 *)(a0 + 0xFC) = (v0 + v1) & 0xFFF;
        }

        func_8012A828(a0, (void *)&(*(short *)D_801D3CBC));
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);

extern s16 D_801D3D64;
extern s16 D_801D3DEC;

void func_8018898C(s32 a0) {
    *(s16 *)(a0 + 0x2) = 3;
    if (*(u16 *)(a0 + 0x86) & 2) {
        *(s16 *)(a0 + 0x34) = 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
        func_8012A828(a0, &D_801D3D64);
        *(u16 *)(a0 + 0xFE) = 0;
    } else {
        *(s16 *)(a0 + 0x34) = 0;
        func_8012A828(a0, &D_801D3DEC);
        *(s32 *)(a0 + 0x1C) = 0x19;
        *(u16 *)(a0 + 0x86) |= 2;
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188A10);

extern const void D_801D3EBC;
extern void func_80188DF4(s32 arg0, s32 arg1, s32 arg2, void *arg3);

void func_80188D54(arg0)
s32 arg0;
{
    extern const void D_801D3EBC;
    func_80188DF4(arg0, 0, 0x14, (void *)&D_801D3EBC);
}


extern void func_80188DC8(void*);
extern void func_80188DF4();
extern short D_801D4494;

void func_80188D80(s32 a0) {
    s32 a1 = 4;
    if (*(s16 *)((s32)a0 + 0x100) == 0) {
        ((void (*)(s32))func_80188DC8)(a0);
    } else {
        ((void (*)(s32, s32, s32, s32))func_80188DF4)(a0, a1, 0x1E, (s32)&D_801D4494);
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80188DC8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


extern void func_8012A828(s32 a0, void *a1);

void func_80188DF4(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    *(short *)((char *)arg0 + 0x34) = arg1;
    *(short *)((char *)arg0 + 0x2) = 4;
    func_8012A828(arg0, arg3);
    *(s32 *)((char *)arg0 + 0x1C) = arg2;
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_80188E3C);

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 D_801960B4[];

void func_80189050(s32 param_1) {
    register s32 s0 __asm__("$16") = param_1;
    s32 *s1;

    __asm__ __volatile__("" : "=r"(s0) : "0"(s0));

    if ((*(u16 *)(s0 + 0x70) & 0x2000) == 0) {
        s1 = &D_801960B4[3];
    } else {
        s1 = &D_801960B4[0];
    }
    *(s16 *)(s0 + 2) = 7;
    func_8012A828(s0, (void *)s1[0]);
    func_8012B200((u8 *)s0);
    func_8012B178(s0, s1[1]);
    *(s32 *)(s0 + 0x1C) = s1[2];
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s16 D_801960CC;
extern s16 D_801960CE;
extern s16 D_801960D0;

extern s32 func_8018F488(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801890C8(s32 a0) {
    struct S8012C658 sp;
    s32 vec[3];
    s32 out[3];
    s16 *p = &D_801960CC;

    func_8018F488(a0, (s32)p);

    vec[0] = *p << 8;
    vec[1] = D_801960CE << 8;
    vec[2] = D_801960D0 << 8;

    func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)vec, (s32)out);

    out[0] += *(s16 *)(a0 + 0x6) << 8;
    out[1] += *(s16 *)(a0 + 0xA) << 8;
    out[2] += *(s16 *)(a0 + 0xE) << 8;

    sp.unk0 = out[0] / 256;
    sp.unk2 = out[1] / 256;
    sp.unk4 = out[2] / 256;
    sp.unk6 = 0x20;
    sp.unk8 = 1;
    sp.unkA = 0;
    sp.unk10 = 0;
    sp.unkE = 0;

    func_8012C51C(&sp, a0);
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h where the
 * real TU's SV3 {short a,b,c} lives (via ../shared/engine_core.h); function-local name. */
typedef struct { s16 a, b, c; } SV3_801891E8;

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s16 D_801D3D64;
extern s16 D_801D3DEC;

extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

void func_801891E8(s32 param_1) {
    SV3_801891E8 pt;
    s32 v[4];

    if (*(u16 *)(param_1 + 0x34) == 0) {
        pt.a = D_80126B5E;
        pt.c = D_80126B66;
        v[0] = *(s16 *)(param_1 + 0x6) - pt.a;
        v[1] = 0;
        v[2] = *(s16 *)(param_1 + 0xE) - pt.c;
        Square0(&v[0], &v[0]);
        if (v[0] + v[2] <= 0x19000) {
            *(s16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
        }
    } else if ((func_8012CBCC(param_1) & 0x2000) != 0) {
        *(s16 *)(param_1 + 0x2) = 3;
        if ((*(u16 *)(param_1 + 0x86) & 2) != 0) {
            *(s16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x28;
            func_8012A828(param_1, &D_801D3D64);
            *(s16 *)(param_1 + 0xFE) = 0;
        } else {
            *(s16 *)(param_1 + 0x34) = 0;
            func_8012A828(param_1, &D_801D3DEC);
            *(s32 *)(param_1 + 0x1C) = 0x19;
            *(u16 *)(param_1 + 0x86) |= 2;
        }
    }
}


/* func_80189324 (ov_SC02_011) -- MATCH, 111/111 ins, match_one standalone.
 *
 * Second-pass fix of the first agent's 9-ins residual (schedule-loadhoist-regchoice).
 * The whole residual was gcc-2.7.2 sched1's LUID tie-break (sched.md S1): every insn in
 * the post-rand() block ties at INSN_PRIORITY 1 except the load-fed subu/sw pairs (pri 2),
 * so the emitted order inside the pri-1 group is exactly ASCENDING LUID = RTL expansion
 * order. Reading the target's block back as statement order gives the required LUID chain
 *     &d  <  (r & 0x1F)  <  lh 0x6  <  lh 0x88  <  (+0x28 / sw 0x1C)  <  d.vy = 0
 * i.e. the frame-address `p = &d` must expand FIRST after the call (that is what puts
 * `addiu $a0,$sp,0x10` at the block top instead of letting it fall into the load->subu
 * wedge), the mask must be split off from the +0x28 add, and both distance loads must be
 * their own statements ahead of the 0x1C store. No pins were needed for the hoist; the
 * $17 pin below is the first agent's (still load-bearing for the func_8012B744 arg).
 *
 * TU check (src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c): no existing decl of func_80189324
 * (INCLUDE_ASM only, L7901), so the definition signature is free. All callee decls copied
 * verbatim from the TU -- func_8012B030 L2607, func_8012B744 L2608, func_8012C354 L3721,
 * func_8012A828 L3723, func_80143970 L4283, rand L949, D_801D3B74 L7864. Square0 uses the
 * canonical engine_core.h form. D_80195FF0 / D_80196058 / (*(short *)D_801D3CBC) are absent from the
 * TU -- typed by access width (address-only lui/addiu).
 */
#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern s32 rand(void);

extern u8 D_80195FF0[];
extern void (*D_80196058[])(void);
extern short D_801D3B74;
extern u8 D_801D3CBC[];

typedef struct {
    s32 vx, vy, vz;
} Vec3_189324;

void func_80189324(s32 a0) {
    s32 idx;
    s32 v0;
    s32 sum;
    Vec3_189324 d;
    s32 r;
    Vec3_189324 *p;
    s32 dx, dz;
    s32 x;
    s32 v1;
    register void *s1_ptr __asm__("$17");

    idx = (*(u16 *)(a0 + 0x70) & 0xF00) >> 8;

    if (func_8012C354(a0, (s32)(D_80195FF0 + idx * 0x34)) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -1;
    *(u8 *)(a0 + 0xC1) = 0;
    *(s32 *)(a0 + 0xBC) = (s32)D_80196058;
    func_80143970(a0);
    func_8012B030((u8 *)a0);

    if ((*(u16 *)(a0 + 0x70) & 0x6000) != 0) {
        *(s16 *)(a0 + 0x2) = 6;
        func_8012A828(a0, (void *)&D_801D3B74);
        return;
    }

    if ((*(u16 *)(a0 + 0x70) & 0x1) != 0) {
        *(s16 *)(a0 + 0x2) = 0xF;
        return;
    }

    if ((*(u16 *)(a0 + 0x70) & 0x100) != 0) {
        *(s16 *)(a0 + 0x2) = 9;
        return;
    }

    *(s16 *)(a0 + 0x2) = 1;
    *(s16 *)(a0 + 0x34) = 0;
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    r = rand();
    p = &d;
    r = r & 0x1F;
    dx = *(s16 *)(a0 + 0x6);
    dz = *(s16 *)(a0 + 0x88);
    *(s32 *)(a0 + 0x1C) = r + 0x28;

    p->vy = 0;
    p->vx = dx - dz;
    p->vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&p->vx, &p->vx);

    sum = d.vx + d.vz;
    s1_ptr = (void *)(a0 + 0x88);
    if (sum > 0x8FFFF) {
        *(s16 *)(a0 + 0xFC) = (s16)func_8012B744((void *)(a0 + 4), s1_ptr);
    } else {
        x = rand() & 0x3FF;
        v1 = x - 0x200;
        if (v1 >= 0) {
            v1 = x + 0x100;
        } else {
            v1 = x - 0x500;
        }
        v0 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        v0 = (v0 + v1) & 0xFFF;
        *(s16 *)(a0 + 0xFC) = v0;
    }

    func_8012A828(a0, (void *)&(*(short *)D_801D3CBC));
}



extern void (*D_801960D4[])(void);

void func_801894E0(void *a0) {
    D_801960D4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80188DF4();
extern void func_8012A828(s32 a0, void *a1);

extern short D_801D3B74;
extern short D_801D4494;

void func_8018951C(s32 param_1) {
    register s32 s0 __asm__("$16");
    s32 v0;

    s0 = param_1;
    if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
        *(u16 *)(s0 + 0x100) = 3;
        if (func_8012BD3C(s0, 0x400, 0x40000) != 0) {
            func_80188DF4(s0, 4, 0x1E, &D_801D4494);
        } else {
            *(u16 *)(s0 + 0x2) = 2;
            *(u16 *)(s0 + 0x34) = 0;
            func_8012A828(s0, &D_801D3B74);
        }
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801895A0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D3B74);
    }


void func_801895CC(s32 a0) {
    s32 v0;
    if (*(s16 *)(a0 + 0x100) == 0) {
        v0 = 0xB;
    } else {
        if (func_8012BD3C(a0, 0x400, 0x40000) == 0) {
            return;
        }
        v0 = 0xD;
    }
    *(s16 *)(a0 + 0x2) = v0;
}



extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80189620(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 12;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


void func_8018964C(void *arg0) {
    if (*(u16 *)((s32)arg0 + 0x72) & 0x4000) {
        *(u16 *)((s32)arg0 + 0x2) = 9;
        *(u16 *)((s32)arg0 + 0x100) = 3;
    }
}


extern short D_801D4494;
extern void func_8012A828(s32 a0, void *a1);

void func_80189674(a0)
s32 a0;
{
    *(s16 *)(a0 + 0x2) = 14;
    func_8012A828(a0, &(*(u8 *)&D_801D4494));
    *(s32 *)(a0 + 0x1C) = 0x1e;
}


#include "common.h"

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801890C8(s32 a0);

void func_801896B4(s32 param_1)
{
    s32 v;
    unsigned short *p;
    unsigned short val;

    v = func_8012B8E4(param_1, 6);
    p = (unsigned short *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);

    if (*(s32 *)(param_1 + 0x1C) == 0xC) {
        func_801890C8(param_1);
    }

    if (func_8012BEE8(param_1) == 0) {
        return;
    }

    val = *(unsigned short *)(param_1 + 0x100);
    val--;
    *(unsigned short *)(param_1 + 0x100) = val;

    {
        s32 v0_shifted = (s32)val << 16;
        if (v0_shifted == 0) {
            *(unsigned short *)(param_1 + 0x2) = 0xB;
        } else {
            *(s32 *)(param_1 + 0x1C) = 0x1E;
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801D3ACC[];

void func_8018974C(s32 a0) {
    s32 s0 = a0;
    func_8012A828(a0, D_801D3ACC);
    *(u16 *)(s0 + 2) = 0x10;
    func_8012B23C(s0);
    *(s32 *)(*(s32 *)(s0 + 0x20) + 4) |= 0x80000000;
}


#include "common.h"

extern void func_8002A04C(void);
extern void func_8012CBF4(s32);
extern void func_8012C098(void);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80188554(s32 a0);

void func_801897A4(s32 a0) {
    s16 field_a;
    s16 field_102;
    s32 result;

    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x10) {
        field_102 = *(s16 *)(a0 + 0x102);
        if (field_102 == 0) {
            ((void (*)(s32))func_8002A04C)(a0);
        }
        ((void (*)(s32))func_8012C098)(a0);
    } else {
        result = ((s32 (*)(s32))func_8012CBF4)(a0);
        if ((result & 0x2000) != 0) {
            if ((result & 0x1000) != 0) {
                func_80131E00((struct S80131E00 *)a0, 0x12);
            } else {
                func_80188554(a0);
            }
        }
    }
}


extern void func_8012CBF4(s32);
extern void func_80188554(s32 a0);

void func_8018983C(s32 a0) {
    s32 s0;

    s0 = a0;
    ((void (*)(s32))func_8012CBF4)(a0);
    if (*(u16 *)(s0 + 0x72) & 0x4000) {
        func_80188554(s0);
    }
}


extern s32 func_8012BCCC(s32 a0);
extern void func_80189050(s32 a0);
extern s32 D_801960B0;

void func_80189880(void *a0) {
    s32 s0 = (s32)a0;
    if (func_8012BCCC(s0) < D_801960B0) {
        func_80189050(s0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern s16 D_801D3D64;
extern s16 D_801D3DEC;

void func_801898C8(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    if (*(u16 *)(a0 + 0x70) & 0x2000) {
        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s16)v0 <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }
    }
    if (func_8012BEE8(a0)) {
        *(u16 *)(a0 + 0x86) |= 2;
        *(s16 *)(a0 + 0x2) = 3;
        if (*(u16 *)(a0 + 0x86) & 2) {
            *(s16 *)(a0 + 0x34) = 1;
            *(s32 *)(a0 + 0x1C) = 0x28;
            func_8012A828(a0, &D_801D3D64);
            *(u16 *)(a0 + 0xFE) = 0;
        } else {
            *(s16 *)(a0 + 0x34) = 0;
            func_8012A828(a0, &D_801D3DEC);
            *(s32 *)(a0 + 0x1C) = 0x19;
            *(u16 *)(a0 + 0x86) |= 2;
        }
    }
}


#include "common.h"

extern void func_80189A50(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801EB9F4;
extern s32 D_801EB9F8;

void func_801899B4(void) {
    s32 v0;
    s32 v1;

    func_8013CB84();
    func_80189A50();

    v1 = D_801EB9F8;

    if (v1 == 1) goto L_handle_v0_1;

    if (v1 >= 2) {
        return;
    }

    if (v1 != 0) {
        return;
    }

    // v1 == 0
    func_8002D4C8(0x5E4, 0);
    v0 = D_801EB9F8;
    v0++;
    D_801EB9F8 = v0;
    return;

L_handle_v0_1:
    v0 = D_801EB9F4;
    v0++;
    D_801EB9F4 = v0;

    if (v0 < 0x97) {
        return;
    }

    func_8002D4C8(0xD, 0x5E4);
    v0 = D_801EB9F8;
    v0++;
    D_801EB9F8 = v0;
}


#include "common.h"

extern u16 D_8019611C[];
extern u16 D_8019615C[];
extern u16 D_801EB56C[];
extern u16 D_801EB5AC[];
extern s32 D_801EB568;
extern u8  D_8019617C[];
extern void func_800183E0(s32 a0);

void func_80189A50(void) {
    u32 i;
    u32 t;

    t = (u32)D_801EB568 >> 8;
    for (i = 0; i < 0x20; i++) {
        D_801EB56C[i] = D_8019611C[(t + i) & 0x1F] | 0x8000;
    }

    t = (u32)D_801EB568 >> 8;
    for (i = 0; i < 0x10; i++) {
        D_801EB5AC[i] = D_8019615C[(t + i) & 0xF] | 0x8000;
    }

    func_800183E0((s32)D_8019617C);

    D_801EB568 += 0x100;
}



extern void (*D_801961D4[])(void);

void func_80189B28(void *a0) {
    D_801961D4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029178(s32 arg);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32 a0, void *a1);

void func_80189B64(s32 a0) {
    extern u8 D_801D4E54;
    extern u8 D_8019105C[];
    extern s16 D_801961AC;
    s32 h;
    if ((func_80029178(0x9F) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    *(s16 *)(a0 + 0x5C) = 0x800;
    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = h;
    if (h == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(h, (s32)&D_801D4E54);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x140, 0xF0);
    *(s32 *)(a0 + 0x58) = (s32)&D_801961AC | 0x10000000 | 0x40000000;
    *(u8 *)(a0 + 0x75) = 1;
    *(u16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0x1C) = 0x1F;
    func_8012A828(a0, (void *)D_8019105C);
}


void func_80189C20(s32 arg0) {
    if (func_8012E778(arg0, 0x8200AA) != 1) {
        return;
    }
    if ((func_8014CB2C() & 0x7FFFFFFF) != 2) {
        return;
    }
    *(u16 *)((s32)arg0 + 0x2) = 2;
    *(u16 *)((s32)arg0 + 0xFC) = 1;
    *(s32 *)((s32)arg0 + 0x1C) = 0x3C;
}


void func_80189C90(s32 s0)
{
    s32 a0;
    s32 v1;
    s32 v0;
    s32 s1;
    s32 s2;

    s1 = *(s32 *)(s0 + 0x20);
    s2 = s1 + 0x10;
    if (rand() & 1) {
        v1 = rand();
        a0 = *(s16 *)(s0 + 0xFC);
        *(s16 *)(s1 + 0x10) = *(u16 *)(s1 + 0x10) + a0 * (v1 % 8 + 1);
    }
    v1 = *(s16 *)s2;
    if (v1 >= 0x39) {
        *(s16 *)(s0 + 0xFC) = -1;
        *(s16 *)s2 = 0x38;
        *(u16 *)(s0 + 0x100) += 1;
        func_8018A084(s0);
        func_80189F30(s0);
        *(s16 *)(s0 + 0xFE) = 5;
        func_8002D4C8(0x661, 0);
    } else {
        if (v1 < 0) {
            *(s16 *)(s0 + 0xFC) = 1;
            *(s16 *)s2 = 0;
        }
    }
    if (*(s16 *)(s0 + 0xFE) != 0) {
        func_80189F30(s0);
        *(u16 *)(s0 + 0xFE) -= 1;
    }
    if (*(s16 *)(s0 + 0x100) >= 2) {
        func_8012B2CC(s0);
        func_8012B200((u8 *)s0);
        func_8012B178(s0, 0xFFFE0000);
        *(s16 *)(s0 + 2) = 3;
        *(s32 *)(s0 + 0x1C) = 10;
        *(s32 *)(s0 + 0xDC) = 0x1F;
        func_8002D4C8(0x61D, 0);
    }
}


void func_80189E00(s32 a0) {
    extern u8 D_801961BC[];
    register s32 s0 __asm__("$16") = a0;
    s32 v0, v1;

    v0 = *(s32 *)(s0 + 0xDC);
    if (v0 != 0) {
        v0 = v0 - 1;
        *(s32 *)(s0 + 0xDC) = v0;
        func_800D0C48(1);
    }

    if (*(u16 *)(s0 + 0x34) == 0) {
        v1 = *(s32 *)(s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x10) + 0x20;
        *(u16 *)(v1 + 0x10) = v0;
        func_8012B178(s0, 0xFFFE0000);
        func_8012AD80(s0);
        v1 = *(s32 *)(s0 + 0x20);
        v0 = *(s16 *)(v1 + 0x10);
        if (v0 < 0x400) goto end;
        *(s16 *)(v1 + 0x10) = 0x400;
        v0 = *(u16 *)(s0 + 0x34) + 1;
        *(u16 *)(s0 + 0x34) = v0;
        func_8012B23C(s0);
    } else {
        v0 = func_8012CBCC(s0);
        if ((v0 & 0x2000) != 0) {
            func_8013C9C4((void *)&D_801961BC);
            func_80029124(0x9F, 1);
            func_8002D4C8(0x61C, 0);
            *(s16 *)(s0 + 2) = 4;
        }
    }
end:
    return;
}


extern s32 func_800D0CE0(void);
    extern void func_8012C218(void *a0);
    void func_80189EF4(void *a0) {
        if (((s32 (*)(s32))func_800D0CE0)((s32)a0) == 1) {
            ((void (*)(s32))func_8012C218)((s32)a0);
        }
    }


extern u16 D_801961CE;
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_80143BDC(u16 *a0);
extern s32 rand(void);

#define SRM_80189F30(r0) __asm__ volatile (          \
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
#define STM_80189F30(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_80189F30(void *param_1) {
    s16 v[8];
    register s32 i __asm__("$17");
    s32 r;
    s32 t;
    s32 flag;
    s32 *m;

    v[1] = D_801961CE;
    m = (s32 *)(*(s32 *)((s32)param_1 + 0x20) + 0x34);
    SRM_80189F30(m);
    STM_80189F30(m);
    for (i = 0; i < 10; i++) {
        r = rand() % 144;
        if (rand() & 1) {
            t = r;
        } else {
            t = -r;
        }
        v[0] = t;
        r = rand() % 48;
        v[2] = ((rand() & 1) ? r : -r) - 48;
        RotTransSV(&v[0], &v[4], &flag);
        func_80143BDC((u16 *)&v[4]);
    }
}


#include "common.h"

extern u16 D_801961CE;
extern void func_8017C294(s32 a0, s16 *a1, s16 a2);

void func_8018A084(s32 a0) {
    s16 v[3];
    register s32 i __asm__("$17");
    s32 r;

    v[1] = D_801961CE;
    for (i = 0; i < 5; i++) {
        s32 t;

        r = rand() % 144;
        if (rand() & 1) {
            t = r;
        } else {
            t = -r;
        }
        v[0] = t;
        r = rand() % 48;
        v[2] = ((rand() & 1) ? r : -r) - 48;
        func_8017C294(a0, v, 1);
    }
}


extern s32 D_8012704C;

s32 func_8018A184(void) {
    if (D_8012704C == 0) {
        return 0x18;
    }
    return 0x2B;
}


#include "common.h"

extern void func_8012A418(void);
extern void func_8012A598(void);
extern void func_8012A018(s32, s32);

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_801269E4;

void func_8018A284(void *a0);

typedef struct { u16 a, b, c, d; } __attribute__((aligned(2))) DataBlock;

void func_8018A1A4(void *a0) {
    u8 *s1;
    u8 *s0;
    register u8 *a1 __asm__("$5");

    s1 = (u8 *)a0;
    s0 = *(u8 **)(s1 + 0xDC);

    func_8012A418();
    func_8012A598();

    D_80126954 = *(s32 *)(void *)s0;
    D_8012695C = *(s32 *)(void *)(s0 + 4);

    /* Load address of D_80126968 into a1 */
    a1 = (u8 *)&D_80126968;

    /* Direct struct assignment for 8-byte unaligned copy */
    *(DataBlock *)(void *)a1 = *(DataBlock *)(void *)(s0 + 8);

    D_80126976 = *(s16 *)(s0 + 0x10);
    D_80126978 = *(s16 *)(s0 + 0x12);
    D_8012697A = *(s16 *)(s0 + 0x14);

    ((void (*)(void *, s32))func_8012A018)((void *)func_8018A284, 0);

    D_801269E4 = *(s32 *)(void *)(s1 + 0xDC);
}


extern void func_8012A4BC(void);
    void func_8018A264(void) {
        ((s32 (*)(void))func_8012A4BC)();
    }



extern void (*D_801D6268[])(void);

void func_8018A284(void *a0) {
    D_801D6268[*(u8 *)((s32)a0 + 0x4)]();
}


extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern void func_8018A438(s32);

void func_8018A2C0(s32 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x9C);
    if ((*(u16 *)(iVar1 + 0x1E) & 1) != 0) {
        s16 *p = &D_80126940;
        if (*(s16 *)(iVar1 + 0x18) < *p) {
            *p = *(s16 *)(iVar1 + 0x18);
        }
    }
    if ((*(u16 *)(iVar1 + 0x1E) & 2) != 0) {
        s16 *p = &D_80126942;
        if (*(s16 *)(iVar1 + 0x1A) < *p) {
            *p = *(s16 *)(iVar1 + 0x1A);
        }
    }
    if ((*(u16 *)(iVar1 + 0x1E) & 4) != 0) {
        s16 *p = &D_80126944;
        if (*(s16 *)(iVar1 + 0x1C) < *p) {
            *p = *(s16 *)(iVar1 + 0x1C);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 1) != 0) {
        s16 *p = &D_80126940;
        if (*p < *(s16 *)(iVar1 + 0x20)) {
            *p = *(s16 *)(iVar1 + 0x20);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 2) != 0) {
        s16 *p = &D_80126942;
        if (*p < *(s16 *)(iVar1 + 0x22)) {
            *p = *(s16 *)(iVar1 + 0x22);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 4) != 0) {
        s16 *p = &D_80126944;
        if (*p < *(s16 *)(iVar1 + 0x24)) {
            *p = *(s16 *)(iVar1 + 0x24);
        }
    }
    func_8018A438(param_1);
}


#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"  /* match_one-only: gives MATRIX/SVECTOR; the real TU already includes this */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;

void func_8018A438(s32 param_1) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    s16 *p;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    p = &D_80126940;
    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)*p;
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)D_80126942;
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)D_80126944;
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + *p;
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + D_80126942;
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + D_80126944;
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}



extern void (*D_801D626C[])(void);

void func_8018A5E4(void *a0) {
    D_801D626C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_8018A620(void) {
        ((void (*)(void))func_8012AD50)();
    }


extern s32 D_80126B58;
extern s32 func_80172688(s32 *a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
void func_8018A1A4(void *a0);

void func_8018A640(s32 *a0) {
    if (func_80172688(&D_80126B58)) {
        func_8018A1A4(a0);
        func_8012BF4C(a0, 0x20);
        func_8012AD50(a0);
    }
}


extern s32 D_80126B58;
extern s32 func_80172688(s32 *a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A264(void);

void func_8018A698(s32 *a0) {
    if (func_80172688(&D_80126B58) == 0) {
        if (func_8012BEE8((s32)a0) != 0) {
            func_8018A264();
            (*(u16 *)((s32)a0 + 2))--;
        }
        return;
    }
    func_8012BF4C(a0, 0x20);
}


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



    extern s16 D_801EB6DE;
    extern s16 D_801EB6E0;
    extern s16 D_801EB6E2;
    void func_8018A7CC(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801EB6DC;
        D_801EB6DC = *(u16 *)((s32)arg0 + 0x0);
        D_801EB6DE = *(u16 *)((s32)arg0 + 0x2);
        D_801EB6E0 = arg1;
        D_801EB6E2 = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018A7FC(s32 a0) {

    extern u8 D_800AF648;
    extern s16 D_801EB6DC;
    extern s16 D_801EB6DE;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801EB6DC = sxy[0];
    D_801EB6DE = sxy[1];
}



extern s16 D_801EB6E2;
    void func_8018A874(s32 arg0) {
        *(s16 *)((s32)&D_801EB6E2 + 0x0) += arg0;
    }


extern s32 func_8018A9BC(void);
extern void func_8018A8E8();

void func_8018A890(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_8018A9BC();
    if (v0 >= 0) {
        func_8018A8E8(v0, (void *)a0, a1, a2);
    }
}



/* func_8018A8E8 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
 *
 * THREE in-TU collisions, all fixed without touching an emitted instruction
 * (src/ov_SC03_014/ov_SC03_014_jr_801848E4.c):
 *
 * (1) memcpy — cookbook §2959 / the sibling note at TU L3742.  The TU declares
 *     memcpy THREE times: L81 + L1518 with the builtin-compatible signature
 *     (void*, const void*, unsigned) and then L1524 as
 *     `extern void *memcpy(void *dst, void *src, s32 n);`.  L1524 disagrees with
 *     gcc's built-in, so duplicate_decls "throws away the built-in" (warning only,
 *     because the old decl was still DECL_BUILT_IN) and installs a PLAIN function
 *     decl.  Two consequences at the splice point (L3635):
 *       a. my own builtin-shaped redeclaration now conflicts with a plain decl —
 *          hard error ("conflicting types for `memcpy'", :3637 vs :1524);
 *       b. even if it compiled, the identifier `memcpy` is no longer a builtin
 *          here, so both copies would lower to `jal memcpy` — but the TARGET
 *          bytes are the INLINE block move (lwl 3 / lwr 0 / swl / swr, no jal).
 *     Fix = do not name memcpy at all: a 4-byte STRUCT ASSIGN through an
 *     ALIGN-1 struct (u8 x4).  That is exactly the sibling func_8018ADA8 lever
 *     in this same TU (TU L3736-3744, cookbook §48-C2): align 1 routes
 *     mips.c expand_block_move, which copy_addr_to_reg's the source into one
 *     held register -> the identical lwl/lwr + swl/swr pair, zero memcpy ref.
 *     The typedef is BLOCK-scoped so it cannot collide with the TU's own
 *     block-scoped `V4` at L3758.
 *
 * (2) func_8018A8E8 itself — the TU prototypes it at L3570 as
 *     `extern void func_8018A8E8(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_8018A8E8") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801EB6E4 / rand — declared VERBATIM as the TU already has them
 *     (D_801EB6E4: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_8018A8E8");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801EB6E4;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801EB6E4);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_8018A8E8 *)((u8 *)s1 + 6) = *(B4_8018A8E8 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_8018A8E8 *)((u8 *)s1 + 10) = *(B4_8018A8E8 *)a3;
    *(u8 *)((u8 *)s1 + 13) = 0;

    v0 = rand() & 0x3f;
    temp_u16 = *(u16 *)((u8 *)a1 + 2);
    *(u16 *)((u8 *)s1 + 2) = temp_u16 + v0 - 0x20;

    v0 = rand() & 0x7f0;
    temp_s16 = *(s16 *)((u8 *)a1 + 4);
    temp_s32 = temp_s16 * (v0 + 0xc00);
    v0 = (s32)(temp_s32 >> 12);
    *(s16 *)((u8 *)s1 + 4) = (s16)v0;

    v0 = *(s16 *)((u8 *)a1 + 6);
    if (v0 != 0) {
        u16 v1 = *(u16 *)((u8 *)s1 + 4);
        *(u8 *)((u8 *)s1 + 9) = 1;
        *(u16 *)((u8 *)s1 + 4) = 0;
        *(u8 *)((u8 *)s1 + 13) = (u8)v1;
    }
}




s32 func_8018A9BC(void) {

    extern s16 D_801EB6E4;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801EB6E4 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_8018A9F8(s32 a0, s32 a1) {

    extern s16 D_801EB6E4;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801EB6E4);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



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



/* func_8018AB20 — draws one entry of the 16-slot D_801EB6E4 particle table:
 * bump-allocates a 0x1C-byte GPU packet out of D_800A5E60, fills it from the
 * table entry, runs two RotMatrixZ/ApplyMatrixSV passes to place the two
 * endpoints, then link-ins the packet into the current double-buffer's OT
 * (the PSY-Q `addPrim` macro pair) and calls func_80016638.
 *
 * STATUS: byte-MATCH, 177/177 instructions (match_one standalone AND spliced
 * into the real TU — the in-TU compile adds ZERO new cc1 diagnostics over the
 * unmodified TU baseline).
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-checked against asm/.../func_8018AB20.s)
 *
 *  §48  STRUCT ASSIGN, not a hand-rolled temp copy.  `m = D_800AE620;` on a
 *       32-byte aggregate routes expr.c move_by_pieces, which emits the exact
 *       lw/lw/lw + sw/sw/sw (x2) + lw/lw + sw/sw grouping AND picks the
 *       target's registers ($a2 = source address, $v0/$v1/$a1 = carriers), and
 *       keeps the arg0*14 allocator chain OUT of the copy.  The manual
 *       three-temp form (DEFINE_func_8012B4B8, engine_core.h L29487) emits the
 *       same instruction MIX but a different allocation (+60 mismatches).
 *
 *  §21/T6  The double-buffer index D_800B9A02 is read at ALL THREE use sites
 *       (three `lhu`s off ONE materialised `la`).  A PLAIN read is CSEd down to
 *       two AND keeps -G0 symbol addressing (lui+lhu per read, +1 insn); a
 *       POINTER local gives the `la` but lets cse fold the third read.  The
 *       `volatile u16 *` pointer local reproduces BOTH properties and leaves
 *       the TU's own `extern s16 D_800B9A02;` untouched.
 *
 *  T6   The OT base is bound to an s32 local (`ot`) so the tag read/write keep
 *       the `0x40($v1)` displacement form instead of folding into the pointer.
 *
 *  L4   `mp`, a pointer local bound to &m, is what puts the matrix address in a
 *       callee-saved register ($s2) and turns each argument setup into a move;
 *       passing the array directly re-materialises `addiu $aN,$sp,0x10` at
 *       every call site and drops $s6 from the frame entirely.
 *
 *  S1   `t = *(u16 *)ent;` is hoisted ABOVE the two `sh $zero` stores — the
 *       sp-relative stores are not disambiguated from the $s0-based load, so
 *       only SOURCE ORDER moves it (4 mismatches).
 *
 *  T-form  `u16 bx/by` (not s32) is what makes `addu $v0,$s3,$v0` come out with
 *       the accumulator first; through s32 locals combine canonicalises the
 *       zero_extend into operand 0 and both adds emit reversed.
 *
 *  §83c-inverse  FRAME: 0x70 = 16 args + 56 declared vars + 32 saved regs + an
 *       8-byte COMPILER TEMP that gcc allocates for the two `symbol+register`
 *       memory references (both D_800A651C).  So the DECLARED locals must total
 *       56, not 60: m(32)@0x10, sv(8)@0x30, out(8)@0x38, v(8)@0x40 — the third
 *       word of the vector handed to func_8004901C (sp+0x48) lands INSIDE that
 *       compiler temp.  `s32 v[3]` gives a 0x78 frame and 19 extra mismatches.
 *       Do NOT invent a dead local to reach the frame size.
 *
 * ---------------------------------------------------------------------------
 * THE TWO RESIDUAL CLUSTERS AND WHAT ACTUALLY CLOSED THEM
 * (both are gcc-2.7.2-map/sched.md §1 rule 7 "BIRTHING BOOST" + rule 5(b)
 *  "potential hazard"; diagnosed from the cc1 `-dS` ready-list trace, which
 *  names the decision verbatim: `;; insn 245 has a greater potential hazard`.)
 *
 *  (a) The three symbol loads before the first RotMatrixZ came out E4,EA,E6
 *      instead of EA,E4,E6.  `lh $a0,D_801EB6E2` is a single-set SET(REG,…) —
 *      the sched1 birthing boost sinks it to just before its consumer (the
 *      jal), i.e. one slot too late.  Statement order CANNOT fix this: written
 *      as a plain local the load is combined into the call's arg setup, so its
 *      LUID is the call's either way (verified: two source orders, identical
 *      bytes).  `register s32 ang __asm__("$4")` keeps the load a separate insn
 *      AT its source position — zero extra instructions, +0 bytes.
 *
 *  (b) The tail's `lw $v1,0($s1)` (`*(u32 *)p`) belongs in the load-delay slot
 *      of `lhu $a0,0($a2)`; ours landed 7 insns later with `lui $a0,0xff00`
 *      taking the slot.  sched1 trace: at T-27 the ready list is
 *      `247 (7f000001) 245 (7f000001)` — BOTH boosted — and the tie goes to the
 *      LOAD via `potential_hazard` (memory-unit users beat ALU insns), so the
 *      load is picked first = placed LAST.  TWO edits are needed and neither
 *      works alone:
 *        1. KILL the boost on the load's destination — `pv` gets a second SET
 *           from a zero-byte dead `__asm__ __volatile__("" : "=r"(pv));` at the
 *           end of the function (sched.md S2: a plain C reassignment does not
 *           work, cse/flow removes it; reusing one local across BOTH addPrim
 *           halves does kill the boost but makes `pv` a 2-death GLOBAL allocno
 *           that loses $v1, §136).  With the boost dead, sched1 emits the
 *           target order exactly (proved with -fno-schedule-insns2).
 *        2. PIN `pv` to $v1 (`register u32 pv __asm__("$3")`).  Without it,
 *           local-alloc gives $v1 to the shorter, denser index quantity and
 *           `pv` lands in $a1/$t0; sched2 then re-applies rule 5(b) and undoes
 *           sched1's order.  With `pv` in $v1 the index is pushed to $a0, the
 *           0xFF000000 constant reuses $a0, and its output-dependence on the
 *           index's `sll/addu` FREEZES it after them — which is precisely the
 *           target's shape, and what makes sched2 leave sched1's order alone.
 *
 *      Pin-trim log (all re-scored): dropping the $a2 `bidx` pin — MATCH;
 *      dropping the $a3 0xFFFFFF pin — MATCH; dropping `ang` — 4 mismatches
 *      (a dead-volatile boost-kill on `ang` does NOT substitute); dropping
 *      `pv` — 11; dropping the dead `pv` asm — 11.  Two pins are the minimum
 *      found.
 *
 * ---------------------------------------------------------------------------
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801EB6DC/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801EB6E0, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_8018AB20 is byte-identical.
 */

void func_8018AB20(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_8018AB20 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801EB6DC;
    extern s16 D_801EB6DE;
    extern s16 D_801EB6E0;
    extern s16 D_801EB6E4;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_8018AB20 m;                    /* sp+0x10 */
    s16 sv[4];                           /* sp+0x30 */
    s16 out[4];                          /* sp+0x38 */
    s32 v[2];                            /* sp+0x40 — 3rd word lives in the temp area */
    void *mp;
    u8 *p;
    u8 *ent;
    s32 ot;
    u16 bx;
    u16 by;
    register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */
    volatile u16 *bidx;
    s32 t;
    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */

    m = D_800AE620;
    mp = &m;

    ent = (u8 *)((arg0 * 14) + (s32)&D_801EB6E4);
    p = (u8 *)D_800A5E60;
    D_800A5E60 = (s32)p + 0x1C;

    p[3] = 6;
    p[7] = 0x32;
    p[4] = ent[6];
    p[5] = ent[7];
    p[6] = ent[8];
    p[0xC] = ent[0xA];
    p[0xD] = ent[0xB];
    p[0xE] = ent[0xC];
    p[0x14] = ent[0xA];
    p[0x15] = ent[0xB];
    p[0x16] = ent[0xC];

    ang = D_801EB6E2;
    bx = (u16)D_801EB6DC;
    by = (u16)D_801EB6DE;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801EB6E0;
    v[1] = *(s32 *)((u8 *)v + 8);
    v[0] = v[1];
    func_8004901C(mp, v);

    t = *(u16 *)ent;
    sv[2] = 0;
    sv[1] = 0;
    sv[0] = t;
    *(s16 *)(p + 8) = bx;
    *(s16 *)(p + 0xA) = by;

    RotMatrixZ(*(s16 *)(ent + 2) - (((s32)*(u16 *)(ent + 4) << 16) >> 17), mp);
    ApplyMatrixSV(mp, sv, out);
    *(s16 *)(p + 0x10) = bx + (u16)out[0];
    *(s16 *)(p + 0x12) = by + (u16)out[1];

    RotMatrixZ(*(s16 *)(ent + 4), mp);
    ApplyMatrixSV(mp, sv, out);
    bx += (u16)out[0];
    *(s16 *)(p + 0x18) = bx;
    by += (u16)out[1];
    *(s16 *)(p + 0x1A) = by;

    /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
    bidx = (volatile u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (*(u32 *)(*(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)) + 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
}


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




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018AE30(s32 a0);

void func_8018AE08(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_8018AE30((s32)pv);
}



/* func_8018AE30 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801E9E68 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_8018AEB8 arg0
 *   sp+0x18  s32 pv[4]   (16 bytes) -> pv[0] = copy dest, &pv[2]/&pv[3] = 0x20/0x24
 *
 * The lwl 0x3 / lwr 0x0 / swl 0x1B / swr 0x18 block move: a 4-byte struct assign
 * whose type has ALIGNMENT 1 (cookbook §48-C2).  Align 1 (not 2) is load-bearing —
 * it is what pushes the copy off the move_by_pieces path (which keeps the SYMBOL
 * in the address and emits a fresh `lui $at,%hi` per reference) onto mips.c
 * expand_block_move, which copy_addr_to_reg's the source address into ONE held
 * register first -> `lui $a1,%hi; addiu $a1,$a1,%lo; lwl 3($a1); lwr 0($a1)`.
 * A {u16,u16} (align 2) struct compiles to the same opcode sequence but with the
 * folded-symbol addressing: 4 mismatches.  Struct assign, NOT memcpy (memcpy
 * byte-matches in isolation but lowers to `jal memcpy` in any TU that declares
 * it — §2959).
 *
 * All four callee prototypes are copied VERBATIM from this TU (func_8004914C /
 * func_800491AC / RotTransPers at file scope L3484-3486; func_8018AEB8 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801E9E68 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8018AEB8(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_8018AE30(s32 a0) {
    extern u8 D_800AF648;
    extern V4_8018AE30 D_801E9E68;
    u16 sxy[4];
    s32 pv[4];

    *(V4_8018AE30 *)pv = D_801E9E68;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_8018AEB8(sxy, pv, 0x10, 0x18);
}



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





void func_8018AF24(void *a0, void *a1, s16 a2) {

    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    extern u8 D_801EB5D8;
    extern u8 D_801EB5D9;
    extern u8 D_801EB5DA;
    extern u32 D_801EB5D4;
    if (a0 != NULL) {
        D_801EB5D0 = *(u16 *)a0;
        D_801EB5D2 = *(u16 *)((s32)a0 + 2);
    } else {
        D_801EB5D0 = 0;
        D_801EB5D2 = 0;
    }

    D_801EB5D8 = *(u8 *)a1;
    D_801EB5D9 = *(u8 *)((s32)a1 + 1);
    D_801EB5DA = *(u8 *)((s32)a1 + 2);
    D_801EB5D4 = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018AF94(s32 a0) {

    extern u8 D_800AF648;
    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801EB5D0 = sxy[0];
    D_801EB5D2 = sxy[1];
}




extern s32 func_8018B174(void);
extern void func_8018B058(s32 a0, s16 a1, u16 a2);

void func_8018B00C(s32 a0, s32 a1) {
    s32 result = func_8018B174();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_8018B058(result, ext_a0, (u16)a1);
    }
}



/* func_8018B058 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801EB5DC.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801EB5DC : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801EB5D6 : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_8018B058(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_8018B058");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801EB5DC;
    extern s16 D_801EB5D6[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_8018B058 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_8018B058 *)((s32)&D_801EB5DC + (a0 << 4));

    rad = a2;
    rad = a2 + (rand() % (rad >> 2) - (rad >> 3));

    ang = a1 + (rand() & 0x3f) - 0x20;
    p->f6 = ang;

    m = rad;
    t8 = (func_80047948(p->f6) * m) >> 12;
    tC = (func_8004787C(p->f6) * m) >> 12;
    p->f8 = t8 << 16;
    p->fC = tC << 16;

    p->f0 = (rand() & 0xf) + 0x10;
    p->f2 = m << 6;
    p->f4 = (s32)D_801EB5D6[0] * 64;
}




s32 func_8018B174(void) {

    extern s16 D_801EB5DC;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801EB5DC + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_8018B1B0 — the 16-slot particle/effect stepper over D_801EB5DC[16]
 * (0x10-byte records; slot 0 = the `active` u16 that func_8018AD5C clears and
 * func_8018B0EC scans).  Layout used here, all as byte-offsets off ONE walked
 * base pointer:
 *   +0x0 u16 active   +0x2 s16 angle   +0x4 u16 dangle
 *   +0x6 s16 dir      +0x8 s32 x       +0xC s32 z
 *
 * IV shape (cookbook §3-Giv / gcc-map L1): the target has ONE biv (the walked
 * base, kept alive by the bare +0x0 accesses, which find_mem_givs excludes from
 * giv formation) plus ONE combined DEST_ADDR giv anchored at base+2
 * (`addiu $s1, $s2, 0x2`).  combine_givs takes g1 from the list HEAD and
 * record_giv PREPENDS, so *the last-emitted offset reference anchors*: the
 * `+= dangle` statement (which ends on a +0x2 store) must therefore come LAST
 * in the body.  Written before the two s32 updates it anchors at base+0xC
 * instead -> 14 mismatched immediates.
 *
 * Both rsin/rcos products are computed BEFORE any store because gcc-2.7.2's
 * sched.c makes every mem ref depend on last_function_call — a store emitted
 * between the two `jal`s could not have floated below the second one.
 *
 * `i++` precedes the pointer bump in the for-increment: that emission order is
 * what puts `addiu $s4,$s4,1` ahead of the giv's `addiu $s1,$s1,0x10` (the
 * biv's own bump then fills the branch delay slot).
 *
 * func_80047948 / func_8004787C keep this TU's file-scope prototypes verbatim
 * (L2197-2198, `s32` param) — the s16 field is sign-extended at the call site
 * by the `lh`, so the narrower m2c-style `s16` prototype is not needed (§17a-1).
 * D_801EB5DC uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018B1B0(void) {

    extern s16 D_801EB5D6;
    extern s16 D_801EB5DC;
    extern void func_8018B2C4(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801EB5D6;
    p = &D_801EB5DC;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_8018B2C4(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_8018B2C4 — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801EB5DC[a0] record, projects the
 * four corner offsets into the packet, then links the packet into the OT.
 *
 * Byte-verified levers (all three were needed; each is worth 8-31 insns):
 *
 *  A. THE OT LINK IS THE libgpu P_TAG BITFIELD, NOT HAND-MASKING.  Writing
 *     `*(u32*)q = (*(u32*)q & 0xFF000000) | (ot & 0xFFFFFF)` is byte-correct
 *     arithmetic but gives the WRONG register assignment (16 mismatches: the
 *     0xFFFFFF / 0xFF000000 / &D_800B9A02 pseudos land in a0/a2/a3 permuted,
 *     and the `lw $v1,0($s3)` gets serialised behind the index load).  The
 *     `unsigned addr:24; unsigned len:8` bitfield insert reproduces both the
 *     allocation and the schedule exactly.  This is just `addPrim(ot, q)`.
 *
 *  B. THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`), NOT
 *     `*(s32*)((u8*)&D_800A651C + i*20)`.  With the pointer-arith spelling gcc
 *     allocates a phantom 8-byte stack temp that is never referenced, pushing
 *     the frame from 0x68 to 0x70 (cookbook D6 in reverse: the frame is too
 *     BIG).  The temp only appears when the SAME lookup expression occurs in
 *     two statements; the ARRAY_REF form (engine_core.h `OtBlk`) kills it.
 *
 *  C. THE LAST ApplyMatrixSV RECOMPUTES THE MATRIX ADDRESS.  The first four
 *     matrix arguments come out of $s4 (`addu $aX,$s4,$zero`), but the fifth is
 *     `addiu $a0,$sp,0x10`.  cse.c cannot be talked out of folding a fifth
 *     `&m` into the existing pseudo: the conditional above it is a
 *     "branch around a block", so cse_end_of_basic_block EXTENDS the basic
 *     block through the join label (status AROUND) and the equivalence class
 *     for (plus fp 16) is still live.  Every source-level attempt to break it
 *     (pointer local, `mp = m` in the skipped arm, a §21 zero-byte re-tie,
 *     do{}while(0) loop notes) either changed nothing or cost 3 insns by
 *     turning the pointer into a two-def global allocno.  Pinning a reader to
 *     $sp makes the expression `(plus (reg 29) 16)` — a different rtx from
 *     `(plus (reg fp) 16)`, so cse never looks it up, and the single-use pseudo
 *     is folded by combine into the one `addiu` the target has.
 *
 *  The svp/outp block around the FIRST ApplyMatrixSV is load-bearing too:
 *  removing it costs 6 insns and two extra callee-saved registers.
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);


/* 0x10-byte-stride record table at D_801EB5DC (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_8018B2C4(s32 a0) {

    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    extern u8 D_801EB5D8;
    extern u8 D_801EB5D9;
    extern u8 D_801EB5DA;

    extern s16 D_801EB5DC;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_8018B2C4 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_8018B2C4 *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_8018B2C4 *)m = *(Mat32_8018B23C_8018B2C4 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801EB5D8;
    *(u8 *)(q + 5) = D_801EB5D9;
    *(u8 *)(q + 6) = D_801EB5DA;

    p = (Rec_8018B23C_8018B2C4 *)((s32)&D_801EB5DC + (a0 << 4));
    x = p->fA + (u16)D_801EB5D0;
    y = p->fE + (u16)D_801EB5D2;
    RotMatrixZ(p->f6, m);

    scale[0] = *(s16 *)((s32)p + 2);
    scale[1] = *(s16 *)((s32)p + 2);
    scale[2] = *(s16 *)((s32)p + 2);
    func_8004901C(m, scale);

    *(s16 *)(sv + 4) = 0;
    *(s16 *)(sv + 2) = 0;
    *(s16 *)(sv + 0) = p->f0;
    {
        void *svp = sv;
        void *outp = out;
        ApplyMatrixSV(m, svp, outp);
        __asm__ __volatile__("" : "=r"(svp));
        __asm__ __volatile__("" : "=r"(outp));
    }

    *(s16 *)(q + 0x8) = x + ((s16)out[0] >> 1) * 3;
    *(s16 *)(q + 0xA) = y + ((s16)out[1] >> 1) * 3;
    *(s16 *)(q + 0xC) = x - ((s16)out[0] >> 1);
    *(s16 *)(q + 0xE) = y - ((s16)out[1] >> 1);
    x = x + out[0];
    *(s16 *)(q + 0x10) = x;
    y = y + out[1];
    *(s16 *)(q + 0x12) = y;

    ang = -0x400;
    if (p->f0 & 1) {
        ang = 0x400;
    }
    RotMatrixZ(ang, m);

    *(s16 *)(sv + 0) = 2;
    {
        /* lever C: sp+0x10 IS &m, but spelled so cse cannot fold it to $s4 */
        register u8 *spr __asm__("$29");
        ApplyMatrixSV(spr + 0x10, sv, out);
    }

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_8018B2C4 *bp = (Bidx_8018B23C_8018B2C4 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_8018B2C4 *)q)->addr =
            ((PTag_8018B23C_8018B2C4 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_8018B2C4 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}


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


s32 func_8018BA0C(u32 a0v);
s16 func_8018B950(u32 a0);

void func_8018B60C(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_8018BA0C(s0);
    sin_val = func_8018B950(s0);

    /* Build rotation matrix on stack */
    v1 = 0x7FF8;
    *(short *)((s32)matrix_stack + 0x04) = sin_val;
    *(short *)((s32)matrix_stack + 0x00) = cos_val;
    *(short *)((s32)matrix_stack + 0x02) = 0;
    *(short *)((s32)matrix_stack + 0x06) = 0;
    *(short *)((s32)matrix_stack + 0x08) = v1;
    *(short *)((s32)matrix_stack + 0x0A) = 0;
    *(short *)((s32)matrix_stack + 0x0C) = -sin_val;
    *(short *)((s32)matrix_stack + 0x0E) = 0;
    *(short *)((s32)matrix_stack + 0x10) = cos_val;

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 0x10;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 0x12;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 0x2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 0x14;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu %0, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0)"
        : "=r"(s1)
        : "0"(s1)
        : "$12", "$13", "$14", "$2"
    );
}


#include "common.h"

/* func_8018B76C — RotMatrix: builds a 3x3 fixed-point (1.15) rotation matrix
 * from the three packed 12-bit Euler angles at a0[0..2].
 *   func_8018BA0C = cosine table lookup, func_8018B950 = sine table lookup.
 * Declarations copied VERBATIM from the TU (ov_SC02_011_jr_8017AE2C.c:6928-6929).
 */

s32 func_8018BA0C(u32 a0v);
s16 func_8018B950(u32 a0);

void func_8018B76C(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_8018BA0C(r[0] & 0xFFF);
    sx = func_8018B950(r[0] & 0xFFF);
    cy = func_8018BA0C(r[1] & 0xFFF);
    sy = func_8018B950(r[1] & 0xFFF);
    cz = func_8018BA0C(r[2] & 0xFFF);
    sz = func_8018B950(r[2] & 0xFFF);

    cxsz = (cx * sz) >> 15;
    cxcz = (cx * cz) >> 15;
    sxsy = (sx * sy) >> 15;

    m[0] = (cz * cy) >> 15;
    m[1] = ((sxsy * cz) >> 15) - cxsz;
    m[2] = ((cxcz * sy) >> 15) + ((sx * sz) >> 15);
    m[3] = (sz * cy) >> 15;
    m[4] = ((sxsy * sz) >> 15) + cxcz;
    m[5] = ((cxsz * sy) >> 15) - ((sx * cz) >> 15);
    m[6] = -sy;
    m[7] = (cy * sx) >> 15;
    m[8] = (cy * cx) >> 15;
}


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


void func_8018BAD8(u8 *a0) {
    u16 v1 = *(u16 *)(a0 + 0x5E);
    if (v1 == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (v1 == 0x24) {
        s16 buf[3];
        buf[0] = 2;
        buf[1] = 0xF;
        buf[2] = -2;
        func_80190C84((s32)a0, (u16 *)buf, 0xD);
    }
}


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


#include "common.h"

void func_8018BBCC(s32 *param_1) {
    int v1;

    v1 = *(short *)((s32)param_1 + 0xaa);
    *(short *)((s32)param_1 + 0x5c) = 0;
    *(short *)((s32)param_1 + 0x98) = 0;
    *(int *)((s32)param_1 + 0x1c) = 0;
    if (v1 == 0) {
        *(short *)((s32)param_1 + 0x100) = *(unsigned short *)(*(int *)((s32)param_1 + 0x20) + 0x18);
    } else {
        *(short *)((s32)param_1 + 0x102) = *(unsigned short *)(*(int *)((s32)param_1 + 0x20) + 0x18);
    }
}


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


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_8018BCC4(s32 param_1) {
    register s32 a __asm__("$4");
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        p = *(s32 *)(param_1 + 0x20);
        h = *(u16 *)(param_1 + 0x100);
        *(s16 *)(p + 0x1C) = h;
        *(s16 *)(p + 0x18) = h;
        a = param_1;
        *(s16 *)(a + 0x5C) |= 1;
        *(s16 *)(a + 0x60) = 0;
        q = *(s32 *)(a + 0x20);
        *(s16 *)(a + 0x62) = *(u16 *)(q + 0x12) + 0x800;
        *(s16 *)(a + 0x5E) = 1;
        ((void (*)(s32, s32))func_80131E00)(a, 1);
    } else {
        a = *(s32 *)(param_1 + 0x20);
        x = *(s16 *)(a + 0x18);
        t = x + (*(s16 *)(param_1 + 0x100) - x) / 4;
        *(s16 *)(a + 0x1C) = t;
        *(s16 *)(a + 0x18) = t;
    }
}



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


extern void func_8002AC00(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018BDB8(s32 *arg0) {
    func_8002AC00(8);
    if (*(u16 *)((u8 *)arg0 + 0x5E) == 0x1D) {
        func_8002D4C8(0x440, 0);
    } else {
        func_8002D4C8(0x43F, 0);
    }
}



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


extern void func_8012A828(s32 a0, void *a1);
extern void D_801DEB58;

s32 func_8018BF60(void *a0) {
    u16 v;
    *(u16 *)((s32)a0 + 2) = 3;
    func_8012A828((s32)a0, &D_801DEB58);
    v = *(u16 *)(*(s32 *)((s32)a0 + 0x78) + 2);
    *(u16 *)((s32)a0 + 0x5E) = 0;
    *(u16 *)((s32)a0 + 0xDC) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x3C;
    *(u16 *)((s32)a0 + 0xFE) = 0;
    *(u16 *)((s32)a0 + 0x5C) = v;
}


extern s32 (*D_801D6FBC[])(void);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void);

void func_8018BFBC(u16 *s0)
{
    s32 v0;
    s32 temp;

    // Call function pointer from table indexed by s0[1]
    v0 = D_801D6FBC[s0[1]]();

    // Check if s0[0] is non-zero
    if (s0[0] != 0) {
        // Load from s0 + 0x10 (0x20 bytes due to u16 pointer arithmetic)
        temp = *(s32 *)(s0 + 0x10);
        // Modify u16 at offset 0x2c of temp
        *(u16 *)((char *)temp + 0x2c) = *(u16 *)((char *)temp + 0x2c) | 0x10;

        // Call func_8012C044 and check result
        v0 = func_8012C044((s32)s0);
        if (v0 != 0) {
            // Call func_8012C098
            ((void (*)(s32))func_8012C098)((s32)s0);
        }
    }
}



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


void func_8018C11C(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF20000);
}


extern void func_8012CBF4(s32);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012C218(void *a0);

extern u8 D_801D7030[];
extern u8 D_800D3918[];

void func_8018C174(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(s32))func_8012CBF4)(param_1);
    if (v0 != 0) {
        func_8012C218((void *)param_1);
        return;
    }

    v0 = func_8012D5E4(param_1, (s32)&D_801D7030, (s32)&D_800D3918, 0xA);
    if (v0 != 0) {
        func_8012C218((void *)param_1);
        return;
    }

    v0 = *(s32 *)(param_1 + 0x1c);
    v0 = v0 - 1;
    *(s32 *)(param_1 + 0x1c) = v0;
    if (v0 == 0) {
        func_8012C218((void *)param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_011/nonmatchings/ov_SC02_011_jr_8017AE2C", func_8018C1E0);

extern s32 func_8012BCCC(s32 a0);

void func_8018C31C(s32 a0) {
    register s32 result __asm__("$2");
    register s32 threshold __asm__("$3");

    if (*(s16 *)(a0 + 0x70) & 0x8000) {
        result = func_8012BCCC(a0);
        threshold = 0x90000;
    } else {
        result = func_8012BCCC(a0);
        threshold = 0x24000;
    }
    threshold = (threshold < result);
    if (threshold) {
        return;
    }
    func_8018BE00(a0);
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018BF60(void *a0);
void func_8018C388(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8018BF60)(param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);

void func_8018C3C0(s32 param_1)
{
    if (func_8012BEE8(param_1) == 1) {
        if (*(s16 *)(param_1 + 0x70) & 0x8000) {
            func_8018BE40(param_1, 0x40000, 0xC4000);
        } else {
            func_8018BE40(param_1, 0x9000, 0x24000);
        }
    }
}



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


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);

extern s32 D_801D6EE8;
extern u8 D_801D6F1C;
extern u8 D_801DEF38;

void func_8018C47C(s32 s0) {
    register s32 v1 __asm__("$3");
    s32 v0;
    s32 a1v;

    v0 = func_8012C354(s0, (s32)&D_801D6EE8);
    if (v0 == 0) {
        return;
    }

    v1 = 0xFFFBFFFD;
    *(s32 *)(s0 + 0xB4) = v1;
    v1 = *(s32 *)(s0 + 0x20);
    *(u8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)&D_801D6F1C;
    *(s32 *)(s0 + 0xC4) = 1;
    v0 = *(u16 *)(v1 + 0x2C);
    v0 |= 0x10;
    *(u16 *)(v1 + 0x2C) = v0;

    v0 = *(s32 *)(s0 + 0x20);
    a1v = *(s16 *)(s0 + 0x70);
    v0 = *(u16 *)(v0 + 0x18);
    *(u16 *)(s0 + 0x100) = v0;

    v0 = func_8012C658(0x125, a1v, s0);
    *(s32 *)(s0 + 0x6C) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s0);
    } else {
        *(s16 *)(s0 + 0x2) = 1;
        func_8012A828(s0, (void *)&D_801DEF38);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void*);
extern void func_8001C214(s32, s32);
extern s32 D_801D8AD8;

void func_8018C534(int param_1)
{
    int v0;
    int v1;
    int temp;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801D8AD8);
        temp = *(int *)(param_1 + 0x64);
        v1 = *(unsigned short *)(temp + 0x36);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0xFE) = 0x7FFF;
        *(short *)(param_1 + 0xFC) = v1;
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

extern u8 D_801DF130[];
extern u8 D_801D6FD4[];




void func_8018C5A4(s32 *self)
{
    s32 *tgt = (s32 *)*(s32 *)((s32)self + 0x64);
    SV3 out;

    if (*(s16 *)((s32)self + 0xFE) == 0x7FFF) {
        *(s16 *)((s32)self + 0xFE) =
            *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
    }

    if (*(s16 *)((s32)self + 0xFC) !=
        *(s16 *)(*(s32 *)((s32)self + 0x64) + 0x36)) {
        func_8012C218(self);
        return;
    }

    *(Blk8 *)(*(s32 *)((s32)self + 0x20) + 0x10) =
        *(Blk8 *)(*(s32 *)((s32)tgt + 0x20) + 0x10);

    if (*(s32 *)(*(s32 *)((s32)self + 0x64) + 0x90) != (s32)D_801DF130) {
        *(s16 *)(*(s32 *)((s32)self + 0x20) + 0x12) =
            *(u16 *)((s32)self + 0xFE);
        *(s32 *)((s32)self + 0x4) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x4);
        *(s32 *)((s32)self + 0x8) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x8);
        *(s32 *)((s32)self + 0xC) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0xC);
    } else {
        func_8012F214(*(s32 *)((s32)self + 0x64), (s32)D_801D6FD4, (s32)&out);
        *(s16 *)((s32)self + 0x6) = out.a;
        *(s16 *)((s32)self + 0xA) = out.b;
        *(s16 *)((s32)self + 0xE) = out.c;
    }

    *(Blk8 *)(*(s32 *)((s32)self + 0x20) + 0x18) =
        *(Blk8 *)(*(s32 *)((s32)tgt + 0x20) + 0x18);

    {
        u16 flag = *(u16 *)(*(s32 *)((s32)tgt + 0x20) + 0x2C);
        u16 cur = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x2C);
        flag &= 0x10;
        cur |= flag;
        *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x2C) = cur;
    }

    *(s32 *)(*(s32 *)((s32)self + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)((s32)tgt + 0x20) + 0x4);
}


#include "common.h"

extern s32 D_801DF74C[];
extern s32 func_8012C044(s32);
extern void func_8018DBF4(s32);

void func_8018C734(void *a0)
{
    s32 v0, v1;

    // Indirect call via table indexed by *(ushort*)(a0 + 2)
    v0 = *(u16 *)((u8 *)a0 + 2);
    v0 = v0 << 2;
    v1 = *(s32 *)((s32)D_801DF74C + v0);
    ((void (*)(void))v1)();

    // Check if first ushort is non-zero
    v0 = *(u16 *)a0;
    if (v0 != 0) {
        v0 = *(u16 *)((u8 *)a0 + 0xFE);
        v0 = v0 + 0x80;
        *(u16 *)((u8 *)a0 + 0xFE) = v0;
        v0 = func_8012C044((s32)a0);

        if (v0 == 1) {
            *(u16 *)((u8 *)a0 + 0x100) = 1;
            func_8018DBF4((s32)a0);
        }
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32, s32);
extern s32 D_801DF598;
extern s32 D_801E2900;
extern s32 D_801DF6AC;

void func_8018C7B8(s32 a0) {
    s32 v0;
    s32 v1;
    void *a0_val;

    if (func_8012C354(a0, (s32)&D_801DF598) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        v1 = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)&D_801DF6AC;
        *(s32 *)(a0 + 0xB4) = -0x20AD;
        *(s32 *)(a0 + 0xE0) = 0;
        v1 = v1 | 0x1;
        *(s32 *)(a0 + 0xC4) = v1;

        func_8012A828(a0, (void *)&D_801E2900);

        if ((*(u16 *)(a0 + 0x70) & 0x1) != 0) {
            a0_val = (void *)*(s32 *)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 1;
            *(s16 *)(a0 + 0x5C) = 0;
            *(s32 *)(a0_val + 0x4) = *(s32 *)(a0_val + 0x4) | 0x80000000;
        } else {
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
        }
    }
}


#include "common.h"

extern s32 func_8012E778(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012BD14(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8018C874(s32 a0)
{
    s32 t;
    s32 u;
    register s32 p __asm__("$3");

    if (*(s16 *)(a0 + 0x102) == 0) {
        if (func_8012E778(a0, 0x64008C) == 0) {
            return;
        }
        *(s16 *)(a0 + 0x102) = 1;
    } else {
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x18FFF) {
            return;
        }
    }

    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 8;
    *(u16 *)(a0 + 0x5C) = 0xAA10;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x2C) |= 0x10;

    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 0x4) &= 0x7FFFFFFF;
    t = func_80047948(0x380);

    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;

    u = func_8004787C(0x380);
    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1A) = (u << 1) + 0x1000;

    *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018C968(s32 s0) {
  s32 v0;
  s32 v1;

  if (func_8012BEE8(s0) != 0) {
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    v1 &= 0xFFEF;
    *(s16 *)(v0 + 0x2C) = v1;
    *(s16 *)(s0 + 0x2) = 3;
  } else {
    s32 a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_80047948(a0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x18) = v0;
    a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_8004787C(a0);
    v0 = v0 << 1;
    v1 = *(s32 *)(s0 + 0x20);
    v0 += 0x1000;
    *(s16 *)(v1 + 0x1A) = v0;
  }
}


extern s32 D_801E2900;
extern void func_8012A828(s32, void*);

void func_8018CA04(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, ((u8 *)&D_801E2900));
    *(s32 *)(param_1 + 0x1C) = 0x20;
    if (*(s32 *)(param_1 + 0xE0) != 0) {
        *(s32 *)(param_1 + 0xE0) = 0;
        *(s16 *)(param_1 + 0xA) = *(s16 *)(param_1 + 0xA) + 0x30;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018DD60(s32 a0);

void func_8018CA64(s32 s0) {
  s32 v0;
  s32 v1;

  v0 = *(s32 *)(s0 + 0x20);
  v1 = *(u16 *)(v0 + 0x12) + 0x40;
  *(s16 *)(v0 + 0x12) = v1;
  if (func_8018DD60(s0) != 1) {
    if (func_8012BEE8(s0) != 0) {
      *(s16 *)(s0 + 0x2) = 5;
    }
  }
}


extern s32 D_801E2900;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);

void func_8018CAC4(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 6;
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE8000);
    func_8012A828(s0, (void *)((u8 *)&D_801E2900));
    *(s32 *)(s0 + 0x1C) = 0x96;
    *(u16 *)(s0 + 0xE6) = 0;
}


extern s32 func_8018DAA8(s32 a0, s32 a1);
extern s32 func_8018DD60(s32 a0);
extern u8 D_800D3918[];

void func_8018CB20(s32 arg0) {
    if (func_8018DD60(arg0) != 1) {
        if (func_8018DAA8(arg0, D_800D3918) == 0) {
            *(s16 *)(arg0 + 2) = 3;
        }
    }
}


extern s32 D_801E29F8;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_8018CB70(a0)
void *a0;
{
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 8;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801E29F8);
    *(s32 *)(s0 + 0x1C) = 0x24;
    *(u16 *)(s0 + 0xE6) = 0;
}


#include "common.h"

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018DAA8();
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);

extern u8 D_800D3918[];

void func_8018CBBC(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 v1 __asm__("$3");
    s32 v0;
    u16 *p;

    s0 = a0;
    __asm__ __volatile__("");
    v0 = func_8012B8E4(s0, 8);
    p = *(u16 **)(s0 + 0x20);
    p[9] = p[9] + (u16)v0;

    if (*(s32 *)(s0 + 0x1C) < 0x19) {
        func_8012B178(s0, 0xFFFC0000);
        v1 = func_8018DAA8(s0, (void *)D_800D3918);

        if (v1 == 0) {
            v0 = 9;
            goto L_store;
        }
        v0 = -1;
        if (v1 == -1) {
            /* target skips the field_2 store entirely on this path */
            return;
        }
        /* else fall through to the common path */
    }

    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = 9;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x2001) {
            v0 = 9;
        } else {
            return;
        }
    }

L_store:
    *(s16 *)(s0 + 0x2) = v0;
}


















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

#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_8018D8B8(s32 a0);

void func_8018CC9C(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;
    u16 sp10[3];

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x1E;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) | 0x80000000;
            *(s16 *)(param_1 + 0xE4) = 3;
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 2 + 0x1000;
        }
        break;
    case 1:
        uVar1 = *(u16 *)(param_1 + 0xE4) - 1;
        *(u16 *)(param_1 + 0xE4) = uVar1;
        if ((s16)uVar1 == 0) {
            sp10[0] = *(u16 *)(param_1 + 0x6);
            sp10[1] = *(u16 *)(param_1 + 0xA) - 0x38;
            sp10[2] = *(u16 *)(param_1 + 0xE);
            {
                s32 e;
                s32 q;

                e = func_80143BDC(sp10);
                if (e != 0) {
                    q = *(s32 *)(e + 0xCC);
                    if (q != 0) {
                        *(s16 *)(q + 0x1A) = 0x5000;
                        *(s16 *)(q + 0x18) = 0x5000;
                    }
                }
            }
            *(s16 *)(param_1 + 0x34) = 2;
        }
        /* fallthrough */
    case 2:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 3;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) & 0x7FFFFFFF;
            func_8018D8B8(param_1);
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x5C) = 0xAA10;
        }
        break;
    case 3:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) & 0xFFEF;
            *(s16 *)(param_1 + 0x2) = 0xB;
        } else {
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = sVar2;
            *(s16 *)(iVar3 + 0x18) = sVar2;
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = uVar1 * 2 + 0x1000;
        }
        break;
    }
}


extern s32 D_801E2AD0;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_8018CEB0(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xC;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801E2AD0);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
    func_8012B23C(s0);
}


#include "common.h"

extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018DAA8();
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern u8 D_800D3918[];

void func_8018CF04(s32 s0) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v0 = func_8012B8E4(s0, 8);
    v1 = *(s32*)(s0 + 0x20);
    *(s16*)(v1 + 0x12) = (s16)(*(u16*)(v1 + 0x12) + v0);
    func_8012B178(s0, 0xFFFC0000);
    v0 = func_8018DAA8(s0, D_800D3918);
    if (v0 == -1)
        return;
    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = func_8012BCCC(s0);
        v0 = (v0 < 0x7001);
        if (v0)
            v0 = 0xD;
        else
            v0 = 0x3;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x3001)
            v0 = 0xD;
        else
            return;
    }
    *(s16*)(s0 + 0x2) = v0;
}


extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E2BA8[];

void func_8018CFAC(s32 param_1) {
    *(s16 *)(param_1 + 2) = 0xE;
    func_8012A828(param_1, D_801E2BA8);
    *(s32 *)(param_1 + 0x1C) = 0x5A;
    *(s16 *)(param_1 + 0xDC) = 0;
    *(s16 *)(param_1 + 0xFE) = 0;
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018D720();

void func_8018CFF4(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v0;
    s32 s1;

    v0 = func_8012BCCC(s0);
    if (v0 <= 0x14400) {
        if (*(s32 *)(s0 + 0x1C) >= 0x16) {
            v0 = func_8012B8E4(s0, 8);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
        }
        s1 = *(s32 *)(s0 + 0x1C);
        if (s1 == 0x15) {
            func_8002D4C8(0x522, 0);
        }
        if (s1 != 0x15 || *(s32 *)(s0 + 0x1C) != s1) {
            s32 v1 = *(s32 *)(s0 + 0x1C);
            if (v1 == 0xB || v1 == 1) {
                func_8018D720(s0);
            }
        } else {
            func_8018D720(s0);
        }
        v0 = func_8012BEE8(s0);
        if (v0 == 0) {
            return;
        }
        v0 = 3;
    } else {
        v0 = 7;
    }
    *(s16 *)(s0 + 2) = (s16)v0;
}


#include "common.h"

extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 D_801E29F8;

void func_8018D0C8(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x10;
    func_8012B2CC(s0);
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFD0000);
    func_8012A828(s0, (void *)&D_801E29F8);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


extern s32 D_801E29F8;
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018DAA8(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012A828(s32 a0, void *a1);

void func_8018D128(s32 a0) {
    if (*(s16 *)(a0 + 0xAA) <= 0) {
        *(u16 *)(a0 + 2) = 3;
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, (void *)&D_801E29F8);
            *(s32 *)(a0 + 0x1C) = 0x1A;
        }
        func_8018DAA8(a0, (s32)D_800D3918);
    }
}




void func_8018D19C(void *a0)
{
    s32 a1;
    s32 b;
    u16 v1;

    a1 = *(s32 *)((s32)a0 + 0x20);
    v1 = *(u16 *)(a1 + 0x2C);
    __asm__ __volatile__("" : : "r"(v1));
    if (v1 & 0x10) {
        *(u16 *)(a1 + 0x2C) = v1 & 0xFFEF;
        b = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(b + 0x1C) = 0x1000;
        *(u16 *)(b + 0x1A) = 0x1000;
        *(u16 *)(b + 0x18) = 0x1000;
    }
}


extern s32 func_8012B864(s32 a0);

void func_8018D1D8(s32 a0) {
    extern s32 func_8012B864(s32 a0);

    s32 s0 = a0;
    *(s16 *)(s0 + 2) = 0xF;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (func_8012B864(s0) + 0x800) & 0xFFF;
}


extern s32 D_801E3018;
extern void func_8012A828(s32 a0, void *a1);
extern void func_80131B14();

void func_8018D218(s32 s0) {
    s32 a0;
    s32 v1;

    a0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(a0 + 0x2C);
    if (v1 & 0x10) {
        *(u16 *)(a0 + 0x2C) = v1 & 0xFFEF;
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x1C) = 0x1000;
        *(u16 *)(v1 + 0x1A) = 0x1000;
        *(u16 *)(v1 + 0x18) = 0x1000;
    }
    func_80131B14(s0);
    func_8012A828(s0, (void *)&D_801E3018);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DF790[];
extern u8 D_801DF79C[];
extern u8 D_801E3098[];

void func_8018D288(s32 param_1) {
    s32 s0 = param_1;
    s32 v0;
    s32 t1;
    s32 t2;
    s32 t3;

    *(u16 *)(s0 + 0x5C) = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (*(u16 *)(s0 + 0x62) + 0x800) & 0xFFF;

    t1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t1 + 0x14) = 0;
    *(u16 *)(t1 + 0x10) = 0;
    func_8012B23C(s0);

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    *(s32 *)(s0 + 0x1C) = 0;

    t2 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t2 + 0x2C) = *(u16 *)(t2 + 0x2C) & 0xFFEF;

    t3 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t3 + 0x1C) = 0x1000;
    *(u16 *)(t3 + 0x1A) = 0x1000;
    *(u16 *)(t3 + 0x18) = 0x1000;

    if (*(u16 *)(s0 + 0x5E) == 9 || *(u16 *)(s0 + 0x5E) == 0x1C) {
        func_8012B14C(s0, (s32)D_801DF790);
        v0 = 0xCC;
    } else {
        func_8012B14C(s0, (s32)D_801DF79C);
        v0 = 0x100;
    }
    *(u16 *)(s0 + 0xDE) = v0;

    func_8012A828(s0, (void *)D_801E3098);
}


#include "common.h"

extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00();
extern void func_8012B23C(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);

extern s32 D_801DF7A8;

void func_8018D370(void *a0) {
    void *s0 = a0;
    s32 v0;
    s32 v1;
    s32 cnt;

    if (*(u8 *)(s0 + 0xC2) != 0) {
        goto L8018D470;
    }

    func_8012DBD0((s32)a0, 0x50,
                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) + 0x800, 0x1D);

    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) - *(u16 *)(s0 + 0xDE);

    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt >= 0x29) {
        goto L8018D50C;
    }

    v1 = ((s32 (*)(s32, s32))func_8012CC64)((s32)s0, (s32)&D_801DF7A8);
    if ((v1 & 0x2000) == 0) {
        goto L8018D444;
    }
    if ((v1 & 0xFF) != 2) {
        goto L8018D410;
    }
    func_80131E00(s0, 0x12);
    return;

L8018D410:
    if (*(s16 *)(s0 + 0x76) <= 0) {
        func_80131E00(s0, 6);
        return;
    }
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(s16 *)(s0 + 2) = 3;
    *(s32 *)(s0 + 0xE0) = 1;
    return;

L8018D444:
    if ((v1 & 0x4000) == 0) {
        return;
    }
    v0 = *(u8 *)(s0 + 0xC2) + 1;
    *(u8 *)(s0 + 0xC2) = v0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    func_8012B23C((s32)s0);
    *(s32 *)(s0 + 0x1C) = 0;
    return;

L8018D470:
    v1 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if ((v1 & 0x2000) == 0) {
        goto L8018D4D4;
    }
    if ((v1 & 0xFF) != 2) {
        goto L8018D49C;
    }
    func_80131E00(s0, 0x12);
    return;

L8018D49C:
    if (*(s16 *)(s0 + 0x76) > 0) {
        goto L8018D4C0;
    }
    func_80131E00(s0, 6);
    goto L8018D4D4;

L8018D4C0:
    *(s16 *)(s0 + 2) = 3;
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(s32 *)(s0 + 0xE0) = 1;

L8018D4D4:
    if ((*(s32 *)(s0 + 0x1C) & 3) == 3) {
        func_80143B6C((s32)s0, 1);
    }
    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt < 0x3D) {
        return;
    }

L8018D50C:
    func_80131E00(s0, 0xD);
    return;
}


void func_8018D52C(void *a0) {
    extern short D_801DF69C;
    s32 v0;

    v0 = *(s32 *)((char *)a0 + 0x20);
    *(s16 *)((char *)a0 + 0x5C) = 0;
    *(s16 *)((char *)v0 + 0x10) = 0;
    *(s16 *)((char *)a0 + 0x34) = 0;
    func_8012E8A8((u8 *)a0);
    func_8012A828((s32)a0, (s32)&D_801DF69C);
}


#include "common.h"

/* func_8018D574 — ov_SC02_011 (TU: src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c)
 *
 * Second-pass repair of a SCHEDULE-REORDER/2 residual (`addiu $a0,$sp,0x10`
 * vs `addiu $s2,$s2,1` swapped at the ternary merge block).  Root cause, from
 * the cc1 `-dS` sched1 dump (bb9, both insns priority 1, unboosted):
 * `rank_for_schedule` (sched.c:2385) fell all the way through to the LUID
 * tie-break, so forward order = RTL birth order.  The `$a0` insn is born at
 * call-expansion time, so `i++` had to move BELOW the call to lose the tie.
 *
 * That alone is not enough: with `i` pinned to a hard reg, gcc-2.7.2's
 * sched_analyze_1 (sched.c:1704) hits its own bug — `call_used_regs[i]` uses
 * the HARD_REGNO_NREGS sub-word index instead of `regno + i`, so it always
 * reads `call_used_regs[0]` ($zero, always call-used) and hangs a
 * REG_DEP_ANTI on the preceding call for EVERY hard-reg set.  That lifted
 * `i++` to priority 2 and stranded it after the call.  A pseudo takes the
 * other arm (sched.c:1732), which is guarded by `reg_n_calls_crossed == 0`;
 * `i` is live across rand(), so it escapes the anti-dep entirely.
 * => drop the `$18` pin on `i` AND sink `i++` below func_80143BDC.
 *
 * Other levers (kept from pass 1): the two divide blocks are genuine r%48 /
 * r%24; the r1%4096 is hand-expanded as ternary-round + shift (writing `%`
 * makes gcc insert a spurious v0->v1 copy); pins hold $s3/$s4/$s0/$a3/$v1;
 * the func_8012B0B4 stack result is cached into a plain local so it stays in
 * a callee-saved reg instead of being reloaded each use.
 *
 * Decls copied verbatim from the destination TU's file-scope declarations
 * (func_80143BDC returns s32 there, TU L11414 — not void).
 */

extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 arg0);
extern void func_8018DBF4(s32);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_80143BDC(u16 *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_8018D574(s32 a0) {
    register s32 obj __asm__("$19");
    s32 i;
    register s32 t4 __asm__("$20");
    register s32 tmp __asm__("$16");
    register s32 q1 __asm__("$7");
    unsigned int *pbuf;
    s32 r1, r2, r4;
    s32 ang1, dist;
    s32 base, v3;
    s32 buf;
    u16 pos[3];

    obj = a0;

    if (*(u16 *)(obj + 0x34) != 0) {
        if (func_8012BEE8(a0) != 0) {
            func_8002AC00(0xA);
            func_80130D48(obj);
            func_8018DBF4(obj);
        }
        return;
    }

    i = 0;
    pbuf = (unsigned int *)&buf;
    for (; i < 10;) {
        r1 = rand();
        tmp = (r1 >= 0) ? r1 : (r1 + 0xFFF);
        tmp = (tmp >> 12) << 12;
        ang1 = r1 - tmp;

        r2 = rand();
        q1 = r2 / 48;
        dist = r2 - q1 * 48;

        func_8012B0B4(pbuf, ang1, dist);
        t4 = buf;

        pos[0] = *(u16 *)(obj + 0x6) + t4;

        v3 = rand() % 24;

        base = *(s16 *)(obj + 0xA) - 0x34;

        r4 = rand();
        {
            s32 t1 = (r4 & 1) ? (base + v3) : (base - v3);
            pos[1] = t1;

            {
                register s32 hi4 __asm__("$3");
                hi4 = t4 >> 16;
                pos[2] = *(u16 *)(obj + 0xE) + hi4;
            }
            func_80143BDC(pos);
            i++;
        }
    }

    *(s32 *)(obj + 0x1C) = 0x10;
    *(u16 *)(obj + 0x34) += 1;

    for (i = 0; i < 3; i++) {
        func_8012C658(0x240, i, obj);
    }
}


extern void RotTransSV(void *a0, void *a1, void *a2);
extern u8 D_801DF68C[];
extern u8 D_801DF694[];

#define SRM_8018D720(r0) __asm__ volatile (          \
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
#define STM_8018D720(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_8018D720(void *param_1)
{
    s32 *m;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;
    u16 cnt;

    m = (s32 *)(*(s32 *)((s32)param_1 + 0x20) + 0x34);

    SRM_8018D720(m);
    STM_8018D720(m);

    RotTransSV(D_801DF68C, sv0, &flag);
    RotTransSV(D_801DF694, sv1, &flag);

    func_8018D820(*(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12), (s32)sv0,
                  *(s16 *)((s32)param_1 + 0xDC));
    func_8018D820(*(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12), (s32)sv1,
                  *(s16 *)((s32)param_1 + 0xDC));

    cnt = *(u16 *)((s32)param_1 + 0xDC);
    cnt = cnt + 1;
    *(u16 *)((s32)param_1 + 0xDC) = cnt;
    if ((s16)cnt >= 3) {
        *(u16 *)((s32)param_1 + 0xDC) = 2;
    }
}


#include "common.h"

extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern u32 D_801DF5CC[];

u8 * func_8018D820(s32 a0, s32 a1, s32 a2) {
    register s32 s0 __asm__("$16") = a2;
    register s32 s2 __asm__("$18") = a0;
    u8 *s1;
    u8 *ret;
    register s32 v1 __asm__("$3");

    s1 = func_801290DC(0x17, (u8 *)a1);

    if (!s1) {
        return NULL;
    }

    s0 = *(s32 *)((char *)s1 + 0x20);
    func_8001CD50(s0, (s32)(&((u8 *)D_801DF5CC)[a2 << 6]));

    /* Force early materialization of the return value into a fresh reg
       (matches target: v0=s1 is scheduled right after the call, before
       the field-init stores). A plain `u8 *ret = s1;` gets copy-propagated
       away by cse and the move sinks to the `return` site instead. */
    __asm__ volatile("move %0, %1" : "=r"(ret) : "r"(s1));

    v1 = 0xC00;
    *(u16 *)((char *)s0 + 0x1E) = v1;
    v1 = 0x1000;
    *(u16 *)((char *)s0 + 0x1A) = v1;
    *(u16 *)((char *)s0 + 0x18) = v1;
    v1 = *(s32 *)((char *)s0 + 0x4);
    *(u16 *)((char *)s0 + 0x12) = s2;
    v1 |= 0x40000000;
    *(s32 *)((char *)s0 + 0x4) = v1;

    return ret;
}


#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"  /* match_one-only: gives Mat32_8018A390_8018FE94; the real TU already includes this */

extern u16 D_80126CB4;
extern u16 D_80126CB6;
extern u16 D_80126CB8;
extern s32 *D_80126B78;
extern Mat32_8018A390_8018FE94 D_800AE620;

extern void func_8012B23C(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012B864(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_8018DDD0();
extern s32 func_8018DE30();

void func_8018D8B8(s32 a0) {
    s32 vec[3];                     /* sp+0x10 */
    s32 out[3];                     /* sp+0x20 */
    u16 sp30[3];                    /* sp+0x30 */
    u16 sv[3];                      /* sp+0x38 */
    s32 unused40[2];                /* sp+0x40 -- dead 8-byte slot the frame requires (§193-I) */
    Mat32_8018A390_8018FE94 m;      /* sp+0x48 */
    s32 pos[3];                     /* sp+0x68 (16.16 fixed point) */

    func_8012B23C(a0);

    sp30[0] = *(u16 *)(a0 + 0x3A);
    sp30[1] = *(u16 *)(a0 + 0x3E);
    sp30[2] = *(u16 *)(a0 + 0x42);

    if (func_8018DDD0(a0) != 0) {
        goto body;
    }

    *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x88);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x8C);
    return;

found:
    *(s16 *)(a0 + 0x6) = sv[0];
    *(s16 *)(a0 + 0xA) = sv[1];
    *(s16 *)(a0 + 0xE) = sv[2];
    *(s32 *)(a0 + 0x14) = 0;
    goto tail;

body:
    *(s16 *)(a0 + 0x6) = D_80126CB4;
    *(s16 *)(a0 + 0xA) = D_80126CB6;
    *(s16 *)(a0 + 0xE) = D_80126CB8;

    vec[2] = (s32)0xFF600000;
    vec[1] = 0;
    vec[0] = 0;

    m = D_800AE620;
    RotMatrixY(*(s16 *)((u8 *)D_80126B78 + 0x12), &m);

    pos[1] = *(s32 *)(a0 + 0x8);
    do {
        pos[0] = *(s32 *)(a0 + 0x4);
        pos[2] = *(s32 *)(a0 + 0xC);
        func_800484EC((s32)&m, (s32)vec, (s32)out);
        pos[0] += out[0];
        pos[2] += out[2];
        sv[0] = *(u16 *)((u8 *)pos + 0x2);
        sv[1] = *(u16 *)((u8 *)pos + 0x6);
        sv[2] = *(u16 *)((u8 *)pos + 0xA);
        if (func_8018DE30(sp30, sv) == 1) {
            goto found;
        }
        vec[2] >>= 1;
    } while (-vec[2] > 0xFFFF);

    func_8012ADE4(a0);

tail:
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B864(a0);
}


#include "common.h"

/* func_8018DAA8 -- mass-lane fresh crack (Phase 31 wave p31f)
 *
 * State-gate then "avoid overlapping same-kind entity" scan of the 0x60-entry
 * table at D_801202A0 (stride 0x10C), same table/stride idiom as
 * func_80190B6C and func_8017CA14 in this TU.
 *
 * func_8012CC1C canonical form (void, $v0 cast) per sibling TUs
 * (ov_SC02_026/027/028's jr_* files): `((s32 (*)(s32,s32))func_8012CC1C)(a0,a1)`.
 * a1 is func_8018DAA8's own second parameter, forwarded untouched -- the
 * target never sets $a1 before the first jal, it just reuses the incoming
 * argument register.
 *
 * func_8012ADE4 / func_8012BC60 / func_8012B6D4 / func_8012B0B4 all already
 * declared in this TU (Law 2) -- reused verbatim.
 */

extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_80131E00(struct S80131E00*, s32);

s32 func_8018DAA8(s32 a0, s32 a1) {
    extern u8 D_801202A0[];
    s32 state;
    u8 *p;
    s32 i;
    s32 ang;
    s32 buf[2];

    state = ((s32 (*)(s32, s32))func_8012CC1C)(a0, a1);

    if ((state & 0xFF) == 2) {
        func_80131E00(a0, 0x12);
        return -1;
    }

    if (state != 0x2000) {
        func_8012ADE4((u8 *)a0);
        return 0;
    }

    for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(u16 *)a0 == *(u16 *)p && a0 != (s32)p) {
            if (func_8012BC60((struct Vec *)(a0 + 4), (struct Vec *)(p + 4)) < 0x1000) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);

                ang = func_8012B6D4((s16 *)(a0 + 4), (s16 *)(p + 4));
                func_8012B0B4((unsigned int *)buf, ang, 0x41);

                {
                    register s32 t1 __asm__("$2") = *(s32 *)(p + 4);
                    register s32 v1 __asm__("$3") = buf[0];
                    register s32 t2 __asm__("$2");
                    register s32 t3 __asm__("$4");
                    register s32 t4 __asm__("$2");

                    *(s32 *)(a0 + 4) = t1;

                    t2 = *(u16 *)(a0 + 6);
                    t3 = *(s32 *)(p + 0xC);
                    t2 = t2 + v1;
                    *(s32 *)(a0 + 0xC) = t3;
                    *(u16 *)(a0 + 6) = t2;

                    t4 = *(u16 *)(a0 + 0xE);
                    v1 = v1 >> 16;
                    t4 = t4 + v1;
                    *(u16 *)(a0 + 0xE) = t4;
                }
                goto found;
            }
        }
    }

found:
    return 1;
}


#include "common.h"

extern void func_8002A04C(void);
extern void func_8002AC00(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801439C0(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_801E2900;

void func_8018DBF4(s32 a0) {
    u16 v1;

    if (*(s16 *)(a0 + 0x100) == 0) {
        func_8002A04C();
    }

    if (*(u8 *)(a0 + 0xC1) == 0xE) {
        func_8002AC00(0xA);
    }

    v1 = *(u16 *)(a0 + 0x70);
    if ((v1 & 1) == 0) {
        goto LCFC;
    }
    if ((v1 & 0x8000) != 0) {
        goto LD44;
    }
    if (*(u8 *)(a0 + 0xC1) == 0) {
        goto LCFC;
    }

    *(u8 *)(a0 + 0xC1) = 0;
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;

    {
        s32 ent;

        *(s16 *)(a0 + 0x5E) = 0;
        *(s16 *)(a0 + 0x5C) = 0;
        *(s16 *)(a0 + 0x76) = *(u16 *)(*(s32 *)(a0 + 0x78));
        ent = *(s32 *)(a0 + 0x20);
        *(s16 *)(ent + 0x14) = 0;
        *(s16 *)(ent + 0x12) = 0;
        *(s16 *)(ent + 0x10) = 0;
    }

    {
        u16 f88 = *(u16 *)(a0 + 0x88);
        u16 f8A = *(u16 *)(a0 + 0x8A);
        u16 f8C = *(u16 *)(a0 + 0x8C);

        *(s32 *)(a0 + 0x1C) = 0x40;
        *(s16 *)(a0 + 0xAA) = 0;
        *(s16 *)(a0 + 0x6) = f88;
        *(s16 *)(a0 + 0xA) = f8A;
        *(s16 *)(a0 + 0xE) = f8C;
        func_8012A828(a0, (void *)&D_801E2900);
    }

    if (*(s32 *)(a0 + 0xCC) != 0) {
        func_801439C0(*(s32 *)(a0 + 0xCC));
    }

    func_8012B2CC(a0);
    return;

LCFC:
    if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
        s32 v1c = *(s32 *)(a0 + 0x68);
        if (v1c != 0) {
            if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
                u16 v0c = *(u16 *)(v1c + 0xA);
                v0c &= 0x7FFF;
                *(u16 *)(v1c + 0xA) = v0c;
            }
        }
    }
LD44:
    func_8012C218((void *)a0);
}


extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);

s32 func_8018DD60(s32 obj) {
    s32 d = func_8012BCCC(obj);
    if (d < 0x2001) {
        *(s16 *)(obj + 0x2) = 7;
        return 1;
    }
    if (d > 0x24000) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x400) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 7;
    return 1;
}




s32 func_8018DDD0(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80134510(s32 arg);

s32 func_8018DE30(void *a0, SVECTOR *a1)
{
    SVECTOR tmp;
    SVECTOR in;
    SVECTOR out;

    if ((func_80133784(1, a0, (s32)a1) & 0x8000) != 0) {
        return 0;
    }

    tmp.vx = a1->vx;
    tmp.vy = a1->vy;
    tmp.vz = a1->vz;

    if (func_80134510((s32)&tmp) == 0) {
        return 0;
    }

    in.vx = tmp.vx;
    in.vy = tmp.vy;
    in.vz = tmp.vz;
    out.vx = tmp.vx;
    out.vy = tmp.vy + 8;
    out.vz = tmp.vz;

    if ((func_80133784(1, &in, (s32)&out) & 0x2000) == 0
        || *((u8 *)&out + 6) != 2) {
        a1->vy = tmp.vy;
        return 1;
    }

    return 0;
}



extern void (*D_801DF7B0[])(void);

void func_8018DF08(void *a0) {
    D_801DF7B0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

   /* 32 bytes, align 4 */
               /* 12 bytes, align 4 */

extern u8 D_80078EAE;
extern Mat32_8018A390_8018FE94 D_800AE620;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018DF44(void *a0)
{
    Mat32_8018A390_8018FE94 m;
    VECTOR vec;
    void *mp;

    vec.vy = 0;
    vec.vx = 0;
    if (!D_80078EAE) {
        vec.vz = (s32)0xFFFB8000;
    } else {
        vec.vz = (s32)0xFFFE8000;
    }

    *(s16 *)((s32)a0 + 0x2C) = 0x3C;
    *(s16 *)((s32)a0 + 0x2) = 1;

    m = D_800AE620;
    mp = &m;

    RotMatrixY(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12), mp);

    func_800484EC((s32)mp, (s32)&vec, (s32)a0 + 0x10);
}


#include "common.h"

extern u16 D_801270C0;
extern s32 func_8018E0AC();
extern void func_801292C8(u8 *a0);

struct vec;
extern void func_8012931C(struct vec *a0);

void func_8018E014(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    s16 v1;
    u16 v0;
    s16 decremented;
    void *ptr_0x20;

    v1 = *(s16 *)&D_801270C0;

    if (v1 == 2) {
        return;
    }

    func_8018E0AC();

    v0 = *(u16 *)(s0 + 0x2C);
    decremented = v0 - 1;
    *(u16 *)(s0 + 0x2C) = decremented;

    if ((s16)v0 < 0) {
        func_801292C8((u8 *)s0);
        return;
    }

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x18) += 0x100;

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x1A) += 0x100;

    func_8012931C((struct vec *)s0);
}


extern s32 D_80126B58;
extern s32 func_8014CAFC(void);
extern s32 func_8018E208(void *a0);
extern u8 D_80078E78[];
extern u8 D_80078EAE;
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_8018E0AC(arg0)
void *arg0;
{
    
    extern u8 D_80078EAE;
    u8 *base;
    u8 *p;
    s32 flag;
    s16 diff[3];
    s16 pointA[3];
    s32 v0;
    void *ptr;

    base = (u8 *)&D_80126B58;
    p = D_80078E78;
    flag = 0;

    if (func_8014CAFC() != 0) {
        if (D_80078EAE != 0) {
            return 0;
        }
        flag = 1;
    }

    if (func_8018E208(arg0) == 0) {
        return 0;
    }

    pointA[0] = *(u16 *)(base + 0x6);
    pointA[1] = *(u16 *)(base + 0xA);
    pointA[2] = *(u16 *)(base + 0xE);

    diff[0] = pointA[0] - *(u16 *)((u8 *)arg0 + 0x6);
    diff[1] = pointA[1] - *(u16 *)((u8 *)arg0 + 0xA);
    diff[2] = pointA[2] - *(u16 *)((u8 *)arg0 + 0xE);

    VectorNormalSS(diff, diff);

    pointA[1] -= 0x20;

    if (!flag) {
        v0 = p[0x36];
        func_8012F568(1, 0x5001, 0, (v0 ^ 1) * 10, (s32)pointA, (s32)diff);
    } else {
        func_8012F568(1, 0x4001, 0, 0xA, (s32)pointA, (s32)diff);
    }

    ptr = *(void **)((u8 *)arg0 + 0x20);
    *(u16 *)(base + 0x42) = *(u16 *)((u8 *)ptr + 0x12);

    return 1;
}


#include "common.h"

/* func_8018E208 — MATCH (84/84 ins, match_one byte-exact).
 *
 * The TU's already-MATCHED GTE idiom (func_8018F390 / func_801904BC: matrix-set
 * + RotTransSV x2 + func_80135888), extended with a COMPUTED matrix
 * (func_80020DA4 + func_80020F34, translation overwritten from the entity's
 * s16 position) and a 4-iteration loop over two advancing per-overlay
 * vertex-pair pointers (D_801DF7B8 and D_801DF7B8+0x20).  Returns 1 on the
 * first func_80135888 hit, else 0.
 *
 * THREE LEVERS were needed on top of the obvious shape (second-pass notes —
 * the first pass sat at 65 mismatched with this same structure):
 *
 * 1. LOOP-INVARIANT HOISTING IS THE PROLOGUE'S ORDERING ENGINE.  matrix, sv0,
 *    sv1 and &flag are written INLINE inside the loop (never via preheader
 *    pointer variables — exactly the matched sibling func_8018F390's idiom).
 *    loop.c then hoists all four to the preheader IN LOOP-USE ORDER, and sched
 *    lays their `addiu $sN,$sp,K` defs down in that same order: $s6=matrix,
 *    $s5=sv0, $s4=&flag, $s3=sv1.  Preheader POINTER VARIABLES instead
 *    (`sv0p = sv0;` etc.) put those defs in SOURCE order and permute the four
 *    callee-saved registers — the first pass's residual, which no amount of
 *    declaration reordering or register pinning could straighten out.
 *    Corollary the target proves: the two `addiu $aN,$sp,0x10` call arguments
 *    are SEPARATE materializations of &matrix.  Any `m = matrix;` before the
 *    calls lets cse feed that pseudo to both call sites (`move $a1,$s6`) — so
 *    the matrix pointer MUST come from the hoist, not from a source variable.
 *
 * 2. `base` MUST BE ITS OWN LOCAL.  `p1 = D_801DF7B8 + 0x20; p0 = D_801DF7B8;`
 *    folds the +0x20 into the %lo and back-computes p0 as `addiu $s0,$s1,-32`
 *    (3 ins).  Going through `base` keeps the symbol address in its own dead
 *    pseudo ($v1) and gives the target's 4-ins
 *    lui/addiu/`addiu $s1,$v1,0x20`/`addu $s0,$v1,$zero`.
 *
 * 3. THE `do { } while (0)` IS LOAD-BEARING — do not delete it.  It is a
 *    zero-code scheduling barrier (gcc-2.7.2 sched_analyze treats
 *    NOTE_INSN_LOOP_BEG/END as a full barrier, cookbook §164/§162j).  Without
 *    it sched2 hoists `p1 += 8` above the func_80135888 call, which leaves the
 *    conditional branch's delay slot empty; reorg then steals `li $v0,1` from
 *    the branch target and inverts beqz+j into a single bnez — 83 ins, a
 *    permanent LENGTH-DRIFT/-1.  Pinned in place, `addiu $s1,$s1,0x8` fills the
 *    beqz slot itself and the target's redundant `beqz … / j … / li $v0,1`
 *    double-branch survives.
 *
 * (A 4th, smaller one: `i` is initialised in the for-init, NOT earlier — an
 * early `i = 0;` outranks the hoisted `addiu $a1,$sp,0x10` by one slot.)
 */

extern s32 D_80126B58;                                     /* TU:53   verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1656 verbatim */
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); /* TU:582  verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);      /* TU:3116 verbatim */

/* neither is declared anywhere in src/ or include/; func_80020DA4 takes the
 * (s32, s32) form of its TU-declared sibling func_80020F34.  D_801DF7B8 is
 * per-overlay data — a family remap must re-point it. */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_801DF7B8[];

/* NOT named gte_SetRotMatrix/gte_SetTransMatrix: the host TU already defines
 * those two names twice and a third definition would collide. */
#define SRM_8018E208(r0) __asm__ volatile (              \
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
#define STM_8018E208(r0) __asm__ volatile (              \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

s32 func_8018E208(void *a0)
{
    s32 *cfg;
    s32  i;
    u8  *p0;
    u8  *p1;
    u8  *base;
    s32  matrix[8];   /* sp+0x10, MATRIX-shaped: t[] at matrix[5..7] */
    s32  sv0[2];      /* sp+0x30 */
    s32  sv1[2];      /* sp+0x38 */
    s32  flag;        /* sp+0x40 */
    s32  hit;

    cfg = (s32 *)&D_80126B58;
    p0 = (u8 *)*(s32 *)((s32)a0 + 0x20);

    func_80020DA4((s32)p0 + 0x10, (s32)matrix);
    func_80020F34((s32)matrix, (s32)p0 + 0x18);

    matrix[5] = *(s16 *)(p0 + 0x8);
    matrix[6] = *(s16 *)(p0 + 0xA);
    matrix[7] = *(s16 *)(p0 + 0xC);

    base = D_801DF7B8;
    p1 = base + 0x20;
    p0 = base;

    for (i = 0; i < 4; i++) {
        SRM_8018E208(matrix);
        STM_8018E208(matrix);

        RotTransSV(p0, sv0, &flag);
        RotTransSV(p1, sv1, &flag);

        hit = func_80135888(*(s32 *)((u8 *)cfg + 0x20), *(s32 *)((u8 *)cfg + 0x38),
                            (s32)sv0, (s32)sv1);
        do { } while (0);   /* scheduling barrier — see note 3, do not delete */
        p1 += 8;
        if (hit != 0) {
            return 1;
        }
        p0 += 8;
    }
    return 0;
}



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


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8018E420(s32 a0, u8 *a1);

void func_8018E3C8(u8 *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_8018E420(0, arg0 + 0xFD);
        func_8018E420(1, arg0 + 0xFE);
        func_8018E420(2, arg0 + 0xFF);
        *(s32 *)(arg0 + 0x1C) = 2;
    }
}


#include "common.h"

extern u32 D_801DF5CC[];
extern u32 D_801DF7F8[];
extern u32 D_801DF810;

void func_8018E420(s32 a0, u8 *a1) {
    u8 idx;
    u32 *dst;

    idx = *a1;
    if (idx >= 7) {
        *a1 = 0;
    }

    a0 <<= 6;
    idx = *a1;
    dst = (u32 *)((u8 *)D_801DF5CC + a0);
    *dst = D_801DF7F8[idx];

    idx = *a1;
    dst++;
    if (idx - 1 < 0) {
        *dst = D_801DF810;
    } else {
        *dst = D_801DF7F8[idx - 1];
    }

    (*a1)++;
}



extern void (*D_801DF84C[])(void);

void func_8018E4BC(void *a0) {
    D_801DF84C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern s32 D_801DF820[];
extern s32 D_801DF82C[];
extern s32 D_801DF844[];

void func_8018E4F8(void *a0)
{
    s32 buf[8];
    u16 out[4];
    register s32 zr __asm__("$0");
    register s32 v0 __asm__("$4");

    v0 = ((s32 (*)(void))func_8012C1B8)() + zr;
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801DF820[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    *(s32 *)((s32)a0 + 0x1C) = 8;
    *(u16 *)((s32)a0 + 0x2) += 1;

    func_8012EC04(*(s32 *)((s32)a0 + 0x64), D_801DF82C[*(u16 *)((s32)a0 + 0x70) & 0xF], buf);
    ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, (s32)D_801DF844, out);

    *(u16 *)((s32)a0 + 0x6) = out[0];
    *(u16 *)((s32)a0 + 0xA) = out[1];
    *(u16 *)((s32)a0 + 0xE) = out[2];

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
}


extern s32 D_801DF838[];
extern s32 func_8012BEE8(s32 a0);

void func_8018E5E4(s32 a0) {
    s32 *p;
    s32 s0;
    s32 r;
    u16 h;

    if (func_8012BEE8(a0) == 0) {
        return;
    }
    s0 = a0;
    *(u16 *)(s0 + 0x2) += 1;
    r = rand();
    h = *(u16 *)(s0 + 0x70);
    p = D_801DF838;
    *(s32 *)(s0 + 0x48) = p[h & 0xF] + r % 1024;
    *(s32 *)(s0 + 0x1C) = 0x100;
    *(s32 *)(s0 + 0xE0) = rand();
}


#include "common.h"

extern s32 func_80047948(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012CBF4(s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8018E678(void *a0)
{
    s32 vec[3];
    s16 out[6];
    s16 t5;

    if ((*(u16 *)((s32)a0 + 0x70) & 0xF) == 2) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) -= 0x10;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = -0x400;
        }
    } else {
        vec[0] = func_80047948((*(s32 *)((s32)a0 + 0xE0) << 6) & 0xFC0) << 8;
        vec[1] = 0;
        vec[2] = 0;
        func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, (s32)vec, (s32)out);
        *(s16 *)((s32)a0 + 0x50) = out[1];
        t5 = out[5];
        *(s32 *)((s32)a0 + 0xE0) = *(s32 *)((s32)a0 + 0xE0) + 1;
        *(s16 *)((s32)a0 + 0x54) = t5;
    }

    if (((s32 (*)(s32))func_8012CBF4)((s32)a0) != 0) {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) += 1;
    } else if (func_8012BEE8((s32)a0) != 0) {
        func_8012C218(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_8018E780(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        if ((*(u16 *)(param_1 + 0x70) & 0xF) == 2) {
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + -0x80;
            if (*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) < -0x400) {
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = -0x400;
            }
        }
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
        }
    } else {
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            ((void (*)(s32))func_8012C218)(param_1);
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 8 + 0x1000;
        }
    }
}


#include "common.h"

/* func_8018E8A0 — ov_SC02_011 / ov_SC02_011_jr_8017AE2C, 211 ins.
 * STATUS: MATCH (relocation-masked, 211/211; frame 0xC0 / vars=136 / regs=9).
 *
 * Five load-bearing spellings, each byte-proven against gcc-2.7.2 source:
 *
 * 1. TWO INDUCTION REGISTERS, $s6=obj+0xCC (biv) and $s4=obj+0xD4 (reduced giv).
 *    `q = zb + k * 3` makes q a giv of a COUNTER biv, so its add_val is the
 *    invariant pseudo `zb`, not a CONST_INT.  simplify_giv_expr (loop.c) refuses
 *    to fold `(reg) + (const)` into an add_val (both invariant, not CONSTANT_P
 *    => returns 0), so the four MEMs q[-1] q[0] ((s16*)q)[-1] ((s16*)q)[1] are
 *    NOT givs at all and keep their -4/-2/0/+2 offsets off $s4.  Spelling the
 *    same addresses off the pointer biv `p` instead gives CONST_INT add_vals,
 *    combine_givs merges all six into ONE register based at 0xD6, and the two
 *    registers collapse (measured: 210 ins, wrong offsets).
 *
 * 2. `zb = obj+0xD4` is assigned INSIDE the loop so LICM hoists it into the
 *    preheader; the giv init then coalesces with it into a single
 *    `addiu $s4,$s3,0xD4` after `addiu $s7,$sp,0x58`.  Assigned before the loop
 *    it stays in the entry block and costs `addiu $v1,$s3,212` + `move $s4,$v1`.
 *
 * 3. THE SECOND COUNTER `k` IS REQUIRED.  loop.c emits a reduced giv's update
 *    with emit_insn_before(..., biv_increment_insn), i.e. immediately BEFORE the
 *    biv it derives from.  The target's increment order is [i++][$s4+=12][$s6+=12],
 *    so the giv must hang off a biv that increments between i and p.  `k` is a
 *    dead counter that loop.c deletes after reduction, leaving exactly that order
 *    (and letting reorg steal `i++` into the `bne $s5,$v0` delay slot).
 *
 * 4. MEM_IN_STRUCT_P ASYMMETRY unblocks the entry-block schedule.  sched.c's
 *    true_dependence() drops a store->load dependence only when the LOAD is
 *    MEM_IN_STRUCT_P at a varying address and the STORE is neither.  Reading the
 *    trail count through a struct type (Cnt_8018E8A0) and writing prim.c[] through
 *    plain `*(u32 *)` casts is what lets the loop-bound `lh 0x108($s3)` float up
 *    past the colour stores; `prim.code` deliberately STAYS a struct member so it
 *    still pins the lh behind it.  With the natural spelling the lh is chained
 *    behind all five sp stores and lands next to the blez with a nop.
 *
 * 5. THE $a0 PIN TRIO.  `d = obj->x1C - i*4` is a global allocno; global.c marks
 *    REG_DEAD before the store, so the output freely reuses the dying $v1 and gcc
 *    picks `subu $v1,$v0,$v1`.  Pinning d alone makes gcc fold the load into $a0
 *    (`lw $a0` / `subu $a0,$a0,$v0`); pinning only the operands leaves d on $v1.
 *    All three pins together are the minimum that reproduces
 *    `lw $v0` / `sll $v1` / `subu $a0,$v0,$v1`.
 */

/* ---- integration surface (§161c), checked against
 *      src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c (func_8018E8A0 is the
 *      INCLUDE_ASM at line 9393):
 *   func_8012C218(void *a0)            TU:4256 verbatim  (also TU:4984 (void*))
 *   func_8004787C(s32 a0)              TU:2197 verbatim  (also TU:6679)
 *   func_80047948(s32 a0)              TU:2196 verbatim  (also TU:6678)
 *   ratan2(s32, s32)                   TU:243  verbatim  (TU:519 same types)
 *   func_80017758(void *, void *)      TU:1755 verbatim  (also TU:6125)
 *   func_80049CAC(s32, s32)            TU:3113 verbatim -> call site casts,
 *                                      exactly the TU's own idiom at TU:3143
 *   RotTransSV(void *, void *, void *) TU:3116 verbatim
 *   func_8012B414(int a0)              NOT declared in this TU; this is the
 *                                      fleet-canonical form (every other TU
 *                                      uses `int`), so the call site casts.
 *
 *   The GTE macros are named SRM_/STM_8018E8A0, NOT gte_SetRotMatrix /
 *   gte_SetTransMatrix: the host TU already defines those two names twice
 *   (TU:9781 and TU:10513) and a third definition would collide.
 *
 *   DATA (family remap must re-point these per overlay): D_801DF7F8 (u32[8]
 *   colour table) and D_801DF85C (u8[], SVECTOR quad source) have NO existing
 *   declaration anywhere in src/ or include/.
 */
extern void func_8012B414(int a0);
extern void func_8012C218(void *a0);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern s32  ratan2(s32 a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32  func_80017758(void *a0, void *a1);

extern u32 D_801DF7F8[];
extern u8  D_801DF85C[];

#define SRM_8018E8A0(r0) __asm__ volatile (          \
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
#define STM_8018E8A0(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

typedef struct { s16 vx, vy, vz, pad; } SVec8_8018E8A0;          /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } Vec16_8018E8A0;          /* 0x10 */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } Mtx_8018E8A0; /* 0x20 */
typedef struct { s16 f[0x86]; } Cnt_8018E8A0;
typedef struct {
    SVec8_8018E8A0 v[4];   /* 0x00 */
    u32            c[4];   /* 0x20 */
    s32            code;   /* 0x30 */
    s32            pad;    /* 0x34 */
} Prim_8018E8A0;           /* 0x38 */

void func_8018E8A0(void *a0)
{
    Vec16_8018E8A0  mv;      /* sp+0x10 */
    Prim_8018E8A0   prim;    /* sp+0x20 */
    Mtx_8018E8A0    mtx;     /* sp+0x58 */
    SVec8_8018E8A0  rot;     /* sp+0x78 */
    s32             flag;    /* sp+0x80 */
    s32            *p;
    s32            *q;
    s32            *zb;
    SVec8_8018E8A0 *src;
    SVec8_8018E8A0 *dst;
    register s32 d __asm__("$4");
    s32 i, j, k, base, ang, t;
    u32 col;

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x40;
    func_8012B414((s32)a0);

    mv.vz  = -0x40000;
    rot.vz = 0;
    col = D_801DF7F8[(*(u16 *)((s32)a0 + 0x10A))++ & 7];
    prim.code = 0x50000000;
    *(u32 *)((s32)&prim + 0x20) = col;
    *(u32 *)((s32)&prim + 0x24) = col;
    *(u32 *)((s32)&prim + 0x28) = col;
    *(u32 *)((s32)&prim + 0x2C) = col;

    p = (s32 *)((s32)a0 + 0xCC);
    for (i = 0, k = 0; i < ((Cnt_8018E8A0 *)a0)->f[0x84]; i++, k++, p += 3) {
        zb = (s32 *)((s32)a0 + 0xD4);
        { register s32 c1 __asm__("$2"); register s32 c2 __asm__("$3");
          c1 = *(s32 *)((s32)a0 + 0x1C); c2 = i * 4; d = c1 - c2; }
        if (d > 0x40) {
            if (i == 4) {
                func_8012C218(a0);
                return;
            }
            continue;
        }
        base = d << 6;
        ang = base & 0xFFF;
        flag = (func_8004787C(ang) << 4) >> 12;

        switch (*(s16 *)((s32)a0 + 0x70)) {
        case 0:
            t = ang;
            goto horiz;
        case 1:
            t = base + 0x800;
            t &= 0xFC0;
        horiz:
            mv.vy = (func_80047948(t) << 4) * flag;
            mv.vx = 0;
            rot.vx = -ratan2(mv.vy, mv.vz);
            rot.vy = 0;
            break;
        case 2:
            t = ang;
            goto vert;
        case 3:
            t = base + 0x800;
            t &= 0xFC0;
        vert:
            mv.vx = (func_80047948(t) << 4) * flag;
            mv.vy = 0;
            rot.vx = 0;
            rot.vy = ratan2(-mv.vz, mv.vx) - 0x400;
            break;
        }
        ((void (*)(void *, void *))func_80049CAC)(&rot, &mtx);

        q = zb + k * 3;
        p[0] += mv.vx;
        q[-1] += mv.vy;
        q[0] += mv.vz;
        mtx.t[0] = ((s16 *)p)[1];
        mtx.t[1] = ((s16 *)q)[-1];
        mtx.t[2] = ((s16 *)q)[1];

        src = (SVec8_8018E8A0 *)(D_801DF85C +
              ((s32)(s16)*(u16 *)((s32)a0 + 0x70) / 2) * 0x20);
        dst = prim.v;

        SRM_8018E8A0(&mtx);
        STM_8018E8A0(&mtx);

        for (j = 0; j < 4; j++, src++, dst++) {
            RotTransSV(src, dst, &flag);
        }
        func_80017758(&prim, (void *)(*(s32 *)((s32)a0 + 0x20) + 0x34));
    }

    *(s32 *)((s32)a0 + 0x1C) += 1;
    if ((*(s32 *)((s32)a0 + 0x1C) & 3) == 0) {
        if (((Cnt_8018E8A0 *)a0)->f[0x84] < 5) {
            ((Cnt_8018E8A0 *)a0)->f[0x84] = ((Cnt_8018E8A0 *)a0)->f[0x84] + 1;
        }
    }
}



extern void (*D_801DF89C[])(void);

void func_8018EBEC(void *a0) {
    D_801DF89C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_8018EC28(void *a0)
{
    s32 v0;
    s32 v1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, 0);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    func_8012B2CC((s32)a0);

    *(u16 *)((s32)a0 + 0x108) = 1;
    *(u16 *)((s32)a0 + 0x2) += 1;
}



extern void (*D_801E33D8[])(void);

void func_8018ECA8(void *a0) {
    D_801E33D8[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_8018F390(void);

void func_8018ECE4(void *a0) {

    extern s32 D_801E3130[];
    extern u8 D_801E30C8[];
    extern u8 D_8019105C[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801E30C8);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801E3130[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_8018F390);
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
        func_8012A828((s32)a0, D_8019105C);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_8018EDB8(void *a0) {
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


void func_8018EDE0(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_8018EDE8(void *a0) {

    extern s32 D_801E3314;
    extern s32 D_801E3300;
    extern s32 D_801E32FC;
    extern s32 D_801E3394;
    extern s32 D_801E3328;
    extern s32 D_801E31F4[];
    extern s32 D_801E3278[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801E3314 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801E32FC = 0;
                D_801E3300 = D_801E3278[v0];
            } else {
                D_801E3300 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801E3278[v0], 1);
                D_801E32FC = 2;
            }
        } else {
            D_801E3314 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801E32FC = 0;
            D_801E3300 = D_801E31F4[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801E3328);
    } else {
        p = &D_801E3394;
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
extern s32 func_8018F138(void);

void func_8018EF34(void *arg0) {

    extern s32 D_801E3130[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801E3130[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801E3130[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_8018F138() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



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




extern void func_80029124(s32, s32);

void func_8018F0A0(void *a0) {

    extern s32 D_801E3130[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801E3130[idx], 1);
}



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




extern s32 func_80029178(s32 arg);

s32 func_8018F138(void) {

    extern s32 D_801E3130[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801E3130[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801E3400[])(void);

void func_8018F19C(void *a0) {
    D_801E3400[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8018F1D8(void *a0) {

    extern u8 D_801E30FC[];
    extern u8 D_801E3AC0[];
    extern u8 D_801E38A0[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801E30FC) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801E3AC0);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801E38A0);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018F260(void *a0) {

    extern u8 D_801E38B0[];
    extern u8 D_801E39B8[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E38B0);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E39B8);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



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


extern s32 *D_80126B78;
extern u8 D_801E33F0[];
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

s32 aF8018A224() __asm__("func_8018F390");

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

    RotTransSV(D_801E33F0, sv0, &flag);
    RotTransSV(D_801E33F0 + 8, sv1, &flag);

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
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
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




extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8018FE20(s32 a0)
{
    extern Rec8_8018A390_8018FE94 D_801E47C4[];

    s32 i;

    for (i = 0; (s16)D_801E47C4[i].x != 0; i++) {
        func_8012C658(0x10D, i, a0);
    }
}



/* func_8018FE94 — allocates a GTE-projection slot, seeds a random spread
 * vector from a per-index table, rotates it by the model's Y angle, applies
 * it to the object's matrix, adds it to the object's position, and seeds
 * three random spin fields.  MATCH (136/136 ins), match_one standalone.
 *
 * Declarations: func_8012B23C / func_8012AD50 / D_801E47C4 / D_801E484C are
 * NOT declared anywhere else in this TU (whole-TU grep, D2) so they're fresh
 * here; func_8012C1B8 / func_8012CAE4 / func_8001C214 / ApplyMatrixSV ARE
 * already file-scope in the TU (L163, L3160-3162) with these EXACT
 * signatures, so re-declaring them identically merges silently (D3).
 *
 * §48 STRUCT ASSIGN: `m = D_800AE620;` on the 32-byte, 4-aligned matrix
 * routes move_by_pieces to the plain lw/lw/lw+sw/sw/sw grouping (no lwl/lwr).
 *
 * §48-C2: `sv = D_801E47C4[idx];` on the 8-byte, 2-aligned (u16 x,y,z; s16 w)
 * record struct falls through move_by_pieces' align>=4 test and emits the
 * lwl/lwr+swl/swr unaligned block-move pair instead — matches the target's
 * four unaligned loads/stores exactly.
 *
 * REGALLOC LEVER (new, byte-verified this session — candidate for the
 * cookbook): a redundant `void *s1 = a0;` local (never reassigned, used only
 * as an alias for the parameter) made gcc-2.7.2 split the parameter pseudo
 * into TWO allocnos — one for its pre-call uses (landing in $s0) and a
 * SEPARATE one (bridged by an extra `move`) for its post-call/cross-branch
 * uses (landing in $s1) — even though the target uses ONE register ($s1)
 * uniformly from the second prologue instruction on. Referencing the
 * parameter `a0` directly everywhere (no alias local) collapses this back to
 * a single allocno and fixed 6 of the 11 mismatches outright.
 *
 * The remaining 5 (an `addu $a0,$v0,zero` copy scheduled too EARLY, and the
 * alloc-check branch/store testing `$a0` instead of `$v0` directly) were a
 * v0-pseudo/call-arg-copy coalescing difference: gcc folded the store, the
 * branch test, AND the func_8012C1B8 return value into one $a0-homed pseudo.
 * Folding the store and the compare into ONE C expression —
 * `if ((*(s32*)(a0+0x20) = v0 = func_8012C1B8()) == 0)` — instead of two
 * separate statements (assign-then-test) made cc1 keep the store/test on the
 * call's native $v0 and defer the $a0 copy to just before its actual
 * consumer (func_8001C214), matching the target's schedule exactly. No
 * register pins, no permuter, no zero-byte asm barriers needed for either
 * residual — both C-lever-closeable (§136-class local-variable/expression-
 * shape levers).
 */
void func_8018FE94(void *a0)
{
          /* 32B, align 4 */
 /* 8B, align 2 */

    extern Mat32_8018A390_8018FE94 D_800AE620;
    extern Rec8_8018A390_8018FE94 D_801E47C4[];
    extern s32 D_801E484C[];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8012B23C(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern s32 rand(void);

    Mat32_8018A390_8018FE94 m;               /* sp+0x10 */
    Rec8_8018A390_8018FE94 sv;               /* sp+0x30 */
    void *mp;
    void *svp;
    s32 v0;
    s16 w;

    m = D_800AE620;
    sv = D_801E47C4[*(s16 *)((s32)a0 + 0x70)];

    mp = &m;
    svp = &sv;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    w = sv.w;
    func_8001C214(v0, D_801E484C[w]);

    RotMatrixY(*(s16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12), mp);

    ApplyMatrixSV(mp, svp, svp);

    *(u16 *)((s32)a0 + 0x6) += sv.x;
    *(u16 *)((s32)a0 + 0xA) += sv.y;
    *(u16 *)((s32)a0 + 0xE) += sv.z;
    func_8012B23C((s32)a0);

    *(s16 *)((s32)a0 + 0x12) = (s16)sv.x >> 3;
    *(s16 *)((s32)a0 + 0x16) = (s16)sv.y >> 3;
    *(s16 *)((s32)a0 + 0x1A) = (s16)sv.z >> 3;

    *(s16 *)((s32)a0 + 0xFC) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0xFE) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0x100) = (s16)((rand() & 0x7FF) - 0x400) >> w;

    func_8012AD50(a0);
}



extern void (*D_801E4858[])(void);

void func_801900B4(void *a0) {
    D_801E4858[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_801900F0(s32 a0) {
    u8 *s0;
    s16 val1;
    s16 val2;

    func_8012AD80(a0);
    s0 = (u8 *)a0;

    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x10) += *(u16 *)(s0 + 0xFC);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x12) += *(u16 *)(s0 + 0xFE);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x14) += *(u16 *)(s0 + 0x100);

    val1 = *(s16 *)(*(s32 *)(s0 + 0x64) + 0x0A);
    val2 = *(s16 *)(s0 + 0x0A);

    if (val2 > val1) {
        func_8012C218((void *)a0);
    }
}



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




s32 func_80190298(void *a0) {
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


void func_801902C0(void) {
}

extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801E8604;
    void func_801902C8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801E8604);
    }



extern s32 func_801789AC(s32);
extern void func_80178D18(void);

void func_801902F4(s32 a0) {
    if (((int (*)(void))func_801789AC)() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 2;
    }
}


extern u8 D_801E38B0[];
extern u8 D_801E39B8[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);

void func_80190334(void *a0) {

    extern u8 D_801E38B0[];
    extern u8 D_801E39B8[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0x100) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E38B0);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E39B8);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E38A0[];

void func_801903F4(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        if (*(s16 *)((s32)a0 + 0xFE) == 2) {
            func_8002D4C8(0x888, 0);
            func_8012A828((s32)a0, D_801E38A0);
        }
        *(s16 *)((s32)a0 + 0x2) = 5;
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


void func_80190460(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80190470(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }





s32 func_80190480(void) {

    extern s32 D_801EB924;
    return !(D_801EB924 ^ 1);
}


extern void func_800296F8(void);
    s32 func_80190498(s32 arg0) {
        ((void (*)(s32))func_800296F8)(*(s32 *)(arg0 + 0xdc));
    }


#include "common.h"

extern s32 *D_80126B78;
extern u8 D_801E8670[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();
extern void RotTransSV(void *a0, void *a1, void *a2);

/* local copy of src/shared/engine_types.h's MATRIX (short m[3][3]; long t[3];) --
 * common.h does not pull in engine_types.h, so declare it locally rather than
 * touching the shared header. */


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

/* §71 sibling: identical shape to func_8018F390 (same TU, this file, D_80126B78/RotTransSV/
 * func_80135888/func_8012BDBC/func_80178BF8/func_80172710 idiom) already MATCHED -- only the
 * per-overlay data symbol (D_801E8670 vs D_801E33F0) differs. §37 asm-label alias avoids the
 * `conflicting types` clash with the fleet's `extern void func_801904BC(void);` used elsewhere
 * in this TU as a state-handler function pointer. */

s32 aF801904E0() __asm__("func_801904BC");

s32 aF801904E0(param_1)
    void *param_1;
{
    MATRIX m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    obj = *(s32 *)((s32)param_1 + 0x64);
    m = *(MATRIX *)((u8 *)D_80126B78 + 0x34);

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);

    RotTransSV(D_801E8670, sv0, &flag);
    RotTransSV(D_801E8670 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x20),
                       *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58),
                       (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_801E86CC[])(void);

void func_80190610(void *a0) {
    D_801E86CC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80190B6C(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80190BC4(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8019064C(s32 a0) {
    extern u8 D_801E8680[];
    extern u8 D_801E868C[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_80190B6C(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801E8680, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801E868C);
        func_80190BC4(a0);
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
extern void func_80190BC4(s32 arg0);
extern void func_80190C40(void *arg0);

void func_80190748(s32 arg0) {
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
            func_80190BC4(arg0);
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
    func_80190C40((void *)arg0);
}


extern u16 D_800B99DA;

extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80190BC4(s32 arg0);
extern void func_80190C40(void *arg0);

void func_801909D8(s32 arg0) {
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
        func_80190BC4(arg0);
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
    func_80190C40((void *)arg0);
}


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
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

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





