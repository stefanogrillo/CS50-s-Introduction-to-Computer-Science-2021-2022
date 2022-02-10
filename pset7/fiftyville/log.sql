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
