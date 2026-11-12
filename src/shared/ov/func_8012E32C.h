/* func_8012E32C — shared body (overlay slot 0x80128158, h_exact 969f6384). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_CameraWsMatrix; // Names ledger: config/names.tsv guess_g_CameraWsMatrix
extern void SetRotMatrix(void *a0);
extern void SetTransMatrix(void *a0);
void func_8012E32C(void) {
    SetRotMatrix(&guess_g_CameraWsMatrix);
    SetTransMatrix(&guess_g_CameraWsMatrix);
}
