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
extern s32 D_801AC170;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_80188520[])(void);
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
extern s32 D_801AD2EC;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_801B20E0;
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
extern int D_801AC170;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8018825C)();
extern s16 (*D_80188260)();
extern M2C_UNK (*D_80188268)();
extern s32 (*D_8018826C)();
extern s32 D_801AD2E8;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_801AC174;
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
extern M2C_UNK D_801885B4;
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
extern s32   D_8018BA98;
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
extern M2C_UNK D_801885CC;
extern M2C_UNK D_801885D4;
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
extern int D_801885DC;
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
extern unsigned char D_801885F8[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_80188604[];
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
extern void (*D_80188618[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80188668[];
extern s16 D_80188698[];
extern s16 D_801886F8[];
extern s16 D_80188700[];
extern s16 D_80188720[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_80188758[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_801887B0[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_801887F8[])(void);
extern void func_80131F28(void *a0);
extern void (*D_80188800[])(void);
extern void func_80131F64(void *a0);
extern void (*D_80188808[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_80188810[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_801887B8;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_801887D8;
extern void func_801321B0(int param_1);
extern int D_801887E8;
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
extern s32 D_801AD358;
extern s32 D_801AD35C[];
extern int D_801AD360;
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
extern u8 D_8018881C;
extern u8 D_80188818;
extern s16 *D_80188820;
extern u8 D_80188824;
extern int D_801AD358;
extern u16 D_801AD368;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_80188820;   /* holds a pointer value (*(u16**)&D_80188820) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_80188834[])(void);
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
extern int D_80188888;
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


DEFINE_func_801387B8()  /* dedup: shared engine-core @0x801387B8 (src/shared) */

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */


// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)

extern void (*D_8018888C[])(void);

void func_80138BE0(int p)
{
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_8018888C[*(short *)(p + 4)]();
}


DEFINE_func_80138C30()  /* dedup: shared engine-core @0x80138C30 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80138DE0);

DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ED0 (src/shared) */

DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392FC (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_801395D4);

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */

DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */

DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */


extern short D_800B9A02;
extern u8 D_800A6518[];
extern u8 D_801888D0;
extern u8 D_80188914;
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
    b164 = (u8 *)&D_801888D0;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_80188914 + off;
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

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80139BE0);

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
extern u8  D_80188958[];   /* sign table, alt (when a1 < 0xC00) */

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
    extern u8 D_80188994[];

    u8 *tbl;
    s16 vec[4];
    s32 res[3];
    s32 i;

    tbl = D_80188994;
    if (((s16)a1) < 0xC00) {
        tbl = D_80188958;
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
extern s16 D_801889D0, D_801889D2, D_801889D4, D_801889D6, D_801889D8, D_801889DA;
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
        if (!(D_801889D2 < ang)) goto outer_else;
        if (!(ang < D_801889D8)) goto inner_else;
        if (ang < D_801889D4) { *(s16 *)L = D_801889D4; goto done; }
        if (D_801889D6 < ang) { *(s16 *)L = D_801889D6; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_801889D0) { *(s16 *)L = D_801889D0; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_801889DA < ang) { *(s16 *)L = D_801889DA; goto done; }
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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B568);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B598);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013B83C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013BD34);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013BD74);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C08C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C360);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C414);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C938);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013C964);


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
extern s32 D_801AD3D0;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_801AD3D0, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern M2C_UNK D_80062BC0;
extern s32 D_801AD3D0;
extern s8 D_801AD3D4;
extern s8 D_801AD3D5;

void func_8013C9C4(void * arg0)
{
    D_801AD3D0 = arg0;
    D_801AD3D4 = 0;
    D_801AD3D5 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}




extern s32 D_801AD3D0;
extern s8 D_801AD3D4;
extern s8 D_801AD3D5;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_801AD3D0;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801AD3D5;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801AD3D4)) * 2) + D_801AD3D0);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801AD3D5 = (unsigned char) p[1];
      D_801AD3D4 = D_801AD3D4 + 1;
      if (D_801AD3D5 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801AD3D4 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801AD3D5 = c - 1;
    }
  }
  return;
}



