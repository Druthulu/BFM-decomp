---
ts: 2026-11-06T08:56:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IoS1yQKe96dp7w0wSfmG
---
h1 scores 0! MATCH — the single-statement `p = *(u16 *)(((Unkstruct_801896EC *)self)->unk20 + 0x18);` gives the right allocation. 

Let me verify h1 has no asm and no pins added (it keeps the a1/a0 pins from orig — allowed as other kinds). Score 0 confirmed by sc.sh. Let me double-check with dt.sh and confirm the body is the lever-free one (no keepalive). h1 has the two register pins but no keepalive asm. 

Item 2 = MATCH. Let me copy h1 to win.c, write notes, and append the moves.md line.

Wait — must also confirm that the result is against the current src (yes, we extracted orig.c from current src, and h1 differs only in the else branch).

Let me finalize item 2:
- win.c = h1.c
- notes.md
- results row: MATCH, best 0, tries ~5, wall -, evidence.

Also append to moves.md: `keepalive | func_801896EC | MATCH: p's pointer and lhu folded into one statement (`p = *(u16*)(self->unk20 + 0x18)`) — p drops from 4 refs/long live to 2 refs, v0/v1 swap closes (G25)`.

Wait, the moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (G25)`.

Let me first double check the h1 score with dt.sh, then write files.

Then item 3: func_8017DB98.

Let me do item 2 finalization now.
