#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
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
extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern s32 func_801508B4(s32);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern s32 func_8016E95C();
extern void func_801754A8(void);
extern void func_8013BC7C();
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int func_801288E8(int arg0);
extern int func_80128940(int arg0);
extern void func_80010AE0(s32 a0);
extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s32 func_80128C98(s32 arg0);
extern s32 func_80128CFC(s32 arg0);
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
extern void func_801299C8();
extern void func_8012944C(void);
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);
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
extern void func_8012A328(void);
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
extern void func_8012A1BC(void);
extern void func_8012A2F4(void);
extern s16 D_80127080;
extern s16 D_801152C2;
extern void func_8012A304(s32 a0, s32 a1);
extern s32 func_80012F74(s32, s32, s32, s32);
extern s32 D_801151D4;
extern void func_8012A418(void);
extern Vec8 D_80114F24;
extern void func_8012A464(void);
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
extern Mat32 D_800AE620;
extern void RotMatrixX(int r, void *m);
extern void RotMatrixY(int r, void *m);
extern void RotMatrixZ(int r, void *m);
extern s32 func_8012B4B8(int param_1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 ratan2(s32 x, s32 y);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8012B77C(s32 out, s32 from, s32 to);
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
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
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
extern void func_8012CC64(s32 a0, s32 a1);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CC88(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012CE2C(s32 a0);
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
extern s32 func_8012DDA4();
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern s16 D_80126B9A;
extern u8 D_801152A8[];
extern void func_8012DFBC(void);
extern void func_8012DFCC(void);
extern void func_8012E014(s32 arg0);
extern void func_8012E138();
extern void func_8012DFD4(u8 *a0);
extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
extern void func_8012E014(s32 a0);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_80049CAC();
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888();
extern void func_8012E138(int model);
extern s32 func_8012E27C(void);
extern void func_8012E284(void);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern void func_8012E28C(s32 arg0, s32 arg1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8012E32C(void);
extern void func_8012E364(s32 arg0_);
extern s32 func_8012E470(s32 a0);
extern void func_8012E4C8(s32 a0);
extern s32 func_8012E504(s32 a0, s32 a1);
extern s32 func_8012E544(s32 a0);
extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012E8C4(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8012E9C0(int param_1);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern s32 func_8002A4FC(s32 a0);
extern s32 func_8012EECC(s32 a0);
extern void func_8012EFB8(s32 a0);
extern void func_8012EF34(s32 a0, s32 a1);
extern void func_8012EF70(s32 a0, s32 a1);
extern s32 aF8012EFB8();
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_8012F274(s32 a0, s32 a1);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s16 D_80126CB6;
extern void func_8012F374(s32 a0, s32 a1);
extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32, s32, s32*, s32*);
extern s32 * func_8012F40C(s32 *param_1, s32 param_2);
extern s32 * func_8012F49C(s32 *param_1, s32 param_2, s32 param_3);
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
extern void func_8012E364();
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
extern void func_8012CBCC(s32);
extern void func_80131E00(struct S80131E00*, s32);
extern void func_80130C08(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80131CF4(s32 a0);
extern void func_80019064(void *a0);
extern s32 aF80131CA8();
extern s32 aF80131CF4();
extern int func_80131D68(int a0, int a1);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void func_80131EEC(void *a0);
extern void func_80131F28(void *a0);
extern void func_80131F64(void *a0);
extern void func_80131FA0(void *a0);
extern void func_80131FDC(void *a0);
extern void func_8001C214(int, int);
extern void func_80132018(int param_1);
extern void func_801320D0(void);
extern void func_801320D8(int param_1);
extern void func_80132144(int param_1);
extern void func_801321B0(int param_1);
extern void func_8013221C(int param_1);
extern void func_8005C324(int dst, int src, int n) __asm__("memcpy"); /* Phase-24: 0x8005C324 is named memcpy for overlays (whale needs it); keep the non-builtin C name here (else built-in codegen), emit via asm-label */
extern void func_801325B8(int a0, int a1, int a2, int a3, int a4);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8013240C(s32 a0);
extern void gteMIMefunc();
extern void func_801325B8(int dst, int src, int m0, int mm, int arg5);
extern void func_8013277C(void);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_80054514(s32 a0, s32 a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_80132DC4(s32 a0, s32 a1, s32 a2);
extern s32 func_80132E6C(s16 *a0);
extern void func_80132EC4(void *a0, s16 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80135888(s32, s32, s32, s32);
extern void func_80132F40(s32 arg0);
extern void func_801330E0(void * param_1, s16 * param_2, s32 param_3);
extern void func_80133060(u8 *a0, s32 *a1, s32 a2);
extern void func_801330E0();
extern void func_8013339C(s16 *a0, s16 *a1);
extern void func_80133298(s32 *a0);
extern void func_8013339C(short *param_1, short *param_2);
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern s32 D_8019A77C[];
void func_80136BC4(s32 a0);
extern void func_8013373C(int a0);
extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);
extern s32 func_80133AB0(s16 flag, s16 x, s16 y, s32 arg3);
extern s32 func_80133CD4();
extern s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2);
extern s32 func_8013435C(s16 *a0, s16 *a1, s32 a2, s16 *a3);
extern s32 func_801343C4(s32 angle, s32 p1, s32 p2);
extern s32 func_80134510(s32 param);
extern s32 func_801345F8(s32 arg);
extern s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
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
extern void func_80136F3C(s32 a0, s32 a1);
extern void func_80137030(s16 a0, s16 a1);
extern void func_80137178(s32 a0, s32 a1);
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
extern s32 aF80137614();
extern s32 func_8013767C(s32 a0);
extern void func_801376E8(int a0, int a1);
extern void func_801376C8(int a0);
extern void func_80139BE0(s32 a0);
extern void * aF801376E8();
extern s32 D_80127524;
extern s32 D_80127528;
extern void func_80137840(s32 a0);
extern void func_80139634(void *);
extern void func_80139DC8(void);
extern void func_8013A860(void);
extern s16 D_8012752E;
extern void func_801379D8(void);
extern void func_801379EC(void);
extern s32 D_80127548[];
extern s32 D_801269F0;
extern s16 D_801269F4;
extern s32 D_801269F8;
extern void func_80138BE0(s32 a0);
extern void func_80137BD8(s32 a0);
extern void func_8013A380(void);
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
extern s32 func_80138DE0(u8 *arg0, u8 arg1, s32 arg2);
extern void func_80139B18(s32 a0);
extern void func_80138AB4(s32 a0);
extern void func_80138C30(void *a0);
extern void func_80139C7C(u8 *a0);
extern s32 func_8013A8FC(s32 arg0);
extern s32 func_80138C60(s32 arg0);
extern void func_8013A9F8(s32 a0, s32 a1);
extern void func_80138D58(s32 a0, u16 a1);
extern s32 func_80014E80(s32 a0, s32 a1);
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
extern s32 func_80139220(s32 a0);
extern void func_801391F0(void *a0);
extern void func_801392C8(void *a0);
extern void func_801395D4(void *);
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);
extern void func_801392FC(s32 arg0, s32 arg1, u8 *arg2);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_801395D4(void * a0);
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
extern s32 func_8013A8BC(void);
extern void func_8013A9B4(s32 a0, s32 a1);
extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B204(s32 a0, s32 a1);
extern void func_8013AF20();
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern s32 D_800A5E60;
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8013AD38(void *flag, s32 a1, void *out2, void *out3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern void func_8013CABC(void);
extern void func_8013CAE8(void);
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);
extern void func_8013CB84(void);
extern void func_8013CF68();
extern void func_8013D064(void);
extern s32 func_8013D13C(void);
extern void func_8013D164(void);
extern void func_8013D53C(void *);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013D3D4(int param_1, int param_2);
extern void func_8013D53C(void *arg0v);
extern void func_800599B8(u16*);
extern void func_8013D9B0(int param_1);
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
extern u8 *D_801274C8;
extern void func_8013E4B4(void);
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
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
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
extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */
extern u16 D_80115112;
extern void func_8013ED6C(void);
extern s32 func_8013EF88();
extern void func_8013F138(void);
extern void func_800D2624(void);
extern unsigned short D_80115114;
extern unsigned short D_80115118;
extern void func_8013F1BC(void);
extern void func_80141C0C(s32);
extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern void func_801407F4(void);
extern s16 func_8014168C(s16);
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
extern s32 * func_80140958();
extern s32 * func_80140D68();
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern void func_80140E6C(void);
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
extern void func_80140F00(void);
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
extern Prim_1412A8 * aF801412A8();
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
extern void func_800D24A0(int);
extern void func_8002D4C8(int, int);
extern void func_80141C0C(int);
extern s32 func_801418F8(void);
extern s32 func_8013F350(void);
extern s32 func_80141A60();
extern void func_8013FAF8(s16, s16);
extern u16 D_80115116;
extern void func_80141B90(void);
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
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_80142C9C(s32 *a0);
extern void func_80142838(s32 *a0);
extern s32 func_80142D38(s32 *a0);
extern void func_801428CC(s32 *a0);
extern void func_8014292C(int param_1);
extern void func_80142978(int param_1);
extern void func_801429C4(int param_1);
extern void func_80142A80(void);
extern void func_80142A10(int param_1);
extern void func_80142C84(s32 a0);
extern void func_80143994(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);
extern void func_801439C0(u8 *a0);
extern void func_80142BB4(s32* param_1, s32 param_2, s32 param_3);
extern void func_80142C7C(void);
extern void func_80142C9C(s32 * arg0);
extern void func_80142DC4(int param_1);
extern void func_80142E38(int param_1);
extern void func_80142EC0(s32 param_1);
extern void func_80142F68(s32 *a0);
extern void func_80142FFC(s32 *a0);
extern void func_8014305C(int param_1);
extern void func_801430F4(s32 *a0);
extern void func_80143188(s32 *a0);
extern int func_8001CA88(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_801431E8(s32 param_1);
extern void func_801432FC(s32 *a0);
extern void func_80143390(s32 *a0);
extern void func_80143458();
extern void func_801433F0(s32 a0);
extern void func_80143458(s32 param_1);
extern void func_8014358C();
extern void func_8014350C(s32 *a0);
extern void func_8014358C(s32 param_1);
extern s32 rand(void);
extern void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143970(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern void func_801439FC(s32 a0);
extern void func_80143B30(void *a0);
extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_80143BDC(u16 *a0);
extern void func_80143C38(void *a0);
extern void func_80143C74(s32 a0, s32 a1);
extern void func_80143C98(void *a0);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void func_80143D28(s32 param_1);
extern void func_80143E68(void *a0);
extern void func_80143EA4(void);
extern void func_80143EAC(void);
extern void func_80143EB4(void);
extern s32 func_8004787C(s32 a0);
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
extern s32 func_80047948(s32 a0);
extern void func_80144090(s32 param_1);
extern void func_801442F8(int param_1);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80144364(int param_1);
extern void func_80144458(void *arg0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80144558(u8 *param_1);
extern void func_8014462C(u8 *a0);
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
extern int func_80144B14(int param_1);
extern void func_80144AEC(s32 *a0);
extern s32 func_80013294(void *a0, void *a1);
extern int func_80144B14(int param_s0);
extern void func_801458E0(void);
extern s32 D_800AE6AC;
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
extern u8 D_80126BA4;
extern void (*D_80183F98[])(void *);
extern void func_8014C6F4();
extern void func_80155150(s32 a0);
extern void func_801470C0(s32 a0);
extern void func_80147478(s32 a0);
extern void func_80147118(s32 a0);
extern void func_8014BDE8(s32 a0);
extern short func_801508F8(s32 a0);
extern void func_8014B5B0(s32 *a0);
extern void func_80161D88();
extern void func_801463A0(void);
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
extern u16 *func_80146750(u16 *param_1);
extern u16 *func_8014680C(short *param_1);
extern void aF801466F0(u16 a0, s32 a1, u16 a2, u16 a3, u16 sp5, s32 sp6, s32 sp7, s32 sp8) __asm__("func_801466F0");
extern void aF801466F0(u16 a0, s32 a1, u16 a2, u16 a3, u16 sp5, s32 sp6, s32 sp7, s32 sp8);
extern unsigned short D_8011FD10;
extern int D_8011FA1C;
extern unsigned short D_8011F9D6;
extern unsigned short D_8011F9DA;
extern unsigned short D_8011F9DE;
extern int D_8011FA20;
extern int D_8011FA24;
extern unsigned short * func_80146750(unsigned short *a0);
extern unsigned short * func_8014680C(short *param_1);
extern s32 D_8011F750;
extern s32 D_8011F754;
extern u8 * func_801468C8(s32 arg0, u8 arg1);
extern s32 D_8011D030;
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146924(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern s32 func_80146994(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern void func_80146AFC(void*);
extern void aF80146A6C();
extern s32 func_80146B9C(void *a0);
extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
extern s32 func_80146B9C(void * arg0);
extern s32 aF80146AFC();
extern u16 D_8011DA28;
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
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146F58(s32 a0, s32 a1);
extern void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3);
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
extern void func_80147364();
extern void func_80147300(u16 arg0);
extern void func_80147324(s32 arg0);
extern void func_80015978(s32, s32*);
extern s32 aF8012E5CC(s32, s32, s32) __asm__("func_8012E5CC");
extern void aF80147364();
extern void func_801473EC(s32 *a0);
extern void func_80147460(s32 a0);
extern void func_80147514();
extern void func_80147628(s32 a0);
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
extern void func_80015978(int a0, int *a1);
extern int func_80133784(int a0, void *a1, int a2);
extern void func_801483E8(unsigned char *self);
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
extern void func_80149374(s32 arg0, s32 arg1);
extern void func_801493D0(s32 param_1, s32 param_2, s32 param_3);
extern void func_8014942C(s32 arg0);
extern void func_80149450(s32 a0, s16 *a1);
extern void func_801494CC(s32 a0, u16 *a1, u16 *a2);
void func_8012F14C(s32 a0, s32 a1, s32 a2);
void func_8012EF70(s32 a0, s32 a1);
extern void func_80149544(s32 a0, s32 a1, s32 a2);
void func_8012EFB8(s32 a0);
extern void func_80149584(s32 param_1, s32 param_2, s32 param_3);
extern void func_8014964C(s32 param_1, s32 param_2);
extern void func_8012EF70(s32, s32);
extern void func_801495C4(s32 a0, s32 a1);
extern s32 func_801496D4(void *a0);
extern void func_8015AD08();
extern void func_80149704(void);
extern void func_8015ACC4();
extern void func_80149724(void);
extern u8 D_80078EBF;
extern s32 func_80149744(struct S_80149744 *a0);
extern void func_8015F7A0();
extern void func_80149788(void);
extern u8 D_80078EC1;
extern s32 func_8014CB7C(void);
extern s32 func_8014C088(s32 a0, s32 a1);
extern u8 func_80165658(s32 a0, s32 a1);
extern s32 func_801497A8(s32 *a0);
extern void func_801653B8();
extern void func_80149864(void);
extern s32 func_8016F1AC(void);
extern s32 func_80149884(void);
extern void func_80160B00();
extern void func_801498C0(void);
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
extern s32 func_801498E0(s32 *a0);
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
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EDEC(s32, s32, s32);
extern void func_80149FA8(void);
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
extern int func_8014A51C(int param_1);
extern s32 func_8014A674(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern s32 func_8014A738(void *arg0);
extern void func_8015E184();
extern void func_8014A830(void);
extern s32 func_80029AF4(void);
extern s32 func_8014A850(s32 param_1);
extern void func_8014AA04(s32 a0);
extern s32 func_80165A20(s32 a0);
extern void func_8014AB7C();
extern void func_8014AC10();
extern void func_8014AA28(void);
extern void func_8014AB5C(void);
extern void func_80162CCC();
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
extern s32 D_80078E98;
extern void func_8014B4D4(void *a0);
extern s16 D_80078E9A;
extern u8 D_80126D1C;
extern s32 D_80126D74;
extern void func_8014B598(s32 a0, s32 a1);
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
extern void func_80029ED4(s32 a0);
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
extern s32 aF8014C4AC();
extern s32 func_8014C568(s16 *a0, s16 *a1);
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
extern void func_8014C6F4(u8 *a);
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
extern s32 D_80126B9C;
extern s32 func_8014CAFC(void);
extern s32 func_8014CB0C(void);
extern s32 func_8014CB1C(void);
extern u8 D_80126D1F;
extern s32 func_8014CB2C(void);
extern s32 func_8014CB58(void);
extern u8 D_80126D1D;
extern void func_8014CB68(void);
extern s32 func_8014CB8C(void);
extern struct Packed8 D_80126C98;
extern short D_80126C9E;
extern void func_8014CB9C(struct Packed8 *a0);
extern s32 D_80126CDC;
extern void func_8014CBD8(void);
extern void func_8014CBF8(void *a0);
extern void func_8014D3E0();
extern void func_8014D04C(void);
extern void func_8014CCB4(void);
extern void func_8014CC28(s32 a0);
extern void func_8014CD0C(u8 *a0);
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern int func_8014CD80(s32 a0, u16 *a1, u16 *a2);
extern int func_80135A4C();
extern int func_80135888();
extern int func_8014C918();
extern int func_8014CD80(int param_1, unsigned short *param_2, unsigned short *param_3);
extern s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2);
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern void func_8014D0A4(s32);
extern s32 func_8014D2A0(s32 a0, void *a1, void *a2);
extern s32 func_8014D12C();
extern void func_8014D0A4(s32 a0);
extern s32 func_8014D12C(s32 arg0, void *a1, void *a2);
extern s32 func_8014D2A0(s32 arg0, void *a1, void *a2);
extern s32 func_8014D610(s32 a0, s32 a1, u16 *a2);
extern s32 func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern s32 func_8014D610(s32 param_1, s32 param_2, u16 *param_3);
extern void func_8014D790(s32);
extern void func_8014D738(void);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2);
extern void func_8014D790(s32 a0);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x);
extern s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8014DF94(s32);
extern void func_8014DF3C(void);
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */
extern void func_8014DF94(s32 arg0);
extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */
extern s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);  /* canonical (engine_core.h:11555) */
extern s32 func_8014E284(s32 a0, s16 *arg1, s16 *arg2);
extern void func_8014E48C(s32);
extern void func_8014E434(void);
extern void func_8014E5B4(s32 a0, void *a1, void *a2);
extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2);
extern void func_8014E48C(s32 a0);
extern s32 aF8014E5B4();
extern void func_8014E6F8(struct SubE6F8*);
extern void func_8014E6A0(void);
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
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014ED80(struct SubED80 *a0);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F24C(struct SubF24C*);
extern void func_8014F1F4(void);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F468();
extern int func_8014F6F4();
extern s32 func_8014F3E8(s32 param_1);
extern int func_8014F74C();
extern s32 D_801152BC;
extern s32 func_8014F4C0(s32 arg0);
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_8014FC18(u8*);
extern void func_8014FBC0(void);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int);
extern void func_8014FCFC(void);
extern int func_8014FD54(int param_1);
extern s32 func_80150170(void *a0);
extern s32 func_8014FE60();
extern s32 func_8014FE60(void *e);
extern s32 func_80135D20(s32 a0, s32 a1, void *a2);
extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
extern s32 func_80150150(s32 a, s32 b);
extern s32 func_801502EC(s32 e, void *a1, void *a2);
extern s32 func_80150460(s32 e, s32 a1);
extern s32 func_80150170(void *e);
extern s32 func_80150460(s32 a, s32 b);
extern s32 func_80150528(void *a0, void *a1, void *a2);
extern void func_801504D8(u16 *a0);
extern s32 func_80150528(void *arg0, void *arg1, void *arg2);
extern s32 func_801506A4();
extern void func_80147324(s32 a0);
extern s32 func_801506A4(s32 arg0, s32 arg1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8015086C(int param_1);
extern s32 func_801508B4(s32 a0);
extern s32 func_8015094C(s32 a0);
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
extern void func_80151664(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_80153C18();  /* fleet canon: K&R empty prototype — engine_core.h:75/:1682 define it (void); a prototyped (s32) decl would be `conflicting types` here, and the arg still passes in $a0 under default promotions, so codegen is unchanged. */
extern void func_80151664(void);
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
extern void func_80151944(void *a0);
extern s32 func_80151924(void);
extern void func_8014E934(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_801519C8(s32 a0);
extern void func_80151980(s32 a0);
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_801519C8(s32 arg0);
extern void func_80151C54(s32 a0);
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_8015BDD0(s32 *a0);
extern void func_80165718(s32 a0);
extern u8 D_800D46E4[];
extern void func_80151AE4(s32 arg0);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80151B98(int param_1);
extern void func_80153C18();
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
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
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
extern void func_8014ED28(s32 a0);
extern void (*D_8011DB28)(s32 a0);
extern s32 func_801536DC(s32 param_1);
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
extern s32 func_801659DC();
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
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
extern void func_80156044(int arg, int a1);
extern void func_80156044(int param_1, int param_2);
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern u16 D_8012693A;
extern u16 D_801152B8;
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern S801563EC * func_801563EC(u16 idx);
extern s32 func_801564B0(s32 a0);
extern s32 D_801151E0[];
extern s32 func_801565C0(void);
extern S8 D_80126AF0[];
extern s32 func_80156600(void* _arg0);
extern void func_80156A14(s32 *a0);
extern void func_80156648(s32 *a0);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_80156670(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, u16 param_6);
extern u8 D_8011DAD8[];
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
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
extern void func_80157808();
extern void func_801577C8(s32 *a0);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_8014ED28(s32 _arg0);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern void func_8015795C(int param_1);
extern void func_80161D20();
extern void func_80157A8C(s32 a0);
extern void func_8016706C(s32 a0);
extern u8 D_800D51AC[];
extern void func_80157AC8(s32 param_1);
extern void func_80157B74(int param_1);
extern void func_8016158C(void *a0);
extern void func_8015BE04(s32 *a0);
extern void func_80157BC8(s32 a0);
extern void func_80157CCC(s32 a0);
extern void func_80157D74(u16 *a0);
extern void func_80157DC4(void *a0);
extern void func_80157FC4(void *a0);
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
extern s32 func_80159464();
extern int func_800D0F8C(int a0);
extern void func_8016F0E4(void);
extern void func_800D0F4C(s32 a0);
extern void func_80158814(void *a0);
extern void func_80158638(void *a0);
extern void func_80158794(void);
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void func_80158AE4(void *a0);
extern void func_80158AB4(void *a0);
extern s32 D_80078EC8;
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
extern void func_80159A20();
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
/* ==== end §8b carried decl layer ==== */



/* func_8015A3C8 (ov_SC01_077_after, 493 ins, jtbl_801D8B34) — Phase 26 crack
 * Entity air/fall update: 7-case switch (0/1/2/6 shared, 3/4/5 own, no default block),
 * then a big velocity-clamp tail with a nested char switch (0x41 / 0x53+0x73).
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — x134 template-safe.
 */
extern s16 currentLocationId;

extern s32 func_80149D9C(s32 a0);
extern void func_80149FA8(void);
extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161B18(void *a0);
extern s32 func_8014A048(s32 a0);
extern void func_8014A218(void);
extern s32 func_80161BE0(s32*);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32 func_80149B54(s32 * arg0);
extern void func_80149BAC(s32 *a0);
extern s32 func_801498E0(s32 *a0);
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern s32 func_80149CD4(s32 a0);
extern void func_8015E880(s32 *a0);
extern s32 func_801496D4(void *a0);
extern void func_80149704(void);
extern s32 func_801488A8(u8 *a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern void func_8015AC48(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 func_801487F4(s32 *a0);
extern s32 func_8016F1C4(void);
extern s32 func_8015AB7C(s32 a0);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_80148824(void *arg0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C6E0(s32 *a0);
extern void func_8014E934(s32 _arg0);
extern void func_80155440(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80161278(void *a0);
extern void func_80161C24(s32 a0, s32 a1);
extern s32 func_80172608(u8 *a0);
extern void func_801483E8(unsigned char*);

s32 func_8015A3C8(arg0)
s32 arg0;
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80078E78[];

    extern void (*D_80184B44[])(void *);

    extern s32 D_800D5428;
    extern u8 D_80184AC8[];
    s32 min;
    s32 grav;
    s32 hi;
    s32 t;
    s32 lo1;
    s32 lo2;
    s32 sv;
    u8 *p;

    p = D_80078E78;
    if (currentLocationId == 0x302A) {
        min = -0xC0000;
        grav = -0x4000;
        hi = 0;
    } else {
        min = -0xB0000;
        grav = -0x1000;
        hi = 0;
    }

    if (func_80149D9C(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149FA8)(arg0);
        return;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (((s32 (*)(s32))func_80161B84)(arg0) != 0) {
        return;
    }
    if (((s32 (*)(s32))func_80161B18)(arg0) != 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D5428) {
        if (func_8014A048(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8014A218)(arg0);
            return;
        }
    }
    if (((s32 (*)(s32))func_80161BE0)(arg0) != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }

    if (func_80149CD4(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) == 0) {
        sv = *(s32 *)(arg0 + 0x2C);
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        if (func_8015ABD4(arg0, sv, min) != 0) {
            func_8015AC48(arg0);
        }
        return;
    }

    ((void (*)(s32))func_80148AFC)(arg0);
    if (*(u32 *)(arg0 + 0x44) & 0x200) {
        if (*(s32 *)(arg0 + 0x23C) == 0) {
            func_80154150(arg0, 0xA);
            func_80154A74(arg0, 0x1C);
        }
        ((void (*)(s32, s32))func_80146DB8)(arg0, (s32)&(*(s32 *)&D_80184AC8));
        func_80147AD4(arg0, 0, 0, 0);
    } else {
        switch (*(u8 *)(arg0 + 0xA9)) {
        case 0x41:
            func_80147AD4(arg0, 0, 0, grav);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                if (((s32 (*)(s32))func_801487F4)(arg0) & 4) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                } else if (func_8016F1C4() == 0) {
                    if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                            *(s32 *)(arg0 + 0x2C) = -0x40000;
                        }
                    } else if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                            *(s32 *)(arg0 + 0x2C) = -0x80000;
                        }
                    }
                }
                if (*(s32 *)(arg0 + 0x2C) < min) {
                    *(s32 *)(arg0 + 0x2C) = min;
                }
                if (*(s32 *)(arg0 + 0x2C) >= hi) {
                    *(s32 *)(arg0 + 0x2C) = hi;
                }
                lo1 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo1) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        case 0x53:
        case 0x73:
            *(s32 *)(arg0 + 0x2C) = (min * (((s32 (*)(s32))func_80148824)(arg0) & 0xFF)) / 127;
            if (func_8016F1C4() == 0) {
                if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                        *(s32 *)(arg0 + 0x2C) = -0x80000;
                    }
                }
                if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x2C) < min) {
                *(s32 *)(arg0 + 0x2C) = min;
            }
            if (*(s32 *)(arg0 + 0x2C) >= hi) {
                *(s32 *)(arg0 + 0x2C) = hi;
            }
            func_80147A84(arg0);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                lo2 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo2) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        }
    }

    ((void (*)(s32))func_801473EC)(arg0);
    if ((min >= *(s32 *)(arg0 + 0x2C)) && !(D_800B99DA & 7)) {
        func_8014C010(arg0, 2);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_8014E934)(arg0) != 0) {
        ((void (*)(s32))func_80155440)(arg0);
        func_80154150(arg0, 0x12);
        func_80154A74(arg0, 0x17);
        *(s32 *)(arg0 + 0x23C) = 1;
    } else {
        if (*(s32 *)(arg0 + 0x23C) != 0) {
            func_801553C0(arg0);
            func_80154150(arg0, 6);
            func_80154A74(arg0, 0x21);
        }
        *(s32 *)(arg0 + 0x23C) = 0;
    }
    if (((s32 (*)(s32))func_80161278)(arg0) == 0) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            func_80161C24(arg0, *(u16 *)(arg0 + 0x16E));
        }
        ((void (*)(s32))func_80172608)(arg0);
        ((void (*)(s32))func_801483E8)(arg0);
    }
}

