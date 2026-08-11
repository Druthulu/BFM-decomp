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
extern u8 D_8017F6D4[];
void func_8002D4C8(s32 a0, s32 a1);
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
extern void func_80142BB4(s32 *param_1, s32 param_2, s32 param_3);
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
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
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
extern void (*D_8017FE70[])(void *);
extern void func_8014C6F4();
extern void func_80155150(s32 a0);
extern void func_801470C0(s32 a0);
extern void func_80147478(s32 a0);
extern void func_80147118(s32 a0);
extern void func_8014BDE8(s32 a0);
extern short func_801508F8(s32 a0);
extern void func_8014B5B0(s32 *a0);
extern void func_80161D88(s32 a0);
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
extern void func_80149544(s32 a0, s32 a1, s32 a2);
extern void func_80149584(s32 a0, s32 a1, s32 a2);
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
extern u8 D_80078E78[];
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
extern void func_8014D3E0(s32 a0);
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
extern s32 func_8014F468(void);
extern int func_8014F6F4(void);
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
extern s32 func_801659DC(u8 *a0);
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
extern s32 D_8011F730;
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern void func_801578C0(s32 a0);
extern void func_80157788(s32 *a0);
extern void func_80157808(s32 *a0);
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

    extern void (*D_80180A1C[])(void *);

    extern s32 D_800D5428;
    extern u8 D_801809A0[];
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
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
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
            D_80180A1C[*(u16 *)arg0]((void *)arg0);
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
            D_80180A1C[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80180A1C[*(u16 *)arg0]((void *)arg0);
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
            D_80180A1C[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }

    if (func_80149CD4(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) == 0) {
        sv = *(s32 *)(arg0 + 0x2C);
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
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
        ((void (*)(s32, s32))func_80146DB8)(arg0, (s32)&(*(s32 *)&D_801809A0));
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
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
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

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015ab7c (src/shared) */


DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015abd4 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (param held in $s0 across 3 calls; lhu 0x16E; &D_801809B0 arg)
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80161CD0(s32 a0, s32 a1);

void func_8015AC48(s32 arg0)
{

    extern M2C_UNK D_801809B0;
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, &D_801809B0);
    func_80161CD0(arg0, M2C_FIELD(arg0, u16 *, 0x16E));
}


DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015ac90 (src/shared) */


DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015acc4 (src/shared) */


DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015ad08 (src/shared) */




void func_8015AD3C(void *a0) {

    extern void (*D_80180B74[])(void);
    D_80180B74[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015ad78 (src/shared) */


DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015adb0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015AE2C);

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015b6f4 (src/shared) */


DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015b7b4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015B858);

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015b8f8 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015bd8c (src/shared) */


DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015bdd0 (src/shared) */


DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015be04 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015BE38);

DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015be74 (src/shared) */


DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015be94 (src/shared) */


DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015bec4 (src/shared) */


DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015bee4 (src/shared) */


DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015bf04 (src/shared) */


DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015bf48 (src/shared) */


DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015bf7c (src/shared) */


DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015bfb0 (src/shared) */




void func_8015BFF4(void *a0) {

    extern void (*D_80180B9C[])(void);
    D_80180B9C[*(u16 *)((s32)a0 + 0x2)]();
}



/* §71 sibling-first: this is DEFINE_func_8015C0C4 (src/shared/engine_core.h L8919)
 * with the two globals replaced by the second parameter and <<6 -> <<7.
 * The explicit temporary `t` keeps the first lh ahead of the 0x238 store.
 *
 * Signature is the fleet canon `(s32 *a0, s32 a1)` declared by
 * DEFINE_func_8015BFB0 (engine_core.h L16218) — a private `(s32, s16 *)`
 * definition also match_one-MATCHes but breaks the real TU with
 * `conflicting types`.  The s16 reads are cast at the use site. */

extern void func_80154150(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80146CA0(void *a0);

void func_8015C030(s32 *a0, s32 a1)
{
    s32 t = *(s16 *)a1 << 7;
    *(s32 *)((s32)a0 + 0x238) = 0x80000;
    *(s32 *)((s32)a0 + 0x234) = t;
    *(s32 *)((s32)a0 + 0x23C) = *(s16 *)(a1 + 4) << 7;
    func_80154150((s32)a0, 0x11);
    func_801553A8(a0);
    func_80146CA0((void *)a0);
}


DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015c08c (src/shared) */


DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015c0c4 (src/shared) */



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

    extern void (*D_80180A1C[])(void *);

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
        D_80180A1C[*(u16 *)((int)param_1)](((int)param_1));
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
        D_80180A1C[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015C32C);

void func_8015C6A4(void) {
}

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015c6ac (src/shared) */


DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015c6e0 (src/shared) */




void func_8015C714(void *a0) {

    extern void (*D_80180BA8[])(void);
    D_80180BA8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015c750 (src/shared) */


DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015c788 (src/shared) */



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

    extern void (*D_80180A1C[])(void*);
    extern int D_801809C0;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_80180A1C)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_80180A1C)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_801809C0);
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

    extern void (*D_80180A1C[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_80180A1C[*(unsigned short *)param_1])(param_1);
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

    extern void (*D_80180A1C[])(void*);
    extern int D_801809C0;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_80180A1C)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_801809C0);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_80180A1C)[*param_1](param_1);
    ((void (*)(u16 *, int))func_80147078)(param_1, 0);
    ((void (*)(u16 *))func_80159B70)(param_1);
    return;
do161240:
    ((void (*)(u16 *))func_80161240)(param_1);
}


DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015cb94 (src/shared) */


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

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015cc0c (src/shared) */


DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015cc40 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015CC74);

DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015ccb0 (src/shared) */


DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015ccd0 (src/shared) */



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

    extern void (*D_80180A1C[])(void *);
    extern u8 D_801809D0;
    extern u8 D_80180BC0;
    extern u8 D_80180BD0;

    s32 temp_v0;
    s32 var_v0;
    struct Sub_8015CD20 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(struct Ent_8015CD20 *))func_801496D4)(((struct Ent_8015CD20 *)arg0)) != 0) {
        D_80180A1C[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((struct Ent_8015CD20 *)arg0)->unk1BC = 0xA;
        ((s32(*)(struct Ent_8015CD20 *))func_80149724)(((struct Ent_8015CD20 *)arg0));
        if (((s32(*)(struct Ent_8015CD20 *))func_80148AFC)(((struct Ent_8015CD20 *)arg0)) & 0xFF) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_801809D0);
        } else {
            ((void(*)(struct Ent_8015CD20 *))func_80146D90)(((struct Ent_8015CD20 *)arg0));
        }
        return;
    }
    temp_v0 = ((struct Ent_8015CD20 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(struct Ent_8015CD20 *))func_80148980)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80180BC0);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x15);
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0xAA;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_8014891C)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80180BD0);
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
        D_80180A1C[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((void(*)(struct Ent_8015CD20 *, s32))func_80147078)(((struct Ent_8015CD20 *)arg0), 0);
        ((void(*)(struct Ent_8015CD20 *))func_80159B70)(((struct Ent_8015CD20 *)arg0));
    } else {
        ((void(*)(struct Ent_8015CD20 *))func_801725E0)(((struct Ent_8015CD20 *)arg0));
    }
}


DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015cf24 (src/shared) */


DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015cf58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015cf8c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015CFC0);

DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015cffc (src/shared) */


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_80180BE0;

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
    *(int *)(param_1 + 0x38) = (int)&D_80180BE0 | 0x40000000;
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

    extern void (*D_80180A1C[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_80180A1C[*(u16 *)arg0](arg0);
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

    extern void (*D_80180A1C[])(void*);
    extern s32 D_80180BFC;
    extern s32 D_80180C00;
    extern s32 D_80180C44;
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
        ((void (**)(s32*))D_80180A1C)[*(u16 *)a0](a0);
        ((void (*)(s32 *))func_80149724)(a0);
        func_80154274(a0, (s32)&D_800D4C14);
        func_80146E90(a0, 0x10);
        {
            u32 t = keep & 0xFFF; /* L3: unsigned value, signed guard -> bgez + srl */
            if ((s32)t < 0) {
                t += 0x1FF;
            }
            p = &D_80180C44; /* L4 + scheduling: the `la` must precede the srl/sll pair */
            off = (t >> 9) * 8;
        }
        *p = *(s32 *)((u8 *)&D_80180BFC + off);
        ((void (*)(s32 *, s32))func_80146DB8)(a0, (s32)(p - 2)); /* 0x801893D8 == &D_80180C44[-2] (no label there) */
        func_801477E8(a0, *(s32 *)((u8 *)&D_80180C00 + off));
        func_80147324(0x5EA);
    } else {
        ((void (*)(s32 *))func_8014FA04)(a0);
        if (((s32 (*)(s32 *))func_8014E6A0)(a0) == 0) {
            ((void (**)(s32*))D_80180A1C)[*(u16 *)a0](a0);
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

    extern s32 D_80180C4C;
    s16 out[4];
    s32 buf[8];
    register s32 s1 __asm__("$17") = a0;
    register s32 *s0 __asm__("$16") = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)s0, (void *)&D_80180C4C, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}



// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_8017FD30[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_8017FD30;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015d480 (src/shared) */


DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015d4b4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015D4E8);

DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015d524 (src/shared) */


DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015d544 (src/shared) */


DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015d57c (src/shared) */



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

    extern unsigned char D_80180C60[];
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
                (short)((signed char)D_80180C60[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_80180C60[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_80180C60[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015da5c (src/shared) */


DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015da90 (src/shared) */


DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015dac4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015DAF8);

DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015db34 (src/shared) */


DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015db6c (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015dc84 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {

    extern s8 D_80180C9C[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015dd74 (src/shared) */


DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015ddf0 (src/shared) */


DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015de24 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015DE58);

DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015de94 (src/shared) */


DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015decc (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015dfe4 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {

    extern s8 D_80180C9C[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80180C9C[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015e0d4 (src/shared) */


DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015e150 (src/shared) */


DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015e184 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015E1B8);

DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015e1f4 (src/shared) */


DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015e22c (src/shared) */


DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015e288 (src/shared) */



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

    extern void (*D_80180A1C[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_80180A1C)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015e40c (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{

    extern u16 D_80180CE4;
    extern u16 D_80180CE6;
    extern u16 D_80180CE8;
    extern s32 D_80180CEC;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80180CE4 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80180CE6 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80180CE8 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_80180CEC, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


extern s32 func_8013C9C4(s32 *a0);
void func_8015E588(void) {

    extern s32 D_80180CF4;
    func_8013C9C4(&D_80180CF4);
}


DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015e5b0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */

void func_8015E698(u16 *param_1)
{

    extern void (*D_80180A1C[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_80180A1C)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015e714 (src/shared) */


DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015e84c (src/shared) */


DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015e880 (src/shared) */


DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015e8b4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015E8E8);

DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015e924 (src/shared) */


DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015e95c (src/shared) */


DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015e9b8 (src/shared) */



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

    extern void (*D_80180A1C[])(void *);
    extern s16 D_801152A0;
    s32 invec[4];
    s32 outbuf[4];
    s32 temp;
    s32 r;

    if (!(((s32 (*)(void))func_801487F4)() & 8)) {
        D_80180A1C[*(u16 *)arg0](arg0);
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
    D_80180A1C[*(u16 *)arg0](arg0);
    ((void (*)(void *))func_80175150)(arg0);
    return;
Lcase2:
    ((void (*)(s32, s32))func_8016EE40)(*(s32 *)((u8 *)arg0 + 0x21C), 0x01000000);
    return;
Ldefault:
    if (((s32 (*)(void *))func_80149744)(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149788)(arg0);
        return;
    }
    if (func_80161B84(arg0) != 0) {
        return;
    }
    if (func_8014A4B4(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_8014A4FC)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149AA8)(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149AD4)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149B54)(arg0) != 0) {
        D_80180A1C[*(u16 *)arg0](arg0);
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
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80161208)(arg0) == 0) {  /* §17a-1 */
        ((void (*)(void *))func_801483E8)(arg0);
    }
}


DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ed6c (src/shared) */


DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015eda0 (src/shared) */


DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015edd4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015EE08);

DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015ee44 (src/shared) */



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
    extern int D_80180A00;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_80180A00);
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

    extern void (*D_80180A1C[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_80180A1C[*(u16 *)arg0](arg0);
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

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015efa4 (src/shared) */


DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015efd8 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015F00C);

DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015f048 (src/shared) */


DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015f080 (src/shared) */


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
    extern void (*D_80180A1C[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_80180A1C[*(u16 *)a0])(a0);
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


DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015f260 (src/shared) */


DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015f2bc (src/shared) */


DEFINE_func_8015F2F0()  /* dedup: shared engine-core @0x8015f2f0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015F324);

DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015f360 (src/shared) */


DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015f380 (src/shared) */




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

    extern void (*D_80180A1C[])(void *);

    extern u8 D_80062BD0;
    extern s32 D_80180D28;
    extern s32 D_80180D38;
    extern s32 D_80180D48;
    s32 sp20[2];
    s32 sp28[2];

    if (((*(u32 *)(arg0 + 0x44) & 0x100) && (func_80149884() != 0)) ||
        (((s32 (*)(s32))func_801496D4)(arg0) != 0)) {
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
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
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80180D28);
            } else {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80180D38);
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
        D_80180A1C[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFE80000);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80180D48);
        ((void (*)(s32, s32))func_80146E90)(arg0, 0x10);
        return;
    }

    func_8014ED28(arg0);
    func_8014FA04(arg0);
    ((void (*)(s32))func_801725B8)(arg0);
}


DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015f738 (src/shared) */


DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015f76c (src/shared) */


DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015f7a0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015F7D4);

DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015f810 (src/shared) */


DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015f848 (src/shared) */



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208();

void func_8015F89C(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_80180A1C[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015f948 (src/shared) */



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_8015F9A4(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_80180A1C[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015fa24 (src/shared) */


DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015fa44 (src/shared) */


DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015fa78 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8015FAAC);


extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_80180A1C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_80180A1C[*(u16 *)arg0](arg0);
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

    extern void (*D_80180A1C[])(void *);
    extern u8 D_80078EC1;
    extern u16 D_801270C0;
    extern u8 D_800B9A17;
    if (param_1[0x61] < 0) {
        ((void (**)())D_80180A1C)[*(u16 *)param_1]();
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
    extern void (*D_80180A1C[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_80180A1C[*(u16 *)param_1](param_1);
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

    extern unsigned int D_80180D78[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_80180D78[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015fdcc (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{

    extern void (*D_80180A1C[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_80180A1C)[param_1[0]]();
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
    extern void (*D_80180A1C[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_80180A1C[*(u16 *)param_1](param_1);
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


DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004c (src/shared) */


DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007c (src/shared) */


DEFINE_func_801600D0()  /* dedup: shared engine-core @0x801600d0 (src/shared) */


DEFINE_func_80160104()  /* dedup: shared engine-core @0x80160104 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80160138);

DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */


DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601ac (src/shared) */


DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601e4 (src/shared) */


DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */



extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {

    extern void (*D_80180A1C[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_80180A1C)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


void func_8016032C(void) {
}

DEFINE_func_80160334()  /* dedup: shared engine-core @0x80160334 (src/shared) */


DEFINE_func_80160368()  /* dedup: shared engine-core @0x80160368 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016039C);

DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603d8 (src/shared) */


DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */








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
extern void func_8015F00C(s32 *a0);

void func_80160534(u8 *p) {

    extern u8  D_80078EC0;
    extern u8  D_80078EBF;
    extern s16 D_801152A0;
    extern void (*D_80180A1C[])(void *);
    func_80149020((s32 *)p);
    func_80149034((s32 *)p);
    if ((D_80078EC0 & 0x7F) != 0 && (func_80148800((s32 *)p) & 0x90) != 0) {
        if (D_80078EBF == 0x80) {
            D_80180A1C[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x13);
            func_8015F00C((s32 *)p);
            return;
        }
        if (func_80149B54((s32 *)p) != 0) {
            D_80180A1C[*(u16 *)p](p);
            func_80149BAC((s32 *)p);
            return;
        }
    }
    if (func_80149AA8((s32 *)p) != 0) {
        D_80180A1C[*(u16 *)p](p);
        func_80149AD4((s32 *)p);
        return;
    }
    if (func_80146E98((s32)p) != 0) {
        if ((func_801487F4((s32 *)p) & 8) != 0) {
            D_80180A1C[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x11);
            func_8015E9B8((s32 *)p);
        } else {
            D_80180A1C[*(u16 *)p](p);
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
        D_80180A1C[*(u16 *)p](p);
        func_80147078((s32 *)p, 9);
        func_8015C714(p);
    } else {
        ((s32 (*)(void *))func_80161208)(p);
    }
}


DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607b8 (src/shared) */


DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607e4 (src/shared) */


DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016084C);

DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */


DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608c0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)



extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_80180A1C[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_80180A1C)[*param_1](param_1);
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

    extern void (*D_80180A1C[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_80180A1C)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160a28 (src/shared) */


DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160a74 (src/shared) */


DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160acc (src/shared) */


DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160b00 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80160B34);

DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160b70 (src/shared) */


DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160bb4 (src/shared) */


DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160c28 (src/shared) */


DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160cb4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_80180A1C + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_80180A1C[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_80180A1C[*(u16 *)arg0](arg0);
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
        D_80180A1C[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160dec (src/shared) */


DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160e3c (src/shared) */


DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160e70 (src/shared) */




void func_80160EA4(void *a0) {

    extern void (*D_80180E28[])(void);
    D_80180E28[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160ee0 (src/shared) */


DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160f00 (src/shared) */


DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160f70 (src/shared) */


DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160fe0 (src/shared) */



// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{

    extern void (*D_80180A1C[])(void *);
    func_80149020(a0);
    D_80180A1C[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */


void func_801610FC(void) {
}

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80161124);


extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016130C(void*, s32);
void aF80161208(void *a0) __asm__("func_80161208");
void aF80161208(void *a0)
{
    ((s32 (*)(s32, u32))func_8016130C)(a0, func_801612B8(a0, 0));
}


DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */


DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */


DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612b8 (src/shared) */


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


extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);
extern void func_80015954(s32, s32);

int func_80161374(int param_1, unsigned int param_2) {

    extern int D_801152BC;
    if ((param_2 == 0) || (param_2 == 0x8000)) {
        ((void (*)(int))func_801599A4)(param_1);
        ((void (*)(int))func_8015BDD0)(param_1);
        return 1;
    }
    if ((param_2 & 0x4000) != 0) {
        if ((D_801152BC != 0) ||
            (*(short *)(param_1 + 10) >= *(short *)(param_1 + 0x8a))) {
            ((void (*)(int))func_801599A4)(param_1);
            ((void (*)(int))func_8015BF48)(param_1);
            return 1;
        }
        ((int (*)(int, int))func_80015954)(param_1 + 0x88, param_1 + 4);
        return 0;
    }
    return 0;
}


DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */


DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */


DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */


DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614e4 (src/shared) */


DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151c (src/shared) */


DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */


DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158c (src/shared) */


DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615c4 (src/shared) */


DEFINE_func_8016163C()  /* dedup: shared engine-core @0x8016163C (src/shared) */

DEFINE_func_80161774()  /* dedup: shared engine-core @0x80161774 (src/shared) */

DEFINE_func_80161888()  /* dedup: shared engine-core @0x80161888 (src/shared) */

extern void func_8016151C(void *a0);
extern s32 func_8016163C(s32 a0, u32 a1);
extern s32 func_80161774(int a0, u32 a1);
extern s32 func_80161888(s32 a0, u32 a1);


// @class: sibling-copy (§71) + asm-label alias on the DEFINITION (§37 / §73 return-axis dodge)
// @stuck: none — match_one MATCH (24 ins) AND rtu_match MATCH (24 ins), real TU, zero fleet edits.
//
// DERIVATION (§71 sibling-first, iteration 1):
//   func_80161888 @ src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c:3640 is an already-MATCHED sibling
//   with the identical flag-dispatch skeleton (1 / 0x4000 / 0x2000 -> 1 / 2 / 4, else 0); this
//   target is that function minus the func_80161D20 consumer call.  Body copied verbatim, call
//   dropped.  int/unsigned int spelling kept from the sibling.  MATCH first try.
//
// WHY THE ASM-LABEL ALIAS (this is the only non-obvious part):
//   The fleet canon declares this function inside a shared macro —
//     src/shared/engine_core.h:3567, DEFINE_func_8016151C():
//       extern void func_8016191C(void *a0, s32 a1);
//   but the byte-true body RETURNS s32 ($v0 = 1/2/4/0), so a plain `int func_8016191C(...)`
//   definition dies with `conflicting types for 'func_8016191C'` in the real TU (rtu CC1 FAIL).
//   That is §73's RETURN axis; a `void` def would DCE the $v0 constants outright.
//   §73's prescribed fix is the fleet widen `extern void`->`extern s32` (T2 / R22) — exactly the
//   edit already applied to the three banked siblings in this same macro block
//   (engine_core.h:3546 func_8016163C -> s32, :3553 func_80161774 -> s32, :3560 func_80161888 -> int).
//   The alias reaches the same place at T0 (draft-only, no tracked file touched): the C identifier
//   is aF8016191C so no decl conflicts, while the emitted SYMBOL is func_8016191C.  The macro's
//   caller func_8016151C keeps calling the `extern void` spelling and is byte-unaffected (it
//   discards the return).  Verified by rtu_match, which extracts by symbol name.
//
//   IF the orchestrator prefers house style over zero-touch: widen engine_core.h:3567 to
//     extern s32 func_8016191C(void *a0, s32 a1);
//   (batch it with any other pending §73 widens, one R22) and then the alias line can be deleted
//   and the definition renamed back to `int func_8016191C(int, unsigned int)`.  Byte-identical
//   either way — confirmed: the same body under the plain name is match_one MATCH in isolation.

extern void func_8014C010(int a0, int a1);

int aF8016191C(int param_1, unsigned int param_2) __asm__("func_8016191C");

int aF8016191C(int param_1, unsigned int param_2) {
    if (param_2 & 1) {
        func_8014C010(param_1, 1);
        return 1;
    }
    if (param_2 & 0x4000) {
        func_8014C010(param_1, 1);
        return 2;
    }
    if (param_2 & 0x2000) {
        func_8014C010(param_1, 1);
        return 4;
    }
    return 0;
}


DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197c (src/shared) */


DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619a4 (src/shared) */


DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619d0 (src/shared) */


DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161a00 (src/shared) */


DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161a30 (src/shared) */


DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161a60 (src/shared) */



extern void func_8014AC10();

void func_80161A90(s32 a0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC0;
    u8 *p = D_80078E78;
    s32 t;

    /* INVERTED diamond: the `t = 0` arm must be the THEN arm.
     * (a) the balanced if/else puts `t = 0` AFTER the branch at regalloc time, so t
     *     does not conflict with the entry `lh` temp and both land in $v0 (an
     *     unconditional `s32 t = 0;` before the if costs $v0 -> $a1, 3 mismatches);
     * (b) with the zero-arm as the THEN arm, reorg steals it into the beqz delay slot
     *     and relax_delay_slots drops the `j` -> 34 ins. The other polarity
     *     (`if (x != 0) t = cmp; else t = 0;`) leaves the `j` + an unfilled slot, +2. */
    if (*(s16 *)(a0 + 0x1C8) == 0) {
        t = 0;
    } else {
        t = ((D_80078EC0 & 0x7F) == 6);
    }
    if (t != 0) {
        /* forces the `lhu 0x1C8($a0)` reload: without it cse reuses the entry `lh`
         * value across the join and folds the reload away. */
        __asm__ __volatile__("" ::: "memory");
        *(u16 *)(a0 + 0x1C8) -= 1;
        /* zero-byte 2nd set of p: kills p's qty-const in cse's skipped-block walk, so
         * `p[0x48]` stays `lbu 0x48($v1)` off the hoisted lui/addiu instead of being
         * folded back into a fresh %hi/%lo pair (cse_expr §H find_best_addr). */
        __asm__("" : "=r"(p) : "0"(p));
    }
    if ((p[0x48] & 0x7F) == 6) {
        if (*(s16 *)(a0 + 0x1C8) == 0) {
            func_8014AC10(0x3B);
        }
    }
}


DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161b18 (src/shared) */


DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161b84 (src/shared) */


s32 func_801497A8(s32 *a0);
void func_801599A4(void *a0);
void func_80149864(void);

s32 func_80161BE0(s32 *a0)
{
  s32 result;

  result = func_801497A8(a0);
  if (result != 0) {
    func_801599A4(a0);
    ((void (*)(void *))func_80149864)(a0);
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

    extern unsigned short D_80180E38[];
    extern unsigned short D_80180E3A[];

    if ((unsigned int)param_2 < 8) {
        if (*(u8 *)(param_1 + 0xDA) != 0) {
            func_80147324(D_80180E38[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 0;
        } else {
            func_80147324(D_80180E3A[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_80180E58[];
    if (param_2 < 8) {
        func_80147324(D_80180E58[param_2]);
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

    extern unsigned short D_80180E68;
    if (param_2 < 8) {
        if (func_800CF8B4() != 0) {
            func_80147324((&D_80180E68)[param_2]);
        }
    }
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161d58 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80161D88);

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
    extern u8 * D_801842A0[];
    extern u8 D_80180E88[];
    extern u8 D_80180EA8[];
    extern u8 D_801842AC[];
    extern u8 D_801842D4[];
    extern u8 D_801842EC[];

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
            D_801842A0[0] = p;
            func_80024054(&D_80180E88, &D_801842AC);
            func_8001CE28(p, &D_801842AC);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801842A0[1] = p;
            func_80024054(&D_80180EA8, &D_801842D4);
            func_8001CE28(p, &D_801842D4);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801842A0[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801842EC, 0x84);
            func_8001CE68(p, &D_801842EC);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801842EC, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620c4 (src/shared) */


DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_8016216C(void)
{

    extern int D_801842A0[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801842A0;
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
    extern s32 D_80180EBC;
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
        return (s32)&D_80180EBC;
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
                return (s32)&D_80180EBC;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80180EBC;
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

    extern int D_801842A0[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801842A0;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_80180EE0[])(void);
    D_80180EE0[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236c (src/shared) */


DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623b8 (src/shared) */


DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */


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
    extern u8 D_80180EEC[];
    extern s32 D_80180F04;
    extern u8 D_80184304[];
    extern u8 D_8018432C[];
    extern u8 D_80184348[];
    extern int D_801842F8[];
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
            D_801842F8[0] = (s32)item;
            func_80024054(D_80180EEC, D_80184304);
            func_8001CE28(item, D_80184304);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801842F8[1] = (s32)item;
            func_80024054(((u8 *)&D_80180F04), D_8018432C);
            func_8001CE28(item, D_8018432C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801842F8[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_80184348, 0x84);
            func_8001CE68(item, D_80184348);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_80184348, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626b8 (src/shared) */


DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_80162760(void)
{

    extern int D_801842F8[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_801842F8;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627c0 (src/shared) */


extern void func_801627C0(void);

// @class: struct
// @stuck: none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_80180F24[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_80180F24[count-1])
//     keeps the array index/decrement separate so %lo(D_80180F24) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).


void func_801627E8(void)
{

    extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_80180F24[])(void);   /* word-stride table of dispatch fn pointers */
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_80180F24[idx]();
    }
}




void func_80162834(void *a0) {

    extern void (*D_80180F28[])(void);
    D_80180F28[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_80180F18;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_80180F18, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628f4 (src/shared) */


DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */


DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162ac0 (src/shared) */


DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162acc (src/shared) */


DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162ae0 (src/shared) */


DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162af4 (src/shared) */


DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162b1c (src/shared) */


void func_80162CC4(void) {
}

INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80162CCC);

DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162d28 (src/shared) */


DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162d88 (src/shared) */


DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162de8 (src/shared) */


DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162e48 (src/shared) */


DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162ea8 (src/shared) */


DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162f08 (src/shared) */


DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162f60 (src/shared) */


DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162f80 (src/shared) */


DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162fa0 (src/shared) */


DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162fc0 (src/shared) */


DEFINE_func_80162FF4()  /* dedup: shared engine-core @0x80162ff4 (src/shared) */


DEFINE_func_801630C4()  /* dedup: shared engine-core @0x801630c4 (src/shared) */


DEFINE_func_80163194()  /* dedup: shared engine-core @0x80163194 (src/shared) */


DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */


DEFINE_func_8016325C()  /* dedup: shared engine-core @0x8016325c (src/shared) */


DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632e0 (src/shared) */


DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632f0 (src/shared) */


DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */


DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633a8 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80163408);

DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345c (src/shared) */



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char aD8018393C_801634D8[8] __asm__("D_8018393C");
    char buf[8];

    memcpy(buf, aD8018393C_801634D8, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


extern void func_80163664(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32);

void func_80163534(a0, a1, a2, a3, a4, a5)
    s32 a0;
    u16 a1;
    u16 a2;
    s32 a3;
    u16 a4;
    u16 *a5;
{

    extern s32 D_80115100;
    extern s32 D_80115200;
    extern s32 D_80115204;
    extern s32 D_80115208;
    extern u16 D_80126B18[];
    extern u16 D_801270B0[];
    extern u16 D_801270B2;
    extern u16 D_801270B4;
    extern u16 D_80126B1A[];
    extern u16 D_80126B1C;
    extern s32 D_80114EB0;
    extern s32 D_80114EC8;
    extern s32 D_8011DAF0;
    extern s32 D_80115298;
    extern s32 D_80126734;
    s32 *p = &D_80115200;

    *p = 0;
    D_80115204 = 0;
    D_80115208 = 0;

    D_801270B0[0] = *(u16 *)(a0 + 0x44) + a5[0];
    D_801270B2 = *(u16 *)(a0 + 0x46) + a5[1];
    D_801270B4 = *(u16 *)(a0 + 0x48) + a5[2];

    D_80126B18[0] = *(u16 *)(a0 + 0x6) + a5[0];
    D_80126B1A[0] = *(u16 *)(a0 + 0xA) + a5[1];
    D_80126B1C = *(u16 *)(a0 + 0xE) + a5[2];

    *p = ((s32 (*)(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32))func_80163664)(a0, a1, a2, (s32)D_801270B0, (s32)D_80126B18,
                               (s32)&D_80114EB0, (s32)&D_80114EC8, (s32)&D_80115100,
                               (s32)&D_8011DAF0, a3, a4, (s32)&D_80115298,
                               (s32)&D_80126734);
}


DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */


DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636d0 (src/shared) */


DEFINE_func_80163764()  /* dedup: shared engine-core @0x80163764 (src/shared) */

DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380c (src/shared) */


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


DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */




void func_80163A58(void *a0) {

    extern void (*D_80180F30[])(void);
    D_80180F30[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163a94 (src/shared) */


DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163c2c (src/shared) */


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
    extern Blk8 D_80183944;
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

    in = D_80183944;
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


DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */


DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642ac (src/shared) */


DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432c (src/shared) */


void func_80164410(void) {
}

DEFINE_func_80164418()  /* dedup: shared engine-core @0x80164418 (src/shared) */


DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_80180F84[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_80180F84[*(u16 *)(param_1 + 2)]();
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
    extern s32 D_80180F4C;
    extern u16 D_80180F80;
    extern s16 D_80180F7E;
    extern s16 D_80180F7C;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_80180F4C;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_80180F80 = 0x80;
        D_80180F7E = 0x80;
        D_80180F7C = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */


extern void func_80162CCC(void);
extern void func_80164ACC();

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_80180F80 read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_80180F80`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.


void func_80164930(s32 param_1) {

    extern s32 D_8011F9D0;
    extern s16 D_80180F7C;
    extern s16 D_80180F7E;
    extern u16 D_80180F80;
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_80180F80 - 8;
        D_80180F80 = nv;
        D_80180F7E = nv;
        D_80180F7C = nv;
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


DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164a74 (src/shared) */


DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164acc (src/shared) */




void func_80164BA0(void *a0) {

    extern void (*D_80180F90[])(void);
    D_80180F90[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_80184358;
    extern u8 D_80184359;
    extern u8 D_8018435A;
    extern u8 D_8018435B;
    extern u8 D_8018435C;
    extern u8 D_8018435D;
    extern u8 D_8018435E;
    extern u8 D_8018435F;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_80184358;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_80184359 = 0xf0;
        *(u8 *)base = 0xf0;
        D_8018435A = 0xc0;
        D_8018435E = 0;
        D_8018435D = 0;
        D_8018435C = 0;
        D_8018435F = 0;
        D_8018435B = 0;
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


DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164cd4 (src/shared) */


DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164d4c (src/shared) */


DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164db0 (src/shared) */


DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164dd0 (src/shared) */







s32 func_80164E40(void) {

    extern u8 D_80184358;
    extern u8 D_80184359;
    extern u8 D_8018435A;
    u8 *p = &D_80184358;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_80184359 != 0) {
        D_80184359 -= 0x10;
    }
    if (D_8018435A != 0) {
        D_8018435A -= 0x10;
    }
    return *(s32 *)p == 0;
}




void func_80164EA4(void *a0) {

    extern void (*D_80180FA0[])(void);
    D_80180FA0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_801843A4[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_801843A4[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164f44 (src/shared) */


DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */


DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */


DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650c4 (src/shared) */


DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */



// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_80184398[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




s32 func_80165140(s32 param_1) {
    extern Slot D_80184398[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_80184398[i];
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

    extern s32 D_80184398;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_80184398;
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

    extern u8  D_80180FB4[];
    extern u32 D_80180FD4, D_80180FD8, D_80180FDC, D_80180FE0;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80180FB4[0x00], p);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80180FB4[0x08], prim + 0x08);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80180FB4[0x10], prim + 0x10);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80180FB4[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_80180FDC;
    *(u32 *)(prim + 0x24) = D_80180FD4;
    *(u32 *)(prim + 0x28) = D_80180FE0;
    *(u32 *)(prim + 0x2c) = D_80180FD8;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}


DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533c (src/shared) */


DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */


DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653b8 (src/shared) */


DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653f4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC1;
    extern void (*D_80180FE4[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_80180FE4[D_80078EC1 & 0x7F])(arg0);
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
    extern void (*D_80180FE4[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80180FE4[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655e4 (src/shared) */


DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_80181060[];
    return D_80181060[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_80181080[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_80181080[a1 & 0x7F];
}


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_801810FC[];
    return D_801810FC[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_8018111C[];
    return D_8018111C[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_8018113C[];
    return D_8018113C[a1 & 0x7F];
}


DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */


DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */


DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657a0 (src/shared) */


DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657d8 (src/shared) */


DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */


DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */


DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658dc (src/shared) */


DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658ec (src/shared) */


DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */


DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */


DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */


DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */


DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */


DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */


DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659a8 (src/shared) */


DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659b8 (src/shared) */


DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659cc (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801659DC);

void func_80165A18(void) {
}

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165a20 (src/shared) */


DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165a50 (src/shared) */


DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165a78 (src/shared) */




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_801811D8[])(void);
    D_801811D8[D_80078EC1 & 0x7F]();
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

    extern void (*D_80181254[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_80181254[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165b6c (src/shared) */


DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165bb4 (src/shared) */


DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165bfc (src/shared) */


DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165c58 (src/shared) */


DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165c78 (src/shared) */


DEFINE_func_80165CA0()  /* dedup: shared engine-core @0x80165ca0 (src/shared) */



void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_8018394C;
    func_8001534C(0, &D_8018394C, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165e90 (src/shared) */


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

    extern void (*D_80181260[])(void);
    D_80181260[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166054()  /* dedup: shared engine-core @0x80166054 (src/shared) */


DEFINE_func_801661CC()  /* dedup: shared engine-core @0x801661cc (src/shared) */


DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */


DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629c (src/shared) */


DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662f4 (src/shared) */


DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634c (src/shared) */


DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663a4 (src/shared) */




void func_801663FC(void *a0) {

    extern void (*D_80181268[])(void);
    D_80181268[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */


DEFINE_func_801665B4()  /* dedup: shared engine-core @0x801665b4 (src/shared) */




void func_80166618(void *a0) {

    extern void (*D_80181330[])(void);
    D_80181330[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_80181340[])(void);
    D_80181340[*(u16 *)((s32)a0 + 0x2)]();
}



   /* 12-byte sub-table record (stride 0xC) */


extern s32 func_80017758(void *a0, void *a1);

s32 func_80166690(s32 param_1, s32 param_2)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    extern u8 D_80184418[];
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
    rec = &D_80184418[i6 * 0xC4];
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

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_80184418).
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
    extern u8 D_80184418[];
    extern void RotTransSV(s32, s32, void*);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_80184418)[param_3];
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
    extern unsigned char D_80184418[];

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
    ((void(*)(void *, int))func_80016714)(&D_80184418[((short)param_4) * 0xc4], 0xc4);
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

    extern u8  D_80181284[];
    extern u8  D_80181270[];
    extern u8  D_80181298[];
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
    p = D_80181284;
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

    p = D_80181270;
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
        p = D_80181298;
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


DEFINE_func_80167714()  /* dedup: shared engine-core @0x80167714 (src/shared) */




void func_801678B4(void *a0) {

    extern void (*D_80181350[])(void);
    D_80181350[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801678F0()  /* dedup: shared engine-core @0x801678f0 (src/shared) */




void func_80167A9C(void *a0) {

    extern void (*D_8018135C[])(void);
    D_8018135C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}






s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {

    extern u16 D_800B99DA;
    extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_80181468;
    extern u8 D_8018147C[];

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

    p = ((u8 *)&D_80181468);
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
    p = D_8018147C;
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
    extern u8   D_801812BC[];
    extern u8   D_801812D0[];
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

    p = D_801812BC;
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

    p = D_801812D0;
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

    extern u8 D_80181314[];
    extern u8 D_801812E4[];
    extern u8 D_801812E5[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80181314[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_801812E4[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_801812E5[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016829C);

DEFINE_func_80168328()  /* dedup: shared engine-core @0x80168328 (src/shared) */


DEFINE_func_801683D8()  /* dedup: shared engine-core @0x801683d8 (src/shared) */



extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_80181320[];
    extern u8 D_801812F8[];
    extern u8 D_801812F9[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80181320[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_801812F8[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_801812F9[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801684B4);

DEFINE_func_80168540()  /* dedup: shared engine-core @0x80168540 (src/shared) */


DEFINE_func_801685EC()  /* dedup: shared engine-core @0x801685ec (src/shared) */


DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */




extern Mat32 D_800AE620;
extern void RotMatrixX(int, void*);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80168664(void *arg0) {
    s32 iVar3;
    void *blk;
    iVar3 = *(s32 *)((u8 *)arg0 + 0x34);
    *(s32 *)((u8 *)arg0 + 0x1c) = 0x20;
    *(s16 *)((u8 *)arg0 + 0x10) = 0x80;
    *(s16 *)((u8 *)arg0 + 0x12) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0x1800;
    *(Blk20 *)((u8 *)arg0 + 0x38) = (*(Blk20 *)&D_800AE620);
    blk = (u8 *)arg0 + 0x38;
    ((s32 (*)(s32, void *))RotMatrixX)(0x400, blk);
    func_80048EAC((void *)(*(s32 *)((u8 *)iVar3 + 0x20) + 0x34), blk);
    func_801670E4((s32)arg0, -6, -0x44, -0x18);
    *(s16 *)((u8 *)arg0 + 2) = *(s16 *)((u8 *)arg0 + 2) + 1;
}




void func_80168744(void *a0) {

    extern void (*D_80181374[])(void);
    D_80181374[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */


DEFINE_func_801687CC()  /* dedup: shared engine-core @0x801687cc (src/shared) */


extern void func_80017E68(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);



void func_80168828(void)
{
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_800173BC(void *a0, void *a1);
    extern u16 D_80181364[];

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
    p = D_80181364;
    for (i = 0; i < 4; i++) {
        svec[0] = *p++;
        svec[2] = *p++;
        ((void (*)(void *, void *))func_80049CAC)(svec, matA);
        func_80048EAC(matB, matA);
        func_800173BC(&thing, matA);
    }
}




void func_801689D8(void *a0) {

    extern void (*D_8018137C[])(void);
    D_8018137C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168a14 (src/shared) */


extern void func_80146C3C(u8*);
void func_80168A88(void) {
    ((void (*)(void))func_80146C3C)();
}




void func_80168AA8(void *a0) {

    extern void (*D_80181384[])(void);
    D_80181384[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168ae4 (src/shared) */


DEFINE_func_80168B70()  /* dedup: shared engine-core @0x80168B70 (src/shared) */

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

    extern void (*D_8018138C[])(void);
    D_8018138C[*(u16 *)((s32)a0 + 0x2)]();
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


DEFINE_func_80168EC4()  /* dedup: shared engine-core @0x80168ec4 (src/shared) */




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

    extern void (*D_80181394[])(void);
    D_80181394[*(u16 *)((s32)a0 + 0x2)]();
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


DEFINE_func_801691B8()  /* dedup: shared engine-core @0x801691b8 (src/shared) */


DEFINE_func_80169228()  /* dedup: shared engine-core @0x80169228 (src/shared) */




void func_801693CC(void *a0) {

    extern void (*D_8018139C[])(void);
    D_8018139C[*(u16 *)((s32)a0 + 0x2)]();
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


DEFINE_func_8016951C()  /* dedup: shared engine-core @0x8016951c (src/shared) */


DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */


DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696d8 (src/shared) */




void func_80169830(void *a0) {

    extern void (*D_801813A4[])(void);
    D_801813A4[*(u16 *)((s32)a0 + 0x2)]();
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


DEFINE_func_801699D0()  /* dedup: shared engine-core @0x801699d0 (src/shared) */


DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169a4c (src/shared) */




void func_80169B80(void *a0) {

    extern void (*D_80181458[])(void);
    D_80181458[*(u16 *)((s32)a0 + 0x2)]();
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
    extern u16 D_801813AC[];
    extern u8 D_8018141C[];
    extern u8 D_8018144C[];
    extern u8 D_80185B38[];
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
    s2 = func_800D222C((void *)arg0, D_8018144C, 0x17);
    if (s2 != 0) {
        *(s32 *)(arg0 + 0x20) = s2;
        rot[0] = rot[0] + D_801813AC[*(s32 *)(arg0 + 0x30)];
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
        *(s32 *)(s2 + 0x34) = (s32)D_80185B38;
        RotMatrixYXZ(rot, D_80185B38);
        func_80048D9C(D_80185B38, mtx);
        *(u16 *)(s2 + 0x18) = 0x5000;
        *(u16 *)(s2 + 0x1A) = 0x2000;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0xC000140;
        func_80128EA8(s2, arg0 + 0x24, (s32)D_8018141C);
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


DEFINE_func_80169E44()  /* dedup: shared engine-core @0x80169e44 (src/shared) */




void func_80169F00(void *a0) {

    extern void (*D_80181460[])(void);
    D_80181460[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(u8*);


void func_80169F3C(int param_1)
{

    extern char D_80181410[];
    extern char D_801813D0[];
    int iVar1;

    ((int (*)(int, int))func_800D1FC8)(param_1, 6);
    iVar1 = func_800D21C4(param_1, D_80181410, 0x16);
    if (iVar1 != 0) {
        *(int *)(param_1 + 0x20) = iVar1;
        *(short *)(iVar1 + 0x1a) = 0x2000;
        *(short *)(iVar1 + 0x18) = 0x2000;
        *(char *)(iVar1 + 0x26) = 0x60;
        *(char *)(iVar1 + 0x25) = 0x60;
        *(char *)(iVar1 + 0x24) = 0x60;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        ((void (*)(int, int, void *))func_80128EA8)(iVar1, param_1 + 0x24, D_801813D0);
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

    extern void (*D_80181498[])(void);
    D_80181498[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016a05c (src/shared) */


DEFINE_func_8016A08C()  /* dedup: shared engine-core @0x8016a08c (src/shared) */


DEFINE_func_8016A1CC()  /* dedup: shared engine-core @0x8016a1cc (src/shared) */


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
    extern u8 D_80181468;
    extern u8 D_8018147C[];

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

    p = ((u8 *)&D_80181468);
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
    p = D_8018147C;
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

    extern void (*D_801814A4[])(void);
    D_801814A4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80048EAC(void *a0, void *a1);

// Seed for func_8016A73C (ov_SC01_077 exemplar). Overlay-local struct guessed.





s32 func_8016A73C(s32 arg0) {
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

    ((Obj_8016A73C *)arg0)->mat = (*(Mat_8016A73C*)&D_800AE620);

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


DEFINE_func_8016A890()  /* dedup: shared engine-core @0x8016a890 (src/shared) */


extern s32 func_80016A5C();
s32 func_8016A8FC(s32 a0)
{
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
    ((s32 (*)(void *, void *))func_80016A5C)(&p, &D_800AE620);
}


DEFINE_func_8016AA50()  /* dedup: shared engine-core @0x8016aa50 (src/shared) */




void func_8016AB30(void *a0) {

    extern void (*D_801814EC[])(void);
    D_801814EC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016AB6C);

INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016b114 (src/shared) */




extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80016ED4(void *a0);


void func_8016B234(s32 param_1) {

    extern u8 D_800AF648;
    extern u8 D_801814E4;
    short input[3];
    Prim_B234 prim;
    struct { s16 xy[2]; s32 sp1c; s32 flag; } out;
    void *dp;
    u32 uVar1;
    s16 iVar2;
    s32 X, Y0, Y1, base, ni;
    register s32 sy __asm__("$16");
    register s16 xtmp __asm__("$4");
    register s32 sxy __asm__("$3");

    dp = &D_800AF648;
    func_8004914C(dp);
    func_800491AC(dp);
    input[0] = *(u16 *)(param_1 + 6);
    input[1] = *(u16 *)(param_1 + 0xA);
    input[2] = *(u16 *)(param_1 + 0xE);
    RotTransPers((s32)input, (s32)out.xy, &out.sp1c, &out.flag);
    if ((out.flag & 0xffffefff) == 0) {
        sxy = *(s32 *)out.xy;
        prim.a04 = 0x10;
        X = *(u16 *)(param_1 + 0x2a) + sxy;
        sy = (u16)out.xy[1];
        prim.ax = prim.cx = X;
        prim.bx = prim.dx = X + 8;
        Y0 = sy - *(u16 *)(param_1 + 0x26);
        prim.ay = prim.by = Y0;
        sxy = *(u16 *)(param_1 + 0x26);
        prim.v0 = prim.v1 = 0x1d0;
        prim.v2 = prim.v3 = 0x1d8;
        sxy = sy + sxy;
        prim.cy = prim.dy = sxy;
        __asm__ __volatile__("" : : "r"(sy));
        prim.r = prim.g = prim.b = *(u8 *)(param_1 + 0x24);
        prim.code = (&D_801814E4)[*(s32 *)(param_1 + 0x2c)];
        if (*(s16 *)(param_1 + 0x26) < 5) {
            prim.tag = 0;
        } else {
            prim.tag = 0x50000000;
        }
        uVar1 = *(u16 *)(param_1 + 0x30);
        iVar2 = 0;
        if (0 < *(s16 *)(param_1 + 0x28) + 1) {
            do {
                base = ((uVar1 + 1) & 0xf) << 3;
                prim.u0 = prim.u2 = base + 0x620;
                prim.u1 = prim.u3 = base + 0x628;
                func_80016ED4(&prim);
                uVar1 = (s32)(uVar1 << 0x10) >> 0x14;
                iVar2 = iVar2 + 1;
                __asm__ __volatile__("");
                xtmp = prim.ax;
                prim.cx = prim.ax = xtmp - 8;
                prim.bx = prim.dx = xtmp;
            } while ((s16)iVar2 < *(s16 *)(param_1 + 0x28) + 1);
        }
    }
}


DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016b3f4 (src/shared) */


DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016b428 (src/shared) */


DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016b448 (src/shared) */




void func_8016B4BC(void *a0) {

    extern void (*D_80181568[])(void);
    D_80181568[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);

void func_8016B4F8(int param_1)
{

    extern int D_801846B8;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801846B8);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}




// @class: schedule
// @stuck: none — MATCH

extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);


void func_8016B5C0(s32 param_1) {

    extern s16 D_8018155C[];
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018155C;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B6BC;

// @class: schedule
// @stuck: none — MATCH (94/94 ins, match_one relocation-masked)
//
// Exemplar of the 138-member h_seq family. The whole crack was ONE statement-order
// lever in the tail: the target's post-func_80015978 fix-up runs
//   v[2].x += off.x;  v[2].y += off.y;  v[0].c = 3;
// (the `c = 3` store LAST). Writing `c = 3` between the two v[2] RMWs — the order the
// Ghidra-C literally prints, and what every prior draft copied — costs 12 mismatches:
// gcc hoists the `li 3` into the load-delay window, which pushes v[2].x into $v1 and
// the off.x temp into $a0, and then the `addu $a0,$s1,$zero` arg copy can no longer be
// scheduled early enough to become the base register of the v[2]/v[0].c stores.
// With `c = 3` last, the arg copy births at the v[2].x/v[2].y boundary (idx 76) exactly
// as the target does, and the mixed $s1-load / $a0-store addressing falls out for free.
// (§67-adjacent: the copy PLACEMENT was the root cause — but here plain statement order
// reaches it, no `__asm__` launder and no register pin needed. Prior notes calling this a
// regalloc tie-break and pinning $a0 were chasing the consequence, not the cause.)
//
// Everything else follows the Ghidra-C: `Prim *p = &prim` (one alias only — a second
// pointer name splits the pseudo and breaks the $s1 base), the `q++` post-increment
// running pointer over the 8-byte table rows, and the ((param_4 << 16) >> 14) byte-offset
// index into D_80181544 (sll 16 / sra 14).


             /* 0x28 */


               /* the 8-byte D_80181544[] row */

extern void func_80013CFC(s32 a0, s32 a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8001739C(void *a0);

/* Def sig is deliberately (s32,s32,s32,s32) — byte-identical to the (int,unsigned,short,int)
 * spelling, and IDENTICAL to this TU's own caller decl `extern void func_8016B6BC(s32,s32,s32,s32);`
 * (ov_SC01_077_jr_8016AB6C.c), so there is no §73/§57 def-side self-decl conflict to reconcile. */
void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {

    extern int D_80181544;
    int iVar1;
    M8_8016B6BC *q;
    Prim_8016B6BC prim;
    Prim_8016B6BC *p = &prim;
    DVec_8016B6BC off;
    unsigned int v;
    unsigned int c;

    q = (M8_8016B6BC *)*(int *)((int)&D_80181544 + ((param_4 << 0x10) >> 0xe));
    p->color = 0x50000000;
    c = (unsigned int)param_2;
    v = 0x20;
    if (c < 0x20) {
        v = c;
    }
    if (*(int *)(param_1 + 0x2c) == 0) {
        c = c | (v << 0x10 | v << 8);
    } else {
        c = c << 8 | v << 0x10 | v;
    }
    p->combined = c;
    iVar1 = (int)(short)param_3;
    p->z1c = 0;
    p->z20 = 0;
    func_80013CFC(iVar1, (int)q++, &p->v[0]);
    func_80013CFC(iVar1, (int)q++, &p->v[1]);
    func_80013CFC(iVar1, (int)q, &p->v[2]);
    func_80015978(param_1 + 4, (s32 *)&off);
    p->v[0].x += off.x;
    p->v[0].y += off.y;
    p->v[1].x += off.x;
    p->v[1].y += off.y;
    p->v[2].x += off.x;
    p->v[2].y += off.y;
    p->v[0].c = 3;
    func_8001739C(p);
}




// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_801815A0[];
    extern unsigned short D_801815A8[];
    extern unsigned short D_801815B0[];
    extern unsigned char D_801846C0[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801846C0 + param_2 * 0x40);
    puVar3 = D_801815A0[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_801815A8[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_801815B0[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016b984 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B9F8;

// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801846B8;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801846B8, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


DEFINE_func_8016BA68()  /* dedup: shared engine-core @0x8016ba68 (src/shared) */


DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_801815B8[])(void);
    D_801815B8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80146C3C(u8*);

// @class: plumbing
// @stuck: none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_801847F4;
    extern u8 D_801847F5;
    extern u8 D_801847F6;
    extern M2C_UNK D_801847F8;
    extern u8 D_801847F9;
    extern u8 D_801847FA;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_801847F4) = 0x20;
        D_801847F5 = 0x20;
        D_801847F6 = 0;
        (*(u8 *)&D_801847F8) = 0xc0;
        D_801847F9 = 0xc0;
        D_801847FA = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016BCC0);

extern s32 func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801847F4;
    extern M2C_UNK D_801847F8;
    extern u8 D_801847F5;
    extern u8 D_801847F6;
    extern u8 D_801847F9;
    extern u8 D_801847FA;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801847F4);
    if (*p1 != 0) *p1 -= 4;
    if (D_801847F5 != 0) D_801847F5 -= 4;
    if (D_801847F6 != 0) D_801847F6 -= 4;
    p2 = &(*(u8 *)&D_801847F8);
    if (*p2 != 0) *p2 -= 4;
    if (D_801847F9 != 0) D_801847F9 -= 4;
    if (D_801847FA != 0) D_801847FA -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


extern void func_80146C3C(u8*);
extern s32 func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);


// @class: plumbing
// @stuck: none — MATCH

s32 func_8016BEA0(s32 param_1)
{

    extern M2C_UNK D_801847F4;
    extern M2C_UNK D_801847F8;
    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    ((void(*)())func_8016BF50)();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_801847F4), &(*(int *)&D_801847F8), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}


DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */



/* §71 sibling-first: this is the head of the already-matched func_8016C2C4
 * (src/ov_SC03_099/ov_SC03_099_jr_8016AB6C.c L2707) lifted into its own leaf. */

extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016BF50(s32 param)
{
    u16 buf[3];
    s32 arg;

    arg = *(s32 *)(param + 0x34);
    buf[0] = *(u16 *)(param + 0x12);
    buf[1] = *(u16 *)(param + 0x16);
    buf[2] = *(u16 *)(param + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, param + 4);
}




extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_80184780;
    func_8016BFD0(a0, a1, a2, a3, &D_80184780);
}


extern void func_800123F0(s32 a0, s32 a1);
extern void func_80013F3C(s32 a0);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_8012EFB8(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

// @class: struct
// @stuck: none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.




void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714();
    extern s32 D_801815C8;
    extern s32 D_801815D0;
    extern s32 D_801815D8;
    extern s32 D_801815E0;

    Mtx buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W *)((s32)a4 + 0x20) = *(W *)a1;
    *(W *)((s32)a4 + 0x24) = *(W *)a1;
    *(W *)((s32)a4 + 0x28) = *(W *)a2;
    *(W *)((s32)a4 + 0x2c) = *(W *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_801815C8, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_801815D0, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_801815D8, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_801815E0, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}




void func_8016C14C(void *a0) {

    extern void (*D_801815E8[])(void);
    D_801815E8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80149350(s32 arg0);

void func_8016C188(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register u8 *s0 __asm__("$16");
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(u8*);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_801847B4[];
    extern s16 D_801847FC;
    extern s16 D_801847FE;
    extern s16 D_80184800;
    extern s16 D_80184804;
    extern s16 D_80184806;
    extern s16 D_80184808;

    s1 = param;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_801847B4;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_801847FC;
        pBD4 = &D_80184804;
        *pBCC = 0x20;
        D_801847FE = 0x20;
        D_80184800 = 0;
        *pBD4 = 0xC0;
        D_80184806 = 0xC0;
        D_80184808 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016C2C4;

// @class: schedule
// @stuck: none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)

extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(u8*);


void func_8016C2C4(s32 param)
{

    extern u8 D_801847FC[];
    extern u8 D_80184804[];
    extern u8 D_801847B4[];
    register s32 s1 __asm__("$17");
    register s32 s0 __asm__("$16");
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_801847FC, D_80184804, D_801847B4);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


extern void func_80016714(void *a0, s32 a1);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_80048EAC(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void func_801465C0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {

    extern s32 D_8011D030;
    extern s32 VectorNormalSS(void *, void *);
    extern short func_8016CF04(s32, s32);
    extern u8 D_80184810[];
    extern u8 D_801848D0;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_80184810[1] = 0xff;
        D_80184810[2] = 0x10;
        D_80184810[0] = 0x10;
        D_80184810[6] = 0;
        D_80184810[5] = 0;
        D_80184810[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_80184810, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801848D0, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        ((void(*)(s32, void *))func_8001CD9C)(iVar5b, D_80184810);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = rand();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}


DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016c74c (src/shared) */


DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016c83c (src/shared) */



extern short func_8016CBC0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);


void func_8016C998(s32 param_1)
{

    extern s32 D_80126B9C;
    extern s16 D_80126CE0;
    u16 *psVar7;
    s32 r;
    short i;
    extern Slot_998 D_801848D0[];

    psVar7 = *(u16 **)(param_1 + 0x34);
    if (*psVar7 != 1) {
        *(s16 *)(param_1 + 2) = 6;
    }
    func_8016CBC0();
    if (*(s16 *)(param_1 + 0x28) != *(s16 *)(*(s32 *)(param_1 + 0x30) + 0x36)) {
        return;
    }
    if ((D_80126B9C & 0x20) == 0) {
        return;
    }
    if ((*(s32 *)(param_1 + 0x1c) == 0) ||
        (*(s16 *)(param_1 + 0x12) < D_80126CE0)) {
        *(s16 *)(param_1 + 0x12) = D_80126CE0;
        i = 0;
        do {
            if (D_801848D0[i].f0 == 0) {
                goto found;
            }
            i++;
        } while (i < 8);
    found:
        if (i >= 8) {
            return;
        }
        r = func_80146A6C(0x30, psVar7, 0, 0, 0, 0x8000, *(s32 *)(param_1 + 0x30));
        if (r == 0) {
            return;
        }
        D_801848D0[i].f0 = 1;
        *(Blk32_998 *)(r + 0x38) = *(Blk32_998 *)(param_1 + 0x38);
        *(s16 *)(r + 0x2a) = i;
        *(s16 *)(r + 6) = *(s16 *)(param_1 + 6);
        *(s16 *)(r + 0xa) = *(s16 *)(param_1 + 0xa);
        *(s16 *)(r + 0xe) = *(s16 *)(param_1 + 0xe);
        *(s32 *)(param_1 + 0x1c) = 0x10;
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}




void func_8016CB84(void *a0) {

    extern void (*D_801815F0[])(void);
    D_801815F0[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016CBC0;

extern s32 func_80017758(void *a0, void *a1);
short func_8016CBC0(void)
{

    extern Blk_8016CBC0 D_801848D0[];
  Poly_8016CBC0 p0;
  Poly_8016CBC0 p1;
  Mtx8_8016CBC0 mtx;
  Blk_8016CBC0 *blk;
  Rec_8016CBC0 *sub;
  Rec_8016CBC0 *pv;
  unsigned int uVar9;
  unsigned int w9;
  unsigned int uc;
  unsigned int a2;
  int col;
  int iVar3;
  int w3;
  unsigned int w3b;
  short count;
  short i;
register unsigned int zr __asm__("$0");
  mtx = (*(Mtx8_8016CBC0 *)&D_800AE620);
  count = 0;
  p1.tag = 0x50000000;
  p0.tag = 0x50000000;
  p1.col[3].b = 0;
  p1.col[3].g = 0;
  p1.col[3].r = 0;
  p1.col[1].b = 0;
  p1.col[1].g = 0;
  p1.col[1].r = 0;
  p0.col[2].b = 0;
  p0.col[2].g = 0;
  p0.col[2].r = 0;
  p0.col[0].b = 0;
  p0.col[0].g = 0;
  p0.col[0].r = 0;
  for (i = 0; i < 8; i++)
  {
    blk = &D_801848D0[i];
    if (blk->f0 != 0)
    {
      sub = blk->ent;
      uVar9 = blk->f1;
      iVar3 = blk->f2;
      col = blk->f3;
      count = count + 1;
      w3 = iVar3 - 1;
      iVar3 = w3 + zr;
      if (w3 != (-1))
      {
        do
        {
          pv = &sub[(short) uVar9];
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[0].x = a;
            b = pv->h[3];
            p1.v[1].x = b;
            p0.v[1].x = (p1.v[0].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[0].y = a;
            b = pv->h[4];
            uc = ((unsigned) (col & 0xFF)) >> 3;
            p1.v[1].y = b;
            p0.v[1].y = (p1.v[0].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[0].z = a;
            b = pv->h[5];
            p1.col[0].g = col;
            p0.col[1].g = col;
            p1.col[0].b = uc;
            p0.col[1].b = uc;
            p1.col[0].r = uc;
            p0.col[1].r = uc;
            p1.v[1].z = b;
            p0.v[1].z = (p1.v[0].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          if (((int) (w9 << 16)) < 0)
          {
            uVar9 = 0xF;
          }
          pv = &sub[(short) uVar9];
          col = col - 0xF;
          a2 = (unsigned) (col & 0xFF);
          a2 = a2 >> 3;
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[2].x = a;
            b = pv->h[3];
            p1.v[3].x = b;
            p0.v[3].x = (p1.v[2].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[2].y = a;
            b = pv->h[4];
            p1.v[3].y = b;
            p0.v[3].y = (p1.v[2].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[2].z = a;
            b = pv->h[5];
            p1.col[2].g = col;
            p0.col[3].g = col;
            p1.col[2].b = a2;
            p0.col[3].b = a2;
            p1.col[2].r = a2;
            p0.col[3].r = a2;
            p1.v[3].z = b;
            p0.v[3].z = (p1.v[2].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          func_80017758(&p0, &mtx);
          func_80017758(&p1, &mtx);
          uc = iVar3 - 1;
          w3b = uc;
          iVar3 = w3b + zr;
        }
        while (((short) w3b) != (-1));
      }
    }
  }

  return count;
}


extern void func_8016D5EC(s32 *a0);
extern void func_800D23D0(void *a0);


/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04 D_801848D0[];

    Blk_8016CF04 *p = &D_801848D0[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}




void func_8016D19C(void *a0) {

    extern void (*D_8018160C[])(void);
    D_8018160C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016D1D8);



void func_8016D428(void *a0) {

    extern void (*D_80181614[])(void);
    D_80181614[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


DEFINE_func_8016D5EC()  /* dedup: shared engine-core @0x8016d5ec (src/shared) */


DEFINE_func_8016D64C()  /* dedup: shared engine-core @0x8016d64c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016D688);

DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016d778 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016D848);

INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_8018167C[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_8018167C[*(unsigned short *)(param_1 + 2)](param_1);
}



// @class: plumbing
// @stuck: none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(u8*);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);


void func_8016DA7C(s32 param_1)
{

    extern u8 D_80181620;
    extern u8 D_8018162C;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_80181620, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_8018162C);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


DEFINE_func_8016DB34()  /* dedup: shared engine-core @0x8016db34 (src/shared) */


DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */


extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);
extern void func_80149374(s32 a0, s32 a1);
extern s32 func_801619D0(void *a0);


s32 func_8016DC20(s32 param_1) {

    extern s32  D_8011D030;
    extern s16  D_80184EF0;
    extern s16  D_80184EF4;
    extern s32  D_80181684;
    extern s32  D_80181690;
    u16 *p;
    short i;
    s32 obj;
    s32 r;
    s32 node;
    s32 e;
    Work8016 w;

    i = 0;
    p = (u16 *)&D_8011D030;
    obj = *(s32 *)(param_1 + 0x34);
    do {
        if ((p != (u16 *)param_1) && (*p == 0x34)) goto done;
        i = i + 1;
        p += 0x2c;
    } while (i < 0x1e);

    func_80149374(obj, param_1 + 4);
    r = func_801619D0((void *)obj);
    i = 0;
    if (r != 0) {
        p = (u16 *)&D_8011D030;
        do {
            if (*p == 0x11) goto ddb0;
            i = i + 1;
            p += 0x2c;
        } while (i < 0x1e);

        func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                      (s16)(*(u16 *)(param_1 + 0xA) - 8),
                      *(s16 *)(param_1 + 0xE), 0, 0);
        w.x = *(u16 *)(param_1 + 6);
        w.y = *(u16 *)(param_1 + 0xA);
        w.z = *(u16 *)(param_1 + 0xE);
        func_800D20C0(&w.x, &w.vx, 0);
        w.vy = 0;
        func_800D23D0(&w.vx);
        i = 0;
        do {
            e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                              *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE),
                              i, 0);
            if (e != 0) {
                *(s16 *)(e + 0x12) = w.vx;
                *(s16 *)(e + 0x16) = w.vy;
                *(s16 *)(e + 0x1A) = 0;
            }
            i = i + 2;
        } while (i < 3);
        goto done;
    }
ddb0:
    if (((D_80184EF0 != *(s16 *)(obj + 6)) || (D_80184EF4 != *(s16 *)(obj + 0xE)))
        && (node = func_800D21C4(param_1, &D_80181684, 0x18), node != 0)) {
        D_80184EF0 = *(u16 *)(obj + 6);
        D_80184EF4 = *(u16 *)(obj + 0xE);
        func_800D1FC8(param_1, 7);
        *(s32 *)(param_1 + 0x20) = node;
        *(u16 *)(node + 0x1A) = 0x3000;
        *(u16 *)(node + 0x18) = 0x3000;
        *(u8 *)(node + 0x26) = 0xFF;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x50000000;
        func_80128EA8(node, param_1 + 0x24, (s32)&D_80181690);
        ((s32 (*)(void *, void *))func_80128ED8)(node, param_1 + 0x24);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        return;
    }
done:
    ((void (*)(s32))func_80146C3C)(param_1);
}




void func_8016DEA4(void *a0) {

    extern void (*D_801816B0[])(void);
    D_801816B0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_8016DEE0(s32 a0) {
    if (((s32 (*)(void *, void *))func_80128ED8)((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}




void func_8016DF20(void *a0) {

    extern void (*D_801816B8[])(void);
    D_801816B8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);
extern void func_80146C3C(u8*);




void func_8016DF5C(s32 param_1)
{

    extern s32 D_8011D030;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_8016E3CC(s32);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_80184EF8;
    extern u8 D_80184EF9;
    extern u8 D_80184EFA;
    extern u8 D_80184EFC;
    extern u8 D_80184EFD;
    extern u8 D_80184EFE;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        register s32 iNew __asm__("$17");
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_80184EF8;
        D_80184EFA = 0xc0;
        *(u8 *)base = 0xc0;
        D_80184EF9 = 0;
        D_80184EFE = 0;
        D_80184EFD = 0;
        D_80184EFC = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        ((void (*)(void *))func_8016E3CC)(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}


DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


DEFINE_func_8016E2E8()  /* dedup: shared engine-core @0x8016e2e8 (src/shared) */


DEFINE_func_8016E358()  /* dedup: shared engine-core @0x8016e358 (src/shared) */


DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_8018170C[])(void);
    D_8018170C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016E5F4()  /* dedup: shared engine-core @0x8016e5f4 (src/shared) */


DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


extern s32 func_80017DC4(void *a0, void *a1);


// @class: regalloc-order
// @stuck: none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

                 /* 0x08 */
     /* 0x20 */




void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(s32, s32, void*);
    extern void func_80016ED4(void *a0);
    extern SVECTOR D_801816CC[4];
    extern s32 D_801816EC;
    extern s32 D_801816F4;
    extern s32 D_801816FC;
    extern s32 D_80181704;

    Prim_8016E7C8_8016E7C8 prim;
    MATRIX_c2 m;
    SVECTOR tmp;
    register Prim_8016E7C8_8016E7C8 *pp __asm__("$18");   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    ((void (*)(void *, void *, void *))RotTransSV)(&D_801816CC[0], pp, &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_801816CC[1], &prim.v[1], &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_801816CC[2], &prim.v[2], &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_801816CC[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_801816EC;
    prim.f1 = D_801816F4;
    prim.f2 = D_801816FC;
    prim.f3 = D_80181704;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}


DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */



// @class: struct
// @stuck: none — MATCH (36/36 ins, match_one relocation-masked)



typedef void (*Handler)(struct Entry *);


s32 func_8016E95C() {

    extern s32 D_80115218;
    extern Handler D_8018174C[];

    struct Entry *p;
    for (p = ((struct Entry *)&D_80115218); p < &((struct Entry *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_8018174C[p->f1](p);
        }
    }
}



/* @class: regalloc (non-coalescing delay-slot copy) + sched (load-temp hoist)
 * @stuck: none — MATCH (53/53 ins, match_one AND rtu_match in the real TU).
 *
 * Two levers, both from the cookbook:
 *
 * 1. §52a "non-coalescing delay-slot copy" + §17 zero-reg-copy (the load-bearing one).
 *    The target holds `p[0]-1` in TWO callee-saved regs: $s0 (the array index, later
 *    destroyed in place by `sll $s0,$s0,1`) and $s4 (the value stored to p[3]), created
 *    by `addu $s4,$s0,$zero` sitting in the DELAY SLOT of `jal func_800D2CA8`. A plain
 *    C `c = i;` is destroyed by cse.c canon_reg head-promotion (measured: 50 ins, -3),
 *    and every #APP-asm spelling of the copy is INELIGIBLE for a delay slot (measured:
 *    51 ins, -2 — tried `__asm__("":"=r"(c):"0"(i))`, a real-opcode
 *    `__asm__("addu %0,%1,$0")`, and the §52b RC-7 post-copy second-set barrier
 *    `c=i; __asm__("":"=r"(c):"0"(c))`; all three collapse or lose the slot).
 *    Only the `$0`-add — `register u32 zr __asm__("$0"); c = i + zr;` — emits a bare
 *    `addu` with no asm insn, so reorg can sink it into the call's delay slot.
 *    NOTE for ×138 propagation: this is a ZERO-REGISTER pin, not an allocation pin —
 *    it constrains no real value. family_sweep's §42e "skip pinned exemplar" guard is
 *    documented over-conservative (§86; the SIGABRT was our own extract_unit macro-drop,
 *    fixed in Phase 27), so this exemplar should still sweep.
 *
 * 2. Free-floating load temp for a scheduler hoist (§52a-adjacent, idiom 7).
 *    With the p+6 store written as one statement the sched2 list scheduler hoists
 *    `lbu $v0,1($a0)` ahead of `sb $s4,3($a0)` and sinks the D_80181738 lui/addu/lhu
 *    chain (8 mismatched, same 53-ins multiset). Splitting the load into its own
 *    statement `h = D_80181738[i];` placed BEFORE `p[2] = 0` (exactly what the Ghidra
 *    seed showed) puts the lhu chain right after `sh $v0,4($a0)` → 0.
 *
 * Data typing: D_8018171C is a WORD array (`sll $v0,$s0,2`; its element is dereferenced
 * as a buffer by func_80024054) => u8 *[]. D_80181734 is byte-indexed (`lbu`, no shift)
 * => u8[]. D_80181738 is halfword-indexed (`sll $s0,$s0,1` + `lhu`) => u16[].
 * `*(s16 *)(p + 4) = -0xD7` emits `addiu $v0,$zero,-0xD7`; 0xFF29 as a u16 would not.
 */


extern s32 func_800D2CA8(s32 a0, s32 a1);
extern void func_800D2D10(s32 a0, s32 a1, void *a2, s32 a3);
extern s32 func_80024054(u8*, u8*);
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016E9EC(u8 *p)
{

    extern u8 *D_8018171C[];
    extern u8 D_80181734[];
    extern u16 D_80181738[];
    register u32 zr __asm__("$0");
    int i;
    int c;
    u8 *buf;
    u8 off;
    u16 h;
    s32 r;

    i = p[0] - 1;
    off = D_80181734[i];
    buf = D_8018171C[i];
    c = i + zr;
    r = func_800D2CA8(p[3], 0x1C);
    func_800D2D10(r, 1, buf + off, 0);
    ((s32 (*)(void *, void *))func_80024054)(buf, p + 8);
    p[3] = c;
    *(s16 *)(p + 4) = -0xD7;
    h = D_80181738[i];
    p[2] = 0;
    *(u16 *)(p + 6) = h;
    p[1] = p[1] + 1;
    ((void (*)(u8 *, s32))func_8016EC0C)(p, 0x80);
}




// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_80181740[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_80181740[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EB3C;

// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {

    extern u8 D_80181730[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_80181730[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_80181740[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_80181740[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_80181740[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EC0C;

extern void func_80017B98(void *a0);

void func_8016EC0C(s32 a0, s32 a1)
{

    extern u8 D_8018172C[];
    /* §100 draft-LOCAL type: a file-scope typedef is an EXEMPLAR-ONLY bank — extract_unit/
       remap_hseq carry only the BODY, so every sibling fails `T8016EC0C undeclared`
       (measured on ov_SC01_000). Block scope travels with the body; byte-neutral. */
 /* 0x1C */
    T8016EC0C s;
    u16 *p;
    s32 x;
    s32 y;
    s32 v;

    s.r = s.g = s.b = a1;
    s.u18 = D_8018172C[*(u8 *)(a0 + 3)];
    s.u0C = 0x640;
    s.u0E = 0x1C8;
    s.u14 = 0;
    s.u08 = 0x28;
    s.u0A = 8;
    x = *(u16 *)(a0 + 4);
    s.x = x + 0x10;
    y = *(u16 *)(a0 + 6);
    s.u04 = 0x10;
    s.y = y;
    func_80017B98(&s);
    s.u08 = 8;
    y += 0xA;
    p = (u16 *)(a0 + 8);
    while (*p != 0xFFFF) {
        v = *p;
        switch (v) {
        case 0x1850:
        case 0x1858:
            s.x = x + 4;
            s.y = y - 7;
            break;
        case 0x3872:
            x += 2;
            p++;
            continue;
        default:
            s.x = x;
            s.y = y;
            x += 8;
            break;
        }
        s.u0C = *(u8 *)p + 0x500;
        s.u0E = (*p >> 8) + 0x100;
        p++;
        func_80017B98(&s);
    }
}


extern void func_80146C3C(u8*);
void func_8016ED6C(void) {
    ((void (*)(void))func_80146C3C)();
}


DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


DEFINE_func_8016EFC8()  /* dedup: shared engine-core @0x8016efc8 (src/shared) */


DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8016F0AC);


/* RECONCILE NOTE (uc3) — the body is byte-unchanged from uc2; only the declaration
 * environment moved.  The gate error was
 *     jr_8016AB6C.c:4183 conflicting types for func_8016F0E4 || :4089 previous declaration
 * :4089 was THIS definition; :4183 is the `extern void func_8016F0E4(void);` carried inside
 * DEFINE_func_8016F4C4() (src/shared/engine_core.h:22579), which the host TU instantiates at
 * ov_SC01_077_jr_8016AB6C.c:4136 — i.e. AFTER the definition, so it is a hard error, not the
 * mere warning produced by the earlier block-scope decl in func_8016F0AC (TU:4047).
 * Byte-true signature is `void (u8 *)`; the fleet canon is `void (void)` — a PARAM/ARITY
 * disagreement on func_8016F0E4 ITSELF.
 *
 * ESCAPE TAKEN: §37/§124 ASM-LABEL ALIAS (escape 2, T0 draft-only, zero tracked-file edits).
 * The C identifier is aF8016F0E4 so this TU declares func_8016F0E4 exactly once (the macro's
 * own `extern void`), while the emitted SYMBOL is func_8016F0E4.  Both existing callers already
 * launder through a cast or take no args, so neither is perturbed:
 *   - func_8016F0AC (TU:4047-4049) casts:  ((void (*)(void *))func_8016F0E4)(&D_80126B58);
 *   - DEFINE_func_8016F4C4 calls func_8016F0E4() with 0 args against its own (void) prototype.
 * cc1-proven: preprocess+compile of the real TU with this body spliced in is free of any
 * func_8016F0E4 diagnostic (the pre-existing unrelated warnings in the TU are unchanged).
 *
 * This SUPERSEDES uc2's //@EDIT de-macroize plan (§65b) and its T2 engine_core.h alternative
 * (§75c) — neither is needed; nothing outside this unit changes, so the bank travels to the
 * 137 siblings as a plain unit (carry the alias DECLARATION line with it — §124 trap 2).
 */

extern void func_8017196C(s32 *a0, s8 a1);   /* == DEFINE_func_8017196C's own signature */
extern void func_80147060(u8 *a0);
extern void func_801511A8(u8 *a0);
extern void func_80148634(void *a0);

// @class: plumbing
// @stuck: none — MATCH (26 ins).
//   Levers: (1) §42b read-global &-cast — the TU declares D_80078EB4 as s16 but the target
//   loads it with `lhu`; the bare `D_80078EB4 != 0` gives `lh` (probed: closeness 1, WIDTH
//   lh!=lhu), so read it as *(u16 *)&D_80078EB4.  (2) both 0x1F8/0x1FC stores are s32 `sw`,
//   emitted before the first jal (the 0x1FC one lands in the delay slot by sched2 — free).
//   (3) the param needs no laundering: it is copied to $s0 at entry and the first call's
//   `move $a0,$s0` is deleted because $a0 already holds it — plain `u8 *p` reproduces this.
//   (4) §37/§124 asm-label alias — see the RECONCILE NOTE above; codegen-neutral (symbol only).

void aF8016F0E4(u8 *p) __asm__("func_8016F0E4");

void aF8016F0E4(u8 *p) {

    extern s16 D_80078EB4;                       /* fleet-canonical spelling; see the &-cast below */
    extern u8 D_800B9A17;
    *(s32 *)(p + 0x1F8) = 0;
    *(s32 *)(p + 0x1FC) = 0;
    func_8017196C((s32 *)p, 0);
    func_80147060(p);
    func_801511A8(p);
    if (*(u16 *)&D_80078EB4 != 0) {
        D_800B9A17 = 1;
    }
    func_80148634(p);
}


DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016F1C4;

// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_8018175C;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018175C;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016f250 (src/shared) */


DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016f264 (src/shared) */


DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016f288 (src/shared) */


DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016f2a8 (src/shared) */


DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016f2c8 (src/shared) */


DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016f2ec (src/shared) */


DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016f30c (src/shared) */


DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016f330 (src/shared) */


DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016f350 (src/shared) */


DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016f374 (src/shared) */


DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016f388 (src/shared) */


DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016f398 (src/shared) */


DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016f410 (src/shared) */


DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016f44c (src/shared) */


DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016f470 (src/shared) */


DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016f494 (src/shared) */


DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016f4c4 (src/shared) */


void func_8016F4F4(void) {
}

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016f4fc (src/shared) */


DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016f540 (src/shared) */


DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016f578 (src/shared) */


DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016f5b0 (src/shared) */


DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016f5e0 (src/shared) */


DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016f610 (src/shared) */


DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016f648 (src/shared) */


DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016f680 (src/shared) */


DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016f6b0 (src/shared) */




void func_8016F6E0(void *a0) {

    extern void (*D_801817D4[])(void);
    D_801817D4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_801817DC[])(void);
    D_801817DC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_801817E4[])(void);
    D_801817E4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_801817EC[])(void);
    D_801817EC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_801817F4[])(void);
    D_801817F4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_801817FC[])(void);
    D_801817FC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_80181808[])(void);
    D_80181808[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_80181814[])(void);
    D_80181814[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_80181820[])(void);
    D_80181820[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_80181830[])(void);
    D_80181830[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_80181840[])(void);
    D_80181840[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_80181848[])(void);
    D_80181848[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_80181850[])(void);
    D_80181850[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_80181858[])(void);
    D_80181858[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_80181860[])(void);
    D_80181860[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_80181868[])(void);
    D_80181868[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_80181870[])(void);
    D_80181870[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_80181878[])(void);
    D_80181878[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_80181880[])(void);
    D_80181880[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_80181888[])(void);
    D_80181888[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_80181890[])(void);
    D_80181890[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */



extern void func_801484B0(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_8014C168(s32*, s32);
extern void func_80171928(void *a0);

void func_801708B0(void* a0)
{

    extern void *D_8011F738;
    u16 sp10[4];
    u16 sp18[4];
    short *r;
    func_801484B0((s32)&sp10, (s32)&sp18);
    ((void (*)(s32, void *, void *))func_80149350)((s32)a0, &sp10, &sp10);
    r = (short *)((s32 (*)(s32, s32))func_8014C168)((s32)a0, (*(s32 *)&D_8011F738));
    r[3] = sp10[0];
    r[5] = sp10[1];
    r[7] = sp10[2];
    func_80171928((void *)a0);
}


DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_80181898[])(void);
    D_80181898[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_801818A0[])(void);
    D_801818A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_801818A8[])(void);
    D_801818A8[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */



extern void func_801718AC(void *a0);

void func_80170CF0(void* a0)
{

    extern void *D_8011F738;
    extern s32 D_8011F73C;
    extern s32 D_8011F740;
    s32 v1;
    void *p;
    ((void (*)(s32))D_8011F738)(a0);
    v1 = *(u8 *)(a0 + 0x217);
    if (v1 == 1) {
        goto case_1;
    }
    if (v1 <= 1) {
        goto done;
    }
    if (v1 == 2) {
        goto case_2;
    }
    goto done;
case_1:
    p = (*(void * *)&D_8011F73C);
    goto call;
case_2:
    p = (*(void * *)&D_8011F740);
call:
    func_801718AC(p);
done:
    ;
}




void func_80170D68(void *a0) {

    extern void (*D_801818B0[])(void);
    D_801818B0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_801818B8[])(void);
    D_801818B8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_801818C0[])(void);
    D_801818C0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_801818C8[])(void);
    D_801818C8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_801818D0[])(void);
    D_801818D0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_801818D8[])(void);
    D_801818D8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_801818E0[])(void);
    D_801818E0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_801818E8[])(void);
    D_801818E8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017129C()  /* dedup: shared engine-core @0x8017129c (src/shared) */


DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_801818F0[])(void);
    D_801818F0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


DEFINE_func_801718AC()  /* dedup: shared engine-core @0x801718ac (src/shared) */


DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */


DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */


DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196c (src/shared) */


DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197c (src/shared) */


DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */


DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719a4 (src/shared) */


DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171a04 (src/shared) */


DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171a10 (src/shared) */


DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171a1c (src/shared) */


DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171a34 (src/shared) */


DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171a44 (src/shared) */


DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171a58 (src/shared) */


DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171a6c (src/shared) */


DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171a80 (src/shared) */


DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171a88 (src/shared) */


DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171ab0 (src/shared) */


DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171b10 (src/shared) */


DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171b44 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171c64 (src/shared) */


DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171cc4 (src/shared) */


DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171d1c (src/shared) */


DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171d78 (src/shared) */


DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171e08 (src/shared) */


DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171ec8 (src/shared) */


DEFINE_func_80171FFC()  /* dedup: shared engine-core @0x80171ffc (src/shared) */


DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209c (src/shared) */


DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */


DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722cc (src/shared) */


DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */


DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */


DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */


DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723c4 (src/shared) */


DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */


DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248c (src/shared) */


DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724ec (src/shared) */


DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250c (src/shared) */


DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */


DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */


DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */


DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725a4 (src/shared) */


DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725b8 (src/shared) */


DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725cc (src/shared) */


DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725e0 (src/shared) */


DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725f4 (src/shared) */


DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */


DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261c (src/shared) */


DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */


DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */


DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */


DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */


DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */


DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267c (src/shared) */


DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */


DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */


DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726a0 (src/shared) */


DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726ac (src/shared) */


DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726b8 (src/shared) */


DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726c4 (src/shared) */


DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726d0 (src/shared) */


DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */


DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */


DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */


DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801727D0);

DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801728E4);

DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801729F0);

DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80172B44);

DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

extern void func_80174684(void *);
extern void func_80172CA0(void*);
void func_80172C50(void *a0) {

    extern s16 D_80126B30;
    *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0;
    func_80174684((void *)func_80172CA0);
}




void func_80172CA0(void *a0) {

    extern void (*D_80181934[])(void);
    D_80181934[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80172DAC);

DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172de8 (src/shared) */


DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172e20 (src/shared) */


void func_80172E8C(void) {
}

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172e94 (src/shared) */


DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ed4 (src/shared) */


DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172efc (src/shared) */


DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172f24 (src/shared) */


DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172f4c (src/shared) */


DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172f9c (src/shared) */


DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172fec (src/shared) */


DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80173078);

DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8017319C);

DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_801818F8;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_801818F8);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}


void func_80173294(void) {
}

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329c (src/shared) */


DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732c4 (src/shared) */


DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732f4 (src/shared) */


DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331c (src/shared) */


DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334c (src/shared) */


DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */


DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733a4 (src/shared) */


DEFINE_func_801733CC()  /* dedup: shared engine-core @0x801733cc (src/shared) */



extern void func_801734BC(s32 a0, s32 a1);

void func_801733FC(s32 a0, s32 a1) {

    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3E;
    extern s16 D_80126B40;
    func_801734BC(a0, a1);
    D_80126B38 = *(struct S80126B38 *)a1;
    D_80126B3E = 1;
    D_80126B40 = 1;
}


DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_80181964[])(void);
    D_80181964[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801736FC);

DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801737E8);

DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8017390C);

DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */



extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern void func_80173B4C(void*);

void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5)
{

    extern s32 D_80126B58;
    extern s32 D_80127508;
    extern s16 D_80126B30;
    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3A;
    extern s16 D_80126B3C;
    extern s16 D_8011F9C8;
    extern s16 D_80126938;
    extern s32 D_8012750C;
    s32 *s1 = &D_80126B58;
    s32 v0;

    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }

    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}




void func_80173B4C(void *a0) {

    extern void (*D_801819A0[])(void);
    D_801819A0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173b88 (src/shared) */


DEFINE_func_80173BC0()  /* dedup: shared engine-core @0x80173bc0 (src/shared) */


DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173c64 (src/shared) */


DEFINE_func_80173CB4()  /* dedup: shared engine-core @0x80173cb4 (src/shared) */


DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173e1c (src/shared) */


DEFINE_func_80173EF8()  /* dedup: shared engine-core @0x80173ef8 (src/shared) */


DEFINE_func_80174158()  /* dedup: shared engine-core @0x80174158 (src/shared) */


DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */


DEFINE_func_801741A8()  /* dedup: shared engine-core @0x801741a8 (src/shared) */


DEFINE_func_801741EC()  /* dedup: shared engine-core @0x801741ec (src/shared) */


void func_80174274(void) {
}

DEFINE_func_8017427C()  /* dedup: shared engine-core @0x8017427c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801742A4);

DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80174384);

DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80174474);

DEFINE_func_801744B0()  /* dedup: shared engine-core @0x801744b0 (src/shared) */


DEFINE_func_801744E0()  /* dedup: shared engine-core @0x801744e0 (src/shared) */


void func_80174524(void) {
}

DEFINE_func_8017452C()  /* dedup: shared engine-core @0x8017452c (src/shared) */


DEFINE_func_80174554()  /* dedup: shared engine-core @0x80174554 (src/shared) */


DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */


DEFINE_func_801745AC()  /* dedup: shared engine-core @0x801745ac (src/shared) */


DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745dc (src/shared) */


DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */


DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */


DEFINE_func_80174650()  /* dedup: shared engine-core @0x80174650 (src/shared) */


DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */


DEFINE_func_80174684()  /* dedup: shared engine-core @0x80174684 (src/shared) */


DEFINE_func_801746A4()  /* dedup: shared engine-core @0x801746a4 (src/shared) */


DEFINE_func_801746DC()  /* dedup: shared engine-core @0x801746dc (src/shared) */


DEFINE_func_80174714()  /* dedup: shared engine-core @0x80174714 (src/shared) */


DEFINE_func_80174754()  /* dedup: shared engine-core @0x80174754 (src/shared) */


DEFINE_func_80174764()  /* dedup: shared engine-core @0x80174764 (src/shared) */


DEFINE_func_80174774()  /* dedup: shared engine-core @0x80174774 (src/shared) */


DEFINE_func_80174784()  /* dedup: shared engine-core @0x80174784 (src/shared) */


DEFINE_func_801747AC()  /* dedup: shared engine-core @0x801747ac (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_801747CC);

DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80174888);

DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_8017496C);

DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (105 ins). Keys: (1) single-buffer struct for the func_80049CAC/func_8012F14C
//   out-params (local_2c..local_14 are fields of ONE stack buffer, not separate scalars — else gcc
//   DCEs the unread ones + overlaps the buffer -> wrong 0x40 frame); (2) $s2/$s1 pins for iVar5/iVar4
//   (call-crossing saved regs); (3) load D_80126B66 as RAW u16 (lhu) with (s16) sext at each USE —
//   this defeats gcc's lhu+sext->lh combine fold so the target's lhu+sll+sra reappears; (4) inline
//   `iVar5 = (s16)D_80126B5E` into the f48 expression so the f28 operand load schedules first.


extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32, s32, s32);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);


s32 func_801749C8(s32 param_1)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    Buf_c1 buf;
    register s32 iVar5 __asm__("$18");
    register u32 iVar4 __asm__("$17");

    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    iVar4 = (u16)D_80126B66;
    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + (iVar5 = (s16)D_80126B5E);
    *(s32 *)(param_1 + 0x4c) = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    func_80049CAC(param_1 + 0x18, (s32)&buf);

    buf.f14 = *(s16 *)(param_1 + 0x28) + iVar5;
    buf.f18 = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    buf.f1c = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    buf.f20 = 0;
    buf.f22 = 0;
    buf.f24 = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&buf, (s32)&buf.f20, (s32)&buf.f28);

    *(s32 *)(param_1 + 0x3c) = buf.f28;
    *(s32 *)(param_1 + 0x40) = buf.f2a;
    *(s32 *)(param_1 + 0x44) = buf.f2c;
}


DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_801819F8[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_801819F8[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_801819F8[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


DEFINE_func_80174CB0()  /* dedup: shared engine-core @0x80174cb0 (src/shared) */


DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */


INCLUDE_ASM("asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_8015A3C8", func_80174F28);

DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_80181A08[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_80181A08[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}


DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751d8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{

    extern u8 D_80078EC0;
    extern void (*D_80181A10[])(s32);
    s32 i = D_80078EC0 - 1;

    D_80181A10[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_80181A28[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_80181A28 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


DEFINE_func_80175308()  /* dedup: shared engine-core @0x80175308 (src/shared) */


DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (37 ins, relocation-masked proxy)



extern s32 func_80029504(void);

void func_801754A8(void) {

    extern u8 D_8011F7A8;
    extern unsigned char D_800B9A13;
    extern s32 D_80126B9C;
    extern DispatchFn D_80181B6C[];
    u8 *p = &D_8011F7A8;
    s32 r = func_80029504();
    s32 flag = 0;

    if (((D_800B9A13 == 0) && ((D_80126B9C & 0x80) == 0)) ||
        (0x4AF < (u32)(r - 10))) {
        flag = 1;
    }
    p[9] = flag;
    D_80181B6C[p[0]]((void *)p);
}



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {

    extern void (*D_80181B78[])();
    D_80181B78[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */


DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */


DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(s32 *param) {

    extern void (*D_80181B84[])();
    D_80181B84[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


extern s32 func_801758FC(void);

/* func_80175820 — twin of the byte-matched func_801759D8 / func_801758FC in this same TU
 * (ov_SC01_077_jr_801734BC).  Same three-part body, different slot:
 *   part 1 tag word = ptr[2]        (0x8 vs 0x4 / 0xC)
 *   part 2 head ptr = D_8011F7A8+0x18 (== D_8011F7C0)
 *   part 3 tail ptr = D_8011F7A8+0x20 (== D_8011F7C8)
 * The two __asm__ memory fences are what keep the three parts from CSE-ing their
 * base addresses together (parts 1/2 stay absolute lui/%lo + idx*4; part 3 keeps the
 * shared `la $v1,D_8011F7A8` + 0x18/0x20 displacements).
 */

   /* size 0x14 */
    /* size 0x0C */

s32 func_80175820(void)
{
    extern s16 D_800B9A02;
    extern S_AE7BC_80175820 D_800AE7BC[];
    extern S_AF634_80175820 D_800AF634[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;

    q = (u16 *)&(*(u16 *)&D_800B9A02);

    ptr = D_800AE7BC[*q].f0;
    old = ptr[2];
    ptr[2] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x20) & 0xffffff);
    __asm__("" ::: "memory");

    p2 = *(u32 **)(p + *q * 4 + 0x18);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    __asm__("" ::: "memory");

    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x18) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x20) - t) >> 2);
    }
}


DEFINE_func_801758FC()  /* dedup: shared engine-core @0x801758fc (src/shared) */





   /* size 0x14 */
    /* size 0x0C */

s32 func_801759D8(void)
{

    extern u8 D_8011F7B1;
    extern s16 D_800B9A02;
    extern S_AE7BC_801759D8 D_800AE7BC[];
    extern S_AF634_801759D8 D_800AF634[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;

    if (D_8011F7B1 != 0) {
        return;
    }

    q = (u16 *)&(*(u16 *)&D_800B9A02);

    ptr = D_800AE7BC[*q].f0;
    old = ptr[1];
    ptr[1] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x40) & 0xffffff);
    __asm__("" ::: "memory");

    p2 = *(u32 **)(p + *q * 4 + 0x38);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    __asm__("" ::: "memory");

    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x38) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x40) - t) >> 2);
    }
}



void func_80175AB8(param_1)
    s16 param_1;
{
   /* size 0x0C */
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];

    extern u8  D_8011F7F0;
    extern u16 D_8011F7B4;
    extern u16 D_8011F7B6;
    extern s16 D_8011F7BC;
    extern s16 D_8011F7BE;
    extern s32 D_8011F804;
    extern u16 D_8011F80A;
    extern u16 D_8011F824;
    extern u8  D_8011F832;
    extern u8  D_8011F83A;
    extern u8 *D_80181AA0[];

    extern u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_);
    extern u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_);
    extern u32  func_801783D0(s32 a0, s32 a1);
    extern u32 *func_80177EA4(u32 *param_1, s32 param_2, u32 param_3, s32 param_4);
    extern u32 *func_80177B5C();
    extern void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_);
    extern u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
    extern s32 func_80024054(u8*, u8*);
    extern s32  func_8005A600(s32, s32, s32, s32, s32);

    u8 local[24];
    u8 *base;
    u8 *arr;
    u32 *slot;
    u32 *p;
    register u32 *a0v __asm__("$4");
    u32 uv;
    s32 k;
    s16 q;
    s32 r1;
    s32 a2v;
    register s32 sum __asm__("$5");
    s32 r2;
    s32 idx;
    s16 sv;

    p = (u32 *)(D_800AF638[param_1].g0 + D_800AF634[param_1].g0 * 4);
    __asm__("" : "=r"(base) : "0"(&D_8011F7F0));               /* L1 */
    arr = base - 0x48;
    slot = (u32 *)(param_1 * 4 + (s32)arr);
    *(volatile u32 *)&slot[6] = (u32)p;                        /* L2 */
    p = func_80176D94(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51));
    p = func_801770E0(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    p = func_80177EA4(p, func_801783D0(D_8011F804, 0),
                      (s16)((*(u16 *)&D_8011F7BC) + 0x39), (s16)((*(u16 *)&D_8011F7BE) + 0x51));
    uv = D_8011F824;
    k = 0x3E7;
    if (uv < 1000) {
        k = uv;
    }
    sv = (s16)func_801783D0(k, 4);
    p = func_80177B5C(p, sv, D_8011F832,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x65));
    q = (s16)D_8011F80A / 15;
    a2v = (q & 3) * 15;
    r1 = func_801783D0((s32)(q << 16) >> 18, 8);
    r2 = func_801783D0(a2v, 0);
    a0v = p;                                                   /* L4 */
    sum = r1 + r2;                                             /* L3 */
    p = ((u32 * (*)(u32 *, s32, s32, s32))func_80177940)(
            a0v, (s16)sum,
            (s16)(*(u16 *)(base - 0x34) + 0x76),
            (s16)(*(u16 *)(base - 0x32) + 0x65));
    idx = D_8011F83A & 0x7F;
    D_8011F83A = idx;
    __asm__ __volatile__("" ::: "memory");
    ((void (*)(s32, u8 *))func_80024054)(((s32 *)D_80181AA0)[idx], local);
    p = func_80178298(p, local,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x5B));
    func_8005A600((s32)p, 0, 0, 0x15, 0);
    *p = (((u32)p - 0x14) & 0xFFFFFF) | 0x2000000;
    slot[8] = (u32)p;
    p += 5;
    D_800AF634[param_1].g0 += ((s32)p - (s32)slot[6]) >> 2;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80175DA8;

   /* size 0x0C */
extern u32 *func_8017742C(u32 *a0, s32 a1, s32 a2);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800183E0(s32 a0);

  /* 0x14 */

void func_80175DA8(param_1)
    u16 param_1;
{

    extern u8  D_8011F7F0;
    extern u8  D_800B9A13;
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];
    extern u16 D_80181A40[];
    extern u16 D_80181A90[];
    extern u16 D_80181A9C;
    extern u8  D_80181B1C[];
    extern u8  D_80181B30[];
    extern s32 D_80181B48[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;

    u8 *base = &D_8011F7F0;
    u8 *s = base - 0x48;
    u16 *src = D_80181A40;
    Sp_80175DA8 *p;
    s16 i;
    s32 arg;
    s32 t;
    s32 fl;
    u16 v;

    p = (Sp_80175DA8 *)(D_800AF638[(s16)param_1].g0 + D_800AF634[(s16)param_1].g0 * 4);
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28) = p;
    i = 0;
    do {
        p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x4000000;
        p->code = *(u32 *)src;
        src += 2;
        if (i < 2) {
            p->x = *src++ + *(u16 *)(s + 0xC);
            p->y = *src++ + *(u16 *)(s + 0xE);
        } else if (i == 2) {
            p->x = *src++ + *(u16 *)(s + 0x10);
            p->y = *src++ + *(u16 *)(s + 0x12);
        } else {
            p->x = *src++ + *(u16 *)(s + 0x14);
            p->y = *src++ + *(u16 *)(s + 0x16);
        }
        p->uv = *(u32 *)src;
        src += 2;
        p->wh = *(u32 *)src;
        src += 2;
        p++;
        i++;
    } while (i < 5);

    *(u8 *)(s + 7) = D_800B9A13;
    p = (Sp_80175DA8 *)func_8017742C((u32 *)p,
                                     (s16)(*(u16 *)(s + 0x10) - 0x98),
                                     (s16)(*(u16 *)(s + 0x12) + 9));
    func_8005A600((s32)p, 0, 0, 0x16, 0);
    p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x2000000;
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x30) = p;
    p++;
    {
        s32 acc = D_800AF634[(s16)param_1].g0;
        D_800AF634[(s16)param_1].g0 =
            acc + (((s32)p - *(s32 *)(s + (s16)param_1 * 4 + 0x28)) >> 2);
    }

    p = *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28);
    if (base[0x48] != 0) {
        *((u8 *)p + 0xD) = 0;
    } else {
        *((u8 *)p + 0xD) = 0xA0;
    }

    {
        u8 *q1 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        *(u16 *)(q1 + 0x22) = 0x6CD6;
        if (base[0x48] & 0x80) {
            *(u16 *)(q1 + 0x20) = D_80181A9C;
            arg = (s32)&D_800D45D4;
        } else {
            u16 *tt = D_80181A90;
            s32 k = base[0x48];
            if (k != 0) {
                k--;
                tt += k;
            }
            *(u16 *)(q1 + 0x20) = *tt;
            arg = D_80181B48[base[0x48]];
        }
    }
    func_800183E0(arg);

    {
        u8 *q2 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        t = (s32)(*(u16 *)(base + 0x2E) << 16);
        if (t != 0) {
            q2[0x49] = D_80181B30[t >> 20];
        } else {
            q2[0x49] = 0xA0;
        }
    }

    {
        u8 *q3 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        v = *(u16 *)(base + 0x40);
        if (v < 100) {
            q3[0x5D] = D_80181B1C[v / 5];
        } else {
            q3[0x5D] = 0;
        }
    }

    fl = *(s16 *)(base + 0x1E) & 0x8000;
    /* §5a zero-byte sched fence: without it sched1 hoists the `la D_800D43D4`
       into the lh's load-delay slot, dropping the target's nop (-1 ins). */
    __asm__("");
    arg = (s32)&D_800D43D4;
    if (fl != 0) {
        arg = (s32)&D_800D4414;
    }
    func_800183E0(arg);
}


DEFINE_func_80176144()  /* dedup: shared engine-core @0x80176144 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176218;


// @class: regalloc-order
// @stuck: none — MATCH (327/327 ins, match_one MATCH; symcheck SYMS-OK 18 symbols)
//
// STRUCTURE (byte-derived, all verified against the .s):
//   $s3=st=&D_8011F7A8 (int base), $s1=st+0x48 (cach), $s2=st+0xE0 (flag), $s5=&(*(u8 *)D_80078E78) (src), $s4=param.
//   6 HUD fields synced src->cach with a chg-flag at [flag]: pairs 0x3A/0x3C and 0x3E/0x40, then 0x14(s32),
//   0x34(u16)+0x42(u8), 0x1A(s16), 0x4A(u8). Each: `if (cach==src) { if(!chg) goto skip; chg=0; } else {adjust}` + draw.
// KEY FINDINGS (reusable):
//   * Base MUST be `s32`, and the index expr written OFFSET-FIRST (`((p<<16)>>14) + st + 0x18`) — a `u8*` base
//     yields `addu rd,st,off`; the target is `addu rd,off,st`. Matches Ghidra's `(...>>0xe) + -0x7fee0840`.
//   * buf is 24 bytes, NOT Ghidra's 32: MIPS STARTING_FRAME_OFFSET = outgoing_args_size(20), so get_frame_size()
//     counts the 4-byte args-alignment gap. var=MIPS_STACK_ALIGN(4+24)=32 -> 32+24+28 -> 0x58. buf[32] gives 0x60.
//   * Block 1 uses RAW GLOBALS (D_8011F82C...) -> absolute lui/%lo; the ne-block uses `st+0x82`/`st+0x11C`
//     ($s3-relative) — both byte-confirmed; cse blocks end at labels so each region picks its own form.
//   * `ne` pinned to $v0 (+6 aligned).
//
// THE TWO LEVERS THAT CLOSED IT (SESSION-21, both byte-proven here; 18 -> 7 -> 3 -> 1 -> 0):
//   (L1) BLOCK-5 STORE DUPLICATED INTO BOTH ARMS (`if (f&1) *(e+0x32A)=0x200; else *(e+0x32A)=...+0x65;`)
//        instead of computing a phi `sv` and storing once after the merge.  Reason: sched1 is a BACKWARD list
//        scheduler and a store is a memory-unit user, so `potential_hazard` floats it to the FRONT of the
//        backward ready list => it is EMITTED ~8 insns late, which stretches the `sv`/`e` live ranges over
//        $v0/$v1/$a0/$a1 and pushes them out to $a2/$a3.  Writing the store in both arms lets cross_jump
//        merge the common tail, so the store lands first at the merge label, `sv`->$v0 and `e`->$a0, and the
//        `lui $a0` anti-dependence then PINS the schedule.  (18 mismatches -> 7.)
//   (L2) THE COMMUTATIVE-ADD OPERAND SWAP.  Target is `addu $a1,$s0,$v0` = plus(ret1, ret2) into a FRESH
//        non-call-crossing quantity that inherits the $a1 arg copy-suggestion.  Plain `sum = i6 + i4` lets
//        local_alloc TIE the dest to the dying `i6` (which crosses call2) => the whole chain is forced
//        call-saved => `addu $s0,$s0,$v0` (3 mismatched).  Accumulating (`i4 = i6 + i4`) frees $a1 but
//        expand_binop SWAPS a commutative op when target==op1, printing `addu $a1,$v0,$s0` (1 mismatched).
//        Fix: route the second call's value through a copy temp first —
//            sum = i4;  i4 = i6 + sum;
//        target(i4) != op1(sum) at EXPAND time so no swap; cse then folds sum back and deletes the copy.
//        => `addu $a1,$s0,$v0`.  MATCH.

extern void  func_80176FF4(s32);
extern void  func_80177340(s32);
extern u32   func_801783D0(s32, s32);
extern void  func_80177F84(s32, s32);
extern void func_80177DA8(u8 * p, u32 v, s32 idx);
extern void func_80177AD4(int, unsigned int);
extern s32   func_80024054(u8 *, u8 *);
extern u32 *func_80178298(u32*, u8*, short, short);
extern s32   func_8005A600(s32, s32, s32, s32, s32);

void func_80176218(s32 param_1)
{

    extern u16 D_80078EB2;
    extern u16 D_8011F82A;
    extern u16 D_8011F82C;
    extern s16 D_80078EB4;
    extern u16 D_8011F8C4;
    extern u8  D_8011F7A8;   /* st base  ($s3) */
    extern u8 D_80078E78[];   /* cur base ($s5) */
    extern u8  D_80181B1C[];
    extern u8 *D_80181AA0[];
    s32 st   = (s32)&D_8011F7A8;   /* $s3 */
    s32 cach = st + 0x48;          /* $s1 */
    s32 flag = st + 0xE0;          /* $s2 */
    s32 cur  = (s32)&(*(u8 *)D_80078E78);   /* $s5 */
    u8 buf[24];
    s32 ne;
    s32 t;
    u16 sA;

    /* ---- block 1: raw-global pair 0x3A/0x3C ---- */
    sA = D_80078EB2;
    t = (sA != D_8011F82A);
    if (D_8011F82C == (*(u16 *)&D_80078EB4)) {
        ne = t;
        if (ne == 0 && D_8011F8C4 == 0) goto L340;
    } else {
        s32 d = (s16)(D_8011F82C - (*(u16 *)&D_80078EB4));
        u16 nv;
        if (d < 0) {
            if (d < -10) nv = D_8011F82C + 2;
            else         nv = D_8011F82C + 1;
        } else {
            if (d > 10)  nv = D_8011F82C - 2;
            else         nv = D_8011F82C - 1;
        }
        D_8011F82C = nv;
        *(u16 *)(flag + 0x3C) = 1;
        *(u16 *)(cach + 0x3A) = *(u16 *)(cur + 0x3A);
        goto L328;
    }
    if (ne) {
        *(u16 *)(st + 0x82)  = sA;
        *(u16 *)(st + 0x11C) = 1;
    } else {
        *(u16 *)(st + 0x11C) = 0;
    }
L328:
    func_80176FF4(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18));
L340:

    /* ---- block 2: pair 0x3E/0x40 ---- */
    sA = *(u16 *)(cur + 0x3E);
    t = (sA != *(u16 *)(cach + 0x3E));
    if (*(u16 *)(cach + 0x40) == *(u16 *)(cur + 0x40)) {
        ne = t;
        if (ne == 0 && *(u16 *)(flag + 0x40) == 0) goto L444;
    } else {
        s32 d = (s16)(*(u16 *)(cach + 0x40) - *(u16 *)(cur + 0x40));
        u16 nc;
        if (d < 0) {
            if (d < -10) nc = *(u16 *)(cach + 0x40) + 2;
            else         nc = *(u16 *)(cach + 0x40) + 1;
        } else {
            if (d > 10)  nc = *(u16 *)(cach + 0x40) - 2;
            else         nc = *(u16 *)(cach + 0x40) - 1;
        }
        *(u16 *)(cach + 0x40) = nc;
        *(u16 *)(flag + 0x40) = 1;
        *(u16 *)(cach + 0x3E) = *(u16 *)(cur + 0x3E);
        goto L3E8;
    }
    if (ne) {
        *(u16 *)(cach + 0x3E) = sA;
        *(u16 *)(flag + 0x40) = 1;
    } else {
        *(u16 *)(flag + 0x40) = 0;
    }
L3E8:
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u16 cc;
        s32 pp;
        func_80177340(*(s32 *)(s0b + 0x18) + 0x104);
        cc = *(u16 *)(cach + 0x40);
        pp = *(s32 *)(s0b + 0x28);
        if (cc < 100)
            *(u8 *)(pp + 0x5D) = D_80181B1C[cc / 5];
        else
            *(u8 *)(pp + 0x5D) = 0;
    }
L444:

    /* ---- block 3: field 0x14 (s32) ---- */
    if (*(s32 *)(cach + 0x14) == *(s32 *)(cur + 0x14)) {
        if (*(s32 *)(flag + 0x14) == 0) goto L4D0;
        *(s32 *)(flag + 0x14) = 0;
        goto L4A8;
    } else {
        s32 d = *(s32 *)(cur + 0x14) - *(s32 *)(cach + 0x14);
        s32 nd;
        if (d > 0) {
            if (d < 10) nd = *(s32 *)(cach + 0x14) + 1;
            else        nd = *(s32 *)(cach + 0x14) + 10;
        } else {
            if (d < -9) nd = *(s32 *)(cach + 0x14) - 10;
            else        nd = *(s32 *)(cach + 0x14) - 1;
        }
        *(s32 *)(cach + 0x14) = nd;
        *(s32 *)(flag + 0x14) = 1;
    }
L4A8:
    {
        u32 r = func_801783D0(*(s32 *)(cach + 0x14), 0);
        func_80177F84(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x208, r);
    }
L4D0:

    /* ---- block 4: field 0x34 (u16) + 0x42 (u8) ---- */
    if (*(u16 *)(cur + 0x34) != *(u16 *)(cach + 0x34)) {
        *(u16 *)(cach + 0x34) = *(u16 *)(cur + 0x34);
        *(u16 *)(flag + 0x34) = 1;
        *(u8 *)(cach + 0x42) = *(u8 *)(cur + 0x42);
    } else {
        if (*(u16 *)(flag + 0x34) == 0) goto L558;
        *(u16 *)(flag + 0x34) = 0;
    }
    {
        u16 e = 999;
        s16 r;
        if (*(u16 *)(cach + 0x34) < 1000) e = *(u16 *)(cach + 0x34);
        r = (s16)func_801783D0((s16)e, 4);
        func_80177DA8(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x294,
                      (s32)r, *(u8 *)(cach + 0x42));
    }
L558:

    /* ---- block 5: field 0x1A (s16) ---- */
    if (*(s16 *)(cach + 0x1A) != *(s16 *)(cur + 0x1A)) {
        *(s16 *)(cach + 0x1A) = *(s16 *)(cur + 0x1A);
        *(s16 *)(flag + 0x1A) = 1;
    } else {
        if (*(s16 *)(flag + 0x1A) == 0) goto L63C;
        *(s16 *)(flag + 0x1A) = 0;
    }
    {
        u16 f = *(u16 *)(cach + 0x1A);
        s32 e = *(s32 *)(((param_1 << 16) >> 14) + st + 0x18);
        s32 i6, i4, sum;
        /* L1: the store is written into BOTH arms so cross_jump merges the tail (see header). */
        if (f & 1) *(s16 *)(e + 0x32A) = 0x200;
        else       *(s16 *)(e + 0x32A) = *(u16 *)(st + 0x16) + 0x65;
        {
            s32 t = (((s16)f / 15) & 3) * 15;
            i6 = func_801783D0(((s16)f / 15) * 0x10000 >> 0x12, 8);
            i4 = func_801783D0((t * 0x10000) >> 16, 0);
        }
        /* L2: copy temp defeats expand_binop's commutative swap; cse folds it back (see header). */
        sum = i4;
        i4 = i6 + sum;
        ((void (*)(s32, s32))func_80177AD4)(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 800,
                      i4 * 0x10000 >> 0x10);
    }
L63C:

    /* ---- block 6: field 0x4A (u8) ---- */
    if (*(u8 *)(cur + 0x4A) != *(u8 *)(cach + 0x4A)) {
        *(u8 *)(cach + 0x4A) = *(u8 *)(cur + 0x4A) & 0x7F;
        *(u8 *)(flag + 0x4A) = 1;
    } else {
        if (*(u8 *)(flag + 0x4A) == 0) return;
        *(u8 *)(flag + 0x4A) = 0;
    }
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u8 *arg = D_80181AA0[*(u8 *)(cach + 0x4A)];
        u32 *p = (u32 *)(*(s32 *)(s0b + 0x18) + 900);
        func_80024054(arg, buf);
        p = ((u32 * (*)(u32 *, u8 *, s32, s32))func_80178298)(p, buf,
                          (s16)(*(u16 *)(st + 0x14) + 0x39),
                          (s16)(*(u16 *)(st + 0x16) + 0x5B));
        func_8005A600((s32)p, 0, 0, 0x15, 0);
        *p = ((u32)((u8 *)p - 0x14) & 0xffffff) | 0x2000000;
        *(u32 **)(s0b + 0x20) = p;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176734;

void func_80176734(s32 param_1)
{
    extern u8  D_8011F7A8;      /* st base  ($s3) */
    extern u8  D_80078E78[];    /* cur base ($s4) */
    extern s16 D_801152BA;
    extern u8  D_8011F7B0;      /* == *(u8 *)(st + 8), read absolutely (mixed addressing) */
    extern u8  D_80115214;
    extern u8  D_80181B3C[];
    extern u16 D_80181A8E[];
    extern u16 D_80181A9C;
    extern u8  D_80181B30[];
    extern s32 D_80181B48[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;
    extern u8  D_800B9A13;
    extern s16 D_80126CE0;
    extern s16 D_80126D20;
    extern s32 D_80126B58;
    extern void func_800183E0(s32 a0);
    extern s32  func_801619D0(void *a0);
    extern s32  func_80161A00(s32 a0);
    extern s32  func_80161A30(s32 a0);
    extern s32  func_80161A60(s32 a0);
    extern void func_801775E0(s32 param_1, s32 param_2);

    s32 st, cach, flag, cur;
    register s32 chg  __asm__("$21");        /* L7 */
    register s32 chg2 __asm__("$16");        /* L7 */
    s32 amp;                                 /* $s0, disjoint from chg2 */
    register u16 tgt __asm__("$5");          /* L7 */
    s32 pv;                                  /* L6: the param copy that owns $s6 */
    s32 ix;                                  /* L6: block A's index, hoisted out of the block */
    u8  dum[8];                              /* L5: dead frame slot (target .frame vars=8) */

    st  = (s32)&D_8011F7A8;
    ix  = ((param_1 << 16) >> 14) + st;
    pv  = param_1;
    cach = st + 0x48;
    flag = st + 0xE0;
    cur  = (s32)&(*(u8 *)D_80078E78);

    /* ---- block A: pulse byte ---- */
    {
        register s32 p __asm__("$5");        /* L7 */
        u8 *q;
        p = *(s32 *)(ix + 0x28);
        q = (u8 *)(p + 0x3C);                /* L2: must live in the entry BB */
        if (D_801152BA != 0) {
            u8 b = D_8011F7B0;               /* L1 */
            u8 v;
            if (b < 0x80) v = b - 0x80;
            else          v = ~b - 0x80;
            q[4] = v;
            *(u8 *)(p + 4) = v;
            *(u8 *)(st + 8) = *(u8 *)(st + 8) + D_80115214;
        } else {
            *(u8 *)(p + 0x40) = 0x80;
            *(u8 *)(p + 4) = 0x80;
        }
    }

    /* ---- block B: 0x48 animation already running ---- */
    if (*(u8 *)(flag + 0x48) != 0) {
        register s32 pp __asm__("$5");       /* L7 */
        pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        *(u8 *)(pp + 0xD) = D_80181B3C[*(u8 *)(flag + 0x48)];
        if (*(u8 *)(flag + 0x48) < 4) {
            *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
        } else {
            u8 c = *(u8 *)(cach + 0x48);
            s32 q = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
            s32 arg;
            if (c & 0x80) {
                *(u16 *)(q + 0x20) = D_80181A9C;
                arg = (s32)&D_800D45D4;
            } else if (c != 0) {
                *(u16 *)(q + 0x20) = D_80181A8E[c];
                arg = D_80181B48[*(u8 *)(cach + 0x48)];
            } else {
                goto Lskip;
            }
            func_800183E0(arg);
        Lskip:
            if (*(u8 *)(flag + 0x48) == 5) {
                if (*(u8 *)(cach + 0x48) == 0) *(u8 *)(flag + 0x48) = 0;
                else *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            } else if (*(u8 *)(flag + 0x48) == 10) {
                *(u8 *)(flag + 0x48) = 0;
            } else {
                *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            }
        }
    /* ---- block C: 0x48 changed -> start the animation ---- */
    } else if (*(u8 *)(cach + 0x48) != *(u8 *)(cur + 0x48)) {
        register s32 pp __asm__("$5");       /* L7 */
        u8 k;                                /* L1: gives the `andi $v1,$v1,0xFF` index mask */
        if (*(u8 *)(cach + 0x48) == 0 && *(u8 *)(cur + 0x48) != 0)
            *(u8 *)(flag + 0x48) = 5;
        else
            *(u8 *)(flag + 0x48) = 0;
        *(u8 *)(cach + 0x48) = *(u8 *)(cur + 0x48);
        pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        k = *(u8 *)(flag + 0x48);
        *(u8 *)(flag + 0x48) = k + 1;
        *(u8 *)(pp + 0xD) = D_80181B3C[k];
    }

    /* ---- block D: field 0x2E (equality-first: the ne-arm must be out of line) ---- */
    if (*(s16 *)(cach + 0x2E) == *(s16 *)(cur + 0x2E)) {
        if (*(s16 *)(flag + 0x2E) == 0) goto L9C0;
        *(s16 *)(flag + 0x2E) = 0;
    } else {
        *(s16 *)(cach + 0x2E) = *(s16 *)(cur + 0x2E);
        *(s16 *)(flag + 0x2E) = 1;
    }
    {
        s32 pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        s32 t = (s32)(*(u16 *)(cach + 0x2E) << 16);
        if (t != 0) *(u8 *)(pp + 0x49) = D_80181B30[t >> 20];
        else        *(u8 *)(pp + 0x49) = 0xA0;
    }
L9C0:

    /* ---- block E: field 0x1E sign flip ---- */
    {
        s32 fa = *(s16 *)(cach + 0x1E) & 0x8000;
        s32 fb = *(s16 *)(cur + 0x1E) & 0x8000;
        if (fa != fb) {
            s32 arg;
            if (fa != 0) {
                *(s16 *)(cach + 0x1E) = 0;
                arg = (s32)&D_800D43D4;
            } else {
                *(s16 *)(cach + 0x1E) = -0x8000;
                arg = (s32)&D_800D4414;
            }
            func_800183E0(arg);
        }
    }

    /* ---- block F: mode byte -> chg ---- */
    {
        u8 m = D_800B9A13;                   /* L1 */
        if (m != 3) {                        /* inverted: `chg = 0` belongs out of line */
            register s32 t __asm__("$2");    /* L3a: pin + 2 uses keeps `chg = t` alive */
            t = (*(u8 *)(st + 7) != m);
            chg = t;
            if (t != 0) *(u8 *)(st + 7) = m;
        } else {
            chg = 0;
        }
    }

    /* ---- block G: switch on cur[0x48] (cases 3/4/5 cross-jump onto one tail) ---- */
    amp = 0;
    switch (*(u8 *)(cur + 0x48)) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) amp = 0xFF;
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) amp = 0xBA;
        break;
    }

    /* ---- block H: amp != 0 short-circuit ---- */
    {
        s32 av;
        av = amp;
        __asm__("" : "=r"(av) : "0"(av));    /* L3b: keeps the `move $v0,$s0` at the merge */
        if (av != 0) {
            *(u8 *)(flag + 0x47) = 1;
            *(u8 *)(cach + 0x4B) = *(u8 *)(cur + 0x48) | 0xF0;
            *(u8 *)(cach + 0x47) = ((s32)D_80126D20 << 7) / av;
            goto Ltail;
        }
    }

    if (*(u8 *)(cach + 0x4B) >= 0xF0) *(u8 *)(cach + 0x4B) = 0;

    /* ---- block I: target level + change flag.  The lhu is unconditional (target loads
       both the signed and the unsigned view of D_80126CE0 up front). ---- */
    tgt = *(u16 *)&D_80126CE0;
    if (D_80126CE0 != 0) {
        u16 v;                               /* dies at the mask -> destructive `andi $v1,$v1` */
        register s32 t __asm__("$2");
        v = tgt;
        *(u8 *)(cach + 0x4B) = v;
        t = (*(u8 *)(cach + 0x47) != (v & 0xFF));
        __asm__("" : "=r"(t) : "0"(t));      /* L3b */
        chg2 = t;
    } else {
        u32 cv = *(u8 *)(cach + 0x47);       /* L8: one load, two compares, no re-mask */
        tgt = *(u8 *)(cur + 0x47);
        chg2 = 0;
        if (cv != tgt || cv == 0x80) chg2 = 1;
        if (*(u8 *)(cur + 0x47) != 0 && *(u8 *)(cach + 0x4B) != 0) {
            *(u8 *)(cach + 0x4B) = 0;
            *(u8 *)(cach + 0x47) = *(u8 *)(cur + 0x47);
        }
    }

    /* ---- block J: nothing-changed fast path.  The target re-tests chg after the flag load;
       the fence below is what stops cse from folding that second test away. ---- */
    {
    register s32 c __asm__("$3");
    c = chg;
    if (chg2 != 0) goto Lbig;
    if (c != 0) goto Lbig;
    if (*(u8 *)(flag + 0x47) == 0) goto Ltail;
    __asm__("" : "=r"(c) : "0"(c));          /* L3b */
    if (c == 0) goto Lzero;
    }
Lbig:
    /* ---- block K: slew cach[0x47] toward tgt ---- */
    {
        u32 c = *(u8 *)(cach + 0x47);
        s32 sv = (s16)tgt;                   /* L8 */
        if ((s32)c < sv) {
            *(u8 *)(cach + 0x47) = tgt;
        } else {
            if (sv != 0) *(u8 *)(cach + 0x47) = c - 3;   /* L4: store in BOTH arms */
            else         *(u8 *)(cach + 0x47) = c - 8;
            c = *(u8 *)(cach + 0x47);        /* stays a real lbu because of L4 */
            if (c == 0 || c > 0x80) {
                *(u8 *)(cach + 0x47) = 0;
                *(u8 *)(cach + 0x4B) = 0;
            } else if ((s32)c < (s16)tgt) {  /* fresh EBB -> the sll/sra is recomputed */
                *(u8 *)(cach + 0x47) = tgt;
            }
        }
        *(u8 *)(flag + 0x47) = 1;
    }
    goto Ltail;
Lzero:
    *(u8 *)(flag + 0x47) = 0;
Ltail:

    /* ---- block L: tail.  m+5 / m+9 are separate temps: `lhu + (m+5)`, not `(lhu + m) + 5`. ---- */
    {
        s32 b = ((pv << 16) >> 14) + st;
        s32 m = (*(u8 *)(st + 7) != 0) << 8;
        s32 m5 = m + 5;
        s32 m9 = m + 9;
        *(u16 *)(*(s32 *)(b + 0x28) + 0x32) = *(u16 *)(st + 0x12) + m5;
        func_801775E0(*(s32 *)(b + 0x28) + 0x64, (s16)(*(u16 *)(st + 0x12) + m9));
    }
}


DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


DEFINE_func_801775E0()  /* dedup: shared engine-core @0x801775e0 (src/shared) */


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


DEFINE_func_801777BC()  /* dedup: shared engine-core @0x801777bc (src/shared) */





// @class: regalloc-order
// @stuck: none — MATCH
void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4) {
    register unsigned int uVar1 __asm__("$2");
    register unsigned int nib __asm__("$3");
    int iVar2;
    register int im1 __asm__("$11");
    int p4;
    register char *p __asm__("$7");
    short iVar4;
    unsigned short uVar5;
    register unsigned int mask __asm__("$12");

    uVar5 = 0x100;
    iVar2 = (int)param_3;
    iVar4 = 0;
    if (0 < iVar2) {
        im1 = iVar2 - 1;
        p4 = (int)param_4;
        mask = ~0x100;
        p = (char *)(param_1 + 0xc);
        do {
            uVar1 = (param_2 << 16) >> 28;
            nib = uVar1;
            if (((uVar1 != 0) || ((int)iVar4 == im1)) ||
                ((int)iVar4 == p4)) {
                uVar5 = 0;
            }
            param_2 = param_2 << 4;
            *p = (char)(nib * 8 + 8);
            *(unsigned short *)(p - 2) = uVar5 | (*(unsigned short *)(p - 2) & mask);
            iVar4 = iVar4 + 1;
            p = p + 0x14;
        } while ((int)iVar4 < iVar2);
    }
    return;
}


DEFINE_func_80177940()  /* dedup: shared engine-core @0x80177940 (src/shared) */


DEFINE_func_80177AD4()  /* dedup: shared engine-core @0x80177ad4 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177B5C;

/* func_80177B5C - MATCH (147/147 ins), wave23.
 *
 * Seed: .run/near6/func_80177B5C_ils.c (permuter-improved, closeness 7).
 * Two residual clusters remained; both cracked, each by a sourced gcc-2.7.2 mechanism.
 *
 * CLUSTER C (idx 86-89) - the "cl | ((n*8+8) | 0x4000)" re-association.
 *   NOT a cse fold. It happens in the FRONT END: fold-const.c fold(), the `associate:`
 *   arm at :3685. For `A | (X | C)`, split_tree(arg1) (:3759, decomposer at :882) splits
 *   arg1 into var=X / con=C because TREE_CONSTANT(op1) holds, then rebuilds it as
 *   `(A | C) | X` at :3785. Verified in the FIRST RTL dump (t.i.rtl insn 215 already
 *   reads `(ior v1 16384)`), so no RTL-level lever (the cse if/else diamond, tie or
 *   volatile barriers, operand swap, shift-vs-multiply) can ever reach it.
 *   ANTIDOTE: hoist the inner IOR into its own statement. The outer arg1 is then a
 *   VAR_DECL, split_tree returns 0, and the associate arm is skipped. (This function
 *   already proved the shape at `tt = uv | 0x1000; p[3] = cl | tt;`, which matched.)
 *
 *   That exposed a REGALLOC residual: the chain landed in $a3 (`sll a3,a3,3`) instead
 *   of $v0. Cause: `n` was pinned to a HARD reg, and local-alloc.c combine_regs():1798
 *   unconditionally records a dying hard-reg SOURCE in qty_phys_sugg[] for the dest
 *   pseudo, so the shift dest inherited $a3. A *pseudo* source cannot do that - :1763
 *   bails when reg_qty[ureg] < 0 (i.e. not block-local), and the target's `n` crosses
 *   the join, so it is exactly such a pseudo.
 *   ANTIDOTE: move the pin off `n` (which dies into the shift) onto `nn` (the tested
 *   value). `nn` pinned to $2 keeps the two distinct so the `addu $a3,$v0,$zero` copy
 *   survives (combine_regs :1841 refuses to tie when the DEST is non-block-local),
 *   while `n` stays a pseudo and the shift chain gets an ordinary local quantity ->
 *   $v0 - which also restores the target schedule, because the $v0 anti-dependence on
 *   `sw $v0,-0x4($a1)` is what stops sched2 hoisting the chain above the store.
 *   [7 -> 8 -> 3]
 *
 * CLUSTER B (idx 24-27) - `lui $t0,0x300` two slots early.
 *   Pure sched1 LUID tie-break, read straight off the -da trace (t.i.sched, T-36):
 *   ready = { 58 (7f000001), 72 (7f000001), ... } - insn 58 (lui $t0) IS birthing-
 *   boosted (sched.c birthing_insn_p:2469 works on hard regs too; reg_n_sets[$t0]==1),
 *   so 58/71/72 all tie at max_priority and rank_for_schedule:2427 falls through to
 *   DESCENDING LUID. Source order put `ca = 0x3000000;` before the mask, so
 *   LUID(58) < LUID(72) and the lui was placed first.
 *   (The companion mask 0xFFFFFF correctly stays at idx 6-7 because lui+ori is TWO
 *   sets of $t1 -> reg_n_sets==2 -> no boost -> it sinks to the block head. Same
 *   mechanism, opposite sign - the model predicts both.)
 *   ANTIDOTE: split the mask into its own statement (`gg`) and materialise the
 *   constant BETWEEN it and the OR, so expand emits addiu, and, lui, or in that order
 *   and LUID(58) > LUID(72). Sweeping the plain statement position of `ca = ...` was
 *   inert (all 11 slots scored 3) - only interposing the temp moves the LUID past the
 *   AND. [3 -> 0]
 *
 * Dead ends measured, not guessed: pin nv to $2 = 27; reuse tt = 24; reuse uv = 29;
 * two-step |= = 15; unpin n = 84 (146 ins, the copy coalesces away); unpin ca = 139;
 * ca as a bare literal = 139 (145 ins - cse merges it with the loop copy, so the hard
 * pin is what keeps the pre-loop and in-loop constants separate); both literal = 143;
 * `(ca = 0x3000000)` as an assignment-EXPRESSION = 114 (148 ins, extra move); reusing
 * the existing `g` for the mask temp instead of a fresh one = 8 (g has a 2nd set later).
 */
u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s32 tbli;
s32 x;
s32 y;
{

    extern u8 D_80181B64[];
register u32 bb __asm__("$14");
  u32 *q;
register u32 v __asm__("$25");
register u32 cl __asm__("$3");
register u32 cs __asm__("$5");
register u32 ca __asm__("$8");
  s16 i;
  u32 mk1;
  u32 cc1;
  u32 flag;
register u32 nn __asm__("$2");
  u32 n;
register u32 t __asm__("$13");
  u32 col;
  u32 uv;
  u32 tt;
  u32 nv;
  u32 x1;
  u32 x2;
  u32 w;
  u32 g;
  u32 gg;
  u32 w3;
register u32 yr __asm__("$16");
register u32 yt __asm__("$4");
register u32 tr __asm__("$21");
register u32 xr __asm__("$17");
register u32 c3 __asm__("$18");
register s32 ff __asm__("$19");
register s32 two __asm__("$20");
  yt = y;
  tr = tbli;
__asm__("" : "=r"(tr) : "0"(tr));
  xr = x;
__asm__("" : "=r"(xr) : "0"(xr));
  mk1 = 0xFFFFFF;
  cc1 = 0x74808080;
  bb = bits;
  t = x + 0xE;
  flag = 0x1000000;
  i = 0;
  two = 2;
  ff = 255;
  ;
  v = D_80181B64[(s16) tbli];
  gg = ((u32) (p - 5)) & mk1;
  ca = 0x3000000;
  p[0] = gg | ca;
  x1 = (x - 3) & 0xFFFF;
  x2 = (x + 5) & 0xFFFF;
  p[1] = cc1;
  yr = yt;
__asm__("" : "=r"(yr) : "0"(yr));
  yt = (s16) yt;
  cs = (yt + 1) << 16;
  w = cs | x1;
__asm__("" : "=r"(w) : "0"(w));
  cl = ((v << 6) | 0x4016) << 16;
  p[2] = w;
  p[3] = cl | 0x1800;
  p += 5;
  p[0] = (((u32) (p - 5)) & mk1) | ca;
  p[1] = cc1;
  p[2] = cs | x2;
  p[3] = cl | 0x1808;
  p += 5;
  q = p;
  yt = yt << 16;
  {
    for (; i < 3; i++)
    {
      nn = ((bb << 16) >> 18) >> 10;
      n = nn;
      if (((nn != 0) || (i == two)) || (i == ff))
      {
        flag = 0;
      }
      q[0] = (((u32) (q - 5)) & 0xFFFFFF) | 0x3000000;
      q[2] = (yt | (t & 0xFFFF)) | flag;
      col = 0x74808080;
      q[1] = col;
      nv = ((n * 8) + 8) | 0x4000;
      q[3] = cl | nv;
      q += 5;
      t += 8;
      bb <<= 4;
    }

  }
  p = q;
__asm__("" : "=r"(v) : "0"(v));
  g = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
__asm__ __volatile__("");
  cs = yr << 16;
  p[0] = g;
  w3 = cs | ((xr + 0x2A) & 0xFFFF);
__asm__ __volatile__("");
  cl = ((v << 6) | 0x4016) << 16;
  uv = ((s16) tr) << 4;
  p[2] = w3;
  tt = uv | 0x1000;
  p[1] = col;
  p[3] = cl | tt;
  p += 5;
  p[0] = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
__asm__ __volatile__("");
  cs = cs | ((xr + 0x32) & 0xFFFF);
  uv = uv | 0x1008;
  cl = cl | uv;
  p[1] = col;
  p[2] = cs;
  p[3] = cl;
  p += 5;
__asm__("" :: "r"(tr), "r"(xr));
  return p;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177DA8;


void func_80177DA8(p, v, idx)
u8 *p;
u32 v;
s16 idx;
{

    extern u8 D_80181B64[];
    u8 *r;
    u16 c;
    u16 flag;
    u32 n;
    u8 m;
    s16 i;
    u8 t;
    u32 x;
    u32 uv;
    u32 w1;
    u32 w2;

    flag = 0x100;
    i = 0;
    t = D_80181B64[idx];
    c = (t << 6) | 0x4016;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    r = p;
    do {
        n = (v << 16) >> 28;
        m = n;
        if (n != 0 || i == 2 || i == 0xFF) {
            flag = 0;
        }
        v <<= 4;
        i++;
        *(s16 *)(r + 0xA) = flag | (*(s16 *)(r + 0xA) & ~0x100);
        *(u8 *)(r + 0xC) = m * 8 + 8;
        r += 0x14;
    } while (i < 3);
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    x = ((t << 6) | 0x4016) << 16;
    uv = idx << 4;
    w1 = uv | 0x1000;
    *(u32 *)(p + 0xC) = x | w1;
    w2 = uv | 0x1008;
    *(u32 *)(p + 0x20) = x | w2;
}


DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */




DEFINE_func_80178004()  /* dedup: shared engine-core @0x80178004 (src/shared) */


DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_80183B94;
    func_8001534C(2, &D_80183B94, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}


DEFINE_func_8017849C()  /* dedup: shared engine-core @0x8017849c (src/shared) */


DEFINE_func_80178608()  /* dedup: shared engine-core @0x80178608 (src/shared) */


DEFINE_func_8017869C()  /* dedup: shared engine-core @0x8017869c (src/shared) */


DEFINE_func_80178744()  /* dedup: shared engine-core @0x80178744 (src/shared) */


DEFINE_func_801787D4()  /* dedup: shared engine-core @0x801787d4 (src/shared) */



// @class: regalloc-order
// @stuck: sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);


void func_80178840(int param_1) {

    extern int D_80181BC4;
    extern int D_80181BD0[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_80181BC4);
        }
        ((void (*)(int, int))func_80131E00)(p, D_80181BD0[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80178970;

// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern s32 func_801789AC(s32 arg0);

int func_80178970(void)
{

    extern s16 D_80185C08;
    register int r __asm__("$2");
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_80185C08 == 0;
    return r;
}
