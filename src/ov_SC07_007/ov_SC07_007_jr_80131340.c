#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct { s32 w[8]; } Vec8;
typedef struct { s32 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s32 vx, vy, vz; } VECTOR;
typedef struct { s16 h[8]; } Buf;
typedef struct { char _b[8]; } M8;   /* size 8, alignment 1 -> unaligned copy */
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
extern void func_80029444(void);
extern void func_800D1754(void);
extern void func_8014ED28(s32 _arg0);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int func_801288E8(int arg0);
extern int func_80128940(int arg0);
extern void func_80010AE0(s32 a0);
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
extern void func_80129010(void);
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
extern void func_80129CF8(void);
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
extern void func_8012A2F4(void);
extern s16 D_80127080;
extern s16 D_801152C2;
extern void func_8012A304(s32 a0, s32 a1);
extern void func_8012A464(void);
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
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_8012A6D0(void* a0, void* a1);
extern s16 func_8012A79C(s16 *a0, s16 *a1);
extern s16 func_8012A758(void);
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
extern u16 D_801274E4[];
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
extern s32 func_8012D714(s32 param_1, u32 param_2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern s32 func_8012DB84(void);
extern s32 func_8012DE2C(s32 a0);
extern s32 func_8012DDA4(void);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
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
extern void func_80130D0C(s32 a0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
/* ==== end §8b carried decl layer ==== */


// @class: plumbing
// @stuck: none — MATCH (424/424). Verified TWICE: match_one 424/424 standalone AND 424/424
//   relocation-masked through the REAL src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c at the
//   func_80131340 slot (L1635) with every DEFINE_ macro expanded (cpp -> cc1 -> maspsx
//   --expand-div -> as, exit 0, zero `conflicting types`).
//
// ---------------------------------------------------------------------------------------
// THE TWO LEVERS THAT CRACKED IT (both byte-proven; do not "clean up"):
//
// (1) `case 0: case 1:` SHARE one block. jtbl_801D8144 (read from the sibling overlay data,
//     asm/ov_SC03_099/data/tail2.data.s @801BCE68) is
//       [0]=0x80131440 [1]=0x80131440 [2]=0x80131634 [3]=0x8013174C [4]=0x801318F4
//     — two entries point at the SAME block. That is the ONLY reason the shared block
//     re-tests `*(u8*)(a0+0xC2) == 0` to gate its vector-init half (gcc-2.7.2 has no VRP,
//     so the switch value is not propagated into the case body).
//
// (2) CROSS-JUMP POLARITY (§5a, the 4-instruction shortfall). The `lh 0x76` / E00-vs-C78
//     if-else appears TWICE (case 3's tail @801318DC and case 4 @80131944). Both arms must
//     be written `if (x <= 0) E00(a0,6); else C78(a0);` — the SAME polarity in BOTH sites.
//     Writing case 3 as the "natural" `if (x > 0) C78 else E00` compiles 4 ins SHORT: gcc
//     merges case 3's ENTIRE tail into case 4's (`j` straight to the shared `lh`).
//     Why (ground-truthed against tools/reference/gcc-2.7.2/jump.c):
//       - jump.c:1969 `find_cross_jump(insn, target, 2, ...)` pairs each `j Lend` with every
//         OTHER jump to Lend (the jump_chain) and merges BACKWARD while
//         `rtx_renumbered_equal_p` holds. The forward walk hits the LOWER address first, so
//         case 3 is always e1 (deleted/redirected) and case 4 is e2 (kept) — hence the
//         surviving .L80131954/.L80131964 bodies physically live in case 4.
//       - With the matching polarity, case 3's FIRST `j` is the E00 body -> it merges into
//         .L80131954, leaving `bgtz -> Lelse; j .L80131954; Lelse:`. Lelse now sits directly
//         after the `j`, so jump.c's conditional-jump-around-an-unconditional-jump transform
//         fires and INVERTS it to `blez -> .L80131954`; the C78 body then merges into
//         .L80131964, giving exactly `blez .L80131954 / j .L80131964`. The two sites are now
//         textually different (blez+j vs bgtz+fallthru), so find_cross_jump stops at the
//         branch and both `lh` blocks survive. That asymmetric-looking output is EMITTED BY
//         symmetric source — the inversion is what creates the asymmetry.
//       - With the opposite polarity in case 3, the C78 body merges FIRST, the inversion
//         fires the other way, and case 3 becomes byte-identical to case 4 -> fully merged.
//     NOTE: the §5a volatile-asm barrier is the WRONG tool here — it would also un-merge the
//     .L80131954/.L80131964 call bodies (+8 ins). The fix is polarity, not a barrier.
//
// OTHER BYTE-PROVEN KEYS:
//   - Two SEPARATE locals for the two func_80131CF4 results. Reusing one `temp` lets gcc
//     coalesce it into $a1 for the second call and emits an extra `move a1,v0` up at the
//     FIRST call site (+1 ins, whole-function cascade).
//   - The /3 store block: `*(s32*)(a0+0x14) = (-D_801C64EC)/3;` must come FIRST (before the
//     0x1C/0xC2 stores). Written after them, gcc will not hoist the D_801C64EC load above
//     `sw zero,0x1C($s0)` and the mult-latency slots fill differently (9 ins reordered).
//   - sp10/18/20/28 are four 8-byte, 2-byte-aligned vectors. `sp28 = sp20` is a DEAD
//     aggregate copy that gcc-2.7.2 KEEPS (no aggregate DSE) — it is load-bearing, not dead
//     code. align(2) < 4 is what makes the copies lwl/lwr + swl/swr (cf. the TU's own `M8`
//     align-1 idiom at L1614, used by func_801312D0 directly above this slot).
//   - Every vector field read is `lhu` -> the fields are u16. Contrast `lh 0xA($s0)`,
//     `lh 0x76($s0)`, `lh 0x12($v0)`, which are genuinely signed (s16 casts).
//   - `func_801319E0(a0)` gets a NOP delay slot, not `addu $a0,$s0,$zero`: cse-2.7.2 deletes
//     the redundant arg copy because $a0 still holds the param at the first call. Declaring
//     it 0-arg to "explain" the nop would be wrong (canonical is 1-arg) — just call it.
//   - `*(s32*)(a0+0x10) = *(s32*)(a0+0x10) * 15 / 16;` -> (x<<4)-x then the bgez/+0xF/sra-4
//     signed-div-by-16 fixup. `>>4` would drop the fixup.
//   - func_80131D68 is 2-arg here — (a0, D_801C64E8); a1 is reloaded from the global before
//     all 5 of its call sites (the value is NOT cached in a callee reg: gcc-2.7.2's cse is
//     extended-basic-block-local, so each join point reloads).
//
// DECL RECONCILE (§17a-1) — the TU declares these at FILE scope BEFORE this slot (L1635),
// so they are HARD `conflicting types` if redeclared differently. Sigs below are byte-copies
// of the canonical set; where the canonical return is `void` but the asm USES $v0, the read
// is done with a call-site cast (the codebase's own idiom, engine_core.h L17026) — which is
// codegen-neutral:
//   - func_8012CBF4 / func_8012CBA4 / func_8012CC64: canonical `void`, $v0 used -> cast.
//   - func_80131E00: canonical takes `struct S80131E00 *` -> declared K&R no-proto here
//     (compatible with the prototyped decl at L1250; params are promotion-safe: ptr + s32),
//     matching the TU's own precedent `extern void func_80131CA8();` at L1189.
//   - func_8012B23C / func_8012CC64 / func_8012CEB0 / func_8012DBD0 / func_8012CBF4 are
//     DEFINE_-instantiated ABOVE this slot — the decls here are exact-identical
//     redeclarations (legal C), not new sigs.
//   - func_80131CF4 is declared 2-arg `(int,int)`, mirroring func_801312D0's already-matched
//     block-scope decl at L1619 (the engine_core canonical 1-arg form is the stale one).

extern void func_801319E0(s32 a0);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012CC64(s32 a0, s32 a1);
extern int func_80131D68(int, int);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_80131E00();
extern void func_80131C78(s32 a0);
extern void func_80131CA8(int a0, int a1);

extern s32 D_801C64E8;
extern s32 D_801C64EC;

void func_80131340(s32 a0)
{
    /* 8-byte, align-2 vector: align < 4 is what makes the assignments unaligned
     * (lwl/lwr + swl/swr) block moves. Block-scope so the body stays self-contained
     * for the dedup_propagate lift (§28-#1) and cannot collide with the TU's `M8`. */
    struct V8 {
        u16 vx, vy, vz, pad;
    };
    extern struct V8 D_801833E8;
    /* BLOCK-scope, mirroring the already-matched func_801312D0's decl at TU L1619: the
     * later DEFINE_func_80131AC8() (TU L1964, AFTER this slot) redeclares func_80131CF4
     * with the stale 1-arg engine_core canonical. A file-scope `extern int
     * func_80131CF4(int,int);` here is a HARD `conflicting types` against it (cc1 rc=33,
     * measured); block-scope goes out of scope before that macro and compiles clean. */
    extern int func_80131CF4(int, int);

    struct V8 sp10;
    struct V8 sp18;
    struct V8 sp20;
    struct V8 sp28;
    s32 temp;
    s32 var_a1;

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_801319E0(a0);
        return;
    }

    temp = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x2E);
    if (temp != 0) {
        sp10.vz = 0;
        sp10.vx = 0;
        sp10.vy = temp;
    } else {
        sp10 = D_801833E8;
    }

    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        var_a1 = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x19);
        if (var_a1 == 0) {
            var_a1 = 0x50;
        }
        func_8012DBD0(a0, var_a1,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
    case 1:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        if (*(u8 *)(a0 + 0xC2) == 0) {
            *(u8 *)(a0 + 0xC2) = 1;
            sp18.vx = *(u16 *)(a0 + 0x3A);
            sp18.vy = *(u16 *)(a0 + 0x3E);
            sp18.vz = *(u16 *)(a0 + 0x42);
            sp20 = sp18;
            sp20.vx += sp10.vx;
            sp20.vy += sp10.vy;
            sp20.vz += sp10.vz;
            sp28 = sp20; /* load-bearing dead aggregate copy — gcc-2.7.2 has no aggregate DSE */
            func_8012CEB0((s32)&sp18, (s32)&sp20, 1);
            sp20.vx -= sp10.vx;
            sp20.vy -= sp10.vy;
            sp20.vz -= sp10.vz;
            *(u16 *)(a0 + 0x3A) = sp20.vx;
            *(u16 *)(a0 + 0x3E) = sp20.vy;
            *(u16 *)(a0 + 0x42) = sp20.vz;
            *(u16 *)(a0 + 0x6) = sp20.vx;
            *(u16 *)(a0 + 0xA) = sp20.vy;
            *(u16 *)(a0 + 0xE) = sp20.vz;
        }
        D_801C64E8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801C64E8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801C64E8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801C64E8 & 0x2000) {
            if (func_80131D68(a0, D_801C64E8) == 1) {
                return;
            }
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        } else if (D_801C64E8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 2:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        D_801C64EC = *(s32 *)(a0 + 0x14);
        D_801C64E8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801C64E8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801C64E8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801C64E8 & 0x2000) {
            if (func_80131D68(a0, D_801C64E8) == 1) {
                return;
            }
            func_80143B6C(a0, 1);
            /* MUST precede the 0x1C/0xC2 stores — see the header note on the /3 block. */
            *(s32 *)(a0 + 0x14) = (-D_801C64EC) / 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u8 *)(a0 + 0xC2) = 3;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        } else if (D_801C64E8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            D_801C64E8 = ((s32 (*)(s32))func_8012CBA4)(a0);
            if (D_801C64E8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (func_80131D68(a0, D_801C64E8) == 1) {
                return;
            }
            if (!(D_801C64E8 & 0x6000)) {
                func_80131E00(a0, 0xD);
                return;
            }
        } else {
            D_801C64E8 = ((s32 (*)(s32))func_8012CBF4)(a0);
            if (D_801C64E8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (D_801C64E8 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
                break;
            } else if (D_801C64E8 & 0x2000) {
                if (func_80131D68(a0, D_801C64E8) == 1) {
                    return;
                }
                *(u8 *)(a0 + 0xC3) |= 1;
            } else if (D_801C64E8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
        }
        if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
            func_80143B6C(a0, 1);
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(D_801C64E8 & 0x6000)) {
            func_80131E00(a0, 0xD);
            return;
        }
        /* polarity MUST match case 4's — see the cross-jump note in the header. */
        if (*(s16 *)(a0 + 0x76) <= 0) {
            func_80131E00(a0, 6);
        } else {
            func_80131C78(a0);
        }
        break;

    case 4:
        D_801C64E8 = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (D_801C64E8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801C64E8 & 0x2000) {
            if (func_80131D68(a0, D_801C64E8) == 1) {
                return;
            }
            if (*(s16 *)(a0 + 0x76) <= 0) {
                func_80131E00(a0, 6);
            } else {
                func_80131C78(a0);
            }
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
                func_80131E00(a0, 0xD);
                return;
            }
        }
        break;
    }

    func_80131CA8(a0, 0x2F);
}


DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80131A34);

DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131ac8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80131B14);

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131c78 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80131CA8);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80131CF4);

DEFINE_func_80131D68()  /* dedup: shared engine-core @0x80131d68 (src/shared) */





void func_80131E00(struct S80131E00 *a0, s32 a1) {

    extern void (*D_80183400[])(struct S80131E00 *a0);
    a0->field_B0 = a1;
    D_80183400[a1](a0);
}


DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131e38 (src/shared) */


DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131e7c (src/shared) */


void func_80131EE4(void) {
}



void func_80131EEC(void *a0) {

    extern void (*D_80183458[])(void);
    D_80183458[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F28(void *a0) {

    extern void (*D_801834A0[])(void);
    D_801834A0[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F64(void *a0) {

    extern void (*D_801834A8[])(void);
    D_801834A8[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FA0(void *a0) {

    extern void (*D_801834B0[])(void);
    D_801834B0[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FDC(void *a0) {

    extern void (*D_801834B8[])(void);
    D_801834B8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80132018);

void func_801320D0(void) {
}


// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_801320D8(int param_1)
{

    extern int D_80183460;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_80183460;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_80132144(int param_1)
{

    extern int D_80183470;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_80183470;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_801321B0(int param_1)
{

    extern int D_80183480;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_80183480;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_8013221C(int param_1)
{

    extern int D_80183490;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_80183490;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801325B8);

void func_8013277C(void) {
}

DEFINE_func_80132784()  /* dedup: shared engine-core @0x80132784 (src/shared) */


DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132dc4 (src/shared) */


DEFINE_func_80132E6C()  /* dedup: shared engine-core @0x80132e6c (src/shared) */


void func_80132EC4(void *a0, s16 a1) {
    while (*(s32 *)a0 != 0) {
        *(s16 *)((s32)a0 + 4) = a1;
        a0 = (void *)((s32)a0 + 8);
    }
}


DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132ef4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80132F40);

DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801330E0);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80133298);

DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339c (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH

extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {

    extern s32 D_801C6530;
    extern s32 D_801C6534[];
    extern int D_801C6538;
    if (a0 != 0) {
        (*(void * *)&D_801C6530) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_801C6534) = a1;
    D_801C6538 = a2;
}




extern void func_80136BC4(s32);

void func_8013373C(s16 arg0) {

    extern s32 D_801C6534[];
    extern s32 D_801C6530;
    s32 temp = D_801C6534[arg0];
    if (temp != 0) {
        D_801C6530 = temp;
        func_80136BC4(temp);
    }
}



typedef struct { u16 f0, f2, f4; s16 f6; } Box_80133784;


s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {

    extern s32 D_801C6530;
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_801834C0;
    extern Box_80133784 * D_801834C4;
    extern s16 D_801C653C;
    extern u16 D_801C6540;

    register s32 s1 __asm__("$17");
    s32 s2;
    register s16 s3 __asm__("$19");
    register s32 s4 __asm__("$20");
    register s16 a0v __asm__("$4");
    register s16 arg0s __asm__("$21");
    s32 dx, dy, dz;
    s32 r, ret;

    a0v = ((s16)arg0);
    s1 = 0;
    s3 = 0;
    s4 = 0;
    s2 = 0;
    arg0s = a0v;
    D_801834C0->f6 = -0x7FFF;
    D_801834C4->f6 = 0x7FFF;
    D_801834C0->f0 = ((Box_80133784 *)arg1)->f0;
    D_801834C0->f4 = ((Box_80133784 *)arg1)->f4;
    D_801834C4->f0 = ((Box_80133784 *)arg2)->f0;
    D_801834C4->f4 = ((Box_80133784 *)arg2)->f4;
    D_801C6540 = 0;
    D_801C653C = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));
        }
        D_801834C0->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_801834C4->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_801834C0->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_801834C4->f0 = D_801834C0->f0;
            D_801834C4->f2 = D_801834C0->f2 + 6;
            s2 = 1;
            D_801834C4->f4 = D_801834C0->f4;
        } else {
            D_801834C4->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");
        __asm__ __volatile__("");
        ret0 = func_80133AB0(arg0s, (s16)D_801834C0->f0, (s16)D_801834C0->f4, (*(s32*)&D_801C6530));
        __asm__("addu %0,%1,$zero" : "=r"(retc) : "r"(ret0));
        ret = retc;
        if (ret == 0) goto after;
        s4 |= ret;
        if (s2 != 0) goto after;
        {
            s16 oldc = s3;
            s3 = s3 + 1;
            if (oldc >= 5) break;
        }
    }

    D_801834C4->f0 = D_801834C0->f0;
    D_801834C4->f2 = D_801834C0->f2;
    s1 = 0x2000;
    D_801834C4->f4 = D_801834C0->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801C653C != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));
        t = D_801834C0->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_801834C4->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_801834C4->f0;
        ((Box_80133784 *)arg2)->f2 = D_801834C4->f2;
        ((Box_80133784 *)arg2)->f4 = D_801834C4->f4;
        ((Box_80133784 *)arg2)->f6 = D_801C6540;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801C6540;
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80133AB0);


s32 func_80133CD4(arg0, cmd, base, arr)
    s16 arg0;
    s16 *cmd;
    s16 *base;
    s32 *arr;
{
    typedef struct { s16 e[4]; } ElemK;

    extern u16 *D_801834C4;
    extern u16 *D_801834C0;
    extern s16 *D_801834CC;
    extern s16 *D_801834C8;
    extern s32 *D_801834D4;
    extern s32 *D_801834D8;
    extern u16 D_801C6540;
    extern u8  D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern u16 D_801152AE;
    extern u8  D_801152B0;
    extern s32 func_80134310();
    extern s32 func_8013435C();

    s16 *s3 = ((ElemK *)base)[cmd[1]].e;
    s32 s6 = arr[cmd[2]];
    s32 s0var, s1var;
    s32 s2a;
    s16 y;

    if (func_80134310(s3, D_801834C4, s6) >= 0)
        return 0;

    s1var = func_80134310(s3, D_801834C0, s6);
    if (s1var < 0)
        return 0;

    s0var = func_80134310(s3, D_801834CC, 0);
    {
        u16 *pac = D_801834C0;
        s16 *pb8 = D_801834CC;
        s16 *pb4 = D_801834C8;
        s32 neg = -s1var;
        pb4[0] = pac[0] + neg * pb8[0] / s0var;
        pb4[1] = pac[1] + neg * pb8[1] / s0var;
        pb4[2] = pac[2] + neg * pb8[2] / s0var;
        if (func_8013435C(((ElemK *)base)[cmd[3]].e, pb4, arr[cmd[4]], s3))
            return 0;
    }
    if (func_8013435C(((ElemK *)base)[cmd[5]].e, D_801834C8, arr[cmd[6]], s3))
        return 0;
    if (func_8013435C(((ElemK *)base)[cmd[7]].e, D_801834C8, arr[cmd[8]], s3))
        return 0;
    if (arg0 < 0) {
        if (func_8013435C(((ElemK *)base)[cmd[9]].e, D_801834C8, arr[cmd[10]], s3))
            return 0;
    }
    if (arg0 & 0x10) {
        if (*(u16 *)cmd & 0x100)
            return 0;
    }
    if (*(u16 *)cmd & 0x200) {
        D_801C6540 = *(u16 *)cmd;
        return 0;
    }

    {
        s32 ret = func_80134310(s3, D_801834C4, s6);
        s32 *pc0;
        s32 *pc4;
        u16 *pb0;
        s32 t, o2;
        s32 q3v;

        {
            s32 *pw = D_801834D4;
            ((struct { s32 w; } *)pw)->w = s3[0];
            pw[1] = s3[1];
            pw[2] = s3[2];
        }
        s1var = -ret;

        __asm__ __volatile__(
            "lwc2 $9, 0(%0)\n"
            "lwc2 $10, 4(%0)\n"
            "lwc2 $11, 8(%0)\n"
            "nop\n"
            "nop\n"
            "sqr 0\n"
            : : "r"(D_801834D4) : "$9", "$10", "$11", "memory");
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(D_801834D8) : "memory");

        pc0 = D_801834D4;
        pc4 = D_801834D8;
        s0var = pc4[0] + pc4[1] + pc4[2];
        pb0 = D_801834C4;
        pb0[0] += s1var * pc0[0] / s0var;
        pb0[1] += s1var * pc0[1] / s0var;
        q3v = s1var * pc0[2] / s0var;

        {
            s32 h;
            h = ((s16 *)pb0)[0];
            s1var = h << 16;
            __asm__("lh %0, 2(%2)" : "=r"(h) : "0"(h), "r"(pb0) : "memory");
            s0var = h << 16;
        }
        pb0[2] += q3v;
        s2a = (s16)pb0[2] << 16;

        t = pc0[0] << 4;
        pc0[0] = t;
        if (t < 0) s1var |= 0xFFFF;
        t = pc0[1] << 4;
        pc0[1] = t;
        if (t < 0) s0var |= 0xFFFF;
        o2 = pc0[2];
        t = o2 << 4;
        pc0[2] = t;
        if (t < 0) s2a |= 0xFFFF;
        s2a += o2 << 5;
        s1var += pc0[0] << 1;
        s0var += pc0[1] << 1;

        do {
            s32 *pl = D_801834D4;
            u16 *pb;
            s1var += pl[0];
            s0var += pl[1];
            s2a += pl[2];
            pb = D_801834C4;
            pb[0] = s1var >> 16;
            pb[1] = s0var >> 16;
            pb[2] = s2a >> 16;
            ret = func_80134310(s3, pb, s6);
        } while (ret < ((s3[1] < -0xE00) ? 0x1800 : 0x2F00));
    }

    y = s3[1];
    if (y >= -0xBCB) {
        D_801834C0[3] = y;
        {
            typedef struct { s8 c[8]; } Blk8;
            *(Blk8 *)&D_801152B0 = *(Blk8 *)s3;
        }
        if (*(u8 *)cmd != 0)
            goto ret1;
        return -1;
    }
    {
        typedef struct { u16 h; } H16;
        u16 *s3u = (u16 *)s3;
        u16 *bp = D_801834C4;
        u16 w;
        ((H16 *)D_801152A8)->h = s3u[0];
        w = s3u[1];
        bp[3] = w;
        ((H16 *)&D_801152AA)->h = w;
        ((H16 *)&D_801152AC)->h = s3u[2];
        ((H16 *)&D_801152AE)->h = s3u[3];
    }
ret1:
    return 1;
}




typedef struct { s16 x, y, z; } Vec3s;

s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) {
    return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2;
}


DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (83 ins, relocation-masked)



s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{

    extern s32 D_801C6530;
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern s16 * D_801834C0;
    extern s16 * D_801834C4;
    extern u16 D_801C6540;
    extern u16 D_801C653C;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_801834C0;
    d94 = D_801C6530;
    pb0 = D_801834C4;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_801C6540 = 0;
    D_801C653C = 0;
    if (func_80133AB0(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_801834C4;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_801C6540;
        return 1;
    }

    pacs = D_801834C0;
    pb0s = D_801834C4;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (func_80133AB0(sangle, b0, pb0s[2], D_801C6530)) {
        goto setdst;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80134510);


// @class: regalloc-order
// @stuck: 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test, s0=puVar7/s1=cnt/s2=scan/s3=iVar8/s4=iVar9/s5=uVar3/s6=uVar10, a1=param/a0=cc/a3=0x8000 pinned, both range-persist copies present, mult+GPU-index+call all byte-correct). Residual = 4 instances of ONE gcc-2.7.2 regalloc/copy-prop tie-break: target computes a preserved-then-masked value in $v0 and reads $v0 for the mask (`subu $v0; addu $persist,$v0; andi $v0,$v0`), gcc here reads the persist reg (`andi $v0,$t0`). (1) range-check-1 andi reads $t0 not $v0; (2) range-check-2 andi reads $a0 not $v0; (3) `hi=uVar1&0x8000` folds into $a0 — target computes in $v0 + copies to $a0 in the branch-delay (same-block copy, gcc coalesces mine); (4) loop-test `cnt&0xffff` folds to direct `andi $v0,$s1` — target copies `addu $v0,$s1` first. Splitting the value into compare-temp + persist-var produces the copy but gcc forward-propagates the copy DEST into the mask; persist-after-compare kills the copy; explicit `register __asm__` pins fold the whole expr chain into the pinned reg; `=r/0` barriers force bad materialization. Also minor: while-loop header-copy adds a `beqz s1` entry guard vs target `j`, and a2/a3 call-arg setup order. Permuter can't run (register __asm__ pins rejected by pycparser). Genuinely compiler-internal — hand-finish or accept as ceiling.


s32 func_801345F8(s32 arg)
{
    extern int func_801347A0(short, u16 *, int, int);
    extern u16 * D_801834C0;
    extern u16 D_801C6540;

    register u16 *param_1 __asm__("$5") = ((u16 *)arg);
    register u16 *cc __asm__("$4") = D_801834C0;
    int c8000 = 0x8000;
    register int zr __asm__("$0");
    u32 c1, c2, uVar6, uVar2, cnt, v14;
    u16 *ptmp, *puVar4, *puVar7, uVar1;
    int hi, harg, iVar9, iVar8, uVar3, uVar10, tbl;

    c1 = ((int)(cc[0] + c8000) >> 7 & 0x1ff) - (u32)param_1[0];
    uVar6 = c1 + zr;
    if ((c1 & 0xffff) < (u32)param_1[2]) {
        c2 = ((int)(cc[2] + c8000) >> 7 & 0x1ff) - (u32)param_1[1];
        uVar2 = c2 + zr;
        if ((c2 & 0xffff) < (u32)param_1[3])
            goto do_mult;
        return 0;
      found:
        D_801C6540 = *puVar7;
        return 1;
      do_mult:
        tbl = *(int *)(param_1 + 4);
        uVar10 = *(int *)(param_1 + 6);
        uVar3 = *(int *)(param_1 + 8);
        iVar9 = *(int *)(param_1 + 0xc);
        iVar8 = *(int *)(param_1 + 0xe);
        ptmp = (u16 *)((((u32)(u16)uVar2 * (u32)param_1[2] + (u32)(u16)uVar6) * 2 & 0xffff) * 2 + tbl);
        cnt = (u32)ptmp[1];
        v14 = *(int *)(param_1 + 10);
        puVar4 = (u16 *)(v14 + (u32)*ptmp + cnt * 2) - 1;
        while (((cnt-- + zr) & 0xffff) != 0) {
            uVar1 = *puVar4;
            hi = uVar1 & 0x8000;
            harg = hi + zr;
            if (hi == 0)
                puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
            else
                puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
            if (func_801347A0((short)harg, puVar7, uVar3, uVar10) != 0)
                goto found;
            puVar4 = puVar4 - 1;
        }
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801347A0);

DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134a28 (src/shared) */



int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801C6540;
    extern s32 func_80134C20(s32, s32, s32, s32);

    u16 *param_4p = (u16 *)param_4;
    register u32 zr __asm__("$0");
    u32 uVar6, uVar2, uVar2c;
    register u32 uVar6c __asm__("$9");
    u16 *puVar4, *ptmp;
    register u32 n __asm__("$18");
    register u32 p0 __asm__("$4");
    register int v14 __asm__("$3");
    u16 *puVar7, uVar1;
    u32 hi, hic;
    int iVar5, iVar9, iVar8, uVar3, uVar10;

    uVar6 = ((int)((param_2 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[0];
    uVar6c = uVar6 + zr;
    if ((uVar6 & 0xffff) < (u32)param_4p[2]) {
        uVar2 = ((int)((param_3 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[1];
        __asm__("addu %0,%1,$zero" : "=r"(uVar2c) : "r"(uVar2));
        if ((uVar2 & 0xffff) < (u32)param_4p[3]) goto work;
        return 0;
    found:
        D_801C6540 = *puVar7;
        return 1;
    work:
        uVar10 = *(int *)(param_4p + 6);
        uVar3 = *(int *)(param_4p + 8);
        iVar9 = *(int *)(param_4p + 0xc);
        iVar8 = *(int *)(param_4p + 0xe);
        ptmp = (u16 *)((((uVar2c & 0xffff) * (u32)param_4p[2] + (uVar6c & 0xffff)) * 2 & 0xffff) * 2 + *(int *)(param_4p + 4));
        v14 = *(int *)(param_4p + 10);
        __asm__ __volatile__("" :: "r"(uVar6c));
        p0 = (u32)*ptmp;
        n = (u32)ptmp[1];
        puVar4 = (u16 *)(v14 + p0 + n * 2) - 1;
        goto test;
    body:
        uVar1 = *puVar4;
        hi = uVar1 & 0x8000;
        hic = hi + zr;
        if (hi == 0)
            puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
        else
            puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
        puVar4 = puVar4 - 1;
        iVar5 = func_80134C20((short)(hic | param_1), (s32)puVar7, uVar3, uVar10);
        if (iVar5 != 0) goto found;
    test:
        {
            u32 m;
            __asm__("addu %0,%1,$zero" : "=r"(m) : "r"(n));
            n--;
            if ((m & 0xffff) != 0) goto body;
        }
    }
    return 0;
}



// @class: regalloc-order
// @try: variant B — direct pins m=$s5($21), c=$s6($22)


s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8 D_801152A8[];
    extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
    extern void * D_801834C0;
    extern void * D_801834C4;
    extern void * D_801834C8;
    extern void * D_801834CC;
    extern u16 D_801C6540;

    s32 temp_a3;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    u16 temp_a1;
    s32 temp_s4;
    s32 c = arg0;
    __asm__ __volatile__("" : "=r"(c) : "0"(c));
    __asm__ __volatile__("" : : "r"(arg0));

    temp_s4 = arg2 + (M2C_FIELD(((void *)arg1), s16 *, 2) * 8);
    temp_s1 = *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 4) * 4));
    var_v0 = 0;
    if (func_80134FB8(temp_s4, (s32) D_801834C4, temp_s1) >= 0) {
        return var_v0;
    }
    temp_v0 = func_80134FB8(temp_s4, (s32) D_801834C0, temp_s1);
    if (temp_v0 < 0) {
        goto block_13;
    }
    temp_v0_2 = func_80134FB8(temp_s4, (s32) D_801834CC, 0);
    temp_a3 = -temp_v0;
    {
        u16 *pB4 = (u16 *)D_801834C8;
        u16 *pAC = (u16 *)D_801834C0;
        s16 *pB8 = (s16 *)D_801834CC;
        pB4[0] = pAC[0] + (temp_a3 * pB8[0]) / temp_v0_2;
        pB4[1] = pAC[1] + (temp_a3 * pB8[1]) / temp_v0_2;
        pB4[2] = pAC[2] + (temp_a3 * pB8[2]) / temp_v0_2;
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 6) * 8), (s32) pB4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 8) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xA) * 8), (s32) D_801834C8, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0xC) * 4))) < -0x2F00) {
        return var_v0;
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xE) * 8), (s32) D_801834C8, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x10) * 4))) < -0x2F00) {
        return var_v0;
    }
    if ((arg0 << 16) < 0) {
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0x12) * 8), (s32) D_801834C8, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x14) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    if (c & 1) {
        if (!(M2C_FIELD(((void *)arg1), u16 *, 0) & 0x300)) {
            goto block_14;
        }
        return 0;
    }
    temp_a1 = M2C_FIELD(((void *)arg1), u16 *, 0);
    if (!(temp_a1 & 0x200)) {
        goto block_14;
    }
    D_801C6540 = temp_a1;
