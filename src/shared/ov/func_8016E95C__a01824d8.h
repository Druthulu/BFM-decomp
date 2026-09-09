/* func_8016E95C — shared body (overlay slot 0x80128158, h_exact a01824d8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8016E95C() {
    extern Handler D_80181E90[];

    struct Entry_8016E95C *p;
    for (p = ((struct Entry_8016E95C *)&D_80115218); p < &((struct Entry_8016E95C *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_80181E90[p->f1](p);
        }
    }
}
