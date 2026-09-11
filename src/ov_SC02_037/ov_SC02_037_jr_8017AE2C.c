#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
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
typedef struct {
    u16 f0, f2, f4;
    s16 f6;
} Blk801539F8;
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
typedef struct { u32 a; u32 b; } __attribute__((packed, aligned(1))) Unaligned8;
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
extern u16 D_80184F60[];
extern void func_80141C0C(s32 a0);
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
void func_801439C0(u8 *a0);
void func_8012AD44(s32 *a0, s16 a1);
void func_8012C218(void *a0);
void func_8012C098(void *param_1);
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
extern void func_801439C0(u8 *a0);
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
void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_80149450(int param_1, short *param_2);
extern void func_801494CC(int param_1, short *param_2, short *param_3);
extern void func_80149544(s32 a0, s32 a1, s32 a2);
void func_8012F14C(s32 a0, s32 a1, s32 a2);
void func_8012EFB8(s32 a0);
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
extern void func_8014CBE8(void);
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
s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
s32 func_8014C918(s32 a0, s32 a1);
extern s32 func_8014D610(s32 a0, s32 a1, u16* a2);
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
extern void func_8014ED28();
extern void (*D_8011DB28)(s32 a0);
extern s32 func_801536DC(s32 param_1);
extern s32 func_80153978(s32 a0, u16 *src);
extern s32 func_80133784(s32 a0, void *src, s32 dst);
extern s32 func_801539F8(s32 a0, void *a1);
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
void func_80147078(s32 *a0, s16 a1);
void func_801578C0(s32 a0);
extern void func_80157788(s32 *a0);
extern void func_80157808(s32 *a0);
extern void func_801577C8(s32 *param_1);
extern void func_801578C0(s32 a0);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_8014ED28();
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
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
void func_80154150(s32 a0, s32 a1);
void func_80146DB8(s32 *a0, s32 *a1);
void func_80161CD0(s32 a0, s32 a1);
extern s32 D_8018623C;
extern void func_8015AC48(s32 a0);
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
extern void func_8015BE38(struct Obj *a0);
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
extern void func_8015CC74(s32 *a0);
extern void func_8015CC40(s32 *a0);
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern s32 func_8015CD20(s32 arg0);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
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
extern s32 func_8015D4E8(s16 *a0);
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
extern void func_8015DAF8(s32 *a0);
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
extern void func_8015DE58(s32 *a0);
extern void func_8015DECC(s32);
extern void func_8015DE94(s32 a0);
extern void func_8015E018(s32 a0);
extern void func_8015DF34(void *arg0);
extern int func_8015DFE4(int a0);
extern void func_8015E018(s32 param_1);
extern int func_8015E0D4(int a0);
extern void func_8015E22C(s32 a0);
extern void func_8015E150(s32 *a0);
extern s32 func_8015E1B8(s32 a0);
extern void func_8015E184(s32 *arg0);
extern void (*D_80186560[])(void);
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
extern void func_8015E8E8(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void (*D_80186594[])(void);
extern void func_8015E8E8(s32* param_1);
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
extern s32 func_8015EE08(s32 a0);
extern void func_8015EDD4(s32 *arg0);
extern void (*D_8018659C[])(void);
extern void func_8015EE44(s32 a0);
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C(s32 *a0);
extern void func_8015EFD8(s32 *a0);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324(s32 *a0);
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
extern s32 func_8015F7D4(s32 a0);
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
extern void (*D_80186680[])(void);
extern void func_80160138(s32* param_1);
extern void func_80160174(s32 *a0);
extern void func_801601E4(s32 *a0);
extern void func_80160244(s32 *a0);
extern void func_801602A4(s32 *a0);
extern void func_8016032C(void);
extern void func_80160410(s32 *a0);
extern void func_80160334(s32 *a0);
extern void func_8016039C(s32 *a0);
extern void func_80160368(s32 *a0);
extern void (*D_80186690[])(void);
extern void func_8016039C(s32* arg);
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
extern void (*D_801866A4[])(void);
extern s32 func_80160B34(s32 param);
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
void func_801599A4(void *a0);
void func_8015BDD0(s32 *a0);
void func_8015BF48(s32 *a0);
void func_80015954(s32 a0, s32 a1);
extern int func_80161374(int a0, unsigned a1);
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
void func_8014C010(s32 a0, s32 a1);
void func_80161D20(s32 a0, s32 a1);
extern s32 func_80161888(s32 a0, u32 a1);
extern void func_8014C010(int a0, int a1);
extern int aF8016191C();
extern s32 func_801619A4(s32 *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern s32 func_80161A60(s32 a0);
s32 func_801497A8(s32 *a0);
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
s32 func_80128ED8(s32 param_1, s32 *param_2);
void func_80146C3C(u8 *a0);
void func_800D22E4(s32 a0);
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
extern void func_80168664(s32 param_1);
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
void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
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
extern void func_8016DB34(s32 a0);
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
s32 func_8014C568(s16 *a0, s16 *a1);
s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s16 func_80171AB0(s32 param_1, void* _arg1);
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
extern s32 func_801727D0(void *a0);
extern void func_80172780(void *a0);
extern void func_80172844(u8 *a0);
extern void func_8017280C(u8 *a0);
extern void func_8017288C(void);
extern s32 func_801728E4(void *a0);
extern void func_80172894(void *a0);
extern void func_80172958(u8 *a0);
extern void func_80172920(u8 *a0);
extern s16 D_80126B36;
extern void func_80172958(u8 * a0);
extern void func_801729A8(void);
extern s32 func_801729F0(void *a0);
extern s16 D_80126B34;
extern s16 D_80126B32;
extern void func_801729B0(s32 a0);
extern void func_80172A8C(void *a0);
extern void func_80172A2C(int param_1);
extern void func_80172ACC(u8 *a0);
extern void func_80172B0C(void);
extern s32 func_80172B44(void *a0);
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
extern s32 func_80172DAC(void *a0);
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
extern s32 func_80173078(void *a0);
extern void func_8017303C(void * a0);
extern void func_801730FC(struct S801730FC *a0);
extern void func_801730B4(s32 a0);
extern void func_8017316C(void);
extern s32 func_8017319C(void *a0);
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
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern s16 D_80126B40;
void func_801734BC(s32 a0, s32 a1);
extern void func_801733FC(s32 a0, s32 a1);
extern void func_801734BC(s32 a0, s32 a1);
extern void func_80173460(s32 a0, s32 a1);
extern void func_80173544(void *a0);
extern void func_801735B8(u8 *a0);
extern void func_80173580(u8 *a0);
extern void func_801735EC(void *a0);
extern void func_80173648(u8 *a0);
extern void func_801736A8(void);
extern s32 func_8014C118(void *a0, s32 a1, s32 a2);
extern s32 func_801736FC(void *a0);
extern void func_801736B0(s32 a0, s32 a1);
extern void func_80173770(u8 *a0);
extern void func_80173738(u8 *a0);
extern void func_801723C4(s32 a0, s32 a1);
extern void func_801737B0(void);
extern s32 func_801737E8(void *a0);
extern void func_801737B8(s16 a0);
extern void func_8017385C(u8 *a0);
extern void func_80173824(u8 *a0);
extern void func_801738D4(void);
extern s32 func_8017390C(void *a0);
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
extern s32 func_801742A4(void *a0);
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
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern void func_80178BF8(s32 _unused0, s32 _unused1);
extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
extern void func_80179B28(s32 a0);
extern void func_80179B74(u16 *p);
extern void func_80179D30(u16 *a0);
extern void func_80179D78(u16 *a0);
extern void func_80179DCC(short a0);
extern void func_80179DF8(void);
extern void func_80179E1C(short a0);
extern void func_80179E48(s16 a0);
extern void func_80179E74(s16 a0);
extern void func_80179EA0(u16 *a0);
extern void func_80179EE8(short a0);
extern void func_80179F14(s16 a0, s16 a1);
extern void func_80179F44(void);
extern void func_80179F6C(short a0);
extern void func_80179F98(u16 *a0);
extern void func_80179FEC(u16 *a0);
extern void func_8017A040(u16 *a0);
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern void func_8017A144(s32 a0);
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
extern int func_800D0CA0(int);
extern int func_8001AAA0(s32 arg0);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
extern s32 func_8017AD0C(s32 arg0);
extern s32 func_8017AD0C(s32);
extern s32 func_8017ADE8(s32 a0);
extern s32 func_8017AE08(void);
/* ==== end §8b carried decl layer ==== */


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974;

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012BE98(s32, u16*);
extern s32 func_80012A60(s32 a0, s32 a1);


void func_8017AE2C(s32 param_1) {

    extern s16 D_801C9A40;
    extern s16 D_801C9A42;
    extern s16 D_801C9A4C;
    s32 pv = param_1;
    s16 *g = &D_801C9A40;

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
                    func_8012B744(p, &D_801C9A4C);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801C9A40+0xC == &D_801C9A4C; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_801C9A40 + 0xC)) < 0x101) {
                    D_801C9A40 = 0;
                    D_801C9A42 = 0;
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
            func_8012B744((void *)(pv + 4), &D_801C9A4C);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (((s32 (*)(s32, u16 *))func_8012BE98)(pv, (u16 *)((s32)&D_801C9A40 + 0xC)) < 0x101) {
            D_801C9A40 = 0;
            D_801C9A42 = 0;
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
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801C96BC;
    extern s16 D_801C96BE;
    extern s16 D_801C96C0;
    extern s16 D_801C96B4;
    extern s16 D_801C96B6;
    extern s16 D_801C96B8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801C96BC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801C96BE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801C96C0, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801C96B4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801C96B6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801C96B8, (s32)((s16)param_2));
}


extern void func_8012A418(void);

void func_8017B1D8(void) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_801C9644;
    extern u16 D_801C96C4;
    extern u16 D_801C96C6;
    extern u16 D_801C96C8;
    extern s16 D_801C9A70;
    func_8012A418();
    D_801C9A70 = 0;
    D_801C9644 = 0;
    D_801C96C4 = D_80126B5E;
    D_801C96C6 = D_80126B62;
    D_801C96C8 = D_80126B66;
}


extern void func_8012A018(s32 a, s32 b);
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017B238;

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{

    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018754C[];
    extern s16 D_801C96BC;
    extern s16 D_801C96B4;
    extern u8 D_8012694C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_8018754C[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018754C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C96BC;
        s16 *p78C = &D_801C96B4;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801C9A70 = 1;
        D_801C9644 = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{

    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801C9664;
    extern SV4_8017B368 D_801C966C;
    extern s16 D_801C96BC;
    extern s16 D_801C96B4;
    extern u16 D_8018754C;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C9664;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C966C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018754C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018754C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C96BC) = loc0;
    (*(SV4_8017B368 *)&D_801C96B4) = loc1;
    D_801C9A70 = 1;
    D_801C9644 = 0;
}




s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801C9664;
    extern SV4_8017B368 D_801C966C;
    extern s16 D_801C96BC;
    extern s16 D_801C96B4;
    extern u16 D_8018754C;
    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C9664;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C966C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018754C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018754C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C96BC) = loc0;
    (*(SV4_8017B368 *)&D_801C96B4) = loc1;
    D_801C9A70 = 1;
    D_801C9644 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801C96BC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801C96BC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801C96BC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801C96B4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801C96B4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801C96B4).c;
}


extern void func_8012A018(s32 a, s32 b);

// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.




s32 func_8017B614(s32 param_1, s32 param_2)
{

    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018754C[];
    extern s16 D_801C96BC;
    extern s16 D_801C96BE;
    extern s16 D_801C96C0;
    extern s16 D_801C96B4;
    extern s16 D_801C96B6;
    extern s16 D_801C96B8;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018754C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018754C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C96BC;
        s16 *p78C = &D_801C96B4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801C96BE;
            v798 = D_801C96C0;
            v78C = *p78C;
            v78E = D_801C96B6;
            v790 = D_801C96B8;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            D_801C9A70 = 1;
            D_801C9644 = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}




// @class: plumbing
// @stuck: none — MATCH



void func_8017B7A8(void)
{

    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8 D_8012694C;
    extern s16 D_801C9644;
    extern s16 D_801C96BC;
    extern s16 D_801C96BE;
    extern s16 D_801C96C0;
    extern s16 D_801C96B4;
    extern s16 D_801C96B6;
    extern s16 D_801C96B8;
    D_8012694C = 1;
    D_801C9644 = 0;
    D_801C96BC = (s16) D_80114F30;
    D_801C96BE = (s16) D_80114F34;
    D_801C96C0 = (s16) D_80114F38;
    D_801C96B4 = (s16) aD80114F24;
    D_801C96B6 = (s16) D_80114F28;
    D_801C96B8 = (s16) D_80114F2C;
}




void func_8017B824(void) {

    extern s32 D_801151D4;
    extern s16 D_801C96D4;
    extern s16 D_801C96D6;
    extern s16 D_801C96D8;
    extern s16 D_801C96DC;
    extern s16 D_801C96DE;
    extern s16 D_801C96E0;
    D_801C96D4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801C96D6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801C96D8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801C96DC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801C96DE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801C96E0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH



void func_8017B880(void)
{

    extern s16 D_801C96D4;
    extern s16 D_801C96D6;
    extern s16 D_801C96D8;
    extern s16 D_801C96DC;
    extern s16 D_801C96DE;
    extern s16 D_801C96E0;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    D_80114F30 = D_801C96D4;
    D_80114F34 = D_801C96D6;
    D_80114F38 = D_801C96D8;
    aD80114F24 = D_801C96DC;
    D_80114F28 = D_801C96DE;
    D_80114F2C = D_801C96E0;
}





s32 func_8017B8E8(s32 src) {

    extern s16 D_801C96B4;
    extern s16 D_801C96BC;
    (*(S8_8017B8E8 *)&D_801C96BC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801C96B4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)




void func_8017B940(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_801C96C4;
    extern u16 D_801C96C6;
    extern u16 D_801C96C8;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8  D_8012694C;
    extern s16 D_801C9644;
    extern short D_801C96CC;
    extern short D_801C96CE;
    extern short D_801C96D0;
    extern s16 D_801C96BC;
    extern s16 D_801C96BE;
    extern s16 D_801C96C0;
    extern s16 D_801C96B4;
    extern s16 D_801C96B6;
    extern s16 D_801C96B8;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801C96C4);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801C96C6);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801C96C8);
    (*(s16 *)&D_801C96CC) = buf[0];
    (*(s16 *)&D_801C96CE) = buf[1];
    (*(s16 *)&D_801C96D0) = buf[2];
    D_801C96BC = D_80114F30 + buf[0];
    D_801C9644 = 0;
    D_801C96BE = D_80114F34 + buf[1];
    D_801C96C0 = D_80114F38 + buf[2];
    D_801C96B4 = aD80114F24 + buf[0];
    D_801C96B6 = D_80114F28 + buf[1];
    D_801C96B8 = D_80114F2C + buf[2];
}


typedef struct { s16 vx, vy; } DVEC2_C974_8017BA3C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017BA3C;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C974_8017BA3C;


// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32, s32, void*);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_c2: 3x3 short rotation + pad + 3 long translation (offset 0x14) */


void func_8017BA3C(s32 param_1, s32 param_2)
{

    extern SV4 D_801C9664;
    extern SV4 D_801C966C;
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_c2, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801C966C) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801C9664 = svec;

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
    D_801C966C = buf1;
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_8017BB34;




