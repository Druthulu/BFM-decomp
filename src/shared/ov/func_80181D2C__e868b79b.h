/* func_80181D2C — shared body (overlay slot 0x80128158, h_exact e868b79b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8018EA0C[])(void);
void func_80181D2C(u8 *param_1)
{
    D_8018EA0C[param_1[0x4]]();
}
