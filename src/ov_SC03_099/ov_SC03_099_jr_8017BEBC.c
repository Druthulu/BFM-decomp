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
extern u8 D_80185958;
extern u8 D_801858C8;
extern u8 D_801858A4;
extern u8 D_80185880;
extern u8 D_80185934;
extern u8 D_80185910;
extern u8 D_801858EC;
extern u8 D_8018585C;
extern void func_80145934(void);
extern u8 D_801859E8;
extern u8 D_801859C4;
extern u8 D_801859A0;
extern u8 D_8018597C;
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
extern unsigned char D_80184DE0[];
extern unsigned char D_80184E10[];
extern unsigned char D_80184E60[];
extern unsigned char D_80184E90[];
extern unsigned char D_80184EC0[];
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
extern void (*D_80184F10[])(void *);
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
extern s32 D_80184FD8[];
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
extern u8 D_80185060[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80185068;
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
extern int D_801BDFF0;
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
extern s32 D_801BDFF4;
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
extern s32 D_80185098;
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
extern void (*D_80185140[])(void);
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
extern void (*D_80185164[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80185154;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80185178[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80185184[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80185194[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801851AC[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018519C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801851C0[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801851DC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801851CC;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801851F0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80185204[])(void);
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
extern s32 D_80185218;
extern void (*D_80185240[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80185220;
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
extern int (*D_8018528C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80185290[])(void);
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
extern unsigned short D_801856F4[];
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
extern void (*D_80185704[])(void);
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
extern int D_801BE028;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018572C[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018570C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018571C;
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
extern void (*D_8018576C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80185774[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80185740;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80185780[])(void);
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
extern u8 D_80185750;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801BE030;
extern s32 D_801BE03C;
extern s32 D_801BE040;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801857BC[])(s32 *);
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
extern s32 D_80185790[];
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
extern s32 D_801BE038;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80185A0C[])(void);
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
extern char D_8018582C[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80185AB0[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80185C04[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80185A20;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80185C0C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80185A30;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80185A50;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80185C14[])(void);
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
extern void (*D_80185C3C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80185C48[])(void);
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
extern void (*D_80185ABC[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80185CEC;
extern void func_8015D380(s32 a0);
extern unsigned char D_80184DD0[];
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
extern unsigned char D_80185D00[];
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
extern s8 D_80185D3C[];
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
extern u16 D_80185D84;
extern u16 D_80185D86;
extern u16 D_80185D88;
extern s32 D_80185D8C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80185D94;
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
extern int D_80185AA0;
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
extern unsigned int D_80185E18[];
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
extern void (*D_80185EC8[])(void);
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
extern u16 D_80185EF8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80185F5C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801BE048[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80185F80[])(void);
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
extern int D_801BE0A0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80185FC8[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80185FB8;
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
extern char D_801BD8D4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80185FD0[])(void);
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
extern void (*D_80186024[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80185FEC;
extern s16 D_80186020;
extern s16 D_8018601E;
extern s16 D_8018601C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80186030[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801BE100;
extern u8 D_801BE101;
extern u8 D_801BE102;
extern u8 D_801BE103;
extern u8 D_801BE104;
extern u8 D_801BE105;
extern u8 D_801BE106;
extern u8 D_801BE107;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80186040[])(void);
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
extern s32 D_801BE140;
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
extern void (*D_80186084[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80186100[];
extern s32 D_80186120[];
extern u8 D_8018619C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801861BC[];
extern u8 D_801861DC[];
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
extern void (*D_80186278[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801862F4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801BD8E4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80186300[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80186308[])(void);
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
extern void (*D_801863D0[])(void);
extern void func_80166618(void *a0);
extern void (*D_801863E0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801863F0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801863FC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018635C[];
extern u8   D_80186370[];
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
extern void (*D_80186414[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018641C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80186424[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018642C[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80186434[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018643C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80186444[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801864F8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80186500[])(void);
extern void func_80169F00(void *a0);
extern char D_801864B0[];
extern char D_80186470[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80186538[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80186544[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018658C[])(void);
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
extern void (*D_80186608[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801BE460;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801865FC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80186640[];
extern unsigned short D_80186648[];
extern unsigned short D_80186650[];
extern unsigned char D_801BE468[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801BE460;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80186658[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801BE59C;
extern M2C_UNK D_801BE5A0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801BE528;
extern void (*D_80186688[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801BE5A4[];
extern u8 D_801BE5AC[];
extern u8 D_801BE55C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80186690[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801866AC[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801866B4[])(void);
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
extern void (*D_8018671C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801866C0;
extern u8 D_801866CC;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80186750[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80186758[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801867AC[])(void);
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
extern u16 D_801867E0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801867D0[];
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
extern s32 D_801867FC;
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
extern void (*D_80186874[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018687C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80186884[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018688C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80186894[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018689C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801868A8[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801868B4[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801868C0[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801868D0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801868E0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801868E8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801868F0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801868F8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80186900[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80186908[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80186910[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80186918[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80186920[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80186928[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80186930[])(void);
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
extern void (*D_80186938[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80186940[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80186948[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80186950[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80186958[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80186960[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80186968[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80186970[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80186978[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80186980[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80186988[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80186990[])(void);
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
extern void (*D_801869D4[])(void);
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
extern M2C_UNK D_80186998;
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
extern void (*D_80186A04[])(void);
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
extern void (*D_80186A40[])(void);
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
extern s32 D_80126950;
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80186A98[])();
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
extern void (*D_80186AA8[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80186AB0[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80186C18[])();
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
extern void (*D_80186C24[])();
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
extern M2C_UNK D_801BDB2C;
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
extern s16 D_801BF3E8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801BECE0;
extern short D_801BF45C;
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
extern s32 D_801BF10C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801BF134;
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
extern s16 D_801BF0F0;
extern s32 func_8017A3B0(void);
extern short D_801BF12C;
extern short D_801BF128;
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
extern s16 D_801BF0F4;
extern u16 D_801BF174;
extern u16 D_801BF176;
extern u16 D_801BF178;
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
extern s16 D_801BF16C;
extern s16 D_801BF16E;
extern s16 D_801BF170;
extern s16 D_801BF164;
extern s16 D_801BF166;
extern s16 D_801BF168;
extern void func_8017B7A8(void);
extern s16 D_801BF184;
extern s16 D_801BF186;
extern s16 D_801BF188;
extern s16 D_801BF18C;
extern s16 D_801BF18E;
extern s16 D_801BF190;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801BF17C;
extern short D_801BF17E;
extern short D_801BF180;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801BF114;
extern SV4 D_801BF11C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801BF13C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801BF138)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80186E00[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
/* ==== end §8b carried decl layer ==== */

/* func_8017BEBC — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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










#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )






#include "../shared/ov/func_8017BEBC__t67f11bf2.h"



extern int func_8017D4FC(int param_1);

void func_8017CD9C(void) {

    extern const void D_80187008;
    extern const void D_801871D4;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = (u8 *)&D_80187008;
    D_801274CC = (void *)&D_801871D4;
    func_8017D4FC(0);
}



extern int func_8017D4FC(int param_1);

void func_8017CDDC(void)
{

    extern u8 D_801871E8[];
    extern u8 D_80187328[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = D_801871E8;
    D_801274CC = D_80187328;
    func_8017D4FC(1);
}



extern void (*D_80186EAC[])(void);

void func_8017CE1C(void *a0) {
    D_80186EAC[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D04C(void);
extern void func_800167B8(s32 a0);

#include "../shared/ov/func_8017CE58__39613891.h"



extern s32 func_800167F0(s32 a0);

s32 func_8017CE9C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017D074(void);

#include "../shared/ov/func_8017CEC0__1f615c3a.h"



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017CF00(u8 *a0) {
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
void func_8017CF7C(void) {
    func_800D1EBC();
}



extern void (*D_80186EC0[])(void);

void func_8017CF9C(void *a0) {
    D_80186EC0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017CFD8(s32 a0) {
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D04C(void) {

    extern s32 D_80186ECC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80186ECC, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D074(void) {

    extern s32 D_80186ED0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80186ED0, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D1D0(void *a0);

void func_8017D09C(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x1F4;
    D_8012695C = 0x4b0;
    D_80126968 = 0x2aa;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D1D0, 0);
    func_8012A094((s32)D_80126948);
    func_8017D1D0(D_80126948);
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D1D0(void *a0);

void func_8017D134(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x1F4;
    D_8012695C = 0x4b0;
    D_80126968 = 0x155;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x50;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D1D0, 1);
    func_8012A094((s32)D_80126948);
    func_8017D1D0(D_80126948);
}



extern void (*D_80186ED4[])(void);

void func_8017D1D0(void *a0) {
    D_80186ED4[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017D364(s32 param_1, s16 *param_2);

void func_8017D20C(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80186EDC[];
    extern Blk8_80126940_8017D20C D_80126940;
    Blk8_80126940_8017D20C sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80186EDC[t];
    }
    sp10 = D_80126940;
    func_8017D364(a0, sp10.v);
}


#include "common.h"



extern u16 func_80148800(s32 *a0);
extern void func_8017D364(s32 param_1, s16 *param_2);

void func_8017D2AC(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80186EE0[];
    extern Blk8_80126940_8017D20C D_80126940;
    Blk8_80126940_8017D20C sp10;
    u8 t;
    s16 lim;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80186EE0[t];
    }
    sp10 = D_80126940;
    lim = -0x180;
    if (sp10.v[1] > lim) {
        s32 v4 = -0x180;
        sp10.v[1] = v4;
    }
    func_8017D364(a0, sp10.v);
}



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

void func_8017D364(s32 param_1, s16 *param_2) {
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



extern void func_8013B7F4(void *a0, int a1);

int func_8017D4FC(int param_1)
{

    extern unsigned char D_80186F24[];
    int iVar1;
    iVar1 = *(int *)(D_80186F24 + param_1 * 4);
    func_8013B7F4((void *)iVar1, 0);
}


extern s32 func_8017D54C();
    s32 func_8017D52C(void) {
        return func_8017D54C();
    }


extern s16 D_8019808C[];
extern s32 D_80186EE4[];
extern s32 D_801BF198;
extern s32 D_801BF19C;
extern s32 D_801BF1A0;
extern s32 D_801BF1A4;
extern s32 D_801BF3D4;
extern void func_800183E0(s32 a0);
extern void func_8017D688(void *a0, s32 a1);

s32 func_8017D54C(void)
{
    switch (D_801BF3D4) {
    case 0:
        D_801BF198 = 1;
        D_801BF19C = 0;
        D_801BF1A0 = 1;
        D_801BF1A4 = 1;
        D_801BF3D4 = 1;
        break;
    case 1:
        if (--D_801BF198 == 0) {
            D_801BF198 = 2;
            func_8017D688(D_8019808C, D_801BF19C * 6);
            D_801BF19C = (D_801BF19C + 1) & 7;
        }
        if (--D_801BF1A0 == 0) {
            D_801BF1A0 = 8;
            func_800183E0(D_80186EE4[D_801BF1A4]);
            D_801BF1A4 = (D_801BF1A4 + 1) & 0xF;
        }
        break;
    }
}



void func_8017D688(void *a0, s32 a1)
{
    s32 offset;
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




s32 func_8017D6E8(void) {

    extern s32 D_8012704C;
    if (D_8012704C == 0) {
        return 0x34;
    }
    return 0x46;
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   D_80126B62     TU:1793/4533  `extern u16` -> cast to s16* at the use site (`lh`)
 *   D_80126B96     TU:3758/4695/5189/5269  `extern u16`
 *   func_8012DEB8  TU:5081/5147/5266/5315  `s32 (s32,s32,s32)`
 *   func_8012BD14  TU:3986                 `s32 (s32)`
 * D_80198540 / D_80198568 / D_80198590 are 20-entry `.short` tables in
 * asm/ov_SC02_026/data/tail.data.s:40884/40909/40934 (loads are `lhu` -> u16).
 * D_801985B8 is the 2-entry fn-ptr table right after them (func_80180A4C /
 * func_80180AF0); same `void (*[])(...)` form as D_801A9EB8 (TU:3653).
 * func_8002D59C is declared nowhere in this TU. */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BD14(s32 a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_8017D708(s32 a0) {

    extern u16 D_80126B62;
    extern u16 D_80126B96;
    extern u16 D_80198540[];
    extern u16 D_80198568[];
    extern u16 D_80198590[];
    extern void (*D_801985B8[])(s32);
 /* 8 bytes */

    V4_8017FAC0_8017D708 p1;
    V4_8017FAC0_8017D708 p2;
    s32 i;
    s32 t;
    s32 y;
    s32 ret;

    t = *(s16 *)(a0 + 0xA) + 0x20;
    y = *(s16 *)&D_80126B62 - t;
    if (y < -0x110) {
        y = -0x110;
    } else if (y > 0) {
        y = 0;
    }
    p1.y = y;
    p2.y = y;

    for (i = 0; i < 20; i += 4) {
        p1.x = D_80198540[i];
        p1.z = D_80198540[i + 1];
        p2.x = D_80198540[i + 2];
        p2.z = D_80198540[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_80198568[i];
        p1.z = D_80198568[i + 1];
        p2.x = D_80198568[i + 2];
        p2.z = D_80198568[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_80198590[i];
        p1.z = D_80198590[i + 1];
        p2.x = D_80198590[i + 2];
        p2.z = D_80198590[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }

    D_801985B8[*(u16 *)(a0 + 0x2)](a0);

    ret = func_8012BD14(a0);
    if (ret > 0x3FFFF) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8002D59C(4, 0x609, *(u16 *)(a0 + 0x70));
    } else {
        *(s16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - 1;
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(a0 + 0xFE) = 4;
            func_8002D59C(0x609, ((0x40000 - ret) * 127) / 0x40000 | 0x1000,
                          *(u16 *)(a0 + 0x70));
        }
    }
}



/* func_8017D9A0 -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * TU-verbatim decls (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c):
 *   extern u8 D_801202A0[];                                     (line 387, 586)
 *   extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);   (line 592)
 *   extern s32 func_80047948(s32 a0);                           (line 2206)
 *   extern s32 func_8004787C(s32 a0);                           (line 2207)
 * Not in this TU: func_8012B6D4 (fleet-standard sig), D_80198604 (2-entry fn-ptr
 * table in ov_SC02_026 tail.data: func_80180B0C / func_80180B90).
 */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_8017D9A0(void *arg0) {

    extern u8 D_801202A0[];
    extern void (*D_80198604[])(void *);
                 /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
                /* stride 0x10C, 0x60 entries (0x6480) */

    /* Two further V4 slots the original body declared ahead of `pos` but that
     * this function never reads: the target frame is 0x50 with locals at
     * 0x10..0x37 and the first live vector at 0x20, i.e. 0x10 bytes of stack
     * precede `pos`. Dropping them yields a 0x40 frame and shifts every sp
     * displacement by 0x10 (36 mismatches). */
    V4_8017FD58_8017D9A0 unused[2];
    V4_8017FD58_8017D9A0 pos;
    V4_8017FD58_8017D9A0 tmp;
    V4_8017FD58_8017D9A0 dst;
    Ent_8017FD58_8017D9A0 *p;
    Ent_8017FD58_8017D9A0 *e;
    s32 i;
    s32 ang;

    p = (Ent_8017FD58_8017D9A0 *)arg0;
    D_80198604[p->f2](p);
    e = (Ent_8017FD58_8017D9A0 *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0x12C) {
            pos.x = e->x;
            pos.y = e->y;
            pos.z = e->z;
            ang = func_8012B6D4((s16 *)&p->f4, (s16 *)&e->f4);
            if (*(s16 *)(p->f64 + 0xFC) < 0) {
                ang -= 0x400;
            } else {
                ang += 0x400;
            }
            ang &= 0xFFF;
            pos.x -= func_8004787C(ang) >> 8;
            pos.z -= func_80047948(ang) >> 8;
            tmp.x = e->x;
            tmp.y = e->y;
            tmp.z = e->z;
            dst = tmp;
            if (func_80135888(p->f20, p->f58, (s32)&pos, (s32)&dst) != 0) {
                e->x = pos.x;
                e->z = pos.z;
            }
        }
    }
}


#include "common.h"

void func_8017DB28(s32 a0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8012B23C(void *a0);
    extern u16 D_801988A8[];
    extern u16 D_801988AA[];
    extern u16 D_801988AC[];
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, s32 a1);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern s32 rand(void);

    extern u8 D_8019860C[];
    extern u8 D_801986CC[];
    extern u8 D_80198754[];
    extern u8 D_80198814[];
    extern u8 D_801988F8[];
    extern u8 D_8019891C[];
    extern u8 D_801985D0[];
    extern u8 D_80198908[];
    extern u8 D_80198914[];

    s32 v0;
    s16 sVar1;
    u32 uVar3;
    u32 uVar5;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8012B23C((void *)a0);
    *(u16 *)(a0 + 0x12) = D_801988A8[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x16) = D_801988AA[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x1A) = D_801988AC[*(s16 *)(a0 + 0xFC) * 4];
    switch (*(s16 *)(a0 + 0x70)) {
    case 0:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_8019860C);
        func_8012A828(a0, (s32)D_801986CC);
        *(s16 *)(a0 + 2) = 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 1:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_80198754);
        func_8012A828(a0, (s32)D_80198814);
        *(s16 *)(a0 + 2) = 4;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s32 *)(a0 + 0x1C) = 8;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(u8 *)(a0 + 0xC0) = 1;
        *(u8 **)(a0 + 0x58) = D_801988F8;
        *(u16 *)(a0 + 0x5C) = 0x8000;
        *(s16 *)(a0 + 0xAE) = -9;
        *(u8 **)(a0 + 0xBC) = D_8019891C;
        *(u32 *)(a0 + 0xB4) = 0;
        *(u8 **)(a0 + 0x78) = D_801985D0;
        *(u32 *)(a0 + 0xC4) |= 2;
        uVar3 = func_8012C658(0x12F, 4, a0);
        *(u32 *)(a0 + 0xCC) = uVar3;
        break;
    case 2:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_8019860C);
        func_8012A828(a0, (s32)D_801986CC);
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 3:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_80198754);
        func_8012A828(a0, (s32)D_80198814);
        *(s16 *)(a0 + 2) = 7;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(s32 *)(a0 + 0x1C) = 6;
        break;
    case 4:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_80198908);
        func_8012A828(a0, (s32)D_80198914);
        *(s16 *)(a0 + 2) = 8;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        break;
    case 5:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_8019860C);
        func_8012A828(a0, (s32)D_801986CC);
        *(s16 *)(a0 + 2) = 9;
        *(u16 *)(a0 + 0xFE) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s16 *)(a0 + 0x100) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE) * 6;
        sVar1 = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x70);
        if (sVar1 == 5) {
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x60) - 0x60;
            sVar1 = (rand() % 0x60) - 0x40;
        } else {
            if (sVar1 != 6) {
                break;
            }
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x20) - 0x20;
            sVar1 = (rand() % 0x60) - 0x50;
        }
        *(s16 *)(a0 + 0x1A) = sVar1;
    }
    uVar5 = rand();
    *(u32 *)(a0 + 0x94) = uVar5 & 0xF;
    *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
}




extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8017DFD4(void *a0) {
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0xEFFFFFFF;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x08000000;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x60000000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4) -
        (func_8004787C(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC) -
        (func_80047948(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x18) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1A) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1C) / 2;
}


extern void func_8012C218(void *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);

void func_8017E168(void *a0)
{
    u16 sv0[4];
    u16 sv1[4];
    s32 flag[4];
    s32 cnt;
    s32 tmp;
    s32 m;

    if (*(s16 *)((s32)a0 + 0xFE) == *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        if ((*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x100) & 0x4000) == 0) {
            goto low;
        }
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) - 0x200;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) - 0x200;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x200) {
            goto tail;
        }
        func_80143B6C((s32)a0, 0);
    }
    func_8012C218(a0);
    return;

low:
    cnt = *(u16 *)((s32)a0 + 0x100) - 1;
    *(s16 *)((s32)a0 + 0x100) = cnt;
    if ((s16)cnt < 9) {
        *(s16 *)((s32)a0 + 0x100) = 0x18;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 5) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 96 - 0x60;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 56 - 0x2C;
        } else if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 6) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 32 - 0x20;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 128 - 0x60;
        }
    }
    tmp = *(s16 *)((s32)a0 + 0x100);
    if (tmp < 0x10) {
        s32 g1;                       /* per-arm local: §5a cross-jump barrier, see header */
        g1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g1 + 0x1A) = tmp * 0x300;
        *(s16 *)(g1 + 0x18) = tmp * 0x300;
    } else {
        s32 g2;                       /* per-arm local: §5a cross-jump barrier, see header */
        g2 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g2 + 0x1A) = (0x20 - tmp) * 0x300;
        *(s16 *)(g2 + 0x18) = (0x20 - tmp) * 0x300;
    }

tail:
    {
        s32 msk;
        msk = 0x80000000;             /* HOISTED OUT OF THE ARM ON PURPOSE — see header (3) */
        if (*(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4) < 0) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= msk;
        } else {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        }
    }

    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);

    sv0[0] = *(u16 *)((s32)a0 + 0x12);
    sv0[1] = *(u16 *)((s32)a0 + 0x16);
    sv0[2] = *(u16 *)((s32)a0 + 0x1A);

    m = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(sv0, sv1, flag);

    *(s16 *)((s32)a0 + 0x6) = sv1[0];
    *(s16 *)((s32)a0 + 0xA) = sv1[1];
    *(s16 *)((s32)a0 + 0xE) = sv1[2];
}



extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8017E518(void *a0) {

    extern void (*D_8019892C[])(void);
    extern u16 D_80126B96;
    s32 t;
    u16 *q;

    D_8019892C[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        if (*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) >= 0) {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
            if (func_8012D624(a0, 0x1c, 0xa) == 1) {
                q = &D_80126B96;
                *q |= 0x200;
            }
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            if (*(s16 *)((s32)a0 + 0x70) == 1) {
                t = *(s32 *)((s32)a0 + 0x1c) - 1;
                *(s32 *)((s32)a0 + 0x1c) = t;
                if (t == 0) {
                    *(s32 *)((s32)a0 + 0x1c) = 8;
                    func_8012C658(0x12f, 3, (s32)a0);
                }
            }
        }
    }
}


extern void (*D_801989D8[])(void);

void func_8017E604(void *a0) {
    D_801989D8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80198A8C[])(void);

void func_8017E640(void *a0) {
    D_80198A8C[*(u16 *)((s32)a0 + 0x2)]();
}



void func_8017E67C(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xc800;
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8017E694(s32 a0) {

    extern u8 D_8019850C[];
    extern u8 D_801984EC[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8018374C[];
    s32 t;

    if (func_8012C354(a0, (s32)D_8019850C) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801984EC;
        *(s32 *)(a0 + 0xC4) = t | 0x2;

        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_8018374C);

        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;

        func_8012C658(0x164, 0x555, a0);
        func_8012C658(0x164, 0xAAA, a0);
        func_8012C658(0x164, 0x1000, a0);
    }
}


void func_8017E738(void *a0) {
        void *a1 = *(void **)((char *)a0 + 0x20);
        short fc = *(unsigned short *)((char *)a0 + 0xfc);
        unsigned short v12 = *(unsigned short *)((char *)a1 + 0x12) + fc;
        *(unsigned short *)((char *)a1 + 0x12) = v12;
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_8017E754(void *a0) {

    extern u8 D_8018374C[];
    extern u8 D_801985D0[];
    extern u8 D_801984EC[];
    if (func_8012C354((s32)a0, (s32)D_801985D0) != 0) {
        void *a2 = *(void **)((char *)a0 + 0x20);

        *(s32 *)((char *)a2 + 0x4) |= 0x80000000;
        *(u8 *)((char *)a0 + 0xC0) = 1;

        *(s32 *)((char *)a0 + 0xBC) = (s32)D_801984EC;
        *(s32 *)((char *)a0 + 0xC4) |= 0x2;

        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_8018374C);

        *(u16 *)((char *)a0 + 0x2) = 1;
        *(u8 *)((char *)a0 + 0x75) = 0;
    }
}


extern void func_8012B2CC(s32 a0);


void func_8017E7D8(s32 *a0) {
    s32 val_at_64;
    s32 deref;
    u16 val1, val2;
    s32 ptr_at_20;

    val_at_64 = *(s32 *)((char *)a0 + 0x64);
    deref = *(s32 *)((char *)val_at_64 + 0x20);
    val1 = *(u16 *)((char *)deref + 0x12);
    val2 = *(u16 *)((char *)a0 + 0x70);
    ptr_at_20 = *(s32 *)((char *)a0 + 0x20);

    *(u16 *)((char *)ptr_at_20 + 0x12) = val1 + val2;

    func_8012B2CC(a0);
}




void func_8017E814(void *a0)
{
    u16 v = *(u16 *)(a0 + 0x5E);
    if (v != 0x1D) {
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x2) = 0x7;
    } else {
        *(u16 *)(a0 + 0x5C) = 0x8000;
    }
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
}



extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_8017E844(s32 a0) {
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        s16 v = *(s16 *)(a0 + 0x70);
        if (v != 0) {
            *(s16 *)(a0 + 0x2) = 2;
            ((void (*)(void*, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
        } else {
            void *p = *(void **)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(p + 0x4) |= 0x80000000;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_8017E8C8(s32 a0) {

    extern u8 D_8019889C[];
    extern s16 D_80126CB6;
    s32 r;

    if (func_8012BCCC(a0) > 0x63FFF) {
        *(u16 *)(a0 + 0x2) = 5;
    } else {
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B864(a0), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_8019889C);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((D_80126CB6 - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0)) {
            *(s16 *)(a0 + 0x16) = -0x18;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}



extern void func_8012E688(void *a0, s32 a1, s32 a2);
extern void func_8012B23C(void *a0);

void func_8017E98C(void *a0) {

    extern u16 D_801988A8[];
    extern u16 D_801988AA[];
    extern u16 D_801988AC[];
    void *a1;

    if (--*(s32 *)((s32)a0 + 0x1c) == 0) {
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x88);
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0x8a);
        *(u16 *)((s32)a0 + 0xe) = *(u16 *)((s32)a0 + 0x8c);
        a1 = *(void **)((s32)a0 + 0x20);
        *(u32 *)((s32)a1 + 0x4) &= 0x7fffffff;
        func_8012E688(a0, 0x679, 0);
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012B23C(a0);
        *(u16 *)((s32)a0 + 0x12) = D_801988A8[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x16) = D_801988AA[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x1a) = D_801988AC[*(s16 *)((s32)a0 + 0xfc) * 4];
    }
}




extern s32 func_8012BD14(s32 a0);
extern void func_80143970(void *a0);
extern void func_8012E688(void *a0, s32 a1, s32 a2);

void func_8017EA6C(s32 a0) {
    s32 ret = func_8012BD14(a0);
    if (ret <= 0x64000) {
        Struct_8017EA6C *ptr = *(Struct_8017EA6C **)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 1;
        ptr->f1 = ptr->f1 & 0x7FFFFFFF;
        func_80143970((void *)a0);
        func_8012E688((void *)a0, 0xBA2, 0);
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_8017EADC(s32 a0) {

    extern u8 D_8019889C[];
    s16 sp10[3];
    s32 r;

    if (func_8012BCCC(a0) <= 0x38400) {
        *(u16 *)(a0 + 0x2) = 2;
    } else {
        sp10[0] = *(u16 *)(a0 + 0x6);
        sp10[2] = *(u16 *)(a0 + 0xE);
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B70C(sp10, (s16 *)(a0 + 0x88)), 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_8019889C);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((*(s16 *)(a0 + 0x8A) - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x8000) {
            *(s16 *)(a0 + 0x16) = -4;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}


void func_8017EBB8(void) {
}


/* func_8017EBC0 — per-frame entity tick:
 *  - decrement the timer at 0x1C if non-zero
 *  - fade the two u16 colour/alpha words at +0x18 / +0x1A of the display record
 *    hanging off 0x20 by 0x100 each
 *  - once the second one drops to <= 0x80, tear the entity down
 *
 * §71 sibling-first: DEFINE_func_801319E0() (engine_core.h L17451) is the same
 * `func_8002A04C(arg0); func_8012C218((void *)arg0);` teardown tail with arg0
 * living in $s0 across the calls — signature and casts copied from it.
 */

extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_8017EBC0(s32 arg0) {
    if (*(s32 *)(arg0 + 0x1C) != 0) {
        *(s32 *)(arg0 + 0x1C) -= 1;
    }
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) -= 0x100;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) -= 0x100;
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) < 0x81) {
        if (*(s16 *)(arg0 + 0x70) == 1) {
            /* LOAD-BEARING: hoisting the argument load into its own local
             * emits `lw $a0,0xCC($s0)` ABOVE the guard branch and leaves the
             * beqz delay slot a nop. Inlining it at the call site instead
             * gives beqz/nop/lw -> 3 mismatches (class DELAY-SLOT). A/B-tested. */
            void *temp = *(void **)(arg0 + 0xCC);
            if (arg0 != 0) {
                func_8012C218(temp);
            }
        }
        func_8002A04C(arg0);
        func_8012C218((void *)arg0);
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_8017EC78(s32 a0) {

    extern u8 D_80198964[];
    extern u8 D_8018374C[];
    extern u16 D_80198998[];
    extern u16 D_8019899A[];
    extern u16 D_8019899C[];
    extern s16 D_8019899E[];
    if (func_8012C354(a0, (s32)D_80198964) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_8018374C);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(u16 *)(a0 + 0x12) = D_80198998[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x16) = D_8019899A[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x1A) = D_8019899C[*(s16 *)(a0 + 0xFC) * 4];
        *(s32 *)(a0 + 0x1C) = D_8019899E[*(s16 *)(a0 + 0xFC) * 4];
        func_8012C588(0x1C4, a0);
    }
}




extern void func_8012CBA4(s32 a0);
extern s32 func_8012DFD4(s32);

void func_8017ED3C(s32 a0) {
    s32 t;

    func_8012CBA4(a0);
    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t == 0) {
        *(s32 *)(a0 + 0x1C) = 0x6;
        *(s16 *)(a0 + 0x2) = 0x2;
    }
    ((void (*)(u8 *))func_8012DFD4)((u8 *)a0);
}



extern s32 func_8012DFD4(s32);

void func_8017ED90(s32 a0) {

    extern s16 D_8019899E[];
    s32 a1 = a0;
    s32 t = *(s32 *)(a1 + 0x1C) - 1;
    *(s32 *)(a1 + 0x1C) = t;
    if (t == 0) {
        s16 idx = *(s16 *)(a1 + 0xFC);
        s32 val = D_8019899E[idx * 4];

        *(s16 *)(a1 + 0x12) = -*(u16 *)(a1 + 0x12);
        *(s16 *)(a1 + 0x16) = -*(u16 *)(a1 + 0x16);
        *(s16 *)(a1 + 0x1A) = -*(u16 *)(a1 + 0x1A);
        *(s16 *)(a1 + 0x2) = 1;
        *(s32 *)(a1 + 0x1C) = val;
    }
    ((void (*)(u8 *))func_8012DFD4)((u8 *)a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 rand(void);


void func_8017EE0C(s32 param_1)
{

    extern u8 D_801989E4[];
    extern u8 D_80198A44[];
    s32 v0;
    s16 sVar1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_801989E4);
        ((void (*)(s32, s32))func_8012A828)(param_1, (s32)D_80198A44);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = 0x10;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = 0x10;
        *(s32 *)(param_1 + 0x94) = rand() & 7;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x10;
        if ((u32)(*(u16 *)(param_1 + 0x70) - 1) >= 0x6fff) {
            *(u16 *)(param_1 + 0x70) = rand() & 0x77ff;
            sVar1 = 2;
        } else {
            sVar1 = 1;
        }
        *(s16 *)(param_1 + 2) = sVar1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_8017EEF0(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_8017EFBC(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s16 *)(a0 + 0x70) = rand() & 0x77FF;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern void (*D_8019A980[])(void);

void func_8017F094(void *a0) {
    D_8019A980[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012C438(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);

void func_8017F0D0(s32 a0) {
    extern u8 D_8019A9C8[];
    extern u8 D_8018374C[];
    extern u16 D_8019AACC[];
    extern u16 D_8019AACE[];
    extern u16 D_8019AAD0[];
    extern u16 D_8019AAD2[];

    s32 v0 = *(u16 *)(a0 + 0x70) & 0xF;
    u16 flag;

    if (func_8012C438(a0, (s32)(D_8019A9C8 + v0 * 52)) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_8018374C);
        *(u8 *)(a0 + 0x75) = 0;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x8040;

        *(u16 *)(a0 + 0xFE) = D_8019AACC[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x100) = D_8019AACE[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x102) = D_8019AAD0[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x104) = D_8019AAD2[*(s16 *)(a0 + 0xFC) * 4];
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x104, 0xDC);

        flag = *(u16 *)(a0 + 0x70) & 0xF0;
        switch (flag) {
        case 0:
            *(s16 *)(a0 + 0x2) = 1;
            break;
        case 0x10:
            *(s16 *)(a0 + 0x2) = 2;
            break;
        case 0x20:
            *(s16 *)(a0 + 0x2) = 3;
            break;
        }
        func_8012C588(0x1C4, a0);
    }
}



// @class: struct
// @stuck: none — MATCH (fn-ptr table %lo-fold via extern array of code ptrs)

extern code_fn D_8019AB1C[];

extern s32 func_8012DFD4(s32 a0);

void func_8017F224(int param_1)
{
    D_8019AB1C[*(unsigned short *)(param_1 + 2)]();
    ((void (*)(int))func_8012DFD4)(param_1);
    return;
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern u8 D_8018374C[];
extern u8 D_8019A91C[];
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32*, s32);

void func_8017F274(a0)
s32 a0;
{
    extern u8 D_8019A91C[];
    extern u8 D_8018374C[];
    u16 old_fc;

    if (func_8012C354(a0, (s32)D_8019A91C) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_8018374C);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 8;
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x104, 0xDC);
        old_fc = *(u16 *)(a0 + 0xFC);
        *(u16 *)(a0 + 0xFC) = 0x60;
        *(u16 *)(a0 + 0xFE) = old_fc;
    }
}


extern s32 func_80047948(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 D_80126B96;
extern u8 D_8019A950[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B414(int a0);

void func_8017F2EC(s32 a0) {
    s32 s2;
    s32 i;
    s32 sum;
    s32 v0;
    u8 *base;
    u8 *p0;
    u8 *p1;
    s32 want;
    u16 setval;

    s2 = a0;

    sum = *(u16 *)(s2 + 0xFE) + *(u16 *)(s2 + 0xFC);
    *(u16 *)(s2 + 0xFE) = sum & 0xFFF;
    if ((sum & 0x7FF) < 0x61) {
        func_8002D4C8(0x6A5, 0);
    }

    v0 = func_80047948(*(s16 *)(s2 + 0xFE));
    *(s16 *)(*(s32 *)(s2 + 0x20) + 0x14) = v0 >> 3;

    if (*(s16 *)(s2 + 0x70) != 0) {
        func_8012B414(s2);
    }

    i = 0;
    want = 1;
    setval = 0x4004;
    base = D_8019A950;
    p1 = base + 8;
    p0 = base;
    for (; i < 5; p1 += 8, i++, p0 += 8) {
        if (func_8012D5E4(s2, (s32)p0, (s32)p1, 0x30) == want) {
            D_80126B96 = setval;
        }
    }
}


extern s32 *D_80126B78;

void func_8017F3EC(a0)
s32 a0;
{
    s16 t;

    *(u16 *)(*(u32 *)(a0 + 0x20) + 0x10) += *(u16 *)(a0 + 0xFE);
    *(u16 *)(*(u32 *)(a0 + 0x20) + 0x12) += *(u16 *)(a0 + 0x100);
    *(u16 *)(*(u32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0x102);

    t = *(s16 *)(a0 + 0x100);
    if (t != 0 && *(u8 *)(a0 + 0x74) != 0) {
        *(u16 *)((s32)D_80126B78 + 0x12) += t;
    }
}



extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

// @class: none — MATCH (46 ins), iteration 1. rtu_match MATCH too.
// @stuck: none.
// Derivation was pure OPCODE-WIDTH reading (no cookbook section needed beyond
// §3-T4 for the two branch senses):
//   * 0x108 `lh`/`sh`      -> s16 counter.
//   * 0x106,0xFE `lhu`+`addu`+`sh` -> u16 += u16 (a signed s16 pair would have
//     loaded `lh`). The `sll 16/sra 16` immediately after is NOT part of the
//     add — it is the `(s16)` cast of the just-stored u16 being handed to
//     func_8004787C, which CSE serves out of the store's register instead of
//     re-loading. Writing the arg as `*(s16 *)(a0 + 0x106)` after the store
//     reproduces it exactly; the SECOND call re-loads with `lh` on its own
//     because $v0/$a0 died across the first jal.
//   * 0x104 `lh` -> s16 multiplicand; mult/mflo/`sra 12` == plain int `>> 12`.
//   * 0x8C,0x8A `lhu` -> u16 bases; 0xE,0xA `sh`.
//   * §3-T4 both branches: `beqz` at the top => source condition is `!= 0` with
//     an early return; `bnez` at the bottom => source condition is `== 0`.
// The shared `sh $v0,0x108($s0)` tail is gcc's own cross-jump merge of the
// `- 1` arm and the `= 0xF` arm — do NOT hand-write it as a merged tail.
void func_8017F480(s32 a0) {
    if (*(s16 *)(a0 + 0x108) != 0) {
        *(s16 *)(a0 + 0x108) = *(s16 *)(a0 + 0x108) - 1;
        return;
    }
    *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) + *(u16 *)(a0 + 0xFE);
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x8C) +
        ((func_8004787C(*(s16 *)(a0 + 0x106)) * *(s16 *)(a0 + 0x104)) >> 12);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A) +
        ((func_80047948(*(s16 *)(a0 + 0x106)) * *(s16 *)(a0 + 0x104)) >> 12);
    if ((*(u16 *)(a0 + 0x106) & 0x7FF) == 0) {
        *(s16 *)(a0 + 0x108) = 0xF;
    }
}



extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

// @class: none — MATCH (46 ins), iteration 1. rtu_match MATCH too.
// @stuck: none.
// Derivation was pure OPCODE-WIDTH reading (no cookbook section needed beyond
// §3-T4 for the two branch senses):
//   * 0x108 `lh`/`sh`      -> s16 counter.
//   * 0x106,0xFE `lhu`+`addu`+`sh` -> u16 += u16 (a signed s16 pair would have
//     loaded `lh`). The `sll 16/sra 16` immediately after is NOT part of the
//     add — it is the `(s16)` cast of the just-stored u16 being handed to
//     func_8004787C, which CSE serves out of the store's register instead of
//     re-loading. Writing the arg as `*(s16 *)(a0 + 0x106)` after the store
//     reproduces it exactly; the SECOND call re-loads with `lh` on its own
//     because $v0/$a0 died across the first jal.
//   * 0x104 `lh` -> s16 multiplicand; mult/mflo/`sra 12` == plain int `>> 12`.
//   * 0x88,0x8A `lhu` -> u16 bases; 0x6,0xA `sh`.
//   * §3-T4 both branches: `beqz` at the top => source condition is `!= 0` with
//     an early return; `bnez` at the bottom => source condition is `== 0`.
// The shared `sh $v0,0x108($s0)` tail is gcc's own cross-jump merge of the
// `- 1` arm and the `= 0xF` arm — do NOT hand-write it as a merged tail.
void func_8017F538(s32 a0) {
    if (*(s16 *)(a0 + 0x108) != 0) {
        *(s16 *)(a0 + 0x108) = *(s16 *)(a0 + 0x108) - 1;
        return;
    }
    *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) + *(u16 *)(a0 + 0xFE);
    *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x88) +
        ((func_8004787C(*(s16 *)(a0 + 0x106)) * *(s16 *)(a0 + 0x104)) >> 12);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A) +
        ((func_80047948(*(s16 *)(a0 + 0x106)) * *(s16 *)(a0 + 0x104)) >> 12);
    if ((*(u16 *)(a0 + 0x106) & 0x7FF) == 0) {
        *(s16 *)(a0 + 0x108) = 0xF;
    }
}



extern void func_801802C4(void *a0);

void func_8017F5F0(void *a0) {

    extern void (*D_8019CA78[])(void);
    D_8019CA78[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(s32 *)((s32)a0 + 0xE8) = *(s32 *)((s32)a0 + 0xE8) + 1;
        if ((*(s32 *)((s32)a0 + 0xE8) & 0xF) == 0) {
            func_801802C4(a0);
        }
    }
}



extern s32 rand(void);
extern s32 func_8012C354(s32, s32);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80143994(s32 *a0, s32 a1);


void func_8017F66C(void *arg0) {

    extern s32 D_8019CA0C;
    extern s32 D_8019CA50;
    extern s32 D_8019EF68;
    s32 t;

    if (((s32 (*)(s32 *, s32))func_8012C354)(arg0, &D_8019CA0C)) {
        *(u8 *)((char *)arg0 + 0xC0) = 1;
        *(s32 *)((char *)arg0 + 0xB4) = -1;
        *(s32 **)((char *)arg0 + 0xBC) = &D_8019CA50;
        *(u32 *)((char *)arg0 + 0xC4) |= 1;
        *(s32 *)((char *)arg0 + 0xE4) = -((rand() % 8 + 0xC) << 16);
        func_8012A828(arg0, &D_8019EF68);
        func_80143994(arg0, 0x1000);
        t = *(u16 *)((char *)arg0 + 0x70) & 0x10;
        if (t != 0) {
            t = 3;
        } else {
            t = 1;
        }
        *(s16 *)((char *)arg0 + 0x2) = t;
    }
}



extern s32 rand(void);
extern void func_8012B200(void *a0);

void func_8017F72C(void *a0) {
    s16 r;
    s16 t;

    r = rand();
    *(u16 *)((s32)a0 + 0x104) = *(u16 *)((s32)a0 + 0xFC);
    t = r;
    func_8012B200(a0);
    if (*(u16 *)((s32)a0 + 0x70) & 1) {
        *(s32 *)((s32)a0 + 0x1C) = (s16)(r % 1800) + 0xE10;
    } else {
        *(s32 *)((s32)a0 + 0x1C) = (s16)(r % 60) + 0x78;
    }
    *(s16 *)((s32)a0 + 0xFE) = t % 32 + 0xA;
    *(s16 *)((s32)a0 + 0x2) = 2;
}



extern void func_80180200(s32 *a0, s32 a1, s32 a2);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_801802AC(void);
extern s32 rand(void);

void func_8017F854(s32 a0) {
    s32 sp10[2];
    s32 t;
    s32 r;

    func_80180200(sp10, a0, a0 + 0x102);
    t = sp10[0];
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
    r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), t >> 16,
                      *(s16 *)(a0 + 0xFE));
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
    func_8012B178(a0, *(s32 *)(a0 + 0xE4));
    func_8012CBF4(a0);
    if ((*(u16 *)(a0 + 0x70) & 2) == 0) {
        if (func_8012BEE8(a0)) {
            if (*(s32 *)(a0 + 0xE0) == 0) {
                if (((s32 (*)(s32))func_801802AC)(a0)) {
                    if (*(u16 *)(a0 + 0x70) & 1) {
                        *(s32 *)(a0 + 0x1C) = rand() % 0x708 + 0xE10;
                    } else {
                        *(s32 *)(a0 + 0x1C) = rand() % 0x3C + 0x78;
                    }
                } else {
                    *(s16 *)(a0 + 0x2) = 5;
                }
            } else {
                *(s16 *)(a0 + 0x2) = 1;
            }
        }
    }
}



extern s32 rand(void);
extern void func_8012B200(void *a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

void func_8017F9C4(s32 a0) {
    u8 auStack_18[8];
    s32 tmp;
    s32 base;
    s32 off;
    s32 val;

    func_8012B200((void *)a0);
    *(s32 *)(a0 + 0x1C) = rand() % 128 + 0x80;
    *(s16 *)(a0 + 0xFE) = rand() % 32 + 10;
    func_8012B0B4((unsigned int *)auStack_18, rand() % 0x1000,
                  rand() % *(s32 *)(a0 + 0xDC));
    tmp = *(s32 *)auStack_18;
    *(s16 *)(a0 + 0x102) = *(u16 *)(a0 + 0x88) + tmp;
    *(s16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x8C) + (tmp >> 16);
    if (*(u16 *)(a0 + 0x70) & 0x20) {
        off = rand() % 256;
        base = *(s16 *)(a0 + 0xFC);
        if (rand() & 1) {
            val = base + off;
        } else {
            val = base - off;
        }
        *(s16 *)(a0 + 0x104) = val;
    } else {
        *(s16 *)(a0 + 0x104) = *(u16 *)(a0 + 0xFC) - rand() % 256;
    }
    *(s16 *)(a0 + 0x2) = 4;
}



extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 rand(void);

void func_8017FB58(s32 a0) {

    extern u16 D_80126B62;
    s32 sp10[6];
    u8 sp28[8];
    s16 q;
    s32 t;
    s32 r;

    *(s16 *)((s32)sp10 + 0x2) = *(u16 *)(a0 + 0x102);
    *(s16 *)((s32)sp10 + 0xA) = *(u16 *)(a0 + 0x106);
    q = *(u16 *)(a0 + 0x104);
    *(s16 *)((s32)sp10 + 0x6) = q;
    if ((*(u16 *)(a0 + 0x70) & 0x20) == 0) {
        *(s16 *)((s32)sp10 + 0x6) = q + D_80126B62;
    } else {
        *(s16 *)((s32)sp10 + 0x6) = q + *(u16 *)(a0 + 0x8A);
    }

    func_8012B77C((s32)sp28, a0 + 4, (s32)sp10);
    t = *(s32 *)sp28;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
    r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), t >> 16,
                      *(s16 *)(a0 + 0xFE));
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
    func_8012B178(a0, *(s32 *)(a0 + 0xE4));
    func_8012CBF4(a0);
    if (func_8012BEE8(a0)) {
        s32 base;
        s32 off;
        s32 val;

        *(s32 *)(a0 + 0x1C) = rand() % 128 + 0x80;
        *(s16 *)(a0 + 0xFE) = rand() % 32 + 10;
        func_8012B0B4((unsigned int *)sp28, rand() % 0x1000,
                      rand() % *(s32 *)(a0 + 0xDC));
        t = *(s32 *)sp28;
        *(s16 *)(a0 + 0x102) = *(u16 *)(a0 + 0x88) + t;
        *(s16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x8C) + (t >> 16);
        if (*(u16 *)(a0 + 0x70) & 0x20) {
            off = rand() % 256;
            base = *(s16 *)(a0 + 0xFC);
            if (rand() & 1) {
                val = base + off;
            } else {
                val = base - off;
            }
            *(s16 *)(a0 + 0x104) = val;
        } else {
            *(s16 *)(a0 + 0x104) = *(u16 *)(a0 + 0xFC) - rand() % 256;
        }
    }
}



extern s32 rand(void);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
/* Declarations conformed VERBATIM to the TU's existing ones
 * (ov_SC02_035_jr_8017BEBC.c:5139 and :5117) — type disagreements are
 * pushed to casts at the use sites below. Zero codegen change. */
extern void func_80180200(s32 *a0, s32 a1, s32 a2);
extern void func_8012B200(void *a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8017FDAC(s32 a0) {
    s16 sp10[4];
    s32 sp18[2];
    s16 r;
    s32 t;
    s32 u;

    r = rand();
    func_8012B0B4((unsigned int *)sp18, (s16)(r % 4095), (s16)(r % 128) + 0xC0);

    t = sp18[0];
    sp10[1] = -0x30;
    sp10[0] = t;
    sp10[2] = t >> 16;
    func_80180200(sp18, a0, (s32)sp10);

    u = sp18[0];
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = u;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = u >> 16;
    func_8012B200((void *)a0);
    func_8012B2CC(a0);
    func_8012B178(a0, *(s32 *)(a0 + 0xE4) + 0xFFFE0000);
    *(s16 *)(a0 + 0x2) = 6;
    *(s16 *)(a0 + 0x34) = 0;
}



extern void func_80180200(s32 *a0, s32 a1, s32 a2);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012B200(void *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_801801D4(s32 a0);
extern s32 rand(void);

void func_8017FEB8(s32 a0) {

    extern u8 D_8019CA48[];
    s32 sp10[2];
    s32 t;
    s32 u;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (((s32 (*)(s32))func_8012CBF4)(a0)) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        } else if (*(s16 *)(a0 + 0x100) < *(s16 *)(a0 + 0xA)) {
            *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0x100);
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 1:
        t = func_8012B8E4(a0, 6);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + t;
        if (func_8012BEE8(a0)) {
            if (rand() & 1) {
                *(s16 *)(a0 + 0x2) = 1;
            } else {
                *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
                func_8012B200((void *)a0);
                *(s32 *)(a0 + 0x1C) = 0x20;
                func_8002D4C8(0x6FF, 0);
            }
        }
        break;
    case 2:
        func_80180200(sp10, a0, (s32)D_8019CA48);
        u = sp10[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = u;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = u >> 16;
        func_8012B178(a0, *(s32 *)(a0 + 0xE4) + 0xFFF80000);
        func_8012CBF4(a0);
        if (func_801801D4(a0) == 1) {
            *(s16 *)(a0 + 0x2) = 1;
        } else if (func_8012BEE8(a0)) {
            *(s16 *)(a0 + 0x2) = 1;
        }
        break;
    default:
        *(s16 *)(a0 + 0x2) = 1;
        break;
    }
}




extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012E778(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 *a0, s32 a1);

void func_80180054(void *arg0) {

    extern s32 D_8019EF68;
    if (func_8012BEE8((s32)arg0)) {
        if (!func_8012E778((s32)arg0, 0xA000C8)) {
            {
                s32 t;
                t = *(u16 *)((char *)arg0 + 0x70) & 0x10;
                *(s16 *)((char *)arg0 + 0x2) = (t == 0) ? 1 : 3;
            }
            *(s16 *)((char *)arg0 + 0x5C) =
                *(u16 *)(*(s32 *)((char *)arg0 + 0x78) + 0x2);
            *(s16 *)((char *)arg0 + 0x76) =
                *(u16 *)(*(s32 *)((char *)arg0 + 0x78));
            *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x18) =
                *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x1A) =
                *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x1C) = 0x1000;
            *(u16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x2C) &= 0x10;
            func_8012E88C((s32)arg0);
            func_8012A828(arg0, &D_8019EF68);
        }
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);


extern void func_8012E8A8(u8 *a0);

void func_80180110(void *arg0) {
    func_8002A04C((s32)arg0);

    if ((*(s16 *)((char *)arg0 + 0x70) & 0x8000) != 0) {
        s32 v1 = *(s32 *)((char *)arg0 + 0x20);
        *(s16 *)((char *)arg0 + 0x2) = 0x7;
        *(s8 *)((char *)arg0 + 0xC1) = 0;
        *(s32 *)((char *)arg0 + 0x1C) = 0x40;
        *(s16 *)((char *)arg0 + 0x5E) = 0;
        *(s16 *)((char *)arg0 + 0x5C) = 0;
        *(s16 *)((char *)v1 + 0x12) = 0;
        *(s16 *)((char *)v1 + 0x10) = 0;
        func_8012E8A8((u8 *)arg0);
        *(s16 *)((char *)arg0 + 0x6) = *(u16 *)((char *)arg0 + 0x88);
        *(s16 *)((char *)arg0 + 0xA) = *(u16 *)((char *)arg0 + 0x8A);
        *(s16 *)((char *)arg0 + 0xE) = *(u16 *)((char *)arg0 + 0x8C);
    } else {
        func_8012C218(arg0);
    }
}


extern void func_8012A828(s32 *a0, s32 a1);
    extern s32 D_8019EF68;
    void func_8018019C(void *arg0) {
        *(s16 *)((char *)arg0 + 0x2) = 1;
        *(s16 *)((char *)arg0 + 0x5c) = *(u16 *)(*(s32 *)((char *)arg0 + 0x78) + 0x2);
        func_8012A828(arg0, &D_8019EF68);
    }



extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern u8 D_8019CA98[];
    s32 func_801801D4(s32 arg0) {
        return ((s32 (*)(s32, void *, void *, s32))func_8012D5E4)(arg0, &D_8019CA98[0], &D_8019CA98[8], 5) != 0;
    }




/* func_80180200 — MATCH (43 ins). Family of 10 / 430 templatable ins.
 * Keys:
 * (1) `la $v1,D_80126CBA` + `lh 0($v1)` + `addiu $a0,$v1,-6` is ONE POINTER LOCAL
 *     (`s16 *q = &D_80126CBA;` then `q - 3`), NOT two externs. A plain `D_80126CBA`
 *     read folds %lo into the load (`lui %hi / lh %lo(sym)($r)`) and `&D_80126CB4`
 *     would emit its own second lui — 2 extra ins. The full-address materialisation
 *     is the tell that the C bound the address to a variable.
 * (2) `s32 sp10[4]; s32 sp20;` in THAT declaration order => sp+0x10 / sp+0x20; the
 *     3 halfword fields are written `*(s16 *)((s32)sp10 + 0x2/0x6/0xA)` — same form
 *     as the matched siblings (src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:4779).
 * (3) The TU declares `extern void func_80180200(s32 *, s32, s32);` at file scope
 *     3x (:5197 :5285 :5319), so an `s32 *` return is a HARD cc1 `conflicting types`
 *     error. The trailing `addu $v0,$s0,$zero` therefore comes from a $2-pinned temp.
 * (4) The pin is load-bearing twice: pinning the POST-CALL temp to $v0 is what stops
 *     sched2 hoisting the return copy into the load-delay slot (unpinned => `lw $v1 /
 *     move $v0,$s0 / sw $v1,0($v0)`, 42 ins, LENGTH-DRIFT -1). Tried and rejected:
 *     `s32 sp20[2]`, `a0[0] =`, a named s32 temp, a cast-return — all identical DIFF.
 * (5) `rv = (s32)a0;` alone is DELETED by flow ($2 is dead at the end of a void fn).
 *     The empty volatile asm keeps it live and emits zero bytes (#APP/#NO_APP only).
 * Verified: spliced into the real TU, cc1 emits the identical instruction stream and
 * exactly the same 10 diagnostics as the unmodified TU (zero new). */
extern s32 func_8012B77C(s32 out, s32 from, s32 to);

void func_80180200(s32 *a0, s32 a1, s32 a2) {

    extern s16 D_80126CBA;
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    register s32 rv __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    q = &D_80126CBA;
    if (*q == 0) {
        p = (u16 *)(q - 3);
        *(s32 *)(a1 + 0xE0) = 0;
    } else {
        p = (u16 *)(a1 + 0x88);
        *(s32 *)(a1 + 0xE0) = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    *(s16 *)(a1 + 0x100) = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = sp20;
    *a0 = rv;
    rv = (s32)a0;
    __asm__ __volatile__("" : : "r" (rv));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
}



extern u8 D_80078EC1;
    s32 func_801802AC(void) {
        return (D_80078EC1 ^ 0x15) == 0;
    }



extern s32 func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

/* The `register ... __asm__("$4")` pin on the FIRST call argument is load-bearing.
 * The target sets $a0 = 0x6FE in the ENTRY block (dbr steals it into the `bnez`
 * delay slot -- sched.md D1 backward fill), but a plain `s32 id = 0x6FE;` local is
 * rematerialised at the use site (single-set constant pseudo -> REG_EQUIV), so the
 * `li` sinks past the label into the join block and dbr fills the slot with the
 * if-body's `lui` instead (SHIFT-DRIFT/+1). Pinning the local to $a0 makes the `li`
 * a hard-reg set that stays where it is written, and the call's arg move degenerates
 * to a deleted `(set (reg 4) (reg 4))`. */
void func_801802C4(void *a0) {
    s32 id;
    s32 vol;
    s32 t;

    vol = 0x7F;
    t = func_8012BD14((s32)a0);
    id = 0x6FE;
    if (t > 0x1000) {
        vol -= (t - 0x1000) / 0x2700;
    }
    func_8002D4C8(id, (vol | 0x1000) & 0xFFFF);
}



/* func_80180330 — "spawn a paired effect entity above/below the actor" template
 * (family exemplar, 15 members / 1455 templatable instructions).
 *
 * Declaration provenance (all verified against the whole TU in one pass, cookbook §135-8):
 *   ((void (*)(s32, s32))func_8012A828)(s32,s32)          — TU col-0 decl (lines 3488/3771/…/4781), identical form
 *   func_8012C658(s32,s32,s32)      — TU col-0 decl (lines 2524/3721/3772/4935)
 *   func_8012C218(void *)           — TU col-0 decl (lines 3545/4016/…/5226)
 *   func_8012B030(u8 *)             — TU col-0 decl (line 4208)
 *   func_8012CEB0(s32,s32,s32)      — TU fn-scope decl (line 4404), same signature
 *   func_8002AC00(s32)              — TU fn-scope decl (line 5085), same signature
 *   func_8001C214(s32,s32)          — NOT declared in this TU; form copied from
 *                                     src/shared/engine_core.h:8751 so it can never clash
 *   D_801A5498 / D_801ACBDC         — real dlabels in asm/ov_SC02_026/data/tail.data.s
 *                                     (0x801B5A4C / 0x801BD190), declared nowhere else
 *
 * Codegen notes (each closed a residual):
 *  - The buf[8] halfword-pair setup is the byte-verified twin of func_801843AC in THIS TU
 *    (line 4403): the three $2/$3/$7 register pins reproduce the original's temp allocation,
 *    and the doubled buf[1]/buf[5] stores are real — the ±8 adjust is a second store, so the
 *    scheduler emits sh/sh then sh/sh with a single lhu of a0+0xA (cookbook §135-4: the list
 *    scheduler preserves the relative order of disambiguable stores).
 *    Third temp lands in $a3 (not $a2 as in func_801843AC) because $a2 is already pinned to
 *    the literal-0 third argument here.
 *  - `>= 0x10` (not `< 0x10` with swapped arms) is what puts the func_8012C218 arm in the
 *    fall-through position and the func_8012B030 arm behind the `j`.
 *  - The `s16 t` temp on line ~72 is load-BEFORE-stores in SOURCE. Without it the lhu of
 *    a0+0x100 cannot hoist above the two ent-relative stores — §135-2's MEM_IN_STRUCT_P
 *    escape does NOT apply here because those stores have varying (register) addresses, so
 *    true_dependence() keeps the edge. Source order is the only lever; costs one nop otherwise.
 *  - The do/while's `sll/sra` pair is CSE store-forwarding: `*(u16*)` read for the += keeps
 *    the HImode load (result is truncated), then the signed compare must materialize the
 *    sign extension of the just-stored register.
 */

extern void func_8002AC00(s32 arg0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C218(void *a0);
extern s32 func_8012B030(u8 *a0);

void func_80180330(void *a0) {

    extern s32 D_801A5498;
    extern s32 D_801ACBDC;
    u16 buf[8];
    s32 ent;
    u16 saved;
    u16 v0;
    u16 v1;
    u16 a3;
    u16 tmp0;

    func_8002AC00(0xD);
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        tmp0 = *(u16 *)((s32)a0 + 0x6);
        v0 = tmp0;
        buf[0] = v0;
        buf[4] = v0;

        v1 = *(u16 *)((s32)a0 + 0xA);
        v0 = v1 - 8;
        buf[1] = v1;
        buf[5] = v1;

        a3 = *(u16 *)((s32)a0 + 0xE);
        buf[1] = v0;
        buf[5] = (v1 + 8);
        buf[2] = a3;
        buf[6] = a3;

        if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) == 0) {
            if ((*(s16 *)((s32)a0 + 0x100) & 0x8000) == 0) {
                saved = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)&D_801A5498);
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801ACBDC);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = saved;
                ent = func_8012C658(0x12C, 1, (s32)a0);
                if (ent != 0) {
                    if (*(s16 *)((s32)a0 + 0xA) >= 0x10) {
                        func_8012C218((void *)ent);
                    } else {
                        *(u16 *)(*(s32 *)(ent + 0x20) + 0x12) = saved;
                        func_8012B030((u8 *)ent);
                        if (*(s16 *)((s32)a0 + 0x70) == 5) {
                            s16 t = *(s16 *)((s32)a0 + 0x100);
                            *(s16 *)(ent + 0x70) = 6;
                            *(s16 *)(ent + 0xFE) = 1;
                            *(s16 *)(ent + 0x100) = t;
                            do {
                                func_8012C658(0x12F, 5, ent);
                                *(s16 *)(ent + 0xFE) = *(u16 *)(ent + 0xFE) + 3;
                            } while (*(s16 *)(ent + 0xFE) < 0x10);
                            *(s16 *)(ent + 0xFE) = 0;
                        }
                    }
                }
            }
        }
    }
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern void func_80143970(void *a0);
extern void func_8012A828(s32*, s32);
extern void func_8012B23C(void *a0);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_801804B4(void *a0) {

    extern u8 D_8019F104[];
    extern u8 D_801ABAE4[];
    extern u8 D_801AB3AC[];
    extern char D_801ACA5C[];
    extern u8 D_801AC8DC[];
    extern s32 D_8019F23C;
    extern s32 D_8019F2DC;
    extern s32 D_8019F324;

    s16 state = *(s16 *)((s32)a0 + 0x70);

    if (func_8012C354((s32)a0, (s32)(D_8019F104 + state * 0x34)) == 0) {
        func_8012CAE4((void *)a0);
    } else {
        s16 state2;
        u16 saved;

        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xB4) = -0x401;
        func_80143970((void *)a0);

        state2 = *(s16 *)((s32)a0 + 0x70);
        switch (state2) {
            case 0:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801ABAE4);
                *(s16 *)((s32)a0 + 0x2) = 1;
                func_8012B23C((void *)a0);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F23C;
                *(s16 *)((s32)a0 + 0xFC) = 0;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 2:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801AB3AC);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s16 *)((s32)a0 + 0x2) = 9;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F2DC;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 1:
            case 3:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801ACA5C);
                *(s16 *)((s32)a0 + 0x2) = 6;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F324;
                break;
            case 4:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801ABAE4);
                *(s16 *)((s32)a0 + 0x2) = 0xD;
                func_8012B23C((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F23C;
                *(s16 *)((s32)a0 + 0xFC) = 0x1E;
                break;
            case 5:
                if (*(s16 *)((s32)a0 + 0xFC) != 0) {
                    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801AC8DC);
                    *(s16 *)((s32)a0 + 0x2) = 0xE;
                    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = rand() & 0xFFF;
                } else {
                    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801ABAE4);
                    *(s16 *)((s32)a0 + 0x2) = 1;
                }
                func_8012B23C((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F23C;
                *(s16 *)((s32)a0 + 0xFE) = 1;
                do {
                    func_8012C658(0x12F, 5, (s32)a0);
                    *(s16 *)((s32)a0 + 0xFE) = *(u16 *)((s32)a0 + 0xFE) + 1;
                } while (*(s16 *)((s32)a0 + 0xFE) < 6);
                *(s16 *)((s32)a0 + 0xFE) = 0;
                break;
            }
        func_8012B2CC((s32)a0);
    }
}


/* func_801806D8 — ov_SC02_026 / ov_SC02_026_jr_8017C180.c   MATCH (237 ins)
 *
 * §136c SIBLING-FIRST provenance (nothing here was derived from the .s that could be copied):
 *   - the func_8004787C / func_80047948 / func_80133784 trig+collide block is copied VERBATIM
 *     from the already-banked SAME-TU sibling func_80183B04 (TU:4468), including the
 *     `s32 r; r = 0x30;` non-const multiplier (T1) and the `V8_801806D8 {u16 x,y,z,w}` locals.
 *   - the RotTransPers + positional-sound block follows the byte-proven RTP_SND() macro in
 *     src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.c:3480 — in particular the $a0-PINNED SCOPES on
 *     &D_800AF648, which rematerialise the lui/addiu before EACH call instead of letting CSE
 *     hoist the address into a callee-saved pseudo.
 *   - the `*(u16*)(*(s32*)(a0+0x20)+0x12) = *(u16*)(...) + d;` accumulate form is copied from
 *     the SAME-TU sibling func_80180C80 (TU:3936).
 *
 * THE FOUR LEVERS THAT CLOSED IT (each one MOVED the count; recorded for the cookbook):
 *
 *  1. §136 L1 — `r = 0x30` MUST BE ITS OWN LOCAL, and the two func_8012B608 results must be
 *     per-arm block-scoped locals (`s32 d`).  Sharing one `s32 r` across all three sites makes
 *     it a GLOBAL allocno; as a BLOCK-LOCAL one it is handed $s0 by local-alloc (which runs
 *     BEFORE global-alloc), which then forces the actor — it conflicts with r — onto $s1 and
 *     lets `anim` (which does not conflict) take $s0.  One shared local ⇒ $s0/$s1 swapped
 *     across the ENTIRE function (98 mismatches).
 *
 *  2. BLKmode STACK SLOTS ARE ROUNDED TO 8.  `u16 sxy[2]` (4 bytes) occupies EIGHT bytes and
 *     pushed z/flag from sp+0x4C/0x50 to sp+0x50/0x54.  A scalar `s32 sxy` read through
 *     `*(u16 *)&sxy` keeps the 4-byte slot.  (Same reason the RTP_SND sibling packs its
 *     sxy/z/flag into ONE struct.)  `s32 mv[4]` + `V8_801806D8 pad[2]` are the 0x10..0x2F filler that
 *     makes vars = 0x48 ⇒ frame 0x68.
 *
 *  3. §21 ZERO-BYTE RE-TIE on `vol`.  Both magic-multiplies write the same match_scratch, so
 *     sched1 (the PRE-reload pass — verified with -fno-schedule-insns/-insns2) is free to swap
 *     them and always hoisted the PAN multiply first, inverting the whole tail schedule and
 *     losing the mfhi→mult hazard nop.  Source statement order does NOT move it (9 spellings
 *     swept, all identical); only the re-tie does.  Worth +2 ins and 33 mismatches.
 *
 *  4. REUSE ONE VARIABLE FOR X AND PAN.  gcc-2.7.2 has no live-range splitting, so one C local
 *     == one hard register: writing `sx = (sx + 0xA0) / 0x14;` (instead of a fresh `pan`) is
 *     what keeps the pan field in $a2 — a separate `pan` local is a fresh allocno and takes the
 *     dying $v1 instead.  Register PINS on `pan` made it WORSE (6 → 10): a local `register`
 *     var is the hard reg for its whole range and evicts the block's temps.  Only `av` needed
 *     a pin ($a1).
 *     Sub-lever: `pan = pan << 8;` must be an IN-PLACE statement (`sll $a2,$a2,8`), not
 *     `(pan << 8)` in the expression — reorg can only steal the shift into the bne delay slot
 *     when it is dead on the fall-through, i.e. when dest == src.  That is the last +1 ins.
 *     Sub-lever: the OR must be spelled `vol | (0x3000 | sx)`.  fold's `associate:` rewrites
 *     `(VAR|CON)|ARG1` to `(CON|ARG1)|VAR`, which is what puts `ori ...,0x3000` on VOL and the
 *     plain `or` on the pan field — and this nesting is the only one of six spellings that
 *     also gets the commutative `or`'s operand order right.
 *
 * DECLARATION SURFACE (RE-AUDITED against the WHOLE TU — above AND below the splice point).
 *   The first audit only looked ABOVE the INCLUDE_ASM at TU:4680 and wrongly concluded that
 *   func_8012BE98 / func_8012B744 / func_8012BD3C / RotTransPers / D_800AF648 "appear nowhere".
 *   They are all declared by the banked sibling func_8018389C at TU:4846-4857, i.e. BELOW the
 *   splice, and cc1 reports only the FIRST conflict — so the byte-correct body was refused with
 *     "conflicting types for func_8012BE98 / func_8012B744".
 *   Every symbol below now carries the TU's ONE existing spelling VERBATIM; where the type
 *   disagreed with what this body wants, the disagreement is pushed to a cast at the USE site
 *   (lever A), which is zero-byte — re-verified MATCH (237 ins) after the change.
 *
 *   copied VERBATIM from their existing TU spellings —
 *     ((void (*)(s32, s32))func_8012A828)(TU:3527 et al), func_8012B608 (4163/4240/4848),
 *     func_8012B1B4 (4164/4241/4697/4849), func_8012CBA4 (4343/4699/4850),
 *     func_8004787C (2206/4700), func_80047948 (2205/4701), func_80133784 (599/4702),
 *     func_8002D4C8 (59/4855), func_8004914C / func_800491AC (2646/2647/4852/4853),
 *     RotTransPers (4854/5017), D_800AF648 (4857/5025), D_801ABAE4 (5378),
 *     func_8012BD3C (4851),
 *     func_8012BE98 (4846, `extern void func_8012BE98(s32 a0, u16 *a1)`)  <- CONFORMED,
 *     func_8012B744 (4847, `extern s32 func_8012B744(void *a0, void *a1)`) <- CONFORMED.
 *   USE-SITE casts that absorb the two conformed types (same idiom as the sibling at TU:4876) —
 *     ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim)   -- void-declared, returns s32
 *     func_8012B744((void *)(a0 + 4), (void *)anim)           -- s32 args -> void * params
 *   NOT declared anywhere in the TU (so this form is free) — D_801AB454 only.
 *     D_801AB454 is a real dlabel in asm/ov_SC02_026/data/tail.data.s:60402.
 *   func_801806D8 itself has NO prototype anywhere in the TU or in any included header (only
 *   the INCLUDE_ASM at 4680), so no §37/§124 asm-label alias is needed on the defined symbol.
 *   The TU includes ../shared/engine_core.h but expands ZERO DEFINE_func_*()/DEFINE_data_*()
 *   macros (verified by grep), so that header contributes no file-scope declaration here.
 *   The conformed func_8012B744 type is also the fleet-dominant one (engine_core.h:3723) and
 *   RotTransPers' is the one engine_core.h:108 uses, so both stay compatible if a macro is
 *   ever spliced in.
 */

extern void func_8012A828(s32*, s32);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_801806D8(s32 a0) {

    extern u8 D_800AF648;
    extern u8 D_801ABAE4[];
    extern u8 D_801AB454[];
    s32 mv[4];   /* sp+0x10 : the 4-word block handed to func_8012B1B4 */
    V8_801806D8 pad[2];   /* sp+0x20 : gcc's own area (vars must be 0x48 for a 0x68 frame) */
    V8_801806D8 sp30;     /* sp+0x30 : func_80133784 arg1 */
    V8_801806D8 sp38;     /* sp+0x38 : func_80133784 arg2 */
    s16 v[4];    /* sp+0x40 : RotTransPers arg0 */
    s32 sxy;     /* sp+0x48 : DVECTOR — see lever 2, a u16[2] here costs 8 bytes */
    s32 z;       /* sp+0x4C */
    s32 flag;    /* sp+0x50 */
    s32 anim;
    s32 r;
    s32 t;

    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801ABAE4);
        *(s16 *)(a0 + 0xFE) = 0;
    }

    anim = a0 + 0x88;
    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim) >= 0x1000) {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), (void *)anim), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    mv[0] = 0;
    mv[1] = 0;
    mv[2] = -(*(s16 *)(a0 + 0xFC) << 17) / 0x18;
    func_8012B1B4(a0, (s32)mv);

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        s32 d;
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B744((void *)(a0 + 4), (void *)anim), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp30.x = *(u16 *)(a0 + 0x6) - ((t * r) >> 12);
    sp30.y = *(u16 *)(a0 + 0xA) - 0x20;
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp30.z = *(u16 *)(a0 + 0xE) - ((t * r) >> 12);
    sp38.x = sp30.x;
    sp38.y = sp30.y + 0x60;
    sp38.z = sp30.z;

    if ((func_80133784(1, &sp30, (s32)&sp38) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    if (*(s16 *)(a0 + 0xFE) == 0 && func_8012BD3C(a0, 0x200, 0x40000) == 1) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AB454);
        *(s16 *)(a0 + 0x2) = 2;
        v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes: rematerialise &D_800AF648 (lui/addiu) before EACH call */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)v, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0x9F) & 0xFFFF) < 0x13F
                      && (u32)((*((u16 *)&sxy + 1) + 0x77) & 0xFFFF) < 0xEF) {
            s32 sx;                             /* screen X, then REUSED as the pan field */
            register s32 av __asm__("$5");      /* |X| — the one pin that helped */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
            s32 vol;
            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;                       /* in place, so reorg can steal it */
            func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
        }
    }

    if (*(s16 *)(a0 + 0xFC) == 0x18) {
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   func_8012B1B4  TU:3931/4008/4455/4529
 *   func_8012B8E4  TU:4456/4528   (not declared above the splice; same form)
 *   func_8012CBA4  TU:4110/4457   (void return -> cast at the use site)
 *   func_8004787C  TU:2206/3652/4190/4458
 *   func_80047948  TU:2205/3651/4459
 *   func_80133784  TU:599/855/4460
 *   func_8012BCCC  TU:3928/4005/4461
 *   func_8012BDBC  TU:4462/5984
 *   func_8012A828  TU:3527/3810/…/4463 (23 decls, all this form)
 *   rand           TU:957/4154/4189/4214/4622
 *   D_801AC5EC     TU:4800/5275/5298 as `extern u8 D_801AC5EC[]`
 * D_801AC3E4 / D_801ABD64 appear nowhere else in the TU; same canonical form. */
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 rand(void);

void func_80180A8C(s32 a0) {

    extern u8 D_801AC3E4[];
    extern u8 D_801ABD64[];
    extern u8 D_801AC5EC[];
    s32 sp10[4];
    V8_80180A8C pad[2];
    V8_80180A8C sp30;
    V8_80180A8C sp38;
    s32 t;
    s32 r;
    s32 v;

    *(s16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = (*(s16 *)(a0 + 0xFC) * -0x20000) / 0x24;
    func_8012B1B4(a0, (s32)sp10);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    v = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp30.x = *(u16 *)(a0 + 0x6) - ((v * r) >> 12);
    sp30.y = *(u16 *)(a0 + 0xA) - 0x20;
    v = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp30.z = *(u16 *)(a0 + 0xE) - ((v * r) >> 12);
    sp38.x = sp30.x;
    sp38.y = sp30.y + 0x60;
    sp38.z = sp30.z;

    if ((func_80133784(1, &sp30, (s32)&sp38) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    t = func_8012BCCC(a0);
    if (t < 0x1001) {
        if (func_8012BDBC(a0, 0x200) == 1) {
            s32 s;
            if ((rand() & 3) == 0) {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AC3E4);
                s = 0x5;
            } else {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801ABD64);
                s = 0xF;
            }
            *(s16 *)(a0 + 0x2) = s;
        }
    }
    if (t > 0x40000) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AC5EC);
        *(s16 *)(a0 + 0x2) = 1;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 1;
    }
    if (*(s16 *)(a0 + 0xFC) == 0x24) {
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



/* func_80180CCC — ov_SC02_026 jr_8017C180 family exemplar (15 members).
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND block from src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.c:3480
 * (func_8017E120) — `u16 sxy[2]`, the `(u32)((sxy[i] + K) & 0xFFFF) < N`
 * range tests, the explicit `(s16)sxy[0]` sign-extension (sll/sra off the
 * already-loaded lhu), and the $a0-pinned scopes that REMATERIALISE
 * &D_800AF648 per call instead of letting CSE hoist it into a callee-saved
 * register (which would shove the actor out of $s0).
 *
 * The head (func_8012B608 accumulate + &0xFFF) copies the form banked at
 * TU:3941 (func_80180C80) / TU:4478 (func_80183B04).  Head + RTP were right on
 * the first compile (115/154); the panner tail took SIX levers, each measured:
 *
 *  1. FRAME PADDING (idiom 6).  Locals start at sp+0x10 (the o32 outgoing-arg
 *     area) but the RTP block is at sp+0x20, so 16 bytes of padding precede it.
 *     It must be an AGGREGATE — a scalar becomes a pseudo and vanishes; only
 *     assign_stack_local aggregates size the frame.  vars 0x28 => frame 0x48.
 *
 *  2. THE abs TESTS `x`, NOT `ax`.  Target is
 *         bgez $a2,L / addu $a1,$a2,$zero (DELAY SLOT) / negu $a1,$a2 / L:
 *     i.e. `ax = x; if (x < 0) ax = -x;`.  The textbook `if (ax < 0) ax = -ax;`
 *     makes the branch DEPEND on the copy, so reorg cannot sink `move ax,x`
 *     into the delay slot: it emits the copy first and fills the slot with the
 *     divide magic's `lui` (12 off).  `__builtin_abs` is the WRONG lever here —
 *     it is one abssi2 insn, the block never splits, and the whole divide pair
 *     re-schedules (22 off).
 *
 *  3. $a1-PIN ON THE abs RESULT (§40 / ov_SC03_006_jr_8012ACE0.c:816).
 *     Unpinned, local-alloc's combine_regs ties the abs dest to its dying input
 *     and every downstream register shifts (12 off).  Pin ONLY the abs result:
 *     pinning `x` or the pan quotient re-seats the divide chain (17 / 8 off).
 *
 *  4. ZERO-BYTE RE-TIE ON `vol` (§21 / S4).  Both divides share one HI/LO, so
 *     the scheduler must choose which `mult` issues first, and priority is
 *     height-to-block-end: the pan quotient feeds the `bne`, so it wins and the
 *     vol chain sinks (41 off, -2 ins).  A NON-volatile
 *     `__asm__("" : "=r"(vol) : "0"(vol));` gives `vol` a free in-block
 *     consumer, flipping the chains back to the target's
 *     `mult / mfhi $t1 / addiu / nop / mult` (that `nop` is the mfhi->mult
 *     hazard and IS in the target).  A *volatile* asm over-serialises (35 off).
 *
 *  5. THE PAN QUOTIENT IS THE SAME VARIABLE AS `x` (§136 L1 — the Ghidra seed
 *     had this right, it reuses iVar5).  Target's `subu $a2,$v1,$v0` puts the
 *     quotient back in x's register; a separate `pan` local is a fresh global
 *     allocno and takes $v1 (earlier in REG_ALLOC_ORDER) — 6 off, and no pin
 *     fixes it.
 *
 *  6. 0x3000 IN A LOCAL, NOT A LITERAL.  fold reassociates
 *     `(vol | 0x3000) | pan` into `vol | (pan | 0x3000)`, landing the `ori` on
 *     the shifted pan — in EVERY literal spelling swept (2-5 off).  Hoisting it
 *     into `flg` leaves no constant for fold to move, and keeping the OR inside
 *     the call ARGUMENT preserves the target's `addiu $a0,0xA9B` -> `ori` ->
 *     `or` order (a standalone `vol |= 0x3000;` statement fixes the tree but
 *     swaps those two, 2 off).
 *
 * Declarations: func_8012B608 / func_8012B1B4 / func_8012CBA4 /
 * func_8004914C / func_800491AC / func_8002D4C8 / D_8019F39C are copied
 * VERBATIM from the TU (lines 3930, 3931, 4110, 2646, 2647, 59, 4464).
 * func_8012BE98 / func_8012B744 / func_8012BD3C / RotTransPers / D_800AF648
 * appear NOWHERE in the TU, so the fleet-dominant forms are used and the
 * return value of the `void`-declared func_8012BE98 is taken through a cast
 * at the call site (idiom 9).
 */

extern void func_8012BE98(s32 a0, u16 *a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_80180CCC(s32 a0) {

    extern u8 D_800AF648;
    extern u8 D_8019F39C[];
    /* locals start at sp+0x10 (the 16-byte outgoing-arg area).  The first
       16 bytes are unreferenced in this function but are part of the
       frame — vars must be 0x28, i.e. frame 0x48. */
    struct {
        s32 pad0[4];   /* sp+0x10 */
        s16 v[3];      /* sp+0x20 */
        s16 pad1;      /* sp+0x26 */
        u16 sxy[2];    /* sp+0x28 */
        s32 z;         /* sp+0x2C */
        s32 flag;      /* sp+0x30 */
    } L;
    void *p88;

    p88 = (void *)(a0 + 0x88);

    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88) >= 0x1000) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    func_8012B1B4(a0, (s32)D_8019F39C);

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        s32 r2;
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        r2 = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                           func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r2;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    if (func_8012BD3C(a0, 0x200, 0x40000) == 1) {
        *(s16 *)(a0 + 0x2) = 7;
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* The target loads &D_800AF648 afresh (lui/addiu $a0) for EACH call.  The
         * second call names the object through a second declaration of the same
         * symbol: its SYMBOL_REF string is a different pointer, so cse does not
         * unify the two address pseudos into one callee-saved register. */
        func_8004914C(&D_800AF648);
        {
            extern u8 D_800AF648_b __asm__("D_800AF648");
            func_800491AC(&D_800AF648_b);
        }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 x = (s16)L.sxy[0];
            s32 vol = x;
            if (vol < 0) {
                vol = -vol;
            }
            vol = ((0xA0 - vol) * 0x7F) / 0xA0;
            x = (x + 0xA0) / 0x14;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            func_8002D4C8(0xA9B, (vol | (0x3000 | x)) & 0xFFFF);
        }
    }
}



extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_80180F34(s32 a0) {

    extern u8 D_8019F39C[];
    extern u8 D_801AC0A4[];
    V8_80180F34 pad[2];
    V8_80180F34 sp20;
    V8_80180F34 sp28;
    s32 t;
    s32 r;
    s32 v;

    func_8012B1B4(a0, (s32)D_8019F39C);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    v = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp20.x = *(u16 *)(a0 + 0x6) - ((v * r) >> 12);
    sp20.y = *(u16 *)(a0 + 0xA) - 0x20;
    v = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp20.z = *(u16 *)(a0 + 0xE) - ((v * r) >> 12);
    sp28.x = sp20.x;
    sp28.y = sp20.y + 0x60;
    sp28.z = sp20.z;

    if ((func_80133784(1, &sp20, (s32)&sp28) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    t = func_8012BCCC(a0);
    if (t < 0x2401) {
        if (func_8012BDBC(a0, 0x200) == 1) {
            *(s16 *)(a0 + 0x2) = 0x11;
            ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AC0A4);
        }
    }
    if (t > 0x40000) {
        *(s16 *)(a0 + 0x2) = 6;
    }
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c) where they
 * already exist, so the splice introduces no conflicting types:
 *   func_8002D4C8  TU:59/3245/3279/4619/4909/…  `void (s32,s32)`
 *   func_8012BCCC  TU:3928/4005/4461            `s32 (s32)`
 *   func_8012A828  TU:3527/3810/…/4463          `void (s32,s32)` (23 decls, all this form)
 *   func_8012B8E4  TU:4456/4528                 `s32 (s32,s32)`
 *   func_8012B1B4  TU:3931/4008/4455/4529       `void (s32,s32)`
 *   func_8012CBCC  TU:3907/3932/4530            `void (s32)`
 *   func_8004914C  TU:2646                      `void (void *)`
 *   func_800491AC  TU:2647                      `void (void *)`
 *   D_80126B62     TU:1793/4533                 `u16` -> cast to s16* at the use site
 *   D_8019F0D4     TU:4722 (block scope)        `s32`  -> `(s32)&D_8019F0D4 | …` (line 4753)
 * RotTransPers / D_800AF648 are not declared in this TU; the forms below are the
 * fleet-canonical ones (ov_SC02_026_jr_80140608.c:416/2312, o0c.c:365/371).
 * D_801ACBF4 / D_8019F3A8 appear nowhere else in the TU (real dlabels in
 * asm/ov_SC02_026/data/tail.data.s:61984 / :47419); same canonical `extern s32` form
 * as the neighbouring D_801BD190 (TU:4385). */
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8012A828(s32*, s32);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);


void func_801810DC(s32 a0) {

    extern u8 D_800AF648;
    extern s32 D_801ACBF4;
    extern s32 D_8019F0D4;
    extern s32 D_8019F3A8;
    extern u16 D_80126B62;
    /* sp+0x10 local block.  Frame is 0x38 = 0x10 outgoing args + 0x20 vars +
     * 8 saved regs ($s0,$ra), so the vars block is 12 bytes larger than the
     * fields this function actually touches -> trailing `unused[3]`. */
    struct {
        s16 v[3];      /* sp+0x10 */
        s16 pad0;      /* sp+0x16 */
        u16 sxy[2];    /* sp+0x18 */
        s32 z;         /* sp+0x1C */
        s32 flag;      /* sp+0x20 */
        s32 unused[1]; /* sp+0x24 */
    } L;
    s16 x;
    s32 y;

    if (*(s32 *)(a0 + 0x94) == 0xD) {
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialised
         * per call (cookbook §88a); otherwise CSE parks it in a callee-saved reg
         * and mis-seats every register in the function. */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 vol = (s16)L.sxy[0];
            if (vol < 0) {
                vol = -vol;
            }
            vol = ((0xA0 - vol) * 127) / 160;
            func_8002D4C8(0x702, (vol | 0x1000) & 0xFFFF);
        }
    }

    if (func_8012BCCC(a0) <= 0x24000) {
        s16 c;
        c = *(u16 *)(a0 + 0x102) + 1;
        *(s16 *)(a0 + 0x102) = c;
        if (c >= 0x78) {
            if ((*(u16 *)(a0 + 0x100) & 0x2000) == 0) {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801ACBF4);
                *(s16 *)(a0 + 0x2) = 10;
                *(s16 *)(a0 + 0x102) = 0;
                *(s32 *)(a0 + 0x58) = (s32)&D_8019F0D4 | 0x40000000 | 0x20000000;
            }
        }
    }

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    x = *(s16 *)(a0 + 0xA);
    y = *(s16 *)&D_80126B62;
    if (x <= y - 0x100) {
        *(s16 *)(a0 + 0xA) = x + 0x8;
    } else if (x >= y - 0x80) {
        *(s16 *)(a0 + 0xA) = x - 0x8;
    }

    func_8012B1B4(a0, (s32)&D_8019F3A8);
    func_8012CBCC(a0);
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c) where they
 * already exist, so the splice introduces no conflicting types:
 *   func_8012B1B4  TU:3892/3969/4452/4498/4623
 *   func_8012CBCC  TU:3868/3893/3970/4665/4824
 *   D_80126B5C     TU:362   (u8  -> cast to s32* at the use site, the load is `lw`)
 *   D_80126B62     TU:1793  (u16 -> cast to s16* at the use site, the load is `lh`)
 * func_8012B8E4 and D_80126B64 are not yet declared in this TU; the forms below are
 * the ones used everywhere else in src/ (s32 return / extern s32). */
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);


void func_80181328(s32 a0) {

    extern u8 D_80126B5C;
    extern u16 D_80126B62;
    extern s32 D_80126B64;
    /* sp10[0..3] is the 4-word block handed to func_8012B1B4 ($a1 = sp+0x10).
     * The frame's extra 8 bytes at sp+0x20 are gcc's OWN spill area (cookbook
     * §83c) -- declaring them as a 6th/5th array element makes the frame 0x40. */
    s32 sp10[4];
    s16 t;
    s32 y;

    if (*(s32 *)(a0 + 0x94) == 0xA) {
        *(s16 *)(a0 + 0x98) = 0;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x4);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    sp10[0] = 0;
    sp10[1] = 0;

    sp10[2] = *(s32 *)(a0 + 0x4) - *(s32 *)&D_80126B5C;
    if (sp10[2] > 0) {
        sp10[2] = -sp10[2];
    }
    sp10[3] = *(s32 *)(a0 + 0xC) - D_80126B64;
    if (sp10[3] > 0) {
        sp10[3] = -sp10[3];
    }
    sp10[2] = (sp10[2] + sp10[3]) >> 4;
    func_8012B1B4(a0, (s32)sp10);

    t = *(s16 *)(a0 + 0xA);
    y = *(s16 *)&D_80126B62;
    if (t <= y - 0xA) {
        *(s16 *)(a0 + 0xA) = t + 0x8;
    } else if (t >= y) {
        *(s16 *)(a0 + 0xA) = t - 0x8;
    } else if (*(s32 *)(a0 + 0x94) == 0xA) {
        *(s16 *)(a0 + 0x2) = 0xB;
        *(s16 *)(a0 + 0x98) = 1;
    }

    func_8012CBCC(a0);
}




void func_80181474(u8 *s0) {

    extern void (*D_8019F3C0[])(void *);
    extern u8 D_801202A0[];
    u16 v0;
    s32 a0;
    u8 *v1;

    // Call indirect function based on index at s0[2]
    v0 = *(u16 *)(s0 + 0x2);
    ((void (*)(u8 *))D_8019F3C0[v0])(s0);

    // Check if s0[0] is zero
    v0 = *(u16 *)(s0);
    if (v0 == 0) return;

    // Check if s0[0x100] & 0x1000 is zero
    v0 = *(u16 *)(s0 + 0x100);
    if ((v0 & 0x1000) == 0) return;

    // Search for entry in D_801202A0 table
    v1 = D_801202A0;
    for (a0 = 0; a0 < 0x60; a0++) {
        if (*(u16 *)(v1) == 0x15E) {
            s16 v1_val = *(s16 *)(v1 + 0x6);
            s16 s0_val = *(s16 *)(s0 + 0x6);
            if (s0_val < v1_val + 0xF0) {
                *(s16 *)(s0 + 0x6) = v1_val + 0xF0;
            }
            return;
        }
        v1 += 0x10C;
    }
}





extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018152C(s32 param_1)
{

    extern s32 D_801151D4;
    s32 sp10[4];
    s32 sp20;
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(param_1 + 0x1C);
    v1 = D_801151D4;
    *(s32 *)(param_1 + 0x1C) = v0 - 1;
    *(s16 *)((s32)sp10 + 0x2) = *(s32 *)(v1 + 0x5C);
    *(s16 *)((s32)sp10 + 0x6) = *(s32 *)(v1 + 0x60);
    *(s16 *)((s32)sp10 + 0xA) = *(s32 *)(v1 + 0x64);
    func_8012B77C((s32)&sp20, param_1 + 4, (s32)sp10);

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (sp20 + 0x400) & 0xFFF;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) += 0x55;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) += 0x55;

    v1 = *(s32 *)(param_1 + 0x1C);
    if (v1 == 0xF) {
        func_8002D4C8(0xCBA, 0);
        v1 = *(s32 *)(param_1 + 0x1C);
    }
    if (v1 < 0x10) {
        if (v1 == 0) {
            func_8012C218((void *)param_1);
        } else {
            param_1 = func_80143C74(param_1, 0);
            if (param_1 != 0) {
                *(s16 *)(param_1 + 0x16) = -4;
                v0 = rand();
                *(s16 *)(param_1 + 0x12) = (v0 & 7) - 4;
                v0 = rand();
                *(s16 *)(param_1 + 0x1A) = (v0 & 7) - 4;
                v0 = rand();
                { s32 t = *(u16 *)(param_1 + 0x6) - 0x10; *(s16 *)(param_1 + 0x6) = t + (v0 & 0x1F); }
                v0 = rand();
                { s32 t = *(u16 *)(param_1 + 0xE) - 0x10; *(s16 *)(param_1 + 0xE) = t + (v0 & 0x1F); }
            }
        }
    }
}



extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);
extern void func_8012B370(void *a0);

void func_80181680(void *a0) {

    extern void (*D_8019F450[])(void *);
    u16 temp;
    s32 a1;

    D_8019F450[*(u16 *)((s32)a0 + 0x2)](a0);

    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        temp = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        a1 = (s32)(temp << 16) >> 24;
        if (func_8012D624(a0, a1, 0x14) == 1) {
            func_8012C218(a0);
        } else {
            *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            func_8012B370(a0);
        }
    }
}




extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);

void func_8018172C(void *a0) {

    extern void (*D_8019F5B0[])(void);
    extern u16 D_80126B96;
    u16 *q;

    D_8019F5B0[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        if (func_8012D624(a0, 0x10, 0x16) == 1) {
            q = &D_80126B96;
            *q |= 0x200;
            func_8012C218(a0);
        } else {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
        }
    }
}




void func_801817DC(void *a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);
    extern void func_80131E00(void *a0, s32 a1);
    extern s32 D_801AC974;
    extern s32 D_8019F23C;
    extern s32 D_8019F0D4;

    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    *(u16 *)(&buf[0]) = v0;
    *(u16 *)(&buf[4]) = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    *(u16 *)(&buf[1]) = v1;
    *(u16 *)(&buf[5]) = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)(&buf[1]) = v0;
    *(u16 *)(&buf[5]) = (v1 + 8);
    *(u16 *)(&buf[2]) = a2;
    *(u16 *)(&buf[6]) = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) != 0) {
        func_80131E00(a0, 6);
    } else {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801AC974);
        *(u16 *)((s32)a0 + 0x2) = 1;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xAA10;
        *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019F23C;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_8019F0D4 | 0x40000000 | 0x20000000;
        *(s16 *)((s32)a0 + 0x88) = *(u16 *)((s32)a0 + 0x6);
        *(s16 *)((s32)a0 + 0x8A) = *(u16 *)((s32)a0 + 0xA);
        *(s16 *)((s32)a0 + 0x8C) = *(u16 *)((s32)a0 + 0xE);
    }
}




/* func_801818C4 — "ground-collision probe, then either bounce-off or pick a state script"
 * (jr_8017C180 family; byte-verified MATCH, 71 ins).
 *
 * Declaration provenance (whole-TU grep in one pass, cookbook §135-8 / D2 — every symbol below
 * checked BOTH above and below the splice point at ov_SC02_026_jr_8017C180.c:4748):
 *   func_8012CEB0(s32,s32,s32)  — TU decls at 4365 (file scope) / 4704 / 4851, identical form
 *   ((void (*)(s32, s32))func_8012A828)(s32,s32)      — 23 TU decls, all this form (or the unnamed-param twin)
 *   func_80131E00(void*,s32)    — TU fn-scope decls at 4706 / 4853, identical form
 *   D_801AC5EC                  — declared BELOW the splice point at 5158 as `extern u8 D_801AC5EC[]`;
 *                                 that exact type is reused here so the two cannot conflict
 *   D_801AAD24 / D_801AAF2C / D_801ABAE4 — real dlabels in asm/ov_SC02_026/data/tail.data.s,
 *                                 declared nowhere else in this TU (D_801ABAE4's `void (*[])(void)`
 *                                 decl lives in a DIFFERENT TU, ov_SC03_125, so it is not a conflict)
 *
 * Codegen notes:
 *  - The buf[8] halfword-pair setup + the three $2/$3/$6 pins are the byte-verified twin of
 *    func_801843AC in THIS TU (line 4703). The doubled buf[1]/buf[5] stores are real: the ±8
 *    adjust is a SECOND store to the same slot, and §135-4 (the list scheduler preserves the
 *    relative order of disambiguable stores) is what emits sh/sh then sh/sh off one lhu of a0+0xA.
 *  - 0x5C takes `ori $v0,$zero,0xAA10`, so the destination must be UNSIGNED (§135-3): through a
 *    s16 the constant folds negative and gcc emits `addiu` instead.
 *  - The 0x100 |= 0x8000 arm needs the plain `x = x | 0x8000` read-modify-write; gcc allocates the
 *    address pseudo to $a0 (the pending call arg) on its own, which is why the lhu/sh are
 *    $a0-based while everything else is $s0-based.
 *  - THE RESIDUAL THAT DECIDED THIS FUNCTION: the D_801AC5EC/D_801ABAE4 selector must be TWO
 *    SEPARATE CALLS, not a `tbl = cond ? A : B;` select feeding one call. With a select, both
 *    arms are single sets of the same pseudo, and gcc-2.7.2's jump.c rewrites
 *    `if (c) t=A; else t=B;` into `t=B; if (c) t=A;` — the D_801ABAE4 lui/addiu hoists ABOVE the
 *    beqz and the whole tail shifts (-3 ins, LENGTH-DRIFT, 20 mismatches). Two calls are not
 *    simple sets, so the transform cannot fire; cross_jump then merges only the common
 *    [move $a0,$s0; jal] tail, which is exactly the target's j-over-arm shape.
 */

extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32*, s32);
extern void func_80131E00(void *a0, s32 a1);

void func_801818C4(void *a0) {

    extern u8 D_801AAD24[];
    extern u8 D_801AAF2C[];
    extern u8 D_801ABAE4[];
    extern u8 D_801AC5EC[];
    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    buf[0] = v0;
    buf[4] = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    buf[1] = v1;
    buf[5] = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    buf[1] = v0;
    buf[5] = (v1 + 8);
    buf[2] = a2;
    buf[6] = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) != 0) {
        *(u16 *)((s32)a0 + 0x100) = *(u16 *)((s32)a0 + 0x100) | 0x8000;
        func_80131E00(a0, 6);
    } else {
        if (*(s32 *)((s32)a0 + 0x90) == (s32)&D_801AAF2C) {
            ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801AAD24);
            *(u16 *)((s32)a0 + 0x2) = 0x14;
            *(u16 *)((s32)a0 + 0x34) = 1;
            *(s16 *)((s32)a0 + 0xFE) = 0;
            *(s32 *)((s32)a0 + 0xCC) = (s32)&D_801ABAE4;
        } else {
            if (*(s16 *)((s32)a0 + 0xFE) != 0) {
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801AC5EC);
            } else {
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801ABAE4);
            }
            *(u16 *)((s32)a0 + 0x2) = 1;
        }
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xAA10;
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);

