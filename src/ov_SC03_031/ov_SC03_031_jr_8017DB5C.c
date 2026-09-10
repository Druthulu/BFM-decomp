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
extern u8 D_801848A0;
extern u8 D_80184810;
extern u8 D_801847EC;
extern u8 D_801847C8;
extern u8 D_8018487C;
extern u8 D_80184858;
extern u8 D_80184834;
extern u8 D_801847A4;
extern void func_80145934(void);
extern u8 D_80184930;
extern u8 D_8018490C;
extern u8 D_801848E8;
extern u8 D_801848C4;
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
extern unsigned char D_80183D28[];
extern unsigned char D_80183D58[];
extern unsigned char D_80183DA8[];
extern unsigned char D_80183DD8[];
extern unsigned char D_80183E08[];
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
extern void (*D_80183E58[])(void *);
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
extern s32 D_80183F20[];
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
extern u8 D_80183FA8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80183FB0;
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
extern int D_801C4D10;
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
extern s32 D_801C4D14;
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
extern s32 D_80183FE0;
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
extern void (*D_80184088[])(void);
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
extern void (*D_801840AC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018409C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801840C0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801840CC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801840DC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801840F4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801840E4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80184108[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80184124[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80184114;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80184138[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018414C[])(void);
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
extern s32 D_80184160;
extern void (*D_80184188[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80184168;
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
extern int (*D_801841D4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801841D8[])(void);
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
extern unsigned short D_8018463C[];
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
extern void (*D_8018464C[])(void);
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
extern int D_801C4D48;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80184674[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80184654;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80184664;
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
extern void (*D_801846B4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801846BC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80184688;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801846C8[])(void);
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
extern u8 D_80184698;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C4D50;
extern s32 D_801C4D5C;
extern s32 D_801C4D60;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80184704[])(s32 *);
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
extern s32 D_801846D8[];
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
extern s32 D_801C4D58;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80184954[])(void);
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
extern char D_80184774[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801849F8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80184B4C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80184968;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80184B54[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80184978;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80184998;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80184B5C[])(void);
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
extern void (*D_80184B84[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80184B90[])(void);
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
extern void (*D_80184A04[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80184C34;
extern void func_8015D380(s32 a0);
extern unsigned char D_80183D18[];
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
extern unsigned char D_80184C48[];
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
extern s8 D_80184C84[];
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
extern u16 D_80184CCC;
extern u16 D_80184CCE;
extern u16 D_80184CD0;
extern s32 D_80184CD4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80184CDC;
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
extern int D_801849E8;
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
extern unsigned int D_80184D60[];
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
extern void (*D_80184E10[])(void);
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
extern u16 D_80184E40[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80184EA4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C4D68[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80184EC8[])(void);
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
extern int D_801C4DC0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80184F10[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80184F00;
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
extern char D_801C4620[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80184F18[])(void);
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
extern void (*D_80184F6C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80184F34;
extern s16 D_80184F68;
extern s16 D_80184F66;
extern s16 D_80184F64;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80184F78[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C4E20;
extern u8 D_801C4E21;
extern u8 D_801C4E22;
extern u8 D_801C4E23;
extern u8 D_801C4E24;
extern u8 D_801C4E25;
extern u8 D_801C4E26;
extern u8 D_801C4E27;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80184F88[])(void);
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
extern s32 D_801C4E60;
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
extern void (*D_80184FCC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80185048[];
extern s32 D_80185068[];
extern u8 D_801850E4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80185104[];
extern u8 D_80185124[];
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
extern void (*D_801851C0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018523C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C4630;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80185248[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80185250[])(void);
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
extern void (*D_80185318[])(void);
extern void func_80166618(void *a0);
extern void (*D_80185328[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80185338[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80185344[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_801852A4[];
extern u8   D_801852B8[];
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
extern void (*D_8018535C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80185364[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018536C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80185374[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018537C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80185384[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018538C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80185440[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80185448[])(void);
extern void func_80169F00(void *a0);
extern char D_801853F8[];
extern char D_801853B8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80185480[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018548C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801854D4[])(void);
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
extern void (*D_80185550[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C5180;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80185544[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80185588[];
extern unsigned short D_80185590[];
extern unsigned short D_80185598[];
extern unsigned char D_801C5188[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C5180;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_801855A0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C52BC;
extern M2C_UNK D_801C52C0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C5248;
extern void (*D_801855D0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C52C4[];
extern u8 D_801C52CC[];
extern u8 D_801C527C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801855D8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801855F4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801855FC[])(void);
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
extern void (*D_80185664[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80185608;
extern u8 D_80185614;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80185698[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_801856A0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801856F4[])(void);
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
extern u16 D_80185728[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80185718[];
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
extern s32 D_80185744;
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
extern void (*D_801857BC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_801857C4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_801857CC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801857D4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801857DC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801857E4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801857F0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801857FC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80185808[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80185818[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80185828[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80185830[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80185838[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80185840[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80185848[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80185850[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80185858[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80185860[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80185868[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80185870[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80185878[])(void);
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
extern void (*D_80185880[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80185888[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80185890[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80185898[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_801858A0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_801858A8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_801858B0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_801858B8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_801858C0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_801858C8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_801858D0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_801858D8[])(void);
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
extern void (*D_8018591C[])(void);
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
extern M2C_UNK D_801858E0;
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
extern void (*D_8018594C[])(void);
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
extern void (*D_80185988[])(void);
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
extern void (*D_801859E0[])();
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
extern void (*D_801859F0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801859F8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80185B60[])();
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
extern void (*D_80185B6C[])();
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
extern M2C_UNK D_801C4878;
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
extern s16 D_801C6230;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C5A00;
extern short D_801C62A4;
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
extern s32 D_801C5E2C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C5E54;
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
extern s16 D_801C5E10;
extern s32 func_8017A3B0(void);
extern short D_801C5E4C;
extern short D_801C5E48;
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
extern s16 D_801C5E14;
extern u16 D_801C5E94;
extern u16 D_801C5E96;
extern u16 D_801C5E98;
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
extern s16 D_801C5E8C;
extern s16 D_801C5E8E;
extern s16 D_801C5E90;
extern s16 D_801C5E84;
extern s16 D_801C5E86;
extern s16 D_801C5E88;
extern void func_8017B7A8(void);
extern s16 D_801C5EA4;
extern s16 D_801C5EA6;
extern s16 D_801C5EA8;
extern s16 D_801C5EAC;
extern s16 D_801C5EAE;
extern s16 D_801C5EB0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C5E9C;
extern short D_801C5E9E;
extern short D_801C5EA0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C5E34;
extern SV4 D_801C5E3C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C5E5C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C5E58)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80185D48[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80185D60[])(void);
extern void func_8017C0E4(void *a0);
extern void (*D_80185E78[])(void);
extern void func_8017CB7C(void *a0);
extern void (*D_80185ED0[])(void);
extern void func_8017CFD4(void *a0);
extern void (*D_80185EE4[])(void);
extern void func_8017D600(void *a0);
extern void (*D_80185EF8[])(void);
extern void func_8017D8A0(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017DB5C — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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
















void func_8017DB5C(s32 arg0)
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
        __asm__ volatile ("");   /* §45-B live-length slider: +1 static insn splits the 228/230 allocno-priority tie (498/498 -> 497/498) */  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus8)
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
                                    gte_stsxy3_f3(pkt);
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



extern void (*D_80185F78[])(void);

void func_8017EA3C(void *a0) {
    D_80185F78[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017ECC8(void);
extern void func_800167B8(s32 a0);

s32 func_8017EA78(s32 a0) {
    func_8017ECC8();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017EABC(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_80185F80[])(void);

void func_8017EAE0(void *a0) {
    D_80185F80[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017ECF0(void);

s32 func_8017EB1C(s32 a0) {
    func_8017ECF0();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern s32 func_80029504(void);
extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017EB5C(s32 a0) {
    s32 v = func_80029504();
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        if (v < 200 && (u32)(v - 150) < 50) {
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
    void func_8017EBF8(void) {
        func_800D1EBC();
    }



extern void (*D_80185F8C[])(void);

void func_8017EC18(void *a0) {
    D_80185F8C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017EC54(s32 a0) {
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
void func_8017ECC8(void) {

    extern s32 D_80185F98(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185F98, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017ECF0(void) {

    extern s32 D_80185FA4(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185FA4, 0x1000000);
}


extern s32 D_80126954;
extern s32 D_80126950;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern u8 D_80126948[];
extern void func_8017EDBC(void *a0);

void func_8017ED18(void) {
    D_80126954 = 0x12C;
    D_80126950 = 0x12C;
    D_8012695C = 0x4B0;
    D_80126968 = 0x2AA;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0x100;
    func_8012A018((s32) func_8017EDBC, 0);
    func_8012A094((s32) D_80126948);
    func_8017EDBC((void *) D_80126948);
}



extern void (*D_80185FB8[])(void);

void func_8017EDBC(void *a0) {
    D_80185FB8[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

extern s16 D_80126940;
extern u16 D_80126942;
extern s16 D_80126944;
extern void func_8017EE98(s32 param_1, s16 *param_2);

void func_8017EDF8(s32 param_1) {
    s16 buf[3];
    s16 x;
    s16 y;
    s16 z;

    x = D_80126940;
    if (x < -0xA0) {
        buf[0] = -0xA0;
    } else if (x > 0xA00) {
        buf[0] = 0xA00;
    } else {
        buf[0] = x;
    }

    z = D_80126944;
    if (z < -0x8B0) {
        buf[2] = -0x8B0;
    } else if (z > 0x800) {
        buf[2] = 0x800;
    } else {
        buf[2] = z;
    }

    y = D_80126942;
    buf[1] = y;

    func_8017EE98(param_1, buf);
}



/* Local address-suffixed clones of the PSX MATRIX/SVECTOR layouts (cookbook: match_one's isolated
 * compile only has -Iinclude, so "../shared/engine_core.h" can't resolve from its scratch dir --
 * the host TU (src/ov_SC02_015/ov_SC02_015_jr_8017AE2C.c) already includes engine_core.h and
 * therefore already has the real MATRIX/SVECTOR in scope; these local names exist ONLY to let this
 * file compile standalone under match_one and carry zero risk of colliding with the host's globals
 * at integration time). Layout: m[3][3] (18B) + 2B pad + t[3] s32 (12B) = 0x20; vx/vy/vz/pad s16 = 8B. */
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_8017D5C8_8017EE98;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_8017D5C8_8017EE98;

extern u16 func_80148800(s32 *a0);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017EE98(s32 param_1, s16 *param_2) {

    extern s16 D_80185FBC[];
    MATRIX_8017D5C8_8017EE98 m1;
    SVECTOR_8017D5C8_8017EE98 svec_in;
    SVECTOR_8017D5C8_8017EE98 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0x14) = D_80185FBC[t];
    }

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



extern void (*D_80186150[])(void);

void func_8017F074(void *a0) {
    D_80186150[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017F0B0(s32 param_1) {
    extern u8 D_80186000[];
    extern void (*D_801860AC[])(void);
    extern u16 D_801860C4[];
    extern u8 D_80182694[];
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern s32 func_80029178(s32 arg);
    extern void func_8012A828(s32*, s32);
    extern void func_8012B2CC(s32 a0);
    s32 idx;
    s32 v;

    if (func_8012C354(param_1, (s32)&D_80186000[(*(u16 *)(param_1 + 0x70) & 0xF) * 0x34]) == 0) {
        return;
    }
    idx = *(u16 *)(param_1 + 0x70) >> 12;
    if ((u8)func_80029178((s32)D_801860AC[idx]) == 0) {
        v = 1;
    } else if (idx == 5) {
        v = 7;
    } else {
        u16 *base = D_801860C4;
        *(s16 *)(param_1 + 2) = 8;
        *(s16 *)(param_1 + 6) = base[idx * 4];
        *(s16 *)(param_1 + 10) = base[idx * 4 + 1];
        *(s16 *)(param_1 + 14) = base[idx * 4 + 2];
        goto end;
    }
    *(s16 *)(param_1 + 2) = v;
end:
    *(u8 *)(param_1 + 0x75) = 1;
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)param_1, (s32)D_80182694);
    func_8012B2CC(param_1);
}


extern s32 func_8012E778(s32 a0, s32 a1);

void func_8017F1B4(s32 param_1) {
    s32 mask;

    if (func_8012E778(param_1, 0x8200AA) != 1) {
        return;
    }
    mask = func_8014CB2C() & 0x7FFFFFFF;
    if (mask != 2) {
        return;
    }
    if ((*(u16 *)(param_1 + 0x70) & 0xF) == mask) {
        *(u16 *)(param_1 + 2) = 6;
        *(s32 *)(param_1 + 0x1C) = 3;
    } else {
        *(u16 *)(param_1 + 2) = 2;
    }
}


extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017F23C(void *a0) {
    *(u16 *)((s32)a0 + 0x2) = 3;
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFFE0000);
    *(s32 *)((s32)a0 + 0x1C) = 0x41;
    func_8002D4C8(0x5C2, 0);
}


extern void func_8012AD80(s32);
extern s32 func_8012BEE8(s32);
extern void func_8017BEBC(s32 a0, s16 *a1, s16 a2);
extern void func_8013C9C4(void *a0);
extern s8 D_80186174[];
extern u8 D_80186114[];

void func_8017F28C(void *arg0)
{
    u8 *s0 = arg0;
    s32 v1;
    s16 *s2;
    s32 i;

    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x10) += 0x10;

    func_8012AD80((s32) s0);

    if (func_8012BEE8((s32) s0) != 0) {
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x10) = 0x400;
        *(u16 *)(s0 + 2) = 4;
        s2 = (s16 *)(D_80186174 + ((*(u16 *)(s0 + 0x70) & 0xF) << 3));
        for (i = 0; i < 5; i++) {
            func_8017BEBC((s32) s0, s2, 0);
        }
    }

    if (*(s32 *)(s0 + 0x1C) == 0x38) {
        func_8013C9C4(D_80186114);
    }
}


extern void func_8012B200(u8 *a0);
    extern s32 func_8017F860(void *a0);
    void func_8017F35C(u8 *a0) {
        *(s16 *)(a0 + 0x2) = 0x5;
        ((void (*)(s32 *))func_8012B200)((s32 *)a0);
        func_8017F860(a0);
    }


void func_8017F394(void *a0) {
    extern s32 func_8012CC40(s32, s32);
    extern void func_8013C9C4(void *);
    extern void func_80029124(s32, s32);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern u8 D_80186100[];
    extern u8 D_8018609C[];
    extern u8 D_801860AC[];

    s32 s0 = (s32)a0;
    s32 ret;
    s32 pad[2];

    ret = func_8012CC40((s32)a0, ((*(u16 *)(s0 + 0x70) & 0xF) << 3) + (s32)D_8018609C);
    if (ret & 0x2000) {
        *(u16 *)(s0 + 2) = 8;
        *(s32 *)(s0 + 0x1C) = 3;
        func_8013C9C4(D_80186100);
        func_80029124(*(u32 *)((char *)D_801860AC + ((*(u16 *)(s0 + 0x70) >> 12) << 2)), 1);
        func_8002D4C8(0x5C3, 0);
    }
}


typedef struct { s16 x, y, z, p; } V3_F428;

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32, s32, s32, s32, s32, s32);
extern void func_8012F214(s32, s32, s32);
extern void func_8002D4C8(s32, s32);
extern void func_8017F95C(s32);
extern void func_8012B260(s32);
extern void func_80029124(s32, s32);
extern u8 *func_801290DC(s32, u8 *);
extern s32 rand(void);

void func_8017F428(s32 self) {

    extern u8 D_80186184[];
    extern u8 D_80185FF0[];
    extern s32 D_801860F4;
    extern void (*D_801860AC[])(void);
    V3_F428 sp18;
    V3_F428 sp20;
    s32 *temp;
    s32 w;
    s32 b;
    s32 b2;
    s32 d;
    s32 d2;
    s32 v;
    s32 i;

    *(s32 *)(self + 0xDC) += 0x40000;
    temp = *(s32 **)(self + 0x20);
    w = *(u16 *)(temp + 4) + *(u16 *)(self + 0xDE);
    *(u16 *)(temp + 4) = w;
    if ((s16)w >= 0x500) {
        *(u16 *)&sp18.x = D_80126B5E;
        *(u16 *)&sp18.y = D_80126B62;
        *(u16 *)&sp18.z = D_80126B66;
        sp20 = sp18;
        sp20.y -= 0x50;
        if (func_80135888(*(s32 **)(self + 0x20), *(s32 *)(self + 0x58), (s32)&sp18, (s32)&sp20) != 0) {
            func_8012F568(1, 0x4002, 0, 0xA, (s32)&sp20, (s32)D_801152A8);
        }
        *(u16 *)(temp + 4) = 0x500;
        *(s32 *)(self + 0xDC) = -(*(s32 *)(self + 0xDC) >> 2);
        func_8012F214(self, (s32)D_80186184, (s32)&sp18);
        sp20 = sp18;
        for (i = 0; i < 5; i++) {
            d = rand() % 96;
            b = sp18.x;
            sp20.x = (rand() & 1) ? b + d : b - d;
            d2 = rand() % 5;
            b2 = sp18.z;
            sp20.z = (rand() & 1) ? b2 + d2 : b2 - d2;
            func_801290DC(0x31, (u8 *)&sp20);
        }
        func_8002D4C8(0x651, 0);
        v = *(s32 *)(self + 0x1C) - 1;
        *(s32 *)(self + 0x1C) = v;
        if (v == 0) {
            *(u16 *)(self + 2) = 8;
            *(s32 *)(self + 0x58) = (s32)&(*(char *)D_80185FF0) | 0x40000000 | 0x20000000;
            *(s32 *)(*(s32 *)(self + 0x20) + 0x20) = (s32)&(*(char *)&D_801860F4);
            func_8017F95C(self);
            func_8012B260(self);
            func_80029124((s32)D_801860AC[*(u16 *)(self + 0x70) >> 12], 1);
        }
    }
}


#include "common.h"

extern void func_8017F95C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern u8 D_80185FF0[];
extern s32 D_801860F4;

void func_8017F6B8(s32 a0) {
    *(s16 *)(a0 + 0x2) = 8;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0x500;
    *(s32 *)(a0 + 0x58) = (s32)D_80185FF0 | 0x40000000 | 0x20000000;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)&D_801860F4;
    func_8017F95C(a0);
    func_8012B2CC(a0);
}


extern u8 * func_801290DC(s32 a0, u8 *a1);
extern u16 D_8018609E[][4];
extern s32 rand(void);

void func_8017F728(void *a0) {
    s16 v[3];
    s32 i;
    s32 b1, b2;
    s32 r1, r2;
    s32 t;

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        v[1] = *(u16 *)((s32)a0 + 0xA) + D_8018609E[*(u16 *)((s32)a0 + 0x70) & 0xF][0];
        for (i = 0; i < 10; i++) {
            r1 = rand() % 160;
            b1 = *(s16 *)((s32)a0 + 6);
            if (rand() & 1)
                t = b1 + r1;
            else
                t = b1 - r1;
            v[0] = t;
            r2 = rand() % 160;
            b2 = *(s16 *)((s32)a0 + 0xE);
            if (rand() & 1)
                t = b2 + r2;
            else
                t = b2 - r2;
            v[2] = t;
            func_801290DC(0x31, v);
        }
        (*(s32 *)((s32)a0 + 0x1C))--;
    }
}



extern u16 D_801860C4[];
extern s32 D_800AE620[];

s32 func_8017F860(void* a0)
{
    Mat32 mat;
    s16 vec[4];
    s32 rot[4];
    s16 in[8];
    s32 ang;
    u16 *base;
    s32 idx;
    s32 t;

    base = D_801860C4;
    idx = *(u16 *)(a0 + 0x70) >> 12;
    in[1] = base[idx * 4 + 0];
    in[3] = base[idx * 4 + 1];
    in[5] = base[idx * 4 + 2];
    func_8012B77C((s32)&ang, (s32)(a0 + 4), (s32)in);
    t = ang;
    mat = *(Mat32 *)&D_800AE620;
    vec[2] = 0;
    vec[0] = t;
    vec[1] = t >> 16;
    func_80049CAC((s32)vec, (s32)&mat);
    rot[1] = 0;
    rot[0] = 0;
    rot[2] = 0xFFFE8000;
    func_800484EC((s32)&mat, (s32)rot, (s32)(a0 + 0x44));
}




extern s32 RotMatrixX(s32 a0, void *a1);
extern s32 D_800AE620[];
extern s32 D_8018618C;

void func_8017F95C(s32 a0) {
    Mat32 mat;
    u16 buf[3];

    mat = *(Mat32 *)&D_800AE620;
    RotMatrixX(-0x300, &mat);
    __asm__ __volatile__(  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lw $12, 0(%0)\n"
        "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n"
        "lw $13, 12(%0)\n"
        "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        :
        : "r"(&mat)
        : "$12", "$13", "$14", "memory"
    );  // !FAKE: gte direct — clobbers ['memory'] (gte_SetRotMatrix_m) beyond Sony's (P36 T5 gte1)
    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 0, 3, 0\n"
        :
        : "r"(&D_8018618C)
        : "memory"
    );
    gte_stsv(buf);

    *(u16 *)(a0 + 6)  += buf[0];
    *(u16 *)(a0 + 0xA) += buf[1];
    *(u16 *)(a0 + 0xE) += buf[2];
}



extern void (*D_801861E0[])(void);

void func_8017FA7C(void *a0) {
    D_801861E0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80186194;
extern s32 D_801861A0;

void func_8017FAB8(void *a0) {
    s32 s0;
    s32 r;
    s32 t;

    s0 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)((s32)s0 + 0x28) = 0x340;
    *(s16 *)((s32)s0 + 0x2A) = 0x100;
    *(s32 *)((s32)s0 + 0x20) = (s32)&D_80186194;
    *(u8 *)((s32)s0 + 0x27) = 0x65;
    *(s32 *)((s32)s0 + 4) |= 0x70000000;
    if (*(s32 *)((s32)a0 + 0x2C) == 0) {
        t = 0x3000;
    } else {
        r = rand();
        t = (r % 4 + 2) * 0x1000;
    }
    *(s16 *)((s32)s0 + 0x1A) = t;
    *(s16 *)((s32)s0 + 0x18) = t;
    *(s16 *)((s32)s0 + 0x10) = 0x400;
    func_80128EA8((s32)s0, (s32)((s32)a0 + 0x24), (s32)&D_801861A0);
    *(s16 *)((s32)a0 + 2) = 1;
}


extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_8017FB84(void *a0) {
    s32 v0;

    v0 = *(s32 *)((s32)a0 + 0x1C);
    if (v0 == 0) {
        func_8012931C((struct vec *)a0);
        v0 = func_80128ED8(*(s32 *)((s32)a0 + 0x20), (s32 *)((s32)a0 + 0x24));
        if (v0 != 0) {
            func_801292C8((u8 *)a0);
        }
    } else {
        *(s32 *)((s32)a0 + 0x1C) = v0 - 1;
    }
}



extern void (*D_80186298[])(void);

void func_8017FBE8(void *a0) {
    D_80186298[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32*, s32);
extern u8 D_80186218[];

void func_8017FC24(void *a0) {
    extern u8 D_80182694[];
    s32 v0;
    s32 ptr;

    ptr = (s32)&D_80186218[(*(u16 *)((s32)a0 + 0x70) & 1) * 0x34];
    *(s32 *)((s32)a0 + 0x78) = ptr;
    *(u16 *)((s32)a0 + 0x5C) = *(u16 *)(ptr + 2);
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C810(v0, *(s32 *)(ptr + 4));
        *(s32 *)((s32)a0 + 0x58) = *(s32 *)(ptr + 8) | 0x50000000;
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) |= 0x8040;
        *(u8 *)((s32)a0 + 0x75) = 1;
        func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x280, 0x1E0);
        *(u16 *)((s32)a0 + 2) = 1;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)D_80182694);
    }
}


extern void (*D_80186280[])(void);
extern void (*D_80186208[])(void);
void func_8017FD00(int param_1)
{
  short v1 = *(short *)(param_1 + 0xfc);
  if (v1 == 1) {
    *(short *)(param_1 + 2) = 2;
    *(short *)(param_1 + 0x5c) = 0;
  } else if (v1 == 2) {
    *(short *)(param_1 + 2) = 4;
    func_8012B14C(param_1, (u32)(*(u16 *)(param_1 + 0x70) & 1) * 12 + (u32)&D_80186280);
    *(int *)(param_1 + 4) += *(int *)(param_1 + 0x10) * 0x40;
    *(int *)(param_1 + 8) += *(int *)(param_1 + 0x14) * 0x40;
    *(int *)(param_1 + 0xc) += *(int *)(param_1 + 0x18) * 0x40;
    if (*(short *)(param_1 + 0x70) == 0) {
      *(short *)(param_1 + 0x5c) = 0x800;
      *(u32 *)(param_1 + 0x58) = (u32)&D_80186208 | 0x40000000 | 0x10000000;
    } else {
      *(short *)(param_1 + 0x5c) = 0;
    }
  }
}


#include "common.h"

extern void func_8012B200(u8 *a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void (*D_80186280[])(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FDE4(void *a0) {
    s32 s0 = (s32)a0;

    *(u16 *)((s32)a0 + 0x2) = 3;
    func_8012B200(a0);
    func_8012B14C(s0, (s32)&D_80186280[(*(u16 *)((s32)a0 + 0x70) & 1) * 3]);
    *(s32 *)((s32)a0 + 0x1C) = 0x40;
    *(u16 *)((s32)a0 + 0x34) = 0;
    func_8002D4C8(0x5C4, 0);
}


extern void func_8012AD80(s32);
extern s32 func_8012BEE8(s32);
extern u8 *func_801290DC(s32, u8 *);

void func_8017FE54(void *arg)
{
    u8 *s1 = arg;

    func_8012AD80((s32) s1);
    if (func_8012BEE8((s32) s1)) {
        *(u16 *)(s1 + 2) = 4;
    }
    if (*(s32 *)(s1 + 0x1C) & 7) {
        return;
    }
    {
        s32 v = *(s16 *)(s1 + 6);
        s16 buf[3];
        s32 s0;
        s32 one;
        u8 *r;
        buf[0] = (*(u16 *)(s1 + 0x70) & 1) ? v + 0x80 : v - 0x80;
        s0 = -0x280;
        buf[1] = -0x202;
        buf[2] = *(u16 *)(s1 + 0xE);
        one = 1;
        do {
            r = func_801290DC(0x31, (u8 *) buf);
            if (r) {
                *(s32 *)(r + 0x2C) = one;
                *(u16 *)(r + 0xE) += s0;
            }
            s0 += 0x80;
        } while (s0 < 0x300);
    }
}


void func_8017FF18(void) {
}

extern u8 D_801202A0[];
extern void func_8013C9C4(void *a0);
extern u8 D_801862AC[];

void func_8017FF20(void *a0) {
    u8 *p = D_801202A0;
    s32 i;

    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0xE5) {
            *(s16 *)((s32)p + 0xFC) = (s32)a0 + 1;
        }
        p += 0x10C;
    }

    if (a0 == NULL) {
        func_8013C9C4(&D_801862AC);
    }
}



extern void (*D_80186434[])(void);

void func_8017FF88(void *a0) {
    D_80186434[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_80186498[])(void);

void func_8017FFC4(void *a0) {
    (*(u16 *)((s32)a0 + 0xFC))++;
    D_80186498[*(u16 *)((s32)a0 + 2)]();
}


extern void (*D_801864FC[])(void);

void func_80180008(void *a0) {
    *(u16 *)((s32)a0 + 0xFC) = *(u16 *)((s32)a0 + 0xFC) + 1;
    D_801864FC[*(u16 *)((s32)a0 + 2)]();
}


extern void (*D_80186560[])(void);

void func_8018004C(void *a0) {
    *(u16 *)((s32)a0 + 0xFC) = *(u16 *)((s32)a0 + 0xFC) + 1;
    D_80186560[*(u16 *)((s32)a0 + 2)]();
}


extern void (*D_801865C4[])(void);

void func_80180090(a0)
void *a0;
{
    (*(u16 *)((s32)a0 + 0xFC))++;
    D_801865C4[*(u16 *)((s32)a0 + 2)]();
}



extern void (*D_80186618[])(void);

void func_801800D4(void *a0) {
    D_80186618[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180110(void *a0) {
        *(short *)((char *)a0 + 0x2) = 1;
    }


extern s32 func_80029504(void);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8017FF20(void *a0);
extern void func_8012C218(void *a0);

extern u8 D_801862FC[];
extern u8 D_80186310[];
extern u8 D_80186324;
extern u8 D_80186338;

void func_8018011C(void *a0) {
    s32 v;

    v = func_80029504();
    if (v == 0x96) {
        func_8012C51C(D_801862FC, (s32)a0);
        func_8012C51C(&D_80186310, (s32)a0);
        func_8012C51C(&D_80186324, (s32)a0);
        func_8012C51C(&D_80186338, (s32)a0);
        *(u16 *)((s32)a0 + 2) = 2;
    } else {
        v = func_80029504();
        if ((u32)v >= 0xA0) {
            func_8017FF20((void *)1);
        }
        func_8012C218(a0);
    }
}


extern u16 D_80126B66;
extern u8 D_8018634C;
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_801746DC(void);

void func_801801C0(s32 param_1)
{
    if ((*(s16 *)&D_80126B66) >= 0x800) {
        *(s16 *)(param_1 + 2) = 3;
        func_80178B18(param_1, (s32)&D_8018634C);
        func_801746DC();
    }
}


extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern void func_80029514(s32);
extern void func_8012C218(void *a0);

void func_80180204(void *arg0) {
    switch (*(s32 *)((s32)arg0 + 0xF8)) {
    case 1:
        *(s32 *)((s32)arg0 + 0xDC) ^= 1;
        break;
    case 2:
        *(s32 *)((s32)arg0 + 0xE0) ^= 1;
        break;
    case 3:
        *(s32 *)((s32)arg0 + 0xE4) ^= 1;
        break;
    case 4:
        *(s32 *)((s32)arg0 + 0xE8) ^= 1;
        break;
    case 5:
        *(s32 *)((s32)arg0 + 0xDC) = 2;
        *(s32 *)((s32)arg0 + 0xE0) = 2;
        *(s32 *)((s32)arg0 + 0xE4) = 2;
        *(s32 *)((s32)arg0 + 0xE8) = 2;
        break;
    }
    *(s32 *)((s32)arg0 + 0xF8) = 0;

    if (func_801789AC((s32)arg0) == 1) {
        func_80029514(0xA0);
        ((void (*)(void *))func_80178D18)(arg0);
        func_8012C218(arg0);
    }
}


extern u8 D_80186444;
extern u8 D_80186450;
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_801802E4(a0)
void *a0;
{
    void *s0;
    s32 v0;
    s32 v1;

    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        extern u8 D_80186444;
        extern u8 D_80186450;
        v1 = 0x4000;

        func_8001CA1C(v0, (s32)&D_80186444);
        func_8012A828((s32 *)s0, (s32)&D_80186450);
        *(s16 *)((s32)s0 + 2) = 1;
        *(u8 *)((s32)s0 + 0xC0) = 1;
        *(u8 *)((s32)s0 + 0xC1) = 0;
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) = v1;
        do { *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) = v1; } while (0);
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1C) = v1;
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)(*(s32 *)((s32)s0 + 0x20) + 4) = (s32)(0x1000000 >> 16) << 16;
        *(s32 *)((s32)s0 + 0x1C) = 0x20;
        *(s16 *)((s32)s0 + 0xFC) = 0;
    }
}


extern void (*D_80186460[])(void);
extern void func_800183E0(s32 a0);

void func_801803AC(param_1)
s32 param_1;
{
    u16 idx;

    idx = (*(u16 *)(param_1 + 0xFC) >> 1) % 6;
    func_800183E0((s32)D_80186460[idx]);

    *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 6) + -8;
    if (--*(s32 *)(param_1 + 0x1C) == 0) {
        *(u16 *)(param_1 + 2) = 2;
    }
}


extern void func_800183E0(s32 a0);
extern void (*D_80186478[])(void *);
extern s32 D_801A46CC;

void func_8018043C(void *a0)
{
    s32 v1;
    u16 h;

    v1 = *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xDC);
    switch (v1) {
    case 0:
        func_800183E0((s32)&D_801A46CC);
        break;
    case 1:
        h = *(u16 *)((u8 *)a0 + 0xFC);
        func_800183E0(*(s32 *)((u8 *)D_80186478 + ((h << 1) & 0x1C)));
        break;
    case 2:
        *(u16 *)((u8 *)a0 + 2) = 3;
        *(u16 *)((u8 *)a0 + 0xFC) = 0;
        *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xDC) = 0;
        break;
    }
}


#include "common.h"

extern void func_800183E0(s32 a0);
extern void (*D_80186478[])(void *);
extern s32 func_8004787C(s32 a0);
extern void func_8017FF20(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801804EC(void *a0)
{
    u16 h;

    func_800183E0(*(s32 *)((u8 *)D_80186478 + ((*(u16 *)((u8 *)a0 + 0xFC) << 1) & 0x1C)));
    h = *(u16 *)((u8 *)a0 + 0xFE) + 0x40;
    *(u16 *)((u8 *)a0 + 0xFE) = h;
    if ((s16)h >= 0x201 || (s16)h < 0x600) {
        *(u16 *)((u8 *)a0 + 0xFC) = 8;
    }
    *(u16 *)((u8 *)a0 + 6) = *(u16 *)((u8 *)a0 + 6) - 2;
    *(s16 *)((u8 *)a0 + 0xA) = -0x32B - ((func_8004787C(*(s16 *)((u8 *)a0 + 0xFE)) << 6) >> 12);
    if (*(s16 *)((u8 *)a0 + 0xFE) == 0x800) {
        *(u16 *)((u8 *)a0 + 2) = 2;
        func_8017FF20((void *)0);
        func_8002D4C8(0x63F, 0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 *a0, s32 a1);

void func_801805B8(void *a0)
{
    void *s0;
    s32 v0;
    s32 v1;


    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        extern u8 D_801864A8;
        extern u8 D_801864B4;
        v1 = 0x4000;

        func_8001CA1C(v0, (s32)&D_801864A8);
        func_8012A828((s32 *)a0, (s32)&D_801864B4);
        *(s16 *)((s32)a0 + 2) = 1;
        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = v1;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = v1;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = v1;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) = (s32)(0x1000000 >> 16) << 16;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }
}


extern void (*D_801864C4[])(void);
extern void func_800183E0(s32 a0);

void func_80180680(param_1)
s32 param_1;
{
    u16 idx;

    idx = (*(u16 *)(param_1 + 0xFC) >> 1) % 6;
    func_800183E0((s32)D_801864C4[idx]);

    *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 6) + -8;
    if (--*(s32 *)(param_1 + 0x1C) == 0) {
        *(u16 *)(param_1 + 2) = 2;
    }
}


extern s32 D_801AA18C;
extern void (*D_801864DC[])(void *);
extern void func_800183E0(s32 a0);

void func_80180710(a0)
void *a0;
{
    s32 v1;
    u16 h;

    v1 = *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE0);
    switch (v1) {
    case 0:
        func_800183E0((s32)&D_801AA18C);
        break;
    case 1:
        h = *(u16 *)((u8 *)a0 + 0xFC);
        func_800183E0(*(s32 *)((u8 *)D_801864DC + ((h << 1) & 0x1C)));
        break;
    case 2:
        *(u16 *)((u8 *)a0 + 2) = 3;
        *(u16 *)((u8 *)a0 + 0xFC) = 0;
        *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE0) = 0;
        break;
    }
}


extern void func_800183E0(s32 a0);
extern void (*D_801864DC[])(void *);
extern s32 func_8004787C(s32 a0);

void func_801807C0(void *a0)
{
    u16 h;

    func_800183E0(*(s32 *)((u8 *)D_801864DC + ((*(u16 *)((u8 *)a0 + 0xFC) << 1) & 0x1C)));
    h = *(u16 *)((u8 *)a0 + 0xFE) + 0x40;
    *(u16 *)((u8 *)a0 + 0xFE) = h;
    if ((s16)h >= 0x201 || (s16)h < 0x600) {
        *(u16 *)((u8 *)a0 + 0xFC) = 8;
    }
    *(u16 *)((u8 *)a0 + 6) = *(u16 *)((u8 *)a0 + 6) - 2;
    *(s16 *)((u8 *)a0 + 0xA) = -0x32B - ((func_8004787C(*(s16 *)((u8 *)a0 + 0xFE)) << 6) >> 12);
    if (*(s16 *)((u8 *)a0 + 0xFE) == 0x800) {
        *(u16 *)((u8 *)a0 + 2) = 2;
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 *a0, s32 a1);

void func_80180878(void *a0)
{
    void *s0;
    s32 v0;
    s32 v1;


    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        extern u8 D_8018650C;
        extern u8 D_80186518;
        v1 = 0x4000;

        func_8001CA1C(v0, (s32)&D_8018650C);
        func_8012A828((s32 *)a0, (s32)&D_80186518);
        *(s16 *)((s32)a0 + 2) = 1;
        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = v1;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = v1;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = v1;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) = (s32)(0x1000000 >> 16) << 16;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }
}


extern void (*D_80186528[])(void);
extern void func_800183E0(s32 a0);

void func_80180940(param_1)
s32 param_1;
{
    u16 idx;

    idx = (*(u16 *)(param_1 + 0xFC) >> 1) % 6;
    func_800183E0((s32)D_80186528[idx]);

    *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 6) + 8;
    if (--*(s32 *)(param_1 + 0x1C) == 0) {
        *(u16 *)(param_1 + 2) = 2;
    }
}


extern s32 D_801AFC4C;
extern void (*D_80186540[])(void *);
extern void func_800183E0(s32 a0);

void func_801809D0(a0)
void *a0;
{
    s32 v1;
    u16 h;

    v1 = *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE4);
    switch (v1) {
    case 0:
        func_800183E0((s32)&D_801AFC4C);
        break;
    case 1:
        h = *(u16 *)((u8 *)a0 + 0xFC);
        func_800183E0(*(s32 *)((u8 *)D_80186540 + ((h << 1) & 0x1C)));
        break;
    case 2:
        *(u16 *)((u8 *)a0 + 2) = 3;
        *(u16 *)((u8 *)a0 + 0xFC) = 0;
        *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE4) = 0;
        break;
    }
}


extern void func_800183E0(s32 a0);
extern void (*D_80186540[])(void *);
extern s32 func_8004787C(s32 a0);

void func_80180A80(void *a0)
{
    u16 h;

    func_800183E0(*(s32 *)((u8 *)D_80186540 + ((*(u16 *)((u8 *)a0 + 0xFC) << 1) & 0x1C)));
    h = *(u16 *)((u8 *)a0 + 0xFE) + 0x40;
    *(u16 *)((u8 *)a0 + 0xFE) = h;
    if ((s16)h >= 0x201 || (s16)h < 0x600) {
        *(u16 *)((u8 *)a0 + 0xFC) = 8;
    }
    *(u16 *)((u8 *)a0 + 6) = *(u16 *)((u8 *)a0 + 6) + 2;
    *(s16 *)((u8 *)a0 + 0xA) = -0x32B - ((func_8004787C(*(s16 *)((u8 *)a0 + 0xFE)) << 6) >> 12);
    if (*(s16 *)((u8 *)a0 + 0xFE) == 0x800) {
        *(u16 *)((u8 *)a0 + 2) = 2;
    }
}


extern u8 D_80186570;
extern u8 D_8018657C;
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_80180B38(a0)
void *a0;
{
    void *s0;
    s32 v0;
    s32 v1;

    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        extern u8 D_80186570;
        extern u8 D_8018657C;
        v1 = 0x4000;

        func_8001CA1C(v0, (s32)&D_80186570);
        func_8012A828((s32 *)s0, (s32)&D_8018657C);
        *(s16 *)((s32)s0 + 2) = 1;
        *(u8 *)((s32)s0 + 0xC0) = 1;
        *(u8 *)((s32)s0 + 0xC1) = 0;
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) = v1;
        do { *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) = v1; } while (0);
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1C) = v1;
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x2C) |= 0x10;
        *(s32 *)(*(s32 *)((s32)s0 + 0x20) + 4) = (s32)(0x1000000 >> 16) << 16;
        *(s32 *)((s32)s0 + 0x1C) = 0x20;
        *(s16 *)((s32)s0 + 0xFC) = 0;
    }
}


extern void (*D_8018658C[])(void);

void func_80180C00(s32 param_1)
{
    u16 idx;

    idx = (*(u16 *)(param_1 + 0xFC) >> 1) % 6;
    func_800183E0((s32)D_8018658C[idx]);

    *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 6) + 8;
    if (--*(s32 *)(param_1 + 0x1C) == 0) {
        *(u16 *)(param_1 + 2) = 2;
    }
}


extern void func_800183E0(s32 a0);
extern void (*D_801865A4[])(void *);
extern s32 D_801B570C;

void func_80180C90(void *a0)
{
    s32 v1;
    u16 h;

    v1 = *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE8);
    switch (v1) {
    case 0:
        func_800183E0((s32)&D_801B570C);
        break;
    case 1:
        h = *(u16 *)((u8 *)a0 + 0xFC);
        func_800183E0(*(s32 *)((u8 *)D_801865A4 + ((h << 1) & 0x1C)));
        break;
    case 2:
        *(u16 *)((u8 *)a0 + 2) = 3;
        *(u16 *)((u8 *)a0 + 0xFC) = 0;
        *(s32 *)(*(u32 *)((u8 *)a0 + 0x64) + 0xE8) = 0;
        break;
    }
}


extern void func_800183E0(s32 a0);
extern void (*D_801865A4[])(void *);
extern s32 func_8004787C(s32 a0);

void func_80180D40(void *a0)
{
    u16 h;

    func_800183E0(*(s32 *)((u8 *)D_801865A4 + ((*(u16 *)((u8 *)a0 + 0xFC) << 1) & 0x1C)));
    h = *(u16 *)((u8 *)a0 + 0xFE) + 0x40;
    *(u16 *)((u8 *)a0 + 0xFE) = h;
    if ((s16)h >= 0x201 || (s16)h < 0x600) {
        *(u16 *)((u8 *)a0 + 0xFC) = 8;
    }
    *(u16 *)((u8 *)a0 + 6) = *(u16 *)((u8 *)a0 + 6) + 2;
    *(s16 *)((u8 *)a0 + 0xA) = -0x32B - ((func_8004787C(*(s16 *)((u8 *)a0 + 0xFE)) << 6) >> 12);
    if (*(s16 *)((u8 *)a0 + 0xFE) == 0x800) {
        *(u16 *)((u8 *)a0 + 2) = 2;
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_80180DF8(s32 a0) {

    extern u8 D_801865E4[];
    extern u8 D_80182694[];
    s32 s0 = a0;

    if (func_8012C354(a0, (s32)D_801865E4)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(s32 *)(s0 + 0xB4) = 1;
        func_8012A828((s32 *)s0, (s32)D_80182694);
        *(u16 *)(s0 + 2) = 1;
    }
}


void func_80180E54(void) {
}

extern s32 func_8013CB84(void);
    void func_80180E5C(void) {
        func_8013CB84();
    }


u8 func_80180E7C(u32 arg0) {
    u8 ret;

    ret = 0x21;
    if ((u32)(arg0 - 0x96) >= 0x32) {
        ret = 0x18;
    }
    return ret;
}


extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void);

void func_80180E98(s32 arg0) {
    u8 val;

    
    if (((s16 *)arg0)[0x80] == 0) {
        func_8002A04C(arg0);
    }

    
    val = ((u8 *)arg0)[0xC1];
    if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
        func_8002AC00(0x7);
    }

    
    ((void (*)(s32))func_8012C098)(arg0);
}


typedef struct { s16 vx, vy, vz, pad; } SV_;
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_8012B23C(s32 a0);
extern void func_80180FE4(s32 a0);
extern void func_80181030();

void func_80180F0C(s32 a0) {
    SV_ in;
    SV_ out;
    s32 v0;

    in.vx = *(s16 *)(a0 + 0x6);
    in.vy = *(s16 *)(a0 + 0xA);
    in.vz = *(s16 *)(a0 + 0xE);
    out = in;
    out.vy += 8;

    if ((func_80133784(1, &in, (s32)&out) & 0x6000) != 0) {
        v0 = 1;
    } else {
        func_8012B23C(a0);
        v0 = 0;
    }

    if (v0 == 0) {
        *(s16 *)(a0 + 0x2) = 8;
        *(s16 *)(a0 + 0x98) = 0;
        return;
    }

    if (*(s32 *)(a0 + 0xC4) & 4) {
        func_80180FE4(a0);
    } else {
        func_80181030(a0);
    }
}


extern short D_801BF57C;
extern void func_8012A828(s32*, s32);
extern void func_8012B23C(s32 a0);

void func_80180FE4(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s16 *)(a0 + 0x34) = 0;
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    ((void (*)(s32, void *))func_8012A828)(a0, &D_801BF57C);
    func_8012B23C(a0);
}


#include "common.h"

extern s32 rand(void);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32*, s32);
extern void func_8012B23C(s32 a0);
extern void Square0(s32 *a0, s32 *a1);
extern s16 D_801BF164;

void func_80181030(s32 param_1) {
    s32 d[3];
    void *target = (void *)(param_1 + 0x88);

    *(s16 *)(param_1 + 0x2) = 1;
    *(s16 *)(param_1 + 0x34) = 0;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    *(s32 *)(param_1 + 0x1C) = (rand() & 0x1F) + 0x24;

    d[0] = *(s16 *)(param_1 + 0x6) - *(s16 *)target;
    d[1] = 0;
    d[2] = *(s16 *)(param_1 + 0xE) - *(s16 *)(param_1 + 0x8C);
    Square0(d, d);

    if (d[0] + d[2] > 0x8FFFF) {
        *(s16 *)(param_1 + 0xFC) = func_8012B744((void *)(param_1 + 0x4), target);
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

    func_8012B23C(param_1);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)param_1, (s32)&D_801BF164);
}



extern void func_8012A828(s32 *a0, s32 a1);
    extern short D_801BF01C;
    void func_80181138(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        func_8012A828((s32 *)a0, (s32)&D_801BF01C);
    }


extern void func_8012A828(s32*, s32);

void func_80181168(void *a0) {

    extern u8 D_801BF20C[];
    extern u8 D_801BF294[];
    *(s16 *)((s32)a0 + 0x2) = 3;
    if (*(u16 *)((s32)a0 + 0x86) & 2) {
        *(s16 *)((s32)a0 + 0x34) = 1;
        *(s32 *)((s32)a0 + 0x1C) = 0x28;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801BF20C);
        *(u16 *)((s32)a0 + 0xFE) = 0;
    } else {
        *(s16 *)((s32)a0 + 0x34) = 0;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801BF294);
        *(s32 *)((s32)a0 + 0x1C) = 0x19;
        *(u16 *)((s32)a0 + 0x86) |= 2;
    }
}


#include "common.h"

extern s32  func_8012B8E4(s32 arg0, s32 arg1);
extern s32  func_8012BEE8(s32 arg0);
extern void func_8012A828(s32*, s32);
extern void func_8012B178(s32 arg0, s32 arg1);
extern void func_8012CBA4(s32 arg0);
extern void func_8012ADE4(u8 *arg0);
extern s32  func_8012BD3C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80142414(s32 arg0, s16 arg1);
extern s32  func_80143B6C(s32 arg0, s32 arg1);
extern void func_80181030();
extern void func_801813B4();
extern void func_8002D4C8(s32 arg0, s32 arg1);

extern u8  D_801BF20C[];
extern u8  D_801BF294[];
extern s32 D_801B6E34;

void func_801811EC(void *a0)
{
    s32 v;
    unsigned short *p;
    s16 t;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        v = func_8012B8E4((s32)a0, 4);
        p = (unsigned short *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
        *p = (unsigned short)(*p + v);

        if (*(s32 *)((s32)a0 + 0x1C) == 0xF) {
            func_80142414((s32)a0, -0x78);
            func_8002D4C8(0x6A9, 0);
        }

        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((s32)a0 + 0x2) = 3;
            if ((*(u16 *)((s32)a0 + 0x86) & 0x2) != 0) {
                *(u16 *)((s32)a0 + 0x34) = 1;
                *(s32 *)((s32)a0 + 0x1C) = 0x28;
                ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801BF20C);
                *(s16 *)((s32)a0 + 0xFE) = 0;
            } else {
                *(u16 *)((s32)a0 + 0x34) = 0;
                ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801BF294);
                *(s32 *)((s32)a0 + 0x1C) = 0x19;
                *(u16 *)((s32)a0 + 0x86) = *(u16 *)((s32)a0 + 0x86) | 0x2;
            }
        }
        break;
    case 1:
        if (*(s32 *)((s32)a0 + 0x1C) >= 0x16) {
            v = func_8012B8E4((s32)a0, 6);
            p = (unsigned short *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
            *p = (unsigned short)(*p + v);
        }

        func_8012B178((s32)a0, D_801B6E34);

        if (((s32 (*)(s32))func_8012CBA4)((s32)a0) != 0x2000) {
            func_8012ADE4((u8 *)a0);
        }

        t = *(u16 *)((s32)a0 + 0xFE) - 1;
        *(u16 *)((s32)a0 + 0xFE) = t;
        if (t <= 0) {
            func_80143B6C((s32)a0, 0);
            *(u16 *)((s32)a0 + 0xFE) = 8;
        }

        if (func_8012BEE8((s32)a0) != 0) {
            func_80181030((s32)a0);
        }

        if (func_8012BD3C((s32)a0, 0x200, 0x1000) != 0) {
            func_801813B4((s32)a0);
        }
        break;
    }
}


extern char D_801BF364[];
extern void func_8012A828(s32*, s32);

void func_801813B4(param_1)
int param_1;
{
    *(short *)(param_1 + 2) = 4;
    *(short *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801BF364);
    *(int *)(param_1 + 0x1c) = 0x14;
}


void func_801813F8(void *a0) {
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_8012B8E4(s32 a0, s32 a1);
    extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);
    extern u8 D_801B6EC4[];
    extern u8 D_801BEF74[];
    extern u8 D_801BF42C[];
    extern short D_801BF01C;
    s32 base = (s32)a0;
    s32 ptr;
    s32 ret;

    switch (*(u16 *)(base + 0x34)) {
    case 0:
        if (*(s32 *)(base + 0x1C) == 7) {
            func_8012D5E4(base, (s32)D_801B6EC4, (s32)D_801B6EC4 + 8, 0xB);
        }
        break;
    case 1:
        ret = func_8012B8E4(base, 6);
        ptr = *(s32 *)(base + 0x20);
        *(u16 *)(ptr + 0x12) += ret;
        break;
    case 2:
        if (*(s32 *)(base + 0x1C) == 0xA) {
            func_8012D5E4(base, (s32)D_801B6EC4, (s32)D_801B6EC4 + 8, 0xB);
        }
        break;
    }

    if (func_8012BEE8(base) == 0) {
        return;
    }

    switch (*(u16 *)(base + 0x34)) {
    case 0:
        if (func_8012BD3C(base, 0x400, 0x4000) == 0) {
            goto state_off;
        }
        *(u16 *)(base + 0x34) = 1;
        func_8012A828((s32 *)base, (s32)D_801BEF74);
        *(s32 *)(base + 0x1C) = 0xA;
        break;
    case 1:
        *(u16 *)(base + 0x34) = 2;
        *(s32 *)(base + 0x1C) = 0x18;
        func_8012A828((s32 *)base, (s32)D_801BF42C);
        break;
    case 2:
    state_off:
        *(u16 *)(base + 0x2) = 2;
        *(u16 *)(base + 0x34) = 0;
        func_8012A828((s32 *)base, (s32)&D_801BF01C);
        break;
    }
}


void func_8018156C(void *a0) {
    extern u8 D_801B6ED8[];
    s32 *tbl;

    tbl = (s32 *)D_801B6ED8;
    if ((*(u16 *)((s32)a0 + 0x70) & 0x2000) == 0) {
        tbl = (s32 *)((s32)tbl + 0xC);
    }
    *(s16 *)((s32)a0 + 0x2) = 7;

    func_8012A828((s32 *)a0, tbl[0]);
    func_8012B2CC((s32)a0);
    func_8012B200((u8 *)a0);
    func_8012B178((s32)a0, tbl[1]);
    *(s32 *)((s32)a0 + 0x1C) = tbl[2];
}


#include "common.h"

extern s32 func_8012C044(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void);

extern s32 D_801B6EF0[];

void func_801815EC(s32 arg0) {
    void (*handler)(s32);
    s32 val;

    /* Load dispatch function from table indexed by field at +0x2 */
    handler = (void (*)(s32))D_801B6EF0[((u16 *)arg0)[1]];
    handler(arg0);

    /* Check field at +0x0 */
    if (((u16 *)arg0)[0] == 0)
        return;

    if (func_8012C044(arg0)) {
        /* Read field at +0xC1, set field at +0x100 */
        val = ((u8 *)arg0)[0xC1];
        ((u16 *)arg0)[0x80] = 1;
        if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
            func_8002AC00(0x7);
        }
        ((void (*)(s32))func_8012C098)(arg0);
    }
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80181690(void) {
        func_8002D4C8(0x6AA, 0);
    }


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_801816B4(u8 *a0) {
        if (*(u8 *)(a0 + 0x5E) == 0xC) {
            func_8002D4C8(0x9DA, 0);
        }
    }


extern void func_8012CBF4(s32 a0);
extern void func_80181030();

void func_801816E4(s32 a0)
{
    func_8012CBF4(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_80181030(a0);
    }
}




extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80181138(short *a0);
extern s32 D_801B6E30;

void func_80181728(s32 a0) {
    s32 ret;
    s32 v0;

    if (*(s32 *)(a0 + 0x1C) >= 4) {
        v0 = *(s32 *)(a0 + 0x20);
        ret = func_8012B608(*(s16 *)(v0 + 0x12), *(s16 *)(a0 + 0xFC), 8);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += ret;
    }
    func_8012B178(a0, D_801B6E30);
    if (((s32 (*)(s32))func_8012CBA4)(a0) != 0x2000) {
        func_8012ADE4((u8 *)a0);
    }
    if (func_8012BEE8(a0) != 0) {
        func_80181138((short *)a0);
    }
}


extern s32 func_8012BCCC(s32 a0);
extern void func_80181030();
extern void func_80181168(void*);

void func_801817D0(a0)
s32 a0;
{
    s32 s0 = a0;
    s32 d[3];

    if (*(u16 *)(s0 + 0x34) == 0 && (*(u16 *)(s0 + 0x72) & 0x4000)) {
        d[0] = *(s16 *)(s0 + 0x6) - *(s16 *)(s0 + 0x88);
        d[1] = 0;
        d[2] = *(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0x8C);
        Square0(d, d);
        if (d[0] + d[2] <= 0x8FFFF && func_8012BCCC(s0) <= 0x10000) {
            ((void (*)(s32))func_80181168)(s0);
        } else {
            func_80181030(s0);
        }
    }
}


extern s32 D_801B6ED4;
extern s32 func_8012BCCC(s32 a0);
extern void func_8012E88C(s32 a0);
extern void func_8018156C();

void func_80181894(void *a0) {
    s32 s0 = (s32)a0;
    s32 v0 = func_8012BCCC(s0);
    if (v0 < D_801B6ED4) {
        func_8012E88C(s0);
        func_8018156C(s0);
    }
}



extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

extern u8 D_801BF20C[];
extern u8 D_801BF294[];

void func_801818E4(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    if (*(u16 *)(a0 + 0x70) & 0x2000) {
        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s16)v0 <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }
    }
    if (func_8012BEE8(a0)) {
        *(u16 *)(a0 + 0x86) |= 2;
        *(s16 *)(a0 + 0x2) = 3;
        if (*(u16 *)(a0 + 0x86) & 2) {
            *(s16 *)(a0 + 0x34) = 1;
            *(s32 *)(a0 + 0x1C) = 0x28;
            ((void (*)(s32, void *))func_8012A828)(a0, &(*(s16 *)D_801BF20C));
            *(u16 *)(a0 + 0xFE) = 0;
        } else {
            *(s16 *)(a0 + 0x34) = 0;
            ((void (*)(s32, void *))func_8012A828)(a0, &(*(s16 *)D_801BF294));
            *(s32 *)(a0 + 0x1C) = 0x19;
            *(u16 *)(a0 + 0x86) |= 2;
        }
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void);
extern void func_8012CBF4(s32 a0);
extern void func_80181030();
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_801819D0(s32 a0) {
    u8 val;
    s16 field_a;
    s16 field_100;
    s32 result;

    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x10) {
        field_100 = *(s16 *)(a0 + 0x100);
        if (field_100 == 0) {
            func_8002A04C(a0);
        }
        val = ((u8 *)a0)[0xC1];
        if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
            func_8002AC00(0x7);
        }
        ((void (*)(s32))func_8012C098)(a0);
    } else {
        result = ((s32 (*)(s32))func_8012CBF4)(a0);
        if ((result & 0x2000) != 0) {
            if ((result & 0x1000) != 0) {
                func_80131E00((struct S80131E00 *)a0, 0x12);
            } else {
                func_80181030(a0);
            }
        }
    }
}


void func_80181A98(void *a0) {
    extern u8 D_801B6E48[];
    extern u8 D_801B6E7C[];
    extern s16 D_801BF01C;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern s32 func_8012B030(u8 *a0);
    extern s32 func_80143970(s32 a0);
    extern void func_8012E8A8(u8 *a0);
    extern void func_8012A828(s32 *a0, s32 a1);
    extern void func_80181030(s32 a0);

    if (func_8012C354((s32)a0, (s32)D_801B6E48) != 0) {
        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xB4) = -1;
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s32 *)((s32)a0 + 0xBC) = (s32)D_801B6E7C;
        func_80143970((s32)a0);
        func_8012B030((u8 *)a0);
        if (*(u16 *)((s32)a0 + 0x70) & 0x6000) {
            *(u16 *)((s32)a0 + 0x2) = 6;
            func_8012A828((s32 *)a0, (s32)&D_801BF01C);
            func_8012E8A8((u8 *)a0);
        } else {
            func_80181030((s32)a0);
        }
    }
}



extern void (*D_801BFB74[])(void);

void func_80181B3C(void *a0) {
    D_801BFB74[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32*, s32);
/* not declared anywhere in the TU */
extern void func_80182224(void);

void func_80181B78(void *a0) {

    extern s32 D_801BF8CC[];
    extern u8 D_801BF864[];
    extern u8 D_80182694[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801BF864);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801BF8CC[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80182224);
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
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80182694);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_80181C4C(void *a0) {
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


void func_80181C74(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80181C7C(void *a0) {

    extern s32 D_801BFAB0;
    extern s32 D_801BFA9C;
    extern s32 D_801BFA98;
    extern s32 D_801BFB30;
    extern s32 D_801BFAC4;
    extern s32 D_801BF990[];
    extern s32 D_801BFA14[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801BFAB0 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801BFA98 = 0;
                D_801BFA9C = D_801BFA14[v0];
            } else {
                D_801BFA9C = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801BFA14[v0], 1);
                D_801BFA98 = 2;
            }
        } else {
            D_801BFAB0 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801BFA98 = 0;
            D_801BFA9C = D_801BF990[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801BFAC4);
    } else {
        p = &D_801BFB30;
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
extern s32 func_80181FCC(void);

void func_80181DC8(void *arg0) {

    extern s32 D_801BF8CC[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801BF8CC[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801BF8CC[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80181FCC() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    void func_80181EE8(void *arg0) {
        *(s16 *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_80181F14(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80181F24(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_80181F34(void *a0) {

    extern s32 D_801BF8CC[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801BF8CC[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_80181F74(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_80181FA8(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_80181FCC(void) {

    extern s32 D_801BF8CC[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801BF8CC[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801BFB9C[])(void);

void func_80182030(void *a0) {
    D_801BFB9C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_8018206C(void *a0) {

    extern u8 D_801BF898[];
    extern u8 D_801C025C[];
    extern u8 D_801C003C[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801BF898) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C025C);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C003C);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32*, s32);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801820F4(void *a0) {

    extern u8 D_801C004C[];
    extern u8 D_801C0154[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C004C);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C0154);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_801821B4 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801C025C, else
 * D_801C003C), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `((void (*)(s32, void *))func_8012A828)(entity, D_801C025C / D_801C003C)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32*, s32);

void func_801821B4(void *a0) {

    extern u8 D_801C025C[];
    extern u8 D_801C003C[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C025C);
        } else {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801C003C);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801BFB8C[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

s32 aF8018A224() __asm__("func_80182224");

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

    RotTransSV(D_801BFB8C, sv0, &flag);
    RotTransSV(D_801BFB8C + 8, sv1, &flag);

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





