#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32);
extern void func_80180354(s32, s32);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_80189E60(s32 a0, s32 a1);

extern u8 D_801B4F5C[];
extern u8 D_801B5174[];
extern u8 D_801CC530[];
extern u8 D_801CC598[];
extern u8 D_801CC868[];
extern u8 D_801CC920[];

void func_80184C74(s32 p)
{
    s16 v18[4];   /* sp+0x18 */
    s32 mat[8];   /* sp+0x20 - MATRIX: 3x3 s16 + pad, 3 s32 at +0x14 */
    s32 s0;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        s0 = func_8012B8E4(p, 8);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += s0;
        if (func_8012BEE8(p) == 0 && s0 != 0) {
            return;
        }
        func_8012A828(p, D_801B4F5C);
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;

    case 1:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801CC598);
            *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        }
        break;

    case 2:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            if (func_8012E778(p, 0xA000C8) == 0) {
                *(s16 *)(p + 2) = 0x14;
                if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                    *(u16 *)(p + 0x34) = 1;
                    func_8012A828(p, D_801CC530);
                } else {
                    *(u16 *)(p + 0x34) = 0;
                    func_8012A828(p, D_801B4F5C);
                }
                return;
            }
            s0 = func_8012BCCC(p);
            if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                if (0x63FFF < s0) {
                    *(s16 *)(p + 2) = 0x14;
                    if ((*(s32 *)(p + 0xE0) & 0x400) == 0) {
                        *(u16 *)(p + 0x34) = 1;
                        func_8012A828(p, D_801CC530);
                    } else {
                        *(u16 *)(p + 0x34) = 0;
                        func_8012A828(p, D_801B4F5C);
                    }
                    return;
                }
            } else if (0xA0000 < (u32)(s0 - 0x24000)) {
                func_8012A828(p, D_801CC920);
                *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
                break;
            }
        }

        if (*(s32 *)(p + 0x94) < 8) {
            *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += func_8012B8E4(p, 8);
        }
        if (*(s32 *)(p + 0x94) != 7) {
            return;
        }

        func_8012EA90(p, 0xB, mat);
        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_801B5174, v18);
        ((void (*)(s32, void *))func_80180354)(p, v18);

        /* gte_SetRotMatrix */
        __asm__ __volatile__(
            "lw $12, 0( %0 );"
            "lw $13, 4( %0 );"
            "ctc2 $12, $0;"
            "ctc2 $13, $1;"
            "lw $12, 8( %0 );"
            "lw $13, 12( %0 );"
            "lw $14, 16( %0 );"
            "ctc2 $12, $2;"
            "ctc2 $13, $3;"
            "ctc2 $14, $4"
            : : "r"(*(s32 *)(p + 0x20) + 0x34) : "$12", "$13", "$14");

        /* column 0: gte_ldclmv / gte_rtir / gte_stclmv */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat) : "$12", "$13", "$14", "memory");

        /* column 1 */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat + 1) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat + 1) : "$12", "$13", "$14", "memory");

        /* column 2 */
        __asm__ __volatile__(
            "lhu $12, 0( %0 );"
            "lhu $13, 6( %0 );"
            "lhu $14, 12( %0 );"
            "mtc2 $12, $9;"
            "mtc2 $13, $10;"
            "mtc2 $14, $11"
            : : "r"((s16 *)mat + 2) : "$12", "$13", "$14");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 3, 3, 0");
        __asm__ __volatile__(
            "mfc2 $12, $9;"
            "mfc2 $13, $10;"
            "mfc2 $14, $11;"
            "sh $12, 0( %0 );"
            "sh $13, 6( %0 );"
            "sh $14, 12( %0 )"
            : : "r"((s16 *)mat + 2) : "$12", "$13", "$14", "memory");

        /* gte_SetTransMatrix */
        __asm__ __volatile__(
            "lw $12, 20( %0 );"
            "lw $13, 24( %0 );"
            "ctc2 $12, $5;"
            "lw $14, 28( %0 );"
            "ctc2 $13, $6;"
            "ctc2 $14, $7"
            : : "r"(*(s32 *)(p + 0x20) + 0x34) : "$12", "$13", "$14");

        /* gte_ldlvl / gte_rt / gte_stlvnl on the translation vector */
        __asm__ __volatile__(
            "lhu $13, 4( %0 );"
            "lhu $12, 0( %0 );"
            "sll $13, $13, 16;"
            "or $12, $12, $13;"
            "mtc2 $12, $0;"
            "lwc2 $1, 8( %0 )"
            : : "r"(&mat[5]) : "$12", "$13");
        __asm__ __volatile__("nop;nop;mvmva 1, 0, 0, 0, 0");
        __asm__ __volatile__(
            "swc2 $25, 0( %0 );"
            "swc2 $26, 4( %0 );"
            "swc2 $27, 8( %0 )"
            : : "r"(&mat[5]) : "memory");

        ((void (*)(void *, void *, void *))func_8012F14C)(mat, D_801B5174, v18);
        func_8018931C(p, v18, 0x282, 2, -0x120, 0);
        func_8018931C(p, v18, 0x282, 2, 0, 0);
        func_8018931C(p, v18, 0x282, 2, 0x120, 0);
        func_80189E60(p, 0x8BD);
        return;

    case 3:
        if (*(u16 *)(p + 0x72) & 0x4000) {
            func_8012A828(p, D_801CC868);
            *(s32 *)(p + 0x48) = 0x4650;
            *(s16 *)(p + 2) = 0x12;
        }
        return;

    case 4:
        if (func_8012BEE8(p) != 0) {
            func_8012A828(p, D_801CC598);
            *(u16 *)(p + 0x34) = 2;
        }
        break;
    }
}
