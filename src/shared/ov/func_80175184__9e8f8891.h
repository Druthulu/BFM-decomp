/* func_80175184 — shared body (overlay slot 0x80128158, h_exact 9e8f8891). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80175184(s32* arg0) {
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_80182900[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}
