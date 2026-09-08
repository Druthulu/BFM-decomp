/* func_8017CC44 — shared body (overlay slot 0x80128158, h_exact 4de1fad1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8017DD7C();
void func_8017CC44(void *a0)
{
    s32 flags = *(s32 *)((s32)a0 + 0x1C);
    s32 ptr = *(s32 *)((s32)a0 + 0x20);
    if (flags & 1) {
        *(s32 *)(ptr + 4) |= 0x80000000;
    } else {
        *(s32 *)(ptr + 4) &= 0x7FFFFFFF;
    }
    if (func_80146E98((s32)a0)) {
        func_8017DD7C();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}
