/* func_80183838 — shared body (overlay slot 0x80128158, h_exact 66d459f2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BAC(s32 a0, s32 a1);
extern void func_80184CB8(s32*, s32);
extern short D_80192030;
void func_80183838(s32 *a0) {
    *(s32 *)((s32)a0[0x33] + 0xB0) = 2;
    if (func_80184BAC(0xC, 0x14) != 0) {
        return;
    }
    *(short *)((char *)a0 + 0x2) = 1;
    ((void (*)(s32 *, void *))func_80184CB8)(a0, (void *)&(*(s32 *)&D_80192030));
}
