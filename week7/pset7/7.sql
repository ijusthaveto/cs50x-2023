SELECt title, rating
FROM movies, ratings
WHERE id = movie_id
AND year = '2010'
AND rating IS NOT NULL
ORDER BY rating DESC, title ASC;