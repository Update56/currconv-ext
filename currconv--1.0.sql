/* /currconv/currconv--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION currconv" to load this file. \quit

CREATE OR REPLACE FUNCTION currency_convert(text ,float4) RETURNS text
AS 'MODULE_PATHNAME', 'currency_convert'
LANGUAGE C;