block_13:
    return 0;
block_14:
    __builtin_memcpy(D_801152A8, (void *)temp_s4, 8);
    VectorNormalSS(D_801834CC, D_801834CC);
    {
        u16 *pB8 = (u16 *)D_801834CC;
        u16 *pB4b = (u16 *)D_801834C8;
        pB4b[0] = pB4b[0] - ((pB8[0] << 0x10) >> 0x1B);
        var_v0 = 1;
        pB4b[1] = pB4b[1] - ((pB8[1] << 0x10) >> 0x1B);
        pB4b[2] = pB4b[2] - ((pB8[2] << 0x10) >> 0x1B);
    }
    return var_v0;
}


DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134fb8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135004);



// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)



extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{

    extern u8 D_801834C4;
    extern u8 D_801834C0;
    extern s16 *D_801834C8;
    extern u8 D_801834CC;
    extern int D_801C6530;
    extern u16 D_801C6540;
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801834C4);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_801834C0); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_801834CC); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801C6530;
    __asm__ __volatile__("" ::: "memory");
    D_801C6540 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_801834C8);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801C6540;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135260);

extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);

/* func_80135480 — cull + coordinate-transform emitter (258 ins, ov_SC01_077 split _a, ×134 family).
 *
 * NOT a §43 s16-param giant. Params are (void*, s32, s16*, s16*); the sole `sll/sra 16` is the s16
 * RETURN narrowing on $s3 (result), not an in-place arg-reg narrow. So §43's K&R-s16-param map does
 * not apply here — no //@EDIT, no ec_edit. func_80135480 has NO ambient prototype/caller anywhere in
 * src/include, so the s16 return type is free (no void->s32 flip, no engine_core.h edit).
 *
 * THE CRACK (residual class = §31 regalloc/schedule, RC-4/RC-2 in gcc-2.7.2-map/regalloc.md):
 * the two output buffers D_801834C0 / D_801834C4 are written through a pointer in each of the two
 * return tails (mode!=0 and mode==0). A single function-scope `s16 *tmp` reused across both tails is a
 * GLOBAL allocno (used in 2 blocks, dies 4x) -> forced onto one hard reg ($a1), which is WRONG and also
 * perturbs the switch's first-`beq` delay-slot fill (extra nop). The target instead allocates each
 * store-group's pointer as a LOCAL-ALLOC pseudo (set once, used 3x, dies once, single block) that picks
 * the lowest-free scratch over its OWN window:
 *     mode!=0 tail:  p_AC -> $v1,  p_B0 -> $v1 (reused, $v0 = the load temp)
 *     mode==0 tail:  p_AC -> $v1,  p_B0 -> $a0 (the sub-scratch occupies $v1, so $v1 is unavailable)
 * Reproduced by giving each of the four store-groups its OWN block-scoped pointer. With the tail
 * allocation correct, the whole schedule (incl. the beq delay slot) re-derives to byte-identical.
 * No register pins (§17 caveat: don't pin $v1 — the target reuses it for the cull; a pin cascades
 * per RC-5). NOTE: the block-scope `s16 *p` intentionally shadows the function-scope `s32 p` (the
 * case-0x20000000 pointer base); scopes never overlap — legal and byte-verified.
 *
 * Zero file-scope footprint (block-scoped typedefs + externs; D_801834C0/B0 read via the ambient
 * `extern u8` + `*(s16**)&` §30 anon-cast, matching neighbor func_80135168) -> ×134-clean for
 * family_sweep --edit-remap with no cc1 crash.
 *
 * VERIFIED: tools/rtu_match.py func_80135480 --split ov_SC01_077_a  ->  MATCH (258 ins), 3x stable.
 */
