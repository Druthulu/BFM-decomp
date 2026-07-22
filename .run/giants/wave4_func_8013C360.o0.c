void func_8013C360(int param_1)
{
    unsigned int *puStack_10;
    unsigned int uStack_c;

    puStack_10 = (unsigned int *)(param_1 + 0x10);
    for (uStack_c = 0; uStack_c < *(unsigned int *)(param_1 + 8); uStack_c++) {
        *(unsigned int *)*puStack_10 = puStack_10[1];
        puStack_10 = puStack_10 + 3;
    }
}
