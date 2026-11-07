---
ts: 2026-11-06T11:44:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZFu1dEAHazdr5g6e96hv
---
Target disassembly (33 insns):
0 move a1,a0         <- a1 = a0v + zr
1 lh v0,208(a1)      <- first load of 0xD0 (a1+0xD0=208)
2 lui a2,0x0         <- a2 = D_80126948
3 addiu a2,a2,0
4 move v1,v0         <- v0 = load; v1 = copy of load (v0 = *(a1+0xD0)+8? no)
5 slti v0,v0,40      <- compare load < 0x28
6 beqz v0,7530       <- if not <0x28 goto else
7 addiu sp,sp,-16    <- delay slot: frame alloc (frame_pad)
8 j 7560
9 addiu v0,v1,8      <- delay: v0 = v1+8 (v1 = load) => v0 = load+8
10 lhu v0,206(a1)    <- else: v0 = *(u16*)(a1+0xCE)
11 lh a0,208(a1)     <- d0 = *(s16*)(a1+0xD0)  [re-load!]
12 addiu v0,v0,2     <- v0 = 0xCE + 2
13 move v1,v0        <- v1 = v0 (cpy? no) hmm
14 sh v1,206(a1)     <- *(a1+0xCE) = v1
15 sh v1,204(a1)     <- *(a1+0xCC) = v1
16 move v1,a0        <- v1 = d0 (cpy = d0 + zr)
17 sll v0,v0,0x10    <- v0 = (s16)v0 sign extend? 
18 sra v0,v0,0x10
19 slt a0,a0,v0      <- a0 = (d0 < v1_signed)?  Wait v1 here is... hmm
20 beqz a0,7564      <- if !(d0 < v0) goto skip
21 addiu v0,v1,2     <- delay: v0 = cpy + 2
22 sh v0,208(a1)     <- *(a1+0xD0) = v0
23 lhu v1,56(a2)     <- result path: v1 = a2->unk38
24 lw v0,220(a1)     <- v0 = *(a1+0xDC)
25 nop
26 subu v0,v0,v1
27 bgtz v0,7580
28 nop
29 move v0,zero
30 addiu sp,sp,16
31 jr ra
32 nop

OK so the target is quite specific. The key opaque copies:
- insn 0: `move a1,a0` (a1 = a0v + zr)
- insn 4: `move v1,v0` — v1 = v0 (the first load copied to v1 so v0 can be used for the compare). This is because v0 is used for both the load and the slti; v1 holds the load value. This is `v0 = *(a1+0xD0); v1 = v0;` — hmm, in source the first arm is `v0 = *(a1+0xD0) + 8;`. But the load happens once at insn 1 into v0, then copied to v1 (insn 4), then slti on v0 (insn 5), then v0 = v1+8 (insn 9). So the compiler kept the load in v0 and copied to v1 for the add. That's a natural copy (not the opaque one).
- insn 11: `lh a0,208(a1)` — the re-load of 0xD0 into a0 (d0). The barrier forced this re-load.
- insn 13: `move v1,v0` — v1 = v0 (0xCE+2)? Then sh v1 twice. Hmm, v0 = lhu 206 + 2; v1 = v0; sh v1,206; sh v1,204. That's `v1 = *(a1+0xCE) + 2; *(a1+0xCE)=v1; *(a1+0xCC)=v1;`. But target has `move v1,v0` then sh v1 — so v1 and v0 both hold the value. Actually the source has `v1 = *(s16*)(a1+0xCE) + 2;` and stores v1. The compiler computed into v0 then moved to v1? That's a copy.
- insn 16: `move v1,a0` — cpy = d0 + zr (cpy in v1, d0 in a0).
- insn 19: `slt a0,a0,v0` — compares d0 (a0) with v0 (sign-extended v1). Wait, but insn 21 uses v1 for `addiu v0,v1,2` (cpy+2). But insn 13 also set v1 = v0. Then insn 16 overwrites v1 = a0 (cpy). So v1 is reused. Hmm, confusing but that's the allocation.

The critical opaque copies are insn 0 (`move a1,a0`) and insn 16 (`move v1,a0`). Without them:
- a1 coalesces to a0 → insn 0 gone, and all `(a1)` become `(a0)`.
- cpy coalesces to d0 → insn 16 gone, and `addiu v0,v1,2` becomes `addiu v0,a0,2` maybe.

Mine had 31 ins (2 fewer), consistent with losing these 2 moves.

