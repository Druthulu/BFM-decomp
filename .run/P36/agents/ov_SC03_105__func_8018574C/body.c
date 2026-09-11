void func_8018574C(void *a0) {
    s32 s0 = (s32)a0;
    s32 rnd;
    s32 t;
    s32 base;
    s32 rem;
    s32 result;
    s16 tmp[3];
    u8 aux[8];

    rnd = rand();
    t = *(s16 *)(s0 + 0xC);
    base = *(s16 *)(s0 + 0x14);
    /* `(s16)t >> 7` (P36 S104 e32): the cast at the shift keeps the target's lh + sra,7;
       `t >> 7` lets combine fold the load's sign extension into lhu + sll,16 + sra,23. */
    rem = rnd % ((s16)t >> 7);
    if (rand() & 1) {
        result = base + rem;
    } else {
        result = base - rem;
    }
    tmp[0] = result;
    tmp[1] = *(u16 *)(s0 + 0x16) + *(u16 *)(s0 + 0x1E);
    tmp[2] = *(u16 *)(s0 + 0x18);
    func_8012F214(*(s32 *)(s0 + 0x20), (s32)tmp, (s32)aux);
    func_8017E5C8((s32)aux);
}
