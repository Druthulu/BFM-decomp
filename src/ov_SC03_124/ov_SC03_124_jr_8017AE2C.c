#include "common.h"
#include "../shared/engine_prelude.h"


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
extern u8 D_8018D0E8;
extern u8 D_8018D058;
extern u8 D_8018D034;
extern u8 D_8018D010;
extern u8 D_8018D0C4;
extern u8 D_8018D0A0;
extern u8 D_8018D07C;
extern u8 D_8018CFEC;
extern void func_80145934(void);
extern u8 D_8018D178;
extern u8 D_8018D154;
extern u8 D_8018D130;
extern u8 D_8018D10C;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
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
extern unsigned char D_8018C570[];
extern unsigned char D_8018C5A0[];
extern unsigned char D_8018C5F0[];
extern unsigned char D_8018C620[];
extern unsigned char D_8018C650[];
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
extern void (*D_8018C6A0[])(void *);
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
extern s32 D_8018C768[];
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
extern u8 D_8018C7F0[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018C7F8;
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
extern int D_801E0650;
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
extern s32 D_801E0654;
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
extern s32 D_8018C828;
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
extern void (*D_8018C8D0[])(void);
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
extern void (*D_8018C8F4[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C8E4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C908[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C914[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C924[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C93C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C92C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C950[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C96C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C95C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C980[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C994[])(void);
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
extern s32 D_8018C9A8;
extern void (*D_8018C9D0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C9B0;
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
extern int (*D_8018CA1C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018CA20[])(void);
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
extern unsigned short D_8018CE84[];
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
extern void (*D_8018CE94[])(void);
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
extern int D_801E0688;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018CEBC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018CE9C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018CEAC;
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
extern void (*D_8018CEFC[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018CF04[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018CED0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018CF10[])(void);
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
extern u8 D_8018CEE0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E0690;
extern s32 D_801E069C;
extern s32 D_801E06A0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018CF4C[])(s32 *);
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
extern s32 D_8018CF20[];
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
extern s32 D_801E0698;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018D19C[])(void);
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
extern char D_8018CFBC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018D240[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018D394[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018D1B0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018D39C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018D1C0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018D1E0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018D3A4[])(void);
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
extern void (*D_8018D3CC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018D3D8[])(void);
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
extern void (*D_8018D24C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018D47C;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018C560[];
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
extern unsigned char D_8018D490[];
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
extern s8 D_8018D4CC[];
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
extern u16 D_8018D514;
extern u16 D_8018D516;
extern u16 D_8018D518;
extern s32 D_8018D51C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018D524;
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
extern int D_8018D230;
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
extern unsigned int D_8018D5A8[];
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
extern void (*D_8018D658[])(void);
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
extern void func_801483E8(unsigned char *self);
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
extern int func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_8018D688[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018D6EC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E06A8[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018D710[])(void);
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
extern int D_801E0700[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018D758[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018D748;
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
extern char D_801DFB40[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018D760[])(void);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418(s32 s0);
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void (*D_8018D7B4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018D77C;
extern s16 D_8018D7B0;
extern s16 D_8018D7AE;
extern s16 D_8018D7AC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018D7C0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E0760;
extern u8 D_801E0761;
extern u8 D_801E0762;
extern u8 D_801E0763;
extern u8 D_801E0764;
extern u8 D_801E0765;
extern u8 D_801E0766;
extern u8 D_801E0767;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018D7D0[])(void);
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
extern s32 D_801E07A0;
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
extern void (*D_8018D814[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D890[];
extern s32 D_8018D8B0[];
extern u8 D_8018D92C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D94C[];
extern u8 D_8018D96C[];
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
extern void func_80165A18(void);
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void (*D_8018DA08[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018DA84[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801DFB50;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018DA90[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018DA98[])(void);
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
extern void (*D_8018DB60[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018DB70[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018DB80[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018DB8C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018DAEC[];
extern u8   D_8018DB00[];
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
extern void (*D_8018DBA4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018DBAC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018DBB4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018DBBC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018DBC4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018DBCC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018DBD4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018DC88[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018DC90[])(void);
extern void func_80169F00(void *a0);
extern char D_8018DC40[];
extern char D_8018DC00[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018DCC8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018DCD4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018DD1C[])(void);
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
extern void (*D_8018DD98[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E0AC0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018DD8C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018DDD0[];
extern unsigned short D_8018DDD8[];
extern unsigned short D_8018DDE0[];
extern unsigned char D_801E0AC8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E0AC0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018DDE8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E0BFC;
extern M2C_UNK D_801E0C00;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E0B88;
extern void (*D_8018DE18[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E0C04[];
extern u8 D_801E0C0C[];
extern u8 D_801E0BBC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018DE20[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018DE3C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018DE44[])(void);
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
extern void (*D_8018DEAC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018DE50;
extern u8 D_8018DE5C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018DEE0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018DEE8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018DF3C[])(void);
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
extern u16 D_8018DF70[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018DF60[];
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
extern s32 D_8018DF8C;
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
extern void (*D_8018E004[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018E00C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018E014[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018E01C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018E024[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018E02C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018E038[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018E044[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018E050[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018E060[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018E070[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018E078[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018E080[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018E088[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018E090[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018E098[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018E0A0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018E0A8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018E0B0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018E0B8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018E0C0[])(void);
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
extern void (*D_8018E0C8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018E0D0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018E0D8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018E0E0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018E0E8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018E0F0[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018E0F8[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018E100[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018E108[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018E110[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018E118[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018E120[])(void);
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
extern void (*D_8018E164[])(void);
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
extern M2C_UNK D_8018E128;
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
extern void (*D_8018E194[])(void);
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
extern void (*D_8018E1D0[])(void);
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
extern void (*D_8018E228[])();
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
extern void (*D_8018E238[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018E240[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018E3A8[])();
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
extern void (*D_8018E3B4[])();
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
extern M2C_UNK D_801DFD98;
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
extern s16 D_801E2570;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern short D_801E25E4;
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
extern s32 D_801E176C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E1794;
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
extern s16 D_801E1750;
extern s32 func_8017A3B0(void);
extern short D_801E178C;
extern short D_801E1788;
extern int func_800D0CA0(int);
extern int func_8001AAA0(s32 arg0);
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

extern s16 D_801E2528;
extern s16 D_801E252A;
extern s16 D_801E2534;

void func_8017AE2C(s32 param_1) {
    s32 pv = param_1;
    s16 *g = &D_801E2528;

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
                    func_8012B744(p, &D_801E2534);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801E2528+0xC == &D_801E2534; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801E2528 + 0xC)) < 0x101) {
                    D_801E2528 = 0;
                    D_801E252A = 0;
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
            func_8012B744((void *)(pv + 4), &D_801E2534);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801E2528 + 0xC)) < 0x101) {
            D_801E2528 = 0;
            D_801E252A = 0;
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
    extern s16 D_801E17CC;
    extern s16 D_801E17CE;
    extern s16 D_801E17D0;
    extern s16 D_801E17C4;
    extern s16 D_801E17C6;
    extern s16 D_801E17C8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801E17CC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801E17CE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801E17D0, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801E17C4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801E17C6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801E17C8, (s32)((s16)param_2));
}



extern s16 D_801E1754;
extern u16 D_801E17D4;
extern u16 D_801E17D6;
extern u16 D_801E17D8;
extern s16 D_801E2570;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    func_8012A418();
    D_801E2570 = 0;
    D_801E1754 = 0;
    D_801E17D4 = D_80126B5E;
    D_801E17D6 = D_80126B62;
    D_801E17D8 = D_80126B66;
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
    extern u8 D_8018E4F0[];
    extern s16 D_801E17CC;
    extern s16 D_801E17C4;
    extern u8 D_8012694C;


    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_8018E4F0[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018E4F0[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E17CC;
        s16 *p78C = &D_801E17C4;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801E2570 = 1;
        D_801E1754 = 0;
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
    extern SV4_8017B368 D_801E1774;
    extern SV4_8017B368 D_801E177C;
    extern s16 D_801E17CC;
    extern s16 D_801E17C4;
    extern u16 D_8018E4F0;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E1774;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E177C;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018E4F0)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018E4F0)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E17CC) = loc0;
    (*(SV4_8017B368 *)&D_801E17C4) = loc1;
    D_801E2570 = 1;
    D_801E1754 = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801E1774;
    extern SV4_8017B368 D_801E177C;
    extern s16 D_801E17CC;
    extern s16 D_801E17C4;
    extern u16 D_8018E4F0;
    extern s16 D_801E1754;
    extern s16 D_801E2570;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E1774;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E177C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018E4F0)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018E4F0)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E17CC) = loc0;
    (*(SV4_8017B368 *)&D_801E17C4) = loc1;
    D_801E2570 = 1;
    D_801E1754 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801E17CC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801E17CC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801E17CC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801E17C4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801E17C4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801E17C4).c;
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
    extern u8 D_8018E4F0[];
    extern s16 D_801E17CC;
    extern s16 D_801E17CE;
    extern s16 D_801E17D0;
    extern s16 D_801E17C4;
    extern s16 D_801E17C6;
    extern s16 D_801E17C8;
    extern u8 D_8012694C[];
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_8018E4F0[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018E4F0[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    *(Blk8_8017B614 *)&D_801E17CC = *(Blk8_8017B614 *)&buf[0];
    *(Blk8_8017B614 *)&D_801E17C4 = *(Blk8_8017B614 *)&buf[8];
    func_8012A018((s32)func_8017BE60, 0);
    D_8012694C[0] = 0;
    D_801E2570 = 1;
    D_801E1754 = 0x1E;
    D_80126990 = ((SV4_8017B368 *)&D_801E17CC)->a;
    D_80126994 = D_801E17CE;
    D_80126998 = D_801E17D0;
    D_80126984 = ((SV4_8017B368 *)&D_801E17C4)->a;
    D_80126988 = D_801E17C6;
    D_8012698C = D_801E17C8;
    func_80129CF8();
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
extern s16 D_801E1754;
extern s16 D_801E17CC;
extern s16 D_801E17CE;
extern s16 D_801E17D0;
extern s16 D_801E17C4;
extern s16 D_801E17C6;
extern s16 D_801E17C8;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801E1754 = 0;
    D_801E17CC = (s16) D_80114F30;
    D_801E17CE = (s16) D_80114F34;
    D_801E17D0 = (s16) D_80114F38;
    D_801E17C4 = (s16) D_80114F24;
    D_801E17C6 = (s16) D_80114F28;
    D_801E17C8 = (s16) D_80114F2C;
}




extern s16 D_801E17E4;
extern s16 D_801E17E6;
extern s16 D_801E17E8;
extern s16 D_801E17EC;
extern s16 D_801E17EE;
extern s16 D_801E17F0;

void func_8017B824(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801151D4;
    D_801E17E4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801E17E6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801E17E8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801E17EC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801E17EE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801E17F0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801E17E4;
extern s16 D_801E17E6;
extern s16 D_801E17E8;
extern s16 D_801E17EC;
extern s16 D_801E17EE;
extern s16 D_801E17F0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801E17E4;
    D_80114F34 = D_801E17E6;
    D_80114F38 = D_801E17E8;
    D_80114F24 = D_801E17EC;
    D_80114F28 = D_801E17EE;
    D_80114F2C = D_801E17F0;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801E17CC), src[8..15] -> (*(S8_8017B8E8 *)&D_801E17C4) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801E17CC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801E17C4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_801E17D4;
extern u16 D_801E17D6;
extern u16 D_801E17D8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801E1754;
extern short D_801E17DC;
extern short D_801E17DE;
extern short D_801E17E0;
extern s16 D_801E17CC;
extern s16 D_801E17CE;
extern s16 D_801E17D0;
extern s16 D_801E17C4;
extern s16 D_801E17C6;
extern s16 D_801E17C8;

void func_8017B940(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801E17D4);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801E17D6);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801E17D8);
    (*(s16 *)&D_801E17DC) = buf[0];
    (*(s16 *)&D_801E17DE) = buf[1];
    (*(s16 *)&D_801E17E0) = buf[2];
    D_801E17CC = D_80114F30 + buf[0];
    D_801E1754 = 0;
    D_801E17CE = D_80114F34 + buf[1];
    D_801E17D0 = D_80114F38 + buf[2];
    D_801E17C4 = D_80114F24 + buf[0];
    D_801E17C6 = D_80114F28 + buf[1];
    D_801E17C8 = D_80114F2C + buf[2];
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

extern SV4 D_801E1774;
extern SV4 D_801E177C;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801E177C) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801E1774 = svec;

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
    D_801E177C = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801E177C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801E1774) = svec;

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
    (*(SV4_8017BB34*)&D_801E177C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801E179C[10])(int);

void func_8017BC38(int param_1)
{
    int i;
    void (**p)(int);

    i = 0;
    p = D_801E179C;
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
extern s16 D_801E1754;
extern s16 D_801E2570;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801E1754 = D_801E1754 + 1;
    if (D_801E1754 >= 0x1F) {
        D_801E2570 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801E1754;
extern s16 D_801E2570;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E1754 = D_801E1754 + 1;
    if (0x18 < D_801E1754) {
        func_8012A4BC();
        D_801E2570 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801E1754;
extern void (*D_801E1798)(void);
extern short D_801E17DC;
extern short D_801E17DE;
extern short D_801E17E0;
extern s16 D_801E2570;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E1754 = D_801E1754 + 1;
    if (D_801E1754 >= 0x19) {
        if (D_801E1798 != 0) {
            (*D_801E1798)();
        } else {
            D_80114F30 = D_80114F30 + D_801E17DC;
            D_80114F34 = D_80114F34 + D_801E17DE;
            D_80114F38 = D_80114F38 + D_801E17E0;
            D_80114F24 = D_80114F24 + D_801E17DC;
            D_80114F28 = D_80114F28 + D_801E17DE;
            D_80114F2C = D_80114F2C + D_801E17E0;
            func_8012A4BC();
        }
        D_801E2570 = 0;
    }
}



extern void (*D_8018E590[])(void);

void func_8017BE60(void *a0) {
    D_8018E590[*(u8 *)((s32)a0 + 0x4)]();
}



extern void (*D_8018E630[])(void);

void func_8017BE9C(void *a0) {
    D_8018E630[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018E638[])(void);

void func_8017BED8(void *a0) {
    D_8018E638[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018E640[])(void);

void func_8017BF14(void *a0) {
    D_8018E640[*(u16 *)((s32)a0 + 0x2)]();
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

    extern u8 D_801E17F8[];
    s32 s3;
    s16 *s0;
    u8 *s2;
    s16 s4;
    Buf8017BF50_8017BF50 buf;

    s3 = a0;
    s0 = *(s16 **)(s3 + 0xDC);
    if (s0 != 0) {
        s2 = D_801E17F8;
        s4 = 0;
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
                *(s32 *)(s2 + 0x14) = *s0++;
                *(s32 *)(s2 + 0x18) = *s0++;
                *(s32 *)(s2 + 0x1C) = *s0++;
                *(u8 **)(v3 + 0x30) = s2;
                s2 += 0x20;
            }
            s4++;
        } while (s4 < 0x10);
    }
    *(u16 *)(s3 + 2) += 1;
}




extern void func_800D23D0(void *a0);

void func_8017C094(void) {

    extern s32 D_801151D4;
    extern s16 D_801E19F8;
    s16 diffs[3];
    s32 *ptr = (s32 *)D_801151D4;

    diffs[0] = (s16)(*(s32 *)((u8 *)ptr + 0x68) - *(s32 *)((u8 *)ptr + 0x5C));
    diffs[1] = (s16)(*(s32 *)((u8 *)ptr + 0x6C) - *(s32 *)((u8 *)ptr + 0x60));
    diffs[2] = (s16)(*(s32 *)((u8 *)ptr + 0x70) - *(s32 *)((u8 *)ptr + 0x64));

    func_800D23D0(diffs);

    D_801E19F8 = (u16)diffs[1];
}



extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017C100(s32 param_1)
{

    extern u8 D_8018E59C[];
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(param_1 + 0x2e) == 0) {
        func_8001CB6C((u8 *)s0, (s32)D_8018E59C, 0x3c0, 0xa0);
    } else {
        func_8001CC3C(s0, (s32)D_8018E59C, 0x3c0, 0xa0);
    }
    *(u8 *)(s0 + 0x27) = 0xfc;
    *(u16 *)(s0 + 0x1a) = 0x3c00;
    *(u16 *)(s0 + 0x18) = 0x3c00;
    *(u32 *)(s0 + 0x4) |= 0x01000000;
    *(u32 *)(s0 + 0x34) = *(u32 *)(param_1 + 0x30);
    (*(u16 *)(param_1 + 0x2))++;
}



extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017C1AC(s32 param_1)
{

    extern s16 D_801E19F8;
    SV4 sv4;
    s32 s0;
    s32 a1;

    s0 = *(s32 *)(param_1 + 0x20);
    sv4.a = -0x20;
    sv4.c = 0;
    sv4.b = D_801E19F8;
    a1 = *(s32 *)(s0 + 0x34);
    RotMatrixYXZ(&sv4, a1);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern void func_8012B260(u8 *a0);


void func_8017C1EC(s32 a0)
{

    extern u8 D_8018AEDC[];
    extern u8 D_8018E618[];
    extern u8 D_8018E620[];
    s32 s0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        ((void (*)(s32))func_8012CAE4)(a0);
        return;
    }

    func_8001C810(s0, (s32)D_8018E618);
    func_8012A828(a0, (s32)D_8018AEDC);

    *(s32 *)(a0 + 0x20) = s0;
    *(s16 *)(s0 + 0x1A) = 0x3C00;
    *(s16 *)(s0 + 0x18) = 0x3C00;
    *(s16 *)(s0 + 0x10) = -0x20;
    *(s16 *)(s0 + 0x12) = -1;
    *(s32 *)(s0 + 0x4) |= 0x8040;
    *(u16 *)(s0 + 0x2C) |= 0x10;

    ((void (*)(s32))func_8012B260)(a0);

    *(s32 *)(a0 + 0x58) = (s32)D_8018E620;
    *(u16 *)(a0 + 0x2) += 1;
}



extern void func_80049CAC(s32 a0, s32 a1);

void func_8017C2B0(s32 a0)
{

    extern u16 D_80126B62;
    extern s16 D_801E19F8;
    s32 unused[2];              /* dead 8-byte local — frame 0x28, not 0x20 */
    s32 s0;

    s0 = *(s32 *)(a0 + 0x20);

    if ((s32)*(s16 *)(a0 + 0xA) - (s32)(*(s16 *)&D_80126B62) >= 0x40) {
        *(s16 *)(a0 + 0x5C) = 0x40;
    } else {
        *(s16 *)(a0 + 0x5C) = 0x800;
    }

    if (*(s16 *)(s0 + 0x12) != D_801E19F8) {
        *(s16 *)(s0 + 0x12) = D_801E19F8;
        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        *(u16 *)(s0 + 0x2C) |= 0x11;
    }
}



extern void (*D_8018E660[])(void);

void func_8017C338(void *a0) {
    D_8018E660[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017C374(s32 param_1) {

    extern u8 D_8018E648;
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

    node = func_800D222C(param_1, &D_8018E648, 0xFD);
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
#include "../shared/ov/func_8017C538.h"



extern void (*D_8018E668[])(void);

void func_8017C5CC(void *a0) {
    D_8018E668[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018E654;

void func_8017C608(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018E654, 0x18);
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
#include "../shared/ov/func_8017C6AC.h"


#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#include "../shared/ov/func_8017C710__t3f3d6beb.h"


// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017D990(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017D5F0(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017D990, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D640(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8017DA18(void *a0);
extern s32 D_80126B9C;
extern u16 D_801270C0;

s32 func_8017D664(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017DA18, 0x1000000);
    D_801270C0 = 2;
    D_80126B9C = D_80126B9C | 0x4000000;
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 0xA;
    return 0;
}



extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);

s32 func_8017D6D4(s32 a0) {

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
void func_8017D784(void) {
    func_800D1EBC();
}



extern void func_800D1E28(void);

s32 func_8017D7A4(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;

    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }

    return 0;
}


    extern void func_800D1E28(void);
    extern void func_8002D4C8(s32, s32);
    extern void func_8001BFD0(void);
    extern s32 func_800291B4(s32);
    extern s32 func_80029524(void);
    extern void func_800D0C48(s32);
    s32 func_8017D7F8(s32 param_1) {
        if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
            ((s32 (*)(void))func_800D1E28)();
            ((s32 (*)(s32, s32))func_8002D4C8)(0x1C, 0);
            ((s32 (*)(void))func_8001BFD0)();
            if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
                ((s32 (*)(s32))func_800D0C48)(1);
            }
            *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
        }
        return 0;
    }



extern void (*D_8018E670[])(void);

void func_8017D88C(void *a0) {
    D_8018E670[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018E678[])(void);

void func_8017D8C8(void *a0) {
    D_8018E678[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018E684[])(void);

void func_8017D904(void *a0) {
    D_8018E684[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018E690[])(void);

void func_8017D940(void *a0) {
    D_8018E690[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_80127050;
    void func_8017D97C(void) {
        D_80127050 = 0x1;
    }



extern void (*D_8018E944[])(void);

void func_8017D990(void *a0) {
    D_8018E944[*(u8 *)((s32)a0 + 0x214)]();
}


void func_8017D9CC(u8 *a0) {
        *(u8 *)(a0 + 0x214) += 1;
    }


extern void func_80175414(s32 _arg0);
    extern void func_8016F0E4(void);
    extern void func_80165770(void);
    void func_8017D9E0(s32 arg0) {
        func_80175414(arg0);
        ((s32 (*)(s32))func_8016F0E4)(arg0);
        ((void (*)(s32))func_80165770)(arg0);
    }



extern void (*D_8018E94C[])(void);

void func_8017DA18(void *a0) {
    D_8018E94C[*(u8 *)((s32)a0 + 0x214)]();
}


void func_8017DA54(void *a0) {
        *(u8 *)((s32)a0 + 0x214) += 1;
    }


extern void func_8016F0E4(void);
    void func_8017DA68(void) {
        ((s32 (*)(void))func_8016F0E4)();
    }



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017DB4C(void *a0);


void func_8017DA88(void) {

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
    func_8012A018((s32)func_8017DB4C, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_8017DB4C(D_80126948);
    func_8012A094((s32)D_80126948);
    func_8017DB4C(D_80126948);
}



extern void (*D_8018E954[])(void);

void func_8017DB4C(void *a0) {
    D_8018E954[*(u8 *)((s32)a0 + 0x4)]();
}


extern void func_8017DD04(s32 param_1);

void func_8017DB88(void *a0) {
    s32 frame_pad[1];
    (void)&frame_pad;
    func_8017DBC4(a0, (u8 *)((s32)a0 + 0xA0));
    func_8017DD04((s32)a0);
}


void func_8017DBBC(s32 *a0) {
    *(s8*)((s32)a0 + 0xA0) = 0;
}




extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_80012A60(s32 a0, s32 a1);

void func_8017DBC4(void *a0, u8 *a1)
{

    extern s32 D_80126B58;
    extern s16 D_8018AECC[];
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
        if ((s16)func_80012A60(*(s16 *)((s32)a0 + 0x1A), D_8018AECC[dir]) < lim) {
            *a1 = dir;
        }
    }

    *(s16 *)((s32)a0 + 0x22) = D_8018AECC[*a1];
}




   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017DD04(s32 param_1)
{
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;

    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    s32 lim;

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


s32 func_8017DEF8(void) {
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    s32 t;
    s32 r;

    if (*(s16 *)&D_80126B5E < 0x230) {
        return 0;
    }
    if (*(s16 *)&D_80126B5E >= 0x371) {
        return 0;
    }
    if (*(s16 *)&D_80126B66 < 0x170) {
        return 0;
    }
    if (*(s16 *)&D_80126B66 >= 0x231) {
        return 0;
    }
    t = func_80029504();
    if (t < 0xD2) {
        r = 0;
    } else if (t < 0xE6) {
        r = 1;
    } else if (t < 0xF0) {
        r = 2;
    } else if (t == 0xFA) {
        r = 6;
    } else if (t < 0x12C) {
        if ((func_80029178(0xF7) & 0xFF) != 0) {
            r = 3;
        } else {
            r = 4;
        }
    } else {
        r = 5;
    }
    if (r != 0) {
        goto one;
    }
    t = func_8012E544(0x17B);
    if (*(u16 *)(t + 2) == 3) {
        goto one;
    }
    return 0;
one:
    return 1;
}


extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);

void func_8017DFE4(void *arg0)
{
    extern short D_801BEA50;
    extern u8 D_801B94EC[];

    *(short *)((char *)arg0 + 0x2) = 2;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E88C((s32)arg0);
    func_8012A828((s32)arg0, (s32)&D_801BEA50);
    func_801843B8((s32)arg0);
    func_801845FC((s32)arg0, (s32)D_801B94EC, 0, 0x60);
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_80183F80(void *a0);
extern void func_801843B8(s32 a0);
extern s32 D_8018E960;

void func_8017E048(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 3;
    func_8012E8E0(s0, (s32)&D_8018E960);
    func_8012E88C(s0);
    func_80183F80((void *)s0);
    func_801843B8(s0);
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern void func_800D0F4C(s32 a0);
extern void func_80178CBC(s32 *a0, s32 a1);
extern s32 func_801789AC(s32 arg0);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_80183F80(void *a0);
extern void func_801843B8(s32 a0);
extern short D_8018EE04;
extern void (*D_8018EE2C)(void *);
extern s32 D_8018E960;

void func_8017E098(void *arg0) {
    s32 stage;
    s32 t;

    t = func_80029504();
    if (t < 0xD2) {
        stage = 0;
    } else if (t < 0xE6) {
        stage = 1;
    } else if (t < 0xF0) {
        stage = 2;
    } else if (t == 0xFA) {
        stage = 6;
    } else if (t < 0x12C) {
        if ((func_80029178(0xF7) & 0xFF) != 0) {
            stage = 3;
        } else {
            stage = 4;
        }
    } else {
        stage = 5;
    }
    if ((u32)(stage - 2) < 2 && *(u16 *)((s32)arg0 + 0x34) == 0) {
        t = func_801789AC(arg0);
        if (t == 1) {
            *(u16 *)((s32)arg0 + 0x34) = 1;
            func_80178CBC((s32 *)arg0, (s32)&D_8018EE04);
            func_80029124(0xF7, 1);
            func_80029124(0xF8, 0);
        } else if (t == 2) {
            *(u16 *)((s32)arg0 + 0x34) = 1;
            func_80178CBC((s32 *)arg0, (s32)&D_8018EE2C);
            func_80029124(0xF7, 0);
            func_80029124(0xF8, 1);
        } else {
            return;
        }
        func_80029514(0xF0);
        func_800D0F4C(0x56);
    } else if (((s32 (*)(void *))func_80178970)(arg0) != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(u16 *)((s32)arg0 + 2) = 3;
        func_8012E8E0((s32)arg0, (s32)&D_8018E960);
        func_8012E88C((s32)arg0);
        func_80183F80(arg0);
        func_801843B8((s32)arg0);
    }
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);
extern void func_8012CAE4(void *a0);
extern s32 func_80183EE4(void *a0, void *a1);
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_80183F80(void *a0);
extern void func_801843B8(s32 a0);
extern void func_801843E0(void *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);

void func_8017E228(void *a0) {
    extern short D_8018E958;
    extern s32 D_8018E960;
    extern void (*D_8018E968)(void);
    extern s32 func_8017E5C4(s32 arg);

    void *s0 = a0;
    s32 v0, v1;

    v1 = func_80029504();
    if (v1 < 0xD2) {
        v1 = 0;
    } else if (v1 < 0xE6) {
        v1 = 1;
    } else if (v1 < 0xF0) {
        v1 = 2;
    } else if (v1 == 0xFA) {
        v1 = 6;
    } else if (v1 < 300) {
        if ((u8)func_80029178(0xF7) != 0) {
            v1 = 3;
        } else {
            v1 = 4;
        }
    } else {
        v1 = 5;
    }

    if (v1 == 5) {
        func_8012CAE4(s0);
        return;
    }
    if (func_80183EE4(s0, &D_8018E968) == 0) {
        return;
    }
    if (func_801842F8(9, 4, 0x12, 0) != 0) {
        *(s16 *)((char *)s0 + 0x2) = 3;
        func_8012E8E0((s32)s0, (s32)&D_8018E960);
        func_8012E88C((s32)s0);
        func_80183F80(s0);
        func_801843B8((s32)s0);
    } else {
        *(s16 *)((char *)s0 + 0x2) = 1;
        func_801843E0(s0, (s32)&D_8018E958);
    }
    {
        void *pv0;
        s32 pv1;
        pv0 = *(void **)((char *)s0 + 0x68);
        pv1 = 0x7FFF;
        *(s16 *)((char *)pv0 + 0xC) = (s16)pv1;
    }
    v0 = func_801788B8((s32)s0, (s32)func_8017E5C4);
    *(s32 *)((char *)s0 + 0xD4) = v0;
    func_8012E8E0(v0, (s32)&D_8018E958);
}



extern void (*D_8018F01C[])(void);

void func_8017E380(void *a0) {
    D_8018F01C[*(u16 *)((s32)a0 + 0x2)]();
}


extern int func_800D0F8C(int a0);
extern s32 func_800D0EC4(void);
extern void func_800D0F0C(s32, s32);

void func_8017E3BC(s32 a0)
{
    if (func_800D0F8C(a0 & 0xFF) == 0) {
        s32 ret;
        ret = func_800D0EC4();
        if (ret != 0) {
            func_800D0F0C(ret, a0);
        }
    }
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_80183F80(void *a0);
extern void func_801843B8(s32 a0);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80178CBC(s32 *a0, s32 a1);
extern s32 D_8018E960;
extern void (*D_8018EFFC[])(void *);

void func_8017E408(s32 a0) {
    s32 var;

    *(s16 *)(a0 + 2) = 6;
    *(s16 *)(a0 + 0x34) = 0;
    func_8012E8E0(a0, (s32)&D_8018E960);
    func_8012E88C(a0);
    func_80183F80((void *)a0);
    func_801843B8(a0);
    var = func_80029504();
    if (var < 0xD2) {
        var = 0;
    } else if (var < 0xE6) {
        var = 1;
    } else if (var < 0xF0) {
        var = 2;
    } else if (var == 0xFA) {
        var = 6;
    } else if (var < 0x12C) {
        if ((func_80029178(0xF7) & 0xFF) != 0) {
            var = 3;
        } else {
            var = 4;
        }
    } else {
        var = 5;
    }
    func_80178CBC((s32 *)a0, (s32)D_8018EFFC[var]);
}


void func_8017E4E4(void) {
    func_80029514(0xD2);
    func_80029124(0x114, 1);
}


extern s32 func_8012E544(s32 arg);
    void func_8017E510(void) {
        s32 r = func_8012E544(0x17B);
        *(s16 *)(r + 0xFC) = 0x2;
    }



extern s32 func_8012E544(s32 arg);
    void func_8017E534(void) {
        s32 r = func_8012E544(0x17B);
        *(s16 *)(r + 0xFC) = 0x1;
    }



extern s32 func_8012E544(s32 arg);
    void func_8017E558(void) {
        s32 r = func_8012E544(0x17B);
        *(s16 *)(r + 0xFC) = 0x4;
    }



extern s32 func_8012E544(s32 arg);
    void func_8017E57C(void) {
        s32 r = func_8012E544(0x17B);
        *(s16 *)(r + 0xFC) = 0x3;
    }



extern s32 func_8012E544(s32 arg);
    void func_8017E5A0(void) {
        s32 r = func_8012E544(0x17B);
        *(s16 *)(r + 0xFC) = 0x5;
    }


extern s32 func_80178BF8();
extern void func_80172710(void);

s32 aF8017E5C4(s32 param_1) __asm__("func_8017E5C4");

s32 aF8017E5C4(s32 param_1)
{
    register s32 obj __asm__("$16") = param_1;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus7)

    if (*(u16 *)(*(s32 *)((char *)obj + 0x64) + 0x2) != 3) {
        return 0;
    }
    if (func_8017DEF8() != 0) {
        *(u16 *)(*(s32 *)((char *)obj + 0x64) + 0x2) = 5;
        func_80178BF8();
        return (s32)func_80172710;
    }
    return 0;
}


extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017DFE4(void *arg0);

extern u8 D_8018F018;
extern u8 D_8018F019;
extern u8 D_8018F01A;
extern u8 D_8018F01B;

void func_8017E62C(void *arg0) {
    u8 a = D_8018F018;
    *(s32 *)(*(s32 *)((char *)arg0 + 0xCC) + 0xB0) = 2;
    if (func_801842F8(a, D_8018F019, D_8018F01A, D_8018F01B) != 0) {
        func_8017DFE4(arg0);
    }
}


extern s32 func_801846CC(s32 a0);
extern s32 func_80185308(s32 arg0);
extern u8 D_801B94F8[];
extern void func_8017E048();
extern void func_801845FC(s32, s32, s32, s32);

void func_8017E694(void *a0)
{
    u16 v1;

    v1 = *(u16 *)((s32)a0 + 0x34);

    if (v1 == 0) {
        goto case0;
    }

    if (v1 == 1) {
        goto case1;
    }

    return;

case0:
    if (func_80185308(0x5) == 0) {
        return;
    }
    if (func_801846CC((s32)a0) == 0) {
        return;
    }
    ((void (*)(void *, void *, s32, s32))func_801845FC)(a0, D_801B94F8, 0, 0x60);
    *(s16 *)((s32)a0 + 0x34) = 1;
    return;

case1:
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (func_801846CC((s32)a0) != 0) {
        func_8017E048((s32)a0);
    }
}


extern s16 D_8018E958;
extern s32 func_801846CC(s32 a0);
extern s32 func_80185308(s32 a0);
extern u8 D_801B94EC[];
extern void func_801843E0(void*, s32);
extern void func_801845FC(s32, s32, s32, s32);

void func_8017E738(void *a0) {
    s32 v0;
    u16 v1;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
        case 0:
            v0 = ((s32 (*)(void *))func_801846CC)(a0);
            if (v0 != 0) {
                ((void (*)(void *, void *, s32, s32))func_801845FC)(a0, D_801B94EC, 1, 0x60);
                *(u16 *)((u8 *)a0 + 0x34) = 1;
            }
            break;
        case 1:
            v0 = func_80185308(0x5);
            if (v0 != 0) {
                v0 = ((s32 (*)(void *))func_801846CC)(a0);
                if (v0 != 0) {
                    *(u16 *)((u8 *)a0 + 0x2) = 1;
                    ((void (*)(void *, void *))func_801843E0)(a0, ((u8 *)&D_8018E958));
                }
            }
            break;
    }
}


extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);

extern u8 D_8018F018;
extern u8 D_8018F019;
extern u8 D_8018F01A;
extern u8 D_8018F01B;
extern short D_801BEA50;
extern u8 D_801B94F8[];

void func_8017E7E0(void *arg0) {
    u8 a = D_8018F018;
    *(s32 *)(*(s32 *)((char *)arg0 + 0xCC) + 0xB0) = 2;
    if (func_801842F8(a, D_8018F019, D_8018F01A, D_8018F01B) == 0) {
        *(s16 *)((char *)arg0 + 2) = 4;
        func_8012E88C((s32)arg0);
        func_8012A828((s32)arg0, (s32)&D_801BEA50);
        func_801843B8((s32)arg0);
        *(s16 *)((char *)arg0 + 0x34) = 0;
        func_801845FC((s32)arg0, (s32)D_801B94F8, 1, 0x60);
    }
}



extern void func_801843E0(void*, s32);
    extern short D_8018F038;
    void func_8017E880(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018F038);
    }



extern void (*D_8018F1C8[])(void);

void func_8017E8AC(void *a0) {
    D_8018F1C8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32*, s32);
    extern short D_8018F190;
    void func_8017E8E8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_8018F190);
    }


extern void func_80029514(int);
void func_8017E914(void) {
    func_80029514(0xdc);
}


void func_8017E934(void) {
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32 arg);
    extern u8 D_8018F054[];
    extern u8 D_8018F080[];
    extern u8 D_8018F0F8[];
    extern u8 D_8018F128[];
    extern u8 D_8018F140[];
    extern u8 D_8018F168[];
    extern u8 D_8018F180[];
    extern s32 D_8018F1B4;

    s32 *p = &D_8018F1B4;
    s32 v1 = func_80029504();

    if (v1 < 0xD2) {
        *p = (s32)&D_8018F054[0];
    } else if (v1 < 0xDC) {
        *p = (s32)&D_8018F080[0];
    } else if (v1 < 0xE6) {
        *p = (s32)&D_8018F0F8[0];
    } else if (v1 < 0xF0) {
        *p = (s32)&D_8018F128[0];
    } else if (v1 < 0x12C) {
        *p = (s32)&D_8018F140[0];
    } else if (func_80029178(0xF9) & 0xFF) {
        *p = (s32)&D_8018F168[0];
    } else {
        *p = (s32)&D_8018F180[0];
    }
}



extern s32 func_801842D4(s32 arg0, s32 arg1);
extern void func_8017E880(void*);

void func_8017EA10(s32 *a0) {
    *(s32 *)((s32)a0[0x33] + 0xB0) = 2;
    if (func_801842D4(11, 23) != 0) {
        return;
    }
    ((void (*)(s32 *))func_8017E880)(a0);
}


void func_8017EA5C(void *arg0) {
    extern s32 func_801842D4(s32 a0, s32 a1);
    extern void func_801843E0(void*, s32);
    extern short D_8018F038;
    *(s32 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xB0) = 2;
    if (func_801842D4(11, 23) != 0) {
        *(short *)((char *)arg0 + 2) = 1;
        func_801843E0(arg0, &D_8018F038);
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_801843E0(void*, s32);

void func_8017EAB4(void * arg0) {

    extern short D_8018F038;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018F038);
    }
}


extern s32 func_80183EE4(void *a0, void *a1);
extern s32 func_801842D4(s32 a0, s32 a1);
extern void func_801843E0(void *a0, s32 a1);
extern s32 func_801788B8(s32 a0, s32 a1);

void func_8017EB04(void *a0) {
    extern void func_8017EB84(void *a0);
    extern short D_8018F038;
    extern u16 D_8018F040[];
    void *s0 = a0;

    if (func_80183EE4(a0, D_8018F040) == 0) {
        return;
    }
    if (func_801842D4(0xB, 0x17) != 0) {
        *(s16 *)((char *)s0 + 2) = 1;
    } else {
        *(s16 *)((char *)s0 + 2) = 2;
    }
    func_801843E0(s0, (s32)&D_8018F038);
    *(s16 *)((char *)*(void **)((char *)s0 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)((char *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)func_8017EB84);
}




extern void func_80172710(void);
extern s32 func_80184004(void);
extern s32 func_80178BF8();

s32 aF80186828(void *a0) __asm__("func_8017EB84");

s32 aF80186828(void *a0)
{
    void *s0 = a0;
    void **v0p;
    u16 v1;

    v0p = (void **)(s0 + 0x64);
    v1 = *(u16 *)(*v0p + 0x2);
    if (v1 != 0x2) {
        return 0;
    }

    if (func_80184004() != 0) {
        *(u16 *)(*v0p + 0x2) = 0x3;
        func_80178BF8();
        return (s32)func_80172710;
    }

    return 0;
}


extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801845FC(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017EBEC(void *a0) {

    extern short D_801D4814;
    extern short D_801B95A4;
    *(short *)((char *)a0 + 0x2) = 2;
    *(u16 *)((char *)a0 + 0x34) = 0;
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D4814);
    func_801843B8((s32)a0);
    func_801845FC((s32)a0, (s32)&D_801B95A4, 0, 0x60);
}


extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_8017EC50(s32* _arg0)
{
    s16 v;

    v = D_80126B5E;
    if (v < -0x80) {
        return;
    }
    if (v >= 0x13) {
        return;
    }
    v = D_80126B66;
    if (v < -0x100) {
        return;
    }
    if (v >= -0x3f) {
        return;
    }
    D_80126B5E = 0x12;
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);

void func_8017ECA0(void *arg0) {
    extern s32 D_8018F1E4;
    extern s32 D_801D414C;
    s32 s0;

    s0 = 3;
    *(s16 *)((char *)arg0 + 0x2) = s0;
    func_8012E8E0((s32)arg0, (s32)&D_8018F1E4);
    func_8012E88C((s32)arg0);
    func_8012A828((s32)arg0, (s32)&D_801D414C);
    *(s16 *)((char *)arg0 + 0x84) = s0;
}


extern void func_801843E0(void *a0, s32 a1);
    extern short D_8018F1DC;
    void func_8017ECFC(s16 *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        func_801843E0(a0, &D_8018F1DC);
    }



extern void (*D_8018F330[])(void);

void func_8017ED28(void *a0) {
    D_8018F330[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32*, s32);
    extern short D_8018F210;
    void func_8017ED64(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_8018F210);
    }


extern u16 D_800B99DA;
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017EBEC(void *a0);

void func_8017ED90(void *arg0)
{
    if ((D_800B99DA & 3) == 0 && func_801842F8(0x11, 0x23, 0x17, 0) != 0) {
        func_8017EBEC(arg0);
    }
}


extern s32 func_801846CC(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);
extern void func_8017EC50(s32 *a0);
extern s32 func_80185308(s32 arg0);
extern void func_8017ECA0(void *arg0);
extern u8 D_80078EBA;
extern s32 D_801B95B0;

void func_8017EDE8(void *a0)
{
    u16 v1;

    v1 = *(u16 *)((s32)a0 + 0x34);
    switch (v1) {
    case 0:
        if (D_80078EBA == 3) {
            func_8017EC50((s32 *)a0);
            if (func_80185308(8) == 0) {
                return;
            }
            if (func_801846CC((s32)a0) == 0) {
                return;
            }
            {
                /* $v0 pin (cookbook §72/§137): local-alloc gives the shorter-lived
                 * `2` quantity $v0 and the 0xCC pointer $v1; the target has them the
                 * other way round. The swap is invariant under every source
                 * permutation tried (statement order, switch vs goto, hoisted
                 * pointer, named constant) -- per §137 that invariance says the
                 * lever is not in the source order, so the pointer is pinned.
                 * The range is lw..sw inside this block and crosses no call, so
                 * the §74 caller-saved hazard does not apply. */
                register s32 *p __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
                p = *(s32 **)((s32)a0 + 0xCC);
                *(s32 *)((s32)p + 0xB0) = 2;
            }
            func_801845FC((s32)a0, (s32)&D_801B95B0, 0, 0x60);
        } else {
            if (func_801846CC((s32)a0) == 0) {
                return;
            }
            func_801845FC((s32)a0, (s32)&D_801B95B0, 0, 0x60);
        }
        *(u16 *)((s32)a0 + 0x34) = 1;
        break;
    case 1:
        if (func_801846CC((s32)a0) != 0) {
            func_8017ECA0(a0);
        }
        break;
    }
}


extern s32 func_801846CC(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);
extern void func_8017EC50(s32 *a0);
extern s32 func_80185308(s32 arg0);
extern void func_801843E0(void *a0, s32 a1);
extern s16 D_801B95A4;
extern s16 D_8018F1DC;

void func_8017EED4(void *a0) {
    u16 v1;
    s32 v0;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
        case 0:
            v0 = func_801846CC((s32)a0);
            if (v0 != 0) {
                func_801845FC((s32)a0, (s32)&D_801B95A4, 1, 0x60);
                *(u16 *)((u8 *)a0 + 0x34) = 1;
            }
            break;
        case 1:
            func_8017EC50((s32 *)a0);
            v0 = func_80185308(8);
            if (v0 != 0) {
                v0 = func_801846CC((s32)a0);
                if (v0 != 0) {
                    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
                    *(u16 *)((u8 *)a0 + 2) = 1;
                    func_801843E0(a0, (s32)&D_8018F1DC);
                }
            }
            break;
    }
}


extern void func_8012E688(void *, s32, s32);
extern s32 func_801842F8(u8, u8, u8, u8);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32);
extern void func_801845FC(s32, s32, s32, s32);
extern u16 D_800B99DA;
extern s32 D_801D4814;
extern s32 D_801B95B0;

void func_8017EF90(void *a0) {
    u16 counter = *(u16 *)((u8 *)a0 + 0x84);
    counter++;
    *(u16 *)((u8 *)a0 + 0x84) = counter;

    if ((s16)counter >= 0x10) {
        func_8012E688(a0, 0x6B5, 0);
        *(u16 *)((u8 *)a0 + 0x84) = 0;
    }

    if ((D_800B99DA & 0x3) == 0) {
        if (func_801842F8(0x11, 0x23, 0x17, 0) == 0) {
            *(u16 *)((u8 *)a0 + 0x2) = 0x6;
            func_8012E88C((s32)a0);
            func_8012A828((s32)a0, (s32)&D_801D4814);
            func_801843B8((s32)a0);
            *(u16 *)((u8 *)a0 + 0x34) = 0;
            func_801845FC((s32)a0, (s32)&D_801B95B0, 1, 0x60);
        }
    }
}


extern s32 func_80178970(void);
extern void func_80178D18(void);
extern void func_80029514(s32);
extern void func_8017ECFC(s16 *);

void func_8017F054(void * param_1) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)param_1);
        func_80029514(0x136);
        func_8017ECFC((s16 *)param_1);
    }
}


void func_8017F09C(void) {
}

extern s32 func_80183EE4(void *a0, void *a1);
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017F1A0(void *a0);

void func_8017F0A4(void *arg0) {

    extern s32 D_8018F1EC;
    extern s32 D_8018F1E4;
    extern s32 D_801D414C;
    extern short D_8018F1DC;

    s32 s0;
    s32 t;

    if ((u32)(func_80029504() - 300) >= 10) {
        func_8012CAE4(arg0);
        return;
    }

    if (func_80183EE4(arg0, &D_8018F1EC) == 0) {
        return;
    }

    if (func_801842F8(0x12, 0, 0x17, 0) != 0) {
        s0 = 3;
        *(s16 *)((char *)arg0 + 0x2) = s0;
        func_8012E8E0((s32)arg0, (s32)&D_8018F1E4);
        func_8012E88C((s32)arg0);
        func_8012A828((s32)arg0, (s32)&D_801D414C);
        *(s16 *)((char *)arg0 + 0x84) = s0;
    } else {
        *(s16 *)((char *)arg0 + 0x2) = 1;
        func_801843E0(arg0, &D_8018F1DC);
    }

    *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    t = func_801788B8((s32)arg0, (s32)func_8017F1A0);
    *(s32 *)((char *)arg0 + 0xD4) = t;
    func_8012E8E0(t, (s32)&D_8018F1DC);
}

extern s32 func_80029504(void);
extern void func_8012CAE4(void *a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_801843E0(void*, s32);


extern s32 func_80178BF8();
extern void func_80172710(void);

s32 aF8017F1A0(void *param_1) __asm__("func_8017F1A0");

s32 aF8017F1A0(void *param_1)
{
    extern void func_8012BD14(s32 a0);
    s32 ptr;

    ptr = *(s32 *)((char *)param_1 + 0x64);
    if (*(u16 *)((char *)ptr + 0x2) != 3) {
        goto ret0;
    }
    if (((s32 (*)(s32))func_8012BD14)(ptr) < 0x4000) {
        goto succ;
    }
ret0:
    return 0;
succ:
    *(u16 *)(*(s32 *)((char *)param_1 + 0x64) + 0x2) = 4;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_8018F46C[])(void);

void func_8017F20C(void *a0) {
    D_8018F46C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80029514(int);
void func_8017F248(void) {
    func_80029514(0x186);
}




extern s32 D_80126B9C;
extern s16 D_8018F37C[];
extern s32 func_80178B18(s32 param_1, s32 param_2);

void func_8017F268(void *a0) {
    if ((D_80126B9C & 0x8000000) != 0) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        func_80178B18((s32)a0, (s32)&D_8018F37C);
    }
}


extern s32 func_80178970(void);
extern void func_80178D18(void);
extern void func_8012C218(void *a0);

void func_8017F2A8(void *param_1) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)param_1);
        func_8012C218(param_1);
    }
}


extern s32 func_80029504(void);
extern void func_8012CAE4(void *a0);
extern s32 func_80183EE4(void *a0, void *a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);

void func_8017F2E8(void *arg0) {

    extern u8 D_8018F358[];
    extern u8 D_8018F350;
    extern u8 D_801BF488;

    if ((u32)(func_80029504() - 0x181) >= 5) {
        func_8012CAE4(arg0);
        return;
    }
    if (func_80183EE4(arg0, &D_8018F358) == 0) {
        return;
    }
    *(short *)(*(int *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    *(short *)((char *)arg0 + 2) = 1;
    func_8012E8E0((s32)arg0, (s32)&D_8018F350);
    func_8012E88C((s32)arg0);
    func_8012A828((s32)arg0, (s32)&D_801BF488);
}


#include "common.h"

void func_8017F380(s32 arg0) {
    typedef struct { short vx, vy, vz, pad; } SVECTOR_8017F40C;
    extern SVECTOR_8017F40C D_8018F784[4];
    extern void func_80029514(s32);

    *(s32 *)(arg0 + 0x58) = (s32)&D_8018F784 | 0x40000000;
    *(u16 *)(arg0 + 0x5C) = 0xC00;
    func_80029514(0x19A);
}


extern s32 D_8018F478;
extern short D_8018F498;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_8017F3BC(s32 a0) {
    *(s16 *)(a0 + 2) = 2;
    func_8012E8E0(a0, (s32)&(*(s32 *)&D_8018F498));
    func_8012E88C(a0);
    func_8012A828(a0, (s32)&D_8018F478);
}



extern void func_801843E0(void*, s32);
    extern short D_8018F498;
    void func_8017F40C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 6;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018F498);
    }


extern s32 func_80029504(void);
extern void func_8012CAE4(void *a0);
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_801843E0(void *a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_801788B8(s32 a0, s32 a1);
extern void func_8017FA98(void *a0);
extern s32 D_801E1A1C;
extern s32 D_801CA44C;
extern short D_8018F498;
extern s32 D_8018F478;
extern s32 D_8018F794;
extern s32 D_8018FA68;
extern s32 D_801BF388;

void func_8017F438(void *arg0) {
    s32 s0 = (s32)arg0;
    s32 s1;
    s32 s2;
    s32 v0;

    s1 = func_80029504();
    if (s1 < 0x181 || (u32)(s1 - 0x1AE) < 0x28 || s1 >= 0x1E0) {
        func_8012CAE4(s0);
        return;
    }
    D_801E1A1C = 0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
        return;
    }
    func_8001C214(v0, (s32)&D_801CA44C);
    s2 = (s32)&(*(s32 *)&D_8018F498);
    *(s16 *)(*(s32 *)(s0 + 0x68) + 0xC) = 0x7FFF;
    func_8012E8E0(s0, s2);
    if ((u32)(s1 - 0x181) < 5) {
        *(s16 *)(s0 + 0x2) = 1;
        func_801843E0(s0, s2);
        *(s32 *)(s0 + 0xD4) = func_801788B8(s0, (s32)func_8017FA98);
    } else if ((u32)(s1 - 0x186) < 0x14) {
        *(s16 *)(s0 + 0x2) = 2;
        func_8012E8E0(s0, s2);
        func_8012E88C(s0);
        func_8012A828(s0, (s32)&D_8018F478);
        *(s32 *)(s0 + 0xD4) = func_801788B8(s0, (s32)func_8017FA98);
    } else if ((u32)(s1 - 0x19A) < 0x14) {
        *(s16 *)(s0 + 0x2) = 5;
        func_8012E8E0(s0, (s32)&D_8018F794);
        func_8012E88C(s0);
        func_8012A828(s0, (s32)&D_801BF388);
        *(s16 *)(s0 + 0x34) = 0;
    } else if ((u32)(s1 - 0x1D6) < 0xA) {
        *(s16 *)(s0 + 0x2) = 7;
        func_8012E8E0(s0, (s32)&D_8018FA68);
        func_8012E88C(s0);
        func_8012A828(s0, (s32)&D_801BF388);
        *(s16 *)(s0 + 0x34) = 0;
    }
    *(s16 *)(*(s32 *)(s0 + 0x68) + 0xC) = 0x7FFF;
}


void func_8017F5CC(void *a0) {
    extern s32 D_801E1A1C;
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void (*D_8018FB8C[])(void *);

    if (D_801E1A1C != 0) {
        D_801E1A1C--;
        if (D_801E1A1C < 1) {
            func_8002D4C8(0xD, 0x6C0);
        }
    }
    D_8018FB8C[*(u16 *)((s32)a0 + 2)](a0);
}


extern void (*D_8018FBAC)(void);
extern void (*D_8018FBB8)(void);
extern s32 D_8018FBC4;
extern s16 D_8018FBC8;
extern s16 D_8018FBC2;
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012931C(void *a0);
extern void func_801292C8(u8 *a0);

void func_8017F63C(void *s1) {
    s32 base;
    s32 t;
    s32 x;
    s32 y;
    s32 node;
    s32 delta;
    s32 h;
    s32 f;
    s32 g;
    s32 e0;
    s32 e1;
    s32 cnt;

    if (*(u16 *)((s32)s1 + 2) == 0) {
        *(s32 *)(*(s32 *)((s32)s1 + 0x20) + 0x20) = (s32)&D_8018FBAC;
        do { t = *(s32 *)((s32)s1 + 0x20); } while (0);
        base = (s32)s1 + 0x24;
        *(s32 *)(t + 4) |= 0x50000000;
        x = *(s32 *)((s32)s1 + 0x20);
        *(u8 *)(x + 0x27) = 0x65;
        y = *(s32 *)((s32)s1 + 0x20);
        *(u16 *)(y + 0x1A) = 0;
        *(u16 *)(y + 0x18) = 0;
        do { func_80128EA8(*(s32 *)((s32)s1 + 0x20), base, (s32)&D_8018FBB8); } while (0);
        node = *(s32 *)((s32)s1 + 0x20);
        delta = D_8018FBC4;
        h = *(u16 *)((s32)s1 + 2);
        *(s32 *)((s32)s1 + 0x2C) = 0x8000000;
        f = *(s32 *)((s32)s1 + 0x14);
        *(s32 *)((s32)s1 + 0x1C) = 0;
        h = h + 1;
        g = f + delta;
        *(s32 *)((s32)s1 + 0x14) = g;
        *(u16 *)((s32)s1 + 2) = h;
        func_80128ED8(node, (s32 *)base);
    } else {
        e1 = D_8018FBC8;
        e0 = *(s32 *)((s32)s1 + 0x2C);
        e0 = e0 + e1;
        *(s32 *)((s32)s1 + 0x2C) = e0;
        e1 = *(s32 *)((s32)s1 + 0x20);
        *(u16 *)(e1 + 0x1A) = e0;
        *(u16 *)(e1 + 0x18) = e0;
        func_8012931C(s1);
        cnt = *(s32 *)((s32)s1 + 0x1C) + 1;
        *(s32 *)((s32)s1 + 0x1C) = cnt;
        if (D_8018FBC2 < cnt) {
            func_801292C8((u8 *)s1);
        }
    }
}


#include "common.h"

void func_8017F768(void) {
    extern s16 D_8018FBD4[];
    extern s32 D_8018FBDC;
    extern s32 D_8018FBCC;
    extern s16 D_8018FBC0;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern u8 *func_801290DC(s32 a0, u8 *a1);
    /* §272/index-L15: this TU declares `extern void func_8017F768(void);` (line 5667) and calls
     * it with no args, so the definition MUST keep the (void) signature; the real incoming
     * argument is read off $a0 with a register pin (§42/§73 PARAMS axis) and copied into an
     * ordinary local so it lands in $s1 across the two calls. */
    s32 a0v;
    s32 param_1 = a0v;
    struct { s16 a, b, c, d; } buf;
    s16 *p;
    s32 term;

    D_8018FBDC = D_8018FBDC + 1;
    if (D_8018FBD4[0] != -1) {
        term = -1;
        p = D_8018FBD4;
        do {
            if (*p == D_8018FBDC) {
                func_8012F214(param_1, (s32)&D_8018FBCC, (s32)&buf);
                func_801290DC(0x47, (u8 *)&buf);
            }
            p++;
        } while (*p != term);
    }
    if (D_8018FBC0 < D_8018FBDC) {
        D_8018FBDC = 0;
    }
}


void func_8017F840(void) {
}


extern void (*D_8018FBE4[])(void);

void func_8017F848(void *a0) {
    D_8018FBE4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

void func_8017F884(int param_1)
{
    extern s32 D_801BB9B0;
    extern s32 D_8018FBE0;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, (s32)&D_801BB9B0);
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = (short)D_8018FBE0;
        *(short *)(*(int *)(param_1 + 0x68) + 0xC) = 0x7FFF;
        *(int *)(param_1 + 0x1C) = 2;
        *(short *)(param_1 + 0x34) = 0;
        *(u16 *)(param_1 + 0x2) += 1;
    }
}


extern s16 func_80174774(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012C218(void *a0);

void func_8017F90C(void *a0) {
    u16 v1;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
    case 0:
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((u8 *)a0 + 0x34) = *(u16 *)((u8 *)a0 + 0x34) + 1;
        }
        break;
    case 1:
        /* The TU declares func_80174774 as `s16` (jr_8017AE2C.c:2385); an s16
         * result would truncate through `sll $v0,$v0,0x10` before the branch,
         * which the target does not have. Cast the CALL SITE (cookbook §22),
         * leaving the canonical decl alone — gcc-2.7.2 folds the cast to a
         * direct `jal`. */
        if (((s32 (*)(void))func_80174774)() != 0) {
            *(s32 *)((u8 *)a0 + 0x1C) = 0x10;
            *(u16 *)((u8 *)a0 + 0x34) = *(u16 *)((u8 *)a0 + 0x34) + 1;
            func_8012E8A8((u8 *)a0);
        }
        break;
    case 2:
        if (func_8012BEE8((s32)a0) != 0) {
            func_8012C218(a0);
        }
        break;
    }
}


#include "common.h"

extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern s32 D_801E256C;
extern void *D_8018F5AC[];
extern void *D_8018F664[];

void func_8017F9D8(void) {
    if (func_801842F8(2, 0, 2, 0x2D) != 0) {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_8018F664;
    } else {
        *(s32 *)(*(s32 *)&D_801E256C + 4) = (s32)D_8018F5AC;
    }
}


extern void func_80029514(int);
void func_8017FA34(void) {
    func_80029514(0x190);
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801E1A1C;

void func_8017FA54(void) {
    func_8002D4C8(0x6C0, 0);
    D_801E1A1C = 0x96;
}


extern s32 D_801E1A18;

void func_8017FA84(void) {
    D_801E1A18 = 1;
}


extern void func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void *aF8017FA98(void *arg0) __asm__("func_8017FA98");
void *aF8017FA98(void *arg0) {
    if (*(u16 *)(*(s32 *)((char *)arg0 + 0x64) + 2) != 2) {
        goto ret0;
    }
    if (((s32 (*)(void *))func_8012BD14)(arg0) < 0x4000) {
        goto succ;
    }
ret0:
    return 0;
succ:
    *(u16 *)(*(s32 *)((char *)arg0 + 0x64) + 2) = 3;
    func_80178BF8();
    return (void *)func_80172710;
}


void func_8017FB04(s32 arg0)
{
    extern u16 D_800B99DA;
    extern s32 func_80029504(void);
    extern void func_8017F3BC(s32 a0);

    if ((D_800B99DA & 3) != 0) {
        return;
    }
    if (func_80029504() < 0x182) {
        return;
    }
    func_8017F3BC(arg0);
}


extern void func_8017F768(void);
void func_8017FB54(void) {
    func_8017F768();
}


void func_8017FB74(void *arg0) {
    extern short D_8018F498;
    extern s32 D_8018F478;
    extern s32 D_801E1A18;
    extern s32 D_8018F60C;
    extern s32 D_8018F5F4;
    extern s32 D_8018F5C4;
    extern s32 D_8018F534;
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern s32 func_80029504(void);
    extern void func_80178CBC(s32*, s32);

    *(short *)((char *)arg0 + 0x2) = 4;
    func_8012E8E0((s32)arg0, (s32)&D_8018F498);
    func_8012E88C((s32)arg0);
    func_8012A828((s32)arg0, (s32)&D_8018F478);
    D_801E1A18 = 0;
    if (func_80029504() < 0x190) {
        func_80178CBC((s32 *)arg0, (s32)&D_8018F534);
    } else {
        if (func_801842F8(2, 0, 2, 0x2D) != 0) {
            func_80178CBC((s32 *)arg0, (s32)&D_8018F60C);
        } else if (func_801842F8(2, 0, 0x14, 0) != 0) {
            func_80178CBC((s32 *)arg0, (s32)&D_8018F5F4);
        } else {
            func_80178CBC((s32 *)arg0, (s32)&D_8018F5C4);
        }
    }
}


extern s32 D_801E1A18;
extern u8 D_8018F4B8[];
extern s32 func_8017B368();
extern s32 func_80178970(void);
extern void func_80178D18(void);
extern s16 D_8018F498;
extern s32 D_8018F478;
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);

void func_8017FC58(void *arg0) {
    if (D_801E1A18 == 1) {
        ((void (*)(s32, s32))func_8017B368)((s32)arg0, (s32)D_8018F4B8);
    }
    if (((s32 (*)(void *))func_80178970)(arg0) != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(s16 *)((s32)arg0 + 2) = 2;
        func_8012E8E0((s32)arg0, (s32)&D_8018F498);
        func_8012E88C((s32)arg0);
        func_8012A828((s32)arg0, (s32)&D_8018F478);
    }
}


extern void func_801851D8(s32 arg);
    void func_8017FCE4(void) {
        func_801851D8(0x7);
    }


extern void func_80185238(s32 arg);
    void func_8017FD04(void) {
        func_80185238(0x7);
    }


extern s32 func_8012E57C(s32 arg0, s32 arg1);
    void func_8017FD24(void) {
        s32 r;
        s32 p;
        r = func_8012E57C(0x61, 0x7);
        if (r != 0) {
            *(s16 *)(r + 0xE8) = 1;
        }
    }


s32 func_8017FD58(void) {
    extern s32 D_801E2460;
    return (u32)(D_801E2460 ^ 1) != 0;
}


#include "common.h"

void func_8017FD70(s32 arg0) {
    extern s32 D_80126B9C;
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_80029514(s32);
    extern s16 D_8018F7C8;
    extern int func_80178970();
    extern void func_80178D18();
    extern void func_8017F40C(void *arg0);
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (D_80126B9C & 0x8000000) {
            *(u16 *)(arg0 + 0x34) = 1;
            func_80178B18(arg0, &D_8018F7C8);
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)(arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            func_80029514(0x1AE);
            func_8017F40C((void *)arg0);
        }
        break;
    }
}


void func_8017FE10(void) {
}

extern s32 func_8012C588(s32 a0, s32 a1);
    void func_8017FE18(u8 *a0) {
        ((void (*)(s32, s32))func_8012C588)(0x3D7, (s32)a0);
    }



extern s32 func_8012E544(s32 arg);
    void func_8017FE3C(void) {
        s32 p = func_8012E544(0x224);
        if (p != 0) {
            *(u16*)(p + 0x34) += 1;
        }
    }


extern s32 func_8012E544(s32 arg);
    void func_8017FE78(void) {
        s32 p = func_8012E544(0x224);
        if (p != 0) {
            *(u16*)(p + 0x34) += 1;
        }
    }


#include "common.h"

void func_8017FEB4(s32 arg0) {
    extern s32 D_80126B9C;
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_80029514(s32);
    extern void func_801843E0(void *, s32);
    extern short D_8018FA9C;
    extern short D_8018F498;
    extern int func_80178970();
    extern void func_80178D18();
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (D_80126B9C & 0x8000000) {
            *(u16 *)(arg0 + 0x34) = 1;
            func_80178B18(arg0, &D_8018FA9C);
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)(arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            func_80029514(0x1E0);
            *(u16 *)(arg0 + 2) = 6;
            func_801843E0((void *)arg0, &D_8018F498);
        }
        break;
    }
}


extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801845FC(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017FF64(void *a0) {

    extern short D_801BEA50;
    extern short D_801B9550;
    *(short *)((char *)a0 + 0x2) = 2;
    *(u16 *)((char *)a0 + 0x34) = 0;
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801BEA50);
    func_801843B8((s32)a0);
    func_801845FC((s32)a0, (s32)&D_801B9550, 0, 0x60);
}




extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);


void func_8017FFC8(void *a0) {

    extern short D_8018FBF4;
    extern short D_801D3BC4;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_8018FBF4);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D3BC4);
    func_801843B8((s32)a0);
}




extern void func_801843E0(void*, s32);
    extern short D_8018FBEC;
    void func_80180020(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 7;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018FBEC);
    }


extern s32 D_8018FBF4;
extern s32 D_801D3BC4;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_8018004C(s32 a0) {
    *(s16 *)(a0 + 2) = 8;
    func_8012E8E0(a0, (s32)&D_8018FBF4);
    func_8012E88C(a0);
    func_8012A828(a0, (s32)&D_801D3BC4);
}


extern s32 D_801BEAF8;
extern s32 D_801D3BC4;
extern void func_8012A828(s32, s32);
extern s32 func_8012B608(s32, s32, s32);

void func_8018009C(s32 param_1)
{
    s32 v0;
    s32 a1;
    s32 t0;
    s32 t1;
    s32 r;

    switch ((s16)(*(u16 *)(param_1 + 0xFC) - 1)) {
    case 1:
        if (*(s32 *)(param_1 + 0x90) != (s32)&D_801D3BC4) {
            func_8012A828(param_1, (s32)&D_801D3BC4);
        }
        v0 = *(s32 *)(param_1 + 0x20);
        __asm__ __volatile__(""); /* §5a cross-jump barrier, placed between the two tail  // !FAKE: barrier — NEEDED COMPILE-ERROR (P36 rung B tus7)
                                      stores (not immediately before the jump) so reorg can
                                      still fill the branch delay slot with `a1 = 0xC00`;
                                      keeps this arm's tail distinct from case 0's identical
                                      one so gcc does not fold the two duplicate tails */
        a1 = 0xC00;
        goto common;
    case 0:
        if (*(s32 *)(param_1 + 0x90) != (s32)&D_801BEAF8) {
            func_8012A828(param_1, (s32)&D_801BEAF8);
        }
        v0 = *(s32 *)(param_1 + 0x20);
        a1 = 0xC00;
        goto common;
    case 3:
        t0 = *(s32 *)(param_1 + 0x90);
        t1 = (s32)&D_801D3BC4;
        goto LAB_80180154;
    case 2:
        t0 = *(s32 *)(param_1 + 0x90);
        t1 = (s32)&D_801BEAF8;
    LAB_80180154:
        if (t0 != t1) {
            func_8012A828(param_1, t1);
        }
        v0 = *(s32 *)(param_1 + 0x20);
        a1 = 0xE00;
    common:
        r = func_8012B608((s32)*(s16 *)(v0 + 0x12), a1, 8);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + r;
        return;
    case 4:
        func_801801B0(param_1);
        return;
    default:
        return;
    }
}


extern short D_801BEA50;
extern void func_8012A828(s32, s32);

void func_801801B0(param_1)
int param_1;
{
    *(short *)(param_1 + 2) = 9;
    *(short *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801BEA50);
    *(int *)(param_1 + 0x1c) = 0xf;
}



extern void (*D_8018FC14[])(void);

void func_801801F4(void *a0) {
    D_8018FC14[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180230(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
    }


extern u16 D_800B99DA;
extern u8 D_8018FC10;
extern u8 D_8018FC11;
extern u8 D_8018FC12;
extern u8 D_8018FC13;
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017FF64(void *a0);

void func_8018023C(void *a0) {
    if ((D_800B99DA & 3) == 0 && func_801842F8(D_8018FC10, D_8018FC11, D_8018FC12, D_8018FC13) != 0) {
        func_8017FF64(a0);
    }
}


extern s32 func_801846CC(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);
extern void func_8017FFC8(void *a0);
extern s16 D_801B9560;

void func_801802A8(void *a0) {
    s32 v0;
    u16 v1;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
        case 0:
            v0 = func_801846CC((s32)a0);
            if (v0 != 0) {
                func_801845FC((s32)a0, (s32)&D_801B9560, 1, 0x60);
                *(u16 *)((u8 *)a0 + 0x34) = 1;
            }
            break;
        case 1:
            v0 = func_801846CC((s32)a0);
            if (v0 != 0) {
                func_8017FFC8(a0);
            }
            break;
    }
}


extern s32 func_801846CC(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);
extern void func_801843E0(void *a0, s32 a1);
extern s16 D_801B9550;
extern s16 D_8018FBEC;

void func_80180334(void *a0) {
    s32 v0;
    u16 v1;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
        case 0:
            v0 = func_801846CC((s32)a0);
            if (v0 != 0) {
                func_801845FC((s32)a0, (s32)&D_801B9550, 1, 0x60);
                *(u16 *)((u8 *)a0 + 0x34) = 1;
            }
            break;
        case 1:
            v0 = func_801846CC((s32)a0);
            if (v0 != 0) {
                *(u16 *)((u8 *)a0 + 0x2) = 1;
                func_801843E0(a0, (s32)&D_8018FBEC);
            }
            break;
    }
}


extern u16 D_800B99DA;
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801845FC(s32, s32, s32, s32);
extern short D_801BEA50;
extern s16 D_801B9560;
extern void func_8018004C(s32 a0);

void func_801803CC(void *arg0)
{
    if (*(s16 *)((char *)arg0 + 0xFC) != 0) {
        func_8018004C((s32)arg0);
    }
    if ((D_800B99DA & 3) == 0 && func_801842F8(9, 4, 0x12, 0) == 0) {
        *(s16 *)((char *)arg0 + 2) = 6;
        func_8012E88C((s32)arg0);
        func_8012A828((s32)arg0, (s32)&D_801BEA50);
        func_801843B8((s32)arg0);
        *(s16 *)((char *)arg0 + 0x34) = 0;
        func_801845FC((s32)arg0, (s32)&D_801B9560, 0, 0x60);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80180020(void *arg0);

void func_80180478(void * arg0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        func_80180020(arg0);
    }
}


void func_801804B8(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern void func_8012CBA4(s32 a0);
extern void func_801843E0();

void func_801804C0(void *a0) {
    s32 v0;
    u16 v1;
    s32 w;

    extern short D_8018FBEC;

    v1 = *(u16 *)((u8 *)a0 + 0x34);
    switch (v1) {
    case 0:
        v0 = func_8012B608(*(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12), 0x400, 8);
        *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) += v0;
        if (func_8012BEE8((s32)a0) != 0) {
            w = *(u16 *)((u8 *)a0 + 0x34);
            *(s32 *)((u8 *)a0 + 0x1C) = 0x2D;
            *(u16 *)((u8 *)a0 + 0x34) = w + 1;
        }
        break;
    case 1:
        v0 = func_8012B608(*(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12), 0x400, 8);
        *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) += v0;
        func_8012B178((s32)a0, 0xFFFA0000);
        func_8012CBA4((s32)a0);
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((u8 *)a0 + 0x2) = 7;
            ((void (*)(s32, s32))func_801843E0)((int)a0, (int)&D_8018FBEC);
        }
        break;
    }
}


#include "common.h"

extern s32 func_80183EE4(void *a0, void *a1);
extern s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_801843B8(s32 a0);
extern void func_801843E0(void*, s32);
extern void func_8012CAE4(void *a0);

void func_801805AC(void *a0) {

    extern short D_8018FBEC;
    extern s32 D_8018FBF4;
    extern void (*D_8018FBFC)(void);
    extern s32 D_801D3BC4;
    void *v1;

    if ((u32)(func_80029504() - 0xC8) >= 0xA) {
        func_8012CAE4(a0);
        return;
    }
    if (func_80183EE4(a0, &D_8018FBFC) != 0) {
        if (func_801842F8(9, 4, 0x12, 0) != 0) {
            *(short *)((char *)a0 + 0x2) = 3;
            func_8012E8E0((s32)a0, (s32)&D_8018FBF4);
            func_8012E88C((s32)a0);
            ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D3BC4);
            func_801843B8((s32)a0);
        } else {
            *(short *)((char *)a0 + 0x2) = 1;
            ((void (*)(s32, s32))func_801843E0)((int)a0, (int)&D_8018FBEC);
        }
        v1 = *(void **)((char *)a0 + 0x68);
        *(short *)((char *)v1 + 0xC) = 0x7FFF;
    }
}


void func_80180684(void) {
}


extern void (*D_8018FDFC[])(void);

void func_8018068C(void *a0) {
    D_8018FDFC[*(u16 *)((s32)a0 + 0x2)]();
}





s32 func_801806C8(void) {

    extern s32 D_801E2460;
    return !(D_801E2460 ^ 1);
}


extern s32 func_8012C588(s32, s32);
void func_801806E0(void) {
    ((void (*)(s32, s32))func_8012C588)(0x1CD, 0);
}


extern void func_800D1724(s32 a0);
    extern s32 D_8018E894;
    void func_80180704(void) {
        ((void (*)(void *))func_800D1724)(&D_8018E894);
    }


void func_8018072C(void) {
}

extern s32 func_80029178(s32 arg);
extern int func_800D0F8C(int a0);
extern void func_80178CBC(s32 *a0, s32 a1);
extern void func_80029124(s32, s32);
extern void func_800D0F4C(s32 a0);
extern u8 D_8018FD84;
extern u8 D_8018FC54;
extern u8 D_8018FCB4;

void func_80180734(s32 a0) {
    s32 t;

    *(s16 *)(a0 + 2) = 3;
    t = func_80029178(0x106);
    if ((t & 0xFF) != 0) {
        func_80178CBC((s32 *)a0, (s32)&D_8018FD84);
    } else if (func_800D0F8C(0x58) == 0) {
        func_80178CBC((s32 *)a0, (s32)&D_8018FC54);
    } else {
        func_80178CBC((s32 *)a0, (s32)&D_8018FCB4);
        func_80029124(0x106, 1);
        func_800D0F4C(0x58);
    }
}


#include "common.h"

extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_801843E0(void*, s32);

void func_801807D8(void * arg0) {

    extern short D_8018FC3C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 1;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018FC3C);
    }
}


#include "common.h"

extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_80029124(s32, s32);
extern void func_800D0F4C(s32 a0);
extern u8 D_8018FCB4;

void func_80180828(s32 a0)
{
    *(s16 *)(a0 + 2) = 5;
    func_80178B18(a0, (s32)&D_8018FCB4);
    func_80029124(0x106, 1);
    func_800D0F4C(0x58);
}


#include "common.h"

extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_801843E0(void*, s32);

void func_80180868(void * arg0) {

    extern short D_8018FC3C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 1;
        ((void (*)(s32, s32))func_801843E0)((int)arg0, (int)&D_8018FC3C);
    }
}


extern s32 func_80029504(void);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern short D_8018FC3C;
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8018095C(void *a0);
extern void func_801843E0(void*, s32);

void func_801808B8(arg0)
void *arg0;
{
    extern short D_8018FC3C;
    s32 t;
    s32 v;
    void *v1;

    t = func_80029504();
    if ((u32)(t - 0xC8) >= 0x1AE) {
        func_8012CAE4(arg0);
        return;
    }
    v = ((s32 (*)())func_8012C1B8)();
    *(s32 *)((char *)arg0 + 0x20) = v;
    if (v == 0) {
        func_8012CAE4(arg0);
    }
    func_8001C214(*(s32 *)((char *)arg0 + 0x20), 0);
    *(s16 *)((char *)arg0 + 2) = 1;
    ((void (*)(s32*, s32))func_801843E0)((s32 *)arg0, (s32)&D_8018FC3C);
    v1 = *(void **)((char *)arg0 + 0x68);
    *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
    *(s32 *)((char *)arg0 + 0xD4) = func_801788B8((s32)arg0, (s32)&func_8018095C);
}


extern s32 D_80126B58;
extern s32 D_80126B9C;
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern short D_8018FC3C;
extern s32 func_800133E4(s16 *a0, s16 *a1);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_8018095C(void *a0)
{
    s16 *p;
    s32 r;

    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 1) {
        return 0;
    }
    p = (s16 *)&D_80126B58;
    if ((D_80126B9C & 0x8000000) == 0) {
        r = 0;
        goto chain_fail;
    }
    p += 2;
    if (func_800133E4((s16 *)&D_8018FC3C, p) >= 0x6401) {
        r = 0;
        goto chain_fail;
    }
    if (*(s16 *)&D_80126B5E >= 0x281) {
        r = 0;
        goto chain_fail;
    }
    r = *(s16 *)&D_80126B66 >= -0x380;
chain_fail:
    if (r) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 2;
        func_80178BF8();
        return (s32)func_80172710;
    }
    return 0;
}



extern void (*D_8018FE1C[])(void);

void func_80180A24(void *a0) {
    D_8018FE1C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_8018FE14;

void func_80180A60(void * arg0) {
    func_8012E8E0((s32)arg0, (s32)&D_8018FE14);
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_80180A88(void *a0)
{
    extern void (*D_801BA6D4[])(s32 *);
    extern s32 D_8018FE14;
    s32 s0;
    s32 v1;
    s32 t;

    s0 = (s32)a0;
    v1 = func_80029504();
    if (v1 < 0xC8) {
        func_8012CAE4((void *)s0);
        return;
    }
    if (v1 < 0x258) {
        if ((u8)func_80029178(0x106) == 0) {
            func_8012CAE4((void *)s0);
            return;
        }
        goto init;
    }
    if (v1 >= 0x276) {
        func_8012CAE4((void *)s0);
        return;
    }
init:
    t = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s0 + 0x20) = t;
    if (t == 0) {
        func_8012CAE4((void *)s0);
        return;
    }
    func_8001C214(t, (s32)&D_801BA6D4[0]);
    func_8012E8E0(s0, (s32)&D_8018FE14);
    *(s16 *)(*(s32 *)(s0 + 0x68) + 0xC) = 0x7FFF;
    *(s16 *)(s0 + 0x2) = 1;
}


extern void (*D_8018FEA4[])(void);

void func_80180B40(void *a0) {
    D_8018FEA4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180B7C(void) {
}

extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_8018FE4C;
    void func_80180B84(short *param_1) {
        *(short *)((char *)param_1 + 0x2) = 0x3;
        func_80178CBC((s32 *)param_1, (s32)&D_8018FE4C);
    }


extern int func_80178970(void);
extern void func_80178D18(void);

void func_80180BB0(void *a0) {
    extern u32 D_8018FE2C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 1;
        *(s32 *)((char *)a0 + 0x58) = (s32)&D_8018FE2C | 0x40000000;
        *(short *)((char *)a0 + 0x5C) = 0x800;
    }
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_801788B8(s32 a0, s32 a1);

void func_80180C0C(void *a0) {
    extern s32 D_801BA0BC;
    extern s32 D_8018FE24;
    extern u32 D_8018FE2C;
    extern void func_80180CC8();
    s32 t;
    s32 v0;

    t = func_80029504();
    if ((u32)(t - 0xC8) >= 0x190) {
        func_8012CAE4(a0);
        return;
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801BA0BC);
    *(s16 *)(*(s32 *)((char *)a0 + 0x68) + 0xC) = 0x7FFF;
    func_8012E8E0((s32)a0, (s32)&D_8018FE24);
    *(s16 *)((char *)a0 + 0x2) = 1;
    *(s32 *)((char *)a0 + 0x58) = (s32)&D_8018FE2C | 0x40000000;
    *(s16 *)((char *)a0 + 0x5C) = 0x800;
    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)func_80180CC8);
}


extern void func_8012BD14(s32);
extern s32 func_80178BF8();      /* TU-canonical */
extern void func_80172710(void); /* TU-canonical */

s32 aF80180CC8(void *arg0) __asm__("func_80180CC8");

s32 aF80180CC8(void *arg0)
{
    extern u16 D_80126B66;

    if (*(u16 *)(*(s32 *)((s32)arg0 + 0x64) + 0x2) != 1) {
        return 0;
    }
    if (((s32 (*)(void))func_8012BD14)() >= 0x4000) {
        return 0;
    }
    if (*(s16 *)&D_80126B66 < -0x2F0) {
        return 0;
    }
    *(u16 *)(*(s32 *)((s32)arg0 + 0x64) + 0x2) = 2;
    func_80178BF8();
    return (s32)func_80172710;
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SV3_80180D48;

void func_80180D48(void)
{
    extern s32 D_801E1A28;
    extern s32 D_801E256C;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_8012F40C(void *, void *);

    SV3_80180D48 in1, in2;
    s32 out[2];
    s16 a, b;
    s32 p, t;

    *(s32 *)(*(s32 *)&D_801E256C + 4) =
        *(u16 *)(*(s32 *)&D_801E1A28 + 6) | ((s32)*(s16 *)(*(s32 *)&D_801E1A28 + 0xE) << 16);

    in1.vx = *(u16 *)(*(s32 *)&D_801E1A28 + 6);
    in1.vy = *(u16 *)(*(s32 *)&D_801E1A28 + 0xA);
    in1.vz = *(u16 *)(*(s32 *)&D_801E1A28 + 0xE);

    in2.vx = D_80126B5E;
    in2.vy = D_80126B62;
    in2.vz = D_80126B66;

    func_8012F40C(out, &in1);
    a = out[0];
    func_8012F40C(out, &in2);
    do { b = out[0]; } while (0);
    /* §194-A: zero-byte sched1 fence AFTER the defining statement so `b = out[0]`
       emits FIRST in its block, ahead of the D_801E256C lui/lw pair. */

    p = *(s32 *)&D_801E256C;
    t = a & 0xFFFF;
    *(u32 *)(p + 0xC) = t;
    if (a >= b) {
        *(u32 *)(p + 0xC) = t | 0x10000;
    }
    p = *(s32 *)&D_801E256C;
    t = b & 0xFFFF;
    *(u32 *)(p + 0x14) = t;
    if (a < b) {
        *(u32 *)(p + 0x14) = t | 0x10000;
    }
}


void func_80180E40(void *param_1) {
    extern u8 D_80078E78[];
    extern u8 D_80078EB0[];
    extern u8 D_8018FEB4[];
    extern u8 D_8018FEB6[];
    extern u8 D_8018FEB8[];
    extern s32 D_801E1A20;
    extern s32 D_801E1A24;
    extern void (*D_8018FEF0)(void *);
    extern s32 func_8016F1C4(void);
    extern void func_801851D8(s32 arg);
    extern void func_80185754(s32 arg0, s32 arg1);
    extern void func_80185238(s32 arg);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern void func_80178CBC(s32 *a0, s32 a1);
    extern s32 func_801789AC(s32 arg0);
    extern void func_80178D18(void);

    register void *arg0 __asm__("$19") = param_1;  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus7)
    u8 *var_s5;
    s32 var_s2;
    s32 var_s0;
    s16 *var_s1;
    s32 var_a0;
    s32 var_v1;
    u32 var_s4;
    s32 unused[2];

    var_s5 = D_80078E78;
    var_s2 = 0;
    var_s0 = 0;
    var_s1 = (s16 *)&D_8018FEB4;
    var_a0 = *(s16 *)D_80078EB0;
    var_v1 = 0;
    var_s4 = var_a0;

    for (; var_s0 < 6; var_s1 += 4, var_s0++, var_v1 += 8) {
        if ((var_a0 < *(s16 *)(D_8018FEB6 + var_v1)) ||
            (*(s16 *)(D_8018FEB8 + var_v1) <= var_a0)) {
            continue;
        }
        var_s2 = 1;
        if (func_8016F1C4() == 0) {
            func_801851D8(0xE);
            func_80185754(0xE, 0x3C);
        }
        if (*var_s1 != 0) {
            break;
        }
        if (func_8016F1C4() == 0) {
            func_8012C658(0x1D2, var_s0, 0);
            *var_s1 = 1;
        }
        break;
    }
    if (var_s2 == 0) {
        func_80185238(0xE);
    }
    __asm__ __volatile__("" : "=r"(var_s4) : "0"(var_s4));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus7)
    if ((D_801E1A20 < (s32)*(u16 *)(var_s5 + 0x34)) &&
        (((var_s4 - 0x1000) & 0xFFFF) < 0x11)) {
        D_801E1A20 = *(u16 *)(var_s5 + 0x34);
        {
            s32 v = 0x28;
            do {
                *(s16 *)((s32)&D_8018FEB4 + v) = 0;
                v -= 8;
            } while (v >= 0);
        }
    }
    if (D_801E1A24 != 0) {
        s32 t = D_801E1A24 - 2;
        D_801E1A24 = t;
        if (t < 0) {
            D_801E1A24 = 0;
        }
    }
    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 1:
        *(u16 *)((s32)arg0 + 0x34) = 2;
        func_80178CBC((s32 *)arg0, (s32)&D_8018FEF0);
        break;
    case 2:
        if (func_801789AC((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(u16 *)((s32)arg0 + 0x34) = 0;
        }
        break;
    }
}



extern void (*D_8018FF38[])(void);

void func_80181040(void *a0) {
    D_8018FF38[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012A828(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_801845FC(s32, s32, s32, s32);

s32 func_8018107C()
{
    extern u8 D_801DE0E8[];
    extern s32 D_80190018[];
    extern s16 D_801B95F0;
    extern u8 D_80190020;

    register s32 t __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
    s32 s0;
    s32 a1v;
    s32 zv;
    u8 a3v;

    s0 = t;
    *(u16 *)((s32)s0 + 2) = 2;
    func_8012A828(t, (s32)D_801DE0E8);
    func_8012E8E0((s32)s0, (s32)&D_80190018[0]);
    a1v = (s32)&D_801B95F0;
    zv = 0;
    a3v = D_80190020;
    *(u16 *)((s32)s0 + 0x34) = 0;
    func_801845FC((s32)s0, a1v, zv, a3v);
}


void func_801810E4(void *a0)
{
    extern s32 func_801846CC(s32 a0);
    extern void func_801845FC(s32, s32, s32, s32);
    extern s32 func_801842D4(s32 a0, s32 a1);
    extern void func_8012A828(s32, s32);
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern void func_8012E8A8(u8 *a0);
    extern void func_8012C218(void *a0);
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern u8 D_80190020;
    extern s32 D_80190024[];
    extern s16 D_8018FF68;
    extern s16 D_8018FEE4;
    extern s16 D_8018FEE8;
    extern s32 D_801E1A24;

    s32 i;
    s32 t;
    s32 t2;
    s32 a3v;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        if (func_801846CC((s32)a0) != 0) {
            a3v = D_80190020;
            *(s16 *)((s32)a0 + 0x34) = 1;
            func_801845FC((s32)a0, D_80190024[*(s16 *)((s32)a0 + 0x70)], 0, a3v);
        }
        if (func_801842D4(7, 0x17) != 0) {
            *(s16 *)((s32)a0 + 0x34) = 2;
        }
        break;
    case 1:
        if (func_801846CC((s32)a0) != 0) {
            a3v = D_80190020;
            *(s16 *)((s32)a0 + 0x34) = 0;
            func_801845FC((s32)a0, D_80190024[*(s16 *)((s32)a0 + 0x70)], 1, a3v);
        }
        if (func_801842D4(7, 0x17) != 0) {
            *(s16 *)((s32)a0 + 0x34) = 2;
        }
        break;
    case 2:
        *(s16 *)((s32)a0 + 0x34) = 3;
        func_8012A828((s32)a0, (s32)&D_8018FF68);
        *(s32 *)((s32)a0 + 0x1C) = 0x14;
        break;
    case 3:
        if (func_8012BEE8((s32)a0) != 0) {
            if (D_8018FEE8 + 4 >= D_801E1A24) {
                t2 = D_801E1A24 + 2;
                D_801E1A24 = t2 + D_8018FEE8;
                for (i = 0; i < D_8018FEE4; i++) {
                    func_8012C588(0x25F, (s32)a0);
                }
                func_8012E8A8((u8 *)a0);
                *(s32 *)((s32)a0 + 0x1C) = 0xA;
                *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
            }
        }
        break;
    case 4:
        if ((*(s32 *)((s32)a0 + 0x1C) & 1) == 0) {
            t = func_80132EF4((s32)a0, 0x22);
            if (t != 0) {
                *(s16 *)(t + 0x34) = 0x5001;
                *(s32 *)(t + 0x14) = 0xFFFA0000;
            }
        }
        if (func_8012BEE8((s32)a0) != 0) {
            func_8012C218(a0);
        }
        break;
    }
}



extern void (*D_8019003C[])(void);

void func_801812D0(void *a0) {
    D_8019003C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018130C(void *a0p)
{
    extern s32 D_80190048[];
    extern u16 D_8018FEE6;
    extern s16 D_8018FEE8;
    extern s16 D_8018FEEA;
    extern s16 D_8018FEEC;
    extern u16 D_8018FEEE;
    extern void func_8012B23C(s32 a0);
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8012B2CC(s32 a0);
    extern s32 rand(void);
    extern s32 func_80047948(s32 a0);
    extern s32 func_8004787C(s32 a0);
    register void *arg0 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus7)
    s32 s0;
    s32 v0;
    s32 s2;
    s32 s3;

    arg0 = a0p;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
    } else {
        func_8001C214(*(s32 *)((char *)arg0 + 0x20), D_80190048[rand() & 0xF]);
        *(u16 *)((char *)arg0 + 0x2) += 1;
        *(u16 *)((char *)arg0 + 0xA) -= D_8018FEE6;
        *(s32 *)((char *)arg0 + 0x1C) = D_8018FEE8;
        func_8012B2CC((s32)arg0);
        func_8012B23C((s32)arg0);

        s2 = D_8018FEEA;
        s2 = (rand() & 0xFFF) * -s2;
        *(s32 *)((char *)arg0 + 0x14) = s2;

        s2 = D_8018FEEC;
        s0 = rand() & 0xFFF;
        s3 = func_80047948(s0) * s2;
        s0 = func_8004787C(s0) * s2;
        s3 = (s3 * (rand() & 0xFF)) >> 4;
        s0 = (s0 * (rand() & 0xFF)) >> 4;
        *(s32 *)((char *)arg0 + 0x10) = s3;
        *(s32 *)((char *)arg0 + 0x18) = s0;

        *(u16 *)((char *)arg0 + 0xFC) = D_8018FEEE & rand();
        *(u16 *)((char *)arg0 + 0xFE) = D_8018FEEE & rand();
        *(u16 *)((char *)arg0 + 0x100) = D_8018FEEE & rand();
    }
}



extern void (*D_80190088[])(void);

void func_801814A4(void *a0) {
    D_80190088[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801814E0(void *arg0) {
    extern s32 func_80029504(void);
    extern void func_8012CAE4(void *a0);
    extern s32 func_801788B8(s32 arg0, s32 arg1);
    extern void func_801816C8(s32 a0);
    extern s32 D_801E1A20;
    extern s32 D_801E1A24;
    extern s32 D_8018FEB4;
    s32 v;

    if ((u32)(func_80029504() - 200) >= 400) {
        func_8012CAE4(arg0);
        return;
    }

    D_801E1A20 = 0;
    for (v = 0x28; v >= 0; v -= 8) {
        *(s16 *)((char *)&D_8018FEB4 + v) = 0;
    }
    *(s16 *)((s32)arg0 + 2) = 1;
    *(s16 *)((s32)arg0 + 0x34) = 0;
    D_801E1A24 = 0;
    func_801788B8((s32)arg0, (s32)func_801816C8);
}


extern s32 func_8018107C(void);
    void func_8018156C(void) {
        func_8018107C();
    }


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_8018158C(void *arg0) {
    extern s32 D_801D71F0[];
    extern s32 D_80190018[];
    extern u8 D_801DE0E8[];
    extern u8 D_80190008;
    s32 v0;

    v0 = func_80029504();
    if ((u32)(v0 - 0xC8) >= 0x190) {
        func_8012CAE4(arg0);
        return;
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
        return;
    }
    func_8001C214(v0, (s32)D_801D71F0);
    func_8012A828((s32)arg0, (s32)D_801DE0E8);
    *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    func_8012E8E0((s32)arg0, (s32)&D_80190018);
    *(s32 *)((char *)arg0 + 0x58) = (s32)&D_80190008 | 0x40000000;
    *(s16 *)((char *)arg0 + 0x5C) = 0x810;
    *(s16 *)((char *)arg0 + 0x2) = 1;
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80181644(void *a0)
{
    void *s0;

    func_8012AD80((s32)a0);
    s0 = a0;

    *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x10) + *(u16 *)((char *)s0 + 0xFC);

    *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x12) + *(u16 *)((char *)s0 + 0xFE);

    *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)((char *)s0 + 0x20) + 0x14) + *(u16 *)((char *)s0 + 0x100);

    if (func_8012BEE8((s32)s0) != 0) {
        func_8012C218(s0);
    }
}


/* func_801816C8 — ov_SC03_124 / ov_SC03_124_jr_8017AE2C, 57 ins, match_one MATCH (57/57).
 *
 * Scans the 0x10C-stride actor table D_801202A0[0x6480] for an entry whose
 * +0x00 == 0x1D2, +0x02 == 2 and +0x34 < 2; asks func_8012BD14() for permission
 * (< 0x4001), publishes the entry in D_801E1A28, stamps 1 into the caller's
 * linked object (+0x64)->+0x34, pokes func_80178BF8() and returns the address of
 * the next callback (func_80172710).  Sibling of aF8017F1A0 / aF8017FA98 / aF8018CB18
 * in this TU — same decl surface, same house style.
 *
 * DECL SURFACE (§37 / §73 / §376): the TU already carries `extern void func_801816C8(s32 a0);`
 * (L6948, used only to take the address at L6966).  The byte-true signature disagrees on
 * BOTH axes (void->s32, void->void*), so the definition is emitted under the C identifier
 * `aF801816C8` with an __asm__("func_801816C8") label — the same alias form already banked
 * three times in this file (aF8017F1A0 L5395, aF8017FA98 L5757, aF8018CB18 L7180).  Verified:
 * MATCH with and without the alias; without it cc1 emits "type mismatch with previous
 * external decl" (warning only, rc=0), with it, nothing.
 * func_8012BD14 and D_801E1A28 use the TU-canonical spellings (void(s32) with a cast at use,
 * s32) — NOT the fleet's s32(s32)/s16.
 *
 * THE TWO LEVERS (both byte-witnessed here; the whole residual was WHICH of the three
 * pre-loop constants got hoisted, and in what order — see §193-F/§148-A):
 *
 *  1. `register s32 idA __asm__("$21")` set in the preheader.  A plain `u16 idA = 0x1D2;`
 *     is constant-propagated into the loop compare by cse1 and then re-hoisted by
 *     move_movables, which emits it at loop_start — i.e. AFTER every real preheader
 *     statement.  Measured: all six source orderings of the three inits emit 0x1D2 LAST,
 *     while the target wants it FIRST.  The hard-register pin blocks the propagation, so
 *     the `addiu $s5,$zero,0x1D2` stays a genuine preheader insn and leads.
 *
 *  2. The two `__asm__ ("")` fences raise loop.c's `insn_count` from 25 to 27 at ZERO bytes
 *     (an ASM_INPUT is a real insn to loop.c and emits nothing).  §193-F's threshold
 *     staircase, read out of `cc1 -dL`:
 *         Loop from 22 to 105: 27 real insns.
 *         Insn 41: regno 80 (life 1), savings 1  moved to 123      29*1*1 = 29 >= 27  -> $s4 = 2
 *         Insn 71: regno 87 (life 1), savings 1 not desirable      26*1*1 = 26 <  27  -> 1 stays inline
 *     At 26 insns BOTH move: the constant 1 lands in $s6, costing an extra callee-saved
 *     slot (+3 ins, 60 vs 57).  At 27 exactly one moves — which is the target.
 *
 *  q = p + 0x34 is deliberately NOT written as a variable: loop.c strength-reduces it into
 *  its own giv ($s1) and combine_givs folds the p+2 access onto it as -0x32($s1), and the
 *  giv init is emitted AFTER the hoisted movables — giving the target's 0x1D2 / 2 / q order.
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_801816C8 \
 *           --c .run/S70w_1/opus/func_801816C8.c \
 *           --asm-subdir asm/ov_SC03_124/nonmatchings/ov_SC03_124_jr_8017AE2C  -> MATCH (57 ins)
 */

extern void func_8012BD14(s32);
extern s32 func_80178BF8();
extern void func_80172710(void);
extern u8 D_801202A0[];
extern s32 D_801E1A28;

s32 aF801816C8(void *a0) __asm__("func_801816C8");

s32 aF801816C8(void *a0) {
    u8 *p = D_801202A0;
    u8 *end = D_801202A0 + 0x6480;
    u16 idA;

    if (p != end) {
        idA = 0x1D2;
        do {
            if (*(u16 *)p == idA) {
                if (*(u16 *)(p + 2) == 2) {
                    if (*(u16 *)(p + 0x34) < 2) {
                        if (((s32 (*)(s32))func_8012BD14)((s32)p) < 0x4001) {
                            s32 obj = *(s32 *)((s32)a0 + 0x64);
                            D_801E1A28 = (s32)p;
                            *(s16 *)(obj + 0x34) = 1;
                            func_80178BF8();
                            return (s32)func_80172710;
                        }
                    }
                }
            }
            p += 0x10C;
        } while (p != end);
    }
    return 0;
}




s32 func_801817AC(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u16 D_80126B62;
    s16 v1;
    s32 result;

    v1 = *(s16 *)&D_80126B5E;
    if (v1 < 0x400) {
        result = 0;
    } else if (v1 >= 0x501) {
        result = 0;
    } else {
        v1 = *(s16 *)&D_80126B66;
        if (v1 < 0x580) {
            result = 0;
        } else if (v1 >= 0x601) {
            result = 0;
        } else {
            v1 = *(s16 *)&D_80126B62;
            result = (v1 >= -0x200);
        }
    }
    return result;
}


extern void func_8012B2CC(s32 a0);
    void func_80181810(void * arg0) {
        s32 *p = *(s32 **)((char *)arg0 + 0x20);
        *(short *)((char *)arg0 + 0x2) = 0x2;
        *(short *)((char *)p + 0x12) = -0x600;
        func_8012B2CC((s32)arg0);
    }


extern void func_8012B2CC(s32 a0);
void func_80181840(void *arg0) {
    s32 *p = *(s32 **)((char *)arg0 + 0x20);
    *(short *)((char *)arg0 + 0x2) = 0x4;
    *(short *)((char *)p + 0x12) = 0x600;
    func_8012B2CC((s32)arg0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80181A1C(void *arg0);

void func_80181870(void *arg0) {

    extern u8 D_801BA7F4[];
    extern u8 D_801BA8E4[];
    extern u8 D_80190090[];
    extern u8 D_801900A0[];
    s32 v0;
    s32 t;
    s32 *p;

    v0 = ((s32 (*)(void *))func_8012C1B8)(arg0);
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
    } else {
        func_8001C214(v0, *(s16 *)((char *)arg0 + 0x70) == 0 ? (s32)&D_801BA7F4[0] : (s32)&D_801BA8E4[0]);
        *(s16 *)((char *)arg0 + 0x5C) = 0x800;
        *(s32 *)((char *)arg0 + 0x58) =
            (s32)&D_801900A0[*(s16 *)((char *)arg0 + 0x70) * 0x10] | 0x40000000;
        func_8012E8E0((s32)arg0, (s32)&D_80190090[*(s16 *)((char *)arg0 + 0x70) * 8]);
        *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
        t = func_80029504();
        if ((func_80029178(0xF6) & 0xFF) == 0 && t < 0xE6) {
            if (*(s16 *)((char *)arg0 + 0x70) == 0) {
                *(s16 *)((char *)arg0 + 0x2) = 1;
                *(s16 *)((char *)arg0 + 0x34) = 0;
                func_801788B8((s32)arg0, (s32)func_80181A1C);
            } else {
                s32 *q = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 3;
                *(s16 *)((char *)arg0 + 0x34) = 0;
                *(s16 *)((char *)q + 0x12) = 0;
                *(s32 *)((char *)arg0 + 0x1C) = 0x30;
            }
        } else {
            if (*(s16 *)((char *)arg0 + 0x70) == 0) {
                p = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 2;
                *(s16 *)((char *)p + 0x12) = -0x600;
                func_8012B2CC((s32)arg0);
            } else {
                p = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 4;
                *(s16 *)((char *)p + 0x12) = 0x600;
                func_8012B2CC((s32)arg0);
            }
        }
    }
}



extern void (*D_801901D0[])(void);

void func_801819E0(void *a0) {
    D_801901D0[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_80181A1C — state-2 gate for the SC04_018 actor state machine.
 *
 * Reads the actor's linked object (a0->0x64), requires its state word (+0x2) == 1
 * and the actor's own +0x34 flag clear, then asks func_801817AC() for permission;
 * on success it stamps 1 into the linked object's +0x34, pokes func_80178BF8() and
 * returns the address of the next callback (func_80172710).
 *
 * DECL SURFACE (§73 / §37): the TU already carries a fleet-canonical forward decl
 *   `extern void func_80181A1C(void *arg0);`   (ov_SC04_018_jr_8017AE2C.c L7759)
 * used only to take the function's ADDRESS at L7786.  The byte-true signature
 * disagrees on BOTH §73 axes (return void->s32 AND params void->void*), so neither
 * the fleet widen nor a cast-at-use fixes it.  Instead the definition is emitted
 * under the C identifier `aF8018CB18` with an __asm__("func_80181A1C") label
 * (§37 asm-label alias, the proven function-definition form — cf.
 * src/ov_SC03_099/ov_SC03_099_after.c L533).  The C-level name never collides with
 * the canonical decl, the emitted symbol is unchanged, and codegen is byte-identical
 * (verified: match_one MATCH 31/31 with and without the alias).
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_80181A1C \
 *           --c .run/s7/ov_SC04_018/func_80181A1C.c \
 *           --asm-subdir asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C  -> MATCH (31 ins)
 */

extern s32 func_801817AC(void);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */

s32 aF8018CB18(void *a0) __asm__("func_80181A1C");

s32 aF8018CB18(void *a0)
{
    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 1) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        return 0;
    }
    if (func_801817AC() == 0) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) = 1;
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_80029124(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0F4C(s32 a0);
extern s32 func_8012E57C(s32 a0, s32 a1);


void func_80181A98(void *a0)
{
    s32 result;

    *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;

    func_8002D4C8(0x7A0, 0);
    func_80029124(0xF6, 1);
    func_800D0F4C(0x59);

    result = func_8012E57C(0x1F2, 1);

    if (result) {
        *(u16 *)(result + 0x34) = *(u16 *)(result + 0x34) + 1;
    }
}





s32 func_80181B08(void) {

    extern s32 D_801E2460;
    return !(D_801E2460 ^ 2);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80181B20(void) {
        func_8002D4C8(0x7E0, 0);
    }
