-- SQL query to list the names of all people who starred in Toy Story

SELECT name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE title = "Toy Story";

-- First select column Name from Movies; join the Movies table with Stars table based on the "ids" of movies
-- Second, join People table to Stars table based on "ids" of stars/people
-- Third select the Title of interest
