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
extern s32 D_80189E40[];
extern u8 D_80078E78[];
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32, s32, s32, s32);
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
extern u16 D_800B99DA;
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
extern s32 func_8014C568(void *a0);
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
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
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
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
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
extern s32 func_80128ED8(void *a0, void *a1);
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




extern s32 D_801151D4;
extern s16 D_801AE614;
extern s16 D_801AE616;
extern s16 D_801AE618;
extern s16 D_801AE61C;
extern s16 D_801AE61E;
extern s16 D_801AE620;

void func_8017B824(void) {
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

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017BEBC);


extern void (*D_8018BC74[])(void);

void func_8017BEE4(void *a0) {
    D_8018BC74[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017BF20);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017BF58);

DEFINE_func_8017BF98()  /* dedup: shared engine-core @0x8017BF98 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017BFA0);


extern void (*D_8018BC80[])(void);

void func_8017BFC8(void *a0) {
    D_8018BC80[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C004);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C03C);

DEFINE_func_8017C07C()  /* dedup: shared engine-core @0x8017C07C (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C084);


extern void (*D_8018BD40[])(void);

void func_8017C0C8(void *a0) {
    D_8018BD40[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C104);

extern void func_8017C154(void);
void func_8017C12C(void) {
    func_8017C154();
}


DEFINE_func_8017C14C()  /* dedup: shared engine-core @0x8017C14C (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C154);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C290);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C624);


extern void (*D_8018BD80[])(void);

void func_8017C664(void *a0) {
    D_8018BD80[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C6A0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C814);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017C8FC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CC44);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CCC4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CD10);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CE10);


extern void (*D_8018BDA0[])(void);

void func_8017CE54(void *a0) {
    D_8018BDA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CE90);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017CFBC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D098);


extern void (*D_8018BDB0[])(void);

void func_8017D0DC(void *a0) {
    D_8018BDB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D118);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D194);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D1E0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D318);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D5F8);


extern void (*D_8018BDBC[])(void);

void func_8017D63C(void *a0) {
    D_8018BDBC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D678);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D75C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D804);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D890);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D900);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017D9C8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DA98);


extern void (*D_8018BF40[])(void);

void func_8017DB00(void *a0) {
    D_8018BF40[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DB3C);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DBC4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DC28);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DC4C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DCC0);

DEFINE_func_8017DD74()  /* dedup: shared engine-core @0x8017DD74 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DD7C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DDBC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DE24);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DE8C);

DEFINE_func_8017DF7C()  /* dedup: shared engine-core @0x8017DF7C (src/shared) */


extern void (*D_8018BF84[])(void);

void func_8017DF84(void *a0) {
    D_8018BF84[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017DFC0);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017E35C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017EE98);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017EECC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017EF08);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017EF68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017FE8C);


extern void (*D_8018BFC0[])(void);

void func_8017FEC8(void *a0) {
    D_8018BFC0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017FF04);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017FF54);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8017FFB0);


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180034);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018019C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801801E8);


extern void (*D_8018BFD4[])(void);

void func_801804F4(void *a0) {
    D_8018BFD4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180530);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180570);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801805E0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018066C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180740);


extern void (*D_8018BFE8[])(void);

void func_80180794(void *a0) {
    D_8018BFE8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801807D0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180884);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801808E0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180A50);

extern void func_80183674(void);
    void func_80180AB8(void) {
        func_80183674();
    }



extern void (*D_8018C040[])(void);

void func_80180AD8(void *a0) {
    D_8018C040[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180B14);


extern s32 func_800167F0(s32 a0);

s32 func_80180B58(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018C048[])(void);

void func_80180B7C(void *a0) {
    D_8018C048[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180BB8);


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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180CD0);

s32 func_80180D0C(void) {
        return 0;
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180D14);


extern void (*D_8018C070[])(void);

void func_80180D5C(void *a0) {
    D_8018C070[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180D98);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180DD4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180E58);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180EE0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180F14);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80180FC8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018103C);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801810D0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181114);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801811B4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801811DC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181204);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018127C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801812BC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181388);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801813FC);

extern s32 func_8017EE98(s32 arg);
    extern s32 func_80171990(u8 *a0);
    void func_80181440(s32 param_1) {
        if (((int (*)(void))func_8017EE98)() != 0) {
            ((void (*)(s32))func_80171990)(param_1);
        }
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181478);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801814DC);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018C0A0;

void func_8018152C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018C0A0, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181554);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801815E8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801816AC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181774);

extern void func_8012A568(void (*a0)(void));
    extern s32 func_80181864(s32 a0);
    s32 func_8018183C(void)
{
        ((void (*)(void *))func_8012A568)((void *)func_80181864);
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181864);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181918);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181940);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801819F4);


