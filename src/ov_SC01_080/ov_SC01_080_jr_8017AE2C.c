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
extern u8 D_80185A90;
extern u8 D_80185A00;
extern u8 D_801859DC;
extern u8 D_801859B8;
extern u8 D_80185A6C;
extern u8 D_80185A48;
extern u8 D_80185A24;
extern u8 D_80185994;
extern void func_80145934(void);
extern u8 D_80185B20;
extern u8 D_80185AFC;
extern u8 D_80185AD8;
extern u8 D_80185AB4;
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
extern unsigned char D_80184F18[];
extern unsigned char D_80184F48[];
extern unsigned char D_80184F98[];
extern unsigned char D_80184FC8[];
extern unsigned char D_80184FF8[];
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
extern void (*D_80185048[])(void *);
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
extern s32 D_80185110[];
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
extern u8 D_80185198[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801851A0;
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
extern int D_801C4888;
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
extern s32 D_801C488C;
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
extern s32 D_801851D0;
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
extern void (*D_80185278[])(void);
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
extern void (*D_8018529C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018528C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801852B0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801852BC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801852CC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801852E4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801852D4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801852F8[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80185314[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80185304;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80185328[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018533C[])(void);
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
extern s32 D_80185350;
extern void (*D_80185378[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80185358;
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
extern int (*D_801853C4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801853C8[])(void);
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
extern unsigned short D_8018582C[];
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
extern void (*D_8018583C[])(void);
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
extern int D_801C48C0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80185864[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80185844;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80185854;
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
extern void (*D_801858A4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801858AC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80185878;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801858B8[])(void);
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
extern u8 D_80185888;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C48C8;
extern s32 D_801C48D4;
extern s32 D_801C48D8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801858F4[])(s32 *);
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
extern s32 D_801858C8[];
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
extern s32 D_801C48D0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80185B44[])(void);
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
extern char D_80185964[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80185BE8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80185D3C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80185B58;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80185D44[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80185B68;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80185B88;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80185D4C[])(void);
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
extern void (*D_80185D74[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80185D80[])(void);
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
extern void (*D_80185BF4[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80185E24;
extern void func_8015D380(s32 a0);
extern unsigned char D_80184F08[];
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
extern unsigned char D_80185E38[];
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
extern s8 D_80185E74[];
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
extern u16 D_80185EBC;
extern u16 D_80185EBE;
extern u16 D_80185EC0;
extern s32 D_80185EC4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80185ECC;
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
extern int D_80185BD8;
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
extern unsigned int D_80185F50[];
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
extern void (*D_80186000[])(void);
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
extern u16 D_80186030[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80186094;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C48E0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801860B8[])(void);
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
extern int D_801C4938[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80186100[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801860F0;
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
extern char D_801C4190[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80186108[])(void);
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
extern void (*D_8018615C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80186124;
extern s16 D_80186158;
extern s16 D_80186156;
extern s16 D_80186154;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80186168[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C4998;
extern u8 D_801C4999;
extern u8 D_801C499A;
extern u8 D_801C499B;
extern u8 D_801C499C;
extern u8 D_801C499D;
extern u8 D_801C499E;
extern u8 D_801C499F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80186178[])(void);
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
extern s32 D_801C49D8;
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
extern void (*D_801861BC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80186238[];
extern s32 D_80186258[];
extern u8 D_801862D4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801862F4[];
extern u8 D_80186314[];
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
extern void (*D_801863B0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018642C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C41A0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80186438[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80186440[])(void);
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
extern void (*D_80186508[])(void);
extern void func_80166618(void *a0);
extern void (*D_80186518[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80186528[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80186534[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80186494[];
extern u8   D_801864A8[];
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
extern void (*D_8018654C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80186554[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018655C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80186564[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018656C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80186574[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018657C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80186630[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80186638[])(void);
extern void func_80169F00(void *a0);
extern char D_801865E8[];
extern char D_801865A8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80186670[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018667C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801866C4[])(void);
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
extern void (*D_80186740[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C4CF8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80186734[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80186778[];
extern unsigned short D_80186780[];
extern unsigned short D_80186788[];
extern unsigned char D_801C4D00[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C4CF8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80186790[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C4E34;
extern M2C_UNK D_801C4E38;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C4DC0;
extern void (*D_801867C0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C4E3C[];
extern u8 D_801C4E44[];
extern u8 D_801C4DF4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801867C8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801867E4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801867EC[])(void);
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
extern void (*D_80186854[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801867F8;
extern u8 D_80186804;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80186888[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80186890[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801868E4[])(void);
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
extern u16 D_80186918[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80186908[];
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
extern s32 D_80186934;
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
extern void (*D_801869AC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801869B4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801869BC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801869C4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801869CC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801869D4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801869E0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801869EC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801869F8[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80186A08[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80186A18[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80186A20[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80186A28[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80186A30[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80186A38[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80186A40[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80186A48[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80186A50[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80186A58[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80186A60[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80186A68[])(void);
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
extern void (*D_80186A70[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80186A78[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80186A80[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80186A88[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80186A90[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80186A98[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80186AA0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80186AA8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80186AB0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80186AB8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80186AC0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80186AC8[])(void);
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
extern void (*D_80186B0C[])(void);
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
extern M2C_UNK D_80186AD0;
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
extern void (*D_80186B3C[])(void);
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
extern void (*D_80186B78[])(void);
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
extern void (*D_80186BD0[])();
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
extern void (*D_80186BE0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80186BE8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80186D50[])();
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
extern void (*D_80186D5C[])();
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
extern M2C_UNK D_801C43E8;
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
extern s16 D_801C7EDC;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C5578;
extern short D_801C7F4C;
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
extern s32 D_801C59A4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C59CC;
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
extern s16 D_801C5988;
extern s32 func_8017A3B0(void);
extern short D_801C59C4;
extern short D_801C59C0;
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

extern s16 D_801C7EA8;
extern s16 D_801C7EAA;
extern s16 D_801C7EB4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801C7EA8;

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
                    func_8012B744(p, &D_801C7EB4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801C7EA8+0xC == &D_801C7EB4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801C7EA8 + 0xC)) < 0x101) {
                    D_801C7EA8 = 0;
                    D_801C7EAA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801C7EB4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801C7EA8 + 0xC)) < 0x101) {
            D_801C7EA8 = 0;
            D_801C7EAA = 0;
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
    extern s16 D_801C5A04;
    extern s16 D_801C5A06;
    extern s16 D_801C5A08;
    extern s16 D_801C59FC;
    extern s16 D_801C59FE;
    extern s16 D_801C5A00;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801C5A04, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801C5A06, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801C5A08, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801C59FC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801C59FE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801C5A00, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801C598C;
extern u16 D_801C5A0C;
extern u16 D_801C5A0E;
extern u16 D_801C5A10;
extern s16 D_801C7EDC;

void func_8017B1D8(void) {
    func_8012A418();
    D_801C7EDC = 0;
    D_801C598C = 0;
    D_801C5A0C = D_80126B5E;
    D_801C5A0E = D_80126B62;
    D_801C5A10 = D_80126B66;
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
    extern u8 D_80186E98[];
    extern s16 D_801C5A04;
    extern s16 D_801C59FC;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80186E98[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80186E98[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C5A04;
        s16 *p78C = &D_801C59FC;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801C7EDC = 1;
        D_801C598C = 0;
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
    extern SV4_8017B368 D_801C59AC;
    extern SV4_8017B368 D_801C59B4;
    extern s16 D_801C5A04;
    extern s16 D_801C59FC;
    extern u16 D_80186E98;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C59AC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C59B4;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80186E98)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80186E98)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C5A04) = loc0;
    (*(SV4_8017B368 *)&D_801C59FC) = loc1;
    D_801C7EDC = 1;
    D_801C598C = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801C59AC;
    extern SV4_8017B368 D_801C59B4;
    extern s16 D_801C5A04;
    extern s16 D_801C59FC;
    extern u16 D_80186E98;
    extern s16 D_801C598C;
    extern s16 D_801C7EDC;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C59AC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C59B4;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80186E98)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80186E98)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C5A04) = loc0;
    (*(SV4_8017B368 *)&D_801C59FC) = loc1;
    D_801C7EDC = 1;
    D_801C598C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801C5A04).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801C5A04).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801C5A04).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801C59FC).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801C59FC).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801C59FC).c;
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
    extern u8 D_80186E98[];
    extern s16 D_801C5A04;
    extern s16 D_801C5A06;
    extern s16 D_801C5A08;
    extern s16 D_801C59FC;
    extern s16 D_801C59FE;
    extern s16 D_801C5A00;
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
        s32 a1addr = (s32)&D_80186E98[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80186E98[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C5A04;
        s16 *p78C = &D_801C59FC;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801C5A06;
            v798 = D_801C5A08;
            v78C = *p78C;
            v78E = D_801C59FE;
            v790 = D_801C5A00;
            __asm__ __volatile__("");
            D_801C7EDC = 1;
            D_801C598C = 0x1E;
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
extern s16 D_801C598C;
extern s16 D_801C5A04;
extern s16 D_801C5A06;
extern s16 D_801C5A08;
extern s16 D_801C59FC;
extern s16 D_801C59FE;
extern s16 D_801C5A00;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801C598C = 0;
    D_801C5A04 = (s16) D_80114F30;
    D_801C5A06 = (s16) D_80114F34;
    D_801C5A08 = (s16) D_80114F38;
    D_801C59FC = (s16) D_80114F24;
    D_801C59FE = (s16) D_80114F28;
    D_801C5A00 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801C5A1C;
extern s16 D_801C5A1E;
extern s16 D_801C5A20;
extern s16 D_801C5A24;
extern s16 D_801C5A26;
extern s16 D_801C5A28;

void func_8017B824(void) {
    D_801C5A1C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801C5A1E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801C5A20 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801C5A24 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801C5A26 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801C5A28 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801C5A1C;
extern s16 D_801C5A1E;
extern s16 D_801C5A20;
extern s16 D_801C5A24;
extern s16 D_801C5A26;
extern s16 D_801C5A28;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801C5A1C;
    D_80114F34 = D_801C5A1E;
    D_80114F38 = D_801C5A20;
    D_80114F24 = D_801C5A24;
    D_80114F28 = D_801C5A26;
    D_80114F2C = D_801C5A28;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801C5A04), src[8..15] -> (*(S8_8017B8E8 *)&D_801C59FC) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801C5A04) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801C59FC) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801C5A0C;
extern u16 D_801C5A0E;
extern u16 D_801C5A10;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801C598C;
extern short D_801C5A14;
extern short D_801C5A16;
extern short D_801C5A18;
extern s16 D_801C5A04;
extern s16 D_801C5A06;
extern s16 D_801C5A08;
extern s16 D_801C59FC;
extern s16 D_801C59FE;
extern s16 D_801C5A00;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801C5A0C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801C5A0E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801C5A10);
    (*(s16 *)&D_801C5A14) = buf[0];
    (*(s16 *)&D_801C5A16) = buf[1];
    (*(s16 *)&D_801C5A18) = buf[2];
    D_801C5A04 = D_80114F30 + buf[0];
    D_801C598C = 0;
    D_801C5A06 = D_80114F34 + buf[1];
    D_801C5A08 = D_80114F38 + buf[2];
    D_801C59FC = D_80114F24 + buf[0];
    D_801C59FE = D_80114F28 + buf[1];
    D_801C5A00 = D_80114F2C + buf[2];
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

extern SV4 D_801C59AC;
extern SV4 D_801C59B4;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801C59B4) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801C59AC = svec;

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
    D_801C59B4 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801C59B4)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801C59AC) = svec;

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
    (*(SV4_8017BB34*)&D_801C59B4) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801C59D4[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801C59D4;
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
extern s16 D_801C598C;
extern s16 D_801C7EDC;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801C598C = D_801C598C + 1;
    if (D_801C598C >= 0x1F) {
        D_801C7EDC = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801C598C;
extern s16 D_801C7EDC;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801C598C = D_801C598C + 1;
    if (0x18 < D_801C598C) {
        func_8012A4BC();
        D_801C7EDC = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801C598C;
extern void (*D_801C59D0)(void);
extern short D_801C5A14;
extern short D_801C5A16;
extern short D_801C5A18;
extern s16 D_801C7EDC;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801C598C = D_801C598C + 1;
    if (D_801C598C >= 0x19) {
        if (D_801C59D0 != 0) {
            (*D_801C59D0)();
        } else {
            D_80114F30 = D_80114F30 + D_801C5A14;
            D_80114F34 = D_80114F34 + D_801C5A16;
            D_80114F38 = D_80114F38 + D_801C5A18;
            D_80114F24 = D_80114F24 + D_801C5A14;
            D_80114F28 = D_80114F28 + D_801C5A16;
            D_80114F2C = D_80114F2C + D_801C5A18;
            func_8012A4BC();
        }
        D_801C7EDC = 0;
    }
}



extern void (*D_80186F38[])(void);

void func_8017BE60(void *a0) {
    D_80186F38[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017BEBC);

extern void ReadRotMatrix(void *a0);
extern void PushMatrix(void);
extern void func_8004974C(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void PopMatrix(void);
void func_8017C294(u16 *a0, void *a1) {
    s32 mat[8];
    s32 buf[8];
    s16 sv[4];
    ReadRotMatrix((void *)mat);
    PushMatrix();
    sv[0] = (s16)(a0[0] - *(s32 *)((u8 *)mat + 0x14));
    sv[1] = (s16)(a0[1] - *(s32 *)((u8 *)mat + 0x18));
    sv[2] = (s16)(a0[2] - *(s32 *)((u8 *)mat + 0x1C));
    func_8004974C((void *)mat, (void *)buf);
    ApplyMatrixSV((void *)buf, (void *)sv, a1);
    PopMatrix();
}


int func_8017C338(short *param_1, short *param_2, short *param_3, int param_4) {
    register int i2o __asm__("$5");
    register int i4o __asm__("$9");
    short sVar1; int rx, rz, uVar5;
    i4o = param_2[1];
    __asm__ __volatile__("" : : "r"(i4o));
    i2o = param_1[1]; uVar5 = 0;
    if (i2o >= i4o) {
        rx = param_1[0] - i2o * (param_2[0] - param_1[0]);
        rz = param_1[2] - i2o * (param_2[2] - param_1[2]);
    } else {
        register int den __asm__("$3");
        int p2x = param_2[0], p2z = param_2[2];
        den = i2o - i4o;
        rx = p2x + i4o * (p2x - param_1[0]) / den;
        rz = p2z + i4o * (p2z - param_1[2]) / den;
    }
    if (rx >= -0x7fff) { i2o = 0x7fff; if (rx < 0x8000) i2o = rx; }
    else i2o = -0x7fff;
    *param_3 = (short)i2o;
    if (rz >= -0x7fff) { i2o = 0x7fff; if (rz < 0x8000) i2o = rz; }
    else i2o = -0x7fff;
    param_3[2] = (short)i2o; param_3[1] = 0; sVar1 = (short)param_4;
    if ((int)*param_3 < *param_1 - param_4) { uVar5 = 0xffffffff; *param_3 = *param_1 - sVar1; }
    if (*param_1 + param_4 < (int)*param_3) { uVar5 = 0xffffffff; *param_3 = *param_1 + sVar1; }
    if ((int)param_3[2] < param_1[2] - param_4) { uVar5 = 0xffffffff; param_3[2] = param_1[2] - sVar1; }
    if (param_1[2] + param_4 < (int)param_3[2]) { uVar5 = 0xffffffff; param_3[2] = param_1[2] + sVar1; }
    return uVar5;
}


extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
void func_8017C530(s32 a0, s32 a1) {
    s32 ofx;
    s32 ofy;
    s32 sxy;
    s32 p;
    ReadGeomOffset(&ofx, &ofy);
    func_8004921C(0, 0);
    RotTransPers(a0, a1, &sxy, &p);
    func_8004921C(ofx, ofy);
}



/* func_8017C59C — ov_SC01_080_jr_8017AE2C — MAP-TILE model renderer (947 ins).
* Family clone of the byte-matched func_8017C6F4 (ov_SC03_126, s43). Same 947-ins body;
 * only the D_* cell-table and the rect-helper callee differ per overlay (s43 wave remap).
 * Outer: screen rect -> 64x64 cell grid window -> per-cell bbox RTPT/RTPS cull.
 * Inner: per-prim RTPT -> flag/nclip/opz cull -> switch(w & 0xF):
 *   0,1=POLY_F4 / 2,3=POLY_FT4 / 4,5=POLY_F3 / 6,7=POLY_FT3 -> OT insert.
 * NOTE: the F3 arm bbox-tests the packet through PFT3_C59C offsets (8/0x10/0x18)
 * — a source-level copy/paste quirk of this variant, reproduced verbatim.
 *
 * MATCH (947 ins, pin-free) — s43 Fable crack. Two load-bearing source shapes
 * (byte-proven; see .run/s43/fable/8017C6F4/NOTES.md):
 *   1. X-pass and Y-pass bbox min/max intermediates are DISTINCT variables
 *      (xmn1..xmx2 vs ymn1..ymx2) — the target allocates them differently.
 *   2. The cell-level clamps REUSE the prim-loop vars (mn/mx for X, mny/my
 *      for Y); there are no separate mnc/mxc. This puts the clamps in
 *      $t0/$a2/$a3/$a1 and makes the Y-pass `mny = ymn1` a deleted self-move.
 * Neither change matches alone (63 / 624 mismatches); prim lands $t5 and
 * cell $t3 naturally once the bbox block allocates right.
 */

typedef struct { u32 w0, w1, w2; } PrimC59C;
typedef struct { u8 *vtx; u32 f4; u32 xx, yy, zz; PrimC59C *prim, *end; } CellC59C;

typedef struct { s16 vx, vy; } DVEC2_C59C;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C59C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2; } PF3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2, x3, y3; } PF4_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; } PFT3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PFT4_C59C;

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
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
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

void func_8017C59C(s32 arg0)
{
    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MTX_C59C *);
    extern void func_80052E38(MTX_C59C *);
    extern void func_8017BEBC(void *, void *, s32);
    extern u8 D_801C75E0[];
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    s16 rect[4];
    DVEC2_C59C tmpxy[4];
    SVEC2_C59C box[8];
    SVEC2_C59C sxy[8];
    MTX_C59C mtx;
    struct { long flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 cx0, cx1, cy0, cy1, y, col;
    CellC59C **rowptr;
    CellC59C **p;
    CellC59C *cell;
    PrimC59C *prim;
    PrimC59C *end;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    u32 xlo, xhi, ylo, yhi, zlo, zhi;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 ymn1, ymx1, ymn2, ymx2;
    s32 my, mny, mx, mn;

    func_800491EC();
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);
    func_8017BEBC(D_801C75E0, rect, *(s32 *)(arg0 + 0x60));

    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    cx0 = (rect[0] + 0x4000) / 512;
    cx1 = (rect[0] + rect[2] + 0x4000) / 512 + 2;
    cx0 = (cx0 < 0) ? 0 : ((cx0 > 0x3F) ? 0x3F : cx0);
    cx1 = (cx1 < 0) ? 0 : ((cx1 > 0x3F) ? 0x3F : cx1);
    cy0 = (rect[1] + 0x4000) / 512 - 1;
    cy1 = (rect[1] + rect[3] + 0x4000) / 512 + 2;
    cy0 = (cy0 < 0) ? 0 : ((cy0 > 0x3F) ? 0x3F : cy0);
    cy1 = (cy1 < 0) ? 0 : ((cy1 > 0x3F) ? 0x3F : cy1);

    rowptr = (CellC59C **)(*(s32 *)(arg0 + 0xC)) + (cy0 * 64 + cx0);

    for (y = cy0; y < cy1; y++, rowptr += 0x40) {
        for (col = cx0, p = rowptr; col < cx1; col++, p++) {
            cell = *p;
            if (cell == 0) continue;

            wx = cell->xx;
            xlo = wx & 0xFFFF;
            xhi = wx >> 16;
            wy = cell->yy;
            ylo = wy & 0xFFFF;
            yhi = wy >> 16;
            wz = cell->zz;
            zlo = wz & 0xFFFF;
            zhi = wz >> 16;

            box[0].vx = xlo; box[0].vy = ylo; box[0].vz = zlo;
            box[1].vx = xhi; box[1].vy = ylo; box[1].vz = zlo;
            box[2].vx = xlo; box[2].vy = ylo; box[2].vz = zhi;
            box[3].vx = xhi; box[3].vy = ylo; box[3].vz = zhi;
            box[4].vx = xlo; box[4].vy = yhi; box[4].vz = zlo;
            box[5].vx = xhi; box[5].vy = yhi; box[5].vz = zlo;
            box[6].vx = xlo; box[6].vy = yhi; box[6].vz = zhi;
            box[7].vx = xhi; box[7].vy = yhi; box[7].vz = zhi;

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
            mn = xmn1;
            if (xmn2 < mn) mn = xmn2;
            mx = xmx1;
            if (mx < xmx2) mx = xmx2;
            if (mx < -0xA0) continue;
            if (!(mn < 0xA1)) continue;

            xa32 = sxy[0].vy;
            xb32 = sxy[1].vy;
            if (xb32 < xa32) { ymx1 = xa32; ymn1 = xb32; } else { ymn1 = xa32; ymx1 = xb32; }
            t32 = sxy[2].vy;
            if (ymx1 < t32) ymx1 = t32; else if (t32 < ymn1) ymn1 = t32;
            t32 = sxy[3].vy;
            if (ymx1 < t32) ymx1 = t32; else if (t32 < ymn1) ymn1 = t32;
            xa32 = sxy[4].vy;
            xb32 = sxy[5].vy;
            if (xb32 < xa32) { ymx2 = xa32; ymn2 = xb32; } else { ymn2 = xa32; ymx2 = xb32; }
            t32 = sxy[6].vy;
            if (ymx2 < t32) ymx2 = t32; else if (t32 < ymn2) ymn2 = t32;
            t32 = sxy[7].vy;
            if (ymx2 < t32) ymx2 = t32; else if (t32 < ymn2) ymn2 = t32;
            mny = ymn1;
            if (ymn2 < mny) mny = ymn2;
            my = ymx1;
            if (my < ymx2) my = ymx2;
            if (my < -0x78) continue;
            if (!(mny < 0x79)) continue;

            prim = cell->prim;
            end = cell->end;
            vtx = cell->vtx;
            while (prim < end) {
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
                    code = w & 0xF;
                    vd = vtx + ((w & 0xFFF0) >> 1);
                    gte_stopz(&g.opz);
                    if (g.opz > 0) {
                        switch (code) {
                        case 4:
                        case 5:
                            gte_stsxy3_f3(pkt);
                            gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                            if (((PFT3_C59C *)pkt)->x0 > ((PFT3_C59C *)pkt)->x1) {
                                mx = ((PFT3_C59C *)pkt)->x0;
                                mn = ((PFT3_C59C *)pkt)->x1;
                            } else {
                                mn = ((PFT3_C59C *)pkt)->x0;
                                mx = ((PFT3_C59C *)pkt)->x1;
                            }
                            if (((PFT3_C59C *)pkt)->x2 > mx) mx = ((PFT3_C59C *)pkt)->x2;
                            else if (((PFT3_C59C *)pkt)->x2 < mn) mn = ((PFT3_C59C *)pkt)->x2;
                            if (mx >= -0xA0 && mn < 0xA1) {
                                if (((PFT3_C59C *)pkt)->y0 > ((PFT3_C59C *)pkt)->y1) {
                                    my = ((PFT3_C59C *)pkt)->y0;
                                    mny = ((PFT3_C59C *)pkt)->y1;
                                } else {
                                    mny = ((PFT3_C59C *)pkt)->y0;
                                    my = ((PFT3_C59C *)pkt)->y1;
                                }
                                if (((PFT3_C59C *)pkt)->y2 > my) my = ((PFT3_C59C *)pkt)->y2;
                                else if (((PFT3_C59C *)pkt)->y2 < mny) mny = ((PFT3_C59C *)pkt)->y2;
                                if (my >= -0x78 && mny < 0x79) {
                                    s32 za;
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
                                    ((PF3_C59C *)pkt)->rgbc = prim->w0;
                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                    pkt += 0x14;
                                }
                            }
                            break;
                        case 6:
                        case 7:
                            gte_stsxy3c(&tmpxy[0]);
                            gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                            if (tmpxy[0].vx > tmpxy[1].vx) {
                                mx = tmpxy[0].vx;
                                mn = tmpxy[1].vx;
                            } else {
                                mn = tmpxy[0].vx;
                                mx = tmpxy[1].vx;
                            }
                            if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                            else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                            if (mx >= -0xA0 && mn < 0xA1) {
                                if (tmpxy[0].vy > tmpxy[1].vy) {
                                    my = tmpxy[0].vy;
                                    mny = tmpxy[1].vy;
                                } else {
                                    mny = tmpxy[0].vy;
                                    my = tmpxy[1].vy;
                                }
                                if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                if (my >= -0x78 && mny < 0x79) {
                                    s32 za;
                                    u32 *otp;
                                    u32 *tp;
                                    gte_avsz3();
                                    if (g.sz0 > g.sz1) {
                                        za = g.sz0;
                                        if (za < g.sz2) za = g.sz2;
                                    } else {
                                        za = g.sz1;
                                        if (za < g.sz2) za = g.sz2;
                                    }
                                    g.opz = za;
                                    if (code != 6) g.opz = za + 0x200;
                                    *(u32 *)&((PFT3_C59C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                    *(u32 *)&((PFT3_C59C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                    *(u32 *)&((PFT3_C59C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                    tp = (u32 *)prim->w0;
                                    ((PFT3_C59C *)pkt)->rgbc = tp[0];
                                    ((PFT3_C59C *)pkt)->uvc0 = tp[1];
                                    ((PFT3_C59C *)pkt)->uvp1 = tp[2];
                                    ((PFT3_C59C *)pkt)->uv2 = tp[3];
                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                    pkt += 0x20;
                                }
                            }
                            break;
                        case 0:
                        case 1:
                            gte_stsxy3_f3(pkt);
                            gte_ldv0(vd);
                            gte_rtps();
                            if (((PF4_C59C *)pkt)->x0 > ((PF4_C59C *)pkt)->x1) {
                                mx = ((PF4_C59C *)pkt)->x0;
                                mn = ((PF4_C59C *)pkt)->x1;
                            } else {
                                mn = ((PF4_C59C *)pkt)->x0;
                                mx = ((PF4_C59C *)pkt)->x1;
                            }
                            if (((PF4_C59C *)pkt)->x2 > mx) mx = ((PF4_C59C *)pkt)->x2;
                            else if (((PF4_C59C *)pkt)->x2 < mn) mn = ((PF4_C59C *)pkt)->x2;
                            if (((PF4_C59C *)pkt)->y0 > ((PF4_C59C *)pkt)->y1) {
                                my = ((PF4_C59C *)pkt)->y0;
                                mny = ((PF4_C59C *)pkt)->y1;
                            } else {
                                mny = ((PF4_C59C *)pkt)->y0;
                                my = ((PF4_C59C *)pkt)->y1;
                            }
                            if (((PF4_C59C *)pkt)->y2 > my) my = ((PF4_C59C *)pkt)->y2;
                            else if (((PF4_C59C *)pkt)->y2 < mny) mny = ((PF4_C59C *)pkt)->y2;
                            gte_stflg(&g.flag);
                            if (!(g.flag & 0x7F85E000)) {
                                gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                gte_stsxy((long *)&((PF4_C59C *)pkt)->x3);
                                if (((PF4_C59C *)pkt)->x3 < mn) mn = ((PF4_C59C *)pkt)->x3;
                                else if (mx < ((PF4_C59C *)pkt)->x3) mx = ((PF4_C59C *)pkt)->x3;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (((PF4_C59C *)pkt)->y3 < mny) mny = ((PF4_C59C *)pkt)->y3;
                                    else if (my < ((PF4_C59C *)pkt)->y3) my = ((PF4_C59C *)pkt)->y3;
                                    if (my >= -0x78 && mny < 0x79) {
                                        s32 za, zb;
                                        u32 *otp;
                                        zb = g.sz2;
                                        if (zb < g.sz3) zb = g.sz3;
                                        za = g.sz0;
                                        if (za < g.sz1) za = g.sz1;
                                        if (za < zb) za = zb;
                                        g.opz = za;
                                        if (code != 0) g.opz = za + 0x200;
                                        ((PF4_C59C *)pkt)->rgbc = prim->w0;
                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
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
                            gte_stflg(&g.flag);
                            if (!(g.flag & 0x7F85E000)) {
                                gte_stsxy(&tmpxy[3]);
                                gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                if (tmpxy[0].vx > tmpxy[1].vx) {
                                    mx = tmpxy[0].vx;
                                    mn = tmpxy[1].vx;
                                } else {
                                    mn = tmpxy[0].vx;
                                    mx = tmpxy[1].vx;
                                }
                                if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                if (tmpxy[3].vx > mx) mx = tmpxy[3].vx;
                                else if (tmpxy[3].vx < mn) mn = tmpxy[3].vx;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    if (tmpxy[3].vx > my) my = tmpxy[3].vx;
                                    else if (tmpxy[3].vx < mny) mny = tmpxy[3].vx;
                                    if (my >= -0x78 && mny < 0x79) {
                                        s32 za, zb;
                                        u32 *otp;
                                        u32 *tp;
                                        u32 uvw;
                                        gte_avsz4();
                                        zb = g.sz2;
                                        if (zb < g.sz3) zb = g.sz3;
                                        za = g.sz0;
                                        if (za < g.sz1) za = g.sz1;
                                        if (za < zb) za = zb;
                                        g.opz = za;
                                        if (code != 2) g.opz = za + 0x200;
                                        *(u32 *)&((PFT4_C59C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x3 = *(u32 *)&tmpxy[3];
                                        tp = (u32 *)prim->w0;
                                        ((PFT4_C59C *)pkt)->rgbc = tp[0];
                                        ((PFT4_C59C *)pkt)->uvc0 = tp[1];
                                        ((PFT4_C59C *)pkt)->uvp1 = tp[2];
                                        uvw = tp[3];
                                        ((PFT4_C59C *)pkt)->uv2 = uvw;
                                        ((PFT4_C59C *)pkt)->uv3 = uvw >> 16;
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
                prim++;
            }
        }
    }
    D_800A5E60 = pkt;
}


#include "common.h"

/* Declarations conformed to the fleet/engine_core canon (engine_core.h:3695, :3797,
 * :3794, :3800, :3833, :3836, :108) and to this TU's own existing spellings
 * (ov_SC01_080_jr_8017AE2C.c:2206 func_8004787C, :2470 D_800B9A02, :3379 RotTransPers).
 * The vertex struct is BLOCK-scope on purpose: engine_types.h already typedefs a
 * file-scope `SVEC`, so a second file-scope definition would be a C89 redefinition. */
extern void func_8012E32C(void);
extern s32 func_8004787C(s32 a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void *func_80010A08(s32);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32 arg0, s32 arg1);
extern u32 D_80186FF8[];
extern s32 D_800A651C;
extern s16 D_800B9A02;

void func_8017D468(void* p)
{
    struct { s16 vx, vy, vz, pad; } v[4];
    u16 base[3];
    s32 buf[2];
    s32 sp40;
    s32 sp44;
    s32 A;
    s32 rs, i, ang, k, d, r;
    u32 *prim;

    func_8012E32C();
    rs = func_8004787C((*(s32 *)(p + 0x1C) * 0x800) / 30);
    base[0] = *(u16 *)(p + 6);
    base[1] = *(u16 *)(p + 0xA);
    A = (rs << 8) >> 12;
    base[2] = *(u16 *)(p + 0xE);
    ang = *(s32 *)(p + 0x1C) << 4;
    i = 0;
    do {
        func_8012B0B4((unsigned int *)buf, ang, 0x20);
        k = rs * 3 + 0x1000;
        d = buf[0];
        v[0].vx = base[0] + d;
        v[0].vy = base[1];
        v[0].vz = base[2] + (d >> 16);
        v[2].vx = base[0] + (((s16)d * k) >> 12);
        v[2].vy = base[1] - A;
        v[2].vz = base[2] + (((d >> 16) * k) >> 12);
        func_8012B0B4((unsigned int *)buf, ang + 0x2AA, 0x20);
        d = buf[0];
        v[1].vx = base[0] + d;
        v[1].vy = base[1];
        v[1].vz = base[2] + (d >> 16);
        v[3].vx = base[0] + (((s16)d * k) >> 12);
        v[3].vy = base[1] - A;
        v[3].vz = base[2] + (((d >> 16) * k) >> 12);
        prim = (u32 *)func_80010A08(0x24);
        prim[1] = D_80186FF8[i];
        prim[3] = D_80186FF8[i + 1];
        *((u8 *)prim + 7) = 0x3A;
        prim[7] = 0;
        prim[5] = 0;
        prim[0] = 0x8000000;
        r = RotTransPers((s32)&v[0], (s32)(prim + 2), &sp40, &sp44);
        RotTransPers((s32)&v[1], (s32)(prim + 4), &sp40, &sp44);
        RotTransPers((s32)&v[2], (s32)(prim + 6), &sp40, &sp44);
        RotTransPers((s32)&v[3], (s32)(prim + 8), &sp40, &sp44);
        AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + r * 4, prim);
        func_8012E28C(r, 1);
        i++;
        ang = ang + 0x2AA;
    } while (i < 6);
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017D72C);

#include "common.h"

/* @class: schedule
 * @stuck: none - MATCH (174 ins).
 * Key lever: the three global accumulators MUST use THREE SEPARATE pointer
 * locals (p1/p2/p3), not one reassigned `p`. With one pseudo holding all three
 * addresses, alias.c cannot record reg_base_value (REG_N_SETS > 1), the three
 * blocks become mutually memory-dependent, the `la` insn's sched1 priority
 * becomes the longest in the block and it is hoisted ~11 slots too early.
 * One set per pointer => each base resolves to its own SYMBOL_REF and the
 * schedule matches. (Writing `D_801C5AA8 += x` directly gives the %lo-folded
 * lui+lw / lui+sw form, which is a different shape and one insn longer.)
 * Tail: the 0x76>0 test is written inverted (<= 0 arm first) so the big block
 * is the fall-through-to-epilogue block, as in the target.
 */

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8017DBF4(void *arg0);

/* 16.16 world-scroll accumulators; the *AAA/*AAE/*AB2 aliases are the HIGH
   halfwords of the same three words (little-endian +2).
   RECONCILIATION (§183 STRUCT-view-cast): the AAA/AAE/AB2 spellings are the
   array form owned by the sibling draft func_8017D72C, where `D_801C5AAA[0] =`
   is LOAD-BEARING (ARRAY_REF => MEM_IN_STRUCT_P kills sched.c:817's
   true_dependence drop clause).  Adopting the array DECL here is free, but
   reading them as `D_801C5AAA[0]` is NOT: it makes these loads in-struct too
   and shifts this function's schedule (measured: reconcile_slate reverted it).
   Reading through `*(u16 *)D_801C5AAA` keeps the declaration compatible while
   the INDIRECT_REF operand stays a NOP_EXPR (not a PLUS_EXPR), so the loads
   stay non-struct exactly as with the old `extern u16 D_801C5AAA;` scalar --
   and the cast also restores the target's `lhu`.  Do NOT "simplify" these
   three casts back to subscripts. */
extern s32 D_801C5AA8;
extern s16 D_801C5AAA[];
extern s32 D_801C5AAC;
extern s16 D_801C5AAE[];
extern s32 D_801C5AB0;
extern s16 D_801C5AB2[];

void func_8017D93C(s32 arg0) {
    extern s32 D_80186FB0[];
    extern u8 D_80186F6C;
    extern u8 D_80186F5C;

    u16 in[4];   /* sp+0x10 */
    u16 out[4];  /* sp+0x18 */
    s32 *p1;
    s32 *p2;
    s32 *p3;
    s32 t;
    s32 o;
    s32 base;
    s32 idx;
    u16 *dst;

    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x48) = *(s16 *)(arg0 + 0xDC);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x50) = *(s16 *)(arg0 + 0xDE);
    in[0] = (*(s32 *)(arg0 + 0x1C) & 1) << 2;
    in[2] = 0;
    in[1] = 0;
    func_8012F214(arg0, (s32)&in[0], (s32)&out[0]);

    *(u16 *)(arg0 + 6) = out[0];
    *(u16 *)(arg0 + 0xE) = out[2];
    *(s16 *)(arg0 + 0x98) = 0;
    base = *(s32 *)(*(s32 *)(arg0 + 0x90));
    idx = *(s16 *)(arg0 + 0xFC);
    *(s32 *)(arg0 + 0x10) += *(s32 *)(arg0 + 0x44);
    *(s32 *)(arg0 + 0x14) += *(s32 *)(arg0 + 0x48);
    *(s32 *)(arg0 + 0x18) += *(s32 *)(arg0 + 0x4C);

    p1 = &D_801C5AA8;
    *p1 += *(s32 *)(arg0 + 0x10);
    p2 = &D_801C5AAC;
    *p2 += *(s32 *)(arg0 + 0x14);
    p3 = &D_801C5AB0;
    *p3 += *(s32 *)(arg0 + 0x18);

    dst = (u16 *)(base + idx * 12);
    dst[0] = *(u16 *)D_801C5AAA - in[0];
    dst[1] = *(u16 *)D_801C5AAE;
    dst[2] = *(u16 *)D_801C5AB2 - in[2];

    if (*(s32 *)(arg0 + 0x1C) >= 0xB) {
        o = func_8012C588(0x24, arg0);
        if (o != 0) {
            in[0] = dst[0];
            in[1] = dst[1];
            in[2] = dst[2];
            func_8012F214(arg0, (s32)&in[0], (s32)&out[0]);
            *(u16 *)(o + 6) = out[0];
            *(u16 *)(o + 0xA) = out[1];
            *(u16 *)(o + 0xE) = out[2];
        }
    }

    if (func_8012BEE8(arg0) != 0) {
        if (*(s16 *)(arg0 + 0x76) <= 0) {
            if (*(s16 *)(arg0 + 0x70) == 4) {
                func_8012C218((void *)arg0);
            } else {
                func_8017DBF4((void *)arg0);
            }
        } else {
            ((void (*)(s32, s32))func_8012A828)(arg0, D_80186FB0[*(s16 *)(arg0 + 0x76)]);
            *(s16 *)(arg0 + 2) = 1;
            if (*(s16 *)(arg0 + 0x70) == 4) {
                *(s32 *)(arg0 + 0x58) = (s32)&D_80186F6C;
            } else {
                *(s32 *)(arg0 + 0x58) = (s32)&D_80186F5C;
            }
            *(u32 *)(arg0 + 0x58) |= 0x60000000;
            t = *(s32 *)(arg0 + 0x20);
            *(u16 *)(t + 0x1C) = 0x1C00;
            *(u16 *)(t + 0x1A) = 0x1C00;
            *(u16 *)(t + 0x18) = 0x1C00;
            *(u16 *)(arg0 + 0x5E) = 0;
            *(u16 *)(arg0 + 0x5C) |= 0x8800;
            *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 0xDC);
            *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0xDE);
        }
    }
}



extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_80183884;
extern M2C_UNK D_801891AC;

void func_8017DBF4(void *arg0) {
    void *temp_v1;

    func_8001C214(M2C_FIELD(arg0, void **, 0x20), &D_801891AC);
    func_8012A828(arg0, &D_80183884);
    M2C_FIELD(arg0, s16 *, 2) = 3;
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0xDC);
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(arg0, u16 *, 0xDE);
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) & 0x77FF);
    M2C_FIELD(temp_v1, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x2C) & 0xFFEF);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
}



// @class: schedule
// @stuck: none — MATCH (pending byte-gate); pure store sequence, gcc -O2 schedules a0/a1 materialization

extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80174784(void);
extern M2C_UNK D_80183884;

void func_8017DC78(int param_1) {
    unsigned short uVar1;

    func_8012A828(param_1, &D_80183884);
    *(short *)(param_1 + 2) = 4;
    *(short *)(param_1 + 0x34) = 0;
    *(int *)(param_1 + 0x1c) = 0x1e;
    uVar1 = *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *(short *)(param_1 + 0xe8) = 0;
    *(int *)(param_1 + 0xe0) = 0x400000;
    *(int *)(param_1 + 0xe4) = 0;
    *(short *)(param_1 + 0xea) = uVar1;
    func_8002D4C8(0x49e, 0);
    func_8002D4C8(0x4a2, 0);
    func_80174784();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32, s32, s32);
extern void func_8012A828(s32 a0, void *a1);


void func_8017DCF8(s32 arg0) {

    extern u8 D_80188970;
    extern u8 D_80186FC4;
    extern s32 D_80186FB0[];
    extern u8 D_80186F6C;
    extern u8 D_80186F5C;
    register s32 param_1 __asm__("$16") = arg0;
    register s32 iVar1 __asm__("$17");
    s32 ret;
    s32 iVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = ret;
    iVar1 = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001C214)(iVar1, &D_80188970);
        func_8001D0E8(iVar1, 0x104, 0x190);
        *(u16 *)(iVar1 + 0x1c) = 0x1c00;
        *(u16 *)(iVar1 + 0x1a) = 0x1c00;
        *(u16 *)(iVar1 + 0x18) = 0x1c00;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0x10;
        *(u16 *)(param_1 + 0x76) = 4;
        *(s32 *)(param_1 + 0x78) = (s32)&D_80186FC4;
        *(u16 *)(param_1 + 0xdc) = *(u16 *)(param_1 + 6);
        *(u16 *)(param_1 + 0xde) = *(u16 *)(param_1 + 0xe);
        ((void (*)(s32, s32))func_8012A828)(param_1, D_80186FB0[*(s16 *)(param_1 + 0x76)]);
        *(u16 *)(param_1 + 2) = 1;
        if (*(s16 *)(param_1 + 0x70) == 4) {
            *(s32 *)(param_1 + 0x58) = (s32)&D_80186F6C;
        } else {
            *(s32 *)(param_1 + 0x58) = (s32)&D_80186F5C;
        }
        iVar2 = *(s32 *)(param_1 + 0x20);
        *(u32 *)(param_1 + 0x58) = *(u32 *)(param_1 + 0x58) | 0x60000000;
        *(u16 *)(iVar2 + 0x1c) = 0x1c00;
        *(u16 *)(iVar2 + 0x1a) = 0x1c00;
        *(u16 *)(iVar2 + 0x18) = 0x1c00;
        *(u16 *)(param_1 + 0x5e) = 0;
        *(u16 *)(param_1 + 0x5c) = *(u16 *)(param_1 + 0x5c) | 0x8800;
        *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 0xdc);
        *(u16 *)(param_1 + 0xe) = *(u16 *)(param_1 + 0xde);
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold; (unsigned)(field-1)<2 forces sltiu not slti)

extern void func_8017D72C();
extern void (*D_80187028[])();

void func_8017DE38(int param_1)
{
    if (((unsigned int)(*(unsigned short *)(param_1 + 2) - 1) < 2) &&
        ((*(unsigned short *)(param_1 + 0x5c) & 1) != 0)) {
        func_8017D72C();
    } else {
        D_80187028[*(unsigned short *)(param_1 + 2)]();
    }
}


#include "common.h"

/* Declarations copied verbatim from src/ov_SC01_080/ov_SC01_080_jr_8017AE2C.c (law 2) */
extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_80183884;

/* new to this TU */
extern void func_8012B21C(void *a0);
extern s32 D_8018703C[];

void func_8017DEB0(s32 arg0) {
    s32 ret;
    s32 obj;
    s32 base;
    s32 ang;
    s32 v;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4((void *)arg0);
    } else {
        func_8001C214(*(s32 *)(arg0 + 0x20), D_8018703C[rand() % 3]);
        if (*(s16 *)(arg0 + 0x70) != 0) {
            s32 addr = arg0 + 0x24;
            ang = -*(s16 *)(arg0 + 0xE);
            base = ang + 0x400;
            *(s16 *)(arg0 + 0x2A) = -2;
            *(s16 *)(arg0 + 0x24) = base * 48 / 2048;
            *(s16 *)(arg0 + 0x26) = base * 96 / 2048;
            *(s16 *)(arg0 + 0x28) = base / 64;
            obj = *(s32 *)(arg0 + 0x20);
            *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x80;
            *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80) = addr;
        }
        obj = *(s32 *)(arg0 + 0x20);
        *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x10;
        obj = *(s32 *)(arg0 + 0x20);
        *(u16 *)(obj + 0x1C) = 0x2000;
        *(u16 *)(obj + 0x1A) = 0x2000;
        *(u16 *)(obj + 0x18) = 0x2000;
        func_8012A828(arg0, &D_80183884);
        *(s16 *)(arg0 + 2) = 1;
        func_8012B21C((void *)arg0);
        *(s32 *)(arg0 + 0x48) = 0x18000;
        v = rand() << 4;
        if ((rand() & 1) == 0) {
            v = -v;
        }
        *(s32 *)(arg0 + 0x10) = v;
        v = rand() << 4;
        if ((rand() & 1) == 0) {
            v = -v;
        }
        *(s32 *)(arg0 + 0x18) = v;
        if (*(s16 *)(arg0 + 0x70) == 0) {
            *(s32 *)(arg0 + 0x14) = -(rand() << 4);
        } else {
            *(s32 *)(arg0 + 0x14) = -0x80000 - (rand() << 5);
        }
        *(s32 *)(arg0 + 0x1C) = 0x32;
    }
}



extern void (*D_80187050[])(void);

void func_8017E0A4(void *a0) {
    D_80187050[*(u16 *)((s32)a0 + 0x2)]();
}



extern Blk8 D_80187014;

void func_8017E0E0(s32 a0) {
    if (*(s16 *)((s32)a0 + 0x70) == 4) {
        *(Blk8 *)((s32)a0 + 0x50) = D_80187014;
    }
}



// @class: struct
// @stuck: none — MATCH; int *p=&D_801270DC + deref for both load AND store forces addiu-base in $s1 (callee-saved), reused via 0x0($s1) — direct global ref re-materializes lui per access
extern void func_8012BD14(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017DC78(int param_1);

extern int D_801270DC;
extern s32 D_80126D50;

void func_8017E124(int param_1) {
    int v;
    int *p = &D_801270DC;

    if (*p == 0) {
        if (((int (*)(int))func_8012BD14)(param_1) < 0x4001) {
            v = func_8012E544(0x161);
            if (v != 0) {
                *(short *)(v + 0xfc) = 1;
                *(short *)(v + 0xfe) = 3 - *(short *)(param_1 + 0x70);
            }
            *p = 1;
            *(int *)(param_1 + 0x1c) = 0x1e;
        }
    } else {
        ((void (*)(int))func_8012BEE8)(param_1);
        if (*(int *)(param_1 + 0x1c) == 0 && D_80126D50 == 0 &&
            ((int (*)(int))func_8012BD14)(param_1) < 0x241) {
            func_8017DC78(param_1);
        }
    }
}



// @class: remat
// @stuck: none — MATCH. Key idiom: D_801270C8 read+write via a pointer var (s32 *p = &D_801270C8; *p+=1; *p>=4) forces gcc to materialize the symbol address ONCE (lui+addiu %lo into one reg) and reuse it for both lw and sw, vs two separate %lo-folded lui's from `D_801270C8 += 1`. Also 0x34 field is lhu (u16) not lh.

extern s32 D_801270C8;
extern s32 D_801270CC;
extern u8 D_80189450;
extern M2C_UNK D_80183884;

extern void func_8017D468(void *arg0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801747AC(s32 a0);

void func_8017E1FC(s32 arg0) {
    s32 temp;
    s32 *p;

    if (*(u16 *)(arg0 + 0x34) == 0) {
        temp = *(s32 *)(arg0 + 0xE4) + *(s32 *)(arg0 + 0xE0);
        *(s32 *)(arg0 + 0xE8) = *(s32 *)(arg0 + 0xE8) + temp;
        *(s32 *)(arg0 + 0xE4) = temp;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = *(s16 *)(arg0 + 0xEA);
        func_8017D468((void *)arg0);
        if (((s32 (*)(void *))func_8012BEE8)((void *)arg0) != 0) {
            *(s16 *)(arg0 + 0x34) = 1;
            ((void (*)(s32, void *))func_8001C214)(*(s32 *)(arg0 + 0x20), &D_80189450);
            ((void (*)(void *, void *))func_8012A828)((void *)arg0, &D_80183884);
            ((void (*)(void))func_801747AC)();
            p = &D_801270C8;
            *p += 1;
            if (*p >= 4) {
                D_801270CC = 2;
            }
        }
    }
}



// @class: plumbing
// @stuck: none — MATCH (51 ins; key lever: §3-T4 branch-polarity invert >=0x30 → OR-block falls through, AND-block is branch target with lui hoisted to delay slot)

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8017E2C8(int param_1)
{
    int iVar1;

    ((void (*)(void))func_8012AD80)();
    if (*(int *)(param_1 + 0x1c) >= 0x30) {
        *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) =
            *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) | 0x80000000;
    } else {
        *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) =
            *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) & 0x7fffffff;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) + 0x17;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x43;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x58;
    iVar1 = func_8012BEE8(param_1);
    if (iVar1 != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
    return;
}


extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s16 D_80126970;
extern s16 D_80126972;
extern s16 D_80126974;
extern u8 D_80126948[];
extern void func_8017E578(void *a0);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);

void func_8017E394(void) {
    D_80126954 = 0x1F4;
    D_8012695C = 0x2BC;
    D_80126968 = 0x38;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x8C;
    D_80126972 = -0x8C;
    D_8012697A = 0;
    D_80126970 = 0;
    D_80126974 = 0;
    func_8012A018((s32)func_8017E578, 0);
    func_8017E578(D_80126948);
    func_8012A094((s32)D_80126948);
}


void func_8017E448(s32 arg0) {
    extern s32 func_8012B6D4(s16 *a0, s16 *a1);
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8017E578(void *a0);
    extern u8 D_80126948[];
    extern u8 D_80126B5C;
    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    s32 arr[3];

    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4EE;
    arr[2] = 0;
    arr[1] = 0;
    arr[0] = 0;
    D_80126968 = 0x120;
    D_8012696A = func_8012B6D4((s16 *)&D_80126B5C, (s16 *)arr);
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E578, 1);
    func_8017E578(D_80126948);
}


void func_8017E4F4(void) {
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8017E578(void *a0);
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x12C;
    D_8012695C = 0x190;
    D_80126968 = 0;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x40;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E578, 2);
    func_8017E578(D_80126948);
}



extern void (*D_80189458[])(void);

void func_8017E578(void *a0) {
    D_80189458[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017E5B4(s32 a0) {
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 arr[3];
    s32 v0;
    s32 s0 = a0;
    v0 = ratan2(*(s16 *)&D_80126B5E, *(s16 *)&D_80126B66);
    *(s16 *)(s0 + 0x22) = (s16)(v0 & 0xFFF);
    arr[0] = D_80126B5E;
    arr[1] = D_80126B62;
    arr[2] = D_80126B66;
    func_8017E8A0(s0, arr);
    func_8017EA68(s0);
}


extern s32 D_80189464;
extern s16 D_80126ADA;
extern s16 D_80126ADE;
extern s16 D_80126AE2;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8017E8A0(s32 a0, s32 a1);
extern s32 func_8017EC48(s32 a0);

void func_8017E630(s32 a0)
{
    s32 *s1;
    s32 x;
    u16 buf[3];

    x = func_8004787C(*(s16 *)(a0 + 0x22));
    s1 = &D_80189464;
    *(s16 *)(a0 + 0x2E) = -x * *s1 / 4096;
    x = func_80047948(*(s16 *)(a0 + 0x22));
    *(s16 *)(a0 + 0x32) = -x * *s1 / 4096;

    buf[0] = D_80126B5E;
    buf[1] = D_80126B62;
    buf[2] = D_80126B66;
    func_8017E8A0(a0, (s32)&buf);

    *(s32 *)(a0 + 0x48) = D_80126ADA;
    *(s32 *)(a0 + 0x4C) = D_80126ADE;
    *(s32 *)(a0 + 0x50) = D_80126AE2;
    func_8017EC48(a0);
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017E724);

#include "common.h"

/* Reading source: matched twin ov_SC01_084:func_8017DECC (seed_sim 0.9636).
   Target differs from the twin in that param_2 here is a POINTER to a
   3x s16 vector (used only for mtx.t[]), not a scalar added into rot.vy;
   and the rotation args are passed straight from *(s16*)(param_1+off)
   with no intermediate "rot" struct (the asm has no stores into a rot
   local, so none is declared here). */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_8017E8A0;   /* 0x20; .t @ +0x14 */
typedef struct { s16 vx, vy, vz, pad; } Sv_8017E8A0;      /* 0x08 */

void func_8017E8A0(s32 param_1, s32 param_2)
{
    Mtx_8017E8A0 mtx;   /* sp+0x10 */
    Sv_8017E8A0 vec;    /* sp+0x30 */
    Sv_8017E8A0 out;    /* sp+0x38 */

    *(s32 *)(param_1 + 8) = (s16)func_80012C6C(*(s16 *)(param_1 + 8), *(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = func_80012ABC(*(s16 *)(param_1 + 0x1a), *(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = func_80012ABC(*(s16 *)(param_1 + 0x1c), *(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = func_80012C6C(*(s16 *)(param_1 + 0x2a), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = func_80012C6C(*(s16 *)(param_1 + 0x2c), *(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)(s16)D_80126B5E;
    *(s32 *)(param_1 + 0x4c) = (s32)*(s16 *)(param_1 + 0x2a) + (s32)(s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2c) + (s32)(s16)D_80126B66;

    func_80013F3C((s32)&mtx);
    func_800123F0((s32)&mtx, (s32)*(s16 *)(param_1 + 0x1c));
    func_80012558((s32)&mtx, (s32)*(s16 *)(param_1 + 0x1a));
    func_800126C4((s32)&mtx, (s32)*(s16 *)(param_1 + 0x18));

    mtx.t[0] = (s32)*(s16 *)(param_1 + 0x28) + (s32)*(s16 *)(param_2 + 0);
    mtx.t[1] = (s32)*(s16 *)(param_1 + 0x2a) + (s32)*(s16 *)(param_2 + 2);
    mtx.t[2] = (s32)*(s16 *)(param_1 + 0x2c) + (s32)*(s16 *)(param_2 + 4);

    vec.vx = 0;
    vec.vy = 0;
    vec.vz = (s16)*(s32 *)(param_1 + 0x10);

    func_8012F14C((s32)&mtx, (s32)&vec, (s32)&out);

    *(s32 *)(param_1 + 0x3c) = out.vx;
    *(s32 *)(param_1 + 0x40) = out.vy;
    *(s32 *)(param_1 + 0x44) = out.vz;
}


#include "common.h"

extern s32 func_80013200(s32 *a0, s32 *a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];

void func_8017EA68(s32 param_1) {
    s32 v1[3];
    s32 v2[3];
    s32 dist;
    s32 angle;
    s32 v0;

    v1[0] = *(s32 *)(param_1 + 0x48);
    v1[1] = 0;
    v1[2] = *(s32 *)(param_1 + 0x50);
    v2[0] = *(s32 *)(param_1 + 0x3C);
    v2[1] = 0;
    v2[2] = *(s32 *)(param_1 + 0x44);
    dist = func_80013200(v1, v2);
    angle = ratan2(*(s32 *)(param_1 + 0x4C) - *(s32 *)(param_1 + 0x40), dist);
    if (angle >= 0x801) {
        angle = 0x1000 - angle;
    }
    v0 = angle * 300 / 1024 + 0xC8;
    D_800B9ABA[0] = (s16)v0;

    angle = ratan2(*(s32 *)(param_1 + 0x48) - *(s32 *)(param_1 + 0x3C),
                    *(s32 *)(param_1 + 0x50) - *(s32 *)(param_1 + 0x44));
    v0 = angle * 640 / 4096 + 0x140;
    D_800B9AB8[0] = (s16)v0;
}


extern s32 func_80013200(s32 *a0, s32 *a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];

void func_8017EB64(s32 param_1) {
    s32 v1[3];
    s32 v2[3];
    s32 dist;
    s32 angle;
    s32 v0;

    v1[0] = *(s32 *)(param_1 + 0x48);
    v1[1] = 0;
    v1[2] = *(s32 *)(param_1 + 0x50);
    v2[0] = *(s32 *)(param_1 + 0x3C);
    v2[1] = 0;
    v2[2] = *(s32 *)(param_1 + 0x44);
    dist = func_80013200(v1, v2);
    angle = ratan2(*(s32 *)(param_1 + 0x4C) - *(s32 *)(param_1 + 0x40), dist);
    if (angle >= 0x801) {
        angle = 0x1000 - angle;
    }
    v0 = angle * 300 / 1024 + 0xC8;
    D_800B9ABA[0] = (s16)v0;

    v0 = *(s32 *)(param_1 + 0x48) * 640 / 4096;
    D_800B9AB8[0] = (s16)v0;
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017EC48);


extern void (*D_801894B8[])(void);

void func_8017ED0C(void *a0) {
    D_801894B8[*(u8 *)((s32)a0 + 0x15)]();
}



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017EEE0(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017ED48(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017EEE0, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017ED98(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_801894C0[])(void);

void func_8017EDBC(void *a0) {
    D_801894C0[*(u8 *)((s32)a0 + 0x15)]();
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8017F184(void *arg0);

s32 func_8017EDF8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_8017F184, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 10;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017EE44(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(2);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017EEC0(void) {
        func_800D1EBC();
    }



extern void (*D_80189638[])(void);

void func_8017EEE0(void *a0) {
    D_80189638[*(u8 *)((s32)a0 + 0x214)]();
}


















extern void func_8016F398(void);
extern void func_80171B44(s32 *a0);
void func_8017EF1C(u8 *a0)
{
  s32 p = (s32) a0;
  ((void (*)(s32 *)) func_8016F398)((s32 *) ((s32) a0));
  a0++;
  a0--;
  *((u8 *) (((s32) a0) + 0x214)) += 1;
  ((s32 (*)(s32)) func_80171B44)(p);
}

extern s32 func_80171B4C(s32 a0, s32 a1);
extern s32 func_800CF854(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8014706C(void *a0);
extern s32 func_8013767C(s32 a0);
extern u8 D_800D5A34[];

void func_8017EF58(int param_1)
{
    if (func_80171B4C(param_1, 0x1E) != 0) {
        if (((int (*)(void))func_800CF854)() != 0) {
            *(char *)(param_1 + 0x214) = 3;
        } else {
            ((int (*)(int, int))func_80154274)(param_1, (int)&D_800D5A34);
            ((int (*)(int))func_8014706C)(param_1);
            *(int *)(param_1 + 0x198) = func_8013767C(*(int *)(param_1 + 0x198));
            *(char *)(param_1 + 0x214) = *(char *)(param_1 + 0x214) + 1;
            *(short *)(param_1 + 0x20c) = 0;
        }
    }
}


extern s32 func_8016F410(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80139914(s32 a0);
extern s32 func_801399F0(s32 a0);
extern void func_80147060(u8 *a0);

extern u8 D_800D599C[];
extern u8 D_801894CC[];
extern u8 D_801895CC[];
extern u8 D_8018954C[];
extern u8 D_800D5A34[];

void func_8017EFDC(int param_1) {
    switch (*(s16 *)(param_1 + 0x20C)) {
    case 0:
        if (func_8016F410(0) != 0) {
            *(u16 *)(param_1 + 0x20C) = *(u16 *)(param_1 + 0x20C) + 1;
            func_80154274((s32 *)param_1, (s32)&D_800D599C);
        }
        break;
    case 2:
        if (func_8016F410(1) != 0) {
            func_80154274((s32 *)param_1, (s32)&D_801894CC);
            *(u16 *)(param_1 + 0x20E) = 0;
            *(u16 *)(param_1 + 0x20C) = *(u16 *)(param_1 + 0x20C) + 1;
        }
        break;
    case 3:
        if (((*(u16 *)(param_1 + 0xB8) & 0x8000) != 0) && (*(s16 *)(param_1 + 0x20E) == 0)) {
            *(u16 *)(param_1 + 0x20E) = 1;
            func_80154274((s32 *)param_1, (s32)&D_801895CC);
        }
        if (func_8016F410(2) != 0) {
            func_80154274((s32 *)param_1, (s32)&D_8018954C);
            *(u16 *)(param_1 + 0x20C) = *(u16 *)(param_1 + 0x20C) + 1;
        }
        break;
    case 1:
    case 4:
        if ((*(u16 *)(param_1 + 0xB8) & 0x8000) != 0) {
            func_80154274((s32 *)param_1, (s32)&D_800D5A34);
            *(u16 *)(param_1 + 0x20C) = *(u16 *)(param_1 + 0x20C) + 1;
        }
        break;
    case 5:
        break;
    }

    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        func_80147060((u8 *)param_1);
        *(u8 *)(param_1 + 0x214) = *(u8 *)(param_1 + 0x214) + 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH (param_1 survives across func_8016F0E4 → lands in $s0; passed to func_80165770)

extern void func_8016F0E4(void);
extern void func_80165770(void);
extern void func_80175414(s32 _arg0);

void func_8017F14C(s32 param_1)
{
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(param_1);
    ((void (*)(void))func_80175414)();
}



extern void (*D_80189648[])(void);

void func_8017F184(void *a0) {
    D_80189648[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171B44(s32 *a0);
extern void func_8017F204(s32 a0);

void func_8017F1C0(s32 a0)
{
    *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0;
    func_80171B44((s32 *)a0);
    func_8017F204(a0);
}



// @class: plumbing
// @stuck: none — MATCH (expected); simple call + conditional u8 increment

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017F204(int param_1)
{
    if (func_80171B4C(param_1, 0x2) != 0) {
        *(unsigned char *)(param_1 + 0x214) += 1;
    }
    return;
}


extern void func_8016F0E4(void);
    void func_8017F248(void) {
        ((s32 (*)(void))func_8016F0E4)();
    }



extern void (*D_80189654[])(void);

void func_8017F268(void *a0) {
    D_80189654[*(u8 *)((s32)a0 + 0x214)]();
}


extern s32 func_80172658(s32 *a0);
extern s32 ratan2(s32 dx, s32 dy);
extern void func_80175454(void);
extern s16 D_80126968;
extern s16 D_80189664[][4];
extern s16 D_80189668[][4];

void func_8017F2A4(s32 *param_1)
{
    s32 idx;
    s16 curx;
    s16 curz;

    if (func_80172658(param_1) != 0) {
        idx = *(s32 *)((s32)param_1 + 0x218);
        curx = *(s16 *)((s32)param_1 + 6);
        curz = *(s16 *)((s32)param_1 + 0xE);
        *(s16 *)((s32)param_1 + 0x20C) = ratan2(curx - D_80189664[idx][0], curz - D_80189668[idx][0]) & 0xFFF;
        *(s16 *)((s32)param_1 + 0x20E) = D_80126968;
        D_80126968 = 0x38E;
        func_80175454();
        *(u8 *)((s32)param_1 + 0x214) = *(u8 *)((s32)param_1 + 0x214) + 1;
    }
}


extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_8013767C(s32 a0);
extern u8 D_8018A6A8[];

void func_8017F344(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), M2C_FIELD(arg0, s16 *, 0x20C), 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if ((temp_v0 << 0x10) == 0) {
        M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_8018A6A8);
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}



extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017F3C0(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017F414);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F458(void) {

    extern s32 D_80189684(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80189684, 0x1000000);
}



extern void (*D_80189690[])(void);

void func_8017F480(void *a0) {
    D_80189690[*(u8 *)((s32)a0 + 0x215)]();
}


extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171928(void *a0);
void func_8017F4BC(s32 a0) {

    extern void *D_80189694;
    if (func_80171AB0(a0, &D_80189694) == 0) {
        func_80171928((void *)a0);
    }
}



extern void (*D_8018A05C[])(void);

void func_8017F500(void *a0) {
    D_8018A05C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C51C(void *a0, s32 a1);
extern M2C_UNK D_801A37A4;
extern M2C_UNK D_801899C4;

typedef struct {
    u8 pad[6];
    u16 v;
    u16 z2;
    u16 z1;
    u8 tail[12];
} Stk;

void func_8017F53C(s32 arg0)
{
    register s32 param_1 __asm__("$16") = arg0;
    s32 ret;
    s32 handle;
    s32 cnt;
    Stk b1;
    Stk bx;
    Stk b2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    handle = ret;
    *(s32 *)((s8 *)param_1 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(handle, (s32)&D_801A37A4);
        func_8001D0E8(handle, 0x7FFF, 0x7FFF);
        func_8012A828(param_1, &D_801899C4);
        *(u8 *)((s8 *)param_1 + 0xFC) = 0;
        b1.v = 0xB;
        b1.z1 = 0;
        b1.z2 = 0;
        func_8012C51C(&b1, (s32)param_1);
        *(s32 *)((s8 *)param_1 + 0xF0) = 0x1C0;
        b2.v = 0x28;
        b2.z1 = 0;
        b2.z2 = 0;
        func_8012C51C(&b2, (s32)param_1);
        bx.v = 0x27;
        bx.z1 = 0;
        bx.z2 = 0;
        func_8012C51C(&bx, (s32)param_1);
        *(s16 *)((s8 *)param_1 + 0x100) = 0x90;
        cnt = *(u16 *)((s8 *)param_1 + 2);
        *(s16 *)((s8 *)param_1 + 0xFE) = 0;
        *(s16 *)((s8 *)param_1 + 0x102) = 0xFF;
        *(s16 *)((s8 *)param_1 + 2) = cnt + 1;
    }
}


void func_8017F638(s32 arg0) {
    volatile u8 sp18[8];
    s32 v1;
    extern s32 D_801270C8;
    extern void func_8017F458(void);
    extern void func_80175454(void);
    extern s32 D_8012718C;
    extern u8 D_801AC738[];
    extern void *D_80189CEC;
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_800D0C48(s32 a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_801806DC(void);

    if (D_801270C8 < 4) {
        return;
    }
    func_8017F458();
    func_80175454();
    v1 = *(s32 *)(arg0 + 0x20);
    *(s16 *)(arg0 + 0xA) = 0x89F;
    *(s32 *)(arg0 + 0xF0) = 0xA5F;
    *(s16 *)(v1 + 0x12) = 0;
    v1 = *(s16 *)(arg0 + 0xA);
    *(s32 *)(arg0 + 0xDC) = 1;
    *(s32 *)(arg0 + 0xE4) = 0x20;
    D_8012718C = v1;
    func_8001C214(*(s32 *)(arg0 + 0x20), D_801AC738);
    func_8001D0E8(*(s32 *)(arg0 + 0x20), 0x800, 0x800);
    func_800D0C48(0);
    func_8002D4C8(0x404, 0);
    func_8012A828(arg0, &D_80189CEC);
    func_801806DC();
    *(u16 *)((s32)arg0 + 2) += 1;
}


#include "common.h"

extern s16 D_80126ADA;
extern s16 D_80126ADE;
extern s16 D_80126AE2;
extern u16 D_800B99DC;
extern u8 D_80183CB4[];
extern void func_8013C9C4(void *a0);
extern void func_8017E448(s32 arg0);

void func_8017F710(s32 arg0) {
    u16 cnt;

    if (--*(s32 *)(arg0 + 0xE4) == 0) {
        *(s32 *)(arg0 + 0xE0) = 0x30;
        *(s32 *)(arg0 + 0xE4) = 0x40;
        func_8017E448(arg0);
        cnt = *(u16 *)(arg0 + 6);
        D_80126ADE = -0x130;
        D_80126ADA = cnt;
        D_80126AE2 = *(u16 *)(arg0 + 0xE);
        (*(u16 *)(arg0 + 2))++;
    } else if (--*(s32 *)(arg0 + 0xDC) == 0) {
        func_8013C9C4(&D_80183CB4);
        *(s32 *)(arg0 + 0xDC) = (D_800B99DC & 7) + 3;
    }
}


#include "common.h"

extern s32 D_80126950;
extern s16 D_80126978;
extern u16 D_800B99DC;
extern s32 D_80127188;
extern s32 D_801C5AB8;
extern u8 D_80183CB4[];
extern void func_8013C9C4(void *a0);

void func_8017F7D0(s32 arg0) {
    s32 radius;
    u16 cnt;

    if (--*(s32 *)(arg0 + 0xE0) == 0) {
        *(u8 *)(arg0 + 0xFC) = 1;
        D_80127188 = 1;
    }
    if (--*(s32 *)(arg0 + 0xE4) == 0) {
        *(s32 *)(arg0 + 0xE4) = 0;
        *(s32 *)(arg0 + 0xE8) = (s32) D_80126978 << 16;
        *(s32 *)(arg0 + 0xEC) = 0;
        radius = D_80126950;
        *(u16 *)(arg0 + 0xDC) = 0;
        *(s32 *)(arg0 + 0xE0) = 2;
        *(u16 *)(arg0 + 0xDE) = radius;
        D_80127188 = 2;
        cnt = *(u16 *)(arg0 + 2);
        D_801C5AB8 = 1;
        *(u16 *)(arg0 + 2) = cnt + 1;
    } else if (--*(s32 *)(arg0 + 0xDC) == 0) {
        func_8013C9C4(&D_80183CB4);
        *(s32 *)(arg0 + 0xDC) = (D_800B99DC & 7) + 3;
    }
}


#include "common.h"


typedef struct {
    u8 pad0[8];
    s32 f08;
    s32 f0C;
    u8 pad10[0x20];
    s16 f30;
} Work_80126948;
extern Blk8 D_801C46E8;
extern u8 D_80126948[];
extern s32 D_8012718C;
extern s32 D_80127188;
extern s32 D_801C5AB8;
extern s16 D_80126ADA;
extern s16 D_80126ADE;
extern s16 D_80126AE2;
extern u16 D_800B99DC;
extern u8 D_80183CB4[];
extern void func_8013C9C4(void *a0);
extern void func_8013BD74(void *a0, void *a1);
extern void func_8013373C(s16 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern int func_8001AAA0(void);
extern s32 D_801C7EE0;
extern s32 D_80193C64;

void func_8017F8C0(s32 arg0) {
    Blk8 buf;
    Work_80126948 *w = &(*(Work_80126948 *)D_80126948);
    s32 radius;
    s32 cnt;
    s32 val;

    buf = *(Blk8 *)&D_801C46E8;
    if (*(s16 *)(arg0 + 0x100) == 0) {
        if (*(s16 *)(arg0 + 0xFE) == 0 && ((s32 (*)(s32))func_8001AAA0)(0x11) != 0) {
            *(u16 *)(arg0 + 0xFE) = 1;
        }
    } else {
        *(s16 *)(arg0 + 0x100) = *(s16 *)(arg0 + 0x100) - 1;
    }
    if (--*(s16 *)(arg0 + 0x102) == 0 && *(s16 *)(arg0 + 0xFE) != 0) {
        func_8002D4C8(0x102, 0);
        *(u16 *)(arg0 + 0xFE) = 2;
    }
    D_8012718C = *(s16 *)(arg0 + 0xA);
    cnt = *(u16 *)(arg0 + 0xA);
    *(s16 *)(arg0 + 0xA) = cnt - 8;
    if ((u32)(cnt - 0x1E1) < 0x1DF) {
        radius = *(s32 *)(arg0 + 0xE8) + 0xCCC00;
        *(s32 *)(arg0 + 0xE8) = radius;
        w->f30 = radius >> 16;
    }
    if (*(s16 *)(arg0 + 0xA) < 0x3B8) {
        *(s32 *)(arg0 + 0xDC) += -0x1AE40;
        *(s32 *)(arg0 + 0xEC) += 0xD;
        w->f0C = *(s16 *)(arg0 + 0xDE);
        w->f08 = w->f0C;
    }
    if (*(s16 *)(arg0 + 0xA) <= 0) {
        *(u16 *)(arg0 + 0xA) = 0;
        func_8013BD74(&D_801C7EE0, &D_80193C64);
        func_8013373C(0);
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x24) = 0;
        func_8002D4C8(4, 0x404);
        func_8002D4C8(0x405, 0);
        D_80127188 = 3;
        *(s32 *)(arg0 + 0xDC) = 0x34;
        *(s32 *)(arg0 + 0xE0) = 0x44;
        (*(u16 *)(arg0 + 2))++;
    } else {
        if (*(s32 *)(arg0 + 0xE4) != 0) {
            D_80126ADA = *(u16 *)(arg0 + 6);
            D_80126AE2 = *(u16 *)(arg0 + 0xE);
            val = *(s32 *)(arg0 + 0xEC) + 0x4E8;
            D_80126ADE = *(u16 *)(arg0 + 0xA) - val;
        } else if (*(s16 *)(arg0 + 0xA) < 0x3B8) {
            *(s32 *)(arg0 + 0xE4) = 1;
            D_80126ADA = *(u16 *)(arg0 + 6);
            D_80126ADE = *(s16 *)(arg0 + 0xA) - 0x4E8;
            D_80126AE2 = *(u16 *)(arg0 + 0xE);
        }
        D_801C5AB8--;
        if (D_801C5AB8 == 0) {
            func_8013C9C4(&D_80183CB4);
            D_801C5AB8 = (D_800B99DC & 7) + 3;
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FB5C(s32 p)
{
    extern int func_8001AAA0(void);
    switch (*(s16 *)(p + 0xFE)) {
    case 0:
        if (((int (*)(s32))func_8001AAA0)(0x11) != 0) {
            *(u16 *)(p + 0xFE) = 1;
        }
        break;
    case 1:
        func_8002D4C8(0x102, 0);
        *(u16 *)(p + 0xFE) += 1;
        break;
    case 2:
        *(u16 *)(p + 2) += 1;
        break;
    }
}



extern Blk8 D_801C46E8;
extern s32 D_80127188;
extern void func_8017E4F4(void);
extern s32 func_8016F0AC(void);
extern void func_80175414(s32);

void func_8017FC04(s32 arg0) {
    Blk8 buf;
    buf = *(Blk8 *)&D_801C46E8;
    if (*(s32 *)(arg0 + 0xE0) < 0x4000) {
        if (--*(s32 *)(arg0 + 0xDC) == 0) {
            D_80127188 = 4;
            func_8017E4F4();
            func_8016F0AC();
            ((void (*)(void))func_80175414)();
        }
        if (--*(s32 *)(arg0 + 0xE0) == 0) {
            *(s32 *)(arg0 + 0xE0) = 0x4000;
            *(s32 *)(arg0 + 0xDC) = 8;
        }
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017FCC0);

extern u16 D_801C7600[];

void func_8017FCFC(u16 *a0) {
    register u16 *p __asm__("$5");
    register s32 i __asm__("$6");
    register s32 c __asm__("$7");
    register u16 *q __asm__("$3");

    p = D_801C7600;
    i = 0;
    c = 0x20;
    q = p + 2;
    do {
        if (*(s16 *)(q + 1) == 0) {
            *(s16 *)(q + 1) = c;
            p[0] = a0[0];
            q[-1] = a0[1];
            q[0] = a0[2];
            return;
        }
        i++;
        q += 4;
        p += 4;
    } while (i < 0x100);
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8017FD64);

extern void (*D_8018A1F8[])(void);

void func_8017FF78(void *a0) {
    D_8018A1F8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017FFB4(s32 arg0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8001D074(s32, s32);
    extern void func_800233CC(void *a0, u16 a1);
    extern void func_8001CD9C(s32 a0, void *a1);
    extern u8 D_801AE2D8;
    extern u8 D_8018A02C;
    extern u8 D_80189974;
    extern s32 D_801C7EC0;

    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18") = arg0;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s2 + 0x20) = v0;
    s0 = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s2);
        return;
    }
    func_8001C214(s0, &D_801AE2D8);
    func_8001D0E8(s0, 0x800, 0x800);
    func_8012A828((void *)s2, &D_8018A02C);
    D_801C7EC0 = 0;
    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
    *(s32 *)(s2 + 0xF4) = s1;
    if (s1 != 0) {
        func_800233CC(&D_80189974, 0x50);
        func_8001CD9C(s1, &D_80189974);
    }
    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
    *(s32 *)(s2 + 0xF8) = s1;
    if (s1 != 0) {
        func_800233CC(&D_80189974, 0x40);
        func_8001CD9C(s1, &D_80189974);
    }
    *(u16 *)(s2 + 0x34) = 0;
    *(s32 *)(s2 + 4) = *(s32 *)(*(s32 *)(s2 + 0x64) + 4);
    *(s32 *)(s2 + 8) = *(s32 *)(*(s32 *)(s2 + 0x64) + 8) - *(s32 *)(*(s32 *)(s2 + 0x64) + 0xF0);
    *(s32 *)(s2 + 0xC) = *(s32 *)(*(s32 *)(s2 + 0x64) + 0xC);
    *(u16 *)(s2 + 2) = *(u16 *)(s2 + 2) + 1;
}



INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801800F4);


extern s32 D_801C7EC0;

void func_80180174(void) {
    D_801C7EC0 = 1;
}


extern void (*D_801899B4[])(void);
extern void (*D_801899BC[])(void);
extern s32 D_8018A200[];

void func_80180188(s32 param_1)
{
    u16 sp10[3];

    func_8012B2CC(param_1);
    func_8012F14C(*(s32 *)(param_1 + 0x20) + 0x34, (s32)D_801899B4, (s32)sp10);
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0x8) = sp10[0];
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0xC) = sp10[2];
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0x10) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10);
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0x12) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *(u16 *)(*(s32 *)(param_1 + 0xF4) + 0x14) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14);
    func_8012F14C(*(s32 *)(param_1 + 0x20) + 0x34, (s32)D_801899BC, (s32)sp10);
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0x8) = sp10[0];
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0xC) = sp10[2];
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0x10) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10);
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0x12) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *(u16 *)(*(s32 *)(param_1 + 0xF8) + 0x14) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14);
    ((void (*)(s32))D_8018A200[*(u16 *)((s32)param_1 + 0x34)])(param_1);
}


void func_801802D8(void *a0) {
    s32 *p1, *q1;
    p1 = *(s32 **)((s32)a0 + 0xF4);
    p1[1] = p1[1] | 0xD0000040;
    q1 = *(s32 **)((s32)a0 + 0xF8);
    q1[1] = q1[1] | 0xD0000040;
    *(s32 *)((s32)a0 + 0xE4) = 0x80;
    *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
}


extern s32 D_801270C8;
extern s32 D_801C7EC0;
extern u8 D_80189974;
extern u8 D_80189975;
extern u8 D_80189976;

void func_80180320(s32 arg0) {
    s32 t;
    s32 p2;
    u16 cnt;

    if (D_801270C8 < 4 && D_801C7EC0 != 0) {
        t = 0x50000040;
        *(s32 *)(*(s32 *)(arg0 + 0xF4) + 4) = t;
        p2 = *(s32 *)(arg0 + 0xF8);
        D_801C7EC0 = 0;
        *(s32 *)(p2 + 4) = t;
        D_80189974 = 0xFF;
        D_80189975 = 0x10;
        D_80189976 = 0x10;
        *(s32 *)(arg0 + 0xE4) = 6;
        cnt = *(u16 *)(arg0 + 0x34);
        *(s32 *)(arg0 + 0xE8) = 0xFF;
        *(u16 *)(arg0 + 0x34) = cnt + 1;
    }
}


extern u8 D_80189974;

void func_801803AC(s32 arg0) {
    if (*(s32 *)(arg0 + 0xE4) == 0) {
        *(s32 *)(arg0 + 0xE8) = *(s32 *)(arg0 + 0xE8) - 0x40;
        if (*(s32 *)(arg0 + 0xE8) <= 0) {
            *(s32 *)(arg0 + 0xE8) = 0;
        }
        D_80189974 = *(s32 *)(arg0 + 0xE8);
        if (*(s32 *)(arg0 + 0xE8) == 0) {
            *(s32 *)(*(s32 *)(arg0 + 0xF4) + 4) = 0xD0000040;
            *(s32 *)(*(s32 *)(arg0 + 0xF8) + 4) = 0xD0000040;
            *(u16 *)(arg0 + 0x34) = 1;
        }
    } else {
        *(s32 *)(arg0 + 0xE4) = *(s32 *)(arg0 + 0xE4) - 1;
    }
}



extern void (*D_8018A20C[])(void);

void func_80180420(void *a0) {
    D_8018A20C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018045C(s32 arg0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, void *a1);
    extern u8 D_801AE850;
    extern u8 D_8018A044;

    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = arg0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }
    func_8001C214(s1, &D_801AE850);
    func_8001D0E8(s1, 0x800, 0x800);
    func_8012A828((void *)s0, &D_8018A044);
    *(s32 *)(s1 + 4) = *(s32 *)(s1 + 4) | 0x40;
    *(s32 *)(s0 + 4) = *(s32 *)(*(s32 *)(s0 + 0x64) + 4);
    *(s32 *)(s0 + 8) = *(s32 *)(*(s32 *)(s0 + 0x64) + 8) - *(s32 *)(*(s32 *)(s0 + 0x64) + 0xF0);
    *(s32 *)(s0 + 0xC) = *(s32 *)(*(s32 *)(s0 + 0x64) + 0xC);
    *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
}


void func_80180528(s32 arg0) {
    s32 *p = (s32 *)(arg0 + 0x64);
    s32 *t = (s32 *)*p;
    *(s32 *)(arg0 + 4) = t[1];
    *(s16 *)(arg0 + 0xA) = *(u16 *)(*p + 0xA) - *(s32 *)(*p + 0xF0);
    *(s32 *)(arg0 + 0xC) = *(s32 *)(*p + 0xC);
}


extern void (*D_8018A214[])(void);

void func_8018055C(void *a0) {
    D_8018A214[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80180598);

extern s32 D_80127190;

void func_80180654(void *a0) {
    if (*(u8 *)(*(s32 *)((s32)a0 + 0x64) + 0xFC) != 0) {
        *(s32 *)((s32)a0 + 0xDC) = 0x60;
        D_80127190 = *(s16 *)((s32)a0 + 0xA);
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
}


extern void func_8012C218(void *a0);
extern s32 D_80127190;

void func_80180694(void *arg0) {
    D_80127190 = *(s16 *)((s32)arg0 + 0xA);
    *(u16 *)((s32)arg0 + 0xA) += 8;
    if (--*(s32 *)((s32)arg0 + 0xDC) == 0) {
        func_8012C218(arg0);
    }
}


extern s32 D_80127188;
extern s32 func_8012C750(s32 a0);

void func_801806DC(void) {
    struct {
        s16 unk00;
        s16 unk02;
        s16 unk04;
        s16 unk06;
        s16 unk08;
        s16 unk0A;
        s16 unk0C;
        s16 unk0E;
        s32 unk10;
    } buf;

    D_80127188 = 0;
    buf.unk06 = 0x72;
    buf.unk04 = 0;
    buf.unk02 = 0;
    buf.unk00 = 0;
    buf.unk0A = 0;
    buf.unk08 = 0;
    buf.unk0E = 0;
    buf.unk10 = 0;
    func_8012C750((s32)&buf);
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80180728);

extern u8 D_801C5D40[];
extern s32 D_80127188;

void func_801808B8(s32 param_1) {
    s16 i;
    u8 *p;
    u8 *q;
    i = 0;
    do {
        p = func_801291C0();
        if (p != 0) {
            *(u16 *)p = 0x19;
            *(u16 *)(p + 0x2C) = 0;
            *(s32 *)(p + 0x34) = (s32)&D_801C5D40 + (*(s16 *)(param_1 + 0xDC) << 5);
            *(s16 *)(param_1 + 0xDC) = *(s16 *)(param_1 + 0xDC) + 1;
            if (*(s16 *)(param_1 + 0xDC) >= 0xC0) {
                *(s16 *)(param_1 + 0xDC) = 0;
            }
        }
        i = i + 1;
    } while (i < 3);
    if (*(s32 *)(param_1 + 0x1C) == 0) {
        func_8012913C(0x14);
        q = func_8012913C(0x14);
        if (q != 0) {
            *(u16 *)(q + 0x2E) = 0x71;
        }
        q = func_8012913C(0x14);
        if (q != 0) {
            *(u16 *)(q + 0x2E) = 0xE3;
        }
        *(s32 *)(param_1 + 0x1C) = 0x10;
        if (D_80127188 != 0) {
            *(s32 *)(param_1 + 0x1C) = 0x60;
            *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
        }
    } else {
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801809E4);

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80180D54);

extern void (*D_8018A22C[])(void);

void func_80180F30(void *a0) {
    D_8018A22C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_8018A240[])(void);

void func_80180F6C(void *a0) {
    D_8018A240[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80180FA8);

extern s32 D_80127190;
extern void func_801292C8(u8 *a0);

void func_80181040(void *a0) {
    u16 v0;
    s32 v1;

    *(u16 *)((s8 *)a0 + 0xA) = D_80127190 - 0x150;
    v1 = *(s32 *)((s8 *)a0 + 0x20);
    v0 = *(u16 *)(v1 + 0x18) + 0x80;
    *(u16 *)(v1 + 0x18) = v0;
    *(u16 *)(v1 + 0x1A) = v0;
    v0 = *(u16 *)((s8 *)a0 + 0x2E) - 1;
    *(u16 *)((s8 *)a0 + 0x2E) = v0;
    if ((s16)v0 == -1) {
        func_801292C8((u8 *)a0);
    }
}


extern void (*D_8018A248[])(void);

void func_801810A8(void *a0) {
    D_8018A248[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801810E4);

extern void (*D_8018A250[])(void);

void func_801813D4(void *a0) {
    D_8018A250[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181410);

extern void (*D_8018A258[])(void);

void func_8018155C(void *a0) {
    D_8018A258[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_8018A264[])(void);

void func_80181598(void *a0) {
    D_8018A264[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801815D4);

extern s32 D_80127190;
extern void D_801C5CC0;

void func_801816E4(void *a0)
{
    s32 *s0 = (s32 *)a0;
    s32 *s1;
    s32 v0;
    s32 v1;

    *(u16 *)((s8 *)s0 + 0x6) = 0;
    v0 = D_80127190;
    s1 = *(s32 **)((s8 *)s0 + 0x20);
    *(u16 *)((s8 *)s0 + 0xE) = 0;
    v0 += -0x154;
    *(u16 *)((s8 *)s0 + 0xA) = v0;
    func_8001CD50((s32)s1, (s32)&D_801C5CC0);

    v0 = -0x7800;
    *(u16 *)((s8 *)s1 + 0x1E) = v0;
    v0 = 0x400;
    *(u16 *)((s8 *)s1 + 0x10) = v0;
    v0 = *(s32 *)((s8 *)s1 + 0x4);
    v1 = 0x50000000;
    v0 |= v1;
    *(s32 *)((s8 *)s1 + 0x4) = v0;

    v0 = *(u16 *)((s8 *)s0 + 0x2);
    v1 = 0x1F;
    *(u16 *)((s8 *)s0 + 0x2E) = v1;
    v0 += 1;
    *(u16 *)((s8 *)s0 + 0x2) = v0;
}


typedef struct { s32 q[16]; } Str_801C5B00;
extern Str_801C5B00 D_801C5B00[];
extern void func_801292C8(u8 *arg0);

void func_80181770(u8 *arg0) {
    u16 sp1E;
    u8 *sp18;

    sp1E = *(u16 *)(arg0 + 0x2E);
    sp18 = *(u8 **)(arg0 + 0x20);
    *(u16 *)(arg0 + 0x2E) = sp1E - 1;
    if ((s16)sp1E < 0) {
        func_801292C8(arg0);
    } else {
        *(u32 *)(sp18 + 0x20) = (u32)&D_801C5B00[(s16)(sp1E - 1) >> 2];
    }
}


extern void func_801292C8(u8 *a0);
extern void func_8012931C(struct vec *a0);

void func_801817CC(s32 *a0) {
    func_8012931C((struct vec *)a0);
    if (*(s16 *)((u8 *)a0 + 0x28) != 0) {
        func_80169A4C((s32)a0, *(s32 *)((u8 *)a0 + 0x34));
        *(s32 *)((u8 *)a0 + 0x14) += 0xF000;
    } else {
        func_801696D8((s32)a0, *(s32 *)((u8 *)a0 + 0x34));
        *(s32 *)((u8 *)a0 + 0x14) += 0x8000;
    }
    if (--*(s32 *)((u8 *)a0 + 0x1C) == -1) {
        func_801292C8((u8 *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181854);

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181918);

extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);

typedef struct { u8 b[8]; } Copy8;

void func_801819D0(s32 a0) {
    u16 sp10[3];
    u16 sp18[4];

    sp10[0] = *(u16 *)(a0 + 6);
    sp10[1] = *(u16 *)(a0 + 0xA);
    sp10[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(sp10, sp18, 1);
    func_800D23D0(sp18);
    sp18[2] = sp18[1] << 2;
    if (*(s32 *)(a0 + 0x34) != 0) {
        *(Copy8 *)(*(s32 *)(a0 + 0x34) + 0x10) = *(Copy8 *)sp18;
    }
}


void func_80181A70(void *a0)
{
    extern u8 D_801C5D00[];
    extern u8 D_8018A220[];
    extern void func_801465C0(void);
    s32 s0;

    s0 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)((s32)a0 + 0xA) = -0x680;
    *(s16 *)((s32)a0 + 0xE) = 0xF0;
    func_8001CD50((s32)s0, (s32)D_801C5D00);
    if (*(s16 *)((s32)a0 + 0x2C) == 0) {
        *(u16 *)((s32)a0 + 6) = 0;
        *(s16 *)(s0 + 0x12) = -0x200;
    } else {
        *(s16 *)((s32)a0 + 6) = -0x60;
        *(s16 *)(s0 + 0x12) = 0x1A0;
    }
    *(s16 *)(s0 + 0x10) = -0x100;
    *(s32 *)(s0 + 4) |= 0x50000000;
    s0 = ((s32 (*)(void))func_801465C0)();
    if (s0 != 0) {
        func_8001CB6C((u8 *)s0, (s32)D_8018A220, 0x280, 0x180);
        *(u8 *)(s0 + 0x27) = 0x4D;
        *(u16 *)(s0 + 8) = *(u16 *)((s32)a0 + 6);
        *(u16 *)(s0 + 0xA) = *(u16 *)((s32)a0 + 0xA);
        *(u16 *)(s0 + 0xC) = *(u16 *)((s32)a0 + 0xE);
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s32 *)((s32)a0 + 0x34) = s0;
    }
    *(s32 *)((s32)a0 + 0x2C) = 0x4000;
    *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    *(s32 *)((s32)a0 + 0x30) = 0x70;
}


void func_80181B80(void *a0) {
        *(short *)((char *)a0 + 0x2) = 1;
    }


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181B8C);

extern s32 func_8012B8A4(s16 *);
extern void func_80028620(s32, void *);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;

void func_80181BB0(s16 *arg) {
    int a;
    int t;
    unsigned char *a1;

    a = (func_8012B8A4(arg) - 0x600) & 0xFFF;
    if (a < 0x800) {
        t = a << 8;
    } else {
        a = 0xFFF - a;
        t = a << 8;
    }
    a1 = &D_800A5E94;
    a1[0] = (unsigned char)((t - a) / 2048);
    D_800A5E95 = (unsigned char)(a * 3 * 17 * 4 / 2048);
    D_800A5E96 = (unsigned char)(a * 127 / 2048);
    func_80028620(0, a1 - 0xC);
}


extern void (*D_8018A26C[])(void);

void func_80181C68(void *a0) {
    D_8018A26C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181CA4);

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80181D98);

void func_80181F5C(void *arg0)
{
    extern void func_80181D98(void *a0);
    extern void func_8017F268(void *a0);
    void *s0;

    s0 = arg0;
    func_80181D98(arg0);
    if (*(s16 *)((s32)s0 + 0xFC) == 1) {
        func_8016ED8C((s32)func_8017F268, 0x1000000, *(s16 *)((s32)s0 + 0xFE));
        *(s16 *)((s32)s0 + 0xFC) = 0;
    }
}


extern u16 D_800B99DA;
extern s32 D_801270D0;
extern void func_8002D59C(s32, s32, s32);

void func_80181FAC(s32 arg0) {
    register s32 id __asm__("$5");
    s32 dist;
    s32 vol;

    if ((D_800B99DA & 1) == 0) {
        dist = *(s16 *)(arg0 + 0xFC) - D_801270D0;
        if (dist < 0) {
            dist = -dist;
        }
        vol = ((700 - dist) * 127) / 700;
        if (vol < 0) {
            vol = 0;
        } else if (vol > 127) {
            vol = 127;
        }
        id = 0x4A4;
        if (*(s16 *)(arg0 + 0x70) == 2) {
            id = 0x4A5;
        }
        if (*(s32 *)(arg0 + 0xDC) == 0) {
            if (dist < 700) {
                func_8002D59C(id, (u16)(vol | 0x5000), *(u16 *)(arg0 + 0x36));
                *(s32 *)(arg0 + 0xDC) = 1;
            }
        } else {
            if (dist < 700) {
                func_8002D59C(id, (u16)(vol | 0x5000), *(u16 *)(arg0 + 0x36));
                *(s32 *)(arg0 + 0xDC) = 1;
            } else {
                func_8002D59C(4, id, *(u16 *)(arg0 + 0x36));
                *(s32 *)(arg0 + 0xDC) = 0;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801820AC);

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80182290);


extern void (*D_8018A2F4[])(void);

void func_801822D0(void *a0) {
    D_8018A2F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8018230C);

INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801824D0);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8002D4C8(s32, s32);
extern s32 rand(void);
extern s16 D_80126CB4;
extern s16 D_80126CB6;
extern s16 D_80126CB8;
extern u16 D_80126B5E;
extern s32 *D_80126B78;
extern s32 D_80126B68;
extern s32 D_80126B70;
extern s16 D_8018A300;
extern s32 D_801C0264;
extern s32 D_80183884;

void func_801824FC(s32 arg0) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        ((void (*)(s32, s32))func_8001C214)(v0, (s32)&D_801C0264);
        ((void (*)(s32, void *))func_8012A828)(arg0, &D_80183884);
        *(s16 *)(arg0 + 2) = 1;
        *(u16 *)(arg0 + 6) = D_80126CB4;
        *(u16 *)(arg0 + 0xA) = D_80126CB6;
        *(u16 *)(arg0 + 0xE) = D_80126CB8;
        *(s32 *)(arg0 + 8) = 0xFDFE0000;
        if (((D_80126B5E + 0x2C0) & 0xFFFF) >= 0x581U && *(s16 *)((s32)D_80126B78 + 0x12) == 0x800) {
            *(s32 *)(arg0 + 4) += D_80126B68 * 40 + (rand() & 0x3F) - 0x20;
            *(s32 *)(arg0 + 0xC) += D_80126B70 * 40;
            if (*(s16 *)(arg0 + 0xE) >= 0x380) {
                *(s16 *)(arg0 + 0xE) = 0x380;
            }
        }
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x80000000;
        *(s32 *)(arg0 + 0x1C) = D_8018A300;
        func_8002D4C8(0x49F, 0);
    }
}


extern void (*D_8018A32C[])(void);

void func_80182670(void *a0) {
    D_8018A32C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_8018A40C[])(void);

void func_801826AC(void *a0) {
    D_8018A40C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_801826E8);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32, void*);
extern void (*D_8018A2E8[])(void *);
extern u8 D_8018A2C8[];
extern u8 D_8018A2D8[];
extern M2C_UNK D_80183884;

void func_801827B4(void *a0) {
    s32 ret;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(ret, (s32)D_8018A2E8[*(s16 *)((s32)a0 + 0x70)]);
    func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0xC0, 0x94);
    *(s32 *)((s32)a0 + 0x58) =
        (*(s16 *)((s32)a0 + 0x70) == 2 ? (s32)&D_8018A2D8 : (s32)&D_8018A2C8) | 0x40000000;
    *(s16 *)((s32)a0 + 0x5C) = 0x800;
    ((void (*)(void *, void *))func_8012A828)(a0, &(*(u8 *)&D_80183884));
    *(s16 *)((s32)a0 + 2) = 1;
    *(s32 *)((s32)a0 + 0xDC) = 0;
}


typedef struct { u16 x, y, z, w; } V4_8018287C;

extern s32 D_80126B58;
extern s32 D_8018A30C[][2];
extern s32 D_8018A310[][2];

void func_8018287C(s32 arg0) {
    V4_8018287C in;   /* sp+0x10 */
    V4_8018287C out;  /* sp+0x18 */
    u16 *base;
    s32 i;

    base = (u16 *)&D_80126B58;
    if (func_8012BEE8(arg0) != 0) {
        for (i = 0; i < 4; i++) {
            in.x = *(u16 *)(arg0 + 6) + D_8018A30C[i][0];
            in.y = *(u16 *)(arg0 + 0xA);
            in.z = *(u16 *)(arg0 + 0xE) + D_8018A310[i][0];
            out = in;
            out.y -= 0x18;
            if (func_8012DF34(0, (s32)&in, (s32)&out) != 0) {
                base[0x21] = i << 10;
                base[0x20] = 0xA;
            }
        }
        func_8002D4C8(0x4A7, 0);
        func_8012C588(0x37, arg0);
        func_8012C218((void *)arg0);
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80182990);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_8018A338[];
extern u8 D_8018A3B0[];

void func_80182A00(void *a0) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001CA1C((void *)v0, &D_8018A338);
        func_8012A828((s32)a0, &D_8018A3B0);
        *(u16 *)((s32)a0 + 2) = 1;
        *(s32 *)((s32)a0 + 0x1C) = 0xA;
    }
}


s32 func_80182A70(void) {
        return 0x2;
    }



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_80182EF8(u8 *a0);
extern void (*D_8018A454[])(int);

void func_80182A78(int param_1)
{
    ((void (*)(void))func_80182EF8)();
    D_8018A454[*(unsigned short *)(param_1 + 2)](param_1);
}


void func_80182AC4(s32 *param_1) {
    extern s32 D_801C755C[];
    extern s32 D_801C7560[];
    extern void func_8012AD50();
    s32 *p;
    s32 *q;
    s32 val;
    s32 i;

    q = &D_801C7560[0];
    val = 1;
    i = 3;
    p = &D_801C755C[0];
    for (; i >= 0; i--) {
        *p = val;
        p--;
    }
    q[12] = 0x50000000;
    q[9] = 0xC0E060;
    q[8] = 0xC0E060;
    q[11] = 0;
    q[10] = 0;
    *(s16 *)((s32)param_1 + 0xFC) = 0;
    *(s16 *)((s32)param_1 + 0xFE) = 0;
    ((void (*)(void))func_8012AD50)();
}


extern void func_80182B90(void *a0, s32 a1, s16 a2);

void func_80182B30(int param_1)
{
    unsigned short t;

    func_80182B90((void *)param_1, *(short *)(param_1 + 0xFC), *(short *)(param_1 + 0xFE));
    *(unsigned short *)(param_1 + 0xFC) = *(unsigned short *)(param_1 + 0xFC) + 1;
    t = *(unsigned short *)(param_1 + 0xFE) + 1;
    *(unsigned short *)(param_1 + 0xFE) = t;
    if ((short)t >= 0x10) {
        *(unsigned short *)(param_1 + 0xFE) = 0;
    }
}


#include "common.h"

/* Structural analysis (fresh crack, no banked twin):
 * D_8018A414 is an array of 16-byte, alignment-1 records (two 8-byte blobs);
 * accessed with lwl/lwr in the target, which is the tell for a struct whose
 * members are byte arrays (alignment 1) rather than word-typed fields.
 * D_801C7550 is a plain s32 array of (at least) 4 elements, used as a
 * "gate" table: index i and index (i+1)&3 must both be non-zero before the
 * record at index i is forwarded to func_80182CB8. */

typedef struct {
    u8 raw[8];
} S8Blob;

typedef struct {
    S8Blob a;
    S8Blob b;
} Entry16;

extern Entry16 D_8018A414[];
extern s32 D_801C7550[];
extern void func_80182CB8(void *a0, S8Blob *a1, S8Blob *a2, s16 a3, s16 a4);

typedef union {
    s32 plain;
    struct { s32 idx : 15; } bf;
} LoopVar;

void func_80182B90(void *a0, s32 a1, s16 a2) {
    LoopVar i;
    Entry16 *p1;
    Entry16 *p2;

    i.plain = 0;
    p1 = D_8018A414;
    p2 = (Entry16 *)((u8 *)D_8018A414 + 8);

    for (; i.plain < 4; i.plain++) {
        if (D_801C7550[i.plain] != 0 && D_801C7550[(i.plain + 1) & 3] != 0) {
            S8Blob la = p1[i.bf.idx].a;
            S8Blob lb = p2[i.bf.idx].a;
            func_80182CB8(a0, &la, &lb, (s16)a1, a2);
        }
    }
}


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80182CB8);

extern u8 D_801202A0[];
extern s32 D_801C7550[];

void func_80182EF8(u8 *a0) {
    s32 i;

    for (i = 0; i < 0x60; i++) {
        u8 *p = &D_801202A0[i * 0x10C];

        if (*(u16 *)(p + 0x00) == 0x14) {
            if (*(s16 *)(p + 0x76) < 3) {
                D_801C7550[*(u16 *)(p + 0x70) & 3] = 0;
            }
        }
    }
}


extern void func_801832C0(void *a0);
extern void (*D_8018A468[])(int);
extern s32 D_801C7550[];
extern void func_8012C098(void *a0);

void func_80182F64(int param_1)
{
    if (*(short *)(param_1 + 0x70) == 2) {
        func_801832C0((void *)param_1);
    } else {
        D_8018A468[*(unsigned short *)(param_1 + 2)](param_1);
        if ((D_801C7550[*(short *)(param_1 + 0xFC)] == 0) ||
            ((D_801C7550[(*(short *)(param_1 + 0xFC) - 1) & 3] == 0) &&
             (D_801C7550[(*(short *)(param_1 + 0xFC) + 1) & 3] == 0))) {
            func_8012C098((void *)param_1);
        }
    }
}


extern s32 func_8012AD50(void *a0);
    void func_80183034(void) {
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_80183054);

extern void func_80183278();
extern void func_8012C098(void *a0);

void func_801831A0(s32 a0) {
    s32 s0;

    s0 = a0;
    func_80183278();
    if ((*(s32 *)(s0 + 0x1C) != 0) && (--*(s32 *)(s0 + 0x1C) == 0)) {
        func_8012C098((void *) s0);
    }
}


extern u16 D_800B99DA;
extern u32 D_801C7594;
extern u32 D_801C7598;

void func_801831E8(s32 arg0) {
    extern void func_8012C098(void *);
    u32 *ptr = (u32 *) &D_801C7594;

    if (D_800B99DA & 1) {
        *ptr = 0x80A040;
    } else {
        *ptr = 0x709030;
    }
    D_801C7598 = 0;
    if ((*(s32 *)(arg0 + 0x1C) != 0) && (--*(s32 *)(arg0 + 0x1C) == 0)) {
        func_8012C098((void *) arg0);
    }
}


extern void func_80183278();
    void func_80183258(s32 *a0) {
        *(s16 *)((s32)a0 + 0xFE) = 0;
        func_80183278();
    }


extern u16 D_8018A478[][4];

void func_80183278(s32 *a0) {
    u16 idx;
    u16 *ent;
    s32 dst;

    idx = (*(u16 *)((s32)a0 + 0xFE) + 1) & 1;
    *(u16 *)((s32)a0 + 0xFE) = idx;
    ent = &D_8018A478[idx][0];
    dst = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(dst + 0x28) = ent[0];
    *(u16 *)(dst + 0x2A) = ent[1];
    *(u8 *)(dst + 0x27) = (u8)ent[2];
}


extern void (*D_8018A488[])(void);

void func_801832C0(void *a0) {
    D_8018A488[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_801832FC(void) {
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC01_080/nonmatchings/ov_SC01_080_jr_8017AE2C", func_8018331C);




