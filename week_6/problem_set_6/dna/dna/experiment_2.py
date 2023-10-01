dic_1 =  {'name': 'Charlie', 'AGATC': '3', 'AATG': '2', 'TATC': '5'}
dic_2 = {"AGATC": 3, "AATG": 2, "TATC": 5}

def compare_dicts(d1, d2):
    for key in d2:
        # Check if key is in d1 and if the values match
        # Note: Convert values to integer for comparison as they are stored as strings in d1
        if int(d1[key]) != d2[key]:
            return False
    print("same")
        
result = compare_dicts(dic_1, dic_2)
print(result)