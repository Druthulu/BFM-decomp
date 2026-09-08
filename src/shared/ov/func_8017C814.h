/* func_8017C814 — shared body (overlay slot 0x80128158, h_exact 72996053). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_8017D5F8(void *a0, s32 a1, s32 a2);
void func_8017C814(void *a0) {
    s32 *a2 = *(s32 **)((s32)a0 + 0x20);
    s16 sum;
    s32 pad[2];
    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        a2[1] |= 0x80000000;
    } else {
        a2[1] &= 0x7FFFFFFF;
    }
    *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x10) + 0x6C000;
    sum = *(u16 *)((s32)a2 + 0x1A) + *(u16 *)((s32)a0 + 0x12);
    *(u16 *)((s32)a2 + 0x1A) = sum;
    *(u16 *)((s32)a2 + 0x18) = sum;
    if (sum >= 0x1001) {
        *(u16 *)((s32)a2 + 0x1A) = 0x1000;
        *(u16 *)((s32)a2 + 0x18) = 0x1000;
        func_80146E90((s32 *)a0, 0);
        func_8017D5F8(a0, *(s32 *)((s32)a0 + 0x2C), 0);
        func_80146E90((s32 *)a0, 0);
        *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    }
}
