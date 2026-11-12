/* func_80158814 — shared body (overlay slot 0x80128158, h_exact b665efef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80158814(void *arg0) {
    D_8018E850 = 0;
    D_8018E85C = 1;
    D_8018E860 = 0;
    *(s8 *)((s32)arg0 + 0xA8) = 0;
    ((void (*)(void))guess_ClearHideRequest221)();
    ((void (*)(void *))guess_ClearHideRequest220)(arg0);
    ((void (*)(void *))guess_ClearHideRequest222)(arg0);
    ((void (*)(void *, s32))guess_SetState)(arg0, 0x1A);
    ((void (*)(void *))func_80158880)(arg0);
}
