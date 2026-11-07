---
ts: 2026-11-06T12:14:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IlJ8mBPWsg9utExFL0zt
---
--keep prints candidate object path. I could use that to objdump. But simpler: is there a tool to dump target? The item dir in T10 example had `tgt` file. Maybe delever_search leaves scratch with --keep including target listing.

Let me try --keep with a1.c and look at the scratch.

Also, the diff summary shows target's insns only at mismatch points. The key differences:

1. mine: `move t4,a1` / target: `move t3,a1`. Hmm at insn 1. Where does a copy of a1 to t3/t4 come from in my a1.c? I removed a1v... Wait, maybe it's `(s16) arg2` computations? No, insn 1 is at the very top.

Hmm, maybe `move t4,a1` in mine is actually pos? No, pos moved at insn 4: move t3,a2 (mine) vs move t4,a2 (target).

Hold on. Mine insn 1: `move t4,a1`; insn 4: `move t3,a2`. Target insn 1: `move t3,a1`; insn 4: `move t4,a2`.

So both mine and target copy arg1 to a temp at insn1 and arg2 to a temp at insn4, but with t3/t4 swapped. In my source, the only arg2 copy is... hmm I have no explicit copy of arg2 in a1.c! Unless `(s16) arg2` in the branch causes a move? At insn 4 though, before the branch. gcc might copy arg2 into a pseudo because it's used in several places (`(s16) arg2` twice, and arg2+2/arg2-2).

And arg1 copy to temp at insn1? Maybe from `arg1 & 1` in the if test — gcc copies arg1 into a temp? Actually `andi v0,t4,0x1` in mine uses t4, while target `andi a1,a1,0x1` uses a1 directly. So in target, the arg1 copy at insn1 is for a different variable (maybe the one tested at insn2 uses a1). Hmm, target: insn1 move t3,a1; insn2 andi a1,a1,1. So target's move t3,a1 copies arg1 to t3 and then uses arg1 for the test. What is the t3 copy? Maybe it's `a1v` — the launder tied to $5=a1, but the compiler decided the launder output lives in a1? No wait, the pin says a1v is $5 (a1). Hmm.

Wait — $5 in MIPS o32 is a1, and t3 is $11. But the target's `move t3,a1`: source a1 (arg1) → t3. And then the &1 test uses a1. So there are two copies of arg1's value: one in a1 (used for tests) and one in t3.

Maybe in the target, a1v is NOT in $5. Let me reconsider: `register s32 a1v __asm__("$5")` pins a1v to $5=a1. The launder `__asm__("" : "=r"(a1v) : "0"(arg1))` forces a1v in the same reg as arg1. arg1 is a param → a0 ($4). Wait! arg1 is the SECOND parameter. o32: arg0=$4(a0), arg1=$5(a1), arg2=$6(a2). So arg1 is in a1 already. OK so both a1v and arg1 in $5.

Hmm, but the target shows `move t3,a1` — maybe that's pos? No, pos=arg2.

Wait, maybe I mis-assign. Let me get the target disassembly to understand. Use --keep.

Actually the move at insn 1 might be the `-var_v1` or something scheduled early. Let's get the actual listing.

Let me run with --keep and inspect the scratch files.