extern void (*D_8018C100[])(void);

void func_80181A78(void *a0) {
    D_8018C100[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181AB4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181BA4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181C38);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181CCC);

void func_80181E98(void) {
}

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181EA0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181F14);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80181F78);


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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801823BC);

extern void func_8013C0F8(void *a0);
    extern s32 func_8017EF08(s32 a0);
    extern s32 D_801A3A0C;
    extern s32 D_801AEB58;
    void func_8018242C(void) {
        ((void (*)(void *))func_8013C0F8)(&D_801A3A0C);
        ((void (*)(s32))func_8017EF08)((s32)&D_801AEB58);
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182464);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801824D4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182560);

s16 func_801825D8(void) {

    extern s16 D_801AEAFE;
    return D_801AEAFE;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801825E8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182614);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018270C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018278C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801827C0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801827F4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182828);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182888);

















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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018291C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182950);

extern void func_801816AC(void);
    void func_801829C8(void) {
        func_801816AC();
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801829E8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182A30);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182A90);

extern void func_80181554(void);
    void func_80182AD0(void) {
        func_80181554();
    }


extern void func_80181774(void);
    void func_80182AF0(void) {
        func_80181774();
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182B10);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182B68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182BB8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182C10);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182CD8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80182E38);


extern void (*D_8018C66C[])(void);

void func_80183088(void *a0) {
    D_8018C66C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801830C4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183130);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801831E4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018325C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183338);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183674);

extern void (*D_8018C94C[])(void);

void func_801836E0(void *a0) {
    D_8018C94C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018371C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183790);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801837DC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018381C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183884);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801838FC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183A1C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183B20);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183BC4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183C9C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183DAC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183E48);


extern void (*D_8018C964[])(void);

void func_80183EFC(void *a0) {
    D_8018C964[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80183F38);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801840F8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801842CC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184398);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801844AC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184524);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184578);


s32 func_801845B8(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x6;
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801845CC);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801846F8);

void func_80184808(void *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184818);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184870);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801848A4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184940);

extern void func_8017BEBC(void);
    void func_801849A8(void) {
        func_8017BEBC();
    }


extern s32 func_8017BFA0(void);
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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184A28);

void func_80184A50(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }


void func_80184A5C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x3;
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184A68);


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
extern void func_80184B30(u8 *a0);
extern void (*D_8018CC58[])(int);

void func_80184AE4(int param_1)
{
    ((void (*)(void))func_80184B30)();
    D_8018CC58[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184B30);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184B80);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184C24);

void func_80184C60(void) {
}

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184C68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184CBC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184D68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184DD8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184E68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184EB8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184F68);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80184FD8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185028);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801850E4);

extern void func_80184A68(void);
void func_8018514C(void) {
    func_80184A68();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018516C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801851CC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185264);


extern void (*D_8018CC70[])(void);

void func_80185318(void *a0) {
    D_8018CC70[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185354);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801853F0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185520);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018562C);

















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

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185814);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801858E8);


extern void (*D_8018CCA0[])(void);

void func_8018593C(void *a0) {
    D_8018CCA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185978);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801859B4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185A5C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185B04);


extern void (*D_8018CD04[])(void);

void func_80185BA8(void *a0) {
    D_8018CD04[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185BE4);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185CAC);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185DE0);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185EB4);


s32 func_80185EDC(void) {
    return 122;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185EE4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80185F48);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801860A8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018628C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186348);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801863F4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186468);


extern void (*D_801AAA64[])(void);

void func_80186688(void *a0) {
    D_801AAA64[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801866C4);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018677C);


extern s16 D_801B1EF4;
    extern s16 D_801B1EF6;
    extern s16 D_801B1EF8;
    extern s16 D_801B1EFA;
    void func_8018681C(s32 arg0, s32 arg1, s32 arg2) {
        D_801B1EF4 = *(u16 *)((s32)arg0 + 0x0);
        D_801B1EF6 = *(u16 *)((s32)arg0 + 0x2);
        D_801B1EF8 = arg1;
        D_801B1EFA = arg2;
    }


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018684C);

extern s16 D_801B1EFA;

void func_801868C4(u16 a0) {
    s16 *p = &D_801B1EFA;
    *(u16 *)((char *)p + 0x0) += a0;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801868E0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186938);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186A0C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186A48);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186A94);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186B70);

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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186E58);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186E80);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186F08);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186F74);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80186FE4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_8018705C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801870A8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801871C4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187200);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187314);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801875F8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187720);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187754);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187798);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801878A8);

















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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_801879B8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187AB8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80187B34);


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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80188160);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_8017AE2C", func_80188194);