s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
{

    extern Box_80133784 * D_801834C0;
    extern Box_80133784 * D_801834C4;
    typedef struct { s32 vx, vy, vz, pad; } Vec32;
    typedef struct { s16 vx, vy, vz, pad; } Vec16;
    typedef struct { s32 w0, w4, w8, wC; s16 h10, hpad; s32 t0, t1, t2; } Mat32;
    extern void func_80048EAC(void *m0, void *m1);
    extern void func_8004914C(void *m);
    extern void ApplyTransposeMatrixLV(void *m, void *in, void *out);
    extern void ApplyRotMatrixLV(void *in, void *out);
    extern void ApplyRotMatrix(void *in, void *out);
    extern s32 D_801C6544, D_801C6548, D_801C654C, D_801C6550;
    extern s16 D_801C6554;
    extern s32 D_801C6564;
    extern s16 D_801C6568, D_801C656A, D_801C656C, D_801C656E, D_801C6570, D_801C6572;

    Vec32 in0, in1, rotout;
    Mat32 mat2;
    Vec16 vecin;
    s32 result;
    s32 mode;
    s32 q1, q2;
    s32 p;
    s32 t18, t1A, t1C;
    s32 *m;

    in0.vx = param_3[0] - *(s32 *)((s32)param_1 + 0x48);
    in0.vz = param_3[2] - *(s32 *)((s32)param_1 + 0x50);
    if ((param_2 & 0x10000000) == 0) {
        if (in0.vx * in0.vx + in0.vz * in0.vz > 0x40000) {
            return 0;
        }
    }
    mode = param_2 & 0x60000000;
    if (mode != 0) {
        result = 1;
        if (param_2 >= 0) {
            mode &= 0x40000000;
        }
        in0.vy = param_3[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vx = param_4[0] - *(s32 *)((s32)param_1 + 0x48);
        in1.vy = param_4[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vz = param_4[2] - *(s32 *)((s32)param_1 + 0x50);
        switch (mode) {
        case 0x60000000:
            m = &D_801C6544;
            *m = 0x1000000 / *(s16 *)((s32)param_1 + 0x18);
            q1 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1A);
            q2 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1C);
            D_801C6548 = 0;
            D_801C6550 = 0;
            D_801C654C = q1;
            D_801C6554 = q2;
            func_80048EAC((void *)((s32)param_1 + 0x34), m);
            ApplyTransposeMatrixLV(m, &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            /* fallthrough */
        case 0x20000000:
            p = (param_2 & 0xFFFFFFF) | 0x80000000;
            t18 = *(s16 *)((s32)param_1 + 0x18);
            t1A = *(s16 *)((s32)param_1 + 0x1A);
            t1C = *(u16 *)((s32)param_1 + 0x1C);
            mat2.w4 = 0;
            mat2.wC = 0;
            mat2.w0 = t18;
            mat2.w8 = t1A;
            mat2.h10 = t1C;
            func_8004914C(&mat2);
            vecin.vx = *(u16 *)(p + 4);
            vecin.vy = *(u16 *)(p + 8);
            vecin.vz = *(u16 *)(p + 0xC);
            ApplyRotMatrix(&vecin, &rotout);
            D_801C6568 = rotout.vx;
            D_801C656C = rotout.vy;
            D_801C6570 = rotout.vz;
            vecin.vx = *(u16 *)(p + 6);
            vecin.vy = *(u16 *)(p + 0xA);
            vecin.vz = *(u16 *)(p + 0xE);
            ApplyRotMatrix(&vecin, &rotout);
            D_801C6564 = 0;
            D_801C656A = rotout.vx;
            D_801C656E = rotout.vy;
            D_801C6572 = rotout.vz;
            result += 2;
            break;
        case 0x40000000:
            ApplyTransposeMatrixLV((void *)((s32)param_1 + 0x34), &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            break;
        }
        {
            s16 *p = *(s16 **)&D_801834C0;
            p[0] = in0.vx;
            p[1] = in0.vy;
            p[2] = in0.vz;
        }
        {
            s16 *p = *(s16 **)&D_801834C4;
            p[0] = in1.vx;
            p[1] = in1.vy;
            p[2] = in1.vz;
        }
        return result;
    }
    {
        s16 *p = *(s16 **)&D_801834C0;
        p[0] = in0.vx;
        p[1] = ((u16 *)param_3)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = in0.vz;
    }
    {
        s16 *p = *(s16 **)&D_801834C4;
        p[0] = ((u16 *)param_4)[0] - *(s32 *)((s32)param_1 + 0x48);
        p[1] = ((u16 *)param_4)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = ((u16 *)param_4)[2] - *(s32 *)((s32)param_1 + 0x50);
    }
    return 1;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135888);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135A4C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135D20);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80135EB0);


