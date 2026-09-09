#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* 8 bytes */
                 /* 32 bytes */
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
extern void func_801463A0();
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
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
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
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern void func_8014CD80(s32 a0, void *a1, void *a2);
extern s32 func_8014D2A0(s32 a0, void *a1, void *a2);
extern s32 func_8014D12C(s32 a0, void *a1, void *a2);
extern void func_8014D0A4(s32 a0);
extern void func_8014D610(s32 a0, void *a1, void *a2);
extern s32 func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2);
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
extern s32 func_8014F468(void);
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
extern s32 func_801506A4();
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
extern s32 func_8014F3E8(s32 a0);
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
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
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
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
extern void func_8014D738(void);
extern s32 func_8015C128(s32 param_1);
extern s32 func_801496D4(void*);
extern s32 func_801619A4(s32*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_801498E0(s32*);
extern void func_80149954(s32 a0);
extern s32 func_80149A64(s32*);
extern void func_800CCCC0(s32 a0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_8014CC28(s32);
extern s32 func_8014F3E8(s32);
extern void func_80159BE4(s32 a0);
extern void func_8015C6E0(s32*);
extern void func_8015C32C(s32 arg0);
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
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void func_8014E6A0(void);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
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
extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);
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
extern void func_8015E5B0(u8 *self);
extern void func_8015E698(u16 *param_1);
extern void func_8015E714(s32 *a0);
extern void func_8015E95C(s32);
extern void func_8015E84C(s32 *a0);
extern void func_8015E8E8(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void func_8015E924(s32 a0);
extern void func_8015E95C(s32 a0);
extern s16 D_801152A0;
extern void func_80160818(s32 *a0);
extern void func_8015ED6C(s32 *a0);
extern void func_8015EE7C(s32);
extern void func_8015EDA0(s32 *a0);
extern s32 func_8015EE08(s32 a0);
extern void func_8015EDD4(s32 *arg0);
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
extern s32 func_80161208(void);
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void func_8015F360(void);
extern s32 func_801725B8(u8 *a0);
extern void func_8015F380(void* arg0);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80146DB8(s32*, s32*);
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
extern void func_8015F948(s32 *param_1);
extern void func_8015FA24(s32 arg0);
extern void func_8015FBE0(s32 *a0);
extern void func_8015FA44(s32 *a0);
extern void func_8015FAAC(s32 *a0);
extern void func_8015FA78(s32 *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_8015FAE8(void *arg0);
extern void func_8015FCC8(void *param_1);
extern void func_8015FD74(int param_1);
extern u8 func_80165700(s32 a0, s32 a1);
extern void func_8015FDCC(s32 a0);
extern void func_8015FE70(u16 *param_1);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);
extern void func_8015FF20(void *param_1);
extern u16 D_801270C0;
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
extern void func_800D0F4C(s32 a0);
extern u8 D_80110EC0;
extern void func_80160F70(s32 a0);
extern void func_80160FE0(s32 *a0);
extern void func_80161034(void *a0);
extern void func_80161094(s32 a0);
extern void func_801610FC(void);
extern void func_801483E8(void);
extern s32 func_80161A60(s32 a0);
extern void func_8016130C(void *a0, s32 a1);
extern void func_80161374(void *a0, s32 a1);
extern void func_80161278(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);
extern s32 func_8016197C(s32 a0, s32 a1);
extern s32 func_80161488(void *a0);
extern void func_80161888(void *a0, s32 a1);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern int func_801497A8(void);
extern int func_80161BE0(void *param_1);
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern void func_800D1734(void *);
extern void func_80161D88(void);
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
extern void func_80162B1C(void);
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
extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163234(s32 a0);
extern s32 D_80115100;
extern s32 func_801632E0(void);
extern s32 D_80115200;
extern s32 func_801632F0(void);
extern u16 D_80126B18[];
extern void func_80163328(void);
extern s32 func_801633A8(void);
extern s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);
extern void func_8016345C(s32 a0, u16 a1, s32 a2, u16 a3, s32 a4);
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418(void);
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
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
extern void func_80016ED4(void *a0);
extern s32 func_80017DC4(void *a0, void *a1);
extern u8 D_80126CF8;
extern void func_8016533C(void);
extern void func_801653F4(s32 a0);
extern void func_80165580(s32 a0);
extern void func_80165374(s32 a0);
extern void func_80165580(s32 _arg0);
extern void func_801653B8(s32 *a0);
extern s32 func_80165624(s32 a0);
extern u8 D_80078EC5;
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 func_801656D0(s32 a0, s32 a1);
extern void func_800CAF6C(void);
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
extern void func_80165E90(void);
extern void func_80166018(void *a0);
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
extern void func_80166618(void *a0);
extern void func_80166654(void *a0);
extern s32 func_80166994();
extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801678B4(void *a0);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern int func_80029178(int);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801681FC(s32 param_1);
extern void func_80168430(s32 param_1);
extern void func_80168640(s32 a0);
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80168664(void *arg0);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_80168D58(void *a0);
extern void func_80168F40(void *arg0);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_801696D8(s32 a0, s32 a1);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_80169B80(void *a0);
extern void func_80169F00(void *a0);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A700(void *a0);
extern s32 func_80016A5C();
extern s32 func_8016A8FC(s32 a0);
extern void func_8016AB30(void *a0);
extern void func_8016B234();
extern void func_800D22E4(s32 a0);
extern void func_8016AFB0(s32 a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
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
extern void func_8001CD9C(int, void *);
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern void func_8012EFB8(s32 a0);
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void func_8016BBA4(void *a0);
extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8016BD78(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04();
extern void func_8016C83C(s32 a0);
extern short func_8016CBC0(void);
extern void func_8016C998(s32 param_1);
extern void func_8016CB84(void *a0);
extern void func_8016D19C(void *a0);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void*);
extern void func_80147324(int a);
extern void RotMatrixYXZ(void *a, void *b);
extern void ApplyMatrixSV(void *a, void *b, void *c);
extern void func_8016D1D8(int param_1);
extern void func_8016D428(void *a0);
extern void func_8016D464(u8 *a0);
extern void func_8016D4DC(s32 a0);
extern void func_8016D688(int param_1);
extern void func_8016DBD8(u8 *a0);
extern void func_8016DA30(int param_1);
extern void func_8016DEA4(void *a0);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void func_8016E5B8(void *a0);
extern void func_8016E778();
extern void func_8016E688(void *a0);
extern void func_8016E6E4(s32 a0);
extern void func_8016E7C8(int param_1, short *p1, unsigned int *p2);
extern void func_8016E778(int param_1);
extern s32 D_80115218;
extern void func_8016E8F0(void);
extern void func_8016E918(short param_1, short param_2);
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern void func_8016EB3C(s32 p);
extern void func_8016EBA8(u8 *param_1);
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
extern s32 func_8016EFC8(s32);
extern s32 func_8016EFA8(s32 a0);
extern void func_8016F094(s32 *a0);
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
extern void func_8016F0E4(void);
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
extern void func_80147060(u8 *a0);
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
extern void func_8012A568(void (*a0)(void));
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void func_80170810(void *a0);
extern void func_801708B0(void *a0);
extern u8 D_800D5DA8;
extern void func_8017084C(s32 a0);
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
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
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
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void func_801714E4(void *a0);
extern struct B16 D_800A5E88;
extern struct B16 D_800A5E98;
extern struct B16 D_800A5EA8;
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
extern s32 func_80172CA0(void *a0);
extern void func_80172C50(void *a0);
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
extern void func_801734BC(s32 a0, s32 a1);
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
extern s32 func_80173B4C(void*);
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
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
extern void func_8012A018(s32 a, s32 b);
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
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void func_80174BF4(void * arg0);
extern s32 func_80174CB0(s32, s32);
extern s32 func_80174C60(s32 a0);
extern void func_80174C80(s32 a0);
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
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);
extern void func_8017553C(s32 *param);
extern void func_801757A0(s32 a0);
extern void func_80175590(void *arg0);
extern s16 D_800B9A02;
extern void func_801757A0(s32);
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
extern s32 func_80178004(s32 a0, s32 a1, s32 a2);
extern u8 D_8011F7B1;
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s16 D_8011F81E;
extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801783D0(s32 a0, s32 a1);
extern void *func_801777BC(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern u16 D_8011F82C;
extern u16 D_8011F82A;
extern u32 * func_80176D94(void *param_1, u32 param_2, s16 param_3_);
extern void func_801778A8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80176FF4(s32 a0);
extern u16 D_8011F830;
extern u16 D_8011F82E;
extern u32 * func_801770E0(void *param_1, u32 param_2, s16 param_3_);
extern void func_80177340(s32 a0);
extern u8 D_8011F837;
extern u8 D_8011F7F0;
extern u8 D_8011F7AB;
extern u32 * func_8017742C(u32 *param_1, s32 param_2, s32 param_3);
extern void func_801776EC(u8 *a0);
extern void func_801775E0(s32 param_1, s32 param_2);
extern void * func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern uint * func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4);
extern void func_80177F84(s32 param_1, s32 param_2);
extern u32 * func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
extern void func_80178438(u16 *arg0);
extern void func_801787D4(void);
extern void func_8012A908(void);
extern void func_8017869C(s32 a0);
extern void func_80130D0C(s32 a0);
extern s32 D_8011DB08;
extern void func_8017849C(void);
extern void func_8013E4B4(void);
extern s16 D_801270C4;
extern s16 D_801270C2;
extern u8 D_801270C6;
extern u8 D_801270C7;
extern s32 D_801274E0;
extern void func_80178608(void);
extern void func_80178744(s32 a0, s32 a1);
extern void func_80178840();
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80178840(int param_1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
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
extern void func_80179B74(u16 *p);
extern void func_80179DCC(short a0);
extern void func_80179DF8(void);
extern void func_80179E1C(short a0);
extern void func_80179E48(s16 a0);
extern void func_80179E74(s16 a0);
extern void func_80179EA0(u16 *a0);
extern void func_80179B74(u16 *p);
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
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
extern s32 func_8017AD0C(s32 arg0);
extern s32 func_8017AD0C(s32);
extern s32 func_8017ADE8(s32 a0);
extern s32 func_8017AE08(void);
/* ==== end §8b carried decl layer ==== */



extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s32 func_80012A60(s32 a0, s32 a1);

extern s16 D_801A94A0;
extern s16 D_801A94A2;
extern s16 D_801A94AC;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801A94A0;

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
                    func_8012B744(p, &D_801A94AC);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801A94A0+0xC == &D_801A94AC; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801A94A0 + 0xC)) < 0x101) {
                    D_801A94A0 = 0;
                    D_801A94A2 = 0;
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
            func_8012B744((void *)(pv + 4), &D_801A94AC);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801A94A0 + 0xC)) < 0x101) {
            D_801A94A0 = 0;
            D_801A94A2 = 0;
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
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801A7CCC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801A7CCE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801A7CD0, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801A7CC4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801A7CC6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801A7CC8, (s32)((s16)param_2));
}


extern void func_8012A418(void);

void func_8017B1D8(void) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_801A7C54;
    extern u16 D_801A7CD4;
    extern u16 D_801A7CD6;
    extern u16 D_801A7CD8;
    extern s16 D_801A94D0;
    func_8012A418();
    D_801A94D0 = 0;
    D_801A7C54 = 0;
    D_801A7CD4 = D_80126B5E;
    D_801A7CD6 = D_80126B62;
    D_801A7CD8 = D_80126B66;
}


extern void func_8012A018(s32 a, s32 b);

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_8017BE60(void*);
    extern u8 D_80185900[];
    extern s16 D_801A7CCC;
    extern s16 D_801A7CC4;
    extern u8 D_8012694C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80185900[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80185900[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801A7CCC;
        s16 *p78C = &D_801A7CC4;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801A94D0 = 1;
        D_801A7C54 = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CC4;
    extern u16 D_80185900;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801A7C74;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801A7C7C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185900)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185900)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801A7CCC) = loc0;
    (*(SV4_8017B368 *)&D_801A7CC4) = loc1;
    D_801A94D0 = 1;
    D_801A7C54 = 0;
}




s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CC4;
    extern u16 D_80185900;
    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801A7C74;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801A7C7C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185900)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185900)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801A7CCC) = loc0;
    (*(SV4_8017B368 *)&D_801A7CC4) = loc1;
    D_801A94D0 = 1;
    D_801A7C54 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801A7CCC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801A7CCC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801A7CCC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801A7CC4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801A7CC4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801A7CC4).c;
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
    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80185900[];
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80185900[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80185900[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801A7CCC;
        s16 *p78C = &D_801A7CC4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801A7CCE;
            v798 = D_801A7CD0;
            v78C = *p78C;
            v78E = D_801A7CC6;
            v790 = D_801A7CC8;
            __asm__ __volatile__("");
            D_801A94D0 = 1;
            D_801A7C54 = 0x1E;
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
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8 D_8012694C;
    extern s16 D_801A7C54;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    D_8012694C = 1;
    D_801A7C54 = 0;
    D_801A7CCC = (s16) D_80114F30;
    D_801A7CCE = (s16) D_80114F34;
    D_801A7CD0 = (s16) D_80114F38;
    D_801A7CC4 = (s16) D_80114F24;
    D_801A7CC6 = (s16) D_80114F28;
    D_801A7CC8 = (s16) D_80114F2C;
}




void func_8017B824(void) {

    extern s32 D_801151D4;
    extern s16 D_801A7CE4;
    extern s16 D_801A7CE6;
    extern s16 D_801A7CE8;
    extern s16 D_801A7CEC;
    extern s16 D_801A7CEE;
    extern s16 D_801A7CF0;
    D_801A7CE4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801A7CE6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801A7CE8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801A7CEC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801A7CEE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801A7CF0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH



void func_8017B880(void)
{

    extern s16 D_801A7CE4;
    extern s16 D_801A7CE6;
    extern s16 D_801A7CE8;
    extern s16 D_801A7CEC;
    extern s16 D_801A7CEE;
    extern s16 D_801A7CF0;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    D_80114F30 = D_801A7CE4;
    D_80114F34 = D_801A7CE6;
    D_80114F38 = D_801A7CE8;
    D_80114F24 = D_801A7CEC;
    D_80114F28 = D_801A7CEE;
    D_80114F2C = D_801A7CF0;
}





s32 func_8017B8E8(s32 src) {

    extern s16 D_801A7CC4;
    extern s16 D_801A7CCC;
    (*(S8_8017B8E8 *)&D_801A7CCC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801A7CC4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)




void func_8017B940(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_801A7CD4;
    extern u16 D_801A7CD6;
    extern u16 D_801A7CD8;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8  D_8012694C;
    extern s16 D_801A7C54;
    extern short D_801A7CDC;
    extern short D_801A7CDE;
    extern short D_801A7CE0;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801A7CD4);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801A7CD6);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801A7CD8);
    (*(s16 *)&D_801A7CDC) = buf[0];
    (*(s16 *)&D_801A7CDE) = buf[1];
    (*(s16 *)&D_801A7CE0) = buf[2];
    D_801A7CCC = D_80114F30 + buf[0];
    D_801A7C54 = 0;
    D_801A7CCE = D_80114F34 + buf[1];
    D_801A7CD0 = D_80114F38 + buf[2];
    D_801A7CC4 = D_80114F24 + buf[0];
    D_801A7CC6 = D_80114F28 + buf[1];
    D_801A7CC8 = D_80114F2C + buf[2];
}




// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_c2: 3x3 short rotation + pad + 3 long translation (offset 0x14) */


void func_8017BA3C(s32 param_1, s32 param_2)
{

    extern SV4 D_801A7C74;
    extern SV4 D_801A7C7C;
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_c2, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801A7C7C) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801A7C74 = svec;

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
    D_801A7C7C = buf1;
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);




