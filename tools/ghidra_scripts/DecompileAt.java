// DecompileAt.java — headless postScript: decompile the function at a given
// address (default 0x80018730, the LZSS streaming decompressor) and print the C.
// Used to verify Phase 1's milestone substance (recognizable LZSS code) directly
// from Ghidra's decompiler. Usage: -postScript DecompileAt.java [hexaddr]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

public class DecompileAt extends GhidraScript {
    @Override
    public void run() throws Exception {
        String addrStr = "80018730";
        String[] a = getScriptArgs();
        if (a.length > 0) addrStr = a[0];
        Address addr = toAddr(addrStr);
        println("=== DECOMPILE @ 0x" + addrStr + " ===");
        Function f = getFunctionContaining(addr);
        if (f == null) f = getFunctionAt(addr);
        if (f == null) {
            println("NO FUNCTION at/containing 0x" + addrStr + ". Raw instructions follow:");
            Instruction ins = getInstructionAt(addr);
            for (int i = 0; i < 24 && ins != null; i++) {
                println(String.format("  %s  %s", ins.getAddress(), ins.toString()));
                ins = ins.getNext();
            }
            println("=== END DECOMPILE ===");
            return;
        }
        println("Function: " + f.getName() + " @ " + f.getEntryPoint()
                + "  bytes=" + f.getBody().getNumAddresses());
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        DecompileResults res = di.decompileFunction(f, 90, monitor);
        if (res != null && res.decompileCompleted()) {
            println(res.getDecompiledFunction().getC());
        } else {
            println("DECOMPILE FAILED: " + (res != null ? res.getErrorMessage() : "null result"));
        }
        di.dispose();
        println("=== END DECOMPILE ===");
    }
}
