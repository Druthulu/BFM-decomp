#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { int a; short cmd; short b; } Elem_8012ACE0_8012ACE0;      /* 8-byte element, cmd @ +4 */
typedef struct { char pad[0x90]; Elem_8012ACE0_8012ACE0 *list; } Owner_8012ACE0_8012ACE0;    /* list ptr @ +0x90 */
struct S8012D664_8012D664 { short a, b, c; };
typedef struct Entry_8012DDA4 {
    u16 active;
    unsigned char pad[0x10C - 2];
} Entry_8012DDA4;
typedef struct { char _b[8]; } M8_801312D0;   /* size 8, alignment 1 -> unaligned copy */
typedef struct { u16 f0, f2, f4; s16 f6; } Box_80133784;
typedef struct {
    u16 f0;   /* 0x0 */
    u16 f2;   /* 0x2 */
    u16 f4;   /* 0x4 */
    s16 f6;   /* 0x6 */
} Foo_80134510_80134510;
typedef struct {
    /* 0x00 */ u16 f0;
    /* 0x02 */ s16 f2;
    /* 0x04 */ s16 f4;
    /* 0x06 */ s16 f6;
    /* 0x08 */ s16 f8;
    /* 0x0A */ s16 fa;
    /* 0x0C */ s16 fc;
    /* 0x0E */ s16 fe;
    /* 0x10 */ s16 f10;
    /* 0x12 */ s16 f12;
    /* 0x14 */ s16 f14;
} S0_801347A0;
typedef struct {
    /* 0x0 */ s16 f0;
    /* 0x2 */ s16 f2;
    /* 0x4 */ s16 f4;
    /* 0x6 */ s16 f6;
} Elem_801347A0;
typedef struct {
    /* 0x0 */ u16 f0;
    /* 0x2 */ u16 f2;
    /* 0x4 */ u16 f4;
    /* 0x6 */ u16 f6;
} SVec_801347A0;
typedef struct { char s[10]; } S10_80136C90;
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
extern s32 D_80193DA4;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_8017DF74[])(void);
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
extern s32 D_80194F1C;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_80196358;
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
extern int D_80193DA4;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017DCB0)();
extern s16 (*D_8017DCB4)();
extern M2C_UNK (*D_8017DCBC)();
extern s32 (*D_8017DCC0)();
extern s32 D_80194F18;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_80193DA8;
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
extern M2C_UNK D_8017E008;
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
extern s32   D_801814EC;
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
extern M2C_UNK D_8017E020;
extern M2C_UNK D_8017E028;
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
extern void func_8012E88C(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012E8C4(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_8017E030;
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
extern unsigned char D_8017E04C[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_8017E058[];
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
extern void (*D_8017E06C[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_8017E0BC[];
extern s16 D_8017E0EC[];
extern s16 D_8017E14C[];
extern s16 D_8017E154[];
extern s16 D_8017E174[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_8017E1AC[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_8017E204[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_8017E24C[])(void);
extern void func_80131F28(void *a0);
extern void (*D_8017E254[])(void);
extern void func_80131F64(void *a0);
extern void (*D_8017E25C[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_8017E264[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_8017E20C;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_8017E22C;
extern void func_801321B0(int param_1);
extern int D_8017E23C;
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
extern void func_801330E0(s16 *a0, s16 *a1, s32 a2);
extern void func_80133060(u8 *a0, s32 *a1, s32 a2);
extern void func_8013339C(short *param_1, short *param_2);
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern s32 D_80194F88;
extern s32 D_80194F8C[];
extern int D_80194F90;
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
extern u8 D_8017E270;
extern u8 D_8017E26C;
extern s16 *D_8017E274;
extern u8 D_8017E278;
extern int D_80194F88;
extern u16 D_80194F98;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_8017E274;   /* holds a pointer value (*(u16**)&D_8017E274) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_8017E288[])(void);
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
extern s32 D_80127548[];
extern int D_8017E2DC;
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
/* ==== end §8b carried decl layer ==== */

/* func_801380E0 (ov_SC01_077_a, 438 ins, jtbl_801D81F0) — Phase 26 crack
 * Script-command interpreter: for(;;) fetch cmd byte, dispatch (>=0x20 -> extern
 * handler; ==0 -> END; else 25-case jump table), loop while `cont`.
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — x134 template-safe.
 *
 * match_one: MATCH (438 ins). jtbl VERIFIED: 25 entries, byte-identical offsets
 * (0x17C 0x184 0x220 0x218 0x20C 0x254 0x13C 0x168 0x404 0x118 0x268 0x3C0 0x3D0
 *  0x424 0x444 0x454 0x47C 0x494 0x4EC 0x544 0x58C 0x1F8 0x5B4 0x5C0 0x5E4);
 * bound `sltiu 0x19`; default -> +0x624; case 0 peel `beqz` -> +0x634; .text 0x6D8.
 *
 * FOUR levers made this land (all in the cookbook's §46/§47 family):
 *  L-A  s32 (NOT pointer) address arithmetic. `pc + base` vs `base + pc` is a real
 *       byte difference (`addu $v0,$v0,$s3` vs `addu $v0,$s3,$v0`): C's
 *       pointer_int_sum() canonicalises ptr-first and DESTROYS source operand order,
 *       so a `u8 *base` can never emit the idx-first form. Plain int + a cast at the
 *       deref keeps gcc's PLUS operand order == source order.
 *  L-B  `u32 cmd` — the `cmd >= 0x20` guard must be UNSIGNED (`sltiu`, not `slti`).
 *  L-C  THE $s5 HOIST (this is the crack). The target holds &D_8012752E in a
 *       callee-saved reg across the whole loop and reaches D_8012752C at -2($s5).
 *       gcc will NOT do this for a plain global (a symbolic address is a legitimate
 *       MIPS address — GO_IF_LEGITIMATE_ADDRESS/CONSTANT_ADDRESS_P), and a local
 *       `s16 *snd = &D_8012752E;` written INSIDE case 11 gets constant-folded straight
 *       back into `sh $x, %lo(D_8012752E)-2($at)` by cse's find_best_addr.
 *       §46-L2 is the fix: set the pointer at the LOOP TOP, so its def and its uses
 *       live in DIFFERENT extended basic blocks (the case-11 body is only reachable
 *       through the `jr` table, so cse starts a fresh hash table there and cannot
 *       fold). The `la` then survives cse, loop.c's move_movables hoists it into the
 *       PREHEADER (exactly .L80138138), and global-alloc gives it $s5.
 *       Case 25 deliberately keeps the PLAIN global (lui/lh) — matching the target.
 *  L-D  PER-CASE temps. Sharing one `q` across cases 18/19/20 makes the pseudo
 *       multi-block => it leaves local-alloc for global-alloc and both branches of
 *       case 18/19 land their result in $v0 — which lets the post-reload cross_jump
 *       tail-merge the `sh $v0,0($s0)` with the default block's store (2 ins short).
 *       Separate q18/q19/q20 keeps each block-local; the true-branch gets $v1, the
 *       false-branch $v0, and the tails stay APART (the §46-L5 register-divergence
 *       rule, here obtained for free by scoping rather than by pinning).
 *
 * Bonus (no lever needed, just don't fight it): the two out-of-line blocks at the top
 * of the function (func_80139914+return, and state=0xD+return) are loop.c
 * find_and_verify_loops (loop.c:2382) MOVING a loop-exiting block to the barrier
 * before the loop and inverting the branch around it. Writing the natural
 * `if (...) { call(); return; }` inside a real `for(;;)` reproduces it exactly.

 */


s32 func_801380E0(s32 arg0) {
    extern void func_8001931C(s32);
    extern void func_8001AAD0(s32, s32);
    extern s32 func_8001B22C(void);
    extern void func_80029124(s32, s32);
    extern s32 func_800CF864(s32, s32);
    extern void func_80138AB4(s32, s32);
    extern s32 func_80138C60(s32, s32);
    extern void func_80138D58(s32, s32);
    extern s32 func_80138DE0(s32, s32, s32);
    extern void func_801391F0(s32, s32);
    extern void func_80139220(s32, s32);
    extern void func_80139788(s32);
    extern void func_80139914(s32);
    extern void func_80139A8C(s32);
    extern void func_80139B18(s32);
    extern s16 D_8012752C;
    extern s32 D_80127530[];

    u16 *p;
    s32 base;
    s32 cont;
    u32 cmd;
    s32 sub;
    s32 pc;
    s32 t;
    s32 f;
    s32 f0;
    s32 q18;
    s32 q19;
    s32 q20;
    u32 idx;
    s16 *snd;

    t = *(u8 *)(arg0 + 0xC);
    if (t != 0) {
        *(u8 *)(arg0 + 0xC) = t - 1;
        goto done;
    }

    for (;;) {
        cont = 0;
        snd = &D_8012752E;
        if (*(s32 *)(arg0 + 8) & 0x400) {
            base = D_80127530[*(u16 *)(arg0 + 0x4A)];
            p = (u16 *)(arg0 + 0x44);
        } else {
            p = (u16 *)(arg0 + 0x10);
            base = *(s32 *)(arg0 + 0);
        }
        pc = *p;
        cmd = *(u8 *)(pc + base);
        sub = *(u8 *)(pc + base + 1);

        if (cmd >= 0x20) {
            cont = func_80138DE0(arg0, cmd, sub);
            if (!(*(s32 *)(arg0 + 8) & 0x80220)) {
                cont = 0;
            }
        } else if (cmd != 0) {
            switch (cmd) {
            case 10:
                func_80139220(arg0, cmd);
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) & ~0x80000;
                break;

            case 7:
                if (*(s32 *)(arg0 + 8) & 0x10000) {
                    cont = 1;
                } else {
                    *(s16 *)(arg0 + 4) = 3;
                }
                *p += 1;
                break;

            case 8:
                func_801391F0(arg0, cmd);
                *p += 1;
                break;

            case 1:
                *(u8 *)(arg0 + 0x23) = sub;
                cont = 1;
                *p += 2;
                break;

            case 2:
                *(u8 *)(arg0 + 0x22) = sub;
                *(u8 *)(arg0 + 0x20) = *(u8 *)(*p + base + 2);
                *p += 3;
                if (func_80138C60(arg0, cmd) == 0) {
                    func_80139914(arg0);
                    return;
                }
                *(s16 *)(arg0 + 4) = 9;
                if (*(u8 *)(base + *p) == 5) {
                    *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4000;
                    *p += 1;
                }
                break;

            case 22:
                *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) & ~0x20) | 0x4001;
                cont = 1;
                *p += 1;
                break;

            case 5:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4000;
                cont = 1;
                *p += 1;
                break;

            case 4:
                *(u8 *)(arg0 + 0xD) = sub;
                cont = 1;
                *p += 2;
                break;

            case 3:
                if (*(s32 *)(arg0 + 8) & 0x20000) {
                    cont = 1;
                    *p += 2;
                } else {
                    *(s16 *)(arg0 + 4) = 0xB;
                    *(u8 *)(arg0 + 0xD) = sub;
                    *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) | 0x8000) & ~0x20;
                }
                break;

            case 6:
                *(s16 *)(arg0 + 4) = 4;
                *p += 1;
                break;

            case 11:
                if ((*snd != 0) || (*(s32 *)(arg0 + 8) & 0x20)
                    || (func_800CF864(pc, cmd) == 0)) {
                    cont = 1;
                    *p += 4;
                } else {
                    snd[-1] = *(u8 *)(*p + base + 2) + (*(u8 *)(*p + base + 3) << 8);
                    *p += 4;
                    *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) & ~0x60020) | 0x10000;
                    if (snd[-1] != 0) {
                        func_8001AAD0(sub & 0x7F, snd[-1]);
                        if (sub & 0x80) {
                            *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x40000;
                        }
                        if ((*(u8 *)(base + *p) == 2) || (*(s32 *)(arg0 + 8) & 0x40000)) {
                            cont = 1;
                        } else {
                            *(s16 *)(arg0 + 4) = 0x10;
                        }
                        if (func_8001B22C() == 0) {
                            f = *(s32 *)(arg0 + 8);
                            if (f & 1) {
                                func_8001931C(f);
                            } else {
                                *(s32 *)(arg0 + 8) = (f & ~0x10000) | 0x20020;
                                func_80139788(f);
                            }
                            *(s16 *)(arg0 + 4) = 2;
                        }
                    } else {
                        cont = 1;
                    }
                }
                break;

            case 12:
                *(s16 *)(arg0 + 4) = 6;
                *(u8 *)(arg0 + 0x21) = 2;
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4300;
                break;

            case 13:
                *(s16 *)(arg0 + 4) = 6;
                *(u8 *)(arg0 + 0x21) = 3;
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4300;
                break;

            case 9:
                func_80138D58(arg0, sub);
                cont = 1;
                *p += 2;
                break;

            case 14:
                *(s16 *)(arg0 + 4) = 8;
                *(u16 *)(arg0 + 0x44) = 0;
                func_80138AB4(arg0, cmd);
                *p += 1;
                break;

            case 15:
                *(u16 *)(arg0 + 0x44) = 0;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x400;
                cont = 1;
                *p += 1;
                break;

            case 16:
                func_80029124(sub | (*(u8 *)(*p + base + 2) << 8), 1);
                cont = 1;
                *p += 3;
                break;

            case 17:
                func_80029124(sub | (*(u8 *)(*p + base + 2) << 8), 0);
                cont = 1;
                *p += 3;
                break;

            case 18:
                if (((u8(*)(s32, s32))func_80029178)(sub | (*(u8 *)(*p + base + 2) << 8), cmd)) {
                    q18 = *p;
                    *p = *(u8 *)(q18 + base + 3) + (q18 + 4);
                } else {
                    *p = *p + 4;
                }
                cont = 1;
                break;

            case 19:
                if (!((u8(*)(s32, s32))func_80029178)(sub | (*(u8 *)(*p + base + 2) << 8), cmd)) {
                    q19 = *p;
                    *p = *(u8 *)(q19 + base + 3) + (q19 + 4);
                } else {
                    *p = *p + 4;
                }
                cont = 1;
                break;

            case 20:
                if (!(*(s32 *)(arg0 + 8) & 0x20000)) {
                    q20 = *p + base;
                    *(u16 *)(arg0 + 0xE) = *(u8 *)(q20 + 1) + (*(u8 *)(q20 + 2) << 8);
                }
                cont = 1;
                *p += 3;
                break;

            case 21:
                if (*(u16 *)(arg0 + 0xE) != 0) {
                    *(s16 *)(arg0 + 4) = 0xF;
                } else {
                    cont = 1;
                }
                *p += 1;
                break;

            case 23:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 2;
                cont = 1;
                *p += 1;
                break;

            case 24:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x80000;
                cont = 1;
                *p += 1;
                break;

            case 25:
                *p += 1;
                if ((*(s32 *)(arg0 + 8) & 0x10000) && (D_8012752C != 0)) {
                    *(s16 *)(arg0 + 4) = 0x10;
                } else {
                    cont = 1;
                }
                break;

            default:
                *p = pc + 1;
                cont = 1;
                break;
            }
        } else {
            f0 = *(s32 *)(arg0 + 8);
            if (f0 & 0x400) {
                idx = *(u16 *)(arg0 + 0x4A);
                *(s32 *)(arg0 + 8) = f0 & ~0x400;
                if (idx < 3) {
                    *(u16 *)(arg0 + 0x4A) = idx + 1;
                }
            } else if (f0 & 0x2000) {
                *(s16 *)(arg0 + 4) = 0xD;
                return;
            } else {
                *(s16 *)(arg0 + 4) = 0xA;
                return;
            }
        }

        if (cont == 0) {
            break;
        }
    }

    if (*(u8 *)(arg0 + 0xC) == 0) {
        *(u8 *)(arg0 + 0xC) = *(u8 *)(arg0 + 0xD);
    }
done:
    func_80139A8C(arg0);
    func_80139B18(arg0);
}


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_801387B8);

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */


// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)

extern void (*D_8017E2E0[])(void);

void func_80138BE0(int p)
{
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_8017E2E0[*(short *)(p + 4)]();
}


void func_80138C30(void * a0)
{
        s16 v1 = *(s16 *)((s32)a0 + 0x4);
        if (v1 == 4) {
            *(s16 *)((s32)a0 + 0x4) = 2;
        } else {
            *(s32 *)((s32)a0 + 0x8) |= 0x800;
        }
    }


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_80138DE0);

DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ED0 (src/shared) */

DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392FC (src/shared) */

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_801395D4);

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */

DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */

DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */


extern short D_800B9A02;
extern u8 D_800A6518[];
extern u8 D_8017E324;
extern u8 D_8017E368;
extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{
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
    b164 = (u8 *)&D_8017E324;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_8017E368 + off;
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

DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399A8 (src/shared) */

DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399F0 (src/shared) */

DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139A34 (src/shared) */

DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139A44 (src/shared) */

DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139A68 (src/shared) */

DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139A8C (src/shared) */

DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139B18 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139C7C (src/shared) */

DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139D04 (src/shared) */

DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139DC8 (src/shared) */

DEFINE_func_80139DEC()  /* dedup: shared engine-core @0x80139DEC (src/shared) */

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139DF4 (src/shared) */

DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139E84 (src/shared) */

DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139F0C (src/shared) */

DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139FBC (src/shared) */

DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139FE8 (src/shared) */

DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013A0A4 (src/shared) */

DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013A164 (src/shared) */

DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013A1E8 (src/shared) */

DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013A250 (src/shared) */

DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013A2BC (src/shared) */

DEFINE_func_8013A378()  /* dedup: shared engine-core @0x8013A378 (src/shared) */

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013A380 (src/shared) */

DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013A448 (src/shared) */

DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013A4C4 (src/shared) */

DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013A530 (src/shared) */

DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013A860 (src/shared) */

DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013A8B0 (src/shared) */

DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013A8BC (src/shared) */

DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013A8FC (src/shared) */

DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013A9B4 (src/shared) */

DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013A9F8 (src/shared) */

DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013AA24 (src/shared) */

DEFINE_func_8013AB54()  /* dedup: shared engine-core @0x8013AB54 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (122 ins). GTE lerp+mvmva loop. Two levers: (1) flat `extern s16`
//   source arrays indexed [2*i]/[2*i+1] force 4 separate walking IVs (t2/t3/t4/t5) instead of
//   one shared offset-IV + symbol(reg) addressing; (2) INVERTED-arm if/else
//   `if (flag<0) out3=-tbl; else out3=tbl;` gives the target's bgez polarity + reload-per-arm
//   sign-flip block (a plain ?: hoists the common lbu; the inverted if/else does not, and gcc
//   still merges the sb). out2[i]=out2[0] tail-copy of the align-2 Pair_8013AD38 emits lwl/lwr/swl/swr.
#include "common.h"

typedef struct { s16 x, y; } Pair_8013AD38;

extern s16 D_800D45F4[];   /* src0 (flat: [2*i]=x, [2*i+1]=y) */
extern u8  D_8017E3AC[];   /* sign table, alt (when a1 < 0xC00) */

#define gte_ldv0(r0)  __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(r0) : "memory")

#define gte_mvmva0()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")

#define gte_stlvnl(r0)  __asm__ __volatile__( \
    "swc2 $25, 0(%0)\n" \
    "swc2 $26, 4(%0)\n" \
    "swc2 $27, 8(%0)\n" \
    : : "r"(r0) : "memory")

