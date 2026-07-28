#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* size 8, alignment 1 -> unaligned copy */
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
extern void func_80144B9C();
extern u8 D_800B9A17;
extern u8 D_800B9A10;
extern void func_80128420(void);
extern s32 func_800D0588(void);
extern void func_801284B8(void);
extern void func_80175308();
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
extern u8 D_80126948[];
extern struct BigCopy D_80114EE8;
extern s32 D_80126E60[];
extern s8 D_801150D6;
extern s8 D_801152C0;
extern u8 D_80127504;
extern void func_800144D4(void);
extern void func_80129C40(s32 _arg0);
extern void func_8012A328();
extern void func_80053308(s32);
extern s32 func_80012F74(s32, s32, s32, s32);  /* canonical s32 (engine_core); (s16)-cast the return for the sll/sra */
extern void GsSetRefView2L(void *);
extern s8 D_801150D6;            /* canonical (engine_core macro): s8 — access via *(u8*)& for lbu */
extern s32 D_80126F04[];
extern u8 D_80126948[];          /* canonical (sibling): u8[] — cast (s32*) at use */
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
extern s32 func_8012CC88();
extern u8 D_800D3918[];
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern s32 func_8012CC88();
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
extern void func_8012E138();
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
extern void func_80131E00();
extern s32 D_801F4D80;
extern s32 D_801F4D84;
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void func_80019064(void *a0);
extern void func_8016AA50(int, int);
extern void func_8016B428(int);
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
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
/* ==== end §8b carried decl layer ==== */



// @class: regalloc-order
// @stuck: none — MATCH (match_one 100/100 + rtu_match real-TU); needs the PAIRED //@EDIT on ((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)(return s16->s32 + `s32 result;`->`s16 result;`, whole-TU byte-neutral, verified) + one $s1 pin on `flag`
//@EDIT s16 ((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)||s32 ((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
//@EDIT     s32 result;||    s16 result;

/* func_80135D20 — "is <thing> visible/hittable from <pos>" gate (100 ins, ov_SC06_018 jr_8012ACE0).
 *
 * Builds a second probe point 0x300 above the caller's point on the stack, asks func_80135480 to
 * cull/transform it, then dispatches on that result (jtbl_801D2A90, cases 0..4; default falls
 * through with p/flag/q UNINITIALISED — reproduced by leaving the switch without a default).
 *
 * Load-bearing details (do not "clean up"):
 *  - `u8 dead[96];` is a DEAD aggregate whose only job is the frame layout: it forces the probe
 *    buffer to sp+0x70 and the frame to 0x98 (gcc-2.7.2 assign_stack_local runs at expand time, so
 *    an unreferenced aggregate still owns its slot). Remove it and every sp offset shifts by 0x60.
 *  - `__asm__ __volatile__("")` is the §5a CROSS-JUMP BARRIER: without it jump.c merges the peeled
 *    first func_80135EB0 probe into the list loop (100 ins -> 88).
 *  - the explicit goto layout (loop / hit / body / elsepath) reproduces the target's basic-block
 *    ORDER: the `hit` block sits physically between the loop test and the loop body. A structured
 *    while/do-while emits the inverted layout (-3 ins, 39 diffs).
 *  - `register s32 flag __asm__("$17")` is a §17 pin. WITHOUT it gcc ties `arg1`->$s1 / `flag`->$s2,
 *    the reverse of the target (12 diffs, everything else already byte-exact). Pin-free attempts
 *    (declaring `flag` before `p`; assigning `flag` first in every case body) were both tried and
 *    do NOT flip the tie-break. The pin's live range does cross calls, so prefer ×1 banking.
 *  - func_80135480 must be declared INT-returning here: the target does NOT re-extend the callee's
 *    result before the switch (`addu $v1,$v0,$zero` only), while an s16-returning prototype costs a
 *    `sll/sra 16` pair. The two //@EDIT lines flip the in-TU definition s16->s32 and narrow its local
 *    `result` to s16 instead — the narrowing simply moves from the return-type conversion to the
 *    assignment, so the WHOLE TU compiles byte-identically (objdump-diffed: only the filename line
 *    changes). Both edits are required; flipping the return type alone drops func_80135480's tail
 *    `sll/sra` and shortens it by one instruction.
 */
extern s16 func_80135480(void*, s32, s16*, s16*);
extern s32 func_80135EB0(void *arg0, s32 arg1_);
extern s32 func_801345F8(s32 arg);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801F4DDC;
extern s32 D_801F4DFC;

s32 func_80135D20(s32 arg0, s32 arg1, u16 *arg2)
{
    u8 dead[96];
    u16 sp[3];
    s32 *p;
    register s32 flag __asm__("$17");
    s32 q;

    sp[0] = arg2[0];
    sp[1] = arg2[1] + 0x300;
    sp[2] = arg2[2];
    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, (s16 *)arg2, (s16 *)sp)) {
    case 0:
        return 0;
    case 1:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        q = arg0 + 0x34;
        p = &D_801F4DFC;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_801F4DDC;
        p = &D_801F4DFC;
        flag = 1;
        break;
    }
    if (arg1 >= 0) {
        goto elsepath;
    }
    if (func_80135EB0(p, 0) != 0) {
        goto hit;
    }
    p = (s32 *)*p;
    if (p == NULL) {
        return 0;
    }
    __asm__ __volatile__("");
loop:
    if (func_80135EB0(p, 0) == 0) {
        goto body;
    }
hit:
    func_80136A94(flag, arg0, (s32)arg2, q);
    return 1;
body:
    p = (s32 *)*p;
    if (p != NULL) {
        goto loop;
    }
    return 0;
elsepath:
    if (func_801345F8(arg1) != 0) {
        goto hit;
    }
    return 0;
}


// @class: struct
// @stuck: none — MATCH (289 ins). symcheck: only the cosmetic jtbl_801D81B8 floor (§8 carve).
//
// func_80135EB0 — h_seq family exemplar (x138 across the overlay fleet). Levers that made it:
//  1. m2 (the y-axis mask) MUST be the if/else form, NOT `m2=0x10; if (a8<=t3) m2=...`.
//     Both emit the same compact `bnez; li $s2,0x10` pair, but the pre-init form lets CSE carry
//     the D_8018A99C pointer load into the (m1|m2)==0 block; the if/else form ends the CSE
//     extended-BB so the block reloads `lui/lw D_8018A99C` (target does). Worth 2 ins + the whole
//     big-block register assignment.
//  2. Zero-byte `__asm__ __volatile__("")` fences in case 1 and case 2 (DIFFERENT templates, "" vs " ")
//     block gcc-2.7.2 cross_jump from folding those two bodies into case 6's second-call tail
//     (they are byte-identical to it; the target keeps all three copies). Worth 10 ins.
//  3. Zero-byte fences between the three big-block coordinate groups stop sched2 hoisting the next
//     group's `lhu` into the previous group's load-delay nop (restores 2 nops).
//  4. `D_801152AA = 0;` AFTER the h0 statement: it shortens the [6]-field temp's local-alloc live
//     range so c0 wins $v1 and the field temps take $v0/$a0 (target), not $v1/$v0.
//  5. case 4 reaches case 8's tail through a shared `L288` label using `w = x << 16` / `w >> 16`
//     so the shared block is exactly `sra $a1,$a1,16` — that is target's .L80136288. `w` pinned to
//     $a1 ($5); it never spans a jal so §74 does not apply.
//  6. arg1 copied into a $s3-pinned local — without it global-alloc gives arg1 $s2 and m2 $s3
//     (arg1 has more refs; target's priority order is arg0, sext-temp, m2, arg1).
//  7. `ret0:` sits between case 8 and case 10 and `done:`/`case 0:` after case 10 — that is the
//     target's basic-block order; reorg then produces the inline `move $v0,$zero` delay slots.

extern u8 D_80126720[];

extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 func_801365B8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32, s32, s32);

