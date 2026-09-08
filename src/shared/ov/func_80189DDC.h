/* func_80189DDC — shared body (overlay slot 0x80128158, h_exact c7faab26). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80115126;
extern s32 D_801B92E4[];
void *func_80189DDC(s32 a0) {
    return (void *)D_801B92E4[D_80115126 * 10 + (s16) a0];
}
