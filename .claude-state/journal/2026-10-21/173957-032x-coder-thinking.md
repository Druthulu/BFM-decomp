---
ts: 2026-10-21T23:39:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yBJuI0XgU6DggepgYbD5
---
`delever.py --apply-body TU FN FILE` writes the tree — not allowed for me (constraint: no writes to src/). But it "judges" — it may print the verdict including all recipes. Actually --apply-body applies (writes). Don't use.

Hmm, what about a read-only judge? `--plan`? `--status`?

Alternative for multi-includer verification: The "bank verdict" checks every recipe of the TU. There's `tools/delever.py --apply-body` (writes). Not allowed.

But maybe I can verify all includers by a different route: create a candidate body and check it against *each includer's baseline* by... the tool picks rec[0].

Practical approach: since the function body compiles identically regardless of includer (the header content is the same and the function is independent), scoring at rec[0] is strong evidence. To be safer, I can verify that the *baseline* function bytes are the same in all includer objects: e.g. compare objdump of the function in two different includer baseline objects. If identical, then one score suffices.

I can do that with tools/asm_verbatim.py or tools/asm-differ? Let me check tools/asm_verbatim.py --help. Actually simpler: use `tools/alloc_table.py`? Let me check what it does. Or find the baseline objects and objdump them with plain `objdump` (allowed? objdump is a binary in PATH; running it may be allowed).

Let me test: find baseline objects. oracle.baseline_path(rec["obj"]) — rec["obj"] is the object's path in the fleet run. Let me find objects for the 136 includers: build/<alias>/... hmm, build/md_MAIN_001/md_MAIN_001.elf exists. The baseline path probably under build/asm/<alias>/data/....

Let me look at build/asm/md_MAIN_001/data listing.

Honestly, the cheapest check: the diff output from --try gives target insns; if the target bytes are the same for all includers (they must be — the ROM function is one function, and each TU's build contains the same function compiled the same way), then it's fine. The only risk is that some includer has different macro context. Given all includers are "ov_*_after.c" files including the same header, likely identical.

I'll note in the log that the score was checked at the header's first includer and that the function's baseline bytes are includer-independent (evidence: the tool's --try compiles the candidate at rec[0] and compares against that includer's baseline object, which contains the same function).

Hmm, but to be more faithful to the brief, let me try to rotate includers. Idea: `tools/delever_search.py --try TU FN FILE --body` where TU is the header. recs_for(tu) returns recipes for includers in the order of inc.get(tu). If I could change the order... The order comes from dl.includers() → probably a scan of the tree. Not controllable.

Alternative idea: check the same function through a *different* header/TU that includes it? No.

Another idea: the tool has `--only` and `--plan` etc. Not helpful.

OK here's a cleaner idea: use `tools/asm-differ` or `tools/asm_verbatim.py` to compare the function bytes across two includer objects — if identical, one check is enough. Let me check what asm_verbatim does.

Let me not over-engineer. Priority: find lever-free bodies. I'll verify the includer-independence claim once per item using objdump on two baseline objects (cheap, one Bash call), and note it.

Let me now check where baseline objects live. Look at oracle.baseline_path.
