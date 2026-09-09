/* func_80145CEC — shared body (overlay slot 0x80128158, h_exact 786de7de). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80145CEC() {
    extern int func_80016714();
    extern int func_8001C320();
    extern int func_801552F4();
    extern int func_80147084();
    extern int func_80147098();
    extern int func_801470AC();
    extern int func_80149210();
    extern int func_8014BE9C();
    extern int func_8016533C();
    extern int func_801627C0();
    extern int func_80162AF4();
    extern int func_80165C78();
    extern int func_801468C8();
    extern int func_80145EE8();
    extern int func_8014C968();
    extern int func_8014C6D0();
    extern int func_80165938();
    extern int func_80153C8C();
    extern int func_800290BC();
    extern s32 D_800AFAE8;
    extern s32 D_800DE2A4;
    extern s32 D_801152C8;
    extern s32 D_80180C28;
    extern s32 * D_80126B78[1];
    extern s32 * D_800AF7C8;
    extern s32 * D_80126B90;
    extern s16 D_80126BB8;
    extern s16 D_80126BBA;
    extern s16 D_80126BBC;
    extern s16 D_80126BC0;
    extern s16 D_80126BC2;
    extern s16 D_80126BC4;
    extern s16 D_80126BC8;
    extern s16 D_80126BCA;
    extern s16 D_80126BCC;
    extern s16 D_80126D10;
    extern s16 D_80126D12;
    extern s16 D_80126C4E;
    extern s16 currentLocationId;
    extern s32 D_8011F9C4;
    extern s32 D_8012707C;
    extern s32 D_8011DB10;

    unsigned int uVar1;
    s32 pad[2];
    (void)&pad;

    func_80016714(&D_80126B58, 0x254);
    D_80126B78[0] = (s32 *)&D_800AFAE8;
    D_800AF7C8 = (s32 *)&D_801152C8;
    func_8001C320(&D_800AFAE8, &D_800DE2A4);
    *(s32 *)((s32)D_80126B78[0] + 0x28) = 0x7fff7fff;
    D_80126B90 = (s32 *)&D_80180C28;
    *(u16 *)((s32)D_80126B78[0] + 0x18) = 0x1000;
    D_80126BC8 = 0x1000;
    D_80126BC0 = 0x1000;
    D_80126BB8 = 0x1000;
    *(u16 *)((s32)D_80126B78[0] + 0x1a) = 0x1000;
    D_80126BCA = 0x1000;
    D_80126BC2 = 0x1000;
    D_80126BBA = 0x1000;
    *(u16 *)((s32)D_80126B78[0] + 0x1c) = 0x1000;
    D_80126BCC = 0x1000;
    D_80126BC4 = 0x1000;
    D_80126BBC = 0x1000;
    D_80126D12 = 0x1000;
    D_80126D10 = 0x1000;
    D_80126C4E = 0x1000;
    func_801552F4(&D_80126B58);
    func_80147084(&D_80126B58);
    func_80147098(&D_80126B58);
    func_801470AC(&D_80126B58);
    *(u16 *)((s32)D_80126B78[0] + 0x2c) = *(u16 *)((s32)D_80126B78[0] + 0x2c) | 0x50;
    func_80149210(&D_80126B58, 8);
    func_8014BE9C();
    func_8016533C();
    func_801627C0();
    func_80162AF4();
    func_80165C78();
    func_801468C8(&D_80126B58, 1);
    if (currentLocationId != 0x30a2 && currentLocationId != 0x30a5) {
        func_80145EE8(0);
    }
    func_8014C968();
    func_8014C6D0();
    D_8011F9C4 = 0;
    func_80165938();
    func_80153C8C();
    D_8012707C = 0;
    D_8011DB10 = 0;
    uVar1 = ((int(*)())func_80029504)();
    if (uVar1 >= 10) {
        func_800290BC();
    }
}
