/* func_80187060 — shared body (overlay slot 0x80128158, h_exact 71935dc1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
void func_80187060(int param_1) {
    short v;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x100;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x20;
    v = *(unsigned short *)(param_1 + 0xFC) - 1;
    *(short *)(param_1 + 0xFC) = v;
    if (v == 0) {
        ((void (*)(void))func_8012C218)();
    } else {
        ((void (*)(void))func_8012AD80)();
    }
}
