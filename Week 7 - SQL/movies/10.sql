--List the names of all people who have directed a movie that received a rating of at least 9.0
SELECT name FROM people WHERE id IN
    ( SELECT person_id FROM directors WHERE movie_id IN
        ( SELECT id FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE rating >= 9));