/* func_8015E5B0 — shared body (overlay slot 0x80128158, h_exact 2d57884c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
void func_8015E5B0(u8 *self)
{
    u8 *obj;
    s16 src[4];
    s16 dst[4];
    obj = *(u8 **)(self + 0x18C);
    if (obj == 0) {
        return;
    }
    src[0] = *(u16 *)(self + 0x6);
    src[1] = *(u16 *)(self + 0xA) - 0x14;
    src[2] = *(u16 *)(self + 0xE);
    dst[0] = *(u16 *)(obj + 0x6);
    dst[1] = *(u16 *)(obj + 0xA);
    dst[2] = *(u16 *)(obj + 0xE);
    if (func_80133784(0, src, (s32)dst) != 0) {
        *(u16 *)(obj + 0x6) = dst[0];
        *(u16 *)(obj + 0xA) = dst[1];
        *(u16 *)(obj + 0xE) = dst[2];
    }
    func_80015978((s32)(obj + 4), (s32 *)src);
    src[3] = 0;
    func_8014C4AC((s32)obj, 0x1C, 0, src,
                  *(s16 *)(*(u8 **)(self + 0x20) + 0x12));
    *(s32 *)(self + 0x18C) = 0;
}
