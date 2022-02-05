-- SQL query to list the names of all songs in increasing order of tempo --
-- ASC is acending order, DESC is descending --

SELECT name FROM songs ORDER BY tempo ASC;

-- List by name, case insensitive: SELECT name FROM songs ORDER BY UPPER(name) ASC; --
