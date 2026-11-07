---
ts: 2026-11-06T05:38:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UP9NfhP5ONdpNm6Vb6MB
---
The structure:
```
if (ret != 0) {
    ... stores ...
    if (*(u16*)(arg0+0x16C) != 0x1D) return ret;
    if ((func_80029178(0x21) & 0xFF) == 0) { ret &= ~0x2000; ret |= 0x4000; memcpy; D_801152BC = 1; }
    return ret;
}
```
The two `return ret` merge.

Variants to try:
v2: invert the condition:
```
    if (*(u16 *)(arg0 + 0x16C) == 0x1D) {
        if ((func_80029178(0x21) & 0xFF) == 0) { ... }
    }
    return ret;
```
v3: 
```
    if (*(u16 *)(arg0 + 0x16C) == 0x1D) {
        if (...) { ... }
        return ret;
    }
    return ret;
```
v4: use an else:
```
    if (*(u16 *)(arg0 + 0x16C) == 0x1D) {
        if (...) { ... }
        return ret;
    } else {
        return ret;
    }
```
v5: move the `ret |= 0x4000` differently.

Let me test v2/v3.

Also, note that mine's issue might be *only* the branch shape (2 insns) + the ori placement. Let me try v2 first.
