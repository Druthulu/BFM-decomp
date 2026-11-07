---
ts: 2026-11-06T05:23:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4M5YxzrBFkvRV5j5FYVN
---
Baseline 0. Now write lever-free n1: remove pin (register s32 iVar1 → s32 iVar1) and remove both launders (the `tmp = iVar2; asm;` lines). Let me construct.

The function:

```c
void func_80181784(s32 a0)
{
    s32 iVar1;
    s32 iVar2;
    s32 tmp;
    s32 pad[4];

    func_80181B00(a0);
    func_801820F8(a0);

    iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
    iVar2 = CAST_SIGN(s16, iVar1, 0x10);
    if (iVar2 != 0) {
        tmp = iVar2;
        if (iVar2 < 0) {
            tmp += 0x80;
            ...
```

Note `tmp = iVar2;` remains — that's a real C copy (not a lever). The launder line removed.

Let me create n1 by removing the pin and the two asm lines.

Then score.

Also need to know what the target asm looks like — the pin is $3 for iVar1 (the pointer). iVar1 holds the unk20 pointer across the branches and is reloaded at the end of the first block. The launder on tmp prevents cse from merging tmp with iVar2.

Let's first see the naive score.
