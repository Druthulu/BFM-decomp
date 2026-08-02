extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC03_014_jr_801848E4.c L2534) */
extern void func_80172710(void);

s32 func_801859B0(void *a0)
{
    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        return 0;
    }

    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 2;
    func_80178BF8();
    return (s32)func_80172710;
}
