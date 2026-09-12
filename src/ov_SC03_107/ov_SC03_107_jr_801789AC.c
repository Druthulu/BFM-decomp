#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
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
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B6BC;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B9F8;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016C2C4;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016CBC0;
typedef void (*Handler)(struct Entry *);
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EB3C;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EC0C;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016F1C4;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80175DA8;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176218;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176734;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177B5C;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177DA8;
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80178970;
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
extern void func_80142BB4(s32* param_1, s32 param_2, s32 param_3);
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
extern s32 func_8004787C(s32 a0);
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
extern s32 func_80047948(s32 a0);
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
extern void (*D_80183F98[])(void *);
extern void func_8014C6F4();
extern void func_80155150(s32 a0);
extern void func_801470C0(s32 a0);
extern void func_80147478(s32 a0);
extern void func_80147118(s32 a0);
extern void func_8014BDE8(s32 a0);
extern short func_801508F8(s32 a0);
extern void func_8014B5B0(s32 *a0);
extern void func_80161D88();
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
extern s32 D_80127090;
extern s32 D_80127094;
extern s32 D_80127098;
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
void func_8012F14C(s32 a0, s32 a1, s32 a2);
void func_8012EF70(s32 a0, s32 a1);
extern void func_80149544(s32 a0, s32 a1, s32 a2);
void func_8012EFB8(s32 a0);
extern void func_80149584(s32 param_1, s32 param_2, s32 param_3);
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
extern void func_80162CCC();
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
extern void func_8014D3E0();
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
extern s32 func_8014F468();
extern int func_8014F6F4();
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
extern s32 func_801659DC();
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
extern void func_80157788(int param_1);
extern void func_80157808();
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
extern void func_80161D20();
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
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern void func_80161CD0(s32 a0, s32 a1);
extern s32 D_80184AD8;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern s32 D_800D4B48;
extern void func_8015B8F8(s32 *a0);
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94();
extern void func_8015BE38();
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015AE2C();
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void func_8015C788(s32);
extern void func_8015C750(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80161240(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8015C7E4(u16 *param_1);
extern void func_8015C944(int param_1);
extern void func_8015CA28(u16 *param_1);
extern void func_8015CB94(s32 a0);
extern void func_8015CBCC(void);
extern void func_8015CBD4(void);
extern void func_8015CBDC(void);
extern void func_8015CBE4(void);
extern void func_8015CBEC(void);
extern void func_8015CBF4(void);
extern void func_8015CBFC(void);
extern void func_8015CC04(void);
extern void func_8015CC0C(s32 *param_1);
extern void func_8015CC74();
extern void func_8015CC40(s32 *a0);
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern s32 func_8015CD20(s32 arg0);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0();
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 func_80149FB0(s32);
extern void func_80146DB8(s32*, s32*);
extern void func_8014FA04(s32);
extern void func_80159B70(void*);
extern void func_8015D380(s32);
extern void func_8015D1B8(s32 *a0);
extern void func_8015D380(s32 a0);
extern void func_8015D414(int param_1);
extern void func_8015D57C(s32);
extern void func_8015D480(s32 *a0);
extern s32 func_8015D4E8();
extern void func_8015D4B4(s16 *a0);
extern void func_8015D524(s32 arg0);
extern void func_8015D544(s32 a0);
extern void func_801746DC(void);
extern void func_8015D57C(s32 arg0);
extern void func_80154150(int, int);
extern void func_80149374(int, int);
extern void func_8015D5E8(int param_1);
extern int func_8015E0D4(int);
extern void func_8015DA5C(s32 a0);
extern void func_8015DB6C(s32 a0);
extern void func_8015DA90(s32 *a0);
extern void func_8015DAF8();
extern void func_8015DB6C(s32);
extern void func_8015DB34(s32 a0);
extern void func_8015DCB8(s32 a0);
extern int func_8015DD74(int);
extern void func_8015DBD4(void *arg0);
extern int func_8015DC84(int a0);
extern void func_8015DCB8(s32 param_1);
extern int func_8015DD74(int arg0);
extern void func_8015DECC(s32 a0);
extern void func_8015DDF0(s32 *a0);
extern void func_8015DE58();
extern void func_8015DECC(s32);
extern void func_8015DE94(s32 a0);
extern void func_8015E018(s32 a0);
extern void func_8015DF34(void *arg0);
extern int func_8015DFE4(int a0);
extern void func_8015E018(s32 param_1);
extern int func_8015E0D4(int a0);
extern void func_8015E22C(s32 a0);
extern void func_8015E150(s32 *a0);
extern s32 func_8015E1B8();
extern void func_8015E184(s32 *arg0);
extern void func_8015E22C(s32);
extern void func_8015E1F4(s32 a0);
extern u8 D_800D4FF4[];
extern u8 D_800D5098[];
extern u8 D_800D5060[];
extern s32 func_8014A850(s32 a0);
extern void func_8015E40C(s32 a0);
extern void func_8015E588(void);
extern void func_8015E4B0(s32 a0);
extern void func_8015E288(s32 a0);
extern void func_8015E5B0(u8*);
extern void func_8015E344(u16 *param_1);
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern s32 func_8013C9C4(s32 *a0);
extern void func_8015E5B0(u8 *self);
extern void func_8015E698(u16 *param_1);
extern void func_8015E714(s32 *a0);
extern void func_8015E95C(s32);
extern void func_8015E84C(s32 *a0);
extern void func_8015E8E8();
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void func_8015E924(s32 a0);
extern void func_8015E95C(s32 a0);
extern s16 D_801152A0;
extern void func_80160818(s32 *a0);
extern u16 func_801487F4(s32*);
extern void func_80147078(s32*, s16);
extern s32 func_80149D10(s32);
extern void func_80175150(s32*);
extern void func_8016EE40(s32, s32, s32);
extern s32 func_80149744(struct S_80149744*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32);
extern s32 func_80148E54(void *a0);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80154150(s32, s32);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern void func_801483E8(unsigned char*);
extern void func_8015EA3C(void *arg0);
extern void func_8015ED6C(s32 *a0);
extern void func_8015EE7C(s32);
extern void func_8015EDA0(s32 *a0);
extern s32 func_8015EE08();
extern void func_8015EDD4(s32 *arg0);
extern void func_8015EE44(s32 a0);
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C();
extern void func_8015EFD8(s32 *a0);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324();
extern void func_8015F2F0(s32 *a0);
extern void func_8015F360(void);
extern s32 func_801725B8(u8 *a0);
extern void func_8015F380(void* arg0);
extern s32 func_801496D4(void*);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147A84(s32 a0);
extern void func_80146E90(s32*, s32);
extern s32 func_801725B8(u8*);
extern void func_80019064(void*);
extern void func_801484B0(s32, s32);
extern void func_80148534(s32, s32);
extern void func_8015F448(s32 arg0);
extern void func_8015F738(s32 *a0);
extern void func_8015F848(s32 *a0);
extern void func_8015F76C(s32 *a0);
extern s32 func_8015F7D4();
extern void func_8015F7A0(s32 *arg0);
extern void func_8015F810(s32 *a0);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern void func_8015F89C(void *arg0);
extern void func_8015F948(s32 *param_1);
extern void func_8015F9A4(void *arg0);
extern void func_8015FA24(s32 arg0);
extern void func_8015FBE0(s32 *a0);
extern void func_8015FA44(s32 *a0);
extern void func_8015FAAC(s32 *a0);
extern void func_8015FA78(s32 *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_8015FAE8(void *arg0);
extern void func_8015FBE0(s32 *param_1);
extern void func_8015FCC8(void *param_1);
extern void func_8015FD74(int param_1);
extern u8 func_80165700(s32 a0, s32 a1);
extern void func_8015FDCC(s32 a0);
extern void func_8015FE70(u16 *param_1);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);
extern void func_8015FF20(void *param_1);
extern void func_801601AC(s32 *a0);
extern void func_801600D0(s32 *a0);
extern void func_80160138(s32 *a0);
extern void func_80160104(s32 *a0);
extern void func_80160174(s32 *a0);
extern void func_801601E4(s32 *a0);
extern void func_80160244(s32 *a0);
extern void func_801602A4(s32 *a0);
extern void func_8016032C(void);
extern void func_80160410(s32 *a0);
extern void func_80160334(s32 *a0);
extern void func_8016039C(s32 *a0);
extern void func_80160368(s32 *a0);
extern void func_801603D8(s32 *a0);
extern u8 D_80062BD0;
extern void func_80160410(s32 * a0);
extern void func_80160534(u8 *p);
extern void func_801607B8(s32 *a0);
extern void func_801608C0(s32 *a0);
extern void func_801607E4(s32 *a0);
extern void func_8016084C(s32 *a0);
extern void func_80160888(s32 *a0);
extern void func_80160A74(s32 *a0);
extern void func_80160920(unsigned short *param_1);
extern void func_801609B8(u16 *param_1);
extern void func_80160A28(s32 a0);
extern void func_80160BB4(s32 *a0);
extern void func_80160ACC(s32 *a0);
extern s32 func_80160B34(s32 a0);
extern void func_80160B00(s32 *arg0);
extern void func_80160B70(s32 a0);
extern void func_80160C28(void *arg0);
extern void func_80160CB4(s32 *a0);
extern void func_80160D10(void *arg0);
extern void func_80160DEC(u8 *a0);
extern void func_80160F00();
extern void func_80160E3C(s32 *a0);
extern void func_80160EA4();
extern void func_80160E70(s32 *a0);
extern void func_80160EA4(void *a0);
extern void func_80160EE0(void);
extern void func_80160F00(void* arg0);
extern u8 D_80110EC0;
extern void func_80160F70(s32 a0);
extern void func_80160FE0(s32 *a0);
extern void func_80161034(void *a0);
extern void func_80161094(s32 a0);
extern void func_801610FC(void);
extern void func_8016130C(void*, s32);
extern void aF80161208();
extern void func_8016130C(void *a0, s32 a1);
extern int func_80161374(int param_1, unsigned int param_2);
extern void func_80161278(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);
extern s32 aF8016130C();
extern void func_80015954(s32, s32);
extern s32 func_8016163C(s32 a0, u32 a1);
extern s32 func_80161774(int param_1, u32 param_2);
extern s32 func_8016197C(s32 a0, s32 a1);
extern s32 func_80161488(void *a0);
extern int func_80161888(int param_1, unsigned int param_2);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_80161774(int a0, u32 a1);
extern s32 func_80161888(s32 a0, u32 a1);
extern void func_8014C010(int a0, int a1);
extern int aF8016191C();
extern s32 func_801619A4(s32 *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern s32 func_80161A60(s32 a0);
s32 func_801497A8(s32 *a0);
void func_801599A4(void *a0);
void func_80149864(void);
extern s32 func_80161BE0(s32 *a0);
extern void func_80147324();
extern void func_80161C24(int param_1, int param_2);
extern void func_80161C98(int param_1, u32 param_2);
extern int func_800CF8B4();
extern void func_80147324(int arg0);
extern void aF80161CD0();
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void func_80162330(void *a0);
extern void func_8014706C(void *a0);
extern s32 func_8016236C(u8 *a0);
extern void func_800D0C48(s32 a0);
extern s32 func_801623B8(s32 *a0);
extern s32 func_800167F0(s32 a0);
extern s32 func_80162414(void);
extern s32 func_80162438(s32 _unused0);
extern int func_801626B8(void);
extern void func_80162714(void);
extern void func_80162760(void);
extern void func_801627C0(void);
extern void func_80162834(void *a0);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern void func_80162870(s32 param_1);
extern void func_801628F4(s32 *a0);
extern void func_80162968(s32 param_1);
extern void func_80162AC0(s32 *a0, s8 a1);
extern s32 func_80162AE0(u8 *a0);
extern void func_80162AF4(void);
extern void func_80162CC4(void);
extern s32 D_80126D40;
extern void func_80162D28(s32 *a0);
extern void func_80162D88(s32 *a0);
extern void func_80162DE8(s32 *a0);
extern void func_80162E48(s32 *a0);
extern void func_80162EA8(s32 *a0);
extern void func_80162F60(s32 arg0, s32 arg1);
extern void func_80162F80(s32 arg0, s32 arg1);
extern void func_80162FA0(s32 arg0, s32 arg1);
extern void func_80162F08(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80162FC0(s32 *a0);
extern s32 aD_80127090 __asm__("D_80127090");
extern s32 aD_80127094 __asm__("D_80127094");
extern s32 aD_80127098 __asm__("D_80127098");
extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801630C4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163234(s32 a0);
extern s32 D_80115100;
extern s32 func_801632E0(void);
extern s32 D_80115200;
extern s32 func_801632F0(void);
extern u16 D_80126B18[];
extern void func_80163328(void);
extern s32 func_801633A8(void);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);
extern void func_8016345C(s32 a0, u16 a1, s32 a2, u16 a3, s32 a4);
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80163664(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32);
extern void func_80163534();
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_80163764(s32 a0);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418();
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_801630C4(s32, s32, s32, s32);
extern void func_80164418(s32 s0);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void func_80164744(s32 param_1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern void func_80164BDC(s32 param_1);
extern s32 func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void func_80164EA4(void *a0);
extern void func_80165124(void *a0);
extern void func_80164EE0(int param_1);
extern s32 func_80165140(s32 a0);
extern void func_801651B8(void *a0);
extern void func_80164F44(void *arg0);
extern void func_80165024(void *a0);
extern void func_80165064(s32 *a0);
extern void func_801650C4(s32 *a0);
extern s32 func_80165140(s32 param_1);
extern void func_80165240(void *param_1, void *param_2, void *param_3);
extern void func_801651B8(void * param_1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80016ED4(void *a0);
extern u8 D_80126CF8;
extern void func_8016533C(void);
extern void func_801653F4(s32 a0);
extern void func_80165580(s32 a0);
extern void func_80165374(s32 a0);
extern void func_80165580(s32 _arg0);
extern void func_801653B8(s32 *a0);
extern s32 func_80165624(s32 a0);
extern u8 D_80078EC5;
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 func_801656D0(s32 a0, s32 a1);
extern void func_800CAF6C(s32 *a0);
extern void func_80165770(void);
extern void func_801657D8(void);
extern u8 D_80078EC3;
extern void func_801657A0(void);
extern s32 D_80078EA0;
extern s32 D_80078EA8;
extern u8 D_80078EBB;
extern s32 D_80078ED4;
extern s32 D_80078ED8;
extern s32 D_80078EDC;
extern u8 D_80078EE0;
extern void func_80165874(void);
extern s8 D_80078EC4;
extern void func_801658EC(void);
extern s32 func_80165900(void);
extern s32 func_80165910(void);
extern s32 D_8012672C;
extern s32 D_8012811C;
extern s32 D_80126B08;
extern void func_80165938(void);
extern void func_80165958(void);
extern s32 func_80165978(void);
extern void func_80165988(void);
extern s32 func_801659A8(void);
extern void func_801659B8(void);
extern s32 func_801659CC(void);
extern void func_80165A18(void);
extern u8 D_80078EC2;
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0();
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void func_801663FC(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void func_80166618(void *a0);
extern void func_80166654(void *a0);
extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern void func_80146C3C(u8*);
extern void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void func_8016706C(s32 param_1);
extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80167540(s32 arg0);
extern void func_80167714(s32 param_1);
extern void func_801678B4(void *a0);
extern void func_801678F0(s32 a0);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801681FC(s32 param_1);
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80166690();
extern void func_80168328(s32 arg0);
extern void func_801683D8(s32 a0);
extern void func_80168430(s32 param_1);
extern void func_80168540(s32 a0);
extern void func_801685EC(s32 a0);
extern void func_80168640(s32 a0);
extern void RotMatrixX(int, void*);
extern void func_80168664(s32 a0);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_80168B70(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern s32 func_80016A5C();
extern void func_80168F40(void *a0);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern void func_801696D8(s32 a0, s32 a1);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void func_80169B80(void *a0);
extern s32 func_800D222C(void *a0, void *a1, s32 a2);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80169BBC(s32 arg0);
extern void func_80169E44(s32 a0);
extern void func_80169F00(void *a0);
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290();
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void func_8016AB30(void *a0);
extern void func_8016B234();
extern void func_8016AFB0(s32 a0);
extern void func_8016B114(void *arg0);
extern void func_8016B234(s32 param_1);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern void func_8016B5C0(s32 param_1);
extern void func_80013CFC(s32 a0, s32 a1, void *a2);
extern void func_8001739C(void *a0);
extern void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void func_8001CD9C(int, void *);
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 func_8016BA68(s32, s32);
extern s32 func_8016BA68(s32 arg0, s32 arg1);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern s32 func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern s32 func_8016BF50(s32 param);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void func_8016C14C(void *a0);
extern void func_8016C188(s32 param);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04();
extern void func_8016C83C(s32 a0);
extern short func_8016CBC0(void);
extern void func_8016C998(s32 param_1);
extern void func_8016CB84(void *a0);
extern void func_8016D5EC(s32 *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void func_8016D19C(void *a0);
extern void func_8016D428(void *a0);
extern void func_8016D464(u8 *a0);
extern void func_8016D4DC(s32 a0);
extern void func_8016D64C(int param_1);
extern void func_8016D778(s32 a0);
extern void func_8016DBD8(u8 *a0);
extern void func_8016DA30(int param_1);
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern s32 func_8016DC20(s32 param_1);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void func_8016DF20(void *a0);
extern void func_8016DF5C(s32 param_1);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void func_8016E5B8(void *a0);
extern void func_8016E5F4(s32 arg0);
extern void func_8016E778();
extern void func_8016E688(void *a0);
extern void func_8016E6E4(s32 a0);
extern void func_8016E7C8(int param_1, short *p1, unsigned int *p2);
extern void func_8016E778(int param_1);
extern void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3);
extern s32 D_80115218;
extern void func_8016E918(short param_1, short param_2);
extern s32 func_800D2CA8(s32 a0, s32 a1);
extern void func_800D2D10(s32 a0, s32 a1, void *a2, s32 a3);
extern s32 func_80024054(u8*, u8*);
extern void func_8016EC0C(s32 a0, s32 a1);
extern void func_8016E9EC(u8 *p);
extern void func_8016EAC0(Wave *param_1);
extern void func_8016EB3C(s32 p);
extern void func_8016EBA8(u8 *param_1);
extern void func_80017B98(void *a0);
extern void func_8016ED6C(void);
extern s32 D_80126D70;
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8016ED8C(s32 a0, s32 a1, s32 a2);
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern void func_8016EDBC(s32 a0, s32 a1, s32 a2);
extern void func_8016EE94();
extern void func_8016EDEC(s32 _arg0, s32 _arg1, s32 _arg2);
extern void func_8016EF78(s32 a0);
extern void func_8016EE40(s32 _arg0, s32 _arg1, s32 _arg2);
extern void func_801726D0(void *a0);
extern s32 D_80126D50;
extern s32 D_80126D54;
extern u8 D_80126D6C;
extern u8 D_80126D6D;
extern u8 D_80126D6E;
extern s32 D_80126D5C;
extern s32 D_80126D60;
extern s16 D_80126D64;
extern s16 D_80126D66;
extern s16 D_80126D68;
extern s16 D_80126D6A;
extern u8 D_80126D1A;
extern s32 D_80127058;
extern s32 D_8012705C;
extern s32 D_80127060;
extern s32 D_80127064;
extern s32 D_80127068;
extern s32 D_8012706C;
extern s32 D_80127070;
extern s32 D_80127074;
extern s16 D_80126D20;
extern void func_8016EE94(s32 a0, s32 a1);
extern s32 func_8016EFC8();
extern s32 func_8016EFA8(s32 a0);
extern s32 func_8016EFC8(s32 a0, s32 a1);
extern void func_8016F094(s32 *a0);
extern void func_8017196C(s32 *a0, s8 a1);   /* == DEFINE_func_8017196C's own signature */
extern void func_80147060(u8 *a0);
extern void aF8016F0E4();
extern void func_8016F250(void);
extern void func_8016F288(void);
extern void func_8016F2A8(void);
extern void func_8016F2C8(void);
extern void func_8016F2EC(void);
extern void func_8016F30C(void);
extern void func_8016F330(void);
extern void func_8016F350(void);
extern void func_8016F374(void);
extern void func_8016F388(void);
extern void func_8016F398(void);
extern s32 func_8016F44C(s32 a0);
extern void func_8016F470(s32 a0);
extern s32 func_8016F410(s32 a0);
extern void func_80175414(s32 _arg0);
extern s32 func_8016F4C4(s32);
extern s32 func_8016F494(s32 a0);
extern s32 func_8016F4C4(s32 param_1);
extern void func_8016F4F4(void);
extern void func_801719A4(int a0, int a1);
extern void func_800D1724(s32 a0);
extern void func_80171928(void *a0);
extern void *D_8011F738;
extern void func_8016F4FC(void *a0);
extern void func_8014708C(void *a0);
extern void func_8016F540(void *a0);
extern void func_8016F578(s32 *a0);
extern void func_8016F5B0(void *a0);
extern void func_8016F5E0(u8 *a0);
extern void func_8016F610(void *a0);
extern void func_8016F648(void *a0);
extern void func_8016F680(void *a0);
extern void func_8016F6B0(void *a0);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void func_80170810(void *a0);
extern void func_801708B0(void *a0);
extern u8 D_800D5DA8;
extern void func_8017084C(s32 a0);
extern s32 func_8014C168(s32*, s32);
extern void func_801708B0(void* a0);
extern u8 D_800D5A34[];
extern void func_80170AD8(void *a0);
extern void func_80171904(s32 a0);
extern void func_80170B48(int a0);
extern void func_80170928(void);
extern u8 D_800D59EC[];
extern void func_80170970(void);
extern u8 D_800D599C[];
extern void func_801709B8(void);
extern u8 D_800D5934[];
extern void func_80170A00(void);
extern void func_80170A48(void);
extern u8 D_800D5DC0[];
extern void func_80170A90(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void func_801718AC(void *a0);
extern void func_80170CF0(void* a0);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_80170DE0(u8 * _arg0);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern void func_80170EAC(u8 * _arg0);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_8017118C(u8 * a0);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void func_80171260(void *a0);
extern struct B16 D_800A5E88;
extern struct B16 D_800A5E98;
extern struct B16 D_800A5EA8;
extern void func_801719A4(int, int);
extern s32 func_80171990(u8*);
extern void func_80171384(void*);
extern void func_8017129C(int param_1);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void func_801714E4(void *a0);
extern void func_8017162C(void *a0);
extern void func_80171520(s32 a0);
extern s32 func_801716AC(s32 a0, void *a1, s32 *a2);
extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern s32 func_801716AC(s32 a0, void * a1, s32 * a2);
extern int func_800D0FE0(int a0);
extern void func_801717A0(void *a0);
extern void func_8013E588(void *a0);
extern void func_801717F4(void *a0);
extern void func_80171824(void *a0);
extern void func_80171854(void *a0);
extern void func_80171884(void);
extern void func_80171A1C(u8 *a0);
extern void func_801718AC(void *arg0);
extern void func_80171928(void * a0);
extern void func_8017196C(s32 *a0, s8 a1);
extern void func_80171A04(s32 *a0);
extern void func_80171A10(s32 *a0);
extern void func_80171A34(s32 *a0, s8 a1);
extern s32 func_80171A44(u8 *a0);
extern s32 func_80171A58(u8 *a0);
extern s32 func_80171A6C(u8 *a0);
extern void func_80171A80(s32 *a0, s32 a1);
extern s32 func_80171A88(s32 a0);
extern s16 func_80171AB0(s32 param_1, void * _arg1);
extern void func_80171B10(void *a0);
extern void func_80171EC8(s32 a0);
extern s32 func_80171C64(s32 param_1, s32 param_2);
extern s32 func_80171D78(s32 a0, s32 a1);
extern int func_8017250C(short *a0, short *a1);
extern s32 func_80171CC4(void * a0, void * a1);
extern s32 func_80171FFC(short *a0, short *a1, s32 a2);
extern s32 func_80171D1C(void * a0, void * a1, s32 a2);
extern s32 func_8017248C(s32 a0, s32 a1);
extern s32 func_80171E08(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8017248C(s32, s32);
extern s32 ratan2(s32, s32);
extern void func_80172170(s32, s32);
extern void func_80146D90(s32);
extern void func_80172170(s32 a0, s32 a1);
extern s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_801722CC(s32 *a0);
extern void func_80172304(s32 *a0);
extern void func_80172310(u8 *a0);
extern void func_801723C4(s32 param_1, s32 param_2);
extern void func_80172414(s32 a0);
extern s32 func_801724EC(s32 a0);
extern s32 func_8017248C(s32 arg0, s32 arg1);
extern s32 func_80013450(s32);
extern s32 func_80172560(u8 *a0, u8 *a1);
extern s32 func_8017261C(u8 *a0);
extern s32 func_80172644(u8 *a0);
extern s32 func_80172670(s32 *a0);
extern s32 func_80172688(s32 *a0);
extern s32 func_80172694(s32 *a0);
extern s32 func_801726A0(s32 *a0);
extern s32 func_801726AC(s32 *a0);
extern s32 func_801726B8(s32 *a0);
extern s32 func_801726C4(s32 *a0);
extern s32 func_80172760(s32 a0);
extern s32 func_80174650(s32);
extern void (*D_80127088)(void);
extern s32 D_801270BC;
extern s16 D_80126B0C;
extern void func_801726D0(void * _arg0);
extern void func_80172710(void);
extern void func_80174684(void *);
extern void func_80172738(void);
extern s16 D_80126B30;
extern s32 func_801727D0();
extern void func_80172780(void *a0);
extern void func_80172844(u8 *a0);
extern void func_8017280C(u8 *a0);
extern void func_8017288C(void);
extern s32 func_801728E4();
extern void func_80172894(void *a0);
extern void func_80172958(u8 *a0);
extern void func_80172920(u8 *a0);
extern s16 D_80126B36;
extern void func_80172958(u8 * a0);
extern void func_801729A8(void);
extern s32 func_801729F0();
extern s16 D_80126B34;
extern s16 D_80126B32;
extern void func_801729B0(s32 a0);
extern void func_80172A8C(void *a0);
extern void func_80172A2C(int param_1);
extern void func_80172ACC(u8 *a0);
extern void func_80172B0C(void);
extern s32 func_80172B44();
extern void func_80172B14(s16 a0);
extern s32 D_801150F8;
extern void func_80172BC8(void *a0);
extern void func_80172B80(u8 *a0);
extern void func_80172C48(void);
extern void func_80172CA0(void*);
extern void func_80172C50(void *a0);
extern void func_80172CA0(void *a0);
extern void func_80172D14(u8 *a0);
extern void func_80172CDC(u8 *a0);
extern void func_80172D14(u8 * a0);
extern void func_80172D60(void);
extern s32 D_80127508;
extern s32 func_80172DAC();
extern void func_80172D68(s32 a0);
extern void func_80172E20(u8 *a0);
extern void func_80172DE8(u8 *a0);
extern void func_80172E20(u8 * a0);
extern void func_80172E8C(void);
extern void func_8017303C(void *);
extern void func_80172E94(void);
extern void func_80172ED4(void);
extern void func_80172EFC(void);
extern void func_80172F24(void);
extern u8 D_800D47F4[];
extern void func_80172F4C(void);
extern void func_80172F9C(void);
extern u8 D_800D5C6C[];
extern void func_80172FEC(void);
extern s32 func_80173078();
extern void func_8017303C(void * a0);
extern void func_801730FC(struct S801730FC *a0);
extern void func_801730B4(s32 a0);
extern void func_8017316C(void);
extern s32 func_8017319C();
extern void func_80173174(void);
extern u8 D_800D5AA0[];
extern void func_80173220(void *a0);
extern void func_801731D8(s32 *a0);
extern void func_80173220(void * arg0);
extern void func_80173294(void);
extern void func_801732C4();
extern void func_8017329C(void);
extern void func_801732C4(s32 *a0);
extern void func_8017331C();
extern void func_801732F4(void);
extern void func_8017331C(s32 *a0);
extern void func_80173374();
extern void func_8017334C(void);
extern void func_80173374(s32 *a0);
extern void func_801733A4(void);
extern void func_801733CC(s32 a0);
extern void func_801734BC(s32 a0, s32 a1);
extern void func_801733FC(s32 a0, s32 a1);
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
extern void func_80173544(void *a0);
extern void func_801735B8(u8 *a0);
extern void func_80173580(u8 *a0);
extern s16 D_80126B40;
extern void func_801735EC(void *a0);
extern void func_80173648(u8 *a0);
extern void func_801736A8(void);
extern s32 func_8014C118(void *a0, s32 a1, s32 a2);
extern s32 func_801736FC();
extern void func_801736B0(s32 a0, s32 a1);
extern void func_80173770(u8 *a0);
extern void func_80173738(u8 *a0);
extern void func_801723C4(s32 a0, s32 a1);
extern void func_801737B0(void);
extern s32 func_801737E8();
extern void func_801737B8(s16 a0);
extern void func_8017385C(u8 *a0);
extern void func_80173824(u8 *a0);
extern void func_801738D4(void);
extern s32 func_8017390C();
extern void func_801738DC(s16 a0);
extern void func_80173980(u8 *a0);
extern void func_80173948(u8 *a0);
extern void func_801739D8(u8 *a0);
extern void func_80173A20(void);
extern s32 D_8012750C;
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_8014C118(void*, s32, s32);
extern void func_80173B4C(void*);
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern void func_80173B4C(void *a0);
extern void func_80173BC0(u8 *a0);
extern void func_80173B88(u8 *a0);
extern s16 D_80126B3A;
extern s16 D_8011F9C8;
extern void func_8013E588(void*);
extern void func_80173BC0(u8* a0);
extern void func_80173C64(u8 *a0);
extern u8 D_800D5DB8;
extern void func_80173CB4(s32 a0);
extern void func_80173E1C(s32 a0);
extern s16 D_80126938;
extern void func_800D128C(s32, s32);
extern void func_80174158(s32 a0);
extern void func_8002A088(s32);
extern void func_8002A2D4(s32);
extern void func_8002A544(s32);
extern void func_8002A7B4(s32);
extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);
extern void func_800D0F0C(s32, s32);
extern void func_80145EE8(s32);
extern void func_80173EF8(void *param_1);
extern s32 func_8014BCEC(s32, s32);
extern void func_801741A8(s32 _arg0);
extern s16 D_80126B3C;
extern void func_801741EC(u8 *a0);
extern void func_80174274(void);
extern s32 func_801742A4();
extern void func_8017427C(void);
extern void func_80174318(u8 *a0);
extern void func_801742E0(u8 *a0);
extern void func_80174354(void);
extern s32 func_80174384(void *a0);
extern void func_8017435C(void);
extern void func_801743F0(u8 *a0);
extern void func_801743C0(u8 *a0);
extern void func_801743F0(u8 * a0);
extern void func_80174430(void);
extern s32 func_80174474(void *a0);
extern void func_80174438(s32 a0);
extern void func_801744E0(u8 *a0);
extern void func_801744B0(u8 *a0);
extern void func_80174524(void);
extern void func_80174554();
extern void func_8017452C(void);
extern void func_80174554(s32 arg0);
extern void func_801745AC();
extern void func_80174584(void);
extern void func_801745AC(s32 *a0);
extern void func_80174604(void);
extern void func_801745DC(void);
extern void func_80174630(void);
extern s32 func_80174650(s32 _arg0);
extern void func_80174674(void);
extern void func_80174684(void* a0);
extern void func_801746A4(void);
extern s32 func_800CF8CC(void);
extern s32 func_8016F0AC();
extern void func_80174714(void);
extern s32 func_80174754(void);
extern s16 func_80174764(void);
extern s16 func_80174774(void);
extern s32 func_801747CC(void *a0);
extern void func_80174784(void);
extern s32 func_801747AC(s32 a0);
extern s32 func_80174808(u8 *a0);
extern void func_8017481C(void);
extern s32 func_80174888(void *a0);
extern void func_80174824(void);
extern void func_8017484C(s32 a0);
extern void func_801748C4(s32 a0);
extern void func_801748E4(void);
extern s32 func_8017496C(void *a0);
extern s32 D_80126954;
extern s32 D_80126950;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern s32 func_80012ABC(s32, s32, s32);
extern s32 func_801749C8(s32 param_1);
extern void func_80174BBC(void *a0);
extern void func_80174BF4(void *a0);
extern void func_80174BF4(void * arg0);
extern s32 func_80174CB0();
extern s32 func_80174C60(s32 a0);
extern void func_80174C80(s32 a0);
extern s32 func_80174CB0(s32 param_1, s32 param_2);
extern s32 D_8012697C;
extern u16 D_80126980;
extern s32 func_80174F28(void *a0);
extern void func_80174E9C(s32 a0);
extern void func_80174EF0(s32 a0, s16 a1);
extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2);
extern void func_80174F64(u8 *a0);
extern void func_80174FBC(u8 *a0);
extern s32 func_8017509C(u8 *a0, s32 a1, u8 *a2, u8 *a3);
extern void func_80175184(s32 *a0);
extern void func_80175114(s32 *a0);
extern void func_80175184();
extern void func_80175150(s32 *a0);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern s32 func_80175218(void * param_1);
extern s32 func_80175268(s32 param_1);
extern void func_801752BC(s32 *a0);
extern u8  D_8011F7A8;
extern u8  D_8011F7A9;
extern u8  D_8011F7AE;
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s16 D_8011F7B8;
extern s16 D_8011F7BA;
extern s16 D_8011F7BC;
extern s16 D_8011F7BE;
extern void func_80016714(void *, s32);
extern void func_801757A0(s32);
extern void func_800596F4(s32);
extern void func_80175308(void);
extern u8 D_8011F7AD;
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);
extern void func_8017553C(s32 *param);
extern void func_801757A0(s32 a0);
extern void func_80175590(void *arg0);
extern void func_80175624(void *a0);
extern void func_801757E0(int);
extern void func_80175668(void);
extern void func_80175690(s32 *param);
extern void func_80175DA8(s32 a0);
extern void func_80175AB8(s32 a0);
extern void func_80176144(s32 a0);
extern void func_801756E4(s32 arg0);
extern void func_80175798(void);
extern void func_80176734(s32 a0);
extern void func_80176218(s32 a0);
extern void func_80176D00(s32 a0);
extern void func_801757E0(s32 a0);
extern void func_80175AB8();
extern u32 *func_8017742C(u32 *a0, s32 a1, s32 a2);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80175DA8();
extern void  func_80176FF4(s32);
extern void  func_80177340(s32);
extern u32   func_801783D0(s32, s32);
extern void  func_80177F84(s32, s32);
extern void func_80177DA8(u8 * p, u32 v, s32 idx);
extern void func_80177AD4(int, unsigned int);
extern s32   func_80024054(u8 *, u8 *);
extern u32 *func_80178298(u32*, u8*, short, short);
extern void func_80176218(s32 param_1);
extern void func_80176734(s32 param_1);
extern s32 func_80178004();
extern u8 D_8011F7B1;
extern s16 D_8011F81E;
extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801783D0(s32 a0, s32 a1);
extern void *func_801777BC();
extern u16 D_8011F82C;
extern u16 D_8011F82A;
extern u32 * func_80176D94(void *param_1, u32 param_2, s16 param_3_);
extern void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4);
extern void func_80176FF4(s32 a0);
extern u16 D_8011F830;
extern u16 D_8011F82E;
extern u32 * func_801770E0(void *param_1, u32 param_2, s16 param_3_);
extern void func_80177340(s32 a0);
extern u8 D_8011F837;
extern u8 D_8011F7F0;
extern u8 D_8011F7AB;
extern u32 * func_8017742C(u32 *param_1, s32 param_2, s32 param_3);
extern u8 D_8011F83B;
extern void func_801776EC(u8 *a0);
extern void func_801775E0(s32 param_1, s32 param_2);
extern void * func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern void * func_801777BC(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_);
extern void func_80177AD4(int param_1, unsigned int param_2);
extern u32 * func_80177B5C();
extern void func_80177DA8();
extern uint * func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4);
extern void func_80177F84(s32 param_1, s32 param_2);
extern s32 func_80178004(uint *param_1, uint param_2, int param_3);
extern u32 * func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
extern void func_80178438(u16 *arg0);
extern void func_801787D4(void);
extern void func_8017869C(s32 a0);
extern void func_80130D0C(s32 a0);
extern s32 D_8011DB08;
extern s16 D_801270C4;
extern s16 D_801270C2;
extern u8 D_801270C6;
extern u8 D_801270C7;
extern void func_80178744(s32 a0, s32 a1);
extern void func_80178840();
extern void func_80178840(int param_1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_801789AC(s32 arg0);
extern int func_80178970(void);
/* ==== end §8b carried decl layer ==== */



extern void func_8017BC38(int a0);
extern void func_8017A4AC(void);
extern void func_8017AE2C(s32 a0);
extern s32 func_801399F0(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);

extern short D_8019BD3C;
extern s32 D_8019B9A8;
extern s32 D_8019BBE4;
extern s32 D_8019B594;
extern s32 D_8019B9D4;
extern s32 D_8019B590;

s32 func_801789AC(s32 arg0)
{
    s32 ret;

    func_8017BC38(arg0);
    func_8017A4AC();
    func_8017AE2C(arg0);

    switch ((s16)(D_8019BD3C - 1)) {
    case 0:
        ret = func_801399F0(D_8019B9A8);
        D_8019BBE4 = ret;
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8019B590);
        break;
    case 1:
        ret = func_801399F0(D_8019B9A8);
        D_8019BBE4 = ret;
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8019B590);
        break;
    case 2:
        func_80178CBC(arg0, D_8019B590);
        break;
    case 3:
        if (--D_8019B594 > 0) {
            break;
        }
        func_80178CBC(arg0, D_8019B590);
        break;
    case 4:
        ret = ((s32 (*)(s32))D_8019B9D4)(arg0);
        if (ret == 0) {
            break;
        }
        func_80178CBC(arg0, D_8019B590);
        break;
    case 5:
        switch (D_8019BBE4) {
        case -1:
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        }
        break;
    }
    return 0;
}

extern void func_8017435C(void);
extern void func_801746A4(void);


// @class: struct
// @unstuck(P36): none — MATCH (pointer var forces &(*(int *)&D_80185DE4) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_80185DE4;

    int *p = &(*(int *)&D_80185DE4);
    *p = ((int)param_2);
    func_80178BF8();
    func_801746A4();
    func_8017435C();
    ((void (*)(int, void *))func_80178CBC)(((int)param_1), (char *)p - 0xC);
}




// @class: regalloc-order
// @unstuck(P36): none — MATCH (pending verify)

s32 func_80178B70(s32 param_1, s32 param_2)
{
    extern void func_80178BF8();
    extern void func_80178CBC();
    extern int D_80185DE4;

    int *p = &D_80185DE4;
    *p = ((int)param_2);
    func_80178BF8();
    func_80178CBC(((int)param_1), p - 3);
}


#include "../shared/ov/func_80178BB8.h"


extern void func_80016714(void *a0, s32 a1);

// @class: other
// @unstuck(P36): none — MATCH (49 ins). Key: init loop pointers via &D_SYMBOL (not (T*)0x801da788 raw int, which emits lui+ori instead of lui%hi+addiu%lo).



void func_80178BF8(s32 _unused0, s32 _unused1)
{
    extern void func_8017B1D8(void);
    extern short D_8019BD3C;
    extern int D_8019B9A8;
    extern short D_8019B9B8;
    extern short D_8019B9B4;
    extern short D_8019B9B0;
    extern short D_8019B9AC;
    extern int D_8019BBE4;
    extern int D_8019B9C0;
    extern s16 D_8019B9A0;
    extern short D_8019B998;
    extern short D_8019B99C;
    extern int D_8019BC98;
    extern unsigned int D_8019BA10;
    extern unsigned short D_8019B996;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_8019BA10;
    D_8019BD3C = 0;
    D_8019B9A8 = 0;
    D_8019B9B8 = 0;
    D_8019B9B4 = 0;
    D_8019B9B0 = 0;
    D_8019B9AC = 0;
    D_8019BBE4 = 1;
    D_8019B9C0 = 0;
    (*(short *)&D_8019B9A0) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_8019B996;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_8019B998 = 0;
    D_8019B99C = 0;
    ((void (*)(int *, int))func_80016714)(&D_8019BC98, 0x14);
    func_8017B1D8();
}


extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);

void func_80178CBC(s32 arg0, s32 arg1) {

    extern s32 D_8019B590;
    extern short D_8019BD3C;
    D_8019B590 = arg1;
    do {
        func_80178D40(arg0, D_8019B590);
    } while (D_8019BD3C == 3);
}



extern void func_80174714(void);

void func_80178D18(void) {

    extern short D_8019BD3C;
    D_8019BD3C = 0;
    func_80174714();
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_80175414(s32 _arg0);
extern void func_80175454(void);

/* func_80178D40 - 890 ins, 94-case jr switch (jtbl_801D8E24).
 * STATUS: **MATCH** -- 890/890 ins, byte-exact (masked). PIN-FREE (this body is
 * templated across 134 overlays; a pinned body would crash the sibling TUs).
 *   python3 tools/match_one.py func_80178D40 --c .run/phase26-cracks/func_80178D40.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC
 *   => MATCH (890 ins)
 * Jump table VERIFIED: 94 entries (= the sltiu 0x5E bound, no trailing zero pad),
 * 93 unique blocks, cases 0xF/0x3F share one block; my case->block sequence is
 * identical to jtbl_801D8E24's.
 *
 * Byte-derived structure (the levers that cracked it):
 *  1. NO status variable. Every case stores `(*(s16*)&D_8019BD3C) = K` DIRECTLY. The shared
 *     `sh $v0, (*(s16*)&D_8019BD3C)` at .L80179AEC is a jump2 CROSS-JUMP merge of those stores:
 *     find_cross_jump's FIRST call (minimum=1, vs the code before the target label)
 *     matches that 1 insn, and because it succeeds the jump_chain loop (minimum=2) is
 *     SKIPPED -- which is what BLOCKS the deeper, wrong 3-insn merges of the identical
 *     func_80137614 tails (cases 0/0x45/0x32). reorg then steals the `li K` back into
 *     each `j` delay slot, so it looks un-merged. A `status` pseudo instead of direct
 *     stores loses that block and costs 6 insns.
 *  2. after-switch = `D_8019B590 += 8;` (.L80179AF4) -> the out-of-range default lands
 *     there with NO explicit `default:` label.
 *  3. arg0/arg1/pv are STRUCT pointers. gcc-2.7.2 sched alias (sched.c true_dependence)
 *     only lets a MEM_IN_STRUCT varying-address load hoist above a non-MEM_IN_STRUCT
 *     fixed-address store (the (*(s16*)&D_8019BD3C) store). Raw `*(T *)(int + off)` casts get
 *     MEM_IN_STRUCT_P = 0 and block that hoist -> stray nops.
 *  4. g = &D_8019BC98 stays a plain `s16 *` (NOT a struct ptr) so its varying,
 *     non-in-struct stores keep their order w.r.t. the loads.
 *  5. Statement order inside the D_8019BC98 cases is load-bearing (sched LUID/priority):
 *     g[0],g[2],g[1] in 0x25/0x48/0x26; g[7],g[8],g[1],g[3] in 0x4F/0x28.
 *  6. Cases 0x5B/0x5C: the loops "found" bodies are emitted BEFORE the case label ->
 *     source-level labels placed between cases + `goto`.
 *  7. Per-case temporaries are BLOCK-LOCAL (local-alloc), not function-scope.
 *  8. stack locals declared in slot order (0x10,0x18,0x20,0x28,0x30,0x38,0x40,0x48,
 *     0x50,0x58,0x60) -> frame 0x78.
 *
 * Case 0x5C -- the last 39 residuals. Four levers, all generalizable:
 *
 *  9. NO-PEEL: a `break` out of a do-while whose target COINCIDES with the loop's own
 *     natural fall-through exit makes NOTE_INSN_LOOP_BEG be followed by an
 *     unconditional jump -> jump.c `duplicate_loop_exit_test` (jump.c:599/2131) rotates
 *     the loop and peels iteration 1 (here `i` was provably 0, so the peeled `i++`
 *     const-folded to `li $a2,1` and dragged an extra lui/addiu/lw address block with
 *     it). Writing `goto L5D;` instead of `break;` -- SAME destination, different
 *     construct -- keeps the loop a plain do-while and the peel disappears.
 *     RULE: never let a loop's `break` land on the loop's own fall-through label.
 *
 * 10. SURVIVING REG-REG COPY (residual #1, `addu $v1,$v0,$zero`). A source-level
 *     `fp = q;` copy ALWAYS dies: cse.c `canon_reg` rewrites every later use of `fp`
 *     to `q` (qty_first_reg keeps the older reg) and flow deletes the now-dead set.
 *     To make a copy SURVIVE, its def and its uses must sit in different extended basic
 *     blocks -- cse resets its hash table at a label with >1 predecessor (a loop top).
 *     So: TEST THE MEM DIRECTLY, then assign the variable inside the branch body:
 *         if (arg1->a.w != 0) { fp5c = arg1->a.w; ... do { ... fp5c ... } while (); }
 *     cse folds the redundant 2nd load into `fp5c = <load temp>` (a copy) in the guard
 *     block, but CANNOT propagate it into the loop body -> the copy is emitted.
 *     (Assigning `fp5c` BEFORE the test gives one pseudo and no copy -- what we had.)
 *
 * 11. CROSS-JUMP-MERGED `(*(s16*)&D_8019BD3C) = 3` (residual #2). `if (i != 10) { (*(s16*)&D_8019BD3C) = 3;
 *     break; }` lets jump2 tail-merge the `lui/sh` into the shared .L80179AEC tail and
 *     reorg steal the `li 3` into the `bne` delay slot. Storing it unconditionally
 *     BEFORE the `if` blocks the merge and costs 3 inline insns.
 *
 * 12. THE UN-COALESCED LOOP COPY (residual #3, `addu $v1,$a0,$zero` + `addiu $a0,$v1,4`).
 *     This is loop.c's NON-REPLACEABLE DEST_REG GIV, not a source-level copy (see #10:
 *     those always die). Recipe -- BOTH halves are needed:
 *       a) make the pointer an INDEX GIV: `p5c = &D_8019B9EC[i5c];`  (a DEST_REG giv)
 *       b) make it NON-replaceable so loop.c emits `emit_insn_after(move dest,new_reg)`
 *          (loop.c:3945): record_giv (loop.c:4437) needs the giv used OUTSIDE the loop
 *          -- so the "found" body goes AFTER the loop and stores through `p5c`.
 *       c) put the BIV increment (`i5c++`) LAST in the body. loop.c inserts the reduced
 *          giv's `addiu` immediately BEFORE the biv's increment insn, so `i5c++` at the
 *          bottom puts `addiu $a0,$v1,4` in the loop-back delay slot. With `i5c++` at
 *          the TOP the giv-add lands at the top, nothing is left to fill the delay slot,
 *          and reorg STEALS the loop-top `move` into it (duplicating it: +1 insn).
 *
 * 13. Loop3 needs its OWN pointer pseudo (`r5c`, not `q5c`). `q5c` is loop1's pointer,
 *     and in loop1 $v1 is held by `fp5c` -> q5c is forced to $a0, and loop3 inherits it.
 *     Both "found" bodies then read $a0, become identical, and jump2 CROSS-JUMPS them
 *     into one block (-2 insns). A distinct pseudo frees loop3 into $v1, so found3
 *     (`sw $zero,0($v1)`) differs from found2 (`sw $zero,0($a0)`) and they stay separate.
 *     RULE: two structurally identical loops must differ in REGISTER, or cross_jump
 *     merges their tails.
 */






M2C_UNK func_80178D40(s32 arg0, s32 arg1)
{

    extern s32 D_80126B58;
    extern s32 D_8019B590;
    extern short D_8019BD3C;
    extern void func_80179B28(s32);
    extern void func_80137614(s32, s32, s32);
    extern void func_8012F214(s32, s32, s32);
    extern s32 *func_8012F40C(s32*, s32);
    extern void func_80179D30(u16*);
    extern void func_80179D78(u16*);
    extern void func_80179EA0(u16*);
    extern void func_80179DCC(short);
    extern void func_80179DF8(void);
    extern void func_80179E1C(short);
    extern void func_80179E48(s16);
    extern void func_80179E74(s16);
    extern void func_80179EE8(short);
    extern void func_80179F14(s16, s16);
    extern void func_80179F44(void);
    extern void func_80179F6C(short);
    extern void func_80179F98(u16*);
    extern void func_80179FEC(u16*);
    extern void func_8017A040(u16*);
    extern void func_8017A094(s32);
    extern void func_8017A0C4(s32);
    extern void func_8017A0F4(void);
    extern void func_8017A11C(void);
    extern void func_8017A144(s32);
    extern void func_8017A180(void);
    extern void func_8017A1A8(void);
    extern void func_8017A1D0(void);
    extern void func_8017A1F8(void);
    extern void func_8017A220(void);
    extern void func_8017A248(void);
    extern void func_8017A270(void);
    extern void func_8017A298(void);
    extern void func_8017A2C0(void);
    extern void func_8017A2E8(void);
    extern void func_8017A310(void);
    extern void func_8017A338(void);
    extern void func_8017A360(void);
    extern void func_8017A388(void);
    extern s32 func_8017A3B0(void);
    extern int func_8017A3D8(void);
    extern s32 func_8017AD0C(s32);
    extern s32 func_8017B238(s32, s32);
    extern s32 func_8017B614(s32, s32);
    extern void func_8017B7A8(void *);
    extern void func_8017B824(void);
    extern void func_8017B880(void);
    extern void func_8017B940(void *);
    extern void func_8017BA3C(s32, s32);
    extern s32 func_8017BB34(s32, s32);
    extern void func_8012A828(s32, void*);
    extern s32 func_8012B8A4(s16*);
    extern void func_8012E88C(u8*);
    extern void func_8012E8A8(u8*);
    extern void func_8001AAD0(s32, s32);
    extern s32 D_8019B594;
    extern s32 D_8019B9A8;
    extern s16 D_8019B9AC;
    extern s16 D_8019B9B0;
    extern s16 D_8019B9B4;
    extern s16 D_8019B9B8;
    extern s32 D_8019B9C0;
    extern s32 D_8019B9C4;
    extern s32 D_8019B9D4;
    extern s16 D_8019B9D8;
    extern s16 D_8019B9DC;
    extern s32 D_8019B9E0;
    extern s32 D_8019B9E8;
    extern s32 D_8019B9EC[10];
    extern s32 D_8019BBE0;
    extern s16 D_8019BC98;
    extern s32 D_8019BCC4;


    SV3_80178D40 v10, v18, v20, v28, v30, v38, v40, v48;
    s32 out50[2];
    SV3_80178D40 v58, v60;
    Actor_80178D40 *pv = &(*(Actor_80178D40*)&D_80126B58);
    s32 i5b, i5c, fp5b, fp5c;
    s32 *q5b, *q5c, *p5c, *r5c;
    s16 *g = &D_8019BC98;

    switch (((Cmd_80178D40 *)arg1)->op) {
    case 1:
        func_80179B28(D_8019B9A8);
        D_8019B9A8 = ((s32 (*)(s32, s32, s32))func_80137614)(((Cmd_80178D40 *)arg1)->a.w, D_8019B9B4, D_8019B9B8 ? 0x48 : 0x40);
        (*(s16*)&D_8019BD3C) = 2;
        break;
    case 0:
        func_80179B28(D_8019B9A8);
        D_8019B9A8 = ((s32 (*)(s32, s32, s32))func_80137614)(((Cmd_80178D40 *)arg1)->a.w, D_8019B9AC, D_8019B9B0 ? 0x48 : 0x40);
        (*(s16*)&D_8019BD3C) = 1;
        break;
    case 0x45:
        ((void (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0));
        if (D_8019BBE0 != 0) {
            func_80179B28(D_8019B9A8);
            D_8019B9A8 = ((s32 (*)(s32, s32, s32))func_80137614)(((Actor_80178D40 *)arg0)->unkDC[1], D_8019B9AC, D_8019B9B0 ? 0x48 : 0x40);
            (*(s16*)&D_8019BD3C) = 1;
        } else {
            (*(s16*)&D_8019BD3C) = 3;
        }
        break;
    case 0x32:
        func_80179B28(D_8019B9A8);
        D_8019B9A8 = ((s32 (*)(s32, s32, s32))func_80137614)(((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w], D_8019B9AC,
                                   D_8019B9B0 ? 0x48 : 0x40);
        (*(s16*)&D_8019BD3C) = 1;
        break;
    case 2:
        func_80179B28(D_8019B9A8);
        if (D_8019B9C0 != 0) {
            D_8019B590 = D_8019B9C0;
            D_8019B9C0 = 0;
            (*(s16*)&D_8019BD3C) = 3;
            return;
        }
        (*(s16*)&D_8019BD3C) = 6;
        break;
    case 6:
        func_80179DF8();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 3:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *))func_80179D30)(&v10);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 4:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *, void *, void *))func_8012F214)(((Actor_80178D40 *)arg0), &v10, &v18);
        ((void (*)(void *))func_80179D30)(&v18);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x4C:
        ((void (*)(void *))func_80179D78)((void *)((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x4D:
        v10.vx = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f0;
        v10.vy = 0;
        v10.vz = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f4;
        ((void (*)(void *, void *, void *))func_8012F214)(((Actor_80178D40 *)arg0), &v10, &v18);
        v18.pad = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f6;
        ((void (*)(void *))func_80179D78)(&v18);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x15:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *, void *, void *))func_8012F214)(((Actor_80178D40 *)arg0)->unkD4, &v10, &v18);
        ((void (*)(void *))func_80179D30)(&v18);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 5:
        ((void (*)(s32))func_80179DCC)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 7:
        ((void (*)(s32))func_80179E1C)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 8:
        ((void (*)(s32))func_80179E74)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 9:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *))func_80179EA0)(&v10);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0xA:
        v10.vx = ((Actor_80178D40 *)arg0)->unk6;
        v10.vy = ((Actor_80178D40 *)arg0)->unkA;
        v10.vz = ((Actor_80178D40 *)arg0)->unkE;
        ((void (*)(void *))func_80179EA0)(&v10);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x16: {
        Actor_80178D40 *p = ((Actor_80178D40 *)arg0)->unkD4;
        v10.vx = p->unk6;
        v10.vy = p->unkA;
        v10.vz = p->unkE;
        ((void (*)(void *))func_80179EA0)(&v10);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    }
    case 0xB:
        func_8017A0F4();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0xC:
        func_8017A11C();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0xD:
        func_8017A180();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0xE:
        func_8017A1A8();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x10:
        func_8017A1D0();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x46:
        func_8017A1F8();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x59:
        func_8017A220();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x5A:
        func_8017A248();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x49:
        func_8017A144(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x47:
        func_8017A270();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x17:
        ((void (*)(s32))func_80179EE8)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x18:
        ((void (*)(s32, s32))func_80179F14)(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x19:
        ((void (*)(s32))func_80179F6C)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x1A:
        ((void (*)(s32))func_80179F98)(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x51:
        ((void (*)(s32))func_8017A040)(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x1B:
        D_8019B9E0 = ((Cmd_80178D40 *)arg1)->a.w;
        func_80179F44();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x1C:
        func_8017A338();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x52:
        func_8017A360();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x1D:
        func_8017A388();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x3B:
        func_8017A094(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x3C:
        func_8017A0C4(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0xF:
    case 0x3F:
        (*(s16*)&D_8019BD3C) = 4;
        D_8019B594 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3E:
        (*(s16*)&D_8019BD3C) = 5;
        D_8019B9D4 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x40:
        D_8019B9D4 = (s32)func_8017A3B0;
        (*(s16*)&D_8019BD3C) = 5;
        break;
    case 0x23:
        ((void (*)(void *, s32))func_8012A828)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x31:
        ((void (*)(void *, s32))func_8012A828)(((Actor_80178D40 *)arg0), ((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x24:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unk20->unk12 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x25:
        g[0] = 1;
        g[2] = ((Actor_80178D40 *)arg0)->unk20->unk12 + ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_8019BD3C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x48:
        g[0] = 1;
        g[2] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_8019BD3C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x26:
        g[0] = 1;
        g[2] = ((s32 (*)(void *))func_8012B8A4)(((Actor_80178D40 *)arg0));
        g[1] = 0x1E;
        (*(s16*)&D_8019BD3C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3D:
        ((void(*)(void *, s32))func_8012E8E0)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x27:
        g[0] = 2;
        g[4] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8019BD3C) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x4F:
        g[5] = 1;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8019BD3C) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        /* fallthrough */
    case 0x28:
        g[5] = 0;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8019BD3C) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        break;
    case 0x29:
        v20.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v20.vy = ((Actor_80178D40 *)arg0)->unkA;
        v20.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *, void *, void *))func_8012F214)(((Actor_80178D40 *)arg0), &v20, &v28);
        g[5] = 0;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v28;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x50:
        v30.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v30.vy = ((Actor_80178D40 *)arg0)->unkA;
        v30.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        ((void (*)(void *, void *, void *))func_8012F214)(((Actor_80178D40 *)arg0), &v30, &v38);
        g[5] = 1;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v38;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x2A:
        g[0] = 4;
        (*(s16*)&D_8019BD3C) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x1E:
        ((void (*)(void *, s32))func_8017B238)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x21:
        ((void (*)(void *, s32))func_8017BA3C)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        ((void (*)(void *, s32))func_8017B238)(((Actor_80178D40 *)arg0), (s32)&D_8019B9C4);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x54:
        ((void (*)(void *, s32))func_8017BB34)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        ((void (*)(void *, s32))func_8017B238)(((Actor_80178D40 *)arg0), (s32)&D_8019B9C4);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x1F:
        ((void (*)(void *, s32))func_8017B614)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x22:
        ((void (*)(void *, s32))func_8017BA3C)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        ((void (*)(void *, s32))func_8017B614)(((Actor_80178D40 *)arg0), (s32)&D_8019B9C4);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x55:
        ((void (*)(void *, s32))func_8017BB34)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        ((void (*)(void *, s32))func_8017B614)(((Actor_80178D40 *)arg0), (s32)&D_8019B9C4);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x20:
        func_8017B7A8(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x4E:
        D_8019B9E8 = ((Cmd_80178D40 *)arg1)->a.w;
        func_8017B940(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x57:
        func_8017B824();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x58:
        func_8017B880();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x2B:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unk2 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2C:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unk34 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2D:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unkD8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2F:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unk10A = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2E:
        (*(s16*)&D_8019BD3C) = 3;
        ((Actor_80178D40 *)arg0)->unkF8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x11:
        func_8017A298();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x12:
        func_8017A2C0();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x13:
        func_8017A2E8();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x14:
        func_8017A310();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x33: {
        void (*f)(Actor_80178D40 *) = (void (*)(Actor_80178D40 *))((Cmd_80178D40 *)arg1)->a.w;
        D_8019BCC4 = (s32)&((Cmd_80178D40 *)arg1)[1];
        f(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8019BD3C) = 3;
        break;
    }
    case 0x30:
        if (((Cmd_80178D40 *)arg1)->a.w == 0) {
            ((void (*)(void *))func_8012E8A8)(((Actor_80178D40 *)arg0));
            (*(s16*)&D_8019BD3C) = 3;
        } else {
            ((void (*)(void *))func_8012E88C)(((Actor_80178D40 *)arg0));
            (*(s16*)&D_8019BD3C) = 3;
        }
        break;
    case 0x4A:
        ((void(*)())func_80175414)();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x4B:
        func_80175454();
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x34:
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B590 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x35:
        D_8019B9C0 = (s32)&((Cmd_80178D40 *)arg1)[1];
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B590 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x36:
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B590 += 8;
        if (((s32 (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0)) == 0) {
            break;
        }
        D_8019B590 = *(s32 *)(D_8019B590 + 4);
        return;
    case 0x37:
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B9AC = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_8019B9B0 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x38:
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B9B4 = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_8019B9B8 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x39: {
        s32 w1, w2;
        v40.vx = ((Actor_80178D40 *)arg0)->unk6;
        v40.vy = ((Actor_80178D40 *)arg0)->unkA;
        v40.vz = ((Actor_80178D40 *)arg0)->unkE;
        v48.vx = pv->unk6;
        v48.vy = pv->unkA;
        v48.vz = pv->unkE;
        ((void (*)(void *, void *))func_8012F40C)(out50, &v40);
        w1 = out50[0];
        ((void (*)(void *, void *))func_8012F40C)(out50, &v48);
        w2 = out50[0];
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B9AC = w1;
        D_8019B9B0 = (s16)w1 >= (s16)w2;
        break;
    }
    case 0x3A: {
        s32 w1, w2;
        v58.vx = ((Actor_80178D40 *)arg0)->unk6;
        v58.vy = ((Actor_80178D40 *)arg0)->unkA;
        v58.vz = ((Actor_80178D40 *)arg0)->unkE;
        v60.vx = pv->unk6;
        v60.vy = pv->unkA;
        v60.vz = pv->unkE;
        ((void (*)(void *, void *))func_8012F40C)(out50, &v58);
        w1 = out50[0];
        ((void (*)(void *, void *))func_8012F40C)(out50, &v60);
        w2 = out50[0];
        (*(s16*)&D_8019BD3C) = 3;
        D_8019B9B4 = w2;
        D_8019B9B8 = (s16)w1 < (s16)w2;
        break;
    }
    case 0x41:
        ((void(*)(s32, s32))func_8002D4C8)(((Cmd_80178D40 *)arg1)->a.uh[0], ((Cmd_80178D40 *)arg1)->a.uh[1]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x42:
        ((void (*)(s32))func_8017AD0C)(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x43:
        D_8019B9D4 = (s32)func_8017A3D8;
        D_8019B9DC = 0;
        (*(s16*)&D_8019BD3C) = 5;
        D_8019B9D8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x44:
        func_8001AAD0(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x53:
        ((void (*)(s32))func_80179E48)(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x56:
        ((void (*)(s32))func_80179FEC)(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    L5B_found:
        fp5b = ((Cmd_80178D40 *)arg1)->a.w;
        *q5b = fp5b;
        ((void (*)(Actor_80178D40 *))fp5b)(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8019BD3C) = 3;
        break;
    case 0x5B:
        i5b = 0;
        q5b = D_8019B9EC;
        do {
            i5b++;
            if (*q5b == 0) {
                goto L5B_found;
            }
            q5b++;
        } while (i5b < 10);
        (*(s16*)&D_8019BD3C) = 3;
        break;
    L5C_found1:
        *q5c = 0;
        goto L5C_join;
    case 0x5C:
        i5c = 0;
        if (((Cmd_80178D40 *)arg1)->a.w != 0) {
            fp5c = ((Cmd_80178D40 *)arg1)->a.w;
            q5c = D_8019B9EC;
            do {
                if (*q5c == fp5c) {
                    goto L5C_found1;
                }
                i5c++;
                q5c++;
            } while (i5c < 10);
        L5C_join:
            if (i5c != 10) {
                (*(s16*)&D_8019BD3C) = 3;
                break;
            }
            i5c = 0;
            do {
                p5c = &D_8019B9EC[i5c];
                if (*p5c != 0) {
                    goto L5C_found2;
                }
                i5c++;
            } while (i5c < 10);
            (*(s16*)&D_8019BD3C) = 3;
            break;
        L5C_found2:
            *p5c = 0;
            goto L5D;
        }
        r5c = D_8019B9EC;
        do {
            i5c++;
            if (*r5c != 0) {
                *r5c = 0;
                goto L5D;
            }
            r5c++;
        } while (i5c < 10);
        /* fallthrough */
    case 0x5D:
    L5D:
        (*(s16*)&D_8019BD3C) = 3;
        break;
    default:
        break;
    }
Lend:
    D_8019B590 += 8;
}

#include "../shared/ov/func_80179B28.h"



// @class: schedule
// @unstuck(P36): none — MATCH (111 ins). symcheck: data syms CLEAN (D_8019B598/D_8019B99C, 0 INVENTED); its lone MISSING is jtbl_801D8F9C, the COMPILER-emitted table ($L17 -> .rdata) — banking needs the §8a/§8e rodata-island flip (35 entries, .align 3), not a source-side ref.
/* func_80179B74 (ov_SC01_077) — command-queue WRITER: copies the opcode + its
 * operand halfwords from *p into the 0x200-entry ring D_8019B598 at write index
 * D_8019B99C.  Mirror of the reader func_8017A4AC (same ring, read index D_801DA710).
 *
 * Three levers were needed on top of the obvious shape (each byte-proven here):
 *  1. jtbl SPAN — the target's table is 35 entries (0..0x22) with NO `addiu a0,a0,-1`
 *     bias and `sltiu v0,a0,0x23`, so the source must contain an empty `case 0:` and
 *     an empty `case 0x22:`; without them gcc biases by -1 and emits sltiu 0x20.
 *  2. SCHEDULE — the operand push must route through a NAMED block-scoped temp
 *     (`{ s16 t = *p++; ring[idx] = t; ... }`).  Written as the anonymous
 *     `ring[idx] = *p++;` the sched1 pass puts the `lh D_8019B99C` ahead of the
 *     `lhu 0(a1)` in exactly the two blocks that also carry a live `addiu a1,a1,2`
 *     (cases {1,5} and {0x17,0x1c,0x1d,0x20}) — 6 of the 8 residual mismatches.
 *     The temp gives the loaded value its own pseudo and flips those two blocks.
 *  3. FRAME — the target reserves 0x80 with NO saves and NO spills; gcc's own
 *     (unused) area for this body is 0x58, so +0x28 of address-taken local is
 *     required: `s32 pad[10]; (void)&pad;` (cookbook §17 phantom-frame INDUCE
 *     lever).  10 words exactly; 8 -> 0x78 and 12 -> 0x88 both miss.
 *
 * Case-block ORDER in the source is the emitted block order: {1,5} then {0x13}
 * then {2,3,4,6,0x12,0x14,0x1f} then {0x17,0x1c,0x1d,0x20}.  The 3-/2-/1-push
 * tails are then cross-jump merged (no calls, so §88 does not block it) into the
 * shared .L80179CE4 / .L80179D08 tail that sits after the last case block.
 *
 * Symbols are the splat spellings and match the sibling TU ov_SC01_077_jr_8017A4AC.c
 * (`extern u16 D_8019B598[0x200];` / `extern s16 D_8019B99C;`) so the whole-binary
 * link and any one-big-TU build see one consistent type.
 */

extern u16 D_8019B598[0x200];
extern s16 D_8019B99C;

void func_80179B74(u16 *p) {
    s32 pad[10];
    s16 c;

    (void)&pad;
    c = *p++;
    D_8019B598[D_8019B99C] = c;
    D_8019B99C = (D_8019B99C + 1) & 0x1FF;
    switch (c) {
    case 0:
        break;
    case 1:
    case 5:
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        break;
    case 0x13:
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        break;
    case 2:
    case 3:
    case 4:
    case 6:
    case 0x12:
    case 0x14:
    case 0x1F:
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        break;
    case 0x17:
    case 0x1C:
    case 0x1D:
    case 0x20:
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        { s16 t = *p++; D_8019B598[D_8019B99C] = t; D_8019B99C = (D_8019B99C + 1) & 0x1FF; }
        break;
    case 0x22:
        break;
    }
}

#include "../shared/ov/func_80179D30.h"


#include "../shared/ov/func_80179D78.h"


#include "../shared/ov/func_80179DCC.h"


#include "../shared/ov/func_80179DF8.h"


#include "../shared/ov/func_80179E1C.h"


#include "../shared/ov/func_80179E48.h"


#include "../shared/ov/func_80179E74.h"


#include "../shared/ov/func_80179EA0.h"


#include "../shared/ov/func_80179EE8.h"


#include "../shared/ov/func_80179F14.h"


#include "../shared/ov/func_80179F44.h"


#include "../shared/ov/func_80179F6C.h"


#include "../shared/ov/func_80179F98.h"


#include "../shared/ov/func_80179FEC.h"


#include "../shared/ov/func_8017A040.h"



extern void func_80179B74(u16 *p);

void func_8017A094(s32 arg0) {

    extern s32 D_8019B9BC;
    s16 sp10;

    D_8019B9BC = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}



extern void func_80179B74(u16 *p);

void func_8017A0C4(s32 arg0) {

    extern s32 D_8019B9BC;
    s16 sp10;

    D_8019B9BC = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}


#include "../shared/ov/func_8017A0F4.h"


#include "../shared/ov/func_8017A11C.h"



extern void func_80179B74(u16 *p);

void func_8017A144(s32 a0) {

    extern s32 D_8019B9E4;
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_8019B9E4 = a0;
}


#include "../shared/ov/func_8017A180.h"


#include "../shared/ov/func_8017A1A8.h"


#include "../shared/ov/func_8017A1D0.h"


#include "../shared/ov/func_8017A1F8.h"


#include "../shared/ov/func_8017A220.h"


#include "../shared/ov/func_8017A248.h"


#include "../shared/ov/func_8017A270.h"


#include "../shared/ov/func_8017A298.h"


#include "../shared/ov/func_8017A2C0.h"


#include "../shared/ov/func_8017A2E8.h"


#include "../shared/ov/func_8017A310.h"


#include "../shared/ov/func_8017A338.h"


#include "../shared/ov/func_8017A360.h"


#include "../shared/ov/func_8017A388.h"




s32 func_8017A3B0(void) {

    extern s16 D_8019B9A0;
    switch (D_8019B9A0) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH


extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{

    extern short D_8019B9DC;
    extern short D_8019B9D8;
    switch (D_8019B9DC) {
    case 0:
        func_800D0CA0(1);
        D_8019B9DC = D_8019B9DC + 1;
        return 0;
    case 100:
    {
        int a;
        a = D_8019B9D8;
        if (a != -1) {
            return ((int (*)(s32 arg0))func_8001AAA0)(a) != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_8019B9DC = D_8019B9DC + 1;
        if (D_8019B9DC < 0x1E) {
            return 0;
        }
        D_8019B9DC = 100;
        return 0;
    }
}



// func_8017A4AC (ov_SC01_077) — 536-ins command/bytecode interpreter, 35-case jtbl switch.


    extern s16 D_8019B998;
    extern s32 D_8019B9E0;


extern void func_80172310(u8*);
extern void func_80172738(void);
extern void func_80172780(void*);
extern void func_80172894(void*);
extern void func_801729B0(s32);
extern void func_80172B14(s16);
extern void func_80172C50(void*);
extern void func_80172D68(s32);
extern void func_80172E94(void);
extern void func_80172ED4(void);
extern void func_80172EFC(void);
extern void func_80172F24(void);
extern void func_80172F4C(void);
extern void func_80172F9C(void);
extern void func_80172FEC(void);
extern void func_80173174(void);
extern void func_8017329C(void);
extern void func_8017334C(void);
extern void func_801733A4(void);
extern void func_801733FC(s32, s32);
extern void func_80173460(s32, s32);
extern void func_801734BC(s32, s32);
extern void func_801736B0(s32, s32);
extern void func_801737B8(s16);
extern void func_801738DC(s16);
extern void func_80173A28(s32, s32, s32, s32, s32, s32);
extern void func_8017427C(void);
extern void func_80174438(s32);
extern void func_8017452C(void);
extern void func_80174584(void);
extern void func_801745DC(void);
extern s32 func_80174754(void);

void func_8017A4AC(void) {

    extern s32 D_80126B58;
    extern s16 D_8019B9A0;
    extern s32 D_8019B9BC;
    extern s32 D_8019B9E4;
    u16 sp18[4];
    u16 sp20[4];
    u16 sp28[4];
    u16 sp30[4];
    struct S126B58 *w = &(*(struct S126B58 *)&D_80126B58);
    s16 cmd;

    if (D_8019B998 == D_8019B99C) {
        if (func_80174754() != 0) {
            D_8019B9A0 = 0;
        } else {
            D_8019B9A0 = 1;
        }
        return;
    }
    D_8019B9A0 = 1;
    if (func_80174754() == 0) {
        return;
    }
    cmd = D_8019B598[D_8019B998];
    D_8019B998 = (D_8019B998 + 1) & 0x1FF;
    switch (cmd) {
    case 0:
        func_80172738();
        return;
    case 1:
        sp18[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172780)(sp18);
        return;
    case 28:
        sp18[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[3] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172894)(sp18);
        return;
    case 2:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(s16))func_801729B0)(arg);
        return; }
    case 3:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        func_80172B14(arg);
        return; }
    case 4:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        { s32 t = w->unk20->unk12 + arg;
        func_80172B14(t & 0xFFF); }
        return; }
    case 5:
        sp18[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp18[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172C50)(sp18);
        return;
    case 6:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(s16))func_80172D68)(arg);
        return; }
    case 7: func_80172E94(); return;
    case 8: func_80172ED4(); return;
    case 27: ((void (*)())D_8019B9E4)(); return;
    case 9: func_80172EFC(); return;
    case 10: func_80172F24(); return;
    case 11: func_80173174(); return;
    case 12: func_80172F4C(); return;
    case 33: func_80172F9C(); return;
    case 34: func_80172FEC(); return;
    case 13: func_801745DC(); return;
    case 14:
    case 15: func_8017329C(); return;
    case 16: func_8017334C(); return;
    case 17: func_801733A4(); return;
    case 18:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        func_801738DC(arg);
        return; }
    case 19: {
        s16 a, b;
        s32 ea, eb;
        a = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF; ea = a;
        b = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF; eb = b;
        func_801736B0(ea, eb);
        return;
    }
    case 20:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(s16))func_801734BC)(arg);
        return; }
    case 23:
        sp20[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp20[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp20[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(s16, u16 *))func_80173460)(arg, sp20);
        return; }
    case 29:
        sp28[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp28[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp28[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(s16, u16 *))func_801733FC)(arg, sp28);
        return; }
    case 32:
        sp30[0] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp30[1] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp30[2] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        sp30[3] = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        ((void (*)(u16 *))func_80172310)(sp30);
        return;
    case 25: func_8017452C(); return;
    case 30: func_80174584(); return;
    case 26: func_8017427C(); return;
    case 24: func_80174438(D_8019B9E0); return;
    case 21:
        ((void (*)(s32, s32, s32, s32, void *, s32))func_80173A28)((*(struct S734 * *)&D_8019B9BC)->unk0, (*(struct S734 * *)&D_8019B9BC)->unk4, (*(struct S734 * *)&D_8019B9BC)->unk8,
                      (*(struct S734 * *)&D_8019B9BC)->unkC, (*(struct S734 * *)&D_8019B9BC)->unk10, (*(struct S734 * *)&D_8019B9BC)->unk18);
        return;
    case 22:
        (*(struct S734 * *)&D_8019B9BC)->unk1C((*(struct S734 * *)&D_8019B9BC)->unk4, (*(struct S734 * *)&D_8019B9BC)->unk10, (*(struct S734 * *)&D_8019B9BC)->unk18);
        return;
    case 31:
        { s16 arg = D_8019B598[D_8019B998]; D_8019B998 = (D_8019B998 + 1) & 0x1FF;
        func_801737B8(arg);
        return; }
    }
}

#include "../shared/ov/func_8017AD0C.h"


#include "../shared/ov/func_8017ADE8.h"


#include "../shared/ov/func_8017AE08.h"


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974;

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012BE98(s32, u16*);
extern s32 func_80012A60(s32 a0, s32 a1);


void func_8017AE2C(s32 param_1) {

    extern s16 D_8019BC98;
    extern s16 D_8019BC9A;
    extern s16 D_8019BCA4;
    s32 pv = param_1;
    s16 *g = &D_8019BC98;

    switch (g[0]) {
    case 0:
    default:
        return;
    case 1:
        g[1] = (u16)g[1] - 1;
        if (g[1] <= 0) {
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) = (u16)g[2];
            goto reset_both;
        }
        {
            s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), g[2], 6);
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
        }
        return;
    case 2:
        func_8012B178(pv, (s32)g[4] << 8);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        break;
    case 3:
        if (g[1] != 0) {
            if (g[5] != 0) {
                void *p = (void *)(pv + 4);
                if ((s16)func_80012A60(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12),
                                       (s16)func_8012B744(p, &g[6])) < 0x100) {
                    g[1] = 0;
                }
                *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    func_8012B744(p, &D_8019BCA4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_8019BC98+0xC == &D_8019BCA4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_8019BC98 + 0xC)) < 0x101) {
                    D_8019BC98 = 0;
                    D_8019BC9A = 0;
                }
            }
            {
                s32 t = func_8012B744((void *)(pv + 4), &g[6]);
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), t, g[3]);
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
            }
            g[1] = (u16)g[1] - 1;
            if (g[1] > 0) {
                return;
            }
            g[1] = 0;
            return;
        }
        *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            func_8012B744((void *)(pv + 4), &D_8019BCA4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_8019BC98 + 0xC)) < 0x101) {
            D_8019BC98 = 0;
            D_8019BC9A = 0;
        }
        return;
    case 4:
        func_8012AD80(pv);
    }
    g[1] = (u16)g[1] - 1;
    if (g[1] > 0) {
        return;
    }
