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
    s16 x;   /* 0x0 */
    s16 y;   /* 0x2 */
    s16 z;   /* 0x4 */
    s16 pad; /* 0x6 */
} Buf8_8017D4F0;
typedef struct {
    s16 unk0;                /* 0x00 */
    u8 pad[0x102];           /* -> 0x104 */
} St_8017E95C_r;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_801871CC;
extern u8 D_8018713C;
extern u8 D_80187118;
extern u8 D_801870F4;
extern u8 D_801871A8;
extern u8 D_80187184;
extern u8 D_80187160;
extern u8 D_801870D0;
extern void func_80145934(void);
extern u8 D_8018725C;
extern u8 D_80187238;
extern u8 D_80187214;
extern u8 D_801871F0;
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
extern unsigned char D_80186654[];
extern unsigned char D_80186684[];
extern unsigned char D_801866D4[];
extern unsigned char D_80186704[];
extern unsigned char D_80186734[];
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
extern void (*D_80186784[])(void *);
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
extern s32 D_8018684C[];
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
extern u8 D_801868D4[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801868DC;
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
extern int D_801B0138;
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
extern s32 D_801B013C;
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
extern s32 D_8018690C;
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
extern void (*D_801869B4[])(void);
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
extern void (*D_801869D8[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_801869C8;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801869EC[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801869F8[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80186A08[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80186A20[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80186A10;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80186A34[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80186A50[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80186A40;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80186A64[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80186A78[])(void);
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
extern s32 D_80186A8C;
extern void (*D_80186AB4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80186A94;
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
extern int (*D_80186B00[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80186B04[])(void);
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
extern unsigned short D_80186F68[];
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
extern void (*D_80186F78[])(void);
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
extern int D_801B0170;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80186FA0[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80186F80;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80186F90;
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
extern void (*D_80186FE0[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80186FE8[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80186FB4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80186FF4[])(void);
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
extern u8 D_80186FC4;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B0178;
extern s32 D_801B0184;
extern s32 D_801B0188;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187030[])(s32 *);
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
extern s32 D_80187004[];
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
extern s32 D_801B0180;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80187280[])(void);
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
extern char D_801870A0[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80187324[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80187478[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80187294;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80187480[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_801872A4;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_801872C4;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80187488[])(void);
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
extern void (*D_801874B0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_801874BC[])(void);
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
extern void (*D_80187330[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80187560;
extern void func_8015D380(s32 a0);
extern unsigned char D_80186644[];
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
extern unsigned char D_80187574[];
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
extern s8 D_801875B0[];
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
extern u16 D_801875F8;
extern u16 D_801875FA;
extern u16 D_801875FC;
extern s32 D_80187600;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80187608;
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
extern int D_80187314;
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
extern unsigned int D_8018768C[];
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
extern void (*D_8018773C[])(void);
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
extern u16 D_8018776C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_801877D0;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B0190[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801877F4[])(void);
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
extern int D_801B01E8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018783C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018782C;
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
extern char D_801AF9FC[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80187844[])(void);
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
extern void (*D_80187898[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80187860;
extern s16 D_80187894;
extern s16 D_80187892;
extern s16 D_80187890;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801878A4[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B0248;
extern u8 D_801B0249;
extern u8 D_801B024A;
extern u8 D_801B024B;
extern u8 D_801B024C;
extern u8 D_801B024D;
extern u8 D_801B024E;
extern u8 D_801B024F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801878B4[])(void);
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
extern s32 D_801B0288;
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
extern void (*D_801878F8[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80187974[];
extern s32 D_80187994[];
extern u8 D_80187A10[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80187A30[];
extern u8 D_80187A50[];
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
extern void (*D_80187AEC[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80187B68[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801AFA0C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80187B74[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80187B7C[])(void);
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
extern void (*D_80187C44[])(void);
extern void func_80166618(void *a0);
extern void (*D_80187C54[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80187C64[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80187C70[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80187BD0[];
extern u8   D_80187BE4[];
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
extern void (*D_80187C88[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80187C90[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80187C98[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80187CA0[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80187CA8[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80187CB0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80187CB8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80187D6C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80187D74[])(void);
extern void func_80169F00(void *a0);
extern char D_80187D24[];
extern char D_80187CE4[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80187DAC[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80187DB8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B62;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80187E00[])(void);
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
extern void (*D_80187E7C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B05A8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80187E70[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80187EB4[];
extern unsigned short D_80187EBC[];
extern unsigned short D_80187EC4[];
extern unsigned char D_801B05B0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B05A8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80187ECC[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B06E4;
extern M2C_UNK D_801B06E8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B0670;
extern void (*D_80187EFC[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B06EC[];
extern u8 D_801B06F4[];
extern u8 D_801B06A4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80187F04[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80187F20[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80187F28[])(void);
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
extern void (*D_80187F90[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80187F34;
extern u8 D_80187F40;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80187FC4[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80187FCC[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188020[])(void);
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
extern u16 D_80188054[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80188044[];
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
extern s32 D_80188070;
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
extern void (*D_801880E8[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801880F0[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801880F8[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188100[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80188108[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80188110[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018811C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80188128[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80188134[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80188144[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80188154[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018815C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80188164[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018816C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80188174[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018817C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80188184[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018818C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80188194[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018819C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_801881A4[])(void);
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
extern void (*D_801881AC[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801881B4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_801881BC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_801881C4[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_801881CC[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_801881D4[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801881DC[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801881E4[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_801881EC[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801881F4[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801881FC[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80188204[])(void);
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
extern void (*D_80188248[])(void);
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
extern M2C_UNK D_8018820C;
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
extern void (*D_80188278[])(void);
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
extern void (*D_801882B4[])(void);
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
extern void (*D_8018830C[])();
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
extern void (*D_8018831C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80188324[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018848C[])();
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
extern void (*D_80188498[])();
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
extern M2C_UNK D_801AFC54;
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
extern s16 D_801B2210;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B0E28;
extern short D_801B2284;
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
extern s32 D_801B1254;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B127C;
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
extern s16 D_801B1238;
extern s32 func_8017A3B0(void);
extern short D_801B1274;
extern short D_801B1270;
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
extern s16 D_801B123C;
extern u16 D_801B12BC;
extern u16 D_801B12BE;
extern u16 D_801B12C0;
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
extern s16 D_801B12B4;
extern s16 D_801B12B6;
extern s16 D_801B12B8;
extern s16 D_801B12AC;
extern s16 D_801B12AE;
extern s16 D_801B12B0;
extern void func_8017B7A8(void);
extern s16 D_801B12CC;
extern s16 D_801B12CE;
extern s16 D_801B12D0;
extern s16 D_801B12D4;
extern s16 D_801B12D6;
extern s16 D_801B12D8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B12C4;
extern short D_801B12C6;
extern short D_801B12C8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B125C;
extern SV4 D_801B1264;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B1284[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B1280)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80188674[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void func_8002850C(s32, s32, s32);   /* TU-declared: void(s32,s32,s32) */
extern void func_80028620(s32, void *);     /* TU-declared: void(s32,void*) */
extern void func_8002931C(void);            /* fleet-modal spelling (n=19); called via cast below */
extern int func_8017DAF0(int);              /* defined in THIS TU: int func_8017DAF0(int param_1) */
extern s16 D_80188720;
extern s16 D_80188722;
extern s16 D_80188724;
extern Blk16 D_80188728;
extern Blk16 D_80188738;
extern Blk16 D_80188748;
extern Blk16 D_800A5E88[3];
extern u8 D_80189ED8[];
extern u8 D_80189F28[];
extern u8 *D_801274C8;
extern void *D_801274CC;
extern void func_8017CDE4(void);
extern void (*D_80188758[])(void);
extern void func_8017CF00(void *a0);
extern void func_8017D2A0(void);
extern s32 func_8017CF3C(s32 a0);
extern s32 func_8017CF80(void);
extern void (*D_80188760[])(void);
extern void func_8017CFA4(void *a0);
extern void func_8017D2C8(void);
extern s32 func_8017CFE0(s32 a0);
extern s32 func_8017D024(void);
extern void (*D_80188768[])(void);
extern void func_8017D048(void *a0);
extern void func_8017D2F0(void);
extern s32 func_8017D084(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D0C4(u8 *a0);
extern s32 func_800D1EBC(void);
extern void func_8017D140(void);
extern void (*D_80188774[])(void);
extern void func_8017D160(void *a0);
extern void func_8017D350(void);
extern s32 func_8017D19C(s32 a0);
extern s32 func_8017D1DC(void *a0);
extern void func_8002931C(void);
extern void func_80029514(s32 a0);
extern void func_8002AED0(void);
extern s32 func_8017D258(void);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8017D318(void *a0);
extern void func_8012A094(s32 a0);
extern void func_8017D4B4(void *a0);
extern void func_8017D418(void);
extern void (*D_8018879C[])(void);
extern s16 D_80126940;
extern s32 D_801270C8;
extern void func_8017D4F0(void *param_1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D730(s32 param_1, s16 *param_2);
extern void func_8013B7F4(void *a0, int a1);
extern int func_8017DAF0(int param_1);
extern void func_8017DB98(s32 a0, s32 a1);
extern void func_8017DB6C(s32 a0);
extern s32 func_8017DE5C(s32 arg0);
extern void (*D_801887B0[])(void);
extern void func_8017DE9C(void *a0);
extern void func_8017DED8(void *a0);
extern void func_8017E05C(void);
extern void func_8017DF30(void);
extern void func_8017E100(void);
extern s32 D_801B12E4;
extern void func_8017E230(s32);
extern void func_8017DF50(void *arg0);
extern void func_8017E008(void *a0);
extern void func_8017E054(void);
extern u16 func_80148800(s32 *);
extern s32 func_80180ED4(void);
extern s32 D_801B12E8;
extern s32 D_801B12E0;
extern void func_8017E18C(s32 arg0, s16 *arg1, s32 arg2, s32 arg3);
extern void func_8017E230(s32 a0);
extern void func_8012DFD4(void *a0);
extern void func_8017E290(void *a0);
extern s32 D_801887C4;
extern void func_8017E430(s32 *a0);
extern void func_8017E4D8(void);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern OtBlk D_800A651C[];
extern void func_8017E4E0(void *a0);
extern void func_8012C218(void *a0);
extern void func_8017E648(void *a0);
extern s32 D_801270CC;
extern s16 D_801B1700;
extern s16 D_801B1704;
extern s16 D_801B1708;
extern s16 D_801B170C;
extern s16 D_801B1710;
extern s16 D_801B1714;
extern s16 D_801B1718;
extern s16 D_801B171C;
extern s16 D_801B1720;
extern s16 D_801B1724;
extern s16 D_801B1728;
extern s16 D_801B172C;
extern s16 D_801B1730;
extern s16 D_801B1734;
extern s16 D_801B1738;
extern s16 D_801B173C;
extern s16 D_801B1740;
extern s16 D_801B1744;
extern s16 D_801B1748;
extern s16 D_801B174C;
extern s32 D_801B1B54;
extern void func_8017E95C();
extern void func_8017E9B8(void);
extern s32 func_8017EEC4();
extern void func_8017F580();
extern void func_8017F894();
extern void func_80181BC8();
extern void func_801817A8();
extern void func_8017E6C0(void *a0);
extern St_8017E95C_r D_801B12F0[4];
extern St_8017E95C_r D_801B12F8[4];
extern void func_8017E95C(void);
extern void (*D_801888B8[])();
extern void func_80181E08(s32 arg0);
extern s32 func_8012E544(s32 a0);
extern void func_8012B0B4(u32 *a0, s32 a1, s32 a2);
extern s32 func_80182090(s32, s32);
extern void func_80181CA4();
extern void func_8017ED5C(s32 a0);
/* ==== end §8b carried decl layer ==== */


extern s16 D_801B1738;

typedef struct {
    s16 x, y, z, pad;
} V_8017EEC4;

extern void func_8017EF94(V_8017EEC4 *a0, s32 a1);

s32 func_8017EEC4(void) {
    V_8017EEC4 v;
    s32 rec;

    rec = func_8012E544(0x2CD);
    if (rec != 0) {
        switch (*(u16 *)(rec + 0x2)) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            D_801B1738 = 1;
            break;
        case 1:
        case 7:
        case 8:
            D_801B1738 = 0;
            break;
        }
        if (D_801B1738 != 0) {
            v.x = *(u16 *)(rec + 0x6);
            v.y = *(u16 *)(rec + 0xA);
            v.z = *(u16 *)(rec + 0xE);
            v.y -= 0x50;
            func_8017EF94(&v, 0);
            func_8017EF94(&v, 1);
            func_8017EF94(&v, 2);
        }
    }
}


/* func_8017EF94 (ov_SC06_025, 292 ins) -- MATCH, 0 mismatched (match_one, masked).
 *
 * Split-quad billboard draw: project 4 corners of D_8018890C[arg1][], then emit either one
 * quad, or two quads split at screen y == 0x100 with the shared edge interpolated.
 *
 * TWO residuals remained on the carried backlog draft; both are now closed, and both are
 * SOURCE-SHAPE facts, not scheduling:
 *
 *  (1) idx 59-62 -- the `lui/addiu $fp` symbol pair must emit BEFORE the `lw 0x5C($sp)` flag
 *      load (whose shadow the target fills with the maspsx hazard `nop`, because the delay-slot
 *      filler steals the `li $s5,0x28` that used to fill it).  The fix is NOT a fence (§194-A's
 *      AFTER-placement asm was tried: 294 ins) -- it is STATEMENT POSITION (§176-A / §3-T2):
 *      `h = 0x28;` belongs in the POST-call-1 block, after `q = &D_801B1B58;`.  With `h = 0x28`
 *      in the pre-call block the `li` still lands in the delay slot but the la pair sinks below
 *      the load, and sy/h swap $s4/$s5.
 *
 *  (2) idx 251-252 -- `li $v0,0x28 / subu $v0,$v0,$s0` where the target has `subu $v0,$s5,$s0`.
 *      NEW LAW (see note below): `D_801B1B58.h = h - n;` with an s16 field narrows in the FRONT
 *      END -- convert.c:269-317 `convert_to_integer` distributes the SI->HI truncation into the
 *      operands of a PLUS/MINUS/AND/IOR/XOR, so the RTL is
 *          (set (reg:HI A) (subreg:HI (reg h)))          <- a HImode COPY of h
 *          (set (reg:HI B) (subreg:HI (reg n)))
 *          (set (reg:SI C) (minus (subreg:SI A) (subreg:SI B)))
 *      and cse then rewrites that COPY's source to the constant, because COST(const_int)=0 <
 *      COST(pseudo)=1 (cse.c:481 COST / 5222-5250 fold_rtx's cheapest-operand replacement).
 *      A copy cannot be coalesced once it is a `li`, so the store costs 2 insns.
 *      Assigning through an s32 temp (`hh = h - n; D_801B1B58.h = hh;`) leaves the subtraction
 *      SImode: cse then tries to fold the constant into the `minus` itself, and validate_change
 *      REJECTS it (mips.md subsi3 wants reg_or_0_operand), so `h` survives in $s5.  The extra
 *      reference also lifts h's allocno rank back over sy's, restoring $s4/$s5.
 *
 * Cookbook sections that unlocked the rest: §167-10 (signed-narrow lvalue compared then re-read
 * = one `move` + 8 bytes of frame -- the two x-guards must read sp30.x directly, not a hoisted
 * s32), §195-M (the frame walk: 32-byte dead leading aggregate `pre[8]` + 5 orphans = vars 120),
 * §229 (naming the address births the $fp pseudo), §L22980 (lhu vs lh per access, u16-vs-s16),
 * §3-I4 (the variable divisor's break 7 / break 6 guards).
 *
 * V_8017EEC4 is the TU's own typedef (already at file scope above func_8017EEC4); it is spelled
 * here verbatim for the standalone compile and harvest_verify strips it at splice time.
 */
#include "common.h"
extern void func_8012EF70(s32 a0, s32 a1);


typedef struct { s16 vx, vy; } DV_8017EF94;
typedef struct { s16 vx, vy, vz, pad; } SV_8017EF94;
typedef struct {
    s16 x, y, w, h;
    union { DV_8017EF94 d; s32 w32; } v[4];
} Quad_8017EF94;

extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_8017F424(s16 *);
extern short D_800B9A02;
extern SV_8017EF94 D_8018890C[][4];
extern Quad_8017EF94 D_801B1B58;
extern s32 D_801B1B74;

void func_8017EF94(V_8017EEC4 *arg0, s32 arg1) {
    s32 pre[8];
    V_8017EEC4 sp30;
    SV_8017EF94 out[4];
    s32 p;
    s32 flag;
    s32 t;
    s32 r, total;
    s32 sx, sy;
    s32 n, h, w, hh;
    Quad_8017EF94 *q;

    func_8012EF70((s32)arg0, (s32)&sp30);
    if ((u32)(sp30.x + 0x77) >= 0x13F) {
        return;
    }
    if ((u32)(sp30.x + 0xC7) >= 0x13F) {
        return;
    }
    if ((u32)(sp30.y + 0x63) >= 0xEF) {
        return;
    }
    if ((u32)(sp30.y + 0x8B) >= 0xEF) {
        return;
    }
    sp30.x = sp30.x + 0x78;
    if (*(u16 *)&D_800B9A02 != 0) {
        t = sp30.y + 0x64;
    } else {
        t = sp30.y + 0x154;
    }
    sp30.y = t;
    if (sp30.y <= 0) {
        sp30.y = 0;
    }
    w = 0x50;
    sx = sp30.x;
    sy = sp30.y;

    r = RotTransPers((s32)&D_8018890C[arg1][0], (s32)&out[0], &p, &flag);
    total = r;
    q = &D_801B1B58;
    h = 0x28;
    if (flag < 0) {
        return;
    }
    if (r <= 0) {
        return;
    }
    r = RotTransPers((s32)&D_8018890C[arg1][1], (s32)&out[1], &p, &flag);
    total += r;
    if (flag < 0) {
        return;
    }
    if (r <= 0) {
        return;
    }
    r = RotTransPers((s32)&D_8018890C[arg1][2], (s32)&out[2], &p, &flag);
    total += r;
    if (flag < 0) {
        return;
    }
    if (r <= 0) {
        return;
    }
    r = RotTransPers((s32)&D_8018890C[arg1][3], (s32)&out[3], &p, &flag);
    total += r;
    if (flag < 0) {
        return;
    }
    if (r <= 0) {
        return;
    }
    D_801B1B74 = total / 4;
    if (sy < 0x100 && sy + 0x28 >= 0x100) {
        n = 0xFF - sy;
        if (n > 0) {
            q->x = sx;
            D_801B1B58.y = sy;
            D_801B1B58.w = w;
            D_801B1B58.h = n;
            D_801B1B58.v[0].d.vx = out[0].vx;
            D_801B1B58.v[1].d.vx = out[1].vx;
            D_801B1B58.v[2].d.vx = out[2].vx;
            D_801B1B58.v[3].d.vx = out[3].vx;
            D_801B1B58.v[0].d.vy = out[0].vy;
            D_801B1B58.v[1].d.vy = out[1].vy;
            D_801B1B58.v[2].d.vy = out[0].vy + (out[2].vy - out[0].vy) * n / h;
            D_801B1B58.v[3].d.vy = out[1].vy + (out[3].vy - out[1].vy) * n / h;
            func_8017F424((s16 *)q);
        }
        {
        Quad_8017EF94 *d2 = q;
        d2->x = sx;
        D_801B1B58.y = 0x100;
        D_801B1B58.w = w;
        hh = h - n;
        D_801B1B58.h = hh;
        D_801B1B58.v[0].d.vx = out[0].vx;
        D_801B1B58.v[1].d.vx = out[1].vx;
        D_801B1B58.v[2].d.vx = out[2].vx;
        D_801B1B58.v[3].d.vx = out[3].vx;
        D_801B1B58.v[0].d.vy = out[0].vy + (out[2].vy - out[0].vy) * n / h;
        D_801B1B58.v[1].d.vy = out[1].vy + (out[3].vy - out[1].vy) * n / h;
        D_801B1B58.v[2].d.vy = out[2].vy;
        D_801B1B58.v[3].d.vy = out[3].vy;
        func_8017F424((s16 *)d2);
        }
    } else {
        Quad_8017EF94 *d1 = q;
        d1->x = sx;
        d1->y = sy;
        d1->w = w;
        d1->h = h;
        d1->v[0].w32 = *(s32 *)&out[0];
        d1->v[1].w32 = *(s32 *)&out[1];
        d1->v[2].w32 = *(s32 *)&out[2];
        d1->v[3].w32 = *(s32 *)&out[3];
        func_8017F424((s16 *)d1);
    }
}


#include "common.h"

/* func_8017F424 (ov_SC06_025, 87 ins) -- MATCH, relocation-masked (tools/match_one.py).
 *
 * Builds one POLY_FT4 (0x28) from an 0x20-byte sprite descriptor and hangs it on the OT:
 *   src+0x00 u16 : tpage-x source; low 6 bits are u0/u2, &0xFFC0 -> GetTPage arg2
 *   src+0x02 u16 : tpage-y source; low byte is v0/v1,   &0xFF00 -> GetTPage arg3
 *   src+0x04/0x06 u8 : the u/v spans added onto u0/v0 for the far corners
 *   src+0x08..0x17   : the four already-projected xy words -> p+8/0x10/0x18/0x20
 *   src+0x1C   s32   : otz handed to func_801823D4(otz, -0x1A)
 *
 * BANKING NOTE (§376/§378): the TU already carries `extern s32 func_8017F424(s16 *);` (:2899)
 *   and the definition here agrees with it verbatim -- do NOT let sig_unify widen the parameter.
 *   The `s32` return is real: the function falls out of AddPrim with $v0 live and the TU's decl
 *   says s32; there is no explicit `return`, and adding one costs nothing but is not what the
 *   original wrote.  Every extern below is already declared IDENTICALLY in the TU
 *   (:2755 GetTPage, :2759 D_800A651C, :4936 func_80010A08, :4939 AddPrim, :4942 func_801823D4,
 *   :2467/:4944 D_800B9A02) except GetClut, which the TU does not declare at all -- the spelling
 *   used here is the fleet canon `extern s32 GetClut(s32, s32);` (src/800.c:4195/:4349/:4686).
 *   The local `OtBlk` typedef is the standard strip-on-bank copy: see the identical note on
 *   func_8017F788 / func_8017FB50 in this same TU.
 *
 * Structure notes:
 *   - The frame is 0x48 (= 0x10 outgoing args + 0x10 rounded gp saves + 40 vars) but NOTHING in
 *     the body touches $sp.  Those 40 bytes are a DECLARED-but-unreferenced aggregate -- cookbook
 *     §333.  Read straight off the frame arithmetic before drafting; without `dead[40]` the
 *     prologue/epilogue and every save offset are wrong.
 *   - u0/v0 live in temps because the target loads src+0 and src+2 ONCE (`lbu $v1` / `lbu $a0`
 *     held across every store), while src+4 and src+6 are RE-LOADED for the 0x24/0x25 corner:
 *     gcc-2.7.2 has no type-based aliasing, so the u8 stores through `p` kill the cse of any
 *     src read that is spelled inline.  Spelling all four inline costs 2 extra loads; hoisting
 *     src+4/src+6 into temps costs 2 loads the other way.
 *   - src+0 is read BOTH as u16 (`lhu`, for the GetTPage &0xFFC0 arg) and as u8 (`lbu`, for
 *     the &0x3F u-coordinate).  Two widths at one address = two differently-cast reads in C;
 *     a single u16 read + `(u8)` cast gives `lhu`+`andi 0xFF` instead of `lbu`.
 *   - uv store order is the natural u0,v0,u1,v1,u2,v2,u3,v3; sched1 floats the two independent
 *     stores (p+0x15, p+0x1C) up to fill the `lbu $v0,4($s1)` load-use delay.
 */

/* engine_types.h:525 `OtBlk` VERBATIM (typedef struct { s32 a; s32 b[4]; } OtBlk;).  match_one's
 * standalone -Iinclude compile cannot reach engine_types.h (only the real TU does, via
 * engine_core.h), so restate it locally -- see func_8017F788 / func_8017FB50 in this same TU. */


extern void *func_80010A08(s32);
extern s32 GetClut(s32, s32);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_801823D4(s32, s32);
extern s32 AddPrim(s32, void *);
extern OtBlk D_800A651C[];
extern short D_800B9A02;

s32 func_8017F424(s16 *param_1)
{
    u8 *p;
    u8 *s;
    u8 u0;
    u8 v0;
    s32 otz;
    u8 dead[40];   /* §333: .frame is 0x48 = 0x10 args + 0x10 saves + 40 vars */

    s = (u8 *)param_1;
    p = (u8 *)func_80010A08(0x28);
    *(u16 *)(p + 0x0E) = GetClut(0, 0x1F0);
    *(u16 *)(p + 0x16) = GetTPage(2, 0,
                                  (s16)(*(u16 *)(s + 0) & 0xFFC0),
                                  (s16)(*(u16 *)(s + 2) & 0xFF00));
    *(p + 3) = 9;
    *(s32 *)(p + 4) = 0x606060;
    *(p + 7) = 0x2C;

    u0 = s[0] & 0x3F;
    v0 = s[2];
    p[0x0C] = u0;
    p[0x0D] = v0;
    p[0x14] = u0 + s[4];
    p[0x15] = v0;
    p[0x1C] = u0;
    p[0x1D] = v0 + s[6];
    p[0x24] = u0 + s[4];
    p[0x25] = v0 + s[6];

    *(s32 *)(p + 0x08) = *(s32 *)(s + 0x08);
    *(s32 *)(p + 0x10) = *(s32 *)(s + 0x0C);
    *(s32 *)(p + 0x18) = *(s32 *)(s + 0x10);
    *(s32 *)(p + 0x20) = *(s32 *)(s + 0x14);

    otz = func_801823D4(*(s32 *)(s + 0x1C), -0x1A);
    AddPrim(D_800A651C[(u16)D_800B9A02].a + otz * 4, p);
}


#include "common.h"

extern s32 func_8012E544(s32 a0);
extern s32 rand(void);
extern u16 D_800B99DA;
extern s16 D_801B1734;
extern void (*D_8018896C[])(void);
extern void func_8017F664(s32 a0, s32 a1);

void func_8017F580(void) {
    s16 buf[3];
    s32 rec;
    s32 i;
    s32 fn;

    rec = func_8012E544(0x2CD);
    if (rec != 0 && *(u16 *)(rec + 2) == 4 && *(u16 *)(rec + 0x34) == 2) {
        if ((D_800B99DA & 0x1F) == 0) {
            D_801B1734 = rand() % 6;
        }
        fn = D_8018896C[D_801B1734];
        for (i = 0; i < 6; i++) {
            func_8017F664(i, fn);
        }
    }
}


#include "common.h"

/* 8-byte, alignment-2 struct: block-assign between two of these (or global<->local)
 * always emits lwl/lwr+swl/swr on this compiler (§48-C2 — align 1 AND align 2 both
 * fall through to the unaligned move; only align>=4 gets lw/sw). Individual field
 * accesses stay plain lhu/sh because each u16 field is itself naturally 2-aligned. */
typedef struct {
    u16 unk0;
    s16 unk2;
    u16 unk4;
    u16 unk6;
} V16x4;

extern V16x4 D_80188984[];
extern u16 D_80188994[];
extern u16 D_800B99DA;
extern void func_8017F788(void *a0, void *a1, s32 a2);

void func_8017F664(s32 a0, s32 a1) {
    V16x4 a;
    V16x4 b;
    s32 idx;
    s32 delta;

    idx = a0 & 1;
    a = D_80188984[idx];
    b = a;

    b.unk2 = -0x178;
    b.unk4 -= 0x100;

    if (idx) {
        delta = ((D_800B99DA & 7) - 3) * 48;
        b.unk0 = b.unk0 - delta;
    } else {
        delta = ((D_800B99DA & 7) - 3) * 48;
        b.unk0 = b.unk0 + delta;
    }

    b.unk0 += D_80188994[a0];

    func_8017F788(&a, &b, a1);
}


#include "common.h"

/* engine_types.h:525 `OtBlk` VERBATIM (typedef struct { s32 a; s32 b[4]; } OtBlk;).  match_one's
 * standalone -Iinclude compile cannot reach engine_types.h (only the real TU does, via
 * engine_core.h), so restate it locally -- see func_8017FB50 / func_80181E08 in this same TU. */


/* LINE_F2 packet, 0x10 bytes: tag(4) + rgb/code(4, code byte at +3) + xy0(4) + xy1(4). */
typedef struct {
    s32 tag;   /* 0x00 */
    s32 rgb;   /* 0x04   code byte lives at +3 of this word */
    s32 xy0;   /* 0x08 */
    s32 xy1;   /* 0x0C */
} LineF2;

extern void *func_80010A08(s32);
extern void func_8012E32C(void);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_801823D4(s32, s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);
extern OtBlk D_800A651C[];
extern short D_800B9A02;

void func_8017F788(void* param_1, void* param_2, s32 param_3)
{
    LineF2 *obj;
    s32 p;
    s32 flag;
    s32 otz;

    obj = (LineF2 *)func_80010A08(0x10);
    obj->rgb = param_3;
    *((u8 *)obj + 7) = 0x42;
    obj->tag = 0x03000000;
    func_8012E32C();

    otz = RotTransPers(param_1, (s32)&obj->xy0, &p, &flag);
    if (otz > 0 && flag >= 0) {
        if (RotTransPers(param_2, (s32)&obj->xy1, &p, &flag) > 0 && flag >= 0) {
            otz = func_801823D4(otz, -0x1A);
            AddPrim(D_800A651C[(u16)D_800B9A02].a + otz * 4, obj);
            func_8012E28C(otz, 1);
        }
    }
}


#include "common.h"

extern s32 func_8012E544(s32 a0);
extern void func_8017F9D8(s32 param_1);
extern s16 D_801B1730;
extern s16 D_801889A8;
extern s16 D_801889AA[];

void func_8017F894(void) {
    s32 rec;
    u16 *p;
    s32 off;
    s32 i;
    s32 idx;
    s32 counter;
    s32 term;

    rec = func_8012E544(0x2CD);
    if (rec == 0) {
        return;
    }
    if (*(u16 *)(rec + 2) != 4) {
        D_801B1730 = 0;
        return;
    }
    if (*(u16 *)(rec + 0x34) != 2) {
        D_801B1730 = 0;
    }
    D_801B1730 = D_801B1730 + 1;
    if (D_801B1730 >= 500) {
        D_801B1730 = 0;
    }
    if (D_801889A8 != -1) {
        i = 0;
        counter = D_801B1730;
        term = -1;
        p = (u16 *)&D_801889A8;
        off = 0;
        do {
            if ((s16)*p / 2 == counter) {
                func_8017F9D8((s32)*(s16 *)((u8 *)D_801889AA + off));
                idx = i << 2;
                goto found;
            }
            p += 2;
            off += 4;
            i++;
        } while (*(s16 *)p != term);
        idx = i << 2;
found:
        if (*(s16 *)((u8 *)&D_801889A8 + idx) != -1) {
            return;
        }
    }
    func_8017F9D8(0);
}


#include "common.h"

extern s16 D_801B1728;
extern s16 D_801B172C;
extern s32 D_8018899C[];
extern void func_8012E32C(void);
extern void func_8017FB50(s32, s32);

void func_8017F9D8(s32 param_1) {
    u8 arr[16];
    u8 *top;
    u8 *base;
    u8 *end;
    s32 *tbl;
    s32 i;
    u8 val;

    if (param_1 < 0) {
        param_1 = 0;
    } else if (param_1 >= 8) {
        param_1 = 7;
    }
    if (D_801B1728 < param_1) {
        D_801B1728 = param_1;
        D_801B172C = 2;
    } else {
        D_801B172C = D_801B172C - 1;
        if ((s32)(D_801B172C << 16) <= 0) {
            D_801B172C = 2;
            D_801B1728 = D_801B1728 - 1;
            if ((s32)(D_801B1728 << 16) <= 0) {
                D_801B1728 = 0;
            }
        }
    }

    top = &arr[7];
    base = &arr[8];
    end = (u8 *)((s32)param_1 + (s32)base);
    do {
        val = (s32)base <= (s32)end;
        *base = val;
        *top = val;
        top--;
        base++;
    } while ((s32)base < (s32)&arr[16]);

    if (D_801B1728 != 0) {
        arr[8 + D_801B1728] = 2;
        arr[7 - D_801B1728] = 2;
    }

    i = 0;
    func_8012E32C();
    tbl = D_8018899C;
    for (; i < 16; i++) {
        if (arr[i] != 0) {
            ((void (*)(void *, s32))func_8017FB50)((void *)i, tbl[arr[i]]);
        }
    }
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h, where the
 * real TU's SVECTOR {short vx,vy,vz,pad;} and OtBlk {s32 a; s32 b[4];} live (via
 * ../shared/engine_core.h). Function-scoped local names so they collide with nothing;
 * integrator should drop these and use the TU's own SVECTOR/OtBlk when banking. */
typedef struct { short vx, vy, vz, pad; } SVEC_8017FB50;
/* engine_types.h:525 `OtBlk` VERBATIM (typedef struct { s32 a; s32 b[4]; } OtBlk;).  The real TU
 * reaches it through engine_core.h -> engine_types.h, so the bank driver strips this local copy;
 * match_one's standalone -Iinclude compile cannot see that header, hence the restatement.  Spelled
 * IDENTICALLY in every draft of this wave that touches D_800A651C (func_8017E4E0 / func_8017FB50 /
 * func_80181E08) so the merged TU ends with one declaration of the symbol (wave law 4).  The
 * array-of-struct form is load-bearing: the raw-word `extern s32 D_800A651C;` + &-arithmetic
 * spelling costs the %lo fold (lui $at/addu/lw %lo -> la + addu + lw) inside a loop. */

extern OtBlk D_800A651C[];

extern void *func_80010A08(s32);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 AddPrim(s32, void *);
extern s32 func_801823D4(s32, s32);
extern short D_800B9A02;
extern SVEC_8017FB50 D_801889EC;

void func_8017FB50(s32 arg0, s32 arg1)
{
    void *obj;
    SVEC_8017FB50 base;
    SVEC_8017FB50 v[4];
    s32 i;
    s32 tmp;
    s32 idx;

    obj = func_80010A08(0x18);

    *(u8 *)((u8 *)obj + 3) = 5;
    *(s32 *)((u8 *)obj + 4) = arg1;
    *(u8 *)((u8 *)obj + 7) = 0x28;

    base = D_801889EC;
    base.vx = base.vx + arg0 * 40;
    base.vy = base.vy;
    base.vz = base.vz;

    for (i = 1; i < 4; i++) {
        v[i - 1] = base;
    }

    v[0].vx = v[0].vx + 0x20;
    v[0].vy = v[0].vy;
    v[0].vz = v[0].vz;
    v[1].vx = v[1].vx;
    v[1].vy = v[1].vy + 0x10;
    v[1].vz = v[1].vz;
    v[2].vx = v[2].vx + 0x20;
    v[2].vy = v[2].vy + 0x10;
    v[2].vz = v[2].vz;

    {
        register s32 *flag_out __asm__("$17") = (s32 *)&v[3] + 1;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus9)
        register s32 *p_out __asm__("$18") = (s32 *)&v[3];  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
        tmp = RotTransPers((s32)&base, (s32)((u8 *)obj + 8), p_out, flag_out);
        RotTransPers((s32)&v[0], (s32)((u8 *)obj + 0xC), p_out, flag_out);
        RotTransPers((s32)&v[1], (s32)((u8 *)obj + 0x10), p_out, flag_out);
        RotTransPers((s32)&v[2], (s32)((u8 *)obj + 0x14), p_out, flag_out);
    }

    idx = func_801823D4(tmp, -0x1A);

    AddPrim(D_800A651C[(u16)D_800B9A02].a + idx * 4, obj);
}


#include "common.h"

/* func_8017FD28 (ov_SC06_025, 137 ins) -- MATCH, relocation-masked (tools/match_one.py).
 *
 * BANKING NOTE (read before gating -- this draft CANNOT compile in the TU as-is):
 *   The definition MUST return s32.  Every `return 1/2/0` is a real target instruction
 *   (`addiu $v0,1` @8017FD7C, `addiu $v0,2` @8017FD84/8017FF1C, the shared `addu $v0,$zero,$zero`
 *   @8017FF30).  Compiled `void` it drops to 128 ins -- byte-tested, -9.
 *   But ov_SC06_025_jr_8017EEC4.c already carries TWO declarations of this symbol that a
 *   `s32` definition conflicts with (cc1 exit 33, `conflicting types for func_8017FD28`):
 *       :3107  extern void func_8017FD28();      (file scope)
 *       :3225  extern void func_8017FD28();      (block scope, in func_801805BC)
 *   Both call sites ALREADY cast (`((s32 (*)(...))func_8017FD28)(...)`), so the fix is the
 *   §17a-1 same-function direction: tools/normalize_self_decls.py, or simply flip those two
 *   `void` -> `s32`.  DO NOT let sig_unify rewrite this def to the fleet-canonical
 *   `void func_8017FD28(s32)` -- that canon is the §238 homonym from ov_SC03_010/011 +
 *   engine_core.h, a DIFFERENT function at the same address; it costs the match.
 *
 * Structure notes:
 *   - `row` (the 8-byte D_80188CA4 pair) MUST be a local pointer: spelling the two accesses as
 *     D_80188CA4[arg1][0/1] re-folds the global address into each MEM (lui $at/addu $at) and
 *     costs 2 ins; the target computes the row into $a1 once.
 *   - q[arg2] is read TWICE on purpose (lhu for the 0xDE store, lh for the *8 index): the
 *     intervening store to (s0+0xDE) kills the cse of the halfword, but not of the ADDRESS.
 *   - v is read straight out of an s16 array: the lhu + sll16/sra16 (rather than one `lh`) is
 *     combine keeping the shifted temp alive because `v / 2` reuses it as the sign bit
 *     (`srl $v0,$a3,31` @8017FDA0).  Do not "simplify" the read.
 *   - ONE trailing `return 0;` with an else-if chain: that is what builds the shared
 *     .L8017FF30 (`addu $v0,$zero,$zero`) the >=6 and >0 arms `j` to, and what lets the
 *     delay-slot filler retarget the other two arms to .L8017FF34 with $v0=0 in the slot.
 *     Per-arm `return 0;` statements cost an extra `move $v0,$zero`.
 *   - Call-arg globals are written as the argument expression, NOT hoisted to a temp: the temp
 *     forces `lw $v1` + `move $a1,$v1`; sched1 legally floats the arg load above the
 *     D_801B1740/D_801B1744 store (different symbols) to reach the target's `lw $a1` form.
 */
s32 func_8017FD28(void *arg0, s32 arg1, s32 arg2) {
    extern s16 *D_80188CA4[][2];
    extern void *D_80188CBC[];
    extern void *D_80188D0C[];
    extern u8 D_80189054[];                        /* TU spelling, :4597 */
    extern s16 D_801B1724;
    extern s16 D_801B1740;
    extern s16 D_801B1744;
    extern void func_8012A828(s32 a0, void *a1);   /* TU spelling, :3475/:4416 */
    extern void func_8012AD80(s32 a0);             /* TU spelling, :3393 */
    extern s32 func_8012B744();                    /* unspecified params: the TU calls it with
                                                    * ONE arg at :3876 */
    extern void func_80181B90(s32 a0);             /* TU definition, :3934 */
    extern void func_8017FF4C(s32 arg0, s16 *arg1, s32 arg2);  /* TU definition, :3069 */
    extern s32 rand(void);                         /* TU spelling, :2854 */

    s32 s0;
    s16 **row;
    s16 *q;
    s16 *pp;
    s32 v;
    s32 diff;
    s32 r;

    row = D_80188CA4[arg1];
    v = row[0][arg2];
    s0 = (s32)arg0;
    if (v <= 0) {
        if (D_801B1724 != 0) {
            return 2;
        }
        return 1;
    }
    q = row[1];
    *(s16 *)(s0 + 0xDE) = q[arg2];
    diff = v / 2 - *(s32 *)(s0 + 0x1C);
    pp = (s16 *)&D_80189054[q[arg2] * 8];
    if (diff >= 6) {
        if (D_801B1744 != 1) {
            D_801B1744 = 1;
            func_8012A828(s0, D_80188D0C[D_801B1740]);
        }
        *(s16 *)(s0 + 0xA) = -0x1EE;
        *(s16 *)(s0 + 0x8) = 0;
    } else if (diff == 5) {
        r = rand() % 3;
        D_801B1740 = r;
        func_8012A828(s0, D_80188CBC[r]);
        D_801B1744 = 0;
        func_8012B744((void *)(s0 + 4), pp);
        func_8017FF4C(s0, pp, 5);
    } else if (diff > 0) {
        func_8012AD80(s0);
        if (*(s16 *)(s0 + 0xA) >= -0x1ED) {
            *(s16 *)(s0 + 0xA) = -0x1EE;
        }
    } else {
        func_8012AD80(s0);
        if (*(s16 *)(s0 + 0xA) >= -0x1ED) {
            *(s16 *)(s0 + 0xA) = -0x1EE;
        }
        *(s16 *)(s0 + 0xA) = -0x1EE;
        *(s16 *)(s0 + 0x8) = 0;
        func_80181B90(*(s16 *)(s0 + 0xDE));
        if (D_801B1724 != 0) {
            return 2;
        }
        *(u16 *)(s0 + 0xDC) += 1;
    }
    return 0;
}


extern s32 D_80188A00;

void func_8017FF4C(s32 arg0, s16 *arg1, s32 arg2) {
    s32 t0;
    s32 a3;
    s32 a1;
    s32 a0r;
    s32 a2v;
    s32 var;

    t0 = arg0;
    a3 = arg2;
    if (a3 <= 0) {
        a3 = 1;
    }
    a1 = ((arg1[0] - *(s16 *)(t0 + 6)) << 16) / a3;
    a0r = ((arg1[2] - *(s16 *)(t0 + 0xE)) << 16) / a3;
    a2v = D_80188A00;
    var = (-a2v / 2) * a3;
    *(s32 *)(t0 + 0x44) = 0;
    *(s32 *)(t0 + 0x4C) = 0;
    *(s32 *)(t0 + 0x48) = a2v;
    *(s32 *)(t0 + 0x14) = var;
    *(s32 *)(t0 + 0x10) = a1;
    *(s32 *)(t0 + 0x18) = a0r;
}



typedef struct { u8 b[16]; } Blk16A1;

extern s16 D_801B1B8C;
extern s16 D_801B1B88;
extern s16 D_801B1B82;
extern s16 D_801B1B7A;
extern s16 D_801B1B7C;
extern Blk16A1 D_801B1B78;
extern Blk16A1 D_80188D30;
extern Blk16A1 D_80188D40;

void func_80180020(void) {
    s16 st;
    s16 next;
    u8 pad8[8];

    st = D_801B1B8C;
    switch (st) {
    case 0:
        next = D_801B1B88 + 1;
        D_801B1B88 = next;
        if (next < 0x46) return;
        {
            s16 v0 = st + 1;
            D_801B1B88 = 0;
            D_801B1B8C = v0;
        }
        return;
    case 1:
        {
            s32 a1 = D_801B1B88;
            D_801B1B82 = 0x380 - ((a1 * 0x200) / 90);
            D_801B1B7A = 0x20 - ((a1 * 96) / 90);
            D_801B1B7C = ((a1 * 0x80) / 90) - 0x80;
            next = a1 + 1;
        }
        D_801B1B88 = next;
        if (next < 0x5A) return;
        {
            s16 v1 = st + 1;
            D_801B1B88 = 0;
            D_801B1B8C = v1;
        }
        return;
    case 2:
        next = D_801B1B88 + 1;
        D_801B1B88 = next;
        if (next < 0x46) return;
        {
            s16 v2 = st + 1;
            D_801B1B78 = D_80188D30;
            D_801B1B88 = 0;
            D_801B1B8C = v2;
        }
        return;
    case 3:
        next = D_801B1B88 + 1;
        D_801B1B88 = next;
        if (next < 0x46) return;
        {
            s16 v3;
            D_801B1B78 = D_80188D40;
            v3 = 2;
            D_801B1B88 = 0;
            D_801B1B8C = v3;
        }
        return;
    }
}


/* Declarations are BLOCK-scope on purpose (this TU's house style, cf. the
 * block-scope decl layers at func_80180300 and neighbours in this file).
 * A file-scope prototype for func_8012A828 here would become visible to
 * func_80181C74, which deliberately calls `func_8012A828()` with no
 * arguments behind a no-prototype decl -- a file-scope prototype turns that
 * call into a hard `too few arguments` error and fails the whole-binary gate
 * even though this function itself is byte-identical. */
s32 func_80180284(void)
{
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_80029124(s32 a0, s32 a1);
    extern s32 D_801270CC;
    extern s16 D_801B1710;
    extern s16 D_801B1714;
    extern u8 D_801889F8[];
    extern u8 D_801A01A4[];

    register void *arg0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    void *s0;

    s0 = arg0;
    *(u16 *)((s32)s0 + 0x2) = 2;
    *(u16 *)((s32)s0 + 0x34) = 0;
    func_8012E8E0((s32)s0, (s32)&D_801889F8);
    func_8012A828((s32)s0, &D_801A01A4);
    *(s32 *)((s32)s0 + 0x1C) = 5;
    D_801270CC = 1;
    D_801B1710 = 0;
    D_801B1714 = 0;
    func_80029124(0x11E, 0);
}


#include "common.h"

/* Declarations are BLOCK-scope on purpose (this TU's house style, cf. the
 * block-scope decl layers at :3210, :3437-3444, :3578-3580, :3671-3674).
 * A file-scope prototype for func_8012A828 here would become visible to
 * func_80181C74 (:4202), which deliberately calls `func_8012A828()` with no
 * arguments behind a no-prototype decl — a file-scope prototype turns that
 * call into a hard `too few arguments` error and fails the whole-binary gate
 * even though this function itself is byte-identical.  Decls emit no code
 * (cookbook §8c), so scoping them costs nothing. */
void func_80180300(void *arg0)
{
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_8016F388(void);
    extern void func_80180D84(void *arg0);
    extern s32 D_801270C8;
    extern s16 D_801B1708;
    extern s16 D_801B1710;
    extern s16 D_801B1714;
    extern s16 D_801B1724;
    extern s16 D_801B1744;
    extern u8 D_801889F8[];
    extern u8 D_80188E40[];
    extern u8 D_801A08B4[];
    u16 var;

    *(u16 *)(arg0 + 2) = 3;
    func_8012E8E0(arg0, (s32)&D_801889F8);
    func_8012A828(arg0, &D_801A08B4);
    *(s32 *)(arg0 + 0x1C) = 0x3C;
    var = (*(u16 *)&D_801B1714);
    *(u16 *)(arg0 + 0x34) = 0;
    *(u16 *)(arg0 + 0xDC) = 0;
    *(u16 *)(arg0 + 0xDE) = 0;
    D_801B1708 = 0;
    D_801B1724 = 0;
    D_801B1744 = 1;
    D_801B1710 = var + 1;
    if (D_801B1710 >= 4) {
        func_80180D84((void *)arg0);
    } else {
        func_80178B18(arg0, (s32)&D_80188E40);
        func_8016F388();
        D_801270C8 = 2;
    }
}


#include "common.h"

extern s32 func_801789AC(s32 arg0);
extern void func_80181700(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8017FD28();      /* adopt sibling draft func_801805BC's spelling; return recovered by cast at the call (§183 SIGNATURE-cast-at-call) */
extern void func_80182148(void);      /* TU's own definition later in this file: void(void) */
extern void func_80180520(void *a0);

extern s16 D_801B1708;
extern s16 D_801B170C;
extern s16 D_801B1710;

void func_801803D4(s32 arg0) {
    s32 s0 = arg0;
    u16 state;

    func_801789AC(arg0);
    state = *(u16 *)(s0 + 0x34);

    switch (state) {
    case 0:
        func_80181700((void *)s0);
        if (func_8012BEE8(s0) != 0) {
            u16 newstate = *(u16 *)(s0 + 0x34) + 1;
            s16 tmp1710 = D_801B1710;
            *(u16 *)(s0 + 0x34) = newstate;
            D_801B1708 = tmp1710;
        }
        break;
    case 1:
        if (D_801B1708 == D_801B170C) {
            *(u16 *)(s0 + 0x34) = state + 1;
            *(s32 *)(s0 + 0x1C) = 0;
            *(s16 *)(s0 + 0xDC) = 0;
            func_80182148();
        }
        break;
    case 2: {
        s32 cnt = *(s32 *)(s0 + 0x1C);
        s32 arg1 = D_801B1710;
        s32 arg2 = *(s16 *)(s0 + 0xDC);
        cnt = cnt + 1;
        arg1 = arg1 - 1;
        *(s32 *)(s0 + 0x1C) = cnt;
        if (((s32 (*)())func_8017FD28)(s0, arg1, arg2) == 1) {
            *(s32 *)(s0 + 0x1C) = 0x2D;
            *(s16 *)(s0 + 0xA) = -0x1EE;
            *(s16 *)(s0 + 0x8) = 0;
            *(u16 *)(s0 + 0x34) += 1;
        }
        break;
    }
    case 3:
        if (func_8012BEE8(s0) != 0) {
            func_80180520((void *)s0);
        }
        break;
    }
}


#include "common.h"

/* func_80180520  (ov_SC06_025, 39 ins)  --  MATCH.
 *
 * Shape adopted from this TU's already-banked siblings func_80180D28 /
 * func_80180D84 / func_80182720, which drive the same
 * D_801889F8 + D_801A08B4 + D_801B1724 / D_801B1744 + D_801270C8 quintet
 * (law 2: twins give the shape, never the symbols or the literals -- every
 * symbol below was re-read off THIS target's own relocation lines, and the
 * store order is the target's, not the twins': the p->unk34 zero lands AFTER
 * D_801B1744 = 1 here, not before the first call as in func_80180D28).
 *
 * All externs are BLOCK scope, the house style of the two adjacent banked
 * functions -- the TU already carries file-scope decls for most of these and
 * block scope keeps this definition byte- and namespace-neutral for the rest
 * of the object.
 */
void func_80180520(void *arg0) {
    extern s32 D_801270C8;
    extern s16 D_801B1724;
    extern s16 D_801B1744;
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_801789AC(s32 arg0);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern void func_8016F388(void);
    extern u8 D_801889F8[];
    extern u8 D_801A08B4[];
    extern void (*D_80188E84[])(void *);

    *(s16 *)((char *)arg0 + 0x2) = 4;
    func_8012E8E0((s32)arg0, (s32)&D_801889F8);
    func_8012A828((s32)arg0, &D_801A08B4);
    *(s32 *)((char *)arg0 + 0x1C) = 0x1E;
    D_801B1744 = 1;
    *(s16 *)((char *)arg0 + 0x34) = 0;
    *(s16 *)((char *)arg0 + 0xDC) = 0;
    *(s16 *)((char *)arg0 + 0xDE) = 0;
    D_801B1724 = 0;
    D_801270C8 = 1;
    func_801789AC((s32)arg0);
    func_80178CBC((s32)arg0, (s32)&D_80188E84);
    func_8016F388();
}


#include "common.h"

/* func_801805BC  (ov_SC06_025, 143 ins)  --  MATCH, relocation-masked.
 *
 * Three findings are LOAD-BEARING; do not "clean them up" without re-gating:
 *
 *  1. The p-> accesses MUST be COMPONENT_REFs (a struct), not *(T *)(x + K)
 *     casts.  Only a COMPONENT_REF sets MEM_IN_STRUCT_P (cookbook §30 / §3-F),
 *     and gcc-2.7.2 true_dependence drops the edge between a /s varying-address
 *     MEM and a non-/s FIXED-address MEM -- which is what lets the D_801B1710 /
 *     D_801B1708 loads hoist ABOVE the p->unk34 / p->unk1C stores in cases 0
 *     and 1.  With raw casts the loads sink below the stores: 50 mismatches.
 *
 *  2. The INNER switch needs its EMPTY `case 0: break;`.  With only {1,2} the
 *     node count is 2, balance_case_nodes leaves a chain and emit_case_nodes
 *     takes its "omit the conditional branch to default ... it costs too much
 *     space to save so little time" arm (stmt.c:5669-5686) -> two bare `beq`s.
 *     Adding node 0 makes it 3, so the tree gets a median split and emits the
 *     ordering test: `beq lo` / `slti lo+1` / `bnez -> default` / `beq hi`.
 *     (Node 0's body is empty, so its label IS the end label; jump.c then folds
 *     `beqz -> test ; j end` into the inverted `bnez -> end`.)  §163c's
 *     "empty case label is load-bearing" for TABLES, in its decision-TREE form.
 *
 *  3. func_80180808 is called with NO ARGUMENT.  The target sets up no $a0 at
 *     all for it (the delay slot is a nop) and the call inherits the $a0 that
 *     still holds p->unk34.  Any argument at all is byte-wrong here: inside
 *     `case 2:` cse knows the switch value == 2 and folds every spelling of it
 *     (`v`, `p->unk34`, a separate s32 index local) to a literal `li $a0,2`.
 *     Verified against all three spellings -- each cost exactly this one insn.
 */

extern void func_8016F388(void);
extern s32  func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern void func_801807F8(s32);
extern void func_80182448(void);

void func_801805BC(void *arg0) {

    /* block-scope layout type: the target's alias behaviour needs MEM_IN_STRUCT_P
     * on the p-> accesses (gcc-2.7.2 true_dependence lets a varying in-struct MEM
     * pass a non-struct constant-address MEM), which a raw *(u16*)(x+K) cast
     * cannot give.  Named uniquely so it can never collide with a TU typedef. */
    typedef struct {
        u8  pad_0[0x8];
        s16 unk8;       /* 0x08 */
        s16 unkA;       /* 0x0A */
        u8  pad_C[0x10];
        s32 unk1C;      /* 0x1C */
        u8  pad_20[0x14];
        u16 unk34;      /* 0x34 */
        u8  pad_36[0xA6];
        s16 unkDC;      /* 0xDC */
    } Obj801805BC;

    extern s32  func_8012BEE8(s32);
    extern void func_80181700(void *arg0);
    extern void func_80180808();      /* fleet is SPLIT (void* x6 / s32 x4):
                                       * unspecified params conflict with neither */
    extern s32 func_8017FD28();      /* no extern exists anywhere in src/; the only
                                       * banked def spelling is ('void',()) -- so take
                                       * that and cast at the use, TU house style */
    extern void func_80180950(void *arg0);
    extern void func_80180D84(void *arg0);
    extern void func_801808AC(void *arg0);
    extern void func_8002D834(void);

    extern s16 D_801B1708;
    extern s16 D_801B170C;
    extern s16 D_801B1710;
    extern s16 D_801B1724;
    extern s32 D_80188E74[];

    Obj801805BC *p = (Obj801805BC *)arg0;
    u16 v;
    s32 r;
    s32 r2;

    func_801789AC((s32)arg0);

    v = p->unk34;   /* HImode local -> lives in $a0; `andi 0xffff` re-extends it
                     * for the switch, which is why the field is u16 and not s16 */

    switch (v) {
    case 0:
        func_80181700(p);
        if (func_8012BEE8((s32)p) != 0) {
            p->unk34 += 1;
            D_801B1708 = D_801B1710;
            func_8002D834();
            D_801B170C = 0;
        }
        break;

    case 1:
        if (D_801B1708 == D_801B170C) {
            p->unk34 += 1;
            p->unk1C = 0;
            p->unkDC = 0;
            func_801807F8(D_80188E74[D_801B1710]);
        }
        break;

    case 2:
        p->unk1C += 1;
        r = ((s32 (*)(void))func_80180808)();
        if (r == v) {
            D_801B1724 = 1;
        }
        r2 = ((s32 (*)(void *, s32, s32))func_8017FD28)(p, D_801B1710 - 1, p->unkDC);
        switch (r2) {
        case 0:
            break;
        case 1:
            if (r == 3) {
                p->unk1C = 0;
                D_801B1708 = 0;
                p->unkA = -494;
                p->unk8 = 0;
                p->unk34 += 1;
            }
            break;
        case 2:
            ((void (*)(void *))func_80178D18)(p);
            func_80182448();
            func_8016F388();
            func_80180950(p);
            break;
        }
        break;

    case 3:
        if (D_801B170C == 0) {
            ((void (*)(void *))func_80178D18)(p);
            func_80182448();
            func_8016F388();
            if (D_801B1710 >= 3) {
                func_80180D84(p);
            } else {
                func_801808AC(p);
            }
        }
        break;
    }
}


void func_801807F8(s32 a0) {

    extern s32 D_801B1B50;
    D_801B1B50 = a0;
}


/* func_80180808 -- cursor-advance probe over the 8-byte record at *D_801B1B50.
 * Returns: 3 = cursor unset (-1), 2 = pos outside [min,max], 1 = advanced,
 * or (max < pos*2) << 1 when the selector itself is unset. */
s32 func_80180808() {

    typedef struct { s32 f0; s16 f4; s16 f6; } Rec_80180808;

    extern s16 D_801B1704;
    extern s16 D_801B1720;
    extern s32 D_801B1B50;

    s32 pos = D_801B1704 * 2;
    Rec_80180808 *rec = (Rec_80180808 *)D_801B1B50;

    if (rec->f0 == -1) {
        return 3;
    }
    if (D_801B1720 != -1) {
        if (D_801B1720 != rec->f0) {
            return 2;
        }
        if (pos < rec->f4) {
            return 2;
        }
        if (!(rec->f6 < pos)) {
            D_801B1B50 = (s32)(rec + 1);
            return 1;
        }
        return 2;
    }
    return (rec->f6 < pos) << 1;
}


void func_801808AC(void *arg0)
{
    /* Declarations kept BLOCK-scope on purpose, matching this TU's house style
     * (see the comment above func_80180300 in the same file): a file-scope
     * prototype for func_8012A828 here would become visible to func_80181C74,
     * which deliberately calls `func_8012A828()` with no arguments behind a
     * no-prototype decl -- a file-scope prototype turns that into a hard
     * "too few arguments" error and fails the whole-binary gate even though
     * this function's own body is byte-identical. */
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_80137614(s32 a0, s32 a1, s32 a2);
    extern void func_80029124(s32 a0, s32 a1);
    extern void func_801746A4(void);

    extern u8 D_801889F8[];
    extern u8 D_801A1FDC[];
    extern void (*D_80189BE4[])(void);
    extern s32 D_801270C8;
    extern s32 D_801B1B54;
    extern s16 D_801B1714;

    *(u16 *)((s32)arg0 + 2) = 5;
    *(u16 *)((s32)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_801889F8);
    func_8012A828((s32)arg0, &D_801A1FDC);
    *(s32 *)((s32)arg0 + 0x1C) = 0;
    D_801270C8 = 2;
    D_801B1B54 = func_80137614((s32)D_80189BE4, 0, 0xC0);
    func_80029124(0x120, 0);
    func_801746A4();
    D_801B1714++;
}


void func_80180950(void *arg0) {

    typedef struct {
        u8  pad0[0x2];
        s16 unk2;       /* 0x02 */
        u8  pad4[0x18];
        s32 unk1C;      /* 0x1C */
        u8  pad20[0x14];
        s16 unk34;      /* 0x34 */
        u8  pad36[0xA6];
        s16 unkDC;      /* 0xDC */
        s16 unkDE;      /* 0xDE */
    } Obj80180950;

    extern s32 D_801270C8;
    extern s16 D_801B1708;
    extern s16 D_801B1710;

    Obj80180950 *p = (Obj80180950 *)arg0;

    p->unk2 = 6;
    p->unk34 = 0;
    p->unkDC = 0;
    p->unkDE = 0;
    ((struct { s32 f; } *)&D_801270C8)->f = 3;
    D_801B1708 = 0;
    D_801B1710 = 0;
    p->unk1C = 0x16;
}


#include "common.h"

/* func_8018098C  (ov_SC06_025) -- 5-way actor state dispatcher on p->unk34.
 *
 * Declarations kept BLOCK-scope on purpose, matching this TU's house style
 * (see the comment above func_801808AC in the same file): a file-scope
 * prototype for func_8012A828 here would become visible to func_80181C74,
 * which deliberately calls `func_8012A828()` with no arguments behind a
 * no-prototype decl. */
void func_8018098C(void *arg0) {

    typedef struct {
        u8  pad_0[0x1C];
        s32 unk1C;      /* 0x1C */
        u8  pad_20[0x14];
        u16 unk34;      /* 0x34 */
    } Obj8018098C;

    extern void func_80180B7C(s32 a0);
    extern void func_80181700(void *a0);
    extern s32  func_8012BEE8(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32  func_80137614(s32 a0, s32 a1, s32 a2);
    extern s32  func_801399F0(s32 a0);
    extern void func_801823FC(s32 a0);
    extern void func_8016F374(void);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_80181668(void);
    extern s32  func_801822F0(void);
    extern void func_80180D28(void *a0);

    extern void (*D_801897FC[])(void);
    extern s32 D_801A0FBC;
    extern s32 D_801A249C;
    extern s32 D_801270C8;
    extern s32 D_801B1B54;
    extern s16 D_801B1708;
    extern s16 D_801B170C;

    Obj8018098C *p = (Obj8018098C *)arg0;

    switch (p->unk34) {
    case 0:
        func_80180B7C((s32)p);
        if (func_8012BEE8((s32)p) != 0) {
            func_8012A828((s32)p, &D_801A0FBC);
            p->unk1C = 0x3C;
            p->unk34 += 1;
            D_801B1B54 = func_80137614((s32)D_801897FC, 0, 0xC0);
        }
        break;

    case 1:
        func_80181700(p);
        if (func_8012BEE8((s32)p) != 0) {
            if (func_801399F0(D_801B1B54) != 0) {
                func_801823FC(D_801B1B54);
                p->unk34 += 1;
            }
        }
        break;

    case 2:
        func_80181700(p);
        if (D_801B170C == D_801B1708) {
            p->unk1C = 0x1E;
            p->unk34 += 1;
            /* §3-F: a plain scalar store at a FIXED address loses its dependence on
             * the varying /s p->unk34 store and hoists above it (sched.c:817).  The
             * COMPONENT_REF spelling -- this TU's own idiom, see func_80180950 --
             * sets MEM_IN_STRUCT_P and keeps the store in source order. */
            ((struct { s32 f; } *)&D_801270C8)->f = 0;
        }
        break;

    case 3:
        func_80181700(p);
        if (func_8012BEE8((s32)p) != 0) {
            func_8016F374();
            func_8012A828((s32)p, &D_801A249C);
            p->unk1C = 0x78;
            p->unk34 += 1;
        }
        break;

    case 4:
        func_80181700(p);
        p->unk1C -= 1;
        if (p->unk1C == 0x6C) {
            func_8002D4C8(0x9DB, 0);
            func_80181668();
        }
        if (p->unk1C == 0x3C) {
            func_801822F0();
        }
        if (p->unk1C <= 0) {
            func_8002D4C8(4, 0x9DB);
            func_80180D28(p);
        }
        break;
    }
}


#include "common.h"

extern void func_80181750();
extern void func_80181C74(s32 *a0, s32 a1);   /* verbatim from its own definition later in this TU */
extern void func_8012AD80(s32 a0);
extern void func_80181700(void *a0);
extern s16 D_80189074;
extern s16 D_80189078;
extern s32 D_801A19BC;
extern s32 D_8018885C;

/* 6-way actor state dispatcher on *(s32 *)(a0 + 0x1C).
 * The shared tail (func_8012AD80 + the 0xA clamp) is WRITTEN OUT in each of the
 * four converging arms on purpose (law 22 / cookbook §193-C): gcc-2.7.2's
 * cross_jump merges the scheduled common SUFFIX, and that merge is what
 * reproduces the target's per-predecessor "addu $a0,$s0,$zero" reloads.
 * Hoisting the tail to one merge point under-counts by exactly 2 instructions. */
void func_80180B7C(s32 a0) {
    s32 state = *(s32 *)(a0 + 0x1C);
    s32 p = (s32)&D_80189074;

    if (state >= 0x15) {
        func_80181750(a0, p);
        func_80181C74((s32 *)a0, (s32)&D_801A19BC);
        return;
    }

    if (state == 0x14) {
        s32 vx;
        s32 vz;
        func_80181750(a0, p);
        vx = (((s32)*(s16 *)p - (s32)*(s16 *)(a0 + 0x6)) << 16) / state;
        vz = (((s32)D_80189078 - (s32)*(s16 *)(a0 + 0xE)) << 16) / state;
        /* velocity triple 0x10/0x14/0x18, then the 0x44/0x48/0x4C triple —
         * both written in plain ascending source order (law 19 / §190-B).
         * sched1 is what interleaves them into the target's
         * 0x44, 0x48, 0x4C, 0x14, 0x10, 0x18 emission order; do NOT
         * hand-pre-schedule this block. */
        *(s32 *)(a0 + 0x10) = vx;
        *(s32 *)(a0 + 0x14) = 0xFFE98000;
        *(s32 *)(a0 + 0x18) = vz;
        *(s32 *)(a0 + 0x44) = 0;
        *(s32 *)(a0 + 0x48) = 0x24000;
        *(s32 *)(a0 + 0x4C) = 0;
        func_8012AD80(a0);
        if (*(s16 *)(a0 + 0xA) >= -0x1ED) {
            *(s16 *)(a0 + 0xA) = -0x1EE;
        }
    } else if (state >= 7) {
        func_80181750(a0, p);
        func_8012AD80(a0);
        if (*(s16 *)(a0 + 0xA) >= -0x1ED) {
            *(s16 *)(a0 + 0xA) = -0x1EE;
        }
    } else if (state == 6) {
        func_80181C74((s32 *)a0, (s32)&D_8018885C);
        func_8012AD80(a0);
        if (*(s16 *)(a0 + 0xA) >= -0x1ED) {
            *(s16 *)(a0 + 0xA) = -0x1EE;
        }
    } else if (state >= 3) {
        func_8012AD80(a0);
        if (*(s16 *)(a0 + 0xA) >= -0x1ED) {
            *(s16 *)(a0 + 0xA) = -0x1EE;
        }
    } else {
        *(s16 *)(a0 + 0xA) = -0x1EE;
        *(s16 *)(a0 + 0x8) = 0;
        func_80181700((void *)a0);
    }
}


void func_80180D28(void *arg0) {
    extern s32 D_801270C8;
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern u8 D_801889F8[];
    extern s32 D_801A0FBC;

    *(s16 *)((char *)arg0 + 0x2) = 7;
    *(s16 *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_801889F8);
    func_8012A828((s32)arg0, &D_801A0FBC);
    D_801270C8 = 0;
    *(s32 *)((char *)arg0 + 0x1C) = 0x3C;
}


void func_80180D84(void *arg0) {
    /* block-scope layout type, named uniquely so it can never collide with the
     * TU's file-scope typedef St_8017E95C_r (gcc-2.7.2 rejects typedef
     * redefinition; cookbook §120: rename, don't remove) */
    typedef struct {
        s16 unk0;                /* 0x00 */
        u8 pad[0x102];           /* -> 0x104 */
    } Obj80180D84;

    extern s32 D_801270C8;
    extern St_8017E95C_r D_801B12F0[4];
    extern void func_8012A828(s32 a0, void *a1);
    extern void (*D_80188F18[])(void);
    extern u8 D_801889F8[];
    extern u8 D_801A892C[];

    *(s16 *)((char *)arg0 + 0x2) = 8;
    *(s16 *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_801889F8);
    func_8012A828((s32)arg0, &D_801A892C);
    D_801270C8 = 0;
    *(s32 *)((char *)arg0 + 0x1C) = 0;
    func_8002A088(0x190);
    func_8002D4C8(0xA98, 0);
    func_80029514(0x5DC);
    func_800D0C48(1);
    func_80016714(((Obj80180D84 *)D_801B12F0), 0x410);
    func_80178BF8();
    func_801746A4();
    func_80178CBC((s32)arg0, (s32)&D_80188F18);
}


extern void (*D_80189020[])(void);

void func_80180E30(void *a0) {
    extern s16 D_801B1720;
    extern void func_80182170(void *a0);
    u16 flag;

    D_80189020[*(u16 *)((s32)a0 + 0x2)]();
    flag = *(u16 *)((s32)a0 + 0x0);
    D_801B1720 = -1;
    if (flag != 0) {
        ((void (*)())func_80182170)(a0);
    }
}



extern void (*D_8018908C[])(void);

void func_80180E98(void *a0) {
    D_8018908C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_801890A4[])(void);

s32 func_80180ED4(void)
{
    register s32 a0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    return (s32)&D_801890A4[a0 * 2];
}


extern s32 func_8012E544(s32 a0);

s32 func_80180EE8(void) {
    s32 rec;
    s32 h;
    s32 ret;

    rec = func_8012E544(0x2CD);
    if (rec == 0) {
        return 1;
    }
    h = *(u16 *)(rec + 2);
    if (h == 6) {
        ret = 0;
    } else {
        ret = (h ^ 7) != 0;
    }
    return ret;
}



extern void (*D_801890CC[])(void);

void func_80180F34(void *a0) {
    D_801890CC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Stride-4 record: only the leading s16 is ever read here.
 * D_801891F4 and D_801891F6 are two independent relocation symbols 2 bytes
 * apart; both tables are walked with the same 4-byte stride, so the second is
 * reached through a pointer cast of &D_801891F6 (the target's `la $v1` form). */
typedef struct {
    s16 v;
    s16 pad;
} Rec4_801891F4;

extern Rec4_801891F4 D_801891F4[];
extern s16 D_801891F6;
extern s16 D_801B1704;
extern u8 D_801B1B90[];
extern s32 D_8019AB90;
extern s32 D_8019B030;
extern u8 D_80189174[];
extern u8 D_801891B4[];
extern u8 D_80189194[];
extern u8 D_801891D4[];

extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_8013240C(s32 a0);

void func_80180F70(void *a0) {
    /* +0xE8 timer; the two arms share the decrement+expire tail, which
     * cross_jump merges back into one block (law 10 / §186). */
    if (*(s32 *)((s32)a0 + 0xE8) != 0) {
        (*(s32 *)((s32)a0 + 0xE8))--;
        if (*(s32 *)((s32)a0 + 0xE8) == 0) {
            *(s16 *)((s32)a0 + 0x5E) = 0;
            *(u16 *)((s32)a0 + 0x5C) &= 0xFFFE;
        }
    } else {
        if (*(u16 *)((s32)a0 + 0x5C) & 1) {
            *(s32 *)((s32)a0 + 0xE8) = 0x14;
        }
        if (*(s32 *)((s32)a0 + 0xE8) != 0) {
            (*(s32 *)((s32)a0 + 0xE8))--;
            if (*(s32 *)((s32)a0 + 0xE8) == 0) {
                *(s16 *)((s32)a0 + 0x5E) = 0;
                *(u16 *)((s32)a0 + 0x5C) &= 0xFFFE;
            }
        }
    }

    /* §190-A preheader strata. `base` must be indexed by the SAME biv `i`
     * (base[i], not a second walking pointer p++): only then is &base[i] a
     * reduced address giv, so loop.c emits its `la $v1,%lo(D_801891F6)` init
     * in the THIRD stratum -- i.e. AFTER the hoisted invariants li 2 / li -1.
     * Written as a separate `p` pointer, the `la` is an ordinary preheader
     * statement (first stratum) and lands two slots too early; no amount of
     * source-statement reordering can fix that, because the constants are
     * hoisted to loop_start and always follow the source preheader.
     * The guard must stay the SCALAR read of D_801891F6 (not base[0]) or cse
     * shares one address register and the absolute `lh %lo()` guard load turns
     * into `la`+`lh 0($x)` (+1 insn). Compare written `target == arr[i]` so the
     * bne operands land as `bne $a2,$v0`. */
    if (D_801891F6 != -1) {
        Rec4_801891F4 *base = (Rec4_801891F4 *)&D_801891F6;
        s32 i = 0;
        s32 target = (s32)D_801B1704 * 2;
        do {
            if (target == D_801891F4[i].v) {
                if (base[i].v == 1) {
                    *(s16 *)((s32)a0 + 0xFC) = 1;   /* +0xFC = pending anim id */
                } else {
                    *(s16 *)((s32)a0 + 0xFC) = 2;
                }
            }
            i++;
        } while (base[i].v != -1);
    }

    if (*(s16 *)((s32)a0 + 0x70) != 1 && *(s16 *)((s32)a0 + 0x70) != 3) {
        s16 fc = *(s16 *)((s32)a0 + 0xFC);
        switch (fc) {
        case 1:
            if (*(s16 *)((s32)a0 + 0x70) == 0) {
                func_80132288((s32 *)D_801B1B90, (s32 *)D_80189174, D_8019AB90);
            } else {
                func_80132288(
                    (s32 *)(D_801B1B90 + (*(s16 *)((s32)a0 + 0x70) << 4)),
                    (s32 *)D_801891B4, D_8019B030);
            }
            *(s16 *)((s32)a0 + 0xFC) = 0;
            break;
        case 2:
            if (*(s16 *)((s32)a0 + 0x70) == 0) {
                func_80132288((s32 *)D_801B1B90, (s32 *)D_80189194, D_8019AB90);
            } else {
                func_80132288(
                    (s32 *)(D_801B1B90 + (*(s16 *)((s32)a0 + 0x70) << 4)),
                    (s32 *)D_801891D4, D_8019B030);
            }
            *(s16 *)((s32)a0 + 0xFC) = 0;
            break;
        }
        func_8013240C((s32)(D_801B1B90 + (*(s16 *)((s32)a0 + 0x70) << 4)));
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);

extern s32 D_801890D4[];
extern u8 D_801890E4[];
extern u8 D_80189104[];
extern u8 D_801B1B90[];   /* adopt sibling draft func_80180F70's spelling (§183 TYPE-adopted-TU); narrowed at the use site */
extern s32 D_8019AB90;
extern u8 D_80189174[];   /* adopt sibling draft func_80180F70's spelling (§183 TYPE-adopted-TU); cast at the call */
extern s32 D_801B1BB0[];
extern s32 D_8019B030;
extern u8 D_801891B4[];   /* adopt sibling draft func_80180F70's spelling (§183 TYPE-adopted-TU); cast at the call */

void func_80181148(void *a0)
{
    s32 iVar2;
    s32 v1;

    iVar2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = iVar2;
    if (iVar2 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(iVar2, D_801890D4[*(s16 *)((s32)a0 + 0x70)]);

        *(u16 *)((s32)a0 + 0x5C) = 0xC800;
        *(u8  *)((s32)a0 + 0x75) = 2;
        *(s16 *)((s32)a0 + 2) = 1;

        *(s32 *)((s32)a0 + 0xE8) = 0;
        *(s32 *)((s32)a0 + 0x58) = ((s32)&D_80189104[*(s16 *)((s32)a0 + 0x70) * 16] | 0x40000000);
        func_8012E8E0((s32)a0, (s32)&D_801890E4[*(s16 *)((s32)a0 + 0x70) * 8]);

        v1 = *(s16 *)((s32)a0 + 0x70);
        *(s16 *)((s32)a0 + 0xFC) = 0;
        if (v1 == 0) {
            func_80132288((s32 *)D_801B1B90, (s32 *)D_80189174, D_8019AB90);
        } else if (v1 == 2) {
            func_80132288(D_801B1BB0, (s32 *)D_801891B4, D_8019B030);
        }
    }
}



extern void (*D_8018923C[])(void);

void func_80181260(void *a0) {
    D_8018923C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012DFD4(void *a0);

void func_8018129C(void *a0) {

    extern void (*D_8018939C[])(void);
    D_8018939C[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_8012DFD4(a0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s16 D_801B173C;

void func_801812FC(s32 a0) {
    switch (*(u16 *)(a0 + 0x34)) {
    case 0: {
        s32 c = 0x1000;
        s32 flag;
        s32 base;
        do { *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10; } while (0);
        base = *(s32 *)(a0 + 0x20);
        flag = D_801B173C;
        *(s16 *)(base + 0x18) = c;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = c;
        if (flag == 0) {
            break;
        }
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(s16 *)(a0 + 0x34) = 1;
        if (*(s16 *)(a0 + 0x70) == 0) {
            func_8002D4C8(0xC0F, 0);
        }
        break;
    }
    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1000;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = (0x3C - *(s32 *)(a0 + 0x1C)) * 0x1000 / 0x3C;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1000;
        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0;
            *(s16 *)(a0 + 0x34) = 2;
            if (*(s16 *)(a0 + 0x70) == 0) {
                func_8002D4C8(0xC10, 0);
            }
        }
        break;
    case 2:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1000;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1000;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1000;
        break;
    }
}


extern void (*D_801893F4[])(void);

void func_80181488(void *a0) {
    D_801893F4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern u8 D_80189408[];

void func_801814C4(void *a0) {
    s32 s0 = (s32)a0;
    *(s16 *)(s0 + 0x2) = 2;
    func_8012E8E0((s32)a0, (s32)D_80189408 + (*(s16 *)(s0 + 0x70) << 3));
    *(s32 *)(s0 + 0x1C) = 0x77;
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

void func_80181514(void *a0)
{
    void *s0;
    void *v1;
    s32 v0;
    s32 a1;
    s32 x1, x2;

    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        return;
    }

    s0 = (void *)func_80132EF4((s32)a0, 0x22);
    if (s0 == NULL) {
        return;
    }

    v1 = *(void **)((s32)s0 + 0x20);
    if (v1 != NULL) {
        *(u16 *)((s32)v1 + 0x2C) = 0xC040;
    }

    v0 = rand() & 0x3F;
    *(s16 *)((s32)s0 + 0xE) = *(u16 *)((s32)s0 + 0xE) - v0;

    {
        s32 t = *(s32 *)((s32)a0 + 0x1C);
        if (t < 0x3D) {
            a1 = t;
        } else {
            a1 = 0x78 - t;
        }
    }

    x1 = (a1 << 21) / 60;
    *(s32 *)((s32)s0 + 0x18) = -0x80000 - x1;

    x2 = ((a1 * 3) << 13) / 60;
    *(s16 *)((s32)s0 + 0x34) = (s16)(((x2 + 0x1000) & ~3) | 1);

    *(s32 *)(*(s32 *)((s32)s0 + 0x20) + 4) |= 0x70000000;
}



extern void (*D_8018942C[])(void);

void func_8018162C(void *a0) {
    D_8018942C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80181668(void) {
    s32 i;
    s32 shift_temp;
    s32 v0;

    for (i = 0; i < 3; i++) {
        shift_temp = (i << 16) >> 16;
        v0 = func_8012E57C(0x327, shift_temp);
        if (v0 != 0) {
            *(s16 *)((char *)v0 + 0xFC) = 1;
        }
    }
}



extern void (*D_801894F0[])(void);

void func_801816C4(void *a0) {
    D_801894F0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80181700(void *a0)
{
    s32 *p = (s32 *)a0;
    s32 *q1, *q2;
    s32 r, t;

    q1 = *(s32 **)((u8 *)p + 0x20);
    r = func_8012B608(*(s16 *)((u8 *)q1 + 0x12), 0, 4);
    q2 = *(s32 **)((u8 *)p + 0x20);
    t = *(u16 *)((u8 *)q2 + 0x12);
    t += r;
    *(s16 *)((u8 *)q2 + 0x12) = t;
}


void func_80181750(void *a0)
{
    s32 *p = (s32 *)a0;
    s32 *q1, *q2;
    s32 r, t;

    t = func_8012B744(p + 1);
    q1 = *(s32 **)((u8 *)p + 0x20);
    r = func_8012B608(*(s16 *)((u8 *)q1 + 0x12), t, 4);
    q2 = *(s32 **)((u8 *)p + 0x20);
    t = *(u16 *)((u8 *)q2 + 0x12);
    t += r;
    *(s16 *)((u8 *)q2 + 0x12) = t;
}


#include "common.h"

extern s16 D_801B1700;
extern s16 D_801B1704;   /* adopt sibling draft func_80180F70's spelling (§183 TYPE-adopted-TU); zero-extended at the use site */
extern s16 D_801B1708;
extern s16 D_801B170C;
extern u16 D_801894F8[];
extern s16 D_80189500[];
extern s32 func_8002D80C(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801817A8(void)
{
    switch (D_801B1700) {
    case 0:
        D_801B1704 = *(u16 *)&D_801B1704 + 1;
        if (D_801B170C != D_801B1708) {
            func_8002D4C8(0x27, D_801894F8[D_801B1708]);
            D_801B1700 = 1;
        }
        if (D_801B170C != 0) {
            if (!(D_801B1704 < D_80189500[D_801B170C])) {
                D_801B1708 = 0;
                func_8002D4C8(0x27, D_801894F8[0]);
                D_801B1700 = 1;
            }
        }
        break;
    case 1:
        {
            s32 ret = func_8002D80C() & 0xFFFF;
            s16 idx = D_801B1708;

            if (ret == (s16)D_801894F8[idx]) {
                D_801B170C = idx;
                D_801B1700 = 0;
                D_801B1704 = 0;
            }
        }
        break;
    }
}


#include "common.h"

/* engine_types.h:525 `OtBlk` VERBATIM (typedef struct { s32 a; s32 b[4]; } OtBlk;).  The real TU
 * reaches it through engine_core.h -> engine_types.h, so the bank driver strips this local copy;
 * match_one's standalone -Iinclude compile cannot see that header, hence the restatement.  Spelled
 * IDENTICALLY in every draft of this wave that touches D_800A651C (func_8017F788 / func_80181E08 in
 * this same TU) so the merged TU ends with one declaration of the symbol. */


extern OtBlk D_800A651C[];
extern short D_800B9A02;
extern void *func_80010A08(s32);
extern void func_8012E32C(void);
extern void func_8012B0B4(u32 *a0, s32 a1, s32 a2);
extern s32 func_8004787C(s32 a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);
extern s32 func_801823D4(s32, s32);

void func_801818D8(u16 *pv, s32 arg1, s32 n, s32 col) {
    typedef struct {
        s32 tag;   /* 0x00 */
        s32 rgb0;  /* 0x04   code byte lives at +3 of this word */
        s32 xy0;   /* 0x08 */
        s32 rgb1;  /* 0x0C */
        s32 xy1;   /* 0x10 */
        s32 rgb2;  /* 0x14 */
        s32 xy2;   /* 0x18 */
        s32 rgb3;  /* 0x1C */
        s32 xy3;   /* 0x20 */
    } G4;
    typedef struct { s16 vx, vy, vz, pad; } V8;

    V8 sv[4];   /* sp+0x10 .. 0x2F */
    s32 v[2];   /* sp+0x30 */
    s32 p;      /* sp+0x38 */
    s32 flag;   /* sp+0x3C */
    G4 *q;
    s32 i, ang, t, r, sc, dy, otz;

    if (n >= 1 && n <= 9) {
        func_8012E32C();
        r = func_8004787C((n << 11) / 10);
        dy = (r * 192) >> 12;
        sc = r + 0x1000;
        for (i = 0, ang = 0; i < 16; i++, ang += 0x100) {
            func_8012B0B4((u32 *)v, ang, arg1);
            t = v[0];
            sv[0].vx = pv[0] + t;
            sv[0].vy = pv[1];
            sv[0].vz = pv[2] + (t >> 16);
            sv[2].vx = pv[0] + (((s16)t * sc) >> 12);
            sv[2].vy = pv[1] - dy;
            sv[2].vz = pv[2] + (((t >> 16) * sc) >> 12);

            func_8012B0B4((u32 *)v, ang + 0x100, arg1);
            t = v[0];
            sv[1].vx = pv[0] + t;
            sv[1].vy = pv[1];
            sv[1].vz = pv[2] + (t >> 16);
            sv[3].vx = pv[0] + (((s16)t * sc) >> 12);
            sv[3].vy = pv[1] - dy;
            sv[3].vz = pv[2] + (((t >> 16) * sc) >> 12);

            q = (G4 *)func_80010A08(0x24);
            /* chained, neighbour-verified store order (see func_80181E08 in this TU):
             * rgb1=rgb0=col emits 0x4 then 0xC; rgb2=rgb3=0 emits 0x1C then 0x14.
             * The two zero stores MUST follow the colour pair in source order --
             * leading with them costs 4 insns of SCHEDULE-REORDER (the lw of the
             * spilled `col` and the li 0x3A no longer hoist above them). */
            q->rgb1 = q->rgb0 = col;
            q->rgb2 = q->rgb3 = 0;
            *((u8 *)q + 7) = 0x3A;   /* POLY_G4 | semi-transparent */
            q->tag = 0x08000000;     /* 8 words */
            otz = RotTransPers((s32)&sv[0], (s32)&q->xy0, &p, &flag);
            RotTransPers((s32)&sv[1], (s32)&q->xy1, &p, &flag);
            RotTransPers((s32)&sv[2], (s32)&q->xy2, &p, &flag);
            RotTransPers((s32)&sv[3], (s32)&q->xy3, &p, &flag);
            otz = func_801823D4(otz, -0x1A);
            AddPrim(D_800A651C[(u16)D_800B9A02].a + otz * 4, q);
            func_8012E28C(otz, 1);
        }
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80181B90(s32 a0) {
    s32 shift_temp;
    s32 v1;

    shift_temp = ((a0 << 16) >> 16);
    v1 = func_8012E57C(0x2C7, shift_temp);
    if (v1 != 0) {
        *(s32 *)((char *)v1 + 0x1C) = 0xA;
    }
}


extern u16 D_80126B62;
extern s16 D_801B1718;
extern s16 D_801B171C;

void func_80181BC8(void) {
    s32 hit;

    hit = ((s16)D_80126B62 == -0x178);
    if (D_801B1718 == 0 && hit) {
        D_801B171C = 1;
    } else {
        D_801B171C = 0;
    }
    D_801B1718 = hit;
}



extern void Square0(s32 *a0, s32 *a1);

s32 func_80181C1C(s16 *a0) {

    extern s16 D_80126B5E;
    extern s16 D_80126B66;
    s32 in[3];
    s32 out[3];
    in[0] = a0[3] - D_80126B5E;
    in[1] = 0;
    in[2] = a0[7] - D_80126B66;
    Square0(in, out);
    return out[0] + out[2];
}


extern void func_8012A828();
void func_80181C74(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0x90) != a1) {
        func_8012A828();
    }
}


#include "common.h"

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

/* 8-byte unaligned vector: forces lwl/lwr + swl/swr for the two tail copies
 * (an aligned struct would emit lw/sw and lose the match). */
typedef struct { u16 x, y, z, pad; } Vec8_80181CA4;

/* a0: dest struct ptr. a1: src1 struct ptr (Vec8_80181CA4-shaped: x,y,z,pad).
 * a2: scalar, call1's 3rd func_8012B0B4 arg. a3: scalar, stored to a0+0xEC.
 * a4 (stack): src2 struct ptr (same shape as a1). a5 (stack): scalar, call2's
 * 3rd func_8012B0B4 arg. a6 (stack): scalar, stored to a0+0xF0.
 * a7 (stack): low half stored to a0+0x6.
 *
 * a7 MUST be declared s32, not u16 (§189-D / §195): PROMOTE_PROTOTYPES makes a
 * narrow parm's DECL_ARG_TYPE `int`, so nominal_mode(HI) != passed_mode(SI),
 * assign_parms sets did_conversion and SKIPS the REG_EQUIV note -> local-alloc
 * never doubles its live length -> the pseudo wins a callee-saved seat and
 * evicts a5. Declared s32 it keeps the REG_EQUIV, loses the seat, and reload
 * narrows the equivalent MEM back to the target's `lhu 0x64($sp)`. */
void func_80181CA4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7) {
    s32 sp10[2];
    s32 sp18[2];
    s32 ang;
    s32 i;
    s32 t;

    /* both counters init'd in the for-init and both bumped in the for-increment:
     * i must be emitted before ang on BOTH sides (init order and bump order). */
    for (i = 0, ang = 0; i < 0xC; i++, ang += 0x155) {
        func_8012B0B4((unsigned int *)sp10, ang, a2);
        t = sp10[0];
        *(s16 *)(a0 + 0x2C + i * 8) = *(u16 *)(a1 + 0x0) + (t >> 16);
        *(s16 *)(a0 + 0x2E + i * 8) = *(u16 *)(a1 + 0x2);
        *(s16 *)(a0 + 0x30 + i * 8) = *(u16 *)(a1 + 0x4) + t;

        func_8012B0B4((unsigned int *)sp18, ang, a5);
        t = sp18[0];
        *(s16 *)(a0 + 0x8C + i * 8) = *(u16 *)(a4 + 0x0) + (t >> 16);
        *(s16 *)(a0 + 0x8E + i * 8) = *(u16 *)(a4 + 0x2);
        *(s16 *)(a0 + 0x90 + i * 8) = *(u16 *)(a4 + 0x4) + t;
    }

    *(s32 *)(a0 + 0xEC) = a3;
    *(s32 *)(a0 + 0xF0) = a6;
    *(u16 *)(a0 + 0x6) = a7;

    *(Vec8_80181CA4 *)(a0 + 0xF4) = *(Vec8_80181CA4 *)(a1 + 0x0);
    *(Vec8_80181CA4 *)(a0 + 0xFC) = *(Vec8_80181CA4 *)(a4 + 0x0);
}


#include "common.h"

/* engine_types.h:525 `OtBlk` VERBATIM (typedef struct { s32 a; s32 b[4]; } OtBlk;).  The real TU
 * reaches it through engine_core.h -> engine_types.h, so the bank driver strips this local copy;
 * match_one's standalone -Iinclude compile cannot see that header, hence the restatement.  Spelled
 * IDENTICALLY in every draft of this wave that touches D_800A651C (func_8017E4E0 / func_8017FB50 /
 * func_80181E08) so the merged TU ends with one declaration of the symbol (wave law 4).  The
 * array-of-struct form is load-bearing: the raw-word `extern s32 D_800A651C;` + &-arithmetic
 * spelling costs the %lo fold (lui $at/addu/lw %lo -> la + addu + lw) inside a loop. */

extern OtBlk D_800A651C[];


/* ov_SC06_025 : func_80181E08   (162 ins, byte-exact)
 *
 * Ring emitter for the entity at arg0.  Two 12-entry 8-byte vertex rings live at
 * arg0+0x2C (inner/"a") and arg0+0x8C (outer/"b"); the apex vertex is at arg0+0xF4.
 *
 *   loop 1 : 12 semi-transparent POLY_G4 (tag 0x08000000, code 0x3A, 0x24 bytes)
 *            bridging a[i],a[i+1],b[i],b[i+1]; the i==11 quad wraps to entry 0.
 *            Two colour words: arg0+0xEC -> rgb0/rgb1, arg0+0xF0 -> rgb2/rgb3.
 *   loop 2 : 12 semi-transparent POLY_G3 (tag 0x06000000, code 0x32, 0x1C bytes)
 *            fanning a[i], a[(i+1)%12] and the apex; all three rgb words come from
 *            func_80182090(arg0->0xEC, 0x2800).
 *
 * Each primitive is depth-sorted with func_801823D4(otz, -0x1A) and linked into the
 * live OT via D_800A651C[D_800B9A02].a + otz*4, then handed to func_8012E28C with the
 * s16 at arg0+6.
 */
void func_80181E08(s32 arg0) {
    /* --- packet layouts (word offsets verified against the target's sw/sb) ------ */
    typedef struct {
        s32 tag;   /* 0x00 */
        s32 rgb0;  /* 0x04   code byte lives at +3 of this word */
        s32 xy0;   /* 0x08 */
        s32 rgb1;  /* 0x0C */
        s32 xy1;   /* 0x10 */
        s32 rgb2;  /* 0x14 */
        s32 xy2;   /* 0x18 */
        s32 rgb3;  /* 0x1C */
        s32 xy3;   /* 0x20 */
    } G4;
    typedef struct {
        s32 tag;   /* 0x00 */
        s32 rgb0;  /* 0x04 */
        s32 xy0;   /* 0x08 */
        s32 rgb1;  /* 0x0C */
        s32 xy1;   /* 0x10 */
        s32 rgb2;  /* 0x14 */
        s32 xy2;   /* 0x18 */
    } G3;
    typedef struct { s16 vx, vy, vz, pad; } V8;   /* 8-byte ring stride */

    extern void *func_80010A08(s32);
    extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
    extern s32 RotTransPers(s32, s32, s32 *, s32 *);
    extern s32 AddPrim(s32, void *);
    extern void func_8012E28C(s32, s32);
    extern void func_8012E32C(void);
    extern s32 func_801823D4(s32, s32);
    extern s32 func_80182090();
    extern short D_800B9A02;      /* TU's own spelling (see line 2466/2820 of the TU) */

    V8 *pa, *pb;
    G4 *q;
    G3 *t;
    s32 p;                        /* sp+0x28 : RotTransPers* `p`   out-param */
    s32 flag;                     /* sp+0x2C : RotTransPers* `flag` out-param */
    s32 i;
    s32 otz;
    s32 c;
    s32 c2;
    s32 col;
    s32 v0p, v1p, v2p, v3p;
    /* Loop 1 hoists both out-param addresses into callee-saved regs.  Written as
     * plain locals the pointers land in $fp/$s6 instead of $s7/$s6: gcc's
     * allocno_compare ranks `zpush` (3 refs, loop-weighted) above them.  Pinning the
     * two pointers frees $fp for `zpush` and reproduces the target exactly. */
    register s32 *pp __asm__("$23");   /* &p    */  // !FAKE: pin $23 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 *pf __asm__("$22");   /* &flag */  // !FAKE: pin $22 — NEEDED DIFFERS (P36 rung B tus9)
    s32 zpush;

    func_8012E32C();
    pa = (V8 *)(arg0 + 0x2C);
    pb = (V8 *)(arg0 + 0x8C);
    i = 0;
    pp = &p;
    pf = &flag;
    zpush = *(s16 *)(arg0 + 6);

    for (; i < 12; ) {
        q = (G4 *)func_80010A08(0x24);
        c = *(s32 *)(arg0 + 0xEC);
        q->rgb0 = q->rgb1 = c;          /* chained: stores 0xC then 0x4 */
        c2 = *(s32 *)(arg0 + 0xF0);
        *((u8 *)q + 7) = 0x3A;
        q->tag = 0x08000000;
        q->rgb2 = q->rgb3 = c2;         /* chained: stores 0x1C then 0x14 */
        if (i != 11) {
            v0p = (s32)pa;
            v1p = (s32)pa + 8;
            v2p = (s32)pb;
            v3p = (s32)pb + 8;
        } else {
            v0p = arg0 + 0x84;          /* a[11] */
            v1p = arg0 + 0x2C;          /* a[0]  */
            v2p = arg0 + 0xE4;          /* b[11] */
            v3p = arg0 + 0x8C;          /* b[0]  */
        }
        otz = RotTransPers4(v0p, v1p, v2p, v3p,
                            &q->xy0, &q->xy1, &q->xy2, &q->xy3, pp, pf);
        /* Zero-byte re-tie: without it combine folds `move $s1,$v0; move $a0,$s1`
         * into a single `move $a0,$v0` (the target keeps both).  §189-C form. */
        __asm__("" : "=r"(otz) : "0"(otz));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        otz = func_801823D4(otz, -0x1A);
        AddPrim(D_800A651C[*(u16 *)&D_800B9A02].a + otz * 4, q);
        func_8012E28C(otz, zpush);
        i++;
        pa++;
        pb++;
    }

    col = func_80182090(*(s32 *)(arg0 + 0xEC), 0x2800);
    pa = (V8 *)(arg0 + 0x2C);

    for (i = 0; i < 12; i++) {
        t = (G3 *)func_80010A08(0x1C);
        t->rgb0 = col;
        *((u8 *)t + 7) = 0x32;
        t->rgb2 = col;
        t->rgb1 = col;
        t->tag = 0x06000000;
        otz = RotTransPers((s32)&pa[i], (s32)&t->xy0, &p, &flag);
        RotTransPers((s32)&pa[(i + 1) % 12], (s32)&t->xy1, &p, &flag);
        RotTransPers(arg0 + 0xF4, (s32)&t->xy2, &p, &flag);
        otz = func_801823D4(otz, -0x1A);
        AddPrim(D_800A651C[*(u16 *)&D_800B9A02].a + otz * 4, t);
        func_8012E28C(otz, zpush);
    }
}


s32 func_80182090(s32 color, s32 mult) {
    s32 g = ((u32)color >> 8) & 0xFF;
    s32 r = color & 0xFF;
    s32 b = ((u32)color >> 16) & 0xFF;

    r = func_80182118(r, mult);
    g = func_80182118(g, mult);
    b = func_80182118(b, mult);
    return r | (g << 8) | (b << 16);
}


s32 func_80182118(s32 a0, s32 a1) {
    a0 = (a0 * a1) >> 12;
    if (a0 < 0) {
        a0 = 0;
    } else if (a0 >= 0x100) {
        a0 = 0xFF;
    }
    return a0;
}


extern void func_80016714(void *a0, s32 a1);
extern s32 D_801B1750;

void func_80182148(void) {
    func_80016714(&D_801B1750, 0x400);
}


extern void func_8017DB6C(s32 a0);
extern void func_80182268(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80182170(void *a0)
{
    void *s0;
    s32 v1;

    s0 = a0;
    v1 = *(u16 *)((u8 *)s0 + 0x2);

    switch (v1) {
    case 0:
    case 1:
    case 2:
        return;

    case 3:
        func_8017DB6C(0);
        if (*(u16 *)((u8 *)s0 + 0x34) < 2) {
            func_80182268(-0x7000, 0x7000, -0x39, 0x230);
        } else {
            func_80182268(-0x10, 0x10, 0x1B0, 0x1CA);
        }
        return;

    case 4:
        func_80182268(-0x7000, 0x7000, 0x140, 0x230);
        return;

    case 5:
        func_80182268(-0x7000, 0x7000, 0x140, 0x230);
        return;

    case 6:
        func_80182268(-0x7000, 0x7000, -0x39, 0x230);
        return;

    case 7:
        func_80182268(-0x7000, 0x7000, -0x39, 0x230);
        return;

    case 8:
        func_80182268(-0x7000, 0x7000, -0x39, 0x3D0);
        return;
    }
}


#include "common.h"

extern s16 D_80126B5E;
extern s16 D_80126B66;

void func_80182268(s32 a0, s32 a1, s32 a2, s32 a3) {
    if (D_80126B5E < a0) {
        D_80126B5E = a0;
    }
    if (a1 < D_80126B5E) {
        D_80126B5E = a1;
    }
    if (D_80126B66 < a2) {
        D_80126B66 = a2;
    }
    if (a3 < D_80126B66) {
        D_80126B66 = a3;
    }
}


extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u8 D_80189514[];
extern u8 D_8018950C;
extern s16 D_80126B9A;

s32 func_801822F0(void)
{
    func_8012F568(1, 0xC01A, 0, 0x5A, &D_80189514, &D_8018950C);
    D_80126B9A = 0;
}


extern s32 func_8012BEE8(s32 a0);
extern s16 D_80126B66;
extern u16 D_80126B62;
extern u8 D_80189524[];
extern u8 D_8018951C;
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s16 D_80126B9A;

void func_8018233C(s32 *a0)
{
    if (func_8012BEE8((s32)a0) == 0) {
        return;
    }
    if (D_80126B66 >= -0x38) {
        return;
    }
    if ((s16)D_80126B62 < -0x1B8) {
        return;
    }
    func_8012F568(1, 0xC018, 0, 0x5A, &D_80189524, &D_8018951C);
    D_80126B9A = 0;
    a0[7] = 0x5A;
}


s32 func_801823D4(s32 param_1, s32 param_2)
{
    param_1 = param_1 + param_2;
    if (param_1 < 0) {
        param_1 = 0;
    } else if (0xfff < param_1) {
        param_1 = 0xfff;
    }
    return param_1;
}


extern void func_80139914(s32 a0);
void func_801823FC(s32 a0) {
    s32 v1;
    if (a0 == 0) return;
    if (*(s32 *)a0 == 0) return;
    v1 = *(s16 *)(a0 + 4);
    if (v1 == 0) return;
    if (v1 == 0xE) return;
    func_80139914(a0);
}


extern void func_80146D90(s32 a0);
    extern s32 D_80126B58;
    void func_80182448(void) {
        ((void (*)(void *))func_80146D90)(&D_80126B58);
    }


void func_80182470(void) {
    extern s16 D_80126B66;
    extern s32 func_80180284(void);
    if (D_80126B66 >= 0xC0) {
        func_80180284();
    }
}



extern s32 D_801270C8;

void func_801824A0(void) {
    D_801270C8 = 2;
}


#include "common.h"

/* func_801824B4 — 5-way state dispatch on the u16 state field at +0x34.
 *
 * SECOND-PASS KEY (what the first pass got wrong): the function is **void**,
 * and the `addiu $v0,$zero,-0x178` sitting in the dispatch's
 * `beq $v1,$v0,.L80182598` delay slot is NOT a default return value — it is
 * case 3's OWN compare constant, stolen from the head of the case-3 block by
 * the delay-slot filler (legal precisely because $v0 is dead on the
 * fall-through/default path of a void function).  Reading it as a return value
 * forces an s32 signature, which then costs `move v0,zero` on the early
 * return, `li v0,3` in case 3, and a re-materialized `li v0,-376` on the
 * (unreachable) v1<2 dispatch corner — the first pass's 7 residuals, all three
 * sub-classes at once.  Corollary worth banking: a constant materialized in a
 * dispatch-tree delay slot may belong to the BRANCH TARGET, not the fallthrough.
 *
 * Second tell in the same vein: `addu $a0,$s0,$zero` in `jal func_80178970`'s
 * own delay slot cannot be a hoisted argument for the *later* func_80178D18
 * call ($a0 is caller-saved and the intervening call clobbers it) — so
 * func_80178970 genuinely TAKES the object pointer.  The TU declares it
 * `extern int func_80178970(void);` (line 2536), so the arity is recovered by
 * a cast at the use site, exactly as this TU's own func_801846F4 (line 4716)
 * does for func_80178D18.
 *
 * Declarations (law 2 — copied verbatim from this TU where they exist):
 *   func_80029124 @ 503, func_80029178 @ 65, func_8016F388 @ 1955,
 *   func_80178970 @ 2536, func_80178B18 @ 2537, func_80178D18 @ 2544,
 *   D_80126B62 @ 1792 (`extern u16`, cast to s16 at the single use so the
 *   lhu+sext folds to a bare `lh`), func_80181C74 defined @ 3724.
 *   func_80180300 is INCLUDE_ASM'd @ 3587 with no decl — fleet-unanimous
 *   `void func_80180300(void *a0)` adopted.  D_801270CC: fleet `extern s32`.
 *   D_80188D50 / D_801A249C are address-of-only opaques with no decl in this
 *   TU — declared in this TU's own local style (cf. D_801B1750 @ 3744:
 *   `extern s32 D_x;` + `&D_x`).
 *
 * Verified: match_one MATCH (68 ins), and the whole TU re-compiles clean with
 * this body substituted for the INCLUDE_ASM (no redeclaration conflicts).
 */

extern void func_80181C74(s32 *a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8016F388(void);
extern int func_80178970(void);
extern void func_80178D18(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_80180300(void *a0);
extern u16 D_80126B62;
extern s32 D_801270CC;
extern s32 D_80188D50;
extern s32 D_801A249C;

void func_801824B4(void *a0)
{
    void *s0;
    s32 v1;

    s0 = a0;
    v1 = *(u16 *)((u8 *)s0 + 0x34); /* state */

    switch (v1) {
    case 0:
        func_80178B18((s32)s0, (s32)&D_80188D50);

        /* tail duplicated in case 0 and case 1; cross_jump merges the two
         * scheduled suffixes into the single physical block .L80182564 (§193-C
         * — suffix-only merge, so it must be written at the END of both arms) */
        func_8016F388();
        *(u16 *)((u8 *)s0 + 0x34) = *(u16 *)((u8 *)s0 + 0x34) + 1;
        return;

    case 1:
        if ((func_80029178(0x11E) & 0xFF) != 0) {
            func_80029124(0x11E, 0);
            func_80181C74((s32 *)s0, (s32)&D_801A249C);
        }

        if (((s32 (*)(void *))func_80178970)(s0) == 0) {
            return;
        }
        ((void (*)(void *))func_80178D18)(s0);

        func_8016F388();
        *(u16 *)((u8 *)s0 + 0x34) = *(u16 *)((u8 *)s0 + 0x34) + 1;
        return;

    case 2:
        /* cse substitutes the case-equality register for the literal 2, so the
         * store is `sw $v1, %lo(D_801270CC)($at)` with no `li` */
        D_801270CC = v1;
        func_80180300(s0);
        return;

    case 3:
        if ((s16)D_80126B62 != -0x178) {
            *(u16 *)((u8 *)s0 + 0x34) = 0;
        }
        return;
    }
}


s32 func_801825C4(s32 *a0) {
        return *(u16 *)((s32)a0 + 0x2) != 0x3;
    }



s32 func_801825D8(s32 *a0) {
        return *(u16 *)((s32)a0 + 0x2) != 0x4;
    }


extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801A249C;
extern s32 func_801399F0(s32 a0);
extern s32 D_801B1B54;
extern void func_80174714(void);
extern void func_801823FC(s32 a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern u8 D_801889F8[];
extern u8 D_801A08B4[];
extern s16 D_801B1714;
extern s16 D_801B1708;
extern s16 D_801B1724;
extern s16 D_801B1744;
extern s16 D_801B1710;
extern s32 D_801270C8;
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8016F388();
extern void func_80180D84(void *arg0);
extern u8 D_80188E40[];

void func_801825EC(s32 param_1)
{
    u16 var;

    if ((func_80029178(0x120) & 0xFF) != 0) {
        func_80029124(0x120, 0);
        func_8012A828(param_1, &D_801A249C);
    }

    if (func_801399F0(D_801B1B54) != 0) {
        func_80174714();
        func_801823FC(D_801B1B54);
        *(u16 *)(param_1 + 2) = 3;
        func_8012E8E0(param_1, (s32)&D_801889F8);
        func_8012A828(param_1, &D_801A08B4);
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        var = (*(u16 *)&D_801B1714);
        *(u16 *)(param_1 + 0x34) = 0;
        *(u16 *)(param_1 + 0xDC) = 0;
        *(u16 *)(param_1 + 0xDE) = 0;
        D_801B1708 = 0;
        D_801B1724 = 0;
        D_801B1744 = 1;
        D_801B1710 = var + 1;
        if (D_801B1710 >= 4) {
            func_80180D84((void *)param_1);
        } else {
            func_80178B18(param_1, (s32)&D_80188E40);
            func_8016F388();
            D_801270C8 = 2;
        }
    }
}


extern s32 func_8012BEE8(s32 arg);
extern s16 D_80126B66;
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s16 D_801B1714;
extern s16 D_801B1708;
extern s16 D_801B1724;
extern s16 D_801B1744;
extern s16 D_801B1710;
extern s32 func_80178B18(s32 param_1, s32 param2);
extern void func_8016F388();
extern s32 D_801270C8;
extern void func_80180D84(void *arg0);
extern u8 D_801889F8[];
extern u8 D_801A08B4[];
extern u8 D_80188E40[];

void func_80182720(s32 arg0) {
    u16 var;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (func_8012BEE8(arg0) != 0) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        break;
    case 1:
        if (D_80126B66 >= 0xC0) {
            *(u16 *)(arg0 + 2) = 3;
            func_8012E8E0(arg0, (s32)&D_801889F8);
            func_8012A828(arg0, &D_801A08B4);
            *(s32 *)(arg0 + 0x1C) = 0x3C;
            var = (*(u16 *)&D_801B1714);
            *(u16 *)(arg0 + 0x34) = 0;
            *(u16 *)(arg0 + 0xDC) = 0;
            *(u16 *)(arg0 + 0xDE) = 0;
            D_801B1708 = 0;
            D_801B1724 = 0;
            D_801B1744 = 1;
            D_801B1710 = var + 1;
            if (D_801B1710 >= 4) {
                func_80180D84((void *)arg0);
            } else {
                func_80178B18(arg0, (s32)&D_80188E40);
                func_8016F388();
                D_801270C8 = 2;
            }
        }
        break;
    }
}


void func_80182850(s32 *a0) {
    extern void func_8012B2CC(s32 a0);
    extern void func_8012B200(void *a0);
    extern void func_8012B14C(s32 a0, s32 a1);
    extern void (*D_80188EE4)(void *);
    extern s32 D_80188EF0;
    s32 v0;

    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B14C((s32)a0, (s32)&D_80188EE4);
    v0 = D_80188EF0;
    a0[7] = 0;
    a0[18] = v0;
}


extern void func_8012AD80(s32 a0);
extern s32 D_80188EF4;
extern void func_80015D4C(s32 a0, s32 a1, s32 a2, s32 a3, u8 a4, u8 a5, u8 a6, u16 a7, u16 a8);

void func_801828A0(s32 a0) {
    s32 s0;
    s32 sum;
    s32 x;

    s0 = a0;
    func_8012AD80(s0);
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) += D_80188EF4;
    sum = *(s32 *)(s0 + 0x1C) + 4;
    x = *(s32 *)(s0 + 0x1C) = sum;
    if (x >= 0x100) {
        x = 0xFF;
    }
    func_80015D4C(-0xA0, -0x78, 0x140, 0xF0, x, x, x, 0x20, 1);
}


s32 func_80182938(u8 *param_1)
{
    *(u16 *)(*(u8 **)(param_1 + 0x20) + 0x10) = 0;
    *(u32 *)(param_1 + 0x1C) = 0xFF;
    return 0xFF;
}


void func_80182950(u8 *param_1)
{
    s32 x;

    x = *(s32 *)(param_1 + 0x1C) - 0x10;
    *(s32 *)(param_1 + 0x1C) = x;
    if (x < 0) {
        x = 0;
    }
    x &= 0xFF;
    func_80015D4C(-0xA0, -0x78, 0x140, 0xF0, x, x, x, 0x20, 1);
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8017DB6C(s32 a0);
extern s16 D_801B173C;

void func_801829B4(void *a0)
{
    void *s0;
    s32 v1;

    s0 = a0;
    v1 = *(u16 *)((u8 *)s0 + 0x34);

    switch (v1) {
    case 0:
        *(u16 *)((u8 *)s0 + 0x34) = *(u16 *)((u8 *)s0 + 0x34) + 1;
        return;

    case 1:
        if (((s32 (*)(void *))func_80178970)(s0) == 0) {
            return;
        }
        ((void (*)(void *))func_80178D18)(s0);

        *(u16 *)((u8 *)s0 + 0x34) = *(u16 *)((u8 *)s0 + 0x34) + 1;
        return;

    case 2:
        func_8017DB6C(1);
        *(u16 *)((u8 *)s0 + 0x34) = *(u16 *)((u8 *)s0 + 0x34) + 1;
        return;

    case 3:
        func_8017DB6C(1);
        D_801B173C = 1;
        return;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8017ADE8(s32 a0);
extern s32 D_801889F4[];
extern u8 D_801889F8[];
extern u8 D_801A01A4[];

void func_80182A78(void *a0) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, D_801889F4[*(s16 *)((s32)a0 + 0x70)]);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = 0x1000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x1000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 0x1000;
    func_8017ADE8(1);
    *(s16 *)((s32)a0 + 2) = 1;
    func_8012E8E0((s32)a0, (s32)&D_801889F8);
    func_8012A828((s32)a0, &D_801A01A4);
}


#include "common.h"

extern void func_801818D8();
extern void (*D_8018907C[])(void);
extern s32 func_8012E544(s32 a0);
extern void func_8012E8A8(u8 *a0);

void func_80182B44(void *a0) {
    u16 vec[4];
    s32 rec;

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) - 1;
        vec[0] = *(u16 *)((s32)a0 + 6);
        vec[1] = *(u16 *)((s32)a0 + 0xA);
        vec[2] = *(u16 *)((s32)a0 + 0xE);
        func_801818D8(vec, 0x28, *(s32 *)((s32)a0 + 0x1C),
                      D_8018907C[*(s16 *)((s32)a0 + 0x70)]);
    }
    rec = func_8012E544(0x2CD);
    if ((rec != 0) && (*(u16 *)(rec + 2) >= 8)) {
        func_8012E8A8(a0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_80189044[];
extern u8 D_80189054[];

void func_80182BE8(void *a0)
{
    s32 iVar2;

    iVar2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = iVar2;
    if (iVar2 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(iVar2, D_80189044[*(s16 *)((s32)a0 + 0x70)]);

    *(s16 *)((s32)a0 + 0x2) = 1;
    func_8012E8E0((s32)a0, (s32)&D_80189054[*(s16 *)((s32)a0 + 0x70) * 8]);
    *(s32 *)((s32)a0 + 0x1C) = 0;
}


#include "common.h"

extern s16 D_801B171C;
extern s16 D_801B1720;
extern u16 D_801890C4[];
extern void (*D_8018907C[])(void);
extern s32 func_80181C1C(s16 *a0);
extern s32 func_80180EE8();
extern void func_8012E688(s32 a0, u16 a1, u16 a2);
extern void func_801818D8();

void func_80182C74(void *arg0) {
    s32 s0;
    u16 sp10[3];

    s0 = (s32)arg0;
    if (D_801B171C != 0) {
        if (func_80181C1C((s16 *)s0) < 0xC41) {
            *(s32 *)(s0 + 0x1C) = 10;
            D_801B1720 = *(u16 *)(s0 + 0x70);
            if (func_80180EE8() != 0) {
                func_8012E688(s0, D_801890C4[*(s16 *)(s0 + 0x70)], 0);
            }
        }
    }
    if (*(s32 *)(s0 + 0x1C) != 0) {
        *(s32 *)(s0 + 0x1C) -= 1;
        sp10[0] = *(u16 *)(s0 + 0x6);
        sp10[1] = *(u16 *)(s0 + 0xA);
        sp10[2] = *(u16 *)(s0 + 0xE);
        func_801818D8(sp10, 0x30, *(s32 *)(s0 + 0x1C), ((s32 *)D_8018907C)[*(s16 *)(s0 + 0x70)]);
    }
}


extern void func_8012C1B8(void);   /* fleet-modal spelling, cast at call */
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void (*D_80189094[])(void);
extern void (*D_801890A4[])(void);

void func_80182D4C(void *a0)
{
    s32 v0;
    s32 v1;
    s16 v;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C810(v0, ((s32 *)D_80189094)[*(s16 *)((s32)a0 + 0x70)]);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(v1 + 0x4) |= 0x8000;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x1C) = 0xC00;
    *(u16 *)(v1 + 0x1A) = 0xC00;
    *(u16 *)(v1 + 0x18) = 0xC00;

    *(s16 *)((s32)a0 + 0x2) = 1;
    v = *(s16 *)((s32)a0 + 0x70);
    func_8012E8E0((s32)a0, (s32)D_801890A4 + (v << 3));

    *(s32 *)((s32)a0 + 0x1C) = 0;
}


extern s32 D_80126B60;
extern s32 func_80047948(s32 a0);

s32 func_80182E14(void *a0)
{
    s32 s0;
    u16 v0;
    s16 t;

    s0 = (s32)a0;
    v0 = *(u16 *)(s0 + 0x34);
    if (v0 == 0) goto body0;
    if (v0 == 1) goto body1;
    return 0;

body0:
    v0 = *(u16 *)(s0 + 0xFC) + 0x40;
    *(u16 *)(s0 + 0xFC) = v0;
    if ((s16)v0 >= 0x400) {
        D_80126B60 -= 0x80000;
        *(u16 *)(s0 + 0x34) += 1;
    }
    *(s32 *)(s0 + 0x8) -= (0x1000 - func_80047948(*(s16 *)(s0 + 0xFC))) << 7;
    goto ret0;

body1:
    t = *(s16 *)(s0 + 0xA);
    if (t >= -0x300) goto tminus8;
    *(s16 *)(s0 + 0xA) = -0x300;
    return 1;

tminus8:
    *(s16 *)(s0 + 0xA) = t - 8;

ret0:
    return 0;
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80182EFC(void) {
        func_8002D4C8(0xC0E, 0);
    }


extern void func_80015D4C(s32 a0, s32 a1, s32 a2, s32 a3, u8 a4, u8 a5, u8 a6, u16 a7, u16 a8);
extern s16 D_801B1748;

void func_80182F20(void) {
    s32 x;
    x = D_801B1748;
    x = x + 4;
    if (x >= 0x100) {
        x = 0xFF;
    }
    func_80015D4C(-0xA0, -0x78, 0x140, 0xF0, x, x, x, 0x20, 2);
    D_801B1748 = x;
}


extern void func_80015D4C(s32 a0, s32 a1, s32 a2, s32 a3, u8 a4, u8 a5, u8 a6, u16 a7, u16 a8);
extern s16 D_801B174C;

void func_80182F98(void) {
    s32 x;
    x = D_801B174C;
    x = x - 3;
    if (x < 0) {
        x = 0;
    }
    func_80015D4C(-0xA0, -0x78, 0x140, 0xF0, x, x, x, 0x20, 2);
    D_801B174C = x;
}


void func_8018300C(void) {
    extern void (*D_80188EDC[])(void);
    extern St_8017E95C_r aD801B12F0[4] __asm__("D_801B12F0");
    s32 rec;

    rec = func_8012E544(0x2CD);
    if (rec != 0) {
        func_8012E8E0(rec, (s32)D_80188EDC);
        func_80016714(aD801B12F0, 0x410);
        D_801B12F0[0].unk0 = 2;
        D_801B12F8[0].unk0 = 0;
    }
}


extern void func_800D1724(s32 a0);
    extern s32 D_801886A4;
    void func_80183068(void) {
        ((void (*)(void *))func_800D1724)(&D_801886A4);
    }


#include "common.h"

extern s32 func_8012E544(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801A538C[];

void func_80183090(void) {
    s32 v0;
    v0 = func_8012E544(0x2CD);
    if (v0 != 0) {
        func_8012A828(v0, D_801A538C);
    }
}


extern s32 func_8012E544(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801A5CB4[];

void func_801830C8(void) {
    s32 v0;
    v0 = func_8012E544(0x2CD);
    if (v0 != 0) {
        func_8012A828(v0, D_801A5CB4);
    }
}


extern s32 func_8012E544(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801A6584[];

void func_80183100(void) {
    s32 v0;
    v0 = func_8012E544(0x2CD);
    if (v0 != 0) {
        func_8012A828(v0, D_801A6584);
    }
}


#include "common.h"

extern void func_8012C1B8(void);   /* fleet-modal spelling, adopted from sibling draft func_80181148 (§183 SIGNATURE-cast-at-call); return recovered by the cast below */
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern u8 D_80189254[];
extern u8 D_8019A6B0[];
extern u8 D_801892A4[];
extern u8 D_80189294[];

void func_80183138(void *a0) {
    s32 v0;
    s32 v1;
    s16 v;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    if (func_8012C354((s32)a0, (s32)D_80189254) == 0) {
        return;
    }

    func_8001C810(*(s32 *)((s32)a0 + 0x20), (s32)D_8019A6B0);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(v1 + 0x4) |= 0x8040;

    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xB4) = -1;
    *(s16 *)((s32)a0 + 0xAE) = -1;
    *(s16 *)((s32)a0 + 0x2) = 1;
    v = *(s16 *)((s32)a0 + 0x70);

    func_8012E8E0((s32)a0, (s32)D_801892A4 + (v << 3));

    *(u8 *)((s32)a0 + 0x75) = 8;
    func_8012A828((s32)a0, D_80189294);

    *(s32 *)((s32)a0 + 0x1C) = 0xA;
}


extern void func_8012BE54(s32 a0);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801892CC;

void func_80183228(void *a0) {
    u16 *v0;

    v0 = *(u16 **)((s32)a0 + 0x20);
    *(u16 *)((s32)v0 + 0x1C) = 0xC00;
    *(u16 *)((s32)v0 + 0x1A) = 0xC00;
    *(u16 *)((s32)v0 + 0x18) = 0xC00;
    if (((s32 (*)(s32))func_8012BE54)(a0) < 0x6401) {
        func_80178B18((s32)a0, (s32)&D_801892CC);
        *(u16 *)((s32)a0 + 0x2) = 2;
        *(u16 *)((s32)a0 + 0x34) = 0;
        func_8002D4C8(0xB01, 0);
    }
}


void func_80183298(void *a0)
{
    extern s32 func_8012E544(s32 a0);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8002D4C8(s32 a0, s32 a1);

    void *s0;
    u16 state;

    s0 = a0;

    if (func_8012E544(0x2CD) == 0) {
        return;
    }

    state = *(u16 *)((u8 *)s0 + 0x34);

    switch (state) {
    case 0:
        ((void (*)(void *))func_80178970)(s0);
        break;

    case 1:
        if (((s32 (*)(void *))func_80178970)(s0) == 0) {
            break;
        }
        ((void (*)(void *))func_80178D18)(s0);
        *(u16 *)((u8 *)s0 + 0x2) = 3;
        func_8002D4C8(0xB02, 0);
        break;
    }
}


void func_80183328(void) {
}

#include "common.h"

extern void func_8012C1B8(void);   /* fleet-modal spelling, cast at call */
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);

extern s32 D_801893AC[];
extern u8 D_801893B4[];
extern u8 D_801893C4[];

void func_80183330(void *a0)
{
    s32 iVar2;

    iVar2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = iVar2;
    if (iVar2 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(iVar2, D_801893AC[*(s16 *)((s32)a0 + 0x70)]);

    *(u16 *)((s32)a0 + 0x5C) = 0xC00;
    *(s32 *)((s32)a0 + 0x58) = ((s32)&D_801893C4 | 0x40000000);
    *(u8 *)((s32)a0 + 0x75) = 8;
    *(s16 *)((s32)a0 + 0x2) = 1;
    func_8012E8E0((s32)a0, (s32)&D_801893B4[*(s16 *)((s32)a0 + 0x70) * 8]);
    *(s32 *)((s32)a0 + 0x1C) = 0x1E;
    *(s16 *)((s32)a0 + 0x34) = 0;
}


extern s32 D_80189420[];

extern void func_801814C4(void *a0);

void func_801833E8(void *a1) {
    if (*(s32 *)((s32)a1 + 0xDC) < D_80189420[*(s16 *)((s32)a1 + 0x70)]) {
        *(s32 *)((s32)a1 + 0xDC) = *(s32 *)((s32)a1 + 0xDC) + 0xC0000;
    }
    if (*(s32 *)((s32)a1 + 0xDC) > D_80189420[*(s16 *)((s32)a1 + 0x70)]) {
        *(s32 *)((s32)a1 + 0xDC) = D_80189420[*(s16 *)((s32)a1 + 0x70)];
    }
    {
        void *prim = *(void **)((s32)a1 + 0x20);
        *(u16 *)((s32)prim + 0x14) = *(u16 *)((s32)prim + 0x14) + *(u16 *)((s32)a1 + 0xDE);
    }
    if (*(s16 *)((s32)a1 + 0xFC) != 0) {
        func_801814C4(a1);
    }
}


extern void func_80181514(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E8E0(s32 a0, s32 a1);

extern u8 D_80189408[];

void func_80183490(s32 arg0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v1;
    register s32 a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    s32 h;

    v0 = *(s32 *)(arg0 + 0xDC);
    v1 = -0x80000;
    v0 = v0 + v1;
    v1 = -0x2800000;
    *(s32 *)(arg0 + 0xDC) = v0;
    if (v0 < v1) {
        *(s32 *)(arg0 + 0xDC) = v1;
    }

    v0 = *(s32 *)(arg0 + 0x20);
    a1 = *(u16 *)(arg0 + 0xDE);
    v1 = *(u16 *)(v0 + 0x14);
    v1 = v1 + a1;
    *(u16 *)(v0 + 0x14) = v1;

    func_80181514((void *)arg0);

    if (func_8012BEE8(arg0) != 0) {
        h = *(s16 *)(arg0 + 0x70);
        *(u16 *)(arg0 + 0x2) = 1;
        v0 = (s32)D_80189408;
        *(u16 *)(arg0 + 0xFC) = 0;
        h = h << 3;
        func_8012E8E0(arg0, (s32)&D_80189408[h]);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);

extern s32 D_801893FC[];
extern u8 D_80189408[];

void func_80183528(void *a0)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801893FC[*(s16 *)((s32)a0 + 0x70)]);
    *(s16 *)((s32)a0 + 2) = 1;
    func_8012E8E0((s32)a0, (s32)D_80189408 + (*(s16 *)((s32)a0 + 0x70) << 3));
}


extern s32 D_801270CC;
extern void func_8012E88C(void);
extern void func_8018233C(s32 *a0);
extern void func_8012E8A8(u8 *a0);

void func_801835B0(s32 *a0)
{
    if (D_801270CC == 2) {
        func_8012E88C();
        func_8018233C(a0);
    } else {
        func_8012E8A8((u8 *)a0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern s8 D_80189438[];
extern u8 D_801894E0[];
extern u8 D_80189498[];

void func_80183604(void *a0) {
    s32 v0;
    s32 v1;
    s32 v2;
    s16 v;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001CA1C(v0, (s32)&D_80189438);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x1C) = 0x6000;
    *(u16 *)(v1 + 0x1A) = 0x6000;
    *(u16 *)(v1 + 0x18) = 0x6000;

    v2 = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(v2 + 0x4) |= 0x50000000;

    *(s16 *)((s32)a0 + 0x2) = 1;
    v = *(s16 *)((s32)a0 + 0x70);
    func_8012E8E0((s32)a0, (s32)D_801894E0 + (v << 3));

    func_8012A828((s32)a0, D_80189498);

    *(s32 *)((s32)a0 + 0x1C) = 0;
}



extern void func_80019064(void *a0);

void func_801836CC(void *a0) {

    extern u8 D_801AD9E4;
    extern void (*D_801ADA0C[])(void *);
    func_80019064(&D_801AD9E4);
    D_801ADA0C[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_80183724(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_80183774(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


extern u8 D_801AD9EC[];
extern void func_80147324(s32 a0);
extern int func_801511E0(int arg);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80183988(void);
extern s32 func_80172630(u8 *a0);
extern void func_80146CA0(void *a0);

void func_80183774(s32 a0)
{
    s32 s0 = a0;
    func_80147324(0x451);
    ((void (*)(s32))func_801511E0)(s0);
    ((void (*)(s32, s32))func_80154274)(s0, (s32)D_801AD9EC);
    ((void (*)(s32))func_80149020)(s0);
    *(u8 *)(s0 + 0xDE) = 0x1E;
    *(u8 *)(s0 + 0xDF) = 0;
    func_80183988();
    ((void (*)(s32))func_80172630)(s0);
    ((void (*)(s32))func_80146CA0)(s0);
}



/* func_801837E0 @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_801837E0 --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_801837E0.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_80183934 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_801839AC` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
 * stub for this function) — a simple "find a free slot, mark it used" scan
 * returning the slot index or -1.
 *
 * Body shape (byte-confirmed against the .s, no residual after first draft):
 *   func_80015978(a0+4, buf)     -- fills a 3-short (SVECTOR-shaped) local from
 *                                    the actor's position substruct at a0+4; this
 *                                    exact `s16 buf[4]; func_80015978(a0+4,(s32*)buf);`
 *                                    idiom is the established fleet form (see
 *                                    engine_core.h DEFINE_func_8014A380/8016D778/
 *                                    8017C908 dedup macros).
 *   buf[1] -= 0x40                -- immediately after the call. The readback here
 *                                    is `lhu` (not `lh`) even though buf is a SIGNED
 *                                    s16 array: gcc-2.7.2 always emits `lhu` for a
 *                                    plain HImode load that feeds straight into an
 *                                    `sh` store (cookbook: "It does NOT cost you the
 *                                    lhu on readback" bullet, P30 wave 4). No cast
 *                                    needed, no separate unsigned local needed.
 *   do { ... } while (++i < 3)    -- the asm has NO initial top-of-loop test before
 *                                    label .L80182318 (s3=0 set, then falls straight
 *                                    into the body) -- a genuine do-while in the
 *                                    source, not a for-loop gcc happened to rotate.
 *   if (func_801839AC() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
 *      - the three back-to-back `rand()` calls assign straight to 3 locals in
 *        source order; gcc's own delay-slot filler moves each captured value into
 *        a callee-saved reg ($s0/$s1) via the NEXT call's branch-delay slot
 *        (standard call-crossing-value idiom, cookbook "ORDER" register-allocation
 *        entry) -- no manual reordering needed, plain sequential C reproduces it.
 *      - the final random offset is computed into a **s16 local** (not s32): the
 *        assignment truncates+sign-extends via `sll/sra` in-register (matches the
 *        target's `sll $s0,$s0,16 / sra $s0,$s0,16` with NO memory round-trip,
 *        because the s16 value is used immediately as a call argument rather than
 *        stored to a separate memory slot).
 *   cnt = *(u8*)(a0+0xDE); *(u8*)(a0+0xDE) = cnt + 0xff; if (cnt == 0) { ... } else { ... }
 *      - `lbu` (not `lb`) for the read: the "feeds only a truncated store + an
 *        equality-to-zero test" idiom, so either signedness of the C type reads
 *        identically; u8 chosen to match the common counter-byte convention used
 *        elsewhere in this TU.
 *      - THE ONE non-obvious lever: write the decrement as `cnt + 0xff`, not
 *        `cnt - 1`. Both are mathematically identical mod 256 (only the low byte
 *        survives the `sb`), and both compile to a single `addiu`, but gcc-2.7.2
 *        picks a DIFFERENT immediate encoding for each source spelling: `cnt - 1`
 *        emits `addiu $v0,$v1,-1` (imm 0xFFFF, sign-extended -1); `cnt + 0xff`
 *        emits `addiu $v0,$v1,0xFF` (imm 0x00FF, the literal as typed) — which is
 *        what the target has. Confirmed the signedness of `cnt` (s8 vs u8) makes
 *        no difference here; the literal's own spelling is the lever. New
 *        cookbook idiom candidate (not in §31 as of this match).
 */

extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_801839AC(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_80183934(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_801837E0(s32 param_1)
{
    s16 buf[4];
    s32 i;
    s32 iVar1;
    s32 uVar3;
    s32 uVar4;
    s32 uVar5;
    s16 rnd;
    u8 cnt;

    func_80015978(param_1 + 4, (s32 *)buf);
    buf[1] -= 0x40;

    i = 0;
    do {
        iVar1 = func_801839AC();
        if (iVar1 >= 0) {
            func_80146A6C(0x51, (void *)param_1, buf[0], buf[1], buf[2], iVar1, 0);

            uVar3 = rand();
            uVar4 = rand();
            uVar5 = rand();
            rnd = (uVar3 & 3) * 0x400 + (uVar4 & 3) * 0xfa + (uVar5 & 3) * 0x44;
            func_80146A6C(0x52, (void *)param_1, 0, -0x20, 0x10, rnd, 0);
        }
        i++;
    } while (i < 3);

    cnt = *(u8 *)(param_1 + 0xde);
    *(u8 *)(param_1 + 0xde) = cnt + 0xff;
    if (cnt == 0) {
        func_80183934(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_80183934 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
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
 *   func_80183934  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_80183934(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_80183988(void)
{
    extern u8 D_801B1BE3;
    s32 i = 19;
    u8 *p = &D_801B1BE3;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_801839AC(void)
{

    extern u8 D_801B1BD0[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801B1BD0;
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



extern void (*D_801ADA18[])(void);

void func_801839F0(void *a0) {
    D_801ADA18[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @unstuck(P36): none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801B1BE4 + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_80183C20(void*);
extern void func_80183BF0(s32*);
extern int rand(void);

void func_80183A2C(int param_1)
{

    extern unsigned char D_801B1BE4[];
    int iVar3;
    int iVar3b;
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801B1BE4 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    iVar3b = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_80183C20)(iVar5);
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
        ((void (*)(int))func_80183BF0)(param_1);
    }
}




extern s32 func_80183C34(s32 *a0, s32 a1);
extern void func_80183BF0(s32 *a0);

void func_80183B78(s32 *a0)
{

    extern unsigned char D_801B1BE4[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801B1BE4 + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_80183C34(a0, table_base) == 0) {
            return;
        }
    }

    func_80183BF0(a0);
}



















extern void func_80146C3C(void);
void func_80183BF0(s32 *param_1)
{
    extern u8 D_801B1BD0[];

    D_801B1BD0[param_1[0x2c / 4]] = 0;
    ((void (*)(s32 *))func_80146C3C)(param_1);
}



void func_80183C20(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_80183C34 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_80183C34(s32 *a0, s32 a1);
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
s32 func_80183C34(s32 *a0, s32 a1) {
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



extern void (*D_801ADA50[])(void);

void func_80183C9C(void *a0) {
    D_801ADA50[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_80183CD8(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_80183D74(s32 param_1);

void func_80183D24(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_80183D74(param);
    }
}


void func_80183D6C(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_80183ED8();

void func_80183D74(s32 param_1) {

    extern u32 *D_801ADA48[];
    extern Blk8 D_801ADA64[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_801ADA48[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_801ADA64[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_80183ED8(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
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

extern SVECTOR_8017E6D8 D_801B20E4[4];
extern struct PW8017E6D8 D_801B2104;
extern struct PW8017E6D8 D_801B2108;
extern u8 D_801B210C, D_801B210D, D_801B210E, D_801B2110, D_801B2111, D_801B2112;
extern int D_801B2114;


/* GTE VARIANT `gte_rt_m`: memory beyond Sony's `gte_rt` — a scheduling steer, its uses are marked (P36 T5) */
#define gte_rt_m()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")


void func_80183ED8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
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

    r0_00 = &D_801B20E4[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801B2114 = 0x50000000;
        D_801B210C = 0;
        D_801B210D = 0;
        D_801B210E = 0;
        D_801B2110 = 0;
        D_801B2111 = 0;
        D_801B2112 = 0;
    }
    D_801B2104 = h[0];
    D_801B2108 = h[1];

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
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}




extern void (*D_801ADAC8[])(void);

void func_80184254(void *a0) {
    D_801ADAC8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801842C0();
    extern void func_80146CA0(void *a0);
    void func_80184290(s32 *a0) {
        func_801842C0(a0);
        ((s32 (*)(s32))func_80146CA0)((s32)a0);
    }


extern void func_80019064(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_80062C14;
extern void *D_801ADA84;
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);

void func_801842C0(s32 a0) {
    func_80019064(&D_80062C14);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0x800;
    func_80154274((s32 *)a0, (s32)&D_801ADA84);
    func_80146DE8((s32 *)a0, 0, 0, 0x180000);
    func_801477E8((s32 *)a0, 0);
    func_80149020((s32 *)a0);
    func_80146CA0((void *)a0);
}


extern u16 D_800B99DA;

void func_80184340(s32 *a0) {
    s32 pad[8];
    func_80149020(a0);
    func_80147A84((s32)a0);
    func_801473EC(a0);
    func_80148038((s32)a0, 0x18000);
    func_80147460((s32)a0);
    if (!(D_800B99DA & 1)) {
        func_8014C010((s32)a0, 2);
    }
    func_801535F4(a0);
    if (*(s16 *)((s32)a0 + 0xE) < -0x38) {
        *(s16 *)((s32)a0 + 0xE) = -0x38;
        func_80146CA0(a0);
    }
}


extern void func_80184410();
extern void func_80159B3C(void*);
extern void func_80165718(s32);
void func_801843D8(void *a0) {
    func_80184410(a0);
    ((s32 (*)(struct S *))func_80159B3C)((struct S *)a0);
    ((void (*)(void *))func_80165718)(a0);
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_80151664(void);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_80184410(s32 a0)
{
    s32 buf[2];

    ((void (*)(s32))func_80151664)(a0);
    func_80015978(a0 + 4, buf);
    func_8012F568(1, 0xC018, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 0x5A, buf, buf);
}



extern void (*D_801AE188[])(void);

void func_80184468(void *a0) {
    D_801AE188[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_80184B50(void);

void func_801844A4(void *a0) {

    extern s32 D_801ADEE0[];
    extern u8 D_801ADE78[];
    extern u8 D_80184FC0[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801ADE78);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801ADEE0[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80184B50);
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
        func_8012A828((s32)a0, D_80184FC0);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_80184578(void *a0) {
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


void func_801845A0(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_801845A8(void *a0) {

    extern s32 D_801AE0C4;
    extern s32 D_801AE0B0;
    extern s32 D_801AE0AC;
    extern s32 D_801AE144;
    extern s32 D_801AE0D8;
    extern s32 D_801ADFA4[];
    extern s32 D_801AE028[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801AE0C4 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801AE0AC = 0;
                D_801AE0B0 = D_801AE028[v0];
            } else {
                D_801AE0B0 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801AE028[v0], 1);
                D_801AE0AC = 2;
            }
        } else {
            D_801AE0C4 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801AE0AC = 0;
            D_801AE0B0 = D_801ADFA4[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801AE0D8);
    } else {
        p = &D_801AE144;
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
extern s32 func_801848F8(void);

void func_801846F4(void *arg0) {

    extern s32 D_801ADEE0[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801ADEE0[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801ADEE0[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_801848F8() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    void func_80184814(void *arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_80184840(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80184850(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_80184860(void *a0) {

    extern s32 D_801ADEE0[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801ADEE0[idx], 1);
}


extern void func_8014ADA8(s32 a0, s32 a1);
    extern s32 D_80126B58;
    void func_801848A0(s32 arg0) {
        s32 temp_v0 = *(s32 *)(arg0 + 0xdc);
        ((void (*)(void *, s32))func_8014ADA8)((void *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
    }


extern s16 func_80174764(void);
    s32 func_801848D4(void) {
        return ((u32)((s32 (*)(void))func_80174764)() == 1);
    }




extern s32 func_80029178(s32 arg);

s32 func_801848F8(void) {

    extern s32 D_801ADEE0[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801ADEE0[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801AE1B0[])(void);

void func_8018495C(void *a0) {
    D_801AE1B0[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80184998(void *a0) {

    extern u8 D_801ADEAC[];
    extern u8 D_801AE870[];
    extern u8 D_801AE650[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801ADEAC) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801AE870);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801AE650);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80184A20(void *a0) {

    extern u8 D_801AE660[];
    extern u8 D_801AE768[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801AE660);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801AE768);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_80184AE0 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801AE870, else
 * D_801AE650), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801AE870 / D_801AE650)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_80184AE0(void *a0) {

    extern u8 D_801AE870[];
    extern u8 D_801AE650[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801AE870);
        } else {
            func_8012A828((s32)a0, D_801AE650);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801AE1A0[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

s32 aF8018A224() __asm__("func_80184B50");

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

    RotTransSV(D_801AE1A0, sv0, &flag);
    RotTransSV(D_801AE1A0 + 8, sv1, &flag);

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






