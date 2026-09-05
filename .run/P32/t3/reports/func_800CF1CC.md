# func_800CF1CC — MATCH

## Analysis

Target: 21 instructions in md_MAIN_007 binary.

The function:
1. Calls func_800CF408 with parameters (0, D_800D1368)
2. Calls func_800167F0 with parameter 4
3. Tests the lower 16 bits of the return value
4. If non-zero, increments global s32 D_800D1374

## Draft

```c
extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF1CC(void) {
    func_800CF408(0, D_800D1368);

    if ((func_800167F0(4) & 0xFFFF) != 0) {
        D_800D1374++;
    }
}
```

## Verification

- match_one: MATCH (21 ins)
- rtu_match: MATCH (21 ins)
- All symbols (func_800CF408, func_800167F0, D_800D1368, D_800D1374) verified against target assembly relocations
- All symbol declarations copied exactly from destination TU or matched to TU's house style
