#include "common.h"
#include "../shared/engine_core.h"

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
/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */
struct S80131E00;
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
extern s32 D_801D7F90;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);
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
extern s32 D_801D9484;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_801DAAC0;
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
extern int D_801D7F90;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
M2C_UNK func_80010DE0();                            /* extern */
extern s16 D_800B9A00;
extern M2C_UNK (*D_80186AF0)();
extern s16 (*D_80186AF4)();
s32 func_8002AF08();                                /* extern */
s32 func_800CFBE8();                                /* extern */
extern M2C_UNK (*D_80186AFC)();
extern s32 (*D_80186B00)();
extern s32 D_801D9480;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D7F94;
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
extern u8 D_80126948[];
void func_8012A048(void *a0, s32 a1, u8 a2);
extern void func_8012A018(s32 a0, s32 a1);
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
extern void func_8012A418(void);
extern void func_8012A464(void);
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
extern M2C_UNK D_80186E48;
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
extern s32 func_800132BC(s32 a0, s32 a1);
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
extern s32   D_8018A32C;
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
extern M2C_UNK D_80186E60;
extern M2C_UNK D_80186E68;
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
extern int D_80186E70;
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
extern void func_80131B14(void);
extern void func_8012F75C(s32 a0);
extern s32 func_8012BEE8(s32);
extern void func_8012F7B4(s32 a0);
extern void func_80131170();
extern void func_80131CA8();
extern unsigned char D_80186E8C[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_80186E98[];
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
extern int  D_80186EA4;
extern void func_8012FCC4(int param_1);
void func_801319E0(int);
void func_80131C78(int);
void func_80131CA8(int, int);
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
extern void (*D_80186EAC[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80186EFC[];
extern s16 D_80186F2C[];
extern s16 D_80186F8C[];
extern s16 D_80186F94[];
extern s16 D_80186FB4[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_80186FEC[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_80187044[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_8018708C[])(void);
extern void func_80131F28(void *a0);
extern void (*D_80187094[])(void);
extern void func_80131F64(s32 *a0);
extern s32 (*D_8018709C[])();
extern s32 func_80131FA0(s16 *a0);
extern s32 (*D_801870A4[])();
extern s32 func_80131FDC(s16 *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_8018704C;
extern void func_801320D8(int param_1);
extern int D_8018705C;
extern void func_80132144(int param_1);
extern int D_8018706C;
extern void func_801321B0(int param_1);
extern int D_8018707C;
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
extern s32 D_801D94F0;
extern s32 D_801D94F4[];
extern int D_801D94F8;
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern void func_80136BC4(s32);
extern void func_8013373C(s16 arg0);
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
extern s32 func_80135004(s32 arg0, s32 p1, s32 p2);
extern u8 D_801870B0;
extern u8 D_801870AC;
extern s16 *D_801870B4;
extern u8 D_801870B8;
extern int D_801D94F0;
extern u16 D_801D9500;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_801365B8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_801870B4;   /* holds a pointer value (*(u16**)&D_801870B4) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_801870C8[])(void);
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
extern int D_8018711C;
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


// @class: other
// @stuck: none — MATCH (100 ins)
// Levers (gcc-2.7.2 switch dispatch-tree reconstruction — the Ghidra if-chain is a DECOMPILER
// ARTIFACT, not source; transliterating it floors at 49-off):
//  1. `beq`-forward-to-body + a lone median `slt` split == a real gcc switch tree, not an if-chain.
//     count=4 cases {1,7,10,23} < CASE_VALUES_THRESHOLD(5) => branch tree, not a jump table. The
//     `if (cmd != 0)` guard is OUTSIDE the switch (a 5th case would cross the threshold -> jtbl).
//     No low-bound test before `case 10` == stmt.c "omit the branch to default to avoid only one
//     right child" (node->right is a childless single value -> plain do_jump_if_equal).
//  2. SIGNED `slti` on the median split but UNSIGNED `sltiu` on `cmd >= 0x20`: `u8 cmd` gives both
//     free — switch() default-promotes u8 -> int (signed tree), while `>= 0x20` on a zero-extended
//     u8 folds to an unsigned compare. (`u32 cmd` yields sltiu on the split and needs an ugly
//     `switch ((s32)cmd)` cast to match — same bytes, less plausible as the original source.)
//  3. Case-body emission order == SOURCE order: target lays out 10, 1, 7, 23, default.
//  4. `func_80139220(arg0)` is 1-arg here (no `li a1,10`); the ov_SC03_099 sibling's 2-arg
//     `func_80139220(arg0, cmd)` const-props cmd=10 into an extra `li a1,10`. The eager
//     `lbu a1/a2` pair is func_80138DE0(arg0, cmd, sub) ARG SETUP — that is why only $a0 is
//     reloaded at each jal, and why `cont=1` can be delay-slot-stolen from the case-1 body head.






DEFINE_func_801387B8()  /* dedup: shared engine-core @0x801387B8 (src/shared) */


/* func_80138948: sh 7 @0x4; sb 0 @0x1F; sb 0 @0xD (store order = source order). */
DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */

// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)

extern void (*D_80187120[])(void);

void func_80138BE0(int p)
{
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_80187120[*(short *)(p + 4)]();
}


DEFINE_func_80138C30()  /* dedup: shared engine-core @0x80138C30 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801380E0", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801380E0", func_80138DE0);

/* func_80138ED0 — region-a bit-unpacking / tilemap builder (159 ins, reach-134).
 * STATUS: MATCH (match_one = 0, relocation-masked byte-identical), cracked from close=21.
 *
 * Levers applied (all gcc-2.7.2-source-cited; -> cookbook §31/§32):
 *  [C1 prologue/sched]  `pb = param_3;` as the FIRST statement. sched.c:3191-3215 pins the leading
 *      run of SET(reg, hard-reg-src) parm copies at block-0 head in sched1 ("don't delay getting
 *      parameters"). combine folds the pinned `s3<-a2` parm copy into the statement-positioned
 *      pb-init, so the a2 read escapes the pin, gets a late LUID, and sched2 (backward list sched,
 *      ties broken by LUID after the class-of-last-scheduled rule) reproduces the target prologue:
 *      addiu a1,sp,16 hoisted, saves ra/s4/s3/s0 batched by the schedule_select hazard rule
 *      (sched.c:2686), and move s3,a2 landing in the lbu load-delay gap.
 *  [C2 preheader order]  Per-branch `u32 pv = uVar1;` BEFORE `p = base;` replaces loop.c's
 *      move_movables hoist of the in-loop zero-extend (loop.c:1652/1810 emits at loop_start, which
 *      lands AFTER the p=base statement -> wrong order). Explicit statement = target order
 *      [andi t1,s4][move a1,t2].
 *  [C2b copy-loop body order]  `iVar2++` moved to the END of the do-body (LUID order drives the
 *      final [lhu][addiu src][addiu t0] arrangement).
 *  [C3 tail regalloc]  The crux. Target assignment {dcount=v1, c36+df=v0, chain=v1, ba=a1, dst=a0,
 *      src=a2} is reached by:
 *      - dp pinned $4: kills the &D local qty entirely (lui a0/addiu a0/addiu a0,4 all in hard a0),
 *        and hard-blocks a0 for src.
 *      - ba pinned $5 (+ dst pinned $4, disjoint inner scope): the two sides of the surviving
 *        giv-init-style move `addu a0,a1,zero`. The $5 pin also raises reg_n_sets[$a1] so sched1's
 *        birthing boost (sched.c:2507 adjust_priority, reload_completed==0 only) does not fire on
 *        the call-arg insn a1<-sp+16 — that boost would scramble the prologue (class 1).
 *      - `tmp` (the bit-loop sll temp, global allocno already in v1) REUSED for the mult chain:
 *        a multi-block pseudo has reg_qty < 0, so local-alloc combine_regs (local-alloc.c:1667)
 *        refuses to tie ba to the chain, and set_preference's operand-strip (global.c:1545,
 *        format[0]=='e') poisoning is neutralized by conflict pruning.
 *      - mult split `tmp = (df << 1) + df; tmp = tmp << 4;` so the addu lands directly in tmp's
 *        pseudo: only ONE fresh local (q1 = df<<1) remains, whose density loses v0 to {c36,df}.
 *      - THE 3-QTY SORT BUG: local-alloc.c:1441-1463/:1494-1516 sorts <=3 local qtys with an
 *        unrolled switch that COMPARES fixed qty numbers (qty_compare(0,1),(1,2),(0,1)) but
 *        EXCHANGES order-slots; when pri(q1)>pri(q0),pri(q2) the third compare re-fires and undoes
 *        the first swap -> allocation in CREATION order, not density order. With >=4 qtys it uses
 *        qsort (correct density order). The zero-instruction DECOY qty (asm-def anchored on ba +
 *        asm-use) pushes the tail-preheader block back to 4 qtys => density order => {c36,df}
 *        (tied via combine_regs since c36 dies at the subu) takes v0 first, dcount falls to v1,
 *        q1 to v1, and first-fit (global.c:904 find_reg; regs_used_so_far pre-seeded with all
 *        call-used regs, global.c:352) gives src=a2.
 *      - The dual dummy `asm("" :: "r"(c36), "r"(dcount))` releases the li-36 and the lw together
 *        in sched1's backward pass; the class rule (sched.c:2385 rank_for_schedule: cost-1 dep =
 *        class 3 beats cost-2 load dep = class 1) then emits [lw v1][li v0] in target order.
 *      All asm()s are empty templates: zero bytes, input-only or write-then-read pairs — the
 *      byte-gate certifies the allocation they induce.
 */
DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ED0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

/* func_801392FC (T7, 182 ins, reach-134, HARDEST tier — all 8 $s0-$s7)  —  MATCH (182 ins).
 * GsSPRITE-drawing loop; LOOP form of the banked twin func_80139680 (engine_core.h DEFINE_).
 * $s map: $s0=arg0, $s1=i, $s2=rem, $s3=arg1, $s4=acc(+=0xC), $s5=arg2(natural, NO pin), $s6=0xC,
 * $s7=0xC-arg1.  Solved by Fable5 from the Opus close=2 seed; every lever below byte-verified.
 *
 * LEVER 1 (R1, the wall — count-load software-pipeline):  carry the raw count across the backedge:
 *   u16 cnt loaded VOLATILE in the preheader and re-loaded VOLATILE at the loop tail (after the
 *   call); divisor = (s16)cnt + 1 at the loop top.  Mechanics (gcc-2.7.2 source):
 *   - flow.c:2087: LOG_LINKS only created when BLOCK_NUM(use)==BLOCK_NUM(def) — combine can never
 *     fold the tail/preheader lhu (def BB) into the top-BB sll/sra sign-extend, so the "split and
 *     schedulable" sequence the target shows is simply a cross-BB dataflow, unreachable from any
 *     single-BB expression (that was the seed's dead end).
 *   - reorg.c fill_slots_from_thread then steals the top-BB-leading sll into the loop-back bnez
 *     delay slot and redirects the label to the sra (the sll appears twice: preheader fall-in +
 *     delay slot).
 *   - WHY VOLATILE (frame parity, not semantics): a non-volatile cnt load gets cse-commoned with
 *     the same-address *(s16*) condition read (the LOOP_CONT label between them is deleted as
 *     unused before cse2), and combine then does the KEEP-LOAD fold (newi2pat): combine.c:2089
 *     sets elim_i2=0 when newi2pat!=0, so the dead ashift-temp's REG_DEAD is NOT dropped
 *     (distribute_notes:10741), walks back, hits a CODE_LABEL and plants a (use reg) insn
 *     (combine.c:10835-10847); the stale-ref allocno then gets an 8-byte reload stack slot
 *     (frame 0x88/0x90 instead of 0x80).  The volatile mem is never hashed by cse (do_not_record),
 *     the condition folds CLEAN (temps fully elided, no slot), and sched2 still hoists the lh
 *     above the volatile lhu because sched.c:811 read_dependence requires BOTH mems volatile.
 *     Target frame keeps exactly ONE such slot: the w keep-load fold at +0x34 (lh/addu/slti shape).
 * LEVER 2 (prologue): NO $21 register pin (the seed needed one; with this body shape arg2 lands
 *   in $s5 naturally).  The natural param copy is batched sw s5/addu s5,a2 ahead of a0=0/a1=1.
 * LEVER 3 (buf+0x0F byte stores): route each `rem*12 + *(u8*)(arg0+0x3A) [+ arg1]` sum through an
 *   s32 temp — defeats the C-frontend QI-shorten, whose canonical QImode (plus (lbu) (prod)) has
 *   the operands swapped vs the target's SI-mode (plus (prod) (lbu)) — [addu v0,v0,v1 not
 *   addu v1,v1,v0].  (The s16 store at buf+0x06 IS shortened: mem-first there is correct.)
 * LEVER 4 (pre-call schedule / jal delay = i++): `acc += 0xC; i++;` AFTER the call statement.
 *   sched2 is the 2.7.2 BACKWARD list scheduler; rank_for_schedule ties break on INSN_LUID
 *   (original order), so statement position steers the a0/a1 arg setups early and leaves i++
 *   adjacent for reorg's slot fill.
 * LEVER 5 (post-loop block): statement order buf+0x04, buf+0x06, buf+0x0A, buf+0x0E, buf+0x0F —
 *   the LOOP BODY's own order (x,y,h,0E,0F), NOT the emission order.  This keeps sched1 from
 *   sinking the buf4 store into the s3-2 chain (which would stretch the 0x30-tmp's live range and
 *   flip the local-alloc v0/v1 assignment cascade: qty priority = log2(refs)*refs*size/length,
 *   local-alloc.c qty_compare).  The lone load-delay nop after lhu 0x30 is the target's own stall.
 * LEVER 6 (>=0xFD tail): the final call is WRITTEN IN BOTH ARMS (duplicated).  Post-reload
 *   cross-jumping (jump2 runs between sched2 and dbr) merges only the identical [jal] suffix
 *   (arm tails diverge one insn earlier), creating .L8013959C at the else's jal; dbr then fills
 *   the arm's j-slot with the a0 copy and the shared jal's slot stays nop (label blocks the
 *   backward scan).  The buf+0x04 += old buf+0x08 read is INLINE (no u16 t local) — expansion
 *   order lhu30-then-lhu(buf8) puts the loaded old-w in $a0 and lets sched pull the 0x20/0x0E
 *   stores into the load latency, matching 145-152 exactly.
 * LEVER 7 (the one pin): register s32 a1c __asm__("$5") used ONLY to re-arm a1 before the arm's
 *   SECOND call (`a1c = (s32)arg2; func(..., a1c, ...)`), producing the mid-block addu a1,s5 and
 *   suppressing call#2's own a1 copy (which is what limits the cross-jump depth to [jal] and
 *   frees the j delay slot for a0).  Call#1 and the else call pass plain (s32)arg2 — call#1's own
 *   a1 copy becomes its jal-delay fill.
 */
DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392FC (src/shared) */


DEFINE_func_801395D4()  /* dedup: shared engine-core @0x801395D4 (src/shared) */

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */

// @class: struct
// @stuck: none — MATCH (89 ins). GsSPRITE build (twin func_80139680). Levers: (1) two loads per
// D_80187164 addr — signed *(s16*) for tpage, unsigned *(u16*) for u/v — placed at their natural
// program points (buf stores interposed) so gcc can't CSE-merge them; (2) s32 temps t2/t0 force lh
// (defeat mask-driven lh->lhu narrow that would srl-reassociate the shift); (3) hi/lo temps pin the
// tpage OR structure so `|0x20` binds the middle term (else fold hoists it onto the first term);
// (4) pins: e=$a3, off=$a0 (index reuses the freed arg reg); (5) b164 base materialized into its OWN
// reg via `b164=&sym; b164=off+b164` (two-stmt) so base+ptr share $a2 (a separate base local/pin
// lands base in $v0 or ripples the tail).

#include "common.h"

extern short D_800B9A02;
extern u8 D_800A6518[];
extern u8 D_80187164;
extern u8 D_801871A8;
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
    b164 = (u8 *)&D_80187164;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_801871A8 + off;
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801380E0", func_80139BE0);

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

// @class: regalloc-order
// @stuck: none — MATCH; p=&D_80127524 pointer idiom + memory barrier forces *p reload for call arg
DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013A2BC (src/shared) */


DEFINE_func_8013A378()  /* dedup: shared engine-core @0x8013A378 (src/shared) */


struct S8013A4C4;

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013A380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013A448 (src/shared) */

DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013A4C4 (src/shared) */

/* func_8013A530 — region-a giant (204 ins, reach-134, HARDEST tier: ALL 8 $s0-$s7 + $fp).
 * Camera/entity transform dispatch on mode = *(u16*)(ent+0x18) (ent = *(param_1+4), held in $fp).
 * STATUS: match_one MATCH (204 ins), Fable5 Phase-24 T7. LOOSE/intended types.
 *
 * The whole function is byte-exact: the CASE1 block (all 8 $s regs live across three calls
 * func_80015F04/F04/5D4C), the sltiu/slti dispatch, both magic divisions (/0x9a,/0x2a), the
 * unaligned 4-byte copy, the frame, AND the clamp's double register-split (the last 10).
 *
 * LEVERS (all cookbook-cited):
 *  [dispatch]  outer `uVar2<7` on the u16 -> sltiu (gcc folds u16<C to unsigned); the redundant inner
 *      guard uses a SIGNED copy `sVar2=uVar2` -> a FRESH slti (a single signed cmp emits slt; only
 *      CSE-reuse canonicalises signed->unsigned). Branch polarity read off the target `beq ==1`:
 *      `if(uVar2!=1){DEFAULT}else{CASE1}` makes DEFAULT the fall-through, CASE1 the branched-to/last.
 *  [§17a] unaligned 4-byte mem->mem copy -> memcpy((void*)dst,(void*)src,4) -> lwl/lwr/swl/swr.
 *  [§32-5] frame is +8 over args+saves -> a dead 8-byte local (int deadlocal[2]).
 *  [§17]  bVar1 pinned $t0 (fixes its reg + pushes the 0x99/4 consts to $t1); a zero-byte
 *      __asm__("":: "r"(bVar1)) extends its range past the div2 `&0x10` so the andi lands in $v0
 *      (not in-place $t0) -> div1+div2 byte-exact.
 *  [§17]  f34 pinned $a1 (field34) so uVar6 takes $a0 (density-tie the target resolves the other way).
 *
 *  CLAMP (the former close=10 residual — RC-6 verdict OVERTURNED, no $v1 pin needed; cookbook §36):
 *  [pin]   fc stays pinned $a1: canon_reg NEVER rewrites hard-reg uses (cse.c:2545 "Never replace a
 *      hard reg") -> both compares keep reading fc even while iVar7 holds an equivalent value.
 *  [$0-add] `register int zr __asm__("$0"); iVar7 = fc + zr;` — the copy as (plus $a1 $0), NOT
 *      (set reg reg): cse forms no fc<->iVar7 equivalence (make_regs_eqv never runs -> no canon
 *      poisoning either direction) and combine cannot absorb the fc load into iVar7 (no extend+plus
 *      pattern) — a plain `int iVar7 = fc;` gets REVERSED (load->pseudo, pin<-copy, 1 insn short).
 *      (plus $a1 $0) assembles to the byte-identical `addu $v1,$a1,$zero`; maspsx/ASPSX-2.56 hops it
 *      over the slt into the beqz delay slot (cc1 emits [lh;lh;addu;slt;beqz]).
 *      iVar7 as a PSEUDO (not a $v1 pin) un-poisons reload's retry pool: with $2/$3 pins,
 *      regs_explicitly_used -> bad_spill_regs (reload1.c:3900-15) forced CASE1's 2nd-product
 *      retry_global_alloc to $t2; unpinned it lands $v1 (".greg: Register 177 now in 3").
 *  [flip]  then-arm inner compare spelled `((t<<16)>>16) > (int)mem` (canonically the SAME slt as
 *      `mem < t-ext`): mirrors the else-arm's expansion-uid order so sched1's BACKWARD list
 *      scheduler (mem-unit hazard blocks the lh next to the sh; boosted-group ties break by uid)
 *      keeps the fe-reload lh BELOW the addiu that kills iVar7 -> the reload (local-alloc, first
 *      pick) and iVar7 (global) are live-DISJOINT and can both hold $v1. Unflipped, sched1 hoists
 *      the lh to the block top ("blocking insn 185 for 1 cycles") -> hard-3 conflict -> iVar7=$a0.
 *  [dens]  two-input dummy `__asm__("" :: "r"(iVar7), "r"(t));` in the ELSE arm (anchors at t's def,
 *      §34 toolkit): +1 ref lifts iVar7's allocno priority (global.c:594 floor_log2(refs)*refs/len:
 *      3/10 -> 8/11) past the fe-load's 3/5, so iVar7 allocates FIRST -> $v1, fe -> $a0. Must NOT
 *      sit in block1: its #APP markers land between the addu-copy and the slt and block maspsx's
 *      delay-slot hop (that was v4's last diff).
 *  [keep]  `__asm__("" :: "r"(fc));` after the clamp: fc/$a1 no longer DIES at the else-compare slt,
 *      so the slt-result temp gets no qty_phys_sugg $a1 suggestion (local-alloc.c suggested-first
 *      path) and falls to plain first-fit $v0, matching the target.
 *  [nat]   the 2nd split (lh $v1 / addu $a0,$v1 / slt on $v1 / sh $a0) is NATURAL: `(int)mem`
 *      expands as HI-load + sll/sra; the body re-load cse-folds onto the HI pseudo; combine merges
 *      the extend into one lh and re-emits the HI pseudo as a subreg copy (the store temp).
 */
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
//   still merges the sb). out2[i]=out2[0] tail-copy of the align-2 Pair emits lwl/lwr/swl/swr.
#include "common.h"


extern s16 D_800D45F4[];   /* src0 (flat: [2*i]=x, [2*i+1]=y) */
extern u8  D_801871EC[];   /* sign table, alt (when a1 < 0xC00) */

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
    extern u8 D_80187228[];

    u8 *tbl;
    s16 vec[4];
    s32 res[3];
    s32 i;

    tbl = D_80187228;
    if (((s16)a1) < 0xC00) {
        tbl = D_801871EC;
    }

    for (i = 0; i < 30; i++) {
        vec[0] = D_800D45F4[2 * i]     + (((D_800D466C[2 * i]     - D_800D45F4[2 * i])     * ((s16)a1)) >> 12);
        vec[1] = D_800D45F4[2 * i + 1] + (((D_800D466C[2 * i + 1] - D_800D45F4[2 * i + 1]) * ((s16)a1)) >> 12);
        gte_ldv0(vec);
        gte_mvmva0();
        gte_stlvnl(res);
        ((Pair *)out2)[i].x = res[0];
        ((Pair *)out2)[i].y = res[1];
        if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[2 * i];     else ((s8 *)out3)[2 * i]     = tbl[2 * i];
        if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[2 * i + 1]; else ((s8 *)out3)[2 * i + 1] = tbl[2 * i + 1];
    }
    ((Pair *)out2)[i] = ((Pair *)out2)[0];
    if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[0]; else ((s8 *)out3)[2 * i]     = tbl[0];
    if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[1]; else ((s8 *)out3)[2 * i + 1] = tbl[1];
}


/* func_8013AF20 — MATCH (185 ins) — Phase 24 T7 Fable5 batch, giant 3/3.
 *
 * 3 GPU-primitive-builder loops (2× LINE_F2 len=3 code=0x40, 1× POLY_F4 len=5
 * code=0x28), each ending in the PS1 libgpu addPrim(ot, prim) idiom.
 *
 * THE CRACK (was: Opus close=15, permuter-stuck 40k iters — "loop-invariant
 * const-materialization order coupled to AND order"):
 *
 * 1) addPrim is a P_TAG BITFIELD store, not user masks. setaddr writes the
 *    24-bit `addr` field; gcc's store_fixed_bit_field (expmed.c:556) expands
 *    it as: value & 0x00ffffff FIRST (must_and :667, mask emitted :679-681),
 *    THEN *dest & 0xff000000 (:694-696), THEN or(destmasked, value) (:706 —
 *    dest chain stays op0 of the OR). So the 0x00ffffff movable is FOUND (and
 *    preheader-emitted by move_movables) BEFORE 0xff000000, while the body
 *    still computes the dest-AND first — the decoupling no user-mask C reorder
 *    can express (any `&`-operand swap flips the AND/OR shape with it).
 *
 * 2) NO scheduling barrier. The old do{}while(0) around the 0x3d stores added
 *    a NOTE_INSN_LOOP nest: flow.c weights refs by loop_depth (flow.c:2067/
 *    2315/2501/2711), inflating the 0x3d const's refs 7→10 and flipping the
 *    loop-1 $a2/$a3 contest (pri 4166 > 4000). With the bitfield form the
 *    barrier's original purpose (puVar5→$t1) holds without it.
 *
 * 3) Why the mask WINS $a2 (gdb-on-cc1 verified): sched1 pre-reload-splits
 *    every insn (sched.c:4830 try_split) → mips.md:3208 large_int define_split
 *    turns li 0xffffff into lui+ori → reg_n_sets=2 → FAILS the single-set gate
 *    (local-alloc.c:1021) → ESCAPES update_equiv_regs' live-length doubling
 *    (local-alloc.c:1064). One-instruction consts (61, 0x40, 3, 0xff000000)
 *    get doubled. Priorities (allocno_compare, global.c): mask fl2(7)*7/35 =
 *    4000 vs 0x3d fl2(7)*7/72 = 1944 → mask allocates first → first-fit $a2.
 *    (n_sets 61=1 mask=2 ff000000=1; LL 36/35/33 → post-equiv 72/35/66.)
 *
 * Cookbook §36 (this entry) + gcc-2.7.2-map/loop.md L4 / regalloc.md RC-7.
 */
DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013AF20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013B204 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (189/189). Levers: (1) POLY_FT4 UV stores in per-vertex source order
//   (u0,v0),(u1,v1),(u2,v2),(u3,v3) -> exact const-materialize schedule + 0xEF held in $v1 across
//   the angle branch, u3 store fills the bnez delay slot. (2) vertex reads *(volatile s32*) force
//   the target's reload-each-vertex (defeats CSE). (3) addPrim via P_TAG 24-bit bitfield store
//   (value-mask-first order, cookbook §36). (4) raw lwc2/mvmva/swc2 inline-asm + memory clobbers.
#include "common.h"


extern void *func_80010A08(s32);
extern s16 D_80187264, D_80187266, D_80187268, D_8018726A, D_8018726C, D_8018726E;
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
        if (!(D_80187266 < ang)) goto outer_else;
        if (!(ang < D_8018726C)) goto inner_else;
        if (ang < D_80187268) { *(s16 *)L = D_80187268; goto done; }
        if (D_8018726A < ang) { *(s16 *)L = D_8018726A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_80187264) { *(s16 *)L = D_80187264; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8018726E < ang) { *(s16 *)L = D_8018726E; goto done; }
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


/* func_8013B568..func_8013C964 (16 contiguous fns) moved to ov_SC01_077_o0.c — built -O0 (Phase-19 T1). */

