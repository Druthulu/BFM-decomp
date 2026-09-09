#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
extern void func_80016714(void *a0, s32 a1);
extern void func_8013C98C(void);
extern void func_80019064(void *a0);
extern void func_8013C9C4(void * arg0);
extern void func_8013CA14(void);
extern void func_8013CABC(void);
extern void func_8013CAE8(void);
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern s16 currentLocationId;
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
extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013D3D4(int param_1, int param_2);
extern void func_800599B8(s32 a0, s32 a1);
extern void func_8013D9B0(int param_1);
extern void func_8013DBE4(int param_1);
extern s32 func_8013E054(void);
extern int SquareRoot12(int a0);
extern int func_8013E064(s16 *a0, s16 *a1);
extern int func_8013E0FC(s16 *a0, s16 *a1);
extern int func_8013E194(s16 *a0, s16 *a1);
extern void Square12(s32 *a0, s32 *a1);
extern s32 func_8013E22C(struct VecA *a0, struct VecB *a1);
extern s16 D_80126CB0;
extern s32 func_8013E298(s16 *a0);
extern s16 D_80126CAC;
extern short D_80126CAE;
extern int func_8013E2C4(short *a0);
/* extern void *D_801274CC; -- see the D_801274D0/D_801274CC note above (header-canonical s32) */
extern s32 func_8013E410(void);
extern s32 func_8013E448(s32 a0);
extern void func_8012C724(s32 a0, s32 a1);
extern void func_8013E370(void);
/* D_801274D0 / D_801274CC: jr_isolate_all's §8b layer carried these from an EARLIER region of the
 * old object as `s32 (*)(s32)` and `void *`, but ../shared/func_80144B9C.h — the whale's canonical
 * decl set (line ~136) — declares both `s32`. Nothing in THIS region uses either; all 137 other
 * whale-including files carry no such decl at all, so dropping them matches every precedent.
 * Enumerated with `cdecl` (R33), not one build at a time: of the header's 94 symbols the layer
 * re-declared exactly 3, and only these two conflict. Decls emit no code => byte-neutral (§8c),
 * and byte-gated. If a future jr re-split regenerates this layer, the conflict returns here. */
