---
ts: 2026-11-06T11:52:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h45IA0Wf85HRMk7r3q4l
---
So with the bit-field, the reload became `andi v0,v0,0xff` — still folded, but the schedule changed (store after addiu). So the bit-field didn't block the forwarding (maybe combine knows the store value).

Hmm, actually the `andi v0,v0,0xff` at line 13 is the bit-field load being replaced by `v0 & 0xff`? That means the compiler knows the memory at +6 equals v0's low byte. Combine? Or cse still forwarded the store (maybe the store wasn't a bit-field store because f6:8 at byte-aligned offset is a plain QI store, not ZERO_EXTRACT!).

Right: an 8-bit bit-field at a byte-aligned offset is emitted as a plain QI store, not ZERO_EXTRACT. So cse forwards normally.

To get a ZERO_EXTRACT, the bit-field must not be byte-aligned (e.g., `unsigned f6 : 8` starting at bit 4). But then the address/offset differs and the code would shift. Not matching.

Hmm.

OK so this path doesn't work.

Let me think again. The target's lbu: the original code must have prevented cse from forwarding. Since cse forwards plain QI stores, the original must have had a memory-clobbering event between the store and the load, OR the store and load addresses were not provably equal.

Wait — maybe the original used **two different base pointers**: the store via one pointer variable and the load via another, where cse can't prove they're equal because one is a **parameter copy** and the other is the parameter... no, copies are known equal.

What if the load's base is `arg0` and the store's base is a pointer **loaded from the stack** (a spill)? cse would see a memory load as the base, not equal to arg0.

Hmm, but then the asm would differ (extra lw).

What if the store is to `*(u8 *)((u8 *)arg0 + 6)` and the load from `*(u8 *)((u8 *)arg0 + 6)` but with `arg0` being **reassigned** in between to an equal value? E.g., `arg0 = (u8*)arg0 + 0;` — an identity launder. Not allowed.

What if the original had `p[6]` stored and then read via `p[6]` where p is a **volatile-free local copy** that the compiler cannot equate because p is assigned conditionally? No.

Hmm, let me reconsider: maybe the reload isn't cse-able because the store is to a **different address** that happens to alias at runtime but the compiler doesn't know. E.g., store via `*(u8*)((u8*)arg0 + 6)` and load via `*(u8*)((u8*)arg0 + 6)` — same.

What if the original stored through an `s16` write covering bytes 6-7, then read byte 6? The store would be `sh`, not `sb`. Target is sb.

OK, let me look at the actual game: this is likely a "state machine" function. The `lbu v0,6(s0)` after `sb v0,6(s0)` is a classic "read back after write" that the original compiler kept because... hmm.

Actually! Maybe the original code is:
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
and the original compiler DID forward it, but the ORIGINAL source had a different structure and the target's lbu comes from a **different read**. Let me reconsider: maybe the target's `lbu v0,6(s0)` is not a reload but the initial read of p[6] for the NEXT computation? No, it's after the sb.

Wait, maybe the original code is:
```
temp_a0 = p[5];
p[6] = p[6] - temp_a0;    // sb v0
temp_v0 = p[6];           // lbu v0 -- reads the byte just written
temp_v1 = -(temp_v0 & 0xFF);
```
But target computes andi/negu BEFORE sb. Hmm, unless sched1 moved the andi/negu up. Let me check: if the source were `p[6] = p[6]-a; temp_v0 = p[6]; temp_v1 = -(temp_v0 & 0xff);`, then temp_v1 uses the RELOADED byte, and the andi/negu would be after lbu. Target: andi/negu before sb. So no.

What if the original is:
```
temp_v0 = p[6] - temp_a0;
p[6] = (u8)temp_v0;
temp_v0 = p[6];
temp_v1 = -(temp_v0 & 0xFF);
```
then sched1 might hoist the andi/negu above the sb? No, they depend on the reload.

Hmm, target has andi v1,v0,0xff BEFORE sb v0,6. So temp_v1 is computed from the pre-store v0. So the source computes temp_v1 before the store.

