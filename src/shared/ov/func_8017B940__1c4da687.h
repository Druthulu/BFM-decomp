/* func_8017B940 — shared body (overlay slot 0x80128158, h_exact 1c4da687). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&guess_g_PlayerPosX) - (*(s16 *)&D_8018F994);
    buf[1] = (*(s16 *)&guess_g_PlayerPosY) - (*(s16 *)&D_8018F996);
    buf[2] = (*(s16 *)&guess_g_PlayerPosZ) - (*(s16 *)&D_8018F998);
    (*(s16 *)&D_8018F99C) = buf[0];
    (*(s16 *)&D_8018F99E) = buf[1];
    (*(s16 *)&D_8018F9A0) = buf[2];
    D_8018F98C = guess_g_StoredRefPointX + buf[0];
    D_8018F914 = 0;
    D_8018F98E = guess_g_StoredRefPointY + buf[1];
    D_8018F990 = guess_g_StoredRefPointZ + buf[2];
    D_8018F984 = guess_g_StoredViewPointX + buf[0];
    D_8018F986 = guess_g_StoredViewPointY + buf[1];
    D_8018F988 = guess_g_StoredViewPointZ + buf[2];
}