s32 func_80135EB0(void *arg0, s32 arg1_) {

    extern u8 D_8018A99C;
    extern u8 D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern s32 D_801150D8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    register s32 arg1 __asm__("$19") = arg1_;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 m1;
    s32 m2;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 n1;
    s32 n2;
    s32 r;
    s32 sv;
    register s32 w __asm__("$5");
    void *q;

    t1 = (*(s16 **)&D_8018A99C)[0];
    if (t1 < M2C_FIELD(arg0, s16 *, 4)) {
        m1 = 1;
    } else {
        m1 = (M2C_FIELD(arg0, s16 *, 6) < t1) << 1;
    }
    t2 = (*(s16 **)&D_8018A99C)[2];
    if (t2 < M2C_FIELD(arg0, s16 *, 0xC)) {
        m1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t2) {
        m1 |= 8;
    }
    t3 = (*(s16 **)&D_8018A99C)[1];
    if (t3 < M2C_FIELD(arg0, s16 *, 8)) {
        m2 = 0x10;
    } else {
        m2 = (M2C_FIELD(arg0, s16 *, 0xA) < t3) << 5;
    }
    if ((m1 | m2) == 0) {
        u16 *ac;
        s16 *b4;
        s32 c0;
        s32 c1;
        s32 h0;
        s32 h1;

        ac = *(u16 **)&D_8018A99C;
        b4 = D_8018A9A4;
        c0 = ac[0];
        b4[0] = c0;
        h0 = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
        D_801152AA = 0;
        (*(s16 *)D_80126720) = h0;
        (*(s16 *)D_801152A8) = c0 - h0;
        __asm__ __volatile__("");
        c1 = ac[2];
        b4[2] = c1;
        h1 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
        D_80126724 = h1;
        D_801152AC = c1 - h1;
        __asm__ __volatile__("");
        b4[1] = ac[1];
        D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
        VectorNormalSS(D_801152A8, D_801152A8);
        D_801150D8 |= 1;
        return 1;
    }

    t4 = (*(s16 **)&D_8018A9A0)[0];
    if (t4 < M2C_FIELD(arg0, s16 *, 4)) {
        n1 = 1;
    } else {
        n1 = (M2C_FIELD(arg0, s16 *, 6) < t4) << 1;
    }
    t5 = (*(s16 **)&D_8018A9A0)[2];
    if (t5 < M2C_FIELD(arg0, s16 *, 0xC)) {
        n1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t5) {
        n1 |= 8;
    }
    t6 = (*(s16 **)&D_8018A9A0)[1];
    if (t6 < M2C_FIELD(arg0, s16 *, 8)) {
        n2 = 0x10;
    } else {
        n2 = (M2C_FIELD(arg0, s16 *, 0xA) < t6) << 5;
    }
    if (((m1 | m2) & (n1 | n2)) != 0) {
        goto ret0;
    }
    {
        u16 *b0 = *(u16 **)&D_8018A9A0;
        u16 *ac = *(u16 **)&D_8018A99C;
        s16 *b8 = *(s16 **)&D_8018A9A8;

        b8[0] = b0[0] - ac[0];
        b8[1] = b0[1] - ac[1];
        b8[2] = b0[2] - ac[2];
    }

    switch (m1) {
    case 4:
        q = arg0;
        sv = M2C_FIELD(arg0, s16 *, 0xC);
        w = arg1 << 16;
        goto L288;
    case 1:
        r = func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4));
        __asm__ __volatile__("");
        goto done;
    case 2:
        r = func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6));
        __asm__ __volatile__(" ");
        goto done;
    case 5:
        if (func_80136334(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 0xC)) != 0) {
            return 1;
        }
        r = func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4));
        goto done;
    case 6:
        if (func_80136334(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 0xC)) != 0) {
            return 1;
        }
        r = func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6));
        goto done;
    case 9:
        if (func_801365B8(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 4)) != 0) {
            return 1;
        }
        /* fallthrough */
    case 8:
        q = arg0;
        sv = M2C_FIELD(arg0, s16 *, 0xE);
        w = (arg1 | 1) << 16;
    L288:
        r = func_80136334(q, w >> 16, sv);
        goto done;
    ret0:
        return 0;
    case 10:
        if (func_801365B8(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 6)) != 0) {
            return 1;
        }
        r = func_80136334(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 0xE));
    done:
        if (r != 0) {
            return 1;
        }
    case 0:
        if (m2 == 0) {
            goto ret0;
        }
        if (m2 == 0x10) {
            if (((s32 (*)(void *, s32, s32))func_80136824)(arg0, (s16) arg1, M2C_FIELD(arg0, s16 *, 8)) == 0) {
                goto ret0;
            }
        } else {
            if (((s32 (*)(void *, s32, s32))func_80136824)(arg0, (s16) (arg1 | 1), M2C_FIELD(arg0, s16 *, 0xA)) == 0) {
                goto ret0;
            }
        }
    default:
        return 1;
    }
}


s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    register s32 a1v __asm__("$11");
    register s32 a2v __asm__("$12");
    register s32 n __asm__("$5");
    register s16 *b4 __asm__("$7");
    s32 d;
    s32 dx;
    s32 denom;
    s32 result;
    s32 frame_pad[2];
    (void)&frame_pad;
    __asm__("" : "=r"(a1v) : "0"(arg1));
    a2v = arg2;

    if (!(arg1 & 1)) {
        dx = (s16) arg2 - (*(s16 **)&D_8018A99C)[2];
        d = dx;
        denom = -(*(s16 **)&D_8018A9A8)[2];
    } else {
        denom = (*(s16 **)&D_8018A9A8)[2];
        d = (*(s16 **)&D_8018A99C)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_8018A9A8;
        u16 *ac = *(u16 **)&D_8018A99C;
        b4 = D_8018A9A4;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_8018A9A0;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_8018A9A4[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_8018A9A4[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}



// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_8018A99C/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_8018A9A4 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    u16 *ac;
    s16 *b8;
    s16 *b4;
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s32 temp_a1;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;
    s32 a1c;
    s32 a2c;
    s32 cond;
    register u32 zr __asm__("$0");

    __asm__("addu %0,%1,$zero" : "=r"(a1c) : "r"(arg1));
    cond = arg1 & 1;
    a2c = arg2 + zr;
    if (!cond) {
        var_v1 = (s16) arg2 - (*(s16 **)&D_8018A99C)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_8018A9A8)[0];
    } else {
        var_a3 = (*(s16 **)&D_8018A9A8)[0];
        var_v1 = (*(s16 **)&D_8018A99C)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_8018A99C;
    b4 = D_8018A9A4;
    b8 = *(s16 **)&D_8018A9A8;
    b4[0] = ac[0] + var_a1;
    temp_a1 = -var_v1;
    b4[1] = ac[1] + (temp_a1 * b8[1]) / var_a3;
    temp_v0 = ac[2] + (temp_a1 * b8[2]) / var_a3;
    b4[2] = temp_v0;
    var_v0 = 0;
    if (temp_v0 < M2C_FIELD(arg0, s16 *, 0xC)) {
        return var_v0;
    }
    if (M2C_FIELD(arg0, s16 *, 0xE) < temp_v0) {
        return var_v0;
    }
    temp_v1 = b4[1];
    if (temp_v1 < M2C_FIELD(arg0, s16 *, 8)) {
        return var_v0;
    }
    if (M2C_FIELD(arg0, s16 *, 0xA) < temp_v1) {
        return var_v0;
    }
    __asm__("" :: "r"(a1c));
    __asm__("" :: "r"(a1c));
    if (a1c & 0x8000) {
        b4[1] = (s16) (*(u16 **)&D_8018A9A0)[1];
        b4[2] = (s16) (*(u16 **)&D_8018A9A0)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_8018A9A4, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_8018A9A4, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_8018A99C/B0/B8 are file-scope `extern u8`, D_8018A9A4 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_8018A9A4 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;

    register u16 *ac __asm__("$4");
    register s16 *b8 __asm__("$6");
    register s16 *b4 __asm__("$9");
    register s32 r __asm__("$3");
    register s32 pos __asm__("$12");
    register s32 a1v __asm__("$5");
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s16 var_v0_3;
    s32 temp_a1;
    s32 var_t0;
    s32 var_v1;
    s16 *b4b;
    u16 *p;

    __asm__ ("" : "=r"(a1v) : "0"(arg1));
    pos = arg2;
    if (!(a1v & 1)) {
        var_t0 = (s16) arg2 - (*(s16 **)&D_8018A99C)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_8018A9A8)[1];
    } else {
        var_a3 = (*(s16 **)&D_8018A9A8)[1];
        var_v1 = (*(s16 **)&D_8018A99C)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_8018A9A8);
    ac = (*(u16 **)&D_8018A99C);
    b4 = D_8018A9A4;
    temp_a1 = -var_v1;
    r = (temp_a1 * b8[0]) / var_a3;
    b4[0] = ac[0] + r;
    b4[1] = ac[1] + var_t0;
    r = (temp_a1 * b8[2]) / var_a3;
    temp_v0 = ac[2] + r;
    b4[2] = temp_v0;
    temp_v1 = b4[0];
    if (temp_v1 < M2C_FIELD(((void *)arg0), s16 *, 4)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 6) < temp_v1) {
        return 0;
    }
    if (temp_v0 < M2C_FIELD(((void *)arg0), s16 *, 0xC)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 0xE) < temp_v0) {
        return 0;
    }
    if (arg1 & 0x8000) {
        p = (*(u16 **)&D_8018A9A0);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_8018A9A4;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_8018A9A4;
        D_801152AA = -0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos - 2;
    }
    b4b[1] = var_v0_3;
    __asm__ __volatile__("" :: "r"(pos));
    (*(s16 *)D_80126720) = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 4) + M2C_FIELD(((void *)arg0), s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 8) + M2C_FIELD(((void *)arg0), s16 *, 0xA)) >> 1);
    D_80126724 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 0xC) + M2C_FIELD(((void *)arg0), s16 *, 0xE)) >> 1);
    return 1;
}



