/* func_8012A464 — shared body (overlay slot 0x80128158, h_exact 7bec4d36). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_g_ActiveCamera;
extern Vec8 guess_g_StoredViewPointX;
void func_8012A464(void)
{
    guess_g_StoredViewPointX = *(Vec8 *)(*(s32 *)&guess_g_ActiveCamera + 0x3C);
}
