-- Keep a log of any SQL queries you execute as you solve the mystery

-- Open the SQL prompt: sqlite3 fiftyville.db
-- The theft took place on July 28, 2021 and it took place on Humphrey Street

-- 1 Seek information about the crimes occurred the July 28, 2021 on Humphrey Street
SELECT description FROM crime_scene_reports WHERE year = "2021" AND month = "7" AND day = "28" AND street = "Humphrey Street";
-- Theft of the CS50 Duck took place at 10:15 am at Humphrey Street Bakery. 3 witnesses interviewed.

-- 2 The theft took place at 10:15 am at the Humphrey Street bakery; seek for interviews of 3 witnesses on July 28, 2021; Littering at 16:36
SELECT transcript FROM interviews WHERE year = "2021" AND month = "7" AND day = "28";
-- (1) The thief left the Bakery's parking lot with a car at 10:25 am circa; see security footage for the plate
-- (2) the thief withdrawed money at Leggett Street ATM earlier in the morning;
-- (3) the thief made a call that was less than a minute long, asking for the earliest flight ticket in the next morning to the other person

-- 3.1 PARKING LOT
SELECT activity, license_plate, minute FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "25" AND activity = "exit";
-- LICENSE PLATES EXITING:
-- (10:16) 5P2BI95
-- (10:18) 94KL13X
-- (10:18) 6P58WS2
-- (10:19) 4328GD8
-- (10:20) G412CB7
-- (10:21) L93JTIZ
-- (10:23) 322W7JE
-- (10:23) 0NTHK55
SELECT name, id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "27" AND activity = "exit");
-- LICENSE PLATE OWNERS:
-- Vanessa (221103)
-- Barry (243696)
-- Iman (396669)
-- Sofia (398010)
-- Luca (467400)
-- Diana (514354)
-- Kelsey (560886)
-- Bruce (686048)

-- 3.2 ATM AT LEGGETT STREET
SELECT id, account_number FROM atm_transactions WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- IDS AND ACCOUNT NUMBERS:
-- (246) 28500762
-- (264) 28296815
-- (266) 76054385
-- (267) 49610011
-- (269) 16153065
-- (288) 25506511
-- (313) 81061156
-- (336) 26013199
SELECT name, id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- BANK ACCOUNT HOLDERS:
-- Bruce (686048)
-- Diana (514354)
-- Brooke (458378)
-- Kenny (395717)
-- Iman (396669)
-- Luca (467400)
-- Taylor (449774)
-- Benista (438727)
SELECT name, id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "27" AND activity = "exit");
-- (SUSPECTS):
-- Bruce (686048)
-- Diana (514354)
-- Iman (396669)
-- Luca (467400)

-- 3.3.1 PHONE CALL LESS THAN 1 MINUTE LONG
SELECT caller, receiver FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60";
-- CALLERS -> RECEIVERS:
-- (130) 555-0289 -> (996) 555-8899 
-- (499) 555-9472 -> (892) 555-8872 
-- (367) 555-5533 -> (375) 555-8161
-- (499) 555-9472 -> (717) 555-1342 
-- (286) 555-6063 -> (676) 555-6554 
-- (770) 555—1861 -> (725) 555-3243 
-- (031) 555-6622 -> (910) 555-3251 
-- (826) 555-1652 -> (066) 555—9701 
-- (338) 555-6650 -> (704) 555-2131 
SELECT name, id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60");
-- CALLERS:
-- Kenny (395717)
-- Sofia (398010)
-- Benista (438727)
-- Taylor (449774)
-- Diana (514354)
-- Kelsey (560886)
-- Bruce (686048)
-- Carina (907148)
SELECT name, id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "27" AND activity = "exit");
-- CALLERS WHO WENT TO THE BAKERY:
-- Sofia (398010)
-- Diana (514354)
-- Kelsey (560886)
-- Bruce (686048)
SELECT name, id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "27" AND activity = "exit");
-- (SUSPECTS):
-- Bruce (686048)
-- Diana (514354)

SELECT id, name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60");
-- RECEIVERS (SUSPECTS):
-- James (250277)
-- Larry (251693)
-- Anna (484375)
-- Jack (567218)
-- Melissa (626361)
-- Jacqueline (712712)
-- Philip (847116)
-- Robin (864400)
-- Doris (953679)

-- 3.3.2 The receiver bought the earliest flight ticket for the next morning to the thief
SELECT id, full_name FROM airports WHERE full_name LIKE "Fiftyville%";
-- ID:
-- 8
SELECT destination_airport_id, id, hour, minute FROM flights WHERE origin_airport_id = "8" AND year = "2021" AND month = "7" AND day = "29" AND hour < "13" ORDER BY hour ASC LIMIT 1;
-- Earliest fight departs at 8:20 am;
-- DESTINATION AIRPORT ID:
-- 4
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE origin_airport_id = "8" AND year = "2021" AND month = "7" AND day = "29" AND hour < "13" ORDER BY hour ASC LIMIT 1);
-- DESTINATION:
-- New York City
SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = "8" AND year = "2021" AND month = "7" AND day = "29" AND hour < "13" ORDER BY hour ASC LIMIT 1);
-- PASSPORT NUMBERS:
-- 7214083635
-- 1695452385
-- 5773159633
-- 1540955065
-- 8294398571
-- 1988161715
-- 9878712108
-- 8496433585
SELECT name, id FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = "8" AND year = "2021" AND month = "7" AND day = "29" AND hour < "13" ORDER BY hour ASC LIMIT 1));
-- PASSPORT OWNERS LEAVING FROM FIFTYVILLE TO NYC:
-- Kenny (395717)
-- Sofia (398010)
-- Taylor (449774)
-- Luca (467400)
-- Kelsey (560886)
-- Edward (651714)
-- Bruce (686048)
-- Doris (953679)
SELECT name, id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = "2021" AND month = "7" AND day = "28" AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = "2021" AND month = "7" AND day = "28" AND hour = "10" AND minute >= "15" AND minute <= "27" AND activity = "exit") AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = "8" AND year = "2021" AND month = "7" AND day = "29" AND hour < "13" ORDER BY hour ASC LIMIT 1));
-- THIEF:
-- Bruce (686048)

SELECT phone_number FROM people WHERE name = "Bruce";
-- (367) 555-5533
SELECT receiver FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60" AND caller = "(367) 555-5533";
-- (375) 555-8161
SELECT name, id FROM people WHERE phone_number = "(375) 555-8161";
-- ACCOMPLICE:
-- Robin (864400)

-- THIEF: Bruce
-- DESTINATION: New York City
-- ACCOMPLICE: Robin
