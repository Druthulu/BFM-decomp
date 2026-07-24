#include "common.h"
#include "../shared/engine_core.h"


void func_8013B568(s32 arg0) {

    extern s32 D_80182714;
    D_80182714 = arg0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013B598);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013B6A0);

   /* sizeof 0x1C stride */
void func_8013B7AC(int a0) {
    extern E_3B7AC D_801A9420[];
 D_801A9420[a0].f0 = 0; }




void func_8013B7F4(s32 a0, s32 a1) {

    extern s32 D_801A953C;
    func_8013B83C(a0, a1, D_801A953C);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013B83C);




void func_8013BC7C(void *arg0) {

    extern void (*D_80181F78[])(void *);
    D_80181F78[((S_8013BC7C *)arg0)->f68](arg0);
}



/* func_8013BCDC (ov_SC01_077_o0, -O0): guarded indirect call through D_80182714.
 * D_80182714 is declared `extern s32` in the TU (canonical-sig layer) and holds a
 * function pointer; read it as an s32, test non-null, cast to fn-ptr and call.
 * Frame residual: target frame is 0x30 (saves $ra/$fp/$s0 at 0x28/0x24/0x20) — 16
 * bytes of var_size above the minimal 0x20. At -O0 (no DCE) an unused 16-byte local
 * reserves exactly that var region (cookbook §42 lever 3, frame-pad induction) with
 * zero body instructions. 22/22 byte-identical via rtu_match. */
void func_8013BCDC(void) {

    extern s32 D_80182714;
    s32 pad[4];
    if (D_80182714 != 0) {
        ((void (*)(void))D_80182714)();
    }
}



void func_8013BD34(s32 a0) {

    extern s32 D_801A94D8;
    func_8013BD74(&D_801A94D8, a0);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013BD74);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C08C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C0F8);


void func_8013C360(s32 a0) {
    s32 *p;
    u32 i;
    p = (s32 *)(a0 + 0x10);
    for (i = 0; i < *(u32 *)(a0 + 8); i++) {
        *(s32 *)(*(s32 *)p) = *(s32 *)((s32)p + 4);
        p = (s32 *)((s32)p + 0xC);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C414);


void func_8013C938(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 1;
}



void func_8013C964(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 0;
}