// @class: schedule
// @stuck: none — MATCH (76 ins, relocation-masked). Key lever: the D_80126720/22/24 tail is a
//   global-short RMW `+=`. Writing it via a cast `*(u16*)&SYM = *(u16*)&SYM + x` makes gcc CSE
//   the address into a base reg (base-reuse) for ALL three — but the target only base-reuses
//   D_80126720 (a SCHEDULER artifact: its addr-lui fills the load-delay slot after the pb4[4]
//   load, and since $v0 is live it lands in $a0, reused for load+store). D_80126722/24 use the
//   plain inline 2-lui form. Fix = DIRECT scalar RMW `SYM = SYM + x` (no &/cast) → inline %hi/%lo;
//   the scheduler alone forces base-reuse on #1. Also: `s16 D_80126724 = D_80126724 + int` emits
//   LHU (gcc-2.7.2 drops the sign-extend because the sum is truncated to 16b on the sh) — so the
//   canonical s16 decl is byte-safe here (no u16 retype needed, keeps the sign-sensitive callers).



s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern u8 D_801152A8[];
    extern u8 D_80126720[];
    extern s16 *D_8018A9A4;   /* holds a pointer value (*(u16**)&D_8018A9A4) */
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_8018A9A4, *(void **)&D_8018A9A4);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_8018A9A4;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}


DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136bc4 (src/shared) */


DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136c1c (src/shared) */


void func_80136C3C(void) {
}

void func_80136C44(void) {
}

void func_80136C4C(void) {
}



void func_80136C54(void)
{

    extern unsigned short D_800B99F0;
    extern void (*D_8018A9B8[])(void);
    D_8018A9B8[D_800B99F0]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_80136C90);

void func_80136D00(void) {
}

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136d08 (src/shared) */


DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136dfc (src/shared) */


