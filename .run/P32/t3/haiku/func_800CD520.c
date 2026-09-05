const u32 D_800CD364[] = { 0x545C3A43, 0x41504D49, 0x4F5C4B43, 0x4D454450, 0x502E314F, 0x65005441, 0x3C02800C, 0x9442AE04 };

/* func_8001AD38 is declared by the TU at file scope as (const char*) — spelled like the TU (§376) */
extern s32 D_800CDD34;
extern void func_800116A0(void);

void func_800CD520(void) {
    func_8001AD38((const char *)D_800CD364);
    D_800CDD34 = 0;
    func_800116A0();
}
