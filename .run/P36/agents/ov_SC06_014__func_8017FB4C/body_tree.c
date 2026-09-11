void func_8017FB4C(void *a0)
{
    void *s3 = a0;
    void *s2;
    void *p;
    s32 v1;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 bits;
    s32 s0;
    s32 s1;

    s2 = *(void **)((s32)s3 + 0x20);
    func_8017FD74(s3);
    p = (*(void * *)&D_801A14A8);
    if (p == 0) {
        goto END;
    }
    v0 = *(u16 *)((s32)s2 + 0x12) + 0x800;
    p = *(void **)((s32)p + 0x20);
    bits = *(u16 *)((s32)p + 0x12) & 0x400;
    s0 = v0 & 0xFFF;
    if (bits == 0) {
        goto ELSE;
    }
    s1 = func_80012A60(s0, 0x400);
    v0 = func_80012A60(s0, 0xC00);
    v1 = (s16)s1;
    v0 = (s16)v0;
    v0 = (v0 < v1);
    if (v0 != 0) {
        goto TRUE1;
    }
    v0 = 0x400;
    goto STORE;
TRUE1:
    v0 = 0xC00;
    goto STORE;
ELSE:
    s1 = func_80012A60(s0, 0);
    v0 = func_80012A60(s0, 0x800);
    v1 = (s16)s1;
    v0 = (s16)v0;
    v0 = (v0 < v1);
    if (v0 != 0) {
        goto TRUE2;
    }
    *(u16 *)((s32)s2 + 0x12) = 0;
    goto END;
TRUE2:
    v0 = 0x800;
STORE:
    *(u16 *)((s32)s2 + 0x12) = v0;
END:
    func_80171990((u8 *)s3);
}
