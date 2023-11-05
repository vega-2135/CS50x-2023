.schema crime_scene_reports;
-- Check in table crime_scene_reports, report of crimes that occurred on the 28 of July of 2021 in Humphrey Street
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND year = '2021' AND month = '7' AND day = '28';

-- Check .schema interviews to see what colums this table has
.schema interviews

-- Check interviews table from the day and street where the crime took place
SELECT * FROM interviews WHERE year = '2021' AND month = '7' AND day = '28';

-- transcript
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Check earliest flight from Fiftyville
SELECT * FROM airports WHERE city = 'Fiftyville';
SELECT * FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = '2021' AND month = '7' AND day = '29';

-- id	origin_airport_id	destination_airport_id	year	month	day	hour	minute
-- 36	8	                        4	            2021	  7	     29	 8	      20
-- 43	8	                        1	            2021	  7	     29	 9	      30


-- Check atm trasactions and bakery sequrity logs from people that used the atm on the day that the robery took place and also parked in bakery

-- This are the new suspects:

-- Check the transaction that where made before robery (check interviews)
SELECT * FROM bakery_security_logs WHERE license_plate IN(
    SELECT license_plate from people WHERE id
        IN(SELECT person_id FROM bank_accounts WHERE account_number
            -- Check account numbers from people that withdrowed money at Leggett Street when the crime happened
            IN(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = '2021' AND month = '7' AND day = '28')))AND year = '2021' AND month = '7' AND day = '28' AND hour < '10';


-- Suspects:
SELECT * from people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN(
    SELECT license_plate from people WHERE id
        IN(SELECT person_id FROM bank_accounts WHERE account_number
            -- Check account numbers from people that withdrowed money at Leggett Street when the crime happened
            IN(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = '2021' AND month = '7' AND day = '28')))AND year = '2021' AND month = '7' AND day = '28' AND hour < '10');

-- id	    name	phone_number	passport_number	license_plate
-- 396669	Iman	(829) 555-5269	  7049073643	   L93JTIZ
-- 449774	Taylor	(286) 555-6063	  1988161715	   1106N58
-- 467400	Luca	(389) 555-5198	  8496433585	   4328GD8
-- 514354	Diana	(770) 555-1861	  3592750733	   322W7JE
-- 686048	Bruce	(367) 555-5533	  5773159633	   94KL13X

-- Check flights taken by suspects, search for flight 36 and 43 (the earliest flights on the 29th)
SELECT * FROM passengers WHERE passport_number IN(SELECT passport_number from people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN(
    SELECT license_plate from people WHERE id
        IN(SELECT person_id FROM bank_accounts WHERE account_number
            IN(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = '2021' AND month = '7' AND day = '28')))AND year = '2021' AND month = '7' AND day = '28' AND hour < '10'));

-- flight_id	passport_number	seat
-- 36	        5773159633	     4A
-- 36	        1988161715	     6D
-- 36	        8496433585	     7B

-- Check destination of flight 36
SELECT * FROM flights WHERE id = '36';

-- Check all info from arrival airport of flight 36
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = '36');

-- Check name from passport_number from above
SELECT name FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE passport_number IN(SELECT passport_number from people WHERE license_plate IN(SELECT license_plate FROM bakery_security_logs WHERE license_plate IN(
    SELECT license_plate from people WHERE id
        IN(SELECT person_id FROM bank_accounts WHERE account_number
            IN(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = '2021' AND month = '7' AND day = '28')))AND year = '2021' AND month = '7' AND day = '28' AND hour < '10'))AND flight_id = '36');

-- names: Taylor Luca Bruce

-- Check call made by those persons (start with Luca) and then check if receivers took the same flight as the caller

-- LUKA:

-- Calls from Luca wheren't on the 28th phone_number
SELECT * FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Luca');

-- Check for people that called Luka on the 28th
SELECT * FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Luca');

-- Check names of people who called Luca
SELECT name FROM people WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Luca')));
--names: Walter Kathryn

-- Check if one of those callers took the same flight as luca on the 29th
SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Luca'));

SELECT * FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Luca')));

--Check flights taken by Walter and Kathryn (none of them are on the 29th)
SELECT * FROM flights WHERE id IN(SELECT flight_id FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Luca'))));

-- TAYLOR
-- Check calls made by Taylor on the 28th
SELECT * FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Taylor');

-- Check for shorter call made
SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Taylor') AND duration <= '60';

-- CHeck for name of receiver of shorter call
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Taylor') AND duration <= '60');
--name: James

-- Check receiver phone numbers
SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Taylor') AND year = '2021' AND month = '7' AND day = '28';

-- Check flights taken by those persons ()none on the 29th
SELECT * FROM flights WHERE id IN(SELECT flight_id FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Taylor') AND year = '2021' AND month = '7' AND day = '28')));


-- Check for people that called Taylor on the 28th
SELECT * FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Taylor');

-- Check names of people who called Taylor
SELECT name FROM people WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Taylor')));
--names: Kayla, Billy, Ralph

-- Check if one of those callers took the same flight as Taylor on the 29th
SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Taylor'));

SELECT * FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Taylor')));

--Check flights taken by callers (none of them are on the 29th)
SELECT * FROM flights WHERE id IN(SELECT flight_id FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Taylor'))));


-- BRUCE ---> THIEF
-- Check calls made by Bruce on the 28th
SELECT * FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce');

-- Check receiver phone numbers on the 28th
SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = '2021' AND month = '7' AND day = '28';

-- Check for shorter call made
SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = '2021' AND month = '7' AND day = '28' AND duration <= '60';

-- CHeck for name of receiver of shorter call
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = '2021' AND month = '7' AND day = '28' AND duration <= '60');
--name: Robin ---> ACCOMPLICE

-- Check flights taken by those persons ()none on the 29th
SELECT * FROM flights WHERE id IN(SELECT flight_id FROM passengers WHERE passport_number IN(SELECT passport_number FROM people WHERE phone_number IN(SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = '2021' AND month = '7' AND day = '28')));


-- Check for people that called Bruce on the 28th...NONE on the 28th
SELECT * FROM phone_calls WHERE receiver = (SELECT phone_number  FROM people WHERE name = 'Bruce');
