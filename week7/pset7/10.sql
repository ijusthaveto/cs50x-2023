SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM directors
    WHERE movie_id in (
        SELECT movie_id FROM ratings
        WHERE rating >= 9.0
    )
);