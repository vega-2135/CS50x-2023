UPDATE shows SET title = 'How I Met Your Mother' WHERE title LIKE 'How i met your mother';
UPDATE shows SET title = 'Brooklyn Nine-Nine' WHERE title LIKE 'b%99';
UPDATE shows SET title = 'Game of Thrones' WHERE title LIKE 'game%';
UPDATE shows SET title = 'Game of Thrones' WHERE title LIKE 'GoT';
UPDATE shows SET title = 'Grey''s Anatomy' WHERE title LIKE 'grey%';
SELECT * FROM shows ORDER BY title ASC;
UPDATE shows SET title = 'It''s Always Sunny in Philadelphia' WHERE title =  'Its Always Sunny in Philidelphia';
