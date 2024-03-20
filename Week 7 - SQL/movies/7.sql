--List all movies released in 2010 and their ratings, in descending order by rating
SELECT movies.title, ratings.rating
FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010 ORDER BY rating DESC, title ASC;
