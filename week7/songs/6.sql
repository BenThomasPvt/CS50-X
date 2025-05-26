SELECT name FROM songs
WHERE songs.artist_id =(
SELECT id FROM artists
WHERE name = 'Post Malone');
