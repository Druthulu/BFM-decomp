/* func_8016EAC0 — shared body (overlay slot 0x80128158, h_exact 8bfcb845). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016EAC0(struct Entry_8016E95C *param_1)
{
    unsigned char bVar1;

    param_1->unk4.s = param_1->unk4.s + D_80182638[param_1->unk2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->unk2 + 1;
    param_1->unk2 = bVar1;
    if (5 < bVar1) {
        param_1->unk2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}
