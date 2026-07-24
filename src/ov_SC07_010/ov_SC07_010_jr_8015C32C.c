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
extern void func_8013D53C(void);
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
extern u8 D_801202A0[];
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
extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
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
extern volatile u16 D_8011511A;
extern u16 D_8011512E;   /* §17a-1: canonical width (jr_8013F350 TUs decl u16); byte-neutral here (only use is store-0) */
extern s32  func_80029178(s32 a0);
extern void func_801418F8(void);
extern void func_80141A60(void);
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
extern s32 func_80142D38(s32 *a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_801428CC(s32 *a0);
extern void func_8014292C(int param_1);
extern void func_80142978(int param_1);
extern void func_801429C4(int param_1);
extern void func_80142A80(void);
extern void func_80142C7C(void);
extern void func_80142C84(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_80142C9C(s32 * arg0);
extern void func_80142B2C(void *arg0);
extern void func_80142DC4(int param_1);
extern void func_80142E38(int param_1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142EC0(s32 param_1);
extern void func_80142FFC(s32 *a0);
extern void func_8014305C(int param_1);
extern void func_80143188(s32 *a0);
extern void *memcpy(void *, const void *, u32);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801431E8(s32 param_1);
extern s32 func_8012C044(s32 a0);
extern void func_80142C9C(s32 *a0);
extern s32 func_8012BF10(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801432FC(s32 *a0);
extern void func_80143390(s32 *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80143458(s32 param_1);
extern void func_8014358C(s32 param_1);
extern u8 *func_8012913C(s32 a0);
extern s32 rand(void);
extern void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143970(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80143994(s32 a0, s32 a1);
extern void func_801439C0(u8 *a0);
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
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012B200(u8 *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80144558(u8 *param_1);
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
extern void func_80144B14(void);
extern void func_80144AEC(s32 *a0);
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
extern u8 D_800AF630[];
extern u8 D_80078EC0;
extern s32 D_80126B58;
extern void func_80145BF8(void);
extern void func_80145C54(void);
extern void func_80146014(s32 a0);
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);
extern void func_8014607C(void);
extern s32 *D_80126B78;
extern u8 D_80078EC1;
extern s32 D_80078EC8;
extern s32 D_80126B9C;
extern s32 D_8011F730;
extern u16 D_801152B8;
extern u16 D_8012693A;
extern u8 D_80126BE0[];
extern u8 D_801150F0[];
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
extern void func_80015978(s32 a0, s32 *a1);
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
extern s32 D_8011F750;
extern s32 D_8011F754;
extern u8 * func_801468C8(s32 arg0, u8 arg1);
extern s32 D_8011D030;
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146924(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80146994(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern s32 func_80146B9C(void *a0);
extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
extern u16 D_8011DA28;
extern s32 func_80146B9C(void * arg0);
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
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146F58(s32 a0, s32 a1);
extern void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80126DB0[];
extern u16 D_80126DB6;
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
extern void func_801470C0(s32 a0);
extern void func_80147118(s32 a0);
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
extern void func_80147364(u16, s32);
extern void func_80147300(u16 arg0);
extern void func_80147324(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80147460(s32 a0);
extern void func_80147514();
extern void func_80147628(s32 a0);
extern void func_80147478(s32 a0);
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
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_80147E44(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80147F50(s32 arg0);
extern volatile s32 D_80127090;
extern volatile s32 D_80127094;
extern volatile s32 D_80127098;
extern void func_80147F78(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80148038(s32 a0, s32 a1);
extern s32 csqrt(s32 a0);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80148094(int param_1, short *param_2, int *param_3);
extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern void func_801484B0(s32 a0, s32 a1);
extern s32 func_80154358(void *a0);
extern void func_801484E8(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_8014856C(s32 a0, s32 a1);
extern void func_801485B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80148634(void *a0);
extern u8 D_800B9A64;
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
extern s32 func_80047D3C(s32 a0);
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
extern s32 D_801151D4;
extern void func_80149204(s32 *a0);
extern void func_80149210(s32 a0, s32 a1);
extern s32 func_80149284(s32 *a0, s32 a1);
extern void func_80149350(s32 arg0);
extern void func_80149290(s32 a0);
extern void func_8012F14C(s32);
extern void func_8012F038(s32);
extern void func_8014942C(s32 arg0);
extern s32 func_801496D4(void *a0);
extern void func_8015AD08();
extern void func_80149704(void);
extern void func_8015ACC4();
extern void func_80149724(void);
extern u8 D_80078EBF;
extern s32 func_80149744(struct S_80149744 *a0);
extern void func_8015F7A0();
extern void func_80149788(void);
extern void func_801653B8();
extern void func_80149864(void);
extern s32 func_8016F1AC(void);
extern s32 func_80149884(void);
extern void func_80160B00();
extern void func_801498C0(void);
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
extern void func_80146750(void *a0);
extern s32 func_801498E0(s32 *a0);
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
extern void func_80149FA8(void);
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32, s32, s32, s32);
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
extern s32 func_8014A674(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015E184();
extern void func_8014A830(void);
extern s32 func_80029AF4(void);
extern s32 func_8014A850(s32 param_1);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80165A20(s32 a0);
extern void func_8014AB7C();
extern void func_8014AC10();
extern void func_8014AA28(void);
extern void func_8014AB5C(void);
extern void func_80162CCC(void);
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
extern u8 D_80078E78[];
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
extern void func_80166244();
extern void func_8014B4D4(void *a0);
extern s16 D_80078E9A;
extern u8 D_80126D1C;
extern s32 D_80126D74;
extern void func_8014B598(s32 a0, s32 a1);
extern void func_8014B5B0(s32 *a0);
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
extern u8 D_800B9A17;
extern void func_8014BCC0(s32 a0, s32 a1);
extern u16 D_80078EB6;
extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD60(s32 param_1, s32 param_2);
extern void func_8014BD98(s32 a0, u16 a1);
extern void func_8014BDC8(void);
extern void func_8014BDE0(void);
extern s32 func_8017267C(s32 *a0);
extern s32 func_80013294(void *a0, void *a1);
extern void func_80029ED4(s32 a0);
extern void func_8014BDE8(s32 a0);
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
extern s32 func_8014C088(s32 a0, s32 a1);
extern s32 func_8014C0C8(s32 a0_unused, s32 a1, s32 a2);
extern s32 func_8014C118(void * a0, s32 a1, s32 a2);
extern s32 func_8014C168(s32 * param_1, s32 param_2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_8014C1C8(s32 a0, s32 a1, void* a2);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
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
extern s32 func_8014C860(s32 a0, s32 a1);
extern void func_8014C8C8(s32 a0, s32 *a1);
extern void func_8014C88C(s32 a0);
extern void func_8014C8C8(s32 dst, s32 * src);
extern void func_8014C8F0(s32 arg0);
extern u8 D_801151F0[];
extern s32 func_8014C918(s32 a0, s32 a1);
extern s32 D_80126B50;
extern void func_8014C968(void);
extern void func_8014C978(void);
extern s32 func_8014C98C(void);
extern void func_80139914(s32 a0);
extern s32 func_8014CA00(s32 a0);
extern u16 func_8014CA70(s32 a0, s32 a1);
extern s32 func_8014CA14(s32 a0, s32 a1);
extern u16 func_8014CAE4(s32 *a0, s32 a1);
extern s32 func_8014CA88(s32 *a0, s32 a1);
extern s32 func_8014CAFC(void);
extern s32 func_8014CB0C(void);
extern s32 func_8014CB1C(void);
extern u8 D_80126D1F;
extern s32 func_8014CB2C(void);
extern s32 func_8014CB58(void);
extern u8 D_80126D1D;
extern void func_8014CB68(void);
extern s32 func_8014CB7C(void);
extern s32 func_8014CB8C(void);
extern struct Packed8 D_80126C98;
extern short D_80126C9E;
extern void func_8014CB9C(struct Packed8 *a0);
extern s32 D_80126CDC;
extern void func_8014CBD8(void);
extern void func_8014CBF8(void *a0);
extern void func_8014D3E0(s32 a0);
extern void func_8014D04C(void);
extern void func_8014CCB4(void);
extern void func_8014CC28(s32 a0);
extern void func_8014CD0C(u8 *a0);
extern void func_8014CF04(s32 a0, void *a1, void *a2);
extern void func_8014CD80(s32 a0, void *a1, void *a2);
extern void func_8014D2A0(s32 a0, void *a1, void *a2);
extern void func_8014D12C(s32 a0, void *a1, void *a2);
extern void func_8014D0A4(s32 a0);
extern void func_8014D610(s32 a0, void *a1, void *a2);
extern void func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern void func_8014D820(s32 a0, void *a1, void *a2);
extern void func_8014D790(s32 a0);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2);
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */
extern void func_8014DF94(s32 arg0);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */
extern s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);  /* canonical (engine_core.h:11555) */
extern s32 func_8014E284(s32 a0, s16 *arg1, s16 *arg2);
extern void func_8014E5B4(s32 a0, void *a1, void *a2);
extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2);
extern void func_8014E48C(s32 a0);
extern s32 func_8014E83C(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E790(s32 a0, s16 *a1, s16 *a2);
extern void func_8014E6F8(struct SubE6F8 *a0);
extern s32 func_8014E790(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014E83C(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_8014E98C(void *a0);
extern u16 D_800B99DA;
extern s32 D_801150D8;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014ED80(struct SubED80 *a0);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern void func_8014F4C0(u8 *a0);
extern void func_8014F468(void);
extern u8 D_800D3918[];
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern s32 func_80150170(void *a0);
extern s32 func_8014FE60(void *a0);
extern void func_8014FDF4(struct S8014FDF4 *a0);
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
extern s32 func_801506A4(s32 a0, s32 a1);
extern s32 func_801505FC(s32 a0);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8015086C(int param_1);
extern s32 func_801508B4(s32 a0);
extern s32 func_8015094C(s32 a0);
extern short func_801508F8(s32 a0);
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
extern u8 D_80126948[];
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
extern s32 func_8012DB84(void);
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
extern s32 func_80151944(void);
extern s32 func_80151924(void);
extern void func_8014E934(s32 a0);
extern void func_8014F3E8(s32 a0);
extern void func_801519C8(s32 a0);
extern void func_80151980(s32 a0);
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801519C8(s32 arg0);
extern void func_80151C54(s32 a0);
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_8015BDD0(s32 *a0);
extern void func_80165718(s32 a0);
extern u8 D_800D46E4[];
extern void func_80151AE4(s32 arg0);
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
extern void func_801553C0(s32 a0);
extern void func_80153C18();
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
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
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
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
extern void func_8014ED28(s32 _arg0);
extern void (*D_8011DB28)(s32 a0);
extern s32 func_801536DC(s32 param_1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
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
extern void func_80151664(void);
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
extern void func_800183E0(s32 a0);
extern void func_801550FC(s32 arg0);
extern void func_8001D150(s32, s32);
extern void func_8001D130(int, int);
extern void func_80155150(int param_1);
extern s32 D_800DE2A4[];
extern void func_801552F4(s32 a0);
extern void func_80155344(s32 a0);
extern s32 func_80155394(s32 *a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80029178(s32);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern s32 func_80161104(void);
extern void func_801555F4(void *);
extern void func_801555BC(void *a0);
extern int func_80155A44(int param_1);
extern int func_80161208();
extern u8 D_800D4DA8[];
extern void func_80155B20(s32 *a0);
extern s32 D_800D4DB4;
extern void func_80155B9C(s32 a0);
extern u8 D_800D4DD4[];
extern void func_80155C0C(s32 *a0);
extern void func_8014ED28(s32 a0);
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
extern int func_80156044(int arg, int a1);
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern S801563EC * func_801563EC(u16 idx);
extern s32 func_801564B0(s32 a0);
extern s32 D_801151E0[];
extern s32 func_801565C0(void);
extern void func_80156A14(s32 *a0);
extern void func_80156648(s32 *a0);
extern u8 D_8011DAD8[];
extern s32 func_8014C568(void *a0);
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void func_8014CC28(s32 a0);      /* defined  */
extern void func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
extern void func_80157580(s32 arg0);
extern u8 D_800D4F14[];
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_80157808(s32 a0);
extern void func_801577C8(int param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
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
extern void func_80157DC4(void *a0);
extern void func_80157FC4(void *a0);
extern void func_80157D74(u16 *a0);
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
extern void func_80158794(void);
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void func_80158AE4(void *a0);
extern void func_80158AB4(void *a0);
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
extern s32 func_8013767C(s32 a0);
extern void func_80158F00(int param_1);
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80158FA4(s32 param_1);
extern s32 func_801399F0(s32 a0);
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
extern void func_80129248(s16 a0);
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
extern void func_80159A20(void *a0);
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
extern s32 func_80161CD0(s32 a0, s32 a1);
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
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(void);
extern s32 func_8015B858(u8 *a0);
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
extern s32 func_8015B950(void);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern void func_8014D738(void);
extern s32 func_8015C128(s32 param_1);
/* ==== end §8b carried decl layer ==== */



extern u16 D_800B99DA;

extern s32 func_80149FB0(s32 a0);
extern s32 func_801496D4(void*);
extern void func_80149704(void);
extern s32 func_801619A4(s32*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_801498E0(s32*);
extern void func_80149954(s32 a0);
extern s32 func_80149A64(s32*);
extern void func_800CCCC0(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_8014D738(void);
extern void func_8014CC28(s32);
extern void func_8014F3E8(s32);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_80159BE4(s32 a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015C6E0(s32*);

void func_8015C32C(s32 arg0) {

    extern void (*D_8018465C[])(void *);
    s32 iVar2;
    u32 uVar4;
    s32 vin[4];
    s32 vout[4];

    func_80149FB0(arg0);
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_8018465C[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_8018465C[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_8018465C[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        func_80149954(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_8018465C[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
    }
    if ((func_80148AFC((void *)arg0) & 0xff) != 0) {
        vin[0] = 0;
        vin[1] = 0;
        vin[2] = -0x4000;
        func_8001382C((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), vin, vout);
        *(s32 *)(arg0 + 0x234) += vout[0];
        *(s32 *)(arg0 + 0x238) += vout[1];
        *(s32 *)(arg0 + 0x23c) += vout[2];
    }
    func_8001382C((s16)-*(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12), (void *)(arg0 + 0x234), vout);
    func_80146DB8((s32 *)arg0, vout);
    func_80147A84(arg0);
    ((void (*)(s32))func_801473EC)(arg0);
    if ((D_800B99DA & 3) == 0) {
        func_8014C010(arg0, 1);
        func_80147324(0x65f);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_8018465C[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    iVar2 = ((s32 (*)(s32))func_8014CC28)(arg0);
    uVar4 = ((u32 (*)(s32))func_8014F3E8)(arg0);
    if (uVar4 != 0) {
        if ((uVar4 & 0x4000) == 0) {
            if (func_80146E98(arg0) != 0) {
                D_8018465C[*(u16 *)arg0]((void *)arg0);
                func_80147078((s32 *)arg0, 0);
                func_80159BE4(arg0);
            }
        } else {
            func_80147078((s32 *)arg0, 4);
            func_8015C0C4(arg0);
        }
    } else {
        if (iVar2 == 0) {
            D_8018465C[*(u16 *)arg0]((void *)arg0);
            func_80147078((s32 *)arg0, 3);
            ((void (*)(s32))func_8015BE94)(arg0);
        }
    }
}


void func_8015C6A4(void) {
}

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015c6ac (src/shared) */


DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015c6e0 (src/shared) */




void func_8015C714(void *a0) {

    extern void (*D_801847E8[])(void);
    D_801847E8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015c750 (src/shared) */


DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015c788 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80149704(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);


void func_8015C7E4(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    extern int D_80184600;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_8018465C)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_8018465C)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184600);
                        ((void (*)(u16 *, s32))func_80146E90)(param_1, 0x14);
                        ((void (*)(u16 *))func_80146CA0)(param_1);
                    }
                    if ((param_1[0x5c] & 0x2000) != 0) {
                        ((void (*)(u16 *, s32))func_80161C24)(param_1, param_1[0xb7]);
                        ((void (*)(u16 *, s32))func_8014C010)(param_1, 2);
                    }
                }
            }
        }
    }
    return;
}




// @class: struct
// @stuck: none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


void func_8015C944(int param_1) {

    extern void (*D_8018465C[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_8018465C[*(unsigned short *)param_1])(param_1);
        ((void (*)(int, int))func_80147078)(param_1, 0);
        ((void (*)(int))func_80159B70)(param_1);
    } else {
        if (((int (*)(int))func_80161240)(param_1) == 0) {
            if (func_80146E98(param_1) != 0) {
                ((void (*)(int))func_80146CA0)(param_1);
            }
            if ((*(unsigned short *)(param_1 + 0xb8) & 0x2000) != 0) {
                func_80161C24(param_1, *(unsigned short *)(param_1 + 0x16e));
            }
        }
    }
}



// @class: schedule
// @stuck: none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80161240(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80149704(void);


void func_8015CA28(u16 *param_1) {

    extern void (*D_8018465C[])(void*);
    extern int D_80184600;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_8018465C)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184600);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_8018465C)[*param_1](param_1);
    ((void (*)(u16 *, int))func_80147078)(param_1, 0);
    ((void (*)(u16 *))func_80159B70)(param_1);
    return;
do161240:
    ((void (*)(u16 *))func_80161240)(param_1);
}


DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015cb94 (src/shared) */


void func_8015CBCC(void) {
}

void func_8015CBD4(void) {
}

void func_8015CBDC(void) {
}

void func_8015CBE4(void) {
}

void func_8015CBEC(void) {
}

void func_8015CBF4(void) {
}

void func_8015CBFC(void) {
}

void func_8015CC04(void) {
}

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015cc0c (src/shared) */


DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015cc40 (src/shared) */




void func_8015CC74(s32 *a0) {

    extern void (*D_801847F8[])(void);
    D_801847F8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015ccb0 (src/shared) */


DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015ccd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015CD20);

DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015cf24 (src/shared) */


DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015cf58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015cf8c (src/shared) */




void func_8015CFC0(s32 *a0) {

    extern void (*D_80184830[])(void);
    D_80184830[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015cffc (src/shared) */


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_80184820;

    int iVar4;
    register unsigned short uVar1 __asm__("$19");
    register unsigned short uVar5 __asm__("$17");
    short sVar2;
    short sVar3;

    ((void (*)(int, void *))func_80154274)(param_1, &D_800D550C);
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    iVar4 = *(short *)(*(int *)(param_1 + 0x20) + 0x12);
    uVar1 = *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x180) + 0x20) + 0x12);
    uVar5 = (uVar1 + 0x800) & 0xfff;
    sVar2 = func_80012A60(iVar4, (short)uVar1);
    sVar3 = func_80012A60(iVar4, uVar5);
    if (sVar2 < sVar3) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar1;
    } else {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar5;
    }
    *(int *)(param_1 + 0x38) = (int)&D_80184820 | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}




// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {

    extern void (*D_8018465C[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((void (*)(void *))func_801725F4)(arg0);
        *(s32 *)((u8 *)arg0 + 0x234) = 0xFF1D0000;
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10) = 0x600;
        *(u16 *)((u8 *)arg0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10);
        func_80146CA0(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015D1B8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015D380);


// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_80183970[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_80183970;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015d480 (src/shared) */


DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015d4b4 (src/shared) */




s32 func_8015D4E8(s16 *a0) {

    extern void (*D_80184894[])(void);
    D_80184894[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015d524 (src/shared) */


DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015d544 (src/shared) */


DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015d57c (src/shared) */



// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);


void func_8015D5E8(int param_1)
{

    extern unsigned char D_801848A0[];
    int iVar1;
    int iVar2;

    if (((int (*)(void))func_80161B18)() != 0)
        return;
    if (((int (*)(int))func_80161B84)(param_1) != 0)
        return;
    if ((*(unsigned short *)(param_1 + 0xb8) & 0x4000) != 0)
        func_80154A74(param_1, 0x17);
    if (((int (*)(int))func_80161208)(param_1) != 0)
        return;
    if (*(unsigned short *)(param_1 + 0xb8) == 0x8000) {
        *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + -3;
        func_80154150(param_1, 0x1a);
        ((void (*)(int))func_80146CA0)(param_1);
    } else {
        iVar1 = *(int *)(param_1 + 0x178);
        if (iVar1 != 0) {
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 6) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015da5c (src/shared) */


DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015da90 (src/shared) */


DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015dac4 (src/shared) */




void func_8015DAF8(s32 *a0) {

    extern void (*D_801848D4[])(void);
    D_801848D4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015db34 (src/shared) */


DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015db6c (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015dc84 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {

    extern s8 D_801848DC[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015dd74 (src/shared) */


DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015ddf0 (src/shared) */


DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015de24 (src/shared) */




void func_8015DE58(s32 *a0) {

    extern void (*D_801848F4[])(void);
    D_801848F4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015de94 (src/shared) */


DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015decc (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015dfe4 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {

    extern s8 D_801848DC[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015e0d4 (src/shared) */


DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015e150 (src/shared) */


DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015e184 (src/shared) */




s32 func_8015E1B8(s32 a0) {

    extern void (*D_80184914[])(void);
    D_80184914[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015e1f4 (src/shared) */


DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015e22c (src/shared) */


DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015e288 (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);


void func_8015E344(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_8018465C)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015e40c (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{

    extern u16 D_80184924;
    extern u16 D_80184926;
    extern u16 D_80184928;
    extern s32 D_8018492C;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80184924 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80184926 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80184928 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_8018492C, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015E588);

DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015e5b0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */

void func_8015E698(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_8018465C)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015e714 (src/shared) */


DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015e84c (src/shared) */


DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015e880 (src/shared) */


DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015e8b4 (src/shared) */




void func_8015E8E8(s32 *a0) {

    extern void (*D_80184948[])(void);
    D_80184948[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015e924 (src/shared) */


DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015e95c (src/shared) */


DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015e9b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015EA3C);

DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ed6c (src/shared) */


DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015eda0 (src/shared) */


DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015edd4 (src/shared) */




s32 func_8015EE08(s32 a0) {

    extern void (*D_80184950[])(void);
    D_80184950[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015ee44 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);


void func_8015EE7C(s32 param_1)
{

    extern int D_800D4C48;
    extern int D_80184640;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_80184640);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}




extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_8015EEE0(void *arg0)
{

    extern void (*D_8018465C[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}


void func_8015EF9C(void) {
}

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015efa4 (src/shared) */


DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015efd8 (src/shared) */




void func_8015F00C(s32 *a0) {

    extern void (*D_80184958[])(void);
    D_80184958[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015f048 (src/shared) */


DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015f080 (src/shared) */


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {

    extern s32 D_80062BE8;
    extern void (*D_8018465C[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_8018465C[*(u16 *)a0])(a0);
        ((void (*)(void *, s32))func_80147078)(a0, 0);
        func_80159B70(a0);
    } else {
        if (flag & 0x4000) {
            ((void (*)(s32))func_8014AB5C)(0x19);
            ((void (*)(s32))func_8014AB5C)(0x1D);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 1, 0, 1);
            func_801466F0(0x1D, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_80019064(&D_80062BE8);
            func_80147324(0x9DA);
        }
        if (((s32 (*)(s32 *))func_80161208)(a0) == 0) {
            func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
        }
    }
}


DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015f260 (src/shared) */


DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015f2bc (src/shared) */


DEFINE_func_8015F2F0()  /* dedup: shared engine-core @0x8015f2f0 (src/shared) */




void func_8015F324(s32 *a0) {

    extern void (*D_80184960[])(void);
    D_80184960[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015f360 (src/shared) */


DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015f380 (src/shared) */




extern s32 func_80149884(void);
extern s32 func_801496D4(void*);
extern void func_80149724(void);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_80146DB8(s32*, s32*);
extern void func_80146E90(s32*, s32);
extern void func_8014ED28(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_801725B8(u8*);
extern void func_80147324(s32 a0);
extern void func_80019064(void*);
extern void func_801484B0(s32, s32);
extern void func_80148534(s32, s32);

void func_8015F448(s32 arg0) {

    extern void (*D_8018465C[])(void *);

    extern u8 D_80062BD0;
    extern s32 D_80184968;
    extern s32 D_80184978;
    extern s32 D_80184988;
    s32 sp20[2];
    s32 sp28[2];

    if (((*(u32 *)(arg0 + 0x44) & 0x100) && (func_80149884() != 0)) ||
        (((s32 (*)(s32))func_801496D4)(arg0) != 0)) {
        D_8018465C[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0);
        return;
    }

    if (*(u8 *)(arg0 + 0x245) == 0) {
        if (*(u8 *)(arg0 + 0x244) == 0) {
            if (((s32 (*)(s32))func_80148800)(arg0) & 0x10) {
                *(u8 *)(arg0 + 0x244) = 1;
                *(u8 *)(arg0 + 0x245) = 1;
            }
        } else if (((s32 (*)(s32))func_80148800)(arg0) & 0x80) {
            *(u8 *)(arg0 + 0x244) = 0;
            *(u8 *)(arg0 + 0x245) = 1;
        }
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x3000) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            ((void (*)(void *, void *))func_801484B0)(sp20, sp28);
            func_80147324(0x56D);
        } else {
            ((void (*)(void *, void *))func_80148534)(sp20, sp28);
            func_80147324(0x56E);
        }
        ((void (*)(s32 *))func_80019064)(&(*(s32 *)&D_80062BD0));
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 0, 0);
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 1, 0);
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
        if (*(u8 *)(arg0 + 0x245) != 0) {
            *(u8 *)(arg0 + 0x245) = 0;
            *(u16 *)(arg0 + 0xB8) = *(u16 *)(arg0 + 0xBA);
            if (((s32 (*)(s32))func_80148980)(arg0) != 0) {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184968);
            } else {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184978);
            }
        }
    } else {
        *(u16 *)(arg0 + 0x246) = *(u16 *)(arg0 + 6);
        *(u16 *)(arg0 + 0x248) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(arg0 + 0x24A) = *(u16 *)(arg0 + 0xE);
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (((s32 (*)(s32))func_8014F1F4)(arg0) != 0) {
            *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 0x246);
            *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x248);
            *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x24A);
        }
    }

    if (((s32 (*)(s32))func_8014FCFC)(arg0) == 0) {
        D_8018465C[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFE80000);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80184988);
        ((void (*)(s32, s32))func_80146E90)(arg0, 0x10);
        return;
    }

    func_8014ED28(arg0);
    func_8014FA04(arg0);
    ((void (*)(s32))func_801725B8)(arg0);
}


DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015f738 (src/shared) */


DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015f76c (src/shared) */


DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015f7a0 (src/shared) */




s32 func_8015F7D4(s32 a0) {

    extern void (*D_80184998[])(void);
    D_80184998[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015f810 (src/shared) */


DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015f848 (src/shared) */



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

void func_8015F89C(void *arg0) {

    extern void (*D_8018465C[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_8018465C[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015f948 (src/shared) */



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

void func_8015F9A4(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015fa24 (src/shared) */


DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015fa44 (src/shared) */


DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015fa78 (src/shared) */




void func_8015FAAC(s32 *a0) {

    extern void (*D_801849A4[])(void);
    D_801849A4[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_8018465C[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8015FBE0);

extern void func_801599A4(void *a0);

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)


extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018465C[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018465C[*(u16 *)param_1](param_1);
        ((void (*)(void *, s32))func_80147078)(param_1, 0);
        func_80159B70(param_1);
    } else {
        *(u8 *)((s32)param_1 + 0x197) = 0;
        *(u8 *)((s32)param_1 + 0xBE) = 0;
        *(u8 *)((s32)param_1 + 0xBF) = 0;
        *(u8 *)((s32)param_1 + 0x1A0) = (u8)*(s32 *)((s32)param_1 + 0x184);
        ((s32 (*)(void *, s32))func_8014BFF4)(param_1, 1);
        func_80146CA0(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple 3-call sequence with global table index


extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{

    extern unsigned int D_801849B8[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_801849B8[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015fdcc (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_8018465C)[param_1[0]]();
            ((void (*)(u16 *, s16))func_80147078)(param_1, 0);
            ((void (*)(u16 *))func_80159B70)(param_1);
            return;
        }
        param_1[0x5c] = param_1[0x5d];
    }
    if ((param_1[0x5c] & 0x4000) != 0) {
        ((void (*)(u16 *, s16))func_80154A74)(param_1, 0x11);
    }
    ((void (*)(u16 *))func_80161208)(param_1);
}




extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

void func_8015FF20(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018465C[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018465C[*(u16 *)param_1](param_1);
        ((void (*)(void *, s16))func_80147078)(param_1, 0);
        func_80159B70(param_1);
        return;
    }

    v2 = *(s32 *)((s32)param_1 + 0x184);
    if (v2 < 0) {
        func_80150820((s32)param_1, func_801656E8((s32)param_1, v2 & 0xFF) & 0xFF);
    } else {
        if (*(u8 *)((s32)param_1 + 0x1A0) != *(u8 *)((s32)param_1 + 0x196)) {
            *(u8 *)((s32)param_1 + 0x1A0) = (u8)v2;
            *(u8 *)((s32)param_1 + 0x197) = 0;
            *(u8 *)((s32)param_1 + 0xBE) = 0;
            *(u8 *)((s32)param_1 + 0xBF) = 0;
            func_8014BFF4((s32)param_1, 1);
        }

        cur = *(u8 *)((s32)param_1 + 0x1A0);
        D_80078EC1 = cur;
        D_80078EC2 = cur;
        func_80165670((s32)param_1, cur);
        ((void (*)(void *))func_80165840)(param_1);
        ((void (*)(void *))func_801658DC)(param_1);
        func_80154A74((s32)param_1, 0x11);
        D_801270C0 = 1;
    }

    ((void (*)(void *))func_8016004C)(param_1);
}


DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004c (src/shared) */


DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007c (src/shared) */


DEFINE_func_801600D0()  /* dedup: shared engine-core @0x801600d0 (src/shared) */


DEFINE_func_80160104()  /* dedup: shared engine-core @0x80160104 (src/shared) */




void func_80160138(s32 *a0) {

    extern void (*D_80184A34[])(void);
    D_80184A34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */


DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601ac (src/shared) */


DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601e4 (src/shared) */


DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */



extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {

    extern void (*D_8018465C[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_8018465C)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


void func_8016032C(void) {
}

DEFINE_func_80160334()  /* dedup: shared engine-core @0x80160334 (src/shared) */


DEFINE_func_80160368()  /* dedup: shared engine-core @0x80160368 (src/shared) */




void func_8016039C(s32 *a0) {

    extern void (*D_80184A44[])(void);
    D_80184A44[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603d8 (src/shared) */


DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */








/* data */

/* callees (engine_core.h canonical sigs) */
extern void func_80149020(s32 *a0);
extern void func_80149034(s32 *a0);
extern u16  func_80148800(s32 *a0);
extern s32  func_80149B54(s32 *a0);
extern void func_80149BAC(s32 *a0);
extern s32  func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32  func_80146E98(s32 a0);
extern u16  func_801487F4(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_80159B70(void *a0);
extern s32  func_800CF8B4();
extern s32  func_801491C4(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32  func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F00C(s32 *a0);

void func_80160534(u8 *p) {

    extern u8  D_80078EC0;
    extern u8  D_80078EBF;
    extern s16 D_801152A0;
    extern void (*D_8018465C[])(void *);
    func_80149020((s32 *)p);
    func_80149034((s32 *)p);
    if ((D_80078EC0 & 0x7F) != 0 && (func_80148800((s32 *)p) & 0x90) != 0) {
        if (D_80078EBF == 0x80) {
            D_8018465C[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x13);
            func_8015F00C((s32 *)p);
            return;
        }
        if (func_80149B54((s32 *)p) != 0) {
            D_8018465C[*(u16 *)p](p);
            func_80149BAC((s32 *)p);
            return;
        }
    }
    if (func_80149AA8((s32 *)p) != 0) {
        D_8018465C[*(u16 *)p](p);
        func_80149AD4((s32 *)p);
        return;
    }
    if (func_80146E98((s32)p) != 0) {
        if ((func_801487F4((s32 *)p) & 8) != 0) {
            D_8018465C[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x11);
            func_8015E9B8((s32 *)p);
        } else {
            D_8018465C[*(u16 *)p](p);
            func_80147078((s32 *)p, 0);
            func_80159B70(p);
        }
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
            ((*(u16 *)&D_801152A0) + func_801491C4((s32)p)) & 0xFFF;
    }
    func_80147AD4((s32)p, *(s32 *)(p + 0x234), *(s32 *)(p + 0x238),
                  *(s32 *)(p + 0x23C));
    func_801473EC((s32 *)p);
    if (((s32 (*)(s32 *))func_8014D738)((s32 *)p) != 0) {
        D_8018465C[*(u16 *)p](p);
        func_80147078((s32 *)p, 9);
        func_8015C714(p);
    } else {
        ((s32 (*)(void *))func_80161208)(p);
    }
}


DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607b8 (src/shared) */


DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607e4 (src/shared) */


DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */




void func_8016084C(s32 *a0) {

    extern void (*D_80184A4C[])(void);
    D_80184A4C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */


DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608c0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)



extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_8018465C[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_8018465C)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))func_80154150)(param_1, 0x25);
            ((void (*)(unsigned short *))func_80146CA0)(param_1);
        }
    }
    return;
}




// @class: struct
// @stuck: none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */

void func_801609B8(u16 *param_1) {

    extern void (*D_8018465C[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_8018465C)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160a28 (src/shared) */


DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160a74 (src/shared) */


DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160acc (src/shared) */


DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160b00 (src/shared) */




s32 func_80160B34(s32 a0) {

    extern void (*D_80184A58[])(void);
    D_80184A58[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160b70 (src/shared) */


DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160bb4 (src/shared) */


DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160c28 (src/shared) */


DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160cb4 (src/shared) */


extern void func_8015DBD4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_8018465C + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_8018465C[*(u16 *)arg0](arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x1AC) == 0) {
            if ((((s32 (*)(void *))func_80148800)(arg0) & 0xF0) == 0) {
                goto dd0;
            }
        } else {
            s32 t = *(s32 *)((u8 *)arg0 + 0x1AC) - 0xAAA8;
            *(s32 *)((u8 *)arg0 + 0x1AC) = t;
            if (t >= 0) {
                goto dd0;
            }
        }
        D_8018465C[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160dec (src/shared) */


DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160e3c (src/shared) */


DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160e70 (src/shared) */




void func_80160EA4(void *a0) {

    extern void (*D_80184A68[])(void);
    D_80184A68[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160ee0 (src/shared) */


DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160f00 (src/shared) */


DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160f70 (src/shared) */


DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160fe0 (src/shared) */



// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{

    extern void (*D_8018465C[])(void *);
    func_80149020(a0);
    D_8018465C[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */


void func_801610FC(void) {
}

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */


DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161208);

DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */


DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */


DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016130C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161374);

DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */


DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */


DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */


DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614e4 (src/shared) */


DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151c (src/shared) */


DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */


DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158c (src/shared) */


DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615c4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016163C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161774);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161888);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016191C);

DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197c (src/shared) */


DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619a4 (src/shared) */


DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619d0 (src/shared) */


DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161a00 (src/shared) */


DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161a30 (src/shared) */


DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161a60 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161A90);

DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161b18 (src/shared) */


DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161b84 (src/shared) */


DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161be0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161C24);


// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_80184A98[];
    if (param_2 < 8) {
        func_80147324(D_80184A98[param_2]);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161CD0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161d58 (src/shared) */



// @class: other
// @stuck: none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);

void func_80161D88(void) {

    extern s32 D_800AE6B0;
    extern s32 D_800AE6A8;
    extern s32 D_80184AFC;
    if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (func_80029178(0x141) & 0xFF) != 0) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_80184AFC);
    }
}


extern s32 func_800291DC(s32);







void func_80161E08(s32 param_1) {

    extern u8 D_800AF630[];
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_80078EB0;
    extern u16 D_800B5BD8;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern u16 D_800B5C10;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern u16 D_800B5C48;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_801A6BA8[];
    extern u8 D_80184AC8[];
    extern u8 D_80184AE8[];
    extern u8 D_801A6BB4[];
    extern u8 D_801A6BDC[];
    extern u8 D_801A6BF4[];

    u8 *base = &(*(u8 *)&D_800AF630);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (D_800B5BD8 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65A8));
            D_801A6BA8[0] = p;
            func_80024054(&D_80184AC8, &D_801A6BB4);
            func_8001CE28(p, &D_801A6BB4);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801A6BA8[1] = p;
            func_80024054(&D_80184AE8, &D_801A6BDC);
            func_8001CE28(p, &D_801A6BDC);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801A6BA8[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801A6BF4, 0x84);
            func_8001CE68(p, &D_801A6BF4);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801A6BF4, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620c4 (src/shared) */


DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_8016216C(void)
{

    extern int D_801A6BA8[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801A6BA8;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



extern s32 func_800291DC(s32);

s32 func_801621CC(s32 arg0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    extern s32 D_80184AFC;
    register s32 s0 __asm__("$16") = arg0;       /* $s0: arg0, crosses the call */
    register u8 *s1 __asm__("$17") = D_80078E78; /* $s1: base, hoisted for the loop */
    register s32 i __asm__("$5");                /* $a1: counter (pin fixes the i/d swap) */
    u32 a2;
    s32 d;                                       /* $a0: natural alloc; load via $v0 temp */
    s32 v, last, hi, lo;
    char pad[8];                                 /* phantom 8B local -> frame 0x28 (vars=8) */

    a2 = func_800291DC(8);
    if ((a2 & 0x8000) == 0) {
        return 0;
    }
    a2 &= 0x7FFF;
    if (((a2 >> 8) == D_80078EB1) && ((a2 & 0xFF) <= (u32)D_80078EB0)) {
        return (s32)&D_80184AFC;
    }
    d = s1[0x39] - 1;
    i = 0;
    if (s0 <= 0) {
        return 0;
    }
    hi = (a2 >> 8) & 0xFF;
    last = s0 - 1;
    lo = a2 & 0xFF;
    do {
        if ((s8)d < 0) {
            d = 0x17;
        }
        v = (s8)d;
        if (hi == v) {
            if (i != last) {
                return (s32)&D_80184AFC;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80184AFC;
            }
            goto bot;
        }
        i++;
    bot:
        d--;
    } while (i < s0);
    return 0;
}



// @class: schedule
// @stuck: none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

void func_801622C4(void)
{

    extern int D_801A6BA8[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801A6BA8;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_80184B20[])(void);
    D_80184B20[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236c (src/shared) */


DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623b8 (src/shared) */


DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */


extern s32 func_800291DC(s32);








s32 func_80162438(s32 _unused0) {

    extern s16 D_80078EB0;
    extern u8 D_800AF630[];
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80184B2C[];
    extern s32 D_80184B44;
    extern u8 D_801A6C0C[];
    extern u8 D_801A6C34[];
    extern u8 D_801A6C50[];
    extern int D_801A6C00[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    register u8 *base __asm__("$18");
    register u8 *item __asm__("$17");

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            register u8 *t __asm__("$2") = base + 0x65A8;
            item = t;
            D_801A6C00[0] = (s32)item;
            func_80024054(D_80184B2C, D_801A6C0C);
            func_8001CE28(item, D_801A6C0C);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801A6C00[1] = (s32)item;
            func_80024054(((u8 *)&D_80184B44), D_801A6C34);
            func_8001CE28(item, D_801A6C34);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801A6C00[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801A6C50, 0x84);
            func_8001CE68(item, D_801A6C50);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801A6C50, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626b8 (src/shared) */


DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_80162760(void)
{

    extern int D_801A6C00[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_801A6C00;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801627E8);



void func_80162834(void *a0) {

    extern void (*D_80184B68[])(void);
    D_80184B68[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_80184B58;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_80184B58, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628f4 (src/shared) */


DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */


DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162ac0 (src/shared) */


DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162acc (src/shared) */


DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162ae0 (src/shared) */


DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162af4 (src/shared) */


DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162b1c (src/shared) */


void func_80162CC4(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80162CCC);

DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162d28 (src/shared) */


DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162d88 (src/shared) */


DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162de8 (src/shared) */


DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162e48 (src/shared) */


DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162ea8 (src/shared) */


DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162f08 (src/shared) */


DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162f60 (src/shared) */


DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162f80 (src/shared) */


DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162fa0 (src/shared) */


DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162fc0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80162FF4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801630C4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80163194);

DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016325C);

DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632e0 (src/shared) */


DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632f0 (src/shared) */


DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */


DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633a8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (21 ins, relocation-masked)


s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern unsigned char D_801A6448[8];

    unsigned char sp18[8];
    memcpy(sp18, D_801A6448, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}


DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345c (src/shared) */



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char D_801A6448[8];
    char buf[8];

    memcpy(buf, D_801A6448, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80163534);

DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */


DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636d0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80163764);

DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380c (src/shared) */


DEFINE_func_801638A0()  /* dedup: shared engine-core @0x801638a0 (src/shared) */


DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */




void func_80163A58(void *a0) {

    extern void (*D_80184B70[])(void);
    D_80184B70[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163a94 (src/shared) */


DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163c2c (src/shared) */


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149350(s32 arg0);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern s32 func_8014CA00(s32 a0);
extern u16 func_80156370(u16 a0);
extern void func_80162D88(s32 *a0);

void func_80163EC8(s32 param_1) {
    extern Blk8 D_801A6450;
    extern u16 D_800B99DA;
    extern u8 func_801656D0(s32 a0, s32 a1);
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    Blk8 in;
    u16 out[4];
    s16 buf[4];
    s32 psVar6;
    s32 iVar8;
    s32 iVar7;
    register s32 uVar5 __asm__("$2");   /* PIN (flagged): uVar5 -> $v0 */
    u16 uVar4;
    u8 uVar3;

    in = D_801A6450;
    psVar6 = *(s32 *)(param_1 + 0x4c);
    iVar8 = *(s32 *)(param_1 + 0x20);
    func_80162D88((s32 *)param_1);

    if (*(s32 *)(psVar6 + 0x184) == 0) {
        uVar5 = *(s32 *)(psVar6 + 0x44);
        *(s16 *)(psVar6 + 0x18a) = 0;
        *(s16 *)(psVar6 + 0x188) = 0;
        *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
        func_80146CA0((void *)param_1);
        func_80146CA0((void *)param_1);
        return;
    }
    if (*(s16 *)(*(s32 *)(psVar6 + 0x184) + 0x36) == *(u16 *)(psVar6 + 0x194)) {
        goto LAB_matched;
    }
    *(s32 *)(psVar6 + 0x184) = 0;
    uVar5 = *(s32 *)(psVar6 + 0x44);
    *(s16 *)(psVar6 + 0x18a) = 0;
    *(s16 *)(psVar6 + 0x188) = 0;
    *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);
    return;

LAB_matched:
    *(s16 *)(psVar6 + 0x18a) = *(u16 *)(psVar6 + 0x18a) + 1;
    if ((D_800B99DA & 3) == 0) {
        if (*(s16 *)(psVar6 + 0x188) >= *(u8 *)(param_1 + 0x67)) {
            *(s16 *)(psVar6 + 0x188) = *(s16 *)(psVar6 + 0x188) - *(u8 *)(param_1 + 0x67);
        } else {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
        if (*(s16 *)(psVar6 + 0x188) < 0) {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
    }

    *(s16 *)(param_1 + 0x66) = *(u16 *)(param_1 + 0x66) + 0x40;
    uVar5 = func_80148800((s32 *)psVar6);
    if ((uVar5 & 0x80) != 0) {
        *(s16 *)(param_1 + 0x66) = 0;
        uVar3 = func_801656D0(psVar6, func_8014CA00(*(s32 *)(psVar6 + 0x184)) & 0xff);
        *(s16 *)(psVar6 + 0x188) = *(u16 *)(psVar6 + 0x188) + uVar3;
        *(s16 *)(iVar8 + 0x1a) = 0x4000;
        *(s16 *)(iVar8 + 0x18) = 0x4000;
        *(s32 *)(iVar8 + 0x48) = *(s16 *)(param_1 + 0x58);
        *(s32 *)(iVar8 + 0x4c) = *(s16 *)(param_1 + 0x5a);
        *(s32 *)(iVar8 + 0x50) = *(s16 *)(param_1 + 0x5c);
        ((void (*)(s32, s32, s32))func_80149350)(param_1, (s32)&in, (s32)out);
        *(s16 *)(param_1 + 0x6) = out[0];
        *(s16 *)(param_1 + 0xa) = out[1];
        *(s16 *)(param_1 + 0xe) = out[2];
    }

    if (0x80 < *(s16 *)(psVar6 + 0x188)) {
        *(s16 *)(psVar6 + 0x188) = 0x80;
    }
    if (*(s16 *)(psVar6 + 0x188) >= 0x80) {
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0xe);
            func_8014C4AC(iVar7, 0xe, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            func_80146994(0x33, param_1, 0, iVar7);
        }
    } else {
        if (*(s16 *)(psVar6 + 0x18a) < 0x80 && *(u16 *)psVar6 != 0x19) {
            goto LAB_end;
        }
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0x21);
            func_8014C4AC(iVar7, 0x21, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            if ((*(s32 *)(iVar7 + 0xb4) & 0x40000) != 0) {
                func_8014AD30(param_1, (u16 *)buf, 0, *(s16 *)(iVar7 + 0x60));
            }
        }
    }

    uVar5 = func_8014CA00(iVar7);
    *(s32 *)(psVar6 + 0x184) = uVar5;
    if (0x1e < (u32)uVar5) {
        *(s32 *)(psVar6 + 0x184) = 0;
    }
    func_80146E90((s32 *)param_1, 0x20);
    *(s32 *)(psVar6 + 0x44) = *(s32 *)(psVar6 + 0x44) & ~0x20;
    func_80147324(0x449);
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);

LAB_end:
    uVar4 = func_80012F74(*(s16 *)(iVar8 + 0x1a), 0x1800, 3, 1);
    *(s16 *)(iVar8 + 0x1a) = uVar4;
    *(s16 *)(iVar8 + 0x18) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0x6), *(s16 *)(param_1 + 0x58), 8, 1);
    *(s16 *)(param_1 + 0x6) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xa), *(s16 *)(param_1 + 0x5a), 8, 1);
    *(s16 *)(param_1 + 0xa) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xe), *(s16 *)(param_1 + 0x5c), 8, 1);
    *(s16 *)(param_1 + 0xe) = uVar4;
}


DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */


DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642ac (src/shared) */


DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432c (src/shared) */


void func_80164410(void) {
}

DEFINE_func_80164418()  /* dedup: shared engine-core @0x80164418 (src/shared) */

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_80184BC4[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_80184BC4[*(u16 *)(param_1 + 2)]();
    if (iVar1 != 0) {
        ((void (*)(s32))func_80162D28)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);


void func_801647A4(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_80184B8C;
    extern u16 D_80184BC0;
    extern s16 D_80184BBE;
    extern s16 D_80184BBC;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_80184B8C;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_80184BC0 = 0x80;
        D_80184BBE = 0x80;
        D_80184BBC = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80164930);

DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164a74 (src/shared) */


DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164acc (src/shared) */




void func_80164BA0(void *a0) {

    extern void (*D_80184BD0[])(void);
    D_80184BD0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_801A6C60;
    extern u8 D_801A6C61;
    extern u8 D_801A6C62;
    extern u8 D_801A6C63;
    extern u8 D_801A6C64;
    extern u8 D_801A6C65;
    extern u8 D_801A6C66;
    extern u8 D_801A6C67;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801A6C60;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801A6C61 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801A6C62 = 0xc0;
        D_801A6C66 = 0;
        D_801A6C65 = 0;
        D_801A6C64 = 0;
        D_801A6C67 = 0;
        D_801A6C63 = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}


DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164cd4 (src/shared) */


DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164d4c (src/shared) */


DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164db0 (src/shared) */


DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164dd0 (src/shared) */







s32 func_80164E40(void) {

    extern u8 D_801A6C60;
    extern u8 D_801A6C61;
    extern u8 D_801A6C62;
    u8 *p = &D_801A6C60;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_801A6C61 != 0) {
        D_801A6C61 -= 0x10;
    }
    if (D_801A6C62 != 0) {
        D_801A6C62 -= 0x10;
    }
    return *(s32 *)p == 0;
}




void func_80164EA4(void *a0) {

    extern void (*D_80184BE0[])(void);
    D_80184BE0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_801A6CAC[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_801A6CAC[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164f44 (src/shared) */


DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */


DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */


DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650c4 (src/shared) */


DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */



// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_801A6CA0[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




s32 func_80165140(s32 param_1) {
    extern Slot D_801A6CA0[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_801A6CA0[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern void func_80165240(void *param_1, void *param_2, void *param_3);

void func_801651B8(void * param_1)
{

    extern s32 D_801A6CA0;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801A6CA0;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            ((s32 (*)(s32, s32, s32))func_80165240)(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}


extern void func_80016ED4(void *a0);
extern s32 func_80017DC4(void *a0, void *a1);

void func_80165240(void *param_1, void *param_2, void *param_3)
{

    extern u8 D_80184BF4[];
    extern u32 D_80184C14, D_80184C18, D_80184C1C, D_80184C20;
    extern u32 D_80184C14, D_80184C18, D_80184C1C, D_80184C20;
    extern u32 D_80184C14, D_80184C18, D_80184C1C, D_80184C20;
    extern u32 D_80184C14, D_80184C18, D_80184C1C, D_80184C20;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ApplyMatrixSV(mat, &D_80184BF4[0x00], p);
    ApplyMatrixSV(mat, &D_80184BF4[0x08], prim + 0x08);
    ApplyMatrixSV(mat, &D_80184BF4[0x10], prim + 0x10);
    ApplyMatrixSV(mat, &D_80184BF4[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_80184C1C;
    *(u32 *)(prim + 0x24) = D_80184C14;
    *(u32 *)(prim + 0x28) = D_80184C20;
    *(u32 *)(prim + 0x2c) = D_80184C18;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}


DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533c (src/shared) */


DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */


DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653b8 (src/shared) */


DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653f4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC1;
    extern void (*D_80184C24[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_80184C24[D_80078EC1 & 0x7F])(arg0);
            }
        }
    }
    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 == 0x1A) {
        return;
    }
    if (s1[0x49] == 0x19) {
        func_800CAE0C(arg0);
    }
}



// @class: struct
// @stuck: none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{

    extern u8 D_80078EC5;
    extern u8 D_80078EC1;
    extern void (*D_80184C24[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80184C24[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655e4 (src/shared) */


DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_80184CA0[];
    return D_80184CA0[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_80184CC0[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_80184CC0[a1 & 0x7F];
}


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_80184D3C[];
    return D_80184D3C[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_80184D5C[];
    return D_80184D5C[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_80184D7C[];
    return D_80184D7C[a1 & 0x7F];
}


DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */


DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */


DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657a0 (src/shared) */


DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657d8 (src/shared) */


DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */


DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */


DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658dc (src/shared) */


DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658ec (src/shared) */


DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */


DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */


DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */


DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */


DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */


DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */


DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659a8 (src/shared) */


DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659b8 (src/shared) */


DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659cc (src/shared) */




s32 func_801659DC(u8 *a0) {

    extern void (*D_80184D9C[])(void);
    D_80184D9C[*(u8 *)((s32)a0 + 0x1A0)]();
}


void func_80165A18(void) {
}

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165a20 (src/shared) */


DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165a50 (src/shared) */


DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165a78 (src/shared) */




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_80184E18[])(void);
    D_80184E18[D_80078EC1 & 0x7F]();
}


void func_80165B08(void) {
}

void func_80165B10(void) {
}

void func_80165B18(void) {
}

void func_80165B20(void) {
}



void func_80165B28(void *a0) {

    extern void (*D_80184E94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_80184E94[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165b6c (src/shared) */


DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165bb4 (src/shared) */


DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165bfc (src/shared) */


DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165c58 (src/shared) */


DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165c78 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80165CA0);


void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_801A6458;
    func_8001534C(0, &D_801A6458, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165e90 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80165FA4);



void func_80166018(void *a0) {

    extern void (*D_80184EA0[])(void);
    D_80184EA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80166054);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801661CC);

DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */


DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629c (src/shared) */


DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662f4 (src/shared) */


DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634c (src/shared) */


DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663a4 (src/shared) */




void func_801663FC(void *a0) {

    extern void (*D_80184EA8[])(void);
    D_80184EA8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801665B4);



void func_80166618(void *a0) {

    extern void (*D_80184F70[])(void);
    D_80184F70[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_80184F80[])(void);
    D_80184F80[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80166690);

extern void func_801484B0(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_801A6D20).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
s32 func_80166994(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    extern u8 D_801A6D20[];
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_801A6D20)[param_3];
    s32 uVar6 = *(s32 *)(param_1 + 0x34);
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->count = 0;
        p->idx = 0;
        p->timer = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
        break;
    case 2: {
        u8 bVar3 = p->timer - 0x10;
        p->timer = bVar3;
        if (bVar3 < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 bVar1 = p->count;
            if (bVar1 >= 2 && (bVar3 >> 4) < bVar1) {
                p->count = bVar1 - 1;
            }
        }
        return 0;
    }
    }

    if (param_3 < 2) {
        func_801484B0((s32)v10, (s32)v18);
    } else {
        func_80148534((s32)v10, (s32)v18);
    }
    func_80165FA4(uVar6, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(uVar6, (s32)v10, (s32)v10);
    RotTransSV(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_4;
        v20[1] = v28[1] + v20[1] / param_4;
        v20[2] = v28[2] + v20[2] / param_4;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80166F58);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016706C);


// @class: schedule
// @stuck: 16/279 masked. 3 runs, ONE residual class: gcc's list-scheduler puts `la $s2` (p=DATA) + `addu $s4,$zero,$zero` (i=0) BEFORE the callee-arg address setup (addiu $a1,$sp,0x10 / addu $a2,$a1,$zero); the target emits them AFTER. Inert to ~40 statement-order permutations + pin/barrier combos (sched priority dominates the LUID tie-break, sched.c rank_for_schedule). Runs: 19-24 (blk1), 111-114 (region-B cx-load rotation), 177-182 (blk3). Permuter fuel.




extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);


s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8  D_80184EC4[];
    extern u8  D_80184EB0[];
    extern u8  D_80184ED8[];
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_80126CE0;
    Fr_801670E4 f;
    register u8 *p   __asm__("$18");   /* $s2 */
    register s32 ent __asm__("$19");   /* $s3 */
    s16 i;
    s32 d;
    s32 node;
    u16 c;
    u8 cv;
    u8 cv2;
    register s32 gA __asm__("$2");
    register s32 cxv __asm__("$4");
    register s32 czv __asm__("$5");
    u8 *vc;
    u8 *ap;
    u8 *mp;
    u8 *va;
    u8 *vb;

    ent = arg0;
    node = *(s32 *)(ent + 0x34);
    f.v[1].z = 0;
    f.v[1].y = 0;
    f.v[1].x = 0;
    f.v[3].z = 0;
    f.v[2].z = 0;
    f.v[0].z = 0;
    f.col[1].b = 0x70;
    cv = *(u8 *)(ent + 0x12);
    f.cx = arg1;
    __asm__ __volatile__("");
    va = (u8 *)&f.cx;
    __asm__ __volatile__("" : "=r"(va) : "0"(va));
    f.cy = arg2;
    vb = va;
    __asm__ __volatile__("" : "=r"(vb) : "0"(vb));
    p = D_80184EC4;
    i = 0;
    f.col[0].b = 0;
    f.col[0].g = 0;
    f.col[0].r = 0;
    f.col[2].b = 0;
    f.col[2].g = 0;
    f.col[2].r = 0;
    f.col[3].b = 0;
    f.col[3].g = 0;
    f.col[3].r = 0;
    f.code = 0x50000000;
    f.cz = arg3;
    f.col[1].r = cv;
    f.col[1].g = cv;
    ((void (*)(s32, void *, void *))func_80149350)(node, va, vb);

    c = f.cx;
    *(s16 *)(ent + 0x06) = c;
    *(s32 *)(ent + 0x4C) = (s16)c;
    c = f.cy;
    *(s16 *)(ent + 0x0A) = c;
    *(s32 *)(ent + 0x50) = (s16)c;
    c = f.cz;
    *(s16 *)(ent + 0x0E) = c;
    *(s32 *)(ent + 0x54) = (s16)c;
    func_800D20C0(&f.cx, f.a8, 7);
    func_80017E68(&f.cx, f.m1);
    func_800D23D0(f.a8);
    RotMatrixYXZ(f.a8, f.m1);

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].y = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].y = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].y = (s8)*p--;
        func_80017758(f.v, f.m1);
    } while ((i = i + 1) < 4);

    p = D_80184EB0;
    gA = 0xA0;
    cxv = (s16)f.cx;
    f.col[1].g = gA;
    gA = D_801269A4;
    czv = (s16)f.cz;
    f.col[1].b = 0x10;
    f.col[1].r = 0x10;
    f.pos[0] = gA - cxv;
    i = 0;
    f.v[3].y = 0;
    f.v[2].y = 0;
    f.v[0].y = 0;
    f.pos[1] = D_801269A8 - (s16)f.cy;
    f.pos[2] = D_801269AC - czv;

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].z = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].z = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].z = (s8)*p--;
        func_80017758(f.v, (void *)(ent + 0x38));
    } while ((i = i + 1) < 4);

    if (*(s32 *)(ent + 0x30) > 0) {
        vc = (u8 *)&f.cx;
        __asm__ __volatile__("" : "=r"(vc) : "0"(vc));
        mp = f.m1;
        ap = mp;
        __asm__ __volatile__("" : "=r"(ap) : "0"(ap));
        p = D_80184ED8;
        i = 0;
        d = (s16)f.a8[0] >> 6;
        f.cx += d;
        f.cy += d;
        f.cz += d;
        func_80017E68(vc, ap);
        f.cx = f.cy = f.cz = ((u32)*(s32 *)(ent + 0x30) >> 1) + D_80126CE0 * 0x20;
        func_80017DC4(&f.cx, f.m2);
        func_80048EAC(f.m2, mp);
        f.v[3].z = 0;
        f.v[2].z = 0;
        f.v[0].z = 0;
        cv2 = *(u8 *)(ent + 0x12);
        f.col[1].b = 0x20;
        f.col[1].r = 0x20;
        f.col[3].b = 0;
        f.col[3].r = 0;
        f.col[2].b = 0;
        f.col[2].r = 0;
        f.col[0].b = 0;
        f.col[0].r = 0;
        f.col[3].g = 0;
        f.col[2].g = 0;
        f.col[0].g = 0;
        f.col[1].g = cv2 + 0x60;
        do {
            f.v[0].x = (s8)*p++;
            f.v[0].y = (s8)*p++;
            f.v[2].x = (s8)*p++;
            f.v[2].y = (s8)*p++;
            f.v[3].x = (s8)*p++;
            f.v[3].y = (s8)*p--;
            func_80017758(f.v, f.m1);
        } while ((i = i + 1) < 8);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80167540);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80167714);



void func_801678B4(void *a0) {

    extern void (*D_80184F90[])(void);
    D_80184F90[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801678F0);



void func_80167A9C(void *a0) {

    extern void (*D_80184F9C[])(void);
    D_80184F9C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80167AE0);

extern s32 func_80017758(void *a0, void *a1);
extern int func_80029178(int);


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {

    extern u16  D_800B99DA;
    extern u8   D_80184EFC[];
    extern u8   D_80184F10[];
    u8 buf[0x54];
    u8 *p;
    s16 i;

    func_80168070(arg0, ((s16 *)arg1), ((s16 *)arg2), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];
    if (((u8 (*)(s32))func_80029178)(0x81) != 0) {
        buf[0x45] = buf[0x45] << 2;
        buf[0x46] = buf[0x46] >> 1;
    }

    p = D_80184EFC;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x22) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x32) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3A) = (s8)*p--;
        func_80017758(buf + 0x20, buf);
    }

    p = D_80184F10;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x24) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x34) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3C) = (s8)*p--;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


extern void func_80149350(s32 arg0);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_80149350)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ApplyMatrixSV((void *)(*(s32 *)(param_1 + 0x20) + 0x34), dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}



extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801681FC(s32 param_1) {

    extern u8 D_80184F54[];
    extern u8 D_80184F24[];
    extern u8 D_80184F25[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80184F54[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80184F24[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_80184F25[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016829C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168328);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801683D8);


extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_80184F60[];
    extern u8 D_80184F38[];
    extern u8 D_80184F39[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80184F60[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80184F38[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80184F39[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801684B4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168540);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801685EC);

DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */


DEFINE_func_80168664()  /* dedup: shared engine-core @0x80168664 (src/shared) */




void func_80168744(void *a0) {

    extern void (*D_80184FB4[])(void);
    D_80184FB4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801687CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168828);



void func_801689D8(void *a0) {

    extern void (*D_80184FBC[])(void);
    D_80184FBC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168a14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168A88);



void func_80168AA8(void *a0) {

    extern void (*D_80184FC4[])(void);
    D_80184FC4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168ae4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168B70);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168BDC);



void func_80168D58(void *a0) {

    extern void (*D_80184FCC[])(void);
    D_80184FCC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168D94);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80168EC4);

DEFINE_func_80168F40()  /* dedup: shared engine-core @0x80168f40 (src/shared) */




void func_8016901C(void *a0) {

    extern void (*D_80184FD4[])(void);
    D_80184FD4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
void func_80169058(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX */
    s16 v40[16];  /* sp+0x40 MATRIX */
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = ((u32)(v0 & 0x7F00)) >> 5;
        __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
        v0 = v0 + 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE40;
        v0 = (((u32)(v0 & 0x7F00)) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" : : "r"(v1), "r"(v0));
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ApplyMatrixSV(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 c = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = c + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801691B8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169228);



void func_801693CC(void *a0) {

    extern void (*D_80184FDC[])(void);
    D_80184FDC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169408);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016951C);

DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */


DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696d8 (src/shared) */




void func_80169830(void *a0) {

    extern void (*D_80184FE4[])(void);
    D_80184FE4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
void func_8016986C(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX */
    s16 v40[16];  /* sp+0x40 MATRIX */
    s32 v1;
    s32 t;
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    v1 = rand();
    v10[0] = (v1 & 0x1FC) + 0x180;
    if (*(s32 *)(s1 + 0x2C) & 0x2) {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0x200;
    } else {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0xC00;
    }
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    if ((*(s32 *)(s1 + 0x2C) & 0x1) == 0) {
        *(s32 *)(s1 + 0x2C) = 0xE00;
    } else {
        *(s32 *)(s1 + 0x2C) = 0xA00;
    }
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ApplyMatrixSV(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 tmp = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = tmp + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801699D0);

DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169a4c (src/shared) */




void func_80169B80(void *a0) {

    extern void (*D_80185098[])(void);
    D_80185098[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169BBC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169E44);



void func_80169F00(void *a0) {

    extern void (*D_801850A0[])(void);
    D_801850A0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169F3C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80169FE0);



void func_8016A020(void *a0) {

    extern void (*D_801850D8[])(void);
    D_801850D8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016a05c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016A08C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016A1CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016A290);



void func_8016A700(void *a0) {

    extern void (*D_801850E4[])(void);
    D_801850E4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016A73C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016A890);

DEFINE_func_8016A8FC()  /* dedup: shared engine-core @0x8016a8fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016AA50);



void func_8016AB30(void *a0) {

    extern void (*D_8018512C[])(void);
    D_8018512C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016B114);



extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80016ED4(void *a0);


void func_8016B234(s32 param_1) {

    extern u8 D_800AF648;
    extern u8 D_80185124;
    short input[3];
    Prim_B234 prim;
    struct { s16 xy[2]; s32 sp1c; s32 flag; } out;
    void *dp;
    u32 uVar1;
    s16 iVar2;
    s32 X, Y0, Y1, base, ni;
    register s32 sy __asm__("$16");
    register s16 xtmp __asm__("$4");
    register s32 sxy __asm__("$3");

    dp = &D_800AF648;
    func_8004914C(dp);
    func_800491AC(dp);
    input[0] = *(u16 *)(param_1 + 6);
    input[1] = *(u16 *)(param_1 + 0xA);
    input[2] = *(u16 *)(param_1 + 0xE);
    RotTransPers((s32)input, (s32)out.xy, &out.sp1c, &out.flag);
    if ((out.flag & 0xffffefff) == 0) {
        sxy = *(s32 *)out.xy;
        prim.a04 = 0x10;
        X = *(u16 *)(param_1 + 0x2a) + sxy;
        sy = (u16)out.xy[1];
        prim.ax = prim.cx = X;
        prim.bx = prim.dx = X + 8;
        Y0 = sy - *(u16 *)(param_1 + 0x26);
        prim.ay = prim.by = Y0;
        sxy = *(u16 *)(param_1 + 0x26);
        prim.v0 = prim.v1 = 0x1d0;
        prim.v2 = prim.v3 = 0x1d8;
        sxy = sy + sxy;
        prim.cy = prim.dy = sxy;
        __asm__ __volatile__("" : : "r"(sy));
        prim.r = prim.g = prim.b = *(u8 *)(param_1 + 0x24);
        prim.code = (&D_80185124)[*(s32 *)(param_1 + 0x2c)];
        if (*(s16 *)(param_1 + 0x26) < 5) {
            prim.tag = 0;
        } else {
            prim.tag = 0x50000000;
        }
        uVar1 = *(u16 *)(param_1 + 0x30);
        iVar2 = 0;
        if (0 < *(s16 *)(param_1 + 0x28) + 1) {
            do {
                base = ((uVar1 + 1) & 0xf) << 3;
                prim.u0 = prim.u2 = base + 0x620;
                prim.u1 = prim.u3 = base + 0x628;
                func_80016ED4(&prim);
                uVar1 = (s32)(uVar1 << 0x10) >> 0x14;
                iVar2 = iVar2 + 1;
                __asm__ __volatile__("");
                xtmp = prim.ax;
                prim.cx = prim.ax = xtmp - 8;
                prim.bx = prim.dx = xtmp;
            } while ((s16)iVar2 < *(s16 *)(param_1 + 0x28) + 1);
        }
    }
}


DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016b3f4 (src/shared) */


DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016b428 (src/shared) */


DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016b448 (src/shared) */




void func_8016B4BC(void *a0) {

    extern void (*D_801851A8[])(void);
    D_801851A8[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);

void func_8016B4F8(int param_1)
{

    extern int D_801A6FC0;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801A6FC0);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}




// @class: schedule
// @stuck: none — MATCH

extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);


void func_8016B5C0(s32 param_1) {

    extern s16 D_8018519C[];
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018519C;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016B6BC);


// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_801851E0[];
    extern unsigned short D_801851E8[];
    extern unsigned short D_801851F0[];
    extern unsigned char D_801A6FC8[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801A6FC8 + param_2 * 0x40);
    puVar3 = D_801851E0[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_801851E8[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_801851F0[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016B984);


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801A6FC0;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801A6FC0, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_801851F8[])(void);
    D_801851F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BBE0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BCC0);

extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801A70FC;
    extern M2C_UNK D_801A7100;
    extern u8 D_801A70FD;
    extern u8 D_801A70FE;
    extern u8 D_801A7101;
    extern u8 D_801A7102;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801A70FC);
    if (*p1 != 0) *p1 -= 4;
    if (D_801A70FD != 0) D_801A70FD -= 4;
    if (D_801A70FE != 0) D_801A70FE -= 4;
    p2 = &(*(u8 *)&D_801A7100);
    if (*p2 != 0) *p2 -= 4;
    if (D_801A7101 != 0) D_801A7101 -= 4;
    if (D_801A7102 != 0) D_801A7102 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BEA0);

DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BF50);


extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801A7088;
    func_8016BFD0(a0, a1, a2, a3, &D_801A7088);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016BFD0);



void func_8016C14C(void *a0) {

    extern void (*D_80185228[])(void);
    D_80185228[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016C188);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016C2C4);

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016C49C);

DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016c74c (src/shared) */


DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016c83c (src/shared) */



extern short func_8016CBC0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);


void func_8016C998(s32 param_1)
{

    extern s32 D_80126B9C;
    extern s16 D_80126CE0;
    u16 *psVar7;
    s32 r;
    short i;
    extern Slot_998 D_801A71D8[];

    psVar7 = *(u16 **)(param_1 + 0x34);
    if (*psVar7 != 1) {
        *(s16 *)(param_1 + 2) = 6;
    }
    func_8016CBC0();
    if (*(s16 *)(param_1 + 0x28) != *(s16 *)(*(s32 *)(param_1 + 0x30) + 0x36)) {
        return;
    }
    if ((D_80126B9C & 0x20) == 0) {
        return;
    }
    if ((*(s32 *)(param_1 + 0x1c) == 0) ||
        (*(s16 *)(param_1 + 0x12) < D_80126CE0)) {
        *(s16 *)(param_1 + 0x12) = D_80126CE0;
        i = 0;
        do {
            if (D_801A71D8[i].f0 == 0) {
                goto found;
            }
            i++;
        } while (i < 8);
    found:
        if (i >= 8) {
            return;
        }
        r = func_80146A6C(0x30, psVar7, 0, 0, 0, 0x8000, *(s32 *)(param_1 + 0x30));
        if (r == 0) {
            return;
        }
        D_801A71D8[i].f0 = 1;
        *(Blk32_998 *)(r + 0x38) = *(Blk32_998 *)(param_1 + 0x38);
        *(s16 *)(r + 0x2a) = i;
        *(s16 *)(r + 6) = *(s16 *)(param_1 + 6);
        *(s16 *)(r + 0xa) = *(s16 *)(param_1 + 0xa);
        *(s16 *)(r + 0xe) = *(s16 *)(param_1 + 0xe);
        *(s32 *)(param_1 + 0x1c) = 0x10;
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}




void func_8016CB84(void *a0) {

    extern void (*D_80185230[])(void);
    D_80185230[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_80017758(void *a0, void *a1);
short func_8016CBC0(void)
{

    extern Blk20 D_800AE620;

    extern Blk_8016CBC0 D_801A71D8[];
  Poly_8016CBC0 p0;
  Poly_8016CBC0 p1;
  Mtx8_8016CBC0 mtx;
  Blk_8016CBC0 *blk;
  Rec_8016CBC0 *sub;
  Rec_8016CBC0 *pv;
  unsigned int uVar9;
  unsigned int w9;
  unsigned int uc;
  unsigned int a2;
  int col;
  int iVar3;
  int w3;
  unsigned int w3b;
  short count;
  short i;
register unsigned int zr __asm__("$0");
  mtx = (*(Mtx8_8016CBC0 *)&D_800AE620);
  count = 0;
  p1.tag = 0x50000000;
  p0.tag = 0x50000000;
  p1.col[3].b = 0;
  p1.col[3].g = 0;
  p1.col[3].r = 0;
  p1.col[1].b = 0;
  p1.col[1].g = 0;
  p1.col[1].r = 0;
  p0.col[2].b = 0;
  p0.col[2].g = 0;
  p0.col[2].r = 0;
  p0.col[0].b = 0;
  p0.col[0].g = 0;
  p0.col[0].r = 0;
  for (i = 0; i < 8; i++)
  {
    blk = &D_801A71D8[i];
    if (blk->f0 != 0)
    {
      sub = blk->ent;
      uVar9 = blk->f1;
      iVar3 = blk->f2;
      col = blk->f3;
      count = count + 1;
      w3 = iVar3 - 1;
      iVar3 = w3 + zr;
      if (w3 != (-1))
      {
        do
        {
          pv = &sub[(short) uVar9];
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[0].x = a;
            b = pv->h[3];
            p1.v[1].x = b;
            p0.v[1].x = (p1.v[0].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[0].y = a;
            b = pv->h[4];
            uc = ((unsigned) (col & 0xFF)) >> 3;
            p1.v[1].y = b;
            p0.v[1].y = (p1.v[0].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[0].z = a;
            b = pv->h[5];
            p1.col[0].g = col;
            p0.col[1].g = col;
            p1.col[0].b = uc;
            p0.col[1].b = uc;
            p1.col[0].r = uc;
            p0.col[1].r = uc;
            p1.v[1].z = b;
            p0.v[1].z = (p1.v[0].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          if (((int) (w9 << 16)) < 0)
          {
            uVar9 = 0xF;
          }
          pv = &sub[(short) uVar9];
          col = col - 0xF;
          a2 = (unsigned) (col & 0xFF);
          a2 = a2 >> 3;
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[2].x = a;
            b = pv->h[3];
            p1.v[3].x = b;
            p0.v[3].x = (p1.v[2].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[2].y = a;
            b = pv->h[4];
            p1.v[3].y = b;
            p0.v[3].y = (p1.v[2].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[2].z = a;
            b = pv->h[5];
            p1.col[2].g = col;
            p0.col[3].g = col;
            p1.col[2].b = a2;
            p0.col[3].b = a2;
            p1.col[2].r = a2;
            p0.col[3].r = a2;
            p1.v[3].z = b;
            p0.v[3].z = (p1.v[2].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          func_80017758(&p0, &mtx);
          func_80017758(&p1, &mtx);
          uc = iVar3 - 1;
          w3b = uc;
          iVar3 = w3b + zr;
        }
        while (((short) w3b) != (-1));
      }
    }
  }

  return count;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016CF04);



void func_8016D19C(void *a0) {

    extern void (*D_8018524C[])(void);
    D_8018524C[*(u16 *)((s32)a0 + 0x2)]();
}







   /* 8 bytes */
                 /* 32 bytes */


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void*);
extern void func_80147324(int a);
extern int  rand(void);
extern void RotMatrixYXZ(void *a, void *b);
extern void ApplyMatrixSV(void *a, void *b, void *c);

void func_8016D1D8(int param_1) {

    extern u8 D_801A7158[];
    extern u8 D_801A7198[];
    int iVar5;
    int iVar2;
    u16 uVar1;
    unsigned int uVar3;
    short sVar4;
    SVEC_L1 sv;
    MTX_L1 mtx;

    iVar5 = *(int *)(param_1 + 0x34);
    if (*(int *)(param_1 + 0x2c) == 0) {
        D_801A7158[1] = 0xE0;
        D_801A7158[2] = 0xE0;
        D_801A7158[0] = 0xE0;
        D_801A7158[6] = 0;
        D_801A7158[5] = 0;
        D_801A7158[4] = 0;
        iVar5 = ((int (*)(void))func_801465C0)();
        if (iVar5 != 0) {
            int pp;
            *(int *)(param_1 + 0x20) = iVar5;
            ((void (*)(void *, int))func_800233CC)(D_801A7158, 0x28);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar5, D_801A7158);
            *(short *)(iVar5 + 0x1a) = 0x1400;
            *(u32 *)(iVar5 + 4) |= 0x50000000;
            pp = *(int *)(param_1 + 0x30);
            *(u16 *)(param_1 + 0x28) = *(u16 *)(pp + 0x36);
            *(u16 *)(param_1 + 0x12) = *(u16 *)(pp + 6);
            *(short *)(param_1 + 0x16) = *(u16 *)(pp + 0xa) - 0x28;
            uVar1 = *(u16 *)(pp + 0xe);
            *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
            *(u16 *)(param_1 + 0x1a) = uVar1;
        }
        *(int *)(param_1 + 0x1c) = 8;
        func_80147324(0x647);
    } else {
        D_801A7198[1] = 0xE0;
        D_801A7198[2] = 0x20;
        D_801A7198[0] = 0x20;
        D_801A7198[5] = 0;
        D_801A7198[6] = 0;
        D_801A7198[4] = 0;
        iVar2 = ((int (*)(void))func_801465C0)();
        if (iVar2 != 0) {
            *(int *)(param_1 + 0x20) = iVar2;
            ((void (*)(void *, int))func_800233CC)(D_801A7198, 0x18);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar2, D_801A7198);
            *(u32 *)(iVar2 + 4) |= 0x50000000;
            *(u16 *)(param_1 + 6) = *(u16 *)(iVar5 + 6);
            *(u16 *)(param_1 + 0xa) = *(u16 *)(iVar5 + 0xa);
            *(u16 *)(param_1 + 0xe) = *(u16 *)(iVar5 + 0xe);
            uVar3 = rand();
            sv.vx = ((uVar3 & 0x7F) * 8) - 0x80;
            sv.vy = (uVar3 & 0x7F00) >> 3;
            sv.vz = 0;
            RotMatrixYXZ(&sv, &mtx);
            sv.vy = 0;
            sv.vx = 0;
            sv.vz = 0x240;
            ApplyMatrixSV(&mtx, &sv, &sv);
            *(int *)(param_1 + 0x10) = (int)sv.vx << 0xc;
            *(int *)(param_1 + 0x14) = (int)sv.vy << 0xc;
            sVar4 = (uVar3 & 0x3F0) + 0x200;
            *(int *)(param_1 + 0x18) = (int)sv.vz << 0xc;
            *(short *)(iVar2 + 0x1a) = sVar4;
            *(short *)(iVar2 + 0x18) = sVar4;
            *(int *)(param_1 + 0x1c) = 0x10;
            *(short *)(param_1 + 2) = 2;
        }
    }
}




void func_8016D428(void *a0) {

    extern void (*D_80185254[])(void);
    D_80185254[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016D5EC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016D64C);


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void *);

void func_8016D688(int param_1)
{

    extern unsigned char D_801A7158[];
    int iVar2;
    int iVar3;

    D_801A7158[1] = 0xe0;
    D_801A7158[2] = 0xe0;
    D_801A7158[0] = 0xe0;
    D_801A7158[6] = 0;
    D_801A7158[5] = 0;
    D_801A7158[4] = 0;
    iVar2 = ((int (*)(void))func_801465C0)();
    if (iVar2 != 0) {
        *(int *)(param_1 + 0x20) = iVar2;
        ((void (*)(void *, int))func_800233CC)(D_801A7158, 0x28);
        func_8001CD9C(iVar2, D_801A7158);
        *(unsigned short *)(iVar2 + 0x1a) = 0x1400;
        *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x50000000;
        iVar3 = *(int *)(param_1 + 0x30);
        *(unsigned short *)(param_1 + 0x28) = *(unsigned short *)(iVar3 + 0x36);
        *(unsigned short *)(param_1 + 0x12) = *(unsigned short *)(iVar3 + 6);
        *(short *)(param_1 + 0x16) = *(unsigned short *)(iVar3 + 0xa) - 0x28;
        *(unsigned short *)(param_1 + 0x1a) = *(unsigned short *)(iVar3 + 0xe);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016D778);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016D848);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_801852BC[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_801852BC[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016DB34);

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016DC20);



void func_8016DEA4(void *a0) {

    extern void (*D_801852F0[])(void);
    D_801852F0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016DEE0);



void func_8016DF20(void *a0) {

    extern void (*D_801852F8[])(void);
    D_801852F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016DF5C);

DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E2E8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E358);

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_8018534C[])(void);
    D_8018534C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E5F4);

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E7C8);

DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E95C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016E9EC);


// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_80185380[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_80185380[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {

    extern u8 D_80185370[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_80185370[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_80185380[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_80185380[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_80185380[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016EC0C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016ED6C);

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


DEFINE_func_8016EFC8()  /* dedup: shared engine-core @0x8016EFC8 (src/shared) */

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8016F0E4);

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */



// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_8018539C;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018539C;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016f250 (src/shared) */


DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016f264 (src/shared) */


DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016f288 (src/shared) */


DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016f2a8 (src/shared) */


DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016f2c8 (src/shared) */


DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016f2ec (src/shared) */


DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016f30c (src/shared) */


DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016f330 (src/shared) */


DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016f350 (src/shared) */


DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016f374 (src/shared) */


DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016f388 (src/shared) */


DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016f398 (src/shared) */


DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016f410 (src/shared) */


DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016f44c (src/shared) */


DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016f470 (src/shared) */


DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016f494 (src/shared) */


DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016f4c4 (src/shared) */


void func_8016F4F4(void) {
}

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016f4fc (src/shared) */


DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016f540 (src/shared) */


DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016f578 (src/shared) */


DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016f5b0 (src/shared) */


DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016f5e0 (src/shared) */


DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016f610 (src/shared) */


DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016f648 (src/shared) */


DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016f680 (src/shared) */


DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016f6b0 (src/shared) */




void func_8016F6E0(void *a0) {

    extern void (*D_80185414[])(void);
    D_80185414[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_8018541C[])(void);
    D_8018541C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_80185424[])(void);
    D_80185424[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_8018542C[])(void);
    D_8018542C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_80185434[])(void);
    D_80185434[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_8018543C[])(void);
    D_8018543C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_80185448[])(void);
    D_80185448[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_80185454[])(void);
    D_80185454[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_80185460[])(void);
    D_80185460[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_80185470[])(void);
    D_80185470[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_80185480[])(void);
    D_80185480[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_80185488[])(void);
    D_80185488[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_80185490[])(void);
    D_80185490[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_80185498[])(void);
    D_80185498[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_801854A0[])(void);
    D_801854A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_801854A8[])(void);
    D_801854A8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_801854B0[])(void);
    D_801854B0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_801854B8[])(void);
    D_801854B8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_801854C0[])(void);
    D_801854C0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_801854C8[])(void);
    D_801854C8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_801854D0[])(void);
    D_801854D0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_801854D8[])(void);
    D_801854D8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_801854E0[])(void);
    D_801854E0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_801854E8[])(void);
    D_801854E8[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80170CF0);



void func_80170D68(void *a0) {

    extern void (*D_801854F0[])(void);
    D_801854F0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_801854F8[])(void);
    D_801854F8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_80185500[])(void);
    D_80185500[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_80185508[])(void);
    D_80185508[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_80185510[])(void);
    D_80185510[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_80185518[])(void);
    D_80185518[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_80185520[])(void);
    D_80185520[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_80185528[])(void);
    D_80185528[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8017129C);

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_80185530[])(void);
    D_80185530[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */


DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */


DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196c (src/shared) */


DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197c (src/shared) */


DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */


DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719a4 (src/shared) */


DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171a04 (src/shared) */


DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171a10 (src/shared) */


DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171a1c (src/shared) */


DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171a34 (src/shared) */


DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171a44 (src/shared) */


DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171a58 (src/shared) */


DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171a6c (src/shared) */


DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171a80 (src/shared) */


DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171a88 (src/shared) */


DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171ab0 (src/shared) */


DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171b10 (src/shared) */


DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171b44 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171c64 (src/shared) */


DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171cc4 (src/shared) */


DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171d1c (src/shared) */


DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171d78 (src/shared) */


DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171e08 (src/shared) */


DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171ec8 (src/shared) */



DEFINE_func_80171FFC()  /* dedup: shared engine-core @0x80171FFC (src/shared) */


DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209c (src/shared) */


DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */


DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722cc (src/shared) */


DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */


DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */


DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */


DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723c4 (src/shared) */


DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */


DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248c (src/shared) */


DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724ec (src/shared) */


DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250c (src/shared) */


DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */


DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */


DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */


DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725a4 (src/shared) */


DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725b8 (src/shared) */


DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725cc (src/shared) */


DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725e0 (src/shared) */


DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725f4 (src/shared) */


DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */


DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261c (src/shared) */


DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */


DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */


DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */


DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */


DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */


DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267c (src/shared) */


DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */


DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */


DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726a0 (src/shared) */


DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726ac (src/shared) */


DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726b8 (src/shared) */


DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726c4 (src/shared) */


DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726d0 (src/shared) */


DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */


DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */


DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */


DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */




s32 func_801727D0(void *a0) {

    extern void (*D_80185540[])(void);
    D_80185540[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */




s32 func_801728E4(void *a0) {

    extern void (*D_8018554C[])(void);
    D_8018554C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */




s32 func_801729F0(void *a0) {

    extern void (*D_80185558[])(void);
    D_80185558[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */




s32 func_80172B44(void *a0) {

    extern void (*D_80185568[])(void);
    D_80185568[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

extern void func_80174684(void *);
extern s32 func_80172CA0(void *a0);
void func_80172C50(void *a0) {

    extern s16 D_80126B30;
    *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0;
    func_80174684((void *)func_80172CA0);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80172CA0);

DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */




s32 func_80172DAC(void *a0) {

    extern void (*D_80185580[])(void);
    D_80185580[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172de8 (src/shared) */


DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172e20 (src/shared) */


void func_80172E8C(void) {
}

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172e94 (src/shared) */


DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ed4 (src/shared) */


DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172efc (src/shared) */


DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172f24 (src/shared) */


DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172f4c (src/shared) */


DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172f9c (src/shared) */


DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172fec (src/shared) */


DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303c (src/shared) */




s32 func_80173078(void *a0) {

    extern void (*D_8018558C[])(void);
    D_8018558C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */




s32 func_8017319C(void *a0) {

    extern void (*D_80185598[])(void);
    D_80185598[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_80185538;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_80185538);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}


void func_80173294(void) {
}

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329c (src/shared) */


DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732c4 (src/shared) */


DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732f4 (src/shared) */


DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331c (src/shared) */


DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334c (src/shared) */


DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */


DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733a4 (src/shared) */


DEFINE_func_801733CC()  /* dedup: shared engine-core @0x801733cc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_801855A4[])(void);
    D_801855A4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */




s32 func_801736FC(void *a0) {

    extern void (*D_801855B8[])(void);
    D_801855B8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */




s32 func_801737E8(void *a0) {

    extern void (*D_801855C4[])(void);
    D_801855C4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */




s32 func_8017390C(void *a0) {

    extern void (*D_801855D0[])(void);
    D_801855D0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */



extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern s32 func_80173B4C(void*);

void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5)
{

    extern s32 D_80126B58;
    extern s32 D_80127508;
    extern s16 D_80126B30;
    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3A;
    extern s16 D_80126B3C;
    extern s16 D_8011F9C8;
    extern s16 D_80126938;
    extern s32 D_8012750C;
    s32 *s1 = &D_80126B58;
    s32 v0;

    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }

    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80173B4C);

DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173b88 (src/shared) */


DEFINE_func_80173BC0()  /* dedup: shared engine-core @0x80173bc0 (src/shared) */


DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173c64 (src/shared) */


DEFINE_func_80173CB4()  /* dedup: shared engine-core @0x80173cb4 (src/shared) */


DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173e1c (src/shared) */


DEFINE_func_80173EF8()  /* dedup: shared engine-core @0x80173ef8 (src/shared) */


DEFINE_func_80174158()  /* dedup: shared engine-core @0x80174158 (src/shared) */


DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */


DEFINE_func_801741A8()  /* dedup: shared engine-core @0x801741a8 (src/shared) */


DEFINE_func_801741EC()  /* dedup: shared engine-core @0x801741ec (src/shared) */


void func_80174274(void) {
}

DEFINE_func_8017427C()  /* dedup: shared engine-core @0x8017427c (src/shared) */




s32 func_801742A4(void *a0) {

    extern void (*D_80185600[])(void);
    D_80185600[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */




s32 func_80174384(void *a0) {

    extern void (*D_8018560C[])(void);
    D_8018560C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */




s32 func_80174474(void *a0) {

    extern void (*D_80185618[])(void);
    D_80185618[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801744B0()  /* dedup: shared engine-core @0x801744b0 (src/shared) */


DEFINE_func_801744E0()  /* dedup: shared engine-core @0x801744e0 (src/shared) */


void func_80174524(void) {
}

DEFINE_func_8017452C()  /* dedup: shared engine-core @0x8017452c (src/shared) */


DEFINE_func_80174554()  /* dedup: shared engine-core @0x80174554 (src/shared) */


DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */


DEFINE_func_801745AC()  /* dedup: shared engine-core @0x801745ac (src/shared) */


DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745dc (src/shared) */


DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */


DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */


DEFINE_func_80174650()  /* dedup: shared engine-core @0x80174650 (src/shared) */


DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */


DEFINE_func_80174684()  /* dedup: shared engine-core @0x80174684 (src/shared) */


DEFINE_func_801746A4()  /* dedup: shared engine-core @0x801746a4 (src/shared) */


DEFINE_func_801746DC()  /* dedup: shared engine-core @0x801746dc (src/shared) */


DEFINE_func_80174714()  /* dedup: shared engine-core @0x80174714 (src/shared) */


DEFINE_func_80174754()  /* dedup: shared engine-core @0x80174754 (src/shared) */


DEFINE_func_80174764()  /* dedup: shared engine-core @0x80174764 (src/shared) */


DEFINE_func_80174774()  /* dedup: shared engine-core @0x80174774 (src/shared) */


DEFINE_func_80174784()  /* dedup: shared engine-core @0x80174784 (src/shared) */


DEFINE_func_801747AC()  /* dedup: shared engine-core @0x801747ac (src/shared) */




s32 func_801747CC(void *a0) {

    extern void (*D_80185624[])(void);
    D_80185624[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */




s32 func_80174888(void *a0) {

    extern void (*D_8018562C[])(void);
    D_8018562C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */




s32 func_8017496C(void *a0) {

    extern void (*D_80185634[])(void);
    D_80185634[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801749C8);

DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_80185638[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_80185638[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_80185638[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80174CB0);

DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */




s32 func_80174F28(void *a0) {

    extern void (*D_80185640[])(void);
    D_80185640[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_80185648[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_80185648[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}


DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751d8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{

    extern u8 D_80078EC0;
    extern void (*D_80185650[])(s32);
    s32 i = D_80078EC0 - 1;

    D_80185650[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_80185668[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_80185668 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


DEFINE_func_80175308()  /* dedup: shared engine-core @0x80175308 (src/shared) */

DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801754A8);


extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {

    extern void (*D_801857B8[])();
    D_801857B8[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */


DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */


DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(s32 *param) {

    extern void (*D_801857C4[])();
    D_801857C4[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80175820);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801758FC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801759D8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80175AB8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80175DA8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80176144);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80176218);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


DEFINE_func_801775E0()  /* dedup: shared engine-core @0x801775E0 (src/shared) */


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801777BC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801778A8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80177940);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80177AD4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80177B5C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80177DA8);

DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80178004);

DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_801A66A0;
    func_8001534C(2, &D_801A66A0, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}


DEFINE_func_8017849C()  /* dedup: shared engine-core @0x8017849c (src/shared) */


DEFINE_func_80178608()  /* dedup: shared engine-core @0x80178608 (src/shared) */


DEFINE_func_8017869C()  /* dedup: shared engine-core @0x8017869c (src/shared) */


DEFINE_func_80178744()  /* dedup: shared engine-core @0x80178744 (src/shared) */


DEFINE_func_801787D4()  /* dedup: shared engine-core @0x801787d4 (src/shared) */



// @class: regalloc-order
// @stuck: sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);


void func_80178840(int param_1) {

    extern int D_80185804;
    extern int D_80185810[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_80185804);
        }
        ((void (*)(int, int))func_80131E00)(p, D_80185810[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern int func_801789AC(void);

int func_80178970(void)
{

    extern s16 D_801A94D0;
    register int r __asm__("$2");
    int v;

    v = func_801789AC();
    r = 0;
    if (v != 0)
        r = D_801A94D0 == 0;
    return r;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_801789AC);

extern void func_8017435C(void);
extern void func_801746A4(void);

// @class: struct
// @stuck: none — MATCH (pointer var forces &(*(int *)&D_801858FC) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_801858FC;

    int *p = &(*(int *)&D_801858FC);
    *p = ((int)param_2);
    func_80178BF8();
    func_801746A4();
    func_8017435C();
    ((void (*)(int, void *))func_80178CBC)(((int)param_1), (char *)p - 0xC);
}




// @class: regalloc-order
// @stuck: none — MATCH (pending verify)

s32 func_80178B70(s32 param_1, s32 param_2)
{
    extern void func_80178BF8();
    extern void func_80178CBC();
    extern int D_801858FC;

    int *p = &D_801858FC;
    *p = ((int)param_2);
    func_80178BF8();
    func_80178CBC(((int)param_1), p - 3);
}


DEFINE_func_80178BB8()  /* dedup: shared engine-core @0x80178bb8 (src/shared) */


extern void func_80016714(void *a0, s32 a1);

// @class: other
// @stuck: none — MATCH (49 ins). Key: init loop pointers via &D_SYMBOL (not (T*)0x801da788 raw int, which emits lui+ori instead of lui%hi+addiu%lo).



void func_80178BF8(s32 _unused0, s32 _unused1)
{
    extern void func_8017B1D8(void);
    extern short D_801A9544;
    extern int D_801A7C58;
    extern short D_801A7C68;
    extern short D_801A7C64;
    extern short D_801A7C60;
    extern short D_801A7C5C;
    extern int D_801A93EC;
    extern int D_801A7C70;
    extern s16 D_801A7C50;
    extern short D_801A7C48;
    extern short D_801A7C4C;
    extern int D_801A94A0;
    extern unsigned int D_801A7CC0;
    extern unsigned short D_801A7C46;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_801A7CC0;
    D_801A9544 = 0;
    D_801A7C58 = 0;
    D_801A7C68 = 0;
    D_801A7C64 = 0;
    D_801A7C60 = 0;
    D_801A7C5C = 0;
    D_801A93EC = 1;
    D_801A7C70 = 0;
    (*(short *)&D_801A7C50) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_801A7C46;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_801A7C48 = 0;
    D_801A7C4C = 0;
    ((void (*)(int *, int))func_80016714)(&D_801A94A0, 0x14);
    func_8017B1D8();
}


extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);

void func_80178CBC(s32 arg0, s32 arg1) {

    extern s32 D_801A7840;
    extern short D_801A9544;
    D_801A7840 = arg1;
    do {
        func_80178D40(arg0, D_801A7840);
    } while (D_801A9544 == 3);
}



extern void func_80174714(void);

void func_80178D18(void) {

    extern short D_801A9544;
    D_801A9544 = 0;
    func_80174714();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179b28 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179d30 (src/shared) */


DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179d78 (src/shared) */


DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179dcc (src/shared) */


DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179df8 (src/shared) */


DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179e1c (src/shared) */


DEFINE_func_80179E48()  /* dedup: shared engine-core @0x80179e48 (src/shared) */


DEFINE_func_80179E74()  /* dedup: shared engine-core @0x80179e74 (src/shared) */


DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179ea0 (src/shared) */


DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179ee8 (src/shared) */


DEFINE_func_80179F14()  /* dedup: shared engine-core @0x80179f14 (src/shared) */


DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179f44 (src/shared) */


DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179f6c (src/shared) */


DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179f98 (src/shared) */


DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179fec (src/shared) */


DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017a040 (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A094(s32 arg0) {

    extern s32 D_801A7C6C;
    s16 sp10;

    D_801A7C6C = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}



extern void func_80179B74(s16 *a0);

void func_8017A0C4(s32 arg0) {

    extern s32 D_801A7C6C;
    s16 sp10;

    D_801A7C6C = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}


DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017a0f4 (src/shared) */


DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017a11c (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {

    extern s32 D_801A7C94;
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801A7C94 = a0;
}


DEFINE_func_8017A180()  /* dedup: shared engine-core @0x8017a180 (src/shared) */


DEFINE_func_8017A1A8()  /* dedup: shared engine-core @0x8017a1a8 (src/shared) */


DEFINE_func_8017A1D0()  /* dedup: shared engine-core @0x8017a1d0 (src/shared) */


DEFINE_func_8017A1F8()  /* dedup: shared engine-core @0x8017a1f8 (src/shared) */


DEFINE_func_8017A220()  /* dedup: shared engine-core @0x8017a220 (src/shared) */


DEFINE_func_8017A248()  /* dedup: shared engine-core @0x8017a248 (src/shared) */


DEFINE_func_8017A270()  /* dedup: shared engine-core @0x8017a270 (src/shared) */


DEFINE_func_8017A298()  /* dedup: shared engine-core @0x8017a298 (src/shared) */


DEFINE_func_8017A2C0()  /* dedup: shared engine-core @0x8017a2c0 (src/shared) */


DEFINE_func_8017A2E8()  /* dedup: shared engine-core @0x8017a2e8 (src/shared) */


DEFINE_func_8017A310()  /* dedup: shared engine-core @0x8017a310 (src/shared) */


DEFINE_func_8017A338()  /* dedup: shared engine-core @0x8017a338 (src/shared) */


DEFINE_func_8017A360()  /* dedup: shared engine-core @0x8017a360 (src/shared) */


DEFINE_func_8017A388()  /* dedup: shared engine-core @0x8017a388 (src/shared) */




s32 func_8017A3B0(void) {

    extern s16 D_801A7C50;
    switch (D_801A7C50) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}



// @class: regalloc-order
// @stuck: none — MATCH


extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{

    extern short D_801A7C8C;
    extern short D_801A7C88;
    switch (D_801A7C8C) {
    case 0:
        func_800D0CA0(1);
        D_801A7C8C = D_801A7C8C + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_801A7C88;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801A7C8C = D_801A7C8C + 1;
        if (D_801A7C8C < 0x1E) {
            return 0;
        }
        D_801A7C8C = 100;
        return 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_jr_8015C32C", func_8017A4AC);

DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017ad0c (src/shared) */


DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ade8 (src/shared) */


DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017ae08 (src/shared) */
