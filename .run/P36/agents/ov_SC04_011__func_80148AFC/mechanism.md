# func_80148AFC (ov_SC04_011_after.c) — T7 agent c3 — IN PROGRESS

Best so far: score 6 (COUNT, 70 vs 71) — body.c. The whole case-0x53/0x73 block is byte-identical after
rewriting `if (lo != 0x80 || hi != 0x80) { ...; return 1; } return 0;` as the natural
`if (lo == 0x80 && hi == 0x80) return 0; ...; return 1;` (removes 3 levers: both $2 pins, the $3 pin and the memory barrier).
Remaining: the $5 pin + launder class (the missing `move s1,a1` copy) — same residual as the twins func_80148E54 / func_80148D44.
