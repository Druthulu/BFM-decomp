void func_801836B0(void *arg0)
{
    if (*(s16 *)((s32)arg0 + 0xFE) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);
        *(s16 *)((s32)arg0 + 0xFE) = 0;
        *(s16 *)((s32)arg0 + 0x102) = 0;
    }
    ((void (*)(void *, s32))func_8012AD44)(arg0, 3);
    if (*(s16 *)((s32)arg0 + 0xFC) == 0) {
        *(u16 *)((s32)arg0 + 0x34) = 2;
        *(s32 *)((s32)arg0 + 0x1C) = 0x40;
    }
}
