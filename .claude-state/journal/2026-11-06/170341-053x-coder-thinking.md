---
ts: 2026-11-07T00:03:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JNXtCzoNmHFMaSJSPh10
---
Let me map:
- r80: 24 refs, live 66, crosses 1 call → param_1? param_1 is used in func_8012DDE2C (call 1), *(param_1+0x58), func_80013350(param_1+4,...) (call). Hmm 24 refs is a lot for param_1.

Hmm wait. Let me reconsider. Maybe r80 = iVar1 (the loop cursor, used many times in the loop body) — 24 refs, live 66. Yes! iVar1 is used ~15-20 times in the loop.

- r81: 20 refs, live 60 → param_1? The self pointer used ~20 times? Let me count param_1 uses: func_8012DDE2C(param_1) [1], *(u32*)(param_1+0x58) [2], then in the loop `func_80013350(param_1+4, iVar1+4)` [3]. Only 3. Hmm, no.

Wait, the loop body:
```
u16 uVar6 = *(u16*)(iVar1+0x5c);       // iVar1
if ((uVar6 & 0x8000) != 0) {
  if ((uVar6 & 0x4000) == 0) {
    if (*(u16*)(iVar1+0x5e) != param_4) {
      if ((*(u16*)(iVar1+0xae) & 1) == 0) {
        if (func_80013350(param_1+4, iVar1+4) < iVar5) {
          *(u16*)(iVar1+0x60) = param_2;
          *(u16*)(iVar1+0x62) = param_3;
          *(u16*)(iVar1+0x5e) = param_4;
          *(u16*)(iVar1+0x5c) = *(u16*)(iVar1+0x5c) | 1;
        }
      }
    }
  }
}
iVar1 = func_8012DDA4();
```
iVar1: many uses (~14). param_1: 2 (in func_80013350 arg and earlier). param_2,3: 1 each. param_4: 2.

So r80 (24 refs) = iVar1? and r81 (20 refs) = ??? Hmm.

Hold on, maybe iVar1 is r80 with 24 refs and r81 is param_1 with... no, 20.

Hmm, wait. Maybe the pseudos include uVar3, iVar5, etc. r81 20 refs — could be uVar6 (the loaded halfword, used in tests and the final store)? uVar6: used in (uVar6&0x8000), (uVar6&0x4000), and `*(u16*)(iVar1+0x5c) = *(u16*)(iVar1+0x5c) | 1`. ~4.

Hmm. Let me just get the actual register assignment from the .lreg dump. Let me grep "Register N in M" lines within the function.

Actually, the .lreg dump prints ";; Register N in M." lines. Let me grep those for this function.
