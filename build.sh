gcc lisp.c mpc.c -ledit -lm -o lisp 
if [ $? -eq 1 ]; then echo 'ERROR'
else ./lisp
fi