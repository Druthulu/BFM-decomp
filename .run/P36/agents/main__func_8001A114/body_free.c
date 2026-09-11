int func_8001A114(void) {
    int ret;
    u8 *p;
    int r;
    int i;
    CdlFILE *fp;
    int *rp;
    s32 *sp;
    int c0;
    int c1;

    ret = 0;
    switch (D_800AE6F4) {
    case 0:
        func_800434BC();
        c0 = 1;
        c1 = 0;
        p = &cdReq_cdResult;
        func_80043830(c0, (u8 *)c1, p);
        if ((*p & 0x10) != 0) {
            break;
        }
        D_800AE6F4 = D_800AE6F4 + 1;
        /* fallthrough */
    case 1:
        r = func_80046630(0);
        if (r == 2) {
            goto bump;
        }
        if (r != 0x10) {
            break;
        }
    reset:
        D_800AE6F4 = 0;
        break;
    case 2:
        p = &D_800AE740;
        *p = 0x80;
        if (func_80043830(0xE, p, p - 8) == 0) {
            break;
        }
        if ((p[-8] & 0x10) != 0) {
            goto reset;
        }
        cdReq_retry = 0;
        D_800AE6F4 = D_800AE6F4 + 1;
        break;
    case 3:
        rp = &cdReq_retry;
        *rp = *rp + 1;
        if (*rp < 3) {
            break;
        }
        *rp = 0;
        D_800AE6F4 = D_800AE6F4 + 1;
        break;
    case 4:
        r = func_8004674C();
        if ((r == 1) || (r == 0x10) || (r == 0)) {
            D_800AE6F4 = 0;
        }
        if (r != 2) {
            break;
        }
    bump:
        sp = &D_800AE6F4;
        *sp = *sp + 1;
        break;
    case 5:
        i = 0;
        fp = &D_80063028;
        do {
            r = (int)CdSearchFile(fp, (char *)fp - 0x14);
            if (r != -1) {
                break;
            }
            i = i + 1;
        } while (i < 0x10);
        if ((u32)(r + 1) < 2) {
            goto reset;
        }
        ret = 1;
        break;
    }
    return ret;
}
