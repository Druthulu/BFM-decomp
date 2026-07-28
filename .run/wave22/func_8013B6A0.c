void func_8013B6A0(s32 idx, u16 *src, s32 val)
{
    typedef struct {
        s32 f0;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        s32 fC;
        u8  pad[0xC];
    } Ent_8013B6A0;
    typedef struct {
        u16 f0;
        u16 f2;
        u16 f4;
    } Src_8013B6A0;
    extern Ent_8013B6A0 D_801DAA08[];

    D_801DAA08[idx].f0 = 1;
    D_801DAA08[idx].f4 = ((Src_8013B6A0 *)src)->f0;
    D_801DAA08[idx].f6 = ((Src_8013B6A0 *)src)->f2;
    D_801DAA08[idx].f8 = ((Src_8013B6A0 *)src)->f4;
    D_801DAA08[idx].fC = val;
}
