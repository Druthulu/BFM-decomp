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
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80128FAC(u16 *arg0);
extern s16 D_8011DB2C;
extern s16 D_8011DB30;
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
extern s16 D_800B9AAE[];
extern s16 D_800B9AB0[];
extern s16 D_800B9AB4[];
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
/* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_800AE688[];
/* canonical (10 siblings): scalar s32 — store (s32)ptr */
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
extern s32 func_8012B77C(s32 out, s32 a1, s32 a2);
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
extern char D_801C841C[];
void func_80136BC4(s32 a0);
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
/* ==== end §8b carried decl layer ==== */



// @class: regalloc-order
// @stuck: none — MATCH (490 ins, match_one, canonical-typed)
//
// func_8013F350 — 490-ins GIANT (menu/pad state machine, double jump table
// jtbl_801D8860 [8] + jtbl_801D8880 [5]). Load-bearing levers, do NOT "clean up":
//
//  1. `register s32 off __asm__("$4")` — THE crack. gcc otherwise emits pmax
//     before pcur, letting pcur sink into the beq delay slot (target has a nop
//     there) and losing the off/pmax coalesce into $a0. Pinning off cost 0 insns
//     and took the diff 162 -> 13. (`bb` shares $4; live ranges are disjoint.)
//  2. `register u16 *pd __asm__("$5")` + the "=r"/"0" self-barrier — without the
//     barrier gcc const-propagates &D_8011511C away and %lo-folds every access
//     (target holds the base: lhu 0($a1) / lhu 4($a1) / sh 4($a1)). The barrier
//     emits zero code; it only hides the pointer's constant value from cse.
//     NOTE: `ps` (&D_8011511A) must NOT get the same barrier — it regressed.
//  3. `case 0/2/3: break;` in the inner switch are NOT dead — 5 case nodes is
//     what pushes gcc past CASE_VALUES_THRESHOLD into a jump table (jtbl_801D8880)
//     instead of a compare chain (worth 18 instructions).
//  4. case 5 tests (flags & 0x10) with `!= 0 -> goto tail6`, case 6 with
//     `== 0 -> break`. The OPPOSITE polarity is what stops gcc cross-jumping the
//     two tails into one (§5a class, solved by source shape, not an asm barrier).
//  5. `if (d > 0) A; else if (d < 0) A;` — a single `d > 0 || d < 0` is folded to
//     `d != 0` by the FRONT END (andi 0xffff; beqz). Two ifs keep bgtz+bgez; gcc's
//     cross-jump then re-merges the twin store blocks, which is the target's shape.
//  6. 0x1000/0x8000/0x2000 blocks are written in-place (`pcur[0] = pcur[0] - 1`)
//     -> one register + a load-delay nop. The 0x4000 block needs the `b` temp
//     (its ==3 arm restores the original), so it keeps two registers and no nop.
//  7. `s16 d` (not s32 + <<16>>16): the wide form pushed the frame 0x30 -> 0x38.
//  8. `pad` is u16 (its andi 0xFFFF is real) but `st` must stay u16 AND be used
//     only for the pointer math / `st == 2` — the D_80115140 index re-reads
//     D_8011511A, which is what keeps st free of a masking andi.
//
// Canonical-reconciled (§17a-1) and re-verified MATCH: D_8011512E keeps the TU's
// `u16` canonical with `*(s16*)&` at the read sites (target needs lh), and
// func_8014168C keeps the canonical s16(s16) decl with s32(s32) call-site casts.
// Def sig is s32(void); engine_core.h canon is `void func_8013F350(void)` and the
// callers already cast (`((short (*)(void))func_8013F350)()`) -> def-side reconcile.

extern u16 D_80115110;
extern u16 D_8011511C;
extern u16 D_8011511E;
extern u16 D_80115120;
extern u16 D_80115122;
extern s16 D_80115128;
extern s16 D_8011512A;
extern u16 D_8011512E;
extern u8  D_80115140[];
extern s16 D_8011514C;
extern s16 D_8011514E;
extern u8  D_80115152;
extern u8 D_80115158[];   /* macro-canonical redecl (§8e) */
extern u8 D_8011515C;     /* macro-canonical redecl (§8e) */
extern u8  D_80184CA8[];
extern u8  D_80184CC0[];
extern u16 D_80184BC4[];

extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);
extern s16 func_8014168C(s16 a0);
extern void func_8014AA04(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801415C0(s32 a0, s32 a1);
extern void func_80141C0C(s32 a0);
extern s32 func_80140608(s32 a0);
extern void func_801407F4(void);
extern s32 func_801416D4(s16);  /* macro-canonical redecl (§8e) */

s32 func_8013F350(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_8011511A;
    register u16 *pd __asm__("$5") = &D_8011511C;
    u16 *ps;
    u16 *pf;
    u16 *pg;
    u16 pad;
    u16 st;
    u8 *pcur;
    u8 *pmax;
    u8 *p2e;
    u8 *p3e;
    register s32 off __asm__("$4");
    s16 i;
    s32 r;
    s16 rs;
    s16 d;
    u8 b;
    register u8 bb __asm__("$4");
    u8 m;
    s32 chg;

    __asm__ __volatile__("" : "=r"(pd) : "0"(pd));
    pad = *pd;
    chg = 0;
    if (pad != 0) {
        if (pad == pd[2]) {
            D_80115122 = D_80115122 - 1;
            if (D_80115122 == 0) {
                D_8011511E = pad & 0xF000;
                D_80115122 = 3;
            }
        } else {
            pd[2] = pad;
            D_80115122 = 6;
        }
    } else {
        D_80115120 = 0;
        D_80115122 = 0xC;
    }

    i = 0;
    do {
        if ((func_80029178(D_80184CA8[i]) & 0xFF) == 0) {
            break;
        }
        i = i + 1;
    } while (i < 6);
    *(u16 *)D_80115158 = i | 0x100;          /* §18: sh under canonical u8[] */

    switch (D_8011511A) { /* jtbl_801D8860 */
    case 0:
        r = ((s32 (*)(s32))func_8014168C)(0);
        rs = (s16)r;
        if ((func_80029178(D_80184CA8[rs]) & 0xFF) != 0 && (D_8011511E & 0x40) != 0) {
            func_8014AA04((r + 1) & 0xFF);
            if (rs != 0) {
                func_8002D4C8(0x461, 0);
            } else {
                func_8002D4C8(0x460, 0);
            }
        }
        break;
    case 1:
        if ((D_8011511E & 0x40) != 0) {
            D_80115128 = ((s32 (*)(s32))func_8014168C)(1) + 1;
            D_8011511A = 2;
            func_80141C0C(3);
            return 1;
        }
        if (D_80115128 != 4) {
            break;
        }
        goto tail7;
    case 2:
        switch (D_80115128) { /* jtbl_801D8880 */
        case 0:
            break;
        case 1:
            r = ((s32 (*)(s32))func_8014168C)(2);
            pf = &D_8011511E;
            if ((*pf & 0x40) != 0) {
                if ((*(s16 *)&D_8011512E) == 0) {
                    if ((func_800291B4(D_80184CC0[(s16)r]) & 0xFF) != 0 && (*pf & 0x40) != 0) {
                        D_8011511A = 5;
                        *(s16 *)&D_80115152 = 0;
                        func_80141C0C(3);
                        return 1;
                    }
                    func_80141C0C(5);
                } else {
                    func_801415C0((s16)r, (*(s16 *)&D_8011512E) & 0xF);
                    D_8011512E = 0;
                    func_80141C0C(3);
                    return 1;
                }
            } else if ((*pf & 0x20) != 0) {
                if ((*(s16 *)&D_8011512E) == 0) {
                    D_8011512E = r | 0x8000;
                } else {
                    func_801415C0((s16)r, (*(s16 *)&D_8011512E) & 0xF);
                    D_8011512E = 0;
                }
                func_80141C0C(3);
            }
            break;
        case 4:
            if ((D_8011511E & 0xA000) != 0) {
                chg = func_80140608(2);
            }
            func_801407F4();
            break;
        case 2:
            break;
        case 3:
            break;
        }
        if (D_80115128 != 0 && (D_8011511E & 0x10) != 0 && D_80115110 != 1) {
            D_8011511E = D_8011511E & 0xFFEF;
            D_8011511A = 1;
            D_8011512E = 0;
            func_80141C0C(6);
        }
        break;
    case 3:
        if (D_8011514E == 0 && (D_8011511E & 0x40) != 0) {
            D_8011511A = D_8011511A + 3;
            func_80141C0C(3);
            return 1;
        }
        break;
    case 5:
        if ((D_8011511E & 0x40) != 0) {
            rs = (s16)((s32 (*)(s32))func_801416D4)(D_80115152);  /* §17a-1: def is (s16) */
            if (rs != 0) {
                if (rs < 0) {
                    D_8011512A = 1;
                } else {
                    D_8011511A = D_8011511A - 3;
                    func_80141C0C(4);
                    return 1;
                }
            }
            break;
        }
        if ((D_8011511E & 0x10) != 0) {
            goto tail6;
        }
        break;
    case 6:
        if ((D_8011511E & 0x10) == 0) {
            break;
        }
    tail6:
        pg = &D_8011511E;
        *pg = *pg & 0xFFEF;
        D_8011511A = D_8011511A - 3;
        func_80141C0C(6);
        return 1;
    case 7:
        if ((D_8011511E & 0xA000) != 0) {
            chg = func_80140608(7);
        }
    tail7:
        func_801407F4();
        break;
    }

    ps = &D_8011511A;
    
    st = *ps;
    p2e = (u8 *)ps + 0x2E;
    p3e = (u8 *)ps + 0x3E;
    off = st << 1;
    pcur = p2e + off;
    pmax = p3e + off;
    if (st == 2 || 1 < pmax[0]) {
        if ((D_8011511E & 0x1000) != 0) {
            pcur[0] = pcur[0] - 1;
            chg = 1;
            if (0x7F < pcur[0]) {
                if (D_8011511A != 3) {
                    pcur[0] = pmax[0] - 1;
                } else {
                    pcur[0] = 0;
                    chg = 0;
                }
            }
        }
        if ((D_8011511E & 0x4000) != 0) {
            b = pcur[0];
            pcur[0] = b + 1;
            chg = 1;
            if (pmax[0] <= (u8)(b + 1)) {
                if (D_8011511A != 3) {
                    pcur[0] = 0;
                } else {
                    pcur[0] = b;
                    chg = 0;
                }
            }
        }
        if (D_8011511A == 2 && D_80115128 == 1) {
            if ((D_8011511E & 0x8000) != 0) {
                pcur[1] = pcur[1] - 1;
                chg = 1;
                if (0x7F < pcur[1]) {
                    pcur[1] = pmax[1] - 1;
                }
            }
            if ((D_8011511E & 0x2000) != 0) {
                pcur[1] = pcur[1] + 1;
                chg = 1;
                if (pmax[1] <= pcur[1]) {
                    pcur[1] = 0;
                }
            }
        } else {
            bb = pcur[0];
            m = D_80115140[D_8011511A];
            d = (s8)bb - (s8)m;
            if (d > 0) {
                D_80115140[D_8011511A] = bb;
            } else if (d < 0) {
                D_80115140[D_8011511A] = bb;
            }
        }
        if (D_8011511A == 1) {
            D_80115128 = ((s32 (*)(s32))func_8014168C)(1) + 1;
            if ((D_8011511E & 0x5000) != 0) {
                D_8011514C = 0;
            }
        }
        *(u16 *)&D_8011515C = D_80184BC4[D_80115128];  /* §18: sh under canonical u8 */
        if ((chg << 0x10) != 0) {
            func_80141C0C(1);
        }
    }
    return 0;
}



// @class: regalloc-order
// @stuck: none — MATCH (312/312, relocation-masked)










extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958();
extern int   func_80141100(int);
extern s16   func_8014168C(s16);
extern s32   func_8013FFD8(s16, s32, s32 *);
extern void func_80024054(void *a0, void *a1);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern int func_80137D08(int arg0, int arg1, short arg2);
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);


void func_8013FAF8(s16 arg0, s16 arg1) {

    extern s32    D_801151D0;
    extern u16    D_8011511A;
    extern Hw4    D_8011516A[];
    extern u8     D_80078EC0;
    extern Rec20  D_800AE7B8[];
    extern Blk60  D_8018460C[];
    extern Blk20  D_8018490C[];
    extern Prim4  D_80184A0C[];
    extern Prim4  D_80184A7C[];
    extern Prim4 *D_80184B70[];
    extern s32    D_80184B90[];
    extern u8 D_80184BB0;
    extern s16    D_80184F84;
    extern s16    D_80184F86;
    u8 sp18[72];
    s32 sp60[2];
    s32 *ot;
    s16 i;
    s16 j;
    s32 flag;
    s32 addr;
    Prim4 *p;
    s32 r;
    s32 t;
    s16 *pp;
    s32 flag2;
    register s32 flag3 __asm__("$18");

    func_80140E6C();
    func_80140F00();
    ot = func_80140958((s32 *)D_801151D0, arg0, arg1);
    if (D_8011511A < 6) {
        ot = (s32 *)func_80141100((int)ot);
    }
    for (i = arg0; i < arg1; i++) {
        if (i == D_8011511A || i == 2 || i == 4) {
            flag = 0;
        } else {
            flag = 0xFF;
        }
        p = &D_80184A0C[i];
        if (i != 5) {
            if (i == 2) {
                addr = ((s32 *)&D_80184BB0)[*(s16 *)&D_80115128];
            } else {
                addr = D_80184B90[i];
            }
        } else {
            addr = func_8013FFD8(2, func_8014168C(2), sp60);
        }
        func_80024054(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_80184B70[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && *(s16 *)&D_80115128 != 0) {
                p = D_80184A7C;
            }
            flag2 = flag;
            for (;;) {
                r = func_8013FFD8(i, j++, sp60);
                if (r == 0) {
                    break;
                }
                if (r < 0) {
                    func_80024054(r, sp18);
                    t = 1;
                    if (i == 0 && (D_80078EC0 & 0x7F) == j) {
                        t = 0xB6;
                    }
                    if (flag2 != 0) {
                        sp60[0] += -0x282828;
                    }
                    ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, t, sp60[0]);
                }
                p++;
            }
        }
        func_8005A600((s32)ot, 0, 0, 0x15, 0);
        flag3 = flag;
        *ot = 0x2000000;
        *ot = (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFFFFFF) | 0x2000000;
        D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] =
            (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);
        ot = func_800D29F8(flag3,
                           func_800D27DC(flag3 != 0, ot + 10, &D_8018460C[i], 8, D_8011516A[i].x),
                           &D_8018490C[i], 2, D_8011516A[i].x);
    }
    pp = &D_80184F84;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &D_800AE7B8[*(u16 *)&D_800B9A02], 2);
    }
    if (*pp != 0 && D_80184F86 != 0) {
        ot = func_8013AB54(ot, D_800AE7B8[*(u16 *)&D_800B9A02].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    D_801151D0 = (s32)ot;
}


extern u8 D_80184CC0[];


/* func_8013FFD8 — 213 ins, double jump-table, per-location family (134 members). */

extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);

extern short D_80115128;

s32 func_8013FFD8(s16 arg0, s32 arg1, s32 *arg2) {

    extern u8  D_80184CA8[];
    /* block decl dropped — file-scope array decl covers (§8e) */
    extern u8  D_80184CCC[];
    extern u8  D_80184CD3[];
    extern u8  D_80184CD4[];
    extern s32 D_80184BFC;
    extern s32 D_80184C14[];
    extern char *D_80184BD0;
    extern unsigned short D_80184BE4[];
    extern u8 D_80184C54;
    extern u8 D_80184C58;
    extern u8 *D_80184C64;
    extern s32 D_8010F3C4[];
    extern s32 D_8010EDE8[];
    extern u8  D_80115143;
    extern void * D_801C84F4;
    extern void * D_801C84F0;
    s32 ret;

    *arg2 = 0x808080;
    ret = 0;

    switch (arg0) {                                   /* jtbl_801D8898 */
    case 0: {
        s16 s0 = (s16) arg1;
        if (s0 < 6) {
            if ((((s32 (*)(u8))func_80029178)(D_80184CA8[s0]) & 0xFF) == 0) {
                return 1;
            }
            ret = ((s32 *)&D_80184BFC)[s0];
        }
        break;
    }
    case 1: {
        s16 v1 = (s16) arg1;
        if (v1 < 4) {
            ret = D_80184C14[v1];
        }
        break;
    }
    case 2:
        switch ((*(s16 *)&D_80115128)) {                         /* jtbl_801D88B8 */
        case 0: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80184BD0)[v1];
            }
            break;
        }
        case 1: {
            s16 v1 = (s16) arg1;
            if (v1 < 0xC) {
                s32 v3 = ((s32 (*)(u8, s32))func_800291B4)(((u8 *)&D_80184CC0)[v1], arg1) & 0xFF;
                if (v3 == 0) {
                    return 1;
                }
                ret = D_8010EDE8[v3 * 3];
            }
            break;
        }
        case 2: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))func_80029178)((*(u8 * *)&D_801C84F4)[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = (*(s32 * *)&D_801C84F0)[s0];
            }
            break;
        }
        case 3: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))func_80029178)(D_80184CCC[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = ((s32 *)D_80184BE4)[s0];
            }
            break;
        }
        case 4: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80184C64)[v1];
            }
            break;
        }
        }
        break;
    case 3: {
        s16 t = (s16) arg1;
        if (t <= 0) {
            s16 s0 = t + D_80115143;
            if (s0 != 0) {
                if ((((s32 (*)(u8, s32))func_800291B4)(D_80184CD3[s0], arg1) & 0xFF) == 0) {
                    *arg2 = 0x804040;
                }
                ret = D_8010F3C4[s0];
            } else {
                ret = (*(s32 *)&D_80184C54);
            }
        }
        break;
    }
    case 5: {
        s16 v1 = (s16) arg1;
        if (v1 < 3) {
            ret = ((s32 *)&D_80184C58)[v1];
        }
        break;
    }
    case 6: {
        s16 s0 = (s16) arg1;
        if (s0 < 0x28) {
            s32 idx;
            if ((((s32 (*)(u8, s32))func_800291B4)(D_80184CD4[s0], arg1) & 0xFF) == 0) {
                *arg2 = 0x804040;
            }
            idx = s0 + 1;
            ret = D_8010F3C4[idx];
        }
        break;
    }
    case 7: {
        s16 v1 = (s16) arg1;
        if (v1 < 5) {
            ret = ((s32 *)&D_80184C64)[v1];
        }
        break;
    }
    }
    return ret;
}

extern short D_80115128;
extern u8 D_80184CA8[];
extern u8 D_80184CC0[];
extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);




/* indexed data arrays (overlay) */


/* address-return symbols (main RAM) */

