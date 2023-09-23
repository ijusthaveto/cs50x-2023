SELECT title
FROm movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p ON p.id = s.person_id
WHERE p.name = 'Bradley Cooper'
AND m.id IN (
 SELECT movie_id
 FROM stars
 WHERE person_id IN (
  SELECT id FROM people
  WHERE name = 'Jennifer Lawrence'
 )
);
