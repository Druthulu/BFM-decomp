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
extern u8 D_8018F74C;
extern u8 D_8018F6BC;
extern u8 D_8018F698;
extern u8 D_8018F674;
extern u8 D_8018F728;
extern u8 D_8018F704;
extern u8 D_8018F6E0;
extern u8 D_8018F650;
extern void func_80145934(void);
extern u8 D_8018F7DC;
extern u8 D_8018F7B8;
extern u8 D_8018F794;
extern u8 D_8018F770;
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
extern unsigned char D_8018EBD4[];
extern unsigned char D_8018EC04[];
extern unsigned char D_8018EC54[];
extern unsigned char D_8018EC84[];
extern unsigned char D_8018ECB4[];
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
extern void (*D_8018ED04[])(void *);
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
extern s32 D_8018EDCC[];
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
extern u8 D_8018EE54[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018EE5C;
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
extern int D_801E5BA8;
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
extern s32 D_801E5BAC;
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
extern s32 D_8018EE8C;
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
extern void (*D_8018EF34[])(void);
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
extern void (*D_8018EF58[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018EF48;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018EF6C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018EF78[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018EF88[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018EFA0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018EF90;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018EFB4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018EFD0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018EFC0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018EFE4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018EFF8[])(void);
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
extern s32 D_8018F00C;
extern void (*D_8018F034[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018F014;
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
extern int (*D_8018F080[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018F084[])(void);
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
extern unsigned short D_8018F4E8[];
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
extern void (*D_8018F4F8[])(void);
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
extern int D_801E5BE0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018F520[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018F500;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018F510;
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
extern void (*D_8018F560[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018F568[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018F534;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018F574[])(void);
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
extern u8 D_8018F544;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E5BE8;
extern s32 D_801E5BF4;
extern s32 D_801E5BF8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018F5B0[])(s32 *);
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
extern s32 D_8018F584[];
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
extern s32 D_801E5BF0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018F800[])(void);
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
extern char D_8018F620[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018F8A4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018F9F8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018F814;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018FA00[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018F824;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018F844;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018FA08[])(void);
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
extern void (*D_8018FA30[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018FA3C[])(void);
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
extern void (*D_8018F8B0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018FAE0;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018EBC4[];
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
extern unsigned char D_8018FAF4[];
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
extern s8 D_8018FB30[];
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
extern u16 D_8018FB78;
extern u16 D_8018FB7A;
extern u16 D_8018FB7C;
extern s32 D_8018FB80;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018FB88;
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
extern int D_8018F894;
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
extern unsigned int D_8018FC0C[];
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
extern void (*D_8018FCBC[])(void);
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
extern u16 D_8018FCEC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018FD50;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E5C00[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018FD74[])(void);
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
extern int D_801E5C58[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018FDBC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018FDAC;
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
extern char D_801E5054[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018FDC4[])(void);
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
extern void (*D_8018FE18[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018FDE0;
extern s16 D_8018FE14;
extern s16 D_8018FE12;
extern s16 D_8018FE10;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018FE24[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E5CB8;
extern u8 D_801E5CB9;
extern u8 D_801E5CBA;
extern u8 D_801E5CBB;
extern u8 D_801E5CBC;
extern u8 D_801E5CBD;
extern u8 D_801E5CBE;
extern u8 D_801E5CBF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018FE34[])(void);
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
extern s32 D_801E5CF8;
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
extern void (*D_8018FE78[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018FEF4[];
extern s32 D_8018FF14[];
extern u8 D_8018FF90[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018FFB0[];
extern u8 D_8018FFD0[];
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
extern void (*D_8019006C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801900E8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E5064;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801900F4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801900FC[])(void);
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
extern void (*D_801901C4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801901D4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801901E4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801901F0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80190150[];
extern u8   D_80190164[];
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
extern void (*D_80190208[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80190210[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80190218[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80190220[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80190228[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80190230[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80190238[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801902EC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801902F4[])(void);
extern void func_80169F00(void *a0);
extern char D_801902A4[];
extern char D_80190264[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8019032C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80190338[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80190380[])(void);
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
extern void (*D_801903FC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E6018;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801903F0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80190434[];
extern unsigned short D_8019043C[];
extern unsigned short D_80190444[];
extern unsigned char D_801E6020[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E6018;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019044C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E6154;
extern M2C_UNK D_801E6158;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E60E0;
extern void (*D_8019047C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E615C[];
extern u8 D_801E6164[];
extern u8 D_801E6114[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80190484[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801904A0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801904A8[])(void);
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
extern void (*D_80190510[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801904B4;
extern u8 D_801904C0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80190544[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019054C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801905A0[])(void);
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
extern u16 D_801905D4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801905C4[];
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
extern s32 D_801905F0;
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
extern void (*D_80190668[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80190670[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80190678[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80190680[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80190688[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80190690[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8019069C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801906A8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801906B4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801906C4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801906D4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801906DC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801906E4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801906EC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801906F4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801906FC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80190704[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8019070C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80190714[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8019071C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80190724[])(void);
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
extern void (*D_8019072C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80190734[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8019073C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80190744[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8019074C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80190754[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8019075C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80190764[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8019076C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80190774[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8019077C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80190784[])(void);
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
extern void (*D_801907C8[])(void);
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
extern M2C_UNK D_8019078C;
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
extern void (*D_801907F8[])(void);
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
extern void (*D_80190834[])(void);
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
extern void (*D_8019088C[])();
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
extern void (*D_8019089C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801908A4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80190A0C[])();
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
extern void (*D_80190A18[])();
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
extern M2C_UNK D_801E52AC;
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
extern s16 D_801E7AB0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E6898;
extern short D_801E7B24;
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
extern s32 D_801E6CC4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E6CEC;
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
extern s16 D_801E6CA8;
extern s32 func_8017A3B0(void);
extern short D_801E6CE4;
extern short D_801E6CE0;
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

extern s16 D_801E7A68;
extern s16 D_801E7A6A;
extern s16 D_801E7A74;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801E7A68;

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
                    func_8012B744(p, &D_801E7A74);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801E7A68+0xC == &D_801E7A74; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801E7A68 + 0xC)) < 0x101) {
                    D_801E7A68 = 0;
                    D_801E7A6A = 0;
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
            func_8012B744((void *)(pv + 4), &D_801E7A74);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801E7A68 + 0xC)) < 0x101) {
            D_801E7A68 = 0;
            D_801E7A6A = 0;
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
    extern s16 D_801E6D24;
    extern s16 D_801E6D26;
    extern s16 D_801E6D28;
    extern s16 D_801E6D1C;
    extern s16 D_801E6D1E;
    extern s16 D_801E6D20;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801E6D24, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801E6D26, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801E6D28, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801E6D1C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801E6D1E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801E6D20, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801E6CAC;
extern u16 D_801E6D2C;
extern u16 D_801E6D2E;
extern u16 D_801E6D30;
extern s16 D_801E7AB0;

void func_8017B1D8(void) {
    func_8012A418();
    D_801E7AB0 = 0;
    D_801E6CAC = 0;
    D_801E6D2C = D_80126B5E;
    D_801E6D2E = D_80126B62;
    D_801E6D30 = D_80126B66;
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
    extern u8 D_80190B54[];
    extern s16 D_801E6D24;
    extern s16 D_801E6D1C;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80190B54[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80190B54[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E6D24;
        s16 *p78C = &D_801E6D1C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801E7AB0 = 1;
        D_801E6CAC = 0;
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
    extern SV4_8017B368 D_801E6CCC;
    extern SV4_8017B368 D_801E6CD4;
    extern s16 D_801E6D24;
    extern s16 D_801E6D1C;
    extern u16 D_80190B54;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E6CCC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E6CD4;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80190B54)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80190B54)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E6D24) = loc0;
    (*(SV4_8017B368 *)&D_801E6D1C) = loc1;
    D_801E7AB0 = 1;
    D_801E6CAC = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801E6CCC;
    extern SV4_8017B368 D_801E6CD4;
    extern s16 D_801E6D24;
    extern s16 D_801E6D1C;
    extern u16 D_80190B54;
    extern s16 D_801E6CAC;
    extern s16 D_801E7AB0;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E6CCC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E6CD4;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80190B54)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80190B54)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E6D24) = loc0;
    (*(SV4_8017B368 *)&D_801E6D1C) = loc1;
    D_801E7AB0 = 1;
    D_801E6CAC = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801E6D24).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801E6D24).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801E6D24).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801E6D1C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801E6D1C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801E6D1C).c;
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
    extern u8 D_80190B54[];
    extern s16 D_801E6D24;
    extern s16 D_801E6D26;
    extern s16 D_801E6D28;
    extern s16 D_801E6D1C;
    extern s16 D_801E6D1E;
    extern s16 D_801E6D20;
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
        s32 a1addr = (s32)&D_80190B54[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80190B54[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E6D24;
        s16 *p78C = &D_801E6D1C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801E6D26;
            v798 = D_801E6D28;
            v78C = *p78C;
            v78E = D_801E6D1E;
            v790 = D_801E6D20;
            __asm__ __volatile__("");
            D_801E7AB0 = 1;
            D_801E6CAC = 0x1E;
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
extern s16 D_801E6CAC;
extern s16 D_801E6D24;
extern s16 D_801E6D26;
extern s16 D_801E6D28;
extern s16 D_801E6D1C;
extern s16 D_801E6D1E;
extern s16 D_801E6D20;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801E6CAC = 0;
    D_801E6D24 = (s16) D_80114F30;
    D_801E6D26 = (s16) D_80114F34;
    D_801E6D28 = (s16) D_80114F38;
    D_801E6D1C = (s16) D_80114F24;
    D_801E6D1E = (s16) D_80114F28;
    D_801E6D20 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801E6D3C;
extern s16 D_801E6D3E;
extern s16 D_801E6D40;
extern s16 D_801E6D44;
extern s16 D_801E6D46;
extern s16 D_801E6D48;

void func_8017B824(void) {
    D_801E6D3C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801E6D3E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801E6D40 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801E6D44 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801E6D46 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801E6D48 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801E6D3C;
extern s16 D_801E6D3E;
extern s16 D_801E6D40;
extern s16 D_801E6D44;
extern s16 D_801E6D46;
extern s16 D_801E6D48;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801E6D3C;
    D_80114F34 = D_801E6D3E;
    D_80114F38 = D_801E6D40;
    D_80114F24 = D_801E6D44;
    D_80114F28 = D_801E6D46;
    D_80114F2C = D_801E6D48;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801E6D24), src[8..15] -> (*(S8_8017B8E8 *)&D_801E6D1C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801E6D24) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801E6D1C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801E6D2C;
extern u16 D_801E6D2E;
extern u16 D_801E6D30;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801E6CAC;
extern short D_801E6D34;
extern short D_801E6D36;
extern short D_801E6D38;
extern s16 D_801E6D24;
extern s16 D_801E6D26;
extern s16 D_801E6D28;
extern s16 D_801E6D1C;
extern s16 D_801E6D1E;
extern s16 D_801E6D20;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801E6D2C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801E6D2E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801E6D30);
    (*(s16 *)&D_801E6D34) = buf[0];
    (*(s16 *)&D_801E6D36) = buf[1];
    (*(s16 *)&D_801E6D38) = buf[2];
    D_801E6D24 = D_80114F30 + buf[0];
    D_801E6CAC = 0;
    D_801E6D26 = D_80114F34 + buf[1];
    D_801E6D28 = D_80114F38 + buf[2];
    D_801E6D1C = D_80114F24 + buf[0];
    D_801E6D1E = D_80114F28 + buf[1];
    D_801E6D20 = D_80114F2C + buf[2];
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

extern SV4 D_801E6CCC;
extern SV4 D_801E6CD4;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801E6CD4) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801E6CCC = svec;

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
    D_801E6CD4 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801E6CD4)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801E6CCC) = svec;

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
    (*(SV4_8017BB34*)&D_801E6CD4) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801E6CF4[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801E6CF4;
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
extern s16 D_801E6CAC;
extern s16 D_801E7AB0;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801E6CAC = D_801E6CAC + 1;
    if (D_801E6CAC >= 0x1F) {
        D_801E7AB0 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801E6CAC;
extern s16 D_801E7AB0;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E6CAC = D_801E6CAC + 1;
    if (0x18 < D_801E6CAC) {
        func_8012A4BC();
        D_801E7AB0 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801E6CAC;
extern void (*D_801E6CF0)(void);
extern short D_801E6D34;
extern short D_801E6D36;
extern short D_801E6D38;
extern s16 D_801E7AB0;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E6CAC = D_801E6CAC + 1;
    if (D_801E6CAC >= 0x19) {
        if (D_801E6CF0 != 0) {
            (*D_801E6CF0)();
        } else {
            D_80114F30 = D_80114F30 + D_801E6D34;
            D_80114F34 = D_80114F34 + D_801E6D36;
            D_80114F38 = D_80114F38 + D_801E6D38;
            D_80114F24 = D_80114F24 + D_801E6D34;
            D_80114F28 = D_80114F28 + D_801E6D36;
            D_80114F2C = D_80114F2C + D_801E6D38;
            func_8012A4BC();
        }
        D_801E7AB0 = 0;
    }
}



extern void (*D_80190BF4[])(void);

void func_8017BE60(void *a0) {
    D_80190BF4[*(u8 *)((s32)a0 + 0x4)]();
}



extern void (*D_80190C94[])(void);

void func_8017BE9C(void *a0) {
    D_80190C94[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80190C9C[])(void);

void func_8017BED8(void *a0) {
    D_80190C9C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80190CA4[])(void);

void func_8017BF14(void *a0) {
    D_80190CA4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017BF50);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017C094);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017C100);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017C1AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017C1EC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017C2B0);


extern void (*D_80190CC4[])(void);

void func_8017C338(void *a0) {
    D_80190CC4[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017C374(s32 param_1) {

    extern u8 D_80190CAC;
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

    node = func_800D222C(param_1, &D_80190CAC, 0xFD);
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


DEFINE_func_8017C5CC()  /* dedup: shared engine-core @0x8017C5CC (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_80190CB8;

void func_8017C608(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_80190CB8, 0x18);
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


extern void (*D_80190CE4[])(void);

void func_8017D5F0(void *a0) {
    D_80190CE4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_80190CD4;

void func_8017D62C(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_80190CD4 | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


DEFINE_func_8017D6A8()  /* dedup: shared engine-core @0x8017D6A8 (src/shared) */

DEFINE_func_8017D6B0()  /* dedup: shared engine-core @0x8017D6B0 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017D6EC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017D77C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017D9B8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DA08);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DAC4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DBDC);


// @class: regalloc-order
// @stuck: none — MATCH

extern u32 D_801E6FE8;
extern u16 D_80190D24[];
extern u16 D_801E6FEC[];
extern s32 D_80190D44;

extern void func_800183E0(s32 a0);

void func_8017DC0C(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_80190D24;
    base = D_801E6FE8 >> 8;
    p = D_801E6FEC;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_80190D44);
    D_801E6FE8 = D_801E6FE8 + 0x100;
}



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017E038(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017DC98(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017E038, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017DCE8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DD0C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DD7C);

extern void func_800D1EBC(void);
    void func_8017DE2C(void) {
        func_800D1EBC();
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DE4C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017DEA0);


extern void (*D_80190D64[])(void);

void func_8017DF34(void *a0) {
    D_80190D64[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80190D6C[])(void);

void func_8017DF70(void *a0) {
    D_80190D6C[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80190D78[])(void);

void func_8017DFAC(void *a0) {
    D_80190D78[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80190D84[])(void);

void func_8017DFE8(void *a0) {
    D_80190D84[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_80127050;
    void func_8017E024(void) {
        D_80127050 = 1;
    }



extern void (*D_80191060[])(void);

void func_8017E038(void *a0) {
    D_80191060[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017E074()  /* dedup: shared engine-core @0x8017E074 (src/shared) */

extern void func_80175414(s32);
extern void func_8016F0E4(void);
extern void func_80165770(void);
void func_8017E088(void *a0) {
    ((void (*)(void *))func_80175414)(a0);
    ((s32 (*)(struct S *))func_8016F0E4)((struct S *)a0);
    ((void (*)(void *))func_80165770)(a0);
}



extern void (*D_80191068[])(void);

void func_8017E0C0(void *a0) {
    D_80191068[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017E0FC()  /* dedup: shared engine-core @0x8017E0FC (src/shared) */

extern void func_8016F0E4(void);
void func_8017E110(void) {
    func_8016F0E4();
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017E1F4(void *a0);


void func_8017E130(void) {

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
    func_8012A018((s32)func_8017E1F4, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    func_8017E1F4(D_80126948);
    func_8012A094((s32)D_80126948);
    func_8017E1F4(D_80126948);
}



extern void (*D_80191070[])(void);

void func_8017E1F4(void *a0) {
    D_80191070[*(u8 *)((s32)a0 + 0x4)]();
}


















extern void func_8017E26C(s32 *a0, s32 a1);
extern void func_8017E3AC(s32 a0);
void func_8017E230(s32 *a0)
{
  s32 *new_var;
  volatile long pad;
  new_var = a0;
  func_8017E26C(new_var, ((s32) new_var) + 0xA0);
  func_8017E3AC((s32) new_var);
}

DEFINE_func_8017E264()  /* dedup: shared engine-core @0x8017E264 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E26C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E3AC);


extern void func_80184CB8(s32*, s32);
    extern short D_80191074;
    void func_8017E5A0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191074);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E5CC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E628);


extern void (*D_801912A8[])(void);

void func_8017E760(void *a0) {
    D_801912A8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012A828(s32 *a0, s32 a1);
    extern short D_801B9B50;
    void func_8017E79C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        func_8012A828((s32 *)a0, (s32)&D_801B9B50);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E7CC);


extern void (*D_801912C8[])(void);

void func_8017E810(void *a0) {
    D_801912C8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801910A0;
    void func_8017E84C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801910A0);
    }



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191288;
    void func_8017E878(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 7;
        func_80178CBC((int)arg0, (int)&D_80191288);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E8A4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E8FC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E950);

extern void func_8012C588(s32, s32);
void func_8017E99C(void) {
    func_8012C588(0x22B, 0);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017E9C0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EA0C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EAAC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EAFC);

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017E79C(short*);
void func_8017EBA0(s32 a0) {
    func_8012AD80(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8017E79C)(a0);
    }
}


extern void func_8017E7CC(void);
    void func_8017EBE0(u8 *a0) {
        if (*(u16 *)((s32)a0 + 0x34) == 1) {
            func_8017E7CC();
        }
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EC10);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017ECF4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EDA4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017EE6C);


extern void func_80184CB8(s32*, s32);
    extern short D_801912D8;
    void func_8017F02C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801912D8);
    }


DEFINE_func_8017F058()  /* dedup: shared engine-core @0x8017F058 (src/shared) */



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191304;
    void func_8017F094(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_80191304);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F0C0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F0D8);

extern void func_80029124(s32 arg0, s32 arg1);
    void func_8017F108(void) {
        func_80029124(0x10C, 0);
        func_80029124(0x10D, 1);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F138);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F174);

extern void func_80029514(int);
void func_8017F1A8(void) {
    func_80029514(0x280);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F1C8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F224);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F28C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F2DC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F35C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F418);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F500);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F564);


extern void (*D_801916E4[])(void);

void func_8017F5BC(void *a0) {
    D_801916E4[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern int func_800D0F8C(int a0);
extern void func_80178CBC(s32, s32);

void func_8017F5F8(void *a0) {

    extern short D_80191694;
    extern short D_801915EC;
    s32 t;
    s32 v;

    *(short *)((char *)a0 + 0x2) = 0x4;
    t = func_80029504();
    v = 0;
    if (t >= 0x280) {
        if (t < 0x2B2) {
            if ((func_80029178(0x107) & 0xFF) != 0) {
                if (func_800D0F8C(0x63) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x64) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x65) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x66) != 0) {
                    v = 3;
                } else {
                    v = 2;
                }
            } else {
                v = 1;
            }
        } else if (t < 0x2E4) {
            v = 4;
        } else {
            v = 5;
        }
    }
    if (v == 1) {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_80191694);
    } else {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801915EC);
    }
}



extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern int func_800D0F8C(int a0);
extern void func_80178CBC(s32, s32);

void func_8017F6D8(void *a0) {

    extern short D_801916C4;
    extern short D_80191624;
    s32 t;
    s32 v;

    *(short *)((char *)a0 + 0x2) = 0x7;
    t = func_80029504();
    v = 0;
    if (t >= 0x280) {
        if (t < 0x2B2) {
            if ((func_80029178(0x107) & 0xFF) != 0) {
                if (func_800D0F8C(0x63) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x64) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x65) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x66) != 0) {
                    v = 3;
                } else {
                    v = 2;
                }
            } else {
                v = 1;
            }
        } else if (t < 0x2E4) {
            v = 4;
        } else {
            v = 5;
        }
    }
    if (v == 1) {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801916C4);
    } else {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_80191624);
    }
}



extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern int func_800D0F8C(int a0);
extern void func_80178CBC(s32, s32);

void func_8017F7B8(void *a0) {

    extern short D_801916C4;
    extern short D_80191624;
    s32 t;
    s32 v;

    *(short *)((char *)a0 + 0x2) = 0xd;
    t = func_80029504();
    v = 0;
    if (t >= 0x280) {
        if (t < 0x2B2) {
            if ((func_80029178(0x107) & 0xFF) != 0) {
                if (func_800D0F8C(0x63) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x64) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x65) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x66) != 0) {
                    v = 3;
                } else {
                    v = 2;
                }
            } else {
                v = 1;
            }
        } else if (t < 0x2E4) {
            v = 4;
        } else {
            v = 5;
        }
    }
    if (v == 1) {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801916C4);
    } else {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_80191624);
    }
}



extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern int func_800D0F8C(int a0);
extern void func_80178CBC(s32, s32);

void func_8017F898(void *a0) {

    extern short D_801916C4;
    extern short D_80191624;
    s32 t;
    s32 v;

    *(short *)((char *)a0 + 0x2) = 0xa;
    t = func_80029504();
    v = 0;
    if (t >= 0x280) {
        if (t < 0x2B2) {
            if ((func_80029178(0x107) & 0xFF) != 0) {
                if (func_800D0F8C(0x63) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x64) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x65) != 0) {
                    v = 3;
                } else if (func_800D0F8C(0x66) != 0) {
                    v = 3;
                } else {
                    v = 2;
                }
            } else {
                v = 1;
            }
        } else if (t < 0x2E4) {
            v = 4;
        } else {
            v = 5;
        }
    }
    if (v == 1) {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801916C4);
    } else {
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_80191624);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017F978);

extern void func_80029124(s32 a, s32 b);
void func_8017FA34(void) {
    func_80029124(0x107, 0x1);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FA58);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FB0C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FBB0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FC58);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FCD8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FD28);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FD88);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FDE4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FE54);


extern void (*D_80191814[])(void);

void func_8017FF34(void *a0) {
    D_80191814[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8017FF70);


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018001C);

DEFINE_func_801800E0()  /* dedup: shared engine-core @0x801800E0 (src/shared) */


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018011C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180134);

DEFINE_func_8018015C()  /* dedup: shared engine-core @0x8018015C (src/shared) */


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191874;
    void func_80180164(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        func_80178CBC((int)arg0, (int)&D_80191874);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180190);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801801E0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180284);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018034C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801803BC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018042C);


extern void (*D_801919C4[])(void);

void func_8018048C(void *a0) {
    D_801919C4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801804C8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180504);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_80180544(void) {
        if ((func_80029178(0x110) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x110, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180580);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801805C0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180618);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018067C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801806CC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180740);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180814);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180888);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801808FC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180954);

extern void func_80184CB8(s32 *a0, s32 a1);
    extern short D_801919E0;
    void func_801809DC(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        func_80184CB8((s32 *)a0, (s32)&D_801919E0);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180A08);


extern void (*D_80191A80[])(void);

void func_80180B6C(void *a0) {
    D_80191A80[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180BA8);


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191A20;
    void func_80180C0C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 7;
        func_80178CBC((int)arg0, (int)&D_80191A20);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180C38);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180CC0);


/* func_80180D38 — state-machine callback registered by func_80180A08.
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
 *   - +0x34 is reloaded after the D_801E7010 store, and 0x64 is reloaded too:
 *     gcc-2.7.2 CSE invalidates memory on the global store, so re-express both
 */

extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);

s32 func_80180D38(void *a0)
{

    extern s16 D_801E7010;
    extern s16 D_801E7012;
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
        D_801E7010 = st;
        D_801E7012 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180E28);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180EE8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80180F7C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181020);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181090);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181124);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801811F4);

extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_80191A58;
    void func_80181244(short *param) {
        param[1] = 0xB;
        func_80178CBC((int)param, (int)&D_80191A58);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181270);

extern void func_80184CB8(s32 *a0, s32 a1);
    extern short D_80191AB0;
    void func_801812D0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        func_80184CB8((s32 *)a0, (s32)&D_80191AB0);
    }



extern void (*D_80191B20[])(void);

void func_801812FC(void *a0) {
    D_80191B20[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_80191AE8;
    void func_80181338(short *param) {
        param[1] = 4;
        func_80178CBC((int)param, (int)&D_80191AE8);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181364);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801813A4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181400);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181474);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801814C4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181564);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801815DC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181648);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801816A8);