extern s32 D_801AD3F4;
extern s32 D_801AD3E8;
extern s32 D_801AD3EC;
extern s32 D_801AD3F8;

void func_8013CABC(void) {
    D_801AD3F4 = 1;
    D_801AD3E8 = 1;
    D_801AD3EC = 0;
    D_801AD3F8 = 1;
}



extern s32 D_801AD3E8;
extern s32 D_801AD3EC;
extern s32 D_801AD3F0;
extern s32 D_801AD3F4;
extern s32 D_801AD3F8;

void func_8013CAE8(void) {
    D_801AD3E8 = 1;
    D_801AD3F4 = 0;
    D_801AD3EC = 0;
    D_801AD3F0 = -1;
    D_801AD3F8 = 0;
}



extern s32 D_801AD3F4;
extern s32 D_801AD3F8;
extern s32 D_801AD420;
extern s32 D_801AD424;

void func_8013CB20(void)
{
    D_801AD420 = D_801AD3F8;
    D_801AD424 = D_801AD3F4;
    D_801AD3F8 = 1;
    D_801AD3F4 = 0;
}



extern s32 D_801AD420;
extern s32 D_801AD424;
extern s32 D_801AD3F8;
extern s32 D_801AD3F4;

void func_8013CB5C(void) {
    D_801AD3F8 = D_801AD420;
    D_801AD3F4 = D_801AD424;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013CB84);

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
    extern u8 D_801B1FF8;
    extern u8 D_801B1FF9;
    extern u8 D_801B1FFA;
    extern u8 D_801B1FFB;
    extern u8 D_801B1FFC;
    extern u8 D_801B1FFD;
    extern u8 D_801B1FFE;
    extern u8 D_801B1FFF;
    extern u8 D_801B2000;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801B1FF8; t1 = D_801B1FF9; t2 = D_801B1FFA;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801B1FFB; t1 = D_801B1FFC; t2 = D_801B1FFD;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801B1FFE; t1 = D_801B1FFF; t2 = D_801B2000;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_801AD400;
extern s32 D_801AD3E8;
extern s32 D_801AD404;
extern s32 D_801AD3F4;
extern void func_8013D9B0(void);

void func_8013D064(void)
{
    if (D_801AD400 != 0) {
        if (D_801AD400 != 2) {
            if (((D_801AD400 < 3) && (D_801AD400 == 1)) &&
                (D_801AD404 = D_801AD404 + 1, 0x23a < D_801AD404)) {
                D_801AD3E8 = D_801AD400;
                D_801AD400 = 2;
            }
        } else {
            D_801AD3E8 = D_801AD3E8 + -1;
            if (D_801AD3E8 == 0) {
                D_801AD3E8 = D_801AD400;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801AD3F4 == 0) {
                    D_801AD400 = D_801AD400 + 1;
                }
            }
        }
    }
    return;
}




extern void func_8013D9B0(void);
extern s32 D_801AD3F4;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801AD3F4;
}



extern s32 D_801AD400;

void func_8013D164(void) {
    D_801AD400 = 1;
}



void func_8013D178(void) {

    extern u8 D_801B1FF8;
    extern u8 D_801B1FF9;
    extern u8 D_801B1FFA;
    extern u8 D_801B1FFB;
    extern u8 D_801B1FFC;
    extern u8 D_801B1FFD;
    extern u8 D_801B1FFE;
    extern u8 D_801B1FFF;
    extern u8 D_801B2000;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    extern unsigned char D_801B2098, D_801B2099, D_801B209A, D_801B209B, D_801B209C, D_801B209D, D_801B209E, D_801B209F, D_801B20A0;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801B1FF8; v = *p; t = D_801B2098;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FF9; v = *p; t = D_801B2099;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFA; v = *p; t = D_801B209A;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFB; v = *p; t = D_801B209B;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFC; v = *p; t = D_801B209C;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFD; v = *p; t = D_801B209D;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFE; v = *p; t = D_801B209E;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B1FFF; v = *p; t = D_801B209F;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801B2000; v = *p; t = D_801B20A0;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}



// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_801B20DA;
extern u8 D_801B2186;
extern u8 D_801B2002;
extern u8 D_801B20BC;
extern u8 D_801B1FE0;
extern u8 D_801B2001;
extern s32 D_801B20C0;

