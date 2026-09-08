/* func_8016FE2C — shared body (overlay slot 0x80128158, h_exact ec4659af). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80172658(s32 *a0);
extern s32 func_80171990(u8 *a0);
void func_8016FE2C(u8 * a0)
{
    if (func_80172658(a0) != 0) {
        *(u16 *)((char *)a0 + 0xAC) |= 0x40;
        *(u16 *)((char *)a0 + 0xAA) |= 0x40;
        func_80171990((u8 *)a0);
    }
}
