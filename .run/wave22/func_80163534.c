/* canonical (sig_hints) — return type widened s32 so the `sw $v0` after the jal has a
   source; the hint's `void` cannot express the store. */
extern s32 func_80163664(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32);

/* canonical (sig_hints) */
extern s32 D_80115100;
extern s32 D_80115200;
extern u16 D_80126B18[];

/* derived from the asm: separate lui/%lo per symbol => distinct externs */
extern s32 D_80115204;
extern s32 D_80115208;
extern u16 D_801270B0[];
extern u16 D_801270B2;
extern u16 D_801270B4;
/* LOAD-BEARING: D_80126B1A must be declared/stored as an ARRAY, not a scalar.
   gcc-2.7.2 true_dependence() lets an in-struct MEM with an unstable (register)
   address bypass a not-in-struct MEM with a stable (symbol) address. As a scalar,
   the `sh %lo(D_80126B1A)` store does NOT conflict with `a5[2]`, so the block-6
   `lhu $t0,4($t0)` gets hoisted into the D_80126B1A block's load-delay slot and the
   whole filler queue shifts one slot early (75 ins, no `nop`). ARRAY_REF sets
   MEM_IN_STRUCT_P on the store => the two MEMs conflict => the load stays put. */
extern u16 D_80126B1A[];
extern u16 D_80126B1C;
extern s32 D_80114EB0;
extern s32 D_80114EC8;
extern s32 D_8011DAF0;
extern s32 D_80115298;
extern s32 D_80126734;

void func_80163534(s32 a0, u16 a1, u16 a2, s32 a3, u16 a4, u16 *a5)
{
    s32 *p = &D_80115200;

    *p = 0;
    D_80115204 = 0;
    D_80115208 = 0;

    D_801270B0[0] = *(u16 *)(a0 + 0x44) + a5[0];
    D_801270B2 = *(u16 *)(a0 + 0x46) + a5[1];
    D_801270B4 = *(u16 *)(a0 + 0x48) + a5[2];

    D_80126B18[0] = *(u16 *)(a0 + 0x6) + a5[0];
    D_80126B1A[0] = *(u16 *)(a0 + 0xA) + a5[1];
    D_80126B1C = *(u16 *)(a0 + 0xE) + a5[2];

    *p = func_80163664(a0, a1, a2, (s32)D_801270B0, (s32)D_80126B18,
                               (s32)&D_80114EB0, (s32)&D_80114EC8, (s32)&D_80115100,
                               (s32)&D_8011DAF0, a3, a4, (s32)&D_80115298,
                               (s32)&D_80126734);
}