extern void func_80184CB8(s32*, s32);
    extern short D_80191B34;
    void func_8018170C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 7;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191B34);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181738);


extern void func_80184CB8(s32*, s32);
    extern short D_80191B34;
    void func_8018178C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 9;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191B34);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801817B8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181804);


extern void (*D_80191BDC[])(void);

void func_80181924(void *a0) {
    D_80191BDC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181960);

DEFINE_func_80181998()  /* dedup: shared engine-core @0x80181998 (src/shared) */

DEFINE_func_801819B0()  /* dedup: shared engine-core @0x801819B0 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801819C8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181A28);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181A68);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181AA8);


/* func_80181B34 — guarded dispatch: ask func_80184BAC(9, 0xF); if it answers
 * zero, run func_801816A8 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_801816A8(void *arg0);

void func_80181B34(void *arg0) {
    if (func_80184BAC(9, 0xF) == 0) {
        func_801816A8(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181B74);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181BEC);


/* func_80181C78 — guarded dispatch: ask func_80184BAC(15, 0x11); if it answers
 * zero, run func_80181738 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80181738(void *arg0);

void func_80181C78(void *arg0) {
    if (func_80184BAC(15, 0x11) == 0) {
        func_80181738(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181CB8);


/* func_80181DC4 — guarded dispatch: ask func_80184BAC(17, 0x12); if it answers
 * zero, run func_801817B8 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_801817B8(void *arg0);

void func_80181DC4(void *arg0) {
    if (func_80184BAC(17, 0x12) == 0) {
        func_801817B8(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181E04);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181EFC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181F70);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80181FE4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018203C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182120);


extern void func_80184CB8(s32*, s32);
    extern short D_80191C08;
    void func_801821A8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191C08);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801821D4);

DEFINE_func_8018233C()  /* dedup: shared engine-core @0x8018233C (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182378);


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191C48;
    void func_80182490(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 7;
        func_80178CBC((int)arg0, (int)&D_80191C48);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801824BC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182544);


/* func_801825BC — state-machine callback registered by func_80180A08.
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
 *   - +0x34 is reloaded after the D_801E7020 store, and 0x64 is reloaded too:
 *     gcc-2.7.2 CSE invalidates memory on the global store, so re-express both
 */

extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);

s32 func_801825BC(void *a0)
{

    extern s16 D_801E7020;
    extern s16 D_801E7022;
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
        D_801E7020 = st;
        D_801E7022 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801826AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018276C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182800);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801828B0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182920);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801829AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182A7C);


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191EB0;
    void func_80182ACC(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 11;
        func_80178CBC((int)arg0, (int)&D_80191EB0);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182AF8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182B58);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182BCC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182C24);


extern void (*D_80192014[])(void);

void func_80182C98(void *a0) {
    D_80192014[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182CD4);

extern s32 D_801D7E84;
    extern s32 D_801D6C98;
    void func_80182D0C(void) {
        D_801D6C98 = D_801D7E84;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182D24);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182D84);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_80182DC4(void) {
        if ((func_80029178(0x113) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x113, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182E00);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182E40);


/* func_80182ED8 — guarded dispatch: ask func_80184BAC(7, 0xE); if it answers
 * zero, run func_80182C24 on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80182C24(void *arg0);

void func_80182ED8(void *arg0) {
    if (func_80184BAC(7, 0xE) == 0) {
        func_80182C24(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182F18);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80182F88);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183024);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801830F4);

extern void func_80184CB8(s32 *a0, s32 a1);
    extern short D_80192030;
    void func_801831AC(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        func_80184CB8((s32 *)a0, (s32)&D_80192030);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801831D8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183248);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801832A8);


extern void func_80184CB8(s32*, s32);
    extern short D_80192030;
    void func_8018330C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80192030);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183338);


extern void (*D_8019211C[])(void);

void func_80183438(void *a0) {
    D_8019211C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80192070;
    void func_80183474(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x4;
        func_80178CBC((int)a0, (int)&D_80192070);
    }



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80192070;
    void func_801834A0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        func_80178CBC((int)arg0, (int)&D_80192070);
    }


extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_801920C4;
    void func_801834CC(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0xc;
        func_80178CBC((s32 *)a0, (s32)&D_801920C4);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801834F8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183538);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183578);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183604);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183674);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801836C0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018370C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018375C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801837A8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801837EC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183838);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183890);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801838E0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183938);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801839A8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183A08);


extern void (*D_80192230[])(void);

void func_80183A68(void *a0) {
    D_80192230[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801921B8;
    void func_80183AA4(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        func_80178CBC((int)arg0, (int)&D_801921B8);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183AD0);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_80183B10(void) {
        if ((func_80029178(0x115) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x115, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183B4C);

extern s32 func_80184FA4(void);
    extern void func_801839A8(s32 arg0);
    void func_80183B8C(s32 param_1) {
        if (((s32 (*)(void))func_80184FA4)() != 0) {
            ((void (*)(s32))func_801839A8)(param_1);
        }
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183BC4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183C28);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183C78);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183CBC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183D80);


extern void func_80184CB8(s32*, s32);
    extern short D_8019224C;
    void func_80183DF4(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 1;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_8019224C);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183E20);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183E6C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183FA8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80183FF4);


extern void (*D_80192414[])(void);

void func_80184130(void *a0) {
    D_80192414[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018416C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801841AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801841EC);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_8018422C(void) {
        if ((func_80029178(0x116) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x116, 1);
            return 1;
        }
        return 0;
    }




extern void func_80178CBC(s32, s32);
    extern short D_801922E4;
    void func_80184268(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x8;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801922E4);
    }




extern void func_80178CBC(s32, s32);
    extern short D_8019232C;
    void func_80184298(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0xe;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_8019232C);
    }




extern void func_80178CBC(s32, s32);
    extern short D_80192334;
    void func_801842C8(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x4;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_80192334);
    }


extern void func_80178CBC(s32 arg0, s32 arg1);
extern s16 D_801923A4;

void func_801842F8(void *arg0) {
    *(s16 *)((char *)arg0 + 0x2) = 0xB;
    *(s16 *)((char *)arg0 + 0x34) = 0;
    func_80178CBC((s32)arg0, &D_801923A4);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184328);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184374);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801843C4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184410);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184460);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801844AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184504);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184560);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801845B8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018465C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184738);


void func_8018479C(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }



void func_801847AC(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801847BC);


















extern void func_8012A828(s32*, s32);
void func_80184858(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x4)));
}



















extern void func_8012A828(s32*, s32);
void func_80184884(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x8)));
}



















extern void func_8012A828(s32*, s32);
void func_801848B0(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0xc)));
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801848DC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184960);

extern s32 func_80184960(s32 arg);
    extern void func_80184AC4(void *a0);
    void func_80184A90(u8 *a0) {
        *(s32 *)(a0 + 0xe0) = func_80184960((s32)a0);
        func_80184AC4(a0);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184AC4);

extern short D_800BA2BA;
    s32 func_80184B04(s32 arg0) {
        return *(short *)((char *)&D_800BA2BA + (*(short *)(*(s32 *)(arg0 + 0xd0) + 0x10) << 2));
    }



extern void (*D_801B8720[])(void);

void func_80184B2C(void *a0) {
    D_801B8720[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80184B68()  /* dedup: shared engine-core @0x80184B68 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184B70);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184BAC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184BD0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184C28);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184C90);

DEFINE_func_80184CB0()  /* dedup: shared engine-core @0x80184CB0 (src/shared) */


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184CB8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184D00);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184D5C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184DD0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184E44);


