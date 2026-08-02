void func_8017BEBC(void *a0, void *a1, s16 a2) {
    s16 v0, v1, v2;
    s32 tmp, cond;
    int i;

    // Load three unsigned 16-bit values from a1
    v0 = *(u16 *)(a1 + 0);
    v1 = *(u16 *)(a1 + 2) - 0x14;
    v2 = *(u16 *)(a1 + 4);

    // Load from a0 + 0x20, add 0x34, and call func_8012F14C
    tmp = *(s32 *)(a0 + 0x20);
    func_8012F14C(tmp + 0x34);

    // Loop twice (i = 0, 1)
    for (i = 0; i < 2; i++) {
        // If a2 != 0, use 1; otherwise use loop counter
        if (a2 != 0) {
            cond = 1;
        } else {
            cond = i;
        }

        // Call func_80146A6C with conditional value
        func_80146A6C(0x25, a0, cond, v0, cond, 0, v2);
    }
}