So I need real C to force:
(a) a1 to be a separate pseudo from a0v (keep `move a1,a0`).
(b) cpy to be a separate pseudo from d0 (keep `move v1,a0`).
(c) the re-load of 0xD0 (d0) to survive cse (the barrier did this).

For (c): the barrier forced a second `lh a0,208(a1)`. Without it, cse folds d0 into the first load (v0/v1). Real C to force a re-read: make the first load not cse-equivalent. E.g., first load via a different expression/type. Hmm.

For (a): a1 = a0v copy. Real C trick? 

This looks like a genuine opaque-copy WALL. The G07 WALLs (func_80181E64 etc.) were for exactly this. But some got MATCHed later with HImode tricks. Let me check if func_80181E64's MATCH applies here. It was `s16 v and the store reads v: the HImode copy t = v escapes cse`. That's for an s16 value copy. Here a1 is a pointer.

Hmm. Let me think about (a) differently. The target's a1 is a copy of a0. What if the source parameter is used to initialize a local pointer of a different type, and the code uses that pointer? E.g.:
```
u8 *a1 = (u8 *)a0v;
```
Then a1 is a pointer pseudo. Would it coalesce with a0v? a0v is s32, a1 is u8*. They're different modes (SImode vs PSImode? On MIPS, pointers are SImode). Both SImode, so coalescing possible. Hmm.

What if a1 is declared `volatile u8 *`? No, changes accesses.

What about using an array index that forces a new pseudo? 

Actually — maybe the trick is to make a0v used for something else so its live range conflicts with a1. E.g., if a0v is used AFTER a1 is defined. In the target, a0v (a0) is dead after insn 0 (only a1 used). If I add a use of a0v later that's legitimately part of the computation... but the computation uses a1. There's no natural use of a0v.

Alternatively, make a1 a HImode-derived pointer? Like `s16 h = (s16)a0v; a1 = h;` — truncates.

Hmm, what about `a1 = (s32)(u16)a0v;`? Truncates.

This is the classic opaque-copy wall. Let me check the moves.md WALL entries for the exact tag and see if there's a known crack for s32 pointer copies.

grep moves.md for "opaque" showed:
- func_80181E64 WALL cse-opaque-copy — then MATCHed (s16 v)
- func_800D0D7C WALL cse-opaque-copy
- func_8003DF8C WALL cse-opaque-copy — then MATCHed (u16 i/j)

So the cracks used HImode values. For a pointer (SImode), maybe a `u16` index trick?

Let me look at the actual function more. `a1 = a0v + zr` — a1 is used as a byte pointer (a1 + 0xD0 etc.). The comment says the copy keeps a1 in $a0. Actually wait: target insn 0 `move a1,a0`, so a1 gets $a1, a0v is $a0. So a1 is in $a1, a0v in $a0. Without the copy, a1 coalesces to $a0.

Hmm, what if I write the parameter as a pointer type at the definition? The signature is `s32 func_80182334(s32 a0v)`. I can't change it. But inside, I could do `s32 a1 = a0v;`.

Let me try the HImode trick: maybe if a1 is loaded via a u16 intermediate that doesn't truncate because... no.

Let me reconsider: is there a real-C way to make gcc not coalesce a copy? Yes: if the source and dest have overlapping live ranges and different uses. Or if the copy is "opaque" due to a mode change. A mode change from SImode to a narrower mode and back (sign/zero extend) would create a separate pseudo. E.g.:
```
a1 = (s32)(u16)(a0v & 0xFFFF) ... 
```
no, truncates.

But the address a0v is in RAM (0x80xxxxxx). Truncating to u16 loses it.

Hmm.

Actually — wait. What if the copy is via a union or a struct field? `((s32*)&a1)[0] = a0v;`? That might force a memory store. No.

What about `a1 = a0v; a1 = a1;`? identity launder, not allowed and gets deleted.

Let me look at whether the `cpy = d0 + zr` can be cracked with a real-C move. `cpy = d0;` coalesces. To keep cpy separate: use d0 in another way. E.g., `cpy = d0; v0 = cpy + 2;` where d0 is also used in the comparison `v1 <= d0`. So d0 is used twice (in slt and in cpy). If cpy = d0 and cpy used in addiu, and d0 used in slt, then they could share a register (no conflict). The opaque copy forced a separate reg because the target needs `addiu v0,v1,2` (cpy in v1) and `slt a0,a0,v0` (d0 in a0). 

