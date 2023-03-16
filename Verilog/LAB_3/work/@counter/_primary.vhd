library verilog;
use verilog.vl_types.all;
entity Counter is
    generic(
        WIDTH           : integer := 8
    );
    port(
        dout            : out    vl_logic_vector;
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        en              : in     vl_logic;
        up              : in     vl_logic
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WIDTH : constant is 1;
end Counter;