void func_80136EC4(void) {
}

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ecc (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (match_one 61/61, relocation-masked)
//
// 2-line "X cross" GsSortLine family (same shape as byte-proven DEFINE_func_80137030 /
// DEFINE_func_80137178, RED variant):
//   line1 = (a0-3, a1-3) -> (a0+3, a1+3);  line2 = (a0+3, a1-3) -> (a0-3, a1+3);
//   color r=0xFF g=0 b=0.  All four endpoints are loop-invariant across the two calls, so all
//   six live values (x0,y0,x1,y1,white,base) are homed in $s0-$s5 for the whole body.
//
// Levers that make gcc-2.7.2 -O2 emit the target's exact regalloc + schedule:
//   * ROLE COALESCING (the 28 -> 13 step): the target coalesces x0 into a0's incoming copy
//     ($s1: `addu $s1,$a0,$zero` ... `addiu $s1,$s1,-0x3`) and y1 into a1's copy ($s2), while
//     x1 lands in a FRESH $s0. gcc coalesces whichever derived value is computed LAST off the
//     param, so the source must emit y0, x1, y1, x0 in that order — writing x0 first (the
//     "natural" order) coalesces x1 instead and costs 28 instructions.
//   * `__asm__("" : "=r"(x1) : "0"(x1))` right after `x1 = a0 + 3;` nails x1's compute point
//     between x1 and y1, which is what keeps x1 from being the last a0-user (13 -> 7).
//   * PINS: x1 -> $s0 ($16), x0 -> $s1 ($17), base(&D_800A6518) -> $s3 ($19), white(0xFF) ->
//     $s4 ($20). Without the x1 pin the whole $s bank rotates by one; without the x0 pin the
//     a0-copy fights x1 for $s0. y0/y1 must stay UNPINNED — pinning y1 to $s2 kills the
//     `addu $s2,$a1,$zero` param copy entirely (a1 stays in $a1, -1 insn, 58 mismatched).
//   * NO anchor on `white`: an `__asm__` on white front-loads its `li $s4,255` ahead of the
//     call's $a0/$a2 argument setup (the last 4-mismatch schedule residual). Leaving white
//     un-anchored lets the scheduler emit `addiu $a0,$sp,0x10` / `addu $a2,$zero,$zero` first,
//     exactly as the target does.
DEFINE_func_80136F3C()  /* dedup: shared engine-core @0x80136F3C (src/shared) */


DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (match_one 78/78, relocation-masked)
//
// 3-line GsSortLine family (same shape as byte-proven DEFINE_func_80137030), blue variant:
//   x0=a0-3, x1=a0+3 constant; y0: a1-3 -> a1+3 -> a1+3 ; y1: a1-3 -> a1-3 -> a1+3 ; color r=0 g=0 b=0xFF.
// Levers that make gcc-2.7.2 -O2 emit the target's exact regalloc + schedule:
//   * y0/y1 as two separate vars each reassigned in-place: a1 is clobbered by each call, so gcc is
//     forced to materialize a1-3 and a1+3 BEFORE call1. The surviving a1-3 (needed at line2.y1) is
//     preserved by a reload-inserted live-range split ($s5 -> $s4, the `addu $s4,$s5,$zero` copy) when
//     $s5 is reused for a1+3. Do NOT write an explicit copy (it front-loads as a real insn).
//   * pin x0->$s3, white(0xFF)->$s1, base(&D_800A6518)->$s2. Leave x1 UNPINNED: gcc naturally homes a0
//     in $s0 (prologue `addu $s0,$a0,$zero`) and computes x1=$s0+3 in place, landing x1 in $s0 and
//     scheduling it early (right after y0). Pinning x1, or any __asm__ touching x1, perturbs the
//     register pressure and destroys the fragile reload split (drops to 77 ins).
//   * the `__asm__("" : "=r"(x0) : "0"(x0))` anchor nails x0's compute point right after the three
//     initial computes (x0, y0, x1) so it schedules before the store/split block (16 -> 12 -> MATCH).







DEFINE_func_80137178()  /* dedup: shared engine-core @0x80137178 (src/shared) */


DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372b0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375ec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767c (src/shared) */


DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376c8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377b4 (src/shared) */


DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379d8 (src/shared) */


DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379ec (src/shared) */



// @class: regalloc-order (walker-family, §52/§52a) — PIN-FREE
// Role-swap ($s0<->$s2 between loop1 and loops2/3) is driven by DENSITY (K2), not pins:
//  - loop1 pointer has an extra ref (p != D_80127524 compare) -> wins $s0; index -> $s2
//  - loop2/3 index has >= pointer refs -> wins $s0; pointer -> $s2
// Separate per-loop pointer/index vars => separate pseudos => can take different regs.


DEFINE_func_801379FC()  /* dedup: shared engine-core @0x801379FC (src/shared) */




// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern void func_80138BE0(int p);

void func_80137B80(void) {

    extern s32 D_80127548[];
    extern int D_8018AA0C;
    extern int D_801269F0;
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8018AA0C += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137bd8 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.


extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{

    extern unsigned char D_80126A0E;
    extern short D_80126A0A;
    extern s16 D_801269F4;
    extern int D_800A5E60;
    extern int D_8018AA0C;
    extern int D_801269F0;
    unsigned char buf[3];

    D_800A5E60 = arg0;
    D_80126A0A = arg2;
    ((void (*)(void *, int, int))func_801392FC)(&D_801269F0, D_80126A0E, arg1);
    if ((*(short *)&D_801269F4) == 7) {
        buf[0] = 0x39;
        buf[1] = 0xFF;
        buf[2] = 0x71;
        ((void (*)(void *, void *, int))func_80137DD4)(&D_801269F0, buf, arg1);
    } else if ((*(short *)&D_801269F4) == 3) {
        if (D_8018AA0C & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137DD4 (src/shared) */

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137fd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_801380E0);

/* de-macroized: per-overlay-local decl for func_80138DE0 (byte-true sig); do NOT re-macroize */
    void func_801387B8(s32 arg0) {
        extern s32 func_80138DE0(u8*, u8, s32);
        extern s32 func_80139220(s32 a0);
        extern void func_80138948(void *a0);
        extern void func_80139A8C(s32 a0);
        extern void func_80139B18(s32 a0);
        extern s32 D_80127530[];
        u16 *p;
        s32 base;
        s32 cont;
        u8 cmd;
        s32 sub;
        s32 pc;
        for (;;) {
            cont = 0;
            if (*(s32 *)(arg0 + 8) & 0x400) {
                base = D_80127530[*(u16 *)(arg0 + 0x4A)];
                p = (u16 *)(arg0 + 0x44);
            } else {
                p = (u16 *)(arg0 + 0x10);
                base = *(s32 *)(arg0 + 0);
            }
            pc = *p;
            cmd = *(u8 *)(base + pc);
            sub = *(u8 *)(base + pc + 1);
            if (cmd >= 0x20) {
                cont = func_80138DE0(arg0, cmd, sub);
                if (!(*(s32 *)(arg0 + 8) & 0x80220)) {
                    cont = 0;
                }
            } else {
                if (cmd != 0) {
                    switch (cmd) {
                    case 10:
                        func_80139220(arg0);
                        *p += 1;
                        goto loop_end;
                    case 1:
                        cont = 1;
                        *(u8 *)(arg0 + 0x23) = sub;
                        *p += 2;
                        goto loop_end;
                    case 7:
                        if (!(*(s32 *)(arg0 + 8) & 0x20000)) {
                            *(s32 *)(arg0 + 8) &= ~0x20;
                        }
                        break;
                    case 23:
                        *(s32 *)(arg0 + 8) |= 2;
                    default:
                        cont = 1;
                        *p += 1;
                        goto loop_end;
                    }
                }
                func_80138948((void *)arg0);
            }
        loop_end:
            if (cont == 0) {
                func_80139A8C(arg0);
                func_80139B18(arg0);
                return;
            }
        }
    }  /* dedup: shared engine-core @0x801387B8 (src/shared) */

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */


DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895c (src/shared) */


/* de-macroized: per-overlay-local decl for func_80138DE0 (byte-true sig); do NOT re-macroize */
    extern s16 D_80127540[4];
    extern s32 func_80139D04(s32 a0, s32 a1);
    extern s32 func_80138DE0(u8*, u8, s32);
    extern void func_80139B18(s32 a0);
    void func_80138AB4(s32 a0) {
        u8 sp10[8];
        s32 s0 = a0;
        s32 s1;
        s32 a0v;
        s1 = func_80139D04((s32)sp10, (u16)D_80127540[*(u16 *)(s0 + 0x48)]) & 0xFFFF;
        do {
            s32 v1 = *(u16 *)(s0 + 0x44);
            a0v = 0;
            if ((s32)v1 < s1) {
                s32 a1v = (sp10[v1] + 0x30) & 0xFF;
                a0v = func_80138DE0(s0, a1v, 0);
                if (*(s32 *)(s0 + 0x8) & 0x80220) {
                    /* a0v stays */
                } else {
                    a0v = 0;
                }
            } else {
                s32 t = *(u16 *)(s0 + 0x48);
                if ((u32)t < 3) {
                    *(s16 *)(s0 + 0x48) = t + 1;
                }
                *(s16 *)(s0 + 0x4) = 2;
            }
        } while (a0v != 0);
        func_80139B18(s0);
    }  /* dedup: shared engine-core @0x80138ab4 (src/shared) */


DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138b88 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)


void func_80138BE0(int p)
{

    extern void (*D_8018AA10[])(void);
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_8018AA10[*(short *)(p + 4)]();
}


void func_80138C30(void *a0) {
    if (*(s16 *)((s32)a0 + 4) == 4) {
        *(s16 *)((s32)a0 + 4) = 2;
    } else {
        *(u32 *)((s32)a0 + 8) |= 0x800;
    }
}


extern s32 func_80139BE0(s32);

s32 func_80138C60(s32 arg0)
{
    typedef struct {
        u8 b0;
        u8 b1;
        u8 b2;
        u8 b3;
    } Q_80138C60;
    extern Q_80138C60 D_8018A9DC[];
    u16 t;
    u8 b;
    s32 f;
    s32 idx;

    if (*(s32 *)(arg0 + 8) & 0x2000) {
        return 1;
    }

    t = *(u8 *)(arg0 + 0x22) & 7;
    *(s16 *)(arg0 + 0x18) = t;
    if (t < 2) {
        *(u8 *)(arg0 + 0x20) = 0;
    }

    f = *(s32 *)(arg0 + 8);
    if (f & 0x40) {
        *(u8 *)(arg0 + 0x22) = (*(u8 *)(arg0 + 0x22) & 0x67) | (f & ~0x67);
    }

    b = *(u8 *)(arg0 + 0x22);
    if (b & 0x80) {
        idx = (b & 0x18) >> 3;
    } else {
        idx = (b & 0x78) >> 3;
        if (b & 0x60) {
            *(s16 *)(arg0 + 0x1C) = 0;
        }
    }

    *(Q_80138C60 *)(arg0 + 0x24) = D_8018A9DC[idx];

    func_80139BE0(arg0);
    func_80139C7C((u8 *)arg0);
    return func_8013A8FC(arg0);
}


DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138d58 (src/shared) */


DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138db8 (src/shared) */


// @class: struct
// @stuck: none — MATCH
/* func_80138DE0 — advance the text cursor by 1 or 2 after emitting a glyph.
 *
 * Key levers (both required; the body itself is a plain if/else-if):
 *  - D_80127548 MUST be declared as an ARRAY (`extern s32 D_80127548[];`) and accessed as
 *    D_80127548[0].  As a scalar, gcc emits the assembler-macro form twice in the tail
 *    (lui+lw %lo / lui+sw %lo via $at, 8 insns); as an array the address is materialised once
 *    (la $v1 = lui+addiu) and the lw/sw use 0($v1), which is what the target does and is one
 *    instruction shorter.  This is the §40b indexed-global idiom, and it is also the form the
 *    shared engine-core macro DEFINE_func_80138ED0() already uses for this same symbol.
 *  - arg1 is a byte param (u8): each use re-emits `andi ...,0xFF` (§I2), which is why the
 *    0x20-subtraction path recomputes the mask instead of reusing $v1.
 *  - The 2nd argument of func_80138ED0 is u32, so the (u16) cast supplies the `andi 0xFFFF`.
 *  - The `if (arg2 != 0) return 0;` tail check is redundant on the two call paths; gcc's
 *    thread_jumps folds them straight to the return-0 tails (.L80138EB8 / .L80138EBC), and the
 *    `*p = ...` store is cross-jumped between the +2 and +1 arms.
 */
#include "common.h"

extern s32 D_80127548[];
extern u8 D_800D3AB4[];
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);

s32 func_80138DE0(u8 *arg0, u8 arg1, s32 arg2) {
    u16 *p;

    if (D_80127548[0] == 0) {
        return 0;
    }
    p = (u16 *)(arg0 + 0x44);
    if ((*(u32 *)(arg0 + 8) & 0x400) == 0) {
        p = (u16 *)(arg0 + 0x10);
        if (*(s16 *)(arg0 + 4) == 8) {
            p = (u16 *)(arg0 + 0x44);
        }
    }
    if (arg1 >= 0xE0) {
        arg2 = func_80138ED0(arg0, 0x1F, D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 2;
    } else if (arg1 >= 0x20) {
        arg2 = func_80138ED0(arg0, (u16)(arg1 - 0x20), D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 1;
    }
    if (arg2 != 0) {
        return 0;
    }
    D_80127548[0] = D_80127548[0] - 1;
    return D_80127548[0];
}


DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ed0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914c (src/shared) */


DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391f0 (src/shared) */


DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */


DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392c8 (src/shared) */


DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392fc (src/shared) */


DEFINE_func_801395D4()  /* dedup: shared engine-core @0x801395D4 (src/shared) */

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */



extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{

    extern short D_800B9A02;
    extern u8 D_800A6518[];
    extern u8 D_8018AA54;
    extern u8 D_8018AA98;
    register u8 *e __asm__("$7");
    register s32 off __asm__("$4");
    s32 buf[12];
    u8 *b164;
    u8 *b1A8;
    s32 sc;
    s32 t2;
    s32 t0;
    s32 hi;
    s32 lo;
    s32 uu;
    s32 vv;

    e = (u8 *)arg0;
    b164 = (u8 *)&D_8018AA54;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_8018AA98 + off;
    *(s16 *)((u8 *)buf + 0x10) = *(u16 *)(b1A8 + 0);
    *(s16 *)((u8 *)buf + 0x12) = *(u16 *)(b1A8 + 2);
    *(u8 *)((u8 *)buf + 0x16) = 0x80;
    *(u8 *)((u8 *)buf + 0x15) = 0x80;
    *(u8 *)((u8 *)buf + 0x14) = 0x80;
    *(s16 *)((u8 *)buf + 0x06) = *(u16 *)(e + 0x32);
    *(s16 *)((u8 *)buf + 0x08) = 0x20;
    *(s16 *)((u8 *)buf + 0x0A) = 0x28;

    uu = (*(u16 *)(b164 + 0) & 0x3F) << 2;
    *(u8 *)((u8 *)buf + 0x0E) = uu;
    vv = *(u16 *)(b164 + 2);
    *(u8 *)((u8 *)buf + 0x0F) = vv;

    if (*(u8 *)(e + 0x22) & 8) {
        *(s16 *)((u8 *)buf + 0x04) =
            *(u16 *)(e + 0x30) + *(u16 *)(e + 0x34) + 0x28;
        sc = -*(u16 *)(e + 0x28);
    } else {
        *(s16 *)((u8 *)buf + 0x04) = *(u16 *)(e + 0x30) - 0x28;
        sc = *(u16 *)(e + 0x28);
    }
    *(s16 *)((u8 *)buf + 0x1C) = sc;
    *(s16 *)((u8 *)buf + 0x1E) = *(u16 *)(e + 0x2A);
    *(s16 *)((u8 *)buf + 0x1A) = 0;
    *(s16 *)((u8 *)buf + 0x18) = 0;
    *(s32 *)((u8 *)buf + 0x20) = 0;

    GsSortSprite(buf, &D_800A6518[(u16)D_800B9A02 * 20],
                 *(u16 *)(e + 0x1A));
}


DEFINE_func_80139914()  /* dedup: shared engine-core @0x80139914 (src/shared) */


DEFINE_func_80139954()  /* dedup: shared engine-core @0x80139954 (src/shared) */


DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399a8 (src/shared) */


DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399f0 (src/shared) */


DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139a34 (src/shared) */


DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139a44 (src/shared) */


DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139a68 (src/shared) */


DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139a8c (src/shared) */


DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139b18 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139c7c (src/shared) */


DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139d04 (src/shared) */


DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139dc8 (src/shared) */


void func_80139DEC(void) {
}

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139df4 (src/shared) */


DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139e84 (src/shared) */


DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139f0c (src/shared) */


DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139fbc (src/shared) */


DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139fe8 (src/shared) */


DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013a0a4 (src/shared) */


DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013a164 (src/shared) */


DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013a1e8 (src/shared) */


DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013a250 (src/shared) */


DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013a2bc (src/shared) */


void func_8013A378(void) {
}

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013a380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013a448 (src/shared) */


DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013a4c4 (src/shared) */


DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013a530 (src/shared) */


DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013a860 (src/shared) */


DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013a8b0 (src/shared) */


DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013a8bc (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013a8fc (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013a9b4 (src/shared) */


DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013a9f8 (src/shared) */


DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013aa24 (src/shared) */


extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern void func_8013AF20();
s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_800A5E60;
    u8 buf[0xE4];          /* spans 0x10 .. 0xF4 */
    s32 neg;
    s32 a, b;
    s32 t4, t6;
    t4 = *(s16 *)(a2 + 4) * 12;
    *(s16 *)(buf + 0xE0) = t4 + 0x10;   /* sp+0xF0 */
    neg = a3 & 0x8000;
    t6 = *(s16 *)(a2 + 6) * 12 + (*(s16 *)(a2 + 6) - 1) * 2;
    *(s16 *)(buf + 0xE2) = t6 + 8;
    if (neg == 0) {
        *(s16 *)(buf + 0xE0) = t4 + 0x38;
        *(s16 *)(buf + 0xE2) = t6 + 0x10;
    }
    a = ((s32)*(s16 *)(buf + 0xE0) << 12) / 154;
    b = ((s32)*(s16 *)(buf + 0xE2) << 12) / 42;
    *(s16 *)(buf + 0xE0) = a;
    *(s16 *)(buf + 0xE2) = b;
    if (neg != 0) {
        *(s16 *)(buf + 0xE0) = -a;
    }
    *(s16 *)(buf + 0xC8) = b;          /* 0xD8 */
    *(s16 *)(buf + 0xC2) = 0;          /* 0xD2 */
    *(s16 *)(buf + 0xC4) = 0;          /* 0xD4 */
    *(s16 *)(buf + 0xC6) = 0;          /* 0xD6 */
    *(s16 *)(buf + 0xCA) = 0;          /* 0xDA */
    *(s16 *)(buf + 0xCC) = 0;          /* 0xDC */
    *(s16 *)(buf + 0xCE) = 0;          /* 0xDE */
    *(s16 *)(buf + 0xD0) = 0x1000;     /* 0xE0 */
    *(s16 *)(buf + 0xC0) = *(u16 *)(buf + 0xE0);   /* 0xD0 */
    *(s32 *)(buf + 0xD4) = *(s16 *)(a2 + 0);       /* 0xE4 */
    *(s32 *)(buf + 0xD8) = *(s16 *)(a2 + 2);       /* 0xE8 */
    *(s32 *)(buf + 0xDC) = 0;                       /* 0xEC */
    __asm__ __volatile__("" ::: "memory");
    {
        register s32 *p __asm__("$2") = (s32 *)(buf + 0xC0);
        __asm__ __volatile__(
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
            "lw $12, 20(%0)\n"
            "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n"
            "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n"
            "ctc2 $14, $7\n"
            : : "r"(p) : "$12", "$13", "$14", "memory");
    }
    func_8013AD38(buf + 0xE0, 0, buf + 0x00, buf + 0x80);
    D_800A5E60 = a0;
    if (a3 != 0) {
        func_8013B274(a1, 0x80, buf + 0xE0);
    }
    func_8013AF20(a1, a2, buf + 0x00, buf + 0x80);
    return D_800A5E60;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013AD38);

DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013af20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013b204 (src/shared) */




extern void *func_80010A08(s32);

void func_8013B274(s32 a0, s32 a1, void *a2)
{

    extern s16 D_8018AB54, D_8018AB56, D_8018AB58, D_8018AB5A, D_8018AB5C, D_8018AB5E;
    extern u16 D_800D45F6;
    u8 *p;
    s32 L[10];
    s16 sa;
    s32 quot;
    s16 ang;

    p = (u8 *)func_80010A08(0x28);
    p[3] = 9;
    p[7] = 0x2C;
    p[4] = 0x80;
    p[5] = 0x80;
    p[6] = 0x80;
    *(s16 *)(p + 0x16) = 0x37;
    *(s16 *)(p + 0xE) = 0x6FD6;
    p[0xC] = 0xE0;
    p[0xD] = 0;
    p[0x14] = 0xEF;
    p[0x15] = 0;
    p[0x1C] = 0xE0;
    p[0x1D] = 0xF;
    p[0x24] = 0xEF;
    p[0x25] = 0xF;

    sa = (s16)a1;
    if (sa == 0) {
        *(s16 *)L = 0;
    } else {
        quot = ((s32)sa << 12) / ((s16*)a2)[0];
        ang = (s16)quot;
        if (!(D_8018AB56 < ang)) goto outer_else;
        if (!(ang < D_8018AB5C)) goto inner_else;
        if (ang < D_8018AB58) { *(s16 *)L = D_8018AB58; goto done; }
        if (D_8018AB5A < ang) { *(s16 *)L = D_8018AB5A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_8018AB54) { *(s16 *)L = D_8018AB54; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8018AB5E < ang) { *(s16 *)L = D_8018AB5E; goto done; }
        *(s16 *)L = quot;
    done: ;
    }
    *(s16 *)((u8 *)L + 2) = D_800D45F6;

    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(L) : "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n"
        "swc2 $26, 4(%0)\n"
        "swc2 $27, 8(%0)\n"
        : : "r"((u8 *)L + 8) : "memory");

    if (((s16*)a2)[1] > 0)
        *(s32 *)((u8 *)L + 0xC) -= 1;
    else
        *(s32 *)((u8 *)L + 0xC) += 2;

    *(s16 *)L = 9;
    *(s16 *)((u8 *)L + 2) = 9;
    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 3, 0\n"
        : : "r"(L) : "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n"
        "swc2 $26, 4(%0)\n"
        "swc2 $27, 8(%0)\n"
        : : "r"((u8 *)L + 0x18) : "memory");

    *(s16 *)(p + 8) = *(volatile s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0xA) = *(volatile s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x10) = *(volatile s32 *)((u8 *)L + 8) + *(volatile s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x12) = *(volatile s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x18) = *(volatile s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0x1A) = *(volatile s32 *)((u8 *)L + 0xC) + *(volatile s32 *)((u8 *)L + 0x1C);
    *(s16 *)(p + 0x20) = *(volatile s32 *)((u8 *)L + 8) + *(volatile s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x22) = *(volatile s32 *)((u8 *)L + 0xC) + *(volatile s32 *)((u8 *)L + 0x1C);

    ((P_TAG *)p)->addr = ((P_TAG *)a0)->addr;
    ((P_TAG *)a0)->addr = (u32)p;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B568);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B598);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013B83C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013BD34);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013BD74);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C08C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C360);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C414);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C938);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C964);


extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801F4E40;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801F4E40, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013C9C4);


void func_8013CA14(void)
{

    extern s32 D_801F4E40;
    extern s8 D_801F4E44;
    extern s8 D_801F4E45;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801F4E40;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801F4E45;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801F4E44)) * 2) + D_801F4E40);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801F4E45 = (unsigned char) p[1];
      D_801F4E44 = D_801F4E44 + 1;
      if (D_801F4E45 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801F4E44 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801F4E45 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801F4E64;
    extern s32 D_801F4E58;
    extern s32 D_801F4E5C;
    extern s32 D_801F4E68;
    D_801F4E64 = 1;
    D_801F4E58 = 1;
    D_801F4E5C = 0;
    D_801F4E68 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801F4E58;
    extern s32 D_801F4E5C;
    extern s32 D_801F4E60;
    extern s32 D_801F4E64;
    extern s32 D_801F4E68;
    D_801F4E58 = 1;
    D_801F4E64 = 0;
    D_801F4E5C = 0;
    D_801F4E60 = -1;
    D_801F4E68 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801F4E64;
    extern s32 D_801F4E68;
    extern s32 D_801F4E90;
    extern s32 D_801F4E94;
    D_801F4E90 = D_801F4E68;
    D_801F4E94 = D_801F4E64;
    D_801F4E68 = 1;
    D_801F4E64 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801F4E90;
    extern s32 D_801F4E94;
    extern s32 D_801F4E68;
    extern s32 D_801F4E64;
    D_801F4E68 = D_801F4E90;
    D_801F4E64 = D_801F4E94;
}




