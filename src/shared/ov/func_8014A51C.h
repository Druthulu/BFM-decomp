/* func_8014A51C — shared body (overlay slot 0x80128158, h_exact bc569e9c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_TestGameFlag(s32);
int func_8014A51C(int param_1) {
    if (((unsigned char (*)(int))guess_TestGameFlag)(0x1e) == 0) return 0;
    if (*(unsigned int *)(param_1 + 0x44) & 0x400) return 0;
    if (*(unsigned char *)(param_1 + 0xa8) >= 0x19) return 0;
    if (*(unsigned char *)(param_1 + 0x223) != 0) return 0;
    if ((*(unsigned short *)(param_1 + 0xac) & 0x40) == 0) return 0;
    return 1;
}
