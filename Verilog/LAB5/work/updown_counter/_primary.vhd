library verilog;
use verilog.vl_types.all;
entity updown_counter is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        control         : in     vl_logic;
        count           : out    vl_logic_vector(7 downto 0)
    );
end updown_counter;