extern s16 currentLocationId;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_801F4E68;
    extern s32 D_801F4E60;
    extern s32 D_801F4E64;
    extern s32 D_801F4E58;
    extern s32 D_801F4E5C;
    extern s32 D_801F4E6C;
    extern s32 D_801F4E78;
    extern s32 D_801F4E80;
    extern s32 D_801F62E0;
    extern s32 D_801F6260;
    extern s32 D_801F6254[];
    extern u8 D_801F6221;
    extern u8 D_801F636E;
    extern u8 D_801F62DC;
    extern Rec12 D_8018AD74[];
    extern Rec9 D_8018AD3C[];
    extern u8 D_801F62B8;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801F62E0 = 0;
    if (D_801F4E68 == 0 && s0 != D_801F4E60) {
        ta = D_8018AD74[s0].a;
        tb = D_8018AD74[s0].b;
        tc = D_8018AD74[s0].c;
        D_801F4E60 = s0;
        D_801F6221 = tc;
        D_801F636E = ta;
        D_801F62DC = tb;
        *(Rec9 *)&D_801F62B8 = D_8018AD3C[s0];
        D_801F4E64 = 1;
        D_801F4E58 = 1;
        if (D_801F4E78 & 2) {
            if (s0 == 4) { D_801F6254[0] = 0x100; D_801F6260 = 0x80; }
            if (s0 == 0) { D_801F6254[0] = 0x100; D_801F6260 = 0; }
        }
    }
    if (D_801F4E64 != 0) {
        t = D_801F4E58 - 1;
        D_801F4E58 = t;
        if (t == 0) {
            if (D_801F4E68 == 0) {
                if ((D_801F4E78 & 2) && s0 == 4) {
                    if (D_801F4E80 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801F4E80 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801F4E58 = 2;
                if (D_801F4E64 != 0) {
                    if (D_801F4E78 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801F6260;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801F6260;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801F4E78 & 2) {
                    if (s0 == 4) D_801F6260 = 0;
                    if (s0 == 0) D_801F6260 = 0x80;
                }
            } else {
                if (D_801F4E80 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801F4E58 = 1;
            }
        }
    }
    D_801F4E6C = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801F4E64 != 0) D_801F4E6C = D_801F4E5C;
            else D_801F4E6C = 0x1F;
        } else if (s0 == 4) {
            if (D_801F4E64 != 0) D_801F4E6C = 0x1F - D_801F4E5C;
            else D_801F4E6C = 0;
        }
    }
}




void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801F6218;
    extern u8 D_801F6219;
    extern u8 D_801F621A;
    extern u8 D_801F621B;
    extern u8 D_801F621C;
    extern u8 D_801F621D;
    extern u8 D_801F621E;
    extern u8 D_801F621F;
    extern u8 D_801F6220;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801F6218; t1 = D_801F6219; t2 = D_801F621A;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801F621B; t1 = D_801F621C; t2 = D_801F621D;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801F621E; t1 = D_801F621F; t2 = D_801F6220;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern void func_8013D9B0();

