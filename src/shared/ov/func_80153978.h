/* func_80153978 — shared body (overlay slot 0x80128158, h_exact d1eecebe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *src, s32 dst);
extern s32 func_801539F8(s32 a0, void *a1);
s32 func_80153978(s32 a0, u16 *src) {
    Buf80153978 buf;
    buf.unk0 = src[0];
    buf.unk2 = src[1] + 0x1F;
    buf.unk4 = src[2];
    if (func_80133784(0, src, (s32)&buf) == 0x2000 &&
        buf.unk6 == 0 &&
        func_801539F8(a0, &buf) == 0) {
        return 0;
    }
    return 1;
}
