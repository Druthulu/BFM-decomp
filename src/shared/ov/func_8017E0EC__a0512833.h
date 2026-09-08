/* func_8017E0EC — shared body (overlay slot 0x80128158, h_exact a0512833). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80115112;
void func_8017E0EC(void) {
    register s32 *p __asm__("$3"); /* pinned to $v1 */
    register s32 v __asm__("$2"); /* pinned to $v0 */
    p = &D_80115112;
    v = *(u16 *)p + 1;
    *(u16 *)p = v;
}