s32 func_8017BB34(s32 param_1, s32 param_2)
{

    extern SV4 D_801C9664;
    extern SV4 D_801C966C;
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_c2, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801C966C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801C9664) = svec;

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
    (*(SV4_8017BB34*)&D_801C966C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0


void func_8017BC38(int param_1)
{

    extern void (*D_801C968C[10])(int);
    int i;
    void (**p)(int);

    i = 0;
    p = D_801C968C;
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
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);

void func_8017BCA0(int param_1) {

    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    func_8017B0E4(param_1, 0xC);
    D_801C9644 = D_801C9644 + 1;
    if (D_801C9644 >= 0x1F) {
        D_801C9A70 = 2;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)


extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{

    extern s16 D_801C9644;
    extern s16 D_801C9A70;
    func_8017B0E4(param_1, 6);
    D_801C9644 = D_801C9644 + 1;
    if (0x18 < D_801C9644) {
        func_8012A4BC();
        D_801C9A70 = 0;
    }
    return;
}



// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);



void func_8017BD50(int param_1)
{

    extern s16 D_801C9644;
    extern void (*D_801C9688)(void);
    extern short D_801C96CC;
    extern short D_801C96CE;
    extern short D_801C96D0;
    extern s16 D_801C9A70;
    extern s32 aD80114F24 __asm__("D_80114F24");
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    func_8017B0E4(param_1, 6);
    D_801C9644 = D_801C9644 + 1;
    if (D_801C9644 >= 0x19) {
        if (D_801C9688 != 0) {
            (*D_801C9688)();
        } else {
            D_80114F30 = D_80114F30 + D_801C96CC;
            D_80114F34 = D_80114F34 + D_801C96CE;
            D_80114F38 = D_80114F38 + D_801C96D0;
            aD80114F24 = aD80114F24 + D_801C96CC;
            D_80114F28 = D_80114F28 + D_801C96CE;
            D_80114F2C = D_80114F2C + D_801C96D0;
            func_8012A4BC();
        }
        D_801C9A70 = 0;
    }
}




void func_8017BE60(void *a0) {

    extern void (*D_801875EC[])(void);
    D_801875EC[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}




/* func_8017BEBC — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801C96E8..D_801C9710 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017BEBC(s32 param_1, s32 param_2)
{

    extern s32 D_801C96E8;
    extern s32 D_801C96EC;
    extern s32 D_801C96F0;
    extern s32 D_801C96F8;
    extern s32 D_801C96FC;
    extern s32 D_801C9700;
    extern s32 D_801C9708;
    extern s32 D_801C970C;
    extern s32 D_801C9710;
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */

    SV4_L_8017C558 vec;                              /* sp+0x10 */
    MTX_L_8017C558 mtx;                              /* sp+0x18 */
    s32 obj = *(s32 *)(param_1 + 0xCC);
    s32 prim = *(s32 *)(param_1 + 0x20);
    s32 mode;
    s32 val;
    s32 hi;
    s32 code;
    s32 t;

    if ((s16)param_2 != 0) {
        mode = 0x40000000;
        val = 0x1000;
    } else {
        mode = 0x50000000;
        val = 0x1333;
    }
    code = *(s32 *)(prim + 4) & 0xCFFFFFFF;
    hi = 0x40000000;
    *(s32 *)(prim + 4) = code | (mode | hi);

    if (*(u16 *)(*(s32 *)(param_1 + 0xCC)) != 0) {
        *(s16 *)(obj + 0x1A) = val;
        *(s16 *)(obj + 0x18) = val;
    }

    t = *(u16 *)(param_1 + 0xFC) + 0x80;
    *(u16 *)(param_1 + 0xFC) = t;
    vec.a = t;
    t = *(u16 *)(param_1 + 0xFE) + 0x100;
    *(u16 *)(param_1 + 0xFE) = t;
    vec.b = t;
    vec.c = 0;
    RotMatrixYXZ(&vec, &mtx);

    vec.b = 0;
    vec.a = 0;
    vec.c = 0x100;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(&mtx, &vec, &vec);

    D_801C9708 = vec.a;
    D_801C96F8 = vec.a;
    D_801C96E8 = vec.a;
    D_801C970C = vec.b;
    D_801C96FC = vec.b;
    D_801C96EC = vec.b;
    D_801C9710 = vec.c;
    D_801C9700 = vec.c;
    D_801C96F0 = vec.c;
}





/* func_8017BFEC — ov_SC02_027_jr_8017AE2C (227 ins).  MATCH (match_one, 227/227).
 *
 * RETRY-WAVE RE-VERIFICATION (§136b — the ledgered DIFF describes an OBSOLETE draft).
 * The s8 gate ran 14:53; THIS file was written 15:22, 28 min AFTER it.  The gate never saw it.
 * Four independent checks on the file as it stands:
 *   1. match_one              -> MATCH (227 ins)
 *   2. rtu_match (whole TU)   -> MATCH (227 ins); CC1 clean, the only warning is the TU's
 *                                pre-existing `memcpy' builtin one at TU:1530 (baseline too)
 *   3. FULL RELOCATION RESOLVE (the byte-gate's view, which match_one's mask cannot see):
 *      every R_MIPS_26 / HI16 / LO16 resolved from the D_<addr>/func_<addr> symbol values and
 *      compared word-for-word against the target .s -> 0/227 diffs.  Every jal target, every
 *      %hi/%lo symbol AND addend is right.
 *   4. COLLATERAL: TU compiled with and without the splice; all 53 other functions emit
 *      IDENTICAL words.  The only deltas are .text-relative `j' addends, every one shifted by
 *      exactly 0x38C == this function's size, which the linker resolves identically.
 * No codegen work was needed; the previous agent's tbl/tbl2 split + load-before-store lever
 * (documented below) had already closed it.
 *
 * Declarations reconciled against the WHOLE TU (grepped in one pass, D2):
 *   func_800291B4  TU:59/3422   extern s32 func_800291B4(s32 arg);     -> `& 0xFF` at the call
 *   func_8001C810  TU:1548      extern void func_8001C810(s32 a0, s32 a1);
 *   func_8001CD50  TU:1564/3518 extern void func_8001CD50(s32, s32);
 *   func_800233CC  TU:1565/3519 extern void func_800233CC(void *, unsigned short);
 *   func_8001D074  TU:124/129/3517 declared VOID -> s32 return taken through a cast (idiom 9)
 *   func_8012A828  TU:3730      extern void func_8012A828(s32 a0, void *a1);
 *   D_801152BA     TU:3657      extern u16 D_801152BA;   (the SIGNED uses need an (s16) cast:
 *                               combine folds (s16)(u16 mem) back to a plain `lh`)
 *   D_80115214     TU:3432/3658 extern s16 D_80115214;
 *   D_801C96E8     TU:3333      extern s32 D_801C96E8;
 * func_8012CAE4 / func_8012C354 are absent from the TU; the canonical engine_core.h forms
 * are reused verbatim (DEFINE_func_8012CAE4 @15355 `void func_8012CAE4(void *a0)`,
 * DEFINE_func_8012C354 @15748 `s32 func_8012C354(s32 a0, s32 a1)`).
 * D_80187620 / D_8018765C / D_801C38D0 / every D_801D9E9x-ECx / D_801C9798 appear nowhere
 * in the TU or engine_core.h (only D_801C96E8..EB8 and D_801D9F00..F06 are declared there).
 * D_801C38F8 is declared BLOCK-SCOPE here on purpose: the TU's only other declaration
 * (TU:3587, `extern Rec_8017C738 D_801C38F8[];`) is itself block-scope inside func_8017C738,
 * so neither is a file-scope decl the other can collide with.
 *
 * THE 0x6C-BYTE TABLE COPY.  9 x 12-byte records = 108 bytes at alignment 2, so
 * gcc-2.7.2's mips.c:expand_block_move takes the align < UNITS_PER_WORD path and emits the
 * runtime `or / andi 3 / beq` alignment probe, an unaligned lwl/lwr loop, an aligned lw/sw
 * loop, and an unaligned 12-byte tail.  The join label after the two loops resets cse, which
 * is why the target RE-COMPUTES 108*D_801152BA for the *(a0+0xD8) store.
 *
 * WHAT CLOSED THE LAST 7 (sched.md §1.7 / §S2 — THE BIRTHING BOOST).  Two independent levers,
 * both required; neither is statement-order:
 *
 *  1. `idx = (s16)D_801152BA;` must be read BEFORE the `*(s16*)(s1+0x10) = 0x400` store.
 *     Store-then-load is a true dependence (both MEMs non-struct: the store's address varies,
 *     the load's is constant, so true_dependence's MEM_IN_STRUCT_P escape does not apply) and
 *     it pins `sh 0x10(s1)` ABOVE the `lh`.  Load-first makes it an ANTI dep, whose cost is
 *     still +1 in 2.7.2 (insn_cost is dep-kind-blind, sched.md [A23]), lifting pri(sh) to 2 so
 *     the store is picked first by the backward scheduler and lands LAST, at index 93.
 *
 *  2. `tbl` and `tbl2` MUST BE TWO SEPARATE LOCALS.  One shared `tbl` gives the D_801C9798
 *     address pseudo REG_N_SETS==2, which KILLS the birthing boost (birthing_insn_p,
 *     sched.c:2469/2490): the unboosted `la $a0` then floats to the front of the pri-1 group
 *     and lands at index 86, shoving `la $a2,D_801C38F8` to 88 (this was the entire 7-insn
 *     residual: 86..92 rotated).  Splitting the two uses makes each pseudo single-set, the
 *     boost raises `la $a0` to its consumer's priority so it sinks to 91, and `la $a2` — whose
 *     pseudo IS genuinely multi-set (expand_block_move increments it in both copy loops, so it
 *     can never be boosted) — falls to the front at 86, exactly as the target has it.
 *     Verified invariant: with a shared `tbl`, ALL 8 legal orderings of the 4 head statements
 *     x 2 store forms (INDIRECT_REF and ARRAY_REF) give the SAME wrong order — proof the
 *     residual was priority/boost-driven, not LUID/statement-order-driven.
 */
extern s32 func_800291B4(s32 arg);
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);



void func_8017BFEC(s32 a0) {

    extern u8 D_80187620[];
    extern u8 D_8018765C[];
    extern s32 D_801C38D0;
    extern u16 D_801152BA;
    extern s16 D_80115214;
    extern s32 D_801C96E8;
    extern u8 D_801C96F4;
    extern u8 D_801C96F5;
    extern u8 D_801C96F6;
    extern u8 D_801C9704;
    extern u8 D_801C9705;
    extern u8 D_801C9706;
    extern u8 D_801C9715;
    extern u8 D_801C9716;
    extern u8 D_801C9718;
    extern u8 D_801C9719;
    extern u8 D_801C971A;
    extern u8 D_801C971C;
    extern u8 D_801C971D;
    extern u8 D_801C971E;
    extern u8 D_801C9724;
    /* 9 x 12-byte records = 0x6C bytes, alignment 2 */
    extern Blk027_8017C688 D_801C38F8;
    extern Blk027_8017C688 D_801C9798[];

    u8 *v1;
    s32 s1;
    u8 *p;
    s32 t;
    s16 i;
    Blk027_8017C688 *dst;
    Blk027_8017C688 *tbl2;
    s32 idx;
    Blk027_8017C688 *tbl;
    s32 u;
    s32 w;

    v1 = *(u8 **)(a0 + 0xDC);
    if ((func_800291B4(v1[0] + 0x3A) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    if (*(s32 *)(a0 + 0x20) == 0) {
        if (func_8012C354(a0, (s32)D_80187620) == 0) {
            return;
        }
        func_8001C810(*(s32 *)(a0 + 0x20), (s32)&D_801C38D0);
        func_8012A828(a0, (void *)&D_8018765C[(s16)D_801152BA * 16]);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x20;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)&D_801C96E8;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x40000000;
        *(s16 *)(a0 + 0xAE) = -3;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 == 0) {
        return;
    }

    p = &D_801C9718;
    *(s32 *)(a0 + 0xCC) = s1;
    func_8001CD50(s1, (s32)p);

    D_801C971A = 0x80;
    *p = 0x80;
    D_801C9719 = 0xE0;
    D_801C971D = 0;
    D_801C971C = 0;
    D_801C971E = 0;
    func_800233CC(p, 0x38);

    tbl = D_801C9798;
    idx = (s16)D_801152BA;
    dst = &tbl[idx];
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x8) = *(u16 *)(a0 + 0x6);
    t = *(u16 *)(a0 + 0xA) - 4;
    *(u16 *)(a0 + 0xA) = t;
    *(s16 *)(s1 + 0xA) = t;
    *(s16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(s1 + 0x4) |= 0x50000000;

    D_801C9716 = 0xFF;
    D_801C9724 = 0xFF;
    D_801C9706 = 0xFF;
    D_801C9704 = 0xFF;
    D_801C96F6 = 0xFF;
    D_801C96F4 = 0xFF;
    D_801C9715 = 0x80;
    D_801C9705 = 0x80;
    D_801C96F5 = 0x80;

    *dst = D_801C38F8;

    i = 5;
    tbl2 = D_801C9798;
    *(s32 *)(a0 + 0xD8) = (s32)&tbl2[(s16)D_801152BA];

    while (i < 0x28) {
        if ((func_800291B4(i + 0x3B) & 0xFF) != 0) {
            break;
        }
        i++;
    }
    if (i != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    }

    w = D_801152BA + 1;
    u = *(u16 *)(a0 + 0x2) + 1;
    D_80115214 = 0;
    D_801152BA = w;
    *(u16 *)(a0 + 0x2) = u;
}





/* Declarations copied VERBATIM from the TU (ov_SC02_027_jr_8017AE2C.c):
 *   func_800291B4  TU:59
 *   currentLocationId TU:349
 *   D_80126B5C     TU:361  (scalar u8 -> pass (s32)&D_80126B5C)
 *   D_801202A0     TU:385
 *   func_80013328  TU:520
 *   D_800B99DA     TU:615
 *   rand           TU:957/1092/3543
 *   D_80126B62     TU:1793/2740/3068
 *   func_801746A4  TU:2397
 *   func_80178B18  TU:2539/3653
 *   func_8017BEBC  TU:3465/3542 (void return)
 *   D_80115214     TU:3547
 * func_8012BD14 / D_80187654 / D_801876B8 appear nowhere in the TU; the
 * canonical engine_core.h form of func_8012BD14 is `void func_8012BD14(s32)`
 * (DEFINE_func_8012BD14), so it is declared void and the s32 return is taken
 * through a cast at the call site (idiom 9). */
extern s32 func_800291B4(s32 arg);
extern s16 currentLocationId;
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 rand(void);
extern void func_801746A4(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017BEBC(s32 a0, s32 a1);
extern void func_8012BD14(s32 a0);

void func_8017C378(s32 a0) {

    extern u16 D_800B99DA;

    extern u8 D_80126B5C;
    extern u8 D_801202A0[];
    extern u16 D_80126B62;
    extern s16 D_80115214;
    extern u8 D_80187654[];
    extern u8 D_801876B8[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    s32 s0 = *(s32 *)(a0 + 0x20);
    s16 found;
    s32 lvl;
    s16 i;
    s16 j;
    s32 rand_val;

    if ((D_800B99DA & 0xF) == 0) {
        u8 *p;
        u8 *end;
        for (p = D_801202A0, end = p + 0x6480; p < end; p += 0x10C) {
            if (*(u16 *)p == 0x128) {
                found = ((s32)p == a0);
                break;
            }
        }
        lvl = func_80013328(a0 + 4, (s32)&D_80126B5C);
        if (lvl < 0x800) {
            lvl = 0x44 - ((lvl >> 5) & 0x38);
        } else {
            lvl = 4;
        }
        if (found != 0 || D_80115214 < lvl) {
            D_80115214 = lvl;
        }
    }

    *(u16 *)(s0 + 0x12) += 0x20;
    rand_val = rand();
    func_8017BEBC(a0, rand_val & 0xF);

    if (*(u16 *)(a0 + 0x5E) != 0) {
        for (i = 0; (u16)i < 8; i++) {
            if (*(u16 *)(a0 + 0x5E) == D_80187654[i]) {
                func_801746A4();
                *(s32 *)(a0 + 0x1C) = 0x20;
                *(u16 *)(a0 + 0x2) += 1;
            }
        }
        *(s16 *)(a0 + 0x5E) = 0;
        return;
    }

    if (*(s16 *)(a0 + 0x10A) != 0) {
        return;
    }

    j = 5;
    do {
        if ((func_800291B4(j + 0x3B) & 0xFF) != 0) {
            break;
        }
        j++;
    } while (j < 0x28);

    if (j != 0x28) {
        *(s16 *)(a0 + 0x10A) = 1;
    } else if (((s32 (*)(s32))func_8012BD14)(a0) < 0x2A40) {
        if (currentLocationId == 0x3028) {
            if ((u16)(*(u16 *)(a0 + 0xA) - D_80126B62 + 4) < 4) {
                *(u16 *)(a0 + 0x106) += 1;
            }
            if (*(s16 *)(a0 + 0x106) < 2) {
                return;
            }
        }
        func_80178B18(a0, (s32)D_801876B8);
        *(s16 *)(a0 + 0x10A) = 1;
        *(s16 *)(a0 + 0x2) = 0xA;
    } else {
        *(s16 *)(a0 + 0x106) = 0;
    }
}





extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);

/* 0x801DA0F0 has no symbol (it is interior to D_801DA084); the real relocs
 * in the .s are D_801C995C/108/10C, with $s0 = D_801C995C - 0x14. */

void func_8017C5F0(s32 a0) {

    extern u8 D_801C9758;
    extern u8 D_801C9759;
    extern u8 D_801C975A;
    extern u8 D_801C975C;
    extern u8 D_801C975D;
    extern u8 D_801C975E;
    extern s32 D_801C995C[];
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801C9758;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801C9759 = 0xFF;
    D_801C975A = 0xFF;
    *p = 0xFF;
    D_801C975E = 8;
    D_801C975C = 8;
    D_801C975D = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801C995C[0] = sp[0];
    D_801C995C[1] = sp[1];
    D_801C995C[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801C995C[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801C995C[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}






extern s16 func_80128CFC(u16 a0);
extern void func_8017BEBC(s32 a0, s32 a1);

void func_8017C738(s32 a0) {
    extern Rec_8017C738_8017CDD4 D_801C38F8[];

    Rec_8017C738_8017CDD4 *q = D_801C38F8;
    Rec_8017C738_8017CDD4 *p = *(Rec_8017C738_8017CDD4 **)(a0 + 0xD8);
    u8 *v1 = *(u8 **)(a0 + 0xDC);
    s32 s1 = *(s32 *)(a0 + 0xD0);
    s32 s4 = *(s32 *)(a0 + 0x20);
    s16 val;
    s32 t;
    s16 i;

    if (v1[1] != 0) {
        if (*(s16 *)(a0 + 0x108) == 0) {
            *(s16 *)(a0 + 0x108) = func_80128CFC(*(u16 *)(v1 + 2));
        }
    }

    val = *(u16 *)(s1 + 0x1A) + 0x80;
    *(s16 *)(s1 + 0x1A) = val;
    *(s16 *)(s1 + 0x18) = val;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t != -1) {
        func_8017BEBC(a0, 0);
        for (i = 0; i < 9; ) {
            p->f0 += (s16)q->f0 >> 1;
            if (i != 0) {
                p->f2 += (q->f2 + 0x30) >> 1;
                p->f4 += (s16)q->f4 >> 1;
                p->f6 += 0x40;
                p->f8 += 0x80;
                p->fA += 0x100;
            }
            i++;
            q++;
            p++;
        }
    } else {
        *(s16 *)s4 = 0;
        *(u16 *)(a0 + 0x2) += 1;
    }
}




void func_8017C8B8(void *a0) {

    extern void (*D_80187708[])(void);
    D_80187708[*(u16 *)((s32)a0 + 0x2)]();
}






#include "../shared/ov/func_8017C8F4.h"






#include "../shared/ov/func_8017C940.h"





#include "../shared/ov/func_8017CA34.h"






#include "../shared/ov/func_8017CAB4.h"






#include "../shared/ov/func_8017CB68.h"






#include "../shared/ov/func_8017CBD4__6f36e213.h"


#include "../shared/ov/func_8017CC60.h"


#include "../shared/ov/func_8017CC80__229aadd9.h"


#include "../shared/ov/func_8017CCD4.h"




void func_8017CD10(void *a0) {

    extern void (*D_80187760[])(void);
    D_80187760[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8017CD4C.h"




// @class: plumbing
// @stuck: none — signed s32 counter at 0x1C, delay-slot store is the unconditional bump

#include "../shared/ov/func_8017CD9C__85f5930d.h"



/* Entity record touched by func_8017CDF8 (offsets read straight off the asm):
 *   0x02 u16   frame/state counter (lhu / sh)
 *   0x1C s32   tick counter (lw / sw), signed compare against 0x20
 *   0x2A u16   y-ish delta, decremented by 0x10 (lhu / sh)
 *   0x2C u16   sound id passed to func_80147324 (lhu)
 *   0x30 s32   suppress flag
 */

#include "../shared/ov/func_8017CDF8__6241b634.h"


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017CE7C;


/* func_8017CE7C — entity tick with a two-mode "hit/shake" arm.
 *   +0x1C s32  frame counter (lw / sw), signed compare against 0x20
 *   +0x34 ptr  sub-object read up-front (lives in $s0 across the jals)
 *   +0x30 s32  mode flag (0 = direct sub-object, else the +0x20 sub-sub-object)
 *   +0x02 u16  state word bumped in the timeout arm
 *
 * §71 sibling-first: func_8017C69C in this same TU is the identical shape —
 * counter @0x1C, sub-object @0x34, the 0x60/0x62/0x64 halfword triple and the
 * `do { func_80146A6C(0x1B, obj, ...); } while (++i < 3);` s16 loop.
 */

#include "../shared/ov/func_8017CE7C__5c1a6867.h"


extern void func_8017D030(int);
extern void func_80146C3C();
void func_8017CFE4(int param_1)
{
    unsigned short uVar1;
    uVar1 = *(unsigned short *)(param_1 + 0x12) - 0x100;
    *(unsigned short *)(param_1 + 0x12) = uVar1;
    if ((short)uVar1 > 0) {
        func_8017D030(param_1);
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017D030;


/* func_8017D030 — 4-point primitive sweep driven by the 44-byte curve table
 * D_80187734.  Builds a rotation matrix from the entity's angle @0x12, then a
 * translation from the sub-object @0x34, then walks the table three times
 * (10 x stride-4, 20 x stride-2, 20 x stride-2 guarded by the s16 @0x2A).
 */



           /* 0x34 */

            /* 0x20 */

extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);

void func_8017D030(int param_1)
{

    extern u16 D_800B99DA;
    extern u8  D_80187734[];
    SVec8_8017C218 rot;
    s32   pad0[2];
    Prim_8017C218  prim;
    s32   pad1[1];
    Mtx_8017C218   mtx;
    s32   pad2[8];
    s32   obj;
    u8   *p;
    s16   i;
    s32   c;

    obj = *(s32 *)(param_1 + 0x34);
    rot.vx = rot.vy = rot.vz = *(u16 *)(param_1 + 0x12);
    func_80017DC4(&rot, &mtx);

    prim.v[1].vx = prim.v[1].vy = prim.v[1].vz = 0;
    prim.v[0].vy = prim.v[2].vy = prim.v[3].vy = 0;
    prim.c[1].r = prim.c[1].g = prim.c[1].b = 0;

    c = ((s32)(s16)*(u16 *)(param_1 + 0x12) >> 5) + 0x20;
    prim.c[0].r = prim.c[0].g = prim.c[0].b =
    prim.c[2].r = prim.c[2].g = prim.c[2].b =
    prim.c[3].r = prim.c[3].g = prim.c[3].b = c;
    if (D_800B99DA & 1) {
        prim.c[0].r = prim.c[2].r = prim.c[3].r = prim.c[3].r >> 1;
    }

    prim.code = 0x50000000;
    rot.vx = *(u16 *)(obj + 0x6);
    rot.vy = *(u16 *)(obj + 0xA) - 8;
    rot.vz = *(u16 *)(obj + 0xE);
    func_80017E68(&rot, &mtx);

    p = D_80187734;
    i = 0;
    do {
        prim.v[0].vx = (s8)*p++;
        prim.v[0].vz = (s8)*p++;
        prim.v[2].vx = (s8)*p++;
        prim.v[2].vz = (s8)*p++;
        prim.v[3].vx = (s8)*p++;
        prim.v[3].vz = (s8)*p--;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 10);

    prim.c[0].r = prim.c[0].g = prim.c[0].b = 0;
    p = D_80187734;
    i = 0;
    do {
        prim.v[2].vx = (s8)*p++;
        prim.v[0].vx = prim.v[2].vx << 1;
        prim.v[2].vz = (s8)*p++;
        prim.v[0].vz = prim.v[2].vz << 1;
        prim.v[3].vx = (s8)*p++;
        prim.v[1].vx = prim.v[3].vx << 1;
        prim.v[3].vz = (s8)*p--;
        prim.v[1].vz = prim.v[3].vz << 1;
        func_80017758(&prim, &mtx);
        i++;
    } while (i < 0x14);

    if (*(s16 *)(param_1 + 0x2A) != 0) {
        p = D_80187734;
        i = 0;
        do {
            prim.v[0].vx = prim.v[2].vx = (s8)*p++;
            prim.v[0].vz = prim.v[2].vz = (s8)*p++;
            prim.v[1].vx = prim.v[3].vx = (s8)*p++;
            prim.v[1].vz = prim.v[3].vz = (s8)*p--;
            prim.v[0].vy = prim.v[1].vy = *(u16 *)(param_1 + 0x2A);
            func_80017758(&prim, &mtx);
            i++;
        } while (i < 0x14);
    }
}




void func_8017D33C(void *a0) {

    extern void (*D_80187774[])(void);
    D_80187774[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8017D378__f93a4aa3.h"


#include "../shared/ov/func_8017D3B8__55df4134.h"


void func_80147324(s32 arg0);
void func_80147084(s32 *a0);
void func_801472B4(void *a0);
void func_8017D030(int param_1);

#include "../shared/ov/func_8017D428__db524090.h"


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017D4B4;

/* §71 sibling-first: the state-machine "tick" shape of func_8017C610 / func_8017F2E0
 * (src/ov_SC03_119/ov_SC03_119_jr_8017AE2C.c L3712) — read the frame counter at
 * +0x1C, store counter+1, branch on the OLD value, else-arm resets the counter and
 * bumps the state word at +0x2, then tail-calls the shared advance helper.
 * §3-T4: target is `slti 0x20 ; beqz else` => `if (t < 0x20) { then } else { reset }`. */

#include "../shared/ov/func_8017D4B4__7ab6a3b9.h"


extern void func_8017D030(int);
extern void func_80146C3C(u8*);
void func_8017D588(void *a0)
{
    void *obj;
    s16 v;
    v = *(u16 *)((s32)a0 + 0x12) - 0x100;
    obj = *(void **)((s32)a0 + 0x34);
    *(s16 *)((s32)a0 + 0x12) = v;
    if (v > 0) {
        ((void (*)(void *))func_8017D030)(a0);
    } else {
        *(s16 *)((s32)obj + 0x64) = 0x1000;
        *(s16 *)((s32)obj + 0x62) = 0x1000;
        *(s16 *)((s32)obj + 0x60) = 0x1000;
        ((void (*)(void))func_80146C3C)();
    }
}




void func_8017D5DC(void *a0) {

    extern void (*D_80187788[])(void);
    D_80187788[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8017D618 — spawn/scatter tick for the +0x34 sub-object (state word @0x2).
 * MATCH (45 ins), match_one + rtu_match. Four levers, in the order they were found:
 *
 * 1. §71 sibling-first — same entity shape as func_8017C610 / func_8017C69C in this
 *    TU: sub-object pointer @0x34 read BEFORE the call (it lives in $s1 across the
 *    jal), state word @0x2 bumped last. §3-T4: `beqz $v1,else` => `if (p->f2C) {..}`.
 *    ONE rand() feeds three fields; the raw low 6 bits use a bare `andi` (no extend)
 *    while the >>12 / >>6 uses share one `sll $x,16` — that shared sign-extend is
 *    what forces `r` to be a `short` local rather than an int.
 *
 * 2. §5a CROSS-JUMP — both arms end in `sh ?,0xA($s0)`; gcc tail-merged them (23 off).
 *    They only stay separate because the loaded halfword lands in a DIFFERENT hard
 *    reg per arm, which needs (a) the load to be its own statement at the TOP of each
 *    arm and (b) a SEPARATE temp per arm (t / t2) — one shared temp is one pseudo,
 *    gets one register in both arms, and re-merges. 23 -> 10 -> 6.
 *
 * 3. +0x16 is SIGNED: the target materialises -0x20 as `addiu $v0,$zero,-0x20`, not
 *    `ori 0xffe0`, so that store must go through an s16.
 *
 * 4. §49 BIRTHING BOOST (the last 6 -> 2 -> 0). Residual was two ALU insns swapped
 *    with identical registers; source statement order does NOT flip it, because
 *    sched1's `adjust_priority`/`birthing_insn_p` hands every SET(REG,..) whose dest
 *    has REG_N_SETS==1 a 0x7f000001 priority, so it sinks to just before its consumer
 *    and fixes the .greg LUID order that sched2's tie-break then reads.
 *    THE DIAL: give the offending insn's dest a SECOND set so it loses the boost —
 *    here one `u16 d` reused by both tail statements. It must be a THIRD temp, not
 *    `c` itself: writing `c = c + 1;` also un-boosts c's LOAD, which then starves to
 *    the front of the block and swaps the two `lhu`s instead. Boost the loads, starve
 *    the arithmetic. */

#include "../shared/ov/func_8017D618__744f5451.h"


void func_800D22E4(s32 a0);
void func_8017D728(void *a0);
void func_80146C3C(u8 *a0);

void func_8017D6CC(void *a0)
{
    s32 *ptr = (s32 *)((u8 *)a0 + 0x1C);
    s32 v0 = *ptr;
    *ptr = v0 + 1;

    if (v0 < 0xA) {
        func_800D22E4((s32)a0);
        func_8017D728(a0);
    } else {
        func_80146C3C((u8 *)a0);
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017D728;


#include "../shared/ov/func_8017D728__81ba1d70.h"


/* Tier-1 structural transcription of func_8017D898 (ov_SC02_037).
 *
 * NOTE: the Ghidra scaffold at .run/ghidra_c/func_8017D898.c does NOT match
 * this asm at all (wrong function / stale seed — completely different
 * control flow, a short-array collision routine vs. this GTE particle/quad
 * renderer). It was discarded rather than adapted.
 *
 * Instead this is a known structural sibling: func_8017D898 is a shared
 * "jr" routine that recurs verbatim (module-address-identical) across many
 * overlays. It is ALREADY matched, byte-for-byte, at:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017D898.c (lines 2811-3167)
 * That C body was checked mnemonic-by-mnemonic against this binary's asm
 * (prologue loads, the (*(u8 * *)&D_800A5E60)/D_800B9A02/D_800A6610 globals, the 8/0xC/
 * 0x10/0x64 struct-field offsets, the bbox min/max ladders, the switch's 4
 * OT-tag constants 0x4000000/0x7000000/0x5000000/0x9000000 in F3/FT3/F4/FT4
 * order, and the pkt/prim increments 0x14/0x20/0x18/0x28) and lines up
 * exactly, so it is transcribed here as-is (no #includes; types/macros/
 * externs inlined at file scope per the tier-1 contract). Byte-level
 * register allocation / scheduling for THIS overlay's copy is left to the
 * next tier.
 */
















extern s32 func_800491EC(void);
extern void func_800547D8(s32, MATRIX2 *);
extern void func_80052E38(MATRIX2 *);
extern s32 D_800A5E60;
extern u8 D_800A6610[];
extern short D_800B9A02;
















void func_8017D898(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = (*(u8 * *)&D_800A5E60);
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

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
                if ((s16)mxc >= -0x78 && (s16)mnc < 0x79) {
                    prim = (Prim *)part->prim;
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
                                case 4:
                                case 5:
                                    gte_stsxy3_f3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyF3 *)pkt)->x0 > ((PolyF3 *)pkt)->x1) {
                                        mx = ((PolyF3 *)pkt)->x0;
                                        mn = ((PolyF3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF3 *)pkt)->x0;
                                        mx = ((PolyF3 *)pkt)->x1;
                                    }
                                    if (((PolyF3 *)pkt)->x2 > mx) mx = ((PolyF3 *)pkt)->x2;
                                    else if (((PolyF3 *)pkt)->x2 < mn) mn = ((PolyF3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyF3 *)pkt)->y0 > ((PolyF3 *)pkt)->y1) {
                                            my = ((PolyF3 *)pkt)->y0;
                                            mny = ((PolyF3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyF3 *)pkt)->y0;
                                            my = ((PolyF3 *)pkt)->y1;
                                        }
                                        if (((PolyF3 *)pkt)->y2 > my) my = ((PolyF3 *)pkt)->y2;
                                        else if (((PolyF3 *)pkt)->y2 < mny) mny = ((PolyF3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 4) g.opz = za + 0x200;
                                            ((PolyF3 *)pkt)->rgbc = prim->w0;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x14;
                                        }
                                    }
                                    break;
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3 *)pkt)->x0 > ((PolyFT3 *)pkt)->x1) {
                                        mx = ((PolyFT3 *)pkt)->x0;
                                        mn = ((PolyFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3 *)pkt)->x0;
                                        mx = ((PolyFT3 *)pkt)->x1;
                                    }
                                    if (((PolyFT3 *)pkt)->x2 > mx) mx = ((PolyFT3 *)pkt)->x2;
                                    else if (((PolyFT3 *)pkt)->x2 < mn) mn = ((PolyFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3 *)pkt)->y0 > ((PolyFT3 *)pkt)->y1) {
                                            my = ((PolyFT3 *)pkt)->y0;
                                            mny = ((PolyFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3 *)pkt)->y0;
                                            my = ((PolyFT3 *)pkt)->y1;
                                        }
                                        if (((PolyFT3 *)pkt)->y2 > my) my = ((PolyFT3 *)pkt)->y2;
                                        else if (((PolyFT3 *)pkt)->y2 < mny) mny = ((PolyFT3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x200;
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 0:
                                case 1:
                                    gte_stsxy3_f3(pkt);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (((PolyF4 *)pkt)->x0 > ((PolyF4 *)pkt)->x1) {
                                        mx = ((PolyF4 *)pkt)->x0;
                                        mn = ((PolyF4 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF4 *)pkt)->x0;
                                        mx = ((PolyF4 *)pkt)->x1;
                                    }
                                    if (((PolyF4 *)pkt)->x2 > mx) mx = ((PolyF4 *)pkt)->x2;
                                    else if (((PolyF4 *)pkt)->x2 < mn) mn = ((PolyF4 *)pkt)->x2;
                                    if (((PolyF4 *)pkt)->y0 > ((PolyF4 *)pkt)->y1) {
                                        my = ((PolyF4 *)pkt)->y0;
                                        mny = ((PolyF4 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF4 *)pkt)->y0;
                                        my = ((PolyF4 *)pkt)->y1;
                                    }
                                    if (((PolyF4 *)pkt)->y2 > my) my = ((PolyF4 *)pkt)->y2;
                                    else if (((PolyF4 *)pkt)->y2 < mny) mny = ((PolyF4 *)pkt)->y2;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                        if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                        else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                            else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb, zc;
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                zc = za;
                                                if (zc < zb) zc = zb;
                                                g.opz = zc;
                                                ((PolyF4 *)pkt)->rgbc = prim->w0;
                                                otp = (u32 *)(((zc >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x18;
                                            }
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
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x200;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
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
    (*(u8 * *)&D_800A5E60) = pkt;
}




void func_8017E778(void *a0) {

    extern void (*D_80187808[])(void);
    D_80187808[*(u8 *)((s32)a0 + 0x15)]();
}


extern void func_8017E9C4();
extern void func_800167B8(s32 a0);

s32 func_8017E7B4(s32 a0)
{
    func_8017E9C4(a0);
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


int func_800167F0(int arg);

#include "../shared/ov/func_8017E7F8__511a8b68.h"




void func_8017E81C(void *a0) {

    extern void (*D_80187810[])(void);
    D_80187810[*(u8 *)((s32)a0 + 0x15)]();
}






extern void func_8017E9EC(void);

s32 func_8017E858(s32 a0) {
    func_8017E9EC();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E898(u8 *a0) {
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


#include "../shared/ov/func_8017E914__37f67f3a.h"




void func_8017E934(void *a0) {

    extern void (*D_8018781C[])(void);
    D_8018781C[*(u8 *)((s32)a0 + 0x15)]();
}





extern void func_800D1E28(void);

s32 func_8017E970(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;

    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }

    return 0;
}


    extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
    extern s32 D_80187828(void *a0);
    void func_8017E9C4(void) {
        ((void (*)(void *, s32))func_8016EE40)((void *)D_80187828, 0x1000000);
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E9EC(void) {

    extern s32 D_8018782C(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018782C, 0x1000000);
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);

void func_8017EA14(void) {

    extern s32 D_80126954;
    extern s32 D_80126950;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern void func_8017EB88(void *a0);
    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x238;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017EB88, 0);
    func_8012A094((s32)D_80126948);
    func_8017EB88(D_80126948);
}


void func_8017EAB4(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern void func_8012A018(s32 a, s32 b);
    extern void func_8012A094(s32 a0);
    extern void func_8017EB88(void *a0);
    D_80126954 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0xE3;
    D_8012696A = 0x221;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x40;
    D_8012697A = 0;
    ((void (*)(void *, s32))func_8012A018)((void *)func_8017EB88, 0x1);
    func_8012A094((s32)D_80126948);
    func_8017EB88((void *)D_80126948);
}


void func_8017EB50(void) {
    extern void func_8012A018(s32 a0, s32 a1);
    extern void func_8017EB88(void *a0);
    extern u8 D_80126948[];

    func_8012A018((s32)func_8017EB88, 2);
    func_8017EB88(D_80126948);
}




void func_8017EB88(void *a0) {

    extern void (*D_80187840[])(void);
    D_80187840[*(u8 *)((s32)a0 + 0x4)]();
}











extern s32 D_80126B58;
extern s32 *D_80126B78;
extern s16 D_80126940;
extern u16 func_80148800(s32 *a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8017EEC4(s32 arg0, void *arg1);

void func_8017EBC4(s32 param_1)
{
    extern s16 D_8018784C[];
    Unaligned8 sp10;
    s32 t;
    register s32 u __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    s32 a0;
    register int zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)

    if (func_80148800(&D_80126B58) & 3) {
        *(u8 *)(param_1 + 5) = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(s32 *)(param_1 + 0x14) = D_8018784C[*(u8 *)(param_1 + 5)];
    }

    sp10 = *(Unaligned8 *)&D_80126940;

    if (*(s16 *)(param_1 + 0xA0) == 0) {
        t = -func_8004787C(*(s16 *)((s32)D_80126B78 + 0x12));
        if (t < 0) {
            t += 0x1F;
        }
        *(s16 *)(param_1 + 0x2E) = t >> 5;

        t = -func_80047948(*(s16 *)((s32)D_80126B78 + 0x12));
        if (t < 0) {
            t += 0x1F;
        }
        *(s16 *)(param_1 + 0x32) = t >> 5;

        *(s16 *)(param_1 + 0xA0) = 0x20;
    } else {
        *(s16 *)(param_1 + 0xA0) = *(s16 *)(param_1 + 0xA0) - 1;
    }

    u = -0x500 - *(u16 *)(param_1 + 0x28);
    a0 = u + zr;
    if ((u << 16) >> 16 > *(s16 *)&sp10.a) {
        *(s16 *)&sp10.a = a0;
    }

    u = 0x500 - *(u16 *)(param_1 + 0x28);
    a0 = u + zr;
    if ((u << 16) >> 16 < *(s16 *)&sp10.a) {
        *(s16 *)&sp10.a = a0;
    }

    u = -0xA00 - *(u16 *)(param_1 + 0x2C);
    a0 = u + zr;
    if ((u << 16) >> 16 > *(s16 *)&sp10.b) {
        *(s16 *)&sp10.b = a0;
    }

    func_8017EEC4(param_1, &sp10);
}


extern s32 func_8017EEC4(s32 arg0, void *arg1);
extern s32 D_80187850;

void func_8017ED68(s32 arg0) {
    func_8017EEC4(arg0, &D_80187850);
}



extern s16 D_80126940;

typedef struct {
    s16 pad00[4];
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 pad1E;
    s16 f20;
    s16 f22;
    s16 f24;
    s16 pad26;
    s16 f28;
    s16 f2A;
    s16 f2C;
    s16 f2E;
    s16 f30;
    s16 f32;
} St_8017ED90;

extern s32 func_8017EEC4(s32 arg0, void *arg1);
extern s32 func_800130D0(s32 arg0, s32 arg1, s32 arg2);

void func_8017ED90(St_8017ED90 *arg0)
{
    Unaligned8 sp10;
    s16 var_s0;
    s16 var_s1;
    s16 var_s2;

    sp10 = *(Unaligned8 *)&D_80126940;
    var_s0 = func_80012C6C(((s16 *)arg0)[4], 500, 32);
    arg0->f08 = arg0->f0C = var_s0;
    var_s1 = func_80012C6C(((s16 *)arg0)[8], 1200, 32);
    arg0->f10 = arg0->f14 = var_s1;
    var_s2 = func_80012DBC(arg0->f18, 568, 16, 1);
    arg0->f18 = arg0->f20 = var_s2;
    arg0->f1A = arg0->f22 = func_80012DBC(arg0->f1A, 2048, 16, 1);
    arg0->f1C = arg0->f24 = func_80012DBC(arg0->f1C, 0, 16, 1);
    arg0->f28 = arg0->f2E = func_800130D0(arg0->f28, 0, 32);
    arg0->f2A = arg0->f30 = func_800130D0(arg0->f2A, 0, 32);
    arg0->f2C = arg0->f32 = func_800130D0(arg0->f2C, 0, 32);
    func_8017EEC4(arg0, &sp10);
}


extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_800130D0(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);




s32 func_8017EEC4(s32 arg0, void *arg1)
{
    s16 *param_2 = (s16 *)arg1;
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(arg0 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(arg0 + 0x8),  (s32)*(s16 *)(arg0 + 0xC),  4);
    *(s32 *)(arg0 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(arg0 + 0x10), (s32)*(s16 *)(arg0 + 0x14), 4);
    *(s16 *)(arg0 + 0x18) = func_80012ABC((s32)*(s16 *)(arg0 + 0x18), (s32)*(s16 *)(arg0 + 0x20), 4);
    *(s16 *)(arg0 + 0x1A) = func_80012ABC((s32)*(s16 *)(arg0 + 0x1A), (s32)*(s16 *)(arg0 + 0x22), 4);
    *(s16 *)(arg0 + 0x1C) = func_80012ABC((s32)*(s16 *)(arg0 + 0x1C), (s32)*(s16 *)(arg0 + 0x24), 4);
    *(s16 *)(arg0 + 0x28) = func_800130D0((s32)*(s16 *)(arg0 + 0x28), (s32)*(s16 *)(arg0 + 0x2E), 4);
    *(s16 *)(arg0 + 0x2A) = func_800130D0((s32)*(s16 *)(arg0 + 0x2A), (s32)*(s16 *)(arg0 + 0x30), 4);
    *(s16 *)(arg0 + 0x2C) = func_800130D0((s32)*(s16 *)(arg0 + 0x2C), (s32)*(s16 *)(arg0 + 0x32), 4);
    *(s32 *)(arg0 + 0x48) = (s32)*(s16 *)(arg0 + 0x28) + (s32)param_2[0];
    *(s32 *)(arg0 + 0x4C) = (s32)*(s16 *)(arg0 + 0x2A) + (s32)param_2[1];
    *(s32 *)(arg0 + 0x50) = (s32)*(s16 *)(arg0 + 0x2C) + (s32)param_2[2];
    func_80049CAC(arg0 + 0x18, (s32)&m1);
    m1.t[0] = *(s16 *)(arg0 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(arg0 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(arg0 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(arg0 + 0x10);
    func_8012F14C((s32)&m1, (s32)&svec_in, (s32)&svec_out);
    *(s32 *)(arg0 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(arg0 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(arg0 + 0x44) = (s32)svec_out.vz;
}


extern void func_8017F07C(void);
void func_8017F05C(void) {
    func_8017F07C();
}


void func_8017F07C(void) {
    extern s32 D_801C9A5C;
    extern s32 D_801C9968;
    extern s32 D_801C996C;
    extern s32 D_801C9970;
    extern s32 D_801C9974;
    extern u8 D_801A041C[];
    extern s32 D_80187858[];
    extern void func_8017F1B8(void *a0, s32 a1);

    switch (D_801C9A5C) {
    case 0:
        D_801C9968 = 1;
        D_801C996C = 0;
        D_801C9970 = 1;
        D_801C9974 = 1;
        D_801C9A5C = 1;
        break;
    case 1:
        if (--D_801C9968 == 0) {
            D_801C9968 = 2;
            func_8017F1B8(D_801A041C, D_801C996C * 6);
            D_801C996C = (D_801C996C + 1) & 7;
        }
        if (--D_801C9970 == 0) {
            D_801C9970 = 8;
            func_800183E0(D_80187858[D_801C9974]);
            D_801C9974 = (D_801C9974 + 1) & 0xF;
        }
        break;
    }
}



void func_8017F1B8(void *a0, s32 a1)
{
    s32 offset;
    s16 buf[4];
    u16 t0, t1, t2, t3;
    u16 *ptr;

    offset = a1 << 1;
    ptr = (u16 *)((s32)offset + (s32)a0);

    t0 = ptr[0];
    buf[0] = t0;

    t1 = ptr[1];
    buf[1] = t1;

    t2 = ptr[2];
    buf[2] = t2;

    t3 = ptr[3];
    buf[3] = t3;

    MoveImage(buf, ptr[4], ptr[5]);
}




void func_8017F218(void *a0) {

    extern void (*D_801878DC[])(void);
    D_801878DC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012DFD4(u8*);

void func_8017F254(void *a0) {

    extern void (*D_8018793C[])(void);
    D_8018793C[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        ((void (*)(void *))func_8012DFD4)(a0);
    }
}


extern void func_8001FC08();

void func_8017F2B4(s32 param_1_a0)
{
    register s32 param_1 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus9)
    s32 base;
    s32 diff;
    s32 quot;
    u8 val;
    u8 *p;
    s32 negc;
    u8 lo;
    register u8 hi __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    param_1 = param_1_a0;

    if (*(s16 *)(param_1 + 0xA) < 0xC0) {
        diff = 0xC0 - *(s16 *)(param_1 + 0xA);
        quot = (diff * 63) / 0xC0;
        __asm__("addiu %0, %1, 0x50" : "=r"(val) : "r"(quot));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        if (val >= 0x7F) {
            val = 0x7F;
        }

        base = *(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x24) + 0x0);
        p = (u8 *)base;
        __asm__("nop\n\taddiu %0, %1, 0x35" : "=r"(p) : "r"(p));  // !FAKE: instruction nop — REFUSED instruction `nop` has no C spelling in the table (P36 rung B tus9)
        *p = val;
        __asm__("addiu %0, %1, 4" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = val;
        __asm__("addiu %0, %1, 0x1C" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = val;
        __asm__("addiu %0, %1, 4" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = val;
        __asm__("addiu %0, %1, 0x1C" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = val;
        __asm__("addiu %0, %1, 4" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = val;
        p = (s32)p + 0x1C;
        *p = val;
        p[4] = val;

        {
            s32 x = -(s32) * (u16 *)(param_1 + 0xA);
            __asm__("addu %0, %1, $0" : "=r"(negc) : "r"(x));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B tus9)
            if ((s16)x > 0) {
                negc = 0;
            }
        }

        {
            s32 t0 = *(s32 *)(param_1 + 0x20);
            s32 t1 = *(s32 *)(t0 + 0x24);
            s32 loW, hiW;
            __asm__ __volatile__("addu %0, %1, $0" : "=r"(loW) : "r"(negc));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B tus9)
            base = *(s32 *)(t1 + 0x0);
            __asm__ __volatile__("srl %0, %1, 8" : "=r"(hiW) : "r"(negc));  // !FAKE: instruction srl — NEEDED DIFFERS (P36 rung B tus9)
            lo = (u8)loW;
            hi = (u8)hiW;
        }
        p = (u8 *)base;
        __asm__("addiu %0, %1, 0xCA" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = lo;
        __asm__("addiu %0, %1, 1" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = hi;
        __asm__("addiu %0, %1, 0x17" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = lo;
        __asm__("addiu %0, %1, 1" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = hi;
        __asm__("addiu %0, %1, 0xF" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = lo;
        __asm__("addiu %0, %1, 1" : "=r"(p) : "r"(p));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B tus9)
        *p = hi;
        p = (s32)p + 0xF;
        *p = lo;
        p[1] = hi;

        func_8001FC08(*(s32 *)(param_1 + 0x20));
    }
}


extern s32 func_8012C0EC(s32 a0);
extern void func_8017F2B4(s32 a0);

void func_8017F3F8(void *a0) {
    extern void (*D_80187988[])(void *);

    if (func_8012C0EC((s32)a0) == 0) {
        D_80187988[*(u16 *)((s32)a0 + 0x2)](a0);
        if (*(u16 *)((s32)a0 + 0x0) != 0) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) &= 0x7FFFFFFF;
            func_8017F2B4((s32)a0);
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) |= 0x80000000;
        }
    }
}


void func_8017F490(s32 a0) {
    extern void (*D_801878A8[])(void);
    extern u8 D_80183F38[];
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);

    s32 s0;
    s32 t;
    s32 t1;
    s32 t2;

    t = func_8012C354(a0, (s32)D_801878A8);
    s0 = a0;
    if (t != 0) {
        func_8001D0E8(*(s32 *)(s0 + 0x20), 0x104, 0xF0);
        func_8012A828(s0, D_80183F38);
        *(s16 *)(s0 + 0x2) = 1;
        func_8012B030((u8 *)s0);

        t1 = func_8012C588(0x1B2, s0);
        *(s32 *)(s0 + 0xCC) = t1;
        if (t1 != 0) {
            *(s16 *)(t1 + 0x16) = -9;
            *(s16 *)(t1 + 0x1A) = 0x20;
            *(s16 *)(t1 + 0xE) = *(u16 *)(t1 + 0xE) - 0x264;
            *(s16 *)(t1 + 0xA) = *(u16 *)(t1 + 0xA) + 0x82;
        }

        t2 = func_8012C588(0x1B2, s0);
        *(s32 *)(s0 + 0xD0) = t2;
        if (t2 != 0) {
            *(s16 *)(t2 + 0x16) = -9;
            *(s16 *)(t2 + 0x1A) = -0x20;
            *(s16 *)(t2 + 0xE) = *(u16 *)(t2 + 0xE) + 0x264;
            *(s16 *)(t2 + 0xA) = *(u16 *)(t2 + 0xA) + 0x82;
        }

        *(u8 *)(s0 + 0x75) = 0;
    }
}


#include "common.h"

extern u8 D_801202A0[];
extern void func_8002D4C8(s32 a0, s32 a1);

/* func_8017F578 — scan the 0x60-entry / 0x10C-stride D_801202A0 table for a
 * type-0x12C entry whose y/x/z are within (+-0x30/-0x20, +-0x70) of a0's, and
 * if one is found flag a0 (+0xFE) and both linked objects (+0xCC/+0xD0).
 *
 * Two non-obvious gcc-2.7.2 shapes are load-bearing here (both byte-measured):
 *
 *  1. `t1 = 0x12C` is an explicit LOCAL, not a literal in the compare. As a
 *     literal, loop.c hoists the `li` into the preheader, which puts it AFTER
 *     the source-level `t0 = 1`; the target has the 0x12C first. Keeping it a
 *     source statement fixes the preheader order (13 -> 11 mismatches).
 *     Likewise `a2 += 0x10C` lives in the for-increment, not the body, so the
 *     `a3++` biv increment precedes the giv's (11 -> 9).
 *
 *  2. `va` is ONE variable reused by all three range tests, while the a0-side
 *     operand stays an inline expression. local-alloc.c:1765 (combine_regs)
 *     refuses to tie a subu's destination to operand 1 when that pseudo is not
 *     block-local, so making the minuend a multi-block (global) allocno pushes
 *     the tie onto operand 2 — which is exactly the target's
 *     `subu $v0, $v1, $v0` (dest reuses the SUBTRAHEND's register) instead of
 *     `subu $v0, $v0, $v1`. Splitting `va` into per-test temporaries, or making
 *     BOTH operands shared variables, both give the wrong register pair (9 off).
 */
void func_8017F578(s32 a0)
{
    s32 a3;
    u8 *a2;
    s32 t0;
    s32 t1;
    s32 v1p;
    s32 va;

    if (*(s16 *)(a0 + 0xFE) != 0) {
        return;
    }

    a3 = 0;
    a2 = D_801202A0;
    t1 = 0x12C;
    t0 = 1;
    for (; a3 < 0x60; a3++, a2 += 0x10C) {
        if (*(u16 *)a2 == t1) {
            va = *(s16 *)(a2 + 0xA);
            if ((u32)(va - *(s16 *)(a0 + 0xA) + 0x30) < 0x51) {
                va = *(s16 *)(a2 + 0x6);
                if ((u32)(va - *(s16 *)(a0 + 0x6) + 0x70) < 0xE1) {
                    va = *(s16 *)(a2 + 0xE);
                    if ((u32)(va - *(s16 *)(a0 + 0xE) + 0x70) < 0xE1) {
                        goto found;
                    }
                }
            }
        }
    }
    t0 = 0;

found:
    if (t0 != 1) {
        return;
    }

    v1p = *(s32 *)(a0 + 0xCC);
    if (v1p != 0) {
        *(s16 *)(v1p + 0xFC) = 9;
    }
    v1p = *(s32 *)(a0 + 0xD0);
    if (v1p != 0) {
        *(s16 *)(v1p + 0xFC) = 9;
    }
    *(s16 *)(a0 + 0xFE) = 1;
    func_8002D4C8(0x73A, 0);
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C354(s32 a0, s32 a1);

void func_8017F684(s32 param_1)
{
    extern u8 D_801878F4[];
    extern u8 D_80187934[];
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);

    s32 s0;
    s32 t;

    t = func_8012C354(param_1, (s32)D_801878F4);
    s0 = param_1;
    if (t != 0) {
        func_8001D0E8(*(s32 *)(s0 + 0x20), 0x104, 0xF0);
        func_8012A828(s0, D_80187934);
        *(s16 *)(s0 + 0x2) = 1;
        *(u8 *)(s0 + 0x75) = 0;
        func_8012B2CC(s0);
    }
}


void func_8017F6EC(s32 *a0)
{
    if (*(s16 *)((s32)a0 + 0xFC) != 0) {
        *(s16 *)((s32)a0 + 0xFC) = *(s16 *)((s32)a0 + 0xFC) - 1;
        *(u16 *)((s32)a0 + 0xE) += *(u16 *)((s32)a0 + 0x1A);
        *(u16 *)((s32)a0 + 0xA) += *(u16 *)((s32)a0 + 0x16);
    }
}


extern s32 func_8012C354(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B2CC(s32);
extern u8 D_80183F38[];
extern void (*D_80187954[])(void);

void func_8017F734(s32 param_1) {
    if (func_8012C354(param_1, (s32)D_80187954) != 0) {
        func_8012A828(param_1, (void *)D_80183F38);
        *(s16 *)(param_1 + 0x2) = 1;
        *(u8 *)(param_1 + 0x75) = 0;
        *(s32 *)(param_1 + 0xDC) = *(s32 *)(param_1 + 8);
        func_8012B2CC(param_1);
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012DFD4(u8 *a0);

void func_8017F798(s32 a0)
{
    s32 v0;
    s32 v1;

    if (*(u8 *)(a0 + 0x74) != 0) {
        if (*(s16 *)(a0 + 0x84) == 0) {
            func_8002D4C8(0xA08, 0);
            *(s16 *)(a0 + 0x84) = 1;
        }
        func_8012DFD4((u8 *)a0);
        v0 = *(s32 *)(a0 + 0x8);
        v1 = 0x20000;
    } else {
        if (*(s16 *)(a0 + 0x84) != 0) {
            func_8002D4C8(4, 0xA08);
            *(s16 *)(a0 + 0x84) = 0;
        }
        v1 = *(s32 *)(a0 + 0x8);
        v0 = *(s32 *)(a0 + 0xDC);
        if (v1 < v0) {
            return;
        }
        v0 = -0x8000;
    }
    *(s32 *)(a0 + 0x8) = v1 + v0;
}



s32 func_8017F83C(void) {
    return 72;
}



/* func_8017F844 — "spawn a paired effect entity above/below the actor" template
 * (family exemplar, 15 members / 1455 templatable instructions).
 *
 * Declaration provenance (all verified against the whole TU in one pass, cookbook §135-8):
 *   ((void (*)(s32, s32))func_8012A828)(s32,s32)          — TU col-0 decl (lines 3488/3771/…/4781), identical form
 *   func_8012C658(s32,s32,s32)      — TU col-0 decl (lines 2524/3721/3772/4935)
 *   func_8012C218(void *)           — TU col-0 decl (lines 3545/4016/…/5226)
 *   func_8012B030(u8 *)             — TU col-0 decl (line 4208)
 *   func_8012CEB0(s32,s32,s32)      — TU fn-scope decl (line 4404), same signature
 *   func_8002AC00(s32)              — TU fn-scope decl (line 5085), same signature
 *   func_8001C214(s32,s32)          — NOT declared in this TU; form copied from
 *                                     src/shared/engine_core.h:8751 so it can never clash
 *   D_801A9DAC / D_801B14F0         — real dlabels in asm/ov_SC02_026/data/tail.data.s
 *                                     (0x801B5A4C / 0x801BD190), declared nowhere else
 *
 * Codegen notes (each closed a residual):
 *  - The buf[8] halfword-pair setup is the byte-verified twin of func_801843AC in THIS TU
 *    (line 4403): the three $2/$3/$7 register pins reproduce the original's temp allocation,
 *    and the doubled buf[1]/buf[5] stores are real — the ±8 adjust is a second store, so the
 *    scheduler emits sh/sh then sh/sh with a single lhu of a0+0xA (cookbook §135-4: the list
 *    scheduler preserves the relative order of disambiguable stores).
 *    Third temp lands in $a3 (not $a2 as in func_801843AC) because $a2 is already pinned to
 *    the literal-0 third argument here.
 *  - `>= 0x10` (not `< 0x10` with swapped arms) is what puts the func_8012C218 arm in the
 *    fall-through position and the func_8012B030 arm behind the `j`.
 *  - The `s16 t` temp on line ~72 is load-BEFORE-stores in SOURCE. Without it the lhu of
 *    a0+0x100 cannot hoist above the two ent-relative stores — §135-2's MEM_IN_STRUCT_P
 *    escape does NOT apply here because those stores have varying (register) addresses, so
 *    true_dependence() keeps the edge. Source order is the only lever; costs one nop otherwise.
 *  - The do/while's `sll/sra` pair is CSE store-forwarding: `*(u16*)` read for the += keeps
 *    the HImode load (result is truncated), then the signed compare must materialize the
 *    sign extension of the just-stored register.
 */

extern void func_8002AC00(s32 arg0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C218(void *a0);
extern s32 func_8012B030(u8 *a0);

void func_8017F844(void *a0) {

    extern s32 D_801A9DAC;
    extern s32 D_801B14F0;
    u16 buf[8];
    s32 ent;
    u16 saved;
    u16 v0;
    u16 v1;
    u16 a3;
    u16 tmp0;

    func_8002AC00(0xD);
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        tmp0 = *(u16 *)((s32)a0 + 0x6);
        v0 = tmp0;
        buf[0] = v0;
        buf[4] = v0;

        v1 = *(u16 *)((s32)a0 + 0xA);
        v0 = v1 - 8;
        buf[1] = v1;
        buf[5] = v1;

        a3 = *(u16 *)((s32)a0 + 0xE);
        buf[1] = v0;
        buf[5] = (v1 + 8);
        buf[2] = a3;
        buf[6] = a3;

        if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) == 0) {
            if ((*(s16 *)((s32)a0 + 0x100) & 0x8000) == 0) {
                saved = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)&D_801A9DAC);
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B14F0);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = saved;
                ent = func_8012C658(0x12C, 1, (s32)a0);
                if (ent != 0) {
                    if (*(s16 *)((s32)a0 + 0xA) >= 0x10) {
                        func_8012C218((void *)ent);
                    } else {
                        *(u16 *)(*(s32 *)(ent + 0x20) + 0x12) = saved;
                        func_8012B030((u8 *)ent);
                        if (*(s16 *)((s32)a0 + 0x70) == 5) {
                            s16 t = *(s16 *)((s32)a0 + 0x100);
                            *(s16 *)(ent + 0x70) = 6;
                            *(s16 *)(ent + 0xFE) = 1;
                            *(s16 *)(ent + 0x100) = t;
                            do {
                                func_8012C658(0x12F, 5, ent);
                                *(s16 *)(ent + 0xFE) = *(u16 *)(ent + 0xFE) + 3;
                            } while (*(s16 *)(ent + 0xFE) < 0x10);
                            *(s16 *)(ent + 0xFE) = 0;
                        }
                    }
                }
            }
        }
    }
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_80143970(s32);
extern void func_8012A828(s32, void*);
extern void func_8012B23C(s32);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_8017F9C8(void *a0) {

    extern u8 D_801A3A18[];
    extern u8 D_801B03F8[];
    extern u8 D_801AFCC0[];
    extern char D_801B1370[];
    extern u8 D_801B11F0[];
    extern s32 D_801A3B50;
    extern s32 D_801A3BF0;
    extern s32 D_801A3C38;

    s16 state = *(s16 *)((s32)a0 + 0x70);

    if (func_8012C354((s32)a0, (s32)(D_801A3A18 + state * 0x34)) == 0) {
        func_8012CAE4((void *)a0);
    } else {
        s16 state2;
        u16 saved;

        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xB4) = -0x401;
        ((void (*)(void *))func_80143970)((void *)a0);

        state2 = *(s16 *)((s32)a0 + 0x70);
        switch (state2) {
            case 0:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801B03F8);
                *(s16 *)((s32)a0 + 0x2) = 1;
                ((void (*)(void *))func_8012B23C)((void *)a0);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3B50;
                *(s16 *)((s32)a0 + 0xFC) = 0;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 2:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801AFCC0);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s16 *)((s32)a0 + 0x2) = 9;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3BF0;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 1:
            case 3:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B1370);
                *(s16 *)((s32)a0 + 0x2) = 6;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3C38;
                break;
            case 4:
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801B03F8);
                *(s16 *)((s32)a0 + 0x2) = 0xD;
                ((void (*)(void *))func_8012B23C)((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3B50;
                *(s16 *)((s32)a0 + 0xFC) = 0x1E;
                break;
            case 5:
                if (*(s16 *)((s32)a0 + 0xFC) != 0) {
                    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801B11F0);
                    *(s16 *)((s32)a0 + 0x2) = 0xE;
                    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = rand() & 0xFFF;
                } else {
                    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801B03F8);
                    *(s16 *)((s32)a0 + 0x2) = 1;
                }
                ((void (*)(void *))func_8012B23C)((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3B50;
                *(s16 *)((s32)a0 + 0xFE) = 1;
                do {
                    func_8012C658(0x12F, 5, (s32)a0);
                    *(s16 *)((s32)a0 + 0xFE) = *(u16 *)((s32)a0 + 0xFE) + 1;
                } while (*(s16 *)((s32)a0 + 0xFE) < 6);
                *(s16 *)((s32)a0 + 0xFE) = 0;
                break;
            }
        func_8012B2CC((s32)a0);
    }
}

    typedef struct {
        u16 x, y, z, w;
    } V8_8017FBEC;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017FBEC;

/* func_8017FBEC — ov_SC02_026 / ov_SC02_026_jr_8017C180.c   MATCH (237 ins)
 *
 * §136c SIBLING-FIRST provenance (nothing here was derived from the .s that could be copied):
 *   - the func_8004787C / func_80047948 / func_80133784 trig+collide block is copied VERBATIM
 *     from the already-banked SAME-TU sibling func_80183B04 (TU:4468), including the
 *     `s32 r; r = 0x30;` non-const multiplier (T1) and the `V8_8017FBEC {u16 x,y,z,w}` locals.
 *   - the RotTransPers + positional-sound block follows the byte-proven RTP_SND() macro in
 *     src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.c:3480 — in particular the $a0-PINNED SCOPES on
 *     &D_800AF648, which rematerialise the lui/addiu before EACH call instead of letting CSE
 *     hoist the address into a callee-saved pseudo.
 *   - the `*(u16*)(*(s32*)(a0+0x20)+0x12) = *(u16*)(...) + d;` accumulate form is copied from
 *     the SAME-TU sibling func_80180C80 (TU:3936).
 *
 * THE FOUR LEVERS THAT CLOSED IT (each one MOVED the count; recorded for the cookbook):
 *
 *  1. §136 L1 — `r = 0x30` MUST BE ITS OWN LOCAL, and the two func_8012B608 results must be
 *     per-arm block-scoped locals (`s32 d`).  Sharing one `s32 r` across all three sites makes
 *     it a GLOBAL allocno; as a BLOCK-LOCAL one it is handed $s0 by local-alloc (which runs
 *     BEFORE global-alloc), which then forces the actor — it conflicts with r — onto $s1 and
 *     lets `anim` (which does not conflict) take $s0.  One shared local ⇒ $s0/$s1 swapped
 *     across the ENTIRE function (98 mismatches).
 *
 *  2. BLKmode STACK SLOTS ARE ROUNDED TO 8.  `u16 sxy[2]` (4 bytes) occupies EIGHT bytes and
 *     pushed z/flag from sp+0x4C/0x50 to sp+0x50/0x54.  A scalar `s32 sxy` read through
 *     `*(u16 *)&sxy` keeps the 4-byte slot.  (Same reason the RTP_SND sibling packs its
 *     sxy/z/flag into ONE struct.)  `s32 mv[4]` + `V8_8017FBEC pad[2]` are the 0x10..0x2F filler that
 *     makes vars = 0x48 ⇒ frame 0x68.
 *
 *  3. §21 ZERO-BYTE RE-TIE on `vol`.  Both magic-multiplies write the same match_scratch, so
 *     sched1 (the PRE-reload pass — verified with -fno-schedule-insns/-insns2) is free to swap
 *     them and always hoisted the PAN multiply first, inverting the whole tail schedule and
 *     losing the mfhi→mult hazard nop.  Source statement order does NOT move it (9 spellings
 *     swept, all identical); only the re-tie does.  Worth +2 ins and 33 mismatches.
 *
 *  4. REUSE ONE VARIABLE FOR X AND PAN.  gcc-2.7.2 has no live-range splitting, so one C local
 *     == one hard register: writing `sx = (sx + 0xA0) / 0x14;` (instead of a fresh `pan`) is
 *     what keeps the pan field in $a2 — a separate `pan` local is a fresh allocno and takes the
 *     dying $v1 instead.  Register PINS on `pan` made it WORSE (6 → 10): a local `register`
 *     var is the hard reg for its whole range and evicts the block's temps.  Only `av` needed
 *     a pin ($a1).
 *     Sub-lever: `pan = pan << 8;` must be an IN-PLACE statement (`sll $a2,$a2,8`), not
 *     `(pan << 8)` in the expression — reorg can only steal the shift into the bne delay slot
 *     when it is dead on the fall-through, i.e. when dest == src.  That is the last +1 ins.
 *     Sub-lever: the OR must be spelled `vol | (0x3000 | sx)`.  fold's `associate:` rewrites
 *     `(VAR|CON)|ARG1` to `(CON|ARG1)|VAR`, which is what puts `ori ...,0x3000` on VOL and the
 *     plain `or` on the pan field — and this nesting is the only one of six spellings that
 *     also gets the commutative `or`'s operand order right.
 *
 * DECLARATION SURFACE (RE-AUDITED against the WHOLE TU — above AND below the splice point).
 *   The first audit only looked ABOVE the INCLUDE_ASM at TU:4680 and wrongly concluded that
 *   func_8012BE98 / func_8012B744 / func_8012BD3C / RotTransPers / D_800AF648 "appear nowhere".
 *   They are all declared by the banked sibling func_8018389C at TU:4846-4857, i.e. BELOW the
 *   splice, and cc1 reports only the FIRST conflict — so the byte-correct body was refused with
 *     "conflicting types for func_8012BE98 / func_8012B744".
 *   Every symbol below now carries the TU's ONE existing spelling VERBATIM; where the type
 *   disagreed with what this body wants, the disagreement is pushed to a cast at the USE site
 *   (lever A), which is zero-byte — re-verified MATCH (237 ins) after the change.
 *
 *   copied VERBATIM from their existing TU spellings —
 *     ((void (*)(s32, s32))func_8012A828)(TU:3527 et al), func_8012B608 (4163/4240/4848),
 *     func_8012B1B4 (4164/4241/4697/4849), func_8012CBA4 (4343/4699/4850),
 *     func_8004787C (2206/4700), func_80047948 (2205/4701), func_80133784 (599/4702),
 *     func_8002D4C8 (59/4855), func_8004914C / func_800491AC (2646/2647/4852/4853),
 *     RotTransPers (4854/5017), D_800AF648 (4857/5025), D_801B03F8 (5378),
 *     func_8012BD3C (4851),
 *     func_8012BE98 (4846, `extern void func_8012BE98(s32 a0, u16 *a1)`)  <- CONFORMED,
 *     func_8012B744 (4847, `extern s32 func_8012B744(void *a0, void *a1)`) <- CONFORMED.
 *   USE-SITE casts that absorb the two conformed types (same idiom as the sibling at TU:4876) —
 *     ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim)   -- void-declared, returns s32
 *     func_8012B744((void *)(a0 + 4), (void *)anim)           -- s32 args -> void * params
 *   NOT declared anywhere in the TU (so this form is free) — D_801AFD68 only.
 *     D_801AFD68 is a real dlabel in asm/ov_SC02_026/data/tail.data.s:60402.
 *   func_8017FBEC itself has NO prototype anywhere in the TU or in any included header (only
 *   the INCLUDE_ASM at 4680), so no §37/§124 asm-label alias is needed on the defined symbol.
 *   The TU includes ../shared/engine_core.h but expands ZERO DEFINE_func_*()/DEFINE_data_*()
 *   macros (verified by grep), so that header contributes no file-scope declaration here.
 *   The conformed func_8012B744 type is also the fleet-dominant one (engine_core.h:3723) and
 *   RotTransPers' is the one engine_core.h:108 uses, so both stay compatible if a macro is
 *   ever spliced in.
 */

extern void func_8012A828(s32, void*);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_8017FBEC(s32 a0) {

    extern u8 D_800AF648;
    extern u8 D_801B03F8[];
    extern u8 D_801AFD68[];
    typedef struct {
        u16 x, y, z, w;
    } V8_8017FBEC;
    s32 mv[4];   /* sp+0x10 : the 4-word block handed to func_8012B1B4 */
    V8_8017FBEC pad[2];   /* sp+0x20 : gcc's own area (vars must be 0x48 for a 0x68 frame) */
    V8_8017FBEC sp30;     /* sp+0x30 : func_80133784 arg1 */
    V8_8017FBEC sp38;     /* sp+0x38 : func_80133784 arg2 */
    s16 v[4];    /* sp+0x40 : RotTransPers arg0 */
    s32 sxy;     /* sp+0x48 : DVECTOR — see lever 2, a u16[2] here costs 8 bytes */
    s32 z;       /* sp+0x4C */
    s32 flag;    /* sp+0x50 */
    s32 anim;
    s32 r;
    s32 t;

    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801B03F8);
        *(s16 *)(a0 + 0xFE) = 0;
    }

    anim = a0 + 0x88;
    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim) >= 0x1000) {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), (void *)anim), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    mv[0] = 0;
    mv[1] = 0;
    mv[2] = -(*(s16 *)(a0 + 0xFC) << 17) / 0x18;
    func_8012B1B4(a0, (s32)mv);

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        s32 d;
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B744((void *)(a0 + 4), (void *)anim), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp30.x = *(u16 *)(a0 + 0x6) - ((t * r) >> 12);
    sp30.y = *(u16 *)(a0 + 0xA) - 0x20;
    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp30.z = *(u16 *)(a0 + 0xE) - ((t * r) >> 12);
    sp38.x = sp30.x;
    sp38.y = sp30.y + 0x60;
    sp38.z = sp30.z;

    if ((func_80133784(1, &sp30, (s32)&sp38) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    if (*(s16 *)(a0 + 0xFE) == 0 && func_8012BD3C(a0, 0x200, 0x40000) == 1) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AFD68);
        *(s16 *)(a0 + 0x2) = 2;
        v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes: rematerialise &D_800AF648 (lui/addiu) before EACH call */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)v, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0x9F) & 0xFFFF) < 0x13F
                      && (u32)((*((u16 *)&sxy + 1) + 0x77) & 0xFFFF) < 0xEF) {
            s32 sx;                             /* screen X, then REUSED as the pan field */
            register s32 av __asm__("$5");      /* |X| — the one pin that helped */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
            s32 vol;
            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;                       /* in place, so reorg can steal it */
            func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
        }
    }

    if (*(s16 *)(a0 + 0xFC) == 0x18) {
        *(s16 *)(a0 + 0xFC) = 0;
    }
}


    typedef struct {
        u16 x, y, z, w;
    } V8_8017FFA0;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8017FFA0;

/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   func_8012B1B4  TU:3931/4008/4455/4529
 *   func_8012B8E4  TU:4456/4528   (not declared above the splice; same form)
 *   func_8012CBA4  TU:4110/4457   (void return -> cast at the use site)
 *   func_8004787C  TU:2206/3652/4190/4458
 *   func_80047948  TU:2205/3651/4459
 *   func_80133784  TU:599/855/4460
 *   func_8012BCCC  TU:3928/4005/4461
 *   func_8012BDBC  TU:4462/5984
 *   func_8012A828  TU:3527/3810/…/4463 (23 decls, all this form)
 *   rand           TU:957/4154/4189/4214/4622
 *   D_801B0F00     TU:4800/5275/5298 as `extern u8 D_801B0F00[]`
 * D_801B0CF8 / D_801B0678 appear nowhere else in the TU; same canonical form. */
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 rand(void);

void func_8017FFA0(s32 a0) {

    extern u8 D_801B0CF8[];
    extern u8 D_801B0678[];
    extern u8 D_801B0F00[];
    typedef struct {
        u16 x, y, z, w;
    } V8_8017FFA0;
    s32 sp10[4];
    V8_8017FFA0 pad[2];
    V8_8017FFA0 sp30;
    V8_8017FFA0 sp38;
    s32 t;
    s32 r;
    s32 v;

    *(s16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = (*(s16 *)(a0 + 0xFC) * -0x20000) / 0x24;
    func_8012B1B4(a0, (s32)sp10);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    v = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp30.x = *(u16 *)(a0 + 0x6) - ((v * r) >> 12);
    sp30.y = *(u16 *)(a0 + 0xA) - 0x20;
    v = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp30.z = *(u16 *)(a0 + 0xE) - ((v * r) >> 12);
    sp38.x = sp30.x;
    sp38.y = sp30.y + 0x60;
    sp38.z = sp30.z;

    if ((func_80133784(1, &sp30, (s32)&sp38) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    t = func_8012BCCC(a0);
    if (t < 0x1001) {
        if (func_8012BDBC(a0, 0x200) == 1) {
            s32 s;
            if ((rand() & 3) == 0) {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801B0CF8);
                s = 0x5;
            } else {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801B0678);
                s = 0xF;
            }
            *(s16 *)(a0 + 0x2) = s;
        }
    }
    if (t > 0x40000) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801B0F00);
        *(s16 *)(a0 + 0x2) = 1;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 1;
    }
    if (*(s16 *)(a0 + 0xFC) == 0x24) {
        *(s16 *)(a0 + 0xFC) = 0;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_801801E0;

/* func_801801E0 — ov_SC02_026 jr_8017C180 family exemplar (15 members).
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND block from src/ov_SC06_030/ov_SC06_030_jr_8017C8D0.c:3480
 * (func_8017E120) — `u16 sxy[2]`, the `(u32)((sxy[i] + K) & 0xFFFF) < N`
 * range tests, the explicit `(s16)sxy[0]` sign-extension (sll/sra off the
 * already-loaded lhu), and the $a0-pinned scopes that REMATERIALISE
 * &D_800AF648 per call instead of letting CSE hoist it into a callee-saved
 * register (which would shove the actor out of $s0).
 *
 * The head (func_8012B608 accumulate + &0xFFF) copies the form banked at
 * TU:3941 (func_80180C80) / TU:4478 (func_80183B04).  Head + RTP were right on
 * the first compile (115/154); the panner tail took SIX levers, each measured:
 *
 *  1. FRAME PADDING (idiom 6).  Locals start at sp+0x10 (the o32 outgoing-arg
 *     area) but the RTP block is at sp+0x20, so 16 bytes of padding precede it.
 *     It must be an AGGREGATE — a scalar becomes a pseudo and vanishes; only
 *     assign_stack_local aggregates size the frame.  vars 0x28 => frame 0x48.
 *
 *  2. THE abs TESTS `x`, NOT `ax`.  Target is
 *         bgez $a2,L / addu $a1,$a2,$zero (DELAY SLOT) / negu $a1,$a2 / L:
 *     i.e. `ax = x; if (x < 0) ax = -x;`.  The textbook `if (ax < 0) ax = -ax;`
 *     makes the branch DEPEND on the copy, so reorg cannot sink `move ax,x`
 *     into the delay slot: it emits the copy first and fills the slot with the
 *     divide magic's `lui` (12 off).  `__builtin_abs` is the WRONG lever here —
 *     it is one abssi2 insn, the block never splits, and the whole divide pair
 *     re-schedules (22 off).
 *
 *  3. $a1-PIN ON THE abs RESULT (§40 / ov_SC03_006_jr_8012ACE0.c:816).
 *     Unpinned, local-alloc's combine_regs ties the abs dest to its dying input
 *     and every downstream register shifts (12 off).  Pin ONLY the abs result:
 *     pinning `x` or the pan quotient re-seats the divide chain (17 / 8 off).
 *
 *  4. ZERO-BYTE RE-TIE ON `vol` (§21 / S4).  Both divides share one HI/LO, so
 *     the scheduler must choose which `mult` issues first, and priority is
 *     height-to-block-end: the pan quotient feeds the `bne`, so it wins and the
 *     vol chain sinks (41 off, -2 ins).  A NON-volatile
 *     `__asm__("" : "=r"(vol) : "0"(vol));` gives `vol` a free in-block
 *     consumer, flipping the chains back to the target's
 *     `mult / mfhi $t1 / addiu / nop / mult` (that `nop` is the mfhi->mult
 *     hazard and IS in the target).  A *volatile* asm over-serialises (35 off).
 *
 *  5. THE PAN QUOTIENT IS THE SAME VARIABLE AS `x` (§136 L1 — the Ghidra seed
 *     had this right, it reuses iVar5).  Target's `subu $a2,$v1,$v0` puts the
 *     quotient back in x's register; a separate `pan` local is a fresh global
 *     allocno and takes $v1 (earlier in REG_ALLOC_ORDER) — 6 off, and no pin
 *     fixes it.
 *
 *  6. 0x3000 IN A LOCAL, NOT A LITERAL.  fold reassociates
 *     `(vol | 0x3000) | pan` into `vol | (pan | 0x3000)`, landing the `ori` on
 *     the shifted pan — in EVERY literal spelling swept (2-5 off).  Hoisting it
 *     into `flg` leaves no constant for fold to move, and keeping the OR inside
 *     the call ARGUMENT preserves the target's `addiu $a0,0xA9B` -> `ori` ->
 *     `or` order (a standalone `vol |= 0x3000;` statement fixes the tree but
 *     swaps those two, 2 off).
 *
 * Declarations: func_8012B608 / func_8012B1B4 / func_8012CBA4 /
 * func_8004914C / func_800491AC / func_8002D4C8 / D_801A3CB0 are copied
 * VERBATIM from the TU (lines 3930, 3931, 4110, 2646, 2647, 59, 4464).
 * func_8012BE98 / func_8012B744 / func_8012BD3C / RotTransPers / D_800AF648
 * appear NOWHERE in the TU, so the fleet-dominant forms are used and the
 * return value of the `void`-declared func_8012BE98 is taken through a cast
 * at the call site (idiom 9).
 */

extern void func_8012BE98(s32 a0, u16 *a1);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_801801E0(s32 a0) {

    extern u8 D_800AF648;
    extern u8 D_801A3CB0[];
    /* locals start at sp+0x10 (the 16-byte outgoing-arg area).  The first
       16 bytes are unreferenced in this function but are part of the
       frame — vars must be 0x28, i.e. frame 0x48. */
    struct {
        s32 pad0[4];   /* sp+0x10 */
        s16 v[3];      /* sp+0x20 */
        s16 pad1;      /* sp+0x26 */
        u16 sxy[2];    /* sp+0x28 */
        s32 z;         /* sp+0x2C */
        s32 flag;      /* sp+0x30 */
    } L;
    void *p88;

    p88 = (void *)(a0 + 0x88);

    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88) >= 0x1000) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    func_8012B1B4(a0, (s32)D_801A3CB0);

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        s32 r2;
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
        r2 = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                           func_8012B744((void *)(a0 + 4), p88), 0x20);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r2;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }

    if (func_8012BD3C(a0, 0x200, 0x40000) == 1) {
        *(s16 *)(a0 + 0x2) = 7;
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* The target loads &D_800AF648 afresh (lui/addiu $a0) for EACH call.  The
         * second call names the object through a second declaration of the same
         * symbol: its SYMBOL_REF string is a different pointer, so cse does not
         * unify the two address pseudos into one callee-saved register. */
        func_8004914C(&D_800AF648);
        {
            extern u8 D_800AF648_b __asm__("D_800AF648");
            func_800491AC(&D_800AF648_b);
        }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 x = (s16)L.sxy[0];
            s32 vol = x;
            if (vol < 0) {
                vol = -vol;
            }
            vol = ((0xA0 - vol) * 0x7F) / 0xA0;
            x = (x + 0xA0) / 0x14;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            func_8002D4C8(0xA9B, (vol | (0x3000 | x)) & 0xFFFF);
        }
    }
}


    typedef struct {
        u16 x, y, z, w;
    } V8_80180448;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80180448;

extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);