extern s32 func_80029504(void);
    extern void func_80029514(s32 arg0);
    void func_80184EA0(void) {
        if (((s32 (*)(void))func_80029504)() == 0x3A2) {
            ((void (*)(s32))func_80029514)(0x3AC);
        }
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184ED4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80184FA4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018516C);


extern void (*D_801B8740[])(void);

void func_801851B4(void *a0) {
    D_801B8740[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801851F0()  /* dedup: shared engine-core @0x801851F0 (src/shared) */

DEFINE_func_801851F8()  /* dedup: shared engine-core @0x801851F8 (src/shared) */

DEFINE_func_80185200()  /* dedup: shared engine-core @0x80185200 (src/shared) */

DEFINE_func_80185208()  /* dedup: shared engine-core @0x80185208 (src/shared) */

DEFINE_func_80185210()  /* dedup: shared engine-core @0x80185210 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185218);

DEFINE_func_8018525C()  /* dedup: shared engine-core @0x8018525C (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185264);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801852EC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801854C4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185664);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801856E0);

extern void func_80185EEC(void);
void func_801857AC(void) {
    func_80185EEC();
}



extern s32 func_8018516C(s32 a0);
extern void func_8018589C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_80185EEC(void);

void func_801857CC(s32 a0) {
    if (func_8018516C(a0) == 2) {
        func_8018589C(a0);
    }
    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(u16 *)(a0 + 0x34) = 1;
    }
    *(u16 *)(a0 + 0x100) = *(u16 *)(a0 + 0x100) + *(u16 *)(a0 + 0x102);
    if (*(s16 *)(a0 + 0x100) >= 0x50) {
        *(u16 *)(a0 + 0x100) = 0x50;
    }
    *(u16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - *(u16 *)(a0 + 0x100);
    if (*(s16 *)(a0 + 0xFE) <= 0) {
        func_8012E688(a0, 0x515, 0);
        func_8018589C(a0);
    } else {
        ((void (*)(s32))func_80185EEC)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018589C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185904);

DEFINE_func_80185978()  /* dedup: shared engine-core @0x80185978 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801859D8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185A58);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185AB0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185B10);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185B58);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185BA8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185BE0);


extern s16 currentLocationId;
extern s32 func_80185D10(void *a0);
extern s32 func_801862A8(void *a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void *func_80185C6C(void *a0) {
    if (currentLocationId == 0x3069) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x2) != 2) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        return 0;
    }
    if (*(s16 *)((s32)a0 + 0x10A) != 0) {
        return 0;
    }
    if (func_80185D10(a0) == 0) {
        return 0;
    }
    if (func_801862A8(a0) != 0) {
        return 0;
    }
    *(s16 *)((s32)a0 + 0x34) = 1;
    func_80178BF8();
    return (void *)func_80172710;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185D10);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185D70);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185EEC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185F20);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185F54);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80185FB8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018602C);

DEFINE_func_80186084()  /* dedup: shared engine-core @0x80186084 (src/shared) */


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801860C0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018613C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018625C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801862A8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801863B4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80186410);

s16 func_80186450(void) {

    extern s16 D_801E7030;
    return D_801E7030;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80186460);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801864AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018651C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80186570);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80186E24);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801877B0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801878E8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801880EC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80188428);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80188778);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_801889B8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80188B84);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80188E1C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189214);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189540);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189DDC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189E14);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189E54);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_80189EA0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A0B4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A168);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A1D0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A224);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A2E0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A6C8);

