---
ts: 2026-11-06T09:55:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w5hkgIn26TijqX2jseSJ
---
The toolchain objdump is `mipsel-linux-gnu-objdump`. Let me find the build object for the functions and dump the target function asm. Use run.sh to keep output under control, then read tail.

Let me start with func_8017D730 target. First, item setup: copy current def to orig.c. Let me create a script to extract the function body from src? Simpler: read the exact lines and write orig.c manually.

Let me plan the work per item:

Item 1: func_8017D730 (ov_SC06_006). Body lines 3141-3193. It has:
- pin `register s32 v0 __asm__("$2")`
- keepalive asm `__asm__ __volatile__("" :: "r"(cmp))` on cmp
- pin tmp3 `$3` plus keepalive on tmp3

Need to remove all those. Note `register` vars are forbidden in our output; and no `__asm__`. So rewrite:

```c
void func_8017D730(void) {
    s32 a0;
    s32 v0;
    s32 v1;
    s32 t;
    s32 rem;

    if (!func_8018034C()) {
        func_8017F7C4((s32)&D_80185AFC);
    }
    func_8017FECC(7);
    func_8017FECC(9);
    a0 = D_801F8084;
    if (a0 == 0x5A) {
        D_801F8094 = D_801F8094 + 1;
    }
    if (D_80185CF8 < a0) {
        rem = a0 % D_80185CFC;
        if (rem == D_80185D00) {
            t = ((a0 - 0x171) << 12) / 81;
            v0 = (t * 96) >> 12;
            v1 = 0x7F - v0;
            if (v1 < 0x1F) { v1 = 0x1F; }
            a0 = 0x406;
            if (v1 >= 0x80) { v1 = 0x7F; }
            func_8002D4C8(a0, (u16)(v1 | 0x1000));
        }
        a0 = D_801F8084;
        rem = a0 % D_80185CFC;
        if (rem == D_80185D04) {
            t = ((a0 - 0x171) << 12) / 81;
            v0 = (t * 96) >> 12;
            v1 = 0x7F - v0;
            { s32 cmp = (v1 < 0x1F); }
            { register s32 tmp3 __asm__("$3") = 0x1F; }
            func_8002D4C8(0x407, 0);
        }
    }
}
```

But cmp and tmp3 are dead in the second branch — need to remove entirely (they were levers). So the second branch becomes:
```c
        if (rem == D_80185D04) {
            t = ((a0 - 0x171) << 12) / 81;
            v0 = (t * 96) >> 12;
            v1 = 0x7F - v0;
            func_8002D4C8(0x407, 0);
        }
```
Wait but in the target, the second branch probably computes the same but discards. The v1 computation has no side effect, so flow would delete it if unused... Actually v1 is used in first branch only. In the second branch, v1 assigned but not used → dead. Hmm, but orig had it with the pins to keep it alive (that's why the keepalive). So lever-free it'll be dropped, meaning mismatch unless the target doesn't have it either. Let me check the target asm.

Let me dump the target asm.
