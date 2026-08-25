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
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
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
extern s32 D_80184124;
extern void func_8013373C(s32 a0);
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
/* ==== end §8b carried decl layer ==== */


// @class: struct
// @stuck: none — MATCH (289 ins). symcheck: only the cosmetic jtbl_801D81B8 floor (§8 carve).
//
// func_80135EB0 — h_seq family exemplar (x138 across the overlay fleet). Levers that made it:
//  1. m2 (the y-axis mask) MUST be the if/else form, NOT `m2=0x10; if (a8<=t3) m2=...`.
//     Both emit the same compact `bnez; li $s2,0x10` pair, but the pre-init form lets CSE carry
//     the D_8017E910 pointer load into the (m1|m2)==0 block; the if/else form ends the CSE
//     extended-BB so the block reloads `lui/lw D_8017E910` (target does). Worth 2 ins + the whole
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

extern u8 D_8017E910;
extern u8 D_8017E914;
extern s16 *D_8017E918;
extern u8 D_8017E91C;
extern s32 D_801150D8;
extern u8 D_80126720[];

extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 func_801365B8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32, s32, s32);

s32 func_80135EB0(void *arg0, s32 arg1_) {
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

    t1 = (*(s16 **)&D_8017E910)[0];
    if (t1 < M2C_FIELD(arg0, s16 *, 4)) {
        m1 = 1;
    } else {
        m1 = (M2C_FIELD(arg0, s16 *, 6) < t1) << 1;
    }
    t2 = (*(s16 **)&D_8017E910)[2];
    if (t2 < M2C_FIELD(arg0, s16 *, 0xC)) {
        m1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t2) {
        m1 |= 8;
    }
    t3 = (*(s16 **)&D_8017E910)[1];
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

        ac = *(u16 **)&D_8017E910;
        b4 = D_8017E918;
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

    t4 = (*(s16 **)&D_8017E914)[0];
    if (t4 < M2C_FIELD(arg0, s16 *, 4)) {
        n1 = 1;
    } else {
        n1 = (M2C_FIELD(arg0, s16 *, 6) < t4) << 1;
    }
    t5 = (*(s16 **)&D_8017E914)[2];
    if (t5 < M2C_FIELD(arg0, s16 *, 0xC)) {
        n1 |= 4;
    } else if (M2C_FIELD(arg0, s16 *, 0xE) < t5) {
        n1 |= 8;
    }
    t6 = (*(s16 **)&D_8017E914)[1];
    if (t6 < M2C_FIELD(arg0, s16 *, 8)) {
        n2 = 0x10;
    } else {
        n2 = (M2C_FIELD(arg0, s16 *, 0xA) < t6) << 5;
    }
    if (((m1 | m2) & (n1 | n2)) != 0) {
        goto ret0;
    }
    {
        u16 *b0 = *(u16 **)&D_8017E914;
        u16 *ac = *(u16 **)&D_8017E910;
        s16 *b8 = *(s16 **)&D_8017E91C;

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
    extern u8 D_8017E910;
    extern u8 D_8017E914;
    extern s16 *D_8017E918;
    extern u8 D_8017E91C;
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
        dx = (s16) arg2 - (*(s16 **)&D_8017E910)[2];
        d = dx;
        denom = -(*(s16 **)&D_8017E91C)[2];
    } else {
        denom = (*(s16 **)&D_8017E91C)[2];
        d = (*(s16 **)&D_8017E910)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_8017E91C;
        u16 *ac = *(u16 **)&D_8017E910;
        b4 = D_8017E918;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_8017E914;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_8017E918[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_8017E918[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}



// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_8017E910/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_8017E918 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern u8 D_8017E910;
    extern u8 D_8017E914;
    extern s16 *D_8017E918;
    extern u8 D_8017E91C;
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
        var_v1 = (s16) arg2 - (*(s16 **)&D_8017E910)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_8017E91C)[0];
    } else {
        var_a3 = (*(s16 **)&D_8017E91C)[0];
        var_v1 = (*(s16 **)&D_8017E910)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_8017E910;
    b4 = D_8017E918;
    b8 = *(s16 **)&D_8017E91C;
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
        b4[1] = (s16) (*(u16 **)&D_8017E914)[1];
        b4[2] = (s16) (*(u16 **)&D_8017E914)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_8017E918, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_8017E918, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_8017E910/B0/B8 are file-scope `extern u8`, D_8017E918 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_8017E918 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern u8 D_8017E910;
    extern u8 D_8017E914;
    extern s16 *D_8017E918;
    extern u8 D_8017E91C;
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
        var_t0 = (s16) arg2 - (*(s16 **)&D_8017E910)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_8017E91C)[1];
    } else {
        var_a3 = (*(s16 **)&D_8017E91C)[1];
        var_v1 = (*(s16 **)&D_8017E910)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_8017E91C);
    ac = (*(u16 **)&D_8017E910);
    b4 = D_8017E918;
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
        p = (*(u16 **)&D_8017E914);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_8017E918;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_8017E918;
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
    extern s16 *D_8017E918;   /* holds a pointer value (*(u16**)&D_8017E918) */
    extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)a3, *(void **)&D_8017E918, *(void **)&D_8017E918);
        ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_8017E918;
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
    extern void (*D_8017E92C[])(void);
    D_8017E92C[D_800B99F0]();
}




