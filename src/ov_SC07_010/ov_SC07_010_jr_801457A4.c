#include "common.h"
#include "../shared/engine_core.h"

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
extern void *D_801274CC;
extern s32 func_8013E410(void);
extern s32 func_8013E448(s32 a0);
extern void func_8012C724(s32 a0, s32 a1);
extern void func_8013E370(void);
extern s32 (*D_801274D0)(s32);
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
extern volatile u16 D_8011511A;
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
extern s32 func_8012C0EC(s32 *a0);
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
extern s32 func_80128ED8(void *a0, void *a1);
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

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_801457A4", func_801457A4);

void func_801458E0(void) {
}

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458e8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_801844F8 block defeats the tail-merge of the two identical D_801844F8 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145934(void) {

    extern u8 D_801844F8;
    extern u8 D_80184468;
    extern u8 D_80184444;
    extern u8 D_80184420;
    extern u8 D_801844D4;
    extern u8 D_801844B0;
    extern u8 D_8018448C;
    extern u8 D_801843FC;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801844F8;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801844F8 load from being
         * tail-merged with the v>=0x384 D_801844F8 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80184468;
    } else if (v >= 0x578) {
        p = &D_80184444;
    } else if (v >= 0x514) {
        p = &D_80184420;
    } else if (v >= 0x384) {
        p = &D_801844F8;
    } else if (v >= 0x258) {
        p = &D_801844D4;
    } else if (v >= 0xC8) {
        p = &D_801844B0;
    } else if (v >= 0xA) {
        p = &D_8018448C;
    } else {
        p = &D_801843FC;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_80184588 block defeats the tail-merge of the two identical D_80184588 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145A2C(void) {

    extern u8 D_80184588;
    extern u8 D_80184468;
    extern u8 D_80184444;
    extern u8 D_80184420;
    extern u8 D_80184564;
    extern u8 D_80184540;
    extern u8 D_8018451C;
    extern u8 D_801843FC;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80184588;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80184588 load from being
         * tail-merged with the v>=0x384 D_80184588 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80184468;
    } else if (v >= 0x578) {
        p = &D_80184444;
    } else if (v >= 0x514) {
        p = &D_80184420;
    } else if (v >= 0x384) {
        p = &D_80184588;
    } else if (v >= 0x258) {
        p = &D_80184564;
    } else if (v >= 0xC8) {
        p = &D_80184540;
    } else if (v >= 0xA) {
        p = &D_8018451C;
    } else {
        p = &D_801843FC;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145b24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145bf8 (src/shared) */


DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145c54 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_801457A4", func_80145CEC);



// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);


void func_80145EE8(s32 param_1)
{

    extern unsigned char D_80183980[];
    extern unsigned char D_801839B0[];
    extern unsigned char D_80183A00[];
    extern unsigned char D_80183A30[];
    extern unsigned char D_80183A60[];
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_80183980);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_801839B0);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_80183A00);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_80183A30);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_80183A60);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_80183980);
        ((void (*)(void *))func_80146014)(D_801839B0);
        ((void (*)(void *))func_80146014)(D_80183A00);
        ((void (*)(void *))func_80146014)(D_80183A30);
        ((void (*)(void *))func_80146014)(D_80183A60);
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
        "lui   $at, %%hi(D_801A6B48)\n"
        "sw    $v0, %%lo(D_801A6B48)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B48)\n"
        "lw    $v0, %%lo(D_801A6B48)($v0)\n"
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


DEFINE_func_80146128()  /* dedup: shared engine-core @0x80146128 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_80183AB0[u8 idx](&arg))

void func_80146360(void)
{

    extern void (*D_80183AB0[])(void *);
    extern u8 D_80126BA4;
    extern s32 D_80126B58;
    D_80183AB0[D_80126BA4](&D_80126B58);
}





   /* size 8, align 1 -> unaligned block move */

extern void func_8014C6F4();
extern void func_80155150(s32 a0);
extern void func_801470C0(s32 a0);
extern void func_80147478(s32 a0);
extern void func_80147118(s32 a0);
extern void func_8014BDE8(s32 a0);
extern short func_801508F8(s32 a0);
extern void func_8014B5B0(s32 *a0);
extern void func_80161D88(s32 a0);


