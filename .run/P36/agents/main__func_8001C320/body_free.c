void func_8001C320(s32 a0, s32 a1)
{
    extern void func_8001C9D0(void);
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern void GsMapModelingData(u32 *p);
    extern void GsLinkObject5();
    extern void *GsPresetObject();
    extern u8 D_800AF630[];
    extern u8 D_80063548[];
    extern u16 D_800AF7CC;
    extern s32 *D_800AF7C8;
    extern u8 D_800A5BD0[];

    s32 sp10[8];
    s32 obj;
    s32 next;
    s32 work;
    s32 entry;
    u16 c2;

    obj = a0;
    func_8001C9D0();
    *(u16 *)obj = 1;
    *(u16 *)(obj + 2) = 1;
    func_80052D90(0, (void *)(obj + 0x30));
    func_80054514(obj + 0x30, (s32)&sp10[0]);
    work = (s32)D_800AF630;
    *(s32 *)(obj + 0x24) = a1;
    if (a1 != 0) {
        *(s32 *)(obj + 0x20) = (s32)D_80063548;
        next = (s32)D_800AF7C8;
        *(u16 *)(obj + 0x2E) = D_800AF7CC;
        if (*(s32 *)a1 != 0) {
            do {
                entry = (*(s32 *)a1 & 0x80FFFFFF) + 4;
                a1 += 4;
                GsMapModelingData((u32 *)entry);
                c2 = *(u16 *)(work + 0x19C);
                *(u16 *)(work + 0x19C) = c2 + 1;
                GsLinkObject5((u32 *)(entry + 8),
                              (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], 0);
                next = (s32)GsPresetObject(
                    (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], (void *)next);
            } while (*(s32 *)a1 != 0);
        }
        *(s32 *)(work + 0x198) = next;
    }
}
