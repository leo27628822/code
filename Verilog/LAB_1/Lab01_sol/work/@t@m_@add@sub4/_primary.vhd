library verilog;
use verilog.vl_types.all;
entity TM_AddSub4 is
    generic(
        t               : integer := 200
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of t : constant is 1;
end TM_AddSub4;