reset_both:
    g[0] = 0;
    g[1] = 0;
    return;
}

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);


// @class: plumbing
// @unstuck(P36): none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_8019BA1C;
    extern s16 D_8019BA1E;
    extern s16 D_8019BA20;
    extern s16 D_8019BA14;
    extern s16 D_8019BA16;
    extern s16 D_8019BA18;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_8019BA1C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_8019BA1E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_8019BA20, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_8019BA14, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_8019BA16, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_8019BA18, (s32)((s16)param_2));
}


extern void func_8012A418(void);

void func_8017B1D8(void) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_8019B9A4;
    extern u16 D_8019BA24;
    extern u16 D_8019BA26;
    extern u16 D_8019BA28;
    extern s16 D_8019BCC8;
    func_8012A418();
    D_8019BCC8 = 0;
    D_8019B9A4 = 0;
    D_8019BA24 = D_80126B5E;
    D_8019BA26 = D_80126B62;
    D_8019BA28 = D_80126B66;
}


extern void func_8012A018(s32 a, s32 b);
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017B238;

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @unstuck(P36): none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{

    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80185DE8[];
    extern s16 D_8019BA1C;
    extern s16 D_8019BA14;
    extern u8 D_8012694C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_80185DE8[((u32)param_2) * 0x10];
        a2addr = (s32)&D_80185DE8[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_8019BA1C;
        s16 *p78C = &D_8019BA14;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_8019BCC8 = 1;
        D_8019B9A4 = 0;
    }
}



