#include "common.h"
#include "../shared/engine_core.h"

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
extern void func_8013BC7C(void);
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
extern s32 func_80029178(s32 arg);
extern s32 func_801380E0(s32 arg0);
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
extern unsigned char D_80182A74[];
extern void func_80139BE0(int param_1);
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
/* ==== end §8b carried decl layer ==== */


extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_8019A7F0;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_8019A7F0, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern void func_80019064(void *a0);

void func_8013C9C4(void * arg0)
{

    extern M2C_UNK D_80062BC0;
    extern s32 D_8019A7F0;
    extern s8 D_8019A7F4;
    extern s8 D_8019A7F5;
    D_8019A7F0 = arg0;
    D_8019A7F4 = 0;
    D_8019A7F5 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}



void func_8013CA14(void)
{

    extern s32 D_8019A7F0;
    extern s8 D_8019A7F4;
    extern s8 D_8019A7F5;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_8019A7F0;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_8019A7F5;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_8019A7F4)) * 2) + D_8019A7F0);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_8019A7F5 = (unsigned char) p[1];
      D_8019A7F4 = D_8019A7F4 + 1;
      if (D_8019A7F5 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_8019A7F4 = 0;
        *base = 0;
      }
    }
    else
    {
      D_8019A7F5 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_8019A814;
    extern s32 D_8019A808;
    extern s32 D_8019A80C;
    extern s32 D_8019A818;
    D_8019A814 = 1;
    D_8019A808 = 1;
    D_8019A80C = 0;
    D_8019A818 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_8019A808;
    extern s32 D_8019A80C;
    extern s32 D_8019A810;
    extern s32 D_8019A814;
    extern s32 D_8019A818;
    D_8019A808 = 1;
    D_8019A814 = 0;
    D_8019A80C = 0;
    D_8019A810 = -1;
    D_8019A818 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_8019A814;
    extern s32 D_8019A818;
    extern s32 D_8019A840;
    extern s32 D_8019A844;
    D_8019A840 = D_8019A818;
    D_8019A844 = D_8019A814;
    D_8019A818 = 1;
    D_8019A814 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_8019A840;
    extern s32 D_8019A844;
    extern s32 D_8019A818;
    extern s32 D_8019A814;
    D_8019A818 = D_8019A840;
    D_8019A814 = D_8019A844;
}




