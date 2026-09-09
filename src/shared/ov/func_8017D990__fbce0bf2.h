/* func_8017D990 — shared body (overlay slot 0x80128158, h_exact fbce0bf2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017D990(void *a0)
{
    s32 t;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0xA) {
        ((void (*)(void))func_800D22E4)();
        func_8017D9EC(a0);
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}
