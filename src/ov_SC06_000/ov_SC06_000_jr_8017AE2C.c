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
extern u8 D_8018A7C0;
extern u8 D_8018A730;
extern u8 D_8018A70C;
extern u8 D_8018A6E8;
extern u8 D_8018A79C;
extern u8 D_8018A778;
extern u8 D_8018A754;
extern u8 D_8018A6C4;
extern void func_80145934(void);
extern u8 D_8018A850;
extern u8 D_8018A82C;
extern u8 D_8018A808;
extern u8 D_8018A7E4;
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
extern unsigned char D_80189C48[];
extern unsigned char D_80189C78[];
extern unsigned char D_80189CC8[];
extern unsigned char D_80189CF8[];
extern unsigned char D_80189D28[];
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
extern void (*D_80189D78[])(void *);
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
extern s32 D_80189E40[];
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
extern u8 D_80189EC8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80189ED0;
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
extern int D_801AD480;
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
extern s32 D_801AD484;
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
extern s32 D_80189F00;
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
extern void (*D_80189FA8[])(void);
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
extern void (*D_80189FCC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80189FBC;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80189FE0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80189FEC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80189FFC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018A014[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018A004;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018A028[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018A044[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018A034;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018A058[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018A06C[])(void);
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
extern s32 D_8018A080;
extern void (*D_8018A0A8[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018A088;
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
extern int (*D_8018A0F4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018A0F8[])(void);
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
extern unsigned short D_8018A55C[];
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
extern void (*D_8018A56C[])(void);
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
extern int D_801AD4B8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018A594[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018A574;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018A584;
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
extern void (*D_8018A5D4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018A5DC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018A5A8;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018A5E8[])(void);
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
extern u8 D_8018A5B8;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801AD4C0;
extern s32 D_801AD4CC;
extern s32 D_801AD4D0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018A624[])(s32 *);
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
extern s32 D_8018A5F8[];
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
extern s32 D_801AD4C8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018A874[])(void);
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
extern char D_8018A694[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018A918[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018AA6C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018A888;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018AA74[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018A898;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018A8B8;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018AA7C[])(void);
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
extern void (*D_8018AAA4[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018AAB0[])(void);
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
extern void (*D_8018A924[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018AB54;
extern void func_8015D380(s32 a0);
extern unsigned char D_80189C38[];
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
extern unsigned char D_8018AB68[];
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
extern s8 D_8018ABA4[];
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
extern u16 D_8018ABEC;
extern u16 D_8018ABEE;
extern u16 D_8018ABF0;
extern s32 D_8018ABF4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018ABFC;
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
extern int D_8018A908;
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
extern unsigned int D_8018AC80[];
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
extern void (*D_8018AD30[])(void);
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
extern u16 D_8018AD60[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018ADC4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801AD4D8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018ADE8[])(void);
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
extern int D_801AD530[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018AE30[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018AE20;
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
extern char D_801ACD90[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018AE38[])(void);
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
extern void (*D_8018AE8C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018AE54;
extern s16 D_8018AE88;
extern s16 D_8018AE86;
extern s16 D_8018AE84;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018AE98[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801AD590;
extern u8 D_801AD591;
extern u8 D_801AD592;
extern u8 D_801AD593;
extern u8 D_801AD594;
extern u8 D_801AD595;
extern u8 D_801AD596;
extern u8 D_801AD597;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018AEA8[])(void);
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
extern s32 D_801AD5D0;
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
extern void (*D_8018AEEC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018AF68[];
extern s32 D_8018AF88[];
extern u8 D_8018B004[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018B024[];
extern u8 D_8018B044[];
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
extern void (*D_8018B0E0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018B15C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801ACDA0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018B168[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018B170[])(void);
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
extern void (*D_8018B238[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018B248[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018B258[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018B264[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018B1C4[];
extern u8   D_8018B1D8[];
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
extern void (*D_8018B27C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018B284[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018B28C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018B294[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018B29C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018B2A4[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018B2AC[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018B360[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018B368[])(void);
extern void func_80169F00(void *a0);
extern char D_8018B318[];
extern char D_8018B2D8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018B3A0[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018B3AC[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018B3F4[])(void);
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
extern void (*D_8018B470[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801AD8F0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018B464[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018B4A8[];
extern unsigned short D_8018B4B0[];
extern unsigned short D_8018B4B8[];
extern unsigned char D_801AD8F8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801AD8F0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018B4C0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801ADA2C;
extern M2C_UNK D_801ADA30;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801AD9B8;
extern void (*D_8018B4F0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801ADA34[];
extern u8 D_801ADA3C[];
extern u8 D_801AD9EC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018B4F8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018B514[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018B51C[])(void);
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
extern void (*D_8018B584[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018B528;
extern u8 D_8018B534;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018B5B8[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018B5C0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018B614[])(void);
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
extern u16 D_8018B648[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018B638[];
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
extern s32 D_8018B664;
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
extern void (*D_8018B6DC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018B6E4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018B6EC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018B6F4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018B6FC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018B704[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018B710[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018B71C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018B728[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018B738[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018B748[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018B750[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018B758[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018B760[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018B768[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018B770[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018B778[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018B780[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018B788[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018B790[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018B798[])(void);
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
extern void (*D_8018B7A0[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018B7A8[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018B7B0[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018B7B8[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018B7C0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018B7C8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018B7D0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018B7D8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018B7E0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018B7E8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018B7F0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018B7F8[])(void);
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
extern void (*D_8018B83C[])(void);
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
extern M2C_UNK D_8018B800;
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
extern void (*D_8018B86C[])(void);
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
extern void (*D_8018B8A8[])(void);
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
extern void (*D_8018B900[])();
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
extern void (*D_8018B910[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018B918[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018BA80[])();
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
extern void (*D_8018BA8C[])();
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
extern M2C_UNK D_801ACFE8;
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
extern s16 D_801B20D8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801AE170;
extern short D_801B2184;
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
extern s32 D_801AE59C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801AE5C4;
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
extern s16 D_801AE580;
extern s32 func_8017A3B0(void);
extern short D_801AE5BC;
extern short D_801AE5B8;
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

extern s16 D_801B20A8;
extern s16 D_801B20AA;
extern s16 D_801B20B4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801B20A8;

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
                    func_8012B744(p, &D_801B20B4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801B20A8+0xC == &D_801B20B4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801B20A8 + 0xC)) < 0x101) {
                    D_801B20A8 = 0;
                    D_801B20AA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801B20B4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801B20A8 + 0xC)) < 0x101) {
            D_801B20A8 = 0;
            D_801B20AA = 0;
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
    extern s16 D_801AE5FC;
    extern s16 D_801AE5FE;
    extern s16 D_801AE600;
    extern s16 D_801AE5F4;
    extern s16 D_801AE5F6;
    extern s16 D_801AE5F8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801AE5FC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801AE5FE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801AE600, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801AE5F4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801AE5F6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801AE5F8, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801AE584;
extern u16 D_801AE604;
extern u16 D_801AE606;
extern u16 D_801AE608;
extern s16 D_801B20D8;

void func_8017B1D8(void) {
    func_8012A418();
    D_801B20D8 = 0;
    D_801AE584 = 0;
    D_801AE604 = D_80126B5E;
    D_801AE606 = D_80126B62;
    D_801AE608 = D_80126B66;
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
    extern u8 D_8018BBC8[];
    extern s16 D_801AE5FC;
    extern s16 D_801AE5F4;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018BBC8[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018BBC8[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801AE5FC;
        s16 *p78C = &D_801AE5F4;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801B20D8 = 1;
        D_801AE584 = 0;
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
    extern SV4_8017B368 D_801AE5A4;
    extern SV4_8017B368 D_801AE5AC;
    extern s16 D_801AE5FC;
    extern s16 D_801AE5F4;
    extern u16 D_8018BBC8;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801AE5A4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801AE5AC;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018BBC8)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018BBC8)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801AE5FC) = loc0;
    (*(SV4_8017B368 *)&D_801AE5F4) = loc1;
    D_801B20D8 = 1;
    D_801AE584 = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801AE5A4;
    extern SV4_8017B368 D_801AE5AC;
    extern s16 D_801AE5FC;
    extern s16 D_801AE5F4;
    extern u16 D_8018BBC8;
    extern s16 D_801AE584;
    extern s16 D_801B20D8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801AE5A4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801AE5AC;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018BBC8)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018BBC8)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801AE5FC) = loc0;
    (*(SV4_8017B368 *)&D_801AE5F4) = loc1;
    D_801B20D8 = 1;
    D_801AE584 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801AE5FC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801AE5FC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801AE5FC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801AE5F4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801AE5F4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801AE5F4).c;
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
    extern u8 D_8018BBC8[];
    extern s16 D_801AE5FC;
    extern s16 D_801AE5FE;
    extern s16 D_801AE600;
    extern s16 D_801AE5F4;
    extern s16 D_801AE5F6;
    extern s16 D_801AE5F8;
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
        s32 a1addr = (s32)&D_8018BBC8[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018BBC8[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801AE5FC;
        s16 *p78C = &D_801AE5F4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801AE5FE;
            v798 = D_801AE600;
            v78C = *p78C;
            v78E = D_801AE5F6;
            v790 = D_801AE5F8;
            __asm__ __volatile__("");
            D_801B20D8 = 1;
            D_801AE584 = 0x1E;
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
extern s16 D_801AE584;
extern s16 D_801AE5FC;
extern s16 D_801AE5FE;
extern s16 D_801AE600;
extern s16 D_801AE5F4;
extern s16 D_801AE5F6;
extern s16 D_801AE5F8;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801AE584 = 0;
    D_801AE5FC = (s16) D_80114F30;
    D_801AE5FE = (s16) D_80114F34;
    D_801AE600 = (s16) D_80114F38;
    D_801AE5F4 = (s16) D_80114F24;
    D_801AE5F6 = (s16) D_80114F28;
    D_801AE5F8 = (s16) D_80114F2C;
}




extern s16 D_801AE614;
extern s16 D_801AE616;
extern s16 D_801AE618;
extern s16 D_801AE61C;
extern s16 D_801AE61E;
extern s16 D_801AE620;

void func_8017B824(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801151D4;
    D_801AE614 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801AE616 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801AE618 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801AE61C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801AE61E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801AE620 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801AE614;
extern s16 D_801AE616;
extern s16 D_801AE618;
extern s16 D_801AE61C;
extern s16 D_801AE61E;
extern s16 D_801AE620;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801AE614;
    D_80114F34 = D_801AE616;
    D_80114F38 = D_801AE618;
    D_80114F24 = D_801AE61C;
    D_80114F28 = D_801AE61E;
    D_80114F2C = D_801AE620;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801AE5FC), src[8..15] -> (*(S8_8017B8E8 *)&D_801AE5F4) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801AE5FC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801AE5F4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801AE604;
extern u16 D_801AE606;
extern u16 D_801AE608;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801AE584;
extern short D_801AE60C;
extern short D_801AE60E;
extern short D_801AE610;
extern s16 D_801AE5FC;
extern s16 D_801AE5FE;
extern s16 D_801AE600;
extern s16 D_801AE5F4;
extern s16 D_801AE5F6;
extern s16 D_801AE5F8;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801AE604);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801AE606);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801AE608);
    (*(s16 *)&D_801AE60C) = buf[0];
    (*(s16 *)&D_801AE60E) = buf[1];
    (*(s16 *)&D_801AE610) = buf[2];
    D_801AE5FC = D_80114F30 + buf[0];
    D_801AE584 = 0;
    D_801AE5FE = D_80114F34 + buf[1];
    D_801AE600 = D_80114F38 + buf[2];
    D_801AE5F4 = D_80114F24 + buf[0];
    D_801AE5F6 = D_80114F28 + buf[1];
    D_801AE5F8 = D_80114F2C + buf[2];
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

extern SV4 D_801AE5A4;
extern SV4 D_801AE5AC;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801AE5AC) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801AE5A4 = svec;

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
    D_801AE5AC = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801AE5AC)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801AE5A4) = svec;

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
    (*(SV4_8017BB34*)&D_801AE5AC) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801AE5CC[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801AE5CC;
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
extern s16 D_801AE584;
extern s16 D_801B20D8;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801AE584 = D_801AE584 + 1;
    if (D_801AE584 >= 0x1F) {
        D_801B20D8 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801AE584;
extern s16 D_801B20D8;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801AE584 = D_801AE584 + 1;
    if (0x18 < D_801AE584) {
        func_8012A4BC();
        D_801B20D8 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801AE584;
extern void (*D_801AE5C8)(void);
extern short D_801AE60C;
extern short D_801AE60E;
extern short D_801AE610;
extern s16 D_801B20D8;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801AE584 = D_801AE584 + 1;
    if (D_801AE584 >= 0x19) {
        if (D_801AE5C8 != 0) {
            (*D_801AE5C8)();
        } else {
            D_80114F30 = D_80114F30 + D_801AE60C;
            D_80114F34 = D_80114F34 + D_801AE60E;
            D_80114F38 = D_80114F38 + D_801AE610;
            D_80114F24 = D_80114F24 + D_801AE60C;
            D_80114F28 = D_80114F28 + D_801AE60E;
            D_80114F2C = D_80114F2C + D_801AE610;
            func_8012A4BC();
        }
        D_801B20D8 = 0;
    }
}



extern void (*D_8018BC68[])(void);

void func_8017BE60(void *a0) {
    D_8018BC68[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

extern void func_80174684(void *);
extern void func_8017BEE4(void *);

void func_8017BEBC(void) {
    func_80174684((void *)func_8017BEE4);
}



extern void (*D_8018BC74[])(void);

void func_8017BEE4(void *a0) {
    D_8018BC74[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_8017BF58(void *a0);
void func_8017BF20(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    func_8017BF58(a0);
}


extern void func_801827F4(void);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32 a0);

void func_8017BF58(void *a0) {
    if (((s32 (*)(void *))func_801827F4)(a0) == 0) {
        return;
    }
    func_80171A1C(a0);
    func_80174650(a0);
}


DEFINE_func_8017BF98()  /* dedup: shared engine-core @0x8017BF98 (src/shared) */

extern void func_80174684(void *);
extern void func_8017BFC8(void *);

s32 func_8017BFA0(void)
{
    func_80174684((void *)func_8017BFC8);
}



extern void (*D_8018BC80[])(void);

void func_8017BFC8(void *a0) {
    D_8018BC80[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_8017C03C(void *a0);
void func_8017C004(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    func_8017C03C(a0);
}


extern void func_801827C0(void);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32 a0);

void func_8017C03C(void *a0) {
    if (((s32 (*)(void *))func_801827C0)(a0) == 0) {
        return;
    }
    func_80171A1C(a0);
    func_80174650(a0);
}


DEFINE_func_8017C07C()  /* dedup: shared engine-core @0x8017C07C (src/shared) */

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017C084(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2B, a0, t0, t1, t2, a1, a2);
}



extern void (*D_8018BD40[])(void);

void func_8017C0C8(void *a0) {
    D_8018BD40[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017C104(u8 *a0) {
    s32 frame_pad[10];
    (void)&frame_pad;
    *(u16 *)(a0 + 0xE) += 0x10;
    (*(u16 *)(a0 + 2))++;
}


extern void func_8017C154();
void func_8017C12C(void) {
    func_8017C154();
}


DEFINE_func_8017C14C()  /* dedup: shared engine-core @0x8017C14C (src/shared) */

    extern SVECTOR_8017C290 D_8018BD54[4];
    void func_8017C154(void *a0)
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
                f = D_8018BD54[i];
                *(s16 *)((u8 *)a0 + 0x12) = i + j;
                func_8017C290((int)a0, buf20, &c, &d, &e, &f, (s16 *)((u8 *)a0 + 0x10));
            }
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

void func_8017C290(int a, s16 *b, SVECTOR_8017E72C *c, SVECTOR_8017E72C *d,
                   SVECTOR_8017E72C *e, SVECTOR_8017E72C *f, s16 *g)
{

    extern struct PW8017E72C D_8018BC8C[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern SVECTOR_8017E72C D_801AE6A8[4];
    extern struct PW8017E72C D_801AE6C8;
    extern struct PW8017E72C D_801AE6CC;
    extern u8 D_801AE6D0, D_801AE6D1, D_801AE6D2, D_801AE6D4, D_801AE6D5, D_801AE6D6;
    extern int D_801AE6D8;
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

    r0_00 = &D_801AE6A8[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801AE6D8 = 0x50000000;
        D_801AE6C8 = D_8018BC8C[*(s32 *)(a + 0x2C)];
        D_801AE6CC = D_8018BC8C[*(s32 *)(a + 0x2C)];
        D_801AE6D0 = 0;
        D_801AE6D1 = 0;
        D_801AE6D2 = 0;
        D_801AE6D4 = 0;
        D_801AE6D5 = 0;
        D_801AE6D6 = 0;
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


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017C624(void *a0, s16 a1, s32 a2) {
    func_80146A6C(0x2C, a0, 0, (s16)a1, 0, a2, 0);
}



extern void (*D_8018BD80[])(void);

void func_8017C664(void *a0) {
    D_8018BD80[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146F58(s32 a0, s32 a1);

/* MATCH (match_one, 93/93). ov_SC03_014_jr_8017AE2C, family reach x7 (zero-crack exemplar; see
 * asm/ov_SC03_0{14,15,24,118,119}/... and ov_SC06_000, all still INCLUDE_ASM as of this crack).
 *
 * sibling-search (cookbook §160g) hits, all from src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c
 * (the destination TU itself) plus one cross-overlay MATCHed twin:
 *   - func_8017CE10(void *a0, s32 a1, s32 a2)   -- defined verbatim in THIS TU (line 3679)
 *   - func_80147324(D_8018BCDC[idx][0])          -- exact idiom of func_8017C8FC's
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
extern void func_8017CE10(void *a0, s32 a1, s32 a2);
extern void func_80147324(s32 a0);
extern void func_80146C3C(void);

/* new-to-this-TU data symbols (own address only in this function; payload owned by
 * asm/ov_SC03_014/data/tail.data.s, a data-only splat unit -- extern is correct, not a definition,
 * per §160c's "same .s as the function" test). D_8018BD98 bytes: 0000 0000 ECFF 0000 = {0,0,-20,0}.
 * D_8018BD74: 12 opaque bytes (a GPU-primitive template), address-only use -> §160f array style. */

void func_8017C6A0(void *a0) {

    extern s16 D_8018BD98[4];
    extern u8 D_8018BD74[12];
    extern u16 D_8018BCDC[][2];
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

        ApplyMatrixSV(mat, D_8018BD98, vecOut);

        *(u16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + vecOut[0];
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) + vecOut[1];
        *(u16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) + vecOut[2];

        func_80015978(s1, (s32 *)vecOut);
        func_8012EF70((s32)vecOut, (s32)vecOut);
        func_80015954((s32)vecOut, s1);

        func_8001CB00((s32)s3, D_8018BD74, 0x280, 0x100);

        *(u8 *)(s3 + 0x27) = 0x80;

        *(s16 *)(s3 + 0x2C) = *(u16 *)(a0 + 0xE);
        *(s16 *)(s3 + 0x1A) = 0;
        *(s16 *)(s3 + 0x18) = 0;

        *(s32 *)(a0 + 0x10) = 0;
        func_8017CE10(a0, *(s32 *)(a0 + 0x2C), 0x8F);

        func_80147324(D_8018BCDC[*(s32 *)(a0 + 0x2C)][0]);

        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}




extern void func_80146E90(s32 *a0, s32 a1);
extern void func_8017D5F8(void *a0, s32 a1, s32 a2);

void func_8017C814(void *a0) {
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
        func_8017D5F8(a0, *(s32 *)((s32)a0 + 0x2C), 0);
        func_80146E90((s32 *)a0, 0);
        *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
}



extern void func_8017CE10(void *a0, s32 a1, s32 a2);
extern void func_8017D098(void *a0, s32 a1, s32 a2);
extern void func_80146C3C(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);

void func_8017C8FC(void *a0) {

    extern s32 D_8011D030;
    extern u16 D_8018BCF0[][2];
    s32 *s2;

    s2 = *(s32 **)((s32)a0 + 0x20);

    if (*(s32 *)((s32)a0 + 0x1C) < 0x100) {
        if ((*(s32 *)((s32)a0 + 0x1C) & 0xF) == 0) {
            func_8017CE10(a0, *(s32 *)((s32)a0 + 0x2C), 0xF);
            if ((*(s32 *)((s32)a0 + 0x1C) & 0xF) == 0) {
                s32 flags = *(s32 *)((s32)a0 + 0x1C) << 15;
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 1);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 2);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 3);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 4);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 5);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 6);
                func_8017D098(a0, *(s32 *)((s32)a0 + 0x2C), flags | 7);
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
        func_80147324(D_8018BCF0[idx][0]);

        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
}


extern void func_8017DD7C();

void func_8017CC44(void *a0)
{
    s32 flags = *(s32 *)((s32)a0 + 0x1C);
    s32 ptr = *(s32 *)((s32)a0 + 0x20);

    if (flags & 1) {
        *(s32 *)(ptr + 4) |= 0x80000000;
    } else {
        *(s32 *)(ptr + 4) &= 0x7FFFFFFF;
    }

    if (func_80146E98((s32)a0)) {
        func_8017DD7C();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8017CCC4(void *a0) {
    s32 *a1 = *(s32 **)((s32)a0 + 0x20);
    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        *(s32 *)(a1 + 1) |= 0x80000000;
    } else {
        *(s32 *)(a1 + 1) &= 0x7FFFFFFF;
    }
    *(s16 *)((s32)a0 + 0x24) = 3;
    *(s32 *)((s32)a0 + 0x1C) += 1;
}



extern void func_8017CE10(void *a0, s32 a1, s32 a2);
extern void func_80147324(s32 a0);
extern void func_80146C3C(void);

void func_8017CD10(void *a0) {

    extern u16 D_8018BD04[][2];
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
        func_8017CE10(a0, *(s32 *)((s32)a0 + 0x2C), 0x8F);
        func_80147324(D_8018BD04[*(s32 *)((s32)a0 + 0x2C)][0]);
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }

    *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017CE10(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2D, a0, t0, t1, t2, a1, a2);
}



extern void (*D_8018BDA0[])(void);

void func_8017CE54(void *a0) {
    D_8018BDA0[*(u16 *)((s32)a0 + 0x2)]();
}



/* callee-set / sibling search (cookbook §160g): all callees resolved from the DESTINATION TU
 * itself, src/ov_SC03_014/ov_SC03_014_jr_8017AE2C.c, whose immediately-preceding matched sibling
 * func_8017C6A0 (same TU, same family) uses the identical:
 *   - func_801465C0 loose void(void) file-scope decl, fought via a zero-arg cast-at-callsite
 *     (§161c) -- `((void *(*)(void))func_801465C0)()`.
 *   - func_80146C3C(void) called on the failure path with the object pointer cast in.
 *   - the returned object (named s3 there, s1 here) has s16 fields at +0x18/+0x1A/+0x2C, matching
 *     this function's `*(s16*)(s1+0x18)`, `+0x1A`, `+0x2C` stores exactly.
 * ((void (*)(void *, void *))func_8001CD04)(void*,void*) is defined in src/800.c (INCLUDE_ASM, shared engine) --
 * asm/nonmatchings/800/func_8001CD04.s shows it stores its 2nd arg into (a0+0x20), confirming a0
 * here is the newly-allocated object and a1 is an address it retains -- i.e. ((void (*)(void *, void *))func_8001CD04)(s1, s2)
 * installs s2 (&D_801AE628) onto the object.
 * The `lwl/lwr`+`swl/swr` pair at D_8018BCA0[idx] / D_801AE628 is the §160a align-1 struct-copy
 * idiom; D_8018BCA0 is already `extern M2C_UNK D_8018BCA0;` (address-only) in many ov_SC05_017
 * TUs, and the shared align-1 4-byte struct type `B4` (src/shared/engine_types.h:713) is already
 * used repo-wide for this exact shape. The SAME address (&D_801AE628) also takes a plain ALIGNED
 * `sw` of 0xFFFFFF on the other branch -- an explicit `(u32*)` cast forces that, while the direct
 * `B4` struct assignment on the table-lookup branch keeps the align-1 `swl/swr` -- §160a's "read
 * the move width off the target, not off the data's apparent type", both branches hitting the same
 * lvalue.
 * D_801AE628/844/845/846 are owned by asm/ov_SC03_014/data/tail19.data.s (a data-only splat unit,
 * §160c) -- not bundled with this function's .s, so plain `extern` declarations are correct, not a
 * definition. D_801AE628 is one `.word` (4 bytes); D_801AE62C and D_801AE62D are each one `.byte`;
 * D_801AE62E opens a much larger multi-byte block in that data file, but this function only stores
 * a zero to its FIRST byte, so a scalar `extern u8 D_801AE62E;` is sufficient here.
 *
 * TYPE: match_one's standalone `common.h` does NOT reach src/shared/engine_types.h (only the real
 * TU's `#include "../shared/engine_core.h"` does), so `B4` isn't visible here. Per the
 * ov_SC06_032_jr_8018FCE8.c precedent ("cc1 errors on the redefinition" of an identical-name
 * typedef), a fresh, function-scoped name is used instead -- collides with nothing; the integrator
 * may DROP this local typedef and reuse the TU's own `B4` when banking into the host TU.
 */

typedef struct { u8 d[4]; } Blk4_8017CE90_8017CE90;

extern void func_801465C0(void);
extern void func_8001CD04(s32, s32);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146C3C(void);


void func_8017CE90(void *a0)
{

    extern Blk4_8017CE90_8017CE90 D_8018BCA0[];
    extern Blk4_8017CE90_8017CE90 D_801AE628;
    extern u8 D_801AE62C;
    extern u8 D_801AE62D;
    extern u8 D_801AE62E;
    void *s1;
    Blk4_8017CE90_8017CE90 *s2;
    s32 pad[10];

    s1 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s1;

    if (s1 != NULL) {
        s2 = &D_801AE628;
        ((void (*)(void *, void *))func_8001CD04)(s1, s2);

        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;
        func_800233CC(s2, 0x50);

        *(s32 *)((u8 *)a0 + 0x10) = 0;
        if (*(s32 *)((u8 *)a0 + 0x30) & 0x80) {
            *(u32 *)s2 = 0xFFFFFF;
            *(s16 *)((u8 *)s1 + 0x1A) = 0x80;
            *(s16 *)((u8 *)s1 + 0x18) = 0x80;
            *(s32 *)((u8 *)a0 + 0x14) = 0x80;
        } else {
            *s2 = D_8018BCA0[*(s32 *)((u8 *)a0 + 0x2C)];
            *(s32 *)((u8 *)a0 + 0x14) = 0x20;
        }

        D_801AE62C = 0;
        D_801AE62D = 0;
        D_801AE62E = 0;

        *(s32 *)((u8 *)a0 + 0x30) = *(s32 *)((u8 *)a0 + 0x30) & 0x7F;
        *(s16 *)((u8 *)s1 + 0x2C) = *(u16 *)((u8 *)a0 + 0xE) + 0x10;
        *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


void func_8017CFBC(void *a0)
{
    typedef struct { u8 d[4]; } Blk4_8017CE90_8017CE90;
    extern Blk4_8017CE90_8017CE90 D_801AE628;
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146C3C(void);
    void *s2;
    void *s1;
    s32 v0;
    s32 v1;

    s2 = a0;
    s1 = *(void **)((u8 *)s2 + 0x20);
    D_801AE628.d[0] = func_80012F74(D_801AE628.d[0], 0, 10, 1);
    D_801AE628.d[1] = func_80012F74(D_801AE628.d[1], 0, 10, 1);
    D_801AE628.d[2] = func_80012F74(D_801AE628.d[2], 0, 10, 1);

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

void func_8017D098(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2E, a0, t0, t1, t2, a1, a2);
}



extern void (*D_8018BDB0[])(void);

void func_8017D0DC(void *a0) {
    D_8018BDB0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern void func_80146E90(s32 *a0, s32 a1);

void func_8017D118(s32 param_1)
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

void func_8017D194(void *a0) {
    if (func_80146E98((s32)a0)) {
        func_80146E90((s32 *)a0, 8);
        *(u16 *)((s32)a0 + 0x28) = 0x20;
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


    typedef struct { s16 vx; u16 vy; s16 vz, pad; } SVec_8017D1E0;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017D1E0;



extern s32 func_80146E98(s32 a0);
extern void func_80147324(s32 arg0);
extern void func_80146C3C(void);
extern void func_8017D318(int a0, SVECTOR_8017C290 *a1, SVECTOR_8017C290 *a2, s32 a3);

void func_8017D1E0(void *a0)
{

    extern u16 D_8018BD18[][2];
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
            func_80147324(D_8018BD18[*(s32 *)((s32)a0 + 0x2C)][0]);
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
    func_8017D318((int)a0, &vec1, &vec2, *(s16 *)((s32)a0 + 0x24));

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

void func_8017D318(int a0, SVECTOR_8017C290 *a1, SVECTOR_8017C290 *a2, s32 a3)
{

    extern struct PW8017C290 D_8018BCB4[];
    extern struct PW8017C290 D_8018BCC8[];
    extern SVECTOR_8017C290 D_801AE6A8[4];
    extern struct PW8017C290 D_801AE6C8;
    extern struct PW8017C290 D_801AE6CC;
    extern u8 D_801AE6D0, D_801EA8E9, D_801EA8EA, D_801AE6D4, D_801EA8ED, D_801EA8EE;
    extern u8 D_801AE6D0, D_801EA8E9, D_801EA8EA, D_801AE6D4, D_801EA8ED, D_801EA8EE;
    extern int D_801AE6D8;
    MATRIX_8017C290 m;
    SVECTOR_8017C290 *r0_00;
    SVECTOR_8017C290 *r0;
    SVECTOR_8017C290 *pSVar6;

    D_801AE6D8 = 0x50000000;
    D_801AE6C8 = D_8018BCB4[*(s32 *)(a0 + 0x2C)];
    D_801AE6CC = D_8018BCC8[*(s32 *)(a0 + 0x2C)];
    *(struct PW8017C290 *)&D_801AE6D0 = D_8018BCB4[*(s32 *)(a0 + 0x2C)];
    *(struct PW8017C290 *)&D_801AE6D4 = D_8018BCC8[*(s32 *)(a0 + 0x2C)];

    func_80013F3C((s32)&m);
    RotMatrixZ((s16)a3, &m);
    m.t[0] = *(s16 *)(a0 + 0x6);
    m.t[1] = *(s16 *)(a0 + 0xA);
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801AE6A8[0];

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

void func_8017D5F8(void *a0, s32 a1, s32 a2) {
    s16 t0 = *(s16 *)(a0 + 0x6);
    s16 t1 = *(s16 *)(a0 + 0xA);
    s16 t2 = *(s16 *)(a0 + 0xE);
    func_80146A6C(0x2F, a0, t0, t1, t2, a1, a2);
}



extern void (*D_8018BDBC[])(void);

void func_8017D63C(void *a0) {
    D_8018BDBC[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017D678 -- ov_SC03_014, TU ov_SC03_014_jr_8017AE2C.c
 *
 * §160g sibling-first: destination TU itself has the exact template two functions earlier,
 * func_8017CE90 (same TU, same family, allocate-then-attach-a-fixed-color-quad shape):
 *   - func_801465C0 loose `void(void)` file-scope decl (TU line 130/3614/3910), fought via a
 *     zero-arg cast-at-callsite `((void *(*)(void))func_801465C0)()` (§161c).
 *   - ((void (*)(void *, void *))func_8001CD04)(void*,void*) shared-engine helper (src/800.c, INCLUDE_ASM) that stores its
 *     2nd arg into (a0+0x20) -- confirms s1=result-object, s0=&D_801AE668 retained address.
 *   - `*(s1+4) |= 0x50000000` computed and stored in the delay slot of the FOLLOWING
 *     func_800233CC jal (same instruction-order idiom as func_8017CE90's identical line).
 *   - func_80146C3C(void) called on the alloc-failure path with the object pointer cast in
 *     (`((void (*)(void *))func_80146C3C)(a0)`), same as func_8017CE90's else-branch.
 * func_80146E90(s32*,s32) is already declared+called directly (no cast) at TU line 3801
 * (`func_80146E90((s32 *)a0, 0x20);`) -- reused verbatim here with a different 2nd arg.
 * The color-quad global block D_801AE668.. is fixed by this TU's OWN later sibling
 * func_8017D900 (a few lines below in the same file), whose header comment explicitly notes:
 * "In-TU sibling func_8017D678 shows D_801AE669/D_801AE66A are SEPARATE u8 globals (each gets
 * its own lui/%lo sb)" -- i.e. func_8017D900 was written FROM this function's own asm. That
 * comment also fixes D_801AE66C as a plain u8 (its Quad_801EA880 4-byte-struct framing only
 * matters for func_8017D900's block-copy; here each of D_801AE66C/885/886 gets an independent
 * byte store, so plain scalar externs are correct and sufficient).
 *
 * Source statement order mirrors instruction order 1:1 (straight-line alloc/init, no branches
 * inside the success path); the `a0 = s2` register move for the func_80146E90 call argument is
 * expected to be scheduler-hoisted early by gcc/sched2 exactly as seen in every other sibling in
 * this TU -- no special C construct needed for that.
 */

extern void func_801465C0(void);
extern void func_8001CD04(s32, s32);
extern void func_800233CC(void *a0, u16 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C3C(void);


void func_8017D678(void *a0)
{

    extern u8 D_801AE668;
    extern u8 D_801AE669;
    extern u8 D_801AE66A;
    extern u8 D_801AE66C;
    extern u8 D_801AE66D;
    extern u8 D_801AE66E;
    void *s1;
    void *s0;
    s32 pad[10];

    s1 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s1;

    if (s1 != NULL) {
        s0 = &D_801AE668;
        ((void (*)(void *, void *))func_8001CD04)(s1, s0);

        *(s32 *)((u8 *)s1 + 4) |= 0x50000000;
        func_800233CC(s0, 0x100);

        *(s16 *)((u8 *)s1 + 0x1A) = 0;
        *(s16 *)((u8 *)s1 + 0x18) = 0;
        *(s32 *)((u8 *)a0 + 0x10) = 0x80;
        *(s16 *)((u8 *)s1 + 0x2C) = 0x10;

        *(u8 *)s0 = 0xFF;
        D_801AE669 = 0xFF;
        D_801AE66A = 0xFF;
        D_801AE66C = 0;
        D_801AE66D = 0;
        D_801AE66E = 0;

        func_80146E90((s32 *)a0, 0xC0);
        *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);
extern u16 D_8018BD2C[];
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);

void func_8017D75C(s32 param) {
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
        v0 = D_8018BD2C[v0 << 1];
        func_80147324(v0);

        v0 = *(u16 *)(param + 0x2);
        *(s16 *)(param + 0x2) = v0 + 1;
    }
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);

void func_8017D804(s32 param) {
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


extern u8 D_801AE66C;
extern u8 D_801AE66D;
extern u8 D_801AE66E;

void func_8017D890(void *arg0, void *a1) {
    s16 var;

    a1 = *(void **)((s32)arg0 + 0x20);
    var = *(u16 *)((s32)a1 + 0x1A) + 0x200;
    *(u16 *)((s32)a1 + 0x1A) = var;
    *(u16 *)((s32)a1 + 0x18) = var;
    if (var >= 0x1001) {
        D_801AE66C = 0xFF;
        D_801AE66D = 0xFF;
        D_801AE66E = 0xFF;
        *(u16 *)((s32)a1 + 0x1A) = 0x1000;
        *(u16 *)((s32)a1 + 0x18) = 0x1000;
        *(u16 *)((s32)arg0 + 2) = *(u16 *)((s32)arg0 + 2) + 1;
    }
}



/* func_8017D900 — fade the 4-byte colour quad at D_801AE668 one step toward 0
 * (func_80012F74 = "step a value toward a target"), splat the byte over the
 * three sibling bytes, mirror the whole quad into the three following quads,
 * then tear the entity down once the byte reaches 0.
 *
 * §71 sibling-first: DEFINE_func_801685EC() (engine_core.h L8520) is the same
 * `if (<call result> == 0) ((void (*)(s32))func_80146C3C)(arg0);` teardown tail.
 * In-TU sibling func_8017D678 shows D_801AE669/D_801AE66A are SEPARATE u8
 * globals (each gets its own lui/%lo sb) while D_801AE668's address lives in a
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
 *  - `u8 *p = &D_801AE668;` (§20) — one address register ($s0, callee-saved
 *    across the jal) serves the lbu, the sb and all three block-move sources.
 *  - chained assignment `D_801AE669 = D_801AE66A = *p = f(...)` gives the
 *    target's store order 880, 882, 881 (right-to-left after the *p store).
 *  - the 4×u8 struct (align 1) is what makes the assignment expand to inline
 *    lwl/lwr + swl/swr instead of a `jal memcpy` (cf. §38).
 */

 /* align 1 => movstrsi expands to lwl/lwr + swl/swr */


extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

void func_8017D900(s32 arg0) {

    extern u8 D_801AE668;
    extern u8 D_801AE669;
    extern u8 D_801AE66A;
    extern u8 D_801AE66C;
    extern u8 D_801AE670;
    extern u8 D_801AE674;
    u8 *p = &D_801AE668;

    D_801AE669 = D_801AE66A = *p = func_80012F74(*p, 0, 10, 1);
    __asm__("");
    *(Quad_801EA880_8017D900 *)&D_801AE66C = *(Quad_801EA880_8017D900 *)p;
    *(Quad_801EA880_8017D900 *)&D_801AE670 = *(Quad_801EA880_8017D900 *)p;
    *(Quad_801EA880_8017D900 *)&D_801AE674 = *(Quad_801EA880_8017D900 *)p;
    __asm__("");
    if (*p == 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


extern s32 D_8011D030;
extern u16 D_8018BCF0[][2];
extern void func_80146C3C();
extern void func_80147364(u16, s32);

void func_8017D9C8(s32 a0) {

    extern s32 D_8011D030;
    extern u16 D_8018BCF0[][2];
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

    func_80147364(4, D_8018BCF0[a0][0]);
}


extern s16 D_80126B30;
extern s16 D_80126B3A;
extern s32 D_8012750C;
extern s16 D_8011F9C8;
extern void func_80174684(void *);
extern void func_8017DB00(void *);

struct S8_8017DA98 { s16 m[4]; };

void func_8017DA98(s16 a0, void *a1, s32 a2) {
    *(struct S8_8017DA98 *)&D_80126B30 = *(struct S8_8017DA98 *)a1;
    D_80126B3A = a0;
    D_8012750C = a2;
    func_80174684((void *)func_8017DB00);
    (*(s32 *)&D_8011F9C8) = 0;
}



extern void (*D_8018BF40[])(void);

void func_8017DB00(void *a0) {
    D_8018BF40[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_8017DB74(u8*);
void func_8017DB3C(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    ((void (*)(void *))func_8017DB74)(a0);
}


extern s32 func_80171CC4(void *a0, void *a1);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B36;
void func_8017DB74(u8 *a0) {
    s16 *p = &D_80126B36;
    if (*p != 0) {
        if (func_80171CC4(a0, p - 3) == 0) {
            return;
        }
    }
    func_80171A1C(a0);
}


DEFINE_func_8017DBC4()  /* dedup: shared engine-core @0x8017DBC4 (src/shared) */



extern void func_80171A1C(u8*);

void func_8017DC28(void *a0) {
    *(s32 *)((s32)a0 + 0x200) = 1;
    ((s32 (*)(void *))func_80171A1C)(a0);
}


extern s32 D_8018BDD8;
extern u8 D_800B9A11;
extern void func_8012943C(void);
extern void func_8013C938(void);
extern void func_8014706C(void *arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);

    void func_8017DC4C(s32 *a0) {
        s32 v0 = a0[0x80];
        s32 v1;
        v1 = v0 - 1;
        a0[0x80] = v1;
        if (v1 != -1) {
            return;
        }
        func_8014706C(a0);
        func_80154274(a0, (s32)&D_8018BDD8);
        func_8013C938();
        D_800B9A11 = 0xC0;
        func_8012943C();
        func_80171A1C((u8 *)a0);
    }


extern s16 D_80126B3A;
extern s16 D_80126B3C;
extern void func_8017C624(void *a0, s16 a1, s32 a2);
extern void func_80171A1C(u8 *a0);

void func_8017DCC0(u8 *a0)
{
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
        func_8017C624(a0, -0x60, v);
        func_80171A1C(a0);
    }
}


DEFINE_func_8017DD74()  /* dedup: shared engine-core @0x8017DD74 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DD7C);

DEFINE_func_8017DDBC()  /* dedup: shared engine-core @0x8017DDBC (src/shared) */


extern u8 D_8018BE7C;
extern u8 D_800B9A11;
extern void func_80129428(void);
extern void func_8013C964(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);

void func_8017DE24(s32 *a0) {
    s32 v0 = a0[0x80];
    s32 v1;
    v1 = v0 - 1;
    a0[0x80] = v1;
    if (v1 != -1) {
        return;
    }
    func_80154274(a0, (s32)&D_8018BE7C);
    func_8013C964();
    D_800B9A11 = 0;
    func_80129428();
    func_80171A1C((u8 *)a0);
}


extern void func_80147324(s32 a0);
extern void func_80147060(u8 *a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern s32 func_80174650(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B3A;
extern s16 D_8011F9C8;

void func_8017DE8C(u8 *a0) {
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


DEFINE_func_8017DF7C()  /* dedup: shared engine-core @0x8017DF7C (src/shared) */


extern void (*D_8018BF84[])(void);

void func_8017DF84(void *a0) {
    D_8018BF84[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017DFC0(s32 param_1) {

    extern u8 D_8018BF6C;
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

    node = func_800D222C(param_1, &D_8018BF6C, 0xFD);
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


extern void func_80146C3C(void);
void func_8017E184(u8 *p) {
    u8 *q;
    s32 t;
    s32 b;
    q = *(u8 **)(p + 0x20);
    *(u16 *)(p + 0x16) = *(u16 *)(p + 0x16) + *(u16 *)(p + 0x14);
    if (*(s32 *)(p + 0x1C) < 8) {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x200;
    } else {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x51;
    }
    b = *(u8 *)(q + 0x26) - 2;
    *(s16 *)(q + 0x1A) = *(u16 *)(p + 0x16);
    *(s8 *)(q + 0x26) = b;
    *(s8 *)(q + 0x25) = b;
    *(s8 *)(q + 0x24) = b;
    t = *(s32 *)(p + 0x1C);
    *(s32 *)(p + 0x1C) = t + 1;
    if (t >= 0x1E) {
        ((void (*)(u8 *))func_80146C3C)(p);
    }
}



extern void (*D_8018BF8C[])(void);

void func_8017E218(void *a0) {
    D_8018BF8C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018BF78;

void func_8017E254(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018BF78, 0x18);
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


extern void func_80146C3C(void);
void func_8017E2F8(int a0) {
    int v0 = *(int *)(a0 + 0x1C);
    register unsigned char *p __asm__("$5") = *(unsigned char **)(a0 + 0x20);
    *(int *)(a0 + 0x1C) = v0 + 1;
    if (v0 >= 0x1F) {
        func_80146C3C();
    } else {
        unsigned short hv = *(unsigned short *)(p + 0x1A) + 0x1E0;
        signed char bv = *(unsigned char *)(p + 0x26) - 3;
        *(unsigned short *)(p + 0x1A) = hv;
        *(unsigned short *)(p + 0x18) = hv;
        *(signed char *)(p + 0x26) = bv;
        *(signed char *)(p + 0x25) = bv;
        *(signed char *)(p + 0x24) = bv;
    }
}


/* func_8017E35C — ov_SC06_000 / split TU ov_SC06_000_jr_8017AE2C, 719 ins, 0xB3C bytes.
 *
 * ============================ STRUCTURAL MAP ==============================
 * void func_8017E35C(s32 actor)
 *
 * WHAT IT DOES: the overlay's "draw one model" routine.  For every PART of a
 * model it (a) projects the part's 8-corner AABB through the GTE, (b) rejects
 * the part on OTZ and on a screen-space bounding box, then (c) for every
 * PRIM in the part projects the 3/4 vertices, rejects on the GTE error flag,
 * on NCLIP backface (opz<=0) and again on a screen box, and finally emits a
 * POLY_FT3 (code 6/7) or POLY_FT4 (code 2/3) packet and links it into the OT
 * bucket ((opz>>2)<<2) + ot.  The packet's CLUT word gets a depth-driven bias
 * ((clamp(opz-400,0)>>8) << 22).  pkt walks D_800A5E60 by 0x28 per packet
 * (BOTH paths, even the 0x20-byte FT3) and is written back at the end.
 *
 * PROLOGUE  frame 0x1C0; saves ra/fp/s7..s0 @0x1BC..0x198.  s1 = actor.
 *           if (*(s32*)actor != 0) -> .L8017EE64 (plain return; D_800A5E60
 *           is NOT written on this path).
 *
 * SETUP     lim = func_800491EC() + *(s32*)(actor+0x64)     -> spill 0x100
 *           func_800547D8(actor+0x10, &mtx); func_80052E38(&mtx)  mtx @0xC0
 *           pkt($t6)   = D_800A5E60
 *           part($s2)  = *(Part35C**)(actor+0xC)      stride 0x14, giv $s1=part+0xC
 *           obj        = *(s32*)(actor+8)
 *           nparts($fp)= *(s32*)(obj+8)   ; vtx($t9) = *(u8**)(obj+0x10)
 *           ot($s7)    = &D_800A6610[D_800B9A02 << 14]
 *           $s4=&vbuf (spilled to 0x108), $s5=&g.sz0, $s6=&g.sz1, $t8=0xFFFFFF
 *           if (nparts <= 0) -> .L8017EE5C (store-back only)
 *
 * OUTER  .L8017E418  for (j=0; j<nparts; j++, part++)
 *   build box[8] @sp+0x20 from (xx.lo|xx.hi, yy.lo|yy.hi, zz.lo|zz.hi)
 *     order: 0=(xl,yl,zl) 1=(xh,yl,zl) 2=(xl,yl,zh) 3=(xh,yl,zh)
 *            4=(xl,yh,zl) 5=(xh,yh,zl) 6=(xl,yh,zh) 7=(xh,yh,zh)
 *   ldv3c(box)/rtpt/stsxy3(sxy0..2) ldv0(box3)/rtps/stsxy(sxy3)
 *   ldv3c(box+4)/rtpt/stsxy3(sxy4..6) ldv0(box7)/rtps/stsxy(sxy7)
 *   stszotz(&g.otz);   if (lim < g.otz) -> .L8017EE48 (next part)
 *   min/max of sxy[0..3].vx & sxy[4..7].vx -> mnc,mxc, cull |x|>0xA0
 *   min/max of the .vy halves            -> mnc,mxc, cull  y outside -0x6E..0x6E
 *   nprim = part->nprim (spill 0x190); prim = part->prim; if (!nprim) next part
 *
 * INNER  .L8017E810  for (i=0; i<nprim; i++, prim++)     i unsigned (sltu)
 *   w=prim->w1; va=vtx+(w&0xFFFF); vb=vtx+(w>>16);
 *   w=prim->w2; vc=vtx+(w&0xFFFF); w>>=16;
 *   vbuf[0..2] = *(V8*)va/vb/vc      <- UNALIGNED 8-byte block moves
 *                                       (lwl/lwr + swl/swr pairs @0xA0/A8/B0)
 *   ldv3c(vbuf); rtpt; stflg(&g.flag); if (g.flag & 0x7F85E000) -> .L8017EE30
 *   nclip(); code = w&7; vd = vtx + (w & 0xFFF8); stopz(&g.opz)
 *   if (g.opz <= 0) -> .L8017EE30
 *   switch(code)  (gcc decision tree: <2 def, <4 -> QUAD, >=8 def, <6 def)
 *
 *   case 6,7  .L8017E940  TRI / POLY_FT3, tag 0x07000000
 *     stsxy3_g3(pkt)  [swc2 8/16/24]  ; stsz3(&g.sz0,&g.sz1,&g.sz2)
 *     x-cull on pkt->x0/x1/x2, y-cull on pkt->y0/y1/y2
 *     za = max(sz0,sz1,sz2); g.opz = za; if (code==7) g.opz = za+0x50
 *   case 2,3  .L8017EB20  QUAD / POLY_FT4, tag 0x09000000
 *     stsxy3c(tmpxy); vdbuf = *(V8*)vd; ldv0(&vdbuf); rtps
 *     x/y min-max on tmpxy[0..2]; stflg; if (flag&mask) -> .L8017EE30
 *     stsz4(); stsxy(&pkt->x3); fold x3/y3 into the min/max; cull
 *     za = max(sz0,sz1,max(sz2,sz3)); g.opz=za; if (code==3) g.opz=za+0x50
 *     pkt->x0..x2 = tmpxy[0..2]  (32-bit lw/sw)
 *
 *   TAIL .L8017EE04 (shared by both cases, TRI reaches it with `j`):
 *     otp = (u32*)(((g.opz>>2)<<2) + ot)
 *     *(u32*)pkt = (*otp & 0xFFFFFF) | tag;  *otp = (*otp & 0xFF000000)|(pkt&0xFFFFFF)
 *     pkt += 0x28   (giv $t3 = pkt+0x24 carries every ordinary ld/st)
 *
 * .L8017EE5C  D_800A5E60 = pkt      .L8017EE64  epilogue.
 *
 * FRAME MAP (from the sp-relative refs in the target):
 *   0x00 outgoing args        0x10 DVec35C tmpxy[4]     0x20 SVec35C box[8]
 *   0x60 SVec35C sxy[8]      0xA0 V8 vbuf[3]            0xB8 V8 vdbuf
 *   0xC0 Mtx35C mtx          0xE0 g{otz,flag,opz,sz0..sz3}
 *   0x100 spill lim   0x108 spill &vbuf   0x190 spill nprim   0x198.. saved regs
 * ==========================================================================
 *
 * Idiom sources: the matched relative func_8017F510 in
 * src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c (same family, plus a light
 * volume).  Its GTE macro bank, its box-build/min-max/cull shapes and its
 * OT-link tail are reused verbatim here.
 *
 * ===== THE FIVE DECISIVE LEVERS (522 -> 0 mismatches) =====
 *  1. LOAD-GROUPING drives sched.  `wx=..; wy=..; wz=..;` as three ADJACENT
 *     loads, THEN the five copy/shift statements, THEN the box stores in
 *     strict address order.  Interleaving the loads with their consumers
 *     made sched1 sink the zz load and reorder 24 stores (-25 diff).
 *  2. SPLIT THE BOX BUILD ACROSS THE GTE LATENCY.  box[4..7] is written
 *     BETWEEN `gte_rtps()` and `gte_stsxy(&sxy[3])`, not up-front.  The
 *     "memory" clobbers on the swc2 macros make this order UNREACHABLE by
 *     the scheduler -- it is purely a source fact.  It also lengthens wz/zh
 *     past the &sxy address quantities, which is what pushes local-alloc
 *     onto $a1/$a2 and the whole temp file into the target's assignment.
 *  3. READ A SPILLED STACK VALUE ONCE.  `oz = g.opz;` feeding BOTH the
 *     `oz-400` clamp and `(oz>>2)<<2`.  Two separate `g.opz` reads cost a
 *     second `lw` and left three load-delay `nop`s the target fills with
 *     the OT-address arithmetic.
 *  4. HOIST THE DEPTH BIAS.  `d = (d >> 8) << 22;` as its own statement
 *     before the `tp` loads (not inline in the uvc0 expression).  That puts
 *     `sra` at the clamp's join point so maspsx can duplicate it into the
 *     bgez delay slot (+1 ins, and it is the target's +1).
 *  5. REF-COUNT DIAL (cookbook RC-15) + GIV-BASE ORDER.
 *     `__asm__ __volatile__ ("" :: "r" (nparts));` at the head of the
 *     innermost outer-loop cull block: byte-free, but it lifts nparts'
 *     reg_n_refs by loop_depth so nparts beats &vbuf for the last register
 *     -- &vbuf spills to 0x108, nprim spills to 0x190, the frame grows
 *     0x1B8 -> 0x1C0 and the whole temp allocation snaps to the target
 *     (653 -> 5 mismatches in ONE edit).
 *     Then `prim = part->prim;` BEFORE `nprim = part->nprim;`: loop.c's
 *     combine_givs makes the LAST-CREATED giv the base, so the read order
 *     of the two trailing Part fields picks `part+0xC` vs `part+0x10`
 *     (5 -> 0).
 *
 * TU-safety: the six aggregate typedefs are given function-unique names
 * (engine_types.h already defines byte-identical DVECTOR2/SVECTOR2/MATRIX2/
 * PolyFT3/PolyFT4/Part), the scalar typedefs are omitted, and D_800B9A02 is
 * declared `s16` with a `(u16)` cast at the use site to agree with the two
 * existing `extern short/s16` decls at ov_SC06_000_jr_8017AE2C.c:2466-2468
 * (the cast still folds into `lhu`).  rtu_match.py: MATCH.
 */


extern s32  func_800491EC(void);
extern void func_800547D8(s32, Mtx35C *);
extern void func_80052E38(Mtx35C *);
extern s16  D_800B9A02;

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

#define gte_stsxy3_g3(r0) __asm__ volatile (     \
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

void func_8017E35C(s32 arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8   D_800A6610[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8  *D_800A5E60;
    typedef struct { u32 w0, w1, w2; } Prim;
    typedef struct { u8 b[8]; } V8;

    DVec35C tmpxy[4];
    SVec35C box[8];
    SVec35C sxy[8];
    V8 vbuf[3];
    V8 vdbuf;
    Mtx35C mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *pkt;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part35C *part;
    u32 ot;
    u32 w;
    s32 code;
    u8 *va, *vb, *vc, *vd;
    u32 wx, wy, wz, zh;
    s16 my, mny, mx, mn;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s32 za, zb, d, oz;
    u32 *tp;
    u32 uvw;

    if (*(s32 *)arg0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = *(Part35C **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(u16)D_800B9A02 << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        wy = part->yy;
        wz = part->zz;
        mn = wx;
        mx = wx >> 16;
        mny = wy;
        my = wy >> 16;
        zh = wz >> 16;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = zh;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = zh;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();

        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = zh;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = zh;

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
                    __asm__ __volatile__ ("" :: "r" (nparts));
                    prim = (Prim *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        vbuf[0] = *(V8 *)va;
                        vbuf[1] = *(V8 *)vb;
                        vbuf[2] = *(V8 *)vc;
                        gte_ldv3c(vbuf);
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
                                    /* ---------------- TRI (FT3) ---------------- */
                                    gte_stsxy3_g3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((Ft3_35C *)pkt)->x0 > ((Ft3_35C *)pkt)->x1) {
                                        mx = ((Ft3_35C *)pkt)->x0; mn = ((Ft3_35C *)pkt)->x1;
                                    } else {
                                        mn = ((Ft3_35C *)pkt)->x0; mx = ((Ft3_35C *)pkt)->x1;
                                    }
                                    if (((Ft3_35C *)pkt)->x2 > mx) mx = ((Ft3_35C *)pkt)->x2;
                                    else if (((Ft3_35C *)pkt)->x2 < mn) mn = ((Ft3_35C *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((Ft3_35C *)pkt)->y0 > ((Ft3_35C *)pkt)->y1) {
                                            my = ((Ft3_35C *)pkt)->y0; mny = ((Ft3_35C *)pkt)->y1;
                                        } else {
                                            mny = ((Ft3_35C *)pkt)->y0; my = ((Ft3_35C *)pkt)->y1;
                                        }
                                        if (((Ft3_35C *)pkt)->y2 > my) my = ((Ft3_35C *)pkt)->y2;
                                        else if (((Ft3_35C *)pkt)->y2 < mny) mny = ((Ft3_35C *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else               { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x50;
                                            oz = g.opz;
                                            d = oz - 400;
                                            if (d < 0) d = 0;
                                            d = (d >> 8) << 22;
                                            tp = (u32 *)prim->w0;
                                            ((Ft3_35C *)pkt)->rgbc = tp[0];
                                            ((Ft3_35C *)pkt)->uvc0 = tp[1] + d;
                                            ((Ft3_35C *)pkt)->uvp1 = tp[2];
                                            ((Ft3_35C *)pkt)->uv2  = tp[3];
                                            otp = (u32 *)(((oz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    vdbuf = *(V8 *)vd;
                                    gte_ldv0(&vdbuf);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                    else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((Ft4_35C *)pkt)->x3);
                                        if (((Ft4_35C *)pkt)->x3 < mn) mn = ((Ft4_35C *)pkt)->x3;
                                        else if (mx < ((Ft4_35C *)pkt)->x3) mx = ((Ft4_35C *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((Ft4_35C *)pkt)->y3 < mny) mny = ((Ft4_35C *)pkt)->y3;
                                            else if (my < ((Ft4_35C *)pkt)->y3) my = ((Ft4_35C *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x50;
                                                oz = g.opz;
                                                d = oz - 400;
                                                if (d < 0) d = 0;
                                                d = (d >> 8) << 22;
                                                *(u32 *)&((Ft4_35C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((Ft4_35C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((Ft4_35C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((Ft4_35C *)pkt)->rgbc = tp[0];
                                                ((Ft4_35C *)pkt)->uvc0 = tp[1] + d;
                                                ((Ft4_35C *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((Ft4_35C *)pkt)->uv2 = uvw;
                                                ((Ft4_35C *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((oz >> 2) << 2) + ot);
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


s32 func_8017EE98(s32 arg) {
    extern s32 D_801AE6E0;

    D_801AE6E0 -= 4;
    if (D_801AE6E0 < 0) {
        D_801AE6E0 = 0;
        return 1;
    }
    return 0;
}


s32 func_8017EECC(void) {
    extern s32 D_801AE6E0;

    D_801AE6E0 = D_801AE6E0 + 4;
    if (D_801AE6E0 >= 0x80) {
        D_801AE6E0 = 0x80;
        return 1;
    }
    return 0;
}


s32 func_8017EF08(s32 a0) {
    s32 buf[8];
    s32 ret;

    extern void func_80052D90(s32 a0, s32 a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern s32 D_801AE6E0;

    func_80052D90(0, a0);
    func_80054514(a0, (s32)buf);
    ret = 0x80;
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    *(s16 *)(a0 + 0x50) = 0;
    *(s16 *)(a0 + 0x52) = 0;
    *(s16 *)(a0 + 0x54) = 0;
    D_801AE6E0 = ret;
    return ret;
}


/* func_8017EF68 — ov_SC06_000 / split TU ov_SC06_000_jr_8017AE2C, 969 ins, 0xF24 bytes.
 * THE LARGEST UNMATCHED FUNCTION IN THE GAME (singleton).
 *
 * ======================= STRUCTURAL MAP (asm-derived) =====================
 * void func_8017EF68(s32 arg0, s32 arg1, s32 arg2)
 *
 * It is the "constant-colour + subtractive overlay quad + distance-CLUT"
 * TEXTURED-ONLY member of the mesh-renderer family whose MATCHED relatives are
 *   src/ov_SC06_029/ov_SC06_029_jr_8017C954.c :: func_8017C954   (1194 ins, MATCH)
 *   src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c :: func_8017F510   (lit variant)
 * Skeleton, GTE macro set, OT-insert idiom and screen-bbox reject are identical.
 *
 * PROLOGUE  frame 0x228.  saves s0-s7/fp/ra @ 0x200..0x224.
 *   if (*(s32*)arg0 != 0) return;                      -> bnez -> epilogue
 *   lim  = func_800491EC() + *(s32*)(arg0+0x64);       -> spill 0x100
 *   func_800547D8(arg2, &mtx); func_80052E38(&mtx);
 *   pkt  = D_800A5E60;                     ($t5, kept live over the whole loop)
 *   ot   = &D_800A6610[(u16)D_800B9A02 << 14];         ($t9)
 *   d = D_801AE6E0; colA = d|d<<8|d<<16;               -> spill 0x108
 *   e = d*2; if (e > 0xFF) e = 0xFF; colB = ...;       -> spill 0x110 (sltiu!)
 *   part = (Part*)(arg1+0x14)   -> spill 0x120 ; giv part+0xC -> $s1
 *   nparts = *(s32*)(arg1+8)    -> spill 0x118 ; vtx = *(u8**)(arg1+0x10) -> $t8
 *   if (nparts <= 0) goto store-back.
 *
 * OUTER LOOP (j, signed, spilled @0x1F0) over Part[] stride 0x14:
 *   builds the 8-corner AABB in box[8] from part->xx/yy/zz (each u32 = two s16),
 *   rtpt/stsxy3 + rtps/stsxy x2 -> sxy[8], gte_stszotz(&g.otz);
 *   if (lim >= g.otz) { screen-x bbox reject -0xA0/0xA1, screen-y -0x6E/0x6F;
 *     INNER LOOP (i, UNSIGNED, $s0) over Prim[] stride 0xC, nprim in $fp:
 *       vv[0..2] = *(SVECTOR2*)(vtx + idx)   (three lwl/lwr block copies)
 *       gte_ldv3c(&vv[0]); rtpt; stflg; if (!(flag & 0x7F85E000)) {
 *         nclip; code = w>>16 & 7; vd = vtx + (w>>16 & 0xFFF8); stopz;
 *         if (g.opz > 0) switch (code) {          [gcc if-TREE, no jtbl]
 *            case 3  -> arm E : POLY_FT4 (len 9, colA|0x2E000000) THEN a
 *                               7-word (0x1C, len 6) subtractive overlay:
 *                               +4 = 0xE1000040, +8 = colB|0x2A000000,
 *                               +0xC..+0x18 = the four screen xy words.
 *            case 2  -> arm D : POLY_FT4 (len 9, rgbc = tp[0]),  pkt += 0x28
 *            case 6/7-> arm B : POLY_FT3 (len 7, rgbc = tp[0]),  pkt += 0x28 (!)
 *            0,1,4,5 -> nothing (this variant is textured-only)
 *         }
 *       }
 *   }
 *   D_800A5E60 = pkt;
 *
 * DISTANCE-CLUT (this variant's own delta vs every matched relative):
 *   dz = za - 0x190; if (dz < 0) dz = 0;   pkt->uvc0 = tp[1] + ((dz>>8)<<22);
 *   i.e. the CLUT y is bumped one row per 256 units of depth past 400.
 *
 * FRAME  0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 vv[4] |
 *        0xC0 mtx | 0xE0 g{otz,flag,opz,sz0..sz3} | 0x100..0x1F8 = 32 EIGHT-byte
 *        spill slots | 0x200..0x227 saved regs.   Used spills:
 *        0x100 lim, 0x108 colA, 0x110 colB, 0x118 nparts, 0x120 part,
 *        0x128 &vv[0] (loop-invariant address), 0x1F0 j, 0x1F8 &g.sz2.
 *
 * ================== STATUS: MATCH 969/969 (match_one + rtu_match) =========
 * S43 (2026-08-05, Fable session): closed by L6+L7 below. The residual analysis
 * that follows is kept as the historical record of the 2-mismatch state; its
 * §49 LUID hypothesis was INCOMPLETE — see the corrected root cause at L6.
 * ---------------------------------------------------------------------------
 * `SCHEDULE-REORDER/2`.  match_one AND rtu_match (real TU) both report the SAME
 * two instructions, transposed, registers already identical:
 *     mine 75/76 :  lw $v0,0($s3)  /  srl $a2,$a1,16
 *     tgt  75/76 :  srl $a2,$a1,16 /  lw $v0,0($s3)
 * i.e. `wq = wz >> 16` vs the `part->xx` load, in the outer loop's first block.
 *
 * ------- THE FIVE LEVERS THAT TOOK 827 mismatched -> 2 (each byte-measured) --
 * L1  BOX SPLIT AROUND THE FIRST RTPS.  box[0..3] are filled, the first
 *     ldv3c/rtpt/stsxy3 + ldv0/rtps issued, and only THEN box[4..7] filled,
 *     with gte_stsxy(&sxy[3]) *after* them (the classic "do work while the GTE
 *     runs" hand-optimisation).  A gte_stsxy `"memory"` clobber is a hard sched
 *     barrier, so the target's 12 `sh 0x40..0x5C` sitting between `rtps` and
 *     `swc2 $14,0($v0)` can only come from source order.       827 -> 845/972.
 * L2  `s32 code` (NOT u32) — the switch dispatch is `slti`, not `sltiu`.
 * L3  ZERO-BYTE $a2 DIAL: `__asm__ __volatile__ ("" ::: "$6");` inside arm E
 *     (case 3), immediately before its y min/max.  This is §46-L1 / cookbook
 *     §47 applied one slot the other way: without it the {mny,my,mx,mn} global
 *     allocno quad lands on (a2,a3,t0,t1); the target's is (a3,t0,t1,t2).  The
 *     dial makes $a2 conflict so the whole quad slides one slot along
 *     reg_alloc_order.  It ALSO flips the whole spill set to the target's
 *     (part/j/&g.sz2 spilled, nprim -> $fp) and the frame 0x218 -> 0x228.
 *     100 -> 26 structural deltas, 95.7% -> 97.4% kept.  Positions tried: before
 *     arm E's x min/max, before its y min/max, and right after its gte_rtps()
 *     are ALL equivalent (2 mismatched); AFTER the y min/max costs +2 (it then
 *     blocks reorg from stealing `addiu $v0,$sp,0xE4` into the branch delay).
 * L4  IN-PLACE SHIFT CHAINS (cookbook §46-L4, the local-alloc combine_regs tie).
 *     `otp = (u32*)(((za>>2)<<2)+ot)` gives `sra $a0,$a1,2 / sll / addu` as a
 *     3-insn block plus nops; the target ties the chain into za's own register.
 *     Write it as SELF-ASSIGNMENT instead:  `za >>= 2; za <<= 2; otp = za+ot;`
 *     and likewise `dz >>= 8; dz <<= 22;`.  This is what removes the LAST of the
 *     length drift: 978 -> 969 ins, 26 -> 6 structural deltas.
 * L5  `u32 *tp;` and `u32 uvw;` AT FUNCTION SCOPE, not per-arm.  Per-arm they are
 *     single-block => local allocnos, get $v1 first, and push zb/dz to $a1; the
 *     target has zb/dz=$v1, tp=$a1.  Function scope makes tp a global allocno
 *     and the pair swaps back.  44 -> 4 mismatched (this is 40 of the 44!).
 *     (`otp` stays per-arm, and arm E keeps TWO separately-scoped otp's — that
 *     is L4's precondition, cookbook §46-L4.)
 * Plus two small ones: read `prim` BEFORE `nprim` (moves the strength-reduced
 *     giv base from part+0x10 to the target's part+0xC, worth 7 ins), and a
 *     SEPARATE variable `wq` for `wz >> 16` (the sibling reuses `wy`; reuse ties
 *     both to $a2, the target wants wy=$v1 / wq=$a2).
 *
 * ------------------------- THE RESIDUAL (read this first) -------------------
 * sched2 ties on INSN_LUID (`sched.c rank_for_schedule`, cookbook §49):
 *   BOTH candidates measure priority 3 — `lw $s3,0x120($sp)` -> `lw $v0,0($s3)`
 *   and `lw $a1,-4($s1)` -> `srl $a2,$a1,16` are each "load + one dependent".
 *   The backward scheduler therefore picks the LARGER LUID first (= places it
 *   LAST).  sched1 SINKS the srl to sit immediately before its first consumer
 *   (`sh $a2,0x34($sp)`), giving it the larger LUID, so it always lands after
 *   the load.  The target needs the opposite sign.
 * DO NOT RE-BUY (all byte-measured on this draft):
 *   - every permutation of the {xx,yy,zz} read order and of the mn/mx/mny/my
 *     assignment order (2, 6, 14 or 16 mismatched; NEVER 0) — the pair is
 *     invariant under source statement order, which is exactly the §49
 *     signature of a sched1 sink rather than an expand-stream LUID;
 *   - box[0..3] store groupings: per-element (this file, 2), vy/vz-then-vx (2),
 *     all-vz/all-vy/all-vx (10), vz-first-per-element (10), box[2..3] first (14);
 *   - reading part->xx inline at the vx stores (14) or via `*(u32*)part` (16);
 *   - `__asm__ volatile("")` before the xx read (+1 ins, 864), after it (+1 ins,
 *     863), after `wq` (29); `asm("" :: "r"(wq))` (29); `asm("" ::: "$2")`
 *     before the xx read (14) / after wq (29);
 *   - `register u32 wq __asm__("$6")` (2, no change); dropping `wq` and writing
 *     `wz >> 16` inline at all four sites (2, no change).
 * -------- L6  THE GHOST-WEDGE PAIR (S43; what actually closed it) ----------
 * TRUE ROOT CAUSE (read from cc1's own -dR trace + sched.c/global.c source):
 *   sched2 (backward) trace at the block: the wx load (insn 112) becomes ready
 *   EXACTLY one tick after the first box sh (139) is picked (anti-dep, MIPS
 *   ADJUST_COST clamps anti cost to 1) and is ALWAYS unit-blocked there
 *   (`;; blocking insn 112 for 1 cycles` — r3000 memory-unit
 *   blockage(load,store)=2, so a load can NEVER issue in the tick right after
 *   a store pick).  schedule_select therefore wedges one ready ALU insn
 *   between the lw and the sh — under ANY source order / LUID assignment the
 *   wedge slot eats a real insn (all reachable outputs enumerated: srl-a2,
 *   srl-t0 or addu-a3 lands at idx 76).  The target has NOTHING there, which
 *   is only possible if the wedge tick was absorbed by a ZERO-EMISSION insn.
 * L6a `__asm__("" : "=r"(wq) : "0"(wq), "r"(wz));` right after `wq = wz>>16`.
 *   The in/out re-tie is same-reg (empty template → 0 bytes) and (a) becomes
 *   the a2-chain insn sched2 picks into the blocked tick (pred = the srl,
 *   succs = the wq-reading sh's → ready exactly when needed, pri 2), and
 *   (b) makes reg_n_sets(wq)=2, killing the §49 sched1 birthing boost.  The
 *   bare re-tie alone flips wz/wq off $a1/$a2 (wq density rises); the extra
 *   `"r"(wz)` read restores the pair (the §S13 both-rivals counter-lever).
 * L7  `__asm__("" : "=r"(pkt) : "0"(pkt));` immediately after L6a.
 *   L6a alone rotates the {s4,s5,s7} homes of the &g.sz0/1/2 loop invariants
 *   (12 mismatches): global.c allocno_compare pri = (int)((floor_log2(refs)*
 *   refs/live_length)*10000*size); the trio (refs 10, lengths 742/743/744)
 *   sits ON the integer-floor boundary 300000/742=404 vs /743=403, and ONE
 *   extra in-loop insn drops sz2 into the same bucket as sz1 (alloc order
 *   [254,250,252]→[252,254,250], first-allocated gets $s7).  A SECOND
 *   zero-emission in-range insn pushes lengths to 744/745/746 = (403,402,402),
 *   restoring the target order.  pkt is the re-tie host because its huge
 *   ref count sits nowhere near a floor boundary (ot-host: LENGTH-DRIFT 705;
 *   double-wq: REGALLOC-PERM 10 — both measured).
 * ========================================================================= */

/* Types below live in src/shared/engine_types.h (identical spellings); the guard
 * keeps this draft self-contained for tools/match_one.py yet conflict-free when
 * spliced into the real TU (tools/rtu_match.py), which pulls engine_types.h in. */
#ifndef BFM_ENGINE_TYPES_H



extern void func_800547D8(s32, MATRIX2 *);
extern void func_80052E38(MATRIX2 *);



#endif

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

void func_8017EF68(s32 arg0, s32 arg1, s32 arg2)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern s32 D_801AE6E0;

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    SVECTOR2 vv[4];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    u32 colA;
    u32 colB;
    s32 nparts;
    Part *part;
    u32 nprim;
    s32 j;
    u32 i;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w;
    s32 code;
    u32 wx, wy, wz;
    u32 wq;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    s32 d;
    u32 e;
    u32 *tp;
    u32 uvw;

    if (*(s32 *)arg0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg2, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    d = D_801AE6E0;
    colA = (d << 16) | (d << 8) | d;
    e = d * 2;
    if (e > 0xFF) e = 0xFF;
    colB = (e << 16) | (e << 8) | e;
    part = (Part *)(arg1 + 0x14);
    nparts = *(s32 *)(arg1 + 8);
    vtx = *(u8 **)(arg1 + 0x10);

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wq = wz >> 16;
        __asm__("" : "=r"(wq) : "0"(wq), "r"(wz));
        __asm__("" : "=r"(pkt) : "0"(pkt));
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wq;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wq;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        box[4].vx = mn; box[4].vy = my; box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my; box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my; box[6].vz = wq;
        box[7].vx = mx; box[7].vy = my; box[7].vz = wq;
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
                        vv[0] = *(SVECTOR2 *)va;
                        vv[1] = *(SVECTOR2 *)vb;
                        vv[2] = *(SVECTOR2 *)vc;
                        gte_ldv3c(&vv[0]);
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
                                        if (my >= -0x6E && mny < 0x6F) {
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
                                            zb = za - 0x190;
                                            if (zb < 0) zb = 0;
                                            zb >>= 8;
                                            zb <<= 22;
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1] + zb;
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            za >>= 2;
                                            za <<= 2;
                                            otp = (u32 *)(za + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                    break;
                                case 2:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vv[3] = *(SVECTOR2 *)vd;
                                    gte_ldv0(&vv[3]);
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
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                u32 *otp;
                                                s32 dz;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                dz = za - 0x190;
                                                if (dz < 0) dz = 0;
                                                dz >>= 8;
                                                dz <<= 22;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1] + dz;
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                za >>= 2;
                                            za <<= 2;
                                            otp = (u32 *)(za + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vv[3] = *(SVECTOR2 *)vd;
                                    gte_ldv0(&vv[3]);
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
                                    __asm__ __volatile__ ("" ::: "$6");
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
                                        gte_stsxy((long *)&tmpxy[3]);
                                        if (tmpxy[3].vx < mn) mn = tmpxy[3].vx;
                                        else if (mx < tmpxy[3].vx) mx = tmpxy[3].vx;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (tmpxy[3].vy < mny) mny = tmpxy[3].vy;
                                            else if (my < tmpxy[3].vy) my = tmpxy[3].vy;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                s32 dz;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                dz = za - 0x190;
                                                if (dz < 0) dz = 0;
                                                dz >>= 8;
                                                dz <<= 22;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                *(u32 *)&((PolyFT4 *)pkt)->x3 = *(u32 *)&tmpxy[3];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = colA | 0x2E000000;
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1] + dz;
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                {
                                                u32 *op1;
                                                za >>= 2;
                                                za <<= 2;
                                                op1 = (u32 *)(za + ot);
                                                *(u32 *)pkt = (*op1 & 0xFFFFFF) | 0x9000000;
                                                *op1 = (*op1 & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                }
                                                pkt += 0x28;
                                                pkt[3] = 6;
                                                *(u32 *)(pkt + 8) = colB | 0x2A000000;
                                                *(u32 *)(pkt + 0xC) = *(u32 *)&tmpxy[0];
                                                *(u32 *)(pkt + 4) = 0xE1000040;
                                                *(u32 *)(pkt + 0x10) = *(u32 *)&tmpxy[1];
                                                *(u32 *)(pkt + 0x14) = *(u32 *)&tmpxy[2];
                                                *(u32 *)(pkt + 0x18) = *(u32 *)&tmpxy[3];
                                                {
                                                u32 *op2 = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*op2 & 0xFFFFFF) | 0x6000000;
                                                *op2 = (*op2 & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                }
                                                pkt += 0x1C;
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


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017FE8C(void *a0) {
    func_80146A6C(0x19, a0, 0, 0, 0, 0, 1);
}



extern void (*D_8018BFC0[])(void);

void func_8017FEC8(void *a0) {
    D_8018BFC0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017FF04(void *a0)
{
    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        func_80147324(*(u16 *)((s32)a0 + 0x2E));
    }
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



// @class: plumbing
// @stuck: none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

extern void func_801801E8(int);

void func_8017FF54(int param_1)
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
    func_801801E8(param_1);
    return;
}



/* Entity record touched by func_8017FFB0 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */

extern void func_80147324(s32 arg0);
extern void func_801801E8(int);

void func_8017FFB0(Ent_8017BFE0_8017FFB0 *param_1)
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
    ((void (*)(Ent_8017BFE0_8017FFB0 *))func_801801E8)(param_1);
}





/* func_80180034 — entity tick with a two-mode "hit/shake" arm.
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
extern void func_801801E8(int);

void func_80180034(void *a0)
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
    ((void (*)(void *))func_801801E8)(a0);
}


extern void func_801801E8(int);
extern void func_80146C3C(void);
void func_8018019C(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_801801E8(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}




/* func_801801E8 — 4-point primitive sweep driven by the 44-byte curve table
 * D_8018BF94.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_801801E8(int param_1)
{

    extern u16 D_800B99DA;
    extern u8  D_8018BF94[];
    SVec8_8017C218_801801E8 rot;
    s32   pad0[2];
    Prim_8017C218_801801E8  prim;
    s32   pad1[1];
    Mtx_8017C218_801801E8   mtx;
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

    p = D_8018BF94;
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
    p = D_8018BF94;
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
        p = D_8018BF94;
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



extern void (*D_8018BFD4[])(void);

void func_801804F4(void *a0) {
    D_8018BFD4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_80180530(void *a0)
{
    func_80147324(*(u16 *)((s32)a0 + 0x2E));
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



/* func_80180570 — a state-tick: bump the frame counter at 0x1C; while it is
 * below 0xC spin the angle at 0x12 by 0xE0, otherwise reset the counter, zero
 * the vector at *(0x34)+0x60/0x64, set +0x62 to 0x3000 and advance the state
 * word at 0x02.  Falls through to ((void (*)(void *))func_801801E8)(a0) on both arms (the target
 * leaves $a0 untouched, so the call needs no move).
 *
 * §71 sibling-first: func_8017C560 (same TU, 4 bytes earlier) is the same
 * `*(u16 *)(a0 + 2) += 1` idiom, and func_801801E8's own prologue reads
 * `lw $s1, 0x34($s2)` / `lhu $v0, 0x12($s2)` — same record, same widths.
 */

extern void func_801801E8(int);

void func_80180570(void *a0) {
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
    ((void (*)(void *))func_801801E8)(a0);
}



/* func_801805E0 — small entity tick:
 *   read counter @0x1C and the sub-object pointer @0x34 up-front, bump the
 *   counter unconditionally (gcc puts that store in the beqz delay slot),
 *   then either slide @0x2A down by 0x10 or run the 3-call teardown. */

extern void func_80147324(s32 arg0);
extern void func_80147084(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801801E8(int);

void func_801805E0(void *a0)
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
    ((void (*)(void *))func_801801E8)(a0);
}



extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_801801E8(int);

void func_8018066C(void *a0)
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
    ((void (*)(void *))func_801801E8)(a0);
}


extern void func_801801E8(int);
extern void func_80146C3C(void);
void func_80180740(void *a0)
{
    void *obj;
    s16 v;
    v = *(u16 *)((s32)a0 + 0x12) - 0x100;
    obj = *(void **)((s32)a0 + 0x34);
    *(s16 *)((s32)a0 + 0x12) = v;
    if (v > 0) {
        ((void (*)(void *))func_801801E8)(a0);
    } else {
        *(s16 *)((s32)obj + 0x64) = 0x1000;
        *(s16 *)((s32)obj + 0x62) = 0x1000;
        *(s16 *)((s32)obj + 0x60) = 0x1000;
        func_80146C3C();
    }
}



extern void (*D_8018BFE8[])(void);

void func_80180794(void *a0) {
    D_8018BFE8[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_801807D0 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
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

void func_801807D0(void *a0)
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
extern void func_801808E0(void *a0);
void func_80180884(void *a0)
{
    s32 t;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0xA) {
        ((void (*)(void))func_800D22E4)();
        func_801808E0(a0);
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}




void func_801808E0(void *a0)
{
    extern Mtx8_8017C910_801808E0 aD800AE620 __asm__("D_800AE620");
    extern void aFunc80016A5C(void *arg0, void *arg1) __asm__("func_80016A5C");
    Prim_8017C910_801808E0 prim;
    Mtx8_8017C910_801808E0 mtx;
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


extern void func_801472F0(void *a0);
extern void func_8014B2A8(void);
extern u8 D_80078EC0;
extern s32 D_80078EA4;
extern void func_8002931C(s32);
extern void (*D_8011DB28)(s32 a0);
extern void func_80180AB8(void);
extern void func_80029514(s32);

void func_80180A50(void)
{
    func_801472F0((void *)0x42E);
    func_8014B2A8();
    D_80078EA4 = 0xA00000;
    D_80078EC0 &= 0x7F;
    func_8002931C(0x1A40000);
    D_8011DB28 = func_80180AB8;
    func_80029514(0x4BA);
}


extern void func_80183674();
    void func_80180AB8(void) {
        func_80183674();
    }



extern void (*D_8018C040[])(void);

void func_80180AD8(void *a0) {
    D_8018C040[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801811B4(void);
extern void func_800167B8(s32 a0);

s32 func_80180B14(s32 a0) {
    func_801811B4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80180B58(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018C048[])(void);

void func_80180B7C(void *a0) {
    D_8018C048[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801811DC(void);

s32 func_80180BB8(s32 a0) {
    func_801811DC();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_80180BF8(u8 *a0) {
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
    void func_80180C74(void) {
        func_800D1EBC();
    }



extern void (*D_8018C054[])(void);

void func_80180C94(void *a0) {
    D_8018C054[*(u8 *)((s32)a0 + 0x15)]();
}




















extern void func_8018152C(void);
s32 func_80180CD0(s32 arg0)
{
  s32 temp_v0;
 do { func_8018152C(); temp_v0 = (*((u8 *) (arg0 + 0x15))) + 1; *((u8 *) (arg0 + 0x15)) = temp_v0; } while (temp_v0 = 0);
  return temp_v0;
}


s32 func_80180D0C(void) {
        return 0;
    }


extern void func_80011ADC(void);
extern u8 D_800B9A10;

s32 func_80180D14(s32 arg0) {
    func_80011ADC();
    *(s32 *)(arg0 + 8) &= 0x7F000000;
    D_800B9A10 = 1;
    return 0;
}



extern void (*D_8018C070[])(void);

void func_80180D5C(void *a0) {
    D_8018C070[*(u8 *)((s32)a0 + 0x216)]();
}


extern s32 D_801AE6E8;
extern void func_801815E8(void);
extern s32 func_80171990(u8 *a0);

void func_80180D98(u8 *a0) {
    D_801AE6E8 = 0;
    func_801815E8();
    *(s32 *)(a0 + 0x204) = 0;
    func_80171990(a0);
}


extern s32 func_80171990(u8 *a0);
extern s16 D_801274EA;

void func_80180DD4(u8 *a0) {
    s16 *p;
    s32 d;
    s32 t;
    s32 w;
    s32 lim;

    p = &D_801274EA;
    d = *(u16 *)(a0 + 0xA) - 0x300;
    t = *(u16 *)p - d;
    w = *(s32 *)(a0 + 0x204) + 0x4000;
    *(s32 *)(a0 + 0x204) = w;
    lim = 0x600000;
    if (w > lim) {
        *(s32 *)(a0 + 0x204) = lim;
    }
    *(u16 *)p = *(u16 *)p - *(u16 *)(a0 + 0x206);
    if ((s16)t < 0x200) {
        func_80171990(a0);
    }
}


extern s32 func_80171990(u8 *a0);
extern s16 D_801274EA;

void func_80180E58(u8 *a0) {
    s32 amt;
    s16 *p;
    s32 d;
    s32 t;
    s32 w;
    s32 lim;

    amt = 0xFFFE4000;
    p = &D_801274EA;
    d = *(u16 *)(a0 + 0xA) - 0x300;
    t = *(u16 *)p - d;
    w = *(s32 *)(a0 + 0x204) + amt;
    *(s32 *)(a0 + 0x204) = w;
    lim = 0x10000;
    if (w < lim) {
        *(s32 *)(a0 + 0x204) = lim;
    }
    *(u16 *)p = *(u16 *)p - *(u16 *)(a0 + 0x206);
    if ((s16)t < 0) {
        *(s32 *)(a0 + 0x200) = 0x1E;
        func_80171990(a0);
    }
}


extern s32 func_80171990(u8*);
void func_80180EE0(void *a0) {
    s32 v0 = *(s32 *)((u8 *)a0 + 0x200) - 1;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 == -1) {
        ((void (*)(void *))func_80171990)(a0);
    }
}


extern s32 func_8012E544(s32 a0);
extern void func_8012C098(void *a0);
extern void func_80185D7C(void);
extern void func_80181554(void);
extern void func_80171928(void *a0);

void func_80180F14(s32 a0) {
    s32 v0;

    v0 = func_8012E544(0x2E6);
    if (v0 != 0) {
        func_8012C098((void *)v0);
    }

    v0 = func_8012E544(0x2F6);
    if (v0 != 0) {
        func_8012C098((void *)v0);
    }

    v0 = func_8012E544(0x2F5);
    if (v0 != 0) {
        func_8012C098((void *)v0);
    }

    v0 = func_8012E544(0x310);
    if (v0 != 0) {
        func_8012C098((void *)v0);
    }

    v0 = func_8012E544(0x2F2);
    if (v0 != 0) {
        func_8012C098((void *)v0);
    }

    func_80185D7C();
    func_80181554();
    func_80171928((void *)a0);
}


extern void (*D_8018C084[])(void);
extern s32 func_80149184(s32 a0);
extern s16 D_801152A0;
extern void func_80183674();
extern void func_80172358(u8 *a0, u8 *a1);

void func_80180FC8(void *a0)
{
    s16 buf[2];

    D_8018C084[*(u8 *)((s32)a0 + 0x216)]();
    D_801152A0 = func_80149184((s32)a0);
    ((void (*)(void *))func_80183674)(buf);
    buf[1] = -0x3AE;
    func_80172358((u8 *)a0, buf);
}


extern void func_8014708C(void *a0);
extern s32 func_801472C8(struct S *a0);
extern s32 func_80171990(u8*);
void func_8018103C(void *a0) {
    func_8014708C(a0);
    func_801472C8((struct S *)a0);
    ((void (*)(void *))func_80171990)(a0);
}


extern void func_80154150(s32 a0, s32 a1);
    extern void func_8014706C(void *arg0);
    extern s32 func_80171990(u8 *a0);
    void func_80181074(s32 arg0) {
        func_80154150(arg0, 0x4);
        ((void (*)(s32))func_8014706C)(arg0);
        ((void (*)(void *))func_80171990)((void *)arg0);
    }


extern s32 func_80171990(u8 *a0);
    void func_801810B0(void) {
        ((s32 (*)(void))func_80171990)();
    }


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171990(u8 *a0);

void func_801810D0(s32 arg0) {
    func_80146994(0x1A, arg0, 0xA030A04, 0);
    func_80171990((u8 *)arg0);
}


extern s32 func_8014C050(s32 a0, s32 a1);
extern s32 func_8013767C(s32 a0);
extern s32 func_80171990(u8 *a0);
extern M2C_UNK D_80191F00;

void func_80181114(void *a0) {
    if (!func_8014C050((s32)a0, 0x1A)) {
        *(s32 *)((u8 *)a0 + 0x198) = func_8013767C((s32)&D_80191F00);
        ((void (*)(void *))func_80171990)(a0);
    }
}


extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80171928(void *a0);
void func_80181164(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(s32 *)(a0 + 0x198) = 0;
        func_80171928(a0);
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_801811B4(void) {

    extern s32 D_8018C060(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018C060, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_801811DC(void) {

    extern s32 D_8018C09C(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018C09C, 0x1000000);
}


extern s32 D_8018C0B4[];
extern s32 D_801AE6E8;
extern s32 func_80182888(void);

void func_80181204(s32 a0) {
    void (*func_ptr)(void);
    u8 idx = *(u8 *)(a0 + 0x216);
    func_ptr = (void (*)(void))D_8018C0B4[idx];
    func_ptr();
    if (D_801AE6E8 == 0) {
        if (func_80182888() != 0) {
            D_801AE6E8 += 1;
        }
    }
}


extern void func_8014706C(void*);
extern void func_8014708C(void*);
extern s32 func_801472C8(struct S*);
extern s32 func_80171990(u8*);
void func_8018127C(s32 a0) {
    ((void (*)(s32))func_8014706C)(a0);
    ((void (*)(s32))func_8014708C)(a0);
    ((s32 (*)(s32))func_801472C8)(a0);
    ((void (*)(s32))func_80171990)(a0);
}


extern s32 func_8001311C(s32 a0, s32 a1, s32 a2);
extern s16 D_8018C0D0;
extern s16 D_8018C0D2;
extern s16 D_8018C0D4;

void func_801812BC(void *a0)
{
    s32 d;
    s16 acc;

    d = func_8001311C(*(s16 *)((s32)a0 + 6), D_8018C0D0, 10);
    *(u16 *)((s32)a0 + 6) = *(u16 *)((s32)a0 + 6) + d;
    acc = d;
    d = func_8001311C(*(s16 *)((s32)a0 + 10), D_8018C0D2, 10);
    *(u16 *)((s32)a0 + 10) = *(u16 *)((s32)a0 + 10) + d;
    acc = acc | d;
    d = func_8001311C(*(s16 *)((s32)a0 + 14), D_8018C0D4, 10);
    *(u16 *)((s32)a0 + 14) = *(u16 *)((s32)a0 + 14) + d;
    acc = acc | d;
    if (acc == 0) {
        func_80147060(a0);
        func_80147084(a0);
        func_801472B4(a0);
        func_80171990(a0);
    }
}


void func_80181388(u8 *a0)
{
    s16 *p;
    s32 r;
    r = func_80012B04(((s16 **)a0)[8][9], 0x800, 4);
    if ((s16)r == 0) {
        func_80171990(a0);
    }
    p = ((s16 **)a0)[8];
    ((u16 *)p)[9] = (((u16 *)p)[9] + r) & 0xFFF;
}


extern s32 D_801AE6E8;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_801813FC(u8 *a0) {
    if (D_801AE6E8 != 0) {
        func_8002D4C8(0x92A, 0);
        func_80171990(a0);
    }
}


extern s32 func_8017EE98(s32 arg);
    extern s32 func_80171990(u8 *a0);
    void func_80181440(s32 param_1) {
        if (((int (*)(void))func_8017EE98)() != 0) {
            ((void (*)(s32))func_80171990)(param_1);
        }
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181478);

extern s32 func_8017EECC(void);
extern void func_80171928(void *a0);
extern u8 D_800AE6BD;

void func_801814DC(void *a0) {
    if (func_8017EECC()) {
        D_800AE6BD += 1;
        func_80171928(a0);
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018C0A0;

void func_8018152C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018C0A0, 0x1000000);
}


void func_80181554(void) {
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_80181A78(void *);
    extern void func_8012A018(s32, s32);
    extern void func_8012A094(s32);

    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 0);
    func_8012A094((s32)D_80126948);
    func_80181A78((void *)D_80126948);
}


void func_801815E8(void) {
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8012A094(s32 a0);
    extern void func_80181A78(void *a0);
    extern void func_80181E98();
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;
    extern s16 D_80126942;

    D_80126954 = 0x12C;
    D_8012695C = 0x898;
    D_80126968 = -0x155;
    D_8012696A = 0x200;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    D_801274EC = 0;
    D_801274E8 = 0;
    D_801274EA = D_80126942 + 0xC00;
    func_8012A018((s32)func_80181A78, 1);
    func_8012A094((s32)D_80126948);
    func_80181A78(D_80126948);
    func_80181E98(D_80126948);
}


void func_801816AC(void) {
    extern struct { u8 b[8]; } D_8018C0E0, D_801274E8;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_8012A018(s32, s32);
    extern void func_8012A094(s32);
    extern void func_80181A78(void *);

    D_801274E8 = D_8018C0E0;
    D_80126954 = 0x190;
    D_8012695C = 0x900;
    D_80126968 = 0x140;
    D_8012696A = 0xE00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 2);
    func_8012A094((s32)D_80126948);
    func_80181A78((void *)D_80126948);
}


typedef struct { u8 b[8]; } Blk8_80181774;

void func_80181774(void) {
    extern Blk8_80181774 D_8018C0E8;
    extern Blk8_80181774 D_801274E8;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_8012A018(s32, s32);
    extern void func_8012A094(s32);
    extern void func_80181A78(void *);

    D_801274E8 = D_8018C0E8;
    D_80126954 = 0x190;
    D_8012695C = 0x900;
    D_80126968 = 0x140;
    D_8012696A = 0xE00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 2);
    func_8012A094((s32)D_80126948);
    func_80181A78((void *)D_80126948);
}


extern void func_8012A568(void (*a0)(void));
    extern s32 func_80181864(s32 a0);
    s32 func_8018183C(void)
{
        ((void (*)(void *))func_8012A568)((void *)func_80181864);
    }




s32 func_80181864(s32 _arg0)
{
    extern Blk8_80181774 D_8018C0F0;
    extern Blk8_80181774 D_801274E8;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_8012A018(s32, s32);
    extern void func_80181A78(void *);

    D_801274E8 = D_8018C0F0;
    D_80126954 = 0x190;
    D_8012695C = 0x480;
    D_80126968 = 0x180;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 2);
    func_80181A78((void *)D_80126948);
}


extern s32 func_80181940;
extern void func_8012A568(void (*)(void));
void func_80181918(void) {
    ((s32 (*)(s32 *))func_8012A568)(&func_80181940);
}


void aF80181940(void) __asm__("func_80181940");
void aF80181940(void) {
    typedef struct { u8 b[8]; } Blk8_80181940;
    extern Blk8_80181940 D_8018C0F8;
    extern Blk8_80181940 D_801274E8;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_8012A018(s32 a, s32 b);
    extern void func_80181A78(void *a0);

    D_801274E8 = D_8018C0F8;
    D_80126954 = 0x190;
    D_8012695C = 0x200;
    D_80126968 = 0x40;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 2);
    func_80181A78((void *)D_80126948);
}


void func_801819F4(void) {
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_80181A78(void *);
    extern void func_8012A018(s32, s32);

    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181A78, 0);
    func_80181A78((void *)D_80126948);
}



extern void (*D_8018C100[])(void);

void func_80181A78(void *a0) {
    D_8018C100[*(u8 *)((s32)a0 + 0x4)]();
}


typedef struct { s16 v[4]; } Blk8_80126940_8017D474;
typedef struct { s16 v[8]; } Blk16_80126940;

void func_80181AB4(s32 a0) {

    extern s32 D_80126B58;
    extern u8 D_8018C114[];
    extern Blk8_80126940_8017D474 D_80126940;
    extern u16 func_80148800(s32 *a0);
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181CCC();
    extern void func_80181EA0();
    Blk16_80126940 sp10;
    register s32 ang __asm__("$16");
    s32 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = *(s16 *)(D_8018C114 + t * 2);
    }
    *(Blk8_80126940_8017D474 *)&sp10 = *(Blk8_80126940_8017D474 *)D_80126940.v;

    ang = ratan2(sp10.v[0], sp10.v[2]) & 0xFFF;
    if (sp10.v[1] > -0x200) {
        sp10.v[1] = -0x200;
    }

    func_80181CCC(a0, sp10.v, ang);
    func_80181EA0(a0, sp10.v, ang);
}


void func_80181BA4(s32 param_1)
{
    typedef struct { u8 b[8]; } Blk8_80181774;
    typedef struct { s16 m0, m1, m2, m3; } Sp10_80181BA4;
    extern Blk8_80181774 D_801274E8;
    extern s32 ratan2(s32 dx, s32 dy);
    extern void func_80181CCC();
    extern void func_80181F14();
    Sp10_80181BA4 sp10;
    register s32 ang __asm__("$16");

    sp10 = *(Sp10_80181BA4 *)D_801274E8.b;
    ang = ratan2(sp10.m0, sp10.m2) & 0xFFF;
    func_80181CCC(param_1, (s32)&sp10, ang);
    func_80181F14(param_1, (s32)&sp10, ang);
}


void func_80181C38(s32 param_1)
{
    typedef struct { u8 b[8]; } Blk8_80181774;
    typedef struct { s16 m0, m1, m2, m3; } Sp10_80181C38;
    extern Blk8_80181774 D_801274E8;
    extern void func_80181CCC();
    extern void func_80181EA0();
    Sp10_80181C38 sp10;
    register s32 ang __asm__("$16");

    sp10 = *(Sp10_80181C38 *)D_801274E8.b;
    ang = ratan2(sp10.m0, sp10.m2) & 0xFFF;
    func_80181CCC(param_1, (s32)&sp10, ang);
    func_80181EA0(param_1, (s32)&sp10, ang);
}


extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_801860A8(u16 *r, s16 *m);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_80181CCC(s32 param_1, s32 param_2, s32 param_3)
{
    u8 mat[0x20];
    s16 svIn[4];
    u16 vecOut[4];
    u16 r[4];

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C(*(s16 *)(param_1 + 0x8),  *(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC(*(s16 *)(param_1 + 0x1A), *(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC(*(s16 *)(param_1 + 0x1C), *(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C(*(s16 *)(param_1 + 0x2A), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C(*(s16 *)(param_1 + 0x2C), *(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + *(s16 *)(param_2 + 0);
    *(s32 *)(param_1 + 0x4C) = *(s16 *)(param_1 + 0x2A) + *(s16 *)(param_2 + 2);
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2C) + *(s16 *)(param_2 + 4);

    r[0] = *(u16 *)(param_1 + 0x18);
    r[1] = *(u16 *)(param_1 + 0x1A) + param_3;
    r[2] = *(u16 *)(param_1 + 0x1C);
    func_801860A8(r, (s16 *)mat);

    svIn[0] = 0;
    svIn[1] = 0;
    svIn[2] = *(s32 *)(param_1 + 0x10);
    ApplyMatrixSV(mat, svIn, vecOut);

    *(s32 *)(param_1 + 0x3C) = ((s16)vecOut[0] >> 3) + *(s16 *)(param_1 + 0x28) + *(s16 *)(param_2 + 0);
    *(s32 *)(param_1 + 0x40) = ((s16)vecOut[1] >> 3) + *(s16 *)(param_1 + 0x2A) + *(s16 *)(param_2 + 2);
    *(s32 *)(param_1 + 0x44) = ((s16)vecOut[2] >> 3) + *(s16 *)(param_1 + 0x2C) + *(s16 *)(param_2 + 4);
}


void func_80181E98(void) {
}

extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];

void func_80181EA0(s32 param_1, s32 param_2, s16 param_3)
{
    D_800B9AB8[0] = param_3 * 0x280 / 0x1000;
    D_800B9ABA[0] = 0xF0 - (-0x200 - *(s16 *)(param_2 + 2)) * 0xF0 / 0xA00;
}


extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];

void func_80181F14(s32 param_1, s32 param_2, s16 param_3)
{
    s32 iVar1;
    iVar1 = param_3 * 0x280;
    if (iVar1 < 0) {
        iVar1 += 0xFFF;
    }
    D_800B9AB8[0] = (s16)((iVar1 >> 12) - 0xA0);
    iVar1 = 0x852 - (s32)*(s16 *)(param_2 + 2);
    if (iVar1 < 0) {
        iVar1 += 0xF;
    }
    D_800B9ABA[0] = (s16)(0xF0 - (iVar1 >> 4));
}


void func_80181F78(void) {
    extern u32 D_801AE6F0;
    extern s32 D_801AE6F4;
    extern s32 D_801AE6F8;
    extern s32 D_801B20C4;
    extern u16 D_8018C118[];
    extern u16 D_8018C318[];
    extern u16 D_801AE6FC[];
    extern u16 D_801AE8FC[];
    extern u8 D_8018C518[];
    extern u8 D_801A9528[];
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_800183E0(s32 a0);
    extern void func_80182828(void *a0, s32 a1);
    u32 i;

    for (i = 0; i < 16; i++) {
        s32 idx = ((D_801AE6F0 >> 8) + i) & 0xF;
        D_801AE6FC[i] = D_8018C118[idx];
        D_801AE6FC[16 + i] = D_8018C118[16 + idx];
        D_801AE6FC[32 + i] = D_8018C118[32 + idx];
        D_801AE6FC[48 + i] = D_8018C118[48 + idx];
        D_801AE6FC[64 + i] = D_8018C118[64 + idx];
        D_801AE6FC[80 + i] = D_8018C118[80 + idx];
        D_801AE6FC[96 + i] = D_8018C118[96 + idx];
        D_801AE6FC[112 + i] = D_8018C118[112 + idx];
        D_801AE6FC[128 + i] = D_8018C118[128 + idx];
        D_801AE6FC[144 + i] = D_8018C118[144 + idx];
        D_801AE6FC[160 + i] = D_8018C118[160 + idx];
        D_801AE6FC[176 + i] = D_8018C118[176 + idx];
        D_801AE6FC[192 + i] = D_8018C118[192 + idx];
        D_801AE6FC[208 + i] = D_8018C118[208 + idx];
        D_801AE6FC[224 + i] = D_8018C118[224 + idx];
        D_801AE6FC[240 + i] = D_8018C118[240 + idx];
        D_801AE8FC[i] = D_8018C318[idx];
        D_801AE8FC[16 + i] = D_8018C318[16 + idx];
        D_801AE8FC[32 + i] = D_8018C318[32 + idx];
        D_801AE8FC[48 + i] = D_8018C318[48 + idx];
        D_801AE8FC[64 + i] = D_8018C318[64 + idx];
        D_801AE8FC[80 + i] = D_8018C318[80 + idx];
        D_801AE8FC[96 + i] = D_8018C318[96 + idx];
        D_801AE8FC[112 + i] = D_8018C318[112 + idx];
        D_801AE8FC[128 + i] = D_8018C318[128 + idx];
        D_801AE8FC[144 + i] = D_8018C318[144 + idx];
        D_801AE8FC[160 + i] = D_8018C318[160 + idx];
        D_801AE8FC[176 + i] = D_8018C318[176 + idx];
        D_801AE8FC[192 + i] = D_8018C318[192 + idx];
        D_801AE8FC[208 + i] = D_8018C318[208 + idx];
        D_801AE8FC[224 + i] = D_8018C318[224 + idx];
        D_801AE8FC[240 + i] = D_8018C318[240 + idx];
    }
    func_800183E0((s32)D_8018C518);
    D_801AE6F0 -= 0x100;
    if (D_801B20C4 == 0)
        goto Lcase0;
    if (D_801B20C4 == 1)
        goto Lcase1;
    goto Lend;
Lcase0:
    D_801AE6F4 = 1;
    D_801AE6F8 = 0;
    func_8002D4C8(0xB39, 0);
    D_801B20C4 += 1;
    goto Lend;
Lcase1:
    if (--D_801AE6F4 != 0)
        goto Lend;
    D_801AE6F4 = 2;
    func_80182828(D_801A9528, D_801AE6F8 * 6);
    D_801AE6F8 = (D_801AE6F8 + 1) & 0x1F;
Lend:;
}



extern void (*D_8018C548[])(void);

void func_80182348(void *a0) {
    D_8018C548[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8013C0F8(void *a0);
    extern s32 func_8017EF08(s32 a0);
    extern s32 D_801A158C;
    extern s32 D_801AEB00;
    void func_80182384(void) {
        ((void (*)(void *))func_8013C0F8)(&D_801A158C);
        ((void (*)(s32))func_8017EF08)((s32)&D_801AEB00);
    }


extern s16 D_801AEB52[];
extern s32 D_801A158C;
extern s32 D_801AEB1C;
extern s32 D_801B20E0;
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8017EF68(s32 a0, s32 a1, s32 a2);

void func_801823BC(a0, a1)
s32 a0;
s32 a1;
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);
    extern s16 D_801AEB52[];
    extern s32 D_801B20E0;
    extern s32 D_801A158C;
    extern s32 D_801AEB1C;
    register s16 *q asm("$17");

    q = D_801AEB52;
    *q = a0;
    func_80049CAC((s32)q - 2, (s32)q - 78);
    __asm__("" : "=r"(q) : "0"(q));
    D_801AEB1C = (s16)a1;
    *(s32 *)((s32)q - 82) = 0;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_801A158C, (s32)q - 82);
}


extern void func_8013C0F8(void *a0);
    extern s32 func_8017EF08(s32 a0);
    extern s32 D_801A3A0C;
    extern s32 D_801AEB58;
    void func_8018242C(void) {
        ((void (*)(void *))func_8013C0F8)(&D_801A3A0C);
        ((void (*)(s32))func_8017EF08)((s32)&D_801AEB58);
    }


void func_80182464(s32 a0, s32 a1)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);
    extern s16 D_801AEBAA[];
    extern s32 D_801B20E0;
    extern s32 D_801A3A0C;
    extern s32 D_801AEB74;
    register s16 *q asm("$17");

    q = D_801AEBAA;
    *q = a0;
    func_80049CAC((s32)q - 2, (s32)q - 78);
    __asm__("" : "=r"(q) : "0"(q));
    D_801AEB74 = (s16)a1;
    *(s32 *)((s32)q - 82) = 0;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_801A3A0C, (s32)q - 82);
}



extern void func_8013C0F8(void *a0);
extern s32 func_8017EF08(s32 a0);
extern s32 D_8019FD8C;
extern s32 D_80197B60;
extern s32 D_801AEBB0;
extern s32 D_801AEC08;
extern s32 D_801AEC60;
extern s32 D_801AEAFC;

void func_801824D4(void *a0) {
    func_8013C0F8(&D_8019FD8C);
    func_8013C0F8(&D_80197B60);
    func_8017EF08((s32)&D_801AEBB0);
    func_8017EF08((s32)&D_801AEC08);
    D_801AEAFC = 0x1310000;
    D_801AEC60 = 0;
    ((struct { u8 pad[2]; u16 f; } *)a0)->f += 1;
    *(s16 *)((s32)a0 + 0xE0) = 1;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182560);

s16 func_801825D8(void) {

    extern s16 D_801AEAFE;
    return D_801AEAFE;
}


s32 func_801825E8(void) {
    extern s32 D_801AEC60;

    if (D_801AEC60 < 2) {
        D_801AEC60 = 1;
        return 0;
    }
    return 1;
}


extern s32 D_801AEAFC;
extern s16 D_801AEAFE;
extern void (*D_801889E4[])(void);
extern u16 D_800B99DC;
extern s32 D_801B20E0;
extern s32 D_8019FD8C;
extern s32 D_80197B60;
extern s32 D_801AEBCC;
extern s32 D_801AEC08;
extern void func_8013C9C4(void *a0);
extern void func_8017EF68(s32 arg0, s32 arg1, s32 arg2);

void func_80182614(void *a0) {
    s32 *p;
    s32 *base;
    s32 *q;
    u16 val;

    __asm__("la %0, D_801AEAFC" : "=r"(p));
    *p += 0xFFFEE000;
    if (D_801AEAFE < 0) {
        *p = 0;
        (*(u16 *)((s32)a0 + 2))++;
    }
    val = *(u16 *)((s32)a0 + 0xE0);
    val--;
    *(u16 *)((s32)a0 + 0xE0) = val;
    if ((val << 0x10) == 0) {
        func_8013C9C4(&D_801889E4);
        *(u16 *)((s32)a0 + 0xE0) = (D_800B99DC & 7) + 3;
    }
    __asm__("la %0, D_801B20E0" : "=r"(base));
    __asm__("la %0, D_801AEBCC" : "=r"(q));
    q[-7] = 0;
    q[0] = D_801AEAFE;
    func_8017EF68((s32)base, (s32)&D_8019FD8C, (s32)q - 0x1C);
    func_8017EF68((s32)base, (s32)&D_80197B60, (s32)&D_801AEC08);
}


void func_8018270C(void) {
    extern s32 D_801B20E0;
    extern s32 D_8019FD8C;
    extern s32 D_80197B60;
    extern s32 D_801AEC08;
    extern s32 D_801AEBCC;
    extern s32 D_801AEC60;
    extern s16 D_801AEAFE;
    extern void func_8013373C(s16 a0);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);

    s32 *p;
    __asm__("la %0, D_801AEBCC" : "=r"(p));

    p[-7] = 0;
    p[0] = D_801AEAFE;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_8019FD8C, (s32)(p - 7));
    func_8017EF68((s32)&D_801B20E0, (s32)&D_80197B60, (s32)&D_801AEC08);
    D_801AEC60 = 2;
    func_8013373C(0);
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_8018278C(void) {

    extern u8 D_800AF420[];
    func_8001ABBC(0, 0, D_800AF420, 0, 0);
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801827C0(void) {

    extern u8 D_800AF428[];
    func_8001ABBC(0, 0, D_800AF428, 0, 0);
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801827F4(void) {

    extern u8 D_800AF430[];
    func_8001ABBC(0, 0, D_800AF430, 0, 0);
}



void func_80182828(void *a0, s32 a1)
{
    register s32 offset __asm__("$2");
    s16 buf[4];
    u16 t0, t1, t2, t3;
    u16 *ptr;

    offset = a1 << 1;
    ptr = (u16 *)((s32)offset + (s32)a0);

    t0 = ptr[0];
    buf[0] = t0;

    t1 = ptr[1];
    buf[1] = t1;

    t2 = ptr[2];
    buf[2] = t2;

    t3 = ptr[3];
    buf[3] = t3;

    MoveImage(buf, ptr[4], ptr[5]);
}


s32 func_80182888(void)
{
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_800A2E20;
    extern u8 D_800AF410[];
    s32 *p = &D_800C7C60;

    *p = 0x51;
    D_800C7C64 = &D_800A2E20;
    func_8001ABBC(0, 0, D_800AF410, 0, (u32)p);
}


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_801828DC(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 2);
  new_var = 0x801828E0;
}

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_801828FC(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x3);
    }


extern void func_80182BB8(s32 a0);
extern void func_8012AD44(s32*, s16);
void func_8018291C(s32 a0) {
    func_80182BB8(a0);
    ((void (*)(s32, s32))func_8012AD44)(a0, 0x4);
}


extern void (*D_8018C5F8[])(void);

s16 func_801825D8(void);

void func_80182950(void *arg0) {
    s32 temp_v0;
    u16 temp_v1;
    u16 temp_a1;

    D_8018C5F8[*(u16 *) ((s32) arg0 + 2)]();
    temp_v0 = ((s32 (*)(void)) func_801825D8)();
    temp_v1 = *(u16 *) ((s32) arg0 + 0xFE);
    temp_a1 = *(u16 *) ((s32) arg0 + 0x100);
    *(u16 *) ((s32) arg0 + 0xA) = (temp_v1 + temp_a1) + temp_v0 - 0x131;
    func_8012B2CC((s32) arg0);
    func_80182C10(arg0);
}


extern void func_801816AC(void);
    void func_801829C8(void) {
        func_801816AC();
    }


extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_801829E8(void) {
    s32 s0;

    s0 = func_801825E8();
    if (s0 != 0) {
        func_8002D4C8(0x919, 0);
        func_8002D4C8(4, 0x918);
    }
    return s0;
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182A30(s32 arg0) {
    s32 i;
    s32 *ptr;
    s32 a0;

    a0 = arg0;
    i = 0;
    ptr = (s32 *)(a0 + 0xCC);
    do {
        *ptr = func_8012C658(0x26A, i, a0);
        i++;
        ptr++;
    } while (i < 4);
}


void func_80182A90(s32 *a0)
{
    s32 i;
    s32 *p;

    i = 0;
    p = a0 + 0x33;
    do {
        s32 v1 = *p;
        if (v1 != 0) {
            *(u16 *)(v1 + 0x5C) &= 0xFBFF;
        }
        p++;
        i++;
    } while (i < 4);
}


extern void func_80181554(void);
    void func_80182AD0(void) {
        func_80181554();
    }


extern void func_80181774(void);
    void func_80182AF0(void) {
        func_80181774();
    }


extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80182B10(u8 *a0) {
    s16 var = *(s16 *)(a0 + 0x100);
    if (var >= -0x24F) {
        *(s16 *)(a0 + 0x100) = var - 4;
        return 0;
    }
    func_8002D4C8(0x929, 0);
    func_8002D4C8(4, 0x928);
    return 1;
}



extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182B68(s32 arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8012C658(0x26b, i, arg0);
    }
}


void func_80182BB8(s32 arg0)
{
    s32 i;
    s32 *ptr;

    i = 0;
    ptr = (s32 *)((s32)arg0 + 0xCC);
    do {
        if (*ptr != 0) {
            func_80183130((void *)*ptr);
        }
        i = i + 1;
        ptr = ptr + 1;
    } while (i < 4);
}


void func_80182C10(s32 a0) {
    extern s32 func_800133BC(s32 a0, s32 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern u8 D_8018C60C[];
    extern u8 D_80126B5C;

    s32 v1;
    s32 v0;

    v1 = func_800133BC((s32)&D_8018C60C, (s32)&D_80126B5C);
    if (v1 < 0x40) {
        v1 = 0x7F;
    } else if (v1 < 0x140) {
        v1 = 0x7F - ((v1 - 0x40) >> 1);
    } else {
        v1 = 0;
    }
    if (*(s16 *)(a0 + 0x84) != 0) {
        if ((v1 << 0x10) != 0) {
            func_8002D4C8(0xB6A, (v1 | 0x1000) & 0xFFFF);
        } else {
            func_8002D4C8(0xB6A, 0x1000);
            *(s16 *)(a0 + 0x84) = 0;
        }
    } else if ((v1 << 0x10) != 0) {
        func_8002D4C8(0xB6A, (v1 | 0x1000) & 0xFFFF);
        *(s16 *)(a0 + 0x84) = 1;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);

extern int D_8018C614[];
extern void *D_8018C65C[];
extern unsigned char D_8018C63C[];

void func_80182CD8(int param_1)
{
    int iVar2;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C810(iVar2, D_8018C614[*(short *)(param_1 + 0x70)]);
        *(int *)(*(int *)(param_1 + 0x20) + 4) |= 0x8040;
        *(int *)(*(int *)(param_1 + 0x20) + 0x28) = 0x1800180;
        if (*(short *)(param_1 + 0x70) < 4) {
            *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
                *(short *)(param_1 + 0x70) * 0x400;
            *(unsigned short *)(param_1 + 0x5c) = 0xCC00;
            *(short *)(param_1 + 0xfe) = 0;
            if (*(short *)(param_1 + 0x70) != 2) {
                *(int *)(param_1 + 0xcc) = func_8012C658(0x26A, 4, param_1);
            }
        } else {
            *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 100) + 0x20) + 0x12);
            *(unsigned char *)(param_1 + 0xc0) = 1;
            *(unsigned short *)(param_1 + 0x5c) = 0x8C00;
            *(short *)(param_1 + 0xae) = -5;
            *(void **)(param_1 + 0xbc) = D_8018C65C;
            *(int *)(param_1 + 0xb4) = 0;
            *(short *)(param_1 + 0xfe) = 1;
            *(int *)(param_1 + 0xc4) |= 2;
        }
        *(unsigned char *)(param_1 + 0x75) = 2;
        *(int *)(param_1 + 0x58) =
            (((int)&D_8018C63C + (*(short *)(param_1 + 0xfe) << 4)) | 0x40000000);
        func_8012AD50(param_1);
    }
    return;
}


void func_80182E38(int param_1)
{
    extern s32 D_80126B58;
    extern s32 D_801AECB0;
    extern unsigned char D_8018C644;
    extern void func_8004978C(s16 *a0, void *a1);
    extern void func_8018325C(s32 a0, void *a1, void *a2);
    extern void func_8012E014(s32 a0);
    extern void func_8012B2CC(s32 a0);

    short *dst;
    char mat[0x20];
    char sv[8];
    int v0;
    int t1;
    int t2;
    unsigned int uVar2;
    int t;

    dst = (short *)&D_80126B58;
    if (*(short *)(param_1 + 0x70) < 4) {
        *(unsigned short *)(sv + 2) = 0;
        *(unsigned short *)(sv + 0) = 0;
        t1 = *(short *)(*(int *)(param_1 + 0x64) + 0x100);
        if (t1 >= -0xd0) {
            v0 = -0x1a0;                          /* retail: -0x1A0 in the j delay slot, jumping PAST the negu */
        } else {
            t = (t1 + 0xc0) * 0x3600;
            v0 = -(((int)t >> 16) + 0x1a0);       /* the negu belongs to the else-arm only */
        }
        *(short *)(sv + 4) = v0;
        func_8004978C((s16 *)(*(int *)(param_1 + 0x20) + 0x10), mat);
        __asm__ __volatile__(
            "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n" "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
            : : "r"(mat) : "$12", "$13", "$14", "memory");
        __asm__ __volatile__("lwc2 $0, 0(%0)\n" "lwc2 $1, 4(%0)\n" : : "r"(sv) : "memory");
        __asm__ __volatile__("nop\n" "nop\n" "mvmva 1, 0, 0, 3, 0\n" : : : "memory");
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 2(%0)\n" "sh $14, 4(%0)\n"
            : : "r"(sv) : "$12", "$13", "$14", "memory");
        *(short *)(param_1 + 6) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 6) + *(unsigned short *)(sv + 0);
        *(short *)(param_1 + 10) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 10) + *(unsigned short *)(sv + 2);
        *(short *)(param_1 + 14) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 14) + *(unsigned short *)(sv + 4);
        t2 = *(short *)(*(int *)(param_1 + 0x64) + 0x100);
        if (t2 != 0 && t2 >= -0x24f) {
            uVar2 = *(unsigned int *)(param_1 + 0x1c);
            *(unsigned int *)(param_1 + 0x1c) = uVar2 + 1;
            if ((uVar2 & 7) == 0) {
                *(short *)(sv + 0) = -0x48;
                *(short *)(sv + 2) = 0;
                *(short *)(sv + 4) = 0x58;
                func_8018325C(param_1, mat, sv);
                *(short *)(sv + 0) = 0x48;
                func_8018325C(param_1, mat, sv);
            }
        }
    } else {
        *(short *)(param_1 + 6) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 6);
        *(short *)(param_1 + 10) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 10);
        *(short *)(param_1 + 14) = *(unsigned short *)(*(int *)(param_1 + 0x64) + 14);
    }
    if (D_801AECB0 == 0 && *(unsigned char *)(param_1 + 0x74) != 0) {
        func_8012E014(param_1);
        *(dst + 5) =
            (*(unsigned short *)(param_1 + 10) +
             *(unsigned short *)(&D_8018C644 + (*(short *)(param_1 + 0xfe) << 4))) - 1;
    } else {
        func_8012B2CC(param_1);
    }
}



extern void (*D_8018C66C[])(void);

void func_80183088(void *a0) {
    D_8018C66C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801830C4(int param_1)
{
    extern s32 func_8012C588(s32 a0, s32 a1);

    int v0;

    *(unsigned short *)(param_1 + 0x5c) =
        *(unsigned short *)(param_1 + 0x5c) | 0x4000;
    *(short *)(param_1 + 0xae) = -1;
    *(unsigned char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    func_8012C588(0x271, param_1);
    v0 = *(int *)(*(int *)(param_1 + 0x64) + 0x64);
    *(short *)(v0 + 0x102) = *(short *)(v0 + 0x102) - 1;
}


void func_80183130(void *param_1)
{
    extern void func_8001C924(void *a0, s32 *a1);
    extern s32 *D_8018C628[];

    void *cur = param_1;
    s32 mask;

    func_8001C924(*(void **)((s32)cur + 0x20),
                  D_8018C628[*(s16 *)((s32)cur + 0x70)]);
    mask = 0xFFFF7FFF;
    *(s32 *)(*(s32 *)((s32)cur + 0x20) + 0x4) &= mask;

    cur = *(void **)((s32)cur + 0xCC);
    {
        s32 **tbl = D_8018C628;

        if (cur != 0) {
            func_8001C924(*(void **)((s32)cur + 0x20),
                          tbl[*(s16 *)((s32)cur + 0x70)]);
            *(s32 *)(*(s32 *)((s32)cur + 0x20) + 0x4) &= mask;
        }
    }
}


void func_801831E4(s32 *param_1)
{
    s32 t;
    s32 i;

    i = 0;
    param_1 = (s32 *)((s32)param_1 + 0xCC);
    do {
        if (*param_1 != 0) {
            *(s32 *)(*(s32 *)(*param_1 + 0x20) + 4) |= 0x8000;
            t = *(s32 *)(*param_1 + 0xCC);
            if (t != 0) {
                *(s32 *)(*(s32 *)(t + 0x20) + 4) |= 0x8000;
            }
        }
        i++;
        param_1++;
    } while (i < 4);
}


#define gte_SetRotMatrix(r0) __asm__ volatile ( \
    "lw $12, 0( %0 );"                          \
    "lw $13, 4( %0 );"                          \
    "ctc2 $12, $0;"                             \
    "ctc2 $13, $1;"                             \
    "lw $12, 8( %0 );"                          \
    "lw $13, 12( %0 );"                         \
    "lw $14, 16( %0 );"                         \
    "ctc2 $12, $2;"                             \
    "ctc2 $13, $3;"                             \
    "ctc2 $14, $4"                              \
    :                                           \
    : "r"( r0 )                                 \
    : "$12", "$13", "$14" )
#define gte_ldv0(r0) __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n"                     \
    "lwc2 $1, 4(%0)\n"                     \
    : : "r"(r0) : "memory")
#define gte_rtv0() __asm__ __volatile__(   \
    "nop\n"                                \
    "nop\n"                                \
    "mvmva 1, 0, 0, 3, 0\n"                \
    : : : "memory")
#define gte_stsv(r0) __asm__ __volatile__( \
    "mfc2 $12, $9\n"                       \
    "mfc2 $13, $10\n"                      \
    "mfc2 $14, $11\n"                      \
    "sh $12, 0(%0)\n"                      \
    "sh $13, 2(%0)\n"                      \
    "sh $14, 4(%0)\n"                      \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

extern s32 func_80132EF4(s32 a0, s32 a1);

void func_8018325C(s32 a0, void *a1, void *a2)
{
    s32 rec;
    u16 out[4];

    rec = func_80132EF4(a0, 0x22);
    if (rec != 0) {
        *(u16 *)(rec + 0x34) = 0x3002;
        gte_SetRotMatrix(a1);
        gte_ldv0(a2);
        gte_rtv0();
        gte_stsv(out);
        *(u16 *)(rec + 0x6) = *(u16 *)(rec + 0x6) + out[0];
        *(u16 *)(rec + 0xA) = *(u16 *)(rec + 0xA) + out[1];
        *(u16 *)(rec + 0xE) = *(u16 *)(rec + 0xE) + out[2];
    }
}


extern void func_80133298(s32 *arg);

void func_80183338(void *a0) {
    extern void (*D_8018C69C[])(void *);
    if (*(u8 *)((s32)a0 + 0x74)) {
        func_80133298((s32 *)a0);
    }
    D_8018C69C[*(u16 *)((s32)a0 + 0x2)](a0);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183398);


extern void (*D_8018C734[])(void);

void func_80183574(void *a0) {
    D_8018C734[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801835B0);


extern void (*D_8018C7FC[])(void);

void func_80183638(void *a0) {
    D_8018C7FC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s16 D_801AECB4;
extern void (*D_8018C744[])(void *);

void func_80183674(void *a0) {
    s32 a1 = *(s32 *)&D_801AECB4;
    if (a1 != 0) {
        *(u16 *)((s32)a0 + 0) = *(u16 *)(a1 + 6);
        *(u16 *)((s32)a0 + 4) = *(u16 *)(a1 + 0xE);
        *(u16 *)((s32)a0 + 2) = *(u16 *)(a1 + 0xA)
            + *(u16 *)((s32)D_8018C744 + (*(s16 *)(a1 + 0x70) << 4)) - 8;
    } else {
        *(u16 *)((s32)a0 + 4) = 0;
        *(u16 *)((s32)a0 + 2) = 0;
        *(u16 *)((s32)a0 + 0) = 0;
    }
}


extern void (*D_8018C94C[])(void);

void func_801836E0(void *a0) {
    D_8018C94C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80182A30(s32 arg0);
extern void func_80182B68(s32 arg0);

void func_8018371C(s32 a0)
{
    s32 v0;
    u16 v1;
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C2C4(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern s32 D_801AECB0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C2C4(v0);
    v1 = *(u16 *)(a0 + 0xA);
    *(u16 *)(a0 + 0x100) = 0;
    *(u16 *)(a0 + 0xFE) = v1;
    func_80182A30(a0);
    func_80182B68(a0);
    D_801AECB0 = 0;
    func_8012AD50((void *)a0);
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"

extern MatEntry D_8018C558[];
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_801828DC(void);

void func_80183790(void *param_1)
{
    if (*(s16 *)((s32)param_1 + 0x102) == 3) {
        func_80178B18((s32)param_1, (s32)D_8018C558);
        ((void (*)(s32))func_801828DC)((s32)param_1);
    }
}


extern void func_80178D18(void);

void func_801837DC(void *a0) {
    if (func_80178970() != 0) {
        ((void (*)(void *))func_80178D18)(a0);
        func_801828FC(a0);
    }
}


/*
 * func_8018381C — actor update gate.
 * Runs the table swap + state entry only while the actor is idle (+0x102 == 0)
 * and the global mode word is anything except 2/3 (sltiu range check).
 */
void func_8018381C(void *param_1)
{
    extern s32 D_80126B58;
    extern void (*D_8018C5A0[])(void);

    if ((*(s16 *)((s32)param_1 + 0x102) == 0) && ((u32)(*(u16 *)&D_80126B58 - 2) >= 2)) {
        func_80178B18((s32)param_1, (s32)D_8018C5A0);
        func_8018291C((s32)param_1);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern s32 D_801AECB0;
extern void func_801831E4(s32*);
extern void func_80182A90(s32*);

void func_80183884(s32 arg0) {
    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (func_80178970() == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)(arg0);
        ((s32 (*)(s32))func_801831E4)(arg0);
        D_801AECB0 = 1;
        ((void (*)(s32))func_80182A90)(arg0);
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern u8 D_801A7DB0[];
extern u16 D_8018C674[];
extern u16 D_8018C676[];
extern u16 D_8018C678[];
extern u16 D_8018C67A[];
extern u8 D_8018C68C[];

void func_801838FC(s32 a0)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C810(v0, (s32)D_801A7DB0);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x8040;
    *(u16 *)(a0 + 0x6) = D_8018C674[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(a0 + 0xA) = D_8018C676[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(a0 + 0xE) = D_8018C678[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = D_8018C67A[*(s16 *)(a0 + 0x70) * 4];
    *(s32 *)(a0 + 0x58) = (s32)D_8018C68C | 0x20000000;
    *(u8 *)(a0 + 0x75) = 2;
    *(u16 *)(a0 + 0x5C) = 0xCC00;
    func_8012AD50((void *)a0);
}


void func_80183A1C(s32 a0) {
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(u8 *)(a0 + 0x74) != 0) {
            if ((func_8014CB2C() & 0x7FFFFFFF) == 2) {
                *(s32 *)(a0 + 0x1C) = 4;
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            }
        }
        break;
    case 1:
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x800;
            if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) == 0) {
                *(u16 *)(*(s32 *)(a0 + 0x64) + 0x102) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x102) + 1;
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 1;
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            } else {
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) - 1;
            }
        }
        break;
    case 2:
        break;
    case 3:
        break;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_80182384(void);
extern void func_8018242C(void);
extern void func_801835B0(void *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_8018C72C[];

void func_80183B20(s32 a0)
{
    s32 v0;
    u16 v1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C2C4(v0);
    if (*(s16 *)(a0 + 0x70) == 0) {
        func_80182384();
        *(s32 *)(a0 + 0x1C) = 0xA0;
    } else {
        func_8018242C();
    }
    v1 = *(u16 *)(a0 + 0xA);
    *(u16 *)(a0 + 0x100) = 0;
    *(u16 *)(a0 + 0xFE) = v1;
    func_801835B0((void *)a0, D_8018C72C[*(s16 *)(a0 + 0x70)]);
    func_8012AD50((void *)a0);
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s32 func_8012AD50(void *a0);

extern u8 D_8018C73C[];
extern u16 D_8018C7BC[];
extern u16 D_8018C7BE[];
extern u16 D_8018C7C0[];

void func_80183BC4(s32 a0)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C2C4(v0);
    *(u8 *)(a0 + 0x75) = 2;
    *(u16 *)(a0 + 0x5C) = 0xCC00;
    *(s32 *)(a0 + 0x58) = ((s32)D_8018C73C + *(s16 *)(a0 + 0x70) * 16) | 0x50000000;
    *(u16 *)(a0 + 0x6) = D_8018C7BC[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(a0 + 0xA) = D_8018C7BE[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(a0 + 0xE) = D_8018C7C0[*(s16 *)(a0 + 0x70) * 4];
    *(u16 *)(a0 + 0xFC) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0xFC);
    func_8012AD50((void *)a0);
}


typedef struct { s16 m[16]; } Mat_80183C9C;

extern void func_8004978C(s16 *a0, void *a1);
extern u16 D_8018C7BC[];
extern void func_8012E014(s32 a0);

void func_80183C9C(void *a0)
{
    Mat_80183C9C mat;
    u16 res[3];
    s32 self = (s32)a0;

    *(s16 *)(*(s32 *)(self + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 0x12) + *(u16 *)(self + 0xFC);

    func_8004978C((s16 *)(*(s32 *)(self + 0x20) + 0x10), &mat);

    __asm__ __volatile__(
        "lw $12, 0(%0)\n"
        "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n"
        "lw $13, 12(%0)\n"
        "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        : : "r"(&mat) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__("lwc2 $0, 0(%0)\nlwc2 $1, 4(%0)"
                         : : "r"(&D_8018C7BC[*(s16 *)(self + 0x70) * 4]) : "memory");
    __asm__ __volatile__("nop\nnop\nmvmva 1, 0, 0, 3, 0" : : : "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\nmfc2 $13, $10\nmfc2 $14, $11\nsh $12, 0(%0)\nsh $13, 2(%0)\nsh $14, 4(%0)"
        : : "r"(res) : "$12", "$13", "$14", "memory");

    *(s16 *)(self + 0x6) = *(u16 *)(*(s32 *)(self + 0x64) + 0x6) + res[0];
    *(s16 *)(self + 0xA) = *(u16 *)(*(s32 *)(self + 0x64) + 0xA) + res[1];
    *(s16 *)(self + 0xE) = *(u16 *)(*(s32 *)(self + 0x64) + 0xE) + res[2];

    if (*(u8 *)(self + 0x74) != 0) {
        func_8012E014(self);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern u8 D_8018C804;
extern s32 D_8018C8C4;

void func_80183DAC(void *arg0)
{
    register void *self __asm__("$16") = arg0;
    s32 h;

    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)self + 0x20) = h;
    if (h == 0) {
        func_8012CAE4(self);
    } else {
        func_8001CA1C(h, (s32)&D_8018C804);
        func_8012A828((s32)self, &D_8018C8C4);
        *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x18) = 0x2800;
        *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x1A) = 0x2800;
        *(u32 *)(*(s32 *)((s32)self + 0x20) + 4) |= 0x50000000;
        func_8002D4C8(0x92B, 0);
        func_8012AD50(self);
    }
}


typedef struct { s32 w[8]; } Mat32L;

void func_80183E48(void *a0)
{
    extern s32 D_800AE620;
    extern void CompMatrix(void *a0, void *a1, void *a2);

    Mat32L m; /* sp+0x10 */
    void *mp;

    m = *(Mat32L *)&D_800AE620;
    mp = &m;
    *(s32 *)((s32)mp + 0x18) = -0xF8;
    *(s32 *)((s32)mp + 0x14) = 0;
    *(s32 *)((s32)mp + 0x1C) = 8;

    CompMatrix((void *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34),
               mp,
               (void *)(*(s32 *)((s32)a0 + 0x20) + 0x34));

    *(volatile u16 *)(*(volatile s32 *)((s32)a0 + 0x20) + 0x2C) |= 1;
}



extern void (*D_8018C964[])(void);

void func_80183EFC(void *a0) {
    D_8018C964[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80184870();
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801AB54C[];
extern u8 D_8018C970[];
extern s32 D_801AECB8[];
extern u8 D_8018C97C[];
extern u8 D_8018C9CC[];
extern s8 D_8018C9AC[];
extern void (*D_8018CAA8[])(void *);

void func_80183F38(void *a0)
{
    register void *self __asm__("$16") = a0;
    register void *obj  __asm__("$17");
    s32 h;
    s32 pad[8];

    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)self + 0x20) = h;
    if (h == 0) {
        goto L_fail;
    }
    if (*(s16 *)((s32)self + 0x70) != 0) {
        goto L_da8;
    }
    func_8001C214(h, (s32)D_801AB54C);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12) = 0x800;
    obj = (void *)((s32 (*)(void))func_8012C194)();
    *(s32 *)((s32)self + 0xCC) = (s32)obj;
    if (obj != 0) {
        goto L_ce4;
    }
L_fail:
    func_8012CAE4(self);
    return;
L_ce4:
    func_8001CB6C((u8 *)obj, (s32)D_8018C970, 0x2F0, 0x138);
    func_80184870(self);
    *(u16 *)((s32)obj + 0x18) = 0x2400;
    *(u16 *)((s32)obj + 0x1A) = 0x1C00;
    *(u16 *)((s32)obj + 0x12) = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
    *(u32 *)((s32)obj + 4) |= 0x51000000;
    *(u8 *)((s32)obj + 0x27) = 0xED;
    func_80128EA8((s32)obj, (s32)D_801AECB8, (s32)D_8018C97C);
    *(u8 *)((s32)self + 0xC0) = 1;
    *(s32 *)((s32)self + 0xBC) = (s32)D_8018C9CC;
    *(s32 *)((s32)self + 0x58) = (s32)D_8018C9AC | 0x40000000;
    *(u16 *)((s32)self + 0x5C) = 0x8000;
    *(s16 *)((s32)self + 0xAE) = -3;
    {
        s32 v0 = *(s32 *)((s32)self + 0xC4);
        u16 v1 = *(u16 *)((s32)self + 0xA);
        *(s32 *)((s32)self + 0xB4) = 0;
        *(u8 *)((s32)self + 0xC1) = 0;
        *(s32 *)((s32)self + 0xC4) = v0 | 2;
        *(u16 *)((s32)self + 0x102) = v1;
        *(u16 *)((s32)self + 0xFE) = v1;
    }
    func_8012AD50(self);
    return;
L_da8:
    func_8001CA1C(h, 0);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)((s32)self + 0x20) + 4) |= 0x71000000;
    *(s32 *)((s32)self + 0x14) = 0xFFFE0000;
    *(s32 *)((s32)self + 0x18) = 0x30000;
    *(u16 *)((s32)self + 0xFC) = 0;
    func_8012A828((s32)self, D_8018CAA8);
    func_8012AD44((s32 *)self, 9);
}


extern void func_8013CABC(void);
extern void func_80184A50(void *a0);
extern int func_8001AAA0(void);
extern void func_8018278C(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_80184398(s32 a0);
extern void func_801842CC(s32 arg0);
extern int func_80178970(void);
extern s32 D_801AECC0;

void func_801840F8(s32 arg0)
{
    s32 t;

    t = *(s32 *)(arg0 + 0x1C);
    if (t == 0x30) {
        func_8013CABC();
    } else if (t == 0x10) {
        func_80184A50((void *)*(s32 *)(arg0 + 0xD0));
    }

    if (*(u16 *)(arg0 + 0x84) & 1) {
        t = *(s32 *)(arg0 + 0x64);
        *(u16 *)(t + 0x6) -= 3;
        t = *(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20);
        *(u16 *)(t + 0x8) -= 3;
        *(u16 *)(arg0 + 0x6) -= 3;
    } else {
        t = *(s32 *)(arg0 + 0x64);
        *(u16 *)(t + 0x6) += 3;
        t = *(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20);
        *(u16 *)(t + 0x8) += 3;
        *(u16 *)(arg0 + 0x6) += 3;
    }

    *(u16 *)(arg0 + 0x84) += 1;
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (((int (*)(int))func_8001AAA0)(0x7B) != 0) {
            *(u16 *)(arg0 + 0x34) += 1;
        }
        break;
    case 1:
        if (D_801AECC0 == 0) {
            D_801AECC0 = ((s32 (*)(void))func_8018278C)();
        }
        break;
    }

    if ((func_8012BEE8(arg0) != 0) && (D_801AECC0 != 0)) {
        func_80184398(arg0);
    } else {
        if (*(s32 *)(arg0 + 0x1C) < 0x48) {
            if ((*(u16 *)(arg0 + 0x84) & 3) == 0) {
                func_801842CC(arg0);
            }
        }
    }

    ((void (*)(s32))func_80178970)(arg0);
}


void func_801842CC(s32 arg0)
{
    s32 s0;
    for (s0 = 0; s0 < 0x49; s0 += 0x18) {
        s32 a1 = func_80132EF4(arg0, 0x22);
        if (a1 == 0)
            continue;
        {
            register s32 v0 __asm__("v0");
            register s32 v1 __asm__("v1");
            register s32 a0 __asm__("a0");
            v0 = *(u16 *)(arg0 + 0x84);
            a0 = *(u16 *)(a1 + 0xE);
            v0 &= 0x4;
            v1 = v0 * 2;
            __asm__("":"=r"(v1):"0"(v1));
            v1 = v1 + v0;
            v1 = s0 + v1;
            v1 = v1 - 0x2A;
            v0 = *(u16 *)(a1 + 0x6);
            a0 += 0x28;
            *(u16 *)(a1 + 0xE) = a0;
            v0 -= v1;
            *(u16 *)(a1 + 0x6) = v0;
            v0 = *(u16 *)(a1 + 0xA);
            v1 = v1 << 16;
            v0 -= 0x20;
            *(u16 *)(a1 + 0xA) = v0;
            v0 = v1 >> 16;
            if (v0 >= 0) {
                v0 = v0 << 7;
            } else {
                v0 = v0 << 7;
                v0 = -v0;
            }
            v0 += 0x1000;
            *(u16 *)(a1 + 0x34) = v0;
            *(s32 *)(a1 + 0x14) = 0xFFFE0000;
            *(s32 *)(a1 + 0x18) = 0x30000;
        }
    }
}


void func_80184398(s32 a0) {

    extern u8 D_8018C9DC[];
    register s32 obj  __asm__("$16");            /* $s0 */
    register s32 self __asm__("$17") = a0;       /* $s1 */
    s32 t0;
    s32 t1;
    s32 t2;

    obj = *(s32 *)(self + 0x20);
    func_8001CA1C(obj, (s32)D_8018C9DC);

    *(u16 *)(self + 0xA) = *(u16 *)(self + 0xA) - 0xA0;
    *(u16 *)(self + 0xE) = *(u16 *)(self + 0xE) + 0x10;
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
    func_801863F4(obj);

    *(u16 *)(obj + 0x5C) = 0;
    func_8012AD44((s32 *)obj, 2);

    t2 = *(s32 *)(self + 0xD0);
    if (t2 != 0) {
        *(u16 *)(t2 + 0x2C) = 0;
        func_80184A5C((void *)t2);
    }

    func_80186E34();
    func_80186E58(self + 4);

    func_8002D4C8(0x920, 0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80184AA8(void *a0);
extern void (*D_8018CAA8[])(void *);

void func_801844AC(s32 a0)
{
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2C00;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3800;
    func_8012A828(a0, D_8018CAA8);
    *(s16 *)((s32)a0 + 0xFC) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    func_8012AD44((s32 *)a0, 4);
    if (*(s32 *)(a0 + 0xD0) != 0) {
        func_80184AA8((void *)*(s32 *)(a0 + 0xD0));
    }
}


extern void func_8012B200(void *arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80184AD4(void *a0);

void func_80184524(void *arg0)
{
    void *a0;

    *(s32 *)((s32)arg0 + 0x1C) = 4;
    func_8012B200(arg0);
    func_8012AD44((s32 *)arg0, 5);
    a0 = *(void **)((s32)arg0 + 0xD0);
    if (a0 != NULL) {
        func_80184AD4(a0);
    }
}


void func_80184578(s32 param_1)
{
    extern void func_80184808(void *arg0);
    extern s8 D_8018C9BC[];
    extern void func_8012AD44(s32 *a0, s16 a1);

    *(s32 *)((s32)param_1 + 0x58) = (s32)&D_8018C9BC;
    func_80184808((void *)param_1);
    func_8012AD44((s32 *)param_1, 6);
}



s32 func_801845B8(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x6;
    }


extern s32 func_801439C0(s32 a0);
extern void func_8012B200(void*);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801292C8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_801845CC(int a0)
{
    register s32 s0 __asm__("$16") = a0;
    u8 *ptr;
    s32 val1;
    s32 val2;
    s32 t2;

    func_801439C0(*(s32 *)(s0 + 0xCC));
    ((void (*)(u8 *))func_8012B200)((u8 *)s0);

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

    func_8002D4C8(0x922, 0);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018467C(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x8);
    }


extern void func_8013CAE8(void);
    void func_8018469C(void) {
        func_8013CAE8();
    }



extern void (*D_8018CC08[])(void);

void func_801846BC(void *a0) {
    D_8018CC08[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_8018CC30[];
extern s32 D_801AECC0;
extern void (*D_8018CB50[])(void);

void func_801846F8(s32 a0) {
    u32 i;
    register s32 ptr __asm__("$3");
    register s32 obj __asm__("$4");
    s16 val;
    register s32 val2 __asm__("$3");

    for (i = 0; i < 8; i++) {
        if (*(u16 *)(a0 + 0x5E) == D_8018CC30[i]) {
            ptr = *(s32 *)(a0 + 0x64);
            val = *(u16 *)(ptr + 6);
            D_801AECC0 = 0;
            val = val + 1;
            *(u16 *)(ptr + 6) = val;
            *(s32 *)(a0 + 0x1C) = 0x50;
            *(u16 *)(a0 + 0x84) = 0;
            *(u16 *)(a0 + 6) = *(u16 *)(a0 + 6) + 1;
            func_8012AD44((s32 *)a0, 2);

            obj = func_80132EF4(a0, 0x59);
            *(s32 *)(a0 + 0xD0) = obj;
            if (obj != 0) {
                *(u16 *)(obj + 6) = *(u16 *)(a0 + 6);
                *(u16 *)(obj + 0xA) = *(u16 *)(a0 + 0xA);
                val2 = *(u16 *)(a0 + 0xE);
                *(s16 *)(obj + 0x2C) = -0xA0;
                *(s32 *)(obj + 0x34) = a0;
                *(u16 *)(obj + 0xE) = val2;
            }

            func_80178B18(a0, (s32)D_8018CB50);

            /* Source order IS emitted order: 0x5C standalone, 0x5E sinks into
             * the jal delay slot; the second 0x5E store sinks into the j. */
            *(u8 *)(a0 + 0xC1) = 0;
            *(u16 *)(a0 + 0x5C) = 0;
            *(u16 *)(a0 + 0x5E) = 0;
            func_8002D4C8(0x91F, 0);
            *(u16 *)(a0 + 0x5E) = 0;
            goto done;
        }
    }

    *(u16 *)(a0 + 0x5E) = 0;
done:
    func_8002D4C8(0x426, 0);
}


void func_80184808(void *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


void func_80184818(s32 param_1)
{
    func_8012AD80(param_1);
    if (0x14000 < *(s32 *)(param_1 + 0x14))
        *(s32 *)(param_1 + 0x48) = -0x1400;
    else if (*(s32 *)(param_1 + 0x14) < -0x14000)
        *(s32 *)(param_1 + 0x48) = 0x1400;
}


void func_80184870(s32 arg0) {
    s32 *p = *(s32 **)((s32)arg0 + 0xcc);
    *(u16 *)((s32)p + 0x8) = *(u16 *)((s32)arg0 + 0x6);
    *(s16 *)((s32)p + 0xa) = *(u16 *)((s32)arg0 + 0xa) - 0xe0;
    *(s16 *)((s32)p + 0xc) = *(u16 *)((s32)arg0 + 0xe) + 0x8;
}




int func_801848A4(int a0, void* a1)
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

    result = func_80184940((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = s0[7];
        stack_buf[6] = v0;
        stack_buf[2] = v0;
        result = func_80184940((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}


void func_80184940(s32 param_1, s32 param_2, s32 param_3)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    s32 sp10[2];
    s32 sp18[2];

    func_8012F214(param_1, param_2, (s32)&sp10[0]);
    func_8012F214(param_1, param_3, (s32)&sp18[0]);
    func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&sp10[0], (s32)&sp18[0]);
}


extern void func_8017BEBC(void);
    void func_801849A8(void) {
        func_8017BEBC();
    }


extern s32 func_8017BFA0();
    void func_801849C8(void) {
        func_8017BFA0();
    }


extern s32 func_8018183C(void);
    void func_801849E8(void) {
        func_8018183C();
    }


extern void func_80181918(void);
    void func_80184A08(void) {
        func_80181918();
    }


extern void func_800D1724(s32);
void func_80184A28(void) {

    extern s32 D_8018BFF0;
    ((s32 (*)(s32 *))func_800D1724)(&D_8018BFF0);
}


void func_80184A50(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }


void func_80184A5C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x3;
    }


extern u8 D_801AECC5;

void func_80184A68(void) {
    register u8 *a0 __asm__("a0");
    a0 = &D_801AECC5;
    __asm__("" : "=r"(a0) : "0"(a0));
    if (a0[0] < 0xF8U) {
        a0[0] += 4;
        a0[-1] += 6;
        a0[1] += 4;
    }
}



extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80184AA8(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x4;
        func_8002D4C8(0x921, 0);
    }


void func_80184AD4(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0;
    }



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_80184B30();
extern void (*D_8018CC58[])(int);

void func_80184AE4(int param_1)
{
    ((void (*)(void))func_80184B30)();
    D_8018CC58[*(unsigned short *)(param_1 + 2)](param_1);
}


extern void func_80129350(s32 *a0, s32 a1);
extern void func_80133060(s32 *a0, s32 a1, s32 a2);

void func_80184B30(s32 *a0) {
    s32 *s0;
    s32 a1;

    s0 = a0;
    a1 = *(s32 *)((u8 *)s0 + 0x34);
    func_80129350(s0, a1);

    a1 = (s32)((u8 *)s0 + 0x4);
    *(s16 *)((u8 *)s0 + 0xA) = *(u16 *)((u8 *)s0 + 0xA) + *(u16 *)((u8 *)s0 + 0x2C);
    func_80133060((s32 *)((u8 *)s0 + 0x4), a1, -0x180);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184B80);

extern s16 func_801825D8(void);

void func_80184C24(void *arg0) {
    s16 ret = func_801825D8();
    *(u16 *)((s32)arg0 + 0xA) = *(u16 *)((s32)arg0 + 0xFE) + ret - 0x131;
}


void func_80184C60(void) {
}

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184C68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184CBC);

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern int func_80178970(void);
void func_80184524(void *arg0);

void func_80184D68(s32 arg0)
{
    if (func_8012BEE8(arg0) == 0) {
        if ((*(u32 *)(arg0 + 0x1C) & 3) == 0) {
            func_8012C658(0x2BB, 1, arg0);
        }
    }
    if (*(s16 *)(arg0 + 0x98) == 0) {
        func_80184524((void *)arg0);
    }
    ((void (*)(s32))func_80178970)(arg0);
}


extern int func_80178970(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_80184578(s32 a0);

    void func_80184DD8(s32 arg0) {
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
                func_80184578(arg0);
            }
        }
        ((void (*)(s32))func_80178970)(arg0);
    }


    extern int func_80178970(void);
    extern void func_80184818(int a0);
    extern int func_801848A4(int a0, void *a1);
    extern void func_801845CC();
    extern char D_8018C9BC[];
    void func_80184E68(int param_1)
    {
        ((void (*)(void))func_80178970)();
        func_80184818(param_1);
        if (func_801848A4(param_1, (void *)&D_8018C9BC) != 0) {
            func_801845CC(param_1);
        }
    }


extern void func_8012AD80(s32 a0);
extern void func_8018467C(void *arg0);
extern int func_80178970(void);

void func_80184EB8(s32 a0) {
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
    } else {
        func_8018467C(a0);
    }

    ((void (*)(s32))func_80178970)(a0);
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern s16 D_801B20D8;

void func_80184F68(s32 arg0) {
    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (func_80178970() == 0) {
            return;
        }
        if (D_801B20D8 != 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)(arg0);
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80184FD8(void *param_1) {
    (*(u16 *)((char *)param_1 + 0xFC))++;
    func_8012AD80(param_1);
    if (*(s16 *)((char *)param_1 + 0x98) == 0) {
        func_8012C218(param_1);
    }
}


extern Block4 D_801AD2DC;
extern Block4 D_801AECC8;
extern u8 D_801AECC4;
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);

void func_80185028(a0)
s32 a0;
{
    register u8 *s0 __asm__("$16");
    register s32 *s1 __asm__("$17");
    s32 *v1;
    s32 *a0_ptr;
    s8 pad[32];  

    s1 = (s32 *)a0;
    s0 = (u8 *)&D_801AECC4;

    
    func_8001CD9C(s1[8], (s32 *)s0);  

    
    func_800233CC(s0, 0x80);

    
    *(Block4 *)s0 = D_801AD2DC;

    
    D_801AECC8 = D_801AD2DC;

    
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x18) = 0x800;

    
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x1A) = 0x1000;

    
    a0_ptr = s1[8];
    *(s32 *)((s8 *)a0_ptr + 0x4) |= 0x50000000;

    
    *(s16 *)((s8 *)s1 + 0x2) = 1;

    (void)pad;  
}


extern u8 D_801AECC4;
extern u8 D_801AECC5;
extern u8 D_801AECC6;

void func_801850E4(void) {
    u8 *p = &D_801AECC4;
    if (*p < 0x60U) {
        *p += 4;
    }
    if (D_801AECC5 < 0xC0U) {
        D_801AECC5 += 4;
    }
    if (D_801AECC6 < 0xC0U) {
        D_801AECC6 += 4;
    }
}


extern void func_80184A68(void);
void func_8018514C(void) {
    func_80184A68();
}


extern void func_80184A68(void);

void func_8018516C(int param_1) {
    register int p __asm__("$4");
    p = *(int *)(param_1 + 0x20);
    if (*(short *)(p + 0x18) < 0x5000) {
        *(short *)(p + 0x18) = *(short *)(p + 0x18) + 0x800;
    }
    if (*(short *)(p + 0x1a) < 0x5000) {
        *(short *)(p + 0x1a) = *(short *)(p + 0x1a) + 0x800;
    }
    func_80184A68();
}


extern u8 D_801AECC4;
extern u8 D_801AECC5;
extern u8 D_801AECC6;

void func_801851CC(s32 arg0) {
    u8 *q;
    s32 p = *(s32 *)(arg0 + 0x20);
    if (*(s16 *)(p + 0x18) >= 0x801) {
        *(s16 *)(p + 0x18) = *(s16 *)(p + 0x18) - 0x200;
    }
    if (*(s16 *)(p + 0x1A) >= 0x801) {
        *(s16 *)(p + 0x1A) = *(s16 *)(p + 0x1A) - 0x200;
    }
    q = &D_801AECC5;
    if (*q >= 0xC1) {
        *q -= 4;
        D_801AECC4 -= 6;
        D_801AECC6 -= 4;
    }
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185264);


extern void (*D_8018CC70[])(void);

void func_80185318(void *a0) {
    D_8018CC70[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185354);

extern u8 D_801AED08[];
extern void func_80185520(void*);
extern void func_8018562C();
extern void func_80185734(s32 *a0);
extern void func_80185764(s32 a0, s32 *a1);
extern void func_80185814(u16*, s16*);
extern s32 rand(void);

void func_801853F0(s32 arg0)
{
    register s32 i __asm__("$17");
    register s32 off __asm__("$18");
    u8 *e;

    i = 0;
    off = 0;
    while (i < 200) {
        e = D_801AED08 + off;
        if (*(s32 *)(e + 0x1C) == 0) {
            if (*(s32 *)(e + 0x24) != 0) {
                *(u16 *)(e + 0xA) += 0x80;
                if (*(s32 *)(e + 0x20) == 0) {
                    func_80185734((s32 *)e);
                } else {
                    (*(s32 *)(e + 0x20))--;
                }
                (*(s32 *)(e + 0x24))--;
                goto call_562c;
            } else {
                func_80185734((s32 *)e);
                if (*(u8 *)(e + 0x18) == 0) {
                    if ((rand() & 3) == 0) {
                        func_80185764(arg0, e);
                    }
                    ((s32 (*)(s32 *, s32))func_80185520)((s32 *)e, i);
                    ((void (*)(s32, s32 *))func_80185814)(arg0, e);
                } else {
call_562c:
                    func_8018562C(arg0, e);
                }
            }
            i++;
        } else {
            (*(s32 *)(e + 0x1C))--;
            i++;
        }
        off += 0x2C;
    }
}


void func_80185520(void *a0) {
    s32 s0;
    s32 s1;
    s32 t;
    s32 idx;

    s0 = rand();
    s1 = rand();
    t = rand();
    idx = ((s0 & 3) << 10) + (s1 & 3) * 341 + (t & 0xF) * 11;
    __asm__ __volatile__("");
    *(u16 *)((s32)a0 + 0x14) = 0x2E0;
    *(u16 *)((s32)a0 + 0x0C) = 0x2E0;
    *(u16 *)((s32)a0 + 0x02) = idx;
    *(u16 *)((s32)a0 + 0x04) = 0;
    *(u16 *)((s32)a0 + 0x00) = 0;
    *(u16 *)((s32)a0 + 0x12) = 0;
    *(u16 *)((s32)a0 + 0x0A) = 0;
    *(u16 *)((s32)a0 + 0x10) = 0;
    *(u16 *)((s32)a0 + 0x08) = 0;
    *(s32 *)((s32)a0 + 0x20) = 8;
    *(s32 *)((s32)a0 + 0x24) = (rand() % 8) + 0x10;
    *(s32 *)((s32)a0 + 0x1C) = (rand() & 3) + (rand() & 3);
    *(s32 *)((s32)a0 + 0x28) = 0;
    *(s32 *)((s32)a0 + 0x18) = 0x202020;
}


typedef struct {
    u16 h0, h1, h2, h3;
} Q_8018562C;

typedef struct {
    Q_8018562C rot;
    s32 t0, t1, t2, t3;
} ROW_8018562C;

typedef struct {
    Q_8018562C head;
    Q_8018562C tail;
    ROW_8018562C row;
} BIG_8018562C;

typedef struct {
    s16 m[10];
    s32 x;
    s32 y;
    s32 z;
} MB_8018562C;

void func_8018562C(void *a0, void *a1) {
    BIG_8018562C b;
    MB_8018562C mb;
    extern void func_80017D98(void *);
    extern void func_80017DF8(void *, void *);
    extern void func_800173BC(void *, void *);

    func_80017D98(mb.m);
    func_80017DF8(a1, mb.m);
    mb.x = *(s16 *)((s8 *)a0 + 6);
    mb.y = *(s16 *)((s8 *)a0 + 0xA);
    mb.z = *(s16 *)((s8 *)a0 + 0xE);
    b.tail = *(Q_8018562C *)((s8 *)a1 + 8);
    b.head = b.tail;
    b.head.h0 = b.head.h0 - 0x20;
    b.tail.h0 = b.tail.h0 + 0x20;
    b.row.rot = *(Q_8018562C *)((s8 *)a1 + 0x10);
    b.row.t1 = 0;
    b.row.t0 = 0;
    b.row.t2 = *(s32 *)((s8 *)a1 + 0x18);
    b.row.t3 = 0x50000000;
    func_800173BC(&b, mb.m);
}


















void func_80185734(s32 *a0)
{
  int new_var;
  s32 v = *((u8 *) (((s32) a0) + 0x18));
  v -= 4;
  if (v < 0)
  {
    v = 0;
  }
  new_var = (v = ((v << 16) | (v << 8)) | v);
  *((s32 *) (((s32) a0) + 0x18)) = new_var;
}

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185764);

extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern int func_80188160(short *pos, int a1, int a2);
extern s32 D_8018CC8C;
extern void *D_8018CC9C;
extern void *D_8018CC98;

void func_80185814(u16 *a0, s16 *a1)
{
    int ret;
    s32 tmp[4];
    s32 dead[8];
    u16 buf[4];

    func_800139C8(a1[1], a1 + 8, buf);
    buf[0] = buf[0] + a0[3];
    buf[1] = buf[1] + a0[5];
    buf[2] = buf[2] + a0[7];
    buf[3] = 0x1E;
    func_8001382C(a1[1], &D_8018CC8C, tmp);
    tmp[3] = (s32)D_8018CC98;
    ret = func_80188160(buf, tmp, (int)D_8018CC9C);
    if (ret != 0) {
        *(s16 *)(*(s32 *)(ret + 0x20) + 0x18) = 0x400;
    }
}


void func_801858E8(void *arg0)
{
    extern void func_80185A5C(void *a0, void *a1);
    extern u8 D_801B0F68[];

    s32 i = 0;
    u8 *p = D_801B0F68;

    while (i < 0x50) {
        if (*(s32 *)(p + 0x24) == 0) {
            func_80185A5C(p, arg0);
            break;
        }
        i++;
        p += 0x2C;
    }
}



extern void (*D_8018CCA0[])(void);

void func_8018593C(void *a0) {
    D_8018CCA0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801B0F8C;
extern s32 func_8012AD50(void *a0);

void func_80185978(void) {
    s32 i = 0xD94;
    do {
        *(s32 *)((s32)&D_801B0F8C + i) = 0;
        i -= 0x2C;
    } while (i >= 0);
    ((void (*)(void))func_8012AD50)();
}


extern u8 D_801B0F68[];
extern void func_80185B04(void *a0, void *a1);

void func_801859B4(void *a0) {
    s32 i;

    for (i = 0; i < 0x50; i++) {
        u8 *s0 = D_801B0F68 + i * 0x2C;
        if (*(s32 *)(s0 + 0x24) != 0) {
            *(u16 *)(s0 + 0xA) += 0x40;
            if (*(s32 *)(s0 + 0x20) == 0) {
                *(u16 *)(s0 + 0x12) += 0x40;
            } else {
                (*(s32 *)(s0 + 0x20))--;
            }
            (*(s32 *)(s0 + 0x24))--;
            func_80185B04(a0, s0);
        }
    }
}



extern s32 rand(void);

void func_80185A5C(s32 param_1, s32 param_2)
{
    s32 r;

    *(s32 *)(param_1 + 0x20) = 8;
    r = rand();
    *(s32 *)(param_1 + 0x24) = (r % 8) + 0x10;
    *(s32 *)(param_1 + 0x18) = 0x101010;
    *(Blk8 *)(param_1 + 8) = *(Blk8 *)param_2;
    *(Blk8 *)(param_1 + 0x10) = *(Blk8 *)param_2;
}


typedef struct {
    u16 h0, h1, h2, h3;
} QB_80185B04;

typedef struct {
    s16 m[10];
    s32 x;
    s32 y;
    s32 z;
} MB_80185B04;

typedef struct {
    QB_80185B04 a;
    QB_80185B04 b;
    s32 c;
    s32 d;
    s32 e;
} BIG_80185B04;

void func_80185B04(void *a0, void *a1)
{
    BIG_80185B04 b;
    MB_80185B04 mb;
    extern void func_80017D98(void *);
    extern void aFunc80016A5C(void *arg0, void *arg1) __asm__("func_80016A5C");

    func_80017D98(mb.m);
    mb.z = 0;
    mb.y = 0;
    mb.x = 0;
    b.a = *(QB_80185B04 *)((s8 *)a1 + 8);
    b.b = *(QB_80185B04 *)((s8 *)a1 + 0x10);
    b.d = 0;
    b.c = *(s32 *)((s8 *)a1 + 0x18);
    b.e = 0x50000000;
    aFunc80016A5C(&b, mb.m);
}



extern void (*D_8018CD04[])(void);

void func_80185BA8(void *a0) {
    D_8018CD04[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C194(void);
extern void func_8001CEC0(s32 a0, void *a1);
extern s32 func_8012AD50(void *a0);

extern int D_8018CCCC;

void func_80185BE4(int param_1)
{
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C194)();
    if (v0 != 0) {
        ((void (*)(s32, void *))func_8001CEC0)(v0, &D_8018CCCC);
        *(short *)(v0 + 0x2c) = 1;
        ((s32 (*)(void *))func_8012AD50)((void *)param_1);
    }
}


void func_80185C40(void *a0) {
        *(u16 *)((s32)a0 + 0xA) += 1;
        if (*(s16 *)((s32)a0 + 0xA) >= 0x101) {
            *(u16 *)((s32)a0 + 0xA) = 0x100;
        }
    }



extern void (*D_8018CE0C[])(void);

void func_80185C70(void *a0) {
    D_8018CE0C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800233CC(void *a0, u16 a1);
extern s32 func_8012AD50(void *a0);
extern void func_801878A8();

void func_80185CAC(void *param_1)
{
    extern u8 D_8018CD0C[];
    extern s32 D_801B2150;
    extern void (*D_8018CDCC[])(void);

    func_800233CC(D_8018CD0C, 0x20);
    func_800233CC(D_8018CD0C + 0x40, 0x20);
    func_800233CC(D_8018CD0C + 0x80, 0x20);
    func_801878A8(&D_801B2150, D_8018CDCC);
    func_8012AD50(param_1);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185D24);

extern s32 func_80187754(s32 *a0);
void func_80185D7C(void) {

    extern s32 D_801B2150;
    func_80187754(&D_801B2150);
}



extern void (*D_8018CE14[])(void);

void func_80185DA4(void *a0) {
    D_8018CE14[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80185DE0(int param_1)
{
    extern void func_8012C1B8(void);
    extern void func_8001C810(s32 a0, s32 a1);
    extern s32 func_8012AD50(void *a0);
    extern u8 D_801AA1C8[];

    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 != 0) {
        func_8001C810(v0, (s32)D_801AA1C8);
        *(int *)(v0 + 4) |= 0x50000000;
        ((s32 (*)(void *))func_8012AD50)((void *)param_1);
    }
}


void func_80185E44(void) {
}


extern void (*D_8018CE1C[])(void);

void func_80185E4C(void *a0) {
    D_8018CE1C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_80185E88(u8 *a0) {
        *(s16 *)(a0 + 0xFC) = 0;
        *(u16 *)(a0 + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


extern s16 D_800B9AB8[];

void func_80185EB4(void *a0) {
    u16 var;
    var = *(u16 *)((s32)a0 + 0xFC);
    *(u16 *)((s32)a0 + 0xFC) = var + 1;
    *(u16 *)&D_800B9AB8[0] += var;
}



s32 func_80185EDC(void) {
    return 122;
}



/* func_80185EE4 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_80185F48((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_80185F48();

void func_80185EE4(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_80185F48)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}



void func_80185F48(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_80186348(s0);
    sin_val = func_8018628C(s0);

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



void func_801860A8(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_80186348(r[0] & 0xFFF);
    sx = func_8018628C(r[0] & 0xFFF);
    cy = func_80186348(r[1] & 0xFFF);
    sy = func_8018628C(r[1] & 0xFFF);
    cz = func_80186348(r[2] & 0xFFF);
    sz = func_8018628C(r[2] & 0xFFF);

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



/* func_8018628C — quadrant-folded sine lookup over a 0x400-entry u16 table.
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
 * Q2's base is D_801A91D0 == D_801AA1D0 - 0x1000: gcc folded the `- 0x800`
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


s16 func_8018628C(u32 a0)
{

    extern u16 D_801AA1D0[];
    if (a0 < 0x400) {
        return D_801AA1D0[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801AA1D0[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801AA1D0[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801AA1D0[0xFFF - a0];
    }
}



/* func_80186348 — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801AA1D0); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801AA1D0)[a - 0x400]  ->  base ((s16 *)D_801AA1D0)-0x800 = D_801A99D0, index a*2
 *   ((s16 *)D_801AA1D0)[a - 0xC00]  ->  base ((s16 *)D_801AA1D0)-0x1800 = D_801A89D0, index a*2
 * so no extra externs are needed for D_801A99D0 / D_801A89D0.
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


s32 func_80186348(u32 a0v)
{

    extern u16 D_801AA1D0[];
    if (a0v < 0x400) {
        return ((s16 *)D_801AA1D0)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801AA1D0)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801AA1D0)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801AA1D0)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}



extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern Rec8_8018A390_80186468 D_801AA9D0[];

void func_801863F4(void *a0)
{
    s32 i;

    for (i = 0; (s16)D_801AA9D0[i].x != 0; i++) {
        func_8012C658(0x10D, i, (s32)a0);
    }
}



/* func_80186468 — allocates a GTE-projection slot, seeds a random spread
 * vector from a per-index table, rotates it by the model's Y angle, applies
 * it to the object's matrix, adds it to the object's position, and seeds
 * three random spin fields.  MATCH (136/136 ins), match_one standalone.
 *
 * Declarations: func_8012B23C / func_8012AD50 / D_801AA9D0 / D_801AAA58 are
 * NOT declared anywhere else in this TU (whole-TU grep, D2) so they're fresh
 * here; func_8012C1B8 / func_8012CAE4 / func_8001C214 / ApplyMatrixSV ARE
 * already file-scope in the TU (L163, L3160-3162) with these EXACT
 * signatures, so re-declaring them identically merges silently (D3).
 *
 * §48 STRUCT ASSIGN: `m = D_800AE620;` on the 32-byte, 4-aligned matrix
 * routes move_by_pieces to the plain lw/lw/lw+sw/sw/sw grouping (no lwl/lwr).
 *
 * §48-C2: `sv = D_801AA9D0[idx];` on the 8-byte, 2-aligned (u16 x,y,z; s16 w)
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
void func_80186468(void *a0)
{
          /* 32B, align 4 */
 /* 8B, align 2 */

    extern Mat32_8018A390_80186468 D_800AE620;
    extern Rec8_8018A390_80186468 D_801AA9D0[];
    extern s32 D_801AAA58[];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8012B23C(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern s32 rand(void);

    Mat32_8018A390_80186468 m;               /* sp+0x10 */
    Rec8_8018A390_80186468 sv;               /* sp+0x30 */
    void *mp;
    void *svp;
    s32 v0;
    s16 w;

    m = D_800AE620;
    sv = D_801AA9D0[*(s16 *)((s32)a0 + 0x70)];

    mp = &m;
    svp = &sv;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    w = sv.w;
    func_8001C214(v0, D_801AAA58[w]);

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



extern void (*D_801AAA64[])(void);

void func_80186688(void *a0) {
    D_801AAA64[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_801866C4(s32 a0) {
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


void func_80186758(void) {

    extern s16 D_801B1EFC;
    s16 *p = &D_801B1EFC;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_8018677C — cookbook §71 (sibling-first).
 * func_8018681C is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_8018681C(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_80186938 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
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


extern void func_8018681C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80186938(s32 arg0, Rec_8018A6A4_8018677C *arg1, s32 arg2, s32 arg3);

void func_8018677C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_8018677C sp10;
    s32 i;
    s32 ang;

    func_8018681C(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_80186938(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



    extern s16 D_801B1EF6;
    extern s16 D_801B1EF8;
    extern s16 D_801B1EFA;
    void func_8018681C(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801B1EF4;
        D_801B1EF4 = *(u16 *)((s32)arg0 + 0x0);
        D_801B1EF6 = *(u16 *)((s32)arg0 + 0x2);
        D_801B1EF8 = arg1;
        D_801B1EFA = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018684C(s32 a0) {

    extern s16 D_801B1EF4;
    extern s16 D_801B1EF6;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801B1EF4 = sxy[0];
    D_801B1EF6 = sxy[1];
}


extern s16 D_801B1EFA;

void func_801868C4(u16 a0) {
    s16 *p = &D_801B1EFA;
    *(u16 *)((char *)p + 0x0) += a0;
}



s32 func_80186A0C(void);
extern void func_80186938(s32 arg0, Rec_8018A6A4_8018677C *arg1, s32 arg2, s32 arg3);

void func_801868E0(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_80186A0C();
    if (v0 >= 0) {
        func_80186938(v0, (Rec_8018A6A4_8018677C *)a0, a1, a2);
    }
}



/* func_80186938 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
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
 * (2) func_80186938 itself — the TU prototypes it at L3570 as
 *     `extern void func_80186938(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_80186938") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801B1EFC / rand — declared VERBATIM as the TU already has them
 *     (D_801B1EFC: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_80186938");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801B1EFC;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801B1EFC);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_80186938 *)((u8 *)s1 + 6) = *(B4_80186938 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_80186938 *)((u8 *)s1 + 10) = *(B4_80186938 *)a3;
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




s32 func_80186A0C(void) {

    extern s16 D_801B1EFC;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801B1EFC + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_80186A48(s32 a0, s32 a1) {

    extern s16 D_801B1EFC;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801B1EFC);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_80186A94 — 16-entry table walk, stride 0xE, over D_801B1EFC.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801B1EFC; s16 *p = &D_801B1EFC; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_80186B70(s32 arg0);

void func_80186A94(void) {

    extern s16 D_801B1EFC;
    s16 *p = &D_801B1EFC;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_80186B70(i);
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



/* func_80186B70 — draws one entry of the 16-slot D_801B1EFC particle table:
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
 * LEVERS (each byte-checked against asm/.../func_80186B70.s)
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
 *      instead of EA,E4,E6.  `lh $a0,D_801B1EFA` is a single-set SET(REG,…) —
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
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801B1EF4/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801B1EF8, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_80186B70 is byte-identical.
 */

void func_80186B70(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_80186B70 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801B1EF4;
    extern s16 D_801B1EF6;
    extern s16 D_801B1EF8;
    extern s16 D_801B1EFC;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_80186B70 m;                    /* sp+0x10 */
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

    ent = (u8 *)((arg0 * 14) + (s32)&D_801B1EFC);
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

    ang = D_801B1EFA;
    bx = (u16)D_801B1EF4;
    by = (u16)D_801B1EF6;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801B1EF8;
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


void func_80186E34(void) {

    extern s16 D_801B1DF4;
    s16 *p = &D_801B1DF4;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_80186E80(s32 a0);

void func_80186E58(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_80186E80((s32)pv);
}



/* func_80186E80 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801AD2E0 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_80186F08 arg0
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
 * func_800491AC / RotTransPers at file scope L3484-3486; func_80186F08 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801AD2E0 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80186F08(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_80186E80(s32 a0) {
    extern u8 D_800AF648;
    extern V4_80186E80 D_801AD2E0;
    u16 sxy[4];
    s32 pv[4];

    *(V4_80186E80 *)pv = D_801AD2E0;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_80186F08(sxy, pv, 0x10, 0x18);
}



extern void func_80186F74(void *a0, void *a1, s16 a2);
extern void func_801870A8(s32 a0, s16 a1, u16 a2);

void func_80186F08(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_80186F74(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_801870A8(i, j, arg3);
    }
}





void func_80186F74(void *a0, void *a1, s16 a2) {

    extern s16 D_801B1DE8;
    extern s16 D_801B1DEA;
    extern u8 D_801B1DF0;
    extern u8 D_801B1DF1;
    extern u8 D_801B1DF2;
    extern u32 D_801B1DEC;
    if (a0 != NULL) {
        D_801B1DE8 = *(u16 *)a0;
        D_801B1DEA = *(u16 *)((s32)a0 + 2);
    } else {
        D_801B1DE8 = 0;
        D_801B1DEA = 0;
    }

    D_801B1DF0 = *(u8 *)a1;
    D_801B1DF1 = *(u8 *)((s32)a1 + 1);
    D_801B1DF2 = *(u8 *)((s32)a1 + 2);
    D_801B1DEC = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80186FE4(s32 a0) {

    extern s16 D_801B1DE8;
    extern s16 D_801B1DEA;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801B1DE8 = sxy[0];
    D_801B1DEA = sxy[1];
}




extern s32 func_801871C4(void);
extern void func_801870A8(s32 a0, s16 a1, u16 a2);

void func_8018705C(s32 a0, s32 a1) {
    s32 result = func_801871C4();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_801870A8(result, ext_a0, (u16)a1);
    }
}



/* func_801870A8 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801B1DF4.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801B1DF4 : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801B1DEE : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_801870A8(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_801870A8");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801B1DF4;
    extern s16 D_801B1DEE[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_801870A8 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_801870A8 *)((s32)&D_801B1DF4 + (a0 << 4));

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
    p->f4 = (s32)D_801B1DEE[0] * 64;
}




s32 func_801871C4(void) {

    extern s16 D_801B1DF4;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801B1DF4 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_80187200 — the 16-slot particle/effect stepper over D_801B1DF4[16]
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
 * D_801B1DF4 uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80187200(void) {

    extern s16 D_801B1DEE;
    extern s16 D_801B1DF4;
    extern void func_80187314(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801B1DEE;
    p = &D_801B1DF4;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_80187314(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_80187314 — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801B1DF4[a0] record, projects the
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


/* 0x10-byte-stride record table at D_801B1DF4 (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_80187314(s32 a0) {

    extern s16 D_801B1DE8;
    extern s16 D_801B1DEA;
    extern u8 D_801B1DF0;
    extern u8 D_801B1DF1;
    extern u8 D_801B1DF2;

    extern s16 D_801B1DF4;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_80187314 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_80187314 *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_80187314 *)m = *(Mat32_8018B23C_80187314 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801B1DF0;
    *(u8 *)(q + 5) = D_801B1DF1;
    *(u8 *)(q + 6) = D_801B1DF2;

    p = (Rec_8018B23C_80187314 *)((s32)&D_801B1DF4 + (a0 << 4));
    x = p->fA + (u16)D_801B1DE8;
    y = p->fE + (u16)D_801B1DEA;
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
        Bidx_8018B23C_80187314 *bp = (Bidx_8018B23C_80187314 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_80187314 *)q)->addr =
            ((PTag_8018B23C_80187314 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_80187314 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}


extern s16 D_801B2152;
extern s32 D_801B2164[8];
extern u16 D_800AF7BC;
extern u16 D_800AF7BE;
extern u8 D_801B2150[];

void func_801875F8() {
    s32 i;
    s32 flag;
    u16 x;
    s16 y;
    s32 h;
    s16 hv;
    s32 p0;
    s32 p1;
    u32 w;
    s32 *pw;
    s16 *ph;

    flag = 0;
    y = D_801B2152;
    x = *(u16 *)D_801B2150;

    if ((y > -((D_800AF7BE >> 1) + 0x10)) && (y < (D_800AF7BE >> 1) + 0x10)) {
        if ((-((D_800AF7BC >> 1) + 0x10) < (s16)x)) {
            flag = (s16)x < ((D_800AF7BC >> 1) + 0x10);
        }
    }

    pw = ((s32 *)D_801B2164);
    ph = (s16 *)((s32 *)D_801B2164) - 8;

    for (i = 0; i < 8; i++) {
        h = pw[i];
        if (h != 0) {
            if (flag) {
                hv = ph[i];
                p0 = (s16)x * hv;
                p1 = y * hv;
                w = *(u32 *)(h + 4);
                *(u32 *)(h + 4) = w & 0x7FFFFFFF;
                *(s16 *)(h + 8) = p0 >> 12;
                *(s16 *)(h + 0xA) = p1 >> 12;
            } else {
                w = *(u32 *)(h + 4);
                *(u32 *)(h + 4) = w | 0x80000000;
            }
        }
    }
}


void func_80187720(u8 *a0)
{
    s32 a1;
    u8 *v1;

    a1 = 0;
    v1 = a0;
    *(s16 *)(a0 + 2) = 0;
    *(s16 *)(a0 + 0) = 0;
    do {
        *(s16 *)(a0 + 4) = 0;
        *(s32 *)(v1 + 0x14) = 0;
        v1 += 4;
        a1 += 1;
        a0 += 2;
    } while (a1 < 8);
}


s32 func_80187754(s32 *arg0) {
    s32 i;
    s32 t;

    ((s16 *)arg0)[1] = 0;
    ((s16 *)arg0)[0] = 0;
    for (i = 0; i < 8; i++) {
        ((s16 *)arg0)[i + 2] = 0;
        t = arg0[i + 5];
        arg0[i + 5] = 0;
        if (t != 0) {
            *(s16 *)t = 0;
        }
    }
}


extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3);
extern s32 D_801B2164[8];

s32 func_80187798(s16 id, void *rec, s16 x, s16 y, u8 p)
{
    s32 i;
    s32 obj;

    for (i = 0; i < 8 && *(s32 *)(D_801B2164 + i) != 0; i++)
        ;
    if (i < 8) {
        obj = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
        if (obj != 0) {
            func_8001CB00(obj, rec, x, y);
            *(u8 *)(obj + 0x27) = p;
            *(u32 *)(obj + 4) |= 0xD0000000;
            *(s32 *)(D_801B2164 + i) = obj;
            *(s16 *)((u8 *)D_801B2164 + i * 2 - 0x10) = id;
            return i;
        }
    }
    return -1;
}



extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD04(s32 a0, s32 a1);




void func_801878A8(Ctl_8018A550_801878A8 *ctl, Rec_8018A550_801878A8 *rec)
{
    s32 i;
    Obj_8018A550_801878A8 *m;
    s16 v;
    u16 t;

    do {
        for (i = 0; i < 8; i++) {
            if (ctl->slots[i] == 0) {
                break;
            }
        }
        m = (Obj_8018A550_801878A8 *)((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
        if (m != 0) {
            ((void (*)(Obj_8018A550_801878A8 *, s32))func_8001CD04)(m, rec->fC);
            m->f4 |= 0xF0000000;
            v = rec->f6;
            m->f1C = v;
            m->f1A = v;
            m->f18 = v;
            ctl->slots[i] = m;
            ctl->ids[i] = rec->f4;
        }
        t = rec->f0;
        rec++;
    } while (t != 0xFF);
}


















void func_80187998(s32 *a0, s32 a1, s32 a2, s32 a3)
{
  s8 *new_var2;
  s8 *new_var;
  s32 *new_var3;
  new_var2 = a0;
  new_var3 = new_var2 + 0x0;
  new_var2 = (s8 *) new_var3;
  new_var = new_var2;
  *new_var = a1;
  *((s8 *) (new_var2 + 0x1)) = a2;
  *((s8 *) (new_var2 + 0x2)) = a3;
}

void func_801879A8(s32 *a0, s8 a1, s8 a2, s8 a3) {
        *(s8*)((s32)a0 + 0x4) = a1;
        *(s8*)((s32)a0 + 0x5) = a2;
        *(s8*)((s32)a0 + 0x6) = a3;
    }



extern void func_80187AB8(void *a0);
extern void func_80187B34(void *a0);
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_801879B8(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_80187AB8(a0);
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
    func_80187B34((void *)*(s32 *)((s32)a0 + 0x20));
}




void func_80187AB8(void *a0) {
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

void func_80187B34(void *a0)
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
extern int func_80188194(short *pos, int a1, int a2);

void func_80187FD4(unsigned short *param_1, short *param_2, short *param_3,
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
        p = func_80188194(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


extern int func_80188194(short *pos, int a1, int a2);

int func_80188160(short *pos, int a1, int a2) {
    int ret;
    ret = func_80188194(pos, a1, a2);
    if (ret != 0) {
        *(s16 *)(ret + 0x32) = 1;
    }
    return ret;
}


extern u8 *func_801290DC(s32 a0, u8 *a1);

int func_80188194(short *pos, int a1, int a2)
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