extern void func_8012C098(void *param_1);

void func_801819E0(s32 a0) {
    s32 ent;

    if (*(u16 *)a0 != 0) {
        if (*(s16 *)(a0 + 0x70) == 4) {
            ent = func_8012C658(0x12C, 4, a0);
            if (ent != 0) {
                *(u16 *)(ent + 0x6) = *(u16 *)(a0 + 0x88);
                *(u16 *)(ent + 0x88) = *(u16 *)(a0 + 0x88);
                *(u16 *)(ent + 0xE) = *(u16 *)(a0 + 0x8C);
                *(u16 *)(ent + 0x8C) = *(u16 *)(a0 + 0x8C);
                *(u16 *)(ent + 0xA) = *(u16 *)(a0 + 0x8A) - 0x400;
                *(u16 *)(ent + 0x8A) = *(u16 *)(a0 + 0x8A);
                func_8012B2CC(ent);
            }
        }
        if (func_80153BD8(a0)) {
            func_80153BF0(a0);
        }
        if (*(s32 *)(a0 + 0x78) != 0) {
            func_8002A04C(a0);
        }
        func_8012C098((void *)a0);
    }
}



extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

void func_80181AC0(s32 a0) {

    extern u8 D_8019F0B8[];
    V8_80181AC0 sp10;
    V8_80181AC0 sp18;

    if (*(s32 *)(a0 + 0x94) >= 8) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8012B1B4(a0, (s32)D_8019F0B8);
        if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
            sp10.x = *(u16 *)(a0 + 0x3A);
            sp10.y = *(u16 *)(a0 + 0x3E);
            sp10.z = *(u16 *)(a0 + 0x42);
            sp18 = sp10;
            sp18.y += 8;
            if (func_80133784(1, &sp10, (s32)&sp18) != 0) {
                *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
            }
        }
    }
}




