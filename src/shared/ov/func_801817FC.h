/* func_801817FC — shared body (overlay slot 0x80128158, h_exact eb4731f8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801817FC(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        if ((func_80029178(0xB8) & 0xFF) == 0) {
            func_800D0C48(1);
        }
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}
