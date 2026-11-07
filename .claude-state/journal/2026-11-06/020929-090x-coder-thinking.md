---
ts: 2026-11-06T09:09:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HlRXxgDMiwxTOqqHvVOB
---
There are many MATCHes using dead resets (`p1 = 0;`, `m1 = 0;`, `x = 0`) — the §373/C0414 dead-reset technique is accepted as a legitimate move in this project, even for `barrier` and `launder` kinds. E.g. line 254: "MATCH: ... + dead reset x=0 (C0414) after t=diff<<9; cse1 drops the value ...". So dead stores are accepted real C.

But our v31 is not a dead *reset* of a value that's later used; it's a dead *conditional store* that keeps a dead computation alive. That's closer to a keepalive in spirit.

Hmm. Let me think about what distinguishes a "crack" from a "new lever". The project's rule: a crack removes the artificial lever and finds real C that produces the same code. If the real C is itself an artificial construct whose only purpose is codegen steering (a dead store, a dead reset), the project still accepts it — the dead-reset is a documented technique (C0414). The line between "real C" and "lever" is drawn at asm/pins/identity-launders, per the brief's enumeration.

The brief says: "no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

A dead `if` that keeps a dead product — I'd classify it as a new keepalive (artificial liveness). It's not in the enumerated banned list but "no new lever of any kind" covers it.

Hmm, but consider: is the product dead in the *target*? Yes. The target's dead multiply is what the asm forced. A real-C crack must force it too. The ONLY ways are artificial (a dead store or a branch). If the project's standard allows dead-resets, then a dead store is "real C". The dead-reset technique also creates a dead store artificially. The difference: a dead reset's store is deleted and doesn't keep a computation; here the dead *branch* keeps the computation.

Given the ambiguity, what's the best action? The brief says MATCH = the kinds gone. The expert judges. I should report what I found honestly and let the expert decide: either mark MATCH with v31 (with a clear note about the mechanism) or mark WALL with best 0-but-lever-in-disguise. 

Hmm, the instructions: "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". This tells me the project cares about not laundering the same lever into another form. A dead-if keepalive is arguably "the keepalive lever in C form". The task is to remove the keepalive; if the replacement is another keepalive (a dead store that the optimizer keeps until after flow), the item isn't cracked in spirit.

Let me look at the wall list for a tag like "keepalive-in-disguise" or similar... The walls.txt has `flow-unused-result` which is exactly this: "flow deletes results the target computes but never uses". The dead multiply is a flow-unused-result. The only way to keep it is a use; a real use costs an insn; a fake use is a lever.

I'll make a decision: report the item as WALL `flow-unused-result` with best 20, BUT note in the evidence/notes that a dead-store condition (`if (product) cull = 1;`, cull dead) reproduces the bytes (score 0) and is a *keepalive-class lever in C form*, not a crack. That's the honest, conservative call, and it gives the expert the information to override.

Hmm, but the brief's DONE WHEN: "every item of G24x/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." A WALL row is fine.

But wait — should I instead record MATCH with v31? The risk of a false MATCH is higher (the shard's whole purpose is deleveraging; a disguised lever would pollute the bank). The risk of a WALL is a missed crack. The expert can review. The project's honesty rule: report what's true. I'll go with WALL and document v31 explicitly.

Hmm, hold on. Let me reconsider once more. Is `if (product) cull = 1;` really a "keepalive" in the project's taxonomy? Let me look at how the project defines "keepalive" in the context: the row kinds are pin/launder/barrier/keepalive. A keepalive is typically `__asm__("" :: "r"(x))` or a macro. The kind was assigned by the delever tool based on the site. The task: remove it. v31 removes it. The replacement construct is a dead store.

The project's C0414 dead-reset is explicitly a *launder* replacement (it's used to break cse equivalence). In our case the dead store is used to keep a value live — that's a keepalive replacement. There's no documented cookbook entry for "dead-store keepalive"; if I found one, it would be a new technique. The brief says "no new lever of any kind" — so it's banned.

Decision: WALL, best 20, with v31 documented as a near-miss that is a lever in disguise (score 0 but artificial).

Hmm, wait. But then my results row says WALL best 20 — the lowest score of a *lever-free* body is actually 0 (v31, which is lever-free by the enumerated list but is a new lever by spirit). Ugh. The definition: "best = lowest score of a lever-free body". v31 is not lever-free if we consider the dead-if a lever. So best = 20 is consistent with my judgment.

Let me also double-check the timing: item started 01:54, now ~02:10. 16 min. I need ≥20 min for a WALL. I'll spend a few more minutes trying one more avenue, then finalize at ~02:15.

One more avenue: can we make the dead multiply survive *without* a dead store/branch, i.e., with a real use that costs no insn? What about making the product part of an expression that feeds something already computed? E.g., the `w = (u32)p & 0xFFFFFF;` — no.