#include "../shared/ov/func_8015AB7C.h"


#include "../shared/ov/func_8015ABD4.h"


extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80161CD0(s32 a0, s32 a1);

extern s32 D_80184AD8;

void func_8015AC48(s32 arg0)
{
    u16 val;
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, (s32 *)&D_80184AD8);
    val = *(u16 *)((u8 *)arg0 + 0x16E);
    func_80161CD0(arg0, val);
}


#include "../shared/ov/func_8015AC90.h"


#include "../shared/ov/func_8015ACC4.h"


#include "../shared/ov/func_8015AD08.h"




void func_8015AD3C(void *a0) {

    extern void (*D_80184C9C[])(void);
    D_80184C9C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015AD78.h"


#include "../shared/ov/func_8015ADB0.h"



/* func_8015AE2C (ov_SC01_077_after, 562 ins, jtbl_801D8B54) — Phase 26 crack
 * Entity main-update dispatcher: 7-case switch (0/1/2/6 shared, 3/4/5 own, no default
 * block — out-of-range falls to the after-switch join), then movement/clamp/decay tail.
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — ×134 template-safe.
 *
 * match_one: MATCH (562 ins). rtu_match (whole-TU): MATCH (562 ins) — see func_8015AE2C.md
 * for the two TU-side prerequisites (engine_core.h DEFINE_func_8015BEC4 extern must drop its
 * `(void)` prototype, and the def must stay K&R) plus the jtbl_carve trailing-pad-word note.
 *
 * Signature: `s32` return + K&R def are REQUIRED by the TU, byte-neutral vs void/ANSI here
 * (both verified MATCH 562): engine_core.h's thunk DEFINE_func_8015BEC4 does
 * `return func_8015AE2C();` (s32, zero-arg call) — only an unprototyped K&R def coexists
 * with that call. §41d does not bite on this body (it has early `return;`s).
 *
 * jtbl_801D8B54 = 7 entries [0,1,2,6]->0x8015AEE4  [3]->0x8015AFE0  [4]->0x8015AFF0
 * [5]->0x8015B000, bound `sltiu 7`, default(out-of-range) -> 0x8015B044 (after-switch).
 * The raw dlabel's 8th word 0x00000000 is NOT a table entry: it is the original TU's
 * intra-TU `.align 3` pad between consecutive jtbls (B34/B54/B74 chain) — the compiled
 * object emits exactly 28 B; the pad must stay in the raw post-carve data piece.
 */
extern void (*D_80184B44[])(void *);
extern s32 func_80161A60(s32 a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_80149FB0(s32 a0);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149C08(s32 a0);
extern void func_801577C8();
extern s32 func_8015B6F4(s32 a0);
extern s32 func_8015B7B4(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8015B8F8(s32 *a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801498E0(s32 *a0);
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern int func_80155FF8(int arg, int a1);
extern s32 func_8015B858(u8 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147814(s32 a0, s32 a1);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32 a0);
extern int func_80148AFC(void *a0);
extern s32 func_80149184(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147A30(s32 a0, s32 a1, s32 a2);
extern s32 func_80146E98(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32 *a0);
extern s32 func_80172644(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_8014C050(s32 a0, s32 a1);
extern void func_800CCB78(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80161488(void *a0);
extern void func_80146CA0(void *a0);
extern s32 func_8014A674(s32 *a0);
extern void func_8014E434(void);
extern void func_8015CC40(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern void func_8014E6A0(void);
extern void func_8015CF8C(s32 *a0);
extern s32 func_801725A4(u8 *a0);
extern s32 D_800D4E94;
extern s32 D_800D4ED4;
extern u8 D_800D4F8C[];
extern s32 D_800D4A9C;
extern s32 D_800D4B48;

s32 func_8015AE2C(arg0)
s32 arg0;
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800D4BE0[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801152A0;
    s32 flag;
    s32 r;
    s32 lim;
    s32 doit;
    s32 t;

    flag = 0;
    if ((func_80161A60(arg0) != 0) && (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) && (*(s32 *)(arg0 + 0x34) >= 0)) {
        flag = 1;
        if (*(s32 *)(arg0 + 0x5C) == 0) {
            *(s32 *)(arg0 + 0x58) = 0;
            *(s32 *)(arg0 + 0x54) = 0;
            *(s32 *)(arg0 + 0x50) = 0;
        }
        *(s32 *)(arg0 + 0x5C) = 1;
    } else {
        *(s32 *)(arg0 + 0x5C) = 0;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (*(s32 *)(arg0 + 0x1B0) == 0) {
        switch (((s32 (*)(s32))func_801619A4)(arg0)) {
        case 0:
        case 1:
        case 2:
        case 6:
            if (*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) {
                if (func_80149C08(arg0) != 0) {
                    D_80184B44[*(u16 *)arg0]((void *)arg0);
                    ((void (*)(s32))func_801577C8)(arg0);
                    return;
                }
            }
            if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
                if (func_8015B6F4(arg0) == 0) {
                    ((void (*)(s32))func_8015B7B4)(arg0);
                }
            } else {
                if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
                    func_80154A74(arg0, 0x22);
                    ((void (*)(s32))func_8015B8F8)(arg0);
                    *(u32 *)(arg0 + 0x44) &= ~2;
                    if (flag != 0) {
                        ((void (*)(s32, s32, s32, s32))func_80146994)(0x3B, arg0, 0, 0);
                    }
                }
            }
            break;
        case 3:
            ((void (*)(s32))func_801498E0)(arg0);
            break;
        case 4:
            ((void (*)(s32))func_80149954)(arg0);
            break;
        case 5:
            if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
                D_80184B44[*(u16 *)arg0]((void *)arg0);
                func_800CCCC0(arg0);
                return;
            }
            break;
        }
    }
    if (*(u32 *)(arg0 + 0x44) & 2) {
        ((void (*)(s32, s32))func_80155FF8)(arg0, *(u8 *)(arg0 + 0x1AA));
    } else {
        if ((*(s32 *)(arg0 + 0x240) == 0) && (((s32 (*)(s32))func_8015B858)(arg0) != 0)) {
            *(s32 *)(arg0 + 0x240) += 1;
        }
        if ((*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) && (*(u16 *)(arg0 + 0xB8) & 0x8000)) {
            ((void (*)(s32))func_8015B8F8)(arg0);
        } else if ((*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) ||
                   (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4B48)) {
            if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
                if (*(s32 *)(arg0 + 0x34) >= 0) {
                    *(u16 *)(arg0 + 0xB8) += 1;
                }
            }
        }
    }
    if (*(u8 *)(arg0 + 0x1C6) != 0) {
        if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
            func_80148038(arg0, 0xFFFE6000);
        } else {
            func_80148038(arg0, 0x1A000);
        }
        lim = 0x40000;
        if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
            lim = 0xC0000;
        }
        if (*(s32 *)(arg0 + 0x34) < -lim) {
            *(s32 *)(arg0 + 0x34) = -lim;
        } else if (lim < *(s32 *)(arg0 + 0x34)) {
            *(s32 *)(arg0 + 0x34) = lim;
        }
        func_80147460(arg0);
    } else {
        if (*(s32 *)(arg0 + 0x34) < 0) {
            if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
                func_80147814(arg0, 0xFFFF0000);
            }
            func_80147814(arg0, 0x10000);
        }
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = ((*(u16 *)&D_801152A0) + func_801491C4(arg0)) & 0xFFF;
    }
    if (flag == 0) {
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            ((void (*)(s32, s32))func_80146E90)(arg0, 4);
            if (*(s32 *)(arg0 + 0x2C) > -0x80000) {
                *(s32 *)(arg0 + 0x2C) = -0x80000;
                func_80147A30(arg0, -0x10000, 0xBA000);
            } else {
                func_80147A30(arg0, -0x1000, 0xBA000);
            }
        } else {
            if (func_80146E98(arg0) != 0) {
                func_80146D90(arg0);
            }
        }
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (*(u8 *)(arg0 + 0x1C6) == 0) {
            func_80148038(arg0, 0x1A000);
            func_80147460(arg0);
        }
    } else {
        ((void (*)(s32))func_80172644)(arg0);
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            func_80146D90(arg0);
            func_80147AD4(arg0, 0, 0, 0xFFFF4000);
            *(s32 *)(arg0 + 0x50) += *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 0x54) += *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x58) += *(s32 *)(arg0 + 0x18);
            if (*(s32 *)(arg0 + 0x50) > 0xBA000) {
                *(s32 *)(arg0 + 0x50) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x50) < -0xBA000) {
                *(s32 *)(arg0 + 0x50) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x54) > 0xBA000) {
                *(s32 *)(arg0 + 0x54) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x54) < -0xBA000) {
                *(s32 *)(arg0 + 0x54) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x58) > 0xBA000) {
                *(s32 *)(arg0 + 0x58) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x58) < -0xBA000) {
                *(s32 *)(arg0 + 0x58) = -0xBA000;
            }
            *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
            ((void (*)(s32))func_801473EC)(arg0);
        } else {
            doit = 0;
            if (*(s32 *)(arg0 + 0x50) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x50) >= 0) {
                    *(s32 *)(arg0 + 0x50) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x50) < 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x50) += 0x8000;
                    if (*(s32 *)(arg0 + 0x50) >= 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x54) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x54) >= 0) {
                    *(s32 *)(arg0 + 0x54) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x54) < 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x54) += 0x8000;
                    if (*(s32 *)(arg0 + 0x54) >= 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x58) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x58) >= 0) {
                    *(s32 *)(arg0 + 0x58) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x58) < 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x58) += 0x8000;
                    if (*(s32 *)(arg0 + 0x58) >= 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                }
            }
            if (doit != 0) {
                *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
                *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
                *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
                ((void (*)(s32))func_801473EC)(arg0);
            }
            if (!(*(u32 *)(arg0 + 0x44) & 2)) {
                ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xF, 0x12);
            }
        }
        t = func_8014C050(arg0, 0x3B);
        if (t != 0) {
            func_800CCB78(t);
        }
        if ((*(u16 *)(arg0 + 0x1C8) & 0x1F) == 0) {
            ((void (*)(s32, s32, s32, s32))func_80146994)(0x3C, arg0, 0, 0);
        }
    }
    if (*(s32 *)(arg0 + 0x1B0) != 0) {
        if (*(s32 *)(arg0 + 0x1B0) == 1) {
            func_80154A74(arg0, 0x22);
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32))func_80154274)(arg0, *(s32 *)(arg0 + 0x1B4));
        }
    }
    r = ((s32 (*)(s32))func_80161488)(arg0);
    if (r & 5) {
        *(u32 *)(arg0 + 0x44) &= ~2;
        if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) {
            func_80154150(arg0, 0xE);
        } else {
            func_80154150(arg0, 0x10);
        }
        ((void (*)(s32))func_80146CA0)(arg0);
    }
    if (r == 0) {
        if ((((s32 (*)(s32))func_8014A674)(arg0) != 0) && (((s32 (*)(s32))func_8014E434)(arg0) != 0)) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CC40)(arg0);
        } else if ((((s32 (*)(s32))func_8014A69C)(arg0) != 0) && (((s32 (*)(s32))func_8014E6A0)(arg0) != 0)) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CF8C)(arg0);
        } else {
            ((void (*)(s32))func_801725A4)(arg0);
        }
    }
}

#include "../shared/ov/func_8015B6F4.h"


#include "../shared/ov/func_8015B7B4.h"




extern int func_8014A51C(int param_1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);

s32 func_8015B858(u8 *a0)
{
    extern u8 D_800D4BE0[];
    extern s32 D_8011F730;

    if (*(u8 *)(a0 + 0x1C6) != 0) {
        return 0;
    }
    if (*(s32 *)(a0 + 0x240) != 0) {
        return 0;
    }
    if (((s32 (*)(void))func_8014A51C)() == 0) {
        return 0;
    }
    *(s32 *)(a0 + 0x23C) = *(s32 *)(a0 + 0xB4);
    *(u8 *)(a0 + 0x244) = *(u8 *)(a0 + 0xBC);
    func_801477E8((s32 *)a0, 0xFFF20000);
    func_80154274((s32 *)a0, (s32)D_800D4BE0);
    D_8011F730 |= 2;
    return 1;
}


#include "../shared/ov/func_8015B8F8.h"



