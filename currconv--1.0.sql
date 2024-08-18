/* /currconv/currconv--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION currconv" to load this file. \quit

CREATE OR REPLACE FUNCTION convert_from_rub(float4) RETURNS text
AS 'MODULE_PATHNAME', 'convert_from_rub'
LANGUAGE C;