extern void func_80131B14(void);
extern void func_8012B23C(void *a0);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181B98(s32 a0) {
    s32 s0 = a0;
    u16 v0 = *(u16 *)(s0 + 0x100);
    u16 v1 = *(u16 *)(s0 + 0x60);

    v0 |= 0x8000;
    v1 <<= 2;

    *(u16 *)(s0 + 0x100) = v0;
    *(u16 *)(s0 + 0x60) = v1;
    func_80131B14();

    *(u8 *)(s0 + 0xC2) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    func_8012B23C((void *)s0);

    func_80131A34(s0, 0x8);
    func_8002D4C8(0xA74, 0);
}


extern s32 func_80153BD8(s32 arg);
    extern s32 func_80153BF0(s32 a0);
    void func_80181C00(u8 *a0) {
        *(s16 *)(a0 + 0xfe) = 0;
        if (func_80153BD8((s32)a0)) {
            ((void (*)(void *))func_80153BF0)(a0);
        }
    }




/* Modeled on the byte-matched sibling func_801843AC in the same TU
 * (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:4677-4719): identical two-box
 * build + func_8012CEB0 collision probe, differing only in the mask (0x19 vs
 * 0x1F) and the else-arm payload. All declarations are block-scope and copied
 * verbatim from the TU so the splice introduces no conflicting types. */