void func_8013AD38(void *flag, s32 a1, void *out2, void *out3)
{
    extern s16 D_800D466C[];
    extern u8 D_8017E3E8[];

    u8 *tbl;
    s16 vec[4];
    s32 res[3];
    s32 i;

    tbl = D_8017E3E8;
    if (((s16)a1) < 0xC00) {
        tbl = D_8017E3AC;
    }

    for (i = 0; i < 30; i++) {
        vec[0] = D_800D45F4[2 * i]     + (((D_800D466C[2 * i]     - D_800D45F4[2 * i])     * ((s16)a1)) >> 12);
        vec[1] = D_800D45F4[2 * i + 1] + (((D_800D466C[2 * i + 1] - D_800D45F4[2 * i + 1]) * ((s16)a1)) >> 12);
        gte_ldv0(vec);
        gte_mvmva0();
        gte_stlvnl(res);
        ((Pair_8013AD38 *)out2)[i].x = res[0];
        ((Pair_8013AD38 *)out2)[i].y = res[1];
        if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[2 * i];     else ((s8 *)out3)[2 * i]     = tbl[2 * i];
        if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[2 * i + 1]; else ((s8 *)out3)[2 * i + 1] = tbl[2 * i + 1];
    }
    ((Pair_8013AD38 *)out2)[i] = ((Pair_8013AD38 *)out2)[0];
    if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[0]; else ((s8 *)out3)[2 * i]     = tbl[0];
    if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[1]; else ((s8 *)out3)[2 * i + 1] = tbl[1];
}



DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013AF20 (src/shared) */

DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013B204 (src/shared) */



extern void *func_80010A08(s32);
extern s16 D_8017E424, D_8017E426, D_8017E428, D_8017E42A, D_8017E42C, D_8017E42E;
extern u16 D_800D45F6;

void func_8013B274(s32 a0, s32 a1, void *a2)
{
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
        if (!(D_8017E426 < ang)) goto outer_else;
        if (!(ang < D_8017E42C)) goto inner_else;
        if (ang < D_8017E428) { *(s16 *)L = D_8017E428; goto done; }
        if (D_8017E42A < ang) { *(s16 *)L = D_8017E42A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_8017E424) { *(s16 *)L = D_8017E424; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8017E42E < ang) { *(s16 *)L = D_8017E42E; goto done; }
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


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B568);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B598);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013B83C);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013BD34);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013BD74);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C08C);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C360);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C414);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C938);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013C964);


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
extern s32 D_80195000;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_80195000, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern M2C_UNK D_80062BC0;
extern s32 D_80195000;
extern s8 D_80195004;
extern s8 D_80195005;

void func_8013C9C4(void * arg0)
{
    D_80195000 = arg0;
    D_80195004 = 0;
    D_80195005 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}




extern s32 D_80195000;
extern s8 D_80195004;
extern s8 D_80195005;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_80195000;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_80195005;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_80195004)) * 2) + D_80195000);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_80195005 = (unsigned char) p[1];
      D_80195004 = D_80195004 + 1;
      if (D_80195005 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_80195004 = 0;
        *base = 0;
      }
    }
    else
    {
      D_80195005 = c - 1;
    }
  }
  return;
}



