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
      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018C880;
extern u8 D_8018C7F0;
extern u8 D_8018C7CC;
extern u8 D_8018C7A8;
extern u8 D_8018C85C;
extern u8 D_8018C838;
extern u8 D_8018C814;
extern u8 D_8018C784;
extern void func_80145934(void);
extern u8 D_8018C910;
extern u8 D_8018C8EC;
extern u8 D_8018C8C8;
extern u8 D_8018C8A4;
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
extern unsigned char D_8018BD08[];
extern unsigned char D_8018BD38[];
extern unsigned char D_8018BD88[];
extern unsigned char D_8018BDB8[];
extern unsigned char D_8018BDE8[];
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
extern void (*D_8018BE38[])(void *);
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
extern s32 D_8018BF00[];
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
extern u8 D_8018BF88[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018BF90;
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
extern int D_801B8498;
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
extern s32 D_801B849C;
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
extern s32 D_8018BFC0;
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
extern void (*D_8018C068[])(void);
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
extern void (*D_8018C08C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C07C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C0A0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C0AC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C0BC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C0D4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C0C4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C0E8[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C104[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C0F4;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C118[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C12C[])(void);
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
extern s32 D_8018C140;
extern void (*D_8018C168[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C148;
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
extern int (*D_8018C1B4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018C1B8[])(void);
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
extern unsigned short D_8018C61C[];
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
extern void (*D_8018C62C[])(void);
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
extern int D_801B84D0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018C654[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018C634;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018C644;
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
extern void (*D_8018C694[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018C69C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018C668;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018C6A8[])(void);
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
extern u8 D_8018C678;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B84D8;
extern s32 D_801B84E4;
extern s32 D_801B84E8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018C6E4[])(s32 *);
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
extern s32 D_8018C6B8[];
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
extern s32 D_801B84E0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018C934[])(void);
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
extern char D_8018C754[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018C9D8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018CB2C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018C948;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018CB34[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018C958;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018C978;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018CB3C[])(void);
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
extern void (*D_8018CB64[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018CB70[])(void);
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
extern void (*D_8018C9E4[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018CC14;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018BCF8[];
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
extern unsigned char D_8018CC28[];
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
extern s8 D_8018CC64[];
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
extern u16 D_8018CCAC;
extern u16 D_8018CCAE;
extern u16 D_8018CCB0;
extern s32 D_8018CCB4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018CCBC;
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
extern int D_8018C9C8;
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
extern unsigned int D_8018CD40[];
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
extern void (*D_8018CDF0[])(void);
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
extern u16 D_8018CE20[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018CE84;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B84F0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018CEA8[])(void);
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
extern int D_801B8548[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018CEF0[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018CEE0;
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
extern char D_801B7AA8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018CEF8[])(void);
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
extern void (*D_8018CF4C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018CF14;
extern s16 D_8018CF48;
extern s16 D_8018CF46;
extern s16 D_8018CF44;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018CF58[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B85A8;
extern u8 D_801B85A9;
extern u8 D_801B85AA;
extern u8 D_801B85AB;
extern u8 D_801B85AC;
extern u8 D_801B85AD;
extern u8 D_801B85AE;
extern u8 D_801B85AF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018CF68[])(void);
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
extern s32 D_801B85E8;
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
extern void (*D_8018CFAC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D028[];
extern s32 D_8018D048[];
extern u8 D_8018D0C4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D0E4[];
extern u8 D_8018D104[];
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
extern void (*D_8018D1A0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018D21C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B7AB8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018D228[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018D230[])(void);
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
extern void (*D_8018D2F8[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018D308[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018D318[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018D324[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018D284[];
extern u8   D_8018D298[];
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
extern void (*D_8018D33C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018D344[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018D34C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018D354[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018D35C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018D364[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018D36C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018D420[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018D428[])(void);
extern void func_80169F00(void *a0);
extern char D_8018D3D8[];
extern char D_8018D398[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018D460[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018D46C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018D4B4[])(void);
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
extern void (*D_8018D530[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B8908;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018D524[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018D568[];
extern unsigned short D_8018D570[];
extern unsigned short D_8018D578[];
extern unsigned char D_801B8910[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B8908;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018D580[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B8A44;
extern M2C_UNK D_801B8A48;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B89D0;
extern void (*D_8018D5B0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B8A4C[];
extern u8 D_801B8A54[];
extern u8 D_801B8A04[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018D5B8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018D5D4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018D5DC[])(void);
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
extern void (*D_8018D644[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018D5E8;
extern u8 D_8018D5F4;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018D678[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018D680[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018D6D4[])(void);
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
extern u16 D_8018D708[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018D6F8[];
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
extern s32 D_8018D724;
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
extern void (*D_8018D79C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018D7A4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018D7AC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018D7B4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018D7BC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018D7C4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018D7D0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018D7DC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018D7E8[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018D7F8[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018D808[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018D810[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018D818[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018D820[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018D828[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018D830[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018D838[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018D840[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018D848[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018D850[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018D858[])(void);
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
extern void (*D_8018D860[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018D868[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018D870[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018D878[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018D880[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018D888[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018D890[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018D898[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018D8A0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018D8A8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018D8B0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018D8B8[])(void);
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
extern void (*D_8018D8FC[])(void);
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
extern M2C_UNK D_8018D8C0;
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
extern void (*D_8018D92C[])(void);
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
extern void (*D_8018D968[])(void);
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
extern void (*D_8018D9C0[])();
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
extern void (*D_8018D9D0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018D9D8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018DB40[])();
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
extern void (*D_8018DB4C[])();
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
extern M2C_UNK D_801B7D00;
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
extern s16 D_801BCCA8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B9188;
extern short D_801BCD1C;
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
extern s32 D_801B95B4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B95DC;
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
extern s16 D_801B9598;
extern s32 func_8017A3B0(void);
extern short D_801B95D4;
extern short D_801B95D0;
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
extern s16 D_801B959C;
extern u16 D_801B961C;
extern u16 D_801B961E;
extern u16 D_801B9620;
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
extern s16 D_801B9614;
extern s16 D_801B9616;
extern s16 D_801B9618;
extern s16 D_801B960C;
extern s16 D_801B960E;
extern s16 D_801B9610;
extern void func_8017B7A8(void);
extern s16 D_801B962C;
extern s16 D_801B962E;
extern s16 D_801B9630;
extern s16 D_801B9634;
extern s16 D_801B9636;
extern s16 D_801B9638;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B9624;
extern short D_801B9626;
extern short D_801B9628;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B95BC;
extern SV4 D_801B95C4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B95E4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B95E0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018DD28[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018DD88[])(void);
extern void func_8017C114(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017C8D0 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
 * Outer loop: per-part bbox -> RTPT/RTPS projection -> g.otz + screen cull.
 * Inner loop: per-prim RTPT -> g.flag/nclip/g.opz cull -> switch(code&7):
 *   4,5=POLY_F3 / 6,7=POLY_FT3 / 0,1=POLY_F4 / 2,3=POLY_FT4 -> OT insert.
 * GTE ops are verbatim PsyQ inline_c.h macro bodies (rtps/rtpt/nclip spelled via
 * the project gas macros from include/gte_macros.inc, pulled in by common.h).*
 * CLOSED 2026-07-13 (Phase 26 session 8, Fable5 Max): match_one MATCH 952/952, PIN-FREE.
 * The close=2 residual (two transposed preheader addius) was a global.c allocno-priority TIE:
 *   pseudo 228 = &g.sz1 (sp+0xD0): refs 13, live_length 783 -> pri int(3*13*10000/783) = 498
 *   pseudo 230 = &g.sz2 (sp+0xD4): refs 13, live_length 782 -> pri int(3*13*10000/782) = 498
 * Tie -> creation-order tie-break -> sz1 allocated first (t8) = swapped. The shipped workaround
 * permuted the stsz3 operand list (creation sz0,sz2,sz1) which fixed allocation but transposed
 * the preheader emission (close=2). TRUE FIX: natural operand order restored (emission correct)
 * + ONE zero-byte `__asm__ volatile ("")` inside the common live range (between two existing GTE
 * volatile asms, so no new cse/sched barrier) -> L 784/783 -> pri 497 vs 498 -> the tie SPLITS
 * toward the shorter-lived allocno (sz2) -> sz2 first -> t8. All 10 grants cascade. The slider
 * emits nothing (#APP/#NO_APP only); the tie can ONLY split toward the target's allocation
 * because the later-defined pseudo always has the shorter range. Cookbook §47.
 */

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

void func_8017C8D0(s32 arg0)
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
                                            if (code != 4) g.opz = za + 0x200;
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
                                            if (code == 7) g.opz = za + 0x200;
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
                                                if (code == 3) g.opz = za + 0x200;
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



extern void (*D_8018DD90[])(void);

void func_8017D7B0(void *a0) {
    D_8018DD90[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 rand(void);

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} SubRec_801EB5C8_8017D7EC; /* 0x1C */

typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017D7EC subs[16];
} GroupRec_801EB5C8_8017D7EC; /* 0x1D0 */


void func_8017D7EC(s32 param_1)
{

    extern GroupRec_801EB5C8_8017D7EC D_801B9708[8];
    s32 i, j;
    GroupRec_801EB5C8_8017D7EC *grp;
    SubRec_801EB5C8_8017D7EC *sub;

    for (i = 0; i < 8; i++) {
        grp = &D_801B9708[i];
        grp->g0 = 0;
        grp->g2 = i << 9;
        grp->gC = (rand() & 0xF) << 16;
        grp->g4 = ((rand() & 0xF) << 15) + 0x10000;
        grp->g8 = ((rand() & 0xF) << 12) + 0x8000;

        for (j = 0; j < 16; j++) {
            sub = &grp->subs[j];
            sub->f0 = 0;
            sub->f2 = (rand() & 3) + 4;
            sub->f8 = (j << 8) + (rand() & 0xF) * 56;
            sub->fA = (rand() & 0xF) << 8;
            sub->f14 = (rand() & 0xF) << 13;
            sub->fC = ((rand() & 0xF) << 14) + 0x10000;
            sub->f10 = ((rand() & 0xF) << 12) + 0x8000;
            sub->f4 = 0x200;
            sub->f6 = (rand() & 0xF) << 4;
            sub->f18 = ((rand() & 3) << 5) + 0x40;
        }
    }

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017D994);


extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_8012EFB8(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80017DC4(void *a0, void *a1);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016ED4(void *a0);




void func_8017DB28(s32 a0, s32 a1) {

    extern SVECTOR_8017F40C_8017DB28 D_8018DD98[4];
    Prim_8017F40C_8017DB28 prim;
    u8 matBuf[0x20];
    SVECTOR_8017F40C_8017DB28 vecB;
    SVECTOR_8017F40C_8017DB28 angBuf;
    SVECTOR_8017F40C_8017DB28 sinOut;
    SVECTOR_8017F40C_8017DB28 sv1, sv2, sv3, sv4;
    u32 mask;
    s32 rowPtr;
    SVECTOR_8017F40C_8017DB28 *ap;
    void *mp;
    SVECTOR_8017F40C_8017DB28 *dv;

    func_80015978(a0 + 4, (s32 *)&vecB);
    angBuf.vx = 0;
    angBuf.vy = 0;
    angBuf.vz = *(u16 *)(a1 + 0xe);
    func_800139C8((s32) *(s16 *)(a1 + 2), &angBuf, &angBuf);
    mask = ((u32(*)(void *, void *))func_8012EFB8)(&vecB, &vecB);
    if ((mask & 0xffffefff) == 0) {
        Prim_8017F40C_8017DB28 *pp = &prim;
        s32 off;
        s32 cnt;
        cnt = 0;
        ap = &angBuf;
        mp = matBuf;
        dv = D_8018DD98;
        off = 0x10;
        pp->v[0].vz = 3;
        pp->code = 0x12;
        pp->tag = 0x50000000;
        pp->k30 = 0x870;
        pp->k32 = 0x1a8;
        pp->k34 = 0x88f;
        pp->k36 = 0x1a8;
        pp->k38 = 0x870;
        pp->k3a = 0x1c7;
        pp->k3c = 0x88f;
        pp->k3e = 0x1c7;
        vecB.vx = vecB.vx + angBuf.vx;
        vecB.vy = vecB.vy + angBuf.vy;
        vecB.vz = vecB.vz + angBuf.vz;
        do {
            rowPtr = a1 + off;
            {
                u32 c = *(u32 *)(rowPtr + 0x18);
                pp->bcast = c | ((c << 0x10) | (c << 8));
            }
            angBuf.vx = angBuf.vy = angBuf.vz = *(u16 *)(rowPtr + 4);
            func_80017DC4(ap, mp);
            angBuf.vx = 0;
            angBuf.vy = 0;
            angBuf.vz = *(u16 *)(rowPtr + 0xa);
            func_80017E30(ap, mp);
            ApplyMatrixSV(mp, &dv[0], &sv1);
            ApplyMatrixSV(mp, &dv[1], &sv2);
            ApplyMatrixSV(mp, &dv[2], &sv3);
            ApplyMatrixSV(mp, &dv[3], &sv4);
            angBuf.vx = 0;
            angBuf.vy = 0;
            angBuf.vz = *(u16 *)(rowPtr + 0x16);
            func_800139C8((s32) *(s16 *)(rowPtr + 8), ap, &sinOut);
            sinOut.vx = sinOut.vx + vecB.vx;
            sinOut.vz = sinOut.vz + vecB.vy;
            pp->v[0].vx = sinOut.vx + sv1.vx;
            pp->v[0].vy = sinOut.vz + sv1.vy;
            pp->v[1].vx = sinOut.vx + sv2.vx;
            pp->v[1].vy = sinOut.vz + sv2.vy;
            pp->v[2].vx = sinOut.vx + sv3.vx;
            off = off + 0x1c;
            pp->v[2].vy = sinOut.vz + sv3.vy;
            cnt = cnt + 1;
            pp->v[3].vx = sinOut.vx + sv4.vx;
            pp->v[3].vy = sinOut.vz + sv4.vy;
            func_80016ED4(pp);
        } while (cnt < 0x10);
    }
}



extern void func_801890C8(s32);

void func_8017DDE0(void) {

    extern const void D_8018F71C;
    extern const void D_8018F7F8;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = (u8 *)&D_8018F71C;
    D_801274CC = (void *)&D_8018F7F8;
    ((int (*)(int))func_801890C8)(0);
}



extern void (*D_8018DE2C[])(void);

void func_8017DE20(void *a0) {
    D_8018DE2C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E00C(void);
extern void func_800167B8(s32 a0);

s32 func_8017DE5C(s32 a0) {
    func_8017E00C();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017DEA0(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018DE34[])(void);

void func_8017DEC4(void *a0) {
    D_8018DE34[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E034(void);

s32 func_8017DF00(s32 a0) {
    func_8017E034();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017DF40(s32 a0) {
    s32 t;
    s32 r = func_80029504();

    t = *(s32 *)(a0 + 0x28) - 1;
    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        if (r == 0x258 && !(func_80029178(0x132) & 0xFF)) {
            func_80029124(0x132, 1);
            func_800D0C48(1);
        }
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017DFEC(void) {
        func_800D1EBC();
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E00C(void) {

    extern s32 D_8018DE40(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018DE40, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E034(void) {

    extern s32 D_8018DE54(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018DE54, 0x1000000);
}


extern s32 func_80147054(void*);
extern void func_80171928(void*);
void func_8017E05C(s32 a0) {
    ((void (*)(void))func_80147054)();
    ((void (*)(s32))func_80171928)(a0);
}


void func_8017E08C(void) {
    extern s32 D_80126954;
    extern s32 D_80126950;
    extern s32 D_8012695C;
    extern s16 D_8012696A;
    extern s16 D_80126968;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s32 D_801BA588;
    extern u8 D_80126948[];
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8012A094(s32 a);
    extern void func_8017E134(void *a0);
    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x320;
    D_8012696A = 0x800;
    D_801BA588 = 0;
    D_80126968 = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0xB0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E134, 0);
    func_8012A094((s32)D_80126948);
    func_8017E134(D_80126948);
}



extern void (*D_8018DE58[])(void);

void func_8017E134(void *a0) {
    D_8018DE58[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017E170(s32 a0) {

    extern s32 D_801BA588;
    D_801BA588 = a0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017E180);


// @class: schedule
// @stuck: none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017E33C(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void D_8018DE68(void);

s32 func_8017E4D4(s32 arg0, s16 *arg1, s32 arg2)
{
    u8 *p;
    u8 *q;

    p = func_8012913C(0x39);
    if (p == NULL) {
        return 0;
    }
    q = *(u8 **)(p + 0x20);
    *(s16 *)(q + 0x2) = 2;
    *(void (**)(void))(q + 0x20) = D_8018DE68;
    *(u8 *)(q + 0x27) = 0x74;
    *(s16 *)(q + 0x28) = 0x3C5;
    *(s16 *)(q + 0x2A) = 0x1E0;
    *(u32 *)(q + 0x4) |= 0xC000040;
    *(u32 *)(q + 0x34) = *(u32 *)(arg0 + 0x20) + 0x34;
    *(s16 *)(q + 0x2E) = arg1[0];
    *(s16 *)(q + 0x30) = arg1[1];
    *(s16 *)(q + 0x32) = arg1[2];
    if (arg2 != 0) {
        *(s16 *)(q + 0x1A) = 0x800;
        *(s16 *)(q + 0x18) = 0x800;
    } else {
        *(s16 *)(q + 0x18) = -0x800;
        *(s16 *)(q + 0x1A) = 0x800;
    }
    *(s32 *)(p + 0x2C) = arg0;
    return (s32)p;
}


extern u8 D_8018DE5C;
extern u8 D_8018DE80;

s32 func_8017E5C8(s32 param_1) {
    s32 s1, s0;
    s32 r, q;
    s16 sv;

    s1 = (s32)func_801290DC(0x38, (u8 *)param_1);
    if (s1 == 0) {
        return 0;
    }
    s0 = *(s32 *)(s1 + 0x20);
    *(s32 *)(s0 + 0x20) = (s32)&D_8018DE5C;
    *(u8 *)(s0 + 0x27) = 0x66;
    r = rand();
    q = r;
    if (r < 0) {
        q = r + 0xFFF;
    }
    sv = (s16)(r + (q >> 0xC) * -0x1000 + 0x800);
    *(s16 *)(s0 + 0x1A) = sv;
    *(s16 *)(s0 + 0x18) = sv;
    *(s32 *)(s0 + 4) |= 0x50000000;
    func_80128EA8(s0, s1 + 0x24, (s32)&D_8018DE80);
    *(s32 *)(s1 + 0x14) = 0xFFF80000;
    return s1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(void);
extern void func_8012931C(void *);

void func_8017E67C(s32 a0) {
    s32 s0 = a0;
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(s0 + 0x20), (void *)(s0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(s0);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017E6C0);


extern void (*D_8018DED0[])(void);

void func_8017E758(void *a0) {
    D_8018DED0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E794(void *a0) {
    extern s32 func_8017EBA8();
    extern void (*D_8018E048[])(void *);
    if (func_8017EBA8(a0) == 0) {
        D_8018E048[*(u16 *)((s32)a0 + 0x2)](a0);
    }
}


#include "common.h"

/* func_8017E7E8 @ 0x8017E7E8  (ov_SC03_105, 143 ins)  -- MATCH
 *
 * Spawns an effect/sprite object (func_8012C1B8), attaches it at owner+0x20 and
 * branches on the owner's 0x70 flag word:
 *    bit 15 set   -> "dying/hit" variant (anim DF38/DFE0, state 2, 0x2000 scale)
 *    low nibble   -> "active" variant  (anim DED8/DF98, random 0..8 +8 at 0xFE,
 *                    a world-space offset vector fed through func_8012B77C)
 *    otherwise    -> "idle" variant    (anim DF38/DFE0, 0xC000 at 0x48)
 *
 * Notes for the banker:
 *  - 0x70 is read with two SEPARATE `*(s16 *)(a0+0x70)` expressions: cse turns the
 *    second into a reg-reg copy IN bb0, which is exactly the target's
 *    `lh $v0 / addu $v1,$v0,$zero / andi $v0,0x8000 / ... / andi $v0,$v1,0xF`.
 *    A single cached local loses that copy (142 ins).
 *  - sp20 must be a SCALAR s32 (its 8-byte stride is what makes the frame 0x40);
 *    `s32 sp20[3]` pushes the frame to 0x48 with the same instruction stream.
 *  - the 0x58 store must be ONE expression with explicit left-assoc parens; a
 *    3-statement local-variable version schedules the %hi/%lo pair to the top of
 *    the block and eats the load-delay nop after `lw $v1,0x20($s0)`.
 */

/* ---- callees: TU spellings where the TU already has one, fleet-modal otherwise ---- */
extern void func_8012C1B8(void);              /* TU:4202 (return taken via a cast, TU house style) */
extern void func_8012CAE4(void *a0);          /* TU:4203 */
extern void func_8012B2CC(s32 a0);            /* TU:2535 */
extern s32  rand(void);                       /* TU:958 / TU:3187 */
extern void func_8001CA1C(s32 a0, s32 a1);            /* fleet modal x1069 */
extern void func_8012A828(s32 a0, void *a1);          /* fleet modal x2791 */
extern void func_8012B178(s32 a0, s32 a1);            /* fleet modal x1749 */
extern s32  func_8012B77C(s32 out, s32 from, s32 to); /* fleet modal x83+ */

/* ---- data ---- */
extern u8  D_80126B5C;      /* TU:362 -- scalar u8, s32 view at the use site (camera X) */
extern s32 D_80126B64;      /* project-canonical decl (camera Z)                        */
extern u8  D_8018DED8[];
extern u8  D_8018DF38[];
extern u8  D_8018DF98[];
extern u8  D_8018DFE0[];
extern s32 D_8018E028;      /* address-only: OR'd with 0x60000000 into owner+0x58 */
extern s32 D_8018E054[];    /* 16-entry X-offset table indexed by (0x70 & 0xF)    */

void func_8017E7E8(s32 a0) {
    s32 sp10[3];   /* world-space "to" vector handed to func_8012B77C */
    s32 sp20;      /* func_8012B77C output (packed angle pair)        */
    s32 obj;
    s32 r;
    s32 v;
    s32 w;

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    *(s32 *)(a0 + 0x20) = obj;              /* delay-slot store => dominates the test (§194-M) */
    if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
        if (*(s16 *)(a0 + 0x70) & 0xF) {
            func_8001CA1C(obj, (s32)D_8018DED8);
            func_8012A828(a0, D_8018DF98);

            r = rand();
            *(s32 *)(a0 + 0x1C) = 8;
            *(s16 *)(a0 + 0xFE) = r % 9 + 8;    /* magic 0x38E38E39 => signed /9 */

            sp10[0] = *(s32 *)&D_80126B5C
                    + D_8018E054[*(u16 *)(a0 + 0x70) & 0xF];    /* X */
            sp10[1] = 0xFEFE0000;                               /* Y (16.16)     */
            sp10[2] = D_80126B64;                               /* Z             */
            *(u16 *)((s32)sp10 + 0x6) -= 0x40;                  /* Y integer half */

            func_8012B77C((s32)&sp20, a0 + 4, (s32)sp10);

            v = sp20;
            /* the sh kills the cse of *(s32*)(a0+0x20), so it is re-loaded (§193-E) */
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = v;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = v >> 16;
            func_8012B2CC(a0);
            func_8012B178(a0, *(s32 *)(a0 + 0xDC));
        } else {
            func_8001CA1C(obj, (s32)D_8018DF38);
            func_8012A828(a0, D_8018DFE0);
            *(s32 *)(a0 + 0x48) = 0xC000;
            *(s16 *)(a0 + 0xAE) = -1;
        }
        /* shared TAIL written once above the join -- cross_jump merges suffixes only
         * (law 10 / §193-C); duplicating it into both arms costs the `li 0x1800` twice */
        *(s16 *)(obj + 0x1A) = 0x1800;
        *(s16 *)(obj + 0x18) = 0x1800;
        *(u16 *)(a0 + 0x2) += 1;
    } else {
        func_8001CA1C(obj, (s32)D_8018DF38);
        func_8012A828(a0, D_8018DFE0);
        w = *(s32 *)(a0 + 0xDC);
        *(s16 *)(a0 + 0x2)   = 2;
        *(s16 *)(a0 + 0xAE)  = -1;
        *(s16 *)(a0 + 0x100) = w;
        *(s16 *)(obj + 0x1A) = 0x2000;
        *(s16 *)(obj + 0x18) = 0x2000;
    }

    *(s32 *)(obj + 0x4) |= 0x50000000;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
    /* two separate `or`s: the ADDR_EXPR is not an INTEGER_CST so fold never
     * associates 0x20000000|0x40000000 into a single lui 0x6000 */
    *(s32 *)(a0 + 0x58) = ((s32)&D_8018E028 | 0x20000000) | 0x40000000;
    *(u16 *)(a0 + 0x5C) |= 0x8000;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017EA24);

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_80126B96;
extern void (*D_8018E038[])(void);

void func_8017EB08(s32 param_1) {
    s32 sp10[2];
    s32 ang;
    s32 t;

    ang = *(u16 *)(param_1 + 0x100) + 0x40;
    *(u16 *)(param_1 + 0x100) = ang;
    func_8012B0B4((unsigned int *)sp10, (s16)ang, *(s16 *)(param_1 + 0xFC));
    t = sp10[0];
    *(s16 *)(param_1 + 6) = *(u16 *)(param_1 + 0x88) + t;
    *(s16 *)(param_1 + 0xE) = *(u16 *)(param_1 + 0x8C) + (t >> 16);
    if (func_8012D5E4(param_1, (s32)D_8018E038, (s32)D_8018E038 + 8, 10) == 1) {
        u16 *flagp = &D_80126B96;
        *flagp |= 0x4200;
    }
}


extern void func_8017F140(s32);

s32 func_8017EBA8(void *a0) {
    if (!(*(u16 *)(a0 + 0x5C) & 1)) {
        return 0;
    }
    if (*(u16 *)(a0 + 0x5E) != 0x24) {
        ((void (*)(void))func_8017F140)();
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017EBF8);


extern void (*D_8018E12C[])(void);

void func_8017EC5C(void *a0) {
    D_8018E12C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8017F0C8(s32 a0, s32 a1);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32  D_80126B64;
extern u8   D_8018E064[];
extern u8   D_8018E0C4[];
extern u8   D_8018E10C[];
extern u8   D_8018E11C[];

void func_8017EC98(void *a0) {
    s32 sp10[3];
    s16 sp20[3];
    s32 sp28[3];
    s32 sp38[8];
    s32 sp58;
    s32 obj;

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    *(s32 *)(a0 + 0x20) = obj;
    func_8001CA1C(obj, (s32)D_8018E064);
    func_8012A828((s32)a0, D_8018E0C4);

    *(s16 *)(obj + 0x18) = (*(s16 *)(a0 + 0xFC) < 0) ? 0x3000 : -0x3000;
    *(s16 *)(obj + 0x1A) = *(s32 *)(a0 + 0xDC);
    *(s32 *)(obj + 0x4) |= 0x50000000;
    *(u16 *)(obj + 0x2C) |= 0x10;
    *(u16 *)(a0 + 0x5C) = 0x8000;
    *(s16 *)(a0 + 0xAE) = -1;
    if (*(u16 *)(a0 + 0x70) & 1) {
        func_8017F0C8((s32)a0, 0xFFF40000);
        *(u16 *)(a0 + 0x34) += 1;
    } else {
        sp10[0] = *(s32 *)(a0 + 0x4);
        sp10[1] = 0xFEFE0000;
        sp10[2] = D_80126B64;
        func_8012B77C((s32)&sp58, (s32)(a0 + 4), (s32)sp10);

        sp20[2] = 0;
        sp28[1] = 0;
        sp28[0] = 0;
        sp28[2] = -0x8000;
        sp20[0] = sp58;
        sp20[1] = sp58 >> 16;
        func_80049CAC((s32)sp20, (s32)sp38);
        func_800484EC((s32)sp38, (s32)sp28, (s32)(a0 + 0x44));
    }

    if (*(s16 *)(a0 + 0xFC) < 0) {
        *(s32 *)(a0 + 0x58) = (((s32)D_8018E10C | 0x40000000) | 0x20000000);
    } else {
        *(s32 *)(a0 + 0x58) = (((s32)D_8018E11C | 0x40000000) | 0x20000000);
    }
    *(u16 *)(a0 + 0x2) += 1;
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012CBF4(s32 a0);
extern s32 func_8012CBA4(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8017F018(s32 a0);
extern void func_8017F0C8(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

typedef struct {
    u16 f0;
    u16 f1;
    u16 f2;
    u16 f3;
    u16 f4;
    u16 f5;
    u16 f6;
    u16 f7;
    s32 f8;
} Local_8017EE34;

void func_8017EE34(s32 a0) {
    s32 s0 = a0;
    Local_8017EE34 local;
    u16 t6, tA, tE;
    register s32 fc __asm__("$6");
    s32 cnt;
    s32 v0;
    u16 v1;

    if (*(u16 *)(s0 + 0x34) == 0) {
        if ((func_8012CBF4(s0) & 0x2000) != 0) {
            func_8017F0C8(s0, 0xFFF40000);
            t6 = *(u16 *)(s0 + 0x6);
            tA = *(u16 *)(s0 + 0xA);
            tE = *(u16 *)(s0 + 0xE);
            *(s32 *)(s0 + 0x1C) = 4;
            *(s32 *)(s0 + 0xE0) = 3;
            fc = *(s16 *)(s0 + 0xFC);
            cnt = *(u16 *)(s0 + 0x34) + 1;
            *(u16 *)(s0 + 0xFE) = t6;
            *(u16 *)(s0 + 0x100) = tA;
            *(u16 *)(s0 + 0x102) = tE;
            *(u16 *)(s0 + 0x34) = cnt;
            if (fc < 0) {
                func_8002D4C8(0xC07, 0);
            }
        }
    } else {
        if (func_8012BEE8(s0) == 1) {
            v0 = *(s32 *)(s0 + 0xE0);
            if (v0 != 0) {
                v0 = v0 - 1;
                v1 = *(u16 *)(s0 + 0xFE);
                *(s32 *)(s0 + 0xE0) = v0;
                *(s32 *)(s0 + 0x1C) = 3;
                local.f0 = v1;
                local.f1 = *(u16 *)(s0 + 0x100);
                local.f2 = *(u16 *)(s0 + 0x102);
                local.f3 = 0x171;
                local.f4 = 1;
                local.f5 = 0;
                local.f6 = 0x7FFF;
                local.f7 = *(u16 *)(s0 + 0xFC);
                local.f8 = (*(s32 *)(s0 + 0xE0) << 11) + 0x1000;
                func_8012C51C(&local, s0);
            }
        }
        if ((func_8012CBA4(s0) & 0x8000) != 0) {
            *(s32 *)(s0 + 0x1C) = 0x10;
            *(u16 *)(s0 + 0x34) = 0;
            *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
            return;
        }
    }
    func_8017F018(s0);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8017EF94(s32 a0)
{
    s32 v1;
    u16 v0;

    if (*(u16 *)(a0 + 0x34) == 0) {
        v1 = *(s32 *)(a0 + 0x20);
        v0 = *(u16 *)(v1 + 0x1A);
        *(u16 *)(v1 + 0x1A) = v0 + 0x300;
        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x10;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_8012C218((void *)a0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017F018);

void func_8017F0C8(s32 a0, s32 a1) {
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(a0 + 0xFC);
    func_8012B2CC(a0);
    func_8012B23C(a0);
    func_8012B178(a0, a1);
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x10) / 0x18;
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 rand(void);

void func_8017F140(s32 a0) {
    s32 s1;
    s32 v0;

    s1 = func_80132EF4(a0, 0x22);
    if (s1 != 0) {
        *(u16 *)(s1 + 0x34) = ((rand() % 3 << 12) + 0x2000) | 2;
        *(s32 *)(s1 + 0x14) = 0xFFFE0000 - ((rand() % 3) << 16);
    }
    func_8012C218((void *)a0);
}



extern void (*D_8018E258[])(void);

void func_8017F1F8(void *a0) {
    D_8018E258[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017F234);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017F55C);

void func_8017F864(void) {
}

void func_8017F86C(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017F874(s32 a0) {
    s32 s0 = a0;

    if (*(u16 *)(s0 + 0x34) != 0) {
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 2) = 5;
            *(s32 *)(s0 + 0x48) = 0x2000;
            *(s32 *)(s0 + 0x1C) = 0x40;
            func_8002D4C8(0x770, 0);
        }
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

/* a0-bit-3 gate: every 8th tick, spawn 2 particles (func_80132EF4(a0, 0x4D))
 * and randomise them.
 *
 * NOTE (S54 second pass, §195): oldA/oldB MUST be two distinct locals, one per
 * field, even though a single reused `old` is semantically identical.  sched.c's
 * adjust_priority() only grants the birthing-insn priority bump to an insn whose
 * destination pseudo has reg_n_sets == 1 (birthing_insn_p, sched.c:2490).  A
 * shared `old` is set twice, so the `lh` never gets bumped at sched1, is picked
 * last in that block, and lands right after the `mult` -- which gives it a LOWER
 * luid than the `sra $v1,$v0,31` at sched2 and loses the sched2 tie between them.
 * Field 0xE only survived the same bug because its block also holds field 0x6's
 * `sh`, and that second memory-unit insn makes potential_hazard() (sched.c:1344,
 * unit_n_insns) break the tie the other way.  Splitting the local restores the
 * bump and both blocks emit `sra` before `lh`, as the target does.
 */
void func_8017F8D8(s32 a0) {
    s32 i;
    s32 s2;

    func_8012AD80(a0);
    if ((*(s32 *)(a0 + 0x1C) & 7) == 0) {
        for (i = 0; i < 2; i++) {
            s2 = func_80132EF4(a0, 0x4D);
            if (s2 != 0) {
                s32 oldA;
                s32 oldB;
                s32 t;
                s32 v;
                s32 r5;
                s32 tmp;
                s32 p20;

                /* field 0x6: += rand()%96 with a random sign */
                t = rand() % 96;
                oldA = *(s16 *)(s2 + 0x6);
                if (rand() & 1) {
                    v = oldA + t;
                } else {
                    v = oldA - t;
                }
                *(s16 *)(s2 + 0x6) = v;

                /* field 0xE: same idiom */
                t = rand() % 96;
                oldB = *(s16 *)(s2 + 0xE);
                if (rand() & 1) {
                    v = oldB + t;
                } else {
                    v = oldB - t;
                }
                *(s16 *)(s2 + 0xE) = v;

                *(u16 *)(s2 + 0xA) = *(u16 *)(s2 + 0xA) - 0x40;
                *(s32 *)(s2 + 0x14) = -0x60000;         /* -6.0 in 16.16 */

                /* sub-object at 0x20: fields 0x18/0x1A get (rand()%4 + 4) << 12 */
                r5 = rand();
                p20 = *(s32 *)(s2 + 0x20);
                tmp = ((r5 % 4) + 4) << 12;
                *(s16 *)(p20 + 0x1A) = tmp;
                *(s16 *)(p20 + 0x18) = tmp;

                *(s32 *)(s2 + 0x1C) = rand() % 5;
            }
        }
    }
    if (func_8012BEE8(a0) != 0) {
        func_8002D4C8(4, 0x770);
        func_8012C218((void *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FA90);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FAE8);


extern void (*D_8018E270[])(void);

void func_8017FBAC(void *a0) {
    D_8018E270[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80128EA8(s32, s32, s32);
extern u8 D_800D387C[];
extern u8 D_800D3888[];

void func_8017FBE8(void *arg0) {
    void *work;

    work = *(void **)((s8 *)arg0 + 0x20);
    *(u32 *)((s8 *)work + 0x20) = (u32)&D_800D387C;
    *(u8 *)((s8 *)work + 0x27) = 0x9C;
    *(u32 *)((s8 *)work + 0x4) |= 0x50000000;
    func_80128EA8((s32)work, (s32)arg0 + 0x24, (s32)D_800D3888);
    *(u16 *)((s8 *)arg0 + 0x2) += 1;
    if (*(s32 *)((s8 *)arg0 + 0x1C) != 0) {
        *(u32 *)((s8 *)work + 0x4) |= 0x80000000;
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FC74);


extern void (*D_8018E278[])(void);

void func_8017FCF0(void *a0) {
    D_8018E278[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FD2C);

#include "common.h"

extern void func_8012C218(void *a0);
extern s32 func_80134510(s32 arg);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern u8 D_801152A8[];
extern s32 func_8017FEA8(void *a0);

void func_8017FDB8(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x64);
    s16 sp[3];

    if (*(s16 *)(v0 + 0x36) != *(s16 *)(a0 + 0xFE)) {
        func_8012C218((void *)a0);
        return;
    }

    sp[0] = *(u16 *)(v0 + 6);
    sp[1] = *(u16 *)(v0 + 0xA) - 0x10;
    sp[2] = *(u16 *)(v0 + 0xE);
    if (func_80134510((s32)&sp[0]) == 0) {
        return;
    }

    *(s16 *)(a0 + 6) = sp[0];
    *(s16 *)(a0 + 0xA) = sp[1];
    *(s16 *)(a0 + 0xE) = sp[2];

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA);
    func_8017FEA8((void *)a0);
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FEA8);


extern void (*D_8018E280[])(void);

void func_8017FF54(void *a0) {
    D_8018E280[*(u16 *)((s32)a0 + 0x2)]();
}




void func_8017FF90(s32 arg0) {
    extern Rec12 D_8018DE74[];
    s32 v1;

    v1 = *(s32 *)(arg0 + 0x20);
    *(Rec12 **)(v1 + 0x20) = D_8018DE74;
    *(u8 *)(v1 + 0x27) = 0x6D;
    *(u16 *)(v1 + 0x28) = 0x3CD;
    *(u16 *)(v1 + 0x2A) = 0x1A0;
    *(u16 *)(v1 + 0x1A) = 0x1800;
    *(u16 *)(v1 + 0x18) = 0x1800;
    *(u16 *)(v1 + 0x2C) = 0xC010;
    *(u32 *)(arg0 + 0x14) = 0x80000;
    *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    *(u32 *)(arg0 + 0x1C) = 0x40;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8017FFEC);


#include "common.h"

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern char D_8018D3D8[];
extern char D_8018D398[];

void func_80180030(s32 arg0)
{
    s32 temp;

    temp = *(s32 *)(arg0 + 0x20);
    *(s32 *)(temp + 0x20) = (s32)D_8018D3D8;
    *(u8 *)(temp + 0x27) = 0x16;
    *(u16 *)(temp + 0x1A) = 0x6000;
    *(u16 *)(temp + 0x18) = 0x6000;
    *(u8 *)(temp + 0x26) = 0x60;
    *(u8 *)(temp + 0x25) = 0x60;
    *(u8 *)(temp + 0x24) = 0x60;
    *(s32 *)(temp + 4) |= 0x50000000;
    func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)D_8018D398);
    *(u16 *)(arg0 + 2) += 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(void);
void func_801800C0(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}


#include "common.h"

extern void (*D_8018E7E8[])(void);
extern s32 func_8004787C(s32 a0);
extern void func_80183F84(void *a0, void *a1);
extern s16 D_8018EE04;
extern s16 D_8018EE06;
extern s16 D_8018EE08;
extern s32 D_801BA6A8;
extern s32 D_801BA6AC;

void func_80180100(void *a0)
{
    void *s0 = a0;

    D_8018E7E8[*(u16 *)((s32)s0 + 0x2)]();

    if (*(u16 *)s0 != 0) {
        s32 v0;
        s32 v1;
        s32 pad[2]; /* dead local: reserves the target's 8 extra frame bytes, §162i1/§164-05 */
        (void)pad;

        v0 = *(u16 *)((s32)s0 + 0x5C);
        v1 = *(s16 *)((s32)s0 + 0xAC);
        v0 &= 0xFFFE;
        *(u16 *)((s32)s0 + 0x5C) = v0;
        __asm__ __volatile__("");

        if (v1 != 0) {
            v0 = v1;
            __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
            v0 = v0 - 1;
            *(s16 *)((s32)s0 + 0xAC) = v0;
            v0 = func_8004787C((s16)v0 << 8);
            v1 = (v0 * 3 << 6) >> 12;
            v1 += 0x40;
            D_8018EE04 = v1;
            D_8018EE08 = -0x40;
            D_8018EE06 = -0x40;
        } else {
            D_8018EE08 = 0x80;
            D_8018EE06 = 0x80;
            D_8018EE04 = 0x80;
        }

        func_80183F84(s0, (void *)D_801BA6A8);
        func_80183F84(s0, (void *)D_801BA6AC);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801801F8);

extern void func_801824CC(s32, s32, s32, s32, s32);

void func_801802B0(s32 a0) {
    func_801824CC(a0, 0x1000, 0, -0x20, 0x800000);
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801802E0);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801803A0);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801806F8);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80180ABC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80180EC0);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801813BC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801818E8);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80181C84);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80182220);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018226C);

void func_80182334(void) {
}

#include "common.h"

extern void func_8012E9C0(s32 a0);
extern s16 D_8018EDFC;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

s32 func_8018233C(s32 arg0) {
    s16 flags;
    s32 spawn;
    s32 target;
    s16 *p;

    flags = *(u16 *)(arg0 + 0x5C);
    if (!(flags & 1)) {
        return 0;
    }
    if (*(u16 *)(arg0 + 0x5E) == 0x22) {
        *(u16 *)(arg0 + 0x5C) = flags & 0xFFFE;
        *(u16 *)(arg0 + 0x5E) = 0;
        return 0;
    }

    p = &D_8018EDFC;
    *(u16 *)(arg0 + 0x60) = 8;
    func_8012E9C0(arg0);
    *p -= *(u16 *)(arg0 + 0x60);

    if (*(s16 *)(arg0 + 0xAC) == 0) {
        *(s16 *)(arg0 + 0xAC) = 8;
    }
    func_8002D4C8(0xC08, 0);

    spawn = func_80132EF4(arg0, 0x22);
    if (spawn != 0) {
        *(u16 *)(spawn + 0x34) = ((rand() % 3 << 12) + 0x4000) | 2;
        *(s32 *)(spawn + 0x14) = 0xFFF80000 - ((rand() % 3) << 16);
        *(u16 *)(spawn + 0x6) = *(u16 *)(arg0 + 0x7C);
        *(u16 *)(spawn + 0xA) = *(u16 *)(arg0 + 0x7E);
        *(u16 *)(spawn + 0xE) = *(u16 *)(arg0 + 0x80);
    }

    if (*p <= 0) {
        *p = 0;
        target = *(s32 *)(arg0 + 0x64);
        *(s16 *)(target + 0x2) = 4;
        *(u16 *)(arg0 + 0x5C) = 0;
        *(s16 *)(arg0 + 0x2) = 0xA;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801824CC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801829CC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80182BD8);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80182DCC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80183174);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801831E0);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801834A4);

extern s32 rand(void);
extern s32 func_801850D8();
extern u8 D_8018E47C[];

void func_8018364C(void *arg0) {
    s16 sp20[3];
    s32 i;
    s32 r;
    s32 ret;

    sp20[2] = 0;
    sp20[0] = 0;
    sp20[1] = -0x120;
    for (i = 0; i < 10; i++) {
        r = rand();
        ret = func_801850D8(6, (s16)(i * 0x200 + 0x3000 + r % 1024), 0, 0, sp20,
                            (s32)arg0, (s32)D_8018E47C, 0);
        if (ret != 0) {
            *(s16 *)(ret + 0x52) = i;
            r = rand();
            *(s16 *)(ret + 0x4C) = r % 8;
        }
    }
}


void func_8018373C(void *a0, s32 a1)
{
    s32 arg[3];

    arg[2] = a1;
    arg[1] = 0;
    arg[0] = 0;
    func_8018383C(a0, arg);
}


void func_80183768(void *a0, s32 a1, s32 a2)
{
    s32 s0a, s0b;
    s32 arg[3];

    s0a = func_80047948((*(s32 *)((u8 *)a0 + 0x1C) << 5) & 0xFE0)
        - func_80047948(((*(s32 *)((u8 *)a0 + 0x1C) - 1) << 5) & 0xFE0);
    arg[0] = (a1 * s0a) << 4;
    arg[2] = 0;
    s0b = func_8004787C((*(s32 *)((u8 *)a0 + 0x1C) << 5) & 0x7E0)
        - func_8004787C(((*(s32 *)((u8 *)a0 + 0x1C) - 1) << 5) & 0x7E0);
    arg[1] = -((a2 * s0b) << 4);
    func_8018383C(a0, arg);
}


extern s32 D_801BA5A0;

void func_8018383C(s32 a0, s32 a1)
{
    s32 buf[8];

    func_80049CAC((s32)&D_801BA5A0, (s32)&buf);
    func_800484EC((s32)&buf, a1, a0 + 0x10);
}


#include "common.h"

/* skeleton-twin: ov_SC01_077:func_8012D664 (banked) — same D_80126B5E/62/66
 * globals-into-locals shape, different callee (AABB test func_8013361C
 * instead of func_800132BC). */

typedef struct {
    s16 a, b, c;
} Vec3s16_8018388C;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 *D_80126B90;
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_8018388C(void *a0, s32 a1) {
    Vec3s16_8018388C s;
    Vec3s16_8018388C s1;
    Vec3s16_8018388C diff;
    s16 *box0;
    s16 *box1;

    box0 = (s16 *)(((s32)D_80126B90 & 0xFFFFFFF) | 0x80000000);
    box1 = (s16 *)((*(s32 *)((u8 *)a0 + 0x58) & 0xFFFFFFF) | 0x80000000);

    s.a = D_80126B5E;
    s.b = D_80126B62;
    s.c = D_80126B66;

    s1.a = *(u16 *)((u8 *)a0 + 0x6);
    s1.b = *(u16 *)((u8 *)a0 + 0xA);
    s1.c = *(u16 *)((u8 *)a0 + 0xE);

    if (func_8013361C(box0, box1, &s, &s1) != 0) {
        diff.a = s.a - s1.a;
        diff.b = s.b - s1.b;
        diff.c = s.c - s1.c;

        VectorNormalSS(&diff, &diff);

        func_8012F568(1, 0x4201, 0, a1, &s1, &diff);

        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801839A4);

s32 func_80183A64(s32 *a0, s32 a1, s32 a2) {
        s32 v1 = a0[0x4 / 4];
        if (a1 < v1) {
            a0[0x4 / 4] = a1;
            return 1;
        }
        if (v1 < a2) {
            a0[0x4 / 4] = a2;
            return 1;
        }
        return 0;
    }


#include "common.h"

extern s32 rand(void);
extern s32 func_80183CA4();
extern s32 func_80183C6C(void *arg0, void *arg1);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s16 D_801152B0;

/* Random-behaviour dispatcher.  func_80183CA4() returns a flag word; bit 0x2000
 * and bit 0x8000 select two mirrored behaviours that differ ONLY in the table
 * passed as arg1 of the first func_80183C6C call (D_801152A8 vs &D_801152B0).
 * Each behaviour: 15/16 of the time run the table lookup, 1/16 of the time
 * nudge field 0xF0 by +-(rand() % 512) around a +0x800 bias.
 *
 * The four zero-byte __asm__ fences are REORG steering, not semantics.  gcc's
 * dbr_schedule (reorg.c fill_eager_delay_slots -> fill_slots_from_thread) will
 * otherwise "steal" the first insn of a branch's target/fall-through thread
 * into the branch's delay slot; the target keeps those two delay slots empty.
 * An ASM_OPERANDS insn is not eligible_for_delay, so a fence at a thread's HEAD
 * blocks the steal.  A fence at a thread's TAIL additionally blocks jump.c
 * cross_jump: find_cross_jump compares ASM_OPERANDS including their source
 * line, so two fences on different lines never match and the merge stops there
 * -- which is why only the SECOND region carries the trailing fence: it keeps
 * the first region's own `addu` alive so fill_simple's backward scan can drop
 * it into that region's `j` delay slot (target 80183B44).
 */
s32 func_80183A98(void *a0) {
    s32 flags;
    s32 s0;
    s32 s1;
    struct {
        s16 x0; /* 0x10(sp) */
        s16 x2; /* 0x12(sp) */
    } local;

    flags = func_80183CA4();
    if (flags & 0x2000) {
        if ((rand() & 0xF) != 0) {
            local.x0 = (s16)(*(s32 *)((u8 *)a0 + 0x10) >> 8);
            local.x2 = (s16)(*(s32 *)((u8 *)a0 + 0x14) >> 8);
            *(s32 *)((u8 *)a0 + 0xF0) =
                func_80183C6C(D_800D3918, D_801152A8) * 2 - func_80183C6C(&local, D_800D3918);
        } else {
            s0 = rand() % 512;
            s1 = *(s32 *)((u8 *)a0 + 0xF0) + 0x800;
            {
                s32 t;
                if ((rand() & 1) == 0) {
                    __asm__ __volatile__("");
                    t = s1 - s0;
                } else {
                    __asm__ __volatile__("");
                    t = s1 + s0;
                }
                *(s32 *)((u8 *)a0 + 0xF0) = t;
            }
        }
    } else if (flags & 0x8000) {
        if ((rand() & 0xF) != 0) {
            local.x0 = (s16)(*(s32 *)((u8 *)a0 + 0x10) >> 8);
            local.x2 = (s16)(*(s32 *)((u8 *)a0 + 0x14) >> 8);
            *(s32 *)((u8 *)a0 + 0xF0) =
                func_80183C6C(D_800D3918, &D_801152B0) * 2 - func_80183C6C(&local, D_800D3918);
        } else {
            s0 = rand() % 512;
            s1 = *(s32 *)((u8 *)a0 + 0xF0) + 0x800;
            {
                s32 t;
                if ((rand() & 1) == 0) {
                    __asm__ __volatile__("");
                    t = s1 - s0;
                } else {
                    __asm__ __volatile__("");
                    t = s1 + s0;
                    __asm__ __volatile__("");
                }
                *(s32 *)((u8 *)a0 + 0xF0) = t;
            }
        }
    } else {
        return 0;
    }
    return 1;
}


void func_80183C20(void *a0) {
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    u16 in[2];
    u16 g[2];

    in[0] = *(u16 *)((u8 *)a0 + 6);
    in[1] = *(u16 *)((u8 *)a0 + 0xA);
    g[0] = D_80126B5E;
    g[1] = D_80126B62;
    func_80183C6C(in, g);
}


extern s32 ratan2(s32 dx, s32 dy);
    s32 func_80183C6C(void * arg0, void * arg1) {
        return ((s32 (*)(s32, s32))ratan2)(
            *(s16 *)((u8 *)arg1 + 0x2) - *(s16 *)((u8 *)arg0 + 0x2),
            *(s16 *)((u8 *)arg1 + 0x0) - *(s16 *)((u8 *)arg0 + 0x0)
        ) - 0x400 & 0xFFF;
    }






extern void func_8012AD80(s32 a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

s32 func_80183CA4(s32 a0) {
    s32 s0 = a0;
    s32 ret;
    s16 sp[7];

    sp[0] = *(u16 *)(s0 + 0x3A);
    sp[1] = *(u16 *)(s0 + 0x3E);
    sp[2] = *(u16 *)(s0 + 0x42);
    func_8012AD80(s0);
    sp[4] = *(u16 *)(s0 + 6);
    sp[5] = *(u16 *)(s0 + 0xA);
    sp[6] = *(u16 *)(s0 + 0xE);
    ret = func_8012CEB0((s32)&sp[0], (s32)&sp[4], 0x11);
    *(u16 *)(s0 + 6) = sp[4];
    *(u16 *)(s0 + 0xA) = sp[5];
    *(u16 *)(s0 + 0xE) = sp[6];
    return ret;
}




extern s32 func_8012C51C(void *a0, s32 a1);

void func_80183D38(void *a0, s16 a1, s32 a2) {
    Local_8017EE34 local;

    local.f0 = *(u16 *)((s32)a0 + 0x06);
    local.f1 = *(u16 *)((s32)a0 + 0x0A);
    local.f2 = *(u16 *)((s32)a0 + 0x0E);
    local.f3 = 0x170;
    local.f4 = a1;
    local.f5 = 0;
    local.f6 = 0x7FFF;
    local.f7 = 0;
    local.f8 = a2;
    func_8012C51C(&local, (s32)a0);
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80183DA0);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80183EE8(void) {
        func_8002D4C8(0x4, 0x730);
    }


extern s32 D_801BA5A0;
extern s32 D_801BA5A2;
extern s32 D_801BA5A4;
extern void func_80184604();

void func_80183F0C(void *a0) {
    void *t;
    void *vp;

    *(s16 *)&D_801BA5A0 = 0;
    *(s16 *)&D_801BA5A2 = 0;
    *(s16 *)&D_801BA5A4 = 0;
    t = *(void **)((char *)a0 + 0x78);
    *(s16 *)((char *)a0 + 2) = 3;
    *(s16 *)((char *)a0 + 0x34) = 0;
    *(s32 *)((char *)a0 + 0x1C) = 30;
    *(u16 *)((char *)a0 + 0x5C) = *(u16 *)((char *)t + 2);
    t = *(void **)((char *)a0 + 0x20);
    *(u16 *)((char *)t + 0x1A) = 0x1800;
    *(u16 *)((char *)t + 0x18) = 0x1800;
    vp = *(void **)((char *)a0 + 0x20);
    *(u16 *)((char *)vp + 0x14) = 0;
    *(u16 *)((char *)vp + 0x12) = 0;
    *(u16 *)((char *)vp + 0x10) = 0;
    func_80184604(0);
}


#include "common.h"

/* ---- local layout typedefs (standalone match_one compilation) --------------
 * SVec: {s16 vx,vy,vz,pad;} 8 bytes.
 * Mtx : {s16 m[3][3]; s32 t[3];} 0x20 bytes  (frame 0x50..0x6F).
 * Prim: v[4] @0x00, 8 UV shorts @0x20, bcast @0x30, tag @0x34, code @0x38,
 *       padded to 0x40                       (frame 0x10..0x4F).
 * flag (s32) @0x70.  var_size = 0x40+0x20+8 = 0x68  ->  frame 0x98 w/ 7 saves.
 */
typedef struct { s16 vx, vy, vz, pad; } SVec_80183F84;
typedef struct { short m[3][3]; long t[3]; } MATRIX_80188114;
typedef struct {
    SVec_80183F84 v[4];                       /* 0x00 */
    s16 u0, t0, u1, t1, u2, t2, u3, t3;       /* 0x20 */
    u32 bcast;                                /* 0x30 */
    s32 tag;                                  /* 0x34 */
    u8  code;                                 /* 0x38 */
    u8  pad39[7];                             /* 0x39 -> 0x40 */
} Prim_80183F84;

extern MATRIX_80188114 D_800AE620;

extern void func_80020DA4(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_80016EF8(void *a0, void *a1);

#define gte_SetRotMatrix(r0) __asm__ volatile (          \
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

void func_80183F84(void *a0, void *a1) {
    Prim_80183F84 prim;
    MATRIX_80188114 mtx;
    s32 flag;
    s32 i;
    s16 uL, uR, vT;
    u16 dx, dy;

    if (a1 == 0) {
        return;
    }

    prim.tag = 0x50000000;
    prim.code = 0x74;

    prim.v[0].vx = -0x20; prim.v[0].vy = -0x10;
    prim.v[1].vx =  0x20; prim.v[1].vy = -0x10;
    prim.v[2].vx = -0x20; prim.v[2].vy =  0x10;
    prim.v[3].vx =  0x20; prim.v[3].vy =  0x10;
    prim.v[3].vz = 0;
    prim.v[2].vz = 0;
    prim.v[1].vz = 0;
    prim.v[0].vz = 0;

    dx = *(u16 *)((u8 *)a1 + 4);
    dy = *(u16 *)((u8 *)a1 + 6);

    prim.bcast = 0x808080;

    mtx.t[2] = 0;
    mtx.t[1] = 0;
    mtx.t[0] = 0;

    func_80020DA4((s32)((u8 *)a1 + 8), (s32)&mtx);
    func_80020F34((s32)&mtx, (s32)((u8 *)a1 + 0x10));

    gte_SetRotMatrix(&mtx);
    gte_SetTransMatrix(&mtx);

    for (i = 0; i < 4; i++) {
        RotTransSV(&prim.v[i], &prim.v[i], &flag);
    }

    prim.v[0].vx = prim.v[0].vx + dx;
    prim.v[0].vy = prim.v[0].vy + dy;
    prim.v[1].vx = prim.v[1].vx + dx;
    prim.v[1].vy = prim.v[1].vy + dy;
    prim.v[2].vx = prim.v[2].vx + dx;
    prim.v[2].vy = prim.v[2].vy + dy;
    prim.v[3].vx = prim.v[3].vx + dx;
    prim.v[3].vy = prim.v[3].vy + dy;

    if ((*(s32 *)a1 & 1) == 0) {
        uL = 0xF14; vT = 0x1E0; uR = 0xF53;
    } else {
        uL = 0xF53; vT = 0x1E0; uR = 0xF14;
    }

    prim.u0 = uL; prim.t0 = vT;
    prim.u1 = uR; prim.t1 = vT;
    prim.u2 = uL; prim.t2 = 0x1FF;
    prim.u3 = uR; prim.t3 = 0x1FF;

    if ((*(s32 *)a1 & 2) == 0) {
        func_80016EF8(&prim, (void *)(*(s32 *)((u8 *)a0 + 0x20) + 0x34));
    } else {
        mtx = D_800AE620;
        func_80020F34((s32)&mtx, (s32)(*(s32 *)((u8 *)a0 + 0x20) + 0x18));
        mtx.t[0] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x48);
        mtx.t[1] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x4C);
        mtx.t[2] = *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x50);
        func_80016EF8(&prim, &mtx);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018423C);

extern u8 D_801202A0[];

void func_801843DC(void)
{
    register s32 i __asm__("$17");
    register u8 *p __asm__("$16");
    s32 limit;

    i = 0;
    p = D_801202A0;
    limit = 0x170;
    do {
        if (*(u16 *)p == limit) {
            if (*(s16 *)(p + 0x70) & 0x8000) {
                func_8012C218(p);
            }
        }
        i = i + 1;
        p = p + 0x10C;
    } while (i < 0x60);
    return;
}


extern u16 D_8018E7A0[];
extern u16 D_8018E7C0[];
extern s16 D_801BA6B4[];
extern s16 D_801BA6B6[];
extern s16 D_801BA6B8[];

void func_80184458(void) {
    u16 *q = D_8018E7A0;
    u16 *p = D_8018E7C0;
    s32 i;
    s32 off;
    for (i = 0, off = 0; i < 16; i++, off += 6) {
        *(s16 *)((s32)D_801BA6B4 + off) = (p[0] & 0x1F) - (q[0] & 0x1F);
        *(s16 *)((s32)D_801BA6B6 + off) = ((p[0] >> 5) & 0x1F) - ((q[0] >> 5) & 0x1F);
        *(s16 *)((s32)D_801BA6B8 + off) = ((*p++ >> 10) & 0x1F) - ((*q++ >> 10) & 0x1F);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80184500);

extern u8 D_8018E680[];
extern s32 D_801BA6A8;
extern s32 D_801BA6AC;

void func_80184604(s32 arg0) {
    s32 idx;

    if (arg0 != -1) {
        idx = arg0 * 24;
        D_801BA6A8 = (s32)&D_8018E680[idx];
        D_801BA6AC = (s32)&D_8018E680[idx + 24];
    } else {
        D_801BA6A8 = 0;
        D_801BA6AC = 0;
    }
}



extern void (*D_8018E8DC[])(void);

void func_8018465C(void *a0) {
    D_8018E8DC[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80016714(void *a0, s32 a1);
extern u8 D_801BA734[];
extern MATRIX_80188114 D_800AE620;
extern MATRIX_80188114 D_801BC9B4;
extern u16 D_801BC9C4;

void func_80184698(s32 *a0) {
    func_80016714(&D_801BA734, 0x2280);
    D_801BC9B4 = D_800AE620;
    D_801BC9C4 = 0x1000;
    *(u16 *)((u8 *)a0 + 2) += 1;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80184738);

void func_801847B0(void) {
}

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801847B8);

#include "common.h"

/* Neighbour func_80185238 in this very TU already declares/defines the struct-vec
 * calling convention this function shares (card tu_ref): void func_80185238(struct
 * vec *a0). match_one compiles standalone (no src/shared headers reachable), so we
 * pass the pointer through as void* here -- identical codegen, no dereference
 * happens on our side of the call. The real TU declaration is adopted verbatim at
 * bank time (law 2/8). */
struct vec;
extern void func_80185238(struct vec *a0);
extern void func_80185218(void *arg0);

/* No definition/decl anywhere in the fleet for these three -- derived from the
 * target .s call-site register setup (decl_prior had no "tu" row to adopt). */
extern s32  func_80185680(void *a0, void *a1);
extern void func_80185810(s32 a0);
extern s32 func_80185480();

extern s32 func_80047D3C(s32 a0);
typedef struct { s16 vx, vy, vz, pad; } SVEC_801BA5A8;
extern s32 VectorNormalSS(void *a0, void *a1);
extern SVEC_801BA5A8 D_801BA5A8[];

void func_801848A4(void *a0) {
    void *s1;
    u16 state;

    s1 = (u8 *)a0 + 0x20;
    func_80185680(s1, (u8 *)a0 + 0x48);

    state = *(u16 *)((u8 *)a0 + 0x2);
    switch (state) {
        case 0:
        {
            register s32 v1  __asm__("$3");
            register s32 a0f __asm__("$4");
            register s32 a1f __asm__("$5");
            s32 cnt;

            func_80185238((struct vec *)a0);
            v1  = *(u16 *)((u8 *)a0 + 0x6);
            a0f = *(u16 *)((u8 *)a0 + 0xA);
            cnt = *(s32 *)((u8 *)a0 + 0x1C) + 1;
            a1f = *(u16 *)((u8 *)a0 + 0xE);
            *(s32 *)((u8 *)a0 + 0x1C) = cnt;
            *(u16 *)((u8 *)a0 + 0x34) = v1;
            *(u16 *)((u8 *)a0 + 0x36) = a0f;
            *(u16 *)((u8 *)a0 + 0x38) = a1f;
            if (cnt >= 0x1E) {
                *(u16 *)((u8 *)a0 + 0x2) = *(u16 *)((u8 *)a0 + 0x2) + 1;
            }
            break;
        }
        case 1:
        {
            s32 *p = *(s32 **)((u8 *)a0 + 0x40);
            if ((*(s32 *)((u8 *)p + 0xE0) & 1) != 0) {
                u16 t0 = *(u16 *)((u8 *)a0 + 0x34);
                u16 t1 = *(u16 *)((u8 *)a0 + 0x36);
                u16 t2 = *(u16 *)((u8 *)a0 + 0x38);

                *(u16 *)((u8 *)a0 + 0x2) = state + 1;
                *(u16 *)((u8 *)a0 + 0x6) = t0;
                *(u16 *)((u8 *)a0 + 0xA) = t1;
                *(u16 *)((u8 *)a0 + 0xE) = t2;
                *(s32 *)((u8 *)a0 + 0x1C) = 0;
                *(s32 *)((u8 *)a0 + 0x10) = -(*(s32 *)((u8 *)a0 + 0x10));
                *(s32 *)((u8 *)a0 + 0x14) = -(*(s32 *)((u8 *)a0 + 0x14));
                *(s32 *)((u8 *)a0 + 0x18) = -(*(s32 *)((u8 *)a0 + 0x18));
            }
            break;
        }
        case 2:
        {
            register s32 v1  __asm__("$3");
            register s32 a0f __asm__("$4");
            register s32 a1f __asm__("$5");
            s32 cnt;

            func_80185238((struct vec *)a0);
            v1  = *(u16 *)((u8 *)a0 + 0x6);
            a0f = *(u16 *)((u8 *)a0 + 0xA);
            cnt = *(s32 *)((u8 *)a0 + 0x1C) + 1;
            a1f = *(u16 *)((u8 *)a0 + 0xE);
            *(s32 *)((u8 *)a0 + 0x1C) = cnt;
            *(u16 *)((u8 *)a0 + 0x34) = v1;
            *(u16 *)((u8 *)a0 + 0x36) = a0f;
            *(u16 *)((u8 *)a0 + 0x38) = a1f;
            if (cnt >= 0x1E) {
                func_80185218(a0);
                return;
            }
            break;
        }
    }

    {
        SVEC_801BA5A8 sv;
        s32 idx;
        s32 ret;

        sv.vx = *(u16 *)((u8 *)s1 + 0x14);
        sv.vy = 0;
        sv.vz = *(u16 *)((u8 *)s1 + 0x18);

        idx = *(s16 *)((u8 *)a0 + 0x50);
        ret = VectorNormalSS(&sv, &D_801BA5A8[idx]);
        ret = func_80047D3C(ret);
        *(u16 *)((u8 *)s1 + 0x1A) = ret;
        func_80185480(a0, 0x28);
        func_80185810((s32)s1);
    }
}


#include "common.h"

/* ---------------------------------------------------------------------------
 * func_80184A60  --  MATCH (60/60 ins, relocation-masked).
 *
 * Per-frame update of the "aim" sub-object hanging off *(s0+0x50):
 *   if (owner->flag16 @ +6 == 0)  ->  func_80185218(self) and bail
 *   else                          ->  func_80185680(&self[0x20], &self[0x48]),
 *                                     rebuild the three s16 fields at
 *                                     +0x34/+0x36/+0x38 from
 *                                     mag(+0x54) * (ang(+6)/8) * D_801BA5A8[idx(+0x56)],
 *                                     (>>12, middle component biased -0x40),
 *                                     then func_80185810(&self[0x20]).
 *
 * Declarations (law 2/3):
 *   func_80185218 is DEFINED IN THIS TU at line 3799 -- this extern is its
 *   definition's signature verbatim.  ** BANKING NOTE: func_80184A60 sits at TU
 *   line 3769, BEFORE that definition, so the extern below (or a hoist of the
 *   definition) must survive into the TU. **
 *   func_80185680 / func_80185810 are still INCLUDE_ASM stubs with no TU decl;
 *   the spellings below are the ones that collide least with the sibling drafts
 *   in this wave: `s32 func_80185680(void*, void*)` is func_80184B50.c's decl
 *   verbatim (that draft consumes the return value; this one discards it), and
 *   `void func_80185810(s32)` is the fleet/decl_prior majority (n=5) and
 *   func_80184CA8.c's decl verbatim -- hence the (s32) cast at the call.
 *   The call site here genuinely sets BOTH $a0 and $a1 before the jal, so the
 *   decl_prior single-s32-param row for func_80185680 is a false lead.
 *
 * SVEC_801BA5A8: same NAME and same BODY as the sibling draft func_801848A4.c
 * (§183.1 -- adopting the name without the body is worse than not adopting).
 * ------------------------------------------------------------------------- */
extern void func_80185218(void *arg0);
extern s32  func_80185680(void *a0, void *a1);
extern void func_80185810(s32 a0);


extern SVEC_801BA5A8 D_801BA5A8[];

void func_80184A60(void *arg0) {
    /* PIN 1 (carried from the first-pass draft, §48-A2-shaped): without the $16
     * pin a value crossing the /8 idiom's conditional branch drags in a spurious
     * "move $s2,$s0" plus a phantom 4th callee-saved register. */
    register u8 *s0 __asm__("$16") = (u8 *)arg0;
    u8 *s1;
    void *s2;
    s16 flag;
    s32 ang;
    s32 mag;
    s32 idx;
    s32 scale;
    /* PIN 2 (this pass -- the lever that closed the last 6 diffs).  The three
     * mflo destinations are the product pseudos; gcc gives each of them $v0
     * because $v0 is free in the gap between the `mult` and its `sra`.  The
     * target instead rotates them a3/a3/v1, which only happens once $v0 is
     * LIVE ACROSS the mults -- i.e. once the shifted result is one long-lived
     * value nailed to $v0 rather than three short temps.  greg dump evidence:
     * the product allocnos' conflict sets gain hard reg 2, so global_alloc's
     * plain 0..N scan skips $v0/$v1/$a0/$a1/$a2 and lands on $a3, and takes $v1
     * for the third once `vp` has died.  A `register s32 r;` (no asm) or a
     * plain `s32 r;` reused across all three does NOT do it (still 6 diffs) --
     * the hard-register pin is what forces the conflict. */
    register s32 r __asm__("$2");
    SVEC_801BA5A8 *vp;

    s1 = *(u8 **)(s0 + 0x50);
    s2 = s0 + 0x20;
    flag = *(s16 *)(s1 + 0x6);          /* +0x6 of the owner record */
    if (flag == 0) {
        func_80185218(s0);
        return;
    }

    func_80185680(s2, s0 + 0x48);

    mag = *(s16 *)(s0 + 0x54);
    /* The /8 written out longhand (bgez + addiu 7 + sra 3) AND scoped to its own
     * temp `t`.  The inner scope is load-bearing: with `ang` itself carrying the
     * rounding, `mag * ang` swapped which of mag/ang got $v0 vs $a0 and the mult
     * still printed backwards (row 25).  Giving the rounding its own pseudo lets
     * the natural source order `mag * ang` emit the target's `mult $v0,$a0`. */
    {
        s32 t = *(s16 *)(s1 + 0x6);
        if (t < 0) t += 7;
        ang = t >> 3;
    }
    idx = *(s16 *)(s0 + 0x56);
    vp = &D_801BA5A8[idx];
    scale = mag * ang;

    r = (scale * vp->vx) >> 12;
    *(s16 *)(s0 + 0x34) = r;
    r = ((scale * vp->vy) >> 12) - 0x40;
    *(s16 *)(s0 + 0x36) = r;
    r = (scale * vp->vz) >> 12;
    *(s16 *)(s0 + 0x38) = r;
    func_80185810((s32)s2);
}


#include "common.h"

extern void func_80185218(void *arg0);
extern s32  func_80185680(void *a0, void *a1);
extern void func_8018574C(void *a0);
extern s32  func_8018526C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80185810(s32 a0);

void func_80184B50(u8 *param_1)
{
    register u8 *s0 __asm__("$16") = param_1;
    register u8 *s1 __asm__("$17");
    u8 *s2;
    s32 factor;

    s1 = *(u8 **)(s0 + 0x50);
    s2 = s0 + 0x20;

    if (*(s32 *)(*(s32 *)(s0 + 0x40) + 0xE0) & 2) {
        func_80185218(s0);
        return;
    }

    if (func_80185680(s2, s0 + 0x48) == 1) {
        if (rand() & 1) {
            func_8018574C(s2);
        }
    }

    factor = *(s16 *)(s0 + 0x54) * (*(s16 *)(s1 + 0x12) / *(s16 *)(s0 + 0x56));

    *(s16 *)(s2 + 0x14) = *(u16 *)(s1 + 0x4) + ((factor * *(s16 *)(s1 + 0xC)) >> 12);
    *(s16 *)(s2 + 0x16) = *(u16 *)(s1 + 0x6) + ((factor * *(s16 *)(s1 + 0xE)) >> 12);
    *(s16 *)(s2 + 0x18) = *(u16 *)(s1 + 0x8) + ((factor * *(s16 *)(s1 + 0x10)) >> 12);

    func_8018526C((s32)s0, -0x18, 0x18, 0x30);
    func_80185810((s32)s2);
}


#include "common.h"

extern s32 rand(void);
extern s32 func_80185628();
extern void func_80185810(s32 a0);
extern s32  func_80185680(void *a0, void *a1);
extern s32 func_8017E5C8(s32 a0);
extern void func_80185380(s32 a0, s32 a1, s32 a2);
extern void func_80185218(void *arg0);

void func_80184CA8(s32 a0) {
    s32 v0;
    s16 *s1;
    s32 s3;
    u16 flag;
    s32 counter;
    /* K&R house style: all locals at the top. gcc-2.7.2 assigns stack slots in
       DECLARATION order (cookbook item 6), so buf[8] must be declared BEFORE
       tmp[4] to land at sp+0x10 with tmp at sp+0x20 -- even though tmp's arm
       runs first at runtime. */
    s16 buf[8];
    s16 tmp[4];
    s32 t;
    s16 u;
    s32 rnd;
    s32 base;
    s32 rem;
    s32 result;

    s3 = a0 + 0x20;                       /* $s3 = a0 + 0x20 */
    v0 = *(s32 *)(a0 + 0x54);
    s1 = *(s16 **)(a0 + 0x50);
    if (v0 == 0) {                        /* target: bnez v0 SKIPS the call */
        v0 = func_80185628(a0 + 0x34, (s32)s1);
        *(s16 *)(a0 + 0x28) = v0;
    }

    flag = *(u16 *)(a0 + 2);
    *(s16 *)(a0 + 0x34) = s1[0];
    *(s16 *)(a0 + 0x36) = s1[1];
    *(s16 *)(a0 + 0x38) = s1[2];

    /* flag != 0 first: writing the arms the other way round flips which side
       falls through and corrupts every branch downstream. */
    if (flag != 0) {
        counter = *(s32 *)(a0 + 0x1C);
        if (counter != 0) {
            *(s32 *)(a0 + 0x1C) = counter - 1;
        } else {
            v0 = func_80185680((void *)s3, (void *)(a0 + 0x48));
            if (v0 == 1) {
                rnd = rand();
                t = *(s16 *)(a0 + 0x2C);
                base = *(s16 *)(a0 + 0x34);
                /* Two levers in ONE zero-byte asm.
                   (1) combine expands sign_extend(lh) into ashift/ashiftrt and
                       merges it with the outer >>7, so the natural spelling
                       always emits lhu+sll,16+sra,23 (3 ins). The re-tie breaks
                       the i2->i3 chain, leaving the target's lh + sra,7 (2 ins).
                   (2) naming `base` as an extra INPUT makes the 0x34 load a
                       predecessor of the fence, so sched1 must place it before
                       the fence -- i.e. into the lh 0x2C load-delay slot, which
                       is exactly where the target has `lh $s1,0x34($s0)`.
                       Without it that slot is a nop and the function is 116 ins. */
                __asm__("" : "=r"(t) : "0"(t), "r"(base));
                rem = rnd % (t >> 7);
                if (rand() & 1) {
                    result = base + rem;
                } else {
                    result = base - rem;
                }
                tmp[0] = result;                                        /* sp+0x20 */
                tmp[1] = *(u16 *)(s3 + 0x16) + *(u16 *)(s3 + 0x1E);     /* sp+0x22 */
                tmp[2] = *(u16 *)(s3 + 0x18);                           /* sp+0x24 */
                func_8017E5C8((s32)tmp);
                func_80185218((void *)a0);
            } else {
                /* `u` MUST be declared s16, not s32 (width dial, cookbook
                   §194-B): the 16-bit local keeps the shift result in $v0 and
                   sends the negation to $v1; an s32 local swaps the pair. */
                u = (s16)(*(u16 *)(a0 + 0x2C)) >> 9;
                buf[2] = -u;                                            /* sp+0x14 */
                buf[3] = u;                                             /* sp+0x16 */
                u = (s16)(*(u16 *)(a0 + 0x2E)) >> 9;
                buf[4] = -u;                                            /* sp+0x18 */
                buf[5] = u;                                             /* sp+0x1A */
                u = (s16)(*(u16 *)(a0 + 0x30)) >> 9;
                buf[6] = -u;                                            /* sp+0x1C */
                buf[7] = u;                                             /* sp+0x1E */
                func_80185380(a0, (s32)&buf[0], 0x30);                  /* a1 = sp+0x10 */
                func_80185810(s3);
            }
        }
    } else {
        *(s16 *)(a0 + 2) = flag + 1;
        *(s32 *)(a0 + 0x1C) = rand() % 4;
    }
}


void func_80184E74(u8 *param_1)
{
    register u8 *s0 __asm__("$16") = param_1;
    register u8 *s1 __asm__("$17");
    u8 *s2;
    s32 b;

    s2 = *(u8 **)(s0 + 0x40);
    if (*(s32 *)(s2 + 0xE0) & 0x10) {
        func_80185218(s0);
        return;
    }
    s1 = s0 + 0x20;

    if (func_80185680(s1, s0 + 0x48) == 1) {
        if (rand() & 1) {
            func_8018574C(s1);
        }
    }

    b = *(s16 *)(s2 + 0x102);
    *(s16 *)(s1 + 0x14) = *(u16 *)(s0 + 0x52) * (b / 10);

    func_8018526C((s32)s0, -0x18, 0x48, 0x30);
    func_80185810((s32)s1);
}


void func_80184F5C(s32 arg0) {
    s32 var_s0 = arg0;
    s32 var_s1 = arg0 + 0x20;

    if (func_80185680((void *) var_s1, (void *) (arg0 + 0x48)) == 1) {
        func_80185218((void *) var_s0);
    } else {
        func_80185810(var_s1);
    }
}


#include "common.h"

/* NOTE: destination TU already `#include "../shared/engine_core.h"`, which pulls in
 * engine_types.h's `typedef struct { s16 h[8]; } Buf;`. Drop this local typedef when
 * merging into the TU (kept here only so this draft compiles standalone). */


extern void func_80049CAC(s32 a0, s32 a1);

void func_80184FBC(s32 param_1, s32 param_2, s32 *param_3)
{
    Buf buf;

    if ((param_1 & 0x1000000) != 0) {
        s32 p;
        s32 w;

        p = param_1 & 0xfeffffff;
        p = p + param_2 * 8;
        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        param_1 = param_1 + param_2 * 0xc;
        buf.h[0] = *(s16 *)(param_1 + 6);
        buf.h[1] = *(s16 *)(param_1 + 8);
        buf.h[2] = *(s16 *)(param_1 + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(param_1 + 0);
        param_3[6] = *(s16 *)(param_1 + 2);
        param_3[7] = *(s16 *)(param_1 + 4);
    }
}


#include "common.h"

typedef struct {
    u16 f0, f1, f2, f3;
} Vec4x16;

extern s32 func_801851E0(void);
extern void func_80185660(s32 *a0, s32 *a1, s32 a2);

s32 func_801850D8(s32 a0, s32 a1, s32 a2, s32 a3, Vec4x16 *a5, s32 a6, s32 a7, s32 a8) {
    s32 obj;

    obj = func_801851E0();
    if (obj == 0) {
        return 0;
    }
    *(s32 *)(obj + 0x20) = 0x50000000;
    *(s16 *)(obj + 0x2E) = a1;
    *(s16 *)(obj + 0x2C) = a1;
    *(s16 *)(obj + 0x30) = 0x1000;
    *(Vec4x16 *)(obj + 0x34) = *a5;
    *(s32 *)(obj + 0x40) = a6;
    *(s16 *)(obj + 0x3C) = a2;
    *(s16 *)(obj + 0x3E) = a3;
    func_80185660((s32 *)(obj + 0x20), (s32 *)(obj + 0x48), a7);
    *(s16 *)(obj + 0x0) = a0;
    *(s32 *)(obj + 0x14) = a8;
    *(s16 *)(obj + 0x6) = a5->f0;
    *(s16 *)(obj + 0xA) = a5->f1;
    *(s16 *)(obj + 0xE) = a5->f2;
    return obj;
}


s32 func_801851E0(void) {

    extern u8 D_801BA734[];
    s32 a0;
    s32 v1;
    v1 = (s32)D_801BA734;
    for (a0 = 0; a0 < 0x60; a0++, v1 += 0x5C) {
        if (*(u16 *)v1 == 0) {
            return v1;
        }
    }
    return 0;
}


extern void func_80016714(void *a0, s32 a1);
    void func_80185218(void *arg0) {
        ((void (*)(s32, s32))func_80016714)((s32)arg0, 0x5C);
    }


void func_80185238(struct vec *a0) {
    a0->unk4 += a0->unk10;
    a0->unk8 += a0->unk14;
    a0->unkC += a0->unk18;
}


#include "common.h"

/* match_one isolation has no -I to src/shared/engine_types.h; on bank, drop these local
   typedefs -- the destination TU already defines SVECTOR/MATRIX via its own
   `#include "../shared/engine_core.h"`. */



extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];

s32 func_8018526C(s32 a0, s32 a1, s32 a2, s32 a3) {
    SVECTOR p1;
    SVECTOR p2;
    SVECTOR b;
    SVECTOR c;
    MATRIX  mtx;
    s32 v2;

    p1.vx = *(u16 *)(a0 + 0x34);
    p1.vy = *(u16 *)(a0 + 0x36) + a1 + *(u16 *)(a0 + 0x3E);
    p1.vz = *(u16 *)(a0 + 0x38);

    p2.vx = *(u16 *)(a0 + 0x34);
    p2.vy = *(u16 *)(a0 + 0x36) + a2 + *(u16 *)(a0 + 0x3E);
    p2.vz = *(u16 *)(a0 + 0x38);

    v2 = a3;

    func_80185FB4(*(s32 *)(*(s32 *)(a0 + 0x40) + 0x20), *(s32 *)(a0 + 0x20), (s32)&mtx);

    func_8012F14C((s32)&mtx, (s32)&p1, (s32)&b);
    func_8012F14C((s32)&mtx, (s32)&p2, (s32)&c);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&b, (s32)&c) != 0) {
        func_8012F568(1, 0x4201, 0, v2, (s32)&c, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80185380);

typedef struct { s16 x, y, z, w; } V4_80185480;
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_80185480;

extern void func_80185FB4(s32, s32, s32);
extern void func_8012F14C(s32, s32, s32);
extern s32 func_80135888(s32, s32, s32, s32);
extern void func_8012F568(s32, s32, s32, s32, s32, s32);
extern s32 D_80126B58;
extern u8 D_801152A8[];

s32 func_80185480(void *a0, void *a1)
{
    V4_80185480 va;
    V4_80185480 vb;
    V4_80185480 c;
    V4_80185480 d;
    Mtx32_80185480 mtx;
    u8 *s4p;
    u8 *b58;
    s32 w0;
    s32 w1;
    s32 sum;
    s32 i;

    s4p = (u8 *)a0 + 0x20;

    ((void (*)(s32, void *, void *))func_80185FB4)(*(s32 *)(*(s32 *)((s32)a0 + 0x40) + 0x20),
                  *(s32 *)((s32)a0 + 0x20), &mtx);

    b58 = (u8 *)&D_80126B58;
    w0 = *(s32 *)((s32)a0 + 0x10) << 1;
    w1 = *(s32 *)((s32)a0 + 0x18) << 1;

    va.x = 0;
    vb.x = (*(s16 *)(s4p + 0x14) + *((s16 *)&w0 + 1)) >> 1;
    va.z = 0;
    vb.z = (*(s16 *)(s4p + 0x18) + *((s16 *)&w1 + 1)) >> 1;
    sum = *(u16 *)(s4p + 0x16) + *(u16 *)(s4p + 0x1E) + 0x30;
    vb.y = sum;
    va.y = sum;

    i = 0;
    do {
        func_8012F14C((s32)&mtx, (s32)&va, (s32)&c);
        func_8012F14C((s32)&mtx, (s32)&vb, (s32)&d);
        if (func_80135888(*(s32 *)(b58 + 0x20), *(s32 *)(b58 + 0x38),
                          (s32)&c, (s32)&d) == 0) {
            va = vb;
            vb.x = *(u16 *)(s4p + 0x14) + *((u16 *)&w0 + 1);
            vb.z = *(u16 *)(s4p + 0x18) + *((u16 *)&w1 + 1);
            i++;
        } else {
            func_8012F568(1, 0x4201, 0, (s32)a1, (s32)&d, (s32)D_801152A8);
            return 1;
        }
    } while (i < 2);
    return 0;
}


extern s32 ratan2(s32 a0, s32 a1);

s32 func_80185628(s16 *a0, s16 *a1) {
    s16 ax = a0[1];
    s16 bx = a1[1];
    s16 by = a1[0];
    s16 ay = a0[0];
    return (ratan2(bx - ax, by - ay) + 0x400) & 0xFFF;
}


void func_80185660(s32 *a0, s32 *a1, s32 a2) {
        *(s32 *)((s32)a1 + 0x0) = a2;
        *(s32 *)((s32)a0 + 0x24) = a2;
        *(s16 *)((s32)a1 + 0x4) = 0;
        *(s16 *)((s32)a1 + 0x6) = *(u8 *)a2 & 0x3F;
    }


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80185680);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018574C);



extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);

__asm__(".text\n.align 2\n.globl func_80185810\n.ent\tfunc_80185810\n"
"func_80185810:\n.frame $sp,128,$31\n.mask 0x500F0000,-8\n.fmask 0,0\n"
".set\tnoreorder\n"
"addiu $sp, $sp, -128\n"
"sw $s1, 108($sp)\n"
"addu $s1, $a0, $zero\n"
"sw $s4, 120($sp)\n"
"lui $s4, %hi(D_800AF630)\n"
"addiu $s4, $s4, %lo(D_800AF630)\n"
"sw $ra, 124($sp)\n"
"sw $s3, 116($sp)\n"
"sw $s2, 112($sp)\n"
"sw $s0, 104($sp)\n"
"lw $s3, 0($s1)\n"
"lw $a0, 32($s1)\n"
"lw $s2, 36($s1)\n"
"beqz $a0, .L80185B7C\n"
"lui $v0, 128\n"
"and $v0, $s3, $v0\n"
"beqz $v0, .L801859DC\n"
"addiu $v1, $s4, 24\n"
"lw $t4, 0($v1)\n"
"lw $t5, 4($v1)\n"
"ctc2 $t4, $0\n"
"ctc2 $t5, $1\n"
"lw $t4, 8($v1)\n"
"lw $t5, 12($v1)\n"
"lw $t6, 16($v1)\n"
"ctc2 $t4, $2\n"
"ctc2 $t5, $3\n"
"ctc2 $t6, $4\n"
"lw $v0, 32($a0)\n"
"nop\n"
"addiu $v0, $v0, 52\n"
"lhu $t4, 0($v0)\n"
"lhu $t5, 6($v0)\n"
"lhu $t6, 12($v0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"addiu $v0, $sp, 56\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($v0)\n"
"sh $t5, 6($v0)\n"
"sh $t6, 12($v0)\n"
"lw $v0, 32($s1)\n"
"nop\n"
"lw $v0, 32($v0)\n"
"nop\n"
"addiu $v0, $v0, 54\n"
"lhu $t4, 0($v0)\n"
"lhu $t5, 6($v0)\n"
"lhu $t6, 12($v0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"addiu $v0, $sp, 58\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($v0)\n"
"sh $t5, 6($v0)\n"
"sh $t6, 12($v0)\n"
"lw $v0, 32($s1)\n"
"nop\n"
"lw $v0, 32($v0)\n"
"nop\n"
"addiu $v0, $v0, 56\n"
"lhu $t4, 0($v0)\n"
"lhu $t5, 6($v0)\n"
"lhu $t6, 12($v0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"addiu $v0, $sp, 60\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($v0)\n"
"sh $t5, 6($v0)\n"
"sh $t6, 12($v0)\n"
"lw $t4, 20($v1)\n"
"lw $t5, 24($v1)\n"
"ctc2 $t4, $5\n"
"lw $t6, 28($v1)\n"
"ctc2 $t5, $6\n"
"ctc2 $t6, $7\n"
"lw $v0, 32($s1)\n"
"nop\n"
"lw $v0, 32($v0)\n"
"nop\n"
"addiu $v0, $v0, 72\n"
"lhu $t5, 4($v0)\n"
"lhu $t4, 0($v0)\n"
"sll $t5, $t5, 16\n"
"or $t4, $t4, $t5\n"
"mtc2 $t4, $0\n"
"lwc2 $1, 8($v0)\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 0, 0, 0\n"
"addiu $v0, $sp, 76\n"
"swc2 $25, 0($v0)\n"
"swc2 $26, 4($v0)\n"
"swc2 $27, 8($v0)\n"
"j .L80185B28\n"
"addiu $v0, $sp, 56\n"
".L801859DC:\n"
"lw $a0, 32($a0)\n"
"addu $a1, $s3, $zero\n"
"addiu $s0, $sp, 56\n"
"jal func_80185FB4\n"
"addu $a2, $s0, $zero\n"
"addiu $v1, $s4, 24\n"
"lw $t4, 0($v1)\n"
"lw $t5, 4($v1)\n"
"ctc2 $t4, $0\n"
"ctc2 $t5, $1\n"
"lw $t4, 8($v1)\n"
"lw $t5, 12($v1)\n"
"lw $t6, 16($v1)\n"
"ctc2 $t4, $2\n"
"ctc2 $t5, $3\n"
"ctc2 $t6, $4\n"
"lhu $t4, 0($s0)\n"
"lhu $t5, 6($s0)\n"
"lhu $t6, 12($s0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($s0)\n"
"sh $t5, 6($s0)\n"
"sh $t6, 12($s0)\n"
"addiu $v0, $sp, 58\n"
"lhu $t4, 0($v0)\n"
"lhu $t5, 6($v0)\n"
"lhu $t6, 12($v0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($v0)\n"
"sh $t5, 6($v0)\n"
"sh $t6, 12($v0)\n"
"addiu $v0, $sp, 60\n"
"lhu $t4, 0($v0)\n"
"lhu $t5, 6($v0)\n"
"lhu $t6, 12($v0)\n"
"mtc2 $t4, $9\n"
"mtc2 $t5, $10\n"
"mtc2 $t6, $11\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 3, 3, 0\n"
"mfc2 $t4, $9\n"
"mfc2 $t5, $10\n"
"mfc2 $t6, $11\n"
"sh $t4, 0($v0)\n"
"sh $t5, 6($v0)\n"
"sh $t6, 12($v0)\n"
"lw $t4, 20($v1)\n"
"lw $t5, 24($v1)\n"
"ctc2 $t4, $5\n"
"lw $t6, 28($v1)\n"
"ctc2 $t5, $6\n"
"ctc2 $t6, $7\n"
"addiu $v0, $sp, 76\n"
"lhu $t5, 4($v0)\n"
"lhu $t4, 0($v0)\n"
"sll $t5, $t5, 16\n"
"or $t4, $t4, $t5\n"
"mtc2 $t4, $0\n"
"lwc2 $1, 8($v0)\n"
"nop\n"
"nop\n"
"mvmva 1, 0, 0, 0, 0\n"
"swc2 $25, 0($v0)\n"
"swc2 $26, 4($v0)\n"
"swc2 $27, 8($v0)\n"
"addiu $v0, $sp, 56\n"
".L80185B28:\n"
"lw $t4, 0($v0)\n"
"lw $t5, 4($v0)\n"
"ctc2 $t4, $0\n"
"ctc2 $t5, $1\n"
"lw $t4, 8($v0)\n"
"lw $t5, 12($v0)\n"
"lw $t6, 16($v0)\n"
"ctc2 $t4, $2\n"
"ctc2 $t5, $3\n"
"ctc2 $t6, $4\n"
"lw $t4, 20($v0)\n"
"lw $t5, 24($v0)\n"
"ctc2 $t4, $5\n"
"lw $t6, 28($v0)\n"
"ctc2 $t5, $6\n"
"ctc2 $t6, $7\n"
"lw $v0, 32($s1)\n"
"nop\n"
"lw $v0, 32($v0)\n"
"j .L80185BC4\n"
"addiu $t0, $v0, 16\n"
".L80185B7C:\n"
"addiu $v0, $s4, 24\n"
"lw $t4, 0($v0)\n"
"lw $t5, 4($v0)\n"
"ctc2 $t4, $0\n"
"ctc2 $t5, $1\n"
"lw $t4, 8($v0)\n"
"lw $t5, 12($v0)\n"
"lw $t6, 16($v0)\n"
"ctc2 $t4, $2\n"
"ctc2 $t5, $3\n"
"ctc2 $t6, $4\n"
"lw $t4, 20($v0)\n"
"lw $t5, 24($v0)\n"
"ctc2 $t4, $5\n"
"lw $t6, 28($v0)\n"
"ctc2 $t5, $6\n"
"ctc2 $t6, $7\n"
"addiu $t0, $s1, 4\n"
".L80185BC4:\n"
"addiu $v0, $s1, 20\n"
"lwc2 $0, 0($v0)\n"
"lwc2 $1, 4($v0)\n"
"nop\n"
"nop\n"
"rtps\n"
"addiu $v0, $sp, 16\n"
"swc2 $14, 0($v0)\n"
"addiu $v0, $sp, 88\n"
"swc2 $19, 0($v0)\n"
"lh $v0, 16($sp)\n"
"nop\n"
"bgez $v0, .L80185C00\n"
"nop\n"
"negu $v0, $v0\n"
".L80185C00:\n"
"slti $v0, $v0, 201\n"
"beqz $v0, .L80185F90\n"
"nop\n"
"lh $v0, 18($sp)\n"
"nop\n"
"bgez $v0, .L80185C20\n"
"nop\n"
"negu $v0, $v0\n"
".L80185C20:\n"
"slti $v0, $v0, 161\n"
"beqz $v0, .L80185F90\n"
"nop\n"
"lhu $v0, 12($s1)\n"
"lui $at, %hi(D_801BC9B4)\n"
"sh $v0, %lo(D_801BC9B4)($at)\n"
"lhu $v0, 14($s1)\n"
"lui $t1, %hi(D_801BC9B4)\n"
"addiu $t1, $t1, %lo(D_801BC9B4)\n"
"lui $at, %hi(D_801BC9BC)\n"
"sh $v0, %lo(D_801BC9BC)($at)\n"
"lw $t4, 0($t1)\n"
"lw $t5, 4($t1)\n"
"ctc2 $t4, $0\n"
"ctc2 $t5, $1\n"
"lw $t4, 8($t1)\n"
"lw $t5, 12($t1)\n"
"lw $t6, 16($t1)\n"
"ctc2 $t4, $2\n"
"ctc2 $t5, $3\n"
"ctc2 $t6, $4\n"
"lw $t4, 20($t1)\n"
"lw $t5, 24($t1)\n"
"ctc2 $t4, $5\n"
"lw $t6, 28($t1)\n"
"ctc2 $t5, $6\n"
"ctc2 $t6, $7\n"
"lhu $v0, 8($s2)\n"
"lhu $v1, 28($s1)\n"
"lw $a0, 88($sp)\n"
"addu $v0, $v0, $v1\n"
"sh $v0, 40($sp)\n"
"lhu $v0, 10($s2)\n"
"lhu $v1, 30($s1)\n"
"sh $a0, 44($sp)\n"
"addu $v0, $v0, $v1\n"
"sh $v0, 42($sp)\n"
"lbu $v0, 2($s2)\n"
"nop\n"
"sh $v0, 48($sp)\n"
"lbu $v0, 3($s2)\n"
"addiu $v1, $sp, 40\n"
"sh $a0, 52($sp)\n"
"sh $v0, 50($sp)\n"
"addiu $v0, $sp, 48\n"
"lwc2 $0, 0($v1)\n"
"lwc2 $1, 4($v1)\n"
"lwc2 $2, 0($v0)\n"
"lwc2 $3, 4($v0)\n"
"lwc2 $4, 0($v0)\n"
"lwc2 $5, 4($v0)\n"
"nop\n"
"nop\n"
"rtpt\n"
"addiu $v0, $sp, 24\n"
"swc2 $12, 0($v0)\n"
"addiu $v0, $sp, 32\n"
"swc2 $13, 0($v0)\n"
"addiu $v0, $sp, 92\n"
"cfc2 $t4, $31\n"
"nop\n"
"sw $t4, 0($v0)\n"
"addiu $v0, $sp, 96\n"
"mfc2 $t4, $19\n"
"nop\n"
"sra $t4, $t4, 2\n"
"sw $t4, 0($v0)\n"
"lw $v0, 92($sp)\n"
"addiu $v1, $zero, -4097\n"
"and $v0, $v0, $v1\n"
"bnez $v0, .L80185F90\n"
"srl $a1, $s3, 24\n"
"andi $a1, $a1, 3\n"
"lui $s0, %hi(D_800A5E60)\n"
"lw $s0, %lo(D_800A5E60)($s0)\n"
"sll $v1, $a1, 7\n"
"addiu $v0, $s0, 40\n"
"lui $at, %hi(D_800A5E60)\n"
"sw $v0, %lo(D_800A5E60)($at)\n"
"addiu $v0, $zero, 9\n"
"sb $v0, 3($s0)\n"
"addiu $v0, $zero, 44\n"
"sb $v0, 7($s0)\n"
"lui $at, 1\n"
"addu $at, $s4, $at\n"
"lhu $a2, -23598($at)\n"
"lhu $a0, 4($s2)\n"
"lhu $a3, 6($s2)\n"
"addiu $v0, $zero, 46\n"
"sb $v0, 7($s0)\n"
"srl $v0, $s3, 23\n"
"andi $v0, $v0, 96\n"
"or $v1, $v1, $v0\n"
"andi $v0, $a3, 256\n"
"srl $v0, $v0, 4\n"
"or $v1, $v1, $v0\n"
"andi $v0, $a0, 960\n"
"srl $v0, $v0, 6\n"
"or $v1, $v1, $v0\n"
"andi $v0, $a3, 512\n"
"sll $v0, $v0, 2\n"
"or $v1, $v1, $v0\n"
"andi $v0, $s3, 64\n"
"srl $v0, $v0, 6\n"
"sll $a2, $a2, 14\n"
"sh $v1, 22($s0)\n"
"lbu $v1, 7($s0)\n"
"andi $a3, $a3, 65535\n"
"or $v1, $v1, $v0\n"
"sb $v1, 7($s0)\n"
"addiu $v1, $zero, 2\n"
"lhu $v0, 22($s0)\n"
"subu $v1, $v1, $a1\n"
"andi $v0, $v0, 15\n"
"sll $v0, $v0, 6\n"
"subu $a0, $a0, $v0\n"
"lui $v0, %hi(D_800A6610)\n"
"addiu $v0, $v0, %lo(D_800A6610)\n"
"addu $s1, $a2, $v0\n"
"lhu $v0, 22($s0)\n"
"sllv $a0, $a0, $v1\n"
"andi $v0, $v0, 16\n"
"beqz $v0, .L80185E14\n"
"sb $a0, 12($s0)\n"
"addiu $a3, $a3, -256\n"
".L80185E14:\n"
"lbu $v0, 12($s0)\n"
"sb $a3, 13($s0)\n"
"lbu $v1, 2($s2)\n"
"lbu $a0, 12($s0)\n"
"addu $v0, $v0, $v1\n"
"lbu $v1, 13($s0)\n"
"addiu $v0, $v0, -1\n"
"sb $v0, 20($s0)\n"
"lbu $v0, 13($s0)\n"
"sb $a0, 28($s0)\n"
"sb $v1, 21($s0)\n"
"lbu $v1, 3($s2)\n"
"nop\n"
"addu $v0, $v0, $v1\n"
"lbu $v1, 20($s0)\n"
"addiu $v0, $v0, -1\n"
"sb $v0, 29($s0)\n"
"lbu $a0, 29($s0)\n"
"addiu $v0, $zero, 128\n"
"sb $v0, 6($s0)\n"
"sb $v0, 5($s0)\n"
"sb $v0, 4($s0)\n"
"sb $v1, 36($s0)\n"
"sb $a0, 37($s0)\n"
"lhu $v0, 16($sp)\n"
"lhu $v1, 24($sp)\n"
"nop\n"
"addu $v0, $v0, $v1\n"
"sh $v0, 8($s0)\n"
"lhu $v0, 18($sp)\n"
"lhu $v1, 26($sp)\n"
"nop\n"
"addu $v0, $v0, $v1\n"
"sh $v0, 10($s0)\n"
"lhu $v0, 8($s0)\n"
"lhu $v1, 32($sp)\n"
"nop\n"
"addu $v0, $v0, $v1\n"
"sh $v0, 16($s0)\n"
"lhu $v0, 10($s0)\n"
"lhu $a0, 34($sp)\n"
"sh $v0, 18($s0)\n"
"lhu $v0, 10($s0)\n"
"lhu $v1, 8($s0)\n"
"addu $v0, $v0, $a0\n"
"sh $v0, 26($s0)\n"
"sh $v1, 24($s0)\n"
"lhu $v0, 16($s0)\n"
"lhu $v1, 26($s0)\n"
"lui $a0, %hi(D_801BA6B0)\n"
"lbu $a0, %lo(D_801BA6B0)($a0)\n"
"sh $v0, 32($s0)\n"
"bnez $a0, .L80185F0C\n"
"sh $v1, 34($s0)\n"
"lbu $v0, 1($s2)\n"
"nop\n"
"addiu $v1, $v0, 256\n"
"sltiu $v0, $v0, 224\n"
"bnez $v0, .L80185F20\n"
"sll $v1, $v1, 6\n"
"j .L80185F24\n"
"ori $v0, $v1, 16\n"
".L80185F0C:\n"
"addiu $v0, $a0, 256\n"
"sll $v1, $v0, 6\n"
"sltiu $v0, $a0, 224\n"
"beqz $v0, .L80185F24\n"
"ori $v0, $v1, 16\n"
".L80185F20:\n"
"ori $v0, $v1, 22\n"
".L80185F24:\n"
"sh $v0, 14($s0)\n"
"lui $v0, 48\n"
"and $v0, $s3, $v0\n"
"lui $v1, 32\n"
"bne $v0, $v1, .L80185F50\n"
"lui $a1, 255\n"
"addu $a0, $t0, $zero\n"
"addiu $a1, $sp, 16\n"
"jal func_8001F730\n"
"addu $a2, $s0, $zero\n"
"lui $a1, 255\n"
".L80185F50:\n"
"ori $a1, $a1, 65535\n"
"lui $a2, 65280\n"
"lw $v1, 96($sp)\n"
"lw $a0, 0($s0)\n"
"sll $v1, $v1, 2\n"
"addu $v1, $v1, $s1\n"
"lw $v0, 4($v1)\n"
"and $a0, $a0, $a2\n"
"and $v0, $v0, $a1\n"
"or $a0, $a0, $v0\n"
"sw $a0, 0($s0)\n"
"lw $v0, 4($v1)\n"
"and $a1, $s0, $a1\n"
"and $v0, $v0, $a2\n"
"or $v0, $v0, $a1\n"
"sw $v0, 4($v1)\n"
".L80185F90:\n"
"lw $ra, 124($sp)\n"
"lw $s4, 120($sp)\n"
"lw $s3, 116($sp)\n"
"lw $s2, 112($sp)\n"
"lw $s1, 108($sp)\n"
"lw $s0, 104($sp)\n"
"addiu $sp, $sp, 128\n"
"jr $ra\n"
"nop\n"
".set\treorder\n.end\tfunc_80185810\n");




void func_80185FB4(s32 a0, s32 a1, s32 a2)
{
    extern MATRIX_80188114 D_800AE620;
    extern void func_80020DA4(s32 a0, s32 a1);
    extern void func_80020F34(s32 a0, s32 a1);

    if (a1 & 0x200000) {
        func_80020DA4(a0 + 0x10, a2);
    } else {
        *(MATRIX_80188114 *)a2 = D_800AE620;
    }

    if (a1 & 0x400000) {
        func_80020F34(a2, a0 + 0x18);
    }

    *(s32 *)(a2 + 0x14) = *(s16 *)(a0 + 0x8);
    *(s32 *)(a2 + 0x18) = *(s16 *)(a0 + 0xA);
    *(s32 *)(a2 + 0x1C) = *(s16 *)(a0 + 0xC);
}



extern void (*D_8018F114[])(void);

void func_80186094(void *a0) {
    D_8018F114[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8013373C(s16 arg0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern void func_80188BA8(s32 a0);

extern s32 D_8019CD2C;
extern s32 D_8018E9AC;
extern s32 D_8018EAB4;
extern s32 D_801BCBBC;
extern s16 D_8018EE04;
extern s16 D_8018EE02;
extern s16 D_8018EE00;

void func_801860D0(int param_1)
{
    s32 v1;
    s32 v0;
    u16 flags;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
        return;
    }
    func_8001C214(v0, (s32)&D_8019CD2C);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x7FFF, 0x7FFF);
    *(u16 *)(param_1 + 0x2) = 1;
    if ((u32)func_80029504() < 0x258u) {
        func_8013373C(0);
        func_8012A828(param_1, &D_8018E9AC);
        *(s32 *)(param_1 + 0x6C) = func_8012C588(0x1DE, param_1);
        func_8012C588(0x14D, param_1);
        v1 = *(s32 *)(param_1 + 0x20);
        flags = *(u16 *)(v1 + 0x2C);
        D_801BCBBC = 0;
        *(u16 *)(v1 + 0x2C) = flags | 0x80;
        v1 = *(s32 *)(param_1 + 0x20);
        *(s32 *)(v1 + 0x80) = (s32)&D_8018EE04;
        D_8018EE02 = 0xF0;
        D_8018EE00 = 0xF0;
    } else {
        func_8012A828(param_1, &D_8018EAB4);
        func_80188BA8(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801861DC);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018624C);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80186680);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018676C);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801867D0);


extern s32 func_80178B18(s32, s32);

void func_80186AE8(void *arg0) {

    extern M2C_UNK D_8018EFBC;
    ((void (*)(void *, void *))func_80178B18)(arg0, &D_8018EFBC);
    *(s16 *)((s32)arg0 + 0x2) = 0x7;
    *(s16 *)((s32)arg0 + 0x34) = 0;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80186B24);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80186D54);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80186DDC);

void func_80187038(void) {
}

extern s32 func_801896EC(s32 arg);
    void func_80187040(void) {
        func_801896EC(0x2);
    }


extern void func_80189718(void);
    void func_80187060(void) {
        func_80189718();
    }


extern s32 func_8012C588(s32 a0, s32 a1);
    void func_80187080(void *a0) {
        *(s32 *)((u8 *)a0 + 0xd0) = ((s32 (*)(s32, void *))func_8012C588)(0x217, a0);
    }


extern u16 D_8018EE0C[];
extern s16 D_8018EDFE;
extern s16 D_8018EDFC;
extern s32 D_801BCBBC;

void func_801870B4(void) {
    u16 v = D_8018EE0C[D_801BCBBC];
    D_8018EDFE = v;
    D_8018EDFC = v;
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801870E8);

#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s32 rand(void);
extern s32 func_8012C51C(void *a0, s32 a1);

/* Spawns arg1 "wide" particles then arg2 "low" particles through the shared
 * 0x14-byte spawn record `struct S80190C84` (src/shared/engine_types.h:1337):
 *   f0 = x offset, f2 = 0, f4 = y offset, f6 = 0x1F3 (gfx id),
 *   f8 = variant 1..3, fA = 0, fC = 0x7FFF, fE = 0, f10 = 0.
 * arg0 + 0x6C is the owner handle passed as func_8012C51C's second argument.
 *
 * NOTE (§76 / §156 allocno merge): the two loops MUST use SEPARATE temporaries.
 * Reusing one `t` across both loops merges the allocnos, and the death-merge
 * preference that rides along makes loop 2's raw rand() copy skip $v1 in
 * find_reg pass 0 and land in $a0 (8 mismatches). `t` + `u` = MATCH.
 * Loop 2's two temps DO share one variable (that pairing is byte-neutral). */

void func_801871C0(void *arg0, s32 arg1, s32 arg2) {
    struct S80190C84 sp;
    s32 i;
    s32 t;
    s32 u;

    sp.f6 = 0x1F3;
    sp.fA = 0;
    sp.fC = 0x7FFF;
    sp.fE = 0;
    sp.f10 = 0;
    sp.f2 = 0;

    for (i = 0; i < arg1; i++) {
        t = rand() % 496;
        sp.f0 = (rand() & 1) ? t : -t;
        sp.f4 = (rand() % 256) + 0x80;
        sp.f8 = (rand() % 3) + 1;
        func_8012C51C(&sp, *(s32 *)((s32)arg0 + 0x6C));
    }

    for (i = 0; i < arg2; i++) {
        u = rand() % 256;
        sp.f0 = (rand() & 1) ? u : -u;
        u = rand() % 16;
        sp.f4 = ((rand() & 1) ? u : -u) - 0xD0;
        sp.f8 = (rand() % 3) + 1;
        func_8012C51C(&sp, *(s32 *)((s32)arg0 + 0x6C));
    }
}


/* named key local + while-form tail ordering */
extern u8 D_801202A0[];

void func_801873C8(void) {
    register u8 *q __asm__("$4");
    u8 *p;
    s32 i;
    s32 count;
    s32 key;

    p = D_801202A0;
    count = 0;
    i = 0;
    key = 0x1F3;
    q = p + 0x1C;
    while (i < 0x60) {
        if (*(u16 *)p == key && (*(u16 *)(q + 0x54) & 0x2000)) {
            *(s32 *)q = count << 4;
            *(u16 *)(q + 0x18) += 1;
            count++;
        }
        i++;
        q += 0x10C;
        p += 0x10C;
    }
}


extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);

void func_80187434(void *a0)
{
    s32 buf[8]; /* sp+0x10 */
    s16 out[4]; /* sp+0x30 */
    s32 s0;

    s0 = func_80132EF4((s32)a0, 0x7A);
    if (s0 != 0) {
        out[1] = -0xC5;
        out[0] = 0;
        out[2] = 0x40;
        func_8012EC04((s32)a0, 6, buf);
        func_8012F14C((s32)buf, (s32)out, (s32)out);
        *(s16 *)((s32)s0 + 0x06) = out[0];
        *(s16 *)((s32)s0 + 0x0A) = out[1];
        *(s16 *)((s32)s0 + 0x0E) = out[2];
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x2C) = 0xC020;
    }
}


extern void (*D_8018F140)(void *);

void func_801874D0(void *a0)
{
    s32 buf[8];
    u16 out[4];
    s32 v1;

    func_8012EC04((s32)a0, 6, buf);
    func_8012F14C((s32)buf, (s32)&D_8018F140, (s32)out);

    v1 = *(s32 *)((s32)a0 + 0xCC);
    *(u16 *)(v1 + 0x6) = out[0];
    *(u16 *)(v1 + 0xA) = out[1] + 0x10;
    *(u16 *)(v1 + 0xE) = out[2];
}



extern s32 func_80187540(void *a0);
    s32 func_80187540(void *a0) {
        return *(s16 *)((char *)a0 + 0xfe) == 0x2;
    }


#include "common.h"



extern Vec8_8017E0B4 D_801BC9E0;
extern Vec8_8017E0B4 D_801BC9D8;
extern Vec8_8017E0B4 D_8018ED84;
extern Vec8_8017E0B4 D_8018ED8C;

extern void func_8018774C(void *a0);
extern void func_8012A018(s32 a, s32 b);
extern u8 D_8012694C;
extern s32 D_80126954;
extern s32 D_80126950;
extern s32 D_80126990;
extern s32 D_80126994;
extern s32 D_80126998;
extern s32 D_80126984;
extern s32 D_80126988;
extern s32 D_8012698C;
extern void func_80129CF8(void);

void func_80187554(void)
{
    D_801BC9E0 = D_8018ED84;
    D_801BC9D8 = D_8018ED8C;

    func_8012A018((s32)func_8018774C, 0);

    D_8012694C = 0;
    __asm__ __volatile__("");

    D_80126954 = 0x708;
    D_80126950 = 0x708;
    D_80126990 = D_801BC9E0.vx;
    D_80126994 = D_801BC9E0.vy;
    D_80126998 = D_801BC9E0.vz;
    D_80126984 = D_801BC9D8.vx;
    D_80126988 = D_801BC9D8.vy;
    D_8012698C = D_801BC9D8.vz;

    func_80129CF8();
}




extern Vec8_8017E0B4 D_801BC9E0;
extern Vec8_8017E0B4 D_801BC9D8;
extern s16 D_801BC9E2;
extern s16 D_801BC9E4;
extern s16 D_801BC9DA;
extern s16 D_801BC9DC;
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);

void func_80187668(s32 param_1) {
    *(s32 *)(param_1 + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x48), (s32)D_801BC9E0.vx, 0xC);
    *(s32 *)(param_1 + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x4C), (s32)D_801BC9E2, 0xC);
    *(s32 *)(param_1 + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x50), (s32)D_801BC9E4, 0xC);
    *(s32 *)(param_1 + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x3C), (s32)D_801BC9D8.vx, 0xC);
    *(s32 *)(param_1 + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x40), (s32)D_801BC9DA, 0xC);
    *(s32 *)(param_1 + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x44), (s32)D_801BC9DC, 0xC);
}



extern void (*D_8018F148[])(void);

void func_8018774C(void *a0) {
    D_8018F148[*(u8 *)((s32)a0 + 0x4)]();
}


extern void (*D_8018F14C[])(void);

void func_80187788(void *a0) {
    D_8018F14C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801B44A0;
extern s32 D_8018EA94;

void func_801877C4(s32 a0) {
    s32 v0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801B44A0);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    func_8012A828(a0, &D_8018EA94);
    *(u16 *)(a0 + 0x2) += 1;
}


void func_80187844(void) {
}

extern void (*D_8018F194[])(void);
extern void func_80187F7C(void);

void func_8018784C(void *a0) {
    D_8018F194[*(u16 *)((s32)a0 + 0x2)]();
    func_80187F7C();
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80187890);

#include "common.h"

extern void func_80187A30(void *a0, s32 a1, s32 a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80187928(void *a0) {
    func_80187A30(a0, *(s16 *)((s32)a0 + 0xFE), *(s16 *)((s32)a0 + 0x100));

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        if (func_8012BEE8((s32)a0) == 0) {
            *(u16 *)((s32)a0 + 0x102) = *(u16 *)((s32)a0 + 0x102) + 8;
            *(u16 *)((s32)a0 + 0x104) = *(u16 *)((s32)a0 + 0x104) + 8;
        }
        break;
    case 1: {
        s32 v0 = *(volatile u16 *)((s32)a0 + 0x34);
        *(s32 *)((s32)a0 + 0x1C) = 0x40;
        *(u16 *)((s32)a0 + 0x34) = v0 + 1;
        break;
    }
    case 2:
        if (func_8012BEE8((s32)a0) == 0) {
            *(u16 *)((s32)a0 + 0xFE) = *(u16 *)((s32)a0 + 0xFE) + 8;
            *(u16 *)((s32)a0 + 0x100) = *(u16 *)((s32)a0 + 0x100) + 8;
        } else {
            if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 2) == 9) {
                func_8002D4C8(4, 0x775);
            }
            func_8012C218(a0);
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80187A30);

extern u16 D_800B99DA;
extern u16 D_8018F154[];
extern s16 D_801BC9E8[];
extern s32 D_8018F174;
extern void func_800183E0(s32 a0);

void func_80187F7C(void) {
    u16 *src;
    s16 *dst;
    s32 i;
    s32 m;
    s32 w;
    s32 v;
    s32 pad[2];

    src = D_8018F154;
    i = 0;
    m = D_800B99DA & 0xF;
    dst = &D_801BC9E8[0xF - m];
    for (; i <= m; i++) {
        w = *src++;
        *dst++ = w | -0x8000;
    }
    dst = D_801BC9E8;
    if (15 - m > 0) {
        i = 0;
        do {
            v = *src++;
            *dst++ = v | -0x8000;
            i++;
        } while (i < 15 - m);
    }
    func_800183E0(&D_8018F174);
}



extern void (*D_8018F19C[])(void);

void func_80188040(void *a0) {
    D_8018F19C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_8018807C);

#include "common.h"

/* func_80188114 (ov_SC03_105, 198 ins) — MATCH, match_one relocation-masked.
 *
 * BANKING NOTES (STEP 6 pre-flight against src/ov_SC03_105/ov_SC03_105_jr_8017C8D0.c):
 *  - func_8012F14C / RotTransSV / func_800176F0 are declared EXACTLY as the TU already
 *    declares them (lines 329/3470, 2657, 4325) — copied verbatim, no change needed.
 *  - RotMatrixZ is absent from the TU; the fleet-modal ('void',('s32','void*')) is used.
 *  - D_800AF648 uses the fleet spelling `extern u8` (only its address is taken).
 *  - gte_ldv0 / gte_rtps / gte_stsxy / gte_stszotz / gte_stflg below are TOKEN-IDENTICAL
 *    to the TU's existing definitions (verified) so the redefinition is legal C; the
 *    banker may simply delete them. gte_SetRotMatrix / gte_SetTransMatrix are NEW to
 *    this TU (bodies verbatim from ov_SC03_099_jr_8012ACE0.c:833/847).
 *  - MATRIX_80188114 / SVECTOR_80188114 are layout-identical to the TU's shared MATRIX /
 *    SVECTOR (src/shared/engine_types.h:1168 / :997). They are spelled under local names
 *    ONLY because match_one compiles with -Iinclude alone and cannot reach
 *    ../shared/engine_core.h. ON BANKING: delete both typedefs and drop the "_80188114"
 *    suffix — same body, so the rename is byte-neutral (law 8 satisfied).
 *
 * Frame (0x98): prim@sp+0x10 (0x34 -> 0x38 stride, §193-I), m@sp+0x48, otz@sp+0x68,
 * flag@sp+0x78; saves $s0-$s3/$ra @0x80..0x93.  sp+0x78 is ONE variable: RotTransSV's
 * scratch out-arg and the GTE flag word (the target reads 0x78($sp) after cfc2).
 */

/* ---- PsyQ inline_c.h GTE macro bodies, verbatim (same spelling as the TU's
 *      func_8017BEBC block / ov_SC03_099_jr_8012ACE0.c). ------------------ */

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

/* Layout-identical to the TU's shared MATRIX / SVECTOR (src/shared/engine_types.h:
 *   typedef struct { short m[3][3]; long t[3]; } MATRIX;      -- 0x20
 *   typedef struct { short vx, vy, vz, pad; } SVECTOR;        -- 0x08
 * Spelled under local names here only because match_one compiles the draft with
 * -Iinclude alone and cannot reach ../shared/engine_core.h.  On banking, delete
 * these two typedefs and use the TU's MATRIX / SVECTOR verbatim (law 2/8: same
 * body, so the rename is byte-neutral). */

typedef struct { short vx, vy, vz, pad; } SVECTOR_80188114;

/* sp+0x10 aggregate handed to func_800176F0: 4 SVECTORs + 5 words. */
typedef struct {
    SVECTOR_80188114 v[4];   /* 0x00 */
    s32 f0;         /* 0x20 */
    s32 f1;         /* 0x24 */
    s32 f2;         /* 0x28 */
    s32 f3;         /* 0x2C */
    s32 f4;         /* 0x30 */
} Prim_80188114;

extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_800176F0(void *a0);
extern MATRIX_80188114 D_800AE620;
extern u8 D_800AF648;   /* fleet spelling (ov_SC03_099_jr_801380E0.c et al.); only its address is used */

void func_80188114(s32 param_1)
{
    Prim_80188114 prim;   /* sp+0x10 */
    MATRIX_80188114 m;             /* sp+0x48 */
    s32 otz[4];           /* sp+0x68 */
    s32 flag;             /* sp+0x78 */
    SVECTOR_80188114 *p;
    s32 i;
    s32 a, b, t;
    s16 h;

    t = *(s32 *)(param_1 + 0xE0) - 0x40;
    *(s32 *)(param_1 + 0xE0) = t;
    if (t < -0x300) {
        *(s32 *)(param_1 + 0xE0) = -0x300;
    }

    prim.v[0].vx = -0x10;
    prim.v[1].vx = 0x10;
    h = *(s32 *)(param_1 + 0xE0);
    prim.v[3].vz = 0;
    prim.v[2].vz = 0;
    prim.v[1].vz = 0;
    prim.v[0].vz = 0;
    prim.v[3].vx = 0;
    prim.v[2].vx = 0;
    prim.v[1].vy = 0;
    prim.v[0].vy = 0;
    prim.v[3].vy = h;
    prim.v[2].vy = h;

    m = D_800AE620;
    RotMatrixZ(-*(s16 *)(param_1 + 0xFE), &m);
    func_8012F14C((s32)&m, (s32)&prim.v[2], (s32)&prim.v[2]);

    m = D_800AE620;
    RotMatrixZ(*(s16 *)(param_1 + 0xFE), &m);
    func_8012F14C((s32)&m, (s32)&prim.v[3], (s32)&prim.v[3]);

    gte_SetRotMatrix((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    gte_SetTransMatrix((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

    RotTransSV(&prim.v[0], &prim.v[0], &flag);
    RotTransSV(&prim.v[1], &prim.v[1], &flag);
    RotTransSV(&prim.v[2], &prim.v[2], &flag);
    RotTransSV(&prim.v[3], &prim.v[3], &flag);

    gte_SetRotMatrix(&D_800AF648);
    gte_SetTransMatrix(&D_800AF648);

    for (i = 0, p = &prim.v[0]; i < 4; i++, p++) {
        gte_ldv0(p);
        gte_rtps();
        gte_stsxy(p);
        gte_stflg(&flag);
        gte_stszotz(&otz[i]);
        if (flag & ~0x1000) {
            return;
        }
    }

    a = otz[2];
    if (otz[3] < a) {
        a = otz[3];
    }
    b = otz[0];
    if (otz[1] < b) {
        b = otz[1];
    }
    if (a < b) {
        b = a;
    }
    prim.f0 = 0xC0C0C0;
    prim.f1 = 0xC0C0C0;
    prim.v[0].vz = b;
    prim.f2 = 0;
    prim.f3 = 0;
    prim.f4 = 0x50000000;
    func_800176F0(&prim);
}



// @stuck: none — MATCH (42 ins), iteration 1, rtu_match clean.
// Saturating add of a 3-byte RGB triple by a signed delta.
// Idioms: (1) `s8` by-value param => entry `sll/sra 24` for the sign test only;
//   combine folds the extension back out of `~a1`/`-a1`/`a0[i]+a1` because every
//   consumer is 8-bit (andi 0xFF / sb), so $a1 is used RAW after the test.
// (2) branch sense read off the target `sltu` operand ORDER (§3-T4): positive arm
//   `sltu lim,p[i]` => store when `p[i] <= lim`; negative arm `sltu p[i],lim`
//   => store when `p[i] >= lim`.
// (3) the third `if` written out in BOTH arms; jump.c cross-jumps the identical
//   tails into the shared `j .L8018C344` (§5a) — do not hoist it after the if/else.
void func_8018842C(u8 *a0, s8 a1) {
    u8 lim;

    if (a1 == 0) {
        return;
    }
    if (a1 > 0) {
        lim = ~a1;
        if (a0[0] <= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] <= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] <= lim) {
            a0[2] = a0[2] + a1;
        }
    } else {
        lim = -a1;
        if (a0[0] >= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] >= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] >= lim) {
            a0[2] = a0[2] + a1;
        }
    }
}



extern void (*D_8018F1A4[])(void);

void func_801884D4(void *a0) {
    D_8018F1A4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80188510);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018854C(u8 *a0) {
        *(s8 *)(a0 + 0xFC) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((s32)a0, 0x2);
    }


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80188574);


extern void (*D_8018F1AC[])(void);

void func_80188650(void *a0) {
    D_8018F1AC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018F248[])(void);

void func_8018868C(void *a0) {
    D_8018F248[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8001CD9C(int, void *);

extern M2C_UNK D_8018F1CC;
extern u16 D_8018F200;
extern u16 D_8018F202;
extern u16 D_8018F204;
extern u8 D_8018F208;
extern u8 D_8018F209;
extern u8 D_8018F20A;
extern s32 D_801BCA48;

void func_801886C8(s32 a0) {
    extern s32 func_8012C438(s32 a0, s32 a1);
    extern s32 func_8012C194(void);
    extern void func_8012B260(u8 *a0);

    s32 v0;

    if (func_8012C438(a0, (s32)&D_8018F1CC)) {
        u16 *pFlag = &D_8018F200;

        *pFlag = 0x80;
        D_8018F202 = 0x80;
        D_8018F204 = 0x80;
        *(void **)(*(s32 *)(a0 + 0x20) + 0x80) = pFlag;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x80;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x8000;

        v0 = func_8012C194();
        D_801BCA48 = v0;
        if (v0 != 0) {
            u8 *ptr = (u8 *)&D_8018F208;

            func_8001CD9C((int)v0, (void *)ptr);
            *(u16 *)(D_801BCA48 + 0x2C) = 0xC010;
            *(u16 *)(D_801BCA48 + 0x1A) = 0x800;
            *(u16 *)(D_801BCA48 + 0x18) = 0x800;
            *(s32 *)(D_801BCA48 + 0x4) |= 0x50000000;
            *ptr = 0;
            D_8018F209 = 0;
            D_8018F20A = 0;
        }

        if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
            *(s32 *)(a0 + 0x18) = 0xFFFE0000;
            *(s32 *)(a0 + 0x48) = 0x4000;
            *(s16 *)(a0 + 0x6) = -0x3D;
            *(s16 *)(a0 + 0xA) = -0x166;
            *(s16 *)(a0 + 0xE) = -0xB0;
            func_8012B260((u8 *)a0);
            *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
        } else {
            *(u16 *)(a0 + 0x2) = 2;
            *(s16 *)(a0 + 0xAE) = -3;
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80188828);

extern s16 D_8018EE00;
extern s32 D_8018F254;

void func_801889D4(s32 arg0)
{
    s32 buf[8];
    u16 out[4];
    s16 *ptr;

    if (*(s16 *)((s32)arg0 + 0x100) != 0) {
        func_80188B64(arg0);
        return;
    }
    func_8012EC04(*(s32 *)((s32)arg0 + 0x64), 6, buf);
    func_8012F14C((s32)buf, (s32)&D_8018F254, (s32)out);
    *(u16 *)((s32)arg0 + 0x6) = out[0];
    *(u16 *)((s32)arg0 + 0xA) = out[1];
    *(u16 *)((s32)arg0 + 0xE) = out[2];
    func_80188A94(arg0);
    if ((*(u16 *)((s32)arg0 + 0x5C) & 1) == 0) {
        return;
    }
    func_8002D4C8(0xBC1, 0);
    func_8016B3F4(arg0);
    ptr = &D_8018EE00;
    *ptr = *ptr - 0x50;
    func_80188B64(arg0);
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80188A94);

INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_80188B64);

extern s32 D_8018F25C[];

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80188BA8(s32 a0) {
    s32 i = 0;

    if (D_8018F25C[0] != -1) {
        do {
            s32 t = D_8018F25C[i] | 0x4000;
            func_8012C658(0x1F3, (i << 4) | t, a0);
            i++;
        } while (D_8018F25C[i] != -1);
    }
}



/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);


/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference, so the TU's `extern memcpy` cannot turn
 * this into a CALL.  (house idiom, cf. func_8017B238 / func_8017B614) */

void func_80188C34(s32 param_1)
{

    extern u8 D_801BCA08;
    extern u8 D_801BCA0C;
    extern u8 D_801B82E0;
    extern u8 D_801B82E4;
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801BCA08);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x10;

    func_800233CC(&D_801BCA08, 0x10);

    *(Blk4_8018CE04_80188C34 *)&D_801BCA08 = *(Blk4_8018CE04_80188C34 *)&D_801B82E0;
    *(Blk4_8018CE04_80188C34 *)&D_801BCA0C = *(Blk4_8018CE04_80188C34 *)&D_801B82E4;

    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1E) = 0xC00;
    *(u16 *)(param_1 + 2) += 1;
}


extern u8 D_801BCA0C;
extern void func_800233CC(void *, unsigned short);
extern void func_801292C8(void);
extern void func_8018842C(u8 *a0, s8 a1);

void func_80188D10(void *param_1)
{
    s16 sp18;
    u8 *s0;

    sp18 = *(s16 *)((s32)param_1 + 0x2C);
    if (sp18 < 0x700) {
        s0 = &D_801BCA0C;
        *(s16 *)((s32)param_1 + 0x2C) = sp18 + 0x30;
        func_8018842C(s0, -4);
        func_800233CC(s0 - 4, *(u16 *)((s32)param_1 + 0x2C));
    } else {
        ((void (*)(u8 *))func_801292C8)(param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80188510(s32 a0);

extern u8 D_801B59D8;
extern u8 D_801B6188;

void func_80188D88(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801B59D8);

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        v0 = *(s32 *)(param_1 + 0x20);
        *(s16 *)v0 = 0;
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801B6188);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u8 *)(param_1 + 0xC0) = 0;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x90;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) = param_1 + 0xFC;

    *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0xCC) + 0x2C) |= 0x90;
    *(s32 *)(*(s32 *)(param_1 + 0xCC) + 0x80) = param_1 + 0xFC;

    *(s16 *)(param_1 + 0xFC) = 0x100;
    *(s16 *)(param_1 + 0xFE) = 0x100;
    *(s16 *)(param_1 + 0x100) = 0x100;
    *(s16 *)(param_1 + 0x102) = -2;

    func_80188510(param_1);
}


#include "common.h"

extern void func_8018854C(u8 *a0);

void func_80188EAC(s32 param_1)
{
    s32 a1;
    u16 v0;
    u16 v1;

    a1 = *(s32 *)(param_1 + 0xCC);
    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    if (v1 < 0x5000) {
        s32 p20;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = v1 + 0x100;

        p20 = *(s32 *)(param_1 + 0x20);
        v1 = *(u16 *)(p20 + 0x18);
        *(u16 *)(p20 + 0x1C) = v1;
        *(u16 *)(p20 + 0x1A) = v1;

        v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = v0 + 0x100;

        *(u16 *)(a1 + 0x12) = *(u16 *)(a1 + 0x12) - 0x100;

        *(u16 *)(a1 + 0x8) = *(u16 *)(param_1 + 0x6) + *(u16 *)(param_1 + 0x50);
        *(u16 *)(a1 + 0xA) = *(u16 *)(param_1 + 0xA) + *(u16 *)(param_1 + 0x52);
        *(u16 *)(a1 + 0xC) = *(u16 *)(param_1 + 0xE) + *(u16 *)(param_1 + 0x54);

        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A);
        *(u16 *)(a1 + 0x1C) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1C);
    } else {
        func_8018854C((u8 *)param_1);
    }
}


void func_80188FA4(s32 param_1)
{
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
    {
        u8 v0 = *(u8 *)(param_1 + 0xFC) + 0x10;
        *(u8 *)(param_1 + 0xFC) = v0;
        if (v0 >= 0xF1) {
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x80000000;
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) += 1;
        }
        break;
    }
    case 1:
        if (func_8012BEE8(param_1) != 0) {
            func_80188574(param_1);
        }
        break;
    }

    func_80016450(*(u8 *)(param_1 + 0xFC), 0);
}


void func_80189074(u8 *arg0)
{
    s32 temp_a0;
    u8 var_v1;

    temp_a0 = arg0[0xFC] - 3;
    var_v1 = temp_a0;
    arg0[0xFC] = temp_a0;
    if (var_v1 >= 9) {
        func_80016450(var_v1, 0);
    } else {
        func_8012C218(arg0);
    }
}


extern void func_8013B7F4(s32 arg0, s32 arg1);
extern s32 D_8018F2F0[];

void func_801890C8(s32 param_1)
{
    func_8013B7F4(D_8018F2F0[param_1], 0);
}


extern void func_80189118(void);
void func_801890F8(void) {
    func_80189118();
}


#include "common.h"

extern s32 D_801BCC94;
extern s32 D_801BCA50;
extern s32 D_801BCA54;
extern s32 D_801BCA58;
extern s32 D_801BCA5C;

extern s16 D_801B6190[];
extern s32 D_8018F2B0[];

extern void func_80189254(void *a0, s32 a1);
extern void func_800183E0(s32 a0);

void func_80189118(void) {
    switch (D_801BCC94) {
    case 0:
        D_801BCA50 = 1;
        D_801BCA54 = 0;
        D_801BCA58 = 1;
        D_801BCA5C = 1;
        D_801BCC94 = 1;
        break;
    case 1:
        if (--D_801BCA50 == 0) {
            D_801BCA50 = 2;
            func_80189254(D_801B6190, D_801BCA54 * 6);
            D_801BCA54 = (D_801BCA54 + 1) & 7;
        }
        if (--D_801BCA58 == 0) {
            D_801BCA58 = 8;
            func_800183E0(D_8018F2B0[D_801BCA5C]);
            D_801BCA5C = (D_801BCA5C + 1) & 0xF;
        }
        break;
    }
}



void func_80189254(void *a0, s32 a1)
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




















s32 func_801892B4(s32 arg0)
{
  s32 ret;
 ret = 0x4B; if (0x258 > arg0) { ret = 0x2E;
  }
  else
  {
  }
  return ret;
}



extern void (*D_8018F314[])(void);

void func_801892CC(void *a0) {
    D_8018F314[*(u16 *)((s32)a0 + 0x2)]();
}




s32 func_80189308(void *a0, s32 *p) {
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



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018F304;

void func_80189350(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018F304;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


extern s32 D_8018F2F4;
extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);

void func_801893BC(void *a0) {
    if (func_80029504() == 0x258) {
        if ((func_80029178(0x132) & 0xFF) == 0) {
            *(s32 *)((s32)a0 + 0xDC) = func_80189308(a0, &D_8018F2F4);
        }
    }
}



extern void (*D_8018F490[])(void);

void func_80189418(void *a0) {
    D_8018F490[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);



void func_80189454(void *a0) {

    extern s16 D_8018F31C[][2];
    extern u8 D_8018F348[];
    extern EffectSlot4_80189454 D_8018F354[];
    extern u8 D_8018F380[];
    extern EffectSlot4_80189454 D_8018F3B8;
    extern EffectSlot4_80189454 D_8018F3E0;
    extern EffectSlot4_80189454 D_8018F3E4;
    extern EffectSlot4_80189454 D_8018F414;
    extern EffectSlot4_80189454 D_8018F418;
    extern EffectSlot4_80189454 D_8018F448;
    extern EffectSlot4_80189454 D_8018F44C;
    extern EffectSlot4_80189454 D_8018F47C;
    extern EffectSlot4_80189454 D_8018F480;
    register void *s0 __asm__("$16");
    register void *s1 __asm__("$17");

    s0 = a0;
    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)s0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)s0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_8018F380, D_8018F31C[idx][0], D_8018F31C[idx][1]);
        uVar1 = D_8018F348[*(s32 *)((s32)s0 + 0x2C)];
        *(s16 *)((s32)s1 + 0x2C) = 3;
        *(u8 *)((s32)s1 + 0x27) = uVar1;
        *(s16 *)((s32)s0 + 0x6) = 0;
        *(s16 *)((s32)s0 + 0xA) = 0x50;

        /* The shift chain below needs a BASIC-BLOCK BOUNDARY before every copy
           except the first: gcc-2.7.2 CSE is per-extended-BB, and inside one BB
           it reuses the previous copy's DESTINATION address register as the next
           copy's SOURCE address (costing the lui/addiu pair the target emits).
           `if (c) X else X` supplies the boundary and is cross-jumped away by
           jump2 AFTER regalloc, so it costs 0 instructions (128/128).

           The FIRST copy must stay in block 1 with the `lw 0x2C` / `li 0x50`
           pair, or the index pseudo crosses a block and becomes a GLOBAL allocno
           (regalloc map K8) -- local-alloc then hands $v0 to the 0x50 constant
           and global-alloc is left with $v1 (the REGALLOC-PERM $v0<->$v1 swap).
           Both must be LOCAL qtys in the same block for the target's assignment.
           Its destination is therefore spelled as an INTERIOR ADDRESS of the
           neighbouring symbol (idiom 7): `&D_8018F47C + 4 == &D_8018F480`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)s0 + 0x2C) > 0)
        *(EffectSlot4_80189454 *)((s32)&D_8018F47C + 4) = D_8018F354[*(s32 *)((s32)s0 + 0x2C)];
        if (COND) { D_8018F47C = D_8018F480; } else { D_8018F47C = D_8018F480; }
        if (COND) { D_8018F44C = D_8018F47C; } else { D_8018F44C = D_8018F47C; }
        if (COND) { D_8018F448 = D_8018F44C; } else { D_8018F448 = D_8018F44C; }
        if (COND) { D_8018F418 = D_8018F448; } else { D_8018F418 = D_8018F448; }
        if (COND) { D_8018F414 = D_8018F418; } else { D_8018F414 = D_8018F418; }
        if (COND) { D_8018F3E4 = D_8018F414; } else { D_8018F3E4 = D_8018F414; }
#undef COND
        D_8018F3E0 = D_8018F3E4;
        D_8018F3B8 = D_8018F3E0;

        *(s16 *)((s32)s0 + 0x2) = *(s16 *)((s32)s0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(s0);
    }
}


extern s32 func_80189694(void);
    void func_80189654(void) {
        func_80189694();
    }


extern void func_80146C3C(void);
    void func_80189674(void) {
        func_80146C3C();
    }



extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);

void aF80189694(void) __asm__("func_80189694");
void aF80189694(void)
{

    extern u8 D_8018F398[];
    extern u8 D_8018F3C0[];
    u8 *p;
    s32 i;

    func_80017254(D_8018F398);
    i = 0;
    p = D_8018F3C0;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


INCLUDE_ASM("asm/ov_SC03_105/nonmatchings/ov_SC03_105_jr_8017C8D0", func_801896EC);


extern s32 func_8014C050(s32 a0, s32 a1);

void func_80189718(void) {

    extern s32 D_80126B58;
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void (*D_801B68D0[])(void);

void func_8018975C(void *a0) {
    D_801B68D0[*(u16 *)((s32)a0 + 0x2)]();
}
