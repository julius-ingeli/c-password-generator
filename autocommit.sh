#!/bin/sh
sudo git add .
echo Insert commit message:
read word
git commit -m "$word"
git push
echo Push to remote repo complete. Press ENTER to exit.
read
