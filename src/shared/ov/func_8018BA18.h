/* func_8018BA18 — shared body (overlay slot 0x80128158, h_exact 74d72221). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern u8 D_80078EBA;
extern void func_8018B9D0(void *a0);
void func_8018BA18(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    if (D_80078EBA == 0) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(0xB, 0x10) != 0;
    }
    if (!v0) {
        func_8018B9D0(a0);
    }
}
