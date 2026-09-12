#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8();                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */
/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
struct S;
struct Obj;
   /* 12-byte sub-table record (stride 0xC) */
 /* 0x20 bytes */
                /* 4 + 16*12 = 0xC4 stride */
                 /* 0x08 */
     /* 0x20 */
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
typedef void (*Handler)(struct Entry *);
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80189054;
extern u8 D_80188FC4;
extern u8 D_80188FA0;
extern u8 D_80188F7C;
extern u8 D_80189030;
extern u8 D_8018900C;
extern u8 D_80188FE8;
extern u8 D_80188F58;
extern void func_80145934(void);
extern u8 D_801890E4;
extern u8 D_801890C0;
extern u8 D_8018909C;
extern u8 D_80189078;
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
extern unsigned char D_801884DC[];
extern unsigned char D_8018850C[];
extern unsigned char D_8018855C[];
extern unsigned char D_8018858C[];
extern unsigned char D_801885BC[];
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
extern void (*D_8018860C[])(void *);
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
extern u8 func_80014DC0(u32 a0);
extern u16 func_80014D68(u32 a0);
extern s32 func_80014D94(s32 a0);
extern u8 func_80014CF8(u32 a0, u32 a1);
extern void func_800120DC(u16 *arg0, u16 *arg1);
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
extern s32 D_801151D4;
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
extern u8 D_80126C01;
extern u16 D_80126C02;
extern u16 D_80126C06;
extern s32 D_80188654[];
extern s32 func_80148D44(void);
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
extern void func_801577C8(s32 arg0);
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
extern s32 D_801886D4[];
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
extern u8 D_8018875C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188764;
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
extern struct Packed8 D_80126C98;
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
s32 func_80135888(s32, s32, M2C_UNK, M2C_UNK);      /* extern */
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
extern int D_801D9618;
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
extern s32 D_801D961C;
extern void func_8014FA04(s32 a0);
extern int func_8014FBC0(void);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern void func_8014FCFC(void);
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
extern s32 D_80188794;
extern s32 D_80126990;
extern s32 D_80126994;
extern u8 D_80126948[];
extern s32 func_80021174(s32 a0, s32 a1);
extern s32 func_8015094C(s32 param_1);
extern void (*D_80188798[])(void);
extern void func_80150B28(int param_1);
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
extern void (*D_8018883C[])(void *);
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
extern void (*D_80188860[])(void *);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188850;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188874[])(void *);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188880[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80188890[])(void *);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801888A8[])(void *);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80188898;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801888BC[])(void *);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801888D8[])(void *);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801888C8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801888EC[])(void *);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188900[])(void *);
extern void func_80153320(void *a0);
extern void func_801533A4(s32 a0);
extern void func_8015335C(s32 a0);
extern void func_80153410(s32 *a0);
extern void func_80153490(s32 a0);
extern void func_80153550(s32 a0);
extern void func_801534D8(s32 *a0);
void func_8014ED28(s32 a0);
void func_80146D90(s32 a0);
void func_8014CC28(s32 a0);
void func_8014FA04(s32 a0);
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
extern s32 D_80188914;
extern void (*D_8018893C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018891C;
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
void func_80154C24(s32 a0, s32 *a1, s32 *a2);
void func_80154F9C(s32 a0);
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
extern int (*D_80188988[])(void);
extern s32 func_80155458(s32 param_1);
s32 func_800D02D0(u8);                              /* extern */
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018898C[])(void *);
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
extern s32 func_80161208(void);
void func_80155E30(void *a0);
extern void func_80155E30(void *a0);
extern s32 func_80161208();
extern void func_80155EA4(void *arg0);
extern void func_80155F58(void);
extern s32 func_80155F80();
extern s32 func_80155F60(void);
extern s32 func_80155F80(s32 a0);
extern int func_80155FB0(int arg, int a1);
extern int func_80155FD4(int arg, int a1);
extern void func_80156044(int param_1, int param_2);
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern s32 rand(void);
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern S801563EC * func_801563EC(u16 idx);
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
extern void func_80013E94(void *a0, void *a1);
extern void func_80156A1C(s32 a0, s32 a1);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80188DF0[];
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
extern void (*D_80188E00[])(void *);
extern void func_8014CC28(s32 a0);      /* defined  */
extern s32 func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
extern void func_80157580(s32 arg0);
extern u8 D_800D4F14[];
extern void func_801599A4(void *a0);   /* canonical: void(*)(void *) */
extern void func_80159B3C(void *a0);   /* canonical: void(*)(void *) */
extern s32 func_80161208(void);        /* canonical: s32(*)(void) — call-site cast to pass arg0 */
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern int D_801D9650;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188E28[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188E08;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188E18;
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
extern void (*D_80188E68[])(void *);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188E70[])(void *);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188E3C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188E7C[])(void *);
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
extern u8 D_80188E4C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D9658;
extern s32 D_801D9664;
extern s32 D_801D9668;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188EB8[])(s32 *);
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
extern s32 D_80188E8C[];
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
extern s32 D_801D9660;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80189108[])(void *);
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
extern char D_80188F28[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801891AC[])(void *);
extern void (*D_801891B8[])(void *);
extern void func_80159A20(unsigned char *param_1);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189300[])(void *);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018911C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189308[])(void *);
extern void func_8015A2A0(s32 a0);
extern int D_8018912C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018914C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189310[])(void *);
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
extern void (*D_8018932C[])(void);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015AE2C(s32 arg0);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_80189338[])(void *);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189344[])(void *);
extern void func_8015C788(s32);
extern void func_8015C750(s32 a0);
extern void func_80161240(void *a0);
extern void func_80161C24(s32, s32);
extern void (*D_801891B8[])();
extern void func_8015C944(int param_1);
extern void func_8015CB94(s32 a0);
extern void func_8015CBCC(void);
extern void func_8015CBD4(void);
extern void func_8015CBDC(void);
extern void func_8015CBE4(void);
extern void func_8015CBEC(void);
extern void func_8015CBF4(void);
extern void func_8015CBFC(void);
extern void func_8015CC04(void);
void func_80147078(s32 *a0, s16 a1);
s32 func_8015CCD0();
extern void func_8015CC0C(s32 *param_1);
extern void func_8015CC74(s32 *a0);
extern void func_8015CC40(s32 *a0);
extern void (*D_80189354[])(void);
extern void func_8015CC74(s32 * a0);
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C(int param_1);
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void (*D_8018938C[])(void);
extern void func_8015CFC0(s32 * a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801893E8;
extern void func_8015D380(s32 a0);
extern unsigned char D_801884CC[];
extern void func_8015D414(int param_1);
extern void func_8015D57C(s32);
extern void func_8015D480(s32 *a0);
extern s32 func_8015D4E8(s16 *a0);
extern void func_8015D4B4(s16 *a0);
extern s32 (*D_801893F0[])();
extern void func_8015D524(s32 arg0);
extern void func_8015D544(s32 a0);
extern void func_801746DC(void);
extern void func_8015D57C(s32 arg0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154150(int, int);
extern void func_80149374(int, int);
extern unsigned char D_801893FC[];
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
extern s8 D_80189438[];
extern void func_8015DCB8(s32 param_1);
s32 func_80029AAC();
extern int func_8015DD74(int arg0);
extern void func_8015DECC(s32 a0);
extern void func_8015DDF0(s32 *a0);
extern void func_8015DE58(s32 *a0);
extern void (*D_80189450[])(void);
extern void func_8015DE58(s32 * param_1);
extern void func_8015DECC(s32);
extern void func_8015DE94(s32 a0);
extern void func_8015E018(s32 a0);
extern void func_8015DF34(void *arg0);
extern int func_8015DFE4(int a0);
extern void func_8015E018(s32 param_1);
void func_8014C1A0(s32 arg0, s32 arg1);
void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC(void);
void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern int func_8015E0D4(int a0);
extern void func_8015E22C(s32 a0);
extern void func_8015E150(s32 *a0);
extern s32 func_8015E1B8(s32 a0);
extern void func_8015E184(s32 *arg0);
extern void (*D_80189470[])(void);
extern s32 func_8015E1B8(s32 param_1);
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
extern u16 D_80189480;
extern u16 D_80189482;
extern u16 D_80189484;
extern s32 D_80189488;
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189490;
extern void func_8015E5B0(u8 *self);
extern void func_8015E714(s32 *a0);
extern void func_8015E95C(s32);
extern void func_8015E84C(s32 *a0);
extern void func_8015E8E8(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void (*D_801894A4[])(void);
extern void func_8015E8E8(s32 * param_1);
extern void func_8015E924(s32 a0);
extern void func_8015E95C(s32 a0);
extern s16 D_801152A0;
extern void func_80160818(s32 *a0);
extern void func_8015ED6C(s32 *a0);
extern void func_8015EE7C(s32);
extern void func_8015EDA0(s32 *a0);
extern s32 func_8015EE08(s32 a0);
extern void func_8015EDD4(s32 *arg0);
extern void (*D_801894AC[])(void);
extern void func_8015EE44(s32 a0);
extern int D_800D4C48;
extern int D_8018919C;
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C(s32 *a0);
extern void func_8015EFD8(s32 *a0);
extern void (*D_801894B4[])(void);
extern void func_8015F00C(s32 * param_1);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
extern s32 D_80062BE8;
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void (*D_801894BC[])(void);
extern void func_8015F324(s32 * a0);
extern void func_8015F360(void);
extern s32 func_801725B8(u8 *a0);
extern void func_8015F380(void* arg0);
extern void func_8015F738(s32 *a0);
extern void func_8015F848(s32 *a0);
extern void func_8015F76C(s32 *a0);
extern s32 func_8015F7D4(s32 a0);
extern void func_8015F7A0(s32 *arg0);
extern void (*D_801894F4[])(void);
extern s32 func_8015F7D4(s32 param_1);
extern void func_8015F810(s32 *a0);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern void func_8015F89C(void *arg0);
void func_80154150(s32 a0, s32 a1);
void func_80154A74(s32 a0, s32 a1);
void func_80146C98(s32 *a0, s16 a1);
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
extern unsigned int D_80189514[];
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
extern void (*D_80189590[])(void *);
extern void func_80160138(s32 * a0);
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
extern void (*D_801895A8[])(void *);
extern void func_8016084C(s32 * a0);
extern void func_80160888(s32 *a0);
extern void func_80160A28(s32 a0);
extern void func_80160A74(s32 *a0);
extern void func_80160BB4(s32 *a0);
extern void func_80160ACC(s32 *a0);
extern s32 func_80160B34(s32 a0);
extern void func_80160B00(s32 *arg0);
extern void (*D_801895B4[])(void);
extern void func_80160B70(s32 a0);
extern void func_80160C28(void *arg0);
extern void func_80160CB4(s32 *a0);
extern void func_80160D10(void *arg0);
extern void func_80160DEC(u8 *a0);
extern void func_80160F00();
extern void func_80160E3C(s32 *a0);
extern void func_80160EA4(int param_1);
extern void func_80160E70(s32 *a0);
extern void func_80160EA4(int param_1);
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
extern u16 D_801895F4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189658;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D9670[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018967C[])(void);
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
extern int D_801D96C8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
extern void (*D_801896C0[])(void);   /* word-stride table of dispatch fn pointers */
extern void func_801627E8(void);
extern void (*D_801896C4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801896B4;
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
extern char D_801D8BB0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801896CC[])(void);
extern void func_80163A58(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 D_800DE5A0;
extern s32 D_800636C8;
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418();
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void (*D_80189720[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801896E8;
extern u16 D_8018971C;
extern s16 D_8018971A;
extern s16 D_80189718;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018972C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D9728;
extern u8 D_801D9729;
extern u8 D_801D972A;
extern u8 D_801D972B;
extern u8 D_801D972C;
extern u8 D_801D972D;
extern u8 D_801D972E;
extern u8 D_801D972F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern s32 (*D_8018973C[])();
extern s32 func_80164EA4(s16 *a0);
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
extern s32 D_801D9768;
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
extern void (*D_80189780[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801897FC[];
extern s32 D_8018981C[];
extern u8 D_80189898[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801898B8[];
extern u8 D_801898D8[];
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
extern s32 (*D_801898F8[])();
extern void func_80165A18(void);
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void (*D_80189974[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801899F0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern s32 D_80126728;
extern void func_80165CA0(void);
M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D8BC0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*D_801899FC[])();
extern s32 func_80166018(s16 *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern s32 (*D_80189A04[])();
extern s32 func_801663FC(s16 *a0);
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
extern s32 (*D_80189ACC[])();
extern s32 func_80166618(s16 *a0);
extern s32 (*D_80189ADC[])();
extern s32 func_80166654(s16 *a0);
extern s32 func_80017758(void *a0, void *a1);
extern u8 D_801D97E8[];
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern s32 (*D_80189AEC[])();
extern s32 func_801678B4(s16 *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern s32 (*D_80189AF8[])();
extern s32 func_80167A9C(s16 *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189A58[];
extern u8   D_80189A6C[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80189AB0[];
extern u8 D_80189A80[];
extern u8 D_80189A81[];
extern void func_801681FC(s32 param_1);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern void func_8016829C(s32 a0);
extern s32 func_80166690(s32 a0, s32 a1);
extern void func_80168328(s32 arg0);
s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
s32 func_80166690(s32 a0, s32 a1);
extern void func_801683D8(s32 a0);
extern u8 D_80189ABC[];
extern u8 D_80189A94[];
extern u8 D_80189A95[];
extern void func_80168430(s32 param_1);
extern void func_801684B4(s32 a0);
extern void func_80168540(s32 a0);
extern void func_801685EC(s32 a0);
extern void func_80168640(s32 a0);
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern s32 (*D_80189B10[])();
extern s32 func_80168744(s16 *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern s32 (*D_80189B18[])();
extern s32 func_801689D8(s16 *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern s32 (*D_80189B20[])();
extern s32 func_80168AA8(s16 *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 (*D_80189B28[])();
extern s32 func_80168D58(s16 *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern s32 func_80016A5C();
extern void func_80168F40(void *arg0);
extern s32 func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228();
extern void func_801691B8(void *a0);
extern void (*D_80189B38[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189B40[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189BF4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189BFC[])(void);
extern void func_80169F00(void *a0);
extern char D_80189BAC[];
extern char D_80189B6C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189C34[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80189C40[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80189C88[])(void);
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
extern void (*D_80189D04[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D9A88;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80189CF8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189D3C[];
extern unsigned short D_80189D44[];
extern unsigned short D_80189D4C[];
extern unsigned char D_801D9A90[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D9A88;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189D54[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
M2C_UNK func_8016BF50();                            /* extern */
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D9BC4;
extern M2C_UNK D_801D9BC8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D9B50;
extern void (*D_80189D84[])(void);
extern void func_8016C14C(void *a0);
extern void func_8016C188(s32 param);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D9BCC[];
extern u8 D_801D9BD4[];
extern u8 D_801D9B84[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189D8C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189DA8[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189DB0[])(void);
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
extern void (*D_80189E18[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189DBC;
extern u8 D_80189DC8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern s16  D_801DA2C0;
extern s16  D_801DA2C4;
extern s32  D_80189E20;
extern s32  D_80189E2C;
extern s32 func_8016DC20(s32 param_1);
extern void (*D_80189E4C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189E54[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016DF5C(s32 param_1);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189EA8[])(void);
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
extern u16 D_80189EDC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189ECC[];
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
extern s32 func_8016EFC8();
extern s32 func_8016EFA8(s32 a0);
extern void func_8016F094(s32 *a0);
extern s32 func_8016F0AC();
extern s32 D_80189EF8;
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
extern void (*D_80189F70[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189F78[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189F80[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189F88[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189F90[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189F98[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189FA4[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189FB0[])(void);
extern void func_8016FC90(u8 *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189FBC[])(void);
extern void func_8016FDB4(u8 *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189FCC[])(void);
extern void func_8016FF30(u8 *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189FDC[])(void);
extern void func_8016FFDC(u8 *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189FE4[])(void);
extern void func_80170150(u8 *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189FEC[])(void);
extern void func_80170240(u8 *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189FF4[])(void);
extern void func_801702FC(u8 *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189FFC[])(void);
extern void func_801703E0(u8 *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018A004[])(void);
extern void func_801704B0(u8 *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018A00C[])(void);
extern void func_80170548(u8 *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018A014[])(void);
extern void func_801705F8(u8 *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018A01C[])(void);
extern void func_801706AC(u8 *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018A024[])(void *);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018A02C[])(void *);
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
extern void (*D_8018A034[])(void *);
extern void func_80170B14(int a0);
void func_8014706C(void *a0);
void func_80154274(s32 *a0, s32 a1);
s32 func_80171990(u8 *a0);
void func_80170B90(u8 *a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018A03C[])(void *);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018A044[])(void *);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018A04C[])(void *);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018A054[])(void *);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018A05C[])(void *);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018A064[])(void *);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018A06C[])(void *);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018A074[])(void *);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018A07C[])(void *);
extern void func_801711C0(void *a0);
void func_801719A4(int a0, int a1);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern s32 (*D_8018A084[])(void *);
extern s32 func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern s32 (*D_8018A08C[])(void *);
extern s32 func_801714E4(void *a0);
extern struct B16 D_800A5E88;
extern struct B16 D_800A5E98;
extern struct B16 D_800A5EA8;
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
extern s32  ratan2(s32 a0, s32 a1);   /* ratan2 */
extern void func_80172170(s32 a0, s32 a1);
extern s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_801722CC(s32 *a0);
extern void func_80172304(s32 *a0);
extern void func_80172310(u8 *a0);
extern void func_801723C4(s32 param_1, s32 param_2);
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
extern s32 (*D_8018A09C[])(void *);
extern void func_80172844(u8 *a0);
extern void func_8017280C(u8 *a0);
extern void func_8017288C(void);
extern s32 func_801728E4(void *a0);
extern void func_80172894(void *a0);
extern s32 (*D_8018A0A8[])(void *);
extern void func_80172958(u8 *a0);
extern void func_80172920(u8 *a0);
extern s16 D_80126B36;
extern void func_80172958(u8 * a0);
extern void func_801729A8(void);
extern s32 func_801729F0(void *a0);
extern s16 D_80126B34;
extern s16 D_80126B32;
extern void func_801729B0(s32 a0);
extern s32 (*D_8018A0B4[])(void *);
extern void func_80172A8C(void *a0);
extern void func_80172A2C(int param_1);
extern void func_80172ACC(u8 *a0);
extern void func_80172B0C(void);
extern s32 func_80172B44(void *a0);
extern void func_80172B14(s16 a0);
extern s32 (*D_8018A0C4[])(void *);
extern s32 D_801150F8;
extern void func_80172BC8(void *a0);
extern void func_80172B80(u8 *a0);
extern void func_80172C48(void);
extern s32 (*D_8018A0D0[])(void *);
extern s32 func_80172CA0(void *a0);
extern void func_80172D14(u8 *a0);
extern void func_80172CDC(u8 *a0);
extern void func_80172D14(u8 * a0);
extern void func_80172D60(void);
extern s32 D_80127508;
extern s32 func_80172DAC(void *a0);
extern void func_80172D68(s32 a0);
extern s32 (*D_8018A0DC[])(void *);
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
extern s32 (*D_8018A0E8[])(void *);
extern void func_801730FC(struct S801730FC *a0);
extern void func_801730B4(s32 a0);
extern void func_8017316C(void);
extern s32 func_8017319C(void *a0);
extern void func_80173174(void);
extern s32 (*D_8018A0F4[])(void *);
extern u8 D_800D5AA0[];
extern void func_80173220(void *a0);
extern void func_801731D8(s32 *a0);
extern M2C_UNK D_8018A094;
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
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
/* ==== end §8b carried decl layer ==== */

void func_80174684(void *);

#include "../shared/ov/func_801734BC__t834cdd6a.h"


extern s32 (*D_8018A100[])(void *);

s32 func_80173544(void *a0) {
    return D_8018A100[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80173580.h"

#include "../shared/ov/func_801735B8.h"

extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B40;
extern s16 D_80126B32;

#include "../shared/ov/func_801735EC.h"

#include "../shared/ov/func_80173648.h"

#include "../shared/ov/func_801736A8.h"

#include "../shared/ov/func_801736B0.h"

extern s32 (*D_8018A114[])(void *);

s32 func_801736FC(void *a0) {
    return D_8018A114[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80173738.h"

#include "../shared/ov/func_80173770.h"

#include "../shared/ov/func_801737B0.h"

extern s16 D_80126B30;
extern s32 func_801737E8(void *a0);
extern void func_80174684(void *);

#include "../shared/ov/func_801737B8.h"

extern s32 (*D_8018A120[])(void *);

s32 func_801737E8(void *a0) {
    return D_8018A120[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80173824.h"

/* func_8017385C — overlay ov_SC01_077 shared core */
#include "../shared/ov/func_8017385C.h"

#include "../shared/ov/func_801738D4.h"

extern s16 D_80126B30;
extern s32 func_8017390C(void *a0);
extern void func_80174684(void *);

#include "../shared/ov/func_801738DC.h"

extern s32 (*D_8018A12C[])(void *);

s32 func_8017390C(void *a0) {
    return D_8018A12C[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80173948.h"

#include "../shared/ov/func_80173980.h"

#include "../shared/ov/func_801739D8.h"

#include "../shared/ov/func_80173A20.h"

#include "../shared/ov/func_80173A28.h"

extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern s32 D_80126B58;
extern s32 D_80127508;
extern s16 D_80126B30;
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3A;
extern s16 D_80126B3C;
extern s16 D_8011F9C8;
extern s16 D_80126938;
extern s32 D_8012750C;
extern s32 func_80173B4C(void*);

void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5)
{
    s32 *s1 = &D_80126B58;
    s32 v0;

    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }

    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}


extern s32 (*D_8018A13C[])(void *);

s32 func_80173B4C(void *a0) {
    return D_8018A13C[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80173B88.h"

#include "../shared/ov/func_80173BC0.h"


#include "../shared/ov/func_80173C64.h"

#include "../shared/ov/func_80173CB4.h"


// @class: schedule
// @unstuck(P36): none — MATCH (55 ins). Levers: pin param_1->$s0 ($16) + a register ptr &D_80127508->$s1 ($17)
//   kept across the first block (reused for the !=0 test and the +4 arg); func_801399F0(*(s0+0x198))
//   reuses the outer-test $a0 load as its arg; and DUPLICATE func_80154274()+func_80171A1C() into BOTH
//   if/else arms (don't factor to a shared tail) -- gcc cross-jump-merges the two jals+epilogue but keeps
//   each arm's arg-setup, because the *(s0+0x198)=0 store lands in the !=0 arm's `j` delay slot and breaks
//   the suffix identity right before the merge point.

#include "../shared/ov/func_80173E1C.h"

// @class: other
// @unstuck(P36): switch dispatch tree — verifying gcc -O2 emits 0x79-first balanced tree

#include "../shared/ov/func_80173EF8.h"

extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);

#include "../shared/ov/func_80174158.h"

#include "../shared/ov/func_80174188.h"

// @class: plumbing
// @unstuck(P36): none — MATCH (3 jal stubs + two 0xA00000 global stores reusing one lui)

#include "../shared/ov/func_801741A8.h"

#include "../shared/ov/func_801741EC.h"

#include "../shared/ov/func_80174274.h"

#include "../shared/ov/func_8017427C.h"

extern s32 (*D_8018A15C[])(void *);

s32 func_801742A4(void *a0) {
    return D_8018A15C[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_801742E0.h"

#include "../shared/ov/func_80174318.h"

#include "../shared/ov/func_80174354.h"

#include "../shared/ov/func_8017435C.h"

extern s32 (*D_8018A168[])(void *);

s32 func_80174384(void *a0) {
    return D_8018A168[*(u8 *)((s32)a0 + 0x214)](a0);
}

extern void func_80171A1C(u8 *a0);
extern void func_801743F0(u8 *a0);

#include "../shared/ov/func_801743C0.h"

#include "../shared/ov/func_801743F0.h"

#include "../shared/ov/func_80174430.h"

#include "../shared/ov/func_80174438.h"

extern s32 (*D_8018A174[])(void *);

s32 func_80174474(void *a0) {
    return D_8018A174[*(u8 *)((s32)a0 + 0x214)](a0);
}

extern void func_80171A1C(u8 *a0);
extern void func_801744E0(u8 *a0);

#include "../shared/ov/func_801744B0.h"

#include "../shared/ov/func_801744E0.h"

#include "../shared/ov/func_80174524.h"

#include "../shared/ov/func_8017452C.h"

#include "../shared/ov/func_80174554.h"

#include "../shared/ov/func_80174584.h"

#include "../shared/ov/func_801745AC.h"

#include "../shared/ov/func_801745DC.h"

#include "../shared/ov/func_80174604.h"

#include "../shared/ov/func_80174630.h"

#include "../shared/ov/func_80174650.h"

#include "../shared/ov/func_80174674.h"

#include "../shared/ov/func_80174684.h"


// @class: plumbing
// @unstuck(P36): none — MATCH (straight stub: two calls, fn-ptr args + 0x1000000 immediate)

#include "../shared/ov/func_801746A4.h"

#include "../shared/ov/func_801746DC.h"

#include "../shared/ov/func_80174714.h"

#include "../shared/ov/func_80174754.h"

#include "../shared/ov/func_80174764.h"

#include "../shared/ov/func_80174774.h"

#include "../shared/ov/func_80174784.h"

#include "../shared/ov/func_801747AC.h"

extern s32 (*D_8018A180[])(void *);

s32 func_801747CC(void *a0) {
    return D_8018A180[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_80174808.h"

#include "../shared/ov/func_8017481C.h"

#include "../shared/ov/func_80174824.h"

#include "../shared/ov/func_8017484C.h"

extern s32 (*D_8018A188[])(void *);

s32 func_80174888(void *a0) {
    return D_8018A188[*(u8 *)((s32)a0 + 0x214)](a0);
}

#include "../shared/ov/func_801748C4.h"

#include "../shared/ov/func_801748E4.h"

#include "../shared/ov/func_801748EC.h"

extern s32 (*D_8018A190[])(void *);

s32 func_8017496C(void *a0) {
    return D_8018A190[*(u8 *)((s32)a0 + 0x4)](a0);
}

#include "../shared/ov/func_801749A8.h"

// @class: schedule
// @unstuck(P36): none — MATCH (105 ins). Keys: (1) single-buffer struct for the func_80049CAC/func_8012F14C
//   out-params (local_2c..local_14 are fields of ONE stack buffer, not separate scalars — else gcc
//   DCEs the unread ones + overlaps the buffer -> wrong 0x40 frame); (2) $s2/$s1 pins for iVar5/iVar4
//   (call-crossing saved regs); (3) load D_80126B66 as RAW u16 (lhu) with (s16) sext at each USE —
//   this defeats gcc's lhu+sext->lh combine fold so the target's lhu+sll+sra reappears; (4) inline
//   `iVar5 = (s16)D_80126B5E` into the f48 expression so the f28 operand load schedules first.

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s16 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);


s32 func_801749C8(s32 param_1)
{
    Buf_c1 buf;
    s32 iVar5;
    u32 iVar4;

    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    iVar4 = (u16)D_80126B66;
    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + (iVar5 = (s16)D_80126B5E);
    *(s32 *)(param_1 + 0x4c) = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    func_80049CAC(param_1 + 0x18, (s32)&buf);

    buf.f14 = *(s16 *)(param_1 + 0x28) + iVar5;
    buf.f18 = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    buf.f1c = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    buf.f20 = 0;
    buf.f22 = 0;
    buf.f24 = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&buf, (s32)&buf.f20, (s32)&buf.f28);

    *(s32 *)(param_1 + 0x3c) = buf.f28;
    *(s32 *)(param_1 + 0x40) = buf.f2a;
    *(s32 *)(param_1 + 0x44) = buf.f2c;
}

#include "../shared/ov/func_80174B6C.h"

#include "../shared/ov/func_80174BBC.h"

// @class: struct
// @unstuck(P36): none — MATCH (27 ins) via func-ptr array fold extern void(*D_8018A194[])()

extern void (*D_8018A194[])();

void func_80174BF4(void * arg0)
{
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_8018A194[M2C_FIELD(arg0, u8 *, 4)]();
}

#include "../shared/ov/func_80174C60.h"

extern s32 func_80174CB0(s32, s32);

#include "../shared/ov/func_80174C80.h"

extern s16 func_80012ABC(s32, s32, s32);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80013F3C(s32 a0);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
s32 func_80174CB0(s32 param_1, s32 param_2)
{

    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;
    s16 *pv = &D_80126940;
    MATRIX mtx;
    SVECTOR vec;
    SVECTOR out;
    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);
    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)*pv;
    *(s32 *)(param_1 + 0x4c) = (s32)*(s16 *)(param_1 + 0x2a) + (s32)D_80126942;
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2c) + (s32)D_80126944;
    func_80013F3C((s32)&mtx);
    func_800123F0((s32)&mtx, (s32)*(s16 *)(param_1 + 0x1c));
    func_80012558((s32)&mtx, ((s32)*(s16 *)(param_1 + 0x1a) + (s32)(s16)param_2) & 0xFFF);
    func_800126C4((s32)&mtx, (s32)*(s16 *)(param_1 + 0x18));
    mtx.t[0] = (s32)*(s16 *)(param_1 + 0x28) + (s32)*pv;
    mtx.t[1] = (s32)*(s16 *)(param_1 + 0x2a) + (s32)D_80126942;
    mtx.t[2] = (s32)*(s16 *)(param_1 + 0x2c) + (s32)D_80126944;
    vec.vx = 0;
    vec.vy = 0;
    vec.vz = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&mtx, (s32)&vec, (s32)&out);
    *(s32 *)(param_1 + 0x3c) = (s32)out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)out.vz;
}


#include "../shared/ov/func_80174E9C.h"

#include "../shared/ov/func_80174ED4.h"

#include "../shared/ov/func_80174EF0.h"

extern s32 (*D_8018A19C[])(void *);

s32 func_80174F28(void *a0) {
    return D_8018A19C[*(u8 *)((s32)a0 + 0x4)](a0);
}

#include "../shared/ov/func_80174F64.h"

#include "../shared/ov/func_80174FBC.h"

#include "../shared/ov/func_80175014.h"

#include "../shared/ov/func_8017509C.h"

#include "../shared/ov/func_80175114.h"

#include "../shared/ov/func_80175150.h"

extern void (*D_8018A1A4[])(void*);
extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_8018A1A4[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}

#include "../shared/ov/func_801751D8.h"

// @class: struct
// @unstuck(P36): none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern u8 D_80078EC0;
extern void (*D_8018A1AC[])(s32);
extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{
    s32 i = D_80078EC0 - 1;

    D_8018A1AC[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}

// @class: struct
// @unstuck(P36): none — MATCH
//
// Indexed fn-ptr table call. Writing D_8018A1C4[D_80078EC0 - 1]() lets gcc reassociate
// (x-1)*4 -> x*4 - 4 and fold the -4 into the lw displacement (lw -4($at)), dropping the
// `addiu -1`. The target keeps `addiu $v0,$v0,-1; sll $v0,2` separate then folds %lo at
// offset 0. The fix: integer address arithmetic with an explicit << 2 on (x-1):
//   (s32)base + ((x - 1) << 2)  -> keeps (x-1) live in the index reg, folds %lo(base) into lw.

#include "common.h"

extern u8 D_80078EC0;
extern VoidFn D_8018A1C4[];

s32 func_80175268(s32 param_1)
{
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_8018A1C4 + ((D_80078EC0 - 1) << 2)))();
}

#include "../shared/ov/func_801752BC.h"

#include "../shared/ov/func_80175308.h"

// @class: remat
// @unstuck(P36): none — MATCH
#include "../shared/ov/func_80175414.h"

#include "../shared/ov/func_80175454.h"

#include "../shared/ov/func_80175494.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (37 ins, relocation-masked proxy)



extern s32 func_80029504(void);
extern u8 D_8011F7A8;
extern unsigned char D_800B9A13;
extern s32 D_80126B9C;
extern DispatchFn D_8018A308[];

void func_801754A8(void) {
    u8 *p = &D_8011F7A8;
    s32 r = func_80029504();
    s32 flag = 0;

    if (((D_800B9A13 == 0) && ((D_80126B9C & 0x80) == 0)) ||
        (0x4AF < (u32)(r - 10))) {
        flag = 1;
    }
    p[9] = flag;
    D_8018A308[p[0]]((void *)p);
}


// @class: struct
// @unstuck(P36): none — MATCH expected. fn-ptr-table dispatch: byte at param+1 indexes D_8018A314[] declared extern void(*[])() so %lo folds into the lw of the fn-ptr; dispatched call takes no args (no $a0 setup before jalr), then three plain jal tail calls.
#include "common.h"

extern void (*D_8018A314[])();
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {
    D_8018A314[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}

#include "../shared/ov/func_80175590.h"

#include "../shared/ov/func_80175624.h"

#include "../shared/ov/func_80175668.h"

// @class: struct
// @unstuck(P36): none — MATCH expected (indexed fn-ptr-table call + 3 direct calls; mirrors byte-matched func_80130D0C)

extern void (*D_8018A320[])(void);
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(void *a0) {
    D_8018A320[*(u8 *)((s32)a0 + 1)]();
    func_801758FC();
    func_80175820();
    func_801759D8();
}

#include "../shared/ov/func_801756E4.h"

#include "../shared/ov/func_80175798.h"

#include "../shared/ov/func_801757A0.h"

#include "../shared/ov/func_801757E0.h"

#include "common.h"

/* func_80175820 — twin of the byte-matched func_801759D8 / func_801758FC in this same TU
 * (ov_SC01_077_jr_801734BC).  Same three-part body, different slot:
 *   part 1 tag word = ptr[2]        (0x8 vs 0x4 / 0xC)
 *   part 2 head ptr = D_8011F7A8+0x18 (== D_8011F7C0)
 *   part 3 tail ptr = D_8011F7A8+0x20 (== D_8011F7C8)
 * The two __asm__ memory fences are what keep the three parts from CSE-ing their
 * base addresses together (parts 1/2 stay absolute lui/%lo + idx*4; part 3 keeps the
 * shared `la $v1,D_8011F7A8` + 0x18/0x20 displacements).
 */

   /* size 0x14 */
    /* size 0x0C */

#include "../shared/ov/func_80175820.h"


#include "../shared/ov/func_801758FC.h"



   /* size 0x14 */
    /* size 0x0C */

#include "../shared/ov/func_801759D8.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (188/188), symcheck SYMS-OK (22 symbols)
//
// func_80175AB8 — ov_SC01_077 h_seq exemplar (188 ins, ×138 members).
// Zero file-scope footprint (§28/§43): typedef + every extern is block-scoped so the body
// lifts as one unit for dedup_propagate / family_sweep.
//
// FOUR byte-proven levers found here (all newly measured this session, closeness 15 -> 0):
//
//  L1  base-pointer opacity WITHOUT killing the birthing boost (sched.c birthing_insn_p).
//      $s2 must hold &D_8011F7F0 while `arr = base - 0x48` stays a SEPARATE addiu, so the
//      symbol must not constant-fold.  The obvious fence `__asm__("" : "=r"(base) : "0"(base))`
//      works but sets `base` TWICE => reg_n_sets[base]==2 => birthing_insn_p() returns 0 =>
//      adjust_priority() skips the max_priority boost => the `la` is scheduled at the very top
//      instead of after `sll $s3,$v0,2`.  Fix: fence a SINGLE-set pseudo —
//          __asm__("" : "=r"(base) : "0"(&D_8011F7F0));
//      `base` is now set once (by the asm) and the address temp once (by the `la`), so BOTH keep
//      the birthing boost and land where the target puts them.  (15 -> 5 mismatches.)
//
//  L2  a volatile STORE is a memory barrier that register moves may cross; a
//      `__asm__ __volatile__("" ::: "memory")` is a FULL barrier that they may not.
//      sched.c's ASM_OPERANDS case adds a dependence on every reg's last set/use for a volatile
//      asm, so the memory fence pinned `sw $s1,0x18($s4)` BEFORE the call's `addu $a0,$s1,$zero`.
//      Writing the store as `*(volatile u32 *)&slot[6] = ...` keeps the store anchored (dropping
//      the fence entirely let it sink 11 slots) while letting the arg move hoist past it.
//      (5 -> 3 mismatches.)  The SECOND memory fence (before func_80024054) is still required.
//
//  L3  local-alloc.c block_alloc ties operand 0 to the first input operand that DIES
//      (combine_regs).  `sum = r1 + r2` therefore inherits r1's quantity — and r1 crosses a call,
//      so the whole quantity is forced call-preserved ($s0) and the `move $5,ext` copy-suggestion
//      is ignored.  Neither variable reuse nor an extra post-addu use of r1 breaks the tie
//      (sched1 runs first and re-sinks the use).  A pin whose live range crosses no call does:
//          register s32 sum __asm__("$5");
//      (§44-correction: a pin that does not span a `jal` is ×N-safe.)  (3 -> 2 mismatches.)
//
//  L4  pinning `sum` to $a1 makes gcc emit it before the $a0 arg move; pinning the $a0 arg too
//      (`register u32 *a0v __asm__("$4"); a0v = p;`) restores the target order.  (2 -> 0.)
//
// Also note the deliberate MIXED addressing of the same objects: (*(u16 *)&D_8011F7BC)/(*(u16 *)&D_8011F7BE) are read
// absolutely at the 3rd call (lui/lhu) and $s2-relatively (-0x34/-0x32) at the 4th/6th/7th.  That
// is what the target does; writing either form uniformly breaks it.

#include "common.h"

void func_80175AB8(param_1)
    s16 param_1;
{
   /* size 0x0C */
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];

    extern u8  D_8011F7F0;
    extern u16 D_8011F7B4;
    extern u16 D_8011F7B6;
    extern s16 D_8011F7BC;
    extern s16 D_8011F7BE;
    extern s32 D_8011F804;
    extern u16 D_8011F80A;
    extern u16 D_8011F824;
    extern u8  D_8011F832;
    extern u8  D_8011F83A;
    extern u8 *D_8018A23C[];

    extern u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_);
    extern u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_);
    extern u32  func_801783D0(s32 a0, s32 a1);
    extern u32 *func_80177EA4(u32 *param_1, s32 param_2, u32 param_3, s32 param_4);
    extern u32 *func_80177B5C(u32 *a0, s32 a1, s32 a2, s32 a3, s32 a4);
    extern void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_);
    extern u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
    extern s32 func_80024054(u8*, u8*);
    extern s32  func_8005A600(s32, s32, s32, s32, s32);

    u8 local[24];
    u8 *base;
    u8 *arr;
    u32 *slot;
    u32 *p;
    s16 q;
    s32 a2v;
    s32 t;
    s32 idx;
    s16 sv;

    p = (u32 *)(D_800AF638[param_1].g0 + D_800AF634[param_1].g0 * 4);
    base = &D_8011F7F0;
    arr = base - 0x48;
    slot = (u32 *)(param_1 * 4 + (s32)arr);
    *(volatile u32 *)&slot[6] = (u32)p;
    p = func_80176D94(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51));
    p = func_801770E0(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    t = func_801783D0(D_8011F804, 0);
    p = func_80177EA4(p, t,
                      (s16)((*(u16 *)&D_8011F7BC) + 0x39), (s16)((*(u16 *)&D_8011F7BE) + 0x51));
    sv = (s16)func_801783D0((D_8011F824 < 1000) ? D_8011F824 : 0x3E7, 4);
    p = func_80177B5C(p, sv, D_8011F832,
                      (s16)(*(u16 *)(arr + 0x14) + 0x39),
                      (s16)(*(u16 *)(arr + 0x16) + 0x65));
    q = (s16)D_8011F80A / 15;
    a2v = (q & 3) * 15;
    t = func_801783D0(q >> 2, 8) + func_801783D0(a2v, 0);
    p = ((u32 * (*)(u32 *, s32, s32, s32))func_80177940)(
            p, (s16)t,
            (s16)(*(u16 *)(arr + 0x14) + 0x76),
            (s16)(*(u16 *)(arr + 0x16) + 0x65));
    idx = D_8011F83A & 0x7F;
    D_8011F83A = idx;
    func_80024054(*(u8 **)((u8 *)D_8018A23C + idx * 4), local);
    p = func_80178298(p, local,
                      (s16)(*(u16 *)(arr + 0x14) + 0x39),
                      (s16)(*(u16 *)(arr + 0x16) + 0x5B));
    func_8005A600((s32)p, 0, 0, 0x15, 0);
    *p = (((u32)p - 0x14) & 0xFFFFFF) | 0x2000000;
    slot[8] = (u32)p;
    p += 5;
    D_800AF634[param_1].g0 += ((s32)p - (s32)slot[6]) >> 2;
}


// @class: schedule
// @unstuck(P36): none — MATCH (231 ins)
#include "common.h"

extern u8  D_8011F7F0;
extern u8  D_800B9A13;
   /* size 0x0C */
extern S_AF634 D_800AF634[];
extern S_AF634 D_800AF638[];
extern u16 D_8018A1DC[];
extern u16 D_8018A22C[];
extern u16 D_8018A238;
extern u8  D_8018A2B8[];
extern u8  D_8018A2CC[];
extern s32 D_8018A2E4[];
extern u8  D_800D43D4;
extern u8  D_800D4414;
extern u8  D_800D45D4;
extern u32 *func_8017742C(u32 *a0, s32 a1, s32 a2);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800183E0(s32 a0);

  /* 0x14 */

void func_80175DA8(param_1)
    u16 param_1;
{

    u8 *base = &D_8011F7F0;
    u8 *s = base - 0x48;
    u16 *src = D_8018A1DC;
    Sp_80175DA8 *p;
    s16 i;
    s32 arg;
    s32 t;
    s32 fl;
    u16 v;

    p = (Sp_80175DA8 *)(D_800AF638[(s16)param_1].g0 + D_800AF634[(s16)param_1].g0 * 4);
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28) = p;
    i = 0;
    do {
        p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x4000000;
        p->code = *(u32 *)src;
        src += 2;
        if (i < 2) {
            p->x = *src++ + *(u16 *)(s + 0xC);
            p->y = *src++ + *(u16 *)(s + 0xE);
        } else if (i == 2) {
            p->x = *src++ + *(u16 *)(s + 0x10);
            p->y = *src++ + *(u16 *)(s + 0x12);
        } else {
            p->x = *src++ + *(u16 *)(s + 0x14);
            p->y = *src++ + *(u16 *)(s + 0x16);
        }
        p->uv = *(u32 *)src;
        src += 2;
        p->wh = *(u32 *)src;
        src += 2;
        p++;
        i++;
    } while (i < 5);

    *(u8 *)(s + 7) = D_800B9A13;
    p = (Sp_80175DA8 *)func_8017742C((u32 *)p,
                                     (s16)(*(u16 *)(s + 0x10) - 0x98),
                                     (s16)(*(u16 *)(s + 0x12) + 9));
    func_8005A600((s32)p, 0, 0, 0x16, 0);
    p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x2000000;
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x30) = p;
    p++;
    {
        s32 acc = D_800AF634[(s16)param_1].g0;
        D_800AF634[(s16)param_1].g0 =
            acc + (((s32)p - *(s32 *)(s + (s16)param_1 * 4 + 0x28)) >> 2);
    }

    p = *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28);
    if (base[0x48] != 0) {
        *((u8 *)p + 0xD) = 0;
    } else {
        *((u8 *)p + 0xD) = 0xA0;
    }

    {
        u8 *q1 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        *(u16 *)(q1 + 0x22) = 0x6CD6;
        if (base[0x48] & 0x80) {
            *(u16 *)(q1 + 0x20) = D_8018A238;
            arg = (s32)&D_800D45D4;
        } else {
            u16 *tt = D_8018A22C;
            s32 k = base[0x48];
            if (k != 0) {
                k--;
                tt += k;
            }
            *(u16 *)(q1 + 0x20) = *tt;
            arg = D_8018A2E4[base[0x48]];
        }
    }
    func_800183E0(arg);

    {
        u8 *q2 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        t = (s32)(*(u16 *)(base + 0x2E) << 16);
        if (t != 0) {
            q2[0x49] = D_8018A2CC[t >> 20];
        } else {
            q2[0x49] = 0xA0;
        }
    }

    {
        u8 *q3 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        v = *(u16 *)(base + 0x40);
        if (v < 100) {
            q3[0x5D] = D_8018A2B8[v / 5];
        } else {
            q3[0x5D] = 0;
        }
    }

    do { fl = *(s16 *)(base + 0x1E) & 0x8000; } while (0);
    /* §5a zero-byte sched fence: without it sched1 hoists the `la D_800D43D4`
       into the lh's load-delay slot, dropping the target's nop (-1 ins). */
    arg = (s32)&D_800D43D4;
    if (fl != 0) {
        arg = (s32)&D_800D4414;
    }
    func_800183E0(arg);
}


#include "common.h"

/* func_80176144 — RECONCILED variant of .run/uc/func_80176144.c
 *
 * GATE BLOCKER (whole-binary build, NOT match_one):
 *   src/ov_SC01_077/ov_SC01_077_jr_801734BC.c:3476: conflicting types for `D_800AF634'
 *   || previous declaration at :3296
 *
 * ROOT CAUSE — a HOISTED file-scope typedef, not a bad signature:
 *   That TU hoists, at FILE scope, for func_80175DA8:
 *       :3295  typedef struct { s32 g0; s32 pad[2]; } S_AF634;
 *       :3296  extern S_AF634 D_800AF634[];
 *       :3297  extern S_AF634 D_800AF638[];
 *   The stored draft re-declares the SAME struct shape as a BLOCK-scope typedef
 *   (rule D — it must travel to the 137 sibling overlays, which have no such
 *   preamble).  A block-scope `typedef struct {...} S_AF634;` is a DISTINCT type
 *   from the file-scope one (C has no structural typing), so the block-scope
 *   `extern S_AF634 D_800AF634[];` re-declares the symbol incompatibly with the
 *   in-scope file-scope decl -> hard error.
 *   Note the earlier block-scope copies in the same TU (:3080 func_80175820,
 *   :3123 func_801759D8) do NOT error: they precede :3296, so no file-scope decl
 *   of D_800AF634 is in scope there.  Anything AFTER :3296 collides.  Our
 *   definition lands at :3476.  That is why only this one fired.
 *
 * FIX — §37/§124 ASM-LABEL ALIAS applied to the DATA symbols (cookbook §2516:
 *   "asm-label alias for sibling-decl signedness/proto conflicts ... beats
 *   reconcile's *(u16*)&D_x cast whose address-of PERTURBS regalloc"):
 *   the two objects are reached through PRIVATE C identifiers aAF634 / aAF638
 *   carrying __asm__("D_800AF634") / __asm__("D_800AF638").  The emitted
 *   %hi/%lo relocations are against the same symbols, so codegen is unchanged,
 *   while the C names can never collide with ANY sibling TU's declaration —
 *   whether hoisted, block-scope, or absent.  No header edit; no src/ edit.
 *   Strictly better than deleting the local decls (which would bind this
 *   exemplar to the one TU that happens to hoist them).
 *
 * The s32 parameter + explicit (s16) narrowing is retained from the stored draft
 * (canonical decl in engine_core.h:18985/:4587 is `void func_80176144(s32)`;
 * the K&R short param would itself be a conflicting-types error).  The (s16)
 * narrowing IS the entry `sll $s0,$a0,16 / sra $s0,$s0,16` pair.
 *
 * Verified: python3 tools/match_one.py func_80176144 --c .run/uc2/func_80176144.c
 *           --asm-subdir ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC -> MATCH (53 ins)
 */

#include "../shared/ov/func_80176144.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (327/327 ins, match_one MATCH; symcheck SYMS-OK 18 symbols)
//
// STRUCTURE (byte-derived, all verified against the .s):
//   $s3=st=&D_8011F7A8 (int base), $s1=st+0x48 (cach), $s2=st+0xE0 (flag), $s5=&(*(u8 *)D_80078E78) (src), $s4=param.
//   6 HUD fields synced src->cach with a chg-flag at [flag]: pairs 0x3A/0x3C and 0x3E/0x40, then 0x14(s32),
//   0x34(u16)+0x42(u8), 0x1A(s16), 0x4A(u8). Each: `if (cach==src) { if(!chg) goto skip; chg=0; } else {adjust}` + draw.
// KEY FINDINGS (reusable):
//   * Base MUST be `s32`, and the index expr written OFFSET-FIRST (`((p<<16)>>14) + st + 0x18`) — a `u8*` base
//     yields `addu rd,st,off`; the target is `addu rd,off,st`. Matches Ghidra's `(...>>0xe) + -0x7fee0840`.
//   * buf is 24 bytes, NOT Ghidra's 32: MIPS STARTING_FRAME_OFFSET = outgoing_args_size(20), so get_frame_size()
//     counts the 4-byte args-alignment gap. var=MIPS_STACK_ALIGN(4+24)=32 -> 32+24+28 -> 0x58. buf[32] gives 0x60.
//   * Block 1 uses RAW GLOBALS (D_8011F82C...) -> absolute lui/%lo; the ne-block uses `st+0x82`/`st+0x11C`
//     ($s3-relative) — both byte-confirmed; cse blocks end at labels so each region picks its own form.
//   * `ne` pinned to $v0 (+6 aligned).
//
// THE TWO LEVERS THAT CLOSED IT (SESSION-21, both byte-proven here; 18 -> 7 -> 3 -> 1 -> 0):
//   (L1) BLOCK-5 STORE DUPLICATED INTO BOTH ARMS (`if (f&1) *(e+0x32A)=0x200; else *(e+0x32A)=...+0x65;`)
//        instead of computing a phi `sv` and storing once after the merge.  Reason: sched1 is a BACKWARD list
//        scheduler and a store is a memory-unit user, so `potential_hazard` floats it to the FRONT of the
//        backward ready list => it is EMITTED ~8 insns late, which stretches the `sv`/`e` live ranges over
//        $v0/$v1/$a0/$a1 and pushes them out to $a2/$a3.  Writing the store in both arms lets cross_jump
//        merge the common tail, so the store lands first at the merge label, `sv`->$v0 and `e`->$a0, and the
//        `lui $a0` anti-dependence then PINS the schedule.  (18 mismatches -> 7.)
//   (L2) THE COMMUTATIVE-ADD OPERAND SWAP.  Target is `addu $a1,$s0,$v0` = plus(ret1, ret2) into a FRESH
//        non-call-crossing quantity that inherits the $a1 arg copy-suggestion.  Plain `sum = i6 + i4` lets
//        local_alloc TIE the dest to the dying `i6` (which crosses call2) => the whole chain is forced
//        call-saved => `addu $s0,$s0,$v0` (3 mismatched).  Accumulating (`i4 = i6 + i4`) frees $a1 but
//        expand_binop SWAPS a commutative op when target==op1, printing `addu $a1,$v0,$s0` (1 mismatched).
//        Fix: route the second call's value through a copy temp first —
//            sum = i4;  i4 = i6 + sum;
//        target(i4) != op1(sum) at EXPAND time so no swap; cse then folds sum back and deletes the copy.
//        => `addu $a1,$s0,$v0`.  MATCH.
extern u16 D_80078EB2;
extern u16 D_8011F82A;
extern u16 D_8011F82C;
extern s16 D_80078EB4;
extern u16 D_8011F8C4;
extern u8  D_8011F7A8;   /* st base  ($s3) */
extern u8 D_80078E78[];   /* cur base ($s5) */
extern u8  D_8018A2B8[];
extern u8 *D_8018A23C[];

extern void  func_80176FF4(s32);
extern void  func_80177340(s32);
extern u32   func_801783D0(s32, s32);
extern void  func_80177F84(s32, s32);
extern void func_80177DA8(u8 * p, u32 v, s32 idx);
extern void func_80177AD4(int, unsigned int);
extern s32   func_80024054(u8 *, u8 *);
extern u32 *func_80178298(u32*, u8*, short, short);
extern s32   func_8005A600(s32, s32, s32, s32, s32);

void func_80176218(s32 param_1)
{
    s32 st   = (s32)&D_8011F7A8;   /* $s3 */
    s32 cach = st + 0x48;          /* $s1 */
    s32 flag = st + 0xE0;          /* $s2 */
    s32 cur  = (s32)&(*(u8 *)D_80078E78);   /* $s5 */
    u8 buf[24];
    s32 ne;
    s32 t;
    u16 sA;

    /* ---- block 1: raw-global pair 0x3A/0x3C ---- */
    sA = D_80078EB2;
    t = (sA != D_8011F82A);
    if (D_8011F82C == (*(u16 *)&D_80078EB4)) {
        ne = t;
        if (ne == 0 && D_8011F8C4 == 0) goto L340;
    } else {
        s32 d = (s16)(D_8011F82C - (*(u16 *)&D_80078EB4));
        u16 nv;
        if (d < 0) {
            if (d < -10) nv = D_8011F82C + 2;
            else         nv = D_8011F82C + 1;
        } else {
            if (d > 10)  nv = D_8011F82C - 2;
            else         nv = D_8011F82C - 1;
        }
        D_8011F82C = nv;
        *(u16 *)(flag + 0x3C) = 1;
        *(u16 *)(cach + 0x3A) = *(u16 *)(cur + 0x3A);
        goto L328;
    }
    if (ne) {
        *(u16 *)(st + 0x82)  = sA;
        *(u16 *)(st + 0x11C) = 1;
    } else {
        *(u16 *)(st + 0x11C) = 0;
    }
L328:
    func_80176FF4(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18));
L340:

    /* ---- block 2: pair 0x3E/0x40 ---- */
    sA = *(u16 *)(cur + 0x3E);
    t = (sA != *(u16 *)(cach + 0x3E));
    if (*(u16 *)(cach + 0x40) == *(u16 *)(cur + 0x40)) {
        ne = t;
        if (ne == 0 && *(u16 *)(flag + 0x40) == 0) goto L444;
    } else {
        s32 d = (s16)(*(u16 *)(cach + 0x40) - *(u16 *)(cur + 0x40));
        u16 nc;
        if (d < 0) {
            if (d < -10) nc = *(u16 *)(cach + 0x40) + 2;
            else         nc = *(u16 *)(cach + 0x40) + 1;
        } else {
            if (d > 10)  nc = *(u16 *)(cach + 0x40) - 2;
            else         nc = *(u16 *)(cach + 0x40) - 1;
        }
        *(u16 *)(cach + 0x40) = nc;
        *(u16 *)(flag + 0x40) = 1;
        *(u16 *)(cach + 0x3E) = *(u16 *)(cur + 0x3E);
        goto L3E8;
    }
    if (ne) {
        *(u16 *)(cach + 0x3E) = sA;
        *(u16 *)(flag + 0x40) = 1;
    } else {
        *(u16 *)(flag + 0x40) = 0;
    }
L3E8:
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u16 cc;
        s32 pp;
        func_80177340(*(s32 *)(s0b + 0x18) + 0x104);
        cc = *(u16 *)(cach + 0x40);
        pp = *(s32 *)(s0b + 0x28);
        if (cc < 100)
            *(u8 *)(pp + 0x5D) = D_8018A2B8[cc / 5];
        else
            *(u8 *)(pp + 0x5D) = 0;
    }
L444:

    /* ---- block 3: field 0x14 (s32) ---- */
    if (*(s32 *)(cach + 0x14) == *(s32 *)(cur + 0x14)) {
        if (*(s32 *)(flag + 0x14) == 0) goto L4D0;
        *(s32 *)(flag + 0x14) = 0;
        goto L4A8;
    } else {
        s32 d = *(s32 *)(cur + 0x14) - *(s32 *)(cach + 0x14);
        s32 nd;
        if (d > 0) {
            if (d < 10) nd = *(s32 *)(cach + 0x14) + 1;
            else        nd = *(s32 *)(cach + 0x14) + 10;
        } else {
            if (d < -9) nd = *(s32 *)(cach + 0x14) - 10;
            else        nd = *(s32 *)(cach + 0x14) - 1;
        }
        *(s32 *)(cach + 0x14) = nd;
        *(s32 *)(flag + 0x14) = 1;
    }
L4A8:
    {
        u32 r = func_801783D0(*(s32 *)(cach + 0x14), 0);
        func_80177F84(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x208, r);
    }
L4D0:

    /* ---- block 4: field 0x34 (u16) + 0x42 (u8) ---- */
    if (*(u16 *)(cur + 0x34) != *(u16 *)(cach + 0x34)) {
        *(u16 *)(cach + 0x34) = *(u16 *)(cur + 0x34);
        *(u16 *)(flag + 0x34) = 1;
        *(u8 *)(cach + 0x42) = *(u8 *)(cur + 0x42);
    } else {
        if (*(u16 *)(flag + 0x34) == 0) goto L558;
        *(u16 *)(flag + 0x34) = 0;
    }
    {
        u16 e = 999;
        s16 r;
        if (*(u16 *)(cach + 0x34) < 1000) e = *(u16 *)(cach + 0x34);
        r = (s16)func_801783D0((s16)e, 4);
        func_80177DA8(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x294,
                      (s32)r, *(u8 *)(cach + 0x42));
    }
L558:

    /* ---- block 5: field 0x1A (s16) ---- */
    if (*(s16 *)(cach + 0x1A) != *(s16 *)(cur + 0x1A)) {
        *(s16 *)(cach + 0x1A) = *(s16 *)(cur + 0x1A);
        *(s16 *)(flag + 0x1A) = 1;
    } else {
        if (*(s16 *)(flag + 0x1A) == 0) goto L63C;
        *(s16 *)(flag + 0x1A) = 0;
    }
    {
        u16 f = *(u16 *)(cach + 0x1A);
        s32 e = *(s32 *)(((param_1 << 16) >> 14) + st + 0x18);
        s32 i6, i4, sum;
        /* L1: the store is written into BOTH arms so cross_jump merges the tail (see header). */
        if (f & 1) *(s16 *)(e + 0x32A) = 0x200;
        else       *(s16 *)(e + 0x32A) = *(u16 *)(st + 0x16) + 0x65;
        {
            s32 t = (((s16)f / 15) & 3) * 15;
            i6 = func_801783D0(((s16)f / 15) * 0x10000 >> 0x12, 8);
            i4 = func_801783D0((t * 0x10000) >> 16, 0);
        }
        /* L2: copy temp defeats expand_binop's commutative swap; cse folds it back (see header). */
        sum = i4;
        i4 = i6 + sum;
        ((void (*)(s32, s32))func_80177AD4)(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 800,
                      i4 * 0x10000 >> 0x10);
    }
L63C:

    /* ---- block 6: field 0x4A (u8) ---- */
    if (*(u8 *)(cur + 0x4A) != *(u8 *)(cach + 0x4A)) {
        *(u8 *)(cach + 0x4A) = *(u8 *)(cur + 0x4A) & 0x7F;
        *(u8 *)(flag + 0x4A) = 1;
    } else {
        if (*(u8 *)(flag + 0x4A) == 0) return;
        *(u8 *)(flag + 0x4A) = 0;
    }
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u8 *arg = D_8018A23C[*(u8 *)(cach + 0x4A)];
        u32 *p = (u32 *)(*(s32 *)(s0b + 0x18) + 900);
        func_80024054(arg, buf);
        p = ((u32 * (*)(u32 *, u8 *, s32, s32))func_80178298)(p, buf,
                          (s16)(*(u16 *)(st + 0x14) + 0x39),
                          (s16)(*(u16 *)(st + 0x16) + 0x5B));
        func_8005A600((s32)p, 0, 0, 0x15, 0);
        *p = ((u32)((u8 *)p - 0x14) & 0xffffff) | 0x2000000;
        *(u32 **)(s0b + 0x20) = p;
    }
}


// @class: regalloc-order + schedule
// @unstuck(P36): none — MATCH (371/371 ins, match_one MATCH)
//
// func_80176734 — ov_SC01_077 HUD-state pump, 371 ins.  Direct sibling of the already-matched
// func_80176218 in the same TU: same base quartet
//     $s3 = st   = &D_8011F7A8          (int base, NOT u8* — see 80176218's note)
//     $s1 = cach = st + 0x48            (the cached/displayed copy)
//     $s2 = flag = st + 0xE0            (the per-field "changed" flags)
//     $s4 = cur  = &D_80078E78          (the live gameplay struct)
// and the same OFFSET-FIRST index idiom `((param<<16)>>14) + st + 0x28`
// (a u8* base emits `addu rd,st,off`; the target wants `addu rd,off,st`).
//
// CONTROL-FLOW SKELETON (byte-derived from the .s; no loops, one switch, 8 straight-line blocks):
//   A  p = st.ptr[param];  q = p+0x3C
//      if (D_801152BA) { triangle-wave pulse byte -> q[4] and p[4]; st[8] += D_80115214 }
//      else            { p[0x40] = p[4] = 0x80 }
//   B  if (flag[0x48]) { p->[0xD] = anim[flag48]; if (flag48<4) flag48++ else {draw + advance} }
//   C  else if (cach[0x48] != cur[0x48]) { seed flag48 (5 or 0); cach48 = cur48; draw; flag48++ }
//   D  0x2E sync (equality-first if/else) + the 0x49 gauge byte
//   E  0x1E sign-bit flip -> one of two func_800183E0 calls
//   F  D_800B9A13 mode byte -> chg
//   G  switch (cur[0x48]) { 3,4,5 -> amp=0xFF on hit; 6 -> amp=0xBA } (gcc decision tree, no jtbl)
//   H  if (amp) { flag[0x47]=1; cach[0x4B]=cur48|0xF0; cach[0x47]=(D_80126D20<<7)/amp; goto tail }
//   I  else derive tgt/chg2 from D_80126CE0 or cur[0x47]
//   J  if (!chg2 && !chg && !flag[0x47]) goto tail;  chg==0 -> flag[0x47]=0 (out-of-line else)
//   K  else slew cach[0x47] toward tgt (-3 / -8, clamp, flag[0x47]=1)
//   L  tail: st.ptr[param][0x32] = st[0x12]+m+5 ; func_801775E0(ptr+0x64, st[0x12]+m+9)
//   Frame 0x40, $ra at 0x3C, $s0-$s6 saved at 0x20..0x38.
//
// LEVERS THAT CLOSED IT (335 -> 206 -> 96 -> 57 -> 36 -> 19 -> 15 -> 5 -> 0):
//
//  L1  `u8 b` + `u8 v` in block A is what produces the target's `andi $v0,$v1,0xFF`.
//      With `s32 v` combine folds the QI zero_extend straight into the `sltiu` (no andi);
//      with a QImode *result* the arithmetic arms go through force_to_mode (mask dropped ->
//      `addiu $v0,$v1,-0x80` / `nor;addiu` on the RAW lbu reg) while the comparison keeps its
//      zero_extend as a real `andi`.  Same idiom for `u8 k` in block C and `u8 m` in block F.
//
//  L2  `q = p + 0x3C` must be computed in the ENTRY block (before the D_801152BA branch).
//      combine's LOG_LINKS are per-basic-block, so a cross-BB `q` cannot be folded back into
//      `sb v,0x40(p)` — which is exactly why the target keeps a separate `addiu $a0,$a1,0x3C`.
//
//  L3  THE COPY-TEMP FAMILY (5 of the 7 missing instructions were `move` insns gcc had deleted).
//      `t = (a != b); x = t;` normally collapses to one `sltu x,...`.  Two ways to keep the copy:
//        (a) give `t` a second use AND a `register __asm__` pin  (block F: `register s32 t $2`);
//        (b) a zero-byte single-set fence `__asm__("" : "=r"(t) : "0"(t));` between the compute
//            and the copy — the copy then links to the asm, which combine cannot substitute.
//      (b) is used for `av = amp` (switch merge), `chg2 = t` (block I) and `c = chg` (block J).
//      The block-J fence does double duty: it re-defines `c` so cse's record_jump_equiv loses
//      `c == 0` on the fall-through path and the target's *second* `beqz $v1` survives.
//
//  L4  Block K: the store must be DUPLICATED into both arms (`= c-3` / `= c-8`), not written once
//      after a phi.  cse runs before cross_jump, so with two stores the following
//      `c = *(u8*)(cach+0x47)` sits in a fresh extended basic block and stays a REAL `lbu`;
//      write it once and cse forwards the stored value into an `andi` (-1 ins).  cross_jump then
//      merges the two `sb`s back into the single one at .L80176C3C.  (Same lever as 80176218 L1.)
//
//  L5  `u8 dum[8]` — the target's `.frame` has vars=8 (frame 0x40 vs 0x38 with no stack locals and
//      no spill anywhere in the body).  gcc allocates frame space for an aggregate local in
//      expand_decl whether or not it is ever read, so the original had a dead local here.
//
//  L6  `pv` (a plain copy of the parameter) is what splits the parameter's live range the way the
//      target does: block A indexes off `param_1` (whose pseudo dies in the entry block -> $a0, so
//      `sll $v0,$a0,16` can be scheduled before the save) while blocks B..L index off `pv` -> $s6.
//      `ix` is hoisted out of block A so the `pv = param_1` copy lands after the index chain and
//      before cach/flag/cur — that is the target's prologue interleave (s3, index, s6, s1, s2, s4).
//
//  L7  Pins that only fix first-fit order (none spans a `jal`, so all are x N-safe per §44):
//      chg=$s5($21), chg2=$s0($16), tgt=$a1($5), p=$a1($5) in block A, pp=$a1($5) in blocks B/C.
//      `p`/`pp` on $a1 is the one that cascades: it frees $a0 for `q` and for the block-B base,
//      and it is what lets reorg steal `sll $a0,$s6,16` into the .L80176C8C delay slot.
//
//  L8  Block I else-arm: cache cach[0x47] in a `u32 cv` local.  Reading it twice through the
//      pointer makes gcc re-mask (`andi $v1,$v1,0xff`, +1 ins); the local keeps both compares on
//      the raw lbu reg like the target.  Block K: hoist `sv = (s16)tgt` so the `!= 0` test reuses
//      the sign-extended $a0 instead of emitting `andi $a1,0xffff`.
//
// Declaration environment: every extern is block-scoped (§28/§43 zero file-scope footprint).
// The types match the decls already at file scope in ov_SC01_077_jr_801734BC.c
// (D_8011F7A8 u8, D_80078E78 u8[], D_8018A238 u16, D_8018A2CC u8[], D_8018A2E4 s32[],
//  D_800D43D4/4414/45D4 u8, D_800B9A13 u8, D_80126D20 s16, D_80126B58 s32,
//  func_800183E0(s32), func_801619D0(void*), func_80161A00/30/60(s32)); func_801775E0 is the
// shared engine-core DEFINE later in the same TU, so it needs the forward decl below.

#include "common.h"

void func_80176734(s32 param_1)
{
    extern u8  D_8011F7A8;      /* st base  ($s3) */
    extern u8  D_80078E78[];    /* cur base ($s4) */
    extern s16 D_801152BA;
    extern u8  D_8011F7B0;      /* == *(u8 *)(st + 8), read absolutely (mixed addressing) */
    extern u8  D_80115214;
    extern u8  D_8018A2D8[];
    extern u16 D_8018A22A[];
    extern u16 D_8018A238;
    extern u8  D_8018A2CC[];
    extern s32 D_8018A2E4[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;
    extern u8  D_800B9A13;
    extern s16 D_80126CE0;
    extern s16 D_80126D20;
    extern s32 D_80126B58;
    extern void func_800183E0(s32 a0);
    extern s32  func_801619D0(void *a0);
    extern s32  func_80161A00(s32 a0);
    extern s32  func_80161A30(s32 a0);
    extern s32  func_80161A60(s32 a0);
    extern void func_801775E0(s32 param_1, s32 param_2);

    s32 st, cach, flag, cur;
    s16 chg;        /* s16: every `(s32)chg` is a sign extension that combine reduces to a copy ($v1) */
    s16 amp;        /* s16, and reused as block I's change flag (the target keeps both in $s0) */
    u16 tgt;
    s32 pv;                                  /* the param copy that owns $s6 */
    s32 ix;                                  /* block A's index, hoisted out of the block */
    u8  dum[8];                              /* dead frame slot (target .frame vars=8) */
    s32 p;          /* ONE sprite-list pointer for blocks A, B and C: its conflicts leave it $a1 */

    st  = (s32)&D_8011F7A8;
    ix  = ((param_1 << 16) >> 14) + st;
    pv  = param_1;
    cach = st + 0x48;
    flag = st + 0xE0;
    cur  = (s32)&(*(u8 *)D_80078E78);

    /* ---- block A: pulse byte ---- */
    {
        u8 *q;
        p = *(s32 *)(ix + 0x28);
        q = (u8 *)(p + 0x3C);                /* must live in the entry BB */
        if (D_801152BA != 0) {
            u8 b = D_8011F7B0;
            u8 v;
            if (b < 0x80) v = b - 0x80;
            else          v = ~b - 0x80;
            q[4] = v;
            *(u8 *)(p + 4) = v;
            *(u8 *)(st + 8) = *(u8 *)(st + 8) + D_80115214;
        } else {
            *(u8 *)(p + 0x40) = 0x80;
            *(u8 *)(p + 4) = 0x80;
        }
    }

    /* ---- block B: 0x48 animation already running ---- */
    if (*(u8 *)(flag + 0x48) != 0) {
        p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        *(u8 *)(p + 0xD) = D_8018A2D8[*(u8 *)(flag + 0x48)];
        if (*(u8 *)(flag + 0x48) < 4) {
            *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
        } else {
            u8 c = *(u8 *)(cach + 0x48);
            s32 arg;
            p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
            if (c & 0x80) {
                *(u16 *)(p + 0x20) = D_8018A238;
                arg = (s32)&D_800D45D4;
            } else if (c != 0) {
                *(u16 *)(p + 0x20) = D_8018A22A[c];
                arg = D_8018A2E4[*(u8 *)(cach + 0x48)];
            } else {
                goto Lskip;
            }
            func_800183E0(arg);
        Lskip:
            if (*(u8 *)(flag + 0x48) == 5) {
                if (*(u8 *)(cach + 0x48) == 0) *(u8 *)(flag + 0x48) = 0;
                else *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            } else if (*(u8 *)(flag + 0x48) == 10) {
                *(u8 *)(flag + 0x48) = 0;
            } else {
                *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            }
        }
    /* ---- block C: 0x48 changed -> start the animation ---- */
    } else if (*(u8 *)(cach + 0x48) != *(u8 *)(cur + 0x48)) {
        u8 k;                                /* gives the `andi $v1,$v1,0xFF` index mask */
        if (*(u8 *)(cach + 0x48) == 0 && *(u8 *)(cur + 0x48) != 0)
            *(u8 *)(flag + 0x48) = 5;
        else
            *(u8 *)(flag + 0x48) = 0;
        *(u8 *)(cach + 0x48) = *(u8 *)(cur + 0x48);
        p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        k = *(u8 *)(flag + 0x48);
        *(u8 *)(flag + 0x48) = k + 1;
        *(u8 *)(p + 0xD) = D_8018A2D8[k];
    }

    /* ---- block D: field 0x2E (equality-first: the ne-arm must be out of line) ---- */
    if (*(s16 *)(cach + 0x2E) == *(s16 *)(cur + 0x2E)) {
        if (*(s16 *)(flag + 0x2E) == 0) goto L9C0;
        *(s16 *)(flag + 0x2E) = 0;
    } else {
        *(s16 *)(cach + 0x2E) = *(s16 *)(cur + 0x2E);
        *(s16 *)(flag + 0x2E) = 1;
    }
    {
        s32 pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        s32 t = (s32)(*(u16 *)(cach + 0x2E) << 16);
        if (t != 0) *(u8 *)(pp + 0x49) = D_8018A2CC[t >> 20];
        else        *(u8 *)(pp + 0x49) = 0xA0;
    }
L9C0:

    /* ---- block E: field 0x1E sign flip ---- */
    {
        s32 fa = *(s16 *)(cach + 0x1E) & 0x8000;
        s32 fb = *(s16 *)(cur + 0x1E) & 0x8000;
        if (fa != fb) {
            s32 arg;
            if (fa != 0) {
                *(s16 *)(cach + 0x1E) = 0;
                arg = (s32)&D_800D43D4;
            } else {
                *(s16 *)(cach + 0x1E) = -0x8000;
                arg = (s32)&D_800D4414;
            }
            func_800183E0(arg);
        }
    }

    /* ---- block F: mode byte -> chg ---- */
    {
        u8 m = D_800B9A13;
        if (m != 3) {                        /* inverted: `chg = 0` belongs out of line */
            chg = (*(u8 *)(st + 7) != m);
            if (chg != 0) *(u8 *)(st + 7) = m;
        } else {
            chg = 0;
        }
    }

    /* ---- block G: switch on cur[0x48] (cases 3/4/5 cross-jump onto one tail) ---- */
    amp = 0;
    switch (*(u8 *)(cur + 0x48)) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) amp = 0xFF;
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) amp = 0xBA;
        break;
    }

    /* ---- block H: amp != 0 short-circuit ---- */
    {
        if (amp != 0) {
            *(u8 *)(flag + 0x47) = 1;
            *(u8 *)(cach + 0x4B) = *(u8 *)(cur + 0x48) | 0xF0;
            *(u8 *)(cach + 0x47) = ((s32)D_80126D20 << 7) / amp;
            goto Ltail;
        }
    }

    if (*(u8 *)(cach + 0x4B) >= 0xF0) *(u8 *)(cach + 0x4B) = 0;

    /* ---- block I: target level + change flag.  The lhu is unconditional (target loads
       both the signed and the unsigned view of D_80126CE0 up front). ---- */
    tgt = *(u16 *)&D_80126CE0;
    if (D_80126CE0 != 0) {
        u8 v;                                /* u8: a SUBREG copy cse keeps; masked in place at the compare */
        v = tgt;
        *(u8 *)(cach + 0x4B) = v;
        amp = (*(u8 *)(cach + 0x47) != v);
    } else {
        u32 cv = *(u8 *)(cach + 0x47);       /* one load, two compares, no re-mask */
        tgt = *(u8 *)(cur + 0x47);
        amp = 0;
        if (cv != tgt || cv == 0x80) amp = 1;
        if (*(u8 *)(cur + 0x47) != 0 && *(u8 *)(cach + 0x4B) != 0) {
            *(u8 *)(cach + 0x4B) = 0;
            *(u8 *)(cach + 0x47) = *(u8 *)(cur + 0x47);
        }
    }

    /* ---- block J/K: slew cach[0x47] toward tgt when anything changed.  The inner test re-reads
       chg after the flag load (cse cannot see through the label), jump threading sends the outer
       `chg != 0` past it. ---- */
    if (amp != 0 || chg != 0 || *(u8 *)(flag + 0x47) != 0) {
        if (amp != 0 || chg != 0) {
            u32 c = *(u8 *)(cach + 0x47);
            s32 sv = (s16)tgt;
            if ((s32)c < sv) {
                *(u8 *)(cach + 0x47) = tgt;
            } else {
                if (sv != 0) *(u8 *)(cach + 0x47) = c - 3;   /* store in BOTH arms */
                else         *(u8 *)(cach + 0x47) = c - 8;
                c = *(u8 *)(cach + 0x47);        /* stays a real lbu because of the two stores */
                if (c == 0 || c > 0x80) {
                    *(u8 *)(cach + 0x47) = 0;
                    *(u8 *)(cach + 0x4B) = 0;
                } else if ((s32)c < (s16)tgt) {  /* fresh EBB -> the sll/sra is recomputed */
                    *(u8 *)(cach + 0x47) = tgt;
                }
            }
            *(u8 *)(flag + 0x47) = 1;
        } else {
            *(u8 *)(flag + 0x47) = 0;
        }
    }
Ltail:

    /* ---- block L: tail.  m+5 / m+9 are separate temps: `lhu + (m+5)`, not `(lhu + m) + 5`. ---- */
    {
        s32 b = ((pv << 16) >> 14) + st;
        s32 m = (*(u8 *)(st + 7) != 0) << 8;
        s32 m5 = m + 5;
        s32 m9 = m + 9;
        *(u16 *)(*(s32 *)(b + 0x28) + 0x32) = *(u16 *)(st + 0x12) + m5;
        func_801775E0(*(s32 *)(b + 0x28) + 0x64, (s16)(*(u16 *)(st + 0x12) + m9));
    }
}


#include "../shared/ov/func_80176D00.h"

/* func_80176D94 (ov_SC01_077) — 152 ins. Port of the MATCHED sibling func_801770E0
 * (src/ov_SC01_077/ov_SC01_077.c:10352, Fable5 crack): the two targets are
 * instruction-ISOMORPHIC (diff = immediates/symbols only). All levers inherited:
 *  - /s-load dep lattice: both D-globals read as struct-member-at-offset-0 (COMPONENT_REF
 *    sets MEM_IN_STRUCT_P on the LOAD) → full store↔load conflict lattice (sched.c:816-864
 *    drop clauses both fail) → tail = source statement order around the loads.
 *  - `dl` multi-set load var (reg_n_sets==2 → no birthing boost → lhu stays at source pos).
 *  - v0m-before-c6055 block: [1]-statement-first with the [0] value precomputed → mask
 *    0xffffff materializes first; c6000dcff pinned $a2 (breaks the sched2 $v1 fixed point).
 *  - head (u16)param_2 (zero_extend) vs tail param_2 & 0xffff (AND) — CSE-dodge, no
 *    cross-call CSE, no 7th callee-save.
 *  - u4/u5 fresh single-set call-result vars (S2 boost → jal delay slots);
 *    c3/cad/cff = $s5/$s4/$s3 pins. param_2/uVar5/iVar6 UNPINNED (natural $s2/$s0/$s1).
 * Constant swaps vs 770E0: 0x6e16{5010,5808,4060,3858}→0x6b56{5040,5808,4060,3858},
 * D_8011F830→D_8011F82C, D_8011F82E→D_8011F82A, 0xb8→0xad, 0x6055ff00→0x6000dcff,
 * 0x60ff3214→0x600000ff, (iVar6-4)→(iVar6+10), (iVar6-5)→(iVar6+9).
 */

#include "../shared/ov/func_80176D94.h"

#include "../shared/ov/func_80176FF4.h"

// MATCH (152/152) — func_801770E0, Fable5 crack, Phase 24 T7 §G.
// Was: the regalloc.md §RC-6 NAMED exemplar, CLOSE=47 floor. VERDICT DOWNGRADED: not a
// pressure-lock — the 47 residual was a MISSING MEMORY-DEPENDENCE LATTICE (wrong dep graph),
// and once restored every remaining edit was local+monotone: 47 -> 12 -> 10 -> 4 -> MATCH.
//
// LEVER 1 (47->12, THE STRUCTURAL KEY — "/s-load dep lattice"):
//   gcc-2.7.2 expr.c marks INDIRECT_REF-of-PLUS as MEM_IN_STRUCT_P: `p[k]` (k!=0) stores are
//   mem/s, bare `*p` is not. sched.c:829-907 true/anti_dependence DROP the conflict when one
//   side is /s+varying(+!QI) and the other non-/s+fixed → `puVar3[k]` stores never order
//   against a plain `lhu D_global` (fixed-address, non-/s) → both tail lhu's float free and
//   ~40 insns of store/mul schedule collapse into priority soup (the old "RC-6" 47).
//   FIX (zero bytes): load the global as a struct member at offset 0 —
//   `((struct hs*)&D_8011F830)->h` — COMPONENT_REF sets /s on the LOAD; both exception
//   clauses now fail for every store↔load pair → full conflict lattice: stores before the
//   load statement hold it down (true deps), stores after stay below it (anti deps).
//   The whole tail order then equals SOURCE statement order (S1) around the two loads.
// LEVER 2 (12->10, re-validated old 49->47 lever): compute the [0]-store value into a
//   block-local `v0m` BEFORE the [1]=0x6055ff00 statement → mask 0xffffff materializes first.
//   (2-insn split consts have reg_n_sets==2 → never birthing-boosted → they place at the
//   block top in LUID order; the temp reorders the LUIDs.)
// LEVER 3 (10->4, the pin): the residual LOOKED like schedule but was ONE local-alloc
//   first-fit: 0x6055ff00 got $v1 (its window [birth..sw1] missed the $v1 v0m-chain since
//   sched1 had sw1 above the chain); c6055=$v1 then FORCES sw1 above the chain in sched2
//   (hard-reg anti-web: sw1 reads $v1, chain writes $v1) — a self-consistent wrong fixed
//   point. Block-scoped `register u32 c6055 __asm__("$6") = 0x6055ff00;` puts it in $a2
//   (target), sched2's webs relax, and sw1/lhu/retv/move all fall into place (6 insns).
//   RC-5 channels clean: narrow scope, $a2 already ever-live (arg reg), no spills.
// LEVER 4 (4->0): C89 decl-initializer order = LUID order: `u32 v0m = expr;` BEFORE the
//   pinned c6055 decl puts the mask materialization below the pinned lui/ori → the two
//   2-insn const pairs land [mask, 0x6055ff00] at the top like the target.
// Supporting structure (needed, from Ghidra's REAL variable reuse):
//   - `dl` multi-set (both D-loads through one u32 var) → no birthing boost → the lhu's
//     stay at source position (a single-set load var sinks to its consumer).
//   - head uses `(u16)param_2` (zero_extend RTL) vs tail `param_2 & 0xffff` (AND rtl) —
//     different cse hashes → no cross-call CSE → no 7th callee-save; replaces the old
//     volatile-asm barrier (which is a FULL scheduling barrier per sched.c ASM_OPERANDS
//     handling and had warped the tail).
//   - u4/u5 fresh single-set call-result vars (S2 boost → jal delay slots), c3/cb8/cff
//     $s5/$s4/$s3 pins for the 777BC extra args: unchanged from the close draft.
// Negative results (do not retry): unboosting the v0m chain (multi-set va / named+retied
//   t0c / v0m-reuse-as-mul2-t) regresses 10 -> 35..71 — the target NEEDS the inline
//   single-set birthing boosts; a retie on a shared const breaks cse-sharing with literal
//   uses elsewhere (+1 insn) unless ALL uses go through the var.
// Decl-reconcile notes (unchanged): func_80177784 canonical 4-arg called 3-arg
//   (cast_call_sites), func_801777BC INCLUDE_ASM 7-arg, D_8011F830/D_8011F82E u16.

/* /s-cast helper anonymized inline below (self-contained for ×134 propagation) */
#include "../shared/ov/func_801770E0.h"

#include "../shared/ov/func_80177340.h"

#include "../shared/ov/func_8017742C.h"

// @class: regalloc-order (walker-family, §52) — PIN-FREE MATCH (0-off), 67 ins
// Byte-exact via match_one; NO `register __asm__` pins (cookbook §42e safe for the x134 sweep).
//
// Levers that got it to 0 (all pin-free):
//  L-store  (§52 "in-loop-const-in-both-arms" analogue): assign the recomputed base
//           `s0 = param_1 + 0x14` in BOTH if/else arms + a single store after. Keeps the
//           recomputed base live across the branch merge so the p[6]/p[0xa] stores address
//           off the recomputed $s0 — NOT address-CSE'd onto the still-live param base $s1.
//           (A ternary/store-once collapses the base back to $s1+0x1a — the historic residual.)
//  L-layout (§52 lever-1 "mutated-parameter / no derived copy"): use `param_1` directly as
//           the persistent keeper (`... = param_1 + 0x14`) with `s0 = param_1` as the working
//           copy. gcc saves param_1 -> $s1 (keeper) and chains $s0 = $s1 (working), giving the
//           target copy DIRECTION. An explicit `s1` keeper var reverses the chain ($s0=a0;$s1=$s0).
//  L-sched  (RC-1 / K1 declaration-order): declare the param_2 copy `pp` AFTER `s0`. Its pseudo
//           is created after s0's, so sched1 emits the s0 working-copy BEFORE the param_2 save
//           in the prologue (target order: s1, s0, s2, s3). Using param_2 directly saved $s2
//           first and broke the prologue order (4-off).
//  L-call   (block layout): `if (c != 0) { ...; goto docall; }` block form keeps the range
//           checks as the entry fall-through (correct global layout); duplicated func call
//           (both arms) cross-jumps to one block placed after st0 (target order).
//
// Note (fragility): the `pp` decl position is load-bearing for the prologue schedule, and the
// two-call cross-jump reproduces the target's single call block with the arg in the jal delay
// slot. The single-call / branch-only-callit forms invert the whole-function block layout
// (gcc cross-jumps the two `goto`s). Whole-binary gate is the real arbiter.
#include "common.h"
#include "../shared/ov/func_801775E0.h"


#include "../shared/ov/func_801776EC.h"

#include "../shared/ov/func_80177784.h"

#include "../shared/ov/func_801777BC.h"



// @class: regalloc-order
// @stuck: none — MATCH
#include "../shared/ov/func_801778A8.h"


















#include "../shared/ov/func_80177940.h"


#include "../shared/ov/func_80177AD4.h"

/* func_80177B5C - MATCH (147/147 ins), wave23.
 *
 * Seed: .run/near6/func_80177B5C_ils.c (permuter-improved, closeness 7).
 * Two residual clusters remained; both cracked, each by a sourced gcc-2.7.2 mechanism.
 *
 * CLUSTER C (idx 86-89) - the "cl | ((n*8+8) | 0x4000)" re-association.
 *   NOT a cse fold. It happens in the FRONT END: fold-const.c fold(), the `associate:`
 *   arm at :3685. For `A | (X | C)`, split_tree(arg1) (:3759, decomposer at :882) splits
 *   arg1 into var=X / con=C because TREE_CONSTANT(op1) holds, then rebuilds it as
 *   `(A | C) | X` at :3785. Verified in the FIRST RTL dump (t.i.rtl insn 215 already
 *   reads `(ior v1 16384)`), so no RTL-level lever (the cse if/else diamond, tie or
 *   volatile barriers, operand swap, shift-vs-multiply) can ever reach it.
 *   ANTIDOTE: hoist the inner IOR into its own statement. The outer arg1 is then a
 *   VAR_DECL, split_tree returns 0, and the associate arm is skipped. (This function
 *   already proved the shape at `tt = uv | 0x1000; p[3] = cl | tt;`, which matched.)
 *
 *   That exposed a REGALLOC residual: the chain landed in $a3 (`sll a3,a3,3`) instead
 *   of $v0. Cause: `n` was pinned to a HARD reg, and local-alloc.c combine_regs():1798
 *   unconditionally records a dying hard-reg SOURCE in qty_phys_sugg[] for the dest
 *   pseudo, so the shift dest inherited $a3. A *pseudo* source cannot do that - :1763
 *   bails when reg_qty[ureg] < 0 (i.e. not block-local), and the target's `n` crosses
 *   the join, so it is exactly such a pseudo.
 *   ANTIDOTE: move the pin off `n` (which dies into the shift) onto `nn` (the tested
 *   value). `nn` pinned to $2 keeps the two distinct so the `addu $a3,$v0,$zero` copy
 *   survives (combine_regs :1841 refuses to tie when the DEST is non-block-local),
 *   while `n` stays a pseudo and the shift chain gets an ordinary local quantity ->
 *   $v0 - which also restores the target schedule, because the $v0 anti-dependence on
 *   `sw $v0,-0x4($a1)` is what stops sched2 hoisting the chain above the store.
 *   [7 -> 8 -> 3]
 *
 * CLUSTER B (idx 24-27) - `lui $t0,0x300` two slots early.
 *   Pure sched1 LUID tie-break, read straight off the -da trace (t.i.sched, T-36):
 *   ready = { 58 (7f000001), 72 (7f000001), ... } - insn 58 (lui $t0) IS birthing-
 *   boosted (sched.c birthing_insn_p:2469 works on hard regs too; reg_n_sets[$t0]==1),
 *   so 58/71/72 all tie at max_priority and rank_for_schedule:2427 falls through to
 *   DESCENDING LUID. Source order put `ca = 0x3000000;` before the mask, so
 *   LUID(58) < LUID(72) and the lui was placed first.
 *   (The companion mask 0xFFFFFF correctly stays at idx 6-7 because lui+ori is TWO
 *   sets of $t1 -> reg_n_sets==2 -> no boost -> it sinks to the block head. Same
 *   mechanism, opposite sign - the model predicts both.)
 *   ANTIDOTE: split the mask into its own statement (`gg`) and materialise the
 *   constant BETWEEN it and the OR, so expand emits addiu, and, lui, or in that order
 *   and LUID(58) > LUID(72). Sweeping the plain statement position of `ca = ...` was
 *   inert (all 11 slots scored 3) - only interposing the temp moves the LUID past the
 *   AND. [3 -> 0]
 *
 * Dead ends measured, not guessed: pin nv to $2 = 27; reuse tt = 24; reuse uv = 29;
 * two-step |= = 15; unpin n = 84 (146 ins, the copy coalesces away); unpin ca = 139;
 * ca as a bare literal = 139 (145 ins - cse merges it with the loop copy, so the hard
 * pin is what keeps the pre-loop and in-loop constants separate); both literal = 143;
 * `(ca = 0x3000000)` as an assignment-EXPRESSION = 114 (148 ins, extra move); reusing
 * the existing `g` for the mask temp instead of a fresh one = 8 (g has a 2nd set later).
 */
extern u8 D_8018A300[];
u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s16 tbli;
s16 x;
s16 y;
{
    extern u8 D_8018A300[];
    u32 *q;
    u32 v;
    u32 cl;
    u32 cs;
    u32 cl2;
    u32 tt2;
    u32 cs2;
    u32 ca;
    u32 mk1;
    u32 cc1;
    u32 flag;
    u32 n;
    u8 m;
    u16 t;
    s16 i;
    u32 col;
    u32 uv;
    u32 tt;
    u32 nv;
    u32 x1;
    u32 x2;
    u32 gg;
    s32 yt;
    u32 yl;
    u32 c;
    u16 bb;
    u32 c0;
    u32 w;

    mk1 = 0xFFFFFF;
    cc1 = 0x74808080;
    bb = bits;
    t = x + 0xE;
    flag = 0x1000000;
    i = 0;
    v = D_8018A300[tbli];
    gg = ((u32)(p - 5)) & mk1;
    ca = 0x3000000;
    p[0] = gg | ca;
    x1 = (u16)(x - 3);
    x2 = (u16)(x + 5);
    p[1] = cc1;
    yt = y;
    c0 = yt + 1;
    c0 <<= 16;
    w = c0 | x1;
    __asm__("" : "=r"(w) : "0"(w)); // !FAKE: launder w — a second set of w stops sched1 launching the p[2] `or` at its store (birthing_insn_p, sched.c:2469), so it stays ahead of the cl chain and sched2's equal-priority tie (sched.c:2385) keeps that order; no plain spelling does (S103 c19) (P36 S103 c46 minimum-lever)
    c = v << 6;
    c |= 0x4016;
    cl = c << 16;
    p[2] = w;
    p[3] = cl | 0x1800;
    p += 5;
    p[0] = (((u32)(p - 5)) & mk1) | ca;
    p[1] = cc1;
    p[2] = c0 | x2;
    p[3] = cl | 0x1808;
    p += 5;
    q = p;
    yl = yt << 16;
    do {
        n = (u32)(bb << 16) >> 28;
        m = n;
        if (n != 0 || i == 2 || i == 0xFF) {
            flag = 0;
        }
        q[0] = (((u32)(q - 5)) & 0xFFFFFF) | 0x3000000;
        q[2] = (yl | t) | flag;
        col = 0x74808080;
        q[1] = col;
        nv = ((m * 8) + 8) | 0x4000;
        q[3] = cl | nv;
        q += 5;
        t += 8;
        i++;
        bb <<= 4;
    } while (i < 3);
    p = q;
    p[0] = (((u32)(p - 5)) & 0xFFFFFF) | 0x3000000;
    cs = y << 16;
    p[2] = cs | (u16)(x + 0x2A);
    cl2 = ((v << 6) | 0x4016) << 16;
    uv = tbli << 4;
    tt = uv | 0x1000;
    p[1] = col;
    p[3] = cl2 | tt;
    p += 5;
    p[0] = (((u32)(p - 5)) & 0xFFFFFF) | 0x3000000;
    cs2 = cs | (u16)(x + 0x32);
    tt2 = uv | 0x1008;
    p[1] = col;
    p[2] = cs2;
    p[3] = cl2 | tt2;
    p += 5;
    return p;
}

extern u8 D_8018A300[];

void func_80177DA8(p, v, idx)
u8 *p;
u32 v;
s16 idx;
{
    u8 *r;
    u16 c;
    u16 flag;
    u32 n;
    u8 m;
    s16 i;
    u8 t;
    u32 x;
    u32 uv;
    u32 w1;
    u32 w2;

    flag = 0x100;
    i = 0;
    t = D_8018A300[idx];
    c = (t << 6) | 0x4016;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    r = p;
    do {
        n = (v << 16) >> 28;
        m = n;
        if (n != 0 || i == 2 || i == 0xFF) {
            flag = 0;
        }
        v <<= 4;
        i++;
        *(s16 *)(r + 0xA) = flag | (*(s16 *)(r + 0xA) & ~0x100);
        *(u8 *)(r + 0xC) = m * 8 + 8;
        r += 0x14;
    } while (i < 3);
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    x = ((t << 6) | 0x4016) << 16;
    uv = idx << 4;
    w1 = uv | 0x1000;
    *(u32 *)(p + 0xC) = x | w1;
    w2 = uv | 0x1008;
    *(u32 *)(p + 0x20) = x | w2;
}


// @class: regalloc-order
// @unstuck(P36): none — MATCH

#include "../shared/ov/func_80177EA4.h"

// @class: schedule
// @unstuck(P36): none — MATCH (pin hoisted consts 5/$t2 + 0xfeff/$t1 BEFORE the $a2 ptr init fixes prologue order; ==5 uses register c5, but <5 loop-back uses literal 5 -> slti)
#include "common.h"

#include "../shared/ov/func_80177F84.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (full register pins per sibling func_80177EA4; running-ptr $s2 to stop unroll-rebase;
//   literal 0x3000000 (not pinned var) to lazy-schedule its lui after the addiu/and; nx barrier to keep
//   iVar4=nx separate from the test temp; ret-in-$v0 temp + q-barrier to order the post-call move pair)
#include "common.h"


#include "../shared/ov/func_80178004.h"


// @class: iv-combine
// @unstuck(P36): none — MATCH (78 ins, relocation-masked)
//
// KEY LEVERS (byte-gated):
//  1. SINGLE moving pointer (param_1), write record fields as offsets off param_1
//     (NOT a second `puVar3` var — the two-pointer form leaves an unused param_1+0x12
//     init and gcc reanchors the giv anyway).
//  2. GIV ANCHOR = the LAST giv-store in PROGRAM ORDER (gcc loop.c: record_giv PREPENDS
//     to bl->giv, combine_givs makes giv_array[0]=the-last-recorded the base). The target
//     anchors its store giv at param_1+0x12 (all displacements <=0), so the +0x12 store
//     (`*(short*)(param_1+0x12)=8`) MUST be the LAST store before the pointer bump.
//     Moving it last: 15-mismatch -> 3.
//  3. switch case-BODY layout order follows source order: emit 0x1850/0x1858 (the break
//     cases) FIRST, then the 0x3870/0x3871/0x3872 continue cases, then default.
//  4. byte fields read via post-increment: `c=*p2++; ...; d=*p2++;` (target advances
//     param_2 by +1 twice, not +2 once, in the store path).
//  5. <0x861 branch-polarity: write `if (x>=0x861) +=8; else +=7;` so the +=8 (else of
//     the source intent) falls through first and gcc emits `bnez` to the +=7 body (§3-T4).

#include "../shared/ov/func_80178298.h"

#include "../shared/ov/func_801783D0.h"

M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D8E08;

void func_80178438(u16 *arg0) {
    func_8001534C(2, &D_801D8E08, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}

// @class: struct
// @unstuck(P36): none — MATCH (91 ins). Keys: (1) two-pointer do-while over D_801202A0
//   (base ptr p=$s1, derived q=p+0x54=$s0, counter i=$s2) all PINNED via register
//   __asm__ to get the 3-saved-reg frame (0x20) + exact alloc order; (2) the &&-chain
//   if(byte6C!=0 && byte6D!=0) func_80130D0C else fptr -> func_80130D0C is the
//   fall-through THEN block, fptr the jumped-to ELSE (matches the two-beqz target CFG);
//   (3) the indirect-call table base D_8011DB08 PINNED to $v1 ($3) so it reuses store2's
//   freed reg AND HOISTS before the byte6C branch (else block then carries load-delay
//   nops, matching target); (4) byte6C read into a temp PINNED to $v0 ($2), read EARLY
//   (between store1 and store2) so it (a) reuses store1's freed $v0 and (b) lets store3
//   (sw -0x14) become the byte6C-beqz DELAY-SLOT fill instead of a standalone+nop. The
//   reg pins for tbl/c6c are the lever that beat the gcc reorg tie-break (delay-slot
//   packing) — without them the only residual was store3 standalone (+1 nop, 92 ins).

#include "common.h"

#include "../shared/ov/func_8017849C.h"

#include "../shared/ov/func_80178608.h"

#include "../shared/ov/func_8017869C.h"

#include "../shared/ov/func_80178744.h"

#include "../shared/ov/func_801787D4.h"

// @class: regalloc-order
// @unstuck(P36): sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

extern int D_8018A360;
extern int D_8018A36C[];

void func_80178840(int param_1) {
    int p;
    int s1byte;
    int param_12;
    param_12 = param_1;
    p = param_12;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_8018A360);
        }
        ((void (*)(int, int))func_80131E00)(p, D_8018A36C[s1byte]);
    }
}

#include "common.h"

#include "../shared/ov/func_801788B8.h"

// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern s32 func_801789AC(s32 arg0);
extern s16 D_801DAAB8;

int func_80178970(void)
{
    register int r __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_801DAAB8 == 0;
    return r;
}
