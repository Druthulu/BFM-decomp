#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
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
extern void func_80144B9C();
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
extern void func_8012A328();
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
extern s32 func_8012CC88();
extern u8 D_800D3918[];
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012CC40(s32 arg0, s32 arg1);
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
extern void func_8012E014();
extern void func_8012E138();
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
extern void func_80131E00();
extern s32 D_801F4D80;
extern s32 D_801F4D84;
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern int func_80131D68(int a0, int a1);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void func_80131EEC(void *a0);
extern void func_80131F28(void *a0);
extern void func_80131F64(void *a0);
extern void func_80131FA0(void *a0);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern void func_801320D8(int param_1);
extern void func_80132144(int param_1);
extern void func_801321B0(int param_1);
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
extern void func_801330E0(void * param_1, s16 * param_2, s32 param_3);
extern void func_80133060(u8 *a0, s32 *a1, s32 a2);
extern void func_8013339C(short *param_1, short *param_2);
extern s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3);
extern void func_80136BC4(s32 a0);
extern void func_801336E8(void *a0, int a1, int a2);
extern void func_80136BC4(s32);
extern void func_8013373C(s16 arg0);
extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);
extern s32 func_80133CD4();
extern s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2);
extern s32 func_8013435C(s16 *a0, s16 *a1, s32 a2, s16 *a3);
extern s32 func_801343C4(s32 angle, s32 p1, s32 p2);
extern s32 func_801345F8(s32 arg);
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
extern void func_801376E8();
extern void func_801376C8(int a0);
extern s32 D_80127524;
extern s32 D_80127528;
extern void func_80137840(s32 a0);
extern void func_80139634(void *);
extern void func_80139DC8(void);
extern s16 D_8012752E;
extern void func_801379D8(void);
extern void func_801379EC(void);
extern void func_80138BE0(s32 a0);
extern void func_80137BD8(s32 a0);
extern void func_8013A380(void);
extern void func_801379FC(void);
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
extern s32 func_80138DE0(s32 a0, s32 a1, s32 a2);
extern void func_80139B18(s32 a0);
extern void func_80138AB4(s32 a0);
extern void func_80138C30(void *a0);
extern void func_8013A9F8(s32 a0, s32 a1);
extern void func_80138D58(s32 a0, u16 a1);
extern s32 func_80014E80(s32 a0, s32 a1);
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
extern s32 D_80127548[];
extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);
extern s32 func_80139220(s32 a0);
extern void func_801391F0(void *a0);
extern void func_801392C8(void *a0);
extern void func_801395D4(void *);
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);
extern void func_801392FC(s32 arg0, s32 arg1, u8 *arg2);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
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
extern s16 D_801269F4;
extern s32 D_801269F0;
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
extern void func_80139C7C(u8 *a0);
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
extern void func_8013A860(void);
extern s32 func_8013A8BC(void);
extern void func_8013A9B4(s32 a0, s32 a1);
extern s32 func_8013A8FC(s32 arg0);
extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B204(s32 a0, s32 a1);
extern void func_8013AF20();
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern void func_8013CA14(void);
extern void func_8013CABC(void);
extern void func_8013CAE8(void);
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern void func_8013CF68();
extern void func_8013D9B0();
extern void func_8013D064(void);
extern s32 func_8013D13C(void);
extern void func_8013D164(void);
extern void func_8013D178(void);
extern void func_8013D330(void);
extern void func_8013D53C();
extern void func_8013DD68();
extern void func_8013D8FC(void);
extern void func_8013CF68(void);
extern void func_8013D3D4(int param_1, int param_2);
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
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
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
extern s32 func_8013EE10();
extern void func_8013F138(void);
extern void func_800D2624(void);
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
extern u8  D_8018B4A8[];
extern u8  D_8018B4C0[];
extern u16 D_8018B3C4[];
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
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
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
extern s32 func_80142D38(s32 *a0);
extern void func_80142BB4(s32 *a0, s32 a1, s32 a2);
extern void func_801428CC(s32 *a0);
extern void func_8014292C(int param_1);
extern void func_80142978(int param_1);
extern void func_801429C4(int param_1);
extern void func_80142A80(void);
extern void func_80142C7C(void);
extern void func_80142C84(s32 a0);
extern void func_80142C9C(s32 * arg0);
extern void func_80142B2C();
extern void func_80142DC4(int param_1);
extern void func_80142E38(int param_1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142EC0(s32 param_1);
extern void func_80142FFC(s32 *a0);
extern void func_8014305C(int param_1);
extern void func_80143188(s32 *a0);
extern int func_8001CA88(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_801431E8(s32 param_1);
extern void func_80142C9C(s32 *a0);
extern void func_801432FC(s32 *a0);
extern void func_80143390(s32 *a0);
extern void func_80143458(s32 param_1);
extern void func_8014358C(s32 param_1);
extern s32 rand(void);
extern void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143970(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80143994(s32 a0, s32 a1);
extern void func_801439C0(u8 *a0);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern void func_801439FC(s32 a0);
extern void func_80143B30(void *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_80143BDC(u16 *a0);
extern void func_80143C38(void *a0);
extern void func_80143C74(s32 a0, s32 a1);
extern void func_80143C98(void *a0);
extern void func_80143E68(void *a0);
extern void func_80143EA4(void);
extern void func_80143EAC(void);
extern void func_80143EB4(void);
extern s32 func_8004787C(s32 a0);
extern void func_80143EBC(s32 a0);
extern void func_80144054(void *a0);
extern void func_801442F8(int param_1);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80144364(int param_1);
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
extern void func_80144A98(u8 *a0);
extern void func_80144B14();
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
extern u8 D_80078EC0;
extern void func_80145BF8(void);
extern void func_80145C54(void);
extern void func_80146014(s32 a0);
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
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
extern void func_80146750();
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
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern void func_8014A1B0(s32 a0, s32 a1);
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
extern void func_80019064(void *a0);
extern s32 D_80078E98;
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
extern void func_8014CD80();
extern s32 func_8014D2A0();
extern s32 func_8014D12C();
extern void func_8014D0A4(s32 a0);
extern void func_8014D610();
extern s32 func_8014D4C0();
extern void func_8014D438(s32 a0);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2);
extern void func_8014D790(s32 a0);
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
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014ED80(struct SubED80 *a0);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern void func_8014F4C0();
extern s32 func_8014F468(void);
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern s32 func_80150170(void *a0);
extern s32 func_8014FE60();
extern void func_8014FDF4(struct S8014FDF4 *a0);
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
extern s32 func_8014F3E8();
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
extern s32 func_8014F3E8();      /* declared */
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
extern s32 func_8014A51C();
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
extern int func_80148AFC(void*);
extern s32 func_80161B18(void *);
extern s32 func_80161B84(void *);
extern u16 func_80148800(s32*);
extern s32 func_80165624(s32);
extern s32 func_801488A8(u8*);
extern void func_80154A74(s32, s32);
extern void func_8015DAC4(s32*);
extern void func_8015DE24(s32*);
extern void func_8015DA5C(s32);
extern void func_8015F948(s32*);
extern void func_800CAF14(void *);
extern void func_80154150(s32, s32);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_80149374(s32, s32);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *);
extern void func_8015C714(void *);
extern void func_801483E8(void);
extern void func_8015D738(void *arg0);
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
extern s32 func_8013C9C4(s32 *a0);
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
extern u16 func_801487F4(s32*);
extern s32 func_80149D10(s32);
extern void func_80175150(s32*);
extern void func_8016EE40(s32, s32, s32);
extern s32 func_80149744(struct S_80149744*);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32);
extern s32 func_80148E54(void *a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern void func_8015EA3C(void *arg0);
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
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
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
extern void func_801483E8();
extern s32 func_80161A60(s32 a0);
extern void func_8016130C(void *a0, s32 a1);
extern void func_80161278(void *a0);
extern s32 func_8014F3E8(s32 a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern int D_801152BC;
extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);
extern void func_80015954(s32, s32);
extern int func_80161374(int param_1, unsigned int param_2);
extern s32 func_80161488(void *a0);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_8016163C(s32 arg0, u32 arg1);
extern void func_8015F2F0(s32*);
extern s32 func_80161774(int param_1, u32 param_2);
extern void func_8014C010(int a0, int a1);
extern void func_80161D20(s32, s32);
extern int func_80161888(int param_1, unsigned int param_2);
extern s32 func_8016197C(s32 a0, s32 a1);
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
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
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
extern void func_80164418();
extern void func_80163764(s32 a0);
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
extern s32 D_80126728;
extern void func_80165CA0(void);
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
extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801670E4(s32, s32, s32, s32);
extern s32 func_80167540(s32 arg0);
extern void func_801678B4(void *a0);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(u8*);
extern void func_801678F0(s32 a0);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern int func_80029178(int);
extern void func_80168070();
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801681FC(s32 param_1);
extern void func_80168430(s32 param_1);
extern void func_80168640(s32 a0);
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
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
extern s32 func_80169228(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_801696D8(s32 a0, s32 a1);
extern void func_80169830(void *a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_80169B80(void *a0);
extern void func_80169F00(void *a0);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void func_8016A700(void *a0);
extern s32 func_80016A5C();
extern s32 func_8016A8FC(s32 a0);
extern void func_8016AB30(void *a0);
/* ==== end §8b carried decl layer ==== */


extern void func_8016B234();
extern void func_800D22E4(s32 a0);

void func_8016AE5C(s32 param_1) {
    s32 sp;

    sp = *(s32 *)(param_1 + 0x20);
    if (*(u32 *)(param_1 + 0x2C) < 6) {
        func_8016B234();
    }
    switch (*(u32 *)(param_1 + 0x2C)) {
    case 0:
        *(s16 *)(param_1 + 0xA) -= *(s32 *)(param_1 + 0x1C);
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        if (*(s32 *)(param_1 + 0x1C) != 0) {
            if ((*(s32 *)(param_1 + 0x1C) & 3) == 1) {
                *(s16 *)(param_1 + 0x26) += 1;
            }
            return;
        }
        *(s16 *)(param_1 + 0x24) = 0xFF;
        *(s32 *)(param_1 + 0x1C) = 8;
        *(s16 *)(param_1 + 2) += 1;
        return;
    case 1:
    case 5:
        func_800D22E4(param_1);
        *(s32 *)(param_1 + 0x14) += 0x18000;
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
        *(s16 *)(param_1 + 0xA) -= *(s32 *)(param_1 + 0x1C);
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        if (*(s32 *)(param_1 + 0x1C) == 0) {
            if (*(u32 *)(param_1 + 0x2C) < 6) {
                *(s16 *)(param_1 + 0x24) = 0xC0;
                *(s32 *)(param_1 + 0x1C) = 8;
            } else {
                *(u8 *)(sp + 0x26) = 0xC0;
                *(u8 *)(sp + 0x25) = 0xC0;
                *(u8 *)(sp + 0x24) = 0xC0;
                *(s32 *)(param_1 + 0x1C) = 0xC;
            }
            *(s16 *)(param_1 + 2) += 1;
        }
        break;
    }
}

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016B114);



extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80016ED4(void *a0);


void func_8016B234(s32 param_1) {

    extern u8 D_8018D570;
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
        prim.code = (&D_8018D570)[*(s32 *)(param_1 + 0x2c)];
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

    extern void (*D_8018D5F4[])(void);
    D_8018D5F4[*(u16 *)((s32)a0 + 0x2)]();
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

    extern int D_801F5360;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801F5360);
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

    extern s16 D_8018D5E8[];
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
    psVar5 = D_8018D5E8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}



// @class: schedule
// @stuck: none — MATCH (94/94 ins, match_one relocation-masked)
//
// Exemplar of the 138-member h_seq family. The whole crack was ONE statement-order
// lever in the tail: the target's post-func_80015978 fix-up runs
//   v[2].x += off.x;  v[2].y += off.y;  v[0].c = 3;
// (the `c = 3` store LAST). Writing `c = 3` between the two v[2] RMWs — the order the
// Ghidra-C literally prints, and what every prior draft copied — costs 12 mismatches:
// gcc hoists the `li 3` into the load-delay window, which pushes v[2].x into $v1 and
// the off.x temp into $a0, and then the `addu $a0,$s1,$zero` arg copy can no longer be
// scheduled early enough to become the base register of the v[2]/v[0].c stores.
// With `c = 3` last, the arg copy births at the v[2].x/v[2].y boundary (idx 76) exactly
// as the target does, and the mixed $s1-load / $a0-store addressing falls out for free.
// (§67-adjacent: the copy PLACEMENT was the root cause — but here plain statement order
// reaches it, no `__asm__` launder and no register pin needed. Prior notes calling this a
// regalloc tie-break and pinning $a0 were chasing the consequence, not the cause.)
//
// Everything else follows the Ghidra-C: `Prim *p = &prim` (one alias only — a second
// pointer name splits the pseudo and breaks the $s1 base), the `q++` post-increment
// running pointer over the 8-byte table rows, and the ((param_4 << 16) >> 14) byte-offset
// index into D_8018D5D0 (sll 16 / sra 14).


             /* 0x28 */


               /* the 8-byte D_8018D5D0[] row */

extern void func_80013CFC(s32 a0, s32 a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8001739C(void *a0);

/* Def sig is deliberately (s32,s32,s32,s32) — byte-identical to the (int,unsigned,short,int)
 * spelling, and IDENTICAL to this TU's own caller decl `extern void func_8016B6BC(s32,s32,s32,s32);`
 * (ov_SC01_077_jr_8016AB6C.c), so there is no §73/§57 def-side self-decl conflict to reconcile. */
void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {

    extern int D_8018D5D0;
    int iVar1;
    M8_8016B6BC *q;
    Prim_8016B6BC prim;
    Prim_8016B6BC *p = &prim;
    DVec_8016B6BC off;
    unsigned int v;
    unsigned int c;

    q = (M8_8016B6BC *)*(int *)((int)&D_8018D5D0 + ((param_4 << 0x10) >> 0xe));
    p->color = 0x50000000;
    c = (unsigned int)param_2;
    v = 0x20;
    if (c < 0x20) {
        v = c;
    }
    if (*(int *)(param_1 + 0x2c) == 0) {
        c = c | (v << 0x10 | v << 8);
    } else {
        c = c << 8 | v << 0x10 | v;
    }
    p->combined = c;
    iVar1 = (int)(short)param_3;
    p->z1c = 0;
    p->z20 = 0;
    func_80013CFC(iVar1, (int)q++, &p->v[0]);
    func_80013CFC(iVar1, (int)q++, &p->v[1]);
    func_80013CFC(iVar1, (int)q, &p->v[2]);
    func_80015978(param_1 + 4, (s32 *)&off);
    p->v[0].x += off.x;
    p->v[0].y += off.y;
    p->v[1].x += off.x;
    p->v[1].y += off.y;
    p->v[2].x += off.x;
    p->v[2].y += off.y;
    p->v[0].c = 3;
    func_8001739C(p);
}



// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_8018D62C[];
    extern unsigned short D_8018D634[];
    extern unsigned short D_8018D63C[];
    extern unsigned char D_801F5368[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801F5368 + param_2 * 0x40);
    puVar3 = D_8018D62C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_8018D634[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_8018D63C[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016B984);


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801F5360;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801F5360, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_8018D644[])(void);
    D_8018D644[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BBE0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BCC0);

extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801F549C;
    extern M2C_UNK D_801F54A0;
    extern u8 D_801F549D;
    extern u8 D_801F549E;
    extern u8 D_801F54A1;
    extern u8 D_801F54A2;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801F549C);
    if (*p1 != 0) *p1 -= 4;
    if (D_801F549D != 0) D_801F549D -= 4;
    if (D_801F549E != 0) D_801F549E -= 4;
    p2 = &(*(u8 *)&D_801F54A0);
    if (*p2 != 0) *p2 -= 4;
    if (D_801F54A1 != 0) D_801F54A1 -= 4;
    if (D_801F54A2 != 0) D_801F54A2 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BEA0);

DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BF50);


extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801F5428;
    func_8016BFD0(a0, a1, a2, a3, &D_801F5428);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016BFD0);



void func_8016C14C(void *a0) {

    extern void (*D_8018D674[])(void);
    D_8018D674[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016C188);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016C2C4);

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


extern s32 D_8011D030;
extern void func_80016714(void *a0, s32 a1);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_80048EAC(void *m0, void *m1);
extern void func_800D23D0(void *a0);
extern void func_801465C0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {
    extern s32 VectorNormalSS(void *, void *);
    extern short func_8016CF04();
    extern u8 D_801F54B8[];
    extern u8 D_801F5578;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_801F54B8[1] = 0xff;
        D_801F54B8[2] = 0x10;
        D_801F54B8[0] = 0x10;
        D_801F54B8[6] = 0;
        D_801F54B8[5] = 0;
        D_801F54B8[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_801F54B8, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801F5578, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        ((void(*)(s32, void *))func_8001CD9C)(iVar5b, D_801F54B8);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = rand();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}


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
    extern Slot_998 D_801F5578[];

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
            if (D_801F5578[i].f0 == 0) {
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
        D_801F5578[i].f0 = 1;
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

    extern void (*D_8018D67C[])(void);
    D_8018D67C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_80017758(void *a0, void *a1);
short func_8016CBC0(void)
{

    extern Blk20 D_800AE620;

    extern Blk_8016CBC0 D_801F5578[];
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
    blk = &D_801F5578[i];
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


extern void func_800D23D0(void *a0);
extern s32 func_8016C49C();
extern void func_8016D5EC(s32 *a0);


/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04 D_801F5578[];

    Blk_8016CF04 *p = &D_801F5578[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}




void func_8016D19C(void *a0) {

    extern void (*D_8018D698[])(void);
    D_8018D698[*(u16 *)((s32)a0 + 0x2)]();
}







   /* 8 bytes */
                 /* 32 bytes */


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void*);
extern void func_80147324(int a);
extern int  rand(void);

void func_8016D1D8(int param_1) {

    extern u8 D_801F54F8[];
    extern u8 D_801F5538[];
    int iVar5;
    int iVar2;
    u16 uVar1;
    unsigned int uVar3;
    short sVar4;
    SVEC_L1 sv;
    MTX_L1 mtx;

    iVar5 = *(int *)(param_1 + 0x34);
    if (*(int *)(param_1 + 0x2c) == 0) {
        D_801F54F8[1] = 0xE0;
        D_801F54F8[2] = 0xE0;
        D_801F54F8[0] = 0xE0;
        D_801F54F8[6] = 0;
        D_801F54F8[5] = 0;
        D_801F54F8[4] = 0;
        iVar5 = ((int (*)(void))func_801465C0)();
        if (iVar5 != 0) {
            int pp;
            *(int *)(param_1 + 0x20) = iVar5;
            ((void (*)(void *, int))func_800233CC)(D_801F54F8, 0x28);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar5, D_801F54F8);
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
        D_801F5538[1] = 0xE0;
        D_801F5538[2] = 0x20;
        D_801F5538[0] = 0x20;
        D_801F5538[5] = 0;
        D_801F5538[6] = 0;
        D_801F5538[4] = 0;
        iVar2 = ((int (*)(void))func_801465C0)();
        if (iVar2 != 0) {
            *(int *)(param_1 + 0x20) = iVar2;
            ((void (*)(void *, int))func_800233CC)(D_801F5538, 0x18);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar2, D_801F5538);
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

    extern void (*D_8018D6A0[])(void);
    D_8018D6A0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016D5EC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016D64C);


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void *);

void func_8016D688(int param_1)
{

    extern unsigned char D_801F54F8[];
    int iVar2;
    int iVar3;

    D_801F54F8[1] = 0xe0;
    D_801F54F8[2] = 0xe0;
    D_801F54F8[0] = 0xe0;
    D_801F54F8[6] = 0;
    D_801F54F8[5] = 0;
    D_801F54F8[4] = 0;
    iVar2 = ((int (*)(void))func_801465C0)();
    if (iVar2 != 0) {
        *(int *)(param_1 + 0x20) = iVar2;
        ((void (*)(void *, int))func_800233CC)(D_801F54F8, 0x28);
        func_8001CD9C(iVar2, D_801F54F8);
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016D778);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016D848);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_8018D708[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_8018D708[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016DB34);

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */



extern s32 D_8011D030;
extern s16 D_801F5B98;
extern s16 D_801F5B9C;
extern u8 D_8018D710[];
extern u8 D_8018D71C[];

extern void func_80149374(s32 a0, s32 a1);
extern s32 func_801619D0(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8016DC20(s16 *param_1) {
    u16 *psVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s16 i;
    s16 sp[6];

    i = 0;
    psVar1 = (u16 *)&D_8011D030;
    iVar4 = *(s32 *)((u8 *)param_1 + 0x34);
    do {
        if ((psVar1 != (u16 *)param_1) && (*psVar1 == 0x34)) goto end;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80149374(iVar4, (s32)param_1 + 4);
    iVar2 = func_801619D0((void *)iVar4);
    i = 0;
    if (iVar2 == 0) goto ddb0;
    psVar1 = (u16 *)&D_8011D030;
    do {
        if (*psVar1 == 0x11) goto ddb0;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80146A6C(0x11, param_1, *(s16 *)((u8 *)param_1 + 6),
                  (s16)(*(u16 *)((u8 *)param_1 + 0xa) - 8),
                  *(s16 *)((u8 *)param_1 + 0xe), 0, 0);
    sp[0] = *(u16 *)((u8 *)param_1 + 6);
    sp[1] = *(u16 *)((u8 *)param_1 + 0xa);
    sp[2] = *(u16 *)((u8 *)param_1 + 0xe);
    func_800D20C0(&sp[0], &sp[4], 0);
    sp[5] = 0;
    func_800D23D0(&sp[4]);
    i = 0;
    do {
        iVar3 = func_80146A6C(0x12, param_1, *(s16 *)(iVar4 + 6),
                              *(s16 *)(iVar4 + 0xa), *(s16 *)(iVar4 + 0xe),
                              i, 0);
        if (iVar3 != 0) {
            *(u16 *)(iVar3 + 0x12) = sp[4];
            *(u16 *)(iVar3 + 0x16) = sp[5];
            *(u16 *)(iVar3 + 0x1a) = 0;
        }
        i = i + 2;
    } while (i < 3);
    goto end;
ddb0:
    if (((D_801F5B98 != *(s16 *)(iVar4 + 6)) || (D_801F5B9C != *(s16 *)(iVar4 + 0xe))) &&
        (iVar2 = func_800D21C4((s32)param_1, D_8018D710, 0x18), iVar2 != 0)) {
        D_801F5B98 = *(u16 *)(iVar4 + 6);
        D_801F5B9C = *(u16 *)(iVar4 + 0xe);
        func_800D1FC8((s32)param_1, 7);
        *(s32 *)((u8 *)param_1 + 0x20) = iVar2;
        *(u16 *)(iVar2 + 0x1a) = 0x3000;
        *(u16 *)(iVar2 + 0x18) = 0x3000;
        *(u8 *)(iVar2 + 0x26) = 0xff;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        func_80128EA8(iVar2, (s32)param_1 + 0x24, (s32)D_8018D71C);
        ((s32 (*)(void *, void *))func_80128ED8)((void *)iVar2, (void *)((s32)param_1 + 0x24));
        *(u16 *)((u8 *)param_1 + 2) = *(u16 *)((u8 *)param_1 + 2) + 1;
        return;
    }
end:
    ((void (*)(s16 *))func_80146C3C)(param_1);
}




void func_8016DEA4(void *a0) {

    extern void (*D_8018D73C[])(void);
    D_8018D73C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016DEE0);



void func_8016DF20(void *a0) {

    extern void (*D_8018D744[])(void);
    D_8018D744[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016DF5C);

DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E2E8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E358);

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_8018D798[])(void);
    D_8018D798[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E5F4);

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E7C8);

DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E95C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016E9EC);


// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_8018D7CC[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_8018D7CC[param_1->f2];
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

    extern u8 D_8018D7BC[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_8018D7BC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_8018D7CC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_8018D7CC[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_8018D7CC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016EC0C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016ED6C);

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


DEFINE_func_8016EFC8()  /* dedup: shared engine-core @0x8016EFC8 (src/shared) */

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_8016F0E4);

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */



// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_8018D7E8;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018D7E8;
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

    extern void (*D_8018D860[])(void);
    D_8018D860[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_8018D868[])(void);
    D_8018D868[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_8018D870[])(void);
    D_8018D870[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_8018D878[])(void);
    D_8018D878[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_8018D880[])(void);
    D_8018D880[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_8018D888[])(void);
    D_8018D888[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_8018D894[])(void);
    D_8018D894[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_8018D8A0[])(void);
    D_8018D8A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_8018D8AC[])(void);
    D_8018D8AC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_8018D8BC[])(void);
    D_8018D8BC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_8018D8CC[])(void);
    D_8018D8CC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_8018D8D4[])(void);
    D_8018D8D4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_8018D8DC[])(void);
    D_8018D8DC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_8018D8E4[])(void);
    D_8018D8E4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_8018D8EC[])(void);
    D_8018D8EC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_8018D8F4[])(void);
    D_8018D8F4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_8018D8FC[])(void);
    D_8018D8FC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_8018D904[])(void);
    D_8018D904[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_8018D90C[])(void);
    D_8018D90C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_8018D914[])(void);
    D_8018D914[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_8018D91C[])(void);
    D_8018D91C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_8018D924[])(void);
    D_8018D924[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_8018D92C[])(void);
    D_8018D92C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_8018D934[])(void);
    D_8018D934[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80170CF0);



