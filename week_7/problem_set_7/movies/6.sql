-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.

--     Your query should output a table with a single column and a single row 
--     (not counting the header) containing the average rating.

SELECT avg(rating) 
FROM ratings 
WHERE movie_id 
IN (SELECT id FROM movies where year = '2012');
