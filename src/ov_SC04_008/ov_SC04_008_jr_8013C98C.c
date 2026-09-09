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
extern s32 D_8018FA4C;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_8017ED5C[])(void);
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
extern s32 D_80190BB4;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_80193450;
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
extern int D_8018FA4C;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017EA98)();
extern s16 (*D_8017EA9C)();
extern M2C_UNK (*D_8017EAA4)();
extern s32 (*D_8017EAA8)();
extern s32 D_80190BB0;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018FA50;
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
extern M2C_UNK D_8017EDF0;
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
extern s32   D_801822D4;
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
extern M2C_UNK D_8017EE08;
extern M2C_UNK D_8017EE10;
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
extern int D_8017EE18;
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
extern unsigned char D_8017EE34[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_8017EE40[];
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
extern void (*D_8017EE54[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_8017EEA4[];
extern s16 D_8017EED4[];
extern s16 D_8017EF34[];
extern s16 D_8017EF3C[];
extern s16 D_8017EF5C[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_8017EF94[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_8017EFEC[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_8017F034[])(void);
extern void func_80131F28(void *a0);
extern void (*D_8017F03C[])(void);
extern void func_80131F64(void *a0);
extern void (*D_8017F044[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_8017F04C[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_8017EFF4;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_8017F014;
extern void func_801321B0(int param_1);
extern int D_8017F024;
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
extern s32 D_80190C20;
extern s32 D_80190C24[];
extern int D_80190C28;
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
extern u8 D_8017F058;
extern u8 D_8017F054;
extern s16 *D_8017F05C;
extern u8 D_8017F060;
extern int D_80190C20;
extern u16 D_80190C30;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_8017F05C;   /* holds a pointer value (*(u16**)&D_8017F05C) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_8017F070[])(void);
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
extern int D_8017F0C4;
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
extern void (*D_8017F0C8[])(void);
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
extern u8 D_8017F10C;
extern u8 D_8017F150;
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
extern u8  D_8017F194[];   /* sign table, alt (when a1 < 0xC00) */
extern void func_8013AD38(void *flag, s32 a1, void *out2, void *out3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern s16 D_8017F20C, D_8017F20E, D_8017F210, D_8017F212, D_8017F214, D_8017F216;
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
extern s32 D_80190C98;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_80190C98, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern M2C_UNK D_80062BC0;
extern s32 D_80190C98;
extern s8 D_80190C9C;
extern s8 D_80190C9D;

void func_8013C9C4(void * arg0)
{
    D_80190C98 = arg0;
    D_80190C9C = 0;
    D_80190C9D = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}




extern s32 D_80190C98;
extern s8 D_80190C9C;
extern s8 D_80190C9D;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_80190C98;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_80190C9D;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_80190C9C)) * 2) + D_80190C98);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_80190C9D = (unsigned char) p[1];
      D_80190C9C = D_80190C9C + 1;
      if (D_80190C9D == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_80190C9C = 0;
        *base = 0;
      }
    }
    else
    {
      D_80190C9D = c - 1;
    }
  }
  return;
}



extern s32 D_80190CBC;
extern s32 D_80190CB0;
extern s32 D_80190CB4;
extern s32 D_80190CC0;

void func_8013CABC(void) {
    D_80190CBC = 1;
    D_80190CB0 = 1;
    D_80190CB4 = 0;
    D_80190CC0 = 1;
}



extern s32 D_80190CB0;
extern s32 D_80190CB4;
extern s32 D_80190CB8;
extern s32 D_80190CBC;
extern s32 D_80190CC0;

void func_8013CAE8(void) {
    D_80190CB0 = 1;
    D_80190CBC = 0;
    D_80190CB4 = 0;
    D_80190CB8 = -1;
    D_80190CC0 = 0;
}



extern s32 D_80190CBC;
extern s32 D_80190CC0;
extern s32 D_80190CE8;
extern s32 D_80190CEC;

void func_8013CB20(void)
{
    D_80190CE8 = D_80190CC0;
    D_80190CEC = D_80190CBC;
    D_80190CC0 = 1;
    D_80190CBC = 0;
}



extern s32 D_80190CE8;
extern s32 D_80190CEC;
extern s32 D_80190CC0;
extern s32 D_80190CBC;

void func_8013CB5C(void) {
    D_80190CC0 = D_80190CE8;
    D_80190CBC = D_80190CEC;
}




extern s16 currentLocationId;
extern s32 D_80190CC0;
extern s32 D_80190CB8;
extern s32 D_80190CBC;
extern s32 D_80190CB0;
extern s32 D_80190CB4;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_80190CC4;
    extern s32 D_80190CD0;
    extern s32 D_80190CD8;
    extern s32 D_80193430;
    extern s32 D_801933B0;
    extern s32 D_801933A4[];
    extern u8 D_80193371;
    extern u8 D_801934BE;
    extern u8 D_8019342C;
    extern Rec12 D_8017F42C[];
    extern Rec9 D_8017F3F4[];
    extern u8 D_80193408;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_80193430 = 0;
    if (D_80190CC0 == 0 && s0 != D_80190CB8) {
        ta = D_8017F42C[s0].a;
        tb = D_8017F42C[s0].b;
        tc = D_8017F42C[s0].c;
        D_80190CB8 = s0;
        D_80193371 = tc;
        D_801934BE = ta;
        D_8019342C = tb;
        *(Rec9 *)&D_80193408 = D_8017F3F4[s0];
        D_80190CBC = 1;
        D_80190CB0 = 1;
        if (D_80190CD0 & 2) {
            if (s0 == 4) { D_801933A4[0] = 0x100; D_801933B0 = 0x80; }
            if (s0 == 0) { D_801933A4[0] = 0x100; D_801933B0 = 0; }
        }
    }
    if (D_80190CBC != 0) {
        t = D_80190CB0 - 1;
        D_80190CB0 = t;
        if (t == 0) {
            if (D_80190CC0 == 0) {
                if ((D_80190CD0 & 2) && s0 == 4) {
                    if (D_80190CD8 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_80190CD8 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_80190CB0 = 2;
                if (D_80190CBC != 0) {
                    if (D_80190CD0 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801933B0;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801933B0;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_80190CD0 & 2) {
                    if (s0 == 4) D_801933B0 = 0;
                    if (s0 == 0) D_801933B0 = 0x80;
                }
            } else {
                if (D_80190CD8 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_80190CB0 = 1;
            }
        }
    }
    D_80190CC4 = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_80190CBC != 0) D_80190CC4 = D_80190CB4;
            else D_80190CC4 = 0x1F;
        } else if (s0 == 4) {
            if (D_80190CBC != 0) D_80190CC4 = 0x1F - D_80190CB4;
            else D_80190CC4 = 0;
        }
    }
}


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


void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_80193368;
    extern u8 D_80193369;
    extern u8 D_8019336A;
    extern u8 D_8019336B;
    extern u8 D_8019336C;
    extern u8 D_8019336D;
    extern u8 D_8019336E;
    extern u8 D_8019336F;
    extern u8 D_80193370;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));  // !FAKE: instruction la — NEEDED DIFFERS (P36 rung B tus3)

    *(s32 *)(base - 0xC) = 0;
    t0 = D_80193368; t1 = D_80193369; t2 = D_8019336A;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_8019336B; t1 = D_8019336C; t2 = D_8019336D;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_8019336E; t1 = D_8019336F; t2 = D_80193370;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_80190CC8;
