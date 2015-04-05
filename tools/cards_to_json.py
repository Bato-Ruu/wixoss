#!/usr/bin/python

import json
import sys
import csv
import re

carddata = open(sys.argv[1], encoding='utf-8', errors='replace', newline='')
data = []
cardreader = csv.DictReader(carddata, delimiter='\t')
for row in cardreader:
    row["Effects"] = dict()
    row["Effects"]["Constant"] = []
    row["Effects"]["On-Play"] = []
    row["Effects"]["Action"] = []
    current_effect = ""
    current_effect_key = ""
    for word in row["Text"].split():
        #if word == "{Constant}" or word == "{Action}" or word == "{On-Play}" or "Guard" in word or "Multi-Ener" in word or "||" in word:
        if word == "||":
            if current_effect_key != "":
                row["Effects"][current_effect_key].append(current_effect[1:])
            current_effect = ""
            continue
        if word == "{Constant}" or word == "{Action}" or word == "{On-Play}":
            if re.match("{[A-Za-z-]*}", word):
                current_effect_key = word[1:-1]
            else:
                current_effect_key = ""
            continue
        current_effect += " " + word
    if current_effect_key != "":
        row["Effects"][current_effect_key].append(current_effect[1:])
    data.append(row)
carddata.close()
carddata_json = open("cards.json", "w")

json.dump(data, carddata_json, indent=4, separators=(',', ': '))
carddata_json.close()
