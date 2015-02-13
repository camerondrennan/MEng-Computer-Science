set echo off
set linesize 140
define_editor = vi
set pagesize 50
column auto format A4
column pas format A3
column air_con format A3
column model_no format A8
column model_name format A10
column length format 999.99
column width format 99.99
column regi format A4
column new format 99,990.99
column avg(new) format 99,990.99
column avg(a1) format 99,990.99
column avg(good) format 99,990.99
column avg(fair) format 99,990.99
column avg(poor) format 99,990.99
column avg(trade) format 99,990.99
column a1  format 99,990.99
column good format 99,990.99
column fair format 99,990.99
column poor format 99,990.99
column trade format 99,990.99
column hw format 90
column hd format 90
column hl format 90
column aw format 90
column ad format 90
column al format 90
column hf format 90
column ha format 90
column af format 90
column aa format 90
column pts format 90
column p format 90
set termout off
create synonym model for jnw.model;
create synonym derivative for jnw.derivative;
create synonym year_price for jnw.year_price;
create synonym emp for jnw.emp;
create synonym dept for jnw.dept;
set termout on
set echo on
