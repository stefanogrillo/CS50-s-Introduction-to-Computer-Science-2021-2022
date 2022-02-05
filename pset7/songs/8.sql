-- SQL query that lists the names of the songs that feature other artists --

SELECT name FROM songs WHERE name LIKE "%feat%";

-- Do not focus on artist_id, since it is a unique value associated to the song --
-- Focus on song's name if it contains: feat, featuring. Search for a PATTERN --