void func_801463A0(void)
{

    extern s32 D_80126B58;

    extern s32 *D_80126B78;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_80126C90;
    extern u16 D_80126C92;
    extern u16 D_80126C94;
    extern s32 D_80126B9C;
    extern s32 D_80126BA0;
    extern u8 D_80126BE0[];     /* identical to the decl DEFINE_func_80146128() already emits in this TU */
    extern u8 D_80126BE8[];
    extern u16 D_80126BE0_hw __asm__("D_80126BE0");   /* halfword view of BE0 — see NEW IDIOM above */
    extern u16 D_80126BE2;
    extern u16 D_80126BE4;
    extern s16 D_80126C9E;
    s32 obj;
    short v;

    obj = (s32)D_80126B78;
    func_8014C6F4((s32)&D_80126B58);
    func_80155150((s32)&D_80126B58);
    func_801470C0((s32)&D_80126B58);
    func_80147478((s32)&D_80126B58);
    func_80147118((s32)&D_80126B58);
    if (obj != 0) {
        v = D_80126B5E + D_80126C90;
        *(short *)(obj + 8) = v;
        *(s32 *)(obj + 0x48) = (s32)v;
        v = D_80126B62 + D_80126C92;
        *(short *)(obj + 0xA) = v;
        *(s32 *)(obj + 0x4C) = (s32)v;
        v = D_80126B66 + D_80126C94;
        *(short *)(obj + 0xC) = v;
        *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x11;
        *(s32 *)(obj + 0x50) = (s32)v;
    }
    func_8014BDE8((s32)&D_80126B58);
    *(Blk8_801463A0 *)&D_80126BE8 = *(Blk8_801463A0 *)&D_80126BE0;
    D_80126BE0_hw = D_80126B5E;
    D_80126BE2 = D_80126B62;
    D_80126BE4 = D_80126B66;
    D_80126BA0 = D_80126B9C;
    D_80126B9C = D_80126B9C & 0x3FFFFFFF;
    func_801508F8((s32)&D_80126B58);
    D_80126C9E = 0;
    func_8014B5B0(&D_80126B58);
    func_80161D88((s32)&D_80126B58);
}


DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */


DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */


DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */


DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659c (src/shared) */


DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465c0 (src/shared) */


DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465e4 (src/shared) */


DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */


DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466b4 (src/shared) */


DEFINE_func_801466F0()  /* dedup: shared engine-core @0x801466F0 (src/shared) */



u16 *func_80146750(u16 *param_1) {

    extern u16 D_8011FD10;
    extern int D_8011FA1C;
    extern u16 D_8011F9D6;
    extern u16 D_8011F9DA;
    extern u16 D_8011F9DE;
    extern int D_8011FA20;
    extern int D_8011FA24;
    s32 iVar1;
    s32 iVar2;
    u16 *psVar3;
    register u16 *psVar4 __asm__("$7"); /* $a3: pin so &sym loads here, copy -> psVar3($v1) */

    iVar2 = 8;
    psVar4 = &D_8011FD10;
    psVar3 = psVar4;
    iVar1 = 0x340;
    for (; iVar2 < 0x14; iVar2++) {
        if (*psVar3 == 0) {
            *(u32 *)((char *)&(*(u32 *)&D_8011FA1C) + iVar1) = *(u32 *)((char *)param_1 + 8);
            *psVar3 = *param_1;
            *(u16 *)((char *)&D_8011F9D6 + iVar1) = param_1[1];
            *(u16 *)((char *)&D_8011F9DA + iVar1) = param_1[2];
            *(u16 *)((char *)&D_8011F9DE + iVar1) = param_1[3];
            *(u32 *)((char *)&(*(u32 *)&D_8011FA20) + iVar1) = *(u32 *)((char *)param_1 + 0xC);
            *(u32 *)((char *)&(*(u32 *)&D_8011FA24) + iVar1) = *(u32 *)((char *)param_1 + 0x10);
            return psVar4;
        }
        psVar4 = psVar4 + 0x34;
        psVar3 = psVar3 + 0x34;
        iVar1 = iVar1 + 0x68;
    }
    return (u16 *)0x0;
}


DEFINE_func_8014680C()  /* dedup: shared engine-core @0x8014680C (src/shared) */

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


DEFINE_func_80146F58()  /* dedup: shared engine-core @0x80146f58 (src/shared) */


DEFINE_func_80146FC4()  /* dedup: shared engine-core @0x80146fc4 (src/shared) */


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


DEFINE_func_801483E8()  /* dedup: shared engine-core @0x801483E8 (src/shared) */

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
    extern ActorFn D_80183AB8[];
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
        return D_80183AB8[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
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
    extern s32 D_80183AF8[];
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
    return (s32)(s16)((s16 (*)())(D_80183AF8[D_80126C02 >> 0xc]))();
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
/* derived from asm: lui/addu/lw %lo(D_80183B38) indexed by (u16>>12)*4, then jalr with no args;
 * the result is sign-extended from 16 bits => the table's functions return s16. */

s32 func_80148E54(s32 arg0) {

    extern s32 D_801151D4;
    extern s16 (*D_80183B38[])();
    register s32 tmp __asm__("$4") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                                             *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    ang = tmp;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_80183B38[*(u16 *)(arg0 + 0xAA) >> 12]();
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


extern void func_8012F14C(s32);
void func_80149350(s32 arg0) {
    func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34);
}


DEFINE_func_80149374()  /* dedup: shared engine-core @0x80149374 (src/shared) */


DEFINE_func_801493D0()  /* dedup: shared engine-core @0x801493d0 (src/shared) */


extern void func_8012F038(s32);
void func_8014942C(s32 arg0) {
    func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34);
}


DEFINE_func_80149450()  /* dedup: shared engine-core @0x80149450 (src/shared) */


DEFINE_func_801494CC()  /* dedup: shared engine-core @0x801494cc (src/shared) */


DEFINE_func_80149544()  /* dedup: shared engine-core @0x80149544 (src/shared) */


