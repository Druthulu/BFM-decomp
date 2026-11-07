---
ts: 2026-11-06T15:41:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_POsXnrj5lAu1Li3xnqMa
---
Still sum in s0. So the do-while didn't split the cse EBB where it matters (maybe the EBB split happens but cse still has the constant).

At this point I have 32 scored tries. The wall tag cse-const-addr fits. But hold on — let me think about the actual mechanism once more. The cse fold happens because mb's value is the constant symbol. The launder makes it unknown.

Is there a plain-C way to make gcc not substitute a constant into a register? The substitution is cse's `equiv_constant` (reg_equiv_constant) which applies when a register has a single constant set. If mb is set from a constant but *also* used in a context that requires a register (e.g., taking its address or using it as an asm operand), cse won't substitute. Plain C: taking the address of mb (`&mb`) forces mb into memory and adds code. 

What if mb is used as an lvalue in a way cse sees? Like `mb = (u8*)&D_800AF630; ... mb++; ...`? The increment changes the value.

Hmm — what if we do the increment and then decrement? identity, disallowed.

What if the base is `mb` but the calls use `mb + 0x18` and we *also* use mb as a byte store base somewhere between? That adds instructions.

I'm fairly confident this is the cse-const-addr wall. But the brief says a WALL needs ≥20 min and ≥30 scored tries. Let me check the elapsed time: item 2 started around 08:35? Let me check current time.

Actually, wait. Let me try one more class: the "named derived pointer kept as a register address" — what if we make the *derived* pointer `mb18 = mb + 0x18` named and use it twice, with mb constant? cse folds mb18 to constant. Same.

What about making the base pointer come from a *struct copy* of the matrix? no.

One more idea: use `param_4` legitimately? The address D_800AF630 is fixed. Hmm.

What about a *different symbol*: maybe the original source used `&D_800AF630` but the TU could declare it with a different type such that the +0x18 is a field access through a *pointer dereference* that cse can't fold... e.g. `extern u8 *D_800AF630;`?? That would change the object.

I'll wall this item. But wait — before walling, the brief says WALL (best = lowest score of a lever-free body). Best lever-free is 6. Wall tag: cse-const-addr. Evidence: gcc pass + mechanism ≤140 chars.

Let me verify the elapsed time for item 2. Let me check date now.