void func_80170D68(void *a0) {

    extern void (*D_8018D93C[])(void);
    D_8018D93C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_8018D944[])(void);
    D_8018D944[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_8018D94C[])(void);
    D_8018D94C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_8018D954[])(void);
    D_8018D954[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_8018D95C[])(void);
    D_8018D95C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_8018D964[])(void);
    D_8018D964[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_8018D96C[])(void);
    D_8018D96C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_8018D974[])(void);
    D_8018D974[*(u8 *)((s32)a0 + 0x216)]();
}


// @class: struct
// @stuck: none — MATCH (three 16-byte struct copies into a loaded dst pointer)



DEFINE_func_8017129C()  /* dedup: shared engine-core @0x8017129C (src/shared) */


DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_8018D97C[])(void);
    D_8018D97C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801718AC);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80171B4C);

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

    extern void (*D_8018D98C[])(void);
    D_8018D98C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */




s32 func_801728E4(void *a0) {

    extern void (*D_8018D998[])(void);
    D_8018D998[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */




s32 func_801729F0(void *a0) {

    extern void (*D_8018D9A4[])(void);
    D_8018D9A4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */




s32 func_80172B44(void *a0) {

    extern void (*D_8018D9B4[])(void);
    D_8018D9B4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80172C50);



void func_80172CA0(void *a0) {

    extern void (*D_8018D9C0[])(void);
    D_8018D9C0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */




s32 func_80172DAC(void *a0) {

    extern void (*D_8018D9CC[])(void);
    D_8018D9CC[*(u8 *)((s32)a0 + 0x214)]();
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

    extern void (*D_8018D9D8[])(void);
    D_8018D9D8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */




s32 func_8017319C(void *a0) {

    extern void (*D_8018D9E4[])(void);
    D_8018D9E4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_8018D984;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_8018D984);
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_8018D9F0[])(void);
    D_8018D9F0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */




s32 func_801736FC(void *a0) {

    extern void (*D_8018DA04[])(void);
    D_8018DA04[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */




s32 func_801737E8(void *a0) {

    extern void (*D_8018DA10[])(void);
    D_8018DA10[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */




s32 func_8017390C(void *a0) {

    extern void (*D_8018DA1C[])(void);
    D_8018DA1C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80173A60);



void func_80173B4C(void *a0) {

    extern void (*D_8018DA2C[])(void);
    D_8018DA2C[*(u8 *)((s32)a0 + 0x214)]();
}


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

    extern void (*D_8018DA4C[])(void);
    D_8018DA4C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */




s32 func_80174384(void *a0) {

    extern void (*D_8018DA58[])(void);
    D_8018DA58[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */




s32 func_80174474(void *a0) {

    extern void (*D_8018DA64[])(void);
    D_8018DA64[*(u8 *)((s32)a0 + 0x214)]();
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

    extern void (*D_8018DA70[])(void);
    D_8018DA70[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */




s32 func_80174888(void *a0) {

    extern void (*D_8018DA78[])(void);
    D_8018DA78[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */




s32 func_8017496C(void *a0) {

    extern void (*D_8018DA80[])(void);
    D_8018DA80[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (pins $s2=D_80126B5E, $s1=D_80126B66 + Buf_c1 struct local; ported from the banked ov_SC01_000 exemplar)



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32, s32, s32);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);


s32 func_801749C8(s32 param_1)
{
    Buf_c1 buf;
    register s32 iVar5 __asm__("$18");
    register u32 iVar4 __asm__("$17");

    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    iVar4 = (u16)D_80126B66;
    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + (iVar5 = (s16)D_80126B5E);
    *(s32 *)(param_1 + 0x4c) = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    func_80049CAC(param_1 + 0x18, (s32)&buf);

    buf.f14 = *(s16 *)(param_1 + 0x28) + iVar5;
    buf.f18 = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    buf.f1c = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    buf.f20 = 0;
    buf.f22 = 0;
    buf.f24 = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&buf, (s32)&buf.f20, (s32)&buf.f28);

    *(s32 *)(param_1 + 0x3c) = buf.f28;
    *(s32 *)(param_1 + 0x40) = buf.f2a;
    *(s32 *)(param_1 + 0x44) = buf.f2c;
}


DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_8018DA84[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_8018DA84[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_8018DA84[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (123 ins)
//
// Sibling of func_801749C8 (already banked in this same TU, ~line 8640): identical 8-call
// clamp/approach prologue and identical trailing MATRIX+SVECTOR / func_8012F14C rotate.
// Two deltas vs that sibling: the single func_80049CAC(p+0x18,&m) is expanded inline here into
// the 4-call matrix build (func_80013F3C / func_800123F0 / func_80012558 / func_800126C4), and
// param_2 is a *short* (hence the sll/sra 16 on $s1) folded into the func_80012558 angle & 0xFFF.
//
// THE ONLY NON-OBVIOUS LEVER (regalloc-order, +2 ins = the $s2 save/restore pair):
//   The target keeps &D_80126940 materialized in a callee-saved reg ($s2: lui+addiu once, then
//   `lh 0($s2)` on BOTH sides of the 4 matrix calls), while D_80126942/44 are re-emitted as
//   lui + `lh %lo(...)` at each of their two uses. Reading D_80126940 as a plain scalar makes gcc
//   treat all three uniformly (121 ins, no $s2) -> LENGTH-DRIFT -2. Taking its address ONCE into
//   a local pointer (`s16 *pv = &D_80126940;`) forces the address into a call-crossing pseudo,
//   which lands in $s2. No `register __asm__` pin is needed.
//
// BANKING NOTES (this draft is written to drop straight into
// src/ov_SC07_006/ov_SC07_006_jr_8015C32C.c):
//   * Every callee decl below is VERBATIM the one the TU already carries at file scope —
//     func_80012ABC (engine_core.h:28579 / TU:8631), func_80012C6C (TU:1149),
//     func_80013F3C/func_80012558/func_800126C4/func_800123F0 (TU:1152-1155),
//     func_8012F14C (TU:399).  The s16-returning calls therefore go through the
//     `((s16 (*)(s32,s32,s32))f)(...)` func-ptr cast idiom already used by func_801749C8,
//     so the canonical s32 prototypes are kept and NEVER redeclared.
//   * D_80126940/42/44 are already `extern s16` at TU:160-162 — drop the three externs below.
//   * MATRIX / SVECTOR are locally-unique names (== MATRIX / SVECTOR layouts) so
//     they cannot collide with engine_types.h; they may be kept as-is or swapped for
//     MATRIX / SVECTOR when banking.
//   * THE OWN-SIGNATURE BLOCKER (the layer under the func_80012ABC one): the TU expands
//     DEFINE_func_80174C80() at line 8702, and that macro carries
//         extern s32 func_80174CB0(s32, s32);
//     So this function MUST be defined `s32 func_80174CB0(s32, s32)` — a `void`/`s16 param_2`
//     draft compiles fine standalone but dies with "conflicting types for `func_80174CB0'"
//     in the TU. The s16-ness of param_2 (the sll/sra 16 at 80174DDC) is recovered by the
//     explicit `(s16)param_2` cast at the func_80012558 use site; byte-identical either way.
//
// VERIFIED IN-TU: appending this file to a copy of the real TU (with the INCLUDE_ASM line
// removed) compiles cc1-clean (rc=0, same as baseline) and the resulting object's
// func_80174CB0 is 123/123 instructions with 0 diffs vs the target .s.
#include "common.h"

/* --- standalone-only scaffolding (bank-safe: names are unique to this function) --- */

DEFINE_func_80174CB0()  /* dedup: shared engine-core @0x80174CB0 (src/shared) */


DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */




s32 func_80174F28(void *a0) {

    extern void (*D_8018DA8C[])(void);
    D_8018DA8C[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_8018DA94[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_8018DA94[v1](arg0);
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
    extern void (*D_8018DA9C[])(s32);
    s32 i = D_80078EC0 - 1;

    D_8018DA9C[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_8018DAB4[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_8018DAB4 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


// @class: struct
// @stuck: none — MATCH (67 ins). Base pointer `p=&D_8011F7A8` shares $t0 for offset-0
// store + p+0x48 struct-assign dest + p+0xE0 call arg; field stores 1/6/0xC..0x16 are
// separate globals (LO_SUM); 152-byte struct assign -> gcc block-move (16B loop + 8B tail);
// &D_800B9A02 held in $s0 across the calls via an explicit `s16 *q` pointer local
// (lh for signed read, *(u16*)q for the lhu ^1 read).
#include "common.h"

 /* 0x98 = 152 bytes */

DEFINE_func_80175308()  /* dedup: shared engine-core @0x80175308 (src/shared) */


DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801754A8);


extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8();

void func_8017553C(s32 *param) {

    extern void (*D_8018DC04[])();
    D_8018DC04[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */


DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */


DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8();

void func_80175690(s32 *param) {

    extern void (*D_8018DC10[])();
    D_8018DC10[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80175820);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801758FC);

// @class: schedule
// @stuck: none — MATCH (56 ins)
#include "common.h"

extern u8 D_8011F7B1;
extern u8 D_8011F7A8;
extern s16 D_800B9A02;

typedef struct { u32 *f0; s32 pad[4]; } S_AE7BC;   /* size 0x14 */
typedef struct { s32 g0; s32 pad[2]; } S_AF634;    /* size 0x0C */
extern S_AE7BC D_800AE7BC[];
extern S_AF634 D_800AF634[];

s32 func_801759D8(void)
{
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;

    if (D_8011F7B1 != 0) {
        return;
    }

    q = (u16 *)&(*(u16 *)&D_800B9A02);

    ptr = D_800AE7BC[*q].f0;
    old = ptr[1];
    ptr[1] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x40) & 0xffffff);
    __asm__("" ::: "memory");

    p2 = *(u32 **)(p + *q * 4 + 0x38);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    __asm__("" ::: "memory");

    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x38) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x40) - t) >> 2);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80175AB8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80175DA8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80176144);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80176218);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


/* de-macroized: per-overlay-local decl for func_801778A8 (byte-true sig); do NOT re-macroize */
    extern u32 func_801783D0(s32 a0, s32 a1);
    extern void func_801778A8(int, unsigned int, short, short);
    extern u16 D_8011F82C;
    extern u16 D_8011F82A;
    void func_80176FF4(s32 a0) {
        s32 v0;
        a0 += 0x50;
        func_801778A8(a0, (s16)func_801783D0(D_8011F82C, 4), 3, 0xFF);
        a0 += 0x3C;
        func_801778A8(a0, (s16)func_801783D0(D_8011F82A, 4), 3, 0xFF);
        a0 += 0x3C;
        *(s16 *)(a0 + 0xC) = (u32)(D_8011F82C * 10355) >> 15;
        a0 += 0x14;
        v0 = ((s32)(D_8011F82A * 10355) << 1) >> 16;
        *(s16 *)(a0 + 0xC) = v0;
        *(s16 *)(a0 + 0x20) = v0 + 2;
    }  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


/* de-macroized: per-overlay-local decl for func_801778A8 (byte-true sig); do NOT re-macroize */
    extern u32 func_801783D0(s32 a0, s32 a1);
    extern void func_801778A8(int, unsigned int, short, short);
    extern u16 D_8011F830;
    extern u16 D_8011F82E;
    void func_80177340(s32 a0) {
        s32 v0;
        a0 += 0x50;
        func_801778A8(a0, (s16)func_801783D0(D_8011F830, 4), 3, 0xFF);
        a0 += 0x3C;
        func_801778A8(a0, (s16)func_801783D0(D_8011F82E, 4), 3, 0xFF);
        a0 += 0x3C;
        *(s16 *)(a0 + 0xC) = (u32)(D_8011F830 * 10355) >> 15;
        a0 += 0x14;
        v0 = ((s32)(D_8011F82E * 10355) << 1) >> 16;
        *(s16 *)(a0 + 0xC) = v0;
        *(s16 *)(a0 + 0x20) = v0 + 2;
    }  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


DEFINE_func_801775E0()  /* dedup: shared engine-core @0x801775E0 (src/shared) */


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


#include "common.h"

DEFINE_func_801777BC()  /* dedup: shared engine-core @0x801777BC (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH
void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4)
{
    register unsigned int uVar1 __asm__("$2");
    register unsigned int nib __asm__("$3");
    int iVar2;
    register int im1 __asm__("$11");
    int p4;
    register char *p __asm__("$7");
    short iVar4;
    unsigned short uVar5;
    register unsigned int mask __asm__("$12");

    uVar5 = 0x100;
    iVar2 = (int)param_3;
    iVar4 = 0;
    if (0 < iVar2) {
        im1 = iVar2 - 1;
        p4 = (int)param_4;
        mask = ~0x100;
        p = (char *)(param_1 + 0xc);
        do {
            uVar1 = (param_2 << 16) >> 28;
            nib = uVar1;
            if (((uVar1 != 0) || ((int)iVar4 == im1)) ||
                ((int)iVar4 == p4)) {
                uVar5 = 0;
            }
            param_2 = param_2 << 4;
            *p = (char)(nib * 8 + 8);
            *(unsigned short *)(p - 2) = uVar5 | (*(unsigned short *)(p - 2) & mask);
            iVar4 = iVar4 + 1;
            p = p + 0x14;
        } while ((int)iVar4 < iVar2);
    }
    return;
}



DEFINE_func_80177940()  /* dedup: shared engine-core @0x80177940 (src/shared) */

// @class: iv-combine
// @stuck: none — MATCH (34 ins). Cracked the cookbook's stubbed IV-combine divergence.
//
// Three levers, all required:
//  1. IV-COMBINE ANCHOR (the stubbed blocker): the byte-RMW split gcc into 2 IVs (anchor
//     0x1e). Fix per cookbook §20 anchor-steering: keep `base` a biv NOT dereferenced at +0
//     (index as base[0x20] / base+0x1e, all positive-offset givs so the biv eliminates + the
//     givs merge to ONE reduced reg), and write the BYTE store LAST so record_giv makes it
//     giv_array[0] -> anchor flips to p+0x20, hw reaches it at displacement -2. (The hw
//     load+store givs at -2 combining is what raised benefit past the reduce threshold in the
//     walked-pointer form; the all-giv merge sidesteps it.)
//  2. REGISTER-`and` (not `andi 0xfeff`): load the hw into an explicit `int t` first, so gcc
//     loses the "16-bit from lhu" fact and hoists 0xfffffeff into t1 -> `and a0,a0,t1`.
//  3. THE COALESCED-AWAY MOVE (`addu v1,v0,zero` in the branch delay slot): gcc naturally
//     coalesces the nibble straight into $v1. Force the target's copy with an explicit
//     $v0-pinned condition var `c` and $v1-pinned byte var `b` doing `b = c` — c tests in the
//     bnez, b survives to the byte store, the move lands in the delay slot.

DEFINE_func_80177AD4()  /* dedup: shared engine-core @0x80177AD4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80177B5C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80177DA8);

DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80178004);

DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_801F49E4;
    func_8001534C(2, &D_801F49E4, 0x80, 0x88, 0, 0);
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

    extern int D_8018DC50;
    extern int D_8018DC5C[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_8018DC50);
        }
        ((void (*)(int, int))func_80131E00)(p, D_8018DC5C[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern int func_801789AC(void);

int func_80178970(void)
{

    extern s16 D_801F62F8;
    register int r __asm__("$2");
    int v;

    v = func_801789AC();
    r = 0;
    if (v != 0)
        r = D_801F62F8 == 0;
    return r;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_801789AC);

extern void func_8017435C(void);
extern void func_801746A4(void);

// @class: struct
// @stuck: none — MATCH (pointer var forces &(*(int *)&D_8018DD48) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_8018DD48;

    int *p = &(*(int *)&D_8018DD48);
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
    extern int D_8018DD48;

    int *p = &D_8018DD48;
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
    extern short D_801F636C;
    extern int D_801F5FF8;
    extern short D_801F6008;
    extern short D_801F6004;
    extern short D_801F6000;
    extern short D_801F5FFC;
    extern int D_801F6214;
    extern int D_801F6010;
    extern s16 D_801F5FF0;
    extern short D_801F5FE8;
    extern short D_801F5FEC;
    extern int D_801F62C8;
    extern unsigned int D_801F6060;
    extern unsigned short D_801F5FE6;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_801F6060;
    D_801F636C = 0;
    D_801F5FF8 = 0;
    D_801F6008 = 0;
    D_801F6004 = 0;
    D_801F6000 = 0;
    D_801F5FFC = 0;
    D_801F6214 = 1;
    D_801F6010 = 0;
    (*(short *)&D_801F5FF0) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_801F5FE6;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_801F5FE8 = 0;
    D_801F5FEC = 0;
    ((void (*)(int *, int))func_80016714)(&D_801F62C8, 0x14);
    func_8017B1D8();
}


extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);

void func_80178CBC(s32 arg0, s32 arg1) {

    extern s32 D_801F5BE0;
    extern short D_801F636C;
    D_801F5BE0 = arg1;
    do {
        func_80178D40(arg0, D_801F5BE0);
    } while (D_801F636C == 3);
}



extern void func_80174714(void);

void func_80178D18(void) {

    extern short D_801F636C;
    D_801F636C = 0;
    func_80174714();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006_jr_8016AE5C", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179b28 (src/shared) */