void func_80181C3C(void *a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);
    extern void func_80131E00(void *a0, s32 a1);
    extern char D_801ACA5C[];

    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    *(u16 *)(&buf[0]) = v0;
    *(u16 *)(&buf[4]) = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    *(u16 *)(&buf[1]) = v1;
    *(u16 *)(&buf[5]) = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)(&buf[1]) = v0;
    *(u16 *)(&buf[5]) = (v1 + 8);
    *(u16 *)(&buf[2]) = a2;
    *(u16 *)(&buf[6]) = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x19) != 0) {
        func_80131E00(a0, 6);
    } else {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801ACA5C);
        *(u16 *)((s32)a0 + 0x2) = 6;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xA810;
    }
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c:4453-4456),
 * so the splice introduces no conflicting types. Type disagreements are pushed
 * to casts at the use sites (cookbook §37 lever A) — codegen-neutral. */
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

void func_80181CE0(s32 *s0) {

    extern u8 D_8019F0B8[];

    Data_t_80181CE0 buf_src, buf_dst;
    s32 v0;

    func_8012B1B4((s32)s0, (s32)D_8019F0B8);

    v0 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if (v0 & 0x6000) {
        return;
    }

    // Load halfwords from s0
    buf_src.a = *(u16 *)((u8 *)s0 + 0x3A);
    buf_src.b = *(u16 *)((u8 *)s0 + 0x3E);
    buf_src.c = *(u16 *)((u8 *)s0 + 0x42);

    // Struct assignment generates lwl/lwr + swl/swr
    buf_dst = buf_src;

    // Modify the b field of buf_dst (at offset 2)
    buf_dst.b += 8;

    v0 = func_80133784(1, &buf_src, (s32)&buf_dst);
    if (v0 == 0) {
        return;
    }

    // Copy three words
    *(s32 *)((u8 *)s0 + 0x04) = *(s32 *)((u8 *)s0 + 0x38);
    *(s32 *)((u8 *)s0 + 0x08) = *(s32 *)((u8 *)s0 + 0x3C);
    *(s32 *)((u8 *)s0 + 0x0C) = *(s32 *)((u8 *)s0 + 0x40);
}