void func_80180448(s32 a0) {

    extern u8 D_801A3CB0[];
    extern u8 D_801B09B8[];
    typedef struct {
        u16 x, y, z, w;
    } V8_80180448;
    V8_80180448 pad[2];
    V8_80180448 sp20;
    V8_80180448 sp28;
    s32 t;
    s32 r;
    s32 v;

    func_8012B1B4(a0, (s32)D_801A3CB0);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    v = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    r = 0x30;
    sp20.x = *(u16 *)(a0 + 0x6) - ((v * r) >> 12);
    sp20.y = *(u16 *)(a0 + 0xA) - 0x20;
    v = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF);
    sp20.z = *(u16 *)(a0 + 0xE) - ((v * r) >> 12);
    sp28.x = sp20.x;
    sp28.y = sp20.y + 0x60;
    sp28.z = sp20.z;

    if ((func_80133784(1, &sp20, (s32)&sp28) & 0x6000) == 0) {
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
    }

    t = func_8012BCCC(a0);
    if (t < 0x2401) {
        if (func_8012BDBC(a0, 0x200) == 1) {
            *(s16 *)(a0 + 0x2) = 0x11;
            ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801B09B8);
        }
    }
    if (t > 0x40000) {
        *(s16 *)(a0 + 0x2) = 6;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_801805F0;

/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c) where they
 * already exist, so the splice introduces no conflicting types:
 *   func_8002D4C8  TU:59/3245/3279/4619/4909/…  `void (s32,s32)`
 *   func_8012BCCC  TU:3928/4005/4461            `s32 (s32)`
 *   func_8012A828  TU:3527/3810/…/4463          `void (s32,s32)` (23 decls, all this form)
 *   func_8012B8E4  TU:4456/4528                 `s32 (s32,s32)`
 *   func_8012B1B4  TU:3931/4008/4455/4529       `void (s32,s32)`
 *   func_8012CBCC  TU:3907/3932/4530            `void (s32)`
 *   func_8004914C  TU:2646                      `void (void *)`
 *   func_800491AC  TU:2647                      `void (void *)`
 *   D_80126B62     TU:1793/4533                 `u16` -> cast to s16* at the use site
 *   D_801A39E8     TU:4722 (block scope)        `s32`  -> `(s32)&D_801A39E8 | …` (line 4753)
 * RotTransPers / D_800AF648 are not declared in this TU; the forms below are the
 * fleet-canonical ones (ov_SC02_026_jr_80140608.c:416/2312, o0c.c:365/371).
 * D_801B1508 / D_801A3CBC appear nowhere else in the TU (real dlabels in
 * asm/ov_SC02_026/data/tail.data.s:61984 / :47419); same canonical `extern s32` form
 * as the neighbouring D_801BD190 (TU:4385). */
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8012A828(s32, void*);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);