extern s16 currentLocationId;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_8019A818;
    extern s32 D_8019A810;
    extern s32 D_8019A814;
    extern s32 D_8019A808;
    extern s32 D_8019A80C;
    extern s32 D_8019A81C;
    extern s32 D_8019A828;
    extern s32 D_8019A830;
    extern s32 D_8019BCB0;
    extern s32 D_8019BC30;
    extern s32 D_8019BC24[];
    extern u8 D_8019BBF1;
    extern u8 D_8019BD3E;
    extern u8 D_8019BCAC;
    extern Rec12 D_80182E10[];
    extern Rec9 D_80182DD8[];
    extern u8 D_8019BC88;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_8019BCB0 = 0;
    if (D_8019A818 == 0 && s0 != D_8019A810) {
        ta = D_80182E10[s0].a;
        tb = D_80182E10[s0].b;
        tc = D_80182E10[s0].c;
        D_8019A810 = s0;
        D_8019BBF1 = tc;
        D_8019BD3E = ta;
        D_8019BCAC = tb;
        *(Rec9 *)&D_8019BC88 = D_80182DD8[s0];
        D_8019A814 = 1;
        D_8019A808 = 1;
        if (D_8019A828 & 2) {
            if (s0 == 4) { D_8019BC24[0] = 0x100; D_8019BC30 = 0x80; }
            if (s0 == 0) { D_8019BC24[0] = 0x100; D_8019BC30 = 0; }
        }
    }
    if (D_8019A814 != 0) {
        t = D_8019A808 - 1;
        D_8019A808 = t;
        if (t == 0) {
            if (D_8019A818 == 0) {
                if ((D_8019A828 & 2) && s0 == 4) {
                    if (D_8019A830 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_8019A830 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_8019A808 = 2;
                if (D_8019A814 != 0) {
                    if (D_8019A828 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_8019BC30;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_8019BC30;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_8019A828 & 2) {
                    if (s0 == 4) D_8019BC30 = 0;
                    if (s0 == 0) D_8019BC30 = 0x80;
                }
            } else {
                if (D_8019A830 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_8019A808 = 1;
            }
        }
    }
    D_8019A81C = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_8019A814 != 0) D_8019A81C = D_8019A80C;
            else D_8019A81C = 0x1F;
        } else if (s0 == 4) {
            if (D_8019A814 != 0) D_8019A81C = 0x1F - D_8019A80C;
            else D_8019A81C = 0;
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
    extern u8 D_8019BBE8;
    extern u8 D_8019BBE9;
    extern u8 D_8019BBEA;
    extern u8 D_8019BBEB;
    extern u8 D_8019BBEC;
    extern u8 D_8019BBED;
    extern u8 D_8019BBEE;
    extern u8 D_8019BBEF;
    extern u8 D_8019BBF0;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_8019BBE8; t1 = D_8019BBE9; t2 = D_8019BBEA;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_8019BBEB; t1 = D_8019BBEC; t2 = D_8019BBED;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_8019BBEE; t1 = D_8019BBEF; t2 = D_8019BBF0;
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

    extern s32 D_8019A820;
    extern s32 D_8019A808;
    extern s32 D_8019A824;
    extern s32 D_8019A814;
    if (D_8019A820 != 0) {
        if (D_8019A820 != 2) {
            if (((D_8019A820 < 3) && (D_8019A820 == 1)) &&
                (D_8019A824 = D_8019A824 + 1, 0x23a < D_8019A824)) {
                D_8019A808 = D_8019A820;
                D_8019A820 = 2;
            }
        } else {
            D_8019A808 = D_8019A808 + -1;
            if (D_8019A808 == 0) {
                D_8019A808 = D_8019A820;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_8019A814 == 0) {
                    D_8019A820 = D_8019A820 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_8019A814;
    func_8013D9B0();
    return D_8019A814;
}




void func_8013D164(void) {

    extern s32 D_8019A820;
    D_8019A820 = 1;
}



void func_8013D178(void) {

    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern unsigned char D_8019BBE8, D_8019BBE9, D_8019BBEA, D_8019BBEB, D_8019BBEC, D_8019BBED, D_8019BBEE, D_8019BBEF, D_8019BBF0;
    extern u8 D_8019BC88;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    extern unsigned char D_8019BC88, D_8019BC89, D_8019BC8A, D_8019BC8B, D_8019BC8C, D_8019BC8D, D_8019BC8E, D_8019BC8F, D_8019BC90;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_8019BBE8; v = *p; t = D_8019BC88;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBE9; v = *p; t = D_8019BC89;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBEA; v = *p; t = D_8019BC8A;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBEB; v = *p; t = D_8019BC8B;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBEC; v = *p; t = D_8019BC8C;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBED; v = *p; t = D_8019BC8D;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBEE; v = *p; t = D_8019BC8E;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBEF; v = *p; t = D_8019BC8F;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019BBF0; v = *p; t = D_8019BC90;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_8019BCCA;
    extern u8 D_8019BD3E;
    extern u8 D_8019BBF2;
    extern u8 D_8019BCAC;
    extern u8 D_8019BBD0;
    extern u8 D_8019BBF1;
    extern s32 D_8019BCB0;
    if ((D_8019BCCA & 0xff) != D_8019BD3E) {
        D_8019BCCA = ((D_8019BCCA & 0xff) < D_8019BD3E) ? (D_8019BCCA + 1) : (D_8019BCCA - 1);
    }
    if ((D_8019BBF2 & 0xff) != D_8019BCAC) {
        D_8019BBF2 = ((D_8019BBF2 & 0xff) < D_8019BCAC) ? (D_8019BBF2 + 1) : (D_8019BBF2 - 1);
    }
    if ((D_8019BBD0 & 0xff) != D_8019BBF1) {
        D_8019BBD0 = ((D_8019BBD0 & 0xff) < D_8019BBF1) ? (D_8019BBD0 + 1) : (D_8019BBD0 - 1);
    }
    D_8019BCB0 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C(void *);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_8019A7F8;
    extern void *D_8019A7FC;
    extern void *D_8019A800;
    extern s32 D_8019A828;
    extern s32 D_8019A82C;
    extern s32 D_8019A830;
    extern s32 D_8019BC24[];
    extern u8 D_80182CE8[];
    extern u8 D_80182D90[];
    extern u8 D_80182C40[];
    extern u8 D_80182D3C[];
    extern u8 D_80182DBC[];
    extern u8 D_80182C94[];
    u8 *p = D_80078E78;

    D_8019A828 = param_2;
    D_8019A82C = (param_2 >> 2) & 3;
    D_8019A830 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_8019A7F8 = D_80182CE8;
        D_8019A7FC = D_80182D90;
        D_8019A800 = D_80182C40;
    } else {
        D_8019A7F8 = D_80182D3C;
        D_8019A7FC = D_80182DBC;
        D_8019A800 = D_80182C94;
    }
    func_8013D53C((void *)param_1);
    if ((param_2 & 1) != 0) {
        if (D_8019A830 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_8019A828 & 2) != 0) {
            D_8019BC24[0] = 0x140;
            D_8019BC24[3] = 0x80;
            if (p[0x37] == 4) {
                D_8019BC24[0] = 0x140;
                D_8019BC24[3] = 0;
            }
            if (p[0x37] == 0) {
                D_8019BC24[0] = 0x140;
                D_8019BC24[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */








void func_8013D53C(void *arg0v) {

    extern Rec9 D_80182DD8[];
    extern Rec12 D_80182E10[];
    extern s32 D_8019A828;
    extern u8 D_80078EAF;
    extern s32 D_8019A810;
    extern u8 D_8019BCCA;
    extern u8 D_8019BD3E;
    extern u8 D_8019BBF2;
    extern u8 D_8019BCAC;
    extern u8 D_8019BBD0;
    extern u8 D_8019BBF1;
    extern u8 D_8019BC88;
    extern s32 D_8019BCB0;
    extern s32 D_8019A824;
    extern s32 D_8019A820;
    extern s32 D_8019A81C;
    extern s32 D_8019A808;
    extern s32 D_8019A814;
    extern s32 D_8019A818;
    extern void *D_8019A7F8;
    extern s32 D_8019A830;
    extern void *D_8019A800;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_80182E14[];
    extern u8 D_80182E18[];
    extern unsigned char D_8019BBE8;
    extern s16 *D_8019A804;
    extern s32 D_8019A834;
    extern s32 D_8019A838;
    extern s32 D_8019A83C;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_8019A828 & 1)) {
        D_8019A810 = 1;
    } else {
        D_8019A810 = D_80078EAF;
    }

    b0 = ((u8 *)D_80182E10)[D_8019A810 * 12];
    D_8019BCCA = b0;
    D_8019BD3E = b0;
    b1 = D_80182E14[D_8019A810 * 12];
    D_8019BBF2 = b1;
    D_8019BCAC = b1;
    b2 = D_80182E18[D_8019A810 * 12];
    D_8019BBD0 = b2;
    D_8019BBF1 = b2;

    (*(S9 *)&D_8019BBE8) = ((S9 *)D_80182DD8)[D_8019A810];
    (*(S9 *)&D_8019BC88) = *(S9 *)(&D_8019BBD0 + 0x18);  /* same addr as (*(S9 *)&D_8019BBE8); distinct sym defeats cse, keeps %hi/%lo */

    D_8019BCB0 = 1;
    D_8019A824 = -1;
    D_8019A820 = 0;
    D_8019A81C = -1;
    D_8019A808 = 0;
    D_8019A814 = 0;
    D_8019A818 = 0;

    if ((D_8019A828 & 2) && (D_8019A810 == 4)) {
        s0v = (*(s32 * *)&D_8019A7F8)[18];
        t9v = (*(s32 * *)&D_8019A7F8)[19];
        t8v = (*(s32 * *)&D_8019A7F8)[20];
    } else {
        s32 *p = (s32 *)(D_8019A810 * 12 + (s32) (*(s32 * *)&D_8019A7F8));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_8019A804) = arg0;
    if (arg0 != 0) {
        if (D_8019A830 != 0) {
            s32 *p = (s32 *)(D_8019A810 * 12 + (s32) (*(s32 * *)&D_8019A800));
            D_8019A834 = p[0];
            D_8019A838 = p[1];
            D_8019A83C = p[2];
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




// @class: schedule
// @stuck: none — MATCH (45 ins, match_one verified)

extern void func_800599B8(u16*);

void func_8013D8FC(void)
{

    extern s16 *D_8019A804;
    register s16 *psVar3 __asm__("$17");
    register s16 *psVar2 __asm__("$16");
    register s32 c9 __asm__("$19");
    register s32 cff __asm__("$18");
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_8019A804;
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

    extern void *D_8019A7FC;
    extern s16 *D_8019A804;
    extern s32 D_8019A814;
    extern s32 D_8019A81C;

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

    psVar15 = (*(u16 * *)&D_8019A804);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_8019A7FC)[param_1];
        D_8019A81C = -1;
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
        D_8019A814 = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_8019A800)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_8019A800;
    extern s16 *D_8019A804;
    extern s32 D_8019A814;
    extern s32 D_8019A834;
    extern s32 D_8019A838;
    extern s32 D_8019A83C;
    int *p;
    int x, y, z;
    int flag;

    if (D_8019A804 != 0) {
        D_8019A814 = 0;
        p = (int *)(param_1 * 12 + (int)D_8019A800);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_8019A834 != x) {
            flag = 1;
            if (D_8019A834 < x) {
                if (x - D_8019A834 < 5) {
                    D_8019A834 = x;
                } else {
                    D_8019A834 = D_8019A834 + 4;
                }
            } else {
                if (D_8019A834 - x < 5) {
                    D_8019A834 = x;
                } else {
                    D_8019A834 = D_8019A834 - 4;
                }
            }
        }
        if (D_8019A838 != y) {
            flag = 1;
            if (D_8019A838 < y) {
                if (y - D_8019A838 < 5) {
                    D_8019A838 = y;
                } else {
                    D_8019A838 = D_8019A838 + 4;
                }
            } else {
                if (D_8019A838 - y < 5) {
                    D_8019A838 = y;
                } else {
                    D_8019A838 = D_8019A838 - 4;
                }
            }
        }
        if (D_8019A83C != z) {
            flag = 1;
            if (D_8019A83C < z) {
                if (z - D_8019A83C < 5) {
                    D_8019A83C = z;
                } else {
                    D_8019A83C = D_8019A83C + 4;
                }
            } else {
                if (D_8019A83C - z < 5) {
                    D_8019A83C = z;
                } else {
                    D_8019A83C = D_8019A83C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_8019A814 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC03_107/nonmatchings/ov_SC03_107_jr_8013C98C", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_8019A81C;
    return D_8019A81C;
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


DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013e4b4 (src/shared) */


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
    extern void (*D_8018385C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018385C[D_80115112];
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
    extern s32 D_80183848;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_80183820;
    extern s16 D_80183822;
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
        ep = (s32 *)&D_80183848;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80183820 = 2;
        D_80183822 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_80183822 = 0;
        D_80183820 = 0;
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
    extern void * D_8019A850;
    extern void * D_8019A854;
    extern unsigned char D_801834C0;
    extern unsigned char D_801834D8;
    extern unsigned char D_8018354C;
    extern unsigned char D_80183554;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_8019A850 = &D_801834C0;
        D_8019A854 = &D_8018354C;
    } else {
        D_8019A850 = &D_801834D8;
        D_8019A854 = &D_80183554;
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
// three bases (D_80115110/D_80183848/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80183848 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_80183848;
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
        v = ((s32 *)&D_80183848)[i] >> 6;
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
extern void func_801376E8(int a0, int a1);
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
    extern unsigned char D_80183824;
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_80183824));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_80183824));
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


INCLUDE_ASM("asm/ov_SC03_107/nonmatchings/ov_SC03_107_jr_8013C98C", func_8013EE10);

extern void func_8013FAF8(s16 a0, s16 a1);


// @class: struct
// @stuck: none — MATCH (108 ins, relocation-masked)




s32 func_8013EF88() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_801151D0;
    extern s16 D_80183820;
    extern s16 D_80183822;
    extern int func_800D0488(int);
    extern void func_800D2624(void);
    extern S115118 D_80115118;
    extern int D_80115168;
    extern unsigned short D_80115114;

    unsigned short v;
    short i;
    register short *p124 __asm__("$16");

    v = D_80115118.field0;
    if (v != 0) {
        v = v - 1;
        D_80115118.field0 = v;
        if (v != 0) {
            (*(int*)&D_801151D0) = D_80115118.arrB0[(*(unsigned short*)&D_800B9A02)];
            ((void(*)(int, int))func_8013FAF8)(0, 5);
            for (i = 0; i < 5; i++) {
                int a = *(int *)((char *)&(*(int*)&D_80115188) + (i << 2));
                int b = *(int *)((char *)&D_80115168 + (i << 2));
                int w = a * 3;
                *(int *)((char *)&(*(int*)&D_80115188) + (i << 2)) = w;
                *(int *)((char *)&D_80115168 + (i << 2)) = b + w;
            }
            if (D_80115118.field0 < 3) {
                unsigned short *p96 = &(*(unsigned short*)&D_80183822);
                *p96 = *p96 - 1;
            }
            {
                unsigned short *p94 = &(*(unsigned short*)&D_80183820);
                short t = *p94 - 2;
                *p94 = t;
                if (t < 0) *p94 = 0;
            }
        }
    }
    p124 = &(*(short*)&D_80115124);
    {
        short x124 = *p124;
        if (x124 != 0) {
            if (func_800D0488(x124) == 0) return;
            *p124 = 0;
        }
    }
    if (D_80115118.field0 == 0) {
        if (D_80115114 == ((*(unsigned short*)&D_800B9A02) ^ 1)) {
            func_800D2624();
        } else {
            D_80115112 = D_80115112 + 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_80183824;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80183824);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */


