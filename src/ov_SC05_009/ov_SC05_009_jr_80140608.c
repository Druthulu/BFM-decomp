#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */
   /* size 8, alignment 1 -> unaligned copy */
              /* 0x5C copy unit, align 4 */
  /* -> frame 0xA0 (gcc adds 0x10 for the struct-copy) */
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
extern s32 D_801945F0;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_8017ED5C[])(void);
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
extern s32 D_80195754;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_80196BD8;
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
extern int D_801945F0;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017EA98)();
extern s16 (*D_8017EA9C)();
extern M2C_UNK (*D_8017EAA4)();
extern s32 (*D_8017EAA8)();
extern s32 D_80195750;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_801945F4;
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
extern M2C_UNK D_8017EDF0;
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
extern s32   D_801822D4;
extern s16 D_801270C4;
extern u16   D_801274E4[];
extern s32   D_8011DB08;
extern s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];
extern void func_8012CBA4(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern s32 func_8012CC88(s32 a0, s32 a1, s32 a2);
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
extern M2C_UNK D_8017EE08;
extern M2C_UNK D_8017EE10;
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
extern int D_8017EE18;
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
extern unsigned char D_8017EE34[];
extern void func_8012F828(int param_1);
extern void func_80131340(s32 a0);
extern void func_8012F87C(s32 a0);
extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern u8 D_8017EE40[];
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
extern void (*D_8017EE54[])(void);
extern void func_80130D0C(void *a0);
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_8017EEA4[];
extern s16 D_8017EED4[];
extern s16 D_8017EF34[];
extern s16 D_8017EF3C[];
extern s16 D_8017EF5C[];
extern void func_80130D48(s32 arg0);
extern void func_80131170(s32 p, s32 b, s32 c);
extern s32 func_801312D0(s32 param_1, void *param_2);
extern void func_8002A04C(s32 a0);
extern void func_801319E0(s32 arg0);
extern s32 func_80131CF4(s32 a0);
extern void (*D_8017EF94[])(struct S80131E00 *a0);
extern void func_80131E38(u8 *a0);
extern void func_80131E7C(s32 a0);
extern void func_80131EE4(void);
extern void (*D_8017EFEC[])(void);
extern void func_80131EEC(void *a0);
extern void (*D_8017F034[])(void);
extern void func_80131F28(void *a0);
extern void (*D_8017F03C[])(void);
extern void func_80131F64(void *a0);
extern void (*D_8017F044[])(void);
extern void func_80131FA0(void *a0);
extern void (*D_8017F04C[])(void);
extern void func_80131FDC(void *a0);
extern void func_801320D0(void);
extern void func_8001C214(int, int);
extern int D_8017EFF4;
extern void func_801320D8(int param_1);
extern s32 func_80132144(s32 param_1);
extern int D_8017F014;
extern void func_801321B0(int param_1);
extern int D_8017F024;
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
extern s32 D_801957C0;
extern s32 D_801957C4[];
extern int D_801957C8;
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
extern u8 D_8017F058;
extern u8 D_8017F054;
extern s16 *D_8017F05C;
extern u8 D_8017F060;
extern int D_801957C0;
extern u16 D_801957D0;
extern int func_80134A74(int, s16, s16, int);
extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);
extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80136334(void *arg0, s32 arg1, s32 arg2);
extern s32 func_80136824(s32 arg0, s32 arg1, s32 arg2);
extern s16 *D_8017F05C;   /* holds a pointer value (*(u16**)&D_8017F05C) */
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80136C3C(void);
extern void func_80136C1C(void);
extern void func_80136C44(void);
extern void func_80136C4C(void);
extern void (*D_8017F070[])(void);
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
extern int D_8017F0C4;
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
extern void func_80138948(void *a0);
extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2);
extern void func_80138B88(s32 a0);
extern void func_8013895C(s32 a0);
extern s16 D_80127540[4];
extern s32 func_80139D04(s32 a0, s32 a1);
extern s32 func_80138DE0(s32 a0, s32 a1, s32 a2);
extern void func_80139B18(s32 a0);
extern void func_80138AB4(s32 a0);
extern void (*D_8017F0C8[])(void);
extern void func_8013A9F8(s32 a0, s32 a1);
extern void func_80138D58(s32 a0, u16 a1);
extern s32 func_80014E80(s32 a0, s32 a1);
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
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
extern u8 D_8017F10C;
extern u8 D_8017F150;
extern void GsSortSprite(void *a0, u8 *a1, s32 a2);
extern void func_801397B0(s32 arg0);
extern void func_8013A8B0(s32 *a0);
extern void func_80139914(s32 arg0);
extern u16 D_80126A08;
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
extern void func_80138C30(void *a0);
extern void func_8013A2BC(s32 a0);
extern void func_8013A378(void);
extern u8 D_8011DA80[];
extern void func_8013A530();
extern void func_8013A448(void *a0);
extern void func_8013A4C4(struct S8013A4C4 *a0);
extern void func_8013A380(void);
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
extern s32 D_800A5E60;
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
extern s16 D_800D45F4[];   /* src0 (flat: [2*i]=x, [2*i+1]=y) */
extern u8  D_8017F194[];   /* sign table, alt (when a1 < 0xC00) */
extern void func_8013AD38(void *flag, s32 a1, void *out2, void *out3);
extern void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4);
extern s16 D_8017F20C, D_8017F20E, D_8017F210, D_8017F212, D_8017F214, D_8017F216;
extern u16 D_800D45F6;
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
extern s32 D_80195838;
extern s32 D_801269D4;
extern s32 D_801269C8;
extern M2C_UNK D_80062BC0;
extern s8 D_8019583C;
extern s8 D_8019583D;
extern void func_8013C9C4(void * arg0);
extern s32 D_8019585C;
extern s32 D_80195850;
extern s32 D_80195854;
extern s32 D_80195860;
extern void func_8013CABC(void);
extern s32 D_80195858;
extern void func_8013CAE8(void);
extern s32 D_80195888;
extern s32 D_8019588C;
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern void func_8013CF68();
extern s32 D_80195868;
extern s32 D_8019586C;
extern void func_8013D9B0(void);
extern void func_8013D064(void);
extern s32 func_8013D13C(void);
extern void func_8013D164(void);
extern u8 D_80196BD2;
extern u8 D_80196C46;
extern u8 D_80196AFA;
extern u8 D_80196BB4;
extern u8 D_80196AD8;
extern u8 D_80196AF9;
extern s32 D_80196BB8;
extern void func_8013D330(void);
extern void *D_80195840;
extern void *D_80195844;
extern void *D_80195848;
extern s32 D_80195870;
extern s32 D_80195874;
extern s32 D_80195878;
extern s32 D_80196B2C[];
extern u8 D_8017F304[];
extern u8 D_8017F3AC[];
extern u8 D_8017F25C[];
extern u8 D_8017F358[];
extern u8 D_8017F3D8[];
extern u8 D_8017F2B0[];
extern void func_8013D53C();
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);
extern void func_8013D3D4(int param_1, int param_2);
extern s16 *D_8019584C;
extern s32 D_8019587C;
extern s32 D_80195880;
extern s32 D_80195884;
extern void func_8013DBE4(int param_1);
extern void func_8013DD68();
extern s32 D_80195864;
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
extern s32 func_8012C750(s32 a0);
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
extern void func_8013E5E8(void);
extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_8017FE64;
extern s32 D_80115188;
extern s16 D_8017FE3C;
extern s16 D_8017FE3E;
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
extern u16 D_8011511E;
extern s32 D_80115130;
extern s16 D_8011514C;
extern void func_8013EA54(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern unsigned char *func_80141CA4(void);
extern short D_80115128;
extern s16 D_8011512A;
extern unsigned char D_8017FE40;
extern void func_8013EB7C(void);
extern u16 D_80115112;
extern void func_8013ED6C(void);
extern s32 func_8013EE10();
extern unsigned short D_80115118;
extern void func_8013F138(void);
extern void func_800D2624(void);
extern unsigned short D_80115114;
extern void func_8013F1BC(void);
extern void func_80141C0C(s32);
extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);
extern s32 func_8013FFD8(s16 arg0, s32 arg1, s32 *arg2);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

extern u8 D_80115148[];
extern u16 D_8011511E;
extern u8 D_80062BDC;

extern s32 func_80028D58(void);
extern void func_80028D78(s32 a0);
extern void func_80019064(void *a0);
extern s32 func_80028DE0(void);
extern void func_80028E00(s32 a0);
extern s32 func_80028FBC(void);
extern void func_80028FDC(s32 a0);
extern s32 func_80029000(void);
extern void func_80029020(s32 a0);
extern s32 func_80028D9C(void);
extern void func_80028DBC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

#include "../shared/ov/func_80140608__t42e81990.h"



// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).

extern u8 *D_8017FB1C;
extern u8 *D_8017FB20;
extern u8 *D_8017FB24;
extern u8 *D_8017FB28;
extern u8 *D_8017FB2C;
extern u16 *D_8017FB30[];
extern u16 *D_8017FB38[];
extern u16 *D_8017FB58[];

extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

#include "../shared/ov/func_801407F4__cdfae9b4.h"





















extern s16 func_8014168C(s16);
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
/* func_80140958 -- MATCH (260 ins), verified by
 *   python3 tools/match_one.py func_80140958 --c .run/near6/wave23/func_80140958.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077
 *
 * Three levers took the seed from 6 -> 0 (see the numbered notes in the inner block):
 *   [L1] `m == i` (not `m == 3`)  -- keeps b[0] a RUNTIME value; `m == 3` let gcc
 *        const-fold it and materialise `li a3,3` / `li t3,12` instead of
 *        `addu a3,v1,zero` / `sll t3,v1,2`.
 *   [L2] one dead `__asm__ volatile("" :: "r"(j))` -- +1 weighted REG_N_REFS on j so
 *        global.c:594 allocno_compare ranks j above k (j -> $a2, k -> $a3).
 *   [L3] `t3v = m * 4` as an EXPLICIT preheader statement (instead of letting loop.c
 *        hoist D_8011516A[m]'s index) -- gives it a LUID *below* the three constant
 *        assignments, which is what puts `move a3,v1 / sll t3,v1,2` ahead of them in
 *        sched1's backward LUID tie-break.
 */
#include "../shared/ov/func_80140958__e2790db1.h"





#include "../shared/ov/func_80140D68.h"



// @class: struct
// @stuck: none — MATCH

extern unsigned char D_80078E7F;
extern unsigned char D_80078E7E;
extern unsigned char D_80078E7D;
extern M2C_UNK D_8017FA58;

extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

#include "../shared/ov/func_80140E6C__84374bda.h"




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)

extern short D_80115128;
extern u8 D_8017FA68;
extern char *D_8017FA88;
extern char *D_8017FA8C;
extern char *D_8017FA90;
extern char *D_8017FA94;
extern char *D_8017FA98;

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

#include "../shared/ov/func_80140F00__815fad8a.h"



// @class: other
// @stuck: none — MATCH

extern short D_80115128;
extern unsigned short D_80115172;
extern unsigned short D_8017F922;
extern unsigned short D_8017F926;
extern unsigned short D_8017F92A;
extern unsigned short D_8017F92E;

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

#include "../shared/ov/func_80141100__110c9682.h"


#define addPrim_1412A8(ot, p) (setaddr_1412A8(p, getaddr_1412A8(ot)), setaddr_1412A8(ot, p))
/* §37/§124 def-side asm-label alias (the S40 class lever). The TU declares
 *   extern int func_801412A8(int, int, int, int, int, int);            (ov_SC01_077.c:2720)
 * and its callers USE the return value (`param_1 = func_801412A8(...)`, :2730-:2736), while the
 * byte-true definition is `Prim_1412A8 *(Prim_1412A8 *, int, int, int, u16, u16)`. The u16 params
 * cannot agree with an `int` prototype (C default argument promotion) and the `()` no-prototype
 * escape is illegal precisely when a param promotes -- so NEITHER side can move. Giving the
 * DEFINITION a private C identifier bound to the emitted symbol by a GNU asm label decouples
 * them: the TU's declaration continues to govern the CALL SITES (their codegen is untouched --
 * which is what match_one could not see, since it only compiles this function), and the
 * definition keeps its byte-true signature. Zero blast radius. */
