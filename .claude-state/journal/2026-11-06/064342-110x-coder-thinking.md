---
ts: 2026-11-06T13:43:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZnBPYOwoOUzpCfZ5hfIn
---
Barrier A removal: only `lbu t7,48(sp)` (the `h` parameter load) is born 2 insns later in mine (index 13 vs 11).

Source:
```
    rgb = 0x808080;
    cyy = cy;
    zf = zoff;
    tpp = tp;
    ww = w;
    hh = h;
    [barrier A]
    pkt = (FT4_801857A4 *)D_800A5E60;
    D_800A5E60 += 0x28;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    *((u8 *)pkt + 3) = 9;
    *(u32 *)&pkt->r0 = rgb;
    pkt->code = 0x2C;
    gte_ldv3(...)
```
The `lbu t7,48(sp)` is `hh = h` (h is a u8 stack parameter at 0x30(sp)? or ww = w?). The target loads it at index 11, mine at 13.

Barrier A is right after the hh assignment. Removing it lets sched1 sink the lbu by 2.

The comment says: "The two zero-byte `__asm__ __volatile__("")` scheduling barriers and the `rgb` local are L1-style dials: they stop sched from sinking the `lbu h` below the D_800A5E60 load and from hoisting the clut chain above the tpage chain."

So barrier A stops sched from sinking the lbu h below the D_800A5E60 load.

Target order around index 11: let me look. Let me dump both listings.

Actually, the fix might be a do-while (C0535) around the hh assignment or the group. Let me try variants:
- do { hh = h; } while (0)
- do { ww = w; hh = h; } while (0)
- reorder: put hh = h earlier/later.
- move `pkt = ...` before the hh assignment? Target: lbu at 11, then D_800A5E60 load...

Let me look at the target disassembly around the start.
