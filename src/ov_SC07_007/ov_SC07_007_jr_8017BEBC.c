#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* size 8, alignment 1 -> unaligned copy */
      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */
extern void func_80128288(void);
extern void func_80128158(void);
extern void func_801285E4(void);
extern void func_80128178(void);
extern void func_80128678(void);
extern void func_80128198(void);
extern void func_80128714(void);
extern void func_801281B8(void);
extern void func_8013E67C(void);
extern void func_801281D8(void);
extern void func_8013E558(void);
extern void func_801281F8(void);
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern void func_80011B7C(int);
extern void func_801282CC(void);
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_80129258(void);
extern void func_801378F0(void);
extern void func_80010E14(void);
extern s16 currentLocationId;
extern s32 func_80029504(void);
extern s32 func_800CF854(s32);
extern s32 func_80128998(void);
extern s32 func_801289F0(void);
extern s32 func_801288E8(s32);
extern s32 func_80128940(s32);
extern s32 func_80029178(s32);
extern s32 func_801288B0(void);
extern void func_80011C10(void);
extern void func_8012832C(void);
extern void func_80129220(void);
extern void func_80011E24(void);
extern void func_80128C14(void);
extern void func_8002AEF8(void);
extern void func_800CFBBC(void);
extern void SsUtReverbOff(void);
extern void func_8013C98C(void);
extern void func_80129C40(s32 a0);
extern void func_800D0630(void);
extern void func_80145CEC(void);
extern void func_80144B9C(void);
extern u8 D_800B9A17;
extern u8 D_800B9A10;
extern void func_80128420(void);
extern s32 func_800D0588(void);
extern void func_801284B8(void);
extern void func_80175308(void);
extern void func_8016E8F0(void);
extern void func_80175494(void);
extern u8 D_800B9A64;
extern void func_801284F0(void);
extern void func_80146074(void);
extern void func_8012853C(void);
extern void func_80178608(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80011A3C(void);
extern short currentLocationId;
extern short D_800B99F2;
extern void func_80128564(void);
extern u8 D_800B9A11;
extern void func_801285D4(void);
extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern void func_80029444(void);
extern void func_800D1754(void);
extern void func_8014ED28(s32 _arg0);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int func_801288E8(int arg0);
extern int func_80128940(int arg0);
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80128FAC(u16 *arg0);
extern s16 D_8011DB2C;
extern s16 D_8011DB30;
extern s32 D_80126AEC;
extern void func_80129010(void);
extern u8 *func_8012913C(s32 a0);
extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void func_8001D074(s32 a, s32 b);
extern u8 *func_801291C0(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 * func_8012913C(s32 arg0);
extern void func_80016714(void *a0, s32 a1);
extern u8 * func_801291C0(void);
extern void func_80129248(s16 a0);
extern void func_801292C8(u8 *a0);
extern void func_8012927C(void);
extern void func_8012931C(struct vec *a0);
extern void func_80129350(s32 a0, s32 a1);
extern void func_80129374(s32 a0, s32 a1);
extern s16 D_800B9AAC[];
extern s16 D_800B9AAE[];
extern s16 D_800B9AB0[];
extern s16 D_800B9AB2[];
extern s16 D_800B9AB4[];
extern s16 D_800B9AB6[];
extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];
extern void func_80129398(void);
extern s16 D_80114EE0;
extern void func_80129428(void);
extern void func_8012943C(void);
extern s32 D_8005128C;
extern u8 D_800B9A78;
extern void func_801298F4(void *arg0);
extern void func_801299C8(s32 a, s32 b, s32 c);
extern void func_8012944C(void);
extern unsigned short D_800B99F0;
extern struct BigCopy D_80126DB8;
extern struct BigCopy D_80114EE8;
extern s32 D_80126E60[];
extern s8 D_801150D6;
extern s8 D_801152C0;
extern u8 D_80127504;
extern void func_800144D4(void);
extern void func_80129C40(s32 _arg0);
extern void func_8012A328(void);
extern void func_80053308(s32);
extern s32 func_80012F74(s32, s32, s32, s32);  /* canonical s32 (engine_core); (s16)-cast the return for the sll/sra */
extern void GsSetRefView2L(void *);
extern s8 D_801150D6;            /* canonical (engine_core macro): s8 — access via *(u8*)& for lbu */
extern s32 D_80126F04[];
/* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_80126FA8[];
extern struct BigCopy D_80126DB8;/* canonical (engine_core macro): struct BigCopy — (s32*)& at use */
extern u8 D_800AF630[];          /* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_800AE688[];
extern s32 D_801151D4;           /* canonical (10 siblings): scalar s32 — store (s32)ptr */
extern void func_80129CF8(void);
extern void func_8012A018(s32 a, s32 b);
extern void func_80129FF4(void);
extern void func_8012A048(void *a0, s32 a1, u8 a2);
extern void func_8012A018(s32 a0, s32 a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern void *memcpy(void *, const void *, unsigned int);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);
extern void func_8012A0E0(void);
extern s32 D_80120204;
extern s32 D_80120200;
extern s32 D_8012020C;
extern s32 D_80120208;
extern s16 D_80120218;
extern s16 D_80120210;
extern s16 D_8012021A;
extern s16 D_80120212;
extern s16 D_8012021C;
extern s16 D_80120214;
extern s16 D_80120226;
extern s16 D_80120220;
extern s16 D_80120228;
extern s16 D_80120222;
extern s16 D_8012022A;
extern s16 D_80120224;
extern s32 D_80120294;
extern s16 D_80120298;
extern s16 D_8012029A;
extern void func_8012A110(void);
extern void func_8012A2F4(void);
extern s16 D_80127080;
extern s16 D_801152C2;
extern void func_8012A304(s32 a0, s32 a1);
extern void func_8012A464(void);
extern s32 D_801151D4;
extern void func_8012A4BC(void);
extern void func_8012A598(void *a0);
extern void func_8012A568(void (*a0)(void));
extern void func_8012A62C(s32);
extern void func_8012A5F8(void (*a0)(void), s32 a1);
extern void func_8012A62C(s32 a0);
extern void func_8012A7D4(void *a0, void *a1);
extern s32 func_8012A6D0(void *a0, void *a1);
extern s16 func_8012A68C(void);
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_8012A6D0(void* a0, void* a1);
extern s16 func_8012A79C(s16 *a0, s16 *a1);
extern s16 func_8012A758(void);
extern void func_8012A7D4(void *arg0, void *arg1);
extern void func_8012AAAC();
extern void func_8012A828(s32 a0, void * a1);
extern int func_8012ACE0(void *a0);
extern void func_8012A860(void *a0, int a1);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012A8E8(void);
extern u8 D_801202A0[];
extern u16 D_801270C0;
extern void func_8012A988(u8 *a0);
extern void func_8012A908(void);
extern s32 func_8012ACE0(void *a0);
extern void func_8012ACA0(void *arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012AD50(void * arg0);
extern void func_8012AD64(s32 *a0, s16 a1);
extern void func_8012AD6C(void *a0);
extern void func_8012AD80(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 D_80126B58;
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80013478(s32 a0, s32 a1);
extern s32 func_8012AE00(s32 a0);
extern s32 func_8012AF0C(s32 a0, s32 a1);
extern s32 func_80134510(s32 arg);
extern s32 func_8012B030(u8 *a0);
extern int func_80047948(int a0);
extern int func_8004787C(int a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern void func_8012B21C(void *a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B260(u8 *a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void RotMatrixYXZ(void *m, void *p);
extern void func_8012B370(int a0);
extern void func_8004978C(s16 *a0, void *a1);
extern void func_8012B414(int a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 ratan2(s32 x, s32 y);
extern s32 func_8012B744(void *a0, void *a1);
extern s16 D_80126CB8;
extern s16 D_80126CB4;
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BA10(s32 arg0, s32 arg1);
extern s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s16 D_80126CBA;
extern s32 func_8012BCCC(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern u8 D_80126B5C;
extern void func_8012BD14(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_800132BC(s32 a0, s32 a1);
extern void func_8012BE98(s32 arg0, u16 * arg1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BF10(s32 a0, s32 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern void func_8012BF54(void *a0);
extern void func_8012BF68(void *a0);
extern s16 D_80126CB0;
extern s32 func_8012BF7C(s16 *a0);
extern s16 D_80126CAC;
extern short D_80126CAE;
extern int func_8012BFA8(short *a0);
extern s32 D_801274D4;
extern s32 D_801274E0;
extern s32 func_8012C044(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012C098(void *param_1);
extern s32 func_8012C0EC(s32 a0);
extern void func_8012C194(void);
extern void func_8001CFDC(s32 a, s32 b);
extern void func_8012C1B8(void);
extern u8 D_800B3DF0[];
extern s32 func_8012C1DC(s32 a0);
extern u8 D_80126720[];
extern u16 * func_8012C284(u16 *a0);
extern u8 D_80120194[];
extern s32 func_8012C2D0(void);
extern s32 func_8012C31C(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern u8 D_80078EAE;
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern s32 func_8012C438(s32 a0, s32 a1);
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C724(s32 a0, s32 a1);
extern s32 func_8012C750(s32 a0);
extern s32 func_8012C820(u8 *a0);
extern u16 D_801274E4[];
extern s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern s32 func_8012CC88(s32 a0, s32 a1, s32 a2);
extern void func_8012CC64(s32 a0, s32 a1);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012CE2C(s32 a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012CFA8(s32 arg0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012D3B4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012D098(u16 *param_1, u32 param_2);
extern void func_8012D098();
extern void func_8012D38C(int a0);
extern void func_8012D3AC(void);
extern s32 AddPrim(s32, void *);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void SetLineF2(void *);
extern void *func_80010A08(s32);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern s32 D_800A651C;
extern u8 D_800AF648;
extern s16 D_800B9A02;
extern void func_8012D4B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012D5DC(void);
extern s16 D_80126B98;
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern int func_8012D664();
extern void func_8012D624(s32 a0);
extern s32 func_8012D714(s32 param_1, u32 param_2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern s32 func_8012DB84(void);
extern s32 func_8012DE2C(s32 a0);
extern s32 func_8012DDA4(void);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern s16 D_80126B9A;
extern u8 D_801152A8[];
extern void func_8012DFBC(void);
extern void func_8012DFCC(void);
extern void func_8012E014(s32 arg0);
extern void func_8012E138(void);
extern void func_8012DFD4(u8 *a0);
extern s32 func_8012E27C(void);
extern void func_8012E284(void);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern void func_8012E28C(s32 arg0, s32 arg1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8012E32C(void);
extern s32 func_8012E470(s32 a0);
extern void func_8012E4C8(s32 a0);
extern s32 func_8012E504(s32 a0, s32 a1);
extern s32 func_8012E544(s32 a0);
extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_8012E778(int param_1, int param_2);
extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012E8C4(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern s32 func_8002A4FC(s32 a0);
extern s32 func_8012EECC(s32 a0);
extern void func_8012EFB8(s32 a0);
extern void func_8012EF34(s32 a0, s32 a1);
extern void func_8012EF70(s32 a0, s32 a1);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s16 D_80126CB6;
extern void func_8012F374(s32 a0, s32 a1);
extern void *memcpy(void *, const void *, u32);
extern u8 D_80126C38;
extern u8 D_80126C40;
extern u16 D_80126B94;
extern u16 D_80126B96;
extern void func_8012F568(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6);
extern void func_80131B14();
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern s32 func_80131A34(s32, s32);
extern void func_80131CA8(int a0, int a1);
extern void func_8012F5F4(s32 arg0);
extern void func_80131C78(s32 a0);
extern void func_8012F68C(s32 arg0);
extern void func_8012F75C(s32 a0);
extern s32 func_8012BEE8(s32);
extern void func_8012F7B4(s32 a0);
extern void func_80131170();
extern void func_80131CA8();
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_8012F8C8(int param_1);
extern void func_8012F91C(s32 a0);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_80131CA8(s32 a0, s32 a1);
extern void func_8012F968(s32 param_1);
extern void func_801319E0(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012FB54(s32 a0);
extern void func_8012FC30(s32 a0);
extern void func_8012FCA4(int a0);
extern void func_80131B14(void);
extern void func_8012FCC4(int param_1);
extern void func_8012FDA8(int param_1);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern void func_8012FE70(s32 a0);
extern void func_8012FF00(s32 a0);
extern void func_8012FF4C(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_8012FF98(u8 *a0);
extern s32 func_80131AC8(void *a0);
extern void func_8013001C(void *a0);
extern void func_80130088(void *a0);
extern s32 func_8012BCCC(s32);
extern void func_801300F4(s32 a0);
extern void func_801301E8(u8 *a0);
extern void func_80130278(s32 arg0);
extern void func_80130314(s32 a0);
extern void func_80130360(s32 a0);
extern void func_8012E364(void);
extern void func_801303A0(s32 a0);
extern void func_801303EC(void *a0);
extern void func_80143CD4(s32 a0);
extern void func_800CB0E8(s32 a0);
extern void func_80130438(s32 a0);
extern void func_801319E0(int);
extern int func_80131D68(int, int);
extern int func_8012BEE8(int);
extern void func_80131CA8(int, int);
extern void func_80130514(int param_1);
extern void func_801305CC(u8 *a0);
extern void func_8012CBF4(s32);
extern s32 func_80131D68(s32 a0, s32 a1);
extern void func_80130650(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80130740(void *a0, u16 *a1);
extern s32 func_801312D0(s32 a0, void *a1);
extern void func_801307B0(s32 a0);
extern void func_80130858(s32 a0);
extern void func_80130898(u8 *a0);
extern void func_801308DC(s32 a0);
extern void func_80166244();
extern void func_80130974(int param_1);
extern void func_80130A18(u8 *a0);
extern void func_80130AC4(s32 a0);
extern int  func_80131A34(int a0, int a1);
extern void func_80130AF0(int param_1);
extern void func_80130D0C(s32 a0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern int func_80131D68(int a0, int a1);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void func_80131EEC(void *a0);
extern void func_80131F28(void *a0);
extern void func_80131F64(void *a0);
extern void func_80131FA0(void *a0);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern void func_801320D8(int param_1);
extern void func_80132144(int param_1);
extern void func_801321B0(int param_1);
extern void func_8013221C(int param_1);
extern void func_8005C324(int dst, int src, int n) __asm__("memcpy"); /* Phase-24: 0x8005C324 is named memcpy for overlays (whale needs it); keep the non-builtin C name here (else built-in codegen), emit via asm-label */
extern void func_801325B8(int a0, int a1, int a2, int a3, int a4);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8013240C(s32 a0);
extern void func_8013277C(void);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_80054514(s32 a0, s32 a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_80132DC4(s32 a0, s32 a1, s32 a2);
extern s32 func_80132E6C(s16 *a0);
extern void func_80132EC4(void *a0, s16 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_801330E0(void * param_1, s16 * param_2, s32 param_3);
extern void func_80133060(u8 *a0, s32 *a1, s32 a2);
extern void func_8013339C(short *param_1, short *param_2);
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern void func_80136BC4(s32);
extern void func_8013373C(s16 arg0);
extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);
extern s32 func_80133CD4();
extern s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2);
extern s32 func_8013435C(s16 *a0, s16 *a1, s32 a2, s16 *a3);
extern s32 func_801343C4(s32 angle, s32 p1, s32 p2);
extern s32 func_801345F8(s32 arg);
extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
extern int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4);
extern s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_801365B8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void func_80136C54(void);
extern void func_80136D00(void);
extern void SetLineG2(void *);
extern void func_80136D08(s32 arg0, s32 arg1);
extern u16 D_80126CC4;
extern M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32);
extern void func_80136DFC(void);
extern void func_80136EC4(void);
extern short D_800B9A02;
extern u8 D_800A6518[];
extern void GsSortLine(void *a0, void *a1, s32 a2);
extern void func_80136ECC(s16 a0, s16 a1, s16 a2, s16 a3, u8 r, u8 g, u8 b);
extern void func_80137030(s16 a0, s16 a1);
extern void ApplyMatrixSV(void *m, Svec_801372B0 *in, Svec_801372B0 *out);
extern void aGsSortLine(Gline_801372B0 *p, void *ot, s32 z) __asm__("GsSortLine");
extern void aF80137030(s32 x, s32 y) __asm__("func_80137030");
extern void func_80137178(s32 x, s32 y);
extern u8  D_800AF630[];
extern u16 aD800B9A02 __asm__("D_800B9A02");
extern void func_801372B0(void);
extern void func_80137614(s32 a0, s32 a1, s32 a2);
extern void func_801375EC(s32 a0, s16 a1);
extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);
extern s32 func_8013767C(s32 a0);
extern void func_801376E8(int a0, int a1);
extern void func_801376C8(int a0);
extern s32 D_80127524;
extern s32 D_80127528;
extern void func_80137840(s32 a0);
extern void func_80139634(void *);
extern void func_80139DC8(void);
extern s16 D_8012752E;
extern void func_801379D8(void);
extern void func_801379EC(void);
extern void func_80138BE0(s32 a0);
extern void func_80137BD8(s32 a0);
extern void func_8013A380(void);
extern void func_801379FC(void);
extern void func_80138BE0(int p);
extern void func_80137B80(void);
extern void func_801392FC();
extern void func_801397B0(s32 a0);
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);
extern u16 D_800B99D8;
extern int func_80137D08(int arg0, int arg1, short arg2);
extern void func_80137FD8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80137DD4(s32 ent, u8 *arg, u8 *work);
extern void func_801387B8(s32 arg0);
extern void func_80138948(void *a0);
extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2);
extern void func_80138B88(s32 a0);
extern void func_8013895C(s32 a0);
extern s16 D_80127540[4];
extern s32 func_80139D04(s32 a0, s32 a1);
extern s32 func_80138DE0(s32 a0, s32 a1, s32 a2);
extern void func_80139B18(s32 a0);
extern void func_80138AB4(s32 a0);
extern void func_80138C30(void *a0);
extern void func_8013A9F8(s32 a0, s32 a1);
extern void func_80138D58(s32 a0, u16 a1);
extern s32 func_80014E80(s32 a0, s32 a1);
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
extern s32 D_80127548[];
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);
extern s32 func_80139220(s32 a0);
extern void func_801391F0(void *a0);
extern void func_801392C8(void *a0);
extern void func_801395D4(void *);
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);
extern void func_801392FC(s32 arg0, s32 arg1, u8 *arg2);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_80139634(void *a0);
extern void func_80139680(s32 arg0, u8 * arg1);
extern void func_8001931C(void);
extern s16 D_8012752C;
extern void func_80139788(void);
extern void GsSortSprite(void *a0, u8 *a1, s32 a2);
extern void func_801397B0(s32 arg0);
extern void func_8013A8B0(s32 *a0);
extern void func_80139914(s32 arg0);
extern u16 D_80126A08;
extern s16 D_801269F4;
extern s32 D_801269F0;
extern s32 *D_80126A30;
extern void func_80139954(void);
extern s32 D_80126A3C;
extern s32 func_801399F0(s32 a0);
extern s32 D_80127520;
extern void func_80139A34(s32 a0);
extern s32 D_80127530[4];
extern void func_80139A44(s32 a0, u16 a1);
extern void func_80139A68(s32 a0, u16 a1);
extern void func_80139A8C(s32 a0);
extern void func_80139C7C(u8 *a0);
extern s16 D_8012811A;
extern void func_80139DEC(void);
extern void func_80139DF4(s32 a0);
extern void func_80139E84(s32 a0);
extern void func_80139F0C(s32 a0);
extern void func_80139FBC(struct obj *a0);
extern s32 func_8001B22C(void *a0);
extern void func_80139FE8(void *a0);
extern void func_8013A0A4(struct S8013A0A4 *a0);
extern void func_8013A164(struct S8013A164 *a0);
extern void func_8013A1E8(s32 a0);
extern void func_8013A250(struct S8013A250 *a0);
extern void func_8013A2BC(s32 a0);
extern void func_8013A378(void);
extern u8 D_8011DA80[];
extern void func_8013A530();
extern void func_8013A448(void *a0);
extern void func_8013A4C4(struct S8013A4C4 *a0);
extern void func_80015D4C();
extern void func_80015F04();
extern void func_8013AA24(s32 a0, s32 a1);
extern void func_8013A530(int param_1);
extern void func_8013A860(void);
extern s32 func_8013A8BC(void);
extern void func_8013A9B4(s32 a0, s32 a1);
extern s32 func_8013A8FC(s32 arg0);
extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B204(s32 a0, s32 a1);
extern void func_8013AF20();
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern void func_8013CA14(void);
extern void func_8013CABC(void);
extern void func_8013CAE8(void);
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern void func_8013CF68();
extern void func_8013D9B0();
extern void func_8013D064(void);
extern s32 func_8013D13C(void);
extern void func_8013D164(void);
extern void func_8013D178(void);
extern void func_8013D330(void);
extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);
extern void func_8013D3D4(int param_1, int param_2);
extern void func_8013DBE4(int param_1);
extern s32 func_8013E054(void);
extern int SquareRoot12(int a0);
extern int func_8013E064(s16 *a0, s16 *a1);
extern int func_8013E0FC(s16 *a0, s16 *a1);
extern int func_8013E194(s16 *a0, s16 *a1);
extern void Square12(s32 *a0, s32 *a1);
extern s32 func_8013E22C(struct VecA *a0, struct VecB *a1);
extern s32 func_8013E298(s16 *a0);
extern int func_8013E2C4(short *a0);
extern void *D_801274CC;
extern s32 func_8013E410(void);
extern s32 func_8013E448(s32 a0);
extern void func_8013E370(void);
extern s32 (*D_801274D0)(s32);
extern s32 D_801274D8;
extern s32 D_801274DC;
extern s32 func_8013E448(s32 param_1);
extern void func_800D24A0(s32 a0);
extern void func_80141788(void);
extern void *D_8011DB24;
extern s32 func_800D0EC4(void);
extern void func_80141874(void);
extern u8 D_800B9A15;
extern unsigned char D_800B9A13;
extern u16 D_80115110;
extern unsigned short D_80115112;
extern void func_8013E588(void * _arg0);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);
extern void func_8013E5E8(void);
extern void func_8013E83C(void);
extern void func_8013E6AC(void);
extern void func_800D24A0(s32 arg);
extern void func_8013E814(void);
extern void func_8013E83C();
extern void func_8013E958();
extern s32 func_80141C50(void);
extern void func_8013F244(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern void func_8013E958(void);
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_8011511A;
extern u16 D_8011511E;
extern s32 D_80115130;
extern s16 D_8011514C;
extern void func_8013EA54(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern unsigned char *func_80141CA4(void);
extern void func_8013EB7C(void);
extern u16 D_80115112;
extern void func_8013ED6C(void);
extern s32 func_8013EE10();
extern void func_8013F138(void);
extern void func_800D2624(void);
extern unsigned short D_80115114;
extern unsigned short D_80115118;
extern void func_8013F1BC(void);
extern void func_80141C0C(s32);
extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958(s32 *, s32, s32);
extern int   func_80141100(int);
extern s16   func_8014168C(s16);
extern s32   func_8013FFD8(s16, s32, s32 *);
extern void func_80024054(void *a0, void *a1);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern void func_8013FAF8(s16 arg0, s16 arg1);
extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern void func_801407F4(void);
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern int func_80029FE4(void);
extern char *func_8002AAB4(void);
extern char *strcpy(char *, const char *);
extern int func_8002A26C(void);
extern int func_8002A2B0(void);
extern int func_8002A4B8(void);
extern int func_8002A998(void);
extern int func_8002A9DC(void);
extern int func_8002A728(void);
extern int func_8002A76C(void);
extern int func_80029FD4(void);
extern s32 func_8002A1B4(void);
extern short func_8002A28C(void);
extern short func_8002A27C(void);
extern s32 func_8002A400(void);
extern short func_8002A4D8(void);
extern short func_8002A4C8(void);
extern s32 func_8002A8E0(void);
extern short func_8002A9B8(void);
extern short func_8002A9A8(void);
extern s32 func_8002A670(void);
extern short func_8002A748(void);
extern short func_8002A738(void);
extern int func_801412A8(int, int, int, int, int, int);
extern int func_80141100(int param_1);
extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_801415C0(s32 param_1, s32 param_2);
extern u8 D_80115148[];
extern u8 D_80115149[];
extern u8 D_80115158[];
extern u8 D_8011514D;
extern u8 D_8011515C;
extern s32 func_800D11F0(s32 a0);
extern s32 func_800D1658(s32 a0);
extern s32 func_801416D4(s16 param_1);
extern void func_8001903C(void);
extern void func_801417C4(void);
extern u8 D_800B9A16;
extern u16 D_80115114;
extern void func_801417F8(void);
extern void func_80141C0C(s32 param_1);
extern s32 func_80015144(void);
extern u16 D_8011511C;
extern s32 func_80029178(s32 arg);
extern unsigned char D_80112C04[];
extern unsigned char D_80112C50[];
extern unsigned char D_80112C9C[];
extern unsigned char D_80112CE8[];
extern unsigned char D_80112D38[];
extern unsigned char D_80112D78[];
extern unsigned char D_80112DBC[];
extern unsigned char D_80112DF4[];
extern unsigned char D_80112E14[];
extern unsigned char D_80112E40[];
extern unsigned char D_80112E6C[];
extern unsigned char D_80112EBC[];
extern unsigned char D_80112F0C[];
extern unsigned char D_80112F48[];
extern unsigned char D_80112F9C[];
extern unsigned char D_80112FDC[];
extern unsigned char D_8011302C[];
extern unsigned char D_80113074[];
extern unsigned char D_801130B8[];
extern unsigned char D_801130E8[];
extern unsigned char D_80113138[];
extern unsigned char D_8011317C[];
extern unsigned char D_801131A8[];
extern unsigned char D_801131E8[];
extern unsigned char D_80113214[];
extern unsigned char D_80113254[];
extern unsigned char D_80113278[];
extern unsigned char D_801132B8[];
extern unsigned char D_801132E4[];
extern unsigned char D_80113324[];
extern unsigned char D_80113360[];
extern unsigned char D_801133A4[];
extern unsigned char D_801133F4[];
extern unsigned char D_80113440[];
extern unsigned char D_80113474[];
extern unsigned char D_801134B0[];
extern unsigned char D_801134FC[];
extern unsigned char D_80113530[];
extern unsigned char D_80113554[];
extern unsigned char D_801135A8[];
extern unsigned char D_80113600[];
extern unsigned char D_80113650[];
extern unsigned char D_80113694[];
extern unsigned char D_801136DC[];
extern unsigned char D_80113724[];
extern unsigned char D_80113744[];
extern unsigned char D_80113770[];
extern unsigned char D_80113794[];
extern unsigned char D_801137D8[];
extern unsigned char D_8011381C[];
extern unsigned char D_8011383C[];
extern unsigned char D_8011386C[];
extern unsigned char D_801138A4[];
extern unsigned char D_801138D0[];
extern unsigned char D_80113900[];
extern unsigned char D_80113944[];
extern unsigned char D_80113964[];
extern unsigned char D_8011399C[];
extern unsigned char D_801139E8[];
extern unsigned char D_80113A28[];
extern unsigned char D_80113A50[];
extern unsigned char D_80113A84[];
extern unsigned char D_80113AB0[];
extern unsigned char D_80113AE0[];
extern unsigned char D_80113B34[];
extern unsigned char D_80113B68[];
extern unsigned char D_80113BA4[];
extern unsigned char D_80113BC0[];
extern unsigned char D_80113BF0[];
extern unsigned char D_80113C20[];
extern unsigned char D_80113C3C[];
extern unsigned char D_80113C7C[];
extern unsigned char * func_80141CA4(void);
extern void func_80142414(s32 a0, s16 a1);
extern void func_80142454(s32 a0);
extern void func_801424E4(short *param_1);
extern void func_801425CC(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern void func_80142608(s32 param_1);
extern void func_801426D4(s32 a0);
extern void func_80142740(int param_1);
extern void func_80142778(u8 *a1);
extern void func_801427DC(void);
extern void func_801427E4(void);
extern void func_801427EC(int param_1);
extern s32 func_80142DB8(s32 *a0);
extern s32 func_80142D38(s32 *a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_801428CC(s32 *a0);
extern void func_8014292C(int param_1);
extern void func_80142978(int param_1);
extern void func_801429C4(int param_1);
extern void func_80142A80(void);
extern void func_80142C7C(void);
extern void func_80142C84(s32 a0);
extern void func_80142C9C(s32 * arg0);
extern void func_80142B2C(void *arg0);
extern void func_80142DC4(int param_1);
extern void func_80142E38(int param_1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142EC0(s32 param_1);
extern void func_80142FFC(s32 *a0);
extern void func_8014305C(int param_1);
extern void func_80143188(s32 *a0);
extern int func_8001CA88(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_801431E8(s32 param_1);
extern void func_80142C9C(s32 *a0);
extern void func_801432FC(s32 *a0);
extern void func_80143390(s32 *a0);
extern void func_80143458(s32 param_1);
extern void func_8014358C(s32 param_1);
extern s32 rand(void);
extern void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143970(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80143994(s32 a0, s32 a1);
extern void func_801439C0(u8 *a0);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern void func_801439FC(s32 a0);
extern void func_80143B30(void *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_80143BDC(u16 *a0);
extern void func_80143C38(void *a0);
extern void func_80143C74(s32 a0, s32 a1);
extern void func_80143C98(void *a0);
extern void func_80143E68(void *a0);
extern void func_80143EA4(void);
extern void func_80143EAC(void);
extern void func_80143EB4(void);
extern s32 func_8004787C(s32 a0);
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
extern void func_801442F8(int param_1);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80144364(int param_1);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80144558(u8 *param_1);
extern void func_801446A4(int param_1);
extern void func_8014477C(void *param_1);
extern void func_80144880(s32 param_1);
extern void func_80144988(s32 a0);
extern void func_801449C8(void *a0);
extern void func_80144A04(s32 *a0);
extern void func_80144A2C(void *a0);
extern void func_80144A68(s32 *a0);
extern void func_80144A90(void);
extern void func_80144A98(u8 *a0);
extern void func_80144B14(void);
extern void func_80144AEC(s32 *a0);
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern void func_80145B24(void);
extern void func_80145934(void);
extern void func_80145A2C(void);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
extern u8 D_80078EC0;
extern void func_80145BF8(void);
extern void func_80145C54(void);
extern void func_80146014(s32 a0);
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
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
extern s32 func_80146994(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern s32 func_80146B9C(void *a0);
extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
extern u16 D_8011DA28;
extern s32 func_80146B9C(void * arg0);
extern void func_80146C3C(u8 *a0);
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
extern void func_80147E44(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80147F50(s32 arg0);
extern volatile s32 D_80127090;
extern volatile s32 D_80127094;
extern volatile s32 D_80127098;
extern void func_80147F78(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80148038(s32 a0, s32 a1);
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
extern s32 func_80148D44(void);
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
extern s32 func_8016F1AC(void);
extern s32 func_80149884(void);
extern void func_80160B00();
extern void func_801498C0(void);
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
extern void func_80146750(void *a0);
extern s32 func_801498E0(s32 *a0);
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
extern s32 func_80149FB0(s32 a0);
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern void func_8014A1B0(s32 a0, s32 a1);
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
extern void func_8014AC10(s32 arg0);
extern void func_8014ACC0(s32 a0, s32 a1);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_80146AFC(void *a0);
extern void func_8014ADA8(s32 a0, s32 a1);
extern void func_8014AD7C(s32 a0);
extern s32 D_80078E8C;
extern u8 D_80078E78[];
extern s32 func_8016F1C4(void);
extern s32 func_8014B154(s32 *a0);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);
extern void func_8014BC80(s32 a0, s32 a1);
extern void func_8014BD60(s32 a0, s32 a1);
extern void func_8014B084(void);
extern void func_8014B034(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern s16 D_80078E90;
extern void func_8014B034(s32 a0);
extern u16 D_80078EAC;
extern u8 D_80078EBA;
extern void func_800D10EC(void);
extern void func_8002AC98(void);
extern void func_8014B12C(void);
extern void func_8014B2F8(void);
extern void func_8014B4C4(void);
extern void func_8014B160(s32 a0);
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
extern void func_80019064(void *a0);
extern s32 D_80078E98;
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
extern void func_8014BC0C(s32 a0, s32 a1);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_8014BCC0(s32 a0, s32 a1);
extern u16 D_80078EB6;
extern s32 func_8014BCEC(s32 a0, s32 a1);
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
extern void func_8014C1C8(s32 a0, s32 a1, void* a2);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
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
extern struct Packed8 D_80126C98;
extern short D_80126C9E;
extern void func_8014CB9C(struct Packed8 *a0);
extern s32 D_80126CDC;
extern void func_8014CBD8(void);
extern void func_8014CBF8(void *a0);
extern void func_8014D3E0(s32 a0);
extern void func_8014D04C(void);
extern void func_8014CCB4(void);
extern void func_8014CC28(s32 a0);
extern void func_8014CD0C(u8 *a0);
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern void func_8014CD80(s32 a0, void *a1, void *a2);
extern s32 func_8014D2A0(s32 a0, void *a1, void *a2);
extern s32 func_8014D12C(s32 a0, void *a1, void *a2);
extern void func_8014D0A4(s32 a0);
extern void func_8014D610(s32 a0, void *a1, void *a2);
extern s32 func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2);
extern void func_8014D790(s32 a0);
extern s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2);
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */
extern void func_8014DF94(s32 arg0);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */
extern s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);  /* canonical (engine_core.h:11555) */
extern s32 func_8014E284(s32 a0, s16 *arg1, s16 *arg2);
extern void func_8014E5B4(s32 a0, void *a1, void *a2);
extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2);
extern void func_8014E48C(s32 a0);
extern s32 func_8014E83C(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E790(s32 a0, s16 *a1, s16 *a2);
extern void func_8014E6F8(struct SubE6F8 *a0);
extern s32 func_8014E790(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014E83C(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_8014E98C(void *a0);
extern u16 D_800B99DA;
extern s32 D_801150D8;
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014ED80(struct SubED80 *a0);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern void func_8014F4C0(u8 *a0);
extern s32 func_8014F468(void);
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern void func_80150170(void *a0);
extern s32 func_8014FE60(void *a0);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_80150150(s32 a, s32 b);
extern s32 func_80150460(s32 a, s32 b);
extern s32 func_80150528(void *a0, void *a1, void *a2);
extern void func_801504D8(u16 *a0);
extern s32 func_80150528(void *arg0, void *arg1, void *arg2);
extern s32 func_801506A4(s32 a0, s32 a1);
extern s32 func_801505FC(s32 a0);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8015086C(int param_1);
extern s32 func_801508B4(s32 a0);
extern s32 func_8015094C(s32 a0);
extern short func_801508F8(s32 a0);
extern s32 func_80021174(s32 a0, s32 a1);
extern s32 func_8015094C(s32 param_1);
extern void func_80150B28(int param_1);
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
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void func_80152C80(s32* a0);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern u8 D_80062C04[];
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
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
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
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
extern void func_801550FC(s32 arg0);
extern void func_8001D150(s32, s32);
extern void func_8001D130(int, int);
extern void func_80155150(int param_1);
extern s32 D_800DE2A4[];
extern void func_801552F4(s32 a0);
extern void func_80155344(s32 a0);
extern s32 func_80155394(s32 *a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
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
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern S801563EC * func_801563EC(u16 idx);
extern s32 func_801564B0(s32 a0);
extern s32 D_801151E0[];
extern s32 func_801565C0(void);
extern void func_80156A14(s32 *a0);
extern void func_80156648(s32 *a0);
extern u8 D_8011DAD8[];
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
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
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_80157808(s32 a0);
extern void func_801577C8(int param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
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
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
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
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void func_80158AE4(void *a0);
extern void func_80158AB4(void *a0);
extern void func_8016F264(void);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80165A78(s32);
extern void func_80158AE4(void * a0);
extern void func_80158BB0(void *arg0);
extern s32 func_80159404(s32 a0, s32 a1);
extern void func_80158C40(s32 *a0);
extern void func_80158CD8(s32 *a0);
extern s32 func_80159434(s32 a0, s32 a1);
extern void func_80158D60(s32 a0);
extern M2C_UNK D_800D5904;
extern void func_80158E24(s32 *a0);
extern int rand(void);
extern void func_80158F00(int param_1);
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80158FA4(s32 param_1);
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
extern u8 D_80110C3C[];
extern void func_80159120(s32 a0);
extern void func_801592CC(s32 *a0);
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void func_80159698(void *a0);
extern s32 func_801596D4(void *a0);
extern void func_80174B6C(void);
extern void func_8013C938(void);
extern void func_8002850C(s32, s32, s32);
extern void func_80028620(s32, void *);
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void func_8015A2A0(s32 a0);
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
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
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern void func_8014D738(void);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void func_8015C788(s32);
extern void func_8015C750(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80161240(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8015C7E4(u16 *param_1);
extern void func_8015C944(int param_1);
extern void func_8015CA28(u16 *param_1);
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
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void func_8014E6A0(void);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern void func_8015D414(int param_1);
extern void func_8015D57C(s32);
extern void func_8015D480(s32 *a0);
extern s32 func_8015D4E8(s16 *a0);
extern void func_8015D4B4(s16 *a0);
extern void func_8015D524(s32 arg0);
extern void func_8015D544(s32 a0);
extern void func_801746DC(void);
extern void func_8015D57C(s32 arg0);
extern void func_80154150(int, int);
extern void func_80149374(int, int);
extern void func_8015D5E8(int param_1);
extern int func_8015E0D4(int);
extern void func_8015DA5C(s32 a0);
extern void func_8015DB6C(s32 a0);
extern void func_8015DA90(s32 *a0);
extern void func_8015DAF8(s32 *a0);
extern void func_8015DB6C(s32);
extern void func_8015DB34(s32 a0);
extern void func_8015DCB8(s32 a0);
extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);
extern int func_8015DD74(int);
extern void func_8015DBD4(void *arg0);
extern int func_8015DC84(int a0);
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
extern void func_8015E5B0(u8*);
extern void func_8015E344(u16 *param_1);
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern s32 func_8013C9C4(s32 *a0);
extern void func_8015E5B0(u8 *self);
extern void func_8015E698(u16 *param_1);
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
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C(s32 *a0);
extern void func_8015EFD8(s32 *a0);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
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
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern void func_8015F948(s32 *param_1);
extern void func_8015FA24(s32 arg0);
extern void func_8015FBE0(s32 *a0);
extern void func_8015FA44(s32 *a0);
extern void func_8015FAAC(s32 *a0);
extern void func_8015FA78(s32 *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_8015FAE8(void *arg0);
extern void func_8015FCC8(void *param_1);
extern void func_8015FD74(int param_1);
extern u8 func_80165700(s32 a0, s32 a1);
extern void func_8015FDCC(s32 a0);
extern void func_8015FE70(u16 *param_1);
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
extern void func_801602A4(s32 *a0);
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
extern void func_80160A74(s32 *a0);
extern void func_80160920(unsigned short *param_1);
extern void func_801609B8(u16 *param_1);
extern void func_80160A28(s32 a0);
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
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern void func_800D1734(void *);
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
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
extern void func_80162760(void);
extern void func_801627C0(void);
extern void func_80162834(void *a0);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
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
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
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
extern void func_80164744(s32 param_1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
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
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 func_801656D0(s32 a0, s32 a1);
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
extern u8 D_80078EC2;
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0();
extern void func_80165E90(void);
extern void func_80166018(void *a0);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void func_801663FC(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern void func_80166618(void *a0);
extern void func_80166654(void *a0);
extern void func_801678B4(void *a0);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80017758(void *a0, void *a1);
extern int func_80029178(int);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801681FC(s32 param_1);
extern void func_80168430(s32 param_1);
extern void func_80168640(s32 a0);
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80168664(void *arg0);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_80168D58(void *a0);
extern void func_80168F40(void *arg0);
extern void func_8016901C(void *a0);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void func_80169830(void *a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_80169B80(void *a0);
extern void func_80169F00(void *a0);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A700(void *a0);
extern s32 func_80016A5C();
extern s32 func_8016A8FC(s32 a0);
extern void func_8016AB30(void *a0);
extern void func_8016B234(void);
extern void func_800D22E4(s32 a0);
extern void func_8016AFB0(s32 a0);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void func_8016BBA4(void *a0);
extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8016BD78(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04();
extern void func_8016C83C(s32 a0);
extern void func_8016CB84(void *a0);
extern void func_8016D19C(void *a0);
extern void func_8016D428(void *a0);
extern void func_8016D464(u8 *a0);
extern void func_8016D4DC(s32 a0);
extern void func_8016DBD8(u8 *a0);
extern void func_8016DA30(int param_1);
extern void func_8016DEA4(void *a0);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_8016E460(void *arg0, void *arg1);
extern void func_8016E5B8(void *a0);
extern void func_8016E778();
extern void func_8016E688(void *a0);
extern void func_8016E6E4(s32 a0);
extern void func_8016E7C8(int param_1, short *p1, unsigned int *p2);
extern void func_8016E778(int param_1);
extern s32 D_80115218;
extern void func_8016E918(short param_1, short param_2);
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern void func_8016EB3C(s32 p);
extern void func_8016EBA8(u8 *param_1);
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
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
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
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_8017118C(u8 * a0);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void func_801714E4(void *a0);
extern struct B16 D_800A5E88;
extern struct B16 D_800A5E98;
extern struct B16 D_800A5EA8;
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
extern s32 func_8017248C(s32, s32);
extern s32 ratan2(s32, s32);
extern void func_80172170(s32, s32);
extern void func_80146D90(s32);
extern void func_80172170(s32 a0, s32 a1);
extern s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_801722CC(s32 *a0);
extern void func_80172304(s32 *a0);
extern void func_80172310(u8 *a0);
extern void func_801723C4(s32 param_1, s32 param_2);
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
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
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
extern void func_80173B4C(void *a0);
extern void func_80173BC0(u8 *a0);
extern void func_80173B88(u8 *a0);
extern s16 D_80126B3A;
extern s16 D_8011F9C8;
extern void func_8013E588(void*);
extern void func_80173BC0(u8* a0);
extern void func_80173C64(u8 *a0);
extern u8 D_800D5DB8;
extern void func_80173CB4(s32 a0);
extern void func_80173E1C(s32 a0);
extern s16 D_80126938;
extern void func_800D128C(s32, s32);
extern void func_80174158(s32 a0);
extern void func_8002A088(s32);
extern void func_8002A2D4(s32);
extern void func_8002A544(s32);
extern void func_8002A7B4(s32);
extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);
extern void func_800D0F0C(s32, s32);
extern void func_80145EE8(s32);
extern void func_80173EF8(void *param_1);
extern s32 func_8014BCEC(s32, s32);
extern void func_801741A8(s32 _arg0);
extern s16 D_80126B3C;
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
extern void func_80174684(void* a0);
extern void func_801746A4(void);
extern s32 func_800CF8CC(void);
extern s32 func_8016F0AC();
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
extern s32 func_8017496C(void *a0);
extern s32 D_80126950;
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_80174BF4(void *a0);
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
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern s32 func_80175218(void * param_1);
extern s32 func_80175268(s32 param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);
extern void func_8017553C(s32 *param);
extern void func_801757A0(s32 a0);
extern void func_80175590(void *arg0);
extern void func_801757A0(s32);
extern void func_80175624(void *a0);
extern void func_801757E0(int);
extern void func_80175668(void);
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
extern void func_801775E0(s32 param_1, s32 param_2);
extern void * func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern uint * func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4);
extern void func_80177F84(s32 param_1, s32 param_2);
extern u32 * func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
extern void func_80178438(u16 *arg0);
extern void func_801787D4(void);
extern void func_8017869C(s32 a0);
extern s32 D_8011DB08;
extern void func_8017849C(void);
extern void func_8013E4B4(void);
extern s16 D_801270C4;
extern s16 D_801270C2;
extern u8 D_801270C6;
extern u8 D_801270C7;
extern void func_80178744(s32 a0, s32 a1);
extern void func_80178840();
extern void func_80178840(int param_1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_801789AC(s32 arg0);
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern void func_80178BF8(s32 _unused0, s32 _unused1);
extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
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
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
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
extern s32 func_8017A3B0(void);
extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
extern s32 func_8017AD0C(s32 arg0);
extern s32 func_8017AD0C(s32);
extern s32 func_8017ADE8(s32 a0);
extern s32 func_8017AE08(void);
extern void func_8017B0E4(int param_1, int param_2);
extern void func_8012A418(void);
extern void func_8017B1D8(void);
extern void func_8017B614(void *, s32);
extern s32 func_8017B238(s32 param_1, s32 param_2);
extern s32 func_8017B368(s32 param);
extern s32 func_8017B490(s32 param);
extern void func_8017B7A8(void);
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern void func_8017B940(void);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8017BCF4(int param_1);
extern void func_8017BD50(int param_1);
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

void func_8017BEBC(s32 arg0)
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




void func_8017CD9C(void *a0) {

    extern void (*D_80186990[])(void);
    D_80186990[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017CDD8);

DEFINE_func_8017CE24()  /* dedup: shared engine-core @0x8017ce24 (src/shared) */




void func_8017CE48(void *a0) {

    extern void (*D_80186998[])(void);
    D_80186998[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017CE84(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0xa;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}


s32 func_8017CEA0(s32 *a0) {
    if (--a0[0xA] == -1) {
        func_800167B8(4);
        *((u8 *)a0 + 0x15) += 1;
    }
    return 0;
}


extern int func_800167F0(int arg);
int func_8017CEF4(void) {
    return (func_800167F0(4) & 0xFFFF) != 0;
}




void func_8017CF18(void *a0) {

    extern void (*D_801869A4[])(void);
    D_801869A4[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017CF54(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0xa;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800167B8(s32 a0);

s32 func_8017CF70(void *a0) {
    s32 v0;
    s32 v1 = -1;
    v0 = *(s32 *)(a0 + 0x28);
    v0 += -1;
    *(s32 *)(a0 + 0x28) = v0;
    if (v0 == v1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1;
    }
    return 0;
}


#include "common.h"

extern s32 func_800167F0(s32 a0);
extern void func_800146B0(s32 a0);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8002AEE4(void);

extern s32 D_800B9A18;
extern s8 D_80078EC6;

s32 func_8017CFEC(void) {
    s32 v0;

    v0 = func_800167F0(4);
    if ((v0 & 0xFFFF) != 0) {
        func_800146B0(1);
        D_800B9A18 = 2;
        func_80029514(0x6A4);
        func_80029124(0x11D, 1);
        func_80029124(0x123, 1);
        D_80078EC6 = 1;
        func_8002AEE4();
        return 1;
    }

    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D064(void) {

    extern s32 D_801869B0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801869B0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D08C(void) {

    extern s32 D_801869BC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801869BC, 0x1000000);
}


#include "common.h"

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

void func_8017D0B4(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s32 D_801C7804;
    extern s32 D_801C7800;

    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_8012696A = 0x1C7;
    D_80126968 = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x40;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D648, 0);
    D_801C7804 = 0;
    D_801C7800 = 0;
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}


#include "common.h"

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

void func_8017D158(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x190;
    D_8012695C = 0x15E;
    D_8012696A = 0x155;
    D_80126968 = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x60;
    D_8012697A = 0;

    func_8012A018((s32)func_8017D648, 1);
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}


#include "common.h"

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

void func_8017D1F0(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x190;
    D_8012695C = 0x15E;
    D_8012696A = 0x800;
    D_80126968 = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x60;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D648, 2);
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017D288);

#include "common.h"

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

void func_8017D350(void) {
    typedef struct { s16 x0, x1, x2, x3; } BlkT;
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_801274E8[];
    extern u8 D_801869C8;

    D_80126954 = 0x190;
    D_8012695C = 0x15E;
    D_80126968 = -0x38;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x60;
    D_8012697A = 0;

    func_8012A018((s32)func_8017D648, 4);
    *(BlkT *)&D_801274E8 = *(BlkT *)&D_801869C8;
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017D41C);

#include "common.h"

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

typedef struct { s16 x0, x1, x2, x3; } UnalignedShortBlock;

void func_8017D4E4(void) {
    extern u8 D_80126948[];
    extern u8 D_801869D8;
    extern u8 D_801274E8[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x190;
    D_8012695C = 0x15E;
    D_80126968 = -0x38;
    D_80126976 = -0x140;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126978 = -0x60;
    D_8012697A = 0;

    func_8012A018((s32)func_8017D648, 6);
    *(UnalignedShortBlock *)&D_801274E8 = *(UnalignedShortBlock *)&D_801869D8;
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017D648(void *a0);

void func_8017D5B0(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x190;
    D_8012695C = 0x414;
    D_80126968 = -0x38;
    D_8012696A = 0x155;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D648, 7);
    func_8012A094((s32)D_80126948);
    func_8017D648(D_80126948);
}




void func_8017D648(void *a0) {

    extern void (*D_801869E0[])(void);
    D_801869E0[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

extern void func_8017DAE8(void *a0, void *a1);
extern void func_8017DF04();
extern void func_8017DC20(void *a0, void *a1, void *a2);
extern u8 D_801274E8[];
extern void (*D_80186A00[])(void);

void func_8017D684(s32 a0) {
    typedef struct { s8 c[8]; } Blk8;
    u8 *base = D_801274E8;
    Blk8 buffer;

    *(Blk8 *)base = *(Blk8 *)D_80186A00;
    buffer = *(Blk8 *)(base + 8);
    ((void (*)(void *, void *))func_8017DAE8)((void *)a0, &buffer);
    *(Blk8 *)(base + 8) = buffer;
    ((void (*)(void *))func_8017DF04)((void *)a0);
    func_8017DC20((void *)a0, base, base + 8);
}


#include "common.h"



extern void func_8017DAE8(void*, void*);
extern void func_8017DD6C(s32, s16 *);
extern void func_8017DF04();
extern Blk8 D_801274F0;

void func_8017D744(s32 s0) {
    /* dead local: reproduces target's 0x30 frame (buffer lands at sp+0x18,
       not sp+0x10) — see §160a/§48-C2 (unaligned struct-assign) + the
       vars_size=16 frame math; never read/written, byte-verified required */
    Blk8 unused;
    Blk8 buffer;

    buffer = D_801274F0;
    ((void (*)(s32, Blk8 *))func_8017DAE8)(s0, &buffer);
    D_801274F0 = buffer;
    ((void (*)(s32))func_8017DF04)(s0);
    func_8017DD6C(s0, (s16 *)&D_801274F0);
}


#include "common.h"

/* SVECTOR is declared in src/shared/engine_types.h (pulled into the real TU via
 * engine_core.h); match_one's standalone compile only sees common.h, so mirror the
 * exact same layout/alignment here (align-2 short quad) purely for the isolated check. */


extern void func_8017DAE8(void*, void*);
extern void func_8017DF04();
extern void func_8017DD6C(s32 a0, s16 *a1);
extern Blk8 D_801274F0;

void func_8017D7D8(s32 a0) {
    s32 pad[2];
    SVECTOR temp;

    temp = (*(SVECTOR *)&D_801274F0);

    ((void (*)(s32, SVECTOR *))func_8017DAE8)(a0, &temp);

    (*(SVECTOR *)&D_801274F0) = temp;

    ((void (*)(s32))func_8017DF04)(a0);
    func_8017DD6C(a0, (s16 *)&(*(SVECTOR *)&D_801274F0));
}


#include "common.h"

extern void func_8017DF04();
extern void func_8017DC20(void *a0, void *a1, void *a2);
extern u8 D_801274E8[];
extern void (*D_80186A08[])(void);



void func_8017D86C(void *a0) {
    u8 *s1 = D_801274E8;

    *(Blk8 *)s1 = *(Blk8 *)D_80186A08;

    func_8017DF04(a0);
    func_8017DC20(a0, s1, s1 + 8);
}


extern Blk8 D_801274F0;
extern void func_8017DAE8(void *a0, void *a1);
extern void func_8017DC20(void *a0, void *a1, void *a2);
extern void func_8017DF04();

void func_8017D8E0(a0)
s32 a0;
{
    s32 pad[2]; 
    Blk8 local_18;

    local_18 = D_801274F0;

    ((void (*)(s32, Blk8 *))func_8017DAE8)(a0, &local_18);

    D_801274F0 = local_18;

    ((void (*)(s32))func_8017DF04)(a0);
    ((void (*)(s32, void *, void *))func_8017DC20)(a0, (void *)((u8 *)&D_801274F0 - 8), (void *)&D_801274F0);
}


#include "common.h"



extern Blk8 D_801274F0;
extern void func_8017DAE8(void*, void*);
extern void func_8017DF04();
extern void func_8017DC20(void*, void*, void*);

void func_8017D978(s32 a0) {
    s32 pad[2]; /* dead local — reserves the 8-byte gap between $sp and local_18 (§162i1) */
    Blk8 local_18;

    local_18 = D_801274F0;

    ((void (*)(s32, Blk8 *))func_8017DAE8)(a0, &local_18);

    D_801274F0 = local_18;

    ((void (*)(s32))func_8017DF04)(a0);
    ((void (*)(s32, void *, void *))func_8017DC20)(a0, (void *)((u8 *)&D_801274F0 - 8), (void *)&D_801274F0);
}


#include "common.h"

/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2 / §160a):
   a struct-typed global with a sub-4-byte declared alignment always falls
   through gcc-2.7.2's output_block_move to the unaligned lwl/lwr+swl/swr
   pair, even though both source and stack destination are physically
   4-byte aligned at runtime. Declaring D_801274F0 as a scalar s32 (the
   first-pass attempt) instead folds the copy to plain lw/sw. */


extern void func_8017DAE8(void *a0, void *a1);
extern void func_8017DF04();
extern void func_8017DC20(void *a0, void *a1, void *a2);
extern Blk8 D_801274F0;

void func_8017DA10(void *a0) {
    s32 pad[2]; /* dead-local frame pad, +8 bytes vars (cookbook §162i1) */
    Blk8 save;

    save = D_801274F0;
    func_8017DAE8(a0, &save);
    D_801274F0 = save;
    func_8017DF04(a0);
    func_8017DC20(a0, (void *)((u8 *)&D_801274F0 - 8), &D_801274F0);
}


#include "common.h"

extern void func_8017DF04();
extern void func_8017DC20(void *a0, void *a1, void *a2);
extern void (*D_80186A10[])(void);
extern void (*D_80186A18[])(void);

void func_8017DAA8(void *a0) {
    func_8017DF04(a0);
    func_8017DC20(a0, D_80186A10, D_80186A18);
}


void func_8017DAE8(void *a0, void *a1)
{
    typedef struct { s16 a, b, c, d; } SV4;
    extern s32 func_8012E544(s32);
    extern void func_80015978(s32, s32 *);
    extern s16 func_800130D0(s16, s16, s16);
    extern s32 D_801C7800;
    extern s32 D_801C7804;
    extern s16 D_80126940;
    extern s16 D_801274F8;

    SV4 loc0;
    s16 s;

    if (D_801C7800 != -1) {
        if (D_801C7800 == 0) {
            loc0 = *(SV4 *)&D_80126940;
        } else {
            s32 v = func_8012E544(D_801C7800);
            if (v != 0) {
                func_80015978(v + 4, (s32 *)&loc0);
            }
        }
    } else {
        loc0 = *(SV4 *)&D_801274F8;
    }
    s = (s16)D_801C7804;
    if (D_801C7804 == -1) {
        *(SV4 *)a1 = loc0;
    } else {
        *(s16 *)a1 = func_800130D0(*(s16 *)a1, loc0.a, s);
        *(s16 *)((u8 *)a1 + 2) = func_800130D0(*(s16 *)((u8 *)a1 + 2), loc0.b, s);
        *(s16 *)((u8 *)a1 + 4) = func_800130D0(*(s16 *)((u8 *)a1 + 4), loc0.c, s);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017DC20);



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

void func_8017DD6C(s32 param_1, s16 *param_2) {
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


extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];

void func_8017DF04(void)
{
    short sVar1;
    int iVar2;

    sVar1 = func_8012A758();
    iVar2 = sVar1 * 0x140;
    if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1ff;
    }
    D_800B9AB8[0] = (short)(iVar2 >> 9);
    D_800B9ABA[0] = 0xf0;
}


void func_8017DF5C(s32 a0, s32 a1) {
    extern s32 D_801C7800;
    extern s32 D_801C7804;

    D_801C7800 = a0;
    D_801C7804 = a1;
}


typedef struct {
    s16 d0, d1, d2, d3;
} Blk8U;

s32 func_8017DF74(s32 a0, s32 a1)
{
    extern s32 D_801C7800;
    extern s32 D_801C7804;
    extern s32 D_801274F8;

    D_801C7800 = -1;
    D_801C7804 = a1;
    *(Blk8U *)&D_801274F8 = *(Blk8U *)a0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017DFB8);

#include "common.h"

extern void func_80175494(void);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern s32 D_801C7AC4;
extern s32 D_801C79CC;
extern s32 D_801C7808;

void func_8017E170(s32 *a0) {
    u16 v0;

    v0 = *(u16 *)((s32)a0 + 0x72);
    D_801C7AC4 = 0;
    D_801C79CC = 0;
    v0 |= 0x1000;
    *(u16 *)((s32)a0 + 0x72) = v0;

    func_80175494();
    func_80016714(&D_801C7808, 0x18);
    func_8012AD44(a0, 0x2);
}


void func_8017E1D0(void) {
}

#include "common.h"

extern s32 D_801C7808;

void func_8017E1D8(void) {
    s32 i;
    s32 *p;

    i = 0;
    p = &D_801C7808;
    do {
        if (*p != 0) {
            ((void (*)(s32 *))(*p))((s32 *)p);
        }
        i++;
        p += 6;
    } while (i < 4);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E234);

s32 func_8017E254(void * arg0)
{
    M2C_FIELD(arg0, s16 *, 0x6) = 0;
    M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E268);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E2B8);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E2F0);

s32 func_8017E33C(void * arg0)
{
    M2C_FIELD(arg0, s16 *, 0x6) = 0;
    M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
}


#include "common.h"

void func_8017E350(s32 a0) {
    extern void func_80016714(void *a0, s32 a1);
    extern u8 D_801274E8[];
    extern Blk8 D_801274F0;
    extern u8 D_801274EC[];
    u16 prev;
    s16 t;

    if ((*(u16 *)(a0 + 8) & 3) == 0) {
        (*(u16 *)(D_801274E8 + 2)) += 1;
    }

    prev = *(u16 *)(a0 + 8);
    *(u16 *)(a0 + 8) = prev + 1;
    if ((prev & 1) != 0) {
        (*(u16 *)D_801274EC) -= 1;
    }

    t = *(s16 *)D_801274E8 - 1;
    *(s16 *)D_801274E8 = t;
    if (t < *(s16 *)((u8 *)&D_801274F0)) {
        func_80016714((void *)a0, 0x18);
    }
}


extern void (*D_80187E48[19])(void);

void func_8017E400(s32 arg0) {
    u16 var_v1;

    var_v1 = *(u16 *) (arg0 + 4);
    *(s32 *) (arg0 + 0x10) = (s32) D_80187E48;
    *(u16 *) (arg0 + 8) = 0;
    *(u16 *) (arg0 + 6) = 0;
    *(u16 *) (arg0 + 4) = var_v1 + 1;
}


void func_8017E424(s32 s0) {
    extern void func_80016714();
    extern void func_80181120();
    s32 s1;

    if (*(s16 *)(s0 + 8) == 0) {
        s1 = *(s32 *)(s0 + 0x10);
        if (*(s32 *)s1 != 0) {
            func_80181120(0, *(s32 *)s1);
            *(s16 *)(s0 + 8) = *(s32 *)(s1 + 4);
            *(s32 *)(s0 + 0x10) = *(s32 *)(s0 + 0x10) + 8;
        } else {
            func_80016714((void *)s0, 0x18);
        }
    } else {
        *(s16 *)(s0 + 8) = *(s16 *)(s0 + 8) - 1;
    }
}


s32 func_8017E4B0(void * arg0)
{
    M2C_FIELD(arg0, s16 *, 0x6) = 0;
    M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E4C4);

extern s32 D_801151D4;

void func_8017E51C(s32 arg0)
{
    s32 ptr = D_801151D4;
    *(u16 *)(ptr + 0x1A) = 0xE00;
    *(u16 *)(ptr + 0x22) = 0xE00;
    *(u16 *)(arg0 + 6) = 0;
    *(u16 *)(arg0 + 4) = *(u16 *)(arg0 + 4) + 1;
}


extern s32 D_801151D4;

void func_8017E544(void) {
    s32 p = D_801151D4;
    *(u16 *)(p + 0x1A) -= 2;
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x1A);
}


extern s32 D_801151D4;

void func_8017E568(void *arg0) {
    s32 p;

    p = D_801151D4;
    *(s32 *)(p + 0x10) = 0x190;
    *(s32 *)(p + 0x14) = 0x190;
    *(s16 *)(p + 0x1A) = 0x200;
    *(s16 *)(p + 0x22) = 0x200;
    M2C_FIELD(arg0, u16 *, 4) = (u16)(M2C_FIELD(arg0, u16 *, 4) + 1);
    M2C_FIELD(arg0, s16 *, 0x6) = 0;
}


extern s32 D_801151D4;

void func_8017E59C(void) {
    s32 p = D_801151D4;
    *(u16 *)(p + 0x1A) += 2;
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x1A);
}


s32 func_8017E5C0(void * arg0)
{
    M2C_FIELD(arg0, u16 *, 0x8) = 0;
    M2C_FIELD(arg0, s16 *, 0x6) = 0;
    M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + 1);
}


void func_8017E5D8(s32 arg0) {
    s16 temp;

    temp = *(u16 *)(arg0 + 8) + 1;
    *(s16 *)(arg0 + 8) = temp;
    if (temp > 0x12) {
        *(s16 *)(arg0 + 8) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017E608);

extern s32 func_80181334(s32 a0, s32 a1);
extern void func_80181120();
extern s32 D_801884EC[];

void func_8017E634(void *arg0) {
    s32 base;
    s32 entry;

    if (func_80181334(0, 7) != 0) {
        *(u16 *)(arg0 + 8) = 0;
        *(u16 *)(arg0 + 10) = 0;
        *(u16 *)(arg0 + 12) = 0;
        *(s32 *)(arg0 + 16) += 1;
    }

    switch (*(s16 *)(arg0 + 10)) {
    case 0:
        base = D_801884EC[*(s32 *)(arg0 + 16)];
        entry = base + (*(s16 *)(arg0 + 8) << 3);
        *(s16 *)(arg0 + 14) = *(s32 *)(entry + 4);
        if (*(s16 *)(arg0 + 14) == 0) {
            *(s16 *)(arg0 + 10) = -1;
        } else {
            func_80181120(0, *(s32 *)entry);
            *(u16 *)(arg0 + 10) += 1;
        }
        break;

    case 1:
        *(s16 *)(arg0 + 14) -= 1;
        if (*(s16 *)(arg0 + 14) == 0) {
            *(u16 *)(arg0 + 10) = 0;
            *(u16 *)(arg0 + 8) += 1;
        }
        break;
    }
}


extern s32 func_80180F84(void);
extern void func_8012C098(void*);
extern void (*D_80188554[])(int);

void func_8017E730(int param_1)
{
    int v0;
    v0 = ((int (*)(void))func_80180F84)();

    if (v0 == 0x1a) {
        ((void (*)(int))func_8012C098)(param_1);
    } else {
        D_80188554[*(unsigned short *)(param_1 + 2)](param_1);
    }
}


#include "common.h"

extern void func_801812BC(void);
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern void func_80143994(s32 a0, s32 a1);
extern void func_801813EC(s32 a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void * arg0);

extern u8 D_801A9B78;
extern s32 D_80187C98[];

void func_8017E798(s32 a0) {
    s32 s1;

    func_801812BC();
    s1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = s1;

    if (s1) {
        func_8001C214(s1, (s32)&D_801A9B78);
        *(s32 *)(s1 + 0x28) = 0x7FFF7FFF;
        *(s16 *)(a0 + 0x52) = 0x4;
        ((void (*)(s32, s32))func_80181048)(a0, (s32)&D_80187C98);
        func_80143994(a0, 0x4000);
        func_801813EC(a0);
        func_8012BF4C((s32 *)a0, 0xA);
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80181048(void*, void*);
extern void func_80181120(void);
extern void func_8012BF4C(s32*, s32);
extern void func_801813CC(s32 a0);
extern s32 func_8012AD50(void*);

extern void (*D_80186B50[])();
extern u8 D_80187E28[];

void func_8017E838(s32 a0) {
    s32 v0;

    v0 = func_8012BEE8(a0);

    if (v0 != 0) {
        ((void (*)(s32, s32))func_80181048)(a0, (s32)&(*(s32 *)D_80186B50));
        ((void (*)(s32, s32))func_80181120)(a0, (s32)&(*(s32 *)D_80187E28));
        ((void (*)(s32, s32))func_8012BF4C)(a0, 0x1E);
        func_801813CC(a0);
        ((s32 (*)(s32))func_8012AD50)(a0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80181048(void*, void*);
extern void func_80181120(void);
extern void func_80181524(s32*, s32);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void *a0);

extern s32 D_80186AA8;
extern s32 D_80187D88;
extern s32 D_8018854C;
extern s32 D_801C7808;
extern void func_80182768(void*);

void func_8017E8A4(s32 a0) {
    s32 result;
    s32 i;
    s32 *ptr;
    s32 func_addr;

    result = func_8012BEE8(a0);
    if (result == 0) {
        return;
    }

    ((void (*)(s32, s32))func_80181048)(a0, (s32)&D_80186AA8);
    ((void (*)(s32, s32))func_80181120)(a0, (s32)&D_80187D88);
    ((void (*)(s32, s32))func_80181524)(a0, (s32)&D_8018854C);
    func_80180F94(2);

    func_addr = (s32)func_80182768;
    i = 0;
    ptr = (s32 *)((s32 *)&D_801C7808);
    for (; i < 4; i++) {
        if (*ptr == 0) {
            *ptr = func_addr;
            break;
        }
        ptr = (s32 *)((s32)ptr + 0x18);
    }

    func_8012AD50((void *)a0);
}


#include "common.h"

extern s32 func_8018152C();
extern void func_8017E234(void *a0);
extern void func_80181048(void *a0, void *a1);
extern void func_8012BF4C(s32*, s32);
extern s32 func_8012AD50(void *arg0);

extern void func_80182768(void *);
extern s32 D_801C7808;
extern s32 D_80187C98[];

void func_8017E94C(void *a0) {
    s32 i;
    s32 *current;
    s32 value;
    s32 comparator;

    if (func_8018152C() == 0) {
        return;
    }

    comparator = (s32)func_80182768;
    current = (s32 *)((s32 *)&D_801C7808);

    for (i = 0; i < 4; i++) {
        value = *current;

        if (value == comparator) {
            func_8017E234(current);
        }

        current = (s32 *)((char *)current + 0x18);
    }

    func_80181048(a0, D_80187C98);
    ((void (*)(void *, s32))func_8012BF4C)(a0, 0x1E);
    func_8012AD50(a0);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8017D158(void);
extern void func_80180F94(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern s32 func_8012AD50(void *arg0);

extern s16 D_801888BC;

void func_8017E9F0(s32 a0) {
    s32 s0;

    s0 = a0;
    if (func_8012BEE8(a0) != 0) {
        func_8017D158();
        func_80180F94(3);
        func_8018122C(s0, &D_801888BC);
        func_8012AD50((void *)s0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017EA48);

#include "common.h"

extern s32 func_80180F84(void);
extern void func_8017D158(void);
extern void func_801813EC(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_80181048(void *a0, void *a1);
extern void func_80181120(void);
extern s32 func_8012AD50(void *arg0);

extern s32 D_801151D4;
extern void (*D_80188AA8[])(void);
extern void (*D_80186BC8[])(void);
extern s16 D_80187DA8[];

void func_8017EB34(s32 a0) {
    register s32 s0 __asm__("$16") = a0;
    register s32 s1 __asm__("$17") = D_801151D4;
    s32 v0;

    if (func_80180F84() != 6) {
        return;
    }

    func_8017D158();

    v0 = 0x11C;
    *(u16 *)((u8 *)s1 + 0x1A) = v0;
    *(u16 *)((u8 *)s1 + 0x22) = v0;

    func_801813EC((s32)s0);
    func_8018122C((s32)s0, &D_80188AA8);
    ((void (*)(s32, void *))func_80181048)((void *)s0, (void *)&D_80186BC8);
    ((void (*)(s32, void *))func_80181120)((s32)s0, (void *)&D_80187DA8);
    func_8012AD50((void *)s0);
}


#include "common.h"

extern s32 func_80180FA4(s32, s32);
extern void func_801810CC(s32, s32, s32);
extern s32 func_80181280(s32 a0);
extern void func_80181048(void*, void*);
extern void func_80181120(void);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void*);

extern u8 D_80186E88;
extern u8 D_80187E08;
extern u8 D_80186C38;
extern s32 D_80187C98[];
extern s32 D_80187D88;

void func_8017EBCC(s32 a0) {
    s32 s0 = a0;

    ((s32 (*)(s32, void *, s32))func_80180FA4)(s0, (void *)&D_80186E88, 0x4);
    ((s32 (*)(s32, void *, s32))func_801810CC)(s0, (void *)&D_80187E08, 0x2);
    ((s32 (*)(s32, void *, s32))func_80180FA4)(s0, (void *)&D_80186C38, 0x2);

    if (func_80181280(s0) != 0) {
        ((s32 (*)(s32, void *))func_80181048)(s0, (void *)&D_80187C98);
        ((void (*)(s32, void *))func_80181120)(s0, (void *)&D_80187D88);
        func_80180F94(0x7);
        ((void (*)(s32))func_8012AD50)(s0);
    }
}


void func_8017EC68(s32 *a0) {
    extern s32 func_80180F84(void);
    extern void func_8018122C(s32 a0, void *a1);
    extern void func_8017D41C(void);
    extern void func_801813EC(s32 a0);
    extern s32 func_8012AD50(void *arg0);
    extern void func_8018263C(void *a0);

    extern s32 D_801151D4;
    extern void (*D_80188BA8[])(void);
    extern s32 D_801C7808;

    register s32 s1 __asm__("$17") = D_801151D4;
    s32 *s0 = a0;
    s32 status;
    register s32 *v1 __asm__("$3");
    s32 v0;
    s32 a4;
    void *fnptr;

    status = func_80180F84();

    if (status != 0xA) {
        return;
    }

    func_8018122C((s32)s0, &D_80188BA8);
    func_8017D41C();
    func_801813EC((s32)s0);

    *(s32 *)((u8 *)s1 + 0x14) = 0x190;
    *(s32 *)((u8 *)s1 + 0x10) = 0x190;

    fnptr = (void *)func_8018263C;
    a4 = 0;
    v1 = (s32 *)&D_801C7808;
    do {
        v0 = *v1;
        a4++;
        if (v0 == 0) {
            *v1 = (s32)fnptr;
            goto loop_done;
        }
        v1 = (s32 *)((u8 *)v1 + 0x18);
    } while (a4 < 4);
loop_done:
    func_8012AD50(s0);
}


#include "common.h"

extern s32 func_80180FA4(s32, s32);
extern void func_80181494();
extern s32 func_8012AD50(void *a0);

extern u8 D_80186EA0;
extern s16 D_80187C80[];

void func_8017ED18(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80186EA0, 0) != 0) {
        ((void (*)(void *, void *, s32))func_80181494)(0, (void *)&D_80187C80, 1);
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern void func_801810CC(s32, s32, s32);
extern s32 func_80180FA4(s32, s32);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void*);
extern u8 D_80187E28[];
extern void (*D_80186B50[])();

void func_8017ED6C(s32 a0) {
    func_801810CC(a0, (s32)D_80187E28, 0);
    ((s32 (*)(s32, s32, s32))func_80180FA4)(a0, (s32)D_80186B50, 0);
    if (func_80181280(a0) != 0) {
        func_80180F94(0xB);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


#include "common.h"

extern s32 func_80180F84(void);
extern void func_8017D158(void);
extern void func_801813EC(s32 a0);
extern void func_80181048(void*, void*);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *arg0);
extern void func_80182678(void *a0);

extern s32 D_801151D4;
extern s32 D_80187C98[];
extern s32 D_801C7808;

void func_8017EDD4(s32 *a0) {
    register s32 s1 __asm__("$17") = D_801151D4;
    s32 *s0 = a0;
    s32 status;
    register s32 *v1 __asm__("$3");
    s32 v0;
    s32 a4;
    void *fnptr;

    status = func_80180F84();

    if (status != 0xE) {
        return;
    }

    func_8017D158();
    func_801813EC((s32)s0);

    *(s32 *)((u8 *)s1 + 0x14) = 0x190;
    *(s32 *)((u8 *)s1 + 0x10) = 0x190;
    ((void (*)(s32, u8 *))func_80181048)((s32)s0, &D_80187C98);

    func_8012BF4C(s0, 0x3C);

    fnptr = (void *)func_80182678;
    a4 = 0;
    v1 = (s32 *)&D_801C7808;
    do {
        v0 = *v1;
        a4++;
        if (v0 == 0) {
            *v1 = (s32)fnptr;
            goto loop_done;
        }
        v1 = (s32 *)((u8 *)v1 + 0x18);
    } while (a4 < 4);
loop_done:
    func_8012AD50(s0);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80180F94(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_80181048(void *a0, void *a1);
extern s32 func_8012AD50(void *arg0);

extern s16 D_80188C4C;
extern void (*D_80186DB0[])();

void func_8017EE90(s32 a0) {
    s32 s0;

    s0 = a0;
    if (func_8012BEE8(a0) != 0) {
        func_80180F94(0xF);
        func_8018122C(s0, &D_80188C4C);
        func_80181048((void *)s0, &D_80186DB0);
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern s32 func_80180FA4(s32, s32);
extern s32 func_8012AD50(void*);
extern s32 D_80186F98;

void func_8017EEF0(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80186F98, 0) != 0) {
        ((void (*)(void *))func_8012AD50)((void *)a0);
    }
}


#include "common.h"

extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_8017EF34(s32 a0) {
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_80180F94(0x10);
        func_8012AD50((void *)a0);
    }
}


extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void*);

void func_8017EF78(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0x11);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


void func_8017EFB8(void* arg0) {
    if (func_80180F84() == 0x12) {
        func_8018141C(arg0, 1);
        func_8012BF4C(arg0, 10);
        func_8012AD50(arg0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_80181120(void);
extern void func_80181048(void*, void*);
extern s32 func_8012AD50(void *a0);

extern void *D_80188D50;
extern u8 D_80187E28[];
extern void *D_80186E28;

void func_8017F008(s32 a0) {
    if (func_8012BEE8(a0) != 0) {
        func_8018122C(a0, &D_80188D50);
        ((void (*)(s32, void *))func_80181120)(a0, &(*(void * *)D_80187E28));
        ((void (*)(s32, void *))func_80181048)(a0, &D_80186E28);
        func_8012AD50((void *)a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern void *D_80187020;
extern void func_80181048(void*, void*);

void func_8017F070(s32 a0) {
    register s32 s0 __asm__("$16");
    s0 = a0;
    if (*(s16 *)((u8 *)s0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_80181048)(s0, &D_80187020);
        ((s32 (*)(s32))func_8012AD50)(s0);
    }
}


#include "common.h"

extern void func_80181048(void*, void*);
extern s32 func_80181280(s32 a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_80187D18;

void func_8017F0BC(s32 a0) {
    s32 v0;

    v0 = *(s16 *)(a0 + 0x98);
    if (v0 == 0) {
        ((void (*)(s32, void *))func_80181048)(a0, (void *)&D_80187D18);
    }

    if (func_80181280(a0) != 0) {
        func_8012BF4C((s32 *)a0, 0x1E);
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80180F94(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_80181470();
extern void func_801826B4(void *a0);
extern s32 func_8012AD50(void *a0);

extern u8 D_80188D68[];
extern u8 D_80187C90[];
extern s32 D_801C7808;

void func_8017F120(s32 a0)
{
    s32 *p;
    s32 i;
    s32 callback;

    if (func_8012BEE8(a0) != 0) {
        func_80180F94(0x13);
        func_8018122C(a0, D_80188D68);
        func_80181470(a0, D_80187C90, 1);

        callback = (s32)func_801826B4;
        i = 0;
        p = ((s32 *)&D_801C7808);
        for (; i < 4; i++) {
            if (*p == 0) {
                *p = callback;
                break;
            }
            p += 6;
        }

        func_8012AD50(a0);
    }
}


#include "common.h"

extern s32 func_80181334(s32 a0, s32 a1);
extern void func_80181120(void);
extern void func_80181048(void*, void*);
extern void func_801826F0(void *a0);
extern s32 func_8012AD50(void *a0);

extern s32 D_80187D88;
extern s32 D_80187C98[];
extern s32 D_801C7808;

void func_8017F1BC(s32 a0)
{
    void *fn_ptr;
    s32 i;
    void **v1;

    if (func_80181334(a0, 0) != 0) {
        /* func_80181120 is already banked in this TU as `void func_80181120(void)`
         * (a register-passthrough tail-call wrapper, TU-committed and non-conflictable);
         * cast-call it here so this call site can pass its real (s32, void*) args
         * without producing a conflicting declaration in the TU. */
        ((void (*)(s32, void *))func_80181120)(a0, &D_80187D88);
        ((void (*)(s32, void *))func_80181048)(a0, &D_80187C98);

        fn_ptr = func_801826F0;
        i = 0;

        for (v1 = (void **)&(*(s16 *)&D_801C7808); i < 4; i++, v1 = (void **)((char *)v1 + 0x18)) {
            if (v1[0] == 0) {
                v1[0] = fn_ptr;
                break;
            }
        }

        func_8012AD50((void *)a0);
    }
}


extern s32 D_80188DCC;
extern s32 D_801C7808;
extern void func_801826F0(void *a0);
extern void func_8018272C(void *a0);
extern s32 func_801815B8(s32 a0, s32 a1);
extern s32 func_80181280(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_8017E234(void *a0);
extern s32 func_8012AD50(void *a0);

void func_8017F250(s32 a0) {
    s32 i;
    s32 j;
    s32 *ptr;
    s32 *ptr2;
    s32 cmp1;
    s32 cmp2;

    func_801815B8(a0, 0);
    if (func_80181280(a0) != 0) {
        func_8018122C(a0, &D_80188DCC);

        cmp1 = (s32)func_801826F0;
        i = 0;
        ptr = (s32 *)&D_801C7808;
        for (; i < 4; i++) {
            if (*ptr == cmp1) {
                func_8017E234(ptr);
            }
            ptr = (s32 *)((s32)ptr + 0x18);
        }

        cmp2 = (s32)func_8018272C;
        j = 0;
        ptr2 = (s32 *)&D_801C7808;
        for (; j < 4; j++) {
            if (*ptr2 == 0) {
                *ptr2 = cmp2;
                break;
            }
            ptr2 = (s32 *)((s32)ptr2 + 0x18);
        }

        func_8012AD50((void *)a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_8017F330(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0x14);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017F370);

extern s32 func_80180F84(void);
extern void (*D_801885B8[])(int);
extern void func_8012C098(void *param_1);

void func_8017F390(int param_1)
{
    int v0;
    v0 = ((int (*)(void))func_80180F84)();

    if (v0 == 0x1a) {
        ((void (*)(int))func_8012C098)(param_1);
    } else {
        D_801885B8[*(unsigned short *)(param_1 + 2)](param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern s32 func_80143970(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_801AFCBC;
extern s32 D_80187088;

void func_8017F3F8(s32 a0) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;

    if (v0 == 0) {
        return;
    }

    func_8001C214(v0, (s32)&D_801AFCBC);
    *(s32 *)(v0 + 0x28) = 0x7FFF7FFF;
    *(s16 *)(a0 + 0x52) = 4;
    ((void (*)(s32, s32))func_80181048)(a0, (s32)&D_80187088);
    func_80143970(a0);
    func_8012AD50((void *)a0);
}


#include "common.h"

extern s32 D_801151D4;
extern s32 func_80180F84(void);
extern void func_8018122C(s32, void *);
extern void func_8017D1F0(void);
extern void func_8018144C(void*, void*);
extern void func_80181048(void*, void*);
extern void func_801825C4(void *a0);
extern s32 func_8012AD50(void *);

extern char D_80188970[];
extern void (*D_80187C78[])(void);
extern char D_801870A0[];
extern s32 D_801C7808;

void func_8017F478(s32 arg0) {
    register s32 s0v __asm__("$16");
    register s32 *s1 __asm__("$17");
    s32 v0;
    s32 *v1;
    s32 a0;
    s32 a1;

    s0v = arg0;
    s1 = (s32 *)D_801151D4;
    v0 = func_80180F84();

    if (v0 != 4) {
        return;
    }

    func_8018122C(s0v, (void *)D_80188970);
    func_8017D1F0();
    ((void (*)(s32, void *))func_8018144C)(s0v, (void *)((char *)D_80187C78));

    v0 = 0x320;
    s1[5] = v0;
    s1[4] = v0;
    ((void (*)(s32, void *))func_80181048)(s0v, (void *)D_801870A0);

    a1 = (s32)func_801825C4;
    a0 = 0;
    v1 = (s32 *)((char *)&D_801C7808);

    for (; a0 < 4; a0++) {
        if (*v1 == 0) {
            *v1 = a1;
            break;
        }
        v1 = (s32 *)((char *)v1 + 0x18);
    }

    func_8012AD50((void *)s0v);
}


extern s32 func_8012AD50(void *arg0);

void func_8017F540(s32 a0) {
    if (*(s16 *)(a0 + 0x98) != 0) {
        *(u16 *)(a0 + 0xE) -= 1;
    } else {
        func_8012AD50((void *)a0);
    }
}


void func_8017F584(s32 a0) {
    extern s32 func_80180FA4(s32, s32);
    extern s32 func_80181334(s32, s32);
    extern void func_801825C4(void *a0);
    extern void func_80182600(void *a0);
    extern void func_8017E234(void *a0);
    extern s32 D_801C7808;
    extern u8 D_80187298;
    extern s32 D_80187E80;
    extern void func_80181048(void*, void*);
    extern void func_80180F94(s32 a0);
    extern s32 func_8012AD50(void*);
    extern s32 func_80181280(s32 a0);
    s32 this = a0;
    s32 i;
    s32 j;
    s32 *ptr;
    s32 *p2;
    s32 fn;
    register s32 comp __asm__("$19");

    ((s32 (*)(s32, void *, s32))func_80180FA4)(this, (void *)&D_80187298, 1);
    if (func_80181334(this, 0) != 0) {
        comp = (s32)func_801825C4;
        ptr = (s32 *)&D_801C7808;
        for (i = 0; i < 4; i++) {
            if (*ptr == comp) {
                func_8017E234(ptr);
            }
            ptr = (s32 *)((char *)ptr + 0x18);
        }
        fn = (s32)func_80182600;
        j = 0;
        p2 = (s32 *)&D_801C7808;
        for (; j < 4; j++) {
            if (*p2 == 0) {
                *p2 = fn;
                break;
            }
            p2 = (s32 *)((char *)p2 + 0x18);
        }
    }
    if (func_80181280(this) != 0) {
        comp = (s32)func_80182600;
        ptr = (s32 *)&D_801C7808;
        for (i = 0; i < 4; i++) {
            if (*ptr == comp) {
                func_8017E234(ptr);
            }
            ptr = (s32 *)((char *)ptr + 0x18);
        }
        func_80181048(this, &D_80187E80);
        func_80180F94(5);
        func_8012AD50(this);
    }
}


extern u8 D_80187440[];
extern s32 func_8012AD50(void * arg0);
extern s32 func_80180FA4(s32, s32);

void func_8017F6BC(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&(*(s32 *)D_80187440), 0) != 0) {
        ((void (*)(void *))func_8012AD50)((void *)a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80180FA4(s32, s32);
extern void (*D_80187EE0)();

void func_8017F700(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187EE0, 0x2) != 0) {
        func_8012AD50(a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80180FF4(s32);
extern void (*D_801874E8)();

void func_8017F744(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FF4)(a0, (void *)&D_801874E8, 0x3) != 0) {
        func_8012AD50(a0);
    }
}


#include "common.h"

extern s32 func_80180F84(void);
extern void func_8017D350(void);
extern void func_8018144C(void *a0, void *a1);
extern void func_80181048(void *a0, void *a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *arg0);
extern s32 D_801151D4;
extern void (*D_80187C78[])(void);
extern u8 D_80187440[];

void func_8017F788(void *a0)
{
    s32 *s1;
    s32 v0;
    void *s0;

    s1 = (s32 *)D_801151D4;
    v0 = func_80180F84();
    s0 = a0;

    if (v0 == 0x7) {
        func_8017D350();
        func_8018144C(s0, D_80187C78);
        s1[0x14 / 4] = 0x190;
        s1[0x10 / 4] = 0x190;
        func_80181048(s0, D_80187440);
        func_8012BF4C((s32 *)s0, 0x1E);
        func_8012AD50(s0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80180F94(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern s32 func_8012AD50(void *arg0);

extern s16 D_80188B18;

void func_8017F814(s32 a0) {
    s32 s0;

    s0 = a0;
    if (func_8012BEE8(a0) != 0) {
        func_80180F94(8);
        func_8018122C(s0, &D_80188B18);
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern s32 func_80180FA4(s32, s32);
extern s32 func_80181280(s32 a0);
extern void func_80181048(void*, void*);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void *a0);

extern s32 D_80187240;
extern s32 D_80187E80;

void func_8017F864(s32 a0) {
    ((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187240, 0);
    if (func_80181280(a0) != 0) {
        ((void (*)(s32, void *))func_80181048)(a0, (void *)&D_80187E80);
        func_80180F94(0x9);
        func_8012AD50((void *)a0);
    }
}


extern s32 D_80187F30;
extern s32 func_8012AD50(void * arg0);
extern s32 func_80180FA4(s32, s32);

void func_8017F8C8(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187F30, 0) != 0) {
        ((void (*)(void *))func_8012AD50)((void *)a0);
    }
}


#include "common.h"

extern s32 D_801151D4;

extern s32 func_80180F84(void);

extern s32 D_801C7808;

extern void func_8018263C(void *a0);
extern void func_8017E234(void *a0);

extern u8 D_80188BDC[];
extern void func_8018122C(s32, void*);

extern u8 D_80187298;
extern void func_80181048(void *a0, void *a1);

extern void func_8017D350(void);

extern void (*D_80187C78[])(void);
extern void func_8018144C(void *a0, void *a1);

extern s32 func_8012AD50(void *a0);

void func_8017F90C(void *a0) {
    s32 p;
    s32 v0;
    s32 i;
    u8 *q;
    void (*cmp)(void *);

    p = D_801151D4;
    v0 = func_80180F84();
    if (v0 == 0xB) {
        cmp = func_8018263C;
        q = ((u8 *)&D_801C7808);
        for (i = 0; i < 4; i++) {
            if (*(void (**)(void *))q == cmp) {
                func_8017E234(q);
            }
            q += 0x18;
        }
        func_8018122C(a0, D_80188BDC);
        func_80181048(a0, &D_80187298);
        func_8017D350();
        func_8018144C(a0, D_80187C78);
        *(s32 *)(p + 0x14) = 0x190;
        *(s32 *)(p + 0x10) = 0x190;
        func_8012AD50(a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_8017F9EC(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0xc);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017FA2C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017FA78);

#include "common.h"

extern s32 func_80180F84(void);
extern s32 D_801151D4;           /* canonical (10 siblings): scalar s32 — store (s32)ptr */
extern void func_8018122C(s32, void*);
extern char D_80188DFC[];
extern void func_80181048(void*, void*);
extern s32 D_80187318;
extern void func_8017E234(void *a0);
extern void func_8017D1F0(void);
extern void func_801813EC(s32 a0);
extern s32 func_8012AD50(void*);
extern void func_8018272C(void *a0);

typedef struct {
    void (*fn)(void *);
    u8 unk4[0x14];
} S_801C7808_Entry;

extern s32 D_801C7808;

void func_8017FAC4(s32 a0) {
    s32 p = D_801151D4;
    s32 i;
    S_801C7808_Entry *entry;

    if (func_80180F84() == 0x14) {
        func_8018122C(a0, (s32)D_80188DFC);
        ((s32 (*)(s32, s32))func_80181048)(a0, (s32)&D_80187318);
        {
            void (*target)(void *) = func_8018272C;
            i = 0;
            entry = ((S_801C7808_Entry *)&D_801C7808);
            for (; i < 4; i++, entry++) {
                if (entry->fn == target) {
                    func_8017E234(entry);
                }
            }
        }
        func_8017D1F0();
        func_801813EC(a0);
        *(s32 *)(p + 0x14) = 0x190;
        *(s32 *)(p + 0x10) = 0x190;
        ((s32 (*)(s32))func_8012AD50)(a0);
    }
}


#include "common.h"

extern s32 D_801151D4;
extern s32 func_801815B8(s32, s32);
extern s32 func_80181334(s32, s32);
extern s32 func_8012AD50(void *);

void func_8017FBA0(s32 a0) {
    s32 *ptr = (s32 *)D_801151D4;

    func_801815B8(a0, 0);
    if (func_80181334(a0, 0) != 0) {
        ptr[5] = 0x12C;
        func_8012AD50((void *)a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_8017FBFC(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0x15);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


void func_8017FC3C(void) {
}

extern s32 func_80180F84(void);
extern void (*D_80188604[])(int);
extern void func_8012C098(void *param_1);

void func_8017FC44(int param_1)
{
    int v0;
    v0 = ((int (*)(void))func_80180F84)();

    if (v0 == 0x1a) {
        ((void (*)(int))func_8012C098)(param_1);
    } else {
        D_80188604[*(unsigned short *)(param_1 + 2)](param_1);
    }
}


#include "common.h"

/* Correcting the TU declaration: the assembly clearly uses v0 as return value */
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern s32 func_80143970(s32 a0);
extern s32 func_8012AD50(void *a0);

extern s32 D_801B5C84;
extern void (*D_80187610[])(void);

void func_8017FCAC(s32 a0) {
    s32 s0;
    s32 s1 = a0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s1 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_801B5C84);
        *(s32 *)(s0 + 0x28) = 0x7FFF7FFF;
        *(s16 *)(s1 + 0x52) = 4;
        ((void (*)(s32, s32))func_80181048)(s1, (s32)&D_80187610);
        func_80143970(s1);
        func_8012AD50((void *)s1);
    }
}


#include "common.h"

extern s32 D_801151D4;
extern void (*D_80187C78[])(void);
extern s32 D_80188A34[];
extern s32 D_80187628[];

extern s32 func_80180F84(void);
extern void func_8017D350(void);
extern void func_8018144C(void *a0, void *a1);
extern void func_8018122C(s32, void*);
extern void func_80181048(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);

void func_8017FD2C(void *a0) {
    register s32 *s1 __asm__("$17");
    register void *s0 __asm__("$16") = a0;
    s32 v0;

    s1 = (s32 *)D_801151D4;
    v0 = ((s32 (*)(void *))func_80180F84)(s0);

    if (v0 != 5) {
        return;
    }

    func_8017D350();
    func_8018144C(s0, (void *)((s32 *)D_80187C78));
    s1[5] = 0x190;
    s1[4] = 0x190;
    func_8018122C(s0, (void *)D_80188A34);
    func_80181048(s0, (void *)D_80187628);
    func_8012AD50(s0);
}


#include "common.h"

extern s32 func_80181334(s32 a0, s32 a1);
extern void func_8018141C();
extern s32 func_80181280(s32 a0);
extern void func_80181048(void*, void*);
extern void func_80180F94(s32 a0);
extern void (*D_80187610[])(void);
extern s32 func_8012AD50(void *a0);

void func_8017FDBC(s32 a0) {
    if (func_80181334(a0, 1) != 0) {
        func_8018141C(a0, 1);
    }

    if (func_80181280(a0) != 0) {
        ((void (*)(s32, void (*a1[])(void)))func_80181048)(a0, D_80187610);
        func_80180F94(6);
        func_8012AD50(a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017FE28);

extern s32 func_80180F84(void);
extern void func_80181048(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);

extern u8 D_80187858;

void func_8017FE74(s32 a0) {
    s32 s0 = a0;
    s32 v0 = func_80180F84();
    if (v0 == 8) {
        func_80181048((void *)s0, (void *)&D_80187858);
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern void func_80181048(void *a0, void *a1);
extern s32 func_80180FA4(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern void *D_801878B8;
extern void *D_80188030;

void func_8017FEC0(void *a0) {
  if (*(s16 *)((s32)a0 + 0x98) == 0) {
    func_80181048(a0, &D_801878B8);
  }

  if (((s32 (*)(s32, void *, s32))func_80180FA4)((s32)a0, (void *)&D_80188030, 1) != 0) {
    func_8012AD50(a0);
  }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8017FF28);

extern s32 func_8012AD50(void * arg0);
extern void *D_80188B5C;
extern void func_8018122C(s32, void*);

void func_8017FF74(s32 a0) {
    register s32 s0 __asm__("$16");
    s0 = a0;
    if (*(s16 *)((u8 *)s0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_8018122C)(s0, &D_80188B5C);
        ((s32 (*)(s32))func_8012AD50)(s0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_8017FFC0(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0xa);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80180000);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8018004C);

extern s32 func_80180F84(void);
extern void func_801813CC(s32 a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *arg0);

void func_801800A4(s32 a0) {
    s32 status;
    s32 *s0;

    status = func_80180F84();
    s0 = (s32 *)a0;

    if (status == 0xC) {
        func_801813CC((s32)s0);
        func_8012BF4C(s0, 0x1E);
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80180F94(s32 a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_80181048(void *, void *);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 func_8012AD50(void *a0);

extern s32 D_80188C00;
extern s32 D_80187740;
extern s32 D_801B54FC;
extern s32 D_801B5CB0;
extern s32 D_801B6438;

void func_801800F4(s32 a0) {
    s32 s0 = a0;

    if (func_8012BEE8(s0) != 0) {
        func_80180F94(0xD);
        func_8018122C(s0, &D_80188C00);
        func_80181048((void *)s0, &D_80187740);
        func_8012BF4C((s32 *)s0, 0);
        func_801325B8((s32)&D_801B54FC, (s32)&D_801B5CB0, (s32)&D_801B6438, 0, 0x1000);
        func_8012AD50((void *)s0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80180188);

extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_801801C8(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0xe);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


#include "common.h"

extern s32 func_80180F84(void);
extern void func_801813EC(s32 a0);
extern void func_8017D4E4(void);
extern void func_8018122C(s32, void*);
extern void func_80181048(void*, void*);
extern s32 func_8012AD50(void *a0);

extern s32 D_80188E4C;
extern s32 D_801876B8;

void func_80180208(s32 a0) {
    s32 s0 = a0;
    s32 v0 = func_80180F84();
    if (v0 == 0x15) {
        func_801813EC(0);
        func_8017D4E4();
        func_8018122C(s0, (s32)&D_80188E4C);
        ((void (*)(s32, s32))func_80181048)(s0, (s32)&D_801876B8);
        func_8012AD50((void *)s0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);

void func_80180274(s32 a0) {
    if (func_80181280(a0) != 0) {
        func_80180F94(0x17);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


void func_801802B4(void) {
}

extern s32 func_80180F84(void);
extern void (*D_80188654[])(int);
extern void func_8012C098(void *param_1);

void func_801802BC(int param_1)
{
    int v0;
    v0 = ((int (*)(void))func_80180F84)();

    if (v0 == 0x1a) {
        ((void (*)(int))func_8012C098)(param_1);
    } else {
        D_80188654[*(unsigned short *)(param_1 + 2)](param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern void func_80143994(s32 a0, s32 a1);
extern s32 func_8012AD50(void* arg0);

extern s32 D_801BA63C;
extern void *D_80188098;

void func_80180324(s32 a0) {
    s32 s0;
    s32 s1;

    s1 = a0;
    s0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s1 + 0x20) = s0;

    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_801BA63C);
        *(s32 *)(s0 + 0x28) = 0x7FFF7FFF;
        *(s16 *)(s1 + 0x52) = 4;
        ((void (*)(s32, s32))func_80181048)(s1, (s32)&D_80188098);
        func_80143994(s1, 0x3000);
        func_8012AD50((void *)s1);
    }
}


extern s32 func_8012E544(s32);
extern s32 func_801815B8(s32, s32);
extern s32 func_80180F84(void);
extern s32 func_8012AD50(void*);

void func_801803A8(s32 a0)
{
    s32 v0;

    v0 = func_8012E544(0x357);
    v0 = func_801815B8(a0, v0);
    v0 = func_80180F84();
    if (v0 == 3) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_801803FC);

#include "common.h"

extern s32 func_8012E544(s32 a0);
extern s32 func_801815B8(s32 a0, s32 a1);
extern s32 func_80180F84(void);
extern void func_80181048(void*, void*);
extern s32 func_8012AD50(void*);

extern void *D_80187B90;
extern void *D_80188098;

void func_8018044C(s32 a0) {
    register s32 s0 __asm__("$16");
    s32 v0;

    s0 = a0;
    v0 = func_8012E544(0x357);
    func_801815B8(s0, v0);

    if (*(s16 *)((u8 *)s0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_80181048)(s0, &D_80187B90);
    }

    v0 = func_80180F84();
    if (v0 == 4) {
        ((void (*)(s32, void *))func_80181048)(s0, &D_80188098);
        ((s32 (*)(s32))func_8012AD50)(s0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_801804D0);

#include "common.h"

extern s32 func_8012E544(s32);
extern s32 func_801815B8(s32, s32);
extern s32 func_80180FA4(s32, s32);
extern s32 func_8012AD50(void*);

extern void (*D_80187AE8)();

void func_80180524(s32 a0)
{
    s32 v0;

    v0 = func_8012E544(0x357);
    v0 = func_801815B8(a0, v0);
    v0 = ((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187AE8, 1);
    if (v0 != 0) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


extern s32 func_80180FA4(s32, s32);
extern s32 func_8012AD50(void *arg0);
extern void (*D_80187AE8)();

void func_80180580(s32 a0) {
    if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187AE8, 0x3) != 0) {
        func_8012AD50(a0);
    }
}


extern void func_80181048(void*, void*);
extern s32 func_8012AD50(void*);
extern void *D_80187B90;

void func_801805C4(s32 a0) {
    register s32 s0 __asm__("$16");
    s0 = a0;
    if (*(s16 *)((u8 *)s0 + 0x98) == 0) {
        ((void (*)(s32, void *))func_80181048)(s0, &D_80187B90);
        ((s32 (*)(s32))func_8012AD50)(s0);
    }
}


extern s32 func_80180F84(void);
extern void func_80181048(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);
extern void *D_80188098;

void func_80180610(s32 a0) {
    s32 s0 = a0;
    s32 v0 = func_80180F84();
    if (v0 == 8) {
        func_80181048((void *)s0, (void *)&D_80188098);
        func_8012AD50((void *)s0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_8012E544(s32 a0);
extern s32 func_80180F84(void);
extern s32 func_801815B8(s32, s32);

void func_8018065C(s32 a0)
{
    s32 v0;

    v0 = func_8012E544(0x358);
    v0 = func_801815B8(a0, v0);
    v0 = func_80180F84();
    if (v0 == 14) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


#include "common.h"

extern s32 func_8012E544(s32 a0);
extern s32 func_801815B8(s32 a0, s32 a1);
extern s32 func_80180F84(void);
extern s32 func_80181334(s32 a0, s32 a1);
extern void func_801813CC(s32 a0);
extern void func_80181470();
extern s32 func_8012AD50(void *a0);
extern u16 D_80187C88;

void func_801806B0(s32 a0) {
    s32 v0;

    v0 = func_8012E544(0x357);
    func_801815B8(a0, v0);
    v0 = func_80180F84();

    if (v0 != 0xF) {
        return;
    }

    v0 = func_80181334(a0, 1);
    if (v0 == 0) {
        return;
    }

    func_801813CC(a0);
    func_80181470(a0, (void *)&D_80187C88, 1);
    func_8012AD50((void *)a0);
}


extern s32 func_80180F84(void);
extern void func_8018122C(s32, void*);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern s32 D_80188CA4[];

void func_80180730(s32 a0) {
    s32 s0 = a0;

    if (func_80180F84() == 0x11) {
        func_8018122C(s0, D_80188CA4);
        func_8012C588(0x388, s0);
        *(s16 *)(s0 + 0xFC) = 0;
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern s32 func_8012E544(s32 a0);
extern s32 func_801815B8(s32, s32);
extern s32 func_80180FA4(s32, s32);
extern s32 func_80181334(s32, s32);
extern void func_80181048(void*, void*);
extern void func_80180F54();
extern void func_80181524(s32 *, s32);
extern s32 func_8012AD50(void *);

extern s32 D_801879C0;
extern void *D_80188098;
extern s32 D_80187900;
extern s32 D_8018864C;

void func_8018078C(s32 a0) {
    s32 v0;
    s16 state = *(s16 *)(a0 + 0xFC);

    switch (state) {
        case 0:
            if (((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_801879C0, 0) != 0) {
                *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
            }
            break;
        case 1:
            v0 = func_8012E544(0x358);
            v0 = func_801815B8(a0, v0);
            v0 = func_80181334(a0, 1);
            if (v0 != 0) {
                ((void (*)(s32, void *))func_80181048)(a0, (void *)&D_80188098);
                ((void (*)(s32, void *))func_80181048)(a0, (void *)&D_801879C0);
                *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
            }
            break;
        case 2:
            v0 = func_8012E544(0x357);
            v0 = func_801815B8(a0, v0);
            v0 = ((s32 (*)(s32, void *, s32))func_80180FA4)(a0, (void *)&D_80187900, 2);
            if (v0 != 0) {
                *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
                func_80180F54();
                func_80181524((s32 *)a0, (s32)&D_8018864C);
                func_8012AD50((void *)a0);
            }
            break;
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_801808C4);

#include "common.h"

extern s32 func_80180FA4(s32, s32);
extern void func_80181048(void*, void*);
extern s32 func_80181334(s32 a0, s32 a1);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void *arg0);

extern void *D_80188098;
extern u8 D_80187BD8;

void func_8018090C(s32 a0) {
    void *ptr = &D_80187BD8;

    ((s32 (*)(s32, void *, s32))func_80180FA4)(a0, ptr, 3);

    if (func_80181334(a0, 4) != 0) {
        func_80181048(a0, &D_80188098);
        func_80181048(a0, ptr);
    }
    if (func_80181334(a0, 5) != 0) {
        func_80181048(a0, &D_80188098);
        func_80181048(a0, ptr);
    }
    if (func_80181334(a0, 6) != 0) {
        func_80181048(a0, &D_80188098);
        func_80181048(a0, ptr);
    }
    if (func_80181280(a0) != 0) {
        func_80180F94(0x12);
        func_8012AD50((void *)a0);
    }
}


extern s32 func_80180F84(void);
extern s32 func_80181334(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_801809FC(s32 a0)
{
    if (func_80180F84() == 0x13 && func_80181334(a0, 1) != 0) {
        func_8012AD50(a0);
    }
}


extern s32 func_8012AD50(void*);
extern s32 func_80180F84(void);
extern s32 func_801815B8(s32, s32);

void func_80180A48(s32 a0)
{
    s32 v0;

    func_801815B8(a0, 0);
    v0 = func_80180F84();
    if (v0 == 0x14) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_8012E544(s32 a0);
extern s32 func_80180F84(void);
extern s32 func_801815B8(s32, s32);

void func_80180A90(s32 a0)
{
    s32 v0;

    v0 = func_8012E544(0x358);
    v0 = func_801815B8(a0, v0);
    v0 = func_80180F84();
    if (v0 == 21) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_8012E544(s32 a0);
extern s32 func_80180F84(void);
extern s32 func_801815B8(s32, s32);

void func_80180AE4(s32 a0)
{
    s32 v0;

    v0 = func_8012E544(0x359);
    v0 = func_801815B8(a0, v0);
    v0 = func_80180F84();
    if (v0 == 22) {
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


void func_80180B38(s32 a0)
{
    func_801815B8(a0, 0);
}


extern s32 func_80180F84(void);
extern void (*D_801886A4[])(int);
extern void func_8012C098(void *param_1);

void func_80180B58(int param_1)
{
    int v0;
    v0 = ((int (*)(void))func_80180F84)();

    if (v0 == 0x1a) {
        ((void (*)(int))func_8012C098)(param_1);
    } else {
        D_801886A4[*(unsigned short *)(param_1 + 2)](param_1);
    }
}


#include "common.h"

/* Externs needed by func_80180BC0 */
/* NOTE: the destination TU (src/ov_SC07_007/ov_SC07_007_jr_8017BEBC.c:296) declares
 * func_8012C1B8 as `void func_8012C1B8(void)`, even though it clearly returns a value
 * (used to seed s1). This mirrors the established idiom already used elsewhere in this
 * TU / sibling TUs (e.g. src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:6815) for the SAME
 * function: keep the TU's `void` decl and cast to a function-pointer type at the call
 * site instead of redeclaring with a conflicting return type. */
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern void func_8001D150(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern s32 D_801C1E00;
extern s32 D_801880A8;

void func_80180BC0(void *a0) {
    register s32 s2 __asm__("$18") = (s32)a0;
    s32 s1;
    s32 s0;

    s1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s2 + 0x20) = s1;

    if (!s1) {
        return;
    }

    s0 = (s32)&D_801C1E00;
    func_8001C214(s1, s0);

    *(s32 *)(s1 + 0x28) = 0x7FFF7FFF;

    *(u16 *)(s2 + 0x52) = 0x4;
    ((void (*)(s32, s32))func_80181048)(s2, (s32)&D_801880A8);

    func_8001D150(s0, 0x19);
    func_8001D150(s0, 0x16);

    *(s32 *)(s1 + 0x4) |= 0x80000000;

    func_8012AD50((void *)s2);
}


#include "common.h"

extern s32 func_80180F84(void);
extern void func_801813EC(s32 a0);
extern s32 func_8012AD50(void *arg0);

void func_80180C6C(s32 param_1)
{
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    if (func_80180F84() == 0x18) {
        *(u16 *)(s0 + 0x12) = 0xC00;
        *(s32 *)(s0 + 4) &= 0x7FFFFFFF;
        *(u16 *)(s0 + 0x2C) |= 0x10;
        func_8017D5B0();
        func_801813EC(param_1);
        func_8012AD50((void *)param_1);
    }
}


extern s32 func_8012AD50(void *arg0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

void func_80180CE8(void *a0) {
    s32 s0;
    s32 ret;

    s0 = *(s32 *)(a0 + 0x20);
    ret = func_8012B608(*(s16 *)(s0 + 0x12), 0x940, 4);
    *(s16 *)(s0 + 0x1C) = 0xB33;
    *(s16 *)(s0 + 0x1A) = 0xB33;
    *(s16 *)(s0 + 0x18) = 0xB33;
    *(s16 *)(s0 + 0x12) = (*(u16 *)(s0 + 0x12) + ret) & 0xFFF;
    if ((s16)ret == 0) {
        func_8012AD50(a0);
    }
}


#include "common.h"

extern s32 func_8012AD50(void *a0);
extern void func_8018122C(s32 a0, void *a1);
extern void func_801827A4(void *a0);

extern void (*D_80188EB0)(void *);
extern s32 D_801C7808;

void func_80180D5C(s32 a0)
{
    void *fn_ptr;
    s32 i;
    void **v1;

    func_8018122C(a0, &D_80188EB0);

    fn_ptr = func_801827A4;
    i = 0;

    for (v1 = (void **)&D_801C7808; i < 4; i++, v1 = (void **)((char *)v1 + 0x18)) {
        if (v1[0] == 0) {
            v1[0] = fn_ptr;
            break;
        }
    }

    func_8012AD50((void *)a0);
}


#include "common.h"

extern s32 func_80181334(s32 a0, s32 a1);
extern void func_80181048(void*, void*);
extern s32 func_80181280(s32 a0);
extern void func_80180F94(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_80188150;

void func_80180DCC(s32 a0) {
    s32 v0;

    v0 = func_80181334(a0, 0);
    if (v0 != 0) {
        ((s32 (*)(s32, void *))func_80181048)(a0, &D_80188150);
    }

    v0 = func_80181280(a0);
    if (v0 != 0) {
        func_80180F94(0x19);
        func_8012AD50(a0);
    }
}


void func_80180E30(void) {
}



void func_80180E38(void *a0) {

    extern void (*D_801886E8[])(void);
    D_801886E8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80180F38(void *a0);
extern s32 func_8012AD50(void *a0);

extern u16 D_801C4C44[];

void func_80180E74(void *a0) {
    s32 v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 != 0) {
        func_8001C214(v0, (s32)D_801C4C44);
        *(s16 *)((s32)a0 + 0xFC) = 0;
        func_80180F38(a0);
        func_8012AD50(a0);
    }
}


extern void func_800183E0(s32 a0);
extern void func_80180F38(void*);
extern s32 D_801886C8[];

void func_80180EC8(s32 param_1)
{
    s32 temp_v0;

    temp_v0 = *(u16 *)(param_1 + 0xFC);
    *(u16 *)(param_1 + 0xFC) = temp_v0 + 1;
    if (D_801886C8[(temp_v0 << 16) >> 16] == 0) {
        *(u16 *)(param_1 + 0xFC) = 1;
        func_800183E0(D_801886C8[0]);
    } else {
        func_800183E0(D_801886C8[(temp_v0 << 16) >> 16]);
    }
    ((void (*)(s32))func_80180F38)(param_1);
}


void func_80180F38(void *a0) {
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
}


extern void func_8012C098(void*);
extern s32 func_8012E544(s32 a0);

    void func_80180F54(void) {
        s32 result = func_8012E544(0x388);
        if (result != 0) {
            ((s32 (*)(void *))func_8012C098)((void *)result);
        }
    }




s32 func_80180F84(void) {

    extern s32 D_801C7A08;
    return D_801C7A08;
}


void func_80180F94(s32 a0) {

    extern s32 D_801C7A08;
    D_801C7A08 = a0;
}


#include "common.h"

extern s32 func_80180FF4(s32);
extern void func_801813A8(s32, s32);

s32 func_80180FA4(s32 a0, s32 a1) {
    register s32 s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    s32 res;
    register s32 tmp __asm__("$6");
    s0 = tmp;
    res = func_80180FF4(s1);
    if (res != 0) {
        func_801813A8(s1, s0);
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80180FF4);

s32 aF80181048(void *a0, void *a1) __asm__("func_80181048");
s32 aF80181048(void *a0, void *a1) {
    extern void func_8012A828(s32 a0, void *a1);

    if (*(s32 *)((u8 *)a0 + 0x90) == (s32)a1) {
        return 0;
    }
    func_8012A828((s32)a0, a1);
    return 1;
}


extern void func_801810CC(s32, s32, s32);
extern void func_801813A8(s32, s32);

s32 func_8018107C(s32 a0, s32 a1, s32 a2) {
    register s32 s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    s32 res;
    register s32 tmp __asm__("$6");
    s0 = tmp;
    res = ((s32 (*)(s32, s32, s32))func_801810CC)(a0, a1, a2);
    if (res != 0) {
        func_801813A8(s1, s0);
        return 1;
    }
    return 0;
}


extern s32 func_80181384(s32, s32);
extern void func_80181120(void);

s32 func_801810CC_body(s32 a0, s32 a1, s32 a2) __asm__("func_801810CC");
s32 func_801810CC_body(s32 a0, s32 a1, s32 a2) {
    if (func_80181384(a0, a2) != 0) {
        ((void (*)(s32, s32))func_80181120)(a0, a1);
        return 1;
    }
    return 0;
}


extern void func_80181140();
void func_80181120(void) {
    func_80181140();
}


void func_80181140(s32 a0, s32 a1) {
    s32 *r = (s32 *)a1;
    if (r[3] == 0) {
        return;
    }
    do {
        MoveImage(r, r[2], r[3]);
        r += 4;
    } while (r[3] != 0);
}


extern s32 D_801C79CC;
extern void func_801812BC(void);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012EFB8(s32 a0);
extern void func_80137614(s32 a0, s32 a1, s32 a2);

void func_801811A0(s32 param_1, s32 param_2, s32 param_3)
{
    u16 sp10[3];
    s32 ret;

    func_801812BC();
    if (D_801C79CC == 0) {
        func_80015978(param_1 + 4, (s32 *)sp10);
        ret = ((s32 (*)(s32, s32))func_8012EFB8)((s32)sp10, (s32)sp10);
        if ((ret & ~0x1000) != 0) {
            sp10[0] = 0;
        }
        *(s32 *)(param_1 + 0xCC) =
            ((s32 (*)(s32, s16, s32))func_80137614)(param_2, (s16)sp10[0], (u16)param_3);
    }
}


extern s32 D_801C79CC;
extern void func_801812BC(void);
extern s32 func_8013767C(s32 a0);

void func_8018122C(s32 param_1, void* param_2)
{
    register s32 base __asm__("$16");
    register s32 val __asm__("$17");

    base = param_1;
    val = param_2;
    func_801812BC();
    if (D_801C79CC == 0) {
        *(s32 *)(base + 0xCC) = func_8013767C(val);
    }
}


extern s32 func_801399F0(s32 a0);
extern s32 D_801C79CC;

s32 func_80181280(s32 a0) {
    if (D_801C79CC == 0) {
        return func_801399F0(*(s32 *) (a0 + 0xCC)) != 0;
    }
    return 0;
}


extern void func_80029124(s32, s32);
void func_801812BC(void) {
    func_80029124(0x125, 0);
    func_80029124(0x126, 0);
    func_80029124(0x127, 0);
    func_80029124(0x128, 0);
    func_80029124(0x129, 0);
    func_80029124(0x12A, 0);
    func_80029124(0x12B, 0);
    func_80029124(0x12C, 0);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181334);

extern s32 func_80029178(s32 arg);

s32 func_80181384(s32 a0, s32 a1)
{
    return (func_80029178(a1 + 0x125) & 0xFF) != 0;
}


extern void func_80029124(s32, s32);

void func_801813A8(s32 a0, s32 a1) {
    func_80029124(a1 + 0x125, 0);
}


extern void func_80142414(s32 a0, s16 a1);

void func_801813CC(s32 a0) {
    func_80142414(a0, -0x8C);
}


#include "common.h"

extern void func_8017DF5C(s32, s32);

void func_801813EC(s32 param_1) {
    s32 var;

    if (param_1 == 0) {
        var = 0;
    } else {
        var = *(u16 *) param_1;
    }
    func_8017DF5C(var, -1);
}


#include "common.h"

extern void func_8017DF5C(s32, s32);

void func_8018141C(s32 param_1, s32 param_2) {
    s32 var;

    if (param_1 == 0) {
        var = 0;
    } else {
        var = *(u16 *) param_1;
    }
    ((void (*)(s32))func_8017DF5C)(var);
}


extern s32 func_8017DF74();

void func_8018144C(void *param_1, void *param_2) {
    func_8017DF74((s32)param_2, -1);
}


extern s32 func_8017DF74();

void func_80181470(s32 a0, void *a1, s32 a2) {
    ((void (*)(void *, s32))func_8017DF74)(a1, a2);
}


extern s32 D_80126B58;
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8017DF74();

void func_80181494(s32 a0, u16 *arg1, void *a2)
{
    u16 sp10[3];
    s32 base;

    base = (s32)&D_80126B58;
    if (a0 == 0) {
        a0 = base + 4;
    } else {
        a0 = a0 + 4;
    }
    func_80015978(a0, sp10);
    sp10[0] = sp10[0] + *(u16 *)arg1;
    sp10[1] = sp10[1] + *(u16 *)(arg1 + 1);
    sp10[2] = sp10[2] + *(u16 *)(arg1 + 2);
    ((void (*)(s32, s32 *))func_8017DF74)((s32)sp10, (s32 *)a2);
}



void func_80181524(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0xF4) = a1;
}


extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);

s32 func_8018152C(s32 a0) {
    s16 *s1;
    s1 = *(s16 **)(a0 + 0xF4);
    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s1) < 0x101) {
        goto ret1;
    }
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B744((void *)(a0 + 4), (void *)s1);
    func_8012B178(a0, *(s16 *)(s1 + 3) << 16);
    func_8012AD80(a0);
    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 8;
    func_8012B030((u8 *)a0);
    return 0;
ret1:
    return 1;
}


extern s32 D_80126B58;
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_80181614();

s32 func_801815B8(s32 arg0, s32 arg1) {
    s16 *ptr;
    s16 var;

    ptr = (s16 *) &D_80126B58;
    if (arg1 == 0) {
        var = func_8012B6D4((s16 *) (arg0 + 4), ptr + 2);
    } else {
        var = func_8012B6D4((s16 *) (arg0 + 4), (s16 *) (arg1 + 4));
    }
    func_80181614(arg0, var);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181614);



void func_80181668(void *a0) {

    extern void (*D_801886FC[])(void);
    D_801886FC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C194(void);
extern s32 func_8012AD50(void * arg0);
extern void func_8001CBDC(void *a0, void *a1, s32 a2, s32 a3);
extern s32 D_801886F0;

void func_801816A4(s32 a0) {
    register s32 s1 asm("$17") = a0;
    register s32 s0 asm("$16");
    u16 v0;

    v0 = *(u16 *)(s1 + 0x72);
    v0 = v0 | 0x1000;
    *(u16 *)(s1 + 0x72) = v0;

    s0 = ((s32 (*)(void))func_8012C194)();

    *(s32 *)(s1 + 0x20) = s0;

    if (s0 != 0) {
        func_8001CBDC((void *)s0, (void *)&D_801886F0, 0x300, 0x100);

        *(u8 *)(s0 + 0x27) = 0x33;
        *(u16 *)(s0 + 0x2C) = 0x1;
        *(s32 *)(s0 + 0x4) = *(s32 *)(s0 + 0x4) | 0x80000000;

        func_8012AD50((void *)s1);
    }
}


#include "common.h"

extern void func_801827E0(void);
extern void func_80181960(s32, s32, s32);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *arg0);

extern s32 D_801C7A08;

void func_80181730(void *a0)
{
    s32 *s1;
    s32 v0;
    void *s0;

    v0 = D_801C7A08;
    s1 = *(s32 **)(a0 + 0x20);
    s0 = a0;

    if (v0 == 0x19) {
        func_801827E0();
        *(u16 *)(s0 + 0x72) |= 0x1000;
        s1[4 / 4] &= 0x7FFFFFFF;
        func_80181960(0xFFFFFF, 2, 0);
        func_8012BF4C((s32 *)s0, 0x3C);
        D_801C7A08 = 0x1A;
        func_8012AD50(s0);
    }
}


#include "common.h"

extern void func_80181960();
extern s32 func_8012BEE8(s32 a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_801817D0(s32 a0) {
    func_80181960(0xFFFFFF, 2, 0);
    if (func_8012BEE8(a0) != 0) {
        func_8012BF4C((s32 *)a0, 0x1E);
        func_8012AD50((void *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181828);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181878);

#include "common.h"

extern void func_80017254(void *);

void func_80181960(s32 arg0, s32 arg1, s32 arg2)
{
    struct {
        u32 f00;
        u16 f04;
        u16 pad06;
        u32 f08;
        u32 pad0C;
        u32 f10;
        u32 pad14;
        u32 f18;
        u32 pad1C;
        void *f20;
        void *f24;
    } st;

    st.f20 = (void *)arg0;
    st.f00 = 0xFF10FEC0;
    st.f08 = 0xFF100140;
    st.f10 = 0x00F0FEC0;
    st.f18 = 0x00F00140;
    st.f04 = arg1;
    st.f24 = (void *)arg2;
    func_80017254(&st);
}


void func_801819BC(s32 arg0)
{
    extern void (*D_801887B8[39])(void *);
    extern s32 D_801C7A08;
    extern s32 D_801C799C;
    extern s32 D_801C7868;
    extern s32 D_801C786C;
    extern s32 D_801C7870;
    extern s32 D_801C79CC;
    extern s32 func_8018283C();

    D_801887B8[*(u16 *)(arg0 + 2)](arg0);

    if (0x19 < D_801C7A08) {
        D_801C799C = D_801C799C + 1;
    }

    if (D_801C7868 != 1) {
        if (D_801C7868 < 2) {
            return;
        }
        if (D_801C7868 == 2) {
            goto Lstore;
        }
        return;
    } else {
        D_801C7870 = 0;
        if (D_801C79CC != 0) {
            return;
        }
        if (func_8018283C(D_801C786C) == 0) {
            return;
        }
        D_801C7868 = D_801C7868 + 1;
    }
Lstore:
    D_801C7870 = 1;
}


void func_80181AA8(s32 *a0) {
    extern s32 D_801C7870;
    extern s32 D_801C7A08;
    extern s32 D_801C7868;
    extern s32 D_801C79A4;
    extern s32 D_801C79B0;
    extern s32 D_800B9A18;
    extern void func_800146B0(s32 a0);
    extern s32 func_8012AD50(void *arg0);

    register s32 one __asm__("$2");
    u16 flags;
    s32 v0;

    one = 1;
    flags = *(u16 *)((s32)a0 + 0x72);
    D_801C7870 = one;
    *(u16 *)((s32)a0 + 0x72) = flags | 0x1000;

    v0 = D_801C7A08;
    D_801C7868 = 0;
    D_801C79A4 = 0;
    D_801C79B0 = 0;

    if (v0 == 0x1B) {
        func_800146B0(7);
        D_800B9A18 = 0;
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern s32 func_80181B8C(void);
extern void func_800146B0(s32 a0);
extern void func_800D1724(s32 a0);
extern s32 func_8012AD50(void * arg0);

extern s32 D_800B9A18;
extern u8 D_80186940[];

void func_80181B28(s32 a0) {
    s32 s0 = a0;

    if (func_80181B8C() != 0) {
        func_800146B0(1);
        D_800B9A18 = 2;
        func_800D1724((s32)D_80186940);
        func_8012AD50((void *)s0);
    }
}


void func_80181B84(void) {
}

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181B8C);

void func_80181DFC(s32 arg0) {
    extern s32 D_801C7868;
    extern s32 D_801C786C;
    extern s32 D_801C7870;

    if (D_801C7870 != 0) {
        D_801C7868 = 1;
        D_801C786C = arg0;
    }
}




s32 func_80181E28(void) {

    extern s32 D_801C7870;
    return D_801C7870;
}


extern s32 D_801C7994[];

void func_80181E38(s32 a0) {
    D_801C7994[a0] = 0;
}


#include "common.h"

extern s32 D_801C7994[];
extern void func_80181F4C(s32, s32);
extern void func_80182184(s32, s32);

s32 func_80181E50(s32 a0, s32 a1) {
    s32 val;
    register s32 s0 __asm__("$16") = 0;

    val = D_801C7994[a0] + 1;
    D_801C7994[a0] = val;

    if (val >= 0x80) {
        D_801C7994[a0] = 0x80;
        s0 = 1;
    }

    if (a0 == 0) {
        ((void (*)(u8, u8))func_80181F4C)((u8)D_801C7994[0], (u8)(a1 & 0xFF));
    } else {
        ((void (*)(u8, u8))func_80182184)((u8)D_801C7994[a0], (u8)(a1 & 0xFF));
    }

    return s0;
}


#include "common.h"

extern s32 D_801C7994[];
extern void func_80181F4C(s32 a0, s32 a1);
extern void func_80182184(s32 a0, s32 a1);

s32 func_80181ED4(s32 a0, s32 a1) {
    s32 *base = D_801C7994;
    s32 s0 = 0;
    s32 *v1 = base + a0;
    s32 v0 = *v1;

    v0--;
    *v1 = v0;

    if (v0 <= 0) {
        *v1 = 0;
        s0 = 1;
    }

    if (a0 == 0) {
        func_80181F4C((s32)*(u8*)&D_801C7994[0], a1 & 0xFF);
    } else {
        func_80182184((s32)*(u8*)v1, a1 & 0xFF);
    }

    return s0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80181F4C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80182184);



void func_801825C4(void *a0) {

    extern void (*D_801882C4[])(void);
    D_801882C4[*(u16 *)((s32)a0 + 0x4)]();
}




void func_80182600(void *a0) {

    extern void (*D_801882CC[])(void);
    D_801882CC[*(u16 *)((s32)a0 + 0x4)]();
}




void func_8018263C(void *a0) {

    extern void (*D_801882D4[])(void);
    D_801882D4[*(u16 *)((s32)a0 + 0x4)]();
}




void func_80182678(void *a0) {

    extern void (*D_801882DC[])(void);
    D_801882DC[*(u16 *)((s32)a0 + 0x4)]();
}




void func_801826B4(void *a0) {

    extern void (*D_801882E4[])(void);
    D_801882E4[*(u16 *)((s32)a0 + 0x4)]();
}




void func_801826F0(void *a0) {

    extern void (*D_801882EC[])(void);
    D_801882EC[*(u16 *)((s32)a0 + 0x4)]();
}




void func_8018272C(void *a0) {

    extern void (*D_801882F4[])(void);
    D_801882F4[*(u16 *)((s32)a0 + 0x4)]();
}




void func_80182768(void *a0) {

    extern void (*D_801882FC[])(void);
    D_801882FC[*(u16 *)((s32)a0 + 0x4)]();
}




void func_801827A4(void *a0) {

    extern void (*D_80188544[])(void);
    D_80188544[*(u16 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_801827E0);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_8018283C);

extern void func_80171928(void*);
void func_80182888(void) {
    ((void (*)(void))func_80171928)();
}


extern s32 func_80180F84(void);
extern void func_80147060(u8 *a0);
extern void func_80171928(void *a0);

void func_801828A8(s32 a0) {
    s32 s0 = a0;
    if (func_80180F84() == 2) {
        func_80147060((u8 *)s0);
        func_80171928((void *)s0);
    }
}



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_801828EC(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 3) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_80182928(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 4) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_80182964(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 6) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }


extern s32 func_80180F84(void);
extern void func_80147060(u8 *a0);
extern void func_80171928(void *a0);

void func_801829A0(s32 a0) {
    if (func_80180F84() == 0xA) {
        func_80147060((u8 *)a0);
        func_80171928((void *)a0);
    }
}



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_801829E4(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 15) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_80182A20(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 18) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_80182A5C(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 19) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }



extern s32 func_80180F84(void);
    extern void func_80171928(void *a0);
    void func_80182A98(void *a0) {
        if (((s32 (*)(s32))func_80180F84)((s32)a0) == 21) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }




void func_80182AD4(void *a0) {

    extern void (*D_801A359C[])(void);
    D_801A359C[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80182B10);

extern s32 func_80180F84(void);
extern void func_80171A80(s32 *a0, s32 a1);
extern void func_80171928(void *a0);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);

void func_80182B50(s32 a0) {
    extern u8 D_801A35A4;

    if (func_80180F84() == 0x17) {
        func_80171A80((s32 *)a0, 0xA);
        func_80171928((void *)a0);
    }

    func_80171D1C((void *)a0, &D_801A35A4, 0x50);
}


extern s32 func_80171A88(s32 a0);
extern void func_80180F94(s32 a0);
extern void func_80171928(void *a0);

void func_80182BA8(s32 a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) - 0x2D;
    if (func_80171A88(a0) != 0) {
        func_80180F94(0x18);
        func_80171928((void *)a0);
    }
}




void func_80182C00(void *a0) {

    extern void (*D_801A35AC[])(void);
    D_801A35AC[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_801719A4(int a0, int a1);
extern s32 func_80171990(u8 *a0);
extern void func_80182C78(u8 *a0);
void func_80182C3C(u8 *a0) {
    func_801719A4((int)a0, 1);
    func_80171990(a0);
    func_80182C78(a0);
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_8017BEBC", func_80182C78);

extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182CBC(s32 a0) {

    extern u8 D_801A3198;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A3198);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182CFC(s32 a0) {

    extern u8 D_801A31B8;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A31B8);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182D3C(s32 a0) {

    extern u8 D_801A3228;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A3228);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182D7C(s32 a0) {

    extern u8 D_801A325C;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A325C);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182DBC(s32 a0) {

    extern u8 D_801A3300;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A3300);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182DFC(s32 a0) {

    extern u8 D_801A333C;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A333C);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182E3C(s32 a0) {

    extern u8 D_801A3394;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A3394);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80171928(void*);
void func_80182E7C(s32 a0) {

    extern u8 D_801A3424;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_801A3424);
    ((s32 (*)(u8 *))func_80171928)((u8 *)a0);
}


extern s32 func_8016EFA8(s32);
void func_80182EBC(void) {

    extern s32 D_801A34B8(void *a0);
    ((void (*)(void *, s32))func_8016EFA8)((void *)D_801A34B8, 0x1000000);
}