extern s32 D_80190CB0;
extern s32 D_80190CCC;
extern s32 D_80190CBC;
extern void func_8013D9B0();

void func_8013D064(void)
{
    if (D_80190CC8 != 0) {
        if (D_80190CC8 != 2) {
            if (((D_80190CC8 < 3) && (D_80190CC8 == 1)) &&
                (D_80190CCC = D_80190CCC + 1, 0x23a < D_80190CCC)) {
                D_80190CB0 = D_80190CC8;
                D_80190CC8 = 2;
            }
        } else {
            D_80190CB0 = D_80190CB0 + -1;
            if (D_80190CB0 == 0) {
                D_80190CB0 = D_80190CC8;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_80190CBC == 0) {
                    D_80190CC8 = D_80190CC8 + 1;
                }
            }
        }
    }
    return;
}




extern void func_8013D9B0();
extern s32 D_80190CBC;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_80190CBC;
}



extern s32 D_80190CC8;

void func_8013D164(void) {
    D_80190CC8 = 1;
}



void func_8013D178(void) {

    extern u8 D_80193368;
    extern u8 D_80193369;
    extern u8 D_8019336A;
    extern u8 D_8019336B;
    extern u8 D_8019336C;
    extern u8 D_8019336D;
    extern u8 D_8019336E;
    extern u8 D_8019336F;
    extern u8 D_80193370;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    extern unsigned char D_80193408, D_80193409, D_8019340A, D_8019340B, D_8019340C, D_8019340D, D_8019340E, D_8019340F, D_80193410;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus3)

    p = &D_80193368; v = *p; t = D_80193408;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80193369; v = *p; t = D_80193409;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336A; v = *p; t = D_8019340A;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336B; v = *p; t = D_8019340B;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336C; v = *p; t = D_8019340C;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336D; v = *p; t = D_8019340D;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336E; v = *p; t = D_8019340E;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_8019336F; v = *p; t = D_8019340F;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80193370; v = *p; t = D_80193410;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}



// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_8019344A;
extern u8 D_801934BE;
extern u8 D_80193372;
extern u8 D_8019342C;
extern u8 D_80193350;
extern u8 D_80193371;
extern s32 D_80193430;

void func_8013D330(void) {
    if ((D_8019344A & 0xff) != D_801934BE) {
        D_8019344A = ((D_8019344A & 0xff) < D_801934BE) ? (D_8019344A + 1) : (D_8019344A - 1);
    }
    if ((D_80193372 & 0xff) != D_8019342C) {
        D_80193372 = ((D_80193372 & 0xff) < D_8019342C) ? (D_80193372 + 1) : (D_80193372 - 1);
    }
    if ((D_80193350 & 0xff) != D_80193371) {
        D_80193350 = ((D_80193350 & 0xff) < D_80193371) ? (D_80193350 + 1) : (D_80193350 - 1);
    }
    D_80193430 = 1;
}




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_80190CA0;
extern void *D_80190CA4;
extern void *D_80190CA8;
extern s32 D_80190CD0;
extern s32 D_80190CD4;
extern s32 D_80190CD8;
extern s32 D_801933A4[];

extern u8 D_8017F304[];
extern u8 D_8017F3AC[];
extern u8 D_8017F25C[];
extern u8 D_8017F358[];
extern u8 D_8017F3D8[];
extern u8 D_8017F2B0[];

extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_80190CD0 = param_2;
    D_80190CD4 = (param_2 >> 2) & 3;
    D_80190CD8 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_80190CA0 = D_8017F304;
        D_80190CA4 = D_8017F3AC;
        D_80190CA8 = D_8017F25C;
    } else {
        D_80190CA0 = D_8017F358;
        D_80190CA4 = D_8017F3D8;
        D_80190CA8 = D_8017F2B0;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_80190CD8 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_80190CD0 & 2) != 0) {
            D_801933A4[0] = 0x140;
            D_801933A4[3] = 0x80;
            if (p[0x37] == 4) {
                D_801933A4[0] = 0x140;
                D_801933A4[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801933A4[0] = 0x140;
                D_801933A4[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */


extern s32 D_80190CD0;
extern s32 D_80190CB8;


extern u8 D_8019344A;
extern u8 D_801934BE;
extern u8 D_80193372;
extern u8 D_8019342C;
extern u8 D_80193350;
extern u8 D_80193371;


extern s32 D_80193430;
extern s32 D_80190CCC;
extern s32 D_80190CC8;
extern s32 D_80190CB0;
extern s32 D_80190CBC;
extern s32 D_80190CC0;

extern void *D_80190CA0;
extern s32 D_80190CD8;
extern void *D_80190CA8;

void func_8013D53C(void *arg0v) {

    extern Rec9 D_8017F3F4[];
    extern Rec12 D_8017F42C[];
    extern u8 D_80078EAF;
    extern u8 D_80193408;
    extern s32 D_80190CC4;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_8017F430[];
    extern u8 D_8017F434[];
    extern unsigned char D_80193368;
    extern s16 *D_80190CAC;
    extern s32 D_80190CDC;
    extern s32 D_80190CE0;
    extern s32 D_80190CE4;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_80190CD0 & 1)) {
        D_80190CB8 = 1;
    } else {
        D_80190CB8 = D_80078EAF;
    }

    b0 = ((u8 *)D_8017F42C)[D_80190CB8 * 12];
    D_8019344A = b0;
    D_801934BE = b0;
    b1 = D_8017F430[D_80190CB8 * 12];
    D_80193372 = b1;
    D_8019342C = b1;
    b2 = D_8017F434[D_80190CB8 * 12];
    D_80193350 = b2;
    D_80193371 = b2;

    (*(S9 *)&D_80193368) = ((S9 *)D_8017F3F4)[D_80190CB8];
    (*(S9 *)&D_80193408) = *(S9 *)(&D_80193350 + 0x18);  /* same addr as (*(S9 *)&D_80193368); distinct sym defeats cse, keeps %hi/%lo */

    D_80193430 = 1;
    D_80190CCC = -1;
    D_80190CC8 = 0;
    D_80190CC4 = -1;
    D_80190CB0 = 0;
    D_80190CBC = 0;
    D_80190CC0 = 0;

    if ((D_80190CD0 & 2) && (D_80190CB8 == 4)) {
        s0v = (*(s32 * *)&D_80190CA0)[18];
        t9v = (*(s32 * *)&D_80190CA0)[19];
        t8v = (*(s32 * *)&D_80190CA0)[20];
    } else {
        s32 *p = (s32 *)(D_80190CB8 * 12 + (s32) (*(s32 * *)&D_80190CA0));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_80190CAC) = arg0;
    if (arg0 != 0) {
        if (D_80190CD8 != 0) {
            s32 *p = (s32 *)(D_80190CB8 * 12 + (s32) (*(s32 * *)&D_80190CA8));
            D_80190CDC = p[0];
            D_80190CE0 = p[1];
            D_80190CE4 = p[2];
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
                    __asm__("" :: "r"(src));  /* +2 refs on src (depth-2): keeps src above i, below the mfhi temp */  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus3)
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            __asm__("" :: "r"(i));  /* +3 refs on i (depth-3): lifts i over dst in the $t2 race */  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus3)
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

    extern s16 *D_80190CAC;
    s16 *psVar3;
    register s16 *psVar2 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus3)
    s32 c9;
    s32 cff;
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_80190CAC;
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


extern void *D_80190CA4;
extern s32 D_80190CBC;
extern void func_800599B8(u16*);
#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{

    extern s16 *D_80190CAC;
    extern s32 D_80190CC4;
    u8 buf[0x20];
    s32 uVar13;
    register u16 *psVar14 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus3)
    u16 *psVar15;
    s32 uVar16;
    void *r0;
    u16 *puVar10;
    register u16 *puVar9 __asm__("$10");  // !FAKE: pin $10 — NEEDED DIFFERS (P36 rung B tus3)
    s32 iVar11;
    register s32 iVar12 __asm__("$14");  // !FAKE: pin $14 — NEEDED DIFFERS (P36 rung B tus3)
    u16 sVar4;
    register u32 uVar5 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus3)
    register u32 uVar7 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus3)
    register u32 uVar1 __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus3)
    u32 uVar6;
    register u32 uVar8 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus3)
    register u32 uVar3 __asm__("$9");  // !FAKE: pin $9 — NEEDED DIFFERS (P36 rung B tus3)

    psVar15 = (*(u16 * *)&D_80190CAC);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_80190CA4)[param_1];
        D_80190CC4 = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus3)
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus3)
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus3)
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus3)
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus3)
                        s32 mh = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
                        register u16 *pi __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus3)
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus3)
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
                            register u32 out __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
                                register void *pb __asm__("$12");  // !FAKE: pin $12 — NEEDED DIFFERS (P36 rung B tus3)
                                __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus3)
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus3)
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus3)
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                s32 c;
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus3)
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
        D_80190CBC = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_80190CA8)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_80190CA8;
