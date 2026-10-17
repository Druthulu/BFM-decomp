#include "common.h"
#include "../shared/engine_prelude.h"


   /* 12-byte sub-table record (stride 0xC) */
 /* 0x20 bytes */
                /* 4 + 16*12 = 0xC4 stride */
                 /* 0x08 */
     /* 0x20 */
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
extern u8 D_80195B0C;
extern u8 D_80195A7C;
extern u8 D_80195A58;
extern u8 D_80195A34;
extern u8 D_80195AE8;
extern u8 D_80195AC4;
extern u8 D_80195AA0;
extern u8 D_80195A10;
extern void func_80145934(void);
extern u8 D_80195B9C;
extern u8 D_80195B78;
extern u8 D_80195B54;
extern u8 D_80195B30;
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
extern unsigned char D_80194F94[];
extern unsigned char D_80194FC4[];
extern unsigned char D_80195014[];
extern unsigned char D_80195044[];
extern unsigned char D_80195074[];
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
extern void (*D_801950C4[])(void *);
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
extern void func_80147514(s32 arg0);
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
extern s32 func_8012EFB8(void *param_1, void *param_2);
extern void func_80149584(s32 arg0, s32 arg1, s32 arg2);
extern void func_8014964C(s32 param_1, s32 param_2);
extern s32 func_801496D4(void *a0);
extern void func_8015AD08(void *arg0);
extern void func_80149704(void);
extern void func_8015ACC4(s32 *arg0);
extern void func_80149724(void);
extern u8 D_80078EBF;
extern s32 func_80149744(struct S_80149744 *a0);
extern void func_8015F7A0(s32 *arg0);
extern void func_80149788(void);
extern void func_801653B8(s32 *a0);
extern void func_80149864(void);
extern s16 currentLocationId;
extern s32 func_8016F1AC(void);
extern s32 func_80149884(void);
extern void func_80160B00(s32 *arg0);
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
extern void func_80157D20(void *param_1, s32 param_2);
extern void func_80149CB4(void *a0, s32 a1);
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
extern s32 D_8019518C[];
extern u8 D_80078E78[];
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern void func_8014A1B0(s32 a0, s32 a1);
extern s32 func_8014A048(s32 param_1);
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern void func_8015D4B4(s16 *a0);
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
extern void func_8015EDD4(s32 *arg0);
extern void func_8014A4FC(void);
extern s32 func_8014A674(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015E184(s32 *arg0);
extern void func_8014A830(void);
extern s32 func_80029AF4(void);
extern s32 func_8014A850(s32 param_1);
extern void func_8014AA04(s32 a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80165A20(s32 a0);
extern void func_8014AB7C(s32 arg0);
extern void func_8014AC10(s32 arg0);
extern void func_8014AA28(void);
extern void func_8014AB5C(void);
extern void func_80162CCC(u8 * a0);
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
extern void func_80166244(void* arg0);
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
extern u8 D_80195214[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8019521C;
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
extern s32 func_8014ED80(SubED80 *a0);
extern int D_801D3D70;
extern void func_8014ED28(s32 _arg0);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern void func_8014F1F4(void);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F4C0(s32 arg0);
extern s32 func_8014F468(void);
extern int func_8014F74C(s32 arg0);
extern int func_8014F6F4(void);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801D3D74;
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
extern s32 func_801504D8(u16 *a0);
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
extern s32 D_8019524C;
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
extern s32 func_80029D3C(s32 n);
extern void func_80151878(void);
extern void func_80153B58(s32 *a0);
extern s32 func_80151880(s32 a0);
extern s32 func_801518D8(s32 a0);
extern void func_80151944(void *a0);
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
extern void (*D_801952F4[])(void);
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
extern void (*D_80195318[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80195308;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019532C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80195338[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80195348[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80195360[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80195350;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80195374[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80195390[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80195380;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801953A4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801953B8[])(void);
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
extern s32 D_801953CC;
extern void (*D_801953F4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801953D4;
extern void func_80153D7C(s32 param_1);
extern void func_8015410C(s32 a0);
extern void func_80153E00(s32 param_1);
extern void func_80151664(s32 a0v);
extern void func_80154134(u8 *a0);
extern void func_80154190(u8 *a0, s32 a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154218(u8 *a0, s32 a1, s32 a2);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_801549F8(s32 a0, s32 a1, s32 a2);
extern void func_801542A4(s32 *a0, s32 a1);
extern void func_801542A4(s32 *a0, s32 a1);
extern void func_8015430C(u8 *arg0, s32 arg1, s32 arg2);
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
extern int (*D_80195440[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80195444[])(void);
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
extern s32 func_80155F80(s32 a0);
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
extern unsigned short D_801958A8[];
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
extern void (*D_801958B8[])(void);
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
extern int D_801D3DA8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801958E0[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801958C0;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801958D0;
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
extern void (*D_80195920[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80195928[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801958F4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80195934[])(void);
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
extern u8 D_80195904;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D3DB0;
extern s32 D_801D3DBC;
extern s32 D_801D3DC0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80195970[])(s32 *);
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
extern s32 D_80195944[];
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
extern s32 D_801D3DB8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80195BC0[])(void);
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
extern char D_801959E0[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80195C64[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80195DB8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80195BD4;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80195DC0[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80195BE4;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80195C04;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80195DC8[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern u8 D_800D4BE0[];
extern int func_8014A51C(int param_1);
extern s32 func_8015B858(u8 *a0);
extern s32 D_800D4B48;
extern void func_8015B8F8(s32 *a0);
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94(s32 *a0);
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
extern void (*D_80195DF0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80195DFC[])(void);
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
extern s32 func_8015CCD0(s32 param_1);
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
extern void (*D_80195C70[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80195EA0;
extern void func_8015D380(s32 a0);
extern unsigned char D_80194F84[];
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
extern unsigned char D_80195EB4[];
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
extern s8 D_80195EF0[];
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
extern u16 D_80195F38;
extern u16 D_80195F3A;
extern u16 D_80195F3C;
extern s32 D_80195F40;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80195F48;
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
extern int D_80195C54;
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
extern void func_8015F380(void* arg0);
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
extern unsigned int D_80195FCC[];
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
extern void func_80160F00(void* arg0);
extern void func_80160E3C(s32 *a0);
extern void func_80160EA4(void *a0);
extern void func_80160E70(s32 *a0);
extern void (*D_8019607C[])(void);
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
extern s32 func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_801960AC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80196110;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D3DC8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80196134[])(void);
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
extern int D_801D3E20[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8019617C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8019616C;
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
extern char D_801D34A0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80196184[])(void);
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
extern void (*D_801961D8[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801961A0;
extern s16 D_801961D4;
extern s16 D_801961D2;
extern s16 D_801961D0;
extern void func_801647A4(int param_1);
extern void func_80164ACC(s32 a0);
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801961E4[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D3E80;
extern u8 D_801D3E81;
extern u8 D_801D3E82;
extern u8 D_801D3E83;
extern u8 D_801D3E84;
extern u8 D_801D3E85;
extern u8 D_801D3E86;
extern u8 D_801D3E87;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801961F4[])(void);
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
extern s32 D_801D3EC0;
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
extern void (*D_80196238[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801962B4[];
extern s32 D_801962D4[];
extern u8 D_80196350[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80196370[];
extern u8 D_80196390[];
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
extern void (*D_8019642C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801964A8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D34B0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801964B4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801964BC[])(void);
extern void func_801663FC(void *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4(s32 *a0);
extern void func_80146C3C(u8 *a0);
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_80196584[])(void);
extern void func_80166618(void *a0);
extern void (*D_80196594[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801965A4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(u8 *a0);
extern void func_801678F0(s32 a0);
extern void (*D_801965B0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80196510[];
extern u8   D_80196524[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
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
extern void (*D_801965C8[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(s32 param_1);
extern void func_801687CC(s32 param_1);
extern void func_80168828(s32 param_1);
extern void (*D_801965D0[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801965D8[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801965E0[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40(void *arg0);
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801965E8[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(s32 arg0);
extern void func_801691B8(void *a0);
extern void (*D_801965F0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801965F8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801966AC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801966B4[])(void);
extern void func_80169F00(void *a0);
extern char D_80196664[];
extern char D_80196624[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801966EC[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801966F8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80196740[])(void);
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
extern void (*D_801967BC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D41E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801967B0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801967F4[];
extern unsigned short D_801967FC[];
extern unsigned short D_80196804[];
extern unsigned char D_801D41E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D41E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019680C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D431C;
extern M2C_UNK D_801D4320;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D42A8;
extern void (*D_8019683C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D4324[];
extern u8 D_801D432C[];
extern u8 D_801D42DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80196844[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80196860[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80196868[])(void);
extern void func_8016D428(void *a0);
extern void func_8016D464(u8 *a0);
extern void func_8016D4DC(s32 a0);
extern void func_8016D5EC(s32 *a0);
extern short func_8016CBC0(void);
extern void func_8016D64C(int param_1);
extern void func_8016D778(s32 a0);
extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
extern void func_8016D848(s32 *a0);
extern void func_8016D984(s32 *a0);
extern void func_8016DBD8(u8 *a0);
extern void (*D_801968D0[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80196874;
extern u8 D_80196880;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80196904[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019690C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80196960[])(void);
extern void func_8016E5B8(void *a0);
extern void func_8016E5F4(s32 arg0);
extern void func_8016E778(int param_1);
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
extern u16 D_80196994[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80196984[];
extern void func_8016EB3C(s32 p);
extern void func_8016EBA8(u8 *param_1);
extern void func_8016ED6C(void);
extern s32 D_80126D70;
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8016ED8C(s32 a0, s32 a1, s32 a2);
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern void func_8016EDBC(s32 a0, s32 a1, s32 a2);
extern void func_8016EE94(s32 a0, s32 a1);
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
extern s32 func_8016EFC8(s32 a0, s32 a1);
extern s32 func_8016EFA8(s32 a0);
extern void func_8016F094(s32 *a0);
extern s32 func_8016F0AC();
extern s32 D_801969B0;
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
extern void func_8016F0E4(u8 * p);
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
extern void (*D_80196A28[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80196A30[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80196A38[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80196A40[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80196A48[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80196A50[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80196A5C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24(s32 a0);
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80196A68[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80196A74[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80196A84[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80196A94[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80196A9C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80196AA4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80196AAC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80196AB4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80196ABC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80196AC4[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80196ACC[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80196AD4[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80196ADC[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80196AE4[])(void);
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
extern void (*D_80196AEC[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80196AF4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80196AFC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80196B04[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80196B0C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80196B14[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80196B1C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80196B24[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80196B2C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80196B34[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80196B3C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80196B44[])(void);
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
extern void (*D_80196B88[])(void);
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
extern M2C_UNK D_80196B4C;
extern void func_80173220(void * arg0);
extern void func_80173294(void);
extern void func_801732C4(s32 *a0);
extern void func_8017329C(void);
extern void func_801732C4(s32 *a0);
extern void func_8017331C(s32 *a0);
extern void func_801732F4(void);
extern void func_8017331C(s32 *a0);
extern void func_80173374(s32 *a0);
extern void func_8017334C(void);
extern void func_80173374(s32 *a0);
extern void func_801733A4(void);
extern void func_801733CC(s32 a0);
extern void func_801734BC(s32 a0, s32 a1);
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
extern void func_801734BC(s32 arg0, s32 _unused1);
extern void (*D_80196BB8[])(void);
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
extern void (*D_80196BF4[])(void);
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
extern void func_80174554(s32 arg0);
extern void func_8017452C(void);
extern void func_80174554(s32 arg0);
extern void func_801745AC(s32 *a0);
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
extern s32 func_801749C8(s32);
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80196C4C[])();
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
extern void (*D_80196C5C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80196C64[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80196DCC[])();
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
extern void (*D_80196DD8[])();
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
extern M2C_UNK D_801D36F8;
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
extern s16 D_801D5B28;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D4A60;
extern short D_801D5B9C;
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
extern s32 D_801D4E8C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D4EB4;
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
extern s16 D_801D4E70;
extern s32 func_8017A3B0(void);
extern short D_801D4EAC;
extern short D_801D4EA8;
extern int func_800D0CA0(int);
extern void func_8001AAA0(s32 arg0);
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
extern s16 D_801D4E74;
extern u16 D_801D4EF4;
extern u16 D_801D4EF6;
extern u16 D_801D4EF8;
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
extern s16 D_801D4EEC;
extern s16 D_801D4EEE;
extern s16 D_801D4EF0;
extern s16 D_801D4EE4;
extern s16 D_801D4EE6;
extern s16 D_801D4EE8;
extern void func_8017B7A8(void);
extern s16 D_801D4F04;
extern s16 D_801D4F06;
extern s16 D_801D4F08;
extern s16 D_801D4F0C;
extern s16 D_801D4F0E;
extern s16 D_801D4F10;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D4EFC;
extern short D_801D4EFE;
extern short D_801D4F00;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D4E94;
extern SV4 D_801D4E9C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D4EBC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D4EB8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80196FB4[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80196FCC[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);

/* func_8017C24C — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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
















#include "../shared/ov/func_8017C24C__t67f11bf2.h"


#include "../shared/ov/func_8017D12C__79ff9481.h"



extern void (*D_80197048[])(void);

void func_8017D14C(void *a0) {
    D_80197048[((Unkstruct_80159698 *)a0)->unk15]();
}




extern void func_8017D3B8(void);
extern void func_800167B8(s32 a0);

s32 func_8017D188(s32 a0) {
    func_8017D3B8();
    func_800167B8(0);
    ((Unkstruct_8017CA8C *)a0)->unk15 += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D1CC(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_80197050[])(void);

void func_8017D1F0(void *a0) {
    D_80197050[((Unkstruct_80159698 *)a0)->unk15]();
}




extern void func_8017D3E0(void);

s32 func_8017D22C(s32 a0) {
    func_8017D3E0();
    ((Unkstruct_8017CB30 *)a0)->unk28 = 10;
    ((Unkstruct_8017CB30 *)a0)->unk15 += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D26C(u8 *a0) {
    if (--(((Unkstruct_8017CB70 *)a0)->unk28) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        ((Unkstruct_8017CB70 *)a0)->unk15 += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017D2E8(void) {
        func_800D1EBC();
    }



extern void (*D_8019705C[])(void);

void func_8017D308(void *a0) {
    D_8019705C[((Unkstruct_80159698 *)a0)->unk15]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017D344(s32 a0) {
    s32 t = ((Unkstruct_8017CC48 *)a0)->unk28 - 1;

    ((Unkstruct_8017CC48 *)a0)->unk28 = t;
    if (t == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        ((Unkstruct_8017CC48 *)a0)->unk15 += 1;
    }
    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D3B8(void) {

    extern s32 D_80197068(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80197068, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8019706C;

void func_8017D3E0(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8019706C, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D4A0(void *a0);

void func_8017D408(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x190;
    D_8012695C = 0x4b0;
    D_80126968 = 0x2aa;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D4A0, 0);
    func_8012A094((s32)D_80126948);
    func_8017D4A0(D_80126948);
}



extern void (*D_80197080[])(void);

void func_8017D4A0(void *a0) {
    D_80197080[((Unkstruct_80126948 *)a0)->unk4]();
}



extern s32 D_80126B58;
extern u16 func_80148800(s32 *a0);
extern void func_8017D648(s32 param_1, s16 *param_2);

void func_8017D4DC(s32 arg0) {
    extern s16 D_80197084[];
    extern Blk8_80126940_8017D4DC D_80126940;
    Blk8_80126940_8017D4DC sp10;
    s16 lo;
    s16 hi;
    s16 p;
    s16 q;
    s16 v;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = ((Unkstruct_8017CF48 *)arg0)->unk5;
        t = (t + 1) & 1;
        ((Unkstruct_8017CF48 *)arg0)->unk5 = t;
        ((Unkstruct_8017CF48 *)arg0)->unk14 = D_80197084[t];
    }
    sp10 = D_80126940;
    if (sp10.v[1] < -0x150) {
        sp10.v[1] = -0x150;
    }
    if (sp10.v[2] >= 0x5B1) {
        sp10.v[2] = 0x5B0;
    }
    v = sp10.v[2];
    if (v < -0x880) {
        lo = -0xC0; hi = 0xC0; p = 0; q = 0xA0;
    } else if (v < 0x280) {
        lo = -0xC0; hi = 0xC0; p = 0; q = 0xA0;
    } else {
        v = sp10.v[0];
        if (v < 0x700) {
            lo = -0xC0; hi = 0xA70;
            if (v < 0) { p = 0; q = 0; }
            else { p = 0xA0; q = 0; }
        } else {
            lo = -0xC0; hi = 0xA70; p = 0; q = 0xA0;
        }
    }
    if (sp10.v[0] < lo) {
        sp10.v[0] = lo;
    } else if (hi < sp10.v[0]) {
        sp10.v[0] = hi;
    }
    ((Unkstruct_8017CF48 *)arg0)->unk2E = p;
    ((Unkstruct_8017CF48 *)arg0)->unk32 = q;
    func_8017D648(arg0, sp10.v);
}


// @class: schedule
// @unstuck(P36): none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017D648(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    ((Unkstruct_8017CF48 *)param_1)->unk8  = (s16)func_80012C6C((s32)CAST_WIDTH(s16, param_1, 0x8),  (s32)((Unkstruct_8017CF48 *)param_1)->unkC,  4);
    ((Unkstruct_8017CF48 *)param_1)->unk10 = (s16)func_80012C6C((s32)CAST_WIDTH(s16, param_1, 0x10), (s32)CAST_WIDTH(s16, param_1, 0x14), 4);
    ((Unkstruct_8017CF48 *)param_1)->unk18 = func_80012ABC((s32)((Unkstruct_8017CF48 *)param_1)->unk18, (s32)((Unkstruct_8017CF48 *)param_1)->unk20, 4);
    ((Unkstruct_8017CF48 *)param_1)->unk1A = func_80012ABC((s32)((Unkstruct_8017CF48 *)param_1)->unk1A, (s32)((Unkstruct_8017CF48 *)param_1)->unk22, 4);
    ((Unkstruct_8017CF48 *)param_1)->unk1C = func_80012ABC((s32)((Unkstruct_8017CF48 *)param_1)->unk1C, (s32)((Unkstruct_8017CF48 *)param_1)->unk24, 4);
    ((Unkstruct_8017CF48 *)param_1)->unk28 = func_80012C6C((s32)((Unkstruct_8017CF48 *)param_1)->unk28, (s32)((Unkstruct_8017CF48 *)param_1)->unk2E, 0x10);
    ((Unkstruct_8017CF48 *)param_1)->unk2A = func_80012C6C((s32)((Unkstruct_8017CF48 *)param_1)->unk2A, (s32)((Unkstruct_8017CF48 *)param_1)->unk30, 0x10);
    ((Unkstruct_8017CF48 *)param_1)->unk2C = func_80012C6C((s32)((Unkstruct_8017CF48 *)param_1)->unk2C, (s32)((Unkstruct_8017CF48 *)param_1)->unk32, 0x10);

    ((Unkstruct_8017CF48 *)param_1)->unk48 = (s32)((Unkstruct_8017CF48 *)param_1)->unk28 + (s32)param_2[0];
    ((Unkstruct_8017CF48 *)param_1)->unk4C = (s32)((Unkstruct_8017CF48 *)param_1)->unk2A + (s32)param_2[1];
    ((Unkstruct_8017CF48 *)param_1)->unk50 = (s32)((Unkstruct_8017CF48 *)param_1)->unk2C + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = ((Unkstruct_8017CF48 *)param_1)->unk28 + param_2[0];
    m1.t[1] = ((Unkstruct_8017CF48 *)param_1)->unk2A + param_2[1];
    m1.t[2] = ((Unkstruct_8017CF48 *)param_1)->unk2C + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = ((Unkstruct_8017CF48 *)param_1)->unk10;
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    ((Unkstruct_8017CF48 *)param_1)->unk3C = (s32)svec_out.vx;
    ((Unkstruct_8017CF48 *)param_1)->unk40 = (s32)svec_out.vy;
    ((Unkstruct_8017CF48 *)param_1)->unk44 = (s32)svec_out.vz;
}


extern s16 D_80126CAC;
extern s16 D_80126CB0;

int func_8017D7E0(short *a0) {
    int data[3];
    data[0] = D_80126CAC - a0[0];
    data[1] = 0;
    data[2] = D_80126CB0 - a0[2];
    gte_lwc2x3_sqr_6a00();
    gte_swc2x3_66ca();
    return (data[0] + data[1] + data[2]) - 0x90001U < 0x18FFF;
}


extern s16 D_80126CAC;
extern s16 D_80126CB0;

int func_8017D874(short *a0) {
    int data[3];
    data[0] = D_80126CAC - a0[3];
    data[1] = 0;
    data[2] = D_80126CB0 - a0[7];
    gte_lwc2x3_sqr_6a00();
    gte_swc2x3_66ca();
    return data[0] + data[1] + data[2] > 0xFFFFF;
}



extern void (*D_80197088[])(void);

void func_8017D8F8(void *a0) {
    D_80197088[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern s32 rand(void);
extern void func_8012AD50(void *a0);

void func_8017D934(void *param_1)
{
    u16 temp_v0;
    u16 temp_v1;
    s32 r1;
    s32 r2;

    temp_v0 = CAST_SIGN(u16, (s32)param_1, 0xFC);
    temp_v1 = CAST_SIGN(u16, (s32)param_1, 0x70);
    ((Unkstruct_800B5CB8 *)param_1)->unkDC = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unkE0 = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unkE4 = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unk100 = temp_v0;
    ((Unkstruct_800B5CB8 *)param_1)->unk102 = temp_v1;
    r1 = rand();
    r2 = rand();
    ((Unkstruct_800B5CB8 *)param_1)->unkFE = (r1 & 0x1F) + (r2 & 0x1F) + 0x3C;
    func_8012AD50(param_1);
}


void func_8017D9A4(int param_1)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int tmp;
    int dcVal;

    if (((Unkstruct_8017D940 *)param_1)->unkFE == 0) {
        iVar2 = func_8004787C((int)((Unkstruct_8017D940 *)param_1)->unk100);
        if (iVar2 < 0) {
            iVar2 = iVar2 + 0x7f;
        }
        iVar2 = iVar2 >> 7;
        tmp = *(unsigned short *)(param_1 + 0x100) + *(unsigned short *)(param_1 + 0x102);
        ((Unkstruct_8017D940 *)param_1)->unk100 = (short)tmp;
        iVar3 = func_80047948((short)tmp);
        if (iVar3 < 0) {
            iVar3 = iVar3 + 0x7f;
        }
        ((Unkstruct_8017D940 *)param_1)->unkE4 = ((Unkstruct_8017D940 *)param_1)->unkE4 + 4;
        iVar3 = iVar3 >> 7;
        if (((Unkstruct_8017D940 *)param_1)->unkE4 >= 0x40) {
            ((Unkstruct_8017D940 *)param_1)->unkE4 = 0;
        }
        dcVal = ((Unkstruct_8017D940 *)param_1)->unkDC;
        ((Unkstruct_8017D940 *)param_1)->unkE0 = ((Unkstruct_8017D940 *)param_1)->unkE0 + 0xb;
        iVar4 = func_8004787C(((Unkstruct_8017D940 *)param_1)->unkE0) * 0x30;
        if (iVar4 < 0) {
            iVar4 = iVar4 + 0xfff;
        }
        iVar5 = iVar4 >> 0xc;
        if (((Unkstruct_8017D940 *)param_1)->unkE0 >= 0x800) {
            *(unsigned short *)(param_1 + 2) = *(unsigned short *)(param_1 + 2) - 1;
            return;
        }
        iVar5 = iVar5 << 0x10 | iVar5 << 8 | iVar5;
        func_8017DB20(param_1, 0, (short)iVar2, (short)iVar3, dcVal, iVar5);
        func_8017DB20(param_1, 1, (short)iVar2, (short)iVar3, dcVal, iVar5);
    } else {
        ((Unkstruct_8017D940 *)param_1)->unkFE = ((Unkstruct_8017D940 *)param_1)->unkFE - 1;
    }
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_800178EC(s32 a0);


void func_8017DB20(s32 param_1, s32 param_2, s16 param_3, s16 param_4, s32 param_5, s32 param_6)
{
    Quad_8017DB20 q;
    Quad_8017DB20 *p;
    s32 buf[2];
    u16 v1val;
    u16 v0val;
    s16 yhi;
    s16 ylo;
    s16 xsel;
    s16 t_vx0;
    s16 t_vx1;

    p = &q;
    func_80015978(param_1 + 4, buf);
    v1val = *(u16 *)buf;
    v0val = *((u16 *)buf + 1);

    t_vx0 = v1val + param_3;
    yhi = v0val + 0x80;
    t_vx1 = v1val + param_4;
    ylo = v0val - 0x80;
    q.vx0 = t_vx0;
    q.vy0 = yhi;
    q.vx1 = t_vx1;
    q.vy1 = ylo;

    switch (param_2) {
    case 0:
        xsel = v1val - 0xA0;
        break;
    case 1:
        xsel = v1val + 0xA0;
        break;
    default:
        goto skip_store;
    }
    q.vx2 = xsel;
    q.vy2 = yhi;
    q.vx3 = xsel;
    q.vy3 = ylo;
skip_store:
    p->vz0 = 0;

    p->rgb0 = p->rgb1 = param_5;
    p->rgb2 = p->rgb3 = param_6;
    p->u0 = ((Unkstruct_8017D940 *)param_1)->unkE4 + 0xC00;
    p->v0 = 0x100;

    p->u1 = ((Unkstruct_8017D940 *)param_1)->unkE4 + 0xC3F;
    p->v1 = 0x100;

    p->u2 = ((Unkstruct_8017D940 *)param_1)->unkE4 + 0xC00;
    p->v2 = 0x13F;

    p->u3 = ((Unkstruct_8017D940 *)param_1)->unkE4 + 0xC3F;
    p->v3 = 0x13F;
    p->clut = 0x36;
    p->flags = 0x50000000;

    func_800178EC((s32)p);
}


extern s32 func_8017DC58(void);

s32 func_8017DC58(void) {
    return 0x7E;
}



extern void func_8012DFD4(void *a0);

void func_8017DC60(void *a0) {

    extern void (*D_80197108[])(void);
    D_80197108[((Unkstruct_8017DC60 *)a0)->unk2]();
    if (((Unkstruct_8017DC60 *)a0)->unk0 != 0) {
        func_8012DFD4(a0);
    }
}


s32 func_8017DCC0(s32 arg0)
{
    s32 w;

    switch (((Unkstruct_8017DCC0 *)arg0)->unk34) {
    case 0:
        w = ((Unkstruct_8017DCC0 *)arg0)->unkA - 8;
        ((Unkstruct_8017DCC0 *)arg0)->unkA = w;
        if ((s16)w < -0x5F) {
            ((Unkstruct_8017DCC0 *)arg0)->unk34 = ((Unkstruct_8017DCC0 *)arg0)->unk34 + 1;
            func_8002D4C8(0xB02, 0);
        }
        break;
    case 1:
        w = ((Unkstruct_8017DCC0 *)arg0)->unkFC + 0x40;
        ((Unkstruct_8017DCC0 *)arg0)->unkFC = w;
        ((Unkstruct_8017DCC0 *)arg0)->unkA = -0x60 - (func_8004787C((s16)w) >> 5);
        if (CAST_SIGN(s16, arg0, 0xFC) < 0x400) {
            break;
        }
        return 1;
    }
    return 0;
}


void func_8017DD88(s32 a0) {
    extern void func_8012A828(s32 a0, void * a1);
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern u8 D_801970C0[];
    extern u8 D_80197100;

    if (func_8012C354(a0, D_801970C0) != 0) {
        func_8001D0E8(((Unkstruct_800B5CB8 *)a0)->unk20, 0xC8, 0x168);
        ((Unkstruct_800B5CB8 *)a0)->unkC0 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unkB4 = -1;
        ((Unkstruct_800B5CB8 *)a0)->unkAE = -1;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unk75 = 0;
        func_8012A828(a0, &D_80197100);
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0xA;
    }
}


extern s16 D_80197090;

void func_8017DE08(s32 param_1) {
    s32 v;

    v = ((Unkstruct_8017DE08_2 *)param_1)->unk1C - 1;
    ((Unkstruct_8017DE08_2 *)param_1)->unk1C = v;
    if (v == 0) {
        func_80178B18(param_1, (s32)&D_80197090);
        ((Unkstruct_8017DE08_2 *)param_1)->unk2 = 2;
        func_8002D4C8(0xB23, 0);
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017DE64(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 3;
    }
}


#include "../shared/ov/func_8017DEA4__76785405.h"


extern void func_80019064(void *a0);

void func_8017DEAC(void *a0) {

    extern u8 D_80197118;
    extern void (*D_80197140[])(void *);
    func_80019064(&D_80197118);
    D_80197140[((Unkstruct_8017CD9C *)a0)->unk2](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_8017DF04(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8017DF54(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}




extern s16 currentLocationId;
extern void func_80147324(s32 a0);
extern s32 func_801511E0(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8017E188(void);
extern void func_80146CA0(void *a0);
extern u8 D_80197120[];

void func_8017DF54(s32 a0)
{
    if (currentLocationId == 0x3083) {
        ((Unkstruct_80126B58 *)a0)->unkA = ((Unkstruct_80126B58 *)a0)->unkA - 8;
    }
    func_80147324(0x451);
    ((void (*)(s32))func_801511E0)(a0);
    ((void (*)(s32, s32))func_80154274)(a0, (s32)D_80197120);
    ((void (*)(s32))func_80149020)(a0);
    ((Unkstruct_80126B58 *)a0)->unkDE = 0xA;
    ((Unkstruct_80126B58 *)a0)->unkDF = 0;
    func_8017E188();
    func_80146CA0((void *)a0);
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_8017E1AC(void);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern void func_8017E134(s32 a0);

void func_8017DFD8(s32 param_1)
{
    s16 buf[4];
    s32 v2;
    s32 uVar3;
    s32 uVar4;
    s32 uVar5;
    s16 rnd;
    u8 cnt;

    func_80015978(param_1 + 4, (s32 *)buf);
    buf[1] -= 0x40;

    while (v2 < 3) {
        v2 = func_8017E1AC();
        if (v2 >= 0) {
            func_80146A6C(0x51, (void *)param_1, buf[0], buf[1], buf[2], v2, 1);

            uVar3 = rand();
            uVar4 = rand();
            uVar5 = rand();
            rnd = (uVar3 & 3) * 0x400 + (uVar4 & 3) * 0xfa + (uVar5 & 3) * 0x44;
            func_80146A6C(0x52, (void *)param_1, 0, -0x20, 0x10, rnd, 1);
        }
    }

    cnt = CAST_SIGN(u8, param_1, 0xde);
    ((Unkstruct_80126B58 *)param_1)->unkDE = cnt + 0xff;
    if (cnt == 0) {
        func_8017E134(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_8017E134 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
 * the standard `func_8014BC44(actor, actor->0xF2)` animation kick, set 0xA8 = 0x20,
 * then hand the actor to func_80151664.
 *
 * Two load-bearing derivations (both byte-verified against the .s):
 *
 *  1. The final call TAKES THE ACTOR. The .s sets `addu $a0,$s0,$zero` immediately
 *     before `jal func_80151664`, but the whole fleet declares
 *         extern void func_80151664(void);
 *     (16 TUs + engine_core.h:2924; ov_SC02_016_after.c:3151 records that a
 *     `void func_80151664(s32)` definition is `conflicting types` everywhere).
 *     So: cookbook idiom 9 — cast at the CALL SITE, never touch the decl:
 *         ((void (*)(s32))func_80151664)(a0)
 *     The .run/ghidra_c seed shows `FUN_80151664()` with no argument and is WRONG
 *     here; the .s wins. This is the single instruction the previous draft missed.
 *
 *  2. `sb $v0, 0xA8($a0)` uses $a0 — NOT $s0 — as its base, and lands in the jal's
 *     delay slot. That needs no local-variable lever (no `s32 s0 = a0;` as the
 *     sibling DEFINE_func_80152790 template uses): the arg copy into $a0 is emitted
 *     ahead of the store, so the store simply addresses off the live copy, and
 *     reorg.c then lifts the last pre-jal insn into the delay slot. Writing a
 *     separate pointer local here would only add a pseudo.
 *
 * Declaration surface (D2 pass over the whole TU, one grep):
 *   func_80147364  -> ov_SC02_016_jr_8017DC70.c:194,360  extern void (u16, s32)
 *   func_80147324  -> :196,777                           extern void (s32)
 *   func_8014BC44  -> :486                                extern void (s32, s32)
 *   func_80151664  -> :880                                extern void (void)  [re-declared
 *                     identically below, which is a legal duplicate declaration]
 *   func_8017E134  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(s32 a0v);

void func_8017E134(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, ((Unkstruct_80126B58 *)a0)->unkF2);
    ((Unkstruct_80126B58 *)a0)->unkA8 = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_8017E188(void)
{
    extern u8 D_801D4F2B;
    s32 i = 19;
    u8 *p = &D_801D4F2B;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_8017E1AC(void)
{

    extern u8 D_801D4F18[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801D4F18;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 20);
    ret = -1;
done:
    return ret;
}



extern void (*D_8019714C[])(void);

void func_8017E1F0(void *a0) {
    D_8019714C[((Unkstruct_80126B58 *)a0)->unk2]();
}


// @class: regalloc-order
// @unstuck(P36): none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801D4F2C + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017E420(void*);
extern void func_8017E3F0(int);
extern int rand(void);

void func_8017E22C(int param_1)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern unsigned char D_801D4F2C[];
    int iVar3;
    int iVar3b;
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801D4F2C + ((Unkstruct_8017E22C_2 *)param_1)->unk2C * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    iVar3b = iVar3;
    ((Unkstruct_8017E22C_2 *)param_1)->unk20 = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8017E420)(iVar5);
        *(unsigned int *)(iVar3 + 4) = *(unsigned int *)(iVar3 + 4) | 0x50000000;
        if (((Unkstruct_8017E22C_2 *)param_1)->unk2C != 0) {
            sVar2 = (rand() & 3) * 0x800 + 0x1000;
            ((Unkstruct_8017E22C_4 *)iVar3)->unk1A = sVar2;
            ((Unkstruct_8017E22C_4 *)iVar3)->unk18 = sVar2;
            *(unsigned short *)(param_1 + 0x12) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                ((Unkstruct_8017E22C_2 *)param_1)->unk12 = -((Unkstruct_8017E22C_2 *)param_1)->unk12;
            }
            *(unsigned short *)(param_1 + 0x1a) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                ((Unkstruct_8017E22C_2 *)param_1)->unk1A = -((Unkstruct_8017E22C_2 *)param_1)->unk1A;
            }
        } else {
            ((Unkstruct_8017E22C_4 *)iVar3b)->unk1A = 0x4000;
            ((Unkstruct_8017E22C_4 *)iVar3b)->unk18 = 0x4000;
        }
        ((Unkstruct_8017E22C_2 *)param_1)->unk2 = ((Unkstruct_8017E22C_2 *)param_1)->unk2 + 1;
    } else {
        func_8017E3F0(param_1);
    }
}




extern s32 func_8017E434(s32 *a0, s32 a1);
extern void func_8017E3F0(int);

void func_8017E378(s32 *a0)
{

    extern unsigned char D_801D4F2C[];
    s32 param;
    s32 table_base;

    param = ((Unkstruct_8017DB6C *)a0)->unk2C;
    table_base = (s32)D_801D4F2C + param * 0x40;

    if (param != 0) {
        ((Unkstruct_8017DB6C *)a0)->unk6 += ((Unkstruct_8017DB6C *)a0)->unk12;
        ((Unkstruct_8017DB6C *)a0)->unkE += ((Unkstruct_8017DB6C *)a0)->unk1A;

        if (func_8017E434(a0, table_base) == 0) {
            return;
        }
    }

    ((void (*)(s32 *))func_8017E3F0)(a0);
}




















extern void func_80146C3C(u8 *a0);
void aF8017E3F0(s32 *param_1) __asm__("func_8017E3F0");
void aF8017E3F0(s32 *param_1)
{

    extern s8 D_801D4F18;
  int new_var;
register s32 p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
s32 r;
  p = (s32) (&D_801D4F18);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}



void func_8017E420(void *a0) {
        ((Unkstruct_8017DC14 *)a0)->unk0 = 0xF0F0F0;
        ((Unkstruct_8017DC14 *)a0)->unk4 = 0;
    }




/* func_8017E434 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_8017E434(s32 *a0, s32 a1);
 *
 * Two derivations that mattered (both byte-verified against the .s):
 *  - Both `-0x20` subtractions and the `sll $v0,$a2,16` in the bnez delay slot
 *    are reorg.c fill-from-target duplicates, NOT source duplication: one
 *    `t -= 0x20` after the if reproduces them exactly.
 *  - `(t << 8) | (t | 0xFF0000)` written as ONE expression is reassociated by
 *    fold()'s associate/split_tree step into `t | ((t<<8) | 0xFF0000)`, which
 *    swaps $v0/$v1 on the two temps. Splitting it into three statements gives
 *    fold nothing to reassociate and reproduces the target's temp lifetimes
 *    (local-alloc's qty_compare gives the SHORT-lived temps the lower reg, so
 *    the long-lived `x` correctly lands in $v1 and the pair in $v0).
 */
s32 func_8017E434(s32 *a0, s32 a1) {
    s32 t;
    s32 ret;

    if (((Unkstruct_8017DB6C *)a0)->unk30 == 0) {
        t = *(u8 *)(a1 + 1);
    } else {
        t = *(u8 *)(a1 + 2);
    }
    t -= 0x20;
    ret = 1;
    if (t > 0) {
        if (((Unkstruct_8017DB6C *)a0)->unk30 == 0) {
            s32 x = t << 8;
            s32 y = t | 0xFF0000;
            t = x | y;
        } else {
            t = (t << 16) | 0xFFFF;
        }
        *(s32 *)a1 = t;
        ret = 0;
    }
    return ret;
}



extern void (*D_80197184[])(void);

void func_8017E49C(void *a0) {
    D_80197184[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8017E4D8(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(((Unkstruct_80126B58 *)param_1)->unk34, param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    ((Unkstruct_80126B58 *)param_1)->unk2 = ((Unkstruct_80126B58 *)param_1)->unk2 + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C(u8 *a0);
extern void func_8017E574(s32 param_1);

void func_8017E524(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_8017E574(param);
    }
}


void func_8017E56C(void) {
}

// @class: regalloc-order
// @unstuck(P36): none — MATCH (89 ins). Blk8(align1) struct copies + array indexing (IV-base regalloc)
#include "common.h"



extern u32 *D_8019717C[];
extern Blk8 D_80197198[];
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8017E6D8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, PW8017E6D8 *h);

void func_8017E574(s32 param_1) {
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_8019717C[((Unkstruct_80126B58 *)param_1)->unk30];
    CAST_WIDTH(s16, param_1, 0x10) = ((Unkstruct_80126B58 *)param_1)->unk2C;
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_80197198[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8017E6D8(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
        }
    }
}


// @class: regalloc-order
// @unstuck(P36): none — MATCH (223 ins). Giant GTE coord transform. Two levers: (1) vy = {int t=vy-0x10; t+(r&0x1f);}
//   blocks the (r&0x1f)-16 reassoc that materialized -0x10 via `li 0xfff0` (+1 ins); (2) inline the one-shot
//   r0_00+1 stsv arg so it stays a $v0 temp instead of stealing a saved reg from the reused pSVar6.

   /* 8, align 2 -> lwl/lwr copy */
  /* 0x20 */
    /* 4, align 1 -> lwl/lwr */

extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern int rand(void);
extern void func_80017714(void *);

extern SVECTOR_8017E6D8 D_801D542C[4];
extern PW8017E6D8 D_801D544C;
extern PW8017E6D8 D_801D5450;
extern u8 D_801D5454, D_801D5455, D_801D5456, D_801D5458, D_801D5459, D_801D545A;
extern int D_801D545C;




void func_8017E6D8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
                   SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, PW8017E6D8 *h)
{
    MATRIX_8017E6D8 m;
    SVECTOR_8017E6D8 *r0_00;
    SVECTOR_8017E6D8 *pSVar6;
    SVECTOR_8017E6D8 *r0;
    int r;
    int mask;

    func_80013F3C((s32)&m);
    RotMatrixZ(g[0], &m);
    m.t[0] = b[0];
    m.t[1] = b[1];
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801D542C[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801D545C = 0x50000000;
        D_801D5454 = 0;
        D_801D5455 = 0;
        D_801D5456 = 0;
        D_801D5458 = 0;
        D_801D5459 = 0;
        D_801D545A = 0;
    }
    D_801D544C = h[0];
    D_801D5450 = h[1];

    f->vx = f->vx + c->vx;
    f->vy = f->vy + c->vy;
    r = rand();
    mask = f->pad & r;
    if (*(u16 *)(a + 0x12) & 1)
        f->vx = f->vx + mask;
    else
        f->vx = f->vx - mask;
    r = rand();
    { int t = f->vy - 0x10; f->vy = t + (r & 0x1f); }

    gte_ldv0(c);
    gte_rtv0tr();
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rtv0tr();
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rtv0tr();
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rtv0tr();
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rtv0tr();
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rtv0tr();
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8017EA54(param_1, param_2)
s32 param_1;
s32 param_2;
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    SVECTOR sv1;
    SVECTOR sv2;

    sv1.vx = CAST_SIGN(short, param_1, 6);
    sv1.vy = CAST_SIGN(short, param_1, 0xa) + -0x20;
    sv1.vz = CAST_SIGN(short, param_1, 0xe);
    iVar1 = func_8004787C(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    iVar3 = (short)param_2;
    sv2.vy = sv1.vy;
    sv2.vx = sv1.vx - (short)(iVar1 * iVar3 >> 0xc);
    iVar1 = func_80047948(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    sv2.vz = sv1.vz - (short)(iVar1 * iVar3 >> 0xc);
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x8000) != 0) {
        iVar1 = func_8004787C(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
        ((Unkstruct_800B5CB8 *)param_1)->unk6 = sv2.vx + (short)(iVar1 * iVar3 >> 0xc);
        iVar1 = func_80047948(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
        ((Unkstruct_800B5CB8 *)param_1)->unkE = sv2.vz + (short)(iVar1 * iVar3 >> 0xc);
        return 1;
    }
    return 0;
}



/* TU declares func_8017EB8C as void(void) (S35 self-axis) but the asm takes
 * $a0 as a pointer parameter — bind through a private C name. */
extern void aF8017ED80(void *param_1) __asm__("func_8017EB8C");

void aF8017ED80(void *param_1) {
    u8 *a0 = (u8 *)param_1;
    s32 iVar2;

    if (((Unkstruct_8017EB8C *)a0)->unk0 != 0) {
        iVar2 = ((Unkstruct_8017EB8C *)a0)->unkCC;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk8 = ((Unkstruct_8017EB8C *)a0)->unk6;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unkA = ((Unkstruct_8017EB8C *)a0)->unkA;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unkC = ((Unkstruct_8017EB8C *)a0)->unkE;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk10 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk10;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk12 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk12 + ((Unkstruct_8017EB8C *)a0)->unkFC;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk14 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk14;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk18 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk18;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk1A = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk1A;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk1C = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk1C;
        if (((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk4 & 0x80000000) {
            ((Unkstruct_8017EB8C_2 *)iVar2)->unk4 |= 0x80000000;
        } else {
            ((Unkstruct_8017EB8C_2 *)iVar2)->unk4 &= 0x7FFFFFFF;
        }

        iVar2 = ((Unkstruct_8017EB8C *)a0)->unkD0;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk8 = ((Unkstruct_8017EB8C *)a0)->unk6;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unkA = ((Unkstruct_8017EB8C *)a0)->unkA;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unkC = ((Unkstruct_8017EB8C *)a0)->unkE;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk10 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk10;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk12 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk12 + ((Unkstruct_8017EB8C *)a0)->unkFE;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk14 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk14;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk18 = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk18;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk1A = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk1A;
        ((Unkstruct_8017EB8C_2 *)iVar2)->unk1C = ((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk1C;
        if (((Unkstruct_8017EB8C_3 *)*(s32 *)(a0 + 0x20))->unk4 & 0x80000000) {
            ((Unkstruct_8017EB8C_2 *)iVar2)->unk4 |= 0x80000000;
        } else {
            ((Unkstruct_8017EB8C_2 *)iVar2)->unk4 &= 0x7FFFFFFF;
        }
    }
}



/* func_8017ED60 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (open-only h_norm
 * cluster exemplar, 7 members).
 *
 * a0+0x0  : u16 active flag; 0 => early return.
 * a0+0x84 : s16 sound cooldown timer.
 *   cooldown != 0  -> just decrement it.
 *   cooldown == 0  -> try to play a positional sound (RotTransPers screen
 *                     projection of the parent's position, range-gated on
 *                     screen X/Y, volume from the classic div-by-0xF0 /
 *                     div-by-0x1E magic-constant idiom -- byte-proven sibling
 *                     form is func_80181CF0 in this same TU, sndid 0x849 here
 *                     vs 0x961 there), then unconditionally reset the timer
 *                     to 0xA regardless of whether the sound actually played.
 * a0+0xFC / 0xFE : running hit-combo accumulators, bumped by +/-0x280 every
 *                     call (unconditional tail).
 * Tail always calls ((void (*)(void *))func_8017EB8C)(a0) (the TU's canonical decl for this
 * symbol is void(void) -- S35 self-axis -- so this draft binds its own
 * private extern with the asm's real void(void*) shape).
 *
 * Control flow is EXPLICIT goto/label, mirroring source-order block
 * placement (gcc-2.7.2 lays out basic blocks in literal source order, not by
 * fallthrough preference -- see the func_80181CF0 comment, same TU): the
 * cooldown!=0 decrement is the SHORT block and sits out-of-line (jumped to),
 * the cooldown==0 RTP+sound block is the LONG block and sits inline
 * (fallthrough), matching the target's physical layout exactly.
 *
 * MATCH levers (byte-proven, 2026-08-05):
 *  1. Naive `if(old!=0){cool=old-1;}else{...}` folds trivially: reorg.c's
 *     delay-slot filler steals the single-insn decrement into the `bnez`'s
 *     own delay slot and retargets the branch straight to the join label
 *     (2 ins short of target). The target instead keeps a genuine copy
 *     (`addu $v1,$v0,zero`) in the delay slot and a SEPARATE `addiu $v0,$v1,-1`
 *     at the decrement site. Reproduced by pinning a second variable
 *     `register s32 v1 __asm__("$3")`, assigned UNCONDITIONALLY right after
 *     the load (`v1 = old;`) -- the scheduler places that copy in the
 *     branch's delay slot on its own, and the decrement (`cool = v1 - 1`)
 *     can no longer be folded away. `cool` is separately pinned to
 *     `__asm__("$2")` so its other def sites (the three `cool = 0xA` early
 *     exits) don't drift onto $3 by coalescing with v1.
 *  2. The tail's `sh $v0,0x84($s0)` / `addu $a0,$s0,zero` order (store off
 *     the callee-saved pointer BEFORE reloading it into the call-argument
 *     register) needed a `__asm__ __volatile__("":::"memory")` fence right
 *     after the store -- without it, sched1 hoists the independent a0-reload
 *     ahead of the store even when the reload is written later in source.
 *  3. Frame is -0x38, 8 bytes (2 words) larger than the natural -0x30 the
 *     locals alone produce; `pad2[2]` (dead, address never read) inside `L`
 *     reserves them, mirroring func_80181CF0's own "dead aggregate sizes the
 *     frame" idiom.
 */


/* §37/§124 def-side asm-label alias (P30 S1d class lever): the TU declares
 * `extern void func_8017ED60(void);` (L4082, L4091) for callers that invoke it with NO args,
 * while the byte-true definition takes an s32 in $a0 -> `conflicting types`. Neither side can
 * move (a no-prototype escape is illegal once a param promotes), so the DEFINITION gets a
 * private C identifier and binds the emitted symbol with a GNU asm label. Zero blast radius:
 * the TU's declaration never meets the definition, and the emitted symbol is unchanged. */
void aF8017EF54(s32 a0) __asm__("func_8017ED60");

void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern u8   D_800AF648_b __asm__("D_800AF648");
    extern void func_8017EB8C(s32);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    if (((Unkstruct_8017ED60 *)a0)->unk0 == 0) {
        return;
    }

    if (((Unkstruct_8017ED60 *)a0)->unk84 == 0) {
        L.v[0] = ((Unkstruct_8017ED60_2 *)*(s32 *)(a0 + 0x20))->unk48;
        L.v[1] = ((Unkstruct_8017ED60_2 *)*(s32 *)(a0 + 0x20))->unk4C;
        L.v[2] = ((Unkstruct_8017ED60_2 *)*(s32 *)(a0 + 0x20))->unk50;
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

        if (L.flag >= 0 && (u16)(L.sxy[0] + 0xEF) < 0x1DF
                        && (u16)(L.sxy[1] + 0xB3) < 0x167) {
            s32 sx = (s16)L.sxy[0];
            s32 av;

            av = (sx < 0) ? -sx : sx;
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x849, (av | (0x3000 | sx)) & 0xFFFF);
        }
        ((Unkstruct_8017ED60 *)a0)->unk84 = 0xA;
    } else {
        (((Unkstruct_8017ED60 *)a0)->unk84)--;
    }

    ((Unkstruct_8017ED60 *)a0)->unkFC += 0x280;
    ((Unkstruct_8017ED60 *)a0)->unkFE -= 0x280;
    ((void (*)(void *))func_8017EB8C)((void *)a0);
}



extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8 * func_8012913C(s32 arg0);
extern void func_8017EB8C(s32);

void func_8017EF0C(s32 a0)
{

    extern s32  D_801151D4;
    u16 nv[4];
    s32 g;
    s32 s0;
    s32 idx;

    g = D_801151D4;

    if (((Unkstruct_800B5CB8 *)a0)->unk0 != 0) {
        idx = ((Unkstruct_800B5CB8 *)a0)->unk1C & 3;
        switch (idx) {
        case 0:
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            break;
        case 1:
            break;
        case 2:
        case 3:
            s0 = (s32)func_8012913C(0x23);
            if (s0 != 0) {
                *(s16 *)(s0 + 0x6) = ((Unkstruct_800B5CB8 *)a0)->unk6 + (rand() & 0x3F) - 0x20;
                *(s16 *)(s0 + 0xA) = ((Unkstruct_800B5CB8 *)a0)->unkA + (rand() & 0x3F) - 0x30;
                {
                    s32 r = rand();
                    s32 t = ((Unkstruct_800B5CB8 *)a0)->unkE;
                    *(s32 *)(s0 + 0x18) = 0;
                    *(s32 *)(s0 + 0x14) = 0;
                    *(s32 *)(s0 + 0x10) = 0;
                    *(s16 *)(s0 + 0xE) = t + (r & 0x3F) - 0x20;
                }
                *(s16 *)(s0 + 0x34) = (rand() & 0x17FF) + 0x800;
                nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
                nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
                nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
                VectorNormalSS(nv, nv);
                *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)nv[0] >> 6);
                *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)nv[1] >> 6);
                *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)nv[2] >> 6);
            }
            break;
        }
        ((void (*)(s32))func_8017EB8C)(a0);
    }
}



extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017EA54(s32 a0, s32 a1);

void func_8017F0F4(s32 a0)
{
    s16 hi;
    s16 pos;
    s32 sp10[3];
    u16 state;
    s32 ret;

    hi = CAST_SIGN(s16, a0, 0x8A);
    pos = CAST_SIGN(s16, a0, 0xA);

    if (pos >= hi - 8) {
        if (((Unkstruct_800B5CB8 *)a0)->unk48 >= 0) {
            ((Unkstruct_800B5CB8 *)a0)->unk48 = -0x8000;
            ((Unkstruct_800B5CB8 *)a0)->unk14 = ((Unkstruct_800B5CB8 *)a0)->unk14 >> 1;
        }
    } else {
        if (hi + 8 >= pos) {
            if (((Unkstruct_800B5CB8 *)a0)->unk48 <= 0) {
                ((Unkstruct_800B5CB8 *)a0)->unk48 = 0x8000;
                ((Unkstruct_800B5CB8 *)a0)->unk14 = ((Unkstruct_800B5CB8 *)a0)->unk14 >> 1;
            }
        }
    }

    if (((Unkstruct_800B5CB8 *)a0)->unkDC < -0x40000) {
        ((Unkstruct_800B5CB8 *)a0)->unkDC = -0x40000;
    }

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = ((Unkstruct_800B5CB8 *)a0)->unkDC;
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
    func_8012CBCC(a0);

    state = ((Unkstruct_800B5CB8 *)a0)->unk34;
    switch (state) {
    case 0: {
        s32 s0v;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_8017EA54(a0, 0x51) == 0) {
                goto set_state1;
            }
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s0v);
        v1p = ((Unkstruct_800B5CB8 *)a0)->unk20;
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 8);
        p20 = ((Unkstruct_800B5CB8 *)a0)->unk20;
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 &= 0xFFF;
        ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
        break;
    }
    case 1: {

        ((Unkstruct_800B5CB8 *)a0)->unkDC = ((Unkstruct_800B5CB8 *)a0)->unkDC << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_8017EA54(a0, 0x51) == 0) {
            goto end_switch;
        }
        goto rand_tail;
    }
    case 2: {
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        p744 = func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88));
        v1p = ((Unkstruct_800B5CB8 *)a0)->unk20;
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 0x10);
        p20 = ((Unkstruct_800B5CB8 *)a0)->unk20;
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = ((Unkstruct_800B5CB8 *)a0)->unk20;
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        ((Unkstruct_800B5CB8 *)a0)->unkDC = ((Unkstruct_800B5CB8 *)a0)->unkDC >> 1;
        func_8017EA54(a0, 0x51);
        if (((Unkstruct_800B5CB8 *)a0)->unk102 == 0) {
            ((Unkstruct_800B5CB8 *)a0)->unk34 = 3;
        } else {
            ((Unkstruct_800B5CB8 *)a0)->unk102 = ((Unkstruct_800B5CB8 *)a0)->unk102 - 1;
        }
        break;
    }
    case 3: {
        s32 s2v;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        ((Unkstruct_800B5CB8 *)a0)->unkDC = ((Unkstruct_800B5CB8 *)a0)->unkDC << 1;
        if (func_8017EA54(a0, 0x51) != 0) {
            goto rand_tail;
        }
        if (ret <= 0x40000) {
            goto set_state1;
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s2v);
        v1p = ((Unkstruct_800B5CB8 *)a0)->unk20;
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 1);
        if ((u32)(b608 + 0xFF) < 0x1FF) {
            goto end_switch;
        }
        goto rand_tail;
    }
    }
    goto end_switch;

rand_tail:
    ((Unkstruct_800B5CB8 *)a0)->unk34 = 2;
    {
        s32 r = rand();
        ((Unkstruct_800B5CB8 *)a0)->unk102 = (r & 7) + 8;
    }
    goto end_switch;

set_state1:
    ((Unkstruct_800B5CB8 *)a0)->unk34 = 1;

end_switch:
    if (((Unkstruct_800B5CB8 *)a0)->unk100 != 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk100 = ((Unkstruct_800B5CB8 *)a0)->unk100 - 1;
    } else {
        s32 ret3;

        ret3 = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret3 <= 0x24000) {
            ((Unkstruct_800B5CB8 *)a0)->unk2 = 2;
            ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x3C;
        }
    }
}




extern void func_80180354(s32, s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);


void func_8017F430(s32 param_1)
{
    extern u8 D_800AF648_b __asm__("D_800AF648");

    extern u8 D_801AAF24;
    extern u8 D_801AAF2C;
    extern u8 D_801AAF34;
    extern u8 D_800AF648;
    /* L5: slot offsets are exact only through ONE struct — copied verbatim
       from the banked RTP_SND sibling func_80180CA8 (same TU) so the
       sp+0x10.."0x2B layout reproduces byte-for-byte. */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s16 sVar1;
    s32 s0;

    if (((Unkstruct_800B5CB8 *)param_1)->unk1C == 0) {
        sVar1 = ((Unkstruct_800B5CB8 *)param_1)->unk100 - 1;
        ((Unkstruct_800B5CB8 *)param_1)->unk100 = sVar1;
        if (sVar1 == 0) {
            ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
            ((Unkstruct_800B5CB8 *)param_1)->unk100 = 0x3c;
            ((Unkstruct_800B5CB8 *)param_1)->unk8A = CAST_SIGN(s16, param_1, 0xa) - 0x140;
        } else {
            ((Unkstruct_800B5CB8 *)param_1)->unk1C = (sVar1 == 1) ? 0x3c : 3;

            ((s32 (*)(s32, s32))func_80180354)(param_1, (s32)&D_801AAF24);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x34, (s32)&D_801AAF2C, (s32)L.nv);
                ((Unkstruct_800B5CB8 *)s0)->unk6  = L.nv[0];
                ((Unkstruct_800B5CB8 *)s0)->unkA = L.nv[1];
                ((Unkstruct_800B5CB8 *)s0)->unkE = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x34, (s32)&D_801AAF34, (s32)L.nv);
                ((Unkstruct_800B5CB8 *)s0)->unk6  = L.nv[0];
                ((Unkstruct_800B5CB8 *)s0)->unkA = L.nv[1];
                ((Unkstruct_800B5CB8 *)s0)->unkE = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk48;
            L.rv[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk4C;
            L.rv[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk50;
            { void *r4; r4 = &D_800AF648; func_8004914C(r4); }
            { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
            RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
            if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                          && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                s32 x = (s16)L.sxy[0];
                s32 ax;

                ax = x;
                if (x < 0) {
                    ax = -x;
                }
                ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                x = (x + 0xF0) / 0x1E;
                if (x == 0x10) {
                    x = 0xF;
                }
                x = x << 8;
                {
                    s32 flg = 0x3000;
                    func_8002D4C8(0x84A, ((ax | flg) | x) & 0xFFFF);
                }
            }
        }
    } else {
        ((Unkstruct_800B5CB8 *)param_1)->unk1C = ((Unkstruct_800B5CB8 *)param_1)->unk1C - 1;
    }
}











void func_8017F6D8(s32 a0)
{

    extern s16 D_801AAF3C[];
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    switch (((Unkstruct_8017F6D8 *)a0)->unk34) {
    case 0:
    {
        s16 idx = ((Unkstruct_8017F6D8 *)a0)->unk70;
        s16 *p = &D_801AAF3C[(idx - 1) * 4];
        s16 gx = *(s16 *)&D_80126B5E;
        s16 gz;
        s32 p20;

        if (!(*p < gx)) {
            break;
        }
        p++;
        if (!(gx < *p)) {
            break;
        }
        p++;
        gz = *(s16 *)&D_80126B66;
        if (!(*p < gz)) {
            break;
        }
        if (!(gz < p[1])) {
            break;
        }

        p20 = ((Unkstruct_8017F6D8 *)a0)->unk20;
        *(u32 *)(p20 + 4) = *(u32 *)(p20 + 4) & 0x7FFFFFFF;

        {
            s32 t;

            CAST_ALIAS(s16, a0, 0x88) = D_80126B5E;
            CAST_ALIAS(s16, a0, 0x6)  = D_80126B5E;
            t = D_80126B62 - 0x80;
            CAST_ALIAS(s16, a0, 0x8A) = t;

            t = ((Unkstruct_8017F6D8 *)a0)->unk34;
            {
                s16 z;
                z = D_80126B66;
                ((Unkstruct_8017F6D8 *)a0)->unk34 = (t + 1);
                ((Unkstruct_8017F6D8 *)a0)->unk8C = z;
                ((Unkstruct_8017F6D8 *)a0)->unkE  = z;
            }
        }
        break;
    }
    case 1:
    {
        s16 v;

        v = ((Unkstruct_8017F6D8 *)a0)->unkA + 8;
        ((Unkstruct_8017F6D8 *)a0)->unkA = v;
        if (v < ((Unkstruct_8017F6D8 *)a0)->unk8A) {
            break;
        }
        ((Unkstruct_8017F6D8 *)a0)->unk2 = 1;
        ((Unkstruct_8017F6D8 *)a0)->unk34 = 0;
        break;
    }
    }
}


extern s32 D_801AAF5C[];
extern s32 func_8012C044(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C098(void *a0);
extern void func_8017ED60();  // K&R: 0 of 1 args (P37 rung D t4_D1)

void func_8017F808(s32 a0)
{
    void (*handler)(s32);

    handler = (void (*)(s32))D_801AAF5C[CAST_SIGN(u16, a0, 0x2)];
    handler(a0);

    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0)
        return;

    ((void (*)(s32))func_8017ED60)(a0);

    if (func_8012C044(a0) == 0)
        return;

    if (((Unkstruct_800B5CB8 *)a0)->unk70 == 0) {
        if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0)
            func_80016714(CAST_SIGN(void *, a0, 0xCC), 0x84);
        if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0)
            func_80016714(CAST_SIGN(void *, a0, 0xD0), 0x84);
        func_8012C098((void *)a0);
    } else {
        if (CAST_SIGN(u16, a0, 0x2) < 4)
            ((Unkstruct_800B5CB8 *)a0)->unk2 = 4;
    }
}



extern void (*D_801AAF88[])(void);

void func_8017F8E0(void *a0) {
    D_801AAF88[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern s32 D_801AAF90;
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

void func_8017F91C(s32 a0)
{
    SV4 in;
    SV4 out;
    u16 uStack_c;

    if (((Unkstruct_800B5CB8 *)a0)->unk34 == 0) {
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
            *(u16 *)(*(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk64 + 0x20) + 0x12);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, ((Unkstruct_800B5CB8 *)a0)->unk70 * 12 + (s32)&D_801AAF90);

        in.v[0] = 0;
        in.v[1] = 0;
        in.v[2] = 0x10;
        func_8012F214(a0, (s32)&in, (s32)&out);
        ((Unkstruct_800B5CB8 *)a0)->unk6 = out.v[0];
        ((Unkstruct_800B5CB8 *)a0)->unkA = out.v[1];
        uStack_c = out.v[2];
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x5a;
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unkE = uStack_c;
    }

    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 += -0x80;
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 += 4;
    *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) += CAST_SIGN(u16, a0, 0xfc);

    ((Unkstruct_800B5CB8 *)a0)->unkDC = ((Unkstruct_800B5CB8 *)a0)->unk14;
    if ((((s32 (*)(s32))func_8012CBCC)(a0)) & 0x6000) {
        ((Unkstruct_800B5CB8 *)a0)->unk14 = -((Unkstruct_800B5CB8 *)a0)->unkDC;
        if (--((Unkstruct_800B5CB8 *)a0)->unkAC == 0) {
            func_8012C218((void *)a0);
        }
    }

    {
        s32 iVar3 = ((Unkstruct_800B5CB8 *)a0)->unk1C - 1;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = iVar3;
        if (iVar3 == 0) {
            func_8012C218((void *)a0);
        }
    }
}



extern void (*D_801AAFA8[])(void);

void func_8017FA90(void *a0) {
    D_801AAFA8[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_8017FACC(s32 a0)
{
    if (((Unkstruct_800B5CB8 *)a0)->unk70 != 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 4;
        ((Unkstruct_800B5CB8 *)a0)->unk5C = 0;
        CAST_WIDTH(u16, a0, 0x5E) = 0;
        ((Unkstruct_800B5CB8 *)a0)->unkC1 = 0;
        return;
    }

    if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0)
        func_80016714(CAST_SIGN(void *, a0, 0xCC), 0x84);

    if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0)
        func_80016714(CAST_SIGN(void *, a0, 0xD0), 0x84);

    func_8002A04C(a0);
    func_8012C218((void *)a0);
}



extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8017EB8C(s32);

void func_8017FB54(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8017EB8C)(a0);
}




extern void func_8017ED60();  // K&R: 0 of 1 args (P37 rung D t4_D1)
    void func_8017FB8C(s32 *param) {
        ((Unkstruct_8017FB8C_2 *)*(s32 *)((char *)param + 0x20))->unk10 = 0xE00;
        func_8017ED60();
    }




extern void func_8017ED60();  // K&R: 0 of 1 args (P37 rung D t4_D1)
    void func_8017FBB4(s32 arg0) {
        s32 temp_v1 = ((Unkstruct_8017FBB4 *)arg0)->unk20;
        ((Unkstruct_8017FBB4_2 *)temp_v1)->unk10 += 0x20;
        ((void (*)(void))func_8017ED60)();
    }


extern void func_80131E00(s32 a0, s32 a1);
extern void func_8017ED60();  // K&R: 0 of 1 args (P37 rung D t4_D1)

void func_8017FBE8(s32 a0) {
    if (((Unkstruct_8017FBE8_3 *)a0)->unk76 < 0) {
        func_80131E00(a0, 6);
        return;
    }
    ((Unkstruct_8017FBE8_3 *)a0)->unk2 = 1;
    ((Unkstruct_8017FBE8_3 *)a0)->unk100 = 0x3C;
    ((Unkstruct_8017FBE8_3 *)a0)->unk34 = 0;
    func_8017ED60();
}



extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_8017ED60();  // K&R: 0 of 1 args (P37 rung D t4_D1)

void func_8017FC34(s32 a0)
{
    s32 s0;

    if (((Unkstruct_8017FC34_2 *)a0)->unk0 != 0) {
        s0 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
        if (s0 != 0) {
            ((Unkstruct_8017FC34 *)s0)->unk6 = ((Unkstruct_8017FC34_2 *)a0)->unk6 + (rand() & 0x3F) - 0x20;
            ((Unkstruct_8017FC34 *)s0)->unkA = ((Unkstruct_8017FC34_2 *)a0)->unkA + (rand() & 0x3F) - 0x30;
            ((Unkstruct_8017FC34 *)s0)->unkE = ((Unkstruct_8017FC34_2 *)a0)->unkE + (rand() & 0x3F) - 0x20;
            ((Unkstruct_8017FC34 *)s0)->unk10 = -((Unkstruct_8017FC34_2 *)a0)->unk10;
            ((Unkstruct_8017FC34 *)s0)->unk14 = -((Unkstruct_8017FC34_2 *)a0)->unk14;
            ((Unkstruct_8017FC34 *)s0)->unk18 = -((Unkstruct_8017FC34_2 *)a0)->unk18;
            ((Unkstruct_8017FC34_3 *)*(s32 *)(s0 + 0x20))->unk18 = 0x800;
            ((Unkstruct_8017FC34_3 *)*(s32 *)(s0 + 0x20))->unk1A = 0x800;
        }
        ((void (*)(s32))func_8017ED60)(a0);
    }
}


extern void func_8017EB8C(s32 arg0);
    void func_8017FD20(s32 *a0) {
        ((Unkstruct_8017FD20 *)a0)->unk10 = ((Unkstruct_8017FD20 *)a0)->unk10 >> 1;
        ((Unkstruct_8017FD20 *)a0)->unk18 = ((Unkstruct_8017FD20 *)a0)->unk18 >> 1;
        ((void (*)(s32 *))func_8017EB8C)(a0);
    }


extern void func_8017EB8C(s32 arg0);
    void func_8017FD54(u8 *param_1) {
        param_1[0xC1] = 0xC;
        ((Unkstruct_8017FD54_2 *)param_1)->unk1C = 0x3C;
        ((void (*)(void))func_8017EB8C)();
    }


#include "common.h"

/* func_8017FD80 (ov_SC06_018_jr_8017C24C) — card twin ov_SC06_008:func_8017FF74 (banked),
 * mirrored spelling: block-scope externs, direct BEE8 test, bare & 0x2000, cast idiom.
 * Tail callee is func_8017EB8C in THIS binary (twin's func_8017ED80 == same source fn,
 * cf. this TU's aF8017ED80 __asm__("func_8017EB8C") alias); kept (s32)-proto for
 * compatibility with this TU's earlier decls.
 */

void func_8017FD80(s32 a0)
{
    extern void func_801319E0(s32 a0);
    extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
    extern s32 func_8012CBF4(s32 a0);
    extern void func_80131C78(s32 a0);
    extern void func_80131E00(int a0, int a1);
    extern void func_8017EB8C(s32 a0);
    s16 field_a;
    s32 result;

    field_a = CAST_SIGN(s16, a0, 0xA);
    if (field_a >= 0x10) {
        func_801319E0(a0);
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_80131E00(a0, 6);
        } else {
            result = ((s32 (*)(s32))func_8012CBF4)(a0);
            if (result & 0x2000) {
                func_80131C78(a0);
            }
            ((void (*)(s32))func_8017EB8C)(a0);
        }
    }
}


void func_8017FE0C(s32 a0) {

    extern s32 func_8012C354(s32 a0, s32 a1);
    extern s32 func_80143970(s32 a0);
    extern void func_8012A828(s32 a0, void * a1);
    extern void func_8012B200(u8 *a0);
    extern void func_8012C1B8(void);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_80016714(void *a0, s32 a1);
    extern void func_8012CAE4(void *a0);
    extern u8 D_801AAE28[];
    extern u8 D_801ACB68[];
    extern u8 D_801AAE5C[];
    extern u8 D_801AC878[];
    extern u8 D_801ACB50[];
    extern u8 D_80193900[];

    s32 s0;
    u16 t;

    if (func_8012C354(a0, D_801AAE28) == 0) {
        return;
    }
    ((Unkstruct_800B5CB8 *)a0)->unkC0 = 1;
    ((Unkstruct_800B5CB8 *)a0)->unkB4 = -0x1001;
    ((s32 (*)(s32))func_80143970)(a0);
    func_8012A828(a0, D_801ACB68);
    CAST_SIGN(u16, a0, 0x2) += 1;
    func_8012B200((u8 *)a0);
    ((Unkstruct_800B5CB8 *)a0)->unkBC = (s32)D_801AAE5C;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        goto fail;
    }
    ((Unkstruct_800B5CB8 *)a0)->unkCC = s0;
    func_8001C214(s0, (s32)D_801AC878);
    t = ((Unkstruct_800B5CB8 *)s0)->unk2C | 0x10;
    ((Unkstruct_800B5CB8 *)s0)->unk20 = *(s32 *)D_80193900;
    ((Unkstruct_800B5CB8 *)s0)->unk2C = t;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        func_80016714((void *)((Unkstruct_800B5CB8 *)a0)->unkCC, 0x84);
fail:
        func_8012CAE4(a0);
        return;
    }
    ((Unkstruct_800B5CB8 *)a0)->unkD0 = s0;
    func_8001C214(s0, (s32)D_801ACB50);
    t = ((Unkstruct_800B5CB8 *)s0)->unk2C | 0x10;
    ((Unkstruct_800B5CB8 *)s0)->unk20 = *(s32 *)D_80193900;
    ((Unkstruct_800B5CB8 *)s0)->unk2C = t;
    ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x3C;
    ((Unkstruct_800B5CB8 *)a0)->unkDC = 0xFFFC0000;
}




extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern s32 func_8017EA54(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);

void func_8017FF34(s32 a0)
{

    extern s32 D_80126B60;
    s32 sp10[3];

    if (CAST_WIDTH(s32, a0, 8) >= D_80126B60 - 0x200000) {
        if (((Unkstruct_800B5CB8 *)a0)->unk48 >= 0) {
            ((Unkstruct_800B5CB8 *)a0)->unk48 = -0x8000;
            ((Unkstruct_800B5CB8 *)a0)->unk14 = ((Unkstruct_800B5CB8 *)a0)->unk14 >> 1;
        }
    } else {
        if (D_80126B60 - 0x180000 >= CAST_WIDTH(s32, a0, 8)) {
            if (((Unkstruct_800B5CB8 *)a0)->unk48 <= 0) {
                ((Unkstruct_800B5CB8 *)a0)->unk48 = 0x8000;
                ((Unkstruct_800B5CB8 *)a0)->unk14 = ((Unkstruct_800B5CB8 *)a0)->unk14 >> 1;
            }
        }
    }

    ((Unkstruct_800B5CB8 *)a0)->unkDC = ((Unkstruct_800B5CB8 *)a0)->unkDC >> 1;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = ((Unkstruct_800B5CB8 *)a0)->unkDC;
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
    func_8012CBCC(a0);
    func_8017EA54(a0, 0x51);

    *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12) += func_8012B8E4(a0, 0x10);
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 &= 0xFFF;

    CAST_SIGN(u16, a0, 0x100) -= 1;
    if (((Unkstruct_800B5CB8 *)a0)->unk100 == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 3;
        ((Unkstruct_800B5CB8 *)a0)->unk100 = 5;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0;
    }
}





void func_80180068(s32 a0) {
    s32 p;
    s32 q;

    p = ((Unkstruct_80180068 *)a0)->unk20;
    ((Unkstruct_80180068 *)a0)->unk6 = 0x7FFF;
    ((Unkstruct_80180068 *)a0)->unkA = -0x1000;
    ((Unkstruct_80180068 *)a0)->unk2 = 5;
    ((Unkstruct_80180068 *)a0)->unk34 = 0;
    ((Unkstruct_80180068 *)a0)->unk1C = 0x12C;
    ((Unkstruct_80180068_2 *)p)->unk4 |= 0x80000000;
    q = ((Unkstruct_80180068 *)a0)->unk20;
    ((Unkstruct_80180068_2 *)q)->unk1C = 0x1000;
    ((Unkstruct_80180068_2 *)q)->unk1A = 0x1000;
    ((Unkstruct_80180068_2 *)q)->unk18 = 0x1000;
    ((Unkstruct_80180068 *)a0)->unk76 = 0x1E0;
    ((Unkstruct_80180068 *)a0)->unk5C = 0x8810;
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void * a1);

void func_801800C8(s32 param_1) {

    extern u8 D_801ACC48[];
    extern u8 D_80193900[];

    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    ((Unkstruct_800B5CB8 *)param_1)->unk20 = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(v0, (s32)D_801ACC48);
        func_8012A828(param_1, D_80193900);
        ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
        ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0x40;
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk10 =
            *(u16 *)(*(s32 *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x10);
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12 =
            *(u16 *)(*(s32 *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x12);
        *(u16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x14) =
            *(u16 *)(*(s32 *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x14);
    }
}




extern void func_8012AD80(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B370(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

extern s32 D_801AAF74;
extern s32 D_801AAF80;
extern u8 D_800D3918[];

void func_80180188(s32 a0)
{
    s32 v0;

    if (CAST_SIGN(s16, a0, 6) == *(s16 *)(a0 + 0xDE) &&
        CAST_SIGN(s16, a0, 0xE) == *(s16 *)(a0 + 0xE2)) {
        func_8012C218((void *)a0);
    } else {
        ((Unkstruct_800B5CB8 *)a0)->unkDC = CAST_WIDTH(s32, a0, 4);
        ((Unkstruct_800B5CB8 *)a0)->unkE0 = CAST_WIDTH(s32, a0, 0xC);
        func_8012B14C(a0, (s32)&D_801AAF74);
        func_8012AD80(a0);

        if (func_8012D5E4(a0, (s32)&D_801AAF80, (s32)&D_800D3918, 0x30) != 0) {
            func_8012C218((void *)a0);
        } else {
            v0 = ((Unkstruct_800B5CB8 *)a0)->unk1C - 1;
            ((Unkstruct_800B5CB8 *)a0)->unk1C = v0;
            if (v0 == 0) {
                func_8012C218((void *)a0);
            } else {
                func_8012B370(a0);
            }
        }
    }
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 rand(void);
extern u8 D_801ACD08[];

void func_8018025C(s32 param_1)
{
    ((Unkstruct_800B5CB8 *)param_1)->unk20 = ((s32 (*)(void))func_8012C1B8)();
    if (((Unkstruct_800B5CB8 *)param_1)->unk20 == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(((Unkstruct_800B5CB8 *)param_1)->unk20, (s32)D_801ACD08);

        ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
        ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
        {
            s32 v1 = ((Unkstruct_800B5CB8 *)param_1)->unk64;
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_80047948(*(s16 *)(t + 0x12));
            CAST_WIDTH(s32, param_1, 0xC) = CAST_WIDTH(s32, param_1, 0xC) + (r << 8);
        }
        {
            s32 v1 = ((Unkstruct_800B5CB8 *)param_1)->unk64;
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_8004787C(*(s16 *)(t + 0x12));
            CAST_WIDTH(s32, param_1, 0x4) = CAST_WIDTH(s32, param_1, 0x4) + (r << 8);
        }
        {
            s32 t = ((Unkstruct_800B5CB8 *)param_1)->unk20;
            *(u16 *)(t + 0x2C) = *(u16 *)(t + 0x2C) | 0x10;
        }
        {
            s32 t = ((Unkstruct_800B5CB8 *)param_1)->unk20;
            *(s16 *)(t + 0x18) = 0x1800;
        }
        {
            s32 t = ((Unkstruct_800B5CB8 *)param_1)->unk20;
            *(s16 *)(t + 0x1A) = 0x1800;
        }
        {
            s32 t = ((Unkstruct_800B5CB8 *)param_1)->unk20;
            *(s16 *)(t + 0x1C) = 0x1800;
        }

        ((Unkstruct_800B5CB8 *)param_1)->unkAC = 2;
        {
            s32 r = rand();
            ((Unkstruct_800B5CB8 *)param_1)->unkFC = r & 0xFF;
        }
    }
}


extern s32 D_801D55A0;
extern s32 func_8012C588(s32 a0, s32 a1);

void func_80180354(s32 a0, s32 a1) {
    D_801D55A0 = a1;
    ((void (*)(s32, s32))func_8012C588)(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801D55A0;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @unstuck(P36): none — MATCH (145/145 ins, match_one confirmed)




s32 func_80180384(s32 param_1) {

    extern M2C_UNK D_80193900;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801ACD24;
    extern MATRIX *D_801ACD58;     /* matrix pool cursor */
    extern MATRIX D_801D5580[];    /* matrix pool end */

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    MATRIX *m;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801ACD24) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80193900));
    iVar5 = ((Unkstruct_80180384 *)param_1)->unk20;
    ((Unkstruct_80180384 *)param_1)->unk70 = 0x80;
    ((Unkstruct_80180384_2 *)iVar5)->unk4 |= 0x50000040;
    ((Unkstruct_80180384_2 *)iVar5)->unk2C |= 1;
    iVar8 = ((Unkstruct_80180384_3 *)*(s32 *)(param_1 + 0x64))->unk20 + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801D55A0, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* take the next matrix from the pool (wraps near the end); the post-increment
       is what keeps the load in $v0 and the copy into $s1. */
    m = D_801ACD58++;
    *(MATRIX **)(param_1 + 0xcc) = m;
    if (D_801ACD58 > D_801D5580) {
        D_801ACD58 = D_801D5580 - 9;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, m);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)m);

    uVar3 = CAST_NONSTRUCT(u16, (char *)&s50, 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)CAST_NONSTRUCT(s16, (char *)&s50, 2) < 0x80) {
        CAST_NONSTRUCT(s16, (char *)&s50, 2) = CAST_NONSTRUCT(s16, (char *)&s50, 2) - 4;
        m = D_801ACD58++;
        *(MATRIX **)(param_1 + 0xd0) = m;
        if (D_801ACD58 > D_801D5580) {
            D_801ACD58 = D_801D5580 - 9;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), m);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)m);
    }
    ((Unkstruct_80180384 *)param_1)->unk2 = ((Unkstruct_80180384 *)param_1)->unk2 + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(void *a0);


// @class: regalloc-order
// @unstuck(P36): none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_801805C8(s32 param_1) {

    extern signed char D_801ACD10[];
    int self = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    do { iVar1 = ((Unkstruct_800B5CB8 *)self)->unk1C; } while (0);
    iVar6 = ((Unkstruct_800B5CB8 *)self)->unk20;
    ((Unkstruct_800B5CB8 *)self)->unk1C = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801ACD10;
        i = 0;
        dest = ((Unkstruct_800B5CB8 *)self)->unkCC;
        t = *(unsigned short *)(self + 0x70);
        *(short *)(buf + 0x0c) = 0;
        *(short *)(buf + 0x0a) = 0;
        *(short *)(buf + 0x08) = 0;
        *(short *)(buf + 0x1c) = 0;
        *(short *)(buf + 0x14) = 0;
        *(short *)(buf + 0x04) = 0;
        buf[0x22] = 0;
        buf[0x21] = 0;
        buf[0x20] = 0;
        buf[0x2a] = 0;
        buf[0x29] = 0;
        buf[0x28] = 0;
        buf[0x2e] = 0;
        buf[0x2d] = 0;
        buf[0x2c] = 0;
        *(int *)(buf + 0x30) = 0x50000000;
        buf[0x25] = t;
        buf[0x26] = t;
        buf[0x24] = t;
        do {
            *(short *)(buf + 0x00) = *p++;
            *(short *)(buf + 0x02) = *p++;
            *(short *)(buf + 0x10) = *p++;
            *(short *)(buf + 0x12) = *p++;
            *(short *)(buf + 0x18) = *p++;
            *(short *)(buf + 0x1a) = *p--;
            func_80017758(buf, (void *)dest);
            i++;
        } while (i < 4);

        td = ((Unkstruct_800B5CB8 *)self)->unkD0;
        if (td != 0) {
            dest = td;
            p = D_801ACD10;
            i = 0;
            t = *(unsigned short *)(self + 0x70);
            *(short *)(buf + 0x0c) = 0;
            *(short *)(buf + 0x0a) = 0;
            *(short *)(buf + 0x08) = 0;
            *(short *)(buf + 0x1c) = 0;
            *(short *)(buf + 0x14) = 0;
            *(short *)(buf + 0x04) = 0;
            buf[0x22] = 0;
            buf[0x21] = 0;
            buf[0x20] = 0;
            buf[0x2a] = 0;
            buf[0x29] = 0;
            buf[0x28] = 0;
            buf[0x2e] = 0;
            buf[0x2d] = 0;
            buf[0x2c] = 0;
            *(int *)(buf + 0x30) = 0x50000000;
            buf[0x25] = t;
            buf[0x26] = t;
            buf[0x24] = t;
            do {
                *(short *)(buf + 0x00) = *p++;
                *(short *)(buf + 0x02) = *p++;
                *(short *)(buf + 0x10) = *p++;
                *(short *)(buf + 0x12) = *p++;
                *(short *)(buf + 0x18) = *p++;
                *(short *)(buf + 0x1a) = *p--;
                func_80017758(buf, (void *)dest);
                i++;
            } while (i < 4);
        }
        do { ((Unkstruct_800B5CB8 *)self)->unk70 = ((Unkstruct_800B5CB8 *)self)->unk70 >> 1; } while (0);
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        func_8012C218((void *)self);
    }
}



extern void (*D_801ACD5C[])(void);

void func_80180868(void *a0) {
    D_801ACD5C[((Unkstruct_80126B58 *)a0)->unk2]();
}


// @class: schedule
// @unstuck(P36): none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_801808A4(int param_1, short param_2)
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    SVECTOR sv1;
    SVECTOR sv2;

    if (((Unkstruct_800B5CB8 *)param_1)->unkDC != 0) goto ret0;
    sv1.vx = CAST_SIGN(short, param_1, 6);
    sv1.vy = CAST_SIGN(short, param_1, 0xa) + -0x20;
    sv1.vz = CAST_SIGN(short, param_1, 0xe);
    iVar1 = func_8004787C(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    iVar3 = (int)param_2;
    sv2.vy = sv1.vy;
    sv2.vx = sv1.vx - (short)(iVar1 * iVar3 >> 0xc);
    iVar1 = func_80047948(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    sv2.vz = sv1.vz - (short)(iVar1 * iVar3 >> 0xc);
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x8000) != 0) {
        iVar1 = func_8004787C(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
        ((Unkstruct_800B5CB8 *)param_1)->unk6 = sv2.vx + (short)(iVar1 * iVar3 >> 0xc);
        iVar1 = func_80047948(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
        ((Unkstruct_800B5CB8 *)param_1)->unkE = sv2.vz + (short)(iVar1 * iVar3 >> 0xc);
        return 1;
    }
    iVar1 = func_8004787C(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    sv1.vx = CAST_SIGN(short, param_1, 6) - (short)(iVar1 * iVar3 >> 0xc);
    sv1.vy = CAST_SIGN(short, param_1, 0xa) + -0x10;
    iVar1 = func_80047948(*(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) & 0xfff);
    sv1.vz = CAST_SIGN(short, param_1, 0xe) - (short)(iVar1 * iVar3 >> 0xc);
    sv2.vx = sv1.vx;
    sv2.vy = sv1.vy + 0x20;
    sv2.vz = sv1.vz;
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x6000) == 0) goto docopy;
ret0:
    return 0;
docopy:
    CAST_WIDTH(int, param_1, 4) = CAST_WIDTH(int, param_1, 0x38);
    CAST_WIDTH(int, param_1, 8) = *(int *)(param_1 + 0x3c);
    CAST_WIDTH(int, param_1, 0xc) = *(int *)(param_1 + 0x40);
    return 1;
}




/* func_80180AB4 — ov_SC06_008 / ov_SC06_008_jr_8017C294
 *
 * Two-arm actor tick keyed on the s16 countdown at actor+0xFC:
 *   arm A (counter == 0, the FALL-THROUGH / longer block): three func_8012C658
 *     spawns with offset pokes, a sound cue, two child-actor state pokes, an
 *     8-iteration 0x281 particle burst, then the RTP positional-sound block
 *     (the byte-proven RTP_SND shape from ov_SC03_099_jr_8017BEBC.c:5406).
 *   arm B (counter != 0): a func_8012913C(0x23) spawn scattered around the
 *     actor, VectorNormalSS toward D_801151D4->{0x5C,0x60,0x64}, sound 0xAF8.
 *
 * Declarations copied VERBATIM from the TU (one-pass grep, D2):
 *   D_801151D4      src/ov_SC06_008/ov_SC06_008_jr_8017C294.c:323
 *   rand            :956
 *   VectorNormalSS  :1849
 *   func_8012C658   :2523
 *   func_8012C588   :3767
 *   func_8012C218   :3782
 *   func_8002D4C8   :59
 *   func_8004914C   :2645
 *   func_800491AC   :2646
 *   func_8012913C   :4356  (non-prototype form, BELOW the splice point)
 *   func_8002AC00   :5447  (block-scope extern only)
 * RotTransPers / D_800AF648 / func_8002A04C are not in this TU -> fleet-dominant forms.
 */

extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8 * func_8012913C(s32 arg0);

void func_80180AB4(s32 a0)
{

    extern s32  D_801151D4;
    extern u8 D_800AF648;
    extern u8 D_800AF648_b __asm__("D_800AF648");

    /* L5: slot offsets are exact only through ONE struct — plain array locals
       get 8-byte-rounded slots and pushed z/flag to 0x28/0x2C (measured). */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s32 g;
    s32 s0;
    s32 i;

    g = D_801151D4;

    if (((Unkstruct_800B5CB8 *)a0)->unkFC == 0) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);

        s0 = ((Unkstruct_800B5CB8 *)a0)->unkCC;
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;
        s0 = ((Unkstruct_800B5CB8 *)a0)->unkD0;
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x30;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.rv[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
        L.rv[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
        L.rv[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
        RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;

            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }
        func_8002A04C(a0);
        func_8012C218((void *)a0);
    } else {
        s0 = (s32)func_8012913C(0x23);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = ((Unkstruct_800B5CB8 *)a0)->unk6 + (rand() & 0x7F) - 0x40;
            *(s16 *)(s0 + 0xA) = ((Unkstruct_800B5CB8 *)a0)->unkA + (rand() & 0x7F) - 0xE0;
            {
                s32 r = rand();
                s32 t = ((Unkstruct_800B5CB8 *)a0)->unkE;
                *(s16 *)(s0 + 0x34) = 0x1800;
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = t + (r & 0x7F) - 0x40;
            }
            L.nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
            L.nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
            L.nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
            VectorNormalSS(L.nv, L.nv);
            *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
            *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
            *(s16 *)(s0 + 0x34) = 0x3000;
            func_8002D4C8(0xAF8, 0);
        }
        ((Unkstruct_800B5CB8 *)a0)->unkFC = CAST_SIGN(u16, a0, 0xFC) - 1;
    }
}




// TARGET: func_80180EB8  (ov_SC06_008, TU ov_SC06_008_jr_8017C294.c, 93 ins)
//
// Template: func_801821F8 in this SAME TU (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c,
// around line 5283) is an already-MATCHED sibling (126 ins) with a documented byte-exact
// idiom set (its comment, verbatim):
//   @class: plumbing
//   @unstuck(P36): none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//     lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//     `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//     (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//     hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//     the `< 1` test.
//
// func_80180EB8 is the SAME body with the leading "if (*(short*)(param_1+0xfc)==0) {...}" block
// (the 0x64-indirected 3x int-copy + 3x u16-copy prologue) removed, and the "already fired" gate
// field is 0xe2 instead of 0x102. Confirmed against the target .s: no reference anywhere to 0xfc,
// 0x64, or 0x102/0x20 offsets; the gate compare is `lh $v1, 0xE2($s0)` / `sh $v1(=0xA), 0xE2($s0)`.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_80180EB8(int param_1)
{
    extern unsigned char D_801AD450[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    ((Unkstruct_800B5CB8 *)param_1)->unkC1 = 0;
    CAST_WIDTH(short, param_1, 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xe2) == 0) {
        *(short *)(param_1 + 0xe2) = 10;
        *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0x4000;
        func_8002D4C8(0x9b7, 0);
        if (((Unkstruct_800B5CB8 *)param_1)->unk60 != 0) {
            if (cVar1 == 0x1d) {
                ((Unkstruct_800B5CB8 *)param_1)->unk82 = 0;
                ((Unkstruct_800B5CB8 *)param_1)->unk7C = *(unsigned short *)(param_1 + 6);
                ((Unkstruct_800B5CB8 *)param_1)->unk7E = *(unsigned short *)(param_1 + 0xa);
                ((Unkstruct_800B5CB8 *)param_1)->unk80 = *(unsigned short *)(param_1 + 0xe);
            }
            if (((Unkstruct_800B5CB8 *)param_1)->unk78 != 0) {
                unaff_s1 = (int)((Unkstruct_800B5CB8 *)param_1)->unk60 *
                           (int)*(short *)(((Unkstruct_800B5CB8 *)param_1)->unk78 + 0x30) >> 0xc;
                if (unaff_s1 < 1) {
                    unaff_s1 = 1;
                }
            }
            *(unsigned short *)(param_1 + 0x76) =
                *(unsigned short *)(param_1 + 0x76) - unaff_s1;
            func_8016AA50(param_1, unaff_s1);
            if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
                ((void (*)(int))func_8016B428)(param_1);
                func_80019064(D_801AD450);
            }
        }
        if (cVar1 != 0x1d) {
            if (*(unsigned char *)(param_1 + 0xc8) != 0) {
                func_8002A520(param_1);
            }
            if (*(unsigned char *)(param_1 + 0xc9) != 0) {
                func_8002A790(param_1);
            }
        }
        if (((Unkstruct_800B5CB8 *)param_1)->unk76 < 1) {
            ((Unkstruct_800B5CB8 *)param_1)->unk5C = 0;
            func_80131E00(param_1, 6);
        }
    }
    return;
}


// @class: schedule
// @unstuck(P36): none — MATCH; success-block placed last via `goto big` (bnez forward into epilogue), single cae4 merge kept

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_800599B8();
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C218(void *a0);
extern void func_8012CAE4(void *a0);

extern u8 D_801AD470[];
extern u8 D_801AD3B4[];
extern u8 D_801AD374[];
extern u8 D_801AD3BC[];
extern u8 D_801AD394[];
extern u8 D_801B16DC[];
extern u8 D_801B498C[];
extern u8 D_801AD4B0[];

void func_8018102C(int param_1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801B47F4[];
    extern u8 D_801B487C[];
    extern u8 D_801B4904[];
    int iVar1;

    iVar1 = func_8012C354(param_1, D_801AD470);
    if (iVar1 != 0) {
        if (((Unkstruct_800B5CB8 *)param_1)->unk70 != 0) {
            func_800599B8(D_801AD3B4, D_801AD374);
            func_800599B8(D_801AD3BC, D_801AD394);
            func_8001C214(((Unkstruct_800B5CB8 *)param_1)->unk20, D_801B16DC);
        }
        ((Unkstruct_800B5CB8 *)param_1)->unkC0 = 1;
        ((Unkstruct_800B5CB8 *)param_1)->unkB4 = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        ((Unkstruct_800B5CB8 *)param_1)->unkAE = 0x2100;
        func_8012A828(param_1, D_801B498C);
        ((Unkstruct_800B5CB8 *)param_1)->unk2 = CAST_SIGN(u16, param_1, 2) + 1;
        func_8012B23C(param_1);
        ((Unkstruct_800B5CB8 *)param_1)->unkC4 = CAST_SIGN(u32, param_1, 0xc4) | 2;
        iVar1 = func_8012C658(0x26f, (int)((Unkstruct_800B5CB8 *)param_1)->unk70, param_1);
        if (iVar1 != 0) {
            ((Unkstruct_800B5CB8 *)param_1)->unkCC = iVar1;
            iVar1 = func_8012C658(0x270, (int)((Unkstruct_800B5CB8 *)param_1)->unk70, param_1);
            if (iVar1 != 0) goto big;
            func_8012C218(((Unkstruct_800B5CB8 *)param_1)->unkCC);
        }
        func_8012CAE4(param_1);
    }
    return;
big:
    ((Unkstruct_800B5CB8 *)param_1)->unkD0 = iVar1;
    ((Unkstruct_800B5CB8 *)param_1)->unkBC = (u32)D_801AD4B0;
    ((Unkstruct_800B5CB8 *)*(int *)(param_1 + 0x20))->unk2C =
        ((Unkstruct_800B5CB8 *)*(int *)(param_1 + 0x20))->unk2C | 0x10;
    ((Unkstruct_800B5CB8 *)*(int *)(param_1 + 0x20))->unk18 = 0x2400;
    ((Unkstruct_800B5CB8 *)*(int *)(param_1 + 0x20))->unk1A = 0x2400;
    *(short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x1c) = 0x2400;
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 8;
    func_8012A828(param_1, D_801B47F4);
    func_8012A828(((Unkstruct_800B5CB8 *)param_1)->unkCC, D_801B487C);
    func_8012A828(((Unkstruct_800B5CB8 *)param_1)->unkD0, D_801B4904);
    return;
}



/* func_801811DC — ov_SC06_008 / ov_SC06_008_jr_8017C294.  MATCH 163/163.
 * Family of 7 (ov_SC06_008/010/018/022/024/032/033, all 163 ins, all still in
 * nonmatchings) — §136e applies: no twin existed, so this is derived from the .s.
 * The byte-proven accumulate head (b744 nested inside b608, then two RE-LOADS of
 * *(s32*)(a0+0x20)) is copied verbatim from src/ov_SC03_099/..._jr_8017BEBC.c:5424.
 *
 * Four levers, each measured against match_one:
 *
 * 1. NO frame padding.  args_size already fills sp+0x00..0x1F, so the four saved
 *    regs land at 0x20..0x2F and the frame is 0x30 with ZERO locals.  A 16-byte
 *    dead aggregate (idiom 6, added on the first draft from a mis-derived
 *    args_size=0x10) made it 0x40 — idiom 6 only applies when the reg-save area
 *    does NOT start at args_size.
 *
 * 2. BRANCH POLARITY / BLOCK LAYOUT (§3-T4, T7).  `if (C) goto X;` followed by a
 *    `break` is REWRITTEN by jump.c's jump-around-jump inversion into
 *    `if (!C) goto break_target;` — which is the wrong polarity here.  The target
 *    wants the true arm to FALL THROUGH.  Two rewrites, both worth +0 instructions
 *    but different bytes:
 *      case 1: `if (A||B) goto st2; break;`  ->  `if (!A && !B) break; goto st2;`
 *              (TRUTH_ANDIF gives reversed branches to `next`, and the trailing
 *               `j st2` is the fall-through — exactly `beqz L600 / j L5E0`.)
 *      case 3: same shape, plus the range test written as the POSITIVE
 *              `if (r >= -0xFF && r <= 0xFF) break;` so fold_range_test's
 *              `sltiu (r+0xFF),0x1FF` branches on TRUE to the switch end and case 3
 *              falls through into st2 (saves the `j`+`nop`, 165 -> 163 ins).
 *    Case 0 keeps the plain `if (A||B) {..} else {..}` — there jump.c's inversion
 *    IS what the target has.
 *
 * 3. THE SHARED STORE BLOCK.  L801815F8/L801815FC (`li v0,1` / `sh v0,0x34`) sit
 *    AFTER st2 in the target, so they are NOT inline `else` arms (cross-jumping
 *    keeps the LAST copy, which would put them BEFORE st2).  They are explicit
 *    trailing labels inside the switch with an `ns` join variable; case 2 enters at
 *    `setstate` with ns=3, cases 0 and 3 enter at `set1`.
 *
 * 4. REGALLOC-PERM -> the $16 pin (see below).
 */

extern s32 rand(void);
extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern int func_801808A4(int param_1, short param_2);

void func_801811DC(s32 a0) {

    extern u8 D_801AD4D0[];

    /* No pin (P36 S104 d30): case 3's two call results share ONE local
     * `ret` — flow counts 4 refs over a live length of 5 (the B608 piece's
     * copy from $v0 is folded into its compare by combine only afterwards),
     * so allocno_compare (global.c:595-607) ranks it at 16000, above the a0
     * copy's 13503. `ret` is allocated first and takes $s0; the a0 copy
     * conflicts with it and takes $s1; `tbl` does not conflict with `ret`
     * and takes $s0 in find_reg pass 0 (global.c:945-953) — exactly the
     * target's assignment. One `d` plus one `r` (refs 2, pri 4000) lose to
     * the a0 copy and give the 2-register permutation the old $16 pin hid. */
    s32 tbl;
    s32 ns;

    tbl = (s32)D_801AD4D0;
    ((void (*)(s32, s32))func_8012B1B4)(a0, tbl);
    func_8012CBCC(a0);

    switch (((Unkstruct_800B5CB8 *)a0)->unk34) {
    case 0:
        if (func_801808A4(a0, 0x48) != 0 ||
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) >
                0x3FFFF) {
            s32 r = func_8012B608(
                *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12),
                func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 8);
            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
                ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 + r;
            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
                ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 & 0xFFF;
            ((void (*)(s32, s32))func_8012B1B4)(a0, tbl);
        } else {
            goto set1;
        }
        break;

    case 1:
        if (func_801808A4(a0, 0x48) == 0 &&
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) <=
                0x3FFFF) {
            break;
        }
        goto st2;

    case 2: {
        s32 r = func_8012B608(
            *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12),
            func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 0x10);
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 + r;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
            ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 & 0xFFF;
    }
        func_801808A4(a0, 0x48);
        {
            s16 c = ((Unkstruct_800B5CB8 *)a0)->unk102;
            if (c == 0) {
                ns = 3;
                goto setstate;
            }
            ((Unkstruct_800B5CB8 *)a0)->unk102 = c - 1;
        }
        break;

    case 3: {
        void *p88 = (void *)(a0 + 0x88);
        s32 ret = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
        if (func_801808A4(a0, 0x48) == 0) {
            if (ret > 0x40000) {
                ret = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12),
                                      func_8012B744((void *)(a0 + 4), p88), 1);
                if (ret >= -0xFF && ret <= 0xFF) {
                    break;
                }
            } else {
                goto set1;
            }
        }
    }
        /* fall through into st2 */
    st2:
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 2;
        ((Unkstruct_800B5CB8 *)a0)->unk102 = (rand() & 7) + 8;
        break;

    set1:
        ns = 1;
    setstate:
        ((Unkstruct_800B5CB8 *)a0)->unk34 = ns;
        break;
    }

    {
        s16 t = ((Unkstruct_800B5CB8 *)a0)->unk100;
        if (t != 0) {
            ((Unkstruct_800B5CB8 *)a0)->unk100 = t - 1;
        } else if (((s32(*)(s32))func_8012BE54)(a0) <= 0x24000) {
            ((Unkstruct_800B5CB8 *)a0)->unk2 = 5;
            ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x3C;
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 * func_8012913C(s32 arg0);
extern void func_8012A828(s32 a0, void * a1);

void func_80181468(s32 a0) {

    extern u8  D_800AF648;
    extern s32 D_801AD334[];
    extern u8  D_801B47F4[];
    extern u8  D_801B487C[];
    extern u8  D_801B4904[];
    struct {
        s16 pad0[4];  /* sp+0x10 — dead, but sizes the frame (idiom 6) */
        s16 v[3];     /* sp+0x18 */
        s16 pad1;     /* sp+0x1E */
        u16 sxy[2];   /* sp+0x20 */
        s32 z;        /* sp+0x24 */
        s32 flag;     /* sp+0x28 */
    } L;
    s32 t;
    s32 ang;
    s32 idx;
    s32 m;
    s32 c;
    s32 p;

    if (((Unkstruct_800B5CB8 *)a0)->unk98 == 0) {
        s32 spr = (s32)func_8012913C(0x7F);
        if (spr != 0) {
            m = *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)
              + (func_8004787C(((Unkstruct_800B5CB8 *)a0)->unk104) >> 3);
            ((Unkstruct_800B5CB8 *)spr)->unk6 = ((Unkstruct_800B5CB8 *)a0)->unk6 - (func_8004787C(m) * 0x6C) / 0x1000;
            ((Unkstruct_800B5CB8 *)spr)->unkA = ((Unkstruct_800B5CB8 *)a0)->unkA - 0x34;
            ((Unkstruct_800B5CB8 *)spr)->unkE = ((Unkstruct_800B5CB8 *)a0)->unkE - (func_80047948(m) * 0x6C) / 0x1000;
            ((Unkstruct_800B5CB8 *)spr)->unk14 = 0x40000;
            CAST_WIDTH(s32, spr, 0x10) = -(func_8004787C(m) * 0xC0);
            CAST_WIDTH(s32, spr, 0x18) = -(func_80047948(m) * 0xC0);
        }
        t = CAST_SIGN(u16, a0, 0x104) + 0x100;
        ((Unkstruct_800B5CB8 *)a0)->unk104 = t;
        ang = (s16)t;
        idx = ang / 0x100;
        m = (s16)(idx % 0x10);
        if (ang == 0x100) {
            L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
            L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
            L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }  // !FAKE: pin expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
            RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
            if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                            && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                s32 x = (s16)L.sxy[0];
                s32 ax;
                ax = x;
                if (x < 0) {
                    ax = -x;
                }
                ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                __asm__("" : "=r"(ax) : "0"(ax));  // !FAKE: launder expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
                x = (x + 0xF0) / 0x1E;
                if (x == 0x10) {
                    x = 0xF;
                }
                x = x << 8;
                {
                    s32 flg = 0x3000;
                    func_8002D4C8(0x95F, ((ax | flg) | x) & 0xFFFF);
                }
            }
        } else if (m == 0) {
            L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
            L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
            L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }  // !FAKE: pin expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
            RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
            if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                            && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                s32 x = (s16)L.sxy[0];
                s32 ax;
                ax = x;
                if (x < 0) {
                    ax = -x;
                }
                ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                __asm__("" : "=r"(ax) : "0"(ax));  // !FAKE: launder expanded from per-TU macro RTP_SND (T8.c3); pass: P40 T8.c3 macro expansion; instrument: delever --rejudge t8_mac
                x = (x + 0xF0) / 0x1E;
                if (x == 0x10) {
                    x = 0xF;
                }
                x = x << 8;
                {
                    s32 flg = 0x3000;
                    func_8002D4C8(0x960, ((ax | flg) | x) & 0xFFFF);
                }
            }
        }
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk20 = D_801AD334[m];
        c = CAST_SIGN(u16, a0, 0x100) - 1;
        ((Unkstruct_800B5CB8 *)a0)->unk100 = c;
        if ((s16)c == 0) {
            p = ((Unkstruct_800B5CB8 *)a0)->unkCC;
            ((Unkstruct_800B5CB8 *)a0)->unk98 = 1;
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
            p = ((Unkstruct_800B5CB8 *)a0)->unkD0;
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
        }
    } else if ((((Unkstruct_800B5CB8 *)a0)->unk72 & 0x4000) != 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 7;
        ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x3C;
        func_8012A828(a0, D_801B47F4);
        p = ((Unkstruct_800B5CB8 *)a0)->unkCC;
        if (p != 0) {
            func_8012A828(p, D_801B487C);
        }
        p = ((Unkstruct_800B5CB8 *)a0)->unkD0;
        if (p != 0) {
            func_8012A828(p, D_801B4904);
        }
    }
}



extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018192C(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    s16 hp;
    s32 p;

    hp = *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14);
    if (hp < 0x301) {
        s32 count;
        s32 total;

        count = CAST_SIGN(u16, a0, 0xFC);
        total = CAST_SIGN(u16, a0, 0xFE);
        count = count + 1;
        total = total + count;
        ((Unkstruct_800B5CB8 *)a0)->unkFC = count;
        ((Unkstruct_800B5CB8 *)a0)->unkFE = total;
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
            *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) + total;
    } else {
        p = ((Unkstruct_800B5CB8 *)a0)->unkD0;
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 3;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x1E;
        ((Unkstruct_800B5CB8 *)a0)->unk98 = 0;
        ((Unkstruct_800B5CB8 *)p)->unk2 = 3;
        ((Unkstruct_800B5CB8 *)p)->unk1C = 0x1E;
        ((Unkstruct_800B5CB8 *)p)->unk98 = 0;

        L.v[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
        L.v[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
        L.v[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
        { void *r4; r4 = &D_800AF648; func_8004914C(r4); }
        { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            func_8002D4C8(0x961, (ax | (0x3000 | x)) & 0xFFFF);
        }
    }
    func_8012B370(a0);
}


extern s32 func_801823F0(void);

/* func_80181AFC -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (family of 7)
 *
 * Low-HP flinch/knockback reaction. hp = *(s16*)(a0->0x20 ptr + 0x14). If
 * 0 < hp < 0xD00, put self AND the partner at a0->0xCC into stagger state 3
 * (a 0x1E-frame timer, status flag cleared), compute a screen-space
 * position via RotTransPers and play a positional sound. Otherwise
 * (hp==0 or hp>=0xD00) apply the accumulated hit-combo counter (0xFC/0xFE)
 * to the target's HP and re-mask its low 12 bits.
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND form from func_8018165C in this same TU (line 4746) -- v[]/pad,
 * u16 sxy[2], s32 z, s32 flag, and the ax/x div-by-0xF0 / div-by-0x1E
 * magic-constant idiom (0x88888889); also confirmed against func_801823F0
 * (same TU) which reuses the identical sndid 0x961 and the identical
 * `sx = (sx + 0xF0) / 0x1E; if (sx == 0x10) sx = 0xF; sx <<= 8;` tail.
 *
 * Control flow: gcc-2.7.2 lays out basic blocks in literal SOURCE order, not
 * by fallthrough-preference. A nested-if spelling (`if (hp<0xD00) { state=3;
 * if (hp!=0) { B; goto end; } } A; end:`) places B (textually the inner
 * then-body) inline right after the tests and relocates A after it -- the
 * REVERSE of the target, which has the short block A inline and the long
 * RTP+sound block B out-of-line. Explicit goto/label with A written BEFORE B
 * in source (`if (hp>=0xD00) goto L_A; state=3; if (hp!=0) goto L_B; L_A: A;
 * goto L_end; L_B: B; L_end: ...`) reproduces the target's physical layout
 * directly -- no branch-polarity inversion needed, just source ORDER.
 *
 * Frame: RotTransPers args are sp+0x10 (v), sp+0x18 (&sxy), sp+0x1C (&z),
 * sp+0x20 (&flag); v[3]+pad1 fills 0x10-0x17, sxy 0x18-0x1B, z 0x1C-0x1F,
 * flag 0x20-0x23 -- leaves a dead 4 bytes (0x24-0x27) before the s0 save at
 * 0x28. A trailing `pad2` dead struct member (same aggregate, so it can't
 * be eliminated) reserves those 4 bytes, mirroring func_8018165C's own
 * "dead aggregate sizes the frame" idiom (comment there: idiom 6).
 */

extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80181AFC(s32 a0) {
    extern u8 D_800AF648_b __asm__("D_800AF648");

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2;    /* sp+0x24 -- dead, sizes the frame */
    } L;

    s16 hp;
    s32 state;
    s32 p;

    hp = *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14);
    if (hp >= 0xD00) {
        goto L_A;
    }
    state = 3;
    if (hp != 0) {
        goto L_B;
    }

L_A:
    {
        s32 count;
        s32 total;

        count = CAST_SIGN(u16, a0, 0xFC);
        total = CAST_SIGN(u16, a0, 0xFE);
        count = count + 1;
        total = total + count;
        ((Unkstruct_800B5CB8 *)a0)->unkFC = count;
        ((Unkstruct_800B5CB8 *)a0)->unkFE = total;
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
            *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) - total;
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
            *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) & 0xFFF;
    }
    goto L_end;

L_B:
    p = ((Unkstruct_800B5CB8 *)a0)->unkCC;
    ((Unkstruct_800B5CB8 *)a0)->unk2 = state;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x1E;
    ((Unkstruct_800B5CB8 *)a0)->unk98 = 0;
    ((Unkstruct_800B5CB8 *)p)->unk2 = state;
    ((Unkstruct_800B5CB8 *)p)->unk1C = 0x1E;
    ((Unkstruct_800B5CB8 *)p)->unk98 = 0;

    L.v[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
    L.v[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
    L.v[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
    { void *r4; r4 = &D_800AF648; func_8004914C(r4); }
    { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
        s32 sx = (s16)L.sxy[0];
        s32 av;
        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_end:
    func_8012B370(a0);
}


extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern void func_8012C218(void *a0);
extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 rand(void);

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181CEC(s32 a0)
{

    extern void (*D_801AD4E0[])(void);
    extern u8 D_800AF648;
    extern u8 D_800AF648_b __asm__("D_800AF648");
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    D_801AD4E0[CAST_SIGN(u16, a0, 0x2)]();

    if (((Unkstruct_800B5CB8 *)a0)->unk0 != 0) {
        if (((Unkstruct_800B5CB8 *)a0)->unk70 == 0 && func_8012C044(a0) != 0) {
            if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0) {
                func_8012C218(CAST_SIGN(void *, a0, 0xCC));
            }
            if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0) {
                func_8012C218(CAST_SIGN(void *, a0, 0xD0));
            }
            func_8012C098((void *)a0);
        } else {
            s16 v;

            v = *(s16 *)(a0 + 0xE2);
            if (v != 0) {
                v = v - 1;
                *(s16 *)(a0 + 0xE2) = v;
                if (v == 0) {
                    ((Unkstruct_800B5CB8 *)a0)->unk5C &= 0xBFFF;
                }
            }

            if ((((Unkstruct_800B5CB8 *)a0)->unk76 < 5) && ((rand() & 3) == 0)) {
                s32 iVar2 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
                s32 r;

                if (iVar2 != 0) {
                    r = rand();
                    *(s32 *)(iVar2 + 0x10) = ((r & 0x7FF) - 0x400) << 8;
                    *(s32 *)(iVar2 + 0x14) = 0xFFF00000;
                    r = rand();
                    *(s32 *)(iVar2 + 0x18) = ((r & 0x7FF) - 0x400) << 8;
                    r = rand();
                    *(u16 *)(iVar2 + 0x6) -= 0x20;
                    *(u16 *)(iVar2 + 0x6) += (r & 0x3F);
                    *(s16 *)(iVar2 + 0xA) -= 0xC0;
                    r = rand();
                    *(u16 *)(iVar2 + 0xE) -= 0x20;
                    *(u16 *)(iVar2 + 0xE) += (r & 0x3F);
                }
            }

            if (CAST_SIGN(u16, a0, 0x2) != 1 && CAST_SIGN(u16, a0, 0x2) != 5) {
                ((Unkstruct_800B5CB8 *)a0)->unk84 = 0xE;
            } else {
                if (((Unkstruct_800B5CB8 *)a0)->unk84 != 0) {
                    ((Unkstruct_800B5CB8 *)a0)->unk84 = ((Unkstruct_800B5CB8 *)a0)->unk84 - 1;
                } else {
                    ((Unkstruct_800B5CB8 *)a0)->unk84 = 0xE;

                    L.v[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
                    L.v[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
                    L.v[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
                    func_8004914C(&D_800AF648);
                    func_800491AC(&D_800AF648_b);
                    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
                    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                        s32 x = (s16)L.sxy[0];
                        s32 ax;
                        ax = x;
                        if (x < 0) {
                            ax = -x;
                        }
                        ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                        x = (x + 0xF0) / 0x1E;
                        if (x == 0x10) {
                            x = 0xF;
                        }
                        x = x << 8;
                        {
                            s32 flg = 0x3000;
                            func_8002D4C8(0x8BF, ((ax | flg) | x) & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
}


// @class: plumbing
// @unstuck(P36): none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//   lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//   `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//   (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//   hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//   the `< 1` test.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);
extern unsigned char D_801AD450[];

void func_80182004(int param_1)
{
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    ((Unkstruct_800B5CB8 *)param_1)->unkC1 = 0;
    CAST_WIDTH(short, param_1, 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (((Unkstruct_800B5CB8 *)param_1)->unkFC == 0) {
        CAST_WIDTH(int, param_1, 4) = *(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 4);
        CAST_WIDTH(int, param_1, 8) = *(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 8);
        CAST_WIDTH(int, param_1, 0xc) = *(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0xc);
        *(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x10) =
            *(unsigned short *)(*(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x10);
        *(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12) =
            *(unsigned short *)(*(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x12);
        *(unsigned short *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x14) =
            *(unsigned short *)(*(int *)(((Unkstruct_800B5CB8 *)param_1)->unk64 + 0x20) + 0x14);
    }
    if (((Unkstruct_800B5CB8 *)param_1)->unk102 == 0) {
        ((Unkstruct_800B5CB8 *)param_1)->unk102 = 10;
        *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0x4000;
        func_8002D4C8(0x9b7, 0);
        if (((Unkstruct_800B5CB8 *)param_1)->unk60 != 0) {
            if (cVar1 == 0x1d) {
                ((Unkstruct_800B5CB8 *)param_1)->unk82 = 0;
                ((Unkstruct_800B5CB8 *)param_1)->unk7C = *(unsigned short *)(param_1 + 6);
                ((Unkstruct_800B5CB8 *)param_1)->unk7E = *(unsigned short *)(param_1 + 0xa);
                ((Unkstruct_800B5CB8 *)param_1)->unk80 = *(unsigned short *)(param_1 + 0xe);
            }
            if (((Unkstruct_800B5CB8 *)param_1)->unk78 != 0) {
                unaff_s1 = (int)((Unkstruct_800B5CB8 *)param_1)->unk60 *
                           (int)*(short *)(((Unkstruct_800B5CB8 *)param_1)->unk78 + 0x30) >> 0xc;
                if (unaff_s1 < 1) {
                    unaff_s1 = 1;
                }
            }
            *(unsigned short *)(param_1 + 0x76) =
                *(unsigned short *)(param_1 + 0x76) - unaff_s1;
            func_8016AA50(param_1, unaff_s1);
            if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
                ((void (*)(int))func_8016B428)(param_1);
                func_80019064(D_801AD450);
            }
        }
        if (cVar1 != 0x1d) {
            if (*(unsigned char *)(param_1 + 0xc8) != 0) {
                func_8002A520(param_1);
            }
            if (*(unsigned char *)(param_1 + 0xc9) != 0) {
                func_8002A790(param_1);
            }
        }
        if (((Unkstruct_800B5CB8 *)param_1)->unk76 < 1) {
            ((Unkstruct_800B5CB8 *)param_1)->unk5C = 0;
            func_80131E00(param_1, 6);
        }
    }
    return;
}





extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 * func_8012913C(s32 arg0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

void func_801821FC(s32 a0) {

    extern s32 D_801151D4;

    extern void func_8002AC00(s32 arg0);
    extern void func_8002A04C(s32 arg0);
    extern u8 D_800AF648;
    extern u8 D_800AF648_b __asm__("D_800AF648");

    u16 v10[4];   /* sp+0x10 */
    s16 v18[4];   /* sp+0x18 */
    s32 sxy;      /* sp+0x20 */
    s32 z;        /* sp+0x24 */
    s32 flag;     /* sp+0x28 */
    s32 base;
    s32 iv;
    s32 i;
    s32 t;
    s32 r;

    base = D_801151D4;

    if (((Unkstruct_800B5CB8 *)a0)->unkFC >= 0x1F) {
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) - 5;
        }
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) + 5;
        }
        iv = func_8012C658(0x32, 2, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) + 8;
        }

        func_8002AC00(0x22);

        iv = ((Unkstruct_800B5CB8 *)a0)->unk64;
        *(s16 *)(iv + 2) = 2;
        iv = *(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk64 + 0xD0);
        *(s16 *)(iv + 2) = 4;
        *(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk64 + 0xCC) = 0;

        i = 0;
        do {
            iv = func_8012C588(0x281, a0);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(s16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(s16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);

        v18[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
        v18[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
        v18[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
        RotTransPers((s32)v18, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((*((u16 *)&sxy + 1) + 0xB3) & 0xFFFF) < 0x167) {
            s32 sx;
            s32 av;

            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            /* one local for |x| AND the volume: gcc-2.7.2 keeps the single pseudo
               in $v1 in place (subu $v1,$v0,$v1); a separate `vol` local steals $a1
               and the whole OR chain drifts (cookbook §136 L1). */
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
        }

        func_8002A04C(a0);
        func_8012C218((void *)a0);
        return;
    }

    iv = (s32)func_8012913C(0x23);
    if (iv != 0) {
        r = rand();
        *(u16 *)(iv + 0x06) = ((Unkstruct_800B5CB8 *)a0)->unk6 + (r & 0x7F) - 0x40;
        r = rand();
        *(u16 *)(iv + 0x0A) = ((Unkstruct_800B5CB8 *)a0)->unkA + (r & 0x7F) - 0x80;
        r = rand();
        *(u16 *)(iv + 0x0E) = ((Unkstruct_800B5CB8 *)a0)->unkE + (r & 0x7F) - 0x40;

        t = func_80047948((s32) * (s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12));
        *(s32 *)(iv + 0x04) = *(s32 *)(iv + 0x04) + (t << 10);

        t = func_8004787C((s32) * (s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12));
        *(u16 *)(iv + 0x34) = 0x1800;
        *(s32 *)(iv + 0x18) = 0;
        *(s32 *)(iv + 0x14) = 0;
        *(s32 *)(iv + 0x10) = 0;
        *(s32 *)(iv + 0x0C) = *(s32 *)(iv + 0x0C) - (t << 10);

        v10[0] = *(s32 *)(base + 0x5C) - *(u16 *)(iv + 0x06);
        v10[1] = *(s32 *)(base + 0x60) - *(u16 *)(iv + 0x0A);
        v10[2] = *(s32 *)(base + 0x64) - *(u16 *)(iv + 0x0E);
        VectorNormalSS(v10, v10);

        *(u16 *)(iv + 0x06) = *(u16 *)(iv + 0x06) + ((s16)v10[0] >> 6);
        *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) + ((s16)v10[1] >> 6);
        *(u16 *)(iv + 0x0E) = *(u16 *)(iv + 0x0E) + ((s16)v10[2] >> 6);
        *(u16 *)(iv + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    ((Unkstruct_800B5CB8 *)a0)->unkFC = CAST_SIGN(u16, a0, 0xFC) + 1;
}


// @class: struct
// @unstuck(P36): none — MATCH

extern int rand(void);
extern s32 func_80143C74(s32 a0, s32 a1);
extern int func_80047948(int);
extern int func_8004787C(int);
extern void (*D_801AD568[])(short *);

void func_80182644(short *param_1)
{
    int iVar3;
    unsigned int uVar2;
    short v;

    v = param_1[0x81];
    if (v != 0) {
        v = v - 1;
        param_1[0x81] = v;
        if (v == 0) {
            *(unsigned short *)(param_1 + 0x2e) &= 0xbfff;
        }
    }
    D_801AD568[*(unsigned short *)(param_1 + 1)](param_1);
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x7e] == 0) {
            CAST_MISALIGNED(int, param_1, 2) = CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 4);
            CAST_ALIAS(int, param_1, 4) = CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 8);
            CAST_MISALIGNED(int, param_1, 6) = CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 0xc);
            *(unsigned short *)(CAST_ALIAS(int, param_1, 0x10) + 0x10) =
                *(unsigned short *)(CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 0x20) + 0x10);
            *(unsigned short *)(CAST_ALIAS(int, param_1, 0x10) + 0x12) =
                *(unsigned short *)(CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 0x20) + 0x12);
            *(unsigned short *)(CAST_ALIAS(int, param_1, 0x10) + 0x14) =
                *(unsigned short *)(CAST_NONSTRUCT(int, CAST_MISALIGNED(int, param_1, 0x32), 0x20) + 0x14);
        }
        if ((param_1[0x3b] < 5) && ((rand() & 3) == 0) &&
            ((iVar3 = func_80143C74(param_1, 0)) != 0)) {
            uVar2 = rand();
            CAST_WIDTH(int, iVar3, 0x10) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            *(unsigned int *)(iVar3 + 0x14) = 0xfff00000;
            uVar2 = rand();
            CAST_WIDTH(int, iVar3, 0x18) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            CAST_WIDTH(int, iVar3, 4) +=
                func_80047948((int)*(short *)(CAST_ALIAS(int, param_1, 0x10) + 0x12)) * 0x400;
            CAST_WIDTH(int, iVar3, 0xc) -=
                func_8004787C((int)*(short *)(CAST_ALIAS(int, param_1, 0x10) + 0x12)) * 0x400;
            uVar2 = rand();
            CAST_SIGN(short, iVar3, 6) -= 0x20;
            CAST_SIGN(short, iVar3, 6) += (uVar2 & 0x3f);
            CAST_SIGN(short, iVar3, 0xa) -= 0x40;
            uVar2 = rand();
            CAST_SIGN(short, iVar3, 0xe) -= 0x20;
            CAST_SIGN(short, iVar3, 0xe) += (uVar2 & 0x3f);
        }
    }
    return;
}




extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 * func_8012913C(s32 arg0);
extern s32  rand(void);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  VectorNormalSS(void *a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002A04C(s32 a0);


void func_80182854(s32 a0) {

    extern s32 D_801151D4;

    extern u8 D_800AF648;

    extern u8 D_800AF648_b __asm__("D_800AF648");
    extern void func_8002AC00(s32 arg0);

    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 v[4];    /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;
    s32 p;
    s32 s0;
    s32 i;

    p = D_801151D4;

    if (((Unkstruct_800B5CB8 *)a0)->unkFC >= 0x1F) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);
        s0 = ((Unkstruct_800B5CB8 *)a0)->unk64;
        *(s16 *)(s0 + 0x2) = 4;
        s0 = *(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk64 + 0xCC);
        *(s16 *)(s0 + 0x2) = 4;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.v[0] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk48;
        L.v[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk4C;
        L.v[2] = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk50;
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }

        *(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk64 + 0xD0) = 0;
        func_8002A04C(a0);
        func_8012C218((void *)a0);
        return;
    }

    s0 = (s32)func_8012913C(0x23);
    if (s0 != 0) {
        *(s16 *)(s0 + 0x6) = ((Unkstruct_800B5CB8 *)a0)->unk6 + (rand() & 0x7F) - 0x40;
        *(s16 *)(s0 + 0xA) = ((Unkstruct_800B5CB8 *)a0)->unkA + (rand() & 0x7F) - 0x80;
        *(s16 *)(s0 + 0xE) = ((Unkstruct_800B5CB8 *)a0)->unkE + (rand() & 0x7F) - 0x40;

        *(s32 *)(s0 + 0x4) =
            *(s32 *)(s0 + 0x4) -
            func_80047948(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x400;
        {
            s32 t = func_8004787C(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x400;
            *(s16 *)(s0 + 0x34) = 0x1800;
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)(s0 + 0x10) = 0;
            *(s32 *)(s0 + 0xC) = *(s32 *)(s0 + 0xC) + t;
        }

        L.nv[0] = *(s32 *)(p + 0x5C) - *(u16 *)(s0 + 0x6);
        L.nv[1] = *(s32 *)(p + 0x60) - *(u16 *)(s0 + 0xA);
        L.nv[2] = *(s32 *)(p + 0x64) - *(u16 *)(s0 + 0xE);
        VectorNormalSS(L.nv, L.nv);

        *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
        *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
        *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
        *(s16 *)(s0 + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    ((Unkstruct_800B5CB8 *)a0)->unkFC = CAST_SIGN(u16, a0, 0xFC) + 1;
}


// @class: other
// @unstuck(P36): none — MATCH (132 ins). Blocker was gcc reassociating `mem - 0x20 + masked`
//   into `mem + (masked - 0x20)` and CSE-hoisting the shared -0x20 (as 0xffe0/ori) into the
//   freed s0, which then filled the jal func_8004787C delay slot. Fix: split `mem - 0x20`
//   into its own temp so addiu -0x20 stays on the memory operand at each of the two sites.

#include "common.h"

extern s32 rand(void);
extern void (*D_801AD5E0[])(s32);
extern s32 func_80143C74(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80182C98(s32 a0) {
    s32 iVar3;
    s32 iVar4;
    s32 r;

    {
        s16 t = ((Unkstruct_80182C98 *)a0)->unk102;
        if (t != 0) {
            t--;
            ((Unkstruct_80182C98 *)a0)->unk102 = t;
            if (t == 0) {
                ((Unkstruct_80182C98 *)a0)->unk5C &= 0xBFFF;
            }
        }
    }

    D_801AD5E0[((Unkstruct_80182C98 *)a0)->unk2](a0);

    if (((Unkstruct_80182C98 *)a0)->unk0 != 0) {
        if (((Unkstruct_80182C98 *)a0)->unkFC == 0) {
            ((Unkstruct_80182C98 *)a0)->unk4 = ((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unk4;
            ((Unkstruct_80182C98 *)a0)->unk8 = ((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unk8;
            ((Unkstruct_80182C98 *)a0)->unkC = ((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unkC;
            ((Unkstruct_80182C98_3 *)*(s32 *)(a0 + 0x20))->unk10 =
                *(s16 *)(((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unk20 + 0x10);
            ((Unkstruct_80182C98_3 *)*(s32 *)(a0 + 0x20))->unk12 =
                *(s16 *)(((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unk20 + 0x12);
            ((Unkstruct_80182C98_3 *)*(s32 *)(a0 + 0x20))->unk14 =
                *(s16 *)(((Unkstruct_80182C98_2 *)*(s32 *)(a0 + 0x64))->unk20 + 0x14);
        }
        if (((Unkstruct_80182C98 *)a0)->unk76 < 5 && (rand() & 3) == 0 &&
            (iVar3 = func_80143C74(a0, 0)) != 0) {
            *(s32 *)(iVar3 + 0x10) = ((rand() & 0x7FF) - 0x400) << 8;
            *(s32 *)(iVar3 + 0x14) = 0xFFF00000;
            *(s32 *)(iVar3 + 0x18) = ((rand() & 0x7FF) - 0x400) << 8;
            iVar4 = func_80047948((s32) ((Unkstruct_80182C98_3 *)*(s32 *)(a0 + 0x20))->unk12);
            *(s32 *)(iVar3 + 4) = *(s32 *)(iVar3 + 4) - iVar4 * 0x400;
            iVar4 = func_8004787C((s32) ((Unkstruct_80182C98_3 *)*(s32 *)(a0 + 0x20))->unk12);
            *(s32 *)(iVar3 + 0xC) = *(s32 *)(iVar3 + 0xC) + iVar4 * 0x400;
            r = rand();
            {
                s32 m6 = *(u16 *)(iVar3 + 6) - 0x20;
                *(u16 *)(iVar3 + 6) = m6 + (r & 0x3F);
            }
            *(u16 *)(iVar3 + 0xA) = *(u16 *)(iVar3 + 0xA) - 0x40;
            r = rand();
            {
                s32 mE = *(u16 *)(iVar3 + 0xE) - 0x20;
                *(u16 *)(iVar3 + 0xE) = mE + (r & 0x3F);
            }
        }
    }
}


// @class: schedule
// @unstuck(P36): none — MATCH. Two levers: (1) split rand()-result into its own var (shared iVar1 forced an extra move a0,v0); (2) reorder decrement before sp[0] to group the two lhu loads as target's scheduler does; (3) materialize &D_80126B96 via a local u16* to CSE the address (lui+addiu once) instead of %hi/%lo split-per-access.








extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8012931C(struct vec *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern u8 * func_8012913C(s32 arg0);
extern void func_801292C8(u8 *a0);
extern int func_8012D664(int arg0, int arg1, int arg2);

extern u8  D_801AD3C4;
extern u8  D_801AD3D0;
extern u16 D_80126B96;
extern u16 D_801270C0;

void func_80182EA8(s32 arg0) {
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (CAST_SIGN(u16, arg0, 2) == 0) {
        *(u8 **)(((Unkstruct_800B5CB8 *)arg0)->unk20 + 0x20) = &D_801AD3C4;
        *(u32 *)(((Unkstruct_800B5CB8 *)arg0)->unk20 + 4) |= 0x50000000;
        ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk27 = 0x59;
        func_80128EA8(((Unkstruct_800B5CB8 *)arg0)->unk20, arg0 + 0x24, (s32)&D_801AD3D0);
        rv = rand();
        ((Unkstruct_800B5CB8 *)arg0)->unk1C = 0x10;
        CAST_WIDTH(s32, arg0, 0x2c) = 0x200;
        ((Unkstruct_800B5CB8 *)arg0)->unk28 = rv % 15;
        ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk18 = 0x1200;
        ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk1A = 0x1200;
        ((Unkstruct_800B5CB8 *)arg0)->unk2 = CAST_SIGN(u16, arg0, 2) + 1;
    } else if (*(s16 *)&D_801270C0 == 1) {
        func_8012931C(arg0);
        func_80128ED8(((Unkstruct_800B5CB8 *)arg0)->unk20, arg0 + 0x24);
        ((Unkstruct_800B5CB8 *)arg0)->unk1C -= 1;
        if ((rand() & 7) == 0 && (p = func_8012913C(0x22)) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk6 = ((Unkstruct_800B5CB8 *)arg0)->unk6;
            ((Unkstruct_800B5CB8 *)p)->unkA = ((Unkstruct_800B5CB8 *)arg0)->unkA;
            ((Unkstruct_800B5CB8 *)p)->unkE = ((Unkstruct_800B5CB8 *)arg0)->unkE;
            CAST_WIDTH(s32, p, 0x10) = CAST_WIDTH(s32, arg0, 0x10) >> 3;
            ((Unkstruct_800B5CB8 *)p)->unk14 = ((Unkstruct_800B5CB8 *)arg0)->unk14 >> 3;
            CAST_WIDTH(s32, p, 0x18) = CAST_WIDTH(s32, arg0, 0x18) >> 3;
            ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk18 + 1;
            ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk2C = 0xc008;
        }
        if (((Unkstruct_800B5CB8 *)arg0)->unk1C == 0) {
            func_801292C8(arg0);
        } else {
            ((Unkstruct_800B5CB8 *)arg0)->unk14 = 0xffff0000;
            iVar1 = CAST_WIDTH(s32, arg0, 0x2c) + 0x80;
            CAST_WIDTH(s32, arg0, 0x2c) = iVar1;
            ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk18 =
                *(s16 *)(((Unkstruct_800B5CB8 *)arg0)->unk20 + 0x18) + (s16)iVar1;
            ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk1A =
                *(s16 *)(((Unkstruct_800B5CB8 *)arg0)->unk20 + 0x1a) + (s16)CAST_WIDTH(s32, arg0, 0x2c);
            ((Unkstruct_800B5CB8 *)arg0)->unkA = CAST_SIGN(s16, arg0, 0xa) - 0x20;
            sp[0] = ((Unkstruct_800B5CB8 *)arg0)->unk6;
            sp[1] = ((Unkstruct_800B5CB8 *)arg0)->unkA;
            sp[2] = ((Unkstruct_800B5CB8 *)arg0)->unkE;
            if (func_8012D664(sp, 0x10, 0xb4) == 1) {
                u16 *q = &D_80126B96;
                *q |= 0x4200;
            }
            ((Unkstruct_800B5CB8 *)arg0)->unkA = CAST_SIGN(s16, arg0, 0xa) + 0x20;
        }
    }
}




void func_8018312C(param_1)
s32 param_1;
{
  int p;
  ((Unkstruct_80181BB4 *)param_1)->unk5C = 0;
  ((Unkstruct_80181BB4 *)param_1)->unkFC = 0x1e;
  p = ((Unkstruct_80181BB4 *)param_1)->unkCC;
  ((Unkstruct_80181BB4_2 *)p)->unk5C = 0;
  p = ((Unkstruct_80181BB4 *)param_1)->unkD0;
  ((Unkstruct_80181BB4_2 *)p)->unk5C = 0;
}



extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern int func_801808A4(int param_1, short param_2);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012A828(s32 a0, void * a1);

void func_8018314C(s32 a0) {
    extern u8 D_801AD4D0[];
    extern u8 D_801B4C8C[];
    extern u8 D_801B4D7C[];
    extern u8 D_801B4E6C[];
    s32 pad[4];

    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)D_801AD4D0);
    func_8012CBCC(a0);
    func_801808A4(a0, 0x48);
    *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12) += func_8012B8E4(a0, 0x10);
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 &= 0xFFF;

    CAST_SIGN(u16, a0, 0x100) -= 1;
    if (((Unkstruct_800B5CB8 *)a0)->unk100 == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 6;
        ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x2D;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0;
        ((Unkstruct_800B5CB8 *)a0)->unk104 = 0;
        func_8012A828(a0, D_801B4C8C);

        if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkCC, D_801B4D7C);
        }
        if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkD0, D_801B4E6C);
        }
    }
}


extern u8 D_801B498C[];
extern u8 D_801B4A8C[];
extern u8 D_801B4B8C[];
extern void func_8012A828(s32 a0, void * a1);

void func_8018324C(s32 a0) {
    if (((Unkstruct_800B5CB8 *)a0)->unk100 == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unk100 = 0x3C;
        func_8012A828(a0, D_801B498C);
        if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkCC, D_801B4A8C);
        }
        if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkD0, D_801B4B8C);
        }
    } else {
        ((Unkstruct_800B5CB8 *)a0)->unk100 = ((Unkstruct_800B5CB8 *)a0)->unk100 - 1;
    }
}



extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_801832EC(s32 a0)
{
    s32 t;
    u32 *p;

    t = ((Unkstruct_800B5CB8 *)a0)->unk1C - 1;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = t;

    if (t != 0) {
        p = CAST_SIGN(u32 *, a0, 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((((Unkstruct_800B5CB8 *)a0)->unk1C & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                ((Unkstruct_800B5CB8 *)obj)->unk1C = 2;
                ((Unkstruct_800B5CB8 *)obj)->unk12 = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                ((Unkstruct_800B5CB8 *)obj)->unk1A = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern u8 D_801B498C[];
extern u8 D_801B4A8C[];
extern u8 D_801B4B8C[];
extern void func_8012A828(s32 a0, void * a1);

void func_801833AC(s32 a0) {
    s16 v0;

    v0 = ((Unkstruct_800B5CB8 *)a0)->unkFC;
    if (v0 == 0) {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 1;
        func_8012A828(a0, D_801B498C);
        if (((Unkstruct_800B5CB8 *)a0)->unkCC != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkCC, D_801B4A8C);
        }
        if (((Unkstruct_800B5CB8 *)a0)->unkD0 != 0) {
            func_8012A828(((Unkstruct_800B5CB8 *)a0)->unkD0, D_801B4B8C);
        }
    } else {
        ((Unkstruct_800B5CB8 *)a0)->unkFC = v0 - 1;
    }
}




















void func_80183444(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern u8 D_801AD514[];
extern u8 D_801AD548[];
extern u8 D_801B244C[];
extern u8 D_801B4A8C[];
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8012B030(u8 *a0);
extern void func_8012B23C(s32 a0);

void func_80183464(a0)
s32 a0;
{

    extern u8 D_801AD514[];
    extern u8 D_801B244C[];
    extern u8 D_801B4A8C[];
    extern u8 D_801AD548[];

    s32 v0;

    v0 = func_8012C354(a0, (s32)D_801AD514);
    if (v0 != 0) {
        if (((Unkstruct_800B5CB8 *)a0)->unk70 != 0) {
            func_8001C214(((Unkstruct_800B5CB8 *)a0)->unk20, (s32)D_801B244C);
        }
        ((Unkstruct_800B5CB8 *)a0)->unkC0 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unkB4 = 0xFFFFDFDF;
        func_8012B030(a0);
        ((Unkstruct_800B5CB8 *)a0)->unkAE = 0x2100;
        func_8012A828(a0, D_801B4A8C);
        ((Unkstruct_800B5CB8 *)a0)->unk2 = CAST_SIGN(u16, a0, 2) + 1;
        func_8012B23C(a0);
        CAST_SIGN(void *, a0, 0xBC) = D_801AD548;
        ((Unkstruct_800B5CB8 *)a0)->unkC4 = CAST_SIGN(u32, a0, 0xC4) | 2;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk2C = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk2C | 0x10;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk18 = 0x2400;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk1A = 0x2400;
        *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x1C) = 0x2400;
    }
}


void func_80183554(void) {
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8012B370(int a0);

void func_8018355C(s32 a0) {
    u16 cnt;
    u16 acc;

    if (*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) < 0x401) {
        cnt = CAST_SIGN(u16, a0, 0xFC);
        acc = CAST_SIGN(u16, a0, 0xFE);
        cnt = cnt + 1;
        acc = acc + cnt;
        ((Unkstruct_800B5CB8 *)a0)->unkFC = cnt;
        ((Unkstruct_800B5CB8 *)a0)->unkFE = acc;
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
            *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) + acc;
        ((Unkstruct_800B5CB8 *)a0)->unkA = ((Unkstruct_800B5CB8 *)a0)->unkA - 4;
        CAST_WIDTH(s32, a0, 4) = CAST_WIDTH(s32, a0, 4) +
            func_80047948(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x40;
        CAST_WIDTH(s32, a0, 0xC) = CAST_WIDTH(s32, a0, 0xC) -
            func_8004787C(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x40;
    } else {
        ((Unkstruct_800B5CB8 *)a0)->unk2 = 3;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x1E;
        ((Unkstruct_800B5CB8 *)a0)->unk98 = 0;
    }
    func_8012B370(a0);
}



extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80183630(s32 a0)
{
    s32 t;
    u32 *p;

    t = ((Unkstruct_800B5CB8 *)a0)->unk1C - 1;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = t;

    if (t != 0) {
        p = CAST_SIGN(u32 *, a0, 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((((Unkstruct_800B5CB8 *)a0)->unk1C & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                ((Unkstruct_800B5CB8 *)obj)->unk1C = 2;
                ((Unkstruct_800B5CB8 *)obj)->unk12 = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                ((Unkstruct_800B5CB8 *)obj)->unk1A = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int);
void func_801836F0(void) {
    ((void (*)(void))func_8012B370)();
}




















void func_80183710(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}


void func_80183730(s32 a0) {

    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 func_8012B030(u8 *a0);
    extern void func_8012A828(s32 a0, void * a1);
    extern void func_8012B23C(s32 a0);

    extern u8 D_801AD58C[];
    extern u8 D_801B31B8[];
    extern u8 D_801AD5C0[];
    extern u8 D_801B4B8C[];

    s32 v0;

    v0 = func_8012C354(a0, D_801AD58C);
    if (v0 != 0) {
        if (((Unkstruct_800B5CB8 *)a0)->unk70 != 0) {
            func_8001C214(((Unkstruct_800B5CB8 *)a0)->unk20, (s32)D_801B31B8);
        }
        ((Unkstruct_800B5CB8 *)a0)->unkC0 = 1;
        ((Unkstruct_800B5CB8 *)a0)->unkB4 = 0xFFFFDFDF;
        func_8012B030(a0);
        CAST_SIGN(void *, a0, 0xBC) = D_801AD5C0;
        ((Unkstruct_800B5CB8 *)a0)->unkAE = 0x2100;
        ((Unkstruct_800B5CB8 *)a0)->unkC4 = CAST_SIGN(u32, a0, 0xC4) | 2;
        func_8012A828(a0, D_801B4B8C);
        ((Unkstruct_800B5CB8 *)a0)->unk2 = CAST_SIGN(u16, a0, 2) + 1;
        func_8012B23C(a0);
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk2C = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk2C | 0x10;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk18 = 0x2400;
        ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk1A = 0x2400;
        *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x1C) = 0x2400;
    }
}


void func_80183824(void) {
}


extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012B370(s32 a0);

void func_8018382C(s32 a0) {
    s16 ang;
    u16 cnt;
    u16 acc;

    ang = *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14);
    if (ang < 0xC00) {
        if (ang != 0) {
            goto state3;
        }
    }

    cnt = CAST_SIGN(u16, a0, 0xFC);
    acc = CAST_SIGN(u16, a0, 0xFE);
    cnt = cnt + 1;
    acc = acc + cnt;
    ((Unkstruct_800B5CB8 *)a0)->unkFC = cnt;
    ((Unkstruct_800B5CB8 *)a0)->unkFE = acc;
    *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) - acc;

    *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) =
        *(u16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x14) & 0xFFF;

    ((Unkstruct_800B5CB8 *)a0)->unkA = ((Unkstruct_800B5CB8 *)a0)->unkA - 8;

    CAST_WIDTH(s32, a0, 4) = CAST_WIDTH(s32, a0, 4) -
        func_80047948(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x80;

    CAST_WIDTH(s32, a0, 0xC) = CAST_WIDTH(s32, a0, 0xC) +
        func_8004787C(*(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12)) * 0x80;
    goto tail;

state3:
    ((Unkstruct_800B5CB8 *)a0)->unk2 = 3;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x1E;
    ((Unkstruct_800B5CB8 *)a0)->unk98 = 0;

tail:
    func_8012B370(a0);
}



extern void func_8012B370(int a0);
extern void func_8012C218(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_80183920(s32 a0)
{
    s32 t;
    u32 *p;

    t = ((Unkstruct_800B5CB8 *)a0)->unk1C - 1;
    ((Unkstruct_800B5CB8 *)a0)->unk1C = t;

    if (t != 0) {
        p = CAST_SIGN(u32 *, a0, 0x20);
        p[1] ^= 0x80000000;
        func_8012B370(a0);

        if ((((Unkstruct_800B5CB8 *)a0)->unk1C & 0x3) != 0) {
            s32 obj = func_8012C588(0x281, a0);
            if (obj != 0) {
                ((Unkstruct_800B5CB8 *)obj)->unk1C = 2;
                ((Unkstruct_800B5CB8 *)obj)->unk12 = (rand() & 0x1F) - 0x10;
                *(s16 *)(obj + 0x16) = -((rand() & 0xF) + 0x10);
                ((Unkstruct_800B5CB8 *)obj)->unk1A = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    func_8012C218((void *)a0);
}


extern void func_8012B370(int a0);
    void func_801839E0(void) {
        ((s32 (*)(void))func_8012B370)();
    }


extern void (*D_801B52BC[])(void);
extern void func_80187250(void *a0);
extern void func_80187320(void *a0);
extern void func_8012C0EC(void *a0);

void func_80183A00(void *a0) {
    D_801B52BC[CAST_SIGN(u16, (s32)a0, 0x2)]();
    if (((Unkstruct_800B5CB8 *)a0)->unk0 != 0) {
        func_80187250(a0);
        func_80187320(a0);
        func_8012C0EC(a0);
    }
}


// @class: struct
// @unstuck(P36): none — MATCH (135/135 ins, match_one confirmed)

extern Elem52_801B5094 D_801B5094[];
extern u8 D_801B522C[];
extern u8 D_801B51B4[];
extern u8 D_801CC180[];
extern u16 D_801CC674;
extern u16 D_801CC4CC;

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_8012B030(u8 *a0);
extern void func_8012B2CC(s32 a0);

void func_80183A70(s32 param_1) {
    s32 iVar1;
    u16 uVar2;

    iVar1 = func_8012C354(param_1, &D_801B5094[CAST_SIGN(u16, param_1, 0x70) & 0xf]);
    if (iVar1 != 0) {
        ((Unkstruct_800B5CB8 *)param_1)->unkC0 = 1;
        CAST_SIGN(u8 *, param_1, 0xbc) = D_801B522C;
        ((Unkstruct_800B5CB8 *)param_1)->unkB4 = -0x8ad;
        CAST_SIGN(u32, param_1, 0xc4) |= 2;
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk2C |= 0x80;
        *(u8 **)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x80) = D_801B51B4;
        func_80143994(param_1, 0x4000);
        ((Unkstruct_800B5CB8 *)param_1)->unk48 = 0x18000;
        uVar2 = CAST_SIGN(u16, param_1, 0x70) & 0xf;
        switch (uVar2) {
        case 0: {
            s32 t;
            CAST_SIGN(u32, param_1, 0xe0) |= 1;
            t = (s32)*(u16 *)(((Unkstruct_800B5CB8 *)param_1)->unk78) << 0x10;
            ((Unkstruct_800B5CB8 *)param_1)->unkFE = (s16)((t >> 0x10) / 2);
            if (((s32)((Unkstruct_800B5CB8 *)param_1)->unk70 & 0x8000) == 0) {
                ((Unkstruct_800B5CB8 *)param_1)->unk2 = 2;
            } else {
                ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
                ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0x1e;
                func_8012A828(param_1, &D_801CC180);
            }
            break;
        }
        case 1:
            CAST_ALIAS(s16, param_1, 2) = 0x13;
            D_801CC674 = 0x28;
            if (((s32)CAST_ALIAS(s16, param_1, 0x70) & 0x8000) != 0) {
                CAST_SIGN(u32, param_1, 0xe0) |= 0x400;
            }
            break;
        case 2:
            ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x18;
            D_801CC4CC = 0x28;
            break;
        case 3:
            ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x1f;
            if (func_8012C658(0x27f, 5, param_1) == 0) {
                func_8012CAE4(param_1);
                return;
            }
            break;
        }
        func_8012B030(param_1);
        CAST_WIDTH(s32, param_1, 0x38) = CAST_WIDTH(s32, param_1, 4);
        *(s32 *)(param_1 + 0x3c) = CAST_WIDTH(s32, param_1, 8);
        *(s32 *)(param_1 + 0x40) = CAST_WIDTH(s32, param_1, 0xc);
        func_8012B2CC(param_1);
    }
}


void func_80183C8C(s32 p) {
    if (((Unkstruct_800B5CB8 *)p)->unk1C == 0xF) {
        func_80142414(p, -0x90);
    }
    if (func_8012BEE8(p) != 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 2;
    }
}


#include "common.h"

/* func_80183CDC — a randomised state entry: seed the timer at 0x1C with
 * rand()%64 + 0x80, park 18000 at 0x48, then nudge the value at 0xE8 by a
 * random 0..1023 in a random direction, push the command list D_801CCCA0,
 * set the state word at 0x02 to 3 and clear bit 6 of the flags at 0xE0.
 *
 * §71 sibling-first: func_8018598C (same TU, MATCHed) is the same
 * `if ((rand() & 1) == 0) v = base - off; else v = base + off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void * a1);
extern u8 D_801CCCA0[];

void func_80183CDC(s32 param_1) {
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    r = rand();
    ((Unkstruct_800B5CB8 *)param_1)->unk1C = r % 0x40 + 0x80;
    ((Unkstruct_800B5CB8 *)param_1)->unk48 = 18000;

    r = rand();
    off = r % 0x400;
    base = ((Unkstruct_800B5CB8 *)param_1)->unkE8;
    if ((rand() & 1) != 0) {
        nv = base + off;
    } else {
        nv = base - off;
    }
    ((Unkstruct_800B5CB8 *)param_1)->unkE8 = nv;

    func_8012A828(param_1, D_801CCCA0);
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 3;
    CAST_SIGN(u32, param_1, 0xE0) &= 0xFFFFFFBF;
}


extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32 rand(void);

void func_80183DA4(s32 param_1)
{
    s32 p = param_1;
    s32 r;
    s32 s0;
    s32 s2;

    ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 8);
    func_8012B178(p, 0xFFFB0000);

    CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFBF;
    if (func_8018765C(p) == 0) {
        func_801877E4(p);
    }

    r = func_8012BDBC(p, 0x300);
    if (r != 0) {
        r = func_8012BCCC(p);
        if (r < 0x100000) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
            return;
        }
    } else {
        r = func_8012BCCC(p);
        if (r < 0x4000) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0xF;
            return;
        }
    }

    if ((CAST_SIGN(u32, p, 0xE0) & 0x40) != 0) {
        return;
    }
    if (func_8012BEE8(p) == 0) {
        return;
    }

    s0 = rand() % 1024;
    s2 = ((Unkstruct_800B5CB8 *)p)->unkE8;
    if ((rand() & 1) == 0) {
        r = s2 - s0;
    } else {
        r = s2 + s0;
    }
    ((Unkstruct_800B5CB8 *)p)->unkE8 = r;
    ((Unkstruct_800B5CB8 *)p)->unk1C = (rand() % 64) + 0x80;
}




extern void func_8012A828(s32 a0, void * a1);

void func_80183F10(s32 param_1)
{

    extern u8 D_801CC1E8[];
    func_8012A828(param_1, D_801CC1E8);
    ((Unkstruct_800B5CB8 *)param_1)->unk48 = 0x4650;
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x5;
}


#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern u16  D_800B99DA;
extern s32  func_80143B6C(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_80187844(s32 a0, s32 a1);
extern s32  D_801D55A8;

void func_80183F50(s32 p)
{
    s32 s1;
    s32 e;

    ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += func_8012B8E4(p, 8);
    func_8012B178(p, 0xFFF90000);

    if ((u32)D_800B99DA % 10 == 0) {
        e = func_80143B6C(p, 0);
        if (e != 0) {
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x18) = 0x5000;
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x1A) = 0x5000;
        }
    }

    func_8018765C(p);

    if (func_8012BDBC(p, 0x300) == 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 6;
        return;
    }
    s1 = func_8012BCCC(p);
    if (s1 >= 0x100000) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 6;
        return;
    }
    if (s1 < 0x6400) {
        e = func_80187844(p, 0);
        if (e == 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 8;
            return;
        }
        if (s1 < D_801D55A8) {
            s32 rv = 8;
            ((Unkstruct_800B5CB8 *)p)->unk2 = rv;
        }
        return;
    }
    if (0x13FFE < s1 - 0x10001U) {
        return;
    }
    e = func_8012BDBC(p, 0x100);
    if (e == 0) {
        return;
    }
    e = func_80187844(p, 0);
    if (e == 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0xA;
        return;
    }
    if (D_801D55A8 <= s1) {
        return;
    }
    ((Unkstruct_800B5CB8 *)p)->unk2 = 8;
}


extern void func_8012A828(s32 a0, void * a1);
extern u8 D_801CC180[];

void func_801840D8(s32 param_1) {
    ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0x20;
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 7;
    func_8012A828(param_1, D_801CC180);
}


void func_8018410C(s32 p) {
    s32 v;

    if (func_8012BDBC(p, 0x300) != 0) {
        v = func_8012BCCC(p);
        if (v < 0x100000) {
            if (v < 0x6400) {
                ((Unkstruct_800B5CB8 *)p)->unk2 = 8;
            } else {
                ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
            }
            return;
        }
    } else {
        v = func_8012BCCC(p);
        if (v < 0x4000) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0xF;
            return;
        }
    }

    if (func_8012BEE8(p) != 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 2;
    }
}


extern u8 D_801CC290[];
extern void func_8012A828(s32 a0, void * a1);

void func_80184194(s32 param_1) {
    func_8012A828(param_1, D_801CC290);
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 9;
    ((Unkstruct_800B5CB8 *)param_1)->unkE0 = (CAST_SIGN(u32, param_1, 0xE0) | 2) & 0xFFFFFFEF;
}


#include "common.h"

extern s32  func_80187130(s32 a0, s32 a1);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32 func_80189E60(s32 arg0, u16 arg1);
extern void func_8012A828(s32 a0, void * a1);
extern u8   D_801CC290[];
extern u8   D_801CCBA8[];

void func_801841E0(s32 p)
{
    s32 v0;
    s32 s1;

    if (func_80187130(p, 0x64) == 1) {
        CAST_SIGN(u32, p, 0xE0) |= 0x10;
    }

    if (((Unkstruct_800B5CB8 *)p)->unk90 == (s32) D_801CC290) {
        if (((Unkstruct_800B5CB8 *)p)->unk94 == 0xB) {
            ((s32 (*)())func_80189E60)(p, 0x8C0);
        }
    } else {
        if (((Unkstruct_800B5CB8 *)p)->unk94 == 8) {
            ((s32 (*)())func_80189E60)(p, 0x8C0);
        }
    }

    if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
        if (func_8012BDBC(p, 0x300) == 0) {
            v0 = 6;
            goto set_and_return;
        }
        s1 = func_8012BCCC(p);
        if (s1 >= 0x100000) {
            v0 = 2;
            goto set_and_return;
        }
        if (s1 < 0x4000) {
            func_8012A828(p, D_801CCBA8);
            CAST_SIGN(u32, p, 0xE0) &= ~0x10;
            return;
        } else if (s1 < 0x6400) {
            if ((((Unkstruct_800B5CB8 *)p)->unkE0 & 0x10) == 0) {
                func_8012A828(p, D_801CCBA8);
                return;
            }
            func_8012A828(p, D_801CC290);
            CAST_SIGN(u32, p, 0xE0) &= ~0x10;
            return;
        } else {
            v0 = 4;
            goto set_and_return;
        }
    }
    return;

set_and_return:
    ((Unkstruct_800B5CB8 *)p)->unk2 = v0;
}


extern u8 D_801CCBA8[];
extern void func_8012A828(s32 a0, void * a1);

void func_8018431C(void *arg0) {
    func_8012A828((s32)arg0, D_801CCBA8);
    ((Unkstruct_800B5CB8 *)arg0)->unk2 = 0xB;
    CAST_WIDTH(s32, (s32)arg0, 0x10) *= 2;
    CAST_WIDTH(s32, (s32)arg0, 0x18) *= 2;
    ((Unkstruct_800B5CB8 *)arg0)->unk34 = 0;
}


#include "common.h"

extern s32  func_80187130(s32 a0, s32 a1);
extern u16  D_80126B96;
extern s32  func_8018765C(s32 a0);
extern u16  D_800B99DA;
extern s32  func_80143B6C(s32 a0, s32 a1);
extern s32 func_80189E60(s32 arg0, u16 arg1);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)

void func_80184370(s32 p)
{
    s32 e;

    if (func_80187130(p, 0x64) == 1) {
        D_80126B96 = 4;
    }

    CAST_WIDTH(s32, p, 0x10) = CAST_WIDTH(s32, p, 0x10) * 31 / 32;
    CAST_WIDTH(s32, p, 0x18) = CAST_WIDTH(s32, p, 0x18) * 31 / 32;
    func_8018765C(p);

    if ((u32)D_800B99DA % 6 == 0) {
        e = func_80143B6C(p, 0);
        if (e != 0) {
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x18) = 0x5000;
            *(s16 *)(*(s32 *)(e + 0xCC) + 0x1A) = 0x5000;
        }
    }

    if (((Unkstruct_800B5CB8 *)p)->unk94 == 8) {
        ((s32 (*)())func_80189E60)(p, 0x8C0);
    }

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        if (((Unkstruct_800B5CB8 *)p)->unk94 == 0xE) {
            ((Unkstruct_800B5CB8 *)p)->unk98 = 0;
            ((Unkstruct_800B5CB8 *)p)->unk1C = 0x1E;
            ((Unkstruct_800B5CB8 *)p)->unk34 += 1;
        }
    } else {
        if (func_8012BEE8(p) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 6;
        }
    }
}


void func_801844C0(void *arg0) {
    extern void func_8012A828(s32 a0, void * a1);
    extern s32 D_801CC4D8;

    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801CC4D8);
    ((Unkstruct_80182F48_2 *)arg0)->unk2 = 0xD;
    ((Unkstruct_80182F48_2 *)arg0)->unk1C = 0x28;
}


extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_8012F214(s32, s32, s32);
extern s32  func_80189284(void *a0, s32 a1, s32 a2);
extern s32 D_80126B9C;
extern u8 D_801B5164[];

void func_80184500(s32 p) {
    s32 buf10[2];

    func_8012F214(p, D_801B5164, buf10);
    if (func_8012BEE8(p) != 0 && !(D_80126B9C & 2)) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
    } else if (func_80189284(buf10, *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), 0x400) == 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
    }
}


extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern s32 func_80013350(s32 a0, void *a1);

extern u8 D_801BB67C;
extern u8 D_801B7EB8;
extern u8 D_801CC1E8[];
extern u8 D_801CD0E8[];

void func_8018457C(s32 p)
{
    u16 uVar1;
    s32 s1;
    s32 r;

    uVar1 = ((Unkstruct_800B5CB8 *)p)->unk34;
    switch (uVar1) {
    case 0:
        s1 = ((Unkstruct_800B5CB8 *)p)->unkCC;
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != ((Unkstruct_800B5CB8 *)p)->unkEC ||
            func_8012BEE8(p) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x23;
            CAST_SIGN(u32, p, 0xE0) |= 0x800;
            return;
        }
        goto call_b6d4;
    case 1:
        if (((Unkstruct_800B5CB8 *)p)->unk98 != 0) {
            return;
        }
        func_8012C218((void *)((Unkstruct_800B5CB8 *)p)->unkCC);
        ((Unkstruct_800B5CB8 *)p)->unkCC = 0;
        func_8001C924(((Unkstruct_800B5CB8 *)p)->unk20, &D_801BB67C);
        func_8012A828(p, D_801CC1E8);
        {
            u16 ns;
            ns = ((Unkstruct_800B5CB8 *)p)->unk34;
            ((Unkstruct_800B5CB8 *)p)->unk1C = 0x200;
            ns = ns + 1;
            CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFFB;
            ((Unkstruct_800B5CB8 *)p)->unk34 = ns;
        }
        return;
    case 2:
        s1 = ((Unkstruct_800B5CB8 *)p)->unkD0;
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != ((Unkstruct_800B5CB8 *)p)->unkEE ||
            func_8012BEE8(p) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
            CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFFE;
            return;
        }
    call_b6d4:
        r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s1 + 4));
        ((Unkstruct_800B5CB8 *)p)->unkE8 = r;
        goto LAB_80184738;
    case 3:
        func_8012C218((void *)((Unkstruct_800B5CB8 *)p)->unkD0);
        ((Unkstruct_800B5CB8 *)p)->unkD0 = 0;
        func_8001C924(((Unkstruct_800B5CB8 *)p)->unk20, &D_801B7EB8);
        func_8012A828(p, D_801CC1E8);
        ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
        ((Unkstruct_800B5CB8 *)p)->unk2 = 5;
        CAST_SIGN(u32, p, 0xE0) |= 1;
        return;
    default:
        goto LAB_80184738;
    }

LAB_80184738:
    r = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 8);
    ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 =
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 + r;

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        func_8012B178(p, 0xFFF8D000);
    } else {
        func_8012B178(p, 0xFFF90000);
    }

    func_8018765C(p);

    r = ((s32(*)(s32, s32))func_80013350)(p + 4, s1 + 4);
    if (r < 0x900) {
        if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
            func_8012A828(p, D_801CD0E8);
        }
        ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
    }
}


extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8012B864(s32 a0);
extern u8 D_801CC180[];

void func_801847FC(s32 a0) {
    func_8012A828(a0, D_801CC180);
    ((Unkstruct_800B5CB8 *)a0)->unk2 = 0x10;
    ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
    ((Unkstruct_800B5CB8 *)a0)->unkE8 = func_8012B864(a0);
}


#include "common.h"

extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_80142414(s32 a0, s16 a1);

void func_80184844(s32 p) {
    s32 r;

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        r = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 4);
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += r;
        if (func_8012BDBC(p, 0x200) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk1C = 0xF;
            ((Unkstruct_800B5CB8 *)p)->unk34 += 1;
            func_80142414(p, -0x90);
        } else if (r == 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 2;
        }
    } else if (func_8012BEE8(p) != 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 4;
    }
}




extern void func_8012A828(s32 a0, void * a1);

void func_80184904(s32 param_1)
{

    extern u8 D_801CC868[];
    func_8012A828(param_1, D_801CC868);
    ((Unkstruct_800B5CB8 *)param_1)->unk48 = 0x4650;
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x12;
}


#include "common.h"

extern s32  func_8012BCCC(s32 a0);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32  func_8012B8A4(s16 *a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern s32  rand(void);

void func_80184944(s32 p)
{
    s32 v;
    s32 r;
    s32 t;

    v = func_8012BCCC(p);
    if (v > 0x144000) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x13;
        return;
    }

    if (v > 0xC4000) {
        if ((CAST_SIGN(u32, p, 0xE0) & 0x40) == 0) {
            r = func_8012B8E4(p, 8);
            ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += r;
        }
    } else {
        if ((u32)(v - 0x24000) <= 0xA0000) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x15;
            return;
        }

        if ((CAST_SIGN(u32, p, 0xE0) & 0x40) == 0) {
            if (func_8012BEE8(p) != 0) {
                t = func_8012B8A4((s16 *)p);
                ((Unkstruct_800B5CB8 *)p)->unkE8 = (t + 0x800) & 0xFFF;
                r = rand();
                ((Unkstruct_800B5CB8 *)p)->unk1C = r % 0x40 + 0x40;
            }
        }

        r = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 8);
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += r;
    }

    func_8012B178(p, 0xFFF9C000);
    CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFBF;
    if (func_8018765C(p) == 0) {
        func_801877E4(p);
    }
}


extern u8 D_801B4F5C[];
extern u8 D_801CC530[];
extern void func_8012A828(s32 a0, void * a1);

void func_80184AA8(p)
s32 p;
{
    extern u8 D_801B4F5C[];
    extern u8 D_801CC530[];

    ((Unkstruct_800B5CB8 *)p)->unk2 = 0x14;
    if (!(CAST_SIGN(u32, p, 0xE0) & 0x400)) {
        ((Unkstruct_800B5CB8 *)p)->unk34 = 1;
        func_8012A828(p, D_801CC530);
    } else {
        ((Unkstruct_800B5CB8 *)p)->unk34 = 0;
        func_8012A828(p, D_801B4F5C);
    }
}


extern s32  func_8012BCCC(s32 a0);
extern void func_8012A828(s32 a0, void * a1);

extern u8 D_801CC530[];
extern u8 D_801CC868[];
extern u8 D_801CC920[];

void func_80184AFC(s32 p)
{
    s32 v;

    switch (((Unkstruct_800B5CB8 *)p)->unk34) {
    case 0:
        if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
            func_8012A828(p, D_801CC530);
            ((Unkstruct_800B5CB8 *)p)->unk34 += 1;
        }
        break;
    case 1:
        v = func_8012BCCC(p);
        if (v > 0x24000) {
            break;
        }

        if ((CAST_SIGN(u32, p, 0xE0) & 0x400) == 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x15;
        } else {
            func_8012A828(p, D_801CC920);
            ((Unkstruct_800B5CB8 *)p)->unk34 += 1;
        }
        break;
    case 2:
        if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
            func_8012A828(p, D_801CC868);
            ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x12;
        }
        break;
    }
}


extern u8 D_801CC530[];
extern void func_8012A828(s32 a0, void * a1);

void func_80184C0C(a0)
s32 a0;
{
    extern u8 D_801CC530[];

    ((Unkstruct_800B5CB8 *)a0)->unk2 = 0x16;
    if ((CAST_SIGN(u32, a0, 0xE0) & 0x400) == 0) {
        func_8012A828(a0, D_801CC530);
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 4;
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0xF;
    } else {
        ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x1E;
        ((Unkstruct_800B5CB8 *)a0)->unk34 = 0;
    }
}


#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_8012A828(s32 a0, void * a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80180354(s32, s32);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80189E60(s32 arg0, u16 arg1);

extern u8 D_801B4F5C[];
extern u8 D_801B5174[];
extern u8 D_801CC530[];
extern u8 D_801CC598[];
extern u8 D_801CC868[];
extern u8 D_801CC920[];

void func_80184C74(s32 p)
{
    s16 v18[4];   /* sp+0x18 */
    s32 mat[8];   /* sp+0x20 - MATRIX: 3x3 s16 + pad, 3 s32 at +0x14 */
    s32 s0;

    switch (((Unkstruct_800B5CB8 *)p)->unk34) {
    case 0:
        s0 = func_8012B8E4(p, 8);
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += s0;
        if (func_8012BEE8(p) == 0 && s0 != 0) {
            return;
        }
        func_8012A828(p, D_801B4F5C);
        ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
        break;

    case 1:
        if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
            func_8012A828(p, D_801CC598);
            ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
        }
        break;

    case 2:
        if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
            if (func_8012E778(p, 0xA000C8) == 0) {
                ((Unkstruct_800B5CB8 *)p)->unk2 = 0x14;
                if ((((Unkstruct_800B5CB8 *)p)->unkE0 & 0x400) == 0) {
                    ((Unkstruct_800B5CB8 *)p)->unk34 = 1;
                    func_8012A828(p, D_801CC530);
                } else {
                    ((Unkstruct_800B5CB8 *)p)->unk34 = 0;
                    func_8012A828(p, D_801B4F5C);
                }
                return;
            }
            s0 = func_8012BCCC(p);
            if ((((Unkstruct_800B5CB8 *)p)->unkE0 & 0x400) == 0) {
                if (0x63FFF < s0) {
                    ((Unkstruct_800B5CB8 *)p)->unk2 = 0x14;
                    if ((((Unkstruct_800B5CB8 *)p)->unkE0 & 0x400) == 0) {
                        ((Unkstruct_800B5CB8 *)p)->unk34 = 1;
                        func_8012A828(p, D_801CC530);
                    } else {
                        ((Unkstruct_800B5CB8 *)p)->unk34 = 0;
                        func_8012A828(p, D_801B4F5C);
                    }
                    return;
                }
            } else if (0xA0000 < (u32)(s0 - 0x24000)) {
                func_8012A828(p, D_801CC920);
                ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
                break;
            }
        }

        if (((Unkstruct_800B5CB8 *)p)->unk94 < 8) {
            ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += func_8012B8E4(p, 8);
        }
        if (((Unkstruct_800B5CB8 *)p)->unk94 != 7) {
            return;
        }

        func_8012EA90(p, 0xB, mat);
        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_801B5174, v18);
        ((void (*)(s32, void *))func_80180354)(p, v18);

        /* gte_SetRotMatrix */
        gte_SetRotMatrix(((Unkstruct_800B5CB8 *)p)->unk20 + 0x34);

        /* column 0: gte_ldclmv / gte_rtir / gte_stclmv */
        gte_ldclmv((s16 *)mat);
        gte_rtir();
        gte_stclmv((s16 *)mat);

        /* column 1 */
        gte_ldclmv((s16 *)mat + 1);
        gte_rtir();
        gte_stclmv((s16 *)mat + 1);

        /* column 2 */
        gte_ldclmv((s16 *)mat + 2);
        gte_rtir();
        gte_stclmv((s16 *)mat + 2);

        /* gte_SetTransMatrix */
        gte_SetTransMatrix(((Unkstruct_800B5CB8 *)p)->unk20 + 0x34);

        /* gte_ldlvl / gte_rt / gte_stlvnl on the translation vector */
        gte_ldlv0(&mat[5]);
        gte_rtv0tr();
        gte_stlvnl(&mat[5]);

        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_801B5174, v18);
        func_8018931C(p, v18, 0x282, 2, -0x120, 0);
        func_8018931C(p, v18, 0x282, 2, 0, 0);
        func_8018931C(p, v18, 0x282, 2, 0x120, 0);
        ((s32 (*)())func_80189E60)(p, 0x8BD);
        return;

    case 3:
        if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
            func_8012A828(p, D_801CC868);
            ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x12;
        }
        return;

    case 4:
        if (func_8012BEE8(p) != 0) {
            func_8012A828(p, D_801CC598);
            ((Unkstruct_800B5CB8 *)p)->unk34 = 2;
        }
        break;
    }
}


#include "common.h"

/* Host TU: src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c
 * Insertion point replaces the INCLUDE_ASM at line 6996, in scope after the
 * decl block that begins at line 6786 (#include "common.h"). That block
 * ALREADY declares (in scope, do not redeclare):
 *   extern s32  func_8012BEE8();                       (line 6789)
 *   extern void func_8012A828(s32 a0, void *a1);        (line 6790)
 *   extern u8   D_801CC868[];                           (line 6803)
 * and elsewhere earlier in the SAME TU (still in scope, file-scope extern):
 *   extern void func_80013350(s32 a0, void *a1);        (line 6647)
 *     -- loose prototype (real callee takes/returns s32,s32->s32); per
 *        cookbook §161c do NOT add a conflicting extern here, cast at the
 *        call site instead (matches the TU's own sibling func_8018457C).
 * New decls needed for this function (not yet declared in this TU's scope
 * at the insertion point):
 *   func_8012B6D4, func_8012B608, func_8012B178, func_8018765C,
 *   func_8012C218, func_8001C924, D_801CD0E8[], D_801BC090[]
 * (func_8012B6D4/B608/B178/8765C signatures copied verbatim from this TU's
 * other declarations of the same symbols, e.g. lines 6643-6646/7043-7045;
 * func_8012C218/func_8001C924 copied from lines 6639-6640.)
 */

extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80013350(s32 a0, void *a1); /* loose proto, real TU decl (line 6647); cast at call site per §161c */
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);

extern u8 D_801CD0E8[];
extern u8 D_801CC868[];
extern u8 D_801BC090[];

void func_801850F4(s32 p)
{
    s32 s1;
    s32 r;

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        s1 = ((Unkstruct_800B5CB8 *)p)->unkCC;
        if (s1 == 0 || CAST_SIGN(s16, s1, 0x36) != ((Unkstruct_800B5CB8 *)p)->unkEC ||
            func_8012BEE8(p) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x23;
            CAST_SIGN(u32, p, 0xE0) |= 0x800;
            return;
        }

        r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s1 + 4));
        ((Unkstruct_800B5CB8 *)p)->unkE8 = r;

        r = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 8);
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 =
            ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 + r;

        func_8012B178(p, 0xFFF8D000);
        func_8018765C(p);

        r = ((s32 (*)(s32, s32))func_80013350)(p + 4, s1 + 4);
        if (r < 0x900) {
            ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
            func_8012A828(p, D_801CD0E8);
        }
    } else {
        if (((Unkstruct_800B5CB8 *)p)->unk98 != 0) {
            return;
        }
        func_8012C218((void *)((Unkstruct_800B5CB8 *)p)->unkCC);
        ((Unkstruct_800B5CB8 *)p)->unkCC = 0;
        func_8001C924(((Unkstruct_800B5CB8 *)p)->unk20, D_801BC090);
        func_8012A828(p, D_801CC868);
        ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x12;
        CAST_SIGN(u32, p, 0xE0) &= ~4;
    }
}


#include "common.h"

/* func_80185268 — randomised state entry (state word 0x19):
 * set the state at 0x02, push command list D_801CC7A0, seed the timer at
 * 0x1C with rand()%64 + 0x80, nudge the value at 0xE8 by a random 0..1023
 * in a random direction, then park 18000 at 0x48.
 *
 * §71 sibling-first: func_80183CDC / func_8018598C (same TU, MATCHed) are the
 * same `if ((rand() & 1) != 0) v = base + off; else v = base - off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void * a1);
extern u8 D_801CC7A0[];

void func_80185268(s32 param_1) {
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x19;
    func_8012A828(param_1, D_801CC7A0);

    r = rand();
    ((Unkstruct_800B5CB8 *)param_1)->unk1C = r % 0x40 + 0x80;

    r = rand();
    off = r % 0x400;
    base = ((Unkstruct_800B5CB8 *)param_1)->unkE8;
    if ((rand() & 1) != 0) {
        nv = base + off;
    } else {
        nv = base - off;
    }
    ((Unkstruct_800B5CB8 *)param_1)->unkE8 = nv;

    ((Unkstruct_800B5CB8 *)param_1)->unk48 = 18000;
}


#include "common.h"

extern u8 D_801B5164[];

extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_80189284(void *a0, s32 a1, s32 a2);
extern s32 func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */  // K&R: 0 of 1 args (P37 rung D t4_D22)

void func_80185320(s32 p) {
    s32 buf10[2];
    s32 r_b608;

    r_b608 = func_8012B608((s32)*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12),
                           ((Unkstruct_800B5CB8 *)p)->unkE8, 0x10);
    ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 =
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 + r_b608;
    func_8012B178(p, 0xFFFBD000);

    CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFBF;
    if (func_8018765C(p) == 0) {
        func_801877E4(p);
    }

    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf10);
    if (func_80189284(buf10, *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), 0x380) != 0 &&
        func_8012BCCC(p) < 0x64000) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x1C;
    } else if (func_8012BEE8(p) != 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x1A;
    }
}


extern u8 D_801CC358[];
extern void func_8012A828(s32 a0, void * a1);

void func_80185400(a0)
s32 a0;
{
    ((Unkstruct_800B5CB8 *)a0)->unk2 = 27;
    func_8012A828(a0, &(*(u8 *)D_801CC358));
    ((Unkstruct_800B5CB8 *)a0)->unk1C = 0x20;
}


extern u8 D_801B5164[];
extern void func_8012F214(s32, s32, s32);
extern s32 func_80189284(void *a0, s32 a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)

void func_80185440(s32 p) {
    s32 buf10[2];
    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf10);
    if (func_80189284(buf10, *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), 0x380) != 0 &&
        func_8012BCCC(p) < 0x64000) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x1C;
    } else if (func_8012BEE8(p) != 0) {
        ((Unkstruct_800B5CB8 *)p)->unk2 = 0x18;
    }
}



extern void func_8012A828(s32 a0, void * a1);
    extern short aD801CC358 __asm__("D_801CC358");
    void func_801854C0(short *a0) {
        ((Unkstruct_801854C0 *)a0)->unk2 = 0x1D;
        ((Unkstruct_801854C0 *)a0)->unk34 = 0;
        ((Unkstruct_801854C0 *)a0)->unk1C = 0xf;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (int)&aD801CC358);
    }


// @class: schedule
// @unstuck(P36): none — MATCH (181 ins, relocation-masked)








extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_8012A828(s32 a0, void * a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_80189380(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern s32 func_80189E60(s32 arg0, u16 arg1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80189284(void *a0, s32 a1, s32 a2);
extern s32 rand(void);

extern u8 D_801CC3D0[];
extern u8 D_801CC358[];
extern u8 D_801B517C[];
extern u8 D_801B518C[];
extern u8 D_801B5164[];

void func_801854F8(s32 p) {
    s32 buf58[8];   /* auStack_58  sp+0x18 (0x20) */
    s32 g38[4];     /* uStack_38/34, iStack_30 sp+0x38 (0x10) */
    u16 g28[4];     /* uStack_28/26/24 sp+0x48 (0x08) */
    u16 out[4];     /* func_80189380 output sp+0x50 (0x08) */
    s32 buf18[2];   /* auStack_18  sp+0x58 (0x08) */
    s32 i;
    s32 e;

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        if (func_8012BEE8() == 0) return;
        func_8012A828(p, D_801CC3D0);
        ((Unkstruct_800B5CB8 *)p)->unk34 += 1;
    }
    if (((Unkstruct_800B5CB8 *)p)->unk94 < 0xe) {
        ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 += func_8012B8E4(p, 8);
    }
    if (((Unkstruct_800B5CB8 *)p)->unk94 == 0xe) {
        func_80189380(p, D_801B517C, out, 0xb);
        func_8018931C(p, out, 0x282, 0, 0, 0);
        e = func_80132EF4(p, 0x22);
        if (e != 0) {
            *(u16 *)(e + 0x34) = 0x7002;
            *(u16 *)(e + 6) = out[0];
            *(u16 *)(e + 0xa) = out[1];
            *(u16 *)(e + 0xe) = out[2];
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc006;
        }
        g28[0] = 0x40;
        g28[1] = ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12;
        g28[2] = 0;
        ((void (*)(void *, void *))func_80049CAC)(g28, buf58);
        i = 0;
        do {
            e = func_80132EF4(p, 0x22);
            if (e != 0) {
                g38[1] = 0;
                g38[0] = 0;
                g38[2] = (rand() % 5 + 4) << 16;
                ((void (*)(void *, void *, s32))func_800484EC)(buf58, g38, e + 0x10);
                *(u16 *)(e + 0x34) = ((rand() % 2 + 2) << 12) | 1;
                *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc006;
                func_80189380(p, D_801B518C + i * 8, out, 0xb);
                *(u16 *)(e + 6) = out[0];
                *(u16 *)(e + 0xa) = out[1];
                *(u16 *)(e + 0xe) = out[2];
            }
            i++;
        } while (i < 5);
        ((s32 (*)())func_80189E60)(p, 0x8be);
    }
    if (((Unkstruct_800B5CB8 *)p)->unk72 & 0x4000) {
        ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf18);
        if (0x63fff < func_8012BCCC(p) ||
            func_80189284(buf18, *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), 0x380) == 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x1b;
            func_8012A828(p, D_801CC358);
            ((Unkstruct_800B5CB8 *)p)->unk1C = 0x20;
        }
    }
}


#include "common.h"

/* §160g sibling search: callee set {func_8012BEE8, func_8012B6D4, func_8012B608,
 * func_8012B178, func_8018765C, func_80013350, func_8012A828, func_8012C218,
 * func_8001C924} matches the ALREADY-MATCHED func_8018457C in this exact TU
 * (src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c, lines 6654-6733) almost verbatim --
 * that function's case 0 (the s1=*(p+0xCC) null/field-0x36-vs-0xEC/func_8012BEE8
 * mismatch guard, then func_8012B6D4 + the func_8012B608/func_8012B178/
 * func_8018765C/func_80013350 tail with the same D_801CD0E8 transition) is a
 * structural template for our "state==0" branch. The "state!=0" branch's tail
 * (set +2=0x1D, +0x34=0, +0x1C=0xF, call func_8012A828) is verbatim the body of
 * the tiny already-MATCHED func_801854C0 a few lines above ours in the same TU
 * (it uses a function-pointer cast only because ITS param is `short *`; ours is
 * already `s32 param_1` so a plain call suffices, mirroring func_801854F8's own
 * plain `func_8012A828(p, D_801CC358);` two lines before our INCLUDE_ASM slot).
 * The `*(u32*)(p+0xE0) &= 0xFFFFFFFB;` mask is byte-identical to func_8018457C's
 * case 1 mask. All extern decls below are copied verbatim from these matched
 * siblings' own decl blocks (same TU, same file-scope conventions).
 */

extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern s32 func_80013350(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);

extern u8 D_801CD0E8[];
extern u8 D_801BBC78;
extern u8 D_801CC358[];

void func_801857CC(s32 param_1)
{
    s32 s1;
    s32 uVar4;
    s32 sVar1;
    s32 r;

    if (((Unkstruct_800B5CB8 *)param_1)->unk34 == 0) {
        s1 = ((Unkstruct_800B5CB8 *)param_1)->unkCC;
        if (s1 == 0 || CAST_SIGN(s16, s1, 0x36) != ((Unkstruct_800B5CB8 *)param_1)->unkEC ||
            func_8012BEE8(param_1) != 0) {
            ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x23;
            CAST_SIGN(u32, param_1, 0xE0) |= 0x800;
            return;
        }

        uVar4 = func_8012B6D4((s16 *)(param_1 + 4), (s16 *)(s1 + 4));
        ((Unkstruct_800B5CB8 *)param_1)->unkE8 = uVar4;

        sVar1 = func_8012B608((s32)*(s16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12), uVar4, 8);
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12 =
            ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12 + sVar1;

        func_8012B178(param_1, 0xFFF8D000);
        func_8018765C(param_1);

        r = ((s32 (*)(s32, s32))func_80013350)(param_1 + 4, s1 + 4);
        if (r < 0x900) {
            ((Unkstruct_800B5CB8 *)param_1)->unk34 = ((Unkstruct_800B5CB8 *)param_1)->unk34 + 1;
            func_8012A828(param_1, D_801CD0E8);
        }
        return;
    }

    if (((Unkstruct_800B5CB8 *)param_1)->unk98 != 0) {
        return;
    }
    func_8012C218((void *)((Unkstruct_800B5CB8 *)param_1)->unkCC);
    ((Unkstruct_800B5CB8 *)param_1)->unkCC = 0;
    func_8001C924(((Unkstruct_800B5CB8 *)param_1)->unk20, &D_801BBC78);
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x1D;
    ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0xF;
    func_8012A828(param_1, D_801CC358);
    CAST_SIGN(u32, param_1, 0xE0) &= 0xFFFFFFFB;
}


extern void func_8012A828(s32 a0, void * a1);
extern u8 D_801CC6E8[];

void func_80185944(s32 p) {
    ((Unkstruct_800B5CB8 *)p)->unk2 = 0x20;
    func_8012A828(p, D_801CC6E8);
    ((Unkstruct_800B5CB8 *)p)->unk1C = 0;
    ((Unkstruct_800B5CB8 *)p)->unkE4 = 0;
    ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
}


// @class: regalloc-order
// @unstuck(P36): none — MATCH (168/168). $s4/$s5 pins for base+&local28; s32 sVar1 for single lh;
//          inverted if for bnez; sp20[3] array so 3 stores survive DSE; fresh-pseudo c=coord in
//          the else so gcc keeps s2v as the commutative addu's first operand (§10 A1 via pseudo order).

#include "common.h"


extern s32 D_80126B58;
/* holds a pointer value */
extern u16       D_800B99DA;
extern u8        D_801B5184;

extern int  rand(void);
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80189380(s32, void*, void*, s32);
extern void func_8018931C(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);

void func_8018598C(s32 param_1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    u8  auStack_38[8];
    s16 sp20[3];
    u8  auStack_28[8];
    StructB58 *b58 = &(*(StructB58 *)&D_80126B58);   /* $s4 */
    short *psVar7 = (short *)(param_1 + 0xec);
    s32 sVar1;
    s32 r_b608;

    if (func_8012BEE8(param_1) != 0) {
        unsigned int *p28 = (unsigned int *)auStack_28; /* $s5 */
        s32 r0 = rand();
        s32 coord;
        s32 s2v;
        s32 r3;
        s32 tmp;

        coord = r0 % 0x400;
        sVar1 = CAST_NONSTRUCT(s16, (*(s32 *)&(*(s32 *)&D_80126B78)), 0x12);
        s2v   = sVar1 + 0x800;
        if ((rand() & 1) == 0) {
            coord = s2v - coord;
        } else {
            s32 c = coord;   /* fresh pseudo so gcc keeps s2v first in the addu (§10 A1) */
            coord = s2v + c;
        }

        func_8012B0B4(p28, coord, rand() % 0x200 + 0x200);

        tmp = *(s32 *)auStack_28;
        psVar7[0] = b58->f6 + tmp;
        psVar7[1] = b58->fa;
        psVar7[2] = b58->fe + (tmp >> 16);

        r3 = rand();
        ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0x80;
        ((Unkstruct_800B5CB8 *)param_1)->unk100 = r3 % 9 + 8;
    }

    if ((CAST_SIGN(u32, param_1, 0xe0) & 0x40) == 0) {
        ((Unkstruct_800B5CB8 *)param_1)->unkE8 = func_8012B744((void *)(param_1 + 4), psVar7);
    }

    r_b608 = func_8012B608((s32)*(s16 *)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x12),
                           ((Unkstruct_800B5CB8 *)param_1)->unkE8,
                           (s32)((Unkstruct_800B5CB8 *)param_1)->unk100);
    ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12 =
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12 + r_b608;
    func_8012B178(param_1, 0xfffa0000);

    CAST_SIGN(u32, param_1, 0xe0) &= 0xffffffbf;
    if (func_8018765C(param_1) == 0) {
        func_801877E4(param_1);
        sp20[1] = 0;
        sp20[0] = 0;
        sp20[2] = -0x100;
        ((void (*)(s32, s32, s32))func_8012F14C)(((Unkstruct_800B5CB8 *)param_1)->unk20 + 0x34,
                                                 (s32)sp20, (s32)psVar7);
    }

    if (((u32)D_800B99DA % 0x28 == 0) && ((CAST_SIGN(u32, param_1, 0xe0) & 0x80) == 0)) {
        ((void (*)(s32, s32, s32, s32))func_80189380)(param_1, (s32)&D_801B5184, (s32)auStack_38, 0xb);
        ((void (*)(s32, s32, s32, s32, s32, s32))func_8018931C)(param_1, (s32)auStack_38, 0x282, 1, 0, 0);
        CAST_SIGN(u32, param_1, 0xe0) |= 0x80;
    }

    if (func_80013478(param_1 + 4, (s32)psVar7) < 0x400) {
        ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0;
    }
}


#include "common.h"

/* Sibling-search hit (cookbook §160g): src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c:6654
 * func_8018457C (already banked) is the SAME structural family — its case 0 (the
 * s0==0||mismatch||func_8012BEE8() guard + call_b6d4/LAB_80184738 tail) and case 3
 * (func_8012C218/func_8001C924/func_8012A828 teardown chain) are literally this
 * function's two branches with different field offsets/globals. Types/signatures below
 * mirror that TU's existing extern decls exactly (host TU already declares all of
 * these at file scope before this insertion point, e.g. lines 6639-6652, 7203-7213).
 */

extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern s32 func_80013350(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012C218(void *a0);
extern void func_8001C924(s32 a0, void *a1);

extern u8 D_801CD0E8[];
extern u8 D_801BC494;
extern u8 D_801CC6E8[];

void func_80185C2C(s32 p)
{
    s32 s0;
    s32 r;

    if (((Unkstruct_800B5CB8 *)p)->unk34 == 0) {
        s0 = ((Unkstruct_800B5CB8 *)p)->unkCC;
        if (s0 == 0 || CAST_SIGN(s16, s0, 0x36) != ((Unkstruct_800B5CB8 *)p)->unkEC ||
            func_8012BEE8(p) != 0) {
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x23;
            CAST_SIGN(u32, p, 0xE0) |= 0x800;
        } else {
            r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s0 + 4));
            ((Unkstruct_800B5CB8 *)p)->unkE8 = r;

            r = func_8012B608(*(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)p)->unkE8, 8);
            ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 =
                ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 + r;

            func_8012B178(p, 0xFFF8D000);

            func_8018765C(p);

            r = ((s32 (*)(s32, s32))func_80013350)(p + 4, s0 + 4);
            if (r < 0x900) {
                ((Unkstruct_800B5CB8 *)p)->unk34 = ((Unkstruct_800B5CB8 *)p)->unk34 + 1;
                func_8012A828(p, D_801CD0E8);
            }
        }
    } else {
        if (((Unkstruct_800B5CB8 *)p)->unk98 == 0) {
            func_8012C218((void *)((Unkstruct_800B5CB8 *)p)->unkCC);
            ((Unkstruct_800B5CB8 *)p)->unkCC = 0;
            func_8001C924(((Unkstruct_800B5CB8 *)p)->unk20, &D_801BC494);
            ((Unkstruct_800B5CB8 *)p)->unk2 = 0x20;
            func_8012A828(p, D_801CC6E8);
            ((Unkstruct_800B5CB8 *)p)->unk48 = 0x4650;
            ((Unkstruct_800B5CB8 *)p)->unk1C = 0;
            ((Unkstruct_800B5CB8 *)p)->unkE4 = 0;
            CAST_SIGN(u32, p, 0xE0) &= 0xFFFFFFFB;
        }
    }
}


extern void func_80187038(s32 e);
    void func_80185DA8(s32 arg0) {
        if (*(s16 *)((s32)arg0 + 0x98) == 0) {
            func_80187038(arg0);
        }
    }


#include "common.h"

/* Sibling-search (§160g) findings, kept for the integration note:
 * - func_8018598C (same TU, ov_SC06_018_jr_8017C24C.c:7215, MATCHED/banked already) shares
 *   func_8012BEE8/func_8012B608/func_8012B178/func_8018765C/func_801877E4 with identical
 *   argument shapes -- confirms every extern signature below except func_8012B8A4/func_8012EFB8.
 * - func_8018457C (same TU, :6654) uses the SAME func_8012B608(*(s16*)(*(s32*)(p+0x20)+0x12),
 *   *(s32*)(p+0xE8), 8) / field += pattern and the SAME func_8012B178(p, 0xFFF8D000) magic
 *   literal -- confirms the b608/b178 idiom byte-for-byte.
 * - func_8012B8A4 canonical decl (many matched TUs): extern s32 func_8012B8A4(s16 *a0);
 * - func_8012EFB8's byte-true body (src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c:1106) is
 *   `s32 func_8012EFB8(void *param_1, void *param_2)` -- TWO pointers, s32 return -- but the
 *   fleet-canon extern in THIS TU (line 335: `extern void func_8012EFB8(s32 a0);`, file scope,
 *   already in effect before this function) conflicts on both arity and return axis. Per §161c,
 *   do NOT add a second extern; cast the existing symbol at the call site instead.
 * - Ghidra seed at .run/ghidra_c/func_80185DD8.c confirms the callee set and control flow
 *   (verified address-matched: FUN_80185dd8, calls FUN_8012be54/bee8/b8a4/b608/b178/8765c/877e4/
 *   efb8/c098) -- used only to cross-check, not copied verbatim (Ghidra's decompile is
 *   -O0-shaped and not reg-alloc-accurate).
 *
 * INTEGRATION SURFACE (for the banking step): every extern below is checked against this TU's
 * (ov_SC06_018_jr_8017C24C.c) own file-scope decls already in effect before line 7301:
 *   func_8012BE54 -> void(s32) EXACT match (host decl at :4212/:5193; cast to (s32(*)(s32)) at
 *     the one call site, mirroring the host's own existing call-site casts at :4363/:5291).
 *   func_8012BEE8 -> s32(s32) EXACT match (:7203).
 *   func_8012B608 -> s32(s32,s32,s32) EXACT match (:6644).
 *   func_8012B178 -> void(s32,s32) EXACT match (:6645/:7044/:7207).
 *   func_8018765C -> s32(s32) EXACT match (:6646/:7045/:7208).
 *   func_801877E4 -> void(s32) EXACT match (:7046/:7209).
 *   func_8012EFB8 -> declared void(s32) to match the host's loose file-scope decl (:335); the
 *     real (void*,void*)->s32 body is invoked through a cast at the call site (§161c), so no
 *     second/conflicting extern is introduced.
 *   func_8012C098 -> void(void*) EXACT match (:5603).
 *   func_8012B8A4 -> NOT declared anywhere in this TU before this point; the draft's
 *     `extern s32 func_8012B8A4(s16 *a0);` is the canonical signature used fleet-wide and
 *     introduces no conflict.
 * Net: zero declaration conflicts predicted against the host TU.
 */

extern void func_8012BE54(s32 a0); /* host TU decl is void (§161c-style loose proto); cast at call site */
extern s32 func_8012BEE8();  // K&R: 0 of 1 args (P37 rung D t4_D22)
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018765C(s32 a0);
extern void func_801877E4(s32 a0);
extern s32 func_8012EFB8(void *param_1, void *param_2); /* loose decl, real body is (void*,void*)->s32; call via cast */
extern void func_8012C098(void *param_1);

void func_80185DD8(s32 a0) {
    s32 r;
    s16 vecA[4];
    s16 vecB[4];
    s32 x;

    if ((CAST_SIGN(u32, a0, 0xE0) & 0x40) == 0) {
        s32 ret = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret <= 0x63FFF) {
            if (func_8012BEE8(a0) != 0) {
                s32 t;
                s32 rr;

                t = func_8012B8A4((s16 *)a0);
                ((Unkstruct_800B5CB8 *)a0)->unkE8 = (t + 0x800) & 0xFFF;
                rr = rand();
                ((Unkstruct_800B5CB8 *)a0)->unk1C = rr % 0x40 + 0x40;
            }
        }
    }

    r = func_8012B608((s32) * (s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12), ((Unkstruct_800B5CB8 *)a0)->unkE8, 8);
    ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 = ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 + r;

    CAST_SIGN(u32, a0, 0xE0) &= 0xFFFFFFBF;
    func_8012B178(a0, 0xFFF8D000);

    if (func_8018765C(a0) == 0) {
        func_801877E4(a0);
    }

    vecA[0] = CAST_SIGN(s16, a0, 0x6);
    vecA[1] = CAST_SIGN(s16, a0, 0xA);
    vecA[2] = CAST_SIGN(s16, a0, 0xE);
    ((s32 (*)(void *, void *))func_8012EFB8)(vecA, vecB);

    x = vecB[0];
    if (x < 0) {
        x = -x;
    }
    /* |z| tested per sign inside the jump context: each arm of the ?: is its own compare-and-branch,
     * so the two `slti 201` tails are not one value-converged abs (the x test above is). */
    if (x >= 0x105 || (vecB[1] >= 0 ? vecB[1] >= 0xC9 : -vecB[1] >= 0xC9)) {
        func_8012C098((void *)a0);
    }
}


#include "common.h"

/* func_80185F58 (ov_SC06_018_jr_8017C24C) — MATCH 198/198, relocation-masked.
 * @class: regalloc-copy + schedule
 * @unstuck(P36): none. Three load-bearing idioms:
 *  1. ONE shared scratch `t` for all three `sll 16` compares. Three separate temps let
 *     local-alloc TIE the short temp to `iVar1` (no `addu $s1,$v0,$zero` at all, 197 ins);
 *     the shared `t` conflicts with `iVar1` so the copy survives.
 *  2. `t = t << 16; if (t <= 0)` instead of `if ((s16)t <= 0)` at the FIRST site only.
 *     With the natural cast the shift lands in a fresh pseudo, so local-alloc's
 *     `optimize_reg_copy_1` (local-alloc.c:700, called at :1007 — MIPS never defines
 *     SMALL_REGISTER_CLASSES so pins cannot block it) finds `t` dying there and rewrites the
 *     use to the copy's destination -> `sll $v0,$s1,16`. Shifting IN PLACE makes the insn
 *     SET `t`, which trips the `reg_set_p (src, p)` break in the forward scan (and flow emits
 *     no REG_DEAD when a reg is set in the insn that last uses it, cookbook §45 Lever B)
 *     -> the scan aborts, the use stays on `$v0`: `sll $v0,$v0,16`. Cookbook §25 triage tell.
 *     Sites 2 and 3 (0xFE / 0x76) have no copy insn, so `(s16)t <= 0` is correct there.
 *  3. case 8 assigns `ptr` AFTER the func_8012A828 call. Assigning it first gives the
 *     `la $s1,D_801B51CC` a low enough LUID to win the `lhu 0x70` load-delay slot, which
 *     eats the target's `nop` (-1 ins). $s1 is callee-saved, so sched1 still hoists the
 *     `la` back above the call — just not into the delay slot.
 * Also: `D_801B5164 + 8` (not a separate D_801B516C symbol) is what produces the CSE'd
 * `addiu $a1,$s2,0x8` off the $s2 base; two symbols would emit a second lui/addiu pair.
 * The `| 0x40000000 | 0x20000000` must stay as TWO ors — gcc-2.7.2 fold has no associate
 * step for BIT_IOR_EXPR, and a folded `| 0x60000000` emits only one lui/or.
 */

extern u8  D_801B5164[];
extern u8  D_801B5084[];
extern u8  D_801BB67C;
extern u8  D_801B51EC[];
extern u8  D_801B51CC[];
extern u8  D_801B51DC[];
extern u8  D_801B51BC[];
extern u8  D_801CCD68[];
extern void *D_801B534C[];

extern void func_8012E9C0(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_80189284(void *a0, s32 a1, s32 a2);
extern s32  func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80189380(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);  /* TU-canonical: matches the decl at ov_SC06_018_jr_8017C24C.c:7883 */
extern void func_8002A520(s32 a0);
extern void func_8002A790(s32 a0);
extern void func_80131E00(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_80189E60(s32 arg0, u16 arg1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_801874E4(s32 a0, s32 a1);

void func_80185F58(s32 p) {
    s32 buf20[2];
    s32 iVar1;
    s32 iVar2;
    s32 t;
    void *ptr;

    func_8012E9C0(p);
    ((Unkstruct_800B5CB8 *)p)->unk1C = 0;
    ((Unkstruct_800B5CB8 *)p)->unk5C = ((Unkstruct_800B5CB8 *)p)->unk5C & 0xFFFE;
    func_8012B23C(p);

    t = (((Unkstruct_800B5CB8 *)p)->unk60 * *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk78 + 0x30)) >> 12;
    iVar1 = t;
    t = t << 16;
    if (t <= 0) {
        iVar1 = 1;
    }

    if (CAST_SIGN(u32, p, 0xE0) & 1) {
        ((void (*)(s32, void *, void *))func_8012F214)(p, D_801B5164, buf20);
        if (func_80189284(buf20, *(s16 *)(((Unkstruct_800B5CB8 *)p)->unk20 + 0x12), 0x400) != 0) {
            func_80146A6C(6, (void *)p, ((Unkstruct_800B5CB8 *)p)->unk7C, ((Unkstruct_800B5CB8 *)p)->unk7E,
                          ((Unkstruct_800B5CB8 *)p)->unk80, 0, 0);
            t = CAST_SIGN(u16, p, 0xFE) - iVar1;
            ((Unkstruct_800B5CB8 *)p)->unkFE = t;
            if ((s16)t <= 0) {
                func_80189380(p, D_801B5164 + 8, buf20, 0xC);
                func_8018931C(p, buf20, 0x27F, 0, 0, 0);
                ((Unkstruct_800B5CB8 *)p)->unk58 = (s32)D_801B5084 | 0x40000000 | 0x20000000;
                ((Unkstruct_800B5CB8 *)p)->unkE0 = CAST_SIGN(u32, p, 0xE0) & 0xFFFFFFFE;
                func_8001C924(((Unkstruct_800B5CB8 *)p)->unk20, &D_801BB67C);
            }
            func_8012B14C(p, (s32)D_801B51EC);
            ((Unkstruct_800B5CB8 *)p)->unk34 = 3;
            return;
        }
    }

    if (CAST_WIDTH(u16, p, 0x5E) != 0x1D) {
        if (((Unkstruct_800B5CB8 *)p)->unkC8 != 0) {
            func_8002A520(p);
        }
        if (((Unkstruct_800B5CB8 *)p)->unkC9 != 0) {
            func_8002A790(p);
        }
    }

    t = CAST_SIGN(u16, p, 0x76) - iVar1;
    ((Unkstruct_800B5CB8 *)p)->unk76 = t;
    if ((s16)t <= 0) {
        func_80131E00(p, 0xC);
        return;
    }

    ((Unkstruct_800B5CB8 *)p)->unk98 = 0;
    ((Unkstruct_800B5CB8 *)*(s32 *)(p + 0x20))->unk12 = (((Unkstruct_800B5CB8 *)p)->unk62 + 0x800) & 0xFFF;
    iVar2 = ((Unkstruct_800B5CB8 *)p)->unk20;
    *(s16 *)(iVar2 + 0x14) = 0;
    *(s16 *)(iVar2 + 0x10) = 0;
    func_8012B2CC(p);
    ((s32 (*)())func_80189E60)(p, 0x9B7);

    switch (CAST_WIDTH(u16, p, 0x5E)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 0xB:
    case 0xC:
    case 0x10:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x28:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x31:
    case 0x32:
        ((Unkstruct_800B5CB8 *)p)->unk34 = 4;
        func_8012A828(p, D_801B534C[CAST_SIGN(u16, p, 0x70) & 0xF]);
        return;
    case 8:
        func_8012A828(p, D_801B534C[CAST_SIGN(u16, p, 0x70) & 0xF]);
        ptr = D_801B51CC;
        break;
    case 5:
    case 0x1D:
    case 0x20:
    case 0x26:
    case 0x2A:
        ptr = D_801B51DC;
        func_8012A828(p, D_801CCD68);
        ((Unkstruct_800B5CB8 *)p)->unkE0 = CAST_SIGN(u32, p, 0xE0) | 8;
        ((Unkstruct_800B5CB8 *)p)->unkAE = CAST_SIGN(u16, p, 0xAE) | 1;
        func_801874E4(p, -0x8000);
        break;
    default:
        ptr = D_801B51BC;
        break;
    }
    func_8012B14C(p, (s32)ptr);
    ((Unkstruct_800B5CB8 *)p)->unk34 = 0;
}

