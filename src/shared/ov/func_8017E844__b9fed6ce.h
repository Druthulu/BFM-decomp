/* func_8017E844 — shared body (overlay slot 0x80128158, h_exact b9fed6ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E844(a0)
u8 *a0;
{
    s16 arr[3];

    if (--(*(s32 *)(a0 + 0x200)) == -1) {
        *(u16 *)(a0 + 0x74) = 0x1080;
        *(u16 *)(a0 + 0x72) = 0x1080;
        *(u16 *)(a0 + 0x70) = 0x1080;
        arr[0] = *(u16 *)(a0 + 6) - 0x40;
        arr[1] = *(u16 *)(a0 + 0xA) - 0x10;
        arr[2] = *(u16 *)(a0 + 0xE) + 0x10;
        func_80146A6C(0x36, a0, (s16)arr[0], (s16)arr[1], (s16)arr[2], 0, 0);
        func_80171990(a0);
    }
}
