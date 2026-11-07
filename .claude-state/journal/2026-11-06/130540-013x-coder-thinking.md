---
ts: 2026-11-06T20:05:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AseVp030sEden7TCghgA
---
So in the target loop:
- `sw v0,0(s1)` after call, v0 = call result.
- lhu v1 = table; sh v1,136(v0); sh v1,6(v0) — uses v0 (call result) as base for unk88 and unk6.
- lw v1,0(s1) — reload *p into v1.
- li v0,-1024; sh v0,10(v1) — unkA = -0x400 via v0.
- lw v1,0(s1) — reload *p again.
- lhu v0 = table2; sh v0,140(v1); sh v0,14(v1).
- lw v0,0(s1); addiu s0,s0,1; lw v1,32(v0); lhu v0 = table3; addiu s3,s3,8; sh v0,18(v1) — *(v0+0x20)->unk12.
- lw v1,0(s1); li v0,-146; sh v0,138(v1).

So the target keeps v0 = call result across the first two stores (not reloading from *p). In C: after `*p = v0`, uses `((Unk*)v0)->unk88 = t; ((Unk*)v0)->unk6 = t;`. So the source presumably uses v0 directly rather than reloading `*p`. My body does `((Unkstruct_800B5CB8 *)v0)->unk88 = t;` — yes uses v0. Good.

But then `CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;` loads *p into v1. Then `e = *p;` — loads *p into e; then `v0 = *(u16*)(...)`; uses e for unk8C/unkE. Target: `lw v1,0(s1)` then lhu v0 table2, then sh to 140(v1) and 14(v1) — so e is v1, and the table value in v0. Fine.

Then `v0 = *p;` reload, `i++`, `((Unk*)*(s32*)(v0+0x20))->unk12 = ...` — target: lw v0,0(s1); addiu s0,s0,1; lw v1,32(v0); lhu v0 table3; addiu s3; sh v0,18(v1). Hmm: v0 = *p; then `*(s32*)(v0+0x20)` into v1; then table3 into v0. In source, `((Unk*)*(s32*)(v0+0x20))->unk12 = *(u16*)(&D_8019B92E + off);` — the RHS loads table3. The compiler would compute base from v0+0x20 → v1, then load table3 → v0? Table3 address uses at, so lhu v0,0(at) is fine.

Then `off += 8; CAST_NONSTRUCT(s16,*p,0x8A) = -0x92; p++;` target: lw v1,0(s1) (reload *p), li v0,-146, sh v0,138(v1). And addiu s1,s1,4 in the branch delay. Good.

So target's loop body is very close to source; the pin forced the call result to $2, which is what the target naturally has... but why does the lever-free version score 35? Because without the pin, the call result gets moved to v1? Diff: mine[44:46] `move v1,v0; sw v1,0(s1)` vs target `sw v0,0(s1)`. And mine uses v0 for table load at 48: `lhu v0,0(at)` vs target `lhu v1,0(at)`; then `sh v0,136(v1)` where v1 is the call result... 

So without the pin, the call result went to v1 (via move v1,v0), and v0 is used for the table value. That's a register allocation difference. The pin forced result into $2.

Hmm. So the challenge: lever-free, make the call result land in v0 and the table loads in v1. This is a local-alloc/global-alloc decision.

Approach from moves: "pin | func_801821C8 | MATCH: twin ... copy hoisted via s16 temp (tmp=(s16)t; u=tmp before the if; else t=u-1); HImode copy escapes cse, move v1,v0 stays in the bnez delay slot".

Another: "pin | func_8017EAD8 | MATCH: self var dropped, arg0 used directly..."

The core issue: call result pseudo vs table-value pseudo. In the target, call result = v0; table value = v1. The move `move v1,v0` in mine indicates local-alloc gave the call result to v1 and then... hmm, actually `move v1,v0` right after jal means the call result (in $2=v0) is copied to v1 for the pseudo assigned v1. So local-alloc assigned the result pseudo to v1 (call result copy). Target: the result pseudo stays in v0.

Wait but `*p = v0` — the result pseudo is used as base of stores at 136/6 (unk88/unk6). Since v0 is hard-wired as the call return, a pseudo used right after call would prefer v0 (copy pref). But cse/reg alloc: `v0` var is used in multiple places (call result, then `v0 = *(u16*)` reassigned, then `v0 = *p`). Because it's the same variable with multiple sets, it's not a single pseudo; each set is a separate pseudo, and the live ranges are separate. But the name reuse might not matter.

Hmm, mine has `move v1,v0; sw v1,0(s1)` and then `lhu v0,0(at)` — so the result pseudo got v1, and the table pseudo got v0. Then `sh v0,136(v1)` — wait, if the result is v1 and the table value v0, then sh v0,136(v1) is correct semantically. Target has sh v1,136(v0), i.e., table in v1 and result in v0.

