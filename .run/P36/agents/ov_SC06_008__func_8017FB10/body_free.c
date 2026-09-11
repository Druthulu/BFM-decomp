void func_8017FB10(s32 a0)
{
    SV4 in;
    SV4 out;
    s16 v1;
    u16 uStack_c;

    if (*(u16 *)(a0 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, *(s16 *)(a0 + 0x70) * 12 + (s32)&D_8019C970);

        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        func_8012F214(a0, (s32)&in, (s32)&out);
        *(u16 *)(a0 + 6) = out.a;
        *(u16 *)(a0 + 0xa) = out.b;
        uStack_c = out.c;
        *(s32 *)(a0 + 0x1c) = 0x5a;
        *(u16 *)(a0 + 0x34) = 1;
        *(u16 *)(a0 + 0xe) = uStack_c;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += -0x80;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 4;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0xfc);

    *(s32 *)(a0 + 0xdc) = *(s32 *)(a0 + 0x14);
    if ((((s32 (*)(s32))func_8012CBCC)(a0)) & 0x6000) {
        s32 negdc;
        negdc = -*(s32 *)(a0 + 0xdc);
        v1 = *(u16 *)(a0 + 0xac);
        v1 -= 1;
        *(s16 *)(a0 + 0xac) = v1;
        *(s32 *)(a0 + 0x14) = negdc;
        if (v1 == 0) {
            func_8012C218((void *)a0);
        }
    }

    {
        s32 iVar3 = *(s32 *)(a0 + 0x1c) - 1;
        *(s32 *)(a0 + 0x1c) = iVar3;
        if (iVar3 == 0) {
            func_8012C218((void *)a0);
        }
    }
}