#include "../shared/ov/func_801412A8.h"


#include "../shared/ov/func_801415C0.h"

#include "../shared/ov/func_8014168C.h"

#include "../shared/ov/func_801416D4.h"


extern unsigned short D_80115112;
extern void (*D_8017FEB8[])(void);

#include "../shared/ov/func_80141788__4d15e15c.h"


#include "../shared/ov/func_801417C4.h"

#include "../shared/ov/func_801417F8.h"


extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);

extern u16 D_8011511E;
extern unsigned short D_80115112;

#include "../shared/ov/func_80141874__9e298500.h"









extern u16 D_80115110;
extern u16 D_80115112;
extern unsigned short D_80115118;
extern volatile u16 D_8011511A;
extern s16 D_80115128;
extern s32 D_80115130;
extern s16 D_8017FE3C;
extern s16 D_8017FE3E;

extern void func_800D24A0(s32 a0);
extern s32  func_80029178(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80141C0C(s32 a0);

void func_801418F8(void)
{

    extern s16 D_8011512E;
    extern u8 D_80115158[];
    extern s16 D_8011515A;
    extern u8 D_8011515C;
    extern s16 D_8011515E;
    extern s16 D_80115162;
    extern s16 D_80115166;
    extern u8  D_8017FADC;
    extern u8  D_8017FAF4;
    extern u8  D_8017FB68;
    extern u8  D_8017FB70;
    extern void *D_80195898;
    extern void *D_8019589C;
    u16 t;

    func_800D24A0(1);
    D_8011511A = 2;
    t = D_8011511A;
    (*(s16 *)&D_80115118) = 0;
    D_80115130 = 0;
    if (t >= 4) {
        D_8011511A = t - 3;
    }
    (*(s16 *)D_80115158) = 0x106;
    if ((func_80029178(0x1C) & 0xFF) == 0) {
        D_80195898 = &D_8017FADC;
        D_8019589C = &D_8017FB68;
    } else {
        D_80195898 = &D_8017FAF4;
        D_8019589C = &D_8017FB70;
    }
    D_8011515A = 0x104;
    (*(s16 *)&D_8011515C) = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;
    if (D_80115110 == 3) {
        func_8002D4C8(0x46E, 0);
    } else {
        func_80141C0C(0);
    }
    D_80115128 = 1;
    D_8017FE3C = 0xE;
    D_8017FE3E = 3;
    D_80115112 = D_80115112 + 1;
}


/* func_80141A60 @ 0x80141A60 (0x130, 76 ins) -- ov_SC01_000 shared engine fn.
 *
 * ((s32 *)D_801151C8)[]: word (s32) table indexed by (u16)(*(u16 *)&D_800B9A02) -> D_801151D0.
 * D_8011511A: u16, unsigned compare vs 4 (sltiu).
 * (*(u8 *)&D_8011514C)/4D/5C: u8 fields; a1 = (s16)((*(u8 *)&D_8011514C) + D_8011514D*D_8011515C).
 * D_80115130: cached s32 handle. D_8017FE40: address-taken arg to func_801376E8.
 * D_80115116: s16 <- 0xfff8 (ori, positive const). D_80115112: u16 counter.
 */

extern s16 D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
/* D_8011511A: this TU declares it volatile at file scope -> a direct read reloads on every
 * use; the cast-at-use *(u16 *)&D_8011511A strips volatile so gcc CSEs the three reads into
 * one load (matches the single-load target). */
extern s16 D_8011514C;
extern s32 D_80115130;
extern u8  D_8017FE40;
extern u16 D_80115112;

extern s32  func_8013F350(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern s32  func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern s32  func_800D0EC4(void);

#include "../shared/ov/func_80141A60__74c515f5.h"


#include "../shared/ov/func_80141B90.h"

#include "../shared/ov/func_80141C04.h"


// @class: struct
// @stuck: none — MATCH expected (indexed u16 global: (s16)param_1*2 + D_80115110, *2 array stride)

extern u16 D_80115110;
extern u8 D_8017FE18;
extern void func_8002D4C8(s32 a0, s32 a1);

#include "../shared/ov/func_80141C0C__80e53220.h"


#include "../shared/ov/func_80141C50.h"

#include "../shared/ov/func_80141CA4.h"

#include "../shared/ov/func_80142414.h"

#include "../shared/ov/func_80142454.h"


// @class: struct
// @stuck: none — MATCH (58 ins). STRUCT branch reconstruction + 3 levers: (1) §3-T4 branch-polarity
//   invert in the ==0 arm so the func_8012C218 cold path sinks to the tail; (2) *(volatile int*) on
//   the two extra param_1[0x32] reloads to defeat gcc CSE (gcc reloads via register reuse, not a store);
//   (3) param_1[0x7e] pinned to $v1 (register __asm__("$3")) + an input-only scheduling barrier
//   __asm__ __volatile__("" : : "r"(a)) on the 0xA read so the pinned load is anchored AFTER it in the
//   ==0 arm (matches the load2-reused-as-$v1 ordering).

extern void func_8012C218(void *a0);

#include "../shared/ov/func_801424E4__ca18e5c5.h"



extern void (*D_8017FEF8[])(void);

#include "../shared/ov/func_801425CC__8a9d3cad.h"



// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_8017FEDC;

#include "../shared/ov/func_80142608__03fdea6a.h"


#include "../shared/ov/func_801426D4.h"

#include "../shared/ov/func_80142740.h"

#include "../shared/ov/func_80142778.h"

#include "../shared/ov/func_801427DC.h"

#include "../shared/ov/func_801427E4.h"


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_8017FF0C[])();

#include "../shared/ov/func_801427EC__9eacfd81.h"


#include "../shared/ov/func_80142838.h"

#include "../shared/ov/func_801428CC.h"


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_8017FF28[])();