extern s16 *D_80190CAC;
extern s32 D_80190CBC;
extern s32 D_80190CDC;
extern s32 D_80190CE0;
extern s32 D_80190CE4;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_80190CAC != 0) {
        D_80190CBC = 0;
        p = (int *)(param_1 * 12 + (int)D_80190CA8);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_80190CDC != x) {
            flag = 1;
            if (D_80190CDC < x) {
                if (x - D_80190CDC < 5) {
                    D_80190CDC = x;
                } else {
                    D_80190CDC = D_80190CDC + 4;
                }
            } else {
                if (D_80190CDC - x < 5) {
                    D_80190CDC = x;
                } else {
                    D_80190CDC = D_80190CDC - 4;
                }
            }
        }
        if (D_80190CE0 != y) {
            flag = 1;
            if (D_80190CE0 < y) {
                if (y - D_80190CE0 < 5) {
                    D_80190CE0 = y;
                } else {
                    D_80190CE0 = D_80190CE0 + 4;
                }
            } else {
                if (D_80190CE0 - y < 5) {
                    D_80190CE0 = y;
                } else {
                    D_80190CE0 = D_80190CE0 - 4;
                }
            }
        }
        if (D_80190CE4 != z) {
            flag = 1;
            if (D_80190CE4 < z) {
                if (z - D_80190CE4 < 5) {
                    D_80190CE4 = z;
                } else {
                    D_80190CE4 = D_80190CE4 + 4;
                }
            } else {
                if (D_80190CE4 - z < 5) {
                    D_80190CE4 = z;
                } else {
                    D_80190CE4 = D_80190CE4 - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_80190CBC = flag;
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (187 ins). Levers: struct-assign DRAWENV copy (align via type); pbase local for $s2-relative D_800B9A02; two-biv SPRT loop (q anchored one-above -> gcc re-anchors, no bare-deref); P_TAG_8013DD68 addPrim; single p var coalesces puVar7->puVar15; pins uVar2=$v1,iVar14=$a3,c5=$t3; biv-increment order sets q-init-before-puVar10-init; Buf_8013DD68 0x68 -> frame 0xA0.

              /* 0x5C copy unit, align 4 */
  /* -> frame 0xA0 (gcc adds 0x10 for the struct-copy) */


#define IDVAL (*(u16 *)(pbase + 0xA3D2))
#define OTE ((P_TAG_8013DD68 *)(D_800BA0E4 + IDVAL * 0x10))

void func_8013DD68() {
    extern void SetDrawEnv(void *p, void *env);
    extern u16 D_800AF7B8;
    extern u8 D_800BA0E4[];
    extern u8 D_8017F468[];

    u32 *p;
    u16 uVar1;
    u16 *puVar16;
    u16 *q;
    u16 *puVar10;
    register u16 uVar2 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus3)
    int uVar5;
    register int iVar14 __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus3)
    Buf_8013DD68 buf;
    u8 *pbase;
    u8 *base;

    pbase = D_800AF630;
    puVar16 = (*(u16 * *)&D_80190CAC);
    p = (*(u32 * *)&D_800A5E60);
    uVar1 = *puVar16;
    puVar16 = puVar16 + 1;
    base = pbase + (u32)D_800AF7B8 * 0x5C;
    buf.env = *(DrawEnv_8013DD68 *)(base + 0x38);
    *((u8 *)&buf + 0x18) = 0;
    SetDrawEnv(p, &buf);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    iVar14 = 0;
    if (uVar1 != 0) {
        int c5 = 5;
        puVar10 = (u16 *)((int)p + 0x18);
        q = puVar16 + 8;
        do {
            *(u8 *)((int)puVar10 + -0x15) = c5;
            uVar2 = q[-6];
            *(u8 *)((int)puVar10 + -0xd) = 100;
            *(u8 *)((int)puVar10 + -0x10) = (u8)(*(int*)&D_80190CDC);
            *(u8 *)((int)puVar10 + -0xf) = (u8)(*(int*)&D_80190CE0);
            uVar5 = (*(int*)&D_80190CE4);
            *(u32 *)((int)puVar10 + -0x14) = uVar2 & 0x9ff | 0xe1000400;
            *(u8 *)((int)puVar10 + -0xe) = (u8)uVar5;
            *(u16 *)((int)puVar10 + -0xc) = q[-4];
            iVar14 = iVar14 + 1;
            *(u16 *)((int)puVar10 + -0xa) = q[-3];
            *(u8 *)((int)puVar10 + -8) = (u8)*puVar16;
            uVar2 = q[-7];
            *(u16 *)((int)puVar10 + -6) = 0x7800;
            *(u8 *)((int)puVar10 + -7) = (u8)uVar2;
            puVar16 = puVar16 + 8;
            *(u16 *)((int)puVar10 + -4) = q[-2];
            *(u16 *)((int)puVar10 + -2) = q[-1];
            ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
            puVar10 = puVar10 + 0xc;
            OTE->addr = (u32)p;
            p = p + 6;
            q = q + 8;
        } while (iVar14 < (int)(u32)uVar1);
    }
    SetDrawEnv(p, D_8017F468);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    (*(u32 * *)&D_800A5E60) = p;
    return;
}




extern s32 D_80190CC4;

s32 func_8013E054(void) {
    return D_80190CC4;
}


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


#include "../shared/ov/func_8013E5E8__0b4494b1.h"


#include "../shared/ov/func_8013E67C.h"


// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_8017FE64;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_8017FE3C;
extern s16 D_8017FE3E;
extern unsigned short D_80115112;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

#include "../shared/ov/func_8013E6AC__55bb00e6.h"


#include "../shared/ov/func_8013E814.h"

// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {
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
    extern void * D_80190CF8;
    extern void * D_80190CFC;
    extern unsigned char D_8017FADC;
    extern unsigned char D_8017FAF4;
    extern unsigned char D_8017FB68;
    extern unsigned char D_8017FB70;


    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((((int(*)(int))func_80029178)(0x1c) & 0xFF) == 0) {
        D_80190CF8 = &D_8017FADC;
        D_80190CFC = &D_8017FB68;
    } else {
        D_80190CF8 = &D_8017FAF4;
        D_80190CFC = &D_8017FB70;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        ((void(*)(int, int))func_8002D4C8)(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_8017FE64/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_8017FE64 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

#include "../shared/ov/func_8013E958__10b2e065.h"



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
extern unsigned char D_8017FE40;

#include "../shared/ov/func_8013EB7C__c502c10e.h"


#include "../shared/ov/func_8013ED6C.h"

extern short D_800B9A02;
extern unsigned short D_80115112;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern s16 D_8017FE3C;
extern s16 D_8017FE3E;
extern unsigned char D_8017FE40;
extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8017FE3E` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_8017FE3C` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.




#include "../shared/ov/func_8013EE10__1b85d9be.h"











extern s16 D_800B9A02;
extern s32 D_801151D0;
extern E4  aD80115188[] __asm__("D_80115188");
extern u16 D_80115124;
extern u16 D_80115112;
extern s16 D_8017FE3E;
extern s16 D_8017FE3C;

extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);

#include "../shared/ov/func_8013EF88__bc5ad667.h"



// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_8017FE40;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

#include "../shared/ov/func_8013F138__6cd0b346.h"


#include "../shared/ov/func_8013F1BC.h"

#include "../shared/ov/func_8013F244.h"

