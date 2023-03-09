library verilog;
use verilog.vl_types.all;
entity AddSub4 is
    port(
        a               : in     vl_logic_vector(3 downto 0);
        b               : in     vl_logic_vector(3 downto 0);
        cin             : in     vl_logic;
        cout            : out    vl_logic;
        sum             : out    vl_logic_vector(3 downto 0);
        sel             : in     vl_logic
    );
end AddSub4;
