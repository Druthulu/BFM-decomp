/* func_8012F038 — shared body (overlay slot 0x80128158, h_exact b4078382). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
void func_8012F038(int param_1, short *param_2, short *param_3) {
    int in[3];
    int out[3];
    in[0] = (int)param_2[0] - *(int *)(param_1 + 0x14);
    in[1] = (int)param_2[1] - *(int *)(param_1 + 0x18);
    in[2] = (int)param_2[2] - *(int *)(param_1 + 0x1c);
    ApplyTransposeMatrixLV((void *)param_1, in, out);
    param_3[0] = out[0];
    param_3[1] = out[1];
    param_3[2] = out[2];
}
