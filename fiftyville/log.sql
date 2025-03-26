-- Keep a log of any SQL queries you execute as you solve the mystery.



--! To understand more about when the theft stole cs50 duck and more info to understand the whole scene.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

--
SELECT id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id;

-- To get the flight's ids
SELECT id FROM flights WHERE;
1 .... 58


--! To get the destination_airport_ids
 SELECT origin_airport_id FROM flights WHERE (day = 28 AND month = 7) AND ((hour = 10 AND minute >= 15) OR hour > 10);
 8 8 8 2 6 1 6 8 8 7 3 4

--! To get the city the theft booked a flight from
SELECT city FROM airports JOIN flights ON airports.id = flights.origin_airport_id WHERE (origin_airport_id = 8) OR (origin_airport_id = 2) OR (origin_airport_id = 6) OR (origin_airport_id = 1) OR (origin_airport_id = 7) OR (origin_airport_id = 3) OR (origin_airport_id = 4);
Chicago /Beijing /Los Angles /New York City /Boston /Fiftyville

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--! To get the cities that the theft escaped to one of them
SELECT city FROM airports JOIN flights ON airports.id = flights.destination_airport_id WHERE destination_airport_id NOT IN (SELECT origin_airport_id FROM flights);
Delhi /San Fransico / Paris/ Tokyo

--! To get the ids from `crime_scene_reports` table
SELECT id FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
295
297

-- In my way to figure out the theft's name
SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 LIMIT 5;

-- In my way to figure out the accomplice's name
SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 LIMIT 5;

--! --! To get the bakery_security_logs ids by day, month, and hour
SELECt id FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10;
258 .... 271

--! To get the vehicles that were detected by the bakery's security system.
SELECT license_plate FROM bakery_security_logs WHERE (day = 28 AND month = 7) AND ((hour = 10) OR (hour = 9 AND minute >= 45) OR (hour = 11 AND minute < 0));
license_id  name    passport_number   activity  flight_id
R3G7486 Brandon  7874488539  enterance 10:8 2
13FNH73 Sophia   3642612721  ...  10:14     6
5P2BI95 Vanessa  2963008352  exit 10:16     2
94KL13X Bruce    5773159633  ..  10:18     36
6P58WS2 Barry    7526138472  ..  10:18
4328GD8 Luca     1207566299  ..  10:19     4
G412CB7 Sofia    1695452385  ..  10:20     36
L93JTIZ Iman     7049073643  ..  10:21     26
322W7JE Diana    3592750733  ..  10:23     54
0NTHK55 Kelsey   8294398571  ..  10:23     36
1106N58 Taylor   1988161715  ..  10:35     36


NRYN856 Denise   4001449165
WD5M8I6 Thomas   6034823042
V47T75I Jeremy   1207566299



--! To get the vehicles that were detected by the bakery's security system.
SELECT license_plate FROM bakery_security_logs WHERE (day = 28 AND month = 7) AND (hour = 10 AND minute >= 15);

--! To know the ids loged in 28 july from 9:45 to 10:15 a.m.
SELECT id FROM bakery_security_logs WHERE (day = 28 AND month = 7) AND ((hour = 10 AND minute >= 15) OR hour > 10 OR (hour = 9 AND minute >= 45));

260 ..... 292




--! To get the names of people from the `people` table who have a bank account and made the highest ATM transaction on the 28th of July.
SELECT name, atm_location, amount
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day IN (27,28) AND month = 7 AND transaction_type = 'withdraw' AND amount >= 50 ORDER BY amount DESC;

atm_location   amount  name    passport_number  activity flight_id license_plate origin_airport_id   destination_airport_id   city  phone_number (caller)   phone_number (receiver)
Humphrey Lane  100     Lisa
Humphrey Lane  100     Paul
Leggett Street 95      Barbara 1165086731                 41    HN8I106
Leggett Street 80      Brooke  4408372428  exit 14:57     53    QX4YZN3   8     9     -> Tokyo   (122) 555-4581     ------------- (831) 555-0973 accomplice is "Brenda"
Leggett Street 60      Taylor  1988161715  exit 10:35     36    1106N58   8     4     -> New york city (286) 555-6063 -----------  (676) 555-6554 43 min , accomplice is "James"
----(310) 555-8568
Leggett Street 55      Karen   5031682798                 39    IH61G08
Leggett Street 50      Bruce   5773159633  exit 10:18     36    94KL13X   8     4     -> New york city  (367) 555-5533 ---------  (375) 555-8161  45 min , accomplice is "Robin"
----(344) 555-9601, (022) 555-4052 , (704) 555-5790 75

Daboin Sanchez Drive .. Pamela
Carvalho Road  ..       Randy



--! To get the streets' names
SELECT street FROM crime_scene_reports WHERE day = 28 AND month = 7;
Axmark Road
Boyce Avenue
Humphrey Street
Widenius Street
Humphery Street


-- ! To get the passport number by `name`
SELECT passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE name = 'Karen' ;

SELECT activity FROM bakery_security_logs WHERE (day = 28 AND month = 7) AND (hour = 10 AND minute >= 15);













    asada
    addad
    addad

tab shift

        asada
        addad
        addad

shift tab

    asada
    addad
    addad
