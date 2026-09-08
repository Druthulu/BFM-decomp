/* func_80157D74 — shared body (overlay slot 0x80128158, h_exact d1410418). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80157DC4(void *a0);
extern void func_80157FC4(void *a0);
void func_80157D74(u16 *a0) {
    switch (a0[0]) {
    case 0x24:
        func_80157DC4(a0);
        break;
    case 0x25:
        func_80157FC4(a0);
        break;
    }
}
