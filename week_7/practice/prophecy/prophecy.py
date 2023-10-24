from cs50 import SQL
import csv


def main():
    students_names = []
    houses = []
    heads = []
    relationship = []

    # Read csv file
    # Add student's name, house and head to their correnponding list
    with open("students.csv", newline="") as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            student_name = row["student_name"]
            house = row["house"]
            head = row["head"]
            relation = {"student_name" : row["student_name"], "house": row["house"]}

            add_student_names(student_name, students_names)
            add_houses(house, houses)
            add_heads(head, heads)
            add_relationship(relation, relationship)

    # Insert data from csv file to tables in roster.db file
    db = SQL("sqlite:///roster.db")

    for i in range(len(students_names)):
        db.execute("INSERT INTO students(student_name) VALUES (?)", students_names[i])
    
    for i in range(len(houses)):
        db.execute("INSERT INTO houses(house_name, head) VALUES (?, ?)", houses[i], heads[i])
    
    # An alternative for the avove loop would be:
    #for house, head in zip(houses, heads):
        #db.execute("INSERT INTO houses(house_name, head) VALUES (?, ?)", house, head)
    
    for i in range(len(relationship)):
        db.execute("INSERT INTO house_assigments(student_id, house_id) VALUES ((SELECT id FROM students WHERE student_name = ?), (SELECT id from houses WHERE house_name = ?))", relationship[i]["student_name"], relationship[i]["house"])

def add_student_names(student_name, students_names):
    if student_name not in students_names:
        students_names.append(student_name)

def add_houses(house, houses):
    if house not in houses:
        houses.append(house)

def add_heads(head, heads):
    if head not in heads:
        heads.append(head)

def add_relationship(relation, relationship):
    if relation not in relationship:
        relationship.append(relation)
        
if __name__ == "__main__":
    main()

