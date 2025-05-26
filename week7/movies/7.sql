SELECT movies.title, MAX(ratings.rating) AS highest_rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
GROUP BY movies.title
ORDER BY highest_rating DESC, movies.title;
