---
ts: 2026-11-06T20:06:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_msof1YK2ryOCduuOq6ua
---
There's `--explain TU FN` which reads a body's residual. But it says "read one body's residual (no writes)" — probably for the tree body. Not sure it takes a file. Let me instead use --keep to get the candidate object and disassemble. But that's heavier.

Actually, dt.sh with tail gives diff. That's enough. Let me try variants.

Let me write candidate bodies. I'll create win.c starting from nopin.c and try.

Variant 1: separate temp for call result `s32 r`.

Actually wait — think about why target has v0 for the result. In target, after jal, `sw v0,0(s1)` directly. That's the call-result pseudo assigned v0. Then table value v1.

In mine, result → v1, table → v0. So local-alloc gave the call-result pseudo v1 (with a copy from v0) and the table pseudo v0.

Possibly the table pseudo's qty (ref count / live length) is higher, and local-alloc's priority gives it first pick. Since the table pseudo is used twice (two stores) and the result pseudo is used 3 times (store + 2 stores as base) — hmm.

Wait: the result pseudo is used as base of the two stores unk88/unk6 plus `*p = v0` store. So 3 uses. The table pseudo used twice. Result has more refs. Hmm.

But maybe the result pseudo is born at the call (in the same block) and dies after two stores; the table pseudo born after. local-alloc's `qty_compare` uses floor_log2(refs)*refs/live_length, prioritizing... In GCC 2.7.2 local-alloc, quantities are sorted by `qty_n_refs` primarily? Let me check local-alloc.c in tools/reference.

Actually there's a simpler known lever: `-f` no. Let me look at the source of local-alloc qty_compare.

Actually, let's just try things. Time budget 20-30 min per item, 4 items ~2h.

Candidate ideas for item 1:
(a) hoist table load before the call: `t = table;` then call. No—the target loads after the call.
(b) Use a `s16`/`u16` temp for the table: it is u16.
(c) Use the call result directly without the `v0` var: `*p = func_8012C588(...)` — then store to *p; but we need the result as base later. Could do `p[0] = ...` then `((Unk*)p[0])`? That reloads.
(d) Assign the result to `p` itself? No.
(e) Make the table pseudo die earlier / not conflict: the table value is loaded from a table and used for two stores to the result base. In target, lhu v1 after sw v0. Both live at the same time (v0 and v1). So conflict is unavoidable; the allocator chooses.

Hmm, so why does the lever-free version pick v1 for the result? Maybe because the result pseudo is created from the call and the call's return in $2 must be copied; local-alloc gives $2 preference to the pseudo... but if the table pseudo is allocated v0 first (higher qty), the result gets v1.

qty: table pseudo: 2 refs, live from lhu to second sh (short). result pseudo: 3 refs (sw, base of 2 sh), live from jal to second sh. Both similar. Hmm.

Wait — maybe the real difference: in target, `*p = v0` and the two stores use v0. In mine, `move v1,v0; sw v1,0(s1)` then `sh v0,136(v1); sh v0,6(v1)`. Wait, that means the result pseudo is v1 and the table is v0 in mine. The `move v1,v0` is the call-result copy. But then where's the table load? mine[48] `lhu v0,0(at)`. So yes.

local-alloc allocates pseudos in qty order, giving each the preferred or a free hard reg. $2=v0 is the call-clobbered return; the result pseudo has a preference for v0. The table pseudo (no preference) takes... hmm, local-alloc gives hard regs by `reg_preferred_class`/`reg_alternate_class`. For a pseudo with no preference, the class is GENERAL_REGS and it scans... In local-alloc `block_alloc`, it uses `find_free_reg` with the class; it tries the preferred reg, then... The allocation order: qty sorted by qty_compare, higher qty first. Then `find_free_reg` picks the first free reg of the class in a rotated order (the `reg_alloc_order`? there's a "last_allocno" rotation).

GCC 2.7.2 local-alloc.c: `qty_compare` sorts by `qty_n_refs`... let me actually read it. It's small.
