---
ts: 2026-11-06T03:43:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tFeJ9Yfkmm6K3P91j24v
---
Item 1: baseline lever-free body reorders statements. The barriers in orig were placed to keep ordering. Let me look at the target assembly to understand. The function writes a bunch of globals. The barrier after `D_8012697C = D_801864AC[idx];` keeps that store before the following load/store group.

The diff: at mine[36:36], target inserts the `D_8012697C = D_801864AC[idx]` group (lui/addu/lw/lui/sw) — meaning in lever-free mine, this group moved later. And mine[39:42] has the D_80126980 load moved earlier. So sched1/reorder moves.

Wait, actually those are target instructions appearing where mine has them elsewhere — it's a scheduling order difference, not missing code (68 = 68 ins).

The barrier `__asm__ __volatile__("" ::: "memory")` forces memory ops ordering. Without it, the compiler reorders the D_8012697C store relative to D_80126980 store etc.

To replace: create a real data dependency between statements. For instance, the index `idx` used for both loads: `D_8012697C = D_801864AC[idx];` and `(D_80126980[0]) = D_801864B8[idx];`. cse may share `idx`. We need ordering. Hmm.

Let me get the target disassembly to see the exact order. Let me use the tools. Maybe there's a tgt file in the item dir? No. delever_search has --explain? It compares. Let me check if there's a way to dump target disassembly: tools/cc1_dumps_tu.sh or dt.sh prints diff only. There's .run/P40/T10/func_80181F4C/tgt maybe a target disassembly. Let me see how it was made.

Actually maybe simpler: read the full orig body and reason. Let me look at orig.c.

The body:
```
idx = func_800291B4(0xE0) & 0xFF;
D_80126954 = 0x64;
D_8012695C = 0x80;
D_8012696A = 0x800;
D_80126968 = 0;
D_8012696C = 0;
D_80126976 = 0;
D_80126978 = 0x70;
D_8012697A = 0;
func_8012A018((s32)func_8017D8C4, 0);
func_8012A094((s32)D_80126948);
D_8012697C = D_801864AC[idx];
[barrier]
(D_80126980[0]) = D_801864B8[idx];
t = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = t;
[barrier]
D_801A1274 = D_801864D0[idx];
func_8017D8C4(D_80126948);
D_801151D4 = (s32)D_80126948;
```

Target order around 36: after the call func_8012A094, target does:
lui at,0x0; addu at,at,s0; lw v0,0(at); lui at,0x0; sw v0,0(at)  -> D_8012697C = D_801864AC[idx]
then presumably load D_801864B8[idx] → D_80126980.

Mine lever-free does: first loads D_801864B8[idx] (lui/addu/lw a1) then... hmm mine[39:42] delete: lui at; addu at,at,s0; lw a1,0(at) — that's a load into a1 (the B8 load). So mine does B8 load before AC load/store.

So the barrier forces the AC store first. In C, statements are in that order already; but the scheduler reorders independent loads. To create dependency, we can make the second store depend on the first. E.g. `(D_80126980[0]) = D_801864B8[idx] + (D_8012697C == 0 ? 0 : 0)`? That's a fake identity. Hmm, identity-statement launders do NOT count as a crack. But that's for launders of asm, e.g. `w = (w>>16<<16)|x`. A real data dependency that preserves value... Hmm.

Actually maybe simpler: the target's order could be achieved by restructuring C so that idx is used twice in a dependent way. But careful: what does "identity-statement launder" mean exactly: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". So a `+0` dependency trick probably doesn't count as a crack either.

Let me first look at the full target/mine to understand what score 20 consists of. There are multiple reorderings. Maybe a simple reordering of statements or splitting temps gives the target order naturally.

Let me get the target disassembly. How? Let me check delever_search --explain or find the object. Maybe tools/ has a disassembler helper. Let me check tools listing for a target dump tool.

Actually `dt.sh` output shows target diff inline. The full function diff shows only mismatched region. I can infer.

Let me consider: maybe moving the `D_8012697C = ...` assignment to a temp then storing later? The target does the load+store of AC immediately after the call, and B8 load later. In mine, sched1 hoisted B8 load above the AC store. To prevent hoisting the B8 load above the AC store, make the B8 index depend on the AC store value? But that's fake.

Alternative: maybe write the stores via a helper? Hmm.

Wait — maybe the real trick is that the barriers aren't needed at all if the C is restructured; maybe the function was already decompiled with barriers as a crutch, but a different plain-C form gives the same order. The moves.md shows barrier items cracked by "init at decl" (G18). Here barriers are memory barriers around global stores.

Let me look at the target disassembly fully. I'll use tools/cc1_dumps_tu.sh? That gives TU dumps from cc1. But the target disassembly — how is the target obtained? delever_search compares with "the function in build/". The build/ has the compiled object? Wait: "compares with the function in build/". Hmm, build/ is the built ROM object? Actually build/ likely contains the reference object disassembly from the ROM. Let me look at delever_search source briefly to find where target comes from.