// @class: plumbing
// @stuck: none — MATCH (271/271, pin-free, zero asm). The ONLY residual is DEF-SIDE plumbing, and it is now named exactly: the in-TU instantiation `DEFINE_func_8015BEE4()` (engine_core.h:1851-1855) expands to `extern s32 func_8015B950(void);` INSIDE ov_SC01_077_jr_8015AE2C.c, ~14 lines BELOW this definition, so the 1-param def collides with a `(void)` prototype -> `conflicting types for func_8015B950` (.run/bank_func_8015B950.log). §73 PARAMS axis / T0. Surgical fix = §65b de-macroize that ONE instantiation (blast radius: this TU); the fleet-wide `(void)`->`()` header edit is §63 and must be R22-validated.
/* func_8015B950 (ov_SC01_077_jr_8015AE2C, 271 ins, jtbl_801D8B74) — SESSION-21 re-verified
 *
 * ── ROUND-2 INDEPENDENT RE-VERIFICATION (2026-07-27, fresh agent, §88e discipline) ─────────────
 *   match_one : MATCH (271 ins) against the CURRENT tree — §87 staleness re-checked today.
 *   .text size: compiled .text = 0x43C = 1084 B = 271 ins, EXACTLY the target's declared 0x43C
 *               ("nonmatching func_8015B950, 0x43C"). So this is NOT a §83a length drift hiding
 *               behind a zero count — the count is over equal-length streams.
 *   jtbl      : RE-DECODED MECHANICALLY, not inherited. Compiled .rodata = 0x1C = 28 B = 7 words,
 *               7x R_MIPS_32 -> .text with implicit addends [58,58,58,E0,F0,100,58]; +0x8015B950
 *               = [8015B9A8, 8015B9A8, 8015B9A8, 8015BA30, 8015BA40, 8015BA50, 8015B9A8].
 *               Diffed word-for-word against asm/ov_SC01_077/data/tail14.data.s:15-23 — 7/7 identical.
 *   symcheck  : SYMS-DIFF target=35 draft=34, sole MISSING = jtbl_801D8B74. This is the §81 jr
 *               FALSE POSITIVE, re-confirmed here by reading the relocs: gcc emits its OWN table and
 *               references it with R_MIPS_HI16/LO16 against the SECTION `.rodata` (t.o +0x40/+0x48),
 *               so the splat's dlabel NAME can never appear in the draft object's relocation set.
 *               Nothing is dropped and nothing is invented: the draft's other 34 symbols are exactly
 *               the target's other 34.
 *   FAMILY    : the x138 remap is clean and §84-safe. Every sibling is 271 ins with an IDENTICAL
 *               callee set; only THREE names vary per overlay — the two data labels and the jtbl:
 *                 ov_SC01_077  D_80184AD8 / D_80184B44 / jtbl_801D8B74
 *                 ov_SC03_099  D_80185A50 / D_80185ABC / jtbl_801BD898
 *                 ov_SC06_008  D_80187E44 / D_80187EB0 / jtbl_801A8734
 *               The pair is always +0x6C apart, and NO literal in this draft encodes that distance
 *               (both labels are referenced by name), so there is no §84 derived-offset hazard.
 *               D_8011F9C4 is fleet-constant (main-EXE data) and must NOT be remapped.
 *
 * match_one: MATCH (271 ins) against the CURRENT tree (§87 staleness re-checked, 2026-07-27).
 * PIN-FREE, zero asm, offset-pure (s32 arg0 + raw offsets) — x138 template-safe.
 * Provenance: this is the Phase-26 crack (.run/phase26-cracks/func_8015B950.c) re-gated verbatim,
 * with ONE deliberate change: the definition's return type void -> s32.
 *   - `void func_8015B950(s32 arg0)` : MATCH (271 ins)   [the Phase-26 form]
 *   - `s32  func_8015B950(s32 arg0)` : MATCH (271 ins)   [shipped — §3a-1 void->s32 is byte-neutral]
 * The fleet/engine_core.h canonical decl is `extern s32 func_8015B950(void);` (engine_core.h:1852),
 * and the last bank attempt (.run/bank_func_8015B950.log) died on `conflicting types for
 * func_8015B950`. Shipping the s32 return kills the §73 RETURN axis for free and leaves only the
 * cheap T0 PARAMS axis for the ladder (fix_header_decl.py / --fix-def-sig / cast_call_sites).
 * Both forms are byte-identical, so the orchestrator may swap the return type back at zero cost.
 *
 * SYMBOLS (§58 rules 1/2 — all splat spellings, all verified present):
 *   D_80184B44    asm/ov_SC01_077/data/tail.data.s:4355 (the state-handler vtable)
 *   D_80184AD8    asm/ov_SC01_077/data/tail.data.s:4293
 *   D_8011F9C4    main-EXE data; spelled `extern s32 D_8011F9C4;` in 5+ already-banked TUs
 *   jtbl_801D8B74 asm/ov_SC01_077/data/tail14.data.s:15 (compiler jump table — not named in C)
 *
 * JTBL VERIFIED (§8a gate): compiled .rodata = exactly 0x1C B / 7 words, 7x R_MIPS_32 .text with
 * addends [0x58,0x58,0x58,0xE0,0xF0,0x100,0x58] -> +0x8015B950 = [B9A8,B9A8,B9A8,BA30,BA40,BA50,
 * B9A8] == the original words at 0x801D8B74..0x801D8B8C. Bound `sltiu $v0,$v1,0x7` matches.
 * The raw dlabel's 8th word 0x00000000 is NOT an entry — it is the intra-TU `.align 3` pad of the
 * B34/B54/B74 jtbl chain; the object can never emit it (maspsx drops .align), so it must stay in
 * the post-carve RAW data piece (the §53/§62/§81 carve chain applies at bank time).
 *
 * Same family as the TU's own already-matched func_8015AE2C: 7-case switch on ((s32 (*)(s32))func_801619A4)()
 * (0/1/2/6 shared, 3/4/5 own, no default block — out-of-range and every `break` fall to the
 * after-switch join), then a chain of "state handler" tests, each dispatching
 * D_80184B44[*(u16*)arg0](arg0) and returning.
 *
 * THREE LEVERS (draft -> MATCH in 3 compiles):
 *
 * 1. PROLOGUE CONSTANT = an INITIALIZED LOCAL, not a literal in the compare.
 *    Target opens with `lui $s2, 0xFFF5` in the *prologue*, used once ~200 ins later in
 *    `slt $v0,$s2,$s1`. No gcc-2.7.2 pass hoists a (set reg const_int) across basic blocks
 *    (loop.c needs a loop; cse/combine/sched never move insns between BBs) — so the insn must
 *    have been EMITTED in the first BB, i.e. the constant is a local initialized at the top of
 *    the function. cse then cannot fold it back into the compare: the `slt` operand predicate is
 *    `arith_operand`, which rejects a CONST_INT wider than 16 bits, so validate_change fails and
 *    the pseudo survives. Its live range spans every call -> global.c gives it a callee-saved reg.
 *    Writing `z > -0xB0000` inline instead emits the `lui` into the branch delay slot next to the
 *    compare (caller-saved $v0) and the function is 1 insn short. => `s32 lim = -0xB0000;` at top.
 *
 * 2. `lh` vs `lhu`: a short->short copy is a pure HImode move and gcc emits `lhu`. The target's
 *    `lh $v0,0x26($s0)` means the value passed through an SImode (int) temp: expand makes
 *    (set (reg:SI) (sign_extend (mem:HI))) + (set (mem:HI) (subreg:HI ...)), and combine cannot
 *    merge them (the merged form is mem<-mem, which no movhi accepts) so the sign-extending load
 *    survives. => route both halfword copies through the `s32 t` temp.
 *
 * 3. THE `goto` LAYOUT — dodging jump.c's store-flag conversion (jump.c:1005-1065).
 *    An if/else chain writing 0/1 into `doit` makes gcc collapse the last pair into
 *    `sltiu $v0,$v0,1`. jump.c fires that conversion when the insn immediately after a
 *    conditional jump is a lone `SET pseudo, CONST_INT` whose following simplejump targets the
 *    SAME label as the branch (jump.c:1038 `reallabelprev == temp || ... JUMP_LABEL(temp4) ==
 *    JUMP_LABEL(insn)`) — exactly the shape of `if (c) x=0; else x=1;`.
 *    The target instead cross-jumps ALL the `doit=0` exits into ONE shared block placed after the
 *    `doit=1` fall-through; reorg's fill_slots_from_thread then COPIES that single set into all
 *    three branch delay slots and redirects each branch past it (which is why `addu $v0,$zero,
 *    $zero` appears 3x in delay slots and the shared block vanishes). A `goto zero;` / `goto one;`
 *    chain expresses that layout directly, and each conditional jump is then followed by a
 *    compare/call rather than a lone const set, so the store-flag conversion never triggers.
 *    GENERAL RULE: multiple predicates that all assign the SAME constant to one flag => write
 *    them as `goto` to a shared assignment, never as an if/else ladder.
 */


s32 func_8015B950(s32 arg0)
{

    s16 sp10[4];
    s16 sp18[4];
    s32 t;
    s32 z;
    s32 doit;
    s32 lim = -0xB0000;

    if (((s32(*)())func_80161B18)() != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }
    if (func_80149CD4(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80149744)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149788)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        if (((u8)((s32 (*)(s32))func_80148AFC)(arg0)) == 0) {
            func_80146D90(arg0);
        }
        if ((*(s32 *)(arg0 + 0x24) | *(s32 *)(arg0 + 0x2C)) != 0) {
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xD, 6);
        }
        *(s32 *)(arg0 + 0x238) = 1;
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) != 0) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = 0;
        t = *(s16 *)(arg0 + 0x26);
        sp18[0] = t;
        sp18[1] = 0;
        t = *(s16 *)(arg0 + 0x2E);
        sp18[2] = t;
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 1);
        ((void (*)(s32))func_8015A264)(arg0);
        t = -(((s32 (*)(s16 *, s16 *))func_80013294)(sp10, sp18) << 0x10);
        if (t < *(s32 *)(arg0 + 0x2C)) {
            *(s32 *)(arg0 + 0x2C) = t;
        }
        return;
    }
    if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        return;
    }
    z = *(s32 *)(arg0 + 0x2C);
    if (func_8016F1AC() != 0) {
        goto zero;
    }
    if (z <= lim) {
        goto one;
    }
    if (D_8011F9C4 == 0) {
        goto zero;
    }
    if (((u8)((s32(*)(s32))func_80029178)(0x21)) != 0) {
        goto zero;
    }
one:
    doit = 1;
    goto join;
zero:
    doit = 0;
join:
    if (doit != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        func_80154150(arg0, 9);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184AD8);
        ((void (*)(s32, s32))func_80161CD0)(arg0, *(u16 *)(arg0 + 0x16E));
        return;
    }
    if (((s32(*)(s32))func_80161208)(arg0) == 0) {
        ((void (*)(s32))func_801725A4)(arg0);
    }
}

#include "../shared/ov/func_8015BD8C.h"


#include "../shared/ov/func_8015BDD0.h"


#include "../shared/ov/func_8015BE04.h"


#include "common.h"

extern void (*D_80184CB8[])(void);

void func_8015BE38(void *a0) {
    D_80184CB8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015BE74.h"


#include "../shared/ov/func_8015BE94.h"


#include "../shared/ov/func_8015BEC4.h"


#include "../shared/ov/func_8015BEE4.h"


#include "../shared/ov/func_8015BF04.h"


#include "../shared/ov/func_8015BF48.h"


#include "../shared/ov/func_8015BF7C.h"


#include "../shared/ov/func_8015BFB0.h"




void func_8015BFF4(void *a0) {

    extern void (*D_80184CC4[])(void);
    D_80184CC4[*(u16 *)((s32)a0 + 0x2)]();
}



/* §71 sibling-first: this is DEFINE_func_8015C0C4 (src/shared/engine_core.h L8919)
 * with the two globals replaced by the second parameter and <<6 -> <<7.
 * The explicit temporary `t` keeps the first lh ahead of the 0x238 store.
 *
 * Signature is the fleet canon `(s32 *a0, s32 a1)` declared by
 * DEFINE_func_8015BFB0 (engine_core.h L16218) — a private `(s32, s16 *)`
 * definition also match_one-MATCHes but breaks the real TU with
 * `conflicting types`.  The s16 reads are cast at the use site. */

#include "../shared/ov/func_8015C030.h"


#include "../shared/ov/func_8015C08C.h"


#include "../shared/ov/func_8015C0C4.h"



extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80147324(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern int func_80148AFC(void *a0);
extern s32 func_80149FB0(s32 a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_8014CC28(s32 a0);
extern void func_8014D738(void);
extern s32 func_8014F3E8(s32 a0);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);



s32 func_8015C128(s32 param_1) {

    extern void (*D_80184B44[])(void *);

    extern u16 D_800B99DA;
    extern void func_8015C6E0(s32*);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_80184B44[*(u16 *)((int)param_1)](((int)param_1));
        ((void (*)(int))func_8015C6E0)(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_80184B44[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}




extern u16 D_800B99DA;

extern s32 func_80149FB0(s32 a0);
extern s32 func_801496D4(void*);
extern void func_80149704(void);
extern s32 func_801619A4(s32*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_801498E0(s32*);
extern s32 func_80149954(s32);
extern s32 func_80149A64(s32*);
extern void func_800CCCC0(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_8014D738(void);
extern void func_8014CC28(s32);
extern s32 func_8014F3E8(s32);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_80159BE4(s32 a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015C6E0(s32*);

void func_8015C32C(s32 arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern void (*D_80184B44[])(void *);
    s32 iVar2;
    u32 uVar4;
    s32 vin[4];
    s32 vout[4];

    func_80149FB0(arg0);
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
    }
    if ((func_80148AFC((void *)arg0) & 0xff) != 0) {
        vin[0] = 0;
        vin[1] = 0;
        vin[2] = -0x4000;
        func_8001382C((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), vin, vout);
        *(s32 *)(arg0 + 0x234) += vout[0];
        *(s32 *)(arg0 + 0x238) += vout[1];
        *(s32 *)(arg0 + 0x23c) += vout[2];
    }
    func_8001382C((s16)-*(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12), (void *)(arg0 + 0x234), vout);
    func_80146DB8((s32 *)arg0, vout);
    func_80147A84(arg0);
    ((void (*)(s32))func_801473EC)(arg0);
    if ((D_800B99DA & 3) == 0) {
        func_8014C010(arg0, 1);
        func_80147324(0x65f);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    iVar2 = ((s32 (*)(s32))func_8014CC28)(arg0);
    uVar4 = ((u32 (*)(s32))func_8014F3E8)(arg0);
    if (uVar4 != 0) {
        if ((uVar4 & 0x4000) == 0) {
            if (func_80146E98(arg0) != 0) {
                D_80184B44[*(u16 *)arg0]((void *)arg0);
                func_80147078((s32 *)arg0, 0);
                func_80159BE4(arg0);
            }
        } else {
            func_80147078((s32 *)arg0, 4);
            func_8015C0C4(arg0);
        }
    } else {
        if (iVar2 == 0) {
            D_80184B44[*(u16 *)arg0]((void *)arg0);
            func_80147078((s32 *)arg0, 3);
            ((void (*)(s32))func_8015BE94)(arg0);
        }
    }
}

void func_8015C6A4(void) {
}

#include "../shared/ov/func_8015C6AC.h"


#include "../shared/ov/func_8015C6E0.h"




void func_8015C714(void *a0) {

    extern void (*D_80184CD0[])(void);
    D_80184CD0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015C750.h"


#include "../shared/ov/func_8015C788.h"



// @class: struct
// @stuck: none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80149704(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);


void func_8015C7E4(u16 *param_1)
{

    extern void (*D_80184B44[])(void*);
    extern int D_80184AE8;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_80184B44)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_80184B44)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184AE8);
                        ((void (*)(u16 *, s32))func_80146E90)(param_1, 0x14);
                        ((void (*)(u16 *))func_80146CA0)(param_1);
                    }
                    if ((param_1[0x5c] & 0x2000) != 0) {
                        ((void (*)(u16 *, s32))func_80161C24)(param_1, param_1[0xb7]);
                        ((void (*)(u16 *, s32))func_8014C010)(param_1, 2);
                    }
                }
            }
        }
    }
    return;
}




// @class: struct
// @stuck: none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


void func_8015C944(int param_1) {

    extern void (*D_80184B44[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_80184B44[*(unsigned short *)param_1])(param_1);
        ((void (*)(int, int))func_80147078)(param_1, 0);
        ((void (*)(int))func_80159B70)(param_1);
    } else {
        if (((int (*)(int))func_80161240)(param_1) == 0) {
            if (func_80146E98(param_1) != 0) {
                ((void (*)(int))func_80146CA0)(param_1);
            }
            if ((*(unsigned short *)(param_1 + 0xb8) & 0x2000) != 0) {
                func_80161C24(param_1, *(unsigned short *)(param_1 + 0x16e));
            }
        }
    }
}



// @class: schedule
// @stuck: none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80161240(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80149704(void);


void func_8015CA28(u16 *param_1) {

    extern void (*D_80184B44[])(void*);
    extern int D_80184AE8;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_80184B44)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184AE8);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_80184B44)[*param_1](param_1);
    ((void (*)(u16 *, int))func_80147078)(param_1, 0);
    ((void (*)(u16 *))func_80159B70)(param_1);
    return;
do161240:
    ((void (*)(u16 *))func_80161240)(param_1);
}


#include "../shared/ov/func_8015CB94.h"


void func_8015CBCC(void) {
}

void func_8015CBD4(void) {
}

void func_8015CBDC(void) {
}

void func_8015CBE4(void) {
}

void func_8015CBEC(void) {
}

void func_8015CBF4(void) {
}

void func_8015CBFC(void) {
}

void func_8015CC04(void) {
}

#include "../shared/ov/func_8015CC0C.h"


#include "../shared/ov/func_8015CC40.h"


#include "common.h"

extern void (*D_80184CE0[])(void);

void func_8015CC74(void *a0) {
    D_80184CE0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015CCB0.h"


#include "../shared/ov/func_8015CCD0.h"



extern void func_80146D90(s32 a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern s32 func_8014891C(s32 a0);
extern s32 func_80148980(u8 *a0);
extern s32 func_801489E8(s32 a0);
extern s32 func_80148A48(s32 a0);
extern int func_80148AFC(void *a0);
extern s32 func_801496D4(void *a0);
extern void func_80149724(void);
extern s32 func_80149FB0(s32 a0);
extern void func_8014E434(void);
extern void func_8014FA04(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725E0(u8 *a0);





s32 func_8015CD20(s32 arg0) {

    extern void (*D_80184B44[])(void *);
    extern u8 D_80184AF8;
    extern u8 D_80184CE8;
    extern u8 D_80184CF8;

    s32 temp_v0;
    s32 var_v0;
    struct Sub_8015CD20 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(struct Ent_8015CD20 *))func_801496D4)(((struct Ent_8015CD20 *)arg0)) != 0) {
        D_80184B44[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((struct Ent_8015CD20 *)arg0)->unk1BC = 0xA;
        ((s32(*)(struct Ent_8015CD20 *))func_80149724)(((struct Ent_8015CD20 *)arg0));
        if (((s32(*)(struct Ent_8015CD20 *))func_80148AFC)(((struct Ent_8015CD20 *)arg0)) & 0xFF) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80184AF8);
        } else {
            ((void(*)(struct Ent_8015CD20 *))func_80146D90)(((struct Ent_8015CD20 *)arg0));
        }
        return;
    }
    temp_v0 = ((struct Ent_8015CD20 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(struct Ent_8015CD20 *))func_80148980)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80184CE8);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x15);
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0xAA;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_8014891C)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80184CF8);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x14);
            ((struct Ent_8015CD20 *)arg0)->unkB8 = 1;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_801489E8)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 + 0x71;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_80148A48)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0x71;
block_13:
            sp->unk12 = var_v0 & 0xFFF;
        }
    } else {
        ((struct Ent_8015CD20 *)arg0)->unk234 = temp_v0 - 1;
    }
    ((void(*)(struct Ent_8015CD20 *))func_8014FA04)(((struct Ent_8015CD20 *)arg0));
    if (((s32(*)(struct Ent_8015CD20 *))func_8014E434)(((struct Ent_8015CD20 *)arg0)) == 0) {
        D_80184B44[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((void(*)(struct Ent_8015CD20 *, s32))func_80147078)(((struct Ent_8015CD20 *)arg0), 0);
        ((void(*)(struct Ent_8015CD20 *))func_80159B70)(((struct Ent_8015CD20 *)arg0));
    } else {
        ((void(*)(struct Ent_8015CD20 *))func_801725E0)(((struct Ent_8015CD20 *)arg0));
    }
}


