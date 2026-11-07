---
ts: 2026-11-06T21:39:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ggiLWtLeDVyLCzX8AwFe
---
Reproduced score 13. Now the residual is a register swap v1<->a0 across 10 instructions. The notes: "the only residual is a v1<->a0 swap on the tail (`lw v1,0(a3)` tag value vs `lw v1,20(sp)` oidx): local-alloc gives the tag-load qty $3 and oidx $4; the target has oidx $3 and the tag $4 (the $3 pin on oidx)."

So local-alloc assigns $3 to the "tag value" qty and $4 to oidx. We need the opposite. local-alloc qty priority: it assigns registers in order of... In local-alloc, qty_compare uses `qty->n_deaths`? Let me recall gcc 2.7.2 local-alloc.c qty_compare_1:

```c
static int
qty_compare_1 (q1, q2)
{
  ...
  /* Consider "quantity" of register usage. */
  if (q1->n_refs != q2->n_refs)
    return q1->n_refs - q2->n_refs; ...
```
Hmm actually let me read the source in tools/reference/gcc-2.7.2/local-alloc.c. Let me grep for qty_compare.

The two pseudos: oidx (g.otz<<2) is computed once and used at insn 166/170/172 and later at 187? Let's map the diff. mine insn 162 lw v1,0(a3) vs target lw a0,0(a3). That's loading arg3? Wait `lw 0(a3)` — a3 is the 4th arg (arg3, s32*). Hmm at 162? That seems late. Actually target body: the tail uses `*(u16 *)(base+0xA3D2)`? base is a0? Let me get the full disassembly to understand. Use dt.sh output? It only gives diff. Maybe use --keep to get object and objdump. Or read the target listing from the build? The dt.sh compares with function in build/. Let me just get the full diff text.

Actually I can reconstruct: mine[162] = lw v1,0(a3). Hmm what is at 0(a3)? arg3 is s32* used at top for i. Wait no — maybe registers shifted: the diff shows 10 pairs v1->a0 and a0->v1. It's a pure swap of two pseudo registers across a region. The two pseudos: one is "tag value" loaded via lw 0(a3)? Hmm, "lw v1,0(a3) tag value" — maybe the `*(u16 *)(base + 0xA3D2)` load, where a3 = base+...? No, base is a pointer; but at that point a3 could hold base+0xA3D2. Yes! `*(u16 *)(base + 0xA3D2)` may be compiled as addiu a3, base, 0xA3D2 then lw v1,0(a3). Hmm but the target uses a3 too? Let me look at full listing around 150-197.

Let me use --keep to get object path and objdump it (but objdump output goes to .run dir; use run.sh? no). Simpler: I can compile and disassemble via tools. Actually dt.sh prints only diff. Let me run delever_search --try ... --keep and then objdump. But the scratch is under /tmp? --keep keeps per-call scratch, path printed. Let's do that.

Actually, easier: the target disassembly exists in build/ maybe. Let me find. The scoring compares with the function in build/. There may be a reference .s. Let me check what delever_search uses. Read the tool? It's big maybe. Let me grep for "target" / disassembly source.

Actually, better to use `--explain TU FN` which reads one body's residual. Hmm.

Let me look at the full picture differently: The swap is local-alloc qty priority between the tag value (`*(u16 *)(base+0xA3D2)` used twice? Actually appears twice in source: once in `*(u32*)pkt = ... &D_800A6614[oidx + (*(u16*)(base+0xA3D2)<<14)]` and once in `otp = ...`). And oidx used in both index expressions. So both are multi-use.

Target: oidx in $3 (v1), tag in $4 (a0). Mine: tag in $3, oidx in $4.

Wait but the diff at 162 says `lw v1,0(a3)` mine vs `lw a0,0(a3)` target. So in the target, the tag load result is a0. In mine it's v1. And at 166 `lw a0,20(sp)` mine vs `lw v1,20(sp)` target: that's oidx? 20(sp) maybe g.otz? g is on stack. So oidx = otz<<2: load otz from stack, sll, then addu with... Actually 166 lw a0,20(sp) = load g.otz; 170 sll a0,a0,2. Then 172 addu v0,a0,v0 — hmm v0 is D_800A6614 base? So index = otz*4 + D_800A6614? Wait oidx + (tag<<14) computed. Hmm.

Anyway, mine: tag -> $3, oidx -> $4 (a0). Target: oidx -> $3, tag -> $4.

Why? local-alloc qty priority. qty_compare_1 in local-alloc.c:

```c
static int
qty_compare_1 (q1, q2)
     struct qty *q1, *q2;
{
  /* Consider "quantity" of register usage. */
  if (q1->n_refs != q2->n_refs)
    return q1->n_refs - q2->n_refs;
  ...
```

Hmm need to read. Let me grep the source.

Actually, in local-alloc, `qty_sort` sorts qtys by `qty_compare_1` and assigns in that order. Let me read local-alloc.c around qty_compare_1.

Let me find it.
