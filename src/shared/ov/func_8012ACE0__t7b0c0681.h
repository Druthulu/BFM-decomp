/* func_8012ACE0 — shared body (overlay slot 0x80128158, h_text 7b0c0681). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012ACE0(void *o) {
    int i;
    for (i = 0; ; i++) {
        switch (((Owner_8012ACE0_8012ACE0 *)o)->list[i].cmd) {
            case -2:
            case -1:
            case 0:
                return i;
            case -50: case -45: case -40: case -35: case -30:   /* scatter -> force jump table (min=-50 sets low bound) */
            default:
                break;
        }
    }
}
