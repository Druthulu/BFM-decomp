/* func_8018178C — shared body (overlay slot 0x80128158, h_exact 5b1ba7c9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80184CB8(s32*, s32);
    extern short D_80191B34;
    void func_8018178C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 9;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_80191B34);
    }