void func_801805F0(s32 a0) {

    extern u8 D_800AF648;
    extern s32 D_801B1508;
    extern s32 D_801A39E8;
    extern s32 D_801A3CBC;
    extern u16 D_80126B62;
    /* sp+0x10 local block.  Frame is 0x38 = 0x10 outgoing args + 0x20 vars +
     * 8 saved regs ($s0,$ra), so the vars block is 12 bytes larger than the
     * fields this function actually touches -> trailing `unused[3]`. */
    struct {
        s16 v[3];      /* sp+0x10 */
        s16 pad0;      /* sp+0x16 */
        u16 sxy[2];    /* sp+0x18 */
        s32 z;         /* sp+0x1C */
        s32 flag;      /* sp+0x20 */
        s32 unused[1]; /* sp+0x24 */
    } L;
    s16 x;
    s32 y;

    if (*(s32 *)(a0 + 0x94) == 0xD) {
        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialised
         * per call (cookbook §88a); otherwise CSE parks it in a callee-saved reg
         * and mis-seats every register in the function. */
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                        && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 vol = (s16)L.sxy[0];
            if (vol < 0) {
                vol = -vol;
            }
            vol = ((0xA0 - vol) * 127) / 160;
            func_8002D4C8(0x702, (vol | 0x1000) & 0xFFFF);
        }
    }

    if (func_8012BCCC(a0) <= 0x24000) {
        s16 c;
        c = *(u16 *)(a0 + 0x102) + 1;
        *(s16 *)(a0 + 0x102) = c;
        if (c >= 0x78) {
            if ((*(u16 *)(a0 + 0x100) & 0x2000) == 0) {
                ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B1508);
                *(s16 *)(a0 + 0x2) = 10;
                *(s16 *)(a0 + 0x102) = 0;
                *(s32 *)(a0 + 0x58) = (s32)&D_801A39E8 | 0x40000000 | 0x20000000;
            }
        }
    }

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    x = *(s16 *)(a0 + 0xA);
    y = *(s16 *)&D_80126B62;
    if (x <= y - 0x100) {
        *(s16 *)(a0 + 0xA) = x + 0x8;
    } else if (x >= y - 0x80) {
        *(s16 *)(a0 + 0xA) = x - 0x8;
    }

    func_8012B1B4(a0, (s32)&D_801A3CBC);
    func_8012CBCC(a0);
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c) where they
 * already exist, so the splice introduces no conflicting types:
 *   func_8012B1B4  TU:3892/3969/4452/4498/4623
 *   func_8012CBCC  TU:3868/3893/3970/4665/4824
 *   D_80126B5C     TU:362   (u8  -> cast to s32* at the use site, the load is `lw`)
 *   D_80126B62     TU:1793  (u16 -> cast to s16* at the use site, the load is `lh`)
 * func_8012B8E4 and D_80126B64 are not yet declared in this TU; the forms below are
 * the ones used everywhere else in src/ (s32 return / extern s32). */
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);