void func_8013D330(void) {
    if ((D_801B20DA & 0xff) != D_801B2186) {
        D_801B20DA = ((D_801B20DA & 0xff) < D_801B2186) ? (D_801B20DA + 1) : (D_801B20DA - 1);
    }
    if ((D_801B2002 & 0xff) != D_801B20BC) {
        D_801B2002 = ((D_801B2002 & 0xff) < D_801B20BC) ? (D_801B2002 + 1) : (D_801B2002 - 1);
    }
    if ((D_801B1FE0 & 0xff) != D_801B2001) {
        D_801B1FE0 = ((D_801B1FE0 & 0xff) < D_801B2001) ? (D_801B1FE0 + 1) : (D_801B1FE0 - 1);
    }
    D_801B20C0 = 1;
}




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_801AD3D8;
extern void *D_801AD3DC;
extern void *D_801AD3E0;
extern s32 D_801AD408;
extern s32 D_801AD40C;
extern s32 D_801AD410;
extern s32 D_801B2034[];

extern u8 D_80188AC8[];
extern u8 D_80188B70[];
extern u8 D_80188A20[];
extern u8 D_80188B1C[];
extern u8 D_80188B9C[];
extern u8 D_80188A74[];

extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_801AD408 = param_2;
    D_801AD40C = (param_2 >> 2) & 3;
    D_801AD410 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801AD3D8 = D_80188AC8;
        D_801AD3DC = D_80188B70;
        D_801AD3E0 = D_80188A20;
    } else {
        D_801AD3D8 = D_80188B1C;
        D_801AD3DC = D_80188B9C;
        D_801AD3E0 = D_80188A74;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801AD410 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801AD408 & 2) != 0) {
            D_801B2034[0] = 0x140;
            D_801B2034[3] = 0x80;
            if (p[0x37] == 4) {
                D_801B2034[0] = 0x140;
                D_801B2034[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801B2034[0] = 0x140;
                D_801B2034[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013D53C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013D9B0);


// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801AD3E0)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_801AD3E0;
extern s16 *D_801AD3E4;
extern s32 D_801AD3F4;
extern s32 D_801AD414;
extern s32 D_801AD418;
extern s32 D_801AD41C;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_801AD3E4 != 0) {
        D_801AD3F4 = 0;
        p = (int *)(param_1 * 12 + (int)D_801AD3E0);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801AD414 != x) {
            flag = 1;
            if (D_801AD414 < x) {
                if (x - D_801AD414 < 5) {
                    D_801AD414 = x;
                } else {
                    D_801AD414 = D_801AD414 + 4;
                }
            } else {
                if (D_801AD414 - x < 5) {
                    D_801AD414 = x;
                } else {
                    D_801AD414 = D_801AD414 - 4;
                }
            }
        }
        if (D_801AD418 != y) {
            flag = 1;
            if (D_801AD418 < y) {
                if (y - D_801AD418 < 5) {
                    D_801AD418 = y;
                } else {
                    D_801AD418 = D_801AD418 + 4;
                }
            } else {
                if (D_801AD418 - y < 5) {
                    D_801AD418 = y;
                } else {
                    D_801AD418 = D_801AD418 - 4;
                }
            }
        }
        if (D_801AD41C != z) {
            flag = 1;
            if (D_801AD41C < z) {
                if (z - D_801AD41C < 5) {
                    D_801AD41C = z;
                } else {
                    D_801AD41C = D_801AD41C + 4;
                }
            } else {
                if (D_801AD41C - z < 5) {
                    D_801AD41C = z;
                } else {
                    D_801AD41C = D_801AD41C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801AD3F4 = flag;
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
    extern u8 D_80188C2C[];

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
    puVar16 = (*(u16 * *)&D_801AD3E4);
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
            *(u8 *)((int)puVar10 + -0x10) = (u8)(*(int*)&D_801AD414);
            *(u8 *)((int)puVar10 + -0xf) = (u8)(*(int*)&D_801AD418);
            uVar5 = (*(int*)&D_801AD41C);
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
    SetDrawEnv(p, D_80188C2C);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    (*(u32 * *)&D_800A5E60) = p;
    return;
}




extern s32 D_801AD3FC;

s32 func_8013E054(void) {
    return D_801AD3FC;
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
    extern void (*D_8018963C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018963C[D_80115112];
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
extern s32 D_80189628;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_80189600;
extern s16 D_80189602;
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
        ep = (s32 *)&D_80189628;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80189600 = 2;
        D_80189602 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_80189602 = 0;
        D_80189600 = 0;
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
    extern void * D_801AD430;
    extern void * D_801AD434;
    extern unsigned char D_801892A0;
    extern unsigned char D_801892B8;
    extern unsigned char D_8018932C;
    extern unsigned char D_80189334;


    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((((int(*)(int))func_80029178)(0x1c) & 0xFF) == 0) {
        D_801AD430 = &D_801892A0;
        D_801AD434 = &D_8018932C;
    } else {
        D_801AD430 = &D_801892B8;
        D_801AD434 = &D_80189334;
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
// three bases (D_80115110/D_80189628/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80189628 -> $a3) and freeing the delay slot
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
        v = ((s32 *)&D_80189628)[i] >> 6;
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
extern unsigned char D_80189604;

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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_80189604));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_80189604));
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
extern s16 D_80189600;
extern s16 D_80189602;
extern unsigned char D_80189604;
extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_80189602` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_80189600` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

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
    r = &D_80189602;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_80189600 = (u16)D_80189600 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80189604);
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


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013EF88);


// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_80189604;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80189604);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013F1BC (src/shared) */

DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013F244 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013F350);


