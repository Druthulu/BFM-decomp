struct S { char pad[0x68]; int idx; };

extern void (*D_8017EBC0[])();

void func_8013BC7C(struct S *param_1) {
    D_8017EBC0[param_1->idx](param_1);
}
