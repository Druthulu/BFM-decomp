/* func_801470C0 — shared body (overlay slot 0x80128158, h_exact 2b1537f4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801470C0(s32 a0) {
    s32 a1;
    a1 = *(s32*)(a0 + 0x20);
    if (a1 != 0) {
        if ((*(u8*)(a0 + 0x221) | *(u8*)(a0 + 0x220) | *(u8*)(a0 + 0x222)) != 0) {
            *(s32*)(a1 + 0x4) |= 0x80000000;
        } else {
            *(s32*)(a1 + 0x4) &= 0x7FFFFFFF;
        }
    }
}
