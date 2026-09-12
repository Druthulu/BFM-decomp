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
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018EB18;
extern u8 D_8018EA88;
extern u8 D_8018EA64;
extern u8 D_8018EA40;
extern u8 D_8018EAF4;
extern u8 D_8018EAD0;
extern u8 D_8018EAAC;
extern u8 D_8018EA1C;
extern void func_80145934(void);
extern u8 D_8018EBA8;
extern u8 D_8018EB84;
extern u8 D_8018EB60;
extern u8 D_8018EB3C;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
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
extern unsigned char D_8018DFA0[];
extern unsigned char D_8018DFD0[];
extern unsigned char D_8018E020[];
extern unsigned char D_8018E050[];
extern unsigned char D_8018E080[];
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
extern void (*D_8018E0D0[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_8018E198[];
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
extern u8 D_8018E220[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018E228;
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
extern int D_801F61D8;
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
extern s32 D_801F61DC;
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
extern s32 D_8018E258;
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
extern void (*D_8018E300[])(void);
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
extern void (*D_8018E324[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018E314;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018E338[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018E344[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018E354[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018E36C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018E35C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018E380[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018E39C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018E38C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018E3B0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018E3C4[])(void);
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
extern s32 D_8018E3D8;
extern void (*D_8018E400[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018E3E0;
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
extern int (*D_8018E44C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018E450[])(void);
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
extern unsigned short D_8018E8B4[];
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
extern void (*D_8018E8C4[])(void);
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
extern int D_801F6210;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018E8EC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018E8CC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018E8DC;
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
extern void (*D_8018E92C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018E934[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018E900;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018E940[])(void);
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
extern u8 D_8018E910;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801F6218;
extern s32 D_801F6224;
extern s32 D_801F6228;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018E97C[])(s32 *);
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
extern s32 D_8018E950[];
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
extern s32 D_801F6220;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018EBCC[])(void);
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
extern char D_8018E9EC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018EC70[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018EDC4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018EBE0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018EDCC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018EBF0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018EC10;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018EDD4[])(void);
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
extern void (*D_8018EDFC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018EE08[])(void);
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
extern void func_8015D01C(int param_1);
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void (*D_8018EC7C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018EEAC;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018DF90[];
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
extern unsigned char D_8018EEC0[];
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
extern s8 D_8018EEFC[];
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
extern u16 D_8018EF44;
extern u16 D_8018EF46;
extern u16 D_8018EF48;
extern s32 D_8018EF4C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018EF54;
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
extern int D_8018EC60;
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
extern unsigned int D_8018EFD8[];
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
extern void func_80160EA4(void *a0);
extern void func_80160E70(s32 *a0);
extern void (*D_8018F088[])(void);
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
extern u16 D_8018F0B8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018F11C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801F6230[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018F140[])(void);
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
extern int D_801F6288[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018F188[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018F178;
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
extern char D_801F5A20[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018F190[])(void);
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
extern void (*D_8018F1E4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern s32 D_8018F1AC;
extern s16 D_8018F1E0;
extern s16 D_8018F1DE;
extern s16 D_8018F1DC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018F1F0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801F62E8;
extern u8 D_801F62E9;
extern u8 D_801F62EA;
extern u8 D_801F62EB;
extern u8 D_801F62EC;
extern u8 D_801F62ED;
extern u8 D_801F62EE;
extern u8 D_801F62EF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018F200[])(void);
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
extern s32 D_801F6328;
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
extern void (*D_8018F244[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018F2C0[];
extern s32 D_8018F2E0[];
extern u8 D_8018F35C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018F37C[];
extern u8 D_8018F39C[];
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
extern void (*D_8018F438[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018F4B4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801F5A30;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018F4C0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018F4C8[])(void);
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
extern void (*D_8018F590[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018F5A0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018F5B0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018F5BC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018F51C[];
extern u8   D_8018F530[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
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
extern void (*D_8018F5D4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018F5DC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018F5E4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018F5EC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018F5F4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018F5FC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018F604[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018F6B8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018F6C0[])(void);
extern void func_80169F00(void *a0);
extern char D_8018F670[];
extern char D_8018F630[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018F6F8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018F704[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018F74C[])(void);
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
extern void (*D_8018F7C8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801F6648;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018F7BC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018F800[];
extern unsigned short D_8018F808[];
extern unsigned short D_8018F810[];
extern unsigned char D_801F6650[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801F6648;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018F818[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801F6784;
extern M2C_UNK D_801F6788;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801F6710;
extern void (*D_8018F848[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801F678C[];
extern u8 D_801F6794[];
extern u8 D_801F6744[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018F850[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018F86C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018F874[])(void);
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
extern void (*D_8018F8DC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018F880;
extern u8 D_8018F88C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018F910[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018F918[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018F96C[])(void);
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
extern u16 D_8018F9A0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018F990[];
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
extern s32 D_8018F9BC;
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
extern void (*D_8018FA34[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018FA3C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018FA44[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018FA4C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018FA54[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018FA5C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018FA68[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018FA74[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018FA80[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018FA90[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018FAA0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018FAA8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018FAB0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018FAB8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018FAC0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018FAC8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018FAD0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018FAD8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018FAE0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018FAE8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018FAF0[])(void);
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
extern void (*D_8018FAF8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018FB00[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018FB08[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018FB10[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018FB18[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018FB20[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018FB28[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018FB30[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018FB38[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018FB40[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018FB48[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018FB50[])(void);
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
extern void (*D_8018FB94[])(void);
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
extern M2C_UNK D_8018FB58;
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
extern void (*D_8018FBC4[])(void);
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
extern void (*D_8018FC00[])(void);
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
extern void (*D_8018FC58[])();
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
extern void func_80175184(s32* arg0);
extern void func_80175114(s32 *a0);
extern void func_80175184(s32* arg0);
extern void func_80175150(s32 *a0);
extern void (*D_8018FC68[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018FC70[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018FDD8[])();
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
extern void (*D_8018FDE4[])();
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
extern M2C_UNK D_801F5C78;
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
extern void func_80178840(int param_1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_801789AC(s32 arg0);
extern s16 D_801F7840;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801F6EC8;
extern short D_801F78B4;
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
extern s32 D_801F72F4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801F731C;
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
extern s16 D_801F72D8;
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
extern void func_8012BE98(s32, u16*);
extern s32 func_80012A60(s32 a0, s32 a1);


void func_8017AE2C(s32 param_1) {

    extern s16 D_801F7810;
    extern s16 D_801F7812;
    extern s16 D_801F781C;
    s32 pv = param_1;
    s16 *g = &D_801F7810;

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
                    func_8012B744(p, &D_801F781C);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801F7810+0xC == &D_801F781C; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_801F7810 + 0xC)) < 0x101) {
                    D_801F7810 = 0;
                    D_801F7812 = 0;
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
            func_8012B744((void *)(pv + 4), &D_801F781C);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_801F7810 + 0xC)) < 0x101) {
            D_801F7810 = 0;
            D_801F7812 = 0;
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
// @unstuck(P36): none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801F7354;
    extern s16 D_801F7356;
    extern s16 D_801F7358;
    extern s16 D_801F734C;
    extern s16 D_801F734E;
    extern s16 D_801F7350;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801F7354, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801F7356, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801F7358, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801F734C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801F734E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801F7350, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s16 D_801F72DC;
extern u16 D_801F735C;
extern u16 D_801F735E;
extern u16 D_801F7360;
extern s16 D_801F7840;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    func_8012A418();
    D_801F7840 = 0;
    D_801F72DC = 0;
    D_801F735C = D_80126B5E;
    D_801F735E = D_80126B62;
    D_801F7360 = D_80126B66;
}


// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @unstuck(P36): none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018FF20[];
    extern s16 D_801F7354;
    extern s16 D_801F734C;
    extern u8 D_8012694C;


    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_8018FF20[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018FF20[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801F7354;
        s16 *p78C = &D_801F734C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801F7840 = 1;
        D_801F72DC = 0;
    }
}



// @class: struct
// @unstuck(P36): none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801F72FC;
    extern SV4_8017B368 D_801F7304;
    extern s16 D_801F7354;
    extern s16 D_801F734C;
    extern u16 D_8018FF20;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801F72FC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801F7304;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018FF20)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018FF20)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801F7354) = loc0;
    (*(SV4_8017B368 *)&D_801F734C) = loc1;
    D_801F7840 = 1;
    D_801F72DC = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801F72FC;
    extern SV4_8017B368 D_801F7304;
    extern s16 D_801F7354;
    extern s16 D_801F734C;
    extern u16 D_8018FF20;
    extern s16 D_801F72DC;
    extern s16 D_801F7840;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801F72FC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801F7304;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018FF20)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018FF20)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801F7354) = loc0;
    (*(SV4_8017B368 *)&D_801F734C) = loc1;
    D_801F7840 = 1;
    D_801F72DC = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801F7354).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801F7354).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801F7354).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801F734C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801F734C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801F734C).c;
}


// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @unstuck(P36): 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.




s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018FF20[];
    extern s16 D_801F7354;
    extern s16 D_801F7356;
    extern s16 D_801F7358;
    extern s16 D_801F734C;
    extern s16 D_801F734E;
    extern s16 D_801F7350;
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

        src = &D_8018FF20[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018FF20[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    *(Blk8_8017B614 *)&D_801F7354 = *(Blk8_8017B614 *)&buf[0];
    *(Blk8_8017B614 *)&D_801F734C = *(Blk8_8017B614 *)&buf[8];
    func_8012A018((s32)func_8017BE60, 0);
    D_8012694C[0] = 0;
    D_801F7840 = 1;
    D_801F72DC = 0x1E;
    D_80126990 = ((SV4_8017B368 *)&D_801F7354)->a;
    D_80126994 = D_801F7356;
    D_80126998 = D_801F7358;
    D_80126984 = ((SV4_8017B368 *)&D_801F734C)->a;
    D_80126988 = D_801F734E;
    D_8012698C = D_801F7350;
    func_80129CF8();
}




// @class: plumbing
// @unstuck(P36): none — MATCH

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8 D_8012694C;
extern s16 D_801F72DC;
extern s16 D_801F7354;
extern s16 D_801F7356;
extern s16 D_801F7358;
extern s16 D_801F734C;
extern s16 D_801F734E;
extern s16 D_801F7350;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801F72DC = 0;
    D_801F7354 = (s16) D_80114F30;
    D_801F7356 = (s16) D_80114F34;
    D_801F7358 = (s16) D_80114F38;
    D_801F734C = (s16) D_80114F24;
    D_801F734E = (s16) D_80114F28;
    D_801F7350 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801F736C;
extern s16 D_801F736E;
extern s16 D_801F7370;
extern s16 D_801F7374;
extern s16 D_801F7376;
extern s16 D_801F7378;

void func_8017B824(void) {
    D_801F736C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801F736E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801F7370 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801F7374 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801F7376 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801F7378 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @unstuck(P36): none — MATCH

extern s16 D_801F736C;
extern s16 D_801F736E;
extern s16 D_801F7370;
extern s16 D_801F7374;
extern s16 D_801F7376;
extern s16 D_801F7378;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801F736C;
    D_80114F34 = D_801F736E;
    D_80114F38 = D_801F7370;
    D_80114F24 = D_801F7374;
    D_80114F28 = D_801F7376;
    D_80114F2C = D_801F7378;
}


// @class: struct
// @unstuck(P36): none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801F7354), src[8..15] -> (*(S8_8017B8E8 *)&D_801F734C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801F7354) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801F734C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @unstuck(P36): none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u16 D_801F735C;
extern u16 D_801F735E;
extern u16 D_801F7360;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801F72DC;
extern short D_801F7364;
extern short D_801F7366;
extern short D_801F7368;
extern s16 D_801F7354;
extern s16 D_801F7356;
extern s16 D_801F7358;
extern s16 D_801F734C;
extern s16 D_801F734E;
extern s16 D_801F7350;

void func_8017B940(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801F735C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801F735E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801F7360);
    (*(s16 *)&D_801F7364) = buf[0];
    (*(s16 *)&D_801F7366) = buf[1];
    (*(s16 *)&D_801F7368) = buf[2];
    D_801F7354 = D_80114F30 + buf[0];
    D_801F72DC = 0;
    D_801F7356 = D_80114F34 + buf[1];
    D_801F7358 = D_80114F38 + buf[2];
    D_801F734C = D_80114F24 + buf[0];
    D_801F734E = D_80114F28 + buf[1];
    D_801F7350 = D_80114F2C + buf[2];
}



// @class: struct
// @unstuck(P36): none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_L48: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801F72FC;
extern SV4 D_801F7304;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801F7304) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801F72FC = svec;

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
    D_801F7304 = buf1;
}


// @class: struct
// @unstuck(P36): none — MATCH (65 ins)
#include "common.h"




s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801F7304)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801F72FC) = svec;

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
    (*(SV4_8017BB34*)&D_801F7304) = buf1;
}




// @class: regalloc-order
// @unstuck(P36): pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801F7324[10])(int);

void func_8017BC38(int param_1)
{
    int i;
    void (**p)(int);

    i = 0;
    p = D_801F7324;
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
// @unstuck(P36): none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);
extern s16 D_801F72DC;
extern s16 D_801F7840;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801F72DC = D_801F72DC + 1;
    if (D_801F72DC >= 0x1F) {
        D_801F7840 = 2;
    }
}




// @class: plumbing
// @unstuck(P36): none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801F72DC;
extern s16 D_801F7840;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801F72DC = D_801F72DC + 1;
    if (0x18 < D_801F72DC) {
        func_8012A4BC();
        D_801F7840 = 0;
    }
    return;
}




// @class: regalloc-order
// @unstuck(P36): none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801F72DC;
extern void (*D_801F7320)(void);
extern short D_801F7364;
extern short D_801F7366;
extern short D_801F7368;
extern s16 D_801F7840;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801F72DC = D_801F72DC + 1;
    if (D_801F72DC >= 0x19) {
        if (D_801F7320 != 0) {
            (*D_801F7320)();
        } else {
            D_80114F30 = D_80114F30 + D_801F7364;
            D_80114F34 = D_80114F34 + D_801F7366;
            D_80114F38 = D_80114F38 + D_801F7368;
            D_80114F24 = D_80114F24 + D_801F7364;
            D_80114F28 = D_80114F28 + D_801F7366;
            D_80114F2C = D_80114F2C + D_801F7368;
            func_8012A4BC();
        }
        D_801F7840 = 0;
    }
}



extern void (*D_8018FFC0[])(void);

void func_8017BE60(void *a0) {
    D_8018FFC0[*(u8 *)((s32)a0 + 0x4)]();
}


#include "../shared/ov/func_8017BE9C__76785405.h"

#include "../shared/ov/func_8017BEA4.h"

#include "../shared/ov/func_8017BEAC.h"

#include "../shared/ov/func_8017BEB4.h"


extern void (*D_8018FFE4[])(void);

void func_8017BEBC(void *a0) {
    D_8018FFE4[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017BEF8(s32 param_1) {

    extern u8 D_8018FFCC;
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

    node = func_800D222C(param_1, &D_8018FFCC, 0xFD);
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


#include "../shared/ov/func_8017C0BC.h"


extern void (*D_8018FFEC[])(void);

void func_8017C150(void *a0) {
    D_8018FFEC[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @unstuck(P36): none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018FFD8;

void func_8017C18C(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018FFD8, 0x18);
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


#include "../shared/ov/func_8017C230.h"


/* func_8017C294 — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801F7380..D_801F73A8 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017C294(s32 param_1, s32 param_2)
{

    extern s32 D_801F7380;
    extern s32 D_801F7384;
    extern s32 D_801F7388;
    extern s32 D_801F7390;
    extern s32 D_801F7394;
    extern s32 D_801F7398;
    extern s32 D_801F73A0;
    extern s32 D_801F73A4;
    extern s32 D_801F73A8;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_8017C294 vec;                              /* sp+0x10 */
    MTX_L_8017C294 mtx;                              /* sp+0x18 */
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

    D_801F73A0 = vec.a;
    D_801F7390 = vec.a;
    D_801F7380 = vec.a;
    D_801F73A4 = vec.b;
    D_801F7394 = vec.b;
    D_801F7384 = vec.b;
    D_801F73A8 = vec.c;
    D_801F7398 = vec.c;
    D_801F7388 = vec.c;
}



/* func_8017C3C4 — ov_SC02_027_jr_8017AE2C (227 ins).  MATCH (match_one, 227/227).
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
 *   D_801F7380     TU:3333      extern s32 D_801F7380;
 * func_8012CAE4 / func_8012C354 are absent from the TU; the canonical engine_core.h forms
 * are reused verbatim (DEFINE_func_8012CAE4 @15355 `void func_8012CAE4(void *a0)`,
 * DEFINE_func_8012C354 @15748 `s32 func_8012C354(s32 a0, s32 a1)`).
 * D_8019001C / D_80190058 / D_801E91B4 / every D_801D9E9x-ECx / D_801F7430 appear nowhere
 * in the TU or engine_core.h (only D_801F7380..EB8 and D_801D9F00..F06 are declared there).
 * D_801E91DC is declared BLOCK-SCOPE here on purpose: the TU's only other declaration
 * (TU:3587, `extern Rec_8017C738 D_801E91DC[];`) is itself block-scope inside func_8017C738,
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
 *  2. `tbl` and `tbl2` MUST BE TWO SEPARATE LOCALS.  One shared `tbl` gives the D_801F7430
 *     address pseudo REG_N_SETS==2, which KILLS the birthing boost (birthing_insn_p,
 *     sched.c:2469/2490): the unboosted `la $a0` then floats to the front of the pri-1 group
 *     and lands at index 86, shoving `la $a2,D_801E91DC` to 88 (this was the entire 7-insn
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



void func_8017C3C4(s32 a0) {

    extern u8 D_8019001C[];
    extern u8 D_80190058[];
    extern s32 D_801E91B4;
    extern u16 D_801152BA;
    extern s16 D_80115214;
    extern s32 D_801F7380;
    extern u8 D_801F738C;
    extern u8 D_801F738D;
    extern u8 D_801F738E;
    extern u8 D_801F739C;
    extern u8 D_801F739D;
    extern u8 D_801F739E;
    extern u8 D_801F73AD;
    extern u8 D_801F73AE;
    extern u8 D_801F73B0;
    extern u8 D_801F73B1;
    extern u8 D_801F73B2;
    extern u8 D_801F73B4;
    extern u8 D_801F73B5;
    extern u8 D_801F73B6;
    extern u8 D_801F73BC;
    /* 9 x 12-byte records = 0x6C bytes, alignment 2 */
    extern Blk027_8017C3C4 D_801E91DC;
    extern Blk027_8017C3C4 D_801F7430[];

    u8 *v1;
    s32 s1;
    u8 *p;
    s32 t;
    s16 i;
    Blk027_8017C3C4 *dst;
    Blk027_8017C3C4 *tbl2;
    s32 idx;
    Blk027_8017C3C4 *tbl;
    s32 u;
    s32 w;

    v1 = *(u8 **)(a0 + 0xDC);
    if ((func_800291B4(v1[0] + 0x3A) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    if (*(s32 *)(a0 + 0x20) == 0) {
        if (func_8012C354(a0, (s32)D_8019001C) == 0) {
            return;
        }
        func_8001C810(*(s32 *)(a0 + 0x20), (s32)&D_801E91B4);
        func_8012A828(a0, (void *)&D_80190058[(s16)D_801152BA * 16]);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x20;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)&D_801F7380;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)(a0 + 0xAE) = -3;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 == 0) {
        return;
    }

    p = &D_801F73B0;
    *(s32 *)(a0 + 0xCC) = s1;
    func_8001CD50(s1, (s32)p);

    D_801F73B2 = 0x80;
    *p = 0x80;
    D_801F73B1 = 0xE0;
    D_801F73B5 = 0;
    D_801F73B4 = 0;
    D_801F73B6 = 0;
    func_800233CC(p, 0x38);

    tbl = D_801F7430;
    idx = (s16)D_801152BA;
    dst = &tbl[idx];
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x8) = *(u16 *)(a0 + 0x6);
    t = *(u16 *)(a0 + 0xA) - 4;
    *(u16 *)(a0 + 0xA) = t;
    *(s16 *)(s1 + 0xA) = t;
    *(s16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(s1 + 0x4) |= 0x50000000;

    D_801F73AE = 0xFF;
    D_801F73BC = 0xFF;
    D_801F739E = 0xFF;
    D_801F739C = 0xFF;
    D_801F738E = 0xFF;
    D_801F738C = 0xFF;
    D_801F73AD = 0x80;
    D_801F739D = 0x80;
    D_801F738D = 0x80;

    *dst = D_801E91DC;

    i = 5;
    tbl2 = D_801F7430;
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
 *   func_8017C294  TU:3465/3542 (void return)
 *   D_80115214     TU:3547
 * func_8012BD14 / D_80190050 / D_801900B4 appear nowhere in the TU; the
 * canonical engine_core.h form of func_8012BD14 is `void func_8012BD14(s32)`
 * (DEFINE_func_8012BD14), so it is declared void and the s32 return is taken
 * through a cast at the call site (idiom 9). */
extern s32 func_800291B4(s32 arg);
extern s16 currentLocationId;
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_801746A4(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017C294(s32 param_1, s32 param_2);
extern void func_8012BD14(s32 a0);

void func_8017C750(s32 a0) {

    extern u8 D_80126B5C;
    extern u8 D_801202A0[];
    extern u16 D_80126B62;
    extern s16 D_80115214;
    extern u8 D_80190050[];
    extern u8 D_801900B4[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_800B99DA;
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
    func_8017C294(a0, rand_val & 0xF);

    if (*(u16 *)(a0 + 0x5E) != 0) {
        for (i = 0; (u16)i < 8; i++) {
            if (*(u16 *)(a0 + 0x5E) == D_80190050[i]) {
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
        func_80178B18(a0, (s32)D_801900B4);
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
 * in the .s are D_801F75F4/108/10C, with $s0 = D_801F75F4 - 0x14. */

void func_8017C9C8(s32 a0) {

    extern u8 D_801F73F0;
    extern u8 D_801F73F1;
    extern u8 D_801F73F2;
    extern u8 D_801F73F4;
    extern u8 D_801F73F5;
    extern u8 D_801F73F6;
    extern s32 D_801F75F4[];
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801F73F0;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801F73F1 = 0xFF;
    D_801F73F2 = 0xFF;
    *p = 0xFF;
    D_801F73F6 = 8;
    D_801F73F4 = 8;
    D_801F73F5 = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801F75F4[0] = sp[0];
    D_801F75F4[1] = sp[1];
    D_801F75F4[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801F75F4[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801F75F4[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017C294(s32 param_1, s32 param_2);

void func_8017CB10(s32 a0) {
    extern Rec_8017C738_8017CB10 D_801E91DC[];

    Rec_8017C738_8017CB10 *q = D_801E91DC;
    Rec_8017C738_8017CB10 *p = *(Rec_8017C738_8017CB10 **)(a0 + 0xD8);
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
        func_8017C294(a0, 0);
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



extern void (*D_80190104[])(void);

void func_8017CC90(void *a0) {
    D_80190104[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017CCCC(void) {
    func_8014BCEC((s32)&D_80126B58, 0x5);
    func_8014BD24((s32)&D_80126B58, 0x270F);
    func_8002D4C8(0xBFE, 0);
}




extern s16 func_80128CFC(u16 a0);
extern void func_8017C294(s32 param_1, s32 param_2);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);


#include "../shared/ov/func_8017CD18.h"



#include "../shared/ov/func_8017CE0C__0dc7d970.h"




extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);

void func_8017CE8C(s32 a0) {
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

void func_8017CF40(s32 a0) {
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

void func_8017CFAC(s32 a0) {
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


extern void func_8012C218(void*);
void func_8017D038(void) {
    ((void (*)(void))func_8012C218)();
}




#include "../shared/ov/func_8017D058__2a8e3f10.h"


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017D0AC(void *a0) {
    func_80146A6C(0x19, a0, 0, 0, 0, 0, 1);
}



extern void (*D_8019015C[])(void);

void func_8017D0E8(void *a0) {
    D_8019015C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017D124(void *a0)
{
    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        func_80147324(*(u16 *)((s32)a0 + 0x2E));
    }
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



// @class: plumbing
// @unstuck(P36): none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

#include "../shared/ov/func_8017D174__63f2a03f.h"



/* Entity record touched by func_8017D1D0 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */

extern void func_80147324(s32 arg0);
extern void func_8017D408(int);

#include "../shared/ov/func_8017D1D0__4cb1b80e.h"




/* func_8017D254 — entity tick with a two-mode "hit/shake" arm.
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
extern void func_8017D408(int);

#include "../shared/ov/func_8017D254__6005a281.h"


extern void func_8017D408(int);
extern void func_80146C3C(void);
#include "../shared/ov/func_8017D3BC__ba800c4d.h"




/* func_8017D408 — 4-point primitive sweep driven by the 44-byte curve table
 * D_80190130.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_8017D408(int param_1)
{

    extern u16 D_800B99DA;
    extern u8  D_80190130[];
    SVec8_8017C218_8017D408 rot;
    s32   pad0[2];
    Prim_8017C218_8017D408  prim;
    s32   pad1[1];
    Mtx_8017C218_8017D408   mtx;
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

    p = D_80190130;
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
    p = D_80190130;
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
        p = D_80190130;
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



extern void (*D_80190170[])(void);

void func_8017D714(void *a0) {
    D_80190170[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80147324(s32 arg0);
void func_8017D750(void *a0)
{
    func_80147324(*(u16 *)((s32)a0 + 0x2E));
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}



/* func_8017D790 — a state-tick: bump the frame counter at 0x1C; while it is
 * below 0xC spin the angle at 0x12 by 0xE0, otherwise reset the counter, zero
 * the vector at *(0x34)+0x60/0x64, set +0x62 to 0x3000 and advance the state
 * word at 0x02.  Falls through to ((void (*)(void *))func_8017D408)(a0) on both arms (the target
 * leaves $a0 untouched, so the call needs no move).
 *
 * §71 sibling-first: func_8017C560 (same TU, 4 bytes earlier) is the same
 * `*(u16 *)(a0 + 2) += 1` idiom, and func_8017D408's own prologue reads
 * `lw $s1, 0x34($s2)` / `lhu $v0, 0x12($s2)` — same record, same widths.
 */

extern void func_8017D408(int);

#include "../shared/ov/func_8017D790__42dfaf58.h"



/* func_8017D800 — small entity tick:
 *   read counter @0x1C and the sub-object pointer @0x34 up-front, bump the
 *   counter unconditionally (gcc puts that store in the beqz delay slot),
 *   then either slide @0x2A down by 0x10 or run the 3-call teardown. */

extern void func_80147324(s32 arg0);
extern void func_80147084(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_8017D408(int);

#include "../shared/ov/func_8017D800__263d9dd9.h"



extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017D408(int);

#include "../shared/ov/func_8017D88C__5e749510.h"


extern void func_8017D408(int);
extern void func_80146C3C(void);
#include "../shared/ov/func_8017D960__c5477afd.h"



extern void (*D_80190184[])(void);

void func_8017D9B4(void *a0) {
    D_80190184[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017D9F0 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
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

#include "../shared/ov/func_8017D9F0__0eb8e2b4.h"


extern void func_800D22E4(s32 a0);
extern void func_80146C3C(void);
extern void func_8017DB00(void *a0);
#include "../shared/ov/func_8017DAA4__afe985ed.h"




#include "../shared/ov/func_8017DB00__5f7aa778.h"


extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012CAE4(void *a0);
extern s32  func_8012C354(s32 a0, s32 a1);
extern s32  func_80143970(s32 a0);

/* --- overlay-local data; none of these are declared anywhere in the TU. --- */

void func_8017DC70(void *a0) {

    extern u8 D_80078E78[];
    extern s16 D_801F7600;
    extern u8  D_80190450[];
    extern u8  D_80190324[];
    extern u8  D_8019018C[];
    extern u8  D_80190358[];
    extern s32 D_801F7604;
    extern s32 D_801F7608;
    /* §17 base-pointer cache: the D_80078E78 base is read ONCE at +0x1A but the original
       still pinned it in callee-saved $s1 across the first call -- that only happens when
       the base is a pointer LOCAL, not a direct D_80078E78[0x1A] (which folds %lo per use). */
    u8 *p = D_80078E78;
    s32 t;

    if ((u8)func_80029178(D_80190450[*(s16 *)((s32)a0 + 0x70)]) != 0 ||
        (*(s16 *)((s32)a0 + 0x70) == 4 && (u32)func_80029504() < 0xC8)) {
        func_8012CAE4(a0);
        return;
    }

    t = *(u16 *)(p + 0x1A);
    if (t < 0x12C || t > 0x527) {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_80190324) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x5C) |= 0x10;
        func_8012A828((s32)a0, D_8019018C);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)&D_801F7600 = *(s16 *)((s32)a0 + 0x88) << 16;
        D_801F7604 = *(s16 *)((s32)a0 + 0x8A) << 16;
        D_801F7608 = *(s16 *)((s32)a0 + 0x8C) << 16;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    } else {
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            return;
        }
        if (func_8012C354((s32)a0, (s32)D_80190358) == 0) {
            return;
        }
        *(s16 *)((s32)a0 + 0xAE) = -4;
        *(s32 *)((s32)a0 + 0xCC) = func_80143970((s32)a0);
        *(u16 *)((s32)a0 + 0x2) = 7;
    }
}


extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017E5C0(s32 a0, s16 a1, s16 a2);
extern void func_8017E634(s16 *a0);
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
void func_8017DE0C(s32 a0) {

    extern void (*D_80190214[])(void);
    extern s16 D_801F7600;
    extern s32 D_801F760C;
    extern s32 D_801F7614;
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

        func_8012A828(a0, (void *)&D_80190214);

        t = *(u16 *)(a0 + 0x10A) + 1;
        *(u16 *)(a0 + 0x10A) = t;

        if ((t & 3) != 0) {
            if (*(s16 *)(a0 + 0x104) == 0) {
                s32 r = rand();
                s32 x;
                s32 y;

                x = *(s16 *)(a0 + 0x88) - 0x200;
                x += (r & 0x7F) << 3;
                D_801F760C = x << 16;

                y = *(s16 *)(a0 + 0x8C) - 0x200;
                y += (u32)(r & 0x7F00) >> 5;
                D_801F7614 = y << 16;
            } else {
                func_8017E634((s16 *)a0);
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0xC00;
            }
        } else {
            for (i = 0; i < 2; i++) {
                ((s32 *)&D_801F760C)[i] = ((s32 *)&D_801F7600)[i];
            }
        }

        i = 8;
        if (*(s16 *)(a0 + 0x108) >= 0xD) {
            i = 2;
        }

        ret = func_8012BB3C(a0 + 4, (s32)&D_801F760C,
                            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), i);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + ret;

        ang = -3 - *(u16 *)(a0 + 0x104);
        func_8017E5C0(a0, ang, 0x50);

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
extern void func_8017E710(s32 a0);
extern void func_8017E5C0(s32 a0, s16 a1, s16 a2);
extern void func_8017E634(s16 *a0);

void func_8017E010(s32 a0) {

    extern u8 D_8019018C[];
    extern s32 D_801F760C;
    extern s32  D_801903F4;
    /* §135-6 dead locals: the target frame is 0x50 = args(0x20, func_80146A6C takes 7)
       + var(0x20) + gp(0x10).  Only 0x10 of that 0x20 is claimed -- by two phantom reload
       slots (the sign extensions of the 0x106 and 0x104 halfwords, which combine folds into
       `lh` while the pseudos keep stale ref counts) -- so the original carried 16 bytes of
       locals it no longer uses.  Without this the frame lands at 0x40. */
    s32 dead[4];
    u16 flags;
    s32 v;
    s16 ret;
    s16 spd;
    s32 m;

    ret = 0;
    /* `flags` is a u16 (only its low 16 bits are ever tested): the copy into it is a
       HImode SUBREG move that cse's (set REG0 REG1) swap cannot take, so the call result
       stays its own local pseudo -- the first test reads it straight from $v0 while the
       saved copy lives in $s1 (`move s1,v0; andi v0,v0,0x6000`). */
    flags = ((s32 (*)(s32))func_8012CBA4)(a0);

    /* `m` blocks fold_truthop from merging the two bitfield tests below into a single
       `andi $v1,$s1,0xe000` -- the target keeps `& 0x8000` and `& 0x6000` separate. */
    if ((flags & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)a0);
        func_8017E710(a0);
        if (*(s32 *)(a0 + 0x1C) >= 9) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 8;
        }
    }

    m = flags & 0x8000;
    if (m != 0 || (flags & 0x6000) != 0x2000) {
        if (*(s16 *)(a0 + 0x106) == 0) {
            *(s16 *)(a0 + 0x106) = 0x111;
        }
        if (*(s32 *)(a0 + 0x1C) >= 5) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 4;
        }
        *(u16 *)(a0 + 0x108) = *(u16 *)(a0 + 0x108) + 1;
    } else {
        *(s16 *)(a0 + 0x106) = 0;
    }

    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v != 0) {
        if ((v & 3) == 0) {
            if (func_8012BC60((void *)(a0 + 4), (void *)&D_801F760C) < 0x900) {
                *(s32 *)(a0 + 0x1C) = 1;
            }
        }
        /* The func_8017E5C0 call is written in BOTH arms on purpose: gcc-2.7.2's sched1
           interleaves the $a0/$a2 arg setup into each arm's load-delay slots, and only
           then does cross-jumping merge the common tail (it stops at the differing `sh`).
           A single call after the if/else leaves those slots as nops (+2 ins, -1 length)
           and forces the arm pointer into $a0, wrecking the whole block's allocation.
           `ang0`/`ang1` are per-arm locals (§136 L1): one shared local becomes a GLOBAL
           allocno (2 deaths) and loses $a1.  Both must be s32 -- writing the expression
           inline lets convert_to_integer narrow it to UNSIGNED HImode (the u16 operand),
           which emits `ori $a1,$zero,0xfffd` instead of `addiu $a1,$zero,-0x3` + sll/sra. */
        if (*(s16 *)(a0 + 0x106) == 0) {
            s32 r = func_8012BB3C(a0 + 4, (s32)&D_801F760C,
                                  *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 8);
            s32 p = *(s32 *)(a0 + 0x20);
            s32 ang0;
            *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang0 = -3 - *(u16 *)(a0 + 0x104);
            func_8017E5C0(a0, ang0, 0);
        } else {
            s32 q = *(s32 *)(a0 + 0x20);
            s32 ang1;
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + *(s16 *)(a0 + 0x106);
            ang1 = -3 - *(u16 *)(a0 + 0x104);
            func_8017E5C0(a0, ang1, 0);
        }
        if (*(s16 *)(a0 + 0x104) != 0) {
            if ((u32)*(s32 *)(a0 + 0x94) < 0xB) {
                *(s32 *)(a0 + 0x94) = *(s32 *)(a0 + 0x94) + 1;
            }
            if ((*(s32 *)(a0 + 0x1C) & 7) == 0) {
                ret = 1;
            }
        }
    } else {
        s16 t;

        func_8012B200((u8 *)a0);
        func_8012A828(a0, D_8019018C);
        *(s32 *)(a0 + 0x1C) = 0x14 - (*(s16 *)(a0 + 0x104) << 1);
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x23FFF) {
            *(s16 *)(a0 + 0x102) = 0xA - *(u16 *)(a0 + 0x104);
        } else {
            *(s16 *)(a0 + 0x102) = 0;
        }
        t = *(s16 *)(a0 + 0x104);
        if (t != 0) {
            t = t - 4;
            *(s16 *)(a0 + 0x104) = t;
            if (t < 0) {
                *(s16 *)(a0 + 0x104) = 0;
            }
        }
        *(s16 *)(a0 + 0x2) = 1;
    }

    if (*(s16 *)(a0 + 0xFC) != 0) {
        if (func_8016F1AC() != 0) {
            /* §17/idiom-7: 0x801891F4 is INTERIOR to D_801891D8 and has no symbol, but the
               target does NOT build it with its own %hi/%lo -- it derives it from the
               D_801903F4 base already in $a2 (`addiu $a1,$a2,-0x1C`).  Caching the base in
               a POINTER LOCAL reproduces that; `(s32)&D_801903F4 - 0x1C` folds into a
               second lui/addiu pair and splits the store into lui+sw($at). */
            s32 *tbl = &D_801903F4;

            *(s16 *)(a0 + 0x10A) = 0;
            *tbl = *(u16 *)(a0 + 0x88) | (*(s16 *)(a0 + 0x8C) << 16);
            func_80178B70(a0, (s32)tbl - 0x1C);
            *(s16 *)(a0 + 0x98) = 0;
            *(s32 *)(a0 + 0x1C) = 0x14;
            func_8012B200((u8 *)a0);
            *(s16 *)(a0 + 0x2) = 3;
        }
        return;
    }

    if (*(u16 *)(a0 + 0x5E) != 0) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(a0 + 0x62);
        func_8017E5C0(a0, -0xF, 0);
        func_8017E634((s16 *)a0);
        *(s16 *)(a0 + 0x5E) = 0;
        *(s16 *)(a0 + 0x104) = 0xA;
        ret = 1;
    } else {
        s32 d = ((s32 (*)(s32))func_8012BD14)(a0);

        if (d <= 0xFFFF) {
            spd = 0;
            if (d >= 0x4000) {
                spd = (func_8012BDBC(a0, 0x500) != 0) << 2;
            } else if (d >= 0x1000) {
                if (func_8012BDBC(a0, 0x680) != 0) {
                    spd = 7;
                }
            } else {
                spd = 9;
            }
            if (spd != 0) {
                func_8017E634((s16 *)a0);
                if (*(s16 *)(a0 + 0x104) == 0) {
                    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B864(a0) - 0x800;
                    ret = 1;
                }
                *(s16 *)(a0 + 0x104) = spd;
                func_8017E5C0(a0, -7 - spd, 0);
            }
        }
    }

    /* `ret` is a short: the test sign-extends it, combine reduces the extension of a 0/1
       value to a plain copy (`move v0,s2`, which reorg also puts in the two delay slots). */
    if (ret != 0) {
        func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0);
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


void func_8017E404(s32 a0) {

    extern u8 D_8019018C[];
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
    func_8012A828(a0, D_8019018C);

    *(s16 *)(a0 + 0x104) = 0;
    *(s16 *)(a0 + 0x102) = 0xA;
    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 4) |= 0x80000000;

    func_801439C0(*(s32 *)(a0 + 0xCC));

    *(s32 *)(a0 + 0x1C) = 0x14;
    *(s16 *)(a0 + 0x2) = 6;
}


extern void (*D_80190460[])(void);

void func_8017E584(void *a0) {
    D_80190460[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_8017E5C0 -- ov_SC03_002 / ov_SC03_002_jr_8017AE2C
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

void func_8017E5C0(s32 a0, s16 a1, s16 a2) {
    u32 xz;

    func_8012B0B4(&xz, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), a1 << 4);

    *(s32 *)(a0 + 0x10) = (s16)xz << 12;
    *(s32 *)(a0 + 0x18) = ((s32)xz >> 16) << 12;
    if (a2 != 0) {
        *(s32 *)(a0 + 0x1C) = a2;
    }
}


extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_8017E634(s16 *a0) {

    extern u8 D_80126B5C;
    extern s16 D_801F7600;
    extern s32 D_801F760C;
    extern s32 D_801F7614;
    extern u8 D_8019038C[];
    extern s16 D_801903AC[];
    extern s16 D_801903AE[];
    /* The target frame is 0x28 with only $s0/$s1/$ra saved at 0x18/0x1C/0x20, i.e. 8 bytes
       of locals sit below the register save area and are never touched. The original source
       declared a local it no longer uses; the same fossil is visible in the neighbours
       (func_8017C594 carries 16 such bytes). gcc-2.7.2 still reserves the slot. */
    s32 sp10[2];
    s32 a, b, t, r, off, x, y;

    a = (func_8012B6D4((s16 *)&D_80126B5C, &D_801F7600) >> 7) & 0x18;
    b = func_8012B6D4(a0 + 2, &D_801F7600);
    t = a | ((b >> 9) & 7);
    off = D_8019038C[t] << 2;
    r = rand();

    /* The struct reads are plain INDIRECT_REFs, not ARRAY_REFs: an `a0[0x46]` here sets
       MEM_IN_STRUCT_P, which lets gcc-2.7.2's true_dependence() drop the dependence against
       the constant-address store and hoist the second `lh` above `sw D_801F760C`. */
    x = *(s16 *)((s32)a0 + 0x88) + *(s16 *)((u8 *)D_801903AC + off) - 0x100;
    x += (r & 0x7F) << 2;
    D_801F760C = x << 16;

    y = *(s16 *)((s32)a0 + 0x8C) + *(s16 *)((u8 *)D_801903AE + off) - 0x100;
    y += (unsigned)(r & 0x7F00) >> 6;
    D_801F7614 = y << 16;
}




/* func_8017E710 -- ov_SC02_011 / ov_SC02_011_jr_8017AE2C   [target: 133 ins]
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


void func_8017E710(s32 a0) {
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern s32  ratan2(s32 a0, s32 a1);
    extern s16  D_801152B0;
    extern s16  D_801152B4;
    extern s32  func_80133784(s32 a0, void *a1, s32 a2);
    extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void RotMatrixY(s32 a0, void *a1);
    extern Mtx8_8017DE10_8017E710 D_800AE620;

    u8 in[8];
    u8 out[8];
    Mtx8_8017DE10_8017E710 m;
    s32 base;
    s32 ang;
    s16 arg;
    s32 d;

    *(s16 *)(in + 0) = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x12);
    *(s16 *)(in + 2) = *(u16 *)(a0 + 0xA) + 8;
    *(s16 *)(in + 4) = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x1A);
    *(s16 *)(out + 0) = *(u16 *)(a0 + 0x6);
    *(s16 *)(out + 2) = *(u16 *)(a0 + 0xA) + 8;
    *(s16 *)(out + 4) = *(u16 *)(a0 + 0xE);
    if ((func_80133784(1, &in[0], (s32)&out[0]) & 0xC000) != 0) {
        base = ratan2(D_801152B0, D_801152B4) & 0xFFF;
        ang = ratan2(*(s32 *)(a0 + 0x10), *(s32 *)(a0 + 0x18)) & 0xFFF;
        d = ang - base;
        d <<= 16;
        if (d < 0) {
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
        d = (s16)*(u16 *)(out + 4) >> 1;
        *(s16 *)(out + 4) = *(u16 *)(a0 + 0xE) + d;
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

void func_8017E924(s32 a0) {

    extern u8 D_8019027C[];
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
        func_8012A828(a0, D_8019027C);

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

void func_8017E9F8(s32 a0) {

    extern void (*D_80190214[])(void);
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
    func_8012A828(a0, (void*)&D_80190214);

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

void func_8017EAC8(s32 a0)
{

    extern u8 D_80190450[];
    if (func_80178970() == 0) return;

    ((void (*)(s32))func_80178D18)(a0);

    func_80029124((s32)D_80190450[*(s16 *)((s32)a0 + 0x70)], 1);
    ((void (*)(s32))func_8012C218)(a0);
}



extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_8012E778(s32 param_1, s32 param_2);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_801439C0(s32 a0);
extern void func_8012C218(void*);

void func_8017EB20(s32 a0)
{

    extern u8 D_80078E78[];
    extern s32 D_80190430;
    s32 s0 = a0;
    u8 *v1 = D_80078E78;
    s32 v0;

    if (*(s16 *)((u8 *)s0 + 0x100) != 0) {
        goto L_8017D524;
    }

    if (*(u16 *)((u8 *)s0 + 0x5E) == 0) {
        goto L_8017D524;
    }

    func_80178B18(s0, (s32)&D_80190430);
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

void func_8017EC18(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 7;
    }
}



extern void (*D_80190534[])(void);

void func_8017EC58(void *a0) {
    D_80190534[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);
void func_8017EC94(s32 a0) {

    extern u8 D_80190484;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_80190484);
    func_80171990((u8 *)a0);
}


extern s32 func_80171990(u8 *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147324(s32 arg0);

void func_8017ECD4(arg0)
void *arg0;
{
    if (*(u16 *)((s32)arg0 + 0xB8) & 0x4000) {
        *(s32 *)((s32)arg0 + 0x44) |= 0x20000;
        func_801466F0(0x16, (s32)arg0, 0, -0x80, -0x10, 0, 0, 0);
        func_80147324(0x7BC);
        func_80171990((u8 *)arg0);
    }
}


void func_8017ED50(s32 a0)
{
    if (func_8014C088(a0, 0x16) == 0)
    {
        *(s32 *)(a0 + 0x44) &= ~0x20000;
        func_8014B5C4((s32 *)a0, func_8014CB58() & 0xFF, 0x80);
        func_80171990((u8 *)a0);
    }
}


void func_8017EDB0(void) {
}

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
    extern s32 D_8019052C;
    void func_8017EDB8(void) {
        ((void (*)(void *, s32))func_8016EE40)(&D_8019052C, 0x1000000);
    }


















extern s32 D_80126D54;
extern s32 D_8019052C;
s32 func_8017EDE0(void)
{
  int new_var2;
  int new_var;
  new_var2 = (new_var = 0);
  return ((u32) (D_80126D54 ^ ((u32) (&D_8019052C)))) == new_var;
  new_var = 0x1;
 do { } while (new_var2); do { } while (0);
}

    s32 func_8017EDFC(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_80126B0C;
        return D_80126B0C;
    }


    extern void (*D_8019057C[])(void);
    extern void func_80162D28(s32*);
    void func_8017EE0C(void *a0) {
        D_8019057C[*(u16 *)((s32)a0 + 0x2)]();
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            ((void (*)(void *))func_80162D28)(a0);
        }
    }



extern void func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);

void func_8017EE6C(s32 a0) {

    extern s32 D_801F1068;
    extern s16 D_80190578;
    extern s16 D_80190576;
    extern s16 D_80190574;
    s32 iVar1;
    s32 iVar2;

    iVar1 = *(s32 *)(a0 + 0x4C);
    iVar2 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001C214(iVar2, (s32)&D_801F1068);
        *(u16 *)(iVar2 + 0x10) = 0x800;
        *(u16 *)(a0 + 0x60) = 0;
        func_80149374(iVar1, a0 + 4);
        func_80146DE8((s32 *)a0, 0, 0xFFC00000, 0);
        D_80190578 = 0x80;
        D_80190576 = 0x80;
        D_80190574 = 0x80;
        func_80146CA0((void *)a0);
        if (*(s32 *)(a0 + 0x50) == 0) {
            *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0x10;
        }
    }
}


extern void func_8001C810(s32 a0, s32 a1);
extern void func_8013C9C4(void * arg0);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_80162FC0(s32 *a0);
extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017EF38(s32 a0) {
    extern u8 D_8019058C[];
    extern s32 D_801F16C0;
    extern s32 D_80190544;

    s32 iVar1;
    s32 iVar2;
    s16 sVar1;

    iVar1 = *(s32 *)(a0 + 0x4c);
    iVar2 = *(s32 *)(a0 + 0x20);
    func_8016325C(a0, 0, 0x20000, 0);
    func_80162FC0((s32 *)a0);
    if ((*(s16 *)(a0 + 0x60) == 0) && (0 < *(s32 *)(a0 + 0x28))) {
        u16 uVar1;
        *(u16 *)(iVar2 + 0x10) = 0;
        uVar1 = *(u16 *)(a0 + 0x60);
        *(u16 *)(a0 + 0x60) = uVar1 + 1;
    }
    sVar1 = *(s16 *)(iVar1 + 0xA);
    if (sVar1 < *(s16 *)(a0 + 0xA)) {
        u16 uVar1;
        s32 uVar2;
        *(s16 *)(a0 + 0xA) = sVar1;
        func_8013C9C4(D_8019058C);
        *(u16 *)(a0 + 0x60) = *(u16 *)(iVar2 + 0x18);
        func_8001C810(iVar2, (s32)&D_801F16C0);
        *(s32 **)(iVar2 + 0x80) = &D_80190544;
        *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0xA0;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        uVar1 = *(u16 *)(a0 + 0x60);
        *(u16 *)(iVar2 + 0x1c) = uVar1;
        *(u16 *)(iVar2 + 0x1a) = uVar1;
        *(u16 *)(iVar2 + 0x18) = uVar1;
        if (*(s32 *)(a0 + 0x50) == 0) {
            *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0x10;
            func_801466B4(0x1B, a0, 0, 0, 1);
            func_801466B4(0x1B, a0, 1, 0, 1);
            func_801466B4(0x1B, a0, 2, 0, 1);
            func_801466B4(0x1B, a0, 3, 0, 1);
            uVar2 = 0x81D;
        } else {
            uVar2 = 0xC5E;
        }
        func_80147324(uVar2);
        func_80146CA0((void *)a0);
    } else if (*(s16 *)(a0 + 0x60) != 0) {
        s16 sVar2;
        sVar2 = *(u16 *)(iVar2 + 0x1c) + 0x100;
        *(s16 *)(iVar2 + 0x1c) = sVar2;
        *(s16 *)(iVar2 + 0x1a) = sVar2;
        *(s16 *)(iVar2 + 0x18) = sVar2;
    }
}


void func_8017F104(void) {
    extern u16 D_80190578;
    extern s16 D_80190576;
    extern s16 D_80190574;
    extern void func_80146CA0(void *a0);
    s16 sVar1;

    sVar1 = D_80190578 + 8;
    D_80190578 = sVar1;
    D_80190576 = sVar1;
    D_80190574 = sVar1;
    if (sVar1 >= 0x101) {
        ((void (*)(void))func_80146CA0)();
    }
}


extern s16 D_80190574;
extern s16 D_80190576;
extern s16 D_80190578;
extern void func_80162CCC(void);

void func_8017F160(void) {
    extern s16 D_80190578;
    extern s16 D_80190576;
    extern s16 D_80190574;
    s16 sVar1;

    sVar1 = D_80190578 - 8;
    D_80190578 = sVar1;
    D_80190576 = sVar1;
    D_80190574 = sVar1;
    if (sVar1 < -0x80) {
        func_80162CCC();
    }
}


    extern void func_8017F454();  // K&R: 0 of 1 args (P37 rung D t4_D2)
    extern void (*D_801905C0[])(int);
    extern void func_80162D28(s32*);
    void func_8017F1BC(int param_1)
    {
        func_8017F454();
        D_801905C0[*(unsigned short *)(param_1 + 2)](param_1);
        if (*(s32 *)(param_1 + 0x20) != 0) {
            ((void (*)(int))func_80162D28)(param_1);
        }
    }


extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80162CCC(void);
void func_8017F220(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_80190544;
    extern s32 D_801905A0[];
    s32 iVar1;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_80190544;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        *(s32 *)(param_1 + 0x58) = (s32)&D_801905A0[*(s32 *)(param_1 + 0x50) * 2];
        *(u16 *)(iVar1 + 0x1c) = 0;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(iVar1 + 0x18) = 0;
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        ((void (*)(s32))func_80162CCC)(param_1);
    }
}



/* func_8017F2D0 — per-frame spin + clamp handler (ov_SC03_014, reach x8).
 *
 * Byte-proven shape notes:
 *  - obj->0x1C/0x1A are read u16 / written s16 (this file's house idiom), so
 *    "+= 0x800" is lhu+addiu+sh and the compare re-derives the s16 (sll/sra).
 *  - each clamp needs TWO pseudos: `limN` (s32, the compare operand — it must be
 *    SINGLE-BLOCK so local-alloc TIES the `slt` dest into it, giving the target's
 *    `slt $v1,$v1,$v0`) and `lvN` (s16, the store value — it crosses the branch,
 *    so it is a GLOBAL allocno, global.c never coalesces, and the target's
 *    `addu $aN,$v1,$zero` copy survives).  Sharing one variable per role across
 *    the two blocks makes both global, kills the tie and loses both copies
 *    (regalloc map K8).  `lvN` must be s16: an s32 copy folds away (-2 ins).
 *  - `o` (9 refs / 28 insns, density 9642) out-prioritises lv1 (3 refs / 7,
 *    4285) in global.c's allocno_compare and grabs $a0 first; the target has
 *    $a0 = lv, $a1 = o.  The zero-byte read-modify-write asm below gives lv1 two
 *    extra refs (5 refs / 8 insns -> 12500) so it allocates first and takes $a0,
 *    pushing `o` to $a1.  It emits nothing.  (Byte-identical alternatives:
 *    `register s32 o __asm__("$5");`, or pinning lv1/lv2 to "$4".)
 *    NB gcc-2.7.2 rejects "+r" constraints — use "=r"(x) : "0"(x).
 *  - the 0x10 phantom frame slot is an address-taken pad (cookbook S17/S36#3).
 */

extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8017F2D0(s32 p) {

    extern s16 D_80126B0C;
    s32 o;
    s32 lim1, lim2;
    s16 t1, t2, lv1, lv2;
    s32 pad[3];

    (void)&pad;
    o = *(s32 *)(p + 0x20);
    t1 = *(u16 *)(o + 0x1C) + 0x800;
    *(s16 *)(o + 0x1C) = t1;
    *(s16 *)(o + 0x18) = t1;
    lim1 = **(s16 **)(p + 0x58);
    lv1 = lim1;
    if (lim1 < t1) {
        do { *(s16 *)(o + 0x1C) = lv1; } while (0);
        *(s16 *)(o + 0x18) = lv1;
        D_80126B0C = 1;
    }
    t2 = *(u16 *)(o + 0x1A) + 0x800;
    *(s16 *)(o + 0x1A) = t2;
    lim2 = *(s16 *)(*(s32 *)(p + 0x58) + 2);
    lv2 = lim2;
    if (lim2 < t2) {
        *(s16 *)(o + 0x1A) = lv2;
        func_80146E90((s32 *)p, *(s16 *)(*(s32 *)(p + 0x58) + 4));
        func_80146CA0((void *)p);
    }
}


void func_8017F394(void *a0) {
    extern s32 func_80146E98(s32 a0);
    extern void func_80162CCC(void);

    s32 s1 = (s32)a0;
    u16 *s2;
    u16 *s0;

    s2 = *(u16 **)(s1 + 0x4C);
    s0 = *(u16 **)(s1 + 0x20);

    if (func_80146E98((s32)a0)) {
        {
            s16 t = *(u16 *)(s0 + 0xE) + 0x400;
            *(u16 *)(s0 + 0xE) = t;
            *(u16 *)(s0 + 0xC) = t;
            if (t >= 0x7001) {
                *(u16 *)(s0 + 0xE) = 0x7000;
                *(u16 *)(s0 + 0xC) = 0x7000;
            }
        }
        {
            s16 u = *(u16 *)(s0 + 0xD) + 0x100;
            *(u16 *)(s0 + 0xD) = u;
            if (u >= 0x7001) {
                *(u16 *)(s0 + 0xD) = 0x7000;
            }
        }
    }

    if (*(u16 *)s2 != 0x16) {
        ((void (*)(s32))func_80162CCC)((s32)s1);
    }
}


void func_8017F454(s32 param_1) {
    s32 tbl;
    s32 obj;

    tbl = *(s32 *)(param_1 + 0x4C);
    obj = *(s32 *)(param_1 + 0x20);
    *(s32 *)(param_1 + 0x04) = *(s32 *)(tbl + 0x04);
    *(s32 *)(param_1 + 0x08) = *(s32 *)(tbl + 0x08);
    *(s32 *)(param_1 + 0x0C) = *(s32 *)(tbl + 0x0C);
    *(u16 *)(obj + 0x12) += *(u16 *)(*(s32 *)(param_1 + 0x58) + 0x06);
}


extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8017F498(s32 a0) {
    s32 sp10[8];

    func_80052D90(0, (void *)a0);
    func_80054514(a0, (s32)sp10);
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    *(s16 *)(a0 + 0x50) = 0;
    *(s16 *)(a0 + 0x52) = 0;
    *(s16 *)(a0 + 0x54) = 0;
}


extern void func_8017F510(s32 arg0, s32 arg1, s32 arg2);
    void func_8017F4EC(s32 arg0) {
        func_8017F510(arg0, *(s32 *)(arg0 + 0x8), arg0 + 0x10);
    }


#include "common.h"
#include "../shared/engine_types.h"

/* ===========================================================================
 * func_8017F510 -- 1,511 ins, ov_SC03_006 (behemoth #3).  ***MATCH***
 *
 * WHAT IT IS: the SINGLE-point-light variant of the mesh renderer family.
 *   base   = func_8017CA80  (952 ins, MATCHED, src/ov_SC03_090/...)
 *   lit x3 = func_8017D960  (3,338 ins, 98.8% draft, .run/giants/)
 *   this   = func_8017F510  (1,511 ins) -- ONE light box, plus an ambient
 *            term added to every vertex and an "unlit" flat colour derived
 *            from that same ambient.
 *
 * Differences vs the 3-light variant:
 *   - 3 args (arg0 = actor, arg1 = model = *(arg0+8), arg2 = arg0+0x10).
 *   - early-out `if (*(s32 *)arg0) return;` BEFORE the 3-call prologue.
 *   - Part[] lives INLINE at arg1 + 0x14 (not *(arg0+0xC)).
 *   - ONE light descriptor at D_801F7790 {s32 enable; u16 cx,cy,cz; pad;
 *     s32 range; ...; s32 ambient@+0x18}; defaults cx=cy=cz=0x6000,
 *     r=0x100, rlo=0x80, amb=0, col=0 when disabled.
 *   - per vertex: atten (x,z,y separable falloff) + amb, clamped to 0x80.
 *   - lit   -> POLY_GT3 (0x28, OT 0x9000000, GPU 0x34) /
 *              POLY_GT4 (0x34, OT 0xC000000, GPU 0x3C)
 *              rgb = cbase | c | (c<<8) | 0x800000  (blue fixed at 0x80),
 *              cbase = (tp[0] & 0x2000000) | GPUCODE.
 *     unlit -> POLY_FT3 (0x20, OT 0x7000000) / POLY_FT4 (0x28, OT 0x9000000)
 *              rgbc = (tp[0] & 0xFF000000) | col.
 *
 * Frame (measured from the .s): 0x258 =
 *   0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 mtx |
 *   0xC0 g{otz,flag,opz,sz0..sz3} | 0xE0..0x22F = 42 EIGHT-BYTE spill slots |
 *   0x230..0x257 = 10 saved regs (s0-s7, fp, ra).
 *
 * ===== MEASURED (2026-07-25, session 19, gcc-2.7.2 pinned triple) =====
 *   tools/match_one.py func_8017F510 --c <this file>
 *     --asm-subdir asm/ov_SC03_006/nonmatchings/ov_SC03_006_jr_8017AE2C
 *   -> **MATCH (1511 ins)**      (was: 97 mismatched at s18/b3)
 *   tools/symcheck.py -> SYMS-OK, 12 symbols agree.
 *   PIN-FREE: no `register __asm__` anywhere (§72/§74 audit not needed).
 *   The one `__asm__ __volatile__ ("" :: "r" (mny))` is a ZERO-BYTE density
 *   dial (it emits only #APP/#NO_APP): the compile is 1511 ins EXACT.
 *   NOTE: match_one is the CANDIDATE gate; finish on the whole-binary SHA1
 *   (G3/P9) before calling this banked.
 *
 * ===== THE FOUR LEVERS THAT CLOSED 97 -> 0 (each byte-measured) =====
 * The 97 were FIVE independent decisions, not one cascade.  Order of attack
 * and measured effect (each applied on top of the previous):
 *
 *  L1. `otp` DECLARED PER EMIT ARM (all four: tri-lit/tri-unlit/quad-lit/
 *      quad-unlit), not at function scope.        97 -> (see L2; alone 1515 ins)
 *      WHY: at function scope `otp` has 4 deaths -> local-alloc's gate
 *      (`local-alloc.c:472`, REG_BASIC_BLOCK>=0 && REG_N_DEATHS==1) rejects it
 *      -> it becomes a GLOBAL allocno, so the `(g.opz>>2)<<2` shift chain
 *      cannot TIE into it (K8) and it takes a separate register ($a2).
 *      Per-arm it is a 1-death, 1-block pseudo -> local-alloc ties the whole
 *      chain -> the target's in-place `sra $a0 / sll $a0 / addu $a0,$a0,$s4`.
 *      SIDE EFFECT that matters more than the tie: a global `otp` in $a2 made
 *      the per-tail 0xFFFFFF constant land in $a0; freeing $a2 moved that
 *      constant to $a1 (the target's register).  This is the mechanism in
 *      `global.c:668-671` -- pseudos ALREADY allocated by local-alloc are
 *      re-marked live as HARD regs for global-alloc, so every local-alloc
 *      choice shows up as a hard-reg conflict in the global allocno's
 *      `;; N conflicts:` line.  Read that line, not just the priorities.
 *      (Scoping `otp` only at the innermost-`if` level -- i.e. shared by the
 *      lit and unlit ARMS -- does NOTHING: it still has 2 deaths in 2 blocks.)
 *
 *  L2. `cb` REUSED AS THE UNLIT rgbc TEMP (`cb = (tp[0]&0xFF000000)|col;`
 *      then `pkt->rgbc = cb;`) instead of storing the expression directly.
 *                                                 (L1+L2) 97 -> **10**
 *      WHY: it merges four values into one global allocno (§45-Lever-A /
 *      RC-14 MERGE).  cb's refs go 27 -> 39 and its `allocno_compare`
 *      priority (global.c:594) jumps past `tp`'s, so the grant order becomes
 *      cb -> $a1, c3 -> $a2, tp -> $a3, matching the target instead of
 *      tp -> $a2, cb -> $a1, c3 -> $a3.  ~75 of the 97 fall here.
 *      It ALSO fixes the "residual B" schedule diff for free: with the unlit
 *      rgbc in $a1, the two-insn 0xFFFFFF constant (also $a1) cannot be
 *      materialised until rgbc dies, so sched2 slides it below the single-lui
 *      OT tag -- exactly the target's `lui $v1,0x700 / lui $a1 / ori $a1`
 *      order.  That ordering was NEVER a schedule lever; it was a consequence
 *      of a register grant.  (Generalises the §H reg_renumber-swap oracle
 *      finding: reordering near a reused scratch is usually an ALLOCATION
 *      symptom.)
 *
 *  L3. `rgbw` -- ONE SHARED u32 TEMP FOR THE LIT rgb WORD, written then
 *      stored (`rgbw = cb|c|(c<<8)|0x800000; pkt->rgbN = rgbw;`).
 *                                                 (L1..L3) 10 -> **2**
 *      WHY: the last `| 0x800000` result was TIED by local-alloc's
 *      `combine_regs` (local-alloc.c:1825) into the OR-chain's qty, so the
 *      chain+result shared $v0 and the `sll` temp took $v1.  The target has
 *      the chain in $v1, the sll temp in $v0 and the result back in $v0 --
 *      i.e. the result is a SEPARATE qty and the sll temp out-ranks the
 *      chain.  Routing the result through a multi-set variable (4 sets, 4
 *      deaths) removes it from local-alloc's single-death gate, breaks the
 *      tie, and re-ranks the block's qtys so the sll temp wins $v0.
 *      Only the FIRST chain of each lit tail was ever wrong -- rgb1..rgb3
 *      already matched -- which is the tell that it was a qty-priority
 *      contest, not an expression-shape problem.  (All 6 re-spellings of
 *      the OR expression cost 15-21 instructions; the DAG is not the knob.)
 *
 *  L4. THE BOX-BUILD y PAIR: source order `mny = wy;` BEFORE
 *      `my = wy >> 16;`  PLUS one zero-byte density dial on `mny`.
 *                                                 (L1..L4) 2 -> **MATCH**
 *      WHY (two coupled facts, both measured):
 *      (a) The emission order of `addu $a2,$v1,$zero` / `srl $a3,$v1,16` is
 *          RTL EXPANSION order, NOT a scheduling decision.  Proven by
 *          compiling with `-fno-schedule-insns` and with
 *          `-fno-schedule-insns2`: the pair stays in source order under
 *          BOTH.  So the original must read `mny = wy; my = wy >> 16;`
 *          (which is also what the MATCHED sibling func_8017CA80 has).
 *      (b) But that order alone gives the WRONG registers (36 mismatched):
 *          whichever of the pair is defined SECOND has the shorter
 *          REG_LIVE_LENGTH (106 vs 108 -- exactly the 2 insns between the
 *          two defs) and therefore the higher `allocno_compare` priority
 *          (5*46/106 = 21698 vs 5*46/108 = 21296), so it is granted first
 *          and takes the lower register $a2.  The target wants the
 *          FIRST-defined (`mny`) in $a2.
 *      FIX: RC-15's ref-count axis.  `__asm__ __volatile__ ("" :: "r"(mny))`
 *      placed as the first statement inside the TRI innermost cull block
 *      (loop_depth 3 -> `reg_n_refs += 3`, flow.c) lifts mny 46 -> 49 refs
 *      while adding ~1 to its live length: 5*49/109 = 22477 > 21698, so mny
 *      is granted first and takes $a2, with my taking $a3.  Emits nothing.
 *      Placement matters: the same dummy inside the box-build statement
 *      stream costs +9 instructions (its #APP/#NO_APP kills maspsx's
 *      delay-slot hop, RC-11 caveat); placed at the head of a cull block it
 *      is byte-free.  The same dial in BOTH cull blocks also MATCHes, as
 *      does swapping the `s16 my, mny, ...` declaration order -- so the
 *      declaration order is NOT load-bearing (the priorities are not tied).
 *
 * ===== TRIED AND REJECTED (byte-measured; do not re-buy) =====
 *   From s18: decl-order permutations of amb / my,mny,mx,mn; block-scoping
 *   otp/tp/cb/uvw at the innermost-`if` level (1509); dedicated box-build
 *   min/max vars (1510); splitting `tp` per branch (147); inlining `tp` as
 *   `((u32*)prim->w0)[k]` (1535); reusing `f0` as c3 (176); vertex x/z/y and
 *   y/x/z orders (99-146); `otp = (u32*)(ot + ...)` operand swap; and
 *   `0x800000 | cb | c | (c<<8)` (1526).
 *   From s19 (all on the improved bases): `cb` block-scoped per case or per
 *   arm (1509 -- the 0x800000 lui hoists into the tp-load delay slot);
 *   `tp` per arm (1513); `tp` per case (20 with otparm, 111 alone); scoping
 *   za/zb, uvw, f0, d, c0..c3, x0..z3 (10 / 38 / 1507 -- all neutral or
 *   worse); six re-spellings of the lit rgb OR expression (15-21 ins over);
 *   a named `tp[0]` temp (16); a shared temp for the three packet x-stores
 *   (10, neutral); `cb` split into two statements (14); a shared `c<<8`
 *   temp (1509); dedicated box-build y (92) and x+y (1350) variables; six
 *   box-build statement placements incl. all-loads-first (10, neutral);
 *   decomp-permuter re-seeded at base score 10 (~3,100 iterations, 0
 *   improvement -- its randomisers destroy this shape, scores jump to ~1450).
 *
 * ===== THE GENERALISABLE LESSON =====
 *   Four of the five decisions were LOCAL-vs-GLOBAL allocno-class choices
 *   that C expresses ONLY through DECLARATION SCOPE and variable REUSE:
 *     - narrow the scope so a value has 1 death in 1 block  -> local-alloc
 *       (ties into its producer chain, takes a low scratch);
 *     - widen/merge the variable so it has several deaths   -> global allocno
 *       (enters the density contest, takes an $aN/$sN by priority).
 *   Neither is reachable by statement order, expression shape, pins, or the
 *   permuter.  When a giant's residual is "a block of registers renamed",
 *   enumerate the tail locals and ask, per variable, WHICH ALLOCATOR the
 *   target used -- then set the scope to match.  (New cookbook entry.)
 * =========================================================================== */













/* ---- the two gouraud-textured packet layouts this function emits ---------- */
                                      /* 0x28 */

                                      /* 0x34 */

/* ---- the single light-volume descriptor ---------------------------------- */
extern s32 D_801F7790;
extern u16 D_801F7794, D_801F7796, D_801F7798;
extern s32 D_801F779C;
extern s32 D_801F77A8;

/* ---- the box-containment test for one vertex ----------------------------- */
#define BOXTEST(F, X, Y, Z) \
    if (lo_x < (X) && (X) < hi_x && lo_y < (Y) && (Y) < hi_y && lo_z < (Z) && (Z) < hi_z) F = 1

/* ---- the separable per-axis falloff, visited in x, z, y order ------------ */
#define ATTEN(A, X, Y, Z)                                       \
    A = 0;                                                      \
    d = (X) - cx;   if (d < 0) d = cx - (X);                    \
    if (d < r) { A = 0x80; if (d >= rlo) A = r - d; }           \
    d = (Z) - cz;   if (d < 0) d = cz - (Z);                    \
    if (r < d) A = 0;                                           \
    else if (rlo < d) A = (A * (r - d)) >> 7;                   \
    d = (Y) - cy;   if (d < 0) d = cy - (Y);                    \
    if (r < d) A = 0;                                           \
    else if (rlo < d) A = (A * (r - d)) >> 7;                   \
    A = A + amb;                                                \
    if (A > 0x80) A = 0x80

void func_8017F510(s32 arg0, s32 arg1, s32 arg2)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF630[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *vd;
    u32 ot;
    u8 *pkt;
    s16 x3, z3, y3;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part *part;
    s16 lo_x, hi_x, lo_y, hi_y, lo_z, hi_z;
    s16 cx, cy, cz;
    s32 r, rlo;
    u32 col;
    u8 *va, *vb, *vc;
    u32 w; s32 code;
    u32 vw, vzw;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    u8 *base;
    s32 f0;
    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;
    s32 d;
    s32 c0, c1, c2, c3;
    s32 za, zb;
    u32 *tp;
    u32 cb;
    u32 rgbw;
    u32 uvw;
    s32 amb;

    base = D_800AF630;

    if (*(s32 *)arg0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg2, &mtx);
    func_80052E38(&mtx);

    if (D_801F7790) {
        cx = D_801F7794;
        cy = D_801F7796;
        r = D_801F779C;
        rlo = r - 0x80;
        amb = D_801F77A8;
        cz = D_801F7798;
        if (amb < 0x60) {
            col = amb | 0x600000 | (amb << 8);
        } else {
            col = amb | (amb << 8) | (amb << 16);
        }
    } else {
        cz = 0x6000;
        cy = 0x6000;
        cx = 0x6000;
        r = 0x100;
        rlo = 0x80;
        amb = 0;
        col = 0;
    }

    lo_x = cx - r;  hi_x = cx + r;
    lo_y = cy - r;  hi_y = cy + r;
    lo_z = cz - r;  hi_z = cz + r;

    pkt = D_800A5E60;
    part = (Part *)(arg1 + 0x14);
    nparts = *(s32 *)(arg1 + 8);
    vtx = *(u8 **)(arg1 + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)(base + 0xA3D2)) << 14];

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
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[7].vx = mx; box[7].vy = my;
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
                                    /* ---------------- TRI (FT3 / GT3) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                        else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                        if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                        else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;

                                            f0 = 0;

                                            vw = *(u32 *)va;
                                            vzw = *(u32 *)(va + 4);
                                            x0 = vw; y0 = vw >> 16; z0 = vzw;
                                            BOXTEST(f0, x0, y0, z0);
                                            vw = *(u32 *)vb;
                                            vzw = *(u32 *)(vb + 4);
                                            x1 = vw; y1 = vw >> 16; z1 = vzw;
                                            BOXTEST(f0, x1, y1, z1);
                                            vw = *(u32 *)vc;
                                            vzw = *(u32 *)(vc + 4);
                                            x2 = vw; y2 = vw >> 16; z2 = vzw;
                                            BOXTEST(f0, x2, y2, z2);

                                            if (f0) {
                                                u32 *otp;
                                                ATTEN(c0, x0, y0, z0);
                                                ATTEN(c1, x1, y1, z1);
                                                ATTEN(c2, x2, y2, z2);

                                                *(u32 *)&((PolyGT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyGT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyGT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = (tp[0] & 0x2000000) | 0x34000000;
                                                rgbw = cb | c0 | (c0 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->rgb0 = rgbw;
                                                rgbw = cb | c1 | (c1 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->rgb1 = rgbw;
                                                rgbw = cb | c2 | (c2 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->rgb2 = rgbw;
                                                ((PolyGT3 *)pkt)->uv0 = tp[1];
                                                ((PolyGT3 *)pkt)->uv1 = tp[2];
                                                ((PolyGT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            } else {
                                                u32 *otp;
                                                *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = (tp[0] & 0xFF000000) | col;
                                                ((PolyFT3 *)pkt)->rgbc = cb;
                                                ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                                ((PolyFT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x20;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4 / GT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
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
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;

                                                f0 = 0;

                                                vw = *(u32 *)va;
                                                vzw = *(u32 *)(va + 4);
                                                x0 = vw; y0 = vw >> 16; z0 = vzw;
                                                BOXTEST(f0, x0, y0, z0);
                                                vw = *(u32 *)vb;
                                                vzw = *(u32 *)(vb + 4);
                                                x1 = vw; y1 = vw >> 16; z1 = vzw;
                                                BOXTEST(f0, x1, y1, z1);
                                                vw = *(u32 *)vc;
                                                vzw = *(u32 *)(vc + 4);
                                                x2 = vw; y2 = vw >> 16; z2 = vzw;
                                                BOXTEST(f0, x2, y2, z2);
                                                vw = *(u32 *)vd;
                                                vzw = *(u32 *)(vd + 4);
                                                x3 = vw; y3 = vw >> 16; z3 = vzw;
                                                BOXTEST(f0, x3, y3, z3);

                                                if (f0) {
                                                    u32 *otp;
                                                    ATTEN(c0, x0, y0, z0);
                                                    ATTEN(c1, x1, y1, z1);
                                                    ATTEN(c2, x2, y2, z2);
                                                    ATTEN(c3, x3, y3, z3);

                                                    *(u32 *)&((PolyGT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    gte_stsxy((long *)&((PolyGT4 *)pkt)->x3);
                                                    tp = (u32 *)prim->w0;
                                                    cb = (tp[0] & 0x2000000) | 0x3C000000;
                                                    rgbw = cb | c0 | (c0 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb0 = rgbw;
                                                    rgbw = cb | c1 | (c1 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb1 = rgbw;
                                                    rgbw = cb | c2 | (c2 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb2 = rgbw;
                                                    rgbw = cb | c3 | (c3 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb3 = rgbw;
                                                    ((PolyGT4 *)pkt)->uv0 = tp[1];
                                                    ((PolyGT4 *)pkt)->uv1 = tp[2];
                                                    uvw = tp[3];
                                                    ((PolyGT4 *)pkt)->uv2 = uvw;
                                                    ((PolyGT4 *)pkt)->uv3 = uvw >> 16;
                                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0xC000000;
                                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                    pkt += 0x34;
                                                } else {
                                                    u32 *otp;
                                                    *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    tp = (u32 *)prim->w0;
                                                    cb = (tp[0] & 0xFF000000) | col;
                                                    ((PolyFT4 *)pkt)->rgbc = cb;
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



void func_80180CAC(void) {
    func_80029124(0x142, 0);
    if ((func_800291B4(0xCC) & 0xFF) == 1) {
        func_800291A0(0xCC, 2);
    }
}


extern void func_80029124(s32 arg0, s32 arg1);
    void func_80180CF0(void) {
        func_80029124(0x142, 0);
    }



extern void (*D_801907B8[])(void);

void func_80180D14(void *a0) {
    D_801907B8[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801810B4(void);
extern void func_800167B8(s32 a0);

s32 func_80180D50(s32 a0) {
    func_801810B4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80180D94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_801907C0[])(void);

void func_80180DB8(void *a0) {
    D_801907C0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801810DC(void);
extern void func_800167B8(s32 a0);

s32 func_80180DF4(s32 a0) {
    func_801810DC();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void (*D_801907C8[])(void);

void func_80180E38(void *a0) {
    D_801907C8[*(u8 *)((s32)a0 + 0x15)]();
}



extern void func_800D1E28(void);

s32 func_80180E74(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;

    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }

    return 0;
}



extern void (*D_801907D4[])(void);

void func_80180EC8(void *a0) {
    D_801907D4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80181104(void);

s32 func_80180F04(s32 a0) {
    func_80181104();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_80180F44(u8 *a0) {
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
    void func_80180FC0(void) {
        func_800D1EBC();
    }



extern void (*D_801907E0[])(void);

void func_80180FE0(void *a0) {
    D_801907E0[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 func_80029504(void);
extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8018101C(u8 *a0) {
    s32 s1 = func_80029504();
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        if (s1 >= 0x2C6) {
            func_800D0C48(1);
        }
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_801907EC;

void func_801810B4(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_801907EC, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_801907F8;

void func_801810DC(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_801907F8, 0x1000000);
}


extern s32 D_801907FC;
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);

void func_80181104(void) {
    ((void (*)(s32, s32))func_8016EE40)((s32)&D_801907FC, 0x1000000);
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801811CC(u8 *param_1);

void func_8018112C(void) {
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
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_801811CC, 0);
    func_8012A094((s32)D_80126948);
    func_801811CC(D_80126948);
}


extern void (*D_80190810[])(void);

void func_801811CC(u8 *param_1)
{
    D_80190810[param_1[0x4]]();
}


extern s32 func_80181228();  // K&R: 0/1 of 1 args (P37 rung D t4_D2)
    void func_80181208(void) {
        func_80181228();
    }


#include "common.h"

/* Local address-suffixed clones of the PSX MATRIX/SVECTOR layouts (see cookbook §8c / the
 * seed's own comment in src/ov_SC02_015/ov_SC02_015_jr_8017AE2C.c func_8017D5C8): match_one's
 * isolated compile only has -Iinclude, so "../shared/engine_core.h" can't resolve from its
 * scratch dir. These local names exist ONLY to let this file compile standalone under
 * match_one; the host TU already includes engine_core.h and has the real MATRIX/SVECTOR types.
 * Layout: m[3][3] (18B) + 2B pad + t[3] s32 (12B) = 0x20; vx/vy/vz/pad s16 = 8B. */
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_80181228;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_80181228;

extern s32 D_80126B58;
extern s16 D_80190814[];
extern u16 func_80148800(s32 *a0);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;

s32 func_80181228(s32 param_1)
{
    MATRIX_80181228 m1;
    SVECTOR_80181228 svec_in;
    SVECTOR_80181228 svec_out;
    u8 t;
    s16 *p0;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0x14) = D_80190814[t];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    p0 = &D_80126940;
    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)(*p0);
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)D_80126942;
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)D_80126944;
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + (*p0);
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


extern void (*D_80190824[])(void);

void func_80181418(void *a0) {
    D_80190824[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801BD274[];
extern u8 D_801BAE98[];

void func_80181454(s32 p) {
    s32 v;

    *(s32 *)(p + 0x20) = v = ((s32 (*)(void))func_8012C1B8)();
    if (v == 0) {
        func_8012CAE4((void *)p);
    } else {
        func_8001C214(v, (s32)D_801BD274);
        func_8012A828(p, D_801BAE98);
        *(u16 *)(p + 2) = 1;
        *(s32 *)(*(s32 *)(p + 0x20) + 4) |= 0x80000000;
        func_8012B23C(p);
    }
}


extern s32 func_800291B4(s32 arg);
extern void func_8012BD14(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BAEF0[];

void func_801814DC(s32 a0) {
    if ((func_800291B4(0xCC) & 0xFF) == 1) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x10000) {
            *(s16 *)(a0 + 0x2) = 2;
            func_8012A828(a0, D_801BAEF0);
        }
    }

    if ((func_800291B4(0xCC) & 0xFF) == 0xF) {
        *(s16 *)(a0 + 0xE) -= 0x100;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0x2) = 3;
        func_8012A828(a0, D_801BAEF0);
    }
}


extern void func_8012B14C(s32 a0, s32 a1);
extern void func_800291A0(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 D_80190818[];

void func_801815A8(s32 arg0) {
    s32 pad;
    s32 a0;
    short v;

    func_8012B14C(arg0, (s32)D_80190818);
    a0 = *(s32 *)((s8 *)arg0 + 0x20);
    v = *(short *)((s8 *)a0 + 0x12);
    if (v < 0x800) {
        *(short *)((s8 *)a0 + 0x12) = v + 0x100;
    }
    *(s32 *)((s8 *)arg0 + 0xC) += *(s32 *)((s8 *)arg0 + 0x18);
    *(s32 *)((s8 *)arg0 + 0x4) += *(s32 *)((s8 *)arg0 + 0x10);
    if (*(short *)((s8 *)arg0 + 0xE) < 0x104B) {
        return;
    }
    func_800291A0(0xCC, 2);
    func_8012C218((void *)arg0);
}


extern void func_800291A0(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

void func_8018163C(s32 arg0) {
    short v;

    v = *(short *)((s8 *)arg0 + 0xE) - 0x10;
    *(short *)((s8 *)arg0 + 0xE) = v;
    if (v < 0x345) {
        func_800291A0(0xCC, 0x10);
        func_8012C218((void *)arg0);
    }
}


#include "common.h"

void func_80181694(s32 arg0) {
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern void func_80129374(s32 a0, s32 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8018185C(s32 a0);
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80190834;

    s16 var_s3;
    s16 var_s2;
    s32 temp_v1;
    s32 q;
    s32 dist;
    u16 *p96;

    var_s3 = D_80126B5E - *(u16 *)(arg0 + 6);
    if (var_s3 < 0) {
        var_s3 = -var_s3;
    }
    var_s2 = D_80126B66 - *(u16 *)(arg0 + 0xE);
    if (var_s2 < 0) {
        var_s2 = -var_s2;
    }
    if ((var_s3 < 0x201) && (var_s2 < 0x201)) {
        temp_v1 = *(s32 *)(arg0 + 0x1C);
        *(s32 *)(arg0 + 0x1C) = temp_v1 + 1;
        if (temp_v1 & 1) {
            q = func_80132EF4(arg0, 0x22);
            if (q != 0) {
                func_80129374(q, arg0);
                *(s16 *)(*(s32 *)(q + 0x20) + 0x18) = 0x7000;
                *(s16 *)(*(s32 *)(q + 0x20) + 0x1A) = 0x5000;
            }
        }
        if (func_801818D8(arg0, &D_80190834) != 0) {
            p96 = &D_80126B96;
            D_80126B98 = 0xC;
            *p96 |= 0x4000;
        }
        if ((*(s32 *)(arg0 + 0x1C) & 3) == 0) {
            if (*(s16 *)(arg0 + 0x70) != 0) {
                dist = (var_s3 * var_s3) + (var_s2 * var_s2);
                if (dist <= 0x30000) {
                    func_8002D4C8(0x5A5, (0x1000 | (((0x30000 - dist) * 127) / 0x30000)) & 0xFFFF);
                    *(s16 *)(arg0 + 0xFC) = 1;
                    return;
                }
            } else {
                return;
            }
        } else {
            return;
        }
    }
    func_8018185C(arg0);
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018185C(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        func_8002D4C8(4, 0x5A5);
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



extern void (*D_80190844[])(void);

void func_8018189C(void *a0) {
    D_80190844[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
    /* 0x6 */ u16 w;
} Vec4h_801818D8;

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

s32 func_801818D8(s32 a0, s32 a1) {
    Vec4h_801818D8 p1;
    Vec4h_801818D8 p2;
    s32 result;

    p1.z = *(u16 *)(a1 + 0xC);
    p2.z = *(u16 *)(a1 + 0xE);
    p1.x = p2.x = *(u16 *)(a1 + 0x4);
    p1.y = p2.y = (s16)*(u16 *)(a1 + 0x8) >> 1;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = 0;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = (s16)*(u16 *)(a1 + 0xA) >> 1;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.x = p2.x = *(u16 *)(a1 + 0x6);
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = 0;
    if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.y = p2.y = (s16)*(u16 *)(a1 + 0x8) >> 1;
    result = func_8012DEB8(a0, (s32)&p1, (s32)&p2) != 0;

save:
    return result;
}


extern s32 func_800291B4(s32 arg);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *);
extern s32 D_80190834;

void func_80181A14(void *a0)
{
    void *s0 = a0;
    s32 v0;
    s32 sp10[3];

    if (((func_800291B4(0xCD) & 0xFF) != 0) ||
        (v0 = ((s32 (*)(void))func_8012C1B8)(),
         (*(s32 *)((u8 *)s0 + 0x20) = v0),
         v0 == 0))
    {
        func_8012CAE4(s0);
        return;
    }

    func_8001C2C4(v0);
    *(s16 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x10) = -0x400;
    func_8012B2CC((s32)s0);
    sp10[1] = 0;
    sp10[0] = 0;
    sp10[2] = 0x240000;
    func_8012B14C((s32)s0, (s32)sp10);
    *(s32 *)((u8 *)s0 + 0x58) = (s32)&D_80190834 | 0x40000000;
    *(s16 *)((u8 *)s0 + 0x5C) = 0x800;
    *(s16 *)((u8 *)s0 + 0xFC) = 0;
    func_8012AD50(s0);
}


extern void (*D_801908B4[])(void);

void func_80181ACC(void *a0) {
    D_801908B4[*(u16 *)((s32)a0 + 0x2)]();
}




s32 func_80181B08(void *a0, s32 *p) {
    s32 cur = *(s32 *)((s32)a0 + 0xDC);

    if (p[0] != cur) {
        p += 2;
        for (;;) {
            s32 t = p[0];
            if (t == 0) {
                return cur;
            }
            p += 2;
            if (t == cur) {
                break;
            }
        }
        p -= 2;
    }
    return p[1];
}


#include "common.h"

extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_80181B08(void *a0, s32 *p);

extern s32 D_801908A4[];
extern s32 D_8019084C[];
extern s32 D_80190864[];
extern s32 D_8019087C[];
extern s32 D_80190894[];

void func_80181B50(void *a0) {
    s32 s1;
    s32 v0;
    s32 v1;

    s1 = func_80029504();
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, 0);
    *(s32 *)((s32)a0 + 0x58) = (s32)D_801908A4;
    *(s16 *)((s32)a0 + 0x5C) = 0x80;

    v0 = *(u16 *)((s32)a0 + 0x2) + 1;
    v1 = *(s16 *)((s32)a0 + 0x70);
    *(u16 *)((s32)a0 + 0x2) = v0;

    switch (v1) {
    case 0:
    default:
        if (s1 >= 0x384) {
            *(s32 *)((s32)a0 + 0xDC) = func_80181B08(a0, D_8019087C);
        } else if (s1 >= 0x258) {
            *(s32 *)((s32)a0 + 0xDC) = func_80181B08(a0, D_80190864);
        } else if (s1 >= 0xC8) {
            *(s32 *)((s32)a0 + 0xDC) = func_80181B08(a0, D_8019084C);
        }
        break;
    case 1:
        if (s1 < 0x2EE) {
            return;
        }
        *(s32 *)((s32)a0 + 0xDC) = func_80181B08(a0, D_80190894);
        break;
    }
}


void func_80181C48(void) {
}


// @class: struct
// @unstuck(P36): none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801908EC[])();

void func_80181C50(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_801908EC[*(u16 *)(param_1 + 2)]();
    }
}


void func_80181C9C(void *arg0)
{
    typedef struct {
        u8  unk00[0x1C];
        s32 unk1C;
        u8  unk20[4];
    } Ent_801F7618;
    extern u8 D_80078EB1;
    extern Ent_801F7618 D_801F7618[];
    extern void func_80181FC4(void *arg0);
    s32 i;

    if (D_80078EB1 == 7) {
        *(u16 *)((s32)arg0 + 0x72) |= 0x1000;
        for (i = 0; i < 4; i++) {
            Ent_801F7618 *p = &D_801F7618[i];

            *(s16 *)((s32)p + 0x16) = i;
            func_80181FC4(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}


extern u8 D_80078EB1;
extern u8 D_800AF630[];
extern u8 D_80078E78[];

/* 0x24-stride record at D_801F7618 (4 entries; asm/ov_SC03_006/data/tail18.data.s).
 * Byte-proven twin layout: cookbook sibling func_8017D77C (ov_SC04_018_jr_8017AE2C.c,
 * same jr TU family) uses this exact shape for its D_801E6F58 table; only the fields this
 * function actually names differ (unk1C is the only member accessed via `.`, everything
 * else goes through raw casts, matching the sibling verbatim). */


extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8004787C(s32 a0);
extern void func_80181F74();  // K&R: 0/1 of 0 args (P37 unalias t4_ua2)
extern void func_80182080(void *a0);

void func_80181D38(s32 *arg0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_801F7618 D_801F7618[];
    u8 *m = D_800AF630;
    u8 *q = D_80078E78;
    Ent_801F7618 *p;
    Ent_801F7618 *r;
    s32 i;
    s32 j;
    s32 n;
    s32 h;
    s32 c;
    s32 e;

    if (D_80078EB1 >= 9) {
        n = 0;
        for (j = 0; j < 4; j++) {
            r = &D_801F7618[j];
            if (r->unk1C == 0) {
                n++;
            }
        }
        if (n == 0) {
            func_8012AD44(arg0, 0);
            return;
        }
    }

    i = 0;
    do {
        p = (Ent_801F7618 *)((s32)D_801F7618 + i * 0x24);
        if (p->unk1C == 0) {
            if (*(s16 *)((s32)p + 0xC) > 0x400) {
                if (*(s32 *)((s32)p + 0x18) != 0) {
                    *(s32 *)((s32)p + 0x18) = *(s32 *)((s32)p + 0x18) - 1;
                } else {
                    *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
                }
            } else {
                *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
            }
            if (*(s16 *)((s32)p + 0xC) > 0x800) {
                *(s16 *)((s32)p + 0xC) = 0;
            }
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 64) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x4) = c;
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 256) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x8) = c;
            if ((*(u16 *)(m + 0xA3AA) & 1) == 0) {
                e = *(u16 *)((s32)p + 0xE) + 1;
                *(u16 *)((s32)p + 0xE) = e;
                if ((s16)e >= 0x40) {
                    *(s16 *)((s32)p + 0xE) = 0;
                }
            }
            h = *(s16 *)((s32)p + 0xC);
            if (h == 0) {
                p->unk1C = 1;
            } else if (h > 0x555) {
                if (*(s32 *)((s32)p + 0x20) == 0) {
                    *(s32 *)((s32)p + 0x20) = 1;
                    if (q[0x39] < 9) {
                        func_80181F74(p);
                    }
                }
            }
            func_80182080(p);
        }
        i++;
    } while (i < 4);
}




/* func_80181F74 - iterate through 4-entry array, call func_80181FC4 if any unk1C is non-zero */

extern void func_80181FC4(void *arg0);




void func_80181F74(void)
{

    extern Ent_8017D6EC D_801F7618[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801F7618[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_80181FC4(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_80181FC4(void *arg0) {

    extern void (*D_801908BC[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_801908BC;
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


/* func_80182080 — build 3 textured quads from a 4-vertex table and hand each to
   func_800178EC.  Frame layout: the primitive lives at sp+0x10; the pre-loop
   field inits address it off $sp (`prim.`), the loop body off $s0 (`q->`).

   Two scheduling levers are load-bearing here (do not "simplify" them away):
     * cookbook ADD-7 (§229 addendum) — the literal `3` has no source position of
       its own, so gcc materialises it at its own rank and the prologue saves
       re-order around it.  Naming it (`vz = 3;`) gives the constant a birth
       position that §3-T2's source-order law can then govern.
     * cookbook §194-A — the zero-byte `__asm__ __volatile__("")` fence after the
       last region-1 statement splits the block so that `li $v0,3` schedules with
       the prologue (idx 5) while its `sh` stays down at idx 16, and `i = 0`
       (`addu $s6,$zero,$zero`) sinks to idx 15.
   Statement order `q = &prim;` then `vz = 3;` is what puts the `li` after
   `sw $s0` / `addiu $s0,$sp,0x10`; swapping them costs 3 instructions. */

typedef struct {
    s16 v[4][4];
    s16 t[4][2];
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    u8 f44;
} Prim_80182080;

extern void func_800178EC(s32 a0);

void func_80182080(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_80182080 *q;
    Prim_80182080 prim;
    u16 *p;
    u16 dx;
    u16 dy;
    s32 i;
    s16 vz;

    q = &prim;
    vz = 3;
    do { p = *(u16 **)a0; } while (0);
    dx = *(u16 *)(a0 + 0x12);
    dy = *(u16 *)(a0 + 0x14);
    i = 0;
    prim.v[0][2] = vz;
    prim.f30 = prim.f34 = *(s32 *)(a0 + 4);
    prim.f38 = *(s32 *)(a0 + 8);
    prim.f44 = 0x36;
    prim.f3C = 0;
    prim.f40 = 0x50000000;

    do {
        q->v[0][0] = p[0] + dx;
        q->v[0][1] = p[1] + dy;
        q->v[1][0] = p[2] + dx;
        q->v[1][1] = p[3] + dy;
        q->v[2][0] = p[4] + dx;
        q->v[2][1] = p[5] + dy;
        q->v[3][0] = p[6] + dx;
        q->v[3][1] = p[7] + dy;
        q->t[0][0] = *(u16 *)(a0 + 0xE) + 0xA00 + (s16)p[0] / 2;
        q->t[0][1] = *(u16 *)(a0 + 0x10) + 0x100;
        q->t[1][0] = *(u16 *)(a0 + 0xE) + 0xA00 + (s16)p[2] / 2;
        q->t[1][1] = *(u16 *)(a0 + 0x10) + 0x100;
        q->t[2][0] = *(u16 *)(a0 + 0xE) + 0xA00 + (s16)p[0] / 2;
        q->t[2][1] = *(u16 *)(a0 + 0x10) + 0x13F;
        q->t[3][0] = *(u16 *)(a0 + 0xE) + 0xA00 + (s16)p[2] / 2;
        q->t[3][1] = *(u16 *)(a0 + 0x10) + 0x13F;
        func_800178EC((s32)q);
        p += 8;
        i++;
    } while (i < 3);
}



extern void (*D_80190C34[])(void);

void func_80182290(void *a0) {
    D_80190C34[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_801827E8(s32 a0, s32 a1, s16 a2, s16 a3, s32 a4);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_80029178(s32 a0);

void func_801822CC(s32 param_1)
{
    extern u8 D_801908F4[];
    s32 v0;
    s32 p;

    v0 = func_801827E8(param_1, (s32)D_801908F4, 0x300, 0x140, 0x88);
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        goto fail;
    }
    v0 = func_801827E8(param_1, (s32)D_801908F4, 0x310, 0x140, 0x89);
    *(s32 *)(param_1 + 0xD0) = v0;
    if (v0 == 0) {
        func_80016714((void *)*(s32 *)(param_1 + 0xCC), 0x38);
fail:
        func_8012CAE4((void *)param_1);
        return;
    }
    p = *(s32 *)(param_1 + 0x68);
    *(u16 *)(*(s32 *)(param_1 + 0xCC) + 0x12) = *(u16 *)(p + 0xC);
    p = *(s32 *)(param_1 + 0x68);
    *(u16 *)(*(s32 *)(param_1 + 0xD0) + 0x12) = *(u16 *)(p + 0xC);
    *(s16 *)(param_1 + 0x100) = 0;
    if ((func_80029178(0x121) & 0xFF) == 0) {
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
    } else {
        *(s16 *)(param_1 + 0x2) = 2;
        *(s16 *)(param_1 + 0x34) = 1;
    }
}


#include "common.h"

extern void func_8012BD14(s32 a0);
extern s32 func_80029178(s32 a0);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern s32 func_8014CB58(void);
extern void func_8014B598(s32 a0, s32 a1);
extern s32 func_8016F1AC(void);
extern void func_80175454(void);
extern void func_800D0CA0(s32 arg0);
extern s32 func_8014CB2C(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80182740(s32 param_1);
extern void func_80182794(s32 param_1);
extern void func_801828B0(s32 a0);
extern s32 func_801829FC(void);
extern void func_80029124(s32 a0, s32 a1);
extern s32 func_8016F0AC();
extern void func_8002959C(void);
extern void func_80175414(s32 _arg0);

void func_801823B8(s32 param_1) {

    extern u8 D_80190C14[];
    extern s32 D_80190C24[];
    extern s32 D_8019052C;

    if (((s32 (*)(void))func_8012BD14)() <= 0x400 ||
        (*(u16 *)(param_1 + 0x34) == 1 || *(u16 *)(param_1 + 0x34) == 2)) {
        switch (*(u16 *)(param_1 + 0x34)) {
        case 0:
            if ((func_80029178(0x8B) & 0xFF) == 0) {
                func_80178B18(param_1, (s32)D_80190C14);
                *(u16 *)(param_1 + 0x34) = 2;
            } else {
                func_80178B18(param_1, (s32)D_80190C24);
                *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            }
            break;
        case 1:
            if (func_801789AC(param_1) == 1) {
                ((void (*)(s32))func_80178D18)(param_1);
                *(u16 *)(param_1 + 0x34) = 3;
            }
            break;
        case 2:
            if (func_801789AC(param_1) == 1) {
                ((void (*)(s32))func_80178D18)(param_1);
                *(u16 *)(param_1 + 0x34) = 4;
            }
            break;
        case 3:
            if ((func_80029178(0x121) & 0xFF) == 0 && func_8014CB58() == 3) {
                func_8014B598(3, (s32)&D_8019052C);
                if (func_8016F1AC() != 0) {
                    if ((*(u16 *)(param_1 + 0x100) & 4) == 0) {
                        *(u16 *)(param_1 + 0x100) |= 4;
                        *(s32 *)(param_1 + 0x1C) = 0;
                        func_80175454();
                    }
                }
                if (*(u16 *)(param_1 + 0x100) & 4) {
                    *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) + 1;
                }
                if ((*(u16 *)(param_1 + 0x100) & 2) == 0 &&
                    *(s32 *)(param_1 + 0x1C) == 0x5A) {
                    *(u16 *)(param_1 + 0x100) |= 2;
                    func_800D0CA0(1);
                }
                if ((*(u16 *)(param_1 + 0x100) & 1) == 0) {
                    if ((func_8014CB2C() & 0x8000007F) == 0x80000003) {
                        { u16 n = *(u16 *)(param_1 + 0x34) + 1;
                        *(u16 *)(param_1 + 0x100) |= 1;
                        *(u16 *)(param_1 + 0x34) = n; }
                        func_8002D4C8(0xB11, 0);
                    }
                }
            }
            break;
        }
        if (func_80029178(0x8B) & 0xFF) {
            if (func_8014CB58() == 3) {
                func_80182740(param_1);
                func_80182794(param_1);
                goto join;
            }
            goto setflag;
        }
    } else {
        if (func_80029178(0x8B) & 0xFF) {
setflag:
            *(u8 *)(*(s32 *)(param_1 + 0xCC) + 0x27) = 0x88;
            func_80182794(param_1);
join:
            if (*(u16 *)(param_1 + 0x100) & 1) {
                func_801828B0(param_1);
                if (func_801829FC() == 1) {
                    func_80029124(0x121, 1);
                    *(u16 *)(param_1 + 0x100) &= ~1;
                    func_8016F0AC();
                    *(u16 *)(param_1 + 0x2) = 2;
                    *(u16 *)(param_1 + 0x34) = 0;
                    *(u8 *)(*(s32 *)(param_1 + 0xCC) + 0x27) = 0x88;
                    *(u8 *)(*(s32 *)(param_1 + 0xD0) + 0x27) = 0x89;
                    func_8002959C();
                    func_8002D4C8(4, 0xB11);
                    ((void (*)(void))func_80175414)();
                }
            }
        }
    }
}


extern s16 func_800D0CE0(void);

void func_801826EC(s32 param_1) {
    if (*(u16 *)(param_1 + 0x34) == 0) {
        if (((s32 (*)(void))func_800D0CE0)() != 0) {
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
    }
}



extern void func_800183E0(s32 a0);

void func_80182740(s32 param_1) {

    extern u16 D_800B99DA;
    extern u8 D_80190BF4[];
    extern u8 D_801E867C[];
    *(u8 *)(*(s32 *)(param_1 + 0xCC) + 0x27) = 0x8A;
    func_800183E0((s32)&D_801E867C[D_80190BF4[D_800B99DA & 0x1F] * 16]);
}



extern void func_800183E0(s32 a0);

void func_80182794(s32 param_1) {

    extern u16 D_800B99DA;
    extern u8 D_80190BF4[];
    extern u8 D_801E857C[];
    *(u8 *)(*(s32 *)(param_1 + 0xD0) + 0x27) = 0x8B;
    func_800183E0((s32)&D_801E857C[D_80190BF4[D_800B99DA & 0x1F] * 16]);
}




extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

s32 func_801827E8(s32 a0, s32 a1, s16 a2, s16 a3, s32 a4) {
    s32 obj;

    obj = ((s32 (*)(void))func_8012C194)();
    if (obj == 0) {
        return 0;
    }
    func_8001CB6C((u8 *)obj, a1, a2, a3);
    *(u16 *)(obj + 0x10) = 0xC00;
    *(u8 *)(obj + 0x27) = a4;
    *(u16 *)(obj + 0x1A) = 0x2D00;
    *(u16 *)(obj + 0x18) = 0x2D00;
    *(u16 *)(obj + 8) = *(u16 *)(a0 + 6);
    *(u16 *)(obj + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(obj + 0xC) = *(u16 *)(a0 + 0xE);
    return obj;
}


#include "common.h"

extern u16 D_800B99DA;
extern s16 D_80190C40[];
extern u8 *func_8012913C(s32 a0);
extern void func_8012B0B4(u32 *param_1, s32 param_2, s32 param_3);
extern s32 rand(void);

void func_801828B0(s32 a0) {
    s32 obj;
    s16 *tbl;
    s32 q;
    u32 buf[2];
    s32 v;

    obj = a0;
    if ((D_800B99DA & 3) == 0) {
        for (tbl = D_80190C40; *tbl != -1; tbl++) {
            q = (s32)func_8012913C(0x22);
            if (q != 0) {
                func_8012B0B4(buf, *tbl, rand() % 80 + 0x118);
                v = (s32)buf[0];
                *(u16 *)(q + 0x6) = *(u16 *)(obj + 0x6) + v;
                *(u16 *)(q + 0xE) = *(u16 *)(obj + 0xE) + (v >> 16);
                *(u16 *)(q + 0xA) = *(u16 *)(obj + 0xA) + 0x40;
                *(s32 *)(q + 0x14) = (rand() % 9) * 0x10000 - 0x100000;
                *(u16 *)(q + 0x34) = (rand() & 1) | 0x7FF0;
                *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC008;
            }
        }
    }
}


extern s32 D_801F782C;
extern s32 D_801F76CC;

s32 func_801829FC(void)
{
    if (D_801F782C == 2) {
        if (D_801F76CC == 2) {
            return 1;
        }
    } else {
        D_801F782C = 2;
        D_801F76CC = 0;
    }
    return 0;
}


/* func_80182A44 — 146 ins, ov_SC03_006, TU src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c
 *
 * The per-frame tick of the SC03_006 sequence: pushes the current camera triple
 * (D_80126B5E/62/66) through func_8013B598, then runs a 3-state machine on
 * D_801F782C (0 = init, 1 = draw-only, 2 = animate+draw).
 *
 * ===== THE TWO LEVERS (each byte-measured with tools/match_one.py) =====
 *
 * (1) THE INNER 2-WAY DISPATCH IS AN if-CHAIN, NOT A `switch`.  Target:
 *         beq $v1,$a0,.L80182B5C ; slti $v0,$v1,2 ; beqz $v0,default ; bnez $v1,default
 *     i.e. a case-node tree rooted at 1 with a left leaf 0 and NO right child.
 *     A `switch (D_801F76CC) { case 0: ... case 1: ... }` CANNOT produce that:
 *     gcc-2.7.2 stmt.c:5360 `balance_case_nodes` only splits when `i > 2`, so a
 *     TWO-node list is left LINEAR (root = case 0), and emit_case_nodes'
 *     "right child, no left" arm then emits a bare `do_jump_if_equal` pair —
 *     `beqz`/`beq`, two tests, no `slti` (145 ins, −1).  Writing the three tests
 *     out longhand as nested `if`s reproduces the tree exactly.  Cf. §222-2,
 *     which uses an EMPTY leading case to buy the median split at THREE nodes;
 *     at two nodes there is no case-label spelling that reaches this shape.
 *     (The OUTER switch on D_801F782C is a real 3-node switch — i == 3 takes
 *     stmt.c's `npp = &(*npp)->right` middle-split, root = 1, hence
 *     `beq $v1,$a0` first and the `.L80182AA8` right-subtree block.)
 *
 * (2) THE ±1/+2 ARMS TAKE THE ADDRESS THROUGH A POINTER.  Target:
 *         lui $v1,%hi ; addiu $v1,%lo ; lw $v0,0($v1) ... sw $v0,0($v1)
 *     — `&D_801F76F4` materialised into a register in BOTH arms, with cross_jump
 *     merging the ONE-instruction `sw $v0,0($v1)` tail (§162: one side falls
 *     through into the label ⇒ find_cross_jump's minimum is 1).  Spelling the
 *     arms as plain `D_801F76F4 -= 1;` / `+= 2;` emits the gas-macro folded form
 *     instead (`lw $v0,SYM` → lui/lw %lo; `sw $v0,SYM` → lui $at/sw %lo), whose
 *     shared tail is TWO instructions — 145 ins, and that is the whole −1.
 *     A block-local `s32 *p = &D_801F76F4;` per arm is enough; the `volatile`
 *     of ov_SC03_006.c:220's remat lever also matches but is not needed here,
 *     and §153's integration caution says to gate the PLAIN variant.
 *     Note the other two D_801F76F4 references (the `= 0` at 80182B4C and the
 *     `>= 0x71` read at 80182C10) are SINGLE-use and stay folded — do not
 *     convert them.
 *
 * (3) `case 1:` and the tail of `case 2:` are the same six-instruction
 *     func_8017F510 call; gcc cross-jumps them into the shared .L80182C44, so
 *     write both longhand and let the compiler merge (§88a/§162).
 *
 * Declarations follow the destination TU: D_801F782C/D_801F76CC as `s32`
 * (L7468-7469), D_801F76A8 as `u32` (L7491 — a differing file-scope decl would
 * conflict on splice), func_8017F498/func_8017F510 verbatim from L5833/L5847,
 * func_8013C9C4 from L1299, D_80126B5E/62/66 as `u16` from L1782/L2722/L2734.
 * `(D_800B99DC & 7) + 3` is the same RNG-reseed idiom as ov_SC03_014_o0c.c:2889.
 *
 * MEASURED: tools/match_one.py -> MATCH (146 ins);
 *           tools/symcheck.py  -> SYMS-OK, 23 symbols agree.
 *           match_one is the CANDIDATE gate — finish on the whole-binary SHA1.
 */

#include "common.h"

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_800B99DC;

extern s32 D_801F782C;
extern s32 D_801F76CC;
extern s32 D_801F76D0;
extern s32 D_801F76D4;
extern s32 D_801F76D8;
extern s32 D_801F76F4;
extern u32 D_801F76A8;
extern s32 D_801F7848;
extern s32 D_801BA07C;
extern u8  D_8018CD3C[];

extern void func_8013B598(s32 a0, u16 *a1);
extern void func_8013C0F8(s32 a0);
extern void func_8017F498(s32 a0);
extern void func_8017F510(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_80029178(s32 arg);
extern void func_8013C9C4(void *a0);
extern void func_8013CB84(void);
extern void func_80182C8C(void);
extern void func_800D06E8(void);

void func_80182A44(void) {
    u16 sp10[3];

    sp10[0] = D_80126B5E;
    sp10[1] = D_80126B62;
    sp10[2] = D_80126B66;
    func_8013B598(0, sp10);

    switch (D_801F782C) {
    case 0:
        func_8013C0F8((s32)&D_801BA07C);
        func_8017F498((s32)&D_801F76D8);
        D_801F782C = D_801F782C + 1;
        if ((func_80029178(0x121) & 0xFF) != 0) {
            D_801F782C = 3;
        }
        break;
    case 1:
        func_8017F510((s32)&D_801F7848, (s32)&D_801BA07C, (s32)&D_801F76D8);
        break;
    case 2:
        if (D_801F76CC != 1) {
            if (D_801F76CC >= 2) {
                break;
            }
            if (D_801F76CC != 0) {
                break;
            }
            D_801F76D0 = 0;
            D_801F76D4 = 1;
            D_801F76F4 = 0;
            D_801F76CC = 1;
        }
        if (--D_801F76D4 == 0) {
            func_8013C9C4(D_8018CD3C);
            D_801F76D4 = (D_800B99DC & 7) + 3;
        }
        D_801F76A8 = D_801F76A8 + 0x100;
        D_801F76D0 = D_801F76D0 + 1;
        if (D_801F76D0 >= 0x39) {
            if ((D_801F76D0 & 1) != 0) {
                s32 *p = &D_801F76F4;
                *p = *p - 1;
            } else {
                s32 *p = &D_801F76F4;
                *p = *p + 2;
            }
            D_801F76D8 = 0;
            if (D_801F76F4 >= 0x71) {
                D_801F76CC = D_801F76CC + 1;
            }
        }
        func_8017F510((s32)&D_801F7848, (s32)&D_801BA07C, (s32)&D_801F76D8);
        break;
    }
    func_8013CB84();
    func_80182C8C();
    func_800D06E8();
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH

extern u32 D_801F76A8;
extern u16 D_80190C5C[];
extern u16 D_801F76AC[];
extern s32 D_80190C7C;

extern void func_800183E0(s32 a0);

void func_80182C8C(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_80190C5C;
    base = D_801F76A8 >> 8;
    p = D_801F76AC;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_80190C7C);
    D_801F76A8 = D_801F76A8 + 0x100;
}



extern void (*D_80190D34[])(void);

void func_80182D18(void *a0) {
    D_80190D34[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void ((void (*)(s32*, s32))func_8012A828)(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_8018C90C    : TU declares `extern u8 D_8018C90C[];` (block scope, L3467).
 *                   Conformed; `(s32)D_8018C90C` == `(s32)&D_8018C90C`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_80190CAC, func_80182E4C, func_80182D54 : no other
 *                   declaration anywhere in the TU (func_80182E4C / func_80182D54
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern s32 func_80182E4C(void * a0);

void func_80182D54(s32 a0) {

    extern M2C_UNK D_80190CAC;
    extern u8 D_8018C90C[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_80190CAC)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        ((void (*)(s32*, s32))func_8012A828)((s32 *)s0, (s32)D_8018C90C);
        func_801788B8(s0, (s32)func_80182E4C);
    }
}


void func_80182DB8(void) {
}


extern void func_80178CBC(s32, s32);

void func_80182DC0(s32 *a0)
{

    extern signed char D_80190D28[];
    s32 v0;

    v0 = *(s16 *)((s32)a0 + 0x70);
    v0 = v0 * 4;
    ((void (*)(s32 *, s32))func_80178CBC)(a0, *(s32 *)((s32)D_80190D28 + v0));
    *(s16 *)((s32)a0 + 0x2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80182E0C(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern void func_8012BD14(s32);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80182E4C(a0)
void *a0;
{
    if (((s32 (*)(s32))func_8012BD14)(*(s32 *)((s32)a0 + 0x64)) > 0x1000) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 2;
    func_80178BF8();
    return (s32)func_80172710;
}


extern s32 func_80029178(s32 arg);
extern void func_800D06CC(void);

s32 func_80182EA8(s32 param_1) {
    extern u8 D_80078E78[];
    u8 *p = D_80078E78;

    if (param_1 == 0x4B0 && (func_80029178(0x138) & 0xFF) == 0) {
        func_800D06CC();
        return 0x79;
    }
    if (*(u8 *)(p + 0x37) == 4) {
        return 0x3C;
    }
    return 0xA;
}



extern void (*D_80190D44[])(void);

void func_80182F10(void *a0) {
    D_80190D44[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_801AD31C[];

s32 func_80182F4C(s32 a0, s16 a1)
{
    u8 *base;
    s16 val;
    u16 c0;
    u16 c1;
    u16 outerIdx;
    u16 innerIdx;
    u16 diff;
    s32 prod;
    u16 temp2;
    u16 idx2;
    u16 *tbl;
    s32 p1;
    s32 list;
    s32 p2;
    s32 p3;
    u16 dx;
    u16 n;
    u16 sample;
    s32 addr;
    s16 cur;
    u16 v;

    base = D_801AD31C;
    c0 = 0xF800;
    val = (s16)a0;

    do {
        c1 = 0xFA00;
        outerIdx = (c0 + 0x8000) >> 7 & 0x1FF;
        do {
            innerIdx = (c1 + 0x8000) >> 7 & 0x1FF;
            diff = innerIdx - *(u16 *)(base + 2);
            prod = diff * *(u16 *)(base + 4);
            list = *(s32 *)(base + 0x14);
            p2 = *(s32 *)(base + 0x18);
            p3 = *(s32 *)(base + 0x1C);
            temp2 = outerIdx - *(u16 *)(base + 0);
            tbl = *(u16 **)(base + 0x8);
            idx2 = (prod + temp2) * 2;
            dx = tbl[idx2];
            n = tbl[idx2 + 1];
            p1 = list + dx;
            while (n--) {
                sample = *(u16 *)p1;
                if (!(sample & 0x8000)) {
                    addr = p2 + sample * 18;
                } else {
                    v = sample & 0x7FFF;
                    addr = p3 + v * 22;
                }
                cur = *(s16 *)addr;
                if (cur == val) {
                    *(s16 *)addr = a1;
                }
                p1 += 2;
            }
            c1 += 0x80;
        } while (c1 <= 0xFDFF);
        c0 += 0x80;
    } while (c0 <= 0xFBFF);
}


#include "common.h"

extern s32 func_80182F4C(s32 a0, s16 a1);

void func_80183090(void *a0) {
    func_80182F4C(0x200, -0x7FFE);
    *(u16 *)((s32)a0 + 0x2) += 1;
}


extern s32 func_80182F4C(s32 a0, s16 a1);

void func_801830D0(void *arg0) {
    if ((u8)func_80029178(0x121) != 0) {
        func_80182F4C(-0x7FFE, 0x200);
        func_8012C218(arg0);
    }
}


extern void func_8012E8E0(s32, s32);
extern void func_8012E8A8(u8 *);
extern void func_8012A828(s32, void *);

void func_80183118(void *arg0) {
    extern s32 D_80190D7C;
    extern s32 D_801F2108;
    *(short *)((char *)arg0 + 0x2) = 1;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_80190D7C);
    func_8012E8A8((u8 *)arg0);
    func_8012A828((s32)arg0, (void *)&D_801F2108);
}



extern void (*D_80190F70[])(void);

void func_8018316C(void *a0) {
    D_80190F70[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD80(s32 a0);
extern void func_8012BE98(s32, u16*);
extern void func_8012C218(void*);
extern void func_801834F0(s32 a0, void *a1, void *a2);
extern void func_801833E4(s32 a0);
extern u8 D_801BAEF0[];
extern u8 D_801BAE98[];
extern u8 D_801910C8[];
extern u8 D_801910D0[];
extern u8 D_80190F78[];
extern s32 D_80190D94;

void func_801831A8(s32 param_1) {
    s32 pv = param_1;

    switch (*(u16 *)(pv + 0x34)) {
    case 0:
        *(s32 *)(pv + 0x1C) += 1;
        if (*(s32 *)(pv + 0x1C) >= 0x5A) {
            *(u16 *)(pv + 0x34) += 1;
            func_8012E88C(pv);
            func_8012A828(pv, D_801BAEF0);
        }
        break;
    case 1:
        func_801834F0(pv, D_801910C8, (void *)0xFFFA0000);
        func_8012AD80(pv);
        func_801833E4(pv);
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, D_801910C8) < 0x401) {
            *(u16 *)(pv + 0x34) += 1;
        }
        break;
    case 2:
        func_801834F0(pv, D_801910D0, (void *)0xFFFA0000);
        func_8012AD80(pv);
        func_801833E4(pv);
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, D_801910D0) < 0x401) {
            *(s32 *)(pv + 0x1C) = 0;
            *(u16 *)(pv + 0x34) += 1;
            func_8012A828(pv, D_80190F78);
        }
        break;
    case 3:
        *(s32 *)(pv + 0x1C) += 1;
        if (*(s32 *)(pv + 0x1C) >= 0x3C) {
            *(s32 *)(pv + 0x1C) = 0;
            *(u16 *)(pv + 0x34) += 1;
            func_8012A828(pv, D_801BAE98);
            *(s16 *)(pv + 0xFC) = 0;
        }
        break;
    case 4:
        if (*(s16 *)(pv + 0xFC) == 1) {
            *(s32 *)(pv + 0x1C) = 0;
            *(u16 *)(pv + 0x34) += 1;
            func_8012A828(pv, D_801BAEF0);
        }
        break;
    case 5:
        func_801833E4(pv);
        *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) -= 0x44;
        *(s32 *)(pv + 0x1C) += 1;
        if (*(s32 *)(pv + 0x1C) >= 0xF) {
            *(s32 *)(pv + 0x1C) = 0;
            *(u16 *)(pv + 0x34) += 1;
        }
        break;
    case 6:
        func_801833E4(pv);
        func_801834F0(pv, &D_80190D94, (void *)0xFFFA0000);
        func_8012AD80(pv);
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)&D_80190D94) < 0x401) {
            *(u16 *)(pv + 0x34) += 1;
        }
        break;
    case 7:
        func_8012C218((void *)pv);
        break;
    }
}


void func_801833E4(s32 a0)
{
    extern u16 D_800B99DA;
    extern s16 D_801910D8;
    extern s16 D_801910DA;
    extern s32 func_80132EF4(s32 a0, s32 a1);
    u32 buf[2];
    s32 ang;
    s32 full;
    s32 s1;

    if ((D_800B99DA & 7) == 0) {
        s1 = func_80132EF4(a0, 0x22);
        if (s1 != 0) {
            *(u16 *)(s1 + 0x34) = 0x1000;
            ang = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            func_8012B0B4(buf, ang, D_801910D8);
            full = *(s32 *)buf;
            *(s16 *)(s1 + 6) = *(u16 *)(s1 + 6) + full;
            *(s16 *)(s1 + 0xE) = *(u16 *)(s1 + 0xE) + (full >> 16);
            *(s32 *)(s1 + 0x10) = func_80047948(ang) * D_801910DA;
            *(s32 *)(s1 + 0x18) = func_8004787C(ang) * D_801910DA;
        }
    }
}



extern void (*D_801910DC[])(void);

void func_801834B4(void *a0) {
    D_801910DC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801834F0(s32 a0, void *a1, void *a2) {
    s32 s0 = a0;
    s32 s1 = (s32)a2;
    s32 v0;

    v0 = func_8012B744((void *)(s0 + 4), a1);
    v0 = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), v0, 8);
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
    func_8012B2CC(s0);
    func_8012B178(s0, s1);
}


void func_80183564(void *arg0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32  func_80029504(void);
    extern s32  func_80029178(s32 arg);
    extern u8   D_801F9F30[];

    s32 v0;

    if (func_80029504() != 0x4B0) {
        func_8012CAE4(arg0);
        return;
    }
    if ((func_80029178(0x138) & 0xFF) != 0) {
        func_8012CAE4(arg0);
        return;
    }

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
        return;
    }

    func_8001C214(v0, (s32)D_801F9F30);
    *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    func_80183118(arg0);
    func_8012C588(0x3C9, (s32)arg0);
}


extern s32 *D_80126B78;

void func_801835FC(void *arg0)
{
    *(s16 *)((s32)D_80126B78 + 0x10) = 0;
}



extern void func_8012BE98(s32 a0, u16 *a1);
    extern s32 D_80190D9C;
    s32 func_8018360C(s32 arg0) {
        return ((s32 (*)(s32, void *))func_8012BE98)(arg0, &D_80190D9C) < 0x401;
    }


extern void func_8012BE98(s32 a0, u16 *a1);
    extern s32 D_80190DA4;
    s32 func_80183634(s32 arg0) {
        return ((s32 (*)(s32, void *))func_8012BE98)(arg0, &D_80190DA4) < 0x401;
    }


void func_8018365C(void *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }


extern void func_801834F0(s32 a0, void *a1, void *a2);
extern void func_8012AD80(s32 a0);
extern void func_8012BE98(s32, u16*);
extern s32 D_80190D94;

void func_80183668(s32 param_1) {
    if (*(s16 *)(param_1 + 0xFC) != 1) {
        if (*(s16 *)(param_1 + 0xFC) >= 2) {
            return;
        }
        if (*(s16 *)(param_1 + 0xFC) != 0) {
            return;
        }
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) -= 0x3B;
        *(s32 *)(param_1 + 0x1C) += 1;
        if (*(s32 *)(param_1 + 0x1C) < 0x1E) {
            return;
        }
    } else {
        func_801834F0(param_1, &D_80190D94, (void *)0xFFFC0000);
        func_8012AD80(param_1);
        if (((s32 (*)(s32, u16 *))func_8012BE98)(param_1, &D_80190D94) >= 0x401) {
            return;
        }
    }
    *(u16 *)(param_1 + 0xFC) += 1;
}


s32 func_80183738(s32 *a0) {
        return *(s16 *)((s32)a0 + 0xFC) > 0;
    }


extern s32 func_8012E544(s32 a0);

void func_80183744(void) {
    s32 v0 = func_8012E544(0x3c9);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 1;
    }
}


extern void func_80029124(s32 arg0, s32 arg1);
extern void func_800D0CA0(s32 arg0);

void func_80183774(void) {
    func_80029124(0x138, 1);
    func_800D0CA0(1);
}


extern s16 func_800D0CE0(void);
s32 func_801837A0(void) {
    return ((s32 (*)(void))func_800D0CE0)() == 1;
}


#include "common.h"

extern s32 func_8016F1AC(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012C218(void*);
extern u8 D_80190DC8[];

void func_801837C4(s32 arg0) {
    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        if (func_8016F1AC() == 0) {
            *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
            func_80178B18(arg0, (s32)&D_80190DC8);
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)(arg0) != 0) {
            ((void (*)(s32))func_80178D18)(arg0);
            *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
            ((void (*)(void *))func_8012C218)(arg0);
        }
        break;
    case 2:
    default:
        break;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);

void func_80183864(void *a0) {
    extern u8 D_801BD274[];
    extern u8 D_801BAEF0[];
    extern void (*D_801910C0[])(void);
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)D_801BD274);
        *(s16 *)((s32)a0 + 0x34) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 2) += 1;
        *(u16 *)((s32)a0 + 0x5C) |= 0x10;
        func_8012A828((s32)a0, D_801BAEF0);
        func_8012E8E0((s32)a0, (s32)D_801910C0);
        func_8012E8A8((u8 *)a0);
    }
}


extern void (*D_801BFF04[])(void);
extern s32 func_8012C044(s32 a0);
extern void func_801846D0(void *a0);

void func_801838FC(void *a0) {
    D_801BFF04[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        void *ptr = *(void **)((s32)a0 + 0x20);
        *(u16 *)((s32)ptr + 0x2C) |= 0x10;
        if (!(*(u16 *)((s32)a0 + 0x70) & 0x800)) {
            if (func_8012C044((s32)a0) == 1) {
                *(s32 *)((s32)a0 + 0xE4) = 1;
                func_801846D0(a0);
            }
        }
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80143970(s32 a0);

extern s32 D_801BFE40;
extern s32 D_801BFE74;
extern short D_801C553C;

void func_801839A4(s32 param_1) {
    if (func_8012C354(param_1, (s32)&D_801BFE40) != 0) {
        *(u8 *)(param_1 + 0xC0) = 1;
        *(s32 *)(param_1 + 0xBC) = (s32)&D_801BFE74;
        *(s32 *)(param_1 + 0xB4) = 0xFFFBDFDD;
        *(s16 *)(param_1 + 0xDE) = 0;
        *(s32 *)(param_1 + 0xC4) |= 1;
        func_8012A828(param_1, (void *)&D_801C553C);

        *(s16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        if ((*(u16 *)(param_1 + 0x70) & 1) != 0) {
            *(s16 *)(param_1 + 0x2) = 1;
            *(s16 *)(param_1 + 0x5C) = 0;
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4) |= 0x80000000;
        } else {
            *(s16 *)(param_1 + 0x2) = 3;
            *(s32 *)(param_1 + 0xCC) = func_80143970(param_1);
        }
    }
}


#include "common.h"

extern void func_8012BD14(s32 a0);
extern s32 func_80143970(s32 a0);
extern s32 D_801BFE40;

void func_80183A70(s32 a0) {
    s32 mask;
    s32 p;

    if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x18FFF) {
        return;
    }

    mask = 0x7FFFFFFF;

    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x10;

    *(s32 *)((*(s32 *)(a0 + 0x20)) + 0x4) &= mask;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x2C) |= 0x10;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x1C) = 1;
    *(u16 *)(p + 0x1A) = 1;
    *(u16 *)(p + 0x18) = 1;

    *(s32 *)(a0 + 0xCC) = func_80143970(a0);

    *(u16 *)(a0 + 0x76) = *(u16 *)&D_801BFE40;
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80047948(s32 a0);
extern u16 D_801BFE42;

void func_80183B14(s32 s0) {
  if (func_8012BEE8(s0) != 0) {
    s32 p = *(s32 *)(s0 + 0x20);
    s32 h = *(u16 *)(p + 0x2C);
    h &= 0xFFEF;
    *(s16 *)(p + 0x2C) = h;
    *(s16 *)(s0 + 0x2) = 3;
    *(s16 *)(s0 + 0x5C) = D_801BFE42;
  } else {
    s32 a0;
    s32 r;
    s32 q;
    a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 4;
    r = func_80047948(a0);
    q = *(s32 *)(s0 + 0x20);
    *(s16 *)(q + 0x1C) = r;
    *(s16 *)(q + 0x1A) = r;
    *(s16 *)(q + 0x18) = r;
  }
}



extern void func_8012A828(s32, void*);
    extern short D_801C553C;
    void func_80183B9C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801C553C);
    }


extern s32 func_8012BCCC(s32 a0);
void func_80183BC8(s32 a0) {
    s32 v0 = func_8012BCCC(a0);
    if (v0 <= 0x18000) {
        *(s16 *)(a0 + 0x2) = 5;
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C554C;

void func_80183C08(s32 param_1) {
    *(u16 *)(param_1 + 2) = 6;
    func_8012A828(param_1, (void *)&D_801C554C);
    *(s32 *)(param_1 + 0x1C) = 0x17;
    *(u16 *)(param_1 + 0x34) = 0;
}


extern s32 func_8012BEE8(s32 a0);
extern u8 D_80078EAE;

void func_80183C4C(s32 param_1) {
    if (D_80078EAE != 0) {
        if (*(u16 *)(param_1 + 0x34) == 0 && *(s32 *)(param_1 + 0x94) == 10) {
            *(u16 *)(param_1 + 0x98) = 0;
            *(u16 *)(param_1 + 0x34) += 1;
        }
    } else {
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 2) = 7;
        }
    }
}


extern void func_8012B23C(s32 a0);
extern s32 func_80184300(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C5614;

void func_80183CC4(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x8;
    func_8012B23C(s0);
    func_80184300(s0);
    func_8012A828(s0, (void *)&D_801C5614);
    *(s32 *)((s32)a0 + 0x1C) = 0x2D;
    *(s32 *)((s32)a0 + 0xE0) = 0;
}


#include "common.h"

extern s32 func_80184380(void *a0);
extern s32 func_8012E778(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_801841E4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80184300(s32 a0);

void func_80183D18(void *a0) {
    s32 s0 = (s32)a0;
    s32 s1;
    s32 v1_addr;
    u16 v0_val;

    // Load pointer from offset 0x20 and modify value at offset 0x12
    v1_addr = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1_addr + 0x12) = (u16)((*(u16 *)(v1_addr + 0x12)) - 0x71);

    // Call func_80184380 with original parameter
    func_80184380(a0);

    // Check if bit 0x4000 is set in u16 at offset 0x72
    v0_val = *(u16 *)(s0 + 0x72);
    if (v0_val & 0x4000) {
        if (func_8012E778(s0, 0x8C00B4) == 1) {
            func_8002D4C8(0x662, 0);
        }
    }

    // Call func_801841E4
    s1 = func_801841E4(s0);

    // If s1 != -1
    if (s1 != -1) {
        // If func_8012BEE8 returns non-zero
        if (func_8012BEE8(s0) != 0) {
            // If s1 != 0, call func_80184300
            if (s1 != 0) {
                func_80184300(s0);
            }
            // Set s0[0x1C] = 0x23
            *(s32 *)(s0 + 0x1C) = 0x23;
        }
    }
}


void func_80183DD4(s32 a0) {
    s32 obj;
    u16 val1;
    u16 val2;

    obj = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x5C) = 0;
    *(s16 *)(a0 + 0x98) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
    *(u16 *)(obj + 0x2C) |= 0x10;
    if (*(s16 *)(a0 + 0xAA) == 0) {
        val1 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(s16 *)(a0 + 0x106) = 0;
        *(u16 *)(a0 + 0x100) = val1;
    } else {
        val2 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(s16 *)(a0 + 0x106) = 1;
        *(u16 *)(a0 + 0x104) = val2;
    }
}



// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @unstuck(P36): none - MATCH (41 ins), match_one + rtu_match.
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

void func_80183E3C(s32 param_1) {

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
        m = *(s16 *)(param_1 + 0x104);
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


void func_80183EE0(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_80183EF0(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        if (*(s16 *)(param_1 + 0x106) != 0) {
            p = *(s32 *)(param_1 + 0x20);
            *(s16 *)(p + 0x1C) = 0x1000;
            *(s16 *)(p + 0x18) = 0x1000;
            *(s16 *)(param_1 + 0x106) = 0;
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


extern s32 func_8012BCCC(s32 a0);
extern u8 D_801C57D4[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80183FC8(s32 param_1) {
    s32 ptr;
    s32 ret;
    s32 k;

    ptr = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 0x5C) = 0;
    *(s32 *)(param_1 + 0x1C) = 0x37;
    *(u16 *)(ptr + 0x10) = 0;
    func_8012A828(param_1, D_801C57D4);
    *(u16 *)(param_1 + 0x34) = 0;
    ret = func_8012BCCC(param_1);
    k = 0x52B;
    if (!(0x8FFF < ret)) {
        k = 0x52A;
    }
    func_8002D4C8(k, 0);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_801846D0(void *a0);

void func_80184034(s32 a0) {
    if (*(s32 *)(a0 + 0x1C) < 0xC) {
        s32 mask;
        s32 ptr;
        s32 val;

        mask = 0x80000000;
        ptr = *(s32 *)(a0 + 0x20);
        val = *(s32 *)(ptr + 0x4);
        val ^= mask;
        *(s32 *)(ptr + 0x4) = val;
    }

    if (func_8012BEE8(a0) != 0) {
        func_80130D48(a0);
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) = 0x80000000;
        func_801846D0(a0);
    }
}


void func_801840B8(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        *(short *)((char *)a0 + 0xfe) = 0;
        *(unsigned short *)((char *)a0 + 0x5c) = 0xaa10;
        *(short *)((char *)a0 + 0x102) = 1;
    }


void func_801840D8(void) {
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018C090(s32 a0, u16 *a1, s16 a2);

void func_801840E0(void *a0) {
    s16 sp10[3];
    u16 id;

    id = *(u16 *)(a0 + 0x5E);
    if (id == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        func_8002D4C8(0xAA1, 0);
    } else if (id == 0x24) {
        sp10[2] = 0;
        sp10[0] = 0;
        sp10[1] = -8;
        func_8018C090((s32)a0, (u16 *)sp10, 0xB);
    }
}



/* func_8018415C — light/colour ramp-up on the entity's attached prim block.
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
void func_8018415C(int param_1) {
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

extern void func_8012ADE4(u8 *a0);
extern s32 func_8012AF0C(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern u8 D_801202A0[];

/* func_8018450C lives in the same TU (later INCLUDE_ASM), no prior decl exists
   in this TU -- type by call-site width: two s32 args, return value unused. */
extern void func_8018450C(s32 a0, s32 a1);

/* func_801841E4 -- entity "aggro/hostility" broadcast: query the entity's own
 * status flags via func_8012CBA4(); depending on which bits are set, tell the
 * entity to react (func_8012ADE4) and/or push notify id 2 (func_8018450C).
 * A special status byte (== 2) short-circuits into func_80131E00(obj, 0x12)
 * and returns -1 immediately.  Otherwise walk the 0x60-entry, 0x10C-stride
 * entity table at D_801202A0 looking for another live entry of the SAME kind
 * (u16 at offset 0) that isn't this entity itself and that func_8012AF0C()
 * accepts; on the first hit, either bail out returning 0 (if the flags block
 * already zeroed the state var) or notify (func_8018450C) once more and
 * return the un-zeroed state var (1).
 */
s32 func_801841E4(s32 a0) {
    s32 obj;
    s32 state;
    s32 flags;
    u8 *p;
    s32 i;

    obj = a0;
    state = 1;

    flags = ((s32 (*)(s32))func_8012CBA4)(a0);

    if (flags == 0) {
        goto call_ade4;
    }
    if ((flags & 0xFF) == 2) {
        ((void (*)(s32, s32))func_80131E00)(obj, 0x12);
        return -1;
    }
    if ((flags & 0x8000) != 0) {
        if ((flags & 0x2000) != 0) {
            goto call_notify;
        }
    } else {
        if ((flags & 0x4000) == 0) {
            goto walk;
        }
    }

call_ade4:
    func_8012ADE4((u8 *)obj);

call_notify:
    func_8018450C(obj, 2);
    state = 0;

walk:
    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(u16 *)obj == *(u16 *)p && obj != (s32)p) {
            if (func_8012AF0C(obj, (s32)p) != 0) {
                if (state != 0) {
                    func_8018450C(obj, 2);
                }
                break;
            }
        }
    }
    return state;
}


extern s32 func_80184800(s32 a0);

s32 func_80184300(s32 a0) {
    s32 s0 = a0;

    if (*(s16 *)(s0 + 0xAA) > 0) {
        func_8018450C(s0, 4);
        return 0;
    }
    if (func_8012BCCC(s0) > 0x24000 || func_80184800(s0) == 0) {
        func_8018450C(s0, 3);
        return 0;
    }
    func_8018450C(s0, 0);
    return 1;
}









extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

s32 func_80184380(void *arg0) {
    s16 pointA[3];
    s16 pointB[3];
    s16 diff[3];
    s32 addr;

    pointA[0] = D_80126B5E;
    pointA[1] = D_80126B62;
    pointA[2] = D_80126B66;

    pointB[0] = *(u16 *)((s32)arg0 + 0x6);
    pointB[1] = *(u16 *)((s32)arg0 + 0xA);
    pointB[2] = *(u16 *)((s32)arg0 + 0xE);
    pointA[1] = D_80126B62 - 0x2A;

    addr = (*(s32 *)((s32)arg0 + 0x58) & 0xFFFFFFF) | 0x80000000;

    if (*(s16 *)(addr + 0x4) + pointB[0] > pointA[0]) {
        return 0;
    }
    if (*(s16 *)(addr + 0x6) + pointB[0] < pointA[0]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xC) + pointB[2] > pointA[2]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xE) + pointB[2] < pointA[2]) {
        return 0;
    }
    if (*(s16 *)(addr + 0x8) + pointB[1] > pointA[1]) {
        return 0;
    }
    if (*(s16 *)(addr + 0xA) + pointB[1] < pointA[1]) {
        goto ret0;
    }

    diff[0] = pointA[0] - pointB[0];
    diff[1] = pointA[1] - pointB[1];
    diff[2] = pointA[2] - pointB[2];

    VectorNormalSS(diff, diff);
    func_8012F568(1, 1, *(s16 *)((s32)arg0 + 0xDC), 0xD, (s32)pointA, (s32)diff);
    return 1;

ret0:
    return 0;
}


extern u8 D_80078EAE;
extern u8 D_80078E78[];
extern s32 rand(void);
extern s32 func_8012B864(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018450C(s32 a0, s32 a1) {
    typedef struct { s32 m[8]; } Mtx8_8017DE10_8017E710;
    extern Mtx8_8017DE10_8017E710 D_800AE620;
    s32 obj;
    s32 cur;
    s32 r2;
    s32 flag;
    u8 *base;
    s32 vec[3];
    Mtx8_8017DE10_8017E710 m;
    s32 off;
    s32 val;

    obj = a0;
    flag = D_80078EAE;
    base = D_80078E78;
    vec[1] = 0;
    vec[0] = 0;
    if (flag) {
        vec[2] = (s32)0xFFFA0000;
    } else {
        vec[2] = (s32)0xFFF80000;
    }

    switch (a1) {
    case 0:
        if (base[0x36] != 0 && (rand() & 1) != 0) {
            break;
        }
        /* fall through */
    case 1:
        *(s16 *)(obj + 0xDC) = func_8012B864(obj);
        break;
    case 2:
        off = rand() % 512;
        cur = *(s16 *)(obj + 0xDC);
        if ((rand() & 1) == 0) {
            r2 = cur + 0x800;
            r2 = r2 - off;
        } else {
            r2 = cur + 0x800;
            r2 = r2 + off;
        }
        *(s16 *)(obj + 0xDC) = r2;
        break;
    case 3:
        do {
            val = rand() % 0x1000;
        } while (*(s16 *)(obj + 0xDC) == (s16)val);
        break;
    case 4:
        *(s16 *)(obj + 0xDC) = (func_8012B864(obj) + 0x800) & 0xFFF;
        break;
    }

    m = D_800AE620;
    RotMatrixY(*(s16 *)(obj + 0xDC), &m);
    func_800484EC((s32)&m, (s32)vec, obj + 0x10);
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8002A04C(s32 a0);
extern s32 func_801439C0(s32 a0);
extern void func_8012C218(void *a0);
extern short D_801C553C;

void func_801846D0(void *a0) {
    s32 s0 = (s32)a0;
    s32 p20a;

    *(s16 *)(s0 + 0x76) = 0;

    if (*(s32 *)(s0 + 0xE4) == 0) {
        p20a = *(s32 *)(s0 + 0x20);
        *(u8 *)(s0 + 0xC1) = 0;
        *(s16 *)(s0 + 0x2) = 1;
        *(s32 *)(p20a + 0x4) |= 0x80000000;

        {
            s32 p20b = *(s32 *)(s0 + 0x20);
            *(s16 *)(s0 + 0x5E) = 0;
            *(s16 *)(s0 + 0x5C) = 0;
            *(s16 *)(p20b + 0x14) = 0;
            *(s16 *)(p20b + 0x12) = 0;
            *(s16 *)(p20b + 0x10) = 0;
        }

        {
            s32 p20c = *(s32 *)(s0 + 0x20);
            *(u16 *)(p20c + 0x1C) = 0x1000;
            *(u16 *)(p20c + 0x1A) = 0x1000;
            *(u16 *)(p20c + 0x18) = 0x1000;
        }

        {
            u16 t88 = *(u16 *)(s0 + 0x88);
            u16 t8A = *(u16 *)(s0 + 0x8A);
            *(s16 *)(s0 + 0xDE) = 0;
            *(s16 *)(s0 + 0xAA) = 0;
            *(u16 *)(s0 + 0x6) = t88;
            *(u16 *)(s0 + 0xA) = t8A;
            *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0x8C);
            func_8012A828(s0, (void *)&D_801C553C);
        }
        func_8012B2CC(s0);
        func_8002A04C(s0);

        if (*(s32 *)(s0 + 0xCC) != 0) {
            func_801439C0(*(s32 *)(s0 + 0xCC));
        }
    } else {
        s32 p68;

        if ((*(s16 *)(s0 + 0x70) & 0x8000) == 0) {
            p68 = *(s32 *)(s0 + 0x68);
            if (p68 != 0) {
                if (*(s16 *)(s0 + 0x72) & 0x8000) {
                    *(u16 *)(p68 + 0xA) = *(u16 *)(p68 + 0xA) & 0x7FFF;
                }
            }
        }
        func_8012C218((void *)s0);
    }
}




s32 func_80184800(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


extern s32 D_801C5B08[];
extern s32 func_8012C044(s32 a0);
extern void func_80185D20(s32 a0);

void func_80184860(void *a0)
{
    s32 v0, v1;

    
    v0 = *(u16 *)((u8 *)a0 + 2);
    v0 = v0 << 2;
    v1 = *(s32 *)((s32)D_801C5B08 + v0);
    ((void (*)(void))v1)();

    
    v0 = *(u16 *)a0;
    if (v0 != 0) {
        v0 = *(u16 *)((u8 *)a0 + 0xFE);
        v0 = v0 + 0x80;
        *(u16 *)((u8 *)a0 + 0xFE) = v0;
        v0 = func_8012C044((s32)a0);

        if (v0 == 1) {
            *(u16 *)((u8 *)a0 + 0x100) = 1;
            func_80185D20((s32)a0);
        }
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32, s32);

extern u8 D_801C5954[];
extern u8 D_801C8CBC[];
extern u8 D_801C5A68[];

void func_801848E4(s32 a0)
{
    unsigned short v0;
    s32 ptr;

    if (func_8012C354(a0, (s32)D_801C5954) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xBC) = (s32)D_801C5A68;
    *(s32 *)(a0 + 0xB4) = -0x20AD;
    *(s32 *)(a0 + 0xE0) = 0;
    *(s32 *)(a0 + 0xC4) |= 1;
    func_8012A828(a0, (void *)D_801C8CBC);

    v0 = *(unsigned short *)(a0 + 0x70);
    if (v0 & 0x1) {
        *(unsigned short *)(a0 + 0x2) = 1;
        *(unsigned short *)(a0 + 0x5C) = 0;
        ptr = *(s32 *)(a0 + 0x20);
        *(s32 *)(ptr + 0x4) |= 0x80000000;
    } else {
        *(unsigned short *)(a0 + 0x2) = 3;
        *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
    }
}


#include "common.h"

extern s32 func_8012E778(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012BD14(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_801849A0(s32 a0)
{
    s32 t;
    s32 u;
    s32 p;

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

    *(u16 *)((*(s32 *)(a0 + 0x20)) + 0x2C) |= 0x10;

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


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_80184A94(s32 s0) {
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


extern u8 D_801C8CBC[];
extern void func_8012A828(s32, void*);

void func_80184B30(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, D_801C8CBC);
    *(s32 *)(param_1 + 0x1C) = 0x20;
    if (*(s32 *)(param_1 + 0xE0) != 0) {
        *(s32 *)(param_1 + 0xE0) = 0;
        *(s16 *)(param_1 + 0xA) = *(s16 *)(param_1 + 0xA) + 0x30;
    }
}


extern s32 func_80185E8C(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_80184B90(s32 s0) {
  s32 v0;
  s32 v1;

  v0 = *(s32 *)(s0 + 0x20);
  v1 = *(u16 *)(v0 + 0x12) + 0x40;
  *(s16 *)(v0 + 0x12) = v1;
  if (func_80185E8C(s0) != 1) {
    if (func_8012BEE8(s0) != 0) {
      *(s16 *)(s0 + 0x2) = 5;
    }
  }
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801C8CBC[];

void func_80184BF0(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 6;
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE8000);
    func_8012A828(s0, (void *)D_801C8CBC);
    *(s32 *)(s0 + 0x1C) = 0x96;
    *(u16 *)(s0 + 0xE6) = 0;
}


extern u8 D_800D3918[];
extern s32 func_80185E8C(s32 arg0);

void func_80184C4C(s32 arg0) {
    if (func_80185E8C(arg0) != 1) {
        if (func_80185BD4(arg0, D_800D3918) == 0) {
            *(s16 *)(arg0 + 2) = 3;
        }
    }
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C8DB4;

void func_80184C9C(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 8;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801C8DB4);
    *(s32 *)(s0 + 0x1C) = 0x24;
    *(u16 *)(s0 + 0xE6) = 0;
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80185BD4(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012B178(s32 a0, s32 a1);

void func_80184CE8(s32 a0)
{
    s32 s0;
    s32 v1;
    u16 v0;
    u16 *p;

    s0 = a0;
    v0 = func_8012B8E4(s0, 8);
    p = *(u16 **)(s0 + 0x20);
    p[9] = p[9] + (u16)v0;

    if (*(s32 *)(s0 + 0x1C) < 0x19) {
        func_8012B178(s0, 0xFFFC0000);
        v1 = func_80185BD4(s0, (void *)D_800D3918);

        if (v1 == 0) {
            v0 = 9;
            goto L_store;
        }
        v0 = -1;
        if (v1 == -1) {
            
            return;
        }
        
    }

    if ((func_8012BEE8(s0)) != 0) {
        v0 = 9;
    } else {
        if ((func_8012BCCC(s0)) < 0x2001) {
            v0 = 9;
        } else {
            return;
        }
    }

L_store:
    *(s16 *)(s0 + 0x2) = v0;
}



















void func_80184D98(void *a0)
{
  s32 v1 = *((s32 *) (((s32) a0) + 0x20));
  int new_var;
  *((s16 *) (((s32) a0) + 0x2)) = 0xA;
  *((s16 *) (((s32) a0) + 0x5C)) = 0;
  *((s16 *) (((s32) a0) + (new_var = 0x34))) = 0;
  *((s32 *) (((s32) a0) + 0x1C)) = 0x8;
  *((s16 *) (((s32) v1) + 0x2C)) |= 0x10;
}



extern s32 func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_801859E4(s32 a0);

void func_80184DC8(s32 param_1)
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
            func_801859E4(param_1);
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


extern s32 D_801C8E8C;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80184FDC(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xC;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801C8E8C);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
    func_8012B23C(s0);
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80185BD4(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012B178(s32 a0, s32 a1);

void func_80185030(s32 s0) {
    s32 v0;
    s32 v1;

    v0 = func_8012B8E4(s0, 8);
    v1 = *(s32*)(s0 + 0x20);
    *(s16*)(v1 + 0x12) = (s16)(*(u16*)(v1 + 0x12) + v0);
    func_8012B178(s0, 0xFFFC0000);
    v0 = func_80185BD4(s0, D_800D3918);
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


extern u8 D_801C8F64[];
extern void func_8012A828(s32 a0, void *a1);

void func_801850D8(param_1)
s32 param_1;
{
    *(s16 *)(param_1 + 2) = 0xE;
    func_8012A828(param_1, D_801C8F64);
    *(s32 *)(param_1 + 0x1C) = 0x5A;
    *(s16 *)(param_1 + 0xDC) = 0;
    *(s16 *)(param_1 + 0xFE) = 0;
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018584C(s32 a0);

void func_80185120(void *a0)
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
                func_8018584C(s0);
            }
        } else {
            func_8018584C(s0);
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


extern s32 D_801C8DB4;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_801851F4(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x10;
    func_8012B2CC(s0);
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFD0000);
    func_8012A828(s0, (void *)&D_801C8DB4);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80185BD4(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern s32 D_801C8DB4;

void func_80185254(s32 a0) {
    if (*(s16 *)(a0 + 0xAA) <= 0) {
        *(u16 *)(a0 + 2) = 3;
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, (void *)&D_801C8DB4);
            *(s32 *)(a0 + 0x1C) = 0x1A;
        }
        func_80185BD4(a0, (s32)D_800D3918);
    }
}


void func_801852C8(void *a0)
{
    s32 a1;
    s32 b;
    u16 v1;

    a1 = *(s32 *)((s32)a0 + 0x20);
    v1 = *(u16 *)(a1 + 0x2C);
    if (v1 & 0x10) {
        *(u16 *)(a1 + 0x2C) = v1 & 0xFFEF;
        b = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(b + 0x1C) = 0x1000;
        *(u16 *)(b + 0x1A) = 0x1000;
        *(u16 *)(b + 0x18) = 0x1000;
    }
}


void func_80185304(s32 a0) {
    extern s32 func_8012B864(s32 a0);

    s32 s0 = a0;
    *(s16 *)(s0 + 2) = 0xF;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (func_8012B864(s0) + 0x800) & 0xFFF;
}


extern void func_80131B14();
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C93D4;

void func_80185344(s32 s0) {
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
    func_8012A828(s0, (void *)&D_801C93D4);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern u8 D_801C5B4C[];
extern u8 D_801C5B58[];
extern u8 D_801C9454[];

void func_801853B4(s32 a0) {
    s32 s0 = a0;
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
        func_8012B14C(s0, (s32)D_801C5B4C);
        v0 = 0xCC;
    } else {
        func_8012B14C(s0, (s32)D_801C5B58);
        v0 = 0x100;
    }
    *(u16 *)(s0 + 0xDE) = v0;

    func_8012A828(s0, (void *)D_801C9454);
}


#include "common.h"

// Decls follow the canonical set used across the codebase for these shared
// engine-core functions (see src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c L1590-1594
// and src/shared/engine_core.h): func_8012CC64/func_8012CBA4 canonical `void`
// with $v0 read via a call-site cast; func_80131E00 canonical K&R no-proto.
extern void func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern s32 D_801C5B64;

void func_8018549C(void *a0) {
    void *s0 = a0;
    s32 v0;
    s32 v1;
    s32 cnt;

    if (*(u8 *)(s0 + 0xC2) != 0) {
        goto L_reentry;
    }

    func_8012DBD0((s32)a0, 0x50,
                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) + 0x800, 0x1D);

    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) - *(u16 *)(s0 + 0xDE);

    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt >= 0x29) {
        goto L_call0xD;
    }

    v1 = ((s32 (*)(s32, s32))func_8012CC64)((s32)s0, (s32)&D_801C5B64);
    if ((v1 & 0x2000) == 0) {
        goto L_bit4000_a;
    }
    if ((v1 & 0xFF) != 2) {
        goto L_lh76_a;
    }
    ((void (*)(s32, s32))func_80131E00)((s32)s0, 0x12);
    return;

L_lh76_a:
    if (*(s16 *)(s0 + 0x76) <= 0) {
        ((void (*)(s32, s32))func_80131E00)((s32)s0, 6);
        return;
    }
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(s16 *)(s0 + 2) = 3;
    *(s32 *)(s0 + 0xE0) = 1;
    return;

L_bit4000_a:
    if ((v1 & 0x4000) == 0) {
        return;
    }
    v0 = *(u8 *)(s0 + 0xC2) + 1;
    *(u8 *)(s0 + 0xC2) = v0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    func_8012B23C((s32)s0);
    *(s32 *)(s0 + 0x1C) = 0;
    return;

L_reentry:
    v1 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if ((v1 & 0x2000) == 0) {
        goto L_finish;
    }
    if ((v1 & 0xFF) != 2) {
        goto L_lh76_b;
    }
    ((void (*)(s32, s32))func_80131E00)((s32)s0, 0x12);
    return;

L_lh76_b:
    if (*(s16 *)(s0 + 0x76) > 0) {
        goto L_setmode3;
    }
    ((void (*)(s32, s32))func_80131E00)((s32)s0, 6);
    goto L_finish;

L_setmode3:
    *(s16 *)(s0 + 2) = 3;
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(s32 *)(s0 + 0xE0) = 1;

L_finish:
    if ((*(s32 *)(s0 + 0x1C) & 3) == 3) {
        func_80143B6C((s32)s0, 1);
    }
    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt < 0x3D) {
        return;
    }

L_call0xD:
    ((void (*)(s32, s32))func_80131E00)((s32)s0, 0xD);
    return;
}


extern void func_8012E8A8(u8 *);
extern void func_8012A828(s32, void *);
extern s32 D_801C5A58;

void func_80185658(void *arg0) {
    s32 s0 = (s32)arg0;

    *(u16 *)(s0 + 0x5C) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(u16 *)(s0 + 0x34) = 0;
    func_8012E8A8((u8 *)arg0);
    func_8012A828((s32)arg0, (void *)&D_801C5A58);
}


#include "common.h"

/* func_801856A0 — ov_SC03_006 (TU: src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c)
 *
 * Near-identical twin of func_8018D574 (ov_SC02_011, seed_sim 0.5918) — same
 * SCHEDULE-REORDER/2 residual fix applies verbatim: drop the $18 pin on the
 * loop counter `i` and sink `i++` below the ternary merge (both the a0 setup
 * for func_80143BDC and i++ get scheduled together right after the ternary,
 * before the pos[1] store). Register pins (from the exemplar, confirmed by
 * this target's own asm): obj=$19(s3), tmp=$16(s0), t4=$20(s4), q1=$7(a3),
 * hi4=$3(v1). The third-branch callee here is func_80185D20 (this overlay's
 * sibling of the exemplar's func_8018DBF4).
 *
 * Decls copied verbatim from the destination TU's file-scope declarations
 * (src/ov_SC03_006/ov_SC03_006_jr_8017AE2C.c): func_8012BEE8, func_8002AC00,
 * func_8012B0B4, func_80143BDC (s32 return, u16* — not void), func_8012C658,
 * rand. func_80130D48 and func_80185D20 have no prior TU declaration, so
 * typed by call-site arity/width (single s32 arg, void return).
 */

extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 arg0);
extern void func_80185D20(s32 a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_80143BDC(u16 *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_801856A0(s32 a0) {
    s32 obj;
    s32 i;
    s32 t4;
    s32 tmp;
    s32 q1;
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
            func_80185D20(obj);
        }
        return;
    }

    i = 0;
    pbuf = (unsigned int *)&buf;
    for (; i < 10;) {
        r1 = rand();
        tmp = (r1 >= 0) ? r1 : (r1 + 0xFFF);
        ang1 = r1 - ((tmp >> 12) << 12);

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
                s32 hi4;
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



/* DEF-SIDE ALIAS (§37/§124, §136f#2): TU declares `extern s32 func_8018584C(s32)`
 * (TU:8796) and both callers discard the result; the real definition is
 * effectively VOID (nothing carried out in $v0 — §42d#1 inverse rule). */

void func_8018584C(s32 a0)
{
    extern u8 D_801C5A48[];
    extern u8 D_801C5A50[];

    s32 out0[2];   /* sp+0x10 */
    s32 out1[2];   /* sp+0x18 */
    s32 flag;      /* sp+0x20 */
    s32 *mtx;
    s32 t;

    mtx = *(s32 **)(a0 + 0x20) + 13;
    gte_SetRotMatrix(mtx);
    gte_SetTransMatrix(mtx);

    RotTransSV(D_801C5A48, out0, &flag);
    RotTransSV(D_801C5A50, out1, &flag);

    func_8018594C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                  (s32)out0,
                  *(s16 *)(a0 + 0xDC));
    func_8018594C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                  (s32)out1,
                  *(s16 *)(a0 + 0xDC));

    t = *(u16 *)(a0 + 0xDC) + 1;
    *(u16 *)(a0 + 0xDC) = t;
    if ((s16)t >= 3) {
        *(u16 *)(a0 + 0xDC) = 2;
    }
}


extern u32 D_801C5988[];
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_8001CD50(s32 a0, s32 a1);

u8 *func_8018594C(s16 a0, u8 *a1, s32 a2) {
    u8 *obj;
    u8 *sub;

    obj = func_801290DC(0x17, a1);
    if (obj == NULL) {
        return NULL;
    }

    sub = *(u8 **)(obj + 0x20);
    func_8001CD50((s32)sub, (s32)((u8 *)D_801C5988 + (a2 << 6)));

    *(u16 *)(sub + 0x1E) = 0xC00;
    *(u16 *)(sub + 0x1A) = 0x1000;
    *(u16 *)(sub + 0x18) = 0x1000;
    *(u16 *)(sub + 0x12) = a0;
    *(s32 *)(sub + 0x4) |= 0x40000000;

    return obj;
}


#include "common.h"

void func_801859E4(s32 a0) {
    /* [T51] Declarations scoped INTO the function, exactly as sibling
     * func_8018450C in this TU does: a file-scope decl of these symbols would
     * constrain every LATER function here (func_80186070 / func_80188410
     * re-declare D_800AE620 and RotMatrixY at file scope themselves).
     * Declaration-only move => byte-neutral (cookbook §103).
     * The two typedefs are local standalone-compile clones of
     * src/shared/engine_types.h -- match_one's isolated compile only has
     * -Iinclude and cannot resolve ../shared/engine_types.h, while the host TU
     * already pulls both in via engine_core.h. Same-shape clones, so they
     * merely shadow the real ones; block scope means they can never collide.
     * func_80185F5C is declared with an UNSPECIFIED parameter list on purpose:
     * its real definition later in this TU takes the file-scope SVECTOR*, and
     * an empty list is compatible with any prototype in C89 (pack §195-A). */
    typedef struct { s32 w[8]; } Mtx8_8017DE10_8017E710;
    typedef struct { short vx, vy, vz, pad; } SVECTOR;

    extern void func_8012B23C(s32 a0);
    extern s32  func_80185EFC(s32 a0);
    extern s32 func_80185F5C(void *a0, SVECTOR *a1);
    extern void func_8012ADE4(u8 *a0);
    extern s32  func_8012B864(s32 a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);
    extern Mtx8_8017DE10_8017E710 D_800AE620;
    extern s16 D_80126CB4;
    extern s16 D_80126CB6;
    extern s16 D_80126CB8;
    extern s32 *D_80126B78;

    /* Frame is 0x80 and every slot below is pinned by the target's offsets.
     * Declaration order == ascending sp offset, and any aggregate >= 8 bytes
     * is rounded up to an 8-byte boundary, which is what puts `mtx` on 0x48:
     *   vec 0x10  out 0x20  from 0x30  to 0x38  tmp 0x40  mtx 0x48  pos 0x68
     * `tmp` is never read.  The target reserves 0x40..0x47 all the same, so the
     * original declared a third SVECTOR here whose uses the optimiser removed;
     * dropping it shrinks the frame to 0x78 and moves five other slots. */
    s32 vec[3];
    s32 out[3];
    SVECTOR from;
    SVECTOR to;
    SVECTOR tmp;
    Mtx8_8017DE10_8017E710 mtx;
    s32 pos[3];
    s32 obj;

    obj = a0;
    func_8012B23C(a0);

    /* obj+0x38/0x3C/0x40 are the 16.16 position; these are their integer
     * halves (cookbook §194-G), i.e. where the entity is standing now. */
    from.vx = *(u16 *)(obj + 0x3A);
    from.vy = *(u16 *)(obj + 0x3E);
    from.vz = *(u16 *)(obj + 0x42);

    if (func_80185EFC(obj) == 0) {
        *(u16 *)(obj + 0x6) = *(u16 *)(obj + 0x88);
        *(u16 *)(obj + 0xA) = *(u16 *)(obj + 0x8A);
        *(u16 *)(obj + 0xE) = *(u16 *)(obj + 0x8C);
        return;
    }

    *(s16 *)(obj + 0x6) = D_80126CB4;
    *(s16 *)(obj + 0xA) = D_80126CB6;
    *(s16 *)(obj + 0xE) = D_80126CB8;

    vec[2] = (s32)0xFF600000;
    vec[1] = 0;
    vec[0] = 0;

    mtx = D_800AE620;
    RotMatrixY(*(s16 *)((s32)D_80126B78 + 0x12), &mtx);

    /* Hoisted out of the loop by hand: the target's `lw 0x8($s0)` / `sw
     * 0x6C($sp)` pair sits above .L80185B18, and pos[1] is never accumulated
     * into.  Written inside the loop, gcc cannot prove *(s32*)(obj+8) survives
     * the two calls and re-loads it every iteration (+2 instructions). */
    pos[1] = *(s32 *)(obj + 0x8);

    do {
        pos[0] = *(s32 *)(obj + 0x4);
        pos[2] = *(s32 *)(obj + 0xC);
        func_800484EC((s32)&mtx, (s32)vec, (s32)out);
        pos[0] += out[0];
        pos[2] += out[2];

        /* Cookbook §194-G -- the integer half of a 16.16 stack aggregate.
         * pos[0] and pos[2] were just stored in THIS basic block, so cse hands
         * any `>> 16` spelling back the live pseudo and emits `sra`; only a
         * narrow-typed lvalue at +2 can produce the target's `lhu`.  Same
         * spelling as the sibling func_80188AF4 in this TU.  (pos[1] is the
         * off-block case and would take `lh` from `>> 16`, so it is punned
         * too -- one spelling, three words, uniform bytes.) */
        to.vx = *((u16 *)&pos[0] + 1);
        to.vy = *((u16 *)&pos[1] + 1);
        to.vz = *((u16 *)&pos[2] + 1);

        if (func_80185F5C(&from, &to) == 1) {
            *(u16 *)(obj + 0x6) = to.vx;
            *(u16 *)(obj + 0xA) = to.vy;
            *(u16 *)(obj + 0xE) = to.vz;
            *(s32 *)(obj + 0x14) = 0;
            goto sync;
        }

        vec[2] >>= 1;
    } while (0xFFFF < -vec[2]);

    func_8012ADE4((u8 *)obj);

sync:
    *(s16 *)(*(s32 *)(obj + 0x20) + 0x12) = func_8012B864(obj);
}


#include "common.h"

/* func_80185BD4 -- mass-lane fresh crack (Phase 31 wave p31g)
 *
 * Same shape as func_8018DAA8 (ov_SC02_011, the atlas exemplar, already
 * matched): state-gate via func_8012CC1C, then "avoid overlapping same-kind
 * entity" scan of the 0x60-entry table at D_801202A0 (stride 0x10C).
 *
 * Symbols spelled from the target .s relocations only (§174 law 1):
 * func_8012CC1C, func_80131E00, func_8012ADE4, func_8012B6D4, func_8012B0B4,
 * func_8012BC60, D_801202A0.
 *
 * Callee types per this TU's own existing declarations (§174 law 2), copied
 * verbatim from ov_SC03_006_jr_8017AE2C.c:
 *   func_8012ADE4(u8 *a0)                              (line 4801)
 *   func_8012BC60(struct Vec *a0, struct Vec *a1)       (line 4805)
 *   func_8012B0B4(unsigned int*, int, int)              (line 5119)
 *   func_8012B6D4(s16 *a0, s16 *a1)                     (line 5138)
 *   func_80131E00()  (K&R empty-proto, called through a cast elsewhere)
 *                                                        (lines 7266/8756)
 * func_8012CC1C has no existing decl in this TU; the exemplar's own comment
 * records the canonical void/$v0-cast form used by sibling TUs
 * (ov_SC02_026/027/028's jr_* files) -- reused verbatim here.
 */

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

s32 func_80185BD4(s32 a0, s32 a1) {
    extern u8 D_801202A0[];
    s32 state;
    u8 *p;
    s32 i;
    s32 ang;
    s32 buf[2];

    state = ((s32 (*)(s32, s32))func_8012CC1C)(a0, a1);

    if ((state & 0xFF) == 2) {
        ((void (*)(s32, s32))func_80131E00)(a0, 0x12);
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
                    s32 t1 = *(s32 *)(p + 4);
                    s32 v1 = buf[0];
                    register s32 t2 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
                    s32 t3;
                    register s32 t4 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)

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

extern void func_8002A04C(s32);
extern void func_8002AC00(s32 arg0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801439C0(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);
extern u8 D_801C8CBC[];

void func_80185D20(s32 a0) {
    u16 v1;

    if (*(s16 *)(a0 + 0x100) == 0) {
        ((void (*)(void))func_8002A04C)();
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
        func_8012A828(a0, (void *)&D_801C8CBC);
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

s32 func_80185E8C(s32 obj) {
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




s32 func_80185EFC(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


#include "common.h"
#include "../shared/engine_types.h"

extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80134510(s32 arg);

s32 func_80185F5C(void *a0, SVECTOR *a1)
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



extern void (*D_801C5B6C[])(void);

void func_80186034(void *a0) {
    D_801C5B6C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Local standalone-compile clone of engine_types.h's Mtx8_8017DE10_8017E710
 * (match_one's isolated compile only has -Iinclude, can't resolve
 * ../shared/engine_types.h; the host TU already includes it via engine_core.h). */


extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern Mtx8_8017DE10_8017E710 D_800AE620;

void func_80186070(s32 a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80078EAE;
    Mtx8_8017DE10_8017E710 m;
    s32 vec[3];
    s32 p;
    u8 flag;

    flag = D_80078EAE;
    vec[1] = 0;
    vec[0] = 0;
    vec[2] = (flag == 0) ? (s32)0xFFFB8000 : (s32)0xFFFE8000;

    *(s16 *)(a0 + 0x2C) = 0x3C;
    *(s16 *)(a0 + 0x2) = 1;

    m = D_800AE620;

    p = *(s32 *)(a0 + 0x20);
    RotMatrixY(*(s16 *)(p + 0x12), &m);

    func_800484EC((s32)&m, (s32)vec, a0 + 0x10);
}


void func_80186140(s32 a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    extern u16 D_801270C0;
    s32 s0;

    if (*(s16 *)&D_801270C0 == 2) {
        return;
    }
    func_801861D8((void *)a0);
    if ((*(s16 *)(a0 + 0x2C))-- < 0) {
        func_801292C8((u8 *)a0);
    } else {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) += 0x100;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) += 0x100;
        func_8012931C((struct vec *)a0);
    }
}


#include "common.h"

extern s32 D_80126B58;
extern u8  D_80078E78[];

extern s32 func_8014CAFC(void);
extern s32 func_80186334(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_801861D8(void *arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
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

    if (func_80186334(arg0) == 0) {
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

/* func_80186334 — structurally identical to the TU-proven-MATCH sibling
 * func_8018E208 (ov_SC02_011, cookbook family). Same computed MATRIX
 * (func_80020DA4 + func_80020F34, translation overwritten from the entity's
 * s16 position), same 4-iteration loop over two advancing per-overlay
 * vertex-pair pointers (D_801C5B74 / D_801C5B74+0x20), same
 * func_80135888 hit test. */

extern s32 D_80126B58;                                     /* TU:52   verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1654 verbatim */
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); /* TU:583  verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);      /* TU:3111 verbatim */

/* neither is declared anywhere in this TU; func_80020DA4 takes the
 * (s32, s32) form of its TU-declared sibling func_80020F34.  D_801C5B74 is
 * per-overlay data. */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_801C5B74[];


s32 func_80186334(void *a0)
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

    base = D_801C5B74;
    p1 = base + 0x20;
    p0 = base;

    for (i = 0; i < 4; i++) {
        gte_SetRotMatrix(matrix);
        gte_SetTransMatrix(matrix);

        RotTransSV(p0, sv0, &flag);
        RotTransSV(p1, sv1, &flag);

        hit = func_80135888(*(s32 *)((u8 *)cfg + 0x20), *(s32 *)((u8 *)cfg + 0x38),
                            (s32)sv0, (s32)sv1);
        do { } while (0);   /* scheduling barrier — matched sibling note 3 */
        p1 += 8;
        if (hit != 0) {
            return 1;
        }
        p0 += 8;
    }
    return 0;
}



extern void (*D_801C5BD4[])(void);

void func_80186484(void *a0) {
    D_801C5BD4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801864C0(void *a0) {
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s32 *)((char *)a0 + 0x1c) = 2;
        *(s8 *)((char *)a0 + 0xfc) = 1;
        *(s8 *)((char *)a0 + 0xfe) = 2;
        *(s8 *)((char *)a0 + 0xfd) = 0;
        *(s8 *)((char *)a0 + 0xff) = 4;
        *(s16 *)((char *)a0 + 0xdc) = 0;
    }


extern s32 func_8012BEE8(s32 a0);

void func_801864F4(void *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_8018654C(0, (u8 *)arg0 + 0xFD);
        func_8018654C(1, (u8 *)arg0 + 0xFE);
        func_8018654C(2, (u8 *)arg0 + 0xFF);
        *(s32 *)((char *)arg0 + 0x1C) = 2;
    }
}


extern u32 D_801C5988[];
extern u32 D_801C5BB4[];
extern u32 D_801C5BCC;

void func_8018654C(s32 a0, u8 *a1) {
    u8 idx;
    u32 *dst;

    idx = *a1;
    if (idx >= 7) {
        *a1 = 0;
    }

    a0 <<= 6;
    idx = *a1;
    dst = (u32 *)((u8 *)D_801C5988 + a0);
    *dst = D_801C5BB4[idx];

    idx = *a1;
    dst++;
    if (idx - 1 < 0) {
        *dst = D_801C5BCC;
    } else {
        *dst = D_801C5BB4[idx - 1];
    }

    (*a1)++;
}



extern void (*D_801C5C08[])(void);

void func_801865E8(void *a0) {
    D_801C5C08[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern s32 D_801C5BDC[];
extern s32 D_801C5BE8[];
extern s32 D_801C5C00[];

void func_80186624(void *a0)
{
    s32 buf[8];
    u16 out[4];
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)() + 0;
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801C5BDC[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    *(s32 *)((s32)a0 + 0x1C) = 8;
    *(u16 *)((s32)a0 + 0x2) += 1;

    func_8012EC04(*(s32 *)((s32)a0 + 0x64), D_801C5BE8[*(u16 *)((s32)a0 + 0x70) & 0xF], buf);
    ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, (s32)D_801C5C00, out);

    *(u16 *)((s32)a0 + 0x6) = out[0];
    *(u16 *)((s32)a0 + 0xA) = out[1];
    *(u16 *)((s32)a0 + 0xE) = out[2];

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
}


extern s32 D_801C5BF4[];
extern s32 func_8012BEE8(s32 a0);

void func_80186710(s32 a0) {
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
    p = D_801C5BF4;
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

void func_801867A4(void *a0)
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

void func_801868AC(s32 param_1)
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


extern s32 func_80017758(void *a0, void *a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012B414(int a0);
extern void func_8012C218(void *a0);
    typedef struct { s16 vx; u16 vy; s16 vz, pad; } SVec_8017F67C_801869CC;
typedef struct { u8 d[4]; } Blk4_8017CE90_8017F32C_801869CC;

typedef struct { s16 vx, vy, vz, pad; } SVec8_8018E8A0_801869CC;          /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } Vec16_8018E8A0_801869CC;          /* 0x10 */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } Mtx_8018E8A0_801869CC; /* 0x20 */
typedef struct { s16 f[0x86]; } Cnt_8018E8A0_801869CC;
typedef struct {
    SVec8_8018E8A0_801869CC v[4];   /* 0x00 */
    u32            c[4];   /* 0x20 */
    s32            code;   /* 0x30 */
    s32            pad;    /* 0x34 */
} Prim_8018E8A0_801869CC;           /* 0x38 */

void func_801869CC(void *a0)
{

    extern u32 D_801C5BB4[];
    extern u8 D_801C5C18[];
    Vec16_8018E8A0_801869CC  mv;      /* sp+0x10 */
    Prim_8018E8A0_801869CC   prim;    /* sp+0x20 */
    Mtx_8018E8A0_801869CC    mtx;     /* sp+0x58 */
    SVec8_8018E8A0_801869CC  rot;     /* sp+0x78 */
    s32             flag;    /* sp+0x80 */
    s32            *p;
    s32            *q;
    s32            *zb;
    SVec8_8018E8A0_801869CC *src;
    SVec8_8018E8A0_801869CC *dst;
    register s32 d __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus7)
    s32 i, j, k, base, ang, t;
    u32 col;

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x40;
    func_8012B414((s32)a0);

    mv.vz  = -0x40000;
    rot.vz = 0;
    col = D_801C5BB4[(*(u16 *)((s32)a0 + 0x10A))++ & 7];
    prim.code = 0x50000000;
    *(u32 *)((s32)&prim + 0x20) = col;
    *(u32 *)((s32)&prim + 0x24) = col;
    *(u32 *)((s32)&prim + 0x28) = col;
    *(u32 *)((s32)&prim + 0x2C) = col;

    p = (s32 *)((s32)a0 + 0xCC);
    for (i = 0, k = 0; i < ((Cnt_8018E8A0_801869CC *)a0)->f[0x84]; i++, k++, p += 3) {
        zb = (s32 *)((s32)a0 + 0xD4);
        { register s32 c1 __asm__("$2"); register s32 c2 __asm__("$3");  // !FAKE: pin $2 — NEEDED DIFFERS; pin $3 — NEEDED DIFFERS (P36 rung B tus7)
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

        src = (SVec8_8018E8A0_801869CC *)(D_801C5C18 +
              ((s32)(s16)*(u16 *)((s32)a0 + 0x70) / 2) * 0x20);
        dst = prim.v;

        gte_SetRotMatrix(&mtx);
        gte_SetTransMatrix(&mtx);

        for (j = 0; j < 4; j++, src++, dst++) {
            RotTransSV(src, dst, &flag);
        }
        func_80017758(&prim, (void *)(*(s32 *)((s32)a0 + 0x20) + 0x34));
    }

    *(s32 *)((s32)a0 + 0x1C) += 1;
    if ((*(s32 *)((s32)a0 + 0x1C) & 3) == 0) {
        if (((Cnt_8018E8A0_801869CC *)a0)->f[0x84] < 5) {
            ((Cnt_8018E8A0_801869CC *)a0)->f[0x84] = ((Cnt_8018E8A0_801869CC *)a0)->f[0x84] + 1;
        }
    }
}



extern void (*D_801C5C58[])(void);

void func_80186D18(void *a0) {
    D_801C5C58[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);

void func_80186D54(void *a0)
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



extern void (*D_801C9794[])(void);

void func_80186DD4(void *a0) {
    D_801C9794[*(u16 *)((s32)a0 + 0x2)]();
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
extern void func_801874BC(s32 param_1);

void func_80186E10(void *a0) {

    extern s32 D_801C94EC[];
    extern u8 D_801C9484[];
    extern u8 D_8018C90C[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801C9484);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801C94EC[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_801874BC);
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
        func_8012A828((s32)a0, D_8018C90C);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_80186EE4(void *a0) {
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


void func_80186F0C(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80186F14(void *a0) {

    extern s32 D_801C96D0;
    extern s32 D_801C96BC;
    extern s32 D_801C96B8;
    extern s32 D_801C9750;
    extern s32 D_801C96E4;
    extern s32 D_801C95B0[];
    extern s32 D_801C9634[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801C96D0 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801C96B8 = 0;
                D_801C96BC = D_801C9634[v0];
            } else {
                D_801C96BC = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801C9634[v0], 1);
                D_801C96B8 = 2;
            }
        } else {
            D_801C96D0 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801C96B8 = 0;
            D_801C96BC = D_801C95B0[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801C96E4);
    } else {
        p = &D_801C9750;
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
extern s32 func_80187264(void);

void func_80187060(void *arg0) {

    extern s32 D_801C94EC[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801C94EC[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801C94EC[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80187264() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    void func_80187180(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32))func_8012C218)(*(s32 *)((char *)arg0 + 0xcc));
    }


void func_801871AC(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_801871BC(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_801871CC(void *a0) {

    extern s32 D_801C94EC[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801C94EC[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_8018720C(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
    s32 func_80187240(void) {
        return ((u32)((s32 (*)(void))func_80174764)() == 1);
    }




extern s32 func_80029178(s32 arg);

s32 func_80187264(void) {

    extern s32 D_801C94EC[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801C94EC[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801C97BC[])(void);

void func_801872C8(void *a0) {
    D_801C97BC[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80187304(void *a0) {

    extern u8 D_801C94B8[];
    extern u8 D_801C9E7C[];
    extern u8 D_801C9C5C[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801C94B8) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801C9E7C);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801C9C5C);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018738C(void *a0) {

    extern u8 D_801C9C6C[];
    extern u8 D_801C9D74[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801C9C6C);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801C9D74);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_8018744C — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801C9E7C, else
 * D_801C9C5C), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801C9E7C / D_801C9C5C)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_8018744C(void *a0) {

    extern u8 D_801C9E7C[];
    extern u8 D_801C9C5C[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801C9E7C);
        } else {
            func_8012A828((s32)a0, D_801C9C5C);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801C97AC[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

s32 aF8018A224() __asm__("func_801874BC");

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

    RotTransSV(D_801C97AC, sv0, &flag);
    RotTransSV(D_801C97AC + 8, sv1, &flag);

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


extern s32 D_801CA170[];
extern s32 func_8012C044(s32 a0);
extern void func_80188A2C(void*);

void func_801875B4(s32 a0) {
    s32 *s0 = (s32 *)a0;
    u32 v0;
    u32 (*func_ptr)(void);

    v0 = *(u16 *)((u8 *)s0 + 2);
    v0 = v0 * 4;
    func_ptr = (u32 (*)(void))D_801CA170[v0 / 4];
    func_ptr();

    v0 = *(u16 *)s0;
    if (v0 == 0) {
        return;
    }

    v0 = func_8012C044((s32)s0);
    if (v0 != 1) {
        return;
    }
    ((void (*)(s32))func_80188A2C)((s32)s0);
}


#include "common.h"

extern s32 func_8012E504(s32 a0, s32 a1);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8018893C(s32 arg0);
extern void func_8012B23C(s32 a0);

extern u16 D_801274E4[];
extern u8 D_801CA040[];
extern u8 D_801CA0F8[];
extern u8 D_8018C90C[];

void func_80187628(s32 a0) {
    s32 s0;
    s32 v0;

    if (func_8012E504(a0, 0x6D) != 0) {
        D_801274E4[0] |= 0x1;
        return;
    }
    s0 = a0;

    if (func_8012C354(s0, (s32)D_801CA040) == 0) {
        return;
    }

    *(s8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)D_801CA0F8;
    *(s32 *)(s0 + 0xB4) = -0x48D;

    v0 = *(s32 *)(s0 + 0xC4);
    *(s16 *)(s0 + 0xDC) = 1;
    *(s32 *)(s0 + 0xC4) = v0 | 0x2;

    func_80143970(s0);
    func_8012A828(s0, D_8018C90C);
    func_8018893C(s0);
    func_8012B23C(s0);
}


extern s32 D_801C9EEC[];
extern s32 D_801CAE68;
extern s32 D_801F7730;
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_801888A8(s32 a0, s32 a1);

void func_801876E4(s32 a0) {
    *(s16 *)(a0 + 2) = 2;
    func_80132288(&D_801F7730, D_801C9EEC, D_801CAE68);
    *(s32 *)(a0 + 0x1C) = (rand() % 31) + 30;
    func_801888A8(a0, 1);
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8013240C(s32 a0);
extern s32 D_801F7730;

void func_80187778(s32 a0) {
    if (func_8012BCCC(a0) < 0x4001) {
        *(s16 *)(a0 + 2) = 7;
        return;
    }
    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 2) = 5;
    }
    func_8013240C((s32)&D_801F7730);
}


#include "common.h"

extern void func_801888A8(s32, s32);
extern s32 rand(void);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern s32 func_80188C18(void *a0);

extern s32 D_801F7730;
extern s32 D_801CAE68;
extern s32 D_801C9EEC[];

void func_801877D8(void *a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801C9F04[];
    u8 *s0 = (u8 *)a0;
    s32 v1;

    *(s16 *)(s0 + 0x2) = 4;
    ((void (*)(void *, s32))func_801888A8)(s0, 1);

    do { v1 = (rand() & 1) ? 1 : -1; } while (0);

    *(s16 *)(s0 + 0xE0) = v1;
    if (*(s16 *)(s0 + 0xEA) != 0) {
        *(s32 *)(s0 + 0x1C) = (rand() % 31) + 30;
        func_80132288(&D_801F7730, D_801C9EEC, D_801CAE68);
    } else {
        *(s32 *)(s0 + 0x1C) = (rand() % 31) + 15;
        func_80132288(&D_801F7730, D_801C9F04, D_801CAE68);
        if (func_80188C18(s0) == 1) {
            *(s16 *)(s0 + 0xE8) = 0;
        } else {
            *(s16 *)(s0 + 0xE8) = 1;
        }
    }
}


extern s32  func_801887B0(s32 a0);
extern s32 D_801F7730;
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8013240C(s32 a0);

void func_80187914(s32 arg0) {
    s32 v0;
    s32 v1;

    v0 = *(s16 *)(arg0 + 0xE0);
    v1 = *(s32 *)(arg0 + 0x20);
    *(u16 *)(v1 + 0x12) += v0 * 34;

    if (*(s16 *)(arg0 + 0xEA) == 0) {
        func_8012B178(arg0, 0xFFFE0000);
        if (func_801887B0(arg0) == -1) {
            return;
        }
    }
    if (func_8012BCCC(arg0) < 0x4001) {
        *(s16 *)(arg0 + 2) = 7;
        return;
    }
    if (func_8012BEE8(arg0) != 0) {
        *(s16 *)(arg0 + 2) = 5;
    }
    func_8013240C((s32)&D_801F7730);
}


void func_801879C4(void *a0) {
    extern s32 D_801F7730;
    extern s32 D_801C9F04[];
    extern s32 D_801CAE68;
    u8 *s0 = (u8 *)a0;
    s32 v0;
    s32 *ptr;

    *(s16 *)(s0 + 0x2) = 6;
    do { func_8012B23C(s0); } while (0);
    func_8012B178(s0, (s32)0xFFFE0000);
    v0 = rand();
    *(s32 *)(s0 + 0x1C) = v0 % 61 + 90;
    func_801888A8(s0, 1);
    ptr = &D_801F7730;
    *(s16 *)(s0 + 0xE4) = 0;
    if (*ptr != (s32)D_801C9F04) {
        func_80132288(ptr, D_801C9F04, D_801CAE68);
    }
    if (func_80188C18(s0) == 1) {
        *(s16 *)(s0 + 0xE8) = 0;
    } else {
        *(s16 *)(s0 + 0xE8) = 1;
    }
}


typedef struct { u8 d[4]; } Blk4_8017CE90_8017F32C_80184FF0_80187A9C;


extern s32  func_80047D3C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_8013240C(s32 a0);
extern s32  func_801887B0(s32 a0);
extern void func_801888A8(s32 a0, s32 a1);
extern void func_8018893C(s32 arg0);
extern s32  func_80188A94(s32 a0);
extern void func_80188AF4(s32, s32);

void func_80187A9C(s32 obj) {

    extern u8 D_80078EAE;
    extern s32 D_801C9F04;
    extern s32 D_801C9F24;
    extern s32 D_801CA0E4;   /* VECTOR.z at 0x801C9314 + 8 */
    s32 d;
    s32 p;
    s32 r;

    d = func_8012BCCC(obj);
    if (d <= 0x4000) {
        *(s16 *)(obj + 0x2) = 7;
        return;
    }
    if (D_80078EAE == 0 && d <= 0x8000 && *(s16 *)(obj + 0xE4) != 0) {
        s32 *vz = &D_801CA0E4;

        *vz = -(func_80047D3C(func_8012BCCC(obj)) << 16);
        if (((s32 (*)(s32, s32))func_80188AF4)(obj, (s32)((u8 *)vz - 8)) & 0x2000) {
            *(s16 *)(obj + 0x2) = 9;
            return;
        }
    }
    if (!func_80188A94(obj) || !func_8012BDBC(obj, 0x400)) {
        if (*(s16 *)(obj + 0xE4) != 0) {
            func_8012B178(obj, 0xFFFE0000);
            func_801888A8(obj, 1);
            func_80132288((int *)&D_801F7730, (int *)&D_801C9F04, D_801CAE68);
            *(s16 *)(obj + 0xE4) = 0;
        }
        if (func_8012BEE8(obj)) {
            func_8018893C(obj);
            return;
        }
    } else {
        r = func_8012B8E4(obj, 4);
        p = *(s32 *)(obj + 0x20);
        *(u16 *)(p + 0x12) += r;
        func_8012B178(obj, 0xFFF80000);
        if (*(s16 *)(obj + 0xE4) == 0) {
            func_801888A8(obj, 2);
            func_80132288((int *)&D_801F7730, (int *)&D_801C9F24, D_801CAE68);
            *(s16 *)(obj + 0xE4) = 1;
        }
    }
    r = func_801887B0(obj);
    if (r == 0) {
        if (*(s16 *)(obj + 0xE4) == 0 || *(s16 *)(obj + 0xEA) == 2) {
            *(s16 *)(obj + 0x2) = 3;
        }
    } else if (r == -1) {
        return;
    }
    func_8013240C((s32)&D_801F7730);
}


void func_80187C94(s32 a0) {
    extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
    extern void func_801888A8(s32 a0, s32 a1);
    extern s32 D_801F7730;
    extern s32 D_801CAE68;
    extern s32 D_801C9F44[];
    s32 s0 = a0;

    *(s16 *)(s0 + 0x2) = 8;
    func_80132288(&D_801F7730, D_801C9F44, D_801CAE68);
    *(s32 *)(s0 + 0x1C) = 0x28;
    func_801888A8(s0, 2);
    *(s16 *)(s0 + 0xDE) = 0;
    *(s16 *)(s0 + 0xE6) = 0;
}


#include "common.h"

extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_8018893C(s32 arg0);
extern void func_8013240C(s32 a0);

extern s32 D_801CA0E8[];
extern s32 D_801F7730;

void func_80187CFC(s32 a0) {
    s32 v0;
    s32 v1;

    v0 = func_8012B8E4(a0, 3);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v0;

    if (*(s32 *)(a0 + 0x1C) == 0x28) {
        func_8002D4C8(0x7F, 0);
    }
    if (*(s32 *)(a0 + 0x1C) == 5) {
        func_8002D4C8(0x524, 0);
    }
    if (*(s32 *)(a0 + 0x1C) < 0xB) {
        if (*(s16 *)(a0 + 0xDE) == 0) {
            func_8012D5E4(a0, (s32)D_801CA0E8, (s32)D_801CA0E8 + 8, 0x15);
            *(u16 *)(a0 + 0xDE) ^= 1;
        }
    }
    if (func_8012BEE8(a0) != 0) {
        v1 = func_8012BCCC(a0);
        if (v1 > 0x30000) {
            func_8018893C(a0);
            return;
        }
        if (v1 >= 0x4001) {
            *(s16 *)(a0 + 0x2) = 5;
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x28;
        *(u16 *)(a0 + 0xDE) = 0;
    }
    func_8013240C((s32)&D_801F7730);
}


#include "common.h"

extern s32 D_801F7730;
extern s32 D_801CAE68;
extern s32 D_801C9F6C;
extern s32 D_801CA0E4;
extern s32 D_801CA1A4;

extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_801888A8(s32 a0, s32 a1);
extern s32 func_8012B864(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);

void func_80187E24(s32 a0) {
    s32 s0 = a0;
    s16 ret864;
    s32 *tbl;

    *(s16 *)(s0 + 0x2) = 0xA;
    func_80132288((int *)&D_801F7730, (int *)&D_801C9F6C, D_801CAE68);
    func_801888A8(s0, 2);
    *(s16 *)(s0 + 0xDE) = 0;
    ret864 = func_8012B864(s0);
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = ret864;
    func_8012B2CC(s0);
    tbl = &D_801CA1A4;
    *tbl = D_801CA0E4 / 30;
    func_8012B23C(s0);
    func_8012B14C(s0, (s32)tbl - 8);
    *(s32 *)(s0 + 0x1C) = 0;
    *(s16 *)(s0 + 0x34) = 0;
}


#include "common.h"

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8013240C(s32 a0);

extern s32 D_801CA0E8[];
extern s32 D_801F7730;

void func_80187EF0(s32 param_1) {
    s32 ret;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        if (*(s32 *)(param_1 + 0x1C) < 0xF) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) += 0x44;
        }

        if ((u32)(*(s32 *)(param_1 + 0x1C) - 0x15) < 0xA) {
            if (*(s16 *)(param_1 + 0xDE) == 0) {
                func_8012D5E4(param_1, (s32)((u8 *)D_801CA0E8), (s32)&((u8 *)D_801CA0E8)[8], 0x1F);
                *(u16 *)(param_1 + 0xDE) ^= 1;
            }
        }

        ret = func_8012CBCC(param_1);
        if ((ret & 0xFF) == 2) {
            ((void (*)(s32, s32))func_80131E00)(param_1, 0x12);
            return;
        } else {
            if (ret & 0x2000) {
                *(s32 *)(param_1 + 0x1C) = 0xF;
                *(u16 *)(param_1 + 0x34) += 1;
            }

            *(s32 *)(param_1 + 0x1C) += 1;
            if (*(s32 *)(param_1 + 0x1C) >= 0x28) {
                ((void (*)(s32, s32))func_80131E00)(param_1, 0xD);
            }
        }
    } else {
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x2) = 1;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        }
    }

    ((void (*)(s32 *))func_8013240C)(&D_801F7730);
}


extern M2C_UNK D_801C9FFC;
extern M2C_UNK D_801CA030;
void func_8018803C(s32 a0) {
    s32 s0 = a0;
    func_80188978(a0, (s32)&D_801C9FFC, 0);
    func_8012A828(s0, (void*)&D_801CA030);
}


extern void func_8013240C(s32);
void func_80188080(void) {

    extern s32 D_801F7730;
    ((s32 (*)(s32 *))func_8013240C)(&D_801F7730);
}


extern void func_80188978(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_801C9FFC;
extern u8 D_801CA1A8[];
extern u8 D_801CA1B4[];
extern M2C_UNK D_801CA030;

void func_801880A8(s32 param_1) {
    s32 s0 = param_1;

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    func_80188978(s0, (s32)&D_801C9FFC, 0);

    if (*(u16 *)(s0 + 0x5E) == 9 || *(u16 *)(s0 + 0x5E) == 0x1C) {
        func_8012B14C(s0, (s32)D_801CA1A8);
    } else {
        func_8012B14C(s0, (s32)D_801CA1B4);
    }

    func_8012A828(s0, (void *)((u8 *)&D_801CA030));
}


typedef struct { s16 vx, vy, vz, pad; } SVec8_8018E8A0_80184FF0_80188134;          /* 0x08 */
typedef struct { u8 d[4]; } Blk4_8017CE90_8017F32C_80184FF0_80188134;
    typedef struct { s16 vx; u16 vy; s16 vz, pad; } SVec_8017F67C_80184FF0_80188134;

/* ov_SC03_029 :: func_80188134 (0x80186758, 183 ins)
 *
 * Actor state-machine tick. Shape is the wave-U twin ov_SC01_077:func_801824D0
 * (matched, 181 ins) crossed with the same-binary sibling
 * src/ov_SC03_029/ov_SC03_029_jr_8012ACE0.c::func_80131340 (matched) for the
 * *15/16 signed-div fixup and the func_8012CC64/func_80143B6C call-site casts.
 *
 * Object field map (offsets off the s32 actor pointer):
 *   0x10 s32 velocity X-ish     0x14 s32 (saved/restored around state 1)
 *   0x18 s32 velocity Z-ish     0x1C s32 frame counter
 *   0x20 s32 -> gfx block { ... 0x10 u16 alpha/flag, 0x12 s16 ... }
 *   0xC1 u8 (cleared on hand-off)   0xC2 u8 state   0xC3 u8 bitflags
 */

extern void func_8012DBD0(s32, s32, s32, s32);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8013240C(s32 a0);
extern void func_8018876C(s32 a0);


void func_80188134(s32 a0)
{

    extern s32 D_801CA0A4;
    /* 8 bytes of frame that the body never references: a declared aggregate local
     * gets assign_stack_local'd (var_size 8) and emits zero instructions (§193-I). */
    struct V8_80188134 {
        u16 vx, vy, vz, pad;
    };
    struct V8_80188134 sp10;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0;
    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        ((s32 (*)(s32, s32, s32, s32))func_8012DBD0)(a0, 0x50, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            goto L9E8;
        }
        var_s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801CA0A4);
        if (var_s1 & 0x2000) {
            *(u8 *)(a0 + 0xC2) = 1;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        }
        break;

    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            goto L9E8;
        }
        var_s2 = *(s32 *)(a0 + 0x14);
        var_s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801CA0A4);
        if (var_s1 & 0x2000) {
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = var_s2;
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        } else if (var_s1 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 2:
        /* *15/16 with the signed-division +0xF fixup (never >>4) */
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            var_s1 = ((s32 (*)(s32))func_8012CBA4)(a0);
            /* explicit goto pair: the target emits `bnez -> join ; j L9E8` */
            if (var_s1 & 0x2000) {
                goto L9AC;
            }
            goto L9E8;
        }
        var_s1 = ((s32 (*)(s32))func_8012CBF4)(a0);
        if (var_s1 & 0x2000) {
            *(u8 *)(a0 + 0xC3) |= 1;
        } else if (var_s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
    L9AC:
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(var_s1 & 0x2000)) {
            goto L9E8;
        }
        *(u8 *)(a0 + 0xC1) = 0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        func_8018876C(a0);
        return;
    }
    goto L9F0;

L9E8:
    func_80131E00(a0, 0xD);
L9F0:
    ((void (*)(s32))func_8013240C)((s32)&D_801F7730);
    if ((var_s1 & 0xFF) == 2) {
        func_80131E00(a0, 0x12);
    }
}


#include "common.h"

/* Local standalone-compile clone of engine_types.h's Mtx8_8017DE10_8017E710
 * (match_one's isolated compile only has -Iinclude, can't resolve
 * ../shared/engine_types.h; the host TU already includes it via engine_core.h).
 * Same-shape clone -> byte-neutral; the gate's strip_provided_typedefs drops it. */


void func_80188410(s32 a0)
{
    extern void func_80188978(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012B2CC(s32 a0);
    extern s32 func_8012B864(s32 a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);
    extern Mtx8_8017DE10_8017E710 D_800AE620;
    extern M2C_UNK D_801C9FFC;
    extern M2C_UNK D_801CA030;
    extern u8 D_801CA074[];
    extern u8 D_801CA084[];
    extern u8 D_801CA094[];

    Mtx8_8017DE10_8017E710 m;
    u8 *p;

    func_80188978(a0, (s32)&D_801C9FFC, 0);
    func_8012A828(a0, (void *)&D_801CA030);
    func_8012B2CC(a0);
    m = D_800AE620;
    RotMatrixY((func_8012B864(a0) + 0x800) & 0xFFF, &m);
    /* LOAD-BEARING: every case label 1..0x32 must be WRITTEN OUT. gcc-2.7.2's
     * table-vs-compare-chain choice keys on DISTINCT LABEL COUNT over the
     * value range, not on a `default:` arm: with only the 4 distinct bodies
     * spelled (case 8 / 5,0x1d,0x20 / default) it emits a li/beq chain and no
     * jtbl at all. With ~50 labels it emits addiu $v1,$v0,-1 ; sltiu
     * $v0,$v1,0x32 ; sll 2 ; jtbl_801F5F74 (minval=1, 50 entries) -- the
     * target's exact dispatch. Do NOT "simplify" to a default-only switch. */
    switch (*(u16 *)(a0 + 0x5e)) {
    case 8:
        p = D_801CA084;
        break;
    case 5:
    case 0x1d:
    case 0x20:
        p = D_801CA094;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 30:
    case 31:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    default:
        p = D_801CA074;
        break;
    }
    func_800484EC((s32)&m, (s32)p, a0 + 0x10);
    *(u16 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x1c) = 0;
}


#include "common.h"

extern void func_8012CBA4(s32 a0);
extern void func_8012CC64(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8018876C(s32 a0);
extern void func_8013240C(s32 a0);

void func_80188528(s32 a0) {
    extern s32 D_801CA0A4;
    extern s32 D_801F7730;

    s32 s0;
    s32 s1;
    s32 v0;
    s32 v1;
    s32 t;
    s32 p;
    s32 q;

    s0 = a0;
    v1 = *(u16 *)(s0 + 0x34);
    s1 = 0;

    switch (v1) {
    case 0:
        t = *(s32 *)(s0 + 0x1C) + 1;
        *(s32 *)(s0 + 0x1C) = t;
        if (t >= 0x29) {
            goto timeout;
        }
        q = *(s32 *)(s0 + 0x20);
        *(u16 *)(q + 0x10) -= 0x100;
        s1 = ((s32 (*)(s32, s32))func_8012CC64)(s0, (s32)&D_801CA0A4);
        if (s1 & 0x2000) {
            *(s32 *)(s0 + 0x1C) = 0xF;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
        }
        break;

    case 1:
        s1 = ((s32 (*)(s32))func_8012CBA4)(s0);
        if (!(s1 & 0x2000)) {
            *(u16 *)(s0 + 0x34) = 2;
            *(s32 *)(s0 + 0x1C) = 0;
            func_8012B23C(s0);
            break;
        }
        v0 = func_8012BEE8(s0);
        goto merge2;

    case 2:
        t = *(s32 *)(s0 + 0x1C) + 1;
        *(s32 *)(s0 + 0x1C) = t;
        if (t >= 0x29) {
timeout:
            func_80131E00(s0, 0xD);
            break;
        }
        s1 = ((s32 (*)(s32))func_8012CBCC)(s0);
        v0 = s1 & 0x2000;
merge2:
        if (v0) {
            p = *(s32 *)(s0 + 0x20);
            *(u8 *)(s0 + 0xC1) = 0;
            *(u16 *)(p + 0x10) = 0;
            *(s16 *)(s0 + 0x5E) = 0;
            func_8018876C(s0);
        }
        break;
    }

    ((void (*)(void *))func_8013240C)(&D_801F7730);
    if ((s1 & 0xFF) == 2) {
        func_80131E00(s0, 0x12);
    }
}


extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_801888A8(s32 a0, s32 a1);
extern s32 D_801F7730;
extern s32 D_801CAE68;
extern s32 D_801C9FD4[];

void func_801886C0(s32 a0) {
    func_80132288(&D_801F7730, D_801C9FD4, D_801CAE68);
    func_801888A8(a0, 1);
}


extern void func_8013240C(s32 a0);
extern s32 D_801F7730;

void func_80188710(void) {
    ((void (*)(void *))func_8013240C)(&D_801F7730);
}


















extern void func_80188978(s32 arg0, s32 arg1, s32 arg2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern M2C_UNK D_801C9FFC;
void func_80188738(void)
{
  int new_var;
  func_80188978(new_var, (s32) (&D_801C9FFC), 0);
  new_var = 0xA74;
  func_8002D4C8(0xA74, 0);
 dummy_label_648936: ;
}

extern void func_8012A828(s32 a0, void *a1);

void func_8018876C(s32 a0) {
    extern u8 D_8018C90C[];
    *(s16 *)(a0 + 0x2) = 1;
    func_8012A828(a0, (void *)D_8018C90C);
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    *(s16 *)(a0 + 0xEA) = 0;
}


#include "common.h"

extern void func_8012ADE4(u8 *a0);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);

s32 func_801887B0(s32 a0) {
    s32 s0;
    s32 flags;
    s32 t;

    s0 = a0;
    if (*(s16 *)(s0 + 0xE8) == 0) {
        flags = ((s32 (*)(s32))func_8012CBA4)(a0);
        if ((flags & 0xFF) == 2) {
            ((void (*)(s32, s32))func_80131E00)(s0, 0x12);
            return -1;
        } else if (!(flags & 0x2000)) {
            func_8012ADE4((u8 *)s0);
            *(s16 *)(s0 + 0xEA) = 2;
        } else if (flags & 0x4000) {
            func_8012ADE4((u8 *)s0);
            *(s16 *)(s0 + 0xEA) = 1;
        } else if (flags & 0x8000) {
            *(s16 *)(s0 + 0xEA) = 1;
            return 0;
        } else {
            *(s16 *)(s0 + 0xEA) = 0;
            return 1;
        }
        return 0;
    } else {
        if (!(func_8012CBCC(s0) & 0x2000)) {
            t = *(u16 *)(s0 + 0xE8) + 1;
            *(s16 *)(s0 + 0xE8) = t;
            if ((s16)t >= 0x5A) {
                return -1;
            }
        }
        *(s16 *)(s0 + 0xE8) = 0;
        return 1;
    }
}


extern void func_800183E0(s32 a0);
extern s32 D_801CB010;
extern s32 D_801CB1E0;

s32 func_801888A8_impl(s32 a0, s32 a1) __asm__("func_801888A8");
s32 func_801888A8_impl(s32 a0, s32 a1) {
    if (a1 & 1) {
        if (*(u16 *)(a0 + 0xDC) & 2) {
            func_800183E0((s32)&D_801CB010);
            *(u16 *)(a0 + 0xDC) = a1;
            return 0;
        }
    } else {
        if (a1 & 2) {
            if (*(u16 *)(a0 + 0xDC) & 1) {
                func_800183E0((s32)&D_801CB1E0);
                *(u16 *)(a0 + 0xDC) = a1;
                return 0;
            }
        }
    }
    return 1;
}



extern s32 rand(void);
    void func_8018893C(s32 arg0) {
        if ((rand() & 1) != 0) {
            *(s16*)(arg0 + 0x2) = 0x1;
        } else {
            *(s16*)(arg0 + 0x2) = 0x3;
        }
    }


extern s32 D_801CAE68;
extern s32 D_801CB010;
extern s32 D_801F7730;
extern void func_800183E0(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);

void func_80188978(s32 a0, s32 a1, s32 a2) {
    s32 s1 = a0;
    s32 s0;
    s32 s2 = a2;
    s32 p;

    s0 = a1;

    func_8012B23C(s1);
    func_80132288(&D_801F7730, (s32 *)s0, D_801CAE68);
    s0 = 1;
    if (*(u16 *)(s1 + 0xDC) & 2) {
        func_800183E0((s32)&D_801CB010);
        *(u16 *)(s1 + 0xDC) = s0;
    }
    *(u16 *)(s1 + 0x5C) &= 0xFFFE;
    *(s32 *)(s1 + 0x1C) = s2;
    *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = (*(u16 *)(s1 + 0x62) + 0x800) & 0xFFF;
    p = *(s32 *)(s1 + 0x20);
    *(s16 *)(p + 0x14) = 0;
    *(s16 *)(p + 0x10) = 0;
}


extern void func_8012C218(void *arg0);

void func_80188A2C(void *arg0) {
    int iVar1;
    if ((*(s16 *)((char *)arg0 + 0x70) & 0x8000) == 0) {
        iVar1 = *(int *)((char *)arg0 + 0x68);
        if ((iVar1 != 0) && ((*(s16 *)((char *)arg0 + 0x72) & 0x8000) != 0)) {
            *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7FFF;
        }
    }
    func_8012C218(arg0);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_80188A94(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h, where the
 * real TU's Blk20 { s32 w[8]; } and Vec32 { s32 vx, vy, vz, pad; } live. Local copies here;
 * integrator may drop these and reuse the TU's own (engine_types.h:472, :1098). */
typedef struct { s32 w[8]; } Blk20_80188AF4;
typedef struct { s32 vx, vy, vz, pad; } Vec32_80188AF4;

void func_80188AF4(s32 a0, s32 a1) {
    extern s32  func_8012B864(s32 a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);
    extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern Mtx8_8017DE10_8017E710 D_800AE620;

    u32 pos[3];
    Vec32_80188AF4 out;
    u8 rotIn[8];
    u8 rotOut[8];
    Blk20_80188AF4 m;

    m = (*(Blk20_80188AF4 *)&D_800AE620);
    RotMatrixY(func_8012B864(a0), &m);
    func_800484EC((s32)&m, a1, (s32)&out);

    pos[0] = *(s32 *)(a0 + 0x4) + out.vx;
    pos[1] = *(s32 *)(a0 + 0x8) + out.vy;
    pos[2] = *(s32 *)(a0 + 0xC) + out.vz;

    {
        u16 rix;
        u16 roy;
        u16 roz;
        u16 riz;

        rix = *(u16 *)(a0 + 0x3A);
        roy = *((u16 *)&pos[1] + 1);
        roz = *((u16 *)&pos[2] + 1);
        *(u16 *)(rotIn + 0) = rix;
        *(u16 *)(rotIn + 2) = *(u16 *)(a0 + 0x3E);
        riz = *(u16 *)(a0 + 0x42);
        *(u16 *)(rotOut + 0) = *((u16 *)&pos[0] + 1);
        *(u16 *)(rotOut + 2) = roy;
        *(u16 *)(rotOut + 4) = roz;
        *(u16 *)(rotIn + 4) = riz;
    }

    func_8012CEB0((s32)&rotIn[0], (s32)&rotOut[0], 0);
}


extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_80188C18(void *a0)
{
    short in[4];
    short out[4];
    s32 pa, pb;

    in[0] = *(u16 *)((s32)a0 + 0x6);
    in[1] = *(u16 *)((s32)a0 + 0xA);
    in[2] = *(u16 *)((s32)a0 + 0xE);
    pa = (s32)in;
    pb = (s32)out;
    __builtin_memcpy((void *)pb, (void *)pa, 8);
    out[1] += 8;
    if (func_80133784(1, in, pb) & 0x2000) {
        return 1;
    }
    return 0;
}


extern s32 func_8012C044(s32 a0);
extern u32 D_801D2B4C[];
extern void func_8018A05C(s32 a0);

void func_80188C90(s32 a0) {
    s32 *s0 = (s32 *)a0;
    u32 v0;
    u32 v1;
    u32 (*func_ptr)(void);

    v0 = *(u16 *)((u8 *)s0 + 2);
    v0 = v0 * 4;
    func_ptr = (u32 (*)(void))D_801D2B4C[v0 / 4];
    func_ptr();

    v0 = *(u16 *)s0;
    if (v0 == 0) {
        return;
    }

    v0 = *(u32 *)((u8 *)s0 + 0x20);
    v1 = *(u16 *)((u8 *)v0 + 0x2C);
    v1 = v1 | 0x10;
    *(u16 *)((u8 *)v0 + 0x2C) = v1;

    v0 = func_8012C044(a0);
    v1 = 1;
    if (v0 != v1) {
        return;
    }
    *(u16 *)((u8 *)s0 + 0x102) = (v0 = 1);
    func_8018A05C(a0);
}


extern s32 D_801D2A40;
extern s32 D_801D2A74;
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_80188D1C(s32 param_1) {
    if (func_8012C354(param_1, (s32)&D_801D2A40) != 0) {
        *(u8 *)(param_1 + 0xC0) = 1;
        *(s32 *)(param_1 + 0xBC) = (s32)&D_801D2A74;
        *(s32 *)(param_1 + 0xB4) = 0xFFFBDFD9;
        *(s32 *)(param_1 + 0xDC) = 0;
        *(s16 *)(param_1 + 0x100) = 0x1000;
        *(s32 *)(param_1 + 0xC4) |= 1;
        func_80143970(param_1);
        *(s16 *)(param_1 + 2) = 1;
        func_8012B2CC(param_1);
    }
}




extern void func_8012A828(s32, void*);
    extern short D_801D76C0;
    void func_80188DA0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D76C0);
    }



extern s32 func_8012BCCC(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);

// @class: straight-derive
// @unstuck(P36): none — MATCH (52 ins) on iteration 1, confirmed by rtu_match.
//
// Two things that could have been mis-read off the target asm:
//
// 1. RELOAD_CSE DELETES A REDUNDANT ARG MOVE — do not read "no arg setup" as
//    "zero-arg call". `jal func_8012BCCC` at 0x80184C7C has a bare `nop` delay
//    slot and NO `addu $a0,$s0,$zero` before it, which looks like `f()`. It is
//    `f(a0)`: the incoming param is still live in $a0 in that fall-through
//    block, so gcc-2.7.2's reload_cse_regs (reload1.c) deletes the redundant
//    `move $a0,$s0`. The SAME move survives at .L80184CD0 (0x80184CD0) because
//    reload_cse's value tracking resets at a CODE_LABEL. So: an arg move that
//    is present on the labelled arm and absent on the fall-through arm is ONE
//    source-level call shape, not two.
//
// 2. `lui $v1,1 / slt $v1,$v1,$v0` is `ret <= 0x10000`, not `ret < 0x10001`.
//    gcc lowers `a <= C` to `!(C < a)` and puts the CONSTANT in the first slt
//    operand; writing `< 0x10001` would have materialised 0x10001 instead.
//
// Statement order in the then-arm is the Ghidra order (0x1C store, then the
// 0x34 increment): memrefs_conflict_p disambiguates `+0x1C`/4 from `+0x34`/2
// off the same base, so sched2 legally hoists the `lhu 0x34` above the `sw`
// to cover its load delay — which is exactly the target's interleave.
void func_80188DD0(s32 a0) {

    extern u8 D_801D477C;
    extern u8 D_801D78A8[];
    s32 v;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BCCC(a0) <= 0x10000) {
            func_8001C924(*(s32 *)(a0 + 0x20), (void *)&D_801D477C);
            func_8012A828(a0, (void *)&(*(u8 *)D_801D78A8));
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(u16 *)(a0 + 0x34) += 1;
        }
    } else {
        v = func_8012B8E4(a0, 0xA);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v;
        if (func_8012BEE8(a0) != 0 || v == 0) {
            *(s16 *)(a0 + 0x2) = 5;
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern s32 rand(void);
extern u8 D_801D78A8[];

void func_80188EA0(s32 a0) {
    s32 r;

    *(s16 *)(a0 + 0x2) = 4;
    func_8012A828(a0, D_801D78A8);
    r = rand();
    *(s16 *)(a0 + 0x52) = 0;
    *(s32 *)(a0 + 0x1C) = (r % 17) + 0x28;
}


extern s32 func_8012BEE8(s32 arg);
    void func_80188F14(void *a0) {
        if (func_8012BEE8((s32)a0)) {
            *(s16 *)((s32)a0 + 0x2) = 0x5;
        }
    }


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801D7998;
extern u8 D_80078EAE;

void func_80188F48(void *a0) {
    s32 s0 = (s32)a0;
    s32 v0;

    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE0000);
    func_8012A828(s0, (void *)&D_801D7998);
    *(s32 *)(s0 + 0x1C) = 0x96;
    v0 = D_80078EAE;
    if (v0 == 0) {
        v0 = 7;
    } else {
        v0 = 6;
    }
    *(s16 *)(s0 + 2) = (s16)v0;
}


void func_80188FB0(s32 a0) {
    s32 s0 = a0;
    if (func_8012BD3C(s0, 0x400, 0x10000) == 1) {
        if (func_8012BCCC(s0) < 0x3001) {
            *(s16 *)(s0 + 2) = 8;
            return;
        }
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            func_8012B8E4(s0, (s16)(rand() % 11 + 10)) + *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12);
        func_8012B178(s0, 0xFFFE0000);
        if (func_80189E88(s0) == 0) {
            return;
        }
    } else {
        if (func_80189E88(s0) == 0) {
            *(s16 *)(s0 + 2) = 0xA;
            *(s32 *)(s0 + 0xDC) |= 0x40;
            return;
        }
    }
    if (func_8012BEE8(s0) != 0) {
        func_80189DE0(s0);
    }
}


#include "common.h"

extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 rand(void);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_80189E88(s32 a0);

void func_801890C4(s32 s0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus7)
    s32 v1;

    v0 = func_8012BDBC(s0, 0x400);
    if (v0 == 1) {
        v0 = func_8012BCCC(s0);
        if (v0 >= 0x3001) {
            v0 = rand();
            v0 = func_8012B8E4(s0, (s16)(v0 - v0 / 5 * 5 + 4));
            v1 = *(s32 *)(s0 + 0x20);
            *(s16 *)(v1 + 0x12) = (s16)(*(u16 *)(v1 + 0x12) + v0);
            func_8012B178(s0, 0xFFFC0000);
            func_80189E88(s0);
        } else {
            *(s16 *)(s0 + 2) = 8;
        }
    } else {
        if (func_80189E88(s0) == 0) {
            *(s16 *)(s0 + 2) = 0xA;
        }
    }
}



extern void func_8012A828(s32 a0, void * a1);
extern void func_80189E1C(s32 a0);

void func_80189194(s32 a0)
{

    extern char D_801D7A58[];
    *(short *)(a0 + 0x2) = 0x9;
    func_8012A828(a0, &D_801D7A58);
    *(s32 *)(a0 + 0x1C) = 0x1E;
    func_80189E1C(a0);
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_801891DC;

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 func_80189C68(s32 *arg0);
extern void func_80189B3C(s32 a0);
extern s32 func_80189CD4();  // K&R: 0 of 1 args (P37 rung D t4_D2)
extern void func_80189E1C(s32 a0);

void func_801891DC(s32 a0) {
    s32 v;
    s32 flags;

    v = func_8012B8E4(a0, 0xA);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v;
    if ((*(s32 *)(a0 + 0xDC) & 0x20) != 0) {
        if ((u32)(*(s32 *)(a0 + 0x1C) - 10) < 0xD) {
            func_80189C68(a0);
        }
    } else {
        if (*(s32 *)(a0 + 0x1C) == 0x16) {
            func_80189B3C(a0);
        }
        if (*(s32 *)(a0 + 0x1C) < 0x10) {
            ((void (*)(s32))func_80189CD4)(a0);
        }
    }
    if (func_8012BEE8(a0) != 0) {
        flags = *(s32 *)(a0 + 0xDC);
        if (flags & 1) {
            *(s32 *)(a0 + 0xDC) = flags & 0xFFFFFFFE;
            *(s16 *)(a0 + 2) = 3;
        } else if (flags & 0x10) {
            *(s32 *)(a0 + 0xDC) = flags & 0xFFFFFFEF;
            *(s16 *)(a0 + 2) = 3;
        } else if (func_8012BD3C(a0, 0x400, 0x4000) == 0) {
            *(s16 *)(a0 + 2) = 5;
        } else {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            func_80189E1C(a0);
        }
    }
}



/* func_80189304 — entity state-kick #0xB.
 * Sets the state word at 0x02 to 0xB, hands the entity to the script runner
 * func_8012A828 with table D_801D78A8, clears bit 3 of the flag word at 0xDC,
 * then picks the timer at 0x1C: a fixed 30 when bit 6 was set (also clearing
 * bit 6), otherwise rand() % 16 + 15. Finally, if func_8012BD3C(e,0x400,0x8000)
 * returns 0, bit 3 at 0xDC is set again.
 *
 * §71 sibling-first: func_80184D28 (same TU, same D_801D78A8 script table) is
 * the same `sh 0x2 / jal func_8012A828 / jal rand / sw 0x1C` skeleton and pins
 * the widths: `sh` at 0x02, `sw` at 0x1C/0xDC, and the s16 store scheduled into
 * the jal delay slot.
 */

extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

void func_80189304(void *a0) {

    extern u8 D_801D78A8[];
    s32 flags;
    s32 cleared;
    s32 timer;

    *(s16 *)((s32)a0 + 0x2) = 0xB;
    func_8012A828((s32)a0, D_801D78A8);
    flags = *(s32 *)((s32)a0 + 0xDC);
    cleared = flags & ~8;
    *(s32 *)((s32)a0 + 0xDC) = cleared;
    if (flags & 0x40) {
        *(s32 *)((s32)a0 + 0xDC) = cleared & ~0x40;
        timer = 30;
    } else {
        timer = rand() % 16 + 15;
    }
    *(s32 *)((s32)a0 + 0x1C) = timer;
    if (func_8012BD3C((s32)a0, 0x400, 0x8000) == 0) {
        *(s32 *)((s32)a0 + 0xDC) |= 8;
    }
}


#include "common.h"

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);

void func_801893BC(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v0;

    if (*(s32 *)(s0 + 0xDC) & 8) {
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + 0x44;
    } else {
        v0 = func_8012B8E4(s0, 8);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
        if (v0 == 0) {
            *(s16 *)(s0 + 2) = 5;
            return;
        }
    }
    if (func_8012BEE8(s0) != 0) {
        *(s16 *)(s0 + 2) = 5;
    }
}


extern void func_80189B3C(s32);
    s32 func_8018944C(s32 *a0) {
        *(s32 *)((char *)a0 + 0xdc) &= ~0x10;
        ((void (*)(s32 *))func_80189B3C)(a0);
    }


extern s32 func_80189CD4();  // K&R: 0 of 1 args (P37 rung D t4_D2)
    void func_80189478(void) {
        func_80189CD4();
    }


















void func_80189498(void *a0)
{
  *((short *) (((char *) a0) + 0x2)) = 0x3;
  *((unsigned short *) (((char *) a0) + 0x5c)) = 0xaa10;
  *((short *) (((char *) a0) + 0xfe)) = 0;
}

void func_801894B0(s32 arg0) {
    if (*(s16 *)(arg0 + 0x76) <= 0) {
        *(s32 *)(arg0 + 0xDC) |= 2;
    }
    *(s16 *)(arg0 + 0x52) = -0x30;
}


extern void func_80189B3C(s32 a0);
extern s32 func_80189CD4();  // K&R: 0 of 1 args (P37 rung D t4_D2)

void func_801894DC(s32 a0) {
    if (*(s32 *)(a0 + 0x1C) == *(s32 *)(a0 + 0x1C) / 5 * 5) {
        func_80189B3C(a0);
    }
    if (*(s32 *)(a0 + 0x1C) >= 0xB) {
        ((void (*)(s32))func_80189CD4)(a0);
    }
}


extern u8 D_801D477C;
extern u8 D_801D478C;
extern void func_8001C924(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018C090(s32 a0, u16 *a1, s16 a2);

void func_80189554(s32 param_1) {
    s32 temp_a0;
    s32 v1;
    u16 sp10[3];

    temp_a0 = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(temp_a0 + 0x24) == (s32)&D_801D478C) {
        func_8001C924(temp_a0, &D_801D477C);
    }
    *(s32 *)(param_1 + 0x1C) = 0x18;
    *(s32 *)(param_1 + 0xDC) &= ~0x10;
    v1 = *(u16 *)(param_1 + 0x5E);
    if (v1 == 0x23) {
        *(u16 *)(param_1 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (v1 == 0x24) {
        sp10[0] = 0;
        sp10[1] = 0x10;
        sp10[2] = 0;
        func_8018C090(param_1, sp10, 0);
    }
}


#include "common.h"

extern void func_80189B3C(s32 a0);
extern s32 func_80189CD4();  // K&R: 0 of 1 args (P37 rung D t4_D2)

void func_8018960C(s32 a0) {
    s32 p;

    if (--*(s32 *)(a0 + 0x1C) == 0xE) {
        func_80189B3C(a0);
    }
    if ((u32)(*(s32 *)(a0 + 0x1C) - 4) < 8) {
        ((void (*)(s32))func_80189CD4)(a0);
    }
    if (*(s16 *)(a0 + 0xFE) != 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) += 0x40;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) += 0x40;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) += 0x40;
        p = *(s32 *)(a0 + 0x20);
        if (*(s16 *)(p + 0x18) >= 0x1800) {
            *(s16 *)(p + 0x1C) = 0x1800;
            *(s16 *)(p + 0x1A) = 0x1800;
            *(s16 *)(p + 0x18) = 0x1800;
        }
    }
}


void func_801896EC(s32 param_1) {
    register s32 self __asm__("a1");  // !FAKE: pin a1 — NEEDED DIFFERS (P36 rung B tus7)
    register s32 mask __asm__("a0");  // !FAKE: pin a0 — NEEDED DIFFERS (P36 rung B tus7)
    s32 t;
    s32 q;

    self = param_1;
    t = *(s16 *)(self + 0xAA);
    *(s16 *)(self + 0x5C) = 0;
    *(s16 *)(self + 0x98) = 0;
    *(s32 *)(self + 0x1C) = 0;
    if (t == 0) {
        s32 f;
        mask = ~0x80;
        f = *(s32 *)(self + 0xDC);
        q = *(s32 *)(self + 0x20);
        q = *(u16 *)(q + 0x18);
        f &= mask;
        *(s32 *)(self + 0xDC) = f;
        *(u16 *)(self + 0x100) = q;
    } else {
        s32 p;
        s32 g;
        p = *(s32 *)(self + 0x20);
        g = *(s32 *)(self + 0xDC);
        p = *(u16 *)(p + 0x18);
        __asm__ __volatile__("" : : "r"(p), "r"(p), "r"(p));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus7)
        g |= 0x80;
        *(s32 *)(self + 0xDC) = g;
        *(u16 *)(self + 0x104) = p;
    }
}



// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @unstuck(P36): none - MATCH (41 ins), match_one + rtu_match.
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

void func_80189744(s32 param_1) {

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
        m = *(s16 *)(param_1 + 0x104);
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


void func_801897E8(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }



// @class: regalloc (WIDTH/li!=addu -> MATCH)
// @unstuck(P36): none — MATCH (58 ins), match_one + rtu_match. PIN-FREE (no register __asm__).
// Three levers, in the order they mattered:
//
//  1) The join block indexes every field off $a0, not $s0: the target COPIES the entity into $a0
//     at the TOP of the join block (`addu $a0,$s0,$zero`) and reads 0x5C/0x5E/0x60/0x62/0x20 off
//     that copy.  A naive `e = param_1;` at the join is deleted — cse.c's make_regs_eqv keeps the
//     PARAMETER as qty_first_reg, so canon_reg rewrites every use of `e` back to param_1 and the
//     copy dies.  Writing the copy at the end of the ARMS instead is worse (2 mismatches worse):
//     gcc hoists it above the inner `if` into the beqz delay slot and the arms then read off $a0.
//
//  2) THE LEVER: make the copy's variable ALSO the 0x20 pointer of the /4 arm.  make_regs_eqv only
//     lets the new pseudo take over the quantity when its live range escapes the cse basic block
//     AND outlives the param's last use.  Reusing `a` in the /4 arm (which sits *after* the join in
//     the insn stream, and whose last mention `sh $v0,0x18($a0)` comes after param_1's last mention
//     `lh $v0,0x100($s0)`) satisfies both clauses at once, so `a` becomes canonical, the copy
//     survives, and the block addresses off it.  The same reuse is what puts `lw $a0,0x20($s0)` /
//     `lh $v1,0x18($a0)` in the /4 arm in the target's register order — two separate locals there
//     give the mirrored $v1/$a0 pair (6 extra mismatches; verified).  The reuse must be paired with
//     the join-top copy: `a` shared but copied in the arm instead makes it a plain global allocno,
//     global.c hands it a callee-saved reg and the function grows an $s1 save/restore (60 ins).
//     A `register s32 a __asm__("$4")` pin also reaches 0 here (canon_reg bails on hard regs), but
//     the pin is unnecessary and would trip the §42e/§86 pin guard on the ×6 family remap.
//
//  3) Tail statement order is 0x5C, 0x60, 0x62, 0x5E — the 0x5E store must be LAST.  sched2 works
//     the ready list LIFO, so a 0x5E written third floats to the front of the block as
//     `li $v0,1 / sh $v0,0x5E` and steals $v0 from the 0x5C load-modify-store (9 mismatches).
//     Written last it sinks past `lhu $v0,0x12($v1)`, reuses the now-dead $v1 for its constant and
//     lands where the target has it.  (All 24 orderings byte-swept: only 5C-60-62-5E and
//     60-5C-62-5E reach 0.)
//
//  Widths: 0x100 is read at TWO widths on purpose — `u16` in the flag arm (target `lhu`) and `s16`
//  in the /4 arm (target `lh`); combine folds the extend into the load, so the cast at the use site
//  picks the opcode.  Ditto `|= 1` on the s16 0x5C field giving `lhu`.  §3-T4: both `beqz`es mean
//  the NON-zero arm falls through, i.e. `func_8012BEE8(..) != 0` and `flags & 0x80` are the
//  fall-through arms (Ghidra's seed for this address was a different function entirely).

extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_801897F8(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        if (*(s32 *)(param_1 + 0xDC) & 0x80) {
            p = *(s32 *)(param_1 + 0x20);
            *(s16 *)(p + 0x1C) = 0x1000;
            *(s16 *)(p + 0x18) = 0x1000;
            *(s32 *)(param_1 + 0xDC) &= ~0x80;
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


void func_801898E0(s32 param_1) {
    extern u8 D_801D612C;
    extern u8 D_801D7D90;
    extern void func_8001C924(s32 a0, void *a1);
    extern void func_8012A828(s32 a0, void *a1);

    *(s32 *)(param_1 + 0x1C) = 0x37;
    func_8001C924(*(s32 *)(param_1 + 0x20), &D_801D612C);
    func_8012A828(param_1, &D_801D7D90);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x62);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 arg0);
extern void func_8018A05C(s32 a0);

void func_8018993C(s32 a0) {
    if (*(s32 *)(a0 + 0x1C) < 0x11) {
        s32 mask;
        s32 ptr;
        s32 val;

        mask = 0x80000000;
        ptr = *(s32 *)(a0 + 0x20);
        val = *(s32 *)(ptr + 0x4);
        val ^= mask;
        *(s32 *)(ptr + 0x4) = val;
    }

    if (func_8012BEE8(a0) != 0) {
        func_8002AC00(0xB);
        func_80130D48(a0);
        func_8018A05C(a0);
    }
}


//   the beqz delay slot), so it is the FIRST statement, above the if; (3) both `*(s32*)(p+0x20)`
//   reads in arm A are written as separate expressions — the intervening `sh` to 0x10 blocks CSE,
//   which is why the target reloads 0x20 twice; (4) the tail compare is `iVar1 <= 0x8FFF`, NOT
//   Ghidra's `< 0x9000`: 0x9000 does not fit the signed 16-bit `slti` immediate, so gcc
//   materialises the bound with `ori $v1,$zero,0x8FFF` and emits the operand-reversed
//   `slt $v1,$v1,$v0` + `bnez` over the 0x51F assignment (write the constant as 0x8FFF).
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001C924(s32 a0, void *a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_801899B4(s32 param_1) {

    extern u8 D_801D7E70;
    extern u8 D_801D612C;
    extern u8 D_801D7D90;
    s32 iVar1;
    s32 uVar2;

    *(s16 *)(param_1 + 0x5C) = 0;
    if (*(s32 *)(param_1 + 0xDC) & 2) {
        *(s32 *)(param_1 + 0x1C) = 0x2D;
        func_8012A828(param_1, &D_801D7E70);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            (*(u16 *)(param_1 + 0x62) + 0x800) & 0xFFF;
        *(s16 *)(param_1 + 0x52) = 0;
    } else {
        *(s32 *)(param_1 + 0x1C) = 0x37;
        func_8001C924(*(s32 *)(param_1 + 0x20), &D_801D612C);
        func_8012A828(param_1, &D_801D7D90);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x62);
    }
    iVar1 = func_8012BCCC(param_1);
    uVar2 = 0x520;
    if (iVar1 <= 0x8FFF) {
        uVar2 = 0x51F;
    }
    func_8002D4C8(uVar2, 0);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 a0);
extern void func_8018A05C(s32 a0);

void func_80189A84(s32 a0)
{
    if ((*(s32 *)(a0 + 0xDC) & 0x2) != 0) {
        if (*(s32 *)(a0 + 0x1C) >= 0x15) {
            s32 p = *(s32 *)(a0 + 0x20);
            *(s16 *)(p + 0x10) = *(u16 *)(p + 0x10) - 0x28;
        }
    }
    if (*(s32 *)(a0 + 0x1C) < 0x11) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) ^= 0x80000000;
    }
    if (func_8012BEE8(a0) != 0) {
        func_8002AC00(0xB);
        func_80130D48(a0);
        func_8018A05C(a0);
    }
}


#include "common.h"

extern s32 rand(void);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012B0B4(u32 *param_1, s32 param_2, s32 param_3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80189B3C(s32 a0) {
    s32 i;
    s32 q;
    s32 r3;
    u32 buf[2];
    s32 v;

    if (*(s16 *)(a0 + 0xAA) <= 0) {
        for (i = 0; i < 10; i++) {
            q = func_80132EF4(a0, 0x22);
            if (q != 0) {
                func_8012B0B4(buf, rand() % 4096, rand() % 64);
                v = *(s32 *)buf;
                *(u16 *)(q + 0x6) += v;
                *(u16 *)(q + 0xA) -= 0x60;
                *(u16 *)(q + 0xE) += v >> 16;
                r3 = rand();
                *(s16 *)(q + 0x34) = (r3 % 3) * 0x1000 + 0x3000;
            }
        }
        func_8002D4C8(0x521, 0);
    }
}



s32 func_80189C68(s32 *arg0)
{
    extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 D_801D2B7C[];
    if ((*(u32 *)((s8 *)arg0 + 0xDC) & 1) != 0) {
        return 0;
    }
    if (func_8012D5E4((s32)arg0, (s32)D_801D2B7C, (s32)D_801D2B7C + 8, 0xB) != 1) {
        return 0;
    }
    *(u32 *)((s8 *)arg0 + 0xDC) |= 1;
    return 1;
}


#include "common.h"

extern s32 func_8014CB0C(void);
extern void func_8012BD14(s32 a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

s32 func_80189CD4(s32 a0) {
    s16 diff[3];
    s16 pointA[3];
    s32 flags;

    if (*(u16 *)(a0 + 0x5E) == 0x1E) {
        return 0;
    }
    if (func_8014CB0C() != 0) {
        return 0;
    }
    if ((*(s32 *)(a0 + 0xDC) & 0x10) != 0) {
        return 0;
    }
    if (((s32 (*)(s32))func_8012BD14)(a0) < 0x2401) {
        pointA[0] = D_80126B5E;
        pointA[1] = D_80126B62;
        pointA[2] = D_80126B66;

        diff[0] = pointA[0] - *(u16 *)(a0 + 0x6);
        diff[1] = pointA[1] - *(u16 *)(a0 + 0xA);
        diff[2] = pointA[2] - *(u16 *)(a0 + 0xE);

        VectorNormalSS(diff, diff);

        pointA[1] -= 0x20;
        func_8012F568(1, 6, 0, 0, (s32)pointA, (s32)diff);

        flags = *(s32 *)(a0 + 0xDC);
        flags |= 0x10;
        *(s32 *)(a0 + 0xDC) = flags;
        return 1;
    }
    return 0;
}


extern s32 rand(void);
    void func_80189DE0(s32 arg0) {
        if ((rand() & 1) != 0) {
            *(s16*)(arg0 + 0x2) = 0xA;
        } else {
            *(s16*)(arg0 + 0x2) = 0x3;
        }
    }


extern s32 func_8014CB0C(void);
extern s32 rand(void);

void func_80189E1C(s32 a0) {
    s32 ret;
    s32 s0;

    ret = func_8014CB0C();
    s0 = a0;
    if (ret != 0) {
        *(s32 *)(s0 + 0xDC) |= 0x20;
    } else {
        if ((rand() & 1) != 0) {
            *(s32 *)(s0 + 0xDC) |= 0x20;
        } else {
            *(s32 *)(s0 + 0xDC) &= ~0x20;
        }
    }
}


#include "common.h"

extern void func_8012ADE4(u8 *a0);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern u8 D_801202A0[];

s32 func_80189E88(s32 a0) {
    s32 raw;
    s32 ret;
    u8 *p;
    s32 i;
    u16 kind;
    s16 buf1[3];
    s16 buf2[3];

    ret = 1;
    raw = ((s32 (*)(s32))func_8012CBA4)(a0);
    if ((raw & 0xFF) == 2) {
        ((void (*)(s32, s32))func_80131E00)(a0, 0x12);
        return 0;
    }
    if (raw & 0x8000) {
        if (!(raw & 0x2000)) {
            func_8012ADE4((u8 *)a0);
        }
        ret = 0;
    }
    if ((raw & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)a0);
        ret = 0;
    }

    *(s32 *)(a0 + 0xDC) &= ~0x40;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        kind = *(u16 *)p;
        if (kind == 0xAF || kind == 0x6F || kind == 0x100) {
            if (*(s32 *)(p + 0x58) != 0 && a0 != (s32)p) {
                buf1[0] = *(u16 *)(a0 + 0x3A);
                buf1[1] = *(u16 *)(a0 + 0x3E);
                buf1[2] = *(u16 *)(a0 + 0x42);
                buf2[0] = *(u16 *)(a0 + 0x6);
                buf2[1] = *(u16 *)(a0 + 0xA);
                buf2[2] = *(u16 *)(a0 + 0xE);
                if (func_80135A4C(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58),
                                   (s32 *)buf1, (s32)buf2) != 0) {
                    if ((func_8012CEB0((s32)buf1, (s32)buf2, 0) & 0x2000) == 0) {
                        func_8012ADE4((u8 *)a0);
                        return ret;
                    }
                    *(u16 *)(a0 + 0x6) = buf2[0];
                    *(u16 *)(a0 + 0xA) = buf2[1];
                    *(u16 *)(a0 + 0xE) = buf2[2];
                    break;
                }
            }
        }
    }
    return ret;
}


#include "common.h"

extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C218(void *a0);

void func_8018A05C(s32 a0)
{
    s32 v1;

    if (*(short *)((char *)a0 + 0x102) == 0) {
        func_8002A04C((s32)a0);
        if (*(unsigned char *)((char *)a0 + 0xC1) == 0xE) {
            func_8002AC00(0xB);
        }
    }

    if (!((*(short *)((char *)a0 + 0x70) & 0x8000))) {
        v1 = *(s32 *)((char *)a0 + 0x68);
        if (v1 != 0 && ((*(short *)((char *)a0 + 0x72) & 0x8000))) {
            *(unsigned short *)(v1 + 0xA) = *(unsigned short *)(v1 + 0xA) & 0x7FFF;
        }
    }

    func_8012C218(a0);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_8018A100(void) {
        func_8002D4C8(0x6AA, 0);
    }


extern void func_8018A168();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)
extern void func_8018A3D4();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)

void func_8018A124(s32 *a0, s32 a1) {
    if (*(s32 *)((s32)a0 + 0xC4) & 4) {
        func_8018A168((s32)a0, a1);
    } else {
        func_8018A3D4((s32)a0, a1);
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern unsigned char D_801DFC6C[];

void func_8018A168(int param_1)
{
    *(short *)(param_1 + 2) = 5;
    *(short *)(param_1 + 0x34) = 0;
    *(unsigned short *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, &D_801DFC6C);
    func_8012B23C(param_1);
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A4B4(s32 param_1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8018A5C4(s32 a0);
extern void func_8018A6F4(s32 a0);
extern void func_8018A384(s16 *a0);
extern void func_8018A598(void *a0);
extern s32 func_8018A698(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_8018A3D4();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8018A538(s32 param_1);
extern s32 D_801D7E84;

void func_8018A1B4(s32 a0)
{
    s32 s0 = a0;
    s32 v0;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0: {
        s32 v1;
        v0 = func_8012B8E4(s0, 4);
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + v0;
        if (*(s32 *)(s0 + 0x1C) == 0xF) {
            func_80142414(s0, -0x78);
            func_8002D4C8(0x6A9, 0);
        }
        if (func_8012BEE8(s0) != 0) {
            func_8018A4B4((s16 *)s0);
        }
        break;
    }
    case 1: {
        s32 v1;
        s32 v2;
        v0 = func_8012B8E4(s0, 6);
        v2 = D_801D7E84;
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x12) = *(u16 *)(v1 + 0x12) + v0;
        func_8012B178(s0, v2);
        func_8018A5C4(s0);
        func_8018A6F4(s0);
        func_8018A384((s16 *)s0);
        func_8018A598((void *)s0);
        if (func_8018A698(s0) != 0 || func_8012BCCC(s0) > 0x40000) {
            func_8018A3D4(s0);
        }
        if (func_8012BD3C(s0, 0x300, 0x4000) != 0) {
            func_8018A538(s0);
        }
        break;
    }
    }
}


extern s32 D_801D7F10;

void func_8018A2F8(s32 param_1) {
    s32 *p;
    u16 v;

    v = *(u16 *)(param_1 + 0x70);
    p = &D_801D7F10;
    if ((v & 0x2000) == 0) {
        p += 3;
    }
    *(u16 *)(param_1 + 2) = 7;
    func_8012A828(param_1, (void *)p[0]);
    func_8012B2CC(param_1);
    func_8012B200((u8 *)param_1);
    func_8012B178(param_1, (s32)p[1]);
    *(s32 *)(param_1 + 0x1C) = p[2];
    *(u16 *)(param_1 + 0x5C) = *(u16 *)(*(s32 *)(param_1 + 0x78) + 2);
}


void func_8018A384(s16 *param_1)
{
    s32 s0 = (s32)param_1;
    u16 v;

    v = *(u16 *)(s0 + 0xFE);
    v = v - 1;
    *(u16 *)(s0 + 0xFE) = v;
    if ((s32)(v << 16) <= 0) {
        func_80143B6C(param_1, 0);
        *(u16 *)(s0 + 0xFE) = 8;
    }
}


#include "common.h"

extern s32 rand(void);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8018A698(s32 a0);
extern u8 D_801DFA6C[];

void func_8018A3D4(s32 param_1) {
    *(s16 *)(param_1 + 0x2) = 1;
    *(s16 *)(param_1 + 0x34) = 0;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    *(s32 *)(param_1 + 0x1C) = (rand() & 0x1F) + 0x24;

    if (func_8018A698(param_1) != 0) {
        *(s16 *)(param_1 + 0xFC) =
            func_8012B744((void *)(param_1 + 0x4), (void *)(param_1 + 0x88));
    } else {
        s32 t = rand() & 0x3FF;
        s32 v1 = t - 0x200;

        if (v1 < 0) {
            v1 = t - 0x500;
        } else {
            v1 = t + 0x100;
        }
        *(s16 *)(param_1 + 0xFC) =
            (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v1) & 0xFFF;
    }

    func_8012A828(param_1, D_801DFA6C);
}




extern void func_8012A828(s32, void*);
    extern short D_801DF924;
    void func_8018A484(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801DF924);
    }


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);

extern u8 D_801DFF34;
extern u8 D_801DFB14;

void func_8018A4B4(s32 param_1) {
    *(s16 *)(param_1 + 0x2) = 3;
    if (*(u16 *)(param_1 + 0x86) & 2) {
        *(s16 *)(param_1 + 0x34) = 1;
        *(s32 *)(param_1 + 0x1C) = 0x28;
        func_8012A828(param_1, &D_801DFF34);
        *(u16 *)(param_1 + 0xFE) = 0;
    } else {
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801DFB14);
        *(s32 *)(param_1 + 0x1C) = 0x19;
        *(u16 *)(param_1 + 0x86) |= 2;
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801E0084;
extern s32 D_801D7E84;
extern s32 D_801F7740;

void func_8018A538(s32 param_1) {
    s32 v1;

    *(u16 *)(param_1 + 2) = 4;
    *(u16 *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801E0084);
    v1 = D_801D7E84;
    *(s32 *)(param_1 + 0x1C) = 0x28;
    D_801F7740 = v1;
    func_8002D4C8(0x660, 0);
}


extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801D7F28[];

void func_8018A598(void* arg0)
{
    func_8012D5E4(arg0, (s32)D_801D7F28, (s32)D_801D7F28 + 8, 0x11);
}


extern void func_8012CBA4(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012ADE4(u8 *a0);

s32 func_8018A5C4_impl(s32 a0) __asm__("func_8018A5C4");
s32 func_8018A5C4_impl(s32 a0)
{
    s32 flags;

    flags = ((s32 (*)(s32))func_8012CBA4)(a0);
    if ((flags & 0x1000) != 0) {
        ((void (*)(s32, s32))func_80131E00)(a0, 0x12);
        return 0;
    }
    if (flags != 0x2000) {
        func_8012ADE4((u8 *)a0);
    }
    return 1;
}


#include "common.h"

extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void);

void func_8018A624(s32 arg0) {
    u8 val;

    /* Check field at +0x100 */
    if (((s16 *)arg0)[0x80] == 0) {
        func_8002A04C(arg0);
    }

    /* Check field at +0xC1 */
    val = ((u8 *)arg0)[0xC1];
    if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
        func_8002AC00(0x7);
    }

    /* Always call func_8012C098 */
    ((void (*)(s32))func_8012C098)(arg0);
}


#include "common.h"

extern void Square0(s32 *a0, s32 *a1);

s32 func_8018A698(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return 0x18FFFF < v[0] + v[2];
}


    
typedef struct { s16 a, b, c; } SV3_80184C98;

/* func_8018A6F4 -- same-class neighbour push-away over the 0x60-entry /
 * 0x10C-stride entity table D_801202A0. Banked twin: ov_SC06_018:func_80187320
 * (§193-A), minus its second switch case (no 0x2F4 clamp here) and with a
 * self-id equality guard instead of constant class ids.
 *
 * §37/§124 DEF-SIDE ESCAPE (_body spelling, cf. func_801810CC_body,
 * ov_SC07_007_jr_8017BEBC.c:6600): this TU already declares
 * `extern void func_8018A6F4(s32 a0);` at file scope (the func_80188654 block),
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

s32 func_80188250_body(s32 a0) __asm__("func_8018A6F4");

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
                do { *(u16 *)(a0 + 0xE) = v18[2]; } while (0);
                return 1;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);
    return 0;
}


#include "common.h"

extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void);

extern s32 D_801D7F38[];

void func_8018A86C(s32 arg0) {
    void (*handler)(s32);
    u8 val;

    /* Load dispatch function from table indexed by field at +0x2 */
    handler = (void (*)(s32))D_801D7F38[((u16 *)arg0)[1]];
    handler(arg0);

    /* Check field at +0x0 */
    if (((u16 *)arg0)[0] == 0)
        return;

    /* Check field at +0xA */
    if (((s16 *)arg0)[5] < 0x10)
        return;

    /* Check field at +0x100 */
    if (((s16 *)arg0)[0x80] == 0) {
        func_8002A04C(arg0);
    }

    /* Check field at +0xC1 */
    val = ((u8 *)arg0)[0xC1];
    if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
        func_8002AC00(0x7);
    }

    /* Always call func_8012C098 */
    ((void (*)(s32))func_8012C098)(arg0);
}


extern void func_8012CBF4(s32 a0);
extern void func_8018A3D4();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)

void func_8018A928(s32 a0)
{
    func_8012CBF4(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_8018A3D4(a0);
    }
}


#include "common.h"

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C044(s32 a0);

extern s32 func_8018A698(s32 a0);
extern void func_8018A4B4(s32 param_1);
extern void func_8018A5C4(s32 a0);
extern void func_8018A6F4(s32 a0);
extern void func_8018A484(short *a0);
extern void func_8018A624(s32 arg0);

extern s32 D_801D7E80;

void func_8018A96C(s32 a0)
{
    s32 s0 = a0;
    s32 v0;

    if (*(s32 *)(s0 + 0x1C) >= 4) {
        v0 = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), *(s16 *)(s0 + 0xFC), 8);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
    }

    if (func_8018A698(s0) == 0) {
        if (func_8012BD3C(s0, 0x300, 0x10000) != 0) {
            func_8018A4B4((s16 *)s0);
            return;
        }
    }

    func_8012B178(s0, D_801D7E80);
    func_8018A5C4(s0);
    func_8018A6F4(s0);
    if (func_8012BEE8(s0) != 0) {
        func_8018A484((short *)s0);
        return;
    }
    if (func_8012C044(s0) != 0) {
        *(u16 *)(s0 + 0x100) = 1;
        func_8018A624(s0);
    }
}


extern s32 func_8018A698(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8018A4B4(s32 param_1);
extern void func_8018A3D4();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)

void func_8018AA60(s32 param_1)
{
    if (*(u16 *)(param_1 + 0x34) == 0) {
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            if (func_8018A698(param_1) == 0) {
                if (func_8012BD3C(param_1, 0x300, 0x40000) != 0) {
                    func_8018A4B4((s16 *)param_1);
                    return;
                }
            }
            func_8018A3D4(param_1);
        }
    }
}


#include "common.h"

extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8018A484(short *a0);
extern void func_8018A598(void *a0);
extern void func_8018A5C4(s32 a0);
extern void func_8018A6F4(s32 a0);
extern s32 D_801F7740;

void func_8018AAE4(s32 a0)
{
    u16 v0;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if (*(s32 *)(a0 + 0x1C) % 10 == 0) {
            D_801F7740 += 0x10000;
        }
        func_8012B178(a0, D_801F7740);
        func_8018A5C4(a0);
        func_8018A6F4(a0);
        func_8018A598((void *)a0);

        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s32)(v0 << 16) <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = -(D_801F7740 / 0x10000);
        }

        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0xA;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
    } else if (func_8012BEE8(a0) != 0) {
        func_8018A484((short *)a0);
    }
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern void func_8012E88C(s32 a0);
extern void func_8018A2F8(s32 a0);
extern s32 D_801D7F0C;

void func_8018AC10(void *a0) {
    s32 s0 = (s32)a0;
    s32 v0 = func_8012BCCC(s0);
    if (v0 < D_801D7F0C) {
        func_8012E88C(s0);
        func_8018A2F8(s0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8018A384(s16 *a0);
extern void func_8018A598(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A4B4(s32 param_1);

void func_8018AC60(s32 a0) {
    func_8012AD80(a0);
    if (*(u16 *)(a0 + 0x70) & 0x2000) {
        func_8018A384((s16 *)a0);
        func_8018A598((void *)a0);
    }
    if (func_8012BEE8(a0) != 0) {
        *(u16 *)(a0 + 0x86) |= 2;
        func_8018A4B4((s16 *)a0);
    }
}


void func_8018ACD0(s32 param_1) {
    extern u8 D_801D7E98[];
    extern u8 D_801D7ECC[];
    extern s16 D_801DF924;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8012B030(u8 *a0);
    extern void func_8012E8A8(u8 *a0);
    extern s32 func_80143970(s32 a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_8018A3D4();  // K&R: 1/2 of 1 args (P37 rung D t4_D2)

    if (func_8012C354(param_1, (s32)D_801D7E98) != 0) {
        *(u8 *)(param_1 + 0xC0) = 1;
        *(s32 *)(param_1 + 0xB4) = -1;
        *(u8 *)(param_1 + 0xC1) = 0;
        *(u32 *)(param_1 + 0xBC) = (u32)D_801D7ECC;
        func_80143970(param_1);
        func_8012B030((u8 *)param_1);
        if (*(u16 *)(param_1 + 0x70) & 0x6000) {
            *(u16 *)(param_1 + 2) = 6;
            func_8012A828(param_1, &D_801DF924);
            func_8012E8A8((u8 *)param_1);
            *(u16 *)(param_1 + 0x5C) = 0;
        } else {
            func_8018A3D4(param_1);
        }
        func_8012B2CC(param_1);
    }
}


extern void func_8012C098(void);
    void func_8018AD7C(void) {
        func_8012C098();
    }


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018C090(s32 a0, u16 *a1, s16 a2);

void func_8018AD9C(void *a0) {
    s16 sp10[3];
    u16 id;

    id = *(u16 *)(a0 + 0x5E);
    if (id == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (id == 0x24) {
        sp10[0] = 2;
        sp10[1] = 0xF;
        sp10[2] = -2;
        func_8018C090((s32)a0, (u16 *)sp10, 0xD);
    }
}



/* func_8018AE08 — light/colour ramp-up on the entity's attached prim block.
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
void func_8018AE08(int param_1) {
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


void func_8018AE90(s32 param_1) {
    *(s16 *)(param_1 + 0x5C) = 0;
    *(s16 *)(param_1 + 0x98) = 0;
    *(s32 *)(param_1 + 0x1C) = 0;
    if (*(s16 *)(param_1 + 0xAA) == 0) {
        *(s16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    } else {
        *(s16 *)(param_1 + 0x102) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    }
}



// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @unstuck(P36): none - MATCH (41 ins), match_one + rtu_match.
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

void func_8018AED4(s32 param_1) {

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



void func_8018AF78(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_8018AF88(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        p = *(s32 *)(param_1 + 0x20);
        do { h = *(u16 *)(param_1 + 0x100); } while (0);
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
// @unstuck(P36): none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);
extern void D_801E7D24;

void func_8018B034(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801E7D24)) {
        func_8012A828(arg0, &D_801E7D24);
    }
}


extern void func_8002AC00(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018B07C(s32 *arg0) {
    func_8002AC00(8);
    if (*(u16 *)((u8 *)arg0 + 0x5E) == 0x1D) {
        func_8002D4C8(0x440, 0);
    } else {
        func_8002D4C8(0x43F, 0);
    }
}



extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E81AC;

void func_8018B0C4(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801E81AC);
    *(s32 *)(a0 + 0x1C) = 0x14;
}



// @class: schedule
// @unstuck(P36): none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_8018B1B4 else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_8018B1B4(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E8104;

s32 func_8018B104(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_8018B1B4(param_1);
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
    func_8012A828(param_1, &D_801E8104);
    return 1;
}



// @class: plumbing
// @unstuck(P36): none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801E7EC4;

void func_8018B1B4(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801E7EC4);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_8018B210(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0x14;
    }


extern void D_801E7D24;
extern void func_8012A828(s32 a0, void *a1);

s32 func_8018B224(a0)
void *a0;
{
    u16 v;
    *(u16 *)((s32)a0 + 2) = 3;
    func_8012A828((s32)a0, &D_801E7D24);
    v = *(u16 *)(*(s32 *)((s32)a0 + 0x78) + 2);
    *(u16 *)((s32)a0 + 0x5E) = 0;
    *(u16 *)((s32)a0 + 0xDC) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x3C;
    *(u16 *)((s32)a0 + 0xFE) = 0;
    *(u16 *)((s32)a0 + 0x5C) = v;
}


extern s32 (*D_801E0188[])(void);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void);

void func_8018B280(u16 *s0)
{
    s32 v0;
    s32 temp;

    
    v0 = D_801E0188[s0[1]]();

    
    if (s0[0] != 0) {
        
        temp = *(s32 *)(s0 + 0x10);
        
        *(u16 *)((char *)temp + 0x2c) = *(u16 *)((char *)temp + 0x2c) | 0x10;

        
        v0 = func_8012C044((s32)s0);
        if (v0 != 0) {
            
            ((void (*)(s32))func_8012C098)((s32)s0);
        }
    }
}



extern void (*D_801E01A8[])(void);

void func_8018B304(void *a0) {
    D_801E01A8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E01F0[])(void);

void func_8018B340(void *a0) {
    D_801E01F0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @unstuck(P36): none — MATCH (clean if/else, sh into delay slot of func_8001CA88 call)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern void func_80143994(s32 a0, s32 a1);
extern int D_801E01B0;

void func_8018B37C(int param_1)
{
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        *(short *)(param_1 + 2) = 1;
        func_8001CA88(*(int *)(param_1 + 0x20), &D_801E01B0);
        func_80143994(param_1, 0x1000);
    }
}


extern void func_8012B2CC(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8018B3E0(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF20000);
}


extern void func_8012CBF4(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012C218(void *a0);
extern s16 D_801E01FC[];
extern u8 D_800D3918[];

void func_8018B438(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(s32))func_8012CBF4)(param_1);
    if (v0 != 0) goto kill;
    v0 = func_8012D5E4(param_1, (s32)&D_801E01FC, (s32)D_800D3918, 0xA);
    if (v0 != 0) goto kill;
    v0 = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = v0;
    if (v0 != 0) return;
kill:
    func_8012C218((void *)param_1);
}



extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018B224(void * a0);
extern u16 D_80126B96;
extern u8 D_801E0170[];
extern u8 D_801E0180[];

void func_8018B4A4(s32 arg0) {
    u16 sp10[3];
    u16 sp18[12];

    if (*(s32 *)(arg0 + 0x1C) == 9) {
        if (func_8012D5E4(arg0, (s32)D_801E0170, (s32)(D_801E0170 + 8), 10) != 0) {
            D_80126B96 |= 0x800;
        }
        if (*(s16 *)(arg0 + 0x70) & 0x8000) {
            func_8012F214(arg0, (s32)D_801E0180, (s32)sp10);
            sp18[3] = 0x126;
            sp18[5] = 0;
            sp18[6] = 0x7FFF;
            sp18[0] = sp10[0];
            sp18[1] = sp10[1];
            sp18[2] = sp10[2];
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            func_8012C51C(sp18, arg0);
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x100;
            func_8012C51C(sp18, arg0);
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) - 0x100;
            func_8012C51C(sp18, arg0);
        }
        func_8002D4C8(0x43E, 0);
    }
    if (func_8012BEE8(arg0) != 0) {
        ((void (*)(void *))func_8018B224)(arg0);
    }
}


extern s32 func_8012BCCC(s32 a0);

void func_8018B5E0(s32 a0) {
    s32 result;
    s32 threshold;

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
    func_8018B0C4(a0);
}


extern s32 func_8012BEE8(s32 arg);
    extern s32 func_8018B224(void * a0);
    void func_8018B64C(void *a0) {
        if (func_8012BEE8((s32)a0)) {
            ((void (*)(s32))func_8018B224)((s32)a0);
        }
    }


extern s32 func_8012BEE8(s32 a0);

void func_8018B684(s32 param_1)
{
    if (func_8012BEE8(param_1) == 1) {
        if (*(s16 *)(param_1 + 0x70) & 0x8000) {
            func_8018B104(param_1, 0x40000, 0xC4000);
        } else {
            func_8018B104(param_1, 0x9000, 0x24000);
        }
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018B210(void*);

void func_8018B6E8(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_8018B210)(param_1);
    }
}


extern s32 D_801E00B4;
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_801E00E8;
extern u8 D_801E8104;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012CAE4(void *a0);

void func_8018B740(s32 s0) {
    s32 v1;
    s32 v0;
    s32 a1v;

    v0 = func_8012C354(s0, (s32)&D_801E00B4);
    if (v0 == 0) {
        return;
    }

    v1 = 0xFFFBFFFD;
    *(s32 *)(s0 + 0xB4) = v1;
    v1 = *(s32 *)(s0 + 0x20);
    *(u8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)&D_801E00E8;
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
        func_8012A828(s0, (void *)&D_801E8104);
    }
}


extern s32 D_801E1CA4;
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_8018B7F8(int param_1)
{
    int v0;
    int v1;
    int temp;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801E1CA4);
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
extern s32 D_801E82FC;
extern s32 D_801E01A0;

void func_8018B868(int param_1)
{
    s32 unk64;
    SV4 svec;

    unk64 = *(s32 *)(param_1 + 0x64);

    if (*(s16 *)(param_1 + 0xFE) == 0x7FFF) {
        *(s16 *)(param_1 + 0xFE) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
    }

    if (*(s16 *)(param_1 + 0xFC) != *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x36)) {
        func_8012C218((void *)param_1);
        return;
    }

    *(SV4 *)(*(s32 *)(param_1 + 0x20) + 0x10) = *(SV4 *)(*(s32 *)(unk64 + 0x20) + 0x10);

    if (*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x90) != (s32)&D_801E82FC) {
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xFE);
        *(s32 *)(param_1 + 0x4) = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x4);
        *(s32 *)(param_1 + 0x8) = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x8);
        *(s32 *)(param_1 + 0xC) = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0xC);
    } else {
        func_8012F214(*(s32 *)(param_1 + 0x64), (s32)&D_801E01A0, (s32)&svec);
        *(s16 *)(param_1 + 0x6) = svec.a;
        *(s16 *)(param_1 + 0xA) = svec.b;
        *(s16 *)(param_1 + 0xE) = svec.c;
    }

    *(SV4 *)(*(s32 *)(param_1 + 0x20) + 0x18) = *(SV4 *)(*(s32 *)(unk64 + 0x20) + 0x18);

    {
        u16 flag = *(u16 *)(*(s32 *)(unk64 + 0x20) + 0x2C) & 0x10;
        u16 dflags = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) = dflags | flag;
    }

    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4) = *(s32 *)(*(s32 *)(unk64 + 0x20) + 0x4);
}


extern void func_80029124(s32 arg0, s32 arg1);
    void func_8018B9F8(void) {
        func_80029124(0xF0, 1);
    }


extern void (*D_801F1714[])(void);

void func_8018BA1C(void *a0) {
    D_801F1714[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8018BF78(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8018BFD0(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018BA58(s32 a0) {
    extern u8 D_801F16C8[];
    extern u8 D_801F16D4[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_8018BF78(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801F16C8, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801F16D4);
        func_8018BFD0(a0);
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
extern void func_8018BFD0(s32 arg0);
extern void func_8018C04C(void *arg0);

void func_8018BB54(s32 arg0) {
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
            func_8018BFD0(arg0);
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
    func_8018C04C((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8018BFD0(s32 arg0);
extern void func_8018C04C(void *arg0);

void func_8018BDE4(s32 arg0) {

    extern u16 D_800B99DA;
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
        func_8018BFD0(arg0);
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
    func_8018C04C((void *)arg0);
}



/* func_8018BF78 — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_8018BF78(s32 arg0) {
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



extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8018BFD0(s32 arg0) {
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



/* func_8018C04C — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_8018C04C(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_8018C090(s32 a0, u16 *a1, s16 a2) {
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


extern void func_80174684(void *);
    extern s32 func_8018C118;
    void func_8018C0F0(void) {
        func_80174684(&func_8018C118);
    }




void aF8018C118(void *a0) __asm__("func_8018C118");
void aF8018C118(void *a0)
{

    extern void (*D_801F2594[])(void);
    D_801F2594[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014706C(void *a0);
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);

void func_8018C154(s32 *a0) {
    s32 *v1;
    func_8014706C(a0);
    func_801553A8(a0);
    func_80155440(a0);
    func_80154150((s32)a0, 0x26);
    func_80154A74((s32)a0, 0x1E);
    v1 = *(s32 **)((u8 *)a0 + 0x20);
    *(u16 *)((u8 *)v1 + 0x10) = 0xFE9;
    *(s32 *)((u8 *)a0 + 0x208) = 0;
    func_80171A1C((u8 *)a0);
    func_8018C1C4(a0);
}


extern void func_80171A1C(u8*);

    void func_8018C1C4(void *arg0) {
        s32 p;
        s32 q;
        *(s32 *)((u8 *)arg0 + 0x208) += 0x1c000;
        p = *(s32 *)((u8 *)arg0 + 0x20);
        *(u16 *)((u8 *)p + 0x10) = (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x20A)) & 0xfff;
        q = *(s32 *)((u8 *)arg0 + 0x20);
        if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
            *(u16 *)((u8 *)q + 0x10) = 0xc00;
            *(u16 *)((u8 *)arg0 + 0xb8) = 1;
            ((void (*)(void *))func_80171A1C)(arg0);
        }
    }


extern s32 func_80174650(s32);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);

    void func_8018C240(void *a0) {
        if (*(u16 *)(a0 + 0xB8) & 0x8000) {
            func_80154150((s32)a0, 0x27);
            func_80154A74((s32)a0, 0x1F);
            func_80171A1C((u8 *)a0);
            func_80174650((s32)a0);
        }
    }


void func_8018C29C(void) {
}

extern void func_80174684(void *);
    extern s32 func_8018C2CC;
    void func_8018C2A4(void) {
        func_80174684(&func_8018C2CC);
    }




void aF8018C2CC(void *a0) __asm__("func_8018C2CC");
void aF8018C2CC(void *a0)
{

    extern void (*D_801F25A4[])(void);
    D_801F25A4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014706C(void *a0);
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32 a0);

void func_8018C308(s32 *a0) {
    func_8014706C(a0);
    func_801553A8(a0);
    func_80155440(a0);
    *(s16 *)((u8 *)(*(s32 **)((u8 *)a0 + 0x20)) + 0x10) = 0xC00;
    func_80154150((s32)a0, 0x27);
    func_80154A74((s32)a0, 0x1F);
    func_80171A1C((u8 *)a0);
    func_80174650((s32)a0);
}


void func_8018C374(void) {
}

extern void func_80174684(void *);
    extern void func_8018C3A4(void *a0);
    void func_8018C37C(void) {
        func_80174684((void *)func_8018C3A4);
    }




void func_8018C3A4(void *a0) {

    extern void (*D_801F25AC[])(void);
    D_801F25AC[*(u8 *)((s32)a0 + 0x214)]();
}


extern u8 D_801F2528[];
extern void func_8014706C(void *arg0);
extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern void func_8018C43C(void *a0);

void func_8018C3E0(s32 *a0) {
    func_8014706C(a0);
    func_80154274(a0, (s32)D_801F2528);
    *(s16 *)((u8 *)(*(s32 **)((u8 *)a0 + 0x20)) + 0x10) = 0xC00;
    func_80147324(0xA05);
    func_80171A1C((u8 *)a0);
    func_8018C43C(a0);
}


extern s32 func_80174650(s32);
extern void func_80147060(u8 *a0);
extern void func_80171A1C(u8 *a0);

    void func_8018C43C(void *a0) {
        if (*(u16 *)(a0 + 0xB8) & 0x8000) {
            func_80147060((u8 *)a0);
            func_80171A1C((u8 *)a0);
            func_80174650((s32)a0);
        }
    }


void func_8018C48C(void) {
}

extern void func_80174684(void *);
    extern void func_8018C4BC(void *a0);
    void func_8018C494(void) {
        func_80174684((void *)func_8018C4BC);
    }




void func_8018C4BC(void *a0) {

    extern void (*D_801F25B8[])(void);
    D_801F25B8[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014706C(void *arg0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern void func_8018C58C();

void func_8018C4F8(void *a0) {
    func_8014706C(a0);
    func_80154150((s32)a0, 0x24);
    func_80154A74((s32)a0, 0x1D);
    func_80171A1C((u8 *)a0);
    func_8018C58C((s32)a0);
}


extern void func_80154150(s32 a0, s32 a1);
extern void func_80171A1C(u8 *a0);

void func_8018C548(void *a0) {
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_80154150((s32)a0, 0x25);
        func_80171A1C((u8 *)a0);
    }
}


void func_8018C58C(void) {
}