// @class: regalloc-order
// @stuck: none — MATCH (312/312, relocation-masked)








typedef struct { u16 f0; s16 f2; } Prim4;
typedef struct { s16 x; s16 y; } Hw4;
typedef struct { s32 f0; u32 *f4; s32 f8; s32 fC; s32 f10; } Rec20;
typedef struct { u8 d[0x60]; } Blk60;


extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958(s32 *, s32, s32);
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

extern s32    D_801151D0;
extern u16    D_8011511A;
extern short D_80115128;
extern u8     D_80078EC0;
extern short D_800B9A02;
extern s16    D_80189600;
extern s16    D_80189602;

void func_8013FAF8(s16 arg0, s16 arg1) {

    extern Hw4    D_8011516A[];
    extern Rec20  D_800AE7B8[];
    extern Blk60  D_80188C88[];
    extern Blk20  D_80188F88[];
    extern Prim4  D_80189088[];
    extern Prim4  D_801890F8[];
    extern Prim4 *D_801891EC[];
    extern s32    D_8018920C[];
    extern u8 D_8018922C;
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
        p = &D_80189088[i];
        if (i != 5) {
            if (i == 2) {
                addr = ((s32 *)&D_8018922C)[*(s16 *)&D_80115128];
            } else {
                addr = D_8018920C[i];
            }
        } else {
            addr = func_8013FFD8(2, func_8014168C(2), sp60);
        }
        func_80024054(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_801891EC[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && *(s16 *)&D_80115128 != 0) {
                p = D_801890F8;
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
                           func_800D27DC(flag3 != 0, ot + 10, &D_80188C88[i], 8, D_8011516A[i].x),
                           &D_80188F88[i], 2, D_8011516A[i].x);
    }
    pp = &D_80189600;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &D_800AE7B8[*(u16 *)&D_800B9A02], 2);
    }
    if (*pp != 0 && D_80189602 != 0) {
        ot = func_8013AB54(ot, D_800AE7B8[*(u16 *)&D_800B9A02].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    D_801151D0 = (s32)ot;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8014032C);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80140608);


// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).

extern u8 *D_801892E0;
extern u8 *D_801892E4;
extern u8 *D_801892E8;
extern u8 *D_801892EC;
extern u8 *D_801892F0;
extern u16 *D_801892F4[];
extern u16 *D_801892FC[];
extern u16 *D_8018931C[];

extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

