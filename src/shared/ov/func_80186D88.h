/* func_80186D88 — shared body (overlay slot 0x80128158, h_exact 6ce35974). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80143BDC(u16 *a0);
extern void func_80187558();
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
void func_80186D88(void *s0) {
    void *a0;
    s16 v0, v1;
    u16 sp[3];
    s32 result;
    void *v3;
    a0 = *(void **)((char *)s0 + 0x64);
    v0 = *(s16 *)((char *)a0 + 0xE);
    v1 = *(s16 *)((char *)s0 + 0xE);
    if ((v0 - 0x80) < v1) {
        *(s16 *)((char *)a0 + 0xFE) = 1;
        sp[0] = *(u16 *)((char *)s0 + 0x6);
        sp[1] = *(u16 *)((char *)s0 + 0xA) - 0x40;
        sp[2] = *(u16 *)((char *)s0 + 0xE);
        result = func_80143BDC(sp);
        if (result) {
            v3 = *(void **)((char *)result + 0xCC);
            *(s16 *)((char *)v3 + 0x1A) = 0x5000;
            *(s16 *)((char *)v3 + 0x18) = 0x5000;
        }
        func_80187558(s0);
        func_8002D4C8(0x4DC, 0);
        func_8012C218(s0);
    }
}