DEFINE_func_8018A740()  /* dedup: shared engine-core @0x8018A740 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A77C);

DEFINE_func_8018A898()  /* dedup: shared engine-core @0x8018A898 (src/shared) */


extern void (*D_801E0524[])(void);

void func_8018A8D4(void *a0) {
    D_801E0524[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E0534[])(void);

void func_8018A910(void *a0) {
    D_801E0534[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E0544[])(void);

void func_8018A94C(void *a0) {
    D_801E0544[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8018A988()  /* dedup: shared engine-core @0x8018A988 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018A990);

DEFINE_func_8018AB3C()  /* dedup: shared engine-core @0x8018AB3C (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018AB78);


extern s32 D_801E01F0;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018ACD4(void) {
    D_801E7980 = &D_801E01F0;
    func_8018A168(0x474, 0x4B0);
}



extern s32 D_801E0228;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AD08(void) {
    D_801E7980 = &D_801E0228;
    func_8018A168(0x474, 0x4EC);
}



extern s32 D_801E0260;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AD3C(void) {
    D_801E7980 = &D_801E0260;
    func_8018A168(0x474, 0x4B0);
}



extern s32 D_801E0288;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AD70(void) {
    D_801E7980 = &D_801E0288;
    func_8018A168(0x474, 0x4B0);
}



extern s32 D_801E02C0;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018ADA4(void) {
    D_801E7980 = &D_801E02C0;
    func_8018A168(0x474, 0x528);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018ADD8);


extern s32 D_801E0338;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AE4C(void) {
    D_801E7980 = &D_801E0338;
    func_8018A168(0x474, 0x1A4);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018AE80);


extern s32 D_801E0390;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AECC(void) {
    D_801E7980 = &D_801E0390;
    func_8018A168(0x12c, 0x1A4);
}


DEFINE_func_8018AF00()  /* dedup: shared engine-core @0x8018AF00 (src/shared) */


extern s32 D_801E0440;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AF34(void) {
    D_801E7980 = &D_801E0440;
    func_8018A168(0x474, 0x4B0);
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018AF68);


extern s32 D_801E0488;
extern s32 D_801E7980;
extern void func_8018A168(s32 arg0, s32 arg1);

void func_8018AFB4(void) {
    D_801E7980 = &D_801E0488;
    func_8018A168(0x564, 0x1A4);
}


DEFINE_func_8018AFE8()  /* dedup: shared engine-core @0x8018AFE8 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018AFF0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B0AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B158);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B19C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B2B8);


extern void func_8012B414(int a0);
    void func_8018B354(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B388);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B400);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B448);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B4EC);

DEFINE_func_8018B564()  /* dedup: shared engine-core @0x8018B564 (src/shared) */


extern void (*D_801E056C[])(void);

void func_8018B570(void *a0) {
    D_801E056C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B5AC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B614);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B660);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B6A0);

DEFINE_func_8018B6E8()  /* dedup: shared engine-core @0x8018B6E8 (src/shared) */



extern void (*D_801E0580[])(void);

void func_8018B6F4(void *a0) {
    D_801E0580[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B730);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B798);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B7FC);

DEFINE_func_8018B868()  /* dedup: shared engine-core @0x8018B868 (src/shared) */



extern void (*D_801E0594[])(void);

void func_8018B874(void *a0) {
    D_801E0594[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B8B0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B904);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B948);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018B988);

