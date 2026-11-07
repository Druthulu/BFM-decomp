---
ts: 2026-11-06T04:48:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pNgO9OSEMTLtHdfTKfY4
---
own_fallthrough checks labels between the branch and the first active insn. If a CODE_LABEL exists there (other than the passed label with nuses 1), own_thread=0.

So if the fall-through starts with a label that has ≥2 uses (i.e., another jump targets the if-body start), own_fallthrough=0. Then fill_slots_from_thread with own_thread=0 and thread_if_true=0: the loop `for (trial=thread; !stop_search_p(trial, !thread_if_true=1) && (!lose || own_thread=0); ...)`. stop_search_p with labels_p=1 → the CODE_LABEL at the start stops immediately → no fill → nop! 

So: create a label at the start of the if-body with ≥2 uses, i.e., another branch jumps to the body start. In C, that means a `goto` to the clamp statement from somewhere else, where gcc keeps the label because it's reached from two places. But then the target code would have a second jump to that label — changing instructions.

Unless... the second jump is a jump to the same place that would be optimized into the same target? Hmm.

Alternatively, a label with 2 uses could come from the same jump being duplicated? no.

Let's think about `LABEL_NUSES != 1`: even a label with nuses==1 stops the thread if it's not the `label` argument... The loop passes `label=NULL_RTX` and allow_fallthrough=1; condition: `insn != label` — with label NULL, any CODE_LABEL → return 0. So ANY label between the branch and the first active insn makes own_fallthrough=0! Even a single-use label.

Wait, but own_thread_p(thread=NEXT_INSN(insn), NULL_RTX, 1): the loop from thread to active_insn (the first active insn at/after thread). If thread is a CODE_LABEL, then insn=thread=CODE_LABEL → returns 0. But this only matters if there's a label immediately after the branch.

So: if the first thing after the conditional branch is a CODE_LABEL, own_fallthrough = 0, and then in fill_slots_from_thread the loop starts at trial=thread=label, and stop_search_p(label, labels_p=1) = 1 → loop doesn't run → no fill → nop!

But wait: for the target to still be correct, the label must not produce any instruction, and the branch's fall-through goes to the label. Labels are free (no bytes). And the label must survive to reorg. If it's referenced by another jump, it survives; if not, gcc's `delete_unreferenced_labels` removes it.

Can we get a label there that is referenced but the referencing jump is... hmm, any reference adds a jump somewhere.

BUT: here's the trick — a label can be referenced by a jump that is optimized away later, or by a `NOTE_INSN_...`? No.

Alternatively: a label right after the branch could come from a `goto` that is the same target as the branch, i.e., a conditional and an unconditional jump to the same label. Consider:

```
if (0x80 >= D_80078EBF) goto end;
D_80078EBF = 0x80;
end:
```

Hmm, that's the same as the if.

What if we write:
```
if (0x80 < D_80078EBF) {
  goto set;
}
goto end;
set:
  D_80078EBF = 0x80;
end:
```
That adds jumps.

OK, think differently: labels appear at loop heads too. do-while(0) — loop.c/flow might create a label? The `do { } while (0)` is usually optimized away at the tree level, but at -O2 with the old gcc, `do{}while(0)` might survive to RTL as a loop with a CODE_LABEL at the head? C0535 says do-while(0) splits cse1 EBB, so it does survive somehow (as a NOTE_INSN_LOOP_BEG? or a label?). Let's just try it.

Actually, hold on. Let me reconsider the whole item: maybe I'm overcomplicating. The moves catalog says barrier→"store per if-arm" for one function. For this one, maybe a simple statement-order/expression change makes cse/reorg produce the target.

Let me look at what the barrier does at the RTL level in the *original*: the asm is inside the if-body, before the store. `stop_search_p` stops eager fill. So the nop is because of the asm. A real-C equivalent must make the eager scan stop.

Given the analysis, the viable real-C mechanisms:
(1) a CODE_LABEL at the fall-through start with own_fallthrough=0 and stop_search_p(label)=1.
(2) an insn that `may_trap_p` (a load) or sets a needed resource (ra/sp) as the first insn.
(3) prediction>0 path: first try target thread; if it fills from the epilogue... no.

For (1): what if the if-body start has a label due to a *loop*? E.g., write the clamp as a `do { D_80078EBF = 0x80; } while (0);` inside the if. If gcc keeps the loop structure (label at head + jump back), we'd get extra code. But maybe loop.c converts it or deletes it. C0535 says do-while(0) splits cse1 EBB — that implies it survives as a loop until at least cse1, then gets removed? Hmm.

Let me just try a batch of candidates empirically. That's the fastest path. Let me write 8 bodies.

Body base (without barrier):

```c
void func_8014A59C(s32 a0) {
    s32 r;
    s32 add;
    if (*(u32 *)(a0 + 0x44) & 1) {
        if ((*(u16 *)(a0 + 0xAA) & 8) != 0) {
            r = func_80029178(0x20);
            add = 3;
            if ((r & 0xFF) != 0) {
                add = 6;
            }
            D_80078EBF = D_80078EBF + add;
            if (0x80 < D_80078EBF) {
                D_80078EBF = 0x80;
            }
        }
    } else {
        D_80078EBF = 0;
    }
}
```

Candidates:
b1: do { D_80078EBF = 0x80; } while (0); inside the if.
b2: add = 0x80; D_80078EBF = add;
b3: if (D_80078EBF > 0x80) { D_80078EBF = 0x80; }
b4: if (!(D_80078EBF <= 0x80)) { D_80078EBF = 0x80; }
b5: r = 0; D_80078EBF = 0x80; (dead reset before)
b6: if (0x80 < D_80078EBF) { s32 z; z = 0x80; D_80078EBF = z; }
b7: if (0x80 < D_80078EBF) { D_80078EBF = 0x80; } else { r = 0; } — adds.
b8: `if (0x80 < D_80078EBF) { D_80078EBF = (u8)0x80; }`
b9: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80 & 0xFF; }`
b10: use a pointer: `u8 *p = &D_80078EBF; ... if (0x80 < *p) { *p = 0x80; }`
b11: `if (0x80 < D_80078EBF) { D_80078EBF = 0x80; return; }`? changes.

Let me also consider that the `li v0,128` could be made non-movable by making v0 live at the epilogue... no.

Let me create the candidates and score them in one sc.sh call.

Actually, one more idea that directly targets `may_trap_p`: if the first insn of the body is a *load*, it can't be moved. Could we write the clamp value as a load from a global? e.g. `D_80078EBF = D_80078EBF;`? no. The value 0x80 must be a constant to match `li v0,128`.

Hmm, what if the store is done as `*(u8 *)&D_80078EBF = 0x80;` — same.

Let me try the batch. I'll write the files with a small script (Write tool for each is tedious; use a heredoc? Bash heredoc writes files — allowed? Writing under .run with bash is fine but the house style prefers the Write tool. However multiple files; I'll use the Write tool for a generator script under .run and run it. Simpler: use python script via Write.

Actually, simplest: write each candidate with the Write tool. 10 files. That's a lot of calls. Instead, write a generator script .run/P40/T11/G21/gen1.py that writes the bodies from a template with a `clamp` snippet. Then run it. Then sc.sh on all.

Let me do that.
