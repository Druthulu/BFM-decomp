// GetSymbolAt.java — read-only: print the function/symbol name at a given address.
// Used by tools/ghidra_mcp_verify.sh to confirm (rule R9) that a recent edit actually
// persisted to the saved project DB after a Ghidra save-shutdown. No package decl
// (Ghidra script). Pure ghidra API (no extension import) so it compiles/run anywhere.
//
// Arg: <address> (e.g. 0x80018730). Prints: BFMVERIFY SYMBOL@<addr>=<name>

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;

public class GetSymbolAt extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] a = getScriptArgs();
        if (a == null || a.length < 1) {
            println("BFMVERIFY ERROR: missing address argument");
            return;
        }
        String argAddr = a[0].trim();
        long off = Long.decode(argAddr); // accepts 0x-prefixed hex
        Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(off);

        String name = "<none>";
        Function f = currentProgram.getFunctionManager().getFunctionAt(addr);
        if (f != null) {
            name = f.getName();
        } else {
            Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(addr);
            if (s != null) {
                name = s.getName();
            }
        }
        println("BFMVERIFY " + argAddr + " name=[" + name + "]");
    }
}
