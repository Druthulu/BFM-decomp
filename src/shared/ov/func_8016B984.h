/* func_8016B984 — shared body (overlay slot 0x80128158, h_exact c20da3b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern void func_80146C3C();
void func_8016B984(void *a0) {
    if (*(s32*)((s32)a0 + 0x10) != 0) {
        func_80016714(*(void**)((s32)a0 + 0x10), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x14) != 0) {
        func_80016714(*(void**)((s32)a0 + 0x14), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x18) != 0) {
        func_80016714(*(void**)((s32)a0 + 0x18), 0x38);
    }
    ((void (*)(void *))func_80146C3C)(a0);
}
