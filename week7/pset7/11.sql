SELECT m.title
FROm movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id
JOIN ratings r ON r.movie_id = s.movie_id
WHERE p.name = 'Chadwick Boseman'
ORDER BY r.rating DESC
LIMIT 5;