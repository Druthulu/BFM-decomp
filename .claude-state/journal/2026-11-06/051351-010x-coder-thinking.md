---
ts: 2026-11-06T12:13:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jhw5ufk3AE6dpfoaDZwU
---
OK. Now for my items. Item 1: func_80136824 in ov_SC04_011. It's a function with barrier, keepalive, launder. I need to remove the asm launder and pins and barriers.

Let me copy orig.c first (the bare definition from src lines 1075-1156). Then attempt a de-levered body.

Key: `register s32 pos __asm__("$12")` — pin. `register s32 a1v __asm__("$5")` — pin. `__asm__ ("" : "=r"(a1v) : "0"(arg1))` — launder. `__asm__ __volatile__("")` — barriers, keepalive.

Lever-free means removing those. The challenge is making gcc 2.7.2 allocate identically without them.

Let me create orig.c and a first candidate: strip the asm and see the score/diff.

First check whether there's a build dir with the function; delever_search compares with the function in build/. Fine.

Let's write orig.c by extracting lines 1075-1156 exactly. Use sed to write to file (that's a file creation under .run; fine). But rules: Read files with Read tool or ranged sed; using sed to extract to a file is fine.

Actually the brief says start from the current def in src (copy to <dir>/orig.c). Let me do that with sed -n '1075,1156p'.

Then a nopin.c variant with the asm lines removed, adjust code accordingly.

Let me think about what the original lever body did:
- pin pos to $12 (t4?) wait $12 = t4. pin a1v to $5 = a1.
- launder a1v from arg1 forces a1v in a reg? `__asm__ ("" : "=r"(a1v) : "0"(arg1));` — ties output to same reg as input arg1, so a1v gets arg1's register... Actually it's a copy with register constraint "0", meaning same register as arg1. This is a "launder" to force a move.
- pos = arg2 (after launder), so pos holds arg2 but pinned to $12.
- barriers in the if branches prevent instruction motion (scheduling).
- keepalive pos at the end.

To remove these, need real C that yields the same scheduling. That's the hard part.

Let me first see the score of the stripped body to know how far off.

Plan for item 1 candidate a1.c: remove register/asm declarations, replace a1v with arg1 (or a temp `s32 a1v = arg1;`), pos = arg2 (a temp `s32 pos = arg2;`). Remove barriers/keepalive.

Actually careful: `if (!(a1v & 1))` — with a1v laundered from arg1. If we just use arg1, then arg1 is used directly. The launder was presumably needed because arg1 is used later too (`if (arg1 & 0x8000)`, `if (arg1 & 1)`) and they wanted a copy. With a1v as a normal local `s32 a1v = arg1;` gcc may coalesce it into arg1's reg anyway. But it can't — arg1 is a parameter in $a0 and a1v needs to be separate if both live? If a1v = arg1 and arg1 not modified, coalescing is likely (same value). The launder forced a register with the same reg constraint, so it also coalesced? "=r" with "0" input means a1v shares arg1's register, but the asm breaks the copy propagation so gcc treats a1v as a distinct value from arg1 (with a move emitted or not — since same reg, no move). Hmm, actually it's a value barrier: a1v = identity(arg1) but gcc can't see through; both are in $5 (a1) and live simultaneously? If same register, they can't be simultaneously live with different values... but they're the same value. The asm says output in same reg as input, so no move needed; gcc then treats a1v as living in arg1's register after that point. Effectively a1v IS arg1's register, but the compiler thinks a1v is a fresh value, so uses of arg1 later reload? No, arg1 is still live in its own reg = $5. So a1v and arg1 in same reg. That's fine.

So the launder's purpose was to pin a1v into $5 (via the pin decl) while forcing a use/move so it's a separate pseudo. Actually the pin decl already pins a1v. The launder is needed to assign a1v = arg1 without a move? Without the launder, `a1v = arg1;` with a1v pinned to $5 would emit a move $5,$4, and maybe gcc eliminates it? Since pinned regs are hard regs; a copy to hard reg emits a move.

Hmm. So de-levering means we need gcc to naturally put things in $12/$5.

Let me just start: create orig.c, nopin.c with asm removed and a1v replaced by arg1, pos replaced by arg2 where used... but pos is assigned arg2 and used at pos+2/pos-2. Let's keep local `s32 pos = arg2;` — that's the natural code.

Let me generate and score.

First, time tracking: start time 05:13. Item 1 start.

Let me write orig.c.
