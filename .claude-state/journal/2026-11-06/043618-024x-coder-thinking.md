---
ts: 2026-11-06T11:36:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q2DJ6P6rLmc162756sAv
---
Differences from target:
1. `andi s1,v0,0xfff` at 3260 vs target `andi a1,v0,0xfff` then `move s1,a1` in the beq delay slot. So target keeps tmp in a1 and copies to s1 later; mine directly computes into s1. That's the $5 pin: pin makes tmp a1 and `sVar3 = tmp` a copy. Real C: `tmp` used only as sVar3; combine folds. To keep the copy: maybe make tmp's lifetime... Actually the target code: `andi a1, v0, 0xfff` then `move s1,a1` in the delay slot of the case compare. So the value stays in a1 (caller-saved) until the switch dispatch, then copied to s1 (callee-saved) — because the case 0x41 arm calls through a function pointer which clobbers a1. So a1 holds it until the switch, and the copy to s1 is placed in the delay slot.

Mine: computes directly into s1 (callee-saved) since the value is live across the switch. That's a global-alloc decision: mine's pseudo got s1; target's got a1 with an explicit copy. This is the `global-copy-pref` / lreg issue.

Hmm. To get target: the value should live in a1 (a caller-saved reg) until the switch dispatch, then be copied to s1. This happens when the value's pseudo is assigned a1 and there's a copy. With the pin $5=a1, `register s32 tmp __asm__("$5")` forces tmp in a1; then sVar3 = tmp is a separate pseudo that got s1, and the copy remained (cse didn't merge because tmp is a hard reg).

Real C without pin: `tmp` and `sVar3` are the same value; the compiler will just keep one pseudo. The copy `move s1,a1` appears because the hard-reg variable's value must be moved out before the call. 

How to get the same without the pin? Maybe: make the value live in a1 through the switch by having it used *after* the switch dispatch. Hmm, but global-alloc chose s1 for mine.

What if sVar3 is computed later (after the switch's case-0x41 arm)? No — it's used in the 0x53 arm only.

Actually, the register allocation: the pseudo is live from 3260 to 3308 (through the switch). global-alloc prefers callee-saved (s1) for a long-lived value. The target has it in a1 (caller-saved) with an explicit copy to s1 at the dispatch. Why? Because the pin forced a1 for tmp, then the copy sVar3=tmp got s1.

Without a pin, can we force a1? Not by C.

Hmm, but wait: maybe there's a real-C structure where the value is computed, then used in the switch dispatch... 

Alternative: maybe use the fact that the target's `move s1,a1` is in the beq delay slot. The value in a1 is used by the switch arms. If we restructure so that the switch is on `bVar1` but the value is passed... 

Honestly, this item may be a wall. But let's think about what levers exist: the kinds are barrier,launder. We must remove barrier and launder. Pins ($5,$3,$2) are NOT in the kinds for this item! The brief says: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." Hmm — it defines lever-free as none of the row kinds remain, but then parenthetically says "no pin (register-asm/__asm__ reg steer), launder, barrier..." That suggests all levers must go regardless of the row kinds. But then results format has PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). So PARTIAL means keeping only some of the row kinds. And the constraint "levers of other kinds the def already had (pins under other causes) may stay, never added" — this says pins of other kinds may stay! So the row kinds for this item are barrier,launder; pins are a different kind and may stay.

Wait but the kinds field is "barrier,launder" while the def has pins. The pins are under other causes, so they may stay. And "levers of other kinds the def already had may stay, never added". So I only need to remove barrier and launder; the pins can stay!

Hmm, but "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm...), launder, barrier, keepalive macro or asm; no new lever of any kind." This sentence contradicts. It says lever-free = none of the row kinds remain, and then lists all lever types. Maybe the list is generic boilerplate: no pin/launder/barrier/keepalive/asm = the set of lever categories. But the constraint line is more specific: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So for this item: kinds = barrier,launder. I must remove the barrier and the launder. Pins may stay.

That changes everything! With pins staying: $5 tmp in a1, $3 bb, $2 c80, $2 hi. Remove only the memory barrier and the launder.

The launder: `__asm__("" : "=r"(tmp) : "0"(tmp));` then `sVar3 = tmp;`. Removing the launder: with tmp pinned to a1, `sVar3 = tmp` still generates a copy (hard reg → pseudo). Does cse merge? The launder exists to prevent cse from coalescing tmp and sVar3. Removing it may still work since tmp is a hard reg; a copy from a hard reg can't be merged. Let's test.

The barrier removal: then cse forwards the second load → one load. That changes insn count. Unless the pins change it. Hmm, the barrier is the harder one.

Let me first try removing only the launder and keep the barrier, and see. Then removing only the barrier keeping the launder. Then both.

Actually the goal is MATCH = both kinds gone (win.c scores 0 with no barrier and no launder, pins may stay).

Let me test:
v2: remove launder, keep barrier.
v3: keep launder, remove barrier.
v4: remove both.

Let me create v2 and v3 quickly.

For the barrier removal, `sVar4 = ratan2(...)` — the second load would be cse'd. Hmm, but with the pin on bb ($3 = v1), the first load is in v1 (hard reg). The second read `*(u16*)(p+0xAE)` — cse would substitute... the memory expression was loaded into a hard reg v1; cse can forward it. So one load. Target has two.

So removing the barrier alone changes code. Unless the pinned bb is used... hmm.

Wait, but maybe the barrier's effect isn't the double load. Let me test to see.

Let me create candidates.
