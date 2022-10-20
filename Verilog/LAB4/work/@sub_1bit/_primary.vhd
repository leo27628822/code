library verilog;
use verilog.vl_types.all;
entity Sub_1bit is
    port(
        X               : in     vl_logic;
        Y               : in     vl_logic;
        Z               : in     vl_logic;
        B               : out    vl_logic;
        D               : out    vl_logic
    );
end Sub_1bit;
