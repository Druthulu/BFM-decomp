/* func_8012D714 — shared body (overlay slot 0x80128158, h_exact 6c9f5e3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
s32 func_8012D714(s32 param_1, u32 param_2) {
    u16 a[3];
    u16 b[3];
    u32 base;
    base = (*(u32 *)(param_1 + 0x58) & 0xFFFFFFF) | 0x80000000;
    if (param_2 & 1) {
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 8);
        b[2] = *(u16 *)(base + 0xC);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 0xA);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xC);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xE);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 8);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 0xA);
        a[2] = *(u16 *)(base + 0xE);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
    }
    if (param_2 & 2) {
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 4);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xC);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xE);
        b[0] = *(u16 *)(base + 4);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 6);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xC);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 6);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xE);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
    }
    if (param_2 & 4) {
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 4);
        b[1] = *(u16 *)(base + 8);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 4);
        a[1] = *(u16 *)(base + 0xA);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 4);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 6);
        a[1] = *(u16 *)(base + 8);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 8);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
        a[0] = *(u16 *)(base + 6);
        a[1] = *(u16 *)(base + 0xA);
        a[2] = *(u16 *)(base + 0xC);
        b[0] = *(u16 *)(base + 6);
        b[1] = *(u16 *)(base + 0xA);
        b[2] = *(u16 *)(base + 0xE);
        if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) {
            return 1;
        }
    }
    return 0;
}
