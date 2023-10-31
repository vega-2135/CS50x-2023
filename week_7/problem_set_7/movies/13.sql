-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

--     Your query should output a table with a single column for the name of each person.
--     There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--     Kevin Bacon himself should not be included in the resulting list.



-- Show name of all actors that have been in movies with Kevin Bacon born 1958 (don't show kevin bacon himself)
SELECT name from people WHERE id IN
(
    -- Get ids of all actors that have been in movies with Kevin Bacon born 1958
    SELECT person_id from stars WHERE movie_id IN
    (
        -- Get movie ids starred by Kevin Bacon
        SELECT movie_id from stars WHERE person_id =
        (
            -- Get kevin id
            SELECT id from people WHERE name = 'Kevin Bacon' and birth = 1958
        )
        -- Don't show kevin bacon in the result
    ) AND person_id !=
        (
            -- Get kevin id
            SELECT id from people WHERE name = 'Kevin Bacon' and birth = 1958
        )
);
