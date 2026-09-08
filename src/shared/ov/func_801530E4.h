/* func_801530E4 — shared body (overlay slot 0x80128158, h_exact 2ddaebea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void func_801474EC(s32 *a0);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern void func_80155440(s32 *a0);
extern u8 D_80062C04[];
void func_801530E4(s32 arg0)
{
    func_80019064(&D_80062C04);
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x40;
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80155440(arg0);
    func_80146CA0(arg0);
}