extern s32 D_80195024;
extern s32 D_80195018;
extern s32 D_8019501C;
extern s32 D_80195028;

void func_8013CABC(void) {
    D_80195024 = 1;
    D_80195018 = 1;
    D_8019501C = 0;
    D_80195028 = 1;
}



extern s32 D_80195018;
extern s32 D_8019501C;
extern s32 D_80195020;
extern s32 D_80195024;
extern s32 D_80195028;

void func_8013CAE8(void) {
    D_80195018 = 1;
    D_80195024 = 0;
    D_8019501C = 0;
    D_80195020 = -1;
    D_80195028 = 0;
}



extern s32 D_80195024;
extern s32 D_80195028;
extern s32 D_80195050;
extern s32 D_80195054;

void func_8013CB20(void)
{
    D_80195050 = D_80195028;
    D_80195054 = D_80195024;
    D_80195028 = 1;
    D_80195024 = 0;
}



extern s32 D_80195050;
extern s32 D_80195054;
extern s32 D_80195028;
extern s32 D_80195024;

void func_8013CB5C(void) {
    D_80195028 = D_80195050;
    D_80195024 = D_80195054;
}


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013CB84);

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
    extern u8 D_80196270;
    extern u8 D_80196271;
    extern u8 D_80196272;
    extern u8 D_80196273;
    extern u8 D_80196274;
    extern u8 D_80196275;
    extern u8 D_80196276;
    extern u8 D_80196277;
    extern u8 D_80196278;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_80196270; t1 = D_80196271; t2 = D_80196272;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_80196273; t1 = D_80196274; t2 = D_80196275;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_80196276; t1 = D_80196277; t2 = D_80196278;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_80195030;