void func_801407F4(void)
{
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_801892E0;
    iVar2 = func_80028D58();
    puVar3 = D_801892F4[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_801892E4;
    iVar2 = func_80028DE0();
    puVar3 = D_801892F4[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_801892E8 + 0x18) = *D_801892FC[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_801892EC + 0x18) = *D_801892FC[iVar2];

    puVar1 = D_801892F0;
    iVar2 = func_80028D9C();
    puVar3 = D_8018931C[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80140958);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80140D68);


// @class: struct
// @stuck: none — MATCH

extern unsigned char D_80078E7F;
extern unsigned char D_80078E7E;
extern unsigned char D_80078E7D;
extern M2C_UNK D_8018921C;

extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_8018921C);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)

extern short D_80115128;
extern u8 D_8018922C;
extern char *D_8018924C;
extern char *D_80189250;
extern char *D_80189254;
extern char *D_80189258;
extern char *D_8018925C;

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
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_8018922C);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_8018924C;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80189250;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80189254;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80189258;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018925C;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}



// @class: other
// @stuck: none — MATCH

extern short D_80115128;
extern unsigned short D_80115172;
extern unsigned short D_801890E6;
extern unsigned short D_801890EA;
extern unsigned short D_801890EE;
extern unsigned short D_801890F2;

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
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_801890E6;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_801890EA;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_801890EE;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_801890F2;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_801412A8);

DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415C0 (src/shared) */

DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168C (src/shared) */

DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416D4 (src/shared) */


extern unsigned short D_80115112;
extern void (*D_8018967C[])(void);

void func_80141788(void)
{
    D_8018967C[D_80115112]();
}


DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417C4 (src/shared) */

DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417F8 (src/shared) */


extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);

extern u16 D_8011511E;
extern unsigned short D_80115112;

void func_80141874(void) {

    extern u16 D_8011511C;
    extern u16 D_80115116;
    extern void (*D_80189688[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80189688[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_801418F8);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80141A60);

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80141B90);

DEFINE_func_80141C04()  /* dedup: shared engine-core @0x80141C04 (src/shared) */


// @class: struct
// @stuck: none — MATCH expected (indexed u16 global: (s16)param_1*2 + D_80115110, *2 array stride)

extern u16 D_80115110;
extern u8 D_801895DC;
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80141C0C(s32 param_1)
{
    func_8002D4C8(*(u16 *)(&D_801895DC + (((param_1 << 16) >> 15) + (u32)D_80115110) * 2), 0);
}


DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141C50 (src/shared) */

DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141CA4 (src/shared) */

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

    extern void (*D_801896AC[])(void);
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_801896AC[(unsigned short)param_1[1]])();
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



extern void (*D_801896BC[])(void);

void func_801425CC(void *a0) {
    D_801896BC[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_801896A0;

void func_80142608(s32 param_1)
{
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_801896A0);
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


DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426D4 (src/shared) */

DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */

DEFINE_func_80142778()  /* dedup: shared engine-core @0x80142778 (src/shared) */

DEFINE_func_801427DC()  /* dedup: shared engine-core @0x801427DC (src/shared) */

DEFINE_func_801427E4()  /* dedup: shared engine-core @0x801427E4 (src/shared) */


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801896D0[])();

void func_801427EC(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_801896D0[*(u16 *)(param_1 + 2)]();
    }
}


DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428CC (src/shared) */


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801896EC[])();

