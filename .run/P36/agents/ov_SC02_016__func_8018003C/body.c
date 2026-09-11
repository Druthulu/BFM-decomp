void func_8018003C(s32 arg0)
{
    s32 obj;
    s32 v;

    obj = *(s32 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x10) += *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg0 + 0x14) += *(s32 *)(arg0 + 0x30);
    *(s32 *)(arg0 + 0x18) += *(s32 *)(arg0 + 0x34);
    func_8012931C((struct vec *)arg0);
    v = *(u16 *)(obj + 0x1A) - 0x100;
    *(u16 *)(obj + 0x1A) = v;
    *(u16 *)(obj + 0x18) = v;
    if (func_80128ED8(obj, (s32 *)(arg0 + 0x24)) != 0) {
        func_801292C8((u8 *)arg0);
    } else {
        v = *(s32 *)(arg0 + 0x1C);
        if (v != 0) {
            v--;
            *(s32 *)(arg0 + 0x1C) = v;
            if (v == 0) {
                func_801292C8((u8 *)arg0);
            }
        }
    }
}