extern void func_8012B14C(s32 a0, s32 a1);

void func_80181DA0(s32 a0)
{

    extern u8 D_8019F0C8[];
    *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) & -5;
    func_8012B14C(a0, (s32)D_8019F0C8);
}


extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);

void func_80181DD4(s32 a0)
{
    s32 v0;

    if (*(u8 *)((s32)a0 + 0x5E) == 0x23) {
        *(u16 *)((s32)a0 + 0x100) |= 0x4000;
    }
    v0 = func_80153BD8(a0);
    if (v0 != 0) {
        func_80153BF0(a0);
    }
}


extern s32 func_80153BD8(s32 arg);
    extern s32 func_80153BF0(s32 a0);
    void func_80181E30(s32 arg0) {
        if (func_80153BD8(arg0)) {
            ((void (*)(s32))func_80153BF0)(arg0);
        }
    }




extern void func_8012A828(s32*, s32);

void func_80181E68(s32 a0)
{

    extern u8 D_801AB5C4[];
    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AB5C4);
        *(s16 *)(a0 + 0x2) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 1;
    }
}




extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32*, s32);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80153C74(s16 a0, s16 a1);


void func_80181EC4(s32 a0) {

    extern u8 D_801AB5C4[];
    extern s32 aD801AF930 __asm__("D_8019F37C");
    extern s32 aD801AF938 __asm__("D_8019F384");
    s32 val;

    if (func_80153BD8(a0) == 0) {
        ((void (*)(s32))func_80153BF0)(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AB5C4);
        *(s16 *)(a0 + 0x2) = 0x13;
        *(s16 *)(a0 + 0x34) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
    }

    if ((*(s32 *)(a0 + 0x94) == 0xA) || (*(s32 *)(a0 + 0x94) == 0x1A)) {
        if (func_8012DEB8(a0, (s32)&aD801AF930, (s32)&aD801AF938) == 1) {
            func_8002D4C8(0xCB2, 0);
            val = *(u16 *)(a0 + 0x70) - 2;
            if ((u32)val < 2) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_80181F9C(void *a0) {

    extern u8 D_801AB5C4[];
    s16 val70;
    u16 val72;

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        val70 = *(s16 *)(a0 + 0x70);
        if (val70 == 0x2) {
            func_8012C588(0x1A7, (s32)a0);
        } else {
            func_8002D4C8(0xCB3, 0);
            func_8012C588(0x19F, (s32)a0);
        }
    }

    val72 = *(u16 *)(a0 + 0x72);
    if ((val72 & 0x4000) != 0) {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801AB5C4);
        *(s16 *)(a0 + 0x2) = 0x3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 0;
    }
}




extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32*, s32);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80153C74(s16 a0, s16 a1);