void func_8018083C(s32 a0) {

    extern u8 D_80126B5C;
    extern u16 D_80126B62;
    extern s32 D_80126B64;
    /* sp10[0..3] is the 4-word block handed to func_8012B1B4 ($a1 = sp+0x10).
     * The frame's extra 8 bytes at sp+0x20 are gcc's OWN spill area (cookbook
     * §83c) -- declaring them as a 6th/5th array element makes the frame 0x40. */
    s32 sp10[4];
    s16 t;
    s32 y;

    if (*(s32 *)(a0 + 0x94) == 0xA) {
        *(s16 *)(a0 + 0x98) = 0;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x4);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    sp10[0] = 0;
    sp10[1] = 0;

    sp10[2] = *(s32 *)(a0 + 0x4) - *(s32 *)&D_80126B5C;
    if (sp10[2] > 0) {
        sp10[2] = -sp10[2];
    }
    sp10[3] = *(s32 *)(a0 + 0xC) - D_80126B64;
    if (sp10[3] > 0) {
        sp10[3] = -sp10[3];
    }
    sp10[2] = (sp10[2] + sp10[3]) >> 4;
    func_8012B1B4(a0, (s32)sp10);

    t = *(s16 *)(a0 + 0xA);
    y = *(s16 *)&D_80126B62;
    if (t <= y - 0xA) {
        *(s16 *)(a0 + 0xA) = t + 0x8;
    } else if (t >= y) {
        *(s16 *)(a0 + 0xA) = t - 0x8;
    } else if (*(s32 *)(a0 + 0x94) == 0xA) {
        *(s16 *)(a0 + 0x2) = 0xB;
        *(s16 *)(a0 + 0x98) = 1;
    }

    func_8012CBCC(a0);
}