Real C: if I compute `cpy = d0 + 0`? identity. `cpy = d0 & 0xFFFFFFFF`? identity-ish (but maybe not folded? gcc might keep it). Hmm, `& 0xFFFFFFFF` on s32 is identity and folds.

What about making cpy s16? d0 is s16 (loaded via `lh` into s32). `cpy = d0;` with cpy s16... then `cpy + 2`. The s16 width might create a sign-extend and separate pseudo (HImode trick!). Let me try: declare `s16 cpy;` instead of s32. Then `cpy = d0;` is an HImode copy → escapes cse → separate reg. And `v0 = cpy + 2;` → sign-extend then add.

Similarly for a1: a1 is a pointer, can't be s16.

But maybe (a) can be handled by declaring a1 differently. Let me think about the `move a1,a0` — what if the parameter is used through a pointer cast and the local is a `u8 *`? Let me just experiment.

Let me try variants:
1. cpy as s16 (HImode trick).
2. a1 as u8* (`u8 *a1 = (u8 *)a0v;`) and adjust accesses to use a1 (a1 + 0xD0 already works on u8*).
   Actually currently a1 is s32 and accesses are `*(s16 *)(a1 + 0xD0)`. If a1 is u8*, `*(s16 *)(a1 + 0xD0)` still works (a1 + 0xD0 is u8* + int). Good.
3. Force the re-load (c) by making the first load through a different path.

Let me first check the target: insn 1 `lh v0,208(a1)` is the first load of 0xD0, used for the `< 0x28` compare and the +8. Then insn 11 `lh a0,208(a1)` re-loads 0xD0 into a0 (d0). So two separate loads of the same address. Without the barrier, cse would reuse. To force a re-load in real C, I could:
- Make the first access a different type so cse doesn't equate: e.g., first read via `*(u16*)(a1+0xD0)` (lhu) — but target first load is `lh` (s16). Hmm.
- Use a `volatile` read for the second: `d0 = *(volatile s16*)(a1+0xD0);` — volatile forces a re-read (and is real C, not a barrier/pin). But volatile might add different codegen? A volatile lh is still `lh`. Actually volatile prevents cse and reordering. But it might also prevent other optimizations. The comment said "without volatile's lhu+sll/sra cost" — implying volatile made it lhu+sll/sra. Hmm, because a volatile s16 read might be done as a volatile word? No. Let me just try `volatile` on the second load.

Actually the comment: "the zero-byte "memory" clobber invalidates it without volatile's lhu+sll/sra cost." So using volatile instead of the memory clobber would produce lhu+sll/sra (worse). So volatile isn't the answer.

Hmm. Let me think: what real C makes the compiler NOT fold two loads of the same address? A store in between to a possibly-aliasing location. There IS a store: `*(s16 *)(a1+0xCE) = v1; *(s16*)(a1+0xCC) = v1;` but those come AFTER d0's load (insn 11 is before the stores at 14-15). Wait order: insn 10 lhu 0xCE, insn 11 lh 0xD0 (d0), insn 12 addiu, insn 13 move v1, insn 14 sh 0xCE, insn 15 sh 0xCC, insn 16 move v1,a0, ... So d0 load is BEFORE the stores. The first load (insn 1) is at the top. Between insn 1 and insn 11, is there a store? No stores, only reads. So cse folds.

To force the re-load, I need a store to a possibly-aliasing address between the two loads, or make the loads not cse-equivalent. 

Real C: the source reads `*(s16*)(a1+0xD0)` at the top (for the compare) and `d0 = *(s16*)(a1+0xD0)` in the else. If I make the top read use a `u16` type and the else use `s16`? The target top load is `lh` (s16) and d0 load is `lh` (s16). Same type.

Hmm, but what if the top read is through a struct member and the else through a pointer? get_inner_reference vs pointer deref might create different memory refs that cse doesn't equate? Possibly. But risky.

Actually — the simplest real-C to force a reload: put the first read's result in a variable that's "used up", and re-read. cse tracks memory. A store to `*(s16*)(a1+0xCE)` between the reads would invalidate. But in the target, the 0xCE store is AFTER d0's load. What if I reorder the source so the 0xCE store happens before the d0 read? Then the store would invalidate the 0xD0 cse entry (0xCE and 0xD0 differ by 2, but the compiler can't prove non-aliasing for s16 stores at different offsets? It might). Actually the target has: v1 = load 0xCE + 2; d0 = load 0xD0; store 0xCE; store 0xCC; ... So the source order is load 0xCE, load 0xD0, store 0xCE. If I reorder to: store 0xCE; store 0xCC; then load 0xD0 → the stores would invalidate the top load's cse entry (if the compiler can't prove 0xCC/0xCE don't alias 0xD0). Then d0 would be a fresh load! And the target's order has the stores after the load, but maybe reordering is a "statement order" move (allowed, real C).

