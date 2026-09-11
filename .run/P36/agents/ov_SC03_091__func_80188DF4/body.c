s32 func_80188DF4(s32 a0)
{
    typedef struct { s32 w0; s32 w1; } Cmd;
    Cmd *ptr;
    s32 val;
    s32 next;

    val = *(s32 *)(a0 + 0xE0);
    if (val == 0) {
        return 1;
    }
    val = val - 1;
    *(s32 *)(a0 + 0xE0) = val;
    if (val > 0) {
        return 0;
    }

    ptr = *(Cmd **)(a0 + 0xD0);
    ptr = ptr + 1;
    if ((ptr->w0 & 0x40000000) != 0) {
        ptr = *(Cmd **)(a0 + 0xCC);
    } else if (ptr->w0 < 0) {
        *(s32 *)(a0 + 0xE0) = 0;
        return 1;
    }
    next = ptr->w0;
    *(Cmd **)(a0 + 0xD0) = ptr;
    *(s32 *)(a0 + 0xE0) = next;
    func_800183E0(ptr->w1);
    return 0;
}