DEFINE_func_80149584()  /* dedup: shared engine-core @0x80149584 (src/shared) */



/* func_801495C4  (ov_SC01_077, 34 ins) — clone of the banked sibling func_8014964C.
 *
 * REGISTER-PIN-FREE byte-match (close=0). The sibling's engine_core.h macro pins
 * `register s32 p2 __asm__("$16")` to force a1->$s0; that pin is REMOVED here — once
 * the &buf CSE-hoist is broken, natural density allocation puts a1 in $s0 by itself
 * (a1: 7 refs / 21 insns crosses 2 calls; &buf pseudo out-densities it otherwise).
 *
 * Wall (pure-C, zero-asm): gcc-2.7.2 CSE commons the two identical stack-address
 * computations `&buf` (sp+0x20, passed to both calls) into ONE call-crossing pseudo,
 * which then wins $s0 over a1 (RC-2/K2 density) and spills a1 to $s1 (frame 0x30->0x38).
 * v1 (buf declared first, buf@sp+0x10) rematerializes &buf and matches everything but
 * the in/buf slot offsets; but correct slots REQUIRE `in,result,buf` decl order, which
 * puts buf@sp+0x20 and triggers the hoist. Every zero-asm CSE-break tried (2 pointer
 * vars, single ptr 2-set, struct, (char*)result+8, buf[z-z], a1&0, volatile ptr) is
 * folded/re-commoned by gcc. The two `m1/m2` reg-tie barriers below make the two &buf
 * opaque so each is materialized fresh (as the target does); `pin`/`mtx` barriers fix
 * the call-1 arg-materialization schedule order. These are __asm__ value-barriers, NOT
 * `register __asm__("$N")` pins.
 */
extern void func_8012F14C(s32);
extern void func_8012EF70(s32, s32);

void func_801495C4(s32 a0, s32 a1) {
    s16 in[4];
    s16 result[4];
    s16 buf[4];
    s16 *pin;
    s16 *m1;
    s16 *m2;
    s32 mtx;

    in[0] = *(u16 *)(a1 + 0x2);
    in[1] = *(u16 *)(a1 + 0x6);
    in[2] = *(u16 *)(a1 + 0xA);
    pin = in;                  __asm__ __volatile__("" : "=r"(pin) : "0"(pin));
    mtx = *(s32 *)(a0 + 0x20); __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx));
    m1 = buf;                  __asm__ __volatile__("" : "=r"(m1) : "0"(m1));
    ((void (*)(s32, void *, void *))func_8012F14C)(mtx + 0x34, pin, m1);
    m2 = buf;                  __asm__ __volatile__("" : "=r"(m2) : "0"(m2));
    ((void (*)(void *, void *))func_8012EF70)(m2, result);
    *(s16 *)(a1 + 0x2) = result[0];
    *(s16 *)(a1 + 0x6) = result[1];
    *(s16 *)(a1 + 0xA) = result[2];
}


DEFINE_func_8014964C()  /* dedup: shared engine-core @0x8014964c (src/shared) */


DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496d4 (src/shared) */


DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */


DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */


DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */


DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */


DEFINE_func_801497A8()  /* dedup: shared engine-core @0x801497A8 (src/shared) */

DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */


DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */


DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498c0 (src/shared) */


DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498e0 (src/shared) */


DEFINE_func_80149954()  /* dedup: shared engine-core @0x80149954 (src/shared) */


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


