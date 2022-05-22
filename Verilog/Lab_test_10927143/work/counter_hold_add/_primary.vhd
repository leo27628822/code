library verilog;
use verilog.vl_types.all;
entity counter_hold_add is
    port(
        sel             : in     vl_logic_vector(1 downto 0);
        dout            : out    vl_logic_vector(3 downto 0);
        rst             : in     vl_logic;
        clk             : in     vl_logic;
        a               : in     vl_logic_vector(2 downto 0);
        b               : in     vl_logic_vector(2 downto 0)
    );
end counter_hold_add;