#include "../shared/ov/func_8015CF24.h"


#include "../shared/ov/func_8015CF58.h"


#include "../shared/ov/func_8015CF8C.h"


#include "common.h"

extern void (*D_80184D18[])(void);

void func_8015CFC0(void *a0) {
    D_80184D18[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015CFFC.h"


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_80184D08;

    int iVar4;
    register unsigned short uVar1 __asm__("$19");
    register unsigned short uVar5 __asm__("$17");
    short sVar2;
    short sVar3;

    ((void (*)(int, void *))func_80154274)(param_1, &D_800D550C);
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    iVar4 = *(short *)(*(int *)(param_1 + 0x20) + 0x12);
    uVar1 = *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x180) + 0x20) + 0x12);
    uVar5 = (uVar1 + 0x800) & 0xfff;
    sVar2 = func_80012A60(iVar4, (short)uVar1);
    sVar3 = func_80012A60(iVar4, uVar5);
    if (sVar2 < sVar3) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar1;
    } else {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar5;
    }
    *(int *)(param_1 + 0x38) = (int)&D_80184D08 | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}




// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {

    extern void (*D_80184B44[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((void (*)(void *))func_801725F4)(arg0);
        *(s32 *)((u8 *)arg0 + 0x234) = 0xFF1D0000;
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10) = 0x600;
        *(u16 *)((u8 *)arg0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10);
        func_80146CA0(arg0);
    }
}



extern s32 func_80149FB0(s32);
extern void func_80147324(s32 a0);
extern u16  func_80148800(s32 *a0);
extern void func_80149724(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146DB8(s32*, s32*);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_8014FA04(s32);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void*);
extern void func_8015D380(s32);
extern s32  func_801725F4(u8 *a0);


void func_8015D1B8(s32 *a0)
{

    extern void (*D_80184B44[])(void*);
    extern s32 D_80184D24;
    extern s32 D_80184D28;
    extern s32 D_80184D6C;
    extern s32 D_800D4C14;
    s32 sum;
    s32 keep;
    s32 obj;
    s16 cur;
    s16 prev;
    s16 d;
    s32 off;
    s32 *p;
    s32 dummy[2]; /* L1: dead, but its stack slot is what makes the frame 0x38 */

    ((void (*)(void))func_80149FB0)();
    obj = *(s32 *)((u8 *)a0 + 0x20);
    sum = *(u16 *)(obj + 0x10) + *(u16 *)((u8 *)a0 + 0x236);
    *(u16 *)(obj + 0x10) = sum & 0xFFF;
    keep = sum; /* L2: AFTER the store — this is what keeps the $s0 copy alive */

    cur = *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x10);
    prev = *(s16 *)((u8 *)a0 + 0x244);
    if (cur - prev >= 0) {
        d = cur - prev;
    } else {
        d = prev - cur;
    }
    if (d > 0x800) {
        func_80147324(0x5E9);
    }
    *(u16 *)((u8 *)a0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x10);

    if (func_80148800(a0) & 0x40) {
        ((void (**)(s32*))D_80184B44)[*(u16 *)a0](a0);
        ((void (*)(s32 *))func_80149724)(a0);
        func_80154274(a0, (s32)&D_800D4C14);
        func_80146E90(a0, 0x10);
        {
            u32 t = keep & 0xFFF; /* L3: unsigned value, signed guard -> bgez + srl */
            if ((s32)t < 0) {
                t += 0x1FF;
            }
            p = &D_80184D6C; /* L4 + scheduling: the `la` must precede the srl/sll pair */
            off = (t >> 9) * 8;
        }
        *p = *(s32 *)((u8 *)&D_80184D24 + off);
        ((void (*)(s32 *, s32))func_80146DB8)(a0, (s32)(p - 2)); /* 0x801893D8 == &D_80184D6C[-2] (no label there) */
        func_801477E8(a0, *(s32 *)((u8 *)&D_80184D28 + off));
        func_80147324(0x5EA);
    } else {
        ((void (*)(s32 *))func_8014FA04)(a0);
        if (((s32 (*)(s32 *))func_8014E6A0)(a0) == 0) {
            ((void (**)(s32*))D_80184B44)[*(u16 *)a0](a0);
            func_80147078(a0, 0);
            ((void (*)(s32 *))func_80159B70)(a0);
        } else {
            ((void (*)(s32 *))func_8015D380)(a0);
            func_801725F4(a0);
        }
    }
}




// @class: regalloc-order
// @stuck: pinning a0->$s1 and buffer-ptr->$s0; body copy already matches
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void *memcpy(void *dst, const void *src, u32 n);


void func_8015D380(s32 a0) {

    extern s32 D_80184D74;
    s16 out[4];
    s32 buf[8];
    register s32 s1 __asm__("$17") = a0;
    register s32 *s0 __asm__("$16") = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)s0, (void *)&D_80184D74, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}



// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_80183E58[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_80183E58;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


#include "../shared/ov/func_8015D480.h"


#include "../shared/ov/func_8015D4B4.h"


#include "common.h"

extern void (*D_80184D7C[])(void);

