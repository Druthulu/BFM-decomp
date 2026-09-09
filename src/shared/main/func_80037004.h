/* the clearTbl40 pair — ONE body at two addresses of main (h_exact a0744d60): the name-parameterized
 * include form — the site defines SHARED_FN, includes this, undefines it (Phase 35; the worked example
 * for the deferred cross-address classes). Members: config/dedup.us.yaml I0_clearTbl40. */
extern u8 D_80076251;

void SHARED_FN(void) {
    s32 i;
    for (i = 0x40; i >= 0; i -= 0x10) {
        (&D_80076251)[i] = 0;
    }
}