extern void func_80144A04(s32*);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EDEC(s32 a0, s32 a1);
s32 func_80149F2C(s32 a0, s32 a1) {
    void *s1 = a0;
    s32 *s0;
    if (*(u16 *)a1 == 0x83 || *(u16 *)a1 == 0x61) {
        s0 = (s32 *)((s32 (*)(s32 *))func_80144A04)((s32 *)a1);
        if (s0 != 0) {
            func_801599A4(s1);
            func_80159B3C(s1);
            func_8016EDEC((s32)s0, 0x1000000);
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

    extern s32 D_80183B78[];
    extern u8 D_80078E78[];
    s32 *p = &D_80183B78[0];
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


DEFINE_func_8014A048()  /* dedup: shared engine-core @0x8014A048 (src/shared) */


DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014a1b0 (src/shared) */


DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014a218 (src/shared) */


DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014a238 (src/shared) */


DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014a2e4 (src/shared) */


DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014a380 (src/shared) */


DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014a3e0 (src/shared) */


DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014a454 (src/shared) */


DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014a4b4 (src/shared) */


DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014a4fc (src/shared) */


DEFINE_func_8014A51C()  /* dedup: shared engine-core @0x8014A51C (src/shared) */

DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014a59c (src/shared) */


DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014a638 (src/shared) */


DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014a674 (src/shared) */


DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014a680 (src/shared) */


DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014a69c (src/shared) */


DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014a6a8 (src/shared) */


DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014a6c4 (src/shared) */


DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014a71c (src/shared) */










extern s32 func_80029178(s32);

s32 func_8014A738(void *arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];
    Vec_8014A738 d;
    u32 i;
    Ent_801202A0 *base;

    if ((func_80029178(0x83) & 0xFF) == 0) {
        return 0;
    }
    base = (Ent_801202A0 *)D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (base[i].state == 7) {
            d.vx = ((Ent_801202A0 *)arg0)->x - base[i].x;
            d.vz = ((Ent_801202A0 *)arg0)->z - base[i].z;
            if (d.vx >= 0) {
                if (d.vx < 0x40) {
                    goto zcheck;
                }
            } else {
                if (-d.vx < 0x40) {
                    goto zcheck;
                }
            }
            continue;
        zcheck:
            if (d.vz >= 0) {
                if (d.vz < 0x40) {
                    goto found;
                }
            } else {
                if (-d.vz < 0x40) {
                    goto found;
                }
            }
            continue;
        found:
            return 1;
        }
    }
    return 0;
}


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


DEFINE_func_8014ADE0()  /* dedup: shared engine-core @0x8014ADE0 (src/shared) */

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


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_801457A4", func_8014C1A0);

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

s32 aF8014C4AC(a0, a1, a2, a3, a4)
s32 a0;
s32 a1;
s32 a2;
s16 *a3;
u16 a4;
{
   /* block-scope: no file-scope conflict (§100) */
    extern s32 D_80126CD0;
    extern u16 D_8012693A;
    extern u16 D_801152B8;
    u16 t;

    if (a0 == 0) {
        return 0;
    }
    if (*(u16 *)a0 == 0) {
        return 0;
    }
    if (a1 == 9 || a1 == 0x11 || a1 == 0x29 || a1 == 0xA || D_80126CD0 != a0) {
        t = *(u16 *)(a0 + 0x5C);
        *(u16 *)(a0 + 0x5E) = a1;
        *(u16 *)(a0 + 0x62) = a4;
        *(u16 *)(a0 + 0x60) = a2;
        *(u16 *)(a0 + 0x5C) = t | 1;
        *(V4U_8014C4AC *)(a0 + 0x7C) = *(V4U_8014C4AC *)a3;
        *(u8 *)(a0 + 0xC9) = D_8012693A;
        *(u8 *)(a0 + 0xC8) = D_801152B8;
        return a0;
    }
    return 0;
}


DEFINE_func_8014C568()  /* dedup: shared engine-core @0x8014C568 (src/shared) */

DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014c59c (src/shared) */



extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {

    extern u8 D_80183C08;
    return func_8014C5FC(a0, a1, &D_80183C08);
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


void func_8014C6F4(u8 *a) {
    extern u8 D_80078E78[];
    extern s32 D_8011F9D0;
    extern s32 func_8016F1AC(void);
    extern void func_80015978(s32 a0, s32 *a1);

    u8 *p = D_80078E78;
    register u8 *e __asm__("$2");
    register u8 *lim __asm__("$3");
    u8 *q;
    s32 want;
    u8 *src;

    if ((*(u32 *)(a + 0x44) & 2) != 0) {
        a[0x1C3] = 1;
    }
    if (((*(u32 *)(a + 0x44) ^ *(u32 *)(a + 0x48)) & *(u32 *)(a + 0x44) & 0x200) != 0) {
        a[0x1C3] = 0;
    }
    *(M8_8014C6F4 *)(a + 0x164) = *(M8_8014C6F4 *)(*(u8 **)(a + 0x20) + 0x10);
    if (func_8016F1AC() != 0
        || (((*(u32 *)(a + 0x44) & 0x200) != 0) && a[0x1C3] == 0)) {
        *(s16 *)(a + 0x162) = 1;
        goto tail;
    }
    if (p[0x49] == 0x17) {
        want = 0x22;
        q = (u8 *)&D_8011F9D0;
        lim = q + 0xC30;
        for (; q < lim; q += 0x68) {
            if (*(u16 *)q == want) {
                e = q;
                goto found;
            }
        }
        e = 0;
    found:
        if (e != 0) {
            src = e + 4;
            goto call;
        }
    }
    if (*(u16 *)a == 0x19) {
        goto done;
    }
    src = a + 4;
call:
    func_80015978((s32)src, (s32 *)(a + 0x15C));
done:
    *(s16 *)(a + 0x162) = 0;
tail:
    if (*(s16 *)(a + 0x15A) == 0) {
        *(u16 *)(a + 0x154) = *(u16 *)(a + 0x6);
        *(u16 *)(a + 0x156) = *(u16 *)(a + 0xA);
        *(u16 *)(a + 0x158) = *(u16 *)(a + 0xE);
    }
    *(s16 *)(a + 0x15A) = 0;
}


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


DEFINE_func_8014CBE8()  /* dedup: shared engine-core @0x8014cbe8 (src/shared) */


DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014cbf8 (src/shared) */


DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014cc28 (src/shared) */



extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{

    extern int D_801A6B50;
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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014cd0c (src/shared) */


DEFINE_func_8014CD80()  /* dedup: shared engine-core @0x8014CD80 (src/shared) */

extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3);

// @class: loop-guard
// @stuck: none — MATCH (82 ins), symcheck SYMS-OK (4 symbols agree)
//
// Keys (template for the 137-member h_seq family):
//  (1) THE LOOP-BOUND DUALITY. The entry guard is register-relative (`addiu $v0,$s0,0x6480` +
//      `sltu`) but the BACK EDGE rematerialises the absolute bound (`lui/addiu %hi/%lo(D_80126720)`
//      + `sltu`). A plain `for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C)` also reaches
//      MATCH (82 ins) under relocation masking, but it relocates the back edge against
//      D_801202A0+0x6480 and symcheck reports `MISSING D_80126720` — i.e. it cannot be trusted to
//      bank on the symbol set. The split form below (entry guard `p < p + 0x6480`, back edge
//      `(u32)p < (u32)D_80126720`) yields the same 82 bytes AND the target's symbol set. This is
//      the func_8014DD8C / engine_core.h split-guard idiom, reused verbatim.
//  (2) TWO INDUCTION VARIABLES, secondary base +0x75. $s1 = $s0 + 0x75 is the giv gcc combines all
//      of 0x0A/0x20/0x58/0x5C/0x74/0x75 onto (the two BYTE accesses at 0x74/0x75 force an unaligned
//      base, so `q` must be u8*, not the s32* of the func_8014EA4C sibling). Written explicitly as
//      `q = p + 0x75` with negative displacements (-0x6B/-0x55/-0x1D/-0x19/-0x1).
//  (3) The `!=`-nested if ladder (not `&&`-chained, not `continue`d) reproduces the fall-through-to-
//      .L8014D00C CFG; the success block returns 1 so both exits merge on the shared epilogue.
//  (4) `t = *(s32 *)(q - 0x1D)` is loaded ONCE and reused as arg1 of func_80135A4C — that is why
//      `lw $a1, -0x1D($s1)` sits at the zero-test, not at the call.
//  (5) `& 0xFF` on the func_8014C918 result is load-bearing: it is the `andi $v1,$v0,0xFF` before
//      `sh $v1, 0x16E($s2)` (§I2 — sh alone would not mask).
//  Register fallout is natural, no pins needed: a0->$s2, a2->$s3, a1->$s4 (param_3 outranks param_2
//  on allocno priority because of its 4 extra uses in the success block).

extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);

s32 func_8014CF04(s32 a0, s32 a1, void *a2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];

    extern u8 D_80126720[];
    u8 *p;
    u8 *q;
    s32 t;

    p = D_801202A0;
    if (p < p + 0x6480) {
        q = p + 0x75;
    loop:
        if (*(u16 *)p != 0) {
            if ((*(u16 *)(q - 0x19) & 0x400) != 0) {
                t = *(s32 *)(q - 0x1D);
                if (t != 0) {
                    if (p != *(u8 **)(a0 + 0x178)) {
                        if (p != *(u8 **)(a0 + 0x174)) {
                            if (*(s16 *)(q - 0x6B) >= *(s16 *)(a0 + 0xA)) {
                                if (func_80135A4C(*(s32 *)(q - 0x55), t, (s32 *)a1, (s32)a2) != 0) {
                                    *(u8 **)(a0 + 0x174) = p;
                                    q[-1] = 1;
                                    *(u16 *)(a0 + 6) = *(u16 *)a2;
                                    *(u16 *)(a0 + 0xA) = *(u16 *)((u8 *)a2 + 2);
                                    *(u16 *)(a0 + 0xE) = *(u16 *)((u8 *)a2 + 4);
                                    *(u16 *)(a0 + 0x16E) = func_8014C918(a0, q[0]) & 0xFF;
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        p += 0x10C;
        q += 0x10C;
        if ((u32)p < (u32)D_80126720) {
            goto loop;
        }
    }
    return 0;
}



extern void func_8014D0A4(s32);

void func_8014D04C(void) {
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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014d0a4 (src/shared) */



extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);

s32 func_8014D12C(s32 arg0, void *a1, void *a2)
{
    u16 *arg1 = (u16 *)a1;
    u16 *arg2 = (u16 *)a2;
    s32 e;

    arg1[1] -= 3;
    arg2[1] += 8;
    e = *(s32 *)(arg0 + 0x174);
    if ((*(u16 *)e == 0) || ((*(u16 *)(e + 0x5C) & 0x400) == 0) || (*(s32 *)(e + 0x58) == 0) ||
        (*(s16 *)(e + 0xA) < *(s16 *)(arg0 + 0xA))) {
        if (*(u16 *)e != 0) {
            *(u8 *)(e + 0x74) = 0;
        }
        *(s32 *)(arg0 + 0x174) = 0;
        return 0;
    }
    arg1[0] = *(u16 *)(arg0 + 0x98);
    arg1[1] = *(u16 *)(arg0 + 0x9A) - 3;
    arg1[2] = *(u16 *)(arg0 + 0x9C);
    if ((*(u16 *)(e + 0x5C) & 8) != 0) {
        arg2[1] = arg1[1] + 0x18;
    }
    if (func_80135A4C(*(s32 *)(e + 0x20), *(s32 *)(e + 0x58), (s32 *)arg1, (s32)arg2) != 0) {
        *(u16 *)(arg0 + 6) = arg2[0];
        *(u16 *)(arg0 + 0xA) = arg2[1];
        *(u16 *)(arg0 + 0xE) = arg2[2];
        *(u16 *)(arg0 + 0x16E) = func_8014C918(arg0, *(u8 *)(e + 0x75)) & 0xFF;
        return 1;
    }
    *(u8 *)(e + 0x74) = 0;
    *(s32 *)(arg0 + 0x174) = 0;
    return 0;
}



extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);

s32 func_8014D2A0(s32 arg0, void *a1, void *a2)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];

    extern u8 D_80126720[];
    u16 *arg2 = (u16 *)a2;
    u8 *p;
    s32 t;

    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if ((*(u16 *)p != 0) && ((*(u16 *)(p + 0x5C) & 0x400) != 0) &&
                ((t = *(s32 *)(p + 0x58)) != 0) &&
                (p != *(u8 **)(arg0 + 0x178)) && (p != *(u8 **)(arg0 + 0x170)) &&
                (*(s16 *)(p + 0xA) >= *(s16 *)(arg0 + 0xA)) &&
                (func_80135A4C(*(s32 *)(p + 0x20), t, (s32 *)a1, (s32)arg2) != 0)) {
                *(u16 *)(arg0 + 6) = arg2[0];
                *(u16 *)(arg0 + 0xA) = arg2[1];
                *(u16 *)(arg0 + 0xE) = arg2[2];
                *(u16 *)(arg0 + 0x16E) = func_8014C918(arg0, *(u8 *)(p + 0x75)) & 0xFF;
                return 1;
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
    return 0;
}



extern void func_8014D438(s32);

void func_8014D3E0(s32 a0) {
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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014d438 (src/shared) */


DEFINE_func_8014D4C0()  /* dedup: shared engine-core @0x8014D4C0 (src/shared) */


extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);

s32 func_8014D610(s32 param_1, s32 param_2, u16 *param_3) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];
    u16 *psVar4;
    u8 *puVar3;
    s32 iVar2;

    psVar4 = (u16 *)D_801202A0;
    while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) {
        puVar3 = (u8 *)psVar4 + 0x75;
        if (*psVar4 != 0 && (*(u16 *)(puVar3 - 0x19) & 0x400) != 0 &&
            *(s32 *)(puVar3 - 0x1D) != 0 &&
            *(s16 *)(puVar3 - 0x6B) >= *(s16 *)(param_1 + 0xA)) {
            iVar2 = ((s32 (*)(s32, s32, s32, u16 *))func_80135A4C)(
                *(s32 *)(puVar3 - 0x55), *(s32 *)(puVar3 - 0x1D), param_2, param_3);
            if (iVar2 != 0) {
                *(s32 *)(param_1 + 0x174) = (s32)psVar4;
                puVar3[-1] = 1;
                *(u16 *)(param_1 + 6) = param_3[0];
                *(u16 *)(param_1 + 0xA) = param_3[1];
                *(u16 *)(param_1 + 0xE) = param_3[2];
                *(u16 *)(param_1 + 0x16E) = func_8014C918(param_1, *puVar3) & 0xff;
                return 1;
            }
        }
        psVar4 += 0x86;
    }
    return 0;
}



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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014d790 (src/shared) */


extern void func_8012AAAC(void *arg0);

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
//     cc1    rc=33   <-- ".../tu.c:1901: conflicting types for `Ent'"
//                        "src/shared/engine_types.h:434: previous declaration of `Ent'"
//     maspsx rc=0
//     as     rc=0    (only benign "used $at without .set noat" warnings)
// `33` is CC1's exit code, surfaced by the recipe's `set -o pipefail` (Makefile:560).
// Because `as` is the LAST stage in that pipe, make attributes the failure to the
// assembler — the same misread that made func_8012AAAC's "opaque Error 33" look
// assembler-shaped until it was isolated stage by stage.
//
// ROOT CAUSE: the draft declared `typedef struct Ent { ... } Ent;` at FILE scope.
// `Ent` is already a shared engine type (src/shared/engine_types.h:434,
//   typedef struct { u16 guard; u16 pad; u16 field; u8 rest[14]; } Ent;
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
// `u8 D_80183C10[]`, `s16 currentLocationId`. symcheck: SYMS-OK, 12 symbols agree.
//
// The one deliberate divergence (§27 step 2 / rule 3): func_80135A4C's canonical
// extern is 4-arg but this call site sets only $a0-$a2, so the canonical decl is
// kept verbatim (it is also the TU's own spelling at ov_SC01_077_after.c:1651/1709)
// and the ARITY is cast at the call site.
//
// BANKING NOTE for the orchestrator (carried forward from SESSION-18, still true):
// 1 `self_decl_hdr` axis remains — DEFINE_func_8014D790's body declares
// func_8014D820, so that macro in engine_core.h needs the §85 return-axis widen
// (already applied). With the `Ent` collision gone the TU's cc1 stage is clean.










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
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801202A0[];

    extern u8 D_80183C10[];
    extern u8 D_801152A8[];
    extern s16 D_801152AC;
  /* BLOCK-SCOPE types — see the header note. `Ent` at file scope collides with
     src/shared/engine_types.h:434 and kills the TU's cc1 stage (exit 33). */
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4;
  typedef struct EntD820
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
  } Ent;
  int new_var2;
  s16 new_var3;
register u16 *a2 __asm__("$7");
  V4 out[3];
  V4 pos;
  Desc desc;
  Ent *ent;
  Ent *p;
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
  ent = *((Ent **) (a0v + 0x170));
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
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
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
    func_800139C8(ang, D_80183C10, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_80183C10, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_80183C10, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014df94 (src/shared) */


DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014e048 (src/shared) */


DEFINE_func_8014E284()  /* dedup: shared engine-core @0x8014E284 (src/shared) */


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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014e48c (src/shared) */


DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014e514 (src/shared) */


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

s32 aF8014E5B4(s32 a0, void *a1, void *a2)
{

    extern u8 D_801202A0[];
    register u8 *p __asm__("$17");
    register u8 *q __asm__("$16");
    u8 *e;
    s32 t;

    p = D_801202A0;
    if (p < p + 0x6480) {
        e = p + 0x6480;
        q = p + 0xE;
    loop:
        if (*(u16 *)p != 0) {
            if ((*(u16 *)(q + 0x4E) & 0x40) != 0) {
                t = *(s32 *)(q + 0x4A);
                if (t != 0) {
                    if (func_80135888(*(s32 *)(q + 0x12), t, (s32)a1, (s32)a2) != 0) {
                        *(u8 **)(a0 + 0x17C) = p;
                        *(u16 *)(a0 + 6) = *(u16 *)(q - 8);
                        *(u16 *)(a0 + 0xE) = *(u16 *)q;
                        return 1;
                    }
                }
            }
        }
        p += 0x10C;
        q += 0x10C;
        if (p < e) {
            goto loop;
        }
    }
    return 0;
}



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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014e6f8 (src/shared) */


DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014e790 (src/shared) */


DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014e83c (src/shared) */



extern s32 func_8014E98C(void*);

void func_8014E934(s32 a0) {
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
        "jal   func_8014E98C\n"
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014e98c (src/shared) */


DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014ea4c (src/shared) */



extern s32 func_8014ED80(struct SubED80*);

void func_8014ED28(s32 a0) {
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
        "jal   func_8014ED80\n"
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014f24c (src/shared) */


DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014f2e0 (src/shared) */


DEFINE_func_8014F3E8()  /* dedup: shared engine-core @0x8014F3E8 (src/shared) */


extern s32 func_8014F4C0();

s32 func_8014F468(void)
{

    extern int D_801A6B54;
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
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F4C0()  /* dedup: shared engine-core @0x8014f4c0 (src/shared) */



extern int func_8014F74C();

void aF8014F6F4(void) __asm__("func_8014F6F4");
void aF8014F6F4(void)
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
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014f74c (src/shared) */



// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801A6B54; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);

void func_8014FA04(s32 a0)
{

    extern s32 D_801A6B54;
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
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
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
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
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
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014fd54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014fdf4 (src/shared) */



s32 func_8014FE60(void *e) {

    extern u8 D_801152A8[];
    extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
    extern s32 func_80150150(s32 e, s32 a1);

    u8 a[8];
    u8 b[8];
    u8 out[8];
    s32 r5;
    s32 r6;

    *(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(((s32)e) + 6);
    *(s16 *)(a + 2) = *(s16 *)(b + 2) = *(u16 *)(((s32)e) + 0xA) - 0x10;
    *(s16 *)(a + 4) = *(s16 *)(b + 4) = *(u16 *)(((s32)e) + 0xE);

    r5 = func_8014FFDC(((s32)e), a, out);
    r6 = func_80150150(((s32)e), (s32)b);

    if (r6 == 0) {
        *(s16 *)(b + 2) = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(a + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(a + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(a + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8);
        } else {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(b + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(b + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(b + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), D_801152A8, 8);
        }
        *(u16 *)(((s32)e) + 0x7e) &= 0xfffe;
        return 1;
    }
    {
        register s32 c __asm__("$3"); /* $v1 */
        register s32 t __asm__("$4"); /* $a0 */
        t = *(u16 *)(a + 0);
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = *(u16 *)(a + 4);
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}



DEFINE_func_8014FFDC()  /* dedup: shared engine-core @0x8014FFDC (src/shared) */


DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */


DEFINE_func_80150170()  /* dedup: shared engine-core @0x80150170 (src/shared) */


DEFINE_func_801502EC()  /* dedup: shared engine-core @0x801502EC (src/shared) */


DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */



extern void func_801504D8(u16*);

void aF80150480(void) __asm__("func_80150480");
void aF80150480(void)
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
        "jal   func_801504D8\n"
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504d8 (src/shared) */


DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */


DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505fc (src/shared) */


extern void func_80147324(s32 a0);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_8014ADA8(s32 a0, s32 a1);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);



s32 aF801506A4(s32 arg0, s32 arg1) __asm__("func_801506A4");
s32 aF801506A4(s32 arg0, s32 arg1)
{

    extern s16 D_80078EB4;
    extern void func_80150820(s32, s32);
    extern void func_8015086C(int);
    extern unsigned short D_80183C20[];
    extern unsigned short D_80183C28[];
    extern unsigned short D_80183C30[];

    int mode;

    mode = ((struct Ent_801506A4 *)arg1)->unk0;
    ((struct Ent_801506A4 *)arg1)->unk5C |= 1;
    switch (mode) {
    case 0x31:
        ((void(*)(int))func_80147324)(0x452);
        ((void(*)(int, unsigned))func_8014ADA8)(((int)arg0), D_80183C20[((struct Ent_801506A4 *)arg1)->unk70]);
        ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 3, D_80183C20[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0x32:
        if ((*(unsigned short*)&(*(u16 *)&D_80078EB4)) != 0) {
            ((void(*)(int))func_80147324)(0x452);
            ((void(*)(int, unsigned, int))func_8014BB24)(((int)arg0), D_80183C28[((struct Ent_801506A4 *)arg1)->unk70], 1);
            ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 2, D_80183C28[((struct Ent_801506A4 *)arg1)->unk70]);
        }
        break;
    case 0x33:
        ((void(*)(int))func_80147324)(0x452);
        ((void (*)(int, unsigned))func_80150820)(((int)arg0), D_80183C30[((struct Ent_801506A4 *)arg1)->unk70]);
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



extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {

    extern S16 D_801A61BC;
    extern s32 D_80183C38;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern u8 D_80126948[];
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801A61BC;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_80183C38, (s32)&arg);
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

    extern s32 D_801A6B54;
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
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
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
    extern void (*D_80183C3C[])(void);
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80183C3C[sub]();
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

    extern void (*D_80183CD0[])(void);
    D_80183CD0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */


DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519c8 (src/shared) */


DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151ae4 (src/shared) */


DEFINE_func_80151B98()  /* dedup: shared engine-core @0x80151B98 (src/shared) */

DEFINE_func_80151C54()  /* dedup: shared engine-core @0x80151C54 (src/shared) */



void func_80151D24(void *a0) {

    extern void (*D_80183CE0[])(void);
    D_80183CE0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151d60 (src/shared) */


DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151db0 (src/shared) */


DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151e78 (src/shared) */


DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ecc (src/shared) */


DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151f38 (src/shared) */


DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151fb4 (src/shared) */




void func_80152058(void *a0) {

    extern void (*D_80183D04[])(void);
    D_80183D04[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_80183CF4;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80183CF4);
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


DEFINE_func_801522CC()  /* dedup: shared engine-core @0x801522CC (src/shared) */




void func_80152370(void *a0) {

    extern void (*D_80183D18[])(void);
    D_80183D18[*(u16 *)((s32)a0 + 0x2)]();
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
    extern u8 D_80183D24[];
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_80183D24; /* $s2 = &D_80183D24 */

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

    extern void (*D_80183D34[])(void);
    D_80183D34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526d4 (src/shared) */


DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */


DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */




void func_8015282C(void *a0) {

    extern void (*D_80183D4C[])(void);
    D_80183D4C[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_80183D3C;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80183D3C);
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

    extern void (*D_80183D60[])(void);
    D_80183D60[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152ba8 (src/shared) */


DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152bf0 (src/shared) */


DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152c40 (src/shared) */


DEFINE_func_80152C80()  /* dedup: shared engine-core @0x80152c80 (src/shared) */




void func_80152D24(void *a0) {

    extern void (*D_80183D7C[])(void);
    D_80183D7C[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_80183D6C;
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_80183D6C);
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

    extern void (*D_80183D90[])(void);
    D_80183D90[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309c (src/shared) */


DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530e4 (src/shared) */


DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */


DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531bc (src/shared) */


DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */


DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327c (src/shared) */




void func_80153320(void *a0) {

    extern void (*D_80183DA4[])(void);
    D_80183DA4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335c (src/shared) */


DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533a4 (src/shared) */


DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */


DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */


DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534d8 (src/shared) */


DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */


extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014ED28(s32 _arg0);
extern void func_8014FA04(s32 a0);

s32 func_801535F4(void *arg0) {
    s32 var_s1;
    register u32 flags __asm__("$4");
    register u32 fcopy __asm__("$3");
    s32 ret;

    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    __asm__ __volatile__("" : : "r"(flags));
    return ret;
}


DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369c (src/shared) */


DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536dc (src/shared) */


DEFINE_func_80153800()  /* dedup: shared engine-core @0x80153800 (src/shared) */


DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */


DEFINE_func_801539F8()  /* dedup: shared engine-core @0x801539f8 (src/shared) */


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

    extern s32 D_80183DB8;
    extern void (*D_80183DE0[])(void *a0);
    extern s16 D_8011DB0C;
    extern u16 D_8011F748;
    ((s32 (*)(s32))func_80019064)((s32)&D_80183DB8);
    D_80183DE0[a0->idx](a0);
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

    extern u8 D_80183DC0;
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_80183DC0);
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

