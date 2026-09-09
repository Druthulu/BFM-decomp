/* func_8017C120 — shared body (overlay slot 0x80128158, h_exact c2ebbc57). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C120(void *a0)
{
    s32 val;

    val = *(s32 *)((s32)a0 + 0x1C);
    val--;
    *(s32 *)((s32)a0 + 0x1C) = val;

    if (val != -1) {
        func_800D22E4((s32)a0);
        *(s32 *)((s32)a0 + 0x14) += 0x1A000;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}
