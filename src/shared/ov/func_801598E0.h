/* func_801598E0 — shared body (overlay slot 0x80128158, h_exact c7959a66). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80159968(void *a0);
void func_801598E0(u8 *a0) {
    switch (a0[0xA9]) {
    case 0x41:
        *(u16 *)(a0 + 0xAA) &= 0xAFFF;
        *(u16 *)(a0 + 0xAC) &= 0xAFFF;
        break;
    case 0x53:
    case 0x73:
        *(u16 *)(a0 + 0xAE) = a0[0xAE] | 0x8000;
        break;
    }
    func_80159968((void *)a0);
}