// @class: struct
// @unstuck(P36): none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{

    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_8019B9C4;
    extern SV4_8017B368 D_8019B9CC;
    extern s16 D_8019BA1C;
    extern s16 D_8019BA14;
    extern u16 D_80185DE8;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_8019B9C4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_8019B9CC;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185DE8)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185DE8)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_8019BA1C) = loc0;
    (*(SV4_8017B368 *)&D_8019BA14) = loc1;
    D_8019BCC8 = 1;
    D_8019B9A4 = 0;
}




s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_8019B9C4;
    extern SV4_8017B368 D_8019B9CC;
    extern s16 D_8019BA1C;
    extern s16 D_8019BA14;
    extern u16 D_80185DE8;
    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_8019B9C4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_8019B9CC;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185DE8)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185DE8)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_8019BA1C) = loc0;
    (*(SV4_8017B368 *)&D_8019BA14) = loc1;
    D_8019BCC8 = 1;
    D_8019B9A4 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_8019BA1C).a;
    D_80126994 = (*(SV4_8017B368 *)&D_8019BA1C).b;
    D_80126998 = (*(SV4_8017B368 *)&D_8019BA1C).c;
    D_80126984 = (*(SV4_8017B368 *)&D_8019BA14).a;
    D_80126988 = (*(SV4_8017B368 *)&D_8019BA14).b;
    D_8012698C = (*(SV4_8017B368 *)&D_8019BA14).c;
}


