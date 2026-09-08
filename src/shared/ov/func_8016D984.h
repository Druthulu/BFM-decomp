/* func_8016D984 — shared body (overlay slot 0x80128158, h_exact 3ef37ce7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C();
extern void func_800D22E4(s32 a0);
void func_8016D984(s32 *a0) {
    if ((--*(s32 *)((char *)a0 + 0x1C)) == 0) {
        func_80146C3C();
    } else {
        func_800D22E4((s32)a0);
        *(s32 *)((char *)a0 + 0x10) -= *(s32 *)((char *)a0 + 0x10) >> 4;
        *(s32 *)((char *)a0 + 0x14) -= *(s32 *)((char *)a0 + 0x14) >> 4;
        *(s32 *)((char *)a0 + 0x18) -= *(s32 *)((char *)a0 + 0x18) >> 4;
    }
}