s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_801834C0;
    extern Box_80133784 * D_801834C4;
    extern s16 *D_801834C8;
    extern u8 D_801834CC;
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
        dx = (s16) arg2 - (*(s16 **)&D_801834C0)[2];
        d = dx;
        denom = -(*(s16 **)&D_801834CC)[2];
    } else {
        denom = (*(s16 **)&D_801834CC)[2];
        d = (*(s16 **)&D_801834C0)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_801834CC;
        u16 *ac = *(u16 **)&D_801834C0;
        b4 = D_801834C8;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_801834C4;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_801834C8[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_801834C8[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}



// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_801834C0/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_801834C8 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_801834C0;
    extern Box_80133784 * D_801834C4;
    extern s16 *D_801834C8;
    extern u8 D_801834CC;
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
        var_v1 = (s16) arg2 - (*(s16 **)&D_801834C0)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_801834CC)[0];
    } else {
        var_a3 = (*(s16 **)&D_801834CC)[0];
        var_v1 = (*(s16 **)&D_801834C0)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_801834C0;
    b4 = D_801834C8;
    b8 = *(s16 **)&D_801834CC;
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
        b4[1] = (s16) (*(u16 **)&D_801834C4)[1];
        b4[2] = (s16) (*(u16 **)&D_801834C4)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_801834C8, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_801834C8, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_801834C0/B0/B8 are file-scope `extern u8`, D_801834C8 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_801834C8 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_801834C0;
    extern Box_80133784 * D_801834C4;
    extern s16 *D_801834C8;
    extern u8 D_801834CC;
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
        var_t0 = (s16) arg2 - (*(s16 **)&D_801834C0)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_801834CC)[1];
    } else {
        var_a3 = (*(s16 **)&D_801834CC)[1];
        var_v1 = (*(s16 **)&D_801834C0)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_801834CC);
    ac = (*(u16 **)&D_801834C0);
    b4 = D_801834C8;
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
        p = (*(u16 **)&D_801834C4);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_801834C8;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_801834C8;
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



