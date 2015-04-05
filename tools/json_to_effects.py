#!/usr/bin/python

import json
import sqlite3
import os
import sys

DATABASE = "cards.db"
try:
    os.remove(DATABASE)
except:
    pass
conn = sqlite3.connect(DATABASE, check_same_thread=False)

c = conn.cursor()
c.execute('CREATE TABLE IF NOT EXISTS Cards (Id INTEGER PRIMARY KEY, Name TEXT)')
c.execute('CREATE TABLE IF NOT EXISTS Effects (Id INTEGER PRIMARY KEY, Effect TEXT)')
c.execute('CREATE TABLE IF NOT EXISTS Timings (Id INTEGER PRIMARY KEY, Timing TEXT)')
c.execute('CREATE TABLE IF NOT EXISTS CardsToEffects (Id INTEGER PRIMARY KEY, Card INTEGER, Effect INTEGER)')
c.execute('CREATE TABLE IF NOT EXISTS TimingsToEffects (Id INTEGER PRIMARY KEY, Timing INTEGER, Effect INTEGER)')
c.execute('INSERT INTO Timings (Timing) VALUES(?)', ("Action",))
c.execute('INSERT INTO Timings (Timing) VALUES(?)', ("Constant",))
c.execute('INSERT INTO Timings (Timing) VALUES(?)', ("On-Play",))

conn.commit()

card_json = open("cards.json", "r")
card_dict = json.load(card_json)
card_json.close()

for card in card_dict:
    c.execute('INSERT OR REPLACE INTO Cards (Name) VALUES(?)', (card["Name"],))
    card_id = c.lastrowid
    if len(card["Effects"].keys()) > 0:
        for key in card["Effects"].keys():
            c.execute('SELECT * FROM Timings WHERE Timing LIKE ?', (key,))
            (timing_id, _) = c.fetchone()
            c.execute('INSERT INTO Effects (Effect) VALUES(?)', (card["Effects"][key],))
            effect_id = c.lastrowid
            c.execute('INSERT INTO TimingsToEffects (Timing, Effect) VALUES(?, ?)', (timing_id, effect_id))
            c.execute('INSERT INTO CardsToEffects (Card, Effect) VALUES(?, ?)', (card_id, effect_id))
    print(str(card_id) + "|" + card["Name"])

conn.commit()
