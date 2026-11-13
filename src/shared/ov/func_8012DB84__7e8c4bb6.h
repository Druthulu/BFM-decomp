/* func_8012DB84 — shared body (overlay slot 0x80128158, h_exact 7e8c4bb6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of guess_SetPlayerHit; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x40, ov_SC04_008 objdump */
s32 func_8012DB84(void)
{
    func_8014C978();
    guess_SetPlayerHit(1, 0xC001, 0, 0x3E8, &D_8017EE08, &D_8017EE10);
}