extern void func_8012A018(s32 a, s32 b);

// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @unstuck(P36): 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.




s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80185DE8[];
    extern s16 D_8019BA1C;
    extern s16 D_8019BA1E;
    extern s16 D_8019BA20;
    extern s16 D_8019BA14;
    extern s16 D_8019BA16;
    extern s16 D_8019BA18;
    extern u8 D_8012694C[];
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_80185DE8[((u32)param_2) * 0x10];
        a2addr = (s32)&D_80185DE8[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    *(Blk8_8017B614 *)&D_8019BA1C = *(Blk8_8017B614 *)&buf[0];
    *(Blk8_8017B614 *)&D_8019BA14 = *(Blk8_8017B614 *)&buf[8];
    func_8012A018((s32)func_8017BE60, 0);
    D_8012694C[0] = 0;
    D_8019BCC8 = 1;
    D_8019B9A4 = 0x1E;
    D_80126990 = ((SV4_8017B368 *)&D_8019BA1C)->a;
    D_80126994 = D_8019BA1E;
    D_80126998 = D_8019BA20;
    D_80126984 = ((SV4_8017B368 *)&D_8019BA14)->a;
    D_80126988 = D_8019BA16;
    D_8012698C = D_8019BA18;
    func_80129CF8();
}




// @class: plumbing
// @unstuck(P36): none — MATCH



void func_8017B7A8(void)
{

    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8 D_8012694C;
    extern s16 D_8019B9A4;
    extern s16 D_8019BA1C;
    extern s16 D_8019BA1E;
    extern s16 D_8019BA20;
    extern s16 D_8019BA14;
    extern s16 D_8019BA16;
    extern s16 D_8019BA18;
    D_8012694C = 1;
    D_8019B9A4 = 0;
    D_8019BA1C = (s16) D_80114F30;
    D_8019BA1E = (s16) D_80114F34;
    D_8019BA20 = (s16) D_80114F38;
    D_8019BA14 = (s16) aD80114F24;
    D_8019BA16 = (s16) D_80114F28;
    D_8019BA18 = (s16) D_80114F2C;
}




void func_8017B824(void) {

    extern s32 D_801151D4;
    extern s16 D_8019BA34;
    extern s16 D_8019BA36;
    extern s16 D_8019BA38;
    extern s16 D_8019BA3C;
    extern s16 D_8019BA3E;
    extern s16 D_8019BA40;
    D_8019BA34 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_8019BA36 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_8019BA38 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_8019BA3C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_8019BA3E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_8019BA40 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @unstuck(P36): none — MATCH



void func_8017B880(void)
{

    extern s16 D_8019BA34;
    extern s16 D_8019BA36;
    extern s16 D_8019BA38;
    extern s16 D_8019BA3C;
    extern s16 D_8019BA3E;
    extern s16 D_8019BA40;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    D_80114F30 = D_8019BA34;
    D_80114F34 = D_8019BA36;
    D_80114F38 = D_8019BA38;
    aD80114F24 = D_8019BA3C;
    D_80114F28 = D_8019BA3E;
    D_80114F2C = D_8019BA40;
}





s32 func_8017B8E8(s32 src) {

    extern s16 D_8019BA14;
    extern s16 D_8019BA1C;
    (*(S8_8017B8E8 *)&D_8019BA1C) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_8019BA14) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @unstuck(P36): none — MATCH (63 ins)




void func_8017B940(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_8019BA24;
    extern u16 D_8019BA26;
    extern u16 D_8019BA28;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8  D_8012694C;
    extern s16 D_8019B9A4;
    extern short D_8019BA2C;
    extern short D_8019BA2E;
    extern short D_8019BA30;
    extern s16 D_8019BA1C;
    extern s16 D_8019BA1E;
    extern s16 D_8019BA20;
    extern s16 D_8019BA14;
    extern s16 D_8019BA16;
    extern s16 D_8019BA18;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_8019BA24);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_8019BA26);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_8019BA28);
    (*(s16 *)&D_8019BA2C) = buf[0];
    (*(s16 *)&D_8019BA2E) = buf[1];
    (*(s16 *)&D_8019BA30) = buf[2];
    D_8019BA1C = D_80114F30 + buf[0];
    D_8019B9A4 = 0;
    D_8019BA1E = D_80114F34 + buf[1];
    D_8019BA20 = D_80114F38 + buf[2];
    D_8019BA14 = aD80114F24 + buf[0];
    D_8019BA16 = D_80114F28 + buf[1];
    D_8019BA18 = D_80114F2C + buf[2];
}


typedef struct { s16 vx, vy; } DVEC2_C974_8017BA3C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017BA3C;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C974_8017BA3C;


// @class: struct
// @unstuck(P36): none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32, s32, void*);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_c2: 3x3 short rotation + pad + 3 long translation (offset 0x14) */


void func_8017BA3C(s32 param_1, s32 param_2)
{

    extern SV4 D_8019B9C4;
    extern SV4 D_8019B9CC;
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_c2, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_8019B9CC) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_8019B9C4 = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    ((void (*)(void *, void *, void *))RotTransSV)(&v1, &buf1, &buf2);
    D_8019B9CC = buf1;
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017BB34;




s32 func_8017BB34(s32 param_1, s32 param_2)
{

    extern SV4 D_8019B9C4;
    extern SV4 D_8019B9CC;
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_c2, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_8019B9CC)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_8019B9C4) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_8019B9CC) = buf1;
}




// @class: regalloc-order
// @unstuck(P36): pending self-check — register order param=$s2 counter=$s1 ptr=$s0


void func_8017BC38(int param_1)
{

    extern void (*D_8019B9EC[10])(int);
    int i;
    void (**p)(int);

    i = 0;
    p = D_8019B9EC;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}



// @class: plumbing
// @unstuck(P36): none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);

