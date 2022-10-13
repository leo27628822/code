library verilog;
use verilog.vl_types.all;
entity ALU_MSB is
    port(
        dataOut         : out    vl_logic;
        set             : out    vl_logic;
        cout            : out    vl_logic;
        dataA           : in     vl_logic;
        dataB           : in     vl_logic;
        cin             : in     vl_logic;
        sel             : in     vl_logic_vector(1 downto 0);
        binvert         : in     vl_logic;
        less            : in     vl_logic
    );
end ALU_MSB;
