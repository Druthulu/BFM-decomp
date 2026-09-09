/* func_80142A80 — shared body (overlay slot 0x80128158, h_exact e460239a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80142A80(void)
{
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_8018DE88;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_8018E7C8 = mul * (local.b[0] >> 4);
    D_8018E7C9 = mul * (local.b[1] >> 4);
    D_8018E7CA = mul * (local.b[2] >> 4);
}
