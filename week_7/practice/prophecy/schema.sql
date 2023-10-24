DROP TABLE IF EXISTS students;

CREATE TABLE students (
    id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    house_name TEXT NOT NULL,
    head TEXT NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE house_assigments (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY (student_id) REFERENCES students(id)
    FOREIGN KEY (house_id) REFERENCES houses(id)
);

select * from houses where house_name = 'Slytherin';

select id from houses where house_name = 'Slytherin';

select * from house_assigments where house_id = 1;

select student_id from house_assigments where house_id = 1;

select student_id from house_assigments where house_id = (select id from houses where house_name = 'Slytherin');

select student_name from students where id in (select student_id from house_assigments where house_id = (select id from houses wh
ere house_name = 'Slytherin'));