-- Keep a log of any SQL queries you execute as you solve the mystery.

-- The theft took place on July 28, 2021 and that it took place on Humphrey Street
SELECt description FROM crime_scene_reports
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';

SELECT transcript FROM interviews
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';

SELECT name suspects FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15 AND minute <= 25
ORDER BY suspects;

SELECt p.name as suspects FROM people p
JOIN bank_accounts b ON b.person_id = p.id
JOIN atm_transactions a ON a.account_number = b.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
ORDER BY suspects;

SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (
    SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
);

SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- The thief is Bruce!

SELECT city FROM airports
WHERE id = (
    SELECT destination_airport_id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
);

-- The destination is New York City!

SELECT phone_number FROM people WHERE name = 'Bruce';

-- Bruce's phone number is (367) 555-5533!

SELECT name FROM people WHERE phone_number = (
    SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = '(367) 555-5533'
);

-- Robin is the accomplice!