s32 func_80136C90()
{
    extern void func_8001534C(int, void *, int, int, int, int);
    extern S10_80136C90 D_80182F70;
    S10_80136C90 buf = D_80182F70;
    func_8001534C(0, &buf, 0x78, 0x10, 0, 0);
}


void func_80136D00(void) {
}

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136d08 (src/shared) */


DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136dfc (src/shared) */


void func_80136EC4(void) {
}

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ecc (src/shared) */


DEFINE_func_80136F3C()  /* dedup: shared engine-core @0x80136f3c (src/shared) */


DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


DEFINE_func_80137178()  /* dedup: shared engine-core @0x80137178 (src/shared) */


DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372b0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375ec (src/shared) */


extern void func_801375EC(s32 a0, s16 a1);

// @class: schedule (arg-copy placement) — PIN-FREE
// match_one: MATCH (26 ins).  rtu: MATCH (26 ins) with NO //@EDIT and NO header edit.
//
// ---- RECONCILE 2026-08-01 (uc2 -> uc3) ---------------------------------------------------
// GATE ERROR was:
//   jr_80135D20.c:1412 conflicting types for func_80137614 || :1362 previous declaration
// :1362 is `DEFINE_func_801375EC()`, whose expansion (src/shared/engine_core.h:2819) carries
//   extern void func_80137614(s32 a0, s32 a1, s32 a2);
// and it is instantiated two lines ABOVE this function's INCLUDE_ASM splice point (:1364).
// :1412 is this draft's own definition.  So the conflicting symbol is func_80137614 ITSELF
// and the axis is the §73 RETURN type: the shared header says `void`, the target ends
// `addu $v0, $s0, $zero` and callers in other overlays consume the result
// (ov_SC03_099_jr_80178D40.c already declares it `extern s32 func_80137614(s32,s32,s32)`),
// so the definition MUST stay s32.  Re-voiding the definition is the decay loop: gcc-2.7.2
// silently drops the $v0 set and you get 25/26 ins, class LENGTH-DRIFT/-1.
//
// ESCAPE USED: §37/§124 ASM-LABEL ALIAS (escape #2).  The definition is given a distinct C
// identifier `aF80137614` with __asm__("func_80137614"), so it never collides with the
// header's `extern void func_80137614` while still emitting the canonical symbol.  Zero
// header edits, zero TU edits, blast radius 0 — this replaces uc2's //@EDIT §65b de-macroize
// of DEFINE_func_801375EC, which would have had to be repeated at all 138 sweep sites.
// The TU already uses this exact idiom 60-odd lines below
// (`void *aF801376E8(int a0, int a1) __asm__("func_801376E8");`), so it travels to siblings.
// The in-TU call from func_801375EC still binds to the header's extern declaration and
// resolves to the same symbol at link time; func_801375EC's own 10 instructions are unchanged.
//
// ---- CODEGEN (unchanged from uc2 — do not touch) -----------------------------------------
// Residual before the lever: 4 mismatched, the (sw $sN / addu $sN,$aX) prologue PAIRS mirrored —
// target births $s2<-a2 then $s3<-a1; the naive draft births $s3<-a1 then $s2<-a2 (parm order),
// and drags `sw $s3` above `sw $s2` with it.  Register ASSIGNMENT was already right in both, so
// this is NOT a regalloc problem.  Measured INERT: body statement order, extra plain locals,
// K&R parm-declaration order (incl. declaring a2 before a1 in the K&R decl block).
//
// LEVER — cookbook §67 (arg-copy PLACEMENT).  One zero-instruction launder of the a1 parameter
// pins WHERE its entry copy materialises; a2's copy then takes the earlier slot and the register
// saves fall back into ascending order.  DIRECTION MATTERS and is the opposite of the intuition:
// laundering a2 (the copy that must move EARLIER) is inert — launder the copy that must land
// LATER.  §67 rule 1 respected: the laundered local is NOT pinned.  A pinned variant
// (register s32 __asm__("$18") / __asm__("$19") on a2/a1) also MATCHes, but pins are strictly
// worse for the ×138 family sweep (§42e/§86 pin guard), so the pin-free single launder is banked.
//
// Shape copied from the matched next-door sibling DEFINE_func_8013767C() (engine_core.h),
// which is this function minus the 0xD8 mask and the +0x1C halfword store.

extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);

s32 aF80137614(s32 a0, s32 a1, s32 a2) __asm__("func_80137614");

DEFINE_func_80137614()  /* dedup: shared engine-core @0x80137614 (src/shared) */


DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767c (src/shared) */


DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376c8 (src/shared) */



/* @class: plumbing (globals-around-two-calls)
 * @stuck: none — MATCH (51 ins).
 *
 * RECONCILE (§37/§124 ASM-LABEL ALIAS) — no TU / header edit required.
 *   Gate error: ov_SC01_077_jr_80135D20.c:1415: conflicting types for `func_801376E8'
 *               || previous declaration at :1368
 *   :1368 is DEFINE_func_801376C8(), the shared engine-core macro that carries
 *   `extern void func_801376E8(int a0, int a1);` — a VOID return. The target's last
 *   pre-epilogue instruction is `addu $v0, $s1, $zero`, i.e. it RETURNS &D_801269F0,
 *   so the definition MUST be non-void; a `void` definition makes gcc-2.7.2 merely warn
 *   and DROP the returned value, killing that instruction (LENGTH-DRIFT/-1, 50 ins).
 *   The conflict is on func_801376E8 ITSELF and is a pure RETURN-type disagreement
 *   (params already agree: int,int), so the §37/§124 alias applies verbatim:
 *   define under the C name aF801376E8 with __asm__("func_801376E8") so the C-level
 *   declaration never collides, while the emitted symbol is still func_801376E8.
 *   Codegen is untouched — an asm label renames the symbol, nothing else.
 *   (The earlier draft's `//@EDIT` widening of the shared extern to `void *` is a
 *   T2 fleet-shared edit; the alias is T0 draft-only. Cookbook §124: fix the reader,
 *   not the source.)
 *
 * Byte levers (unchanged from the passing draft):
 *  - `obj` local holding (s32)&D_801269F0: the address is CSEd ONCE into $s1 and reused
 *    for both jal args and the return (same idiom as the neighbouring func_80137B80).
 *  - D_80126A24 is s16 (`lh`) but D_80126A26 is u16 (`lhu`) with an explicit (s16) cast
 *    at the use site: gcc combines the cast's `sll 16; sra 16` with the `>>1` into
 *    `sll 16; sra 17`, which is exactly what the target emits. A plain s16 D_80126A26
 *    would give `lh; sra 1` instead.
 *  - D_80126A14 as u16[2] (`lhu` loads, `%lo(D_80126A14 + 0x2)` for element 1).
 */


extern void func_801377B4(s32 a0, s32 a1, s32 a2);
extern void func_80139BE0(s32 a0);

void *aF801376E8(int a0, int a1) __asm__("func_801376E8");

DEFINE_func_801376E8()  /* dedup: shared engine-core @0x801376E8 (src/shared) */


DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377b4 (src/shared) */


DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */



extern void func_80016714(void *a0, s32 a1);
extern void func_8013A860(void);

void func_801378F0(void) {

    extern u8 D_80127520[];
    extern u8 aD801269F0[] __asm__("D_801269F0"); /* §37 alias: TU canon is `extern int D_801269F0` */
    extern u8 D_80126A28[];
    extern u8 D_8017E934[];
    s32 i;
    s32 si;
    s32 di;
    u8 *p;

    func_80016714(D_80127520, 0xBFC);
    i = 0;
    si = 0;
    p = aD801269F0;
    di = 0;
    do {
        func_80016714(p, 0x4C);
        *(u16 *)&D_80126A28[di]     = *(u16 *)&D_8017E934[si];
        *(u16 *)&D_80126A28[di + 2] = *(u16 *)&D_8017E934[si + 2];
        *(u16 *)&D_80126A28[di + 4] = *(u16 *)&D_8017E934[si + 4];
        *(u16 *)&D_80126A28[di + 6] = *(u16 *)&D_8017E934[si + 6];
        p += 0x4C;
        i += 1;
        si += 8;
        di += 0x4C;
    } while (i < 3);
    func_8013A860();
}


DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379d8 (src/shared) */


DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379ec (src/shared) */


DEFINE_func_801379FC()  /* dedup: shared engine-core @0x801379fc (src/shared) */




// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern void func_80138BE0(int p);

void func_80137B80(void) {

    extern s32 D_80127548[];
    extern int D_8017E980;
    extern int D_801269F0;
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8017E980 += 1;
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
    extern int D_8017E980;
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
        if (D_8017E980 & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137dd4 (src/shared) */


DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137fd8 (src/shared) */

