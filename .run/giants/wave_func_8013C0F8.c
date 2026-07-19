typedef struct Foo {
    unsigned char pad[0xc];
    unsigned int count;   /* 0xc */
    int field10;          /* 0x10 */
} Foo;                    /* size 0x14 */

typedef struct Bar {
    unsigned char b0;     /* 0x0 */
    unsigned char b1;     /* 0x1 */
    unsigned char b2;     /* 0x2 */
    unsigned char tag;    /* 0x3 */
    unsigned int a;       /* 0x4 */
    unsigned int b;       /* 0x8 */
} Bar;                    /* size 0xc */

void func_8013C0F8(int param_1) {
    int iVar1;
    int iVar2;
    unsigned int local_18;
    unsigned int local_14;
    Bar *local_10;
    Foo *local_c;

    iVar1 = param_1 + 0x14;
    if (*(char *)(param_1 + 4) == '\0') {
        iVar2 = iVar1 + *(int *)(param_1 + 0xc);
        *(int *)(param_1 + 0xc) = iVar2;
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + iVar1;
        local_c = (Foo *)iVar1;
        for (local_18 = 0; local_18 < *(unsigned int *)(param_1 + 8); local_18++, local_c++) {
            local_c->field10 = local_c->field10 + iVar1;
            local_10 = (Bar *)local_c->field10;
            for (local_14 = 0; local_14 < local_c->count; local_14++, local_10++) {
                switch (local_10->tag) {
                case 0x24:
                case 0x2c:
                case 0x34:
                case 0x3c:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                case 0x26:
                case 0x2e:
                case 0x36:
                case 0x3e:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                }
            }
        }
        *(unsigned char *)(param_1 + 4) = 1;
    }
}