void func_8017BCA0(int param_1) {

    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    func_8017B0E4(param_1, 0xC);
    D_8019B9A4 = D_8019B9A4 + 1;
    if (D_8019B9A4 >= 0x1F) {
        D_8019BCC8 = 2;
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH expected (simple short-increment + guarded call)


extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{

    extern s16 D_8019B9A4;
    extern s16 D_8019BCC8;
    func_8017B0E4(param_1, 6);
    D_8019B9A4 = D_8019B9A4 + 1;
    if (0x18 < D_8019B9A4) {
        func_8012A4BC();
        D_8019BCC8 = 0;
    }
    return;
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);



void func_8017BD50(int param_1)
{

    extern s16 D_8019B9A4;
    extern void (*D_8019B9E8)(void);
    extern short D_8019BA2C;
    extern short D_8019BA2E;
    extern short D_8019BA30;
    extern s16 D_8019BCC8;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    func_8017B0E4(param_1, 6);
    D_8019B9A4 = D_8019B9A4 + 1;
    if (D_8019B9A4 >= 0x19) {
        if (D_8019B9E8 != 0) {
            (*D_8019B9E8)();
        } else {
            D_80114F30 = D_80114F30 + D_8019BA2C;
            D_80114F34 = D_80114F34 + D_8019BA2E;
            D_80114F38 = D_80114F38 + D_8019BA30;
            aD80114F24 = aD80114F24 + D_8019BA2C;
            D_80114F28 = D_80114F28 + D_8019BA2E;
            D_80114F2C = D_80114F2C + D_8019BA30;
            func_8012A4BC();
        }
        D_8019BCC8 = 0;
    }
}




void func_8017BE60(void *a0) {

    extern void (*D_80185E88[])(void);
    D_80185E88[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}

#include "common.h"

/* ============================================================================
 * func_8017BEBC — ov_SC03_107 / TU ov_SC03_107_jr_801789AC  (741 ins)
 *
 * Structural sibling of the MATCHED func_8017CAD4 (ov_SC06_010_jr_8017A4AC.c,
 * 755 ins) and func_8017BEBC (ov_SC04_005_jr_8017BEBC.c).  Deltas vs those:
 *   - 1 param, no ctx->f0 early-out; part/nparts/vtx loaded indirectly
 *     (part = *(arg0+0xC), model = *(arg0+8), nparts = model->8, vtx = model->0x10)
 *   - extra light-vector prologue: ReadRotMatrix/PushMatrix/func_8004974C/
 *     ApplyMatrixSV/PopMatrix, then outv.vy -= 0x180
 *   - Y screen-cull limits -0x6E/0x6F (SC04_005 twin: -0x78/0x79)
 *   - switch(code&7) handles ONLY {6,7}=POLY_FT3 and {2,3}=POLY_FT4
 *   - opz bias +0x200 spelled `if (code != 6)` / `if (code != 2)` (beq form)
 *   - FT3 arm carries a dead `gte_avsz3()` before the sz max
 *   - fogged rgbc: clamp0(0x80 - (opz-0x190)/24) splatted to 3 bytes
 *   - 0x00FFFFFF / 0xFF000000 OT masks ARE hoisted to the OUTER preheader here
 *     ($s1/$s4), so plain literals — no §37 S2-kill re-tie needed.
 *
 * DECLS: the destination TU already declares D_800A5E60 (`extern s32`, line 846),
 * D_800B9A02 (line 718 + the u16 asm-alias aD800B9A02 line 730) and
 * ApplyMatrixSV (line 725); those spellings are used verbatim below.
 * ========================================================================== */

typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017BEBC;

extern s32 func_800491EC(void);
extern void func_800547D8(s32, MTX_8017BEBC *);
extern void func_80052E38(MTX_8017BEBC *);
extern void ReadRotMatrix(void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void func_8004974C(void *, void *);
/* ApplyMatrixSV: no local extern here — the TU already declares it (lines 725 / 1145,
 * `void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*)`); the call site below casts
 * every arg to (void*), which converts silently to that prototype. Re-declaring it here as
 * (void*, void*, void*) is a DIFFERENT (incompatible) prototype and triggers cc1's
 * "conflicting types for `ApplyMatrixSV'" at splice time — recovery fix S64/func_8017BEBC. */
extern s32 D_800A5E60;
extern u8 D_800A6610[];
extern u16 aD800B9A02 __asm__("D_800B9A02");














void func_8017BEBC(s32 arg0)
{
    typedef struct { u16 vx, vy, vz, pad; } UV8;
    typedef struct { s16 vx, vy; } XDV2;
    typedef struct { s16 vx, vy, vz, pad; } XSV2;
    typedef struct { u32 xx, yy, zz; u32 nprim; u32 *prim; } XPart;
    typedef struct { u32 w0, w1, w2; } XPrim;
    typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1;
                     s16 x2, y2; u16 uv2, p2; } XFT3;
    typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1;
                     s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } XFT4;

    XDV2  tmpxy[4];   /* 0x10 */
    XSV2  box[8];     /* 0x20 */
    XSV2  sxy[8];     /* 0x60 */
    MTX_8017BEBC mtx;        /* 0xA0 */
    UV8   lv;         /* 0xC0 */
    UV8   outv;       /* 0xC8 */
    MTX_8017BEBC m2;         /* 0xD0 */
    MTX_8017BEBC m3;         /* 0xF0 */
    XSV2  sv;         /* 0x110 */
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;   /* 0x118 */

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    XPart *part;
    XPrim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *vd;
    u8 *va, *vb, *vc;
    u32 w;
    s32 code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    {
        /* §153 address-rematerialisation launder: &m2 / &m3 are each an argument
         * TWICE inside this one CSE basic block, so cse unifies the pseudos and
         * global.c hands them a callee-saved reg ($s0 + `move $aN,$s0` per site).
         * The target rematerialises `addiu $aN,$sp,N` at every site. Each launder
         * SETS the pseudo, emptying the address's equivalence class; non-volatile
         * asm so sched2 may still hoist the arg setup above the sv loads. */
        s32 _pm2 = (s32)&m2;
        __asm__("" : "=r"(_pm2) : "0"(_pm2));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        lv.vx = 0;
        lv.vy = 0;
        lv.vz = 0;
        ReadRotMatrix((void *)_pm2);
    }
    PushMatrix();
    sv.vx = lv.vx - m2.t[0];
    sv.vy = lv.vy - m2.t[1];
    sv.vz = lv.vz - m2.t[2];
    {
        s32 _a = (s32)&m2;
        s32 _b = (s32)&m3;
        __asm__("" : "=r"(_a) : "0"(_a));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        __asm__("" : "=r"(_b) : "0"(_b));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        func_8004974C((void *)_a, (void *)_b);
    }
    ApplyMatrixSV((void *)&m3, (void *)&sv, (void *)&outv);
    PopMatrix();
    outv.vy = outv.vy - 0x180;

    pkt = (u8 *)D_800A5E60;
    part = *(XPart **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[aD800B9A02 << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;
        box[4].vx = mn; box[4].vy = my;
        box[5].vx = mx; box[5].vy = my;
        box[6].vx = mn; box[6].vy = my;
        box[7].vx = mx; box[7].vy = my;
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[5].vz = wz;
        box[2].vz = wy;
        box[3].vz = wy;
        box[6].vz = wy;
        box[7].vz = wy;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
            xa32 = sxy[0].vx;
            xb32 = sxy[1].vx;
            if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
            t32 = sxy[2].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            t32 = sxy[3].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            xa32 = sxy[4].vx;
            xb32 = sxy[5].vx;
            if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
            t32 = sxy[6].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            t32 = sxy[7].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            mnc = xmn1;
            if (xmn2 < xmn1) mnc = xmn2;
            mxc = xmx1;
            if (mxc < xmx2) mxc = xmx2;
            if ((s16)mxc >= -0xA0 && (s16)mnc < 0xA1) {
                xa32 = sxy[0].vy;
                xb32 = sxy[1].vy;
                if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
                t32 = sxy[2].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                t32 = sxy[3].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                xa32 = sxy[4].vy;
                xb32 = sxy[5].vy;
                if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
                t32 = sxy[6].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                t32 = sxy[7].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                mnc = xmn1;
                if (xmn2 < xmn1) mnc = xmn2;
                mxc = xmx1;
                if (mxc < xmx2) mxc = xmx2;
                if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                    prim = (XPrim *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3(va, vb, vc);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((XFT3 *)pkt)->x0 > ((XFT3 *)pkt)->x1) {
                                        mx = ((XFT3 *)pkt)->x0;
                                        mn = ((XFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((XFT3 *)pkt)->x0;
                                        mx = ((XFT3 *)pkt)->x1;
                                    }
                                    if (((XFT3 *)pkt)->x2 > mx) mx = ((XFT3 *)pkt)->x2;
                                    else if (((XFT3 *)pkt)->x2 < mn) mn = ((XFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((XFT3 *)pkt)->y0 > ((XFT3 *)pkt)->y1) {
                                            my = ((XFT3 *)pkt)->y0;
                                            /* §47 live-length SLIDER x2, differential form: placed where `my` is
                                             * LIVE and `mny` is DEAD (between the two arm assignments), so it
                                             * lengthens ONLY `my`. A slider in the common range moves both
                                             * equally and never reaches the plateau (probed A=0..8: my/mny
                                             * stayed wrong at every count). +2 here lands int(K/L_my) on
                                             * int(K/L_mny) -> exact allocno tie -> global.c allocno_compare
                                             * falls through to creation order -> mny (created first) takes
                                             * $a2, which is what the target has. Zero bytes (#APP/#NO_APP). */
                                            __asm__ volatile ("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                                            __asm__ volatile ("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                                            mny = ((XFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((XFT3 *)pkt)->y0;
                                            my = ((XFT3 *)pkt)->y1;
                                        }
                                        if (((XFT3 *)pkt)->y2 > my) my = ((XFT3 *)pkt)->y2;
                                        else if (((XFT3 *)pkt)->y2 < mny) mny = ((XFT3 *)pkt)->y2;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, tz, q, rgb;
                                            u32 *otp;
                                            u32 *tp;
                                            gte_avsz3();
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 6) g.opz = za + 0x200;
                                            tz = g.opz;
                                            tp = (u32 *)prim->w0;
                                            q = 0x80 - (tz - 0x190) / 24;
                                            if (q < 0) q = 0;
                                            rgb = q | (q << 8) | (q << 16);
                                            ((XFT3 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                            ((XFT3 *)pkt)->uvc0 = tp[1];
                                            ((XFT3 *)pkt)->uvp1 = tp[2];
                                            ((XFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((tz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) {
                                        mx = tmpxy[0].vx;
                                        mn = tmpxy[1].vx;
                                    } else {
                                        mn = tmpxy[0].vx;
                                        mx = tmpxy[1].vx;
                                    }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        /* §47 slider x2 — same tie, the FT4 arm's half of it. */
                                        __asm__ volatile ("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                                        __asm__ volatile ("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((XFT4 *)pkt)->x3);
                                        if (((XFT4 *)pkt)->x3 < mn) mn = ((XFT4 *)pkt)->x3;
                                        else if (mx < ((XFT4 *)pkt)->x3) mx = ((XFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((XFT4 *)pkt)->y3 < mny) mny = ((XFT4 *)pkt)->y3;
                                            else if (my < ((XFT4 *)pkt)->y3) my = ((XFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb, tz, q, rgb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code != 2) g.opz = za + 0x200;
                                                *(u32 *)&((XFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((XFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((XFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tz = g.opz;
                                                tp = (u32 *)prim->w0;
                                                q = 0x80 - (tz - 0x190) / 24;
                                                if (q < 0) q = 0;
                                                rgb = q | (q << 8) | (q << 16);
                                                ((XFT4 *)pkt)->rgbc = (tp[0] & 0xFF000000) | rgb;
                                                ((XFT4 *)pkt)->uvc0 = tp[1];
                                                ((XFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((XFT4 *)pkt)->uv2 = uvw;
                                                ((XFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((tz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    D_800A5E60 = (s32)pkt;
}




void func_8017CA50(void *a0) {

    extern void (*D_80185FA0[])(void);
    D_80185FA0[*(u8 *)((s32)a0 + 0x15)]();
}






extern void func_8017CD88(void);
extern void func_800167B8(s32 a0);

s32 func_8017CA8C(s32 a0) {
    func_8017CD88();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017CAD0(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




void func_8017CAF4(void *a0) {

    extern void (*D_80185FA8[])(void);
    D_80185FA8[*(u8 *)((s32)a0 + 0x15)]();
}






extern void func_8017CDB0(void);

s32 func_8017CB30(s32 a0) {
    func_8017CDB0();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017CB70(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_8017CBEC(void) {
    func_800D1EBC();
}




void func_8017CC0C(void *a0) {

    extern void (*D_80185FB4[])(void);
    D_80185FB4[*(u8 *)((s32)a0 + 0x15)]();
}






extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017CC48(s32 a0) {
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}




void func_8017CCBC(void *a0) {

    extern void (*D_80185FC0[])(void);
    D_80185FC0[*(u8 *)((s32)a0 + 0x15)]();
}


    s32 func_8017CCF8(u8 *a0) {
        if (--(*(s32 *)(a0 + 0x28)) == -1) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            if ((func_80029178(0xB8) & 0xFF) == 0) {
                func_800D0C48(1);
            }
            func_800D1E28();
            *(u8 *)(a0 + 0x15) += 1;
        }
        return 0;
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017CD88(void) {

    extern s32 D_80185FCC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185FCC, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017CDB0(void) {

    extern s32 D_80185FD8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185FD8, 0x1000000);
}


#include "common.h"



extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s16 D_80126960;
extern s16 D_80126962;
extern u16 D_801269E8;
extern u16 D_801269EA;
extern u8 D_80126948[];
extern s16 D_80126940;
extern s16 D_801274E8;
extern Blk8 D_801274F0;

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017CF0C(void *a0);

void func_8017CDD8(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x258;
    D_80126968 = 0x71;
    D_8012696A = 0xC00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x32;
    D_8012697A = 0;
    func_8012A018((s32)func_8017CF0C, 0);
    *(Blk8 *)&D_801274E8 = *(Blk8 *)&D_80126940;
    func_8012A094((s32)D_80126948);
    func_8017CF0C(D_80126948);
    func_8012A094((s32)D_80126948);
    *(Blk8 *)&D_801274E8 = D_801274F0;
    D_80126968 = D_801269E8;
    D_80126960 = D_801269E8;
    D_8012696A = D_801269EA;
    D_80126962 = D_801269EA;
}




void func_8017CF0C(void *a0) {

    extern void (*D_80185FEC[])(void);
    D_80185FEC[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

/* 8 bytes, align 1 -> both copies lower through gcc-2.7.2's UNALIGNED
   lwl/lwr + swl/swr pair (cookbook §48-C2 / §160a).  Struct assignment, not
   memcpy: this TU declares `extern void *memcpy(...)` (and an asm-labelled
   `memcpy` at :656), which turns a memcpy call into a real CALL at TU scope
   (see the TU's own note at :5134).  Uniquely named so engine_types.h's
   file-scope `Blk8` typedef is not redefined (C89 rejects a duplicate). */
typedef struct { u8 b[8]; } Blk8_8017CF48;

extern s16 D_80126940;
/* §37 asm-label alias: the destination TU already carries `extern Blk8 D_801274F0;`
   at file scope, so a second file-scope decl of that identifier at another type
   would be a hard error.  Same symbol, own C name. */
extern u8 D_801274F0_8017CF48[8] __asm__("D_801274F0");
extern void (*D_80185FF0[8])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8017D280(s32 a0, s16 *a1);
extern s32 func_8017D418(s16 *arg0, s16 *arg1);
extern void func_8017D474(s32 a0, s32 a1, s32 a2);
extern void func_8017D4C8(s32 a0, s32 a1, s32 a2);
extern void func_8017D51C(s32 *a0, s32 *a1, s32 *a2);

void func_8017CF48(s32 a0) {
    s32 tp;
    register s32 base __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
    void *ap;
    s16 buf[4];
    s32 flag, t;
    s32 t0, t1, u1, u2;

    *(Blk8_8017CF48 *)buf = *(Blk8_8017CF48 *)&D_80126940;
    if (buf[2] < 0x101) goto B;
    if (buf[0] < -0x740) buf[0] = -0x740;
    if (buf[0] < 0xA41) { flag = 0; goto L00C; }
    buf[0] = 0xA40;
    flag = 0;
    goto L00C;
B:
    if (buf[0] < -0x640) buf[0] = -0x640;
    if (buf[0] < 0x581) { flag = 0; goto L00C; }
    buf[0] = 0x580;
    flag = 0;
L00C:
    ap = buf;
    __asm__("" : "=r"(ap) : "0"(ap));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    base = (s32)&D_80185FF0;
    if (func_8017D418((s16 *)ap, (s16 *)base)) goto L164;
    if (func_8017D418(buf, (s16 *)(base + 0x10))) { func_8017D51C((s32 *)a0, (s32 *)buf, (s32 *)(base + 0x10)); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x20))) { func_8017D474(a0, (s32)buf, base + 0x20); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x30))) { func_8017D51C((s32 *)a0, (s32 *)buf, (s32 *)(base + 0x30)); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x40))) { func_8017D4C8(a0, (s32)buf, base + 0x40); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x50))) { func_8017D4C8(a0, (s32)buf, base + 0x50); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x60))) { func_8017D474(a0, (s32)buf, base + 0x60); flag = 1; goto L174; }
    if (func_8017D418(buf, (s16 *)(base + 0x70))) { func_8017D51C((s32 *)a0, (s32 *)buf, (s32 *)(base + 0x70)); flag = 1; goto L174; }
    ap = buf;
    __asm__("" : "=r"(ap) : "0"(ap));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    base = base + 0x80;
    if (func_8017D418((s16 *)ap, (s16 *)base)) goto L164;
    goto L174;
L164:
    func_8017D4C8(a0, (s32)buf, base);
    flag = 1;
L174:
    t = flag;
    if (t == 0) goto LAB;
    t = func_80012DBC(*(s16 *)(a0 + 0x18), *(s16 *)(a0 + 0xA0), 0xA, 1);
    *(s16 *)(a0 + 0x20) = t;
    *(s16 *)(a0 + 0x18) = t;
    *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x22) = func_80012DBC(*(s16 *)(a0 + 0x1A), *(s16 *)(a0 + 0xA2), 0xA, 1);
    goto LEND;
LAB:
    t = func_80012ABC(*(s16 *)(a0 + 0x18), *(s16 *)(a0 + 0xA0), 0xA);
    *(s16 *)(a0 + 0x20) = t;
    *(s16 *)(a0 + 0x18) = t;
    *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x22) = func_80012ABC(*(s16 *)(a0 + 0x1A), *(s16 *)(a0 + 0xA2), 0xA);
LEND:
    tp = (s32)D_801274F0_8017CF48;
    __asm__("" : "=r"(tp) : "0"(tp));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    *(Blk8_8017CF48 *)tp = *(Blk8_8017CF48 *)buf;
    t0 = func_80012F74(*(s16 *)(tp - 8), buf[0], 4, 1);
    u1 = buf[1];
    *(s16 *)(tp - 8) = t0;
    t1 = func_80012F74(*(s16 *)(tp - 6), u1, 4, 1);
    u2 = buf[2];
    *(s16 *)(tp - 6) = t1;
    *(s16 *)(tp - 4) = func_80012F74(*(s16 *)(tp - 4), u2, 4, 1);
    func_8017D280(a0, (s16 *)(tp - 8));
}





// @class: schedule
// @unstuck(P36): none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017D280(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


s32 func_8017D418(s16 *arg0, s16 *arg1) {
    if (arg0[0] < arg1[0] || arg1[1] < arg0[0] || arg0[2] < arg1[2]) {
        return 0;
    }
    return arg1[3] >= arg0[2];
}


void func_8017D474(s32 a0, s32 a1, s32 a2) {
    *(u16 *)(a0 + 0xA0) = *(u16 *)(a2 + 8);
    *(u16 *)(a0 + 0xA2) = *(u16 *)(a2 + 0xA);
    *(s32 *)(a0 + 0x14) = *(s32 *)(a2 + 0xC);
    {
        s32 y = *(s16 *)(a2 + 2);
        s32 x = *(s16 *)(a2 + 0);
        s32 frame_pad[1];
        (void)&frame_pad;
        *(s16 *)(a1 + 0) = x + (y - x) / 2;
    }
}


void func_8017D4C8(s32 a0, s32 a1, s32 a2) {
    *(u16 *)(a0 + 0xA0) = *(u16 *)(a2 + 8);
    *(u16 *)(a0 + 0xA2) = *(u16 *)(a2 + 0xA);
    *(s32 *)(a0 + 0x14) = *(s32 *)(a2 + 0xC);
    {
        s32 y = *(s16 *)(a2 + 6);
        s32 x = *(s16 *)(a2 + 4);
        s32 frame_pad[1];
        (void)&frame_pad;
        *(s16 *)(a1 + 4) = x + (y - x) / 2;
    }
}


void func_8017D51C(s32 *a0, s32 *a1, s32 *a2) {
    *(u16 *)((s32)a0 + 0xA0) = *(u16 *)((s32)a2 + 0x8);
    *(u16 *)((s32)a0 + 0xA2) = *(u16 *)((s32)a2 + 0xA);
    *(s32 *)((s32)a0 + 0x14) = *(s32 *)((s32)a2 + 0xC);
}




void func_8017D540(void *a0) {

    extern void (*D_801860C0[])(void);
    D_801860C0[*(u16 *)((s32)a0 + 0x2)]();
}






s32 func_8017D57C(void *a0, s32 *p) {
    s32 cur = *(s32 *)((s32)a0 + 0xDC);

    if (p[0] != cur) {
        p += 2;
        for (;;) {
            s32 t = p[0];
            if (t == 0) {
                return cur;
            }
            p += 2;
            if (t == cur) {
                break;
            }
        }
        p -= 2;
    }
    return p[1];
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

void func_8017D5C4(void *a0) {
    s32 s1;
    s32 v0;
    s32 ad;
    s32 t;

    extern u8 D_801860B0;
    extern u8 D_801860A0[];
    extern void (*D_80186090[])(void);
    extern u8 D_80186080[];

    s1 = func_80029504();
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, 0);
    ad = (s32)&D_801860B0;
    *(s32 *)((s32)a0 + 0x58) = ad;
    t = *(u16 *)((s32)a0 + 0x2);
    *(s16 *)((s32)a0 + 0x5C) = 0x80;
    *(u16 *)((s32)a0 + 0x2) = t + 1;

    if (s1 >= 0x384) {
        *(s32 *)((s32)a0 + 0xDC) = func_8017D57C(a0, (s32 *)D_801860A0);
    } else if (s1 >= 0x258) {
        *(s32 *)((s32)a0 + 0xDC) = func_8017D57C(a0, (s32 *)D_80186090);
    } else if (s1 >= 0xC8) {
        *(s32 *)((s32)a0 + 0xDC) = func_8017D57C(a0, (s32 *)D_80186080);
    }
}


void func_8017D690(void) {
}

#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern u8 D_801860C8[];

void func_8017D698(s32 a0) {
    s32 r;
    s32 v1;

    if (*(u16 *)(a0 + 0x2) == 0) {
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(a0 + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        ((void (*)(s32))func_8001C2C4)(r);
        *(s16 *)(a0 + 0x5C) = 0x40;
        *(u8 *)(a0 + 0x75) = 0x4;
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
        v1 = *(s16 *)(a0 + 0x70) << 4;
        *(s32 *)(a0 + 0x58) = (s32)&D_801860C8 + v1;
    }
}



s32 func_8017D728(void) {
    return 73;
}




void func_8017D730(void *a0) {

    extern void (*D_8018614C[])(void);
    D_8018614C[*(u16 *)((s32)a0 + 0x2)]();
}






/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void ((void (*)(s32*, s32))func_8012A828)(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_801827D4    : TU declares `extern u8 D_801827D4[];` (block scope, L3467).
 *                   Conformed; `(s32)D_801827D4` == `(s32)&D_801827D4`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_801860E8, func_8017D878, func_8017D76C : no other
 *                   declaration anywhere in the TU (func_8017D878 / func_8017D76C
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern s32 func_8017D878(s32);   /* S80 #10: the real signature (returns the address of func_80172710 or 0); only its ADDRESS is used here */

void func_8017D76C(s32 a0) {

    extern M2C_UNK D_801860E8;
    extern u8 D_801827D4[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_801860E8)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        ((void (*)(s32*, s32))func_8012A828)((s32 *)s0, (s32)D_801827D4);
        func_801788B8(s0, (s32)func_8017D878);
    }
}


void func_8017D7D0(void) {
}

extern void func_80178CBC(s32 a0, s32 a1);
extern u8 D_8018611C;
extern u8 D_80186134[];

void func_8017D7D8(s32 a0) {
    s32 s0 = a0;

    if (*(s16 *)(s0 + 0x70) != 0) {
        func_80178CBC(a0, (s32)D_80186134);
    } else {
        func_80178CBC(s0, (s32)&D_8018611C);
    }
    *(s16 *)(s0 + 0x2) = 3;
}





extern int func_80178970(void);
extern void func_80178D18(void);

void func_8017D838(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


/* func_8017D878 -- verbatim-asm bank (cookbook §265, file-scope form).
   Recovered semantics: takes the actor pointer in $a0. Reads the word at +100,
   passes it to func_8012BD14, and bails with $v0 = 0 when the result is >= 4097.
   Otherwise walks the 96-entry table at D_801202A0 (stride 268): entries whose
   halfword at +0 equals 548 are probed with func_8012BC60(actor+4, entry+4);
   a result below 4096 also bails with $v0 = 0. On success: stores 2 into the
   halfword at +2 of the object the word at +100 points to, calls func_80178BF8
   with no arguments, and returns the ADDRESS of func_80172710 in $v0. */

#include "common.h"

struct Vec;

extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern void func_8012BD14(s32 a0);
extern void func_80172710(void);
extern void func_80178BF8();

s32 func_8017D878(s32 arg0)
{
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;
    s32 v1;

    if (((s32 (*)(s32))func_8012BD14)(*(s32 *)(arg0 + 0x64)) >= 0x1001) {
        return 0;
    }
    for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p == 0x224) {
            if (((s32 (*)(s32, s32))func_8012BC60)(arg0 + 4, (s32)(p + 4)) < 0x1000) {
                return 0;
            }
        }
    }
    v1 = *(s32 *)(arg0 + 0x64);
    *(s16 *)(v1 + 2) = 2;
    /* zero-arg call: target jal carries no argument setup */
    ((void (*)())func_80178BF8)();
    return (s32)func_80172710;
}


extern s32 func_8012C044(s32 a0);
extern u32 D_8019208C[];
extern void func_8017EEA8(void*);

void func_8017D92C(s32 a0) {
    s32 *s0 = (s32 *)a0;
    u32 v0;
    u32 v1;
    u32 (*func_ptr)(void);

    v0 = *(u16 *)((u8 *)s0 + 2);
    v0 = v0 * 4;
    func_ptr = (u32 (*)(void))D_8019208C[v0 / 4];
    func_ptr();

    v0 = *(u16 *)s0;
    if (v0 == 0) {
        return;
    }

    v0 = *(u32 *)((u8 *)s0 + 0x20);
    v1 = *(u16 *)((u8 *)v0 + 0x2C);
    v1 = v1 | 0x10;
    *(u16 *)((u8 *)v0 + 0x2C) = v1;

    v0 = func_8012C044(a0);
    v1 = 1;
    if (v0 != v1) {
        return;
    }
    *(u16 *)((u8 *)s0 + 0x102) = (v0 = 1);
    ((void (*)(s32))func_8017EEA8)(a0);
}


extern s32 D_80191F80;
extern s32 D_80191FB4;
void func_8017D9B8(s32 a0) {
    if (func_8012C354(a0, (s32)&D_80191F80) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xBC) = (s32)&D_80191FB4;
        *(s32 *)(a0 + 0xB4) = 0xFFFBDFD9;
        *(s32 *)(a0 + 0xDC) = 0;
        *(s16 *)(a0 + 0x100) = 0x1000;
        *(s32 *)(a0 + 0xC4) |= 1;
        func_80143970(a0);
        *(s16 *)(a0 + 0x2) = 1;
    }
}





extern void func_8012A828(s32, void*);
    extern short D_80196C28;
    void func_8017DA34(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_80196C28);
    }


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017DA64;

extern s32 func_8012BCCC(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);

// @class: straight-derive
// @unstuck(P36): none — MATCH (52 ins) on iteration 1, confirmed by rtu_match.
//
// Two things that could have been mis-read off the target asm:
//
// 1. RELOAD_CSE DELETES A REDUNDANT ARG MOVE — do not read "no arg setup" as
//    "zero-arg call". `jal func_8012BCCC` at 0x80184C7C has a bare `nop` delay
//    slot and NO `addu $a0,$s0,$zero` before it, which looks like `f()`. It is
//    `f(a0)`: the incoming param is still live in $a0 in that fall-through
//    block, so gcc-2.7.2's reload_cse_regs (reload1.c) deletes the redundant
//    `move $a0,$s0`. The SAME move survives at .L80184CD0 (0x80184CD0) because
//    reload_cse's value tracking resets at a CODE_LABEL. So: an arg move that
//    is present on the labelled arm and absent on the fall-through arm is ONE
//    source-level call shape, not two.
//
// 2. `lui $v1,1 / slt $v1,$v1,$v0` is `ret <= 0x10000`, not `ret < 0x10001`.
//    gcc lowers `a <= C` to `!(C < a)` and puts the CONSTANT in the first slt
//    operand; writing `< 0x10001` would have materialised 0x10001 instead.
//
// Statement order in the then-arm is the Ghidra order (0x1C store, then the
// 0x34 increment): memrefs_conflict_p disambiguates `+0x1C`/4 from `+0x34`/2
// off the same base, so sched2 legally hoists the `lhu 0x34` above the `sw`
// to cover its load delay — which is exactly the target's interleave.
void func_8017DA64(s32 a0) {

    extern u8 D_80193CE4;
    extern u8 D_80196E10[];
    s32 v;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BCCC(a0) <= 0x10000) {
            func_8001C924(*(s32 *)(a0 + 0x20), (void *)&D_80193CE4);
            func_8012A828(a0, (void *)&(*(u8 *)D_80196E10));
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(u16 *)(a0 + 0x34) += 1;
        }
    } else {
        v = func_8012B8E4(a0, 0xA);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v;
        if (func_8012BEE8(a0) != 0 || v == 0) {
            *(s16 *)(a0 + 0x2) = 5;
        }
    }
}


extern u8 D_80196E10[];
extern void func_8012A828(s32 a0, void *a1);

void func_8017DB34(s32 a0) {
    *(s16 *)(a0 + 2) = 4;
    func_8012A828(a0, (void *)&(*(u8 *)D_80196E10));
    *(s32 *)(a0 + 0x1C) = rand() % 17 + 0x28;
    *(u16 *)(a0 + 0x52) = 0;
}



extern s32 func_8012BEE8(s32 arg);
    void func_8017DBA8(void *a0) {
        if (func_8012BEE8((s32)a0)) {
            *(s16 *)((u8 *)a0 + 0x2) = 0x5;
        }
    }


extern u8 D_80078E78[];
extern void (*D_80196F00[])(void *);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012B23C(s32 a0);

void func_8017DBDC(a0)
void *a0;
{
    s32 r;
    s32 rem;
    s32 h;
    s32 val;
    unsigned char *p;
    s32 pad[4];

    r = rand();
    p = D_80078E78;
    rem = r % 1024;
    h = *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
    if (rand() & 1) {
        val = h + rem;
    } else {
        val = h - rem;
    }
    *(s32 *)((s32)a0 + 0xE0) = val;
    func_8012B23C((s32)a0);
    func_8012A828((s32 *)a0, (s32)D_80196F00);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(s32 *)((s32)a0 + 0xE4) = 0;
    if (p[0x36] == 0) {
        *(s16 *)((s32)a0 + 2) = 7;
    } else {
        *(s16 *)((s32)a0 + 2) = 6;
    }
}


void func_8017DCA0(s32 arg0) {
    if (func_8012BD3C(arg0, 0x400, 0x20000) == 1) {
        if (func_8012BCCC(arg0) < 0x3001) {
            *(s16 *)(arg0 + 2) = 8;
            return;
        }
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) += func_8012B8E4(arg0, 8);
    } else {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) +=
            func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                          *(s32 *)(arg0 + 0xE0), 0xA);
    }
    func_8012B178(arg0, *(s32 *)(arg0 + 0xE8));
    func_8017ED6C(arg0, 0);
    if ((func_8017EB70(arg0) != 0) && (func_8012BEE8(arg0) != 0)) {
        func_8017EAC8(arg0);
    }
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017ED6C(s32 a0, s32 a1);
extern s32 func_8017EB70(s32 arg0);

void func_8017DD78(s32 arg0) {
    if (func_8012BDBC(arg0, 0x400) == 1) {
        if (func_8012BCCC(arg0) < 0x3001) {
            *(s16 *)(arg0 + 2) = 8;
            return;
        }
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) += func_8012B8E4(arg0, 4);
        func_8012B178(arg0, *(s32 *)(arg0 + 0xE8));
        func_8017ED6C(arg0, 1);
    } else {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) += func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), *(s32 *)(arg0 + 0xE0), 0xA);
        func_8012B178(arg0, *(s32 *)(arg0 + 0xE8));
        func_8017ED6C(arg0, 0);
    }
    func_8017EB70(arg0);
}


extern void func_8012A828(s32 a0, void * a1);
extern void func_8017EB04(s32 a0);
extern char D_80196FC0[];

void func_8017DE58(s32 a0)
{
    *(short *)(a0 + 0x2) = 0x9;
    func_8012A828(a0, &D_80196FC0);
    *(s32 *)(a0 + 0x1C) = 0x1E;
    func_8017EB04(a0);
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017DEA0;

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 func_8017E960();
extern void func_8017E888();
extern void func_8017E9CC(s32);
extern void func_8017EB04(s32 a0);

void func_8017DEA0(s32 a0) {
    s32 v;
    s32 flags;

    v = func_8012B8E4(a0, 0xA);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v;
    if ((*(s32 *)(a0 + 0xDC) & 0x20) != 0) {
        if ((u32)(*(s32 *)(a0 + 0x1C) - 10) < 0xD) {
            func_8017E960(a0);
        }
    } else {
        if (*(s32 *)(a0 + 0x1C) == 0x16) {
            func_8017E888(a0);
        }
        if (*(s32 *)(a0 + 0x1C) < 0x10) {
            ((void (*)(s32))func_8017E9CC)(a0);
        }
    }
    if (func_8012BEE8(a0) != 0) {
        flags = *(s32 *)(a0 + 0xDC);
        if (flags & 1) {
            *(s32 *)(a0 + 0xDC) = flags & 0xFFFFFFFE;
            *(s16 *)(a0 + 2) = 3;
        } else if (flags & 0x10) {
            *(s32 *)(a0 + 0xDC) = flags & 0xFFFFFFEF;
            *(s16 *)(a0 + 2) = 3;
        } else if (func_8012BD3C(a0, 0x400, 0x4000) == 0) {
            *(s16 *)(a0 + 2) = 5;
        } else {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            func_8017EB04(a0);
        }
    }
}



/* func_8017DFC8 — entity state-kick #0xB.
 * Sets the state word at 0x02 to 0xB, hands the entity to the script runner
 * func_8012A828 with table D_80196E10, clears bit 3 of the flag word at 0xDC,
 * then picks the timer at 0x1C: a fixed 30 when bit 6 was set (also clearing
 * bit 6), otherwise rand() % 16 + 15. Finally, if func_8012BD3C(e,0x400,0x8000)
 * returns 0, bit 3 at 0xDC is set again.
 *
 * §71 sibling-first: func_80184D28 (same TU, same D_80196E10 script table) is
 * the same `sh 0x2 / jal func_8012A828 / jal rand / sw 0x1C` skeleton and pins
 * the widths: `sh` at 0x02, `sw` at 0x1C/0xDC, and the s16 store scheduled into
 * the jal delay slot.
 */

extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

void func_8017DFC8(void *a0) {

    extern u8 D_80196E10[];
    s32 flags;
    s32 cleared;
    s32 timer;

    *(s16 *)((s32)a0 + 0x2) = 0xB;
    func_8012A828((s32)a0, D_80196E10);
    flags = *(s32 *)((s32)a0 + 0xDC);
    cleared = flags & ~8;
    *(s32 *)((s32)a0 + 0xDC) = cleared;
    if (flags & 0x40) {
        *(s32 *)((s32)a0 + 0xDC) = cleared & ~0x40;
        timer = 30;
    } else {
        timer = rand() % 16 + 15;
    }
    *(s32 *)((s32)a0 + 0x1C) = timer;
    if (func_8012BD3C((s32)a0, 0x400, 0x8000) == 0) {
        *(s32 *)((s32)a0 + 0xDC) |= 8;
    }
}


void func_8017E080(s32 a0) {
    s32 v;

    if ((*(s32 *)(a0 + 0xDC) & 8) != 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 0x44;
    } else {
        v = func_8012B8E4(a0, 8);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v;
        if (v == 0) {
            *(s16 *)(a0 + 2) = 5;
            return;
        }
    }
    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 2) = 5;
    }
}


extern void func_8017E888();

void func_8017E110(s32 a0) {
    *(s32 *)(a0 + 0xDC) &= ~0x10;
    func_8017E888(a0);
    *(s32 *)(a0 + 0x1C) = 0xA;
}




extern s32 func_8012BEE8(s32 arg);
    extern void func_8017E9CC(s32 arg);
    void func_8017E154(s32 arg0) {
        if (!func_8012BEE8(arg0)) {
            func_8017E9CC(arg0);
        }
    }




void func_8017E18C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x3;
        *(short *)((char *)a0 + 0xfe) = 0;
        *(unsigned short *)((char *)a0 + 0x5c) = 0xaa10;
        *(int *)((char *)a0 + 0xdc) &= ~0x10;
    }


void func_8017E1B4(void *a0)
{
    if (*(short *)((char *)a0 + 0x76) <= 0) {
        *(int *)((char *)a0 + 0xDC) |= 0x2;
    }
    *(int *)((char *)a0 + 0xE4) = 0;
    *(short *)((char *)a0 + 0x52) = -0x30;
}


extern void func_8017E888();
extern void func_8017E9CC(s32);

void func_8017E1E4(s32 arg0) {
    if (*(s32 *)(arg0 + 0x1C) == *(s32 *)(arg0 + 0x1C) / 5 * 5) {
        func_8017E888(arg0);
        *(s32 *)(arg0 + 0xE4) = 0xA;
    }
    if (*(s32 *)(arg0 + 0xE4) != 0) {
        func_8017E9CC(arg0);
        *(s32 *)(arg0 + 0xE4) -= 1;
    }
}


extern void func_8001C924(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801823FC(s32 a0, u16 *a1, s16 a2);

void func_8017E270(s32 param_1) {
    extern u8 D_80193CE4;
    extern u8 D_80193CF4;
    u16 arr[3];
    s32 temp;

    temp = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(temp + 0x24) == (s32)&D_80193CF4) {
        func_8001C924(temp, &D_80193CE4);
    }
    *(s32 *)(param_1 + 0x1C) = 0x18;
    *(s32 *)(param_1 + 0xDC) &= ~0x10;
    if (*(u16 *)(param_1 + 0x5E) == 0x23) {
        *(s16 *)(param_1 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (*(u16 *)(param_1 + 0x5E) == 0x24) {
        arr[0] = 0;
        arr[1] = 0x10;
        arr[2] = 0;
        func_801823FC(param_1, arr, 0);
    }
}



extern void func_8017E888();
extern void func_8017E9CC(s32);

void func_8017E328(s32 a0) {
    s32 v1;
    s32 v0;

    *(s32 *)(a0 + 0x1C) -= 1;
    if (*(s16 *)(a0 + 0xFE) != 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) += 0x40;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) += 0x40;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) += 0x40;
        v1 = *(s32 *)(a0 + 0x20);
        if (*(s16 *)(v1 + 0x18) >= 0x1800) {
            *(u16 *)(v1 + 0x1C) = 0x1800;
            *(u16 *)(v1 + 0x1A) = 0x1800;
            *(u16 *)(v1 + 0x18) = 0x1800;
        }
    }

    if (*(s32 *)(a0 + 0x1C) == 0xE) {
        func_8017E888(a0);
        v0 = 0xA;
    } else {
        if (*(s32 *)(a0 + 0xE4) == 0) {
            return;
        }
        func_8017E9CC(a0);
        v0 = *(s32 *)(a0 + 0xE4) - 1;
    }
    *(s32 *)(a0 + 0xE4) = v0;
}


void func_8017E418(s32 arg0, s32 arg1) {
    s32 t;

    arg1 = arg0;
    t = *(s16 *)(arg1 + 0xAA);
    *(s16 *)(arg1 + 0x5C) = 0;
    *(s16 *)(arg1 + 0x98) = 0;
    *(s32 *)(arg1 + 0x1C) = 0;
    if (t == 0) {
        s32 p = *(s32 *)(arg1 + 0x20);
        s32 v = *(s32 *)(arg1 + 0xDC);
        s32 u = *(u16 *)(p + 0x18);
        *(s32 *)(arg1 + 0xDC) = v & ~0x80;
        *(s16 *)(arg1 + 0x100) = u;
    } else {
        s32 p = *(s32 *)(arg1 + 0x20);
        s32 v = *(s32 *)(arg1 + 0xDC);
        s32 u = *(u16 *)(p + 0x18);
        *(s32 *)(arg1 + 0xDC) = v | 0x80;
        *(s16 *)(arg1 + 0x104) = u;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017E470;

// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @unstuck(P36): none - MATCH (41 ins), match_one + rtu_match.
// Three levers, in the order they mattered:
//  1) The `mult` sitting in BOTH branch arms is a dbr DELAY-SLOT STEAL from the
//     join block, not two multiplies in the source. The C selects the
//     MULTIPLICAND in the arms (`m`), and multiplies ONCE after the join.
//     That also makes the product a LOCAL allocno, so local-alloc coalesces
//     expand_divmod's `copy_to_mode_reg` temp away -> no `move v0,a0`, and the
//     bgez/addiu/shift all run in-place on $v0 (this was the whole 8-22 residual).
//  2) `srl` (not `sra`) for the /0x1000: the quotient's ONLY use must be a
//     narrowing store, i.e. hold it in an `s16 t`. combine's force_to_mode then
//     rewrites ASHIFTRT->LSHIFTRT because the high bits are discarded. Storing
//     `v / 0x1000` inline (2 SImode uses) keeps `sra`.
//  3) `m` must be `s32`, not `s16` - a narrow local costs lhu+sll+sra (loose
//     typing); the s32 local keeps the plain `lh`.
//  4) `p` and `q` are two SEPARATE variables so the reloaded 0x20 pointer lands
//     in $a0 rather than re-using $v1.

extern s32 func_8004787C(s32 a0);

void func_8017E470(s32 param_1) {

    extern s16 D_80126CE0;
    s32 v;
    s32 p;
    s32 q;
    s32 m;
    s16 t;

    v = func_8004787C(0x400 - (D_80126CE0 * 8));
    if (*(s16 *)(param_1 + 0xAA) == 0) {
        m = *(s16 *)(param_1 + 0x100);
    } else {
        m = *(s16 *)(param_1 + 0x104);
    }
    p = *(s32 *)(param_1 + 0x20);
    t = (v * m) / 0x1000;
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;
    q = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(q + 0x18) <= 0) {
        *(s16 *)(q + 0x1C) = 1;
        *(s16 *)(q + 0x18) = 1;
    }
}





void func_8017E514(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }



// @class: regalloc (WIDTH/li!=addu -> MATCH)
// @unstuck(P36): none — MATCH (58 ins), match_one + rtu_match. PIN-FREE (no register __asm__).
// Three levers, in the order they mattered:
//
//  1) The join block indexes every field off $a0, not $s0: the target COPIES the entity into $a0
//     at the TOP of the join block (`addu $a0,$s0,$zero`) and reads 0x5C/0x5E/0x60/0x62/0x20 off
//     that copy.  A naive `e = param_1;` at the join is deleted — cse.c's make_regs_eqv keeps the
//     PARAMETER as qty_first_reg, so canon_reg rewrites every use of `e` back to param_1 and the
//     copy dies.  Writing the copy at the end of the ARMS instead is worse (2 mismatches worse):
//     gcc hoists it above the inner `if` into the beqz delay slot and the arms then read off $a0.
//
//  2) THE LEVER: make the copy's variable ALSO the 0x20 pointer of the /4 arm.  make_regs_eqv only
//     lets the new pseudo take over the quantity when its live range escapes the cse basic block
//     AND outlives the param's last use.  Reusing `a` in the /4 arm (which sits *after* the join in
//     the insn stream, and whose last mention `sh $v0,0x18($a0)` comes after param_1's last mention
//     `lh $v0,0x100($s0)`) satisfies both clauses at once, so `a` becomes canonical, the copy
//     survives, and the block addresses off it.  The same reuse is what puts `lw $a0,0x20($s0)` /
//     `lh $v1,0x18($a0)` in the /4 arm in the target's register order — two separate locals there
//     give the mirrored $v1/$a0 pair (6 extra mismatches; verified).  The reuse must be paired with
//     the join-top copy: `a` shared but copied in the arm instead makes it a plain global allocno,
//     global.c hands it a callee-saved reg and the function grows an $s1 save/restore (60 ins).
//     A `register s32 a __asm__("$4")` pin also reaches 0 here (canon_reg bails on hard regs), but
//     the pin is unnecessary and would trip the §42e/§86 pin guard on the ×6 family remap.
//
//  3) Tail statement order is 0x5C, 0x60, 0x62, 0x5E — the 0x5E store must be LAST.  sched2 works
//     the ready list LIFO, so a 0x5E written third floats to the front of the block as
//     `li $v0,1 / sh $v0,0x5E` and steals $v0 from the 0x5C load-modify-store (9 mismatches).
//     Written last it sinks past `lhu $v0,0x12($v1)`, reuses the now-dead $v1 for its constant and
//     lands where the target has it.  (All 24 orderings byte-swept: only 5C-60-62-5E and
//     60-5C-62-5E reach 0.)
//
//  Widths: 0x100 is read at TWO widths on purpose — `u16` in the flag arm (target `lhu`) and `s16`
//  in the /4 arm (target `lh`); combine folds the extend into the load, so the cast at the use site
//  picks the opcode.  Ditto `|= 1` on the s16 0x5C field giving `lhu`.  §3-T4: both `beqz`es mean
//  the NON-zero arm falls through, i.e. `func_8012BEE8(..) != 0` and `flags & 0x80` are the
//  fall-through arms (Ghidra's seed for this address was a different function entirely).

extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_8017E524(s32 param_1) {
    s32 a;
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        if (*(s32 *)(param_1 + 0xDC) & 0x80) {
            p = *(s32 *)(param_1 + 0x20);
            *(s16 *)(p + 0x1C) = 0x1000;
            *(s16 *)(p + 0x18) = 0x1000;
            *(s32 *)(param_1 + 0xDC) &= ~0x80;
        } else {
            p = *(s32 *)(param_1 + 0x20);
            h = *(u16 *)(param_1 + 0x100);
            *(s16 *)(p + 0x1C) = h;
            *(s16 *)(p + 0x18) = h;
        }
        a = param_1;
        *(s16 *)(a + 0x5C) |= 1;
        *(s16 *)(a + 0x60) = 0;
        q = *(s32 *)(a + 0x20);
        *(s16 *)(a + 0x62) = *(u16 *)(q + 0x12) + 0x800;
        *(s16 *)(a + 0x5E) = 1;
        ((void (*)(s32, s32))func_80131E00)(a, 1);
    } else {
        a = *(s32 *)(param_1 + 0x20);
        x = *(s16 *)(a + 0x18);
        t = x + (*(s16 *)(param_1 + 0x100) - x) / 4;
        *(s16 *)(a + 0x1C) = t;
        *(s16 *)(a + 0x18) = t;
    }
}


extern u8 D_80195694;
extern u8 D_801972F8;
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8017E60C(s32 param_1) {
    *(s32 *)(param_1 + 0x1C) = 0x37;
    func_8001C924(*(s32 *)(param_1 + 0x20), &D_80195694);
    func_8012A828(param_1, &D_801972F8);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x62);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_8017EEA8(void*);
extern u16 D_800B99DA;

void func_8017E668(s32 a0) {
    s32 v0;
    u16 v2;

    // Check if *(s32*)(a0 + 0x1C) < 0x11
    if (*(s32*)(a0 + 0x1C) < 0x11) {
        s32 mask;
        s32 ptr;
        s32 val;

        mask = 0x80000000;
        ptr = *(s32*)(a0 + 0x20);  // Load pointer from a0+0x20
        val = *(s32*)(ptr + 0x4);  // Load value from pointer+4
        val ^= mask;               // XOR with mask
        *(s32*)(ptr + 0x4) = val;  // Store back
    }

    // Call func_8012BEE8 and check result
    v0 = func_8012BEE8(a0);
    if (v0 != 0) {
        // Load and mask D_800B99DA
        v2 = D_800B99DA & 0x1F;
        if (v2 == 0) {
            func_80130D48(a0);
        }
        ((void (*)(s32))func_8017EEA8)(a0);
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH (52 ins), iteration 1. Keys: (1) §3-T4 — Ghidra inverted the arms; the
//   target's `beqz $v0,.L8018589C` means the (flags&2)!=0 arm FALLS THROUGH, so write
//   `if (*(s32*)(p+0xDC) & 2) {A} else {B}`; (2) the 0x5C zero-store is unconditional (it sits in
//   the beqz delay slot), so it is the FIRST statement, above the if; (3) both `*(s32*)(p+0x20)`
//   reads in arm A are written as separate expressions — the intervening `sh` to 0x10 blocks CSE,
//   which is why the target reloads 0x20 twice; (4) the tail compare is `iVar1 <= 0x8FFF`, NOT
//   Ghidra's `< 0x9000`: 0x9000 does not fit the signed 16-bit `slti` immediate, so gcc
//   materialises the bound with `ori $v1,$zero,0x8FFF` and emits the operand-reversed
//   `slt $v1,$v1,$v0` + `bnez` over the 0x51F assignment (write the constant as 0x8FFF).
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001C924(s32 a0, void *a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_8017E6F0(s32 param_1) {

    extern u8 D_801973D8;
    extern u8 D_80195694;
    extern u8 D_801972F8;
    s32 iVar1;
    s32 uVar2;

    *(s16 *)(param_1 + 0x5C) = 0;
    if (*(s32 *)(param_1 + 0xDC) & 2) {
        *(s32 *)(param_1 + 0x1C) = 0x2D;
        func_8012A828(param_1, &D_801973D8);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            (*(u16 *)(param_1 + 0x62) + 0x800) & 0xFFF;
        *(s16 *)(param_1 + 0x52) = 0;
    } else {
        *(s32 *)(param_1 + 0x1C) = 0x37;
        func_8001C924(*(s32 *)(param_1 + 0x20), &D_80195694);
        func_8012A828(param_1, &D_801972F8);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x62);
    }
    iVar1 = func_8012BCCC(param_1);
    uVar2 = 0x520;
    if (iVar1 <= 0x8FFF) {
        uVar2 = 0x51F;
    }
    func_8002D4C8(uVar2, 0);
}


extern s32 func_8012BEE8(s32 a0);
extern u16 D_800B99DA;
extern void func_80130D48(s32 a0);
extern void func_8017EEA8(void*);

void func_8017E7C0(s32 a0)
{
    if ((*(s32 *)(a0 + 0xDC) & 0x2) != 0) {
        if (*(s32 *)(a0 + 0x1C) >= 0x15) {
            s32 p = *(s32 *)(a0 + 0x20);
            *(s16 *)(p + 0x10) = *(u16 *)(p + 0x10) - 0x1E;
        }
    }

    if (*(s32 *)(a0 + 0x1C) < 0x11) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) ^= 0x80000000;
    }

    if (func_8012BEE8(a0) != 0) {
        if ((D_800B99DA & 0x1F) == 0) {
            func_80130D48(a0);
        }
        ((void (*)(s32))func_8017EEA8)(a0);
    }
}


extern void func_80143BDC(u16*);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B0B4(u32 *a0, s32 a1, s32 a2);

void func_8017E888(s32 arg0) {
    s32 i;
    s32 q;
    u16 sp10[3];
    u32 buf[2];
    s32 v;
    u32 *bp;

    if (*(s16 *)(arg0 + 0xAA) <= 0) {
        for (i = 0; i < 20; i++) {
            bp = buf;
            func_8012B0B4(bp, rand() % 4096, 64);
            v = *(s32 *)buf;
            sp10[0] = *(u16 *)(arg0 + 0x6) + v;
            sp10[1] = *(u16 *)(arg0 + 0xA) - 0x60;
            sp10[2] = *(u16 *)(arg0 + 0xE) + (v >> 16);
            q = ((s32 (*)(u16 *))func_80143BDC)(sp10);
            if (q != 0) {
                *(u8 *)(*(s32 *)(q + 0xCC) + 0x27) = 0x5B;
            }
        }
        func_8002D4C8(0x521, 0);
    }
}


extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801920BC;

s32 func_8017E960(s32 param_1) {
    s32 v0;
    s32 v1;

    if ((*(s32 *)(param_1 + 0xDC) & 1) != 0) {
        return 0;
    }
    v0 = func_8012D5E4(param_1, (s32)&D_801920BC, (s32)&D_801920BC + 8, 0x13);
    if (v0 != 1) {
        return 0;
    }
    v1 = *(s32 *)(param_1 + 0xDC);
    v1 = v1 | 1;
    *(s32 *)(param_1 + 0xDC) = v1;
    return 1;
}


typedef struct {
    s32 a;
    s32 b;
} Pair_801B5E30_8017E9CC;

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8012BD14(s32 a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* §200 ALIAS ESCAPE (S56). The asm PROVES an s32 return -- every exit path writes $v0
 * (addu $v0,$zero,$zero at 0x80182828/0x8018283C/0x80182858; addiu $v0,$zero,1 at
 * 0x801828E8) -- but this TU already declares the symbol `void` at three sites, two of
 * them file-scope, with live callers. Only the LINK name has to agree: define the body
 * under a private C name carrying the real assembler name, and the existing void decls
 * stay valid for the callers. Same idiom as `extern void aF80137030(...) __asm__(...)`
 * already in ov_SC03_099/ov_SC06_008, applied to a DEFINITION rather than a decl. */
s32 aF8018280C(s32 a0) __asm__("func_8017E9CC");

s32 aF8018280C(s32 a0) {
    extern u16 D_80126B62;
    s16 diff[3];
    s16 pointA[3];
    s32 flags;

    if (*(u16 *)(a0 + 0x5E) == 0x1E) {
        return 0;
    }
    if ((*(s32 *)(a0 + 0xDC) & 0x10) != 0) {
        return 0;
    }
    if (((s32 (*)(s32))func_8012BD14)(a0) < 0x2401) {
        pointA[0] = D_80126B5E;
        pointA[1] = D_80126B62;
        pointA[2] = D_80126B66;

        diff[0] = pointA[0] - *(u16 *)(a0 + 0x6);
        diff[1] = pointA[1] - *(u16 *)(a0 + 0xA);
        diff[2] = pointA[2] - *(u16 *)(a0 + 0xE);

        VectorNormalSS(diff, diff);

        pointA[1] -= 0x20;
        func_8012F568(1, 0x2001, 0, 0, (s32)pointA, (s32)diff);

        flags = *(s32 *)(a0 + 0xDC);
        flags |= 0x10;
        *(s32 *)(a0 + 0xDC) = flags;
        return 1;
    }
    return 0;
}




extern s32 rand(void);
    void func_8017EAC8(s32 arg0) {
        if ((rand() & 1) != 0) {
            *(s16*)(arg0 + 0x2) = 0xA;
        } else {
            *(s16*)(arg0 + 0x2) = 0x3;
        }
    }


extern s32 func_8014CB1C(void);

void func_8017EB04(s32 a0) {
    if (func_8014CB1C() != 0) {
        *(s32 *)(a0 + 0xDC) |= 0x20;
    } else {
        if ((rand() & 1) != 0) {
            *(s32 *)(a0 + 0xDC) |= 0x20;
        } else {
            *(s32 *)(a0 + 0xDC) &= ~0x20;
        }
    }
}


/* func_8017EB70 (ov_SC03_107 / jr_801789AC) — 127 ins, match_one MATCH.
 *
 * "Chase/push-away" AI tick: read the actor's state word, bail on states 2 / 0x1A,
 * clamp two fields, then walk the 0x60-entry entity table at D_801202A0 (stride
 * 0x10C) looking for a nearby live neighbour and try to step this actor to a point
 * 0x61 units away from it (func_8012CEB0 is the collision/move probe).
 *
 * Provenance (cookbook §160g sibling search): the INNER half is the already-banked
 * func_8017E404 in src/ov_SC02_000/ov_SC02_000_jr_8017AE2C.c:4538 — same
 * ratan2->func_8012B0B4->`d = *(s32*)&buf`->out.vx/out.vz packed-offset idiom, same
 * SVEC in/out/buf stack order.  The OUTER counted walk is the in-TU banked
 * func_801822E4 (same file, :7772): `p = D_801202A0; for (i=0;i<0x60;i++)`.
 *
 * Three non-obvious levers, in the order the gate found them:
 *
 * 1. `lose:` INSIDE the 0x1A arm (cookbook §162g).  The target's `beqz $v0,
 *    .L8017EBDC` at 0x8017ECFC is a BACKWARD branch into a block emitted between the
 *    0x1A arm and the 0x2000 test.  Per §162g cross-jumping only ever emits FORWARD
 *    merges, so this edge can only be a source-level `goto`.  Putting the label
 *    after the arm's `return 0;` (C permits a goto into a block) reproduces the
 *    block order with zero extra jumps — no `if (0) {}` wrapper, no jump threading
 *    needed.
 *
 * 2. `bp` exists only to create a MOVABLE (cookbook §162e2).  `&buf` passed straight
 *    to func_8012B0B4 is expanded into the arg register in place, so scan_loop has
 *    nothing to hoist: the draft was 124 ins with only $s0-$s5 and no
 *    `addiu $s6,$sp,0x20` preheader hoist.  Naming it forces a pseudo, which becomes
 *    the second movable (after `arg0 + 4`), lands in $s6, and the preheader order
 *    falls out as body order: $s0, $s4, $s5, $s6, then the +0xE giv $s2.  (&in/&out
 *    stay unnamed — the target keeps THOSE inline as `addiu $a0,$sp,0x10` /
 *    `addiu $a1,$sp,0x18`.)   -3 ins -> 0.
 *
 * 3. `i++, p += 0x10C` in the FOR-INCREMENT, not `p += 0x10C;` as the last body
 *    statement.  The +0xE giv's increment is emitted adjacent to its biv ($s0), so
 *    body-tail `p += ...` gives [$s2++, $s4++] and the comma form gives the target's
 *    [$s4++, $s2++].  Last 2 mismatched instructions.
 *
 * INTEGRATION (§161c): every extern below except func_8017EEA8 is ALREADY declared
 * at file scope in src/ov_SC03_107/ov_SC03_107_jr_801789AC.c, identically —
 * D_801202A0 :338, func_8012ADE4 :349, func_8012B0B4 :361, func_8012B6D4 :382,
 * func_8012BC60 :397, func_8012CBA4 :452, func_8012CEB0 :458, func_80131E00 :562.
 * The whole extern block may be dropped on banking.  func_8012CBA4 is declared
 * `void` there and func_8012BC60/func_80131E00 take struct pointers, so all three
 * are reached through call-site function-pointer casts (codegen-neutral, §17a-1) —
 * verified MATCH both with those casts against loose `()` decls and against the TU's
 * exact struct-typed prototypes.  func_8017EEA8 has no decl in the TU (it is
 * INCLUDE_ASM at :6456), so its extern must be kept.  SVEC_EB70 is a fresh tag —
 * no collision in the TU.
 */
#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SVEC_EB70;

struct Vec;
struct S80131E00;

extern void func_8012CBA4(s32 a0);                 /* TU decl is void -> cast at call site */
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8017EEA8(void *a0);
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);

s32 func_8017EB70(s32 arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];
    SVEC_EB70 in;
    SVEC_EB70 out;
    SVEC_EB70 buf;
    s32 v;
    s32 d;
    s32 i;
    u8 *p;
    u16 px, pz;
    unsigned int *bp;

    v = ((s32 (*)(s32))func_8012CBA4)(arg0);
    if ((v & 0xFF) == 2) {
        ((void (*)(s32, s32))func_80131E00)(arg0, 0x12);
        return 0;
    }
    if ((v & 0xFF) == 0x1A) {
        func_8017EEA8((void *)arg0);
        return 0;
    lose:
        func_8012ADE4((u8 *)arg0);
        return 1;
    }
    if ((v & 0x2000) == 0) {
        func_8012ADE4((u8 *)arg0);
    }
    *(s32 *)(arg0 + 0xDC) &= ~0x40;
    if (*(s32 *)(arg0 + 0x14) > 0xFFFFF) {
        *(s32 *)(arg0 + 0x14) = 0x100000;
    }
    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(s32 *)(p + 0x58) != 0 && arg0 != (s32)p) {
            if (((s32 (*)(s32, s32))func_8012BC60)(arg0 + 4, (s32)(p + 4)) < 0x2400) {
                bp = (unsigned int *)&buf;
                func_8012B0B4(bp,
                              func_8012B6D4((s16 *)(arg0 + 4), (s16 *)(p + 4)), 0x61);
                d = *(s32 *)&buf;
                px = *(u16 *)(p + 6);
                out.vx = px;
                out.vy = *(u16 *)(p + 0xA);
                pz = *(u16 *)(p + 0xE);
                out.vz = pz;
                out.vx = px + d;
                out.vz = pz + (d >> 16);
                in.vx = *(u16 *)(arg0 + 0x3A);
                in.vy = *(u16 *)(arg0 + 0x3E);
                in.vz = *(u16 *)(arg0 + 0x42);
                if ((func_8012CEB0((s32)&in, (s32)&out, 0) & 0x2000) == 0) {
                    goto lose;
                }
                *(s16 *)(arg0 + 6) = out.vx;
                *(s16 *)(arg0 + 0xA) = out.vy;
                *(s16 *)(arg0 + 0xE) = out.vz;
                break;
            }
        }
    }
    return 1;
}



extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

s32 func_8017ED6C(s32 a0, s32 a1) {
    s32 sp10[3];
    s32 sp20[3];
    s16 buf[8];

    sp20[1] = 0;
    sp20[0] = 0;
    sp20[2] = 0xFFF80000;

    func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp20, (s32)sp10);

    buf[0] = *(u16 *)(a0 + 0x3A);
    buf[1] = *(u16 *)(a0 + 0x3E);
    buf[2] = *(u16 *)(a0 + 0x42);

    sp10[0] = sp10[0] + *(s32 *)(a0 + 0x44);
    sp10[1] = sp10[1] + *(s32 *)(a0 + 0x48);
    sp10[2] = sp10[2] + *(s32 *)(a0 + 0x4C);

    sp10[0] = sp10[0] + *(s32 *)(a0 + 0x4);
    sp10[1] = sp10[1] + *(s32 *)(a0 + 0x8);
    sp10[2] = sp10[2] + *(s32 *)(a0 + 0xC);

    buf[4] = *(u16 *)((s32)sp10 + 0x2);
    buf[5] = *(u16 *)((s32)sp10 + 0x6);
    buf[6] = *(u16 *)((s32)sp10 + 0xA);

    func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0);

    if (*(s16 *)(a0 + 0xA) > *(s16 *)&buf[5]) {
        *(s32 *)(a0 + 0xE8) = 0xFFF80000 - (a1 << 19);
        return 1;
    } else {
        *(s32 *)(a0 + 0xE8) = 0xFFFE0000 - (a1 << 17);
        return 0;
    }
}


#include "common.h"

extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C218(void *a0);

void func_8017EEA8(void *a0)
{
    s32 v1;

    if (*(short *)((char *)a0 + 0x102) == 0) {
        func_8002A04C((s32)a0);
        func_8002AC00(0x1A);
    }

    if (!((*(short *)((char *)a0 + 0x70) & 0x8000))) {
        v1 = *(s32 *)((char *)a0 + 0x68);
        if (v1 != 0 && ((*(short *)((char *)a0 + 0x72) & 0x8000))) {
            *(unsigned short *)(v1 + 0xA) = *(unsigned short *)(v1 + 0xA) & 0x7FFF;
        }
    }

    func_8012C218(a0);
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012C1B8(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);


void func_8017EF3C(void *a0v)
{

    extern u8 D_801973F8[];
    extern u8 D_80198828[];
    extern u8 D_801974CC[];
    extern u8 D_80197498[];
    extern u8 D_8019BA48[];
    extern u8 D_8019742C[];
    extern u8 D_80197438[];
    extern u8 D_80197440[];
    extern u8 D_80197450[];
    extern u16 D_80197454;
    extern u8 D_80197458[];
    extern u8 D_80197464[];
    extern u8 D_8019746C[];
    extern u8 D_80197490[];
    extern u16 D_80197494;
    extern u8 D_8019747C[];
    extern u8 D_80197488[];
    extern u8 D_8019BA89;
    extern u8 D_8019BA8A;
    extern u8 D_8019BA8C;
    s32 e;
    s32 r;
    s32 o;
    s32 cc;
    s32 sv;
    u8 *p;
    u8 *q;

    e = (s32)a0v;

    switch (*(s16 *)(e + 0x70)) {
    case 0:
        if (func_8012C354(e, (s32)D_801973F8) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801974CC;
        func_8012A828(e, D_80198828);
        *(s16 *)(e + 0x2) = 1;
        *(s16 *)(e + 0x34) = 1;
        func_8012B23C(e);
        func_8012B1B4(e, (s32)D_80197498);
        *(s32 *)(e + 0xCC) = (s32)(D_8019BA48 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 1, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 1:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_8019742C);
        func_8012A828(e, D_80197438);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_80197440 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197450;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197454;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 2, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_80197458);
        func_8012A828(e, D_80197464);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_8019746C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197490;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197494;
        return;

    case 7:
        if (func_8012C354(e, (s32)D_801973F8) == 0) {
            return;
        }
        p = &D_8019BA89;
        q = p - 1;
        D_8019BA8A = 0xFF;
        *q = 0xFF;
        *p = 0;
        D_8019BA8A = 0;
        D_8019BA8C = 0;
        func_800233CC(q, 0x20);
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801974CC;
        func_8012A828(e, D_80198828);
        *(s16 *)(e + 0x2) = 8;
        *(s16 *)(e + 0x34) = 0xB;
        func_8012B23C(e);
        sv = *(s16 *)(e + 0xFC);
        *(s16 *)(e + 0xFC) = 0;
        *(s32 *)(e + 0xCC) = (s32)(D_8019BA48 + sv * 8);
        o = func_8012C658(0x1EA, 8, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 8:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_8019742C);
        func_8012A828(e, D_80197438);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_80197440 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197450;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197454;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 9, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_80197458);
        func_8012A828(e, D_80197464);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_8019746C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197490;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197494;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 14:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_8019747C);
        func_8012A828(e, D_80197488);
        *(s16 *)(e + 0x2) = 0xC;
        *(u16 *)(*(s32 *)(e + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x10);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x12);
        *(s32 *)(e + 0x14) = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x10)) << 9;
        {
            s32 t1 = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x10) = -((t1 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        {
            s32 t2 = func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x18) = -((t2 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        *(s32 *)(e + 0x10) = (*(s32 *)(e + 0x10) * 2) / 3;
        *(s32 *)(e + 0x1C) = 0x12C;
        *(s32 *)(e + 0x14) = (*(s32 *)(e + 0x14) * 2) / 3;
        *(s32 *)(e + 0x18) = (*(s32 *)(e + 0x18) * 2) / 3;
        return;

    case 15:
        if (func_8012C354(e, (s32)D_801973F8) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801974CC;
        func_8012A828(e, D_80198828);
        *(s16 *)(e + 0x2) = 0xD;
        *(s16 *)(e + 0x34) = 0xD;
        func_8012B23C(e);
        *(s32 *)(e + 0xCC) = (s32)(D_8019BA48 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 0x11, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(s16 *)(e + 0xFC) = 0xA;
        return;

    case 16:
    case 24:
        *(s16 *)(e + 0x2) = 0xE;
        *(s32 *)(e + 0x1C) = 6;
        return;

    case 17:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_8019742C);
        func_8012A828(e, D_80197438);
        *(s16 *)(e + 0x2) = 0x11;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_80197440 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197450;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197454;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 0x12, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        r = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_80197458);
        func_8012A828(e, D_80197464);
        *(s16 *)(e + 0x2) = 0x10;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_8019746C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_80197490;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_80197494;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 25:
        *(s16 *)(e + 0x2) = 0x13;
        return;
    }
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

void func_8017F6E8(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 1 || *(s16 *)(a0 + 0x70) == 8) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(u32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) & 0x80000000) {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
    } else {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) &= ~0x80000000;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x70) < 8) {
        *(s16 *)(a0 + 0x108) = (*(u16 *)(a0 + 0x108) + 0x40) & 0xFFF;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) & 0xFFF;

        flag = *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) -
               *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        if (flag > 0x800) {
            flag = flag - 0x1000;
        }
        if (flag < -0x800) {
            flag = flag + 0x1000;
        }
        if (flag > 0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) - 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else if (flag < -0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + (flag / 16);
        }

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) +
            (func_8004787C(*(s16 *)(a0 + 0x108)) >> 6);

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
        out[1] = out[1] - 0x40;

        pos[0] = *(u16 *)(a0 + 6);
        pos[1] = *(u16 *)(a0 + 0xA) + 0x10;
        pos[2] = *(u16 *)(a0 + 0xE);
        flag = func_8012CEB0((s32)out, (s32)pos, 1);
        if (flag & 0x1000) {
            return;
        }
        if (flag != 0) {
            s32 d;
            s32 t = pos[1] - 0x10;
            d = *(s16 *)(a0 + 0xA) - t;
            if (d < 5) {
                return;
            }
            if (d > 0x40) {
                d = 0x40;
            }
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + (d << 4);

            func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
            gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
            gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

            p = *(s16 **)(a0 + 0xD0);
            sv[0] = 0;
            sv[1] = 0;
            sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
            RotTransSV(sv, out, &flag);

            *(s16 *)(a0 + 6) = out[0];
            *(s16 *)(a0 + 0xA) = out[1];
            *(s16 *)(a0 + 0xE) = out[2];
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x80;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) & 0xFFF;
            if ((u32)(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x801) < 0x3FF) {
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00;
            }
        }
    } else {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 6;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) = func_80047948(ang2) >> 6;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + 0xC00;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
}



extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012CC40(s32 arg0, s32 arg1);   /* fleet-canonical: void; $v0 used -> cast at call site */

void func_8017FCF0(s32 a0)
{
    extern u8 D_80197498[];
    extern s32 D_801974B4;

    s16 pos1[4];
    s16 pos2[4];
    s32 s1;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;
    func_8012B1B4(a0, (s32)D_80197498);

    {
        s16 *p1 = pos1;
        s16 *p2 = pos2;
        s32 x, y, z;

        x = *(u16 *)(a0 + 0x6);
        p2[0] = x;
        p1[0] = x;
        y = *(u16 *)(a0 + 0xA);
        p2[1] = y;
        p1[1] = y;
        z = *(u16 *)(a0 + 0xE);
        p2[1] = y + 0x40;
        p2[2] = z;
        p1[2] = z;
        s1 = func_8012CEB0((s32)p1, (s32)p2, 1);
    }

    if (s1 & 0x6000) {
        if (!(s1 & 0x1000)) {
            s1 = func_8012BCCC(a0);
            if (s1 < 0x4001) {
                if (func_8012BDBC(a0, 0x200) == 1) {
                    *(s16 *)(a0 + 0x2) = 4;
                    *(s16 *)(a0 + 0xFC) = 0;
                    *(s16 *)(a0 + 0x100) = *(u16 *)(a0 + 0xA);
                }
            }
        }
    }
    if (s1 > 0x40000) {
        *(s16 *)(a0 + 0x2) = 1;
    }

    if ((((s32 (*)(s32, s32))func_8012CC40)(a0, (s32)&D_801974B4) & 0x1000) != 0) {
        *(s16 *)(a0 + 0x2) = 0x12;
    }
}