What about making the product's result the *condition* of an existing branch? The target has branches: `if (otz > 0 && cull == 0)`. What if we replace `otz > 0` with `(a[2]-z)*buf[5] > 0`? The target's condition loads otz from the stack and does `blez`. If we used the product instead, the code would differ (mult instead of lw). No.

What about `if (a[8]) idx -= 0x40;` → `if ((a[2]-z)*buf[5] && a[8])`? changes.

What about the `if (a[7] == 0) a[7] = 1; else if (a[7] == 1) a[7] = 2;` → add the product? changes.

No.

Another avenue: the `mult` could be kept if its result feeds a *dead* `mflo` that's part of a HI/LO chain? E.g., if a later `mfhi` exists... no.

I'm settling on WALL. Let me finalize at the 20-minute mark. Let me do one more batch of 3-4 variants to be thorough (and use the time):
- v35: `if (product) tt = 1;` with tt dead (a new temp) — the branch's body sets a dead temp; same mechanism as v31 but with a temp instead of cull.
- v36: `if (product) idx = 0;` — idx is pinned $4; the store is dead? idx is assigned later inside the if-block. Hmm, `idx = otz;` comes later. So idx = 0 is dead → same mechanism, but idx is a pinned variable; might differ.
- v37: `cull = (product) != 0;` — dead assignment to cull (overwritten by cull=0) → maybe the product is kept? cull = product != 0 creates slt; the assignment is dead → flow deletes the slt? The slt is a register set (dead) → deleted, and then the mult dead → deleted. Probably 22.
- v38: `if (product) { }` — empty body → tree-level removal.

v35/v36 are the same class as v31 (dead-store keepalive). They'd score 0 too, but they're not legitimate. I don't need more of that class.

Let me instead try:
- v37: `if (product) cull = 1; else cull = 0;` — a real if/else where both arms set cull, and cull is later overwritten by `cull = 0;`. This is a *complete* conditional assignment (not obviously a dead store); the branch would be kept until jump2? The else arm `cull = 0` and then the later `cull = 0` — gcc might merge. Let me test; if it scores 0 and looks like a real statement, it's still a dead store.

Honestly, any construct that keeps the dead multiply is artificial. The question is whether the project accepts it.

Let me look at the brief's wording once more: "write a lever-free body of func ... that scores 0. Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

"keepalive macro or asm" — so keepalives are macros or asm. v31 has neither. "no new lever of any kind" — a dead-if is not a lever of the pin/launder/barrier/keepalive kind per the enumeration... but "any kind" is broad.

Consider the project's own acceptance of dead-resets (C0414) which ARE artificial constructs. The line the project draws: asm-based or identity-based tricks are levers; dead stores/resets in plain C are accepted (they're "real C" — the original compiler's behavior is being matched by legitimate source). Indeed, dead stores are common in real code.

Hmm, actually, a dead `if` is NOT something a real programmer would write. But neither is `p1 = 0;` (dead reset). The project accepted those as moves because they're plain C and the original binary plausibly had them.

The target binary has a dead multiply. The original source plausibly had something like `if (product) ...` — a dead computation that the compiler kept. Actually, you know what? The original source might genuinely have had a dead branch! In real game code, you see things like:
```c
if ((a[2] - z) * buf[5]) {
    ...
}
```
Hmm.

Given the target binary itself has a dead multiply, the original C likely had a use that the compiler couldn't fully eliminate. A dead conditional store is a plausible original.

I need to decide. The safest for the project: report WALL with a clear note that v31 (dead-store condition) scores 0 but is a keepalive-class lever in C form, and let the expert decide. The expert can flip it to MATCH if they consider it legitimate.

Actually, hmm, wait. Let me reconsider the item's framing: the shard's items are "singleton crack shard G24x (scratch-only)" — the coder writes results and the expert banks them. A WALL with a documented near-miss is valuable.

But there's a risk the expert wants MATCH. The results.tsv format only allows one result. I'll go WALL and document v31 prominently in notes.md and the moves.md line. Hmm, but the moves.md line format: `kind | func | MATCH: move / WALL: tag — mechanism (G24x)`.

Let me finalize: WALL flow-unused-result, best 20, tries 34 (c1,c2,c3,v01-v31,v32-v34 = let me count: c1,c2,c3 = 3; v01..v34 = 34; total 37 lever-free bodies scored; plus orig). Wait v01-v26 = 26, v27-v30 = 4, v31-v34 = 4 → 34 variants + 3 = 37 lever-free scored bodies. Plus orig baseline = 38 scored runs.

Hmm, the results row currently says tries 33. Let me update it to 37. But wait — should I count v31 (score 0)? It's a lever-free body by the enumerated list but I'm calling it a lever. For "tries", count all scored lever-free candidates: 37.

Let me update the row (one action per command per the brief: a results.tsv fix is its own step).

Time: ~02:11. Let me also spend a couple more minutes on one genuinely different idea before finalizing at 02:14+.

