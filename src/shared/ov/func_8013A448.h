/* func_8013A448 — shared body (overlay slot 0x80128158, h_exact 46170b36). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A530();
void func_8013A448(void *a0) {
    s16 *a1 = *(s16 **)((char *)a0 + 0x4);
    if (*(u16 *)((char *)a0 + 0x2) == 0) {
        *(s16 *)((char *)a1 + 0x2A) = 0x400;
        *(s16 *)((char *)a1 + 0x28) = 0x400;
        *(s16 *)((char *)a0 + 0x2) = *(u16 *)((char *)a0 + 0x2) + 1;
    } else {
        *(s16 *)((char *)a1 + 0x28) = *(u16 *)((char *)a1 + 0x28) + 0x200;
        *(s16 *)((char *)a1 + 0x2A) = *(u16 *)((char *)a1 + 0x2A) + 0x200;
        if (*(s16 *)((char *)a1 + 0x28) == 0x1000) {
            *(s16 *)((char *)a0 + 0x0) = 2;
            *(s16 *)((char *)a0 + 0x2) = 0;
        }
    }
    func_8013A530();
}