s32 func_8014032C(s32 param_1, s32 param_2) {
    extern int (*D_80184FF0[])(void);
    extern int (*D_80184FE0[])(void);
    extern void * D_80184CFC[];
    extern void * D_80184D2C[];
    extern void * D_80184D3C[];
    extern void * D_80184D14[];
    extern u8 D_80184CCC[];
    extern void * D_80184D54[];
    extern void * D_80184D6C[];
    extern void * D_80184D80[];
    extern u8 D_80184CD3[];
    extern u8 * D_801C84F4;
    extern u8 D_801117EC[];
    extern u8 D_801117B4[];
    extern u8 D_80112BC8[];
    extern u8 D_80112B58[];
    extern u8 D_80112BA8[];
    extern u8 D_80112B90[];


    int cVar1;
    unsigned int uVar3;
    void *result;

    result = D_801117EC;
    switch (((short)param_1)) {
    case 0:
        if (((s32(*)(s32))func_80029178)(D_80184CA8[((short)param_2)]) & 0xFF) {
            result = D_80184CFC[((short)param_2)];
        }
        break;
    case 1:
        result = D_80184D2C[((short)param_2)];
        break;
    case 2:
        switch ((*(s16*)&D_80115128)) {
        case 0:
            if (D_80184FF0[((short)param_2)]() == 0) {
                ((short)param_2) = 5;
            } else if (D_80184FE0[((short)param_2)]() != 0) {
                ((short)param_2) = 4;
            }
            result = D_80184D3C[((short)param_2)];
            break;
        case 1:
            goto case5;
        case 2:
            if (((s32(*)(s32))func_80029178)(D_801C84F4[((short)param_2)]) & 0xFF) {
                if (((short)param_2) == 5 && (((s32(*)(s32))func_80029178)(0x1C) & 0xFF)) {
                    result = D_801117B4;
                } else {
                    result = D_80184D14[((short)param_2)];
                }
            }
            break;
        case 3:
            if (((s32(*)(s32))func_80029178)(D_80184CCC[((short)param_2)]) & 0xFF) {
                result = D_80184D54[((short)param_2)];
            }
            break;
        case 4:
            result = D_80184D6C[((short)param_2)];
            break;
        }
        break;
    case 5:
    case5:
        uVar3 = ((s32(*)(s32))func_800291B4)(D_80184CC0[((short)param_2)]) & 0xFF;
        if (uVar3 != 0) {
            result = D_80184D80[uVar3];
        }
        break;
    case 3:
        if (((short)param_2) != 0) {
            cVar1 = ((s32(*)(s32))func_800291B4)(D_80184CD3[((short)param_2)]) & 0xFF;
            if (cVar1 == 0) {
                result = D_80112B58;
            } else {
                result = D_80112BA8;
                if (cVar1 == 1) {
                    result = D_80112B90;
                }
            }
        } else {
            result = D_80112BC8;
        }
        break;
    case 6:
    case 7:
    default:
        result = 0;
        break;
    }
    return result;
}


extern u8 D_80115148[];
extern u16 D_8011511E;
extern u8 D_80062BDC;

extern s32 func_80028D58(void);
extern void func_80028D78(s32 a0);
extern void func_80019064(void *a0);
extern s32 func_80028DE0(void);
extern void func_80028E00(s32 a0);
extern s32 func_80028FBC(void);
extern void func_80028FDC(s32 a0);
extern s32 func_80029000(void);
extern void func_80029020(s32 a0);
extern s32 func_80028D9C(void);
extern void func_80028DBC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80140608(s32 a0) {
    s16 t;
    register s32 iVar2 __asm__("$2");
    register s32 zr __asm__("$0");
    s32 uVar3;
    u32 uVar4;
    s32 uVar5 = 1;

    switch (D_80115148[(s16)a0 * 2]) {
    case 0:
        t = func_80028D58() ^ 1;
        func_80028D78(t);
        if (t != 0) {
            return uVar5;
        }
        func_80019064(&D_80062BDC);
        return uVar5;
    case 1:
        func_80028E00((s16)(func_80028DE0() ^ 1));
        return uVar5;
    case 2:
        iVar2 = func_80028FBC();
        if (D_8011511E & 0x8000) {
            iVar2 = iVar2 - 1;
            uVar4 = iVar2 + zr;
            if ((s16)iVar2 < 0) {
                uVar4 = 0;
                uVar5 = 0;
            }
        } else {
            iVar2 = iVar2 + 1;
            uVar4 = iVar2 + zr;
            if ((s16)iVar2 >= 8) {
                uVar4 = 7;
                uVar5 = 0;
            }
        }
        func_80028FDC((s16)uVar4);
        func_8002D4C8(0x21, uVar4 & 0xFFFF);
        goto ret;
    case 3:
        iVar2 = func_80029000();
        if (D_8011511E & 0x8000) {
            iVar2 = iVar2 - 1;
            uVar4 = iVar2 + zr;
            if ((s16)iVar2 < 0) {
                uVar4 = 0;
                uVar5 = 0;
            }
        } else {
            iVar2 = iVar2 + 1;
            uVar4 = iVar2 + zr;
            if ((s16)iVar2 >= 8) {
                uVar4 = 7;
                uVar5 = 0;
            }
        }
        func_80029020((s16)uVar4);
        func_8002D4C8(0x22, uVar4 & 0xFFFF);
        goto ret;
    case 4:
        t = func_80028D9C() ^ 1;
        func_80028DBC(t);
        uVar3 = 0xB;
        if (t == 0) {
            uVar3 = 0xC;
        }
        func_8002D4C8(uVar3, 0);
        goto ret;
    default:
        goto ret;
    }
ret:
    return uVar5;
}



// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).


extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

void func_801407F4(void)
{

    extern u8 *D_80184C64;
    extern u8 *D_80184C68;
    extern u8 *D_80184C6C;
    extern u8 *D_80184C70;
    extern u8 *D_80184C74;
    extern u16 *D_80184C78[];
    extern u16 *D_80184C80[];
    extern u16 *D_80184CA0[];
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_80184C64;
    iVar2 = func_80028D58();
    puVar3 = D_80184C78[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_80184C68;
    iVar2 = func_80028DE0();
    puVar3 = D_80184C78[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_80184C6C + 0x18) = *D_80184C80[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_80184C70 + 0x18) = *D_80184C80[iVar2];

    puVar1 = D_80184C74;
    iVar2 = func_80028D9C();
    puVar3 = D_80184CA0[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}





















extern s16 func_8014168C(s16);
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
/* func_80140958 -- MATCH (260 ins), verified by
 *   python3 tools/match_one.py func_80140958 --c .run/near6/wave23/func_80140958.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077
 *
 * Three levers took the seed from 6 -> 0 (see the numbered notes in the inner block):
 *   [L1] `m == i` (not `m == 3`)  -- keeps b[0] a RUNTIME value; `m == 3` let gcc
 *        const-fold it and materialise `li a3,3` / `li t3,12` instead of
 *        `addu a3,v1,zero` / `sll t3,v1,2`.
 *   [L2] one dead `__asm__ volatile("" :: "r"(j))` -- +1 weighted REG_N_REFS on j so
 *        global.c:594 allocno_compare ranks j above k (j -> $a2, k -> $a3).
 *   [L3] `t3v = m * 4` as an EXPLICIT preheader statement (instead of letting loop.c
 *        hoist D_8011516A[m]'s index) -- gives it a LUID *below* the three constant
 *        assignments, which is what puts `move a3,v1 / sll t3,v1,2` ahead of them in
 *        sched1's backward LUID tie-break.
 */
s32 *func_80140958(ot, i, n)
s32 *ot;
s16 i;
s16 n;
{

    extern short D_800B9A02;
    extern u16 D_80115110;
    extern u8 D_80115140[];
    extern s16 D_8011514E;
    extern u8 D_80115158[];
    extern Hw4 D_8011516A[];
    extern Prim4 D_80184A7C[];
    extern Prim4 *D_80184B70[];
    extern u8 D_80115143;
    extern Prim4 D_80184A2C[];
    extern s16 D_80184F8C[];
    extern s16 D_80184F9C[];
    extern u16 D_80184AAC;
    extern u16 D_80184AAE;
  extern Env_80140958 D_800AE7BC[];
  Prim4 *p;
  s16 t;
  s32 c3;
register u16 *a __asm__("$20");
register u16 *b __asm__("$21");
register u16 *c __asm__("$23");
register u16 *e __asm__("$22");
register u16 *pb __asm__("$10");
register u32 m24 __asm__("$8");
register u32 mhi __asm__("$9");
register s32 eight __asm__("$2");
  if (i < n)
  {
    c3 = 3;
    a = &D_80115110;
    b = a + 5;
    c = a + 3;
    e = &D_80184AAE;
    do
    {
      if (((a[0] == 0) && (a[1] != c3)) && (a[1] < 6))
      {
        if (i == a[5])
        {
          ot = func_80140D68(ot, &D_80184A2C[i], i, D_80184F8C[a[3] & 7], 0);
        }
      }
      else
      {
        p = D_80184B70[i];
        if (((p != 0) && (i == b[0])) && (i != 6))
        {
          if ((i == 2) && ((*((s16 *) (b + 7))) != 0))
          {
            p = D_80184A7C;
          }
          if (i != c3)
          {
            t = ((s32 (*)(s16)) func_8014168C)(i) * 2;
          }
          else
          {
            t = ((*((u8 *) (&D_8011514E))) - D_80115143) * 2;
          }
          ot = func_80140D68(ot, p, i, D_80184F9C[c[0] & 7], t);
          if (((i == 2) && ((*((s16 *) (c + 9))) == 1)) && ((*((s16 *) (c + 12))) != 0))
          {
            ot = func_80140D68(ot, p, 2, 8, ((*((s16 *) (c + 12))) & 0xF) * 2);
          }
        }
      }
      if (i == c3)
      {
        s32 m = b[0];
        /* [L1] compare against `i`, NOT against the literal 3. */
        if ((m == i) && ((b[-2] & 8) != 0))
        {
          s16 j;
          s32 k;
          s32 t3v;
          u8 *q = ((u8 *) ot) + 0x14;
          s16 y;
          j = 0;
          k = m;
          t3v = m * 4;                  /* [L3] explicit, must sit before the 3 constants */
          pb = (u16 *) (&D_800B9A02);
          m24 = 0xFFFFFF;
          mhi = 0xFF000000;
          for (; j < 2; j++)
          {
            if (j == 0)
            {
              if (D_80115140[k] == 0)
              {
                continue;
              }
              q[-7] = 0x30;
              y = (*e) - 4;
            }
            else
            {
              s32 k2 = k * 2;
              if ((((s8 *) D_80115158)[k2] - ((s8 *) D_80115140)[k]) < 2)
              {
                continue;
              }
              q[-7] = 0x38;
              y = (*e) + 3;
            }
            *((s16 *) (q - 10)) = y;
__asm__("" ::: "memory");
            *((u32 *) ot) = 0x4000000;
            q[-8] = 0x78;
            *((u32 *) (q - 0x10)) = 0x64808080;
            *((s16 *) (q - 6)) = 0x4056;
            *((s16 *) (q - 0xC)) = (D_80184AAC + ((u16) *((u16 *) (((u8 *) D_8011516A) + t3v)))) + 0x4A;
            eight = 8;
            *((s16 *) (q - 2)) = eight;
            *((s16 *) (q - 4)) = eight;
            *((u32 *) ot) = ((*((u32 *) ot)) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
            {
register u32 *op __asm__("$4");
              op = D_800AE7BC[*pb].ot;
              op[2] = (op[2] & mhi) | (((u32) ot) & m24);
            }
            q += 0x14;
            ot += 5;
            __asm__ volatile("" :: "r"(j));   /* [L2] zero code, +1 ref on j */
          }

        }
      }
      i = i + 1;
    }
    while (i < n);
  }
  return ot;
}





s32 *func_80140D68(out, src, idx, dx, ofs)
    s32 *out;
    Prim4 *src;   /* conformed to the fleet prototype; used only as (s32)src */
    s16  idx;
    s32  dx;
    s16  ofs;
{

    extern Hw4 D_8011516A[];
    extern short D_800B9A02;
    /* §94 TYPE-CARRY: this typedef and its extern MUST be BLOCK-scope. extract_unit carries
       file-scope externs and #defines into each remapped sibling (Phase-27 _carry_macros) but
       NOT file-scope typedefs — so a file-scope Env_800D29F8 is silently dropped from every
       sibling and the family sweeps 0/137. Body-local typedefs DO survive (PTag_80140D68 below
       is the proof), so it lives here. */
         /* 0x14 stride */
    extern Env_800D29F8 D_800AE7BC[];


    register u32 mhi __asm__("$8");
    s16 *q;
    s32  a;

    out[0] = 0x04000000;
    *((u8 *)out + 0xC) = 0x70;
    *((u8 *)out + 0xD) = 0x10;
    mhi = 0x64808080;
    out[1] = mhi;
    *(u16 *)((u8 *)out + 0xE) = 0x4056;

    dx -= 0xD;
    q = (s16 *)(ofs * 2 + (s32)src);
    a = (u16)q[0] + (u16)D_8011516A[idx].x;
    a += dx;
    *(s16 *)((u8 *)out + 0x8) = a;
    *(s16 *)((u8 *)out + 0xA) = q[1] - 4;
    *(s16 *)((u8 *)out + 0x12) = 0x10;
    *(s16 *)((u8 *)out + 0x10) = 0x10;

    ((PTag_80140D68 *)out)->addr = ((PTag_80140D68 *)((D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot) + 2))->addr;
    ((PTag_80140D68 *)((D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot) + 2))->addr = (u32)out;

    return out + 5;
}




// @class: struct
// @stuck: none — MATCH


extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {

    extern unsigned char D_80078E7F;
    extern unsigned char D_80078E7E;
    extern unsigned char D_80078E7D;
    extern M2C_UNK D_80184BA0;
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_80184BA0);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)


extern int func_80029FE4(void);
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern char *func_8002AAB4(void);
extern char *strcpy(char *, const char *);
extern int func_8002A26C(void);
extern int func_8002A2B0(void);
extern int func_8002A4B8(void);
extern s32 func_8002A4FC(s32 a0);
extern int func_8002A998(void);
extern int func_8002A9DC(void);
extern int func_8002A728(void);
extern int func_8002A76C(void);
extern int func_80029FD4(void);

void func_80140F00(void) {

    extern short D_80115128;
    extern u8 D_80184BB0;
    extern char *D_80184BD0;
    extern char *D_80184BD4;
    extern char *D_80184BD8;
    extern char *D_80184BDC;
    extern char *D_80184BE0;
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_80184BB0);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_80184BD0;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BD4;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BD8;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BDC;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BE0;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}




// @class: other
// @stuck: none — MATCH


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

int func_80141100(int param_1)
{

    extern short D_80115128;
    extern unsigned short D_80115172;
    extern unsigned short D_80184A6A;
    extern unsigned short D_80184A6E;
    extern unsigned short D_80184A72;
    extern unsigned short D_80184A76;
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_80184A6A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A6E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A72;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A76;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


#define addPrim_1412A8(ot, p) (setaddr_1412A8(p, getaddr_1412A8(ot)), setaddr_1412A8(ot, p))
/* §37/§124 def-side asm-label alias (the S40 class lever). The TU declares
 *   extern int func_801412A8(int, int, int, int, int, int);            (ov_SC01_077.c:2720)
 * and its callers USE the return value (`param_1 = func_801412A8(...)`, :2730-:2736), while the
 * byte-true definition is `Prim_1412A8 *(Prim_1412A8 *, int, int, int, u16, u16)`. The u16 params
 * cannot agree with an `int` prototype (C default argument promotion) and the `()` no-prototype
 * escape is illegal precisely when a param promotes -- so NEITHER side can move. Giving the
 * DEFINITION a private C identifier bound to the emitted symbol by a GNU asm label decouples
 * them: the TU's declaration continues to govern the CALL SITES (their codegen is untouched --
 * which is what match_one could not see, since it only compiles this function), and the
 * definition keeps its byte-true signature. Zero blast radius. */
DEFINE_func_801412A8()  /* dedup: shared engine-core @0x801412A8 (src/shared) */


DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415c0 (src/shared) */


DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168c (src/shared) */


DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416d4 (src/shared) */




void func_80141788(void)
{

    extern unsigned short D_80115112;
    extern void (*D_80185000[])(void);
    D_80185000[D_80115112]();
}


DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417c4 (src/shared) */


DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417f8 (src/shared) */



extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);


void func_80141874(void) {

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018500C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018500C[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}



// @class: loose-typing
// @stuck: none — MATCH (90 ins). Key levers:
//   (1) D_8011511A must be a DIRECT volatile global (block-scope `extern volatile unsigned short`),
//       NOT `*(volatile u16*)&D_8011511A`. Volatile forces the store-2-then-read-back reload (else
//       gcc folds 2>=4 and drops the branch); direct-global access recomputes %hi/%lo per reference
//       (3 fresh lui) whereas the `&`-cast pointer form CSEs the address into ONE register (2 ins short).
//   (2) Reconcile with the TU/engine_core canonical types: D_80115158 is `u8[]` (decays -> `*(u16*)D_80115158`),
//       D_8011515C is `u8` (halfword store -> `*(u16*)&D_8011515C`), func_80029178 is `s32(s32)`. Do not
//       redeclare these — the shared DEFINE macros already provide them (conflicting-types hard error).

extern void func_800D24A0(int);
extern void func_8002D4C8(int, int);
extern void func_80141C0C(int);

s32 func_801418F8(void) {

    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern unsigned short D_80115118;
    extern short D_80115128;
    extern s32 D_80115130;
    extern u8 D_80115158[];
    extern u8 D_8011515C;
    extern s16 D_80184F84;
    extern s16 D_80184F86;
    extern u16 D_8011515A;
    extern u16 D_8011515E;
    extern u16 D_80115162;
    extern u16 D_80115166;
    extern u16 D_8011512E;
    extern void *D_801C84F0;
    extern void *D_801C84F4;
    extern u8 D_80184C24;
    extern u8 D_80184C3C;
    extern u8 D_80184CB0;
    extern u8 D_80184CB8;
    extern volatile unsigned short D_8011511A;
    extern s32 func_80029178(s32);
    unsigned short t;

    func_800D24A0(1);
    D_8011511A = 2;
    t = D_8011511A;
    D_80115118 = 0;
    D_80115130 = 0;
    if (t >= 4) {
        D_8011511A = t - 3;
    }
    *(u16*)D_80115158 = 0x106;
    if ((func_80029178(0x1C) & 0xFF) == 0) {
        D_801C84F0 = &D_80184C24;
        D_801C84F4 = &D_80184CB0;
    } else {
        D_801C84F0 = &D_80184C3C;
        D_801C84F4 = &D_80184CB8;
    }
    D_8011515A = 0x104;
    *(u16*)&D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;
    if (D_80115110 == 3) {
        func_8002D4C8(0x46E, 0);
    } else {
        func_80141C0C(0);
    }
    D_80115128 = 1;
    D_80184F84 = 0xE;
    D_80184F86 = 3;
    D_80115112 += 1;
}


extern s32 func_800D0EC4(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern void func_80139954(void);
extern s32 func_8013F350(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern s32 func_8014032C(s32 a0, s32 a1);

// @class: plumbing
// @stuck: TBD — first pass



s32 func_80141A60()
{

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern u16 D_8011511A;
    extern s32 D_80115130;
    extern s16 D_8011514C;
    extern u8 D_8011515C;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern unsigned char D_80184F88;
    int v;
    s32 frame_pad[2];
    (void)&frame_pad;

    D_801151D0 = ((int *)D_801151C8)[(*(unsigned short *)&D_800B9A02)];
    func_8013F350();
    if ((*(unsigned short *)&D_8011511A) >= 4) {
        func_8013FAF8((short)(*(unsigned short *)&D_8011511A), (short)((*(unsigned short *)&D_8011511A) + 1));
    }
    func_8013FAF8(2, 3);
    v = ((int(*)(int, int))func_8014032C)(2, (short)((*(unsigned char *)&D_8011514C) + (*(unsigned char *)&D_8011514D) * (*(unsigned char *)&D_8011515C)));
    if (v != 0 && v != D_80115130) {
        D_80115130 = v;
        func_80139954();
        ((void (*)(int, void *))func_801376E8)(v, &(*(int *)&D_80184F88));
    }
    func_80137B80();
    if (func_800D0EC4() != 0) {
        (*(unsigned short *)&D_80115116) = 0xFFF8;
        (*(unsigned short *)&D_80115112) = (*(unsigned short *)&D_80115112) + 1;
    }
}


DEFINE_func_80141B90()  /* dedup: shared engine-core @0x80141b90 (src/shared) */


void func_80141C04(void) {
}

extern u16 D_80115110;
extern u16 D_80184F60[];

void func_80141C0C(s32 a0)
{
    s32 index = ((a0 << 16) >> 15) + D_80115110;
    u16 value = D_80184F60[index];
    func_8002D4C8(value, 0);
}


DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141c50 (src/shared) */


DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141ca4 (src/shared) */


DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */


DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */



// @class: struct
// @stuck: none — MATCH (58 ins). STRUCT branch reconstruction + 3 levers: (1) §3-T4 branch-polarity
//   invert in the ==0 arm so the func_8012C218 cold path sinks to the tail; (2) *(volatile int*) on
//   the two extra param_1[0x32] reloads to defeat gcc CSE (gcc reloads via register reuse, not a store);
//   (3) param_1[0x7e] pinned to $v1 (register __asm__("$3")) + an input-only scheduling barrier
//   __asm__ __volatile__("" : : "r"(a)) on the 0xA read so the pinned load is anchored AFTER it in the
//   ==0 arm (matches the load2-reused-as-$v1 ordering).

extern void func_8012C218(void *a0);

void func_801424E4(short *param_1) {

    extern void (*D_80185030[])(void);
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_80185030[(unsigned short)param_1[1]])();
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x38] != 0) {
            iVar2 = *(int *)(param_1 + 0x32);
            if (iVar2 == 0) {
                return;
            }
            *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
            t = (unsigned short)param_1[0x7e];
            sVar1 = *(unsigned short *)(iVar2 + 10) + t;
            param_1[5] = sVar1;
            *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
        } else {
            unsigned short a;
            iVar2 = *(int *)(param_1 + 0x32);
            if ((iVar2 != 0) && (*(short *)(iVar2 + 0x36) == param_1[0x7f])) {
                *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
                a = *(unsigned short *)(*(volatile int *)(param_1 + 0x32) + 10);
                __asm__ __volatile__("" : : "r"(a));
                t = (unsigned short)param_1[0x7e];
                sVar1 = a + t;
                iVar2 = *(volatile int *)(param_1 + 0x32);
                param_1[5] = sVar1;
                *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
                return;
            }
            ((void (*)(short *))func_8012C218)(param_1);
        }
    }
    return;
}