So it's just a swap: which pseudo gets v0. This looks like lreg-qty-priority or local-alloc ordering.

Since the pin forced the result to $2, the crack without a pin needs the allocator to choose v0 for the result. Options:
1. Reduce the table pseudo's priority so it doesn't grab v0. E.g., make the table value an s16/u16 temp? It's already u16.
2. Make the result pseudo's live range/preference stronger: e.g., use the result more times, or split so it's born right at the call.

Actually the result pseudo is the call return; the copy `move v1,v0` arises because the pseudo wants v1. With a copy preference, the result should prefer v0! Unless the result pseudo is also tied to something else.

Hmm wait, maybe it's the opposite: `sw v1,0(s1)` — the store's source is v1. The result pseudo was allocated v1. The copy `move v1,v0` is the call-result copy. Copy preference: the call result copy (hard $2 → pseudo) prefers $2=v0 unless the pseudo has a conflict. Why would it not prefer v0? Because v0 is taken by the table pseudo? But table pseudo is defined after... Actually local-alloc allocates within basic blocks; the whole loop is one basic block. All three v0-valued pseudos compete.

Let's get the dumps to see the actual allocation. Use tools/cc1_dumps_tu.sh. But first, cheaper: try C variants.

Idea A: combine the two stores differently: `((Unk*)v0)->unk88 = t; ((Unk*)v0)->unk6 = t;` — this is what source has. The reload structure: target does `lw v1,0(s1)` before the -0x400 store, then again before table2. That matches source (`CAST_NONSTRUCT(s16,*p,0xA)` reloads *p; then `e = *p` reloads).

Since the source already matches structurally, the only issue is the v0/v1 swap. This is a classic "lreg-qty-priority" or "global-pri-bank-order" wall, but maybe a real-C tweak can flip.

What about making the table value a `s32` or `u32` temp? The target `lhu v1,0(at)` then `sh v1,136(v0)` — if we widen the temp to s32/u32, the compiler would need `lhu` then maybe `sll/sra`? Actually target just lhu and sh (no extension) — u16 is right.

Hmm, what about the order: source loads t = table then stores. Target: lhu v1, then sh. Same.

Alternative: use `v0` variable differently — e.g., don't reuse the same C variable name for the call result and the later loads; use separate temps. That might change cse/reg allocation. Since `v0` is a single C variable with multiple sets, GCC 2.7.2 creates one pseudo per set but they share a variable? No — each assignment creates a new pseudo (register) but the variable is the same. Actually the C variable's value is a single pseudo per live range... in gcc, each set to a VAR_DECL creates a new pseudo and the variable is just a name; the register allocator sees separate pseudos per set. However, `v0 = func(...)` then `*p = v0` then later `v0 = *(u16*)` — these are separate pseudos.

So renaming doesn't change much, but could change scheduling/reg order.

Let me try the simplest variants:
1. Use a separate temp for the call result: `s32 r = func_8012C588(...); *p = r; ((Unk*)r)->unk88 = t; ...`
2. Use `*p` instead of the result variable for the stores (source of the reload).
3. Widen/narrow temps.

Let me first get dumps to understand. Actually let me try a batch of candidates with sc.sh. Let me create variants.

The orig body case 2:

```
        ((void (*)(s32))func_8001AAA0)(0x41);
        i = 0;
        p = D_801AECD8;
        off = 0;
        while (i < 5) {
            v0 = func_8012C588(0x1C5, param_1);
            *p = v0;
            t = *(u16 *)((s32)&D_8019B928 + off);
            ((Unkstruct_800B5CB8 *)v0)->unk88 = t;
            ((Unkstruct_800B5CB8 *)v0)->unk6 = t;
            CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;
            e = *p;
            v0 = *(u16 *)((s32)&D_8019B92C + off);
            ((Unkstruct_800B5CB8 *)e)->unk8C = v0;
            ((Unkstruct_800B5CB8 *)e)->unkE = v0;
            v0 = *p;
            i++;
            ((Unkstruct_800B5CB8 *)*(s32 *)(v0 + 0x20))->unk12 =
                *(u16 *)((s32)&D_8019B92E + off);
            off += 8;
            CAST_NONSTRUCT(s16, *p, 0x8A) = -0x92;
            p++;
        }
```

Let me check the full instruction diff for mine to see all 200 vs 197.

Actually the diff shows mine has extra: move v1,v0 + sw v1 (2 insns vs target 1) = +1; delete mine[66:67] `lw v1,32(v1)` vs target... target at 61-62 has `lw v1,32(v0)` and mine has an extra `lw v1,32(v1)`? Hmm mine 60-66 region. Let me get the full mine disassembly. dt.sh may write it. Let me check what delever_search does and whether there's an easy way to dump the compiled body.

Let me look at delever_search.py usage/options.