extern s32 D_80195018;
extern s32 D_80195034;
extern s32 D_80195024;
extern void func_8013D9B0(void);

void func_8013D064(void)
{
    if (D_80195030 != 0) {
        if (D_80195030 != 2) {
            if (((D_80195030 < 3) && (D_80195030 == 1)) &&
                (D_80195034 = D_80195034 + 1, 0x23a < D_80195034)) {
                D_80195018 = D_80195030;
                D_80195030 = 2;
            }
        } else {
            D_80195018 = D_80195018 + -1;
            if (D_80195018 == 0) {
                D_80195018 = D_80195030;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_80195024 == 0) {
                    D_80195030 = D_80195030 + 1;
                }
            }
        }
    }
    return;
}




extern void func_8013D9B0(void);
extern s32 D_80195024;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_80195024;
}



extern s32 D_80195030;

void func_8013D164(void) {
    D_80195030 = 1;
}



void func_8013D178(void) {

    extern u8 D_80196270;
    extern u8 D_80196271;
    extern u8 D_80196272;
    extern u8 D_80196273;
    extern u8 D_80196274;
    extern u8 D_80196275;
    extern u8 D_80196276;
    extern u8 D_80196277;
    extern u8 D_80196278;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    extern unsigned char D_80196310, D_80196311, D_80196312, D_80196313, D_80196314, D_80196315, D_80196316, D_80196317, D_80196318;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_80196270; v = *p; t = D_80196310;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196271; v = *p; t = D_80196311;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196272; v = *p; t = D_80196312;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196273; v = *p; t = D_80196313;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196274; v = *p; t = D_80196314;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196275; v = *p; t = D_80196315;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196276; v = *p; t = D_80196316;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196277; v = *p; t = D_80196317;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_80196278; v = *p; t = D_80196318;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}



// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_80196352;
extern u8 D_801963C6;
extern u8 D_8019627A;
extern u8 D_80196334;
extern u8 D_80196258;
extern u8 D_80196279;
extern s32 D_80196338;

void func_8013D330(void) {
    if ((D_80196352 & 0xff) != D_801963C6) {
        D_80196352 = ((D_80196352 & 0xff) < D_801963C6) ? (D_80196352 + 1) : (D_80196352 - 1);
    }
    if ((D_8019627A & 0xff) != D_80196334) {
        D_8019627A = ((D_8019627A & 0xff) < D_80196334) ? (D_8019627A + 1) : (D_8019627A - 1);
    }
    if ((D_80196258 & 0xff) != D_80196279) {
        D_80196258 = ((D_80196258 & 0xff) < D_80196279) ? (D_80196258 + 1) : (D_80196258 - 1);
    }
    D_80196338 = 1;
}




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_80195008;
extern void *D_8019500C;
extern void *D_80195010;
extern s32 D_80195038;
extern s32 D_8019503C;
extern s32 D_80195040;
extern s32 D_801962AC[];

extern u8 D_8017E51C[];
extern u8 D_8017E5C4[];
extern u8 D_8017E474[];
extern u8 D_8017E570[];
extern u8 D_8017E5F0[];
extern u8 D_8017E4C8[];

extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_80195038 = param_2;
    D_8019503C = (param_2 >> 2) & 3;
    D_80195040 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_80195008 = D_8017E51C;
        D_8019500C = D_8017E5C4;
        D_80195010 = D_8017E474;
    } else {
        D_80195008 = D_8017E570;
        D_8019500C = D_8017E5F0;
        D_80195010 = D_8017E4C8;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_80195040 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_80195038 & 2) != 0) {
            D_801962AC[0] = 0x140;
            D_801962AC[3] = 0x80;
            if (p[0x37] == 4) {
                D_801962AC[0] = 0x140;
                D_801962AC[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801962AC[0] = 0x140;
                D_801962AC[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013D53C);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013D9B0);


// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_80195010)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_80195010;
extern s16 *D_80195014;
extern s32 D_80195024;
extern s32 D_80195044;
extern s32 D_80195048;
extern s32 D_8019504C;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_80195014 != 0) {
        D_80195024 = 0;
        p = (int *)(param_1 * 12 + (int)D_80195010);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_80195044 != x) {
            flag = 1;
            if (D_80195044 < x) {
                if (x - D_80195044 < 5) {
                    D_80195044 = x;
                } else {
                    D_80195044 = D_80195044 + 4;
                }
            } else {
                if (D_80195044 - x < 5) {
                    D_80195044 = x;
                } else {
                    D_80195044 = D_80195044 - 4;
                }
            }
        }
        if (D_80195048 != y) {
            flag = 1;
            if (D_80195048 < y) {
                if (y - D_80195048 < 5) {
                    D_80195048 = y;
                } else {
                    D_80195048 = D_80195048 + 4;
                }
            } else {
                if (D_80195048 - y < 5) {
                    D_80195048 = y;
                } else {
                    D_80195048 = D_80195048 - 4;
                }
            }
        }
        if (D_8019504C != z) {
            flag = 1;
            if (D_8019504C < z) {
                if (z - D_8019504C < 5) {
                    D_8019504C = z;
                } else {
                    D_8019504C = D_8019504C + 4;
                }
            } else {
                if (D_8019504C - z < 5) {
                    D_8019504C = z;
                } else {
                    D_8019504C = D_8019504C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_80195024 = flag;
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (187 ins). Levers: struct-assign DRAWENV copy (align via type); pbase local for $s2-relative D_800B9A02; two-biv SPRT loop (q anchored one-above -> gcc re-anchors, no bare-deref); P_TAG_8013DD68 addPrim; single p var coalesces puVar7->puVar15; pins uVar2=$v1,iVar14=$a3,c5=$t3; biv-increment order sets q-init-before-puVar10-init; Buf_8013DD68 0x68 -> frame 0xA0.

typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG_8013DD68;
typedef struct { u32 w[23]; } DrawEnv_8013DD68;              /* 0x5C copy unit, align 4 */
typedef struct { DrawEnv_8013DD68 env; u8 pad[0x0C]; } Buf_8013DD68;  /* -> frame 0xA0 (gcc adds 0x10 for the struct-copy) */


#define IDVAL (*(u16 *)(pbase + 0xA3D2))
#define OTE ((P_TAG_8013DD68 *)(D_800BA0E4 + IDVAL * 0x10))

void func_8013DD68() {
    extern void SetDrawEnv(void *p, void *env);
    extern u16 D_800AF7B8;
    extern u8 D_800BA0E4[];
    extern u8 D_8017E680[];

    u32 *p;
    u16 uVar1;
    u16 *puVar16;
    u16 *q;
    u16 *puVar10;
    register u16 uVar2 __asm__("$3");
    int uVar5;
    register int iVar14 __asm__("$7");
    Buf_8013DD68 buf;
    u8 *pbase;
    u8 *base;

    pbase = D_800AF630;
    puVar16 = (*(u16 * *)&D_80195014);
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
        register int c5 __asm__("$11") = 5;
        puVar10 = (u16 *)((int)p + 0x18);
        q = puVar16 + 8;
        do {
            *(u8 *)((int)puVar10 + -0x15) = c5;
            uVar2 = q[-6];
            *(u8 *)((int)puVar10 + -0xd) = 100;
            *(u8 *)((int)puVar10 + -0x10) = (u8)(*(int*)&D_80195044);
            *(u8 *)((int)puVar10 + -0xf) = (u8)(*(int*)&D_80195048);
            uVar5 = (*(int*)&D_8019504C);
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
    SetDrawEnv(p, D_8017E680);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    (*(u32 * *)&D_800A5E60) = p;
    return;
}




extern s32 D_8019502C;

s32 func_8013E054(void) {
    return D_8019502C;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013E064 (src/shared) */

DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013E0FC (src/shared) */

DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013E194 (src/shared) */

DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013E22C (src/shared) */

DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013E298 (src/shared) */

DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013E2C4 (src/shared) */

DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013E370 (src/shared) */

DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013E410 (src/shared) */

DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013E448 (src/shared) */

DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013E4B4 (src/shared) */

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013E558 (src/shared) */

DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013E588 (src/shared) */


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
    extern void (*D_8017F090[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8017F090[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013E67C (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_8017F07C;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_8017F054;
extern s16 D_8017F056;
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
        register s32 *ep __asm__("$8");
        register s32 *fp __asm__("$9");
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_8017F07C;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_8017F054 = 2;
        D_8017F056 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8017F056 = 0;
        D_8017F054 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013E814 (src/shared) */

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
    extern void * D_80195060;
    extern void * D_80195064;
    extern unsigned char D_8017ECF4;
    extern unsigned char D_8017ED0C;
    extern unsigned char D_8017ED80;
    extern unsigned char D_8017ED88;


    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((((int(*)(int))func_80029178)(0x1c) & 0xFF) == 0) {
        D_80195060 = &D_8017ECF4;
        D_80195064 = &D_8017ED80;
    } else {
        D_80195060 = &D_8017ED0C;
        D_80195064 = &D_8017ED88;
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
// three bases (D_80115110/D_8017F07C/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_8017F07C -> $a3) and freeing the delay slot
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
        v = ((s32 *)&D_8017F07C)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}



DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013EA54 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern void func_8013F350(void);
extern void func_8013FAF8(s32 a0, s32 a1);
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
extern unsigned char D_8017F058;

void func_8013EB7C(void) {
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8017F058));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8017F058));
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


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ED6C (src/shared) */

extern short D_800B9A02;
extern unsigned short D_80115112;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern s16 D_8017F054;
extern s16 D_8017F056;
extern unsigned char D_8017F058;
extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s32 a0, s32 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8017F056` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_8017F054` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

typedef struct { s32 f0; } E4;



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
    r = &D_8017F056;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_8017F054 = (u16)D_8017F054 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8017F058);
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


INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013EF88);


// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_8017F058;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8017F058);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013F1BC (src/shared) */

DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013F244 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013F350);

INCLUDE_ASM("asm/ov_SC02_004/nonmatchings/ov_SC02_004_jr_801380E0", func_8013FAF8);