DEFINE_func_8018B9D0()  /* dedup: shared engine-core @0x8018B9D0 (src/shared) */


extern void (*D_801E05A8[])(void);

void func_8018B9DC(void *a0) {
    D_801E05A8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BA18);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BA80);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BAE4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BB50);


extern void (*D_801E05B4[])(void);

void func_8018BC3C(void *a0) {
    D_801E05B4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BC78);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BCDC);


extern void (*D_801E05BC[])(void);

void func_8018BD58(void *a0) {
    D_801E05BC[*(u16 *)((s32)a0 + 0x2)]();
}



void func_8018BD94(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BDA4);


extern void func_80184CB8(s32*, s32);
    extern short D_801E05C4;
    void func_8018BDE0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E05C4);
    }



extern void func_80184CB8(s32*, s32);
    extern short D_801E05C4;
    void func_8018BE0C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E05C4);
    }



extern void (*D_801E0690[])(void);

void func_8018BE38(void *a0) {
    D_801E0690[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BE74);

extern s32 func_8014CB1C(void);
    s32 func_8018BEE8(void) {
        return func_8014CB1C() != 0;
    }


DEFINE_func_8018BF08()  /* dedup: shared engine-core @0x8018BF08 (src/shared) */




extern void func_80178CBC(s32, s32);
    extern short D_801E0648;
    void func_8018BF34(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801E0648);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BF64);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018BFCC);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C038);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C0B0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C114);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C1E0);


