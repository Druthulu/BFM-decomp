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
extern u8 D_80184978;
extern u8 D_801848E8;
extern u8 D_801848C4;
extern u8 D_801848A0;
extern u8 D_80184954;
extern u8 D_80184930;
extern u8 D_8018490C;
extern u8 D_8018487C;
extern void func_80145934(void);
extern u8 D_80184A08;
extern u8 D_801849E4;
extern u8 D_801849C0;
extern u8 D_8018499C;
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
extern unsigned char D_80183E00[];
extern unsigned char D_80183E30[];
extern unsigned char D_80183E80[];
extern unsigned char D_80183EB0[];
extern unsigned char D_80183EE0[];
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
extern void (*D_80183F30[])(void *);
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
extern s32 D_80183FF8[];
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
extern u8 D_80184080[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80184088;
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
/* canonical TU type (engine_core) — read via *(u16*) cast */
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
extern int D_801B0A90;
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
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801B0A94;
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
extern s32 D_801840B8;
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
extern void (*D_80184160[])(void);
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
extern void (*D_80184184[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80184174;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80184198[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801841A4[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801841B4[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801841CC[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801841BC;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801841E0[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801841FC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801841EC;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80184210[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80184224[])(void);
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
extern s32 D_80184238;
extern void (*D_80184260[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80184240;
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
extern int (*D_801842AC[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801842B0[])(void);
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
extern unsigned short D_80184714[];
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
extern void (*D_80184724[])(void);
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
extern int D_801B0AC8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018474C[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018472C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018473C;
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
extern void (*D_8018478C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80184794[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80184760;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801847A0[])(void);
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
extern u8 D_80184770;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B0AD0;
extern s32 D_801B0ADC;
extern s32 D_801B0AE0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801847DC[])(s32 *);
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
extern s32 D_801847B0[];
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
extern s32 D_801B0AD8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80184A2C[])(void);
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
extern u32 D_800AFAE8[];
extern char D_8018484C[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80184AD0[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80184C24[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80184A40;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80184C2C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80184A50;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80184A70;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80184C34[])(void);
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
extern void (*D_80184C5C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80184C68[])(void);
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
extern void (*D_80184ADC[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80184D0C;
extern void func_8015D380(s32 a0);
extern unsigned char D_80183DF0[];
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
extern unsigned char D_80184D20[];
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
extern s8 D_80184D5C[];
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
extern u16 D_80184DA4;
extern u16 D_80184DA6;
extern u16 D_80184DA8;
extern s32 D_80184DAC;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80184DB4;
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
extern int D_80184AC0;
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
extern unsigned int D_80184E38[];
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
extern void (*D_80184EE8[])(void);
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
extern u16 D_80184F18[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80184F7C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B0AE8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80184FA0[])(void);
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
extern int D_801B0B40[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80184FE8[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80184FD8;
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
extern char D_801B03A0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80184FF0[])(void);
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
extern void (*D_80185044[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018500C;
extern s16 D_80185040;
extern s16 D_8018503E;
extern s16 D_8018503C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80185050[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B0BA0;
extern u8 D_801B0BA1;
extern u8 D_801B0BA2;
extern u8 D_801B0BA3;
extern u8 D_801B0BA4;
extern u8 D_801B0BA5;
extern u8 D_801B0BA6;
extern u8 D_801B0BA7;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80185060[])(void);
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
extern s32 D_801B0BE0;
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
extern void (*D_801850A4[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80185120[];
extern s32 D_80185140[];
extern u8 D_801851BC[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801851DC[];
extern u8 D_801851FC[];
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
extern void (*D_80185298[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80185314[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B03B0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80185320[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80185328[])(void);
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
extern void (*D_801853F0[])(void);
extern void func_80166618(void *a0);
extern void (*D_80185400[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80185410[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018541C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018537C[];
extern u8   D_80185390[];
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
extern void (*D_80185434[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018543C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80185444[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018544C[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80185454[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018545C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80185464[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80185518[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80185520[])(void);
extern void func_80169F00(void *a0);
extern char D_801854D0[];
extern char D_80185490[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80185558[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80185564[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801855AC[])(void);
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
extern void (*D_80185628[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B0F00;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018561C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80185660[];
extern unsigned short D_80185668[];
extern unsigned short D_80185670[];
extern unsigned char D_801B0F08[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B0F00;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80185678[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B103C;
extern M2C_UNK D_801B1040;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B0FC8;
extern void (*D_801856A8[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B1044[];
extern u8 D_801B104C[];
extern u8 D_801B0FFC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801856B0[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801856CC[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801856D4[])(void);
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
extern void (*D_8018573C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801856E0;
extern u8 D_801856EC;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80185770[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80185778[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801857CC[])(void);
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
extern u16 D_80185800[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801857F0[];
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
extern s32 D_8018581C;
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
extern void (*D_80185894[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018589C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801858A4[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801858AC[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801858B4[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801858BC[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801858C8[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801858D4[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801858E0[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801858F0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80185900[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80185908[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80185910[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80185918[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80185920[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80185928[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80185930[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80185938[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80185940[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80185948[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80185950[])(void);
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
extern void (*D_80185958[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80185960[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80185968[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80185970[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80185978[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80185980[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80185988[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80185990[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80185998[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801859A0[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801859A8[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801859B0[])(void);
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
extern void (*D_801859F4[])(void);
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
extern M2C_UNK D_801859B8;
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
extern void (*D_80185A24[])(void);
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
extern void (*D_80185A60[])(void);
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
extern void (*D_80185AB8[])();
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
extern void (*D_80185AC8[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80185AD0[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80185C38[])();
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
extern void (*D_80185C44[])();
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
extern M2C_UNK D_801B05F8;
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
extern s16 D_801B1FB8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B1780;
extern short D_801B202C;
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
extern s32 D_801B1BAC;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B1BD4;
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
extern s16 D_801B1B90;
extern s32 func_8017A3B0(void);
extern short D_801B1BCC;
extern short D_801B1BC8;
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
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801B1B94;
extern u16 D_801B1C14;
extern u16 D_801B1C16;
extern u16 D_801B1C18;
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
extern s16 D_801B1C0C;
extern s16 D_801B1C0E;
extern s16 D_801B1C10;
extern s16 D_801B1C04;
extern s16 D_801B1C06;
extern s16 D_801B1C08;
extern void func_8017B7A8(void);
extern s16 D_801B1C24;
extern s16 D_801B1C26;
extern s16 D_801B1C28;
extern s16 D_801B1C2C;
extern s16 D_801B1C2E;
extern s16 D_801B1C30;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B1C1C;
extern short D_801B1C1E;
extern short D_801B1C20;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B1BB4;
extern SV4 D_801B1BBC;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B1BDC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B1BD8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80185E20[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80185E58[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_80185E6C[])(void);
extern void func_8017C524(void *a0);
extern void (*D_80185E80[])(void);
extern void func_8017C7C4(void *a0);
extern void (*D_80185F98[])(void);
extern void func_8017D47C(void *a0);
extern void func_8012C218(void *a0);
extern void func_8017D824(void *param_1);
/* ==== end §8b carried decl layer ==== */

/* func_8017D898 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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






#include "../shared/ov/func_8017D898__t67f11bf2.h"



extern void (*D_80186014[])(void);

void func_8017E778(void *a0) {
    D_80186014[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E9A8(void);
extern void func_800167B8(s32 a0);

#include "../shared/ov/func_8017E7B4__db514c4d.h"



#include "../shared/ov/func_8017E7F8__511a8b68.h"




extern void func_8017E9D0(void);

#include "../shared/ov/func_8017E81C__1834ba2f.h"



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E85C(u8 *a0) {
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
void func_8017E8D8(void) {
    func_800D1EBC();
}



extern void (*D_80186028[])(void);

void func_8017E8F8(void *a0) {
    D_80186028[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017E934(s32 a0) {
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
void func_8017E9A8(void) {

    extern s32 D_80186034(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80186034, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E9D0(void) {

    extern s32 D_80186040(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80186040, 0x1000000);
}




void func_8017E9F8(void) {

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
    extern u16 D_801269E8;
    extern s16 D_801B1EB8;
    extern void func_8017EAB0(void *);
    extern void func_8012A018(s32, s32);
    extern void func_8012A094(s32);

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x3E8;
    D_80126968 = 0x155;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x50;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EAB0, 0);
    func_8012A094((s32)D_80126948);
    func_8017EAB0((void *)D_80126948);
    func_8012A094((s32)D_80126948);
    D_801B1EB8 = D_801269E8;
}



extern void (*D_80186054[])(void);

void func_8017EAB0(void *a0) {
    D_80186054[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

/* func_8017EAEC — ov_SC05_005 / ov_SC05_005_jr_8017D898   (107 ins, MATCH)
 *
 * Per-frame camera driver for this scene: every 4th tick (func_80148800 & 3)
 * it flips the 1-bit phase at +5 and reloads the +0x14 field from the 2-entry
 * table D_801860AC, then copies the 8-byte camera aggregate D_80126940 onto the
 * stack, clamps it, offsets a second copy by sin/cos of the player angle, asks
 * func_8017EE64 for a yaw and hands both to func_8017EC98.
 *
 * Levers:
 *   §48-C2 — D_80126940 is an 8-byte, 2-BYTE-ALIGNED aggregate, so the plain
 *     struct assign `sp10 = D_80126940;` is what emits the lwl/lwr + swl/swr
 *     block copy (same typedef shape the rest of this family uses).
 *   base+offset — `lw $v0, 0x20($s1)` reads D_80126B78 through the SAME $s1 that
 *     holds &D_80126B58 for the func_80148800 call, so it must be spelled off
 *     that base (`base[8]`), never as its own %hi(D_80126B78) fold.
 *   /128 — `bgez / addiu 0x7F / sra 7` is a signed divide by 128, not `>> 7`.
 *   §286 — THE ONLY RESIDUAL (closeness 4). Written as a plain statement,
 *     `*(s16 *)(a0 + 0xA0) = r;` is emitted BEFORE the argument setup, so the
 *     `li $a3,1` wins the jal's delay slot and the sh lands 4 insns early.
 *     Folding the store into a comma-expression in an ARGUMENT position places
 *     its RTL after the last arg move, and the sh takes the delay slot: 4 -> 0.
 */

/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */
typedef struct { s16 v[4]; } Blk8_80126940_8017D6D0_8017EAEC;

extern u16  func_80148800(s32 *a0);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern s32  func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  func_8017EE64(u8 *param_1, s16 *param_2, s16 *param_3);
extern void func_8017EC98(s32 param_1, s32 param_2, s16 *param_3);
extern s32  D_80126B58;

void func_8017EAEC(s32 a0) {

    extern s16 D_801860AC[];
    extern u8  D_80186058[];
    extern s16 D_801B1EB8;
    extern Blk8_80126940_8017D6D0_8017EAEC D_80126940;

    Blk8_80126940_8017D6D0_8017EAEC sp10;
    Blk8_80126940_8017D6D0_8017EAEC sp18;
    s32 *base;
    u8 t;
    s32 r;

    base = &D_80126B58;
    if (func_80148800(base) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_801860AC[t];
    }
    sp10 = D_80126940;
    if (sp10.v[0] < -0x1440) {
        sp10.v[0] = -0x1440;
    }
    if (sp10.v[1] > -0x200) {
        sp10.v[1] = -0x200;
    }
    if (sp10.v[0] > 0x1100) {
        if (sp10.v[2] > -0x80) {
            sp10.v[2] = -0x80;
        }
    }
    sp18.v[0] = sp10.v[0] - func_8004787C(((s16 *)base[8])[9]) / 128;
    sp18.v[2] = sp10.v[2] - func_80047948(((s16 *)base[8])[9]) / 128;
    sp18.v[1] = sp10.v[1];
    r = func_8017EE64(D_80186058, sp10.v, sp18.v);
    /* §286: the store must ride the jal's delay slot -- see header. */
    D_801B1EB8 = func_80012DBC(D_801B1EB8, (s16)r, 4, (*(s16 *)(a0 + 0xA0) = r, 1));
    func_8017EC98(a0, D_801B1EB8, sp10.v);
}



extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017F448(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_8017EC98(s32 param_1, s32 param_2, s16 *param_3) {
    s32 m1[8];
    u16 svec_in[4];
    u16 svec_out[4];
    u16 rot[4];

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_3[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_3[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_3[2];

    rot[0] = *(u16 *)(param_1 + 0x18);
    rot[1] = *(u16 *)(param_1 + 0x1A) + param_2;
    rot[2] = *(u16 *)(param_1 + 0x1C);
    func_8017F448(rot, m1);

    svec_in[0] = 0;
    svec_in[1] = 0;
    svec_in[2] = *(s32 *)(param_1 + 0x10);
    ApplyMatrixSV(m1, svec_in, svec_out);

    *(s32 *)(param_1 + 0x3C) = ((s32)(s16)svec_out[0] >> 3) + *(s16 *)(param_1 + 0x28) + param_3[0];
    *(s32 *)(param_1 + 0x40) = ((s32)(s16)svec_out[1] >> 3) + *(s16 *)(param_1 + 0x2A) + param_3[1];
    *(s32 *)(param_1 + 0x44) = ((s32)(s16)svec_out[2] >> 3) + *(s16 *)(param_1 + 0x2C) + param_3[2];
}


extern u32 func_8017EFF4(s16 *param_1, s16 *param_2, s16 *param_3);
extern u32 func_8017F0AC(s16 *param_1, s16 *param_2, s16 *param_3);
extern u32 func_8017F164(s16 *param_1, s16 *param_2, s16 *param_3);
extern s32 ratan2(s32 a0, s32 a1);

s32 func_8017EE64(u8 *param_1, s16 *param_2, s16 *param_3) {
    u32 a3;

    while (1) {
        switch (param_1[0]) {
            case 0:
                a3 = func_8017EFF4((s16 *)(param_1 + 2), (s16 *)(param_1 + 6), param_2);
                break;
            case 1:
                a3 = func_8017F0AC((s16 *)(param_1 + 2), (s16 *)(param_1 + 6), param_2);
                break;
            case 2:
                a3 = func_8017F164((s16 *)(param_1 + 2), (s16 *)(param_1 + 6), param_2);
                break;
            case 0xFF:
                a3 = 0;
                break;
        }
        if (a3 != 0) {
            param_1 += 0xE;
            continue;
        }
        switch (param_1[1]) {
            case 0:
                return ratan2(param_3[0] - *(s16 *)(param_1 + 0xA), param_3[2] - *(s16 *)(param_1 + 0xC)) & 0xFFF;
            case 1:
                return ratan2(*(s16 *)(param_1 + 0xA) - param_3[0], *(s16 *)(param_1 + 0xC) - param_3[2]) & 0xFFF;
            case 2:
                a3 = 0x800;
                return a3;
            case 3:
                a3 = 0x400;
                return a3;
            case 4:
                a3 = 0xB00;
                return a3;
            case 5:
                a3 = 0x480;
                return a3;
        }
        param_1 += 0xE;
    }
}



/* func_8017EFF4 — ov_SC02_039 / ov_SC02_039_jr_8017BEBC   (46 ins, MATCH)
 *
 * 2D bounding-box reject on the segment (param_1 -> param_2) against the query
 * point param_3 (x at [0], y at [2]), then a GTE cross-product sign test:
 * func_800495EC is the handwritten `mtc2 SXY0/SXY1/SXY2` NCLIP wrapper at
 * 0x800495EC, so each argument is a packed (u16)x | (y << 16) screen point.
 * Returns 1 when the point is on the "reject" side of a bbox edge, 0 when it is
 * outside the span, else the sign of the NCLIP result (~r >> 31 == r >= 0).
 *
 * LOAD-BEARING CONSTRUCTS — do not "clean up" without re-running match_one:
 *  - s16 locals assigned from the s16 loads: store_expr into a PROMOTE_MODE
 *    pseudo emits `lh <temp>` + `addu <var>,<temp>,$zero`; the compares use the
 *    temp, the packing uses the copy. That copy pair is 6 of the 46 insns.
 *  - `(u16)ay << 16` (not `(s32)ay << 16`): the unsigned conversion of a signed
 *    promoted short forces the widening copy for the y terms too; the signed
 *    form lets combine fold it into the sll and loses 3 insns.
 *  - `do { ... } while (0)` around the tail: the loop note bumps loop_depth, so
 *    flow.c's `reg_n_refs += loop_depth` reweights the K2 density priorities.
 *    A bare `{ ... }` block instead permutes $t1..$t4 (11 mismatches).
 *  - the two zero-byte `__asm__` re-ties (cookbook §30 / gcc-2.7.2-map regalloc):
 *    the first makes the pinned $t0/$a3/$v1 conflict with the cx load temp
 *    (pushing it to $t1); the second keeps the ax/bx/cx copies live past their
 *    own `andi` so the mask does not reuse the dying source register.
 *    They emit no instructions; they only move the allocation.
 *  - the $8/$7/$3 pins on la/lb/lc (cookbook §17): local-alloc otherwise hands
 *    the three masks $v0/$v1/$a3 and the whole global assignment shifts down.
 *  - `s32 pad[2]`: dead locals for the target's 0x50 frame (vars=56).
 */

extern s32 func_800495EC(s32 a0, s32 a1, s32 a2);

u32 func_8017EFF4(s16 *param_1, s16 *param_2, s16 *param_3) {
    s16 ax, ay, bx, by, cx, cy;
    register s32 la __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 lb __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 lc __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u32 r;
    s32 pad[2];

    ax = param_1[0];
    cx = param_3[0];
    if (cx < ax) {
        return 0;
    }
    __asm__ __volatile__("" : : "r"(la), "r"(lb), "r"(lc));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
    bx = param_2[0];
    if (bx < cx) {
        return 1;
    }
    by = param_2[1];
    do {
        cy = param_3[2];
        if (cy < by) {
            return 0;
        }
        ay = param_1[1];
        if (ay >= cy) {
            la = (u16)ax;
            lb = (u16)bx;
            lc = (u16)cx;
            __asm__ __volatile__("" : : "r"(ax), "r"(bx), "r"(cx));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
            r = func_800495EC(la | ((u16)ay << 16), lb | ((u16)by << 16),
                              lc | ((u16)cy << 16));
            return ~r >> 31;
        }
        return 1;
    } while (0);
}


extern s32 func_800495EC(s32 a0, s32 a1, s32 a2);

u32 func_8017F0AC(s16 *param_1, s16 *param_2, s16 *param_3) {
    s16 ax, ay, bx, by, cx, cy;
    register s32 la __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 lb __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 lc __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u32 r;
    s32 pad[2];

    cx = param_3[0];
    bx = param_2[0];
    if (cx < bx) {
        return 0;
    }
    __asm__ __volatile__("" : : "r"(la), "r"(lb), "r"(lc));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
    ax = param_1[0];
    if (ax < cx) {
        return 1;
    }
    do {
        cy = param_3[2];
        ay = param_1[1];
        if (cy > ay) {
            return 0;
        }
        by = param_2[1];
        if (cy >= by) {
            la = (u16)ax;
            lb = (u16)bx;
            lc = (u16)cx;
            __asm__ __volatile__("" : : "r"(ax), "r"(bx), "r"(cx));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
            r = func_800495EC(la | ((u16)ay << 16), lb | ((u16)by << 16),
                              lc | ((u16)cy << 16));
            return ~r >> 31;
        }
        return 1;
    } while (0);
}




u32 func_8017F164(param_1, param_2, param_3)
s16 *param_1;
s16 *param_2;
s16 *param_3;
{
    if ((*param_3 < *param_1) || (*param_2 < *param_3) ||
        (param_3[2] < param_1[1])) {
        return 1;
    }
    return param_2[1] < param_3[2];
}



extern void (*D_801860C0[])(void);

void func_8017F1BC(void *a0) {
    D_801860C0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_801860B0;

void func_8017F1F8(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_801860B0 | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


void func_8017F274(void) {
}


s32 func_8017F27C(void) {
    return 95;
}



/* func_8017F284 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_8017F2E8((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8017F2E8();

void func_8017F284(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_8017F2E8)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}



void func_8017F2E8(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_8017F6E8(s0);
    sin_val = func_8017F62C(s0);

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



void aF8017F448(u16 *r, s16 *m) __asm__("func_8017F448");
void aF8017F448(u16 *r, s16 *m)
{
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_8017F6E8(r[0] & 0xFFF);
    sx = func_8017F62C(r[0] & 0xFFF);
    cy = func_8017F6E8(r[1] & 0xFFF);
    sy = func_8017F62C(r[1] & 0xFFF);
    cz = func_8017F6E8(r[2] & 0xFFF);
    sz = func_8017F62C(r[2] & 0xFFF);

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



/* func_8017F62C — quadrant-folded sine lookup over a 0x400-entry u16 table.
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
 * Q2's base is D_801A4838 == D_801A5838 - 0x1000: gcc folded the `- 0x800`
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


s16 func_8017F62C(u32 a0)
{

    extern u16 D_801A5838[];
    if (a0 < 0x400) {
        return D_801A5838[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801A5838[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801A5838[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801A5838[0xFFF - a0];
    }
}



/* func_8017F6E8 — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801A5838); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801A5838)[a - 0x400]  ->  base ((s16 *)D_801A5838)-0x800 = D_801A5038, index a*2
 *   ((s16 *)D_801A5838)[a - 0xC00]  ->  base ((s16 *)D_801A5838)-0x1800 = D_801A4038, index a*2
 * so no extra externs are needed for D_801A5038 / D_801A4038.
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


s32 func_8017F6E8(u32 a0v)
{

    extern u16 D_801A5838[];
    if (a0v < 0x400) {
        return ((s16 *)D_801A5838)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801A5838)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801A5838)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801A5838)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}


void func_8017F794(void *a0) {
    extern void (*D_801A6190[])(void);
    extern s32 D_801AB144;
    extern void func_8018093C(void *a0);
    extern s32 func_8012C0EC(s32 a0);
    s32 temp;

    D_801A6190[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        if (*(s32 *)((s32)a0 + 0x90) == (s32)&D_801AB144) {
            temp = *(s32 *)((s32)a0 + 0x94);
            if (temp == 10) {
                func_80181DE4((s32)a0, 0x7F9);
            } else if (temp == 15) {
                func_80181DE4((s32)a0, 0x7F8);
            }
        }
        func_8018093C(a0);
        func_8012C0EC((s32)a0);
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C97C(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8017F840(void *a0) {

    extern u8 D_801A6068[];
    extern u8 D_801A6140[];
    extern s32 D_801A60D8[];

    s16 flag;

    if (func_8012C354((s32)a0, (s32)(D_801A6068 + (*(u16 *)((s32)a0 + 0x70) & 0xF) * 0x34)) == 0) {
        return;
    }

    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xBC) = (s32)D_801A6140;
    *(s32 *)((s32)a0 + 0xB4) = 0xFFFF5FFF;
    *(s32 *)((s32)a0 + 0xC4) |= 3;

    func_8001C97C(D_801A60D8[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    if ((*(u16 *)((s32)a0 + 0x70) & 1) != 0) {
        *(s16 *)((s32)a0 + 0xAE) = -0x81;
        *(u8 *)((s32)a0 + 0x75) = 2;
        flag = *(s16 *)((s32)a0 + 0x70);

        if ((flag & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 6;
            *(s16 *)((s32)a0 + 0x76) = 1;
            return;
        }
        if ((flag & 0x4000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 8;
            *(s16 *)((s32)a0 + 0x76) = 1;
            return;
        }
        if ((flag & 0x2000) != 0) {
            *(s16 *)((s32)a0 + 0x2) = 0xA;
            *(s16 *)((s32)a0 + 0x76) = 1;
        } else {
            *(s16 *)((s32)a0 + 0x2) = 3;
            func_8012B030((u8 *)a0);
        }
    } else {
        *(s16 *)((s32)a0 + 0xAE) = 0xC;
        *(s16 *)((s32)a0 + 0x2) = 1;
    }

    func_80143994((s32)a0, 0x4000);
}



extern void func_8012A828(s32 arg0, s32 arg1);

void func_8017F988(void *arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801AB1CC;
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801AB1CC);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
}


extern s16 D_80126CB4;
extern s32 func_8012BE98(s32 a0, u16 *a1);

void func_8017F9C0(void *param_1) {
    if ((*(u16 *)((s32)param_1 + 0x70) & 1) != 0) {
        return;
    }
    if (func_8012BE98((s32)param_1, (u16 *)&D_80126CB4) > 0x240000) {
        return;
    }
    *(s16 *)((s32)param_1 + 2) = 0xC;
}


extern s32 rand(void);
extern void func_8012B23C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_801AB144;

void func_8017FA1C(s32 param_1) {
    s32 r;

    r = rand();
    *(s32 *)(param_1 + 0xE0) = r % 4096;
    *(s16 *)(param_1 + 2) = 4;
    r = rand();
    *(s32 *)(param_1 + 0x1C) = r % 32 + 0x40;
    *(s32 *)(param_1 + 0xE4) &= ~1;
    func_8012B23C(param_1);
    func_8012A828(param_1, (s32)&D_801AB144);
}



/* callee spellings adopted from the ov_SC05_003 sibling TUs / src/shared canon (law 2) */
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);            /* canonical void; $v0 used -> cast at use site */
extern void func_8012ADE4(u8 *a0);
extern void func_80180F60();            /* same-TU INCLUDE_ASM neighbour */
extern s32  func_8012B8E4(s32 arg0, s32 arg1);
extern s32  func_8012BEE8(s32 a0);
extern s32  rand(void);

void func_8017FABC(s32 param_1) {
    extern u16 D_800B99DA;
    extern s32 D_801A60D8[];
    s32 p = param_1;
    s32 t;
    s32 n;
    s32 off;
    s32 base;
    s32 nv;

    /* 0x20 -> sub-object, +0x12 = u16 angle/timer */
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) +=
        func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE0), 0xA);
    func_8012B178(p, 0xFFF80000);

    if ((((s32 (*)(s32))func_8012CBA4)(p) & 0xFF00) != 0x2000) {
        func_8012ADE4((u8 *)p);
        n = *(s32 *)(p + 0xE8) + 1;
        *(s32 *)(p + 0xE8) = n;
        if (n >= 0x80) {
            func_80180F60(p);
        } else {
            *(s32 *)(p + 0xE4) |= 1;
        }
    } else {
        *(s32 *)(p + 0xE8) = 0;
        *(s32 *)(p + 0xE4) &= ~1;
    }

    t = *(s32 *)(p + 0xE4);
    if (t & 2) {
        *(s16 *)(p + 2) = 5;
        *(s32 *)(*(s32 *)(p + 0x20) + 0x24) = D_801A60D8[*(u16 *)(p + 0x70) & 0xF];
        *(s32 *)(p + 0xE4) &= ~2;
    } else if ((t & 1) == 0) {
        if ((D_800B99DA & 0x3F) == 0) {
            *(s32 *)(p + 0xE0) += func_8012B8E4(p, 8);
        }
        if (func_8012BEE8(p) == 1) {
            off = rand() % 1024;
            base = *(s32 *)(p + 0xE0);
            if ((rand() & 1) != 0) {
                nv = base + off;
            } else {
                nv = base - off;
            }
            *(s32 *)(p + 0xE0) = nv;
            *(s32 *)(p + 0x1C) = rand() % 32 + 0x40;
        }
    } else {
        *(s32 *)(p + 0xE0) += 0x21;
    }
}


extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012ADE4(u8 *a0);

void func_8017FCA4(s32 param_1) {
    extern s32 D_801A60D0[];

    if (func_8012BDBC(param_1, 0x400) == 0) {
        *(s16 *)(param_1 + 2) = 4;
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x24) = D_801A60D0[*(u16 *)(param_1 + 0x70) & 0xF];
    }
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + func_8012B8E4(param_1, 8);
    func_8012B178(param_1, 0xFFF80000);
    if (((s32 (*)(s32))func_8012CBA4)(param_1) != 0x2000) {
        func_8012ADE4((u8 *)param_1);
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80134510(s32 a0);
extern void func_80180E78(s32 a0, s32 a1);
extern u8 D_801152A8[];
extern s16 D_801152AA;
extern s16 D_801152AC;
extern s32 D_801AB144;

void func_8017FD44(s32 a0) {
    s16 sp10[3];
    s32 v1;

    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x12) = *(u16 *)(a0 + 0xFC);
    func_8012A828(a0, (s32)&D_801AB144);
    sp10[0] = *(u16 *)(a0 + 6);
    sp10[1] = *(u16 *)(a0 + 0xA);
    sp10[2] = *(u16 *)(a0 + 0xE);
    if (func_80134510((s32)sp10)) {
        *(u16 *)(a0 + 6) = sp10[0];
        *(u16 *)(a0 + 0xA) = sp10[1];
        *(u16 *)(a0 + 0xE) = sp10[2];
        *(s16 *)(a0 + 0xE8) = (*(s16 *)D_801152A8);
        *(s16 *)(a0 + 0xEA) = D_801152AA;
        *(s16 *)(a0 + 0xEC) = D_801152AC;
        func_80180E78(a0, a0 + 0xE8);
        *(s16 *)(a0 + 2) = 7;
    }
}


typedef struct { s16 h[3]; } SV3L;
extern void func_80180C0C(s16 *a0);
extern void func_80180F3C(void *a0);
extern s32 func_801809F0();
extern void func_8012C218(void *a0);
extern void func_80180DF0(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern u8 D_801152A8[];
extern s16 D_801152B0;
extern u8 D_800D3918[];

void func_8017FE10(s32 a0) {
    extern u8 D_801A60E8[];   /* two 0x10-byte records: +0x00 and +0x10 */
    SV3L sp10;
    s32 v1;

    v1 = ((s32 (*)(void *, void *, s32))func_80180C0C)((void *)a0, D_800D3918, 1);
    if ((v1 & 0xE000) == 0) {
        ((void (*)(s32, void *, void *))func_80180F3C)(a0, &D_801A60E8[0], &sp10);
        v1 = func_801809F0(a0, &sp10, 1, 1);
        if ((v1 & 0xE000) == 0) {
            func_8012C218((void *)a0);
            return;
        }
    }
    {
        void *tbl = (void *)D_801152A8;
        if (v1 & 0xC000) {
            tbl = (void *)&D_801152B0;
        }
        ((void (*)(s32, void *, s32))func_80180DF0)(a0, tbl, 4);
    }
    func_8012B178(a0, 0xFFF80000);
}


extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8017FEC8(void *a0) {
    extern s32 D_801AB144;
    extern s32 D_801A6058[];
    s32 ptr;
    unsigned short v0;

    func_8012A828((s32)a0, (s32)&D_801AB144);

    ptr = *(s32 *)((s32)a0 + 0x20);
    v0 = *(unsigned short *)((s32)a0 + 0xDC);
    *(unsigned short *)(ptr + 0x10) = v0;

    ptr = *(s32 *)((s32)a0 + 0x20);
    v0 = *(unsigned short *)((s32)a0 + 0xDE);
    *(unsigned short *)(ptr + 0x12) = v0;

    *(s32 *)((s32)a0 + 0x58) = (s32)D_801A6058 | 0x40000000 | 0x20000000;
    func_8012B2CC((s32)a0);

    func_8012B178((s32)a0, 0xFFF80000);

    *(unsigned short *)((s32)a0 + 0x2) = 9;
}


struct vecr { int _m; };

extern void func_8012AD80(struct vec*);
extern void func_80180F3C(void *a0);
extern s32 func_801809F0();
extern void func_8012C218(void *a0);

void func_8017FF4C(s32 arg0) {
    extern u8 D_801A60E8[]; /* two 0x10-byte records */
    s32 sp10[2];
    s32 ret;
    s32 v1;

    ((void (*)(struct vecr *))func_8012AD80)((struct vecr *)arg0);
    ((void (*)(s32, void *, void *))func_80180F3C)(arg0, &D_801A60E8[0], &sp10);
    ret = func_801809F0(arg0, &sp10, 1, 1);
    v1 = ret & 0xFF;
    if (v1 == 0x1A || v1 == 0x1C || ret == 0) {
        func_8012C218((void *)arg0);
    }
}



extern s32 D_801AB144;
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void *D_801A6048;
extern u8 D_801A6100[];

void func_8017FFC8(s32 a0) {
    s32 ptr;
    u16 v0;
    u16 f70;

    func_8012A828(a0, (s32)&D_801AB144);

    ptr = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(a0 + 0xDC);
    *(u16 *)(ptr + 0x10) = v0;

    ptr = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(a0 + 0xDE);
    *(u16 *)(ptr + 0x12) = v0;

    *(s32 *)(a0 + 0x58) = (s32)&D_801A6048 | 0x40000000 | 0x20000000;

    f70 = *(u16 *)(a0 + 0x70);
    *(s32 *)(a0 + 0xCC) = (s32)D_801A6100 + ((f70 & 0xF0) << 1);
    func_8012B2CC(a0);

    func_8012B178(a0, 0xFFF80000);

    *(u16 *)(a0 + 0x2) = 0xB;
    *(u16 *)(a0 + 0x34) = 0;
}




/* func_80180068 — 4-state handler on the u16 state word at +0x34.
 * Symbols spelled from asm/ov_SC05_003/nonmatchings/ov_SC05_003_jr_8017BEBC/func_80180068.s
 *
 * TU-adopted declarations (law 2):
 *   func_8012AD80 / func_8012C218 / func_80012C6C / func_80180F3C come from
 *   src/ov_SC05_003/ov_SC05_003_jr_8017BEBC.c verbatim; func_80180F3C is
 *   DEFINED there with one parameter, so its 3-arg use is a call-site cast
 *   (same idiom the TU already uses for ApplyMatrixSV / func_8012CBCC).
 */

extern void func_8012AD80(struct vec *a0);
extern void func_8012C218(void *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80180F3C(void*);

extern s32  func_801809F0();
extern s32  func_80180D4C();

extern void func_8012B21C(void *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern s32  func_80013478(s32 a0, s32 a1);   /* 2nd arg is the +0xCC record: the
                                              * copy-suggestion that puts it in $a1
                                              * (see the note at the use site) */


void func_80180068(s32 a0) {

    extern u8   D_801A60E8[];   /* two 0x10-byte records: +0x00 and +0x10 */
    SV3_8012CC88 sp10;   /* sp+0x10, 8 bytes -> 0x28 frame */
    s32 r;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        func_8012AD80((struct vec *)a0);
        ((void (*)(s32, void *, void *))func_80180F3C)(a0, &D_801A60E8[0], &sp10);
        func_801809F0(a0, &sp10, 1, 1);
        ((void (*)(s32, void *, void *))func_80180F3C)(a0, &D_801A60E8[0x10], &sp10);
        if (func_80180D4C(a0, &sp10, 1) & 0x2000) {
            func_8012B21C((void *)a0);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    /* case 1: the second read of *(s32 *)(a0 + 0xCC) is ALSO func_80013478's
     * arg1.  local-alloc's copy-suggestion then homes that pseudo in $a1 and
     * deletes the redundant `move $a1,$a1`, which is why the target loads
     * `lw $a1, 0xCC($s1)` and the `lh` lands in $v1 instead of reusing the base.
     * Writing the call with one argument compiles to 152/152 with those exact
     * two instructions in $v1 (only a `register __asm__("$5")` pin recovers it,
     * and a pin would forfeit the h_seq family). */
    case 1:
        if (*(s16 *)(*(s32 *)(a0 + 0xCC) + 6) != -1) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                func_80012C6C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10), 0, 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) +
                func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4),
                                            (void *)*(s32 *)(a0 + 0xCC)),
                              8);
        }
        func_8012B178(a0, 0xFFF80000);
        r = ((s32 (*)(s32))func_8012CBA4)(a0) & 0x8000;
        if (*(s16 *)(*(s32 *)(a0 + 0xCC) + 6) != -1) {
            if (func_80013478(a0 + 4, *(s32 *)(a0 + 0xCC)) < 0x100) {
                *(s32 *)(a0 + 0xCC) = *(s32 *)(a0 + 0xCC) + 8;
            }
        } else if (r != 0) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    case 2:
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            func_80012C6C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10), -0x400, 8);
        func_8012B178(a0, 0xFFF80000);
        func_8012CBCC(a0);
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x21) {
            *(s32 *)(a0 + 0x48) = 0;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;

    case 3:
        func_8012AD80((struct vec *)a0);
        ((void (*)(s32, void *, void *))func_80180F3C)(a0, &D_801A60E8[0], &sp10);
        if ((func_801809F0(a0, &sp10, 1, 1) & 0xE000) == 0) {
            func_8012C218((void *)a0);
        }
        break;
    }
}


extern s32 D_801A60D8[];
extern s32 D_801AB214;
void func_801802C8(s32 *a0) {
    s32 *s0 = a0;
    s32 v0;
    s32 v1;
    *(s16 *)((char *)s0 + 2) = 0xD;
    *(s16 *)((char *)s0 + 0x34) = 0;
    *(s32 *)((char *)s0 + 0x1C) = 0;
    func_8012C588(0x24F, (s32)s0);
    v1 = *(s32 *)((char *)s0 + 0x20);
    v0 = D_801A60D8[*(u16 *)((char *)s0 + 0x70) & 0xF];
    *(s32 *)(v1 + 0x24) = v0;
    func_8012A828((s32)s0, (s32)&D_801AB214);
}



extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);


void func_80180338(s32 arg0) {

    extern s32 D_801AB264;
    extern s32 D_801AB2EC;
    extern s32 D_801AB1CC;
    extern s32 D_801A60D0[];
    s32 v0;
    s32 p;
    u16 mode;
    s32 idx;
    s32 q;

    v0 = func_8012B864(arg0);
    v0 = func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), v0 + 0x800, 10);
    p = *(s32 *)(arg0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;

    mode = *(u16 *)(arg0 + 0x34);
    switch (mode) {
        case 0:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                func_8012A828(arg0, (s32) &D_801AB264);
                v0 = *(u16 *)(arg0 + 0x34) + 1;
                *(u16 *)(arg0 + 0x34) = v0;
            }
            break;
        case 1:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                v0 = *(s32 *)(arg0 + 0x1C) + 1;
                *(s32 *)(arg0 + 0x1C) = v0;
                if (v0 >= 4) {
                    func_8012A828(arg0, (s32) &D_801AB2EC);
                    *(u16 *)(arg0 + 0x34) += 1;
                }
            }
            break;
        case 2:
            if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
                func_8012A828(arg0, (s32) &D_801AB1CC);
                *(s32 *)(arg0 + 0x1C) = 0x1E;
                *(u16 *)(arg0 + 0x34) += 1;
            }
            break;
        case 3:
            if (func_8012BEE8(arg0) != 0) {
                idx = *(u16 *)(arg0 + 0x70) & 0xF;
                *(u16 *)(arg0 + 0x2) = 1;
                q = *(s32 *)(arg0 + 0x20);
                *(s32 *)(q + 0x24) = D_801A60D0[idx];
            }
            break;
    }
}


extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012E9C0(s32 a0);
extern void func_80131E00();

void func_801804C0(s32 param_1) {
    s32 s0;
    s32 v0;
    s32 v1;
    s32 a2;
    s32 p;
    s32 ret;

    func_8012E9C0(param_1);
    s0 = param_1;

    v0 = *(s32 *)(s0 + 0x78);
    v1 = *(s16 *)(s0 + 0x60);
    v0 = *(s16 *)(v0 + 0x30);
    a2 = v1 * v0;
    v0 = a2 >> 12;
    v1 = v0;
    __asm__ __volatile__("" : "=r"(v0) : "0"(v0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    if ((s16)v0 <= 0) {
        v1 = 1;
    }

    v0 = *(u16 *)(s0 + 0x76) - v1;
    *(s16 *)(s0 + 0x76) = v0;

    v0 = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(s16 *)(s0 + 0x5C) = v0;
    if (*(s16 *)(s0 + 0x76) <= 0) {
        *(s16 *)(s0 + 0x5C) = 0;
    }

    v1 = *(u16 *)(s0 + 0x70);
    if (v1 & 1) {
        if ((v1 & 0xE000) != 0) {
            goto label_468;
        }
        v0 = *(u16 *)(s0 + 0x62);
        p = *(s32 *)(s0 + 0x20);
        v0 = (v0 + 0x800) & 0xFFF;
        *(u16 *)(p + 0x12) = v0;
    }
    v0 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v0 + 0x14) = 0;
    *(s16 *)(v0 + 0x10) = 0;
    func_8012B2CC(s0);

label_468:
    func_8012B23C(s0);

    if (*(s16 *)(s0 + 0x76) <= 0) {
        func_80131E00(s0, 0xC);
    } else {
        ret = func_80131A34(s0, 4);
        if (ret != 0) {
            *(s8 *)(s0 + 0xC2) = 0;
        } else {
            *(s8 *)(s0 + 0xC2) = 1;
            *(s16 *)(s0 + 0x98) = 0;
            *(s32 *)(s0 + 0x1C) = 0x10;
        }
    }
}


extern void func_8012CBCC(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_80131E00();
extern void func_80180900(u8 *a0);
extern void func_801808A4(s32 a0);

void func_801805D4(s32 a0) {
    s32 v0;
    s32 v1;
    s32 s1;

    s1 = 0;
    v1 = ((s32 (*)(s32))func_8012CBCC)(a0) & 0xFF;
    if (v1 == 2) {
        func_80131E00(a0, 0x12);
    } else if (v1 == 0x1A) {
        ((void (*)(s32))func_80180900)(a0);
    } else {
        if (*(u8 *)(a0 + 0xC2) != 0) {
            v0 = func_8012BEE8(a0);
        } else {
            v0 = *(u16 *)(a0 + 0x72) & 0x4000;
        }
        if (v0 != 0) {
            s1 = 1;
        }
        if (s1 != 0) {
            func_801808A4(a0);
        }
    }
}


void func_8018068C(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
    }




extern s32 D_801AB3AC;
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801806A0(s32 param_1) {
    func_8012A828(param_1, (s32)&D_801AB3AC);
    *(u16 *)(param_1 + 0x5C) = 0;
    *(u16 *)(param_1 + 0x34) = 0;
    *(s32 *)(param_1 + 0x1C) = 0x10;
    func_8002D4C8(0x84D, 0);
}



extern s32 func_8012BEE8(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80180D4C();
extern void func_80180F3C(void*);
extern void func_8012E8C4(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_80180900(u8*);
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 dx, s32 dy);

/* a0 = actor base (state u16 at +0x34, mode s32 at +0x1C).
 * case 0/1/2 dispatch on the actor's state field; case 0 additionally spawns
 * a sub-object via func_80132EF4(a0, 0x50) and, depending on flag bits
 * returned by func_80180D4C, aims it using a table entry (D_801152B0 /
 * D_801152A8) via ratan2 + func_80047D3C (hypot-like). */
void func_801806EC(s32 a0) {

    extern s16 D_801152B0;
    extern u8 D_801152A8[];
    extern u8 D_801A60E8[];
    s32 state;
    s32 s2;
    void *s1;
    s16 buf[4];
    s32 flags;
    s32 v0;
    s32 t0;
    s32 t1;
    s16 tmp;

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x80;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        s2 = func_80132EF4(a0, 0x50);
        if (s2 == 0) {
            return;
        }
        s1 = 0;
        ((void (*)())func_80180F3C)(a0, D_801A60E8, buf);
        flags = func_80180D4C(a0, buf, 1);
        if (flags & 0xC000) {
            s1 = &D_801152B0;
        } else if (flags & 0x2000) {
            s1 = D_801152A8;
        }
        if (s1 != 0) {
            v0 = ratan2(*(s16 *)((u8 *)s1 + 4), *(s16 *)((u8 *)s1 + 2));
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x10) = v0 + 0x400;
            tmp = *(s16 *)((u8 *)s1 + 4);
            t0 = tmp * tmp;
            tmp = *(s16 *)((u8 *)s1 + 2);
            t1 = tmp * tmp;
            v0 = func_80047D3C(t0 + t1);
            v0 = ratan2(*(s16 *)((u8 *)s1 + 0), -v0);
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x12) = v0;
        } else {
            *(s16 *)(*(s32 *)(s2 + 0x20) + 0x10) = 0x400;
        }
        return;
    case 1:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x20;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;
    case 2:
        func_8012E8C4(a0);
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        func_80130D48(a0);
        ((void (*)(s32))func_80180900)(a0);
        return;
    default:
        return;
    }
}


void func_801808A4(s32 param_1)
{
    s32 ptr;
    u16 flags;

    ptr = *(s32 *)(param_1 + 0x78);
    flags = *(u16 *)(param_1 + 0x70);
    *(u8 *)(param_1 + 0xC1) = 0;
    *(u16 *)(param_1 + 0x5E) = 0;
    *(u16 *)(param_1 + 0x5C) = *(u16 *)(ptr + 2);
    if (flags & 1) {
        if (flags & 0x8000) {
            *(u16 *)(param_1 + 2) = 6;
            return;
        }
        if (flags & 0x4000) {
            *(u16 *)(param_1 + 2) = 8;
            return;
        }
        if (flags & 0x2000) {
            *(u16 *)(param_1 + 2) = 0xA;
            return;
        }
        *(u16 *)(param_1 + 2) = 3;
    } else {
        *(u16 *)(param_1 + 2) = 1;
    }
}


extern void func_8002AC00(s32 arg);
extern void func_8002A04C(s32 a0);
extern void func_8012C098(void *param_1);

void func_80180900(u8 *a0) {
    func_8002AC00(0x19);
    ((s32 (*)(u8 *))func_8002A04C)(a0);
    ((void (*)(u8 *))func_8012C098)(a0);
}



extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 D_801A61C8;
extern s32 *D_80126B78;
extern u8 D_801152A8[];

s32 func_8018093C(void *a0) {
    SVECTOR buf1;
    SVECTOR buf2;

    func_8012F14C((s32)D_80126B78 + 0x34, (s32)&D_801A61C8, (s32)&buf1);
    func_8012F14C((s32)D_80126B78 + 0x34, (s32)&D_801A61C8 + 8, (s32)&buf2);
    if (func_80135888(*(s32 *)((s32)a0 + 0x20), *(s32 *)((s32)a0 + 0x58), (s32)&buf1, (s32)&buf2) != 0) {
        func_8012F568(1, 1, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12), 0x20, (s32)&buf2, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


struct vec;
extern void func_8012AD80(struct vec *a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_801809F0(s32 a0, s32 a1, s32 a2, s32 a3) {
    u16 sp10[4];
    u16 sp18[4];
    s32 v0;

    if (a3 == 0) {
        sp10[0] = *(u16 *)(a0 + 0x3A);
        sp10[1] = *(u16 *)(a0 + 0x3E);
        sp10[2] = *(u16 *)(a0 + 0x42);
        func_8012AD80((struct vec *)a0);
    } else {
        sp10[0] = *(u16 *)(a0 + 0x06);
        sp10[1] = *(u16 *)(a0 + 0x0A);
        sp10[2] = *(u16 *)(a0 + 0x0E);
    }

    sp18[0] = *(u16 *)(a0 + 0x06);
    sp18[1] = *(u16 *)(a0 + 0x0A);
    sp18[2] = *(u16 *)(a0 + 0x0E);
    sp18[0] += *(u16 *)(a1 + 0);
    sp18[1] += *(u16 *)(a1 + 2);
    sp18[2] += *(u16 *)(a1 + 4);

    v0 = func_80133784((s32)(s16)a2, sp10, (s32)sp18);
    if ((v0 & 0xE000) == 0) {
        sp10[0] = sp18[0];
        sp10[1] = sp18[1] + 8;
        sp10[2] = sp18[2];
        v0 = func_80133784((s32)(s16)a2, sp18, (s32)sp10);
        if ((v0 & 0xE000) == 0) {
            sp18[0] = sp10[0] + *(u16 *)(a1 + 0);
            sp18[1] = sp10[1] + *(u16 *)(a1 + 2);
            sp18[2] = sp10[2] + *(u16 *)(a1 + 4);
            v0 = func_80133784((s32)(s16)a2, sp10, (s32)sp18);
            if ((v0 & 0xE000) == 0) {
                sp18[0] = sp10[0] - *(u16 *)(a1 + 0);
                sp18[1] = sp10[1] - *(u16 *)(a1 + 2);
                sp18[2] = sp10[2] - *(u16 *)(a1 + 4);
                v0 = func_80133784((s32)(s16)a2, sp10, (s32)sp18);
            }
            v0 |= *(u8 *)((char *)sp18 + 6);
            *(u16 *)(a0 + 0x06) = sp18[0];
            *(u16 *)(a0 + 0x0A) = sp18[1];
            *(u16 *)(a0 + 0x0E) = sp18[2];
            goto done;
        }
        v0 |= *(u8 *)((char *)sp10 + 6);
        *(u16 *)(a0 + 0x06) = sp10[0];
        *(u16 *)(a0 + 0x0A) = sp10[1];
        *(u16 *)(a0 + 0x0E) = sp10[2];
        goto done;
    }
    v0 |= *(u8 *)((char *)sp18 + 6);
    *(u16 *)(a0 + 0x06) = sp18[0];
    *(u16 *)(a0 + 0x0A) = sp18[1];
    *(u16 *)(a0 + 0x0E) = sp18[2];
done:
    return v0;
}


struct vec;
extern void func_8012AD80(struct vec *a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 aF80180C0C(s32 a0, s32 a1, s32 a2) __asm__("func_80180C0C");

s32 aF80180C0C(s32 a0, s32 a1, s32 a2) {
    u16 sp10[4];
    u16 sp18[4];
    s32 v0;

    sp10[0] = *(u16 *)(a0 + 0x3A);
    sp10[1] = *(u16 *)(a0 + 0x3E);
    sp10[2] = *(u16 *)(a0 + 0x42);
    sp10[0] += *(u16 *)(a1 + 0);
    sp10[1] += *(u16 *)(a1 + 2);
    sp10[2] += *(u16 *)(a1 + 4);

    func_8012AD80((struct vec *)a0);

    sp18[0] = *(u16 *)(a0 + 0x06);
    sp18[1] = *(u16 *)(a0 + 0x0A);
    sp18[2] = *(u16 *)(a0 + 0x0E);
    sp18[0] += *(u16 *)(a1 + 0);
    sp18[1] += *(u16 *)(a1 + 2);
    sp18[2] += *(u16 *)(a1 + 4);

    v0 = ((s32 (*)(s32, s32, s32))func_80133784)((s32)(s16)a2, (s32)sp10, (s32)sp18);

    sp18[0] -= *(u16 *)(a1 + 0);
    sp18[1] -= *(u16 *)(a1 + 2);
    v0 |= *(u8 *)((char *)sp18 + 6);
    sp18[2] -= *(u16 *)(a1 + 4);
    *(u16 *)(a0 + 0x06) = sp18[0];
    *(u16 *)(a0 + 0x0A) = sp18[1];
    *(u16 *)(a0 + 0x0E) = sp18[2];
    return v0;
}


s32 func_80180D4C(u8 *a0, u8 *a1, s32 a2) {
    u16 sp10[3];
    u16 sp18[4];

    sp10[0] = *(u16 *)(a0 + 0x6);
    sp10[1] = *(u16 *)(a0 + 0xA);
    sp10[2] = *(u16 *)(a0 + 0xE);

    sp18[0] = *(u16 *)(a0 + 0x6);
    sp18[1] = *(u16 *)(a0 + 0xA);
    sp18[2] = *(u16 *)(a0 + 0xE);

    sp18[0] += *(u16 *)(a1 + 0x0);
    sp18[1] += *(u16 *)(a1 + 0x2);
    sp18[2] += *(u16 *)(a1 + 0x4);

    return func_80133784((s16)a2, sp10, sp18) | *(u8 *)((u8 *)sp18 + 6);
}


extern void func_80180E78(s32 a0, s32 a1);

void func_80180DF0(s32 a0, s32 a1, s32 a2) {
    s32 s1;
    s1 = (s16)a2;
    *(s16 *)(a0 + 0xE8) = func_80012C6C(*(s16 *)(a0 + 0xE8), *(s16 *)a1, s1);
    *(s16 *)(a0 + 0xEA) = func_80012C6C(*(s16 *)(a0 + 0xEA), *(s16 *)(a1 + 2), s1);
    *(s16 *)(a0 + 0xEC) = func_80012C6C(*(s16 *)(a0 + 0xEC), *(s16 *)(a1 + 4), s1);
    func_80180E78(a0, a0 + 0xE8);
}


void func_80180E78(s32 a0, s32 a1) {
    s16 ang[4];
    void *m;

    m = (void *)(*(s32 *)(a0 + 0x20) + 0x34);
    ang[0] = ratan2(*(s16 *)(a1 + 4), *(s16 *)(a1 + 2));
    ang[2] = ratan2(*(s16 *)a1,
                    -func_80047D3C((*(s16 *)(a1 + 4)) * (*(s16 *)(a1 + 4)) +
                                   (*(s16 *)(a1 + 2)) * (*(s16 *)(a1 + 2))));
    func_80013F3C((s32)m);
    RotMatrixY(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), m);
    RotMatrixZ(ang[2], m);
    RotMatrixX(ang[0], m);
    func_8012B260((u8 *)a0);
}


extern void ApplyMatrixSV(void*, void*, void*);
    void func_80180F3C(void * arg0) {
        ((void (*)(s32 *))ApplyMatrixSV)(*(void **)((char *)arg0 + 0x20) + 0x34);
    }


void func_80180F60(u8 *arg) {
    u16 sp10[4];
    u16 sp18[4];
    s32 sp20;
    s32 s1;
    s32 s2;
    s32 v0;
    s32 v1;

    sp10[1] = *(u16 *)(arg + 0xA);
    s1 = *(s16 *)(*(s32 *)(arg + 0x20) + 0x12);
    for (s2 = 0; s2 < 0x20; s2++) {
        func_8012B0B4(&sp20, s1, 0x10);
        v1 = sp20;
        sp10[0] = sp18[0] = *(u16 *)(arg + 6) + v1;
        sp10[2] = sp18[2] = *(u16 *)(arg + 0xE) + (v1 >> 16);
        sp18[1] = *(u16 *)(arg + 0xA) + 8;
        if (func_80133784(1, sp10, sp18) & 0x2000) {
            *(u16 *)(arg + 6) = sp18[0];
            *(u16 *)(arg + 0xA) = sp18[1];
            *(u16 *)(arg + 0xE) = sp18[2];
            *(s32 *)(arg + 0xE0) = s1;
            *(s16 *)(*(s32 *)(arg + 0x20) + 0x12) = s1;
            break;
        }
        s1 += 0x80;
    }
    *(s32 *)(arg + 0xE8) = 0;
}


extern void func_800183E0(s32 a0);
extern u16 D_800B99DA;
extern s32 D_801A61D8[];
extern s32 D_801A6210[];
extern s32 D_801A6248[];

void func_8018104C(void) {
    func_800183E0(D_801A61D8[D_800B99DA % 14]);
    func_800183E0(D_801A6210[D_800B99DA % 14]);
    func_800183E0(D_801A6248[D_800B99DA & 0xF]);
}



extern void (*D_801A6294[])(void);

void func_80181128(void *a0) {
    D_801A6294[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(void *a0, void *a1);
extern u8 D_801A6288[];
extern void func_801815E0();

void func_80181164(s32 arg0)
{
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);

    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        *(s32 *)((u8 *)arg0 + 0x20) = v0;

        func_8001CA1C((void *)v0, D_801A6288);

        *(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x2C) |= 0x10;

        *(s16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x18) =
            ((s32)*(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x18) << 16) >> 17;

        *(s16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x1A) =
            ((s32)*(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x1A) << 16) >> 17;

        *(s16 *)((u8 *)arg0 + 0xFE) =
            *(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x64)) + 0x36);

        func_801815E0(arg0, 2);

        *(s16 *)((u8 *)arg0 + 2) = 1;
    }
}


extern void func_801815E0();
extern s32 D_801AB374;
extern s32 D_801AB2EC;

void func_80181224(void *a0) {
    s32 a2 = *(s32 *)((u8 *)a0 + 0x64);
    s32 v1 = *(s16 *)((u8 *)a0 + 0xFE);
    s32 a1 = *(s32 *)((u8 *)a0 + 0x20);

    if (v1 != *(s16 *)((u8 *)a2 + 0x36) || *(s32 *)((u8 *)a2 + 0x90) == &D_801AB374) {
        *(s32 *)((u8 *)a0 + 0x48) = 0xC000;
        *(s16 *)((u8 *)a0 + 2) = 3;
    } else {
        u16 m18 = *(u16 *)((u8 *)a1 + 0x18);
        u16 t1a = *(u16 *)((u8 *)a1 + 0x1A);

        *(u16 *)((u8 *)a1 + 0x18) = m18 + 0x40;
        *(u16 *)((u8 *)a1 + 0x1A) = t1a + 0x40;
        if (*(s16 *)((u8 *)a1 + 0x18) >= 0x1801 || (s16)(t1a + 0x40) >= 0x1801) {
            *(u16 *)((u8 *)a1 + 0x1A) = 0x1800;
            *(u16 *)((u8 *)a1 + 0x18) = 0x1800;
        }

        a1 = *(s32 *)((u8 *)a0 + 0x64);
        if (*(s32 *)((u8 *)a1 + 0x90) == &D_801AB2EC && *(s32 *)((u8 *)a1 + 0x94) == 9) {
            *(s16 *)((u8 *)a0 + 2) = 2;
        }
        func_801815E0(a0, 2);
    }
}


void func_801812F4(s32 a0) {
    extern u8 D_80126B5C;
    extern void func_8012B2CC();
    extern s32 func_80013328(s32 a0, s32 a1);
    extern void func_8012B14C();
    extern void func_8012CBF4();
    extern s32 func_80181DE4(s32 a0, s32 a1);
    s16 t;
    s32 vec[4];

    t = *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + 0x800;
    func_8012B2CC(a0);
    vec[0] = 0;
    vec[1] = 0xFFF00000;
    vec[2] = -((func_80013328(&D_80126B5C, a0 + 4) << 0x10) / 0x22);
    func_8012B14C(a0, (s32)vec);
    *(s32 *)(a0 + 0x48) = 0x18000;
    func_8012CBF4(a0);
    func_80181DE4(a0, 0x7FA);
    *(s16 *)(a0 + 2) = 3;
}



/* Callees / globals — spelled exactly as this TU's own declarations
 * (law 2/2b). See src/ov_SC05_003/ov_SC05_003_jr_8017BEBC.c for the
 * canonical spellings this draft adopted:
 *   - D_801270C0  : extern u16 D_801270C0;   (line 1129)  read via *(s16*)& cast
 *                   (idiom seen at src/ov_SC03_006/ov_SC03_006_jr_80140608.c:1778)
 *   - D_801152B0  : extern s16 D_801152B0;   (line 405)
 *   - D_801152A8  : extern u8 D_801152A8[];  (line 600/635)
 *   - func_8012C218 : extern void func_8012C218(void *a0);  (line 4730, used by
 *                     the in-TU neighbour func_80182470 at line 4739)
 *   - func_8012CBF4 : canonical decl is `void func_8012CBF4(s32 a0)` (see
 *                     src/shared/engine_core.h DEFINE_func_8012CBF4); callers
 *                     that need its $v0 side value cast the call, e.g.
 *                     src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:4793.
 *   - func_80132EF4 : extern s32 func_80132EF4(s32 a0, s32 a1); (used earlier
 *                     in this same TU, e.g. line 4553/4586).
 *   - ratan2, func_80047D3C : per this TU's own externs (lines 247/270 area).
 *   - func_80181DE4 : DEFINED earlier in this same TU (line 4454) as
 *                     `s32 func_80181DE4(s32 a0, s32 a1)`.
 *   - func_8012D5E4 : extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
 *                     (repo-wide idiom `(s32)D_x, (s32)D_x + 8` — e.g.
 *                     src/ov_SC04_007/ov_SC04_007_jr_8017BEBC.c:6765).
 *   - D_80126B96  : not declared in this TU yet; repo-wide canonical is
 *                     `extern u16 D_80126B96;`.
 *   - D_801A62A8  : brand-new symbol (no other TU references it). Declared
 *                     raw array per the func_8012D5E4-table idiom
 *                     `extern u8 D_x[];`.
 */

extern void func_8012C218(void *a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_80181DE4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

void func_801813B4(s32 a0) {

    extern u16 D_801270C0;
    extern s16 D_801152B0;
    extern u8 D_801152A8[];
    extern u16 D_80126B96;
    extern u8 D_801A62A8[];
    s32 obj = a0;
    s16 v1;
    s16 *s1;
    s32 s0;
    s32 i;
    s32 pad[2]; /* dead-local frame pad (cookbook §162i1); target frame is 8
                 * bytes larger than this body's live locals account for. */

    if (*(s16 *)(obj + 0xA) >= 0x10) {
        func_8012C218((void *)a0);
        return;
    }

    s1 = 0;
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    if (*(s16 *)&D_801270C0 == 2) {
        return;
    }

    v1 = ((s32 (*)(s32))func_8012CBF4)(obj);
    if (v1 & 0xC000) {
        s1 = &D_801152B0;
    } else if (v1 & 0x2000) {
        s1 = (s16 *)D_801152A8;
    }

    if (s1 != 0) {
        for (i = 0; i < 6; i++) {
            func_80132EF4(obj, 0x51);
        }
        s0 = func_80132EF4(obj, 0x50);
        if (s0 != 0) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
                ratan2(s1[2], s1[1]) + 0x400;
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                ratan2(s1[0], -func_80047D3C(s1[2] * s1[2] + s1[1] * s1[1]));
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x14) = 0;
        }
        func_80181DE4(obj, 0x7FB);
        func_8012C218((void *)obj);
    } else {
        if (func_8012D5E4(obj, (s32)D_801A62A8, (s32)D_801A62A8 + 8, 0x18) == 1) {
            D_80126B96 = 0x4014;
        }
    }
}


extern void func_8012C218(void *a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80181DE4(s32 a0, s32 a1);

void func_80181540(s32 a0) {
    s32 obj = a0;
    void *s0;
    s32 i;

    if (*(s16 *)(obj + 0xA) >= 0x10) {
        func_8012C218((void *)obj);
        return;
    }

    if (((s32 (*)(s32))func_8012CBF4)(obj) & 0x6000) {
        s0 = func_80132EF4(obj, 0x50);
        if (s0 != 0) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0x400;
        }
        for (i = 0; i < 3; i++) {
            func_80132EF4(obj, 0x51);
        }
        func_80181DE4(obj, 0x7FB);
        func_8012C218((void *)obj);
    }
}


#include "common.h"

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern u8 D_801A62B8[];

void func_801815E0(s32 arg0, s32 arg1) {
    s32 buf[8];
    u16 out[4];

    func_8012EC04(*(s32 *)(arg0 + 0x64), arg1, buf);
    func_8012F14C(buf, D_801A62B8, out);
    *(u16 *)(arg0 + 0x6) = out[0];
    *(u16 *)(arg0 + 0xA) = out[1];
    *(u16 *)(arg0 + 0xE) = out[2];
}



extern s32 func_80181828(void *a0);  /* S79 #6: the body (twin of ov_SC05_003:func_80181720) returns s32; callers ignore it — byte-neutral */

void func_80181648(void *a0) {

    extern void (*D_801A62CC[])(void);
    D_801A62CC[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_80181828(a0);
    }
}


void func_801816A8(void *arg0) {
    extern s32 D_801A62C0;
    s32 val = 0x0C000040;
    u8 *p = *(u8 **)((s32)arg0 + 0x20);

    p[0x26] = 0x80;
    p[0x25] = 0x80;
    p[0x24] = 0x80;
    *(u16 *)(p + 0x00) = 2;
    *(u16 *)(p + 0x02) = 2;
    *(u16 *)(p + 0x28) = 0x2F0;
    *(u16 *)(p + 0x2A) = 0x100;
    *(s32 *)(p + 0x20) = (s32)&D_801A62C0;
    *(volatile u16 *)(p + 0x2C) = 0;
    *(u16 *)(p + 0x2C) = 0xC006;
    p[0x27] = 0x51;
    *(u16 *)(p + 0x08) = 0;
    *(u16 *)(p + 0x0A) = 0;
    *(u16 *)(p + 0x0C) = 0;
    *(u16 *)(p + 0x2E) = 0;
    *(u16 *)(p + 0x30) = 0;
    *(u16 *)(p + 0x32) = 0;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x04) = val;
    *(u16 *)(p + 0x1A) = 0xC00;
    *(u16 *)(p + 0x18) = 0xC00;
    (*(u16 *)((s32)arg0 + 2))++;
}


extern void func_80181740_dummy(void);

void func_80181740(void *a0)
{
    s32 p;

    p = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(p + 0x18) += 0x20;
    *(u16 *)(p + 0x1A) += 0x20;
    if (++*(s32 *)((s32)a0 + 0x1C) >= 0x80) {
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
}


void func_80181798(void *a0) {
        s32 v0;
        v0 = *(s32 *)((s32)a0 + 0x1C);
        v0 += 1;
        *(s32 *)((s32)a0 + 0x1C) = v0;
        if (v0 >= 0x40) {
            *(u16 *)((s32)a0 + 0x2) += 1;
        }
    }


extern void func_801292C8(u8 *a0);

void func_801817CC(a0)
u8 *a0;
{
    u8 *a1 = *(u8 **)(a0 + 0x20);

    *(u16 *)(a1 + 0x18) = *(u16 *)(a1 + 0x18) - 0x100;
    *(u16 *)(a1 + 0x1A) = *(u16 *)(a1 + 0x1A) - 0x100;
    if (*(s16 *)(a1 + 0x18) <= 0 || *(s16 *)(a1 + 0x1A) <= 0) {
        func_801292C8(a0);
    }
}


/* Handwritten function (the target .s itself is splat-flagged handwritten) -- a bare-jr/mult/GTE
 * shape no -O2 C reaches -- cookbook section 265 verbatim-asm lane, file-scope form, precedented by
 * VectorNormal/func_8017D810 in src/800b.c). Transcribed 1:1 from
 * asm/ov_SC05_005/nonmatchings/ov_SC05_005_jr_8017D898/func_80181828.s.
 *
 * Recovered C semantics: squared-XZ-distance + Y-band gate against the actor at a0; on pass,
 * normalizes the XZ/0/Z-ish diff vector via VectorNormal and fires func_8012F568(1,0x4014,0,
 * 0x18,&xy,&diff16) (an effect/sound-ish call), returning 1; otherwise returns 0.
 */
/* func_80181828 (ov_SC05_003, 87 ins) — MATCH.
 * Callees / globals spelled from THIS target's own relocation lines (law 1) and
 * typed per the destination TU's existing decls (law 2):
 *   D_801270C0 / D_80126B5E / D_80126B62 / D_80126B66 : extern u16, read via (s16)
 *     (the TU already declares all four u16 — lines 1129 / 3992 / body of
 *      func_8017F1AC; the `lh %lo(...)` in the .s is the (s16) cast, not s16 decl)
 *   func_8012F568 : extern void func_8012F568(s32 x6)  (TU line 4650 / 5662)
 *   VectorNormal  : the .s says `jal VectorNormal` (NOT the TU's VectorNormalSS);
 *                   repo idiom is the empty-param `extern void VectorNormal();`
 *                   (src/md_SC07_004/md_SC07_004.c:4167).
 *
 * Two levers were needed on top of the neighbour shape (func_8017F1AC, §194-E):
 *  1. cookbook §197-A — `lh $a1,0x18($v0) ; sra $a1,$a1,7` was coming out as
 *     `lhu ; sll 16 ; sra 23` (LENGTH-DRIFT +1). The zero-byte asm re-tie
 *     `__asm__("" : "=r"(h) : "0"(h))` takes the shift's operand out of the
 *     sign-extension's equivalence class and restores the 2-instruction form.
 *  2. §193-C cross-jumping — with plain `return 0;` in both arms of the
 *     ±10 window test, gcc merged the common `slti ; bnez` suffix (-4 ins).
 *     Routing the negative arm through `goto ret0;` (the same idiom the in-TU
 *     neighbour func_8017F1AC uses) splits the two exits and reproduces the
 *     target's bltz / j / beqz .L80181868 layout exactly.
 * Statement order raw[0],raw[1],raw[2],vx,vy,vz is load-bearing: it fixes the
 * $a0/$v1 roles of the 0x6 and 0xE halfwords (sched1 birth order).
 */

extern u16 D_801270C0;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void VectorNormal();
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_80181828(void *arg0) {
    typedef struct { s32 vx, vy, vz; } VEC3L;
    VEC3L v;
    s16 raw[4];
    s16 buf[4];
    s32 r;
    s32 d;
    s32 h;

    if (*(s16 *)&D_801270C0 == 2) {
        return 0;
    }

    h = *(s16 *)(*(s32 *)((s32)arg0 + 0x20) + 0x18);
    __asm__("" : "=r"(h) : "0"(h));   /* §197-A re-tie: keeps lh + sra 7 */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    r = h >> 7;
    raw[0] = *(u16 *)((s32)arg0 + 0x6);
    raw[1] = *(u16 *)((s32)arg0 + 0xA);
    raw[2] = *(u16 *)((s32)arg0 + 0xE);
    v.vx = (s16)D_80126B5E - raw[0];
    v.vy = 0;
    v.vz = (s16)D_80126B66 - raw[2];

    /* gte SQR on the XZ difference vector (in place) */
    __asm__ volatile (
        "lwc2 $9, 0( %0 );"
        "lwc2 $10, 4( %0 );"
        "lwc2 $11, 8( %0 );"
        "nop;"
        "nop;"
        "sqr 0;"
        "swc2 $25, 0( %0 );"
        "swc2 $26, 4( %0 );"
        "swc2 $27, 8( %0 )"
        :
        : "r"(&v)
        : "$9", "$10", "$11", "memory");

    if (r * r <= v.vx + v.vz) {
        return 0;
    }

    d = (s16)D_80126B62 - *(s16 *)((s32)arg0 + 0xA);
    if (d < 0) {
        if (9 < *(s16 *)((s32)arg0 + 0xA) - (s16)D_80126B62) {
            goto ret0;
        }
    } else if (9 < d) {
        return 0;
    }

    VectorNormal(&v, &v);
    buf[0] = v.vx;
    buf[1] = v.vy;
    buf[2] = v.vz;
    func_8012F568(1, 0x4014, 0, 0x18, (s32)raw, (s32)buf);
    return 1;
ret0:
    return 0;
}




extern void (*D_801A62E8[])(void);

void func_80181984(void *a0) {
    D_801A62E8[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_801819C0;

extern s32 rand(void);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801819C0(s32 arg0) {

    extern s32 D_801A62DC;
    s32 p;
    s32 tmp;
    s32 t2, t3, t4, t5;
    s32 rem128;
    s32 signed_rem;
    SVECTOR sv;
    MATRIX m;
    VECTOR v;

    p = *(s32 *)(arg0 + 0x20);
    *(s32 *)(p + 0x20) = (s32)&D_801A62DC;
    *(u8 *)(p + 0x27) = 0x52;
    *(u16 *)(p + 0x28) = 0x2D0;
    *(u16 *)(p + 0x2A) = 0x100;

    tmp = rand() % 0x1000 + 0x800;
    *(u16 *)(p + 0x1A) = tmp;
    *(u16 *)(p + 0x18) = tmp;

    t2 = rand();
    rem128 = t2 % 128;

    t3 = rand();
    if (!(t3 & 1)) {
        signed_rem = -rem128 - 0x300;
    } else {
        signed_rem = rem128 - 0x300;
    }
    sv.vx = signed_rem;

    t4 = rand();
    sv.vy = t4 % 0x1000;

    sv.vz = 0;
    v.vy = 0;
    v.vx = 0;

    t5 = rand();
    v.vz = -0x60000 - ((t5 % 4) << 16);

    func_80049CAC((s32)&sv, (s32)&m);
    func_800484EC((s32)&m, (s32)&v, arg0 + 0x10);

    *(s32 *)(arg0 + 0x1C) = 0x2D;
    *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
}


extern void func_801292C8(u8 *a0);
extern u8 D_800D3918[];

void func_80181B10(s32 a0) {
    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_801292C8((u8 *)a0);
        return;
    }
    if (func_80181BB4(a0, (s32)D_800D3918, 0x11) & 0x6000) {
        func_801292C8((u8 *)a0);
        return;
    }
    *(s32 *)(a0 + 0x1C) -= 1;
    if (*(s32 *)(a0 + 0x1C) < 0x23) {
        *(s32 *)(a0 + 0x14) += 0x10000;
    }
}



extern void func_8012931C(struct vec *a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

/* a0 = actor/entity base (struct vec-compatible; s16 fields at +6/+A/+E, s32 flag/vel at +0x14),
 * a1 = s16[3] offset vector, a2 = mode passed through to func_8012CEB0.
 * Same family as func_8012CC88 (src/ov_SC02_027/ov_SC02_027_jr_8012ACE0.c etc) but the
 * position-integration step is a real call to func_8012931C instead of being inlined. */
s32 func_80181BB4(s32 a0, s32 a1, s32 a2) {
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16*)(a0 + 0x06);
    sp10.vy = *(u16*)(a0 + 0x0A);
    sp10.vz = *(u16*)(a0 + 0x0E);
    sp10.vx += *(u16*)(a1 + 0);
    sp10.vy += *(u16*)(a1 + 2);
    sp10.vz += *(u16*)(a1 + 4);

    func_8012931C((struct vec *)a0);

    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a1 + 0);
    sp18.vy += *(u16*)(a1 + 2);
    sp18.vz += *(u16*)(a1 + 4);

    v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, a2);

    sp18.vx -= *(u16*)(a1 + 0);
    sp18.vy -= *(u16*)(a1 + 2);
    sp18.vz -= *(u16*)(a1 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;

    if (v0 & 0x6000) {
        *(s32*)(a0 + 0x14) = 0;
    }
    return v0;
}








extern void func_8012BE54(s32);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_80181D08(void *arg0) {
    struct {
        u16 u06;
        u16 u0A;
        u16 u0E;
        u16 unk16;
        u16 u70;
        u16 zero1A;
        u16 unk1C;
        u16 unk1E;
        s32 unk20;
    } sp;
    s32 var;

    var = (*(s32 *)((char *)arg0 + 0x1C))++;
    if ((var % (s32)*(s16 *)((char *)arg0 + 0xFC)) != 0) {
        return;
    }
    if (((s32 (*)(s32))func_8012BE54)((s32)arg0) <= 0x240000) {
        sp.u06 = *(u16 *)((char *)arg0 + 0x6);
        sp.u0A = *(u16 *)((char *)arg0 + 0xA);
        sp.u0E = *(u16 *)((char *)arg0 + 0xE);
        sp.unk16 = 0x1FB;
        sp.u70 = *(u16 *)((char *)arg0 + 0x70);
        sp.zero1A = 0;
        sp.unk1E = *(u16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC);
        sp.unk20 = *(s32 *)((char *)arg0 + 0xDC);
        sp.unk1C = 0x7FFF;
        func_8012C51C(&sp, (s32)arg0);
    }
}




extern void func_8012EFB8(s32 a0);
extern void func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80181DE4(s32 a0, s32 a1) {
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)
    SVec_80181CDC_80181DE4 pos;
    SVec_80181CDC_80181DE4 out;
    s32 val;
    s32 lvl;
    s32 t;
    s32 x;
    s32 n;
    s32 y;
    s32 arg;

    val = 0x7F;
    arg = a1;
    pos.vx = *(s16 *)(a0 + 0x6);
    pos.vy = *(s16 *)(a0 + 0xA);
    pos.vz = *(s16 *)(a0 + 0xE);
    ((void (*)(void *, void *))func_8012EFB8)(&pos, &out);
    lvl = 7;

    t = out.vx;
    if (t < 0) { t = -t; }
    if (t >= 0xC9) { return 0; }

    if (out.vy >= 0) {
        if (out.vy >= 0xA1) { return 0; }
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    } else {
        if (-out.vy >= 0xA1) { return 0; }
    }

    val -= ((((s32 (*)(s32))func_8012BD14)(a0) - 0x1000) * 0x7F) / 0xFF000;
    x = out.vx;
    n = lvl + x / 0x19;
    lvl = n + zr;
    if ((s16)n < 0) { lvl = 0; }
    else if ((s16)n > 0xF) { lvl = 0xF; }
    y = (lvl << 8) | 0x3000;
    func_8002D4C8(arg & 0xFFFF, (val | y) & 0xFFFF);
    return 1;
}


extern void (*D_801ABAB4[])(void);

void func_80181F48(void *a0) {
    D_801ABAB4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_80181FCC(s32 a0);
extern void func_80146CA0(void *a0);
void func_80181F84(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_80181FCC(a0);
    func_80146CA0((void *)a0);
}


extern u8 D_80062BF4[];
extern s32 D_800D5880;
extern s32 D_800D58AC;
extern void func_80019064(void *a0);
extern void func_80149020(s32 *a0);
extern void func_80147324(s32 a0);
extern int func_801511E0(int a0);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146CA0(void *a0);

void func_80181FCC(s32 a0)
{
    s32 s1;
    s32 s0;

    s1 = a0;
    func_80019064(D_80062BF4);
    func_80149020((s32 *)s1);
    func_80147324(0x451);
    func_801511E0(s1);
    if ((s16)func_80012A60(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12), *(s16 *)(s1 + 0xF4)) >= 0x401) {
        func_80154274((s32 *)s1, (s32)&D_800D5880);
    } else {
        func_80154274((s32 *)s1, (s32)&D_800D58AC);
    }
    s0 = 1;
    func_80154A74(s1, 0x16);
    func_80149020((s32 *)s1);
    func_80146994(0x42, s1, 0, 0);
    func_80146A6C(0x42, (void *)s1, 0x20, 0, 0, s0, 0);
    func_80146A6C(0x42, (void *)s1, 0, 0, 0x20, s0, 0);
    func_80146A6C(0x42, (void *)s1, -0x20, 0, 0, s0, 0);
    func_80146A6C(0x42, (void *)s1, 0, 0, -0x20, s0, 0);
    func_80146CA0((void *)s1);
}


extern void func_80149020(s32 *a0);
extern void func_80182194(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_80165718(s32 a0);
extern u8 D_800D46E4[];
extern M2C_UNK D_800D5880;

void func_80182120(s32 arg0)
{
    func_80149020(arg0);
    if (*(u16 *)((s32)arg0 + 0xB8) == 0x8000) {
        func_80182194(arg0);
        func_80159B3C(arg0);
        if (*(s32 *)((s32)arg0 + 0xB4) == (s32)&D_800D5880) {
            ((void (*)(s32, s32, s32))func_801542DC)(arg0, (s32)D_800D46E4, 0xE);
        }
        func_80165718(arg0);
    }
}


extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_80182194(s32 a0)
{
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



extern void (*D_801ABB1C[])(void);

void func_801821D4(void *a0) {
    D_801ABB1C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801823AC();
extern u8 D_801ABAC0[];
extern u8 D_801ABACC[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801465C0(void);
extern void func_80146C3C();

void func_80182210(s32 param_1)
{
    extern u8 D_801ABAC0[];
    extern u8 D_801ABACC[];
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    func_8001CC3C(iVar1, (s32)D_801ABAC0, 0x270, 0x100);
    *(u8 *)(iVar1 + 0x27) = 0x9B;
    *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
    if (*(s32 *)(param_1 + 0x2C) == 0) {
        *(u16 *)(iVar1 + 0x1A) = 0x3000;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
    }
    *(u8 *)(iVar1 + 0x25) = 0xC0;
    *(u8 *)(iVar1 + 0x26) = 0x40;
    *(u8 *)(iVar1 + 0x24) = 0x40;
    func_80128EA8(iVar1, param_1 + 0x24, (s32)D_801ABACC);
    *(s32 *)(param_1 + 0x14) = 0xfffc0000;
    func_801823AC(param_1);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();

void func_801822E8(void *a0)
{
    s32 self;
    s32 obj;

    obj = *(s32 *)(a0 + 0x20);
    if (func_80128ED8(obj, (s32 *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    } else {
        *(s32 *)(a0 + 0x14) += -0x8000;
        *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x14);
        *(u16 *)(obj + 0x18) += 0x500;
        if (*(s32 *)(a0 + 0x2C) == 0) {
            *(u16 *)(obj + 0x1A) += 0x300;
        } else {
            *(u16 *)(obj + 0x1A) += 0x600;
        }
        *(u8 *)(obj + 0x26) -= 4;
        *(u8 *)(obj + 0x24) = *(u8 *)(obj + 0x26);
        *(u8 *)(obj + 0x25) -= 8;
    }
}


s32 func_801823AC(s32 arg0)
{
    func_80149374(*(s32 *) (arg0 + 0x34), arg0 + 4);
    if (*(s32 *) (arg0 + 0x2C) == 0) {
        func_800D1FC8(arg0, 5);
    }
}