void func_8017FE24(s32 e) {

    extern u8 D_80197498[];
    extern void func_8012C218(void *a0);
    extern void func_8012CC64(s32, s32);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern void func_8012E688(s32, u16, u16);
    extern void func_8012B23C(s32 a0);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32 rand(void);
    extern s32 D_801974B4;

    s32 p;
    s32 n;
    s32 dir;

    if (--*(s16 *)(e + 0xFC) == 0) {
        n = 0;
        p = e;
        do {
            p = *(s32 *)(p + 0x6C);
            n++;
        } while (p != 0);
        if (n < 7) {
            p = e;
            while (p != 0) {
                s32 next = *(s32 *)(p + 0x6C);
                func_8012C218((void *)p);
                p = next;
            }
            return;
        }
    }

    {
        s32 f;

        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) += 0x40;
        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) &= 0xFFF;
        f = ((s32 (*)(s32, void *))func_8012CC64)(e, &D_801974B4);

        if (f & 0x1000) {
            *(s16 *)(e + 0x2) = 0x12;
            return;
        }

        n = 0;
        if (f & 0xC000) {
            s16 p1[3];
            s16 p2[3];

            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
                x = *(u16 *)(e + 6);
                p1[0] = x - 0x20;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE) + 0x20;
                p1[2] = z;
                q[0] = x + 0x20;
                q[1] = y;
                q[2] = z;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    *(s16 *)(e + 0x12) = -(rand() & 3) - 4;
                    n = 1;
                } else {
                    q[0] = p1[0] + 0x40;
                    q[1] = p1[1];
                    q[2] = p1[2];
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        *(s16 *)(e + 0x12) = (rand() & 3) + 4;
                        n = 2;
                    }
                }
            }
            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                x = *(u16 *)(e + 6);
                p1[0] = x;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE);
                p1[2] = z;
                q[0] = x;
                q[1] = y;
                q[2] = z + 0x40;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    *(s16 *)(e + 0x1A) = -(rand() & 3) - 4;
                    n += 4;
                } else {
                    q[0] = p1[0];
                    q[1] = p1[1];
                    q[2] = p1[2] + 0x40;
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        *(s16 *)(e + 0x1A) = (rand() & 3) + 4;
                        n += 8;
                    }
                }
            }

            switch (n - 1) {
            case 0:
                dir = 0x800;
                break;
            case 1:
                dir = 0;
                break;
            case 3:
                dir = 0x400;
                break;
            case 4:
                dir = 0x600;
                break;
            case 5:
                dir = 0x200;
                break;
            case 7:
                dir = 0xC00;
                break;
            case 8:
                dir = 0xA00;
                break;
            case 9:
                dir = 0xE00;
                break;
            }
            *(s16 *)(*(s32 *)(e + 0x20) + 0x12) = dir;
        } else if (f & 0x2000) {
            ((void (*)(s32, s32, s32))func_8012E688)(e, 0x833, 0);
            if ((rand() & 0xF) == 0) {
                s32 t1;
                s32 t2;
                s32 t3;

                *(s16 *)(*(s32 *)(e + 0x20) + 0x14) = 0;
                t1 = *(u16 *)(e + 6);
                t2 = *(u16 *)(e + 0xA);
                t3 = *(u16 *)(e + 0xE);
                *(s16 *)(e + 0x2) = 1;
                *(s16 *)(e + 0x34) = 1;
                *(s16 *)(e + 0x70) = 0;
                *(s16 *)(e + 0x88) = t1;
                *(s16 *)(e + 0x8A) = t2;
                *(s16 *)(e + 0x8C) = t3;
                func_8012B23C(e);
                func_8012B1B4(e, (s32)&D_80197498);
                p = *(s32 *)(e + 0x6C);
                if (p != 0) {
                    do {
                        *(s16 *)(p + 0x2) = 2;
                        *(s16 *)(p + 0x70) -= 0x10;
                        *(s16 *)(*(s32 *)(p + 0x20) + 0x14) = 0;
                        p = *(s32 *)(p + 0x6C);
                    } while (p != 0);
                }
                *(s16 *)(e + 0xFC) = 0;
            } else {
                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
            }
        }
    }

    if (*(s16 *)(e + 0xA) >= 0x65) {
        func_8012C218((void *)e);
    }
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801801E4(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 0x11) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(u32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) & 0x80000000) {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
    } else {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) &= ~0x80000000;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x14);

    {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 3;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_80047948(ang2) >> 3;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
}


extern void (*D_801974FC[])(void);
extern void func_80049CAC(s32 a0, s32 a1);

    void func_80180428(void *a0) {
        D_801974FC[*(u16 *)(a0 + 2)]();
        if (*(u16 *)a0 != 0) {
            if ((*(s16 *)(a0 + 0x70)) == 0 || (*(s16 *)(a0 + 0x70)) == 7) {
                func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
            }
            if ((*(s16 *)(a0 + 0x70)) == 0xF) {
                func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
            }
            func_8012B260((u8 *)a0);
        }
    }



extern u8 *func_8012913C(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_801292C8(u8 *a0);

typedef struct {
    u16 x, y, z;
    u8 flag;
} V8_80187968_801804D8;

void func_801804D8(s32 a0) {
    u32 v0;
    u8 *s1;

    v0 = *(u16 *)(a0 + 0x10A) + 1;
    *(u16 *)(a0 + 0x10A) = v0;

    if ((v0 & 7) == 0) {
        s1 = func_8012913C(0x7B);
        if (s1 != 0) {
            V8_80187968_801804D8 p1;
            V8_80187968_801804D8 q;

            v0 = *(u16 *)(a0 + 0x10A);
            *(s32 *)(s1 + 0x2C) = (v0 & 0x18) >> 3;

            p1.x = *(u16 *)(a0 + 0x6);
            p1.y = *(u16 *)(a0 + 0xA);
            p1.z = *(u16 *)(a0 + 0xE);
            q.x = p1.x;
            q.y = p1.y + 0x80;
            q.z = p1.z;

            func_80133784(1, &p1, (s32)&q);

            if (q.flag) {
                *(u16 *)(s1 + 0x6) = *(u16 *)(a0 + 0x6);
                *(u16 *)(s1 + 0xA) = q.y;
                *(u16 *)(s1 + 0xE) = *(u16 *)(a0 + 0xE);
            } else {
                func_801292C8(s1);
            }
        }
    }
}




void func_801805BC(void *a0) {

    extern void (*D_8019754C[])(void);
    D_8019754C[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 *func_8012913C(s32 a0);
extern u8 D_8019BA88[];
extern void func_8001CD50(s32 a0, s32 a1);

void func_801805F8(a0)
s32 a0;
{
    extern u8 D_8019BA88[];
    u8 pad[16];
    u8 *result;

    result = func_8012913C(0x7C);
    if (result != 0) {
        *(u16 *)(result + 0x6) = *(u16 *)(a0 + 0x6);
        *(u16 *)(result + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(result + 0xE) = *(u16 *)(a0 + 0xE);
        func_8001CD50(*(s32 *)(result + 0x20), (s32)D_8019BA88);
    }
}


void func_8018065C(void *a0) {
    extern s32 D_801151D4;
    extern void (*D_80197554[])(void *);
    s16 in[8];
    s32 out[2];
    s32 s0 = (s32)a0;
    s32 v1 = D_801151D4;
    s32 t;

    in[1] = *(s32 *)(v1 + 0x5C);
    in[3] = *(s32 *)(v1 + 0x60);
    in[5] = *(s32 *)(v1 + 0x64);
    func_8012B77C((s32)out, s0 + 4, (s32)in);
    t = out[0];
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = t;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = t >> 16;
    D_80197554[*(u16 *)(s0 + 2)](a0);
}



extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012B23C(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);

void func_801806F0(s32 a0)
{
    extern u8 D_80197498[];
    u16 out[4];
    u16 pos[4];
    u16 t0, t1, t2;

    *(u16 *)(a0 + 0x5C) = 0xA810;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x34);

    t0 = *(u16 *)(a0 + 0x6);
    pos[0] = t0;
    out[0] = t0;
    t1 = *(u16 *)(a0 + 0xA);
    pos[1] = t1;
    out[1] = t1 - 0x18;
    t2 = *(u16 *)(a0 + 0xE);
    pos[2] = t2;
    out[2] = t2;
    func_8012CEB0((s32)out, (s32)pos, 1);

    *(u16 *)(a0 + 0xA) = pos[1] - 0x10;

    if (*(s16 *)(a0 + 0x70) == 0xF) {
        s32 c;

        c = *(s32 *)(a0 + 0x20);
        *(u16 *)(c + 0x14) = 0;

        *(u16 *)(a0 + 0x2) = 1;
        *(u16 *)(a0 + 0x34) = 1;
        *(u16 *)(a0 + 0x70) = 0;
        *(u16 *)(a0 + 0x88) = *(u16 *)(a0 + 0x6);
        *(u16 *)(a0 + 0x8A) = *(u16 *)(a0 + 0xA);
        *(u16 *)(a0 + 0x8C) = *(u16 *)(a0 + 0xE);
        func_8012B23C(a0);
        func_8012B1B4(a0, (s32)D_80197498);

        {
            s32 n = *(s32 *)(a0 + 0x6C);
            while (n != 0) {
                *(u16 *)(n + 0x2) = 2;
                *(u16 *)(n + 0x70) = *(u16 *)(n + 0x70) - 0x10;
                *(u16 *)(*(s32 *)(n + 0x20) + 0x14) = 0;
                n = *(s32 *)(n + 0x6C);
            }
        }
        *(u16 *)(a0 + 0xFC) = 0;
    } else {
        func_8012B23C(a0);
        func_8012B1B4(a0, (s32)D_80197498);
    }
}



extern void func_8012E688(s32, u16, u16);
    void func_80180818(void *a0) {
        if (*(s16 *)((s32)a0 + 0x76) > 0) {
            ((void (*)(s32, s32, s32))func_8012E688)((s32)a0, 0x8C6, 0);
        }
    }






extern void func_8012E688(s32, u16, u16);
    extern void func_8002AC00(s32 arg0);
    void func_80180848(void *arg0) {
        ((void (*)(s32, s32, s32))func_8012E688)((s32)arg0, 0x8C7, 0);
        func_8002AC00(0x10);
    }


void func_80180874(void) {
}


void func_8018087C(s32 a0)
{
    extern void func_8012BE98(s32 a0, u16 *a1);
    extern s32  func_8012B744(void *a0, void *a1);
    extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
    extern void func_8012CC40(s32 arg0, s32 arg1);
    extern s32  func_8012C0EC(s32 a0);
    extern u8   D_80197498[];
    extern s32  D_801974B4;

    s32 anim = a0 + 0x88;

    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim) >= 0x4000) {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), (void *)anim), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        func_8012B1B4(a0, (s32)D_80197498);
    } else {
        if (func_8012BD3C(a0, 0x200, 0x40000) == 1) {
            *(s16 *)(a0 + 0x2) = 3;
        }
    }

    if ((((s32 (*)(s32, s32))func_8012CC40)(a0, (s32)&D_801974B4) & 0x1000) != 0) {
        *(s16 *)(a0 + 0x2) = 0x12;
    } else {
        func_8012C0EC(a0);
    }
}


extern s32 func_8004787C(s32 a0);
extern void func_8012E688(s32, u16, u16);

void func_80180968(s32 a0)
{
    *(u16 *)(a0 + 0xFC) += 0x20;
    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x100);
    *(s32 *)(a0 + 0x8) -= func_8004787C(*(s16 *)(a0 + 0xFC)) << 10;

    if (*(s16 *)(a0 + 0xFC) >= 0x400) {
        *(s16 *)(a0 + 0x2) = 5;
        *(s16 *)(a0 + 0xFE) = 4;
        func_8012E688(a0, 0x98F, 0);
    }
}


extern s32 D_801974A4;
extern s32 D_801974AC;
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

    void func_801809E8(s32 a0)
    {
        s32 val;
        *(s32*)(a0 + 0x8) += 0x100000;
        val = func_8004787C(*(s16*)(*(s32*)(a0 + 0x20) + 0x12));
        *(s32*)(a0 + 0x4) -= val << 8;
        val = func_80047948(*(s16*)(*(s32*)(a0 + 0x20) + 0x12));
        *(s32*)(a0 + 0xC) -= val << 8;
        if (--*(s16*)(a0 + 0xFE) == 0) {
            *(s16*)(a0 + 0x2) = 6;
            func_8012D5E4(a0, (s32)&D_801974A4, (s32)&D_801974AC, 0xF);
            *(s16*)(a0 + 0xFE) = 8;
        }
    }



extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012E688(s32, u16, u16);

void func_80180A9C(s32 a0)
{
    *(s32 *)(a0 + 0x8) -= 0x80000;
    *(s32 *)(a0 + 0x4) += func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7;
    *(s32 *)(a0 + 0xC) += func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7;

    if (--*(s16 *)(a0 + 0xFE) == 0) {
        if (func_8012BCCC(a0) < 0x4001) {
            if (func_8012BDBC(a0, 0x200) == 1) {
                *(s16 *)(a0 + 0x2) = 5;
                *(s16 *)(a0 + 0xFE) = 4;
                ((void (*)(s32, s32, s32))func_8012E688)(a0, 0x98F, 0);
            } else {
                *(s16 *)(a0 + 0x2) = 7;
            }
        } else {
            *(s16 *)(a0 + 0x2) = 7;
        }
    }
}


extern int func_8004787C(int a0);

void func_80180B7C(a0)
void *a0;
{
    *(u16 *)((s32)a0 + 0xFC) += 0x20;
    *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a0 + 0x100);
    *(s32 *)((s32)a0 + 8) -= func_8004787C(*(s16 *)((s32)a0 + 0xFC)) << 10;
    if (*(s16 *)((s32)a0 + 0xFC) >= 0x800) {
        *(u16 *)((s32)a0 + 2) = 3;
    }
}


    extern s32 func_8012BCCC(s32 a0);
    void func_80180BE4(s32 a0) {
        s16 v = *(s16 *)(a0 + 0xFC);
        if (v != 0) {
            *(s16 *)(a0 + 0xFC) = v - 1;
        } else if (func_8012BCCC(a0) <= 0xFFFFF) {
            *(s16 *)(a0 + 0x2) = 0x9;
        }
    }


extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern void func_801804D8(s32);

void func_80180C44(void *a0) {
    extern u8 D_80126B5C;
    s32 d;
    u16 t;

    func_8012B77C((s32)&d, (s32)a0 + 4, (s32)&D_80126B5C);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = d >> 16;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = d;
    t = *(u16 *)((s32)a0 + 0xA);
    t = t - 8;
    *(u16 *)((s32)a0 + 0xA) = t;
    if (*(s16 *)((s32)a0 + 0x8A) - (s16)t >= 0x81) {
        *(s16 *)((s32)a0 + 2) = 0xA;
        *(s16 *)((s32)a0 + 0xFC) = 0xC;
    }
    func_801804D8((s32)a0);
}


extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801804D8(s32);

void func_80180CD4(void *a0) {
    s16 v = *(u16 *)((s32)a0 + 0xFC) - 1;
    *(u16 *)((s32)a0 + 0xFC) = v;
    if (v == 0) {
        *(u16 *)((s32)a0 + 2) = 0xB;
    }
    if (*(s16 *)((s32)a0 + 0xFC) == 6) {
        func_8012C658(0x1EA, 0xE, (s32)a0);
        func_8002D4C8(0xC5D, 0);
    }
    ((void (*)(void *))func_801804D8)(a0);
}


extern void func_801804D8(s32);

void func_80180D48(a0)
void *a0;
{
    u16 w;

    w = *(u16 *)(a0 + 0xA) + 8;
    *(u16 *)(a0 + 0xA) = w;
    if (*(s16 *)(a0 + 0x8A) - (s16)w <= 0) {
        *(s16 *)(a0 + 2) = 8;
        *(s16 *)(a0 + 0xFC) = 0x1E;
    }
    func_801804D8((s32)a0);
}


extern s32 D_801974BC;
extern s32 D_801974C4;
extern void func_8012CBF4(s32);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012C218(void *a0);
extern void func_801805F8(s32 a0);

void func_80180D98(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012CBF4)();
    if (v0 != 0) {
        ((void (*)(s32))func_8012C218)(param_1);
        return;
    }

    v0 = func_8012D5E4(param_1, (s32)&D_801974BC, (s32)&D_801974C4, 0xF);
    if (v0 == 1) {
        ((void (*)(s32))func_8012C218)(param_1);
        return;
    }

    v0 = *(s32 *)(param_1 + 0x1c);
    v0 = v0 - 1;
    *(s32 *)(param_1 + 0x1c) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    } else {
        func_801805F8(param_1);
    }
}


extern void func_8012BE54(s32);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_80180E18(void *a0) {
    s32 e = (s32)a0;
    s32 o;

    if (((s32 (*)(s32))func_8012BE54)(e) > 0x23FFFF) {
        return;
    }
    if (--*(s32 *)(e + 0x1C) != 0) {
        return;
    }
    o = func_8012C658(0x1EA, 0xF, e);
    *(s32 *)(e + 0x1C) = (rand() & 0x1F) + 0x2D;
    if (*(s16 *)(e + 0x70) == 0x18 && o != 0) {
        *(u16 *)(*(s32 *)(o + 0x20) + 0x12) = 0x400;
    }
}



extern int func_8012C658(int arg0, int arg1, int arg2);
extern void func_8017F6E8(int a0);

void func_80180EB8(int a0)
{
    short cnt;
    int v1;

    *(short *)(a0 + 0x2) = 2;
    cnt = *(unsigned short *)(a0 + 0x70) + 1;
    *(unsigned short *)(a0 + 0x70) = cnt;

    if (cnt < 7) {
        v1 = func_8012C658(0x1EA, cnt, a0);
        if (v1 != 0) {
            *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            *(unsigned short *)(v1 + 0x108) = (*(unsigned short *)(a0 + 0x70) - 1) << 9;
        }
    }

    cnt = *(short *)(a0 + 0x70);
    if (cnt >= 8) {
        if (cnt < 14) {
            v1 = func_8012C658(0x1EA, cnt, a0);
            if (v1 != 0) {
                *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            }
        }
    }

    *(unsigned short *)(a0 + 0x70) = *(unsigned short *)(a0 + 0x70) - 1;
    func_8017F6E8(a0);
}




extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80180F88(int a0)
{
    short cnt;
    int v1;

    *(short *)(a0 + 0x2) = 0x11;
    cnt = *(unsigned short *)(a0 + 0x70) + 1;
    *(unsigned short *)(a0 + 0x70) = cnt;

    if (cnt < 0x17) {
        v1 = func_8012C658(0x1EA, cnt, a0);
        if (v1 != 0) {
            *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            *(s32 *)(a0 + 0x6C) = v1;
            *(unsigned short *)(v1 + 0x108) = (*(unsigned short *)(a0 + 0x70) - 0x11) << 9;
        }
    }

    *(unsigned short *)(a0 + 0x70) = *(unsigned short *)(a0 + 0x70) - 1;
    func_801801E4(a0);
}




