OK. Let me try yet another idea: **the store value is not temp_v0 but a truncated copy that cse can't equate**. For instance, if temp_v0 is `s32` and the store is `*(u8*) = temp_v0;` the RTL is (subreg:QI (reg:SI)). cse records it. If instead the store is `*(u8*) = (u8)(temp_v0 >> 0);` combine simplifies.

What if the store value is `(u8)temp_v0` but temp_v0 is **reassigned** right after the store and before the load? Like:
```
*(u8*)(arg0+6) = (u8)temp_v0;
temp_v0 = 0;             // dead? would be optimized
temp_v0 = *(u8*)(arg0+6);
```
The dead assignment is removed. If temp_v0 is used later... no.

What if I use a DIFFERENT variable for the reload:
```
s32 reload;
...
*(u8*)(arg0+6) = (u8)temp_v0;
reload = *(u8*)(arg0+6);
```
cse forwards the stored value into `reload` (still no lbu).

Hmm.

Let me look at whether cse's forwarding is actually defeated by the store being to a MEM with `MEM_IN_STRUCT_P` or a different `in_struct` flag. `note_mem_written` uses MEM_IN_STRUCT_P for alias sets. A store through a `u8*` has MEM_IN_STRUCT_P false (scalar). A load through a struct field has MEM_IN_STRUCT_P true. If the store is scalar and the load is in-struct, cse might still equate by address? The `in_struct` flag affects invalidation (which addresses get invalidated by a store), not the forwarding of the exact same address.

Hmm.

Let me look at the target's cse more carefully: maybe the original's store and load have different addresses at cse time because of the **order of address computation**. In the target, the store is `sb v0,6(s0)` and the load `lbu v0,6(s0)` — same.

Wait, maybe the original used a **function pointer call** in between that's inlined? No.

Let me reconsider the whole thing: maybe the original C for this function is:
```
void func_80175590(void *arg0) {
    u8 a = *(u8*)(arg0+5);
    *(u8*)(arg0+6) = *(u8*)(arg0+6) - a;
    ...
}
```
and the target's lbu is from a second `*(u8*)(arg0+6)` read. The original compiler would forward... unless the store is a compound assignment producing a PLUS in the store, and the reload is separate.

Let me test the compound assignment version:
```
temp_a0 = p[5];
p[6] -= temp_a0;   // or p[6] = p[6] - temp_a0
temp_v0 = p[6];
temp_v1 = -(temp_v0 & 0xFF);
```
But target's andi/negu before sb contradicts.

Hmm, unless combine reorders. Let me just test a few structural variants and look at scores.

Actually — wait. Let me reconsider the target instruction order. Maybe the andi/negu before sb is just sched1 reordering. The dependency: temp_v1 = -(temp_v0 & 0xFF) depends on temp_v0 (the subtraction). If temp_v0 is reloaded AFTER the store, then temp_v1 depends on the reload, so andi/negu must come after lbu. Target has them before sb. So temp_v1 uses the pre-store value. Confirmed.

Unless the reload result is the same as the pre-store value (cse knows), and the compiler scheduled andi/negu before the store because they only need the pre-store v0. In the target (no forwarding), the reload is a real lbu into v0, which would clobber v0. So andi/negu (using v0) must come before the sb/lbu. Exactly the target. So the target's temp_v1 uses the ORIGINAL temp_v0, and the reload writes v0 later. Fine.

So the source is w1's structure. The original compiler didn't forward. Why?

Maybe because in the original, temp_v0 was declared as **`u8`**? Let's think: if temp_v0 is u8:
```
u8 temp_v0;
temp_v0 = *(u8*)(arg0+6) - temp_a0;   // int result truncated to u8
temp_v1 = -(temp_v0 & 0xFF);          // temp_v0 already 0..255
*(u8*)(arg0+6) = temp_v0;
temp_v0 = *(u8*)(arg0+6);
```
The subtraction result assigned to u8 → the compiler stores a QI value. The store value is (reg:QI temp_v0). The load `*(u8*)` → lbu; cse would forward the QI reg → the reload becomes temp_v0 (a QI reg). No lbu, but maybe an andi? Hmm.

