/* func_80157EA4 — shared body (overlay slot 0x80128158, h_exact a32bf889). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80157F64(s32 *a0);
extern int func_80155FF8(int arg, int a1);
extern s32 func_80156600(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80157EA4(void *a0) {
    s32 *v1;
    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
        return;
    }
    if (func_80157F64((s32 *)a0) != 0) {
        return;
    }
    func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
    v1 = (s32 *)func_80156600(a0);
    if (v1 == 0) {
        return;
    }
    if (*(s16 *)((u8 *)a0 + 0x244) != 0) {
        return;
    }
    *(s16 *)((u8 *)a0 + 0x244) = 1;
    func_80146A6C(0x54, a0, *(s16 *)v1, *(s16 *)((u8 *)v1 + 2), *(s16 *)((u8 *)v1 + 4), 0, 0);
}
