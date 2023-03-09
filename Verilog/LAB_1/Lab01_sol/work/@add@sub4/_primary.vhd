library verilog;
use verilog.vl_types.all;
entity AddSub4 is
    port(
        a               : in     vl_logic_vector(3 downto 0);
        b               : in     vl_logic_vector(3 downto 0);
        sel             : in     vl_logic;
        s               : out    vl_logic_vector(3 downto 0);
        cout            : out    vl_logic
    );
end AddSub4;
