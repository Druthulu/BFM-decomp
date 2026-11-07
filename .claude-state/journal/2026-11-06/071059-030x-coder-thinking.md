---
ts: 2026-11-06T14:10:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5exptYJQ93bpuUpg2sLf
---
Priority = floor_log2(n_refs) * n_refs * size / (death - birth).

For i (n_refs=14, size=1 word? qty_size = number of regs = 1 for SI): floor_log2(14)=3, 3*14=42, /life. For dst (n_refs=11): floor_log2(11)=3, 3*11=33 /life.

Without keepalive: i=11, dst=11. Then it's life that decides (or qty number tiebreak). i's birth (insn 307) to death (406) spans ~100 insns; dst's birth (318) to death (394) spans ~76. So dst has shorter life -> higher priority -> gets t2 (first). That matches: mine gives dst t2, i t3.

Target with keepalive: i n_refs=14 -> 42/life_i vs dst 33/life_dst. Even with i's longer life, i wins. Indeed 42/100 vs 33/76 = 0.42 vs 0.434 -> dst would still win if life is (death-birth)! Hmm, so maybe qty_death/birth are in insn counts differently, or refs differ. Let me not over-analyze; empirically the keepalive flips it.

So I need to raise i's refs by 1 or 2 using real C, or shorten i's life, or lower dst's refs.

Now: how to add a real reference to i without changing the generated code?

Idea: The `i < n` comparison. What if I use i in a way that produces the same slt? E.g., write the loop as `for (i = 0; i < n; i++)` with the increment in the for-header. That's still 1 ref for i++ and 1 for i<n, plus the init. No change.

Idea: use `i` for the store index instead of a separate dst pointer... no, that changes addressing.

Idea: Make `n` and `i` interplay: e.g., `if (i < n)` inside... no.

Hmm. Alternative: lower dst's ref count. Currently dst appears in: `dst = src + n` (1 def), `*dst = out` (1 use), `dst++` (1 use + 1 def). In REG_N_REFS terms, how are refs counted? Each REG occurrence in an insn counts? Let me check flow.c or local-alloc's reg_n_refs computation. In local-alloc.c line 297: `qty_n_refs[qty] = reg_n_refs[regno]`. reg_n_refs is set in flow.c? Let me grep.

Actually in gcc 2.7.2, reg_n_refs is computed in `flow_analysis` (flow.c) or in local-alloc. Let me grep reg_n_refs assignment.

But more practically: the reg table says dst (162) used 11 times, i (160) 14 times. Let me compute without keepalives by dumping the c1 (asm-removed) version and reading its register table. That tells me exact refs.

Let me dump c1. But first, is there a cheaper way? Let me just dump the c1 candidate with --keep and cc1. Actually cc1_dumps_tu requires a TU file. --try --keep prints the candidate object path but not the TU. Hmm.

Alternative: temporarily create a modified TU? Not allowed to write src. I can copy the TU into my item dir and edit the copy. The TU is a file under src; copying to .run is fine. But cc1_dumps_tu on a copied TU needs include paths; the script handles -Isrc/shared and dirname. Since the TU includes "../shared/..." it needs its directory to be one level under src? The comment says: "a TU's #include "../shared/..." resolves from any directory one level under src/, and a copied TU's own directory is not one (every scratch copy failed CPP-EMPTY)." So copying to .run breaks includes. hdump.sh handles headers by inlining. For TU dumps they use the real TU.

Hmm. Maybe there's a way: use the --try --keep scratch (delever_search creates a scratch TU somewhere). Let me check what --keep prints. Let me run dt with --keep... but dt.sh doesn't pass --keep. Let me run delever_search directly with --keep on c1.c.

Actually, simpler: I already have the answer I need from the target dump (reg 160=14, 162=11). Let me get the c1 numbers by running delever_search --try --keep and then dumping. Let me see what it prints.
