---
ts: 2026-11-06T15:01:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k7US60jyOvCcl4ZSrAEZ
---
Key: `birthing_insn_p` requires `bb_live_regs & bit` (the dest reg is live at block start) AND `reg_n_sets[i] == 1` — i.e., the pseudo is set exactly ONCE in the whole function. So a second set (reg_n_sets == 2) demotes the birth boost.

Which pseudo? The vol pseudo. In the original single expression, vol is set once → its division insn is a birthing insn (dest live at block start? vol is declared at top and used later... bb_live_regs is per basic block; vol is live into the block if used later — it is, in the func_8002D4C8 call, which is in the same block). So the division insn that sets vol gets max_priority → hoisted first. With a second set of vol, reg_n_sets[vol]=2 → not birthing → no boost.

So ANY second set of the same pseudo works. t1 splits vol into two sets → reg_n_sets=2. But careful: the second set must not be coalesced away by cse/fold into one. `vol = (0xA0-av)*0x7F; vol = vol/0xA0;` → two separate sets in RTL. Good.

But also the first set (`vol = (0xA0-av)*0x7F`) would be the birth insn — it's set once at that point? No — reg_n_sets[vol] = 2, so neither gets boosted. 

Now the question: does the split change the actual instructions? Original: `(0xA0 - av) * 0x7F` then `/ 0xA0`. With split, same operations. The intermediate result must live in a register between the multiply and divide. In the original it also does. Register allocation could differ slightly (the pseudo for the intermediate now is vol itself, same hard reg as final vol — actually better/identical). Let's test.

Also I should double-check: is there only ONE launder in the body? grep.
