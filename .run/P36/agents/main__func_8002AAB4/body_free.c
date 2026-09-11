s32 func_8002AAB4(void) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 v0;
    s32 *v1;
    s32 a0;
    s32 *a1;

    // Get values from the four functions
    s0 = func_8002A26C();
    s2 = func_8002A4B8();
    s1 = func_8002A728();
    v0 = func_8002A998();

    // Sum them: s0 = s0 + s2 + s1; v0 = s0 + v0
    s0 = s0 + s2;
    s0 = s0 + s1;
    v0 = s0 + v0;

    // Rounding: if v0 < 0, add 3 before dividing by 4
    if (v0 < 0) {
        v0 = v0 + 3;
    }

    // Divide by 4 using arithmetic right shift
    s0 = v0 >> 2;

    // Initialize pointer to table
    v1 = D_800638A0;
    a0 = v1[0];

    // If the first threshold is 0, return the default
    if (a0 == 0) {
        return D_800638EC;
    }

    a1 = v1 + 1;

    // Search through the table
    while (1) {
        if (s0 >= a0) {
            return a1[0];
        }

        v1 = v1 + 2;
        a0 = v1[0];

        if (a0 == 0) {
            return D_800638EC;
        }

        a1 = a1 + 2;
    }
}
