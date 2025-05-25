git :
	git add .
	git commit -m "Fixed Bugs and added simulation mode" 
	git push

comp :
	g++ -std=c++17 -g *.cpp -o a; gdb ./a