void func_80182030(s32 a0) {

    extern s32 aD801BC890 __asm__("D_801AC2DC");
    extern s32 aD801AF930 __asm__("D_8019F37C");
    extern s32 aD801AF938 __asm__("D_8019F384");
    u16 val;

    if (func_80153BD8(a0) == 0) {
        ((void (*)(s32))func_80153BF0)(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD801BC890);
        *(s16 *)(a0 + 0x34) = 7;
        *(s16 *)(a0 + 0x2) = 0x13;
        *(s32 *)(a0 + 0x1C) = 0x1E;
    }

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        if (func_8012DEB8(a0, (s32)&aD801AF930, (s32)&aD801AF938) == 1) {
            func_8002D4C8(0xCB2, 0);
            val = *(u16 *)(a0 + 0x70);
            if ((u16)(val - 2) < 2u) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}




extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_801820FC(s32 a0) {

    extern u8 D_8019F3B4[];
    extern u8 D_8019F38C[];
    extern u8 D_8019F394[];
    extern u8 D_801AB3AC[];
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    s32 result;
    u16 val70;
    u16 *q;

    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 0xC;
        func_8012B1B4(a0, (s32)D_8019F3B4);
        *(s16 *)(a0 + 0x16) = -0x8;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AB3AC);
        *(s16 *)(a0 + 0x98) = 0x1;
    }

    if (*(s32 *)(a0 + 0x94) == 0xF) {
        result = func_8012D5E4(a0, (s32)D_8019F38C, (s32)D_8019F394, 0x14);
        if (result == 1) {
            func_8002D4C8(0xCB2, 0);

            val70 = *(u16 *)(a0 + 0x70);
            if (((u32)val70 - 2) < 2) {
                q = &D_80126B96;
                D_80126B98 = 0x18;
                *q = *q | 0x2000;
            }
        }
    }
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012A828(s32*, s32);

