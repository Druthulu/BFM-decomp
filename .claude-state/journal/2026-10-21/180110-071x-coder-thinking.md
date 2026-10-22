---
ts: 2026-10-22T00:01:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jOhgxkeZgv5p6MENB13v
---
While that runs, let me work on another item. Let me try func_80180480 (pin $3 on `p`).

The source:
```c
void func_80180480(s32 a0) {
    extern s16 D_800B9AAC[];
    extern s16 D_800B9B00;
    extern s32 D_801151D4;
    extern s32 func_8012E544(s32 a0);
    extern void func_8012C098(void *a0);
    extern void func_8012BF4C(s32 *a0, s32 a1);
    extern s32 func_8013D13C(void);
    extern s32 func_8012AD50(void *a0);
    register s32 p __asm__("$3");  // !FAKE: pin $3
    s32 v0;

    p = D_801151D4;
    v0 = ((Unkstruct_80126948 *)p)->unk10;
    v0 = v0 - 3;
    ((Unkstruct_80126948 *)p)->unk10 = v0;
    ((Unkstruct_80126948 *)p)->unk14 = v0;
    if (((s32 (*)(s32))func_8013D13C)(10) == 0) {
        ...
    }
}
```
Let me see the rest (lines 5874+).

The pin is $3 (v1). So p is in v1. Removing the pin → p would be allocated to a callee-saved reg (since it's live across calls) or a caller-saved one.

Let me look at the target to see where p lives.

Let me read the rest of the source and getthe target.
