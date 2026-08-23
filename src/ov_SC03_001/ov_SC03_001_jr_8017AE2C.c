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
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018FA44;
extern u8 D_8018F9B4;
extern u8 D_8018F990;
extern u8 D_8018F96C;
extern u8 D_8018FA20;
extern u8 D_8018F9FC;
extern u8 D_8018F9D8;
extern u8 D_8018F948;
extern void func_80145934(void);
extern u8 D_8018FAD4;
extern u8 D_8018FAB0;
extern u8 D_8018FA8C;
extern u8 D_8018FA68;
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
extern unsigned char D_8018EECC[];
extern unsigned char D_8018EEFC[];
extern unsigned char D_8018EF4C[];
extern unsigned char D_8018EF7C[];
extern unsigned char D_8018EFAC[];
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
extern void (*D_8018EFFC[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_8018F0C4[];
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
extern u8 D_8018F14C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018F154;
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
extern int D_801ED4D8;
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
extern s32 D_801ED4DC;
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
extern s32 D_8018F184;
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
extern void (*D_8018F22C[])(void);
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
extern void (*D_8018F250[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018F240;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018F264[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018F270[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018F280[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018F298[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018F288;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018F2AC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018F2C8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018F2B8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018F2DC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018F2F0[])(void);
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
extern s32 D_8018F304;
extern void (*D_8018F32C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018F30C;
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
extern int (*D_8018F378[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018F37C[])(void);
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
extern unsigned short D_8018F7E0[];
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
extern void (*D_8018F7F0[])(void);
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
extern int D_801ED510;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018F818[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018F7F8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018F808;
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
extern void (*D_8018F858[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018F860[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018F82C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018F86C[])(void);
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
extern u8 D_8018F83C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801ED518;
extern s32 D_801ED524;
extern s32 D_801ED528;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018F8A8[])(s32 *);
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
extern s32 D_8018F87C[];
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
extern s32 D_801ED520;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018FAF8[])(void);
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
extern char D_8018F918[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018FB9C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018FCF0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018FB0C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018FCF8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018FB1C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018FB3C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018FD00[])(void);
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
extern void (*D_8018FD28[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018FD34[])(void);
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
extern void (*D_8018FBA8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018FDD8;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018EEBC[];
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
extern unsigned char D_8018FDEC[];
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
extern s8 D_8018FE28[];
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
extern u16 D_8018FE70;
extern u16 D_8018FE72;
extern u16 D_8018FE74;
extern s32 D_8018FE78;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018FE80;
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
extern int D_8018FB8C;
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
extern unsigned int D_8018FF04[];
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
extern void (*D_8018FFB4[])(void);
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
extern u16 D_8018FFE4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80190048;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801ED530[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8019006C[])(void);
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
extern int D_801ED588[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801900B4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801900A4;
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
extern char D_801EC888[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801900BC[])(void);
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
extern void (*D_80190110[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801900D8;
extern s16 D_8019010C;
extern s16 D_8019010A;
extern s16 D_80190108;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8019011C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801ED5E8;
extern u8 D_801ED5E9;
extern u8 D_801ED5EA;
extern u8 D_801ED5EB;
extern u8 D_801ED5EC;
extern u8 D_801ED5ED;
extern u8 D_801ED5EE;
extern u8 D_801ED5EF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8019012C[])(void);
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
extern s32 D_801ED628;
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
extern void (*D_80190170[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801901EC[];
extern s32 D_8019020C[];
extern u8 D_80190288[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801902A8[];
extern u8 D_801902C8[];
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
extern void (*D_80190364[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801903E0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801EC898;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801903EC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801903F4[])(void);
extern void func_801663FC(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_801904BC[])(void);
extern void func_80166618(void *a0);
extern void (*D_801904CC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801904DC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801904E8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80190448[];
extern u8   D_8019045C[];
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
extern void (*D_80190500[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80190508[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80190510[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80190518[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80190520[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80190528[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80190530[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801905E4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801905EC[])(void);
extern void func_80169F00(void *a0);
extern char D_8019059C[];
extern char D_8019055C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80190624[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80190630[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80190678[])(void);
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
extern void (*D_801906F4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801ED948;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801906E8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8019072C[];
extern unsigned short D_80190734[];
extern unsigned short D_8019073C[];
extern unsigned char D_801ED950[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801ED948;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80190744[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EDA84;
extern M2C_UNK D_801EDA88;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EDA10;
extern void (*D_80190774[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EDA8C[];
extern u8 D_801EDA94[];
extern u8 D_801EDA44[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8019077C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80190798[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801907A0[])(void);
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
extern void (*D_80190808[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801907AC;
extern u8 D_801907B8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8019083C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80190844[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80190898[])(void);
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
extern u16 D_801908CC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801908BC[];
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
extern s32 D_801908E8;
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
extern void (*D_80190960[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80190968[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80190970[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80190978[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80190980[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80190988[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80190994[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801909A0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801909AC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801909BC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801909CC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801909D4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801909DC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801909E4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801909EC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801909F4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_801909FC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80190A04[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80190A0C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80190A14[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80190A1C[])(void);
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
extern void (*D_80190A24[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80190A2C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80190A34[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80190A3C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80190A44[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80190A4C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80190A54[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80190A5C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80190A64[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80190A6C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80190A74[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80190A7C[])(void);
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
extern void (*D_80190AC0[])(void);
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
extern M2C_UNK D_80190A84;
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
extern void (*D_80190AF0[])(void);
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
extern void (*D_80190B2C[])(void);
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
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80190B84[])();
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
extern void (*D_80190B94[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80190B9C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80190D04[])();
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
extern void (*D_80190D10[])();
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
extern M2C_UNK D_801ECAE0;
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
extern s16 D_801EF3F0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern short D_801EF464;
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
extern s32 D_801EE5F4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801EE61C;
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
extern s16 D_801EE5D8;
extern s32 func_8017A3B0(void);
extern short D_801EE614;
extern short D_801EE610;
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

extern s16 D_801EF3A8;
extern s16 D_801EF3AA;
extern s16 D_801EF3B4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801EF3A8;

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
                    func_8012B744(p, &D_801EF3B4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801EF3A8+0xC == &D_801EF3B4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801EF3A8 + 0xC)) < 0x101) {
                    D_801EF3A8 = 0;
                    D_801EF3AA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801EF3B4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801EF3A8 + 0xC)) < 0x101) {
            D_801EF3A8 = 0;
            D_801EF3AA = 0;
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
    extern s16 D_801EE654;
    extern s16 D_801EE656;
    extern s16 D_801EE658;
    extern s16 D_801EE64C;
    extern s16 D_801EE64E;
    extern s16 D_801EE650;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801EE654, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801EE656, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801EE658, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801EE64C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801EE64E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801EE650, (s32)((s16)param_2));
}



extern s16 D_801EE5DC;
extern u16 D_801EE65C;
extern u16 D_801EE65E;
extern u16 D_801EE660;
extern s16 D_801EF3F0;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u16 D_80126B62;
    func_8012A418();
    D_801EF3F0 = 0;
    D_801EE5DC = 0;
    D_801EE65C = D_80126B5E;
    D_801EE65E = D_80126B62;
    D_801EE660 = D_80126B66;
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
    extern u8 D_80190E4C[];
    extern s16 D_801EE654;
    extern s16 D_801EE64C;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80190E4C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80190E4C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EE654;
        s16 *p78C = &D_801EE64C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801EF3F0 = 1;
        D_801EE5DC = 0;
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
    extern SV4_8017B368 D_801EE5FC;
    extern SV4_8017B368 D_801EE604;
    extern s16 D_801EE654;
    extern s16 D_801EE64C;
    extern u16 D_80190E4C;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801EE5FC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801EE604;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80190E4C)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80190E4C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801EE654) = loc0;
    (*(SV4_8017B368 *)&D_801EE64C) = loc1;
    D_801EF3F0 = 1;
    D_801EE5DC = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801EE5FC;
    extern SV4_8017B368 D_801EE604;
    extern s16 D_801EE654;
    extern s16 D_801EE64C;
    extern u16 D_80190E4C;
    extern s16 D_801EE5DC;
    extern s16 D_801EF3F0;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801EE5FC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801EE604;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80190E4C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80190E4C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801EE654) = loc0;
    (*(SV4_8017B368 *)&D_801EE64C) = loc1;
    D_801EF3F0 = 1;
    D_801EE5DC = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801EE654).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801EE654).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801EE654).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801EE64C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801EE64C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801EE64C).c;
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
    extern u8 D_80190E4C[];
    extern s16 D_801EE654;
    extern s16 D_801EE656;
    extern s16 D_801EE658;
    extern s16 D_801EE64C;
    extern s16 D_801EE64E;
    extern s16 D_801EE650;
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
        s32 a1addr = (s32)&D_80190E4C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80190E4C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EE654;
        s16 *p78C = &D_801EE64C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801EE656;
            v798 = D_801EE658;
            v78C = *p78C;
            v78E = D_801EE64E;
            v790 = D_801EE650;
            __asm__ __volatile__("");
            D_801EF3F0 = 1;
            D_801EE5DC = 0x1E;
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
extern s16 D_801EE5DC;
extern s16 D_801EE654;
extern s16 D_801EE656;
extern s16 D_801EE658;
extern s16 D_801EE64C;
extern s16 D_801EE64E;
extern s16 D_801EE650;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801EE5DC = 0;
    D_801EE654 = (s16) D_80114F30;
    D_801EE656 = (s16) D_80114F34;
    D_801EE658 = (s16) D_80114F38;
    D_801EE64C = (s16) D_80114F24;
    D_801EE64E = (s16) D_80114F28;
    D_801EE650 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801EE66C;
extern s16 D_801EE66E;
extern s16 D_801EE670;
extern s16 D_801EE674;
extern s16 D_801EE676;
extern s16 D_801EE678;

void func_8017B824(void) {
    D_801EE66C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801EE66E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801EE670 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801EE674 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801EE676 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801EE678 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801EE66C;
extern s16 D_801EE66E;
extern s16 D_801EE670;
extern s16 D_801EE674;
extern s16 D_801EE676;
extern s16 D_801EE678;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801EE66C;
    D_80114F34 = D_801EE66E;
    D_80114F38 = D_801EE670;
    D_80114F24 = D_801EE674;
    D_80114F28 = D_801EE676;
    D_80114F2C = D_801EE678;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801EE654), src[8..15] -> (*(S8_8017B8E8 *)&D_801EE64C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801EE654) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801EE64C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_801EE65C;
extern u16 D_801EE65E;
extern u16 D_801EE660;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801EE5DC;
extern short D_801EE664;
extern short D_801EE666;
extern short D_801EE668;
extern s16 D_801EE654;
extern s16 D_801EE656;
extern s16 D_801EE658;
extern s16 D_801EE64C;
extern s16 D_801EE64E;
extern s16 D_801EE650;

void func_8017B940(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u16 D_80126B62;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801EE65C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801EE65E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801EE660);
    (*(s16 *)&D_801EE664) = buf[0];
    (*(s16 *)&D_801EE666) = buf[1];
    (*(s16 *)&D_801EE668) = buf[2];
    D_801EE654 = D_80114F30 + buf[0];
    D_801EE5DC = 0;
    D_801EE656 = D_80114F34 + buf[1];
    D_801EE658 = D_80114F38 + buf[2];
    D_801EE64C = D_80114F24 + buf[0];
    D_801EE64E = D_80114F28 + buf[1];
    D_801EE650 = D_80114F2C + buf[2];
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

extern SV4 D_801EE5FC;
extern SV4 D_801EE604;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801EE604) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801EE5FC = svec;

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
    D_801EE604 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801EE604)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801EE5FC) = svec;

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
    (*(SV4_8017BB34*)&D_801EE604) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801EE624[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801EE624;
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
extern s16 D_801EE5DC;
extern s16 D_801EF3F0;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801EE5DC = D_801EE5DC + 1;
    if (D_801EE5DC >= 0x1F) {
        D_801EF3F0 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801EE5DC;
extern s16 D_801EF3F0;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EE5DC = D_801EE5DC + 1;
    if (0x18 < D_801EE5DC) {
        func_8012A4BC();
        D_801EF3F0 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801EE5DC;
extern void (*D_801EE620)(void);
extern short D_801EE664;
extern short D_801EE666;
extern short D_801EE668;
extern s16 D_801EF3F0;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EE5DC = D_801EE5DC + 1;
    if (D_801EE5DC >= 0x19) {
        if (D_801EE620 != 0) {
            (*D_801EE620)();
        } else {
            D_80114F30 = D_80114F30 + D_801EE664;
            D_80114F34 = D_80114F34 + D_801EE666;
            D_80114F38 = D_80114F38 + D_801EE668;
            D_80114F24 = D_80114F24 + D_801EE664;
            D_80114F28 = D_80114F28 + D_801EE666;
            D_80114F2C = D_80114F2C + D_801EE668;
            func_8012A4BC();
        }
        D_801EF3F0 = 0;
    }
}



extern void (*D_80190EEC[])(void);

void func_8017BE60(void *a0) {
    D_80190EEC[*(u8 *)((s32)a0 + 0x4)]();
}



extern void (*D_80190F8C[])(void);

void func_8017BE9C(void *a0) {
    D_80190F8C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80190F94[])(void);

void func_8017BED8(void *a0) {
    D_80190F94[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80190F9C[])(void);

void func_8017BF14(void *a0) {
    D_80190F9C[*(u16 *)((s32)a0 + 0x2)]();
}


/* Decl layer conformed to the TU (ov_SC03_001_jr_8017AE2C.c):
 *  - func_8012913C: the TU already declares `extern u8 *func_8012913C(s32 a0);`
 *    at line 7121 -- BELOW this splice point (3327), which is why cc1 reported the
 *    conflict at 7181. Copied verbatim; the s32 use is pushed to a cast at the call
 *    site, matching the idiom the TU itself uses at line 7145. Byte-neutral.
 *  - func_8012C750: not declared in this TU; conformed anyway to the canonical
 *    engine_core.h form (`s32 func_8012C750(s32 a0)`, DEFINE_func_8012C750) with the
 *    pointer arg cast at the call site, so a future macro expansion cannot collide.
 */
extern u8 D_801EE680[];
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);


/* $16-$19 are pinned: without them gcc's strength reduction splits the `s1` store
 * base into TWO induction variables (base+0x18 with offsets -4/0, plus base+0x1C),
 * burning an extra callee-saved reg and growing the frame to 0x48. s4 must stay
 * UNPINNED -- a pin collapses `$v0 = $s4 + 1; $s4 = $v0` into `addiu $s4,$s4,1` and
 * then sign-extends from $s4, losing the target's `addu $s4,$v0,$zero` + sll/sra on
 * $v0 at the loop join. It still lands in $20 naturally once $16-$19 are taken.
 */
void func_8017BF50(s32 a0)
{
    register s32 s3 asm("$19");
    register s16 *s0 asm("$16");
    register s32 *s1 asm("$17");
    register u8 *s2 asm("$18");
    s16 s4;
    Buf8017BF50 buf;

    s3 = a0;
    s0 = *(s16 **)(s3 + 0xDC);
    if (s0 != 0) {
        s2 = D_801EE680;
        s4 = 0;
        s1 = (s32 *)(D_801EE680 + 0x1C);
        buf.unk06 = 0x158;
        buf.unk0A = 0;
        buf.unk08 = 0;
        buf.unk0E = 0;
        buf.unk10 = 0;
        do {
            u16 v1;

            v1 = (u16)*s0;
            if ((v1 & 0xFFFF) == 0x8000) break;

            if (*(s16 *)(s3 + 0x70) != 0) {
                buf.unk00 = *s0++;
                buf.unk02 = *s0++;
                buf.unk04 = *s0++;
                if (((s32 (*)(void *))func_8012C750)(&buf) == 0) break;
            } else {
                s32 v3;

                v3 = ((s32 (*)(s32))func_8012913C)(0x11);
                if (v3 == 0) break;
                s1[-2] = *s0++;
                s1[-1] = *s0++;
                s1[0] = *s0++;
                s1 += 8;
                *(u8 **)(v3 + 0x30) = s2;
                s2 += 0x20;
            }
            s4++;
        } while (s4 < 0x10);
    }
    *(u16 *)(s3 + 2) += 1;
}


extern s32 D_801151D4;
extern s16 D_801EE880;
extern void func_800D23D0(void *a0);

void func_8017C094(void) {
    s16 diffs[3];
    s32 *ptr = (s32 *)D_801151D4;

    diffs[0] = (s16)(*(s32 *)((u8 *)ptr + 0x68) - *(s32 *)((u8 *)ptr + 0x5C));
    diffs[1] = (s16)(*(s32 *)((u8 *)ptr + 0x6C) - *(s32 *)((u8 *)ptr + 0x60));
    diffs[2] = (s16)(*(s32 *)((u8 *)ptr + 0x70) - *(s32 *)((u8 *)ptr + 0x64));

    func_800D23D0(diffs);

    D_801EE880 = (u16)diffs[1];
}


extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80190EF8[];

void func_8017C100(s32 param_1)
{
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(param_1 + 0x2e) == 0) {
        func_8001CB6C((u8 *)s0, (s32)D_80190EF8, 0x3c0, 0xa0);
    } else {
        func_8001CC3C(s0, (s32)D_80190EF8, 0x3c0, 0xa0);
    }
    *(u8 *)(s0 + 0x27) = 0xfc;
    *(u16 *)(s0 + 0x1a) = 0x3c00;
    *(u16 *)(s0 + 0x18) = 0x3c00;
    *(u32 *)(s0 + 0x4) |= 0x01000000;
    *(u32 *)(s0 + 0x34) = *(u32 *)(param_1 + 0x30);
    (*(u16 *)(param_1 + 0x2))++;
}


#include "common.h"

extern void RotMatrixYXZ(void *a0, void *a1);
extern s16 D_801EE880;


void func_8017C1AC(s32 param_1)
{
    SV4 sv4;
    s32 s0;
    s32 a1;

    s0 = *(s32 *)(param_1 + 0x20);
    sv4.a = -0x20;
    sv4.c = 0;
    sv4.b = D_801EE880;
    a1 = *(s32 *)(s0 + 0x34);
    RotMatrixYXZ(&sv4, a1);
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern void func_8012B260(u8 *a0);

extern u8 D_80190F74[];
extern u8 D_80190F7C[];

void func_8017C1EC(s32 a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8018D838[];
    s32 s0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        ((void (*)(s32))func_8012CAE4)(a0);
        return;
    }

    func_8001C810(s0, (s32)D_80190F74);
    func_8012A828(a0, (s32)D_8018D838);

    *(s32 *)(a0 + 0x20) = s0;
    *(s16 *)(s0 + 0x1A) = 0x3C00;
    *(s16 *)(s0 + 0x18) = 0x3C00;
    *(s16 *)(s0 + 0x10) = -0x20;
    *(s16 *)(s0 + 0x12) = -1;
    *(s32 *)(s0 + 0x4) |= 0x8040;
    *(u16 *)(s0 + 0x2C) |= 0x10;

    ((void (*)(s32))func_8012B260)(a0);

    *(s32 *)(a0 + 0x58) = (s32)D_80190F7C;
    *(u16 *)(a0 + 0x2) += 1;
}


// @class: jump-opt / cross-jump — MATCH (34 ins)
// @stuck: none.
//
// TWO byte-levers were needed here (both new, both generalizable to the 10-member family):
//
//  (1) TWO STORES, NOT A TERNARY.  The obvious `v = cond ? 0x800 : 0x40; store v;` is
//      rewritten by jump.c:699 ("Simplify if (...) x = a; else x = b;  ->  x = b;
//      if (...) x = a;") which HOISTS the `li 0x800` above the `slti`.  The hoisted li is
//      then live across the compare, so its pseudo CONFLICTS with the slt result's hard
//      reg and loses $v0 (it lands in $a1 — REGALLOC-PERM/$a1>$v0, 3 mismatches).
//      Writing the store in BOTH arms makes `prev_active_insn (simplejump)` a MEM-dest
//      set, so `GET_CODE (SET_DEST (temp4)) == REG` fails and the hoist is blocked; the
//      two arms stay in their own basic blocks, each `li` is a block-local quantity and
//      first-fits $v0 (K3).  jump2's cross-jumping then re-merges the two identical
//      `sh $v0,0x5C($a0)` tails back into one, and dbr fills the branch delay slot from
//      the TARGET thread — reproducing `bnez; li 0x800(slot); li 0x40; sh` exactly.
//
//  (2) `>=` NOT `<`.  Target is `slti; bnez` = jumpifnot of `diff >= 0x40`, so the 0x40
//      arm is the fall-through THEN and the 0x800 arm is the branch-target ELSE.
//      Writing the condition as `< 0x40` gives beqz and swaps the two `li` immediates.
//
//  (3) 8 bytes of dead stack.  Target frame is 0x28; this body's natural frame is 0x20
//      (vars=8, regs=2/0, args=16).  The original declared an 8-byte local it never
//      reads — reproduced as `unused[2]` (same device as ov_SC03_099_jr_8017BEBC.c:3486).
//
// Declaration surface (checked against the whole TU in one pass, D2):
//   D_80126B62    TU:1790/2726/3054  `extern u16` -> cast to s16* at the use site (the
//                 load is `lh`), exactly as TU:3085 already does.
//   func_80049CAC TU:3105            `extern void func_80049CAC(s32, s32)` — reused verbatim.
//   D_801EE880    not declared anywhere in include/ or src/ (incl. engine_core.h macro
//                 bodies) — this is its first declaration.  Data: 4 shorts @ tail18.

#include "common.h"

extern s16 D_801EE880;
extern void func_80049CAC(s32 a0, s32 a1);

void func_8017C2B0(s32 a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    s32 unused[2];              /* dead 8-byte local — frame 0x28, not 0x20 */
    s32 s0;

    s0 = *(s32 *)(a0 + 0x20);

    if ((s32)*(s16 *)(a0 + 0xA) - (s32)(*(s16 *)&D_80126B62) >= 0x40) {
        *(s16 *)(a0 + 0x5C) = 0x40;
    } else {
        *(s16 *)(a0 + 0x5C) = 0x800;
    }

    if (*(s16 *)(s0 + 0x12) != D_801EE880) {
        *(s16 *)(s0 + 0x12) = D_801EE880;
        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        *(u16 *)(s0 + 0x2C) |= 0x11;
    }
}



extern void (*D_80190FBC[])(void);

void func_8017C338(void *a0) {
    D_80190FBC[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017C374(s32 param_1) {

    extern u8 D_80190FA4;
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

    node = func_800D222C(param_1, &D_80190FA4, 0xFD);
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
void func_8017C538(u8 *p) {
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



extern void (*D_80190FC4[])(void);

void func_8017C5CC(void *a0) {
    D_80190FC4[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_80190FB0;

void func_8017C608(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_80190FB0, 0x18);
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
void func_8017C6AC(int a0) {
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

void func_8017C710(s32 arg0)
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
                                            if (code != 4) g.opz = za + 0x20;
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
                                            if (code == 7) g.opz = za + 0x20;
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
                                                if (code == 3) g.opz = za + 0x20;
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

#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

/* fleet-modal spelling (engine_core.h, n=1411 occurrences) */
extern void func_8012ADE4(u8 *a0);
/* TU-verbatim spelling (already at ov_SC03_001_jr_8017AE2C.c:585) */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_8017D5F0(s32 a0, s32 a1) {
    s32 s0 = a0;
    s32 s1 = a1;
    s16 spA[4];            /* sp+0x10 */
    struct M8012AF0C spB;  /* sp+0x18 (src) */
    struct M8012AF0C spC;  /* sp+0x20 (dst) */

    spA[0] = *(u16 *)(s0 + 0x3A);
    spA[1] = *(u16 *)(s0 + 0x3E);
    spA[2] = *(u16 *)(s0 + 0x42);
    spB.a = *(u16 *)(s0 + 0x6);
    spB.b = *(u16 *)(s0 + 0xA);
    spB.c = *(u16 *)(s0 + 0xE);
    spC = spB;

    if (func_80135888(*(s32 *)(s1 + 0x20), *(s32 *)(s1 + 0x58), (s32)spA, (s32)&spC) != 0) {
        s32 v1;
        s16 a1v;
        s16 a0v;
        s16 a2v;

        func_8012ADE4((u8 *)s0);

        if (*(s32 *)(s1 + 0x58) == 0) {
            return 1;
        }

        v1 = *(s32 *)(*(s32 *)(s1 + 0x78) + 0x8);
        a1v = *(s16 *)(s1 + 0x6);
        a0v = *(s16 *)(s0 + 0x6);
        if (a0v >= a1v + *(s16 *)(v1 + 0x6)) {
            return 1;
        }
        if (a1v + *(s16 *)(v1 + 0x4) >= a0v) {
            return 1;
        }
        a2v = *(s16 *)(s0 + 0xE);
        a1v = *(s16 *)(s1 + 0xE);
        if (a2v >= a1v + *(s16 *)(v1 + 0xE)) {
            return 1;
        }
        if (a1v + *(s16 *)(v1 + 0xC) < a2v) {
            *(s16 *)(s0 + 0xE) = a2v + 0x40;
        }
        return 1;
    }

    return 0;
}


#include "common.h"

/* TU-adopted declarations (law 2 — copied verbatim from src/ov_SC03_001/ov_SC03_001_jr_8017AE2C.c) */
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);

/* Not yet declared anywhere in this TU — added per call-site evidence / shared engine_core fleet consensus */
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_8017D5F0(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 rand(void);

extern s16 D_80191010;
extern s16 D_801BE3F0;
extern s16 D_801BE498;
extern s16 D_8019102C;

void func_8017D734(s32 param_1) {
    if (*(s16 *)(param_1 + 0x100) > 0) {
        if (func_8012CBCC(param_1) & 0x6000) {
            *(s16 *)(param_1 + 0x16) = -4;
        }
        {
            s32 r = func_8012E544(0xAD);
            if (r != 0) {
                func_8017D5F0(param_1, r);
            }
        }
        if (*(s16 *)(param_1 + 0xA) < *(s16 *)(param_1 + 0x8A) - 0x30) {
            *(u16 *)(param_1 + 0xE) = *(u16 *)(param_1 + 0xE) + 0x40;
        }
    }

    if (--*(s32 *)(param_1 + 0x1C) == 0) {
        s32 phase = (u16)(*(u16 *)(param_1 + 0x100) + 1) & 3;
        *(u16 *)(param_1 + 0x100) = phase;
        if (phase == 0) {
            *(s32 *)(param_1 + 0x1C) = 0x14;
            func_8012A828(param_1, (s32)&D_801BE3F0);
        } else if (phase >= 0) {
          if (phase < 4) {
            u16 *s1 = (u16 *)&D_80191010;
            s32 t;

            *(s32 *)(param_1 + 0x1C) = 0x1E;
            func_8012A828(param_1, (s32)&D_801BE498);

            t = func_8012BE98(param_1, s1);
            if (t < 0x4000) {
                s32 r2 = rand();
                s32 v1 = *(s32 *)(param_1 + 0x20);
                *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + (r2 & 0x1FF);
            } else {
                s32 v0 = func_8012B744((void *)(param_1 + 4), s1);
                s32 v1 = *(s32 *)(param_1 + 0x20);
                *(u16 *)(v1 + 0x12) = (u16)v0;
            }
            func_8012B2CC(param_1);
            func_8012B1B4(param_1, (s32)&D_8019102C);
          }
        }
    }
}


#include "common.h"

/* decl_prior: tu spelling adopted verbatim */
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, s32 a1);

/* No TU decl found for these; fleet-modal spelling used except where the asm
 * itself proves a return value is consumed (func_8012CBCC — see notes). */
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_8017D5F0(s32 a0, s32 a1);

/* Small table of s16 fields; only addresses of most are ever taken here. */
extern s16 D_80191020;
extern s16 D_80191018;
extern s16 D_8019101C;
extern s16 D_80191010;
extern s16 D_801BE398;

void func_8017D8A8(s32 param_1) {
    s32 pv = param_1;
    s32 s0;
    s32 v0;
    s32 s2;

    func_8012B1B4(pv, (s32)&D_80191020);
    s0 = func_8012CBCC(pv);
    if (s0 & 0x6000) {
        *(s16 *)(pv + 0x16) = -4;
    }

    v0 = func_8012E544(0xAD);
    if (v0 != 0) {
        if (func_8017D5F0(pv, v0) != 0) {
            s0 |= 0x8000;
        }
    }

    if (s0 & 0x8000) {
        s16 cnt = (s16)(*(u16 *)(pv + 0x104) + 1) & 0x3F;
        *(u16 *)(pv + 0x104) = cnt;
        if (cnt < 0x1F) {
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) += 0x200;
        } else {
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) -= 0x200;
        }
    } else {
        *(u16 *)(pv + 0x104) = 0;
    }

    s2 = pv + 4;
    {
        s16 *p = &D_80191018;
        s32 t = (s32)func_8012B744((void *)s2, p);
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), t, 4);
        *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;

        {
            s32 dx = *(s16 *)(pv + 6) - *p;
            s32 dy = *(s16 *)(pv + 0xE) - D_8019101C;
            if (dx * dx + dy * dy < 0x400) {
                *(s16 *)(pv + 2) = 3;
                func_8012A828(pv, (s32)&D_801BE398);
                v0 = (s32)func_8012B744((void *)s2, &D_80191010);
                *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) = (s16)v0;
            }
        }
    }
}


#include "common.h"

extern void func_8012A828(s32, s32);
extern void func_8012B2CC(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 D_801BE2F0;
extern s32 D_801BE5E0;
extern s32 D_80191038;
extern void *D_80191044[];

void func_8017DA48(s32 a0) {
    /* +0xFC = requested sub-state, +0xFE = acked sub-state */
    if (*(s16 *)(a0 + 0xFC) != *(s16 *)(a0 + 0xFE)) {
        *(s16 *)(a0 + 0xFE) = *(s16 *)(a0 + 0xFC);
        switch (*(s16 *)(a0 + 0xFC)) {
        case 0:
            *(s32 *)(a0 + 0x1C) = 1;   /* timer */
            *(s16 *)(a0 + 0x2) = 1;    /* state */
            break;
        case 1:
            func_8012A828(a0, (s32)&D_801BE2F0);
            *(s16 *)(a0 + 0x2) = 2;
            break;
        case 2:
            func_8012A828(a0, (s32)&D_801BE5E0);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0xC00;
            func_8012B2CC(a0);
            func_8012B1B4(a0, (s32)&D_80191038);
            *(s16 *)(a0 + 0x2) = 4;
            *(s32 *)(a0 + 0x1C) = 0x78;
            break;
        case 3:
            func_8012A828(a0, (s32)&D_801BE2F0);
            *(s16 *)(a0 + 0x2) = 5;
            break;
        }
    }
    ((void (*)(s32))D_80191044[*(u16 *)(a0 + 0x2)])(a0);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017DB6C);

void func_8017DC48(void) {
}

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017DC50);

#include "common.h"

extern s32 func_8012E544(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s16 D_80191020;

typedef struct { s16 vx, vy, vz, pad; } TmpVec_8017DCE4;

void func_8017DCE4(s32 a0)
{
    register s32 pv __asm__("$16") = a0;
    s32 s1;
    s32 flags;
    TmpVec_8017DCE4 tmp;
    s32 v0;

    s1 = func_8012E544(0xAD);
    if (s1 == 0) {
        func_8012C218((void *)pv);
        return;
    }

    func_8012B1B4(pv, (s32)&D_80191020);
    flags = func_8012CBCC(pv);

    if (flags & 0x6000) {
        *(s16 *)(pv + 0x16) = -6;
    }

    if (flags & 0x8000) {
        *(s32 *)(pv + 4) += *(s32 *)(pv + 0x10);
        *(s32 *)(pv + 8) += *(s32 *)(pv + 0x14);
        *(s32 *)(pv + 0xC) += *(s32 *)(pv + 0x18);
    }

    tmp.vx = *(u16 *)(s1 + 6) + 0x20;
    tmp.vz = *(u16 *)(s1 + 0xE) + 0x20;
    v0 = func_8012B744((void *)(pv + 4), &tmp);

    {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), v0, 4);
        *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
    }
}



extern void (*D_8019106C[])(void);

void func_8017DDEC(void *a0) {
    D_8019106C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_8019105C;

void func_8017DE28(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_8019105C | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


DEFINE_func_8017DEA4()  /* dedup: shared engine-core @0x8017DEA4 (src/shared) */


extern void (*D_801910A4[])(void);

void func_8017DEAC(void *a0) {
    D_801910A4[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8017E204(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801EE888 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_8017DEE8(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_8017DEE8 D_801EE888[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_8017DEE8 *p = &D_801EE888[i];

            p->unk16 = i;
            func_8017E204(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}




extern u8 D_80078EB1;
extern u8 D_80078E78[];
extern u8 D_800AF630[];
extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8017E1B4(void *a0);
extern void func_8017E2C0(void *arg0);

void func_8017DF78(void *arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_8017D6EC_8017DEE8 D_801EE888[];
    u8 *m;
    u8 *e78;
    s32 k;

    m = D_800AF630;
    e78 = D_80078E78;

    if (D_80078EB1 >= 9) {
        s32 count;
        s32 i;
        u8 *base;

        base = (u8 *)D_801EE888;
        count = 0;
        for (i = 0; i < 4; i++) {
            if (*(s32 *)(base + i * 0x24 + 0x1C) == 0) {
                count++;
            }
        }
        if (count == 0) {
            func_8012AD44((s32 *)arg0, 0);
            return;
        }
    }

    for (k = 0; k < 4; k++) {
        u8 *p = (u8 *)D_801EE888 + k * 0x24;
        s32 c;

        if (*(s32 *)(p + 0x1C) != 0) {
            continue;
        }

        {
            s16 val = *(s16 *)(p + 0xC);
            if (val < 0x401) {
                *(s16 *)(p + 0xC) = val + 0xB;
            } else if (*(s32 *)(p + 0x18) != 0) {
                *(s32 *)(p + 0x18) -= 1;
            } else {
                *(s16 *)(p + 0xC) = val + 0xB;
            }
        }

        if (*(s16 *)(p + 0xC) >= 0x801) {
            *(s16 *)(p + 0xC) = 0;
        }

        c = (func_8004787C(*(s16 *)(p + 0xC)) / 64) & 0xFF;
        c = c | (c << 16 | c << 8);
        *(s32 *)(p + 0x4) = c;

        c = (func_8004787C(*(s16 *)(p + 0xC)) / 256) & 0xFF;
        c = c | (c << 16 | c << 8);
        *(s32 *)(p + 0x8) = c;

        if ((*(u16 *)(m + 0xA3AA) & 1) == 0) {
            s16 cnt = *(u16 *)(p + 0xE) + 1;
            *(u16 *)(p + 0xE) = cnt;
            if (cnt >= 0x40) {
                *(u16 *)(p + 0xE) = 0;
            }
        }

        {
            s32 val2 = *(s16 *)(p + 0xC);
            if (val2 == 0) {
                *(s32 *)(p + 0x1C) = 1;
            } else if (val2 >= 0x556) {
                if (*(s32 *)(p + 0x20) == 0) {
                    *(s32 *)(p + 0x20) = 1;
                    if (e78[0x39] < 9) {
                        func_8017E1B4(p);
                    }
                }
            }
        }

        func_8017E2C0(p);
    }
}




/* func_8017E1B4 - iterate through 4-entry array, call func_8017E204 if any unk1C is non-zero */

extern void func_8017E204(void *arg0);




void aF8017E1B4(void) __asm__("func_8017E1B4");
void aF8017E1B4(void)
{

    extern Ent_8017D6EC D_801EE888[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801EE888[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_8017E204(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_8017E204(void *arg0) {

    extern void (*D_80191074[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_80191074;
    *(s32 *)(base + 0x4) = 0;
    *(s32 *)(base + 0x8) = 0;
    *(s16 *)(base + 0xC) = 0;
    *(s16 *)(base + 0xE) = 0;
    *(s16 *)(base + 0x10) = 0;

    r1 = rand();
    r2 = rand();
    h = *(s16 *)(base + 0x16) * 80;
    t = (r1 & 7) * 5 - 0xA0;
    *(s16 *)(base + 0x12) = h + t + (r2 & 0xF);

    *(s16 *)(base + 0x14) = -((rand() & 0xF) * 2);
    *(s32 *)(base + 0x1C) = 0;
    *(s32 *)(base + 0x20) = 0;
    *(s32 *)(base + 0x18) = (*(u16 *)(base + 0x16) & 2) * 30;
}




/* func_8017E2C0 — build a 4-vertex SVECTOR quad from an 8-u16 source record,
 * translate it by the actor's (0x12,0x14) offset, and hand it to the
 * 0x80017714 draw helper — three records per call.
 *
 * Frame math: 0x10 arg-save + 0x38 local + 7 saved regs (s0..s5,ra) = 0x68.
 * The local is the same block shape as the D_801AA000 global in
 * ov_SC06_008_jr_8017C294 (SVECTOR v[4]; then six words), with the last
 * word DEAD (idiom 6: the frame delta is a dead field, not codegen).
 *
 * Two levers, both required:
 *  (1) THE PRIM BASE IS A SOURCE-LEVEL POINTER, not `&prim` at the use sites.
 *      Writing the loop body as `prim.v[k].vx = ...` addresses every store
 *      sp-relative, costs no callee-saved register and comes out -3 ins
 *      ($s5 never allocated, no `addiu $s1,$sp,0x10`). Introducing `q = &prim`
 *      BEFORE the loop and using `q->` only inside it reproduces the target
 *      exactly: the pre-loop initialisers stay sp-relative (same block as q's
 *      set, so cse folds them back) while the loop body keeps $s1.
 *  (2) A chained assignment stores the INNERMOST target first. The target's
 *      order is `sw 0x34` then `sw 0x30`, so it must be written
 *      `prim.f20 = prim.f24 = x;` — `f24 = f20 = x` emits 0x30 then 0x34.
 *
 * The two induction pointers ($s4 walking the record and $s0 = $s4 + 0xE)
 * fall out of a SINGLE `u16 *p` walked with `p += 8` — loop.c splits the
 * eight DEST_ADDR givs onto two bases on its own; do not hand-write a
 * second pointer.
 *
 * Byte-identical target asm in ov_SC04_019 and ov_SC05_017 (same TU name),
 * so this body remaps to those overlays unchanged.
 */



extern void func_80017714(void *);

void func_8017E2C0(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_8017E2C0 prim;
    Prim_8017DAC4_8017E2C0 *q;
    u16 *p;
    u16 dx, dy;
    s32 i;

    q = &prim;
    p = *(u16 **)(a0 + 0x0);
    dx = *(u16 *)(a0 + 0x12);
    dy = *(u16 *)(a0 + 0x14);
    i = 0;

    prim.v[0].vz = 3;
    prim.f20 = prim.f24 = *(s32 *)(a0 + 0x4);
    prim.f28 = *(s32 *)(a0 + 0x8);
    prim.f2C = 0;
    prim.f30 = 0x50000000;

    do {
        q->v[0].vx = p[0] + dx;
        q->v[0].vy = p[1] + dy;
        q->v[1].vx = p[2] + dx;
        q->v[1].vy = p[3] + dy;
        q->v[2].vx = p[4] + dx;
        q->v[2].vy = p[5] + dy;
        q->v[3].vx = p[6] + dx;
        q->v[3].vy = p[7] + dy;
        func_80017714(q);
        p += 8;
        i++;
    } while (i < 3);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017E3D8);


// @class: regalloc-order
// @stuck: none — MATCH

extern u32 D_801EE918;
extern u16 D_801910AC[];
extern u16 D_801EE91C[];
extern s32 D_801910CC;

extern void func_800183E0(s32 a0);

void func_8017E408(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_801910AC;
    base = D_801EE918 >> 8;
    p = D_801EE91C;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_801910CC);
    D_801EE918 = D_801EE918 + 0x100;
}



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017E824(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017E494(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017E824, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017E4E4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017E508);


extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);

s32 func_8017E578(s32 a0) {

    extern s16 D_800B9A0A;
    s16 s0;

    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_800D1E28();
        s0 = D_800B9A0A;
        if (s0 != 0x1000 || (s16)func_800D1D94() != s0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017E628(void) {
        func_800D1EBC();
    }



extern void func_800D1E28(void);

s32 func_8017E648(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;

    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }

    return 0;
}


extern void func_800D1E28(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern s32 func_800291B4(s32 arg);
extern void func_800D0C48(s32 a0);

s32 func_8017E69C(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0) {
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}



extern void (*D_801910EC[])(void);

void func_8017E720(void *a0) {
    D_801910EC[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_801910F4[])(void);

void func_8017E75C(void *a0) {
    D_801910F4[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80191100[])(void);

void func_8017E798(void *a0) {
    D_80191100[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8019110C[])(void);

void func_8017E7D4(void *a0) {
    D_8019110C[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_80127050;
    void func_8017E810(void) {
        D_80127050 = 1;
    }



extern void (*D_801913C0[])(void);

void func_8017E824(void *a0) {
    D_801913C0[*(u8 *)((s32)a0 + 0x214)]();
}


void func_8017E860(s32 *a0) {
        *(u8 *)((s32)a0 + 0x214) += 1;
    }


extern void func_80175414(s32 _arg0);
extern void func_8016F0E4(void);
extern void func_80165770(void);
void func_8017E874(void *a0) {
    ((void (*)(void *))func_80175414)(a0);
    ((s32 (*)(struct S *))func_8016F0E4)((struct S *)a0);
    ((void (*)(void *))func_80165770)(a0);
}



extern void (*D_801913C8[])(void);

void func_8017E8AC(void *a0) {
    D_801913C8[*(u8 *)((s32)a0 + 0x214)]();
}


void func_8017E8E8(u8 *a0) {
        *(s8 *)(a0 + 0x214) += 1;
    }


extern void func_8016F0E4(void);
    void func_8017E8FC(void) {
        ((s32 (*)(void))func_8016F0E4)();
    }



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017E9E0(void *a0);


void func_8017E91C(void) {

    extern u8  D_80126948[];
    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8  D_801269E8;
    u8 tmp = D_801269E8;

    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x238;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E9E0, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_8017E9E0(D_80126948);
    func_8012A094((s32)D_80126948);
    func_8017E9E0(D_80126948);
}



extern void (*D_801913D0[])(void);

void func_8017E9E0(void *a0) {
    D_801913D0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017EA1C);

void func_8017EA50(u8 *a0) {
        *(s8 *)(a0 + 0xa0) = 0;
    }




extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_80012A60(s32 a0, s32 a1);

void func_8017EA58(void *a0, u8 *a1)
{

    extern s32 D_80126B58;
    extern s16 D_8018D828[];
    /* Dead aggregate local (idiom 6): args(0x10) + saves(7*4) alone give a 0x30
     * frame; the target is 0x38, i.e. vars != 0.  gcc-2.7.2 rounds the var area
     * to 8, so ONE dead word reproduces it (s32 pad[2] overshoots to 0x40). */
    s32 frame_pad[1];
    u8 dir;
    s32 lim;
    s32 flags;
    s32 held;
    s32 cur;

    dir = *a1;
    held = ((s32(*)(s32 *))func_801487F4)(&D_80126B58);
    cur = ((s32(*)(s32 *))func_80148800)(&D_80126B58);
    *(s16 *)((s32)a0 + 0x9C) = 0x5B;

    lim = 0;
    if (cur & 3) {
        lim = 0x555;
        flags = cur;
        *(s16 *)((s32)a0 + 0xA2) = 8;
    } else if (*(s16 *)((s32)a0 + 0xA2) == 0) {
        if (held & 3) {
            lim = 0x555;
            flags = held;
            *(s16 *)((s32)a0 + 0x9C) = 0x2D;
        }
    } else {
        *(s16 *)((s32)a0 + 0xA2) = *(s16 *)((s32)a0 + 0xA2) - 1;
    }

    if (lim != 0) {
        if (flags & 1) {
            dir = (dir - 1) & 7;
        } else if (flags & 2) {
            dir = (dir + 1) & 7;
        }
        if ((s16)func_80012A60(*(s16 *)((s32)a0 + 0x1A), D_8018D828[dir]) < lim) {
            *a1 = dir;
        }
    }

    *(s16 *)((s32)a0 + 0x22) = D_8018D828[*a1];
}




   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017EB98(s32 param_1)
{
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;

    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    register s32 lim __asm__("$16");

    lim = *(u16 *)(param_1 + 0x9C);

    {
        s32 delta = func_80012B04(*(s16 *)(param_1 + 0x1A), *(s16 *)(param_1 + 0x22), 0x14);
        if ((s16)delta > (s16)lim) {
            delta = lim;
        } else if ((s16)delta < -(s16)lim) {
            delta = -lim;
        }
        *(s16 *)(param_1 + 0x1A) = (*(u16 *)(param_1 + 0x1A) + delta) & 0xFFF;
        *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    }

    *(s16 *)(param_1 + 0x1C) = func_80012ABC(*(s16 *)(param_1 + 0x1C), *(s16 *)(param_1 + 0x24), 4);
    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C(*(s16 *)(param_1 + 0x8),  *(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C(*(s16 *)(param_1 + 0x2A), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C(*(s16 *)(param_1 + 0x2C), *(s16 *)(param_1 + 0x32), 0x10);

    {
        s16 *p940 = &D_80126940;
        *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + *p940;
        *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + D_80126942;
        *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + D_80126944;
        func_80049CAC(param_1 + 0x18, (s32)&m1);

        m1.t[0] = *(s16 *)(param_1 + 0x28) + *p940;
        m1.t[1] = *(s16 *)(param_1 + 0x2A) + D_80126942;
        m1.t[2] = *(s16 *)(param_1 + 0x2C) + D_80126944;
    }
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


extern void func_80187778(s32 *a0, s32 a1);
    extern short D_801913D4;
    void func_8017ED8C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 2;
        func_80187778(a0, &D_801913D4);
    }


#include "common.h"

/* decl block copied verbatim from the destination TU, immediately preceding
 * this function's own address range (src/ov_SC03_001/ov_SC03_001_jr_8017AE2C.c
 * lines 4910-4914, right above the sibling func_8017F058 which shares
 * func_80029504 / func_8018766C / func_80187778 / func_801877C0). */
extern s32 func_80029504(void);
extern s32 func_801877C0(s32);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80187778(s32*, s32);

/* func_8012C1B8 / func_8012CAE4 / func_8001C214 declared as in the TU's
 * func_8017DE28 (lines 4198-4200). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);

/* already declared at TU line 2512 */
extern s32 func_801788B8(s32 arg0, s32 arg1);

/* this function's own callback target, INCLUDE_ASM'd at TU line ~4906 */
extern void func_8017EF30(void);

void func_8017EDB8(void *a0) {

    extern short D_801913D4;
    void *s0 = a0;
    s32 v0;
    s32 v1;
    void *v1p;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
    }
    func_8001C214(*(s32 *)((u8 *)s0 + 0x20), 0);

    v1 = func_80029504();
    if (v1 < 0xC8) {
        v0 = ((s32 (*)(void))func_801877C0)();
        if (v0 == 3) {
            v0 = 2;
        } else {
            v0 = func_8018766C(0xA, 0x10);
            if (v0 != 0) {
                v0 = 1;
            } else {
                v0 = 2;
            }
        }
    } else if (v1 < 0x258) {
        func_8012CAE4(s0);
        return;
    } else if (v1 < 0x384) {
        if (v1 < 0x276) {
            func_8012CAE4(s0);
            return;
        }
        v0 = 1;
    } else {
        v0 = 1;
    }

    *(s16 *)((u8 *)s0 + 0x2) = (s16)v0;
    __asm__ __volatile__("");
    func_80187778((s32 *)s0, (s32)&D_801913D4);

    v1p = *(void **)((u8 *)s0 + 0x68);
    *(s16 *)((u8 *)v1p + 0xC) = 0x7FFF;
    *(s32 *)((u8 *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)&func_8017EF30);
}


extern void (*D_801914A8[])(void);

void func_8017EEA8(void *a0) {
    D_801914A8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32*, s32);
    extern short D_80191438;
    void func_8017EEE4(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_80191438);
    }


extern s32 func_800D0EC4(void);
    s32 func_8017EF10(void) {
        return (func_800D0EC4() == 0);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017EF30);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017EFD4);


extern s32 func_80029504(void);
extern s32 func_801877C0(s32);
extern s32 func_80187904(void);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80187778(s32*, s32);

void func_8017F058(void *a0) {

    extern short D_801913D4;
    void *s0 = a0;
    s32 v1 = func_80029504();
    s32 v0;

    if (v1 < 0xC8) {
        v0 = ((s32 (*)(void))func_801877C0)();
        v1 = 3;
        if (v0 == v1) {
            return;
        }
        v0 = func_8018766C(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    } else if (v1 < 0x258) {
        v0 = 1;
    } else if (v1 < 0x384) {
        v0 = func_8018766C(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    } else {
        v0 = func_80187904();
        v1 = 1;
        if (v0 == v1) {
            return;
        }
        v0 = func_8018766C(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    }

    *(s16 *)((char *)s0 + 0x2) = 0x1;
    ((void (*)(s32, s32))func_80187778)((s32)s0, (s32)&D_801913D4);
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80187778(s32*, s32);

void func_8017F0EC(void * arg0) {

    extern short D_801913D4;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_801913D4);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017F13C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017F1F0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017F258);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017F2AC);


/* func_8017F368 (ov_SC04_018, ov_SC04_018_jr_8017AE2C) — MATCH (250 ins)
 *
 * Shadow/marker quad renderer: builds an outer quad (D_801914BC offset table)
 * through RotNclip4, rejects it on OTZ, builds the inner quad (D_8019153C)
 * through RotTransPers4, then emits 4 semi-transparent POLY_G4 (0x24 each) +
 * one semi-transparent POLY_F4 (0x18) out of one 0xA8 packet allocation.
 *
 * Levers that closed the residual (all byte-verified against the .s):
 *  - frame 0xE0 with locals starting at 0x30: STARTING_FRAME_OFFSET ==
 *    outgoing-args size (RotNclip4 takes 11 args -> 0x2C -> 0x30).  `pad0[16]`
 *    is the DEAD 0x20-byte first local (§136 idiom 6) that puts va at sp+0x50.
 *  - `sxy[8]` is ONE array: RotNclip4 fills [0..3], RotTransPers4 fills [4..7],
 *    and the loop indexes the whole thing (idx values run 0..7).
 *  - `register u16 *dst __asm__("$4")`: a HARD-reg dst is not a biv, so loop.c
 *    cannot strength-reduce its +2/+4 accesses into a second IV.  That is what
 *    gives ONE register with offsets 0/2/4 (unpinned -> 254 ins, extra IV).
 *  - `p2 = p1 + 2` (two walked source pointers): `p1[0]` is a bare deref
 *    (excluded from givs, loop-map L1 rule 4) so p1 stays the biv used at
 *    offset 0, and p2 is the second IV carrying the -2/0 offset cluster.
 *  - `while` loops with `i++` written BEFORE the pointer bumps: the increment
 *    LUID order decides which bump fills the first load-delay slot.
 *  - `s16 idx[4]` as a real ARRAY (ARRAY_REF => MEM_IN_STRUCT_P): that makes
 *    the varying-address packet store conflict with the stack slots, so CSE
 *    cannot forward idx[1..3] and gcc re-loads them with `lh` (an
 *    INDIRECT_REF `*(s16*)(buf+0x82)` forwards them and loses the reloads).
 *  - `D_800A651C[][5]` / `D_801E01Dx[][4]` two-dimensional externs: the 1-D
 *    `sym + byte_offset` spelling makes gcc materialise `&D_800A651C` into a
 *    hoisted callee-saved register ($s5, +4 ins); the 2-D array-ref keeps the
 *    symbol folded in the MEM address (gas `lw $2,sym($1)` macro) and makes the
 *    table index a REDUCED GIV, whose preheader init lands AFTER the hoisted
 *    `addiu $s3,$sp,0x30` movable (target order s3 -> s2 -> s0).
 *  - `type2 = type + zr` ($zero pin): the target keeps TWO pseudos for
 *    (attr & 0xFF) — $a0 for the pre-call use and $s1 for the post-call one —
 *    so a plain second variable would be propagated away by CSE.
 *  - `pk[7] = 0x3A` written AFTER the 0x1C colour store: it only conflicts with
 *    the 0x04 store, so the scheduler sinks it into the `lh 0xB6($sp)` delay
 *    slot exactly as in the target (§135 idiom 4, source order sets the sink).
 */

extern void func_8012E32C(void);
extern void func_8017F750(void *, s32);
extern s32 RotNclip4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);

void func_8017F368(u16 *a0, s32 a1)
{

    extern s32 D_800A651C[][5];
    extern u16 D_801914BC[];
    extern u16 D_8019153C[];
    extern u16 D_801915DC[][4];
    extern u16 D_801915DE[][4];
    extern u16 D_801915E0[][4];
    extern u16 D_801915E2[][4];
    register s32 zr __asm__("$0");

    u16 pad0[16];   /* dead: locals begin at sp+0x30, va must land at sp+0x50 */
    u16 va[16];     /* sp+0x50 — outer quad, 4 x SVECTOR */
    u16 vb[16];     /* sp+0x70 — inner quad, 4 x SVECTOR */
    s32 sxy[8];     /* sp+0x90 — [0..3] RotNclip4, [4..7] RotTransPers4 */
    s16 idx[4];     /* sp+0xB0 */
    s32 p;          /* sp+0xB8 */
    s32 otz;        /* sp+0xBC */
    s32 flag;       /* sp+0xC0 */

    u16 attr;
    s32 type;
    s32 type2;
    u16 *p1;
    u16 *p2;
    register u16 *dst __asm__("$4");
    s32 i;
    u8 *pk;
    s32 j;

    func_8012E32C();

    attr = a0[3];
    type = attr & 0xFF;
    type2 = type + zr;
    if ((attr & 0xF00) == 0x200) {
        func_8017F750(a0, a1);
        return;
    }

    p1 = (u16 *)((u8 *)D_801914BC + type * 0x20);
    i = 0;
    p2 = p1 + 2;
    dst = va;
    while (i < 4) {
        dst[0] = a0[0] + p1[0];
        dst[1] = a0[1] + p2[-1];
        dst[2] = a0[2] + p2[0];
        i++;
        p1 += 4;
        p2 += 4;
        dst += 4;
    }

    if (RotNclip4((s32)&va[0], (s32)&va[4], (s32)&va[8], (s32)&va[12],
                  &sxy[0], &sxy[1], &sxy[2], &sxy[3], &p, &otz, &flag) <= 0) {
        return;
    }

    otz -= 0x10;
    if (otz < 0) {
        return;
    }
    if (otz >= 0x1000) {
        return;
    }

    p1 = (u16 *)((u8 *)D_8019153C + type2 * 0x20);
    i = 0;
    p2 = p1 + 2;
    dst = vb;
    while (i < 4) {
        dst[0] = a0[0] + p1[0];
        dst[1] = a0[1] + p2[-1];
        dst[2] = a0[2] + p2[0];
        i++;
        p1 += 4;
        p2 += 4;
        dst += 4;
    }

    RotTransPers4((s32)&vb[0], (s32)&vb[4], (s32)&vb[8], (s32)&vb[12],
                  &sxy[4], &sxy[5], &sxy[6], &sxy[7], &p, &flag);

    pk = func_80010A08(0xA8);

    for (j = 0; j < 4; j++) {
        idx[0] = D_801915DC[j][0];
        idx[1] = D_801915DE[j][0];
        idx[2] = D_801915E0[j][0];
        idx[3] = D_801915E2[j][0];
        *(s32 *)(pk + 0x4) = a1 & -(idx[0] < 4);
        *(s32 *)(pk + 0xC) = a1 & -(idx[1] < 4);
        *(s32 *)(pk + 0x14) = a1 & -(idx[2] < 4);
        *(s32 *)(pk + 0x1C) = a1 & -(idx[3] < 4);
        pk[7] = 0x3A;
        *(u32 *)(pk + 0x0) = 0x08000000;
        *(s32 *)(pk + 0x8) = sxy[idx[0]];
        *(s32 *)(pk + 0x10) = sxy[idx[1]];
        *(s32 *)(pk + 0x18) = sxy[idx[2]];
        *(s32 *)(pk + 0x20) = sxy[idx[3]];
        AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
        pk += 0x24;
    }

    *(s32 *)(pk + 0x4) = a1;
    pk[7] = 0x2A;
    *(u32 *)(pk + 0x0) = 0x05000000;
    *(s32 *)(pk + 0x8) = sxy[0];
    *(s32 *)(pk + 0xC) = sxy[1];
    *(s32 *)(pk + 0x10) = sxy[2];
    *(s32 *)(pk + 0x14) = sxy[3];
    AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
    func_8012E28C(otz, 1);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017F750);


extern void (*D_801918FC[])(void);

void func_8017F7C8(void *a0) {
    D_801918FC[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8018766C(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_8017F804(s32 param_1) {

    extern u8 D_8019190C[][4];
    s32 i;
    s32 v1;
    s32 uVar1;

    if (func_8018766C(7, 0x13) == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_8019190C[*(s16 *)(param_1 + 0x100)][i] == *(s32 *)(param_1 + 0x1c)) {
            func_8012C658(0x140,
                          *(u8 *)(param_1 + 0xfc) | ((*(s16 *)(param_1 + 0xfe) << 8) & 0xff00),
                          param_1);
            break;
        }
    }
    if (func_8012BEE8(param_1) == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x50;
    uVar1 = rand();
    v1 = *(u16 *)(param_1 + 0xfe) + (uVar1 & 0xf) - 7;
    v1 &= 0xff;
    *(u16 *)(param_1 + 0xfe) = v1;
    uVar1 = rand();
    v1 = *(u16 *)(param_1 + 0xfc) + (uVar1 & 0xf) - 7;
    v1 &= 0xff;
    *(u16 *)(param_1 + 0xfc) = v1;
    uVar1 = rand();
    *(s16 *)(param_1 + 0x100) = uVar1 % 7;
}



extern void (*D_80191928[])(void);

void func_8017F920(void *a0) {
    D_80191928[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80191930[])(void);

void func_8017F95C(void *a0) {
    D_80191930[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80191940[])(void);

void func_8017F998(void *a0) {
    D_80191940[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80191950[])(void);

void func_8017F9D4(void *a0) {
    D_80191950[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017FA10(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_8017FA18(s32 param_1) {
    s32 uVar1;
    s32 iVar2;
    register s32 iVar3 __asm__("$3");
    register s32 iVar4 __asm__("$16");
    u32 uVar3;

    uVar1 = *(u16 *)(param_1 + 0x34);
    if (uVar1 == 1) {
        goto case1;
    }
    if (uVar1 < 2) {
        if (uVar1 == 0) {
            goto case0;
        }
        return;
    }
    if (uVar1 == 2) {
        goto case2;
    }
    if (uVar1 != 3) {
        return;
    }
    goto case3;

case0:
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    iVar4 = uVar3 & 0x3fff;
    iVar4 = iVar4 + 0x7800;
    uVar3 = rand();
    if ((uVar3 & 1) == 0) {
        iVar4 = -iVar4;
    }
    *(s32 *)(param_1 + 0xe0) = iVar4;
    *(s32 *)(param_1 + 0xe4) = 0;
    return;

case1:
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    uVar3 = uVar3 & 0x3f;
    goto tail;

case2:
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + *(s32 *)(param_1 + 0xe4);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    *(s32 *)(param_1 + 0xe0) = -*(s32 *)(param_1 + 0xe0);
    return;

case3:
    __asm__ __volatile__("" ::: "memory");
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = 0;
    uVar3 = rand();
    uVar3 = uVar3 & 0xff;

tail:
    *(u32 *)(param_1 + 0x1c) = uVar3 + 0x40;
}



extern void (*D_80191960[])(void);

void func_8017FBC4(void *a0) {
    D_80191960[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FC00(void)
{

    extern u16 D_800B99DA;
    extern s32 D_80126B58;
    extern u8 D_800AF648;
    extern s32 D_80191968;
    extern s32 func_80013450(s32);
    s32 *p = &D_80126B58;
    s32 sxy, pv, flag;
    s16 x;
    s32 pan;
    s32 dist;
    s32 vol;

    if (!(D_800B99DA & 1)) {
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648);
        if (RotTransPers((s32)&D_80191968, (s32)&sxy, &pv, &flag) <= 0 || flag < 0) {
            func_8002D4C8(4, 0x7E6);
        } else {
            x = *(u16 *)&sxy + 0xA0;
            *(s16 *)&sxy = x;
            if (x < 0) {
                x = 0;
                *(s16 *)&sxy = x;
            } else if (x >= 0x141) {
                x = 0x140;
                *(s16 *)&sxy = x;
            }
            x = *(s16 *)&sxy;
            pan = (x * 15) / 320;
            dist = ((s32 (*)(s32, s32))func_80013450)((s32)(p + 1), (s32)&D_80191968);
            if (dist >= 0x240) {
                dist = 0x23F;
            }
            {
                s32 panpart;
                vol = ((0x23F - dist) * 127) / 576;
                panpart = ((pan << 8) & 0xF00) | 0x3000;
                func_8002D4C8(0x7E6, panpart | (vol & 0x7F));
            }
        }
    }
}


extern s32 D_801915FC;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FD5C(void) {
    D_801EEAE8 = &D_801915FC;
    func_8017F1F0(0x474, 0x4B0);
}


extern s32 D_80191634;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FD90(void) {
    D_801EEAE8 = &D_80191634;
    func_8017F1F0(0x474, 0x4EC);
}


extern s32 D_8019166C;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FDC4(void) {
    D_801EEAE8 = &D_8019166C;
    func_8017F1F0(0x474, 0x4B0);
}


extern s32 D_80191694;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FDF8(void) {
    D_801EEAE8 = &D_80191694;
    func_8017F1F0(0x474, 0x4B0);
}



extern s32 D_801916CC;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FE2C(void) {
    D_801EEAE8 = &D_801916CC;
    func_8017F1F0(0x474, 0x528);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8017FE60);


extern s32 D_80191744;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FED4(void) {
    D_801EEAE8 = &D_80191744;
    func_8017F1F0(0x474, 0x1A4);
}




extern s32 func_80029504(void);
extern void func_8017F1F0(s32 arg0, s32 arg1);

s32 func_8017FF08(void) {

    extern s32 D_8019177C;
    s32 v;
    D_801EEAE8 = (s32)&D_8019177C;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_8017F1F0(0x96, 0xF0);
}



extern s32 D_8019179C;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FF54(void) {
    D_801EEAE8 = &D_8019179C;
    func_8017F1F0(0x12c, 0x1A4);
}



extern s32 D_801917EC;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FF88(void) {
    D_801EEAE8 = &D_801917EC;
    func_8017F1F0(0x474, 0x4B0);
}



extern s32 D_8019184C;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8017FFBC(void) {
    D_801EEAE8 = &D_8019184C;
    func_8017F1F0(0x474, 0x4B0);
}




extern s32 func_80029504(void);
extern void func_8017F1F0(s32 arg0, s32 arg1);

s32 func_8017FFF0(void) {

    extern s32 D_8019187C;
    s32 v;
    D_801EEAE8 = (s32)&D_8019187C;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_8017F1F0(0x474, 0x78);
}



extern s32 D_80191894;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);

void func_8018003C(void) {
    D_801EEAE8 = &D_80191894;
    func_8017F1F0(0x564, 0x1A4);
}


s32 func_80180070(void) {
        return -1;
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180078);

extern void func_8001C214(s32, s32);
extern void func_8012C1B8(void);
extern void func_8012C588(s32, s32);
extern void func_8012CAE4(void *a0);
extern void func_8017F13C(void);

    void func_80180134(void *a0) {
        s32 v0;
        u16 val;
        v0 = ((s32 (*)(void *))func_8012C1B8)(a0);
        *(s32 *)((char *)a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(a0);
            return;
        }
        func_8001C214(v0, 0);
        func_8012C588(0x13F, 0);
        func_8012C588(0x66, 0);
        func_8012C588(0x65, 0);
        func_8012C588(0x14C, 0);
        func_8012C588(0x335, 0);
        func_8012C588(0x3D9, 0);
        val = *(u16 *)((char *)a0 + 0x72);
        *(u16 *)((char *)a0 + 0x2) = 1;
        val |= 0x1000;
        *(u16 *)((char *)a0 + 0x72) = val;
        func_8017F13C();
    }


extern u8 D_80191904[];
extern void func_8012E8E0(s32 a0, s32 a1);

    void func_801801E0(s32 a0) {
        *(s16 *)(a0 + 0x2) = 1;
        func_8012E8E0(a0, (s32)&D_80191904);
        *(s16 *)(a0 + 0xFE) = 0;
        *(s16 *)(a0 + 0xFC) = 0x80;
    }


extern void func_8012B200(u8 *a0);

/*
 * func_80180224 -- ov_SC04_018 / ov_SC04_018_jr_80188E1C, 71 ins, family reach x6.
 *
 * STEP 0 sibling: this is a direct extension of the shared-engine-core macro
 * DEFINE_func_80144558() (src/shared/engine_core.h) -- identical prologue
 * through the func_80128EA8 call and the three field copies (+8/+0xA/+0xC
 * from param_1+6/+0xA/+0xE), but instead of calling func_8012B200(param_1) at
 * the end, this variant sets a handful of extra fields directly and calls
 * func_8012B0B4 (angle -> velocity split), matching the idiom seen at
 * src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:func_8017F9C4/func_8017FB58 and
 * the DEFINE_func_8012B0B4() macro itself (single u32 result word written
 * through the output pointer).
 */
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

void func_80180224(u8 *arg0)
{

    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    register u8 *param_1 __asm__("$16");   /* $s0 */
    s32 raw;
    u32 buf[6];

    param_1 = arg0;
    {
        register s32 s0 __asm__("$17");   /* $s1 -- scoped: dead after func_80128EA8 */
        s0 = ((s32 (*)(void))func_8012C194)();
        if (s0 == 0) {
            func_8012CAE4(param_1);
            return;
        }
        *(s32 *)(param_1 + 0xCC) = s0;
        func_8001CC3C(s0, 0, 0, 0);
        *(s32 *)(s0 + 0x20) = (s32)D_800D387C;
        *(u8 *)(s0 + 0x27) = 0x9C;
        *(u16 *)(s0 + 0x1A) = 0x3000;
        *(u16 *)(s0 + 0x18) = 0x3000;
        *(u32 *)(s0 + 4) = *(u32 *)(s0 + 4) | 0x50000000;
        func_80128EA8(s0, (s32)(param_1 + 0xD0), (s32)D_800D3888);
    }
    {
        s32 obj = *(s32 *)(param_1 + 0xCC);
        *(u16 *)(obj + 8) = *(u16 *)(param_1 + 6);
        *(u16 *)(obj + 0xA) = *(u16 *)(param_1 + 0xA);
        *(u16 *)(obj + 0xC) = *(u16 *)(param_1 + 0xE);
    }
    raw = *(s16 *)(param_1 + 0x70);
    *(s32 *)(param_1 + 0x1C) = 0x5A;
    *(u16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x10) = 0;
    *(s32 *)(param_1 + 0x14) = 0xFFF80000;
    *(s32 *)(param_1 + 0x18) = 0;
    func_8012B0B4((unsigned int *)buf, (raw & 0xFF00) >> 4, (raw & 0xFF) << 6);
    {
        register s32 full __asm__("$2");
        register s32 low  __asm__("$3");
        full = *(s32 *)buf;
        low = *(s16 *)buf;
        *(s32 *)(param_1 + 0x48) = 0;
        *(s32 *)(param_1 + 0x44) = low;
        *(s32 *)(param_1 + 0x4C) = full >> 16;
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180340);


extern void func_8012B414(int a0);
    void func_801803DC(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern s32 D_801BECE0[];
    extern s32 D_80191938[];
    void func_80180410(s32 a0) {
        s32 v0;
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        func_8001C214(v0, (s32)D_801BECE0);
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
        func_8012E8E0(a0, (s32)D_80191938);
        *(s16 *)(a0 + 0x2) = 1;
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180488);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801804D0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180574);

void func_801805EC(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }



extern void (*D_80191978[])(void);

void func_801805F8(void *a0) {
    D_80191978[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180634);

extern s32 func_80180634(void);
extern void func_801805EC(void *a0);

    void func_8018069C(void *a0) {
        s32 s0;
        s0 = 1;
        *(s32 *)(*(s32 *)((char *)a0 + 0xCC) + 0xB0) = s0;
        if (func_80180634() != s0) {
            return;
        }
        func_801805EC(a0);
    }




    void func_801806E8(s32 a0) {
        s32 *v1;
        v1 = *(s32 **)((s32)a0 + 0xCC);
        *(s32 *)((s32)v1 + 0xB0) = 2;
        if (func_80180634() == 0) {
            *(s16 *)((s32)a0 + 0x2) = 1;
        }
    }


extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80180728(void *a0) {
    s32 v0;

    v0 = func_8012E57C(0x61, 0xD);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    v0 = func_80180634();

    if (v0 != 0) {
        v0 = 2;
    } else {
        v0 = 1;
    }

    *(s16 *)((char *)a0 + 0x2) = v0;
}


void func_80180770(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }


extern void (*D_8019198C[])(void);

void func_8018077C(void *a0) {
    D_8019198C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801807B8);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180820);

extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

    void func_80180884(void *a0) {
        s32 v0;
        v0 = func_8012E57C(0x61, 0x8);
        *(s32 *)((char *)a0 + 0xCC) = v0;
        if (D_80078EBA == 3) {
            v0 = 0;
        } else {
            v0 = func_8018766C(0x7, 0x13);
            v0 = (0U < (u32)v0) ? 1 : 0;
        }
        if (v0 != 0) {
            v0 = 1;
        } else {
            v0 = 2;
        }
        *(s16 *)((char *)a0 + 0x2) = v0;
    }


void func_801808F0(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }



extern void (*D_801919A0[])(void);

void func_801808FC(void *a0) {
    D_801919A0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180938);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018098C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801809D0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180A10);



extern void func_8012A828(s32, s32);
    extern short D_801C3B38;
    void func_80180A58(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C3B38);
    }



extern void (*D_80191B0C[])(void);

void func_80180A88(void *a0) {
    D_80191B0C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180AC4);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180B1C);



/* func_80180B5C — state-entry init (family exemplar, reach x11).
 * Sets the actor's state id (halfword @ +0x2) then runs the fixed
 * five-call entry chain. Sibling style copied from func_80180164
 * in the same TU (cookbook §71). */

extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);


void aF80180B5C(void *arg0) __asm__("func_80180B5C");
void aF80180B5C(void *arg0)
{

    extern short D_801919AC;
    extern short D_801C3B38;
    extern short D_801B92EC;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_801919AC);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C3B38);
    func_80187750((s32)arg0);
    func_80187994((s32)arg0, (s32)&D_801B92EC, 0, 0x60);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180BCC);


extern void func_8012A828(s32 a0, s32 a1);
    extern short D_801C3B38;
    void func_80180C3C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        func_8012A828((int)arg0, (int)&D_801C3B38);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180C68);

    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80187750(s32 a0);
    extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
    extern short D_801C3B38;
    extern short D_801B92EC;
    void func_80180CD4(s32 a0) {
        *(u16 *)(a0 + 2) = 6;
        func_8012E88C(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&(*(s32 *)&D_801C3B38));
        func_80187750(a0);
        func_80187994(a0, (s32)&(*(s32 *)&D_801B92EC), 1, 0x60);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180D34);


extern s32 func_801877C0(s32 a0);

void func_80180D5C(s32 a0) {

    extern s32 D_801919D0[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_801919D0[idx];
}



extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_80180D9C(void) {
        if ((func_80029178(0x110) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x110, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_80180AC4(s32 a0);
extern s32 func_80180B5C(void *a0);
void func_80180DD8(int param_1)
{
    if (((int (*)(void))func_80180AC4)() != 0) {
        ((void (*)(int))func_80180B5C)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180E10);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180E68);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180ECC);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180FA0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80180FF8);


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80181078(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 3) {
        return 0;
    }

    if (func_8012BD14(ptr) >= 0x4001) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


void func_801810EC(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }



extern void (*D_80191B30[])(void);

void func_801810F8(void *a0) {
    D_80191B30[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8018766C(s32 arg0, s32 arg1);
extern u8 D_80078EBA;
extern void func_801810EC(void *a0);

    void func_80181134(void *a0) {
        s32 v0;
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
        if (D_80078EBA == 0) {
            v0 = 0;
        } else {
            v0 = func_8018766C(0xB, 0x10) != 0;
        }
        if (!v0) {
            func_801810EC(a0);
        }
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018119C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181200);


extern void func_80187778(s32*, s32);
    extern short D_80191B3C;
    void func_8018126C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80191B3C);
    }


extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80191B3C;
    void func_80181298(short *param_1) {
        *(short *)((char *)param_1 + 0x2) = 0x3;
        func_80187778(param_1, &D_80191B3C);
    }



extern void (*D_80191C08[])(void);

void func_801812C4(void *a0) {
    D_80191C08[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181300);

extern s32 func_8014CB1C(void);
    int func_80181374(void) {
        return func_8014CB1C() != 0;
    }



extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181394(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_80191BC0;
    void func_801813C0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(short *)((char *)a0 + 0x34) = 0;
        func_80178CBC((s32 *)a0, (s32)&D_80191BC0);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801813F0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181458);

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern short D_80191B3C;
extern void func_80187778(s32 *a0, s32 a1);

    void func_801814C4(s32 *arg0) {
        register s32 *s0 asm("$16") = arg0;
        s32 v0, v1;
        *(s32 *)((u8 *)(*(s32 **)((u8 *)s0 + 0xCC)) + 0xB0) = 2;
        v0 = func_8018766C(6, 0x12);
        if (v0 != 0) {
            v1 = 1;
        } else {
            v0 = func_8018766C(0x12, 0x15);
            v1 = (v0 != 0) ? 2 : 0;
        }
        if (v1 != 2) {
            *(s16 *)((u8 *)s0 + 2) = 1;
            func_80187778(s0, (s32)&D_80191B3C);
        }
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018153C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801815A0);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018166C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801816D8);


extern void (*D_80191C20[])(void);

void func_801817C4(void *a0) {
    D_80191C20[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181800);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181864);

extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80191C28;
    void func_801818E0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        func_80187778((s32 *)a0, (s32)&D_80191C28);
    }



extern void (*D_80191C90[])(void);

void func_8018190C(void *a0) {
    D_80191C90[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181948);

void func_80181988(void *a0) {
        *(short *)((char *)a0 + 0x2) = 4;
        *(short *)((char *)a0 + 0x34) = 0;
        *(int *)((char *)a0 + 0x1c) = 0x3c;
    }



extern s32 func_801877C0(s32 a0);

void func_801819A0(s32 a0) {

    extern s32 D_80191C44[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80191C44[idx];
}


extern s32 func_80181948(s32 a0);
extern void func_801818E0(short*);
void func_801819E0(int param_1)
{
    if (((int (*)(void))func_80181948)() != 0) {
        ((void (*)(int))func_801818E0)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181A18);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181A68);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181B40);


extern void func_80172710(void);
extern s32 func_8018739C(void);
extern s32 func_80188D1C(void *);
extern s32 func_80178BF8(void);

s32 func_80181BC0(void *a0)
{
    void *s0 = a0;
    void **v0p;
    u16 v1;

    v0p = (void **)(s0 + 0x64);
    v1 = *(u16 *)(*v0p + 0x2);
    if (v1 != 0x2) {
        return 0;
    }

    if (func_8018739C() == 0) {
        return 0;
    }

    if (func_80188D1C(*v0p) != 0) {
        return 0;
    }

    *(u16 *)(*v0p + 0x2) = 0x3;
    func_80178BF8();

    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80181C38);



extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);


void func_80181CAC(void *a0) {

    extern short D_80191CAC;
    extern short D_801C3890;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_80191CAC);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C3890);
    func_80187750((s32)a0);
}


    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80187750(s32);
    extern void func_80187994(s32, s32, s32, s32);
    void func_80181D04(void *arg0) {
        extern short D_80191CAC;
        extern s32 D_801C37E8;
        extern u8 D_801B9354[];
        void *v1;
        *(short *)((char *)arg0 + 0x2) = 0x4;
        func_8012E8E0((s32)arg0, (s32)&D_80191CAC);
        v1 = *(void **)((char *)arg0 + 0x20);
        *(short *)((char *)v1 + 0x12) = *(short *)((char *)v1 + 0x12) + 0x800;
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&(*(short *)&D_801C37E8));
        func_80187750((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80187994((s32)arg0, (s32)&(*(short *)D_801B9354), 0x1, 0x40);
    }


extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80191CA4;
    void func_80181D8C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        func_80187778((s32 *)a0, (s32)&D_80191CA4);
    }


#include "common.h"

/* decl_prior-driven externs — signatures copied from the TU's own spelling
 * where "tu" was present on the card (wave law 2); rest from "def"/"fleet". */
extern s32 func_8018727C(void *a0, void *a1);
extern void func_80187778(s32 *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_801877C0(s32 a0);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);

extern short D_80191CB4;
extern short D_80191CA4;
extern short D_80191CAC;
extern short D_801C3890;

/* forward decls: both defined later in this TU (func_80181FE0 @6183,
 * func_80182058 @6231) and registered here as callback pointers. */
extern s32 func_80181FE0(void *a0);
extern s32 func_80182058(void *a0);

void func_80181DB8(void *arg0) {
    void *s0 = arg0;
    void *ptr;
    s32 v0;

    if (func_8018727C(arg0, &D_80191CB4) == 0) {
        return;
    }

    func_80187778((s32 *)s0, (s32)&D_80191CA4);

    ptr = *(void **)((u8 *)s0 + 0x68);
    *(s16 *)((u8 *)ptr + 0xC) = 0x7FFF;

    *(s32 *)((u8 *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)func_80181FE0);
    *(s32 *)((u8 *)s0 + 0xD8) = func_801788B8((s32)s0, (s32)func_80182058);

    v0 = ((s32 (*)(void))func_801877C0)();

    if (v0 == 3) {
        if (func_8018766C(0xA, 0x16) == 0) {
            *(s16 *)((u8 *)s0 + 0x2) = 1;
        } else {
            *(s16 *)((u8 *)s0 + 0x2) = 5;
        }
    } else {
        if (func_8018766C(0xA, 0x10) != 0) {
            *(s16 *)((u8 *)s0 + 0x2) = 3;
            func_8012E8E0((s32)s0, (s32)&D_80191CAC);
            func_8012E88C((s32)s0);
            func_8012A828((s32)s0, (s32)&D_801C3890);
            func_80187750((s32)s0);
            return;
        } else {
            if (func_8018766C(0x10, 0x16) != 0) {
                *(s16 *)((u8 *)s0 + 0x2) = 5;
            } else {
                *(s16 *)((u8 *)s0 + 0x2) = 1;
            }
        }
    }

    func_80187778((s32 *)s0, (s32)&D_80191CA4);
}



extern void (*D_80191D3C[])(void);

void func_80181ED4(void *a0) {
    D_80191D3C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80182F3C(s32 a0);
extern short D_80191CAC;
extern short D_801C3890;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_80178CBC(s32*, s32);

void func_80181F10(void *a0) {
    s32 v0;

    *(short *)((char *)a0 + 0x2) = 9;
    func_8012E8E0((s32)a0, (s32)&D_80191CAC);
    func_8012E88C((s32)a0);
    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801C3890);
    v0 = func_80182F3C((s32)a0);
    ((void (*)(s32, s32))func_80178CBC)((s32)a0, v0);
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_80191CDC;
    void func_80181F74(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        func_80178CBC(a0, &D_80191CDC);
    }



extern s32 func_801877C0(s32 a0);

void func_80181FA0(s32 a0) {

    extern s32 D_80191CC8[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80191CC8[idx];
}



extern void func_80172710(void);
extern s32 func_8018739C(void);
extern s32 func_80188D1C(void *);
extern s32 func_80178BF8(void);

s32 func_80181FE0(void *a0)
{
    void *s0 = a0;
    void **v0p;
    u16 v1;

    v0p = (void **)(s0 + 0x64);
    v1 = *(u16 *)(*v0p + 0x2);
    if (v1 != 0x5) {
        return 0;
    }

    if (func_8018739C() == 0) {
        return 0;
    }

    if (func_80188D1C(*v0p) != 0) {
        return 0;
    }

    *(u16 *)(*v0p + 0x2) = 0x6;
    func_80178BF8();

    return (s32)func_80172710;
}



/* func_80182058 — state-machine callback registered by func_80180A08.
 *
 * Shape (read off the target, not off Ghidra — the Ghidra seed is for a
 * different address entirely):
 *   - guard call func_8012BD14(a0->0x64), bail if result > 0x4000
 *   - switch on the u16 at +2 of a0->0x64, cases 3 / 2 / 4 (gcc balances the
 *     tree on the middle case 3, hence `slti $v0,$v1,4` for "index > node->high")
 *   - the comparison constants for the case-2/case-4 sub-tests ride in the
 *     dispatch branch delay slots (§3-T4: read the constant off the delay slot,
 *     not off the branch line) — case 2 tests +0x34 == 1, case 4 tests +0x34 == 0
 *   - the two adjacent globals get their own `lui $at` each => two separate
 *     symbols, NOT one array (§20 pointer-var rule does not apply here)
 *   - +0x34 is reloaded after the D_801EEAF0 store, and 0x64 is reloaded too:
 *     gcc-2.7.2 CSE invalidates memory on the global store, so re-express both
 */

extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);

s32 func_80182058(void *a0)
{

    extern s16 D_801EEAF0;
    extern s16 D_801EEAF2;
    void *p;
    u16 st;

    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        /* LOAD-BEARING zero-byte cross-jump barrier (cookbook §5a).
         * Without it gcc's find_cross_jump merges this `move v0,0; j epi`
         * tail with the identical case-2 failure tail -> 58 ins instead of
         * 60, and the case-2 `beq` then loses its delay-slot fill. */
        __asm__ __volatile__("");
        return 0;
    }

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801EEAF0 = st;
        D_801EEAF2 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182148);


extern s32 func_801886A0(s32 a0);
extern s32 func_80187A64(s32 a0);
extern void func_80187994(s32, s32, s32, s32);
extern void func_80181CAC(void *a0);

void func_801821C0(void *a0)
{

    extern u8 D_801B9354[];
    if (*(u16 *)((s32)a0 + 0x34) == 0) {
        if (func_801886A0(6) == 0) {
            return;
        }
        if (func_80187A64((s32)a0) == 0) {
            return;
        }
        ((void (*)(void *, void *, s32, s32))func_80187994)(a0, D_801B9354, 0, 0x40);
        *(s16 *)((s32)a0 + 0x34) = 1;
        return;
    }

    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (func_80187A64((s32)a0) != 0) {
        func_80181CAC(a0);
    }
}



/* func_80182254 — guarded dispatch: ask func_8018766C(10, 0x10); if it answers
 * zero, run func_80181D04 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80181D04();

void func_80182254(void *arg0) {
    if (func_8018766C(10, 0x10) == 0) {
        func_80181D04(arg0);
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);


void func_80182294(void *a0) {

    extern short D_80191CAC;
    extern short D_801C3890;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_80191CAC);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C3890);
        func_80187750((s32)a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182304);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182398);

#include "common.h"

extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80187778(s32*, s32);

void func_80182400(void * arg0) {

    extern short D_80191CA4;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80191CA4);
    }
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_80191D14;
    void func_80182450(short *param) {
        param[1] = 0xB;
        ((void (*)(s32, s32))func_80178CBC)((int)param, (int)&D_80191D14);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018247C);

extern s16 D_801C36E8;
extern u8 D_801B9360[];
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32 a0);
extern void func_80182898(void);
extern void func_80187750(s32 a0);
extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);

    void func_801824DC(void *arg0) {
        s32 s0;
        s0 = (s32)arg0;
        *(s16*)((char *)arg0 + 0x2) = 2;
        func_8012E88C((s32)arg0);
        __asm__("" ::: "memory");
        ((void (*)(s32 *, s32))func_8012A828)((s32*)s0, (s32)&D_801C36E8);
        func_80187750((s32)s0);
        *(s16*)((char *)arg0 + 0x34) = 0;
        func_80187994((s32)s0, (s32)D_801B9360, 0, 0x80);
        func_80182898();
    }


extern s32 D_80191D74;
extern short D_801CAA80;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32, s32);
extern void func_80182898(void);
extern void func_80187750(s32);

    void func_80182548(void *a0) {
        extern s32 D_80191D74;
        extern short D_801CAA80;
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_80191D74);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CAA80);
        func_80187750((s32)a0);
        func_80182898();
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801825A8);

extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80191D6C;
    void func_8018260C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        func_80187778((s32 *)a0, (s32)&D_80191D6C);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182638);


extern void func_80187778(s32*, s32);
    extern short D_80191D6C;
    void func_8018268C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 9;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80191D6C);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801826B8);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182704);


extern void (*D_80191E0C[])(void);

void func_80182824(void *a0) {
    D_80191E0C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182860);

extern s32 D_801DD064;
extern s32 D_801D6014;

void func_80182898(void) {
    D_801D6014 = D_801DD064;
}


extern s32 D_801EEAF8;
extern s32 D_801D6014;

void func_801828B0(void) {
    *(s32 *)&D_801D6014 = D_801EEAF8;
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80178CBC(s32 *, s32);

void func_801828C8(void *arg0) {

    extern s32 D_80191D74;
    extern s32 D_801C3790;
    extern s32 D_80191DA4;
    *(short *)((char *)arg0 + 0x2) = 5;
    func_8012E8E0((s32)arg0, (s32)&D_80191D74);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C3790);
    func_80178CBC((s32 *)arg0, (s32)&D_80191DA4);
}



extern s32 func_801877C0(s32 a0);

void func_80182928(s32 a0) {

    extern s32 D_80191D90[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80191D90[idx];
}



/* func_80182968 — guarded dispatch: ask func_8018766C(9, 0x12); if it answers
 * NON-zero, run func_801824DC on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_801824DC();

void func_80182968(void *arg0) {
    if (func_8018766C(9, 0x12) != 0) {
        func_801824DC(arg0);
    }
}


extern s32 func_80187A64(s32 a0);
extern s32 func_801886A0(s32 arg0);
extern u8 D_801B936C[];
extern void func_80182548();
extern void func_80187994(s32, s32, s32, s32);

void func_801829A8(void *a0) {
    s32 v0;

    if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
        if ((v0 = func_801886A0(3)) != 0 && (v0 = ((s32 (*)(void *))func_80187A64)(a0)) != 0) {
            ((void (*)(void *, void *, s32, s32))func_80187994)(a0, D_801B936C, 0, 0x80);
            *(u16 *)((u8 *)a0 + 0x34) = 1;
        }
    } else {
        if ((v0 = ((s32 (*)(void *))func_80187A64)(a0)) != 0) {
            func_80182548(a0);
        }
    }
}



/* func_80182A34 — guarded dispatch: ask func_8018766C(9, 0xF); if it answers
 * zero, run func_801825A8 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_801825A8(void *arg0);

void func_80182A34(void *arg0) {
    if (func_8018766C(9, 0xF) == 0) {
        func_801825A8(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182A74);


extern s32 func_80187A64(s32 a0);
extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801886A0(s32 a0);
extern void func_8018260C(short*);

void func_80182AEC(void *arg0) {

    extern u8 D_801B9360[];
    if (*(u16 *)((char *)arg0 + 0x34) == 0) {
        if (((s32 (*)(void))func_80187A64)() != 0) {
            func_80187994((s32)arg0, (s32)&D_801B9360[0], 1, 0x80);
            *(s16 *)((char *)arg0 + 0x34) = 1;
        }
    } else if (func_801886A0(3) != 0) {
        if (func_80187A64((s32)arg0) != 0) {
            ((void (*)(void *))func_8018260C)(arg0);
        }
    }
}



/* func_80182B78 — guarded dispatch: ask func_8018766C(15, 0x11); if it answers
 * zero, run func_80182638 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80182638(void *arg0);

void func_80182B78(void *arg0) {
    if (func_8018766C(15, 0x11) == 0) {
        func_80182638(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80182BB8);


/* func_80182CC4 — guarded dispatch: ask func_8018766C(17, 0x12); if it answers
 * zero, run func_801826B8 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_801826B8(void *arg0);

void func_80182CC4(void *arg0) {
    if (func_8018766C(17, 0x12) == 0) {
        func_801826B8(arg0);
    }
}


#include "common.h"

extern s32 func_8018727C(void *a0, void *a1);
extern void func_80182860(void);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);
extern void func_80182898(void);
extern void func_80187778(s32 *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80182DFC(void *a0);

extern short D_80191D7C;
extern s32 D_80191D74;
extern short D_801CAA80;
extern short D_80191D6C;

void func_80182D04(void *a0) {
    s32 v0;
    void *v1;

    if (func_8018727C(a0, &D_80191D7C) != 0) {
        func_80182860();
        v0 = func_8018766C(9, 0xF);
        if (v0 != 0) {
            *(s16 *)((char *)a0 + 0x2) = 3;
            func_8012E8E0((s32)a0, (s32)&D_80191D74);
            func_8012E88C((s32)a0);
            ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CAA80);
            func_80187750((s32)a0);
            func_80182898();
        } else {
            if (func_8018766C(0xF, 0x11) != 0) {
                *(s16 *)((char *)a0 + 0x2) = 7;
            } else if (func_8018766C(0x11, 0x12) != 0) {
                *(s16 *)((char *)a0 + 0x2) = 9;
            } else {
                *(s16 *)((char *)a0 + 0x2) = 1;
            }
            func_80187778((s32 *)a0, (s32)&D_80191D6C);
        }
        v1 = *(void **)((char *)a0 + 0x68);
        *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
        *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)&func_80182DFC);
    }
}



extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80182DFC(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 3) {
        return 0;
    }

    if (func_8012BD14(ptr) >= 0x4001) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);


void func_80182E70(void *arg0) {

    extern short D_80191E38;
    extern short D_801C37E8;
    extern short D_801B9400;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_80191E38);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C37E8);
    func_80187750((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80187994((s32)arg0, (s32)&D_801B9400, 0, 0x40);
}




extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);


void func_80182EE4(void *a0) {

    extern short D_80191E40;
    extern short D_801C3890;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_80191E40);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C3890);
    func_80187750((s32)a0);
}


#include "common.h"

/* TU spellings adopted verbatim from src/ov_SC03_001/ov_SC03_001_jr_8017AE2C.c
 * (law 2): func_800291B4/func_800291A0 are the file-scope externs at lines 57-58,
 * func_801877C0 is the line-4911 spelling and is CALLED through the file's own
 * zero-arg idiom `((s32 (*)(void))func_801877C0)()` (line 4924) because the target
 * .s leaves $a0 untouched.  func_8012E544 is not declared in this TU; the fleet
 * modal spelling (1365 sites) is used.  The D_* tables follow the TU house style
 * `extern short D_x;` + `(s32)&D_x`. */
extern s32 func_8012E544(s32 a0);
extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);
extern s32 func_801877C0(s32);

extern short D_80191F00;
extern short D_80191F40;
extern short D_80191F80;
extern short D_80191FC0;
extern short D_80192000;
extern short D_80192070;
extern short D_801920C8;
extern short D_80192120;
extern short D_80192190;
extern short D_801921E8;
extern short D_80192278;
extern short D_801922A0;

s32 func_80182F3C(s32 a0) {
    s32 e;
    s32 cond;
    s32 result;
    /* $v0 pin: the two-def return pseudo of the early-out below falls to
     * global_alloc and lands in $a0 (costing a `move $v0,$a0` in each of the two
     * delay slots the target leaves as `nop`).  The pin restores the target's
     * $v0 = pointer / $v1 = 0xA2 / $a0 = halfword assignment at zero byte cost. */
    register s32 v __asm__("$2");
    s32 c;

    /* +0x0 is a u16 object id; 0xA2 selects the 0xA4 partner lookup. */
    if (*(u16 *)(a0 + 0) == 0xA2) {
        e = func_8012E544(0xA4);
        /* if/else STATEMENT, not `&&`/`?:` — fold canonicalises both of those to
         * "non-zero arm first", which emits the [load][zero] block order; the
         * target's cross-jumped shape needs [zero][load]. */
        if (e == 0) {
            cond = 0;
        } else {
            cond = (*(u16 *)(e + 2) == 3);
        }
    } else {
        e = func_8012E544(0xA2);
        if (e == 0) {
            cond = 0;
        } else {
            cond = (*(u16 *)(e + 2) == 3);
        }
    }

    if (!cond) {
        v = (s32)&D_801922A0;
        if (*(u16 *)(a0 + 0) == 0xA2) {
            v = (s32)&D_80192278;
        }
        return v;
    }

    result = (s32)&D_80191F00;
    switch (((s32 (*)(void))func_801877C0)()) {
    case 0:
        c = func_800291B4(0xD6) & 0xFF;
        /* zero-byte re-tie (cookbook §189-C): without it cse folds
         * `(raw & 0xFF) & 1` back onto the raw call result and emits
         * `andi $v0,$v0,1`; the target reads the masked copy, `andi $v0,$a1,1`. */
        __asm__("" : "=r"(c) : "0"(c));
        if (c != 0) {
            result = (s32)&D_80191F80;
            if ((c & 1) != 0) {
                result = (s32)&D_80191F40;
            }
        }
        c++;
        if ((c & 0xFF) == 0) {
            c = 2;
        }
        func_800291A0(0xD6, c & 0xFF);
        break;
    case 1:
        /* signed magic 0x55555556 => the modulo operand is a plain (signed) s32;
         * a u8 `c` would let c-typeck's `shorten` do it unsigned (multu/0xAAAAAAAB). */
        c = func_800291B4(0xD7) & 0xFF;
        switch (c % 3) {
        case 0:
            result = (s32)&D_80191FC0;
            break;
        case 1:
            /* cse re-uses $s0 (== 1 on this arm of the outer switch) for the
             * literal 1, which is where the target's `beq $v0,$s0` comes from. */
            result = (s32)&D_80192000;
            break;
        default:
            result = (s32)&D_80192070;
            break;
        }
        c++;
        func_800291A0(0xD7, c & 0xFF);
        break;
    case 2:
        c = func_800291B4(0xD9) & 0xFF;
        __asm__("" : "=r"(c) : "0"(c));
        result = (s32)&D_80192190;
        if ((c & 1) != 0) {
            result = (s32)&D_801921E8;
        }
        c++;
        func_800291A0(0xD9, c & 0xFF);
        break;
    case 3:
        break;
    default:
        c = func_800291B4(0xD8) & 0xFF;
        __asm__("" : "=r"(c) : "0"(c));
        result = (s32)&D_801920C8;
        if ((c & 1) != 0) {
            result = (s32)&D_80192120;
        }
        c++;
        func_800291A0(0xD8, c & 0xFF);
        break;
    }
    return result;
}


    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80187750(s32);
    extern void func_80187994(s32, s32, s32, s32);
    void func_80183168(void *arg0) {
        extern short D_80191E40;
        extern s32 D_801C37E8;
        extern u8 D_801B940C[];
        void *v1;
        *(short *)((char *)arg0 + 0x2) = 0x4;
        func_8012E8E0((s32)arg0, (s32)&D_80191E40);
        v1 = *(void **)((char *)arg0 + 0x20);
        *(short *)((char *)v1 + 0x12) = *(short *)((char *)v1 + 0x12) + 0x800;
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&(*(short *)&D_801C37E8));
        func_80187750((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80187994((s32)arg0, (s32)&(*(short *)D_801B940C), 0x1, 0x40);
    }


extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80191E38;
    void func_801831F0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        func_80187778((s32 *)a0, (s32)&D_80191E38);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_8018321C);


extern void (*D_801922F0[])(void);

void func_8018333C(void *a0) {
    D_801922F0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80182F3C(s32 a0);
extern short D_80191E40;
extern short D_801C3890;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_80178CBC(s32*, s32);

void func_80183378(void *a0) {
    s32 v0;

    *(short *)((char *)a0 + 0x2) = 9;
    func_8012E8E0((s32)a0, (s32)&D_80191E40);
    func_8012E88C((s32)a0);
    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801C3890);
    v0 = func_80182F3C((s32)a0);
    ((void (*)(s32, s32))func_80178CBC)((s32)a0, v0);
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_80191E70;
    void func_801833DC(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        func_80178CBC((s32 *)a0, (s32)&D_80191E70);
    }



extern s32 func_801877C0(s32 a0);

void func_80183408(s32 a0) {

    extern s32 D_80191E5C[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80191E5C[idx];
}



extern void func_80172710(void);
extern s32 func_8018739C(void);
extern s32 func_80188D1C(void *);
extern s32 func_80178BF8(void);

s32 func_80183448(void *a0)
{
    void *s0 = a0;
    void **v0p;
    u16 v1;

    v0p = (void **)(s0 + 0x64);
    v1 = *(u16 *)(*v0p + 0x2);
    if (v1 != 0x5) {
        return 0;
    }

    if (func_8018739C() == 0) {
        return 0;
    }

    if (func_80188D1C(*v0p) != 0) {
        return 0;
    }

    *(u16 *)(*v0p + 0x2) = 0x6;
    func_80178BF8();

    return (s32)func_80172710;
}



/* func_801834C0 — state-machine callback registered by func_80180A08.
 *
 * Shape (read off the target, not off Ghidra — the Ghidra seed is for a
 * different address entirely):
 *   - guard call func_8012BD14(a0->0x64), bail if result > 0x4000
 *   - switch on the u16 at +2 of a0->0x64, cases 3 / 2 / 4 (gcc balances the
 *     tree on the middle case 3, hence `slti $v0,$v1,4` for "index > node->high")
 *   - the comparison constants for the case-2/case-4 sub-tests ride in the
 *     dispatch branch delay slots (§3-T4: read the constant off the delay slot,
 *     not off the branch line) — case 2 tests +0x34 == 1, case 4 tests +0x34 == 0
 *   - the two adjacent globals get their own `lui $at` each => two separate
 *     symbols, NOT one array (§20 pointer-var rule does not apply here)
 *   - +0x34 is reloaded after the D_801EEB00 store, and 0x64 is reloaded too:
 *     gcc-2.7.2 CSE invalidates memory on the global store, so re-express both
 */

extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);

s32 func_801834C0(void *a0)
{

    extern s16 D_801EEB00;
    extern s16 D_801EEB02;
    void *p;
    u16 st;

    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        /* LOAD-BEARING zero-byte cross-jump barrier (cookbook §5a).
         * Without it gcc's find_cross_jump merges this `move v0,0; j epi`
         * tail with the identical case-2 failure tail -> 58 ins instead of
         * 60, and the case-2 `beq` then loses its delay-slot fill. */
        __asm__ __volatile__("");
        return 0;
    }

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801EEB00 = st;
        D_801EEB02 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801835B0);


extern s32 func_801886A0(s32 a0);
extern s32 func_80187A64(s32 a0);
extern void func_80187994(s32, s32, s32, s32);
extern void func_80182EE4(void *a0);

void func_80183628(void *a0)
{

    extern u8 D_801B940C[];
    if (*(u16 *)((s32)a0 + 0x34) == 0) {
        if (func_801886A0(3) == 0) {
            return;
        }
        if (func_80187A64((s32)a0) == 0) {
            return;
        }
        ((void (*)(void *, void *, s32, s32))func_80187994)(a0, D_801B940C, 0, 0x40);
        *(s16 *)((s32)a0 + 0x34) = 1;
        return;
    }

    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (func_80187A64((s32)a0) != 0) {
        func_80182EE4(a0);
    }
}



extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80183168();

void func_801836BC(s32 *a0) {
    *(s32 *)((s32)a0[0x33] + 0xB0) = 2;
    if (func_8018766C(10, 16) != 0) {
        return;
    }
    func_80183168(a0);
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);


void func_80183708(void *a0) {

    extern short D_80191E40;
    extern short D_801C3890;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_80191E40);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C3890);
        func_80187750((s32)a0);
    }
}



extern s32 func_80187A64(s32 a0);
extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801886A0(s32 a0);
extern void func_801831F0(short*);

void func_80183778(void *arg0) {

    extern u8 D_801B9400[];
    if (*(u16 *)((char *)arg0 + 0x34) == 0) {
        if (((s32 (*)(void))func_80187A64)() != 0) {
            func_80187994((s32)arg0, (s32)&D_801B9400[0], 1, 0x40);
            *(s16 *)((char *)arg0 + 0x34) = 1;
        }
    } else if (func_801886A0(3) != 0) {
        if (func_80187A64((s32)arg0) != 0) {
            ((void (*)(void *))func_801831F0)(arg0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80183804);

#include "common.h"

extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80187778(s32*, s32);

void func_8018386C(void * arg0) {

    extern short D_80191E38;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80191E38);
    }
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_801922C8;
    void func_801838BC(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0xB;
        func_80178CBC((s32 *)a0, (s32)&D_801922C8);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801838E8);



extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);


void func_80183948(void *arg0) {

    extern short D_80192320;
    extern short D_801C36E8;
    extern short D_801B9434;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_80192320);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C36E8);
    func_80187750((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80187994((s32)arg0, (s32)&D_801B9434, 0, 0x60);
}




extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);


void func_801839BC(void *a0) {

    extern short D_80192328;
    extern short D_801CAA80;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_80192328);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CAA80);
    func_80187750((s32)a0);
}


    extern void func_8012E8E0(s32, s32);
    extern void func_8012E88C(s32);
    extern void func_8012A828(s32, s32);
    extern void func_80187750(s32);
    extern void func_80187994(s32, s32, s32, s32);
    void func_80183A14(void *arg0) {
        extern short D_80192328;
        extern short D_801C36E8;
        extern short D_801B9440;
        *(short *)((char *)arg0 + 0x2) = 6;
        func_8012E8E0((s32)arg0, (s32)&D_80192328);
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C36E8);
        func_80187750((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80187994((s32)arg0, (s32)&D_801B9440, 1, 0x60);
    }



extern void (*D_80192418[])(void);

void func_80183A88(void *a0) {
    D_80192418[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80183AC4);


extern s32 D_801DD950;
extern s32 D_801DAAAC;

void func_80183AFC(void) {
    D_801DAAAC = D_801DD950;
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80178CBC(s32 *, s32);

void func_80183B14(void *arg0) {

    extern s32 D_80192328;
    extern s32 D_801C3790;
    extern s32 D_80192398;
    *(short *)((char *)arg0 + 0x2) = 5;
    func_8012E8E0((s32)arg0, (s32)&D_80192328);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C3790);
    func_80178CBC((s32 *)arg0, (s32)&D_80192398);
}



extern s32 func_801877C0(s32 a0);

void func_80183B74(s32 a0) {

    extern s32 D_80192344[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80192344[idx];
}



extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_80183BB4(void) {
        if ((func_80029178(0x113) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x113, 1);
            return 1;
        }
        return 0;
    }



/* func_80183BF0 — guarded dispatch: ask func_8018766C(7, 0xe); if it answers
 * NON-zero, run func_80183948 on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80183948(void *arg0);

void func_80183BF0(void *arg0) {
    if (func_8018766C(7, 0xe) != 0) {
        func_80183948(arg0);
    }
}


extern s32 func_80187A64(s32 a0);
extern s32 func_801886A0(s32 arg0);
extern void *D_801B9440;
extern void func_801839BC(void *a0);
extern void func_80187994(s32, s32, s32, s32);

void func_80183C30(s32 a0) {
    s32 v0, v1;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if ((v0 = func_801886A0(2)) != 0 && (v0 = func_80187A64(a0)) != 0) {
            *(u16 *)(a0 + 0x34) = 1;
            func_80187994(a0, (s32)&D_801B9440, 0, 0x60);
            v1 = *(s32 *)(a0 + 0xCC);
            *(s32 *)(v1 + 0xB0) = 2;
        }
    } else {
        if ((v0 = func_80187A64(a0)) != 0) {
            func_801839BC(a0);
        }
    }
}



/* func_80183CC8 — guarded dispatch: ask func_8018766C(7, 0xE); if it answers
 * zero, run func_80183A14 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80183A14();

void func_80183CC8(void *arg0) {
    if (func_8018766C(7, 0xE) == 0) {
        func_80183A14(arg0);
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);


void func_80183D08(void *a0) {

    extern short D_80192328;
    extern short D_801CAA80;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_80192328);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CAA80);
        func_80187750((s32)a0);
    }
}


extern s32 func_80187A64(s32 a0);
extern s32 func_801886A0(s32 arg0);
extern short D_80192320;
extern short D_801B9434;
extern void func_80187778(s32*, s32);
extern void func_80187994(s32, s32, s32, s32);

void func_80183D78(s32 a0) {
    if (*(u16*)(a0 + 0x34) == 0) {
        if (func_80187A64(a0) != 0) {
            *(s16*)(a0 + 0x34) = 1;
            func_80187994(a0, (s32)&D_801B9434, 1, 0x60);
        }
    } else {
        if (func_801886A0(0x2) != 0) {
            if (func_80187A64(a0) != 0) {
                *(s16*)(a0 + 0x2) = 1;
                func_80187778((s32*)a0, (s32)&D_80192320);
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80183E14);


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80183EE4(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 3) {
        return 0;
    }

    if (func_8012BD14(ptr) >= 0x4001) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_80187778(s32 *a0, s32 a1);

void func_80183F58(void *arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_80192434;
    *(s16 *)((char *)arg0 + 0x2) = 0x2;
    func_80187778(arg0, &D_80192434);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80183F84);

extern s32 D_801B9470;
extern short D_801C37E8;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);

void func_80183FF4(s32 a0) {
    *(u16 *)(a0 + 2) = 6;
    func_8012E88C(a0);
    ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801C37E8);
    func_80187750(a0);
    func_80187994(a0, (s32)&D_801B9470, 0, 0x40);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184054);


extern void func_80187778(s32*, s32);
    extern short D_80192434;
    void func_801840B8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80192434);
    }


#include "common.h"

extern s32 func_8018727C(void *a0, void *a1);
extern s32 func_801877C0(s32 a0);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);
extern void func_80187994(s32, s32, s32, s32);
extern void func_80187778(s32 *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_80184350(void *a0);
extern void func_801843DC(void *a0);

void func_801840E4(void *a0) {

    extern s16 D_80192444;
    extern short D_80192434;
    extern s32 D_801B9470;
    extern short D_801C37E8;
    void *s0 = a0;
    void *v1;
    s32 v0;

    if (func_8018727C(a0, &D_80192444) != 0) {
        if (((s32 (*)(void))func_801877C0)() == 3) {
            v0 = func_8018766C(7, 0x14);
            if (v0 != 0) {
                *(s16 *)((char *)s0 + 0x2) = 2;
            } else {
                *(s16 *)((char *)s0 + 0x2) = 1;
            }
            func_80187778(s0, &D_80192434);
        } else {
            v0 = func_8018766C(7, 0xA);
            if (v0 != 0) {
                *(s16 *)((char *)s0 + 0x2) = 2;
                func_80187778(s0, &D_80192434);
            } else {
                v0 = func_8018766C(0xA, 0xC);
                if (v0 != 0) {
                    *(s16 *)((char *)s0 + 0x2) = 6;
                    func_8012E88C((s32)s0);
                    ((void (*)(s32, s32))func_8012A828)((s32)s0, (s32)&D_801C37E8);
                    func_80187750((s32)s0);
                    func_80187994((s32)s0, (s32)&D_801B9470, 0, 0x40);
                } else {
                    v0 = func_8018766C(0xC, 0x14);
                    if (v0 != 0) {
                        *(s16 *)((char *)s0 + 0x2) = 8;
                    } else {
                        *(s16 *)((char *)s0 + 0x2) = 1;
                    }
                    func_80187778(s0, &D_80192434);
                }
            }
        }

        v1 = *(void **)((char *)s0 + 0x68);
        *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
        *(s32 *)((char *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)&func_80184350);
        *(s32 *)((char *)s0 + 0xD8) = func_801788B8((s32)s0, (s32)&func_801843DC);
    }
}



extern void (*D_80192510[])(void);

void func_80184210(void *a0) {
    D_80192510[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_8019246C;
    void func_8018424C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 4;
        ((void (*)(s32, s32))func_80178CBC)((int)a0, (int)&D_8019246C);
    }



extern void func_80178CBC(s32*, s32);
    extern short D_8019246C;
    void func_80184278(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_8019246C);
    }


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_801924B8;
    void func_801842A4(short *param) {
        param[1] = 0xC;
        ((void (*)(s32, s32))func_80178CBC)((int)param, (int)&D_801924B8);
    }



extern s32 func_801877C0(s32 a0);

void func_801842D0(s32 a0) {

    extern s32 D_80192458[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_80192458[idx];
}



extern s32 func_801877C0(s32 a0);

void func_80184310(s32 a0) {

    extern s32 D_801924A4[];
    s32 idx = func_801877C0(a0);
    *(s32 *)(a0 + 0xE4) = D_801924A4[idx];
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184350);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801843DC);



extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80183F58(void *arg0);

void func_8018444C(void *arg0) {
    s32 v1;

    v1 = *(s32 *)((char *)arg0 + 0xCC);
    *(s32 *)((char *)v1 + 0xB0) = 2;
    if (func_8018766C(7, 0x14) != 0) {
        func_80183F58(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184498);


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80187778(s32*, s32);

void func_8018451C(void * arg0) {

    extern short D_80192434;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80192434);
    }
}


extern s32 func_80187A64(s32 a0);
extern s32 func_801886A0(s32 arg0);
extern void func_80183FF4(s32 a0);

void func_8018456C(void *a0) {
    if (func_801886A0(2)) {
        if (func_80187A64((s32)a0)) {
            func_80183FF4((s32)a0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801845B8);

extern s32 func_80187A64(s32 a0);
extern s32 func_801886A0(s32 arg0);
extern void func_801840B8(void*);

void func_801845FC(void *a0) {
    if (func_801886A0(2)) {
        if (func_80187A64((s32)a0)) {
            ((void (*)(s32))func_801840B8)((s32)a0);
        }
    }
}


    extern s32 func_8018766C(s32 a0, s32 a1);
    extern void func_80187778(s32*, s32);
    extern short D_80192434;
    void func_80184648(s32 *a0) {
        *(s32 *)((s32)a0[0x33] + 0xB0) = 2;
        if (func_8018766C(0xC, 0x14) != 0) {
            return;
        }
        *(short *)((char *)a0 + 0x2) = 1;
        ((void (*)(s32 *, void *))func_80187778)(a0, (void *)&(*(s32 *)&D_80192434));
    }


#include "common.h"

extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80187778(s32*, s32);

void func_801846A0(void * arg0) {

    extern short D_80192434;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_80187778)((int)arg0, (int)&D_80192434);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_801846F0);


extern void (*D_80192544[])(void);

void func_80184748(void *a0) {
    D_80192544[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184784(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


extern s32 func_8012E57C(s32 a0, s32 a1);

    void func_80184794(s32 a0) {
        *(s16 *)(a0 + 0x2) = 1;
        *(s32 *)(a0 + 0xCC) = func_8012E57C(0x61, 0xA);
    }



/* func_801847D0 — state-entry init (family exemplar, reach x11).
 * Sets the actor's state id (halfword @ +0x2) then runs the fixed
 * five-call entry chain. Sibling style copied from func_80180164
 * in the same TU (cookbook §71). */

extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);


void func_801847D0(void *arg0) {

    extern short D_8019254C;
    extern short D_801C3990;
    extern short D_801B94FC;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_8019254C);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801C3990);
    func_80187750((s32)arg0);
    func_80187994((s32)arg0, (s32)&D_801B94FC, 0, 0x60);
}


extern s32 D_801B9510;
extern s32 D_801C3990;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);

void func_80184840(s32 a0) {
    *(u16 *)(a0 + 2) = 3;
    func_8012E88C(a0);
    ((void (*)(s32, s32))func_8012A828)(a0, (s32)&(*(short *)&D_801C3990));
    func_80187750(a0);
    func_80187994(a0, (s32)&D_801B9510, 0, 0x40);
}


    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80187750(s32 a0);
    extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 D_801C3990;
    extern short D_801B94FC;
    void func_801848A0(s32 a0) {
        *(u16 *)(a0 + 2) = 6;
        func_8012E88C(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801C3990);
        func_80187750(a0);
        func_80187994(a0, (s32)&(*(s32 *)&D_801B94FC), 1, 0x60);
    }



extern void (*D_80192624[])(void);

void func_80184900(void *a0) {
    D_80192624[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_801925AC;
    void func_8018493C(short *param) {
        param[1] = 0x5;
        ((void (*)(s32, s32))func_80178CBC)((int)param, (int)&D_801925AC);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184968);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801849E0(void) {
        if ((func_80029178(0x115) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x115, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184A1C);

extern s32 func_80187A64(s32);
    extern void func_80184840();
    void func_80184A8C(s32 arg0) {
        if (func_80187A64(arg0)) {
            func_80184840(arg0);
        }
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184AC4);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184B60);

extern s32 func_80187A64(s32 a0);
extern short D_8019254C;
extern void func_80187778(s32*, s32);

void func_80184BB0(s32 a0)
{
    if (func_80187A64(a0) != 0) {
        *(s16 *)(a0 + 0x2) = 1;
        ((void (*)(s32 *, s32 *))func_80187778)((s32*)a0, &D_8019254C);
    }
}


#include "common.h"

extern s32 func_8018727C(void *a0, void *a1);
extern s32 D_8019255C;

extern s32 func_801877C0(s32 a0);
extern s32 func_8018766C(s32 a0, s32 a1);

extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80187750(s32 a0);
extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801C3990;
extern s32 D_801B9510;

extern void func_80187778(s32 *a0, s32 a1);
extern short D_8019254C;

extern s32 func_80184CF0(void *a0);
extern s32 func_801788B8(s32 a0, s32 a1);

void func_80184BF4(void *arg0) {
    void *s0 = arg0;
    s32 idx;
    s32 ok;
    s32 a0v, a1v;
    void *v1p;

    if (func_8018727C(arg0, &D_8019255C) == 0) {
        return;
    }

    idx = ((s32 (*)(void))func_801877C0)();
    switch (idx) {
    case 0:
        a0v = 7;
        a1v = 0x13;
        break;
    case 3:
        ok = 0;
        goto check;
    default:
        a0v = 9;
        a1v = 0x11;
        break;
    }
    ok = (func_8018766C(a0v, a1v) != 0);

check:
    if (ok != 0) {
        *(short *)((char *)s0 + 0x2) = 3;
        func_8012E88C((s32)s0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)s0, (s32)&D_801C3990);
        func_80187750((s32)s0);
        func_80187994((s32)s0, (s32)&D_801B9510, 0, 0x40);
    } else {
        *(short *)((char *)s0 + 0x2) = 1;
        func_80187778((s32 *)s0, (s32)&D_8019254C);
    }

    v1p = *(void **)((char *)s0 + 0x68);
    *(short *)((char *)v1p + 0xC) = 0x7FFF;
    *(s32 *)((char *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)&func_80184CF0);
}



extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80184CF0(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 3) {
        return 0;
    }

    if (func_8012BD14(ptr) >= 0x4001) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_80187778(s32 *a0, s32 a1);
    extern short D_80192640;
    void func_80184D64(short *param_1) {
        *(short *)((char *)param_1 + 2) = 1;
        func_80187778((s32 *)param_1, (s32)&D_80192640);
    }


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8017AE2C", func_80184D90);
