/* func_80184E4C — shared body (overlay slot 0x80128158, h_exact c7844ae0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 func_80184E4C(s32 a0, s32 a1, s16 a2, s16 a3, s32 a4) {
    s32 obj;
    obj = func_8012C194();
    if (obj == 0) {
        return 0;
    }
    func_8001CB6C((u8 *)obj, a1, a2, a3);
    *(u16 *)(obj + 0x10) = 0xC00;
    *(u8 *)(obj + 0x27) = a4;
    *(u16 *)(obj + 0x1A) = 0x2D00;
    *(u16 *)(obj + 0x18) = 0x2D00;
    *(u16 *)(obj + 8) = *(u16 *)(a0 + 6);
    *(u16 *)(obj + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(obj + 0xC) = *(u16 *)(a0 + 0xE);
    return obj;
}
