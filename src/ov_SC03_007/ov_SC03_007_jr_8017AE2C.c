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
extern u8 D_80189910;
extern u8 D_80189880;
extern u8 D_8018985C;
extern u8 D_80189838;
extern u8 D_801898EC;
extern u8 D_801898C8;
extern u8 D_801898A4;
extern u8 D_80189814;
extern void func_80145934(void);
extern u8 D_801899A0;
extern u8 D_8018997C;
extern u8 D_80189958;
extern u8 D_80189934;
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
extern unsigned char D_80188D98[];
extern unsigned char D_80188DC8[];
extern unsigned char D_80188E18[];
extern unsigned char D_80188E48[];
extern unsigned char D_80188E78[];
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
extern void (*D_80188EC8[])(void *);
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
extern s32 D_80188F90[];
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
extern u8 D_80189018[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80189020;
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
extern int D_801E8B30;
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
extern s32 D_801E8B34;
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
extern s32 D_80189050;
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
extern void (*D_801890F8[])(void);
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
extern void (*D_8018911C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018910C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80189130[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018913C[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018914C[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80189164[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80189154;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80189178[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80189194[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80189184;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801891A8[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801891BC[])(void);
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
extern s32 D_801891D0;
extern void (*D_801891F8[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801891D8;
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
extern int (*D_80189244[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80189248[])(void);
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
extern unsigned short D_801896AC[];
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
extern void (*D_801896BC[])(void);
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
extern int D_801E8B68;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801896E4[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801896C4;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801896D4;
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
extern void (*D_80189724[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018972C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801896F8;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80189738[])(void);
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
extern u8 D_80189708;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E8B70;
extern s32 D_801E8B7C;
extern s32 D_801E8B80;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80189774[])(s32 *);
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
extern s32 D_80189748[];
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
extern s32 D_801E8B78;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_801899C4[])(void);
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
extern char D_801897E4[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80189A68[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189BBC[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_801899D8;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189BC4[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_801899E8;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80189A08;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189BCC[])(void);
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
extern void (*D_80189BF4[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189C00[])(void);
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
extern void (*D_80189A74[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80189CA4;
extern void func_8015D380(s32 a0);
extern unsigned char D_80188D88[];
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
extern unsigned char D_80189CB8[];
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
extern s8 D_80189CF4[];
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
extern u16 D_80189D3C;
extern u16 D_80189D3E;
extern u16 D_80189D40;
extern s32 D_80189D44;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189D4C;
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
extern int D_80189A58;
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
extern unsigned int D_80189DD0[];
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
extern void (*D_80189E80[])(void);
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
extern u16 D_80189EB0[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189F14;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E8B88[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189F38[])(void);
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
extern int D_801E8BE0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189F80[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189F70;
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
extern char D_801E83A8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80189F88[])(void);
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
extern void (*D_80189FDC[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189FA4;
extern s16 D_80189FD8;
extern s16 D_80189FD6;
extern s16 D_80189FD4;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189FE8[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E8C40;
extern u8 D_801E8C41;
extern u8 D_801E8C42;
extern u8 D_801E8C43;
extern u8 D_801E8C44;
extern u8 D_801E8C45;
extern u8 D_801E8C46;
extern u8 D_801E8C47;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189FF8[])(void);
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
extern s32 D_801E8C80;
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
extern void (*D_8018A03C[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018A0B8[];
extern s32 D_8018A0D8[];
extern u8 D_8018A154[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018A174[];
extern u8 D_8018A194[];
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
extern void (*D_8018A230[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018A2AC[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E83B8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018A2B8[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018A2C0[])(void);
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
extern void (*D_8018A388[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018A398[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018A3A8[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018A3B4[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018A314[];
extern u8   D_8018A328[];
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
extern void (*D_8018A3CC[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018A3D4[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018A3DC[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018A3E4[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018A3EC[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018A3F4[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018A3FC[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018A4B0[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018A4B8[])(void);
extern void func_80169F00(void *a0);
extern char D_8018A468[];
extern char D_8018A428[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018A4F0[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018A4FC[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018A544[])(void);
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
extern void (*D_8018A5C0[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E8FA0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018A5B4[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018A5F8[];
extern unsigned short D_8018A600[];
extern unsigned short D_8018A608[];
extern unsigned char D_801E8FA8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E8FA0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018A610[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E90DC;
extern M2C_UNK D_801E90E0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E9068;
extern void (*D_8018A640[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E90E4[];
extern u8 D_801E90EC[];
extern u8 D_801E909C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018A648[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018A664[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018A66C[])(void);
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
extern void (*D_8018A6D4[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018A678;
extern u8 D_8018A684;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018A708[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018A710[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018A764[])(void);
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
extern u16 D_8018A798[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018A788[];
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
extern s32 D_8018A7B4;
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
extern void (*D_8018A82C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018A834[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018A83C[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018A844[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018A84C[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018A854[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018A860[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018A86C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018A878[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018A888[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018A898[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018A8A0[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018A8A8[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018A8B0[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018A8B8[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018A8C0[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018A8C8[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018A8D0[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018A8D8[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018A8E0[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018A8E8[])(void);
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
extern void (*D_8018A8F0[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018A8F8[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018A900[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018A908[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018A910[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018A918[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018A920[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018A928[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018A930[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018A938[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018A940[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018A948[])(void);
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
extern void (*D_8018A98C[])(void);
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
extern M2C_UNK D_8018A950;
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
extern void (*D_8018A9BC[])(void);
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
extern void (*D_8018A9F8[])(void);
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
extern void (*D_8018AA50[])();
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
extern void (*D_8018AA60[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018AA68[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018ABD0[])();
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
extern void (*D_8018ABDC[])();
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
extern M2C_UNK D_801E8600;
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
extern s16 D_801EB250;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E9820;
extern short D_801EB2C4;
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
extern s32 D_801E9C4C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E9C74;
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
extern s16 D_801E9C30;
extern s32 func_8017A3B0(void);
extern short D_801E9C6C;
extern short D_801E9C68;
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

extern s16 D_801EB220;
extern s16 D_801EB222;
extern s16 D_801EB22C;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801EB220;

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
                    func_8012B744(p, &D_801EB22C);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801EB220+0xC == &D_801EB22C; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801EB220 + 0xC)) < 0x101) {
                    D_801EB220 = 0;
                    D_801EB222 = 0;
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
            func_8012B744((void *)(pv + 4), &D_801EB22C);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801EB220 + 0xC)) < 0x101) {
            D_801EB220 = 0;
            D_801EB222 = 0;
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
    extern s16 D_801E9CAC;
    extern s16 D_801E9CAE;
    extern s16 D_801E9CB0;
    extern s16 D_801E9CA4;
    extern s16 D_801E9CA6;
    extern s16 D_801E9CA8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801E9CAC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801E9CAE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801E9CB0, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801E9CA4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801E9CA6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801E9CA8, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801E9C34;
extern u16 D_801E9CB4;
extern u16 D_801E9CB6;
extern u16 D_801E9CB8;
extern s16 D_801EB250;

void func_8017B1D8(void) {
    func_8012A418();
    D_801EB250 = 0;
    D_801E9C34 = 0;
    D_801E9CB4 = D_80126B5E;
    D_801E9CB6 = D_80126B62;
    D_801E9CB8 = D_80126B66;
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
    extern u8 D_8018AD18[];
    extern s16 D_801E9CAC;
    extern s16 D_801E9CA4;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018AD18[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018AD18[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E9CAC;
        s16 *p78C = &D_801E9CA4;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801EB250 = 1;
        D_801E9C34 = 0;
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
    extern SV4_8017B368 D_801E9C54;
    extern SV4_8017B368 D_801E9C5C;
    extern s16 D_801E9CAC;
    extern s16 D_801E9CA4;
    extern u16 D_8018AD18;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E9C54;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E9C5C;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018AD18)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018AD18)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E9CAC) = loc0;
    (*(SV4_8017B368 *)&D_801E9CA4) = loc1;
    D_801EB250 = 1;
    D_801E9C34 = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801E9C54;
    extern SV4_8017B368 D_801E9C5C;
    extern s16 D_801E9CAC;
    extern s16 D_801E9CA4;
    extern u16 D_8018AD18;
    extern s16 D_801E9C34;
    extern s16 D_801EB250;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E9C54;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E9C5C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018AD18)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018AD18)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E9CAC) = loc0;
    (*(SV4_8017B368 *)&D_801E9CA4) = loc1;
    D_801EB250 = 1;
    D_801E9C34 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801E9CAC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801E9CAC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801E9CAC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801E9CA4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801E9CA4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801E9CA4).c;
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
    extern u8 D_8018AD18[];
    extern s16 D_801E9CAC;
    extern s16 D_801E9CAE;
    extern s16 D_801E9CB0;
    extern s16 D_801E9CA4;
    extern s16 D_801E9CA6;
    extern s16 D_801E9CA8;
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
        s32 a1addr = (s32)&D_8018AD18[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018AD18[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E9CAC;
        s16 *p78C = &D_801E9CA4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801E9CAE;
            v798 = D_801E9CB0;
            v78C = *p78C;
            v78E = D_801E9CA6;
            v790 = D_801E9CA8;
            __asm__ __volatile__("");
            D_801EB250 = 1;
            D_801E9C34 = 0x1E;
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
extern s16 D_801E9C34;
extern s16 D_801E9CAC;
extern s16 D_801E9CAE;
extern s16 D_801E9CB0;
extern s16 D_801E9CA4;
extern s16 D_801E9CA6;
extern s16 D_801E9CA8;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801E9C34 = 0;
    D_801E9CAC = (s16) D_80114F30;
    D_801E9CAE = (s16) D_80114F34;
    D_801E9CB0 = (s16) D_80114F38;
    D_801E9CA4 = (s16) D_80114F24;
    D_801E9CA6 = (s16) D_80114F28;
    D_801E9CA8 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801E9CC4;
extern s16 D_801E9CC6;
extern s16 D_801E9CC8;
extern s16 D_801E9CCC;
extern s16 D_801E9CCE;
extern s16 D_801E9CD0;

void func_8017B824(void) {
    D_801E9CC4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801E9CC6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801E9CC8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801E9CCC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801E9CCE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801E9CD0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801E9CC4;
extern s16 D_801E9CC6;
extern s16 D_801E9CC8;
extern s16 D_801E9CCC;
extern s16 D_801E9CCE;
extern s16 D_801E9CD0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801E9CC4;
    D_80114F34 = D_801E9CC6;
    D_80114F38 = D_801E9CC8;
    D_80114F24 = D_801E9CCC;
    D_80114F28 = D_801E9CCE;
    D_80114F2C = D_801E9CD0;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801E9CAC), src[8..15] -> (*(S8_8017B8E8 *)&D_801E9CA4) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801E9CAC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801E9CA4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801E9CB4;
extern u16 D_801E9CB6;
extern u16 D_801E9CB8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801E9C34;
extern short D_801E9CBC;
extern short D_801E9CBE;
extern short D_801E9CC0;
extern s16 D_801E9CAC;
extern s16 D_801E9CAE;
extern s16 D_801E9CB0;
extern s16 D_801E9CA4;
extern s16 D_801E9CA6;
extern s16 D_801E9CA8;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801E9CB4);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801E9CB6);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801E9CB8);
    (*(s16 *)&D_801E9CBC) = buf[0];
    (*(s16 *)&D_801E9CBE) = buf[1];
    (*(s16 *)&D_801E9CC0) = buf[2];
    D_801E9CAC = D_80114F30 + buf[0];
    D_801E9C34 = 0;
    D_801E9CAE = D_80114F34 + buf[1];
    D_801E9CB0 = D_80114F38 + buf[2];
    D_801E9CA4 = D_80114F24 + buf[0];
    D_801E9CA6 = D_80114F28 + buf[1];
    D_801E9CA8 = D_80114F2C + buf[2];
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

extern SV4 D_801E9C54;
extern SV4 D_801E9C5C;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801E9C5C) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801E9C54 = svec;

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
    D_801E9C5C = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801E9C5C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801E9C54) = svec;

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
    (*(SV4_8017BB34*)&D_801E9C5C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801E9C7C[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801E9C7C;
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
extern s16 D_801E9C34;
extern s16 D_801EB250;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801E9C34 = D_801E9C34 + 1;
    if (D_801E9C34 >= 0x1F) {
        D_801EB250 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801E9C34;
extern s16 D_801EB250;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E9C34 = D_801E9C34 + 1;
    if (0x18 < D_801E9C34) {
        func_8012A4BC();
        D_801EB250 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801E9C34;
extern void (*D_801E9C78)(void);
extern short D_801E9CBC;
extern short D_801E9CBE;
extern short D_801E9CC0;
extern s16 D_801EB250;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E9C34 = D_801E9C34 + 1;
    if (D_801E9C34 >= 0x19) {
        if (D_801E9C78 != 0) {
            (*D_801E9C78)();
        } else {
            D_80114F30 = D_80114F30 + D_801E9CBC;
            D_80114F34 = D_80114F34 + D_801E9CBE;
            D_80114F38 = D_80114F38 + D_801E9CC0;
            D_80114F24 = D_80114F24 + D_801E9CBC;
            D_80114F28 = D_80114F28 + D_801E9CBE;
            D_80114F2C = D_80114F2C + D_801E9CC0;
            func_8012A4BC();
        }
        D_801EB250 = 0;
    }
}



extern void (*D_8018ADB8[])(void);

void func_8017BE60(void *a0) {
    D_8018ADB8[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017BEBC);

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



/* func_8017C59C — ov_SC03_007_jr_8017AE2C — MAP-TILE model renderer (947 ins).
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
    extern u8 D_801EB160[];
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
    func_8017BEBC(D_801EB160, rect, *(s32 *)(arg0 + 0x60));

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


extern void func_8017D4C4();

void func_8017D468(s32 a0) {
    if ((func_80029178(0x142) & 0xFF) != 0) {
        func_8002D4C8(0xC4D, 0);
    } else {
        func_80029124(0x142, 1);
    }
    func_8017D4C4(a0);
}



extern s32 D_8018CE04;
    extern u8 *D_801274C8;
    extern s32 D_8018CE90;
    extern void *D_801274CC;
    void func_8017D4C4(void) {
        D_801274C8 = &D_8018CE04;
        D_801274CC = &D_8018CE90;
    }


extern s32 D_8018CEA4;
    extern u8 *D_801274C8;
    extern s32 D_8018CF1C;
    extern void *D_801274CC;
    void func_8017D4EC(void) {
        D_801274C8 = &D_8018CEA4;
        D_801274CC = &D_8018CF1C;
    }



extern s32 D_8018CF30;
    extern u8 *D_801274C8;
    extern s32 D_8018CF94;
    extern void *D_801274CC;
    void func_8017D514(void) {
        D_801274C8 = &D_8018CF30;
        D_801274CC = &D_8018CF94;
    }


extern s32 D_8018CFA8;
    extern u8 *D_801274C8;
    extern s32 D_8018D034;
    extern void *D_801274CC;
    void func_8017D53C(void) {
        D_801274C8 = &D_8018CFA8;
        D_801274CC = &D_8018D034;
    }



extern s32 D_8018D048;
    extern u8 *D_801274C8;
    extern s32 D_8018D0AC;
    extern void *D_801274CC;
    void func_8017D564(void) {
        D_801274C8 = &D_8018D048;
        D_801274CC = &D_8018D0AC;
    }



extern s32 D_8018D0C0;
    extern u8 *D_801274C8;
    extern s32 D_8018D14C;
    extern void *D_801274CC;
    void func_8017D58C(void) {
        D_801274C8 = &D_8018D0C0;
        D_801274CC = &D_8018D14C;
    }



extern s32 D_8018D160;
    extern u8 *D_801274C8;
    extern s32 D_8018D1EC;
    extern void *D_801274CC;
    void func_8017D5B4(void) {
        D_801274C8 = &D_8018D160;
        D_801274CC = &D_8018D1EC;
    }



extern s32 D_8018D200;
    extern u8 *D_801274C8;
    extern s32 D_8018D2A0;
    extern void *D_801274CC;
    void func_8017D5DC(void) {
        D_801274C8 = &D_8018D200;
        D_801274CC = &D_8018D2A0;
    }



extern s32 D_8018D2B4;
    extern u8 *D_801274C8;
    extern s32 D_8018D32C;
    extern void *D_801274CC;
    void func_8017D604(void) {
        D_801274C8 = &D_8018D2B4;
        D_801274CC = &D_8018D32C;
    }



extern s32 D_8018D340;
    extern u8 *D_801274C8;
    extern s32 D_8018D3B8;
    extern void *D_801274CC;
    void func_8017D62C(void) {
        D_801274C8 = &D_8018D340;
        D_801274CC = &D_8018D3B8;
    }



extern s32 D_8018D3CC;
    extern u8 *D_801274C8;
    extern s32 D_8018D46C;
    extern void *D_801274CC;
    void func_8017D654(void) {
        D_801274C8 = &D_8018D3CC;
        D_801274CC = &D_8018D46C;
    }



extern s32 D_8018D480;
    extern u8 *D_801274C8;
    extern s32 D_8018D4F8;
    extern void *D_801274CC;
    void func_8017D67C(void) {
        D_801274C8 = &D_8018D480;
        D_801274CC = &D_8018D4F8;
    }



extern s32 D_8018D50C;
    extern u8 *D_801274C8;
    extern s32 D_8018D584;
    extern void *D_801274CC;
    void func_8017D6A4(void) {
        D_801274C8 = &D_8018D50C;
        D_801274CC = &D_8018D584;
    }



extern s32 D_8018D598;
    extern u8 *D_801274C8;
    extern s32 D_8018D610;
    extern void *D_801274CC;
    void func_8017D6CC(void) {
        D_801274C8 = &D_8018D598;
        D_801274CC = &D_8018D610;
    }


extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);

void func_8017D6F4(void) {
    if ((func_800291B4(0xCC) & 0xFF) < 0xFU) {
        if (func_800291B4(0xCC) & 0xFF) {
            func_800291A0(0xCC, 1);
        }
    }
}


void func_8017D740(void) {
    switch (func_800291B4(0xCC) & 0xFF) {
    case 3:
        func_800291A0(0xCC, 4);
        break;
    case 5:
        func_800291A0(0xCC, 6);
        break;
    case 7:
        func_800291A0(0xCC, 8);
        break;
    case 9:
        func_800291A0(0xCC, 0xA);
        break;
    case 11:
        func_800291A0(0xCC, 0xC);
        break;
    case 13:
        func_800291A0(0xCC, 0xE);
        break;
    case 14:
        func_800291A0(0xCC, 0xF);
        break;
    }
}


void func_8017D7E4(void) {
}

extern s32 D_8018CAA8;
    extern u8 *D_801274C8;
    extern s32 D_8018CDC8;
    extern void *D_801274CC;
    void func_8017D7EC(void) {
        D_801274C8 = &D_8018CAA8;
        D_801274CC = &D_8018CDC8;
    }


extern s32 D_8018CB84;
    extern u8 *D_801274C8;
    extern s32 D_8018CDDC;
    extern void *D_801274CC;
    void func_8017D814(void) {
        D_801274C8 = &D_8018CB84;
        D_801274CC = &D_8018CDDC;
    }


extern s32 D_8018CCC4;
    extern u8 *D_801274C8;
    extern s32 D_8018CDF0;
    extern void *D_801274CC;
    void func_8017D83C(void) {
        D_801274C8 = &D_8018CCC4;
        D_801274CC = &D_8018CDF0;
    }



extern void (*D_8018BBCC[])(void);

void func_8017D864(void *a0) {
    D_8018BBCC[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017DBB4(void);
extern void func_800167B8(s32 a0);

s32 func_8017D8A0(s32 a0) {
    func_8017DBB4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D8E4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018BBD4[])(void);

void func_8017D908(void *a0) {
    D_8018BBD4[*(u8 *)((s32)a0 + 0x15)]();
}


extern void func_800D1E28(void);
extern s32 func_80183F7C(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);

s32 func_8017D944(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_800D1E28();
        if (func_80183F7C() != 0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}



extern void (*D_8018BBE0[])(void);

void func_8017D9D0(void *a0) {
    D_8018BBE0[*(u8 *)((s32)a0 + 0x15)]();
}




    s32 func_8017DA0C(u8 *a0) {
        if (--(*(s32 *)(a0 + 0x28)) == -1) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            if ((func_80029178(0x117) & 0xFF) == 0) {
                func_800D0C48(1);
            }
            func_800D1E28();
            *(u8 *)(a0 + 0x15) += 1;
        }
        return 0;
    }



extern void (*D_8018BBEC[])(void);

void func_8017DA9C(void *a0) {
    D_8018BBEC[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017DBDC(void);

s32 func_8017DAD8(s32 a0) {
    func_8017DBDC();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017DB18(u8 *a0) {
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
    void func_8017DB94(void) {
        func_800D1EBC();
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017DBB4(void) {

    extern s32 D_8018BBF8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018BBF8, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017DBDC(void) {

    extern s32 D_8018BC04(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018BC04, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017DC04);

void func_8017DC54(void) {
    typedef struct { char c[8]; } Blk8_8017DC54;
    extern s16 D_801274E8;
    extern s16 D_8018BC20;

    *(Blk8_8017DC54 *)&D_801274E8 = *(Blk8_8017DC54 *)&D_8018BC20;
    func_8017DD44();
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017DCA4);

typedef struct { char c[8]; } Blk8_8017DCF4;
extern s16 D_801274E8;
extern s16 D_8018BC30;

void func_8017DCF4(void) {
    *(Blk8_8017DCF4 *)&D_801274E8 = *(Blk8_8017DCF4 *)&D_8018BC30;
    func_8017DD44();
}


void func_8017DD44(void) {

    extern void func_8017DDE4(void *a0);
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8012A094(s32 a0);
    extern s32 D_80126954;
    extern s32 D_80126950;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x238;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017DDE4, 0);
    func_8012A094((s32)D_80126948);
    func_8017DDE4(D_80126948);
}



extern void (*D_8018BC38[])(void);

void func_8017DDE4(void *a0) {
    D_8018BC38[*(u8 *)((s32)a0 + 0x4)]();
}


extern void func_8017DE40();
    void func_8017DE20(void) {
        func_8017DE40();
    }


typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017DE40;
typedef struct { s16 a, b, c, d; } SV4_8017DE40;

extern s32 D_80126B58;
extern s16 D_8018BC3C[];
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern s16 D_801274E8;
extern s16 D_801274EC;

void func_8017DE40(s32 param_1)
{
    register s32 p1 __asm__("$17");
    register s16 *p0 __asm__("$16");
    MTX_8017DE40 m1;
    SV4_8017DE40 svec_in;
    s16 vec[3];
    u8 t;

    p1 = param_1;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(p1 + 5) + 1) & 1;
        *(u8 *)(p1 + 5) = t;
        *(s32 *)(p1 + 0x14) = D_8018BC3C[t];
    }

    *(s32 *)(p1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(p1 + 0x8),  (s32)*(s16 *)(p1 + 0xC),  4);
    *(s32 *)(p1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(p1 + 0x10), (s32)*(s16 *)(p1 + 0x14), 4);
    *(s16 *)(p1 + 0x18) = func_80012ABC((s32)*(s16 *)(p1 + 0x18), (s32)*(s16 *)(p1 + 0x20), 4);
    *(s16 *)(p1 + 0x1A) = func_80012ABC((s32)*(s16 *)(p1 + 0x1A), (s32)*(s16 *)(p1 + 0x22), 4);
    *(s16 *)(p1 + 0x1C) = func_80012ABC((s32)*(s16 *)(p1 + 0x1C), (s32)*(s16 *)(p1 + 0x24), 4);
    *(s16 *)(p1 + 0x28) = func_80012C6C((s32)*(s16 *)(p1 + 0x28), (s32)*(s16 *)(p1 + 0x2E), 0x10);
    *(s16 *)(p1 + 0x2A) = func_80012C6C((s32)*(s16 *)(p1 + 0x2A), (s32)*(s16 *)(p1 + 0x30), 0x10);
    *(s16 *)(p1 + 0x2C) = func_80012C6C((s32)*(s16 *)(p1 + 0x2C), (s32)*(s16 *)(p1 + 0x32), 0x10);

    if ((s32)D_80126940 < (s32)D_801274E8 - 0x280) {
        vec[0] = (s32)D_801274E8 - 0x280;
    } else if ((s32)D_801274E8 + 0x280 < (s32)D_80126940) {
        vec[0] = (s32)D_801274E8 + 0x280;
    } else {
        vec[0] = D_80126940;
    }

    if ((s32)D_80126944 < (s32)D_801274EC - 0x280) {
        vec[2] = (s32)D_801274EC - 0x280;
    } else if ((s32)D_801274EC + 0x280 < (s32)D_80126944) {
        vec[2] = (s32)D_801274EC + 0x280;
    } else {
        vec[2] = D_80126944;
    }

    p0 = &D_80126942;
    *(s32 *)(p1 + 0x48) = *(s16 *)(p1 + 0x28) + vec[0];
    *(s32 *)(p1 + 0x4C) = *(s16 *)(p1 + 0x2A) + *p0;
    *(s32 *)(p1 + 0x50) = *(s16 *)(p1 + 0x2C) + vec[2];
    func_80049CAC(p1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(p1 + 0x28) + vec[0];
    m1.t[1] = *(s16 *)(p1 + 0x2A) + *p0;
    m1.t[2] = *(s16 *)(p1 + 0x2C) + vec[2];
    svec_in.a = 0;
    svec_in.b = 0;
    svec_in.c = *(s32 *)(p1 + 0x10);
    func_8012F14C((s32)&m1, (s32)&svec_in, (s32)vec);

    *(s32 *)(p1 + 0x3C) = vec[0];
    *(s32 *)(p1 + 0x40) = vec[1];
    *(s32 *)(p1 + 0x44) = vec[2];
}


extern void (*D_8018BD14[])(void);

void func_8017E0B4(void *a0) {
    D_8018BD14[*(u16 *)((s32)a0 + 2)]();
    if (*(u16 *)((s32)a0 + 0) != 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    }
}


#include "common.h"

extern s32 func_8017EF1C(s32 a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047948(s32 a0);
extern void func_8012B2CC(s32 a0);

extern u16 D_801274E4[];
extern u8 D_8018BC50[];
extern u8 D_8018BC84[];
extern short D_801BB024;

void func_8017E124(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;

    if (func_8017EF1C(a0) == 0) {
        D_801274E4[0] |= 1;
        return;
    }
    s0 = a0;

    if (func_8012C354(s0, (s32)D_8018BC50) == 0) {
        return;
    }

    *(s8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)D_8018BC84;
    *(s32 *)(s0 + 0xB4) = 0xFFFBDFDD;
    *(s16 *)(s0 + 0xDE) = 0;
    *(s32 *)(s0 + 0xC4) |= 1;
    func_80143970(s0);
    func_8012A828(s0, &D_801BB024);

    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;
    v0 = func_80047948(0x380);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x1A) = v0;
    *(s16 *)(v1 + 0x18) = v0;
    *(s32 *)(s0 + 0x1C) = 8;
    *(s16 *)(s0 + 0x2) = 1;
    *(s16 *)(s0 + 0x86) = 1;
    func_8012B2CC(s0);
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80047948(s32 a0);

void func_8017E218(s32 s0) {
  s32 v0;
  s32 v1;

  if (func_8012BEE8(s0) != 0) {
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    v1 &= 0xFFEF;
    *(s16 *)(v0 + 0x2C) = v1;
    *(s16 *)(s0 + 0x2) = 2;
  } else {
    s32 a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_80047948(a0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x1A) = v0;
    *(s16 *)(v1 + 0x18) = v0;
  }
}



extern void func_8012A828(s32, void*);
    extern short D_801BB024;
    void func_8017E294(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801BB024);
    }


extern s32 func_8017EE50();

void func_8017E2C0(s32 a0) {
    if (func_8017EE50(a0) <= 0x10000) {
        *(s16 *)(a0 + 0x2) = 4;
    }
}


extern u8 D_801BB034;
extern void func_8012A828(s32 a0, void *a1);

void func_8017E2FC(a0)
s32 a0;
{
    *(s16 *)(a0 + 0x2) = 5;
    func_8012A828(a0, &D_801BB034);
    *(s32 *)(a0 + 0x1C) = 0x17;
}



extern s32 func_8012BEE8(s32 arg);
    void func_8017E33C(void *a0) {
        if (func_8012BEE8((s32)a0)) {
            *(s16 *)((u8 *)a0 + 0x2) = 0x6;
        }
    }


extern void func_8012B23C(s32 a0);
extern s32 func_8017EA04(s32);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801BB0FC;

void func_8017E370(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x7;
    func_8012B23C(s0);
    ((void (*)(void *))func_8017EA04)((void *)s0);
    func_8012A828(s0, (void *)&D_801BB0FC);
    *(s32 *)((s32)a0 + 0x1C) = 0x23;
}


extern s32 func_8017EA48(s32);
extern void func_8017EC90(s32 a0, s32 a1);
extern s32 func_8017E83C(s32 a0);
extern s32 func_8012E778(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8017EA04(s32);

void func_8017E3C0(void *a0) {
    s32 s0 = (s32)a0;
    register s32 v1_addr asm("$3");
    register u16 v0_val asm("$2");

    v1_addr = *(s32 *)(s0 + 0x20);
    v0_val = *(u16 *)(v1_addr + 0x12);
    *(u16 *)(v1_addr + 0x12) = (u16)(v0_val - 0x71);

    if (((s32 (*)(void *))func_8017EA48)((void *)s0) == 1) {
        func_8017EC90(s0, 2);
        *(s32 *)(s0 + 0x1C) = 0x23;
    } else {
        func_8017E83C(s0);
        if (*(u16 *)(s0 + 0x72) & 0x4000) {
            if (func_8012E778(s0, 0x8C00B4) == 1) {
                func_8002D4C8(0x662, 0);
            }
        }
        if (func_8012BEE8(s0) != 0) {
            ((void (*)(void *))func_8017EA04)((void *)s0);
            *(s32 *)(s0 + 0x1C) = 0x23;
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017E47C);


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

void func_8017E4C8(s32 param_1) {

    extern s16 D_80126CE0;
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


void func_8017E56C(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1c) = 6;
        *(s16 *)((s32)a0 + 0x5c) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_8017E57C(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        if (*(s16 *)(param_1 + 0x104) != 0) {
            p = *(s32 *)(param_1 + 0x20);
            *(s16 *)(p + 0x1C) = 0x1000;
            *(s16 *)(p + 0x18) = 0x1000;
            *(s16 *)(param_1 + 0x104) = 0;
        } else {
            p = *(s32 *)(param_1 + 0x20);
            h = *(u16 *)(param_1 + 0x100);
            *(s16 *)(p + 0x1C) = h;
            *(s16 *)(p + 0x18) = h;
        }
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


extern u8 D_801BB2BC[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

void func_8017E654(s32 param_1) {
    s32 ptr;
    s32 ret;
    s32 k;

    ptr = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 0x5C) = 0;
    *(s32 *)(param_1 + 0x1C) = 0x37;
    *(u16 *)(ptr + 0x10) = 0;
    func_8012A828(param_1, D_801BB2BC);
    *(u16 *)(param_1 + 0x34) = 0;
    ret = func_8012BCCC(param_1);
    k = 0x52B;
    if (!(0x8FFF < ret)) {
        k = 0x52A;
    }
    func_8002D4C8(k, 0);
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017E6C0);

















void func_8017E730(void *a0)
{
  *((short *) (((char *) a0) + 0x2)) = 0x6;
  *((unsigned short *) (((char *) a0) + 0x5c)) = 0xaa10;
  *((short *) (((char *) a0) + 0xfe)) = 0;
}

void func_8017E748(void) {
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018732C(s32 a0, u16 *a1, s16 a2);

void func_8017E750(s32 a0) {
    s16 sp[3];
    u16 t;

    t = *(u16 *)(a0 + 0x5E);
    if (t == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (t == 0x24) {
        sp[2] = 0;
        sp[0] = 0;
        sp[1] = -8;
        func_8018732C(a0, (u16 *)sp, 0xB);
    }
}



/* func_8017E7B4 — light/colour ramp-up on the entity's attached prim block.
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
void func_8017E7B4(int param_1) {
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

/* Declarations per decl_prior / TU house style (ov_SC03_007_jr_8017AE2C.c):
   - func_8012CBA4 is declared void(s32) elsewhere in this TU (line 5964) and called
     through a function-pointer cast to recover the s32 return value (line 5967 style).
   - func_8012B0B4 / func_8012B6D4 match the TU's existing declarations verbatim
     (lines 5904 / 5923).
   - func_8012ADE4, func_8012BC60, func_8012CEB0, func_8017EC90 are not declared
     anywhere in this TU; use the fleet-modal signatures from decl_prior. */
extern void func_8012CBA4(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8017EC90(s32 a0, s32 a1);

typedef struct { s16 vx, vy, vz, pad; } SVEC_E83C;

s32 func_8017E83C(s32 arg0) {
    extern u8 D_801202A0[];
    register s32 ret __asm__("$23");
    s32 v;
    u8 *p;
    s32 i;
    s32 d;
    u16 px, pz;
    SVEC_E83C in;
    SVEC_E83C out;
    SVEC_E83C buf;
    unsigned int *bp;

    ret = 1;
    v = ((s32 (*)(s32))func_8012CBA4)(arg0);
    if (v == 0) {
        func_8012ADE4((u8 *)arg0);
        func_8017EC90(arg0, 2);
        ret = 0;
    } else if ((v & 0xC000) != 0) {
        if ((v & 0x2000) == 0) {
            func_8012ADE4((u8 *)arg0);
        }
        func_8017EC90(arg0, 2);
        ret = 0;
    }

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(s32 *)(p + 0x58) != 0 && arg0 != (s32)p) {
            if (func_8012BC60((void *)(arg0 + 4), (void *)(p + 4)) < 0x1000) {
                bp = (unsigned int *)&buf;
                func_8012B0B4(bp, func_8012B6D4((s16 *)(arg0 + 4), (s16 *)(p + 4)), 0x41);
                d = *(s32 *)&buf;
                px = *(u16 *)(p + 6);
                out.vx = px;
                out.vy = *(u16 *)(p + 0xA);
                pz = *(u16 *)(p + 0xE);
                out.vz = pz;
                out.vx = px + d;
                out.vz = pz + (d >> 16);
                in.vx = *(u16 *)(arg0 + 0x3A);
                in.vy = *(u16 *)(arg0 + 0x3E);
                in.vz = *(u16 *)(arg0 + 0x42);
                if ((func_8012CEB0((s32)&in, (s32)&out, 0) & 0x2000) == 0) {
                    func_8012ADE4((u8 *)arg0);
                    return ret;
                }
                *(s16 *)(arg0 + 6) = out.vx;
                *(s16 *)(arg0 + 0xA) = out.vy;
                *(s16 *)(arg0 + 0xE) = out.vz;
                break;
            }
        }
    }
    return ret;
}


extern void func_8017EC90(s32 a0, s32 a1);

s32 func_8017EA04(s32 arg0) {
    if (*(s16 *)(arg0 + 0xAA) > 0) {
        func_8017EC90(arg0, 4);
        return 0;
    }
    func_8017EC90(arg0, 0);
    return 1;
}


#include "common.h"

/*
 * func_8017EA48 — build a Y-rotated GTE matrix from the actor's yaw, rotate two
 * canned SVECTORs (D_8018BD34[0..1]) into world space and feed them to the
 * collision probe func_80135888 / func_8012DF34.
 *
 * Frame 0x70:
 *   sp+0x10  MTX mtx        (0x20 bytes, copy of D_800AE620)
 *   sp+0x30  SV4 v0         (RotTransSV out #1)
 *   sp+0x38  SV4 v1         (RotTransSV out #2)
 *   sp+0x40  SV4 c0         (copy of v0 -> func_80135888 arg2)
 *   sp+0x48  SV4 c1         (copy of v1 -> func_80135888 arg3)
 *   sp+0x50  SV4 buf        (RotTransSV scratch arg2)
 */

#ifndef gte_SetRotMatrix
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
#endif
#ifndef gte_SetTransMatrix
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
#endif

/* bodies identical to engine_types.h's MTX / SV4; per-function names per the
 * *_<addr> house convention (law 8: same name => same body, else a new name). */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017EA48;
typedef struct { s16 a, b, c, d; } SV4_8017EA48;

extern MTX_8017EA48 D_800AE620;
extern SV4_8017EA48 D_8018BD34[];
/* §-note: declared as a 1-element array so its load carries MEM_IN_STRUCT_P and is
 * therefore killed by every `nonscalar` write (cse.c note_mem_written/invalidate_memory),
 * which is what produces the target's re-load of the pointer before each `sh`. */
extern s32 D_801270C8[];
extern s16 D_80126B98;
extern s16 D_80126B9A;

extern void RotMatrixY(s32 a0, void *a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_8017EF68(void);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);

s32 func_8017EA48(s32 param_1)
{
    MTX_8017EA48 mtx;   /* sp+0x10 */
    SV4_8017EA48 v0;    /* sp+0x30 */
    SV4_8017EA48 v1;    /* sp+0x38 */
    SV4_8017EA48 c0;    /* sp+0x40 */
    SV4_8017EA48 c1;    /* sp+0x48 */
    SV4_8017EA48 buf;   /* sp+0x50 */
    s32 ret;
    s32 r;

    ret = 0;

    mtx = D_800AE620;
    RotMatrixY(*(s16 *)(param_1 + 0xDC), &mtx);
    gte_SetRotMatrix(&mtx);
    gte_SetTransMatrix((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

    RotTransSV(&D_8018BD34[0], &v0, &buf);
    RotTransSV(&D_8018BD34[1], &v1, &buf);

    r = func_8017EF68();
    if (r == 1) {
        if ((*(u16 *)(D_801270C8[0] + 0x5C) & 0x8000) != 0) {
            if (*(u16 *)(D_801270C8[0] + 0x5E) != r) {
                c0 = v0;
                c1 = v1;
                if (func_80135888(*(s32 *)(D_801270C8[0] + 0x20),
                                  *(s32 *)(D_801270C8[0] + 0x58),
                                  (s32)&c0, (s32)&c1) != 0) {
                    *(u16 *)(D_801270C8[0] + 0x5C) |= 1;
                    *(s16 *)(D_801270C8[0] + 0x60) = 0xD;
                    *(u16 *)(D_801270C8[0] + 0x62) = *(u16 *)(param_1 + 0xDC);
                    ret = 1;
                    *(s16 *)(D_801270C8[0] + 0x5E) = 1;
                }
            }
        }
    }

    if (func_8012DF34(param_1, (s32)&v0, (s32)&v1) == 1) {
        s32 yaw;

        ret = 1;
        yaw = *(u16 *)(param_1 + 0xDC);
        D_80126B98 = 0xD;
        D_80126B9A = yaw;
    }

    return ret;
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017EC90);

extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);

void func_8017EE20(s32 arg0) {
    ((void (*)(void))func_8002A04C)();
    ((s32 (*)(s32))func_8012C098)(arg0);
}


extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8017EF68(void);
extern s32 D_801270C8[];
extern s32 func_8012BCCC(s32 a0);

s32 func_8017EE50(s32 arg0)
{
    if (func_8017EF68() != 1) {
        func_8012BCCC(arg0);
    } else {
        func_8012BC60((void *)(arg0 + 4), (void *)(D_801270C8[0] + 4));
    }
}


extern s32  func_8017EF68(void);
extern s32 D_801270C8[];
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B864(s32 a0);

s32 func_8017EEA4(s32 a0) {
    s16 buf[3];

    if (func_8017EF68() != 1) {
        func_8012B864(a0);
    } else {
        buf[0] = *(u16 *)(D_801270C8[0] + 0x6);
        buf[1] = *(u16 *)(D_801270C8[0] + 0xA);
        buf[2] = *(u16 *)(D_801270C8[0] + 0xE);
        func_8012B744((void *)(a0 + 4), buf);
    }
}


extern s32 func_800291B4(s32 arg);

s32 func_8017EF1C(s32 a0) {
    u8 v1;

    v1 = func_800291B4(0xCC);
    if (v1 == 10) {
        return 1;
    }
    if (v1 == 12) {
        return 1;
    }
    if (v1 != 11) {
        return v1 == 13;
    }
    return 1;
}


extern s32 D_801270C8[];

s32 func_8017EF68(void)
{
    if (D_801270C8[0] != 0) {
        return *(s16 *)(D_801270C8[0] + 0x76) > 0;
    }
    return 0;
}



extern void (*D_8018BEF0[])(void);

void func_8017EF98(void *a0) {
    D_8018BEF0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_80180454(s32 a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012B2CC(s32 a0);

extern u16 D_801274E4[];
extern u8 D_8018BD54[];
extern u8 D_8018BE58[];
extern u8 D_801BE488[];

void func_8017EFD4(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;

    if (func_80180454(a0) == 0) {
        D_801274E4[0] |= 1;
        return;
    }
    s0 = a0;

    if (func_8012C354(s0, (s32)D_8018BD54) == 0) {
        return;
    }

    *(s8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)D_8018BE58;
    *(s32 *)(s0 + 0xB4) = -0xA9;
    func_80143970(s0);
    *(s32 *)(s0 + 0xE0) = 0;
    func_8012A828(s0, D_801BE488);

    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    *(s32 *)(s0 + 0x1C) = 8;
    v0 = func_80047948(0x380);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x18) = v0;
    v0 = func_8004787C(0x380);

    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1A) = v0 * 2 + 0x1000;
    *(s16 *)(s0 + 0x2) = 1;
    *(s16 *)(s0 + 0x86) = 1;
    func_8012B2CC(s0);
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_8017F0C8(s32 s0) {
  s32 v0;
  s32 v1;

  if (func_8012BEE8(s0) != 0) {
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    v1 &= 0xFFEF;
    *(s16 *)(v0 + 0x2C) = v1;
    *(s16 *)(s0 + 0x2) = 2;
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


extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BE488[];

void func_8017F164(s32 param_1) {
    *(s16 *)(param_1 + 2) = 3;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, D_801BE488);
    *(s32 *)(param_1 + 0x1C) = rand() % 10 + 0x18;
    if (*(s32 *)(param_1 + 0xE0) == 0) {
        return;
    }
    *(s32 *)(param_1 + 0xE0) = 0;
    *(u16 *)(param_1 + 0xA) += 0x30;
}


extern s32 func_801802A4();
extern s32 func_8012BEE8(s32 a0);

void func_8017F1F8(s32 a0) {
    s32 p;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x40;
    if (func_801802A4(a0) != 1) {
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 2) = 4;
        }
    }
}


extern void func_8012B23C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BE488[];

void func_8017F258(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 5;
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE8000);
    func_8012A828(s0, D_801BE488);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


extern s32 func_801802A4();
extern s32 func_80180064(s32 arg0, s32 arg1);
extern void func_8018022C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern u8 D_800D3918[];

void func_8017F2B4(s32 a0) {
    s32 s0 = a0;
    s32 v;
    s32 v1;

    if (func_801802A4(s0) != 1) {
        v1 = func_80180064(s0, D_800D3918);
        if (v1 != 0) {
            if (v1 == -1) {
                func_8018022C(s0);
                return;
            }
            if (func_8012BEE8(s0) == 0) {
                return;
            }
        }
        *(u16 *)(s0 + 2) = 2;
    }
}


extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801BE580;

void func_8017F334(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 7;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801BE580);
    *(s32 *)((s32)a0 + 0x1C) = 0x24;
}


extern s32 func_8018033C(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_80180064(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80180388(s32);
extern u8 D_800D3918[];

void func_8017F37C(s32 a0) {
    register s32 s0 __asm__("$16");
    s32 v0;
    s32 v1;

    s0 = a0;
    __asm__ __volatile__("");
    v0 = func_8018033C(s0, 8);
    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + v0;
    if (*(s32 *)(s0 + 0x1C) < 0x19) {
        func_8012B178(s0, 0xFFFC0000);
        func_80180064(s0, D_800D3918);
    }
    if (func_8012BEE8(s0) != 0 || ((s32 (*)(s32))func_80180388)(s0) < 0x2001) {
        *(u16 *)(s0 + 2) = 8;
    }
}



















void func_8017F414(void *a0)
{
  s32 v1 = *((s32 *) (((s32) a0) + 0x20));
  int new_var;
  *((s16 *) (((s32) a0) + 0x2)) = 0x9;
  *((s16 *) (((s32) a0) + 0x5C)) = 0;
  *((s16 *) (((s32) a0) + (new_var = 0x34))) = 0;
  *((s32 *) (((s32) a0) + 0x1C)) = 0x8;
  *((s16 *) (((s32) v1) + 0x2C)) |= 0x10;
}



extern s32 func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_8017FE04(s32 a0);

void func_8017F444(s32 param_1)
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
            func_8017FE04(param_1);
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x5C) = 0xAA10;
        }
        break;
    case 3:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) & 0xFFEF;
            *(s16 *)(param_1 + 0x2) = 0xA;
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


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801BE658[];

void func_8017F658(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xB;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)D_801BE658);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    func_8012B23C(s0);
}


extern s32 func_8018033C(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_80180064(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80180388(s32);
extern u8 D_800D3918[];

void func_8017F6A8(s32 param_1) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v0 = func_8018033C(param_1, 8);
    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + v0;
    func_8012B178(param_1, 0xFFFC0000);
    v0 = func_80180064(param_1, D_800D3918);
    if (v0 == 2) {
        v0 = 0xC;
    } else {
        v0 = func_8012BEE8(param_1);
        if (v0 != 0) {
            v0 = ((s32 (*)(s32))func_80180388)(param_1);
            v0 = (v0 < 0x7001);
            if (v0)
                v0 = 0xC;
            else
                v0 = 2;
        } else {
            v0 = ((s32 (*)(s32))func_80180388)(param_1);
            if (v0 < 0x3801)
                v0 = 0xC;
            else
                return;
        }
    }
    *(u16 *)(param_1 + 2) = v0;
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017F750);

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017F794);

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017F850);

extern s32 D_801BE580;
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80180064(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012A828(s32 a0, void *a1);

void func_8017F8AC(s32 a0) {
    if (*(s16 *)(a0 + 0xAA) <= 0) {
        *(u16 *)(a0 + 2) = 2;
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, (void *)&D_801BE580);
            *(s32 *)(a0 + 0x1C) = 0x1A;
        }
        func_80180064(a0, (s32)D_800D3918);
    }
}


void func_8017F920(s32 param_1) {
    s32 p;
    s32 q;
    u16 h;

    p = *(s32 *)(param_1 + 0x20);
    h = *(u16 *)(p + 0x2C);
    if (h & 0x10) {
        *(s16 *)(p + 0x2C) = h & 0xFFEF;
        q = *(s32 *)(param_1 + 0x20);
        *(s16 *)(q + 0x1C) = 0x1000;
        *(s16 *)(q + 0x1A) = 0x1000;
        *(s16 *)(q + 0x18) = 0x1000;
    }
}


extern s32 func_8012B864(s32 a0);

void func_8017F95C(s32 a0) {
    s32 ret;

    *(u16 *)(a0 + 2) = 0xE;
    ret = func_8012B864(a0);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (ret + 0x800) & 0xFFF;
}


extern u8 D_8018BF30[];
extern u8 D_8018BF3C[];
extern u8 D_801BEC20[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);

void func_8017F99C(s32 param_1) {
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
        func_8012B14C(s0, (s32)D_8018BF30);
        v0 = 0xCC;
    } else {
        func_8012B14C(s0, (s32)D_8018BF3C);
        v0 = 0x100;
    }
    *(u16 *)(s0 + 0xDE) = v0;

    func_8012A828(s0, (void *)D_801BEC20);
}


extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern u8 D_8018BF48[];
extern void func_80131E00();

void func_8017FA84(void *a0) {
    s32 p;

    func_8012DBD0((s32)a0, 0xA, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) + 0x800, 0x1D);

    p = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(p + 0x10) = *(u16 *)(p + 0x10) - *(u16 *)((s32)a0 + 0xDE);

    *(s32 *)((s32)a0 + 0x1C) += 1;
    if (*(s32 *)((s32)a0 + 0x1C) >= 0x29) {
        func_80131E00(a0, 0xD);
    } else if ((((s32 (*)(s32, s32))func_8012CC64)((s32)a0, (s32)&D_8018BF48) & 0x2000) != 0) {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(u16 *)((s32)a0 + 0x5E) = 0;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
        *(u16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0xE0) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017FB40);

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8017FBA0);

#include "common.h"

typedef struct { s16 a, b, c, d; } SV4_FC6C;

extern s32 *D_80126B78;
extern u8 D_8018BE48[];
extern u8 D_8018BE50[];
extern void RotTransSV(void *a0, void *a1, void *a2);

#define SRM_FC6C(r0) __asm__ volatile (              \
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
#define STM_FC6C(r0) __asm__ volatile (              \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

extern u8 *func_8017FD6C(s32 a0, s32 a1, s32 a2);

void func_8017FC6C(s32 s2)
{
    SV4_FC6C sv0;   /* sp+0x10 */
    SV4_FC6C sv1;   /* sp+0x18 */
    s32 flag;       /* sp+0x20 */

    SRM_FC6C(*(s32 *)((char *)s2 + 0x20) + 0x34);
    STM_FC6C(*(s32 *)((char *)s2 + 0x20) + 0x34);

    RotTransSV((void *)D_8018BE48, &sv0, &flag);
    RotTransSV((void *)D_8018BE50, &sv1, &flag);

    func_8017FD6C(*(s16 *)(*(s32 *)((char *)s2 + 0x20) + 0x12), (s32)&sv0, *(s16 *)((char *)s2 + 0xDC));
    func_8017FD6C(*(s16 *)(*(s32 *)((char *)s2 + 0x20) + 0x12), (s32)&sv1, *(s16 *)((char *)s2 + 0xDC));

    *(u16 *)((char *)s2 + 0xDC) = *(u16 *)((char *)s2 + 0xDC) + 1;
    if ((s16)*(u16 *)((char *)s2 + 0xDC) >= 3) {
        *(u16 *)((char *)s2 + 0xDC) = 2;
    }
}


extern u32 D_8018BD88[];
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_8001CD50(s32 a0, s32 a1);

u8 * func_8017FD6C(s32 a0, s32 a1, s32 a2) {
    register s32 s0 __asm__("$16") = a2;
    register s32 s2 __asm__("$18") = a0;
    u8 *s1;
    u8 *ret;
    register s32 v1 __asm__("$3");

    s1 = func_801290DC(0x1d, (u8 *)a1);

    if (!s1) {
        return NULL;
    }

    s0 = *(s32 *)((char *)s1 + 0x20);
    func_8001CD50(s0, (s32)(&((u8 *)D_8018BD88)[a2 << 6]));

    
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


#include "common.h"

/* func_8017FE04 -- mass-lane fresh crack (Phase 31 wave p31y)
 *
 * Line-for-line relative of the banked twin ov_SC03_029:func_80184008
 * (seed_sim 0.7737).  Same "pick a spawn offset then walk it in halves until it
 * fits" loop: build a Y-rotated matrix from a random yaw, rotate the canned
 * (0,0,0xFF600000) offset vector into world space, add it to the actor's
 * position, and probe the result; on failure halve the offset and retry.
 *
 * Frame 0x88:
 *   sp+0x10  s32 vec[3]     rotation input vector
 *   sp+0x20  s32 out[3]     rotation output
 *   sp+0x30  u16 sp30[3]    saved actor angles (a0+0x3A/0x3E/0x42)
 *   sp+0x38  u16 sv[3]      candidate position (16.16 -> integer halves)
 *   sp+0x40  s32 unused40[2]  dead 8-byte slot the frame requires (§193-I)
 *   sp+0x48  MTX_8017EA48 m  copy of D_800AE620
 *   sp+0x68  s32 pos[3]     16.16 fixed-point candidate position
 */

/* BANKING NOTE (law 2/8): the destination TU ALREADY has this exact typedef at
 * line 4472 and `extern MTX_8017EA48 D_800AE620;` at 4475, both at file scope
 * and ABOVE this function's INCLUDE_ASM slot (4779).  When banking, DELETE the
 * next two lines -- they are duplicated here only so match_one's isolated
 * compile (which cannot see the host TU) resolves them.  Body is byte-identical
 * to the TU's, so the deletion is codegen-neutral. */

extern MTX_8017EA48 D_800AE620;
extern s32 D_801270C8[];
extern s16 D_80126CB4;
extern s16 D_80126CB6;
extern s16 D_80126CB8;

extern void func_8012B23C(s32 a0);
extern s32  func_80180AF4(void);
extern s32  rand(void);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32  func_80133784(s32 a0, void *a1, s32 a2);
extern s32  func_80134510(s32 a0);
extern s32  func_801803DC(s32 a0);

void func_8017FE04(s32 a0) {
    s32 vec[3];             /* sp+0x10 */
    s32 out[3];             /* sp+0x20 */
    u16 sp30[3];            /* sp+0x30 */
    u16 sv[3];              /* sp+0x38 */
    s32 unused40[2];        /* sp+0x40 */
    MTX_8017EA48 m;         /* sp+0x48 */
    s32 pos[3];             /* sp+0x68 */

    func_8012B23C(a0);

    sp30[0] = *(u16 *)(a0 + 0x3A);
    sp30[1] = *(u16 *)(a0 + 0x3E);
    sp30[2] = *(u16 *)(a0 + 0x42);

    if (func_80180AF4() != 1) {
        goto armB;
    }
    *(s16 *)(a0 + 0x6) = *(u16 *)(D_801270C8[0] + 0x6);
    *(s16 *)(a0 + 0xA) = *(u16 *)(D_801270C8[0] + 0xA);
    *(s16 *)(a0 + 0xE) = *(u16 *)(D_801270C8[0] + 0xE);
    goto rest;

found:
    *(s16 *)(a0 + 0x6) = sv[0];
    *(s16 *)(a0 + 0xA) = sv[1];
    *(s16 *)(a0 + 0xE) = sv[2];
    *(s32 *)(a0 + 0x14) = 0;
    goto tail;

armB:
    *(s16 *)(a0 + 0x6) = D_80126CB4;
    *(s16 *)(a0 + 0xA) = D_80126CB6;
    *(s16 *)(a0 + 0xE) = D_80126CB8;

rest:
    vec[1] = 0;
    vec[0] = 0;
    vec[2] = (s32)0xFF600000;

    m = D_800AE620;
    RotMatrixY(rand() % 4096, &m);

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
        if ((func_80133784(1, sp30, (s32)sv) & 0x8000) == 0) {
            if (func_80134510((s32)sv) != 0) {
                goto found;
            }
        }
        vec[2] >>= 1;
    } while (-vec[2] > 0xFFFF);

    *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x88);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x8C);

tail:
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_801803DC(a0);
}



#include "common.h"

/* func_80180064 (ov_SC03_007 / jr_8017AE2C) — 114 ins.
 *
 * Shape is a near-twin of the ALREADY-BANKED ov_SC03_107:func_8017EB70 (127 ins,
 * seed_sim 0.7782): same "walk the 0x60-entry D_801202A0 table (stride 0x10C)
 * looking for a nearby kin, probe with func_8012BC60/func_8012B6D4/func_8012B0B4,
 * commit via func_8012CEB0" body, same struct-of-3-SVEC stack layout (in/out/buf),
 * same goto-out-of-the-loop-on-failure idiom (twin's `lose:`).  This target skips
 * the twin's state==2 / state==0x1A early-outs and the &=~0x40 / 0xFFFFF clamp —
 * they are simply absent from this .s — and its self/kin predicate is
 * `*(u16*)arg0 != 0 && arg0 != (s32)p && *(u16*)arg0 == *(u16*)p`, not the twin's
 * "p's own fields nonzero" test.
 *
 * func_8012CC1C's REAL definition (src/shared/engine_core.h DEFINE_func_8012CC1C)
 * is `void func_8012CC1C(s32,s32) { func_8012CC88(arg0,0,arg1); }` — genuinely
 * void, but its body's last statement is a call, so $v0 leaks func_8012CC88's
 * return through the epilogue.  Same trick as the twin's func_8012CBA4 call:
 * declare it by its real (TU-absent-here, engine_core.h-canonical) prototype and
 * grab the leaked $v0 through a function-pointer cast at the call site.
 * func_80180AF4 (this TU's own still-unbanked sibling, INCLUDE_ASM'd right after
 * this function) gets the identical treatment: card's decl_prior "def" shows a
 * fleet-banked (void,()) signature elsewhere, but this call site reads $v0, so
 * the same leaked-register cast is used.
 *
 * Declarations already fixed by THIS TU (law 2 — copied verbatim, see the file's
 * own func_801858D4 / func_80185948 / func_80187214):
 *   func_8012B6D4 : extern s32  func_8012B6D4(s16 *a0, s16 *a1);      (line 5923)
 *   func_8012B0B4 : extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3); (line 5904)
 *   D_801202A0    : extern u8 D_801202A0[];                            (line 6393, func_80187214)
 *   D_801270C8    : extern s32 D_801270C8[];  used as D_801270C8[0]     (lines 4480/4948)
 * func_8012BC60 / func_8012CEB0 / func_8012ADE4 / func_8012AF0C / func_8012CC1C /
 * func_80180AF4 are NOT declared anywhere in this TU (grepped clean), so their
 * decl_prior modal fleet spelling is used directly.
 */

typedef struct { s16 vx, vy, vz, pad; } SVEC_80064;

extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern s32  func_8012AF0C(s32 a0, s32 a1);
extern s32  func_80180AF4(void);

s32 func_80180064(s32 arg0, s32 arg1) {
    extern u8 D_801202A0[];
    extern s32 D_801270C8[];
    SVEC_80064 in;
    SVEC_80064 out;
    SVEC_80064 buf;
    unsigned int *bp;
    s32 v;
    s32 d;
    s32 i;
    u8 *p;
    u16 px, pz;

    v = ((s32 (*)(s32, s32))func_8012CC1C)(arg0, arg1);
    if ((v & 0x2000) == 0) {
        func_8012ADE4((u8 *)arg0);
    }

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)arg0 != 0 && arg0 != (s32)p && *(u16 *)arg0 == *(u16 *)p) {
            if (func_8012BC60((void *)(arg0 + 4), (void *)(p + 4)) < 0x1000) {
                bp = (unsigned int *)&buf;
                func_8012B0B4(bp, func_8012B6D4((s16 *)(arg0 + 4), (s16 *)(p + 4)), 0x41);
                d = *(s32 *)&buf;
                px = *(u16 *)(p + 6);
                out.vx = px;
                out.vy = *(u16 *)(p + 0xA);
                pz = *(u16 *)(p + 0xE);
                out.vz = pz;
                out.vx = px + d;
                out.vz = pz + (d >> 16);
                in.vx = *(u16 *)(arg0 + 0x3A);
                in.vy = *(u16 *)(arg0 + 0x3E);
                in.vz = *(u16 *)(arg0 + 0x42);
                if ((func_8012CEB0((s32)&in, (s32)&out, 0) & 0x2000) == 0) {
                    func_8012ADE4((u8 *)arg0);
                    goto after_loop;
                }
                *(s16 *)(arg0 + 6) = out.vx;
                *(s16 *)(arg0 + 0xA) = out.vy;
                *(s16 *)(arg0 + 0xE) = out.vz;
                break;
            }
        }
    }
after_loop:

    v = ((s32 (*)(void))func_80180AF4)();
    if (v == 1) {
        if (func_8012AF0C(arg0, D_801270C8[0]) == v) {
            return 2;
        }
    }
    return 1;
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8018022C);

extern void func_80180388(s32);

s32 func_801802A4(s32 a0) {
    s32 ret;
    s32 d;
    s32 res;

    ret = ((s32 (*)(s32))func_80180388)(a0);
    if (ret < 0x2001) {
        *(s16 *)(a0 + 2) = 6;
        return 1;
    }
    if (0x10000 < ret) {
        return 0;
    }
    d = (func_801803DC(a0) - *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) & 0xFFF;
    if (d < 0x800) {
        res = d < 0x400;
    } else {
        res = (0x1000 - d) < 0x400;
    }
    if (res) {
        *(s16 *)(a0 + 2) = 6;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_8018033C);

extern s32 func_8012BC60(void *a0, void *a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80180AF4(void);
extern s32 D_801270C8[];

void func_80180388(s32 arg0)
{
    if (func_80180AF4() != 1) {
        func_8012BCCC(arg0);
    } else {
        func_8012BC60((void *)(arg0 + 4), (void *)(D_801270C8[0] + 4));
    }
}


extern s32 D_801270C8[];
extern s32 func_80180AF4(void);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);

s32 func_801803DC(s32 a0) {
    s16 buf[3];

    if (func_80180AF4() != 1) {
        func_8012B864(a0);
    } else {
        buf[0] = *(u16 *)(D_801270C8[0] + 0x6);
        buf[1] = *(u16 *)(D_801270C8[0] + 0xA);
        buf[2] = *(u16 *)(D_801270C8[0] + 0xE);
        func_8012B744((void *)(a0 + 4), buf);
    }
}


extern s32 func_800291B4(s32 arg);

s32 func_80180454(s32 a0) {
    s32 v0;
    s32 v1;

    v1 = func_800291B4(0xCC) & 0xFF;
    if (v1 == 8 || v1 == 0xC || v1 == 9) {
        v0 = 1;
    } else {
        v0 = (v1 == 0xD);
    }
    return v0;
}



extern void (*D_8018BF50[])(void);

void func_801804A0(void *a0) {
    D_8018BF50[*(u16 *)((s32)a0 + 0x2)]();
}




extern MTX_8017EA48 D_800AE620;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801804DC(s32 a0)
{
    MTX_8017EA48 m;
    s32 vel[3];

    vel[1] = 0;
    vel[0] = 0;
    vel[2] = 0xFFFE8000;
    m = D_800AE620;
    RotMatrixY(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), &m);
    func_800484EC((s32)&m, (s32)&vel[0], a0 + 0x10);
    *(s16 *)(a0 + 0x2C) = 0x3C;
    *(s16 *)(a0 + 0x2) = 1;
}


#include "common.h"

extern u16 D_801270C0;
extern s32 D_801270C8[];
extern s32 func_80180AF4(void);
extern s32 func_801806B8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801292C8(u8 *a0);
extern void func_8012931C(u8 *a0);

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_8018BF58[];
extern u8 D_8018BF60[];

void func_80180598(void *a0)
{
    register s32 s0 __asm__("$16") = (s32)a0;
    s16 v1;
    u16 v0;
    s16 vec[3];
    void *ptr;

    v1 = *(s16 *)&D_801270C0;
    if (v1 == 2) {
        return;
    }

    if (func_80180AF4() == 1) {
        vec[0] = *(u16 *)(D_801270C8[0] + 0x6);
        vec[1] = *(u16 *)(D_801270C8[0] + 0xA) - 0x10;
        vec[2] = *(u16 *)(D_801270C8[0] + 0xE);
        func_801806B8(s0, (s32)vec, (s32)D_8018BF58, 0);
    }

    vec[0] = *(s16 *)&D_80126B5E;
    vec[1] = (*(s16 *)&D_80126B62) - 0x30;
    vec[2] = *(s16 *)&D_80126B66;
    func_801806B8(s0, (s32)vec, (s32)D_8018BF60, 1);

    v0 = *(u16 *)(s0 + 0x2C);
    *(u16 *)(s0 + 0x2C) = v0 - 1;

    if ((s16)v0 < 0) {
        func_801292C8((u8 *)s0);
        return;
    }

    ptr = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr + 0x18) += 0x100;

    ptr = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr + 0x1A) += 0x100;

    func_8012931C((u8 *)s0);
}


#include "common.h"

/* TU already declares these (verbatim, law 2):
 *   func_8014CAFC  : extern s32 func_8014CAFC(void);                (TU:553)
 *   VectorNormalSS : extern s32 VectorNormalSS(void *a0, void *a1); (TU:1847)
 *   D_80126B5E/62/66 : extern u16 D_80126B5E; ...                   (TU:1789-1791 etc)
 *   D_80126B9A     : extern s16 D_80126B9A;                         (TU:4482)
 *   D_801270C8     : extern s32 D_801270C8[];                       (TU:4480/4948; array-decl
 *                    idiom so *(...)(D_801270C8[0]+off) carries MEM_IN_STRUCT_P and is killed
 *                    by every nonscalar write, forcing a reload -- write the raw expression at
 *                    every use site, do NOT cache into a local.)
 * D_80126B78/D_80126B90 : fleet-modal `extern s32 *D_80126B78;` / `*D_80126B90;` (pointer
 *   variable; the target loads the WORD stored at the variable itself, i.e. the pointer's own
 *   bit pattern cast to s32 -- same idiom as ov_SC02_027_jr_8017D898.c's "(s32)D_80126B78 + 0x34").
 * func_80180838  : defined later in this very TU as
 *                    s32 func_80180838(void *a0, s32 a1, s32 a2)
 *                  -- forward-declare with that exact signature.
 * func_8012F568  : not declared in this TU; fleet-modal 6-s32-arg void function (n=2820),
 *                  confirmed by the banked twin ov_SC02_017:func_80185B5C which calls it as
 *                  func_8012F568(1, 6, 0, 0, (s32)pointA, (s32)diff).
 */
extern s32 func_8014CAFC(void);
extern s32 VectorNormalSS(void *a0, void *a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126B9A;
extern s32 D_801270C8[];
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 func_80180838(void *a0, s32 a1, s32 a2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_801806B8(s32 a0, s32 a1, s32 a2, s32 a3)
{
    s32 s0 = a0;

    if (a3 != 0) {
        if (func_8014CAFC() != 0) {
            return 0;
        }
        if (func_80180838((void *)s0, (s32)D_80126B78, (s32)D_80126B90) != 0) {
            s16 diff[3];
            s16 pointA[3];

            pointA[0] = D_80126B5E;
            pointA[1] = D_80126B62;
            pointA[2] = D_80126B66;

            diff[0] = pointA[0] - *(u16 *)(s0 + 0x6);
            diff[1] = pointA[1] - *(u16 *)(s0 + 0xA);
            diff[2] = pointA[2] - *(u16 *)(s0 + 0xE);

            VectorNormalSS(diff, diff);

            pointA[1] -= 0x20;
            func_8012F568(1, 0x5001, 0, 0, (s32)pointA, (s32)diff);

            {
                register s32 node __asm__("$2");
                node = *(s32 *)(s0 + 0x20);
                node = *(u16 *)(node + 0x12);
                D_80126B9A = node;
            }
            return 1;
        }
        return 0;
    } else {
        if (*(s16 *)(D_801270C8[0] + 0xAA) > 0) {
            return 0;
        }
        if (func_80180838((void *)s0, *(s32 *)(D_801270C8[0] + 0x20), *(s32 *)(D_801270C8[0] + 0x58)) != 0) {
            *(u16 *)(D_801270C8[0] + 0x5C) |= 1;
            *(s16 *)(D_801270C8[0] + 0x5E) = 0x1E;
            {
                register s32 node __asm__("$2");
                node = *(s32 *)(s0 + 0x20);
                node = *(u16 *)(node + 0x12);
                *(u16 *)(D_801270C8[0] + 0x62) = node;
            }
            return 1;
        }
        return 0;
    }
}


#include "common.h"

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); /* TU:588  verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1661 verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);      /* TU:3119 verbatim */

/* not declared anywhere in src/ or include/; func_80020DA4 is the (s32,s32)
 * sibling of TU-declared func_80020F34 (matches banked twin
 * ov_SC02_011:func_8018E208). D_8018BF68 is per-overlay data. */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_8018BF68[];

/* Same SRM/STM idiom as ov_SC02_011:func_8018E208 (not named
 * gte_SetRotMatrix/gte_SetTransMatrix — collides with the TU's own uses). */
#define SRM_80180838(r0) __asm__ volatile (              \
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
#define STM_80180838(r0) __asm__ volatile (              \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

s32 func_80180838(void *a0, s32 a1, s32 a2)
{
    s32  i;
    u8  *p0;
    u8  *p1;
    u8  *base;
    s32  matrix[8];   /* sp+0x10, MATRIX-shaped: t[] at matrix[5..7] */
    s32  sv0[2];      /* sp+0x30 */
    s32  sv1[2];      /* sp+0x38 */
    s32  flag;        /* sp+0x40 */
    s32  hit;

    p0 = (u8 *)*(s32 *)((s32)a0 + 0x20);

    func_80020DA4((s32)p0 + 0x10, (s32)matrix);
    func_80020F34((s32)matrix, (s32)p0 + 0x18);

    matrix[5] = *(s16 *)(p0 + 0x8);
    matrix[6] = *(s16 *)(p0 + 0xA);
    matrix[7] = *(s16 *)(p0 + 0xC);

    base = D_8018BF68;
    p1 = base + 0x20;
    p0 = base;

    for (i = 0; i < 4; i++) {
        SRM_80180838(matrix);
        STM_80180838(matrix);

        RotTransSV(p0, sv0, &flag);
        RotTransSV(p1, sv1, &flag);

        hit = func_80135888(a1, a2, (s32)sv0, (s32)sv1);
        p1 += 8;
        if (hit != 0) {
            return 1;
        }
        p0 += 8;
    }
    return 0;
}



extern void (*D_8018BFC8[])(void);

void func_80180990(void *a0) {
    D_8018BFC8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801809CC(void *a0) {
        *(short *)((char *)a0 + 0x2) = 1;
        *(int *)((char *)a0 + 0x1c) = 2;
        *(unsigned char *)((char *)a0 + 0xfc) = 1;
        *(unsigned char *)((char *)a0 + 0xfe) = 2;
        *(unsigned char *)((char *)a0 + 0xfd) = 0;
        *(unsigned char *)((char *)a0 + 0xff) = 4;
        *(short *)((char *)a0 + 0xdc) = 0;
    }


extern s32 func_8012BEE8(s32 arg);

s32 func_80180A00(void *arg0) {
    if (func_8012BEE8((s32)arg0)) {
        func_80180A58(0, (u8 *)arg0 + 0xFD);
        func_80180A58(1, (u8 *)arg0 + 0xFE);
        func_80180A58(2, (u8 *)arg0 + 0xFF);
        *(s32 *)((char *)arg0 + 0x1C) = 2;
    }
}


extern u32 D_8018BD88[];
extern u32 D_8018BFA8[];
extern u32 D_8018BFC0;

void func_80180A58(s32 a0, u8 *a1) {
    u8 idx;
    u32 *dst;

    idx = *a1;
    if (idx >= 7) {
        *a1 = 0;
    }

    a0 <<= 6;
    idx = *a1;
    dst = (u32 *)((u8 *)D_8018BD88 + a0);
    *dst = D_8018BFA8[idx];

    idx = *a1;
    dst++;
    if (idx - 1 < 0) {
        *dst = D_8018BFC0;
    } else {
        *dst = D_8018BFA8[idx - 1];
    }

    (*a1)++;
}


s32 func_80180AF4(void) {
    extern s32 D_801270C8[];
    s32 p;

    p = D_801270C8[0];
    if (p != 0) {
        return *(s16 *)(p + 0x76) > 0;
    }
    return 0;
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8016AA50(s32 param_1, s32 param_2);

void func_80180B24(s32 arg0) {
    u16 diff;
    s32 p;

    *(s32 *)(arg0 + 0xB4) |= 1;
    *(s32 *)(arg0 + 0xC4) &= ~2;
    if (*(s16 *)(arg0 + 0x60) != 0) {
        *(u16 *)(arg0 + 0x7C) = *(u16 *)(arg0 + 6);
        *(u16 *)(arg0 + 0x7E) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(arg0 + 0x80) = *(u16 *)(arg0 + 0xE);
        func_8016AA50(arg0, *(s16 *)(arg0 + 0x60));
    }
    diff = *(u16 *)(arg0 + 0x76) - *(u16 *)(arg0 + 0x60);
    *(u16 *)(arg0 + 0x5C) = 0;
    *(u16 *)(arg0 + 0x60) = 0;
    *(u16 *)(arg0 + 0x76) = diff;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = (*(u16 *)(arg0 + 0x62) + 0x800) & 0xFFF;
    p = *(s32 *)(arg0 + 0x20);
    *(u16 *)(p + 0x14) = 0;
    *(u16 *)(p + 0x10) = 0;
    func_8012B2CC(arg0);
    func_8012B23C(arg0);
    *(u8 *)(arg0 + 0xC2) = 1;
    *(u16 *)(arg0 + 0x98) = 0;
    *(s32 *)(arg0 + 0x1C) = 0x3C;
    func_8002D4C8(0x526, 0);
}


void func_80180BF8(void *arg0) {
    *(s16 *)((s32)arg0 + 0x98) = 1;
    *(s32 *)((s32)arg0 + 0x1C) = 1;
    *(u16 *)((s32)arg0 + 0x5C) = 0x8810;
    *(s32 *)((s32)arg0 + 0xB4) &= ~1;
    *(s32 *)((s32)arg0 + 0xC4) |= 2;
    if (*(s16 *)((s32)arg0 + 0x76) < 0x370) {
        *(s16 *)((s32)arg0 + 0x76) = 0x2BC;
    }
}


void func_80180C48(s32 a0) {

    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    D_80126CB4 = *(u16 *)(a0 + 0x6);
    D_80126CB6 = *(u16 *)(a0 + 0xa);
    D_80126CB8 = *(u16 *)(a0 + 0xe);
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern s32 func_800291B4(s32 arg);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_80143970(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801270C8[];

extern u8 D_8018BFE0[];
extern u8 D_8018C014[];
extern u8 D_801B101C[];
extern u8 D_80126B5C;
extern s32 D_80126B64;

void func_80180C74(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;
    u8 cat;

    v0 = func_8012C354(a0, (s32)D_8018BFE0);
    s0 = a0;
    if (v0 == 0) {
        return;
    }

    *(s8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xB4) = 0x4000;
    *(s32 *)(s0 + 0xBC) = (s32)D_8018C014;
    *(s8 *)(s0 + 0xC1) = 0;
    *(s32 *)(s0 + 0xC4) = 3;

    if (func_80029504() == 0x32) {
        v1 = func_800291B4(0xCC) & 0xFF;
        if (v1 == 2 || v1 == 4 || v1 == 6 || v1 == 8 || v1 == 0xA || v1 == 0xC) {
            v0 = 0;
        } else {
            v0 = 1;
        }
    } else {
        v0 = 0;
    }

    if ((v0 & 0xFF) != 0) {
        func_8002D4C8(0xC4D, 0);
    }

    v1 = func_800291B4(0xCC) & 0xFF;
    if (v1 == 2) {
        v0 = 0xB4;
    } else if (v1 == 4) {
        v0 = 0xD2;
    } else {
        goto L_not_2_4;
    }
    *(s32 *)(s0 + 0xE0) = v0;
    cat = 2;
    goto L_tail;

L_not_2_4:
    if (v1 == 6) {
        v0 = 0xF0;
        goto L_store_cat0;
    } else if (v1 == 8) {
        *(s32 *)(s0 + 0xE0) = 0x10E;
        cat = 3;
        goto L_tail;
    } else if (v1 == 0xA) {
        v0 = 0x12C;
    } else if (v1 == 0xC) {
        v0 = 0x14A;
    } else {
        cat = 4;
        goto L_tail;
    }
L_store_cat0:
    *(s32 *)(s0 + 0xE0) = v0;
    cat = 0;
L_tail:

    if (cat == 4) {
        func_8012C218((void *)s0);
        return;
    }

    *(s16 *)(s0 + 0x102) = 0;
    func_80143970(s0);
    *(s16 *)(s0 + 0x2) = 1;
    func_8012B23C(s0);
    func_8012A828(s0, D_801B101C);

    *(s16 *)(s0 + 0xDC) = *(u16 *)(s0 + 0x6);
    *(s16 *)(s0 + 0xDE) = *(u16 *)(s0 + 0xE);

    *(s32 *)(s0 + 0x4) = *(s32 *)&D_80126B5C;
    *(s32 *)(s0 + 0xC) = D_80126B64;

    D_801270C8[0] = s0;
}


void func_80180E3C(s32 a0) {
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32 func_8012CBCC(s32 a0);
    extern u8 D_801B0CFC[];
    extern u8 D_8018C03C[];
    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    s32 s0;
    s32 v1;
    s32 v0;

    s0 = a0;
    v1 = *(s16 *)(s0 + 6) - *(s16 *)(s0 + 0xDC);
    if (v1 < -400) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0xC00;
    } else if (!(v1 < 401)) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x400;
    } else {
        v1 = *(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0xDE);
        if (v1 < -400) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x800;
        } else if (!(v1 < 401)) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
        } else {
            func_8012A828(s0, (void *)D_801B0CFC);
            *(s16 *)(s0 + 2) = 5;
            *(s32 *)(s0 + 0x2C) = -786432;
        }
    }

    func_8012B1B4(s0, (s32)D_8018C03C);
    v0 = func_8012CBCC(s0);
    if (v0 & 0x6000) {
        *(s16 *)(s0 + 0x16) = -4;
    }

    D_80126CB4 = *(u16 *)(s0 + 6);
    D_80126CB6 = *(u16 *)(s0 + 0xA);
    D_80126CB8 = *(u16 *)(s0 + 0xE);
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_80180F4C);

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_801810E4);

INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_801813D0);

#include "common.h"

extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801270C8[];
extern u8 D_8018C03C[];

void func_80181544(s32 a0) {
    s32 s0;
    s32 p;
    u16 flag;
    s32 v1;
    s16 t;

    s0 = a0;
    p = *(s32 *)(s0 + 0x20);
    flag = *(u16 *)(p + 0x12);
    *(u16 *)(p + 0x12) = (flag & 0x800) ? (flag + 0x80) : (flag - 0x80);

    func_8012B1B4(s0, (s32)D_8018C03C);
    v1 = func_8012CBCC(s0);
    if (v1 & 0x6000) {
        *(s16 *)(s0 + 0x16) = -4;
    }
    if (v1 & 0x8000) {
        *(s32 *)(s0 + 0x4) += *(s32 *)(s0 + 0x10);
        *(s32 *)(s0 + 0xC) += *(s32 *)(s0 + 0x18);
    }
    if (*(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0xDE) < -0xFA0) {
        func_8012C218((void *)s0);
        /* array decl adopted for slate agreement (func_8017EA48 owns the array
         * spelling); the &[0] cast keeps the store non-MEM_IN_STRUCT so codegen is
         * byte-identical to the original scalar form (expr.c:4567 INDIRECT_REF). */
        *(s32 *)&D_801270C8[0] = 0;
    } else {
        extern s16 D_80126CB4;
        extern s16 D_80126CB6;
        extern s16 D_80126CB8;

        t = *(u16 *)(s0 + 0x84) - 1;
        *(u16 *)(s0 + 0x84) = t;
        if (t == 0) {
            func_8002D4C8(0x526, 0);
            *(u16 *)(s0 + 0x84) = 10;
        }
        D_80126CB4 = *(u16 *)(s0 + 0x6);
        D_80126CB6 = *(u16 *)(s0 + 0xA);
        D_80126CB8 = *(u16 *)(s0 + 0xE);
    }
}


extern void (*D_8018C08C[])(void);
extern void (*D_8018C074[])(void);

void func_80181668(s32 a0) {
    u16 tag = *(u16 *)((s32)a0 + 0x2);

    if (tag != 0) {
        if (*(s16 *)((s32)a0 + 0x76) < 0x320) {
            D_8018C08C[*(s16 *)((s32)a0 + 0x102)]();
        } else {
            D_8018C074[tag]();
        }
    } else {
        D_8018C074[0]();
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8016AA50(s32 param_1, s32 param_2);

void func_801816EC(s32 a0) {
    s32 s0;
    s32 p;

    s0 = a0;
    *(s16 *)(s0 + 0xAA) = 0;
    *(s16 *)(s0 + 0x5C) = 0;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = 0x1800;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = 0x1800;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1A) = 0x100;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) |= 0x10;
    *(s16 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x1C) = 0x1E;
    *(s16 *)(s0 + 0x98) = 0;
    func_8002D4C8(0x526, 0);

    p = s0;
    *(u16 *)(p + 0x7C) = *(u16 *)(p + 6);
    *(u16 *)(p + 0x7E) = *(u16 *)(p + 0xA);
    *(u16 *)(p + 0x80) = *(u16 *)(p + 0xE);
    func_8016AA50(p, 0xA);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern s32 func_8012CBCC(s32 a0);

void func_8018178C(s32 a0)
{
    switch (*(u16 *)(a0 + 0x34)) {
    case 0: {
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = v0;
        if (v0 == 0) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    }
    case 1: {
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = v0;
        if ((v0 & 2) != 0) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1600;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1600;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x400;
        } else {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1800;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1800;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x100;
        }
        if (*(s32 *)(a0 + 0x1C) == 0) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) &= 0xFFEF;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1000;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1000;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1000;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40;
            func_8012B23C(a0);
        }
        break;
    }
    case 2:
        if (func_8012CBCC(a0) != 0) {
            *(s16 *)(a0 + 0x98) = 1;
            __asm__ __volatile__("" ::: "memory");
            {
                register s32 t __asm__("$2");
                t = *(u16 *)(a0 + 0x76) - 0xA;
                *(u16 *)(a0 + 0x5C) = 0x8810;
                *(s16 *)(a0 + 0x76) = t;
            }
            *(u8 *)(a0 + 0xC1) = 0;
            *(s32 *)(a0 + 0x1C) = 1;
            *(s32 *)(a0 + 0xB4) &= ~1;
            *(s32 *)(a0 + 0xC4) |= 2;
            if (*(s16 *)(a0 + 0x76) < 0x370) {
                *(s16 *)(a0 + 0x76) = 0x2BC;
            }
        }
        break;
    }
}


#include "common.h"

extern u8 D_80126B5C;
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801B0DA4[];
extern u8 D_801B0DD4[];

void func_80181954(s32 a0) {
    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    s32 s0;
    s32 v1;
    s32 ret;
    s32 v0;
    u8 flag;

    s0 = a0;
    ret = func_8012B6D4((s16 *)(s0 + 0x4), (s16 *)&D_80126B5C);
    ret = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), ret, 4);
    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + ret;

    v0 = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v0;
    if (v0 != 0) {
        goto end;
    }

    flag = *(u8 *)(s0 + 0xFF) ^ 1;
    *(u8 *)(s0 + 0xFF) = flag;
    if (flag != 0) {
        *(s32 *)(s0 + 0x1C) = 5;
        func_8012A828(s0, D_801B0DA4);
        func_8002D4C8(0x525, 0);
    } else {
        *(s32 *)(s0 + 0x1C) = 0xF;
        func_8012A828(s0, D_801B0DD4);
    }

end:
    D_80126CB4 = *(u16 *)(s0 + 0x6);
    D_80126CB6 = *(u16 *)(s0 + 0xA);
    D_80126CB8 = *(u16 *)(s0 + 0xE);
}


void func_80181A44(s32 a0) {
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_800291A0(s32, s32);
    extern u8 D_801B101C[];
    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    s32 s0;
    s32 v1;

    s0 = a0;
    func_8012A828(s0, D_801B101C);

    v1 = *(s16 *)(s0 + 6) - *(s16 *)(s0 + 0xDC);
    if (v1 < -0x60) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0xC00;
    } else if (!(v1 < 0x61)) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x400;
    } else {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
    }

    *(s16 *)(s0 + 0x84) = 0xA;
    *(s16 *)(s0 + 0x102) = 1;
    func_800291A0(0xCC, 1);

    *(u16 *)(s0 + 0x5C) = 0;
    D_80126CB4 = *(u16 *)(s0 + 6);
    D_80126CB6 = *(u16 *)(s0 + 0xA);
    D_80126CB8 = *(u16 *)(s0 + 0xE);
}


void func_80181B04(s32 a0) {
    extern u8 D_8018C03C[];
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32 func_8012CBCC(s32 a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    s32 s0;
    s32 v1;
    s16 t;

    s0 = a0;
    v1 = *(s16 *)(s0 + 6) - *(s16 *)(s0 + 0xDC);
    if (v1 < -0x60) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0xC00;
    } else if (!(v1 < 0x61)) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x400;
    } else {
        *(s16 *)(s0 + 0x102) = 2;
    }

    func_8012B1B4(s0, (s32)D_8018C03C);
    v1 = func_8012CBCC(s0);
    if (v1 & 0x6000) {
        *(s16 *)(s0 + 0x16) = -4;
    }

    t = *(u16 *)(s0 + 0x84) - 1;
    *(u16 *)(s0 + 0x84) = t;
    if (t == 0) {
        func_8002D4C8(0x526, 0);
        *(u16 *)(s0 + 0x84) = 10;
    }
    D_80126CB4 = *(u16 *)(s0 + 6);
    D_80126CB6 = *(u16 *)(s0 + 0xA);
    D_80126CB8 = *(u16 *)(s0 + 0xE);
}



extern void (*D_8018C0EC[])(void);

void func_80181BE8(void *a0) {
    D_8018C0EC[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80181C24(s32 a0)
{
    extern u8 D_8018C0B8[];
    extern u8 D_801B35E8[];
    extern u8 D_8018C0A8[];

    if (func_8012C354(a0, (s32)D_8018C0B8) == 0)
        return;

    if (*(s16 *)(a0 + 0x70) == 0) {
        *(s16 *)(a0 + 2) = 1;
        *(s16 *)(a0 + 0xAE) = -1;
        *(s8 *)(a0 + 0x75) = 2;
        return;
    }

    func_8001C214(*(s32 *)(a0 + 0x20), (s32)D_801B35E8);
    *(s32 *)(a0 + 0x58) = (s32)D_8018C0A8 | 0x40000000 | 0x20000000;

    *(s16 *)(a0 + 2) = 1;
    *(s16 *)(a0 + 0xAE) = -1;
    *(s8 *)(a0 + 0x75) = 2;
}


void func_80181CB4(void) {
}


extern void (*D_8018C150[])(void);

void func_80181CBC(void *a0) {
    D_8018C150[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_8018C104[])(void);
extern u8 D_80187704[];
extern s32 func_80181E30(void *);

void func_80181CF8(s32 a0)
{
    s32 s0 = a0;
    s32 v1;

    if (func_8012C354(a0, (s32)D_8018C104) == 0) {
        return;
    }

    if ((u32)func_80029504() >= 0x384) {
        goto L_cae4;
    }

    if (*(s16 *)(s0 + 0x70) != 0) {
        goto L_setup;
    }

    v1 = func_800291B4(0xCC) & 0xFF;
    if (v1 >= 3) {
        func_8012CAE4(s0);
        return;
    }
    if (v1 >= 0xF) {
        goto L_setup;
    }

L_cae4:
    func_8012CAE4(s0);
    return;

L_setup:
    *(u8 *)(s0 + 0xC0) = 1;
    *(s16 *)(s0 + 0x2) = 1;
    func_8012A828(s0, (s32)D_80187704);
    func_801788B8(s0, (s32)func_80181E30);
}


void func_80181DB0(void) {
}

extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_8018C138;
    void func_80181DB8(int param_1) {
        int iVar1;
        iVar1 = param_1;
        ((void (*)(int, int))func_80178CBC)(iVar1, &D_8018C138);
        *(short *)(iVar1 + 2) = 0x3;
    }



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80181DF0(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8(void);
extern void func_80172710(void);

s32 func_80181E30(void *a0)
{
    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x1000) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 2;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_8018C230[])(void);

void func_80181E8C(void *a0) {
    D_8018C230[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int rand(void);
extern int D_8018C220;
extern int *D_8018C1F0[];

void func_80181EC8(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018C220;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
        *(int *)(param_1 + 0xdc) = *(int *)(D_8018C1F0[*(unsigned short *)(param_1 + 0x70) & 0xf] + (rand() % 3));
        *(unsigned short *)(param_1 + 0xfc) = (*(unsigned short *)(param_1 + 0x70) >> 12) << 9;
    }
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_80181F94);

extern void func_8002A04C(s32 a0);
    extern void func_8012C098(void);
    void func_801820AC(s32 param_1) {
        ((void (*)(void))func_8002A04C)();
        ((void (*)(s32))func_8012C098)(param_1);
    }


extern void func_8002D4C8(s32 a0, s32 a1);

void func_801820DC(s32 a0) {
    s16 sp[3];
    u16 t;

    t = *(u16 *)(a0 + 0x5E);
    if (t == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (t == 0x24) {
        sp[0] = 2;
        sp[1] = 0xF;
        sp[2] = -2;
        func_8018732C(a0, (u16 *)sp, 0xD);
    }
}



/* func_80182148 — light/colour ramp-up on the entity's attached prim block.
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
void func_80182148(int param_1) {
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


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_801821D0);


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

void func_80182214(s32 param_1) {

    extern s16 D_80126CE0;
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



void func_801822B8(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_801822C8(s32 param_1) {
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
extern void D_801CAB58;

void func_80182374(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801CAB58)) {
        func_8012A828(arg0, &D_801CAB58);
    }
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_801823BC);

extern void func_8002A04C(s32 a0);
extern void func_8012C098(void);

void func_80182420(s32 arg0) {
    if (*(u16 *)(arg0 + 0x72) & 0x4000) {
        *(u16 *)(arg0 + 0x98) = 0;
        func_8002A04C(arg0);
        ((s32 (*)(s32))func_8012C098)(arg0);
    }
}



extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801CAFE0;

void func_80182468(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801CAFE0);
    *(s32 *)(a0 + 0x1C) = 0x14;
}


extern void func_8012A828(s32 a0, void *a1);
extern void D_801CAB58;

s32 func_801824A8(s32 s0)
{
    *(s16 *)(s0 + 0x2) = 3;
    func_8012A828(s0, &D_801CAB58);
    *(u16 *)(s0 + 0x5C) = 0xA810;
    *(s16 *)(s0 + 0x5E) = 0;
    *(s16 *)(s0 + 0xDC) = 0;
    *(s32 *)(s0 + 0x1C) = 0xA;
    *(s16 *)(s0 + 0xFE) = 0;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801CACF8;

void func_801824FC(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801CACF8);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_80182558(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x5;
        *(s32 *)((s32)a0 + 0x1C) = 0x14;
    }


#include "common.h"

/*
 * func_8018256C — ov_SC03_007 @ 0x8018256C (152 ins)
 *
 * Sibling of the banked func_8017EA48 (same collision-probe tail) but this
 * variant pushes the actor's OWN matrix (*(s32*)(p+0x20) + 0x34) into the GTE
 * via func_8004914C / func_800491AC instead of building one locally.
 *
 * Frame 0x78:
 *   sp+0x10 .. 0x28   outgoing args (func_8012F568 takes 6)
 *   sp+0x38  v0   SV4_8018256C  RotTransSV out #1
 *   sp+0x40  v1   SV4_8018256C  RotTransSV out #2
 *   sp+0x48  c0   SV4_8018256C  copy of v0 -> func_80135888 arg2
 *   sp+0x50  c1   SV4_8018256C  copy of v1 -> func_80135888 arg3
 *   sp+0x58  buf  SV4_8018256C  RotTransSV scratch arg2
 */

/* Bodies identical to engine_types.h's MTX / SV4; per-function names per the
 * *_<addr> house convention (law 8: same name => same body, else a new name).
 * `mtx` is DECLARED AND NEVER USED — it is the frame tell (S193-I): the target's
 * locals start at sp+0x38, i.e. 0x20 above the 0x18-byte outgoing-arg area, and
 * every $sp displacement was uniformly short by 0x20 until this 32-byte aggregate
 * was declared ahead of them.  gcc-2.7.2 assigns a stack slot in expand_decl for
 * every declared aggregate, used or not.  Do not delete it. */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8018256C;  /* 0x20 */
typedef struct { s16 a, b, c, d; } SV4_8018256C;

extern void func_8004914C(void *a0);                                   /* TU:3117 verbatim */
extern void func_800491AC(void *a0);                                   /* TU:3118 verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);                  /* TU:3119 verbatim */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);              /* TU:588  verbatim */
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);                      /* TU:4488 verbatim */
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5); /* fleet modal x2820 */
extern void func_8002D4C8(s32 a0, s32 a1);                             /* TU:57   verbatim */
extern s32 func_8012BEE8(s32 a0);                                      /* TU:4320 verbatim */
extern void func_8012A828(s32 a0, void *a1);                           /* TU:4575 verbatim */

extern s32 D_80126B58;          /* TU:53   verbatim */
extern s32 D_801270C8[];        /* TU:4480 verbatim */
extern u8 D_801152A8[];         /* TU:597  verbatim */
extern void D_801CAB58;         /* TU:5246 verbatim */
extern SV4_8018256C D_8018C340[];        /* overlay-local canned SVECTOR pair */

void func_8018256C(s32 param_1)
{
    MTX_8018256C mtx;   /* sp+0x18 : declared, never used (frame tell, S193-I) */
    SV4_8018256C v0;    /* sp+0x38 */
    SV4_8018256C v1;    /* sp+0x40 */
    SV4_8018256C c0;    /* sp+0x48 */
    SV4_8018256C c1;    /* sp+0x50 */
    SV4_8018256C buf;   /* sp+0x58 */
    u8 *base = (u8 *)&D_80126B58;
    s32 r;
    s32 ok;
    s32 q;

    if (*(s32 *)(param_1 + 0x1C) == 9) {
        func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
        func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

        RotTransSV(&D_8018C340[0], &v0, &buf);
        RotTransSV(&D_8018C340[1], &v1, &buf);

        q = D_801270C8[0];
        if ((*(u16 *)(q + 0x5C) & 0x8000) != 0) {
            if (*(u16 *)(q + 0x5E) != 1) {
                /* NOT `ok = q && *(s16*)(q+0x76) > 0;` — the TRUTH_ANDIF value
                 * expansion lets cse's skip_blocks walk the single-use around-jump
                 * (cse.c:8100) and MERGE the two `1` compare constants into one
                 * pseudo, costing the target's second `addiu $v0,$zero,1`.
                 * The explicit if/else keeps them two pseudos.  */
                if (q != 0) {
                    ok = (*(s16 *)(q + 0x76) > 0);
                } else {
                    ok = 0;
                }
                if (ok == 1) {
                    c0 = v0;
                    c1 = v1;
                    if (func_80135888(*(s32 *)(D_801270C8[0] + 0x20),
                                      *(s32 *)(D_801270C8[0] + 0x58),
                                      (s32)&c0, (s32)&c1) != 0) {
                        *(u16 *)(D_801270C8[0] + 0x5C) |= 1;
                        *(s16 *)(D_801270C8[0] + 0x60) = 9;
                        *(u16 *)(D_801270C8[0] + 0x62) =
                            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
                        *(s16 *)(D_801270C8[0] + 0x5E) = 1;
                    }
                }
            }
        }

        r = func_8012DF34(param_1, (s32)&v0, (s32)&v1);
        if (r == 1) {
            func_8012F568(1, 1, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), 9,
                          (s32)&v1, (s32)D_801152A8);
            if (*(s16 *)(param_1 + 0x70) == r) {
                *(u16 *)(base + 0x3E) |= 0x800;
            }
        }
        func_8002D4C8(0x43E, 0);
    }

    if (func_8012BEE8(param_1) != 0) {
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        *(s16 *)(param_1 + 0x2) = 3;
        func_8012A828(param_1, &D_801CAB58);
        *(u16 *)(param_1 + 0x5C) = 0xA810;
        *(s16 *)(param_1 + 0x5E) = 0;
        *(s16 *)(param_1 + 0xDC) = 0;
        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(s16 *)(param_1 + 0xFE) = 0;
    }
}


#include "common.h"

extern void (*D_8018C350[])(void);

void func_801827CC(void *a0) {
    D_8018C350[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

extern u8 D_801CB130[];
extern u8 D_8018C374[];




void func_8018283C(s32 *self)
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

    if (*(s32 *)(*(s32 *)((s32)self + 0x64) + 0x90) != (s32)D_801CB130) {
        *(s16 *)(*(s32 *)((s32)self + 0x20) + 0x12) =
            *(u16 *)((s32)self + 0xFE);
        *(s32 *)((s32)self + 0x4) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x4);
        *(s32 *)((s32)self + 0x8) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x8);
        *(s32 *)((s32)self + 0xC) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0xC);
    } else {
        func_8012F214(*(s32 *)((s32)self + 0x64), (s32)D_8018C374, (s32)&out);
        *(s16 *)((s32)self + 0x6) = out.a;
        *(s16 *)((s32)self + 0xA) = out.b;
        *(s16 *)((s32)self + 0xE) = out.c;
    }

    *(Blk8 *)(*(s32 *)((s32)self + 0x20) + 0x18) =
        *(Blk8 *)(*(s32 *)((s32)tgt + 0x20) + 0x18);

    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x2C) =
        *(u16 *)(*(s32 *)((s32)tgt + 0x20) + 0x2C);

    *(s32 *)(*(s32 *)((s32)self + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)((s32)tgt + 0x20) + 0x4);

    *(s32 *)(*(s32 *)((s32)self + 0x20) + 0x4) &= 0x7FFFFFFF;
}



extern void (*D_8018C37C[])(void);

void func_801829DC(void *a0) {
    D_8018C37C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182A18(int param_1) {
    *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1a) += 0x200;
    if (*(short *)(*(int *)(param_1 + 0x20) + 0x1a) >= 0x1001) {
        *(unsigned short *)(param_1 + 2) = 1;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x1000;
        *(unsigned short *)(param_1 + 0x5c) = 0xa810;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x2c) &= 0xffef;
    }
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_80182A80);

extern s32 func_8012BEE8(s32 arg);
    extern s32 func_801824A8();
    void func_80182AC4(s32 param_1) {
        if (((s32 (*)(void))func_8012BEE8)() != 0) {
            ((void (*)(s32))func_801824A8)(param_1);
        }
    }


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_80182AFC);


// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80182558(void*);

void func_80182BA4(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_80182558)(param_1);
    }
}


#include "common.h"

extern s32 func_800291B4(s32 arg);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern u16 D_801274E4[];
extern u8 D_8018C248[];
extern u32 D_8018C2B0;
extern u8 D_801CAF38[];

void func_80182BFC(s32 a0)
{
    s32 v0;
    s32 v1;
    s16 s0;
    s32 t0;

    v1 = func_800291B4(0xCC) & 0xFF;
    if (v1 == 4 || v1 == 0xC || v1 == 5) {
        v0 = 1;
    } else {
        v0 = (v1 == 0xD);
    }
    if (v0 == 0) {
        D_801274E4[0] |= 1;
    } else {
        v0 = *(s16 *)(a0 + 0x70);
        if (func_8012C354(a0, (s32)(D_8018C248 + v0 * 52)) == 0) {
            return;
        }
        *(s8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xBC) = (s32)&D_8018C2B0;
        *(s32 *)(a0 + 0xC4) = 1;
        s0 = 1;
        t0 = 0x28;
        *(s32 *)(a0 + 0xB4) = 0xFFFBFFFD;
        *(s16 *)(a0 + 0x86) = s0;
        *(s16 *)(a0 + 0x52) = t0;
        func_8012B2CC(a0);
        *(s16 *)(a0 + 0x2) = s0;
        func_8012A828(a0, D_801CAF38);
    }
}



// @class: struct
// @stuck: none — MATCH expected (folded %lo via extern array decay; a0 carries iVar2 into func_8001C214)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_8018C36C[];

void func_80182D04(int param_1)
{
    int iVar2;
    short uVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(iVar2, D_8018C36C[*(short *)(param_1 + 0x70)]);
        uVar1 = *(short *)(*(int *)(param_1 + 100) + 0x36);
        *(short *)(param_1 + 2) = 1;
        *(short *)(param_1 + 0xfe) = 0x7fff;
        *(short *)(param_1 + 0xfc) = uVar1;
    }
    return;
}


INCLUDE_ASM("asm/ov_SC03_007/nonmatchings/ov_SC03_007_jr_8017AE2C", func_80182D88);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80182F00(void) {
        func_8002D4C8(0x6AA, 0);
    }


extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern void func_8012C098(void);

void func_80182F24(void *arg0) {
    s32 var_a0;

    func_8002A04C((s32)arg0);
    var_a0 = 3;
    if (*(u16 *)((s32)arg0 + 0x70) & 0x200) {
        var_a0 = 7;
    }
    func_8002AC00(var_a0);
    ((void (*)(s32))func_8012C098)((s32)arg0);
}


extern void func_80182FB8();
extern void func_80183004();

void func_80182F74(s32 *a0)
{
    if (*(s32 *)((s32)a0 + 0xC4) & 4)
    {
        func_80182FB8(a0);
    }
    else
    {
        func_80183004(a0);
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u16 D_801E42B0;

void func_80182FB8(s32 param_1) {
    register s32 s0 __asm__("$16") = param_1;

    *(s16 *)(s0 + 0x2) = 7;
    *(s16 *)(s0 + 0x34) = 0;
    *(u16 *)(s0 + 0x5C) = 0xAA10;
    func_8012A828(s0, &D_801E42B0);
    func_8012B23C(s0);
}


extern void func_8012B23C(s32 a0);
extern s32  func_8012CE2C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32  rand(void);
extern u8   D_801E3AE0[];

void func_80183004(s32 a0) {
    s32 v0;
    s32 v1;

    *(s16 *)(a0 + 0x2) = 3;
    *(u16 *)(a0 + 0x34) = 0;
    {
        s32 magic = 0xAA10;
        *(s16 *)(a0 + 0x5C) = magic;
    }
    *(s32 *)(a0 + 0x1C) = (rand() & 0x1F) + 0x28;
    v0 = rand() & 0x3FF;
    v1 = v0 - 0x200;
    if (v1 >= 0) {
        v1 = v0 + 0x100;
    } else {
        v1 = v0 - 0x500;
    }
    v0 = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(v0 + 0x12);
    v0 = (v0 + v1) & 0xFFF;
    *(s16 *)(a0 + 0xFC) = v0;
    func_8012B23C(a0);
    if (func_8012CE2C(a0) != 0) {
        v0 = *(u16 *)(a0 + 0x86) | 1;
    } else {
        v0 = *(u16 *)(a0 + 0x86) & 0xFFFE;
    }
    *(u16 *)(a0 + 0x86) = v0;
    func_8012A828(a0, (void *)D_801E3AE0);
}


#include "common.h"

/* decl_prior fleet-modal spellings (no TU decl found in ov_SC03_007_jr_8017AE2C.c) */
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012CE2C(s32 a0);

/* func_801832B4 is an INCLUDE_ASM stub in THIS TU with no established arity yet;
   the asm shows it called with one arg (pv) so we declare it that way (the "def"
   in decl_prior is a different, coincidentally-same-address function in
   ov_SC04_011 and is not authoritative here). */
extern void func_801832B4(s32 a0);

/* TU-authoritative spellings, copied verbatim from elsewhere in
   ov_SC03_007_jr_8017AE2C.c (law 2). */
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);   /* raw-void TU decl; cast to (s32(*)(s32)) at the call site, law 4 */
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012B23C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

/* func_80182D88 and func_80183284 are defined in THIS TU (the latter already
   matched a few lines below our INCLUDE_ASM stub); adopt its real signature. */
extern void func_80182D88(s32 a0);
extern void func_80183284(short *a0);

/* Raw scalar globals local to this overlay (no cross-overlay symbol reuse is
   authoritative -- ov_SC03_119/118's D_8018C50C is a coincidentally-same-address,
   unrelated overlay global). D_8018C50C is read as a plain word here (offset 0,
   no index), D_801E3AE0 is only ever address-of'd (handler-table id, matching
   this TU's existing "extern short D_xxx;" idiom for func_8012A828's a1 args). */
extern s32 D_8018C50C;
extern u8  D_801E3AE0[];

void func_801830C0(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    s32 v0 = func_8012BCCC(pv);

    if (v0 <= 0x10000) {
        func_801832B4(pv);
        return;
    }

    if (*(s32 *)(pv + 0x1C) >= 8) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12),
                               *(s16 *)(pv + 0xFC), 8);
        *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
    }

    func_8012B178(pv, D_8018C50C);

    if ((*(u16 *)(pv + 0x86) & 1) != 0) {
        s32 mask = ((s32 (*)(s32))func_8012CBA4)(pv) & 0x2000;
        if (mask == 0) {
            func_8012ADE4((u8 *)pv);
        }
    } else {
        s32 mask = func_8012CBCC(pv) & 0x2000;
        if (mask != 0) {
            *(u16 *)(pv + 0x86) |= 1;
        }
    }

    func_80182D88(pv);

    if (func_8012BEE8(pv) != 0) {
        if ((*(u16 *)(pv + 0x86) & 1) != 0) {
            func_80183284((short *)pv);
            return;
        }

        *(s16 *)(pv + 0x2) = 3;
        *(s16 *)(pv + 0x34) = 0;
        *(u16 *)(pv + 0x5C) = 0xAA10;

        {
            s32 t = rand() & 0x1F;
            t += 0x28;
            *(s32 *)(pv + 0x1C) = t;
        }

        {
            s32 r2 = rand() & 0x3FF;
            s32 off = r2 - 0x200;
            if (off >= 0) {
                off = r2 + 0x100;
            } else {
                off = r2 - 0x500;
            }

            {
                s32 v1 = *(u16 *)(*(s32 *)(pv + 0x20) + 0x12);
                v1 = (v1 + off) & 0xFFF;
                *(s16 *)(pv + 0xFC) = v1;
            }
            func_8012B23C(pv);
        }

        if (func_8012CE2C(pv) != 0) {
            *(u16 *)(pv + 0x86) |= 1;
        } else {
            *(u16 *)(pv + 0x86) &= 0xFFFE;
        }

        func_8012A828(pv, (void *)D_801E3AE0);
    }
}




extern void func_8012A828(s32, void*);
    extern short D_801E3998;
    void func_80183284(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x4;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801E3998);
    }


extern void func_8012A828(s32 a0, void *a1);

extern u8 D_801E4B08[];
extern u8 D_801E3B88[];
extern u8 D_801E3C10[];

void func_801832B4(s32 a0) {
    *(u16 *)(a0 + 0x2) = 5;
    if ((*(u16 *)(a0 + 0x86) & 0x2) != 0) {
        *(u16 *)(a0 + 0x34) = 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
        if ((*(u16 *)(a0 + 0x70) & 0x200) != 0) {
            func_8012A828(a0, (void *)D_801E4B08);
        } else {
            func_8012A828(a0, (void *)D_801E3B88);
        }
        *(u16 *)(a0 + 0xFE) = 0;
    } else {
        *(u16 *)(a0 + 0x34) = 0;
        func_8012A828(a0, (void *)D_801E3C10);
        *(s32 *)(a0 + 0x1C) = 0x19;
        *(u16 *)(a0 + 0x86) = (*(u16 *)(a0 + 0x86) | 0x2);
    }
}


#include "common.h"

/* func_8018335C -- ov_SC03_007 state handler (state word at +0x34: 0 = wind-up, 1 = active).
 * House style copied from the destination TU (src/ov_SC03_007/ov_SC03_007_jr_8017AE2C.c):
 * s32 object handle + explicit width casts, per-function extern block.
 */

extern s32  func_8012B8E4(s32 arg0, s32 arg1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32  func_8012CBCC(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern void func_8012B23C(s32 a0);
extern s32  func_8012CE2C(s32 a0);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_80182D88(s32 a0);
extern void func_80183670(s32 a0, s32 a1, s32 a2, void *a3);
extern s32  rand(void);

extern u8  D_801E4B08[];
extern u8  D_801E3B88[];
extern u8  D_801E3C10[];
extern u8  D_801E3AE0[];
extern u8  D_801E3CE0[];
extern u8  D_8018C514[];
extern s32 D_8018C510;
extern s32 D_801E9CD8;

void func_8018335C(s32 a0)
{
    u16 st;
    s32 v;
    unsigned short *p;

    st = *(u16 *)(a0 + 0x34);
    switch (st) {
    case 0:
        v = func_8012B8E4(a0, 4);
        p = (unsigned short *)(*(s32 *)(a0 + 0x20) + 0x12);
        *p = (unsigned short)(*p + v);

        if (*(s32 *)(a0 + 0x1C) == 0xF) {
            ((void (*)(s32, s32))func_80142414)(a0, -0x78);
            func_8002D4C8(0x6A9, 0);
        }

        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x2) = 5;
            if ((*(u16 *)(a0 + 0x86) & 0x2) != 0) {
                *(u16 *)(a0 + 0x34) = 1;
                *(s32 *)(a0 + 0x1C) = 0x28;
                if ((*(u16 *)(a0 + 0x70) & 0x200) != 0) {
                    func_8012A828(a0, (void *)D_801E4B08);
                } else {
                    func_8012A828(a0, (void *)D_801E3B88);
                }
                *(s16 *)(a0 + 0xFE) = 0;
            } else {
                *(u16 *)(a0 + 0x34) = 0;
                func_8012A828(a0, (void *)D_801E3C10);
                *(s32 *)(a0 + 0x1C) = 0x19;
                *(u16 *)(a0 + 0x86) = *(u16 *)(a0 + 0x86) | 0x2;
            }
        }
        break;
    case 1:
    {
        s16 t;

        if (*(s32 *)(a0 + 0x1C) >= 0x16) {
            v = func_8012B8E4(a0, 6);
            p = (unsigned short *)(*(s32 *)(a0 + 0x20) + 0x12);
            *p = (unsigned short)(*p + v);
        }

        func_8012B178(a0, D_8018C510);

        if ((*(u16 *)(a0 + 0x86) & 0x1) != 0) {
            if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) == 0) {
                func_8012ADE4((u8 *)a0);
            }
        } else {
            if ((func_8012CBCC(a0) & 0x2000) != 0) {
                *(u16 *)(a0 + 0x86) = *(u16 *)(a0 + 0x86) | 0x1;
            }
        }

        func_80182D88(a0);

        t = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = t;
        if (t <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }

        if (func_8012BEE8(a0) != 0) {
            s32 r;
            s32 d;

            *(u16 *)(a0 + 0x2) = 3;
            *(u16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 0x5C) = (u16)0xAA10;
            *(s32 *)(a0 + 0x1C) = (rand() & 0x1F) + 0x28;

            r = rand() & 0x3FF;
            d = r - 0x200;
            if (d < 0) {
                d = r - 0x500;
            } else {
                d = r + 0x100;
            }
            *(u16 *)(a0 + 0xFC) =
                (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d) & 0xFFF;
            func_8012B23C(a0);

            if (func_8012CE2C(a0) != 0) {
                *(u16 *)(a0 + 0x86) = *(u16 *)(a0 + 0x86) | 0x1;
            } else {
                *(u16 *)(a0 + 0x86) = *(u16 *)(a0 + 0x86) & 0xFFFE;
            }
            func_8012A828(a0, (void *)D_801E3AE0);
        }

        if (func_8012BD3C(a0, 0x200, 0x1440) != 0) {
            if ((*(u16 *)(a0 + 0x70) & 0x200) != 0) {
                func_80183670(a0, 3, 0x28, (void *)D_8018C514);
                D_801E9CD8 = D_8018C510;
                func_8002D4C8(0x660, 0);
            } else {
                func_80183670(a0, 0, 0x14, (void *)D_801E3CE0);
            }
        }
        break;
    }
    }
}


extern void func_8012A828(s32 a0, void *a1);

void func_80183670(s32 a0, s32 a1, s32 a2, void *a3) {
    *(s16 *)(a0 + 0x34) = a1;
    *(s16 *)(a0 + 0x2) = 6;
    func_8012A828(a0, a3);
    *(s32 *)(a0 + 0x1C) = a2;
}


#include "common.h"

typedef struct { s16 a, b, c, d; } SV4_801836B8;
/* MATRIX_L48 shape, same as the twin func_8017EA48's MTX local (0x20 bytes). Declared but
 * NEVER read/written here -- the frame reserves it (empirically required: dropping it shifts
 * every local $sp offset down by 0x20 and shrinks the frame by 0x20, both wrong) but no
 * instruction touches it. A leftover from the same source template as func_8017EA48, which
 * DOES build and use a local MTX; this sibling calls func_8004914C/func_800491AC on the
 * object's own field pointer instead and simply never deleted the now-dead local. */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_801836B8;

extern s32 D_801270C8[];
extern SV4_801836B8 D_8018C524[];
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u8 D_801152A8[];

void func_801836B8(s32 param_1, s32 param_2)
{
    MTX_801836B8 mtx;  /* sp+0x18 : unused, see typedef comment above */
    SV4_801836B8 v0;   /* sp+0x38 : RotTransSV out #1 */
    SV4_801836B8 v1;   /* sp+0x40 : RotTransSV out #2 */
    SV4_801836B8 c0;   /* sp+0x48 : copy of v0 -> func_80135888 arg2 */
    SV4_801836B8 c1;   /* sp+0x50 : copy of v1 -> func_80135888 arg3 */
    SV4_801836B8 buf;  /* sp+0x58 : RotTransSV scratch arg2 */
    s32 flag;

    func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

    RotTransSV(&D_8018C524[0], &v0, &buf);
    RotTransSV(&D_8018C524[1], &v1, &buf);

    if (D_801270C8[0] == 0) {
        flag = 0;
    } else {
        flag = (0 < *(s16 *)(D_801270C8[0] + 0x76));
    }

    if (flag == 1) {
        if ((*(u16 *)(D_801270C8[0] + 0x5C) & 0x8000) != 0) {
            if (*(u16 *)(D_801270C8[0] + 0x5E) != flag) {
                c0 = v0;
                c1 = v1;
                if (func_80135888(*(s32 *)(D_801270C8[0] + 0x20),
                                   *(s32 *)(D_801270C8[0] + 0x58),
                                   (s32)&c0, (s32)&c1) != 0) {
                    *(u16 *)(D_801270C8[0] + 0x5C) |= 1;
                    *(s16 *)(D_801270C8[0] + 0x60) = param_2;
                    *(u16 *)(D_801270C8[0] + 0x62) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
                    *(s16 *)(D_801270C8[0] + 0x5E) = 1;
                }
            }
        }
    }

    if (func_8012DF34(param_1, (s32)&v0, (s32)&v1) == 1) {
        func_8012F568(1, 1, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), param_2,
                      (s32)&v1, (s32)D_801152A8);
    }
}
