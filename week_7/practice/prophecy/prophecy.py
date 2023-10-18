from cs50 import SQL

from cs50 import SQL
import csv


def main():
    students_names = []
    houses = []
    heads = []

    # Read csv file
    # Add student's name, house and head to their correnponding list
    with open("students.csv", newline="") as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            student_name = row["student_name"]
            house = row["house"]
            head = row["head"]

            add_student_names(student_name, students_names)
            add_houses(house, houses)
            add_heads(head, heads)

    # Insert data from csv file to tables in roster.db file
    db = SQL("sqlite:///roster.db")

    for student_name in students_names:
        db.execute("INSERT INTO students(student_name) VALUES (?)", student_name)
    
    for house in houses:
        db.execute("INSERT INTO houses(house_name) VALUES (?)", house)
    
    for head in heads:
        db.execute("INSERT INTO houses(head) VALUES (?)", head)
    
    #for house, head in zip(houses, heads):
        #db.execute("INSERT INTO houses(house_name, head) VALUES (?, ?)", house, head)

def add_student_names(student_name, students_names):
    if student_name not in students_names:
        students_names.append(student_name)


def add_houses(house, houses):
    if house not in houses:
        houses.append(house)

def add_heads(head, heads):
    if head not in heads:
        heads.append(head)
        
if __name__ == "__main__":
    main()