Wait, but the target's insn order is load 0xD0 (11) before stores (14,15). If I move the stores before the d0 load in source, the generated order might differ. Hmm, but the scheduler could reorder. Let me just try.

Actually, the target order in source is likely:
```
v1 = *(s16*)(a1+0xCE) + 2;
d0 = *(s16*)(a1+0xD0);
cpy = d0 + zr;
*(s16*)(a1+0xCE) = v1;
*(s16*)(a1+0xCC) = v1;
if (v1 <= d0) goto skip;
v0 = cpy + 2;
```
If I reorder to:
```
v1 = *(s16*)(a1+0xCE) + 2;
*(s16*)(a1+0xCE) = v1;
*(s16*)(a1+0xCC) = v1;
d0 = *(s16*)(a1+0xD0);
cpy = d0;
...
```
Then the d0 load after the stores. But does cse still fold it to the top load? The top load is `*(s16*)(a1+0xD0)` and the stores are to 0xCE/0xCC. If cse's true_dependence says they don't alias, it still folds. Hmm.

Let me reconsider the actual barrier comment: "the else-arm re-load of 0xD0 is a genuine second `lh`: cse's memory table reaches into the not-taken arm, so a plain re-read there is folded onto the entry load — the zero-byte `"memory"` clobber invalidates it without volatile's lhu+sll/sra cost."

So cse folds the re-read onto the entry load. The memory clobber invalidates the whole cse memory table.

Real C: make the entry load and the re-read have different memory attributes. E.g., the entry load is through `*(s16*)(a1+0xD0)` and the re-read through a struct field. If they're different RTX forms, cse might not equate. But cse equates based on address + mode. Same address, same mode → equal.

What if the entry load is `s16` and the re-read is via `s16` but the entry load is at a different offset expression that folds to the same? Same.

Hmm. What if I use a union: the entry load reads the union member as s16, the re-read as a different member? Same mode/address.

This is looking like a genuine wall. Let me check the G07 entries and whether any pointer-copy function was cracked. Let me grep moves.md for "func_80182334" (nothing) and for "cse-opaque-copy" MATCHes.

Actually, let me just try a batch of variants quickly:
- v_cpy_s16: cpy as s16.
- v_a1_ptr: a1 as u8*.
- v_both.
- v_reload: reorder stores before d0 load.
- v_volatile: d0 load volatile.
- v_combos.

Let me generate and score. Time budget: I've spent ~? Let me check the time. Started 04:32. It's probably ~05:00 now. Item 2 budget 20-30 min. Let me be efficient.

Let me write gen.py for item 2 with several variants.

Variants based on nopin.c:
1. v_cpy16: `s32 cpy;` → `s16 cpy;`
2. v_a1ptr: `s32 a1;` → `u8 *a1;` and `a1 = a0v;` → `a1 = (u8 *)a0v;`
3. v_a1ptr_cpy16: both
4. v_reload: reorder stores before d0
5. v_vol: `d0 = *(volatile s16 *)(a1 + 0xD0);`
6. v_cpy16_vol
7. v_a1ptr_cpy16_reload

Let me write the generator.

For v_a1ptr, the accesses `*(s16 *)(a1 + 0xD0)` with a1 u8* — fine. `*(s32 *)(a1 + 0xDC)` fine. `(Unkstruct_80126948 *)a2` unaffected.

For v_reload, I need to rewrite the else block:
```
    } else {
        v1 = *(s16 *)(a1 + 0xCE) + 2;
        d0 = *(s16 *)(a1 + 0xD0);
        cpy = d0;
        *(s16 *)(a1 + 0xCE) = v1;
        *(s16 *)(a1 + 0xCC) = v1;
        if (v1 <= d0) {
            goto skip;
        }
        v0 = cpy + 2;
    }
```
to:
```
    } else {
        v1 = *(s16 *)(a1 + 0xCE) + 2;
        *(s16 *)(a1 + 0xCE) = v1;
        *(s16 *)(a1 + 0xCC) = v1;
        d0 = *(s16 *)(a1 + 0xD0);
        cpy = d0;
        if (v1 <= d0) {
            goto skip;
        }
        v0 = cpy + 2;
    }
```

Let me write gen.py.
