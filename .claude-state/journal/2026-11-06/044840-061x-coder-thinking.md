---
ts: 2026-11-06T11:48:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6ST5PIWZ5Wiuh67q1Y2O
---
So mine replaced the reload `lbu v0,6(s0)` with `andi v0,v0,0xff` — i.e., cse forwarded the stored value (v0) and the (u8) reload became just a zero-extend of the existing v0 (which is already 0..255? no, v0 = temp_v0 which is s32). Actually cse forwarded `sb v0,6(s0)` → the reload gets the stored value v0, then `(u8)` cast → andi 0xff. So the instruction count is the same (37) but the reload is gone.

This is exactly the `cse-store-forward` wall (from walls.txt: "cse forwards a store into a reload"). The barrier prevented it.

But score 1 — so close! Can I make the compiler not forward without a barrier? 

The store is `*(u8*)(arg0+6) = (u8)temp_v0;` then `temp_v0 = *(u8*)(arg0+6);`. cse knows the stored value and forwards it.

Real-C ways to prevent forwarding:
- Make the store value and the reload appear to alias differently. E.g., store via a different pointer type or an intervening call.
- Use a `do{}while(0)` block split? C0535 splits cse1's EBB. If the store and reload are in different EBBs, cse won't forward! That's promising. Let me try wrapping the store in a do-while, or the reload.

Actually C0535: "do{}while(0) around two copies splits cse1's EBB". If I wrap the store `*(u8*)((u8*)arg0+6) = (u8)temp_v0;` in `do{}while(0)`, the EBB might split so cse doesn't forward.

But careful: a do-while might also change the schedule (the target has a specific order). Let me try.

Also note the target has a `nop` after `lbu v0,6(s0)` (line 6-7: lbu a0,5; lbu v0,6; nop; subu). Wait line 6 `nop`? Let me look: target lines:
```
1 addiu sp,sp,-24
2 sw s0,16(sp)
3 move s0,a0
4 sw ra,20(sp)
5 lbu a0,5(s0)
6 lbu v0,6(s0)
7 nop
8 subu v0,v0,a0
```
The nop at 7 is a load-delay slot? Actually lbu has a delay slot on MIPS R3000? MIPS I has load delay slots, so `lbu v0,6(s0); nop; subu` — yes the nop fills the load delay. Mine also has it presumably (diff only showed line 12).

So only line 12 differs. Let me try the do-while split around the store/reload.

Option A: `do { *(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0; } while (0);` then `temp_v0 = *(u8 *)((u8 *)arg0 + 6);`
Option B: wrap the reload in do-while.
Option C: wrap both.

Let me test A/B/C. Also consider: maybe use a separate variable for the store value to break cse equivalence:
```
u8 tmpb = (u8)temp_v0;
*(u8*)((u8*)arg0+6) = tmpb;
temp_v0 = *(u8*)((u8*)arg0+6);
```
cse might still forward tmpb. Hmm.

Another: store then read through a different expression that cse can't equate, e.g. `*(u8 *)((u8 *)arg0 + 6)` vs `*((u8 *)arg0 + 6)` — same.

The do-while EBB split is the cleanest.

Let me write w2 with do-while around the store.

Careful about the exact target order: after `sb v0,6(s0)` comes `lbu v0,6(s0)`. So the store then reload. If the do-while creates a block boundary, sched1 might reorder... let's see.

Let me test a few.
