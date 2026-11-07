---
ts: 2026-11-06T14:11:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z18UpnH06zsR6vJi7HqE
---
The includes are "common.h" and "../shared/engine_prelude.h". The cpp invocation in cc1_dumps_tu uses `-Iinclude -I$(dirname $tc) -Isrc/shared -Isrc`. So `common.h` found in include/. `../shared/engine_prelude.h` relative to dirname(tc) — if tc is in my shard dir, `../shared/` doesn't exist. But `-Isrc/shared` doesn't help for a path that starts with `../shared/`. Hmm.

But hdump.sh solves a similar problem by replacing the include with inline body. That's for header items.

Alternative: I can copy the TU to `src/` ... no, can't write to src.

Alternative: create a scratch dir at .run/P40/T11/O02x/_tu/ov_SC01_084/ and put the TU there, plus a `../shared/engine_prelude.h` — i.e., create .run/P40/T11/O02x/_tu/shared/engine_prelude.h as a copy. Then dirname(tc) = _tu/ov_SC01_084, and ../shared/engine_prelude.h = _tu/shared/engine_prelude.h. And common.h from -Iinclude. That works!

Let me do that for dumping candidates. I'll copy the TU and edit the function in the copy to test variants, then dump.

Actually — do I even need the c1 ref numbers? I know target: i=14, dst=11. I want to find a real-C change that makes i's priority > dst's. Let me think about the formula with actual numbers.

Let me get exact birth/death/life for reg 160 and 162 from the lreg dump. The register table doesn't show birth/death, but local-alloc's qty is computed from the pseudo's live range. I can compute from the RTL: reg 160 first def at insn 307, last use at 406. Reg 162 first def at 318, last use at 394.

But qty_birth/death are in terms of insn UIDs, not counts? Actually in local-alloc, `qty_birth[q]` and `qty_death[q]` are insn uids (from `regno_dead` / the live range). The formula divides by (death - birth) which is a uid span, not instruction count. Let me look at how qty_birth is set.

Actually let me just compute empirically: I'll dump c1 and read the "Register N used M times" plus maybe the alloc results. The priority is computed but not printed. Hmm.

Better approach: brute force. Generate many real-C variants, score each with sc.sh, keep the ones that score 0. The search space: I want i to get a lower-numbered register than dst.

Let me brainstorm real-C variants that add refs to i or remove refs from dst:

Variant 1: `dst = src + n;` -> `dst = &src[n];` — same RTL probably.

Variant 2: combine the increments: `dst++, i++, src++;` vs `src++, dst++, i++;` order. Doesn't change refs.

Variant 3: Use `i` in the condition differently: `while (i < n)` at the top of a while loop (instead of do-while). Loop shape change — might alter the CFG/code. Target has do-while with `blez n` guard and `bne` back edge. If I use `while (i < n)`, gcc might produce the same or different.

Variant 4: Declare `i` before `src` etc. Decl order changes pseudo numbers and thus tie-breaks (qty number). Since ties are broken by qty number ("sort by qty number"), and qty numbers follow pseudo reg numbers which follow declaration order! So changing declaration order could flip which gets allocated first when priorities tie. This is a classic move: "decl order".

Wait: the tie-break is qty number (lower first?). Let me read the rest of qty_compare_1.
