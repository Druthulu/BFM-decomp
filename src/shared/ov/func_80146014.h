/* func_80146014 — shared body (overlay slot 0x80128158, h_exact 7eb4113a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void MoveImage(void *a0, s32 a1, s32 a2);
void func_80146014(s32 a0) {
    s32 *r = (s32 *)a0;
    if (r[3] == 0) {
        return;
    }
    do {
        MoveImage(r, r[2], r[3]);
        r += 4;
    } while (r[3] != 0);
}
