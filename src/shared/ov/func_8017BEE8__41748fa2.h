/* func_8017BEE8 — shared body (overlay slot 0x80128158, h_exact 41748fa2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BEE8() {
    s32 obj;

    func_80147364(4, 0x542);
    func_80147364(4, 0x543);
    func_80147364(4, 0x541);
    obj = func_8014C050((s32)&D_80126B58, 0x29);
    if (obj != 0) {
        if (*(s32 *)(obj + 0x34) != 0) {
            func_80016714(*(void **)(obj + 0x34), 0x38);
        }
        if (*(s32 *)(obj + 0x10) != 0) {
            func_80016714(*(void **)(obj + 0x10), 0x38);
        }
        if (*(s32 *)(obj + 0x14) != 0) {
            func_80016714(*(void **)(obj + 0x14), 0x38);
        }
        if (*(s32 *)(obj + 0x18) != 0) {
            func_80016714(*(void **)(obj + 0x18), 0x38);
        }
        if (*(s32 *)(obj + 0x1C) != 0) {
            func_80016714(*(void **)(obj + 0x1C), 0x38);
        }
        ((void (*)(void *))func_80146C3C)((void *)obj);
    }
}