void func_80180988(u8 *s0) {

    extern void (*D_801A3CD4[])(void *);
    u16 v0;
    s32 a0;
    u8 *v1;

    // Call indirect function based on index at s0[2]
    v0 = *(u16 *)(s0 + 0x2);
    ((void (*)(u8 *))D_801A3CD4[v0])(s0);

    // Check if s0[0] is zero
    v0 = *(u16 *)(s0);
    if (v0 == 0) return;

    // Check if s0[0x100] & 0x1000 is zero
    v0 = *(u16 *)(s0 + 0x100);
    if ((v0 & 0x1000) == 0) return;

    // Search for entry in D_801202A0 table
    v1 = D_801202A0;
    for (a0 = 0; a0 < 0x60; a0++) {
        if (*(u16 *)(v1) == 0x15E) {
            s16 v1_val = *(s16 *)(v1 + 0x6);
            s16 s0_val = *(s16 *)(s0 + 0x6);
            if (s0_val < v1_val + 0xF0) {
                *(s16 *)(s0 + 0x6) = v1_val + 0xF0;
            }
            return;
        }
        v1 += 0x10C;
    }
}





extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_80143C74(s32, s32);
extern s32 rand(void);

void func_80180A40(s32 param_1)
{

    extern s32 D_801151D4;
    s32 sp10[4];
    s32 sp20;
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(param_1 + 0x1C);
    v1 = D_801151D4;
    *(s32 *)(param_1 + 0x1C) = v0 - 1;
    *(s16 *)((s32)sp10 + 0x2) = *(s32 *)(v1 + 0x5C);
    *(s16 *)((s32)sp10 + 0x6) = *(s32 *)(v1 + 0x60);
    *(s16 *)((s32)sp10 + 0xA) = *(s32 *)(v1 + 0x64);
    func_8012B77C((s32)&sp20, param_1 + 4, (s32)sp10);

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (sp20 + 0x400) & 0xFFF;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) += 0x55;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) += 0x55;

    v1 = *(s32 *)(param_1 + 0x1C);
    if (v1 == 0xF) {
        func_8002D4C8(0xCBA, 0);
        v1 = *(s32 *)(param_1 + 0x1C);
    }
    if (v1 < 0x10) {
        if (v1 == 0) {
            func_8012C218((void *)param_1);
        } else {
            param_1 = ((s32 (*)(s32, s32))func_80143C74)(param_1, 0);
            if (param_1 != 0) {
                *(s16 *)(param_1 + 0x16) = -4;
                v0 = rand();
                *(s16 *)(param_1 + 0x12) = (v0 & 7) - 4;
                v0 = rand();
                *(s16 *)(param_1 + 0x1A) = (v0 & 7) - 4;
                v0 = rand();
                { s32 t = *(u16 *)(param_1 + 0x6) - 0x10; *(s16 *)(param_1 + 0x6) = t + (v0 & 0x1F); }
                v0 = rand();
                { s32 t = *(u16 *)(param_1 + 0xE) - 0x10; *(s16 *)(param_1 + 0xE) = t + (v0 & 0x1F); }
            }
        }
    }
}




extern void func_8012D624(s32);
extern void func_8012C218(void *a0);
extern void func_8012B370(int);

void func_80180B94(void *a0) {

    extern void (*D_801A3D64[])(void *);
    u16 temp;
    s32 a1;

    D_801A3D64[*(u16 *)((s32)a0 + 0x2)](a0);

    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        temp = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        a1 = (s32)(temp << 16) >> 24;
        if (((s32 (*)(void *, s32, s32))func_8012D624)(a0, a1, 0x14) == 1) {
            func_8012C218(a0);
        } else {
            *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            ((void (*)(void *))func_8012B370)(a0);
        }
    }
}




extern void func_8012D624(s32);
extern void func_8012C218(void *a0);

void func_80180C40(void *a0) {

    extern void (*D_801A3EC4[])(void);
    extern u16 D_80126B96;
    u16 *q;

    D_801A3EC4[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        if (((s32 (*)(void *, s32, s32))func_8012D624)(a0, 0x10, 0x16) == 1) {
            q = &D_80126B96;
            *q |= 0x200;
            func_8012C218(a0);
        } else {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
        }
    }
}




void func_80180CF0(void *a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32, void*);
    extern void func_80131E00(struct S80131E00*, s32);
    extern s32 D_801B1288;
    extern s32 D_801A3B50;
    extern s32 D_801A39E8;

    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    *(u16 *)(&buf[0]) = v0;
    *(u16 *)(&buf[4]) = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    *(u16 *)(&buf[1]) = v1;
    *(u16 *)(&buf[5]) = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)(&buf[1]) = v0;
    *(u16 *)(&buf[5]) = (v1 + 8);
    *(u16 *)(&buf[2]) = a2;
    *(u16 *)(&buf[6]) = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) != 0) {
        ((void (*)(void *, s32))func_80131E00)(a0, 6);
    } else {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B1288);
        *(u16 *)((s32)a0 + 0x2) = 1;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xAA10;
        *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801A3B50;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_801A39E8 | 0x40000000 | 0x20000000;
        *(s16 *)((s32)a0 + 0x88) = *(u16 *)((s32)a0 + 0x6);
        *(s16 *)((s32)a0 + 0x8A) = *(u16 *)((s32)a0 + 0xA);
        *(s16 *)((s32)a0 + 0x8C) = *(u16 *)((s32)a0 + 0xE);
    }
}




/* func_80180DD8 — "ground-collision probe, then either bounce-off or pick a state script"
 * (jr_8017C180 family; byte-verified MATCH, 71 ins).
 *
 * Declaration provenance (whole-TU grep in one pass, cookbook §135-8 / D2 — every symbol below
 * checked BOTH above and below the splice point at ov_SC02_026_jr_8017C180.c:4748):
 *   func_8012CEB0(s32,s32,s32)  — TU decls at 4365 (file scope) / 4704 / 4851, identical form
 *   ((void (*)(s32, s32))func_8012A828)(s32,s32)      — 23 TU decls, all this form (or the unnamed-param twin)
 *   ((void (*)(void *, s32))func_80131E00)(void*,s32)    — TU fn-scope decls at 4706 / 4853, identical form
 *   D_801B0F00                  — declared BELOW the splice point at 5158 as `extern u8 D_801B0F00[]`;
 *                                 that exact type is reused here so the two cannot conflict
 *   D_801AF638 / D_801AF840 / D_801B03F8 — real dlabels in asm/ov_SC02_026/data/tail.data.s,
 *                                 declared nowhere else in this TU (D_801B03F8's `void (*[])(void)`
 *                                 decl lives in a DIFFERENT TU, ov_SC03_125, so it is not a conflict)
 *
 * Codegen notes:
 *  - The buf[8] halfword-pair setup + the three $2/$3/$6 pins are the byte-verified twin of
 *    func_801843AC in THIS TU (line 4703). The doubled buf[1]/buf[5] stores are real: the ±8
 *    adjust is a SECOND store to the same slot, and §135-4 (the list scheduler preserves the
 *    relative order of disambiguable stores) is what emits sh/sh then sh/sh off one lhu of a0+0xA.
 *  - 0x5C takes `ori $v0,$zero,0xAA10`, so the destination must be UNSIGNED (§135-3): through a
 *    s16 the constant folds negative and gcc emits `addiu` instead.
 *  - The 0x100 |= 0x8000 arm needs the plain `x = x | 0x8000` read-modify-write; gcc allocates the
 *    address pseudo to $a0 (the pending call arg) on its own, which is why the lhu/sh are
 *    $a0-based while everything else is $s0-based.
 *  - THE RESIDUAL THAT DECIDED THIS FUNCTION: the D_801B0F00/D_801B03F8 selector must be TWO
 *    SEPARATE CALLS, not a `tbl = cond ? A : B;` select feeding one call. With a select, both
 *    arms are single sets of the same pseudo, and gcc-2.7.2's jump.c rewrites
 *    `if (c) t=A; else t=B;` into `t=B; if (c) t=A;` — the D_801B03F8 lui/addiu hoists ABOVE the
 *    beqz and the whole tail shifts (-3 ins, LENGTH-DRIFT, 20 mismatches). Two calls are not
 *    simple sets, so the transform cannot fire; cross_jump then merges only the common
 *    [move $a0,$s0; jal] tail, which is exactly the target's j-over-arm shape.
 */

extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32, void*);
extern void func_80131E00(struct S80131E00*, s32);

void func_80180DD8(void *a0) {

    extern u8 D_801AF638[];
    extern u8 D_801AF840[];
    extern u8 D_801B03F8[];
    extern u8 D_801B0F00[];
    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    buf[0] = v0;
    buf[4] = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    buf[1] = v1;
    buf[5] = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    buf[1] = v0;
    buf[5] = (v1 + 8);
    buf[2] = a2;
    buf[6] = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) != 0) {
        *(u16 *)((s32)a0 + 0x100) = *(u16 *)((s32)a0 + 0x100) | 0x8000;
        ((void (*)(void *, s32))func_80131E00)(a0, 6);
    } else {
        if (*(s32 *)((s32)a0 + 0x90) == (s32)&D_801AF840) {
            ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801AF638);
            *(u16 *)((s32)a0 + 0x2) = 0x14;
            *(u16 *)((s32)a0 + 0x34) = 1;
            *(s16 *)((s32)a0 + 0xFE) = 0;
            *(s32 *)((s32)a0 + 0xCC) = (s32)&D_801B03F8;
        } else {
            if (*(s16 *)((s32)a0 + 0xFE) != 0) {
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B0F00);
            } else {
                ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B03F8);
            }
            *(u16 *)((s32)a0 + 0x2) = 1;
        }
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xAA10;
    }
}


s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
void func_8012B2CC(s32 a0);
s32 func_80153BD8(s32 a0);
s32 func_80153BF0(s32 a0);
void func_8002A04C(s32 a0);
void func_8012C098(void *param_1);

void func_80180EF4(s32 param_1)
{
    s32 result;

    if (*(unsigned short *)param_1 == 0) {
        return;
    }

    if (*(short *)(param_1 + 0x70) == 4) {
        result = func_8012C658(0x12C, 4, param_1);
        if (result != 0) {
            *(unsigned short *)(result + 0x6) = *(unsigned short *)(param_1 + 0x88);
            *(unsigned short *)(result + 0x88) = *(unsigned short *)(param_1 + 0x88);
            *(unsigned short *)(result + 0xE) = *(unsigned short *)(param_1 + 0x8C);
            *(unsigned short *)(result + 0x8C) = *(unsigned short *)(param_1 + 0x8C);
            *(unsigned short *)(result + 0xA) = *(unsigned short *)(param_1 + 0x8A) - 0x400;
            *(unsigned short *)(result + 0x8A) = *(unsigned short *)(param_1 + 0x8A);
            func_8012B2CC(result);
        }
    }

    if (func_80153BD8(param_1) != 0) {
        func_80153BF0(param_1);
    }

    if (*(s32 *)(param_1 + 0x78) != 0) {
        func_8002A04C(param_1);
    }

    func_8012C098((void *)param_1);
}




extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

void func_80180FD4(s32 a0) {

    extern u8 D_801A39CC[];
    typedef struct { u16 x, y, z, w; } V8_80180FD4;
    V8_80180FD4 sp10;
    V8_80180FD4 sp18;

    if (*(s32 *)(a0 + 0x94) >= 8) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8012B1B4(a0, (s32)D_801A39CC);
        if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x6000) == 0) {
            sp10.x = *(u16 *)(a0 + 0x3A);
            sp10.y = *(u16 *)(a0 + 0x3E);
            sp10.z = *(u16 *)(a0 + 0x42);
            sp18 = sp10;
            sp18.y += 8;
            if (func_80133784(1, &sp10, (s32)&sp18) != 0) {
                *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);
            }
        }
    }
}




extern void func_80131B14(void);
extern void func_8012B23C(s32);
extern s32 func_80131A34(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801810AC(s32 a0) {
    s32 s0 = a0;
    u16 v0 = *(u16 *)(s0 + 0x100);
    u16 v1 = *(u16 *)(s0 + 0x60);

    v0 |= 0x8000;
    v1 <<= 2;

    *(u16 *)(s0 + 0x100) = v0;
    *(u16 *)(s0 + 0x60) = v1;
    func_80131B14();

    *(u8 *)(s0 + 0xC2) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    ((void (*)(void *))func_8012B23C)((void *)s0);

    func_80131A34(s0, 0x8);
    func_8002D4C8(0xA74, 0);
}


s32 func_80153BD8(s32 a0);
s32 func_80153BF0(s32 a0);

void func_80181114(s32 a0)
{
    *(s16 *)(a0 + 0xFE) = 0;
    if (func_80153BD8(a0) == 0) {
        return;
    }
    func_80153BF0(a0);
}




/* Modeled on the byte-matched sibling func_801843AC in the same TU
 * (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:4677-4719): identical two-box
 * build + func_8012CEB0 collision probe, differing only in the mask (0x19 vs
 * 0x1F) and the else-arm payload. All declarations are block-scope and copied
 * verbatim from the TU so the splice introduces no conflicting types. */

void func_80181150(void *a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32, void*);
    extern void func_80131E00(struct S80131E00*, s32);
    extern char D_801B1370[];

    u16 buf[8];
    u16 v0;
    u16 v1;
    u16 a2;
    u16 tmp0;

    tmp0 = *(u16 *)((s32)a0 + 0x6);
    v0 = tmp0;
    *(u16 *)(&buf[0]) = v0;
    *(u16 *)(&buf[4]) = v0;

    v1 = *(u16 *)((s32)a0 + 0xA);
    v0 = v1 - 8;
    *(u16 *)(&buf[1]) = v1;
    *(u16 *)(&buf[5]) = v1;

    a2 = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)(&buf[1]) = v0;
    *(u16 *)(&buf[5]) = (v1 + 8);
    *(u16 *)(&buf[2]) = a2;
    *(u16 *)(&buf[6]) = a2;

    if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x19) != 0) {
        ((void (*)(void *, s32))func_80131E00)(a0, 6);
    } else {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B1370);
        *(u16 *)((s32)a0 + 0x2) = 6;
        *(u16 *)((s32)a0 + 0x5C) = (u16)0xA810;
    }
}




/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c:4453-4456),
 * so the splice introduces no conflicting types. Type disagreements are pushed
 * to casts at the use sites (cookbook §37 lever A) — codegen-neutral. */
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

