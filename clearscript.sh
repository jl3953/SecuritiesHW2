rm /home/user03/printspooler/queue/*
original = $(umask)
umask 077
touch /home/user03/printspooler/queue/usersfiles
echo "10" > /home/user03/printspooler/queue/counter
umask $original
