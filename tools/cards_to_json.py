#!/usr/bin/python

import json
import sys
import csv

carddata = open(sys.argv[1], encoding='utf-8', errors='replace', newline='')
data = []
cardreader = csv.DictReader(carddata, delimiter='\t')
for row in cardreader:
    row["Effects"] = dict()
    if "{Constant}" in row["Text"]:
        row["Effects"]["Constant"] = row["Text"]
    if "{On-Play}" in row["Text"]:
        row["Effects"]["On-Play"] = row["Text"]
    if "{Action}" in row["Text"]:
        row["Effects"]["Action"] = row["Text"]
    data.append(row)
carddata.close()
carddata_json = open("cards.json", "w")

json.dump(data, carddata_json, indent=4, separators=(',', ': '))
carddata_json.close()
