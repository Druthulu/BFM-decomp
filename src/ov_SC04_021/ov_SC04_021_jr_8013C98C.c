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
extern s32 D_8018D4F8;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_8017F510[])(void);
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
extern s32 D_8018E67C;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_8018FAB8;
extern u16 D_800B99DA;
extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern void func_801508B4(void *a0);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern void func_8016E95C(void);
extern void func_801754A8(void);
extern void func_8013BC7C(void);
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern u8 D_800AEFD0;
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_8018D4F8;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017F24C)();
extern s16 (*D_8017F250)();
extern M2C_UNK (*D_8017F258)();
extern s32 (*D_8017F25C)();
extern s32 D_8018E678;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018D4FC;
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
extern void func_801299C8(s32 a, s32 b, s32 c);
extern void func_8012944C(void);
extern unsigned short D_800B99F0;
extern void func_8012A328(void);
extern void func_80053308(s32);
extern s32 func_80012F74(s32, s32, s32, s32);  /* canonical s32 (engine_core); (s16)-cast the return for the sll/sra */
extern void GsSetRefView2L(void *);
extern s8 D_801150D6;            /* canonical (engine_core macro): s8 — access via *(u8*)& for lbu */
extern u8 D_80127504;
extern s32 D_80126E60[];
extern s32 D_80126F04[];
extern u8 D_80126948[];          /* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_80126FA8[];
extern u8 D_800AF630[];          /* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_800AE688[];
extern s32 D_801151D4;           /* canonical (10 siblings): scalar s32 — store (s32)ptr */
extern void func_8012A018(s32 a, s32 b);
extern void func_80129FF4(void);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern void func_8012A048(void *a0, s32 a1, u8 a2);
extern void *memcpy(void *, const void *, unsigned int);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);
extern void func_8012A0E0(void);
extern s8 D_801150D6;
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
extern s8 D_801152C0;
extern void func_8012A2F4(void);
extern s16 D_80127080;
extern s16 D_801152C2;
extern void func_8012A304(s32 a0, s32 a1);
extern s32 D_801151D4;
extern void func_8012A4BC(void);
extern void func_8012A62C(s32);
extern void func_8012A5F8(void (*a0)(void), s32 a1);
extern void func_8012A62C(s32 a0);
extern void func_8012A7D4(void *a0, void *a1);
extern s32 func_8012A6D0(void *a0, void *a1);
extern s16 func_8012A68C(void);
extern s16 func_8012A79C(s16 *a0, s16 *a1);
extern s16 func_8012A758(void);
extern s32 ratan2(s32 a0, s32 a1);
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
extern M2C_UNK D_8017F5A4;
extern void func_8012ACA0(void *arg0);
extern s32 func_8012ACE0(void *o);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012AD50(void * arg0);
extern void func_8012AD64(s32 *a0, s16 a1);
extern void func_8012AD6C(void *a0);
extern void func_8012AD80(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 *D_80126B78;
extern s32 *D_80126B90;
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
extern void func_8012C194(void);
extern void func_8001CFDC(s32 a, s32 b);
extern void func_8012C1B8(void);
extern u8 D_800B3DF0[];
extern s32 func_8012C1DC(s32 a0);
extern void func_8012C218(void *a0);
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
extern s32 func_8012C820(u8 *a0);
extern s32   D_80182A88;
extern s16 D_801270C4;
extern u16   D_801274E4[];
extern s32   D_8011DB08;
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
extern int func_8012D664(int arg0, int arg1, int arg2);
extern s32 func_8012D714(s32 param_1, u32 param_2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern M2C_UNK D_8017F5BC;
extern M2C_UNK D_8017F5C4;
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
extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012E8C4(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_8017F5CC;
extern void func_8012E9C0(int param_1);
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
extern unsigned char D_8017F5E8[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_8017F5F4[];
extern void func_8012F8C8(u8* arg0);
extern void func_8012F91C(s32 a0);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_80131CA8(s32 a0, s32 a1);
extern void func_8012F968(s32 param_1);
extern void func_801319E0(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012FB54(s32 a0);
extern void func_8012FC30(s32 a0);
extern void func_8012FCA4(int a0);
extern s32 func_8012FCC4(s32 param_1);
extern void func_8012FDA8(int param_1);
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
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80130740(void *a0, u16 *a1);
extern s32 func_801312D0(s32 a0, void *a1);
extern void func_801307B0(s32 a0);
extern void func_80130858(s32 a0);
extern void func_80130898(u8 *a0);
extern void func_801308DC(s32 a0);
extern void func_80166244();
extern void func_80130974(int param_1);
extern void func_80130AC4(s32 a0);
extern int  func_80131A34(int a0, int a1);
extern void func_80130AF0(int param_1);
extern void (*D_8017F608[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_8017F658[];
extern s16 D_8017F688[];
extern s16 D_8017F6E8[];
extern s16 D_8017F6F0[];
extern s16 D_8017F710[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_8017F748[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_8017F7A0[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_8017F7E8[])(void);
extern void func_80131F28(void *a0);
extern void (*D_8017F7F0[])(void);
extern void func_80131F64(void *a0);
extern void (*D_8017F7F8[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_8017F800[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_8017F7A8;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_8017F7C8;
extern void func_801321B0(int param_1);
extern int D_8017F7D8;
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
extern s32 D_8018E6E8;
extern s32 D_8018E6EC[];
extern int D_8018E6F0;
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern void func_80136BC4(s32);
extern void func_8013373C(s16 arg0);
extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);
extern s32 func_80133CD4();
extern s32 func_8013435C(s16 *a0, s16 *a1, s32 a2, s16 *a3);
extern s32 func_801343C4(s32 angle, s32 p1, s32 p2);
extern s32 func_80134510(s32 param);
extern s32 func_801345F8(s32 arg);
extern s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
extern s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
extern s32 func_80135004(s32 arg0, s32 p1, s32 p2);
extern u8 D_8017F80C;
extern u8 D_8017F808;
extern s16 *D_8017F810;
extern u8 D_8017F814;
extern int D_8018E6E8;
extern u16 D_8018E6F8;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_8017F810;   /* holds a pointer value (*(u16**)&D_8017F810) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_8017F824[])(void);
extern void func_80136C54(void);
extern s32 func_80136C90();
extern void func_80136D00(void);
extern void SetLineG2(void *);
extern void func_80136D08(s32 arg0, s32 arg1);
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
extern int D_8017F878;
extern int D_801269F0;
extern void func_80138BE0(int p);
extern void func_80137B80(void);
extern void func_801392FC();
extern void func_801397B0(s32 a0);
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);
extern u16 D_800B99D8;
extern void func_80137BD8(s32 a0);
extern unsigned char D_80126A0E;
extern short D_80126A0A;
extern s16 D_801269F4;
extern int D_800A5E60;
extern int func_80137D08(int arg0, int arg1, short arg2);
extern void func_80137FD8(s32 a0, s32 a1, s32 a2, s32 a3);
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
extern void (*D_8017F87C[])(void);
extern void func_80138C30(void *a0);
extern s32 func_80139BE0(s32);
extern s32 func_80138C60(s32 arg0);
extern void func_8013A9F8(s32 a0, s32 a1);
extern void func_80138D58(s32 a0, u16 a1);
extern s32 func_80014E80(s32 a0, s32 a1);
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
extern s32 D_80127548[];
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
extern u8 D_8017F8C0;
extern u8 D_8017F904;
extern void GsSortSprite(void *a0, u8 *a1, s32 a2);
extern void func_801397B0(s32 arg0);
extern void func_8013A8B0(s32 *a0);
extern void func_80139914(s32 arg0);
extern u16 D_80126A08;
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
extern void func_8013A380(void);
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
extern s32 D_800A5E60;
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
extern s16 D_800D45F4[];   /* src0 (flat: [2*i]=x, [2*i+1]=y) */
extern u8  D_8017F948[];   /* sign table, alt (when a1 < 0xC00) */
extern void func_8013AD38(void *flag, s32 a1, void *out2, void *out3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern s16 D_8017F9C0, D_8017F9C2, D_8017F9C4, D_8017F9C6, D_8017F9C8, D_8017F9CA;
extern u16 D_800D45F6;
/* ==== end §8b carried decl layer ==== */


/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */

extern void func_80016714(void *a0, s32 a1);
extern s32 D_8018E760;
extern s32 D_801269D4;
extern s32 D_801269C8;

#include "../shared/ov/func_8013C98C__baeed09f.h"


extern M2C_UNK D_80062BC0;
extern s32 D_8018E760;
extern s8 D_8018E764;
extern s8 D_8018E765;

#include "../shared/ov/func_8013C9C4__564fe0e7.h"




extern s32 D_8018E760;
extern s8 D_8018E764;
extern s8 D_8018E765;
extern s32 D_801269C8;
extern s32 D_801269D4;
#include "../shared/ov/func_8013CA14__83788c45.h"



extern s32 D_8018E784;
extern s32 D_8018E778;
extern s32 D_8018E77C;
extern s32 D_8018E788;

#include "../shared/ov/func_8013CABC__f4f19b4f.h"



extern s32 D_8018E778;
extern s32 D_8018E77C;
extern s32 D_8018E780;
extern s32 D_8018E784;
extern s32 D_8018E788;

#include "../shared/ov/func_8013CAE8__1db1a1b9.h"



extern s32 D_8018E784;
extern s32 D_8018E788;
extern s32 D_8018E7B0;
extern s32 D_8018E7B4;

#include "../shared/ov/func_8013CB20__1985aa20.h"



extern s32 D_8018E7B0;
extern s32 D_8018E7B4;
extern s32 D_8018E788;
extern s32 D_8018E784;

#include "../shared/ov/func_8013CB5C__05c30a55.h"




extern s16 currentLocationId;
extern s32 D_8018E788;
extern s32 D_8018E780;
extern s32 D_8018E784;
extern s32 D_8018E778;
extern s32 D_8018E77C;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

#include "../shared/ov/func_8013CB84__8d303dd8.h"


// @class: struct
// @stuck: none — MATCH (63 ins)
//
// Sets up 3 consecutive 16-byte records (at D_800A5E88[0..2]: {s32 a,b,c; u8 d,e,f,g})
// and registers each via func_80028620(i, &rec[i]).
//
// Keys to the byte match:
//  (1) The base pointer is anchored at D_800A5E94 (= &rec0.d, i.e. rec0+0xC) and materialized
//      via a NON-volatile inline-asm `la` so gcc treats it as OPAQUE (not a const symbol).
//      Opacity is what makes the base-relative stores FOLD into `off($s0)` instead of
//      const-folding to a direct `lui $at; sw %lo(sym)`. A `__asm__ __volatile__` re-tie
//      barrier (cookbook §21) also launders base, but the barrier pins the schedule and
//      pushes the first call's `a0=0` down; the non-volatile `la` avoids the barrier so the
//      scheduler still hoists `addu $a0,$zero,$zero` to the top (matches target idx1).
//  (2) rec0's inner fields (E8C/E90 ints, E95/E96 bytes) are written as DIRECT globals, not
//      base-relative — in the entry block gcc emits them as `lui $at; sw/sb %lo(sym)`. Only
//      the address-taken E88 (= call arg base-0xC) and the offset-0 E94 fold via $s0. rec1/rec2
//      fold entirely (base opaque, all offsets small).
//  (3) The three source bytes per record are loaded into temps t0/t1/t2 BEFORE the stores so
//      gcc keeps them live in three registers ($v1/$a2/$a3) as a group (not one-at-a-time in $v0).
//  (4) Statement order matches the target scheduler: rec1 stores b(=7) before the loads;
//      rec2 stores b(=-0x12) AFTER the loads (the differing constants drive the scheduler).
#include "common.h"


#include "../shared/ov/func_8013CF68__94315c4c.h"




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_8018E790;
extern s32 D_8018E778;
extern s32 D_8018E794;
extern s32 D_8018E784;
extern void func_8013D9B0();

#include "../shared/ov/func_8013D064__10bd61e3.h"




extern void func_8013D9B0();
extern s32 D_8018E784;

#include "../shared/ov/func_8013D13C__3ffb44f9.h"



extern s32 D_8018E790;

#include "../shared/ov/func_8013D164__022cc720.h"



#include "../shared/ov/func_8013D178__421ba659.h"



// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_8018FAB2;
extern u8 D_8018FB2C;
extern u8 D_8018F9DA;
extern u8 D_8018FA94;
extern u8 D_8018F9B8;
extern u8 D_8018F9D9;
extern s32 D_8018FA98;

#include "../shared/ov/func_8013D330__3ba2802e.h"




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_8018E768;
extern void *D_8018E76C;
extern void *D_8018E770;
extern s32 D_8018E798;
extern s32 D_8018E79C;
extern s32 D_8018E7A0;
extern s32 D_8018FA0C[];

extern u8 D_8017FAB8[];
extern u8 D_8017FB60[];
extern u8 D_8017FA10[];
extern u8 D_8017FB0C[];
extern u8 D_8017FB8C[];
extern u8 D_8017FA64[];

extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

#include "../shared/ov/func_8013D3D4__f5857947.h"



   /* 9-byte, align-1 -> unaligned block copy */


extern s32 D_8018E798;
extern s32 D_8018E780;


extern u8 D_8018FAB2;
extern u8 D_8018FB2C;
extern u8 D_8018F9DA;
extern u8 D_8018FA94;
extern u8 D_8018F9B8;
extern u8 D_8018F9D9;


extern s32 D_8018FA98;
extern s32 D_8018E794;
extern s32 D_8018E790;
extern s32 D_8018E778;
extern s32 D_8018E784;
extern s32 D_8018E788;

extern void *D_8018E768;
extern s32 D_8018E7A0;
extern void *D_8018E770;

#include "../shared/ov/func_8013D53C__93ed5239.h"








extern void func_800599B8(u16*);

#include "../shared/ov/func_8013D8FC__392f2627.h"


extern void *D_8018E76C;
extern s32 D_8018E784;
extern void func_800599B8(u16*);

#include "../shared/ov/func_8013D9B0__4b66f7ea.h"



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_8018E770)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_8018E770;
extern s16 *D_8018E774;
extern s32 D_8018E784;
extern s32 D_8018E7A4;
extern s32 D_8018E7A8;
extern s32 D_8018E7AC;

extern void func_8013DD68(void);

#include "../shared/ov/func_8013DBE4__036a62a6.h"


// @class: regalloc-order
// @stuck: none — MATCH (187 ins). Levers: struct-assign DRAWENV copy (align via type); pbase local for $s2-relative D_800B9A02; two-biv SPRT loop (q anchored one-above -> gcc re-anchors, no bare-deref); P_TAG_8013DD68 addPrim; single p var coalesces puVar7->puVar15; pins uVar2=$v1,iVar14=$a3,c5=$t3; biv-increment order sets q-init-before-puVar10-init; Buf_8013DD68 0x68 -> frame 0xA0.

              /* 0x5C copy unit, align 4 */
  /* -> frame 0xA0 (gcc adds 0x10 for the struct-copy) */


#define IDVAL (*(u16 *)(pbase + 0xA3D2))
#define OTE ((P_TAG_8013DD68 *)(D_800BA0E4 + IDVAL * 0x10))

#include "../shared/ov/func_8013DD68__5d222fe2.h"




extern s32 D_8018E78C;

#include "../shared/ov/func_8013E054__b97180c3.h"


#include "../shared/ov/func_8013E064.h"

#include "../shared/ov/func_8013E0FC.h"

#include "../shared/ov/func_8013E194.h"

#include "../shared/ov/func_8013E22C.h"

#include "../shared/ov/func_8013E298.h"

#include "../shared/ov/func_8013E2C4.h"

#include "../shared/ov/func_8013E370.h"

#include "../shared/ov/func_8013E410.h"

#include "../shared/ov/func_8013E448.h"

#include "../shared/ov/func_8013E4B4.h"

#include "../shared/ov/func_8013E558.h"

#include "../shared/ov/func_8013E588.h"


extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);


#include "../shared/ov/func_8013E5E8__ae7678cf.h"


#include "../shared/ov/func_8013E67C.h"


// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_80180618;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_801805F0;
extern s16 D_801805F2;
extern unsigned short D_80115112;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

#include "../shared/ov/func_8013E6AC__e4884635.h"


#include "../shared/ov/func_8013E814.h"

// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

#include "../shared/ov/func_8013E83C__624fc4aa.h"



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_80180618/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80180618 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

#include "../shared/ov/func_8013E958__fb86651d.h"



#include "../shared/ov/func_8013EA54.h"


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

extern short D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_8011511A;
extern u16 D_8011511E;
extern short D_80115128;
extern unsigned short D_80115112;
extern s16 D_8011512A;
extern s32 D_80115130;
extern unsigned char D_801805F4;

#include "../shared/ov/func_8013EB7C__5c31e6e7.h"


#include "../shared/ov/func_8013ED6C.h"

extern short D_800B9A02;
extern unsigned short D_80115112;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern s16 D_801805F0;
extern s16 D_801805F2;
extern unsigned char D_801805F4;
extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_801805F2` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_801805F0` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.




#include "../shared/ov/func_8013EE10__dc80305f.h"











extern s16 D_800B9A02;
extern s32 D_801151D0;
extern E4  aD80115188[] __asm__("D_80115188");
extern u16 D_80115124;
extern u16 D_80115112;
extern s16 D_801805F2;
extern s16 D_801805F0;

extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);

#include "../shared/ov/func_8013EF88__48bc7f10.h"



// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_801805F4;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

#include "../shared/ov/func_8013F138__67cef5a4.h"


#include "../shared/ov/func_8013F1BC.h"

#include "../shared/ov/func_8013F244.h"

