void func_80035210(s32 a0, s32 a1)
{
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    v1 = D_80076218;
    func_8003C498(v1);
    SpuWrite(a0, a1);
    v1 = D_80076218;
    D_80076218 = v1 + a1;
}
