/* func_8016B984 — shared body (overlay slot 0x80128158, h_exact c20da3b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_ZeroMemory(void *a0, s32 a1);
extern s32 guess_FreeSmallObject();  // K&R: ? of 1 args (P37 rung D t4_HD7)
void func_8016B984(void *a0) {
    if (*(s32*)((s32)a0 + 0x10) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x10), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x14) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x14), 0x38);
    }
    if (*(s32*)((s32)a0 + 0x18) != 0) {
        guess_ZeroMemory(*(void**)((s32)a0 + 0x18), 0x38);
    }
    ((void (*)(void *))guess_FreeSmallObject)(a0);
}