extern s32 D_801274D8;
extern s32 D_801274DC;
extern s32 func_800132BC(s32 a0, s32 a1);
extern s32 func_8013E448(s32 param_1);
extern void func_800D24A0(s32 a0);
extern void func_80141788(void);
extern void *D_8011DB24;
extern void func_8013E558(void);
extern s32 func_800D0EC4(void);
extern void func_80141874(void);
extern u8 D_800B9A15;
extern unsigned char D_800B9A13;
extern u16 D_80115110;
extern unsigned short D_80115112;
extern void func_8013E588(void * _arg0);
extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);
extern void func_8013E5E8(void);
extern void func_8013E67C(void);
extern void func_8013E83C(void);
extern s32 func_80029504(void);
extern void func_8013E6AC(void);
extern void func_800D24A0(s32 arg);
extern void func_8013E814(void);
extern void func_8013E83C();
extern void func_8013E958();
extern s32 func_80141C50(void);
extern void func_8013F244(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern void func_80137B80(void);
extern void func_8013E958(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern short D_800B9A02;
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
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern unsigned char *func_80141CA4(void);
extern void func_8013EB7C(void);
extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */
extern u16 D_80115112;
extern void func_8013ED6C(void);
extern s32 func_8013EE10();
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);
extern void func_8013EF88(void);
extern void func_8013F138(void);
extern unsigned short D_80115114;
extern unsigned short D_80115118;
extern void func_8013F1BC(void);
extern void func_80141C0C(s32);
extern u16 D_8011511C;
extern u16 D_80115120;
extern u16 D_80115122;
extern s16 D_80115128;
extern s16 D_8011512A;
extern u16 D_8011512E;
extern u8  D_80115140[];
extern s16 D_8011514E;
extern u8  D_80115152;
extern u8 D_80115158[];   /* macro-canonical (§8e) */
extern u8 D_8011515C;     /* macro-canonical (§8e) */
extern u8  D_8018305C[];
extern u8  D_80183074[];
extern u16 D_80182F78[];
extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);
extern void func_8014AA04(s32 a0);
extern void func_801415C0(s32 a0, s32 a1);
extern void func_80141C0C(s32 a0);
extern s32 func_80140608(s32 a0);
extern void func_801407F4(void);
extern s32 func_801416D4(s16);  /* macro-canonical (§8e) */
extern s32 func_8013F350(void);
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
extern void func_8013FAF8(s16 arg0, s16 arg1);
extern u8 D_80115148[];
extern u8 D_80062BDC;
extern s32 func_80028D58(void);
extern void func_80028D78(s32 a0);
extern s32 func_80028DE0(void);
extern void func_80028E00(s32 a0);
extern s32 func_80028FBC(void);
extern void func_80028FDC(s32 a0);
extern s32 func_80029000(void);
extern void func_80029020(s32 a0);
extern s32 func_80028D9C(void);
extern void func_80028DBC(s32 a0);
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
extern s32 * func_80140958();
extern s32 * func_80140D68();
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern int func_80029FE4(void);
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
extern void func_800291A0(s32, s32);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_801415C0(s32 param_1, s32 param_2);
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
extern u16 D_8011511A;
extern u16 D_8011512E;   /* §17a-1: canonical width (jr_8013F350 TUs decl u16); byte-neutral here (only use is store-0) */
extern s32  func_80029178(s32 a0);
extern void func_801418F8(void);
extern void func_80141A60(void);
extern void func_8013FAF8(s16, s16);
extern u16 D_80115116;
extern void func_80141B90(void);
extern void func_80141C0C(s32 param_1);
extern s32 func_80015144(void);
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
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_80142454(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801424E4(short *param_1);
extern void func_801425CC(void *a0);
extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);
extern void func_80142608(s32 param_1);
extern void func_801426D4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80142740(int param_1);
extern void func_80142778(u8 *a1);
extern void func_801427DC(void);
extern void func_801427E4(void);
extern void func_801427EC(int param_1);
extern s32 func_80142DB8(s32 *a0);
extern s32 func_8012C0EC(s32 a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_80142C9C(s32 *a0);
extern s32 func_8012BF10(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
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
extern void func_8012C098(void);
extern void func_80142BB4(s32 * param_1, s32 param_2, s32 param_3);
extern void func_80142C7C(void);
extern void func_8012CBF4(s32 a0);
extern void func_80142C9C(s32 * arg0);
extern void func_80142DC4(int param_1);
extern void func_80142E38(int param_1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142EC0(s32 param_1);
extern void func_80142F68(s32 *a0);
extern void func_80142FFC(s32 *a0);
extern void func_8014305C(int param_1);
extern void func_801430F4(s32 *a0);
extern void func_80143188(s32 *a0);
extern void *memcpy(void *, const void *, u32);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801431E8(s32 param_1);
extern s32 func_8012C044(s32 a0);
extern void func_801432FC(s32 *a0);
extern void func_80143390(s32 *a0);
extern void func_80143458();
extern void func_8012931C(struct vec *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
extern void func_801433F0(s32 a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80143458(s32 param_1);
extern void func_8014358C();
extern void func_8014350C(s32 *a0);
extern void func_8014358C(s32 param_1);
extern u8 *func_8012913C(s32 a0);
extern s32 rand(void);
extern void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143970(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern u8 D_801152A8[];
extern void func_801439FC(s32 a0);
extern void func_80143B30(void *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_80143BDC(u16 *a0);
extern void func_80143C38(void *a0);
extern void func_80143C74(s32 a0, s32 a1);
extern void func_80143C98(void *a0);
extern void func_80143CD4(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_80143D28(s32 param_1);
extern void func_80143E68(void *a0);
extern void func_80143EA4(void);
extern void func_80143EAC(void);
extern void func_80143EB4(void);
extern s32 func_8004787C(s32 a0);
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
extern void *func_80010A08(s32);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_80047948(s32 a0);
extern s32 AddPrim(s32, void *);
extern void func_80144090(s32 param_1);
extern void func_801442F8(int param_1);
extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80144364(int param_1);
extern void func_8012AD80(s32 a0);
extern void func_80144458(void *arg0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012B200(u8 *a0);
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
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80144A98(u8 *a0);
extern int func_80144B14(int param_1);
extern void func_80144AEC(s32 *a0);
extern int func_80013294(void *a0, void *a1);
/* ==== end §8b carried decl layer ==== */


#include "../shared/ov/func_80144B9C.h"


/* func_801457A4 @ 0x801457A4 — an -O0 function stranded at the whale's end boundary (it is the
 * FIRST fn of the -O2 "after" segment, but its target is -O0: frame-pointer + per-case stack
 * reloads). It can only bank in an -O0 object, so it lives here: _o0b is already -O0-compiled and
 * its .text ends exactly at 0x801457A4 (right after func_80144B9C), placing this fn at its true
 * address with no linker/Makefile change. Its stub was removed from ov_SC01_077_after.c. Def sig
 * conformed byte-neutrally to func_80144B9C.h's decl `void *func_801457A4(s32)` (the whale calls it
 * that way); byte-proven at -O0 (match_one --o0 79/79) and by the whole-binary gate. Phase-29 bank. */
extern int D_80181F74;

void *func_801457A4(s32 param_1) {
    switch (param_1) {
    case 0x1010:
    case 0x1052:
    case 0x1077:
    case 0x1094:
    case 0x2013:
    case 0x2015 ... 0x201a:
    case 0x2055 ... 0x205b:
    case 0x207a ... 0x2080:
    case 0x2097 ... 0x209d:
        return (void *)(&D_80181F74)[param_1 & 0xffff0fff];
    default:
        return (void *)D_80181F74;
        break;
    }
}