void func_8013D064(void)
{

    extern s32 D_801F4E70;
    extern s32 D_801F4E58;
    extern s32 D_801F4E74;
    extern s32 D_801F4E64;
    if (D_801F4E70 != 0) {
        if (D_801F4E70 != 2) {
            if (((D_801F4E70 < 3) && (D_801F4E70 == 1)) &&
                (D_801F4E74 = D_801F4E74 + 1, 0x23a < D_801F4E74)) {
                D_801F4E58 = D_801F4E70;
                D_801F4E70 = 2;
            }
        } else {
            D_801F4E58 = D_801F4E58 + -1;
            if (D_801F4E58 == 0) {
                D_801F4E58 = D_801F4E70;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801F4E64 == 0) {
                    D_801F4E70 = D_801F4E70 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801F4E64;
    func_8013D9B0();
    return D_801F4E64;
}




void func_8013D164(void) {

    extern s32 D_801F4E70;
    D_801F4E70 = 1;
}



void func_8013D178(void) {

    extern u8 D_801F6218;
    extern u8 D_801F6219;
    extern u8 D_801F621A;
    extern u8 D_801F621B;
    extern u8 D_801F621C;
    extern u8 D_801F621D;
    extern u8 D_801F621E;
    extern u8 D_801F621F;
    extern u8 D_801F6220;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801F6218; v = *p; t = D_801F62B8;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F6219; v = *p; t = D_801F62B9;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621A; v = *p; t = D_801F62BA;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621B; v = *p; t = D_801F62BB;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621C; v = *p; t = D_801F62BC;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621D; v = *p; t = D_801F62BD;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621E; v = *p; t = D_801F62BE;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621F; v = *p; t = D_801F62BF;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F6220; v = *p; t = D_801F62C0;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801F62FA;
    extern u8 D_801F636E;
    extern u8 D_801F6222;
    extern u8 D_801F62DC;
    extern u8 D_801F6200;
    extern u8 D_801F6221;
    extern s32 D_801F62E0;
    if ((D_801F62FA & 0xff) != D_801F636E) {
        D_801F62FA = ((D_801F62FA & 0xff) < D_801F636E) ? (D_801F62FA + 1) : (D_801F62FA - 1);
    }
    if ((D_801F6222 & 0xff) != D_801F62DC) {
        D_801F6222 = ((D_801F6222 & 0xff) < D_801F62DC) ? (D_801F6222 + 1) : (D_801F6222 - 1);
    }
    if ((D_801F6200 & 0xff) != D_801F6221) {
        D_801F6200 = ((D_801F6200 & 0xff) < D_801F6221) ? (D_801F6200 + 1) : (D_801F6200 - 1);
    }
    D_801F62E0 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C();
extern void func_8013DD68();
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801F4E48;
    extern void *D_801F4E4C;
    extern void *D_801F4E50;
    extern s32 D_801F4E78;
    extern s32 D_801F4E7C;
    extern s32 D_801F4E80;
    extern s32 D_801F6254[];
    extern u8 D_8018AC4C[];
    extern u8 D_8018ACF4[];
    extern u8 D_8018ABA4[];
    extern u8 D_8018ACA0[];
    extern u8 D_8018AD20[];
    extern u8 D_8018ABF8[];
    u8 *p = D_80078E78;

    D_801F4E78 = param_2;
    D_801F4E7C = (param_2 >> 2) & 3;
    D_801F4E80 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801F4E48 = D_8018AC4C;
        D_801F4E4C = D_8018ACF4;
        D_801F4E50 = D_8018ABA4;
    } else {
        D_801F4E48 = D_8018ACA0;
        D_801F4E4C = D_8018AD20;
        D_801F4E50 = D_8018ABF8;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801F4E80 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801F4E78 & 2) != 0) {
            D_801F6254[0] = 0x140;
            D_801F6254[3] = 0x80;
            if (p[0x37] == 4) {
                D_801F6254[0] = 0x140;
                D_801F6254[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801F6254[0] = 0x140;
                D_801F6254[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */








void func_8013D53C(void *arg0v) {

    extern Rec9 D_8018AD3C[];
    extern Rec12 D_8018AD74[];
    extern s32 D_801F4E78;
    extern u8 D_80078EAF;
    extern s32 D_801F4E60;
    extern u8 D_801F62FA;
    extern u8 D_801F636E;
    extern u8 D_801F6222;
    extern u8 D_801F62DC;
    extern u8 D_801F6200;
    extern u8 D_801F6221;
    extern u8 D_801F62B8;
    extern s32 D_801F62E0;
    extern s32 D_801F4E74;
    extern s32 D_801F4E70;
    extern s32 D_801F4E6C;
    extern s32 D_801F4E58;
    extern s32 D_801F4E64;
    extern s32 D_801F4E68;
    extern void *D_801F4E48;
    extern s32 D_801F4E80;
    extern void *D_801F4E50;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_8018AD78[];
    extern u8 D_8018AD7C[];
    extern unsigned char D_801F6218;
    extern s16 *D_801F4E54;
    extern s32 D_801F4E84;
    extern s32 D_801F4E88;
    extern s32 D_801F4E8C;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_801F4E78 & 1)) {
        D_801F4E60 = 1;
    } else {
        D_801F4E60 = D_80078EAF;
    }

    b0 = ((u8 *)D_8018AD74)[D_801F4E60 * 12];
    D_801F62FA = b0;
    D_801F636E = b0;
    b1 = D_8018AD78[D_801F4E60 * 12];
    D_801F6222 = b1;
    D_801F62DC = b1;
    b2 = D_8018AD7C[D_801F4E60 * 12];
    D_801F6200 = b2;
    D_801F6221 = b2;

    (*(S9 *)&D_801F6218) = ((S9 *)D_8018AD3C)[D_801F4E60];
    (*(S9 *)&D_801F62B8) = *(S9 *)(&D_801F6200 + 0x18);  /* same addr as (*(S9 *)&D_801F6218); distinct sym defeats cse, keeps %hi/%lo */

    D_801F62E0 = 1;
    D_801F4E74 = -1;
    D_801F4E70 = 0;
    D_801F4E6C = -1;
    D_801F4E58 = 0;
    D_801F4E64 = 0;
    D_801F4E68 = 0;

    if ((D_801F4E78 & 2) && (D_801F4E60 == 4)) {
        s0v = (*(s32 * *)&D_801F4E48)[18];
        t9v = (*(s32 * *)&D_801F4E48)[19];
        t8v = (*(s32 * *)&D_801F4E48)[20];
    } else {
        s32 *p = (s32 *)(D_801F4E60 * 12 + (s32) (*(s32 * *)&D_801F4E48));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_801F4E54) = arg0;
    if (arg0 != 0) {
        if (D_801F4E80 != 0) {
            s32 *p = (s32 *)(D_801F4E60 * 12 + (s32) (*(s32 * *)&D_801F4E50));
            D_801F4E84 = p[0];
            D_801F4E88 = p[1];
            D_801F4E8C = p[2];
        } else {
            while ((arg0->cmd & 0xFFFF) != 0xFF) {
                if ((arg0->cmd & 0xFFFF) == 9) {
                    s32 n;
                    s32 i;
                    u16 *src;
                    u16 *dst;
                    n = arg0->w * arg0->h;
                    i = 0;
                    src = arg0->data;
                    __asm__("" :: "r"(src));  /* +2 refs on src (depth-2): keeps src above i, below the mfhi temp */
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            __asm__("" :: "r"(i));  /* +3 refs on i (depth-3): lifts i over dst in the $t2 race */
                            px = *src;
                            r = ((px & 0x1F) * s0v) / 2560;
                            g = (((px & 0x3E0) * t9v) / 2560) & 0x3E0;
                            b = (((px & 0x7C00) * t8v) / 2560) & 0x7C00;
                            out = r | g | b | (px & 0x8000);
                            if (out == 0 && px != 0) {
                                out = 0x8000;
                            }
                            *dst = out;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                }
                arg0++;
            }
        }
    }
}








extern void func_800599B8(u16*);

void func_8013D8FC(void)
{

    extern s16 *D_801F4E54;
    register s16 *psVar3 __asm__("$17");
    register s16 *psVar2 __asm__("$16");
    register s32 c9 __asm__("$19");
    register s32 cff __asm__("$18");
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_801F4E54;
    if (psVar3 != (s16 *)0x0 && (sVar1 = (u16)*psVar3, sVar1 != 0xff)) {
        c9 = 9;
        cff = 0xff;
        psVar2 = psVar3 + 5;
        do {
            if (sVar1 == c9) {
                s32 arg2 = *(s32 *)(psVar2 + 1) + psVar2[-1] * 2;
                buf[0] = psVar2[-3];
                buf[1] = psVar2[-2];
                buf[2] = psVar2[-1];
                buf[3] = *psVar2;
                ((void (*)(s32, s32))func_800599B8)((s32)buf, arg2);
            }
            psVar3 = psVar3 + 8;
            sVar1 = (u16)*psVar3;
            psVar2 = psVar2 + 8;
        } while (sVar1 != cff);
    }
}


extern void func_800599B8(u16*);
#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{

    extern void *D_801F4E4C;
    extern s16 *D_801F4E54;
    extern s32 D_801F4E64;
    extern s32 D_801F4E6C;
    u8 buf[0x20];
    register s32 uVar13 __asm__("$16");
    register u16 *psVar14 __asm__("$17");
    register u16 *psVar15 __asm__("$18");
    register s32 uVar16 __asm__("$19");
    register void *r0 __asm__("$20");
    register u16 *puVar10 __asm__("$11");
    register u16 *puVar9 __asm__("$10");
    register s32 iVar11 __asm__("$13");
    register s32 iVar12 __asm__("$14");
    u16 sVar4;
    register u32 uVar5 __asm__("$3");
    register u32 uVar7 __asm__("$6");
    register u32 uVar1 __asm__("$7");
    register u32 uVar6 __asm__("$4");
    register u32 uVar8 __asm__("$8");
    register u32 uVar3 __asm__("$9");

    psVar15 = (*(u16 * *)&D_801F4E54);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801F4E4C)[param_1];
        D_801F4E6C = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];
                        register s32 mh __asm__("$2") = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;
                        register u16 *pi __asm__("$5");
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");
                            register u32 out __asm__("$2");
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");
                                register void *pb __asm__("$12");
                                __asm__ __volatile__("");
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                                c = (s32)uVar3 < (s32)uVar1;
                                if (c) uVar1 = uVar1 - 0x400;
                            }
                            result = uVar5 | uVar7 | uVar1 | (*(u32 *)(buf + 0xc) & 0x8000);
                            if (result == 0 && *(u32 *)(buf + 0xc) != 0) {
                                result = 0x8000;
                            }
                            *puVar9 = (u16)result;
                            puVar9 = puVar9 + 1;
                            iVar11 = iVar11 + 1;
                            puVar10 = puVar10 + 1;
                        } while (iVar11 < iVar12);
                    }
                    if (uVar13 != 0) {
                        ((void (*)(void *))func_800599B8)(buf);
                    }
                    uVar16 = uVar16 | uVar13;
                }
                psVar15 = psVar15 + 8;
                sVar4 = *psVar15;
                psVar14 = psVar14 + 8;
            } while (sVar4 != 0xff);
        }
        D_801F4E64 = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801F4E50)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68();

