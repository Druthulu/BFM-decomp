s32 func_801818A4(void *a0, void *a1) {
    s16 stack_buf[8];
    s16 v0;
    s32 result;
    s32 ret;

    v0 = ((s16 *)a1)[6];
    stack_buf[2] = v0;
    v0 = ((s16 *)a1)[7];
    stack_buf[5] = 0;
    stack_buf[1] = 0;
    stack_buf[6] = v0;
    v0 = ((s16 *)a1)[2];
    stack_buf[4] = v0;
    stack_buf[0] = v0;

    result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = ((s16 *)a1)[3];
        stack_buf[4] = v0;
        stack_buf[0] = v0;
        result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}
