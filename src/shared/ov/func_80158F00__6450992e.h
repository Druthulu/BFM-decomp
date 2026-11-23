/* func_80158F00 — shared body (overlay slot 0x80128158, h_exact 6450992e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80158F00(int param_1) {
    int *self = (int *)param_1;
    Unkstruct_8001C9D0 *act = (Unkstruct_8001C9D0 *)self[0x20 / 4];
    int gate = D_8018E85C;

    act->head.unk10.w.unk12.u = (u16)((act->head.unk10.w.unk12.u + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = guess_OpenTextWindow(D_801815E8[r % 0xb]);
        ((void (*)(int))guess_NextStep)(param_1);
    }
}
