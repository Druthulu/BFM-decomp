---
ts: 2026-11-06T05:23:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BnZNuLQdn3trh4cbShzu
---
No effect. The stores are still removed. So it's not cse's alias logic; it's something else (maybe the tree-level or the store elimination in `flow`/`dbr`).

Let me find out which pass removes them. Let me check the .greg dump (before global-alloc, after combine and sched) for our function's stores. I need to locate our function in the dump. The dump file starts with the whole TU. Let me grep for a unique nearby symbol or the function's entry. The function is defined at the header include site; the dump may label it. Let me look at line 234 context.

Actually, let me use a different approach: count the `(mem:HI (plus:SI (reg:SI 29) (const_int 24)))` sets in the .flow and .greg dumps and compare. The frame pointer/stack pointer register number in the dump is 29 ($sp) or 30 ($fp). Let me grep for "const_int 24" with context of "set (mem:HI".

Let me find our function's dump section: the function appears once in the TU; the three "func_8014DF94" hits are probably the three header instantiations? No, the header is included once per member file; the TU is one member. Hmm, the header is included by the member; the member might include it multiple times? No.

Actually the three hits might be the function definition + two call references? Let me look at line 234 and 3089 and 55640.

Let me just grep the .greg dump for "set (mem:HI (plus:SI (reg:SI 29) (const_int 24" and count.