#include "../shared/ov/func_8014292C__acc2634e.h"



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801800F8[])();

#include "../shared/ov/func_80142978__0fcd9274.h"



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_801801B0[])();

#include "../shared/ov/func_801429C4__eb8b1525.h"



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)
// @reconcile: func_80142A80 is DEFINED later in this TU as `void func_80142A80(void)`.
//   The uc2 draft declared it `extern void func_80142A80(int)` -> conflicting types.
//   Escape §17a-1/§20: conform the declaration to the TU's, cast at the use site
//   (codegen-neutral: the argument still lands in $a0).

extern void func_80142A80(void);

#include "../shared/ov/func_80142A10__8a1262a1.h"



// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)

extern u16 D_800B99D8;
extern struct packed_word D_80194F80;
extern u8 D_801958A0;
extern u8 D_801958A1;
extern u8 D_801958A2;

void func_80142A80(void)
{
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_80194F80;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801958A0 = mul * (local.b[0] >> 4);
    D_801958A1 = mul * (local.b[1] >> 4);
    D_801958A2 = mul * (local.b[2] >> 4);
}


#include "../shared/ov/func_80142B2C.h"


#include "../shared/ov/func_80142BB4.h"

#include "../shared/ov/func_80142C7C.h"

#include "../shared/ov/func_80142C84.h"

#include "../shared/ov/func_80142C9C.h"

#include "../shared/ov/func_80142D38.h"

#include "../shared/ov/func_80142DB8.h"


// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern int D_8017FF00;

#include "../shared/ov/func_80142DC4__68cf8a8d.h"




// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_8017FF1C[];

#include "../shared/ov/func_80142E38__600b7ab2.h"



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


#include "../shared/ov/func_80142EC0__dcd4ad7c.h"


#include "../shared/ov/func_80142F68.h"

#include "../shared/ov/func_80142FFC.h"


// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_80180108[];
extern unsigned char D_80180168[];

#include "../shared/ov/func_8014305C__8596e332.h"


#include "../shared/ov/func_801430F4.h"

#include "../shared/ov/func_80143188.h"


// @class: regalloc-order
// @stuck: none — MATCH (memcpy unaligned copy; $s0 survivor pinned, store-before-copy keeps $v0 for early store/branch)


extern void *memcpy(void *, const void *, u32);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80142B2C(void *arg0);

extern u8 D_80194F7C;
extern u8 D_801958A0;
extern u8 D_801958A4;

void func_801431E8(s32 param_1) {
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_80194F7C, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801958A0);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801958A0, 0x10);
            memcpy(&D_801958A4, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


#include "../shared/ov/func_801432FC.h"

#include "../shared/ov/func_80143390.h"

#include "../shared/ov/func_801433F0.h"


// @class: plumbing
// @stuck: none — MATCH (pending gate)

extern u8 D_800D387C[];
extern u32 D_801802C0[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

#include "../shared/ov/func_80143458__665a7c97.h"


#include "../shared/ov/func_8014350C.h"


// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

#include "../shared/ov/func_8014358C__b0293ad6.h"


#include "../shared/ov/func_80143640.h"

#include "../shared/ov/func_801437D8.h"

#include "../shared/ov/func_80143970.h"

#include "../shared/ov/func_80143994.h"

#include "../shared/ov/func_801439C0.h"

#include "../shared/ov/func_801439FC.h"


extern void (*D_801803E8[])(void);

#include "../shared/ov/func_80143B30__06dd4c2f.h"


#include "../shared/ov/func_80143B6C.h"

#include "../shared/ov/func_80143BDC.h"


extern void (*D_801803F4[])(void);

void func_80143C38(void *a0) {
    D_801803F4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80143C74.h"


extern void (*D_801803FC[])(void);

#include "../shared/ov/func_80143C98__fbbd8503.h"


#include "../shared/ov/func_80143CD4.h"


// @class: regalloc-order
// @stuck: none — MATCH (80 ins, relocation-masked). iVar2/iVar3 pinned $s1/$s2; sVar4 is an
//   int set BEFORE the call so it naturally takes callee-saved $s3; chained assignment
//   a=b=c=sVar4 materializes the value once (the addu $v0,$s3,$zero move) + delay-slot store.

     /* size 0x0c */

extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

#include "../shared/ov/func_80143D28__b958d830.h"



extern void (*D_80180444[])(void);

#include "../shared/ov/func_80143E68__eeb1309e.h"


#include "../shared/ov/func_80143EA4.h"

#include "../shared/ov/func_80143EAC.h"

#include "../shared/ov/func_80143EB4.h"

#include "../shared/ov/func_80143EBC.h"


extern void (*D_80180458[])(void);

void func_80144054(void *a0) {
    D_80180458[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @stuck: 154/154 ins structural match (callees/consts/ctrl-flow/stack/GPU-packet all byte-correct); residual 25 = caller-saved temp-reg coalescing in the final ring-vertex block (target reuses dead $s0=iVar3 for iVar3-(iVar4>>6) subu where gcc reuses iVar4>>6's reg; iVar4 mflo -> $a3 vs target $v0) + 2-ins schedule swap of giv-increment vs iVar2*4 -> permuter grinder territory (§27 step-5)

 /* 0x14 stride */

#include "../shared/ov/func_80144090.h"


extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)

extern void (*D_80180460[])();

#include "../shared/ov/func_801442F8__1252e589.h"



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801803DC;

#include "../shared/ov/func_80144364__b85d3910.h"




extern void func_80016714(void *a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_801803F0;

#include "../shared/ov/func_80144458__f427c0b3.h"


#include "../shared/ov/func_80144558.h"

#include "../shared/ov/func_8014462C.h"

#include "../shared/ov/func_801446A4.h"



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_80180404;
extern u8 D_80180410;

#include "../shared/ov/func_8014477C__6672be9f.h"



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

extern u8 D_801803DC;
extern u8 D_8018044C;

#include "../shared/ov/func_80144880__b29cd3d4.h"


#include "../shared/ov/func_80144988.h"


extern void (*D_80180468[])(void);

void func_801449C8(void *a0) {
    D_80180468[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80144A04.h"


extern void (*D_80180470[])(void);

void func_80144A2C(void *a0) {
    D_80180470[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80144A68.h"

#include "../shared/ov/func_80144A90.h"

#include "../shared/ov/func_80144A98.h"

#include "../shared/ov/func_80144AEC.h"



// @class: struct
// @stuck: none — MATCH

#include "../shared/ov/func_80144B14.h"