s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern u8 D_801152A8[];
    extern u8 D_80126720[];
    extern s16 *D_801834C8;   /* holds a pointer value (*(u16**)&D_801834C8) */
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_801834C8, *(void **)&D_801834C8);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_801834C8;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}


DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136bc4 (src/shared) */


DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136c1c (src/shared) */


void func_80136C3C(void) {
}

void func_80136C44(void) {
}

void func_80136C4C(void) {
}



void func_80136C54(void)
{

    extern unsigned short D_800B99F0;
    extern void (*D_801834DC[])(void);
    D_801834DC[D_800B99F0]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80136C90);

void func_80136D00(void) {
}

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136d08 (src/shared) */


DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136dfc (src/shared) */


void func_80136EC4(void) {
}

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ecc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80136F3C);

DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80137178);

DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372b0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375ec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767c (src/shared) */


DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376c8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377b4 (src/shared) */


DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379d8 (src/shared) */


DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379ec (src/shared) */



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
extern void func_80138BE0(int p);

void func_80137B80(void) {

    extern s32 D_80127548[];
    extern int D_80183530;
    extern int D_801269F0;
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_80183530 += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137bd8 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.


extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{

    extern unsigned char D_80126A0E;
    extern short D_80126A0A;
    extern s16 D_801269F4;
    extern int D_800A5E60;
    extern int D_80183530;
    extern int D_801269F0;
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
        if (D_80183530 & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137DD4 (src/shared) */

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137fd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801380E0);

DEFINE_func_801387B8()  /* dedup: shared engine-core @0x801387B8 (src/shared) */

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */


DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895c (src/shared) */


DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138ab4 (src/shared) */


DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138b88 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)


void func_80138BE0(int p)
{

    extern void (*D_80183534[])(void);
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_80183534[*(short *)(p + 4)]();
}


void func_80138C30(void *a0) {
    if (*(s16 *)((s32)a0 + 4) == 4) {
        *(s16 *)((s32)a0 + 4) = 2;
    } else {
        *(u32 *)((s32)a0 + 8) |= 0x800;
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138d58 (src/shared) */


DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138db8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80138DE0);

DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ed0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914c (src/shared) */


DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391f0 (src/shared) */


DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */


DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392c8 (src/shared) */


DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_801395D4);

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */



extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{

    extern short D_800B9A02;
    extern u8 D_800A6518[];
    extern u8 D_80183578;
    extern u8 D_801835BC;
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
    b164 = (u8 *)&D_80183578;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_801835BC + off;
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


DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399a8 (src/shared) */


DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399f0 (src/shared) */


DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139a34 (src/shared) */


DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139a44 (src/shared) */


DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139a68 (src/shared) */


DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139a8c (src/shared) */


DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139b18 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139c7c (src/shared) */


DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139d04 (src/shared) */


DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139dc8 (src/shared) */


void func_80139DEC(void) {
}

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139df4 (src/shared) */


DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139e84 (src/shared) */


DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139f0c (src/shared) */


DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139fbc (src/shared) */


DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139fe8 (src/shared) */


DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013a0a4 (src/shared) */


DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013a164 (src/shared) */


DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013a1e8 (src/shared) */


DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013a250 (src/shared) */


DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013a2bc (src/shared) */


void func_8013A378(void) {
}

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013a380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013a448 (src/shared) */


DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013a4c4 (src/shared) */


DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013a530 (src/shared) */


DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013a860 (src/shared) */


DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013a8b0 (src/shared) */


DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013a8bc (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013a8fc (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013a9b4 (src/shared) */


DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013a9f8 (src/shared) */


DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013aa24 (src/shared) */


extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern void func_8013AF20();
s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_800A5E60;
    u8 buf[0xE4];          /* spans 0x10 .. 0xF4 */
    s32 neg;
    s32 a, b;
    s32 t4, t6;
    t4 = *(s16 *)(a2 + 4) * 12;
    *(s16 *)(buf + 0xE0) = t4 + 0x10;   /* sp+0xF0 */
    neg = a3 & 0x8000;
    t6 = *(s16 *)(a2 + 6) * 12 + (*(s16 *)(a2 + 6) - 1) * 2;
    *(s16 *)(buf + 0xE2) = t6 + 8;
    if (neg == 0) {
        *(s16 *)(buf + 0xE0) = t4 + 0x38;
        *(s16 *)(buf + 0xE2) = t6 + 0x10;
    }
    a = ((s32)*(s16 *)(buf + 0xE0) << 12) / 154;
    b = ((s32)*(s16 *)(buf + 0xE2) << 12) / 42;
    *(s16 *)(buf + 0xE0) = a;
    *(s16 *)(buf + 0xE2) = b;
    if (neg != 0) {
        *(s16 *)(buf + 0xE0) = -a;
    }
    *(s16 *)(buf + 0xC8) = b;          /* 0xD8 */
    *(s16 *)(buf + 0xC2) = 0;          /* 0xD2 */
    *(s16 *)(buf + 0xC4) = 0;          /* 0xD4 */
    *(s16 *)(buf + 0xC6) = 0;          /* 0xD6 */
    *(s16 *)(buf + 0xCA) = 0;          /* 0xDA */
    *(s16 *)(buf + 0xCC) = 0;          /* 0xDC */
    *(s16 *)(buf + 0xCE) = 0;          /* 0xDE */
    *(s16 *)(buf + 0xD0) = 0x1000;     /* 0xE0 */
    *(s16 *)(buf + 0xC0) = *(u16 *)(buf + 0xE0);   /* 0xD0 */
    *(s32 *)(buf + 0xD4) = *(s16 *)(a2 + 0);       /* 0xE4 */
    *(s32 *)(buf + 0xD8) = *(s16 *)(a2 + 2);       /* 0xE8 */
    *(s32 *)(buf + 0xDC) = 0;                       /* 0xEC */
    __asm__ __volatile__("" ::: "memory");
    {
        register s32 *p __asm__("$2") = (s32 *)(buf + 0xC0);
        __asm__ __volatile__(
            "lw $12, 0(%0)\n"
            "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n"
            "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n"
            "lw $13, 12(%0)\n"
            "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n"
            "ctc2 $13, $3\n"
            "ctc2 $14, $4\n"
            "lw $12, 20(%0)\n"
            "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n"
            "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n"
            "ctc2 $14, $7\n"
            : : "r"(p) : "$12", "$13", "$14", "memory");
    }
    func_8013AD38(buf + 0xE0, 0, buf + 0x00, buf + 0x80);
    D_800A5E60 = a0;
    if (a3 != 0) {
        func_8013B274(a1, 0x80, buf + 0xE0);
    }
    func_8013AF20(a1, a2, buf + 0x00, buf + 0x80);
    return D_800A5E60;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013AD38);

DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013af20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013b204 (src/shared) */




extern void *func_80010A08(s32);

void func_8013B274(s32 a0, s32 a1, void *a2)
{

    extern s16 D_80183678, D_8018367A, D_8018367C, D_8018367E, D_80183680, D_80183682;
    extern u16 D_800D45F6;
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
        if (!(D_8018367A < ang)) goto outer_else;
        if (!(ang < D_80183680)) goto inner_else;
        if (ang < D_8018367C) { *(s16 *)L = D_8018367C; goto done; }
        if (D_8018367E < ang) { *(s16 *)L = D_8018367E; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_80183678) { *(s16 *)L = D_80183678; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_80183682 < ang) { *(s16 *)L = D_80183682; goto done; }
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


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B568);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B598);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013B83C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013BD34);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013BD74);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C08C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C360);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C414);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C938);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C964);


extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801C65A8;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801C65A8, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013C9C4);


void func_8013CA14(void)
{

    extern s32 D_801C65A8;
    extern s8 D_801C65AC;
    extern s8 D_801C65AD;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801C65A8;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801C65AD;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801C65AC)) * 2) + D_801C65A8);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801C65AD = (unsigned char) p[1];
      D_801C65AC = D_801C65AC + 1;
      if (D_801C65AD == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801C65AC = 0;
        *base = 0;
      }
    }
    else
    {
      D_801C65AD = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801C65CC;
    extern s32 D_801C65C0;
    extern s32 D_801C65C4;
    extern s32 D_801C65D0;
    D_801C65CC = 1;
    D_801C65C0 = 1;
    D_801C65C4 = 0;
    D_801C65D0 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801C65C0;
    extern s32 D_801C65C4;
    extern s32 D_801C65C8;
    extern s32 D_801C65CC;
    extern s32 D_801C65D0;
    D_801C65C0 = 1;
    D_801C65CC = 0;
    D_801C65C4 = 0;
    D_801C65C8 = -1;
    D_801C65D0 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801C65CC;
    extern s32 D_801C65D0;
    extern s32 D_801C65F8;
    extern s32 D_801C65FC;
    D_801C65F8 = D_801C65D0;
    D_801C65FC = D_801C65CC;
    D_801C65D0 = 1;
    D_801C65CC = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801C65F8;
    extern s32 D_801C65FC;
    extern s32 D_801C65D0;
    extern s32 D_801C65CC;
    D_801C65D0 = D_801C65F8;
    D_801C65CC = D_801C65FC;
}



typedef struct { s32 a, b, c; } Rec12;
typedef struct { s32 a, b; s8 c; } __attribute__((packed, aligned(1))) Rec9;

extern s16 currentLocationId;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_801C65D0;
    extern s32 D_801C65C8;
    extern s32 D_801C65CC;
    extern s32 D_801C65C0;
    extern s32 D_801C65C4;
    extern s32 D_801C65D4;
    extern s32 D_801C65E0;
    extern s32 D_801C65E8;
    extern s32 D_801C7AA8;
    extern s32 D_801C7A28;
    extern s32 D_801C7A1C[];
    extern u8 D_801C79E1;
    extern u8 D_801C7B36;
    extern u8 D_801C7AA4;
    extern Rec12 D_80183898[];
    extern Rec9 D_80183860[];
    extern u8 D_801C7A80;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801C7AA8 = 0;
    if (D_801C65D0 == 0 && s0 != D_801C65C8) {
        ta = D_80183898[s0].a;
        tb = D_80183898[s0].b;
        tc = D_80183898[s0].c;
        D_801C65C8 = s0;
        D_801C79E1 = tc;
        D_801C7B36 = ta;
        D_801C7AA4 = tb;
        *(Rec9 *)&D_801C7A80 = D_80183860[s0];
        D_801C65CC = 1;
        D_801C65C0 = 1;
        if (D_801C65E0 & 2) {
            if (s0 == 4) { D_801C7A1C[0] = 0x100; D_801C7A28 = 0x80; }
            if (s0 == 0) { D_801C7A1C[0] = 0x100; D_801C7A28 = 0; }
        }
    }
    if (D_801C65CC != 0) {
        t = D_801C65C0 - 1;
        D_801C65C0 = t;
        if (t == 0) {
            if (D_801C65D0 == 0) {
                if ((D_801C65E0 & 2) && s0 == 4) {
                    if (D_801C65E8 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801C65E8 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801C65C0 = 2;
                if (D_801C65CC != 0) {
                    if (D_801C65E0 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801C7A28;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801C7A28;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801C65E0 & 2) {
                    if (s0 == 4) D_801C7A28 = 0;
                    if (s0 == 0) D_801C7A28 = 0x80;
                }
            } else {
                if (D_801C65E8 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801C65C0 = 1;
            }
        }
    }
    D_801C65D4 = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801C65CC != 0) D_801C65D4 = D_801C65C4;
            else D_801C65D4 = 0x1F;
        } else if (s0 == 4) {
            if (D_801C65CC != 0) D_801C65D4 = 0x1F - D_801C65C4;
            else D_801C65D4 = 0;
        }
    }
}




void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801C79D8;
    extern u8 D_801C79D9;
    extern u8 D_801C79DA;
    extern u8 D_801C79DB;
    extern u8 D_801C79DC;
    extern u8 D_801C79DD;
    extern u8 D_801C79DE;
    extern u8 D_801C79DF;
    extern u8 D_801C79E0;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801C79D8; t1 = D_801C79D9; t2 = D_801C79DA;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801C79DB; t1 = D_801C79DC; t2 = D_801C79DD;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801C79DE; t1 = D_801C79DF; t2 = D_801C79E0;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern void func_8013D9B0();

void func_8013D064(void)
{

    extern s32 D_801C65D8;
    extern s32 D_801C65C0;
    extern s32 D_801C65DC;
    extern s32 D_801C65CC;
    if (D_801C65D8 != 0) {
        if (D_801C65D8 != 2) {
            if (((D_801C65D8 < 3) && (D_801C65D8 == 1)) &&
                (D_801C65DC = D_801C65DC + 1, 0x23a < D_801C65DC)) {
                D_801C65C0 = D_801C65D8;
                D_801C65D8 = 2;
            }
        } else {
            D_801C65C0 = D_801C65C0 + -1;
            if (D_801C65C0 == 0) {
                D_801C65C0 = D_801C65D8;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801C65CC == 0) {
                    D_801C65D8 = D_801C65D8 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801C65CC;
    func_8013D9B0();
    return D_801C65CC;
}




void func_8013D164(void) {

    extern s32 D_801C65D8;
    D_801C65D8 = 1;
}



void func_8013D178(void) {

    extern u8 D_801C79D8;
    extern u8 D_801C79D9;
    extern u8 D_801C79DA;
    extern u8 D_801C79DB;
    extern u8 D_801C79DC;
    extern u8 D_801C79DD;
    extern u8 D_801C79DE;
    extern u8 D_801C79DF;
    extern u8 D_801C79E0;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    extern unsigned char D_801C7A80, D_801C7A81, D_801C7A82, D_801C7A83, D_801C7A84, D_801C7A85, D_801C7A86, D_801C7A87, D_801C7A88;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801C79D8; v = *p; t = D_801C7A80;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79D9; v = *p; t = D_801C7A81;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DA; v = *p; t = D_801C7A82;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DB; v = *p; t = D_801C7A83;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DC; v = *p; t = D_801C7A84;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DD; v = *p; t = D_801C7A85;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DE; v = *p; t = D_801C7A86;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79DF; v = *p; t = D_801C7A87;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C79E0; v = *p; t = D_801C7A88;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801C7AC2;
    extern u8 D_801C7B36;
    extern u8 D_801C79E2;
    extern u8 D_801C7AA4;
    extern u8 D_801C79B8;
    extern u8 D_801C79E1;
    extern s32 D_801C7AA8;
    if ((D_801C7AC2 & 0xff) != D_801C7B36) {
        D_801C7AC2 = ((D_801C7AC2 & 0xff) < D_801C7B36) ? (D_801C7AC2 + 1) : (D_801C7AC2 - 1);
    }
    if ((D_801C79E2 & 0xff) != D_801C7AA4) {
        D_801C79E2 = ((D_801C79E2 & 0xff) < D_801C7AA4) ? (D_801C79E2 + 1) : (D_801C79E2 - 1);
    }
    if ((D_801C79B8 & 0xff) != D_801C79E1) {
        D_801C79B8 = ((D_801C79B8 & 0xff) < D_801C79E1) ? (D_801C79B8 + 1) : (D_801C79B8 - 1);
    }
    D_801C7AA8 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801C65B0;
    extern void *D_801C65B4;
    extern void *D_801C65B8;
    extern s32 D_801C65E0;
    extern s32 D_801C65E4;
    extern s32 D_801C65E8;
    extern s32 D_801C7A1C[];
    extern u8 D_80183770[];
    extern u8 D_80183818[];
    extern u8 D_801836C8[];
    extern u8 D_801837C4[];
    extern u8 D_80183844[];
    extern u8 D_8018371C[];
    u8 *p = D_80078E78;

    D_801C65E0 = param_2;
    D_801C65E4 = (param_2 >> 2) & 3;
    D_801C65E8 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801C65B0 = D_80183770;
        D_801C65B4 = D_80183818;
        D_801C65B8 = D_801836C8;
    } else {
        D_801C65B0 = D_801837C4;
        D_801C65B4 = D_80183844;
        D_801C65B8 = D_8018371C;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801C65E8 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801C65E0 & 2) != 0) {
            D_801C7A1C[0] = 0x140;
            D_801C7A1C[3] = 0x80;
            if (p[0x37] == 4) {
                D_801C7A1C[0] = 0x140;
                D_801C7A1C[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801C7A1C[0] = 0x140;
                D_801C7A1C[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013D53C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013D9B0);


// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801C65B8)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_801C65B8;
    extern s16 *D_801C65BC;
    extern s32 D_801C65CC;
    extern s32 D_801C65EC;
    extern s32 D_801C65F0;
    extern s32 D_801C65F4;
    int *p;
    int x, y, z;
    int flag;

    if (D_801C65BC != 0) {
        D_801C65CC = 0;
        p = (int *)(param_1 * 12 + (int)D_801C65B8);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801C65EC != x) {
            flag = 1;
            if (D_801C65EC < x) {
                if (x - D_801C65EC < 5) {
                    D_801C65EC = x;
                } else {
                    D_801C65EC = D_801C65EC + 4;
                }
            } else {
                if (D_801C65EC - x < 5) {
                    D_801C65EC = x;
                } else {
                    D_801C65EC = D_801C65EC - 4;
                }
            }
        }
        if (D_801C65F0 != y) {
            flag = 1;
            if (D_801C65F0 < y) {
                if (y - D_801C65F0 < 5) {
                    D_801C65F0 = y;
                } else {
                    D_801C65F0 = D_801C65F0 + 4;
                }
            } else {
                if (D_801C65F0 - y < 5) {
                    D_801C65F0 = y;
                } else {
                    D_801C65F0 = D_801C65F0 - 4;
                }
            }
        }
        if (D_801C65F4 != z) {
            flag = 1;
            if (D_801C65F4 < z) {
                if (z - D_801C65F4 < 5) {
                    D_801C65F4 = z;
                } else {
                    D_801C65F4 = D_801C65F4 + 4;
                }
            } else {
                if (D_801C65F4 - z < 5) {
                    D_801C65F4 = z;
                } else {
                    D_801C65F4 = D_801C65F4 - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801C65CC = flag;
    }
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801C65D4;
    return D_801C65D4;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013e064 (src/shared) */


DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013e0fc (src/shared) */


DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013e194 (src/shared) */


DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013e22c (src/shared) */


DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013e298 (src/shared) */


DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013e2c4 (src/shared) */


DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013e370 (src/shared) */


DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013e410 (src/shared) */


DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013e448 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013E4B4);

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013e558 (src/shared) */


DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013e588 (src/shared) */



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
    extern void (*D_801842E4[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_801842E4[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013e67c (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern s16 currentLocationId;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {

    extern u8 D_80078EC0;
    extern u16 D_8011511A;
    extern u16 D_80115124;
    extern u8 D_80115148[];
    extern u8 D_80115140[];
    extern s32 D_801842D0;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_801842A8;
    extern s16 D_801842AA;
    extern unsigned short D_80115112;
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
        ep = (s32 *)&D_801842D0;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_801842A8 = 2;
        D_801842AA = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_801842AA = 0;
        D_801842A8 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013e814 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {

    extern u16 D_80115110;
    extern u16 D_8011511A;
    extern int func_80029178(int);
    extern void func_8002D4C8(int, int);
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
    extern void * D_801C6608;
    extern void * D_801C660C;
    extern unsigned char D_80183F48;
    extern unsigned char D_80183F60;
    extern unsigned char D_80183FD4;
    extern unsigned char D_80183FDC;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801C6608 = &D_80183F48;
        D_801C660C = &D_80183FD4;
    } else {
        D_801C6608 = &D_80183F60;
        D_801C660C = &D_80183FDC;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        func_8002D4C8(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_801842D0/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_801842D0 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_801842D0;
    extern void func_80139954(void);
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
        v = ((s32 *)&D_801842D0)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}


DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013ea54 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern void func_8013FAF8(s16 a0, s16 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);


void func_8013EB7C(void) {

    extern short D_800B9A02;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern u16 D_8011511A;
    extern u16 D_8011511E;
    extern short D_80115128;
    extern unsigned short D_80115112;
    extern s16 D_8011512A;
    extern s32 D_80115130;
    extern unsigned char D_801842AC;
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_801842AC));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_801842AC));
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


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ed6c (src/shared) */


extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_801842AA` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_801842A8` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

typedef struct { s32 f0; } E4;



s32 func_8013EE10() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern s16 D_801842A8;
    extern s16 D_801842AA;
    extern unsigned char D_801842AC;
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
    r = &D_801842AA;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_801842A8 = (u16)D_801842A8 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_801842AC);
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


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007_jr_80131340", func_8013EF88);



// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_801842AC;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_801842AC);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */
