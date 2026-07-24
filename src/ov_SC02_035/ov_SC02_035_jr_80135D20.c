#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */
typedef struct { s32 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s16 h[8]; } Buf;
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
extern s32 D_801BC3F0;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_80184768[])(void);
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
extern s32 D_801BD59C;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_801BE9D8;
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
extern int D_801BC3F0;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_801844A4)();
extern s16 (*D_801844A8)();
extern M2C_UNK (*D_801844B0)();
extern s32 (*D_801844B4)();
extern s32 D_801BD598;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_801BC3F4;
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
extern void func_8012A598(void *a0);
extern void func_8012A568(void (*a0)(void));
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
extern void func_8012AAAC(void);
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
extern M2C_UNK D_801847FC;
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
extern s32   D_80187CE0;
extern s16 D_801270C4;
extern u16   D_801274E4[];
extern s32   D_8011DB08;
extern s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_8012CC88(s32 a0, s32 a1, s32 a2);
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
extern M2C_UNK D_80184814;
extern M2C_UNK D_8018481C;
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
extern void func_8012E014(void);
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
extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_80184824;
extern void func_8012E9C0(int param_1);
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
extern unsigned char D_80184840[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_8018484C[];
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
extern void (*D_80184860[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_801848B0[];
extern s16 D_801848E0[];
extern s16 D_80184940[];
extern s16 D_80184948[];
extern s16 D_80184968[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_80131E00();
extern s32 D_801BD5C0;
extern s32 D_801BD5C4;
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern int func_80131D68(int a0, int a1);
extern void (*D_801849A0[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_801849F8[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_80184A40[])(void);
extern void func_80131F28(void *a0);
extern void (*D_80184A48[])(void);
extern void func_80131F64(void *a0);
extern void (*D_80184A50[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_80184A58[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_80184A00;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_80184A20;
extern void func_801321B0(int param_1);
extern int D_80184A30;
extern void func_8013221C(int param_1);
extern void func_8005C324(int dst, int src, int n) __asm__("memcpy"); /* Phase-24: 0x8005C324 is named memcpy for overlays (whale needs it); keep the non-builtin C name here (else built-in codegen), emit via asm-label */
extern void func_801325B8(int a0, int a1, int a2, int a3, int a4);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8013240C(s32 a0);
extern void memcpy();
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
extern void func_801330E0(s16 *a0, s16 *a1, s32 a2);
extern void func_80133060(u8 *a0, s32 *a1, s32 a2);
extern void func_8013339C(short *param_1, short *param_2);
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern s32 D_801BD608;
extern s32 D_801BD60C[];
extern int D_801BD610;
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern void func_80136BC4(s32);
extern void func_8013373C(s16 arg0);
extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);
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
extern s32 func_80135004(s32 arg0, s32 p1, s32 p2);
extern u8 D_80184A64;
extern u8 D_80184A60;
extern s16 *D_80184A68;
extern u8 D_80184A6C;
extern int D_801BD608;
extern u16 D_801BD618;
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
extern s32 func_80135EB0(s32 *p, s32 flag);
extern s32 func_801345F8(s32 arg);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801BD61C;
extern s32 D_801BD63C;

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
        p = &D_801BD63C;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_801BD61C;
        p = &D_801BD63C;
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

INCLUDE_ASM("asm/ov_SC02_035/nonmatchings/ov_SC02_035_jr_80135D20", func_80135EB0);


s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {
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
        dx = (s16) arg2 - (*(s16 **)&D_80184A60)[2];
        d = dx;
        denom = -(*(s16 **)&D_80184A6C)[2];
    } else {
        denom = (*(s16 **)&D_80184A6C)[2];
        d = (*(s16 **)&D_80184A60)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_80184A6C;
        u16 *ac = *(u16 **)&D_80184A60;
        b4 = D_80184A68;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_80184A64;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_80184A68[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_80184A68[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}




// @class: regalloc-order — per-location family member of ov_SC01_077 exemplar func_801365B8 (x134).
// @stuck: none — MATCH expected; identical structure, only the 4 data ptrs differ (AC/B0/B4/B8 -> B64/68/6C/70).

// D_80184A60/68/70 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_80184A68 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
extern u8 D_80184A64;
extern u8 D_80184A60;
extern s16 *D_80184A68;
extern u8 D_80184A6C;
extern u8 D_80126720[];

s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {
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
        var_v1 = (s16) arg2 - (*(s16 **)&D_80184A60)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_80184A6C)[0];
    } else {
        var_a3 = (*(s16 **)&D_80184A6C)[0];
        var_v1 = (*(s16 **)&D_80184A60)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_80184A60;
    b4 = D_80184A68;
    b8 = *(s16 **)&D_80184A6C;
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
        b4[1] = (s16) (*(u16 **)&D_80184A64)[1];
        b4[2] = (s16) (*(u16 **)&D_80184A64)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_80184A68, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_80184A68, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_80184A60/B0/B8 are file-scope `extern u8`, D_80184A68 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_80184A68 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
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
        var_t0 = (s16) arg2 - (*(s16 **)&D_80184A60)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_80184A6C)[1];
    } else {
        var_a3 = (*(s16 **)&D_80184A6C)[1];
        var_v1 = (*(s16 **)&D_80184A60)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_80184A6C);
    ac = (*(u16 **)&D_80184A60);
    b4 = D_80184A68;
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
        p = (*(u16 **)&D_80184A64);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_80184A68;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_80184A68;
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


extern s16 *D_80184A68;   /* holds a pointer value (*(u16**)&D_80184A68) */

s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_80184A68, *(void **)&D_80184A68);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_80184A68;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}



DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136BC4 (src/shared) */

DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136C1C (src/shared) */

DEFINE_func_80136C3C()  /* dedup: shared engine-core @0x80136C3C (src/shared) */

DEFINE_func_80136C44()  /* dedup: shared engine-core @0x80136C44 (src/shared) */

DEFINE_func_80136C4C()  /* dedup: shared engine-core @0x80136C4C (src/shared) */


extern unsigned short D_800B99F0;
extern void (*D_80184A7C[])(void);

void func_80136C54(void)
{
    D_80184A7C[D_800B99F0]();
}


// @class: struct
// @stuck: none — MATCH (28 ins). 10-byte 1-aligned struct copy (S10_80136C90{char s[10]}) from global D_801BC644 into a stack buffer, then func_8001534C(0,&buf,0x78,0x10,0,0). gcc emits the block move as 2 unaligned words (lwl/lwr+swl/swr) + 2 bytes (lb/sb).


s32 func_80136C90()
{
    extern void func_8001534C(int, void *, int, int, int, int);
    extern S10_80136C90 D_801BC644;

    S10_80136C90 buf = D_801BC644;
    func_8001534C(0, &buf, 0x78, 0x10, 0, 0);
}



DEFINE_func_80136D00()  /* dedup: shared engine-core @0x80136D00 (src/shared) */

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136D08 (src/shared) */

DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136DFC (src/shared) */

DEFINE_func_80136EC4()  /* dedup: shared engine-core @0x80136EC4 (src/shared) */

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ECC (src/shared) */

INCLUDE_ASM("asm/ov_SC02_035/nonmatchings/ov_SC02_035_jr_80135D20", func_80136F3C);

DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */

DEFINE_func_80137178()  /* dedup: shared engine-core @0x80137178 (src/shared) */

DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372B0 (src/shared) */

DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375EC (src/shared) */

INCLUDE_ASM("asm/ov_SC02_035/nonmatchings/ov_SC02_035_jr_80135D20", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767C (src/shared) */

DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_035/nonmatchings/ov_SC02_035_jr_80135D20", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377B4 (src/shared) */

DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_035/nonmatchings/ov_SC02_035_jr_80135D20", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379D8 (src/shared) */

DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379EC (src/shared) */


// @class: regalloc-order (walker-family, §52/§52a) — PIN-FREE
// Role-swap ($s0<->$s2 between loop1 and loops2/3) is driven by DENSITY (K2), not pins:
//  - loop1 pointer has an extra ref (p != D_80127524 compare) -> wins $s0; index -> $s2
//  - loop2/3 index has >= pointer refs -> wins $s0; pointer -> $s2
// Separate per-loop pointer/index vars => separate pseudos => can take different regs.


extern void func_80138BE0(s32 a0);
extern void func_80137BD8(s32 a0);
extern void func_8013A380(void);

void func_801379FC(void) {

    extern s32 D_80127524;
    extern s32 D_80127548[];
    extern s32 D_801269F0;
    extern s16 D_801269F4;
    extern s32 D_801269F8;
    s32 i;

    (*(s32 *)D_80127548) = 0x24;
    if ((D_80127524 != 0) && (*(s32 *)D_80127524 != 0)) {
        s32 p;
        s32 idx;
        func_80138BE0(D_80127524);
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if ((p != D_80127524) && (*(s32 *)((s32)&D_801269F0 + idx) != 0)) {
                func_80138BE0(p);
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    } else {
        s32 p;
        s32 idx;
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if (*(s32 *)((s32)&D_801269F0 + idx) != 0) {
                func_80138BE0(p);
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    }

    {
        s32 p;
        s32 idx;
        s32 flags;
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if (*(s16 *)((s32)&D_801269F4 + idx) != 0) {
                if (*(s32 *)((s32)&D_801269F0 + idx) != 0) {
                    flags = *(s32 *)((s32)&D_801269F8 + idx);
                    if ((flags & 0x1000) != 0) {
                        if ((flags & 0x2000) == 0) {
                            func_80137BD8(p);
                        }
                    }
                }
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    }

    func_8013A380();
}



// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern s32 D_80127548[];
extern int D_80184AD0;
extern int D_801269F0;
extern void func_80138BE0(int p);

void func_80137B80(void) {
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_80184AD0 += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137BD8 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.

extern unsigned char D_80126A0E;
extern short D_80126A0A;
extern s16 D_801269F4;
extern int D_800A5E60;
extern int D_80184AD0;
extern int D_801269F0;

extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{
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
        if (D_80184AD0 & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137DD4 (src/shared) */

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137FD8 (src/shared) */