void func_801425CC(void *a0) {

    extern void (*D_80185040[])(void);
    D_80185040[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);

void func_80142608(s32 param_1)
{

    extern s32 D_80185024;
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_80185024);
        *(short *)(iVar1 + 0x1a) = 0x200;
        *(short *)(iVar1 + 0x18) = 0x200;
        *(short *)(param_1 + 0xfc) = 0x40;
        if (*(short *)(param_1 + 0x70) != 0) {
            goto ad50;
        }
        if (*(s32 *)(param_1 + 100) != 0) {
            *(short *)(param_1 + 0xfe) = *(short *)(*(s32 *)(param_1 + 100) + 0x36);
            goto ad50;
        }
    }
    ((void (*)(s32))func_8012CAE4)(param_1);
    return;
ad50:
    *(short *)(param_1 + 0x98) = 0;
    *(s32 *)(param_1 + 0x90) = 0;
    ((void (*)(s32))func_8012AD50)(param_1);
}


DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426d4 (src/shared) */


DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */


DEFINE_func_80142778()  /* dedup: shared engine-core @0x80142778 (src/shared) */


void func_801427DC(void) {
}

void func_801427E4(void) {
}


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801427EC(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185054[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185054[*(u16 *)(param_1 + 2)]();
    }
}


DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */


DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428cc (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_8014292C(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185070[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185070[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_80142978(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185240[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185240[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801429C4(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_801852F8[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_801852F8[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)
// @reconcile: func_80142A80 is DEFINED later in this TU as `void func_80142A80(void)`.
//   The uc2 draft declared it `extern void func_80142A80(int)` -> conflicting types.
//   Escape §17a-1/§20: conform the declaration to the TU's, cast at the use site
//   (codegen-neutral: the argument still lands in $a0).

extern void func_80142A80(void);

void func_80142A10(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185308[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185308[*(u16 *)(param_1 + 2)]();
        if (*(s16 *)(param_1 + 0xFC) != 0) {
            ((void (*)(int))func_80142A80)(param_1);
        }
    }
}




// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)


void func_80142A80(void)
{

    extern u16 D_800B99D8;
    extern struct packed_word D_801C7B90;
    extern u8 D_801C84F8;
    extern u8 D_801C84F9;
    extern u8 D_801C84FA;
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801C7B90;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801C84F8 = mul * (local.b[0] >> 4);
    D_801C84F9 = mul * (local.b[1] >> 4);
    D_801C84FA = mul * (local.b[2] >> 4);
}


DEFINE_func_80142B2C()  /* dedup: shared engine-core @0x80142B2C (src/shared) */


void func_801439C0(u8 *a0);
void func_8012AD44(s32 *a0, s16 a1);
void func_8012C218(void *a0);
void func_8012C098(void *param_1);

void func_80142BB4(s32* param_1, s32 param_2, s32 param_3)
{
  if (*(short *)((char *)param_1 + 0xfc) == 1) {
    if ((param_2 != 0) || (*(short *)((char *)param_1 + 0x100) == 0)) {
      *(unsigned short *)((char *)param_1 + 0x5c) =
        *(unsigned short *)((char *)param_1 + 0x5c) & 0xfefe;
      *(unsigned int *)(*(int *)((char *)param_1 + 0x20) + 4) =
        *(unsigned int *)(*(int *)((char *)param_1 + 0x20) + 4) | 0x80000000;
      func_801439C0((u8 *)*(int *)((char *)param_1 + 0xcc));
      func_8012AD44((s32 *)param_1, param_3);
    }
  }
  else if ((param_2 != 0) || (*(short *)((char *)param_1 + 0x100) == 0)) {
    func_8012C218(param_1);
  }
  else {
    func_8012C098(param_1);
  }
}


void func_80142C7C(void) {
}

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142c84 (src/shared) */


DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142c9c (src/shared) */


DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142d38 (src/shared) */


DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142db8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);


void func_80142DC4(int param_1)
{

    extern int D_80185048;
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_80185048);
        *(short *)(v0 + 0x1a) = 0x1800;
        *(short *)(v0 + 0x18) = 0x1800;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);


void func_80142E38(int param_1)
{

    extern unsigned char D_80185064[];
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_80185064);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0x1200;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


void func_80142EC0(s32 param_1) {

    extern s32 D_80185230[];
    register s32 d   __asm__("$16") = param_1;   /* $s0 */
    register s32 obj __asm__("$17");             /* $s1 */
    s32 ret;
    s16 sVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
    } else {
        func_8001CA1C(obj, 0);
        sVar2 = (s16)((*(u16 *)(d + 0x70) & 0xf) * 0x600 + 0xc00);
        *(s16 *)(obj + 0x1a) = sVar2;
        *(s16 *)(obj + 0x18) = sVar2;
        *(s16 *)(d + 0xfc) = 0;
        ((void (*)(s32, s32))func_8012A828)(d, D_80185230[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}


DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142f68 (src/shared) */


DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142ffc (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


void func_8014305C(int param_1)
{

    extern unsigned char D_80185250[];
    extern unsigned char D_801852B0[];
    register int s0_param __asm__("$16") = param_1;
    register int s1_copy __asm__("$17");
    int iVar2;
    short sVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(s0_param + 0x20) = iVar2;
    s1_copy = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(s0_param);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_80185250);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_801852B0);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430f4 (src/shared) */


DEFINE_func_80143188()  /* dedup: shared engine-core @0x80143188 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (memcpy unaligned copy; $s0 survivor pinned, store-before-copy keeps $v0 for early store/branch)

extern void *memcpy(void *, const void *, u32);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80142B2C(void *arg0);


void func_801431E8(s32 param_1) {

    extern u8 D_801C7B8C;
    extern u8 D_801C84F8;
    extern u8 D_801C84FC;
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801C7B8C, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801C84F8);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801C84F8, 0x10);
            memcpy(&D_801C84FC, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432fc (src/shared) */


DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */


DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433f0 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{

    extern u8 D_800D387C[];
    extern u32 D_80185408[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_80185408[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_8014350C()  /* dedup: shared engine-core @0x8014350c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8014358C(s32 param_1)
{

    extern u8 D_80185418[];
    extern u32 D_80185514[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_80185418;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x90;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_80185514[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */


DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437d8 (src/shared) */


DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */


DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */


DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439c0 (src/shared) */


DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439fc (src/shared) */




void func_80143B30(void *a0) {

    extern void (*D_80185530[])(void);
    D_80185530[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143b6c (src/shared) */


DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143bdc (src/shared) */




void func_80143C38(void *a0) {

    extern void (*D_8018553C[])(void);
    D_8018553C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143c74 (src/shared) */




void func_80143C98(void *a0) {

    extern void (*D_80185544[])(void);
    D_80185544[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143cd4 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (80 ins, relocation-masked). iVar2/iVar3 pinned $s1/$s2; sVar4 is an
//   int set BEFORE the call so it naturally takes callee-saved $s3; chained assignment
//   a=b=c=sVar4 materializes the value once (the addu $v0,$s3,$zero move) + delay-slot store.

     /* size 0x0c */

extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80143D28(s32 param_1) {

    extern MatEntry D_80185568[];
    register s32 iVar3 __asm__("$18") = *(s32 *)(param_1 + 0x20); /* $s2 */
    register s32 iVar2 __asm__("$17") = *(s32 *)(param_1 + 0x64); /* $s1 */
    MatEntry *p = &D_80185568[*(s16 *)(param_1 + 0x70)];
    s32 sVar4;
    s32 iVar1;

    *(s16 *)(iVar3 + 0x14) = p->f8;
    *(u16 *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + p->fa;
    sVar4 = 0x1000;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)(*(s32 *)(param_1 + 0x20) + 0x34), p, (void *)(param_1 + 0x50));

    if (*(s16 *)(param_1 + 0xfe) == 0 &&
        (iVar2 == 0 || *(s16 *)(iVar2 + 0x36) != *(s16 *)(param_1 + 0xfc) ||
         *(u8 *)(iVar2 + 0xc1) != 6)) {
        if (0x10 < *(s32 *)(param_1 + 0x1c)) {
            *(s32 *)(param_1 + 0x1c) = 0x10;
        }
        *(s16 *)(param_1 + 0xfe) = 1;
    }

    iVar1 = *(s32 *)(param_1 + 0x1c);
    if (iVar1 < 0x11) {
        sVar4 = iVar1 << 8;
    }
    if (0x73 < iVar1) {
        sVar4 = (0x78 - iVar1) << 10;
    }
    *(s16 *)(iVar3 + 0x18) = *(s16 *)(iVar3 + 0x1a) = *(s16 *)(iVar3 + 0x1c) = sVar4;

    if (func_8012BEE8(param_1)) {
        func_8012C218((void *)param_1);
    }
}




void func_80143E68(void *a0) {

    extern void (*D_8018558C[])(void);
    D_8018558C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80143EA4(void) {
}

void func_80143EAC(void) {
}

void func_80143EB4(void) {
}

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143ebc (src/shared) */




void func_80144054(void *a0) {

    extern void (*D_801855A0[])(void);
    D_801855A0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @stuck: 154/154 ins structural match (callees/consts/ctrl-flow/stack/GPU-packet all byte-correct); residual 25 = caller-saved temp-reg coalescing in the final ring-vertex block (target reuses dead $s0=iVar3 for iVar3-(iVar4>>6) subu where gcc reuses iVar4>>6's reg; iVar4 mflo -> $a3 vs target $v0) + 2-ins schedule swap of giv-increment vs iVar2*4 -> permuter grinder territory (§27 step-5)

 /* 0x14 stride */

extern void *func_80010A08(s32);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 AddPrim(s32, void *);

void func_80144090(s32 param_1) {

    extern OtBlk aD800A651C_80144090[] __asm__("D_800A651C");
    extern u8 D_800AF648;
    extern short aD800B9A02_80144090 __asm__("D_800B9A02");
    void *iVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s32 iVar5;
    s32 iVar6;
    struct {
        s16 v10[4];
        u16 sxy[2];
        s32 p;
        s32 flag;
    } L;

    iVar1 = func_80010A08(0x140);
    if (iVar1 != 0) {
        *(s32 *)(param_1 + 4) = *(s32 *)(param_1 + 4) + *(s32 *)(param_1 + 0x10);
        *(s32 *)(param_1 + 8) = *(s32 *)(param_1 + 8) + *(s32 *)(param_1 + 0x14);
        *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)(param_1 + 0x18);
        L.v10[0] = *(u16 *)(param_1 + 6);
        L.v10[1] = *(u16 *)(param_1 + 0xa);
        L.v10[2] = *(u16 *)(param_1 + 0xe);
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648);
        iVar2 = RotTransPers((s32)L.v10, (s32)L.sxy, &L.p, &L.flag);
        iVar2 = iVar2 + 4;
        if (iVar2 < 0) {
            iVar2 = 0;
        }
        iVar6 = 0;
        do {
            *(s32 *)((u8 *)iVar1 + 4) = 0xffffff;
            *(u8 *)((u8 *)iVar1 + 3) = 4;
            *(u8 *)((u8 *)iVar1 + 7) = 0x20;
            if (*(s32 *)(param_1 + 0x1c) - 6 < 1) {
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0];
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1];
            } else {
                iVar5 = func_8004787C(iVar6);
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
                iVar5 = func_80047948(iVar6);
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
            }
            iVar3 = func_8004787C(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar4 = func_80047948(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar6 = iVar6 + 0x100;
            *(s16 *)((u8 *)iVar1 + 0x10) = L.sxy[0] + ((iVar3 + (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0x12) = L.sxy[1] + ((iVar4 + (iVar3 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xc) = L.sxy[0] + ((iVar3 - (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xe) = L.sxy[1] + ((iVar4 - (iVar3 >> 6)) >> 0xc);
            AddPrim(aD800A651C_80144090[(u16)aD800B9A02_80144090].a + (iVar2 * 4), iVar1);
            iVar1 = (u8 *)iVar1 + 0x14;
        } while (iVar6 < 0x1000);
    }
}


extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)


void func_801442F8(int param_1)
{

    extern void (*D_801855A8[])();
    int iVar1;

    D_801855A8[*(u16 *)(param_1 + 2)]();
    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (0x1d < iVar1) {
        func_8012C218(param_1);
    }
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

void func_80144364(int param_1) {

    extern u8 D_80185524;
    int iVar3;
    u16 uVar2;
    s16 sVar1;

    iVar3 = ((s32 (*)(void))func_8012C194)();
    if (iVar3 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        uVar2 = *(u16 *)(*(int *)(param_1 + 0x64) + 0x36);
        *(int *)(param_1 + 0xCC) = iVar3;
        *(u16 *)(param_1 + 0xFC) = uVar2;
        func_8001CB6C((u8 *)iVar3, (s32)&D_80185524, 0x250, 0x1A0);
        *(s32 *)(iVar3 + 4) = 0x60000000;
        *(u8 *)(iVar3 + 0x27) = 0x14;
        *(u16 *)(iVar3 + 0x10) = 0x400;
        *(u16 *)(iVar3 + 8) = *(u16 *)(*(int *)(param_1 + 0x64) + 6);
        *(u16 *)(iVar3 + 0xA) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xA);
        *(u16 *)(iVar3 + 0xC) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xE);
        sVar1 = *(s16 *)(param_1 + 0x70);
        if (sVar1 != 0) {
            *(s16 *)(iVar3 + 0x1A) = sVar1;
            *(s16 *)(iVar3 + 0x18) = sVar1;
        } else {
            *(u16 *)(iVar3 + 0x1A) = 0x2000;
            *(u16 *)(iVar3 + 0x18) = 0x2000;
        }
        *(u16 *)(param_1 + 2) = 1;
    }
}



extern void func_80016714(void *a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80144458(void *arg0) {

    extern s32 D_80185538;
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s2 = M2C_FIELD(arg0, void **, 0xCC);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_s0 = (M2C_FIELD(temp_v0, s16 *, 0x12) - 0x400) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (func_80047948(temp_s0) * D_80185538 * 0x10);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (func_8004787C(temp_s0) * -D_80185538 * 0x10);
            func_8012AD80(arg0);
        }
    }
    M2C_FIELD(temp_s2, u16 *, 8) = (u16) M2C_FIELD(arg0, u16 *, 6);
    M2C_FIELD(temp_s2, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(temp_s2, u16 *, 0xC) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    if (func_80128ED8(temp_s2, arg0 + 0xD0) != 0) {
        func_80016714(temp_s2, 0x38);
        func_8012C218(arg0);
    }
}


DEFINE_func_80144558()  /* dedup: shared engine-core @0x80144558 (src/shared) */


DEFINE_func_8014462C()  /* dedup: shared engine-core @0x8014462c (src/shared) */


DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446a4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8014477C(void *param_1) {

    extern u8 D_8018554C;
    extern u8 D_80185558;
    s32 v0;
    s32 v1;
    register s32 uVar2 __asm__("$2");
    register s32 addr __asm__("$3");
    s32 gv;
    s32 fv;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_8018554C);
    if (*(u16 *)(*(s32 *)((s32)param_1 + 0x64)) != 0) {
        *(s16 *)((s32)param_1 + 0xFC) = *(u16 *)(*(s32 *)((s32)param_1 + 0x64) + 0x36);
        uVar2 = *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58);
        if (uVar2 != 0) {
            addr = uVar2 & 0xFFFFFFF;
            gv = *(u16 *)((addr | 0x80000000) + 8);
            fv = *(u16 *)((s32)param_1 + 0xA) - 0x30;
            *(u16 *)((s32)param_1 + 0xA) = gv + fv;
        } else {
            *(u16 *)((s32)param_1 + 0xA) = *(u16 *)((s32)param_1 + 0xA) - 0x60;
        }
    }
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_80185558);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);


void func_80144880(s32 param_1)
{

    extern u8 D_80185524;
    extern u8 D_80185594;
    register s32 obj  __asm__("$16");   /* $s0 */
    register s32 self __asm__("$17") = param_1;  /* $s1 */
    register s32 b    __asm__("$2");    /* $v0 */
    s32 e;

    obj = ((s32 (*)(void))func_8012C194)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(self);
    } else {
        *(u16 *)(self + 0xFC) = *(u16 *)(*(s32 *)(self + 0x64) + 0x36);
        *(s32 *)(self + 0xCC) = obj;
        if (*(s16 *)(self + 0x70) == 1) {
            func_8001CB6C((u8 *)obj, (s32)&D_80185524, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_80185594, 0x300, 0x1D0);
            b = 0x6A;
        }
        *(u8 *)(obj + 0x27) = (u8)b;
        *(s32 *)(obj + 4) = 0x60000000;
        *(u16 *)(obj + 0x10) = 0x400;
        *(u16 *)(obj + 8) = *(u16 *)(*(s32 *)(self + 0x64) + 6);
        *(u16 *)(obj + 0xA) = *(u16 *)(*(s32 *)(self + 0x64) + 0xA);
        e = *(u16 *)(*(s32 *)(self + 0x64) + 0xE);
        *(u16 *)(obj + 0x1A) = 0x4000;
        *(u16 *)(obj + 0x18) = 0x4000;
        *(u16 *)(obj + 0xC) = (u16)e;
        *(s16 *)(self + 2) = *(s16 *)(self + 2) + 1;
    }
}


DEFINE_func_80144988()  /* dedup: shared engine-core @0x80144988 (src/shared) */




void func_801449C8(void *a0) {

    extern void (*D_801855B0[])(void);
    D_801855B0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144a04 (src/shared) */




void func_80144A2C(void *a0) {

    extern void (*D_801855B8[])(void);
    D_801855B8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144a68 (src/shared) */


void func_80144A90(void) {
}

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144a98 (src/shared) */


DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144aec (src/shared) */


DEFINE_func_80144B14()  /* dedup: shared engine-core @0x80144B14 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_80144B9C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_801457A4);

void func_801458E0(void) {
}

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458e8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_80186144 block defeats the tail-merge of the two identical D_80186144 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145934(void) {

    extern u8 D_80186144;
    extern u8 D_801860B4;
    extern u8 D_80186090;
    extern u8 D_8018606C;
    extern u8 D_80186120;
    extern u8 D_801860FC;
    extern u8 D_801860D8;
    extern u8 D_80186048;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80186144;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80186144 load from being
         * tail-merged with the v>=0x384 D_80186144 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_801860B4;
    } else if (v >= 0x578) {
        p = &D_80186090;
    } else if (v >= 0x514) {
        p = &D_8018606C;
    } else if (v >= 0x384) {
        p = &D_80186144;
    } else if (v >= 0x258) {
        p = &D_80186120;
    } else if (v >= 0xC8) {
        p = &D_801860FC;
    } else if (v >= 0xA) {
        p = &D_801860D8;
    } else {
        p = &D_80186048;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_801861D4 block defeats the tail-merge of the two identical D_801861D4 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145A2C(void) {

    extern u8 D_801861D4;
    extern u8 D_801860B4;
    extern u8 D_80186090;
    extern u8 D_8018606C;
    extern u8 D_801861B0;
    extern u8 D_8018618C;
    extern u8 D_80186168;
    extern u8 D_80186048;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801861D4;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801861D4 load from being
         * tail-merged with the v>=0x384 D_801861D4 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_801860B4;
    } else if (v >= 0x578) {
        p = &D_80186090;
    } else if (v >= 0x514) {
        p = &D_8018606C;
    } else if (v >= 0x384) {
        p = &D_801861D4;
    } else if (v >= 0x258) {
        p = &D_801861B0;
    } else if (v >= 0xC8) {
        p = &D_8018618C;
    } else if (v >= 0xA) {
        p = &D_80186168;
    } else {
        p = &D_80186048;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145b24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145bf8 (src/shared) */


DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145c54 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_80145CEC);



// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);


void func_80145EE8(s32 param_1)
{

    extern unsigned char D_801855CC[];
    extern unsigned char D_801855FC[];
    extern unsigned char D_8018564C[];
    extern unsigned char D_8018567C[];
    extern unsigned char D_801856AC[];
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_801855CC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_801855FC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_8018564C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_8018567C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_801856AC);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_801855CC);
        ((void (*)(void *))func_80146014)(D_801855FC);
        ((void (*)(void *))func_80146014)(D_8018564C);
        ((void (*)(void *))func_80146014)(D_8018567C);
        ((void (*)(void *))func_80146014)(D_801856AC);
        break;
    }
}


DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */


void func_80146074(void) {
}


extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();

void func_8014607C(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146128\n"
        "lui   $at, %%hi(D_801C8538)\n"
        "sw    $v0, %%lo(D_801C8538)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8538)\n"
        "lw    $v0, %%lo(D_801C8538)($v0)\n"
        "nop\n"
        "beqz  $v0, .L80146114\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146360\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801463A0\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        ".L80146114:\n"
        "nop\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


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
s32 func_80146128(void)
{

    extern s32 D_80126B58;
    extern s32 *D_80126B78;
    extern u8 D_80078EC1;
    extern s32 D_80078EC8;
    extern s32 D_80126B9C;
    extern s32 D_8011F730;
    extern u16 D_801152B8;
    extern u16 D_8012693A;
    extern u8 D_80126BE0[];
    extern u8 D_801150F0[];
    register s32 base __asm__("$16");
    register s32 *p   __asm__("$17");
    p = D_80126B78;
    base = (s32)&D_80126B58;
    func_80146FC4(base);
    memcpy((void *)D_801150F0, (void *)D_80126BE0, 8);
    func_80150A70(base);
    ((void (*)(s32))func_80147098)(base);
    func_8014A638(base);
    D_8011F730 = 0;
    D_801152B8 = 0;
    D_8012693A = 0;
    if (D_80078EC1 == 0x10 && D_80078EC8 != 0) {
        *(u16 *)((s32)p + 2) = 6;
        D_80126B9C |= 0x800;
    } else {
        *(u16 *)((s32)p + 2) = 1;
        *(s32 *)(base + 0x44) &= ~0x800;
    }
    if (*(s32 *)(base + 0x1B0) != 0) {
        *(s32 *)(base + 0x1B0) = *(s32 *)(base + 0x1B0) - 1;
    }
    if (func_80155458(base) == 0 && (*(s32 *)(base + 0x44) & 0x4000000) == 0) {
        if ((func_80029104() & 0xFF) != 0) {
            func_8014ADE0(base);
            func_8014B350(base);
            ((void (*)(s32))func_8014B7A4)(base);
            ((void (*)(s32))func_80161D58)(base);
        }
        func_80029344();
        func_80161A90(base);
        ((void (*)(s32))func_8014B504)(base);
        func_80149BEC(base);
        ((void (*)(s32))func_8014B5D0)(base);
        ((void (*)(s32))func_8014C99C)(base);
        func_8014B190(base);
        func_80148648(base, 0);
        ((void (*)(s32))func_80149228)(base);
        func_8014A59C(base);
        ((void (*)(s32))func_8016F14C)(base);
        ((void (*)(s32))func_80154418)(base);
        func_80154BE4(base);
        func_80165694(base);
        func_801654A8(base);
        func_8014A680(base);
        func_8014A6A8(base);
        func_8014A71C(base);
        ((void (*)(s32))func_80172588)(base);
        ((void (*)(s32))func_801473DC)(base);
        ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
        return 1;
    }
    ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
    return 0;
}



// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_801856FC[u8 idx](&arg))

void func_80146360(void)
{

    extern void (*D_801856FC[])(void *);
    extern u8 D_80126BA4;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_80126B58;
    D_801856FC[D_80126BA4](&D_80126B58);
}






   /* size 8, align 1 -> unaligned block move */

DEFINE_func_801463A0()  /* dedup: shared engine-core @0x801463A0 (src/shared) */


DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */


DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */


DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */


DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659c (src/shared) */


DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465c0 (src/shared) */


DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465e4 (src/shared) */


DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */


DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466b4 (src/shared) */


DEFINE_func_801466F0()  /* dedup: shared engine-core @0x801466f0 (src/shared) */


DEFINE_func_80146750()  /* dedup: shared engine-core @0x80146750 (src/shared) */


DEFINE_func_8014680C()  /* dedup: shared engine-core @0x8014680c (src/shared) */


DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468c8 (src/shared) */


DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */


DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */


DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469c8 (src/shared) */



extern void func_80146AFC(void*);
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) __asm__("func_80146A6C");
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6)
{
    u8 sp[0x18];
    *(s16 *)(sp + 0x0) = a0;
    *(s32 *)(sp + 0x8) = a1;
    *(s16 *)(sp + 0x2) = a2;
    *(s16 *)(sp + 0x4) = a3;
    *(s16 *)(sp + 0x6) = a4;
    *(s32 *)(sp + 0xC) = a5;
    *(s32 *)(sp + 0x10) = a6;
    ((s32 (*)(void *))func_80146AFC)(sp);
}


DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146ab4 (src/shared) */


extern s32 func_80146B9C(void * arg0);
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_80146AFC;

/* func_80146AFC — ASCENDING twin of the byte-proven DEFINE_func_80146B9C()
 * in src/shared/engine_core.h (cookbook §71: find the already-matched sibling first).
 * Same 0x58-stride slot table (base D_8011D030), same 7-store copy body in the same
 * order, same $a2/$a1 giv pair. 80146B9C walks DOWN; this one walks UP, so the guard
 * is `p < end`, end = p + 0xA50 (30 slots x 0x58).
 *
 * DECAY ROOT CAUSE (this redraft): the stored backlog draft had been rewritten to
 * `void func_80146AFC(...)`, which drops BOTH `return 0` paths' `addu $v0,$zero,$zero`
 * and the hit path's `j .L80146B94` => LENGTH-DRIFT -2 (38 vs 40) plus $v0/$v1 regalloc
 * drift on the final lw/sw pair. Restoring the s32 return type (the fleet spelling the
 * banked sibling func_80146B9C already uses) restores MATCH at 40/40.
 *
 * RECONCILE (2026-08-01) — the whole-binary gate failed with
 *   ov_SC01_077_after.c:592: conflicting types for `D_8011D030' (previous decl :564)
 * TWO file-scope collisions were present; both are fixed HERE, with NO edit to
 * src/shared/engine_core.h and NO change to the generated code (re-verified MATCH
 * after each step):
 *
 *   1. D_8011D030 (the reported one). DEFINE_func_801469C8() emits
 *      `extern s32 D_8011D030;` at FILE scope (engine_core.h:10811, above the
 *      `s32 func_801469C8(...) {` line), and this TU expands that macro at :564 —

    extern s32 D_8011D030;
 *      i.e. before the splice point :570. The draft's `extern u16` therefore
 *      redeclared it incompatibly at :592. Conformed to the TU's `extern s32`.
 *      Codegen-neutral: the sole use is `(u8 *)&D_8011D030`, an address-of, so the
 *      declared object type never reaches a load/store width (cookbook §20).
 *
 *   2. func_80146AFC ITSELF (latent, would have surfaced next). DEFINE_func_8014C010()
 *      (:13510) and DEFINE_func_8014AD30() (:13524) each emit a file-scope
 *      `extern void func_80146AFC(void *a0);`, and this TU expands them at :1386 and
 *      :1541 — after the splice — so an `s32 func_80146AFC` definition collides on the
 *      RETURN axis. Fixed with the §37/§124 ASM-LABEL ALIAS: the C identifier is
 *      aF80146AFC, the emitted label is func_80146AFC, so the canonical void decl and
 *      this s32 definition never share a namespace. Callers discard the result, so the
 *      void-typed call sites stay codegen-identical.
 *
 * Both were reproduced and then cleared against the real cpp+cc1-2.7.2 pair using a
 * synthetic copy of this TU's declaration environment (.run/uc2/_recon_probe_80146AFC.c):
 * the pre-reconcile spelling emits exactly the gate's error pair; the spelling below
 * compiles clean.
 *
 * ORACLE: tools/match_one.py func_80146AFC --c .run/uc2/func_80146AFC.c
 *         --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_after  -> MATCH (40 ins)
 */


s32 aF80146AFC(void *arg0) __asm__("func_80146AFC");

s32 aF80146AFC(void *arg0)
{
    register u8 *p __asm__("$6");
    register u8 *q __asm__("$5");
    u8 *end;
    p = (u8 *)&D_8011D030;
    end = p + 0xA50;
    if ((u32)p < (u32)end) {
        q = p + 0x30;
        do {
            if (*(u16 *)p == 0) {
                *(s32 *)(q + 0x4) = *(s32 *)((u8 *)arg0 + 0x8);
                *(s16 *)p = *(u16 *)((u8 *)arg0 + 0x0);
                *(s16 *)(q - 0x2A) = *(u16 *)((u8 *)arg0 + 0x2);
                *(s16 *)(q - 0x26) = *(u16 *)((u8 *)arg0 + 0x4);
                *(s16 *)(q - 0x22) = *(u16 *)((u8 *)arg0 + 0x6);
                *(s32 *)(q - 0x4) = *(s32 *)((u8 *)arg0 + 0xC);
                *(s32 *)(q + 0x0) = *(s32 *)((u8 *)arg0 + 0x10);
                return (s32)p;
            }
            p += 0x58;
            q += 0x58;
        } while ((u32)p < (u32)end);
    }
    return 0;
}


DEFINE_func_80146B9C()  /* dedup: shared engine-core @0x80146b9c (src/shared) */


DEFINE_func_80146C3C()  /* dedup: shared engine-core @0x80146c3c (src/shared) */


DEFINE_func_80146C98()  /* dedup: shared engine-core @0x80146c98 (src/shared) */


DEFINE_func_80146CA0()  /* dedup: shared engine-core @0x80146ca0 (src/shared) */


DEFINE_func_80146CB4()  /* dedup: shared engine-core @0x80146cb4 (src/shared) */


DEFINE_func_80146CC8()  /* dedup: shared engine-core @0x80146cc8 (src/shared) */


DEFINE_func_80146D30()  /* dedup: shared engine-core @0x80146d30 (src/shared) */


DEFINE_func_80146D80()  /* dedup: shared engine-core @0x80146d80 (src/shared) */


DEFINE_func_80146D90()  /* dedup: shared engine-core @0x80146d90 (src/shared) */


DEFINE_func_80146DB8()  /* dedup: shared engine-core @0x80146db8 (src/shared) */


DEFINE_func_80146DE8()  /* dedup: shared engine-core @0x80146de8 (src/shared) */


DEFINE_func_80146DF8()  /* dedup: shared engine-core @0x80146df8 (src/shared) */


DEFINE_func_80146E90()  /* dedup: shared engine-core @0x80146e90 (src/shared) */


DEFINE_func_80146E98()  /* dedup: shared engine-core @0x80146e98 (src/shared) */


DEFINE_func_80146EC0()  /* dedup: shared engine-core @0x80146ec0 (src/shared) */


extern s16 func_8012A68C(void);
extern s16 func_8012A758(void);
extern void func_8004978C(s16 *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_80146F58(s32 a0, s32 a1) {
    s16 vec[3];
    u8 mat[0x20];
    vec[0] = func_8012A68C();
    vec[1] = func_8012A758();
    vec[2] = 0;
    func_8004978C(vec, mat);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, (void *)a0, (void *)a1);
}


extern void func_80015954(s32 a0, s32 a1);
extern void *memcpy(void *dst, const void *src, u32 n);
void func_80146FC4(s32 a0) {

    extern u8 D_80126DB0[];
    extern u16 D_80126DB6;
    s32 s1 = a0;
    s32 s0;
    if (*(s16 *)(s1 + 0xA) >= 0x401) {
        s0 = (s32)D_80126DB0;
        func_80015954(s0, s1 + 0x4);
        memcpy((void *)(s1 + 0x88), (void *)s0, 8);
        *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6;
    }
}


DEFINE_func_8014704C()  /* dedup: shared engine-core @0x8014704c (src/shared) */


DEFINE_func_80147054()  /* dedup: shared engine-core @0x80147054 (src/shared) */


DEFINE_func_80147060()  /* dedup: shared engine-core @0x80147060 (src/shared) */


DEFINE_func_8014706C()  /* dedup: shared engine-core @0x8014706c (src/shared) */


DEFINE_func_80147078()  /* dedup: shared engine-core @0x80147078 (src/shared) */


DEFINE_func_80147084()  /* dedup: shared engine-core @0x80147084 (src/shared) */


DEFINE_func_8014708C()  /* dedup: shared engine-core @0x8014708c (src/shared) */


DEFINE_func_80147098()  /* dedup: shared engine-core @0x80147098 (src/shared) */


DEFINE_func_801470A0()  /* dedup: shared engine-core @0x801470a0 (src/shared) */


DEFINE_func_801470AC()  /* dedup: shared engine-core @0x801470ac (src/shared) */


DEFINE_func_801470B4()  /* dedup: shared engine-core @0x801470b4 (src/shared) */


DEFINE_func_801470C0()  /* dedup: shared engine-core @0x801470c0 (src/shared) */


DEFINE_func_80147118()  /* dedup: shared engine-core @0x80147118 (src/shared) */


DEFINE_func_80147264()  /* dedup: shared engine-core @0x80147264 (src/shared) */


DEFINE_func_80147290()  /* dedup: shared engine-core @0x80147290 (src/shared) */


DEFINE_func_801472B4()  /* dedup: shared engine-core @0x801472b4 (src/shared) */


DEFINE_func_801472C8()  /* dedup: shared engine-core @0x801472c8 (src/shared) */


DEFINE_func_801472DC()  /* dedup: shared engine-core @0x801472dc (src/shared) */


DEFINE_func_801472F0()  /* dedup: shared engine-core @0x801472f0 (src/shared) */


DEFINE_func_80147300()  /* dedup: shared engine-core @0x80147300 (src/shared) */


DEFINE_func_80147324()  /* dedup: shared engine-core @0x80147324 (src/shared) */


DEFINE_func_80147364()  /* dedup: shared engine-core @0x80147364 (src/shared) */


DEFINE_func_801473DC()  /* dedup: shared engine-core @0x801473dc (src/shared) */


DEFINE_func_801473EC()  /* dedup: shared engine-core @0x801473ec (src/shared) */


DEFINE_func_80147460()  /* dedup: shared engine-core @0x80147460 (src/shared) */


DEFINE_func_80147478()  /* dedup: shared engine-core @0x80147478 (src/shared) */


DEFINE_func_801474D8()  /* dedup: shared engine-core @0x801474d8 (src/shared) */


DEFINE_func_801474EC()  /* dedup: shared engine-core @0x801474ec (src/shared) */


DEFINE_func_80147514()  /* dedup: shared engine-core @0x80147514 (src/shared) */


DEFINE_func_80147628()  /* dedup: shared engine-core @0x80147628 (src/shared) */


DEFINE_func_80147718()  /* dedup: shared engine-core @0x80147718 (src/shared) */


DEFINE_func_80147788()  /* dedup: shared engine-core @0x80147788 (src/shared) */


DEFINE_func_801477A8()  /* dedup: shared engine-core @0x801477a8 (src/shared) */


DEFINE_func_801477C8()  /* dedup: shared engine-core @0x801477c8 (src/shared) */


DEFINE_func_801477E8()  /* dedup: shared engine-core @0x801477e8 (src/shared) */


DEFINE_func_80147814()  /* dedup: shared engine-core @0x80147814 (src/shared) */


DEFINE_func_80147860()  /* dedup: shared engine-core @0x80147860 (src/shared) */


DEFINE_func_801478B8()  /* dedup: shared engine-core @0x801478b8 (src/shared) */


DEFINE_func_80147928()  /* dedup: shared engine-core @0x80147928 (src/shared) */


DEFINE_func_80147948()  /* dedup: shared engine-core @0x80147948 (src/shared) */


DEFINE_func_8014799C()  /* dedup: shared engine-core @0x8014799c (src/shared) */


DEFINE_func_801479BC()  /* dedup: shared engine-core @0x801479bc (src/shared) */


DEFINE_func_80147A10()  /* dedup: shared engine-core @0x80147a10 (src/shared) */


DEFINE_func_80147A30()  /* dedup: shared engine-core @0x80147a30 (src/shared) */


DEFINE_func_80147A84()  /* dedup: shared engine-core @0x80147a84 (src/shared) */


DEFINE_func_80147AAC()  /* dedup: shared engine-core @0x80147aac (src/shared) */


DEFINE_func_80147AD4()  /* dedup: shared engine-core @0x80147ad4 (src/shared) */


DEFINE_func_80147B18()  /* dedup: shared engine-core @0x80147b18 (src/shared) */


DEFINE_func_80147B5C()  /* dedup: shared engine-core @0x80147b5c (src/shared) */


DEFINE_func_80147C30()  /* dedup: shared engine-core @0x80147c30 (src/shared) */


DEFINE_func_80147CC8()  /* dedup: shared engine-core @0x80147cc8 (src/shared) */


DEFINE_func_80147D38()  /* dedup: shared engine-core @0x80147d38 (src/shared) */


DEFINE_func_80147DC0()  /* dedup: shared engine-core @0x80147dc0 (src/shared) */


DEFINE_func_80147E44()  /* dedup: shared engine-core @0x80147e44 (src/shared) */


DEFINE_func_80147F50()  /* dedup: shared engine-core @0x80147f50 (src/shared) */


DEFINE_func_80147F78()  /* dedup: shared engine-core @0x80147f78 (src/shared) */


DEFINE_func_80148038()  /* dedup: shared engine-core @0x80148038 (src/shared) */


DEFINE_func_80148094()  /* dedup: shared engine-core @0x80148094 (src/shared) */


DEFINE_func_801483E8()  /* dedup: shared engine-core @0x801483e8 (src/shared) */


DEFINE_func_801484B0()  /* dedup: shared engine-core @0x801484b0 (src/shared) */


DEFINE_func_801484E8()  /* dedup: shared engine-core @0x801484e8 (src/shared) */


DEFINE_func_80148534()  /* dedup: shared engine-core @0x80148534 (src/shared) */


DEFINE_func_8014856C()  /* dedup: shared engine-core @0x8014856c (src/shared) */


DEFINE_func_801485B8()  /* dedup: shared engine-core @0x801485b8 (src/shared) */


DEFINE_func_80148634()  /* dedup: shared engine-core @0x80148634 (src/shared) */


DEFINE_func_80148648()  /* dedup: shared engine-core @0x80148648 (src/shared) */


DEFINE_func_801487F4()  /* dedup: shared engine-core @0x801487f4 (src/shared) */


DEFINE_func_80148800()  /* dedup: shared engine-core @0x80148800 (src/shared) */


DEFINE_func_8014880C()  /* dedup: shared engine-core @0x8014880c (src/shared) */


DEFINE_func_80148818()  /* dedup: shared engine-core @0x80148818 (src/shared) */


DEFINE_func_80148824()  /* dedup: shared engine-core @0x80148824 (src/shared) */


DEFINE_func_801488A8()  /* dedup: shared engine-core @0x801488a8 (src/shared) */


DEFINE_func_8014891C()  /* dedup: shared engine-core @0x8014891c (src/shared) */


DEFINE_func_80148980()  /* dedup: shared engine-core @0x80148980 (src/shared) */


DEFINE_func_801489E8()  /* dedup: shared engine-core @0x801489e8 (src/shared) */


DEFINE_func_80148A48()  /* dedup: shared engine-core @0x80148a48 (src/shared) */


DEFINE_func_80148AAC()  /* dedup: shared engine-core @0x80148aac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (71 ins). switch binary-tree; s1 angle = pin-source-of-copy ($5 temp + retie); 2nd-block double-load + 0x80-clobber via $v1/$v0/$a0 pins + lazy hi-pin reusing dead c80 reg

extern s32 ratan2(s32 a0, s32 a1);

int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern ActorFn D_80185704[];
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    register s32 tmp __asm__("$5") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                        *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 sVar3;
    u8 bVar1;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    sVar3 = tmp;
    bVar1 = *(u8 *)(p + 0xA9);

    switch (bVar1) {
    case 0x41:
        return D_80185704[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
    case 0x53:
    case 0x73:
        {
            register u32 bb __asm__("$3");
            register s32 c80 __asm__("$2") = 0x80;
            register s32 lo __asm__("$4");
            register s32 hi __asm__("$2");
            bb = *(u16 *)(p + 0xAE);
            lo = bb & 0xFF;
            if (lo != c80 || (hi = bb >> 8) != 0x80) {
                s32 sVar4;
                __asm__ __volatile__("" : : : "memory");
                sVar4 = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
                *(u16 *)(iVar5 + 0x12) = (sVar3 + sVar4) & 0xFFF;
                return 1;
            }
            return 0;
        }
    }
}


DEFINE_func_80148C18()  /* dedup: shared engine-core @0x80148c18 (src/shared) */


DEFINE_func_80148C20()  /* dedup: shared engine-core @0x80148c20 (src/shared) */


DEFINE_func_80148C34()  /* dedup: shared engine-core @0x80148c34 (src/shared) */


DEFINE_func_80148C4C()  /* dedup: shared engine-core @0x80148c4c (src/shared) */


DEFINE_func_80148C64()  /* dedup: shared engine-core @0x80148c64 (src/shared) */


DEFINE_func_80148C7C()  /* dedup: shared engine-core @0x80148c7c (src/shared) */


DEFINE_func_80148C84()  /* dedup: shared engine-core @0x80148c84 (src/shared) */


DEFINE_func_80148C9C()  /* dedup: shared engine-core @0x80148c9c (src/shared) */


DEFINE_func_80148CB4()  /* dedup: shared engine-core @0x80148cb4 (src/shared) */


DEFINE_func_80148CCC()  /* dedup: shared engine-core @0x80148ccc (src/shared) */


DEFINE_func_80148CE4()  /* dedup: shared engine-core @0x80148ce4 (src/shared) */


DEFINE_func_80148CEC()  /* dedup: shared engine-core @0x80148cec (src/shared) */


DEFINE_func_80148CF4()  /* dedup: shared engine-core @0x80148cf4 (src/shared) */


DEFINE_func_80148D0C()  /* dedup: shared engine-core @0x80148d0c (src/shared) */


DEFINE_func_80148D24()  /* dedup: shared engine-core @0x80148d24 (src/shared) */


DEFINE_func_80148D3C()  /* dedup: shared engine-core @0x80148d3c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (68 ins)
extern s32 ratan2(s32 a0, s32 a1);

s32 func_80148D44(void) {

    extern s32 D_801151D4;
    extern u8 D_80126C01;
    extern u16 D_80126C02;
    extern u16 D_80126C06;
    extern s32 D_80185744[];
    register s32 ang __asm__("$16");
    register s32 a __asm__("$4");
    s32 p;
    s32 res;
    s32 d;

    p = D_801151D4;
    a = (ratan2(*(s32 *)(p + 0x44) - *(s32 *)(p + 0x50),
                  *(s32 *)(p + 0x48) - *(s32 *)(p + 0x3c)) - 0x400) & 0xFFF;
    d = (s32)D_80126C01;
    __asm__ __volatile__("" : : "r"(a));
    ang = a;
    if (d == 0x53) {
        goto final;
    }
    if (d < 0x54) {
        if (d == 0x41) {
            goto call;
        }
        return 0x41;
    }
    if (d != 0x73) {
        return 0x73;
    }
    goto final;
call:
    return (s32)(s16)((s16 (*)())(D_80185744[D_80126C02 >> 0xc]))();
final:
    {
        u32 e = D_80126C06;
        if (((e & 0xff) == 0x80) && ((e >> 8) == (e & 0xff))) {
            return -1;
        }
        __asm__ __volatile__("" : : : "memory");
        res = (ang + ratan2((D_80126C06 & 0xff) - 0x80, 0x80 - (D_80126C06 >> 8))) & 0xFFF;
    }
    return res;
}



extern s32 ratan2(s32, s32);
/* derived from asm: lui/addu/lw %lo(D_80185784) indexed by (u16>>12)*4, then jalr with no args;
 * the result is sign-extended from 16 bits => the table's functions return s16. */

s32 func_80148E54(s32 arg0) {

    extern s32 D_801151D4;
    extern s16 (*D_80185784[])();
    register s32 tmp __asm__("$4") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                                             *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    ang = tmp;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_80185784[*(u16 *)(arg0 + 0xAA) >> 12]();
    case 0x53:
    case 0x73:
        if ((*(u16 *)(arg0 + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(arg0 + 0xAE) >> 8) == 0x80) {
            return -1;
        }
        return (ang + ratan2((*(u16 *)(arg0 + 0xAE) & 0xFF) - 0x80,
                             0x80 - (*(u16 *)(arg0 + 0xAE) >> 8))) & 0xFFF;
    }
}


DEFINE_func_80148F60()  /* dedup: shared engine-core @0x80148f60 (src/shared) */


DEFINE_func_80148F68()  /* dedup: shared engine-core @0x80148f68 (src/shared) */


DEFINE_func_80148F74()  /* dedup: shared engine-core @0x80148f74 (src/shared) */


DEFINE_func_80148F80()  /* dedup: shared engine-core @0x80148f80 (src/shared) */


DEFINE_func_80148F8C()  /* dedup: shared engine-core @0x80148f8c (src/shared) */


DEFINE_func_80148F98()  /* dedup: shared engine-core @0x80148f98 (src/shared) */


DEFINE_func_80148FA0()  /* dedup: shared engine-core @0x80148fa0 (src/shared) */


DEFINE_func_80148FAC()  /* dedup: shared engine-core @0x80148fac (src/shared) */


DEFINE_func_80148FB8()  /* dedup: shared engine-core @0x80148fb8 (src/shared) */


DEFINE_func_80148FC4()  /* dedup: shared engine-core @0x80148fc4 (src/shared) */


DEFINE_func_80148FD0()  /* dedup: shared engine-core @0x80148fd0 (src/shared) */


DEFINE_func_80148FD8()  /* dedup: shared engine-core @0x80148fd8 (src/shared) */


DEFINE_func_80148FE0()  /* dedup: shared engine-core @0x80148fe0 (src/shared) */


DEFINE_func_80148FEC()  /* dedup: shared engine-core @0x80148fec (src/shared) */


DEFINE_func_80148FF8()  /* dedup: shared engine-core @0x80148ff8 (src/shared) */


DEFINE_func_80149004()  /* dedup: shared engine-core @0x80149004 (src/shared) */


DEFINE_func_8014900C()  /* dedup: shared engine-core @0x8014900c (src/shared) */


DEFINE_func_80149020()  /* dedup: shared engine-core @0x80149020 (src/shared) */


DEFINE_func_80149034()  /* dedup: shared engine-core @0x80149034 (src/shared) */


DEFINE_func_80149048()  /* dedup: shared engine-core @0x80149048 (src/shared) */


DEFINE_func_8014905C()  /* dedup: shared engine-core @0x8014905c (src/shared) */


DEFINE_func_80149078()  /* dedup: shared engine-core @0x80149078 (src/shared) */


DEFINE_func_801490E0()  /* dedup: shared engine-core @0x801490e0 (src/shared) */


DEFINE_func_801490E8()  /* dedup: shared engine-core @0x801490e8 (src/shared) */


DEFINE_func_801490F0()  /* dedup: shared engine-core @0x801490f0 (src/shared) */


DEFINE_func_801490F8()  /* dedup: shared engine-core @0x801490f8 (src/shared) */


DEFINE_func_80149184()  /* dedup: shared engine-core @0x80149184 (src/shared) */


DEFINE_func_801491C4()  /* dedup: shared engine-core @0x801491c4 (src/shared) */


DEFINE_func_80149204()  /* dedup: shared engine-core @0x80149204 (src/shared) */


DEFINE_func_80149210()  /* dedup: shared engine-core @0x80149210 (src/shared) */


DEFINE_func_80149228()  /* dedup: shared engine-core @0x80149228 (src/shared) */


DEFINE_func_80149284()  /* dedup: shared engine-core @0x80149284 (src/shared) */


DEFINE_func_80149290()  /* dedup: shared engine-core @0x80149290 (src/shared) */


DEFINE_func_80149350()  /* dedup: shared engine-core @0x80149350 (src/shared) */


DEFINE_func_80149374()  /* dedup: shared engine-core @0x80149374 (src/shared) */


DEFINE_func_801493D0()  /* dedup: shared engine-core @0x801493d0 (src/shared) */


DEFINE_func_8014942C()  /* dedup: shared engine-core @0x8014942c (src/shared) */


void func_8012F038(int param_1, short *param_2, short *param_3);

void func_80149450(int param_1, short *param_2)
{
    short tmp_out[3];
    short tmp_in[3];

    tmp_in[0] = param_2[1];
    tmp_in[1] = param_2[3];
    tmp_in[2] = param_2[5];

    func_8012F038(*(int *)(param_1 + 0x20) + 0x34, tmp_in, tmp_out);

    param_2[1] = tmp_out[0];
    param_2[3] = tmp_out[1];
    param_2[5] = tmp_out[2];
}


extern void func_8012F038(int param_1, short *param_2, short *param_3);

void func_801494CC(int param_1, short *param_2, short *param_3)
{
  short temp_out[3];
  short temp_in[3];

  temp_in[0] = param_2[1];
  temp_in[1] = param_2[3];
  temp_in[2] = param_2[5];

  func_8012F038(*(int *)(param_1 + 0x20) + 0x34, temp_in, temp_out);

  param_3[1] = temp_out[0];
  param_3[3] = temp_out[1];
  param_3[5] = temp_out[2];
}


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EF70(s32 a0, s32 a1);

void func_80149544(s32 a0, s32 a1, s32 a2)
{
    s32 buf[2];

    func_8012F14C(*(s32 *)(a0 + 0x20) + 0x34, a1, buf);
    func_8012EF70(buf, a2);
}


void func_8012F14C(s32 a0, s32 a1, s32 a2);
void func_8012EFB8(s32 a0);

void func_80149584(s32 a0, s32 a1, s32 a2)
{
    char local_10[8];

    func_8012F14C(*(s32*)((char*)a0 + 0x20) + 0x34, a1, (s32)local_10);
    ((void (*)(s32, s32))func_8012EFB8)((s32)local_10, a2);
}


DEFINE_func_801495C4()  /* dedup: shared engine-core @0x801495C4 (src/shared) */


DEFINE_func_8014964C()  /* dedup: shared engine-core @0x8014964c (src/shared) */


DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496d4 (src/shared) */


DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */


DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */


DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */


DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */


DEFINE_func_801497A8()  /* dedup: shared engine-core @0x801497a8 (src/shared) */


DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */


DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */


DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498c0 (src/shared) */


DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498e0 (src/shared) */


/* callees (JSON-canonical, verbatim) */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80147364();
extern s32 func_800CCF28(s32 a0);
extern u16 *func_80146750(u16 *param_1);

/* data (JSON-canonical, verbatim) */
extern u8 D_80126B5C;
extern void *D_8012707C;

/* not in the JSON data list but required by the asm (%hi/%lo currentLocationId);
   type per src/shared/engine_core.h DEFINE_func_80149954() sibling macro (lh => s16) */
extern s16 currentLocationId;

s32 func_80149954(s32 s0)
{
    s32 sp10[2];
    s16 buf[10];

    if (*(s32 *)(s0 + 0x44) & 0x404) {
        return 0;
    }
    if ((*(u16 *)(s0 + 0xAA) & 0x90) == 0) {
        if (currentLocationId == 0x308D) {
            func_80015978((s32)&D_80126B5C, sp10);
            func_8012E5CC((s32)sp10, 0x4, 0x8E0);
            return 0;
        }
        func_8002D4C8(0x4, 0x8E0);
        return 0;
    }
    if (*(u16 *)(s0 + 0xAC) & 0x90) {
        if ((s32)D_8012707C == 0x8E0) {
            D_8012707C = 0;
        } else {
            func_80147364(0x8E0, 0);
        }
    }
    func_800CCF28(s0);
    *(s16 *)((s32)buf + 0x0) = 0x12;
    *(s32 *)((s32)buf + 0x8) = s0;
    *(s16 *)((s32)buf + 0x2) = 0;
    *(s16 *)((s32)buf + 0x4) = -0x1E;
    *(s16 *)((s32)buf + 0x6) = 0;
    *(s32 *)((s32)buf + 0xC) = 0;
    *(s32 *)((s32)buf + 0x10) = 0;
    func_80146750(buf);
    return 1;
}


DEFINE_func_80149A64()  /* dedup: shared engine-core @0x80149a64 (src/shared) */


DEFINE_func_80149AA8()  /* dedup: shared engine-core @0x80149aa8 (src/shared) */


DEFINE_func_80149AD4()  /* dedup: shared engine-core @0x80149ad4 (src/shared) */


DEFINE_func_80149B14()  /* dedup: shared engine-core @0x80149b14 (src/shared) */


DEFINE_func_80149B54()  /* dedup: shared engine-core @0x80149b54 (src/shared) */


DEFINE_func_80149BAC()  /* dedup: shared engine-core @0x80149bac (src/shared) */


DEFINE_func_80149BEC()  /* dedup: shared engine-core @0x80149bec (src/shared) */


DEFINE_func_80149C08()  /* dedup: shared engine-core @0x80149c08 (src/shared) */


DEFINE_func_80149C94()  /* dedup: shared engine-core @0x80149c94 (src/shared) */


DEFINE_func_80149CB4()  /* dedup: shared engine-core @0x80149cb4 (src/shared) */


DEFINE_func_80149CD4()  /* dedup: shared engine-core @0x80149cd4 (src/shared) */


DEFINE_func_80149D10()  /* dedup: shared engine-core @0x80149d10 (src/shared) */


DEFINE_func_80149D9C()  /* dedup: shared engine-core @0x80149d9c (src/shared) */


DEFINE_func_80149DD8()  /* dedup: shared engine-core @0x80149dd8 (src/shared) */


DEFINE_func_80149E94()  /* dedup: shared engine-core @0x80149e94 (src/shared) */


extern void func_80144A04(s32 *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EDEC(s32, s32, s32);
s32 func_80149F2C(s32 a0, s32 a1)
{
    void *s1 = a0;
    s32 *s0;
    if (*(u16 *)a1 == 0x83 || *(u16 *)a1 == 0x61) {
        s0 = (s32 *)((s32 (*)())func_80144A04)((s32 *)a1);
        if (s0 != 0) {
            func_801599A4(s1);
            func_80159B3C(s1);
            ((void (*)(s32, s32))func_8016EDEC)((s32)s0, 0x1000000);
            return 1;
        }
    }
    return 0;
}


void func_80149FA8(void) {
}


// @class: regalloc-order
// @stuck: none — MATCH (38 ins)
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {

    extern s32 D_801857C4[];
    extern u8 D_80078E78[];
    s32 *p = &D_801857C4[0];
    register s32 v __asm__("$3") = *p;
    u8 *q = &D_80078E78[0];
    s32 loc;

    if (v != 0) {
        loc = currentLocationId;
        p = p + 1;
        do {
            if (loc == v) {
                goto ret0;
            }
            v = *p;
            p = p + 1;
        } while (v != 0);
    }

    if ((*(u32 *)(a0 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if (*(s16 *)(a0 + 0x1C8) != 0) {
        return 0;
    }
    if ((*(u16 *)(a0 + 0xAC) & 0x100) == 0) {
    ret0:
        return 0;
    }
    v = q[0x48];
    q[0x48] = v ^ 0x80;
    return 1;
}


extern u8 func_8014BEF8(void);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern void func_8014A1B0(s32 a0, s32 a1);
extern u8 D_801202A0[];

typedef struct {
    /* 0x00 */ s16 a30;
    /* 0x02 */ s16 a2e;
    /* 0x04 */ s16 a2c;
    /* 0x06 */ s16 pad06;
    /* 0x08 */ s32 buf[2];
    /* 0x10 */ s16 a20;
    /* 0x12 */ s16 a1e;
    /* 0x14 */ s16 a1c;
} Loc_8014A048;

s32 func_8014A048(s32 param_1) {
    Loc_8014A048 L;
    s32 s0;
    s32 s2;
    u32 s3;

    if ((*(u32 *)(param_1 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if ((*(u16 *)(param_1 + 0xAC) & 0x80) == 0) {
        if ((*(u16 *)(param_1 + 0xAC) & 0x10) == 0) {
            return 0;
        }
        if (((s32 (*)(s32))func_8014BEF8)(param_1) == 0) {
            goto ret0;
        }
    }
    L.a30 = *(s16 *)(param_1 + 6);
    L.a2e = *(s16 *)(param_1 + 0xA);
    L.a2c = *(s16 *)(param_1 + 0xE);
    L.a1e = -0x10;
    L.a20 = 0;
    L.a1c = -0x20;
    func_8012F14C(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&L.a20, (s32)L.buf);
    s3 = 0;
    s2 = 0;
    while (1) {
        s0 = (s32)D_801202A0 + s2;
        __asm__ __volatile__("" : "=r"(s0) : "0"(s0));
        if ((*(u16 *)s0 != 0) &&
            (*(s32 *)(s0 + 0x58) != 0) &&
            (*(s16 *)(s0 + 0xAA) == 0) &&
            (*(s32 *)(param_1 + 0x184) != s0) &&
            ((*(u16 *)(s0 + 0x5C) & 0x200) != 0) &&
            (func_80135260(*(s32 *)(s0 + 0x20), *(s32 *)(s0 + 0x58), &L.a30, (s16 *)L.buf) != 0)) {
            break;
        }
        s3++;
        s2 += 0x10C;
        if (s3 >= 0x60) {
            return 0;
        }
    }
    *(s32 *)(param_1 + 0x178) = s0;
    func_8014A1B0(param_1, s0);
    return 1;
ret0:
    return 0;
}


DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014a1b0 (src/shared) */


DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014a218 (src/shared) */


DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014a238 (src/shared) */


DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014a2e4 (src/shared) */


DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014a380 (src/shared) */


DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014a3e0 (src/shared) */


DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014a454 (src/shared) */


DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014a4b4 (src/shared) */


DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014a4fc (src/shared) */


DEFINE_func_8014A51C()  /* dedup: shared engine-core @0x8014a51c (src/shared) */


DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014a59c (src/shared) */


DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014a638 (src/shared) */


DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014a674 (src/shared) */


DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014a680 (src/shared) */


DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014a69c (src/shared) */


DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014a6a8 (src/shared) */


DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014a6c4 (src/shared) */


DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014a71c (src/shared) */


  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014A738;








DEFINE_func_8014A738()  /* dedup: shared engine-core @0x8014A738 (src/shared) */


DEFINE_func_8014A830()  /* dedup: shared engine-core @0x8014a830 (src/shared) */


DEFINE_func_8014A850()  /* dedup: shared engine-core @0x8014a850 (src/shared) */


DEFINE_func_8014AA04()  /* dedup: shared engine-core @0x8014aa04 (src/shared) */


DEFINE_func_8014AA28()  /* dedup: shared engine-core @0x8014aa28 (src/shared) */


DEFINE_func_8014AB5C()  /* dedup: shared engine-core @0x8014ab5c (src/shared) */


DEFINE_func_8014AB7C()  /* dedup: shared engine-core @0x8014ab7c (src/shared) */


DEFINE_func_8014ABF0()  /* dedup: shared engine-core @0x8014abf0 (src/shared) */


DEFINE_func_8014AC10()  /* dedup: shared engine-core @0x8014ac10 (src/shared) */


DEFINE_func_8014ACC0()  /* dedup: shared engine-core @0x8014acc0 (src/shared) */


DEFINE_func_8014ACE8()  /* dedup: shared engine-core @0x8014ace8 (src/shared) */


DEFINE_func_8014AD30()  /* dedup: shared engine-core @0x8014ad30 (src/shared) */


DEFINE_func_8014AD7C()  /* dedup: shared engine-core @0x8014ad7c (src/shared) */


DEFINE_func_8014ADA8()  /* dedup: shared engine-core @0x8014ada8 (src/shared) */


DEFINE_func_8014ADE0()  /* dedup: shared engine-core @0x8014ade0 (src/shared) */


DEFINE_func_8014B00C()  /* dedup: shared engine-core @0x8014b00c (src/shared) */


DEFINE_func_8014B034()  /* dedup: shared engine-core @0x8014b034 (src/shared) */


DEFINE_func_8014B084()  /* dedup: shared engine-core @0x8014b084 (src/shared) */


DEFINE_func_8014B12C()  /* dedup: shared engine-core @0x8014b12c (src/shared) */


DEFINE_func_8014B154()  /* dedup: shared engine-core @0x8014b154 (src/shared) */


DEFINE_func_8014B160()  /* dedup: shared engine-core @0x8014b160 (src/shared) */


DEFINE_func_8014B190()  /* dedup: shared engine-core @0x8014b190 (src/shared) */


DEFINE_func_8014B2A8()  /* dedup: shared engine-core @0x8014b2a8 (src/shared) */


DEFINE_func_8014B2D0()  /* dedup: shared engine-core @0x8014b2d0 (src/shared) */


DEFINE_func_8014B2F8()  /* dedup: shared engine-core @0x8014b2f8 (src/shared) */


DEFINE_func_8014B310()  /* dedup: shared engine-core @0x8014b310 (src/shared) */


DEFINE_func_8014B33C()  /* dedup: shared engine-core @0x8014b33c (src/shared) */


DEFINE_func_8014B350()  /* dedup: shared engine-core @0x8014b350 (src/shared) */


DEFINE_func_8014B4C4()  /* dedup: shared engine-core @0x8014b4c4 (src/shared) */


DEFINE_func_8014B4D4()  /* dedup: shared engine-core @0x8014b4d4 (src/shared) */


DEFINE_func_8014B504()  /* dedup: shared engine-core @0x8014b504 (src/shared) */


DEFINE_func_8014B598()  /* dedup: shared engine-core @0x8014b598 (src/shared) */


DEFINE_func_8014B5B0()  /* dedup: shared engine-core @0x8014b5b0 (src/shared) */


DEFINE_func_8014B5B8()  /* dedup: shared engine-core @0x8014b5b8 (src/shared) */


DEFINE_func_8014B5C4()  /* dedup: shared engine-core @0x8014b5c4 (src/shared) */


DEFINE_func_8014B5D0()  /* dedup: shared engine-core @0x8014b5d0 (src/shared) */


DEFINE_func_8014B5D8()  /* dedup: shared engine-core @0x8014b5d8 (src/shared) */


DEFINE_func_8014B6F0()  /* dedup: shared engine-core @0x8014b6f0 (src/shared) */


DEFINE_func_8014B768()  /* dedup: shared engine-core @0x8014b768 (src/shared) */


DEFINE_func_8014B7A4()  /* dedup: shared engine-core @0x8014b7a4 (src/shared) */


DEFINE_func_8014B944()  /* dedup: shared engine-core @0x8014b944 (src/shared) */


DEFINE_func_8014BB0C()  /* dedup: shared engine-core @0x8014bb0c (src/shared) */


DEFINE_func_8014BB24()  /* dedup: shared engine-core @0x8014bb24 (src/shared) */


DEFINE_func_8014BC0C()  /* dedup: shared engine-core @0x8014bc0c (src/shared) */


DEFINE_func_8014BC44()  /* dedup: shared engine-core @0x8014bc44 (src/shared) */


DEFINE_func_8014BC80()  /* dedup: shared engine-core @0x8014bc80 (src/shared) */


DEFINE_func_8014BCC0()  /* dedup: shared engine-core @0x8014bcc0 (src/shared) */


DEFINE_func_8014BCEC()  /* dedup: shared engine-core @0x8014bcec (src/shared) */


DEFINE_func_8014BD24()  /* dedup: shared engine-core @0x8014bd24 (src/shared) */


DEFINE_func_8014BD60()  /* dedup: shared engine-core @0x8014bd60 (src/shared) */


DEFINE_func_8014BD98()  /* dedup: shared engine-core @0x8014bd98 (src/shared) */


DEFINE_func_8014BDC8()  /* dedup: shared engine-core @0x8014bdc8 (src/shared) */


void func_8014BDE0(void) {
}

DEFINE_func_8014BDE8()  /* dedup: shared engine-core @0x8014bde8 (src/shared) */


DEFINE_func_8014BE78()  /* dedup: shared engine-core @0x8014be78 (src/shared) */


DEFINE_func_8014BE9C()  /* dedup: shared engine-core @0x8014be9c (src/shared) */


DEFINE_func_8014BEC0()  /* dedup: shared engine-core @0x8014bec0 (src/shared) */


DEFINE_func_8014BEF8()  /* dedup: shared engine-core @0x8014bef8 (src/shared) */


DEFINE_func_8014BF18()  /* dedup: shared engine-core @0x8014bf18 (src/shared) */


DEFINE_func_8014BF48()  /* dedup: shared engine-core @0x8014bf48 (src/shared) */


DEFINE_func_8014BF6C()  /* dedup: shared engine-core @0x8014bf6c (src/shared) */


DEFINE_func_8014BF8C()  /* dedup: shared engine-core @0x8014bf8c (src/shared) */


DEFINE_func_8014BFB0()  /* dedup: shared engine-core @0x8014bfb0 (src/shared) */


DEFINE_func_8014BFD4()  /* dedup: shared engine-core @0x8014bfd4 (src/shared) */


DEFINE_func_8014BFF4()  /* dedup: shared engine-core @0x8014bff4 (src/shared) */


DEFINE_func_8014C010()  /* dedup: shared engine-core @0x8014c010 (src/shared) */


DEFINE_func_8014C050()  /* dedup: shared engine-core @0x8014c050 (src/shared) */


DEFINE_func_8014C088()  /* dedup: shared engine-core @0x8014c088 (src/shared) */


DEFINE_func_8014C0C8()  /* dedup: shared engine-core @0x8014c0c8 (src/shared) */


DEFINE_func_8014C118()  /* dedup: shared engine-core @0x8014c118 (src/shared) */


DEFINE_func_8014C168()  /* dedup: shared engine-core @0x8014c168 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_8014C1A0);

DEFINE_func_8014C1C8()  /* dedup: shared engine-core @0x8014c1c8 (src/shared) */


DEFINE_func_8014C278()  /* dedup: shared engine-core @0x8014c278 (src/shared) */


DEFINE_func_8014C2B0()  /* dedup: shared engine-core @0x8014c2b0 (src/shared) */


DEFINE_func_8014C308()  /* dedup: shared engine-core @0x8014c308 (src/shared) */


DEFINE_func_8014C3A4()  /* dedup: shared engine-core @0x8014c3a4 (src/shared) */


DEFINE_func_8014C3D0()  /* dedup: shared engine-core @0x8014c3d0 (src/shared) */


DEFINE_func_8014C43C()  /* dedup: shared engine-core @0x8014c43c (src/shared) */



/* §37/§73/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h, inside 8
 * DEFINE_func_* macros); the byte-true body must return s32.  Aliasing the C name sidesteps the
 * RETURN-axis conflict with no header edit.  This line MUST travel with the body. */
s32 aF8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4) __asm__("func_8014C4AC");

DEFINE_func_8014C4AC()  /* dedup: shared engine-core @0x8014C4AC (src/shared) */


DEFINE_func_8014C568()  /* dedup: shared engine-core @0x8014c568 (src/shared) */


DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014c59c (src/shared) */



extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {

    extern u8 D_80185854;
    return func_8014C5FC(a0, a1, &D_80185854);
}


DEFINE_func_8014C5FC()  /* dedup: shared engine-core @0x8014c5fc (src/shared) */


DEFINE_func_8014C6AC()  /* dedup: shared engine-core @0x8014c6ac (src/shared) */


DEFINE_func_8014C6C0()  /* dedup: shared engine-core @0x8014c6c0 (src/shared) */


DEFINE_func_8014C6D0()  /* dedup: shared engine-core @0x8014c6d0 (src/shared) */


DEFINE_func_8014C6E0()  /* dedup: shared engine-core @0x8014c6e0 (src/shared) */





// @class: schedule
// @stuck: none — MATCH (match_one 91/91)
//
// Levers used (all byte-gated on ov_SC07_006):
//  1. §struct  8-byte alignment-1 struct copy `*(M8_8014C6F4*)(a+0x164) = *(M8_8014C6F4*)(p+0x10)`
//     -> the lwl/lwr,lwl/lwr,swl/swr,swl/swr block (engine_types.h M8_xxx convention).
//  2. §17 base-pointer cache: `u8 *p = D_80078E78;` (NOT a direct D_80078E78[0x49]) so gcc pins
//     the base into callee-saved $s1 and hoists the la into the prologue (live across the jal).
//  3. §17 register pins: the search result `e` MUST be $v0 and the limit `lim` $v1, else
//     local-alloc swaps the loop IV/limit pair ($v1<->$a0) and coalesces `e` into the IV.
//  4. DELAY-SLOT lever (new): writing the compare constant as its own pre-loop statement
//     (`want = 0x22;`) instead of the literal `0x22` inside the loop test. With the literal,
//     loop.c hoists the `li $a1,0x22` into the loop PREHEADER (after the duplicated entry test),
//     so reorg.c's guard branch has nothing local to take and instead COPIES the branch-target
//     insn (`addu $v0,$zero,$zero`) into its delay slot and redirects past it — a +1 shift that
//     also lets the loop-back branch steal the same insn (nop -> move). Materialising the
//     constant in the block BEFORE the entry test makes fill_simple_delay_slots take it from
//     the preceding insns, reproducing `beqz $v0,.L8014C7F4 / addiu $a1,$zero,0x22` and leaving
//     the loop-back delay slot a nop. `want` needs no pin — gcc lands it in $a1 on its own.


DEFINE_func_8014C6F4()  /* dedup: shared engine-core @0x8014C6F4 (src/shared) */


DEFINE_func_8014C860()  /* dedup: shared engine-core @0x8014c860 (src/shared) */


DEFINE_func_8014C88C()  /* dedup: shared engine-core @0x8014c88c (src/shared) */


DEFINE_func_8014C8C8()  /* dedup: shared engine-core @0x8014c8c8 (src/shared) */


DEFINE_func_8014C8F0()  /* dedup: shared engine-core @0x8014c8f0 (src/shared) */


DEFINE_func_8014C918()  /* dedup: shared engine-core @0x8014c918 (src/shared) */


DEFINE_func_8014C968()  /* dedup: shared engine-core @0x8014c968 (src/shared) */


DEFINE_func_8014C978()  /* dedup: shared engine-core @0x8014c978 (src/shared) */


DEFINE_func_8014C98C()  /* dedup: shared engine-core @0x8014c98c (src/shared) */


DEFINE_func_8014C99C()  /* dedup: shared engine-core @0x8014c99c (src/shared) */


DEFINE_func_8014CA00()  /* dedup: shared engine-core @0x8014ca00 (src/shared) */


DEFINE_func_8014CA14()  /* dedup: shared engine-core @0x8014ca14 (src/shared) */


DEFINE_func_8014CA70()  /* dedup: shared engine-core @0x8014ca70 (src/shared) */


DEFINE_func_8014CA88()  /* dedup: shared engine-core @0x8014ca88 (src/shared) */


DEFINE_func_8014CAE4()  /* dedup: shared engine-core @0x8014cae4 (src/shared) */


DEFINE_func_8014CAFC()  /* dedup: shared engine-core @0x8014cafc (src/shared) */


DEFINE_func_8014CB0C()  /* dedup: shared engine-core @0x8014cb0c (src/shared) */


DEFINE_func_8014CB1C()  /* dedup: shared engine-core @0x8014cb1c (src/shared) */


DEFINE_func_8014CB2C()  /* dedup: shared engine-core @0x8014cb2c (src/shared) */


DEFINE_func_8014CB58()  /* dedup: shared engine-core @0x8014cb58 (src/shared) */


DEFINE_func_8014CB68()  /* dedup: shared engine-core @0x8014cb68 (src/shared) */


DEFINE_func_8014CB7C()  /* dedup: shared engine-core @0x8014cb7c (src/shared) */


DEFINE_func_8014CB8C()  /* dedup: shared engine-core @0x8014cb8c (src/shared) */


DEFINE_func_8014CB9C()  /* dedup: shared engine-core @0x8014cb9c (src/shared) */


DEFINE_func_8014CBD8()  /* dedup: shared engine-core @0x8014cbd8 (src/shared) */


extern u16 D_80126CC4;

void func_8014CBE8(void)
{
    (*(s16 *)&D_80126CC4) = 0;
}


DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014cbf8 (src/shared) */


DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014cc28 (src/shared) */



extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014CD0C\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014cd0c (src/shared) */


DEFINE_func_8014CD80()  /* dedup: shared engine-core @0x8014cd80 (src/shared) */


DEFINE_func_8014CF04()  /* dedup: shared engine-core @0x8014CF04 (src/shared) */



extern void func_8014D0A4(s32);

void func_8014D04C(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014D0A4\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014d0a4 (src/shared) */




DEFINE_func_8014D12C()  /* dedup: shared engine-core @0x8014D12C (src/shared) */



DEFINE_func_8014D2A0()  /* dedup: shared engine-core @0x8014D2A0 (src/shared) */


extern int D_801C8540;
extern void func_8014D438(s32);

void func_8014D3E0(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014D438\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014d438 (src/shared) */


DEFINE_func_8014D4C0()  /* dedup: shared engine-core @0x8014d4c0 (src/shared) */


extern u8 D_801202A0[];
extern u8 D_80126720[];

s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
s32 func_8014C918(s32 a0, s32 a1);

DEFINE_func_8014D610()  /* dedup: shared engine-core @0x8014D610 (src/shared) */



extern void func_8014D790(s32);

void func_8014D738(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014D790\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014d790 (src/shared) */


  typedef struct EntD820_8014D820
  {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 x;
    u16 f8;
    u16 y;
    u16 fC;
    u16 z;
    u8 p10[0x10];
    s32 f20;
    u8 p24[0x34];
    s32 f58;
    u16 f5C;
    u16 f5E;
    u8 p60[0x10C - 0x60];
  } Ent_8014D820;
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014D820;

// @class: schedule
// @stuck: none — MATCH (304/304), symcheck SYMS-OK 12/12, and the whole-TU cc1 stage now compiles CLEAN
//
// ══════════════════════════════════════════════════════════════════════════════
// SESSION-22 RE-DERIVATION + THE ROOT-CAUSE FIX FOR THE "ASSEMBLER-STAGE" FAILURE
// ══════════════════════════════════════════════════════════════════════════════
// The SESSION-21 draft did reach match_one MATCH (re-verified this session, 304/304)
// and symcheck SYMS-OK — but the whole-binary build died with an opaque `Error 33`
// that was logged as "an ASSEMBLER-stage failure I did not finish diagnosing".
//
// IT IS NOT AN ASSEMBLER FAILURE. Stage-by-stage isolation of the real pipeline
// (cpp | cc1 | maspsx | as) over a scratch copy of src/ov_SC01_077/ov_SC01_077_after.c
// with this function spliced in place of its INCLUDE_ASM gives:
//     cpp    rc=0
//     cc1    rc=33   <-- ".../tu.c:1901: conflicting types for `Ent_8014D820'"
//                        "src/shared/engine_types.h:434: previous declaration of `Ent_8014D820'"
//     maspsx rc=0
//     as     rc=0    (only benign "used $at without .set noat" warnings)
// `33` is CC1's exit code, surfaced by the recipe's `set -o pipefail` (Makefile:560).
// Because `as` is the LAST stage in that pipe, make attributes the failure to the
// assembler — the same misread that made func_8012AAAC's "opaque Error 33" look
// assembler-shaped until it was isolated stage by stage.
//
// ROOT CAUSE: the draft declared `typedef struct Ent_8014D820 { ... } Ent_8014D820;` at FILE scope.
// `Ent_8014D820` is already a shared engine type (src/shared/engine_types.h:434,
//   typedef struct { u16 guard; u16 pad; u16 field; u8 rest[14]; } Ent_8014D820;
// a 20-byte struct), pulled into every overlay TU through
// src/ov_SC01_077/../shared/engine_core.h. gcc-2.7.2 rejects the redefinition
// outright (an ERROR, not the "type mismatch with previous external decl"
// WARNING that the rest of this TU is full of), so cc1 aborts.
//
// THE FIX, and why this shape: all three helper types are now declared at BLOCK
// scope inside func_8014D820 itself. That is strictly better than renaming to
// `Ent_8014D820` at file scope, because this function is an h_seq family EXEMPLAR
// with 138 members: a file-scope type name has to stay unique against 138 distinct
// overlay TUs *and* against whatever engine_types.h grows next, while a block-scope
// typedef can never collide with anything, in any TU, ever. It also matches the
// fleet convention — src/shared/engine_core.h contains ZERO `typedef struct`
// (all 0 of them); every DEFINE_ macro body uses engine_types.h types or local ones.
// Typedefs emit no code and create no allocno, so the move is byte-neutral:
// re-verified MATCH (304 ins) after the change, and the local DECLARATION ORDER
// below is untouched (§76 — declaration order is the dominant regalloc lever here).
//
// ══════════════════════════════════════════════════════════════════════════════
// THE BODY (SESSION-21 derivation, each lever re-verified this session)
// ══════════════════════════════════════════════════════════════════════════════
// func_8014D820 (304 ins, ov_SC01_077, h_seq family exemplar, 138 members).
// The whole residual off the SESSION-18 close=9 seed was a sched1 PERMUTATION
// inside ONE basic block (idx 79..101, the pos/desc set-up between the `slti 0x400`
// guard and the `currentLocationId` test): identical multiset of insns, identical
// register assignment, wrong positions. §66d-5 exactly — classed WIDTH [structural]
// at every waypoint and not structural at all.
//
// The lever (reusable): that block is 12 statements over a small dependency poset
// (load x0/y0/z0 -> add -> store pos.* / desc.*), so source ORDER is the only
// control and the space of linear extensions is enumerable. A dependency-respecting
// sweep found MATCH at
//   x0; pos.x; y0; pos.y; z0; tx; pos.z; tz; desc.x; desc.z; ty; desc.y
// i.e. all three loads and both pos stores first, then the two adds, then the desc
// stores, with the y accumulator (`ty`) computed LAST. No pin, no barrier, no
// permuter run. Eleven hand attempts on this window (SESSION-18) were inert or
// worse — hand-reading a 12-statement schedule permutation is the wrong tool;
// brute-forcing the linear extensions is the right one.
//
// Load-bearing levers (each re-verified by removal this session):
//   * the `a0v` launder (`__asm__("" : "=r"(a0v) : "0"(a0))`) — drop => 9 mismatched
//   * the `a2` $7 pin                                         — drop => 5
//   * the `a2x -> a2` launder (vs a plain copy)               — drop => 1
//   * `new_var3` (the s16 stash of dx feeding ratan2)         — drop => 2
//   * `new_var2` (the desc.y + 0x10 accumulator)              — drop => 2
// The `a2` pin's live range ENDS before the first `jal` (last use is
// `desc.z = a2[2] - a1[2]`), so it is §42e-CORRECTION / §74-safe to propagate.
//
// SYMBOLS (§58 rule 1/2): all five data externs use the canonical splat spelling and
// the engine_core.h type — `u8 D_801202A0[]`, `u8 D_801152A8[]`, `s16 D_801152AC`,
// `u8 D_8018585C[]`, `s16 currentLocationId`. symcheck: SYMS-OK, 12 symbols agree.
//
// The one deliberate divergence (§27 step 2 / rule 3): func_80135A4C's canonical
// extern is 4-arg but this call site sets only $a0-$a2, so the canonical decl is
// kept verbatim (it is also the TU's own spelling at ov_SC01_077_after.c:1651/1709)
// and the ARITY is cast at the call site.
//
// BANKING NOTE for the orchestrator (carried forward from SESSION-18, still true):
// 1 `self_decl_hdr` axis remains — DEFINE_func_8014D790's body declares
// func_8014D820, so that macro in engine_core.h needs the §85 return-axis widen
// (already applied). With the `Ent_8014D820` collision gone the TU's cc1 stage is clean.










extern s16 currentLocationId;
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x)
{

    extern u8 D_801202A0[];
    extern u8 D_8018585C[];
    extern u8 D_801152A8[];
    extern s16 D_801152AC;
  /* BLOCK-SCOPE types — see the header note. `Ent_8014D820` at file scope collides with
     src/shared/engine_types.h:434 and kills the TU's cc1 stage (exit 33). */
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014D820;
  typedef struct EntD820_8014D820
  {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 x;
    u16 f8;
    u16 y;
    u16 fC;
    u16 z;
    u8 p10[0x10];
    s32 f20;
    u8 p24[0x34];
    s32 f58;
    u16 f5C;
    u16 f5E;
    u8 p60[0x10C - 0x60];
  } Ent_8014D820;
  int new_var2;
  s16 new_var3;
register u16 *a2 __asm__("$7");
  V4_8014D820 out[3];
  V4_8014D820 pos;
  Desc desc;
  Ent_8014D820 *ent;
  Ent_8014D820 *p;
  s32 dx;
  s32 dz;
  s32 ex;
  s32 ez;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 ang;
  s32 x0;
  s32 y0;
  s32 z0;
  s32 tx;
  s32 tz;
  s32 ty;
  s32 r;
  s32 t;
  s32 u;
  s32 a0v;
__asm__ __volatile__("" : "=r"(a2) : "0"(a2x));
  t = a2[0];
  u = a1[0];
  dx = t - u;
__asm__ __volatile__("" : "=r"(a0v) : "0"(a0));
  new_var3 = (s16) dx;
  t = a2[2];
  u = a1[2];
  dz = t - u;
  if (((s16) (dx | dz)) == 0)
  {
    goto fail;
  }
  desc.x = dx;
  desc.y = a2[1] - a1[1];
  desc.z = a2[2] - a1[2];
  ent = *((Ent_8014D820 **) (a0v + 0x170));
  if (ent->f0 == 0)
  {
    goto fail;
  }
  if ((ent->f5C & 0x1000) == 0)
  {
    goto fail;
  }
  if (ent->f58 == 0)
  {
    goto fail;
  }
  if (((s32 (*)(s32, s32, s32)) func_80135A4C)(ent->f20, ent->f58, (s32) a1) == 0)
  {
    goto fail;
  }
  ex = ent->x - (*((u16 *) (a0v + 6)));
  ez = ent->z - (*((u16 *) (a0v + 0xE)));
  r1 = (s16) ratan2((s16) dz, new_var3);
  r2 = (s16) ratan2((s16) ez, (s16) ex);
  r3 = (s16) func_80012A60(r1, r2);
  if (0x400 <= r3)
  {
    goto fail;
  }
  desc.f20 = 0;
  desc.f1C = 0;
  desc.f18 = 0;
  x0 = ent->x;
  pos.x = x0;
  y0 = ent->y;
  pos.y = y0;
  z0 = ent->z;
  tx = x0 + desc.x;
  pos.z = z0;
  tz = z0 + desc.z;
  desc.x = tx;
  desc.z = tz;
  ty = (y0 + desc.y) + 8;
  desc.y = ty;
  if (currentLocationId != 0x3008)
  {
    for (p = (Ent_8014D820 *) D_801202A0; p < (Ent_8014D820 *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      func_80135888(p->f20, p->f58, (s32) (&pos), (s32) (&desc));
    }

  }
  else
  {
    ang = ratan2(((s16) x0) - ((s16) tx), ((s16) z0) - ((s16) tz)) & 0xFFF;
    func_800139C8(ang, D_8018585C, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_8018585C, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_8018585C, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = (Ent_8014D820 *) D_801202A0; p < (Ent_8014D820 *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      if (func_8014DCE0((s32) p, (s32) (&pos), (s32) (&out[0])) != 0)
      {
        __builtin_memcpy((void *) ((s32) (&desc)), (void *) ((s32) (&pos)), 8);
      }
    }

  }
  r = func_80133784(0, &pos, (s32) (&desc));
  if ((r == 0) || ((r == 0x2000) && (((*(u16 *) D_801152A8) | ((u16) D_801152AC)) == 0)))
  {
    ent->x = desc.x - desc.f18;
    ent->y = desc.y;
    ent->z = desc.z - desc.f20;
    desc.x -= pos.x;
    desc.y -= pos.y;
    desc.z -= pos.z;
    *((u16 *) (a0v + 6)) = a1[0] + desc.x;
    new_var2 = desc.y;
    new_var2 = new_var2 + 0x10;
    *((u16 *) (a0v + 0xA)) = a1[1] + new_var2;
    *((u16 *) (a0v + 0xE)) = a1[2] + desc.z;
  }
  else
  {
    *((u16 *) (a0v + 6)) = a1[0];
    *((u16 *) (a0v + 0xA)) = a1[1] + 0x10;
    *((u16 *) (a0v + 0xE)) = a1[2];
  }
  return 1;
  fail:
  *((s32 *) (a0v + 0x170)) = 0;

  return 0;
}


DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014dce0 (src/shared) */


DEFINE_func_8014DD8C()  /* dedup: shared engine-core @0x8014dd8c (src/shared) */



extern void func_8014DF94(s32);

void func_8014DF3C(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014DF94\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014df94 (src/shared) */


DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014e048 (src/shared) */


DEFINE_func_8014E284()  /* dedup: shared engine-core @0x8014e284 (src/shared) */



extern void func_8014E48C(s32);

void func_8014E434(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014E48C\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014e48c (src/shared) */


DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014e514 (src/shared) */


extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern s32 func_8014D2A0(s32 arg0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
//
// The return type is LOAD-BEARING here (see DECAY note below), so `void` is not an option.
// Fix = the §37/§124 ASM-LABEL ALIAS, the same lever that banked func_8014C4AC today
// (.run/sweep/*/func_8014C4AC.c): define the body under the C name aF8014E5B4 carrying
// __asm__("func_8014E5B4"). The emitted symbol is unchanged, the C identifier never collides
// with the macro's extern, and NO tracked header edit is needed — the engine_core.h:13392
// §85 return-axis widen described in the old banking note is now UNNECESSARY.
// Byte-checked: match_one MATCH (0 mismatches) before and after the rename.
// The alias line MUST travel with the body to every sibling overlay.
//
// DECAY FIX (2026-08-01, REDRAFT lane) — why the return type cannot be `void`: with `void`,
// gcc-2.7.2 drops the value axis entirely: no `addiu $v0,$zero,0x1`, no `addu $v0,$zero,$zero`
// at .L8014E674, and the `j .L8014E678` merge disappears (the taken path falls straight into
// the shared epilogue), which also frees $v0 so the last `lhu` lands in $v0 instead of the
// target's $v1. `s32` fixes all 23 mismatches at once.
//
// Keys (same D_801202A0 96-entry / stride-0x10C sweep as the func_8014CF04 and func_8014D2A0
// siblings, so most of it is the already-banked idiom):
//
//  (1) LOOP-BOUND DUALITY, register-relative BOTH ends (differs from func_8014CF04!). The
//      target computes `addiu $v1,$s1,0x6480` for the ENTRY guard and then a separate
//      `addu $s5,$v1,$zero` AFTER the guard branch for the loop-carried bound. That extra
//      copy is 1 whole instruction: the plain `e = p + 0x6480; if (p < e)` spelling folds it
//      away and compiles to 58 ins. The spelling that reproduces it is
//        `if (p < p + 0x6480) { e = p + 0x6480; ... }`
//      — the guard makes $v1, CSE turns the in-body `e = p + 0x6480` into a copy of it, and
//      regalloc does not coalesce (gcc-2.7.2 has no coalescing, regalloc.md K8). The back edge
//      then uses the register ($s5), NOT a rematerialised %hi/%lo(D_80126720) as in
//      func_8014CF04 — so do NOT reuse that sibling's absolute-bound half here.
//
//  (2) TWO INDUCTION VARIABLES, secondary base +0xE. `q = p + 0xE` carries every access except
//      the two that use the entry pointer itself (`*(u16 *)p` and `*(u8 **)(a0+0x17C) = p`):
//      offsets -0x8 / 0x0 / 0x12 / 0x4A / 0x4E off q  ==  0x6 / 0xE / 0x20 / 0x58 / 0x5C off p.
//      A single-pointer spelling is NOT equivalent: gcc emits ONE base and the function comes
//      out 56 ins (verified). The negative displacement is the tell that the second pointer is
//      in the source, not a compiler-made giv.
//
//  (3) REGISTER PINS ($16/$17) — the one non-obvious lever, and it is a genuine density
//      knife-edge (regalloc.md K2 / §RC-15). Unpinned, the .lreg reads
//        p:  9 refs / 24 insns -> floor_log2(9)*9/24 = 1.125
//        q:  8 refs / 22 insns -> floor_log2(8)*8/22 = 1.091
//      so p wins $s0 by ~3% and the whole function comes out with p/q SWAPPED (17 mismatches,
//      every one of them a bare $s0<->$s1 rename). The target wants q in $s0. Decl-order swap
//      does nothing (ties are not what decides it — p genuinely out-scores q). Rather than
//      hunt a +1-ref anchor (§RC-11 `#APP` would sit next to three delay slots that maspsx
//      fills: the `beqz $a1` slot, the `jal` slot and the `bnez` slot), pin both:
//        register u8 *p __asm__("$17");  register u8 *q __asm__("$16");
//      Both are callee-saved, so the live-across-`jal` range is §42e/§74-safe by construction
//      (the ov_SC03_099 func_8014D820 caveat only applies to caller-saved pins). Everything
//      else falls out naturally: a0->$s2, a1->$s3, a2->$s4, e->$s5.
//
//  (4) `t = *(s32 *)(q + 0x4A)` is loaded ONCE and reused as arg1 of func_80135888 — that is
//      why `lw $a1, 0x4A($s0)` sits at the zero-test rather than at the call.
//
// The func_80135888 decl below is byte-compatible with the one this TU already carries at
// ov_SC01_077_after.c:2303, so it is not a second conflict axis.

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

/* §37/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h:13392,
 * inside DEFINE_func_8014E48C()); the byte-true body must return s32. Aliasing the C name
 * sidesteps the RETURN-axis conflict with no header edit. This line MUST travel with the body. */
s32 aF8014E5B4(s32 a0, void *a1, void *a2) __asm__("func_8014E5B4");

DEFINE_func_8014E5B4()  /* dedup: shared engine-core @0x8014E5B4 (src/shared) */



extern void func_8014E6F8(struct SubE6F8*);

void func_8014E6A0(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014E6F8\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014e6f8 (src/shared) */


DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014e790 (src/shared) */


DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014e83c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_8014E934);

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014e98c (src/shared) */


DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014ea4c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_8014ED28);

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ed80 (src/shared) */


DEFINE_func_8014EE14()  /* dedup: shared engine-core @0x8014ee14 (src/shared) */



extern s32 func_8014F24C(struct SubF24C*);

void func_8014F1F4(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014F24C\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014f24c (src/shared) */


DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014f2e0 (src/shared) */


DEFINE_func_8014F3E8()  /* dedup: shared engine-core @0x8014f3e8 (src/shared) */


extern int D_801C8544;
extern s32 func_8014F4C0(s32);

s32 func_8014F468(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014F4C0\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F4C0()  /* dedup: shared engine-core @0x8014f4c0 (src/shared) */


extern int D_801C8544;
extern int func_8014F74C();

int func_8014F6F4(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014F74C\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014f74c (src/shared) */



// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801C8544; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);

void func_8014FA04(s32 a0)
{

    extern s32 D_801C8544;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $ra, 16($sp)\n"
        "lw    $v0, 68($a0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 1f\n"
        "addu  $v0, $zero, $zero\n"
        "lui   $a1, 0x1f80\n"
        "ori   $a1, $a1, 0x03fc\n"
        "addu  $t0, $a1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014fa70 (src/shared) */



extern s32 func_8014FC18(u8*);

void func_8014FBC0(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FC18\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014fc18 (src/shared) */



extern int func_8014FD54(int);

void func_8014FCFC(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FD54\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014fd54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014fdf4 (src/shared) */



DEFINE_func_8014FE60()  /* dedup: shared engine-core @0x8014FE60 (src/shared) */


DEFINE_func_8014FFDC()  /* dedup: shared engine-core @0x8014ffdc (src/shared) */


DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */


DEFINE_func_80150170()  /* dedup: shared engine-core @0x80150170 (src/shared) */


DEFINE_func_801502EC()  /* dedup: shared engine-core @0x801502ec (src/shared) */


DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_80150480);

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504d8 (src/shared) */


DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */


DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505fc (src/shared) */


extern void func_80147324(s32 a0);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_8014ADA8(s32 a0, s32 a1);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);



s32 func_801506A4(s32 arg0, s32 arg1) {

    extern u16 aD80078EB4 __asm__("D_80078EB4");
    extern void func_80150820(s32, s32);
    extern void func_8015086C(int);
    extern unsigned short D_8018586C[];
    extern unsigned short D_80185874[];
    extern unsigned short D_8018587C[];

    int mode;

    mode = ((struct Ent_801506A4 *)arg1)->unk0;
    ((struct Ent_801506A4 *)arg1)->unk5C |= 1;
    switch (mode) {
    case 0x31:
        ((void(*)(int))func_80147324)(0x452);
        ((void(*)(int, unsigned))func_8014ADA8)(((int)arg0), D_8018586C[((struct Ent_801506A4 *)arg1)->unk70]);
        ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 3, D_8018586C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0x32:
        if ((*(unsigned short*)&aD80078EB4) != 0) {
            ((void(*)(int))func_80147324)(0x452);
            ((void(*)(int, unsigned, int))func_8014BB24)(((int)arg0), D_80185874[((struct Ent_801506A4 *)arg1)->unk70], 1);
            ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 2, D_80185874[((struct Ent_801506A4 *)arg1)->unk70]);
        }
        break;
    case 0x33:
        ((void(*)(int))func_80147324)(0x452);
        ((void (*)(int, unsigned))func_80150820)(((int)arg0), D_8018587C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0xC5:
    case 0x27B:
        ((void(*)(int))func_80147324)(0x452);
        func_8015086C(((int)arg0));
        break;
    }
}


DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */


DEFINE_func_8015086C()  /* dedup: shared engine-core @0x8015086c (src/shared) */


DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508b4 (src/shared) */


DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508f8 (src/shared) */


  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8015094C;

extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {

    extern S16 D_801C7B94;
    extern s32 D_80185884;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern u8 D_80126948[];
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801C7B94;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_80185884, (s32)&arg);
    if (ret == 0) {
        {
            short cur = *(short *)(param_1 + 6);
            s32 diff = D_80126990 - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 6) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        {
            short cur = *(short *)(param_1 + 0xe);
            s32 diff = *(s32 *)(cam + 0x50) - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 0xe) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        (void)&pad1;
        return 1;
    }
    return 0;
}



extern s32 func_8014FA70(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);

void func_80150A70(s32 a0)
{

    extern s32 D_801C8544;
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $s0, 16($sp)\n"
        "addu  $s0, $a0, $zero\n"
        "sw    $ra, 20($sp)\n"
        "lh    $v1, 6($s0)\n"
        "lh    $v0, 136($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 10($s0)\n"
        "lh    $v0, 138($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 14($s0)\n"
        "lh    $v0, 140($s0)\n"
        "nop\n"
        "beq   $v1, $v0, 3f\n"
        "nop\n"
    "1:\n"
        "lw    $v0, 68($s0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 2f\n"
        "addiu $a0, $s0, 4\n"
        "lui   $a2, 0x1f80\n"
        "ori   $a2, $a2, 0x03fc\n"
        "addu  $t0, $a2, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "addu  $a0, $s0, $zero\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "addiu $a0, $s0, 4\n"
    "2:\n"
        "jal   func_80015978\n"
        "addiu $a1, $s0, 136\n"
    "3:\n"
        "lw    $ra, 20($sp)\n"
        "lw    $s0, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        ".set\treorder\n"
        : : : "memory");
}



// @class: regalloc-order
// @stuck: none — MATCH (fn-ptr table; split idx-1 into a $v0-pinned temp to stop (idx-1)*4 strength-reducing into a -4 load offset AND land the subtract in $v0)


void func_80150B28(int param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_80185888[])(void);
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80185888[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}


void func_80150B9C(void) {
}

DEFINE_func_80150BA4()  /* dedup: shared engine-core @0x80150ba4 (src/shared) */


DEFINE_func_80150BC8()  /* dedup: shared engine-core @0x80150bc8 (src/shared) */


DEFINE_func_80150C48()  /* dedup: shared engine-core @0x80150c48 (src/shared) */


DEFINE_func_80150CA0()  /* dedup: shared engine-core @0x80150ca0 (src/shared) */


DEFINE_func_80150CC4()  /* dedup: shared engine-core @0x80150cc4 (src/shared) */


DEFINE_func_80150CE4()  /* dedup: shared engine-core @0x80150ce4 (src/shared) */


DEFINE_func_80150D04()  /* dedup: shared engine-core @0x80150d04 (src/shared) */


DEFINE_func_80150D24()  /* dedup: shared engine-core @0x80150d24 (src/shared) */


DEFINE_func_80150D44()  /* dedup: shared engine-core @0x80150d44 (src/shared) */


DEFINE_func_80150D64()  /* dedup: shared engine-core @0x80150d64 (src/shared) */


DEFINE_func_80150D84()  /* dedup: shared engine-core @0x80150d84 (src/shared) */


DEFINE_func_80150DA4()  /* dedup: shared engine-core @0x80150da4 (src/shared) */


DEFINE_func_80150DC4()  /* dedup: shared engine-core @0x80150dc4 (src/shared) */


DEFINE_func_80150DE4()  /* dedup: shared engine-core @0x80150de4 (src/shared) */


DEFINE_func_80150E04()  /* dedup: shared engine-core @0x80150e04 (src/shared) */


DEFINE_func_80150E24()  /* dedup: shared engine-core @0x80150e24 (src/shared) */


DEFINE_func_80150E44()  /* dedup: shared engine-core @0x80150e44 (src/shared) */


DEFINE_func_80150E64()  /* dedup: shared engine-core @0x80150e64 (src/shared) */


DEFINE_func_80150E84()  /* dedup: shared engine-core @0x80150e84 (src/shared) */


DEFINE_func_80150EA4()  /* dedup: shared engine-core @0x80150ea4 (src/shared) */


DEFINE_func_80150EC4()  /* dedup: shared engine-core @0x80150ec4 (src/shared) */


void func_80150F78(void) {
}

DEFINE_func_80150F80()  /* dedup: shared engine-core @0x80150f80 (src/shared) */


DEFINE_func_80150FB4()  /* dedup: shared engine-core @0x80150fb4 (src/shared) */


DEFINE_func_80150FD8()  /* dedup: shared engine-core @0x80150fd8 (src/shared) */


DEFINE_func_80151014()  /* dedup: shared engine-core @0x80151014 (src/shared) */


DEFINE_func_80151038()  /* dedup: shared engine-core @0x80151038 (src/shared) */


DEFINE_func_80151070()  /* dedup: shared engine-core @0x80151070 (src/shared) */


DEFINE_func_80151094()  /* dedup: shared engine-core @0x80151094 (src/shared) */


void func_801510B8(void) {
}

void func_801510C0(void) {
}

DEFINE_func_801510C8()  /* dedup: shared engine-core @0x801510c8 (src/shared) */


DEFINE_func_801510EC()  /* dedup: shared engine-core @0x801510ec (src/shared) */


DEFINE_func_80151110()  /* dedup: shared engine-core @0x80151110 (src/shared) */


void func_80151130(void) {
}

DEFINE_func_80151138()  /* dedup: shared engine-core @0x80151138 (src/shared) */


DEFINE_func_8015115C()  /* dedup: shared engine-core @0x8015115c (src/shared) */


DEFINE_func_80151164()  /* dedup: shared engine-core @0x80151164 (src/shared) */


DEFINE_func_80151184()  /* dedup: shared engine-core @0x80151184 (src/shared) */


DEFINE_func_801511A8()  /* dedup: shared engine-core @0x801511a8 (src/shared) */


DEFINE_func_801511C4()  /* dedup: shared engine-core @0x801511c4 (src/shared) */


DEFINE_func_801511E0()  /* dedup: shared engine-core @0x801511e0 (src/shared) */


DEFINE_func_80151204()  /* dedup: shared engine-core @0x80151204 (src/shared) */


DEFINE_func_80151238()  /* dedup: shared engine-core @0x80151238 (src/shared) */


DEFINE_func_8015126C()  /* dedup: shared engine-core @0x8015126c (src/shared) */



/* func_80151664 — INTEGRATE lane.
 * Fleet canon (src/shared/engine_core.h:2924, inside DEFINE_func_8015410C()) declares
 *   extern void func_80151664(void);
 * so a `void func_80151664(s32 a0)` definition is `conflicting types` in every TU that
 * expands that macro (ov_SC01_077_after.c:3910 does).  Cookbook §73 PARAMS axis / §42:
 * keep the canonical (void) signature and read the incoming argument through a $a0 pin.
 * The decl below is reproduced verbatim so this file compiles the real conflict. */
extern void func_80151664(void);

extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();  /* fleet canon: K&R empty prototype (engine_core.h:75, :1682 defines it (void));
                                 * a prototyped (s32) decl is `conflicting types` in this TU. Arg still
                                 * passes in $a0 under default promotions -> codegen unchanged. */

void func_80151664(void) {
    register s32 a0v __asm__("$4");
    s32 s0;
    s32 v1;

    s0 = a0v;
    func_80154A74(s0, 0x11);
    func_801553C0(s0);
    func_801470AC((s32 *)s0);
    func_801472B4((void *)s0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(s0 + 0x3E) = 0;
    *(s16 *)(s0 + 0x40) = 0;
    *(s16 *)(s0 + 0x42) = 0;
    *(s8 *)(s0 + 0xDD) = 0;
    *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE;
    *(s16 *)(v1 + 0x10) = 0;
    *(s16 *)(s0 + 0x60) = 0x1000;
    *(s16 *)(s0 + 0x62) = 0x1000;
    *(s16 *)(s0 + 0x64) = 0x1000;
    func_801477E8((s32 *)s0, 0);
    func_80153C18(s0);
}


DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516f0 (src/shared) */


DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173c (src/shared) */


DEFINE_func_80151780()  /* dedup: shared engine-core @0x80151780 (src/shared) */


void func_80151878(void) {
}

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */


DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518d8 (src/shared) */


DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */




void func_80151944(void *a0) {

    extern void (*D_8018591C[])(void);
    D_8018591C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */


DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519c8 (src/shared) */


DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151ae4 (src/shared) */


DEFINE_func_80151B98()  /* dedup: shared engine-core @0x80151b98 (src/shared) */


DEFINE_func_80151C54()  /* dedup: shared engine-core @0x80151c54 (src/shared) */




void func_80151D24(void *a0) {

    extern void (*D_8018592C[])(void);
    D_8018592C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151d60 (src/shared) */


DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151db0 (src/shared) */


DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151e78 (src/shared) */


DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ecc (src/shared) */


DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151f38 (src/shared) */


DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151fb4 (src/shared) */




void func_80152058(void *a0) {

    extern void (*D_80185950[])(void);
    D_80185950[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152094()  /* dedup: shared engine-core @0x80152094 (src/shared) */



extern void func_80019064(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);

void func_801520DC(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_80185940;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80185940);
    func_801477E8(arg0, 0x40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146A6C(0x10, arg0, M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 0xA), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 0);
    func_80147324(0x441);
    func_80146CA0(arg0);
}


DEFINE_func_80152194()  /* dedup: shared engine-core @0x80152194 (src/shared) */


DEFINE_func_8015220C()  /* dedup: shared engine-core @0x8015220c (src/shared) */


DEFINE_func_80152254()  /* dedup: shared engine-core @0x80152254 (src/shared) */


DEFINE_func_801522CC()  /* dedup: shared engine-core @0x801522cc (src/shared) */




void func_80152370(void *a0) {

    extern void (*D_80185964[])(void);
    D_80185964[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801523AC()  /* dedup: shared engine-core @0x801523ac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (67 ins)

extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80019064(void *a0);
extern int func_80151204(int arg, int a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);


void func_801523F4(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern s32 D_800D58AC;
    extern u8 D_80185970[];
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_80185970; /* $s2 = &D_80185970 */

    ((void (*)(s32, s32))func_80146E90)(arg0, 0);
    func_80019064(&D_80062C04);
    ((void (*)(s32, s32))func_80151204)(arg0, *(s16 *)(arg0 + 0xF2));
    if ((s16)func_80012A60((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                           (s32)*(s16 *)(arg0 + 0xF4)) >= 0x401) {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D5880);
    } else {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D58AC);
    }
    func_80154A74(arg0, 0x16);
    ((void (*)(s32))func_80149020)(arg0);
    s0a = (s32)buf;
    ((void (*)(s32, s32, s32))func_8001382C)((*(u16 *)(arg0 + 0xF4) - *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF,
                  s2a, s0a);
    ((void (*)(s32, s32))func_80146DB8)(arg0, s0a);
    ((void (*)(s32, s32))func_801477E8)(arg0, *(s32 *)(s2a + 0xC));
    func_80147324(0x451);
    ((void (*)(s32))func_80146CA0)(arg0);
    (void)pad;
}


DEFINE_func_80152500()  /* dedup: shared engine-core @0x80152500 (src/shared) */


DEFINE_func_801525F4()  /* dedup: shared engine-core @0x801525f4 (src/shared) */




void func_80152698(void *a0) {

    extern void (*D_80185980[])(void);
    D_80185980[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526d4 (src/shared) */


DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */


DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */




void func_8015282C(void *a0) {

    extern void (*D_80185998[])(void);
    D_80185998[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152868()  /* dedup: shared engine-core @0x80152868 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_801528B0(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_80185988;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80185988);
    func_801477E8(arg0, 0xFFF00000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_8015294C()  /* dedup: shared engine-core @0x8015294c (src/shared) */


DEFINE_func_80152A08()  /* dedup: shared engine-core @0x80152a08 (src/shared) */


DEFINE_func_80152A50()  /* dedup: shared engine-core @0x80152a50 (src/shared) */


DEFINE_func_80152AC8()  /* dedup: shared engine-core @0x80152ac8 (src/shared) */




void func_80152B6C(void *a0) {

    extern void (*D_801859AC[])(void);
    D_801859AC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152ba8 (src/shared) */


DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152bf0 (src/shared) */


DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152c40 (src/shared) */


DEFINE_func_80152C80()  /* dedup: shared engine-core @0x80152c80 (src/shared) */




void func_80152D24(void *a0) {

    extern void (*D_801859C8[])(void);
    D_801859C8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152D60()  /* dedup: shared engine-core @0x80152d60 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_80152DA8(s32 arg0)
{

    extern s32 D_80062C14;
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_801859B8;
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_801859B8);
    func_801477E8(arg0, 0xFFE40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80152E4C()  /* dedup: shared engine-core @0x80152e4c (src/shared) */


DEFINE_func_80152EFC()  /* dedup: shared engine-core @0x80152efc (src/shared) */


DEFINE_func_80152F44()  /* dedup: shared engine-core @0x80152f44 (src/shared) */


DEFINE_func_80152FBC()  /* dedup: shared engine-core @0x80152fbc (src/shared) */




void func_80153060(void *a0) {

    extern void (*D_801859DC[])(void);
    D_801859DC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309c (src/shared) */


DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530e4 (src/shared) */


DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */


DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531bc (src/shared) */


DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */


DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327c (src/shared) */




void func_80153320(void *a0) {

    extern void (*D_801859F0[])(void);
    D_801859F0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335c (src/shared) */


DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533a4 (src/shared) */


DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */


DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */


DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534d8 (src/shared) */


DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */


DEFINE_func_801535F4()  /* dedup: shared engine-core @0x801535F4 (src/shared) */


DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369c (src/shared) */


DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536dc (src/shared) */


extern void func_80015954(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80153978(s32 a0, u16 *src);
extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_80153800(s32 a0) {

    extern void (*D_8011DB28)(s32 a0);
    extern u8 D_80126DB0[];
    extern u16 D_80126DB6;
    s32 s1 = a0;
    s32 s0;
    s32 s2;
    u8 bVar1;
    s16 buf1[4];
    s16 buf2[4];
    if (D_8011DB28 != 0) {
        ((void (*)(s32, s32))func_80015978)(s1 + 4, s1 + 0x88);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
ret0:
        return 0;
    }
    bVar1 = *(u8 *)(s1 + 0xDE);
    if (bVar1 >= 0x21) {
        s32 base = (s32)D_80126DB0;
        func_80015954(base, s1 + 4);
        memcpy((void *)(s1 + 0x88), (void *)base, 8);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
        *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6;
        return 0;
    }
    {
        register s32 m __asm__("$3") = bVar1 * 4;
        s2 = m;
        buf2[1] = *(u16 *)(s1 + 0xA2) - m;
    }
    for (s0 = 0; s0 < 0x80; s0++) {
        s32 ang = s0 * 0x200000;
        buf1[0] = 0;
        buf1[1] = 0;
        buf1[2] = s2;
        func_800139C8(ang >> 0x10, buf1, buf1);
        buf2[0] = *(u16 *)(s1 + 0xA0) + buf1[0];
        buf2[2] = *(u16 *)(s1 + 0xA4) + buf1[2];
        if (((s32 (*)(s32, void *))func_80153978)(s1, buf2) == 0) {
            goto ret0;
        }
    }
    *(u8 *)(s1 + 0xDE) = *(u8 *)(s1 + 0xDE) + 1;
    return 1;
}


DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */


extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);

typedef struct {
    u16 f0, f2, f4;
    s16 f6;
} Blk801539F8;

s32 func_801539F8(s32 a0, void *a1)
{
    Blk801539F8 buf1;
    Blk801539F8 buf2;
    Blk801539F8 buf3;
    s32 r1, r2, r3;

    buf1 = *(Blk801539F8 *)(a0 + 0xA0);
    buf2 = *(Blk801539F8 *)a1;
    buf1.f2 -= 4;
    r1 = func_80133784(0, &buf1, (s32)&buf2);
    if (r1 != 0x2000) {
        return 1;
    }
    buf1 = buf2;
    buf2.f2 += 8;
    r2 = func_80133784(0, &buf1, (s32)&buf2);
    if (r2 != r1) {
        return 1;
    }
    r3 = func_80133784(2, &buf2, (s32)&buf3);
    if (r3 != r2) {
        return 1;
    }
    *(s16 *)(a0 + 0x88) = buf2.f0;
    *(s16 *)(a0 + 0x8A) = buf2.f2;
    *(s16 *)(a0 + 0x8C) = buf2.f4;
    *(Blk801539F8 *)(a0 + 0x90) = *(Blk801539F8 *)(a0 + 0x88);
    return 0;
}


DEFINE_func_80153B58()  /* dedup: shared engine-core @0x80153b58 (src/shared) */


DEFINE_func_80153BD8()  /* dedup: shared engine-core @0x80153bd8 (src/shared) */


DEFINE_func_80153BF0()  /* dedup: shared engine-core @0x80153bf0 (src/shared) */


DEFINE_func_80153C18()  /* dedup: shared engine-core @0x80153c18 (src/shared) */


DEFINE_func_80153C30()  /* dedup: shared engine-core @0x80153c30 (src/shared) */


DEFINE_func_80153C44()  /* dedup: shared engine-core @0x80153c44 (src/shared) */


DEFINE_func_80153C74()  /* dedup: shared engine-core @0x80153c74 (src/shared) */


DEFINE_func_80153C8C()  /* dedup: shared engine-core @0x80153c8c (src/shared) */


DEFINE_func_80153C9C()  /* dedup: shared engine-core @0x80153c9c (src/shared) */


DEFINE_func_80153CBC()  /* dedup: shared engine-core @0x80153cbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (expected); dispatch-table %lo-fold via extern fn-ptr array, s0 holds param across both calls
extern void func_80019064(void *a0);

void func_80153CCC(S80153CCC *a0) {

    extern s32 D_80185A04;
    extern void (*D_80185A2C[])(void *a0);
    extern s16 D_8011DB0C;
    extern u16 D_8011F748;
    ((s32 (*)(s32))func_80019064)((s32)&D_80185A04);
    D_80185A2C[a0->idx](a0);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}


DEFINE_func_80153D34()  /* dedup: shared engine-core @0x80153d34 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (33/33)

extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 currentLocationId;

void func_80153D7C(s32 param_1)
{

    extern u8 D_80185A0C;
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_80185A0C);
    func_80149020((s32 *)param_1);
    *(u16 *)(param_1 + 0x244) = *(u16 *)(param_1 + 6);
    *(u16 *)(param_1 + 0x246) = *(u16 *)(param_1 + 10);
    *(u16 *)(param_1 + 0x248) = *(u16 *)(param_1 + 0xe);
    if (currentLocationId == 0x3075) *(u8 *)(param_1 + 0xde) = 0x14;
    else *(u8 *)(param_1 + 0xde) = 10;
    *(u8 *)(param_1 + 0xdf) = 0;
    __asm__ __volatile__("" ::: "memory");
    func_80146CA0((void *)param_1);
}


DEFINE_func_80153E00()  /* dedup: shared engine-core @0x80153e00 (src/shared) */


DEFINE_func_8015410C()  /* dedup: shared engine-core @0x8015410c (src/shared) */


DEFINE_func_80154134()  /* dedup: shared engine-core @0x80154134 (src/shared) */


DEFINE_func_80154150()  /* dedup: shared engine-core @0x80154150 (src/shared) */


DEFINE_func_80154190()  /* dedup: shared engine-core @0x80154190 (src/shared) */


DEFINE_func_801541D8()  /* dedup: shared engine-core @0x801541d8 (src/shared) */


DEFINE_func_80154218()  /* dedup: shared engine-core @0x80154218 (src/shared) */


DEFINE_func_80154274()  /* dedup: shared engine-core @0x80154274 (src/shared) */


DEFINE_func_801542A4()  /* dedup: shared engine-core @0x801542a4 (src/shared) */


DEFINE_func_801542DC()  /* dedup: shared engine-core @0x801542dc (src/shared) */


DEFINE_func_8015430C()  /* dedup: shared engine-core @0x8015430c (src/shared) */


DEFINE_func_80154358()  /* dedup: shared engine-core @0x80154358 (src/shared) */


DEFINE_func_80154418()  /* dedup: shared engine-core @0x80154418 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037_jr_8013F350", func_8015444C);