s32 func_8017BB34(s32 param_1, s32 param_2)
{

    extern s32 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801A7C7C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801A7C74) = svec;

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
    (*(SV4_8017BB34*)&D_801A7C7C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0


void func_8017BC38(int param_1)
{

    extern void (*D_801A7C9C[10])(int);
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801A7C9C;
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

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    func_8017B0E4(param_1, 0xC);
    D_801A7C54 = D_801A7C54 + 1;
    if (D_801A7C54 >= 0x1F) {
        D_801A94D0 = 2;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)


extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    func_8017B0E4(param_1, 6);
    D_801A7C54 = D_801A7C54 + 1;
    if (0x18 < D_801A7C54) {
        func_8012A4BC();
        D_801A94D0 = 0;
    }
    return;
}



// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);



void func_8017BD50(int param_1)
{

    extern s16 D_801A7C54;
    extern void (*D_801A7C98)(void);
    extern short D_801A7CDC;
    extern short D_801A7CDE;
    extern short D_801A7CE0;
    extern s16 D_801A94D0;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    func_8017B0E4(param_1, 6);
    D_801A7C54 = D_801A7C54 + 1;
    if (D_801A7C54 >= 0x19) {
        if (D_801A7C98 != 0) {
            (*D_801A7C98)();
        } else {
            D_80114F30 = D_80114F30 + D_801A7CDC;
            D_80114F34 = D_80114F34 + D_801A7CDE;
            D_80114F38 = D_80114F38 + D_801A7CE0;
            D_80114F24 = D_80114F24 + D_801A7CDC;
            D_80114F28 = D_80114F28 + D_801A7CDE;
            D_80114F2C = D_80114F2C + D_801A7CE0;
            func_8012A4BC();
        }
        D_801A94D0 = 0;
    }
}




void func_8017BE60(void *a0) {

    extern void (*D_801859A0[])(void);
    D_801859A0[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;

typedef struct { s16 vx, vy, vz, pad; } SVEC_BEBC;

extern s32 func_800491EC(void);
extern void func_8017C294(u16 *a0, void *a1);
extern int func_8017C338(short *param_1, short *param_2, short *param_3, int param_4);
extern void func_8017C530(s32 a0, s32 a1);

#include "../shared/ov/func_8017BEBC__b0ea1ff1.h"


#include "../shared/ov/func_8017C294__dc415768.h"


#include "../shared/ov/func_8017C338__ec532abc.h"


#include "../shared/ov/func_8017C530.h"



/* func_8017C59C — ov_SC07_010_jr_8017AE2C — MAP-TILE model renderer (947 ins).
* Family clone of the byte-matched func_8017C6F4 (ov_SC03_126, s43). Same 947-ins body;
 * only the D_* cell-table and the rect-helper callee differ per overlay (s43 wave remap).
 * Outer: screen rect -> 64x64 cell grid window -> per-cell bbox RTPT/RTPS cull.
 * Inner: per-prim RTPT -> flag/nclip/opz cull -> switch(w & 0xF):
 *   0,1=POLY_F4 / 2,3=POLY_FT4 / 4,5=POLY_F3 / 6,7=POLY_FT3 -> OT insert.
 * NOTE: the F3 arm bbox-tests the packet through PFT3_C59C offsets (8/0x10/0x18)
 * — a source-level copy/paste quirk of this variant, reproduced verbatim.
 *
 * MATCH (947 ins, pin-free) — s43 Fable crack. Two load-bearing source shapes
 * (byte-proven; see .run/s43/fable/8017C6F4/NOTES.md):
 *   1. X-pass and Y-pass bbox min/max intermediates are DISTINCT variables
 *      (xmn1..xmx2 vs ymn1..ymx2) — the target allocates them differently.
 *   2. The cell-level clamps REUSE the prim-loop vars (mn/mx for X, mny/my
 *      for Y); there are no separate mnc/mxc. This puts the clamps in
 *      $t0/$a2/$a3/$a1 and makes the Y-pass `mny = ymn1` a deleted self-move.
 * Neither change matches alone (63 / 624 mismatches); prim lands $t5 and
 * cell $t3 naturally once the bbox block allocates right.
 */

typedef struct { u32 w0, w1, w2; } PrimC59C;
typedef struct { u8 *vtx; u32 f4; u32 xx, yy, zz; PrimC59C *prim, *end; } CellC59C;

typedef struct { s16 vx, vy; } DVEC2_C59C;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C59C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2; } PF3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2, x3, y3; } PF4_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; } PFT3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PFT4_C59C;

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv3c(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 8( %0 );"                          \
    "lwc2 $3, 12( %0 );"                         \
    "lwc2 $4, 16( %0 );"                         \
    "lwc2 $5, 20( %0 )"                          \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3c(r0) __asm__ volatile (       \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 4( %0 );"                         \
    "swc2 $14, 8( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

void func_8017C59C(s32 arg0)
{
    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MTX_C59C *);
    extern void func_80052E38(MTX_C59C *);
    extern void func_8017BEBC(void *, void *, s32);
    extern u8 D_801A93E0[];
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    s16 rect[4];
    DVEC2_C59C tmpxy[4];
    SVEC2_C59C box[8];
    SVEC2_C59C sxy[8];
    MTX_C59C mtx;
    struct { long flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 cx0, cx1, cy0, cy1, y, col;
    CellC59C **rowptr;
    CellC59C **p;
    CellC59C *cell;
    PrimC59C *prim;
    PrimC59C *end;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    u32 xlo, xhi, ylo, yhi, zlo, zhi;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 ymn1, ymx1, ymn2, ymx2;
    s32 my, mny, mx, mn;

    func_800491EC();
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);
    func_8017BEBC(D_801A93E0, rect, *(s32 *)(arg0 + 0x60));

    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    cx0 = (rect[0] + 0x4000) / 512;
    cx1 = (rect[0] + rect[2] + 0x4000) / 512 + 2;
    cx0 = (cx0 < 0) ? 0 : ((cx0 > 0x3F) ? 0x3F : cx0);
    cx1 = (cx1 < 0) ? 0 : ((cx1 > 0x3F) ? 0x3F : cx1);
    cy0 = (rect[1] + 0x4000) / 512 - 1;
    cy1 = (rect[1] + rect[3] + 0x4000) / 512 + 2;
    cy0 = (cy0 < 0) ? 0 : ((cy0 > 0x3F) ? 0x3F : cy0);
    cy1 = (cy1 < 0) ? 0 : ((cy1 > 0x3F) ? 0x3F : cy1);

    rowptr = (CellC59C **)(*(s32 *)(arg0 + 0xC)) + (cy0 * 64 + cx0);

    for (y = cy0; y < cy1; y++, rowptr += 0x40) {
        for (col = cx0, p = rowptr; col < cx1; col++, p++) {
            cell = *p;
            if (cell == 0) continue;

            wx = cell->xx;
            xlo = wx & 0xFFFF;
            xhi = wx >> 16;
            wy = cell->yy;
            ylo = wy & 0xFFFF;
            yhi = wy >> 16;
            wz = cell->zz;
            zlo = wz & 0xFFFF;
            zhi = wz >> 16;

            box[0].vx = xlo; box[0].vy = ylo; box[0].vz = zlo;
            box[1].vx = xhi; box[1].vy = ylo; box[1].vz = zlo;
            box[2].vx = xlo; box[2].vy = ylo; box[2].vz = zhi;
            box[3].vx = xhi; box[3].vy = ylo; box[3].vz = zhi;
            box[4].vx = xlo; box[4].vy = yhi; box[4].vz = zlo;
            box[5].vx = xhi; box[5].vy = yhi; box[5].vz = zlo;
            box[6].vx = xlo; box[6].vy = yhi; box[6].vz = zhi;
            box[7].vx = xhi; box[7].vy = yhi; box[7].vz = zhi;

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
            mn = xmn1;
            if (xmn2 < mn) mn = xmn2;
            mx = xmx1;
            if (mx < xmx2) mx = xmx2;
            if (mx < -0xA0) continue;
            if (!(mn < 0xA1)) continue;

            xa32 = sxy[0].vy;
            xb32 = sxy[1].vy;
            if (xb32 < xa32) { ymx1 = xa32; ymn1 = xb32; } else { ymn1 = xa32; ymx1 = xb32; }
            t32 = sxy[2].vy;
            if (ymx1 < t32) ymx1 = t32; else if (t32 < ymn1) ymn1 = t32;
            t32 = sxy[3].vy;
            if (ymx1 < t32) ymx1 = t32; else if (t32 < ymn1) ymn1 = t32;
            xa32 = sxy[4].vy;
            xb32 = sxy[5].vy;
            if (xb32 < xa32) { ymx2 = xa32; ymn2 = xb32; } else { ymn2 = xa32; ymx2 = xb32; }
            t32 = sxy[6].vy;
            if (ymx2 < t32) ymx2 = t32; else if (t32 < ymn2) ymn2 = t32;
            t32 = sxy[7].vy;
            if (ymx2 < t32) ymx2 = t32; else if (t32 < ymn2) ymn2 = t32;
            mny = ymn1;
            if (ymn2 < mny) mny = ymn2;
            my = ymx1;
            if (my < ymx2) my = ymx2;
            if (my < -0x78) continue;
            if (!(mny < 0x79)) continue;

            prim = cell->prim;
            end = cell->end;
            vtx = cell->vtx;
            while (prim < end) {
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
                    code = w & 0xF;
                    vd = vtx + ((w & 0xFFF0) >> 1);
                    gte_stopz(&g.opz);
                    if (g.opz > 0) {
                        switch (code) {
                        case 4:
                        case 5:
                            gte_stsxy3_f3(pkt);
                            gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                            if (((PFT3_C59C *)pkt)->x0 > ((PFT3_C59C *)pkt)->x1) {
                                mx = ((PFT3_C59C *)pkt)->x0;
                                mn = ((PFT3_C59C *)pkt)->x1;
                            } else {
                                mn = ((PFT3_C59C *)pkt)->x0;
                                mx = ((PFT3_C59C *)pkt)->x1;
                            }
                            if (((PFT3_C59C *)pkt)->x2 > mx) mx = ((PFT3_C59C *)pkt)->x2;
                            else if (((PFT3_C59C *)pkt)->x2 < mn) mn = ((PFT3_C59C *)pkt)->x2;
                            if (mx >= -0xA0 && mn < 0xA1) {
                                if (((PFT3_C59C *)pkt)->y0 > ((PFT3_C59C *)pkt)->y1) {
                                    my = ((PFT3_C59C *)pkt)->y0;
                                    mny = ((PFT3_C59C *)pkt)->y1;
                                } else {
                                    mny = ((PFT3_C59C *)pkt)->y0;
                                    my = ((PFT3_C59C *)pkt)->y1;
                                }
                                if (((PFT3_C59C *)pkt)->y2 > my) my = ((PFT3_C59C *)pkt)->y2;
                                else if (((PFT3_C59C *)pkt)->y2 < mny) mny = ((PFT3_C59C *)pkt)->y2;
                                if (my >= -0x78 && mny < 0x79) {
                                    s32 za;
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
                                    ((PF3_C59C *)pkt)->rgbc = prim->w0;
                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                    pkt += 0x14;
                                }
                            }
                            break;
                        case 6:
                        case 7:
                            gte_stsxy3c(&tmpxy[0]);
                            gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                            if (tmpxy[0].vx > tmpxy[1].vx) {
                                mx = tmpxy[0].vx;
                                mn = tmpxy[1].vx;
                            } else {
                                mn = tmpxy[0].vx;
                                mx = tmpxy[1].vx;
                            }
                            if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                            else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                            if (mx >= -0xA0 && mn < 0xA1) {
                                if (tmpxy[0].vy > tmpxy[1].vy) {
                                    my = tmpxy[0].vy;
                                    mny = tmpxy[1].vy;
                                } else {
                                    mny = tmpxy[0].vy;
                                    my = tmpxy[1].vy;
                                }
                                if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                if (my >= -0x78 && mny < 0x79) {
                                    s32 za;
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
                                    *(u32 *)&((PFT3_C59C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                    *(u32 *)&((PFT3_C59C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                    *(u32 *)&((PFT3_C59C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                    tp = (u32 *)prim->w0;
                                    ((PFT3_C59C *)pkt)->rgbc = tp[0];
                                    ((PFT3_C59C *)pkt)->uvc0 = tp[1];
                                    ((PFT3_C59C *)pkt)->uvp1 = tp[2];
                                    ((PFT3_C59C *)pkt)->uv2 = tp[3];
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
                            if (((PF4_C59C *)pkt)->x0 > ((PF4_C59C *)pkt)->x1) {
                                mx = ((PF4_C59C *)pkt)->x0;
                                mn = ((PF4_C59C *)pkt)->x1;
                            } else {
                                mn = ((PF4_C59C *)pkt)->x0;
                                mx = ((PF4_C59C *)pkt)->x1;
                            }
                            if (((PF4_C59C *)pkt)->x2 > mx) mx = ((PF4_C59C *)pkt)->x2;
                            else if (((PF4_C59C *)pkt)->x2 < mn) mn = ((PF4_C59C *)pkt)->x2;
                            if (((PF4_C59C *)pkt)->y0 > ((PF4_C59C *)pkt)->y1) {
                                my = ((PF4_C59C *)pkt)->y0;
                                mny = ((PF4_C59C *)pkt)->y1;
                            } else {
                                mny = ((PF4_C59C *)pkt)->y0;
                                my = ((PF4_C59C *)pkt)->y1;
                            }
                            if (((PF4_C59C *)pkt)->y2 > my) my = ((PF4_C59C *)pkt)->y2;
                            else if (((PF4_C59C *)pkt)->y2 < mny) mny = ((PF4_C59C *)pkt)->y2;
                            gte_stflg(&g.flag);
                            if (!(g.flag & 0x7F85E000)) {
                                gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                gte_stsxy((long *)&((PF4_C59C *)pkt)->x3);
                                if (((PF4_C59C *)pkt)->x3 < mn) mn = ((PF4_C59C *)pkt)->x3;
                                else if (mx < ((PF4_C59C *)pkt)->x3) mx = ((PF4_C59C *)pkt)->x3;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (((PF4_C59C *)pkt)->y3 < mny) mny = ((PF4_C59C *)pkt)->y3;
                                    else if (my < ((PF4_C59C *)pkt)->y3) my = ((PF4_C59C *)pkt)->y3;
                                    if (my >= -0x78 && mny < 0x79) {
                                        s32 za, zb;
                                        u32 *otp;
                                        zb = g.sz2;
                                        if (zb < g.sz3) zb = g.sz3;
                                        za = g.sz0;
                                        if (za < g.sz1) za = g.sz1;
                                        if (za < zb) za = zb;
                                        g.opz = za;
                                        if (code != 0) g.opz = za + 0x200;
                                        ((PF4_C59C *)pkt)->rgbc = prim->w0;
                                        otp = (u32 *)(((g.opz >> 2) << 2) + ot);
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
                            gte_stflg(&g.flag);
                            if (!(g.flag & 0x7F85E000)) {
                                gte_stsxy(&tmpxy[3]);
                                gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                if (tmpxy[0].vx > tmpxy[1].vx) {
                                    mx = tmpxy[0].vx;
                                    mn = tmpxy[1].vx;
                                } else {
                                    mn = tmpxy[0].vx;
                                    mx = tmpxy[1].vx;
                                }
                                if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                if (tmpxy[3].vx > mx) mx = tmpxy[3].vx;
                                else if (tmpxy[3].vx < mn) mn = tmpxy[3].vx;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    if (tmpxy[3].vx > my) my = tmpxy[3].vx;
                                    else if (tmpxy[3].vx < mny) mny = tmpxy[3].vx;
                                    if (my >= -0x78 && mny < 0x79) {
                                        s32 za, zb;
                                        u32 *otp;
                                        u32 *tp;
                                        u32 uvw;
                                        gte_avsz4();
                                        zb = g.sz2;
                                        if (zb < g.sz3) zb = g.sz3;
                                        za = g.sz0;
                                        if (za < g.sz1) za = g.sz1;
                                        if (za < zb) za = zb;
                                        g.opz = za;
                                        if (code != 2) g.opz = za + 0x200;
                                        *(u32 *)&((PFT4_C59C *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                        *(u32 *)&((PFT4_C59C *)pkt)->x3 = *(u32 *)&tmpxy[3];
                                        tp = (u32 *)prim->w0;
                                        ((PFT4_C59C *)pkt)->rgbc = tp[0];
                                        ((PFT4_C59C *)pkt)->uvc0 = tp[1];
                                        ((PFT4_C59C *)pkt)->uvp1 = tp[2];
                                        uvw = tp[3];
                                        ((PFT4_C59C *)pkt)->uv2 = uvw;
                                        ((PFT4_C59C *)pkt)->uv3 = uvw >> 16;
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
                prim++;
            }
        }
    }
    D_800A5E60 = pkt;
}




void func_8017D468(void *a0) {

    extern void (*D_801859FC[])(void);
    D_801859FC[*(u8 *)((s32)a0 + 0x15)]();
}


#include "common.h"

extern void func_80019028(void);
extern void func_80175494(void);
extern void func_8017DC68(void);
extern void func_800167B8(s32 a0);

s32 func_8017D4A4(s32 a0) {
    func_80019028();
    func_80175494();
    func_8017DC68();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017D4F8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




void func_8017D51C(void *a0) {

    extern void (*D_80185A04[])(void);
    D_80185A04[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017D558(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0xa;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D574(u8 *a0) {
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


#include "common.h"

extern s32 func_800167F0(s32 a0);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8002AEE4(void);
extern s8 D_80078EC6;

s32 func_8017D5F0(void) {
    s32 v0;

    v0 = func_800167F0(4);
    if ((v0 & 0xFFFF) != 0) {
        func_80029514(0x6A4);
        func_80029124(0x11D, 1);
        func_80029124(0x123, 1);
        D_80078EC6 = 1;
        func_8002AEE4();
        return 1;
    }

    return 0;
}


extern void func_8017DCB8(s32 a0);
extern void func_80171928(void *a0);

void func_8017D654(void *a0) {
    func_8017DCB8(1);
    func_80171928(a0);
}




void func_8017D688(void *a0) {

    extern void (*D_80185BF8[])(void);
    D_80185BF8[*(u8 *)((s32)a0 + 0x216)]();
}


void func_8017D6C4(s32 *a0) {
    func_8017DCB8(2);
    func_80171A80(a0, 0x12C);
    *(s16 *)((s32)a0 + 0x20C) = 0;
    func_80171990((u8 *)a0);
}


extern u16 D_800B99DA;
extern s8 D_80185C00;
extern s8 D_80185C02;
extern s16 D_80185C08;
extern void func_8013C9C4(void *);
extern void func_80019064(void *);
extern s32 func_80171A88(s32);
extern void func_8017DCB8(s32);
extern void func_80171928(void *);

void func_8017D708(s32 param_1) {
    u16 sVar1;
    s32 sum;
    s32 ret;
    s8 *base;

    if ((D_800B99DA & 3) == 0) {
        sVar1 = *(u16 *)(param_1 + 0x20c) + 1;
        *(u16 *)(param_1 + 0x20c) = sVar1;
        sum = *(s32 *)(param_1 + 0x204) + (s16)sVar1;
        *(s32 *)(param_1 + 0x204) = sum;
        if (sum > 0x800) {
            *(s32 *)(param_1 + 0x204) = 0x800;
        }
        base = &D_80185C00;
        *base = (s8)(*(s32 *)(param_1 + 0x204) >> 8);
        D_80185C02 = (s8)(-(*(s32 *)(param_1 + 0x204) >> 8));
        func_8013C9C4(base);
        *(u8 *)&D_80185C08 = (u8)((u8)*base * 0x10 + 0x3F);
        func_80019064(&D_80185C08);
    }
    ret = func_80171A88(param_1);
    if (ret != 0) {
        func_8017DCB8(3);
        func_80171928((void *)param_1);
    }
}



extern s32 func_8017DCC8(void);
    extern void func_80171928(void *a0);
    void func_8017D7E4(void *a0) {
        if (((s32 (*)(s32))func_8017DCC8)((s32)a0) == 4) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }




void func_8017D820(void *a0) {

    extern void (*D_80185C24[])(void);
    D_80185C24[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8017DDA0(s32 *a0);
extern void func_80171A80(s32 *a0, s32 a1);
extern s32 func_80171990(u8*);
void func_8017D85C(s32 *a0) {
    s32 *s = a0;
    func_8017DDA0(s);
    func_80171A80(s, 0x1e);
    ((void (*)(void *))func_80171990)(s);
}


extern s32 func_80171A88(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8017EBB8(void *a0, void *a1);
extern void func_80147324(s32 a0);
extern void func_8014706C(void *a0);
extern void func_801542A4(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);
extern s32 D_80185A10;

void func_8017D898(s32 param_1) {
    s32 sp10[2];

    if (func_80171A88(param_1) != 0) {
        func_80015978(param_1 + 4, sp10);
        *(s16 *)sp10 -= 0x20;
        *(s16 *)((u8 *)sp10 + 2) -= 0x20;
        func_8017EBB8((void *)0, sp10);
        func_80147324(0xC13);
        func_8014706C((void *)param_1);
        func_801542A4((s32 *)param_1, (s32)&D_80185A10);
        func_80171990((u8 *)param_1);
    }
}


extern s32 D_801151D4;
extern s32 D_80185AC8;
extern void func_801542A4(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_8017D91C(u8 *a0) {
    s32 ws = D_801151D4;
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        *(s16 *)(ws + 0x22) = 0x200;
        *(s16 *)(ws + 0x1A) = 0x200;
        func_801542A4((s32 *)a0, (s32)&D_80185AC8);
        func_80171990(a0);
    }
}


extern s32 D_801151D4;
extern s32 D_80185AC8;
extern s32 func_80171990(u8 *a0);
extern void func_801542A4();

void func_8017D974(a0)
u8 *a0;
{
    s32 ws = D_801151D4;
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        *(s16 *)(ws + 0x22) = 0x600;
        *(s16 *)(ws + 0x1A) = 0x600;
        func_801542A4((s32 *)a0, (s32)&D_80185AC8);
        func_80171990(a0);
    }
}


extern s32 D_801151D4;
extern s32 D_80185AC8;
extern void func_801542A4(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_8017D9CC(u8 *a0) {
    s32 ws = D_801151D4;
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        *(s16 *)(ws + 0x20) = -0x38;
        *(s16 *)(ws + 0x18) = -0x38;
        *(s16 *)(ws + 0x22) = 0x400;
        *(s16 *)(ws + 0x1A) = 0x400;
        func_801542A4((s32 *)a0, (s32)&D_80185AC8);
        func_80171990(a0);
    }
}


extern void func_80147324(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8017EBB8(void *a0, void *a1);
extern void func_8017F5FC(s16);
extern s32 func_80171990(u8 *a0);
extern u8 D_80185B70[];
extern s32 D_80185C10;

void func_8017DA30(void *arg0) {
    if (*(u16 *)((s32)arg0 + 0xB8) & 0x4000) {
        func_80147324(0xC12);
        func_8013C9C4(&D_80185C10);
    }
    if (*(u16 *)((s32)arg0 + 0xB8) & 0x8000) {
        func_8017EBB8((void *)3, D_80185B70);
        func_8017EBB8((void *)4, D_80185B70);
        ((void (*)(s32))func_8017F5FC)(0);
        ((void (*)(s32))func_8017F5FC)(1);
        func_80171990(arg0);
    }
}


extern s32 func_8017DCC8(void);
extern void func_80016940(s32 a0);
extern s32 func_80171990(u8 *a0);

void func_8017DAD0(void *a0) {
    if (func_8017DCC8() == 5) {
        func_80016940(4);
        func_80171990(a0);
    }
}


extern s32 D_801151D4;
extern u8 D_801202A0[];
extern s32 func_80016978(s32 a0);
extern void func_8012C098(void *a0);

void func_8017DB14(void *arg0) {
    s32 p;
    s32 i;
    s32 c1;
    s32 c2;
    u16 h;
    u8 *q;

    p = D_801151D4;
    if ((func_80016978(4) & 0xFFFF) == 0) {
        return;
    }
    func_80147324(0xC15);
    i = 0;
    c1 = 0x3A9;
    c2 = 0x3AA;
    q = D_801202A0;
    for (; i < 0x60; i++, q += 0x10C) {
        h = *(u16 *)q;
        if (h == c1) {
            func_8012C098((void *)q);
            h = *(u16 *)q;
        }
        if (h == c2) {
            func_8012C098((void *)q);
        }
    }
    func_8017DCB8(6);
    func_80171A80((s32 *)arg0, 0x7F);
    func_8014708C(arg0);
    func_801472C8((struct S *)arg0);
    *(u16 *)(p + 0x20) = 0x38;
    *(u16 *)(p + 0x18) = 0x38;
    func_80171990((u8 *)arg0);
}


extern void func_80016450(s32 a0, s32 a1);
extern s32 func_80171A88(s32 a0);
extern void func_80171928(void *a0);
extern void func_8017DCB8(s32 a0);

void func_8017DC10(void *arg0) {
    func_80016450((*(s32 *)((char *)arg0 + 0x200) << 1) & 0xFE, 0);
    if (func_80171A88((s32)arg0) != 0) {
        func_8017DCB8(7);
        func_80171928(arg0);
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017DC68(void) {

    extern s32 D_80185B78(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185B78, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017DC90(void) {

    extern s32 D_80185C48(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80185C48, 0x1000000);
}


void func_8017DCB8(s32 a0) {

    extern s32 D_801A7CF8;
    D_801A7CF8 = a0;
}




s32 func_8017DCC8(void) {

    extern s32 D_801A7CF8;
    return D_801A7CF8;
}




void func_8017DCD8(void) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern void func_8017DE68(void *a0);
    extern Blob8_8018A47C_8017DEA4 D_801274E8;
    extern Blob8_8018A47C_8017DEA4 D_80185C5C;

    D_801274E8 = D_80185C5C;
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0xA00;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017DE68, 0);
    func_8012A094((s32)D_80126948);
    func_8017DE68((void *)D_80126948);
}




void func_8017DDA0(s32 *a0) {
    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern void func_8017DE68(void *a0);
    extern Blob8_8018A47C_8017DEA4 D_801274E8;
    extern Blob8_8018A47C_8017DEA4 D_80185C64;

    D_801274E8 = D_80185C64;
    D_80126954 = 0x190;
    D_8012695C = 0x190;
    D_80126968 = 0x38;
    D_8012696A = 0x400;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x10;
    D_8012697A = 0;
    func_8012A018((s32)func_8017DE68, 0);
    func_8012A094((s32)D_80126948);
    func_8017DE68((void *)D_80126948);
}




void func_8017DE68(void *a0) {

    extern void (*D_80185C6C[])(void);
    D_80185C6C[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern void func_8017DEEC(s32, s16*);

void func_8017DEA4(s32 a0) {

    extern Blob8_8018A47C_8017DEA4 D_801274E8;
    Blob8_8018A47C_8017DEA4 tmp;

    tmp = D_801274E8;
    ((void (*)(s32, Blob8_8018A47C_8017DEA4 *))func_8017DEEC)(a0, &tmp);
}



// @class: schedule
// @stuck: none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017DEEC(s32 param_1, s16 *param_2) {
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




void func_8017E084(void *a0) {

    extern void (*D_80185CE8[])(void);
    D_80185CE8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E0C0(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v1;
    s32 v0;

    extern void func_8017DCB8(s32);
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *);
    extern void func_8001C214(s32, s32);
    extern void func_8001D0E8(s32, s32, s32);
    extern s32 func_8012AD50(void *);
    extern u8 D_801A7D09[];
    extern u8 D_80192358[];

    s1 = a0;
    func_8017DCB8(0);
    v1 = 9;
    {
        char *p = (char *)&D_801A7D09;
        do {
            *p = 0;
            v1--;
            p--;
        } while (v1 >= 0);
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s1 + 0x20) = v0;
    s0 = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s1);
    } else {
        func_8001C214(s0, (s32)&D_80192358);
        func_8001D0E8(s0, 0x7FFF, 0x7FFF);
        *(s32 *)(s0 + 4) |= 0x40;
        func_8012AD50((void *)s1);
    }
}


void func_8017E168(void) {
}



void func_8017E170(void *a0) {

    extern void (*D_80185CF0[])(void);
    D_80185CF0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E1AC(s32 param_1)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern s32 func_8012AD50(void *a0);
    extern u8 D_80193564[];

    s1 = param_1;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s1 + 0x20) = v0;
    s0 = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s1);
        return;
    }
    func_8001C214(s0, (s32)&D_80193564);
    func_8001D0E8(s0, 0x7FFF, 0x7FFF);
    *(u32 *)(s0 + 4) |= 0x80000040;
    func_8012AD50((void *)s1);
}


void func_8017E234(void *a0) {
    s32 *s0 = *(s32 **)((s32)a0 + 0x20);
    if (func_8017DCC8() == 6) {
        *(s32 *)((s32)s0 + 4) &= 0x7FFFFFFF;
        func_8012AD50(a0);
    }
}


void func_8017E290(void) {
}



void func_8017E298(void *a0) {

    extern void (*D_80185CFC[])(void);
    D_80185CFC[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E2D4(s32 param_1)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern s32 func_8012AD50(void *a0);
    extern u8 D_8019EDE4[];

    s1 = param_1;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s1 + 0x20) = v0;
    s0 = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s1);
        return;
    }
    func_8001C214(s0, (s32)&D_8019EDE4);
    func_8001D0E8(s0, 0x7FFF, 0x7FFF);
    *(u32 *)(s0 + 4) |= 0x40;
    *(u16 *)(s0 + 0x2C) |= 0x10;
    *(u16 *)(s0 + 0x18) = 0;
    *(s32 *)(s1 + 0xDC) = 0;
    *(u16 *)(s1 + 0xFC) = 0;
    *(u16 *)(s1 + 0xFE) = 4;
    func_8012AD50((void *)s1);
}


extern u16 D_800B99DA;
extern void func_8017E70C();

void func_8017E374(s32 a0) {
    s32 v0;
    s32 s0;
    s0 = a0;
    v0 = func_8017DCC8();
    if (v0 == 2) {
        if ((D_800B99DA & 3) == 0) {
            func_8017E70C(s0);
        }
    }
    v0 = func_8017DCC8();
    if (v0 == 3) {
        *(s16*)(s0 + 0x100) = 0x80;
        func_8012AD44((s32*)s0, 2);
    }
}






extern void func_80016450(s32 a0, s32 a1);
extern void func_8017E520();
extern void func_80019064(void *a0);
extern void func_8013C9C4(void *arg0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern void (*D_80185D10[])(void);
extern void (*D_80185D18[])(void);
extern void (*D_80185D20[])(void);

void func_8017E3EC(s32 param_1) {
    s32 s0;
    s32 s1;
    u16 v0;

    __asm__ __volatile__("" : "=r"(s0) : "0"(param_1));

    s1 = *(s32 *)(s0 + 0x20);

    v0 = *(u16 *)(s0 + 0x100) - 4;
    *(u16 *)(s0 + 0x100) = v0;

    if ((s16)v0 < 0) {
        *(u16 *)(s0 + 0x100) = 0;
    }

    func_80016450(*(u8 *)(s0 + 0x100), 0);
    func_8017E520(s0);

    *(s32 *)(s0 + 0xDC) += 0xC0000;

    v0 = *(u16 *)(s1 + 0x18) + *(u16 *)(s0 + 0xDE);
    *(u16 *)(s1 + 0x18) = v0;

    if ((s16)v0 >= 0x1001) {
        *(u16 *)(s1 + 0x18) = 0x1000;
        func_80019064(D_80185D20);
        func_8013C9C4(D_80185D18);
        func_8012BF4C((s32 *)s0, 0x1E);
        func_8012AD50((void *)s0);
    } else {
        func_8013C9C4(D_80185D10);
    }
}


extern void func_8017E520();
extern s32 func_8012BEE8(s32 a0);
extern void func_8017DCB8(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_8017E4D0(s32 a0) {
    func_8017E520(a0);
    if (func_8012BEE8(a0) != 0) {
        func_8017DCB8(0x4);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


#include "../shared/ov/func_8017E518__76785405.h"

extern void func_8017E5B8();

void func_8017E520(s32 a0) {
    s16 t;
    if (*(s16 *)((s32)a0 + 0xFC) < 6) {
        t = *(u16 *)((s32)a0 + 0xFE) - 1;
        *(u16 *)((s32)a0 + 0xFE) = t;
        if (t == -1) {
            func_8017E5B8(a0, (*(s16 *)((s32)a0 + 0xFC))++);
            func_8017E5B8(a0, (*(s16 *)((s32)a0 + 0xFC))++);
            *(u16 *)((s32)a0 + 0xFE) = 4;
        }
    }
}


void func_8017E5B8(s32 a0, s32 a1) {
    struct P8 { s16 unk0; u8 pad[6]; };
    struct P4 { u16 unk0; u16 pad; };
    struct EntA { u8 pad[0xDC]; s32 unkDC; u8 pad2[0x1C]; u16 unkFC; };
    extern struct P8 D_80185D28[];
    extern struct P8 D_80185D2A[];
    extern struct P8 D_80185D2C[];
    extern struct P8 D_80185D2E[];
    extern struct P4 D_80185D5A[];
    extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
    extern void func_80015954(s32 a0, s32 a1);
    extern s32 func_8012C588(s32 a0, s32 a1);
    struct EntA *p;
    s32 i;

    func_80146A6C(0x1E, (void *)a0, D_80185D28[a1].unk0, D_80185D2A[a1].unk0,
                  D_80185D2C[a1].unk0, 0, 0);
    for (i = 0; i < 4; i++) {
        p = (struct EntA *)func_8012C588(0x3A6, 0);
        if (p != 0) {
            func_80015954((s32)&D_80185D28[a1], (s32)p + 4);
            p->unkFC = D_80185D5A[D_80185D2E[a1].unk0].unk0 + (i * 170 - 341);
            p->unkDC = 0;
        }
        p = (struct EntA *)func_8012C588(0x3A6, 0);
        if (p != 0) {
            func_80015954((s32)&D_80185D28[a1], (s32)p + 4);
            p->unkFC = D_80185D5A[D_80185D2E[a1].unk0].unk0 + (i * 170 - 227);
            p->unkDC = 1;
        }
    }
}


extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

struct S6C { u8 pad[8]; };
struct S72 { s16 unk0; u8 pad[6]; };
struct S9E { u16 unk0; u16 pad; };
struct Ent { u8 pad[0xDC]; s32 unkDC; u8 pad2[0x1C]; u16 unkFC; };

extern struct S6C D_80185D6C[];
extern struct S72 D_80185D72[];
extern struct S9E D_80185D9E[];

void func_8017E70C(void) {
    register s32 r __asm__("$19"); /* incoming $s3, never written */
    struct Ent *p;
    s32 t;

    t = rand() % 6;
    p = (struct Ent *)func_8012C588(0x3A6, 0);
    if (p != 0) {
        func_80015954((s32)&D_80185D6C[t], (s32)p + 4);
        p->unkFC = D_80185D9E[D_80185D72[t].unk0].unk0 + (r * 170 - 341);
        p->unkDC = 0;
    }
    p = (struct Ent *)func_8012C588(0x3A6, 0);
    if (p != 0) {
        func_80015954((s32)&D_80185D6C[t], (s32)p + 4);
        p->unkFC = D_80185D9E[D_80185D72[t].unk0].unk0 + (r * 170 - 227);
        p->unkDC = 1;
    }
}




void func_8017E854(void *a0) {

    extern void (*D_80185DB0[])(void);
    D_80185DB0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017E890(s32 a0) {
    extern void func_8012C194(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001CEC0(s32 a0, void *a1);
    extern s32 func_80010B10(void);
    extern s32 func_8012AD50(void *a0);
    extern void (*D_80185CB0[])(void);

    register s32 s0 __asm__("$16") = a0;
    register s32 s1 __asm__("$17");
    s32 r;

    r = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s1) : "r"(r));
    *(s32 *)(s0 + 0x20) = r;

    if (r == 0) {
        func_8012CAE4((void *)s0);
    } else {
        func_8001CEC0(s1, (void *)D_80185CB0);
        *(s16 *)(s1 + 0x2C) = func_80010B10();
        func_8012AD50((void *)s0);
    }
}


extern s16 D_800B9ABA;

void func_8017E900(void *a0) {
    D_800B9ABA = 0xF0;
    *(s16 *)((s32)a0 + 0xA) = 0xF0;
}


void func_8017E914(void *a0) {

    extern void (*D_80185DB8[])(void);
    D_80185DB8[*(u16 *)((s32)a0 + 0x2)]();

    if (a0 != 0 && *(s32 *)((s32)a0 + 0x20) != 0) {
        func_8012B2CC((s32)a0);
    }
}


extern s32 func_8012AD50(void*);
void func_8017E97C(void) {
    ((void (*)(void))func_8012AD50)();
}


extern void func_8012C1B8(void);
extern void func_8001599C(void *a0, void *a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern u8 D_80185DD4[];
extern u8 D_8019F064[];

void func_8017E99C(s32 param_1) {
    s32 v1;
    s32 s0;
    s32 sp[3];

    s0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = s0;
    if (s0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(s0, D_8019F064);
    func_8001D0E8(s0, 0x7FFF, 0x7FFF);
    *(u32 *)(s0 + 4) |= 0x40;
    v1 = *(s32 *)(param_1 + 0xDC);
    if (v1 != 0) {
        if (v1 != 1) {
            goto label;
        }
        *(u16 *)(s0 + 0x1C) = 0x400;
        *(u16 *)(s0 + 0x1A) = 0x400;
        *(u16 *)(s0 + 0x18) = 0x400;
        v1 = *(u16 *)(s0 + 0x2C);
        v1 |= 0x10;
        *(u16 *)(s0 + 0x2C) = v1;
        *(u16 *)(param_1 + 0xFC) += (rand() & 3) * 0x38;
    }
    sp[0] = 0;
    sp[1] = (rand() & 0xF) * -0x100000 / 16;
    sp[2] = (rand() & 0xF) * -0x40000 / 16;
label:
    func_8001382C(*(s16 *)(param_1 + 0xFC), &sp[0], &sp[0]);
    func_8001599C(&sp[0], (void *)(param_1 + 0x10));
    func_8001599C(D_80185DD4, (void *)(param_1 + 0x44));
    func_8012BF4C((s32 *)param_1, 0x5A);
    func_8012AD50((void *)param_1);
}


void func_8017EAF4(s32 arg0) {
    extern u16 D_800B99DA;
    extern void func_8012AD80(s32 a0);
    extern s32 func_8012BEE8(s32 a0);
    extern u8 *func_8012913C(s32 a0);
    extern void func_8012C098(void *a0);
    register s32 pv __asm__("$16") = arg0;
    register s32 wp __asm__("$17");
    u16 flag;
    u8 *a;
    s32 t;

    flag = D_800B99DA;
    wp = *(s32 *)(pv + 0x20);
    if ((flag & 3) == 0) {
        a = func_8012913C(0x75);
        if (a != 0) {
            *(s32 *)(a + 4) = *(s32 *)(pv + 4);
            *(s32 *)(a + 8) = *(s32 *)(pv + 8);
            t = *(s32 *)(pv + 0xC);
            *(s32 *)(a + 0x34) = 1;
            *(s32 *)(a + 0xC) = t;
        }
    }
    *(u16 *)(wp + 0x10) += 0x38;
    *(u16 *)(wp + 0x12) += 0x71;
    *(u16 *)(wp + 0x14) += 0x5B;
    func_8012AD80(pv);
    if (func_8012BEE8(pv) != 0) {
        func_8012C098((void *)pv);
    }
}


extern u8 D_801A7D00[];
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_80015954(s32 a0, s32 a1);

s32 aF8017EBB8(s32 a0, s32 a1) __asm__("func_8017EBB8");
s32 aF8017EBB8(s32 a0, s32 a1) {
    s32 i = 0;
    s32 one = 1;
    u8 *p = D_801A7D00;

    for (; i < 10; i++, p++) {
        if (*p == 0) {
            s32 ent = func_8012C588(0x3A9, 0);
            if (ent != 0) {
                func_80015954(a1, ent + 4);
                *(s16 *)(ent + 0xFC) = a0;
                *(s16 *)(ent + 0x70) = i;
                *p = one;
            }
            return 1;
        }
    }
    return 0;
}


extern void (*D_80185DE4[])(void *);
extern void (*D_80185DF0[])(void *);
extern void (*D_80185DFC[])(void *);
extern void (*D_80185E08[])(void *);
extern void (*D_80185E1C[])(void *);

void func_8017EC6C(s32 arg0)
{
    void (*pfn)(void *);

    switch (*(s16 *)(arg0 + 0xFC)) {
    case 0:
        pfn = D_80185DE4[*(u16 *)((s32)arg0 + 2)];
        break;
    case 1:
        pfn = D_80185DF0[*(u16 *)((s32)arg0 + 2)];
        break;
    case 2:
        pfn = D_80185DFC[*(u16 *)((s32)arg0 + 2)];
        break;
    case 3:
        pfn = D_80185E08[*(u16 *)((s32)arg0 + 2)];
        break;
    case 4:
        pfn = D_80185E1C[*(u16 *)((s32)arg0 + 2)];
        break;
    default:
        return;
    }
    pfn((void *)arg0);
}


extern s32 func_8012AD50(void*);
void func_8017ED54(void) {
    ((void (*)(void))func_8012AD50)();
}


#include "common.h"

extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void*);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(s32, void *);
extern void func_8012C194(void);
extern u32 D_801A7D0C[];

void func_8017ED74(s32 a0) {
    register s32 s2 __asm__("$18") = a0;
    register s32 s0 __asm__("$16");
    s32 s1;
    s32 t;
    s32 u;
    s32 r;

    t = *(s16 *)(s2 + 0x70);
    u = (s32)(u8 *)D_801A7D0C;
    t <<= 6;
    s1 = t + u;
    r = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(r));
    *(s32 *)(s2 + 0x20) = r;

    if (r == 0) {
        func_8012CAE4((void *)s2);
    } else {
        func_8001CD9C(s0, (void *)s1);
        *(u16 *)(s0 + 0x1E) = 0x199;
        *(s32 *)(s0 + 4) |= 0x50000000;
        func_800233CC((void *)s1, 0x40);
        *(s32 *)s1 = 0x2020C0;
        *(s32 *)(s1 + 4) = 0;
        func_8012AD50((void *)s2);
    }
}


#include "common.h"

extern s32 func_8017F4A8(void *a0, void *a1);
extern s32 func_8017F51C(void *a0, void *a1);
extern s32 func_8017F478(u8 *a0);
extern u8 D_80185E2C[];
extern u8 D_80185E30[];

void func_8017EE24(void *a0) {
    s32 v0;

    v0 = func_8017F4A8(a0, D_80185E2C);
    if (v0 == 0) {
        v0 = func_8017F51C(a0, D_80185E30);
    }
    if (v0 != 0) {
        func_8017F478((u8 *)a0);
    }
}


extern s32 func_8012AD50(void*);
void func_8017EE7C(void) {
    ((void (*)(void))func_8012AD50)();
}


extern s32 func_8012AD50(void *a0);
extern u32 D_801A7D0C[];
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);

void func_8017EE9C(a0)
s32 a0;
{
    register s32 s2 __asm__("$18") = a0;
    register s32 s0 __asm__("$16");
    s32 s1;
    s32 t;
    s32 u;
    s32 r;

    t = *(s16 *)(s2 + 0x70);
    u = (s32)(u8 *)D_801A7D0C;
    t <<= 6;
    s1 = t + u;
    r = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(r));
    *(s32 *)(s2 + 0x20) = r;

    if (r == 0) {
        func_8012CAE4((void *)s2);
    } else {
        func_8001CD9C(s0, (void *)s1);
        *(u16 *)(s0 + 0x1E) = 0x199;
        *(s32 *)(s0 + 4) |= 0x50000000;
        func_800233CC((void *)s1, 0x40);
        *(s32 *)s1 = 0x2020C0;
        *(s32 *)(s1 + 4) = 0;
        func_8012AD50((void *)s2);
    }
}


extern s32 func_8017F478(u8 *a0);
extern s32 func_8017F4A8(void *a0, void *a1);
extern s32 func_8017F51C(void *a0, void *a1);
extern u8 D_80185E34[];
extern u8 D_80185E38[];

void func_8017EF4C(void *a0) {
    s32 v0;

    v0 = func_8017F4A8(a0, D_80185E34);
    if (v0 == 0) {
        v0 = func_8017F51C(a0, D_80185E38);
    }
    if (v0 != 0) {
        func_8017F478((u8 *)a0);
    }
}


extern s32 func_8012AD50(void*);
void func_8017EFA4(void) {
    ((void (*)(void))func_8012AD50)();
}


void func_8017EFC4(s32 a0) {
    extern void func_8012C194(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001CD9C(s32 a0, void *a1);
    extern void func_800233CC(void *a0, unsigned short a1);
    extern s32 rand(void);
    extern s32 func_8012AD50(void *a0);
    extern u32 D_801A7D0C[];
    extern s32 D_80185C90[];

    register s32 s2 __asm__("$18") = a0;
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    s32 s1;

    s1 = (*(s16 *)(s2 + 0x70) << 6) + (s32)&D_801A7D0C;
    v0 = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(v0));
    *(s32 *)(s2 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s2);
    } else {
        func_8001CD9C(s0, (void *)s1);
        func_800233CC((void *)s1, 0x80);
        *(s16 *)(s0 + 0x1E) = 0xC00;
        *(s16 *)(s0 + 0x10) = 0x400;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
        *(s32 *)s1 = D_80185C90[rand() & 7];
        *(s32 *)(s1 + 4) = 0;
        func_8012AD50((void *)s2);
    }
}


extern s32 func_8017F478(u8 *a0);
extern s32 func_8017F4A8(void *a0, void *a1);
extern s32 func_8017F51C(void *a0, void *a1);
extern u8 D_80185E3C[];
extern u8 D_80185E40[];

void func_8017F094(void *a0) {
    s32 v0;

    v0 = func_8017F4A8(a0, D_80185E3C);
    if (v0 == 0) {
        v0 = func_8017F51C(a0, D_80185E40);
    }
    if (v0 != 0) {
        func_8017F478((u8 *)a0);
    }
}


extern s32 func_8012AD50(void*);
void func_8017F0EC(void) {
    ((void (*)(void))func_8012AD50)();
}


#include "common.h"

extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void*);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(s32, void *);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern void func_8012C194(void);
extern u32 D_801A7D0C[];

void func_8017F10C(s32 a0) {
    register s32 s2 __asm__("$18") = a0;
    register s32 s0 __asm__("$16");
    s32 s1;
    s32 t;
    s32 u;
    s32 r;

    t = *(s16 *)(s2 + 0x70);
    u = (s32)(u8 *)D_801A7D0C;
    t <<= 6;
    s1 = t + u;
    r = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(r));
    *(s32 *)(s2 + 0x20) = r;

    if (r == 0) {
        func_8012CAE4((void *)s2);
    } else {
        func_8001CD9C(s0, (void *)s1);
        func_800233CC((void *)s1, 0x30);
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s32 *)(s1 + 0) = 0xFFFFFF;
        *(s32 *)(s1 + 4) = 0x10;
        func_8012BF4C((s32 *)s2, 0x96);
        func_8012AD50((void *)s2);
    }
}


extern void func_8017F2BC();
extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_8017F1CC(s32 a0) {
    s32 s0 = a0;
    func_8017F2BC();
    if (func_8012BEE8(s0) != 0) {
        func_8002D4C8(0xC14, 0);
        func_8012AD50((void *)s0);
    }
}


extern s32 func_8012AD50(void*);
extern void func_8017DCB8(s32 a0);
extern void func_8017F2BC();

void func_8017F214(s32 a0) {
    u8 *s0;
    u16 val16;

    s0 = *(u8 **)(a0 + 0x20);
    func_8017F2BC();

    val16 = *(u16 *)(s0 + 0x18);
    val16 += 0x80;
    *(u16 *)(s0 + 0x18) = val16;

    {
        s16 temp = (s16)val16;
        if (temp >= 0x4001) {
            *(u16 *)(s0 + 0x18) = 0x4000;
        }
    }

    *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x18);

    if (*(s16 *)(s0 + 0x18) == 0x4000) {
        func_8017DCB8(0x5);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}


extern void func_8017F2BC();
void func_8017F29C(void) {
    func_8017F2BC();
}


extern u32 D_801A7D0C[];
extern u16 D_800B99DA;

void func_8017F2BC(s16 *arg0) {
    u32 *dst = (u32 *)((u8 *)D_801A7D0C + ((s32)arg0[0x38] << 6));
    if (D_800B99DA & 1)
        *dst = 0xC0C0C0;
    else
        *dst = 0xFFFFFF;
}


extern s32 func_8012AD50(void*);
void func_8017F2FC(void) {
    ((void (*)(void))func_8012AD50)();
}


#include "common.h"

extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void*);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(s32, void *);
extern void func_8012C194(void);
extern u32 D_801A7D0C[];

void func_8017F31C(s32 a0) {
    register s32 s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    s32 s2;

    s2 = (*(s16 *)(s1 + 0x70) << 6) + (s32)&D_801A7D0C;
    v0 = ((s32 (*)(void))func_8012C194)();
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(v0));
    *(s32 *)(s1 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s1);
    } else {
        func_8001CD9C(s0, (void *)s2);
        func_800233CC((void *)s2, 0xA0);
        *(s16 *)(s0 + 0x2C) = 3;
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(s32 *)s2 = 0xFFFFFF;
        *(s32 *)(s2 + 4) = 0x10;
        func_8012AD50((void *)s1);
    }
}


extern s32 func_8012AD50(void *a0);

void func_8017F3D8(s32 *param_1) {
    s16 *s0 = (s16 *)param_1[8];
    s16 v = *(u16 *)((s32)s0 + 0x18) + 0x400;
    *(u16 *)((s32)s0 + 0x18) = v;
    if (v > 0x2000) {
        *(u16 *)((s32)s0 + 0x18) = 0x2000;
        func_8012AD50((void *)param_1);
    }
    *(u16 *)((s32)s0 + 0x1A) = *(u16 *)((s32)s0 + 0x18);
}


extern s32 func_8017F51C(void *a0, void *a1);
extern s32 func_8017F478(u8 *a0);
void func_8017F438(void *a0) {

    extern void *D_80185E44;
    if (func_8017F51C(a0, &D_80185E44)) {
        func_8017F478((u8 *)a0);
    }
}


extern u8 D_801A7D00[];
extern void func_8012C098(void *a0);

s32 func_8017F478(u8 *a0) {
    D_801A7D00[*(s16 *)(a0 + 0x70)] = 0;
    func_8012C098(a0);
}


s32 func_8017F4A8(void *a0, void *a1) {
    s32 p;
    s16 t;
    s16 u;
    s32 r;

    p = *(s32 *)((s32)a0 + 0x20);

    t = *(u16 *)(p + 0x1a) + *(u16 *)a1;
    *(s16 *)(p + 0x1a) = t;
    *(s16 *)(p + 0x18) = t;
    if (*(s16 *)(p + 0x1a) > 0x7000) {
        *(s16 *)(p + 0x1a) = 0x7000;
        *(s16 *)(p + 0x18) = 0x7000;
    }

    u = *(u16 *)(p + 0x1e) + *(u16 *)((u16 *)a1 + 1);
    *(s16 *)(p + 0x1e) = u;
    if ((s16)u < 0x1001) {
        r = 0;
    } else {
        *(s16 *)(p + 0x1e) = 0x1000;
        r = 1;
    }
    return r;
}


extern u32 D_801A7D0C[];
extern s32 func_8017F54C(void *a0, void *a1);

s32 func_8017F51C(void *arg0, void *arg1) {
    return func_8017F54C((void *)((u8 *)D_801A7D0C + (*(s16 *)((s32)arg0 + 0x70) << 6)), arg1);
}


extern void func_8017F5A4(void *a0, s32 a1);

s32 func_8017F54C(void *a0, void *a1) {
    func_8017F5A4(a0, *(s16 *)a1);
    func_8017F5A4((s8 *)a0 + 4, *((s16 *)a1 + 1));
    return (*(u32 *)a0 | *(u32 *)((s8 *)a0 + 4)) == 0;
}


void func_8017F5A4(void *a0, s32 a1) {
    u8 *p = a0;
    s32 v0;

    v0 = p[0] - a1;
    if (v0 < 0) {
        v0 = 0;
    }
    p[0] = v0;
    __asm__ __volatile__("" ::: "memory");
    v0 = p[1] - a1;
    if (v0 < 0) {
        v0 = 0;
    }
    p[1] = v0;
    __asm__ __volatile__("" ::: "memory");
    v0 = p[2] - a1;
    if (v0 < 0) {
        v0 = 0;
    }
    p[2] = v0;
}


extern s32 func_8012C588(s32 a0, s32 a1);

void func_8017F5FC(s16 param_1)
{
    s32 v0;
    v0 = func_8012C588(0x3AA, 0);
    if (v0 != 0) {
        *(s16 *)(v0 + 0xFC) = param_1;
    }
}


void func_8017F638(s32 arg0) {
    u8 sp10[8];
    s32 state;
    s32 found;
    s32 *ptr;
    s32 i;
    s32 obj;
    extern void (*D_80185E48[])(void *);
    extern void (*D_80185E54[])(void *);
    extern u16 D_800B99DA;
    extern u8 D_801A7D00[];
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_80015954(s32 a0, s32 a1);
    extern s32 func_8012C588(s32 a0, s32 a1);

    switch (*(s16 *)(arg0 + 0xFC)) {
    case 0:
        D_80185E48[*(u16 *)((s32)arg0 + 2)]((void *)arg0);
        if ((D_800B99DA & 7) == 0) {
            func_80015978(arg0 + 4, sp10);
            state = 2;
            ptr = (s32 *)sp10;
            for (i = 0, found = 1; i < 10; i++) {
                if (D_801A7D00[i] == 0) {
                    obj = func_8012C588(0x3A9, 0);
                    if (obj == 0) {
                        return;
                    }
                    func_80015954(ptr, obj + 4);
                    *(s16 *)((s32)obj + 0xFC) = state;
                    *(s16 *)((s32)obj + 0x70) = i;
                    D_801A7D00[i] = found;
                    return;
                }
            }
        }
        break;
    case 1:
        D_80185E54[*(u16 *)((s32)arg0 + 2)]((void *)arg0);
        break;
    }
}


extern s32 func_8012AD50(void*);
void func_8017F778(void) {
    ((void (*)(void))func_8012AD50)();
}


void func_8017F798(void *arg0) {
    extern u8 D_801A7F8C[];
    extern u8 D_801A7F8E[];
    extern u8 D_801A7F92[];
    extern u8 D_80185E60[];
    u8 *p;
    s32 i;
    s32 j;
    s32 color;

    func_80016714(&D_801A7F8C, 0x1C0);
    func_80015954((s32)D_80185E60, (s32)arg0 + 4);
    i = 0;
    color = 0x2020C0;
    p = D_801A7F8C + 0x14;
    j = 0;
    for (; i < 0x10; i++, j += 0x1C) {
        *(s16 *)(D_801A7F8E + j) = (i / 2) + 1;
        *(s16 *)(D_801A7F92 + j) = ((i / 2) * 0x200) + (((i & 1) * 3) * 15);
        *(s32 *)p = color;
        p += 0x1C;
    }
    func_8012AD50(arg0);
}


typedef struct {
    s16 state;   /* 0x00 */
    s16 timer;   /* 0x02 */
    s16 unk4;    /* 0x04 */
    s16 unk6;    /* 0x06 */
    s16 unk8;    /* 0x08 */
    s16 unkA;    /* 0x0A */
    s16 unkC;    /* 0x0C */
    s16 unkE;    /* 0x0E */
    s16 unk10;   /* 0x10 */
    s16 unk12;   /* 0x12 */
    s32 unk14;   /* 0x14 */
    u16 unk18;   /* 0x18 */
    u16 unk1A;   /* 0x1A */
} Blk1C;

extern void func_8017FA24(void *a0);
extern void func_8017FA50(s32 a0, void *s0);

void func_8017F860(s32 arg0) {
    extern u8 D_801A7F8C[];
    Blk1C *rec;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        rec = &((Blk1C *)D_801A7F8C)[i];
        rec->unk6 = (rec->unk6 - 0x2D) & 0xFFF;
        switch (rec->state) {
        case 0:
            if (rec->timer != 0) {
                rec->timer--;
                if (rec->timer == 0) {
                    rec->unk4 = -0x155;
                    rec->state++;
                }
            }
            break;
        case 1:
            rec->unkC += 0x100;
            if (rec->unkC > 0x1000) {
                rec->unkC = 0x1000;
            }
            rec->unkE = rec->unk10 = rec->unkC;
            func_8017FA50(arg0, rec);
            if (rec->unkC == 0x1000) {
                rec->timer = 0x1E;
                rec->state++;
            }
            break;
        case 2:
            func_8017FA24(rec);
            func_8017FA50(arg0, rec);
            rec->timer--;
            if (rec->timer == -1) {
                rec->state++;
            }
            break;
        case 3:
            func_8017FA24(rec);
            func_8017FA50(arg0, rec);
            if (rec->unkC == 0) {
                rec->timer = 0;
                rec->state = 0;
            }
            break;
        }
    }
}


void func_8017FA24(void *a0) {
    extern s32 D_80185C70[];
    u16 idx;

    idx = *(u16 *)((s32)a0 + 0x18);
    *(u16 *)((s32)a0 + 0x18) = idx + 1;
    *(s32 *)((s32)a0 + 0x14) = D_80185C70[idx & 7];
}


extern void func_8017FA94();

void func_8017FA50(s32 a0, void *s0)
{
    s32 sp10[2];

    func_80015978(a0 + 4, sp10);
    func_8017FA94((s8 *)s0 + 0xC, (s8 *)s0 + 4, sp10, (s8 *)s0 + 0x14);
}



typedef struct { Blk8 m[4]; } Quad;

extern Blk8 D_80185E68;
extern Blk8 D_80185E70;
extern Blk8 D_80185E78;
extern Blk8 D_80185E80;

extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E30(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_80017738(void *a0, void *a1);

void func_8017FA94(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Quad quad;
    u32 out[6];
    u8 buf[32];

    out[4] = 0x50000000;
    quad.m[0] = D_80185E68;
    quad.m[1] = D_80185E70;
    quad.m[2] = D_80185E78;
    quad.m[3] = D_80185E80;
    out[1] = *(u32 *)a3;
    out[0] = out[1];
    out[3] = 0;
    out[2] = 0;
    func_80017DC4((void *)a0, buf);
    func_80017E30((void *)a1, buf);
    func_80017E68((void *)a2, buf);
    func_80017738(&quad, buf);
}


extern s32 func_8012AD50(void*);
void func_8017FBB8(void) {
    ((void (*)(void))func_8012AD50)();
}


void func_8017FBD8(void *arg0)
{
    extern u8 D_801A814C[];
    extern u8 D_80185E88[];
    extern void func_8017FD54(void *a0);
    u8 *p;
    s32 i;

    func_80016714(D_801A814C, 0x1100);
    func_80015954((s32)D_80185E88, (s32)arg0 + 4);
    i = 0;
    p = D_801A814C;
    do {
        func_8017FD54(p);
        p += 0x44;
    } while (++i < 0x40);
    func_8012AD50(arg0);
}


extern void func_8017FD54(void *a0);
extern void func_8017FED8(u8 *a0);
extern void func_8017FF68(s32 a0, void *a1);
extern u8 D_801A814C[][0x44];

void func_8017FC54(u8 *arg0) {
    s32 i;
    u8 *p;
    s16 kind;
    s16 t;

    for (i = 0; i < 0x40; i++) {
        p = D_801A814C[i];
        kind = *(s16 *)p;
        switch (kind) {
        case 0:
            t = *(u16 *)(p + 2);
            t = t - 1;
            *(u16 *)(p + 2) = t;
            if (t == -1) {
                *(u16 *)(p + 2) = 0x14;
                *(u16 *)p = *(u16 *)p + 1;
            }
            break;
        case 1:
            t = *(u16 *)(p + 2);
            t = t - 1;
            *(u16 *)(p + 2) = t;
            if (t == -1) {
                func_8017FD54(p);
            } else {
                func_8017FF68(arg0, p);
                func_8017FED8(p);
            }
            break;
        }
    }
}


void func_8017FD54(void *param_1) {
    extern s32 D_80185C70[];
    extern u8 D_80185E90[];
    extern u8 D_80185EA0[];
    extern u8 D_80185EB0[];
    typedef struct { u16 w[4]; } Blk8017FD54;
    u16 idx;

    *(u16 *)((s32)param_1 + 0x0) = 0;
    *(u16 *)((s32)param_1 + 0x2) = (rand() & 7) + 1;
    *(u16 *)((s32)param_1 + 0xC) = -((rand() & 3) * 113);
    *(u16 *)((s32)param_1 + 0xE) =
        ((rand() & 3) << 10) +
        ((rand() & 3) * 284) +
        ((rand() & 3) * 56);

    idx = *(u16 *)((s32)param_1 + 0x4);
    *(u16 *)((s32)param_1 + 0x4) = idx + 1;
    *(s32 *)((s32)param_1 + 0x8) = D_80185C70[idx & 7];

    func_800134FC(*(s16 *)((s32)param_1 + 0xC), (void *)D_80185E90, (void *)((s32)param_1 + 0x1C));
    func_8001382C(*(s16 *)((s32)param_1 + 0xE), (void *)((s32)param_1 + 0x1C), (void *)((s32)param_1 + 0x1C));

    func_800134FC(*(s16 *)((s32)param_1 + 0xC), (void *)D_80185EA0, (void *)((s32)param_1 + 0x2C));
    func_8001382C(*(s16 *)((s32)param_1 + 0xE), (void *)((s32)param_1 + 0x2C), (void *)((s32)param_1 + 0x2C));

    *(Blk8017FD54 *)((s8 *)param_1 + 0x3C) = *(Blk8017FD54 *)D_80185EB0;

    *(u16 *)((s32)param_1 + 0x16) = 0x1000;
    if (rand() & 1) {
        *(u16 *)((s32)param_1 + 0x14) = 0x400;
        *(u16 *)((s32)param_1 + 0x18) = 0x7000;
    } else {
        *(u16 *)((s32)param_1 + 0x18) = 0x1000;
        *(u16 *)((s32)param_1 + 0x14) = 0x1000;
    }
}




void func_8017FED8(u8 *a0) {
    s32 v0, v1;
    s32 stack_vals[3];

    v0 = *(s32 *)(a0 + 0x1C);
    v1 = *(s32 *)(a0 + 0x2C);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x1C) = v0;
    stack_vals[0] = v0;

    v0 = *(s32 *)(a0 + 0x20);
    v1 = *(s32 *)(a0 + 0x30);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x20) = v0;
    stack_vals[1] = v0;

    v0 = *(s32 *)(a0 + 0x24);
    v1 = *(s32 *)(a0 + 0x34);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x24) = v0;
    stack_vals[2] = v0;

    *(u16 *)(a0 + 0x3C) += *(u16 *)((u8 *)stack_vals + 2);
    *(u16 *)(a0 + 0x3E) += *(u16 *)((u8 *)stack_vals + 6);
    *(u16 *)(a0 + 0x40) += *(u16 *)((u8 *)stack_vals + 10);
}


extern void func_80015978(s32 a0, s32 *a1);

void func_8017FF68(s32 a0, void *a1) {
    s32 sp18[2];

    func_80015978(a0 + 4, sp18);
    func_8017FFB4((s8 *)a1 + 0x14, (s8 *)a1 + 0xC, (void *)sp18, (s8 *)a1 + 8, (s8 *)a1 + 0x3C);
}



/* Local layout typedefs for standalone match_one compilation.
 * SVECTOR: {s16 vx,vy,vz,pad;} 8 bytes, align 2.
 * MATRIX_L: {s16 m[3][3]; s32 t[3];} 0x20 bytes, align 4.
 * Prim_L:  {SVECTOR v[4]; s16 k30..k3e (8 shorts); u32 bcast; s32 tag; u8 code; u8 pad[7];} 0x40 bytes.
 * Byte-identical sibling of func_8018DA64 (ov_SC04_011, banked): only the
 * D_* data-symbol addresses differ (D_80194DD0/DD8/DE0/DE8 -> D_80185EB8/
 * ED4/EDC/EE4).
 */
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_80182800;
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_80182800;
typedef struct {
    SVECTOR_80182800 v[4];             /* 0x00 */
    s32 k30, k34, k38, k3c;            /* 0x20 */
    u32 bcast;                         /* 0x30 */
    s32 tag;                           /* 0x34 */
    u8  code;                          /* 0x38 */
    u8  pad39[7];                      /* -> 0x40 */
} Prim_80182800;

extern SVECTOR_80182800 D_80185EB8;
extern SVECTOR_80182800 D_80185EC0;
extern SVECTOR_80182800 D_80185EC8;
extern SVECTOR_80182800 D_80185ED0;

extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E30(void*, void*);
extern void func_80016EF8(void *a0, void *a1);

void func_8017FFB4(void *a0, void *a1, SVECTOR_80182800 *a2, s32 *a3, SVECTOR_80182800 *a4) {
    Prim_80182800 prim;
    MATRIX_80182800 mtx;

    prim.tag = 0x50000000;
    prim.code = 0x9B;

    prim.v[0] = D_80185EB8;
    prim.v[1] = D_80185EC0;
    prim.v[2] = D_80185EC8;
    prim.v[3] = D_80185ED0;

    {
        register s32 rK30 __asm__("$9") = 0x010009C0;   /* $t1 */
        register s32 rK34 __asm__("$8") = 0x010009DF;   /* $t0 */
        register s32 rK38 __asm__("$6") = 0x011F09C0;   /* $a2 */
        register s32 rK3c __asm__("$3") = 0x011F09DF;   /* $v1 */

        prim.bcast = *(u32 *)a3;

        prim.k30 = rK30;
        prim.k34 = rK34;
        prim.k38 = rK38;
        prim.k3c = rK3c;
    }

    func_80017DC4(a0, &mtx);
    ((s32 (*)(void *, void *))func_80017E30)(a1, &mtx);

    mtx.t[0] = a2->vx + a4->vx;
    mtx.t[1] = a2->vy + a4->vy;
    mtx.t[2] = a2->vz + a4->vz;

    func_80016EF8(&prim, &mtx);
}


extern s32 func_80029178(s32 a0);
extern s32 func_8002AE60(void);
extern s32 func_80014C54(s32 a0, s32 a1, s32 a2);
extern s32 func_800CF8B4();
extern void func_800D1724(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_80180138(short *a0) {

    extern void (*D_801859D0)(void *);
    extern void (*D_80185ED8[])(void *);
    extern void (*D_80185EFC[])(void *);
    extern void (*D_80185F10[])(void *);
    extern void (*D_80185F28[])(void *);
    extern void (*D_80185F34[])(void *);

    switch (*(s16 *)(a0 + 0x38)) {
    case 0:
        D_80185ED8[*(u16 *)(a0 + 1)](a0);
        break;
    case 1:
        D_80185EFC[*(u16 *)(a0 + 1)](a0);
        break;
    case 2:
        if (func_80029178(0x123) & 0xFF) {
            if (((short (*)(void))func_8002AE60)() << 16 == 0) {
                if ((func_80014C54(0, 0, 0x800) << 16 != 0) ||
                    (func_80014C54(0, 0, 0x40) << 16 != 0)) {
                    if (func_800CF8B4() != 0) {
                        func_800D1724((s32)&D_801859D0);
                    }
                }
            }
        }
        D_80185F10[*(u16 *)(a0 + 1)](a0);
        break;
    case 3:
        D_80185F28[*(u16 *)(a0 + 1)](a0);
        break;
    case 4:
        D_80185F34[*(u16 *)(a0 + 1)](a0);
        break;
    }

    if ((*(u16 *)a0 != 0) && (*(s32 *)(a0 + 0x10) != 0)) {
        func_8012B2CC((s32)a0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern s16 D_801A52E4;
extern s16 D_801A924C;

void func_801802CC(s32 a0) {
    s32 v0;
    s32 s0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    s0 = v0;
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
    } else {
        func_8001C214(s0, (s32)&D_801A52E4);
        func_8001D0E8(s0, 0x7FFF, 0x7FFF);
        *(s32 *)(s0 + 0x80) = (s32)&D_801A924C;
        *(s16 *)(s0 + 0x1C) = 0x600;
        *(s16 *)(s0 + 0x1A) = 0x600;
        *(s16 *)(s0 + 0x18) = 0x600;
        *(s32 *)(s0 + 0x04) |= 0x80000000;
        *(u16 *)(s0 + 0x2C) |= 0x90;
        func_8012AD50((void *)a0);
    }
}


extern void func_80180674(s32, s16);

void func_80180378(void *a0) {
    s32 *s0 = *(s32 **)((s32)a0 + 0x20);
    if (func_8017DCC8() == 6) {
        *(u16 *)((s32)s0 + 0x12) = 0x400;
        *(s32 *)((s32)s0 + 4) &= 0x7FFFFFFF;
        ((void (*)(void *, s32))func_80180674)(a0, 0x80);
        func_8012AD50(a0);
    }
}


void func_801803E8(s32 *a0) {
    if (func_8017DCC8() == 7) {
        func_8012BF4C(a0, 30);
        func_8012AD50(a0);
    }
}


void func_8018042C(s32 a0) {
    extern s32 D_801151D4;
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_8012AD50(void *a0);
    s32 p;
    s32 v0;

    p = D_801151D4;
    v0 = *(s32 *)(p + 0x10);
    v0 -= 3;
    *(s32 *)(p + 0x10) = v0;
    *(s32 *)(p + 0x14) = v0;
    if (func_8012BEE8(a0) != 0) {
        func_8012AD50((void *)a0);
    }
}


void func_80180480(s32 a0) {
    extern s16 D_800B9AAC[];
    extern s16 D_800B9B00;
    extern s32 D_801151D4;
    extern s32 func_8012E544(s32 a0);
    extern void func_8012C098(void *a0);
    extern void func_8012BF4C(s32 *a0, s32 a1);
    extern s32 func_8013D13C(void);
    extern s32 func_8012AD50(void *a0);
    register s32 p __asm__("$3");
    s32 v0;

    p = D_801151D4;
    v0 = *(s32 *)(p + 0x10);
    v0 = v0 - 3;
    *(s32 *)(p + 0x10) = v0;
    *(s32 *)(p + 0x14) = v0;
    if (((s32 (*)(s32))func_8013D13C)(10) == 0) {
        (*(s16 *)&D_800B9AAC) = 0x7FFF;
        D_800B9B00 = 0x7FFF;
        func_8013C938();
        v0 = func_8012E544(0x397);
        if (v0 != 0) {
            func_8012C098((void *)v0);
        }
        v0 = func_8012E544(0x395);
        if (v0 != 0) {
            func_8012C098((void *)v0);
        }
        v0 = func_8012E544(0x396);
        if (v0 != 0) {
            func_8012C098((void *)v0);
        }
        v0 = func_8012E544(0x398);
        if (v0 != 0) {
            func_8012C098((void *)v0);
        }
        func_8012BF4C((s32 *)a0, 0x1E);
        func_8012AD50((void *)a0);
    }
}


extern s32 func_8012AD50(void * arg0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017DCB8(s32 a0);

void func_80180558(s32 a0) {
    if (func_8012BEE8(a0) != 0) {
        func_8017DCB8(0x8);
        ((void (*)(s32))func_8012AD50)(a0);
    }
}









extern void func_80180694(s32 a0);
extern s32 func_8017DCC8(void);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80180598(s32 a0) {
    func_80180694(a0);
    if (func_8017DCC8() == 9) {
        func_8012BF4C((s32 *)a0, 0x1E);
        func_8012AD50((void *)a0);
    }
}


void func_801805E4(s32 arg0) {
    extern void func_80180694(s32 a0);
    register s32 s0 __asm__("$16") = arg0;
    s32 v0;

    func_80180694(arg0);
    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        func_80180A50(s0);
        func_8012AD50((void *)s0);
    }
}


extern void func_80180694(s32 a0);
extern s32 func_80180A98(s32 a0);
extern void func_8017DCB8(s32 a0);
extern void func_8012C098(void *a0);

void func_8018062C(s32 a0) {
    func_80180694(a0);
    if (func_80180A98(a0) != 0) {
        func_8017DCB8(0xA);
        func_8012C098((void *)a0);
    }
}


extern s16 D_801A9250;
extern s16 D_801A924E;
extern s16 D_801A924C;

void func_80180674(s32 a0, s16 a1) {
    D_801A9250 = a1;
    D_801A924E = a1;
    D_801A924C = a1;
}


extern s16 D_801A924C;
extern s16 D_801A924E;
extern s16 D_801A9250;

void func_80180694(s32 _arg0)
{
    s16 *p = &D_801A924C;
    *p += -8;
    if (*p < -0xFF) {
        *p = -0xFF;
    }
    D_801A9250 = *p;
    D_801A924E = *p;
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern s32 D_8019D52C;
extern s32 D_801A9254;

void func_801806E0(void *a0) {
    s32 s1;
    s32 s0;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    s0 = v0;
    s1 = (s32)a0;
    *(s32 *)((s8 *)s1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)s1);
    } else {
        __asm__ __volatile__("");
        func_8001C810(s0, (s32)&D_8019D52C);
        func_8001D0E8(s0, 0x7FFF, 0x7FFF);
        *(u16 *)((s8 *)s0 + 0x18) = *(u16 *)((s8 *)s0 + 0x1A) = *(u16 *)((s8 *)s0 + 0x1C) = 0x600;
        *(s32 *)((s8 *)s0 + 0x80) = (s32)&D_801A9254;
        *(s32 *)((s8 *)s0 + 0x4) |= 0xC0000000;
        *(u16 *)((s8 *)s0 + 0x2C) |= 0x30;
        func_8012AD50((void *)s1);
    }
}


extern s32 func_8017DCC8(void);
extern s32 func_8012AD50(void *a0);

extern u8 D_801A9260;
extern u8 D_801A9261;
extern u8 D_801A9262;
extern u8 D_801A9270;
extern u8 D_801A9272;
extern u8 D_801A9282;
extern u8 D_801A9290;

void func_8018078C(void *a0) {
    s32 *s0 = *(s32 **)((s32)a0 + 0x20);
    if (func_8017DCC8() == 6) {
        *(s32 *)((s32)s0 + 4) &= 0x7FFFFFFF;
        func_8012AD50(a0);
        D_801A9261 = 0xFF;
        D_801A9282 = 0xFF;
        D_801A9290 = 0xFF;
        D_801A9261 = 0xFF;
        D_801A9272 = 0xFF;
        D_801A9270 = 0xFF;
        D_801A9261 = 0xFF;
        D_801A9262 = 0xFF;
        D_801A9260 = 0xFF;
    }
}


extern s32 func_8017DCC8(void);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80180834(s32 arg0) {
    extern s32 func_80180944(s32 a0);
    /* §176-B2: pin the SHORT-LIVED interloper out of the way, not the contested
       pointer.  local-alloc's qty_compare gives the halfword temp (R=4, L=3 ->
       pri 26666) priority over the 0x20 pointer (R=3, L=8 -> pri 3750), so
       first-fit hands the halfword $v0 and the pointer $v1 -- the exact inverse
       of the target.  Pinning the halfword to $v1 frees $v0 for the pointer. */
    register s32 v1 __asm__("$3");
    register s32 s0 __asm__("$16") = arg0;
    s32 v0;

    func_80180944(arg0);
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x12);
    v1 += 0x10;
    *(u16 *)(v0 + 0x12) = v1;
    if (func_8017DCC8() == 9) {
        func_8012BF4C((s32 *)s0, 0x1E);
        func_8012AD50((void *)s0);
    }
}


void func_80180894(s32 arg0) {
    register s32 s0 __asm__("$16") = arg0;
    s32 v0, v1;
    func_80180944(arg0);
    v1 = *(s32 *)(s0 + 0x20);
    v0 = *(u16 *)(v1 + 0x12);
    v0 += 0x10;
    *(u16 *)(v1 + 0x12) = v0;
    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        func_80180A50(s0);
        func_8012AD50((void *)s0);
    }
}


extern s32 func_80180A98(s32 a0);
extern void func_8012C098(void *a0);

void func_801808F0(s32 arg0) {
    extern s32 func_80180944(s32 a0);
    register s32 s0 __asm__("$16") = arg0;
    s32 v1;

    func_80180944(s0);
    v1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(v1 + 0x12) += 0x10;
    if (func_80180A98(s0) != 0) {
        func_8012C098((void *)s0);
    }
}





void func_80180944(s32 param_1)
{
    extern s32 rand(void);
    extern s32 D_801A9254;
    extern s32 D_801A9258;
    extern s32 D_801A925C;
    extern s32 D_801A9264;
    extern s32 D_801A9268;
    extern s32 D_801A926C;
    extern s32 D_801A9274;
    extern s32 D_801A9278;
    extern s32 D_801A927C;
    SV4_L_8017C294 vec;   /* sp+0x10 */
    MTX_L_8017C294 mtx;   /* sp+0x18 */
    s32 prim;
    s32 mode;
    s32 code;
    s32 hi;
    s32 val;

    if ((rand() & 0xF) != 0) {
        mode = 0x40000000;
    } else {
        mode = 0x50000000;
    }
    prim = *(s32 *)(param_1 + 0x20);
    code = *(s32 *)(prim + 4) & 0xCFFFFFFF;
    hi = 0x40000000;
    *(s32 *)(prim + 4) = code | (mode | hi);
    val = *(u16 *)(param_1 + 0x108) + 0x80;
    *(u16 *)(param_1 + 0x108) = val;
    vec.a = val;
    val = *(u16 *)(param_1 + 0x10A) + 0x100;
    *(u16 *)(param_1 + 0x10A) = val;
    vec.b = val;
    vec.c = 0;
    RotMatrixYXZ(&vec, &mtx);
    vec.b = 0;
    vec.a = 0;
    vec.c = 0x200;
    ApplyMatrixSV(&mtx, &vec, &vec);
    D_801A9274 = vec.a;
    D_801A9264 = vec.a;
    D_801A9254 = vec.a;
    D_801A9278 = vec.b;
    D_801A9268 = vec.b;
    D_801A9258 = vec.b;
    D_801A927C = vec.c;
    D_801A926C = vec.c;
    D_801A925C = vec.c;
}


extern void func_800159E4(s32 a0, s32 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);

void func_80180A50(int param_1)
{
    ((void (*)(int, int))func_800159E4)(param_1 + 4, param_1 + 0x10);
    *(unsigned short *)(param_1 + 0x100) = *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x18);
    func_8012BF4C((s32 *)param_1, 0);
}


extern s16 D_80185F50;
extern s16 D_80185F52;
extern s16 D_80185F54;
extern s16 D_80185F56;

s32 func_80180A98(s32 param_1)
{
    int iVar1;
    int iVar3;
    short sVar2;

    iVar1 = *(int *)(param_1 + 0x1c);
    iVar3 = *(int *)(param_1 + 0x20);
    if (iVar1 < 0x3c) {
        *(short *)(param_1 + 6) =
             *(short *)(param_1 + 0x12) +
             (short)((((int)D_80185F50 - (int)*(short *)(param_1 + 0x12)) * iVar1) / 0x3c);
        *(short *)(param_1 + 10) =
             *(short *)(param_1 + 0x16) +
             (short)((((int)D_80185F52 - (int)*(short *)(param_1 + 0x16)) * *(int *)(param_1 + 0x1c)) / 0x3c);
        *(short *)(param_1 + 0xe) =
             *(short *)(param_1 + 0x1a) +
             (short)((((int)D_80185F54 - (int)*(short *)(param_1 + 0x1a)) * *(int *)(param_1 + 0x1c)) / 0x3c);
        sVar2 = *(short *)(param_1 + 0x100) +
                (short)((((int)D_80185F56 - (int)*(short *)(param_1 + 0x100)) * *(int *)(param_1 + 0x1c)) / 0x3c);
        *(short *)(iVar3 + 0x1c) = sVar2;
        *(short *)(iVar3 + 0x1a) = sVar2;
        *(short *)(iVar3 + 0x18) = sVar2;
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
        return 0;
    }
    return 1;
}


extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern u8 D_8019F5EC;
extern u8 D_8019F8F4;
extern u8 D_8019FBF4;
extern u8 D_8019F8EC;
extern void (*D_80185F58[])(void);
extern u16 D_80185F88;
extern u16 D_80185F8A;
extern u16 D_80185F8C;
extern void func_8012C1B8(void);

void func_80180BEC(void *param_1) {
    s32 v0;
    s32 s0;

    func_801325B8((s32)&D_8019F5EC, (s32)&D_8019F8F4, (s32)&D_8019FBF4, 0, 0);
    v0 = ((s32 (*)(void))func_8012C1B8)();
    s0 = v0;
    *(s32 *)((s8 *)param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(s0, (s32)&D_8019F8EC);
        func_8001D0E8(s0, 0x7FFF, 0x7FFF);
        *(s32 *)((s8 *)s0 + 0x80) = (s32)&D_80185F58;
        *(s32 *)((s8 *)s0 + 0x04) |= 0xD0000000;
        *(u16 *)((s8 *)s0 + 0x2C) |= 0xB0;
        D_80185F8C = 0;
        D_80185F8A = 0;
        D_80185F88 = 0;
        *(s16 *)((s8 *)s0 + 0x1C) = 0;
        *(s16 *)((s8 *)s0 + 0x1A) = 0;
        *(s16 *)((s8 *)s0 + 0x18) = 0;
        func_8012AD50(param_1);
    }
}


extern s32 func_8017DCC8(void);
extern s32 func_8012AD50(void *a0);

void func_80180CD4(void *a0) {
    s32 *s0 = *(s32 **)((s32)a0 + 0x20);
    if (func_8017DCC8() == 8) {
        *(s32 *)((s32)s0 + 4) &= 0x7FFFFFFF;
        func_8012AD50(a0);
    }
}









extern void func_80181204(A801593E4 *a0);
extern void func_80181224(void);
extern void func_801811C8(s32 a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80180D30(A801593E4 *a0) {
    u8 *s1;
    u16 w;

    s1 = *(u8 **)((u8 *)a0 + 0x20);
    func_80181204(a0);
    ((void (*)(A801593E4 *))func_80181224)(a0);

    w = *(u16 *)(s1 + 0x1A);
    w = w + 0x10;
    *(u16 *)(s1 + 0x1A) = w;
    if ((s16)w >= 0x24A) {
        *(u16 *)(s1 + 0x1A) = 0x249;
    }

    func_801811C8((s32)a0);
    if (*(s16 *)(s1 + 0x1A) == 0x249) {
        *(u16 *)((u8 *)a0 + 0xFC) = 0;
        func_8012BF4C((s32 *)a0, 0x5A);
        func_8012AD50((void *)a0);
    }
}



extern void func_80181204(A801593E4 *a0);
extern void func_80181224(void);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_80180DC4(A801593E4 *a0) {
    void *s1 = *(void **)((u8 *)a0 + 0x20);
    func_80181204(a0);
    ((void (*)(A801593E4 *))func_80181224)(a0);
    if (func_8012BEE8((s32)a0) != 0) {
        if (*(s16 *)((u8 *)a0 + 0xFC) != 0) {
            if (*(s16 *)((u8 *)s1 + 0x12) >= 0x400) {
                *(s16 *)((u8 *)s1 + 0x12) = 0x400;
                *(s16 *)((u8 *)a0 + 0xFC) = 0;
                func_8012AD50((void *)a0);
            }
        } else {
            if (*(s16 *)((u8 *)s1 + 0x12) < 0x400) {
                *(s16 *)((u8 *)a0 + 0xFC) = 1;
            }
        }
    }
}


#include "common.h"

extern void func_801811C8(s32 a0);
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_801810F8(void *a0);
extern void func_8017DCB8(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_801151D4;
extern u8 D_8019F5EC;
extern u8 D_8019F8F4;
extern u8 D_8019FBF4;
extern u8  D_801A9287;
extern s32 D_801A9288;
extern u8  D_801A928C;
extern u8  D_801A928D;
extern u8  D_801A928E;
extern u8  D_801A928F;
extern u8  D_801A9290;
extern s16 D_801A9292;
extern u8  D_801A9294;
extern u8  D_801A9295;
extern s16 D_801A9296;
extern s16 D_801A9298;
extern s16 D_801A929A;
extern u8  D_801A929F;
extern s32 D_801A92A0;
extern u8  D_801A92A4;
extern u8  D_801A92A5;
extern u8  D_801A92A6;
extern u8  D_801A92A7;
extern s16 D_801A92A8;
extern s16 D_801A92AA;
extern u8  D_801A92AC;
extern u8  D_801A92AD;
extern s16 D_801A92AE;
extern s16 D_801A92B0;
extern s16 D_801A92B2;

void func_80180E68(s32 a0) {
    s32 obj;
    s32 ws;
    s32 v;
    s16 t;

    obj = *(s32 *)(a0 + 0x20);

    v = *(s16 *)(a0 + 0xFC) * 286 / 60 + 0xD6;
    ws = D_801151D4;
    *(s32 *)(ws + 0x10) = v;
    *(s32 *)(ws + 0x14) = v;

    v = *(s16 *)(a0 + 0xFC) * 0x800 / 60 + 0x400;
    *(s16 *)(obj + 0x12) = v;
    *(s16 *)(obj + 0x1A) = *(s16 *)(a0 + 0xFC) * 1463 / 60 + 0x249;
    func_801811C8(a0);
    func_801325B8((s32)&D_8019F5EC, (s32)&D_8019F8F4, (s32)&D_8019FBF4, 0,
                  *(s16 *)(a0 + 0xFC) * 0x1000 / 60);

    t = *(u16 *)(a0 + 0xFC) + 1;
    *(u16 *)(a0 + 0xFC) = t;
    if (t >= 0x3D) {
        *(s16 *)(a0 + 0xFC) = 0x3C;
        *(s32 *)(obj + 4) |= 0x80000000;
        func_801810F8((void *)a0);
        func_8017DCB8(9);

        D_801A9287 = 5;
        D_801A9288 = 0xE10000BB;
        D_801A928F = 0x66;
        D_801A928E = 0x80;
        D_801A928D = 0x80;
        D_801A928C = 0x80;
        *(s16 *)&D_801A9290 = -0x80;
        D_801A9292 = -0x10;
        D_801A9294 = 0;
        D_801A9295 = 0xE0;
        D_801A9296 = 0x7FC0;
        D_801A9298 = 0x100;
        D_801A929A = 0x20;

        D_801A929F = 5;
        D_801A92A0 = 0xE10000BB;
        D_801A92A7 = 0x66;
        D_801A92A6 = 0x80;
        D_801A92A5 = 0x80;
        D_801A92A4 = 0x80;
        D_801A92A8 = -0x80;
        D_801A92AA = -0x10;
        D_801A92AC = 0;
        D_801A92AD = 0xE0;
        D_801A92AE = 0x7FC0;
        D_801A92B0 = 0x100;
        D_801A92B2 = 0x20;

        func_8012AD50((void *)a0);
    }
}


extern s32 func_8017DCC8(void);
extern void func_8012C098(void *a0);
extern short D_800B9A02;
extern u8 D_801A9284[];
extern u8 D_800A6620[];

void func_801810F8(void *a0) {
    s32 pad[2];
    u32 *node;
    u32 *ot;
    u32 tmp;
    register u8 *pbase __asm__("$8");
    register u32 lomask __asm__("$6");
    u8 *obase;

    if (func_8017DCC8() == 0xC) {
        func_8012C098(a0);
        return;
    }

    pbase = D_801A9284;
    lomask = 0xFFFFFF;

    node = (u32 *)(((*(u16 *)&D_800B9A02) * 24) + (s32)pbase);
    tmp = (*node & 0xFF000000) |
          (*(u32 *)&D_800A6620[(*(u16 *)&D_800B9A02) << 14] & lomask);
    obase = D_800A6620;
    __asm__ __volatile__("" :: "r"(obase));
    *node = tmp;

    ot = (u32 *)(((*(u16 *)&D_800B9A02) << 14) + (s32)obase);
    *ot = (*ot & 0xFF000000) |
          ((((*(u16 *)&D_800B9A02) * 24) + (s32)pbase) & lomask);
}


void func_801811C8(s32 arg0) {
    u16 temp;
    arg0 = *(s32 *)(arg0 + 0x20);
    temp = *(u16 *)(arg0 + 0x1A);
    *(s16 *)(arg0 + 0x1C) = temp;
    *(s16 *)(arg0 + 0x18) = (((s32)(s16)temp << 7) / 94);
}


void func_80181204(A801593E4 *a0) {
    S801593E4 *v1 = a0->p20;
    v1->field12 = (v1->field12 + 0x44) & 0xFFF;
}


extern u16 D_80185F88;
extern u16 D_80185F8A;
extern u16 D_80185F8C;

void func_80181224(void) {
    u16 *p = &D_80185F88;

    *p += 4;
    if ((s16)*p >= 0x100) {
        *p = 0xFF;
    }
    D_80185F8C = *p;
    D_80185F8A = *p;
}


extern s32 func_8017DCC8(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801813F8(void *a0, void *a1, void *a2);
extern s32 func_8012AD50(void *a0);
extern void (*D_80185FC0[])(void *);
extern u32 D_80185F90[];

void func_80181270(void *a0) {
    if (func_8017DCC8() == 0xA) {
        func_8002D4C8(0xC16, 0);
        func_801813F8(a0, &D_80185F90[0], &D_80185FC0[0]);
        func_801813F8(a0, &D_80185F90[2], &D_80185FC0[1]);
        func_801813F8(a0, &D_80185F90[4], &D_80185FC0[2]);
        func_8012AD50(a0);
    }
}


extern s32 func_8018140C(void);
extern void func_801813D0();
extern s32 func_80014D94();
extern s32 func_8002AE60(void);
extern void func_8017DCB8(s32 a0);
extern void func_800D1724(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_80181304(s32 a0)
{

    extern s32 D_801859D0;
    s32 s0;
    s32 v0;

    s0 = a0;
    v0 = func_8018140C();
    if (v0 != 0) {
        v0 = func_80014D94(0);
        if ((v0 & 0xF0) != 0) {
            v0 = func_8002AE60();
            if ((v0 << 16) != 0) {
                func_8017DCB8(0xB);
            } else {
                func_800D1724((s32)&D_801859D0);
            }
            func_8012AD50((void *)s0);
        }
    } else {
        func_801813D0(s0);
    }
}



extern s32 func_8017DCC8(void);
    extern void func_8012C098(void *a0);
    void func_80181394(void *a0) {
        if (((s32 (*)(s32))func_8017DCC8)((s32)a0) == 12) {
            ((void (*)(s32))func_8012C098)((s32)a0);
        }
    }


extern s32 func_8001739C(s32 *a0);
void func_801813D0(void) {

    extern s32 D_80185FA8;
    func_8001739C(&D_80185FA8);
}


void func_801813F8(void *a0, void *a1, void *a2) {
    u16 var;
    var = *(u16 *)((s32)a1 + 6);
    *(u16 *)((s32)a1 + 0) = 0;
    *(u16 *)((s32)a1 + 2) = var;
    *(s32 *)((s32)a2 + 0) = 0;
}


extern void (*D_80185FC0[])(void *);
extern u32 D_80185F90[];

s32 func_8018140C(void)
{
    s32 done;
    s32 i;
    s32 c;
    u16 *p;
    u8 *q;

    done = 0;
    for (i = 0; i < 3; i++) {
        p = (u16 *)((u32 *)D_80185F90 + i * 2);
        q = (u8 *)(D_80185FC0 + i);
        switch ((s16)p[0]) {
        case 0:
            p[1] -= 1;
            if ((s16)p[1] == -1) {
                p[0] = p[0] + 1;
            }
            break;
        case 1:
            c = *q;
            c += 0x10;
            if (c >= 0x100) {
                c = 0xFF;
                p[0] = p[0] + 1;
            }
            c = (c << 0x10) | (c << 8) | c;
            *(u32 *)q = c;
            break;
        case 2:
            c = *q;
            c -= 0x10;
            if (c < 0) {
                c = 0;
                p[0] = p[0] + 1;
            }
            c = (c << 0x10) | (c << 8) | c;
            *(u32 *)q = c;
            break;
        case 3:
            done += 1;
            break;
        }
    }
    return done == 3;
}


extern s32 func_8017DCC8(void);
extern void func_800167B8(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_80181534(void *a0) {
    if (func_8017DCC8() == 11) {
        func_800167B8(4);
        func_8012AD50(a0);
    }
}


extern u16 D_800AF7CE;
extern u8 D_800B9A11;
extern s32 D_800B9A18;
void func_80181578(void *arg0) {
    u16 v0;
    v0 = D_800AF7CE;
    D_800AF7CE = v0 + 4;
    if ((u16)(v0 + 4) < 0xFF) {
    } else {
        D_800AF7CE = 0xFF;
    }
    func_80016224((u8)D_800AF7CE, 0);
    if (D_800AF7CE == 0xFF) {
        func_8017DCB8(0xC);
        func_800167B8(0);
        D_800B9A11 = 1;
        func_800146B0(7);
        D_800B9A18 = 0;
        func_8012AD50(arg0);
    }
}


void func_80181620(void *a0) {
    extern s32 func_8012AD50(void *a0);
    if (func_80181F40() != 0) {
        *(u16 *)((s32)a0 + 0xFC) = 0;
        func_8012AD50(a0);
    }
}


extern s32 func_8012AD50(void *a0);
extern void func_801817D0();
extern s16 D_800B9A02;

void func_8018165C(void *a0) {
    u16 v;

    v = *(u16 *)((s32)a0 + 0xFC) + 4;
    *(u16 *)((s32)a0 + 0xFC) = v;
    if ((s16)v > 0x7f) {
        *(u16 *)((s32)a0 + 0xFC) = 0x80;
    }
    func_801817D0(*(u16 *)&D_800B9A02, *(s16 *)((s32)a0 + 0xFC));
    if (*(s16 *)((s32)a0 + 0xFC) == 0x80) {
        func_8012AD50(a0);
    }
}


extern s32 func_80014D94();
extern s32 func_8012AD50(void *a0);
extern void func_801817D0();
extern s16 D_800B9A02;

void func_801816D4(void *a0) {
    if ((func_80014D94(0) & 0xF0) != 0) {
        func_8012AD50(a0);
    }
    func_801817D0(*(u16 *)&D_800B9A02, *(s16 *)((s32)a0 + 0xFC));
}


void func_80181728(void *a0) {
    extern void func_801817D0();
    extern void func_800146B0(s32 a0);
    extern void func_800D1724(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern short D_800B9A02;
    extern s32 D_800B9A18;
    extern u8 D_80078E78[];
    extern void (*D_801859D0)(void *);
    u16 v;

    v = *(u16 *)((s32)a0 + 0xFC) - 4;
    *(u16 *)((s32)a0 + 0xFC) = v;
    if ((s16)v < 0) {
        *(u16 *)((s32)a0 + 0xFC) = 0;
    }
    func_801817D0(*(u16 *)&D_800B9A02, *(s16 *)((s32)a0 + 0xFC));
    if (*(s16 *)((s32)a0 + 0xFC) == 0) {
        func_800146B0(1);
        D_800B9A18 = 2;
        *(u32 *)&D_80078E78 = 1;
        func_800D1724((s32)&D_801859D0);
        func_8012AD50(a0);
    }
}


void func_801817C8(void) {
}

#include "common.h"

/* func_801817D0 (215 ins, ov_SC07_010) -- MATCH.
 * Builds six 24-byte "DR_MODE word + SPRT" packets (setlen 5, code 0x64, 256x256,
 * clut 0x7800) at &D_801A92B4[arg0*0x90 + {0,0x18,0x30,0x48,0x60,0x78}], then
 * addPrim()s all six into the OT word at &D_800A6620[arg0 << 14].
 *
 * Two non-obvious levers were needed (both byte-proven here):
 *  1. sched1 LUID order (sched.md S1 / rank rule 4.iii): the target materialises each
 *     SYMBOL ADDRESS *before* the index arithmetic (`lui/addiu D_801A92B4` then
 *     `sll/addu/sll`). A plain `&SYM[i + K]` expands the index first, so the la gets a
 *     HIGHER luid and sched (which runs BACKWARD) places it later. Fix: assign the bare
 *     symbol to a pointer local FIRST (`pbase`/`obase`) and form the base pointer as
 *     `(u8 *)(i + (s32)pbase)` -- the cast keeps the `addu $t3,$v1,$t4` operand order.
 *     The +K siblings must stay `&D_801A92B4[i + K]` (symbol+const is a CONST rtx, which
 *     is what produces `addiu $v0,$t4,K` + `addu`; going through the pointer local would
 *     collapse them to a single `addiu p0,4`).
 *  2. local-alloc qty order (regalloc.md K2/K3): the 0xFFFFFF mask lands in $t7 and the
 *     0xE100008E constant in $t6 -- the target has them the other way round. Pinning the
 *     mask to $14 (cookbook §17) fixes all 20 affected instructions; it is byte-clean
 *     (constant computed straight into the hard reg, no copy, no spills in this function).
 */

extern u8 D_801A92B4[];
extern u8 D_800A6620[];

void func_801817D0(s32 arg0, s32 arg1) {
    u8 *p0;
    u8 *p1;
    u8 *p2;
    u8 *p3;
    u8 *p4;
    u8 *p5;
    u32 *q0;
    u32 *q1;
    u32 *q2;
    u32 *q3;
    u32 *q4;
    u32 *q5;
    u32 *ot;
    register u32 m24 __asm__("$14");
    s32 i;
    u8 *pbase;
    u8 *obase;

    pbase = D_801A92B4;
    i = arg0 * 0x90;

    p0 = (u8 *)(i + (s32)pbase);
    p0[3] = 5;
    q0 = (u32 *)&D_801A92B4[i + 0x4];
    *q0 = 0xE100008A;
    p0[0xB] = 100;
    p0[0xA] = arg1;
    p0[9] = arg1;
    p0[8] = arg1;
    *(s16 *)(p0 + 0xC) = -0x140;
    *(s16 *)(p0 + 0xE) = -0xF0;
    p0[0x10] = 0;
    p0[0x11] = 0;
    *(s16 *)(p0 + 0x12) = 0x7800;
    *(s16 *)(p0 + 0x14) = 0x100;
    *(s16 *)(p0 + 0x16) = 0x100;

    p1 = &D_801A92B4[i + 0x18];
    p1[3] = 5;
    q1 = (u32 *)&D_801A92B4[i + 0x1C];
    *q1 = 0xE100008C;
    p1[0xB] = 100;
    p1[0xA] = arg1;
    p1[9] = arg1;
    p1[8] = arg1;
    *(s16 *)(p1 + 0xC) = -0x40;
    *(s16 *)(p1 + 0xE) = -0xF0;
    p1[0x10] = 0;
    p1[0x11] = 0;
    *(s16 *)(p1 + 0x12) = 0x7800;
    *(s16 *)(p1 + 0x14) = 0x100;
    *(s16 *)(p1 + 0x16) = 0x100;

    p2 = &D_801A92B4[i + 0x30];
    p2[3] = 5;
    q2 = (u32 *)&D_801A92B4[i + 0x34];
    *q2 = 0xE100008E;
    p2[0xB] = 100;
    p2[0xA] = arg1;
    p2[9] = arg1;
    p2[8] = arg1;
    *(s16 *)(p2 + 0xC) = 0xC0;
    *(s16 *)(p2 + 0xE) = -0xF0;
    p2[0x10] = 0;
    p2[0x11] = 0;
    *(s16 *)(p2 + 0x12) = 0x7800;
    *(s16 *)(p2 + 0x14) = 0x100;
    *(s16 *)(p2 + 0x16) = 0x100;

    p3 = &D_801A92B4[i + 0x48];
    p3[3] = 5;
    q3 = (u32 *)&D_801A92B4[i + 0x4C];
    *q3 = 0xE100009A;
    p3[0xB] = 100;
    p3[0xA] = arg1;
    p3[9] = arg1;
    p3[8] = arg1;
    *(s16 *)(p3 + 0xC) = -0x140;
    *(s16 *)(p3 + 0xE) = 0x10;
    p3[0x10] = 0;
    p3[0x11] = 0;
    *(s16 *)(p3 + 0x12) = 0x7800;
    *(s16 *)(p3 + 0x14) = 0x100;
    *(s16 *)(p3 + 0x16) = 0x100;

    p4 = &D_801A92B4[i + 0x60];
    p4[3] = 5;
    q4 = (u32 *)&D_801A92B4[i + 0x64];
    *q4 = 0xE100009C;
    p4[0xB] = 100;
    p4[0xA] = arg1;
    p4[9] = arg1;
    p4[8] = arg1;
    *(s16 *)(p4 + 0xC) = -0x40;
    *(s16 *)(p4 + 0xE) = 0x10;
    p4[0x10] = 0;
    p4[0x11] = 0;
    *(s16 *)(p4 + 0x12) = 0x7800;
    *(s16 *)(p4 + 0x14) = 0x100;
    *(s16 *)(p4 + 0x16) = 0x100;

    p5 = &D_801A92B4[i + 0x78];
    p5[3] = 5;
    q5 = (u32 *)&D_801A92B4[i + 0x7C];
    *q5 = 0xE100009E;
    p5[0xB] = 100;
    p5[0xA] = arg1;
    p5[9] = arg1;
    p5[8] = arg1;
    *(s16 *)(p5 + 0xC) = 0xC0;
    *(s16 *)(p5 + 0xE) = 0x10;
    p5[0x10] = 0;
    p5[0x11] = 0;
    *(s16 *)(p5 + 0x12) = 0x7800;
    *(s16 *)(p5 + 0x14) = 0x100;
    *(s16 *)(p5 + 0x16) = 0x100;

    obase = D_800A6620;
    ot = (u32 *)((arg0 << 14) + (s32)obase);
    m24 = 0xFFFFFF;

    *(u32 *)p0 = (*(u32 *)p0 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p0 & m24);
    *(u32 *)p1 = (*(u32 *)p1 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p1 & m24);
    *(u32 *)p2 = (*(u32 *)p2 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p2 & m24);
    *(u32 *)p3 = (*(u32 *)p3 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p3 & m24);
    *(u32 *)p4 = (*(u32 *)p4 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p4 & m24);
    *(u32 *)p5 = (*(u32 *)p5 & 0xFF000000) | (*ot & m24);
    *ot = (*ot & 0xFF000000) | ((u32)p5 & m24);
}


void func_80181B2C(void *a0) {
    extern void (*D_80186070[])(void);
    switch (*(s32 *)((s32)a0 + 0x34)) {
    case 0:
        D_80186070[*(u16 *)((s32)a0 + 0x2)]();
        break;
    case 1:
        func_80181E20(a0);
        break;
    }
}


extern s32 func_8001CC3C(s32, s32, s32, s32);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern u8 D_800D387C[];
extern void (*D_80185FD0)(void);

void func_80181B98(s32 param_1)
{
    s32 work;
    s32 val;
    s32 res;

    work = *(s32 *)(param_1 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(work, D_800D387C, 0, 0);
    *(u8 *)(work + 0x27) = 0x9C;
    *(s32 *)(work + 4) = *(s32 *)(work + 4) | 0x50000000;
    val = *(s32 *)(param_1 + 0x2C);
    *(u8 *)(work + 0x24) = 0xC0;
    *(u8 *)(work + 0x25) = 0x40;
    *(u8 *)(work + 0x26) = 0x20;
    res = ((8 - val) * 3) << 9;
    *(u16 *)(work + 0x1A) = res;
    *(u16 *)(work + 0x18) = res;
    func_80128EA8(work, param_1 + 0x24, &D_80185FD0);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


void func_80181C54(void *a0)
{
    extern s32 D_80186088;
    extern void func_800134FC(s32, void *, void *);
    extern void func_8001382C(s32, void *, void *);
    s32 *s = (s32 *)a0;
    s32 *tbl = &D_80186088;
    s16 sp10[8];
    register s32 v0 __asm__("$2");
    register s32 vT3 __asm__("$4");
    u16 v1;

    *tbl = -(*(s32 *)(s + 0xB) << 18);
    func_800134FC(*(s16 *)((s8 *)a0 + 0x30), tbl - 2, sp10);
    func_8001382C(*(s16 *)((s8 *)a0 + 0x32), sp10, sp10);

    v0 = *(s32 *)&sp10[0];
    v1 = *(u16 *)((s8 *)a0 + 2);
    *(s32 *)(s + 4) = v0;
    v0 = *(s32 *)&sp10[2];
    v1 = v1 + 1;
    *(s32 *)(s + 5) = v0;
    __asm__ __volatile__("" ::: "memory");
    vT3 = *(s32 *)&sp10[4];
    v0 = 8;
    *(s32 *)(s + 7) = v0;
    __asm__ __volatile__("" ::: "memory");
    *(u16 *)((s8 *)a0 + 2) = v1;
    *(s32 *)(s + 6) = vT3;
}


void func_80181CDC(void *a0) {
    extern void func_8012931C(void *a0);
    u16 t;
    if ((*(s32 *)((s32)a0 + 0x1C))-- == 0) {
        *(s32 *)((s32)a0 + 0x10) >>= 1;
        *(s32 *)((s32)a0 + 0x14) >>= 1;
        *(s32 *)((s32)a0 + 0x18) >>= 1;
        t = *(u16 *)((s32)a0 + 2) + 1;
        *(u16 *)((s32)a0 + 2) = t;
    } else {
        func_8012931C(a0);
    }
}


void func_80181D48(s32 a0) {
    u8 *s0;
    u8 v1;
    s16 v0;

    s0 = *(u8 **)(a0 + 0x20);
    func_8012931C();

    v0 = *(u8 *)(s0 + 0x24);
    v0 = v0 - 4;
    *(u8 *)(s0 + 0x24) = v0;
    if ((u8)v0 > 0xC0) {
        *(u8 *)(s0 + 0x24) = 0;
    }

    v1 = *(u8 *)(s0 + 0x24);
    if (v1 < *(u8 *)(s0 + 0x25)) {
        *(u8 *)(s0 + 0x25) = v1;
        v1 = *(u8 *)(s0 + 0x24);
    }
    if (v1 < *(u8 *)(s0 + 0x26)) {
        *(u8 *)(s0 + 0x26) = v1;
    }

    v0 = *(u16 *)(s0 + 0x18) + 0x100;
    *(u16 *)(s0 + 0x18) = v0;
    if ((s16)v0 >= 0x4001) {
        *(u16 *)(s0 + 0x18) = 0x4000;
    }

    *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x18);

    if (*(u8 *)(s0 + 0x24) == 0) {
        func_801292C8(a0);
    }
}




void func_80181E20(void *a0) {

    extern void (*D_80186090[])(void);
    D_80186090[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8001CC3C(s32, s32, s32, s32);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern u8 D_800D387C[];
extern u8 D_80186020[];

void func_80181E5C(s32 param_1)
{
    s32 work;

    work = *(s32 *)(param_1 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(work, D_800D387C, 0, 0);
    *(u8 *)(work + 0x27) = 0x9C;
    *(u16 *)(work + 0x1A) = 0x3000;
    *(u16 *)(work + 0x18) = 0x3000;
    *(u32 *)(work + 4) = *(u32 *)(work + 4) | 0x50000000;
    func_80128EA8(work, param_1 + 0x24, D_80186020);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);

void func_80181EEC(int param_1)
{
    int base;
    unsigned short *p;
    unsigned short val;

    base = *(int *)(param_1 + 0x20);
    p = (unsigned short *)(base + 0x1A);
    val = *p - 0x100;
    p[0] = val;
    p[-1] = val;
    if (func_80128ED8(base, (s32 *)(param_1 + 0x24)) != 0) {
        func_801292C8((u8 *)param_1);
    }
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_80181F40(void) {

    extern u8 D_800AF608[];
    func_8001ABBC(0, 0, D_800AF608, 0, 0);
}