Genuinely different idea: what if the product is used to *compute an address that the target computes anyway*? E.g., `gte_ldv3c(&v[0])` — the target computes `addiu v0,sp,16`. If the source were `gte_ldv3c(&v[(product) & 0])`, the index would fold. What about `&v[0] + (product)*0`? folds.

What about `&v[(product) == 0 ? 0 : 0]`? folds.

What about a pointer offset with a runtime-zero: `((u8*)&v[0] + (product & 0))`? folds.

OK. Another: **the `p++` / `p = (FT4*)...`**? no.

Another: the target's `w = (u32)p & 0xFFFFFF;` — what if the source used the product in the mask computation with a fold? no.

I'm done. Let me finalize the records: update the results row's tries to 37, and expand the notes with the v31 finding. And the moves.md line: I already appended a WALL line; I should update it to mention the v31 near-miss. But moves.md is append-only ("append one line"). I can append another line? The brief says "after each item append one line". One line per item. Hmm, I already appended one line for item 3. I shouldn't append a second. Can I edit the line I appended? "append-only" means no rewriting others' lines. My own line could be... risky. I'll leave the moves.md line as is (it's accurate: WALL flow-unused-result with the mechanism) and put the v31 detail in notes.md and the results evidence. Actually, the evidence field should mention the near-miss. Let me update the results row (its own step) with tries 37 and evidence mentioning the dead-store condition.

Let me write the final evidence: "dead product kept only by a real store (+1 ins, best 20); a dead-store `if (product) cull=1;` scores 0 but is a keepalive-class lever in C form; flow insn_dead_p deletes dead reg sets" — that's >140 chars. The brief says evidence ≤140 chars. Let me count and trim:

"dead product; a real store keeps it (+1 ins, best 20); dead-store if scores 0 but is a keepalive-class lever; flow insn_dead_p deletes dead reg sets" — ~140. Let me count: 
"dead product; a real store keeps it (+1 ins, best 20); dead-store if scores 0 but is a keepalive-class lever; flow insn_dead_p deletes dead reg sets"
d-e-a-d(4) space(5)... let me count programmatically later. I'll aim ~135.

Hmm, actually — wait. I want to reconsider the MATCH question one final time, because it materially affects the shard's value.

Let me re-read the brief's constraint: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". This is specifically about identity *statements* that launder a value. A dead conditional store is not an identity statement.

And the enumeration of banned levers: "no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm". A dead if is none of these. "no new lever of any kind" — the phrase's intent is to prevent *new asm/pin/etc.* constructs.

The project's precedent (dead resets accepted as MATCH, including for `barrier` and `launder` kinds) suggests dead stores are legitimate real C.

So maybe v31 IS a MATCH. The mechanism: a dead conditional store keeps the value live through flow; jump2 removes the branch. This is a real C construct that produces the target bytes.

But is it "the same lever in disguise"? The asm keepalive's purpose was to keep the *product computation* alive. v31's purpose is exactly the same. So the lever (artificial liveness) is still there, just in C form. The task says "Lever-free = none of the row kinds remain". The row kind is "keepalive". Is v31's dead if a keepalive? I'd say yes: it's an artificial use whose only effect is to keep a dead computation.

Argh. Let me look at how the tool classifies sites: the delever tool found "site keepalive line 3235 NEEDED". If I feed v31 to the tool, it scores 0 — the tool would consider it a crack.

The brief's purpose: the shard produces MATCHes where the asm lever is replaced by real C. The expert reviews. A dead-store keepalive might be rejected by the expert as a disguised lever — and the brief explicitly warns against identity launders for that reason.

I'll go with WALL, documenting v31 as a score-0 but lever-in-disguise near-miss. This is the conservative, honest call, and the notes give the expert everything.

Hmm, but hold on: if the expert wanted MATCH, my WALL row understates. If the expert wanted WALL, a MATCH row would be a false crack banked. Given the project's strong emphasis on "verify the verifier" and honesty, WALL is safer.

Hmm, hmm. Actually, let me reconsider the semantics one more time: is there ANY way the dead-store if could be part of the original source in a meaningful way? E.g., the original might be:

```c
if ((a[2] - z) * buf[5]) {
    cull = 1;
}
```
No programmer writes that (cull is reset right after).

OK final: WALL.

Wait, actually, let me reconsider whether a *real* use exists that I haven't tried: **use the product in a call to func_8017E410's sibling?** no.

**Use the product as the value of `otz` and remove the gte_stszotz store's overwrite by...** no.

**Use the product in the `gte_stszotz` macro's clobber?** no.

Done. Let me finalize: update results row tries to 37 and evidence, expand notes with v31, and finish. Time check: 02:12. The item's wall requirement: ≥20 min → 01:54+20 = 02:14. Let me do the record steps (they take a couple of minutes) and finish at ~02:15.

Actually, one more thing to verify for the WALL: "best = lowest score of a lever-free body" — I should make sure the best lever-free body is 20. v18/v19/v20 = 20. Yes.

Let me update the results row now (separate command from the check).
