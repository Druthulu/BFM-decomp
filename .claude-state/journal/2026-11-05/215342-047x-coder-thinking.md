---
ts: 2026-11-06T04:53:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8eEwYBC1nCsAkDIVauoG
---
The function is defined via the #include, so --try with the includer path should work... it says not defined. Maybe the tool requires the TU to contain the definition text. Hmm, but tryinc works by patching recs_for. Let me look at how delever_search finds the function and whether --body uses the TU's text. Since tryinc works, the --body flow is fine; --keep just needs to be passed. Let me write a small wrapper script under my shard dir that mimics tryinc but passes --keep. Actually simpler: copy tryinc.py content with --keep added, under .run/P40/T11/G20x/.

But is that "writing a script under my shard dir"? Allowed (scratch under shard). Let me create .run/P40/T11/G20x/tryinc_keep.py.

Actually maybe I don't need the asm; the diff is informative. But the register-pair list (v1->a0 x5, a0->v0 x4) plus the diff suggests a global-alloc difference. Let me think.

Target (from the diff):
```
...
bne v1,v0, ...
lui a0, &D_80127524
addiu a0
lw v0,0(a0)
bne v0,s0, ...
lui v0, &D_80127528   (maybe)
lw v0,0(v0)
...
beqz v0, ...
sw v0,0(a0)
sh v0,26(v1)
lw a0,0(a0)
jal func_80138C30
nop/move?
```
Mine:
```
lui v1, &D_80127524
addiu v1
lw v0,0(v1)
...
lui a0,&D_80127528
lw a0,0(a0)
...
beqz a0,...
sw a0,0(v1)
sh v0,26(v1)
(load for call arg?)
```
Hmm mine uses v1 for &D_80127524 and a0 for the D_80127528 value; target uses a0 for &D_80127524 and v0 for the value. So the p pointer is in a0 in target, v1 in mine. That's a global-alloc/register choice. In target, v0 holds the loaded D_80127528 value then the store uses v0; a0 holds p. In mine, v1 holds p, v0 the loaded value, a0 the D_80127528 value.

Wait mine: `lui a0; lw a0,0(a0)` — a0 = D_80127528 value; `sw a0,0(v1)` store *p = value; `sh v0,26(v1)` — v0 = 1 (the `1` constant); then call arg = *p reload: in mine, what? The diff says target insn 31-32 insert `sh v0,26(v1); lw a0,0(a0)` while mine has `sh v0,26(v1)` at 32 then target 34-35 nop... Let me get full listings.

Let me write the wrapper.