void func_801821D4(s32 a0) {

    extern s32 aD_801BB960 __asm__("D_801AB3AC");
    extern s32 aD_801AF698 __asm__("D_8019F0E4");
    u16 temp;

    if (*(s32 *)(a0 + 0x94) == 0xD) {
        func_8002D4C8(0x702, 0x107F);
    }

    func_8012CBCC(a0);

    temp = *(u16 *)(a0 + 0x102) + 1;
    *(u16 *)(a0 + 0x102) = temp;

    if ((s16)temp == 0x1E) {
        *(u16 *)(a0 + 0x2) = 0x9;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD_801BB960);
        *(u16 *)(a0 + 0x102) = 0;
        *(s32 *)(a0 + 0x14) = 0;
        *(s32 *)(a0 + 0x58) = ((s32)&aD_801AF698 | 0x40000000) | 0x20000000;
    }
}




extern void func_8012CBCC(s32 a0);

void func_80182270(s32 a0) {
    s16 v = *(s16 *)(a0 + 0xFC);

    if (v != 0) {
        *(s16 *)(a0 + 0xFC) = v - 1;
    } else if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x6000) {
        *(s16 *)(a0 + 0x2) = 1;
    }
}


void func_801822C8(void) {
}


void func_801822D0(s32 entity) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_8019F37C[];
    extern u8 D_8019F384[];
    extern u8 D_801ABE6C[];
    extern u8 D_801AC5EC[];

    s32 result;

    result = func_8012DEB8(entity, (s32)&D_8019F37C, (s32)&D_8019F384);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = entity;
        *(u16 *)(entity + 0x2) = 0x10;
        ((void (*)(s32, s32))func_8012A828)(entity, (s32)&D_801ABE6C);
    } else {
        ((void (*)(s32, s32))func_8012A828)(entity, (s32)&D_801AC5EC);
        *(u16 *)(entity + 0x2) = 3;
        *(u16 *)(entity + 0xFC) = 0;
        *(u16 *)(entity + 0xFE) = 1;
    }
}




extern s32 func_80153BD8(s32 a0);
extern void func_8012A828(s32*, s32);

void func_80182370(s32 a0) {

    extern u8 D_801AC5EC[];
    s32 result;

    result = func_80153BD8(a0);
    if (result == 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801AC5EC);
        *(s16 *)(a0 + 0x2) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
    } else {
        *(s16 *)(a0 + 0x2) = 4;
    }
}