void func_8013DBE4(int param_1)
{

    extern void *D_801F4E50;
    extern s16 *D_801F4E54;
    extern s32 D_801F4E64;
    extern s32 D_801F4E84;
    extern s32 D_801F4E88;
    extern s32 D_801F4E8C;
    int *p;
    int x, y, z;
    int flag;

    if (D_801F4E54 != 0) {
        D_801F4E64 = 0;
        p = (int *)(param_1 * 12 + (int)D_801F4E50);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801F4E84 != x) {
            flag = 1;
            if (D_801F4E84 < x) {
                if (x - D_801F4E84 < 5) {
                    D_801F4E84 = x;
                } else {
                    D_801F4E84 = D_801F4E84 + 4;
                }
            } else {
                if (D_801F4E84 - x < 5) {
                    D_801F4E84 = x;
                } else {
                    D_801F4E84 = D_801F4E84 - 4;
                }
            }
        }
        if (D_801F4E88 != y) {
            flag = 1;
            if (D_801F4E88 < y) {
                if (y - D_801F4E88 < 5) {
                    D_801F4E88 = y;
                } else {
                    D_801F4E88 = D_801F4E88 + 4;
                }
            } else {
                if (D_801F4E88 - y < 5) {
                    D_801F4E88 = y;
                } else {
                    D_801F4E88 = D_801F4E88 - 4;
                }
            }
        }
        if (D_801F4E8C != z) {
            flag = 1;
            if (D_801F4E8C < z) {
                if (z - D_801F4E8C < 5) {
                    D_801F4E8C = z;
                } else {
                    D_801F4E8C = D_801F4E8C + 4;
                }
            } else {
                if (D_801F4E8C - z < 5) {
                    D_801F4E8C = z;
                } else {
                    D_801F4E8C = D_801F4E8C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801F4E64 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801F4E6C;
    return D_801F4E6C;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013e064 (src/shared) */


DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013e0fc (src/shared) */


DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013e194 (src/shared) */


DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013e22c (src/shared) */


DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013e298 (src/shared) */


DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013e2c4 (src/shared) */


DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013e370 (src/shared) */


DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013e410 (src/shared) */


DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013e448 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_80135D20", func_8013E4B4);

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013e558 (src/shared) */


DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013e588 (src/shared) */



extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);


void func_8013E5E8(void)
{

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018B7C0[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018B7C0[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013e67c (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern s16 currentLocationId;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {

    extern u8 D_80078EC0;
    extern u16 D_8011511A;
    extern u16 D_80115124;
    extern u8 D_80115148[];
    extern u8 D_80115140[];
    extern s32 D_8018B7AC;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_8018B784;
    extern s16 D_8018B786;
    extern unsigned short D_80115112;
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        register s32 *ep __asm__("$8");
        register s32 *fp __asm__("$9");
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_8018B7AC;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_8018B784 = 2;
        D_8018B786 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8018B786 = 0;
        D_8018B784 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013e814 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {

    extern u16 D_80115110;
    extern u16 D_8011511A;
    extern int func_80029178(int);
    extern void func_8002D4C8(int, int);
    extern void func_80141C0C(int);
    extern unsigned short D_80115118;
    extern unsigned short D_80115128;
    extern unsigned short D_8011512E;
    extern unsigned int D_80115130;
    extern unsigned short D_80115158;
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_801F4EA0;
    extern void * D_801F4EA4;
    extern unsigned char D_8018B424;
    extern unsigned char D_8018B43C;
    extern unsigned char D_8018B4B0;
    extern unsigned char D_8018B4B8;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801F4EA0 = &D_8018B424;
        D_801F4EA4 = &D_8018B4B0;
    } else {
        D_801F4EA0 = &D_8018B43C;
        D_801F4EA4 = &D_8018B4B8;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        func_8002D4C8(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_8018B7AC/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_8018B7AC -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_8018B7AC;
    extern void func_80139954(void);
    extern void func_8014AA28(void);
    extern s32 func_800D0488(s32);
    extern void func_80141C0C(s32);

    s16 *p = &(*(s16*)&D_80115124);
    s16 i;
    s32 v;
    s16 m;

    D_800B9A15 = 0;
    func_80139954();
    if (D_80078EC0 != *p) {
        func_8014AA28();
        if ((D_80078EC0 & 0x7F) != 0) {
            m = D_80078EC0 & 0x7F;
            *p = m;
            if (m == 0 || func_800D0488(m) == 0)
                goto loop;
        }
    }
    *p = 0;
loop:
    for (i = 0; i < 5; i++) {
        s32 *q = &((s32 *)&D_80115110)[i];
        v = ((s32 *)&D_8018B7AC)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}


DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013ea54 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern void func_8013FAF8(s16 a0, s16 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8();
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);


void func_8013EB7C(void) {

    extern short D_800B9A02;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern u16 D_8011511A;
    extern u16 D_8011511E;
    extern short D_80115128;
    extern unsigned short D_80115112;
    extern s16 D_8011512A;
    extern s32 D_80115130;
    extern unsigned char D_8018B788;
    s32 sp10[2];
    short sVar1;
    register short sVar2 __asm__("$2");
    s32 a0v;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (D_8011511A >= 4) {
            func_8013FAF8((s16)D_8011511A, (s16)(D_8011511A + 1));
        }
        func_8013FAF8(0, 5);
        if (D_8011511A == 5) {
            sVar2 = ((short (*)(s32))func_8014168C)(2);
            a0v = 2;
        } else {
            sVar2 = ((short (*)(s32))func_8014168C)((s16)D_8011511A);
            a0v = (s16)D_8011511A;
        }
        iVar4 = func_8014032C(a0v, sVar2);
        if (iVar4 != 0) {
            s32 *p130 = &D_80115130;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8018B788));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8018B788));
            }
            (*(unsigned short *)&D_80115112) -= 1;
        } else {
            if ((D_8011511E & 0x800) != 0 || D_8011512A != 0) {
                func_8013E958();
            }
        }
    }
    (void)sp10;
}


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ed6c (src/shared) */


extern void func_801376E8();
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8018B786` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_8018B784` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.




s32 func_8013EE10() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern s16 D_8018B784;
    extern s16 D_8018B786;
    extern unsigned char D_8018B788;
    extern E4 aD80115188[] __asm__("D_80115188");
    extern E4 D_80115168[];
    extern unsigned short D_80115118;

    short i;
    u16 *p;
    u16 old;
    s16 *r;
    u16 *c;
    s32 sp10[2];

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
    func_8013FAF8(0, 5);
    for (i = 0; i < 5; i++) {
        s32 t = D_80115168[i].f0 * 3 >> 2;
        aD80115188[i].f0 = t;
        D_80115168[i].f0 = D_80115168[i].f0 - t;
    }
    r = &D_8018B786;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_8018B784 = (u16)D_8018B784 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018B788);
        for (i = 0; i < 5; i++) {
            s32 *q = (s32 *)((char *)p - 8);
            *(s32 *)((char *)&q[i] + 0x78) = 0;
            D_80115168[i].f0 = 0;
        }
        c = &D_80115112;
        *c += 1;
    }
    (void)sp10;
}











extern s16 D_800B9A02;

extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);

void func_8013EF88(void)
{

    extern u16 D_80115118;
    extern s32 D_801151D0;
    extern E4  aD80115188[] __asm__("D_80115188");
    extern E4  D_80115168[];
    extern u16 D_80115124;
    extern u16 D_80115114;
    extern u16 D_80115112;
    extern s16 D_8018B786;
    extern s16 D_8018B784;
    u16 *p = &D_80115118;
    u16 old = *p;
    short i;

    if (old != 0) {
        u16 nw = old - 1;
        *p = nw;
        if (nw != 0) {
            D_801151D0 = *(s32 *)((char *)&D_80115118 + 0xB0 + (u16)D_800B9A02 * 4);
            func_8013FAF8(0, 5);
            for (i = 0; i < 5; i++) {
                s32 t = aD80115188[i].f0 * 3;
                aD80115188[i].f0 = t;
                D_80115168[i].f0 = D_80115168[i].f0 + t;
            }
            if (D_80115118 < 3) {
                u16 *s = &(*(u16 *)&D_8018B786);
                *s -= 1;
            }
            {
                u16 *w = &(*(u16 *)&D_8018B784);
                *w -= 2;
                if ((s16)*w < 0) {
                    *w = 0;
                }
            }
        }
    }

    {
        s16 *pv = &(*(s16 *)&D_80115124);
        if (*pv != 0) {
            if (func_800D0488(*pv) == 0) return;
            *pv = 0;
        }
    }

    if (D_80115118 == 0) {
        if (D_80115114 == ((u16)D_800B9A02 ^ 1)) {
            func_800D2624();
        } else {
            D_80115112 += 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8();

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_8018B788;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018B788);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */


