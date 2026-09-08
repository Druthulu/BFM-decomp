/* func_8014B084 — shared body (overlay slot 0x80128158, h_exact bbc5441e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80078EAC;
extern u8 D_80078EBA;
extern void func_800D10EC(void);
extern void func_8002AC98(void);
extern void func_80145C54(void);
void func_8014B084(void) {
    u16 a;
    u8 b;
    a = D_80078EAC + 1;
    b = D_80078EBA + 1;
    D_80078EAC = a;
    D_80078EBA = b;
    if (a >= 0x16E) {
        D_80078EAC = 1;
    }
    D_80078EBA = b % 7;
    func_800D10EC();
    func_8002AC98();
    func_80145C54();
}
