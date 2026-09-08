/* func_8012A4BC — shared body (overlay slot 0x80128158, h_exact bb9bde6e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151D4;
extern struct BigCopy D_80126DB8;
extern struct BigCopy D_80114EE8;
extern u8 D_80127504;
void func_8012A4BC(void) {
    D_80126DB8 = *(struct BigCopy *)D_801151D4;
    *(struct BigCopy *)D_801151D4 = D_80114EE8;
    D_80127504 = 0x30;
}