But the target's `subu v0,v0,a0` is SImode (32-bit subtract). If temp_v0 were u8, the front-end would still do the subtraction in SImode then truncate. The andi 0xff would appear at the assignment. Target has `subu v0,v0,a0; andi v1,v0,0xff` — the andi is for temp_v1, not temp_v0. And `sb v0,6(s0)` stores the low byte. So temp_v0 is s32. OK.

Let me try: maybe the reload is into a variable of a DIFFERENT type, e.g., `temp_v0 = *(s32 *)((u8 *)arg0 + 6) & 0xFF;` no.

Let me take a completely different approach: check if there's an existing wall/cookbook entry about this exact function or a similar "cse-store-forward" with a real-C crack. walls.txt has `cse-store-forward`: "cse forwards a store into a reload and combine drops the dead store (G18x)". moves.md line 37: "barrier | func_8013F1BC | WALL cse-store-forward — cse1 forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it (W06)". 

So `cse-store-forward` is a known WALL where "only a barrier/volatile stops it". That matches our situation exactly! But our target uses `sb`/`lbu` (QI), and the note says "sh value". Same mechanism.

So item 2 is likely a WALL: `cse-store-forward`. But score 1 means the rest matches perfectly. Still a WALL if unfixable.

But wait — maybe the original used a **compound assignment** `*p -= 16` which produced a PLUS in the store, and cse still forwarded. In our case, maybe there's a real-C crack.

Let me think about `do{}while(0)` again: C0535 says it splits cse1's EBB. If the store is in one EBB and the load in another, cse won't forward across the block boundary. My w2/w3 tried do-while around the store or load separately, but maybe I need the do-while to actually create a block boundary. Let me check the cse dump for w2 to see if the EBB split happened.

Hmm, "cse1's EBB" — cse processes extended basic blocks; a do-while(0) creates a NOTE_INSN_LOOP_BEG? Actually a do-while creates a loop note. cse's EBB ends at a loop boundary? The cookbook says it splits cse1's EBB. Let me look at the cse dump of w2 to see.

Actually, maybe the do-while needs to be around the STORE such that the loop note lands between the store and the load. In w2 I wrapped the store in do-while; the loop note would be around the store, so the load after it might still be in the same EBB? Let me check the cse dump.

Let me dump w2's cse and look for the forwarding.

Actually, quicker: let me try wrapping the reload in do-while AND the store, in different combinations, and also try `if (1) {}` etc. Let me look at C0535's second use: "do { t = D[a1*5]; sp10[4] = t; } while (0);" — the do-while contains the load and the store together. The block split kept the FOLLOWING u16 adds out of the load-delay slot.

Let me look at the cse dump for w2 (do-while around the store) to see if insn 33 (the forward) still appears.

Let me run hdump for w2.

Hmm, this is taking a while. Time check: item 2 started 04:47. Now maybe 04:55. Budget 20-30 min. Let me keep going but be efficient.

Let me test a batch of do-while placements:
- around store only (w2, score 1)
- around load only (w3, score 1)
- around both together (w6, score 1)
- around store, with the load inside the same do-while after the store (same as w6)
- around the two statements temp_v1/store? 

Hmm.

Another idea: cse's EBB is split by a **label**. A `goto` label between the store and load would split the block! Real C:
```
*(u8*)(arg0+6) = (u8)temp_v0;
goto L;
L:
temp_v0 = *(u8*)(arg0+6);
```
A goto to the next statement — the compiler might remove the label if unused... but a label is a block boundary in RTL. Would it split cse's EBB? An EBB ends at a label only if the label is a branch target. Here it is (the goto). But the goto itself is removed (jump to next insn), though the label might remain.

Hmm, but a goto creates a CODE_LABEL which breaks the EBB for cse. Let me test! This is real C control flow (like the goto loops used in moves). It's not a lever.

Actually, `goto` might be considered a "loop shape" move, which is allowed ("loop shape"). Let me try.

Similarly, a `do { store; } while (0);` might not create a label, but a real `do { store; } while (cond)` with a variable cond would.

Let me try the goto-label approach: put a label between the store and the load.

```
    *(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
    goto L1;
L1:
    temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
The compiler will see the label is a jump target (from the goto), so cse won't merge across it. And sched1 works within EBBs, so the load stays after.

Let me test this. Also try `if (temp_a0) { ... }` no.

Let me write w8.
