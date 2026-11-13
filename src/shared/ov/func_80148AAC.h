/* func_80148AAC — shared body (overlay slot 0x80128158, h_exact 29761741). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80148AFC(void *a0);
/* $v0 at exit: andi $v0, $v0, 0xFF at ov_MAIN_012:0x80148AC0 or andi $v0, $v0, 0xFF8 at ov_MAIN_012:0x80148AE0; no byte-neutral return: `return 0;` moved `beqz v0,<func_80148AAC+0x40>` at +0x18, ov_MAIN_012 objdump */
s32 func_80148AAC(u8 *a0) {
    u8 *v1;
    if ((func_80148AFC(a0) & 0xff) != 0) {
        v1 = *(u8 **)(a0 + 0x20);
        *(u16 *)(v1 + 0x12) = (*(u16 *)(v1 + 0x12) + 0xFA) & 0xFF8;
    }
}