void func_801811F4(s32 *s0) {

    extern u8 D_801A39CC[];

    Data_t buf_src, buf_dst;
    s32 v0;

    func_8012B1B4((s32)s0, (s32)D_801A39CC);

    v0 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if (v0 & 0x6000) {
        return;
    }

    // Load halfwords from s0
    buf_src.a = *(u16 *)((u8 *)s0 + 0x3A);
    buf_src.b = *(u16 *)((u8 *)s0 + 0x3E);
    buf_src.c = *(u16 *)((u8 *)s0 + 0x42);

    // Struct assignment generates lwl/lwr + swl/swr
    buf_dst = buf_src;

    // Modify the b field of buf_dst (at offset 2)
    buf_dst.b += 8;

    v0 = func_80133784(1, &buf_src, (s32)&buf_dst);
    if (v0 == 0) {
        return;
    }

    // Copy three words
    *(s32 *)((u8 *)s0 + 0x04) = *(s32 *)((u8 *)s0 + 0x38);
    *(s32 *)((u8 *)s0 + 0x08) = *(s32 *)((u8 *)s0 + 0x3C);
    *(s32 *)((u8 *)s0 + 0x0C) = *(s32 *)((u8 *)s0 + 0x40);
}




extern void func_8012B14C(s32 a0, s32 a1);

void func_801812B4(s32 a0)
{

    extern u8 D_801A39DC[];
    *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) & -5;
    func_8012B14C(a0, (s32)D_801A39DC);
}


extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);


void func_801812E8(s32 a0)
{
    s32 v0;

    if (*(u8 *)((s32)a0 + 0x5E) == 0x23) {
        *(u16 *)((s32)a0 + 0x100) |= 0x4000;
    }
    v0 = func_80153BD8(a0);
    if (v0 != 0) {
        func_80153BF0(a0);
    }
}


extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32);
void func_80181344(int param_1)
{
    if (((int (*)(void))func_80153BD8)() != 0) {
        ((void (*)(int))func_80153BF0)(param_1);
    }
}




extern void func_8012A828(s32, void*);

void func_8018137C(s32 a0)
{

    extern u8 D_801AFED8[];
    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AFED8);
        *(s16 *)(a0 + 0x2) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 1;
    }
}




extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32, void*);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80153C74(s16 a0, s16 a1);


void func_801813D8(s32 a0) {

    extern u8 D_801AFED8[];
    extern s32 aD801AF930 __asm__("D_801A3C90");
    extern s32 aD801AF938 __asm__("D_801A3C98");
    s32 val;

    if (func_80153BD8(a0) == 0) {
        ((void (*)(s32))func_80153BF0)(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AFED8);
        *(s16 *)(a0 + 0x2) = 0x13;
        *(s16 *)(a0 + 0x34) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
    }

    if ((*(s32 *)(a0 + 0x94) == 0xA) || (*(s32 *)(a0 + 0x94) == 0x1A)) {
        if (func_8012DEB8(a0, (s32)&aD801AF930, (s32)&aD801AF938) == 1) {
            func_8002D4C8(0xCB2, 0);
            val = *(u16 *)(a0 + 0x70) - 2;
            if ((u32)val < 2) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);

void func_801814B0(void *a0) {

    extern u8 D_801AFED8[];
    s16 val70;
    u16 val72;

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        val70 = *(s16 *)(a0 + 0x70);
        if (val70 == 0x2) {
            func_8012C588(0x1A7, (s32)a0);
        } else {
            func_8002D4C8(0xCB3, 0);
            func_8012C588(0x19F, (s32)a0);
        }
    }

    val72 = *(u16 *)(a0 + 0x72);
    if ((val72 & 0x4000) != 0) {
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_801AFED8);
        *(s16 *)(a0 + 0x2) = 0x3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 0;
    }
}




extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32, void*);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80153C74(s16 a0, s16 a1);


void func_80181544(s32 a0) {

    extern s32 aD801BC890 __asm__("D_801B0BF0");
    extern s32 aD801AF930 __asm__("D_801A3C90");
    extern s32 aD801AF938 __asm__("D_801A3C98");
    u16 val;

    if (func_80153BD8(a0) == 0) {
        ((void (*)(s32))func_80153BF0)(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD801BC890);
        *(s16 *)(a0 + 0x34) = 7;
        *(s16 *)(a0 + 0x2) = 0x13;
        *(s32 *)(a0 + 0x1C) = 0x1E;
    }

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        if (func_8012DEB8(a0, (s32)&aD801AF930, (s32)&aD801AF938) == 1) {
            func_8002D4C8(0xCB2, 0);
            val = *(u16 *)(a0 + 0x70);
            if ((u16)(val - 2) < 2u) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}




extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);


void func_80181610(s32 a0) {

    extern u8 D_801A3CC8[];
    extern u8 D_801A3CA0[];
    extern u8 D_801A3CA8[];
    extern u8 D_801AFCC0[];
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    s32 result;
    u16 val70;
    u16 *q;

    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 0xC;
        func_8012B1B4(a0, (s32)D_801A3CC8);
        *(s16 *)(a0 + 0x16) = -0x8;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801AFCC0);
        *(s16 *)(a0 + 0x98) = 0x1;
    }

    if (*(s32 *)(a0 + 0x94) == 0xF) {
        result = func_8012D5E4(a0, (s32)D_801A3CA0, (s32)D_801A3CA8, 0x14);
        if (result == 1) {
            func_8002D4C8(0xCB2, 0);

            val70 = *(u16 *)(a0 + 0x70);
            if (((u32)val70 - 2) < 2) {
                q = &D_80126B96;
                D_80126B98 = 0x18;
                *q = *q | 0x2000;
            }
        }
    }
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012A828(s32, void*);

void func_801816E8(s32 a0) {

    extern s32 aD_801BB960 __asm__("D_801AFCC0");
    extern s32 aD_801AF698 __asm__("D_801A39F8");
    u16 temp;

    if (*(s32 *)(a0 + 0x94) == 0xD) {
        func_8002D4C8(0x702, 0x107F);
    }

    func_8012CBCC(a0);

    temp = *(u16 *)(a0 + 0x102) + 1;
    *(u16 *)(a0 + 0x102) = temp;

    if ((s16)temp == 0x1E) {
        *(u16 *)(a0 + 0x2) = 0x9;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD_801BB960);
        *(u16 *)(a0 + 0x102) = 0;
        *(s32 *)(a0 + 0x14) = 0;
        *(s32 *)(a0 + 0x58) = ((s32)&aD_801AF698 | 0x40000000) | 0x20000000;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80181784;


extern void func_8012CBCC(s32 a0);

void func_80181784(s32 a0) {
    s16 v = *(s16 *)(a0 + 0xFC);

    if (v != 0) {
        *(s16 *)(a0 + 0xFC) = v - 1;
    } else if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x6000) {
        *(s16 *)(a0 + 0x2) = 1;
    }
}


void func_801817DC(void) {
}


void func_801817E4(s32 entity) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32, void*);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_801A3C90[];
    extern u8 D_801A3C98[];
    extern u8 D_801B0780[];
    extern u8 D_801B0F00[];

    s32 result;

    result = func_8012DEB8(entity, (s32)&D_801A3C90, (s32)&D_801A3C98);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = entity;
        *(u16 *)(entity + 0x2) = 0x10;
        ((void (*)(s32, s32))func_8012A828)(entity, (s32)&D_801B0780);
    } else {
        ((void (*)(s32, s32))func_8012A828)(entity, (s32)&D_801B0F00);
        *(u16 *)(entity + 0x2) = 3;
        *(u16 *)(entity + 0xFC) = 0;
        *(u16 *)(entity + 0xFE) = 1;
    }
}




extern s32 func_80153BD8(s32 a0);
extern void func_8012A828(s32, void*);

void func_80181884(s32 a0) {

    extern u8 D_801B0F00[];
    s32 result;

    result = func_80153BD8(a0);
    if (result == 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B0F00);
        *(s16 *)(a0 + 0x2) = 3;
        *(s16 *)(a0 + 0xFC) = 0;
    } else {
        *(s16 *)(a0 + 0x2) = 4;
    }
}




void func_801818D8(s32 a0) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32, void*);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_801A3C90[];
    extern u8 D_801A3C98[];
    extern u8 D_801B0AC0[];
    extern char D_801B1370[];

    s32 result;

    result = func_8012DEB8(a0, (s32)&D_801A3C90, (s32)&D_801A3C98);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = a0;
        *(u16 *)(a0 + 0x2) = 0x12;
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B0AC0);
    } else {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B1370);
        *(u16 *)(a0 + 0x2) = 0x6;
    }
}




extern s32 func_80153BD8(s32);
extern void func_8012A828(s32, void*);

void func_8018196C(s32 a0)
{

    extern s32 aD801BC890 __asm__("D_801B0BF0");
    s32 v0;

    v0 = func_80153BD8(a0);
    if (v0 != 0) {
        v0 = 0x8;
    } else {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&aD801BC890);
        v0 = 0x6;
    }
    *(s16 *)(a0 + 0x2) = v0;
}





extern s32 func_8012BEE8(s32 a0);

void func_801819B4(int param_1)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x1c) - 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (*(int *)(param_1 + 0x1c) == 0) {
        *(short *)(param_1 + 2) = *(unsigned short *)(param_1 + 0x34);
    }
}




extern void func_8012A828(s32, void*);

void func_801819DC(s32 a0)
{
    if (((*(u16 *)(a0 + 0x72) & 0x4000) != 0) || (*(s16 *)(a0 + 0x98) == 0)) {
        *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x34);
        ((void (*)(s32, s32))func_8012A828)(a0, *(s32 *)(a0 + 0xCC));
    }
}




extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern void func_8012B23C(s32);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);


void func_80181A28(s32 param_1)
{

    extern u8 D_801A3D28[];
    extern u8 D_801A3D40[];
    extern u8 D_801A3D58[];
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_801A3D28);
        ((void (*)(s32, s32))func_8012A828)(param_1, (s32)D_801A3D40);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void *))func_8012B23C)((void *)param_1);
        func_8012B2CC(param_1);
        func_8012B14C(param_1, (s32)D_801A3D58);
        *(s16 *)(param_1 + 2) = 1;
        *(s16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x90;
        *(s16 *)(param_1 + 6) =
            *(u16 *)(param_1 + 6) -
            (func_8004787C(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 8);
        *(s16 *)(param_1 + 0xE) =
            *(u16 *)(param_1 + 0xE) -
            (func_80047948(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) >> 8);
    }
}



extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181B14(s32 a0)
{
    s32 v1;

    if ((((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) != 0) {
        *(s16*)(a0 + 0x2) = 2;
        *(s32*)(a0 + 0x1C) = 0x3C;
        *(s16*)(a0 + 0x98) = 1;

        v1 = *(s32*)(a0 + 0x20);
        *(u16*)(v1 + 0x2C) |= 0x10;

        *(s32*)(*(s32*)(a0 + 0x20) + 0x4) |= 0x8000000;

        *(s16*)(*(s32*)(a0 + 0x20) + 0x12) = 0;
        func_8002D4C8(0xCB4, 0);
    }
}




/* Decls conformed VERBATIM to the TU's own file-scope decl block
 * (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c:5052-5060, the block that feeds the
 * banked sibling func_801850E4). Two of them disagreed with this draft:
 *   func_8012C1B8 -> TU says `void` return, draft wanted s32  (the reported conflict)
 *   func_8012B23C -> TU says `void *` param,  draft wanted s32 (hidden behind it)
 * Both disagreements are pushed to casts at the USE site (§37 lever A) — zero bytes
 * change; the same cast idiom is already used by func_801850E4 above. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 rand(void);
extern void func_8012B23C(s32);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_80181B98(s32 a0)
{

    extern s32 D_801A3D70;
    extern s32 D_801A3E30;
    extern s32 D_801A3EB8;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)a0);
    } else {
        func_8001CA1C(v0, (s32)&D_801A3D70);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801A3E30);
        v0 = rand();
        *(u32 *)(a0 + 0x94) = v0 & 0xF;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);

        ((void (*)(void *))func_8012B23C)((void *)a0);
        func_8012B2CC(a0);
        func_8012B14C(a0, (s32)&D_801A3EB8);

        *(u16 *)(a0 + 0x2) = 1;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;

        *(s16 *)(a0 + 0xA) -= 0x90;

        v0 = func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s16 *)(a0 + 0x6) -= (s16)(v0 >> 8);

        v0 = func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s16 *)(a0 + 0xE) -= (s16)(v0 >> 8);
    }
}


void func_8012CBCC(s32 a0);

void func_80181CA4(s32 a0)
{
    u32 result = ((u32 (*)(s32))func_8012CBCC)(a0);
    if (result & 0x2000) {
        *(s16 *)(a0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);


void func_80181CDC(void *a0) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) + 0x200;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) + -0x200;
    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x1a) < 0x401) {
        func_8012C218(a0);
    }
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   D_80126B62     TU:1793/4533  `extern u16` -> cast to s16* at the use site (`lh`)
 *   D_80126B96     TU:3758/4695/5189/5269  `extern u16`
 *   func_8012DEB8  TU:5081/5147/5266/5315  `s32 (s32,s32,s32)`
 *   func_8012BD14  TU:3986                 `s32 (s32)`
 * D_801C0F84 / D_801C0FAC / D_801C0FD4 are 20-entry `.short` tables in
 * asm/ov_SC02_026/data/tail.data.s:40884/40909/40934 (loads are `lhu` -> u16).
 * D_801C0FFC is the 2-entry fn-ptr table right after them (func_80180A4C /
 * func_80180AF0); same `void (*[])(...)` form as D_801A9EB8 (TU:3653).
 * func_8002D59C is declared nowhere in this TU. */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8012BD14(s32);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_80181D48(s32 a0) {

    extern u16 D_80126B62;
    extern u16 D_80126B96;
    extern u16 D_801C0F84[];
    extern u16 D_801C0FAC[];
    extern u16 D_801C0FD4[];
    extern void (*D_801C0FFC[])(s32);
 /* 8 bytes */

    V4_8017FAC0 p1;
    V4_8017FAC0 p2;
    s32 i;
    s32 t;
    s32 y;
    s32 ret;

    t = *(s16 *)(a0 + 0xA) + 0x20;
    y = *(s16 *)&D_80126B62 - t;
    if (y < -0x110) {
        y = -0x110;
    } else if (y > 0) {
        y = 0;
    }
    p1.y = y;
    p2.y = y;

    for (i = 0; i < 20; i += 4) {
        p1.x = D_801C0F84[i];
        p1.z = D_801C0F84[i + 1];
        p2.x = D_801C0F84[i + 2];
        p2.z = D_801C0F84[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_801C0FAC[i];
        p1.z = D_801C0FAC[i + 1];
        p2.x = D_801C0FAC[i + 2];
        p2.z = D_801C0FAC[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_801C0FD4[i];
        p1.z = D_801C0FD4[i + 1];
        p2.x = D_801C0FD4[i + 2];
        p2.z = D_801C0FD4[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }

    D_801C0FFC[*(u16 *)(a0 + 0x2)](a0);

    ret = ((s32 (*)(s32))func_8012BD14)(a0);
    if (ret > 0x3FFFF) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8002D59C(4, 0x609, *(u16 *)(a0 + 0x70));
    } else {
        *(s16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - 1;
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(a0 + 0xFE) = 4;
            func_8002D59C(0x609, ((0x40000 - ret) * 127) / 0x40000 | 0x1000,
                          *(u16 *)(a0 + 0x70));
        }
    }
}




/* func_80181FE0 -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * TU-verbatim decls (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c):
 *   extern u8 D_801202A0[];                                     (line 387, 586)
 *   extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);   (line 592)
 *   extern s32 func_80047948(s32 a0);                           (line 2206)
 *   extern s32 func_8004787C(s32 a0);                           (line 2207)
 * Not in this TU: func_8012B6D4 (fleet-standard sig), D_801C1048 (2-entry fn-ptr
 * table in ov_SC02_026 tail.data: func_80180B0C / func_80180B90).
 */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_80181FE0(void *arg0) {

    extern u8 D_801202A0[];
    extern void (*D_801C1048[])(void *);
                 /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
                /* stride 0x10C, 0x60 entries (0x6480) */

    /* Two further V4 slots the original body declared ahead of `pos` but that
     * this function never reads: the target frame is 0x50 with locals at
     * 0x10..0x37 and the first live vector at 0x20, i.e. 0x10 bytes of stack
     * precede `pos`. Dropping them yields a 0x40 frame and shifts every sp
     * displacement by 0x10 (36 mismatches). */
    V4_8017FD58 unused[2];
    V4_8017FD58 pos;
    V4_8017FD58 tmp;
    V4_8017FD58 dst;
    Ent_8017FD58 *p;
    Ent_8017FD58 *e;
    s32 i;
    s32 ang;

    p = (Ent_8017FD58 *)arg0;
    D_801C1048[p->f2](p);
    e = (Ent_8017FD58 *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0x12C) {
            pos.x = e->x;
            pos.y = e->y;
            pos.z = e->z;
            ang = func_8012B6D4((s16 *)&p->f4, (s16 *)&e->f4);
            if (*(s16 *)(p->f64 + 0xFC) < 0) {
                ang -= 0x400;
            } else {
                ang += 0x400;
            }
            ang &= 0xFFF;
            pos.x -= func_8004787C(ang) >> 8;
            pos.z -= func_80047948(ang) >> 8;
            tmp.x = e->x;
            tmp.y = e->y;
            tmp.z = e->z;
            dst = tmp;
            if (func_80135888(p->f20, p->f58, (s32)&pos, (s32)&dst) != 0) {
                e->x = pos.x;
                e->z = pos.z;
            }
        }
    }
}



void func_80182168(s32 a0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8012B23C(s32);
    extern u16 D_801C12EC[];
    extern u16 D_801C12EE[];
    extern u16 D_801C12F0[];
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32, void*);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern s32 rand(void);

    extern u8 D_801C1050[];
    extern u8 D_801C1110[];
    extern u8 D_801C1198[];
    extern u8 D_801C1258[];
    extern u8 D_801C133C[];
    extern u8 D_801C1360[];
    extern u8 D_801C1014[];
    extern u8 D_801C134C[];
    extern u8 D_801C1358[];

    s32 v0;
    s16 sVar1;
    u32 uVar3;
    u32 uVar5;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    ((void (*)(void *))func_8012B23C)((void *)a0);
    *(u16 *)(a0 + 0x12) = D_801C12EC[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x16) = D_801C12EE[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x1A) = D_801C12F0[*(s16 *)(a0 + 0xFC) * 4];
    switch (*(s16 *)(a0 + 0x70)) {
    case 0:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C1050);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1110);
        *(s16 *)(a0 + 2) = 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 1:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C1198);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1258);
        *(s16 *)(a0 + 2) = 4;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s32 *)(a0 + 0x1C) = 8;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(u8 *)(a0 + 0xC0) = 1;
        *(u8 **)(a0 + 0x58) = D_801C133C;
        *(u16 *)(a0 + 0x5C) = 0x8000;
        *(s16 *)(a0 + 0xAE) = -9;
        *(u8 **)(a0 + 0xBC) = D_801C1360;
        *(u32 *)(a0 + 0xB4) = 0;
        *(u8 **)(a0 + 0x78) = D_801C1014;
        *(u32 *)(a0 + 0xC4) |= 2;
        uVar3 = func_8012C658(0x12F, 4, a0);
        *(u32 *)(a0 + 0xCC) = uVar3;
        break;
    case 2:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C1050);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1110);
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 3:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C1198);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1258);
        *(s16 *)(a0 + 2) = 7;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(s32 *)(a0 + 0x1C) = 6;
        break;
    case 4:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C134C);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1358);
        *(s16 *)(a0 + 2) = 8;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        break;
    case 5:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801C1050);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_801C1110);
        *(s16 *)(a0 + 2) = 9;
        *(u16 *)(a0 + 0xFE) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s16 *)(a0 + 0x100) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE) * 6;
        sVar1 = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x70);
        if (sVar1 == 5) {
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x60) - 0x60;
            sVar1 = (rand() % 0x60) - 0x40;
        } else {
            if (sVar1 != 6) {
                break;
            }
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x20) - 0x20;
            sVar1 = (rand() % 0x60) - 0x50;
        }
        *(s16 *)(a0 + 0x1A) = sVar1;
    }
    uVar5 = rand();
    *(u32 *)(a0 + 0x94) = uVar5 & 0xF;
    *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
}




extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80182614(void *a0) {
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0xEFFFFFFF;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x08000000;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x60000000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4) -
        (func_8004787C(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC) -
        (func_80047948(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x18) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1A) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1C) / 2;
}


