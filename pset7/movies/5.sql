-- SQL query to list the titles and release years of all Harry Potter movies, in chronological order 

SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year ASC;

-- The following query finds also films not included in the series (other documentaries), so it's wrong
-- SELECT title, year FROM movies WHERE title LIKE "%Harry Potter%" ORDER BY year ASC;
