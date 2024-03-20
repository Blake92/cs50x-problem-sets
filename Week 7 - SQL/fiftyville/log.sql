 SELECT description FROM  crime_scene_reports WHERE description LIKE "%CS50%"; -- we know the the crime was committed at 10:15 AM and three witnesses mention the bakery
 SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2023 AND transcript LIKE "%bakery%"; -- we know that the thief withdrew money from an ATM in Leggett Street before the robbery, left the crime scene with a car from parking lot  within 10 minutes and called an accomplice to book the earliest flight out of fiftyville the next day for less than a minute

--based on the information we gathered, we query the database and find the person name linking all the info together
SELECT name FROM people WHERE id IN (
        SELECT person_id FROM bank_accounts WHERE account_number IN (
            SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
            )
        )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 and HOUR = 10 AND  minute <=25 AND activity = "exit"  -- we know that the thief exited the parking lot within 10 minutes of the robbery so we query in the timeframe within 15 and 25
        )
    AND phone_number IN (
        SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
        )
    AND passport_number IN (
        SELECT passport_number FROM passengers WHERE flight_id = (
            SELECT ID from flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id IN (
                SELECT id FROM airports WHERE city = "Fiftyville"
                )
            ORDER BY hour ASC, minute  -- this one was a little tricky, we need the earliest flight of the day, so we order the query in ASC and take the first result
            )
        );

-- The query found that the thief was Bruce, now we find the city he has escaped to

SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id IN (
        SELECT id FROM airports WHERE city = "Fiftyville"
    )
    AND id IN (
        SELECT flight_id FROM passengers WHERE passport_number = (
            SELECT passport_number FROM people WHERE name = "Bruce"
        )
    )
);

-- The query found that Bruce ecaped to New York City, we are lucky that there was only one bruce, aren't we? Now all we need to do is find the accomplice by seeing who bruce called that day 

SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
    AND caller in (
        SELECT phone_number from people WHERE name = "Bruce"
    )
);

-- The accomplice is Robin