void func_801823C4(s32 a0) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_8019F37C[];
    extern u8 D_8019F384[];
    extern u8 D_801AC1AC[];
    extern char D_801ACA5C[];

    s32 result;

    result = func_8012DEB8(a0, (s32)&D_8019F37C, (s32)&D_8019F384);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = a0;
        *(u16 *)(a0 + 0x2) = 0x12;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801AC1AC);
    } else {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801ACA5C);
        *(u16 *)(a0 + 0x2) = 0x6;
    }
}




extern s32 func_80153BD8(s32);
extern void func_8012A828(s32*, s32);

void func_80182458(s32 a0)
{

    extern s32 aD801BC890 __asm__("D_801AC2DC");
    s32 v0;

    v0 = func_80153BD8(a0);
    if (v0 != 0) {
        v0 = 0x8;
    } else {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD801BC890);
        v0 = 0x6;
    }
    *(s16 *)(a0 + 0x2) = v0;
}



extern s32 func_8012BEE8(s32 a0);

void func_801824A0(int param_1)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x1c) - 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (*(int *)(param_1 + 0x1c) == 0) {
        *(short *)(param_1 + 2) = *(unsigned short *)(param_1 + 0x34);
    }
}




extern void func_8012A828(s32*, s32);

void func_801824C8(s32 a0)
{
    if (((*(u16 *)(a0 + 0x72) & 0x4000) != 0) || (*(s16 *)(a0 + 0x98) == 0)) {
        *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x34);
        ((void (*)(s32, s32))func_8012A828)(a0, *(s32 *)(a0 + 0xCC));
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_8012B23C(void *a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);


void func_80182514(s32 param_1)
{

    extern u8 D_8019F414[];
    extern u8 D_8019F42C[];
    extern u8 D_8019F444[];
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_8019F414);
        ((void (*)(s32, s32))func_8012A828)(param_1, (s32)D_8019F42C);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
        func_8012B23C((void *)param_1);
        func_8012B2CC(param_1);
        func_8012B14C(param_1, (s32)D_8019F444);
        *(s16 *)(param_1 + 2) = 1;
        *(s16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x90;
        *(s16 *)(param_1 + 6) =
            *(u16 *)(param_1 + 6) -
            (func_8004787C(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 8);
        *(s16 *)(param_1 + 0xE) =
            *(u16 *)(param_1 + 0xE) -
            (func_80047948(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 8);
    }
}



extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80182600(s32 a0)
{
    s32 v1;

    if ((((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) != 0) {
        *(s16*)(a0 + 0x2) = 2;
        *(s32*)(a0 + 0x1C) = 0x3C;
        *(s16*)(a0 + 0x98) = 1;

        v1 = *(s32*)(a0 + 0x20);
        *(u16*)(v1 + 0x2C) |= 0x10;

        *(s32*)(*(s32*)(a0 + 0x20) + 0x4) |= 0x8000000;

        *(s16*)(*(s32*)(a0 + 0x20) + 0x12) = 0;
        func_8002D4C8(0xCB4, 0);
    }
}



/* Decls conformed VERBATIM to the TU's own file-scope decl block
 * (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:5052-5060, the block that feeds the
 * banked sibling func_801850E4). Two of them disagreed with this draft:
 *   func_8012C1B8 -> TU says `void` return, draft wanted s32  (the reported conflict)
 *   func_8012B23C -> TU says `void *` param,  draft wanted s32 (hidden behind it)
 * Both disagreements are pushed to casts at the USE site (§37 lever A) — zero bytes
 * change; the same cast idiom is already used by func_801850E4 above. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 rand(void);
extern void func_8012B23C(void *a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_80182684(s32 a0)
{

    extern s32 D_8019F45C;
    extern s32 D_8019F51C;
    extern s32 D_8019F5A4;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)a0);
    } else {
        func_8001CA1C(v0, (s32)&D_8019F45C);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_8019F51C);
        v0 = rand();
        *(u32 *)(a0 + 0x94) = v0 & 0xF;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);

        func_8012B23C((void *)a0);
        func_8012B2CC(a0);
        func_8012B14C(a0, (s32)&D_8019F5A4);

        *(u16 *)(a0 + 0x2) = 1;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;

        *(s16 *)(a0 + 0xA) -= 0x90;

        v0 = func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s16 *)(a0 + 0x6) -= (s16)(v0 >> 8);

        v0 = func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s16 *)(a0 + 0xE) -= (s16)(v0 >> 8);
    }
}


extern void func_8012CBCC(s32 a0);
    void func_80182790(void *a0) {
        if ((((s32 (*)(s32))func_8012CBCC)((s32)a0) & 0x2000) != 0) {
            *(s16 *)((u8 *)a0 + 0x2) = 2;
        }
    }


extern void func_8012C218(void *a0);


void func_801827C8(void *a0) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) + 0x200;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) + -0x200;
    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) < 0x401) {
        func_8012C218(a0);
    }
}



extern void (*D_801BC61C[])(void);

void func_80182834(void *a0) {
    D_801BC61C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
extern u8 D_801BF2EC[];
extern void func_80182A50(void *a0);

void func_80182870(void *a0)
{
    u8 *p;
    s32 i;

    i = 4;
    if (*(s16 *)((s32)a0 + 0xDE) != 0) {
        func_80182A50((void *)a0);
        return;
    }

    p = D_801BF2EC;
    do {
        *p = 0;
        p--;
        i--;
    } while (i >= 0);

    *(s32 *)((s32)a0 + 0x1C) = (rand() & 0x7F) + 0x40;
    func_8012AD50((void *)a0);
}


extern s32 rand(void);
extern void func_80182998(s32 a0, s32 a1);
extern u16 D_801BC62C;
extern u16 D_801BC62E;
extern u16 D_801BC630;

void func_801828E8(s32 a0) {
    u16 *p;
    u16 w;
    s32 r;
    s32 t;

    if (func_8012BEE8(a0)) {
        r = rand();
        p = &D_801BC62C;
        w = *(u16 *)(a0 + 0xFC);
        t = (s16)w / 2 - (r & (w - 1));
        p[0] = *(u16 *)(a0 + 6) + t * 2;
        D_801BC62E = *(u16 *)(a0 + 0xA);
        D_801BC630 = *(u16 *)(a0 + 0xE) + t * 2;
        func_80182998(a0, (s32)p);
        *(s32 *)(a0 + 0x1C) = (rand() & 0x7F) + 0x40;
    }
}




extern s32 func_8012E778(int param_1, int param_2);
extern s32 func_8012C51C(int a0, int a1);

void func_80182998(int param_1, int param_2)
{

    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern u8 D_801BF2E8[];
    s32 i;

    i = 0;
    if (func_8012E778(param_1, ((s32)(D_800AF7BE >> 1) << 16) | (D_800AF7BC >> 1)) != 0) {
        do {
            if (D_801BF2E8[i] == 0) {
                D_801BF2E8[i] = 1;
                *(s32 *)(param_2 + 0x10) = i | 0x80000000;
                *(u16 *)(param_2 + 8) = *(u16 *)(param_1 + 0x70);
                func_8012C51C(param_2, param_1);
                return;
            }
            i++;
        } while (i < 5);
    }
}



extern s32 func_8012C194(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80182DDC(s32 a0);

void func_80182A50(void *a0)
{

    extern u32 D_801BF1A8;
    s32 iVar2;
    u32 *puVar3;

    *(s16 *)((s32)a0 + 0xFC) = 0x7000;
    *(s16 *)((s32)a0 + 0x100) = 0;
    *(s16 *)((s32)a0 + 0xFE) = 0;
    *(s16 *)((s32)a0 + 0x104) = 0;
    *(s16 *)((s32)a0 + 0x106) = 0;
    puVar3 = (u32 *)((u8 *)&D_801BF1A8 + (*(s16 *)((s32)a0 + 0xDC) * 0x40));
    iVar2 = func_8012C194();
    *(s32 *)((s32)a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001CD50(iVar2, (s32)puVar3);
        *(s16 *)(iVar2 + 0x10) = 0x400;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x60000000;
        func_800233CC(puVar3, 0x40);
        puVar3[0] = 0x808080;
        puVar3[1] = 0x808080;
        func_80182DDC((s32)a0);
        *(s16 *)((s32)a0 + 2) = 3;
    }
}



/* func_80182B10 — per-frame entity tick: decay the sound-handle envelope at
 * +0x20, ramp the s16 pair at +0xFE/+0x106 up to a 0x6000 ceiling, then ramp
 * the pair at +0xFC/+0x104 down; when the +0xFC accumulator goes negative the
 * entity releases its D_801BF2E8 slot and hands off to func_8012C218,
 * otherwise it continues in func_80182BDC.
 *
 * §71 sibling-first: func_8018A090 (same TU, 0xC0 bytes earlier) is the
 * initialiser for exactly these fields (+0xFC/+0xFE/+0x100/+0x104/+0x106, the
 * +0x20 handle and the +0xDC slot index) and pins the widths/casts used here.
 * D_801BF2E8[] is the 5-entry slot table func_80189FD8 (same TU) claims from.
 *
 * Levers (all three were needed; each is byte-verified by removal):
 *  1. §3-T4 branch polarity — the 0x6000 guard is written `>= 0x6000` with the
 *     CLAMP as the then-arm, which is what puts `slti/bnez` + the `j` over the
 *     ramp arm in the target order. Writing it `< 0x6000` gives `beqz` and the
 *     arms swapped.
 *  2. Zero-byte `__asm__ __volatile__("" : : : "memory")` at the head of the
 *     ramp arm (§34 toolkit). Without it cse.c relates the guard's
 *     `lh 0xFE` to the ramp's `lhu 0xFE` — same MEM, sign- vs zero-extend —
 *     and rewrites the second as `move`+`andi 0xffff`. That also lands both
 *     arms' final store in $v0, which lets the post-reload jump pass CROSS-JUMP
 *     the two `sh 0xFE` tails (§5a) and eats the `j .L8018A1C4`. The clobber
 *     invalidates the MEM in the hash table so the real second load survives,
 *     the arms end in different registers, and the cross-jump cannot fire.
 *  3. The +0x104 store is SUNK to immediately after the subtract, before the
 *     +0xFC accumulate. Both tail quantities are otherwise born in the same
 *     block, and local-alloc's QTY_CMP_PRI (n_refs*log2(n_refs)/live_length)
 *     then ranks the accumulator ABOVE the delta, handing it $v0 and swapping
 *     the whole block's register pair. Storing the delta early kills its live
 *     range at insn 3, which flips the priority back so the delta takes $v0.
 *     Purely a scheduling/priority dial — the emitted order is unchanged
 *     because reorg pulls `sh 0x104` back into the `bgez` delay slot.
 * Also note the two tail blocks are BLOCK-SCOPED: sharing one function-scope
 * pair across the 0xFE and 0xFC ramps makes them global allocnos (§76), which
 * costs $a1 for the deltas and an extra 8 bytes of frame (0x20 vs 0x18).
 */

extern void func_8012C218(void *a0);
extern void func_80182BDC(void *a0);

void func_80182B10(void *a0)
{

    extern u8 D_801BF2E8[];
    s32 p;
    s32 v;

    p = *(s32 *)((s32)a0 + 0x20);
    if (p != 0) {
        v = *(u16 *)(p + 0x1A) - 0x100;
        *(s16 *)(p + 0x1A) = v;
        *(s16 *)(p + 0x18) = v;
        if (*(s16 *)(p + 0x1A) < 0) {
            *(s16 *)(p + 0x1A) = 0;
            *(s16 *)(p + 0x18) = 0;
        }
    }
    if (*(s16 *)((s32)a0 + 0xFE) >= 0x6000) {
        *(s16 *)((s32)a0 + 0xFE) = 0x6000;
    } else {
        s32 dv, sv;
        dv = *(u16 *)((s32)a0 + 0x106) + 0x400;
        *(s16 *)((s32)a0 + 0x106) = dv;
        *(s16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + dv);
    }
    {
        s32 d = *(u16 *)((s32)a0 + 0x104) - 0x80;
        s16 s;

        *(s16 *)((s32)a0 + 0x104) = d;
        s = *(u16 *)((s32)a0 + 0xFC) + d;
        *(s16 *)((s32)a0 + 0xFC) = s;
        if (s < 0) {
            D_801BF2E8[*(s16 *)((s32)a0 + 0xDC)] = 0;
            func_8012C218(a0);
        } else {
            func_80182BDC(a0);
        }
    }
}




void func_80182BDC(void *a0) {
    extern s32 func_80017DC4(void *a0, void *a1);
    extern s16 func_8012A758(void);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_80017E68(void *a0, void *a1);
    extern s32 func_80017758(void *a0, void *a1);
    extern Blk8_80182BDC D_801BC640, D_801BC648, D_801BC650, D_801BC658;
    extern Blk8_80182BDC D_801BC660, D_801BC668, D_801BC670, D_801BC678;

    u8 buf[0x60];
    u8 *p;
    u8 *q;
    u8 *vp;
    s16 ang;

    *(s32 *)(buf + 0x30) = 0x50000000;
    *(s32 *)(buf + 0x20) = 0x80;
    *(s32 *)(buf + 0x24) = 0x80;
    *(s32 *)(buf + 0x28) = 0;
    *(s32 *)(buf + 0x2c) = 0;

    *(Blk8_80182BDC *)(buf + 0x00) = D_801BC640;
    *(Blk8_80182BDC *)(buf + 0x08) = D_801BC648;
    *(Blk8_80182BDC *)(buf + 0x10) = D_801BC650;
    *(Blk8_80182BDC *)(buf + 0x18) = D_801BC658;

    p = buf + 0x38;
    func_80017DC4((u8 *)a0 + 0xfc, p);
    ang = func_8012A758();
    RotMatrixY(ang, p);

    q = buf + 0x58;
    func_80015978((s32)((u8 *)a0 + 4), (s32 *)q);
    func_80017E68(q, p);

    vp = buf + 0x00;
    func_80017758(vp, p);

    *(s32 *)(buf + 0x30) = 0x60000000;
    *(s32 *)(buf + 0x20) = 0x808080;
    *(s32 *)(buf + 0x24) = 0x808080;

    *(Blk8_80182BDC *)(buf + 0x00) = D_801BC660;
    *(Blk8_80182BDC *)(buf + 0x08) = D_801BC668;
    *(Blk8_80182BDC *)(buf + 0x10) = D_801BC670;
    *(Blk8_80182BDC *)(buf + 0x18) = D_801BC678;

    func_80017758(vp, p);
}


extern s32 func_80182E64(s32 a0);

void func_80182DDC(s32 a0)
{
    s32 t;
    s32 id;

    switch (*(s16 *)(a0 + 0x70)) {
    case 0:
        func_8002D4C8(0x6D5, 0);
        return;
    case 1:
        t = func_80182E64(a0);
        id = 0x856;
        break;
    case 2:
        t = func_80182E64(a0);
        id = 0x857;
        break;
    default:
        return;
    }

    t |= 0x2000;
    func_8002D4C8(id, t & 0xFFFF);
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012EFB8(s32 a0);

s32 func_80182E64(a0)
s32 a0;
{
    extern void func_8012EFB8(s32 a0);
    s32 sp10;
    s32 v1;

    func_80015978(a0 + 4, &sp10);
    if ((((s32 (*)(s32, s32))func_8012EFB8)((s32)&sp10, (s32)&sp10) & 0xFFFFEFFF) != 0) {
        v1 = 1;
    } else {
        v1 = (*(s16 *)&sp10 * 64) / 160 + 0x40;
    }
    if (v1 <= 0) {
        v1 = 1;
    } else if (v1 >= 0x80) {
        v1 = 0x7F;
    }
    return v1;
}



extern void (*D_801BC760[])(void);

void func_80182EE8(void *a0) {
    D_801BC760[*(u16 *)((s32)a0 + 0x2)]();
}
