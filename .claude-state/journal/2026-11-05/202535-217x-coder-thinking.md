---
ts: 2026-11-06T03:25:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BZlmuZQ1wpEM1yZ9TRPI
---
Still 56. Maybe reload folded the pointer into the address, making it a PLUS again at cse time? cse runs BEFORE reload (cse1), so at cse1 the store's address is (reg q) — not a PLUS → should invalidate. Unless the front end expands `*(u16*)(obj+0x14)` to a PLUS-based MEM anyway (it does: the address is computed as (plus obj 20) and assigned to q; the store via q is (mem (reg q))). Hmm, cse's cse_rtx_addr_varies_p(written) checks whether the address varies; (reg q) is a register (varies? it's a pseudo, so "varies" = depends on a register that's not the stack/frame pointer). So all=1 should be set → invalidate the global.

But cse still forwarded. Maybe the forwarding happens in a different pass, not cse1? The count after cse1 was 2 (vs 3 in rtl) for nopin. For r1 I checked: cse refs = 2. So cse1 dropped one. Hmm.

Wait, maybe the two D_80126B78 loads are NOT separated by the store in the RTL order! Let me look at the RTL: the source is:
```
obj = unk20;
store = load(obj+0x14) + (unk2A - load(D_80126B78+0x12));
[barrier]
unk2A = load(D_80126B78+0x12);
```
The RTL order: load obj; load obj+0x14; load D_80126B78; lhu; ...; store obj+0x14; [barrier]; load D_80126B78; lhu; store unk2A.

The two global loads are separated by the store to obj+0x14. cse should invalidate at the store if all=1.

Unless the store's write_data sets nonscalar (PLUS) — the address is (plus (reg obj) 20) because `obj + 0x14` is expanded as a PLUS even when assigned to a pointer q! The pointer q = (u16*)(obj + 0x14) is a REG; the store `*q` is (mem (reg q)). Hmm, but gcc might substitute q's value (obj+20) via cse/combine before cse1? No, cse1 is the first cse.

Hmm, wait: `MEM_IN_STRUCT_P (written)` — for `*q` where q is `u16*`, the MEM is not in-struct. The address is (reg q). `cse_rtx_addr_varies_p` — let me check: does a pseudo register count as varying? The function:
```
static int cse_rtx_addr_varies_p (x)
{
  ...
  if (GET_CODE (x) == REG)
    return REGNO (x) >= FIRST_PSEUDO_REGISTER && ! (regno...)
```
Hmm. Let me read it. Also the `written` for a store via q: (mem:HI (reg q)). The `addr = (reg q)` is not PRE_DEC etc., not BLKmode, not SCRATCH. `cse_rtx_addr_varies_p(written)` → true (a pseudo). Then `if (!((MEM_IN_STRUCT_P(written) || GET_CODE(XEXP(written,0)) == PLUS) && GET_MODE(written) != QImode)) writes_ptr->all = 1;`
- MEM_IN_STRUCT_P(written) = 0; GET_CODE(addr) = REG, not PLUS → the condition is false → all=1. So all=1 → invalidate everything. Should work!

Unless cse doesn't even consider the store because the two loads were merged EARLIER (in `combine`? no, cse1 runs before combine). Or maybe the forwarding happens in `flow`? Let me check the RTL (before cse1): 3 refs. After cse1: 2. So cse1 did it. Hmm, but for s1 (pointer store), did the .cse dump still show 2? Let me check s1's cse dump.

Actually, maybe the two global loads are in different basic blocks or the store isn't between them in the cse sense... Let me look at the nopin .rtl around the loads and the store.
