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
extern s32 D_8019FCD4;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_80181500[])(void);
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
extern s32 D_801A0E94;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_801A2390;
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
extern void func_8013BC7C(void *arg0);
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern u8 D_800AEFD0;
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_8019FCD4;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8018123C)();
extern s16 (*D_80181240)();
extern M2C_UNK (*D_80181248)();
extern s32 (*D_8018124C)();
extern s32 D_801A0E90;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8019FCD8;
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
extern struct BigCopy D_80126DB8;/* canonical (engine_core macro): struct BigCopy — (s32*)& at use */
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
extern struct BigCopy D_80126DB8;
extern struct BigCopy D_80114EE8;
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
extern M2C_UNK D_80181594;
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
extern s32   D_80184A78;
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
extern M2C_UNK D_801815AC;
extern M2C_UNK D_801815B4;
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
extern void func_8012E138(int model);
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
extern int D_801815BC;
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
extern unsigned char D_801815D8[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_801815E4[];
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
extern void func_8012E364(s32 arg0_);
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
extern void (*D_801815F8[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80181648[];
extern s16 D_80181678[];
extern s16 D_801816D8[];
extern s16 D_801816E0[];
extern s16 D_80181700[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_80181738[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_80181790[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_801817D8[])(void);
extern void func_80131F28(void *a0);
extern void (*D_801817E0[])(void);
extern void func_80131F64(void *a0);
extern void (*D_801817E8[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_801817F0[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_80181798;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_801817B8;
extern void func_801321B0(int param_1);
extern int D_801817C8;
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
extern s32 D_801A0F00;
extern s32 D_801A0F04[];
extern int D_801A0F08;
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
extern u8 D_801817FC;
extern u8 D_801817F8;
extern s16 *D_80181800;
extern u8 D_80181804;
extern int D_801A0F00;
extern u16 D_801A0F10;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_80181800;   /* holds a pointer value (*(u16**)&D_80181800) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_80181814[])(void);
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
extern int D_80181868;
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
extern void (*D_8018186C[])(void);
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
extern u8 D_801818B0;
extern u8 D_801818F4;
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
extern u8  D_80181938[];   /* sign table, alt (when a1 < 0xC00) */
extern void func_8013AD38(void *flag, s32 a1, void *out2, void *out3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern s16 D_801819B0, D_801819B2, D_801819B4, D_801819B6, D_801819B8, D_801819BA;
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
extern s32 D_801A0F78;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_801A0F78, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern M2C_UNK D_80062BC0;
extern s32 D_801A0F78;
extern s8 D_801A0F7C;
extern s8 D_801A0F7D;

void func_8013C9C4(void * arg0)
{
    D_801A0F78 = arg0;
    D_801A0F7C = 0;
    D_801A0F7D = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}




extern s32 D_801A0F78;
extern s8 D_801A0F7C;
extern s8 D_801A0F7D;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_801A0F78;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801A0F7D;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801A0F7C)) * 2) + D_801A0F78);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801A0F7D = (unsigned char) p[1];
      D_801A0F7C = D_801A0F7C + 1;
      if (D_801A0F7D == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801A0F7C = 0;
        *base = 0;
      }
    }
    else
    {
      D_801A0F7D = c - 1;
    }
  }
  return;
}



extern s32 D_801A0F9C;
extern s32 D_801A0F90;
extern s32 D_801A0F94;
extern s32 D_801A0FA0;

void func_8013CABC(void) {
    D_801A0F9C = 1;
    D_801A0F90 = 1;
    D_801A0F94 = 0;
    D_801A0FA0 = 1;
}



extern s32 D_801A0F90;
extern s32 D_801A0F94;
extern s32 D_801A0F98;
extern s32 D_801A0F9C;
extern s32 D_801A0FA0;

void func_8013CAE8(void) {
    D_801A0F90 = 1;
    D_801A0F9C = 0;
    D_801A0F94 = 0;
    D_801A0F98 = -1;
    D_801A0FA0 = 0;
}



extern s32 D_801A0F9C;
extern s32 D_801A0FA0;
extern s32 D_801A0FC8;
extern s32 D_801A0FCC;

void func_8013CB20(void)
{
    D_801A0FC8 = D_801A0FA0;
    D_801A0FCC = D_801A0F9C;
    D_801A0FA0 = 1;
    D_801A0F9C = 0;
}



extern s32 D_801A0FC8;
extern s32 D_801A0FCC;
extern s32 D_801A0FA0;
extern s32 D_801A0F9C;

void func_8013CB5C(void) {
    D_801A0FA0 = D_801A0FC8;
    D_801A0F9C = D_801A0FCC;
}




extern s16 currentLocationId;
extern s32 D_801A0FA0;
extern s32 D_801A0F98;
extern s32 D_801A0F9C;
extern s32 D_801A0F90;
extern s32 D_801A0F94;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_801A0FA4;
    extern s32 D_801A0FB0;
    extern s32 D_801A0FB8;
    extern s32 D_801A2370;
    extern s32 D_801A22F0;
    extern s32 D_801A22E4[];
    extern u8 D_801A22B1;
    extern u8 D_801A2402;
    extern u8 D_801A236C;
    extern Rec12 D_80181BD0[];
    extern Rec9 D_80181B98[];
    extern u8 D_801A2348;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801A2370 = 0;
    if (D_801A0FA0 == 0 && s0 != D_801A0F98) {
        ta = D_80181BD0[s0].a;
        tb = D_80181BD0[s0].b;
        tc = D_80181BD0[s0].c;
        D_801A0F98 = s0;
        D_801A22B1 = tc;
        D_801A2402 = ta;
        D_801A236C = tb;
        *(Rec9 *)&D_801A2348 = D_80181B98[s0];
        D_801A0F9C = 1;
        D_801A0F90 = 1;
        if (D_801A0FB0 & 2) {
            if (s0 == 4) { D_801A22E4[0] = 0x100; D_801A22F0 = 0x80; }
            if (s0 == 0) { D_801A22E4[0] = 0x100; D_801A22F0 = 0; }
        }
    }
    if (D_801A0F9C != 0) {
        t = D_801A0F90 - 1;
        D_801A0F90 = t;
        if (t == 0) {
            if (D_801A0FA0 == 0) {
                if ((D_801A0FB0 & 2) && s0 == 4) {
                    if (D_801A0FB8 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801A0FB8 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801A0F90 = 2;
                if (D_801A0F9C != 0) {
                    if (D_801A0FB0 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801A22F0;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801A22F0;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801A0FB0 & 2) {
                    if (s0 == 4) D_801A22F0 = 0;
                    if (s0 == 0) D_801A22F0 = 0x80;
                }
            } else {
                if (D_801A0FB8 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801A0F90 = 1;
            }
        }
    }
    D_801A0FA4 = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801A0F9C != 0) D_801A0FA4 = D_801A0F94;
            else D_801A0FA4 = 0x1F;
        } else if (s0 == 4) {
            if (D_801A0F9C != 0) D_801A0FA4 = 0x1F - D_801A0F94;
            else D_801A0FA4 = 0;
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
    extern u8 D_801A22A8;
    extern u8 D_801A22A9;
    extern u8 D_801A22AA;
    extern u8 D_801A22AB;
    extern u8 D_801A22AC;
    extern u8 D_801A22AD;
    extern u8 D_801A22AE;
    extern u8 D_801A22AF;
    extern u8 D_801A22B0;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));  // !FAKE: instruction la — NEEDED DIFFERS (P36 rung B tus2)

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801A22A8; t1 = D_801A22A9; t2 = D_801A22AA;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801A22AB; t1 = D_801A22AC; t2 = D_801A22AD;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801A22AE; t1 = D_801A22AF; t2 = D_801A22B0;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_801A0FA8;
extern s32 D_801A0F90;
extern s32 D_801A0FAC;
extern s32 D_801A0F9C;
extern void func_8013D9B0();

void func_8013D064(void)
{
    if (D_801A0FA8 != 0) {
        if (D_801A0FA8 != 2) {
            if (((D_801A0FA8 < 3) && (D_801A0FA8 == 1)) &&
                (D_801A0FAC = D_801A0FAC + 1, 0x23a < D_801A0FAC)) {
                D_801A0F90 = D_801A0FA8;
                D_801A0FA8 = 2;
            }
        } else {
            D_801A0F90 = D_801A0F90 + -1;
            if (D_801A0F90 == 0) {
                D_801A0F90 = D_801A0FA8;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801A0F9C == 0) {
                    D_801A0FA8 = D_801A0FA8 + 1;
                }
            }
        }
    }
    return;
}




extern void func_8013D9B0();
extern s32 D_801A0F9C;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801A0F9C;
}



extern s32 D_801A0FA8;

void func_8013D164(void) {
    D_801A0FA8 = 1;
}



void func_8013D178(void) {

    extern u8 D_801A22A8, D_801A22A9, D_801A22AA, D_801A22AB, D_801A22AC, D_801A22AD, D_801A22AE, D_801A22AF, D_801A22B0;
    extern u8 D_801A2348, D_801A2349, D_801A234A, D_801A234B, D_801A234C, D_801A234D, D_801A234E, D_801A234F, D_801A2350;

    {
        u8 *p = &D_801A22A8;
        u8 v = *p, t = D_801A2348;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22A9;
        u8 v = *p, t = D_801A2349;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AA;
        u8 v = *p, t = D_801A234A;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AB;
        u8 v = *p, t = D_801A234B;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AC;
        u8 v = *p, t = D_801A234C;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AD;
        u8 v = *p, t = D_801A234D;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AE;
        u8 v = *p, t = D_801A234E;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22AF;
        u8 v = *p, t = D_801A234F;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
    {
        u8 *p = &D_801A22B0;
        u8 v = *p, t = D_801A2350;
        if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    }
}



// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_801A238A;
extern u8 D_801A2402;
extern u8 D_801A22B2;
extern u8 D_801A236C;
extern u8 D_801A2290;
extern u8 D_801A22B1;
extern s32 D_801A2370;

void func_8013D330(void) {
    if ((D_801A238A & 0xff) != D_801A2402) {
        D_801A238A = ((D_801A238A & 0xff) < D_801A2402) ? (D_801A238A + 1) : (D_801A238A - 1);
    }
    if ((D_801A22B2 & 0xff) != D_801A236C) {
        D_801A22B2 = ((D_801A22B2 & 0xff) < D_801A236C) ? (D_801A22B2 + 1) : (D_801A22B2 - 1);
    }
    if ((D_801A2290 & 0xff) != D_801A22B1) {
        D_801A2290 = ((D_801A2290 & 0xff) < D_801A22B1) ? (D_801A2290 + 1) : (D_801A2290 - 1);
    }
    D_801A2370 = 1;
}




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_801A0F80;
extern void *D_801A0F84;
extern void *D_801A0F88;
extern s32 D_801A0FB0;
extern s32 D_801A0FB4;
extern s32 D_801A0FB8;
extern s32 D_801A22E4[];

extern u8 D_80181AA8[];
extern u8 D_80181B50[];
extern u8 D_80181A00[];
extern u8 D_80181AFC[];
extern u8 D_80181B7C[];
extern u8 D_80181A54[];

extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_801A0FB0 = param_2;
    D_801A0FB4 = (param_2 >> 2) & 3;
    D_801A0FB8 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801A0F80 = D_80181AA8;
        D_801A0F84 = D_80181B50;
        D_801A0F88 = D_80181A00;
    } else {
        D_801A0F80 = D_80181AFC;
        D_801A0F84 = D_80181B7C;
        D_801A0F88 = D_80181A54;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801A0FB8 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801A0FB0 & 2) != 0) {
            D_801A22E4[0] = 0x140;
            D_801A22E4[3] = 0x80;
            if (p[0x37] == 4) {
                D_801A22E4[0] = 0x140;
                D_801A22E4[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801A22E4[0] = 0x140;
                D_801A22E4[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */


extern s32 D_801A0FB0;
extern s32 D_801A0F98;


extern u8 D_801A238A;
extern u8 D_801A2402;
extern u8 D_801A22B2;
extern u8 D_801A236C;
extern u8 D_801A2290;
extern u8 D_801A22B1;


extern s32 D_801A2370;
extern s32 D_801A0FAC;
extern s32 D_801A0FA8;
extern s32 D_801A0F90;
extern s32 D_801A0F9C;
extern s32 D_801A0FA0;

extern void *D_801A0F80;
extern s32 D_801A0FB8;
extern void *D_801A0F88;

void func_8013D53C(void *arg0v) {

    extern Rec9 D_80181B98[];
    extern Rec12 D_80181BD0[];
    extern u8 D_80078EAF;
    extern u8 D_801A2348;
    extern s32 D_801A0FA4;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_80181BD4[];
    extern u8 D_80181BD8[];
    extern unsigned char D_801A22A8;
    extern s16 *D_801A0F8C;
    extern s32 D_801A0FBC;
    extern s32 D_801A0FC0;
    extern s32 D_801A0FC4;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_801A0FB0 & 1)) {
        D_801A0F98 = 1;
    } else {
        D_801A0F98 = D_80078EAF;
    }

    b0 = ((u8 *)D_80181BD0)[D_801A0F98 * 12];
    D_801A238A = b0;
    D_801A2402 = b0;
    b1 = D_80181BD4[D_801A0F98 * 12];
    D_801A22B2 = b1;
    D_801A236C = b1;
    b2 = D_80181BD8[D_801A0F98 * 12];
    D_801A2290 = b2;
    D_801A22B1 = b2;

    (*(S9 *)&D_801A22A8) = ((S9 *)D_80181B98)[D_801A0F98];
    (*(S9 *)&D_801A2348) = *(S9 *)(&D_801A2290 + 0x18);  /* same addr as (*(S9 *)&D_801A22A8); distinct sym defeats cse, keeps %hi/%lo */

    D_801A2370 = 1;
    D_801A0FAC = -1;
    D_801A0FA8 = 0;
    D_801A0FA4 = -1;
    D_801A0F90 = 0;
    D_801A0F9C = 0;
    D_801A0FA0 = 0;

    if ((D_801A0FB0 & 2) && (D_801A0F98 == 4)) {
        s0v = (*(s32 * *)&D_801A0F80)[18];
        t9v = (*(s32 * *)&D_801A0F80)[19];
        t8v = (*(s32 * *)&D_801A0F80)[20];
    } else {
        s32 *p = (s32 *)(D_801A0F98 * 12 + (s32) (*(s32 * *)&D_801A0F80));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_801A0F8C) = arg0;
    if (arg0 != 0) {
        if (D_801A0FB8 != 0) {
            s32 *p = (s32 *)(D_801A0F98 * 12 + (s32) (*(s32 * *)&D_801A0F88));
            D_801A0FBC = p[0];
            D_801A0FC0 = p[1];
            D_801A0FC4 = p[2];
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
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
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
                            do { i++; } while (0);
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

    extern s16 *D_801A0F8C;
    Cmd_8013D53C *p;
    s16 buf[4];

    p = (Cmd_8013D53C *)D_801A0F8C;
    if (p != 0) {
        while (p->cmd != 0xff) {
            if (p->cmd == 9) {
                u16 *data = p->data + p->w;
                buf[0] = p->pad4;
                buf[1] = p->pad6;
                buf[2] = p->w;
                buf[3] = p->h;
                ((void (*)(s16 *, u16 *))func_800599B8)(buf, data);
            }
            p++;
        }
    }
}


extern void *D_801A0F84;
extern s32 D_801A0F9C;
extern void func_800599B8(u16*);

void func_8013D9B0(int param_1)
{
    extern s16 *D_801A0F8C;
    extern s32 D_801A0FA4;
    s16 rect[4];    /* LoadImage rect: x, y, w, h */
    u32 gte[6];     /* [0] fog colour (RGB), [1] source pixel (IRGB), [2] DPCL result (ORGB); [3..5] unused (frame 0x48) */
    Cmd_8013D53C *p;
    u32 *fc;
    u16 cmd;
    s32 flag;
    s32 any;
    s32 n;
    s32 i;
    u16 *src;
    u16 *img;
    u16 *dst;
    s32 r, g, b;
    s32 tr, tg, tb;
    u32 pix;
    u32 out;
    u32 result;

    p = (Cmd_8013D53C *)D_801A0F8C;
    if (p != 0) {
        cmd = p->cmd;
        gte[0] = (*(u32 **)&D_801A0F84)[param_1];
        D_801A0FA4 = -1;
        any = 0;
        if (cmd != 0xff) {
            fc = gte;
            do {
                if (cmd == 9) {
                    i = 0;
                    rect[0] = p->pad4;
                    rect[1] = p->pad6;
                    rect[2] = p->w;
                    rect[3] = p->h;
                    n = p->w * p->h;
                    flag = 0;
                    src = p->data;
                    img = src + n;
                    dst = img;
                    if (n > 0) {
                        do {
                            gte[1] = *src;
                            pix = *dst;
                            r = pix & 0x1f;
                            g = pix & 0x3e0;
                            b = pix & 0x7c00;
                            __asm__ __volatile__("mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)" :: "r"(fc), "r"(&gte[1]) : "memory");  // !FAKE: asm gte_ldIR0z+gte_ldrgb+gte_ldIRGB — the header spells these as three volatile asms (sched.c:1957 barriers), so the IRGB address lands after lwc2 $6, and a pointer set before mtc2 has life 4 and is hoisted (loop.c:1631); one asm keeps its addiu adjacent (life 1) and before mtc2 (P36 S103 c47 minimum-lever)
                            gte_dpcl();
                            __asm__ __volatile__("move $12, %0\n\tswc2 $29, 0($12)" :: "r"(&gte[2]) : "$12", "memory");  // !FAKE: asm gte_stORGB — the header macro does not write $12 itself; the target's move t4,v0 needs it (S103 c17; the header respelling is Drew's T5 call) (P36 S103 c47 minimum-lever)
                            out = gte[2];
                            tr = out & 0x1f;
                            tg = out & 0x3e0;
                            tb = out & 0x7c00;
                            if (r != tr) {
                                if (r < tr) { flag = 1; r += 1; } else flag = 1;
                                if (tr < r) r -= 1;
                            }
                            if (g != tg) {
                                if (g < tg) { flag = 1; g += 0x20; } else flag = 1;
                                if (tg < g) g -= 0x20;
                            }
                            if (b != tb) {
                                if (b < tb) { flag = 1; b += 0x400; } else flag = 1;
                                if (tb < b) b -= 0x400;
                            }
                            result = r | g | b | (gte[1] & 0x8000);
                            if (result == 0 && gte[1] != 0) {
                                result = 0x8000;
                            }
                            *dst = result;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                    if (flag != 0) {
                        ((void (*)(s16 *, u16 *))func_800599B8)(rect, img);
                    }
                    any |= flag;
                }
                p++;
                cmd = p->cmd;
            } while (cmd != 0xff);
        }
        D_801A0F9C = any;
    }
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801A0F88)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_801A0F88;
extern s16 *D_801A0F8C;
extern s32 D_801A0F9C;
extern s32 D_801A0FBC;
extern s32 D_801A0FC0;
extern s32 D_801A0FC4;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_801A0F8C != 0) {
        D_801A0F9C = 0;
        p = (int *)(param_1 * 12 + (int)D_801A0F88);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801A0FBC != x) {
            flag = 1;
            if (D_801A0FBC < x) {
                if (x - D_801A0FBC < 5) {
                    D_801A0FBC = x;
                } else {
                    D_801A0FBC = D_801A0FBC + 4;
                }
            } else {
                if (D_801A0FBC - x < 5) {
                    D_801A0FBC = x;
                } else {
                    D_801A0FBC = D_801A0FBC - 4;
                }
            }
        }
        if (D_801A0FC0 != y) {
            flag = 1;
            if (D_801A0FC0 < y) {
                if (y - D_801A0FC0 < 5) {
                    D_801A0FC0 = y;
                } else {
                    D_801A0FC0 = D_801A0FC0 + 4;
                }
            } else {
                if (D_801A0FC0 - y < 5) {
                    D_801A0FC0 = y;
                } else {
                    D_801A0FC0 = D_801A0FC0 - 4;
                }
            }
        }
        if (D_801A0FC4 != z) {
            flag = 1;
            if (D_801A0FC4 < z) {
                if (z - D_801A0FC4 < 5) {
                    D_801A0FC4 = z;
                } else {
                    D_801A0FC4 = D_801A0FC4 + 4;
                }
            } else {
                if (D_801A0FC4 - z < 5) {
                    D_801A0FC4 = z;
                } else {
                    D_801A0FC4 = D_801A0FC4 - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801A0F9C = flag;
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
    extern u8 D_80181C0C[];

    u32 *p;
    u16 uVar1;
    u16 *puVar16;
    u16 *q;
    u16 *puVar10;
    u16 uVar2;
    int uVar5;
    int iVar14;
    Buf_8013DD68 buf;
    u8 *pbase;
    u8 *base;

    pbase = D_800AF630;
    puVar16 = (*(u16 * *)&D_801A0F8C);
    p = (*(u32 * *)&D_800A5E60);
    uVar1 = *puVar16;
    puVar16 = puVar16 + 1;
    base = pbase + (u32)D_800AF7B8 * 0x5C;
    buf.env = *(DrawEnv_8013DD68 *)(base + 0x38);
    *((u8 *)&buf + 0x18) = 0;
    SetDrawEnv(p, &buf);
    ((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;
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
            *(u8 *)((int)puVar10 + -0x10) = (u8)(*(int*)&D_801A0FBC);
            *(u8 *)((int)puVar10 + -0xf) = (u8)(*(int*)&D_801A0FC0);
            uVar5 = (*(int*)&D_801A0FC4);
            *(u32 *)((int)puVar10 + -0x14) = uVar2 & 0x9ff | 0xe1000400;
            *(u8 *)((int)puVar10 + -0xe) = (u8)uVar5;
            *(u16 *)((int)puVar10 + -0xc) = q[-4];
            iVar14 = iVar14 + 1;
            *(u16 *)((int)puVar10 + -0xa) = q[-3];
            *(u8 *)((int)puVar10 + -8) = (u8)*puVar16;
            *(u8 *)((int)puVar10 + -7) = (u8)q[-7];
            *(u16 *)((int)puVar10 + -6) = 0x7800;
            puVar16 = puVar16 + 8;
            *(u16 *)((int)puVar10 + -4) = q[-2];
            *(u16 *)((int)puVar10 + -2) = q[-1];
            ((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;
            puVar10 = puVar10 + 0xc;
            OTE->addr = (u32)p;
            p = p + 6;
            q = q + 8;
        } while (iVar14 < (int)(u32)uVar1);
    }
    SetDrawEnv(p, D_80181C0C);
    ((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;
    OTE->addr = (u32)p;
    p = p + 0x10;
    (*(u32 * *)&D_800A5E60) = p;
    return;
}




extern s32 D_801A0FA4;

s32 func_8013E054(void) {
    return D_801A0FA4;
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


void func_8013E5E8(void)
{
    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018261C[])(void);
    void (**new_var)(void);
    void (*fp)(void);
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    new_var = &D_8018261C[D_80115112];
    fp = *new_var;
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


#include "../shared/ov/func_8013E67C.h"


// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_80182608;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_801825E0;
extern s16 D_801825E2;
extern unsigned short D_80115112;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        s32 *ep;
        s32 *fp;
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_80182608;
        for (i = 0; i < 5; i++) {
            s32 *fa;
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_801825E0 = 2;
        D_801825E2 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_801825E2 = 0;
        D_801825E0 = 0;
        D_80115112 = 6;
    }
}


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
    extern void * D_801A0FD8;
    extern void * D_801A0FDC;
    extern unsigned char D_80182280;
    extern unsigned char D_80182298;
    extern unsigned char D_8018230C;
    extern unsigned char D_80182314;


    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((((int(*)(int))func_80029178)(0x1c) & 0xFF) == 0) {
        D_801A0FD8 = &D_80182280;
        D_801A0FDC = &D_8018230C;
    } else {
        D_801A0FD8 = &D_80182298;
        D_801A0FDC = &D_80182314;
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
// three bases (D_80115110/D_80182608/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80182608 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{
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
        v = ((s32 *)&D_80182608)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}



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
extern unsigned char D_801825E4;

void func_8013EB7C(void) {
    s32 sp10[2];
    short sVar1;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (D_8011511A >= 4) {
            func_8013FAF8((s16)D_8011511A, (s16)(D_8011511A + 1));
        }
        func_8013FAF8(0, 5);
        if (D_8011511A == 5) {
            iVar4 = func_8014032C((2), (((short (*)(s32))func_8014168C)(2)));
        } else {
            iVar4 = func_8014032C(((s16)D_8011511A), (((short (*)(s32))func_8014168C)((s16)D_8011511A)));
        }
        if (iVar4 != 0) {
            s32 *p130 = &D_80115130;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_801825E4));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_801825E4));
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


#include "../shared/ov/func_8013ED6C.h"

extern short D_800B9A02;
extern unsigned short D_80115112;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern s16 D_801825E0;
extern s16 D_801825E2;
extern unsigned char D_801825E4;
extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_801825E2` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_801825E0` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.




s32 func_8013EE10() {
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
    r = &D_801825E2;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_801825E0 = (u16)D_801825E0 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_801825E4);
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
extern s32 D_801151D0;
extern E4  aD80115188[] __asm__("D_80115188");
extern u16 D_80115124;
extern u16 D_80115112;
extern s16 D_801825E2;
extern s16 D_801825E0;

extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);

void func_8013EF88(void)
{

    extern u16 D_80115118;
    extern E4  D_80115168[];
    extern u16 D_80115114;
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
                u16 *s = &(*(u16 *)&D_801825E2);
                *s -= 1;
            }
            {
                u16 *w = &(*(u16 *)&D_801825E0);
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


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_801825E4;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_801825E4);
        }
        D_80115112 += 1;
    }
}


#include "../shared/ov/func_8013F1BC.h"

#include "../shared/ov/func_8013F244.h"

