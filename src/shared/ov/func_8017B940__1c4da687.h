/* func_8017B940 — shared body (overlay slot 0x80128158, h_exact 1c4da687). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_8018F994);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_8018F996);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_8018F998);
    (*(s16 *)&D_8018F99C) = buf[0];
    (*(s16 *)&D_8018F99E) = buf[1];
    (*(s16 *)&D_8018F9A0) = buf[2];
    D_8018F98C = D_80114F30 + buf[0];
    D_8018F914 = 0;
    D_8018F98E = D_80114F34 + buf[1];
    D_8018F990 = D_80114F38 + buf[2];
    D_8018F984 = D_80114F24 + buf[0];
    D_8018F986 = D_80114F28 + buf[1];
    D_8018F988 = D_80114F2C + buf[2];
}
