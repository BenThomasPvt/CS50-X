-- Keep a log of any SQL queries you execute as you solve the mystery.

--Report of the crime
SELECT * FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2023
AND street = 'Humphrey Street'
AND description LIKE '%theft%';
--id of the cime is 295, time is 10:15am, location near Emma's bakery

--Interviews
SELECT * FROM interviews
WHERE day = 28 AND month = 7 AND year = 2023
AND transcript LIKE '%bakery%';
--interview ids 161, 162, 163; eugene recognised - atm on leggett street; Raymond - theif talked call for less than a minute, earliest flight the next day

--Bakery security logs
SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2023
AND hour = 10 AND minute BETWEEN 15 AND 25 ;

--license plates near bakery at the time of crime
SELECT people.name, bakery_security_logs.license_plate
FROM bakery_security_logs
JOIN people ON people.license_plate  = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2023
AND hour = 10 AND minute BETWEEN 15 AND 25 ;

--atm on legget street
SELECT * FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND day = 28 AND month = 7 AND year = 2023;
--WITH NAMES
SELECT a.*, p.name
FROM atm_transactions a
JOIN bank_accounts b ON a.account_number = b.account_number
JOIN people p ON b.person_id = p.id
WHERE atm_location = 'Leggett Street'
AND day = 28 AND month = 7 AND year = 2023
AND a.transaction_type = 'withdraw';

--phone calls
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2023
AND duration < 60;
--with names
SELECT p.name, pc.caller, pc.receiver
FROM phone_calls pc
JOIN people p ON pc.caller = p.phone_number
WHERE pc.day = 28 AND pc.month = 7 AND pc.year = 2023
AND pc.duration < 60;

--airports
SELECT * FROM airports;
--id 8 CSF
SELECT f.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
FROM flights f
JOIN airports origin ON f.origin_airport_id = origin.id
JOIN airports destination ON f.destination_airport_id = destination.id
WHERE origin.id = 8 AND f.day = 29 AND f.month = 7 AND f.year = 2023
ORDER BY f.hour, f.minute;
--to NYC, 36

--intersection of three interviews
SELECT p.name
FROM bakery_security_logs bsl
JOIN people p ON p.license_plate = bsl.license_plate
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE bsl.day = 28 AND bsl.month = 7 AND bsl.year = 2023
AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 25
AND at.atm_location = 'Leggett Street'
AND at.day = 28 AND at.month = 7 AND at.year = 2023
AND at.transaction_type = 'withdraw'
AND pc.day = 28 AND pc.month = 7 AND pc.year = 2023
AND pc.duration < 60;
--we got names Bruce and Diana

--who boards the flight
SELECT p.name
FROM people p
JOIN passengers ps ON p.passport_number = ps.passport_number
WHERE ps.flight_id = 36
AND p.name IN ('Bruce', 'Diana');
--IT WAS BRUCE!!!!

--accomplice
SELECT p2.name AS receiver
FROM phone_calls pc
JOIN people p1 ON pc.caller = p1.phone_number
JOIN people p2 ON pc.receiver = p2.phone_number
WHERE p1.name = 'Bruce' AND pc.day = 28 AND pc.month = 7 AND pc.year = 2023
AND pc.duration < 60;