extern void func_8012C218(void *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);

void func_801827A8(void *a0)
{
    u16 sv0[4];
    u16 sv1[4];
    s32 flag[4];
    s32 cnt;
    s32 tmp;
    s32 m;

    if (*(s16 *)((s32)a0 + 0xFE) == *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        if ((*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x100) & 0x4000) == 0) {
            goto low;
        }
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) - 0x200;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) - 0x200;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x200) {
            goto tail;
        }
        func_80143B6C((s32)a0, 0);
    }
    func_8012C218(a0);
    return;

low:
    cnt = *(u16 *)((s32)a0 + 0x100) - 1;
    *(s16 *)((s32)a0 + 0x100) = cnt;
    if ((s16)cnt < 9) {
        *(s16 *)((s32)a0 + 0x100) = 0x18;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 5) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 96 - 0x60;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 56 - 0x2C;
        } else if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 6) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 32 - 0x20;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 128 - 0x60;
        }
    }
    tmp = *(s16 *)((s32)a0 + 0x100);
    if (tmp < 0x10) {
        s32 g1;                       /* per-arm local: §5a cross-jump barrier, see header */
        g1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g1 + 0x1A) = tmp * 0x300;
        *(s16 *)(g1 + 0x18) = tmp * 0x300;
    } else {
        s32 g2;                       /* per-arm local: §5a cross-jump barrier, see header */
        g2 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g2 + 0x1A) = (0x20 - tmp) * 0x300;
        *(s16 *)(g2 + 0x18) = (0x20 - tmp) * 0x300;
    }

tail:
    {
        s32 msk;
        msk = 0x80000000;             /* HOISTED OUT OF THE ARM ON PURPOSE — see header (3) */
        if (*(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4) < 0) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= msk;
        } else {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        }
    }

    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);

    sv0[0] = *(u16 *)((s32)a0 + 0x12);
    sv0[1] = *(u16 *)((s32)a0 + 0x16);
    sv0[2] = *(u16 *)((s32)a0 + 0x1A);

    m = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(sv0, sv1, flag);

    *(s16 *)((s32)a0 + 0x6) = sv1[0];
    *(s16 *)((s32)a0 + 0xA) = sv1[1];
    *(s16 *)((s32)a0 + 0xE) = sv1[2];
}



extern void func_8012D624(s32);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182B58(void *a0) {

    extern void (*D_801C1370[])(void);
    extern u16 D_80126B96;
    s32 t;
    u16 *q;

    D_801C1370[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        if (*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) >= 0) {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
            if (((s32 (*)(void *, s32, s32))func_8012D624)(a0, 0x1c, 0xa) == 1) {
                q = &D_80126B96;
                *q |= 0x200;
            }
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            if (*(s16 *)((s32)a0 + 0x70) == 1) {
                t = *(s32 *)((s32)a0 + 0x1c) - 1;
                *(s32 *)((s32)a0 + 0x1c) = t;
                if (t == 0) {
                    *(s32 *)((s32)a0 + 0x1c) = 8;
                    func_8012C658(0x12f, 3, (s32)a0);
                }
            }
        }
    }
}




void func_80182C44(void *a0) {

    extern void (*D_801C141C[])(void);
    D_801C141C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80182C80(void *a0) {

    extern void (*D_801C14D0[])(void);
    D_801C14D0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182CBC(int a0)
{
    unsigned short v0;

    v0 = *(unsigned short *)(a0 + 0x5C);
    *(char *)(a0 + 0xC1) = 0;
    *(short *)(a0 + 0x5E) = 0;
    v0 = v0 & 0xC800;
    *(unsigned short *)(a0 + 0x5C) = v0;
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182CD4(s32 a0) {

    extern u8 D_801C0F50[];
    extern u8 D_801C0F30[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80183F38[];
    s32 t;

    if (func_8012C354(a0, (s32)D_801C0F50) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801C0F30;
        *(s32 *)(a0 + 0xC4) = t | 0x2;

        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_80183F38);

        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;

        func_8012C658(0x164, 0x555, a0);
        func_8012C658(0x164, 0xAAA, a0);
        func_8012C658(0x164, 0x1000, a0);
    }
}


void func_80182D78(void *arg0)
{
    void *a1;
    unsigned short v1;
    unsigned short v0;

    a1 = *(void **)(arg0 + 0x20);
    v1 = *(unsigned short *)(arg0 + 0xFC);
    v0 = *(unsigned short *)(a1 + 0x12);
    v0 = v0 + v1;
    *(unsigned short *)(a1 + 0x12) = v0;
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);

void func_80182D94(void *a0) {

    extern u8 D_801C1014[];
    extern u8 D_801C0F30[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80183F38[];
    if (func_8012C354((s32)a0, (s32)D_801C1014) != 0) {
        void *a2 = *(void **)((char *)a0 + 0x20);

        *(s32 *)((char *)a2 + 0x4) |= 0x80000000;
        *(u8 *)((char *)a0 + 0xC0) = 1;

        *(s32 *)((char *)a0 + 0xBC) = (s32)D_801C0F30;
        *(s32 *)((char *)a0 + 0xC4) |= 0x2;

        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)D_80183F38);

        *(u16 *)((char *)a0 + 0x2) = 1;
        *(u8 *)((char *)a0 + 0x75) = 0;
    }
}


extern void func_8012B2CC(s32 a0);


void func_80182E18(s32 *a0) {
    s32 val_at_64;
    s32 deref;
    u16 val1, val2;
    s32 ptr_at_20;

    val_at_64 = *(s32 *)((char *)a0 + 0x64);
    deref = *(s32 *)((char *)val_at_64 + 0x20);
    val1 = *(u16 *)((char *)deref + 0x12);
    val2 = *(u16 *)((char *)a0 + 0x70);
    ptr_at_20 = *(s32 *)((char *)a0 + 0x20);

    *(u16 *)((char *)ptr_at_20 + 0x12) = val1 + val2;

    func_8012B2CC(a0);
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80182E54;


void func_80182E54(void *a0)
{
    u16 v = *(u16 *)(a0 + 0x5E);
    if (v != 0x1D) {
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x2) = 0x7;
    } else {
        *(u16 *)(a0 + 0x5C) = 0x8000;
    }
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80182E84;


extern void func_8012CBCC(s32 a0);
extern void func_8012E688(s32, u16, u16);

void func_80182E84(s32 a0) {
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        s16 v = *(s16 *)(a0 + 0x70);
        if (v != 0) {
            *(s16 *)(a0 + 0x2) = 2;
            ((void (*)(void*, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
        } else {
            void *p = *(void **)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(p + 0x4) |= 0x80000000;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(s32, u16, u16);

void func_80182F08(s32 a0) {

    extern u8 D_801C12E0[];
    extern s16 D_80126CB6;
    s32 r;

    if (func_8012BCCC(a0) > 0x63FFF) {
        *(u16 *)(a0 + 0x2) = 5;
    } else {
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B864(a0), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801C12E0);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((D_80126CB6 - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0)) {
            *(s16 *)(a0 + 0x16) = -0x18;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}



extern void func_8012E688(s32, u16, u16);
extern void func_8012B23C(s32);

void func_80182FCC(void *a0) {

    extern u16 D_801C12EC[];
    extern u16 D_801C12EE[];
    extern u16 D_801C12F0[];
    void *a1;

    if (--*(s32 *)((s32)a0 + 0x1c) == 0) {
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x88);
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0x8a);
        *(u16 *)((s32)a0 + 0xe) = *(u16 *)((s32)a0 + 0x8c);
        a1 = *(void **)((s32)a0 + 0x20);
        *(u32 *)((s32)a1 + 0x4) &= 0x7fffffff;
        ((void (*)(void *, s32, s32))func_8012E688)(a0, 0x679, 0);
        *(s16 *)((s32)a0 + 0x2) = 1;
        ((void (*)(void *))func_8012B23C)(a0);
        *(u16 *)((s32)a0 + 0x12) = D_801C12EC[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x16) = D_801C12EE[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x1a) = D_801C12F0[*(s16 *)((s32)a0 + 0xfc) * 4];
    }
}




extern void func_8012BD14(s32);
extern s32 func_80143970(s32);
extern void func_8012E688(s32, u16, u16);

void func_801830AC(s32 a0) {
    s32 ret = ((s32 (*)(s32))func_8012BD14)(a0);
    if (ret <= 0x64000) {
        Struct *ptr = *(Struct **)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 1;
        ptr->f1 = ptr->f1 & 0x7FFFFFFF;
        ((void (*)(void *))func_80143970)((void *)a0);
        ((void (*)(void *, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(s32, u16, u16);

void func_8018311C(s32 a0) {

    extern u8 D_801C12E0[];
    s16 sp10[3];
    s32 r;

    if (func_8012BCCC(a0) <= 0x38400) {
        *(u16 *)(a0 + 0x2) = 2;
    } else {
        sp10[0] = *(u16 *)(a0 + 0x6);
        sp10[2] = *(u16 *)(a0 + 0xE);
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B70C(sp10, (s16 *)(a0 + 0x88)), 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801C12E0);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((*(s16 *)(a0 + 0x8A) - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x8000) {
            *(s16 *)(a0 + 0x16) = -4;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}


void func_801831F8(void) {
}


/* func_80183200 — per-frame entity tick:
 *  - decrement the timer at 0x1C if non-zero
 *  - fade the two u16 colour/alpha words at +0x18 / +0x1A of the display record
 *    hanging off 0x20 by 0x100 each
 *  - once the second one drops to <= 0x80, tear the entity down
 *
 * §71 sibling-first: DEFINE_func_801319E0() (engine_core.h L17451) is the same
 * `func_8002A04C(arg0); func_8012C218((void *)arg0);` teardown tail with arg0
 * living in $s0 across the calls — signature and casts copied from it.
 */

extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_80183200(s32 arg0) {
    if (*(s32 *)(arg0 + 0x1C) != 0) {
        *(s32 *)(arg0 + 0x1C) -= 1;
    }
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) -= 0x100;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) -= 0x100;
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) < 0x81) {
        if (*(s16 *)(arg0 + 0x70) == 1) {
            /* LOAD-BEARING: hoisting the argument load into its own local
             * emits `lw $a0,0xCC($s0)` ABOVE the guard branch and leaves the
             * beqz delay slot a nop. Inlining it at the call site instead
             * gives beqz/nop/lw -> 3 mismatches (class DELAY-SLOT). A/B-tested. */
            void *temp = *(void **)(arg0 + 0xCC);
            if (arg0 != 0) {
                func_8012C218(temp);
            }
        }
        func_8002A04C(arg0);
        func_8012C218((void *)arg0);
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_801832B8(s32 a0) {

    extern u8 D_801C13A8[];
    extern u16 D_801C13DC[];
    extern u16 D_801C13DE[];
    extern u16 D_801C13E0[];
    extern s16 D_801C13E2[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80183F38[];
    if (func_8012C354(a0, (s32)D_801C13A8) != 0) {
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_80183F38);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(u16 *)(a0 + 0x12) = D_801C13DC[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x16) = D_801C13DE[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x1A) = D_801C13E0[*(s16 *)(a0 + 0xFC) * 4];
        *(s32 *)(a0 + 0x1C) = D_801C13E2[*(s16 *)(a0 + 0xFC) * 4];
        func_8012C588(0x1C4, a0);
    }
}


void func_8012CBA4(s32 a0);
void func_8012DFD4(u8 *a0);

void func_8018337C(u8 *a0)
{
    s32 v0;

    func_8012CBA4((s32)a0);
    v0 = *(s32 *)(a0 + 0x1C);
    v0--;
    *(s32 *)(a0 + 0x1C) = v0;
    if (v0 == 0) {
        *(s32 *)(a0 + 0x1C) = 6;
        *(s16 *)(a0 + 0x2) = 2;
    }
    func_8012DFD4(a0);
}




extern void func_8012DFD4(u8 *a0);

void func_801833D0(s32 a0) {

    extern s16 D_801C13E2[];
    s32 a1 = a0;
    s32 t = *(s32 *)(a1 + 0x1C) - 1;
    *(s32 *)(a1 + 0x1C) = t;
    if (t == 0) {
        s16 idx = *(s16 *)(a1 + 0xFC);
        s32 val = D_801C13E2[idx * 4];

        *(s16 *)(a1 + 0x12) = -*(u16 *)(a1 + 0x12);
        *(s16 *)(a1 + 0x16) = -*(u16 *)(a1 + 0x16);
        *(s16 *)(a1 + 0x1A) = -*(u16 *)(a1 + 0x1A);
        *(s16 *)(a1 + 0x2) = 1;
        *(s32 *)(a1 + 0x1C) = val;
    }
    func_8012DFD4((u8 *)a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 rand(void);


void func_8018344C(s32 param_1)
{

    extern u8 D_801C1428[];
    extern u8 D_801C1488[];
    s32 v0;
    s16 sVar1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_801C1428);
        ((void (*)(s32, s32))func_8012A828)(param_1, (s32)D_801C1488);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = 0x10;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = 0x10;
        *(s32 *)(param_1 + 0x94) = rand() & 7;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x10;
        if ((u32)(*(u16 *)(param_1 + 0x70) - 1) >= 0x6fff) {
            *(u16 *)(param_1 + 0x70) = rand() & 0x77ff;
            sVar1 = 2;
        } else {
            sVar1 = 1;
        }
        *(s16 *)(param_1 + 2) = sVar1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_80183530(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_801835FC(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s16 *)(a0 + 0x70) = rand() & 0x77FF;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}




void func_801836D4(void *a0) {

    extern void (*D_801C6CAC[])(void);
    D_801C6CAC[*(u16 *)((s32)a0 + 0x2)]();
}






// STEP 0 magic-literal grep: (*(LBlk16 *)&D_800A5E88) / func_8002850C / func_80028620 / func_8012AD44
// all found together in this same TU (ov_SC02_027_jr_8017D898.c). Siblings func_8018A758,
// func_8018A808, func_8018A8B8, func_8018A970 (all banked, same TU) establish the byte-proven
// idioms reused here: struct-assignment for 16-byte Blk16 records (`dst[0]=src[0];` etc.),
// and `extern void func_8012AD44(s32 *a0, s16 a1);` cast-at-call. func_8018A8B8/func_8018A970
// also already declare (*(LBlk16 *)&D_801C6C44) / (*(LBlk16 *)&D_801C6C7C) as a *singular* Blk16_8018A8B8 elsewhere in
// this TU, and (*(LBlk16 *)&D_800A5E88) likewise — since my splice point (replacing the func_80183710
// INCLUDE_ASM stub) sits ABOVE those file-scope decls/typedef, I cannot reuse the
// Blk16_8018A8B8 name here (typedef not yet visible) without a forward-reference problem, and
// per §138 (reconcile direction) redeclaring those two symbols with an INCOMPATIBLE type at
// file scope risks a clash once banked. So every symbol here is declared block-scoped (function
// body) using a locally-named struct type — block-scope externs don't collide with another
// function's block-scope externs for the same symbol (§S38/D2).

typedef struct { s32 w[4]; } LBlk16; /* 16-byte record, block-scoped local name only */

void func_80183710(void *a0)
{
    extern void func_8002850C(s32 a0, s32 a1, s32 a2);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_80028620(s32 a0, void *a1);

    extern s16 D_801C6BCC, D_801C6BCE, D_801C6BD0;
    extern LBlk16 D_801C6BD4;

    extern s16 D_801C6C04, D_801C6C06, D_801C6C08;
    extern LBlk16 D_801C6C0C;

    extern s16 D_801C6C3C, D_801C6C3E, D_801C6C40;
    extern Blk16_8018A8B8 D_801C6C44;

    extern s16 D_801C6C74, D_801C6C76, D_801C6C78;
    extern Blk16_8018A8B8 D_801C6C7C;


    s32 v1 = *(s16 *)((s32)a0 + 0xFC);
    LBlk16 *s0;

    *(s16 *)((s32)a0 + 0xFE) = 0;

    switch (v1) {
    case 0:
        func_8002850C(D_801C6BCC, D_801C6BCE, D_801C6BD0);
        s0 = &D_801C6BD4;
        func_8012AD44((s32 *)a0, 1);
        break;
    case 1:
        func_8002850C(D_801C6C04, D_801C6C06, D_801C6C08);
        s0 = &D_801C6C0C;
        func_8012AD44((s32 *)a0, 2);
        break;
    case 2:
        func_8002850C(D_801C6C3C, D_801C6C3E, D_801C6C40);
        s0 = &(*(LBlk16 *)&D_801C6C44);
        func_8012AD44((s32 *)a0, 3);
        break;
    case 3:
        func_8002850C(D_801C6BCC, D_801C6BCE, D_801C6BD0);
        s0 = &D_801C6BD4;
        func_8012AD44((s32 *)a0, 4);
        break;
    case 4:
        func_8002850C(D_801C6C74, D_801C6C76, D_801C6C78);
        s0 = &(*(LBlk16 *)&D_801C6C7C);
        func_8012AD44((s32 *)a0, 5);
        break;
    }

    {
        LBlk16 *dst = &(*(LBlk16 *)&D_800A5E88);
        LBlk16 *src = s0;

        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];

        func_80028620(0, &dst[0]);
        func_80028620(1, &dst[1]);
        func_80028620(2, &dst[2]);
    }
}



extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_80183904(void *a0) {

    extern struct B16_80185634 aD800A5EA8_80183904 __asm__("D_800A5EA8");
    extern struct B16_80185634 D_801C6BF4;
    extern s32 D_800A5EB0;
    aD800A5EA8_80183904 = D_801C6BF4;
    D_800A5EB0 = func_8004787C(*(s16 *)((s32)a0 + 0xFE)) * 10 / 4096 - 5;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(2, &aD800A5EA8_80183904);
}


#include "common.h"

typedef struct { s32 w[4]; } B16_local;

extern struct B16 D_800A5EA8;
extern B16_local D_801C6C2C;
extern s32 D_800A5EB0;
extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_801839B4(void *a0) {
    (*(B16_local *)&D_800A5EA8) = D_801C6C2C;
    D_800A5EB0 = func_8004787C(*(s16 *)((s32)a0 + 0xFE)) * 6 / 4096 - 3;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(2, &(*(B16_local *)&D_800A5EA8));
}



/* §71 sibling-first: func_80185634 (same TU, already MATCHed) is the exact template.
 * Deltas: record D_800A5EA8<-D_801CCBF8 becomes aD800A5E88_80183A64<-D_801C6C44,
 *         *10/4096-5 becomes *20/4096-10, slot 2 becomes slot 0.
 * The scaled member (D_800A5E90) is record base +8, written as a DIRECT global so it
 * emits `lui $at; sw %lo(..)($at)` rather than folding onto the $s1 record base. */


extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_80183A64(void *a0) {

    extern struct B16_80185794 aD800A5E88_80183A64 __asm__("D_800A5E88");
    extern struct B16_80185794 D_801C6C44;
    extern s32 D_800A5E90;
    aD800A5E88_80183A64 = D_801C6C44;
    D_800A5E90 = func_8004787C(*(s16 *)((s32)a0 + 0xFE)) * 20 / 4096 - 10;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, &aD800A5E88_80183A64);
}


void func_80183B14(void) {
}


/* §37 data asm-label alias: the TU already declares
 *   extern struct B16_80185794 D_800A5E88;
 * at file scope (that tag is defined next to func_80185794).  Re-declaring the
 * symbol with this function's own 16-byte record tag is a `conflicting types`
 * error, and the tag cannot be re-defined either.  Aliasing a private C
 * identifier onto the same linker symbol sidesteps the collision at zero blast
 * radius and emits the identical %hi/%lo(D_800A5E88) pair. */


extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_80183B1C(void *a0) {

    extern struct B16_8018584C aD800A5E88 __asm__("D_800A5E88");
    extern struct B16_8018584C D_801C6C7C;
    extern s32 D_800A5E90;
    s32 t;

    aD800A5E88 = D_801C6C7C;
    t = func_8004787C(*(s16 *)((s32)a0 + 0xFE));
    if (t < 0) t += 0x1FF;
    D_800A5E90 = (t >> 9) + 8;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, &aD800A5E88);
}


