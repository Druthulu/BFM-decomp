void func_801805EC(s32 a0)
{
    SVECTOR svec_in;
    SVECTOR svec_out;
    s32 obj;

    svec_in.vx = *(u16 *)(a0 + 0x12);
    svec_in.vy = *(u16 *)(a0 + 0x16);
    svec_in.vz = *(u16 *)(a0 + 0x1A);
    func_8012F14C((s32)D_80126B78 + 0x34, (s32)&svec_in, (s32)&svec_out);

    *(u16 *)(a0 + 0x6) = svec_out.vx;
    *(u16 *)(a0 + 0xA) = svec_out.vy;
    *(u16 *)(a0 + 0xE) = svec_out.vz;

    obj = *(s32 *)(a0 + 0x20);
    *(u16 *)(obj + 0x14) = *(u16 *)(obj + 0x14) +
        (*(u16 *)(a0 + 0x2A) - *(u16 *)((u8 *)D_80126B78 + 0x12));

    *(u16 *)(a0 + 0x2A) = *(u16 *)((u8 *)D_80126B78 + 0x12);
    if (*(s32 *)(a0 + 0x2C) == 0) {
        if (--*(s32 *)(a0 + 0x1C) != 0) {
            return;
        }
        {
            s32 t = *(s32 *)(a0 + 0x2C);
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s32 *)(a0 + 0x2C) = t + 1;
        }
    } else {
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) ^= 0x80000000;
        if (--*(s32 *)(a0 + 0x1C) != 0) {
            return;
        }
        func_801292C8((u8 *)a0);
    }
}
