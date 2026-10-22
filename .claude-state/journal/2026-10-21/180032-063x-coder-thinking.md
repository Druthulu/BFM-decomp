---
ts: 2026-10-22T00:00:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_LjwBsEKLX8m2gFoYVIAd
---
Now the results.tsv rows. Format: `dir file func kinds result best tries wall evidence` (tabs).

Existing rows in results.tsv (4 items) end with the evidence. I need to append 5 rows in list.tsv order:
list.tsv order: 8017CE7C, 8017E204, 80182F44, 80187250, 8017E4E0, 8017FB50, 8017D3A0, 8017EEB0, 8014CF04.

So append: 8017E4E0, 8017FB50, 8017D3A0, 8017EEB0, 8014CF04.

Rows:
1. func_8017E4E0__ov_SC06_025_jr_8017BEBC	src/ov_SC06_025/ov_SC06_025_jr_8017BEBC.c	func_8017E4E0	pin	WALL	11	125	local-alloc-const-qty	gcc local-alloc: the -0xA0 const pseudo (3 refs, shortest range) wins $2 and shares the qty with the other consts; $3 needs a hard reg
   (evidence ≤140 chars — let me count: "gcc local-alloc: the -0xA0 const pseudo (3 refs, shortest range) wins $2 and shares the qty with the other consts; $3 needs a hard reg" = ~141. Trim: "gcc local-alloc: the -0xA0 const pseudo (3 refs, shortest range) wins $2, shares the qty with the other consts; $3 needs a hard reg" ~ 137. OK.

2. func_8017FB50__ov_SC06_025_jr_8017EEC4	src/ov_SC06_025/ov_SC06_025_jr_8017EEC4.c	func_8017FB50	pin	WALL	2	43	global-alloc-nrefs-prio	gcc global-alloc: 5-ref out-pointers outrank the 2-ref call result, so $16 goes to a pointer; s16 tmp flips it but adds a sign-ext pair
   (~145 → trim) "gcc global-alloc: 5-ref out-pointers outrank the 2-ref call result ($16 to a pointer); s16 tmp flips prio but adds a sign-ext pair" ~ 135 ✓

3. func_8017D3A0__ov_SC06_027_jr_8017BEBC	src/ov_SC06_027/ov_SC06_027_jr_8017BEBC.c	func_8017D3A0	pin	WALL	11	60	local-alloc-const-qty	same as func_8017E4E0: the -0xA0 const pseudo wins $2 and shares the qty with 0xA0/-0x78/0x78; $3 needs a hard reg
   (~140) ✓

4. func_8017EEB0__ov_SC06_032_jr_8017C24C	src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c	func_8017EEB0	pin	MATCH	0	21	-	gcc local-alloc: the 1st call's result moves to its own var w (2 uses); the stored value keeps the short range and wins $2, pin gone
   (~137) ✓

5. func_8014CF04__ov_SC07_006_jr_801457A4	src/ov_SC07_006/ov_SC07_006_jr_801457A4.c	func_8014CF04	pin	WALL	22	61	reload-second-base	gcc reload/loop.c: unpinned, GCC keeps a 2nd base q-1 (extra addiu+sw+loop inc) and q loses $17 to the params
   (~130) ✓

Also, the file must end with a newline and the existing file's last line — let me check whether the existing results.tsv ends with a newline. The `cat` output earlier showed the last row then "=== ls" — so it likely ends with a newline. I'll append with a python script to be safe (tabs!).

Let me write the append script.

Also the moves.md appends (5 lines):
Format: `kind | func | MATCH: the move / WALL: tag — mechanism (G06)`.

- `pin | func_8017E4E0 | WALL local-alloc-const-qty — the -0xA0 const pseudo (3 refs, shortest live range) wins $2 and shares the qty with the other constants; $3 needs a hard reg (G06)`
- `pin | func_8017FB50 | WALL global-alloc-nrefs-prio — the 5-ref out-pointers outrank the 2-ref call result in global-alloc, so $16 goes to a pointer; an s16 tmp flips the priority but adds a sign-extension pair (G06)`
- `pin | func_8017D3A0 | WALL local-alloc-const-qty — same as func_8017E4E0: the -0xA0 const pseudo wins $2, $3 needs a hard reg (G06)`
- `pin | func_8017EEB0 | MATCH — the first call's result gets its own var w (2 uses); the stored value keeps the short live range and wins $2, pin gone (G06)`
- `pin | func_8014CF04 | WALL reload-second-base — unpinned, reload/loop.c keeps a second address base q-1 (extra addiu+sw+loop inc) and q loses $17 to the params (G06)`

The moves.md is shared across shards — appending is allowed by the brief.

Let me write both appends with a python script (tabs for tsv).