s32 func_8015D4E8(void *a0)
{
    D_80184D7C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015D524.h"


#include "../shared/ov/func_8015D544.h"


#include "../shared/ov/func_8015D57C.h"



// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);


void func_8015D5E8(int param_1)
{

    extern unsigned char D_80184D88[];
    int iVar1;
    int iVar2;

    if (((int (*)(void))func_80161B18)() != 0)
        return;
    if (((int (*)(int))func_80161B84)(param_1) != 0)
        return;
    if ((*(unsigned short *)(param_1 + 0xb8) & 0x4000) != 0)
        func_80154A74(param_1, 0x17);
    if (((int (*)(int))func_80161208)(param_1) != 0)
        return;
    if (*(unsigned short *)(param_1 + 0xb8) == 0x8000) {
        *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + -3;
        func_80154150(param_1, 0x1a);
        ((void (*)(int))func_80146CA0)(param_1);
    } else {
        iVar1 = *(int *)(param_1 + 0x178);
        if (iVar1 != 0) {
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 6) =
                (short)((signed char)D_80184D88[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_80184D88[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_80184D88[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}



extern int func_80148AFC(void*);
extern s32 func_80161B18(void *);
extern s32 func_80161B84(void *);
extern u16 func_80148800(s32*);
extern u8 func_8014BEF8(void);
extern s32 func_80165624(s32);
extern s32 func_801488A8(u8*);
extern void func_8014D738(void);
extern s32 func_80161208();
extern void func_80154A74(s32, s32);
extern void func_8015DAC4(s32*);
extern void func_8015DE24(s32*);
extern void func_8015DA5C(s32);
extern void func_8015F948(s32*);
extern void func_800CAF14(void *);
extern void func_80154150(s32, s32);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80149374(s32, s32);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *);
extern void func_8015C714(void *);
extern void func_801483E8(unsigned char*);


void func_8015D738(void *arg0) {

    extern u8 D_80078E78[];
    extern u8 D_80184D88[];

    extern u8 D_80184B08[];
    extern u8 D_80184B18[];
    u8 *p = D_80078E78;
    s32 s1;
    ((void (*)(void))func_80148AFC)();
    if (func_80161B18(arg0) != 0) return;
    if (func_80161B84(arg0) != 0) return;
    s1 = *(s32 *)((char *)arg0 + 0x178);
    if (s1 != 0) {
        if (*(u16 *)s1 == 0x360) goto block_808;
    }
    __asm__ __volatile__("");
    if (s1 != 0) {
        if (*(u16 *)s1 != 0) goto block_7F4;
    }
    D_80184B44[*(u16 *)arg0](arg0);
    ((void (*)(void *, s32))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
block_7F4:
    if (((s32 (*)(void *))func_80148800)(arg0) & 0x80) {
    block_808:
        ((void (*)(void *, s32))func_80154A74)(arg0, 0x11);
        ((void (*)(void *))func_8015DAC4)(arg0);
        return;
    }
    if ((((s32 (*)(void *))func_80148800)(arg0) & 0x10) && ((s32 (*)(void *))func_8014BEF8)(arg0) != 0) {
        ((void (*)(void *, s32))func_80154A74)(arg0, 0x11);
        ((void (*)(void *))func_8015DE24)(arg0);
        return;
    }
    if ((((s32 (*)(void *))func_80148800)(arg0) & 0x20) && p[0x49] == 0xA) {
        if (((s32 (*)(void *))func_80165624)(arg0) != 0) {
            ((void (*)(void *))func_8015DA5C)(arg0);
            ((void (*)(void *))func_8015F948)(arg0);
            return;
        }
        ((void (*)(void *, s32))func_80154A74)(arg0, 0x11);
        func_800CAF14(arg0);
        return;
    }
    if (((s32 (*)(void *))func_801488A8)(arg0) != 0 && *(u16 *)(*(s32 *)((char *)arg0 + 0x178)) != 0x82) {
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1B);
        ((void (*)(void *, void *))func_80146DB8)(arg0, &D_80184B08);
    } else {
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1A);
        ((void (*)(void *, void *))func_80146DB8)(arg0, &D_80184B18);
    }
    ((void (*)(void *))func_80147A84)(arg0);
    ((void (*)(void *))func_801473EC)(arg0);
    s1 = *(s32 *)((char *)arg0 + 0x178);
    *(s16 *)(s1 + 6) = (s16)((s8)D_80184D88[*(s32 *)((char *)arg0 + 0x234)] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xc));
    *(s16 *)(s1 + 0xa) = (s16)((s8)D_80184D88[*(s32 *)((char *)arg0 + 0x234) + 1] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xe));
    *(s16 *)(s1 + 0xe) = (s16)((s8)D_80184D88[*(s32 *)((char *)arg0 + 0x234) + 2] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0x10));
    ((void (*)(void *, void *))func_80149374)(arg0, (void *)(s1 + 4));
    *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = (*(u16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x12) + 0x800) & 0xFFF;
    if (((s32 (*)(void *))func_8014D738)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (func_80161208(arg0) != 0) return;
    ((void (*)(void *))func_801483E8)(arg0);
}


#include "../shared/ov/func_8015DA5C.h"


#include "../shared/ov/func_8015DA90.h"


#include "../shared/ov/func_8015DAC4.h"


#include "common.h"

extern void (*D_80184DBC[])(void);

void func_8015DAF8(void *a0) {
    D_80184DBC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015DB34.h"


#include "../shared/ov/func_8015DB6C.h"



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_80184B44[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


#include "../shared/ov/func_8015DC84.h"



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {

    extern s8 D_80184DC4[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


#include "../shared/ov/func_8015DD74.h"


#include "../shared/ov/func_8015DDF0.h"


#include "../shared/ov/func_8015DE24.h"


#include "common.h"

extern void (*D_80184DDC[])(void);

void func_8015DE58(void *a0) {
    D_80184DDC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015DE94.h"


#include "../shared/ov/func_8015DECC.h"



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_80184B44[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


#include "../shared/ov/func_8015DFE4.h"



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {

    extern s8 D_80184DC4[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80184DC4[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


#include "../shared/ov/func_8015E0D4.h"


#include "../shared/ov/func_8015E150.h"


#include "../shared/ov/func_8015E184.h"


#include "common.h"

extern void (*D_80184DFC[])(void);

s32 func_8015E1B8(void *a0)
{
    D_80184DFC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015E1F4.h"


#include "../shared/ov/func_8015E22C.h"


#include "../shared/ov/func_8015E288.h"



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);


void func_8015E344(u16 *param_1)
{

    extern void (*D_80184B44[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_80184B44)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


#include "../shared/ov/func_8015E40C.h"



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{

    extern u16 D_80184E0C;
    extern u16 D_80184E0E;
    extern u16 D_80184E10;
    extern s32 D_80184E14;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80184E0C + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80184E0E + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80184E10 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_80184E14, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


extern s32 func_8013C9C4(s32 *a0);
void func_8015E588(void) {

    extern s32 D_80184E1C;
    func_8013C9C4(&D_80184E1C);
}


#include "../shared/ov/func_8015E5B0.h"



// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */

void func_8015E698(u16 *param_1)
{

    extern void (*D_80184B44[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_80184B44)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


#include "../shared/ov/func_8015E714.h"


#include "../shared/ov/func_8015E84C.h"


#include "../shared/ov/func_8015E880.h"


#include "../shared/ov/func_8015E8B4.h"


#include "common.h"

extern void (*D_80184E30[])(void);

void func_8015E8E8(void *a0) {
    D_80184E30[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015E924.h"


#include "../shared/ov/func_8015E95C.h"


#include "../shared/ov/func_8015E9B8.h"



extern u16 func_801487F4(s32*);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *a0);
extern s32 func_80149D10(s32);
extern void func_80175150(s32*);
extern void func_8016EE40(s32, s32, s32);
extern s32 func_80149744(struct S_80149744*);
extern void func_80149788(void);
extern s32 func_80161B84(void *a0);
extern s32 func_8014A4B4(void *a0);
extern void func_8014A4FC(void);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32);
extern s32 func_80148E54(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80154150(s32, s32);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern void func_801483E8(unsigned char*);


void func_8015EA3C(void *arg0) {

    extern void (*D_80184B44[])(void *);
    extern s16 D_801152A0;
    s32 invec[4];
    s32 outbuf[4];
    s32 temp;
    s32 r;

    if (!(((s32 (*)(void))func_801487F4)() & 8)) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    r = ((s32 (*)(void *))func_80149D10)(arg0);
    if (r == 1) goto Lcase1;
    if (r < 2) goto Ldefault;
    if (r == 2) goto Lcase2;
    goto Ldefault;
Lcase1:
    D_80184B44[*(u16 *)arg0](arg0);
    ((void (*)(void *))func_80175150)(arg0);
    return;
Lcase2:
    ((void (*)(s32, s32))func_8016EE40)(*(s32 *)((u8 *)arg0 + 0x21C), 0x01000000);
    return;
Ldefault:
    if (((s32 (*)(void *))func_80149744)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149788)(arg0);
        return;
    }
    if (func_80161B84(arg0) != 0) {
        return;
    }
    if (func_8014A4B4(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_8014A4FC)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149AA8)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149AD4)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149B54)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149BAC)(arg0);
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) =
            ((*(u16 *)&D_801152A0) + ((s32 (*)(void *))func_801491C4)(arg0)) & 0xFFF;
    }
    temp = func_80148E54(arg0);
    if ((s16)temp >= 0) {
        s32 d = temp - *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12);
        invec[0] = 0;
        invec[1] = 0;
        invec[2] = 0xFFFC0000;
        func_8001382C((s16)d, invec, outbuf);
        ((void (*)(void *, void *))func_80146DB8)(arg0, outbuf);
        ((void (*)(void *))func_80147A84)(arg0);
        ((void (*)(void *))func_801473EC)(arg0);
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1E);
    } else {
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1D);
    }
    if (((s32 (*)(void *))func_8014D738)(arg0) != 0) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80161208)(arg0) == 0) {  /* §17a-1 */
        ((void (*)(void *))func_801483E8)(arg0);
    }
}


#include "../shared/ov/func_8015ED6C.h"


#include "../shared/ov/func_8015EDA0.h"


#include "../shared/ov/func_8015EDD4.h"


#include "common.h"

extern void (*D_80184E38[])(void);

s32 func_8015EE08(void *a0)
{
    D_80184E38[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015EE44.h"



// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);


void func_8015EE7C(s32 param_1)
{

    extern int D_800D4C48;
    extern int D_80184B28;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_80184B28);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}




extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_8015EEE0(void *arg0)
{

    extern void (*D_80184B44[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}


void func_8015EF9C(void) {
}

#include "../shared/ov/func_8015EFA4.h"


#include "../shared/ov/func_8015EFD8.h"


#include "common.h"

extern void (*D_80184E40[])(void);

void func_8015F00C(void *a0) {
    D_80184E40[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015F048.h"


#include "../shared/ov/func_8015F080.h"


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {

    extern s32 D_80062BE8;
    extern void (*D_80184B44[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_80184B44[*(u16 *)a0])(a0);
        ((void (*)(void *, s32))func_80147078)(a0, 0);
        func_80159B70(a0);
    } else {
        if (flag & 0x4000) {
            ((void (*)(s32))func_8014AB5C)(0x19);
            ((void (*)(s32))func_8014AB5C)(0x1D);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 1, 0, 1);
            func_801466F0(0x1D, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_80019064(&D_80062BE8);
            func_80147324(0x9DA);
        }
        if (((s32 (*)(s32 *))func_80161208)(a0) == 0) {
            func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
        }
    }
}


#include "../shared/ov/func_8015F260.h"


#include "../shared/ov/func_8015F2BC.h"


#include "../shared/ov/func_8015F2F0.h"


#include "common.h"

extern void (*D_80184E48[])(void);

void func_8015F324(void *a0) {
    D_80184E48[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015F360.h"


#include "../shared/ov/func_8015F380.h"




extern s32 func_80149884(void);
extern s32 func_801496D4(void*);
extern void func_80149724(void);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_80146DB8(s32*, s32*);
extern void func_80146E90(s32*, s32);
extern void func_8014ED28(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_801725B8(u8*);
extern void func_80147324(s32 a0);
extern void func_80019064(void*);
extern void func_801484B0(s32, s32);
extern void func_80148534(s32, s32);

void func_8015F448(s32 arg0) {

    extern void (*D_80184B44[])(void *);

    extern u8 D_80062BD0;
    extern s32 D_80184E50;
    extern s32 D_80184E60;
    extern s32 D_80184E70;
    s32 sp20[2];
    s32 sp28[2];

    if (((*(u32 *)(arg0 + 0x44) & 0x100) && (func_80149884() != 0)) ||
        (((s32 (*)(s32))func_801496D4)(arg0) != 0)) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0);
        return;
    }

    if (*(u8 *)(arg0 + 0x245) == 0) {
        if (*(u8 *)(arg0 + 0x244) == 0) {
            if (((s32 (*)(s32))func_80148800)(arg0) & 0x10) {
                *(u8 *)(arg0 + 0x244) = 1;
                *(u8 *)(arg0 + 0x245) = 1;
            }
        } else if (((s32 (*)(s32))func_80148800)(arg0) & 0x80) {
            *(u8 *)(arg0 + 0x244) = 0;
            *(u8 *)(arg0 + 0x245) = 1;
        }
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x3000) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            ((void (*)(void *, void *))func_801484B0)(sp20, sp28);
            func_80147324(0x56D);
        } else {
            ((void (*)(void *, void *))func_80148534)(sp20, sp28);
            func_80147324(0x56E);
        }
        ((void (*)(s32 *))func_80019064)(&(*(s32 *)&D_80062BD0));
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 0, 0);
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 1, 0);
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
        if (*(u8 *)(arg0 + 0x245) != 0) {
            *(u8 *)(arg0 + 0x245) = 0;
            *(u16 *)(arg0 + 0xB8) = *(u16 *)(arg0 + 0xBA);
            if (((s32 (*)(s32))func_80148980)(arg0) != 0) {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184E50);
            } else {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184E60);
            }
        }
    } else {
        *(u16 *)(arg0 + 0x246) = *(u16 *)(arg0 + 6);
        *(u16 *)(arg0 + 0x248) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(arg0 + 0x24A) = *(u16 *)(arg0 + 0xE);
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (((s32 (*)(s32))func_8014F1F4)(arg0) != 0) {
            *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 0x246);
            *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x248);
            *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x24A);
        }
    }

    if (((s32 (*)(s32))func_8014FCFC)(arg0) == 0) {
        D_80184B44[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFE80000);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184E70);
        ((void (*)(s32, s32))func_80146E90)(arg0, 0x10);
        return;
    }

    func_8014ED28(arg0);
    func_8014FA04(arg0);
    ((void (*)(s32))func_801725B8)(arg0);
}


#include "../shared/ov/func_8015F738.h"


#include "../shared/ov/func_8015F76C.h"


#include "../shared/ov/func_8015F7A0.h"


#include "common.h"

extern void (*D_80184E80[])(void);

s32 func_8015F7D4(void *a0)
{
    D_80184E80[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015F810.h"


#include "../shared/ov/func_8015F848.h"



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208();

void func_8015F89C(void *arg0) {

    extern void (*D_80184B44[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_80184B44[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


#include "../shared/ov/func_8015F948.h"



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_8015F9A4(void *arg0) {

    extern void (*D_80184B44[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_80184B44[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


#include "../shared/ov/func_8015FA24.h"


#include "../shared/ov/func_8015FA44.h"


#include "../shared/ov/func_8015FA78.h"


extern void (*D_80184E8C[])(void);

    void func_8015FAAC(void *a0) {
        D_80184E8C[*(u16 *)((s32)a0 + 0x2)]();
    }



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_80184B44[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_80184B44[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147324(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80146CA0(void *a0);


void func_8015FBE0(s32 *param_1)
{

    extern void (*D_80184B44[])(void *);
    extern u8 D_80078EC1;
    extern u16 D_801270C0;
    extern u8 D_800B9A17;
    if (param_1[0x61] < 0) {
        ((void (**)())D_80184B44)[*(u16 *)param_1]();
        ((void (*)(s32 *, s16))func_80147078)(param_1, 0);
        ((void (*)(s32 *))func_80159B70)(param_1);
    } else {
        __asm__ __volatile__("");
        D_80078EC1 = 0;
        ((void (*)(s32 *, s32))func_80154150)(param_1, 0x20);
        ((void (*)(s32 *, s32))func_80154A74)(param_1, 0x18);
        ((void (*)(s32, s32 *, s32, s32, s32, s32, s32))func_80146A6C)(0x16, param_1, 0, 0, 0, 0, 0);
        func_80147324(0x44F);
        ((void (*)(s32 *))func_801553A8)(param_1);
        ((void (*)(s32 *))func_801553C0)(param_1);
        D_801270C0 = 2;
        D_800B9A17 = 0;
        ((void (*)(s32 *))func_80146CA0)(param_1);
    }
}




// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)


extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_80184B44[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_80184B44[*(u16 *)param_1](param_1);
        ((void (*)(void *, s32))func_80147078)(param_1, 0);
        func_80159B70(param_1);
    } else {
        *(u8 *)((s32)param_1 + 0x197) = 0;
        *(u8 *)((s32)param_1 + 0xBE) = 0;
        *(u8 *)((s32)param_1 + 0xBF) = 0;
        *(u8 *)((s32)param_1 + 0x1A0) = (u8)*(s32 *)((s32)param_1 + 0x184);
        ((s32 (*)(void *, s32))func_8014BFF4)(param_1, 1);
        func_80146CA0(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple 3-call sequence with global table index


extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{

    extern unsigned int D_80184EA0[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_80184EA0[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


#include "../shared/ov/func_8015FDCC.h"



// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{

    extern void (*D_80184B44[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_80184B44)[param_1[0]]();
            ((void (*)(u16 *, s16))func_80147078)(param_1, 0);
            ((void (*)(u16 *))func_80159B70)(param_1);
            return;
        }
        param_1[0x5c] = param_1[0x5d];
    }
    if ((param_1[0x5c] & 0x4000) != 0) {
        ((void (*)(u16 *, s16))func_80154A74)(param_1, 0x11);
    }
    ((void (*)(u16 *))func_80161208)(param_1);
}




extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

void func_8015FF20(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_80184B44[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_80184B44[*(u16 *)param_1](param_1);
        ((void (*)(void *, s16))func_80147078)(param_1, 0);
        func_80159B70(param_1);
        return;
    }

    v2 = *(s32 *)((s32)param_1 + 0x184);
    if (v2 < 0) {
        func_80150820((s32)param_1, func_801656E8((s32)param_1, v2 & 0xFF) & 0xFF);
    } else {
        if (*(u8 *)((s32)param_1 + 0x1A0) != *(u8 *)((s32)param_1 + 0x196)) {
            *(u8 *)((s32)param_1 + 0x1A0) = (u8)v2;
            *(u8 *)((s32)param_1 + 0x197) = 0;
            *(u8 *)((s32)param_1 + 0xBE) = 0;
            *(u8 *)((s32)param_1 + 0xBF) = 0;
            func_8014BFF4((s32)param_1, 1);
        }

        cur = *(u8 *)((s32)param_1 + 0x1A0);
        D_80078EC1 = cur;
        D_80078EC2 = cur;
        func_80165670((s32)param_1, cur);
        ((void (*)(void *))func_80165840)(param_1);
        ((void (*)(void *))func_801658DC)(param_1);
        func_80154A74((s32)param_1, 0x11);
        D_801270C0 = 1;
    }

    ((void (*)(void *))func_8016004C)(param_1);
}


#include "../shared/ov/func_8016004C.h"


#include "../shared/ov/func_8016007C.h"


#include "../shared/ov/func_801600D0.h"


#include "../shared/ov/func_80160104.h"


extern void (*D_80184F1C[])(void);

    void func_80160138(void *a0) {
        D_80184F1C[*(u16 *)((s32)a0 + 0x2)]();
    }


#include "../shared/ov/func_80160174.h"


#include "../shared/ov/func_801601AC.h"


#include "../shared/ov/func_801601E4.h"


#include "../shared/ov/func_80160244.h"



extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {

    extern void (*D_80184B44[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_80184B44)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


void func_8016032C(void) {
}

#include "../shared/ov/func_80160334.h"


#include "../shared/ov/func_80160368.h"


extern void (*D_80184F2C[])(void);

    void func_8016039C(void *a0) {
        D_80184F2C[*(u16 *)((s32)a0 + 0x2)]();
    }


#include "../shared/ov/func_801603D8.h"


#include "../shared/ov/func_80160410.h"








/* data */

/* callees (engine_core.h canonical sigs) */
extern void func_80149020(s32 *a0);
extern void func_80149034(s32 *a0);
extern u16  func_80148800(s32 *a0);
extern s32  func_80149B54(s32 *a0);
extern void func_80149BAC(s32 *a0);
extern s32  func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32  func_80146E98(s32 a0);
extern u16  func_801487F4(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_80159B70(void *a0);
extern s32  func_800CF8B4();
extern s32  func_801491C4(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32  func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F00C();

void func_80160534(u8 *p) {

    extern u8  D_80078EC0;
    extern u8  D_80078EBF;
    extern s16 D_801152A0;
    extern void (*D_80184B44[])(void *);
    func_80149020((s32 *)p);
    func_80149034((s32 *)p);
    if ((D_80078EC0 & 0x7F) != 0 && (func_80148800((s32 *)p) & 0x90) != 0) {
        if (D_80078EBF == 0x80) {
            D_80184B44[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x13);
            func_8015F00C((s32 *)p);
            return;
        }
        if (func_80149B54((s32 *)p) != 0) {
            D_80184B44[*(u16 *)p](p);
            func_80149BAC((s32 *)p);
            return;
        }
    }
    if (func_80149AA8((s32 *)p) != 0) {
        D_80184B44[*(u16 *)p](p);
        func_80149AD4((s32 *)p);
        return;
    }
    if (func_80146E98((s32)p) != 0) {
        if ((func_801487F4((s32 *)p) & 8) != 0) {
            D_80184B44[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x11);
            func_8015E9B8((s32 *)p);
        } else {
            D_80184B44[*(u16 *)p](p);
            func_80147078((s32 *)p, 0);
            func_80159B70(p);
        }
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
            ((*(u16 *)&D_801152A0) + func_801491C4((s32)p)) & 0xFFF;
    }
    func_80147AD4((s32)p, *(s32 *)(p + 0x234), *(s32 *)(p + 0x238),
                  *(s32 *)(p + 0x23C));
    func_801473EC((s32 *)p);
    if (((s32 (*)(s32 *))func_8014D738)((s32 *)p) != 0) {
        D_80184B44[*(u16 *)p](p);
        func_80147078((s32 *)p, 9);
        func_8015C714(p);
    } else {
        ((s32 (*)(void *))func_80161208)(p);
    }
}


#include "../shared/ov/func_801607B8.h"


#include "../shared/ov/func_801607E4.h"


#include "../shared/ov/func_80160818.h"


extern void (*D_80184F34[])(void);

    void func_8016084C(void *a0) {
        D_80184F34[*(u16 *)((s32)a0 + 0x2)]();
    }


#include "../shared/ov/func_80160888.h"


#include "../shared/ov/func_801608C0.h"



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)



extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_80184B44[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_80184B44)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))func_80154150)(param_1, 0x25);
            ((void (*)(unsigned short *))func_80146CA0)(param_1);
        }
    }
    return;
}




// @class: struct
// @stuck: none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */

void func_801609B8(u16 *param_1) {

    extern void (*D_80184B44[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_80184B44)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


#include "../shared/ov/func_80160A28.h"


#include "../shared/ov/func_80160A74.h"


#include "../shared/ov/func_80160ACC.h"


#include "../shared/ov/func_80160B00.h"


extern void (*D_80184F40[])(void);

    s32 func_80160B34(void *a0)
{
        D_80184F40[*(u16 *)((s32)a0 + 0x2)]();
    }


#include "../shared/ov/func_80160B70.h"


#include "../shared/ov/func_80160BB4.h"


#include "../shared/ov/func_80160C28.h"


#include "../shared/ov/func_80160CB4.h"



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_80184B44 + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_80184B44[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_80184B44[*(u16 *)arg0](arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x1AC) == 0) {
            if ((((s32 (*)(void *))func_80148800)(arg0) & 0xF0) == 0) {
                goto dd0;
            }
        } else {
            s32 t = *(s32 *)((u8 *)arg0 + 0x1AC) - 0xAAA8;
            *(s32 *)((u8 *)arg0 + 0x1AC) = t;
            if (t >= 0) {
                goto dd0;
            }
        }
        D_80184B44[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


#include "../shared/ov/func_80160DEC.h"


#include "../shared/ov/func_80160E3C.h"


#include "../shared/ov/func_80160E70.h"




void func_80160EA4(void *a0) {

    extern void (*D_80184F50[])(void);
    D_80184F50[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80160EE0.h"


#include "../shared/ov/func_80160F00.h"


#include "../shared/ov/func_80160F70.h"


#include "../shared/ov/func_80160FE0.h"



// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{

    extern void (*D_80184B44[])(void *);
    func_80149020(a0);
    D_80184B44[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


#include "../shared/ov/func_80161094.h"


void func_801610FC(void) {
}

#include "../shared/ov/func_80161104.h"




extern void func_801483E8(unsigned char *self);
extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80149184(s32 a0);
extern void func_801553A8(s32 *a0);
extern s32 func_801725A4(u8 *a0);
extern s32 func_80161A60(s32 a0);
extern void func_80147324(s32 a0);

void func_80161124(void *a0)
{
    extern s16 D_801152A0;
    u8 *self = (u8 *)a0;

    *(s16 *)(self + 0x24A) = 0;
    ((void (*)(void))func_801483E8)();
    func_8014CBF8(a0);
    func_801474EC((s32 *)a0);
    if (*(s32 *)(self + 0x2C) < (s32)0xFFF46000) {
        *(s32 *)(self + 0x2C) = 0xFFF46000;
    }
    if ((*(s32 *)(self + 0x24) | *(s32 *)(self + 0x2C)) != 0) {
        func_80154150((s32)self, 0xF);
    } else {
        func_80154150((s32)self, 0xD);
    }
    func_80154A74((s32)self, 0x22);
    *(s32 *)(self + 0x5C) = 0;
    *(s32 *)(self + 0x240) = 0;
    func_80146E90((s32 *)self, 4);
    D_801152A0 = func_80149184((s32)self);
    func_801553A8((s32 *)self);
    func_801725A4((u8 *)self);
    if (func_80161A60((s32)self) != 0) {
        func_80147324(0x8E1);
    }
}



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016130C(void*, s32);
void aF80161208(void *a0) __asm__("func_80161208");
void aF80161208(void *a0)
{
    ((s32 (*)(s32, u32))func_8016130C)(a0, func_801612B8(a0, 0));
}


#include "../shared/ov/func_80161240.h"


#include "../shared/ov/func_80161278.h"


#include "../shared/ov/func_801612B8.h"


extern void func_80161240(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);

/* REDRAFT (decay axis: RETURN TYPE). The stored draft had been flipped to
 * `void` to fit the fleet header decl in src/shared/engine_core.h, while the
 * body still `return 1; / return 0;`. gcc-2.7.2 silently drops the $v0 sets in
 * that situation, costing the three `addiu $v0, $zero, 1` / `addu $v0,$zero,$zero`
 * instructions the ASM plainly has. Restored to s32 (§109/§85 — the single call
 * site `func_8016130C(a0, func_801612B8(a0, 1));` discards the result, so the
 * void->s32 widen is caller-neutral and must be fixed on the HEADER side). */

/* RECONCILE (§37/§124 asm-label alias — zero header touch).
 * Gate error: jr_8015C32C.c:3501 conflicting types for `func_8016130C'
 *             :3479 previous declaration.
 * TU line 3479 is `DEFINE_func_80161240()`, whose expansion (engine_core.h:3781)
 * declares `extern void func_8016130C(void *a0, s32 a1);` — a RETURN-TYPE
 * disagreement with this draft's required `s32`.  The third line the gate quoted
 * (:5228 "location of previous definition") is unrelated noise: it is the
 * pre-existing `#define SHB(x)` redefinition *warning* between TU lines 5227 and
 * 5538, present with or without this draft.
 * Fix: the C identifier becomes aF8016130C, so it never collides with the
 * canonical `void func_8016130C` declaration, while the GNU asm label makes the
 * EMITTED symbol `func_8016130C`.  The macro's caller func_80161240 keeps calling
 * the `extern void` spelling and is byte-unaffected (it discards the return).
 * Codegen for this function is untouched — match_one still MATCH.
 * (Alternative, house style, NOT taken here per the no-header-edit rule: widen
 * src/shared/engine_core.h:3781 to `extern s32 func_8016130C(void *a0, s32 a1);`
 * and rename back to the plain name — byte-identical either way.) */

s32 aF8016130C(void *a0, s32 a1) __asm__("func_8016130C");

s32 aF8016130C(void *a0, s32 a1)
{
    if ((a1 == 0) || (a1 == 0x8000)) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BDD0)(a0);
        return 1;
    }
    if ((a1 & 0x4000) != 0) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BF48)(a0);
        return 1;
    }
    return 0;
}





// @class: schedule
// @stuck: none — MATCH


#include "../shared/ov/func_80161374.h"


#include "../shared/ov/func_80161418.h"


#include "../shared/ov/func_80161450.h"


#include "../shared/ov/func_80161488.h"


#include "../shared/ov/func_801614E4.h"


#include "../shared/ov/func_8016151C.h"


#include "../shared/ov/func_80161554.h"


#include "../shared/ov/func_8016158C.h"


#include "../shared/ov/func_801615C4.h"


#include "../shared/ov/func_8016163C.h"

#include "../shared/ov/func_80161774.h"

#include "../shared/ov/func_80161888.h"

#include "../shared/ov/func_8016191C.h"


#include "../shared/ov/func_8016197C.h"


#include "../shared/ov/func_801619A4.h"


#include "../shared/ov/func_801619D0.h"


#include "../shared/ov/func_80161A00.h"


#include "../shared/ov/func_80161A30.h"


#include "../shared/ov/func_80161A60.h"



#include "../shared/ov/func_80161A90.h"


#include "../shared/ov/func_80161B18.h"


#include "../shared/ov/func_80161B84.h"


s32 func_801497A8(s32 *a0);
void func_801599A4(void *a0);
void func_80149864(void);

s32 func_80161BE0(s32 *a0)
{
    register s32 *s0 asm("s0") = a0;
    s32 result = func_801497A8(s0);
    if (result != 0) {
        func_801599A4((void *)s0);
        ((void (*)(void *))func_80149864)((void *)s0);
        return 1;
    }
    return 0;
}



extern void func_80147324();

/* RECONCILE (§17a-1/§20): the TU already declares
 *   extern void func_80161C24(s32, s32);   (jr_8015C32C.c:1474 / :1417)
 * so the definition must use (int, int); the unsigned semantics of param_2
 * are restored by a cast at each use (codegen-neutral: sltiu + index math). */
void func_80161C24(int param_1, int param_2)
{

    extern unsigned short D_80184F60[];
    extern unsigned short D_80184F62[];

    if ((unsigned int)param_2 < 8) {
        if (*(u8 *)(param_1 + 0xDA) != 0) {
            func_80147324(D_80184F60[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 0;
        } else {
            func_80147324(D_80184F62[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_80184F80[];
    if (param_2 < 8) {
        func_80147324(D_80184F80[param_2]);
    }
    return;
}



// @class: plumbing
// @stuck: none — MATCH (20 ins)
// DECAY AXIS: return type. The stored draft declared `s32 func_80161CD0(...)` with no
// return statement. That kept $v0 live-out at the epilogue, so gcc-2.7.2's delayed-branch
// pass refused to speculatively fill the second `beqz $v0` delay slot from the fall-through
// with `sll $v0, $s0, 1` — costing one extra nop (21 vs 20 ins) and shifting both branch
// displacements. Declaring the function `void` makes $v0 dead at the return and the fill
// happens. Same return-type axis as the wave, opposite direction (s32 -> void).
// param_2 must be UNSIGNED: the guard assembles as `sltiu $v0, $s0, 0x8`.
//
// RECONCILE (§37/§124 asm-label alias) — the ONLY change vs the uc2 draft; the body is
// byte-identical and untouched.
//   The real TU src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c already carries the m2c canonical
//   declaration
//       :23   extern s32 func_80161CD0(s32 a0, s32 a1);   /* match-first, arity 2 */
//       :1207 extern s32 func_80161CD0(s32 a0, s32 a1);
//   so a plain `void func_80161CD0(int, unsigned int)` definition dies with
//       conflicting types for `func_80161CD0' / previous declaration ... (rtu_match CC1 FAIL).
//   This is the RETURN axis (s32 vs void) plus the param-2 signedness axis, and BOTH spellings
//   are load-bearing for the 20-instruction codegen — conforming the definition to the
//   declaration (escape #1) would perturb bytes, so it is not available here.
//   The alias fixes it at T0: the C identifier is aF80161CD0 (no declaration to collide with)
//   while the EMITTED SYMBOL is func_80161CD0. In-TU callers keep using the `extern s32`
//   spelling and are byte-unaffected (they discard the return). Zero tracked files touched;
//   no header edit is even possible/needed — grep shows func_80161CD0 has NO declaration in
//   include/ or src/shared/, the conflict is purely TU-local m2c boilerplate.
//   Exactly the pattern already banked at src/ov_SC03_099/ov_SC03_099_jr_8015C32C.c:3503
//   for the sibling func_8016191C.
//
//   NOTE on the third gate diagnostic (`:5223 note: location of previous definition`): that is
//   a RED HERRING, unrelated to this function. It is the pre-existing CPP note paired with
//   `:5533 warning: "SHB" redefined` — the TU defines the SHB scheduling-barrier macro twice
//   (post-splice :5222 with __volatile__, :5533 without). It is a warning, present with or
//   without this draft, and it does not fail cc1.

extern int func_800CF8B4();
extern void func_80147324(int arg0);

void aF80161CD0(int param_1, unsigned int param_2) __asm__("func_80161CD0");

void aF80161CD0(int param_1, unsigned int param_2)
{

    extern unsigned short D_80184F90;
    if (param_2 < 8) {
        if (func_800CF8B4() != 0) {
            func_80147324((&D_80184F90)[param_2]);
        }
    }
}


extern void func_80147324(s32 arg0);
extern u16 D_80184FA0[];

    void func_80161D20(int param_1, u32 param_2)
    {
        if (param_2 < 8) {
            func_80147324(D_80184FA0[param_2]);
        }
        return;
    }


#include "../shared/ov/func_80161D58.h"


extern s32 D_800AE6A8;
extern s32 D_800AE6B0;
extern s32 D_80184FE4;
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);

    void func_80161D88(void) {
        if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
            (func_80029178(0x141) & 0xFF) != 0) {
            func_80029124(0x141, 0);
            func_80029124(0x95, 1);
            func_800D1734(&D_80184FE4);
        }
    }


extern s32 func_800291DC(s32);







void func_80161E08(s32 param_1) {

    extern u8 D_800AF630[];
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_80078EB0;
    extern u16 D_800B5BD8;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern u16 D_800B5C10;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern u16 D_800B5C48;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_8019A8F8[];
    extern u8 D_80184FB0[];
    extern u8 D_80184FD0[];
    extern u8 D_8019A904[];
    extern u8 D_8019A92C[];
    extern u8 D_8019A944[];

    u8 *base = &(*(u8 *)&D_800AF630);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (D_800B5BD8 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65A8));
            D_8019A8F8[0] = p;
            func_80024054(&D_80184FB0, &D_8019A904);
            func_8001CE28(p, &D_8019A904);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_8019A8F8[1] = p;
            func_80024054(&D_80184FD0, &D_8019A92C);
            func_8001CE28(p, &D_8019A92C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_8019A8F8[2] = p;
            func_800242D0((s16)func_801620C4(), &D_8019A944, 0x84);
            func_8001CE68(p, &D_8019A944);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_8019A944, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


#include "../shared/ov/func_801620C4.h"


#include "../shared/ov/func_80162120.h"



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_8016216C(void)
{

    extern int D_8019A8F8[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_8019A8F8;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



extern s32 func_800291DC(s32);

s32 func_801621CC(s32 arg0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    extern s32 D_80184FE4;
    register s32 s0 __asm__("$16") = arg0;       /* $s0: arg0, crosses the call */
    register u8 *s1 __asm__("$17") = D_80078E78; /* $s1: base, hoisted for the loop */
    register s32 i __asm__("$5");                /* $a1: counter (pin fixes the i/d swap) */
    u32 a2;
    s32 d;                                       /* $a0: natural alloc; load via $v0 temp */
    s32 v, last, hi, lo;
    char pad[8];                                 /* phantom 8B local -> frame 0x28 (vars=8) */

    a2 = func_800291DC(8);
    if ((a2 & 0x8000) == 0) {
        return 0;
    }
    a2 &= 0x7FFF;
    if (((a2 >> 8) == D_80078EB1) && ((a2 & 0xFF) <= (u32)D_80078EB0)) {
        return (s32)&D_80184FE4;
    }
    d = s1[0x39] - 1;
    i = 0;
    if (s0 <= 0) {
        return 0;
    }
    hi = (a2 >> 8) & 0xFF;
    last = s0 - 1;
    lo = a2 & 0xFF;
    do {
        if ((s8)d < 0) {
            d = 0x17;
        }
        v = (s8)d;
        if (hi == v) {
            if (i != last) {
                return (s32)&D_80184FE4;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80184FE4;
            }
            goto bot;
        }
        i++;
    bot:
        d--;
    } while (i < s0);
    return 0;
}



// @class: schedule
// @stuck: none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

void func_801622C4(void)
{

    extern int D_8019A8F8[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_8019A8F8;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_80185008[])(void);
    D_80185008[*(u8 *)((s32)a0 + 0x15)]();
}


#include "../shared/ov/func_8016236C.h"


#include "../shared/ov/func_801623B8.h"


#include "../shared/ov/func_80162414.h"


extern s32 func_800291DC(s32);








s32 func_80162438(s32 _unused0) {

    extern u8 D_80078EB0;
    extern u8 D_800AF630[];
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80185014[];
    extern s32 D_8018502C;
    extern u8 D_8019A95C[];
    extern u8 D_8019A984[];
    extern u8 D_8019A9A0[];
    extern int D_8019A950[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    register u8 *base __asm__("$18");
    register u8 *item __asm__("$17");

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            register u8 *t __asm__("$2") = base + 0x65A8;
            item = t;
            D_8019A950[0] = (s32)item;
            func_80024054(D_80185014, D_8019A95C);
            func_8001CE28(item, D_8019A95C);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_8019A950[1] = (s32)item;
            func_80024054(((u8 *)&D_8018502C), D_8019A984);
            func_8001CE28(item, D_8019A984);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_8019A950[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_8019A9A0, 0x84);
            func_8001CE68(item, D_8019A9A0);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_8019A9A0, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


#include "../shared/ov/func_801626B8.h"


#include "../shared/ov/func_80162714.h"



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_80162760(void)
{

    extern int D_8019A950[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_8019A950;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


#include "../shared/ov/func_801627C0.h"


extern void func_801627C0(void);

// @class: struct
// @stuck: none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_8018504C[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_8018504C[count-1])
//     keeps the array index/decrement separate so %lo(D_8018504C) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).


void func_801627E8(void)
{

    extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_8018504C[])(void);   /* word-stride table of dispatch fn pointers */
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_8018504C[idx]();
    }
}




void func_80162834(void *a0) {

    extern void (*D_80185050[])(void);
    D_80185050[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_80185040;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_80185040, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


#include "../shared/ov/func_801628F4.h"


#include "../shared/ov/func_80162968.h"


#include "../shared/ov/func_80162AC0.h"


#include "../shared/ov/func_80162ACC.h"


#include "../shared/ov/func_80162AE0.h"


#include "../shared/ov/func_80162AF4.h"


#include "../shared/ov/func_80162B1C.h"


void func_80162CC4(void) {
}

extern void func_80016714(void *a0, s32 a1);

    void func_80162CCC(a0)
u8 *a0;
{
        u8 *s0 = a0;
        u16 *p = *(u16 **)(s0 + 0x20);
        if (p != 0) {
            s32 a1;
            if (*p == 1) {
                a1 = 0x84;
            } else {
                a1 = 0x38;
            }
            func_80016714(p, a1);
        }
        func_80016714(s0, 0x68);
    }


#include "../shared/ov/func_80162D28.h"


#include "../shared/ov/func_80162D88.h"


#include "../shared/ov/func_80162DE8.h"


#include "../shared/ov/func_80162E48.h"


#include "../shared/ov/func_80162EA8.h"


#include "../shared/ov/func_80162F08.h"


#include "../shared/ov/func_80162F60.h"


#include "../shared/ov/func_80162F80.h"


#include "../shared/ov/func_80162FA0.h"


#include "../shared/ov/func_80162FC0.h"


#include "../shared/ov/func_80162FF4.h"


#include "../shared/ov/func_801630C4.h"


#include "../shared/ov/func_80163194.h"


#include "../shared/ov/func_80163234.h"


#include "../shared/ov/func_8016325C.h"


#include "../shared/ov/func_801632E0.h"


#include "../shared/ov/func_801632F0.h"


#include "../shared/ov/func_80163328.h"


#include "../shared/ov/func_801633A8.h"




s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern char aD8018393C_80163408[8] __asm__("D_8019A154");

    unsigned char sp18[8];
    memcpy(sp18, aD8018393C_80163408, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}


#include "../shared/ov/func_8016345C.h"



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char aD8019A154_801634D8[8] __asm__("D_8019A154");
    char buf[8];

    memcpy(buf, aD8019A154_801634D8, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


#include "../shared/ov/func_80163534.h"


#include "../shared/ov/func_80163664.h"


#include "../shared/ov/func_801636D0.h"


#include "../shared/ov/func_80163764.h"

#include "../shared/ov/func_8016380C.h"


extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
extern void *memcpy(void *, const void *, u32);
s32 func_801638A0(u8 *a0, s32 a1) {

    extern s16 D_801152AA;
    u8 buf[8];
    s16 d;
    s32 p;
    __builtin_memcpy(buf, a0 + 0x44, 8);
    p = (s32)(a0 + 4);
    func_80015978(p, (s32 *)a1);
    if (func_80135004(1, buf, a1) != 0) {
        func_80015954(a1, p);
        d = D_801152AA;
        if (d >= -0x578) {
            return 0x8000;
        }
        if (d >= -0xBCB) {
            return 0x4000;
        }
        return 0x2000;
    }
    return 0;
}


#include "../shared/ov/func_80163950.h"




void func_80163A58(void *a0) {

    extern void (*D_80185058[])(void);
    D_80185058[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80163A94.h"


#include "../shared/ov/func_80163C2C.h"


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149350(s32 arg0);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern s32 func_8014CA00(s32 a0);
extern u16 func_80156370(u16 a0);
extern void func_80162D88(s32 *a0);

void func_80163EC8(s32 param_1) {
    extern Blk8 D_8019A15C;
    extern u16 D_800B99DA;
    extern u8 func_801656D0(s32 a0, s32 a1);
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    Blk8 in;
    u16 out[4];
    s16 buf[4];
    s32 psVar6;
    s32 iVar8;
    s32 iVar7;
    register s32 uVar5 __asm__("$2");   /* PIN (flagged): uVar5 -> $v0 */
    u16 uVar4;
    u8 uVar3;

    in = D_8019A15C;
    psVar6 = *(s32 *)(param_1 + 0x4c);
    iVar8 = *(s32 *)(param_1 + 0x20);
    func_80162D88((s32 *)param_1);

    if (*(s32 *)(psVar6 + 0x184) == 0) {
        uVar5 = *(s32 *)(psVar6 + 0x44);
        *(s16 *)(psVar6 + 0x18a) = 0;
        *(s16 *)(psVar6 + 0x188) = 0;
        *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
        func_80146CA0((void *)param_1);
        func_80146CA0((void *)param_1);
        return;
    }
    if (*(s16 *)(*(s32 *)(psVar6 + 0x184) + 0x36) == *(u16 *)(psVar6 + 0x194)) {
        goto LAB_matched;
    }
    *(s32 *)(psVar6 + 0x184) = 0;
    uVar5 = *(s32 *)(psVar6 + 0x44);
    *(s16 *)(psVar6 + 0x18a) = 0;
    *(s16 *)(psVar6 + 0x188) = 0;
    *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);
    return;

LAB_matched:
    *(s16 *)(psVar6 + 0x18a) = *(u16 *)(psVar6 + 0x18a) + 1;
    if ((D_800B99DA & 3) == 0) {
        if (*(s16 *)(psVar6 + 0x188) >= *(u8 *)(param_1 + 0x67)) {
            *(s16 *)(psVar6 + 0x188) = *(s16 *)(psVar6 + 0x188) - *(u8 *)(param_1 + 0x67);
        } else {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
        if (*(s16 *)(psVar6 + 0x188) < 0) {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
    }

    *(s16 *)(param_1 + 0x66) = *(u16 *)(param_1 + 0x66) + 0x40;
    uVar5 = func_80148800((s32 *)psVar6);
    if ((uVar5 & 0x80) != 0) {
        *(s16 *)(param_1 + 0x66) = 0;
        uVar3 = func_801656D0(psVar6, func_8014CA00(*(s32 *)(psVar6 + 0x184)) & 0xff);
        *(s16 *)(psVar6 + 0x188) = *(u16 *)(psVar6 + 0x188) + uVar3;
        *(s16 *)(iVar8 + 0x1a) = 0x4000;
        *(s16 *)(iVar8 + 0x18) = 0x4000;
        *(s32 *)(iVar8 + 0x48) = *(s16 *)(param_1 + 0x58);
        *(s32 *)(iVar8 + 0x4c) = *(s16 *)(param_1 + 0x5a);
        *(s32 *)(iVar8 + 0x50) = *(s16 *)(param_1 + 0x5c);
        ((void (*)(s32, s32, s32))func_80149350)(param_1, (s32)&in, (s32)out);
        *(s16 *)(param_1 + 0x6) = out[0];
        *(s16 *)(param_1 + 0xa) = out[1];
        *(s16 *)(param_1 + 0xe) = out[2];
    }

    if (0x80 < *(s16 *)(psVar6 + 0x188)) {
        *(s16 *)(psVar6 + 0x188) = 0x80;
    }
    if (*(s16 *)(psVar6 + 0x188) >= 0x80) {
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0xe);
            func_8014C4AC(iVar7, 0xe, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            func_80146994(0x33, param_1, 0, iVar7);
        }
    } else {
        if (*(s16 *)(psVar6 + 0x18a) < 0x80 && *(u16 *)psVar6 != 0x19) {
            goto LAB_end;
        }
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0x21);
            func_8014C4AC(iVar7, 0x21, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            if ((*(s32 *)(iVar7 + 0xb4) & 0x40000) != 0) {
                func_8014AD30(param_1, (u16 *)buf, 0, *(s16 *)(iVar7 + 0x60));
            }
        }
    }

    uVar5 = func_8014CA00(iVar7);
    *(s32 *)(psVar6 + 0x184) = uVar5;
    if (0x1e < (u32)uVar5) {
        *(s32 *)(psVar6 + 0x184) = 0;
    }
    func_80146E90((s32 *)param_1, 0x20);
    *(s32 *)(psVar6 + 0x44) = *(s32 *)(psVar6 + 0x44) & ~0x20;
    func_80147324(0x449);
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);

LAB_end:
    uVar4 = func_80012F74(*(s16 *)(iVar8 + 0x1a), 0x1800, 3, 1);
    *(s16 *)(iVar8 + 0x1a) = uVar4;
    *(s16 *)(iVar8 + 0x18) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0x6), *(s16 *)(param_1 + 0x58), 8, 1);
    *(s16 *)(param_1 + 0x6) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xa), *(s16 *)(param_1 + 0x5a), 8, 1);
    *(s16 *)(param_1 + 0xa) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xe), *(s16 *)(param_1 + 0x5c), 8, 1);
    *(s16 *)(param_1 + 0xe) = uVar4;
}


#include "../shared/ov/func_80164270.h"


#include "../shared/ov/func_801642AC.h"


#include "../shared/ov/func_8016432C.h"


void func_80164410(void) {
}

#include "../shared/ov/func_80164418.h"


#include "../shared/ov/func_80164530.h"



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_801850AC[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_801850AC[*(u16 *)(param_1 + 2)]();
    if (iVar1 != 0) {
        ((void (*)(s32))func_80162D28)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);


void func_801647A4(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_80185074;
    extern u16 D_801850A8;
    extern s16 D_801850A6;
    extern s16 D_801850A4;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_80185074;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_801850A8 = 0x80;
        D_801850A6 = 0x80;
        D_801850A4 = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


#include "../shared/ov/func_80164864.h"


extern void func_80162CCC();
extern void func_80164ACC();

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_801850A8 read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_801850A8`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.


void func_80164930(s32 param_1) {

    extern s32 D_8011F9D0;
    extern s16 D_801850A4;
    extern s16 D_801850A6;
    extern u16 D_801850A8;
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_801850A8 - 8;
        D_801850A8 = nv;
        D_801850A6 = nv;
        D_801850A4 = nv;
        if (nv < -0x80) {
            int i, lim;
            Ent_80164930 *p;
            for (i = 0, lim = 0x19, p = ((Ent_80164930 *)&D_8011F9D0); i < 0x14; i++) {
                if (p->f0 == lim && p->f50 != 0) {
                    ((void(*)(Ent_80164930 *))func_80162CCC)(p);
                }
                p++;
            }
            ((void(*)(Ent_80164930 *))func_80162CCC)((Ent_80164930 *)((int)param_1));
        } else {
            ((void(*)(int))func_80164ACC)(((int)param_1));
        }
    } else {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x40;
        u16 uVar2;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        uVar2 = *(u16 *)(iVar3 + 0x1a) - 0x200;
        *(u16 *)(iVar3 + 0x1a) = uVar2;
        if ((int)((unsigned)uVar2 << 0x10) < 0) {
            *(short *)(iVar3 + 0x1a) = 0;
        }
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) - 0x71;
    }
}


#include "../shared/ov/func_80164A74.h"


#include "../shared/ov/func_80164ACC.h"




void func_80164BA0(void *a0) {

    extern void (*D_801850B8[])(void);
    D_801850B8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_8019A9B0;
    extern u8 D_8019A9B1;
    extern u8 D_8019A9B2;
    extern u8 D_8019A9B3;
    extern u8 D_8019A9B4;
    extern u8 D_8019A9B5;
    extern u8 D_8019A9B6;
    extern u8 D_8019A9B7;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_8019A9B0;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_8019A9B1 = 0xf0;
        *(u8 *)base = 0xf0;
        D_8019A9B2 = 0xc0;
        D_8019A9B6 = 0;
        D_8019A9B5 = 0;
        D_8019A9B4 = 0;
        D_8019A9B7 = 0;
        D_8019A9B3 = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}


#include "../shared/ov/func_80164CD4.h"


#include "../shared/ov/func_80164D4C.h"


#include "../shared/ov/func_80164DB0.h"


#include "../shared/ov/func_80164DD0.h"







s32 func_80164E40(void) {

    extern u8 D_8019A9B0;
    extern u8 D_8019A9B1;
    extern u8 D_8019A9B2;
    u8 *p = &D_8019A9B0;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_8019A9B1 != 0) {
        D_8019A9B1 -= 0x10;
    }
    if (D_8019A9B2 != 0) {
        D_8019A9B2 -= 0x10;
    }
    return *(s32 *)p == 0;
}




void func_80164EA4(void *a0) {

    extern void (*D_801850C8[])(void);
    D_801850C8[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_8019A9FC[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_8019A9FC[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


#include "../shared/ov/func_80164F44.h"


#include "../shared/ov/func_80165024.h"


#include "../shared/ov/func_80165064.h"


#include "../shared/ov/func_801650C4.h"


#include "../shared/ov/func_80165124.h"



// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_8019A9F0[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




s32 func_80165140(s32 param_1) {
    extern Slot D_8019A9F0[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_8019A9F0[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern void func_80165240(void *param_1, void *param_2, void *param_3);

void func_801651B8(void * param_1)
{

    extern s32 D_8019A9F0;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_8019A9F0;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            ((s32 (*)(s32, s32, s32))func_80165240)(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}









extern s32  func_80017DC4(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void func_80016ED4(void *a0);



void func_80165240(void *param_1, void *param_2, void *param_3)
{

    extern u8  D_801850DC[];
    extern u32 D_801850FC, D_80185100, D_80185104, D_80185108;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_801850DC[0x00], p);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_801850DC[0x08], prim + 0x08);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_801850DC[0x10], prim + 0x10);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_801850DC[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_80185104;
    *(u32 *)(prim + 0x24) = D_801850FC;
    *(u32 *)(prim + 0x28) = D_80185108;
    *(u32 *)(prim + 0x2c) = D_80185100;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}


/* de-macroized: per-overlay-local decl for func_801659DC (byte-true sig); do NOT re-macroize */
    extern u8 D_80078EC1;
    extern s32 D_80126B58;
    extern u8 D_80126CF8;
    extern s32 func_801659DC();
    void func_8016533C(void) {
        D_80126CF8 = D_80078EC1;
        func_801659DC((u8 *)&D_80126B58);
    }  /* dedup: shared engine-core @0x8016533c (src/shared) */


#include "../shared/ov/func_80165374.h"


#include "../shared/ov/func_801653B8.h"


#include "../shared/ov/func_801653F4.h"



// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC1;
    extern void (*D_8018510C[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_8018510C[D_80078EC1 & 0x7F])(arg0);
            }
        }
    }
    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 == 0x1A) {
        return;
    }
    if (s1[0x49] == 0x19) {
        func_800CAE0C(arg0);
    }
}



// @class: struct
// @stuck: none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{

    extern u8 D_80078EC5;
    extern u8 D_80078EC1;
    extern void (*D_8018510C[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_8018510C[D_80078EC1 & 0x7F]();
    }
}


#include "../shared/ov/func_801655E4.h"


#include "../shared/ov/func_80165624.h"




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_80185188[];
    return D_80185188[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_801851A8[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_801851A8[a1 & 0x7F];
}


#include "../shared/ov/func_80165694.h"




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_80185224[];
    return D_80185224[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_80185244[];
    return D_80185244[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_80185264[];
    return D_80185264[a1 & 0x7F];
}


#include "../shared/ov/func_80165718.h"


#include "../shared/ov/func_80165770.h"


#include "../shared/ov/func_801657A0.h"


#include "../shared/ov/func_801657D8.h"


#include "../shared/ov/func_80165840.h"


#include "../shared/ov/func_80165874.h"


#include "../shared/ov/func_801658DC.h"


#include "../shared/ov/func_801658EC.h"


#include "../shared/ov/func_80165900.h"


#include "../shared/ov/func_80165910.h"


#include "../shared/ov/func_80165938.h"


#include "../shared/ov/func_80165958.h"


#include "../shared/ov/func_80165978.h"


#include "../shared/ov/func_80165988.h"


#include "../shared/ov/func_801659A8.h"


#include "../shared/ov/func_801659B8.h"


#include "../shared/ov/func_801659CC.h"


extern void (*D_80185284[])(void);

s32 func_801659DC(void *a0)
{
    D_80185284[*(u8 *)((s32)a0 + 0x1A0)]();
}


void func_80165A18(void) {
}

#include "../shared/ov/func_80165A20.h"


#include "../shared/ov/func_80165A50.h"


#include "../shared/ov/func_80165A78.h"




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_80185300[])(void);
    D_80185300[D_80078EC1 & 0x7F]();
}


void func_80165B08(void) {
}

void func_80165B10(void) {
}

void func_80165B18(void) {
}

void func_80165B20(void) {
}



void func_80165B28(void *a0) {

    extern void (*D_8018537C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_8018537C[*(u8 *)((s32)a0 + 0x197)]();
}


#include "../shared/ov/func_80165B6C.h"


#include "../shared/ov/func_80165BB4.h"


#include "../shared/ov/func_80165BFC.h"


#include "../shared/ov/func_80165C58.h"


#include "../shared/ov/func_80165C78.h"


#include "../shared/ov/func_80165CA0.h"



void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_8019A164;
    func_8001534C(0, &D_8019A164, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


#include "../shared/ov/func_80165E90.h"


extern void func_80013F3C(s32 a0);
extern void func_80020F34(s32 a0, s32 a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2)
{
    s32 buf[8];
    func_80013F3C((s32)buf);
    func_80020F34((s32)buf, *(s32 *)((u8 *)arg0 + 0x20) + 0x18);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(buf, arg1, arg1);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(buf, arg2, arg2);
}




void func_80166018(void *a0) {

    extern void (*D_80185388[])(void);
    D_80185388[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80166054.h"


#include "../shared/ov/func_801661CC.h"


#include "../shared/ov/func_80166244.h"


#include "../shared/ov/func_8016629C.h"


#include "../shared/ov/func_801662F4.h"


#include "../shared/ov/func_8016634C.h"


#include "../shared/ov/func_801663A4.h"




void func_801663FC(void *a0) {

    extern void (*D_80185390[])(void);
    D_80185390[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80166438.h"


#include "../shared/ov/func_801665B4.h"




void func_80166618(void *a0) {

    extern void (*D_80185458[])(void);
    D_80185458[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_80185468[])(void);
    D_80185468[*(u16 *)((s32)a0 + 0x2)]();
}



   /* 12-byte sub-table record (stride 0xC) */


extern s32 func_80017758(void *a0, void *a1);

s32 func_80166690(s32 param_1, s32 param_2)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    extern u8 D_8019AA70[];
    Frame_80166690 c;
    Blk20 blk;
    Rec_80166690 *sub;
    Rec_80166690 *pv;
    u8 *rec;
    int i6;
    int lt2;
    int p2;
    unsigned int uVar7, uVar8, uVar9;
    int iVar3;
    unsigned int w9, w7, w, t, w3b;
    int w3;
    short sVar10;
    register unsigned int zr __asm__("$0");

    blk = aD800AE620;
    i6 = (short)param_1;
    c.tag = 0x50000000;
    rec = &D_8019AA70[i6 * 0xC4];
    sVar10 = 0;
    if (rec[0] == 0) {
        return 0;
    }
    sub = (Rec_80166690 *)(rec + 4);
    uVar9 = rec[1];
    uVar8 = rec[3];
    uVar7 = uVar8 >> 1;
    iVar3 = rec[2];
    w3 = iVar3 - 1;
    iVar3 = w3 + zr;
    if (w3 != -1) {
        lt2 = i6 < 2;
        p2 = (short)param_2;
        do {
            pv = &sub[(short)uVar9];
            c.v0 = pv->h[0];
            c.v1 = pv->h[1];
            c.v2 = pv->h[2];
            c.w0 = pv->h[3];
            c.w1 = pv->h[4];
            c.w2 = pv->h[5];
            sVar10 = sVar10 + 1;

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c12 = t; c.c02 = t;
                    t = uVar7 + zr;
                } else {
                    w = ((int)(uVar8 << 16) >> 17) + ((int)(uVar8 << 16) >> 19);
                    uVar7 = w + zr;
                    c.c12 = w; c.c02 = w;
                    t = uVar8 + zr;
                }
                c.c11 = t; c.c01 = t; c.c10 = t; c.c00 = t;
            } else {
                t = uVar8 + zr;
                c.c10 = t; c.c00 = t;
                t = uVar7 + zr;
                c.c12 = t; c.c02 = t; c.c11 = t; c.c01 = t;
            }

            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
            if ((int)(w9 << 16) < 0) {
                uVar9 = 0xF;
            }
            pv = &sub[(short)uVar9];
            c.v3 = pv->h[0];
            c.v4 = pv->h[1];
            c.v5 = pv->h[2];
            c.w3 = pv->h[3];
            c.w4 = pv->h[4];
            uVar8 = uVar8 - 0x10;
            w7 = uVar7 - 0x10;
            uVar7 = w7 + zr;
            c.w5 = pv->h[5];
            if ((int)(w7 << 16) < 0) {
                uVar7 = 0;
            }

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar7 + zr;
                } else {
                    t = uVar7 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar8 + zr;
                }
                c.c31 = t; c.c21 = t; c.c30 = t; c.c20 = t;
            } else {
                t = uVar8 + zr;
                c.c30 = t; c.c20 = t;
                t = uVar7 + zr;
                c.c32 = t; c.c22 = t; c.c31 = t; c.c21 = t;
            }

            __asm__ __volatile__("" :: "r"(iVar3));
            func_80017758(&c, &blk);
            w3b = iVar3 - 1;
            iVar3 = w3b + zr;
        } while ((short)w3b != -1);
    }
    return (short)sVar10;
}


extern void func_801484B0(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_8019AA70).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
s32 func_80166994(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    extern u8 D_8019AA70[];
    extern void RotTransSV(s32, s32, void*);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_8019AA70)[param_3];
    s32 uVar6 = *(s32 *)(param_1 + 0x34);
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->count = 0;
        p->idx = 0;
        p->timer = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
        break;
    case 2: {
        u8 bVar3 = p->timer - 0x10;
        p->timer = bVar3;
        if (bVar3 < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 bVar1 = p->count;
            if (bVar1 >= 2 && (bVar3 >> 4) < bVar1) {
                p->count = bVar1 - 1;
            }
        }
        return 0;
    }
    }

    if (param_3 < 2) {
        func_801484B0((s32)v10, (s32)v18);
    } else {
        func_80148534((s32)v10, (s32)v18);
    }
    func_80165FA4(uVar6, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(uVar6, (s32)v10, (s32)v10);
    ((void (*)(void *, void *, void *))RotTransSV)(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_4;
        v20[1] = v28[1] + v20[1] / param_4;
        v20[2] = v28[2] + v20[2] / param_4;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


extern void func_80016714(void *a0, s32 a1);
extern void func_80146C3C(u8*);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{

    extern s32 D_8011D030;
    extern unsigned char D_8019AA70[];

    register int p2 __asm__("$20");             /* $s4 */
    register int p3 __asm__("$17");             /* $s1 */
    register int t2 __asm__("$5");              /* a1 */
    register int t3 __asm__("$6");              /* a2 */
    unsigned short *puVar1;
    short iVar2;
    int eq;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    t2 = ((short)param_2); SHB(t2); p2 = t2; SHB(p2);
    t3 = ((short)param_3); SHB(t3); p3 = t3;
    eq = (p2 == p3);
    do {
        if ((puVar1 != ((unsigned short *)param_1)) &&
            ((unsigned int)*puVar1 == p2 || (unsigned int)*puVar1 == p3) &&
            (!eq ||
             *(int *)(puVar1 + 0x16) == *(int *)(((unsigned short *)param_1) + 0x16))) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
    ((void(*)(void *, int))func_80016714)(&D_8019AA70[((short)param_4) * 0xc4], 0xc4);
}




extern void func_80146C3C(u8*);

void func_8016706C(s32 param_1)
{

    extern s32 D_8011D030;
    unsigned short *puVar1;
    short iVar2;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    do {
        if ((unsigned int)*puVar1 == ((short)param_1)) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
}




// @class: schedule
// @stuck: 16/279 masked. 3 runs, ONE residual class: gcc's list-scheduler puts `la $s2` (p=DATA) + `addu $s4,$zero,$zero` (i=0) BEFORE the callee-arg address setup (addiu $a1,$sp,0x10 / addu $a2,$a1,$zero); the target emits them AFTER. Inert to ~40 statement-order permutations + pin/barrier combos (sched priority dominates the LUID tie-break, sched.c rank_for_schedule). Runs: 19-24 (blk1), 111-114 (region-B cx-load rotation), 177-182 (blk3). Permuter fuel.




extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);


s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8  D_801853AC[];
    extern u8  D_80185398[];
    extern u8  D_801853C0[];
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_80126CE0;
    Fr_801670E4 f;
    register u8 *p   __asm__("$18");   /* $s2 */
    register s32 ent __asm__("$19");   /* $s3 */
    s16 i;
    s32 d;
    s32 node;
    u16 c;
    u8 cv;
    u8 cv2;
    register s32 gA __asm__("$2");
    register s32 cxv __asm__("$4");
    register s32 czv __asm__("$5");
    u8 *vc;
    u8 *ap;
    u8 *mp;
    u8 *va;
    u8 *vb;

    ent = arg0;
    node = *(s32 *)(ent + 0x34);
    f.v[1].z = 0;
    f.v[1].y = 0;
    f.v[1].x = 0;
    f.v[3].z = 0;
    f.v[2].z = 0;
    f.v[0].z = 0;
    f.col[1].b = 0x70;
    cv = *(u8 *)(ent + 0x12);
    f.cx = arg1;
    __asm__ __volatile__("");
    va = (u8 *)&f.cx;
    __asm__ __volatile__("" : "=r"(va) : "0"(va));
    f.cy = arg2;
    vb = va;
    __asm__ __volatile__("" : "=r"(vb) : "0"(vb));
    p = D_801853AC;
    i = 0;
    f.col[0].b = 0;
    f.col[0].g = 0;
    f.col[0].r = 0;
    f.col[2].b = 0;
    f.col[2].g = 0;
    f.col[2].r = 0;
    f.col[3].b = 0;
    f.col[3].g = 0;
    f.col[3].r = 0;
    f.code = 0x50000000;
    f.cz = arg3;
    f.col[1].r = cv;
    f.col[1].g = cv;
    ((void (*)(s32, void *, void *))func_80149350)(node, va, vb);

    c = f.cx;
    *(s16 *)(ent + 0x06) = c;
    *(s32 *)(ent + 0x4C) = (s16)c;
    c = f.cy;
    *(s16 *)(ent + 0x0A) = c;
    *(s32 *)(ent + 0x50) = (s16)c;
    c = f.cz;
    *(s16 *)(ent + 0x0E) = c;
    *(s32 *)(ent + 0x54) = (s16)c;
    func_800D20C0(&f.cx, f.a8, 7);
    func_80017E68(&f.cx, f.m1);
    func_800D23D0(f.a8);
    RotMatrixYXZ(f.a8, f.m1);

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].y = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].y = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].y = (s8)*p--;
        func_80017758(f.v, f.m1);
    } while ((i = i + 1) < 4);

    p = D_80185398;
    gA = 0xA0;
    cxv = (s16)f.cx;
    f.col[1].g = gA;
    gA = D_801269A4;
    czv = (s16)f.cz;
    f.col[1].b = 0x10;
    f.col[1].r = 0x10;
    f.pos[0] = gA - cxv;
    i = 0;
    f.v[3].y = 0;
    f.v[2].y = 0;
    f.v[0].y = 0;
    f.pos[1] = D_801269A8 - (s16)f.cy;
    f.pos[2] = D_801269AC - czv;

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].z = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].z = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].z = (s8)*p--;
        func_80017758(f.v, (void *)(ent + 0x38));
    } while ((i = i + 1) < 4);

    if (*(s32 *)(ent + 0x30) > 0) {
        vc = (u8 *)&f.cx;
        __asm__ __volatile__("" : "=r"(vc) : "0"(vc));
        mp = f.m1;
        ap = mp;
        __asm__ __volatile__("" : "=r"(ap) : "0"(ap));
        p = D_801853C0;
        i = 0;
        d = (s16)f.a8[0] >> 6;
        f.cx += d;
        f.cy += d;
        f.cz += d;
        func_80017E68(vc, ap);
        f.cx = f.cy = f.cz = ((u32)*(s32 *)(ent + 0x30) >> 1) + D_80126CE0 * 0x20;
        func_80017DC4(&f.cx, f.m2);
        func_80048EAC(f.m2, mp);
        f.v[3].z = 0;
        f.v[2].z = 0;
        f.v[0].z = 0;
        cv2 = *(u8 *)(ent + 0x12);
        f.col[1].b = 0x20;
        f.col[1].r = 0x20;
        f.col[3].b = 0;
        f.col[3].r = 0;
        f.col[2].b = 0;
        f.col[2].r = 0;
        f.col[0].b = 0;
        f.col[0].r = 0;
        f.col[3].g = 0;
        f.col[2].g = 0;
        f.col[0].g = 0;
        f.col[1].g = cv2 + 0x60;
        do {
            f.v[0].x = (s8)*p++;
            f.v[0].y = (s8)*p++;
            f.v[2].x = (s8)*p++;
            f.v[2].y = (s8)*p++;
            f.v[3].x = (s8)*p++;
            f.v[3].y = (s8)*p--;
            func_80017758(f.v, f.m1);
        } while ((i = i + 1) < 8);
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);



 /* 0x20 bytes */






s32 func_80167540(s32 arg0) {
    struct Node_80167540 *node;
    struct Entity_80167540 *ent;
    s32 v;

    node = ((struct Entity_80167540 *)arg0)->unk34;
    if (node->unk0 == 1) {
        if (((struct Entity_80167540 *)arg0)->unk12 > ((struct Entity_80167540 *)arg0)->unk10) {
            if (((struct Entity_80167540 *)arg0)->unk1C > 0) {
                ((struct Entity_80167540 *)arg0)->unk10 = (s16) (((s32(*)())rand)() & 0x30);
                v = -0x30;
                goto shared;
            }
        } else if (((struct Entity_80167540 *)arg0)->unk1C < 0) {
            ((struct Entity_80167540 *)arg0)->unk10 = (s16) ((((s32(*)())rand)() & 0x30) + 0x40);
            v = 0x30;
shared:
            ((struct Entity_80167540 *)arg0)->unk1C = v;
        }
        ((struct Entity_80167540 *)arg0)->unk12 = (s16) (((struct Entity_80167540 *)arg0)->unk12 + ((struct Entity_80167540 *)arg0)->unk1C);
        ((struct Entity_80167540 *)arg0)->mat = node->unk20->mat;
        ((void(*)(struct Entity_80167540 *, s32, s32, s32))func_801670E4)(((struct Entity_80167540 *)arg0), 0, 0, 0);
        ent = ((struct Entity_80167540 *(*)(s32, struct Entity_80167540 *, s16, s16, s32, s32, s32))func_80146A6C)(0xE, ((struct Entity_80167540 *)arg0), node->unk6, node->unkA, node->unkE, 0, 0);
        if (ent != 0) {
            ent->mat = node->unk20->mat;
        }
        if (((struct Entity_80167540 *)arg0)->unk34->unk4C->unk44 & 0x20) {
            ((struct Entity_80167540 *)arg0)->unk30 = 0x600;
            ((struct Entity_80167540 *)arg0)->unk2 = (u16) (((struct Entity_80167540 *)arg0)->unk2 + 1);
        }
    } else {
        ((void(*)(struct Entity_80167540 *))func_80146C3C)(((struct Entity_80167540 *)arg0));
    }
}


#include "../shared/ov/func_80167714.h"




void func_801678B4(void *a0) {

    extern void (*D_80185478[])(void);
    D_80185478[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_801678F0.h"




void func_80167A9C(void *a0) {

    extern void (*D_80185484[])(void);
    D_80185484[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}






s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {

    extern u16 D_800B99DA;
    extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_80185590;
    extern u8 D_801855A4[];

    struct Fr fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;

    func_80168070(param_1, ((s16 *)param_2), ((s16 *)param_3), fr.matrix);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = 0xa0;
    } else if (flags & 2) {
        fr.col[1].r = 0xc0;
    } else {
        fr.col[1].r = 0x80;
    }

    p = ((u8 *)&D_80185590);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 2;
    fr.col[1].g = fr.col[1].r >> 2;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_801855A4;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}


extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80029178(s32 arg);


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {

    extern u16  D_800B99DA;
    extern u8   D_801853E4[];
    extern u8   D_801853F8[];
    u8 buf[0x54];
    u8 *p;
    s16 i;

    func_80168070(arg0, ((s16 *)arg1), ((s16 *)arg2), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];
    if (((u8 (*)(s32))func_80029178)(0x81) != 0) {
        buf[0x45] = buf[0x45] << 2;
        buf[0x46] = buf[0x46] >> 1;
    }

    p = D_801853E4;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x22) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x32) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3A) = (s8)*p--;
        func_80017758(buf + 0x20, buf);
    }

    p = D_801853F8;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x24) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x34) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3C) = (s8)*p--;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


extern void func_80149350(s32 arg0);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_80149350)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)(*(s32 *)(param_1 + 0x20) + 0x34), dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}



extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801681FC(s32 param_1) {

    extern u8 D_8018543C[];
    extern u8 D_8018540C[];
    extern u8 D_8018540D[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_8018543C[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_8018540C[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_8018540D[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern void func_80146C3C(u8*);

void func_8016829C(s32 param_1)
{
    s16 v0;

    if ((*(s32 *)(*(s32 *)(param_1 + 0x34) + 0x44) & 2) == 0) {
        ((void (*)(void))func_80146C3C)();
    } else {
        v0 = *(u16 *)(param_1 + 0x2A) - 1;
        *(u16 *)(param_1 + 0x2A) = v0;
        if (v0 == 0) {
            func_80166994(param_1, 0, *(s16 *)(param_1 + 0x2C), 0);
            *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        }
    }
}


#include "../shared/ov/func_80168328.h"


#include "../shared/ov/func_801683D8.h"



extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_80185448[];
    extern u8 D_80185420[];
    extern u8 D_80185421[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80185448[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80185420[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80185421[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern void func_80146C3C();
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);

void func_801684B4(s32 a0) {
    if ((*(s32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 0x2) == 0) {
        ((void (*)(void))func_80146C3C)();
    } else {
        s16 v0 = *(u16 *)(a0 + 0x2A) - 1;
        *(s16 *)(a0 + 0x2A) = v0;
        if (v0 == 0) {
            func_80166994(a0, 0, 2, 0);
            *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
        }
    }
}


#include "../shared/ov/func_80168540.h"


#include "../shared/ov/func_801685EC.h"


#include "../shared/ov/func_80168640.h"




extern void RotMatrixX(int, void*);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168664(s32 a0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Mat32 D_800AE620;
    s32 p;

    p = *(s32 *)(a0 + 0x34);
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x12) = 0;
    *(s32 *)(a0 + 0x30) = 0x1800;
    *(Blk20 *)(a0 + 0x38) = (*(Blk20 *)&D_800AE620);
    ((s32 (*)(s32, void *))RotMatrixX)(0x400, (void *)(a0 + 0x38));
    func_80048EAC((void *)(*(s32 *)(p + 0x20) + 0x34), (void *)(a0 + 0x38));
    func_801670E4(a0, -6, -0x44, -0x18);
    *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
}




void func_80168744(void *a0) {

    extern void (*D_8018549C[])(void);
    D_8018549C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168780.h"


#include "../shared/ov/func_801687CC.h"


extern void func_80017E68(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);



void func_80168828(void)
{
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_800173BC(void *a0, void *a1);
    extern u16 D_8018548C[];

    register s32 a0v __asm__("$4");
    s32 param_1 = a0v;
    Thing_80168828 thing;
    s16 matA[16];
    s16 matB[16];
    s16 svec[4];
    u16 *p;
    short i;
    register s32 c40 __asm__("$3");   /* $v1: hold the CSE'd 0x40 (else gcc folds to $v0 immediate) */

    c40 = 0x40;
    thing.f04 = 2;
    thing.f0c = 0x24;
    thing.f14 = 0x28;
    thing.f08 = -3;
    thing.f10 = 3;
    thing.f02 = 0;
    thing.f00 = 0;
    thing.f12 = 0;
    thing.f0a = 0;
    thing.f18 = c40;
    thing.f19 = c40;
    thing.f22 = c40;
    thing.f1e = c40;
    thing.f1a = 0x10;
    thing.f20 = 0xff;
    thing.f1c = 0xff;
    thing.f21 = 0xc0;
    thing.f1d = 0xc0;
    thing.f24 = 0x50000000;

    svec[0] = *(u16 *)(param_1 + 6);
    svec[1] = *(u16 *)(param_1 + 0xA);
    svec[2] = *(u16 *)(param_1 + 0xE);
    func_80017E68(svec, matA);

    svec[0] = svec[1] = svec[2] = (*(s32 *)(param_1 + 0x1C) << 11) + 0x1000;
    ((void (*)(void *, void *))func_80017DC4)(svec, matA);

    svec[0] = *(u16 *)(param_1 + 0x12);
    svec[1] = *(u16 *)(param_1 + 0x16);
    svec[2] = *(u16 *)(param_1 + 0x1A);
    RotMatrixYXZ(svec, matB);

    func_80048EAC(matA, matB);

    svec[1] = 0;
    p = D_8018548C;
    for (i = 0; i < 4; i++) {
        svec[0] = *p++;
        svec[2] = *p++;
        ((void (*)(void *, void *))func_80049CAC)(svec, matA);
        func_80048EAC(matB, matA);
        func_800173BC(&thing, matA);
    }
}




void func_801689D8(void *a0) {

    extern void (*D_801854A4[])(void);
    D_801854A4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168A14.h"


extern void func_80146C3C(u8*);
void func_80168A88(void) {
    ((void (*)(void))func_80146C3C)();
}




void func_80168AA8(void *a0) {

    extern void (*D_801854AC[])(void);
    D_801854AC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168AE4.h"


#include "../shared/ov/func_80168B70.h"

extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    short mtx[16];
    short vec[4];
    int r;
    register int i __asm__("$17");     /* loop counter, survives the call -> $s1 */
    register int tmp __asm__("$2");    /* increment temp -> $v0 (the split-IV) */
    func_800D2318();
    vec[0] = *(short *)(param_1 + 0x12);
    vec[1] = *(short *)(param_1 + 0x16);
    vec[2] = 0;
    RotMatrixYXZ(vec, mtx);
    vec[0] = 0;
    if (*(int *)(param_1 + 0x2c) < 0) {
        vec[2] = -8;
        vec[1] = -4;
    } else {
        vec[2] = 2;
        vec[1] = -2;
    }
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mtx, vec, vec);
    *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + vec[0];
    *(short *)(param_1 + 0xa) = *(short *)(param_1 + 0xa) + vec[1];
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + vec[2];
    i = 0;
    if ((short)param_4 > 0) {
        do {
            r = func_80146A6C((unsigned short)param_2, (void *)param_1,
                              (short)*(short *)(param_1 + 6),
                              (short)*(short *)(param_1 + 0xa),
                              (short)*(short *)(param_1 + 0xe),
                              (short)param_3, 0);
            if (r != 0) {
                *(short *)(r + 0x12) = *(short *)(param_1 + 0x12);
                *(short *)(r + 0x16) = *(short *)(param_1 + 0x16);
                *(short *)(r + 0x1a) = *(short *)(param_1 + 0x1a);
            }
            tmp = i + 1;
            i = tmp;
            __asm__ __volatile__("" : "=r"(i) : "0"(i));
        } while ((short)tmp < (short)param_4);
    }
}




void func_80168D58(void *a0) {

    extern void (*D_801854B4[])(void);
    D_801854B4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern int rand(void);
void func_80168D94(int a0) {
    int s1 = a0;
    short v10[4];   /* sp+0x10 SVECTOR */
    short v18[16];  /* sp+0x18 MATRIX_L48 */
    short v38[16];  /* sp+0x38 MATRIX_L48 */
    register int v1 __asm__("$3");
    register int v0 __asm__("$2");
    v10[0] = *(unsigned short *)(s1 + 0x12);
    v10[1] = *(unsigned short *)(s1 + 0x16);
    v10[2] = *(unsigned short *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v38);
    if (*(int *)(s1 + 0x2C) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5);
        __asm__("" : "=r"(v0) : "0"(v0));
        v0 += 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE00;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" ::: "memory");
    v10[2] = 0;
    RotMatrixYXZ(v10, v18);
    func_80048EAC(v38, v18);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0x24;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v18, v10, v10);
    {
        register s32 a __asm__("$4") = *(unsigned short *)(s1 + 0x6);
        register s32 b __asm__("$5") = *(unsigned short *)(s1 + 0xA);
        register s32 c __asm__("$3") = *(unsigned short *)(s1 + 0xE);
        *(unsigned short *)(s1 + 0x12) = v10[0];
        *(unsigned short *)(s1 + 0x16) = v10[1];
        {
            s32 z = (unsigned short)v10[2];
            s32 t = *(unsigned short *)(s1 + 0x2);
            *(unsigned short *)(s1 + 0x10) = a;
            *(unsigned short *)(s1 + 0x14) = b;
            *(unsigned short *)(s1 + 0x18) = c;
            *(int *)(s1 + 0x1C) = 0;
            *(unsigned short *)(s1 + 0x2) = t + 1;
            *(unsigned short *)(s1 + 0x1A) = z;
        }
    }
}


#include "../shared/ov/func_80168EC4.h"




typedef struct {
    u16 f00;
    u16 f02;
    u16 f04;
    u16 pad06;
    u16 f08;
    u16 f0A;
    u16 f0C;
    u16 pad0E;
    u8  f10;
    u8  f11;
    u8  f12;
    u8  pad13;
    u8  f14;
    u8  f15;
    u8  f16;
    u8  pad17;
    u32 f18;
} S1_80168F40;

extern s32 func_80016A5C();

void func_80168F40(void *a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Mat32 D_800AE620;
    S1_80168F40 s1;
    Blk20 s2;
    s32 pad[2];

    s1.f00 = *(u16 *)((s32)a0 + 0x10);
    s1.f02 = *(u16 *)((s32)a0 + 0x14);
    s1.f04 = *(u16 *)((s32)a0 + 0x18);
    s1.f08 = *(u16 *)((s32)a0 + 0x6);
    s1.f0A = *(u16 *)((s32)a0 + 0xA);
    s1.f0C = *(u16 *)((s32)a0 + 0xE);
    s1.f10 = 8;
    s1.f14 = 0xC0;
    s1.f12 = 0;
    s1.f11 = 0;
    s1.f16 = 0x80;
    s1.f15 = 0x80;
    s2 = (*(Blk20 *)&D_800AE620);
    s1.f18 = 0x50000000;
    func_80016A5C(&s1, &s2);
}




void func_8016901C(void *a0) {

    extern void (*D_801854BC[])(void);
    D_801854BC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_80169058(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX_L48 */
    s16 v40[16];  /* sp+0x40 MATRIX_L48 */
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = ((u32)(v0 & 0x7F00)) >> 5;
        __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
        v0 = v0 + 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE40;
        v0 = (((u32)(v0 & 0x7F00)) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" : : "r"(v1), "r"(v0));
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 c = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = c + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


#include "../shared/ov/func_801691B8.h"


#include "../shared/ov/func_80169228.h"




void func_801693CC(void *a0) {

    extern void (*D_801854C4[])(void);
    D_801854C4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80169584(s32 param_1);
void func_80169408(s32 a0) {
    register s32 s2 __asm__("$18") = a0;
    register s32 s1 __asm__("$17");
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 out[4];   /* sp+0x18 SVECTOR */
    s16 m[32];    /* sp+0x20 MATRIX_L48 (+ trailing reserve to 0x60 — matches target frame) */
    if (*(s32 *)(s2 + 0x2C) == 0) {
        s32 r = rand();
        s1 = s2 + 0x38;
        v10[0] = (r & 0x7F) << 5;
        v10[1] = ((u32)(r & 0x7F00)) >> 3;
        v10[2] = 0;
        RotMatrixYXZ(v10, m);
        func_80048EAC((void *)s1, m);
        v10[0] = 0;
        v10[1] = 0;
        v10[2] = 2;
        ((void (*)(void *, void *, void *))ApplyMatrixSV)(m, v10, v10);
        *(u16 *)(s2 + 0x12) = v10[0];
        *(u16 *)(s2 + 0x16) = v10[1];
        *(u16 *)(s2 + 0x1A) = v10[2];
        v10[0] = *(u16 *)(s2 + 0x6);
        v10[1] = *(u16 *)(s2 + 0xA);
        v10[2] = *(u16 *)(s2 + 0xE);
        func_800D20C0(v10, out, 1);
        func_800D23D0(out);
        RotMatrixYXZ(out, (void *)s1);
    }
    func_80169584(s2);
    *(u16 *)(s2 + 0x2) = *(u16 *)(s2 + 0x2) + 1;
}


#include "../shared/ov/func_8016951C.h"


#include "../shared/ov/func_80169584.h"


#include "../shared/ov/func_801696D8.h"




void func_80169830(void *a0) {

    extern void (*D_801854CC[])(void);
    D_801854CC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_8016986C(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX_L48 */
    s16 v40[16];  /* sp+0x40 MATRIX_L48 */
    s32 v1;
    s32 t;
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    v1 = rand();
    v10[0] = (v1 & 0x1FC) + 0x180;
    if (*(s32 *)(s1 + 0x2C) & 0x2) {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0x200;
    } else {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0xC00;
    }
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    if ((*(s32 *)(s1 + 0x2C) & 0x1) == 0) {
        *(s32 *)(s1 + 0x2C) = 0xE00;
    } else {
        *(s32 *)(s1 + 0x2C) = 0xA00;
    }
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 tmp = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = tmp + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


#include "../shared/ov/func_801699D0.h"


#include "../shared/ov/func_80169A4C.h"




void func_80169B80(void *a0) {

    extern void (*D_80185580[])(void);
    D_80185580[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_800D222C(void *a0, void *a1, s32 a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(u8*);

void func_80169BBC(s32 arg0) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_801854D4[];
    extern u8 D_80185544[];
    extern u8 D_80185574[];
    extern u8 D_8019BBF8[];
    u16 rot[4];
    s16 vec[4];
    s32 pos[4];
    s16 mtx[16];
    s32 p1;
    s32 s2;

    func_800D2318();
    rot[0] = *(u16 *)(arg0 + 0x12);
    rot[1] = *(u16 *)(arg0 + 0x16);
    rot[2] = 0;
    RotMatrixYXZ(rot, mtx);
    vec[0] = 0;
    vec[1] = -2;
    vec[2] = -0x14;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mtx, vec, vec);
    *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 6) + (u16)vec[0];
    *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0xA) + (u16)vec[1];
    *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0xE) + (u16)vec[2];
    p1 = func_80146A6C(9, (void *)arg0, *(s16 *)(arg0 + 6), *(s16 *)(arg0 + 0xA),
                       *(s16 *)(arg0 + 0xE), 0, 0);
    if (p1 != 0) {
        *(u16 *)(p1 + 0x12) = rot[0];
        *(u16 *)(p1 + 0x16) = rot[1];
        *(u16 *)(p1 + 0x1A) = rot[2];
    }
    func_80146A6C(0xC, (void *)arg0, *(s16 *)(arg0 + 6), *(s16 *)(arg0 + 0xA),
                  *(s16 *)(arg0 + 0xE), 0, 0);
    s2 = func_800D222C((void *)arg0, D_80185574, 0x17);
    if (s2 != 0) {
        *(s32 *)(arg0 + 0x20) = s2;
        rot[0] = rot[0] + D_801854D4[*(s32 *)(arg0 + 0x30)];
        rot[1] = rot[1] - 0x400;
        RotMatrixYXZ(rot, mtx);
        pos[0] = D_801269A4 - *(s16 *)(arg0 + 6);
        pos[1] = D_801269A8 - *(s16 *)(arg0 + 0xA);
        pos[2] = D_801269AC - *(s16 *)(arg0 + 0xE);
        ApplyTransposeMatrixLV(mtx, pos, pos);
        rot[2] = -ratan2(pos[0], pos[1]);
        vec[0] = 0x400;
        vec[1] = -0x400;
        vec[2] = 0;
        RotMatrixYXZ(vec, mtx);
        *(s32 *)(s2 + 0x34) = (s32)D_8019BBF8;
        RotMatrixYXZ(rot, D_8019BBF8);
        func_80048D9C(D_8019BBF8, mtx);
        *(u16 *)(s2 + 0x18) = 0x5000;
        *(u16 *)(s2 + 0x1A) = 0x2000;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0xC000140;
        func_80128EA8(s2, arg0 + 0x24, (s32)D_80185544);
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


#include "../shared/ov/func_80169E44.h"




void func_80169F00(void *a0) {

    extern void (*D_80185588[])(void);
    D_80185588[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(u8*);


void func_80169F3C(int param_1)
{

    extern char D_80185538[];
    extern char D_801854F8[];
    int iVar1;

    ((int (*)(int, int))func_800D1FC8)(param_1, 6);
    iVar1 = func_800D21C4(param_1, D_80185538, 0x16);
    if (iVar1 != 0) {
        *(int *)(param_1 + 0x20) = iVar1;
        *(short *)(iVar1 + 0x1a) = 0x2000;
        *(short *)(iVar1 + 0x18) = 0x2000;
        *(char *)(iVar1 + 0x26) = 0x60;
        *(char *)(iVar1 + 0x25) = 0x60;
        *(char *)(iVar1 + 0x24) = 0x60;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        ((void (*)(int, int, void *))func_80128EA8)(iVar1, param_1 + 0x24, D_801854F8);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_80169FE0(s32 a0) {
    if (((s32 (*)(void *, void *))func_80128ED8)((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}




void func_8016A020(void *a0) {

    extern void (*D_801855C0[])(void);
    D_801855C0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8016A05C.h"


#include "../shared/ov/func_8016A08C.h"


#include "../shared/ov/func_8016A1CC.h"


extern s32 func_80017758(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80149350(s32 arg0);





void func_8016A290(s32 param_1, void *param_2, void *param_3) {

    extern u16 D_800B99DA;
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u8 D_80185590;
    extern u8 D_801855A4[];

    struct Fr_8016A290 fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;
    s32 iVar3;

    iVar3 = *(s32 *)(param_1 + 0x34);

    fr.center.x = (*((s16 *)param_2) + *((s16 *)param_3)) >> 1;
    fr.center.y = (((s16 *)param_2)[1] + ((s16 *)param_3)[1]) >> 1;
    fr.center.z = (((s16 *)param_2)[2] + ((s16 *)param_3)[2]) >> 1;
    ((void(*)(s32, void *, void *))func_80149350)(iVar3, &fr.center, &fr.center);

    *(u16 *)(param_1 + 0x6) = *(u16 *)&fr.center.x;
    *(u16 *)(param_1 + 0xA) = *(u16 *)&fr.center.y;
    *(u16 *)(param_1 + 0xE) = *(u16 *)&fr.center.z;
    func_800D20C0(&fr.center, &fr.diff, 8);
    func_80017E68(&fr.center, fr.mtx);

    fr.diff.x = *(u16 *)((s16 *)param_3) - *(u16 *)((s16 *)param_2);
    fr.diff.y = *(u16 *)(((s16 *)param_3) + 1) - *(u16 *)(((s16 *)param_2) + 1);
    fr.diff.z = *(u16 *)(((s16 *)param_3) + 2) - *(u16 *)(((s16 *)param_2) + 2);
    ((void(*)(s32, void *, void *))ApplyMatrixSV)(*(s32 *)(iVar3 + 0x20) + 0x34, &fr.diff, &fr.diff);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.pos[0] = D_801269A4 - fr.center.x;
    fr.pos[1] = D_801269A8 - fr.center.y;
    fr.pos[2] = D_801269AC - fr.center.z;
    ApplyTransposeMatrixLV(fr.mtx, fr.pos, fr.pos);
    fr.diff.z = -((s32(*)(s32, s32))ratan2)(fr.pos[0], fr.pos[1]);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x20;
    } else if (flags & 2) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x40;
    } else {
        fr.col[1].r = *(s32 *)(param_1 + 0x30);
    }

    p = ((u8 *)&D_80185590);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 3;
    fr.col[1].g = fr.col[1].r >> 3;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_801855A4;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}




void func_8016A700(void *a0) {

    extern void (*D_801855CC[])(void);
    D_801855CC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80048EAC(void *a0, void *a1);

// Seed for func_8016A73C (ov_SC01_077 exemplar). Overlay-local struct guessed.





s32 func_8016A73C(s32 arg0) {

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    int sp10[8];
    short v[3];   /* sp30, sp32, sp34 */
    int r;
    short tmp;

    r = rand();
    v[1] = ((r & 0x7F) << 4) + 0x400;
    v[0] = ((unsigned)(r & 0x7F00) >> 5) - 0x300;
    v[2] = 0;
    ((void(*)(short *, void *))RotMatrixYXZ)(v, sp10);
    ((void(*)(int, void *))func_80048EAC)(((Obj_8016A73C *)arg0)->unk34->unk34->unk20 + 0x34, sp10);
    v[0] = 0;
    v[1] = 0;
    v[2] = -0x50;
    ((int(*)(void *, short *, short *))ApplyMatrixSV)(sp10, v, v);

    ((Obj_8016A73C *)arg0)->mat = (*(Mat_8016A73C*)&aD800AE620);

    tmp = ((Obj_8016A73C *)arg0)->unk6 + v[0];
    ((Obj_8016A73C *)arg0)->unk6 = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[5] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkA + v[1];
    ((Obj_8016A73C *)arg0)->unkA = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[6] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkE + v[2];
    ((Obj_8016A73C *)arg0)->unkE = tmp;
    ((Obj_8016A73C *)arg0)->unk2 = ((Obj_8016A73C *)arg0)->unk2 + 1;
    ((Obj_8016A73C *)arg0)->mat.w[7] = tmp;
}


#include "../shared/ov/func_8016A890.h"


extern s32 func_80016A5C();
s32 func_8016A8FC(s32 a0)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    Prim p;
    int ptr;
    ptr = *(int *)(a0 + 0x34);
    p.v0 = (short)*(int *)(a0 + 0x4C);
    p.v1 = (short)*(int *)(a0 + 0x50);
    p.v2 = (short)*(int *)(a0 + 0x54);
    p.w0 = *(unsigned short *)(ptr + 6);
    p.w1 = *(unsigned short *)(ptr + 0xA);
    p.w2 = *(unsigned short *)(ptr + 0xE);
    p.v0 = (short)(((int)*(short *)(a0 + 6) + *(int *)(a0 + 0x4C)) >> 1);
    p.v1 = (short)(((int)*(short *)(a0 + 0xA) + *(int *)(a0 + 0x50)) >> 1);
    p.v2 = (short)(((int)*(short *)(a0 + 0xE) + *(int *)(a0 + 0x54)) >> 1);
    *(short *)(a0 + 6) = (short)*(int *)(a0 + 0x4C);
    p.w0 = (short)(((int)*(short *)(a0 + 6) + (int)*(short *)(ptr + 6)) >> 1);
    *(int *)(a0 + 0x4C) = p.w0;
    *(short *)(a0 + 0xA) = (short)*(int *)(a0 + 0x50);
    p.w1 = (short)(((int)*(short *)(a0 + 0xA) + (int)*(short *)(ptr + 0xA)) >> 1);
    *(int *)(a0 + 0x50) = p.w1;
    *(short *)(a0 + 0xE) = (short)*(int *)(a0 + 0x54);
    p.w2 = (short)(((int)*(short *)(a0 + 0xE) + (int)*(short *)(ptr + 0xE)) >> 1);
    *(int *)(a0 + 0x54) = p.w2;
    p.b11 = 0x10;
    p.b15 = 0x80;
    p.b16 = 0x20;
    p.b14 = 0x20;
    p.b12 = 0;
    p.b10 = 0;
    p.w18 = 0x50000000;
    ((s32 (*)(void *, void *))func_80016A5C)(&p, &aD800AE620);
}


#include "../shared/ov/func_8016AA50.h"




void func_8016AB30(void *a0) {

    extern void (*D_80185614[])(void);
    D_80185614[*(u16 *)((s32)a0 + 0x2)]();
}