void func_8014292C(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_801896EC[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801898BC[])();

void func_80142978(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_801898BC[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_80189974[])();

void func_801429C4(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_80189974[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80142A10);


// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)

extern u16 D_800B99D8;
extern struct packed_word D_801ACB00;
extern u8 D_801AD438;
extern u8 D_801AD439;
extern u8 D_801AD43A;

void func_80142A80(void)
{
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801ACB00;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801AD438 = mul * (local.b[0] >> 4);
    D_801AD439 = mul * (local.b[1] >> 4);
    D_801AD43A = mul * (local.b[2] >> 4);
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80142B2C);

DEFINE_func_80142BB4()  /* dedup: shared engine-core @0x80142BB4 (src/shared) */

DEFINE_func_80142C7C()  /* dedup: shared engine-core @0x80142C7C (src/shared) */

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142C84 (src/shared) */

DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142C9C (src/shared) */

DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142D38 (src/shared) */

DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142DB8 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern int D_801896C4;

void func_80142DC4(int param_1)
{
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_801896C4);
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

extern unsigned char D_801896E0[];

void func_80142E38(int param_1)
{
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_801896E0);
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

    extern s32 D_801898AC[];
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
        ((void (*)(s32, s32))func_8012A828)(d, D_801898AC[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}


DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142F68 (src/shared) */

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142FFC (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_801898CC[];
extern unsigned char D_8018992C[];

void func_8014305C(int param_1)
{
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
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_801898CC);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_8018992C);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430F4 (src/shared) */

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

extern u8 D_801ACAFC;
extern u8 D_801AD438;
extern u8 D_801AD43C;

void func_801431E8(s32 param_1) {
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801ACAFC, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801AD438);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801AD438, 0x10);
            memcpy(&D_801AD43C, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432FC (src/shared) */

DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */

DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433F0 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (pending gate)

extern u8 D_800D387C[];
extern u32 D_80189A84[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{
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
                  D_80189A84[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_8014350C()  /* dedup: shared engine-core @0x8014350C (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_8014358C);

DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */

DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437D8 (src/shared) */

DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */

DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */

DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439C0 (src/shared) */

DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439FC (src/shared) */


extern void (*D_80189BAC[])(void);

void func_80143B30(void *a0) {
    D_80189BAC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143B6C (src/shared) */

DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143BDC (src/shared) */


extern void (*D_80189BB8[])(void);

void func_80143C38(void *a0) {
    D_80189BB8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143C74 (src/shared) */


extern void (*D_80189BC0[])(void);

void func_80143C98(void *a0) {
    D_80189BC0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143CD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80143D28);


extern void (*D_80189C08[])(void);

void func_80143E68(void *a0) {
    D_80189C08[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143EA4()  /* dedup: shared engine-core @0x80143EA4 (src/shared) */

DEFINE_func_80143EAC()  /* dedup: shared engine-core @0x80143EAC (src/shared) */

DEFINE_func_80143EB4()  /* dedup: shared engine-core @0x80143EB4 (src/shared) */

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143EBC (src/shared) */


extern void (*D_80189C1C[])(void);

void func_80144054(void *a0) {
    D_80189C1C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80144090);

extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)

extern void (*D_80189C24[])();

void func_801442F8(int param_1)
{
    int iVar1;

    D_80189C24[*(u16 *)(param_1 + 2)]();
    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (0x1d < iVar1) {
        func_8012C218(param_1);
    }
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189BA0;

void func_80144364(int param_1) {
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
        func_8001CB6C((u8 *)iVar3, (s32)&D_80189BA0, 0x250, 0x1A0);
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
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_80189BB4;

void func_80144458(void *arg0) {
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s2 = M2C_FIELD(arg0, void **, 0xCC);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_s0 = (M2C_FIELD(temp_v0, s16 *, 0x12) - 0x400) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (func_80047948(temp_s0) * D_80189BB4 * 0x10);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (func_8004787C(temp_s0) * -D_80189BB4 * 0x10);
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

DEFINE_func_8014462C()  /* dedup: shared engine-core @0x8014462C (src/shared) */

DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446A4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_80189BC8;
extern u8 D_80189BD4;

void func_8014477C(void *param_1) {
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
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_80189BC8);
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
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_80189BD4);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

extern u8 D_80189BA0;
extern u8 D_80189C10;

void func_80144880(s32 param_1)
{
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
            func_8001CB6C((u8 *)obj, (s32)&D_80189BA0, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_80189C10, 0x300, 0x1D0);
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


extern void (*D_80189C2C[])(void);

void func_801449C8(void *a0) {
    D_80189C2C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144A04 (src/shared) */


extern void (*D_80189C34[])(void);

void func_80144A2C(void *a0) {
    D_80189C34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144A68 (src/shared) */

DEFINE_func_80144A90()  /* dedup: shared engine-core @0x80144A90 (src/shared) */

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144A98 (src/shared) */

DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144AEC (src/shared) */

INCLUDE_ASM("asm/ov_SC06_000/nonmatchings/ov_SC06_000_jr_801380E0", func_80144B14);