extern void func_80184CB8(s32*, s32);
    extern short D_801E06A8;
    void func_8018C24C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E06A8);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C278);


extern void (*D_801E077C[])(void);

void func_8018C368(void *a0) {
    D_801E077C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801E070C;
    void func_8018C3A4(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801E070C);
    }


extern s32 func_800D0EC4();
s32 func_8018C3D0(void) {
    return func_800D0EC4() == 0;
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C3F0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C494);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C518);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C5AC);


extern void (*D_801E3AF4[])(void);

void func_8018C5FC(void *a0) {
    D_801E3AF4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C638);

DEFINE_func_8018C69C()  /* dedup: shared engine-core @0x8018C69C (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C6A4);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C6F0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C730);


extern void (*D_801E3BA4[])(void);

void func_8018C78C(void *a0) {
    D_801E3BA4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C7C8);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C7F0);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C8A8);

extern void func_8012B2CC(s32 arg);
    void func_8018C90C(void *a0) {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s16 *)(v1 + 0x12) = -0x600;
        func_8012B2CC((s32)a0);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C93C);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018C96C);


extern void (*D_801E3CEC[])(void);

void func_8018CADC(void *a0) {
    D_801E3CEC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CB18);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CB94);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CC04);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_8018CC1C(void) {
        func_8002D4C8(0x7E0, 0);
    }


INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CC40);

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CD74);

DEFINE_func_8018CDDC()  /* dedup: shared engine-core @0x8018CDDC (src/shared) */

DEFINE_func_8018CDE4()  /* dedup: shared engine-core @0x8018CDE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC04_019/nonmatchings/ov_SC04_019_jr_8017AE2C", func_8018CDEC);