extern void func_8012C218(void *a0);
void func_8018101C(void *a0)
{
s32 v0;
s32 v1;
  v0 = (*((s32 *) (((s32) a0) + 0x8)) = (*((s32 *) (((s32) a0) + 0x8))) + 0x40000);
  v1 = 0x400000;
  if (v1 < v0)
  {
    v1 = v1 / 65536;
    ((s32 (*)(s32)) func_8012C218)((s32) a0);
  }
}




extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_80181058(void *a0)
{

    extern u8 D_801202A0[];
    u8 *p;
    s32 cnt;
    s32 i;
    s16 st;
    s32 q;
    s16 t;

    p = D_801202A0;
    cnt = 0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x1EA) {
            st = *(s16 *)(p + 0x70);
            if (st == 0 || st == 7 || st == 0xF) {
                cnt++;
            }
        }
        p += 0x10C;
    }

    if (cnt < 2) {
        p = (u8 *)func_8012C658(0x1EA, 0, (s32)a0);
        if (p != 0) {
            t = rand() & 0xFFF;
            q = *(s32 *)(p + 0x20);
            *(u16 *)(q + 0x12) = t;
            {
                s32 rr = rand() & 0x7F;
                s32 xx = *(u16 *)(p + 0x6) - 0x40;
                *(u16 *)(p + 0x6) = xx + rr;
            }
            {
                s32 rr = rand() & 0x7F;
                s32 xx = *(u16 *)(p + 0xE) - 0x40;
                *(u16 *)(p + 0xE) = xx + rr;
            }
        }
    }
}





extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);

void func_80181140(void *a0)
{

    extern u8 D_8019BAC8[];
    s32 s1;
    u8 *p;

    s1 = *(s32 *)((s32)a0 + 0x20);
    p = D_8019BAC8 + *(s32 *)((s32)a0 + 0x2C) * 0x40;
    func_8001CD50(s1, (s32)p);
    *(s16 *)(s1 + 0x1E) = 0xCCC;
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x1A) = 0;
    *(s16 *)(s1 + 0x18) = 0;
    *(s32 *)(s1 + 4) = *(s32 *)(s1 + 4) | 0x50000000;
    func_800233CC(p, 0x80);
    p[2] = 0xFF;
    p[1] = 0xFF;
    p[0] = 0xFF;
    p[5] = 0x40;
    p[4] = 0x40;
    p[6] = 0x80;
    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
}






/* Declaration reconciliation with src/ov_SC03_118/ov_SC03_118_jr_8017FB84.c:
 *  - D_8019BAC8: the TU already declares it at line 4526 as `extern u8 D_8019BAC8[];`
 *    (used by the banked func_801885D0 just above the splice point). The draft had
 *    `extern s32 D_8019BAC8[]` -> "conflicting types". Lever (A): conform the decl
 *    VERBATIM and keep the disagreement at the use site, which already casts the
 *    decayed pointer to s32. Zero bytes change.
 *  - func_801292C8: not declared anywhere in this TU, but src/shared/engine_core.h
 *    declares it as `extern void func_801292C8(u8 *a0);` inside four DEFINE_ macros
 *    (6304/8491/13623/13794). None of those macros is expanded in this TU today, but
 *    conforming to that shape now makes the splice conflict-proof if one ever is.
 *    $a0 already holds the incoming pointer, so passing it costs no instruction
 *    (jal + nop delay slot, exactly as in the target).
 */

extern void func_801292C8(u8 *a0);

void func_80181204(void *a0) {

    extern u8 D_8019BAC8[];
    s32 v0;
    s32 v1;
    s32 a1;
    s32 a2;
    u8 *v1ptr;

    v0 = *(s32 *)((s32)a0 + 0x1C);
    do { v1 = *(s32 *)((s32)a0 + 0x2C); } while (0);
    a1 = v0 - 1;
    /* §21 zero-byte re-tie barrier: without it gcc's scheduler hoists the 0x2C load
     * (and its sll) ahead of the 0x1C load + addiu pair -- the 4-slot SCHEDULE-REORDER
     * residual. Folding the shift into the address expression fixes the order but then
     * swaps $v0/$v1 across the sll/lui pair (REGALLOC-PERM). The re-tie keeps the
     * in-place `v1 <<= 6` form (so the shift stays in $v1) AND anchors it after the
     * two loads. Emits no code. */
    v1 = v1 << 6;
    a2 = (s32)D_8019BAC8 + v1;
    v1ptr = *(u8 **)((s32)a0 + 0x20);

    *(s32 *)((s32)a0 + 0x1C) = a1;

    if (!(a1 == -1)) {
        v0 = 0x10 - a1;
        *(u16 *)((s32)v1ptr + 0x1A) = v0 << 8;
        *(u16 *)((s32)v1ptr + 0x18) = v0 << 8;

        v1 = *(s32 *)((s32)a0 + 0x1C);
        v0 = (v1 << 8) - v1;
        if (v0 < 0) {
            v0 = v0 + 0xF;
        }
        v0 = (u32)v0 >> 4;

        *(u8 *)(a2 + 0x2) = v0;
        *(u8 *)(a2 + 0x1) = v0;
        *(u8 *)(a2 + 0x0) = v0;

        v0 = *(s32 *)((s32)a0 + 0x1C) << 2;
        *(u8 *)(a2 + 0x5) = v0;
        *(u8 *)(a2 + 0x4) = v0;

        *(u8 *)(a2 + 0x6) = *(s32 *)((s32)a0 + 0x1C) << 3;
    } else {
        func_801292C8((u8 *)a0);
    }
}


    void func_801812B8(void *a0) {
            s32 *p = *(s32 **)((s32)a0 + 0x20);
            p[1] = p[1] | 0x58000000;
            *(s16 *)((s32)p + 0x1E) = 0;
            *(s16 *)((s32)p + 0x18) = 0;
            *(s16 *)((s32)p + 0x1A) = 0;
            *(s16 *)((s32)p + 0x1C) = 0;
            *(s32 *)((s32)a0 + 0x2C) = 0x400;
            *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
        }


extern void func_801292C8(u8 *a0);
extern s32 func_8004787C(s32 a0);

void func_801812F8(void *a0) {
    s32 v0;
    s32 s0;

    v0 = *(s32 *)((s32)a0 + 0x2C);
    s0 = *(s32 *)((s32)a0 + 0x20);
    v0 = v0 - 0x80;
    *(s32 *)((s32)a0 + 0x2C) = v0;
    if (v0 <= 0) {
        func_801292C8((u8 *)a0);
    } else {
        v0 = func_8004787C(v0);
        *(s16 *)(s0 + 0x1A) = v0;
        *(s16 *)(s0 + 0x18) = v0;
    }
}



extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8018134C(s32 a0, s16 a1, s16 a2) {
    s16 p1[3];
    s16 p2[3];
    s32 t;
    s32 result;

    p1[0] = *(u16 *)(a0 + 6);
    p1[1] = *(u16 *)(a0 + 0xA);
    p1[2] = *(u16 *)(a0 + 0xE);

    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
    p2[1] = p1[1];
    p2[0] = p1[0] - (t >> 12);

    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
    p2[2] = p1[2] - (t >> 12);

    result = func_80133784(1, p1, (s32)p2);

    if ((result & 0x8000) && a2) {
        t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
        p1[1] = p2[1];
        p1[0] = p2[0] + (t >> 12);

        t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
        p1[2] = p2[2] + (t >> 12);

        result = func_80133784(1, p2, (s32)p1);

        *(s16 *)(a0 + 6) = p1[0];
        *(s16 *)(a0 + 0xA) = p1[1];
        *(s16 *)(a0 + 0xE) = p1[2];

        if (!(*(u16 *)(a0 + 0x84) & 2)) {
            *(u16 *)(a0 + 0x84) |= 2;
        }
    } else {
        *(u16 *)(a0 + 0x84) &= ~2;
    }

    return result;
}


/* func_80181500 -- ov_SC03_107 / ov_SC03_107_jr_801789AC (212 ins)
 *
 * Decls chosen to agree VERBATIM with the destination TU
 * (src/ov_SC03_107/ov_SC03_107_jr_801789AC.c):
 *   func_8002D4C8  TU:168/3781/5786/5823/6444/8084 `extern void (s32,s32)`  (also `(int,int)` @999)
 *   func_8012B030  TU:357/4991 `extern s32 (u8 *)`
 *   func_8012CBCC  TU:452 `extern void (s32)`, TU:631 `extern void (s32)`
 *                  -> VOID in the TU, so the return value is read through the
 *                     §161c function-pointer cast, never through a re-decl.
 *   func_80131C78  TU:565 `extern void (s32)`
 *   func_80143B6C  TU:581/1143 `extern s32 (s32,s32)`
 *   func_800291C8  TU:983 `extern void (s32,s32)`
 *   func_8018134C  DEFINED at TU:7981 as `s32 func_8018134C(s32,s16,s16)` --
 *                  the definition is above this slot, so the decl below agrees.
 * D_8019BBC8 / D_8019BBCC are declared nowhere in the TU (free choice).
 */

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012B030(u8 *a0);
extern void func_8012CBCC(s32);
extern void func_80131C78(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_800291C8(s32, s32);
extern s32 func_8018134C(s32 a0, s16 a1, s16 a2);

extern s32 D_8019BBC8;
extern s32 D_8019BBCC;

void func_80181500(s32 a0) {
    /* §162i1 dead-local pad: target frame 0x28 = args 0x10 + vars 0x10 + 4*2 regs;
     * the raw draft compiles vars=0. Never read, never &-taken, >=2 elements. */
    s32 pad[4];

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_80131C78(a0);
        *(s16 *)(a0 + 0x2) = 2;
        *(s32 *)(a0 + 0x1C) = 1;
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        D_8019BBC8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_8019BBC8 & 0x6000) {
            if (D_8019BBC8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x531, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            func_80143B6C(a0, 1);
            func_8002D4C8(0x754, 0);
            *(u8 *)(a0 + 0xC2) = 1;
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
            *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) >> 2;
            *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) >> 2;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x78) {
            func_80131C78(a0);
            *(s16 *)(a0 + 0x2) = 2;
            *(s32 *)(a0 + 0x1C) = 1;
        }
        break;

    case 1:
        D_8019BBCC = *(s32 *)(a0 + 0x14);
        D_8019BBC8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_8019BBC8 & 0x6000) {
            if (D_8019BBC8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x531, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            {
                /* The read of D_8019BBCC MUST precede the two pointer stores in the
                 * source: gcc-2.7.2's scheduler cannot hoist a symbol_ref load above a
                 * store through a register base (may-alias), so writing it inline in the
                 * `-D_8019BBCC` expression leaves the load-delay slot unfilled -> a nop,
                 * and the function is 1 instruction long. */
                s32 t;
                func_8002D4C8(0x754, 0);
                func_80143B6C(a0, 1);
                t = D_8019BBCC;
                *(u8 *)(a0 + 0xC2) = 2;
                *(s32 *)(a0 + 0x1C) = 0;
                *(s32 *)(a0 + 0x14) = -t;
            }
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x28) {
            func_80131C78(a0);
            *(s16 *)(a0 + 0x2) = 2;
            *(s32 *)(a0 + 0x1C) = 1;
        }
        break;

    case 2:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        D_8019BBC8 = ((s32 (*)(s32))func_8012CBCC)(a0);
        if (D_8019BBC8 & 0x6000) {
            *(s32 *)(a0 + 0x14) = 0;
            if (D_8019BBC8 & 0x1000) {
                *(s16 *)(a0 + 0x2) = 2;
                *(u8 *)(a0 + 0xC1) = 0;
                *(s16 *)(a0 + 0x5E) = 0;
                *(s32 *)(a0 + 0x1C) = 0x30;
                func_8002D4C8(0x531, 0);
                func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
                return;
            }
            if (!(*(u16 *)(a0 + 0x84) & 1)) {
                *(u16 *)(a0 + 0x84) |= 1;
                func_8002D4C8(0x754, 0);
            }
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x11) {
                func_80131C78(a0);
                func_8012B030((u8 *)a0);
                *(s16 *)(a0 + 0x2) = 1;
                *(u16 *)(a0 + 0x84) &= 0xFFFE;
            }
        }
        break;
    }

    func_8018134C(a0, -0x28, 1);
    *(s16 *)(a0 + 0x108) = *(u16 *)(a0 + 0x108) - 1;
    if (*(s16 *)(a0 + 0x108) == 0) {
        func_800291C8(0xA, *(s16 *)(a0 + 0xFE));
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern s32 func_800291DC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_800291C8(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_8012B23C(s32 a0);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_80181A70(s32 a0);

extern s16 currentLocationId;
extern s16 D_80198B70;
extern s32 D_80198BB8;
extern u16 D_80198BB0;
extern u16 D_80198BB2;
extern u16 D_80198BB4;
extern u8 D_800AF630[];

void func_80181850(s32 a0) {
    s32 v0, v1;
    u8 *p = D_800AF630;

    if (func_8012C354(a0, (s32)&D_80198B70) != 0) {
        if ((u32)func_80029504() < 0x1D7) {
            v1 = func_800291DC(0xA);
            if ((v1 & 0x100) == 0 && (s16)v1 != currentLocationId) {
                func_8012C218((void *)a0);
                return;
            }
        } else {
            func_8012C218((void *)a0);
            return;
        }

        if (*(s16 *)(p + 0xA3D8) == 0x1052) {
            func_80029514(0x1D6);
        }
        v0 = *(u16 *)(p + 0xA3D8);
        *(s16 *)(a0 + 0xFE) = v0;
        func_800291C8(0xA, (s16)v0);
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = -0x489;
        *(s32 *)(a0 + 0xBC) = (s32)&D_80198BB8;
        *(u8 *)(a0 + 0xC1) = 0;
        *(s32 *)(a0 + 0xC4) = 1;
        func_8012B23C(a0);
        func_80143970(a0);
        func_8012B030((u8 *)a0);

        v1 = *(u16 *)(a0 + 0x6);
        *(s16 *)(a0 + 0x2) = 1;
        *(s16 *)(a0 + 0xAE) = -1;
        *(u8 *)(a0 + 0x75) = 8;
        D_80198BB0 = v1;
        D_80198BB2 = *(u16 *)(a0 + 0xA);
        D_80198BB4 = *(u16 *)(a0 + 0xE);

        if (*(s16 *)(p + 0xA3D8) == 0x1052) {
            func_80181A70(a0);
        }
    }
}


void func_801819C8(s32 a0) {
    s32 a1 = a0;

    extern s16 D_80126B62;
    extern u8 D_80198B50;
    extern u8 D_80198B60;
    extern void (*D_80198BF8[])(void *);

    if (*(s16 *)((s32)a1 + 0xFC) != 0) {
        s32 ptr = *(s32 *)((s32)a1 + 0x20);
        *(s16 *)((s32)a1 + 0xFC) -= 1;
        *(s32 *)(ptr + 4) ^= 0x80000000;
    }
    if (D_80126B62 < (s32)*(s16 *)((s32)a1 + 0xA) - 0x30) {
        *(s32 *)((s32)a1 + 0x58) = (u32)&D_80198B60 | 0x40000000 | 0x20000000;
    } else {
        *(s32 *)((s32)a1 + 0x58) = (u32)&D_80198B50 | 0x40000000 | 0x20000000;
    }
    D_80198BF8[*(u16 *)((s32)a1 + 2)]((void *)a1);
}


extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_80198C08;

void func_80181A70(s32 arg0)
{
    s32 v1;

    *(short *)(arg0 + 0x2) = 3;
    *(short *)(arg0 + 0x34) = 0;
    func_8012E8E0(arg0, (s32)&D_80198C08);
    v1 = *(s32 *)(arg0 + 0x68);
    *(short *)(v1 + 0xC) = 0x7FFF;
}


void func_80181AB8(s32 arg0) {
    struct { s16 vx, vy, vz, pad; } buf;
    s32 v;
    s32 t;

    v = func_8012E544(0x17E);
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        break;
    case 1:
        if (v != 0) {
            if (func_80013328((s32)(v + 4), (s32)(arg0 + 4)) >= 0x60) {
                func_8012B0B4((unsigned int *)&buf,
                              func_8012B6D4((s16 *)(arg0 + 4), (s16 *)(v + 4)),
                              0x60);
                t = *(s32 *)&buf;
                *(u16 *)(arg0 + 6) = *(u16 *)(v + 6) + t;
                *(u16 *)(arg0 + 0xE) = *(u16 *)(v + 0xE) + (t >> 16);
            }
        }
        break;
    case 2:
        func_8012C218((void *)arg0);
        break;
    }
}


void func_80181B94(s32 a0) {
    *(u16 *)((s32)a0 + 0x5C) = 0x8E10;
    if (*(s16 *)((s32)a0 + 0x76) < 0x320) {
        *(s16 *)((s32)a0 + 0x76) = 0x384;
    }
}


extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8018134C(s32 a0, s16 a1, s16 a2);
extern s32 D_80198BA4;

void func_80181BB8(void *arg0) {
    *(u8 *)((char *)arg0 + 0xC1) = 4;
    *(u8 *)((char *)arg0 + 0xC2) = 0;
    *(u16 *)((char *)arg0 + 0x5C) &= ~1;
    func_8012B14C((s32)arg0, (s32)&D_80198BA4);
    *(s32 *)((char *)arg0 + 0x1C) = 0;
    *(s16 *)((char *)arg0 + 0x108) = 0x28;
    func_8018134C((s32)arg0, -0x28, 1);
}


void func_80181C1C(s32 a0) {
    extern u16 D_80198BB0;
    extern u16 D_80198BB2;
    extern u16 D_80198BB4;
    s32 ptr;

    ptr = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(ptr + 4) &= 0x7FFFFFFF;
    *(u16 *)((s32)a0 + 0xFC) = 0;
    func_800291C8(0xA, (s16)(*(u16 *)((s32)a0 + 0xFE) | 0x100));
    D_80198BB0 = *(u16 *)((s32)a0 + 0x6);
    D_80198BB2 = *(u16 *)((s32)a0 + 0xA);
    D_80198BB4 = *(u16 *)((s32)a0 + 0xE);
}


extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_80181C98(struct S80131E00 *arg0) {
    func_80131E00(arg0, 3);
}


void func_80181CB8(void) {
}

extern u16 D_80198BB0;
extern u16 D_80198BB2;
extern u16 D_80198BB4;
extern s32 func_8012B030(u8 *a0);

void func_80181CC0(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);
    u16 v0;

    *(u16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x30;

    v0 = *(u16 *)((s32)a0 + 0xA) + 2;
    v1 = *(s32 *)((s32)a0 + 0x1C) - 1;
    *(u16 *)((s32)a0 + 0xA) = v0;
    *(s32 *)((s32)a0 + 0x1C) = v1;
    if (v1 == 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s32 *)((s32)a0 + 0x1C) = 2;
        *(u16 *)((s32)a0 + 0xFC) = 0x3C;
        *(u16 *)((s32)a0 + 0x6) = D_80198BB0;
        *(u16 *)((s32)a0 + 0xA) = D_80198BB2;
        *(u16 *)((s32)a0 + 0xE) = D_80198BB4;
        func_8012B030(a0);
        *(u16 *)((s32)a0 + 0x5C) = 0x8E10;
        if (*(s16 *)((s32)a0 + 0x76) < 0x320) {
            *(u16 *)((s32)a0 + 0x76) = 0x384;
        }
    }
}




void func_80181D88(void *a0) {

    extern void (*D_80198FEC[])(void);
    D_80198FEC[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80181DC4;


extern s32 func_801822E4(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8018233C(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181DC4(s32 a0) {
    extern u8 D_80198FA0[];
    extern u8 D_80198FAC[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_801822E4(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_80198FA0, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_80198FAC);
        func_8018233C(a0);
        *(u16 *)(s0 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA);
        t = *(u16 *)(a0 + 0xE);
        *(u16 *)(s0 + 0x1A) = 0x2000;
        *(u16 *)(s0 + 0x18) = 0x2000;
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(u16 *)(s0 + 0xC) = t;
        v = *(u16 *)(a0 + 0x2) + 1;
        u = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(s32 *)(a0 + 0x1C) = 0x180;
        *(u16 *)(a0 + 0x2) = v;
        *(u16 *)(a0 + 0x10A) = u;
        func_8002D4C8(0xAA0, 0);
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80181EC0;


extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018233C(s32 arg0);
extern void func_801823B8(void *arg0);

void func_80181EC0(s32 arg0) {
    s32 p;
    s32 q;
    s32 r;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;
    s32 t3;
    s32 t4;
    u16 v;
    u16 w;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(arg0 + 0x10A) == *(s16 *)(p + 0x36) && *(s16 *)(p + 0x76) > 0) {
        if (*(s32 *)(arg0 + 0x1C) == (*(s32 *)(arg0 + 0x1C) / 0x30) * 0x30 &&
            *(u8 *)(p + 0xC1) == 0) {
            *(s16 *)(p + 0x60) = 0xA;
            *(u16 *)(p + 0x5C) |= 1;
            v = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
            *(s16 *)(p + 0x5E) = 1;
            *(u16 *)(p + 0x62) = v + 0x800;
            *(u16 *)(p + 0x7C) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(p + 0x7E) = *(u16 *)(arg0 + 0xA);
            *(u16 *)(p + 0x80) = *(u16 *)(arg0 + 0xE);
        }
        if ((*(s32 *)(arg0 + 0x1C) & 7) == 0) {
            q = func_80132EF4(arg0, 0x22);
            if (q != 0) {
                t0 = rand();
                u0 = *(u16 *)(q + 0x6) - 0x10;
                *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                t1 = rand();
                u1 = *(u16 *)(q + 0xE) - 0x10;
                *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                *(u16 *)(q + 0xA) -= 0x20;
                t2 = rand();
                *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 3) << 16);
                t3 = rand();
                t4 = rand();
                *(s16 *)(q + 0x34) = ((t3 % 0x1800 + 0x1000) & ~0xF) | (t4 & 1);
                *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                *(s32 *)(*(s32 *)(q + 0x20) + 0x4) |= 0x40000000;
            }
        }
        r = *(s32 *)(arg0 + 0xCC);
        if (r != 0) {
            ((s32 (*)(void *, void *))func_80128ED8)((void *)r, (void *)(arg0 + 0xDC));
            func_8018233C(arg0);
            *(u16 *)(r + 0x8) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(r + 0xA) = *(u16 *)(arg0 + 0xA);
            w = *(u16 *)(arg0 + 0xE);
            *(u16 *)(r + 0x18) += 0x15;
            *(u16 *)(r + 0x1A) += 0x15;
            *(u16 *)(r + 0xC) = w;
        }
        if (*(u16 *)(p + 0x5E) == 0x23) {
            *(u16 *)(arg0 + 0x2) += 1;
        }
        if (func_8012BEE8(arg0) == 0) {
            return;
        }
    }
    func_801823B8((void *)arg0);
}





extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8018233C(s32 arg0);
extern void func_801823B8(void *arg0);

void func_80182150(s32 arg0) {

    extern u16 D_800B99DA;
    s32 p;
    s32 q;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;

    p = *(s32 *)(arg0 + 0xCC);
    if (p != 0) {
        ((s32 (*)(void *, void *))func_80128ED8)((void *)p, (void *)(arg0 + 0xDC));
        func_8018233C(arg0);
        *(u16 *)(p + 0x8) = *(u16 *)(arg0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(arg0 + 0xE);
        *(u16 *)(p + 0x18) -= 0x200;
        *(u16 *)(p + 0x1A) -= 0x200;
        if (*(s16 *)(p + 0x18) >= 0) {
            if (D_800B99DA % 5 == 0) {
                q = func_80132EF4(arg0, 0x22);
                if (q != 0) {
                    t0 = rand();
                    u0 = *(u16 *)(q + 0x6) - 0x10;
                    *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                    t1 = rand();
                    u1 = *(u16 *)(q + 0xE) - 0x10;
                    *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                    *(u16 *)(q + 0xA) -= 0x20;
                    t2 = rand();
                    *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 4) << 16);
                    *(s16 *)(q + 0x34) = rand() % 0x1800 + 0x2000;
                    *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                }
            }
            return;
        }
    }
    func_801823B8((void *)arg0);
}



/* func_801822E4 — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_801822E4(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x35C && *(s32 *)(arg0 + 0x64) == *(s32 *)(p + 0x64) &&
            arg0 != (s32)p) {
            return 1;
        }
        p += 0x10C;
    }
    return 0;
}



extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8018233C(s32 arg0) {
    s32 buf[8];
    u16 out[4];
    s32 p;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(p + 0x36) == *(s16 *)(arg0 + 0x10A)) {
        func_8012EC04(p, *(s16 *)(arg0 + 0xFC), buf);
        ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, arg0 + 0x88, out);
        *(u16 *)(arg0 + 0x6) = out[0];
        *(u16 *)(arg0 + 0xA) = out[1];
        *(u16 *)(arg0 + 0xE) = out[2];
    }
}



/* func_801823B8 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801823B8(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_801823FC(s32 a0, u16 *a1, s16 a2) {
    struct S80190C84 sp;
    u16 t;
    sp.f0 = a1[0];
    sp.f2 = a1[1];
    t = a1[2];
    sp.f6 = 0x35C;
    sp.fA = 0;
    sp.f8 = 0;
    sp.fE = a2;
    sp.f10 = 0;
    sp.fC = 0x7FFF;
    sp.f4 = t;
    func_8012C51C(&sp, a0);
}


