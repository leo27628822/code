library verilog;
use verilog.vl_types.all;
entity TM is
    generic(
        t               : integer := 200;
        th              : integer := 100
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of t : constant is 1;
    attribute mti_svvh_generic_type of th : constant is 1;
end TM;
